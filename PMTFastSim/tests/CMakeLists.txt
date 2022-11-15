cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTFastSimTest)
project(${name} VERSION 0.1.0)

set(TEST_SOURCES

    junoPMTOpticalModelTest.cc
    DetectorConstructionTest.cc

)

foreach(SRC ${TEST_SOURCES})
    get_filename_component(TGT ${SRC} NAME_WE)
    add_executable(${TGT} ${SRC})

    add_test(${name}.${TGT} ${TGT})

    target_link_libraries(${TGT} Opticks::PMTFastSim)
    target_compile_definitions( ${TGT} PRIVATE PMTSIM_STANDALONE PMTFASTSIM_STANDALONE )

    install(TARGETS ${TGT} DESTINATION lib)
endforeach()

