#pragma once

#include <complex>
#include <cmath>

/**
typedef std::complex<double> Complex ; 
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
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::complex<T>& z)  
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

template<typename T>
struct Matx
{
    std::complex<T> M00, M01 ;   // 4
    std::complex<T> M10, M11 ;   // 4
    void reset(); 
    void dot(const Matx<T>& other); 
};

template<typename T>
inline void Matx<T>::reset()
{
    M00.real(1) ; M00.imag(0) ; 
    M01.real(0) ; M00.imag(0) ; 
    M10.real(0) ; M00.imag(0) ; 
    M11.real(1) ; M00.imag(0) ; 
}
/**

      | T00  T01  |  |  M00   M01 | 
      |           |  |            | 
      | T10  T11  |  |  M10   M11 | 

**/
template<typename T>
inline void Matx<T>::dot(const Matx<T>& other)
{
    std::complex<T> T00 = M00 ; 
    std::complex<T> T01 = M01 ; 
    std::complex<T> T10 = M10 ; 
    std::complex<T> T11 = M11 ; 

    M00 = T00*other.M00 + T01*other.M10;
    M01 = T00*other.M01 + T01*other.M11;
    M10 = T10*other.M00 + T11*other.M10;
    M11 = T10*other.M01 + T11*other.M11;
}

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Matx<T>& m)  
{
    os 
       << "| " << m.M00 << " " << m.M01 << " |" << std::endl 
       << "| " << m.M10 << " " << m.M11 << " |" << std::endl  
       ;
    return os; 
}
#endif


template<typename T>
struct Layr
{
    T  d ; T padding = 0 ;   // 2
    std::complex<T> n ;      // 2

    std::complex<T> st ;     // 2
    std::complex<T> ct ;     // 2



    std::complex<T> rs ;     // 2
    std::complex<T> rp ;     // 2

    std::complex<T> ts ;     // 2
    std::complex<T> tp ;     // 2


    Matx<T> S ;              // 8  
    Matx<T> P ;              // 8

                             // 32 elements : 4*4*2 
    void reset(); 
    void zero(); 
};

template<typename T>
inline void Layr<T>::reset()
{
    S.reset(); 
    P.reset(); 
}

template<typename T>
inline void Layr<T>::zero()
{
    d = 0      ;  padding = 0 ; 
    n.real(0)  ;  n.imag(0) ; 

    st.real(0) ; st.imag(0) ; 
    ct.real(0) ; ct.imag(0) ; 

    rs.real(0) ; rs.imag(0) ; 
    rp.real(0) ; rp.imag(0) ; 

    ts.real(0) ; ts.imag(0) ; 
    tp.real(0) ; tp.imag(0) ; 

    S.reset() ; 
    P.reset() ; 
}





#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const Layr<T>& l)  
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

template<typename F>
struct ART
{   
    F R_s;
    F R_p;
    F T_s;
    F T_p;

    F A_s;
    F A_p;
    F R;
    F T;

    F A;
    F A_R_T ; 
    F wl ; 
    F th ; 
};

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const ART<T>& art )  
{
    os 
        << "ART" << std::endl 
        << " R_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.R_s 
        << " R_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.R_p 
        << std::endl 
        << " T_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.T_s 
        << " T_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.T_p 
        << std::endl 
        << " A_s " << std::fixed << std::setw(10) << std::setprecision(4) << art.A_s 
        << " A_p " << std::fixed << std::setw(10) << std::setprecision(4) << art.A_p 
        << std::endl 
        << " R   " << std::fixed << std::setw(10) << std::setprecision(4) << art.R   
        << " T   " << std::fixed << std::setw(10) << std::setprecision(4) << art.T   
        << " A   " << std::fixed << std::setw(10) << std::setprecision(4) << art.A  
        << " A_R_T " << std::fixed << std::setw(10) << std::setprecision(4) << art.A_R_T 
        << std::endl 
        << " wl  " << std::fixed << std::setw(10) << std::setprecision(4) << art.wl  << std::endl 
        << " th  " << std::fixed << std::setw(10) << std::setprecision(4) << art.th  << std::endl 
        ;
    return os; 
}
#endif

template <typename T, int N>
struct Stack
{
    Layr<T> ll[N] ;  
    Layr<T> comp ; 
    ART<T>  art ; 

    void computeART(T wl, T th); 
};

