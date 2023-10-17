/**
PMTSim_GetSolid_test.cc
========================

**/

#include "ssys.h"
#include "G4VSolid.hh"
#include "PMTSim.hh"

int main()
{
    const char* geom = ssys::getenvvar("GEOM", "xjacSolid" );  
    G4VSolid* solid = PMTSim::GetSolid(geom); 
    assert( solid ); 
    G4cout << *solid << std::endl ; 
 
    return 0 ; 
}


