#pragma once

/**
TComplex.h
=============

HMM inheriting from std::complex<double> and non-member functions 
seems too much hassle just to avoid changing a few TComplex::Conjugate 
into something else like _TComplex::Conjugate

* much easier to just typedef it 

struct TComplex : public std::complex<double> 
{
    using std::complex<double>::complex  ; 
}; 

TComplex operator+( const TComplex& lhs, const TComplex& rhs )
{
}

**/

#include <complex>

typedef std::complex<double> TComplex ; 

namespace _TComplex
{
    inline double   Norm( const TComplex& z ){ return std::norm(z) ; }  // equivalent to z*conj_z       
    inline TComplex Sqrt(const TComplex& z ){ return std::sqrt(z); }        
    inline TComplex Exp( const TComplex& z ){ return std::exp(z) ; }        
    inline TComplex Conjugate( const TComplex& z ){ return std::conj(z) ; }        
}





