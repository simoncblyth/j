
#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/unique.h>
#include <vector>
#include <unordered_set>
#include <iostream>
#include "NP.hh"
#include "sdigest.h"

// Reuse your Digest and DigestHash
using Digest = std::array<unsigned char, 16>;

struct DigestHash
{
    std::size_t operator()(const std::array<unsigned char, 16>& digest) const noexcept
    {
        std::size_t seed = 0;
        // Treat the 16 bytes as four 32-bit chunks for better distribution
        for (size_t i = 0; i < 16; i += 4)
        {
            // Combine four bytes into a 32-bit integer (little-endian)
            uint32_t chunk = (static_cast<uint32_t>(digest[i]) << 24) |
                             (static_cast<uint32_t>(digest[i + 1]) << 16) |
                             (static_cast<uint32_t>(digest[i + 2]) << 8) |
                             static_cast<uint32_t>(digest[i + 3]);
            // Combine into seed using a simple but effective mixing function
            seed ^= std::hash<uint32_t>{}(chunk) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};





extern "C" { 
  #include "md5.cuh"
}


using DigestSet = std::unordered_set<Digest, DigestHash>;

//__global__ void md5_kernel(const float* input, uint8_t* output, size_t num_items) {

int main() {
    // Load hit.npy
    const char* path = "$HITFOLD/hit.npy";
    NP* hit = NP::Load(path);
    if (!hit) {
        std::cerr << "Failed to load " << path << std::endl;
        return 1;
    }

    size_t num_items = hit->shape[0];  // 997,737,665
    size_t item_size = 64;  // 4x4x4 bytes (float32)
    size_t batch_size = 300'000'000;  // ~19.2 GB input, ~4.8 GB digests
    size_t num_batches = (num_items + batch_size - 1) / batch_size;  // ~4

    DigestSet global_duplicates;

    // Allocate GPU buffers
    float* d_input;
    uint8_t* d_digests;
    cudaMalloc(&d_input, batch_size * item_size);
    cudaMalloc(&d_digests, batch_size * 16);

    for (size_t b = 0; b < num_batches; b++) {
        size_t start = b * batch_size;
        size_t end = std::min(start + batch_size, num_items);
        size_t batch_items = end - start;

        // Copy input batch to GPU
        cudaMemcpy(d_input, hit->data() + start * item_size,
                   batch_items * item_size, cudaMemcpyHostToDevice);

        // Compute MD5 digests
        size_t threads_per_block = 256;
        size_t blocks = (batch_items + threads_per_block - 1) / threads_per_block;
        md5_kernel<<<blocks, threads_per_block>>>(d_input, d_digests, batch_items);
        cudaDeviceSynchronize();

        // Sort digests
        thrust::device_ptr<uint8_t> d_digests_ptr(d_digests);
        thrust::device_vector<Digest> d_digests_vec(batch_items);
        cudaMemcpy(thrust::raw_pointer_cast(d_digests_vec.data()), d_digests,
                   batch_items * 16, cudaMemcpyDeviceToDevice);
        thrust::sort(d_digests_vec.begin(), d_digests_vec.end());

        // Detect duplicates (GPU scan)
        thrust::host_vector<Digest> h_digests = d_digests_vec;
        DigestSet batch_duplicates;
        size_t i = 0;
        while (i < batch_items) {
            size_t j = i + 1;
            while (j < batch_items && h_digests[j] == h_digests[i]) ++j;
            if (j - i > 1) {
                batch_duplicates.insert(h_digests[i]);
            }
            i = j;
        }

        // Merge batch duplicates into global
        for (const auto& d : batch_duplicates) {
            global_duplicates.insert(d);
        }
    }

    // Cleanup
    cudaFree(d_input);
    cudaFree(d_digests);
    delete hit;

    std::cout << "Found " << global_duplicates.size() << " unique duplicated 4x4 hits."
              << std::endl;
    return 0;
}


