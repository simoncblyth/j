#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <array>

#include "NP.hh"
#include "ssys.h"

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "NNVTMCPPMTManager.hh"
#include "NNVT_MCPPMT_PMTSolid.hh"

#include "HamamatsuMaskManager.hh"
#include "NNVTMaskManager.hh"
#include "junoPMTOpticalModel.hh"

#include "LowerChimney.hh"

#include "Tub3inchPMTV3Manager.hh"

#include "XJanchorConstruction.hh"
#include "XJfixtureConstruction.hh"

#include "SJCLSanchorConstruction.hh"
#include "SJFixtureConstruction.hh"
#include "SJReceiverConstruction.hh"
#include "SJReceiverFasternConstruction.hh"

#include "FastenerAcrylicConstruction.hh"

#include "WaterPoolConstruction.hh"

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
#include "PMTSim.hh"
#include "ZSolid.h"
#include "SVolume.h"


#include <iostream>
#include <streambuf>

#ifdef POM_DEBUG
#include "NPX.h"
#include "ModelTrigger_Debug.h"
std::vector<ModelTrigger_Debug> ModelTrigger_Debug::RECORD = {} ; 
UName                           ModelTrigger_Debug::PV  = {} ; 
UName                           ModelTrigger_Debug::MLV = {} ; 


NP* PMTSim::ModelTrigger_Debug_Array()   // static
{
    NP* mtda = ModelTrigger_Debug::Array() ; 
    const char* IMPL = junoPMTOpticalModel::ModelTrigger_IMPL_Name() ; 
    assert(IMPL); 
    mtda->set_meta<std::string>("IMPL", IMPL); 
    mtda->set_meta<std::string>("NAME", ModelTrigger_Debug::NAME ); 
    return mtda ; 
}

void PMTSim::ModelTrigger_Debug_Save(const char* savedir)
{
    if(savedir == nullptr) 
    {
        std::cerr << "PMTSim::ModelTrigger_Debug_Save savedir null" << std::endl ; 
        return ; 
    } 
    NP* mtda = ModelTrigger_Debug_Array(); 
    mtda->save(savedir, ModelTrigger_Debug::NAME) ; 
}


#endif


struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer ) 
        : old( std::cout.rdbuf( new_buffer ) ) 
    { } 

    ~cout_redirect( ) { 
        std::cout.rdbuf( old );
    }   

private:
    std::streambuf * old;
};


struct cerr_redirect {
    cerr_redirect( std::streambuf * new_buffer ) 
        : old( std::cerr.rdbuf( new_buffer ) ) 
    { } 

    ~cerr_redirect( ) { 
        std::cerr.rdbuf( old );
    }   

private:
    std::streambuf * old;
};



std::string PMTSim::OutputMessage(const char* msg, const std::string& out, const std::string& err, bool verbose )  // static
{
    std::stringstream ss ; 

    ss << std::left << std::setw(30) << msg << std::right 
       << " yielded chars : "
       << " cout " << std::setw(6) << out.size() 
       << " cerr " << std::setw(6) << err.size() 
       << " : set VERBOSE to see them " 
       << std::endl  
       ;   

    if(verbose) 
    {
        ss << "cout[" << std::endl << out << "]" << std::endl  ;   
        ss << "cerr[" << std::endl << err << "]" << std::endl  ;   
    }
    std::string s = ss.str(); 
    return s ; 
}




double atof_(const char* s_val)
{
    std::istringstream iss(s_val);
    double d ; 
    iss >> d ;   
    return d ; 
}

double getenvdouble(const char* key, double fallback)
{
    char* s_val = getenv(key);
    return s_val ? atof_(s_val) : fallback ; 
}


int PMTSim::LEVEL = ssys::getenvint("PMTSim", 0) ;   // using PLOG across packages needs investigation 


/**
PMTSim::SetEnvironmentSwitches
---------------------------------

Sets switches depending of the content of the name string. 

* have removed  ":pcnk:JUNO_PMT20INCH_POLYCONE_NECK" as that is now standard and non-optional 
* are in process of removing the SIMPLIFY_CSG switches
* others : NOT_USE_REAL_SURFACE and PLUS_DYNODE are for debugging and can remain.

**/

