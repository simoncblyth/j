#include <cassert>
#include "PMTSim.hh"
#include "ZSolid.h"

int main(int argc, char** argv)
{

    //const char* default_name = "maker_body_solid_zcut-183.2246" ; 

    //const char* default_name = "hmsk_solidMask" ; 
    const char* default_name = "hmsk_solidMaskTail" ; 

    const char* name = argc > 1 ? argv[1] : default_name ;  
    G4VSolid* solid = PMTSim::GetSolid(name); 
    ZSolid::Draw(solid); 
    return 0 ; 
}
