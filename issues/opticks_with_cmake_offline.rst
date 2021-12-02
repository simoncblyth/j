opticks_with_cmake_offline
=============================

Opticks-Offline CMT setup
-----------------------------

Connection via CMT macros with contents from *opticks-config* script

::

    epsilon:DetSimPolicy blyth$ cat /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimPolicy/cmt/requirements 
    package DetSimPolicy
    # source the geant4 script first

    use Geant4 v* Externals
    use CLHEP v* Externals
    use Xercesc v* Externals

    # The below sets blank macro values unless CMTEXTRATAGS envvar includes opticks, 
    # thus it does no harm when the optional Opticks external is not installed.
    use OpticksG4OK    v* Externals

    # Enable the debug information in the library
    macro_append DetSimPolicy_cppflags " -g "


::

    epsilon:cmt blyth$ cat /Users/blyth/junotop/offline/Simulation/DetSimV2/Opticks/cmt/requirements 
    package Opticks

    macro Opticks_home "`opticks-config --prefix`"

    set OPTICKSDATAROOT "$(Opticks_home)/opticksdata"

    macro Opticks_cppflags " `opticks-config --cflags` "
    macro Opticks_linkopts " `opticks-config --libs` "



::

    epsilon:Simulation blyth$ find . -name requirements -exec grep -H Opticks {} \;
    ./GenTools/cmt/requirements:# thus it does no harm when the optional Opticks external is not installed.
    ./GenTools/cmt/requirements:use OpticksG4OK    v* Externals
    ./DetSimV2/Opticks/cmt/requirements:package Opticks
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_home "`opticks-config --prefix`"
    ./DetSimV2/Opticks/cmt/requirements:set OPTICKSDATAROOT "$(Opticks_home)/opticksdata"
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_cppflags " `opticks-config --cflags` "
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_linkopts " `opticks-config --libs` "
    ./DetSimV2/DetSimPolicy/cmt/requirements:# thus it does no harm when the optional Opticks external is not installed.
    ./DetSimV2/DetSimPolicy/cmt/requirements:use OpticksG4OK    v* Externals
    epsilon:Simulation blyth$ 


    epsilon:Simulation blyth$ find . -type f -exec grep -l WITH_G4OPTICKS {} \;
    ./GenTools/src/GtOpticksTool.cc
    ./GenTools/src/GtOpticksTool.h
    ./DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./DetSimV2/PhysiSim/include/DsG4Scintillation.h
    ./DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    ./DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    ./DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc



How to hookup with new CMake offline ?
------------------------------------------

* TODO: study how ROOT/Geant4 etc.. are hooked up and try something similar : the difference being that Opticks is always optional 