void PMTSim::SetEnvironmentSwitches(const char* name)  // static
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
            << "PMTSim::SetEnvironment"
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


G4VSolid* PMTSim::GetSolid() // static
{
    const char* geom = ssys::getenvvar("GEOM");
    return geom ? GetSolid(geom) : nullptr ; 
}

/**
PMTSim::GetSolid
-------------------

Example names::

   maker_body_solid_zcut-183.2246

When the name is of form "maker_body_solid_zcut-183.2246" with cut 
value at the end of the name it is extracted.

**/

G4VSolid* PMTSim::GetSolid(const char* name) // static
{
    if(LEVEL > 0) std::cout << " j/PMTSim/PMTSim.cc PMTSim::GetSolid(\"" << name << "\")" << std::endl ; 

    PMTSim::SetEnvironmentSwitches(name);  

    G4VSolid* solid = GetSolid_(name); 

    if( solid == nullptr )
    {
        std::cout 
            << "PMTSim::GetSolid"
            << " FAILED " 
            << " name " << name  
            << std::endl 
            ;
    }

    const char* s_zcut = strstr(name, "zcut") ; 
    double zcut = s_zcut == nullptr ? 999. : atof_(s_zcut+strlen("zcut")) ; 

    if(LEVEL > 0) std::cout 
        << "PMTSim::GetSolid"
        << " name " << name  
        << " zcut " << std::setw(10) << std::fixed << std::setprecision(4) << zcut 
        << std::endl 
        ;

    if( solid != nullptr && s_zcut != nullptr )
    {
        G4VSolid* zcut_solid = ZSolid::ApplyZCutTree(solid, zcut);  
        solid = zcut_solid ; 
    }

    return solid ; 
}





/**
PMTSim::GetSolid_
-------------------

Unlike PMTSim::GetSolid this does not act on zcut specifications in names.
Also it does not run the environment setup. Instead the environment setup 
is done by the GetSolid caller of this. 

**/

G4VSolid* PMTSim::GetSolid_(const char* name) // static 
{
    G4VSolid* solid = nullptr ; 
    if(IsDebugSolid(name))  
    {
        solid = GetDebugSolid(name) ; 
    }
    else if(Contains(name, "Maker"))  // maker comes first as will have manager prefix too
    {
        solid = GetMakerSolid(name) ; 
    }
    else if(HasManagerPrefix(name))   // names begins with one of : hama/nnvt/hmsk/nmsk/lchi
    {
        solid = GetManagerSolid(name) ;
    }

    if( solid == nullptr )
    {    
        G4SolidStore* store = G4SolidStore::GetInstance(); 
        G4bool verbose = false ; 
        solid = store->GetSolid(name, verbose); 
    }    

    if( solid == nullptr )
    {
        std::cout
            << "PMTSim::GetSolid_"
            << " FAILED for name " << name
            << std::endl
            ;   
    }
    return solid ; 
}



NP* PMTSim::GetValues(const char* name) // static
{
    NP* vv = nullptr ; 
    if(HasManagerPrefix(name))   // names begins with one of : hama/nnvt/hmsk/nmsk/lchi
    {
        vv = GetManagerValues(name) ;
    }
    return vv ; 
}




bool PMTSim::StartsWithPrefix(const char* name, const char* prefix)  // static
{
    return strlen(name) >= strlen(prefix) && strncmp( name, prefix, strlen(prefix)) == 0 ; 
}
bool PMTSim::Contains(const char* name, const char* sub)  // static
{
    return strlen(name) >= strlen(sub) && strstr( name, sub) != nullptr  ; 
}


bool PMTSim::IsDebugSolid(const char* name) // static
{
    std::vector<std::string> prefixes = { 
        "Polycone", 
        "TwoTubsUnion", 
        "ThreeTubsUnion",
        "TenTubsUnion"
        } ; 

    bool found = false ; 
    for(unsigned i=0 ; i < prefixes.size() ; i++) 
    {
        const char* prefix = prefixes[i].c_str() ; 
        if(StartsWithPrefix(name, prefix))
        {
           found = true ; 
           break ;  
        }
    }
    if(LEVEL > 1) std::cout << "PMTSim::IsDebugSolid name " << name << " found " << found << std::endl ; 
    return found ; 
}


