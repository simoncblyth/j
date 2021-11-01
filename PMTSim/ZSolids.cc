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
       << " type  " << std::setw(15) << type 
       << " label " << std::setw(10) << label 
       << " zdelta " << std::setw(10) << std::fixed << std::setprecision(3) << zdelta 
       << " z1 " << std::setw(10) << std::fixed << std::setprecision(3) << z1
       << " z0 " << std::setw(10) << std::fixed << std::setprecision(3) << z0
       ;
    std::string s = ss.str(); 
    return s ; 
}

bool ZSolid::is_ellipsoid() const { return strcmp(type.c_str(), "G4Ellipsoid") == 0 ; }
bool ZSolid::is_tubs()      const { return strcmp(type.c_str(), "G4Tubs") == 0 ; }
bool ZSolid::is_polycone()  const { return strcmp(type.c_str(), "G4Polycone") == 0 ; }


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

double ZSolids::getAbsoluteZ( unsigned idx, int type ) const 
{
    assert( idx < solids.size() ); 
    const ZSolid& zsi = solids[idx] ; 
    double az = zsi.zdelta + ( type == 0 ? zsi.z0  : zsi.z1) ; 
    return az ; 
}

double ZSolids::getAbsoluteZ0( unsigned idx) const { return getAbsoluteZ(idx, 0); } 
double ZSolids::getAbsoluteZ1( unsigned idx) const { return getAbsoluteZ(idx, 1); } 

void ZSolids::dump(const char* msg) const
{
    std::cout << msg << std::endl ; 
    for(unsigned i=0 ; i < solids.size() ; i++)
    {
        const ZSolid& zsi = solids[i] ; 
        double az0 = getAbsoluteZ0(i); 
        double az1 = getAbsoluteZ1(i); 
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
        tmp.push_back(zsi.z0); 
        tmp.push_back(zsi.z1);
        tmp.push_back(zsi.zdelta); 
        tmp.push_back(0.); 

        double az0 = getAbsoluteZ0(i); 
        double az1 = getAbsoluteZ1(i); 
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

/**
ZSolids::makeUnionSolidZCut
-----------------------------

Hmm which solids are easy to zcut ?::

   G4Ellipsoid
   G4Polycone  
   G4Tubs (requires change in the offset, or use G4Polycone) 


             ----  cut z 
 

      + az1
      |      ----  straddle z 
      |  
      + az0

             ----  full z

**/


int ZSolids::classifyZCut( unsigned idx, double zcut )
{
    assert( idx < solids.size() ); 
    const ZSolid& zsi = solids[idx] ; 
    double az0 = zsi.zdelta + zsi.z0 ; 
    double az1 = zsi.zdelta + zsi.z1 ; 
    assert( az1 > az0 ); 

    int cls = UNDEFINED ; 
    if(       zcut < az1 && zcut < az0 ) cls = INCLUDE ; 
    else if ( zcut < az1 && zcut > az0 ) cls = STRADDLE ; 
    else if ( zcut > az1 && zcut > az0 ) cls = EXCLUDE ; 
    return cls ; 
}  

unsigned ZSolids::classifyZCutCount( double zcut, int q_cls )
{
    unsigned count(0); 
    for(unsigned idx=0 ; idx < solids.size() ; idx++ )
    {
        int cls = classifyZCut(idx, zcut) ; 
        if( cls == q_cls ) count += 1 ; 
    }
    return count ; 
}


G4VSolid* ZSolids::makeUnionSolidZCut(const std::string& solidname, double zcut) 
{
    unsigned num_undefined = classifyZCutCount(zcut,  UNDEFINED ); 
    unsigned num_include  = classifyZCutCount(zcut,  INCLUDE ); 
    unsigned num_straddle = classifyZCutCount(zcut, STRADDLE ); 
    unsigned num_exclude  = classifyZCutCount(zcut,  EXCLUDE ); 
    unsigned num_solid = num_include + num_straddle ; 
 
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
    int cls = classifyZCut(0, zcut ); 

    assert( cls == INCLUDE || cls == STRADDLE ); // first solid must be at z top and at least partially included 
    if( cls == STRADDLE ) applyZCut( 0, zcut ); 
    if( num_solid == 1 ) return solid ; 

    for(unsigned idx=1 ; idx < solids.size() ; idx++)
    {
        ZSolid& zsi = solids[idx] ;  
        cls = classifyZCut( idx, zcut ); 

        if( cls == STRADDLE ) applyZCut( idx, zcut ); 
        if( cls == INCLUDE || cls == STRADDLE )
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


void ZSolids::applyZCut( unsigned idx, double zcut )
{
    assert( idx < solids.size() ); 
    ZSolid& zsi = solids[idx] ;  

    double az0 = getAbsoluteZ0(idx); 
    double az1 = getAbsoluteZ1(idx); 
    assert( zcut < az1 && zcut > az0 );  
    
    if( zsi.is_ellipsoid() )
    {
        applyZCut_G4Ellipsoid(idx, zcut); 
    }   
    else if( zsi.is_tubs() )
    {
        applyZCut_G4Tubs(idx, zcut) ; 
    }
    else if( zsi.is_polycone() )
    {
        applyZCut_G4Polycone(idx, zcut) ;  
    }
    else
    {
        std::cout << "ZSolids::applyZCut FATAL : not implemented for type " << zsi.type << std::endl ; 
        assert(0); 
    }
}

/**
ZSolids::applyZCut_G4Ellipsoid
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

void ZSolids::applyZCut_G4Ellipsoid( unsigned idx, double zcut)
{  
    ZSolid& zsi = solids[idx] ;  
    G4Ellipsoid* ellipsoid =  dynamic_cast<G4Ellipsoid*>(zsi.solid) ;  
    assert(ellipsoid); 

    double zd = zsi.zdelta ;
    double z1 = zsi.z1 ; 
    double z0 = zsi.z0 ; 
    assert( z1 > z0 ); 
   
    assert( zcut > zd + z0 && zcut < zd + z1 ) ; 
    
    double new_z1 = z1 ; 
    double new_z0 = zcut - zd ;  

    ellipsoid->SetZCuts( new_z0, new_z1 ); 
}


void ZSolids::applyZCut_G4Polycone( unsigned idx, double zcut)
{  
    ZSolid& zsi = solids[idx] ;  
    G4Polycone* polycone = dynamic_cast<G4Polycone*>(zsi.solid) ;  
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
    pars->Z_values[0] = zcut - zsi.zdelta ; 

    polycone->SetOriginalParameters(pars);
}


/**
ZSolids::applyZCut_G4Tubs
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

void ZSolids::applyZCut_G4Tubs( unsigned idx, double zcut )
{  
    ZSolid& zsi = solids[idx] ;  
    G4Tubs* tubs = dynamic_cast<G4Tubs*>(zsi.solid) ;  
    assert(tubs); 

    double zd = zsi.zdelta ; 
    double z0 = zsi.z0 ; 
    double z1 = zsi.z1 ; 

    double hz = (z1 - z0)/2. ; 
    double new_hz = (hz + zd - zcut)/2. ;  
    double new_zd = zcut + new_hz ; 

    tubs->SetZHalfLength(new_hz);  
    zsi.zdelta = new_zd ; 
}

 
