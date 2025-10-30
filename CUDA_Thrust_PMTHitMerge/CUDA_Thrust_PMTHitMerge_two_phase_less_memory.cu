/**
CUDA_Thrust_PMTHitMerge_two_phase_less_memory.cu
====================================================


Core Idea: In-Place Sort + Compact Key
We eliminate separate keys and times arrays by:

Packing (pmtid, time_bucket, time) into a single uint64_t
→ key = (pmtid << 32) | (bucket << 16) | (time_encoded)

Sorting in-place on this packed array

Run-length encoding (RLE) to count unique (pmtid, bucket)

Second pass to compute min(time) per group


**/


#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/scan.h>
#include <thrust/unique.h>
#include <thrust/execution_policy.h>

using namespace thrust;

// ------------------------------------------------------------------
// 1. Pack: (pmtid, time_bucket, quantized_time) → uint64_t
struct pack_key_time {
    const float time_window;
    __host__ __device__ pack_key_time(float tw) : time_window(tw) {}

    __host__ __device__
    uint64_t operator()(const RawHit& h) const {
        int bucket = static_cast<int>(h.time / time_window);

        // Quantize time to 16-bit (0–65535) → ~1e-4 precision
        uint16_t t16 = static_cast<uint16_t>(
            __saturate(h.time / time_window - bucket) * 65535.0f + 0.5f);

        return (static_cast<uint64_t>(h.pmtid) << 32) |
               (static_cast<uint64_t>(bucket)   << 16) |
               (static_cast<uint64_t>(t16));
    }
};

// ------------------------------------------------------------------
// 2. Extract full key: (pmtid, bucket) only
__device__ __host__
uint64_t full_key(uint64_t packed) {
    return packed & 0xFFFFFFFF0000ULL;  // mask out time16
}

// ------------------------------------------------------------------
// PHASE 1: Count merged hits
int count_merged_hits_gpu(const RawHit* d_raw, int N, float time_window)
{
    device_vector<uint64_t> packed(N);

    // Pack everything into 64-bit
    transform(device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)),
              device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)) + N,
              packed.begin(),
              pack_key_time(time_window));

    // Sort by full key (pmtid, bucket)
    sort(packed.begin(), packed.end(),
         [] __device__ (uint64_t a, uint64_t b) {
             return full_key(a) < full_key(b);
         });

    // Count unique full keys
    auto last = unique(packed.begin(), packed.end(),
                       [] __device__ (uint64_t a, uint64_t b) {
                           return full_key(a) == full_key(b);
                       });

    return last - packed.begin();
}

// ------------------------------------------------------------------
// PHASE 2: Fill merged hits
void fill_merged_hits_gpu(
    const RawHit* d_raw, int N, float time_window,
    MergedHit* d_merged, int merged_count)
{
    device_vector<uint64_t> packed(N);
    device_ptr<MergedHit> out(d_merged);

    // Repack + sort (same as phase 1)
    transform(device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)),
              device_ptr<const RawHit>(const_cast<RawHit*>(d_raw)) + N,
              packed.begin(),
              pack_key_time(time_window));

    sort(packed.begin(), packed.end(),
         [] __device__ (uint64_t a, uint64_t b) {
             return full_key(a) < full_key(b);
         });

    // RLE: find run starts
    device_vector<int> run_start(merged_count);
    device_vector<int> flags(N, 0);

    // Flag first element of each run
    auto flag_first = [] __device__ (int i, const uint64_t* data) {
        if (i == 0) return 1;
        return full_key(data[i]) != full_key(data[i-1]) ? 1 : 0;
    };

    transform(counting_iterator<int>(0), counting_iterator<int>(N),
              packed.begin(), flags.begin(),
              [packed_data = thrust::raw_pointer_cast(packed.data())] __device__ (int i, uint64_t _) {
                  return flag_first(i, packed_data);
              });

    exclusive_scan(flags.begin(), flags.end(), run_start.begin(), 0);

    // Final reduction per run
    for_each(counting_iterator<int>(0), counting_iterator<int>(merged_count),
             [=] __device__ (int run_idx) {
                 int start = run_start[run_idx];
                 int end   = (run_idx + 1 < merged_count) ? run_start[run_idx + 1] : N;

                 uint64_t first = packed[start];
                 int pmtid = first >> 32;
                 float min_time = __half2float(__ushort_as_half(first & 0xFFFF));

                 // Scan for min time
                 for (int i = start + 1; i < end; ++i) {
                     float t = __half2float(__ushort_as_half(packed[i] & 0xFFFF));
                     if (t < min_time) min_time = t;
                 }

                 // Reconstruct full time: bucket * window + fractional
                 int bucket = (first >> 16) & 0xFFFF;
                 float full_time = bucket * time_window + min_time;

                 out[run_idx] = {pmtid, full_time, end - start};
             });
}


