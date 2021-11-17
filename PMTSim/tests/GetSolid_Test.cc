#include <cassert>
#include "PMTSim.hh"
#include "ZSolid.hh"

int main(int argc, char** argv)
{
    //const char* default_name = "maker_body_solid" ; 
    const char* default_name = "body_solid" ; 
    const char* name = argc > 1 ? argv[1] : default_name ;  

    PMTSim::SetEnvironmentSwitches(name);  
    G4VSolid* solid = PMTSim::GetSolid_(name); 
    ZSolid::Draw(solid); 
    return 0 ; 
}
