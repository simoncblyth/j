#pragma once
/**
Layr.h
=========

Objective
-----------

Explore thin film optics math using TMM "Transfer Matrix Method" 
by simplifting into a single header and coding in a style amenable 
to being ported to GPU 

References for Thin Film Optics Using "Transfer Matrix Method" (aka TMM)
----------------------------------------------------------------------------

* https://en.wikipedia.org/wiki/Transfer-matrix_method_(optics)

* https://arxiv.org/abs/1603.02720
* ~/opticks_refs/Byrnes_Multilayer_optical_calculations_1603.02720.pdf

* https://pypi.org/project/tmm/
* https://github.com/sbyrnes321/tmm
* http://sjbyrnes.com/science-programming.html
* http://sjbyrnes.com/multilayer_film_optics_programs.html

* :google:`bo sernelius lecture notes pdf`

* http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/TTM/TTM_Sernelius.pdf
* ~/opticks_refs/TTM_Sernelius.pdf


Best explanation of TMM found is on YouTube from Jordan Edmunds

* https://www.youtube.com/watch?v=XuSxmb9-viY

Explains the transfer matrix formalism 

* think of matrix for the medium separate from matrix for interfaces
* 2-vectors are for (E_right E_left) 

Start of the stack:: 

   | E_incident   |
   | E_reflected  |

End of the stack::

   | E_transmitted |      # no left going expected   
   |      0        |

System::  

   | E_incident   |  =    |  M00    M01  |  |   E_trans  |  
   | E_reflected  |       |  M10    M11  |  |    0       |


   E_incident = M00 E_trans          E_trans/E_incident = 1/M00
   E_reflected = M10 E_trans         E_refl/E_incident = M10/M00 


* https://www.youtube.com/watch?v=dE7Yi3u9cvI

Transmission Matrix::
              
         |  E0_r |         1    |   1     r01  |   |  E1_r |
         |       |   =   ------ |              |   |       |
         |  E0_l |        t01   |  r01     1   |   |  E1_l |  


Using    t01t10 - r01r10 = 1

Works for S or P by using the corresponding r and t



* https://www.youtube.com/watch?v=BX_-1ei12sU

Propagation Matrix::
  .         
  EA(x) = E0 exp(i(wt-kx))

  EA(x+L) = E0 exp(i(wt-k(x+L))) = E0 exp(i(wt-kx)) exp(-ikL) = EA(x) exp(-ikL)

  EA(x+L)
  ------- = exp(-ikL)
  EA(x)

  EB  = EA exp(-ikL)

  EA = EB exp(ikL)

  | EA_r |     |   exp(i k1 L1)      0          | |  EB_r |
  |      |  =  |                                | |       |
  | EA_l |     |      0         exp(-i k1 L1)   | |  EB_l |


TODO: find CUDA standin for std::complex and arithmetic functions
--------------------------------------------------------------------

Need complex handling equivalent to::

    std::conj  # these two are trivial
    std::norm

    std::sin   # these need to be "official" :google:`CUDA complex arithmetics`
    std::cos
    std::sqrt
    std::exp

Contenders:

* https://github.com/jtravs/cuda_complex

  * dead project : non starter

* cuComplex.h : looks real awkward and limited

  * https://stackoverflow.com/questions/9860711/cucomplex-h-and-exp

* typedef thrust::complex<double> Complex
* https://thrust.github.io/doc/group__complex__numbers.html

  * looks like thrust::complex can do everything needed, and its included with 
    rather old CUDA versions  
  * examples/UseThrust/UseThrustComplex.cu 
  * THIS IS THE NOW 
  * TODO: exercise thrust::complex 

* https://github.com/NVIDIA/libcudacxx
* https://nvidia.github.io/libcudacxx/releases.html

  * suggests inclusion of cuda/std/complex starts from CUDA 11.3 
  * unconfirmed advantage that suitable simple std::complex CPU code 
    could be ported with only namespace changes 
  * THIS IS PROBABLY THE FUTURE 

* https://nvidia.github.io/cutlass/index.html

  * wrong sledgehammer


TODO : more realistic CPU testing by loading actual refractive indices and thicknesses
-----------------------------------------------------------------------------------------

* not in ~/.opticks/GEOM/J004
* need to add some property harvesting from m_PMTSimParSvc

jcv junoPMTOpticalModel::

    169     int pmtid  = get_pmtid(track);
    170     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    171    
    172     _photon_energy  = energy;
    173     _wavelength     = twopi*hbarc/energy;
    174     n_glass         = _rindex_glass->Value(_photon_energy);
    175    
    176     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    177 
    178     n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    179     k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    180     d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;
    181 
    182     n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    183     k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    184     d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;



TODO : devise CPU/GPU counterpart paired structs for this calculation
-------------------------------------------------------------------------

**/

