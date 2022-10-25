//#include "stdio.h"

#include <cassert>
#include "Layr.h"
#include "LayrTest.h"

#define LAYRTEST_API  __attribute__ ((visibility ("default")))

template<typename T, int N>
__global__ void Stack_computeART_gpu(LayrTestData<T,N>* ltd, const StackSpec<T>& spec )
{ 
    unsigned idx = blockIdx.x * blockDim.x + threadIdx.x;
    if(idx >= ltd->ni) return ;  

    T th = ltd->theta[idx] ; 
    //StackSpec<T> spec = StackSpec<T>::Default() ;  // TODO: pass this in 

    Stack<T,N> stk(ltd->wl, spec) ; 
    stk.computeART(th); 

    ltd->arts[idx] = stk.art ; 
    ltd->comps[idx] = stk.comp ; 
    for(int l=0 ; l < N ; l++) ltd->lls[N*idx+l] = stk.ll[l]; 

    //printf("// ltd.ni %d idx %d stk.art.R %10.4f stk.art.T %10.4f  \n", ltd->ni, idx, stk.art.R, stk.art.T ); 
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

template<typename T, int N>
void LayrTest_launch(LayrTest<T,N>& t, const StackSpec<T>& spec )
{
    assert( t.d_ptr ); 
    dim3 numBlocks ; 
    dim3 threadsPerBlock ; 
    ConfigureLaunch(numBlocks, threadsPerBlock, t.d.ni );  
    Stack_computeART_gpu<T,N><<<numBlocks,threadsPerBlock>>>(t.d_ptr, spec) ; 
}

template LAYRTEST_API void LayrTest_launch(LayrTest<float, 4>&, const StackSpec<float>&  ); 
template LAYRTEST_API void LayrTest_launch(LayrTest<double,4>&, const StackSpec<double>&  ); 

