#pragma once

/**
IGeomManager
===============

Formerly named IGeomStandalone, but renamed as this simple
protocol base can be useful beyond just PMTSIM_STANDALONE tests.
The below geometry providing managers are IGeomManager 
when they are compiled with the PMTSIM_STANDALONE switch::

    HamamatsuR12860PMTManager
    NNVTMCPPMTManager

The methods cannot easily be const as the underlying Manager 
use lazy instanciation. 

**/

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

#include "NP.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"
#include "PMTSIM_API_EXPORT.hh"

class G4LogicalVolume ; 
class G4PVPlacement ;
class G4VSolid ; 
class IPMTElement ; 
class IDetElement ; 
class IDetElementPos ; 


struct PMTSIM_API IGeomManager
{
    IGeomManager( const std::string& name ); 

    const std::string& m_objName;
    std::vector<std::pair<std::string, double>> m_values ;

    template<typename Type>
    bool declProp(const std::string& key, Type& var); 


    const std::string& objName() { return m_objName; }

    void addValue( const char* k , double v ); 
    NP*  getValues(const char* prefix) ;             


    virtual G4LogicalVolume* getLV() = 0 ;  
    virtual G4LogicalVolume* getLV(const char* name) = 0 ;
    virtual G4PVPlacement*   getPV(const char* name) = 0 ;
    virtual G4VSolid*        getSolid(const char* name) = 0 ; 
}; 


inline IGeomManager::IGeomManager( const std::string& name )
    :
    m_objName(name)
{
}


/**
IGeomManager::declProp
------------------------

Do nothing declProp allows Manager code with base class swapped from ToolBase to IGeomManager 
to change less of its setup code. 

**/

template<typename Type>
inline bool IGeomManager::declProp(const std::string& key, Type& var)
{
    std::cout 
        << "IGeomManager::declProp"
        << " objName " << std::setw(30) << objName()
        << " key " << std::setw(20) << key 
        << " var " << var  
        << std::endl
        ; 
    return true ; 
}


inline void IGeomManager::addValue( const char* k, double v )
{
    m_values.push_back({k,v}); 
}

inline NP* IGeomManager::getValues(const char* contains) 
{ 
    getLV(); 
    std::cout 
        << "IGeomManager::getValues "
        << " m_objName " << m_objName 
        << " contains [" << ( contains ? contains : "-" )  << "] return NP::MakeVales " 
        << " m_values.size " << m_values.size()
        << std::endl 
        ;  
    return NP::MakeValues(m_values, contains) ; 
}



