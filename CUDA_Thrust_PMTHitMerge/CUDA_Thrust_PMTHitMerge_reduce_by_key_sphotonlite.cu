/**
CUDA_Thrust_PMTHitMerge_reduce_by_key_sphotonlite.cu
======================================================


**/


#include "sphotonlite.h"
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/reduce.h>
#include <thrust/iterator/zip_iterator.h>


/**
Step 1: GPU Partial Merge (Per Launch)
**/

struct SPHotonLiteMergerGPU 
{
    float time_window;  // 1.0f for 1 ns buckets

    device_vector<uint64_t> d_key;
    device_vector<float>    d_time;
    device_vector<uint32_t> d_lpos;     // optional
    device_vector<uint32_t> d_flagmask; // optional

    SPHotonLiteMergerGPU(float tw = 1.0f) : time_window(tw) {}

    void prepare(const sphotonlite* d_raw, int N) 
    {
        if (N == 0) return;
        d_key.resize(N);
        d_time.resize(N);
        d_lpos.resize(N);
        d_flagmask.resize(N);

        // unzip raw structs from full sphotonlite hit array into (d_key,d_time,d_lpos,d_flagmask) arrays
        // HMM: could combine this with flagmask selection 
        transform(
            make_counting_iterator(0), make_counting_iterator(N),
            make_zip_iterator(make_tuple(d_key.begin(), d_times.begin(), d_lpos.begin(), d_flagmask.begin())),
            [=] __device__ (int i) -> tuple<uint64_t, float, uint32_t, uint32_t> {
                const sphotonlite& lite = d_raw[i];
                int bucket = static_cast<int>(lite.time / time_window);
                unsigned identity = lite.identity();

                uint64_t key = (static_cast<uint64_t>(identity & 0xFFFF) << 48) | bucket; // 16+48 = 64
                return make_tuple(key, l.time, l.lposcost_lposfphi, l.flagmask);
            });


        // sort_by_key moving same (identity,bucket) hits together
        sort_by_key(d_keys.begin(), d_keys.end(),
                    make_zip_iterator(make_tuple(d_time.begin(), d_lpos.begin(), d_flagmask.begin())));
    }

    sphotonlite* merge_partial(int* out_count = nullptr) 
    {
        int N = d_keys.size();
        if (N == 0) { if (out_count) *out_count = 0; return nullptr; }

        device_vector<uint64_t> out_key(N);
        device_vector<float>    out_min_time(N);
        device_vector<uint32_t> out_lpos(N);
        device_vector<uint32_t> out_flagmask(N);
        device_vector<int>      out_count_vec(N);

        //  reduce_by_key combining same (identity,bucket) keys together by adding hitcount
        auto result = reduce_by_key(
            d_key.begin(), d_key.end(),
            make_zip_iterator(make_tuple(d_time.begin(), d_lpos.begin(), d_flagmask.begin(), make_constant_iterator(1))),
            out_key.begin(),
            make_zip_iterator(make_tuple(out_min_time.begin(), out_lpos.begin(), out_flagmask.begin(), out_count_vec.begin())),
            thrust::equal_to<uint64_t>(),
            [] __device__ (const tuple<float,uint32_t,uint32_t,int>& a,
                           const tuple<float,uint32_t,uint32_t,int>& b) -> tuple<float,uint32_t,uint32_t,int> {
                return make_tuple(
                    fminf(get<0>(a), get<0>(b)),  // earlier time
                    get<1>(a),                    // just pick first lpos (HMM: merging makes no sense for lpos)
                    get<2>(a) | get<2>(b),        // HMM: OR-ing flagmask, maybe just pick first like lpos
                    get<3>(a) + get<3>(b)         // sum counts
                );
            });


        int merged_count = result.first - out_keys.begin();
        if (out_count) *out_count = merged_count;

        // allocate for the merged hits
        sphotonlite* d_out = nullptr;
        cudaMalloc(&d_out, merged_count * sizeof(sphotonlite));

        // zip fields together into (sphotonlite)d_out
        transform(
            make_counting_iterator(0), make_counting_iterator(merged_count),
            d_out,
            [=] __device__ (int i) -> sphotonlite {
                uint64_t k = out_keys[i];
                unsigned identity = (k >> 48) & 0xFFFF ;     // hi-16 bits 
                unsigned bucket   = k & 0xFFFFFFFFFFFFull;   // lo-48 bits
                sphotonlite s;
                s.init(identity, bucket * time_window + out_min_time[i], out_flagmask[i]);
                s.set_hitcount_identity(out_count_vec[i], identity);
                s.lposcost_lposfphi = out_lpos[i] ;
                return s;
            });

        return d_out;
    }
};




/**
Step 2: Stream Partials to Disk (Host)
**/



#include <fstream>
#include <vector>

void save_partial(const sphotonlite* d_partial, int count, const std::string& path) {
    std::vector<sphotonlite> h_partial(count);
    cudaMemcpy(h_partial.data(), d_partial, count * sizeof(sphotonlite), cudaMemcpyDeviceToHost);
    std::ofstream f(path, std::ios::binary);
    f.write((char*)h_partial.data(), count * sizeof(sphotonlite));
    cudaFree(d_partial);
}

