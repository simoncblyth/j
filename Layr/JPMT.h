#pragma once
/**
JPMT.h : Specific to JUNO PMTProperty, Material layout
============================================================

Instanciating JPMT.h loads properties for all PMT types from text files 
and creates and populates two arrays : rindex and thickness 
that contain all the PMT param needed for TMM ART calculation.   

This is aiming to provide the input arrays for the CPU counterpart 
of a GPU interpolator using (or doing similar to) QProp.hh/qprop.h 


Higher level variant of JPMT.h ?
----------------------------------

JPMT.h takes a very low level approach by loading the 
property files directly without using PMTSimParamSvc at all. 
That is appropriate for small scale standalone tests, but 
now need to customize G4OpBoundary and have access to the
PMT data within it in order to do the Stack calculation 
there. 

Using PMTSimParamSvc directly is not appealing because:

1. requires a bunch of irrelevant headers 
2. excess dependencies make standalone testing too difficult to setup
3. pedestrian API

So have cut out the heart of PMTSimParamSvc into PMTSimParamData. 
Hence I get access to the exact same data as the Svc but 
have full control of the API and the dependencies : fixing 
all the above problems. 



What exactly is JUNO specific, can it be split off/made an argument/configuration ?
-----------------------------------------------------------------------------------------

* PMTCAT names, num layers, property keys 

Choices
--------

1. where should this code live longterm ? 
2. where should it be used to harvest into SSim ?

Incorporating NPFold.h and updating NP.hh in 
offline would allow this to live in junosw, 
if get rid of StackSpec ?   StackSpec is rather handy though. 


**/

#include "NPFold.h"

struct JPMT
{
    static constexpr const char* _PMTType_base = "$JUNOTOP/data/Detector/Geometry" ;
    static constexpr const char* _PMTType_cats = "Unknown,NNVT,Hamamatsu,HZC,HighQENNVT" ;
    static constexpr const char* _PMTType_names = "PMTType_CD_LPMT.csv,PMTType_CD_SPMT.csv" ; 
    static constexpr int         _PMTType_catfield = 1 ; 
    static NP* LoadPMTType(const char* base, const char* cats, const char* names, int catfield, char delim=',' ); 

    static constexpr const char* _HZC = "HZC_3inch" ; 
    static constexpr const char* _WPP = "WP_PMT" ; 

    static constexpr const char* _HAMA = "R12860" ; 
    static constexpr const char* _NNVT = "NNVTMCP" ; 
    static constexpr const char* _NNVTQ = "NNVTMCP_HiQE" ; 

    static void GetNamesLPMT(  std::vector<std::string>& names );  // formerly GetNames20
    static void GetNamesAll( std::vector<std::string>& names ); 
    static int FindCatLPMT( const char* name );  // formerly FindCat20

    static constexpr int NUM_PMTCAT = 3 ; 
    static constexpr int NUM_LAYER = 4 ; 
    static constexpr int NUM_PROP = 2 ; 

    enum { HAMA, NNVT, NNVTQ }; 
    enum { L0, L1, L2, L3 } ; 
    enum { RINDEX, KINDEX } ; 

    enum { DEFAULT_CAT = HAMA }; 

    NPFold* PMTProperty ; 
    NPFold* Pyrex ; 
    NPFold* Vacuum ; 

    std::vector<const NP*> v_rindex ; 
    std::vector<const NP*> v_thickness ; 
    std::vector<const NP*> v_qe_shape ; 

    NP* rindex ;      // (num_pmtcat, num_layer, num_prop,  num_energies ~15 , num_payload:2 )    # payload is (energy, value)  
    NP* thickness ;   // (num_pmtcat, num_layer, num_payload:1 )
    double* tt ; 
    NP* qe_shape ; 
    NP* cat ; 

    JPMT(); 

    void init(); 
    void init_rindex_thickness(); 
    void init_qe_shape(); 

    const char* get_pmtcat_name( int pmtcat ) const ; 
    double get_thickness_nm(int pmtcat, int layer) const  ; 
    double get_rindex(      int pmtcat, int layer, int prop, double energy_eV ) const  ; 

    // high level API : should be close to the full (non-standalone) equivalent of JPMT.h 
    double get_pmtid_qe( int pmtid, double energy ) const ;   // placeholder returing zero 
    int    get_pmtcat( int pmtid  ) const ;  // placeholder returning DEFAULT_CAT 
    void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const ; 



#ifdef WITH_STACKSPEC
    template<typename T, int N> StackSpec<T,N> get(int pmtcat, T wavelength_nm) const ; 
#endif

