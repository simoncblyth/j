blyth-88-testing-within-monolith
===================================

Next
------

* :doc:`blyth-88-setup-customgeant4-mini-external-package-to-avoid-circular-dependency-issue`

How to do this ?
------------------

Perhaps via Opticks enabled ana-manager that brings U4Recorder/sysrap style 
functionality into the monolith ? 

Essentially need to hookup the U4Recorder event/track/step listeners 
into the monolith ones ?


Review the old G4OpticksAnaMgr
--------------------------------

Start by reviewing what the old "--opticks-anamgr" does::

   jcv JUNODetSimModule




    0495         # == opticks ==
     496         grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=0,
     497                                 help=mh("Control Opticks GPU Optical simulation"))
     498         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     499                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays.")     )
     500 

    1989         # == opticks
    1990         if args.opticks_mode > 0 and args.opticks_anamgr:
    1991             print("appending G4OpticksAnaMgr to AnaMgrList")
    1992             detsimfactory.property("AnaMgrList").append("G4OpticksAnaMgr")
    1993             g4ok_anamgr = sim_conf.tool("G4OpticksAnaMgr")
    1994             g4ok_anamgr.setLogLevel(4)
    1995         pass

jcv G4OpticksAnaMgr::

     28 #ifdef WITH_G4OPTICKS
     29 void G4OpticksAnaMgr::BeginOfRunAction(const G4Run* run) {  BeginOfRun() ;  m_recorder->BeginOfRunAction(run);       }
     30 void G4OpticksAnaMgr::EndOfRunAction(const G4Run* run) {           m_recorder->EndOfRunAction(run);         }
     31 void G4OpticksAnaMgr::BeginOfEventAction(const G4Event* evt) {     m_recorder->BeginOfEventAction(evt);     }
     32 void G4OpticksAnaMgr::EndOfEventAction(const G4Event* evt) {       m_recorder->EndOfEventAction(evt);       }
     33 void G4OpticksAnaMgr::PreUserTrackingAction(const G4Track* trk) {  m_recorder->PreUserTrackingAction(trk);  }
     34 void G4OpticksAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction(trk); }
     35 void G4OpticksAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
     36 #else


* HMM maybe new G4CXOpticksAnaMgr to replace the G4OpticksAnaMgr

      
Looks like Essentially need to update the opticks-anamgr to the U4 way of working 
-----------------------------------------------------------------------------------------

YES: but also need the initialization/finalization done by U4SimulateTest.cc

* probably need to encapsulate some of what U4SimulateTest.cc does 
  into headers so can do that from the monolith 

* so can start standalone by cleaning up the main 

* DONE : tidied up U4SimulateTest.cc/U4Recorder.cc using U4App.h to prepare for use of U4Recorder from an AnaMgr 

* cannot use U4SimulateTest struct within monolith, need to work with the monolith controlled G4RunManager
* similarly cannot use U4RecorderTest.h:U4RecorderTest (not U4App.h)

Plugging into the anamgr dont have clear initialize/finalize hooks other than BeginOfRun/EndOfRun ?
Or perhaps should use BeginOfEvent/EndOfEvent as SEvt needs saving at that cadence. 

