run1_5_notes
==============


::

    Begin of Event --> 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffbd92e0e2 in DepositEnergyAnaMgr::UserSteppingAction (this=0x6864780, step=0x67848e0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc:168
    168	        trkid = ancestors.back();
    (gdb) bt
    #0  0x00007fffbd92e0e2 in DepositEnergyAnaMgr::UserSteppingAction (this=0x6864780, step=0x67848e0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc:168
    #1  0x00007fffd486a062 in MgrOfAnaElem::UserSteppingAction (this=0xa15b350, step=0x67848e0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:74
    #2  0x00007fffbddc6963 in LSExpSteppingAction::UserSteppingAction (this=0xa499ed0, fStep=0x67848e0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpSteppingAction.cc:56
    #3  0x00007fffc6725235 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007fffc673070f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x652c400, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x66d5120) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #8  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


    (gdb) f 0
    #0  0x00007fffbd92e0e2 in DepositEnergyAnaMgr::UserSteppingAction (this=0x6864780, step=0x67848e0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc:168
    168	        trkid = ancestors.back();
    (gdb) list
    163	    //     std::cout << " -> " << trkid << std::endl;
    164	    // }
    165	    int trkid = -1;
    166	    if (ancestors.size()) {
    167	        // only get the last ancestor
    168	        trkid = ancestors.back();
    169	    } else if (prmtrkid) {
    170	        // if no ancestors, maybe a primary track
    171	        trkid = prmtrkid;
    172	    } else {
    (gdb) p ancestors
    $1 = std::vector of length -70918499991552, capacity -70918499991552 = {Cannot access memory at address 0x1020000000000
    (gdb) 



export junoSD_PMT_v2__ProcessHits_EPH_NOLABEL=1
-----------------------------------------------------




