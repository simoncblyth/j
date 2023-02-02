#include <iostream>
#include <iomanip>
#include <CLHEP/Units/SystemOfUnits.h>

#include "SniperKernel/TopTask.h"
#include "SniperKernel/Sniper.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/Task.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"

#include "Geometry/PMTParamSvc.h"
#include "src/PMTSimParamSvc.h"
#include "src/MCParamsFileSvc.hh"  

IPMTSimParamSvc* Get_IPMTSimParamSvc()
{
    Task* top  = new TopTask("top"); 

    Sniper::loadDll("libGeometry.so"); 
    Sniper::loadDll("libMCParamsSvc.so"); 
    Sniper::loadDll("libPMTSimParamSvc.so"); 

    std::cout << " Sniper::dlls() " << Sniper::dlls() << std::endl ; 

    PMTParamSvc*     pps = dynamic_cast<PMTParamSvc*>(top->createSvc("PMTParamSvc")); 
    pps->initialize(); 

    MCParamsFileSvc* mpfs = dynamic_cast<MCParamsFileSvc*>(top->createSvc("MCParamsFileSvc/MCParamsSvc"));
    mpfs->initialize(); 

    PMTSimParamSvc* psps = dynamic_cast<PMTSimParamSvc*>(top->createSvc("PMTSimParamSvc")); 
    psps->initialize(); 

    SniperPtr<IPMTSimParamSvc> psps_ptr(*top, "PMTSimParamSvc"); 

    if(psps_ptr.invalid()) 
    {
        std::cout << "invalid" << std::endl ;  
        return nullptr ; 
    }

    IPMTSimParamSvc* ipsps = psps_ptr.data(); 
    return ipsps ; 
}

int main(int, char** argv)
{
    std::cout << argv[0] << std::endl ; 

    IPMTSimParamSvc* ipsps = Get_IPMTSimParamSvc(); 

    std::cout << " ipsps " << ipsps << std::endl ; 

    if(ipsps == nullptr) return 1 ; 

    const std::vector<int>& all_pmtID = ipsps->get_all_pmtID() ; 

    int num_pmt = all_pmtID.size(); 
    
    std::cout << " num_pmt " << num_pmt << std::endl ; 

    double energy = 5.0*CLHEP::eV ; 

    for(int i=0 ; i < num_pmt ; i++)
    {
        if(i % 1000 != 0) continue ; 
        int pmtid = all_pmtID[i]; 

        double gain = ipsps->get_gain(pmtid) ; 
        double qe   = ipsps->get_pmtid_qe( pmtid, energy );   

        std::cout
            << " pmtid : " << std::setw(8) << pmtid 
            << " gain : " << std::setw(10) << std::fixed << std::setprecision(3)  << gain
            << " qe : " << std::setw(10) << std::fixed << std::setprecision(3)  << qe
            << std::endl ;  
    }

    return 0 ; 
}
