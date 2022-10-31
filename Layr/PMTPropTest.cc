/**
PMTPropTest.cc
==================

Usage::

    ./PMTPropTest.sh 

**/

#include "Layr.h"
#include "sdomain.h"
#include "NPFold.h"
#include "PMTProp.h"

void test_PMTProp()
{
    PMTProp pp ; 
    std::cout << pp.desc() << std::endl ; 
    pp.save("/tmp/PMTPropTest"); 

    int pmtcat = PMTProp::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double> spec = pp.get(pmtcat, wavelength_nm); 
        std::cout << "spec" << std::endl << spec << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_PMTProp(); 
    return 0 ; 
}



