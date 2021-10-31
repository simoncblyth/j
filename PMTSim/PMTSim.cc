#include <iostream>

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

G4VSolid* PMTSim::GetSolid(const char* name, double thickness, char mode) // static
{
    Hamamatsu_R12860_PMTSolid* pmtsolid_maker = new Hamamatsu_R12860_PMTSolid(); 
    std::cout << " pmtsolid_maker " << pmtsolid_maker << std::endl ; 
    G4String solidname = name ; 
    G4VSolid* solid = pmtsolid_maker->GetSolid(solidname, thickness, mode);  
    return solid ; 
}

 


