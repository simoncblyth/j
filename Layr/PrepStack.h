#pragma once
/**
PrepStack.h
==============

This first iteration is superceeded by PMTProp.h 


**/


struct PrepStack
{
    NPFold* pmt ; 
    NPFold* mat0 ; 
    NPFold* mat3 ; 

    const NP* thickness ; 
    const NP* n0r ; 

    const NP* n1r ; 
    const NP* n1i ; 

    const NP* n2r ; 
    const NP* n2i ; 

    const NP* n3r ; 


    double last_wavelength_nm ; 
    double last_energy_eV ; 
 
    PrepStack(const char* pmtname=PMT::NNVT ); 
    std::string desc() const ; 

    template<typename T>
    StackSpec<T> get(T wavelength_nm) ;  // not const as sets last_*

};

inline PrepStack::PrepStack(const char* pmtname)
    :
    pmt(NPFold::LoadProp("PMTProperty", pmtname )),
    mat0(NPFold::LoadProp("Material/Pyrex")),
    mat3(NPFold::LoadProp("Material/Vacuum")),
    thickness(pmt ? pmt->get("THICKNESS") : nullptr ), 
    n0r(mat0 ? mat0->get("RINDEX") : nullptr),
    n1r(pmt ? pmt->get("ARC_RINDEX") : nullptr),
    n1i(pmt ? pmt->get("ARC_KINDEX") : nullptr),
    n2r(pmt ? pmt->get("PHC_RINDEX") : nullptr),
    n2i(pmt ? pmt->get("PHC_KINDEX") : nullptr),
    n3r(mat3 ? mat3->get("RINDEX") : nullptr),

    last_wavelength_nm(0.),
    last_energy_eV(0.)
{
}

inline std::string PrepStack::desc() const 
{
    std::stringstream ss ; 
    ss 
       << " pmt.desc " 
       << std::endl 
       << ( pmt ? pmt->desc() : "-" )  
       << std::endl 
       << " mat0.desc " 
       << std::endl 
       << ( mat0 ? mat0->desc() : "-" )  
       << std::endl 
       << " mat3.desc " 
       << std::endl 
       << ( mat3 ? mat3->desc() : "-" )  
       << std::endl 
       << " thickness " << ( thickness ? thickness->sstr() : "-" ) << std::endl 
       << " n0r " << ( n0r ? n0r->sstr() : "-" ) << std::endl 
       << " n1r " << ( n1r ? n1r->sstr() : "-" ) << std::endl 
       << " n1i " << ( n1i ? n1i->sstr() : "-" ) << std::endl 
       << " n2r " << ( n2r ? n2r->sstr() : "-" ) << std::endl 
       << " n2i " << ( n2i ? n2i->sstr() : "-" ) << std::endl 
       << " n3r " << ( n3r ? n3r->sstr() : "-" ) << std::endl 
       << " last_energy_eV " << std::fixed << std::setw(10) << std::setprecision(5) << last_energy_eV
       << " last_wavelength_nm " << std::fixed << std::setw(10) << std::setprecision(5) << last_wavelength_nm
       ;
    std::string s = ss.str(); 
    return s ; 
}

template<typename T>
inline StackSpec<T> PrepStack::get(T wavelength_nm) 
{
    StackSpec<T> spec ; 
    spec = {} ; 

    last_wavelength_nm = wavelength_nm ; 
    last_energy_eV = sdomain::hc_eVnm/last_wavelength_nm ; 

    double d1_nm = 1e9*thickness->get_named_value<double>("ARC_THICKNESS", -1) ; 
    double d2_nm = 1e9*thickness->get_named_value<double>("PHC_THICKNESS", -1) ; 

    spec.d0  = 0. ; 
    spec.n0r = n0r->interp<double>(last_energy_eV) ;  

    spec.d1  = d1_nm ; 
    spec.n1r = n1r->interp<double>(last_energy_eV) ;  
    spec.n1i = n1i->interp<double>(last_energy_eV) ;  

    spec.d2  = d2_nm ; 
    spec.n2r = n2r->interp<double>(last_energy_eV) ;  
    spec.n2i = n2i->interp<double>(last_energy_eV) ;  

    spec.d3  = 0. ; 
    spec.n3r = n3r->interp<double>(last_energy_eV) ;  

    return spec ; 
}


void test_PrepStack()
{
    PrepStack ps ; 
    unsigned count = 0 ; 
    for(float wavelength_nm=400.f ; wavelength_nm <= 800.f ; wavelength_nm += 100.f )
    {
        StackSpec<float> spec = ps.get(wavelength_nm); 
        if(count == 0 ) std::cout << "pss.desc" << std::endl << ps.desc() << std::endl ; 
        std::cout << "spec" << std::endl << spec << std::endl ; 
        count += 1 ; 
    }
}

