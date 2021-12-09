#pragma once

/**
IGeomManager
===============

Formerly named IGeomStandalone, but renamed as this simple
protocol base can be useful beyond just PMTSIM_STANDALONE tests.
The below geometry providing managers are IGeomManager 
when they are compiled with the PMTSIM_STANDALONE switch::

    HamamatsuR12860PMTManager
    NNVTMCPPMTManager

**/


class G4LogicalVolume ; 
class G4PVPlacement ;
class G4VSolid ; 

struct IGeomManager
{
    virtual G4LogicalVolume* getLV(const char* name) = 0 ;
    virtual G4PVPlacement*   getPV(const char* name) = 0 ;
    virtual G4VSolid*        getSolid(const char* name) = 0 ; 
}; 


