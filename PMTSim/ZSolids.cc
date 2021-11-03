#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4RotationMatrix.hh"

#include "ZSolids.hh"
#include "NP.hh"

std::string ZSolid::desc() const 
{
    std::stringstream ss ; 
    ss 
       << " EntityTypeName " << std::setw(15) << EntityTypeName(solid) 
       << " EntityType " << std::setw(3) << EntityType(solid) 
       << " label " << std::setw(10) << label 
       << " zdelta " << std::setw(10) << std::fixed << std::setprecision(3) << zdelta 
       << " z1 " << std::setw(10) << std::fixed << std::setprecision(3) << z1()
       << " z0 " << std::setw(10) << std::fixed << std::setprecision(3) << z0()
       ;
    std::string s = ss.str(); 
    return s ; 
}

/**
ZSolid::EntityTypeName
-----------------------

Unexpectedly G4 returns EntityType by value rather than by reference
so have to strdup to avoid corruption when the G4String goes out of scope. 

**/

const char* ZSolid::EntityTypeName(const G4VSolid* const solid)  
{
    G4GeometryType type = solid->GetEntityType();  // G4GeometryType typedef for G4String
    return strdup(type.c_str()); 
}

int ZSolid::EntityType(const G4VSolid* const solid)
{
    const char* name = EntityTypeName(solid); 
    int type = _G4Other ; 
    if( strcmp(name, "G4Ellipsoid") == 0 )         type = _G4Ellipsoid ; 
    if( strcmp(name, "G4Tubs") == 0 )              type = _G4Tubs ; 
    if( strcmp(name, "G4Polycone") == 0 )          type = _G4Polycone ; 
    if( strcmp(name, "G4UnionSolid") == 0 )        type = _G4UnionSolid ; 
    if( strcmp(name, "G4SubtractionSolid") == 0 )  type = _G4SubtractionSolid ; 
    if( strcmp(name, "G4IntersectionSolid") == 0 ) type = _G4IntersectionSolid ; 
    if( strcmp(name, "G4DisplacedSolid") == 0 )    type = _G4DisplacedSolid ; 
    return type ; 
}

bool ZSolid::IsBooleanSolid(const G4VSolid* const solid) // static
{
    return dynamic_cast<const G4BooleanSolid*>(solid) != nullptr ; 
}

bool ZSolid::IsDisplacedSolid(const G4VSolid* const solid) // static
{
    return dynamic_cast<const G4DisplacedSolid*>(solid) != nullptr ; 
}


/**
ZSolid::DumpTree
------------------
 
Postorder traversal of CSG tree, eg::


     type          G4Ellipsoid name           PMTSim_Z_I msg       left depth 7 tla (0 0 0) rot (1)
     type               G4Tubs name          PMTSim_Z_II msg      right depth 7 tla (0 0 -2.5) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_2 msg       left depth 6 tla (0 0 0) rot (1)
     type          G4Ellipsoid name         PMTSim_Z_III msg      right depth 6 tla (0 0 -5) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_3 msg       left depth 5 tla (0 0 0) rot (1)
     type           G4Polycone name          PMTSim_Z_IV msg      right depth 5 tla (0 0 -179.216) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_4 msg       left depth 4 tla (0 0 0) rot (1)
     type               G4Tubs name           PMTSim_Z_V msg      right depth 4 tla (0 0 -242.5) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_5 msg       left depth 3 tla (0 0 0) rot (1)
     type          G4Ellipsoid name          PMTSim_Z_VI msg      right depth 3 tla (0 0 -275) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_6 msg       left depth 2 tla (0 0 0) rot (1)
     type               G4Tubs name        PMTSim_Z_VIII msg      right depth 2 tla (0 0 -385) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_8 msg       left depth 1 tla (0 0 0) rot (1)
     type           G4Polycone name          PMTSim_Z_IX msg      right depth 1 tla (0 0 -420) rot (1)
     type         G4UnionSolid name         PMTSim_Z_1_9 msg  pmt_solid depth 0 tla (0 0 0) rot (1)


Postorder traversal means that visit the children before the parents and start the visit at bottom left of the tree.
NTreeAnalyse height 7 count 15::

    .                                                   un    

                                                  un          cy

                                          un          cy        

                                  un          zs                

                          un          cy                        

                  un          co                                

          un          zs                                        
                     (-5) 
      zs      cy                                              
             (-2.5)


**/

