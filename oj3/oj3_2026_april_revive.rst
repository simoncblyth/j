oj3_2026_april_revive
======================

Thoughts
---------

* did not do opticksMode:3 validation since the "muon" hit and GPU hit merging advances
* also input photon running has not been used since the frame/fr rejig
* Custom4 0.1.8 that is current standard is regarded as WITH_CUSTOM4_OLD
* Custom4 0.1.9 under test is first version that is NOT:WITH_CUSTOM4_OLD

WIP
-----

* use ~/j/oj3/oj3.sh as guide for adding opticksMode:3 test capability to ~/oj


opticksMode:3 overview
-------------------------

0. validation by comparing simulations of the same optical photons
1. uses input photons for simple common inputs to simulations A and B (input gensteps also possible, but not the easiest standard way)
2. uses OK/U4Recorder and OJ/U4RecorderAnaMgr
3. needs seq.npy for chi2 history comparison



~/oj/oj3/oj3.sh shakedown
--------------------------


twiddle option to --anamgr-opticks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (ok) A[blyth@localhost junosw]$ diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/python/Tutorial/JUNODetSimModule.py
    499,501c499,501
    <                                 help=mh("Control Opticks GPU Optical simulation 0:CPU/1:GPU/3:CPU+GPU "))
    <         grp_pmt_op.add_argument("--anamgr-opticks", action="store_true", dest="anamgr_opticks", default=False,
    <                                 help=mh("Enable opticks+junosw/U4RecorderAnaMgr for optional use of opticks/U4Recorder saving Geant4 optical propagations into Opticks SEvt NumPy arrays."))
    ---
    >                                 help=mh("Control Opticks GPU Optical simulation"))
    >         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
    >                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
    2447c2447
    <         if args.anamgr_opticks:
    ---
    >         if args.opticks_anamgr:
    2454c2454
    <                 log.info("IGNORING: --anamgr-opticks option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )    
    ---
    >                 log.info("IGNORING: --opticks-anamgr option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )    
    (ok) A[blyth@localhost junosw]$ 
    (ok) A[blyth@localhost junosw]$ 
    (ok) A[blyth@localhost junosw]$ cp Examples/Tutorial/python/Tutorial/JUNODetSimModule.py InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/python/Tutorial/JUNODetSimModule.py
    (ok) A[blyth@localhost junosw]$ 



GenEvtInfoAnaMgr asserts current_trkid < MAX_PARTICLES  (MAX_PARTICLES = 10000)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


* added OPTICKS_INPUT_PHOTON_SLICE="[0:5000]" to investigate if the 10k input photons are off-by-one or many, eg from reemission 

::

    (gdb) f 5
    #5  0x00007fffbd779a2c in GenEvtInfoAnaMgr::PostUserTrackingAction (this=0xae009e0, aTrack=0xcdb37a40) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/GenEvtInfoAnaMgr.cc:232
    232	    assert(current_trkid < MAX_PARTICLES);
    (gdb) p current_trkid
    $1 = 10000
    (gdb) p MAX_PARTICLES
    $2 = 10000
    (gdb) 


::

    2026-04-07 11:43:46.173 INFO  [1007558] [U4Recorder::UserSteppingAction_Optical@1248] ]
    2026-04-07 11:43:46.173 INFO  [1007558] [U4Recorder::PostUserTrackingAction@414] 
    2026-04-07 11:43:46.173 INFO  [1007558] [U4Recorder::PostUserTrackingAction_Optical_@847] fStopAndKill
    2026-04-07 11:43:46.173 INFO  [1007558] [SEvt::finalPhoton@3364] spho (gs:ix:id:gn   09999 9999[  0,  0,  0,  0])
    2026-04-07 11:43:46.173 INFO  [1007558] [U4Recorder::PostUserTrackingAction_Optical_@883] ]
    python: /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/GenEvtInfoAnaMgr.cc:232: virtual void GenEvtInfoAnaMgr::PostUserTrackingAction(const G4Track*): Assertion `current_trkid < MAX_PARTICLES' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff7437886 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbd779a2c in GenEvtInfoAnaMgr::PostUserTrackingAction (this=0xae009e0, aTrack=0xcdb37a40) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/GenEvtInfoAnaMgr.cc:232
    #6  0x00007fffcfdf0eea in MgrOfAnaElem::PostUserTrackingAction (this=0xa900920, trk=0xcdb37a40) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:67
    #7  0x00007fffbd371749 in LSExpTrackingAction::PostUserTrackingAction (this=0xb167ee0, aTrack=0xcdb37a40) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:48
    #8  0x00007fffc643aa70 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc69d5565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe314468e in G4SvcRunManager::SimulateEvent (this=0x66b3c80, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffcfde5d2e in DetSimAlg::execute (this=0x6906400) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #12 0x00007fffd4b4d4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd4b51bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd4b4d054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffcc8d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #16 0x00007fffd465a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffd465a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffd465f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007fffd4658182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x6049ed0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #21 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #22 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #23 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff774b170, func=0x7ffff77345d0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #24 PyEval_EvalCode (co=co@entry=0x50aba0, globals=globals@entry=0x7ffff774b170, locals=locals@entry=0x7ffff774b170) at Python/ceval.c:1148
    #25 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff774b170, globals=0x7ffff774b170, co=0x50aba0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #26 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7717740, globals=globals@entry=0x7ffff774b170, locals=locals@entry=0x7ffff774b170, flags=flags@entry=0x7ffffffee898, arena=arena@entry=0x7ffff7e58d60) at Python/pythonrun.c:1762
    #27 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee898, closeit=<optimized out>, locals=0x7ffff774b170, globals=0x7ffff774b170, start=257, filename=0x7ffff7717740, fp=0x5405d0) at Python/pythonrun.c:1657
    #28 _PyRun_SimpleFileObject (fp=fp@entry=0x5405d0, filename=filename@entry=0x7ffff7717740, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee898) at Python/pythonrun.c:440
    #29 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x5405d0, filename=filename@entry=0x7ffff7717740, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee898) at Python/pythonrun.c:79
    #30 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7717740, program_name=0x7ffff7734510) at Modules/main.c:360
    #31 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #32 pymain_run_python (exitcode=0x7ffffffee894) at Modules/main.c:605
    #33 Py_RunMain () at Modules/main.c:684
    #34 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffee9a0) at Modules/main.c:714
    #35 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #36 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #37 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #38 0x0000000000401075 in _start ()
    (gdb) 



::

    222 void
    223 GenEvtInfoAnaMgr::PostUserTrackingAction(const G4Track* aTrack) {
    224     // only select the primary track
    225     if (aTrack->GetParentID() != 0) {
    226         return;
    227     }
    228     G4int current_trkid = aTrack->GetTrackID();
    229 
    230     // make sure the trkid is valid.
    231     assert(0 < current_trkid);
    232     assert(current_trkid < MAX_PARTICLES);
    233     if (current_trkid <= 0 or current_trkid >= MAX_PARTICLES) {
    234         return;
    235     }
    236 



OPTICKS_INPUT_PHOTON_SLICE="[0:5000]" AVOIDS THE ABOVE ASSERT, GET TO ANOTHER ASSERT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    2026-04-07 14:28:53.457 INFO  [1025256] [QSim::simulate@583] 
    SEvt__MINTIME
     (TAIL - HEAD)/M   0.039553 (head to tail of QSim::simulate method) 
     (LEND - LBEG)/M   0.039312 (multilaunch loop begin to end) 
     (PCAT - LEND)/M   0.000026 (topfold concat and clear subfold) 
     (TAIL - BRES)/M   0.000006 (QSim::reset which saves hits) 
     tot_idt/M         0.001754 (sum of kernel execution int64_t stamp differences in microseconds)
     tot_dt            0.001710 int(tot_dt*M)         1710 (sum of kernel execution double chrono stamp differences in seconds, and scaled to ms) 
     tot_gdt/M         0.013525 (sum of SEvt::gather int64_t stamp differences in microseconds)

        2026-04-07 14:28:53.457 FATAL [1025256] [junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits@360]  sev YES _hit.sstr - expected_shape NO  SEventConfig::ModeLite 0 SEventConfig::MergeWindow 0 merge_flag NO  opticks_mode_merge NO 
        python: /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:369: void junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits(int): Assertion `expected_shape' failed.

        Thread 1 "python" received signal SIGABRT, Aborted.
        0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
        (gdb) bt
        #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
        #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
        #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
        #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
        #4  0x00007ffff7437886 in __assert_fail () from /lib64/libc.so.6
        #5  0x00007fffbcf7f8ec in junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits (this=0xaff5af0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:369
        #6  0x00007fffbcf7f26b in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xaff5af0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:268
        #7  0x00007fffbcf7ef3a in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xaff5af0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:213
        #8  0x00007fffbcf6eae0 in junoSD_PMT_v2::EndOfEvent (this=0xa122ff0, HCE=0xccf894d0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1162
        #9  0x00007fffc63410fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
        #10 0x00007fffc69d5a80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
        #11 0x00007fffe314468e in G4SvcRunManager::SimulateEvent (this=0x6686260, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
        #12 0x00007fffcfde5d2e in DetSimAlg::execute (this=0x66d1210) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
        #13 0x00007fffd4b4d4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
        #14 0x00007fffd4b51bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so


