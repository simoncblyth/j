#pragma once

class G4VSolid ; 
class G4LogicalVolume ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static G4VSolid* GetSolid(const char* name="PMTSim"); 
    static G4LogicalVolume* GetLV(const char* name); 

};



