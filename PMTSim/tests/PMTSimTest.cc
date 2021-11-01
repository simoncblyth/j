#include <iostream>
#include "PMTSim.hh"

int main(int argc, char** argv)
{
    const char* name = "PMTSim_Z" ; 

    G4VSolid* solid = PMTSim::GetSolid(name) ; 
    
    std::cout << " solid " << solid << std::endl ; 

    return 0 ; 
}