Are lacking GPU side _hit array, causing expected_shape assert::

    335 void junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits(int eventID )
    336 {
    337     SProf::Add("junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD");
    338     bool merge_flag = m_merger->getMergeFlag();
    339     bool opticks_mode_merge = 1 == SEventConfig::ModeMerge() ;
    340     size_t num_hit = SEvt::GetNumHit_EGPU() ;
    341 
    342     LOG(LEVEL)
    343         << "[ eventID " << eventID
    344         << " num_hit " << num_hit
    345         << " m_hit_type " << m_hit_type
    346         << " merge_flag " << ( merge_flag ? "YES" : "NO " )
    347         << " opticks_mode_merge " << ( opticks_mode_merge  ? "YES" : "NO " )
    348         << " SEventConfig::ModeLite " << SEventConfig::ModeLite()
    349         ;
    350 
    351     assert( m_hit_type == 1 );
    352     assert( m_merger );
    353     assert( SEventConfig::ModeLite() == 0 );
    354 
    355     const SEvt* sev = SEvt::Get_EGPU();
    356     const NP* _hit = sev ? sev->getHit() : nullptr ;
    357     sphoton* hit = _hit ? (sphoton*)_hit->bytes() : nullptr ;
    358 
    359     bool expected_shape = _hit && _hit->has_shape(num_hit, 4, 4) ;
    360     LOG_IF(fatal, !expected_shape)
    361         << " sev " << ( sev ? "YES" : "NO " )
    362         << " _hit.sstr " << ( _hit ? _hit->sstr() : "-" )
    363         << " expected_shape " << ( expected_shape ? "YES" : "NO " )
    364         << " SEventConfig::ModeLite " << SEventConfig::ModeLite()
    365         << " SEventConfig::MergeWindow " << SEventConfig::MergeWindow()
    366         << " merge_flag " << ( merge_flag ? "YES" : "NO " )
    367         << " opticks_mode_merge " << ( opticks_mode_merge  ? "YES" : "NO " )
    368         ;
    369     assert( expected_shape );



Comment the expected_shape assert
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost junosw]$ git diff Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    diff --git a/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc b/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    index 2e4f1679..46290528 100644
    --- a/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    +++ b/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    @@ -7,8 +7,7 @@
     #include "junoSD_PMT_v2.hh"
     #include "PMTSim/junoSD_PMT_v2_Opticks.hh"
     
    -#include "G4Event.hh"
    -#include "G4RunManager.hh"
    +//#include "G4Event.hh"
     #include "G4SystemOfUnits.hh"
     
     using CLHEP::twopi ;
    @@ -367,7 +366,7 @@ void junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits(int eventID )
             << " merge_flag " << ( merge_flag ? "YES" : "NO " )
             << " opticks_mode_merge " << ( opticks_mode_merge  ? "YES" : "NO " )
             ;
    -    assert( expected_shape );
    +    // assert( expected_shape ); // HMM:asserting when lack _hit is not useful for debugging cause
     
         if( opticks_mode_merge )
         {
    A[blyth@localhost junosw]$ 




Skipping the hit expected_shape assert gets thru to the cleanup SIGABRT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    [2026-04-07 14:55:55,364] p1549760 {/home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/bin/tut_detsim.py:63} INFO - OJ: NOT doing TUT_DETSIM_HARD_EXIT

    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
    #4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
    #5  0x00007ffff7497c70 in _int_free () from /lib64/libc.so.6
    #6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
    #7  0x00007fffc59a0c67 in G4ProcessVector::~G4ProcessVector() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #8  0x00007fffc59a0c89 in G4ProcessVector::~G4ProcessVector() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #9  0x00007fffc599016c in G4ProcessManager::~G4ProcessManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #10 0x00007fffc6a99923 in G4VUserPhysicsList::RemoveProcessManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #11 0x00007fffc6a99b6e in G4VUserPhysicsList::~G4VUserPhysicsList() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #12 0x00007fffbd36c6a8 in LSExpPhysicsList::~LSExpPhysicsList (this=0xad650a0, __in_chrg=<optimized out>, __vtt_parm=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpPhysicsList.cc:152
    #13 0x00007fffbd36c6d0 in LSExpPhysicsList::~LSExpPhysicsList (this=0xad650a0, __in_chrg=<optimized out>, __vtt_parm=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpPhysicsList.cc:152
    #14 0x00007fffc6a71c7f in G4RunManager::DeleteUserInitializations() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #15 0x00007fffc6a7305b in G4RunManager::~G4RunManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #16 0x00007fffe314459f in G4SvcRunManager::~G4SvcRunManager (this=0x65e37f0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #17 0x00007fffe31445ba in G4SvcRunManager::~G4SvcRunManager (this=0x65e37f0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #18 0x00007fffcfda46db in G4Svc::~G4Svc (this=0x6ab7820, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #19 0x00007fffcfda472e in G4Svc::~G4Svc (this=0x6ab7820, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #20 0x00007fffd4b38513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007fffd4b38e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #22 0x00007fffd4b50b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #23 0x00007fffd4b4df64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #24 0x00007fffcc8d983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    


TUT_DETSIM_HARD_EXIT avoids the cleanup error, and relative saving works
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost oj]$ find /data1/blyth/log/oj/oj3/oj3/2026-04-07-1529/OJ_LOCAL_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV_2026Apr07_ok3_inputphoton_seed42_evtmax1/ -type f -name photon.npy
    /data1/blyth/log/oj/oj3/oj3/2026-04-07-1529/OJ_LOCAL_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV_2026Apr07_ok3_inputphoton_seed42_evtmax1/ALL0_no_opticks_event_name/B000/photon.npy
    /data1/blyth/log/oj/oj3/oj3/2026-04-07-1529/OJ_LOCAL_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV_2026Apr07_ok3_inputphoton_seed42_evtmax1/ALL0_no_opticks_event_name/A000/photon.npy
    A[blyth@localhost oj]$ find /data1/blyth/log/oj/oj3/oj3/2026-04-07-1529/OJ_LOCAL_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV_2026Apr07_ok3_inputphoton_seed42_evtmax1/ -type f -name hit.npy
    /data1/blyth/log/oj/oj3/oj3/2026-04-07-1529/OJ_LOCAL_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV_2026Apr07_ok3_inputphoton_seed42_evtmax1/ALL0_no_opticks_event_name/B000/hit.npy
    A[blyth@localhost oj]$ 