G4VSolid* PMTSim::Polycone(const char* name)  // static
{
    G4VSolid* solid = nullptr ; 
    G4double phiStart = 0.00*deg ; 
    G4double phiTotal = 360.00*deg ;
    G4int numZPlanes = 2 ; 
    G4double zPlane[] = { -200.0           , 0.0  } ;   
    G4double rInner[] = {  0.0             , 0.0   } ;   
    G4double rOuter[] = {  275.0           , 275.0 } ;    

    solid = new G4Polycone(
                           name,
                           phiStart,
                           phiTotal,
                           numZPlanes,
                           zPlane,
                           rInner,
                           rOuter
                           );  
    return solid ; 
}

G4VSolid* PMTSim::TwoTubsUnion(const char* name)
{
    G4VSolid* solid = nullptr ; 
    double dz_head = 80.  ; 
    double dz_body = 100. ; 
    G4VSolid* head = new G4Tubs("head", 0., 250., dz_head, 0.00*deg, 360.00*deg );
    G4VSolid* body = new G4Tubs("body", 0., 150., dz_body, 0.00*deg, 360.00*deg );
    G4VSolid* head_body = new G4UnionSolid( "head_body", head, body, 0, G4ThreeVector(0,0,-(dz_head+dz_body+10.))); 
    solid = head_body ; 
    return solid ; 
}

/**
PMTSim::ThreeTubsUnion
--------------------------
                                               

                           |---------------|      dz_head + dz_body + sep                  (1st shift)

            |------------------------------|      dz_head + 2*dz_body + dz_tail + 2*sep    (2nd shift)

                                                            ^ because must push down the full width of the intermediate body  

                    +-------------+
                    |             |
                    |             | +------|------+ 
                    |             | |             |
      +-----------+ |             | |             |
      |           | |             | |             |
      |           | |             | |             |
      |      tail | |             | |             |
      +-----------+ |             | |             |
                    |             | |        head |
                    |             | +-------------+
                    |       body  |
                    +-------------+

**/

G4VSolid* PMTSim::ThreeTubsUnion(const char* name)
{
    double dz_head = 250.  ;  double r_head = 250. ; 
    double dz_body = 150. ;   double r_body = 150. ; 
    double dz_tail = 100.  ;  double r_tail = 100. ;    
    double sep = 20. ; 

    double first_shift = dz_head+dz_body+sep ; 
    double second_shift = dz_head+2.*dz_body+dz_tail+2.*sep ; 

    G4VSolid* head = new G4Tubs("head", 0., r_head, dz_head, 0.00*deg, 360.00*deg );
    G4VSolid* body = new G4Tubs("body", 0., r_body, dz_body, 0.00*deg, 360.00*deg );
    G4VSolid* head_body = new G4UnionSolid( "head_body", head, body, 0, G4ThreeVector(0,0,-first_shift)); 

    G4VSolid* tail = new G4Tubs("tail", 0., r_tail, dz_tail, 0.00*deg, 360.00*deg );
    G4VSolid* head_body_tail = new G4UnionSolid( "head_body_tail", head_body, tail,  0, G4ThreeVector(0,0,-second_shift)); 

    return head_body_tail ; 
}

G4VSolid* PMTSim::TenTubsUnion(const char* name)
{
    unsigned num = 10 ; 
    double* dz = new double[num] ; 
    double* ri = new double[num] ; 
    double* ro = new double[num] ; 
    double* zs = new double[num] ; 
    G4VSolid** so = new G4VSolid*[num] ; 

    for(unsigned i=0 ; i < num ; i++ ) 
    {
        dz[i] = 25. ;  
        ri[i] = 0. ; 
        ro[i] = 25. ; 
        so[i] = nullptr ; 
    }
    double sep = 20. ; 
    double startPhi = 0.00*deg ; 
    double totPhi = 360.00*deg ; 


    G4VSolid* combination = nullptr ;  

    so[0] = new G4Tubs( itoa_("so_%d",0), ri[0], ro[0], dz[0],  startPhi, totPhi ); 
    zs[0] = 0. ; 

    combination = so[0] ; 

    std::cout 
        << "PMTSim::GetDebugSolid"  
        << " name " << name
        << " num " << num
        << std::endl 
        ;

    for(unsigned i=1 ; i < num ; i++) 
    {
        so[i] = new G4Tubs( itoa_("so_%d",i), ri[i], ro[i], dz[i], startPhi, totPhi ); 

        double delta = 0. ; 
        for(unsigned j=0 ; j <= i ; j++) delta += dz[j]*(( j == 0 || j == i ) ? 1. : 2. ) ;

        zs[i] = -(delta+i*sep) ; 
             
        combination = new G4UnionSolid( ijtoa_("so_%d_%d", i-1,i), combination, so[i], 0, G4ThreeVector(0.,0.,zs[i] )) ;     
    }

    std::cout << "zz=" ; 
    for(unsigned i=0 ; i < num ; i++ ) std::cout << int(zs[i]) << "," ;  
    std::cout << std::endl  ; 

    return combination ; 
}
 
