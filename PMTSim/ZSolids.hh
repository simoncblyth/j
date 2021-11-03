#pragma once

class G4VSolid ; 
#include <string>
#include <map>
#include <vector>

struct ZSolid
{
    G4VSolid*   solid ; 
    std::string label ;    // label of the CSG combination  
    double      zdelta ;   // z shift to be applied to the solid when in CSG combination 

    double z1() const ; 
    double z0() const ; 

    enum { _G4Other, _G4Ellipsoid, _G4Tubs, _G4Polycone, _G4UnionSolid, _G4SubtractionSolid, _G4IntersectionSolid, _G4DisplacedSolid } ; 
    static int         EntityType(    const G4VSolid* const solid) ; 
    static const char* EntityTypeName(const G4VSolid* const solid) ; 
    static bool        IsBooleanSolid(const G4VSolid* const solid) ;
    static bool        IsDisplacedSolid(const G4VSolid* const solid) ;

    static void GetDisplacedSolidTransform( G4RotationMatrix* rot, G4ThreeVector* tla, const G4DisplacedSolid* disp ); 
    static void RecursiveDisplacement( G4RotationMatrix* rot, G4ThreeVector* tla, const G4VSolid* node, std::map<const G4VSolid*,const G4VSolid*>* parentmap );  

    enum { UNDEFINED, INCLUDE, STRADDLE, EXCLUDE } ; 
    int classifyZCut( double zcut ) const ;

    void getZRange( double& z0, double& z1 ) const ; 
    static void GetZRange( const G4Ellipsoid* const ellipsoid, double& z0, double& z1 );
    static void GetZRange( const G4Tubs*      const tubs     , double& z0, double& z1 ); 
    static void GetZRange( const G4Polycone*  const polycone , double& z0, double& z1 ); 

    std::string desc() const ; 

    void applyZCut(             double zcut); 
    void applyZCut_G4Ellipsoid( double zcut);
    void applyZCut_G4Tubs(      double zcut);
    void applyZCut_G4Polycone(  double zcut);

    static void      DumpTree(   const char* msg, const G4VSolid* const solid); 
    static void      DumpTree_r( const char* msg, const G4VSolid* const solid, int depth ); 

    static void DumpUp(const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap  ); 
    static void DumpUp_r(const G4VSolid* solid, int depth, std::map<const G4VSolid*,const G4VSolid*>* parentmap );


    static G4VSolid* DeepClone(   const G4VSolid* solid, std::map<const G4VSolid*,const G4VSolid*>* parentmap=nullptr ); 
    static G4VSolid* DeepClone_r( const G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla, std::map<const G4VSolid*,const G4VSolid*>* parentmap ); 
    static G4VSolid* BooleanClone( const  G4VSolid* solid, int depth, G4RotationMatrix* rot, G4ThreeVector* tla, std::map<const G4VSolid*,const G4VSolid*>* parentmap ); 
    static G4VSolid* PrimitiveClone( const  G4VSolid* solid ); 
}; 



/**
ZSolids
=========

Currently the vector of ZSolid is manually collected.
That should be avoidable by traversal of the CSG tree from the root. 
Doing that would allow to eliminate ZSolids entirely and 
allow to support CSG trees more complicated that current 
sequence of unions. 

**/

struct ZSolids 
{
    std::vector<ZSolid> solids ; 

    unsigned classifyZCutCount( double zcut, int q_cls ); 
    G4VSolid* makeUnionSolid(const std::string& solidname) const ; 
    G4VSolid* makeUnionSolidZCut(const std::string& solidname, double zcut ) ;  // non-const because cuts straddle solids 
    void dump(const char* msg) const ; 
    void save(const char* path) const ; 
}; 



