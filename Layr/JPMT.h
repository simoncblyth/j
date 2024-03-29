#pragma once
/**
JPMT.h : Specific to JUNO PMTProperty, Material layout
============================================================

Instanciating JPMT.h loads properties for all PMT types from text files 
and creates and populates two arrays : rindex and thickness 
that contain all the PMT param needed for TMM ART calculation.   

This is aiming to provide the input arrays for the CPU counterpart 
of a GPU interpolator using (or doing similar to) QProp.hh/qprop.h 


* DONE : reimplement JPMT.h in different struct SPMT.h
  operating from the full serialized PMT NPFold rather that the prop txt files


Usage
-------

::

    #include "JPMT.h"
    JPMT* JPMT::INSTANCE = nullptr ;   
    // plant static into compilation unit as JPMT.h is headeronly 



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
#include "C4IPMTAccessor.h"

struct JPMT : public C4IPMTAccessor
{
    static JPMT* INSTANCE ; 
    static JPMT* Get(); 

    static constexpr const char* _TypeName = "JPMT" ;  
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

    static int FindIndex(const std::vector<std::string>& names, const char* name); 
    static int FindCatLPMT( const char* name );  // formerly FindCat20
    static int FindCatAll( const char* name ); 

    static constexpr int NUM_PMTCAT = 3 ; 
    static constexpr int NUM_LAYER = 4 ; 
    static constexpr int NUM_PROP = 2 ; 

    /*  
    static constexpr const double EN0 = 1.55 ;
    static constexpr const double EN1 = 4.20 ;  // 15.5 
    static constexpr const int   NEN = 420 - 155 + 1 ;
    */  
 
    static constexpr const double EN0 = 1.55 ;
    static constexpr const double EN1 = 15.5 ;  
    static constexpr const int   NEN = 1550 - 155 + 1 ;

    // enum { HAMA, NNVT, NNVTQ };  old arbitrary order
    enum { NNVT, HAMA, NNVTQ };  // following "jcv PMTCategory" enum order

    enum { L0, L1, L2, L3 } ; 
    enum { RINDEX, KINDEX } ; 

    enum { DEFAULT_CAT = HAMA }; 

    NPFold* PMTProperty ; 
    NPFold* Pyrex ; 
    NPFold* Vacuum ; 

    std::array<int, 5> mapcat ; 
    std::vector<const NP*> v_rindex ; 
    std::vector<const NP*> v_qeshape ; 

    NP* rindex ;      // (num_pmtcat, num_layer, num_prop,  num_energies ~15 , num_payload:2 )    # payload is (energy, value)  
    NP* thickness ;   // (num_pmtcat, num_layer, num_payload:1 )
    double* tt ; 
    NP* qeshape ; 
    NP* lcqs ;    // placeholder to match SPMT.h 

    NP* cat ; 

    JPMT(); 

    void init(); 
    void init_rindex_thickness(); 
    void init_qeshape(); 
    void init_mapcat(); 

    double get_energy(int j, int nj) const ;

    std::string desc_mapcat() const ; 
    int get_localcat( int pmtcat_ ) const ;   // NOW DOES NO MAPPING 
    int get_localcat_old( int pmtcat_ ) const ; 

    const char* get_pmtcat_name( int pmtcat ) const ; 
    double get_thickness_nm(int pmtcat, int layer) const  ; 
    double get_rindex(      int pmtcat, int layer, int prop, double energy_eV ) const  ; 

    // high level API fulfilling IPMTAccessor.h protocol base (common with non-standalone accessor)
    double get_pmtid_qe( int pmtid, double energy ) const ;   // placeholder returing zero 
    double get_qescale( int pmtid ) const ;   // placeholder returning zero 
    int    get_pmtcat( int pmtid  ) const ;  // placeholder returning DEFAULT_CAT 
    void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const ; 
    NP*     get_stackspec() const ; 


    static NPFold* Serialize() ; 
    NPFold* serialize() const ;  // formerly get_fold

    NPFold* make_testfold() const ; 

    const char* get_typename() const ; 
    int get_num_lpmt() const ; 


#ifdef WITH_STACKSPEC
    template<typename T, int N> StackSpec<T,N> get(int pmtcat, T wavelength_nm) const ; 
#endif

    void save(const char* dir) const ; 
    std::string desc() const ; 
};

inline void JPMT::GetNamesLPMT( std::vector<std::string>& names ) // static
{
/*
    names.push_back(_HAMA);  
    names.push_back(_NNVT);  
    names.push_back(_NNVTQ);  
*/
    // reorder to same as PMTCategory enum numerical order AND also same as JPMT enum  
    names.push_back(_NNVT);  
    names.push_back(_HAMA);  
    names.push_back(_NNVTQ);  
}
inline void JPMT::GetNamesAll( std::vector<std::string>& names ) // static
{
    names.push_back(_WPP);   // follow PMT_CATEGORY enum order 
    names.push_back(_NNVT);  
    names.push_back(_HAMA);  
    names.push_back(_HZC);  
    names.push_back(_NNVTQ);  
}