#include <complex>
#include <cmath>

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
    std::complex<T> M00, M01 ;   // 2+2
    std::complex<T> M10, M11 ;   // 2+2
    void reset();                //  8 elements  
    void dot(const Matx<T>& other); 
};

template<typename T>
inline void Matx<T>::reset()
{
    M00.real(1) ; M00.imag(0) ; 
    M01.real(0) ; M01.imag(0) ; 
    M10.real(0) ; M10.imag(0) ; 
    M11.real(1) ; M11.imag(0) ; 
}
/**

      | T00  T01  |  |  M00   M01 | 
      |           |  |            | 
      | T10  T11  |  |  M10   M11 | 

**/
template<typename T>
inline void Matx<T>::dot(const Matx<T>& other)
{
    std::complex<T> T00(M00) ; 
    std::complex<T> T01(M01) ; 
    std::complex<T> T10(M10) ; 
    std::complex<T> T11(M11) ; 

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


/**
Layr
-----

List layer thickness and complex refractive indices::

    In [20]: np.c_[a.lls[0,:,0,0,0],a.lls[0,:,0,1]]
    Out[20]: 
    array([[  0.  ,   1.  ,   0.  ],
           [500.  ,   1.  ,   0.01],
           [500.  ,   1.  ,   0.01],
           [  0.  ,   1.5 ,   0.  ]])
**/

template<typename T>
struct Layr
{
    T  d ; T padding = 0 ;   // 2      a.lls[0,:,0,0,0]  d of the 4 layers 
    std::complex<T> n ;      // 2      a.lls[0,:,0,1]    n (re,im) of the 4 layers
    std::complex<T> st ;     // 2
    std::complex<T> ct ;     // 2

    std::complex<T> rs ;     // 2
    std::complex<T> rp ;     // 2
    std::complex<T> ts ;     // 2
    std::complex<T> tp ;     // 2

    Matx<T> S ;              // 8  

    Matx<T> P ;              // 8

                             // 32 elements : persisted into shape (4,4,2) 
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
    F R_s;     // R_s = a.arts[:,0,0]
    F R_p;     // R_p = a.arts[:,0,1]
    F T_s;     // T_s = a.arts[:,0,2]
    F T_p;     // T_p = a.arts[:,0,3]

    F A_s;     // A_s = a.arts[:,1,0]
    F A_p;     // A_p = a.arts[:,1,1]
    F R;       // R = a.arts[:,1,2]
    F T;       // T = a.arts[:,1,3]

    F A;       // A = a.arts[:,2,0]
    F A_R_T ;  // A_R_T = a.arts[:,2,1] 
    F wl ;     // wl = a.arts[:,2,2]
    F th ;     // th = a.arts[:,2,3]   

    // persisted into shape (3,4) 
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


template<typename T>
struct StackSpec
{
    T n0r, n0i, d0 ; 
    T n1r, n1i, d1 ; 
    T n2r, n2i, d2 ; 
    T n3r, n3i, d3 ; 

    static StackSpec Default()
    {
        StackSpec ss ; 
        ss.n0r = 1.f  ; ss.n0i = 0.f   ; ss.d0 =   0.f ; 
        ss.n1r = 1.f  ; ss.n1i = 0.01f ; ss.d1 = 500.f ; 
        ss.n2r = 1.f  ; ss.n2i = 0.01f ; ss.d2 = 500.f ; 
        ss.n3r = 1.5f ; ss.n3i = 0.f   ; ss.d3 =   0.f ; 
        return ss ; 
    }
};



/**
Stack
-------

HMM: in reality the refractive indices all depend 
on wavelength so need to know the wavelength at instanciation
of the stack : only the angle can sensibly be an argument
to computeART and even that will requires re-computation 
of almost all the parameters of the layers.

So the object is almost useless other than for organization, 
as have to recompute everything every time. 

Would splitting interface and propagation matrices
help with avoiding having to do everything everytime ?

**/

template <typename T, int N>
struct Stack
{
    Stack(T wl, const StackSpec<T>& ss);
 
    const StackSpec<T> ss ; 
    Layr<T> ll[N] ;  
    Layr<T> comp ; 
    ART<T>  art ; 

    void computeART(T th); 
};

/**
Stack
-------
in reality will need to do property or texture 
lookups here to get the indices using the wavelength
(the thicknesses at least are constant, so they could
be accessed CPU side and planted into the GPU counterpart struct
and then uploaded ready to hit-ground-running)

nm (same length unit as wavelength)

**/

template<typename T, int N>
Stack<T,N>::Stack(T wl, const StackSpec<T>& ss_) 
    :
    ss(ss_)
{
    assert( N == 4 ); 
    Layr<T>& l0 = ll[0] ; 
    Layr<T>& l1 = ll[1] ; 
    Layr<T>& l2 = ll[2] ; 
    Layr<T>& l3 = ll[3] ; 

    l0.n.real(ss.n0r) ; l0.n.imag(ss.n0i) ; l0.d = ss.d0 ; 
    l1.n.real(ss.n1r) ; l1.n.imag(ss.n1i) ; l1.d = ss.d1 ; 
    l2.n.real(ss.n2r) ; l2.n.imag(ss.n2i) ; l2.d = ss.d2 ;          
    l3.n.real(ss.n3r) ; l3.n.imag(ss.n3i) ; l3.d = ss.d3 ; 

    art.wl = wl ; 
}


template <typename T, int N>
void Stack<T,N>::computeART(T th )
{
    const T zero(0) ; 
    const T one(1) ; 
    const T two(2) ; 
    const T twopi(two*M_PI) ; 
    // how to avoid transient double on GPU when T=float ?
    const std::complex<T> zO(one,zero); 
    const std::complex<T> zI(zero,one); 
      

    // Snell : set st,ct of all layers 
    // (depending on indices(hence wl) and incident angle) 
    Layr<T>& l0 = ll[0] ; 
    l0.st = std::sin(th) ; 
    l0.ct = std::cos(th) ;
    for(int idx=1 ; idx < N ; idx++)
    {
        Layr<T>& l = ll[idx] ; 
        l.st = l0.n * l0.st / l.n  ; 
        l.ct = std::sqrt( zO - l.st*l.st );
    }     

    // Fresnel : set rs/rp/ts/tp for N-1 interfaces between N layers
    // (depending on indices(hence wl) and layer ct) 
    // HMM: last layer unset, perhaps zero it ?
    for(int idx=0 ; idx < N-1 ; idx++)
    {
        // cf OpticalSystem::Calculate_rt  
        // https://en.wikipedia.org/wiki/Fresnel_equations
        Layr<T>& i = ll[idx] ; 
        const Layr<T>& j = ll[idx+1] ;  
        i.rs = (i.n*i.ct - j.n*j.ct)/(i.n*i.ct+j.n*j.ct) ; 
        i.rp = (j.n*i.ct - i.n*j.ct)/(j.n*i.ct+i.n*j.ct) ; 
        i.ts = (two*i.n*i.ct)/(i.n*i.ct + j.n*j.ct) ; 
        i.tp = (two*i.n*i.ct)/(j.n*i.ct + i.n*j.ct) ; 
    }

    // for(int idx=0 ; idx < N ; idx++) ll[idx].reset() ;  // S and P set to identity 
    // ACTUALLY: only need to reset 0th layer S,P to identity, as all elements of other layer S,P set below
    ll[0].reset();   

    // populate transfer matrices for both thick and thin layers  
    for(int idx=1 ; idx < N ; idx++)
    {
        const Layr<T>& i = ll[idx-1] ;          
        Layr<T>& j = ll[idx] ;          

        std::complex<T> tmp_s = one/i.ts ; 
        std::complex<T> tmp_p = one/i.tp ; 

        // thick layers have d = 0. 
        // thin layers have thickness presumably comparable to art.wl (WITH SAME LENGTH UNIT: nm)
        std::complex<T> delta         = j.d == zero ? zero : twopi*j.n*j.d*j.ct/art.wl ; 
        std::complex<T> exp_neg_delta = j.d == zero ? one  : std::exp(-zI*delta) ; 
        std::complex<T> exp_pos_delta = j.d == zero ? one  : std::exp( zI*delta) ; 

        j.S.M00 = tmp_s*exp_neg_delta      ; j.S.M01 = tmp_s*i.rs*exp_pos_delta ; 
        j.S.M10 = tmp_s*i.rs*exp_neg_delta ; j.S.M11 =      tmp_s*exp_pos_delta ; 

        j.P.M00 = tmp_p*exp_neg_delta      ; j.P.M01 = tmp_p*i.rp*exp_pos_delta ; 
        j.P.M10 = tmp_p*i.rp*exp_neg_delta ; j.P.M11 =      tmp_p*exp_pos_delta ; 

        // NB: for thin layers the transfer matrices combine interface and propagation between them 
        // AM THINKING :   Thick-Thin-Thin-Thick  
    }

    // product of the transfer matrices
    comp.d = zero ; 
    comp.st = zero ; 
    comp.ct = zero ; 
    comp.S.reset(); 
    comp.P.reset(); 

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

    // getting from amplitude to power relations for relectance R and tranmittance T
    // R : simpler because same medium and angle 
    //  https://en.wikipedia.org/wiki/Fresnel_equations  has _T_s 
    //  https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture13_0.pdf

    std::complex<T> _T_s = (b.n*b.ct)/(t.n*t.ct)*std::norm(comp.ts) ;  
    std::complex<T> _T_p = (std::conj(b.n)*b.ct)/(std::conj(t.n)*t.ct)*std::norm(comp.tp) ; 
    // _T_p top and bot layers usually with real index ? so the conj above just noise ?

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


