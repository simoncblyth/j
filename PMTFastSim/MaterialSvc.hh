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



TODO : Follow PMTSimParamSvc/PMTSimParamData approach with MCParamsSvc/MCParamsData
-------------------------------------------------------------------------------------

Following the experience of pulling Data struct out of Services it is clear
that an analogous approach could easily be used with MCParamsSvc. 

The advantages are:

1. reduces risk of standalone running using different material properties to full running 
2. makes the grab part of the standard Opticks geometry translation and collection into SSim NPFold.  

+-------------------+-------------------------+-----------------+
| Service           |  Data Carrier           | Notes           |
+===================+=========================+=================+
| PMTSimParamSvc    |  PMTSimParamData        |                 |
+-------------------+-------------------------+-----------------+
| PMTParamSvc       |  PMTParamData           |                 |
+-------------------+-------------------------+-----------------+
| MCParamsSvc       |  MCParamsData           | NOT YET IMPL    |
+-------------------+-------------------------+-----------------+


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
