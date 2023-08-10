#include <cassert>
#include <cstdio>

#include "ssys.h"
#include "PMTSim.hh"
#include "ZSolid.h"

int main(int argc, char** argv)
{
    //const char* default_geom = "maker_body_solid_zcut-183.2246" ; 

    const char* default_geom = "hmskSolidMask" ; 
    //const char* default_geom = "hmskSolidMaskTail" ; 

    const char* geom = ssys::getenvvar("GEOM", default_geom );  
    const char* name = argc > 1 ? argv[1] : geom ; 

    printf("default_geom %s geom %s name %s \n", default_geom, geom, name ); 
    printf("(arg overrides GEOM envvar value, envvar value overrides hardcoded default_geom)\n"); 
 
    G4VSolid* solid = PMTSim::GetSolid(name); 
    ZSolid::Draw(solid); 
    return 0 ; 
}