G4VSolid* PMTSim::GetDebugSolid(const char* name)  // static
{
    G4VSolid* solid = nullptr ; 
    if(     StartsWithPrefix(name, "Polycone"))       solid = Polycone(name) ; 
    else if(StartsWithPrefix(name, "TwoTubsUnion"))   solid = TwoTubsUnion(name) ; 
    else if(StartsWithPrefix(name, "ThreeTubsUnion")) solid = ThreeTubsUnion(name) ; 
    else if(StartsWithPrefix(name, "TenTubsUnion"))   solid = TenTubsUnion(name) ; 
    return solid ; 
}



char* PMTSim::itoa_( const char* fmt, int i ) // static
{
    char s[16];
    snprintf(s, 16, fmt, i );   
    return strdup(s); 
}

char* PMTSim::ijtoa_( const char* fmt, int i, int j ) // static
{
    char s[16];
    snprintf(s, 16, fmt, i, j );   
    return strdup(s); 
}


/**
PMTSim::GetMakerSolid
----------------------

This is invoked when the name contains "maker" resulting in direct
access to solids from the makers with no manager instanciated.
Example names::

    hama_maker
    nnvt_maker

NB this is using the original old GetSolid interface where the name does not choose 
between types of solid but rather just supplies the prefix to the fixed tree 
of solids created.

**/

G4VSolid* PMTSim::GetMakerSolid(const char* name)  // static
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1);

    bool hama = StartsWithPrefix(name, HAMA); 
    bool nnvt = StartsWithPrefix(name, NNVT); 
    bool expect = hama ^ nnvt ; 

    if(!expect)
    {
        std::cout 
            << "PMTSim::GetMakerSolid"
            << " FATAL UNEXPECTED PREFIX "
            << " name " << name 
            << std::endl 
            ;
    }
    assert( expect ); 

    G4VSolid* solid = nullptr ; 
    if(hama) 
    {
        Hamamatsu_R12860_PMTSolid* maker = new Hamamatsu_R12860_PMTSolid();
        solid = maker->GetSolid(name);    
    } 
    else if( nnvt )
    { 
        NNVT_MCPPMT_PMTSolid* maker = new NNVT_MCPPMT_PMTSolid() ; 
        solid = maker->GetSolid(name);    
    }
    return solid ; 
}



const char*  PMTSim::LastManagerSolidName   = nullptr ; 
NP*          PMTSim::LastManagerSolidValues = nullptr ; 

void PMTSim::SetLastManagerSolid(const char* name, NP* vv)  // static 
{
    LastManagerSolidName   = name ; 
    LastManagerSolidValues = vv ; 
}

const char* PMTSim::GetLastManagerSolidName(){   return LastManagerSolidName   ;  }
NP*         PMTSim::GetLastManagerSolidValues(){ return LastManagerSolidValues ;  }


G4VSolid* PMTSim::GetManagerSolid(const char* name) // static
{
    if(LEVEL > 0) std::cout << "[ PMTSim::GetManagerSolid " << name << " instanciate PMTSim " << std::endl ;      
    PMTSim* ps = new PMTSim ; 
    if(LEVEL > 0) std::cout << "[ PMTSim::GetManagerSolid PMTSim::getSolid " << name << std::endl ;      
    G4VSolid* solid = ps->getSolid(name); 
    NP* values = ps->getValues(name) ; 

    SetLastManagerSolid(name, values); 

    if( solid == nullptr )
    {
        std::cout << "PMTSim::GetManagerSolid failed for name " << name << std::endl ;  
        ps->m_hama->dump("PMTSim::GetManagerSolid.m_hama");
        SVolume::DumpSolids(); 
    }
 
    if(LEVEL > 0) std::cout << "] PMTSim::GetManagerSolid " << name << std::endl ;      
    return solid ; 
}


