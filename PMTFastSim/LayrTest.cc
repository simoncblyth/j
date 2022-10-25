#include "LayrTest.h"

int main(int argc, char** argv)
{
    {
        StackSpec<float> spec(StackSpec<float>::Default()); 

        LayrTest<float,4> t0 ; 
        t0.scan_cpu(spec) ;
    
        LayrTest<float,4> t1 ; 
        t1.scan_gpu(spec) ;
    }

    {
        StackSpec<double> spec(StackSpec<double>::Default()); 

        LayrTest<double,4> t0 ; 
        t0.scan_cpu(spec) ;

        LayrTest<double,4> t1 ; 
        t1.scan_gpu(spec) ;
    }

    return 0 ; 
}