    void save(const char* dir) const ; 
    std::string desc() const ; 
};

inline void JPMT::GetNamesLPMT( std::vector<std::string>& names ) // static
{
    names.push_back(_HAMA);  
    names.push_back(_NNVT);  
    names.push_back(_NNVTQ);  
}
inline void JPMT::GetNamesAll( std::vector<std::string>& names ) // static
{
    names.push_back(_HZC);  
    names.push_back(_HAMA);  
    names.push_back(_NNVT);  
    names.push_back(_NNVTQ);  
    names.push_back(_WPP);  
}

inline int JPMT::FindCatLPMT( const char* name )  // static
{
    std::vector<std::string> names ; 
    GetNamesLPMT(names); 
    size_t idx = std::distance( names.begin(), std::find( names.begin(), names.end(), name )); 
    return idx >= names.size() ? -1  : int(idx) ;  
} 


inline JPMT::JPMT()
    :
    PMTProperty(NPFold::LoadProp("PMTProperty")),
    Pyrex( NPFold::LoadProp("Material/Pyrex")),
    Vacuum(NPFold::LoadProp("Material/Vacuum")),
    rindex(nullptr),
    thickness(NP::Make<double>(NUM_PMTCAT, NUM_LAYER, 1)),
    tt(thickness->values<double>()),
    qe_shape(nullptr),
    cat(LoadPMTType(_PMTType_base, _PMTType_cats, _PMTType_names, _PMTType_catfield, ','))
{
    init(); 
}

/**
JPMT::init
---------------

Collect RINDEX, KINDEX as function of energy and THICKNESS properties 
for all PMT categories and stack layers into two arrays.::

    epsilon:~ blyth$ cd $NP_PROP_BASE/PMTProperty
    epsilon:PMTProperty blyth$ ls -1
    Dynode
    HZC_3inch
    MCP
    NNVTMCP         ## only these 3 are returned by GetNamesLPMT
    NNVTMCP_HiQE    ##
    R12860          ##
    WP_PMT


    epsilon:PMTProperty blyth$ find . -type f -exec wc -l {} \;

           3 ./WP_PMT/scale           ## key-value
          43 ./WP_PMT/QE_shape        ## vs eV
           9 ./WP_PMT/CE              ## vd deg 

           2 ./R12860/THICKNESS
           2 ./R12860/scale
          43 ./R12860/QE_shape
          14 ./R12860/PHC_RINDEX
          14 ./R12860/PHC_KINDEX
           9 ./R12860/CE
          14 ./R12860/ARC_RINDEX
           2 ./R12860/ARC_KINDEX

           2 ./NNVTMCP_HiQE/THICKNESS
           2 ./NNVTMCP_HiQE/scale
          43 ./NNVTMCP_HiQE/QE_shape
          14 ./NNVTMCP_HiQE/PHC_RINDEX
          14 ./NNVTMCP_HiQE/PHC_KINDEX
           9 ./NNVTMCP_HiQE/CE
          14 ./NNVTMCP_HiQE/ARC_RINDEX
           2 ./NNVTMCP_HiQE/ARC_KINDEX

           9 ./MCP/CE

           2 ./NNVTMCP/THICKNESS
           3 ./NNVTMCP/scale
          43 ./NNVTMCP/QE_shape
          14 ./NNVTMCP/PHC_RINDEX
          14 ./NNVTMCP/PHC_KINDEX
           9 ./NNVTMCP/CE
          14 ./NNVTMCP/ARC_RINDEX
           2 ./NNVTMCP/ARC_KINDEX

           1 ./HZC_3inch/scale
          60 ./HZC_3inch/QE_shape
           9 ./Dynode/CE



**/
inline void JPMT::init()
{
    init_rindex_thickness(); 
    init_qe_shape(); 
}

