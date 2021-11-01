#pragma once

class G4VSolid ; 
#include <string>
#include <vector>

struct ZSolid
{
    std::string type ; 

    G4VSolid*   solid ; 

    // local z-range of solid without any shifts applied, z1 > z0 
    double      z0 ;     
    double      z1 ;    

    // label of the CSG combination  
    std::string label ; 

    // z shift to be applied to the solid when in CSG combination 
    double      zdelta ; 

    std::string desc() const ; 
    bool is_ellipsoid() const ; 
    bool is_polycone() const ; 
    bool is_tubs() const ; 
}; 

struct ZSolids 
{
    std::vector<ZSolid> solids ; 


    enum { UNDEFINED, INCLUDE, STRADDLE, EXCLUDE } ; 
    int classifyZCut( unsigned idx, double zcut );
    unsigned classifyZCutCount( double zcut, int q_cls ); 

    G4VSolid* makeUnionSolid(const std::string& solidname) const ; 
    G4VSolid* makeUnionSolidZCut(const std::string& solidname, double zcut ) ;  // non-const because cuts straddle solids 

    double getAbsoluteZ( unsigned idx, int type ) const ; 
    double getAbsoluteZ0( unsigned idx) const ; 
    double getAbsoluteZ1( unsigned idx) const ; 

    void dump(const char* msg) const ; 
    void save(const char* path) const ; 

    void applyZCut(             unsigned idx, double zcut); 
    void applyZCut_G4Ellipsoid( unsigned idx, double zcut);
    void applyZCut_G4Tubs(      unsigned idx, double zcut);
    void applyZCut_G4Polycone(  unsigned idx, double zcut);
}; 



