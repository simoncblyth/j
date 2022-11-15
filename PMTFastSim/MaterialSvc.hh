#pragma once
/**
MaterialSvc.hh
================

Standalone access to material properties, see::

   jcv IMCParamsSvc
       protocal base using boost::tuple

   jcv MCParamsFileSvc
   jcv LSExpDetectorConstructionMaterial
   jcv LSExpDetectorConstruction   helper_mpt 

**/

class G4MaterialPropertiesTable ; 
#include "G4MaterialPropertyVector.hh" // typedef
#include <string>
#include "IMCParamsSvc.hh"

#include "PMTFASTSIM_API_EXPORT.hh"
struct PMTFASTSIM_API MaterialSvc : public IMCParamsSvc
{
    bool Get(const std::string& param, vec_d2d& props) ;
    bool Get(const std::string& param, vec_s2d& props) ;
    bool Get(const std::string& param, map_s2d& props) ; 

    static const char* GetPath(const char* propPath);
    static G4MaterialPropertyVector* GetMPV(const char* path, bool dump=false); 
    static void AddProperty(G4MaterialPropertiesTable* MPT, const char* propName, const char* propPath); 

};
