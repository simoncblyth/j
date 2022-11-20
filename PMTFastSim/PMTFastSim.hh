#pragma once

#include <vector>
#include <string>
#include <array>

struct NP ; 
class G4VSolid ; 
class G4LogicalVolume ; 
class G4VPhysicalVolume ; 

struct DetectorConstruction ; 

class HamamatsuR12860PMTManager ; 
class NNVTMCPPMTManager ; 
class HamamatsuMaskManager ; 
class NNVTMaskManager ; 
class LowerChimney ; 
class junoPMTOpticalModel ; 

struct IGeomManager ; 

#include "PMTFASTSIM_API_EXPORT.hh"

struct PMTFASTSIM_API PMTFastSim
{
    static int LEVEL ; 
    static void SetEnvironmentSwitches(const char* name); 
    static PMTFastSim* INSTANCE ; 
    static PMTFastSim* Get(); 

    static const char* HAMA ; 
    static const char* NNVT ; 

    static const char* HMSK ; 
    static const char* NMSK ; 
    static const char* LCHI ; 

    static const std::string HMSK_STR ;  
    static const std::string NMSK_STR ;  
    static const std::string LCHI_STR ;  

    static bool StartsWithPrefix(const char* name, const char* prefix) ; 
    static bool Contains(        const char* name, const char* sub) ; 

    static G4LogicalVolume*   GetLV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name, std::vector<double>* tr, std::vector<G4VSolid*>* solids ); 
    static junoPMTOpticalModel* GetPMTOpticalModel(const char* name); 


    bool                       verbose ; 
    DetectorConstruction*      m_dc ;   
    HamamatsuR12860PMTManager* m_hama ; 
    NNVTMCPPMTManager*         m_nnvt ; 
    HamamatsuMaskManager*      m_hmsk ; 
    NNVTMaskManager*           m_nmsk ; 
    LowerChimney*              m_lchi ; 

    static bool HasManagerPrefix( const char* name ); 
    IGeomManager* getManager(const char* name); 

    PMTFastSim(); 
    void init(); 

    static const int NAME_OFFSET ; 
    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    junoPMTOpticalModel* getPMTOpticalModel(const char* name) ; 

    static const char* Name(const char* prefix, int nx, int ny, int nz, const char* suffix); 
    static G4VPhysicalVolume*   WrapLVGrid( G4LogicalVolume* lv, int nx, int ny, int nz  ); 
    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static void Extract( std::vector<long>& vals, const char* s ); 
};



