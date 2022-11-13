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

template<typename T>
void test_scan(const JPMT& pmt, int wavelength, int pmtcat)
{
    T wavelength_nm = wavelength ; 

    const char* pmtcat_label = pmtcat == -1 ? "EGet" :  pmt.get_pmtcat(pmtcat) ; 
    std::cout << " pmtcat " << pmtcat << " pmtcat_label " << pmtcat_label << std::endl ;  

    StackSpec<T> spec( pmtcat == -1 ? StackSpec<T>::EGet() : pmt.get(pmtcat, wavelength_nm ) ); 
    std::cout << spec << std::endl ; 

    int ni = 900 ; 

    LayrTest<T,4> t0(ni, wavelength_nm, pmtcat_label) ; 
    t0.scan_cpu(spec) ;

#ifdef WITH_THRUST
    std::cout << " WITH_THRUST " << std::endl ; 
    LayrTest<T,4> t1(ni, wavelength_nm, pmtcat_label ) ; 
    t1.scan_gpu(spec) ;
#else
    std::cout << " not-WITH_THRUST skip gpu scan " << std::endl ; 
#endif
}

int main(int argc, char** argv)
{
    JPMT pmt ; 
    std::cout << pmt.desc() << std::endl ; 

    int wl = U::GetEnvInt("LAYRTEST_WL", 440) ; 
    const char* cat = U::GetEnv("LAYRTEST_PMTCAT", JPMT::_NNVTQ ); 
    int pmtcat = JPMT::FindCat(cat); 

    test_scan<double>(pmt, wl, pmtcat ); 
    test_scan<float>( pmt, wl, pmtcat ); 

    return 0 ; 
}
