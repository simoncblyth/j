#include <iostream>
#include <iomanip>
#include <functional>
#include <cstdlib>
#include <cassert>

#include <CLHEP/Units/SystemOfUnits.h>

#include "SniperKernel/TopTask.h"
#include "SniperKernel/Sniper.h"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/Task.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"

#include "Geometry/PMTParamSvc.h"
#include "Geometry/PMT.h"
#include "Geometry/PMTCategory.h"

// The below includes need special include_directories setting in CMakeLists.txt 
// in order to grab from src directories.
//
// HMM : perhaps the interface should have initialize to avoid needing these headers ?

#include "src/PMTSimParamSvc.h"
#include "src/MCParamsFileSvc.hh"  


#include "NPFold.h"
#include "NP.hh"

#include <chrono>

namespace schrono
{
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP ; 
    typedef std::chrono::duration<double> DT ; 

    inline std::chrono::time_point<std::chrono::high_resolution_clock> stamp()
    {   
        TP t = std::chrono::high_resolution_clock::now();
        return t ; 
    }   
    inline double duration( 
        std::chrono::time_point<std::chrono::high_resolution_clock>& t0, 
        std::chrono::time_point<std::chrono::high_resolution_clock>& t1 )
    {   
        DT _dt = t1 - t0; 
        double dt = _dt.count() ;
        return dt ; 
    }   
}




IPMTSimParamSvc* Get_IPMTSimParamSvc()
{
    Task* top  = new TopTask("top"); 

    Sniper::loadDll("libGeometry.so"); 
    Sniper::loadDll("libMCParamsSvc.so"); 
    Sniper::loadDll("libPMTSimParamSvc.so"); 

    std::cout << " Sniper::dlls() " << Sniper::dlls() << std::endl ; 

    PMTParamSvc*     pps = dynamic_cast<PMTParamSvc*>(top->createSvc("PMTParamSvc")); 
    pps->initialize(); 

    MCParamsFileSvc* mpfs = dynamic_cast<MCParamsFileSvc*>(top->createSvc("MCParamsFileSvc/MCParamsSvc"));
    mpfs->initialize(); 

    PMTSimParamSvc* psps = dynamic_cast<PMTSimParamSvc*>(top->createSvc("PMTSimParamSvc")); 
    psps->initialize(); 

    SniperPtr<IPMTSimParamSvc> psps_ptr(*top, "PMTSimParamSvc"); 

    if(psps_ptr.invalid()) 
    {
        std::cout << "invalid" << std::endl ;  
        return nullptr ; 
    }

    IPMTSimParamSvc* ipsps = psps_ptr.data(); 
    return ipsps ; 
}


NP* scan_di( std::function<double(int)> fn, const std::vector<int>& ii  )
{
    int ni = ii.size() ; 
    NP* a = NP::Make<double>( ni );
    double* aa = a->values<double>() ;    

    schrono::TP t0 = schrono::stamp();

    for(int i=0 ; i < ni ; i++) aa[i] = fn(ii[i]) ;

    schrono::TP t1 = schrono::stamp();
    double dt = schrono::duration(t0, t1 );  
    a->set_meta<double>("scantime", dt );  

    return a ; 
}

NP* scan_did( std::function<double(int, double)> fn, const std::vector<int>& ii, const std::vector<double>& jj )
{
    int ni = ii.size() ; 
    int nj = jj.size() ; 
    NP* a = NP::Make<double>( ni, nj );
    double* aa = a->values<double>() ;    

    schrono::TP t0 = schrono::stamp();

    for(int i=0 ; i < ni ; i++) for(int j=0 ; j < nj ; j++) aa[i*nj+j] = fn(ii[i], jj[j]) ;

    schrono::TP t1 = schrono::stamp();
    double dt = schrono::duration(t0, t1 );  
    a->set_meta<double>("scantime", dt );  

    return a ; 
} 


namespace PMTID
{
    bool IsLPMT(int pmtID){ return pmtID >= kOFFSET_CD_LPMT && pmtID < kOFFSET_WP_PMT ; }
    bool IsWPMT(int pmtID){ return pmtID >= kOFFSET_WP_PMT  && pmtID < kOFFSET_CD_SPMT ; }
    bool IsSPMT(int pmtID){ return pmtID >= kOFFSET_CD_SPMT ; }
}

