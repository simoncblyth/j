PMTFastSim index
===================


Review Changes : To decide what/how to incorporate changes into blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
--------------------------------------------------------------------------------------------------------------------------------------------

Review Contents of j/PMTFastSim and comment on differences with main and j/PMTSim

Three pots of code:

1. main
2. j/PMTSim : selects as much as possible from main   
3. j/PMTFastSim : free experimentation unconstrained by being within the monolith 

   * HMM: can just regard PMTFastSim as transient expt
   * if some future major change is needed can create a new directory for it 

HMM: pots 2 and 3 are kinda the same thing just at different stages of development 

* some of 3 which will get incorporated into 


PhysiSim switch
------------------

::

     60     declProp("UsePMTOpticalModel", m_doFastSim=false); // just the fast simulation
     61     // conflating PMTOpticalModel with m_doFastSim 


HMM: what about when not using MultiFilm POM ? Still need to use Custom Boundary ? 

Maybe add "MultiFilmPMT" switch to IPMTAccessor


PhysiSim DEPENDS
--------------------

PhysiSim/CMakeLists.txt already depends on the below::

     28     DEPENDS
     29         DetSimAlg
     30         MCParamsSvc
     31         EGet
     32         $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>
     33 

::

    epsilon:junosw blyth$ jcv PMTSimParamData
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    epsilon:junosw blyth$ 

        
::

    epsilon:Simulation blyth$ pwd
    /Users/blyth/junotop/junosw/Simulation
    epsilon:Simulation blyth$ l
    total 8
    0 drwxr-xr-x  37 blyth  staff  1184 Feb 21 16:48 ..
    0 drwxr-xr-x   7 blyth  staff   224 Feb  2 10:49 SimSvc
    0 drwxr-xr-x  23 blyth  staff   736 Oct 17 14:25 DetSimV2
    0 drwxr-xr-x   8 blyth  staff   256 Sep 27 14:00 GenTools
    0 drwxr-xr-x  10 blyth  staff   320 Sep 22 10:11 .
    0 drwxr-xr-x   4 blyth  staff   128 Sep 22 10:11 SNMonitorSim
    0 drwxr-xr-x   6 blyth  staff   192 Sep 22 10:11 GenDecay
    0 drwxr-xr-x   5 blyth  staff   160 Sep 22 10:11 EvtMixing
    0 drwxr-xr-x   4 blyth  staff   128 Sep 22 10:11 ElecSimV3
    8 -rw-r--r--   1 blyth  staff   277 Sep 22 10:11 CMakeLists.txt
    epsilon:Simulation blyth$ 


Simulation/CMakeLists.txt::


     07 add_subdirectory (GenTools)
      8 add_subdirectory (GenDecay)
      9 
     10 add_subdirectory (DetSimV2)
     11 add_subdirectory (EvtMixing)
     12 add_subdirectory (ElecSimV3)
     13 
     14 add_subdirectory (SimSvc)
     15 
     16 add_subdirectory (SNMonitorSim)


HMM SimSvc after DetSimV2 might cause problem ? Maybe OK as junosw is one big CMake pkg ?





    epsilon:DetSimV2 blyth$ l
    total 8
    0 drwxr-xr-x   6 blyth  staff  192 Feb 22 19:06 PhysiSim
    0 drwxr-xr-x   8 blyth  staff  256 Feb  3 15:40 DetSimOptions
    0 drwxr-xr-x   7 blyth  staff  224 Feb  2 15:23 MCParamsSvc
    0 drwxr-xr-x   5 blyth  staff  160 Jan 12 14:25 AnalysisCode
    0 drwxr-xr-x   6 blyth  staff  192 Nov 17 12:06 SimUtil
    0 drwxr-xr-x   6 blyth  staff  192 Oct 17 14:29 PMTSim
    0 drwxr-xr-x  23 blyth  staff  736 Oct 17 14:25 .
    8 -rw-r--r--   1 blyth  staff  591 Sep 28 14:29 CMakeLists.txt
    0 drwxr-xr-x  10 blyth  staff  320 Sep 22 10:11 ..
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 VoxelMethod
    0 drwxr-xr-x   6 blyth  staff  192 Sep 22 10:11 TopTracker
    0 drwxr-xr-x  19 blyth  staff  608 Sep 22 10:11 OpticalProperty
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 OPSimulator
    0 drwxr-xr-x   7 blyth  staff  224 Sep 22 10:11 MCGlobalTimeSvc
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 G4Svc
    0 drwxr-xr-x   6 blyth  staff  192 Sep 22 10:11 G4DAEChroma
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 DetSimMTUtil
    0 drwxr-xr-x   7 blyth  staff  224 Sep 22 10:11 DetSimMT
    0 drwxr-xr-x   6 blyth  staff  192 Sep 22 10:11 DetSimAlg
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 DAE
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 Chimney
    0 drwxr-xr-x   5 blyth  staff  160 Sep 22 10:11 CentralDetector
    0 drwxr-xr-x   6 blyth  staff  192 Sep 22 10:11 CalibUnit
    epsilon:DetSimV2 blyth$ 






What to do about the macros ? Change PMTFASTSIM to PMTSIM ?
-------------------------------------------------------------

1. It makes little sense to use j/PMTSim and j/PMTFastSim simultaneously anyhow.

So need to distinguish some other way (eg the the one that CMake finds) : maybe need some script
to delete an install ?   

* decided to simply change macros from PMTFASTSIM to PMTSIM as code gets incorporated into main 
  and leave them as it

