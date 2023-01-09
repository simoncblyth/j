/**
map_convert_test.cc
======================

::

   ./map_convert_test.sh

The best way to serialize the map depends on whether it really should 
be a map in the first place. Normally maps should really be vectors or arrays, 
and are used only because people are too lazy to subtract an integer offset in keys. 

* Having "char* dummy" in Item messes up alignment, such that do not get expected sizeof(Item)
* Its more convenient for all elements to be the same size rather than use padding.

**/


#include <cstdint>
#include <map>
#include <vector>
#include "NP.hh"

const char* FOLD = getenv("FOLD"); 

struct Item
{
    int64_t idx ; 
#ifdef WITH_DUMMY
    char* dummy{nullptr} ; // 8   
#endif
    double a ;    // 8
    double b ;    // 8
    double c ;    // 8

    void zero(); 
    void fill(int v); 
    static void sizeof_check(); 
}; 

inline void Item::zero()
{
    idx = 0 ; 
    a = 0. ; 
    b = 0. ; 
    c = 0. ; 
}
inline void Item::fill(int v)
{
   idx = v ; 
   a = v ; 
   b = v+1 ; 
   c = v+2 ; 
} 
inline void Item::sizeof_check()  // static
{
    std::cout << " sizeof(Item) " << sizeof(Item) << std::endl ; 
    std::cout << " sizeof(Item)/sizeof(double) " << sizeof(Item)/sizeof(double) << std::endl ; 
    std::cout << " 4*sizeof(double) " << 4*sizeof(double) << std::endl ; 
    std::cout << " 2*sizeof(int) + 3*sizeof(double) " << 2*sizeof(int) + 3*sizeof(double) << std::endl ; 
    std::cout << " sizeof(int) + 3*sizeof(double) " << sizeof(int) + 3*sizeof(double) << std::endl ; 
    std::cout << " sizeof(int) " << sizeof(int) << std::endl ; 
    std::cout << " sizeof(int64_t) " << sizeof(int64_t) << std::endl ; 
    std::cout << " sizeof(double) " << sizeof(double) << std::endl ; 
    std::cout << " sizeof(char*) " << sizeof(char*) << std::endl ; 
    assert( sizeof(Item) == 2*sizeof(int) + 3*sizeof(double)  ); 
    assert( sizeof(Item) == 4*sizeof(double)  ); 
}
inline std::ostream& operator<<(std::ostream& os, const Item& v)
{
    int w = 10 ; 
    os   
       << "("  
       << std::setw(w) << v.idx  
       << ";"  
       << std::setw(w) << v.a
       << ","  
       << std::setw(w) << v.b  
       << ","  
       << std::setw(w) << v.c  
       << ") "  
       ;    
    return os;  
}




int main(int argc, char** argv)
{
    Item::sizeof_check(); 

    std::vector<Item> ii(3) ; 
    ii[0].fill(0) ; 
    ii[1].fill(1) ; 
    ii[2].fill(2) ; 

    NP* _ii = NP::ArrayFromVec<double, Item>( ii ); 

    std::cout << " _ii.sstr " << _ii->sstr() << std::endl ; 

    std::map<int, Item> im ; 
    im[100] = ii[0] ; 
    im[101] = ii[1] ; 
    im[102] = ii[2] ; 

    bool contiguous_key = true ; 
    NP* _im = NP::ArrayFromMap<double, Item>( im, contiguous_key ) ; 
    std::cout << " _im.sstr " << _im->sstr() << std::endl ; 

    _ii->save(FOLD, "ii.npy") ; 
    _im->save(FOLD, "im.npy") ; 

    return 0 ; 
}