// After each launch:
int partial_count;
sphotonlite* d_partial = merger.merge_partial(&partial_count);
save_partial(d_partial, partial_count, "partials/partial_" + std::to_string(launch_id) + ".bin");






/**
Step 3: Incremental GPU Merge (Accumulator)
**/



struct SPHotonLiteIncrementalMerger 
{
    static sphotonlite* merge_incremental(
        const std::vector<std::string>& partial_paths,
        int* final_count,
        float time_window = 1.0f) {

        device_vector<uint64_t> accum_keys;
        device_vector<sphotonlite> accum_hits;

        for (const auto& path : partial_paths) 
        {
            // Load partial
            std::ifstream f(path, std::ios::binary | std::ios::ate);
            size_t size = f.tellg() / sizeof(sphotonlite);
            f.seekg(0);
            std::vector<sphotonlite> h_partial(size);
            f.read((char*)h_partial.data(), size * sizeof(sphotonlite));

            // Upload partial
            device_vector<sphotonlite> d_partial = h_partial;

            // Fill d_keys from d_partial info
            device_vector<uint64_t> d_keys(size);
            transform(d_partial.begin(), d_partial.end(), d_keys.begin(),
                      [=] __device__ (const sphotonlite& s) -> uint64_t {
                          unsigned identity = s.identity();
                          unsigned bucket = static_cast<unsigned>(s.time / time_window);
                          return (static_cast<uint64_t>(identity) << 48) | bucket;
                      });

            // sort d_keys (HMM, expected to already be sorted?)
            sort_by_key(d_keys.begin(), d_keys.end(), d_partial.begin());

            if (accum_keys.empty()) {
                accum_keys = std::move(d_keys);
                accum_hits = std::move(d_partial);
            } else {
                // Merge and reduce
                auto result = merge_and_reduce(accum_keys, accum_hits, d_keys, d_partial);
                accum_keys = std::move(result.first);
                accum_hits.resize(accum_keys.size());
                copy(result.second.begin(), result.second.begin() + accum_keys.size(), accum_hits.begin());
            }
        }

        *final_count = accum_hits.size();
        sphotonlite* d_final = nullptr;
        cudaMalloc(&d_final, accum_hits.size() * sizeof(sphotonlite));
        cudaMemcpy(d_final, raw_pointer_cast(accum_hits.data()), accum_hits.size() * sizeof(sphotonlite), cudaMemcpyDeviceToDevice);
        return d_final;
    }

private:
    static thrust::pair<device_vector<uint64_t>, device_vector<sphotonlite>> merge_and_reduce(
        const device_vector<uint64_t>& keys_a,       device_vector<sphotonlite>& vals_a,
        const device_vector<uint64_t>& keys_b, const device_vector<sphotonlite>& vals_b) {

        size_t total = keys_a.size() + keys_b.size();  // worst case: no reduction
        device_vector<uint64_t>    merged_keys(total);
        device_vector<sphotonlite> merged_vals(total);

        // 
        auto end = thrust::merge_by_key(
            keys_a.begin(), keys_a.end(), 
            keys_b.begin(), keys_b.end(),
            vals_a.begin(), 
            vals_b.begin(),
            merged_keys.begin(), 
            merged_vals.begin());

        device_vector<uint64_t> reduced_keys(total);
        device_vector<sphotonlite> reduced_vals(total);

        auto reduce_end = thrust::reduce_by_key(
            merged_keys.begin(), end.first,
            merged_vals.begin(),
            reduced_keys.begin(),
            reduced_vals.begin(),
            thrust::equal_to<uint64_t>(),
            [] __device__ (const sphotonlite& a, const sphotonlite& b) -> sphotonlite {
                sphotonlite s = a;
                s.set_hitcount_identity(a.hitcount() + b.hitcount(), a.identity());
                s.time = fminf(a.time, b.time);
                s.flagmask |= b.flagmask;
                return s;
            });

        int reduced_size = reduce_end.first - reduced_keys.begin();
        device_vector<uint64_t> final_keys(reduced_size);
        device_vector<sphotonlite> final_vals(reduced_size);
        copy(reduced_keys.begin(), reduced_keys.begin() + reduced_size, final_keys.begin());
        copy(reduced_vals.begin(), reduced_vals.begin() + reduced_size, final_vals.begin());
        return {std::move(final_keys), std::move(final_vals)};
    }
};





/**
Final Usage
**/


std::vector<std::string> partials;
for (int i = 0; i < 32; ++i) partials.push_back("partials/partial_" + std::to_string(i) + ".bin");

int final_count;
sphotonlite* d_final_hits = SPHotonLiteIncrementalMerger::merge_incremental(partials, &final_count);

// Copy to CPU for JUNOSW
std::vector<sphotonlite> h_final(final_count);
cudaMemcpy(h_final.data(), d_final_hits, final_count * sizeof(sphotonlite), cudaMemcpyDeviceToHost);
cudaFree(d_final_hits);





