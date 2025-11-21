
void SPM::add_partial_inmemory(sphotonlite* d_partial, size_t count, cudaStream_t stream)
{
    if(count == 0) { cudaFreeAsync(d_partial, stream); return; }

    if(!master_fold) master_fold = new NPFold ;

    // 1. bring data to host pinned memory (async)
    sphotonlite* h_pinned = nullptr;
    cudaMallocAsync(&h_pinned, count * sizeof(sphotonlite), stream);
    cudaMemcpyAsync(h_pinned, d_partial, count * sizeof(sphotonlite), cudaMemcpyDeviceToHost, stream);

    // 2. need to free device buffer after copy completes → use a stream callback
    struct CallbackData {
        sphotonlite* h_pinned ;
        sphotonlite* d_partial ;
        NPFold* fold ;
        int idx ;
    };
    CallbackData* cb = new CallbackData{h_pinned, d_partial, master_fold, subfold_idx++};

    cudaStreamAddCallback(stream, [](cudaStream_t, cudaError_t, void* userData) {
        CallbackData* d = (CallbackData*)userData;

        // create NP array owning the pinned memory (NP takes ownership)
        NP* a = NP::FromData(h_pinned, count, sizeof(sphotonlite)/sizeof(float)); // shape (count,4,4) or whatever your layout is
        // or simply: NP* a = new NP(h_pinned, count, 16, 4);  // 16 floats = 64 bytes = sphotonlite

        char subname[16];
        snprintf(subname, 16, "%d", d->idx);
        d->fold->add_subfold(subname, a);   // subfold now owns the NP*

        cudaFree(d->d_partial);   // safe now
        delete d;
    }, cb, 0);
        // or cudaMallocAsync + callback if you prefer
}


NP* SPM::finalize_inmemory(float time_window, cudaStream_t stream)
{
    if(!master_fold || master_fold->subfold.empty()) return nullptr;

    // 1. concatenate all partials into one huge flat array (still on host RAM)
    NP* all_hits = master_fold->concat_("hit");   // you decide the key, e.g. "hit" or just use default
    // all_hits now owns the concatenated buffer, subfolds can be cleared

    size_t total = all_hits->num_items();

    // 2. upload the entire thing to GPU once
    sphotonlite* d_all = nullptr;
    cudaMallocAsync(&d_all, total * sizeof(sphotonlite), stream);
    cudaMemcpyAsync(d_all, (sphotonlite*)all_hits->bytes(), total * sizeof(sphotonlite),
                    cudaMemcpyHostToDevice, stream);

    // 3. run your existing merge_partial_select logic on the full array
    //    (it already handles the sentinel, reduction, etc.)
    sphotonlite* d_merged = nullptr;
    size_t      num_merged = 0;

    merge_partial_select(d_all, total, &d_merged, &num_merged,
                         0xffffffffu,   // or your select_flagmask
                         time_window, stream);

    cudaFreeAsync(d_all, stream);

    // 4. bring back to host as NP* for downstream consumers
    NP* result = NP::make(num_merged, 4, 4);  // or whatever shape
    result->read( (float*)d_merged, num_merged*16*sizeof(float) ); // or async + callback

    cudaFreeAsync(d_merged, stream);

    delete master_fold;
    master_fold = nullptr;
    subfold_idx = 0;

    return result;   // owned by caller
}





/**
Recommended for 99 % of cases: One single cudaEvent_t per launch +
cudaEventSynchronize just before finalize (simplest & bulletproof)


**/



class SPM {
    cudaEvent_t   all_partials_done = nullptr;   // created once
    bool          event_created = false;
public:
    void add_partial_inmemory(sphotonlite* d_partial, size_t count, cudaStream_t stream)
    {
        if(count == 0) { cudaFreeAsync(d_partial, stream); return; }

        if(!master_fold) master_fold = new NPFold;

        // record the event on THIS stream the very last thing we do with this launch
        if(!event_created) {
            cudaEventCreateWithFlags(&all_partials_done, cudaEventDisableTiming);
            event_created = true;
        }
        cudaEventRecord(all_partials_done, stream);   // <<< THIS IS THE KEY

        // … same callback as before that does cudaMemcpyAsync → host → NP::FromData → add_subfold
        // the callback frees d_partial and adds the subfold
    }

    NP* finalize_inmemory(float time_window, cudaStream_t final_stream)
    {
        if(!master_fold) return nullptr;

        // BLOCK HERE until **every single launch** has finished its memcpy + callback
        cudaEventSynchronize(all_partials_done);   // <--- one single sync, usually < 50 ms

        // NOW it is 100 % safe → all subfolds are populated
        return finalize_inmemory_fast(time_window, final_stream);
    }

    ~SPM() {
        if(event_created) cudaEventDestroy(all_partials_done);
    }
};



Review the relationship between cudaEvent_t cudaStream_t and use of cudaEventRecord cudaEventSynchronize.
Opticks uses a single instance of an SEvt struct to manage physics event data


