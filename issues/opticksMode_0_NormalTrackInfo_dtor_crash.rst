opticksMode_0_NormalTrackInfo_dtor_crash.rst
===============================================


Probable corruption from Custom4 assuming/setting track info that stomps on NormalTrackInfo
Custom4 0.1.8 use of templated track info is a mistake that forced static_cast which
is very brittle.

Hmm, see ~/j/custom4/ where are looking into the state if custom4



::


    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-03-30 17:56:41.647 [junoSD_PMT_v2::Initialize eventID 0
    2026-03-30 17:56:41.648 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    -------- WWWW ------- G4Exception-START -------- WWWW -------
    *** G4Exception : Warning
          issued by : G4Step::GetDeltaEnergy()
    This method is obsolete and will be removed soon
    *** This is just a warning message. ***
    -------- WWWW -------- G4Exception-END --------- WWWW -------

     *** Break *** segmentation violation



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 3 (Thread 0x7f0010fff640 (LWP 544495) "cuda00001c00008"):
    #0  0x00007f004b70200f in poll () from /lib64/libc.so.6
    #1  0x00007f000931cb37 in ?? () from /lib64/libcuda.so.1
    #2  0x00007f000940bd77 in ?? () from /lib64/libcuda.so.1
    #3  0x00007f0009308883 in ?? () from /lib64/libcuda.so.1
    #4  0x00007f004b68a19a in start_thread () from /lib64/libc.so.6
    #5  0x00007f004b70f240 in clone3 () from /lib64/libc.so.6

    Thread 2 (Thread 0x7f00215ff640 (LWP 544485) "python"):
    #0  0x00007f004b68722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f004b68996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f004bc4df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f004bf50f38 <_PyRuntime+440>, cond=0x7f004bf50f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x636dfe0) at Python/ceval_gil.h:231
    #4  0x00007f004bc4e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x636dfe0) at Python/ceval.c:521
    #5  0x00007f004bd15894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f004bba88f2 in cfunction_vectorcall_O (func=0x7f004b8b79c0, args=0x7f004b5791e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f004bb5a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f004b8b79c0, tstate=0x636dfe0) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f004b8b79c0, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f004bafe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f004bc4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f004b579188, tstate=0x636dfe0) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x636dfe0, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f004bb01e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f003ddebf00, callargs=0x7f003dd974c0, func=0x7f003dd3f9c0, tstate=0x636dfe0) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f004bc4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f004b579020, tstate=0x636dfe0) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x636dfe0, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f004bb5cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f00215feda8, callable=0x7f003dd4ed40, tstate=0x636dfe0) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f004bf5f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f004bd13fe2 in thread_run (boot_raw=0x6ad8120) at ./Modules/_threadmodule.c:1124
    #20 0x00007f004bca87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f004b68a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f004b70f240 in clone3 () from /lib64/libc.so.6

    Thread 1 (Thread 0x7f004b90d740 (LWP 544470) "python"):
    #0  0x00007f004b6d8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f004b64b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f003d8f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f004b54c0f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f003d8f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f004b69a28e in free () from /lib64/libc.so.6
    #7  0x00007f001bbeca81 in __gnu_cxx::new_allocator<int>::deallocate (this=0xc0fdee58, __p=0x1040000000000, __t=18446672605453746176) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/include/c++/11.4.1/ext/new_allocator.h:145
    #8  0x00007f001bbebd26 in std::allocator_traits<std::allocator<int> >::deallocate (__a=..., __p=0x1040000000000, __n=18446672605453746176) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/include/c++/11.4.1/bits/alloc_traits.h:496
    #9  0x00007f001bbea7e8 in std::_Vector_base<int, std::allocator<int> >::_M_deallocate (this=0xc0fdee58, __p=0x1040000000000, __n=18446672605453746176) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/include/c++/11.4.1/bits/stl_vector.h:354
    #10 0x00007f001bbeb79e in std::_Vector_base<int, std::allocator<int> >::~_Vector_base (this=0xc0fdee58, __in_chrg=<optimized out>) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/include/c++/11.4.1/bits/stl_vector.h:335
    #11 0x00007f001bbeb893 in std::vector<int, std::allocator<int> >::~vector (this=0xc0fdee58, __in_chrg=<optimized out>) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/include/c++/11.4.1/bits/stl_vector.h:683
    #12 0x00007f001b412366 in NormalTrackInfo::~NormalTrackInfo (this=0xc0fdee40, __in_chrg=<optimized out>) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:59
    #13 0x00007f001b41238e in NormalTrackInfo::~NormalTrackInfo (this=0xc0fdee40, __in_chrg=<optimized out>) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:59
    #14 0x00007f001a6432fa in G4Track::~G4Track() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4track.so
    #15 0x00007f001ac18795 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #16 0x00007f003458468e in G4SvcRunManager::SimulateEvent (this=0x77abec0, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #17 0x00007f0022088d2e in DetSimAlg::execute (this=0x770de90) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #18 0x00007f00264db4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #19 0x00007f00264dfbbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #20 0x00007f00264db054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007f0020bd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #22 0x00007f002885a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #23 0x00007f002885a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0



::

     199 G4VParticleChange*
     200 C4OpBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     201 {
     202         m_track_label = C4TrackInfo<C4Pho>::GetRef(&aTrack);
     203 #ifdef C4_DEBUG_PIDX
     204         m_track_dump = ( m_track_label != nullptr && m_track_label->id == PIDX && PIDX_ENABLED ) || PIDX == -2  ;
     205 #endif
     206 


     53 /**
     54 C4TrackInfo::GetTrackInfo
     55 --------------------------
     56 
     57 With U4PhotonInfo the ancestor of STrackInfo was using dynamic_cast 
     58 without issue. After moving to the templated STrackInfo the 
     59 dynamic cast always giving nullptr. So switched to static_cast. 
     60 
     61 **/
     62 
     63 template<typename T>
     64 inline C4TrackInfo<T>* C4TrackInfo<T>::GetTrackInfo(const G4Track* track) // static, label by value 
     65 {
     66     G4VUserTrackInformation* ui = track->GetUserInformation() ;
     67     C4TrackInfo<T>* trackinfo = ui ? static_cast<C4TrackInfo<T>*>(ui) : nullptr ;
     68     return trackinfo ;
     69 }
     70 
     71 template<typename T>
     72 inline C4TrackInfo<T>* C4TrackInfo<T>::GetTrackInfo_dynamic(const G4Track* track) // static, label by value 
     73 {
     74     G4VUserTrackInformation* ui = track->GetUserInformation() ;
     75     C4TrackInfo<T>* trackinfo = ui ? dynamic_cast<C4TrackInfo<T>*>(ui) : nullptr ;
     76     return trackinfo ;
     77 }
     78 
     79 

    096 template<typename T>
     97 inline T* C4TrackInfo<T>::GetRef(const G4Track* track) // static, label reference 
     98 {
     99     C4TrackInfo<T>* trackinfo = GetTrackInfo(track);
    100     return trackinfo ? &(trackinfo->label) : nullptr ;
    101 }






