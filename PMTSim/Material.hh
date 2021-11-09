#pragma once
/**
Material.hh
============

Standalone access to material properties, see::

   jcv IMCParamsSvc
   jcv MCParamsFileSvc
   jcv LSExpDetectorConstructionMaterial
   jcv LSExpDetectorConstruction   helper_mpt 


**/

class G4MaterialPropertiesTable ; 
#include "G4MaterialPropertyVector.hh" // typedef
#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API Material

{
     static const char* GetPath(const char* propPath);
     static G4MaterialPropertyVector* GetMPV(const char* path, bool dump=false); 
     static void AddProperty(G4MaterialPropertiesTable* MPT, const char* propName, const char* propPath); 

};
