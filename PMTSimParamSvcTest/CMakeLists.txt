cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(name PMTSimParamSvcTest)
project(${name} VERSION 0.1.0)

include("$ENV{JUNOTOP}/junosw/InstallArea/lib64/cmake/junosw/JUNODependencies.cmake")
include("$ENV{JUNOTOP}/junosw/InstallArea/lib64/cmake/junosw/junoswTargets.cmake")

include_directories(
   $ENV{JUNOTOP}/junosw/Simulation/SimSvc/PMTSimParamSvc
   $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/MCParamsSvc
)

add_executable(${name} ${name}.cc)

target_link_libraries(${name} junosw::PMTSimParamSvc junosw::IPMTSimParamSvc)

install(TARGETS ${name} DESTINATION bin)


