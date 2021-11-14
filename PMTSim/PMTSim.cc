#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

#include "G4String.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SolidStore.hh"
#include "G4DisplacedSolid.hh"
#include "G4Material.hh"

#include "DetectorConstruction.hh"
#include "PMTSim.hh"
#include "ZSolid.hh"


double atof_(char* s_val)
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



G4VSolid* PMTSim::MakerSolid()  // static
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1); 

    Hamamatsu_R12860_PMTSolid* maker = new Hamamatsu_R12860_PMTSolid();

    G4VSolid* body_solid = maker->GetSolid("_body_solid"); 

    ZSolid::Draw(body_solid, "body_solid");   

    double zcut = getenvdouble("ZCUT", -400. );  

    std::cout << " zcut " << zcut << std::endl ; 

    if(zcut < -500.0 ) return body_solid ; 

    G4VSolid* body_solid_zcut = ZSolid::ApplyZCutTree(body_solid, zcut, false );  

    ZSolid::Draw(body_solid_zcut, "body_solid_zcut");   

    return body_solid_zcut ; 
}




const G4VSolid* PMTSim::GetSolid(const char* name) // static
{
    PMTSim* ps = new PMTSim ; 
    const G4VSolid* solid = ps->getSolid(name); 
    if( solid == nullptr )
    {
        std::cout << "PMTSim::GetSolid failed for name " << name << std::endl ;  
    }
    ps->ham->dump("PMTSim::GetSolid");

    std::cout 
        << "PMTSim::GetSolid"
        << " name " << name 
        << " solid " << solid
        << std::endl 
        ;

    if(solid == nullptr) DumpSolids(); 
 
    return solid ; 
}

G4VPhysicalVolume* PMTSim::GetPV(const char* name) // static
{
    PMTSim* ps = new PMTSim ; 
    G4VPhysicalVolume* pv = ps->getPV(name); 
    Traverse(pv); 
    DumpSolids(); 
    return pv ; 
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



PMTSim::PMTSim(const char* name)
    :
    dc(new DetectorConstruction),
    ham(new HamamatsuR12860PMTManager(name))
{
}
G4LogicalVolume* PMTSim::getLV(const char* name)  
{
    return ham->getLV(name) ; 
}
G4VPhysicalVolume* PMTSim::getPV(const char* name) 
{
    G4VPhysicalVolume* pv = ham->getPV(name) ; 
    return pv ; 
}
const G4VSolid* PMTSim::getSolid(const char* name) 
{
    return ham->getSolid(name) ;  
}

void PMTSim::Traverse(const G4VPhysicalVolume* const pv) // static
{
    Traverse_r( pv, 0 ); 
}

void PMTSim::Traverse_r(const G4VPhysicalVolume* const pv, int depth) // static
{
    const G4LogicalVolume* lv = pv->GetLogicalVolume() ;
    const G4VSolid* const so = lv->GetSolid();
    const G4Material* const mt = lv->GetMaterial() ;

    std::cout 
        << "PMTSim::Traverse_r"
        << " depth " << std::setw(2) << depth 
        << " pv " << std::setw(20) << pv->GetName()
        << " lv " << std::setw(20) << lv->GetName()
        << " so " << std::setw(20) << so->GetName()
        << " mt " << std::setw(20) << mt->GetName()
        << std::endl
        ;

    for (size_t i=0 ; i < size_t(lv->GetNoDaughters()) ;i++ ) 
    {
        const G4VPhysicalVolume* const daughter_pv = lv->GetDaughter(i);
        Traverse_r( daughter_pv, depth+1 );
    } 
}


const G4VSolid* PMTSim::getSolidPfx(const char* name) 
{
    const char* pfx = "Ham_" ; 
    bool starts_with_pfx = strstr( name, pfx ) != nullptr ; 
    const char* rel = starts_with_pfx ? name + strlen(pfx) : name ; 

    const G4VSolid* solid = ham->getSolid(rel) ;  

    std::cout 
         << "PMTSim::getSolid"
         << " name " << name
         << " rel " << rel 
         << " solid " << solid 
         << std::endl 
         ; 

    return solid ;  
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


const G4VSolid* PMTSim::GetMakerSolid(const char* name) // static
{
    Hamamatsu_R12860_PMTSolid* pmtsolid_maker = new Hamamatsu_R12860_PMTSolid(); 

    G4String solidname = name ; 
    double thickness = 0. ; 
    char mode = ' '; 
    std::vector<long> vals ; 
    Extract( vals, name ); 

    const G4VSolid* solid = nullptr ; 
    if(vals.size() > 0)
    {
        double zcut = vals[0] ; 
        std::cout << "[ PMTSim::GetSolid extracted zcut " << zcut << " from name " << name  << " mode" << mode << std::endl ; 
        solid = pmtsolid_maker->Old_GetZCutSolid(solidname, zcut, thickness, mode);  
        std::cout << "] PMTSim::GetSolid extracted zcut " << zcut << " from name " << name << " mode " << mode << std::endl ; 
    }
    else
    {
        std::cout << "[ PMTSim::GetSolid without zcut (as no zcut value extracted from name) " << name << std::endl ; 
        solid = pmtsolid_maker->GetSolid(solidname, thickness, mode);  
        std::cout << "] PMTSim::GetSolid without zcut (as no zcut value extracted from name) " << name << std::endl ; 
    }
    return solid ; 
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