void ZSolid::DumpTree( const char* msg, const G4VSolid* const _solid, int depth  )  // static
{
    bool is_boolean = IsBooleanSolid(_solid) ; 
    const G4VSolid* left  = is_boolean ? _solid->GetConstituentSolid(0) : nullptr ; 
    const G4VSolid* right = is_boolean ? _solid->GetConstituentSolid(1) : nullptr ; 

    if(left && right)
    {
        DumpTree("left",  left,  depth+1) ; 
        DumpTree("right", right, depth+1) ; 
    }

    G4RotationMatrix rot ; 
    G4ThreeVector tla(0., 0., 0. ); 
    const G4VSolid* solid = GetDisplacement( &rot, &tla, _solid ); 

    std::cout 
        << " type " << std::setw(20) << EntityTypeName(solid) 
        << " name " << std::setw(20) << solid->GetName() 
        << " msg " << std::setw(10) << msg 
        << " depth " << depth 
        << " tla (" << tla.x() << " " << tla.y() << " " << tla.z() << ")" 
        << std::endl
        ; 
}

const G4VSolid* ZSolid::GetDisplacement( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* _solid  ) // static
{
    const G4DisplacedSolid* disp = dynamic_cast<const G4DisplacedSolid*>(_solid) ; 
    if(disp)
    {
        if(rot) *rot = disp->GetFrameRotation();
        if(rot) assert( rot->isIdentity() ); 
        if(tla) *tla = disp->GetObjectTranslation();  
    }
    const G4VSolid* solid = disp ? disp->GetConstituentMovedSolid() : _solid  ;
    return solid ; 
}


/**
ZSolid::DeepClone
-------------------

Clones a CSG tree of solids, assuming that the tree is
composed only of the limited set of primitives that are supported. 

G4BooleanSolid copy ctor just steals constituent pointers so 
it does not make an independent copy.  
Unlike the primitive copy ctors (at least those looked at: G4Polycone, G4Tubs) 
which appear to make properly independent copies 

**/

G4VSolid* ZSolid::DeepClone( const  G4VSolid* _solid )  // static 
{
    G4RotationMatrix rot ; 
    G4ThreeVector tla ; 
    int depth = 0 ; 
    return DeepClone_r(_solid, depth, &rot, &tla );  
}

G4VSolid* ZSolid::DeepClone_r( const  G4VSolid* _solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla )  // static 
{
    G4VSolid* clone = nullptr ; 

    const G4VSolid* solid = GetDisplacement( rot, tla, _solid ); 
    int type = EntityType(solid); 
    G4String name = solid->GetName() ; 

    std::cout 
        << "ZSolid::DeepClone"
        << " type " << std::setw(20) << EntityTypeName(solid)
        << " name " << std::setw(20) << name
        << " depth " << std::setw(2) << depth
        << " tla (" << tla->x() << " " << tla->y() << " " << tla->z() << ")" 
        << std::endl 
        ; 

    if(IsBooleanSolid(solid))
    {
        const G4BooleanSolid* boolean= dynamic_cast<const G4BooleanSolid*>(solid) ; 
        const G4VSolid* left  = boolean->GetConstituentSolid(0) ; 
        const G4VSolid* right = boolean->GetConstituentSolid(1) ; 

        G4RotationMatrix lrot, rrot ;  
        G4ThreeVector    ltra, rtra ; 

        G4VSolid* left_clone  = DeepClone_r(left,  depth+1, &lrot, &ltra ) ; 
        G4VSolid* right_clone = DeepClone_r(right, depth+1, &rrot, &rtra ) ; 

        assert( lrot.isIdentity() ); 
        assert( rrot.isIdentity() ); 
        assert( ltra.x() == 0. && ltra.y() == 0. && ltra.z() == 0. );  // not expecting transforms on the left

        if( type == _G4UnionSolid )
        {
            clone = new G4UnionSolid(name, left_clone, right_clone, &rrot, rtra );   
        }
        else if( type == _G4SubtractionSolid )
        {
            clone = new G4SubtractionSolid(name, left_clone, right_clone, &rrot, rtra );   
        }
        else if( type == _G4IntersectionSolid )
        {
            clone = new G4IntersectionSolid(name, left_clone, right_clone, &rrot, rtra );   
        }
        else
        {
            std::cout 
                << "ZSolid::DeepClone FATAL unimplemented boolean type " << EntityTypeName(solid) 
                << std::endl 
                ;
            assert(0); 
        }
    }
    else
    {
        if( type == _G4Ellipsoid )
        {
            const G4Ellipsoid* ellipsoid = dynamic_cast<const G4Ellipsoid*>(solid) ; 
            clone = new G4Ellipsoid(*ellipsoid) ;
        }
        else if( type == _G4Tubs )
        {
            const G4Tubs* tubs = dynamic_cast<const G4Tubs*>(solid) ; 
            clone = new G4Tubs(*tubs) ;  
        }
        else if( type == _G4Polycone )
        {
            const G4Polycone* polycone = dynamic_cast<const G4Polycone*>(solid) ; 
            clone = new G4Polycone(*polycone) ;  
        }
        else
        {
            std::cout 
                << "ZSolid::DeepClone FATAL unimplemented prim type " << EntityTypeName(solid) 
                << std::endl 
                ;
            assert(0); 
        } 
    }
    assert(clone);
    clone->SetName(name+"_clone") ; 
    return clone ; 
}    

