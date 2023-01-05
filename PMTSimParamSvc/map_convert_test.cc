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



template<typename T, typename S>
NP* serialize_vec( const std::vector<S>& v )
{
    assert( sizeof(S) > sizeof(T) ); 
    int ni = v.size() ; 
    int nj = sizeof(S) / sizeof(T) ; 

    NP* a = NP::Make<T>(ni, nj); 
    a->read2( (T*)v.data() ); 
    return a ; 
}

template<typename T>
int vector_from_map( std::vector<T>& v,  const std::map<int, T>& m, bool contiguous_key )
{
    typename std::map<int,T>::const_iterator it = m.begin()  ;
    int k0 = it->first ; 

    for(int idx=0 ; idx < int(m.size()) ; idx++)
    {
        int k = it->first ; 
        v[idx] = it->second ;

        if(contiguous_key) assert( k == k0 + idx );  
        //std::cout << " k0 " << k0 << " idx " << idx << " k " << k << " v " << it->second << std::endl ;  

        std::advance(it, 1);  
    }
    return k0 ; 
}

/**
serialize_map
----------------

A vector of S structs is populated from the map in the default key order of the map. 
An NP array is then created from the contiguous vector data.  

When contiguous_key:true the map keys are required to contiguously increment
from the first. The first key is recorded into the metadata of the array with name "k0". 
For example with keys: 100,101,102 the k0 would be 100. 

Serializing maps is most useful for contiguous_key:true as 
map access by key can then be mimicked by simply obtaining the 
array index by subtracting k0 from the map key.  

**/

template<typename T, typename S>
NP* serialize_map( const std::map<int, S>& m, bool contiguous_key )
{
    assert( sizeof(S) > sizeof(T) ); 

    int ni = m.size() ; 
    std::vector<S> v(ni) ; 

    int k0 = vector_from_map<S>( v, m, contiguous_key ); 
    NP* a = serialize_vec<T,S>(v) ; 
    a->set_meta<int>("k0", k0) ; 
    return a ; 
}


int main(int argc, char** argv)
{
    Item::sizeof_check(); 

    std::vector<Item> ii(3) ; 
    ii[0].fill(0) ; 
    ii[1].fill(1) ; 
    ii[2].fill(2) ; 

    NP* _ii = serialize_vec<double, Item>( ii ) ; 
    std::cout << " _ii.sstr " << _ii->sstr() << std::endl ; 

    std::map<int, Item> im ; 
    im[100] = ii[0] ; 
    im[101] = ii[1] ; 
    im[102] = ii[2] ; 

    bool contiguous_key = true ; 
    NP* _im = serialize_map<double, Item>( im, contiguous_key ) ; 
    std::cout << " _im.sstr " << _im->sstr() << std::endl ; 

    _ii->save(FOLD, "ii.npy") ; 
    _im->save(FOLD, "im.npy") ; 

    return 0 ; 
}

