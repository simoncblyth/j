#include <cassert>
#include <cstdio>

#include "SSys.hh"
#include "PMTSim.hh"
#include "X4SolidTree.hh"

int main(int argc, char** argv)
{
    //const char* default_geom = "maker_body_solid_zcut-183.2246" ; 
    //const char* default_geom = "hmsk_solidMask" ; 
    const char* default_geom = "hmsk_solidMaskTail" ; 

    const char* geom = SSys::getenvvar("GEOM", default_geom );  
    const char* name = argc > 1 ? argv[1] : geom ; 

    printf("default_geom %s geom %s name %s \n", default_geom, geom, name ); 
    printf("(arg overrides GEOM envvar value, envvar value overrides hardcoded default_geom)\n"); 
 
    G4VSolid* solid = PMTSim::GetSolid(name); 
    X4SolidTree::Draw(solid); 
    return 0 ; 
}
