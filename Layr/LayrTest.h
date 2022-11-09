#pragma once
/**
LayrTest.h
===========

Note structure allowing reuse of the same code for CPU and GPU running. 

* nvcc compilation just needs layout of the structs, not the methods

**/

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
#include "NP.hh"

#ifdef WITH_THRUST
#include "SU.hh"
#include <cuda_runtime.h>
#endif

#endif
#include "Layr.h"

template<typename T, int N>
struct LayrTestData    // LayrScanData  better name ?
{
    int      ni ;     // number of items : currently angles 
    T        wl ;     // hmm could vary wl, by making this an array 
    T*       theta ; 
    ART<T>*  arts ; 
    Layr<T>* comps ;  
    Layr<T>* lls ; 
};

template<typename T, int N>
struct LayrTest
{
    LayrTestData<T,N> h ;      // host side struct with arrays populated by scan_cpu (OR download from scan_gpu)  

    LayrTestData<T,N> d ;      // host side preparation of device side struct containing device pointers
    LayrTestData<T,N>* d_ptr ; // device pointer to uploaded copy of above d struct, populated by scan_gpu 

    bool             gpu ; 
    const char*      base ; 
    const char*      label ; 

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
    LayrTest(int ni=90, T wl=0, const char* label=nullptr );

#ifdef WITH_THRUST
    void upload(); 
    void download(); 
    void scan_gpu(const StackSpec<T>& spec); 
#else
    // without thrust::complex cannot run on GPU 
#endif
    void scan_cpu(const StackSpec<T>& spec); 

    const char* get_name() const ; 
    void save() const ; 
    std::string desc() const ; 
    std::string brief() const ; 
#endif
};

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template<typename T, int N>
inline LayrTest<T,N>::LayrTest(int ni, T wl, const char* label_ )
    :
    d_ptr(nullptr),
    gpu(false),    // flipped true/false by calling scan_gpu/scan_cpu
    base(U::GetEnv("LAYRTEST_BASE", "/tmp/LayrTest")),
    label(label_ ? strdup(label_) : nullptr)
{
    assert( sizeof(T) == 4 || sizeof(T) == 8 ); 
    h.ni = ni ; 
    h.wl = wl > 0. ? wl : U::GetE<double>("WL", 500.) ; 
    h.theta = new T[ni] ; 
    h.arts  = new ART<T>[ni] ; 
    h.comps = new Layr<T>[ni] ; 
    h.lls   = new Layr<T>[N*ni] ; 

    bool all = false ; 
    for(int i=0 ; i < ni ; i++ ) 
    {
        h.theta[i] = T(i)/T(all ? ni-1 :ni)*M_PI/T(2) ; 
        // ni angles  0 -> (all?1:89/90) * pi/2  radians
    }
    // Avoiding pi/2 (glancing incidence) as get very large float/double mismatch in lls and comps 
    // TODO: look into details to see if this glancing edge case needs some special treatment. 
}

#ifdef WITH_THRUST
template<typename T, int N>
inline void LayrTest<T,N>::upload()   // prepare device side arrays
{
    int ni = h.ni ; 
    d.ni = ni ; 
    d.wl = h.wl ;

    d.theta =       (T*)SU::device_alloc_sizeof(ni, sizeof(T)) ;     
    d.arts  = ( ART<T>*)SU::device_alloc_sizeof(ni, sizeof(ART<T>) ); 
    d.comps = (Layr<T>*)SU::device_alloc_sizeof(ni, sizeof(Layr<T>) ); 
    d.lls   = (Layr<T>*)SU::device_alloc_sizeof(ni, sizeof(Layr<T>)*N ); 

    printf("// upload h.theta[0] %10.4f h.theta[ni-1] %10.4f \n", h.theta[0], h.theta[ni-1] ); 
    SU::copy_host_to_device_sizeof( (char*)d.theta, (char*)h.theta, ni, sizeof(T) ); 

    d_ptr = (LayrTestData<T,N>*)SU::upload_array_sizeof((char*)&d, 1, sizeof(LayrTestData<T,N>) );  
}

