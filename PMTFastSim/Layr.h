#pragma once

#include <complex>
#include <cmath>
typedef std::complex<double> Complex ; 

/**
https://github.com/jtravs/cuda_complex

#include <thrust/complex.h>
typedef thrust::complex<double> Complex ; 
**/



#if defined(__CUDACC__) || defined(__CUDABE__)
#else
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#endif

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
inline std::ostream& operator<<(std::ostream& os, const Complex& z)  
{
    os << "( " 
       << std::setw(10) << std::fixed << std::setprecision(4) << z.real() 
       << " "
       << std::setw(10) << std::fixed << std::setprecision(4) << z.imag() 
       << ")"
       ;
    return os; 
}
#endif

struct Matx
{
    Complex M00, M01, M10, M11 ; 
    void reset(); 
    void dot(const Matx& other); 
};

inline void Matx::reset()
{
    M00.real(1.) ; M00.imag(0.) ; 
    M01.real(0.) ; M00.imag(0.) ; 
    M10.real(0.) ; M00.imag(0.) ; 
    M11.real(1.) ; M00.imag(0.) ; 
}
/**

      | T00  T01  |  |  M00   M01 | 
      |           |  |            | 
      | T10  T11  |  |  M10   M11 | 

**/
inline void Matx::dot(const Matx& other)
{
    Complex T00 = M00 ; 
    Complex T01 = M01 ; 
    Complex T10 = M10 ; 
    Complex T11 = M11 ; 

    M00 = T00*other.M00 + T01*other.M10;
    M01 = T00*other.M01 + T01*other.M11;
    M10 = T10*other.M00 + T11*other.M10;
    M11 = T10*other.M01 + T11*other.M11;
}

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
inline std::ostream& operator<<(std::ostream& os, const Matx& m)  
{
    os 
       << "| " << m.M00 << " " << m.M01 << " |" << std::endl 
       << "| " << m.M10 << " " << m.M11 << " |" << std::endl  
       ;
    return os; 
}
#endif


struct Layr
{
    double  d ; 
    Complex n ; 
 
    Complex st, ct ; 
    Complex rs, rp ; 
    Complex ts, tp ; 

    Matx S, P ; 

    void reset(); 
};

inline void Layr::reset()
{
    S.reset(); 
    P.reset(); 
}

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
inline std::ostream& operator<<(std::ostream& os, const Layr& l)  
{
    os 
       << "Layr"
       << std::endl 
       << std::setw(4) << "n:" << l.n  
       << std::setw(4) << "d:" << std::fixed << std::setw(10) << std::setprecision(4) << l.d  
       << std::endl 
       << std::setw(4) << "st:" << l.st 
       << std::setw(4) << "ct:" << l.ct
       << std::endl 
       << std::setw(4) << "rs:" << l.rs 
       << std::setw(4) << "rp:" << l.rp
       << std::endl 
       << std::setw(4) << "ts:" << l.ts 
       << std::setw(4) << "tp:" << l.tp
       << std::endl 
       << "S" 
       << std::endl 
       << l.S 
       << std::endl 
       << "P"
       << std::endl 
       << l.P
       << std::endl 
       ;
    return os; 
}
#endif

struct ART
{   
    double R_s;
    double R_p;
    double T_s;
    double T_p;
    double A_s;
    double A_p;
    double R;
    double T;
    double A;
};

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
inline std::ostream& operator<<(std::ostream& os, const ART& art )  
{
    os 
        << "ART" << std::endl 
        << " R_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.R_s << std::endl 
        << " R_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.R_p << std::endl 
        << " T_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.T_s << std::endl 
        << " T_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.T_p << std::endl 
        << " A_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.A_s << std::endl 
        << " A_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.A_p << std::endl 
        << " R   " << std::fixed << std::setw(10) << std::setprecision(4) << art.R   << std::endl 
        << " T   " << std::fixed << std::setw(10) << std::setprecision(4) << art.T   << std::endl 
        << " A   " << std::fixed << std::setw(10) << std::setprecision(4) << art.A   << std::endl 
        ;
    return os; 
}
#endif

template <int N>
struct Stack
{
    Layr ll[N] ;  
    Layr comp ; 
    ART  art ; 
    void computeART(double wl, double theta); 
};

