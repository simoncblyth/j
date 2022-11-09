/**
JPMTTest.cc
==================

Usage::

    ./JPMTTest.sh 

**/


#include "sdomain.h" // needed for hc_eVnm used by JPMT::get
#include "Layr.h"    // needed for FOR StackSpec
#include "JPMT.h"

void test_JPMT()
{
    JPMT jp ; 
    std::cout << jp.desc() << std::endl ; 
    jp.save("/tmp/JPMTTest"); 

    int pmtcat = JPMT::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double> spec = jp.get(pmtcat, wavelength_nm); 
        std::cout << "spec" << std::endl << spec << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_JPMT(); 
    return 0 ; 
}



