// name=LayrMinimal ; gcc $name.cc -std=c++11 -lstdc++ -o /tmp/$name && /tmp/$name 

#include "Layr.h"

//typedef double T ; 
typedef float T ; 

int main(int argc, char** argv)
{
    T mct = argc > 1 ? std::atof(argv[1]) : -1.f  ;   // minus_cos_theta
    T wl  = argc > 2 ? std::atof(argv[2]) : 440.f ;   // wavelength_nm

    StackSpec<T> spec(StackSpec<T>::EGet()); // sensitive to L0, L1, L2, L3 envvars 

    Stack<T,4> stack(wl, mct, spec ); // ART calc done in ctor    

    std::cout << spec << stack ; 

    return 0 ; 
} 
