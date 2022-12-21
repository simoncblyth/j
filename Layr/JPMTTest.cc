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
    int pmtcat_0 = JPMT::FindCat20(JPMT::_HAMA) ; 
    assert( pmtcat_0 == JPMT::HAMA ); 

    int pmtcat_1 = JPMT::FindCat20(JPMT::_NNVT) ; 
    assert( pmtcat_1 == JPMT::NNVT ); 

    int pmtcat_2 = JPMT::FindCat20(JPMT::_NNVTQ) ; 
    assert( pmtcat_2 == JPMT::NNVTQ ); 

    int pmtcat_3 = JPMT::FindCat20("other") ; 
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


int main(int argc, char** argv)
{
    /*
    test_FindCat20(); 
    */
    test_JPMT(); 

    return 0 ; 
}