HUH: G4RunManagerKernel::RunTermination SIGSEGV
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 1659.403 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 1659.402 ms

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc6a82df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libnvidia-gpucomp-580.82.07-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffc6a82df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #1  0x00007fffe3144727 in G4SvcRunManager::finalizeRM (this=0x65ee9c0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #2  0x00007fffcfde5e8f in DetSimAlg::finalize (this=0x66733d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #3  0x00007fffd4b37d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd4b4cd6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd4b55588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd4b50611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd4b4d05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffcc8d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #9  0x00007fffd465a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007fffd465a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #11 0x00007fffd465f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #12 0x00007fffd4658182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #13 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x602a1c0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #14 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #15 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff774b350, func=0x7ffff7734520, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #17 PyEval_EvalCode (co=co@entry=0x547300, globals=globals@entry=0x7ffff774b350, locals=locals@entry=0x7ffff774b350) at Python/ceval.c:1148
    #18 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff774b350, globals=0x7ffff774b350, co=0x547300, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #19 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7717690, globals=globals@entry=0x7ffff774b350, locals=locals@entry=0x7ffff774b350, flags=flags@entry=0x7ffffffee788, arena=arena@entry=0x7ffff7e58d60) at Python/pythonrun.c:1762
    #20 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee788, closeit=<optimized out>, locals=0x7ffff774b350, globals=0x7ffff774b350, start=257, filename=0x7ffff7717690, fp=0x545520) at Python/pythonrun.c:1657
    #21 _PyRun_SimpleFileObject (fp=fp@entry=0x545520, filename=filename@entry=0x7ffff7717690, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee788) at Python/pythonrun.c:440
    #22 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x545520, filename=filename@entry=0x7ffff7717690, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee788) at Python/pythonrun.c:79
    #23 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7717690, program_name=0x7ffff7734460) at Modules/main.c:360
    #24 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #25 pymain_run_python (exitcode=0x7ffffffee784) at Modules/main.c:605
    #26 Py_RunMain () at Modules/main.c:684
    #27 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffee890) at Modules/main.c:714
    #28 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #29 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #30 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #31 0x0000000000401075 in _start ()
    (gdb) 



