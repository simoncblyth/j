#include <cstdlib>
#include "Hamamatsu_R12860_PMTSolid.hh"
#include "ZSolid.h"

double atof_(char* s_val)
{
    std::istringstream iss(s_val);
    double d ; 
    iss >> d ;  
    return d ; 
}

double getenvdouble(const char* key, double fallback)
{
    char* s_val = getenv(key);
    return s_val ? atof_(s_val) : fallback ; 
}

int main(int argc, char** argv)
{
    setenv("JUNO_PMT20INCH_POLYCONE_NECK","ENABLED",1); 

    Hamamatsu_R12860_PMTSolid* m_pmtsolid_maker = new Hamamatsu_R12860_PMTSolid();

    G4VSolid* body_solid = m_pmtsolid_maker->GetSolid("_body_solid"); 

    ZSolid::Draw(body_solid, "body_solid");   

    double zcut = getenvdouble("ZCUT", -400. ); 

    std::cout << " zcut " << zcut << std::endl ; 

    G4VSolid* body_solid_zcut = ZSolid::ApplyZCutTree(body_solid, zcut, false ); 

    ZSolid::Draw(body_solid_zcut, "body_solid_zcut");   

    return 0 ; 
}