NP* PMTSim::GetManagerValues(const char* name) // static
{
    NP* vv = nullptr ; 
    if( LastManagerSolidName && name && strcmp(LastManagerSolidName, name) == 0 )
    {
        vv = LastManagerSolidValues ; 
    }
    else
    {
        PMTSim* ps = new PMTSim ; 
        vv = ps->getValues(name) ; 
    }
    return vv ; 
}

std::string PMTSim::Desc(const char* name) // static
{
    std::cout << "[ PMTSim::Desc [" << name << "]" << std::endl ; 
    PMTSim::SetEnvironmentSwitches(name);  
    PMTSim* ps = new PMTSim ; 
    std::string msg = ps->desc(name); 
    std::cout << "] PMTSim::Desc [" << name << "]" << std::endl ; 
    return msg ; 
}
G4LogicalVolume* PMTSim::GetLV(const char* name) // static
{
    std::cout << "[ PMTSim::GetLV [" << name << "]" << std::endl ; 
    PMTSim::SetEnvironmentSwitches(name);  
    PMTSim* ps = new PMTSim ; 
    G4LogicalVolume* lv = ps->getLV(name); 
    std::cout << "] PMTSim::GetLV [" << name << "]" << " lv " << ( lv ? "Y" : "N" ) << std::endl ; 
    return lv ; 
}

G4VPhysicalVolume* PMTSim::GetPV(const char* name) // static
{
    PMTSim::SetEnvironmentSwitches(name);  
    PMTSim* ps = new PMTSim ; 
    G4VPhysicalVolume* pv = ps->getPV(name); 
    SVolume::Traverse(pv, nullptr, nullptr); 
    //DumpSolids(); 
    return pv ; 
}

/**
PMTSim::GetPV
---------------

1. gets the physical volume
2. populates vector of G4VSolid 
3. populates vector of doubles with the structural transforms for each solid 

**/

G4VPhysicalVolume* PMTSim::GetPV(const char* name, std::vector<double>* tr, std::vector<G4VSolid*>* solids ) // static
{
    if(LEVEL > 0 ) std::cout << "PMTSim::GetPV with transforms : name [" << ( name ? name : "-" ) << "]" << std::endl ; 
    PMTSim::SetEnvironmentSwitches(name);  

    PMTSim* ps = new PMTSim ; 
    G4VPhysicalVolume* pv = ps->getPV(name); 

    if(pv == nullptr)
    {
        std::cout << "PMTSim::getPV failed for name [" <<  name << "]" << std::endl ; 
        return pv ; 
    }

    SVolume::Traverse(pv, tr, solids); 
    //SVolume::DumpSolids(); 

    return pv ; 
}


PMTSim::PMTSim()
    :
    verbose(getenv("VERBOSE")!=nullptr),
    HMSK_STR(HMSK),  
    NMSK_STR(NMSK),   
    LCHI_STR(LCHI),   
    TUB3_STR(TUB3),  
    XJAC_STR(XJAC),
    XJFC_STR(XJFC),
    SJCL_STR(SJCL),
    SJFX_STR(SJFX),
    SJRC_STR(SJRC),  
    SJRF_STR(SJRF),  
    FACR_STR(FACR),
    WPCO_STR(WPCO),
    m_dc(nullptr),
    m_hama(nullptr),
    m_nnvt(nullptr),
    m_hmsk(nullptr),
    m_nmsk(nullptr),
    m_lchi(nullptr),
    m_tub3(nullptr),
    m_xjac(nullptr),
    m_xjfc(nullptr),
    m_sjcl(nullptr),
    m_sjfx(nullptr),
    m_sjrc(nullptr),
    m_sjrf(nullptr),
    m_facr(nullptr),
    m_wpco(nullptr)
{
    init(); 
}

