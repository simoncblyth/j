#pragma once
/**
JPMTProp.h : Specific to JUNO PMTProperty, Material layout
============================================================

1. where should this code live longterm ? 
2. where should it be used to harvest into SSim ?

Incorporating NPFold.h and updating NP.hh in 
offline would allow this to live in junosw, 
if get rid of StackSpec ? 

This is aiming to be the CPU counterpart 
to a GPU interpolator using QProp.hh/qprop.h
by collecting the data into two arrays.  

**/

#include "NPFold.h"

struct JPMT
{
    static constexpr const char* HAMA = "R12860" ; 
    static constexpr const char* NNVT = "NNVTMCP" ; 
    static constexpr const char* NNVTQ = "NNVTMCP_HiQE" ; 
};

struct JPMTProp
{
    static constexpr int NUM_PMTCAT = 3 ; 
    static constexpr int NUM_LAYER = 4 ; 
    static constexpr int NUM_PROP = 2 ; 

    enum { HAMA, NNVT, NNVTQ }; 
    enum { L0, L1, L2, L3 } ; 
    enum { RINDEX, KINDEX } ; 
    
    NPFold* PMTProperty ; 
    NPFold* Pyrex ; 
    NPFold* Vacuum ; 
    NPFold* pmt[NUM_PMTCAT] ; 

    std::vector<const NP*> v_rindex ; 
    std::vector<const NP*> v_thickness ; 

    NP* rindex ;      // (num_pmtcat, num_layer, num_prop, ~15 , 2 ) 
    NP* thickness ;   // (num_pmtcat, num_layer, 1 )
    double* tt ; 

    JPMTProp(); 
    void init(); 

    double get_thickness_nm(int pmtcat, int layer) const  ; 
    double get_rindex(      int pmtcat, int layer, int prop, double energy_eV ) const  ; 

    //template<typename T> StackSpec<T> get(int pmtcat, T wavelength_nm) const ; 

    void save(const char* dir) const ; 
    std::string desc() const ; 
};

inline JPMTProp::JPMTProp()
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
JPMTProp::init
---------------

Collect RINDEX, KINDEX as function of energy and THICKNESS properties 
for all PMT categories and stack layers into two arrays. 

**/
inline void JPMTProp::init()
{
    assert( PMTProperty ); 
    pmt[HAMA]  = PMTProperty->get_subfold(JPMT::HAMA) ; 
    pmt[NNVT]  = PMTProperty->get_subfold(JPMT::NNVT) ; 
    pmt[NNVTQ] = PMTProperty->get_subfold(JPMT::NNVTQ) ; 

    for(int i=0 ; i < NUM_PMTCAT ; i++) 
    {
        NPFold* p = pmt[i];  
        const NP* p_thickness = p->get("THICKNESS") ; 

        for(int j=0 ; j < NUM_LAYER ; j++) 
        {
            for(int k=0 ; k < NUM_PROP ; k++) 
            {
                const NP* a = nullptr ; 
                switch(j)
                {
                   case 0: a = (k == 0 ? Pyrex->get("RINDEX")  : NP::ZEROProp<double>() ) ; break ;  
                   case 1: a = p->get( k == 0 ? "ARC_RINDEX"   : "ARC_KINDEX"   )         ; break ; 
                   case 2: a = p->get( k == 0 ? "PHC_RINDEX"   : "PHC_KINDEX"   )         ; break ; 
                   case 3: a = (k == 0 ? Vacuum->get("RINDEX") : NP::ZEROProp<double>() ) ; break ;  
                }
                v_rindex.push_back(a) ; 
            }

            double d = 0. ;  
            switch(j)
            {
               case 0: d = 0. ; break ; 
               case 1: d = 1e9*p_thickness->get_named_value<double>("ARC_THICKNESS", -1) ; break ; 
               case 2: d = 1e9*p_thickness->get_named_value<double>("PHC_THICKNESS", -1) ; break ; 
               case 3: d = 0. ; break ; 
            }
            tt[i*NUM_LAYER + j] = d ;  
        }
    }
    rindex = NP::Combine(v_rindex); 
    const std::vector<int>& shape = rindex->shape ; 
    assert( shape.size() == 3 ); 
    rindex->change_shape( NUM_PMTCAT, NUM_LAYER, NUM_PROP, shape[shape.size()-2], shape[shape.size()-1] );  
}


inline double JPMTProp::get_thickness_nm(int pmtcat, int layer) const  
{
    assert( pmtcat < NUM_PMTCAT ); 
    assert( layer < NUM_LAYER ) ; 
    return tt[pmtcat*NUM_LAYER+layer] ; 
}

inline double JPMTProp::get_rindex(int pmtcat, int layer, int prop, double energy_eV ) const  
{
    assert( pmtcat < NUM_PMTCAT ); 
    assert( layer < NUM_LAYER ) ; 
    assert( prop < NUM_PROP ); 

    return rindex->combined_interp_5( pmtcat, layer, prop, energy_eV ) ; 
}

 


/**
JPMTProp::get
--------------

Notice that this gets all its data from two arrays: thickness and rindex
making it straightforward to do on GPU. 


template<typename T>
inline StackSpec<T> JPMTProp::get(int pmtcat, T wavelength_nm) const  
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

    return spec ; 
}
**/



inline void JPMTProp::save(const char* dir) const 
{
    rindex->save(dir, "rindex.npy"); 
    thickness->save(dir, "thickness.npy"); 
}
inline std::string JPMTProp::desc() const 
{
    std::stringstream ss ; 
    ss << "JPMTProp::desc"
       << " pmt[0].desc " << pmt[0]->desc()
       << " pmt[1].desc " << pmt[1]->desc()
       << " pmt[2].desc " << pmt[2]->desc()
       << " Pyrex.desc  " << Pyrex->desc()
       << " Vacuum.desc  " << Vacuum->desc()
       << " rindex " << ( rindex ? rindex->sstr() : "-" )
       << std::endl  
       << " thickness " << ( thickness ? thickness->sstr() : "-" )
       ;
    std::string s = ss.str(); 
    return s ; 
}