::

    120 bool
    121 DetSimAlg::finalize()
    122 {
    123     if (is_mt) {
    124         return true;
    125     }
    126 
    127     LogInfo << objName()
    128             << " finalized successfully"
    129             << std::endl;
    130     if (m_vis_mac.length()) {
    131         // If user set the vis mac file,
    132         // start to run the GUI
    133         return true;
    134     }
    135     if (run_manager) {
    136         run_manager->finalizeRM();
    137     }
    138     return true;
    139 }






ISTAMP=2026-04-07-1600 ~/oj/oj3/oj3.sh chi2 
-----------------------------------------------

A side all "TO AB"::

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum  3654.2351 ndf  1.0000 sum/ndf  3654.2351 </span> ]
    TO AB                                                                                            :    5000    512 :  3654.2351 : Y :       0      1 : <span class="r">DEVIANT</span>   
    TO BT SA                                                                                         :      -1   2114 :     0.0000 : N :      -1      3 : AZERO C2EXC  
    TO SC BT BT BT BT BT BT SA                                                                       :      -1    215 :     0.0000 : N :      -1      2 : AZERO C2EXC  
    TO SC AB                                                                                         :      -1    208 :     0.0000 : N :      -1     17 : AZERO C2EXC  
    TO SC BT BT BT BT BT BT EC                                                                       :      -1    197 :     0.0000 : N :      -1     33 : AZERO C2EXC  
    TO SC SC BT BT BT BT BT BT SA                                                                    :      -1     80 :     0.0000 : N :      -1     84 : AZERO C2EXC  
    TO SC SC BT BT BT BT BT BT EC                                                                    :      -1     79 :     0.0000 : N :      -1     32 : AZERO C2EXC  
    TO SC SC AB                                                                                      :      -1     71 :     0.0000 : N :      -1     37 : AZERO C2EXC  
    TO SC BT BT SA                                                                                   :      -1     56 :     0.0000 : N :      -1     22 : AZERO C2EXC  
    TO SC BT BT BT BT BT BT BT SA                                                                    :      -1     44 :     0.0000 : N :      -1     65 : AZERO C2EXC  
    TO SC BT SA                                                                                      :      -1     37 :     0.0000 : N :      -1     58 : AZERO C2EXC  
    TO SC BT BT BT SA                                                                                :      -1     34 :     0.0000 : N :      -1    348 : AZERO C2EXC  
    TO SC SC SC BT BT BT BT BT BT EC                                                                 :      -1     32 :     0.0000 : N :      -1     97 : AZERO C2EXC  




Usual reason for this : frame not being honoured as expected 
-------------------------------------------------------------


::

    PYTHONPATH=$HOME PICK=AB MODE=3 ISTAMP=1600 ~/oj/oj3/oj3.sh pdb