inline void JPMT::init_rindex_thickness()
{
    assert( PMTProperty ); 

    std::vector<std::string> names ; 
    GetNamesLPMT(names); 
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

/**
JPMT::init_qe_shape
----------------------

jcv IPMTParamSvc::

     33 enum PMT_CATEGORY {
     34   kPMT_Unknown=-1,
     35   kPMT_NNVT,
     36   kPMT_Hamamatsu,
     37   kPMT_HZC,
     38   kPMT_NNVT_HighQE
     39 };

::
    epsilon:PMTProperty blyth$ find . -name QE_shape -exec wc -l {} \;
          43 ./WP_PMT/QE_shape
          43 ./R12860/QE_shape
          43 ./NNVTMCP_HiQE/QE_shape
          43 ./NNVTMCP/QE_shape
          60 ./HZC_3inch/QE_shape

jcv PMTSimParamSvc::

     288 bool PMTSimParamSvc::init_default() {
     ...
     315   helper_pmt_mpt(m_QEshape_HZC, mcgt.data(),"PMTProperty.HZC_3inch.QE_shape");
     316   helper_pmt_mpt(m_QEshape_NNVT, mcgt.data(),"PMTProperty.NNVTMCP.QE_shape");
     317   helper_pmt_mpt(m_QEshape_NNVT_HiQE, mcgt.data(),"PMTProperty.NNVTMCP_HiQE.QE_shape");
     318   helper_pmt_mpt(m_QEshape_R12860, mcgt.data(),"PMTProperty.R12860.QE_shape");
     319   helper_pmt_mpt(m_QEshape_WP_PMT, mcgt.data(),"PMTProperty.WP_PMT.QE_shape");

    In [6]:  t.jpmt_qe_shape.shape
    Out[6]: (5, 61, 2)

    In [7]: t.jpmt_qe_shape[:,-1].view(np.int64)
    Out[7]: 
    array([[ 0, 60],
           [ 0, 43],
           [ 0, 43],
           [ 0, 43],
           [ 0, 43]])


PMT category files are not on laptop, so grab them::

    cd $JUNOTOP
    tar zcvf data_Detector.tar.gz data/Detector

    epsilon:junotop blyth$ scp P:junotop/data_Detector.tar.gz .

Added NP::LoadCategoryArrayFromTxtFile to load files like::

   $JUNOTOP/data/Detector/Geometry/PMTType_CD_LPMT.csv


**/

inline void JPMT::init_qe_shape()
{
    assert( PMTProperty ); 
    std::vector<std::string> names ; 
    GetNamesAll(names); 

    for(int i=0 ; i < int(names.size()) ; i++) 
    {
        const char* name = names[i].c_str(); 
        NPFold* pmt = PMTProperty->get_subfold(name); 
        const NP* a = pmt->get("QE_shape") ; 
        v_qe_shape.push_back(a) ; 
    }
    qe_shape = NP::Combine(v_qe_shape); 
    qe_shape->set_names(names);  
}

/**
JPMT::LoadPMTType
--------------------

jcv IPMTParamSvc::

     33 enum PMT_CATEGORY {
     34   kPMT_Unknown=-1,
     35   kPMT_NNVT,
     36   kPMT_Hamamatsu,
     37   kPMT_HZC,
     38   kPMT_NNVT_HighQE
     39 };


    In [1]: t.PMTType_CD
    Out[1]: 
    array([[     0,      2],
           [     1,      2],
           [     2,      4],
           [     3,      2],
           [     4,      4],
           ...,
           [325595,      3],
           [325596,      3],
           [325597,      3],
           [325598,      3],
           [325599,      3]], dtype=int32)

    In [2]: t.PMTType_CD.shape
    Out[2]: (43212, 2)


    In [4]: np.unique(t.cat[:,1], return_index=True, return_counts=True )
    Out[4]: 
    (array([1, 2, 3, 4], dtype=int32),
     array([   55,     0, 17612,     2]),
     array([ 2720,  4997, 25600,  9895]))


**/

inline NP* JPMT::LoadPMTType(const char* base, const char* cats, const char* names_, int catfield, char delim ) // static
{
    std::vector<std::string> names ;
    U::MakeVec(names, names_, delim );

    std::vector<NP*> v_cat ; 
    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i].c_str(); 
        NP* a = NPX::LoadCategoryArrayFromTxtFile(base, name, catfield, cats); 
        v_cat.push_back(a); 
    }

    NP* c = NP::Concatenate(v_cat); 
    c->set_names(names); 
    return c ;  
}

inline const char* JPMT::get_pmtcat_name( int pmtcat ) const
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


inline double JPMT::get_pmtid_qe( int pmtid, double energy ) const  // placeholder returing zero 
{
    // HMM: energy or energy_eV ? standalone uses energy_eV for GPU simularity where use float 
    return 0. ; 
}

