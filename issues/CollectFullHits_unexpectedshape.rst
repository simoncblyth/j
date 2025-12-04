FIXED
==========

TEST=hitmerged ojt


336 void junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits(int eventID )
337 {
338     SProf::Add("junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD");
339     bool merge_flag = m_merger->getMergeFlag();
340     bool opticks_mode_merge = 1 == SEventConfig::ModeMerge() ;
341     size_t num_hit = SEvt::GetNumHit_EGPU() ;
342 
343     LOG(LEVEL)
344         << "[ eventID " << eventID
345         << " num_hit " << num_hit
346         << " m_hit_type " << m_hit_type
347         << " merge_flag " << ( merge_flag ? "YES" : "NO " )
348         << " opticks_mode_merge " << ( opticks_mode_merge  ? "YES" : "NO " )
349         << " SEventConfig::ModeLite " << SEventConfig::ModeLite()
350         ;
351 
352     assert( m_hit_type == 1 );
353     assert( m_merger );
354     assert( SEventConfig::ModeLite() == 0 );
355 
356     const SEvt* sev = SEvt::Get_EGPU();
357     const NP* _hit = sev ? sev->getHit() : nullptr ;
358     sphoton* hit = _hit ? (sphoton*)_hit->bytes() : nullptr ;
359 
360     bool expected_shape = _hit && _hit->has_shape(num_hit, 4, 4) ;
361     LOG_IF(fatal, !expected_shape)
362         << " sev " << ( sev ? "YES" : "NO " )
363         << " _hit.sstr " << ( _hit ? _hit->sstr() : "-" )
364         << " expected_shape " << ( expected_shape ? "YES" : "NO " )
365         << " SEventConfig::ModeLite " << SEventConfig::ModeLite()
366         << " SEventConfig::MergeWindow " << SEventConfig::MergeWindow()
367         << " merge_flag " << ( merge_flag ? "YES" : "NO " )
368         << " opticks_mode_merge " << ( opticks_mode_merge  ? "YES" : "NO " )
369         ;
370     assert( expected_shape );
371 

4791 const NP* SEvt::getPhoton() const {    return topfold->get(    SEventConfig::PhotonCompOneName()) ; }
4792 size_t    SEvt::getNumPhoton() const { return topfold->get_num(SEventConfig::PhotonCompOneName()) ; }
4793 const NP* SEvt::getHit() const {       return topfold->get(    SEventConfig::HitCompOneName()) ; }
4794 size_t    SEvt::getNumHit() const {    return topfold->get_num(SEventConfig::HitCompOneName()) ; }


Overhauled::

    1436 unsigned SEventConfig::HitCompOne() // static
    1437 {
    1438     unsigned comp = 0 ;
    1439     int64_t lite = ModeLite();
    1440     int64_t merge = ModeMerge();
    1441     int64_t lite_merge = lite*10 + merge ;
    1442     
    1443     if( lite == 0 || lite == 1 )
    1444     {
    1445         switch(lite_merge)
    1446         {
    1447             case   0: comp = SCOMP_HIT            ; break ;
    1448             case   1: comp = SCOMP_HITMERGED      ; break ;
    1449             case  10: comp = SCOMP_HITLITE        ; break ;
    1450             case  11: comp = SCOMP_HITLITEMERGED  ; break ;
    1451         }
    1452     }   
    1453     else if( lite == 2 )  // debug only
    1454     {
    1455         switch(lite_merge)
    1456         {
    1457             case  20: comp = SCOMP_HITLITE        ; break ;
    1458             case  21: comp = SCOMP_HITLITEMERGED  ; break ;
    1459         }   
    1460     }
    1461 
    1462     return comp ;
    1463 }







2025-12-04 14:11:49.907 ERROR [2911306] [SEvt::addGenstep@2273]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this  
2025-12-04 14:11:49.907 INFO  [2911306] [QSim::MaybeSaveIGS@770]  eventID 0 igs (90, 6, 4, ) igs_null NO  [QSim__SAVE_IGS_EVENTID] -1 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/tmp/blyth/opticks/.opticks/igs.npy] save_igs NO 
2025-12-04 14:11:49.907 INFO  [2911306] [QSim::simulate@465]  eventID      0 igs (90, 6, 4, ) tot_ph_0 9195 tot_ph_0/M 0 xxl NO  MaxSlot 10000000 MaxSlot/M 10 sslice::Desc(igs_slice)
sslice::Desc num_slice 1 TotalPhoton       9195 TotalPhoton/M   0.009195
                  start    stop     offset      count    count/M 
   0 : sslice {       0,      90,         0,      9195}  0.009195
                  start    stop     offset      count    count/M 
 num_slice 1
