/**
just_digest.cu
================

Compare GPU and CPU implementations of MD5 digests
of large numbers of hits.

**/


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

extern "C" { 
  #include "md5.cuh"
}

__global__ void kernel_md5_hash(BYTE* indata, WORD inlen, BYTE* outdata, WORD n_batch);





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



int main() 
{
    const char* hitpath = "$HITFOLD/hit.npy";
    const char* sli = "$HITSLICE" ;
    std::cout << U::Log() << "[ load hit \n" ;
    NP* hit = NP::LoadSlice(hitpath, sli);
    std::cout << U::Log() << "] load hit " << ( hit ? hit->sstr() : "-" ) << "\n"  ;
    if (!hit) {
        std::cerr << "Failed to load " << hitpath << std::endl;
        return 1;
    }


    size_t M = 1000000 ;
    size_t num_item = hit->shape[0];
    size_t item_size = 64;  // 4x4x4 bytes (4x4xfloat32)
    size_t digest_size = 16 ;
    size_t batch_size = U::GetEnvSize("BATCH_SIZE", 100'000'000 );
    size_t num_batch = (num_item + batch_size - 1) / batch_size;

    NP* hitdig_gpu = NP::Make<uint8_t>( num_item, 16 ); 
    NP* hitdig_cpu = NP::Make<uint8_t>( num_item, 16 ); 


    std::cout 
          << U::Log()
          << " num_item " << num_item << "\n"  
          << " num_item/M " << num_item/M << "\n"  
          << " item_size " << item_size << "\n"  
          << " digest_size " << digest_size << "\n"  
          << " batch_size " << batch_size << "\n"  
          << " batch_size/M " << batch_size/M << "\n"  
          << " num_batch " << num_batch << "\n"  
          << " hitdig_gpu " << ( hitdig_gpu ? hitdig_gpu->sstr() : "-" ) << "\n"
          << " hitdig_cpu " << ( hitdig_cpu ? hitdig_cpu->sstr() : "-" ) << "\n"
          ;


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
                                   
        char* h_dst =  hitdig_gpu->bytes() + start*digest_size ; 
        CUDA_CHECK(cudaMemcpy(h_dst, d_batch_digest, batch_item * digest_size, cudaMemcpyDeviceToHost));

        std::cout << U::Log() << "] batch.copy_to_all " << b << "\n" ;
    }

    // Cleanup batch buffers
    std::cout << U::Log() << "[ freebuf \n" ;
    cudaFree(d_batch_input);
    cudaFree(d_batch_digest);
    std::cout << U::Log() << "] freebuf \n" ;
    log_vram("after_freebuf");



    std::cout << U::Log() << "[ CPU digest \n" ;

    unsigned char* hitdig_cpu_bytes = (unsigned char*)hitdig_cpu->bytes() ;

    for(size_t i=0 ; i < num_item ; i++) sdigest::BufRaw_(hitdig_cpu_bytes + digest_size*i,  hit->bytes() + item_size*i, item_size );
    std::cout << U::Log() << "] CPU digest \n" ;


    std::cout << U::Log() << "[ delete hit \n" ;
    delete hit;
    std::cout << U::Log() << "] delete hit \n" ;


    std::cout << U::Log() << "[ save hitdig_gpu \n" ;
    hitdig_gpu->save("$HITFOLD/hitdig_gpu.npy");
    std::cout << U::Log() << "] save hitdig_gpu \n" ;

    std::cout << U::Log() << "[ save hitdig_cpu \n" ;
    hitdig_cpu->save("$HITFOLD/hitdig_cpu.npy");
    std::cout << U::Log() << "] save hitdig_cpu \n" ;


    return 0 ;
}
