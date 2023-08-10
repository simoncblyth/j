#include <cassert>
#include <iostream>
#include "ssys.h"
#include "PMTSim.hh"

int main(int argc, char** argv)
{
    const char* geom_default = "nnvtLogicalPmt" ; 
    //const char* geom_default = "tub3LogicalPmt" ; 
    const char* geom = ssys::getenvvar("GEOM", geom_default );

    G4LogicalVolume* lv = PMTSim::GetLV(geom);

    std::cout << "GetLVTest.main"
       << " geom[" << ( geom ? geom : "-" ) << "]"  
       << " lv " << ( lv ? "YES" : "NO " ) 
       << std::endl
       ; 

    assert(lv); 

    return 0 ; 
}
