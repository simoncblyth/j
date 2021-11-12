#pragma once

#include <vector>
class G4VSolid ; 
class G4LogicalVolume ; 
class G4VPhysicalVolume ; 

struct DetectorConstruction ; 
class HamamatsuR12860PMTManager ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static const G4VSolid* GetSolid(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name); 

    static void Traverse(const G4VPhysicalVolume* const pv); 
    static void Traverse_r(const G4VPhysicalVolume* const pv, int depth); 
    static void DumpSolids(); 

    DetectorConstruction* dc ;   
    HamamatsuR12860PMTManager* ham ; 

    PMTSim(const char* name=""); 

    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    const G4VSolid*     getSolid(const char* name) ;

    const G4VSolid*     getSolidPfx(const char* name) ;

    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static const G4VSolid*      GetMakerSolid(const char* name); 
    static void Extract( std::vector<long>& vals, const char* s ); 
};