::

    123 U4RecorderTest::U4RecorderTest(G4RunManager* runMgr)
    124     :
    125     fPrimaryMode(PrimaryMode()),
    126     fRecorder(new U4Recorder),
    127     fGun(fPrimaryMode == 'G' ? InitGun() : nullptr),
    128     fPV(nullptr)
    129 {



WIP: Create U4RecorderAnaMgr using U4Recorder+SEvt, starting from G4OpticksAnaMgr 
--------------------------------------------------------------------------------------

::

    epsilon:junosw blyth$ jcv G4OpticksAnaMgr
    2 files to edit
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc
    epsilon:junosw blyth$ cd 

Trivial pass thru from U4RecorderAnaMgr to U4Recorder::

    epsilon:junosw blyth$ jcv U4RecorderAnaMgr
    2 files to edit
    ./Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    epsilon:junosw blyth$ 


HMM:

* Where to hold the SEvt ? U4Recorder::setEvt ? 
* Does U4Recorder need to know AnaMgr involved ? 


Looks like hookup only at python level::

    epsilon:junosw blyth$ jgr G4OpticksAnaMgr | grep -v G4OpticksAnaMgr.hh | grep -v G4OpticksAnaMgr.cc 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    * this mode of operation is typically used together with the G4OpticksAnaMgr allowing the Geant4 propagation
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:     G4OpticksAnaMgr and G4OpticksRecorder to save the entire Geant4 optical propagations in OpticksEvent format 
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                                help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            print("appending G4OpticksAnaMgr to AnaMgrList")    
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("AnaMgrList").append("G4OpticksAnaMgr")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            g4ok_anamgr = sim_conf.tool("G4OpticksAnaMgr")
    epsilon:junosw blyth$ 


::

    1989         # == opticks
    1990         if args.opticks_mode > 0 and args.opticks_anamgr:
    1991             print("appending U4RecorderAnaMgr to AnaMgrList")   
    1992             detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    1993             g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    1994             g4ok_anamgr.setLogLevel(4)
    1995         pass


jxv:ntds3 

    data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc: In member function 'virtual void U4RecorderAnaMgr::UserSteppingAction(const G4Step*)':
    /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35:104: error: no matching function for call to 'U4Recorder::UserSteppingAction(const G4Step*&)'
     void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
                                                                                                            ^
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:5:
    /data/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Recorder.hh:68:31: note: candidate: 'template<class T> void U4Recorder::UserSteppingAction(const G4Step*)'
         template<typename T> void UserSteppingAction(const G4Step*);
                                   ^~~~~~~~~~~~~~~~~~
    /data/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Recorder.hh:68:31: note:   template argument deduction/substitution failed:
    /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35:104: note:   couldn't deduce template parameter 'T'
     void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }


::

    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python: symbol lookup error: /data/blyth/junotop/junosw/InstallArea/lib64/libAnalysisCode.so: undefined symbol: _ZN10U4Recorder18UserSteppingActionI25CustomG4OpBoundaryProcessEEvPK6G4Step

    N[blyth@localhost j]$ c++filt _ZN10U4Recorder18UserSteppingActionI25CustomG4OpBoundaryProcessEEvPK6G4Step
    void U4Recorder::UserSteppingAction<CustomG4OpBoundaryProcess>(G4Step const*)
    N[blyth@localhost j]$ 



* Try hiding the template complications at lower level.
* HMM: that means Opticks U4Recorder now depends on CustomG4OpBoundaryProcess complicating dependencies between monolith and opticks ?
* this is kinda difficult to avoid as it really should be coming from Geant4 which is used by both of course



HMM ntds2 is doing geometry translation ?


