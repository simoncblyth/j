#include <iostream>
#include <cassert>
#include <cstdlib>
#include <vector>
#include "PMTSim.hh"

void test_GetMakerSolid()
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
        const G4VSolid* solid = PMTSim::GetMakerSolid(name) ; 
        std::cout << "] PMTSimTest" << " name " << name << " solid " << solid << std::endl ; 
    } 
}


void test_getLV(PMTSim* ps)
{
    std::cout << "test_getLV " << std::endl ; 

    std::vector<const char*> names = { 
        "logical_pmt", 
        "body_log", 
        "inner1_log",
        "inner2_log",
        "dynode_log",
        "logical_cover"
    };

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i] ; 
        G4LogicalVolume* lv = ps->getLV(name); 
        std::cout << " name " << name << " lv " << lv << std::endl ; 
    } 
}

void test_getPV(PMTSim* ps)
{
    std::cout << "test_getPV " << std::endl ; 

    std::vector<const char*> names = { 
        "body_phys", 
        "inner1_phys", 
        "inner2_phys",
        "dynode_phys",
    };

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i] ; 
        G4VPhysicalVolume* pv = ps->getPV(name); 
        std::cout << " name " << name << " pv " << pv << std::endl ; 
    } 
}

void test_getSolid(PMTSim* ps)
{
    std::cout << "test_getSolid " << std::endl ; 
    std::vector<const char*> names = { 
        "pmt_solid", 
        "body_solid", 
        "inner_solid", 
        "inner1_solid", 
        "inner2_solid" 
    };

    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i] ; 
        const G4VSolid* solid = ps->getSolid(name) ; 
        std::cout << " name " << name << " solid " << solid << std::endl ; 
    } 
}

void test_GetSolid(const char* name)
{
    const G4VSolid* solid = PMTSim::GetSolid(name); 
    std::cout << " name " << name << " solid " << solid << std::endl ; 
    assert( solid ); 
}


int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_SIMPLIFY_CSG","ENABLED",1);
    setenv("JUNO_PMT20INCH_NOT_USE_REAL_SURFACE", "ENABLED", 1); 

    const char* name = argc > 1 ? argv[1] : "body_solid" ; 

    test_GetSolid(name); 
 
    //PMTSim ps ; 
    //test_GetMakerSolid(&ps); 
    //test_getLV(&ps); 
    //test_getPV(&ps); 
    //test_getSolid(&ps); 

    return 0 ; 
}
