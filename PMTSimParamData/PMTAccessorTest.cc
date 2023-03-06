// ./PMTAccessorTest.sh 

#include <iostream>

#include <CLHEP/Units/SystemOfUnits.h>
#include <CLHEP/Units/PhysicalConstants.h>
#include "ssys.h"

#include "Geometry/PMTCategory.h"
#include "PMTSimParamSvc/PMTAccessor.h"


void test_get_pmtid_qe(const IPMTAccessor& d )
{
    int pmtid = ssys::getenvint("PMTID", 0)  ; 

    double en0 = 1.55 ; 
    double en1 = 15.5 ; 
    const int N = 100 ; 

    for(int i=0 ; i < N ; i++)
    {
        double en = en0 + (en1-en0)*(double(i)/(N-1)) ;  
        double energy = en*CLHEP::eV ; 
        double wavelength = CLHEP::twopi*CLHEP::hbarc/energy;
        double qe = d.get_pmtid_qe(pmtid, energy);   

        if(qe > 1e-3 ) std::cout
            << " i " << std::setw(3) << i 
            << " PMTID " << std::setw(8) << pmtid 
            << " energy/eV " << std::setw(10) << std::fixed << std::setprecision(4) << energy/CLHEP::eV
            << " wavelength/nm " << std::setw(10) << std::fixed << std::setprecision(4) << wavelength/CLHEP::nm
            << " qe " << std::setw(10) << std::fixed << std::setprecision(4) << qe
            << std::endl 
            ;
    }
}

void test_get_pmtid_qe_max(const IPMTAccessor& d )
{
    int num_lpmt = d.get_num_lpmt() ; 
    std::cout << " num_lpmt " << num_lpmt << std::endl ; 

    const int N = 1000 ; 
    double en0 = 1.55 ; 
    double en1 = 15.5 ; 
    
    NP* a = NP::Make<int>( num_lpmt, 2) ; 
    NP* b = NP::Make<double>( num_lpmt, 4) ; 

    NPFold* fold = new NPFold ; 
    fold->add("a", a); 
    fold->add("b", b); 

    int* aa = a->values<int>(); 
    double* bb = b->values<double>(); 

    for(int i=0 ; i < num_lpmt ;  i++)
    {
        int pmtid = i ; 
        int cat = d.get_pmtcat(pmtid) ; 
        double scale = d.get_qescale(pmtid) ; 


        aa[2*i+0] = pmtid ; 
        aa[2*i+1] = cat ; 

        const char* catname = PMTCategory::Name(cat) ; 

        double qe_max = 0. ; 
        double wl_max = 0. ; 
        double en_max = 0. ; 

        for(int j=0 ; j < N ; j++)
        {
            double en = en0 + (en1-en0)*(double(j)/(N-1)) ;  
            double energy = en*CLHEP::eV ; 
            double wavelength = CLHEP::twopi*CLHEP::hbarc/energy;
            double wl = wavelength/CLHEP::nm ;  

            double qe = d.get_pmtid_qe(pmtid, energy);   

            if( qe > qe_max ) 
            {
                qe_max = qe ; 
                wl_max = wl ; 
                en_max = en ; 
            }
        }

        bb[4*i+0] = qe_max ; 
        bb[4*i+1] = scale ; 
        bb[4*i+2] = wl_max ; 
        bb[4*i+3] = en_max ; 

        std::cout 
            << " pmtid "   << std::setw(6) << pmtid 
            << " scale "   << std::setw(10) << std::fixed << std::setprecision(4) << scale
            << " cat "     << std::setw(6) << cat 
            << " catname " << std::setw(20) << ( catname ? catname : "-" )
            << " qe_max "  << std::setw(10) << std::fixed << std::setprecision(4) << qe_max
            << " wl_max "  << std::setw(10) << std::fixed << std::setprecision(4) << wl_max
            << " en_max "  << std::setw(10) << std::fixed << std::setprecision(4) << en_max
            << std::endl
            ;
    }

    fold->save("$FOLD/test_get_pmtid_qe_max"); 
}




void test_get_pmtcat( const IPMTAccessor& d )
{
    int pcat = -2 ; 
    for(int i=0 ; i < 20000 ; i++)
    {
        int cat = d.get_pmtcat(i) ; 
        const char* catname = PMTCategory::Name(cat) ; 

        if(cat != pcat) std::cout 
            << " i " << std::setw(6) << i 
            << " cat " << std::setw(6) << cat 
            << " catname " << std::setw(20) << ( catname ? catname : "-" )
            << std::endl
            ;

        pcat = cat ; 
    }
}

int main()
{
    const IPMTAccessor* ip = PMTAccessor::Load("$PMTSimParamData_BASE/PMTSimParamData") ; 
    /*
    test_get_pmtcat(*ip); 
    test_get_pmtid_qe(*ip); 
    */

    test_get_pmtid_qe_max(*ip); 


    return 0 ; 
}  



