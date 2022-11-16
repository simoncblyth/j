/**
junoPMTOpticalModelTest.cc
===========================

Try to setup a standlone single PMT test with junoPMTOpticalModel 

**/

#include <sstream>
#include <iostream>

#include "G4String.hh"

#include "DetectorConstruction.hh"
#include "HamamatsuR12860PMTManager.hh"
#include "junoPMTOpticalModel.hh"

#include "Layr.h"
#include "SDirect.hh"
#include "NP.hh"

template<typename T>
struct ART_Scan 
{
    int      ni ;     // number of items : currently angles 
    T        wl ;     // hmm could vary wl, by making this an array 
    T*       mct ;    // minus_cos_theta from -1 to 1, > 0 is backwards stack
    ART_<T>* arts ; 
    Layr<T>* comps ;
    Layr<T>* lls ;
};


template<typename T>
struct junoPMTOpticalModelTest
{
    ART_Scan<T>                h ; 
    bool                       verbose ; 
    const char*                label ; 

    DetectorConstruction*      dc ; 
    HamamatsuR12860PMTManager* mgr ; 
    G4LogicalVolume*           lv ; 
    junoPMTOpticalModel*       pom ; 

    junoPMTOpticalModelTest(T wavelength_nm=440, int ni=900); 
    void init(); 
    void initscan(T wavelength_nm, int ni); 
    void scan(); 

    const char* get_name() const ; 
    std::string title() const ; 
    std::string brief() const ; 
    std::string desc() const ; 
}; 

template<typename T>
junoPMTOpticalModelTest<T>::junoPMTOpticalModelTest(T wavelength_nm, int ni)
    :
    verbose(getenv("VERBOSE")!=nullptr),
    label("R12860"),
    dc(nullptr),
    mgr(nullptr),
    lv(nullptr),  // calls the init
    pom(nullptr)
{
    init();
    initscan(wavelength_nm, ni); 
}


template<typename T>
void junoPMTOpticalModelTest<T>::init()
{
    std::stringstream coutbuf;
    std::stringstream cerrbuf;
    {
        cout_redirect out_(coutbuf.rdbuf());
        cerr_redirect err_(cerrbuf.rdbuf());
   
        dc = new DetectorConstruction ; 
    }
    std::string out = coutbuf.str();
    std::string err = cerrbuf.str();
    std::cout << OutputMessage("junoPMTOpticalModelTest::init" , out, err, verbose );

    assert( strcmp(label, "R12860") == 0 ); 

    G4String plabel = label ; 
    mgr = new HamamatsuR12860PMTManager(plabel) ;
    // TODO: Hamamatsu_R12860_PMTSolid.cc does some "Ellipse_Intersect_Circle " printf not caught by redirect

    lv = mgr->getLV() ; 
    pom = mgr->pmtOpticalModel ; 
}


template<typename T>
void junoPMTOpticalModelTest<T>::initscan(T wavelength_nm, int ni)
{
    h.wl = wavelength_nm  ; 
    h.ni = ni ; 
    h.mct = new T[ni] ; 
    h.arts  = new ART_<T>[ni] ; 
    h.comps = new Layr<T>[ni] ; 
    h.lls   = new Layr<T>[4*ni] ; 
}

template<typename T>
void junoPMTOpticalModelTest<T>::scan()
{
    using CLHEP::twopi ; 
    using CLHEP::hbarc ; 
    T energy =  twopi*hbarc/(nm*h.wl) ; 

    bool half = false ; 
    T max_theta_pi = half ? T(1)/T(2) : T(1) ;   
    bool end_one = half ? false : true ;

    int ni = h.ni ; 

    for(int i=0 ; i < ni ; i++ ) 
    {   
        T frac =  T(i)/T(end_one ? ni-1 : ni) ;   
        T theta = frac*max_theta_pi*M_PI ; 
        h.mct[i] = -cos(theta) ;   
    }   

    for(int i=0 ; i < ni ; i++ ) 
    {
        T minus_cos_theta = h.mct[i] ; 
        ART_<T>& art = h.arts[i] ; 
        Layr<T>& comp = h.comps[i] ; 
        Layr<T>* ll = &h.lls[4*i+0] ; 

        pom->CalculateCoefficients(art, comp, ll, energy, minus_cos_theta); 
        //std::cout << art << std::endl ;
    }

    const char* name = get_name() ; 

    const char* base = U::GetEnv("BASE", "/tmp/junoPMTOpticalModelTest") ; 
    NP* _arts = NP::Make<T>( h.ni, 3, 4 );
    _arts->read2( (T*)h.arts );
    _arts->set_meta<std::string>("title", title() );
    _arts->set_meta<std::string>("brief", brief() );
    _arts->set_meta<std::string>("label", label );
    _arts->set_meta<std::string>("name", name);

    _arts->set_meta<T>("wl", h.wl);
    _arts->save(base, name, "arts.npy" );

    NP::Write(base, name,"comps.npy",(T*)h.comps, h.ni,    4, 4, 2 ) ;
    NP::Write(base, name,"lls.npy",  (T*)h.lls  , h.ni, 4, 4, 4, 2 ) ;

    // /tmp/blyth/opticks/LayrTest/scan__R12860__gpu_thr_float 
}

template<typename T>
const char* junoPMTOpticalModelTest<T>::get_name() const 
{
    std::stringstream ss ; 
    ss  
       << "scan__" 
       << ( label ? label : "-" )
       << "__"
       << "cpu" 
       << "_" 
       << "pom"
       << "_" 
       << ( sizeof(T) == 8 ? "double" : "float" )
       ;
    std::string s = ss.str();
    return strdup(s.c_str()) ;
}

template<typename T>
std::string junoPMTOpticalModelTest<T>::title() const 
{
    const char* name = get_name() ; 
    std::stringstream ss ; 
    ss  
        << "j/PMTFastSim/tests/junoPMTOpticalModelTest"
        << " " << name
        << " ni " << h.ni    
        << " wl " << h.wl
        ;   
    std::string s = ss.str(); 
    return s ; 
}

template<typename T>
std::string junoPMTOpticalModelTest<T>::brief() const
{   
    const char* name = get_name() ;
    std::stringstream ss ;
    ss  
        << "junoPMTOpticalModelTest"
        << "<"  
        << ( sizeof(T) == 8 ? "double" : "float" )
        << ">"   
        << " name " << name
        << " ni " << h.ni
        << " wl " << h.wl        
        << " mct[0] " << h.mct[0]
        << " mct[ni-1] " << h.mct[h.ni-1]
        ; 
    std::string s = ss.str();
    return s ;
}

template<typename T>
std::string junoPMTOpticalModelTest<T>::desc() const 
{
    std::stringstream ss ; 
    ss << "junoPMTOpticalModelTest::desc"
       << " mgr " << ( mgr ? "Y" : "N" )
       << " lv " << ( lv ? "Y" : "N" )
       << " pom " << ( pom ? "Y" : "N" )
       ;
    std::string s = ss.str(); 
    return s ; 
}

int main(int argc, char** argv)
{
    junoPMTOpticalModelTest<double> t ; 
    std::cout << t.desc() << std::endl ; 
    t.scan() ; 

    return 0 ; 
}

