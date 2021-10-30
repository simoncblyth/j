#include <iostream>

#include "HamamatsuR12860PMTManager.hh"
//#include "Hamamatsu_R12860_PMTSolid.hh"

int main()
{
    const char* label = "PMTSim" ; 
    HamamatsuR12860PMTManager* mgr = new HamamatsuR12860PMTManager(label) ; 
    std::cout << " mgr " << mgr << std::endl ; 

    G4LogicalVolume* lv = mgr->getLV(); 
    std::cout << " lv " << lv << std::endl ; 

    //Hamamatsu_R12860_PMTSolid* m_pmtsolid_maker = new Hamamatsu_R12860_PMTSolid(); 
    //std::cout << " m_pmtsolid_maker " << m_pmtsolid_maker << std::endl ; 


    return 0 ; 
}
