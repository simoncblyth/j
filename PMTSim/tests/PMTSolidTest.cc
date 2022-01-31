#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "Hamamatsu_R12860_PMTSolid.hh"
#include "NNVT_MCPPMT_PMTSolid.hh"
#include "X4SolidTree.hh"

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

void repeat_X4SolidTree_Draw( G4VSolid* solid, const char* msg, unsigned num_repeats )
{
    for(unsigned i=0 ; i < num_repeats ; i++)
    {
        X4SolidTree::Draw(solid, msg );   
        std::cout << " i " << std::setw(6) << i << std::endl ; 
    }
}





int main(int argc, char** argv)
{
    //int repeat = 1000 ; 
    int repeat = 0 ; 

    const char* name = "nnvt_body_solid" ; 
    //const char* name = "hama_body_solid" ; 

/* 
Trying to switch on the old obsolete torus neck gives X4SolidTree assert for both hama and nnvt::

   X4SolidTree::BooleanClone expect_tla ERROR (not expecting more than one level of translation) 
   X4SolidTree::BooleanClone tla( 0 0 -193.789) 

    int overwrite = 1 ; 
    setenv("JUNO_PMT20INCH_OBSOLETE_TORUS_NECK", "ENABLED", overwrite ); 
*/


    Hamamatsu_R12860_PMTSolid* hama = new Hamamatsu_R12860_PMTSolid();
    NNVT_MCPPMT_PMTSolid* nnvt = new NNVT_MCPPMT_PMTSolid(); 

    const char* HAMA = "hama" ; 
    const char* NNVT = "nnvt" ; 

    G4VSolid* solid = nullptr ; 
    if( strstr(name, HAMA) == name )
    {
        const char* name_ = name + strlen(HAMA) ; 
        std::cout << " hama.GetSolid " << name_ << std::endl; 
        solid = hama->GetSolid( name_ ); 
    }
    else if( strstr(name, NNVT) == name )
    {
        const char* name_ = name + strlen(NNVT) ; 
        std::cout << " nnvt.GetSolid " << name_ << std::endl; 
        solid = nnvt->GetSolid( name_ ); 
    }

    std::cout 
        << " name " << name
        << " solid " << solid 
        << std::endl
        ; 

    X4SolidTree::Draw(solid, name);

    if( repeat > 0 )
    repeat_X4SolidTree_Draw( solid, name, repeat ); 


    double zcut = getenvdouble("ZCUT", -200. ); 

    std::cout << " zcut " << zcut << std::endl ; 

    G4VSolid* solid_zcut = X4SolidTree::ApplyZCutTree(solid, zcut ); 

    std::cout << " solid_zcut " << solid_zcut << std::endl ; 


    X4SolidTree::Draw(solid_zcut, "solid_zcut");   

    if( repeat > 0 )
    repeat_X4SolidTree_Draw( solid_zcut, "solid_zcut", repeat ); 

    std::cout << "after X4SolidTree::Draw " << std::endl ; 

    return 0 ; 
}

