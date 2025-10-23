
#include <cuda_runtime.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sort.h>
#include <thrust/unique.h>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <array>

#include "sdigest.h"
#include "NP.hh"

using Digest = std::array<unsigned char, 16>;


#define CUDA_CHECK(call) \
    { cudaError_t err = call; if (err != cudaSuccess) { \
        std::cerr << "CUDA error: " << cudaGetErrorString(err) << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(1); } }

// Log VRAM usage
void log_vram(const char* label) {
    size_t free, total;
    CUDA_CHECK(cudaMemGetInfo(&free, &total));
    std::cout << "[ " << label << " VRAM: " << free / (1024.0 * 1024.0) << " MB free of "
              << total / (1024.0 * 1024.0) << " MB\n";
}



std::string DescDigest( unsigned char* digest16 )
{
    char buf[32+1] ;
    for (int n = 0; n < 16; ++n) std::snprintf( &buf[2*n], 32+1, "%02x", (unsigned int)digest16[n]) ;
    buf[32] = '\0' ;
    return std::string(buf, buf + 32);
}

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

using DigestSet = std::unordered_set<Digest, DigestHash>;



struct DigestIndex
{
    unsigned char digest[16];
    uint64_t index;

    __host__ __device__ DigestIndex() : index(0)
    {
        for (int j = 0; j < 16; ++j) digest[j] = 0 ;
    }
    __host__ __device__ DigestIndex(const Digest& d, uint64_t i) : index(i)
    {
        for (int j = 0; j < 16; ++j) digest[j] = d[j];
    }
};

// Comparator for Thrust sorting by digest
struct DigestIndexCompare
{
    __host__ __device__
    bool operator()(const DigestIndex& a, const DigestIndex& b) const
    {
        // Compare digests byte-by-byte
        for (int i = 0; i < 16; ++i) {
            if (a.digest[i] < b.digest[i]) return true;
            if (a.digest[i] > b.digest[i]) return false;
        }
        return false;
    }
};




extern "C" {
  #include "md5.cuh"
}

__global__ void kernel_md5_hash(BYTE* indata, WORD inlen, BYTE* outdata, WORD n_batch);


