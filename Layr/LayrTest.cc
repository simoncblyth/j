/**
LayrTest.cc
=============

DONE: integrated with JPMT.h so can make realistic plots 

Currently gpu scanning is populating the StackSpec on CPU 
using NP interpolation and then that gets passed by value 
into the kernel launch. 

TODO: getting JPMT.h info accessible on GPU

* qudarap/QPMT.hh/qpmt.h  has done most of this : needs integrating 

**/

#include "sdomain.h"
#include "LayrTest.h"
#include "JPMT.h"

template<typename T, int N>
void test_scan_(const JPMT& jpmt, int wavelength, int pmtcat)
{
    T wavelength_nm = wavelength ; 

    const char* pmtcat_label = jpmt.get_pmtcat(pmtcat) ; 
    std::cout << " pmtcat " << pmtcat << " pmtcat_label " << pmtcat_label << std::endl ;  

    StackSpec<T,N> spec = jpmt.get<T,N>(pmtcat, wavelength_nm ) ; 

    std::cout << spec << std::endl ; 

    int ni = 900 ; 

    LayrTest<T,N> t0(ni, wavelength_nm, pmtcat_label) ; 
    t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
    std::cout << " WITH_THRUST " << std::endl ; 
    LayrTest<T,N> t1(ni, wavelength_nm, pmtcat_label ) ; 
    t1.scan_gpu(spec) ;
#else
    std::cout << " not-WITH_THRUST skip gpu scan " << std::endl ; 
#endif
}


template<int N>
void test_scan(const JPMT& jpmt, int wavelength, int pmtcat)
{
    test_scan_<double,N>(jpmt, wavelength, pmtcat ); 
    test_scan_<float,N>( jpmt, wavelength, pmtcat ); 
}

int main(int argc, char** argv)
{
    JPMT jpmt ; 
    std::cout << jpmt.desc() << std::endl ; 

    int mode = U::GetEnvInt("LAYRTEST_MODE", 4) ; 
    int wl = U::GetEnvInt("LAYRTEST_WL", 440) ; 
    const char* cat = U::GetEnv("LAYRTEST_PMTCAT", JPMT::_NNVTQ ); 
    int pmtcat = JPMT::FindCat(cat); 

    switch(mode)
    {
        case 4: test_scan<4>( jpmt, wl, pmtcat );  break ; 
        case 2: test_scan<2>( jpmt, wl, pmtcat );  break ; 
    }

    return 0 ; 
}
