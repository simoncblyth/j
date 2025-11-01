/**
CUDA_Thrust_PMTHitMerge_reduce_by_key_bucket_only.cu
======================================================

**/

#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/reduce.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/counting_iterator.h>

using namespace thrust;

struct RawHit { int pmtid; float time; };
struct MergedHit { int pmtid; float time; int count; };

struct PMTHitMergerGPU 
{
    float time_window;
    device_vector<uint64_t> keys;
    device_vector<int>      counts;

    PMTHitMergerGPU(float tw) : time_window(tw) {}

    // --------------------------------------------------------------
    void prepare(const RawHit* d_raw, int N)
    {
        if (N == 0) return;

        keys.resize(N);
        counts.resize(N, 1);

        // Pack key = (pmtid << 32) | bucket
        transform(counting_iterator<int>(0), counting_iterator<int>(N),
                  keys.begin(),
                  [=] __device__ (int i) -> uint64_t {
                      const RawHit& h = d_raw[i];
                      int bucket = static_cast<int>(h.time / time_window);
                      return (static_cast<uint64_t>(h.pmtid) << 32) | bucket;
                  });

        // Sort by key
        sort_by_key(keys.begin(), keys.end(), counts.begin());
    }

    // --------------------------------------------------------------
    int count_merged()
    {
        if (keys.empty()) return 0;
        device_vector<uint64_t> dummy(N);
        device_vector<int> dummy_val(N);
        auto result = reduce_by_key(keys.begin(), keys.end(),
                                    make_constant_iterator(1),
                                    dummy.begin(), dummy_val.begin());
        return result.first - dummy.begin();
    }

    // --------------------------------------------------------------
    void fill_merged(MergedHit* d_out, int merged_count)
    {
        if (merged_count == 0) return;

        device_vector<uint64_t> out_keys(merged_count);
        device_vector<int>      out_counts(merged_count);

        reduce_by_key(keys.begin(), keys.end(),
                      counts.begin(),
                      out_keys.begin(),
                      out_counts.begin());

        device_ptr<MergedHit> out(d_out);
        auto* k_ptr = raw_pointer_cast(out_keys.data());
        auto* c_ptr = raw_pointer_cast(out_counts.data());

        for_each(counting_iterator<int>(0), counting_iterator<int>(merged_count),
                 [=] __device__ (int i) {
                     uint64_t k = k_ptr[i];
                     int pmtid = k >> 32;
                     int bucket = k & 0xFFFFFFFFu;
                     out[i] = {pmtid, bucket * time_window, c_ptr[i]};
                 });
    }

    // --------------------------------------------------------------
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

merger.prepare(d_hits, n_hits);
int n_merged = merger.count_merged();
MergedHit* d_out = alloc_exact<MergedHit>(n_merged);
merger.fill_merged(d_out, n_merged);


