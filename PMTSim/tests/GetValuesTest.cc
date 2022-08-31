#include "SSys.hh"
#include "NP.hh"
#include "PMTSim.hh"

int main(int argc, char** argv)
{
    const char* default_geom = "nmskSolidMask" ; 
    const char* geom = SSys::getenvvar("GEOM", default_geom );  
    const char* name = argc > 1 ? argv[1] : geom ; 
 
    NP* vv = PMTSim::GetValues(name); 
    std::cout << " name " << name << " vv " << ( vv ? vv->sstr() : "-" ) << std::endl ; 
    if(vv == nullptr) return 1 ; 

    std::cout << vv->descValues() << std::endl ; 
    std::cout << vv->descMeta() << std::endl ; 

    return 0 ; 
}
