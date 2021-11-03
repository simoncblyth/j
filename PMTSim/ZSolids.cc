#include <cassert>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "G4UnionSolid.hh"
#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"

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

const char* ZSolid::EntityTypeName(const G4VSolid* const solid)  
{
    G4GeometryType type = solid->GetEntityType();  // G4GeometryType typedef for G4String
    return type.c_str(); 
}

int ZSolid::EntityType(const G4VSolid* const solid)
{
    const char* name = EntityTypeName(solid); 
    int type = _G4Other ; 
    if( strcmp(name, "G4Ellipsoid") == 0 ) type = _G4Ellipsoid ; 
    if( strcmp(name, "G4Tubs") == 0 )      type = _G4Tubs ; 
    if( strcmp(name, "G4Polycone") == 0 )  type = _G4Polycone ; 
    return type ; 
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

