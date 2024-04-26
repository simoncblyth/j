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

if(Custom4_FOUND)
   message(STATUS "Custom4 already found" )
else()
  set(Custom4_VERBOSE YES)
  #find_package(Custom4 0.1.3 EXACT REQUIRED)
  find_package(Custom4 CONFIG)
  if(Custom4_FOUND)
  message(STATUS "Custom4_VERSION        : ${Custom4_VERSION} ")
  message(STATUS "Custom4_VERSION_MAJOR  : ${Custom4_VERSION_MAJOR} ")
  message(STATUS "Custom4_VERSION_MINOR  : ${Custom4_VERSION_MINOR} ")
  message(STATUS "Custom4_VERSION_PATCH  : ${Custom4_VERSION_PATCH} ")
  message(STATUS "Custom4_VERSION_TWEAK  : ${Custom4_VERSION_TWEAK} ")
  message(STATUS "Custom4_VERSION_COUNT  : ${Custom4_VERSION_COUNT} ")
  endif()
endif()

#[=[
A successful find of Custom4 sets WITH_CUSTOM4::

    cat ${OPTICKS_PREFIX}_externals/custom4/0.1.6/lib/Custom4-0.1.6/Custom4Config.cmake | grep WITH
    set(Custom4_DEFINITIONS -DWITH_CUSTOM4 )
          INTERFACE_COMPILE_DEFINITIONS "WITH_CUSTOM4"

#]=]



include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/include)

include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/SimUtil)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/MCParamsSvc/MCParamsSvc)  # for IMCParamsSvc.hh
include_directories($ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc)   
include_directories($ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc)
include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include)
include_directories($ENV{JUNOTOP}/junosw/Detector/Geometry)
include_directories($ENV{JUNOTOP}/junosw/Utilities/EGet)
include_directories($ENV{JUNOTOP}/junosw/Detector/Identifier)


# HMM: ABOVE IS PICKING UP FROM SOURCE DIRS NOT FROM INSTALL DIRS junosw/InstallArea/include


set(BASE_PMTSimParamSvc $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc)


set(FORMER_HEADERS_PMTSimParamSvc
    ${BASE_PMTSimParamSvc}/IPMTAccessor.h
)

list(APPEND HEADERS_PMTSimParamSvc
    ${BASE_PMTSimParamSvc}/PMTAccessor.h
    ${BASE_PMTSimParamSvc}/PMTSimParamData.h
    ${BASE_PMTSimParamSvc}/_PMTSimParamData.h
    ${BASE_PMTSimParamSvc}/PmtSimData_LPMT.h
    ${BASE_PMTSimParamSvc}/PmtSimData_SPMT.h
)

set(BASE_Geometry       $ENV{JUNOTOP}/junosw/Detector/Geometry/Geometry)
list(APPEND HEADERS_Geometry
    ${BASE_Geometry}/PMT.h
    ${BASE_Geometry}/PMTCategory.h
)

set(FORMER_HEADERS_SimUtil
    ${BASE_SimUtil}/S4Touchable.h
)


set(BASE_SimUtil      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/SimUtil/SimUtil)
list(APPEND HEADERS_SimUtil
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

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Solid.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/XJanchorConstruction.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/SJCLSanchorConstruction.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/CentralDetector/src/SJReceiverConstruction.cc

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Layer.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.cc
     $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/Material.cc


     # TRY moving to common sources (different options) for junosw/PMTSim and j/PMTSim 

     LowerChimney.cc
     LowerChimneyMaker.cc
     ZSolid.cc          ## TODO: this is in offline too, consolidate
     MaterialSvc.cc

     PMTSim.cc
     J_PMTSIM_LOG.cc 

     DetectorConstruction.cc
)

#[=[
#]=]




set(FORMER_SOURCES
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc
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

     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include/ModelTrigger_Debug.h

)

set(FORMER_HEADERS
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include/CustomART.h
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include/CustomART_Debug.h
     $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PhysiSim/include/MultiLayrStack.h
)



message(STATUS "CMAKE_INSTALL_PREFIX     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR     : ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")

add_library( ${name}  SHARED ${SOURCES} ${HEADERS} )

target_compile_definitions( ${name} PRIVATE 
       OPTICKS_PMTSIM 
       PMTSIM_STANDALONE
       WITH_NP
       POM_DEBUG 
       G4USE_STD11 
       SJFixtureConstruction_ORIGINAL_WITH_COMPILATION_WARNINGS_AND_BUG 
)
# G4USE_STD11 avoids missing symbol G4MTHepRandom::getTheEngine() 


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

if(Custom4_FOUND)
    target_link_libraries(${name} PUBLIC Custom4::Custom4 ) 
endif()




bcm_deploy(TARGETS ${name} NAMESPACE Opticks:: SKIP_HEADER_INSTALL)

install(FILES ${HEADERS}                 DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${HEADERS_PMTSimParamSvc}  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PMTSimParamSvc )
install(FILES ${HEADERS_Geometry}        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Geometry)
install(FILES ${HEADERS_SimUtil}         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SimUtil)



add_subdirectory(tests)
