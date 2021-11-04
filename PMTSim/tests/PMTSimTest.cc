#include <iostream>
#include <vector>
#include "PMTSim.hh"


int main(int argc, char** argv)
{
    std::vector<const char*> names = { 
        "PMTSim_Z", 
    //    "PMTSim_Z-200",
    //    "PMTSim_Z-300",
    //    "PMTSim_Z-400"
    };

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i] ; 
        G4VSolid* solid = PMTSim::GetSolid(name) ; 
        std::cout 
            << "PMTSimTest"
            << " name " << name 
            << " solid " << solid 
            << std::endl
            ; 
    } 
    return 0 ; 
}
