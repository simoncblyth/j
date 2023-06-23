#pragma once
/**
LayrTest.h
===========

Note simple structure making use of arrays of structs 
to allow reuse of the same code for both CPU and GPU running. 

* nvcc compilation mainly needs struct layout, rather than the methods

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

/**
LayrTestData : acts as primary host<->device communication mechanism
-----------------------------------------------------------------------

Retaining all the comps, lls for every test item  
is for debugging purposes only. 

NB using simple pointers to arrays enables this struct 
to be used on both device and host and copied between them

**/

template<typename T, int N>
struct LayrTestData    // LayrScanData  better name ?
{
    int      ni ;     // number of items 
    T        wl ;     // hmm could vary wl, by making this an array 

    T*       mct ;    // ni : minus_cos_theta from -1 to 1, > 0 is backwards stack
    ART_<T>* arts ;   // ni : ART_ results
    Layr<T>* comps ;  // ni : composite layers
    Layr<T>* lls ;    // ni*N : individual layers 
};


/**
LayrTest
----------

* h : host side struct with arrays populated by scan_cpu (OR download from scan_gpu)  
* d : host side preparation of device side struct containing device pointers
* d_ptr : device pointer to uploaded copy of above d struct, populated by scan_gpu 

**/

template<typename T, int N>
struct LayrTest
{
    LayrTestData<T,N> h ;   // host instance
    LayrTestData<T,N> d ;   // hostside device instance, to enable pre-init      
    LayrTestData<T,N>* d_ptr ; // pointer to deviceside instance

    bool             gpu ; 
    const char*      base ; 
    const char*      label ; 
    bool half ; 

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
    static const char* Base(); 
    LayrTest(int ni=90, T wl=0, const char* label=nullptr );
    void init_h(int ni, T wl); 

#ifdef WITH_THRUST
    void upload(); 
    void download(); 
    void scan_gpu(const StackSpec<T,N>& spec); 
#else
    // without thrust::complex cannot run on GPU 
#endif
    void scan_cpu(const StackSpec<T,N>& spec); 

    const char* get_name() const ; 
    void save(const StackSpec<T,N>& spec) const ; 
    std::string desc() const ; 
    std::string brief() const ; 
    std::string title() const ; 
#endif
};

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template<typename T, int N>
inline const char* LayrTest<T,N>::Base()  // static 
{
    std::stringstream ss ; 
    ss << U::GetEnv("LAYRTEST_BASE", "/tmp/LayrTest") ; 
    ss << "/" << N ; 
    std::string s = ss.str(); 
    const char* base = strdup(s.c_str()); 
    return base ; 
}

template<typename T, int N>
inline LayrTest<T,N>::LayrTest(int ni, T wl, const char* label_ )
    :
    d_ptr(nullptr),
    gpu(false),    // flipped true/false by calling scan_gpu/scan_cpu
    base(Base()),
    label(label_ ? strdup(label_) : nullptr),
    half(U::GetEnvInt("LAYRTEST_HALF",0) == 1)
{
    init_h(ni, wl); 
}

/**
LayrTest::init_h
-----------------

Hostside allocate, populate mct with minus_cos_theta values for AOI scan.  

**/

template<typename T, int N>
inline void LayrTest<T,N>::init_h(int ni, T wl)
{
    assert( sizeof(T) == 4 || sizeof(T) == 8 ); 
    h.ni = ni ; 
    h.wl = wl > 0. ? wl : U::GetE<double>("WL", 500.) ; 

    h.mct = new T[ni] ; 
    h.arts  = new ART_<T>[ni] ; 
    h.comps = new Layr<T>[ni] ; 
    h.lls   = new Layr<T>[N*ni] ; 

    T max_theta_pi = half ? T(1)/T(2) : T(1) ;  
    bool end_one = half ? false : true ;

    for(int i=0 ; i < ni ; i++ ) 
    {
        T theta_frac =  T(i)/T(end_one ? ni-1 : ni) ;  
        T theta = theta_frac*max_theta_pi*M_PI ; 
        h.mct[i] = -cos(theta) ;  
    }
}

/**
LayrTest::upload
-----------------

1. copy values from h to d LayrTestData instances
2. allocate LayrTestData memory on device, collecting pointers  
3. upload the d instance with pre-initialized pointers to device 

**/

#ifdef WITH_THRUST
template<typename T, int N>
inline void LayrTest<T,N>::upload()   // prepare device side arrays
{
    int ni = h.ni ; 
    d.ni = ni ; 
    d.wl = h.wl ;

    d.mct   =       (T*)SU::device_alloc_sizeof(ni, sizeof(T)) ;     
    d.arts  = (ART_<T>*)SU::device_alloc_sizeof(ni, sizeof(ART_<T>) ); 
    d.comps = (Layr<T>*)SU::device_alloc_sizeof(ni, sizeof(Layr<T>) ); 
    d.lls   = (Layr<T>*)SU::device_alloc_sizeof(ni, sizeof(Layr<T>)*N ); 

    printf("// upload h.mct[0] %10.4f h.mct[ni-1] %10.4f \n", h.mct[0], h.mct[ni-1] ); 
    SU::copy_host_to_device_sizeof( (char*)d.mct, (char*)h.mct, ni, sizeof(T) ); 

    d_ptr = (LayrTestData<T,N>*)SU::upload_array_sizeof((char*)&d, 1, sizeof(LayrTestData<T,N>) );  
}