A side, local photons not placed into target frame::

    In [11]: a.f.record[:,:2]
    Out[11]: 
    array([[[[-250.   ,    0.   ,  230.   ,    0.1  ],
             [  -0.   ,   -0.   ,   -1.   ,    0.   ],
             [   0.   ,    1.   ,    0.   ,  440.   ],
             [   0.   ,    0.   ,    0.   ,    0.   ]],

            [[-250.   ,    0.   ,  230.   ,    0.1  ],
             [  -0.   ,   -0.   ,   -1.   ,    0.   ],
             [   0.   ,    1.   ,    0.   ,  440.   ],
             [  -0.   ,    0.   ,    0.   ,    0.   ]]],


           [[[-249.95 ,    0.   ,  230.   ,    0.1  ],
             [  -0.   ,   -0.   ,   -1.   ,    0.   ],
             [   0.   ,    1.   ,    0.   ,  440.   ],
             [   0.   ,    0.   ,    0.   ,    0.   ]],

            [[-249.95 ,    0.   ,  230.   ,    0.1  ],
             [  -0.   ,   -0.   ,   -1.   ,    0.   ],
             [   0.   ,    1.   ,    0.   ,  440.   ],
             [  -0.   ,    0.   ,    0.   ,    0.   ]]],


B side manage to go somewhere::

    In [12]: b.f.record[:,:2]
    Out[12]: 
    array([[[[  -250.   ,      0.   ,    230.   ,      0.1  ],
             [    -0.   ,     -0.   ,     -1.   ,      0.   ],
             [     0.   ,      1.   ,      0.   ,    440.   ],
             [     0.   ,      0.   ,      0.   ,      0.   ]],

            [[  -250.   ,      0.   , -15895.458,     82.696],
             [     0.634,     -0.195,      0.749,      0.   ],
             [     0.126,      0.981,      0.149,    440.   ],
             [     0.   ,      0.   ,      0.   ,      0.   ]]],


           [[[  -249.95 ,      0.   ,    230.   ,      0.1  ],
             [    -0.   ,     -0.   ,     -1.   ,      0.   ],
             [     0.   ,      1.   ,      0.   ,    440.   ],
             [     0.   ,      0.   ,      0.   ,      0.   ]],

            [[  -249.95 ,      0.   , -10897.409,     57.095],
             [    -0.   ,     -0.   ,     -1.   ,      0.   ],
             [     0.   ,      1.   ,      0.   ,    440.   ],
             [     0.   ,      0.   ,      0.   ,      0.   ]]],




SEvt::setFr not being called
-----------------------------


After SSim::afterPopulate addition of frame hookup the INPUT_PHOTON_FRAME is being honoured
-----------------------------------------------------------------------------------------------

::

    PYTHONPATH=$HOME PICK=AB MODE=3 ISTAMP=2026-04-07-2101 ~/oj/oj3/oj3.sh pdb


::

    In [1]: a.f.sfr
    Out[1]: 
    sframe       : 
    path         : ALL0_oj3ip_nnvt_1000/A000/sfr.npy
    meta         : creator:sfr::serialize
    name:NNVT:0:1000
    ce           : array([  0.   ,   0.   ,   5.438, 264.1  ])
    bbmn         : array([-264.1  , -264.1  , -183.225])
    bbmx         : array([264.1, 264.1, 194.1])
    m2w          : 
    array([[   -0.081,    -0.823,     0.562,     0.   ],
           [   -0.995,     0.098,     0.   ,     0.   ],
           [   -0.055,    -0.559,    -0.827,     0.   ],
           [ 1070.17 , 10865.62 , 16077.11 ,     1.   ]])

    w2m          : 
    array([[   -0.081,    -0.995,    -0.055,     0.   ],
           [   -0.823,     0.098,    -0.559,     0.   ],
           [    0.562,     0.   ,    -0.827,     0.   ],
           [   -0.006,    -0.   , 19434.002,     1.   ]])

    id           : 
    array([[ 1.,  0.,  0.,  0.],
           [ 0.,  1., -0.,  0.],
           [ 0., -0.,  1.,  0.],
           [-0., -0.,  0.,  1.]])



2026-04-08-0945 : ljbb assert after frame hookup change
---------------------------------------------------------

::

    #0  0x00007f4ec8cd8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f4ec8c4b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f4ebaef6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f4ec8e8d0f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f4ebaef4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f4ec8d6ea7c in __strlen_evex () from /lib64/libc.so.6
    #7  0x00007f4e8fb84b6d in sstr::EndsWith (s=0x0, q=0x7f4e8fd4ce55 ".npy") at /home/blyth/opticks/sysrap/sstr.h:255
    #8  0x00007f4e8fbcb30b in stree::get_frame (this=0x67be8a0, q_spec=0x0) at /home/blyth/opticks/sysrap/stree.h:2471
    #9  0x00007f4e8fbcb167 in stree::get_frame_moi_or_ipf (this=0x67be8a0) at /home/blyth/opticks/sysrap/stree.h:2433
    #10 0x00007f4e8fbb8aa9 in SSim::afterPopulated (this=0xda5c9b0) at /home/blyth/opticks/sysrap/SSim.cc:574
    #11 0x00007f4e925c92c8 in G4CXOpticks::setGeometry (this=0xdce6650, world=0xbcf0510) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:314
    #12 0x00007f4e925c7ae1 in G4CXOpticks::SetGeometry (world=0xbcf0510) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:79
    #13 0x00007f4e925c7d90 in G4CXOpticks::SetGeometry_JUNO (world=0xbcf0510, sd=0xb6d35b0, jpmt=0xd9cf290, jlut=0xda5bdc0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:121
    #14 0x00007f4e8ed45287 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xbcf0510, sd=0xb6d35b0, ppd=0x76e6ca0, psd=0x77ae240, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:54
    #15 0x00007f4e8ed08f30 in LSExpDetectorConstruction::setupOpticks (this=0xba8c9c0, world=0xbcf0510) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #16 0x00007f4e8ed087d0 in LSExpDetectorConstruction::Construct (this=0xba8c9c0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #17 0x00007f4e9c22992e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #18 0x00007f4e9c229afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #19 0x00007f4ea20eeb0b in DetSimAlg::initialize (this=0x79ed300) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80



after protect stree::get_frame from nullptr arg oj_build_initialize completes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    oj_build_initialize



BUT opticks-t has 28/220 FAIL : looking like no geom ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    FAILS:  28  / 220   :  Wed Apr  8 09:53:40 2026  :  GEOM J25_7_2_opticks_Debug  
      109/110 Test #109: SysRapTest.SBndTest                                     ***Failed                      0.09   
      3  /43  Test #3  : CSGTest.CSGNameTest                                     ***Failed                      0.10   
      4  /43  Test #4  : CSGTest.CSGNodeTest                                     ***Failed                      0.09   
      5  /43  Test #5  : CSGTest.CSGPrimTest                                     ***Failed                      0.09   
      6  /43  Test #6  : CSGTest.CSGPrimSpecTest                                 ***Failed                      0.10   
      11 /43  Test #11 : CSGTest.CSGTargetGlobalTest                             ***Failed                      0.10   
      19 /43  Test #19 : CSGTest.CSGFoundry_findSolidIdx_Test                    ***Failed                      0.09   
      20 /43  Test #20 : CSGTest.CSGFoundryTest                                  ***Failed                      0.09   
      21 /43  Test #21 : CSGTest.CSGFoundry_getCenterExtent_Test                 ***Failed                      0.09   
      22 /43  Test #22 : CSGTest.CSGFoundry_CreateFromSimTest                    ***Failed                      0.09   
      23 /43  Test #23 : CSGTest.CSGFoundry_MakeCenterExtentGensteps_Test        ***Failed                      0.17   
      24 /43  Test #24 : CSGTest.CSGFoundry_getFrame_Test                        ***Failed                      0.10   
      25 /43  Test #25 : CSGTest.CSGFoundry_getFrameE_Test                       ***Failed                      0.10   
      26 /43  Test #26 : CSGTest.CSGFoundry_getMeshName_Test                     ***Failed                      0.09   
      28 /43  Test #28 : CSGTest.CSGFoundryLoadTest                              ***Failed                      0.10   
      29 /43  Test #29 : CSGTest.CSGScanTest                                     ***Failed                      0.10   
      30 /43  Test #30 : CSGTest.CSGTargetTest                                   ***Failed                      0.09   
      33 /43  Test #33 : CSGTest.CSGQueryTest                                    ***Failed                      0.09   
      34 /43  Test #34 : CSGTest.CSGSimtraceTest                                 ***Failed                      0.09   
      35 /43  Test #35 : CSGTest.CSGSimtraceRerunTest                            ***Failed                      0.10   
      36 /43  Test #36 : CSGTest.CSGSimtraceSampleTest                           ***Failed                      0.09   
      37 /43  Test #37 : CSGTest.CSGCopyTest                                     ***Failed                      0.10   
      18 /22  Test #18 : QUDARapTest.QOpticalTest                                ***Failed                      0.01   
      19 /22  Test #19 : QUDARapTest.QSimWithEventTest                           ***Failed                      0.17   
      20 /22  Test #20 : QUDARapTest.QSimTest                                    ***Failed                      0.10   
      3  /4   Test #3  : CSGOptiXTest.CSGOptiXRenderTest                         ***Failed                      0.10   
      1  /2   Test #1  : G4CXTest.G4CXRenderTest                                 ***Failed                      0.41   
      2  /2   Test #2  : G4CXTest.G4CXOpticks_setGeometry_Test                   ***Failed                      0.13   


::

    (ok) A[blyth@localhost junosw]$ GEOM
    vi /home/blyth/.opticks/GEOM/GEOM.sh
    (ok) A[blyth@localhost junosw]$ geo
                                 BASH_SOURCE : /home/blyth/.opticks/GEOM/GEOM.sh
                                        geom : J25_7_2_opticks_Debug
                                        GEOM : J25_7_2_opticks_Debug
        J25_7_2_opticks_Debug_CFBaseFromGEOM : 
                              current_branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
                                      branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    (ok) A[blyth@localhost junosw]$ 



BINGO : UNEXPECTED J26_1_1_opticks_Debug
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (ok) A[blyth@localhost junosw]$ l /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/
    total 0
    0 drwxr-xr-x. 3 blyth blyth 97 Apr  8 09:51 J26_1_1_opticks_Debug
    0 drwxr-xr-x. 3 blyth blyth 35 Apr  7 21:41 .
    0 drwxr-xr-x. 3 blyth blyth 18 Apr  7 21:41 ..
    (ok) A[blyth@localhost junosw]$ l /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug/
    total 42056
        4 drwxr-xr-x. 3 blyth blyth     4096 Apr  8 09:51 CSGFoundry
        4 -rw-r--r--. 1 blyth blyth      279 Apr  8 09:51 origin_gdxml_report.txt
    21024 -rw-r--r--. 1 blyth blyth 21527618 Apr  8 09:51 origin.gdml
    21024 -rw-r--r--. 1 blyth blyth 21528538 Apr  8 09:51 origin_raw.gdml
        0 drwxr-xr-x. 3 blyth blyth       97 Apr  8 09:51 .


    (ok) A[blyth@localhost junosw]$ geo
                                 BASH_SOURCE : /home/blyth/.opticks/GEOM/GEOM.sh
                                        geom : J26_1_1_opticks_Debug
                                        GEOM : J26_1_1_opticks_Debug
                                   GEOM_NOTE : 81:LJBB_GEOM_IS_NOW_STANDARD
                                    CFB_CAND : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
                                         CFB : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
        J26_1_1_opticks_Debug_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
                              current_branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
                                      branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    (ok) A[blyth@localhost junosw]$ 


Jlatest got bumped to J26.1.1 yesterday causing the GEOM fail
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    [blyth@localhost junosw]$ l /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/
    total 36
    1 drwxrwxr-x. 37 cvmfs cvmfs   48 Apr  7 17:53 .
    1 lrwxrwxrwx.  1 cvmfs cvmfs    7 Apr  7 17:53 Jlatest -> J26.1.1
    1 drwxr-xr-x.  5 cvmfs cvmfs   10 Apr  7 17:53 J25.7.2
    1 drwxr-xr-x.  5 cvmfs cvmfs   76 Apr  2 11:34 J25.7.3
    1 drwxr-xr-x.  4 cvmfs cvmfs   44 Mar 25 18:04 J26.1.1
    1 drwxr-xr-x.  4 cvmfs cvmfs   44 Mar 23 15:59 J26.1.0
    1 drwxr-xr-x.  5 cvmfs cvmfs   76 Feb 11 00:19 J25.7.1
    1 drwxr-xr-x.  4 cvmfs cvmfs   44 Feb  7 10:36 J25.7.4
    1 drwxr-xr-x.  5 cvmfs cvmfs   59 Feb  6 15:05 J25.7.0
    1 drwxr-xr-x.  4 cvmfs cvmfs   76 Jan 13 23:02 J25.6.4
    1 drwxr-xr-x.  4 cvmfs cvmfs   59 Dec 26 18:08 J25.6.3

    A[blyth@localhost junosw]$ l /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
    1 lrwxrwxrwx. 1 cvmfs cvmfs 7 Apr  7 17:53 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest -> J26.1.1
    A[blyth@localhost junosw]$ readlink /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
    J26.1.1


After change GEOM in GEOM.sh, the test fails are fixed::

    (ok) A[blyth@localhost junosw]$ GEOM
    vi /home/blyth/.opticks/GEOM/GEOM.sh
    (ok) A[blyth@localhost junosw]$ geo
                                 BASH_SOURCE : /home/blyth/.opticks/GEOM/GEOM.sh
                                        geom : J26_1_1_opticks_Debug
                                        GEOM : J26_1_1_opticks_Debug
                                   GEOM_NOTE : 81:LJBB_GEOM_IS_NOW_STANDARD
                                    CFB_CAND : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
                                         CFB : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
        J26_1_1_opticks_Debug_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/.opticks/GEOM/J26_1_1_opticks_Debug
                              current_branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
                                      branch : blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    (ok) A[blyth@localhost junosw]$ 




GenEvtInfoAnaMgr 
~~~~~~~~~~~~~~~~

::

    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.415 / 15746.415
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.556 / 15746.556
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.583 / 15746.583
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.808 / 15746.808
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.864 / 15746.864
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15746.921 / 15746.921
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 15747.229 / 15747.229


FIXED : ana/npmeta.py : chi2 unclosed file ResourceWarning
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    oj;ojc


    pvplt MODE:2 
    [sseq_index_test.py

    /data1/blyth/local/opticks_Debug/py/opticks/ana/npmeta.py:129: ResourceWarning: unclosed file <_io.TextIOWrapper name='/tmp/blyth/opticks/sseq_index_test/sseq_index_ab_names.txt' mode='r' encoding='UTF-8'>
      lines = open(path, "r").read().splitlines()
    ResourceWarning: Enable tracemalloc to get the object allocation traceback
    f

    CMDLINE:/data1/blyth/local/opticks_Debug/bin/sseq_index_test.py
    f.base:/tmp/blyth/opticks/sseq_index_test



Above error shows using local opticks install, that is expected with OJ_LOCAL envset 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    oj;oje

    A[blyth@localhost oj]$ echo $OPTICKS_PREFIX
    /data1/blyth/local/opticks_Debug

    A[blyth@localhost oj]$ which sseq_index_test.sh        ## within local OPTICKS_PREFIX
    /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh

    

TODO: check chi2 from non OJ_LOCAL release
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~























opticksMode:3 background details review
-----------------------------------------


OJ python commanline : --opticks-anamgr --opticks-mode 3, replace "gun" with "opticks" and set envvars to configure input photons
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* formerly had to disable all other anamgr, is that still the case after custom4 0.1.9 ? 

::

    0500         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     501                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))

     497         default_opticks_mode = 1 if "OPTICKS_PREFIX" in os.environ else 0
     498         grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=default_opticks_mode,
     499                                 help=mh("Control Opticks GPU Optical simulation 0:CPU/1:GPU/3:CPU+GPU "))
     500         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     501                                 help=mh("Enable opticks+junosw/U4RecorderAnaMgr for optional use of opticks/U4Recorder saving Geant4 optical propagations into Opticks SEvt NumPy arrays."))


    2446         # == opticks
    2447         if args.opticks_anamgr:
    2448             if args.opticks_mode in [2,3]:
    2449                 log.info("appending U4RecorderAnaMgr to AnaMgrList in opticks_mode %d " % args.opticks_mode )
    2450                 detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2451                 g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2452                 g4ok_anamgr.setLogLevel(4)
    2453             elif args.opticks_mode in [0,1]:
    2454                 log.info("IGNORING: --opticks-anamgr option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )
    2455             else:
    2456                 log.info("UNEXPECTED opticks_mode %s " % args.opticks_mode )
    2457             pass
    2458         pass



where the input photons come from, how to configure them
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

     343 const char* SEvt::INPUT_GENSTEP_DIR = spath::Resolve("${SEvt__INPUT_GENSTEP_DIR:-$HOME/.opticks/InputGensteps}") ;
     344 const char* SEvt::INPUT_PHOTON_DIR = spath::Resolve("${SEvt__INPUT_PHOTON_DIR:-$HOME/.opticks/InputPhotons}") ;



OPTICKS_INPUT_PHOTON is the spec
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

     435 NP* SEvt::LoadInputPhoton() // static
     436 {
     437     const char* spec = SEventConfig::InputPhoton();
     438     return spec ? LoadInputPhoton(spec) : nullptr ;
     439 }
     440 NP* SEvt::LoadInputPhoton(const char* spec)
     441 {
     442     bool is_ipr = IsInputPhotonRecord(spec);
     443     NP* a = nullptr ;
     444     if(!is_ipr)
     445     {
     446         a = LoadInputPhoton_photon(spec);
     447     }
     448     else
     449     {
     450         a = LoadInputPhoton_record(spec);
     451     }
     452     return a ;
     453 }




OJ/U4RecorderAnaMgr
~~~~~~~~~~~~~~~~~~~~

* instanciates OK/U4Recorder instance
* passes G4Run G4Track G4Step to the U4Recorder
* regarding G4Event see junoSD_PMT_v2::Initialize/G4CXOpticks::SensitiveDetector_Initialize junoSD_PMT_v2::EndOfEvent/G4CXOpticks::SensitiveDetector_EndOfEvent

  * the G4Event is also passed to the U4Recorder, but via the SensitiveDetector
  * presumably evt handled differently for processing order reasons related to hits



::

     187 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     188 {
     ...
     246 #ifdef WITH_G4CXOPTICKS
     247     if(m_jpmt_opticks)
     248     {
     249         m_jpmt_opticks->Initialize(HCE, m_eventID);
     250     }

    139 #ifdef WITH_G4CXOPTICKS
    140 void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
    141 {  
    ...
    166     G4CXOpticks* gx = G4CXOpticks::Get() ;
    167     gx->SensitiveDetector_Initialize(eventID) ;   // invokes U4Recorder::BeginOfEventAction_


    631 void G4CXOpticks::SensitiveDetector_Initialize(int eventID)
    632 {
    633     LOG(LEVEL) << " eventID " << eventID ;
    634     U4Recorder* recorder = U4Recorder::Get();
    635     if(recorder)
    636     {
    637         recorder->BeginOfEventAction_(eventID);
    638     }
    639 }

    0363 void U4Recorder::BeginOfEventAction_(int eventID_)
     364 {
     365     eventID = eventID_ ;
     366     LOG(info) << " eventID " << eventID ;
     367     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     368     sev->beginOfEvent(eventID);
     369 }








    1149 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
    1150 {
    ...
    1160     if(m_jpmt_opticks)
    1161     {
    1162         m_jpmt_opticks->EndOfEvent(HCE, m_eventID );
    1163     }
    1164 


    199 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
    200 {
    201     G4CXOpticks* gx = G4CXOpticks::Get() ;
    202     gx->SensitiveDetector_EndOfEvent(eventID) ; // invokes U4Recorder::EndOfEventAction_ when recorder enabled
    203 
    204     if(m_merger == nullptr) m_merger = m_jpmt->getMergerOpticks(); // Alt merger for opticksMode:3
    205 
    206     LOG(LEVEL) << "[ " << m_jpmt->desc() ;
    207 
    208     LOG(LEVEL) << std::endl << m_jpmt->descHitCollection() ;
    209 
    210 
    211     if(m_gpu_simulation)
    212     {
    213         EndOfEvent_Simulate(eventID) ; // calls G4CXOpticks::simulate,  collectHit,  G4CXOpticks::reset
    214     }
    215 
    216     LOG(LEVEL) << "] " << m_jpmt->desc() ;
    217 }


    693 void G4CXOpticks::SensitiveDetector_EndOfEvent(int eventID)
    694 {
    695     LOG(LEVEL) << " eventID " << eventID ;
    696     U4Recorder* recorder = U4Recorder::Get();
    697     if(recorder)
    698     {
    699         recorder->EndOfEventAction_(eventID);
    700     }
    701 }


    0371 /**
     372 U4Recorder::EndOfEventAction
     373 -----------------------------
     374 
     375 This is happening later than expected causing lifecycle
     376 issues between the SEvt::ECPU and SEvt::EGPU
     377 
     378 **/
     379 
     380 void U4Recorder::EndOfEventAction_(int eventID_)
     381 {
     382     assert( eventID == eventID_ );
     383     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     384 
     385     #if defined(WITH_PMTSIM) && defined(POM_DEBUG)
     386         NP* mtda = PMTSim::ModelTrigger_Debug_Array();
     387         std::string name = mtda->get_meta<std::string>("NAME", "MTDA.npy") ;
     388         sev->add_array( name.c_str(), mtda );
     389     #else
     390         LOG(LEVEL) << "not-(WITH_PMTSIM and POM_DEBUG)"  ;
     391     #endif
     392 
     393 
     394     // adding to extrafold
     395     sev->add_array("TRS.npy", U4VolumeMaker::GetTransforms() );
     396     sev->add_array("U4R.npy", MakeMetaArray() );
     397     sev->addEventConfigArray();
     398 
     399     sev->gather() ;             // now gathers into fold, separate from topfold
     400 
     401     // ~/j/issues/jok-tds-B-side-missing-NPFold-concat.rst
     402     sev->topfold->concat();         // in this trivial one fold case just copies pointers and arranges skipdelete on fold arrays
     403     sev->topfold->clear_subfold();
     404 
     405     sev->endOfEvent(eventID_);  // does save and clear
     406 
     407     const char* savedir = sev->getSaveDir() ;
     408     LOG(LEVEL) << " savedir " << ( savedir ? savedir : "-" );
     409     SaveMeta(savedir);
     410 }



     571 void U4Recorder::PreUserTrackingAction_Optical_GetLabel( spho& ulabel, const G4Track* track )
     572 {
     573 #ifdef WITH_CUSTOM4_OLD
     574     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
     575 #elif WITH_CUSTOM4
     576     C4Pho* label = C4TrackInfo::GetRef(track);
     577 #else
     578     spho* label = STrackInfo::GetRef(track);
     579 #endif
     580 
     581     if( label == nullptr ) // happens with torch gensteps and input photons
     582     {
     583         PreUserTrackingAction_Optical_FabricateLabel(track) ;
     584 #ifdef WITH_CUSTOM4_OLD
     585         label = C4TrackInfo<C4Pho>::GetRef(track);
     586 #elif WITH_CUSTOM4
     587         label = C4TrackInfo::GetRef(track);
     588 #else
     589         label = STrackInfo::GetRef(track);
     590 #endif
     591     }
     592     assert( label && label->isDefined() );
     593 
     594 #ifdef WITH_CUSTOM4
     595     assert( C4Pho::N == spho::N );
     596 #endif
     597     std::array<int,spho::N> a_label ;
     598     label->serialize(a_label) ;
     599 
     600     ulabel.load(a_label);
     601 
     602     // serialize/load provides firebreak between C4Pho and spho
     603     // so the SEvt doesnt need to depend on CUSTOM4
     604 }




WITH_CUSTOM4_OLD for <= 0.1.8
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* templated vs not-templated track info

::

    ok) A[blyth@localhost u4]$ grep WITH_CUSTOM4_OLD *.*
    CMakeLists.txt:        target_compile_definitions(${name} PRIVATE WITH_CUSTOM4_OLD)
    CMakeLists.txt:        message(STATUS "${name}: Custom4 version ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, adding WITH_CUSTOM4_OLD")
    CMakeLists.txt:        message(STATUS "${name}: Custom4 version NOT: ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, NOT:adding WITH_CUSTOM4_OLD")
    U4.cc:#ifdef WITH_CUSTOM4_OLD
    U4.cc:#ifdef WITH_CUSTOM4_OLD
    U4Recorder.cc:#ifdef WITH_CUSTOM4_OLD
    U4Recorder.cc:#ifdef WITH_CUSTOM4_OLD
    U4Recorder.cc:#ifdef WITH_CUSTOM4_OLD
    U4Recorder.cc:#ifdef WITH_CUSTOM4_OLD
    U4Track.h:#ifdef WITH_CUSTOM4_OLD
    U4Track.h:#ifdef WITH_CUSTOM4_OLD
    (ok) A[blyth@localhost u4]$ 



u4/CMakeLists.txt::

    223 if(Custom4_FOUND)
    224     target_link_libraries(${name} PUBLIC Custom4::Custom4)
    225     target_compile_definitions(${name} PRIVATE WITH_CUSTOM4)
    226 
    227     set(Custom4_VERSION_TRANSITION "0.1.8")
    228     if(Custom4_VERSION VERSION_LESS_EQUAL ${Custom4_VERSION_TRANSITION})
    229         target_compile_definitions(${name} PRIVATE WITH_CUSTOM4_OLD)
    230         message(STATUS "${name}: Custom4 version ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, adding WITH_CUSTOM4_OLD")
    231     else()
    232         message(STATUS "${name}: Custom4 version NOT: ${Custom4_VERSION} <= ${Custom4_VERSION_TRANSITION}, NOT:adding WITH_CUSTOM4_OLD")
    233     endif()
    234 endif()
    235 




OK/U4Recorder manages ECPU SEvt 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

     242 /**
     243 U4Recorder::U4Recorder
     244 -----------------------
     245 
     246 CAUTION: LSExpDetectorConstruction_Opticks::Setup for opticksMode:2
     247 will instanciate SEvt if this is not used
     248 
     249 **/
     250 
     251 U4Recorder::U4Recorder()
     252     :
     253     eventID(-1),
     254     transient_fSuspend_track(nullptr),
     255     rerun_rand(nullptr),
     256     sev(SEvt::CreateOrReuse(SEvt::ECPU)),
     257     tree(nullptr)
     258 {
     259     init();
     260 }
     261 
     262 void U4Recorder::init()
     263 {
     264     INSTANCE = this ;
     265     init_SEvt();
     266 }
     267 




