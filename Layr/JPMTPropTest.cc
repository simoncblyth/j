/**
JPMTPropTest.cc
==================

Usage::

    ./JPMTPropTest.sh 

**/

#include "Layr.h"
#include "sdomain.h"
#include "JPMTProp.h"

void test_JPMTProp()
{
    JPMTProp pp ; 
    std::cout << pp.desc() << std::endl ; 
    pp.save("/tmp/JPMTPropTest"); 

    int pmtcat = JPMTProp::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double> spec = pp.get(pmtcat, wavelength_nm); 
        std::cout << "spec" << std::endl << spec << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_JPMTProp(); 
    return 0 ; 
}