inline int JPMT::FindIndex(const std::vector<std::string>& names, const char* name) // static
{
    size_t idx = std::distance( names.begin(), std::find( names.begin(), names.end(), name )); 
    return idx >= names.size() ? -1  : int(idx) ;  
}
inline int JPMT::FindCatLPMT( const char* name )  // static
{
    std::vector<std::string> names ; 
    GetNamesLPMT(names); 
    return FindIndex(names, name); 
} 
inline int JPMT::FindCatAll( const char* name )  // static
{
    std::vector<std::string> names ; 
    GetNamesAll(names); 
    return FindIndex(names, name); 
} 


JPMT* JPMT::INSTANCE = nullptr ; 

inline JPMT* JPMT::Get()  // static
{
    if(INSTANCE == nullptr) new JPMT ; 
    assert(INSTANCE) ; 
    return INSTANCE ; 
}

/**
JPMT::JPMT based on NPFold::LoadProp low level access to property text files
------------------------------------------------------------------------------

::

    epsilon:~ blyth$ echo $NP_PROP_BASE
    /Users/blyth/junotop/data/Simulation/DetSim
    epsilon:~ blyth$ l $NP_PROP_BASE/
    total 0
    0 drwxr-xr-x   5 blyth  staff   160 Oct 27  2022 ..
    0 drwxr-xr-x   6 blyth  staff   192 Oct 27  2022 .
    0 drwxr-xr-x   9 blyth  staff   288 Oct 27  2022 PMTProperty
    0 drwxr-xr-x   3 blyth  staff    96 Oct 27  2022 PhysiSim
    0 drwxr-xr-x  35 blyth  staff  1120 Oct 27  2022 Material
    0 drwxr-xr-x   3 blyth  staff    96 Oct 27  2022 VoxelMethod


**/

inline JPMT::JPMT()
    :
    PMTProperty(NPFold::LoadProp("PMTProperty")),
    Pyrex( NPFold::LoadProp("Material/Pyrex")),
    Vacuum(NPFold::LoadProp("Material/Vacuum")),
    rindex(nullptr),
    thickness(NP::Make<double>(NUM_PMTCAT, NUM_LAYER, 1)),
    tt(thickness->values<double>()),
    qeshape(nullptr),
    lcqs(nullptr),
    cat(LoadPMTType(_PMTType_base, _PMTType_cats, _PMTType_names, _PMTType_catfield, ','))
{
    INSTANCE = this ; 
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
    init_qeshape(); 
    init_mapcat(); 
}


/**
JPMT::init_rindex_thickness
-----------------------------

1. collect NUM_PMTCAT*NUM_LAYER*NUM_PROP (3*4*2=24) arrays into v_rindex 
2. collect NUM_PMTCAT*NUM_LAYER (3*4=12) thickness values into tt
3. create rindex array with NP::Combine(v_rindex) that combines 2D property arrays 
   of different item counts into a 3D array with the largest item plus one count 
   as the mid dimension. The plus one is used to encode the size into the last column.   
4. change rindex array shape into more intuitive (NUM_PMTCAT, NUM_LAYER, NUM_PROP, max-item-count+1, 2 )
5. collect PMTCAT names into rindex and thickness array names 

**/

