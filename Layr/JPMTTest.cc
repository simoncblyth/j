/**
JPMTTest.cc
==================

Usage::

    ./JPMTTest.sh 

**/


#include "sdomain.h" // needed for hc_eVnm used by JPMT::get
#include "Layr.h"    // needed for FOR StackSpec
#include "JPMT.h"

const char* FOLD = "/tmp/JPMTTest" ; 


void test_FindCat20()
{
    int pmtcat_0 = JPMT::FindCatLPMT(JPMT::_HAMA) ; 
    assert( pmtcat_0 == JPMT::HAMA ); 

    int pmtcat_1 = JPMT::FindCatLPMT(JPMT::_NNVT) ; 
    assert( pmtcat_1 == JPMT::NNVT ); 

    int pmtcat_2 = JPMT::FindCatLPMT(JPMT::_NNVTQ) ; 
    assert( pmtcat_2 == JPMT::NNVTQ ); 

    int pmtcat_3 = JPMT::FindCatLPMT("other") ; 
    assert( pmtcat_3 == -1 ); 
}

void test_JPMT()
{
    JPMT jpmt ; 
    std::cout << jpmt.desc() << std::endl ; 
    jpmt.save(FOLD); 

    int pmtcat = JPMT::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double,4> spec = jpmt.get<double,4>(pmtcat, wavelength_nm); 
        std::cout << "spec" << std::endl << spec << std::endl ; 
    }
}


void test_JPMT_get_stackspec()
{
    JPMT jpmt ; 
    C4IPMTAccessor* ipmt = dynamic_cast<C4IPMTAccessor*>(&jpmt) ; 
   
    std::cout << "test_JPMT_get_stackspec typename " << ipmt->get_typename() << std::endl ; 

    std::array<double, 16> aa ; 
    int pmtcat = 0 ; 
    double energy_eV = 10. ; 
    ipmt->get_stackspec( aa, pmtcat, energy_eV ); 

    std::cout << " aa " << aa ; 
}


int main(int argc, char** argv)
{
    /*
    test_FindCat20(); 
    test_JPMT(); 
    test_JPMT_get_stackspec(); 
    */
    test_JPMT(); 

    return 0 ; 
}