struct Scan
{
    static void Linspace( std::vector<double>& val, double v0, double v1, int num ); 

    IPMTSimParamSvc* ipsps ; 
    NPFold* fold ; 

    const std::vector<int>& all_pmtID ; 
    std::vector<int> lpmtID ; 
    std::vector<int> spmtID ; 
    std::vector<int> wpmtID ; 

    std::vector<int> all_pmtcat ; 
    std::vector<double> energy ; 
    std::vector<double> theta ; 

    static constexpr const char* PROP = "ARC_RINDEX ARC_KINDEX PHC_RINDEX PHC_KINDEX" ;  
    std::vector<std::string> prop ; 

    int num_id ; 
    int num_cat ; 
    int num_energy ; 
    int num_theta ; 
  
    Scan(IPMTSimParamSvc* ipsps); 

    std::string desc() const ; 
    void init(); 
    void add_scan(const char* name, NP* a);
    void add_scan();
    void save() const ; 

};

inline void Scan::Linspace( std::vector<double>& val, double v0, double v1, int num ) // static
{
    val.resize(num); 
    for(int j=0 ; j < num ; j++)
    {
        double fr = double(j)/double(-1) ; 
        val[j] = v0*(1.-fr) + v1*fr ;  
    }
}

inline Scan::Scan(IPMTSimParamSvc* ipsps_ )
    :
    ipsps(ipsps_),
    fold(new NPFold),
    all_pmtID(ipsps->get_all_pmtID()),
    all_pmtcat( {kPMT_Unknown, kPMT_NNVT, kPMT_Hamamatsu, kPMT_HZC, kPMT_NNVT_HighQE }),
    num_id(all_pmtID.size()),
    num_cat(all_pmtcat.size()),
    num_energy(-1),
    num_theta(-1)
{
    init(); 
}

inline std::string Scan::desc() const 
{
    std::stringstream ss ; 
    ss << "Scan::desc"
       << " num_id  " << num_id << std::endl 
       << " num_cat " << num_cat << std::endl 
       << " num_theta " << num_theta << std::endl 
       << " num_energy " << num_energy << std::endl 
       ; 

    std::string str = ss.str(); 
    return str ; 
}


inline void Scan::init()
{
    Linspace(energy, 1.55*CLHEP::eV, 15.5*CLHEP::eV, 100 ); 
    num_energy = energy.size(); 

    Linspace(theta, 0.*CLHEP::degree, 90.*CLHEP::degree, 100 ); 
    num_theta = theta.size();  

    std::stringstream ss(PROP); 
    std::string str;
    while (std::getline(ss, str, ' ')) prop.push_back(str) ; 

    for(int i=0 ; i < int(all_pmtID.size()) ; i++)
    {
        int pmtID = all_pmtID[i] ; 
        if(     PMTID::IsLPMT(pmtID)) lpmtID.push_back(pmtID) ; 
        else if(PMTID::IsWPMT(pmtID)) wpmtID.push_back(pmtID) ; 
        else if(PMTID::IsSPMT(pmtID)) spmtID.push_back(pmtID) ; 
        else assert(0) ; 
    }

}
inline void Scan::add_scan(const char* name, NP* a)
{
    std::cout << "Scan::add_scan " << name << std::endl ; 
    fold->add(name, a);  
}