/**
PMTSim::init
---------------

Instanciates residents with cout+cerr redirected to avoid the noise

1. m_dc(DetectorConstruction)
2. m_hama(HamamatsuR12860PMTManager)
3. m_nnvt(NNVTMCPPMTManager)

**/

void PMTSim::init()
{
    std::stringstream coutbuf;
    std::stringstream cerrbuf;
    {   
        cout_redirect out_(coutbuf.rdbuf());
        cerr_redirect err_(cerrbuf.rdbuf());
    
        m_dc = new DetectorConstruction ; 

        m_hama = new HamamatsuR12860PMTManager(HAMA) ; 
        m_hama->getLV(); 

        m_nnvt = new NNVTMCPPMTManager(NNVT) ; 
        m_nnvt->getLV() ; 

        m_hmsk = new HamamatsuMaskManager(HMSK_STR); 
        m_hmsk->getLV(); 

        m_nmsk = new NNVTMaskManager(NMSK_STR) ;   
        m_nmsk->getLV(); 

        m_lchi = new LowerChimney(LCHI_STR) ;   
        m_lchi->getLV(); 

        m_tub3 = new Tub3inchPMTV3Manager(TUB3_STR) ;   
        m_tub3->getLV(); 

        m_xjac = new XJanchorConstruction(XJAC_STR) ; 
        m_xjac->getLV(); 

        m_xjfc = new XJfixtureConstruction(XJFC_STR) ; 
        m_xjfc->getLV() ; 

        m_sjcl = new SJCLSanchorConstruction(SJCL_STR) ; 
        m_sjcl->getLV(); 

        m_sjfx = new SJFixtureConstruction(SJFX_STR) ; 
        m_sjfx->getLV(); 

        m_sjrc = new SJReceiverConstruction(SJRC_STR) ;
        m_sjrc->getLV(); 

        m_sjrf = new SJReceiverFasternConstruction(SJRF_STR) ; 
        m_sjrf->getLV(); 

        m_facr = new FastenerAcrylicConstruction(FACR_STR) ; 
        m_facr->getLV(); 

        m_wpco = new WaterPoolConstruction(WPCO_STR) ;
        m_wpco->getLV();

        // TO SEE OUTPUT IF THE ABOVE WITHOUT SETTING VERBOSE : MOVE OUTSIDE THIS CAPTURE BLOCK
        // dtors of the redirect structs reset back to standard cout/cerr streams  
    }    

    std::string out = coutbuf.str(); 
    std::string err = cerrbuf.str(); 
    std::cout << OutputMessage("PMTSim::init" , out, err, verbose ); 

    if(LEVEL > 0) std::cout 
        << "PMTSim::init"
        << std::endl
        << " m_hama.desc " << m_hama->desc() 
        << std::endl
        << " m_nnvt.desc " << m_nnvt->desc() 
        << std::endl
        ;

}

bool PMTSim::HasManagerPrefix( const char* name ) // static
{
    bool hama = StartsWithPrefix(name, HAMA ); 
    bool nnvt = StartsWithPrefix(name, NNVT ); 
    bool hmsk = StartsWithPrefix(name, HMSK ); 
    bool nmsk = StartsWithPrefix(name, NMSK ); 
    bool lchi = StartsWithPrefix(name, LCHI ); 
    bool tub3 = StartsWithPrefix(name, TUB3 ); 
    bool xjac = StartsWithPrefix(name, XJAC ); 
    bool xjfc = StartsWithPrefix(name, XJFC ); 
    bool sjcl = StartsWithPrefix(name, SJCL ); 
    bool sjfx = StartsWithPrefix(name, SJFX ); 
    bool sjrc = StartsWithPrefix(name, SJRC ); 
    bool sjrf = StartsWithPrefix(name, SJRF ); 
    bool facr = StartsWithPrefix(name, FACR );
    bool wpco = StartsWithPrefix(name, WPCO );

    int check = 0 ; 
    if(hama) check += 1 ; 
    if(nnvt) check += 1 ; 
    if(hmsk) check += 1 ; 
    if(nmsk) check += 1 ; 
    if(lchi) check += 1 ; 

    if(tub3) check += 1 ; 
    if(xjac) check += 1 ; 
    if(xjfc) check += 1 ; 
    if(sjcl) check += 1 ; 
    if(sjfx) check += 1 ; 
    if(sjrc) check += 1 ; 
    if(sjrf) check += 1 ; 
    if(facr) check += 1 ;
    if(wpco) check += 1 ;

    assert( check == 0 || check == 1 ) ;  
    return check == 1 ; 
}


