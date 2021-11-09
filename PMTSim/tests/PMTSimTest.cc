#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include "PMTSim.hh"

void test_GetSolid()
{
    std::vector<const char*> names = { 
    //    "PMTSim_Z", 
    //    "PMTSim_Zclone", 
    //    "PMTSim_Z-200",
    //    "PMTSim_Z-300",
    //    "PMTSim_Z-400"
          "PMTSim_Z-400"
    };

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i] ; 
        std::cout << "[ PMTSimTest" << " name " << name << std::endl ; 
        const G4VSolid* solid = PMTSim::GetSolid(name) ; 
        std::cout << "] PMTSimTest" << " name " << name << " solid " << solid << std::endl ; 
    } 
}


void test_GetLV()
{
    G4LogicalVolume* lv = PMTSim::GetLV("lv"); 
    assert( lv ); 
}

void test_GetPV()
{
    G4VPhysicalVolume* pv = PMTSim::GetPV("pv"); 
    assert( pv ); 
}




int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_SIMPLIFY_CSG","ENABLED",1);

    //test_GetSolid(); 
    //test_GetLV(); 
    test_GetPV(); 

    return 0 ; 
}
