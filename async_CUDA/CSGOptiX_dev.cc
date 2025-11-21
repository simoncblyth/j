

Problematic SYNC::

    CUstream stream = 0 ;
    OPTIX_CHECK( optixLaunch(...) );
    CUDA_SYNC_CHECK();



Pool of streams::

    static const int NUM_STREAMS = 16;
    static cudaStream_t streams[NUM_STREAMS] = {0};
    static cudaEvent_t  events[NUM_STREAMS]   = {0};
    static bool initialized = false;

    if(!initialized) {
        for(int i=0; i<NUM_STREAMS; i++) {
            cudaStreamCreate(&streams[i]);
            cudaEventCreateWithFlags(&events[i], cudaEventDisableTiming);
        }
        initialized = true;
    }

    int idx = kernel_count % NUM_STREAMS;
    cudaStream_t stream = streams[idx];

    OPTIX_CHECK( optixLaunch(pip->pipeline, (CUstream)stream, d_param, sizeof(Params),
                             &(sbt->sbt), width, height, depth) );

    cudaEventRecord(events[idx], stream);

    // Record the global event used by SPM
    cudaEventRecord(spm.all_partials_done, stream);

    // Async collect into NPFold
    spm.add_partial_inmemory(d_partial, num_partial, stream);

    kernel_count++;



Then at very end::

    cudaEventSynchronize(spm.all_partials_done);   // one single sync
    // or cudaStreamWaitEvent(final_stream, spm.all_partials_done, 0);

    NP* final_result = spm.finalize_inmemory(time_window, 0);






Grok hyperbolae::

    OptixModuleCompileOptions module_opts = {};
    module_opts.maxRegisterCount     = 0;                     // let driver decide
    module_opts.optLevel             = OPTIX_COMPILE_OPTIMIZATION_LEVEL_3;
    module_opts.debugLevel           = OPTIX_COMPILE_DEBUG_LEVEL_NONE;

    // 2024–2025 killer flags
    module_opts.boundValues          = nullptr;
    module_opts.numBoundValues       = 0;

    // These two are the big ones in OptiX 8
    module_opts.flags                = OPTIX_COMPILE_FLAG_PREFER_FAST_TRACE;  // ← new in 8.0
    module_opts.maxPayloadTypes      = 4;   // if you have multiple payload layouts



::

    // Record size must be multiple of OPTIX_SBT_RECORD_ALIGNMENT (64 bytes on NVIDIA)
    struct HitRecord {
        alignas(OPTIX_SBT_RECORD_ALIGNMENT) char header[32];
        float3   data[8];    // geometry data, material params, etc.
    };
    static_assert(sizeof(HitRecord) % OPTIX_SBT_RECORD_ALIGNMENT == 0);






how streams, events, records play together ?



Object,Lives on,What it really is,Lifetime / Scope
cudaStream_t,Host (just a pointer),"A queue of GPU work (kernels, memcpys, etc.)",You create/destroy it
cudaEvent_t,GPU + tiny host handle,A single bit of state on the GPU: “has this happened yet?”,"Created once, reused thousands of times"
"cudaEventRecord(event, stream)",Enqueues a tiny GPU op,“When everything before me in this stream finishes → set event = done”,Does NOT block anything






The Golden Rules (memorize these)

1. cudaEventRecord(event, stream) never blocks the host
    It just drops a tiny marker into the stream. Cost: ~1–2 µs.
 
2. An event becomes “signaled” only when ALL work queued BEFORE the record in that stream has finished.
     
3. Events are stream-specific
   If you record the same event on stream A and stream B, it becomes signaled only when both streams have reached 
   their respective cudaEventRecord calls.

4. You can record the same event on 1000 different streams → it becomes signaled when the 
   last of those streams reaches its record.


Synchronization primitives::

    cudaEventSynchronize(event);   // host blocks until event signaled
    cudaStreamWaitEvent(stream, event, 0);  // stream blocks until event signaled
    cudaEventQuery(event);         // non-blocking poll


















