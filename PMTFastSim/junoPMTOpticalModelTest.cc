/**
junoPMTOpticalModelTest.cc
===========================

Try to setup a standlone single PMT test with junoPMTOpticalModel 

NEXT:

* get ../PMTSim/DetectorConstruction.cc integrated so have the materials

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
    G4String                   label ; 
    DetectorConstruction*      dc ; 
    HamamatsuR12860PMTManager* mgr ; 
    G4LogicalVolume*           lv ; 
    junoPMTOpticalModel*       pmtOpticalModel ; 

    junoPMTOpticalModelTest(); 
    void init(); 
    std::string desc() const ; 

    void calculateCoefficients(T wavelength_nm); 

}; 

template<typename T>
junoPMTOpticalModelTest<T>::junoPMTOpticalModelTest()
    :
    verbose(getenv("VERBOSE")!=nullptr),
    label("junoPMTOpticalModelTest"),
    dc(nullptr),
    mgr(nullptr),
    lv(nullptr),  // calls the init
    pmtOpticalModel(nullptr)
{
    init();
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


    mgr = new HamamatsuR12860PMTManager(label) ;
    // TODO: Hamamatsu_R12860_PMTSolid.cc does some "Ellipse_Intersect_Circle " printf not caught by redirect

    lv = mgr->getLV() ; 
    pmtOpticalModel = mgr->pmtOpticalModel ; 

}


template<typename T>
void junoPMTOpticalModelTest<T>::calculateCoefficients(T wavelength_nm)
{
    using CLHEP::twopi ; 
    using CLHEP::hbarc ; 
    T energy =  twopi*hbarc/(nm*wavelength_nm) ; 

    int ni = 900 ; 

    h.ni = ni ; 
    h.wl = wavelength_nm  ; 
    h.mct = new T[ni] ; 
    h.arts  = new ART_<T>[ni] ; 
    h.comps = new Layr<T>[ni] ; 
    h.lls   = new Layr<T>[4*ni] ; 

    bool half = false ; 
    T max_theta_pi = half ? T(1)/T(2) : T(1) ;   
    bool end_one = half ? false : true ;

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

        pmtOpticalModel->CalculateCoefficients(art, comp, ll, energy, minus_cos_theta); 
        //std::cout << art << std::endl ;
    }


    const char* title = "title" ; 
    const char* brief = "brief" ; 
    const char* label = "label" ; 
    const char* name = "scan__R12860__cpu_pom_double" ; 

    const char* base = U::GetEnv("BASE", "/tmp/junoPMTOpticalModelTest") ; 
    NP* _arts = NP::Make<T>( h.ni, 3, 4 );
    _arts->read2( (T*)h.arts );
    _arts->set_meta<std::string>("title", title);
    _arts->set_meta<std::string>("brief", brief);
    _arts->set_meta<std::string>("label", label);
    _arts->set_meta<std::string>("name", name);

    _arts->set_meta<T>("wl", h.wl);
    _arts->save(base, name, "arts.npy" );

    NP::Write(base, name,"comps.npy",(T*)h.comps, h.ni,    4, 4, 2 ) ;
    NP::Write(base, name,"lls.npy",  (T*)h.lls  , h.ni, 4, 4, 4, 2 ) ;
         

    // /tmp/blyth/opticks/LayrTest/scan__R12860__gpu_thr_float 
}



template<typename T>
std::string junoPMTOpticalModelTest<T>::desc() const 
{
    std::stringstream ss ; 
    ss << "junoPMTOpticalModelTest::desc"
       << " mgr " << ( mgr ? "Y" : "N" )
       << " lv " << ( lv ? "Y" : "N" )
       << " pmtOpticalModel " << ( pmtOpticalModel ? "Y" : "N" )
       ;
    std::string s = ss.str(); 
    return s ; 
}

int main(int argc, char** argv)
{
    junoPMTOpticalModelTest<double> t ; 
    std::cout << t.desc() << std::endl ; 

    t.calculateCoefficients(440.) ; 

    

    return 0 ; 
}