/**
ZSolid::classifyZCut
------------------------

Inclusion status of solid with regard to a particular zcut::

                       --- 
                        .
                        .   EXCLUDE  : zcut entirely above the solid
                        .
                        .
      +---zd+z1----+   --- 
      |            |    .   
      | . zd . . . |    .   STRADDLE : zcut within z range of solid
      |            |    .
      +---zd+z0 ---+   ---
                        .
                        .   INCLUDE  : zcut fully below the solid 
                        .
                        .
                       ---  

**/
int ZSolid::classifyZCut( double zcut ) const 
{
    double az0 = zdelta + z0() ; 
    double az1 = zdelta + z1() ; 
    assert( az1 > az0 ); 

    int cls = UNDEFINED ; 
    if(       zcut < az1 && zcut < az0 ) cls = INCLUDE ; 
    else if ( zcut < az1 && zcut > az0 ) cls = STRADDLE ; 
    else if ( zcut > az1 && zcut > az0 ) cls = EXCLUDE ; 
    return cls ; 
}  

double ZSolid::z0() const 
{
    double z1r ; 
    double z0r ; 
    getZRange( z0r, z1r ); 
    return z0r ; 
}

double ZSolid::z1() const 
{
    double z1r ; 
    double z0r ; 
    getZRange( z0r, z1r ); 
    return z1r ; 
}

void ZSolid::getZRange( double& z0, double& z1 ) const 
{
    switch(EntityType(solid))
    {
        case _G4Ellipsoid: GetZRange( dynamic_cast<G4Ellipsoid*>(solid), z0, z1 );  break ; 
        case _G4Tubs:      GetZRange( dynamic_cast<G4Tubs*>(solid)    ,  z0, z1 );  break ; 
        case _G4Polycone:  GetZRange( dynamic_cast<G4Polycone*>(solid),  z0, z1 );  break ; 
        case _G4Other:    { std::cout << "ZSolid::getZRange FATAL : not implemented for entityType " << EntityTypeName(solid) << std::endl ; assert(0) ; } ; break ;  
    }
}

void ZSolid::GetZRange( const G4Ellipsoid* const ellipsoid, double& _z0, double& _z1 )  // static 
{
    _z1 = ellipsoid->GetZTopCut() ; 
    _z0 = ellipsoid->GetZBottomCut() ;  
}
void ZSolid::GetZRange( const G4Tubs* const tubs, double& _z0, double& _z1 )  // static 
{
    _z1 = tubs->GetZHalfLength() ;  
    _z0 = -_z1 ;  
    assert( _z1 > 0. ); 
}
void ZSolid::GetZRange( const G4Polycone* const polycone, double& _z0, double& _z1 )  // static 
{
    G4PolyconeHistorical* pars = polycone->GetOriginalParameters(); 
    unsigned num_z = pars->Num_z_planes ; 
    for(unsigned i=1 ; i < num_z ; i++)
    {
        double z0 = pars->Z_values[i-1] ; 
        double z1 = pars->Z_values[i] ; 
        assert( z1 > z0 );   
    }
    _z1 = pars->Z_values[num_z-1] ; 
    _z0 = pars->Z_values[0] ;  
}


