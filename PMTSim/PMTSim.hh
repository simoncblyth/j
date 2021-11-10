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
    DetectorConstruction* dc ;   
    HamamatsuR12860PMTManager* ham ; 

    PMTSim(const char* name="PMTSim"); 

    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    const G4VSolid*     getSolid(const char* name) ;

    const G4VSolid*     getSolidPfx(const char* name) ;

    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static const G4VSolid*      GetMakerSolid(const char* name); 
    static void Extract( std::vector<long>& vals, const char* s ); 
};



