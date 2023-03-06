// ./PMTSimParamDataTest.sh 

#include <iostream>

#include <CLHEP/Units/SystemOfUnits.h>
#include <CLHEP/Units/PhysicalConstants.h>
#include "PMTSimParamSvc/PMTSimParamData.h"
#include "PMTSimParamSvc/_PMTSimParamData.h"
#include "Geometry/PMTCategory.h"

#include "ssys.h"


void test_get_pmtid_qe(const PMTSimParamData& d )
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

void test_get_pmtcat(const PMTSimParamData& d )
{
    int pcat = -2 ; 
  
    for(int i=0 ; i < 300000 ; i++)
    {
        int count = d.get_pmtid_count(i);  
        if( count == 0 ) continue ; 

        int cat0 = d.get_pmtcat(i) ; 
        int cat1 = d.get_pmtcat_slowly(i) ; 

        assert( cat0 == cat1 ); 

        int cat = cat0 ;  
        bool valid = PMTCategory::IsValid(cat) ; 
        const char* catname = PMTCategory::Name( cat ) ; 

        if( cat != pcat ) std::cout 
            << " i " << std::setw(7) << i 
            << " count " << std::setw(3) << count 
            << " cat0 " << std::setw(7) << cat0 
            << " cat1 " << std::setw(7) << cat1 
            << " valid " << ( valid ? "Y" : "N" )
            << " catname " << ( catname ? catname : "-" )
            << std::endl 
            ;

        pcat = cat ; 
    }
}



int main()
{
    PMTSimParamData* d = new PMTSimParamData ; 
    _PMTSimParamData::Load(*d, "$PMTSimParamData_BASE/PMTSimParamData") ; 

    std::cout << d->desc() << d->descTotal() << *d ; 

    /*

    test_get_pmtid_qe(*d); 
    */

    test_get_pmtcat(*d); 


    return 0 ; 
}  



