#include <iostream>
#include <cstdlib>
#include <cstring>

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "PMTSim.hh"

G4LogicalVolume* PMTSim::GetLV(const char* name)  // static
{
    HamamatsuR12860PMTManager* mgr = new HamamatsuR12860PMTManager(name) ; 
    std::cout << " mgr " << mgr << std::endl ; 
    G4LogicalVolume* lv = mgr->getLV(); 
    std::cout << " lv " << lv << std::endl ; 
    return lv ; 
}

const G4VSolid* PMTSim::GetSolid(const char* name) // static
{
    Hamamatsu_R12860_PMTSolid* pmtsolid_maker = new Hamamatsu_R12860_PMTSolid(); 

    G4String solidname = name ; 
    double thickness = 0. ; 
    char mode = ' '; 
    std::vector<long> vals ; 
    Extract( vals, name ); 

    const G4VSolid* solid = nullptr ; 
    if(vals.size() > 0)
    {
        double zcut = vals[0] ; 
        std::cout << "[ PMTSim::GetSolid extracted zcut " << zcut << " from name " << name  << " mode" << mode << std::endl ; 
        solid = pmtsolid_maker->GetZCutSolid(solidname, zcut, thickness, mode);  
        std::cout << "] PMTSim::GetSolid extracted zcut " << zcut << " from name " << name << " mode " << mode << std::endl ; 
    }
    else
    {
        std::cout << "[ PMTSim::GetSolid without zcut (as no zcut value extracted from name) " << name << std::endl ; 
        solid = pmtsolid_maker->GetSolid(solidname, thickness, mode);  
        std::cout << "] PMTSim::GetSolid without zcut (as no zcut value extracted from name) " << name << std::endl ; 
    }
    return solid ; 
}


void PMTSim::Extract( std::vector<long>& vals, const char* s )  // static
{
    char* s0 = strdup(s); 
    char* p = s0 ; 
    while (*p) 
    {   
        if( (*p >= '0' && *p <= '9') || *p == '+' || *p == '-') vals.push_back(strtol(p, &p, 10)) ; 
        else p++ ;
    }   
    free(s0); 
}

