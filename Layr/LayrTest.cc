#include "LayrTest.h"

int main(int argc, char** argv)
{
    {
        StackSpec<float> spec(StackSpec<float>::Default()); 

        LayrTest<float,4> t0 ; 
        t0.scan_cpu(spec) ;
    
#ifdef WITH_THRUST
        LayrTest<float,4> t1 ; 
        t1.scan_gpu(spec) ;
#endif
    }

    {
        StackSpec<double> spec(StackSpec<double>::Default()); 

        LayrTest<double,4> t0 ; 
        t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
        LayrTest<double,4> t1 ; 
        t1.scan_gpu(spec) ;
#endif
    }

    return 0 ; 
}
