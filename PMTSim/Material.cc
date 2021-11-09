#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include "G4MaterialPropertyVector.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"
#include "utils.hh"

#include "Material.hh"


/**
Material::GetPath
-------------------

Mimmick MCParamsFileSvc::GetPath 

**/

const char* Material::GetPath(const char* propPath) // static
{
    char* n = strdup(propPath); 
    for(unsigned i=0 ; i < strlen(n) ; i++) if(n[i] == '.') n[i] = '/' ; 
    std::stringstream ss ; 
    ss << getenv("JUNOTOP") ; 
    ss << "/data/Simulation/DetSim/" ;
    ss << n ; 
    free(n); 
    std::string s = ss.str(); 
    return strdup(s.c_str()); 
}


G4MaterialPropertyVector* Material::GetMPV(const char* path, bool dump)  // static
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


/**
Material::AddProperty
-----------------------

After::

   LSExpDetectorConstruction::helper_mpt

**/

void Material::AddProperty(G4MaterialPropertiesTable* MPT, const char* propName, const char* propPath) // static
{
    const char* path = GetPath(propPath); 
    bool dump = false ; 
    G4MaterialPropertyVector* mpv = GetMPV(path, dump); 
    MPT->AddProperty(propName, mpv);
}



