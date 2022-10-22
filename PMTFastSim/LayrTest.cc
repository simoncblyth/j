#include "NP.hh"
#include "Layr.h"

template<typename T>
struct LayrTest
{
    Stack<T,4> stk ;  

    Layr<T>& l0 ; 
    Layr<T>& l1 ; 
    Layr<T>& l2 ; 
    Layr<T>& l3 ; 

    LayrTest<T>() ; 
    void scan(const char* path, int NI, bool reverse); 
};

template<typename T>
LayrTest<T>::LayrTest()
    :
    l0(stk.ll[0]),
    l1(stk.ll[1]),
    l2(stk.ll[2]),
    l3(stk.ll[3])
{
    l0.n.real(1.0) ; l0.n.imag(0.0)  ; l0.d = 0. ; 
    l1.n.real(1.0) ; l1.n.imag(0.01) ; l1.d = 500. ; // nm (same length unit as wavelength)
    l2.n.real(1.0) ; l2.n.imag(0.01) ; l2.d = 500. ;          
    l3.n.real(1.5) ; l3.n.imag(0.0)  ; l3.d = 0. ; 
}

template<typename T>
void LayrTest<T>::scan(const char* dir, int NI, bool reverse)
{
    std::vector<ART<T>> arts(NI) ;  
    std::vector<Layr<T>> comps(NI) ;  
    std::vector<Layr<T>> lls(NI*4) ;  

    T wl(500) ;  // nm 
    for(int i=0 ; i < NI ; i += 1 )
    {
        int j = reverse ? NI - 1 - i : i ;  
        T th = M_PI*T(j)/T(180) ;  // radians

        stk.computeART(wl, th); 
        arts[j] = stk.art; 
        comps[j] = stk.comp ; 
       
        lls[4*j+0] = stk.ll[0] ; 
        lls[4*j+1] = stk.ll[1] ; 
        lls[4*j+2] = stk.ll[2] ; 
        lls[4*j+3] = stk.ll[3] ; 

        std::cout 
            << " i:" << i 
            << " j:" << j 
            << std::endl 
            ; 
        //std::cout << stk << std::endl ; 
        std::cout << stk.art << std::endl ; 
    }

    assert( sizeof(ART<T>)/sizeof(T) == 12 ); 
    assert( sizeof(Layr<T>)/sizeof(T) == 4*4*2 ); 

    NP::Write(dir,"arts.npy", (T*)arts.data(),  arts.size(), 3, 4 ) ; 
    NP::Write(dir,"comps.npy",(T*)comps.data(), comps.size(), 4, 4, 2 ) ; 
    NP::Write(dir,"lls.npy",(T*)lls.data(), lls.size()/4, 4, 4, 4, 2 ) ; 
}

int main(int argc, char** argv)
{
    std::cout << sizeof(Layr<double>) << std::endl ; 

    LayrTest<double> t ; 
    t.scan("/tmp/LayrTest0", 45, false) ;
    t.scan("/tmp/LayrTest1", 45, true ) ;

    return 0 ; 
}