template <int N>
void Stack<N>::computeART(double wl, double theta )
{
    for(int idx=0 ; idx < N ; idx++) ll[idx].reset() ; 

    Complex one(1.,0.); 
    Complex zi(0.,1.); 
  
    Layr& l0 = ll[0] ; 
    l0.st = std::sin(theta) ; 
    l0.ct = std::cos(theta) ;

    for(int idx=1 ; idx < N ; idx++)
    {
        Layr& l = ll[idx] ; 
        l.st = l0.n * l0.st / l.n  ; 
        l.ct = std::sqrt( one - l.st*l.st );
    }     

    for(int idx=0 ; idx < N-1 ; idx++)
    {
        // cf OpticalSystem::Calculate_rt
        Layr& i = ll[idx] ; 
        Layr& j = ll[idx+1] ;  
        i.rs = (i.n*i.ct - j.n*j.ct)/(i.n*i.ct+j.n*j.ct) ; 
        i.rp = (j.n*i.ct - i.n*j.ct)/(j.n*i.ct+i.n*j.ct) ; 
        i.ts = (2.*i.n*i.ct)/(i.n*i.ct + j.n*j.ct) ; 
        i.tp = (2.*i.n*i.ct)/(j.n*i.ct + i.n*j.ct) ; 
    }

    for(int idx=1 ; idx < N ; idx++)
    {
        Layr& l = ll[idx-1] ;          
        Layr& ln = ll[idx] ;          

        Complex tmp_s = 1./l.ts ; 
        Complex tmp_p = 1./l.tp ; 

        if(ln.d > 0.)  // thick layers have d = 0. 
        {
            Complex delta = 2.*M_PI*ln.n*ln.d*ln.ct/wl ;  

            ln.S.M00 = tmp_s*std::exp(-zi*delta) ; 
            ln.S.M01 = tmp_s*l.rs*std::exp(zi*delta) ; 
            ln.S.M10 = tmp_s*l.rs*std::exp(-zi*delta) ; 
            ln.S.M11 = tmp_s*std::exp(zi*delta) ; 

            ln.P.M00 = tmp_p*std::exp(-zi*delta) ; 
            ln.P.M01 = tmp_p*l.rp*std::exp(zi*delta) ; 
            ln.P.M10 = tmp_p*l.rp*std::exp(-zi*delta) ; 
            ln.P.M11 = tmp_p*std::exp(zi*delta) ; 
            // HMM: duplication between S and P feels ugly 
        }
        else
        {
            ln.S.M00 = tmp_s ; 
            ln.S.M01 = tmp_s*l.rs ; 
            ln.S.M10 = tmp_s*l.rs ; 
            ln.S.M11 = tmp_s ; 

            ln.P.M00 = tmp_p ; 
            ln.P.M01 = tmp_p*l.rs ; 
            ln.P.M10 = tmp_p*l.rs ; 
            ln.P.M11 = tmp_p ; 
        }
    }

    comp.reset(); 
    for(int idx=0 ; idx < N ; idx++)
    {
        const Layr& l = ll[idx] ; 
        comp.S.dot(l.S) ; 
        comp.P.dot(l.P) ; 
    }
    comp.rs = comp.S.M10/comp.S.M00 ; 
    comp.rp = comp.P.M10/comp.P.M00 ; 
    comp.ts = one/comp.S.M00 ; 
    comp.tp = one/comp.P.M00 ; 

    Layr& t = ll[0] ; 
    Layr& b = ll[N-1] ; 

    Complex _T_s = (b.n*b.ct)/(t.n*t.ct)*std::norm(comp.ts) ;  
    Complex _T_p = (std::conj(b.n)*b.ct)/(std::conj(t.n)*t.ct)*std::norm(comp.tp) ; 

    art.R_s = std::norm(comp.rs) ; 
    art.R_p = std::norm(comp.rp) ; 
    art.T_s = _T_s.real() ; 
    art.T_p = _T_p.real() ; 

    art.A_s = 1.-art.R_s-art.T_s;
    art.A_p = 1.-art.R_p-art.T_p;
    art.R   = (art.R_s+art.R_p)/2.;
    art.T   = (art.T_s+art.T_p)/2.;
    art.A   = (art.A_s+art.A_p)/2.;
}

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template <int N>
inline std::ostream& operator<<(std::ostream& os, const Stack<N>& stk )  
{
    os << "Stack<" << N << ">" << std::endl ; 
    for(int idx=0 ; idx < N ; idx++) os << "idx " << idx << std::endl << stk.ll[idx] ; 
    os << "comp" 
       << std::endl 
       << stk.comp 
       << std::endl 
       << stk.art 
       << std::endl 
       ; 
    return os; 
}
#endif


