
#include <cuda_runtime.h>
#include <cmath>  // For acosf, atan2f, etc.
#include <cstdio> // For error checking

#define CUDA_CHECK(call) { cudaError_t err = call; if (err != cudaSuccess) { printf("CUDA error: %s\n", cudaGetErrorString(err)); } }

struct Hit {
    float3 global_pos;     // Global x,y,z
    unsigned pmt_id;       // 0 to num_pmts-1
    unsigned transform_idx; // Index into transforms array
};

__global__ void build_pmt_histograms(
    const Hit* d_hits, unsigned num_hits,
    const float* d_transforms, unsigned num_transforms,  // Flattened 4x4 matrices (16 floats each)
    unsigned* d_histograms, unsigned num_pmts,
    unsigned n_theta, unsigned n_phi,
    float radius  // Assumed PMT radius; make per-PMT if varies
) {
    unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= num_hits) return;

    const Hit& hit = d_hits[idx];
    if (hit.pmt_id >= num_pmts) return;  // Invalid PMT

    // Fetch 4x4 transform (assume row-major)
    const float* matrix = d_transforms + hit.transform_idx * 16;

    // Transform global_pos to local_pos (homogeneous: pos.w=1)
    float4 global_hom = make_float4(hit.global_pos.x, hit.global_pos.y, hit.global_pos.z, 1.0f);
    float4 local_hom;
    local_hom.x = matrix[0]*global_hom.x + matrix[1]*global_hom.y + matrix[2]*global_hom.z + matrix[3]*global_hom.w;
    local_hom.y = matrix[4]*global_hom.x + matrix[5]*global_hom.y + matrix[6]*global_hom.z + matrix[7]*global_hom.w;
    local_hom.z = matrix[8]*global_hom.x + matrix[9]*global_hom.y + matrix[10]*global_hom.z + matrix[11]*global_hom.w;
    local_hom.w = matrix[12]*global_hom.x + matrix[13]*global_hom.y + matrix[14]*global_hom.z + matrix[15]*global_hom.w;

    float3 local_pos = make_float3(local_hom.x / local_hom.w, local_hom.y / local_hom.w, local_hom.z / local_hom.w);

    // Normalize (assuming spherical; skip if already unit)
    float norm = sqrtf(local_pos.x*local_pos.x + local_pos.y*local_pos.y + local_pos.z*local_pos.z);
    if (norm < 1e-6f) return;  // Invalid
    local_pos = local_pos / norm;  // Unit vector

    // Compute theta [0, pi], phi [-pi, pi]
    float theta = acosf(local_pos.z);
    float phi = atan2f(local_pos.y, local_pos.x);

    // Bin (clamp to avoid out-of-bounds)
    int theta_bin = (int)floorf(theta * (n_theta / M_PIf));
    int phi_bin = (int)floorf((phi + M_PIf) * (n_phi / (2.0f * M_PIf)));
    theta_bin = max(0, min(theta_bin, (int)n_theta - 1));
    phi_bin = max(0, min(phi_bin, (int)n_phi - 1));

    // Atomic increment
    unsigned offset = hit.pmt_id * (n_theta * n_phi) + theta_bin * n_phi + phi_bin;
    atomicAdd(&d_histograms[offset], 1u);
}

// Host example (adapt to Opticks)
void compute_histograms(Hit* h_hits, unsigned num_hits, float* h_transforms, unsigned num_transforms) {
    const unsigned num_pmts = 30000;
    const unsigned n_theta = 50;
    const unsigned n_phi = 100;
    const float radius = 0.254f;  // Example 20" PMT radius in meters; adjust

    Hit* d_hits; float* d_transforms; unsigned* d_histograms;
    size_t hist_size = num_pmts * n_theta * n_phi * sizeof(unsigned);

    CUDA_CHECK(cudaMalloc(&d_hits, num_hits * sizeof(Hit)));
    CUDA_CHECK(cudaMalloc(&d_transforms, num_transforms * 16 * sizeof(float)));
    CUDA_CHECK(cudaMalloc(&d_histograms, hist_size));

    CUDA_CHECK(cudaMemcpy(d_hits, h_hits, num_hits * sizeof(Hit), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemcpy(d_transforms, h_transforms, num_transforms * 16 * sizeof(float), cudaMemcpyHostToDevice));
    CUDA_CHECK(cudaMemset(d_histograms, 0, hist_size));

    unsigned block_size = 256;
    unsigned grid_size = (num_hits + block_size - 1) / block_size;
    build_pmt_histograms<<<grid_size, block_size>>>(
        d_hits, num_hits, d_transforms, num_transforms,
        d_histograms, num_pmts, n_theta, n_phi, radius
    );
    CUDA_CHECK(cudaDeviceSynchronize());

    // Copy back if needed
    unsigned* h_histograms = new unsigned[num_pmts * n_theta * n_phi];
    CUDA_CHECK(cudaMemcpy(h_histograms, d_histograms, hist_size, cudaMemcpyDeviceToHost));

    // Free memory...
}