2025-12-04 14:11:49.907 INFO  [2911306] [QSim::simulate@487]    0 : sslice {       0,      90,         0,      9195}  0.009195
2025-12-04 14:11:49.928 INFO  [2911306] [SEvt::setNumPhoton@2486]  evt->num_photon 9195 evt->num_tag 0 evt->num_flat 0
2025-12-04 14:11:49.939 INFO  [2911306] [QSim::simulate@513]  eventID 0 xxl NO  i    0 dt    0.008301 slice    0 : sslice {       0,      90,         0,      9195}  0.009195
2025-12-04 14:11:49.939 INFO  [2911306] [SEvt::gather_components@3922]  num_comp 4 from provider QEvt fkey f000
2025-12-04 14:11:49.939 INFO  [2911306] [SEvt::gather_components@3932]  k         genstep a  <f4(90, 6, 4, ) null_component NO 
2025-12-04 14:11:49.940 INFO  [2911306] [QEvt::gatherPhoton@664] [ evt.num_photon 9195 p.sstr (9195, 4, 4, ) evt.photon 0x7fdc52000000
2025-12-04 14:11:49.940 INFO  [2911306] [SEvt::gather_components@3932]  k          photon a  <f4(9195, 4, 4, ) null_component NO 
2025-12-04 14:11:49.940 INFO  [2911306] [SEvt::gather_components@3932]  k             seq a  <u8(9195, 2, 2, ) null_component NO 
[SPM::merge_partial_select num_in 9195 select_flagmask 8192 time_window   1.000 
]SPM::merge_partial_select select_flagmask 8192 time_window   1.000 in 9195 selected 1614 merged 1611 selected/in   0.176 merged/selected   0.998 
2025-12-04 14:11:49.947 INFO  [2911306] [SEvt::gather_components@3932]  k       hitmerged a  <f4(1611, 4, 4, ) null_component NO 
2025-12-04 14:11:49.947 INFO  [2911306] [SEvt::gather_components@3960]  num_comp 4 num_genstep 90 num_photon 9195 num_hit -1 gather_total 1 genstep_total 90 photon_total 9195 hit_total 0

HMM: hitmerged is present but num_hit 0 ? 


2025-12-04 14:11:49.947 INFO  [2911306] [QSim::simulate@543]  num_slice 1 has_hm YES has_hlm NO  do_final_merge NO 
2025-12-04 14:11:49.947 INFO  [2911306] [junoSD_PMT_v2_Opticks::EndOfEvent_Simulate@257] [ eventID 0 [G4CXOpticks::descSimulate
SEvt::descSimulate instance 0 index 0 num_genstep 90 num_photon 9195 num_hit 0 num_hit.is_undef NO  sev.brief SEvt::brief  getIndex 0 hasInputPhoton N hasInputPhotonTransformed N]G4CXOpticks::descSimulate

2025-12-04 14:11:49.947 INFO  [2911306] [junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits@343] [ eventID 0 num_hit 0 m_hit_type 1 merge_flag YES opticks_mode_merge YES SEventConfig::ModeLite 0
2025-12-04 14:11:49.947 FATAL [2911306] [junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits@361]  sev YES _hit.sstr - expected_shape NO  SEventConfig::ModeLite 0 SEventConfig::MergeWindow 1 merge_flag YES opticks_mode_merge YES
python: /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:370: void junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits(int): Assertion `expected_shape' failed.
 *** Break *** abort



===========================================================
There was a crash.
This is the entire stack trace of all threads:
===========================================================

Thread 5 (Thread 0x7fdd1f0ea640 (LWP 2911361) "cuda-EvtHandlr"):
#0  0x00007fdd8650200f in poll () from /lib64/libc.so.6
#1  0x00007fdd4451cb37 in ?? () from /lib64/libcuda.so.1
#2  0x00007fdd4460bd77 in ?? () from /lib64/libcuda.so.1
#3  0x00007fdd44508883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fdd8648a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fdd8650f240 in clone3 () from /lib64/libc.so.6

Thread 4 (Thread 0x7fdd1f8eb640 (LWP 2911360) "python"):
#0  0x00007fdd8648722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
#1  0x00007fdd8648996f in pthread_cond_timedwait

GLIBC_2.3.2 () from /lib64/libc.so.6
#2  0x00007fdd44469b5a in ?? () from /lib64/libcuda.so.1
#3  0x00007fdd44508883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fdd8648a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fdd8650f240 in clone3 () from /lib64/libc.so.6

Thread 3 (Thread 0x7fdd4bdff640 (LWP 2911326) "cuda00001c00008"):
#0  0x00007fdd8650200f in poll () from /lib64/libc.so.6
#1  0x00007fdd4451cb37 in ?? () from /lib64/libcuda.so.1
#2  0x00007fdd4460bd77 in ?? () from /lib64/libcuda.so.1
#3  0x00007fdd44508883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fdd8648a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fdd8650f240 in clone3 () from /lib64/libc.so.6

Thread 2 (Thread 0x7fdd5c3ff640 (LWP 2911316) "python"):
#0  0x00007fdd8648722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
#1  0x00007fdd8648996f in pthread_cond_timedwait

GLIBC_2.3.2 () from /lib64/libc.so.6
#2  0x00007fdd86a4df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7fdd86d50f38 <_PyRuntime+440>, cond=0x7fdd86d50f08 <_PyRuntime+392>) at Python/condvar.h:73
#3  take_gil (tstate=tstate
entry=0x784ef20) at Python/ceval_gil.h:231
#4  0x00007fdd86a4e43e in PyEval_RestoreThread (tstate=tstate
entry=0x784ef20) at Python/ceval.c:521
#5  0x00007fdd86b15894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
#6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
#7  0x00007fdd869a88f2 in cfunction_vectorcall_O (func=0x7fdd867a79c0, args=0x7fdd866ba1e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
#8  0x00007fdd8695a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7fdd867a79c0, tstate=0x784ef20) at ./Include/internal/pycore_call.h:92
#9  PyObject_Vectorcall (callable=0x7fdd867a79c0, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
#10 0x00007fdd868fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
#11 0x00007fdd86a4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7fdd866ba188, tstate=0x784ef20) at ./Include/internal/pycore_ceval.h:73
#12 _PyEval_Vector (tstate=0x784ef20, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
#13 0x00007fdd86901e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7fdd78be6d00, callargs=0x7fdd78b77130, func=0x7fdd78b7f4c0, tstate=0x784ef20) at Python/ceval.c:7349
#14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
#15 0x00007fdd86a4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7fdd866ba020, tstate=0x784ef20) at ./Include/internal/pycore_ceval.h:73
#16 _PyEval_Vector (tstate=0x784ef20, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
#17 0x00007fdd8695cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7fdd5c3feda8, callable=0x7fdd78b028e0, tstate=0x784ef20) at ./Include/internal/pycore_call.h:92
#18 method_vectorcall (method=<optimized out>, args=0x7fdd86d5f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
#19 0x00007fdd86b13fe2 in thread_run (boot_raw=0x7861de0) at ./Modules/_threadmodule.c:1124
#20 0x00007fdd86aa87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
#21 0x00007fdd8648a19a in start_thread () from /lib64/libc.so.6
#22 0x00007fdd8650f240 in clone3 () from /lib64/libc.so.6

Thread 1 (Thread 0x7fdd86e1b4c0 (LWP 2911306) "python"):
#0  0x00007fdd864d8fff in wait4 () from /lib64/libc.so.6
#1  0x00007fdd8644b7e3 in do_system () from /lib64/libc.so.6
#2  0x00007fdd786f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
#3  0x00007fdd8668d0f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
#4  0x00007fdd786f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
#5  <signal handler called>
#6  0x00007fdd8648bedc in __pthread_kill_implementation () from /lib64/libc.so.6
#7  0x00007fdd8643eb46 in raise () from /lib64/libc.so.6
#8  0x00007fdd86428833 in abort () from /lib64/libc.so.6
#9  0x00007fdd8642875b in __assert_fail_base.cold () from /lib64/libc.so.6
#10 0x00007fdd86437886 in __assert_fail () from /lib64/libc.so.6
#11 0x00007fdd4bf763da in junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits (this=0xc591f60, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:370
#12 0x00007fdd4bf75d59 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xc591f60, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:269
#13 0x00007fdd4bf75a28 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xc591f60, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:214
#14 0x00007fdd4bf655f6 in junoSD_PMT_v2::EndOfEvent (this=0x84ba430, HCE=0xc42043e0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1141
#15 0x00007fdd595c30fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
#16 0x00007fdd59c49a80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
#17 0x00007fdd6f38468e in G4SvcRunManager::SimulateEvent (this=0x85275b0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
#18 0x00007fdd62161d3e in DetSimAlg::execute (this=0x84f0ed0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
#19 0x00007fdd673e64b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#20 0x00007fdd673eabbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#21 0x00007fdd673e6054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#22 0x00007fdd5cbd48d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
#23 0x00007fdd6e22a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#24 0x00007fdd6e22a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#25 0x00007fdd6e22f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#26 0x00007fdd6e228182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.

