cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTFastSimTest)
project(${name} VERSION 0.1.0)

set(TEST_SOURCES

    junoPMTOpticalModelTest.cc
    DetectorConstructionTest.cc

    PMTAccessorTest.cc
)

message( STATUS "PMTFastSim_FOUND:${PMTFastSim_FOUND}" )

include_directories(
    $ENV{JUNOTOP}/junosw/Detector/Geometry
    $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc
)

foreach(SRC ${TEST_SOURCES})
    get_filename_component(TGT ${SRC} NAME_WE)
    add_executable(${TGT} ${SRC})

    add_test(${name}.${TGT} ${TGT})

    target_compile_definitions( ${TGT} PRIVATE PMTSIM_STANDALONE PMTFASTSIM_STANDALONE WITH_PMTFASTSIM )
    target_compile_definitions( ${TGT} PRIVATE WITH_NP )    ## for _PMTSimParamData 

    target_link_libraries(${TGT} Opticks::PMTFastSim)

    install(TARGETS ${TGT} DESTINATION lib)
endforeach()

