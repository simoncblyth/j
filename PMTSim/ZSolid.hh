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
    std::map<const G4VSolid*, const G4VSolid*>* parentmap ; 
    std::map<const G4VSolid*, int>*             zclsmap ; 


    static G4VSolid* MakeZCut( const G4VSolid* original, double zcut ); 

    // object methods
    ZSolid(const G4VSolid* root ); 
    void init(); 

    double getZ(const G4VSolid* node ) const ; 
    void   getTreeTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node ) const ; 

    void classifyTree( double zcut ); 
    void classifyTree_r( const G4VSolid* node_, int depth, double zcut ); 

    void cutTree(double zcut);
    void cutTree_r( G4VSolid* node_, int depth, double zcut ); 


    void dumpUp(const char* msg="ZSolid::dumpUp") const ; 
    void dumpUp_r(const G4VSolid* node, int depth) const ; 

    void dumpTree(const char* msg="ZSolid::dumpTree" ) const ; 
    void dumpTree_r( const G4VSolid* node, int depth ) const ; 


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

    static const char* UNDEFINED_ ; 
    static const char* INCLUDE_; 
    static const char* STRADDLE_ ; 
    static const char* EXCLUDE_; 
    static const char* ClassifyName( int zcls ); 


    // simple static convenience functions
    static int    ClassifyZCut( double az0, double az1, double zcut ); 

    // basic solid functions
    static int             EntityType(      const G4VSolid* solid) ; 
    static const char*     EntityTypeName(  const G4VSolid* solid) ; 
    static bool            IsBooleanSolid(  const G4VSolid* solid) ;
    static bool            IsDisplacedSolid(const G4VSolid* solid) ;

    // navigation
    static const G4VSolid* Left(  const G4VSolid* node) ;
    static const G4VSolid* Right( const G4VSolid* node) ;
    static const G4VSolid* Moved( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node) ;

    static       G4VSolid* Left_(       G4VSolid* node) ;
    static       G4VSolid* Right_(      G4VSolid* node) ;
    static       G4VSolid* Moved_( G4RotationMatrix* rot, G4ThreeVector* tla,      G4VSolid* node) ;

    // local node frame access 
    static void ZRange( double& z0, double& z1,  const G4VSolid* solid ) ; 
    static bool CanZ(   const G4VSolid* solid ); 
    static void GetZRange( const G4Ellipsoid* const ellipsoid, double& z0, double& z1 );
    static void GetZRange( const G4Tubs*      const tubs     , double& z0, double& z1 ); 
    static void GetZRange( const G4Polycone*  const polycone , double& z0, double& z1 ); 

    // tree cloning methods
    static G4VSolid* DeepClone(    const G4VSolid* solid ); 
    static G4VSolid* DeepClone_r(  const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 
    static G4VSolid* BooleanClone( const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla ); 
    static void      CheckBooleanClone( const G4VSolid* clone, const G4VSolid* left, const G4VSolid* right ); 
    static G4VSolid* PrimitiveClone( const  G4VSolid* solid ); 

    // recursive operations
    typedef std::map<const G4VSolid*, const G4VSolid*> MSS ; 
    static MSS* MakeParentMap( const G4VSolid* root ); 
    static void FillParentMap_r( const G4VSolid* solid, MSS* parentmap ); 

    static void ApplyZCut(             G4VSolid* node, double local_zcut); 
    static void ApplyZCut_G4Ellipsoid( G4VSolid* node, double local_zcut);
    static void ApplyZCut_G4Tubs(      G4VSolid* node, double local_zcut);
    static void ApplyZCut_G4Polycone(  G4VSolid* node, double local_zcut);

}; 


