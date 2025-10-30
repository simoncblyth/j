

// Phase 1: Count merged hits (no output allocation)
int count_merged_hits_gpu(const RawHit* d_raw, int N, float time_window);

// Phase 2: Fill pre-allocated output
void fill_merged_hits_gpu(const RawHit* d_raw, int N, float time_window, MergedHit* d_merged, int merged_count);



int count_merged_hits_gpu(const RawHit* d_raw, int N, float time_window)
{
    using namespace thrust;

    device_ptr<const RawHit> raw_ptr(const_cast<RawHit*>(d_raw));
    device_vector<uint64_t> keys(N);

    // 1. Compute keys: (pmtid << 32) | time_bucket
    transform(raw_ptr, raw_ptr + N, keys.begin(),hit_key_functor(time_window));

    // 2. Sort keys
    sort(keys.begin(), keys.end());

    // 3. Count unique keys → number of merged hits
    auto last = unique(keys.begin(), keys.end());
    int num_merged = last - keys.begin();

    return num_merged;
}




/**
fill_merged_hits_gpu
-----------------------

Phase 2 – Fill Pre-Allocated Buffer

**/
void fill_merged_hits_gpu( const RawHit* d_raw, int N, float time_window, MergedHit* d_merged_out, int merged_capacity)
{
    using namespace thrust;

    device_ptr<const RawHit> raw_ptr(const_cast<RawHit*>(d_raw));
    device_ptr<MergedHit> out_ptr(d_merged_out);

    device_vector<uint64_t> keys(N);
    device_vector<float>    times(N);

    // Fill keys
    transform(raw_ptr, raw_ptr + N, keys.begin(), hit_key_functor(time_window));
    transform(raw_ptr, raw_ptr + N, times.begin(), first_time_functor());

    // Sort by key, carry times
    sort_by_key(keys.begin(), keys.end(), times.begin());

    // Reduce: min(time) + count per key
    device_vector<uint64_t> out_keys(merged_capacity);
    device_vector<float>    out_min_time(merged_capacity);
    device_vector<int>      out_count(merged_capacity);

    auto result = reduce_by_key(
        keys.begin(), keys.end(),
        make_zip_iterator(make_tuple(times.begin(), make_constant_iterator(1))),
        out_keys.begin(),
        make_zip_iterator(make_tuple(out_min_time.begin(), out_count.begin())),
        equal_to<uint64_t>(),
        // Custom reducer: min + sum
        [] __device__ (tuple<float,int> a, tuple<float,int> b) {
            return make_tuple(min(get<0>(a), get<0>(b)), get<1>(a) + get<1>(b));
        }
    );

    int actual_count = result.first - out_keys.begin();

    // Write final MergedHit
    for_each(counting_iterator<int>(0), counting_iterator<int>(actual_count),
             [=] __device__ (int i) {
                 uint64_t k = out_keys[i];
                 int pmtid = k >> 32;
                 out_ptr[i] = {pmtid, out_min_time[i], out_count[i]};
             });
}




// After photon selection
thrust::device_vector<RawHit> d_hits = ...;

// PHASE 1: Count
int merged_count = count_merged_hits_gpu(thrust::raw_pointer_cast(d_hits.data()),d_hits.size(),time_window);

// PHASE 2: Allocate exactly
MergedHit* d_merged;
cudaMalloc(&d_merged, merged_count * sizeof(MergedHit));

fill_merged_hits_gpu(
    thrust::raw_pointer_cast(d_hits.data()),
    d_hits.size(),
    time_window,
    d_merged,
    merged_count);

// Copy back
std::vector<MergedHit> h_merged(merged_count);
cudaMemcpy(h_merged.data(), d_merged, merged_count * sizeof(MergedHit), cudaMemcpyDeviceToHost);





















