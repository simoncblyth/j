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
#include "HamamatsuR12860PMTManager.hh"
#include "junoPMTOpticalModel.hh"

struct junoPMTOpticalModelTest
{
    G4String                   label ; 
    HamamatsuR12860PMTManager* mgr ; 
    G4LogicalVolume*           lv ; 
    junoPMTOpticalModel*       pmtOpticalModel ; 

    junoPMTOpticalModelTest(); 
    std::string desc() const ; 
}; 

junoPMTOpticalModelTest::junoPMTOpticalModelTest()
    :
    label("junoPMTOpticalModelTest"),
    mgr(new HamamatsuR12860PMTManager(label)),
    lv(mgr->getLV()),  // calls the init
    pmtOpticalModel(mgr->pmtOpticalModel)
{
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
    return 0 ; 
}

