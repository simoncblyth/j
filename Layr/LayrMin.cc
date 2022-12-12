// name=LayrMin ; gcc $name.cc -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name 

#include <cstdlib>
#include "Layr.h"

//typedef double T ; 
typedef float T ; 

int main(int argc, char** argv)
{
    T mct = argc > 1 ? std::atof(argv[1]) : -1.f  ;   // minus_cos_theta
    T wl  = argc > 2 ? std::atof(argv[2]) : 440.f ;   // wavelength_nm

    putenv((char*)"L0=1,0,0");   
    putenv((char*)"L1=1.5,0,0");   

    StackSpec<T,2> ss ; 
    ss.eget();  

    std::cout << ss ; 

    Stack<T,2> stack(wl, mct, ss ); // ART calc done in ctor    

    std::cout << ss << stack ; 

    return 0 ; 
} 
