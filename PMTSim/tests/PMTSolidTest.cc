#include <cstdlib>
#include <iostream>
#include <iomanip>

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


/**
repeat_draw
-------------

Used for debugging some SEGV 

**/

void repeat_ZSolid_Draw( G4VSolid* solid, const char* msg, unsigned num_repeats )
{
    for(unsigned i=0 ; i < num_repeats ; i++)
    {
        ZSolid::Draw(solid, msg );   
        std::cout << " i " << std::setw(6) << i << std::endl ; 
    }
}


int main(int argc, char** argv)
{
    Hamamatsu_R12860_PMTSolid* m_pmtsolid_maker = new Hamamatsu_R12860_PMTSolid();

    G4VSolid* body_solid = m_pmtsolid_maker->GetSolid("_body_solid"); 

    std::cout << " body_solid " << body_solid << std::endl ; 

    //ZSolid::Draw(body_solid, "body_solid");
   
    repeat_ZSolid_Draw( body_solid, "body_solid", 1000 ); 


    double zcut = getenvdouble("ZCUT", -200. ); 

    std::cout << " zcut " << zcut << std::endl ; 

    G4VSolid* body_solid_zcut = ZSolid::ApplyZCutTree(body_solid, zcut ); 

    std::cout << " body_solid_zcut " << body_solid_zcut << std::endl ; 

    //ZSolid::Draw(body_solid_zcut, "body_solid_zcut");   

    repeat_ZSolid_Draw( body_solid_zcut, "body_solid_zcut", 1000 ); 

    std::cout << "after ZSolid::Draw " << std::endl ; 


    return 0 ; 
}

