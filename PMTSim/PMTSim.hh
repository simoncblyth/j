#pragma once

class G4VSolid ; 
class G4LogicalVolume ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static G4VSolid* GetSolid(     const char* name="PMTSim_Z"); 
    static G4VSolid* GetZCutSolid( const char* name="PMTSim_Z", double zcut=-350. ); 
    static G4LogicalVolume* GetLV(const char* name); 

};



