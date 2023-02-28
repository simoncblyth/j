cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTSim)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

#[=[
To avoid duplication of sources many of the
geometry providing .cc and .hh are "stolen" from junosw repo, 
so remember to pull from there to update::

    $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include
    $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src

#]=]


if(PMTSim_VERBOSE)
message(STATUS "j/PMTSim/CMakeLists.txt find_packge... " )
endif()


set(COMPONENTS system program_options filesystem regex )
find_package(Boost REQUIRED COMPONENTS ${COMPONENTS} )
find_package(G4    REQUIRED MODULE)
find_package(CLHEP REQUIRED CONFIG) #   Geant4 should have found it already  : but get HepRotation link errors without 
find_package(SysRap REQUIRED)

include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/SimUtil)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/MCParamsSvc/MCParamsSvc)  # for IMCParamsSvc.hh
include_directories($ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc)   
include_directories($ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include)


set(BASE_PMTSimParamSvc $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc)

list(APPEND HEADERS_PMTSimParamSvc
    ${BASE_PMTSimParamSvc}/IPMTAccessor.h
    ${BASE_PMTSimParamSvc}/PMTAccessor.h
)




set(SOURCES)
set(HEADERS)

list(APPEND SOURCES

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc 
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Layer.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Material.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc



     # TRY moving to common sources (different options) for junosw/PMTSim and j/PMTSim 

     LowerChimney.cc
     LowerChimneyMaker.cc
     ZSolid.cc          ## TODO: this is in offline too, consolidate
     MaterialSvc.cc

     PMTSim.cc
     J_PMTSIM_LOG.cc 

     DetectorConstruction.cc
)




list(APPEND HEADERS
     PMTSIM_API_EXPORT.hh

     ZSolid.h  
     MaterialSvc.hh

     PMTSim.hh
     J_PMTSIM_LOG.hh

     DetectorConstruction.hh

     ../Layr/Layr.h 
     ../Layr/JPMT.h 

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
)

message(STATUS "CMAKE_INSTALL_PREFIX     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR     : ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")

add_library( ${name}  SHARED ${SOURCES} ${HEADERS} )

target_compile_definitions( ${name} PRIVATE OPTICKS_PMTSIM PMTSIM_STANDALONE )

target_include_directories(${name}
     PUBLIC
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${name} PUBLIC 
   Opticks::G4 
   CLHEP::CLHEP 
   Opticks::SysRap
   Boost::system
   Boost::program_options
   Boost::filesystem
)

bcm_deploy(TARGETS ${name} NAMESPACE Opticks:: SKIP_HEADER_INSTALL)

install(FILES ${HEADERS}                 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${HEADERS_PMTSimParamSvc}  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PMTSimParamSvc )



add_subdirectory(tests)