inline void Scan::add_scan()
{
    typedef std::function<double(int, double)> DID ; 
    typedef std::function<double(int)>         DI ;  
    using std::placeholders::_1 ; 
    using std::placeholders::_2 ; 

    DI _get_gain              = std::bind( &IPMTSimParamSvc::get_gain,             ipsps, _1 ); 
    DI _get_sigmaGain         = std::bind( &IPMTSimParamSvc::get_sigmaGain,        ipsps, _1 ); 
    DI _get_pde               = std::bind( &IPMTSimParamSvc::get_pde,              ipsps, _1 ); 
    DI _get_dcr               = std::bind( &IPMTSimParamSvc::get_dcr,              ipsps, _1 ); 
    DI _get_afterPulseProb    = std::bind( &IPMTSimParamSvc::get_afterPulseProb,   ipsps, _1 ); 
    DI _get_prePulseProb      = std::bind( &IPMTSimParamSvc::get_prePulseProb,     ipsps, _1 ); 
    DI _get_tts               = std::bind( &IPMTSimParamSvc::get_tts,              ipsps, _1 ); 
    DI _get_timeOffset        = std::bind( &IPMTSimParamSvc::get_timeOffset,       ipsps, _1 ); 
    DI _get_efficiency        = std::bind( &IPMTSimParamSvc::get_efficiency,       ipsps, _1 ); 
    DI _get_QE                = std::bind( &IPMTSimParamSvc::get_QE,               ipsps, _1 ); 

    DID _get_pmtid_ce         = std::bind( &IPMTSimParamSvc::get_pmtid_ce,         ipsps, _1, _2 ); 
    DID _get_pmtcat_ce        = std::bind( &IPMTSimParamSvc::get_pmtcat_ce,        ipsps, _1, _2 ); 
    DID _get_pmtid_qe         = std::bind( &IPMTSimParamSvc::get_pmtid_qe,         ipsps, _1, _2 ); 
    DID _get_pmtcat_qe        = std::bind( &IPMTSimParamSvc::get_pmtcat_qe,        ipsps, _1, _2 ); 

    DI  _get_pmt_qe_scale     = std::bind( &IPMTSimParamSvc::get_pmt_qe_scale,     ipsps, _1 ); 
    DI  _get_shape_qe_at420nm = std::bind( &IPMTSimParamSvc::get_shape_qe_at420nm, ipsps, _1 ); 
    DI  _get_real_qe_at420nm  = std::bind( &IPMTSimParamSvc::get_real_qe_at420nm,  ipsps, _1 ); 

    add_scan( "get_gain",             scan_di( _get_gain,             all_pmtID ) ); 
    add_scan( "get_sigmaGain",        scan_di( _get_sigmaGain,        all_pmtID ) ); 
    add_scan( "get_pde_lpmt",         scan_di( _get_pde,              lpmtID ) );    
    add_scan( "get_dcr",              scan_di( _get_dcr,              all_pmtID ) ); 
    add_scan( "get_afterPulseProb",   scan_di( _get_afterPulseProb,   all_pmtID ) ); 
    add_scan( "get_prePulseProb",     scan_di( _get_prePulseProb,     all_pmtID ) ); 
    add_scan( "get_tts",              scan_di( _get_tts,              all_pmtID ) ); 
    add_scan( "get_timeOffset",       scan_di( _get_timeOffset,       all_pmtID ) ); 
    add_scan( "get_efficiency",       scan_di( _get_efficiency,       spmtID ) ); 
    add_scan( "get_QE",               scan_di( _get_QE,               spmtID ) ); 

    add_scan( "get_pmtid_ce",         scan_did(_get_pmtid_ce,         all_pmtID,  theta ) ); 
    add_scan( "get_pmtcat_ce",        scan_did(_get_pmtcat_ce,        all_pmtcat, theta ) ); 
    add_scan( "get_pmtid_qe",         scan_did(_get_pmtid_qe,         all_pmtID,  energy ) ); 
    add_scan( "get_pmtcat_qe",        scan_did(_get_pmtcat_qe,        all_pmtcat, energy ) ); 

    add_scan( "get_pmt_qe_scale",     scan_di( _get_pmt_qe_scale,     all_pmtID ) ); 
    add_scan( "get_shape_qe_at420nm", scan_di( _get_shape_qe_at420nm, all_pmtID ) ); 
    add_scan( "get_real_qe_at420nm",  scan_di( _get_real_qe_at420nm,  all_pmtID ) ); 
}

inline void Scan::save() const 
{
    char* FOLD = getenv("FOLD"); 
    std::cout << " save to FOLD " << ( FOLD ? FOLD : "-" ) << std::endl;
    assert(FOLD); 
    fold->save(FOLD); 
}

int main(int, char**)
{
    IPMTSimParamSvc* ipsps = Get_IPMTSimParamSvc(); 
    std::cout << " ipsps " << ipsps << std::endl ; 
    if(ipsps == nullptr) return 1 ; 

    Scan scan(ipsps) ; 
    std::cout << scan.desc() << std::endl ; 
    scan.add_scan(); 
    scan.save(); 

    return 0 ; 
}