int main()
{
    const char* path = "$HITFOLD/hit.npy";
    const char* sli = "$HITSLICE" ;
    std::cout << U::Log() << "[ load hit \n" ;
    NP* hit = NP::LoadSlice(path, sli);
    std::cout << U::Log() << "] load hit " << ( hit ? hit->sstr() : "-" ) << "\n"  ;
    if (!hit) {
        std::cerr << "Failed to load " << path << std::endl;
        return 1;
    }

    size_t M = 1000000 ;
    size_t num_item = hit->shape[0];
    size_t item_size = 64;  // 4x4x4 bytes (4x4xfloat32)
    size_t digest_size = 16 ;
    size_t batch_size = U::GetEnvSize("BATCH_SIZE", 100'000'000 );
    size_t sort_chunk_size = U::GetEnvSize("SORT_CHUNK_SIZE", 100'000'000 );  // ~2.4 GB per chunk
    size_t num_batch = (num_item + batch_size - 1) / batch_size;

    std::cout
          << U::Log()
          << " num_item " << num_item << "\n"
          << " num_item/M " << num_item/M << "\n"
          << " item_size " << item_size << "\n"
          << " digest_size " << digest_size << "\n"
          << " batch_size " << batch_size << "\n"
          << " batch_size/M " << batch_size/M << "\n"
          << " sort_chunk_size " << sort_chunk_size << "\n"
          << " sort_chunk_size/M " << sort_chunk_size/M << "\n"
          << " num_batch " << num_batch << "\n"
          ;



    std::cout << U::Log() << "[ CPU md5 digest check\n" ;

    for(size_t i=0 ; i < 10 ; i++)
    {
        Digest d = sdigest::BufRaw(hit->bytes() + item_size*i, item_size );
        std::cout << std::setw(10) << i << " : " << DescDigest(d.data()) << "\n" ;
    }
    for(size_t i=num_item - 10 ; i < num_item ; i++)
    {
        Digest d = sdigest::BufRaw(hit->bytes() + item_size*i, item_size );
        std::cout << std::setw(10) << i << " : " << DescDigest(d.data()) << "\n" ;
    }
    std::cout << U::Log() << "] CPU md5 digest check\n" ;

    log_vram("before_alloc");

    thrust::device_vector<DigestIndex> all_pairs(num_item);
    CUDA_CHECK(cudaDeviceSynchronize());

    log_vram("after_alloc");


    // Allocate GPU buffers
    BYTE* d_batch_input;
    BYTE* d_batch_digest;
    cudaMalloc(&d_batch_input  , batch_size * item_size);
    cudaMalloc(&d_batch_digest , batch_size * digest_size);
    log_vram("after_buffers");


    for (size_t b = 0; b < num_batch ; b++)
    {
        size_t start = b * batch_size;
        size_t end = std::min(start + batch_size, num_item);
        size_t batch_item = end - start;
        size_t threads_per_block = 256;
        size_t blocks = (batch_item + threads_per_block - 1) / threads_per_block;

        std::cout
            << U::Log()
            << "[ batch.md5 "
            << " b " << std::setw(5) << b
            << " start " << std::setw(12) << start
            << " end " << std::setw(12) << end
            << " batch_item " << std::setw(12) << batch_item
            << " threads_per_block " << std::setw(12) << threads_per_block
            << " blocks " << std::setw(12) << blocks
            << "\n"
            ;


        // Copy input batch to GPU
        CUDA_CHECK(cudaMemcpy(d_batch_input, hit->bytes() + start * item_size, batch_item * item_size, cudaMemcpyHostToDevice));

        // Compute MD5 digests
        kernel_md5_hash<<<blocks, threads_per_block>>>(d_batch_input, item_size, d_batch_digest, batch_item );
        CUDA_CHECK(cudaDeviceSynchronize());

        std::cout << U::Log() << "] batch.md5 " << b << "\n" ;

        // Copy batch digests to full vector (treat d_batch_digests as Digest*)
        std::cout << U::Log() << "[ batch.copy_to_all " << b << "\n" ;


        thrust::host_vector<Digest> h_batch_digest(batch_item);

        CUDA_CHECK(cudaMemcpy(h_batch_digest.data(), d_batch_digest, batch_item * digest_size, cudaMemcpyDeviceToHost));

        thrust::host_vector<DigestIndex> h_batch_pairs(batch_item);
        for (size_t i = 0; i < batch_item ; i++) h_batch_pairs[i] = DigestIndex(h_batch_digest[i], start + i);

        thrust::copy(h_batch_pairs.begin(), h_batch_pairs.end(), all_pairs.begin() + start);
        CUDA_CHECK(cudaDeviceSynchronize());
        log_vram("after_batch_copy");

        std::cout << U::Log() << "] batch.copy_to_all " << b << "\n" ;
    }

    // Cleanup batch buffers
    std::cout << U::Log() << "[ freebuf \n" ;
    cudaFree(d_batch_input);
    cudaFree(d_batch_digest);
    std::cout << U::Log() << "] freebuf \n" ;
    log_vram("after_freebuf");

    std::cout << U::Log() << "[ delete hit \n" ;
    delete hit;
    std::cout << U::Log() << "] delete hit \n" ;



    std::cout << U::Log() << "[ presort.dump\n" ;
    thrust::host_vector<DigestIndex> h_test_pairs(all_pairs.begin(), all_pairs.begin() + 10);
    for (size_t i = 0; i < 10; i++) {
        std::cout << "presort i " << std::setw(10) << i << " digest: ";
        for (unsigned char c : h_test_pairs[i].digest) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << std::dec << std::setfill(' ')  ;
        std::cout <<  " dd " << DescDigest( h_test_pairs[i].digest ) ;
        std::cout << " index: " << h_test_pairs[i].index << std::endl;
    }

    h_test_pairs = thrust::host_vector<DigestIndex>(all_pairs.end() - 10, all_pairs.end());

    for (size_t i = 0 ; i < 10; i++) {
        size_t j = num_item - 10 + i ;
        std::cout << "presort i " << std::setw(10) << j << " digest: ";
        for (unsigned char c : h_test_pairs[i].digest) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << std::dec << std::setfill(' ') ;
        std::cout <<  " dd " << DescDigest( h_test_pairs[i].digest ) ;
        std::cout << " index: " << h_test_pairs[i].index << std::endl;
    }
    std::cout << U::Log() << "] presort.dump\n" ;




    // Chunked GPU sort
    std::cout << U::Log() << "[ sort.chunks " << std::endl;
    size_t num_chunks = (num_item + sort_chunk_size - 1) / sort_chunk_size;
    for (size_t c = 0; c < num_chunks; c++) {
        size_t start = c * sort_chunk_size;
        size_t end = std::min(start + sort_chunk_size, num_item);
        std::cout << "[ sort.chunk " << c << " start " << start << " items " << (end - start) << std::endl;
        try {
            thrust::sort(all_pairs.begin() + start, all_pairs.begin() + end, DigestIndexCompare());
            CUDA_CHECK(cudaDeviceSynchronize());
            log_vram("after_sort_chunk");
        } catch (const thrust::system_error& e) {
            std::cerr << "Thrust sort chunk " << c << " failed: " << e.what() << std::endl;
            // Fallback to host sort
            std::cout << "[ fallback.host_sort " << std::endl;
            thrust::host_vector<DigestIndex> h_pairs = all_pairs;
            std::sort(h_pairs.begin(), h_pairs.end(), DigestIndexCompare());
            all_pairs = h_pairs;  // Copy back to GPU for consistency
            break;
        }
    }
    std::cout << U::Log() << "] sort.chunks " << std::endl;


    // Download to host for scan (16 GB transfer is fast via PCIe; ~10-20 seconds)
    std::cout << U::Log() << "[ copy_to_host \n" ;
    thrust::host_vector<DigestIndex> h_pairs = all_pairs;
    std::cout << U::Log() << "] copy_to_host \n" ;
    log_vram("after_transfer");


    std::cout << U::Log() << "[ dump first and last few digest,index pairs \n" ;


    for(size_t i=0 ; i < 10 ; i++) std::cout
        << " i " << std::setw(10) << i
        << " h_pairs[i].digest : " << DescDigest(h_pairs[i].digest)
        << " h_pairs[i].index : " << std::setw(10) << h_pairs[i].index
        << "\n"
        ;

    for(size_t i=num_item - 10 ; i < num_item ; i++) std::cout
        << " i " << std::setw(10) << i
        << " h_pairs[i].digest : " << DescDigest(h_pairs[i].digest)
        << " h_pairs[i].index : " << std::setw(10) << h_pairs[i].index
        << "\n"
        ;

    std::cout << U::Log() << "] dump first and last few digests \n" ;

    std::cout << U::Log() << "[ scan for dupe \n" ;

    // Scan to collect duplicate indices
    using IndexList = std::vector<uint64_t>;
    std::unordered_map<Digest, IndexList, DigestHash> duplicate_indices;
    size_t i = 0;
    while (i < num_item)
    {
        size_t j = i + 1;
        while (j < num_item && memcmp(h_pairs[j].digest, h_pairs[i].digest, 16) == 0) ++j;
        if (j - i > 1)
        {  // Duplicate found
            IndexList indices;
            for (size_t k = i; k < j; k++) indices.push_back(h_pairs[k].index);

            Digest d;
            memcpy(d.data(), h_pairs[i].digest, 16);
            duplicate_indices[d] = std::move(indices);
        }
        i = j;
    }
    std::cout << U::Log() << "] scan for dupe \n" ;


    // Output results
    std::cout << U::Log() << "Found " << duplicate_indices.size() << " unique duplicated digests.\n";
    uint64_t count = 0 ;

    for (const auto& [digest, indices] : duplicate_indices)
    {
        if( count < 100 )
        {
            std::cout << "Duplicate: "  << std::setw(10) << count << " " ;
            for (unsigned char c : digest) std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << std::dec << std::setfill(' ') ;
            std::cout << " at indices: ";
            for (uint64_t idx : indices) std::cout << std::setw(11) << idx << " ";
            std::cout << "\n";
        }
        count += 1 ;
    }

    return 0;
}


