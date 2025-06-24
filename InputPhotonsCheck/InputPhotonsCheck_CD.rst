InputPhotonsCheck_CD
=======================


::

    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sTarget_RandomSpherical1M_f8/A000 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sTarget_RandomSpherical1M_f8/B000 
     NOT doing ab = SAB(a,b) # do that with : export SAB=1
    [--- abh = SABHit(a,b) ----
    ]--- abh = SABHit(a,b) ----
    [----- repr(abh) 


    SABHit  a_nhit : (  258576 +-  508 )  b_nhit:(   259079 +-  508 )  a/b: (  0.998 +-  0.004 )  b/a: (  1.002 +-  0.004)  [assume uncorr.]


After including CE scale down, SPMT fix
-------------------------------------------

::

    unoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 217961 hitCollectionAlt 217101 hcMuon 0 GPU YE

    SABHit  a_nhit : (  217101 +-  465 )  b_nhit:(   217961 +-  466 )  a/b: (  0.996 +-  0.004 )  b/a: (  1.004 +-  0.004)  [assume uncorr.]

::

    [sseq_index_ab::desc u_size 129074 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1861.5612 ndf 1631.0000 sum/ndf     1.1414 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO AB                                                                                            :  111833 111950 :     0.0612 : Y :       0     27 :   
        TO BT BT BT BT BT BT EC                                                                          :   90826  91776 :     4.9424 : Y :      14      9 :   
        TO BT BT BT BT BT BT SA                                                                          :   87693  87476 :     0.2688 : Y :      11      7 :   
        TO SC AB                                                                                         :   41715  41264 :     2.4512 : Y :      16     25 :   
        TO SC BT BT BT BT BT BT EC                                                                       :   40527  40473 :     0.0360 : Y :       5      1 :   
        TO SC BT BT BT BT BT BT SA                                                                       :   40240  40080 :     0.3187 : Y :      29     14 :   
        TO BT BT SA                                                                                      :   23450  23573 :     0.3217 : Y :      56     21 :   
        TO SC SC BT BT BT BT BT BT SA                                                                    :   15429  15400 :     0.0273 : Y :       3      0 :   






opticksMode 0, not converting geometry
----------------------------------------

::

    junotoptask:DetSimAlg.Calib_GuideTube_Construction_V1_1.getLV  INFO:  getLV at counter 38
    junotoptask:DetSimAlg.Calib_GuideTube_Construction_V1_1.getLV  INFO:  getLV at counter 39
    junotoptask:DetSimAlg.DetSim1Construction.inject  WARN: Failed to get the next volume of guide tube. 
    Total Number of UnknownVolume in CD is 39
    LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 0 WITH_G4CXOPTICKS  proceeding to setup Opticks 
    LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan 
    U::Resolve token [MultiFilmLUTMakerSvc_DIR] does not resolve 
    NP::save failed to U::Resolve path_ $MultiFilmLUTMakerSvc_DIR/multifilm.npy
    [New Thread 0x7fffbd696640 (LWP 2008103)]
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5
    @@@ G4ParticleHPInelastic instantiated for particle neutron data directory variable is G4NEUTRONHPDATA pointing to /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data



::

     445     }
     446     else
     447     {
     448         std::cout
     449             << "LSExpDetectorConstruction::setupOpticks"
     450             << " ekey " << ekey
     451             << " no pmtscan "
     452             << std::endl
     453             ;
     454     }
     455 
     456 
     457     LSExpDetectorConstruction_Opticks::Setup( m_opticksMode, world, m_sd, pps_d, psps_d, pmtscan );
     458 
     459 
     460 


Need to use mode:2 to do the geometry conversion::

    087 G4CXOpticks* G4CXOpticks::SetGeometry_JUNO(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd, NPFold* jpmt, const NP* jlut )
     88 {
     89     LOG(LEVEL) << "[" ;
     90 
     91     // boot SSim adding extra juno PMT info
     92     SSim::CreateOrReuse();   // done previously by G4CXOpticks::G4CXOpticks in opticksMode > 0 or here in opticksMode:0
     93     SSim::AddExtraSubfold("jpmt", jpmt );
     94     SSim::AddMultiFilm(snam::MULTIFILM, jlut);
     95 
     96     SEvt::CreateOrReuse() ;  // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE (which via above assert matches opticksMode)
     97 
     98 
     99     int opticksMode = SEventConfig::IntegrationMode();
    100     if(opticksMode == 2) SetNoGPU() ;
    101 
    102     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
    103 
    104     G4CXOpticks* gx = nullptr ;
    105 
    106     if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
    107     {
    108         gx = SetGeometry(world) ;
    109         SaveGeometry();
    110     }
    111 
    112     LOG(LEVEL) << "]" ;
    113     return gx ;
    114 }




10k is MAX_PARTICLES limit for GenEvtInfoAnaMgr
------------------------------------------------

::

    2315         # == genevt anamgr ==
    2316         if args.anamgr_genevt:
    2317             detsimfactory.property("AnaMgrList").append("GenEvtInfoAnaMgr")


::

    gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbdb498e8 in GenEvtInfoAnaMgr::PostUserTrackingAction (this=0x8e2ab20, aTrack=0xf11b7960) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/GenEvtInfoAnaMgr.cc:232
    #6  0x00007fffcf354efa in MgrOfAnaElem::PostUserTrackingAction (this=0x8dfb770, trk=0xf11b7960) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:67
    #7  0x00007fffbdfc9e59 in LSExpTrackingAction::PostUserTrackingAction (this=0x9138fb0, aTrack=0xf11b7960) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:48
    #8  0x00007fffc663aa70 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc6bc6565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe186b68e in G4SvcRunManager::SimulateEvent (this=0x67d9000, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffcf349d3e in DetSimAlg::execute (this=0x6725b70) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    (gdb) f 5
    #5  0x00007fffbdb498e8 in GenEvtInfoAnaMgr::PostUserTrackingAction (this=0x8e2ab20, aTrack=0xf11b7960) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/GenEvtInfoAnaMgr.cc:232
    232	    assert(current_trkid < MAX_PARTICLES);
    (gdb) p current_trkid
    $1 = 1000000
    (gdb) p MAX_PARTICLES
    $2 = 10000
    (gdb) 




::

    A[blyth@localhost junosw]$ git diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    diff --git a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    index 262b4e0e..d2b50904 100644
    --- a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    +++ b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    @@ -1340,6 +1340,7 @@ class JUNODetSimModule(JUNOModule):
                 self.setup_generator_neutron(args, gt)
             elif args.gentool_mode == "opticks":
                 self.setup_generator_opticks(args, gt)
    +            args.anamgr_genevt = False   ## GenEvtInfoAnaMgr assert current_trkid < MAX_PARTICLES:10k
             elif args.gentool_mode == "genloader":
                 self.setup_generator_genloader(args, gt)
             pass
    A[blyth@localhost junosw]$ 



InteresingProcessAnaMgr SEGV
-------------------------------


::

    idx 8 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[      0.950     -0.221      0.219] dir[      0.950     -0.221      0.219] pol[     -0.224      0.000      0.975]
    idx 9 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[     -0.729      0.656      0.195] dir[     -0.729      0.656      0.195] pol[     -0.258      0.000     -0.966]
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0x69308c8, __p=0x6799b427caf6f61) at /usr/include/c++/11/ext/new_allocator.h:162
    162		{ ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
    (gdb) bt
    #0  0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0x69308c8, __p=0x6799b427caf6f61) at /usr/include/c++/11/ext/new_allocator.h:162
    #1  0x00007fffc7ca2594 in std::allocator_traits<std::allocator<int> >::construct<int, int const&> (__a=..., __p=0x6799b427caf6f61) at /usr/include/c++/11/bits/alloc_traits.h:516
    #2  0x00007fffc7ca182c in std::vector<int, std::allocator<int> >::push_back (this=0x69308c8, __x=@0x7ffffffef474: 1000001) at /usr/include/c++/11/bits/stl_vector.h:1192
    #3  0x00007fffbdf9fa52 in NormalTrackInfo::markTracedAncestors (this=0x69308b0, trkid=1000001) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:59
    #4  0x00007fffbdf9dd05 in InteresingProcessAnaMgr::saveSecondaryInit (this=0x6980890, aTrack=0x106d0d490) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcess
    #5  0x00007fffbdf9b50b in InteresingProcessAnaMgr::PreUserTrackingAction (this=0x6980890, aTrack=0x106d0d490) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:217
    #6  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa15cff0, trk=0x106d0d490) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #7  0x00007fffbe784ebf in LSExpTrackingAction::PreUserTrackingAction (this=0xa34cba0, aTrack=0x106d0d490) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #8  0x00007fffc6730880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x65e13c0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffd485ed3e in DetSimAlg::execute (this=0x667c670) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    (gdb) f 3
    #3  0x00007fffbdf9fa52 in NormalTrackInfo::markTracedAncestors (this=0x69308b0, trkid=1000001) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:59
    59	        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    (gdb) 


::

    059         inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }



    196 void
    197 InteresingProcessAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    198     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    199     // LogDebug << "NormalTrackInfo: " << info << std::endl;
    200 
    201     if (info) {
    202         // select michael electron
    203         if (info->isMichelElectron() && m_legacy_michel_electron) {
    204             saveMichel(aTrack);
    205         }
    206         if (info->isNeutronCapture() && m_legacy_ncapture) {
    207             saveNeutronCapture(aTrack);
    208         }
    209 
    210         if (info->getDecayMode() && m_legacy_decay) {
    211             // if it is the secondaries of g4decay
    212             saveDecayInit(aTrack);
    213         }
    214 
    215 
    216         if (info->isInterestedProcess()) {
    217             saveSecondaryInit(aTrack);
    218         }
    219     }
    220 }





