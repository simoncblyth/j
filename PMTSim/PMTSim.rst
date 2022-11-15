PMTSim
=========

Objective
-----------

Provide Opticks and standalone tests with access to some aspects of JUNOSW
such as PMT geometry via use of the PMTSim library. 

Contents
----------

CMakeLists.txt::

    list(APPEND SOURCES

         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc

         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc 
         $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc

         # TRY moving to common sources (different options) for junosw/PMTSim and j/PMTSim 

         LowerChimney.cc
         LowerChimneyMaker.cc
         ZSolid.cc          ## TODO: this is in offline too, consolidate
         MaterialSvc.cc

         PMTSim.cc
         P4Volume.cc
         DetectorConstruction.cc
    )


    list(APPEND HEADERS
         PMTSIM_API_EXPORT.hh

         ZSolid.h  
         SCanvas.hh
         MaterialSvc.hh

         PMTSim.hh
         P4Volume.hh
         DetectorConstruction.hh

         ../Layr/Layr.h 
         ../Layr/JPMT.h 
    )



Dependencies Excluding Geant4 headers 
----------------------------------------

DetectorConstruction.hh
    only forward decl IMCParamsSvc

DetectorConstruction.cc

    * RefBase.h 
    * IMCParamsSvc.h 
    * DetectorConstruction.hh
    * MaterialSvc.hh





