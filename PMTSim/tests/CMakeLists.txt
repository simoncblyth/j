cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTSimTest)
project(${name} VERSION 0.1.0)

set(TEST_SOURCES
    PMTSimTest.cc
    X4SolidTreeTest.cc
    G4UnionSolidOffsetsTest.cc
    HamamatsuR12860PMTManagerTest.cc
    MaterialSvcTest.cc
    DetectorConstructionTest.cc
    PMTSolidTest.cc
    GetSolidTest.cc
    GetValuesTest.cc
    GetSolid_Test.cc
    GetPVTest.cc
    GetLVTest.cc
)

foreach(SRC ${TEST_SOURCES})
    get_filename_component(TGT ${SRC} NAME_WE)
    add_executable(${TGT} ${SRC})

    add_test(${name}.${TGT} ${TGT})

    target_link_libraries(${TGT} Opticks::PMTSim_standalone)
    target_compile_definitions( ${TGT} PRIVATE PMTSIM_STANDALONE )

    install(TARGETS ${TGT} DESTINATION lib)
endforeach()

