#pragma once
/**
PMTAccessor.h : low dependency access to PMT data  
===================================================

This is the full data equivalent to the standalone JPMT.h 
that is based on top of the PMTSimParamData struct that 
can be obtained from PMTSimParamSvc. 

Fortunately due to PMTSimParamData persisting from _PMTSimParamData 
this struct which is intended to be a monolith resident used together
with a CustomG4OpBoundaryProcess can be compared with JPMT.h 
outside the monolith using "PMTAccessor::Create()" without data argument, 
which will cause the data to be loaded from the directory pointed to 
by envvar PMTSimParamData_BASE

See also:

* j/PMTFastSim/tests/PMTAccessorTest.sh 
* u4/tests/U4PMTAccessorTest.sh 

Note:

* G4MaterialPropertiesTable::GetProperty is not const-correct

**/

#include <string>
#include <sstream>
#include <cstdlib>

#include "G4Material.hh"

#include "Geometry/PMT.h"
#include "Geometry/PMTCategory.h"
#include "PMTSimParamSvc/_PMTSimParamData.h"
#include "PMTSimParamSvc/PMTSimParamData.h"

#include "IPMTAccessor.h"

struct PMTAccessor : public IPMTAccessor
{
    static constexpr const char* TypeName = "PMTAccessor" ; 

    const PMTSimParamData* data ; 

    const G4Material*          Pyrex  ; 
    const G4Material*          Vacuum ; 
    G4MaterialPropertiesTable* PyrexMPT ; 
    G4MaterialPropertiesTable* VacuumMPT ; 
    G4MaterialPropertyVector*  PyrexRINDEX ;  
    G4MaterialPropertyVector*  VacuumRINDEX ; 

    static std::string Desc(); 
    static const PMTSimParamData* LoadPMTSimParamData(const char* base=nullptr ); 
    static const PMTAccessor* Create(const PMTSimParamData* data=nullptr ); 

    PMTAccessor(const PMTSimParamData* data); 
    std::string desc() const ; 


    // IPMTAccessor interface
    double get_pmtid_qe( int pmtid, double energy ) const ; 
    int    get_pmtcat( int pmtid  ) const ; 
    void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const ; 
    const char* get_typename() const ; 

    // HMM: is the argument really energy_eV or energy (factor of 1e-6 between them)
};

inline std::string PMTAccessor::Desc()  // static  
{
    std::stringstream ss ; 
    ss 
        << "PMTAccessor::Desc" 
        << std::endl 
        << "PMTCategory::List() " << PMTCategory::List() 
        << std::endl 
        ; 
    for(int i=kPMT_Unknown ; i <= kPMT_NNVT_HighQE ; i++) ss
        << " PMTCategory::Name(" << std::setw(2) <<  i << ") " 
        << PMTCategory::Name(i) 
        << std::endl 
        ; 
    std::string str = ss.str(); 
    return str ; 
}

inline const PMTSimParamData* PMTAccessor::LoadPMTSimParamData(const char* base_ ) // static
{
    const char* base = base_ ? base_ : getenv("PMTSimParamData_BASE") ; 
    PMTSimParamData* data = new PMTSimParamData ; 
    if(base){ _PMTSimParamData _data(*data) ; _data.load(base); }
    return data ;  
}

inline const PMTAccessor* PMTAccessor::Create(const PMTSimParamData* data_ )  // static 
{ 
    const PMTSimParamData* data = data_ ? data_ : LoadPMTSimParamData() ; 
    PMTAccessor* acc = new PMTAccessor(data); 
    return acc ; 
}

inline PMTAccessor::PMTAccessor(const PMTSimParamData* data_ )
    :
    data(data_),
    Pyrex(G4Material::GetMaterial("Pyrex")),
    Vacuum(G4Material::GetMaterial("Vacuum")),
    PyrexMPT(Pyrex ? Pyrex->GetMaterialPropertiesTable() : nullptr),
    VacuumMPT(Vacuum ? Vacuum->GetMaterialPropertiesTable() : nullptr),
    PyrexRINDEX(PyrexMPT ? PyrexMPT->GetProperty("RINDEX") : nullptr),
    VacuumRINDEX(VacuumMPT ? VacuumMPT->GetProperty("RINDEX") : nullptr)
{
}

inline std::string PMTAccessor::desc() const 
{
    std::stringstream ss ; 
    ss << "PMTAccessor::desc"
       << " data " << data 
       << " Pyrex " << ( Pyrex ? "YES" : "NO" ) 
       << " Vacuum " << ( Vacuum ? "YES" : "NO" )  
       << " TypeName " << get_typename()
       ; 
    std::string str = ss.str(); 
    return str ; 
}

inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
{
    return data->get_pmtid_qe(pmtid, energy) ; 
}
inline int PMTAccessor::get_pmtcat( int pmtid  ) const
{
    return data->get_pmtcat(pmtid) ; 
}
inline void PMTAccessor::get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const
{
    double energy = energy_eV*CLHEP::eV ;  

    ss.fill(0.); 

    ss[4*0+0] = PyrexRINDEX->Value(energy) ; 

    ss[4*1+0] = data->get_pmtcat_prop(       pmtcat, "ARC_RINDEX" , energy );  
    ss[4*1+1] = data->get_pmtcat_prop(       pmtcat, "ARC_KINDEX" , energy );  
    ss[4*1+2] = data->get_pmtcat_const_prop( pmtcat, "ARC_THICKNESS" )/CLHEP::nm ; 

    ss[4*2+0] = data->get_pmtcat_prop(       pmtcat, "PHC_RINDEX" , energy );  
    ss[4*2+1] = data->get_pmtcat_prop(       pmtcat, "PHC_KINDEX" , energy );  
    ss[4*2+2] = data->get_pmtcat_const_prop( pmtcat, "PHC_THICKNESS" )/CLHEP::nm ; 

    ss[4*3+0] = VacuumRINDEX->Value(energy);
}

inline const char* PMTAccessor::get_typename() const 
{ 
    return TypeName ; 
}


