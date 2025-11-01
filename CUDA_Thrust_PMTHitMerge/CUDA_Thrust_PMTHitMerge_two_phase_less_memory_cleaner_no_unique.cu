/**
https://github.com/nvidia/cccl

**/


struct PMTHitMergerGPU {
    device_vector<uint64_t> packed;
    device_vector<int>      flags;
    device_vector<int>      run_start;
    float time_window;

    PMTHitMergerGPU(float tw) : time_window(tw) {}

    // PHASE 1: Count without modifying layout
    int count_merged(const RawHit* d_raw, int N)
    {
        packed.resize(N);
        flags.resize(1, 1);  // start with 1

        transform(... pack ...);
        sort(packed.begin(), packed.end(), full_key_comp);

        // Count transitions in parallel
        auto* data = raw_pointer_cast(packed.data());
        thrust::for_each(counting_iterator<int>(1), counting_iterator<int>(N),
            [=] __device__ (int i) {
                uint64_t k1 = data[i-1] & 0xFFFFFFFF0000ULL;
                uint64_t k2 = data[i]   & 0xFFFFFFFF0000ULL;
                if (k1 != k2) atomicAdd(&flags[0], 1);
            });

        int count;
        cudaMemcpy(&count, raw_pointer_cast(flags.data()), sizeof(int), cudaMemcpyDeviceToHost);
        return count;
    }

    // PHASE 2: Reuse sorted packed buffer
    void fill_merged(MergedHit* d_out, int merged_count)
    {
        run_start.resize(merged_count);
        flags.resize(packed.size());

        // Rebuild flags: 1 at start of each run
        auto* data = raw_pointer_cast(packed.data());
        transform(counting_iterator<int>(0), counting_iterator<int>(packed.size()),
                  flags.begin(),
                  [=] __device__ (int i) -> int {
                      if (i == 0) return 1;
                      return (data[i] & 0xFFFFFFFF0000ULL) != (data[i-1] & 0xFFFFFFFF0000ULL);
                  });

        exclusive_scan(flags.begin(), flags.end(), run_start.begin(), 0);

        // ... same reduction loop ...
    }
};



