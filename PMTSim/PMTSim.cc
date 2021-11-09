#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "DetectorConstruction.hh"
#include "PMTSim.hh"

G4LogicalVolume* PMTSim::GetLV(const char* name)  // static
{
    HamamatsuR12860PMTManager* mgr = new HamamatsuR12860PMTManager(name) ; 
    std::cout << "PMTSim::GetLV mgr " << mgr << std::endl ; 
    G4LogicalVolume* lv = mgr->getLV(); 
    std::cout << "PMTSim::GetLV lv " << lv << std::endl ; 
    return lv ; 
}

G4VPhysicalVolume* PMTSim::GetPV(const char* name) // static
{
    DetectorConstruction* dc = new DetectorConstruction ;   // creates many G4Material and G4OpticalSurface  
    assert( dc ); 

    G4LogicalVolume* lv = GetLV(name); 

    G4String pName = lv->GetName(); 
    pName += "_phys " ; 

    G4RotationMatrix* pRot = nullptr ; 
    G4ThreeVector     tlate(0.,0.,0.);
    G4LogicalVolume*  pMotherLogical = nullptr ; 
    G4bool pMany_unused = false ; 
    G4int pCopyNo = 0 ; 

    G4VPhysicalVolume* pv = new G4PVPlacement(pRot, tlate, lv, pName, pMotherLogical, pMany_unused, pCopyNo ); 
    std::cout << "PMTSim::GetPV pv " << pv << std::endl ; 
    return pv ; 
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




/**
PMTSim::Extract
----------------

Parse string converting groups of 0123456789+- chars into long integers.  

**/

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

