#include <iostream>
#include "PMTSim.hh"

void test_GetSolid()
{
    const char* name = "PMTSim_Z" ; 
    G4VSolid* solid = PMTSim::GetSolid(name) ; 
    std::cout << " solid " << solid << std::endl ; 
}

void test_GetZCutSolid(double zcut)
{
    std::cout << "test_GetZCutSolid " << zcut << std::endl ; 
    const char* name = "PMTSim_Z" ; 
    G4VSolid* solid = PMTSim::GetZCutSolid(name, zcut) ; 
    std::cout << " solid " << solid << std::endl ; 
}

int main(int argc, char** argv)
{
    // test_GetSolid(); 
    test_GetZCutSolid(-300.); 
    return 0 ; 
}
