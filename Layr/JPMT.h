#pragma once
/**
JPMT.h : Specific to JUNO PMTProperty, Material layout
============================================================

Instanciating JPMT.h loads properties for all PMT types from text files 
and creates and populates two arrays : rindex and thickness 
that contain all the PMT param needed for TMM ART calculation.   

This is aiming to provide the input arrays for the CPU counterpart 
of a GPU interpolator using (or doing similar to) QProp.hh/qprop.h 

What exactly is JUNO specific, can it be split off/made an argument/configuration ?
-----------------------------------------------------------------------------------------

* PMTCAT names, num layers, property keys 


Choices
--------

1. where should this code live longterm ? 
2. where should it be used to harvest into SSim ?

Incorporating NPFold.h and updating NP.hh in 
offline would allow this to live in junosw, 
if get rid of StackSpec ? 


**/

#include "NPFold.h"

struct JPMT
{
    static constexpr const char* _HAMA = "R12860" ; 
    static constexpr const char* _NNVT = "NNVTMCP" ; 
    static constexpr const char* _NNVTQ = "NNVTMCP_HiQE" ; 
    static void GetNames( std::vector<std::string>& names ); 

    static constexpr int NUM_PMTCAT = 3 ; 
    static constexpr int NUM_LAYER = 4 ; 
    static constexpr int NUM_PROP = 2 ; 

    enum { HAMA, NNVT, NNVTQ }; 
    enum { L0, L1, L2, L3 } ; 
    enum { RINDEX, KINDEX } ; 
    
    NPFold* PMTProperty ; 
    NPFold* Pyrex ; 
    NPFold* Vacuum ; 

    std::vector<const NP*> v_rindex ; 
    std::vector<const NP*> v_thickness ; 

    NP* rindex ;      // (num_pmtcat, num_layer, num_prop,  num_energies ~15 , num_payload:2 )    # payload is (energy, value)  
    NP* thickness ;   // (num_pmtcat, num_layer, num_payload:1 )
    double* tt ; 

    JPMT(); 
    void init(); 

    const char* get_pmtcat( int pmtcat ) const ; 
    double get_thickness_nm(int pmtcat, int layer) const  ; 
    double get_rindex(      int pmtcat, int layer, int prop, double energy_eV ) const  ; 

#ifdef WITH_STACKSPEC
    // DONT LIKE THIS METHOD : WORKING TO ELIMINATE IT AND StackSpec INTERMEDIARY
    template<typename T> StackSpec<T> get(int pmtcat, T wavelength_nm) const ; 
#endif

    void save(const char* dir) const ; 
    std::string desc() const ; 
};

inline void JPMT::GetNames( std::vector<std::string>& names ) // static
{
    names.push_back(_HAMA);  
    names.push_back(_NNVT);  
    names.push_back(_NNVTQ);  
}



inline JPMT::JPMT()
    :
    PMTProperty(NPFold::LoadProp("PMTProperty")),
    Pyrex( NPFold::LoadProp("Material/Pyrex")),
    Vacuum(NPFold::LoadProp("Material/Vacuum")),
    rindex(nullptr),
    thickness(NP::Make<double>(NUM_PMTCAT, NUM_LAYER, 1)),
    tt(thickness->values<double>()) 
{
    init(); 
}

/**
JPMT::init
---------------

Collect RINDEX, KINDEX as function of energy and THICKNESS properties 
for all PMT categories and stack layers into two arrays. 

**/
inline void JPMT::init()
{
    assert( PMTProperty ); 

    std::vector<std::string> names ; 
    GetNames(names); 
    assert( names.size() == NUM_PMTCAT ); 

    for(int i=0 ; i < NUM_PMTCAT ; i++) 
    {
        const char* name = names[i].c_str(); 
        NPFold* pmt = PMTProperty->get_subfold(name); 
        const NP* pmt_thickness = pmt->get("THICKNESS") ; 
        // p_thickness is funny named value property array 

        for(int j=0 ; j < NUM_LAYER ; j++) 
        {
            for(int k=0 ; k < NUM_PROP ; k++) 
            {
                const NP* a = nullptr ; 
                switch(j)
                {
                   case 0: a = (k == 0 ? Pyrex->get("RINDEX")  : NP::ZEROProp<double>() ) ; break ;  
                   case 1: a = pmt->get( k == 0 ? "ARC_RINDEX"   : "ARC_KINDEX"   )         ; break ; 
                   case 2: a = pmt->get( k == 0 ? "PHC_RINDEX"   : "PHC_KINDEX"   )         ; break ; 
                   case 3: a = (k == 0 ? Vacuum->get("RINDEX") : NP::ZEROProp<double>() ) ; break ;  
                }
                v_rindex.push_back(a) ; 
            }

            double d = 0. ;  
            double scale = 1e9 ; // express thickness in nm (not meters) 
            switch(j)
            {
               case 0: d = 0. ; break ; 
               case 1: d = scale*pmt_thickness->get_named_value<double>("ARC_THICKNESS", -1) ; break ; 
               case 2: d = scale*pmt_thickness->get_named_value<double>("PHC_THICKNESS", -1) ; break ; 
               case 3: d = 0. ; break ; 
            }
            tt[i*NUM_LAYER + j] = d ;  
        }
    }
    rindex = NP::Combine(v_rindex); 

    const std::vector<int>& shape = rindex->shape ; 
    assert( shape.size() == 3 ); 
    rindex->change_shape( NUM_PMTCAT, NUM_LAYER, NUM_PROP, shape[shape.size()-2], shape[shape.size()-1] );  

    rindex->set_names(names); 
    thickness->set_names(names); 
}


