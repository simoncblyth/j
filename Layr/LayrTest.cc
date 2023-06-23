/**
LayrTest.cc : based on JPMT.h and Layr.h 
===========================================

JPMT.h with its partial PMT info is now superceeded 
by SPMT.h with the full PMT info from PMTSimParamData/NPFold

Currently gpu scanning is populating the StackSpec on CPU 
using NP interpolation and then that gets passed by value 
into the kernel launch. 

**/

#include "sdomain.h"
#include "LayrTest.h"
#include "JPMT.h"

/**
test_scan_
-------------

1. Gets StackSpec from JPMT instance and uses that in a CPU scan
   provided by the t0 LayrTest instance.  

2. When compiled WITH_THRUST also does GPU scan using 
   a separate t1 LayrTest instance. 

**/

template<typename T, int N>
void test_scan_(const JPMT& jpmt, int wavelength, int pmtcat)
{
    T wavelength_nm = wavelength ; 

    const char* pmtcat_name = jpmt.get_pmtcat_name(pmtcat) ; 
    std::cout << " pmtcat " << pmtcat << " pmtcat_name " << pmtcat_name << std::endl ;  

    StackSpec<T,N> spec = jpmt.get<T,N>(pmtcat, wavelength_nm ) ; 

    std::cout << spec << std::endl ; 

    int ni = 900 ; 

    LayrTest<T,N> t0(ni, wavelength_nm, pmtcat_name) ; 
    t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
    std::cout << " WITH_THRUST " << std::endl ; 
    LayrTest<T,N> t1(ni, wavelength_nm, pmtcat_name ) ; 
    t1.scan_gpu(spec) ;
#else
    std::cout << " not-WITH_THRUST skip gpu scan " << std::endl ; 
#endif
}

/**
test_scan
----------

Invokes test_scan_ with double then float types. 
Hence when compiled WITH_THRUST four scans are made and saved. 

**/

template<int N>
void test_scan(const JPMT& jpmt, int wavelength, int pmtcat)
{
    test_scan_<double,N>(jpmt, wavelength, pmtcat ); 
    test_scan_<float,N>( jpmt, wavelength, pmtcat ); 
}

/**
test_scans
-------------

1. instanciates JPMT reading partial props (pmtcat level only, not pmtid level) 
   from NP_PROP_BASE

2. invokes test_scan<4> 

**/


void test_scans()
{
    JPMT jpmt ; 
    std::cout << jpmt.desc() << std::endl ; 

    int mode = U::GetEnvInt("LAYRTEST_MODE", 4) ; 
    int wl = U::GetEnvInt("LAYRTEST_WL", 440) ; 
    const char* cat = U::GetEnv("LAYRTEST_PMTCAT", JPMT::_NNVTQ ); 
    int pmtcat = JPMT::FindCatLPMT(cat); 

    switch(mode)
    {
        case 4: test_scan<4>( jpmt, wl, pmtcat );  break ; 
        //case 2: test_scan<2>( jpmt, wl, pmtcat );  break ;   // missing symbol link errors WITH_THRUST
    }
}

int main(int argc, char** argv)
{
    test_scans(); 
    return 0 ; 
}
