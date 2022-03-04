#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <array>

#include "NP.hh"

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "NNVTMCPPMTManager.hh"
#include "NNVT_MCPPMT_PMTSolid.hh"

#include "HamamatsuMaskManager.hh"
#include "NNVTMaskManager.hh"

#include "LowerChimney.hh"


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
#include "X4SolidTree.hh"


#include <iostream>
#include <streambuf>

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
        std::cout 
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
    std::cout << " j/PMTSim/PMTSim.cc PMTSim::GetSolid(\"" << name << "\")" << std::endl ; 

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

    std::cout 
        << "PMTSim::GetSolid"
        << " name " << name  
        << " zcut " << std::setw(10) << std::fixed << std::setprecision(4) << zcut 
        << std::endl 
        ;

    if( solid != nullptr && s_zcut != nullptr )
    {
        G4VSolid* zcut_solid = X4SolidTree::ApplyZCutTree(solid, zcut);  
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
    std::cout << "PMTSim::IsDebugSolid name " << name << " found " << found << std::endl ; 
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


G4VSolid* PMTSim::GetManagerSolid(const char* name) // static
{
    std::cout << "[ PMTSim::GetManagerSolid " << name << std::endl ;      
    PMTSim* ps = new PMTSim ; 
    std::cout << "[ PMTSim::GetManagerSolid PMTSim::getSolid " << name << std::endl ;      
    G4VSolid* solid = ps->getSolid(name); 

    if( solid == nullptr )
    {
        std::cout << "PMTSim::GetManagerSolid failed for name " << name << std::endl ;  
        ps->m_hama->dump("PMTSim::GetManagerSolid.m_hama");
        DumpSolids(); 
    }
 
    std::cout << "] PMTSim::GetManagerSolid " << name << std::endl ;      
    return solid ; 
}

G4LogicalVolume* PMTSim::GetLV(const char* name) // static
{
    PMTSim::SetEnvironmentSwitches(name);  
    PMTSim* ps = new PMTSim ; 
    G4LogicalVolume* lv = ps->getLV(name); 
    return lv ; 
}

G4VPhysicalVolume* PMTSim::GetPV(const char* name) // static
{
    PMTSim::SetEnvironmentSwitches(name);  

    PMTSim* ps = new PMTSim ; 
    G4VPhysicalVolume* pv = ps->getPV(name); 

    Traverse(pv, nullptr, nullptr); 
    //DumpSolids(); 

    return pv ; 
}



G4VPhysicalVolume* PMTSim::GetPV(const char* name, std::vector<double>* tr, std::vector<G4VSolid*>* solids ) // static
{
    PMTSim::SetEnvironmentSwitches(name);  

    PMTSim* ps = new PMTSim ; 
    G4VPhysicalVolume* pv = ps->getPV(name); 

    if(pv == nullptr)
    {
        std::cout << "PMTSim::getPV failed for name [" <<  name << "]" << std::endl ; 
        return pv ; 
    }

    Traverse(pv, tr, solids); 
    //DumpSolids(); 

    return pv ; 
}

void PMTSim::SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* solids, const char* fold, const char* name ) // static
{
    NP* a = MakeArray(tr, solids); 
    a->save(fold, name); 
}

void PMTSim::SaveTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* solids, const char* path ) // static
{
    NP* a = MakeArray(tr, solids); 
    a->save(path); 
}

NP* PMTSim::MakeArray( std::vector<double>* tr, std::vector<G4VSolid*>* solids ) // static
{
    unsigned num = solids->size() ;
    assert( tr->size() == num*16 ); 

    std::stringstream ss ; 
    for(unsigned i=0 ; i < num ; i++) 
    {
        G4VSolid* solid = (*solids)[i] ; 
        G4String name = solid->GetName() ; 
        ss << name << std::endl ; 
    }
    std::string meta = ss.str(); 

    NP* a = NP::Make<double>( num, 4, 4 ); 
    a->read( tr->data() ); 
    a->meta = meta ; 
   
    return a ; 
}

void PMTSim::DumpTransforms( std::vector<double>* tr, std::vector<G4VSolid*>* solids, const char* msg ) // static
{
    std::cout << msg << std::endl ; 
    unsigned num = solids->size() ;
    assert( tr->size() == num*16 ); 
    double* trd = tr->data() ; 

    for(unsigned i=0 ; i < num ; i++)
    {
        G4VSolid* solid = (*solids)[i] ; 
        G4String soname = solid->GetName() ; 
        std::cout 
            << std::setw(5) << i 
            << " : " 
            << std::setw(25) << soname 
            ;

        std::cout << " tr ( " ; 
        for(int j=0 ; j < 16 ; j++ ) 
            std::cout << std::fixed << std::setw(7) << std::setprecision(2) << trd[i*16+j] << " " ;  
        std::cout << ")" << std::endl ; 
    }
}
 
