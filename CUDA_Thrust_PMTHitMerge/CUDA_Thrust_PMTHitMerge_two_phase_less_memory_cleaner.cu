/**
CUDA_Thrust_PMTHitMerge_two_phase_less_memory_cleaner.cu
===========================================================


**/


#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/scan.h>
#include <thrust/unique.h>

using namespace thrust;

struct PMTHitMergerGPU 
{
    // Internal buffers
    device_vector<uint64_t> packed;
    device_vector<int>      flags;
    device_vector<int>      run_start;

    float time_window;

    // ------------------------------------------------------------------
    PMTHitMergerGPU(float tw) : time_window(tw) {}

    // ------------------------------------------------------------------
    // PHASE 1: Pack + sort + count unique (pmtid, bucket)
    int count_merged(const RawHit* d_raw, int N)
    {
        packed.resize(N);
        flags.resize(N);

        // 1. Pack: (pmtid << 32) | (bucket << 16) | time16
        transform(device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)),
                  device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)) + N,
                  packed.begin(),
                  [tw = time_window] __device__ (const RawHit& h) -> uint64_t {
                      int bucket = static_cast<int>(h.time / tw);
                      float frac = h.time / tw - bucket;
                      uint16_t t16 = static_cast<uint16_t>(__saturate(frac) * 65535.0f + 0.5f);
                      return (static_cast<uint64_t>(h.pmtid) << 32) |
                             (static_cast<uint64_t>(bucket)   << 16) |
                             t16;
                  });

        // 2. Sort by full key: (pmtid, bucket)
        sort(packed.begin(), packed.end(),
             [] __device__ (uint64_t a, uint64_t b) {
                 return (a & 0xFFFFFFFF0000ULL) < (b & 0xFFFFFFFF0000ULL);
             });

        // 3. Count unique keys
        auto last = unique(packed.begin(), packed.end(),
                           [] __device__ (uint64_t a, uint64_t b) {
                               return (a & 0xFFFFFFFF0000ULL) == (b & 0xFFFFFFFF0000ULL);
                           });

        return last - packed.begin();
    }

    // ------------------------------------------------------------------
    // PHASE 2: Fill pre-allocated output using already-packed data
    void fill_merged(MergedHit* d_out, int merged_count)
    {
        run_start.resize(merged_count);

        // Flag first element of each run
        auto flag_first = [data = raw_pointer_cast(packed.data())] __device__ (int i) -> int {
            if (i == 0) return 1;
            uint64_t key_prev = data[i-1] & 0xFFFFFFFF0000ULL;
            uint64_t key_curr = data[i]   & 0xFFFFFFFF0000ULL;
            return key_curr != key_prev;
        };

        transform(counting_iterator<int>(0), counting_iterator<int>(packed.size()),
                  flags.begin(), flag_first);

        exclusive_scan(flags.begin(), flags.end(), run_start.begin(), 0);

        device_ptr<MergedHit> out(d_out);

        // Reduce per run: min(time), count
        for_each(counting_iterator<int>(0), counting_iterator<int>(merged_count),
                 [=] __device__ (int idx) {
                     int start = run_start[idx];
                     int end   = (idx + 1 < merged_count) ? run_start[idx + 1] : packed.size();

                     uint64_t first = packed[start];
                     int pmtid = first >> 32;
                     int bucket = (first >> 16) & 0xFFFF;
                     float min_frac = __half2float(__ushort_as_half(first & 0xFFFF));

                     for (int i = start + 1; i < end; ++i) {
                         float t = __half2float(__ushort_as_half(packed[i] & 0xFFFF));
                         if (t < min_frac) min_frac = t;
                     }

                     float time = bucket * time_window + min_frac;
                     int count = end - start;

                     out[idx] = {pmtid, time, count};
                 });
    }

    // ------------------------------------------------------------------
    // Convenience: one-call with auto-allocation
    MergedHit* merge_and_alloc(const RawHit* d_raw, int N, int* out_count)
    {
        int count = count_merged(d_raw, N);
        MergedHit* d_out = nullptr;
        cudaMalloc(&d_out, count * sizeof(MergedHit));
        fill_merged(d_out, count);
        if (out_count) *out_count = count;
        return d_out;
    }
};




// In your Opticks pipeline
PMTHitMergerGPU merger(1.0f);  // time_window = 1 ns

// PHASE 1: Count
int n_merged = merger.count_merged(d_raw_hits, n_hits);

// PHASE 2: Allocate exactly + fill
MergedHit* d_merged = nullptr;
cudaMalloc(&d_merged, n_merged * sizeof(MergedHit));
merger.fill_merged(d_merged, n_merged);

// Or one-liner (if you don't need reuse):
MergedHit* d_merged = merger.merge_and_alloc(d_raw_hits, n_hits, nullptr);








// In your hit processing system:
class HitProcessor {
    PMTHitMergerGPU merger;

public:
    HitProcessor(float tw) : merger(tw) {}

    MergedHit* process(const RawHit* d_hits, int n, int* count) {
        int m = merger.count_merged(d_hits, n);
        MergedHit* d_out = alloc_device<MergedHit>(m);
        merger.fill_merged(d_out, m);
        if (count) *count = m;
        return d_out;
    }
};





