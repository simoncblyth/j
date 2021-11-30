#pragma once

/**
IGeomStandalone
=================

The below geometry providing managers are IGeomStandalone 
when they are compiled with the STANDALONE switch::

    HamamatsuR12860PMTManager
    NNVTMCPPMTManager

**/


class G4LogicalVolume ; 
class G4PVPlacement ;
class G4VSolid ; 

struct IGeomStandalone
{
    virtual G4LogicalVolume* getLV(const char* name) = 0 ;
    virtual G4PVPlacement*   getPV(const char* name) = 0 ;
    virtual G4VSolid*        getSolid(const char* name) = 0 ; 
}; 


