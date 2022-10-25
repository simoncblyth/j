#include "LayrTest.h"

int main(int argc, char** argv)
{
    LayrTest<double,4> t0 ; 
    t0.scan() ;
    t0.save("/tmp/LayrTest0") ;
    std::cout << t0.desc() << std::endl ; 

    LayrTest<float,4> t1 ; 
    t1.scan() ;
    t1.save("/tmp/LayrTest1") ;
    std::cout << t1.desc() << std::endl ; 

    return 0 ; 
}
