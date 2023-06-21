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


template<int N>
void test_scan(const JPMT& jpmt, int wavelength, int pmtcat)
{
    test_scan_<double,N>(jpmt, wavelength, pmtcat ); 
    test_scan_<float,N>( jpmt, wavelength, pmtcat ); 
}


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

void test_StackSpec_serialize()
{
    StackSpec<double, 4> ss0 ;  
    ss0.ls[0] = {0.50, 0.51, 0.52, 0.0 } ; 
    ss0.ls[1] = {0.60, 0.61, 0.62, 0.0 } ; 
    ss0.ls[2] = {0.70, 0.71, 0.72, 0.0 } ; 
    ss0.ls[3] = {0.80, 0.81, 0.82, 0.0 } ; 
    std::cout << " ss0 " << ss0 << std::endl ; 

    std::array<double, 16> aa0 ; 
    ss0.serialize(aa0); 
    std::cout << " aa0 " << aa0 ; 

    StackSpec<double, 4> ss1 ; 
    ss1.import(aa0); 
    std::cout << " ss1 " << ss1 << std::endl ; 
}

void test_StackSpec_is_equal()
{
    StackSpec<double, 4> ss0 ;  
    ss0.ls[0] = {0.50, 0.51, 0.52, 0.0 } ; 
    ss0.ls[1] = {0.60, 0.61, 0.62, 0.0 } ; 
    ss0.ls[2] = {0.70, 0.71, 0.72, 0.0 } ; 
    ss0.ls[3] = {0.80, 0.81, 0.82, 0.0 } ; 
    std::cout << " ss0 " << ss0 << std::endl ; 

    StackSpec<double, 4> ss1(ss0); 
    std::cout << " ss1 " << ss1 << std::endl ; 

    ss1.ls[3].ni = 0.99 ; 


    bool eq = ss0.is_equal(ss1) ; 
    std::cout << " is_equal " << eq << std::endl ; 

    std::cout << ss0.desc_compare(ss1) << std::endl ; 
}


int main(int argc, char** argv)
{
    /*
    test_scans(); 
    test_StackSpec_serialize(); 
    test_StackSpec_is_equal(); 
    */
    test_scans(); 

    return 0 ; 
}