template <typename T, int N>
void Stack<T,N>::computeART(T wl, T th )
{
    for(int idx=0 ; idx < N ; idx++) ll[idx].reset() ;  // S and P set to identity 

    T zero(0) ; 
    T one(1) ; 
    T two(2) ; 

    std::complex<T> zO(one,zero); 
    std::complex<T> zI(zero,one); 
  
    Layr<T>& l0 = ll[0] ; 
    l0.st = std::sin(th) ; 
    l0.ct = std::cos(th) ;

    // Snell : set angles of all layers 
    for(int idx=1 ; idx < N ; idx++)
    {
        Layr<T>& l = ll[idx] ; 
        l.st = l0.n * l0.st / l.n  ; 
        l.ct = std::sqrt( zO - l.st*l.st );
    }     

    // Fresnel rs/rp/ts/tp : HMM note that only N-1 are set, its for the interfaces 
    for(int idx=0 ; idx < N-1 ; idx++)
    {
        // cf OpticalSystem::Calculate_rt
        Layr<T>& i = ll[idx] ; 
        const Layr<T>& j = ll[idx+1] ;  
        i.rs = (i.n*i.ct - j.n*j.ct)/(i.n*i.ct+j.n*j.ct) ; 
        i.rp = (j.n*i.ct - i.n*j.ct)/(j.n*i.ct+i.n*j.ct) ; 
        i.ts = (two*i.n*i.ct)/(i.n*i.ct + j.n*j.ct) ; 
        i.tp = (two*i.n*i.ct)/(j.n*i.ct + i.n*j.ct) ; 
    }

    // populate transfer matrices for both thick and thin layers  
    for(int idx=1 ; idx < N ; idx++)
    {
        const Layr<T>& i = ll[idx-1] ;          
        Layr<T>& j = ll[idx] ;          

        std::complex<T> tmp_s = one/i.ts ; 
        std::complex<T> tmp_p = one/i.tp ; 

        // thick layers have d = 0. , thin layers do not 
        std::complex<T> delta         = j.d == zero ? zero : two*M_PI*j.n*j.d*j.ct/wl ; 
        std::complex<T> exp_neg_delta = j.d == zero ? one  : std::exp(-zI*delta) ; 
        std::complex<T> exp_pos_delta = j.d == zero ? one  : std::exp( zI*delta) ; 

        j.S.M00 = tmp_s*exp_neg_delta      ; j.S.M01 = tmp_s*i.rs*exp_pos_delta ; 
        j.S.M10 = tmp_s*i.rs*exp_neg_delta ; j.S.M11 =      tmp_s*exp_pos_delta ; 

        j.P.M00 = tmp_p*exp_neg_delta      ; j.P.M01 = tmp_p*i.rp*exp_pos_delta ; 
        j.P.M10 = tmp_p*i.rp*exp_neg_delta ; j.P.M11 =      tmp_p*exp_pos_delta ; 
    }

    // product of the transfer matrices
    comp.zero(); // set comp.S and comp.P to identity 
    for(int idx=0 ; idx < N ; idx++)
    {
        const Layr<T>& l = ll[idx] ; 
        comp.S.dot(l.S) ; 
        comp.P.dot(l.P) ; 
    }

    // extract amplitude factors from the composite matrix
    comp.rs = comp.S.M10/comp.S.M00 ; 
    comp.rp = comp.P.M10/comp.P.M00 ; 
    comp.ts = one/comp.S.M00 ; 
    comp.tp = one/comp.P.M00 ; 

    /**
    The vector 2-tuples are for left-going and right-going waves 
           
           | E_inc |     | M00    M01 | | E_tra |
           |       |  =  |            | |       |
           | E_ref |     | M10    M11 | |  0    |

      
             E_inc  = M00 E_tra 

             E_ref  = M10 E_tra 


             E_ref        M10
       r  =  -----   =   -----
             E_inc        M00

             E_tra         1
       t =  -------  =   ------
             E_inc        M00 

    **/

    Layr<T>& t = ll[0] ; 
    Layr<T>& b = ll[N-1] ; 

    std::complex<T> _T_s = (b.n*b.ct)/(t.n*t.ct)*std::norm(comp.ts) ;  
    std::complex<T> _T_p = (std::conj(b.n)*b.ct)/(std::conj(t.n)*t.ct)*std::norm(comp.tp) ; 

    art.R_s = std::norm(comp.rs) ; 
    art.R_p = std::norm(comp.rp) ; 
    art.T_s = _T_s.real() ; 
    art.T_p = _T_p.real() ; 

    // absorption factor by subtracting reflection and transmission
    art.A_s = one-art.R_s-art.T_s;
    art.A_p = one-art.R_p-art.T_p;

    // average of S and P 
    art.R   = (art.R_s+art.R_p)/two ;
    art.T   = (art.T_s+art.T_p)/two ;
    art.A   = (art.A_s+art.A_p)/two ;
    art.A_R_T = art.A + art.R + art.T ;  

    art.wl  = wl ; 
    art.th  = th ; 

}

#if defined(__CUDACC__) || defined(__CUDABE__)
#else
template <typename T, int N>
inline std::ostream& operator<<(std::ostream& os, const Stack<T,N>& stk )  
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