inline void JPMT::init_rindex_thickness()
{
    assert( PMTProperty ); 

    std::vector<std::string> names ; 
    GetNamesLPMT(names); 
    assert( names.size() == NUM_PMTCAT ); 

    for(int i=0 ; i < NUM_PMTCAT ; i++)   // NUM_PMTCAT:3
    {
        const char* name = names[i].c_str(); 
        NPFold* pmt = PMTProperty->get_subfold(name); 
        const NP* pmt_thickness = pmt->get("THICKNESS") ; 
        // p_thickness is funny named value property array 

        for(int j=0 ; j < NUM_LAYER ; j++)   // NUM_LAYER:4 
        {
            for(int k=0 ; k < NUM_PROP ; k++)   // NUM_PROP:2 (RINDEX,KINDEX) 
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
JPMT::init_qeshape
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

inline void JPMT::init_qeshape() // not currently used
{
    assert( PMTProperty ); 
    std::vector<std::string> names ; 
    //GetNamesAll(names); 
    GetNamesLPMT(names); 

    for(int i=0 ; i < int(names.size()) ; i++) 
    {
        const char* name = names[i].c_str(); 
        NPFold* pmt = PMTProperty->get_subfold(name); 
        const NP* a = pmt->get("QE_shape") ; 
        v_qeshape.push_back(a) ; 
    }
    qeshape = NP::Combine(v_qeshape); 
    qeshape->set_names(names);  
}

/**
JPMT::init_mapcat
--------------------

std::array<int, 5>

**/


inline void JPMT::init_mapcat()
{
    std::vector<std::string> names_all ; 
    GetNamesAll(names_all);
    std::vector<std::string> names_lpmt ; 
    GetNamesLPMT(names_lpmt);
    
    for(int i=0 ; i < int(names_all.size()) ; i++) 
    {
        const char* name = names_all[i].c_str(); 
        int idx = FindIndex( names_lpmt,  name ); 
        mapcat[i] = idx ;   // standard cat offset by one mapping to localcat
    } 

    //std::cout << desc_mapcat() ; 
} 

inline std::string JPMT::desc_mapcat() const 
{
    std::vector<std::string> names_all ; 
    GetNamesAll(names_all);
 
    std::stringstream ss ; 
    ss << "JPMT::desc_mapcat" << std::endl ; 
    for(unsigned i=0 ; i < mapcat.size() ; i++) 
    {
        const char* name = names_all[i].c_str(); 
        int idx = mapcat[i] ; 
        ss
           << " i " << std::setw(3) << i 
           << " name "   << std::setw(20) << name 
           << " idx "    << std::setw(4) << idx 
           << std::endl 
           ;  
    }
    std::string str = ss.str(); 
    return str ; 
}


inline double JPMT::get_energy(int j, int nj) const
{
    double fr = double(j)/double(nj-1) ;
    double en = EN0*(1.-fr) + EN1*fr ;
    return en ;
}



/**
JPMT::get_localcat
--------------------

Decided to deal directly in localcat 0,1,2 rather than diddle 

**/

inline int JPMT::get_localcat( int cat ) const 
{
    assert( cat == 0 || cat == 1 || cat == 2 );  
    return cat ; 
}


/**
JPMT::get_localcat_old
------------------------

HMM: given the small number of cats and smallness of the 
data it would be simpler to live with gaps in the arrays 
and just use 1+pmtcat_ directly avoiding mapcat ?

**/

inline int JPMT::get_localcat_old( int pmtcat_ ) const 
{
    assert( pmtcat_ >= -1 && pmtcat_ <= 3 ); 
    int localcat = mapcat[1+pmtcat_] ;   // need to offset as kPMT_Unknown=-1 (corres to WP)
    assert( localcat >= 0 && localcat <= 2 ); 
    return localcat ; 
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
        case NNVT : n = _NNVT  ; break ; 
        case HAMA : n = _HAMA  ; break ; 
        case NNVTQ: n = _NNVTQ ; break ; 
    } 
    return n ; 
}

inline double JPMT::get_thickness_nm(int pmtcat, int layer) const  
{
    int localcat = get_localcat(pmtcat) ; 
    assert( localcat < NUM_PMTCAT && localcat >= 0); 
    assert( layer < NUM_LAYER ) ; 
    return tt[localcat*NUM_LAYER+layer] ; 
}

inline double JPMT::get_rindex(int pmtcat, int layer, int prop, double energy_eV ) const  
{
    int localcat = get_localcat(pmtcat) ; 

    assert( localcat < NUM_PMTCAT && localcat >= 0); 
    assert( layer < NUM_LAYER ) ; 
    assert( prop < NUM_PROP ); 

    return rindex->combined_interp_5( localcat, layer, prop, energy_eV ) ; 
}


inline double JPMT::get_pmtid_qe( int pmtid, double energy ) const  // placeholder returing zero 
{
    return 0. ; 
}
inline double JPMT::get_qescale( int pmtid ) const  // placeholder returing zero 
{
    return 0. ; 
}
inline int JPMT::get_num_lpmt() const 
{
    return 0 ; 
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

inline NP* JPMT::get_stackspec() const
{
    int ni = NUM_PMTCAT ; 
    int nj = NEN ; 
    int nk = 4 ; 
    int nl = 4 ; 

    NP* a = NP::Make<double>(ni, nj, nk, nl );
    double* aa = a->values<double>();

    std::array<double, 16> spec ; 
 
    for(int i=0 ; i < ni ; i++)
    for(int j=0 ; j < nj ; j++)
    {
       double en = get_energy(j, nj );
       get_stackspec(spec, i, en );
       int idx = i*nj*nk*nl + j*nk*nl ;
       memcpy( aa+idx, spec.data(), nk*nl*sizeof(double) );
    }
    return a ;
}


inline NPFold* JPMT::Serialize() // static
{
    JPMT jpmt ; 
    return jpmt.serialize() ; 
}

inline NPFold* JPMT::serialize() const // formerly get_fold
{
    NPFold* fold = new NPFold ; 
    fold->add("rindex", rindex) ; 
    fold->add("thickness", thickness) ;
    fold->add("qeshape", qeshape) ;
    //fold->add("lcqs", lcqs) ;
    return fold ; 
}
inline NPFold* JPMT::make_testfold() const
{
    NPFold* f = new NPFold ;
    f->add("get_stackspec", get_stackspec() ); 
    return f ; 
}


inline const char* JPMT::get_typename() const 
{
    return _TypeName ; 
}



inline void JPMT::save(const char* dir) const 
{
    // HMM: JPMT directory ? 
    rindex->save(dir, "jpmt_rindex.npy"); 
    thickness->save(dir, "jpmt_thickness.npy"); 
    qeshape->save(dir, "jpmt_qeshape.npy"); 
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
