#include "LayrTest.h"

int main(int argc, char** argv)
{
    {
        StackSpec<float> spec(StackSpec<float>::EGet()); 
        std::cout << spec << std::endl ; 

        LayrTest<float,4> t0 ; 
        t0.scan_cpu(spec) ;
    
#ifdef WITH_THRUST
        LayrTest<float,4> t1 ; 
        t1.scan_gpu(spec) ;
#endif
    }

    {
        StackSpec<double> spec(StackSpec<double>::EGet()); 
        std::cout << spec << std::endl ; 

        LayrTest<double,4> t0 ; 
        t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
        LayrTest<double,4> t1 ; 
        t1.scan_gpu(spec) ;
#endif
    }

    return 0 ; 
}