/**
PMTSim::getManager
-------------------

The name prefix is used to find the manager.

+---------+--------------------------+
| prefix  | Manager                  |
+=========+==========================+
| nmsk    |  NNVTMaskManager         |
+---------+--------------------------+

In addition if the name has a suffix following delimiter "__"
then that string is passed to IGeomManger::setOpt

**/

IGeomManager* PMTSim::getManager(const char* geom)
{
    IGeomManager* mgr = nullptr ;   

    bool hama = StartsWithPrefix(geom, HAMA ); 
    bool nnvt = StartsWithPrefix(geom, NNVT ); 
    bool hmsk = StartsWithPrefix(geom, HMSK ); 
    bool nmsk = StartsWithPrefix(geom, NMSK ); 
    bool lchi = StartsWithPrefix(geom, LCHI ); 
    bool tub3 = StartsWithPrefix(geom, TUB3 ); 
    bool xjac = StartsWithPrefix(geom, XJAC ); 
    bool xjfc = StartsWithPrefix(geom, XJFC ); 
    bool sjcl = StartsWithPrefix(geom, SJCL ); 
    bool sjfx = StartsWithPrefix(geom, SJFX ); 
    bool sjrc = StartsWithPrefix(geom, SJRC ); 
    bool sjrf = StartsWithPrefix(geom, SJRF ); 
    bool facr = StartsWithPrefix(geom, FACR );
    bool wpco = StartsWithPrefix(geom, WPCO );

    if(hama) mgr = m_hama ; 
    if(nnvt) mgr = m_nnvt ; 
    if(hmsk) mgr = m_hmsk ; 
    if(nmsk) mgr = m_nmsk ; 
    if(lchi) mgr = m_lchi ; 
    if(tub3) mgr = m_tub3 ; 
    if(xjac) mgr = m_xjac ; 
    if(xjfc) mgr = m_xjfc ; 
    if(sjcl) mgr = m_sjcl ; 
    if(sjfx) mgr = m_sjfx ; 
    if(sjrc) mgr = m_sjrc ; 
    if(sjrf) mgr = m_sjrf ; 
    if(facr) mgr = m_facr ;
    if(wpco) mgr = m_wpco ;

    if(mgr == nullptr)
    {
        std::cerr
            << "PMTSim::getManager FATAL " 
            << " geom " << geom
            << " does not start with one of the expected prefixes "
            << std::endl 
            ;
    }   
    else
    {
        if(LEVEL > 1) std::cout 
            << "PMTSim::getManager " 
            << " found manager for geom " << geom 
            << " hama " << hama 
            << " nnvt " << nnvt 
            << " hmsk " << hmsk
            << " nmsk " << nmsk
            << " lchi " << lchi
            << " tub3 " << tub3
            << " xjac " << xjac
            << " xjfc " << xjfc
            << " sjcl " << sjcl
            << " sjfx " << sjfx
            << " sjrc " << sjrc
            << " sjrf " << sjrf
            << " facr " << facr
            << std::endl 
            ;
 
    }
    assert(mgr);  
    mgr->setGeom(geom);  // Chop head__tail for tail options
    return mgr ; 
}


/**
PMTSim::desc
-------------

Just need the manager prefix, eg "xjac"

**/

std::string PMTSim::desc(const char* mgr_prefix)
{
    IGeomManager* mgr = getManager(mgr_prefix) ; 
    return mgr ? mgr->desc() : "no-manager" ; 
}


/**
PMTSim::getLV PMTSim::getPV PMTSim::getSolid
----------------------------------------------

All three getters work similarly, the first four characters of the name 
(eg hama/nnvt/hmsk/nmsk/lchi) are used to identify the Manager that will be 
used to get the LV/PV or Solid. The managers are passed a string offset to skip the manager prefix.

**/