void ZSolid::applyZCut( double zcut )
{
    double az1 = zdelta + z1() ; 
    double az0 = zdelta + z0() ; 
    assert( zcut < az1 && zcut > az0 );  

    switch(EntityType(solid))
    {
        case _G4Ellipsoid: applyZCut_G4Ellipsoid(zcut);  break ; 
        case _G4Tubs:      applyZCut_G4Tubs(     zcut);  break ; 
        case _G4Polycone:  applyZCut_G4Polycone( zcut);  break ; 
        case _G4Other:    { std::cout << "ZSolid::applyZCut FATAL : not implemented for entityType " << EntityTypeName(solid) << std::endl ; assert(0) ; } ; break ;  
    }
}

/**
ZSolid::applyZCut_G4Ellipsoid
--------------------------------
     
::

    local                                             absolute 
    frame                                             frame    

    z1  +-----------------------------------------+    zd   
         \                                       /
           
            .                              .
    _________________________________________________ zcut 
                .                     .
                                 
    z0                 .      .   
                         
                                     
**/

void ZSolid::applyZCut_G4Ellipsoid( double zcut)
{  
    G4Ellipsoid* ellipsoid =  dynamic_cast<G4Ellipsoid*>(solid) ;  
    assert(ellipsoid); 

    double _z0 = z0(); 
    double _z1 = z1(); 
    assert( _z1 > _z0 ); 

    assert( zcut > zdelta + _z0 && zcut < zdelta + _z1 ) ; 
    
    double new_z1 = _z1 ; 
    double new_z0 = zcut - zdelta ;  

    ellipsoid->SetZCuts( new_z0, new_z1 ); 
}



void ZSolid::applyZCut_G4Polycone( double zcut)
{  
    G4Polycone* polycone = dynamic_cast<G4Polycone*>(solid) ;  
    assert(polycone); 
    G4PolyconeHistorical* pars = polycone->GetOriginalParameters(); 

    unsigned num_z = pars->Num_z_planes ; 
    for(unsigned i=1 ; i < num_z ; i++)
    {
        double z0 = pars->Z_values[i-1] ; 
        double z1 = pars->Z_values[i] ; 
        assert( z1 > z0 );   
    }

    assert( num_z == 2 ); 
    pars->Z_values[0] = zcut - zdelta ; 

    polycone->SetOriginalParameters(pars);
}


/**
ZSolid::applyZCut_G4Tubs
----------------------------

Cutting G4Tubs::


     zd+hz  +---------+               +---------+     new_zd + new_hz
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |             __|_________|__   new_zd
            |         |               |         |
     zd   --|---------|--             |         |
            |         |               |         |
            |         |               |         |
         .  | . . . . | . .zcut . . . +---------+ . . new_zd - new_hz  . . . . . .
            |         | 
            |         |
    zd-hz   +---------+ 


     original height:  2*hz                         
      
     cut height :     

          2*new_hz = 2*hz - (zcut-zd+hz) = hz + zd - zcut 

                        hz + zd - zcut
            new_hz =  -----------------
                             2
          
     cut position

          zcut = new_zd - new_hz 
          new_zd = zcut + new_hz  

**/

void ZSolid::applyZCut_G4Tubs( double zcut )
{  
    G4Tubs* tubs = dynamic_cast<G4Tubs*>(solid) ;  
    assert(tubs); 

    double _z1 = z1(); 
    double _z0 = z0(); 

    double hz = (_z1 - _z0)/2. ; 
    double new_hz = (hz + zdelta - zcut)/2. ;  
    double new_zdelta = zcut + new_hz ; 

    tubs->SetZHalfLength(new_hz);  
    zdelta = new_zdelta ; 
}



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


void ZSolids::dump(const char* msg) const
{
    std::cout << msg << std::endl ; 
    for(unsigned i=0 ; i < solids.size() ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        double az0 = zsi.zdelta + zsi.z0() ; 
        double az1 = zsi.zdelta + zsi.z1() ; 
        std::cout 
            << std::setw(3) << i << " " << zsi.desc() 
            << " az1 " << std::setw(10) << std::fixed << std::setprecision(3) << az1
            << " az0 " << std::setw(10) << std::fixed << std::setprecision(3) << az0
            << std::endl 
            ; 
    }
}

