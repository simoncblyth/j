cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTSim)
project(${name} VERSION 0.1.0)
include(OpticksBuildOptions)

find_package(G4    REQUIRED MODULE)
find_package(CLHEP REQUIRED CONFIG) #   Geant4 should have found it already  : but get HepRotation link errors without 
find_package(SysRap REQUIRED)

set(SOURCES)
set(HEADERS)

list(APPEND SOURCES
     PMTSim.cc
     Hamamatsu_R12860_PMTSolid.cc
     HamamatsuR12860PMTManager.cc 
     OldZSolid.cc
     ZCanvas.cc
     ZSolid.cc
)

list(APPEND HEADERS
     PMTSim.hh
     PMTSIM_API_EXPORT.hh
     OldZSolid.hh
     ZCanvas.hh
     ZSolid.hh
)

message(STATUS "CMAKE_INSTALL_PREFIX     : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_INSTALL_INCLUDEDIR : ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "CMAKE_INSTALL_LIBDIR     : ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")

add_library( ${name}  SHARED ${SOURCES} ${HEADERS} )

target_compile_definitions( ${name} PUBLIC OPTICKS_PMTSIM STANDALONE )

target_include_directories(${name}
     PUBLIC
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${name} PUBLIC Opticks::G4 CLHEP::CLHEP Opticks::SysRap)

bcm_deploy(TARGETS ${name} NAMESPACE Opticks:: SKIP_HEADER_INSTALL)

install(FILES ${HEADERS}  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


add_subdirectory(tests)
