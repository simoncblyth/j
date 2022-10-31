/**
LayrTest.cc
=============

TODO: plotting indices 


**/

#include "sdomain.h"

#include "LayrTest.h"

template<typename T>
void test_scan()
{
    StackSpec<T> spec(StackSpec<T>::EGet()); 
    std::cout << spec << std::endl ; 

    LayrTest<T,4> t0 ; 
    t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
    LayrTest<T,4> t1 ; 
    t1.scan_gpu(spec) ;
#endif
}


int main(int argc, char** argv)
{
    test_scan<float>(); 
    test_scan<double>(); 

    return 0 ; 
}