G4LogicalVolume* PMTSim::getLV(const char* geom)  
{
    IGeomManager* mgr = getManager(geom) ; 
    const char* head = mgr ? mgr->getHead() : nullptr ; 

    std::cout 
        << "PMTSim::getLV" 
        << " geom [" << geom << "]"
        << " mgr " << ( mgr ? "Y" : "N" ) 
        << " head [" << ( head ? head : "-" ) << "]"
        << std::endl
        << " mgr.desc "
        << std::endl
        << ( mgr ? mgr->desc() : "-" )
        << std::endl
        ; 


    return mgr->getLV(head) ;  // name at this point much have mgr prefix and any option suffix removed 
}



NP* PMTSim::getValues(const char* geom)
{
    IGeomManager* mgr = getManager(geom) ; 
    const char* head = mgr->getHead() ; 
    NP* vv0 = mgr->getValues(head);  

    // if the name prefix fails to yield any values, try again with null to get all values
    NP* vv = vv0 == nullptr ? mgr->getValues(nullptr) : vv0 ;  

    if(LEVEL > 0) std::cout 
        << "PMTSim::getValues" 
        << " geom [" << geom << "]"
        << " mgr " << ( mgr ? "Y" : "N" ) 
        << " vv0 " << ( vv0 ? vv0->sstr() : "-" )
        << " vv " << ( vv ? vv->sstr() : "-" )
        << std::endl
        ; 

    return vv ; 
}





G4VSolid* PMTSim::getSolid(const char* geom) 
{
    IGeomManager* mgr = getManager(geom) ; 
    const char* head = mgr->getHead() ; 

    if(LEVEL > 0) std::cout 
         << "[ PMTSim::getSolid " 
         << " geom " << ( geom ? geom : "-" )  
         << " mgr " << ( mgr ? "YES" : "NO " )  
         << " head " << ( head ? head : "-" )  
         << std::endl 
         ; 


    G4VSolid* solid = nullptr ; 

    std::stringstream coutbuf;
    std::stringstream cerrbuf;
    {   
        cout_redirect out_(coutbuf.rdbuf());
        cerr_redirect err_(cerrbuf.rdbuf());

        solid = mgr->getSolid(head) ;  

        // dtors of the redirect structs reset back to standard cout/cerr streams  
    }    

    std::string out = coutbuf.str(); 
    std::string err = cerrbuf.str(); 
    std::cout << OutputMessage("PMTSim::getSolid" , out, err, verbose ); 


    if(LEVEL > 0) std::cout << "] PMTSim::getSolid " << geom << std::endl ; 


    if(solid == nullptr)
        std::cout 
            << "PMTSim::getSolid FAILED " 
            << " geom [" << geom   << "]"
            << std::endl 
            ;


    assert( solid ); 
    return solid ; 
}

/**
PMTSim::getPV
--------------

When name contains "WrapLV" the name is used to get an LV (not a PV)
and that LV is placed multiple times by WrapLVGrid 
into a grid configured by nx, ny, nz within a PV that is returned. 

**/

G4VPhysicalVolume* PMTSim::getPV(const char* name) 
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
const char* PMTSim::Name(const char* prefix, int ix, int iy, int iz, const char* suffix)
{
    std::stringstream ss ; 
    ss << prefix << ix << "_" << iy << "_" << iz << suffix ; 
    std::string s = ss.str();
    return strdup(s.c_str()); 
}

/**
PMTSim::WrapLVGrid
--------------------

Places the argument lv multiple times in a grid of placements configured by nx ny nz
that are placed within world_so/world_lv/world_pv

CAUTION: currently the grid scaling and dimensions of the world box 
make unfounded assumptions regarding the size of the lv 

The number of placements is (2*nx+1)*(2*ny+1)*(2*nz+1)

**/

G4VPhysicalVolume* PMTSim::WrapLVGrid( G4LogicalVolume* lv, int nx, int ny, int nz  )
{
    std::cout << "PMTSim::WrapLVGrid " << nx << " " << ny << " " << nz << std::endl ; 

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
PMTSim::WrapLV
------------------

Places the argument lv into a placeholder G4PVPlacement pv that is returned. 

**/

G4VPhysicalVolume* PMTSim::WrapLV(G4LogicalVolume* lv) // static
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
PMTSim::Extract
----------------

Parse argument string converting groups of numeric 0123456789+- chars into long integers.  

**/

void PMTSim::Extract( std::vector<long>& vals, const char* s )  // static
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