::

    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 2.86528 NumTracks 5
    U4Recorder::PostUserTrackingAction@111: 
    U4Recorder::PreUserTrackingAction@110: 
    U4Recorder::PreUserTrackingAction_Optical@177:  track 0x7fff2f142000 status:fAlive resume_fSuspend NO
    U4Recorder::PreUserTrackingAction_Optical@184: [
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:907: void SEvt::hostside_running_resize(): Assertion `is_self_provider' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) 

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf892b8c in SEvt::hostside_running_resize (this=0x18d8c4740) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:907
    #5  0x00007fffcf89322c in SEvt::beginPhoton (this=0x18d8c4740, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1027
    #6  0x00007fffd29bf4de in U4Recorder::PreUserTrackingAction_Optical (this=0xb38600, track=0x7fff2f142000) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:245
    #7  0x00007fffd29beb4c in U4Recorder::PreUserTrackingAction (this=0xb38600, track=0x7fff2f142000) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:110
    #8  0x00007fffceda69d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0x931170, trk=0x7fff2f142000)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35
    #9  0x00007fffcd11cd39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffcd32bb00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x7fff2f142000)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #10 0x00007fffcf0a87ad in LSExpTrackingAction::PreUserTrackingAction (this=0x5969380, aTrack=0x7fff2f142000)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #11 0x00007fffdba8e5f0 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #12 0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x00007fffcf30945d in G4SvcRunManager::SimulateEvent (this=0x94a5c0, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x00007fffcd10fe9b in DetSimAlg::execute (this=0xb26390) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x00007fffed6c984a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fffed6ce855 in TaskWatchDog::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007fffed6c9574 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007fffedb807a3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vec




Looks like setup confusion between on device and host running::

    SOpticksResource::ResolveUserPrefix@54:  envkey OPTICKS_GEOCACHE_PREFIX prefix /home/blyth/.opticks rc 0
    Missing separate debuginfo for /lib64/libcuda.so.1
    Try: yum --enablerepo='*debug*' install /usr/lib/debug/.build-id/3e/1e7dd516361182d263c7713bd47eaa498bf0cd.debug
    [New Thread 0x7fff9860a700 (LWP 408032)]
    [New Thread 0x7fff97e09700 (LWP 408033)]
    [New Thread 0x7fff97608700 (LWP 408034)]
    SEvt::setCompProvider@483: SEvt::descProvider provider: 0x18e4a88f0 that address is: another object
    LSExpDetectorConstruction_Opticks::Setup@41: ] WITH_G4CXOPTICKS 
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5
    @@@ G4ParticleHPInelastic instantiated for particle neutron data directory variable is G4NEUTRO


Added opticksMode:2 handling to the Setup:: 

     15 void LSExpDetectorConstruction_Opticks::Setup(
     16           int opticksMode,
     17           const G4VPhysicalVolume* world,
     18           const G4VSensitiveDetector* sd,
     19           PMTParamData* ppd,
     20           PMTSimParamData* psd,
     21           NPFold* pmtscan
     22           )
     23 {
     24     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     25     if( opticksMode == 0 ) return ;
     26 
     27     G4CXOpticks::SetGeometry(world) ; 
     28 
     29     _PMTParamData    _ppd(*ppd) ; 
     30     _PMTSimParamData _psd(*psd) ; 
     31 
     32     NPFold* j = new NPFold ; 
     33     j->add_subfold( "PMTParamData",    _ppd.serialize() );
     34     j->add_subfold( "PMTSimParamData", _psd.serialize() );
     35     if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     36 
     37     SSim::AddSubfold("juno", j );
     38 
     39     G4CXOpticks::SaveGeometry(); 
     40 
     41     LOG(info) << "] WITH_G4CXOPTICKS " ; 
     42 }


Inside G4CXOpticks::setGeometry geometry is converted and SEvt gets instanciated, 
for Geant4 running with Opticks instrumentation dont need that. 



Hmm using Instrumented when needs to use Custom::

    U4Recorder::UserSteppingAction_Optical@639: ]
    U4Recorder::UserSteppingAction_Optical@509: [ pv pTarget
    U4Recorder::UserSteppingAction_Optical@550:  flag 0 . is_boundary_flag 0
    U4Recorder::UserSteppingAction_Optical@587:  ERR flag zero : post U4StepPoint::Desc
     proc 2 procName Transportation procNameRaw Transportation
     status 1 statusName fGeomBoundary
     bstat 0 bstatName Undefined
     flag 0 flagName .
    python: /data/blyth/junotop/opticks/u4/U4Recorder.cc:588: void U4Recorder::UserSteppingAction_Optical(const G4Step*) [with T = InstrumentedG4OpBoundaryProcess]: Assertion `flag > 0' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd29c6a61 in U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess> (this=0xb25d30, step=0xadd610)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:588
    #5  0x00007fffd29becc4 in U4Recorder::UserSteppingAction (this=0xb25d30, step=0xadd610) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:128
    #6  0x00007fffced7fa32 in U4RecorderAnaMgr::UserSteppingAction (this=0x9313f0, step=0xadd610)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35
    #7  0x00007fffcd0f6009 in MgrOfAnaElem::UserSteppingAction (this=0x7fffcd304b00 <MgrOfAnaElem::instance()::s_mgr>, step=0xadd610)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:74
    #8  0x00007fffcf0a109d in LSExpSteppingAction::UserSteppingAction (this=0x5969470, fStep=0xadd610)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpSteppingAction.cc:56
    #9  0x00007fffdba82e1d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #11 0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #12 0x00007fffcf30945d in G4SvcRunManager::SimulateEvent (this=0x94a850, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #13 0x00007fffcd0e8e9b in DetSimAlg::execute (this=0xb263e0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSim



::

    114 
    115 #if defined(WITH_PMTSIM) || defined(WITH_CUSTOM_BOUNDARY)
    116 #include "G4OpBoundaryProcess.hh"
    117 #include "CustomG4OpBoundaryProcess.hh"
    118 #else
    119 #include "InstrumentedG4OpBoundaryProcess.hh"
    120 #endif
    121 
    122 void U4Recorder::UserSteppingAction(const G4Step* step)
    123 {
    124     if(!U4Track::IsOptical(step->GetTrack())) return ;
    125 #if defined(WITH_PMTSIM) || defined(WITH_CUSTOM_BOUNDARY)
    126      UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(step);
    127 #else
    128      UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(step);
    129 #endif
    130 }
    131 


This means the Opticks build needs to depend on part of junosw even when not using WITH_PMTSIM 
So should split off CustomG4OpBoundaryProcess from the PMTSIM into an optional mini package.
BUT : that has version shear risk. 

Maybe try again to get templated to work ?


* first take a look at exactly what the Custom dependency of U4Recorder 
  is and see if can separate that out into a header only impl, or relocate the functionality./ 

* reason for this is that CustomG4OpBoundaryProcess is exceedingly similar to G4OpBoundaryProcess
  so its kinda annoying to have a complicate things 

* another alternative is to define a protocol base to avoid the template


U4OpBoundaryProcess.h::

     28 #if defined(WITH_PMTSIM) || defined(WITH_CUSTOM_BOUNDARY)
     29 #include "CustomG4OpBoundaryProcess.hh"
     30 #else
     31 #include "InstrumentedG4OpBoundaryProcess.hh"
     32 #endif
 

u4/CMakeLists.txt::

    135 if(PMTSim_FOUND)
    136     target_link_libraries( ${name} PUBLIC Opticks::PMTSim )
    137     target_compile_definitions( ${name} PUBLIC WITH_PMTSIM PMTSIM_STANDALONE WITH_NP )
    138 endif()


HMM: how to distinguish between three types of Opticks build:

1. standalone test using WITH_PMTSIM : easy as PMTSim_FOUND gets set by CMake
2. building Opticks for use with junosw (need to set WITH_CUSTOM_BOUNDARY) : MAYBE WITH_JUNOSW to be explicit 
3. buidling Opticks without PMTSIM and without junosw 


Suppose can have some Opticks CMake detection that looks for junosw JUNOTOP and sets WITH_JUNOSW when found 



Could make a protocol base followed by both::

    InstrumentedG4OpBoundaryProcess
    CustomG4OpBoundaryProcess 

    IBoundaryProcess

::

    289 inline
    290 G4OpBoundaryProcessStatus G4OpBoundaryProcess::GetStatus() const
    291 {
    292    return theStatus;
    293 }


* decided :doc:`blyth-88-setup-customgeant4-mini-external-package-to-avoid-circular-dependency-issue`


HMM: Where to call SEvt::save ? 
----------------------------------
 
