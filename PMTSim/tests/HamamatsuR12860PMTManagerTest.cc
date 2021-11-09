#include <cassert>
#include <cstdlib>
#include <iostream>
#include "HamamatsuR12860PMTManager.hh"

int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_SIMPLIFY_CSG","ENABLED",1); 

    HamamatsuR12860PMTManager* mgr = new HamamatsuR12860PMTManager("Ham");  

    G4LogicalVolume* lv = mgr->getLV(); 

    assert( lv ); 

    std::cout << " lv " << lv << std::endl ; 

    return 0 ; 
}
