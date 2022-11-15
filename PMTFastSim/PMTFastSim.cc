#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <array>

#include "NP.hh"
#include "SStr.hh"
#include "SSys.hh"
#include "SDirect.hh"

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SolidStore.hh"
#include "G4DisplacedSolid.hh"
#include "G4Material.hh"

#include "G4Box.hh"
#include "G4Polycone.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "PMTFastSim.hh"

#include <iostream>
#include <streambuf>



int PMTFastSim::LEVEL = SSys::getenvint("PMTFastSim", 0) ;   // using PLOG across packages needs investigation 


/**
PMTFastSim::SetEnvironmentSwitches
------------------------------------

Sets switches depending of the content of the name string. 

* have removed  ":pcnk:JUNO_PMT20INCH_POLYCONE_NECK" as that is now standard and non-optional 
* are in process of removing the SIMPLIFY_CSG switches
* others : NOT_USE_REAL_SURFACE and PLUS_DYNODE are for debugging and can remain.

**/

void PMTFastSim::SetEnvironmentSwitches(const char* name)  // static
{
    std::vector<std::string> tagkeys = {
       ":scsg:JUNO_PMT20INCH_SIMPLIFY_CSG",
       ":nurs:JUNO_PMT20INCH_NOT_USE_REAL_SURFACE",
       ":pdyn:JUNO_PMT20INCH_PLUS_DYNODE",
       ":prtc:JUNO_PMT20INCH_PROFLIGATE_TAIL_CUT",
       ":obto:JUNO_PMT20INCH_OBSOLETE_TORUS_NECK"
      } ; 

    for(unsigned i=0 ; i < tagkeys.size() ; i++)
    {
        const std::string& tagkey = tagkeys[i] ; 

        std::string tag_ = tagkey.substr(0,5); 
        std::string key_ = tagkey.substr(6); 
        const char* tag = tag_.c_str(); 
        const char* key = key_.c_str(); 

        bool found = strstr(name, tag) != nullptr ; 
        if(LEVEL > 0 ) std::cout 
            << "PMTFastSim::SetEnvironment"
            << " name " << std::setw(30) << name 
            << " tag [" << tag << "] "
            << " found " << found 
            << " key [" << key << "] "
            << std::endl
            ;
        if(found)
        {
            setenv(key, "ENABLED", 1 ); 
        }
        else
        {
            unsetenv(key); 
        }
    }
}


G4LogicalVolume* PMTFastSim::GetLV(const char* name) // static
{
    std::cout << "[ PMTFastSim::GetLV [" << name << "]" << std::endl ; 
    PMTFastSim::SetEnvironmentSwitches(name);  
    PMTFastSim* pfs = new PMTFastSim ; 
    G4LogicalVolume* lv = pfs->getLV(name); 
    std::cout << "] PMTFastSim::GetLV [" << name << "]" << " lv " << ( lv ? "Y" : "N" ) << std::endl ; 
    return lv ; 
}

G4VPhysicalVolume* PMTFastSim::GetPV(const char* name) // static
{
    PMTFastSim::SetEnvironmentSwitches(name);  
    PMTFastSim* pfs = new PMTFastSim ; 
    G4VPhysicalVolume* pv = pfs->getPV(name); 
    return pv ; 
}

junoPMTOpticalModel* PMTFastSim::GetPMTOpticalModel(const char* name) // static
{
    PMTFastSim::SetEnvironmentSwitches(name);  
    PMTFastSim* pfs = new PMTFastSim ; 
    junoPMTOpticalModel* pom = pfs->getPMTOpticalModel(name); 
    return pom ; 
}


PMTFastSim::PMTFastSim()
    :
    verbose(getenv("VERBOSE")!=nullptr),
    m_dc(nullptr),
    m_hama(nullptr),
    m_nnvt(nullptr),
    m_hmsk(nullptr),
    m_nmsk(nullptr)
{
    init(); 
}

/**
PMTFastSim::init
---------------

Instanciates residents with cout+cerr redirected to avoid the noise

1. m_dc(DetectorConstruction)
2. m_hama(HamamatsuR12860PMTManager)
3. m_nnvt(NNVTMCPPMTManager)

**/