template<typename T, int N>
inline void LayrTest<T,N>::download() // d->h : copy device side arrays down into host side 
{
    int ni = d.ni ; 
    assert( d_ptr != nullptr ); // must upload before download
    SU::copy_device_to_host_sizeof( (char*)h.arts , (char*)d.arts , ni, sizeof(ART<T>) ); 
    SU::copy_device_to_host_sizeof( (char*)h.comps, (char*)d.comps, ni, sizeof(Layr<T>) ); 
    SU::copy_device_to_host_sizeof( (char*)h.lls  , (char*)d.lls  , ni, sizeof(Layr<T>)*N ); 
}

template <typename T, int N>
extern void LayrTest_launch( LayrTest<T,N>& t, const StackSpec<T>& spec ); 

template<typename T, int N>
inline void LayrTest<T,N>::scan_gpu(const StackSpec<T>& spec)
{
    gpu = true ; 
    upload();  // prepare device side arrays

    LayrTest_launch<T,N>(*this, spec) ; // populate them 

    cudaDeviceSynchronize();
    download();   // copy d->h (overwriting any prior scan from scan_cpu OR scan_gpu)
    save();       // persist the h arrays 
}
#endif


/**
LayrTest::scan_cpu
---------------------

Stack does everything in ctor because any change in wl or th 
demands almost everything is recomputed anyhow 

NOTE THE WL DEPENDENCY COMING IN TWICE 

**/
 
template<typename T, int N>
inline void LayrTest<T,N>::scan_cpu(const StackSpec<T>& spec)
{
    gpu = false ; 
    bool reverse = false ; 
    for(int i=0 ; i < h.ni ; i++ )
    {
        int j = reverse ? h.ni - 1 - i : i ; 
        Stack<T,N> stack(h.wl, h.theta[j], spec ) ; 

        h.arts[j] = stack.art; 
        h.comps[j] = stack.comp ; 
        for(int l=0 ; l < N ; l++) h.lls[N*j+l] = stack.ll[l]; 

        //std::cout << stack << std::endl ; 
        //std::cout << "j:" << j << std::endl << stack.art << std::endl ; 
    }
    save(); 
}

template<typename T, int N>
inline std::string LayrTest<T,N>::desc() const 
{
    std::stringstream ss ; 
    for(int i=0 ; i < h.ni ; i++)
    {
        const ART<T>& art = h.arts[i] ; 
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
inline std::string LayrTest<T,N>::brief() const 
{
    const char* name = get_name() ; 
    std::stringstream ss ; 
    ss
        << "LayrTest"
        << "<"  
        << ( sizeof(T) == 8 ? "double" : "float" ) 
        << "," 
        << N 
        << ">"   
#ifdef WITH_THRUST
        << " WITH_THRUST "
#else
        << " not-WITH_THRUST "
#endif
        << " name " << name
        << " ni " << h.ni         
        << " wl " << h.wl         
        << " theta[0] " << h.theta[0]
        << " theta[ni-1] " << h.theta[h.ni-1]
        ; 
    std::string s = ss.str(); 
    return s ; 
}

template<typename T, int N>
inline const char* LayrTest<T,N>::get_name() const 
{
    std::stringstream ss ; 
    ss 
       << "scan_" 
       << ( label ? label : "" )
       << "_"
       << ( gpu ? "gpu" : "cpu" ) 
       << "_" 
#ifdef WITH_THRUST
       << "thr"
#else
       << "std"
#endif
       << "_" 
       << ( sizeof(T) == 8 ? "double" : "float" ) 
       ;
    std::string s = ss.str(); 
    return strdup(s.c_str()) ; 
}

template<typename T, int N>
inline void LayrTest<T,N>::save() const 
{
    std::string br = brief(); 
    std::cout << br << std::endl ;  

    assert( sizeof(ART<T>)/sizeof(T) == 12 ); 
    assert( sizeof(Layr<T>)/sizeof(T) == 4*4*2 ); 

    const char* name = get_name() ; 
    NP::Write(base, name,"comps.npy",(T*)h.comps, h.ni,    4, 4, 2 ) ;
    NP::Write(base, name,"lls.npy",  (T*)h.lls  , h.ni, N, 4, 4, 2 ) ;

    // use manual way for _arts so can set metadata
    NP* _arts = NP::Make<T>( h.ni, 3, 4 );
    _arts->read2( (T*)h.arts ); 
    _arts->set_meta<std::string>("brief", br); 
    _arts->set_meta<std::string>("name", name); 
    _arts->set_meta<std::string>("label", label); 
    _arts->set_meta<T>("wl", h.wl); 
    _arts->save(base, name, "arts.npy" ); 
}
#endif

