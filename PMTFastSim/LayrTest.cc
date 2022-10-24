#include "NP.hh"
#include "Layr.h"

template<typename T, int N>
struct LayrTest
{
    int      ni ;   // number of angles 
    T        wl ; 
    T*       theta ; 
    ART<T>*  arts ; 
    Layr<T>* comps ;  
    Layr<T>* lls ; 

    LayrTest(int ni, T wl=0);
    void scan(const StackSpec<T>& ss, bool reverse=false); 
    void save(const char* dir) const ; 

    std::string desc() const ; 
    std::string brief() const ; 
};

template<typename T, int N>
LayrTest<T,N>::LayrTest(int ni_, T wl_)
    :
    ni(ni_),
    wl(wl_ > 0 ? wl_ : U::GetE<double>("WL", 500.)), 
    theta(new T[ni]),
    arts(new ART<T>[ni] ),
    comps(new Layr<T>[ni]),
    lls(new Layr<T>[N*ni])
{
    assert( sizeof(T) == 4 || sizeof(T) == 8 ); 
    for(int i=0 ; i < ni ; i++ ) theta[i] = T(i)/T(ni-1)*M_PI/T(2) ; // angles from 0 to pi/2 radians
}

template<typename T, int N>
std::string LayrTest<T,N>::brief() const 
{
    std::stringstream ss ; 
    ss
        << "LayrTest<"  << ( sizeof(T) == 8 ? "double" : "float" ) << "," << N << ">"   
#ifdef WITH_THRUST
        << " WITH_THRUST "
#else
        << " not-WITH_THRUST "
#endif
        << " ni " << ni         
        << " wl " << wl         
        << " theta[0] " << theta[0]
        << " theta[ni-1] " << theta[ni-1]
        ; 
    std::string s = ss.str(); 
    return s ; 
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
void LayrTest<T,N>::scan(const StackSpec<T>& spec, bool reverse)
{
    Stack<T,N> stack(wl, spec) ; 
    for(int i=0 ; i < ni ; i++ )
    {
        int j = reverse ? ni - 1 - i : i ;  
        stack.computeART(theta[j]); 

        arts[j] = stack.art; 
        comps[j] = stack.comp ; 
        for(int l=0 ; l < N ; l++) lls[N*j+l] = stack.ll[l]; 

        //std::cout << stack << std::endl ; 
        //std::cout << "j:" << j << std::endl << stack.art << std::endl ; 
    }
}

template<typename T, int N>
std::string LayrTest<T,N>::desc() const 
{
    std::stringstream ss ; 
    for(int i=0 ; i < ni ; i++)
    {
        const ART<T>& art = arts[i] ; 
        ss << " i:" << i 
           << std::endl  
           << art 
           << std::endl 
           ; 
    }
    std::string s = ss.str();
    return s ; 
}

template<typename T, int N>
void LayrTest<T,N>::save(const char* dir) const 
{
    assert( sizeof(ART<T>)/sizeof(T) == 12 ); 
    assert( sizeof(Layr<T>)/sizeof(T) == 4*4*2 ); 

    NP::Write(dir,"comps.npy",(T*)comps, ni, 4, 4, 2 ) ;    // 1 composite layer (4,4,2) at each angle
    NP::Write(dir,"lls.npy",  (T*)lls  , ni, 4, 4, 4, 2 ) ; // 4 layers (4,4,2) at each angle 

    // use manual way for _arts so can set metadata 
    NP* _arts = NP::Make<T>( ni, 3, 4 ); // one ART result (3,4) at each angle 
    _arts->read2( (T*)arts ); 
    _arts->set_meta<std::string>("brief", brief()); 
    _arts->set_meta<T>("wl", wl); 
    _arts->save(dir, "arts.npy" ); 
}

int main(int argc, char** argv)
{
    StackSpec<double> spec(StackSpec<double>::Default()); 
    LayrTest<double,4> t(90) ; 

    std::cout << t.brief() << std::endl ; 

    t.scan(spec, false) ;
    t.save("/tmp/LayrTest0") ;
    std::cout << t.desc() << std::endl ; 

    t.scan(spec, true) ;
    t.save("/tmp/LayrTest1") ;
    std::cout << t.desc() << std::endl ; 

    return 0 ; 
}