inline const char* JPMT::get_pmtcat( int pmtcat ) const
{
    const char* n = nullptr ; 
    switch(pmtcat)
    {
        case HAMA : n = _HAMA  ; break ; 
        case NNVT : n = _NNVT  ; break ; 
        case NNVTQ: n = _NNVTQ ; break ; 
    } 
    return n ; 
}

inline double JPMT::get_thickness_nm(int pmtcat, int layer) const  
{
    assert( pmtcat < NUM_PMTCAT ); 
    assert( layer < NUM_LAYER ) ; 
    return tt[pmtcat*NUM_LAYER+layer] ; 
}

inline double JPMT::get_rindex(int pmtcat, int layer, int prop, double energy_eV ) const  
{
    assert( pmtcat < NUM_PMTCAT ); 
    assert( layer < NUM_LAYER ) ; 
    assert( prop < NUM_PROP ); 

    return rindex->combined_interp_5( pmtcat, layer, prop, energy_eV ) ; 
}


inline void JPMT::save(const char* dir) const 
{
    rindex->save(dir, "jpmt_rindex.npy"); 
    thickness->save(dir, "jpmt_thickness.npy"); 
}
inline std::string JPMT::desc() const 
{
    std::stringstream ss ; 
    ss << "JPMT::desc"
       << " Pyrex.desc  " << Pyrex->desc()
       << " Vacuum.desc  " << Vacuum->desc()
       << " rindex " << ( rindex ? rindex->sstr() : "-" )
       << std::endl  
       << " thickness " << ( thickness ? thickness->sstr() : "-" )
       ;
    std::string s = ss.str(); 
    return s ; 
}









#ifdef WITH_STACKSPEC
/**
JPMT::get
--------------

DONT LIKE THIS METHOD : WORKING TO ELIMINATE IT AND StackSpec INTERMEDIARY

Notice that this gets all its data from two arrays: thickness and rindex
making it straightforward to do on GPU. 

ACTUALLY WHAT I DONT LIKE IS THE SHUFFLING IN AND OUT OF THE INTERMEDIARY TYPE

**/

template<typename T>
inline StackSpec<T> JPMT::get(int pmtcat, T wavelength_nm) const  
{
    double energy_eV = sdomain::hc_eVnm/wavelength_nm ; 

    StackSpec<T> spec ; 

    spec.d0  = tt[pmtcat*NUM_LAYER+L0] ; 
    spec.d1  = tt[pmtcat*NUM_LAYER+L1] ; 
    spec.d2  = tt[pmtcat*NUM_LAYER+L2] ; 
    spec.d3  = tt[pmtcat*NUM_LAYER+L3] ; 

    spec.n0r = rindex->combined_interp_5( pmtcat, L0, RINDEX, energy_eV ) ; 
    spec.n0i = rindex->combined_interp_5( pmtcat, L0, KINDEX, energy_eV ) ; 

    spec.n1r = rindex->combined_interp_5( pmtcat, L1, RINDEX, energy_eV ) ; 
    spec.n1i = rindex->combined_interp_5( pmtcat, L1, KINDEX, energy_eV ) ; 

    spec.n2r = rindex->combined_interp_5( pmtcat, L2, RINDEX, energy_eV ) ; 
    spec.n2i = rindex->combined_interp_5( pmtcat, L2, KINDEX, energy_eV ) ; 

    spec.n3r = rindex->combined_interp_5( pmtcat, L3, RINDEX, energy_eV ) ; 
    spec.n3i = rindex->combined_interp_5( pmtcat, L3, KINDEX, energy_eV ) ; 

    // HMM: could these 8 calls be consolidated ? 

    return spec ; 
}

#endif
