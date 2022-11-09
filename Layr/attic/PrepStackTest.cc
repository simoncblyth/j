
#include "Layr.h"
#include "NPFold.h"
#include "sdomain.h"
#include "PMTProp.h"
#include "PrepStack.h"

void test_PMTProp_vs_PrepStackSpec()
{
    PMTProp pp ; 
    std::cout << pp.desc() << std::endl ; 

    PrepStack ps(PMT::HAMA) ; 

    int pmtcat = PMTProp::HAMA ; 
    for(double wavelength_nm=400. ; wavelength_nm <= 800. ; wavelength_nm += 100. )
    {
        StackSpec<double> s0 = pp.get(pmtcat, wavelength_nm); 
        StackSpec<double> s1 = ps.get(wavelength_nm); 

        std::cout << "s0" << std::endl << s0 << std::endl ; 
        std::cout << "s1" << std::endl << s1 << std::endl ; 
    }
}

int main(int argc, char** argv)
{
    test_PMTProp_vs_PrepStackSpec(); 

    return 0 ; 
}



