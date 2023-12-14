get_ready_for_junosw_plus_opticks_release
===========================================

Overview
----------

* create branch in web interface : blyth-opticks-integration-for-release



checkout branch
---------------

::

    jo
    git fetch 

    N[blyth@localhost junosw]$ git checkout blyth-opticks-integration-for-release
    M	Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    branch 'blyth-opticks-integration-for-release' set up to track 'origin/blyth-opticks-integration-for-release'.
    Switched to a new branch 'blyth-opticks-integration-for-release'
    N[blyth@localhost junosw]$ 



N : update
-----------



::

    N[blyth@localhost legacy]$ jo
    /home/blyth/junotop/junosw
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   cmake/legacy/JUNODependencies.cmake

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ 



    N[blyth@localhost junosw]$ git diff cmake/legacy/JUNODependencies.cmake
    diff --git a/cmake/legacy/JUNODependencies.cmake b/cmake/legacy/JUNODependencies.cmake
    index badbe94..26f191b 100644
    --- a/cmake/legacy/JUNODependencies.cmake
    +++ b/cmake/legacy/JUNODependencies.cmake
    @@ -167,7 +167,7 @@ add_definitions(-DSNIPER_VERSION_2)
     ## Opticks
     if(DEFINED ENV{OPTICKS_PREFIX})
        set(Opticks_VERBOSE YES)
    -   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{JUNOTOP}/opticks/cmake/Modules")
    +   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{OPTICKS_PREFIX}/cmake/Modules")
        find_package(Opticks MODULE)
        message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
     endif()
    @@ -192,4 +192,4 @@ if(NUWRO_LIBRARIES)
     else()
         set(NuWro_Found FALSE)
     endif()
    -link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    \ No newline at end of file
    +link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    N[blyth@localhost junosw]$ 

::

    N[blyth@localhost junosw]$ git diff Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    diff --git a/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc b/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    index 10e0d68..af9016f 100644
    --- a/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    +++ b/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    @@ -113,6 +113,9 @@ so perhaps can remove the GtOpticksTool that duplicates this.
     #ifdef WITH_G4CXOPTICKS
     void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
     {
    +    G4CXOpticks* gx = G4CXOpticks::Get() ; 
    +    gx->SensitiveDetector_Initialize(eventID) ; 
    +
         SEvt::TimerStart() ; 
     
         std::cerr
    @@ -149,15 +152,15 @@ when GPU simulation is done.
     
     void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
     {
    +    G4CXOpticks* gx = G4CXOpticks::Get() ; 
    +    gx->SensitiveDetector_EndOfEvent(eventID) ; 
    +
    +
         if(m_pmthitmerger_opticks == nullptr) m_pmthitmerger_opticks = m_jpmt->getMergerOpticks(); 
         bool gpu_sim = gpu_simulation(); 
     
         LOG(LEVEL) << "[ " << m_jpmt->desc() ; 
     
    -    // int index = 1+eventID ; 
    -    // SEvt::SetIndex(index);   
    -    // IS THIS NEEDED ? WHY ? Presumably as want to save some debug stuff before the simulate that sets the index later
    -    // HOW TO AVOID THAT ? USE add_array SO DONT NEED TO CHANGE THE index ? 
     
         EndOfEvent_Debug(eventID) ; 
     
    N[blyth@localhost junosw]$ 





::

    Updating 2f92190..3f6a299
    error: Your local changes to the following files would be overwritten by merge:
        Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        cmake/legacy/JUNODependencies.cmake
    Please commit your changes or stash them before you merge.
    Aborting



Tao removed below from Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc::

    #include "GenTools/GtOpticksTool.h"

Moved to::

    Simulation/GenTools/src/GtOpticksTool.h





Interface updates
--------------------

::

    [ 92%] Building CXX object Examples/ElecAnalysis/CMakeFiles/ElecAnalysis.dir/src/TestBuffDataAlg.cc.o
    [ 92%] Built target SPMTCalibAlg
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc: In member function 'void junoSD_PMT_v2_Opticks::TerminateEvent()':
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:312:15: error: 'Clear' is not a member of 'SEvt'
      312 |         SEvt::Clear(); // TODO: dont like dealing with both SEvt like this, also Opticks house-keeping should be done elsewhere
          |               ^~~~~
    [ 92%] Building CXX object Examples/RawAnalysis/CMakeFiles/RawAnalysis.dir/src/RawEvtBuilder.cc.o
    [ 92%] Built target WpPMTCalibAlg
    In file included from /data/blyth/junotop/junosw/Simulation/ElecSimV3/ElecSimAlg/src/ElecSimSvc.h:24,



