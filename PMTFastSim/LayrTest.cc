#include "NP.hh"
#include "Layr.h"

template<typename T, int N>
struct LayrTest
{
    const StackSpec<T> ss ; 
    LayrTest(const StackSpec<T>& ss); 
    void scan(const char* dir, T wl, bool reverse=false); 
};


template<typename T, int N>
LayrTest<T,N>::LayrTest(const StackSpec<T>& ss_)
    :
    ss(ss_)
{
}





/**
LayrTest::scan
---------------

Initially it feels like a cheap trick (avoiding need for rerunable object) 
to instanciate the Stack object within the scan loop. 
But actually thats the real situation as the refractive 
indices depend on wavelength : so the matrix stack needs to be 
recomputed for every wl and angle.
Having a fixed wavelength to change angle with is purely artificial
whilst doing angle scanning. 

**/

template<typename T, int N>
void LayrTest<T,N>::scan(const char* dir, T wl, bool reverse)
{
    const int NI=900 ; 
    std::vector<T> theta(NI) ; 
    for(int i=0 ; i < NI ; i++ ) theta[i] = M_PI*0.1*T(i)/T(180) ; 

    std::vector<ART<T>>   arts(NI) ;  
    std::vector<Layr<T>> comps(NI) ;  
    std::vector<Layr<T>> lls(NI*N) ;  

    Stack<T,N> stack(wl, ss) ; 

    for(int i=0 ; i < NI ; i += 1 )
    {
        int j = reverse ? NI - 1 - i : i ;  
        T th = theta[j] ;   // radians

        stack.computeART(th); 

        arts[j] = stack.art; 
        comps[j] = stack.comp ; 
        for(int l=0 ; l < N ; l++) lls[N*j+l] = stack.ll[l]; 

        std::cout << " i:" << i << " j:" << j << std::endl ; 
        if( i == 0 || (i == NI - 1)) std::cout << stack << std::endl ; 
        else std::cout << stack.art << std::endl ; 
    }

    assert( sizeof(ART<T>)/sizeof(T) == 12 ); 
    assert( sizeof(Layr<T>)/sizeof(T) == 4*4*2 ); 

    NP::Write(dir,"arts.npy", (T*)arts.data(),  NI, 3, 4 ) ;       // one ART result (3,4) at each angle 
    NP::Write(dir,"comps.npy",(T*)comps.data(), NI,    4, 4, 2 ) ; // 1 composite layer (4,4,2) at each angle
    NP::Write(dir,"lls.npy",  (T*)lls.data()  , NI, 4, 4, 4, 2 ) ; // 4 layers (4,4,2) at each angle 
}

int main(int argc, char** argv)
{
    StackSpec<double> ss(StackSpec<double>::Default()); 
    LayrTest<double,4> t(ss) ; 

    double wl = U::GetE<double>("WL", 500.) ; 

    t.scan("/tmp/LayrTest0", wl, false) ;
    t.scan("/tmp/LayrTest1", wl, true ) ;

    return 0 ; 
}
