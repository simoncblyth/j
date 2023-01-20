
#include "OPTICKS_LOG.hh"
#include "sdirect.h"

#include "DetectorConstruction.hh"
#include "JPMT.h"
#include "Layr.h"
#include "PMTAccessor.h"

#include <CLHEP/Units/SystemOfUnits.h>


struct PMTAccessorTest
{
    static constexpr const double EPSILON = 1e-10 ; 
    static int PMTCat(int localcat); 
    static NP* Scan( const IPMTAccessor* x, unsigned num_energy ); 

    const PMTSimParamData* data ; 
    const JPMT* jpmt ; ; 

    const PMTAccessor* pmta ;
    const IPMTAccessor* a ; 
    const IPMTAccessor* b ; 

    PMTAccessorTest(); 
    std::string desc() const ; 
    void check_data_lookup() const ; 
    double compare_stackspec( int pmtcat, double energy_eV ) const ; 
    double compare_stackspec() const ; 
    static void thickness_precision_check() ; 

    NP* a_scan() const ; 
    NP* b_scan() const ; 

}; 

inline PMTAccessorTest::PMTAccessorTest()
   :
   data(PMTAccessor::LoadPMTSimParamData()),
   jpmt(new JPMT),
   pmta(PMTAccessor::Create(data)),
   a(dynamic_cast<const IPMTAccessor*>(pmta)),  
   b(dynamic_cast<const IPMTAccessor*>(jpmt)) 
{
}

std::string PMTAccessorTest::desc() const 
{
    std::stringstream ss ; 
    ss << "PMTAccessorTest::desc" << std::endl ; 
    ss << " a " << a->get_typename() << std::endl ; 
    ss << " b " << b->get_typename() << std::endl ; 
    std::string str = ss.str(); 
    return str ; 
}

void PMTAccessorTest::check_data_lookup() const 
{
    LOG(info) << desc() ; 
    int pmtcat = kPMT_Hamamatsu ; 
    double energy_eV = 5.  ; 
    double energy = energy_eV*CLHEP::eV ;

    double v = data->get_pmtcat_prop( pmtcat, "ARC_RINDEX" , energy );  
    LOG(info) << " energy " << energy << " ARC_RINDEX " << v ;  
    LOG(info) << " pmta " << pmta->desc() ;
}

double PMTAccessorTest::compare_stackspec( int pmtcat, double energy_eV ) const
{
    std::array<double, 16> aa_ ;
    std::array<double, 16> bb_ ; 
    a->get_stackspec(aa_, pmtcat, energy_eV ); 
    b->get_stackspec(bb_, pmtcat, energy_eV ); 
    double mx = sys::max_diff( aa_, bb_ );  
    if(mx > EPSILON)
    {
        StackSpec<double, 4> aa ;
        aa.import(aa_); 
     
        StackSpec<double, 4> bb ; 
        bb.import(bb_); 

        LOG(info) 
           << std::endl 
           <<  "aa_ " << aa_ 
           << std::endl 
           <<  "bb_ " << bb_ 
           << std::endl 
           << sys::desc_diff(aa_, bb_) 
           << std::endl 
           << aa.desc_compare(bb) 
           << std::endl 
           ;
    }
    return mx ; 
}

int PMTAccessorTest::PMTCat(int localcat) // static 
{
    int pmtcat = -1 ; 
    switch(localcat)
    {
       case 0:pmtcat = kPMT_Hamamatsu   ; break ; 
       case 1:pmtcat = kPMT_NNVT        ; break ; 
       case 2:pmtcat = kPMT_NNVT_HighQE ; break ; 
    }
    return pmtcat ; 
}

NP* PMTAccessorTest::Scan(const IPMTAccessor* x, unsigned num_energy ) // static
{
    int ni = 3 ; 
    int nj = num_energy ; 

    NP* scan = NP::Make<double>( ni, nj, 4, 4 ) ; 

    unsigned size = 16*sizeof(double) ;


    double en0 = 1.55 ; 
    double en1 = 15.5 ; 

    for(int i=0 ; i < ni ; i++)
    {
        int pmtcat = PMTCat(i); 
        for(int j=0 ; j < nj ; j++)
        {
            double fr = double(j)/double(nj-1) ; 
            double energy_eV = en0*(1.-fr) + en1*(fr) ;  
            std::array<double, 16> ss ; 

            x->get_stackspec(ss, pmtcat, energy_eV ); 

            char* dst = scan->bytes() + (i*nj + j)*size  ; 
            const char* src = (const char*)ss.data() ; 

            memcpy( dst,  src, size );    
        }
    }
    return scan ;
}

NP* PMTAccessorTest::a_scan() const { return Scan(a, 100); }
NP* PMTAccessorTest::b_scan() const { return Scan(b, 100); }


double PMTAccessorTest::compare_stackspec() const
{
    int pmtcat = kPMT_Hamamatsu ; 
    double energy_eV = 5.  ; 
    //double energy = energy_eV*CLHEP::eV ;
    double mx = compare_stackspec( pmtcat, energy_eV ); 
    assert( mx < EPSILON ); 
    return mx ; 
}

void PMTAccessorTest::thickness_precision_check()
{
    // try to pin down a small precision difference 

    double _thickness = 21.13 ;  
    double thickness = _thickness*1e-9*CLHEP::m ; 
    double thickness_nm = thickness/CLHEP::nm ; 
    double thickness_dt = thickness_nm - _thickness ; 

    std::cout 
        << std::setw(20) << "_thickness    " << std::setw(10) << std::scientific << _thickness    << std::endl 
        << std::setw(20) << " thickness    " << std::setw(10) << std::scientific <<  thickness    << std::endl 
        << std::setw(20) << " thickness_nm " << std::setw(10) << std::scientific <<  thickness_nm << std::endl 
        << std::setw(20) << " thickness_dt " << std::setw(10) << std::scientific <<  thickness_dt << std::endl 
        ;
}



const char* FOLD = getenv("FOLD"); 

int main(int argc, char** argv)
{
    OPTICKS_LOG(argc, argv); 

    DetectorConstruction* dc = nullptr ; 

    std::stringstream coutbuf;
    std::stringstream cerrbuf;
    {   
        sdirect::cout_ out_(coutbuf.rdbuf());
        sdirect::cerr_ err_(cerrbuf.rdbuf());
            
        dc = new DetectorConstruction ; 
        // boot G4Material from files read under $JUNOTOP  with verbosity silenced
    }        
    std::string out = coutbuf.str(); 
    std::string err = cerrbuf.str(); 
    bool VERBOSE = getenv("VERBOSE") != nullptr ;   
    std::cout << sdirect::OutputMessage("DetectorConstruction" , out, err, VERBOSE );  

    PMTAccessorTest t ; 
    t.check_data_lookup(); 
    double mx = t.compare_stackspec(); 
    LOG(info) << " mx " << mx ; 


    NP* a = t.a_scan(); 
    NP* b = t.b_scan(); 
    a->save(FOLD, "a.npy" ); 
    b->save(FOLD, "b.npy" ); 

    t.thickness_precision_check(); 

    return 0 ;
}

