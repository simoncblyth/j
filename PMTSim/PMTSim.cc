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

#include "G4Polycone.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"
#include "PMTSim.hh"
#include "ZSolid.hh"


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
PMTSim::GetSolid
-------------------

Example names::

   maker_body_solid_zcut-183.2246

When the name is of form "maker_body_solid_zcut-183.2246" with cut 
value at the end of the name it is extracted.

**/

G4VSolid* PMTSim::GetSolid(const char* name) // static
{
    const char* s_zcut = strstr(name, "zcut") ; 
    double zcut = s_zcut == nullptr ? 999. : atof_(s_zcut+strlen("zcut")) ; 
    std::cout 
        << "PMTSim::GetSolid " << name 
        << " zcut " << std::setw(10) << std::fixed << std::setprecision(4) << zcut 
        << std::endl 
        ;

    G4VSolid* solid = GetSolid_(name); 

    if(s_zcut != nullptr)
    {
        G4VSolid* zcut_solid = ZSolid::ApplyZCutTree(solid, zcut, true );  
        solid = zcut_solid ; 
    }

    return solid ; 
}

G4VSolid* PMTSim::GetSolid_(const char* name) // static 
{
    G4VSolid* solid = nullptr ; 
    if(IsDebugSolid(name))  
    {
        solid = GetDebugSolid(name) ; 
    }
    else if(StartsWithPrefix(name, "maker"))
    {
        solid = GetMakerSolid(name) ; 
    }
    else
    {
        solid = GetManagerSolid(name) ;
    }
    return solid ; 
}

bool PMTSim::StartsWithPrefix(const char* name, const char* prefix)  // static
{
    return strlen(name) >= strlen(prefix) && strncmp( name, prefix, strlen(prefix)) == 0 ; 
}

bool PMTSim::IsDebugSolid(const char* name) // static
{
    std::vector<std::string> prefixes = { 
        "polycone", 
        "two_tubs_union", 
        "three_tubs_union",
        "ten_tubs_union"
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


G4VSolid* PMTSim::GetDebugSolid(const char* name)  // static
{
    G4VSolid* solid = nullptr ; 
    if(StartsWithPrefix(name, "polycone"))
    {
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

    } 
    else if(StartsWithPrefix(name, "two_tubs_union"))
    {
         double dz_head = 80.  ; 
         double dz_body = 100. ; 
         G4VSolid* head = new G4Tubs("head", 0., 250., dz_head, 0.00*deg, 360.00*deg );
         G4VSolid* body = new G4Tubs("body", 0., 150., dz_body, 0.00*deg, 360.00*deg );
         G4VSolid* head_body = new G4UnionSolid( "head_body", head, body, 0, G4ThreeVector(0,0,-(dz_head+dz_body+10.))); 
         solid = head_body ; 
    }
    else if(StartsWithPrefix(name, "three_tubs_union"))
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

         solid = head_body_tail ; 

/**
                                               

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

    } 
    else if(StartsWithPrefix(name, "ten_tubs_union"))
    {
        unsigned num = 10 ; 
        double* dz = new double[num] ; 
        double* ri = new double[num] ; 
        double* ro = new double[num] ; 
        G4VSolid** so = new G4VSolid*[num] ; 

        for(unsigned i=0 ; i < num ; i++ ) dz[i] = 25. ;  //double(200 - i*10); 
        for(unsigned i=0 ; i < num ; i++ ) ri[i] = 0. ; 
        for(unsigned i=0 ; i < num ; i++ ) ro[i] = 25. ; // double(200 - i*10); 
        for(unsigned i=0 ; i < num ; i++ ) so[i] = nullptr ; 

        G4VSolid* combination = nullptr ;  
        double sep = 20. ; 

        so[0] = new G4Tubs( itoa_("so%d",0), ri[0], ro[0], dz[0],  0.00*deg, 360.00*deg ); 
        combination = so[0] ; 

        for(unsigned i=1 ; i < num ; i++) 
        {
            so[i] = new G4Tubs( itoa_("so%d",1), ri[i], ro[i], dz[i], 0.00*deg, 360.00*deg ); 
            double delta = 0. ; 
            for(unsigned j=0 ; j < i ; j++) delta += (( j == i - 1 ) ? dz[j] : 2*dz[j] ); 
            // TODO: not quite separating the first two uniformly 
            combination = new G4UnionSolid( ijtoa_("so%d_%d", i-1,i), combination, so[i], 0, G4ThreeVector(0.,0.,-(delta+i*sep)) ) ;     
        }

        solid = combination ; 
    }
    return solid ; 
}

char* PMTSim::itoa_( const char* fmt, int i ) // static
{
    char s[10];
    snprintf(s, 10, fmt, i );   
    return strdup(s); 
}

char* PMTSim::ijtoa_( const char* fmt, int i, int j ) // static
{
    char s[10];
    snprintf(s, 10, fmt, i, j );   
    return strdup(s); 
}











/**
PMTSim::GetMakerSolid
----------------------

"Maker" solids come from the Hamamatsu_R12860_PMTSolid with no manager involved. 
**/

G4VSolid* PMTSim::GetMakerSolid(const char* name)  // static
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1); 
    Hamamatsu_R12860_PMTSolid* maker = new Hamamatsu_R12860_PMTSolid();
    G4VSolid* solid = maker->GetSolid(name); 
    return solid ; 
}


G4VSolid* PMTSim::GetManagerSolid(const char* name) // static
{
    std::cout << "PMTSim::GetManagerSolid " << name << std::endl ;      

    PMTSim* ps = new PMTSim ; 
    G4VSolid* solid = ps->getSolid(name); 
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
G4VSolid* PMTSim::getSolid(const char* name) 
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


G4VSolid* PMTSim::Old_GetMakerSolid(const char* name) // static
{
    Hamamatsu_R12860_PMTSolid* pmtsolid_maker = new Hamamatsu_R12860_PMTSolid(); 

    G4String solidname = name ; 
    double thickness = 0. ; 
    char mode = ' '; 
    std::vector<long> vals ; 
    Extract( vals, name ); 

    G4VSolid* solid = nullptr ; 
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