void PMTFastSim::init()
{
    std::stringstream coutbuf;
    std::stringstream cerrbuf;
    {   
        cout_redirect out_(coutbuf.rdbuf());
        cerr_redirect err_(cerrbuf.rdbuf());
    
        m_dc = new DetectorConstruction ; 
        m_hama = new HamamatsuR12860PMTManager(HAMA) ; 

        /*
        m_nnvt = new NNVTMCPPMTManager(NNVT) ; 
        m_hmsk = new HamamatsuMaskManager(HMSK_STR); 
        m_nmsk = new NNVTMaskManager(NMSK_STR) ;   
        m_lchi = new LowerChimney(LCHI_STR) ;   
        m_lchi->getLV(); 
        */

        // TO SEE OUTPUT IF THE ABOVE WITHOUT SETTING VERBOSE : MOVE OUTSIDE THIS CAPTURE BLOCK
        // dtors of the redirect structs reset back to standard cout/cerr streams  
    }    

    std::string out = coutbuf.str(); 
    std::string err = cerrbuf.str(); 
    std::cout << OutputMessage("PMTFastSim::init" , out, err, verbose ); 

    if(LEVEL > 0) std::cout 
        << "PMTFastSim::init"
        << std::endl
        << " m_hama.desc " << ( m_hama ? m_hama->desc() : "-" )
        << std::endl
        ;

}


const char* PMTFastSim::HAMA   = "hama" ; 
const char* PMTFastSim::NNVT   = "nnvt" ; 
const char* PMTFastSim::HMSK   = "hmsk" ; 
const char* PMTFastSim::NMSK   = "nmsk" ; 
const char* PMTFastSim::LCHI   = "lchi" ;   // lower chimney  

const std::string PMTFastSim::HMSK_STR = "hmsk" ; 
const std::string PMTFastSim::NMSK_STR = "nmsk" ; 
const std::string PMTFastSim::LCHI_STR = "lchi" ; 


bool PMTFastSim::HasManagerPrefix( const char* name ) // static
{
    bool hama = SStr::StartsWith(name, HAMA ); 
    bool nnvt = SStr::StartsWith(name, NNVT ); 
    bool hmsk = SStr::StartsWith(name, HMSK ); 
    bool nmsk = SStr::StartsWith(name, NMSK ); 
    bool lchi = SStr::StartsWith(name, LCHI ); 

    int check = int(hama) + int(nnvt) + int(hmsk) + int(nmsk) + int(lchi) ; 
    assert( check == 0 || check == 1 ) ;  
    return check == 1 ; 
}


/**
PMTFastSim::getManager
-------------------------

The name prefix is used to find the manager.

+---------+--------------------------+
| prefix  | Manager                  |
+=========+==========================+
| nmsk    |  NNVTMaskManager         |
+---------+--------------------------+

In addition if the name has a suffix following delimiter "__"
then that string is passed to IGeomManger::setOpt

**/

IGeomManager* PMTFastSim::getManager(const char* geom)
{
    IGeomManager* mgr = nullptr ;   

    bool hama = SStr::StartsWith(geom, HAMA ); 
    /*
    bool nnvt = SStr::StartsWith(geom, NNVT ); 
    bool hmsk = SStr::StartsWith(geom, HMSK ); 
    bool nmsk = SStr::StartsWith(geom, NMSK ); 
    bool lchi = SStr::StartsWith(geom, LCHI ); 
    */

    if(hama) mgr = m_hama ; 
    /*
    if(nnvt) mgr = m_nnvt ; 
    if(hmsk) mgr = m_hmsk ; 
    if(nmsk) mgr = m_nmsk ; 
    if(lchi) mgr = m_lchi ; 
    */

    if(mgr == nullptr)
    {
        std::cerr
            << "PMTFastSim::getManager FATAL " 
            << " geom " << geom
            << " does not start with one of the expected prefixes "
            << std::endl 
            ;
    }   
    else
    {
        if(LEVEL > 1) std::cout 
            << "PMTFastSim::getManager " 
            << " found manager for geom " << geom 
            << " hama " << hama 
            << std::endl 
            ;
        /*
            << " nnvt " << nnvt 
            << " hmsk " << hmsk
            << " nmsk " << nmsk
            << " lchi " << lchi
        */
 
    }
    assert(mgr);  
    mgr->setGeom(geom);  // Chop head__tail for tail options
    return mgr ; 
}



/**
PMTSim::getLV PMTSim::getPV PMTSim::getSolid
----------------------------------------------

All three getters work similarly, the first four characters of the name 
(eg hama/nnvt/hmsk/nmsk/lchi) are used to identify the Manager that will be 
used to get the LV/PV or Solid. The managers are passed a string offset to skip the manager prefix.

**/

G4LogicalVolume* PMTFastSim::getLV(const char* geom)  
{
    IGeomManager* mgr = getManager(geom) ; 
    const char* head = mgr ? mgr->getHead() : nullptr ; 

    std::cout 
        << "PMTSim::getLV" 
        << " geom [" << geom << "]"
        << " mgr " << ( mgr ? "Y" : "N" ) 
        << " head [" << ( head ? head : "-" ) << "]"
        << std::endl
        ; 

    return mgr->getLV(head) ;  // name at this point much have mgr prefix and any option suffix removed 
}


/**
PMTSim::getPV
--------------

When name contains "WrapLV" the name is used to get an LV (not a PV)
and that LV is placed multiple times by WrapLVGrid 
into a grid configured by nx, ny, nz within a PV that is returned. 

**/