/**
LayrTest::download
--------------------

Copy the LayrTestData components from device to hostside instance. 

**/

template<typename T, int N>
inline void LayrTest<T,N>::download() // d->h : copy device side arrays down into host side 
{
    int ni = d.ni ; 
    assert( d_ptr != nullptr ); // must upload before download
    SU::copy_device_to_host_sizeof( (char*)h.arts , (char*)d.arts , ni, sizeof(ART_<T>) ); 
    SU::copy_device_to_host_sizeof( (char*)h.comps, (char*)d.comps, ni, sizeof(Layr<T>) ); 
    SU::copy_device_to_host_sizeof( (char*)h.lls  , (char*)d.lls  , ni, sizeof(Layr<T>)*N ); 
}

template <typename T, int N>
extern void LayrTest_launch( LayrTest<T,N>& t, const StackSpec<T,N>& spec ); 

template<typename T, int N>
inline void LayrTest<T,N>::scan_gpu(const StackSpec<T,N>& spec)
{
    gpu = true ; 

    upload();                           // prepare device side arrays
    LayrTest_launch<T,N>(*this, spec) ; // populate device side arrays

    cudaDeviceSynchronize();
    download();                         // copy d->h (overwriting any prior scan from scan_cpu OR scan_gpu)
    save(spec);                        // persist the h arrays 
}
#endif


/**
LayrTest::scan_cpu
---------------------

Stack does everything in ctor because any change in wl or th 
demands almost everything is recomputed anyhow 

NOTE THE WL DEPENDENCY COMING IN TWICE : IN WL AND SPEC

**/
 
template<typename T, int N>
inline void LayrTest<T,N>::scan_cpu(const StackSpec<T,N>& spec)
{
    gpu = false ; 
    bool reverse = false ; 
    for(int i=0 ; i < h.ni ; i++ )
    {
        int j = reverse ? h.ni - 1 - i : i ;      // just debugging reorder
        Stack<T,N> stack(h.wl, h.mct[j], spec ) ; // ART_ calc done in ctor

        h.arts[j] = stack.art; 
        h.comps[j] = stack.comp ; 
        for(int l=0 ; l < N ; l++) h.lls[N*j+l] = stack.ll[l]; 

        //std::cout << stack << std::endl ; 
        //std::cout << "j:" << j << std::endl << stack.art << std::endl ; 
    }
    save(spec);  // saves arts, comps, lls and spec 
}

template<typename T, int N>
inline std::string LayrTest<T,N>::desc() const 
{
    std::stringstream ss ; 
    for(int i=0 ; i < h.ni ; i++)
    {
        const ART_<T>& art = h.arts[i] ; 
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
        << " mct[0] " << h.mct[0]
        << " mct[ni-1] " << h.mct[h.ni-1]
        ; 
    std::string s = ss.str(); 
    return s ; 
}

template<typename T, int N>
inline std::string LayrTest<T,N>::title() const 
{
    const char* name = get_name() ; 
    std::stringstream ss ; 
    ss
        << "j/Layr/LayrTest"
        << " " << name
        << " ni " << h.ni         
        << " wl " << h.wl         
        ; 
    std::string s = ss.str(); 
    return s ; 
}

template<typename T, int N>
inline const char* LayrTest<T,N>::get_name() const 
{
    std::stringstream ss ; 
    ss 
       << "scan__" 
       << ( label ? label : "" )
       << "__"
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
inline void LayrTest<T,N>::save(const StackSpec<T,N>& spec) const 
{
    std::string ti = title(); 
    std::string br = brief(); 
    std::cout << " title " << ti << std::endl ;  
    std::cout << " brief " << br << std::endl ;  

    assert( sizeof(ART_<T>)/sizeof(T) == 4*4 ); 
    assert( sizeof(Layr<T>)/sizeof(T) == 4*4*2 ); 

    const char* name = get_name() ; 
    NP::Write(base, name,"comp.npy",(T*)h.comps, h.ni,    4, 4, 2 ) ;
    NP::Write(base, name,"ll.npy",  (T*)h.lls  , h.ni, N, 4, 4, 2 ) ;

    // use manual way for _arts so can set metadata
    NP* _art = NP::Make<T>( h.ni, 4, 4 );
    _art->read2( (T*)h.arts ); 
    _art->set_meta<std::string>("title", ti); 
    _art->set_meta<std::string>("brief", br); 
    _art->set_meta<std::string>("name", name); 
    _art->set_meta<std::string>("label", label); 
    _art->set_meta<T>("wl", h.wl); 
    _art->save(base, name, "art.npy" ); 

    NP::Write(base, name, "spec.npy", (T*)spec.data(), N, 4 ) ; 

}
#endif

