#pragma once
/**
TComplex.h
=============

Note how using a typedef is so much easier than inheriting from std::complex<double> 
just to avoid changing a few names. 

* SIMPLICITY IS WELL WORTH A FEW NAME CHANGES
* Note also that newer CUDA versions will provide <cuda/std/complex> following the <complex> API

  * https://nvidia.github.io/libcudacxx/
  * https://github.com/NVIDIA/libcudacxx   

Aborted inheritance approach, the difficulty is the large number 
of non-member functions::

    struct TComplex : public std::complex<double> 
    {
        using std::complex<double>::complex  ; 
    }; 

    TComplex operator+( const TComplex& lhs, const TComplex& rhs )
    {
        ...
    }

**/

#include <complex>

typedef std::complex<double> TComplex ; 

namespace _TComplex
{
    inline double   Norm( const TComplex& z ){ return std::norm(z) ; }  // equivalent to z*conj_z  = x*x + y*y     
    inline TComplex Sqrt(const TComplex& z ){ return std::sqrt(z); }        
    inline TComplex Exp( const TComplex& z ){ return std::exp(z) ; }        
    inline TComplex Conjugate( const TComplex& z ){ return std::conj(z) ; }        
}





