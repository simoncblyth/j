
void compute_pmt_histograms(Hit* d_hits, unsigned num_hits, float* d_transforms, unsigned num_transforms) {
    const unsigned num_pmts = 30000, n_theta = 50, n_phi = 100;
    float radius = 0.254f;  // Adjust per PMT type if needed

    // Sort hits
    thrust::device_vector<unsigned> d_pmt_ids(num_hits);
    thrust::device_vector<unsigned> d_indices(num_hits);
    // ... (fill and sort as above)

    // Compute segments
    thrust::device_vector<unsigned> d_offsets(num_pmts + 1);
    thrust::device_vector<unsigned> d_counts(num_pmts);
    compute_pmt_segments(d_pmt_ids, num_hits, num_pmts, d_offsets, d_counts);

    // Allocate histogram
    unsigned* d_histograms;
    CUDA_CHECK(cudaMalloc(&d_histograms, num_pmts * n_theta * n_phi * sizeof(unsigned)));
    CUDA_CHECK(cudaMemset(d_histograms, 0, num_pmts * n_theta * n_phi * sizeof(unsigned)));

    // Launch kernel
    unsigned block_size = 256;
    unsigned shared_mem = n_theta * n_phi * sizeof(unsigned);
    build_pmt_histograms<<<num_pmts, block_size, shared_mem>>>(
        d_hits, d_offsets.data().get(), d_counts.data().get(),
        d_transforms, num_transforms, d_histograms, num_pmts, n_theta, n_phi, radius
    );
    CUDA_CHECK(cudaDeviceSynchronize());
}