void PMTSim::DumpSolids() // static
{
    G4SolidStore* store = G4SolidStore::GetInstance() ; 
    std::cout << "PMTSim::DumpSolids G4SolidStore.size " << store->size() << std::endl ; 
    for( unsigned i=0 ; i < store->size() ; i++)
    {
        G4VSolid* solid = (*store)[i] ; 

        G4DisplacedSolid* disp = dynamic_cast<G4DisplacedSolid*>(solid) ; 
        G4VSolid* moved = disp ? disp->GetConstituentMovedSolid() : nullptr ; 

        std::cout 
            << " i " << std::setw(5) << i 
            << " solid.name " 
            << std::setw(30) << solid->GetName()
            << " moved.name " 
            << std::setw(30) << ( moved ? moved->GetName() : "-" )
            << std::endl
            ; 
    }
}



PMTSim::PMTSim()
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
        m_nnvt = new NNVTMCPPMTManager(NNVT) ; 

        // dtors of the redirect structs reset back to standard cout/cerr streams  
    }    

    std::string out = coutbuf.str(); 
    std::string err = cerrbuf.str(); 

    std::cout 
        << "PMTSim::init" 
        << " cout chars " << std::setw(6) << out.size() 
        << " cerr chars " << std::setw(6) << err.size() 
        << " set VERBOSE to see them " 
        << std::endl  
        ;   


    m_hmsk = new HamamatsuMaskManager(HMSK_STR); 
    m_nmsk = new NNVTMaskManager(NMSK_STR) ;   
    m_lchi = new LowerChimney(LCHI_STR) ;   
    m_lchi->getLV(); 


    if(verbose) 
    {
        std::cout << "cout[" << std::endl << out << "]" << std::endl  ;   
        std::cout << "cerr[" << std::endl << err << "]" << std::endl  ;   
    }

    std::cout 
        << "PMTSim::init"
        << std::endl
        << " m_hama.desc " << m_hama->desc() 
        << std::endl
        << " m_nnvt.desc " << m_nnvt->desc() 
        << std::endl
        ;

}


const char* PMTSim::PREFIX = "0123" ;   // all prefix must have same length 
const char* PMTSim::HAMA   = "hama" ; 
const char* PMTSim::NNVT   = "nnvt" ; 
const char* PMTSim::HMSK   = "hmsk" ; 
const char* PMTSim::NMSK   = "nmsk" ; 
const char* PMTSim::LCHI   = "lchi" ; 

const std::string PMTSim::HMSK_STR = "hmsk" ; 
const std::string PMTSim::NMSK_STR = "nmsk" ; 
const std::string PMTSim::LCHI_STR = "lchi" ; 


bool PMTSim::HasManagerPrefix( const char* name ) // static
{
    bool hama = StartsWithPrefix(name, HAMA ); 
    bool nnvt = StartsWithPrefix(name, NNVT ); 
    bool hmsk = StartsWithPrefix(name, HMSK ); 
    bool nmsk = StartsWithPrefix(name, NMSK ); 
    bool lchi = StartsWithPrefix(name, LCHI ); 

    int check = int(hama) + int(nnvt) + int(hmsk) + int(nmsk) + int(lchi) ; 
    assert( check == 0 || check == 1 ) ;  
    return check == 1 ; 
}

IGeomManager* PMTSim::getManager(const char* name)
{
    IGeomManager* mgr = nullptr ;   

    bool hama = StartsWithPrefix(name, HAMA ); 
    bool nnvt = StartsWithPrefix(name, NNVT ); 
    bool hmsk = StartsWithPrefix(name, HMSK ); 
    bool nmsk = StartsWithPrefix(name, NMSK ); 
    bool lchi = StartsWithPrefix(name, LCHI ); 

    if(hama) mgr = m_hama ; 
    if(nnvt) mgr = m_nnvt ; 
    if(hmsk) mgr = m_hmsk ; 
    if(nmsk) mgr = m_nmsk ; 
    if(lchi) mgr = m_lchi ; 

    if(mgr == nullptr)
    {
        std::cerr
            << "PMTSim::getManager FATAL " 
            << " name " << name
            << " does not start with one of the expected prefixes "
            << std::endl 
            ;
    }   
    else
    {
        std::cout 
            << "PMTSim::getManager " 
            << " found manager for name " << name 
            << " hama " << hama 
            << " nnvt " << nnvt 
            << " hmsk " << hmsk
            << " nmsk " << nmsk
            << " lchi " << lchi
            << std::endl 
            ;
 
    }
    assert(mgr);  
    return mgr ; 
}


const int PMTSim::NAME_OFFSET = 0 ; 

G4LogicalVolume* PMTSim::getLV(const char* name)  
{
    IGeomManager* mgr = getManager(name) ; 
    return mgr->getLV(name + strlen(PREFIX) + NAME_OFFSET) ;  // +1 for _  
}

/**
PMTSim::getPV
--------------

When name contains "WrapLV" the name is used to get an LV (not a PV)
and that LV is placed multiple times into a grid configured by nx, ny, nz

**/

