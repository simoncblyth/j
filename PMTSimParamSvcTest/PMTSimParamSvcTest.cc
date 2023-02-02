#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdlib>
#include <cassert>

#include <CLHEP/Units/SystemOfUnits.h>

#include "SniperKernel/TopTask.h"
#include "SniperKernel/Sniper.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/Task.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"

#include "Geometry/PMTParamSvc.h"

// The below includes need special include_directories setting in CMakeLists.txt 
// in order to grab from src directories.
//
// HMM : perhaps the interface should have initialize to avoid needing these headers ?

#include "src/PMTSimParamSvc.h"
#include "src/MCParamsFileSvc.hh"  


#include "NPFold.h"
#include "NP.hh"


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


NP* scan_di( std::function<double(int)> fn, const std::vector<int>& ii  )
{
    int ni = ii.size() ; 
    NP* a = NP::Make<double>( ni );
    double* aa = a->values<double>() ;    
    for(int i=0 ; i < ni ; i++) aa[i] = fn(ii[i]) ;
    return a ; 
}

NP* scan_did( std::function<double(int, double)> fn, const std::vector<int>& ii, const std::vector<double>& jj )
{
    int ni = ii.size() ; 
    int nj = jj.size() ; 
    NP* a = NP::Make<double>( ni, nj );
    double* aa = a->values<double>() ;    
    for(int i=0 ; i < ni ; i++) for(int j=0 ; j < nj ; j++) aa[i*nj+j] = fn(ii[i], jj[j]) ;
    return a ; 
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

    int num_energy = 100 ; 
    double en0 = 1.55*CLHEP::eV ; 
    double en1 = 15.5*CLHEP::eV ; 
    std::vector<double> energy(num_energy) ; 
    for(int j=0 ; j < num_energy ; j++)
    {
        double fr = double(j)/double(num_energy-1) ; 
        energy[j] = en0*(1.-fr) + en1*fr ;  
    }

    NPFold* fold = new NPFold ; 

    std::function<double(int, double)> _get_pmtid_qe         = std::bind( &IPMTSimParamSvc::get_pmtid_qe, ipsps, std::placeholders::_1, std::placeholders::_2 ) ; 
    std::function<double(int)>         _get_pmt_qe_scale     = std::bind( &IPMTSimParamSvc::get_pmt_qe_scale, ipsps, std::placeholders::_1 ) ; 
    std::function<double(int)>         _get_shape_qe_at420nm = std::bind( &IPMTSimParamSvc::get_shape_qe_at420nm, ipsps, std::placeholders::_1 ) ; 

    fold->add( "get_pmtid_qe",         scan_did(_get_pmtid_qe,         all_pmtID, energy ) ); 
    fold->add( "get_pmt_qe_scale",     scan_di( _get_pmt_qe_scale,     all_pmtID ) ); 
    fold->add( "get_shape_qe_at420nm", scan_di( _get_shape_qe_at420nm, all_pmtID ) ); 

    char* FOLD = getenv("FOLD"); 
    std::cout << " save to FOLD " << ( FOLD ? FOLD : "-" ) << std::endl;
    assert(FOLD); 
    fold->save(FOLD); 

    return 0 ; 
}
