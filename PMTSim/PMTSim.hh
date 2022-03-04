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

struct IGeomManager ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static void SetEnvironmentSwitches(const char* name); 

    static const char* PREFIX ; 
    static const char* HAMA ; 
    static const char* NNVT ; 

    static const char* HMSK ; 
    static const char* NMSK ; 
    static const char* LCHI ; 

    static const std::string HMSK_STR ;  
    static const std::string NMSK_STR ;  
    static const std::string LCHI_STR ;  


    static G4VSolid* GetSolid(const char* name); 

    static G4VSolid* Polycone(const char* name); 
    static G4VSolid* TwoTubsUnion(const char* name); 
    static G4VSolid* ThreeTubsUnion(const char* name); 
    static G4VSolid* TenTubsUnion(const char* name); 



    static G4VSolid* GetSolid_(const char* name); 
    static G4VSolid* GetDebugSolid(const char* name); 
    static G4VSolid* GetMakerSolid(const char* name); 
    static G4VSolid* GetManagerSolid(const char* name); 

    static bool IsDebugSolid(const char* qname)  ; 
    static char* itoa_( const char* fmt, int i ); 
    static char* ijtoa_( const char* fmt, int i, int j ); 

    static bool StartsWithPrefix(const char* name, const char* prefix) ; 
    static bool Contains(        const char* name, const char* sub) ; 

    static G4LogicalVolume*   GetLV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name,  std::vector<double>* tr, std::vector<G4VSolid*>* solids); 

    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* path ); 
    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* fold, const char* name ); 
    static NP* MakeArray( std::vector<double>* tr, std::vector<G4VSolid*>* solids ); 
    static void DumpTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* msg ); 

    static void Traverse(const G4VPhysicalVolume* const pv, std::vector<double>* tr, std::vector<G4VSolid*>* names ); 
    static void Traverse_r(const G4VPhysicalVolume* const pv, int depth, std::vector<double>* tr, std::vector<G4VSolid*>* names); 
    static bool IsIdentityRotation(const std::array<double, 16>& a, double epsilon ) ; 
    static void GetObjectTransform(std::array<double, 16>& a, const G4VPhysicalVolume* const pv); 
    static void DumpSolids(); 

    bool verbose ; 
    DetectorConstruction*      m_dc ;   

    HamamatsuR12860PMTManager* m_hama ; 
    NNVTMCPPMTManager*         m_nnvt ; 

    HamamatsuMaskManager*      m_hmsk ; 
    NNVTMaskManager*           m_nmsk ; 

    LowerChimney*              m_lchi ; 

    static bool HasManagerPrefix( const char* name ); 
    IGeomManager* getManager(const char* name); 

    PMTSim(); 
    void init(); 

    static const int NAME_OFFSET ; 
    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    G4VSolid*           getSolid(const char* name) ;

    static const char* Name(const char* prefix, int nx, int ny, int nz, const char* suffix); 
    static G4VPhysicalVolume*   WrapLVGrid( G4LogicalVolume* lv, int nx, int ny, int nz  ); 
    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static void Extract( std::vector<long>& vals, const char* s ); 
};