inline int JPMT::get_pmtcat( int pmtid  ) const  // placeholder returning default 
{
    // full equivalent needs access to PMT counts and other J headers to provide this 
    return DEFAULT_CAT ; 
}
inline void JPMT::get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const 
{
    ss.fill(0.); 

    ss[4*0+0] = get_rindex(       pmtcat, L0, RINDEX, energy_eV );
 
    ss[4*1+0] = get_rindex(       pmtcat, L1, RINDEX, energy_eV );
    ss[4*1+1] = get_rindex(       pmtcat, L1, KINDEX, energy_eV );
    ss[4*1+2] = get_thickness_nm( pmtcat, L1 ); 

    ss[4*2+0] = get_rindex(       pmtcat, L2, RINDEX, energy_eV );
    ss[4*2+1] = get_rindex(       pmtcat, L2, KINDEX, energy_eV );
    ss[4*2+2] = get_thickness_nm( pmtcat, L2 ); 

    ss[4*3+0] = get_rindex(       pmtcat, L3, RINDEX, energy_eV );
}

inline void JPMT::save(const char* dir) const 
{
    // HMM: JPMT directory ? 
    rindex->save(dir, "jpmt_rindex.npy"); 
    thickness->save(dir, "jpmt_thickness.npy"); 
    qe_shape->save(dir, "jpmt_qe_shape.npy"); 
    cat->save(dir, "cat.npy"); 
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

Notice that this gets all its data from two arrays: thickness and rindex
making it straightforward to do on GPU. 

ACTUALLY WHAT I DONT LIKE ABOUT THIS IS THE SHUFFLING IN AND OUT OF THE INTERMEDIARY TYPE, 
BUT ITS KINDA EXPEDIENT 



TODO: change to energy_eV argumnent and use from u4/CustomART.h 


**/

template<typename T, int N>
inline StackSpec<T,N> JPMT::get(int pmtcat, T wavelength_nm) const  
{
    double energy_eV = sdomain::hc_eVnm/wavelength_nm ; 

    StackSpec<T,N> spec ; 
    assert( N == NUM_LAYER );   
    for(int i=0 ; i < N ; i++)
    {
        spec.ls[i].d = tt[pmtcat*NUM_LAYER+i] ; 
        spec.ls[i].nr = rindex->combined_interp_5( pmtcat, i, RINDEX, energy_eV ) ; 
        spec.ls[i].ni = rindex->combined_interp_5( pmtcat, i, KINDEX, energy_eV ) ; 
    }
    return spec ; 
}



/**
JPMT::get
----------

Trying to specialize to create a 2 layer stack from 
the 4 layer data, using first and last.  

Seems cannot do partial template specialization 
so duplicate for float and double so can do full specialization.

**/

template<> 
inline StackSpec<float,2> JPMT::get(int pmtcat, float wavelength_nm) const  
{
    StackSpec<float,2> spec ; 

    double energy_eV = sdomain::hc_eVnm/wavelength_nm ; 
    int N = 4 ; 
    float zero(0.f); 
   
    spec.ls[0].d = zero ; 
    spec.ls[0].nr = rindex->combined_interp_5( pmtcat, 0, RINDEX, energy_eV ) ; 
    spec.ls[0].ni = zero ; 

    spec.ls[1].d =  zero ; 
    spec.ls[1].nr = rindex->combined_interp_5( pmtcat, N-1, RINDEX, energy_eV ) ; 
    spec.ls[1].ni = zero ; 

    return spec ; 
}

template<> 
inline StackSpec<double,2> JPMT::get(int pmtcat, double wavelength_nm) const  
{
    StackSpec<double,2> spec ; 

    double energy_eV = sdomain::hc_eVnm/wavelength_nm ; 
    int N = 4 ; 
    double zero(0.); 

    spec.ls[0].d = zero ; 
    spec.ls[0].nr = rindex->combined_interp_5( pmtcat, 0, RINDEX, energy_eV ) ; 
    spec.ls[0].ni = zero ; 

    spec.ls[1].d = zero ; 
    spec.ls[1].nr = rindex->combined_interp_5( pmtcat, N-1, RINDEX, energy_eV ) ; 
    spec.ls[1].ni = zero ; 

    return spec ; 
}


#endif
