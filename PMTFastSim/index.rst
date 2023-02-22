PMTFastSim index
===================


Review Changes : To decide what/how to incorporate changes into blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
--------------------------------------------------------------------------------------------------------------------------------------------

Three pots of code:

1. main
2. j/PMTFastSim
3. j/PMTSim 

Review Contents of j/PMTFastSim and comment on differences with main and j/PMTSim


Plumbing
------------

PMTFASTSIM_API_EXPORT.hh

J_PMTFASTSIM_LOG.cc
J_PMTFASTSIM_LOG.hh

CMakeLists.txt
   Links with Opticks externals including Geant4, CLHEP and boost as well as the low level Opticks SysRap package  

   Uses several non-standard source inclusions:
 
   1. brings in Layr.h JPMT.h IPMTAccessor.h PMTAccessor.h from ../Layr  
   2. brings in PMT.h PMTCategory.h from $ENV{JUNOTOP}/junosw/Detector/Geometry/Geometry
   3. brings in PMTSimParamData.h _PMTSimParamData.h from $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc


Utilities
-------------
F4.hh
    G4FastTrack utilities drawing on Opticks U4, eg F4::PhotonId(fastTrack) 



Standalone Materials Environment : NOT NEEDED WITHIN MONOLITH
----------------------------------------------------------------

DetectorConstruction.cc 
DetectorConstruction.hh
   Minimal extraction from the junosw DetectorConstruction that brings in code defined 
   JUNO materials with a non-standard icc::

     43 void DetectorConstruction::DefineMaterials()
     44 {
     45    #include "LSExpDetectorConstructionMaterial.icc"
     46 }

IMCParamsSvc.hh
    protocol base of MaterialSvc, used from LSExpDetectorConstructionMaterial.icc for 
    reading JUNO material properties from files

LSExpDetectorConstructionMaterial.icc

utils.hh
    nasty boost based property from file reading

MaterialSvc.cc
MaterialSvc.hh
    reading properties from file using utils.hh
     

IGeomManager.h
   standalone declProp using envvar, getLV/getSolid/getPV protocol base 



Code Needing to be updated in monolith
-----------------------------------------

HamamatsuR12860PMTManager.cc 
HamamatsuR12860PMTManager.hh
    Made standalone with PMTFASTSIM_STANDALONE macro blocks 

    Enhancements to IGeomManager have reduced code differences between standalone/monolith running 
    (eg mock declProp for config) : will need to bring those into monolith. 

    Macro PMTFASTSIM_STANDALONE no longer appropriate will need to change to PMTSIM_STANDALONE.


Hamamatsu_R12860_PMTSolid.cc
Hamamatsu_R12860_PMTSolid.hh



Standalone adaption of Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc "MultiFilmModel"
--------------------------------------------------------------------------------------------

TComplex.h
    "typedef std::complex<double> TComplex" and a few funcs in _TComplex namespace

Matrix.cc
Matrix.h
    "jdiff Matrix" shows private to public and added dtor impl

Layer.cc
Layer.h
   "jdiff Layer" shows only diff to main is flipping private to public 

Material.cc
Material.h
   "jdiff Material" shows only diff to main is flipping private to public 

OpticalSystem.cc
OpticalSystem.h
    switch TComplex from ROOT to a simple typedef to std::complex

MultiFilmModel.h
MultiFilmModel.cc
    private to public, made TComplex temporaries  into members

    * use different TComplex impl to avoid depending on ROOT for almost no functionality  



PMTFastSim.cc
PMTFastSim.hh
PMTFastSim.rst
RefBase.h
TString.h
ZCanvas.h
ZSolid.cc
ZSolid.h
ellipse_intersect_circle.cc
ellipse_intersect_circle.hh
gather.sh
index.rst

junoPMTOpticalModel.cc
junoPMTOpticalModel.hh
junoPMTOpticalModel.rst

junoPMTOpticalModelSimple.cc
junoPMTOpticalModelSimple.hh
junoPMTOpticalModelSimple.rst

junoPMTOpticalModelSimple_in_customized_G4OpBoundaryProcess.rst
junoPMTOpticalModel_vs_CustomBoundaryART_propagation_time_discrepancy.rst


PMTFastSim/tests
-------------------

CMakeLists.txt

DetectorConstructionTest.cc
DetectorConstructionTest.sh


TComplexTest.cc
LayerTest.cc
MaterialTest.cc
MatrixTest.cc
MultiFilmModelTest.cc
OpticalSystemTest.cc
   tests of the standalone adapted MultiFilmModel components 

buildtest.sh
    gcc minimal builder for the MultiFilmModel component tests


PMTAccessorTest.cc
PMTAccessorTest.py
PMTAccessorTest.sh
    standalone comparison of PMTSimParamData and JPMT implementations of the IPMTAccessor protocol


junoPMTOpticalModelTest.cc
junoPMTOpticalModelTest.sh



