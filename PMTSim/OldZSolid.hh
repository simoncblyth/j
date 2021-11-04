#pragma once

class G4VSolid ; 
#include <string>
#include <vector>


struct OldZSolid  // single node holder
{
    G4VSolid*   solid ; 
    std::string label ;    // label of the CSG combination  
    double      zdelta ;   // z shift to be applied to the solid when in CSG combination 

    std::string desc() const ; 
    double z1() const ; 
    double z0() const ; 
    int classifyZCut( double zcut ) const ;

    void applyZCut(             double zcut); 
    void applyZCut_G4Ellipsoid( double zcut);
    void applyZCut_G4Tubs(      double zcut);
    void applyZCut_G4Polycone(  double zcut);

};


/**
OldZSolidList
==============

Currently the vector of ZSolid is manually collected.
That should be avoidable by traversal of the CSG tree from the root. 
Doing that would allow to eliminate ZSolids entirely and 
allow to support CSG trees more complicated that current 
sequence of unions. 

**/

struct OldZSolidList
{
    std::vector<OldZSolid> solids ; 

    unsigned classifyZCutCount( double zcut, int q_cls ); 
    G4VSolid* makeUnionSolid(const std::string& solidname) const ; 
    G4VSolid* makeUnionSolidZCut(const std::string& solidname, double zcut ) ;  // non-const because cuts straddle solids 
    void dump(const char* msg) const ; 
    void save(const char* path) const ; 
}; 



