/**
JPMTTest.cc
==================

Usage::

    ./JPMTTest.sh 

**/


#include "sdomain.h" // needed for hc_eVnm used by JPMT::get
#include "Layr.h"    // needed for FOR StackSpec
#include "JPMT.h"

void test_FindCat()
{
    int pmtcat_0 = JPMT::FindCat(JPMT::_HAMA) ; 
    assert( pmtcat_0 == JPMT::HAMA ); 

    int pmtcat_1 = JPMT::FindCat(JPMT::_NNVT) ; 
    assert( pmtcat_1 == JPMT::NNVT ); 

    int pmtcat_2 = JPMT::FindCat(JPMT::_NNVTQ) ; 
    assert( pmtcat_2 == JPMT::NNVTQ ); 

    int pmtcat_3 = JPMT::FindCat("other") ; 
    assert( pmtcat_3 == -1 ); 
}

void test_JPMT()
{
    JPMT jpmt ; 
    std::cout << jpmt.desc() << std::endl ; 
    jpmt.save("/tmp/JPMTTest"); 

    int pmtcat = JPMT::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double> spec = jpmt.get(pmtcat, wavelength_nm); 
        std::cout << "spec" << std::endl << spec << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_FindCat(); 
    //test_JPMT(); 
    return 0 ; 
}