G4VPhysicalVolume* PMTSim::getPV(const char* name) 
{
    IGeomManager* mgr = getManager(name) ; 
    G4VPhysicalVolume* pv = nullptr ; 
    bool wrap = strstr(name, "WrapLV") != nullptr ; 
    if(wrap == false)
    {
        pv = mgr->getPV(name + strlen(PREFIX) + NAME_OFFSET) ; 
    }
    else
    {
        G4LogicalVolume* lv = getLV(name); 
        assert(lv); 
        pv = WrapLVGrid(lv,1,1,1);   // -1,0,1 -1,0,1 -1,0,1  3*3*3 = 27  
        assert(pv); 
    }
    return pv ; 
}
G4VSolid* PMTSim::getSolid(const char* name_) 
{
    IGeomManager* mgr = getManager(name_) ; 
    const char* name = name_ + strlen(PREFIX) + NAME_OFFSET ; 
    G4VSolid* solid = mgr->getSolid(name) ;  

    if(solid == nullptr)
        std::cout 
            << "PMTSim::getSolid FAILED " 
            << " name_ [" << name_ << "]" 
            << " name [" << name   << "]"
            << std::endl 
            ;


    assert( solid ); 
    return solid ; 
}


void PMTSim::Traverse(const G4VPhysicalVolume* const pv, std::vector<double>* tr , std::vector<G4VSolid*>* solids ) // static
{
    Traverse_r( pv, 0, tr, solids); 
}

bool PMTSim::IsIdentityRotation(const std::array<double, 16>& a, double epsilon )
{
    unsigned not_identity=0 ; 
    for(unsigned i=0 ; i < 3 ; i++) 
    for(unsigned j=0 ; j < 3 ; j++)
    {
        unsigned idx = i*4 + j ; 
        double expect = i == j ? 1. : 0. ; 
        if( std::abs( a[idx] - expect) > epsilon ) not_identity += 1 ; 
    } 
    return not_identity == 0 ; 
}

void PMTSim::Traverse_r(const G4VPhysicalVolume* const pv, int depth, std::vector<double>* tr, std::vector<G4VSolid*>* solids ) // static
{
    const G4LogicalVolume* lv = pv->GetLogicalVolume() ;
    G4VSolid* so = lv->GetSolid();
    const G4Material* const mt = lv->GetMaterial() ;
    G4String soname = so->GetName(); 

    std::array<double, 16> a ; 
    GetObjectTransform(a, pv); 
    if(tr) for(unsigned i=0 ; i < 16 ; i++) tr->push_back( a[i] ); 
    if(solids) solids->push_back(so); 

    std::cout 
        << "PMTSim::Traverse_r"
        << " depth " << std::setw(2) << depth 
        << " pv " << std::setw(22) << pv->GetName()
        << " lv " << std::setw(22) << lv->GetName()
        << " so " << std::setw(22) << so->GetName()
        << " mt " << std::setw(15) << mt->GetName()
        ;

    bool identity_rot = IsIdentityRotation( a, 1e-6 ); 
    std::cout << " tr ( " ; 
    unsigned i0 = identity_rot ? 4*3 : 0 ; 
    for(unsigned i=i0 ; i < 16 ; i++) std::cout << std::fixed << std::setw(7) << std::setprecision(2) << a[i] << " " ; 
    std::cout << ") " << std::endl ; 

    for (size_t i=0 ; i < size_t(lv->GetNoDaughters()) ;i++ ) 
    {
        const G4VPhysicalVolume* const daughter_pv = lv->GetDaughter(i);
        Traverse_r( daughter_pv, depth+1, tr, solids );
    } 
}

void PMTSim::GetObjectTransform(std::array<double, 16>& a, const G4VPhysicalVolume* const pv)
{
   // preferred for interop with glm/Opticks : obj relative to mother
    G4RotationMatrix rot = pv->GetObjectRotationValue() ;
    G4ThreeVector    tla = pv->GetObjectTranslation() ;
    G4Transform3D    t(rot,tla);

    a[ 0] = t.xx() ; a[ 1] = t.yx() ; a[ 2] = t.zx() ; a[ 3] = 0.f    ;
    a[ 4] = t.xy() ; a[ 5] = t.yy() ; a[ 6] = t.zy() ; a[ 7] = 0.f    ;
    a[ 8] = t.xz() ; a[ 9] = t.yz() ; a[10] = t.zz() ; a[11] = 0.f    ;
    a[12] = t.dx() ; a[13] = t.dy() ; a[14] = t.dz() ; a[15] = 1.f    ;
}

const char* PMTSim::Name(const char* prefix, int ix, int iy, int iz, const char* suffix)
{
    std::stringstream ss ; 
    ss << prefix << ix << "_" << iy << "_" << iz << suffix ; 
    std::string s = ss.str();
    return strdup(s.c_str()); 
}

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

Parse string converting groups of 0123456789+- chars into long integers.  

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

