


    // Input: one entry per photon that flagged a hit
    struct RawHit {
        int   pmtid;      // 4 B
        float time;       // 4 B
        // (optional: photon index, energy, …)
    };

    // Output: one merged hit per (pmtid, time_bucket)
    struct MergedHit {
        int   pmtid;      // 4 B
        float time;       // 4 B  (first photon time in the bucket)
        int   count;      // 4 B
    };




/**

1. Compute time_bucket = floor(time / time_window)   (int)
2. Sort raw hits by  (pmtid, time_bucket)            // thrust::sort
3. Run-length-encode (RLE) on the sorted keys:
        • same key → same merged hit
        • keep min(time) and count photons
4. Write one MergedHit per run

**/



#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/scan.h>
#include <thrust/unique.h>
#include <thrust/execution_policy.h>

using namespace thrust::placeholders;

// ------------------------------------------------------------------
// 1. Helper: key = (pmtid, time_bucket)
struct hit_key_functor {
    const float time_window;
    __host__ __device__ hit_key_functor(float tw) : time_window(tw) {}

    __host__ __device__
    uint64_t operator()(const RawHit& h) const {
        int bucket = static_cast<int>(h.time / time_window);
        // pack 32-bit pmtid (high) + 32-bit bucket (low)
        return (static_cast<uint64_t>(h.pmtid) << 32) | (static_cast<uint32_t>(bucket) & 0xFFFFFFFFULL);
    }
};

// ------------------------------------------------------------------
// 2. Functor to emit the *first* time in a run
struct first_time_functor {
    __host__ __device__
    float operator()(const RawHit& h) const { return h.time; }
};

// ------------------------------------------------------------------
void merge_hits_gpu(
        const RawHit*   d_raw,          // size = N
        int             N,
        float           time_window,
        MergedHit*      d_merged,       // output buffer (size >= N)
        int*            d_num_merged)   // returns final count
{
    using namespace thrust;

    // ------------------------------------------------------------------
    // 0. Thrust device vectors (wrap raw pointers)
    device_ptr<const RawHit>  raw_ptr(const_cast<RawHit*>(d_raw));
    device_ptr<MergedHit>     merged_ptr(d_merged);

    // ------------------------------------------------------------------
    // 1. Build parallel arrays: key, time, index (for ordering)
    device_vector<uint64_t>  keys(N);
    device_vector<float>     times(N);
    device_vector<int>       indices(N);

    // Fill keys : packed (pmtid, time_bucket)
    transform(raw_ptr, raw_ptr + N, keys.begin(), hit_key_functor(time_window));

    // Fill times (needed for min)  exact hit times
    transform(raw_ptr, raw_ptr + N, times.begin(), first_time_functor());

    // Fill indices 0 … N-1
    counting_iterator<int> zero(0);
    copy(zero, zero + N, indices.begin());

    // ------------------------------------------------------------------
    // 2. Sort everything by key (stable order → earliest raw time first)
    sort_by_key(keys.begin(),  keys.end(), make_zip_iterator(make_tuple(times.begin(), indices.begin())));

    // ------------------------------------------------------------------
    // 3. Run-length encode: find segment boundaries
    device_vector<int> segment_flags(N, 0);
    // flag = 1 where key[i] != key[i-1]
    auto key_it = keys.begin();
    transform(make_counting_iterator(1), make_counting_iterator(N),
              keys.begin(), segment_flags.begin(),
              [key_it] __device__ (int i, uint64_t prev_key) {
                  return (key_it[i] != prev_key) ? 1 : 0;
              });

    // exclusive scan → start index of each run
    device_vector<int> run_start(N);
    exclusive_scan(segment_flags.begin(), segment_flags.end(), run_start.begin(), 0);

    // ------------------------------------------------------------------
    // 4. Reduce per run: min(time) + count
    int num_runs = *thrust::max_element(run_start.begin(), run_start.end()) + 1;

    // Allocate output exactly
    device_vector<MergedHit> temp_merged(num_runs);

    // Kernel that writes one MergedHit per run
    // (could also be done with thrust::reduce_by_key – see variant below)
    thrust::for_each(thrust::make_counting_iterator(0),
                     thrust::make_counting_iterator(num_runs),
    [=] __device__ (int run_idx) {
        int start = run_start[run_idx];                 // first element of run
        int end   = (run_idx + 1 < num_runs) ? run_start[run_idx+1] : N;

        uint64_t key = keys[start];
        int pmtid    = static_cast<int>(key >> 32);
        // int bucket   = static_cast<int>(key & 0xFFFFFFFFULL);  // not needed

        float min_time = times[start];
        for (int i = start + 1; i < end; ++i) {
            if (times[i] < min_time) min_time = times[i];
        }

        int count = end - start;

        temp_merged[run_idx] = {pmtid, min_time, count};
    });

    // ------------------------------------------------------------------
    // 5. Copy back to user buffer
    int final_count = static_cast<int>(temp_merged.size());
    copy(temp_merged.begin(), temp_merged.end(), merged_ptr);
    cudaMemcpyAsync(d_num_merged, &final_count, sizeof(int), cudaMemcpyHostToDevice);
}



// after photon propagation
thrust::device_vector<RawHit> d_hits = select_hits_with_thrust(d_photons, num_photons);

// merge
MergedHit* d_merged;
int*       d_count;
cudaMalloc(&d_merged, sizeof(MergedHit)*d_hits.size());
cudaMalloc(&d_count,  sizeof(int));

merge_hits_gpu(thrust::raw_pointer_cast(d_hits.data()),
               d_hits.size(),
               time_window,
               d_merged,
               d_count);

// copy back
int host_count;
cudaMemcpy(&host_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);
std::vector<MergedHit> h_merged(host_count);
cudaMemcpy(h_merged.data(), d_merged, host_count*sizeof(MergedHit), cudaMemcpyDeviceToHost);









/**

if dont need the exact first time and are okay with any time from the group (the min can be obtained with a custom reducer), use:


struct min_time_count {
    float time;
    int   count;
    __host__ __device__ min_time_count() : time(FLT_MAX), count(0) {}
};

struct reducer {
    __host__ __device__
    min_time_count operator()(const min_time_count& a, const min_time_count& b) const {
        min_time_count r;
        r.time  = min(a.time, b.time);
        r.count = a.count + b.count;
        return r;
    }
};

thrust::reduce_by_key(keys.begin(), 
                      keys.end(),
                      thrust::make_zip_iterator(thrust::make_tuple(times.begin(),thrust::make_constant_iterator(1))),
                      keys_out.begin(),
                      zip_out.begin(),
                      thrust::equal_to<uint64_t>(),
                      reducer());




**/



