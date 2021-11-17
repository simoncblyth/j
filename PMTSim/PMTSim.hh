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

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static void SetEnvironmentSwitches(const char* name); 

    static G4VSolid* GetSolid(const char* name); 

    static G4VSolid* GetSolid_(const char* name); 
    static G4VSolid* GetDebugSolid(const char* name); 
    static G4VSolid* GetMakerSolid(const char* name); 
    static G4VSolid* GetManagerSolid(const char* name); 

    static bool IsDebugSolid(const char* qname)  ; 
    static char* itoa_( const char* fmt, int i ); 
    static char* ijtoa_( const char* fmt, int i, int j ); 
    static bool StartsWithPrefix(const char* name, const char* prefix) ; 
    static G4VSolid* Old_GetMakerSolid(const char* name); 

    static G4VPhysicalVolume* GetPV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name,  std::vector<double>* tr, std::vector<G4VSolid*>* solids); 

    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* path ); 
    static void SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* fold, const char* name ); 
    static NP* MakeArray( std::vector<double>* tr, std::vector<G4VSolid*>* solids ); 
    static void DumpTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* names, const char* msg ); 

    static void Traverse(const G4VPhysicalVolume* const pv, std::vector<double>* tr, std::vector<G4VSolid*>* names ); 
    static void Traverse_r(const G4VPhysicalVolume* const pv, int depth, std::vector<double>* tr, std::vector<G4VSolid*>* names); 
    static void GetObjectTransform(std::array<double, 16>& a, const G4VPhysicalVolume* const pv); 
    static void DumpSolids(); 

    bool verbose ; 
    DetectorConstruction* dc ;   
    HamamatsuR12860PMTManager* ham ; 

    PMTSim(const char* name=""); 
    void init(const char* name); 

    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    G4VSolid*           getSolid(const char* name) ;


    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static void Extract( std::vector<long>& vals, const char* s ); 
};



