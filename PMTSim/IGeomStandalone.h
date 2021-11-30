#pragma once

class G4LogicalVolume ; 
class G4PVPlacement ;
class G4VSolid ; 

struct IGeomStandalone
{
    virtual G4LogicalVolume* getLV(const char* name) = 0 ;
    virtual G4PVPlacement*   getPV(const char* name) = 0 ;
    virtual G4VSolid*        getSolid(const char* name) = 0 ; 

    static bool StartsWithPrefix(const char* name, const char* prefix); 

}; 


