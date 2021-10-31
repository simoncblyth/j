#include <iostream>
#include "PMTSim.hh"

int main(int argc, char** argv)
{
    G4VSolid* solid = PMTSim::GetSolid() ; 
    
    std::cout << " solid " << solid << std::endl ; 

    return 0 ; 
}
