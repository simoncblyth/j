#include "LayrTest.h"

int main(int argc, char** argv)
{
    {
        StackSpec<float> spec(StackSpec<float>::Default()); 
        LayrTest<float,4> t ; 
        t.scan_cpu(spec) ;
    }
    
    {
        StackSpec<float> spec(StackSpec<float>::Default()); 
        LayrTest<float,4> t ; 
        t.scan_gpu(spec) ;
    }

    {
        StackSpec<double> spec(StackSpec<double>::Default()); 
        LayrTest<double,4> t ; 
        t.scan_cpu(spec) ;
    }

    /*
    {
        StackSpec<double> spec(StackSpec<double>::Default()); 
        LayrTest<double,4> t ; 
        t.scan_gpu(spec) ;
    }
    */

    return 0 ; 
}
