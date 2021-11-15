#include <cassert>
#include "PMTSim.hh"
#include "ZSolid.hh"

int main(int argc, char** argv)
{
    const char* name = argc > 1 ? argv[1] : "maker_body_solid_zcut-183.2246" ;  
    G4VSolid* solid = PMTSim::GetSolid(name); 
    ZSolid::Draw(solid); 
    return 0 ; 
}
