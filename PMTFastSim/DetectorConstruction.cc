/**
DetectorConstruction.cc
===================================

RefBase.h
    header only templated reference holder, incorporated into PMTSim (copied from SNiPER)
 
IMCParamsSvc.hh
    header only, pure virtual base, NB uses boost::tuple in the interface

LSExpDetectorConstructionMaterial.icc
    code inclusion into DetectorConstruction::DefineMaterials 


**/

#include <iostream>
#include <iomanip>
#define LogError std::cerr

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"

#include "RefBase.h"
#include "IMCParamsSvc.hh"
#include "DetectorConstruction.hh"
#include "MaterialSvc.hh"


DetectorConstruction::DetectorConstruction()
   :
   m_pmt_optical_model(""),
   m_LS_optical_model(""),
   m_use_pmtsimsvc(true)
{
   std::cout << "[ DetectorConstruction::DetectorConstruction " << std::endl ; 
   DefineMaterials();
   std::cout << "] DetectorConstruction::DetectorConstruction " << std::endl ; 
}

void DetectorConstruction::DefineMaterials()
{
   #include "LSExpDetectorConstructionMaterial.icc"
}

/**
DetectorConstruction::helper_mpt
----------------------------------

This method is used by the code included with LSExpDetectorConstructionMaterial.icc that 
runs within DetectorConstruction::DefineMaterials. Note that the ".icc" is modified 
to use MaterialSvc instead of MCParamsSvc::

     131 #ifdef PMTFASTSIM_STANDALONE
     132     MaterialSvc msv ;
     133     RefBase<MaterialSvc> mcgt(&msv) ;
     134 #else
     135     SniperPtr<IMCParamsSvc> mcgt(*m_scope, "MCParamsSvc");
     136     if (mcgt.invalid()) {
     137           G4cout << "Can't find MCParamsSvc." << G4endl;
     138           assert(0);
     139        }
     140 #endif






**/

bool DetectorConstruction::helper_mpt(G4MaterialPropertiesTable* MPT, const std::string& mname,  IMCParamsSvc* params, const std::string& name , double scale )
{
    IMCParamsSvc::vec_d2d props;
    bool st = params->Get(name, props);
    if (!st) {
        LogError << "can't find material property: " << name << std::endl;
        return false;
    }
    G4MaterialPropertyVector* vec = new G4MaterialPropertyVector(0,0,0);

    int N = props.size();
    if (!N) {
        LogError << "empty material property: " << name << std::endl;
        return false;
    }
    for (int i = 0; i < N; ++i) {
        vec->InsertValues(props[i].get<0>(), props[i].get<1>()*scale);
    }
    MPT->AddProperty(mname.c_str(), vec);


    std::cout 
        << "DetectorConstruction::helper_mpt"
        << " mname " << std::setw(20) << mname
        << " name "  << std::setw(100) << name
        << " props.size " << props.size()
        << std::endl 
        ;

    return true ; 
}