* so can do a PMTSim standalone side test of new functionality



::

    epsilon:opticks blyth$ opticks-fl PMTFASTSIM 

    ./extg4/CMakeLists.txt
    ./extg4/tests/X4IntersectVolumeTest.cc

    ./GeoChain/CMakeLists.txt
    ./GeoChain/tests/GeoChainVolumeTest.cc

    ./u4/U4Physics.cc
    ./u4/CMakeLists.txt
    ./u4/tests/U4SimulateTest.cc
    ./u4/tests/U4PMTAccessorTest.cc
    ./u4/tests/U4PMTFastSimTest.cc
    ./u4/InstrumentedG4OpBoundaryProcess.hh
    ./u4/InstrumentedG4OpBoundaryProcess.cc
    ./u4/U4VolumeMaker.cc




    epsilon:opticks blyth$ opticks-fl PMTSIM 

    ./extg4/CMakeLists.txt
    ./extg4/X4SolidTree.hh
    ./extg4/tests/CMakeLists.txt
    ./extg4/tests/X4IntersectVolumeTest.cc
    ./extg4/tests/X4_Get.hh
    ./extg4/X4VolumeMaker.cc


    ./GeoChain/CMakeLists.txt
    ./GeoChain/tests/GeoChainVolumeTest.cc
    ./GeoChain/tests/GeoChainSolidTest.cc

    ./g4ok/tests/CMakeLists.txt

    ./qudarap/tests/CMakeLists.txt

    ./u4/CMakeLists.txt
    ./u4/U4VolumeMaker.cc








Plumbing : That does not need to go anywhere
----------------------------------------------

PMTFASTSIM_API_EXPORT.hh

J_PMTFASTSIM_LOG.cc
J_PMTFASTSIM_LOG.hh

CMakeLists.txt
   Links with Opticks externals including Geant4, CLHEP and boost as well as the low level Opticks SysRap package  

   Uses several non-standard source inclusions:
 
   1. brings in Layr.h JPMT.h IPMTAccessor.h PMTAccessor.h from ../Layr  
   2. brings in PMT.h PMTCategory.h from $ENV{JUNOTOP}/junosw/Detector/Geometry/Geometry
   3. brings in PMTSimParamData.h _PMTSimParamData.h from $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc


PMTFastSim.cc
PMTFastSim.hh
PMTFastSim.rst
    Umbrella Coordinator of standalone geometry access


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

RefBase.h
    Sniper plumbing used with MaterialSvc from DetectorConstruction.cc LSExpDetectorConstructionMaterial.icc, 
    copied here to avoid depending on Sniper

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



PMT Geometry : Changes Needing incorporation into monolith
------------------------------------------------------------

HamamatsuR12860PMTManager.hh
    Not much changed, a few extra members for debug. Added m_natural_geometry renamed m_simple_csg to m_simple.

HamamatsuR12860PMTManager.cc 
    Made standalone with PMTFASTSIM_STANDALONE macro blocks 

    * changes for simpler geometry when m_natural_geometry


Enhancements to IGeomManager have reduced code differences between standalone/monolith running 
(eg mock declProp for config) : will need to bring those into monolith. 

Macro PMTFASTSIM_STANDALONE no longer appropriate will need to change to PMTSIM_STANDALONE.




Standalone FastSim Experiments : NONE OF THIS NEEDS TO BE INCORPORATED
-------------------------------------------------------------------------

junoPMTOpticalModel.cc
junoPMTOpticalModel.hh
    * G4VFastSimulationModel impl : significant changes to use make standalone and use Layr.h 
    * Opticks debug instrumentation 
    * BUT: the entire FastSim approach is dropped in the intended fix 

junoPMTOpticalModel.rst
    Notes on FastSim investigations
    
junoPMTOpticalModelSimple.cc
junoPMTOpticalModelSimple.hh
junoPMTOpticalModelSimple.rst
    Aborted attempt to simplify the FastSim, that concluded that FastSim should be dropped

junoPMTOpticalModelSimple_in_customized_G4OpBoundaryProcess.rst
    initial design thoughts for the fix 

junoPMTOpticalModel_vs_CustomBoundaryART_propagation_time_discrepancy.rst
    notes on random alignment check 


PMT Geometry : Minimal changes wrt main : NO INCORPORATION NEEDED
-------------------------------------------------------------------

Hamamatsu_R12860_PMTSolid.cc
Hamamatsu_R12860_PMTSolid.hh
    "jdiff Hamamatsu_R12860_PMTSolid|sh" only macro name changes


ZSolid.cc
ZSolid.h
    dependency of HamamatsuR12860PMTManager.cc used for Z-cutdowns 

    * "jdiff ZSolid | sh" 
    * differences with main only macro changed from PMTSIM to PMTFASTSIM

ZCanvas.h
    dependent of ZSolid.cc, no difference with main

ellipse_intersect_circle.cc
ellipse_intersect_circle.hh
    dependent of Hamamatsu_R12860_PMTSolid.cc, no difference with main



Standalone adaption of Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc "MultiFilmModel" : NO INCORPORATION
-----------------------------------------------------------------------------------------------------------------

gather.sh
    grabbing the MultiFilmModel files

TString.h
    standalone mockup of ROOT Form, to avoid depending on ROOT for minimal functionality 

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



PMTFastSim/tests
-------------------

CMakeLists.txt
DetectorConstructionTest.cc
DetectorConstructionTest.sh
   plumbing tests 

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



