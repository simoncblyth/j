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



#include <iostream>
#include <streambuf>

struct cout_redirect {
    cout_redirect( std::streambuf * new_buffer ) 
        : old( std::cout.rdbuf( new_buffer ) ) 
    { } 

    ~cout_redirect( ) { 
        std::cout.rdbuf( old );
    }   

private:
    std::streambuf * old;
};


struct cerr_redirect {
    cerr_redirect( std::streambuf * new_buffer ) 
        : old( std::cerr.rdbuf( new_buffer ) ) 
    { } 

    ~cerr_redirect( ) { 
        std::cerr.rdbuf( old );
    }   

private:
    std::streambuf * old;
};


inline std::string OutputMessage(const char* msg, const std::string& out, const std::string& err, bool verbose )  // static
{
    std::stringstream ss ;

    ss << std::left << std::setw(30) << msg << std::right
       << " yielded chars : "
       << " cout " << std::setw(6) << out.size()
       << " cerr " << std::setw(6) << err.size()
       << " : set VERBOSE to see them "
       << std::endl
       ;

    if(verbose)
    {
        ss << "cout[" << std::endl << out << "]" << std::endl  ;
        ss << "cerr[" << std::endl << err << "]" << std::endl  ;
    }
    std::string s = ss.str();
    return s ;
}







struct junoPMTOpticalModelTest
{
    bool                       verbose ; 
    G4String                   label ; 
    DetectorConstruction*      dc ; 
    HamamatsuR12860PMTManager* mgr ; 
    G4LogicalVolume*           lv ; 
    junoPMTOpticalModel*       pmtOpticalModel ; 

    junoPMTOpticalModelTest(); 
    void init(); 
    std::string desc() const ; 

    void calculateCoefficients(); 

}; 

junoPMTOpticalModelTest::junoPMTOpticalModelTest()
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

void junoPMTOpticalModelTest::init()
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


void junoPMTOpticalModelTest::calculateCoefficients()
{
    double energy = 4.*eV ; 
    double minus_cos_theta = -1. ; 
    pmtOpticalModel->CalculateCoefficients(energy, minus_cos_theta); 
}



std::string junoPMTOpticalModelTest::desc() const 
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
    junoPMTOpticalModelTest t ; 
    std::cout << t.desc() << std::endl ; 

    t.calculateCoefficients() ; 

    return 0 ; 
}