One global event pattern::

    class SPM {
        cudaEvent_t all_partials_done = nullptr;
        bool created = false;

        void ensure_event() {
            if(!created) {
                cudaEventCreateWithFlags(&all_partials_done, cudaEventDisableTiming);
                created = true;
            }
        }

    public:
        void add_partial_inmemory(sphotonlite* d_ptr, size_t n, cudaStream_t stream)
        {
            ensure_event();
            // ... your async D→H copy + callback that adds to NPFold

            // THIS IS THE ONLY LINE THAT MATTERS:
            cudaEventRecord(all_partials_done, stream);
        }

        void wait_for_all() {
            cudaEventSynchronize(all_partials_done);  // one single block, usually < 50 ms
        }
    };











::

    static cudaEvent_t global_done = nullptr;
    if(!global_done) cudaEventCreateWithFlags(&global_done, cudaEventDisableTiming);

    cudaStream_t stream = streams[kernel_count % 16];
    optixLaunch(..., (CUstream)stream, ...);
    SPM::add_partial_inmemory(d_partial, count, stream);

    // THIS IS THE MONEY LINE:
    cudaEventRecord(global_done, stream);


::

    cudaEventSynchronize(global_done);   // one sync, safe forever
    NP* final = spm.finalize_inmemory(...);












Multi-event pattern 



Q: Opticks optical photon simulation is organized into physics events, associated
   to the Geant4 events. How to use the one global event pattern in that case when
   everything needs to be repeated, with different seeds hundreds of times ?

A: Do NOT use one single global event for the entire run.
   Instead, use one event per physics event (i.e. per G4 event).
   This gives you perfect isolation, perfect overlap, 
   and zero crosstalk between events — while still getting >95 % GPU utilization.


::

    struct OpticksEvent
    {
        int               event_id;         // G4 event number
        uint64_t          seed_offset;      // different per event
        NPFold*           fold = nullptr;  // collects partials for THIS event only
        cudaEvent_t       done_evt = nullptr;
        cudaStream_t      stream = nullptr; // dedicated or from pool

        ~OpticksEvent() {
            if(done_evt) cudaEventDestroy(done_evt);
            if(stream)   cudaStreamDestroy(stream);
            delete fold;
        }
    };







::

    std::vector<std::unique_ptr<OpticksEvent>> running_events;
    const int MAX_CONCURRENT_EVENTS = 32;   // 16–64 typical on H100/A100

    for(int g4_event_id = 0; g4_event_id < num_g4_events; g4_event_id++)
    {
        // 1. create a fresh event container
        auto ev = std::make_unique<OpticksEvent>();
        ev->event_id = g4_event_id;
        ev->seed_offset = g4_event_id * 1000000ull;   // or proper RNG offset
        ev->fold = new NPFold;
        cudaStreamCreate(&ev->stream);
        cudaEventCreateWithFlags(&ev->done_evt, cudaEventDisableTiming);

        // 2. launch N torchgen + OptiX launches for this event only
        for(int torch = 0; torch < num_torches_per_event; torch++)
        {
            cudaStream_t stream = ev->stream;           // same stream for whole event → max overlap
            // or use a small pool inside the event if you prefer

            // set per-photon seeds using ev->seed_offset + torch + photon_idx

            optixLaunch(pipeline, (CUstream)stream, d_param, ...);

            // your per-launch merge_partial_select → d_partial_hits
            SPM::add_partial_inmemory(d_partial_hits, count, stream, ev->fold); // ← pass fold
        }

        // 3. mark that this physics event is done when its stream finishes
        cudaEventRecord(ev->done_evt, ev->stream);

        running_events.push_back(std::move(ev));

        // 4. reap completed events (non-blocking)
        for(auto it = running_events.begin(); it != running_events.end(); )
        {
            auto& e = *it;
            if(cudaEventQuery(e->done_evt) == cudaSuccess)
            {
                // THIS EVENT IS 100% FINISHED → safe to finalize
                NP* final_hits = SPM::finalize_one_event(e->fold, time_window, e->stream);

                // save or upload to Geant4 / analysis
                save_event_to_SEvt(g4_event_id, final_hits);

                it = running_events.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // 5. optional: throttle concurrency
        if(running_events.size() >= MAX_CONCURRENT_EVENTS)
        {
            // block only until the oldest event finishes
            auto& oldest = running_events.front();
            cudaEventSynchronize(oldest->done_evt);
            // then the loop above will reap it
        }
    }










