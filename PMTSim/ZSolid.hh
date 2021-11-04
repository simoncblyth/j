#pragma once

class G4VSolid ; 
class G4Ellipsoid ; 
class G4Tubs ; 
class G4Polycone ; 
class G4DisplacedSolid ; 

#include "G4RotationMatrix.hh" 
#include "G4ThreeVector.hh" 

#include <string>
#include <map>
#include <vector>

/**
ZSolid : CSG tree manipulations  
=================================



**/

struct ZSolid   
{
    // members
    const G4VSolid* original ; 
    G4VSolid*       root ;     // DeepClone of original, which should be identical to original AND fully independent 

    std::map<const G4VSolid*, const G4VSolid*> parentmap ; 


    // object methods
    ZSolid(const G4VSolid* root ); 
    void init(); 

    void getZRange( double& z0, double& z1 ) const ; 


    // enumerations
    enum { 
        _G4Other, 
        _G4Ellipsoid, 
        _G4Tubs, 
        _G4Polycone, 
        _G4UnionSolid, 
        _G4SubtractionSolid, 
        _G4IntersectionSolid, 
        _G4DisplacedSolid 
     }; 

    enum { 
       UNDEFINED=0, 
         INCLUDE=1<<0, 
        STRADDLE=1<<1, 
         EXCLUDE=1<<2 
     }; 

    // simple static convenience functions
    static int    ClassifyZCut( double az0, double az1, double zcut ); 

    // static solid functions
    static int             EntityType(      const G4VSolid* const solid) ; 
    static const char*     EntityTypeName(  const G4VSolid* const solid) ; 
    static bool            IsBooleanSolid(  const G4VSolid* const solid) ;
    static bool            IsDisplacedSolid(const G4VSolid* const solid) ;
    static const G4VSolid* GetLeft(         const G4VSolid* const solid) ;
    static const G4VSolid* GetRight(        const G4VSolid* const solid) ;

    // recursive dumpers
    static void      DumpTree(   const G4VSolid* solid, const char* msg="ZSolid::DumpTree" ); 
    static void      DumpTree_r( const G4VSolid* solid, int depth ); 

    static void DumpUp(const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap  ); 
    static void DumpUp_r(const G4VSolid* solid, int depth, std::map<const G4VSolid*,const G4VSolid*>* parentmap );

    // recursive operations
    static void FillParentMap(   const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap ); 
    static void FillParentMap_r( const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap ); 

    static void GetDisplacedSolidTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4DisplacedSolid* disp ); 
    static void RecursiveDisplacement(      G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node, std::map<const G4VSolid*,const G4VSolid*>* parentmap );  


    static void GetZRange( const G4Ellipsoid* const ellipsoid, double& z0, double& z1 );
    static void GetZRange( const G4Tubs*      const tubs     , double& z0, double& z1 ); 
    static void GetZRange( const G4Polycone*  const polycone , double& z0, double& z1 ); 
    static double GetZ( const G4VSolid* const solid, int idx) ; 

    // tree cloning methods
    static G4VSolid* DeepClone(    const G4VSolid* solid ); 
    static G4VSolid* DeepClone_r(  const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 
    static G4VSolid* BooleanClone( const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 
    static void      CheckBooleanClone( const G4VSolid* clone, const G4VSolid* left, const G4VSolid* right ); 
    static G4VSolid* PrimitiveClone( const  G4VSolid* solid ); 
}; 


