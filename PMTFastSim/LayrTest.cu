#include "stdio.h"
#include "Layr.h"
#include "LayrTest.h"

__global__ 
void on_device(LayrTestData<float,4>* ltd)
{ 
    unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
    if( idx >= ltd->ni ) return ;  

    float th = ltd->theta[idx] ; 
    StackSpec<float> spec = StackSpec<float>::Default() ; 
    Stack<float,4> stk(ltd->wl, spec) ; 
    stk.computeART(th); 

    printf("// ltd.ni %d idx %d stk.art.R %10.4f stk.art.T %10.4f  \n", ltd->ni, idx, stk.art.R, stk.art.T ); 

    ltd->arts[idx] = stk.art ; 
    ltd->comps[idx] = stk.comp ; 
    for(int l=0 ; l < 4 ; l++) ltd->lls[4*idx+l] = stk.ll[l]; 
} 

void ConfigureLaunch(dim3& numBlocks, dim3& threadsPerBlock, unsigned width )
{ 
    threadsPerBlock.x = 512 ; 
    threadsPerBlock.y = 1 ; 
    threadsPerBlock.z = 1 ; 

    numBlocks.x = (width + threadsPerBlock.x - 1) / threadsPerBlock.x ; 
    numBlocks.y = 1 ; 
    numBlocks.z = 1 ; 
}


#ifdef WITH_CUDA_LAUNCH_MAIN
int main()
{
    LayrTest<float,4> t ; 

    t.upload(); 
    assert( t.d_ptr ); 

    dim3 numBlocks ; 
    dim3 threadsPerBlock ; 
    ConfigureLaunch(numBlocks, threadsPerBlock, t.d.ni );  

    on_device<<<numBlocks,threadsPerBlock>>>(t.d_ptr) ; 
    cudaDeviceSynchronize();

    t.download();

    t.save("/tmp/LayrTest2"); 

    return 0 ; 
}
#endif



