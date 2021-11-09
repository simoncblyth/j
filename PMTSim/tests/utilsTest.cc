#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include "G4MaterialPropertyVector.hh"
#include "G4SystemOfUnits.hh"

#include "utils.hh"

// jcv IMCParamsSvc
// jcv MCParamsFileSvc
// jcv LSExpDetectorConstructionMaterial
// jcv LSExpDetectorConstruction   helper_mpt 


G4MaterialPropertyVector* GetMPV(const char* path, bool dump)
{
    typedef boost::tuple<double, double> elem_d2d; // double, double
    typedef std::vector<elem_d2d> vec_d2d;

    vec_d2d props ; 
    get_implv1(path, props); 

    if(dump) std::cout  
        << "path " << path  
        << std::endl
        << "props.size " << props.size()
        << std::endl
        ; 

    G4MaterialPropertyVector* vec = new G4MaterialPropertyVector(0,0,0);
    for (unsigned i = 0; i < props.size(); ++i) vec->InsertValues(props[i].get<0>(), props[i].get<1>() );
    if(dump)
    {
        for (unsigned i = 0; i < props.size(); ++i)
        {
            double en = props[i].get<0>() ; 
            double va = props[i].get<1>() ; 
            std::cout 
                << " en " << std::setw(10) << std::fixed << std::setprecision(3) << en 
                << " en/eV " << std::setw(10) << std::fixed << std::setprecision(3) << en/eV 
                << " va " << std::setw(10) << std::fixed << std::setprecision(3) << va
                << std::endl 
                ;
        }
    }
    return vec ; 
}


int main(int argc, char** argv)
{
    const char* path = argc > 1 ? argv[1] : nullptr ; 
    if(!path) return 0 ; 

    G4MaterialPropertyVector* vec = GetMPV(path, true); 
    assert(vec); 

    return 0 ; 
}
