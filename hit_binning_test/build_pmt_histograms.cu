/**

kernel where each block processes one PMT’s hits, using shared memory for the (theta, phi) 
histogram to minimize global memory writes.

**/


__global__ void build_pmt_histograms(
    const Hit* d_hits,
    const unsigned* d_offsets,
    const unsigned* d_counts,
    const float* d_transforms, unsigned num_transforms,
    unsigned* d_histograms, unsigned num_pmts,
    unsigned n_theta, unsigned n_phi,
    float radius
) {
    unsigned pmt_id = blockIdx.x;
    if (pmt_id >= num_pmts) return;

    // Shared memory for local histogram
    extern __shared__ unsigned sh_hist[];
    for (unsigned i = threadIdx.x; i < n_theta * n_phi; i += blockDim.x) {
        sh_hist[i] = 0;
    }
    __syncthreads();

    // Process hits for this PMT
    unsigned start = d_offsets[pmt_id];
    unsigned count = d_counts[pmt_id];
    for (unsigned i = threadIdx.x; i < count; i += blockDim.x) {
        unsigned hit_idx = start + i;
        const Hit& hit = d_hits[hit_idx];

        // Transform to local frame
        const float* matrix = d_transforms + hit.transform_idx * 16;
        float4 global_hom = make_float4(hit.global_pos.x, hit.global_pos.y, hit.global_pos.z, 1.0f);
        float4 local_hom;
        local_hom.x = matrix[0]*global_hom.x + matrix[1]*global_hom.y + matrix[2]*global_hom.z + matrix[3]*global_hom.w;
        // ... (compute y, z, w as before)
        float3 local_pos = make_float3(local_hom.x / local_hom.w, local_hom.y / local_hom.w, local_hom.z / local_hom.w);

        // Spherical coords
        float norm = sqrtf(local_pos.x*local_pos.x + local_pos.y*local_pos.y + local_pos.z*local_pos.z);
        if (norm < 1e-6f) continue;
        local_pos = local_pos / norm;

        float theta = acosf(local_pos.z);
        float phi = atan2f(local_pos.y, local_pos.x);

        // Bin
        int theta_bin = (int)floorf(theta * (n_theta / M_PIf));
        int phi_bin = (int)floorf((phi + M_PIf) * (n_phi / (2.0f * M_PIf)));
        theta_bin = max(0, min(theta_bin, (int)n_theta - 1));
        phi_bin = max(0, min(phi_bin, (int)n_phi - 1));

        // Increment shared histogram
        atomicAdd(&sh_hist[theta_bin * n_phi + phi_bin], 1u);
    }
    __syncthreads();

    // Write to global histogram
    for (unsigned i = threadIdx.x; i < n_theta * n_phi; i += blockDim.x) {
        if (sh_hist[i] > 0) {
            atomicAdd(&d_histograms[pmt_id * (n_theta * n_phi) + i], sh_hist[i]);
        }
    }
}

