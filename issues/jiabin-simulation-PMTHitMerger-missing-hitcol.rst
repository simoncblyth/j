jiabin-simulation-PMTHitMerger-missing-hitcol-bt.rst
=======================================================


Overview
----------

Using "--pmt-hit-type 2" results in millions of lines::

    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.


 


Issue
------

::

    cd ~/j/issues/jiabin-simulation-PMTHitMerger-missing-hitcol

    BP=PMTHitMerger::init,PMTHitMerger::saveHit ./jiabin-simulation.sh

    ...

    ## Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0

    Thread 1 "python" hit Breakpoint 1.2, PMTHitMerger::init (this=0xaa6fcc0, hitcol=0xd19cf278) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:145
    warning: 145	/builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc: No such file or directory
    (gdb) bt
    #0  PMTHitMerger::init (this=0xaa6fcc0, hitcol=0xd19cf278) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:145
    #1  0x00007fffbd5f9396 in junoSD_PMT_v2::Initialize (this=0x9dd8340, HCE=0xd1a084c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:223
    #2  0x00007fffc4d71cfa in G4SDStructure::Initialize(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #3  0x00007fffc4d6f6bc in G4SDManager::PrepareNewEvent() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #4  0x00007fffc672e289 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #5  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65c6a00, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #6  0x00007fffd485ed3e in DetSimAlg::execute (this=0x66be8d0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #7  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
   (gdb) 

::

    (gdb) f 0
    #0  PMTHitMerger::init (this=0xaa6fcc0, hitcol=0xd19cf278) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:145
    145	in /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc
    (gdb) 


    142 bool
    143 PMTHitMerger::init(junoHit_PMT_muon_Collection* hitcol) {
    144   
    145   assert(m_time_window > 0);
    146   
    147   // during event begin, retrieve the hit collection
    148   hitCollection_muon = hitcol;
    149   
    150   // clear all vectors but saving pmts number
    151 
    152   std::map<int, std::vector<junoHit_PMT_muon*> >::iterator pmt = m_PMThit_muon.begin();
    153   for ( ; pmt != m_PMThit_muon.end(); ++pmt) pmt->second.clear();
    154 
    155   return true;
    156 }


    0215     m_pmtid2idincol.clear();
     216     assert( m_pmtid2idincol.size() == 0 );
     217 
     218     if (m_pmthitmerger) {
     219         if (m_hit_type == 1) {
     220             m_pmthitmerger->init(hitCollection);
     221         } else if (m_hit_type == 2) {
     222             // TODO
     223             m_pmthitmerger->init(hitCollection_muon);
     224         } else {
     225             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     226         }
     227     }
     228     // make sure the PMT merger exists.
     229     assert(m_pmthitmerger);


Looks like problem of trying to use "m_hit_type == 2"



::

    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.
    ^CWARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted.

    Thread 1 "python" received signal SIGINT, Interrupt.
    0x00007fffbe6a6bbe in Tran<double>::ApplyToFloat (tr=..., p0=0x7ffffffedeb0, w=1, count=1, stride=16, offset=0, normalize=false) at /home/blyth/opticks/sysrap/stran.h:636
    636	        for(unsigned j=0 ; j < 3 ; j++) aa[j] = T(a_[j]) ;  // potentially widen 
    (gdb) b PMTHitMerger::saveHit
    Breakpoint 1 at 0x7fffbd589e9e: PMTHitMerger::saveHit. (2 locations)
    (gdb) b PMTHitMerger::init
    Breakpoint 2 at 0x7fffbd58a126: PMTHitMerger::init. (2 locations)
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1.1, PMTHitMerger::saveHit (this=0xaa6f390, hit_photon=0xdc65f5d0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    warning: 81	/builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc: No such file or directory
    (gdb) bt
    #0  PMTHitMerger::saveHit (this=0xaa6f390, hit_photon=0xdc65f5d0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    #1  0x00007fffbd60c3fb in junoSD_PMT_v2_Opticks::collectHit (this=0xaa86c00, hit=0x7ffffffedfb0, hit_extra=0x0, merged_count=@0x7ffffffee088: 0, savehit_count=@0x7ffffffee084: 491125)
        at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:300
    #2  0x00007fffbd60b8d8 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xaa86c00, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:219
    #3  0x00007fffbd60b4ca in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xaa86c00, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:175
    #4  0x00007fffbd5fbf1f in junoSD_PMT_v2::EndOfEvent (this=0x6595890, HCE=0xc2628450) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1129
    #5  0x00007fffc4d720fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #6  0x00007fffc672ea80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #7  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x6625f80, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #8  0x00007fffd485ed3e in DetSimAlg::execute (this=0x661fb50) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #9  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


