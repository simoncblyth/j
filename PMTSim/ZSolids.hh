#pragma once

class G4VSolid ; 
#include <string>
#include <vector>

struct ZSolid
{
    G4VSolid*   solid ; 
    std::string label ;    // label of the CSG combination  
    double      zdelta ;   // z shift to be applied to the solid when in CSG combination 


    double z1() const ; 
    double z0() const ; 


    enum { _G4Other, _G4Ellipsoid, _G4Tubs, _G4Polycone } ; 
    static int         EntityType(    const G4VSolid* const solid) ; 
    static const char* EntityTypeName(const G4VSolid* const solid) ; 

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
}; 



struct ZSolids 
{
    std::vector<ZSolid> solids ; 

    unsigned classifyZCutCount( double zcut, int q_cls ); 

    G4VSolid* makeUnionSolid(const std::string& solidname) const ; 
    G4VSolid* makeUnionSolidZCut(const std::string& solidname, double zcut ) ;  // non-const because cuts straddle solids 

    void dump(const char* msg) const ; 
    void save(const char* path) const ; 

}; 



