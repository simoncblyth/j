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
class Tub3inchPMTV3Manager ; 

class XJanchorConstruction ; 
class XJfixtureConstruction ; 

class SJCLSanchorConstruction ; 
class SJFixtureConstruction ;
class SJReceiverConstruction ;
class SJReceiverFasternConstruction ;

class FastenerAcrylicConstruction ;

struct IGeomManager ; 

#include "PMTSIM_API_EXPORT.hh"

struct PMTSIM_API PMTSim
{
    static int LEVEL ; 
    bool verbose ; 

#ifdef POM_DEBUG
    static NP*  ModelTrigger_Debug_Array(); 
    static void ModelTrigger_Debug_Save(const char* savedir); 
#endif
    static std::string OutputMessage(const char* msg, const std::string& out, const std::string& err, bool verbose ); 

    static void SetEnvironmentSwitches(const char* name); 

    static constexpr const char* HAMA = "hama" ; 
    static constexpr const char* NNVT = "nnvt" ; 
    static constexpr const char* HMSK = "hmsk" ; 
    static constexpr const char* NMSK = "nmsk" ; 
    static constexpr const char* LCHI = "lchi" ;  // lower chimney 
    static constexpr const char* TUB3 = "tub3" ;  

    static constexpr const char* XJAC = "xjac" ;  
    static constexpr const char* XJFC = "xjfc" ;  

    static constexpr const char* SJCL = "sjcl" ;  
    static constexpr const char* SJFX = "sjfx" ;  
    static constexpr const char* SJRC = "sjrc" ;  
    static constexpr const char* SJRF = "sjrf" ;  

    static constexpr const char* FACR = "facr" ; 

    const std::string HMSK_STR ;  
    const std::string NMSK_STR ;  
    const std::string LCHI_STR ;  
    const std::string TUB3_STR ;  

    const std::string XJAC_STR ;  
    const std::string XJFC_STR ;  

    const std::string SJCL_STR ;  
    const std::string SJFX_STR ;  
    const std::string SJRC_STR ;  
    const std::string SJRF_STR ;  

    const std::string FACR_STR ;  

    static G4VSolid* GetSolid();  // arg from GEOM envvar  
    static G4VSolid* GetSolid(const char* name); 
    static NP*       GetValues(const char* name); 

    static G4VSolid* Polycone(const char* name); 
    static G4VSolid* TwoTubsUnion(const char* name); 
    static G4VSolid* ThreeTubsUnion(const char* name); 
    static G4VSolid* TenTubsUnion(const char* name); 



    static G4VSolid* GetSolid_(const char* name); 
    static G4VSolid* GetDebugSolid(const char* name); 
    static G4VSolid* GetMakerSolid(const char* name); 
    static G4VSolid* GetManagerSolid(const char* name); 

    // avoid having to create the managers twice to get solid and value by keeping static notes
    static const char* LastManagerSolidName ; 
    static NP*         LastManagerSolidValues ; 
    static void        SetLastManagerSolid(const char* name, NP* values); 
    static const char* GetLastManagerSolidName() ; 
    static NP*         GetLastManagerSolidValues() ; 


    static NP* GetManagerValues(const char* name); 



    static bool IsDebugSolid(const char* qname)  ; 
    static char* itoa_( const char* fmt, int i ); 
    static char* ijtoa_( const char* fmt, int i, int j ); 

    static bool StartsWithPrefix(const char* name, const char* prefix) ; 
    static bool Contains(        const char* name, const char* sub) ; 

    static std::string        Desc(const char* name); 
    static G4LogicalVolume*   GetLV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name); 
    static G4VPhysicalVolume* GetPV(const char* name,  std::vector<double>* tr, std::vector<G4VSolid*>* solids); 

    DetectorConstruction*      m_dc ;   

    HamamatsuR12860PMTManager* m_hama ; 
    NNVTMCPPMTManager*         m_nnvt ; 

    HamamatsuMaskManager*      m_hmsk ; 
    NNVTMaskManager*           m_nmsk ; 

    LowerChimney*              m_lchi ; 
    Tub3inchPMTV3Manager*      m_tub3 ; 

    XJanchorConstruction*      m_xjac ; 
    XJfixtureConstruction*     m_xjfc ; 

    SJCLSanchorConstruction*        m_sjcl ; 
    SJFixtureConstruction*          m_sjfx ; 
    SJReceiverConstruction*         m_sjrc ; 
    SJReceiverFasternConstruction*  m_sjrf ; 

    FastenerAcrylicConstruction*    m_facr ; 


    static bool HasManagerPrefix( const char* name ); 
    IGeomManager* getManager(const char* name); 

    PMTSim(); 
    void init(); 

    static const int NAME_OFFSET ; 

    std::string         desc(const char* name); 
    G4LogicalVolume*    getLV(const char* name)  ; 
    G4VPhysicalVolume*  getPV(const char* name) ;
    G4VSolid*           getSolid(const char* name) ;
    NP*                 getValues(const char* name)  ; 

    static const char* Name(const char* prefix, int nx, int ny, int nz, const char* suffix); 
    static G4VPhysicalVolume*   WrapLVGrid( G4LogicalVolume* lv, int nx, int ny, int nz  ); 
    static G4VPhysicalVolume*   WrapLV(G4LogicalVolume* lv) ;
    static void Extract( std::vector<long>& vals, const char* s ); 
};



