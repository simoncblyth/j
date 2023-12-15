opticksMode_1_U4Recorder_trying_to_read_from_nowhere
======================================================


Of course in opticksMode 1 need to disable the U4Recorder

* hmm : its kinda user error to enable the recorder 


jcv JUNODetSimModule::

    0504         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     505                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into Optick     sEvent NumPy arrays."))


    2081         if args.opticks_mode > 0 and args.opticks_anamgr:
    2082             print("appending U4RecorderAnaMgr to AnaMgrList")
    2083             detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2084             g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2085             g4ok_anamgr.setLogLevel(4)
    2086         pass

Try to fix at python level::

    2081         if args.opticks_anamgr:
    2082             if args.opticks_mode > 1:
    2083                 print("appending U4RecorderAnaMgr to AnaMgrList in opticks_mode %d " % args.opticks_mode )
    2084                 detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2085                 g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2086                 g4ok_anamgr.setLogLevel(4)
    2087             else:
    2088                 print(" --opticks-anamgr option enabling U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )   
    2089             pass
    2090         pass




::

   opticksMode 0   NOWT
   opticksMode 1   OK only 
   opticksMode 2   G4 only
   opticksMode 3   OK+G4 





::


    533 void G4CXOpticks::SensitiveDetector_Initialize(int eventID)
    534 {
    535     LOG(error) << " eventID " << eventID ;
    536     U4Recorder* recorder = U4Recorder::Get();
    537     if(recorder)
    538     {
    539         recorder->BeginOfEventAction_(eventID);
    540     }
    541 }

    583 void G4CXOpticks::SensitiveDetector_EndOfEvent(int eventID)
    584 {
    585     LOG(error) << " eventID " << eventID ;
    586     U4Recorder* recorder = U4Recorder::Get();
    587     if(recorder)
    588     {
    589         recorder->EndOfEventAction_(eventID);
    590     }
    591 }




::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    2023-12-15 17:09:45.586 ERROR [55876] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 0
    2023-12-15 17:09:45.586 INFO  [55876] [U4Recorder::BeginOfEventAction_@292]  eventID 0
    Begin of Event --> 0
    2023-12-15 17:09:45.630 ERROR [55876] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 0
    2023-12-15 17:09:45.685 INFO  [55876] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/B000 genstep,photon,record,seq,hit,domain,inphoton
    2023-12-15 17:09:45.801 INFO  [55876] [QSim::simulate@376]  eventID 0 dt    0.013626 ph       9096 ph/M          0 ht       1786 ht/M          0 end NO 
    2023-12-15 17:09:45.829 INFO  [55876] [SEvt::save@3945] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A000 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 1787 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    2023-12-15 17:09:46.444 ERROR [55876] [G4CXOpticks::SensitiveDetector_Initialize@535]  eventID 1
    2023-12-15 17:09:46.444 INFO  [55876] [U4Recorder::BeginOfEventAction_@292]  eventID 1
    Begin of Event --> 1
    2023-12-15 17:09:46.475 ERROR [55876] [G4CXOpticks::SensitiveDetector_EndOfEvent@585]  eventID 1
     *** Break *** segmentation violation



    #7  0x00007fb30daf734a in __memcpy_ssse3_back () from /lib64/libc.so.6
    #8  0x00007fb2dedb2bc6 in NP::read2<float> (this=0xc8f9efb0, src=0xd8423050) at /home/blyth/junotop/opticks/sysrap/NP.hh:5997
    #9  0x00007fb2deddc7b1 in SEvt::gatherRecord (this=0x75e0120) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3078
    #10 0x00007fb2deddd2d2 in SEvt::gatherComponent_ (this=0x75e0120, cmp=8) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3296
    #11 0x00007fb2deddd0b8 in SEvt::gatherComponent (this=0x75e0120, cmp=8) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3282
    #12 0x00007fb2dedde5e0 in SEvt::gather_components (this=0x75e0120) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3490
    #13 0x00007fb2deddf1b4 in SEvt::gather (this=0x75e0120) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3576
    #14 0x00007fb2dfc1e40b in U4Recorder::EndOfEventAction_ (this=0x75b7340, eventID_=1) at /home/blyth/junotop/opticks/u4/U4Recorder.cc:322
    #15 0x00007fb2dfd5d364 in G4CXOpticks::SensitiveDetector_EndOfEvent (this=0xbceca20, eventID=1) at /home/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:589
    #16 0x00007fb2de6bb38b in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xa3c9820, eventID=1) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:139
    #17 0x00007fb2de6ae875 in junoSD_PMT_v2::EndOfEvent (this=0xa3c9880, HCE=0xc8faf100) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    #18 0x00007fb2e5bc50da in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so




