/**
CUDA_Thrust_PMTHitMerge_reduce_by_key.cu
=========================================

**/


#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/reduce.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/tuple.h>

using namespace thrust;

// ------------------------------------------------------------------
// Structs
struct RawHit { int pmtid; float time; };
struct MergedHit { int pmtid; float time; int count; };

// ------------------------------------------------------------------
struct PMTHitMergerGPU {
    float time_window;

    // Reusable buffers
    device_vector<uint64_t> keys;
    device_vector<float>    times;
    device_vector<int>      counts;

    PMTHitMergerGPU(float tw) : time_window(tw) {}

    // --------------------------------------------------------------
    // PREPARE: Pack + sort (once)
    void prepare(const RawHit* d_raw, int N)
    {
        if (N == 0) return;

        keys.resize(N);
        times.resize(N);
        counts.resize(N);

        // 1. Pack: key = (pmtid << 32) | bucket
        //          value = (time_frac, 1)
        auto zip_out = make_zip_iterator(make_tuple(keys.begin(), times.begin(), counts.begin()));
        transform(counting_iterator<int>(0), counting_iterator<int>(N),
                  zip_out,
                  [=] __device__ (int i) -> tuple<uint64_t, float, int> {
                      const RawHit& h = d_raw[i];
                      int bucket = static_cast<int>(h.time / time_window);
                      float frac = h.time - bucket * time_window;
                      uint64_t key = (static_cast<uint64_t>(h.pmtid) << 32) | bucket;
                      return make_tuple(key, frac, 1);
                  });

        // 2. Sort by key : with the values (times:frac, counts:1) following along 
        sort_by_key(keys.begin(), keys.end(), make_zip_iterator(make_tuple(times.begin(), counts.begin())));
    }

    // --------------------------------------------------------------
    // PHASE 1: Count merged hits (uses prepared data)
    int count_merged()
    {
        if (keys.empty()) return 0;

        device_vector<uint64_t> dummy_keys(keys.size());
        device_vector<int>      dummy_vals(keys.size());

        auto result = reduce_by_key(
            keys.begin(), keys.end(),
            make_constant_iterator(1),
            dummy_keys.begin(),
            dummy_vals.begin()
        );

        return result.first - dummy_keys.begin();
    }

    // --------------------------------------------------------------
    // PHASE 2: Fill output (uses prepared data)
    void fill_merged(MergedHit* d_out, int merged_count)
    {
        if (merged_count == 0) return;

        device_vector<uint64_t> out_keys(merged_count);
        device_vector<float>    out_min_time(merged_count);
        device_vector<int>      out_count(merged_count);

        auto result = reduce_by_key(
            keys.begin(), keys.end(),
            make_zip_iterator(make_tuple(times.begin(), counts.begin())),
            out_keys.begin(),
            make_zip_iterator(make_tuple(out_min_time.begin(), out_count.begin())),
            equal_to<uint64_t>(),
            [] __device__ (tuple<float,int> a, tuple<float,int> b) {
                return make_tuple(min(get<0>(a), get<0>(b)), get<1>(a) + get<1>(b));
            }
        );

        device_ptr<MergedHit> out(d_out);
        auto* k_ptr = raw_pointer_cast(out_keys.data());
        auto* t_ptr = raw_pointer_cast(out_min_time.data());
        auto* c_ptr = raw_pointer_cast(out_count.data());

        for_each(counting_iterator<int>(0), counting_iterator<int>(merged_count),
                 [=] __device__ (int i) {
                     uint64_t k = k_ptr[i];
                     int pmtid = k >> 32;
                     int bucket = k & 0xFFFFFFFFu;
                     float time = bucket * time_window + t_ptr[i];
                     out[i] = {pmtid, time, c_ptr[i]};
                 });
    }

    // --------------------------------------------------------------
    // Convenience: full merge with auto-allocation
    MergedHit* merge_and_alloc(const RawHit* d_raw, int N, int* out_count = nullptr)
    {
        prepare(d_raw, N);
        int count = count_merged();
        MergedHit* d_out = nullptr;
        cudaMalloc(&d_out, count * sizeof(MergedHit));
        fill_merged(d_out, count);
        if (out_count) *out_count = count;
        return d_out;
    }
};


PMTHitMergerGPU merger(1.0f);

// --- In your frame loop ---
merger.prepare(d_raw_hits, n_hits);     // ← ONE packing + sort

int n_merged = merger.count_merged();   // ← Fast count
MergedHit* d_merged = nullptr;
cudaMalloc(&d_merged, n_merged * sizeof(MergedHit));

merger.fill_merged(d_merged, n_merged); // ← Uses cached sorted data


