/**
MaterialSvc.cc
=================



**/

#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include "G4MaterialPropertyVector.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4SystemOfUnits.hh"
#include "utils.hh"

#include "MaterialSvc.hh"


bool MaterialSvc::Get(const std::string& param, vec_d2d& props)
{  
    const std::string path = GetPath( param.c_str() );
    return get_implv1(path, props); 
}

bool MaterialSvc::Get(const std::string& param, vec_s2d& props)
{
    const std::string path = GetPath( param.c_str() );
    return get_implv1(path, props);
}

bool MaterialSvc::Get(const std::string& param, map_s2d& props)
{
    vec_s2d vec_props;
    const std::string path = GetPath( param.c_str() );
    bool st = get_implv1(path, vec_props);
    for (vec_s2d::iterator it = vec_props.begin(); it != vec_props.end(); ++it) props[it->get<0>()] = it->get<1>(); 
    return st; 
}




/**
MaterialSvc::GetPath
-------------------

Mimmick MCParamsFileSvc::GetPath 

**/

const char* MaterialSvc::GetPath(const char* propPath) // static
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


G4MaterialPropertyVector* MaterialSvc::GetMPV(const char* path, bool dump)  // static
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

    G4MaterialPropertyVector* vec = new G4MaterialPropertyVector((G4double*)0,(G4double*)0,(size_t)0);

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
MaterialSvc::AddProperty
-----------------------

After::

   LSExpDetectorConstruction::helper_mpt

**/

void MaterialSvc::AddProperty(G4MaterialPropertiesTable* MPT, const char* propName, const char* propPath) // static
{
    const char* path = GetPath(propPath); 
    bool dump = false ; 
    G4MaterialPropertyVector* mpv = GetMPV(path, dump); 
    MPT->AddProperty(propName, mpv);
}