G4VPhysicalVolume* PMTFastSim::getPV(const char* name) 
{
    IGeomManager* mgr = getManager(name) ; 
    const char* head = mgr->getHead() ; 

    G4VPhysicalVolume* pv = nullptr ; 
    bool wrap = strstr(head, "WrapLV") != nullptr ; 
    if(wrap == false)
    {
        pv = mgr->getPV(head) ;
    }
    else
    {
        G4LogicalVolume* lv = getLV(head); 
        assert(lv); 
        pv = WrapLVGrid(lv,1,1,1);   // -1,0,1 -1,0,1 -1,0,1  3*3*3 = 27  
        assert(pv); 
    }
    return pv ; 
}



junoPMTOpticalModel* PMTFastSim::getPMTOpticalModel(const char* name) 
{
    IGeomManager* mgr = getManager(name) ; 
    junoPMTOpticalModel* pom = mgr ? mgr->getPMTOpticalModel(name) : nullptr ; 

    std::cout 
        << "PMTFastSim::getPMTOpticalModel"
        << " name " << ( name ? name : "-" )
        << " mgr " << ( mgr ? "Y" : "N" )
        << " pom " << ( pom ? "Y" : "N" )
        << std::endl 
        ;

    return pom ; 
}



const char* PMTFastSim::Name(const char* prefix, int ix, int iy, int iz, const char* suffix)
{
    std::stringstream ss ; 
    ss << prefix << ix << "_" << iy << "_" << iz << suffix ; 
    std::string s = ss.str();
    return strdup(s.c_str()); 
}

/**
PMTFastSim::WrapLVGrid
------------------------

Places the argument lv multiple times in a grid of placements configured by nx ny nz
that are placed within world_so/world_lv/world_pv

CAUTION: currently the grid scaling and dimensions of the world box 
make unfounded assumptions regarding the size of the lv 

The number of placements is (2*nx+1)*(2*ny+1)*(2*nz+1)

**/

G4VPhysicalVolume* PMTFastSim::WrapLVGrid( G4LogicalVolume* lv, int nx, int ny, int nz  )
{
    std::cout << "PMTFastSim::WrapLVGrid " << nx << " " << ny << " " << nz << std::endl ; 

    G4Material* vacuum = G4Material::GetMaterial("Vacuum"); 
    int extent = std::max(std::max(nx, ny), nz); 
    G4double sc = 500. ; 
    G4double halfside = sc*extent*3. ; 
    G4Box* world_so = new G4Box("World_so", halfside, halfside, halfside ); 
    G4LogicalVolume* world_lv = new G4LogicalVolume(world_so,vacuum,"World_lv",0,0,0); 
    G4VPhysicalVolume* world_pv = new G4PVPlacement(0,G4ThreeVector(),world_lv ,"World_pv",0,false,0);

    for(int ix=-nx ; ix < nx+1 ; ix++)
    for(int iy=-ny ; iy < ny+1 ; iy++)
    for(int iz=-nz ; iz < nz+1 ; iz++)
    {
        const char* iname = Name("item", ix, iy, iz, "" );         
        G4ThreeVector tla( sc*double(ix), sc*double(iy), sc*double(iz) ); 
        G4VPhysicalVolume* pv_n = new G4PVPlacement(0, tla, lv ,iname,world_lv,false,0);
        assert( pv_n ); 
    }
    return world_pv ; 
}

/**
PMTFastSim::WrapLV
--------------------

Places the argument lv into a placeholder G4PVPlacement pv that is returned. 

**/

G4VPhysicalVolume* PMTFastSim::WrapLV(G4LogicalVolume* lv) // static
{
    G4String pName = lv->GetName(); 
    pName += "_phys " ; 

    G4RotationMatrix* pRot = nullptr ; 
    G4ThreeVector     tlate(0.,0.,0.);
    G4LogicalVolume*  pMotherLogical = nullptr ; 
    G4bool pMany_unused = false ; 
    G4int pCopyNo = 0 ; 

    G4VPhysicalVolume* pv = new G4PVPlacement(pRot, tlate, lv, pName, pMotherLogical, pMany_unused, pCopyNo ); 
    std::cout << "PMTSim::WrapLV pv " << pv << std::endl ; 
    return pv ; 
}

/**
PMTFastSim::Extract
---------------------

Parse argument string converting groups of numeric 0123456789+- chars into long integers.  

**/

void PMTFastSim::Extract( std::vector<long>& vals, const char* s )  // static
{
    char* s0 = strdup(s); 
    char* p = s0 ; 
    while (*p) 
    {   
        if( (*p >= '0' && *p <= '9') || *p == '+' || *p == '-') vals.push_back(strtol(p, &p, 10)) ; 
        else p++ ;
    }   
    free(s0); 
}

