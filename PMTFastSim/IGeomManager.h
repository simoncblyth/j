#pragma once

/**
IGeomManager
===============

Formerly named IGeomStandalone, but renamed as this simple
protocol base can be useful beyond just PMTSIM_STANDALONE tests.
The geometry providing managers defined in the below headers 
are IGeomManager when they are compiled with the PMTSIM_STANDALONE switch::

    HamamatsuMaskManager.hh
    NNVTMaskManager.hh
    NNVTMCPPMTManager.hh
    HamamatsuR12860PMTManager.hh
    LowerChimney.hh

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
#include "PMTFASTSIM_API_EXPORT.hh"

class G4LogicalVolume ; 
class G4PVPlacement ;
class G4VSolid ; 
class IPMTElement ; 
class IDetElement ; 
class IDetElementPos ; 


struct PMTFASTSIM_API IGeomManager
{
    static constexpr const int LEVEL = 0 ;  // using PLOG across projects inconvenient ?
    static constexpr const char* PREFIX = "0123" ; 
    IGeomManager( const std::string& objName ); 

    const std::string& m_objName;
    char* m_geom ;
    char* m_head ;
    char* m_tail ;

    std::vector<std::pair<std::string, double>> m_values ;

    template<typename Type>
    bool declProp(const std::string& key, Type& var); 

    static void Chop( char** head, char** tail, const char* delim, const char* str );
    void setGeom(const char* geom); 
    const char* getGeom() const ;  
    const char* getHead() const ;  
    const char* getTail() const ;  

    bool hasOpt(const char* q) const ; 


    const std::string& objName() { return m_objName; }

    void addValue( const char* k , double v ); 
    NP*  getValues(const char* prefix) ;             


    virtual G4LogicalVolume* getLV() = 0 ;  
    virtual G4LogicalVolume* getLV(const char* name) = 0 ;
    virtual G4PVPlacement*   getPV(const char* name) = 0 ;
    virtual G4VSolid*        getSolid(const char* name) = 0 ; 
}; 


inline IGeomManager::IGeomManager( const std::string& objName )
    :
    m_objName(objName), 
    m_geom(nullptr),
    m_head(nullptr),
    m_tail(nullptr)
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
    if(LEVEL > 0) std::cout 
        << "IGeomManager::declProp"
        << " objName " << std::setw(30) << objName()
        << " key " << std::setw(20) << key 
        << " var " << var  
        << std::endl
        ; 
    return true ; 
}


/**
IGeomManager::Chop
--------------------

Chop *str* into *head* and *tail* delimited by *delim*

**/

inline void IGeomManager::Chop( char** head, char** tail, const char* delim, const char* str ) // static
{   
    *head = strdup(str); 
    char* p = strstr(*head, delim);  // pointer to first occurence of delim in str or null if not found
    if(p) p[0] = '\0' ; 
    *tail = p ? p + strlen(delim) : nullptr ;
}

/**
IGeomManager::setGeom
----------------------

Canonically called from PMTSim::getManager immediately 
after picking the appropriate manager to handle the geom 
argument. 

**/



inline void IGeomManager::setGeom( const char* geom )
{
    assert( geom ); 
    m_geom = strdup(geom) ; 
    Chop( &m_head, &m_tail, "__" , m_geom + strlen(PREFIX) );
  
    if(LEVEL > 0) std::cout 
        << "IGeomManager::setGeom "
        << " m_geom " << ( m_geom ? m_geom : "-" )
        << " m_head " << ( m_head ? m_head : "-" )
        << " m_tail " << ( m_tail ? m_tail : "-" )
        << std::endl 
        ;   

    assert( m_head );  
}
inline const char* IGeomManager::getGeom() const { return m_geom ; }
inline const char* IGeomManager::getHead() const { return m_head ; }
inline const char* IGeomManager::getTail() const { return m_tail ; }

inline bool IGeomManager::hasOpt(const char* q) const 
{
    bool has = q && m_tail && strlen(q) <= strlen(m_tail) && strstr( m_tail, q ) != nullptr ; 
    
    if(LEVEL > 2) std::cout 
        << "IGeomManager::hasOpt" 
        << " q " << ( q  ? q : "-" )
        << " m_tail " << ( m_tail ? m_tail : "-" )
        << " has " << ( has ? "YES" : "NO" )
        << std::endl
        ; 

    return has ; 

}

inline void IGeomManager::addValue( const char* k, double v )
{
    m_values.push_back({k,v}); 
}

inline NP* IGeomManager::getValues(const char* contains) 
{ 
    getLV(); 

    NP* vv = NP::MakeValues(m_values, contains) ; 
    if(LEVEL > 0 ) std::cout 
        << "IGeomManager::getValues "
        << " m_objName " << m_objName 
        << " contains [" << ( contains ? contains : "-" )  << "] return NP::MakeVales " 
        << " m_values.size " << m_values.size()
        << " vv " << ( vv ? vv->sstr() : "-" )
        << std::endl 
        ;  

    if(vv && m_geom) vv->set_meta<std::string>("geom", m_geom) ; 
    if(vv && m_head) vv->set_meta<std::string>("head", m_head) ; 
    if(vv && m_tail) vv->set_meta<std::string>("tail", m_tail) ; 
    return vv ; 
}



