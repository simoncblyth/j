small_diffs_between_array_counts_and_hitCollection_counts
============================================================


Overview
----------

* getting same or more in the hitCollection so its not merge reduction
* 0/1/2/3 more in hitCollection that in the array ? hows that possible ? 
* looked at the Merger anyhow, dont see any problem.

* dumping hitCollection entries before and after adding the Opticks hits 
  shows are starting with a small number 0->3 hits in the hitCollection

  * should not be any ordinary hits  



TODO : see where the few start hits come from
------------------------------------------------


::

    LOG=1 BP=junoSD_PMT_v2::ProcessHits ~/j/okjob.sh   

    LOG=1 BP=junoSD_PMT_v2::SaveNormHit ~/j/okjob.sh 


::

    2023-12-15 20:01:52.553 INFO  [147860] [junoSD_PMT_v2_Opticks::Initialize@104]  opticksMode 1 eventID 0 LEVEL 4:INFO
    Begin of Event --> 0

    Thread 1 "python" hit Breakpoint 1, junoSD_PMT_v2::ProcessHits (this=0x8c198e0, step=0x5dbdbe0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:388
    388	    G4bool is_hit = ProcessHits_(step, nullptr) ; 
    (gdb) bt
    #0  junoSD_PMT_v2::ProcessHits (this=0x8c198e0, step=0x5dbdbe0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:388
    #1  0x00007fffd0d552dc in G4SteppingManager::Stepping() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #2  0x00007fffd0d60aaf in G4TrackingManager::ProcessOneTrack(G4Track*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffd0d9bd0d in G4EventManager::DoProcessing(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #4  0x00007fffc7e1d68e in G4SvcRunManager::SimulateEvent (this=0x58cba40, i_event=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #5  0x00007fffc7601d3e in DetSimAlg::execute (this=0x5e06740) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #6  0x00007fffd4e05511 in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd4e09c1d in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



::

    Thread 1 "python" hit Breakpoint 4, junoSD_PMT_v2::SaveNormHit (this=0x8c198e0, pmtID=489, local_pos=..., global_pos=..., hittime=251.55561584166097, track=0xc7804740, edep=2.9476464653232259e-06) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:940
    940	      m_jpmt_dbg->SaveNormHit_count += 1 ; 
    (gdb) p global_pos
    $1 = {dx = -6873.9171829242223, dy = 176.27110541857093, dz = 18075.375036135811}
    (gdb) p wavelength
    $2 = 6.953355803940186e-310
    (gdb) p pmtID
    $3 = 489
    (gdb) 





Check entries before and after + dump the few hits from before
------------------------------------------------------------------

::

    131 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
    132 {
    133     G4CXOpticks* gx = G4CXOpticks::Get() ;
    134     gx->SensitiveDetector_EndOfEvent(eventID) ;
    135 
    136     if(m_merger == nullptr) m_merger = m_jpmt->getMergerOpticks();
    137 
    138     LOG(LEVEL) << "[ " << m_jpmt->desc() ;
    139 
    140     LOG(LEVEL) << std::endl << m_jpmt->descHitCollection() ;
    141     
    142     
    143     if(m_gpu_simulation)
    144     {   
    145         EndOfEvent_Simulate(eventID) ;
    146     }
    147     
    148     
    149     LOG(LEVEL) << "] " << m_jpmt->desc() ;
    150 }
    151 



Issue
---------

::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    2023-12-15 17:32:41.789 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 0
    Begin of Event --> 0
    2023-12-15 17:32:41.796 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 0
    2023-12-15 17:32:41.896 INFO  [132718] [QSim::simulate@376]  eventID 0 dt    0.011824 ph       9096 ph/M          0 ht       1786 ht/M          0 end NO 
    2023-12-15 17:32:41.926 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A000 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 1787 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    2023-12-15 17:32:41.947 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 1
    Begin of Event --> 1
    2023-12-15 17:32:41.950 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 1
    2023-12-15 17:32:42.016 INFO  [132718] [QSim::simulate@376]  eventID 1 dt    0.009394 ph       8915 ph/M          0 ht       1779 ht/M          0 end NO 
    2023-12-15 17:32:42.044 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A001 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 1 hitCollection 1780 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (2) 
    junoSD_PMT_v2::Initialize eventID 2
    2023-12-15 17:32:42.605 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 2
    Begin of Event --> 2
    2023-12-15 17:32:42.612 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 2
    2023-12-15 17:32:42.687 INFO  [132718] [QSim::simulate@376]  eventID 2 dt    0.009655 ph       9163 ph/M          0 ht       1800 ht/M          0 end NO 
    2023-12-15 17:32:42.714 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A002 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 1 hitCollection 1801 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (3) 
    junoSD_PMT_v2::Initialize eventID 3
    2023-12-15 17:32:42.767 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 3
    Begin of Event --> 3
    2023-12-15 17:32:42.771 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 3
    2023-12-15 17:32:42.839 INFO  [132718] [QSim::simulate@376]  eventID 3 dt    0.009354 ph       9038 ph/M          0 ht       1778 ht/M          0 end NO 
    2023-12-15 17:32:42.866 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A003 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 1 hitCollection 1778 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (4) 
    junoSD_PMT_v2::Initialize eventID 4
    2023-12-15 17:32:43.012 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 4
    Begin of Event --> 4
    2023-12-15 17:32:43.020 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 4
    2023-12-15 17:32:43.090 INFO  [132718] [QSim::simulate@376]  eventID 4 dt    0.009717 ph       8942 ph/M          0 ht       1734 ht/M          0 end NO 
    2023-12-15 17:32:43.116 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A004 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 1 hitCollection 1736 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (5) 
    junoSD_PMT_v2::Initialize eventID 5
    2023-12-15 17:32:43.249 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 5
    Begin of Event --> 5
    2023-12-15 17:32:43.256 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 5
    2023-12-15 17:32:43.329 INFO  [132718] [QSim::simulate@376]  eventID 5 dt    0.010099 ph       9353 ph/M          0 ht       1814 ht/M          0 end NO 
    2023-12-15 17:32:43.355 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A005 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 1 hitCollection 1815 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (6) 
    junoSD_PMT_v2::Initialize eventID 6
    2023-12-15 17:32:43.414 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 6
    Begin of Event --> 6
    2023-12-15 17:32:43.423 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 6
    2023-12-15 17:32:43.494 INFO  [132718] [QSim::simulate@376]  eventID 6 dt    0.010118 ph       9162 ph/M          0 ht       1751 ht/M          0 end NO 
    2023-12-15 17:32:43.520 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A006 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 1 hitCollection 1751 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (7) 
    junoSD_PMT_v2::Initialize eventID 7
    2023-12-15 17:32:43.605 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 7
    Begin of Event --> 7
    2023-12-15 17:32:43.617 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 7
    2023-12-15 17:32:43.686 INFO  [132718] [QSim::simulate@376]  eventID 7 dt    0.009702 ph       9158 ph/M          0 ht       1740 ht/M          0 end NO 
    2023-12-15 17:32:43.712 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A007 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 1 hitCollection 1742 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (8) 
    junoSD_PMT_v2::Initialize eventID 8
    2023-12-15 17:32:43.814 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 8
    Begin of Event --> 8
    2023-12-15 17:32:43.822 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 8
    2023-12-15 17:32:43.893 INFO  [132718] [QSim::simulate@376]  eventID 8 dt    0.010177 ph       9017 ph/M          0 ht       1756 ht/M          0 end NO 
    2023-12-15 17:32:43.920 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A008 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 1 hitCollection 1758 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (9) 
    junoSD_PMT_v2::Initialize eventID 9
    2023-12-15 17:32:43.989 ERROR [132718] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 9
    Begin of Event --> 9
    2023-12-15 17:32:44.002 ERROR [132718] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 9
    2023-12-15 17:32:44.070 INFO  [132718] [QSim::simulate@376]  eventID 9 dt    0.009464 ph       9274 ph/M          0 ht       1812 ht/M          0 end NO 
    2023-12-15 17:32:44.097 INFO  [132718] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A009 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 1 hitCollection 1815 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully



