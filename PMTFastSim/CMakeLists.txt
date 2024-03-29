cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTFastSim)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

#[=[
To avoid duplication of sources many of the
geometry providing .cc and .hh are "stolen" from junosw repo, 
so remember to pull from there to update::

    $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include
    $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src

#]=]


if(PMTFastSim_VERBOSE)
message(STATUS "j/PMTFastSim/CMakeLists.txt find_packge... " )
endif()


set(COMPONENTS system program_options filesystem regex )
find_package(Boost REQUIRED COMPONENTS ${COMPONENTS} )
find_package(G4    REQUIRED MODULE)
find_package(CLHEP REQUIRED CONFIG) #   Geant4 should have found it already  : but get HepRotation link errors without 
find_package(SysRap REQUIRED)


set(SOURCES)
set(HEADERS)

#include_directories($ENV{HOME}/j/PMTSim)
include_directories($ENV{HOME}/j/Layr)

#include_directories($ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc)
#  $ENV{JUNOTOP}/junosw/Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc

list(APPEND SOURCES
    DetectorConstruction.cc
    HamamatsuR12860PMTManager.cc
    Hamamatsu_R12860_PMTSolid.cc
    ZSolid.cc
    junoPMTOpticalModel.cc
    junoPMTOpticalModelSimple.cc
    MultiFilmModel.cc
    OpticalSystem.cc
    Layer.cc 
    Matrix.cc
    Material.cc
    MaterialSvc.cc
    PMTFastSim.cc
    J_PMTFASTSIM_LOG.cc
)

list(APPEND HEADERS
    PMTFASTSIM_API_EXPORT.hh
    DetectorConstruction.hh
    HamamatsuR12860PMTManager.hh
    IGeomManager.h
    junoPMTOpticalModel.hh
    MultiFilmModel.h
    OpticalSystem.h
    Layer.h
    Matrix.h
    Material.h
    MaterialSvc.hh
    TComplex.h 
    ../Layr/Layr.h  
    ../Layr/JPMT.h  
    ../Layr/IPMTAccessor.h  
    ../Layr/PMTAccessor.h  
    PMTFastSim.hh
    J_PMTFASTSIM_LOG.hh
)


set(BASE_Geometry $ENV{JUNOTOP}/junosw/Detector/Geometry/Geometry)
list(APPEND HEADERS_Geometry
    ${BASE_Geometry}/PMT.h
    ${BASE_Geometry}/PMTCategory.h
)

set(BASE_PMTSimParamSvc $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc)
list(APPEND HEADERS_PMTSimParamSvc
    ${BASE_PMTSimParamSvc}/PMTSimParamData.h
    ${BASE_PMTSimParamSvc}/_PMTSimParamData.h
    ${BASE_PMTSimParamSvc}/PmtSimData_LPMT.h
    ${BASE_PMTSimParamSvc}/PmtSimData_SPMT.h
)


message(STATUS "CMAKE_INSTALL_PREFIX     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR     : ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")

add_library( ${name}  SHARED ${SOURCES} ${HEADERS} ${HEADERS_Geometry} ${HEADERS_PMTSimParamSvc} )

target_compile_definitions( ${name} PRIVATE OPTICKS_PMTFASTSIM PMTFASTSIM_STANDALONE PMTSIM_STANDALONE )

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
install(FILES ${HEADERS}           DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${HEADERS_Geometry}  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Geometry )
install(FILES ${HEADERS_PMTSimParamSvc}  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/PMTSimParamSvc )


add_subdirectory(tests)