void ZSolids::save(const char* path) const 
{
    std::vector<double> tmp ; 
    unsigned num = solids.size() ; 
    for(unsigned i=0 ; i < num ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        tmp.push_back(zsi.z0()); 
        tmp.push_back(zsi.z1());
        tmp.push_back(zsi.zdelta); 
        tmp.push_back(0.); 

        double az0 = zsi.zdelta + zsi.z0() ; 
        double az1 = zsi.zdelta + zsi.z1() ; 
        tmp.push_back(az0);
        tmp.push_back(az1);
        tmp.push_back(0.); 
        tmp.push_back(0.); 
    }
    NP* a = NP::Make<double>( num, 2, 4 ); 
    a->read(tmp.data()); 
    a->save(path); 
}


G4VSolid* ZSolids::makeUnionSolid(const std::string& solidname) const 
{
    dump("ZSolids::makeUnionSolid"); 
    G4VSolid* solid = solids[0].solid ;
    for(unsigned i=1 ; i < solids.size() ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        solid = new G4UnionSolid(
				 solidname+zsi.label,
				 solid,     
				 zsi.solid, 
				 0,
				 G4ThreeVector(0,0,zsi.zdelta)
				 );  
    }
 
    save("/tmp/ZSolids.npy"); 

    return solid ; 
}



unsigned ZSolids::classifyZCutCount( double zcut, int q_cls )
{
    unsigned count(0); 
    for(unsigned idx=0 ; idx < solids.size() ; idx++ )
    {
        ZSolid& zsi = solids[idx] ;  
        if( zsi.classifyZCut(zcut) == q_cls ) count += 1 ; 
    }
    return count ; 
}


/**
ZSolids::makeUnionSolidZCut
-----------------------------

Hmm which solids are easy to zcut ?::

   G4Ellipsoid
   G4Polycone  
   G4Tubs (requires change in the offset, or use G4Polycone) 

**/


G4VSolid* ZSolids::makeUnionSolidZCut(const std::string& solidname, double zcut) 
{
    unsigned num_undefined = classifyZCutCount(zcut, ZSolid::UNDEFINED ); 
    unsigned num_include   = classifyZCutCount(zcut, ZSolid::INCLUDE ); 
    unsigned num_straddle  = classifyZCutCount(zcut, ZSolid::STRADDLE ); 
    unsigned num_exclude   = classifyZCutCount(zcut, ZSolid::EXCLUDE ); 
    unsigned num_solid     = num_include + num_straddle ; 
 
    std::cout 
         << "ZSolids::makeUnionSolidZCut"
         << " num_undefined " << num_undefined
         << " num_include " << num_include
         << " num_straddle " << num_straddle
         << " num_exclude " << num_exclude
         << " num_solid " << num_solid
         << std::endl 
         ;

    assert( num_undefined == 0 );  
    assert( num_solid > 0 );  

    ZSolid& zsi0 = solids[0] ;  
    G4VSolid* solid = zsi0.solid ;
    int cls = zsi0.classifyZCut(zcut ); 

    assert( cls == ZSolid::INCLUDE || cls == ZSolid::STRADDLE ); // first solid must be at z top and at least partially included 
    if( cls == ZSolid::STRADDLE ) zsi0.applyZCut( zcut ); 
    if( num_solid == 1 ) return solid ; 

    for(unsigned idx=1 ; idx < solids.size() ; idx++)
    {
        ZSolid& zsi = solids[idx] ;  
        cls = zsi.classifyZCut( zcut ); 

        if( cls == ZSolid::STRADDLE ) zsi.applyZCut( zcut ); 
        if( cls == ZSolid::INCLUDE || cls == ZSolid::STRADDLE )
        {
            solid = new G4UnionSolid(
                     solidname+zsi.label,
                     solid,     
                     zsi.solid, 
                     0,
                     G4ThreeVector(0,0,zsi.zdelta)
                     );  
        }
    }
    return solid ;
}


/**
ZSolids::getAbsoluteZ
-----------------------

Initially tried adding up the zdelta for all the solids that came 
before, but that is incorrect because the input tree structure only ever 
has one rhs for each primitive other than the leftmost which has none. 

NTreeAnalyse height 7 count 15::

    .                                                   un    

                                                  un          cy

                                          un          cy        

                                  un          zs                

                          un          cy                        

                  un          co                                

          un          zs                                        
                     (-5) 
      zs      cy                                              
             (-2.5)


NTreeAnalyse height 3 count 15::


                                  un                            

                  un                              un            

          un              un              un              un    

      zs      cy      zs      co      cy      zs      cy      cy


**/

