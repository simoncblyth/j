#pragma once

class G4VSolid ; 
#include <string>
#include <vector>

struct ZSolid
{
    G4VSolid*   solid ; 

    // local z-range of solid without any shifts applied, z1 > z0 
    double      z0 ;     
    double      z1 ;    

    // label of the CSG combination  
    std::string label ; 

    // z shift to be applied to the solid when in CSG combination 
    double      zdelta ; 

    std::string desc() const ; 

}; 

struct ZSolids 
{
    std::vector<ZSolid> solids ; 

    G4VSolid* makeUnionSolid(const std::string& solidname, double zcut ) const ; 
    double getAbsoluteZShift(unsigned idx) const ; 

    void dump(const char* msg) const ; 
}; 



