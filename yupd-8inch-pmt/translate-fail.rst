translate fail
==================

ljbb::

    entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4SubtractionSolid] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sInnerReflectorInCD_TSubWaterDistributor_cutTube2] num_entityType 0 num_solidName 480 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4SubtractionSolid] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sOuterWaterInCD_TSubWaterDistributor_cutTube2] num_entityType 0 num_solidName 480 num 480
    U4Mesh::NumberOfRotationSteps
     entityType_ekey[U4Mesh__NumberOfRotationSteps_entityType_G4SubtractionSolid] solidName_ekey[U4Mesh__NumberOfRotationSteps_solidName_sOuterReflectorInCD_TSubWaterDistributor_cutTube2] num_entityType 0 num_solidName 480 num 480
    ]U4Tree::initSolids
    2026-01-08 15:58:08.172 INFO  [3720664] [U4Tree::init@300] -initNodes
    2026-01-08 15:58:12.702 INFO  [3720664] [U4Tree::init@302] -initSurfaces_Serialize
    2026-01-08 15:58:12.718 INFO  [3720664] [U4Tree::init@305] -initStandard
    2026-01-08 15:58:12.792 INFO  [3720664] [U4Tree::init@308] -initRecorder
    U4Tree::initRecorder FAIL no U4Recorder
    U4Tree::init U4Tree::desc
     st Y
     top Y
     sid Y
     level 0
     lvidx 348
     pvs 385989
     materials 23
     surfaces 124
     solids 348
     enable_osur YES
     enable_isur YES

    2026-01-08 15:58:12.792 INFO  [3720664] [U4Tree::Create@227] ]new U4Tree
    2026-01-08 15:58:12.792 INFO  [3720664] [U4Tree::Create@229] [stree::factorize
    python: /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:4966: void stree::collectGlobalNodes(): Assertion `do_triangulate == false && "triangulate solid is currently only supported for remainder nodes"' failed.
     *** Break *** abort



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 3 (Thread 0x7f16d35ff640 (LWP 3720686) "cuda00001c00008"):
    #0  0x00007f170df0200f in poll () from /lib64/libc.so.6
    #1  0x00007f16cbb1cb37 in ?? () from /lib64/libcuda.so.1
    #2  0x00007f16cbc0bd77 in ?? () from /lib64/libcuda.so.1
    #3  0x00007f16cbb08883 in ?? () from /lib64/libcuda.so.1
    #4  0x00007f170de8a19a in start_thread () from /lib64/libc.so.6
    #5  0x00007f170df0f240 in clone3 () from /lib64/libc.so.6

    Thread 2 (Thread 0x7f16e3dff640 (LWP 3720676) "python"):
    #0  0x00007f170de8722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f170de8996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f170e44df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f170e750f38 <_PyRuntime+440>, cond=0x7f170e750f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x5948a10) at Python/ceval_gil.h:231
    #4  0x00007f170e44e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x5948a10) at Python/ceval.c:521
    #5  0x00007f170e515894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f170e3a88f2 in cfunction_vectorcall_O (func=0x7f170e0df920, args=0x7f170e7e91e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f170e35a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f170e0df920, tstate=0x5948a10) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f170e0df920, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f170e2fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f170e44f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f170e7e9188, tstate=0x5948a10) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x5948a10, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f170e301e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f17005efb00, callargs=0x7f170053c790, func=0x7f170054bce0, tstate=0x5948a10) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f170e44f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f170e7e9020, tstate=0x5948a10) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x5948a10, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f170e35cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f16e3dfeda8, callable=0x7f1700546de0, tstate=0x5948a10) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f170e75f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f170e513fe2 in thread_run (boot_raw=0x1481e40) at ./Modules/_threadmodule.c:1124
    #20 0x00007f170e4a87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f170de8a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f170df0f240 in clone3 () from /lib64/libc.so.6

    Thread 1 (Thread 0x7f170e870740 (LWP 3720664) "python"):
    #0  0x00007f170ded8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f170de4b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f17000f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f17003e10f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f17000f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f170de8bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #7  0x00007f170de3eb46 in raise () from /lib64/libc.so.6
    #8  0x00007f170de28833 in abort () from /lib64/libc.so.6
    #9  0x00007f170de2875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007f170de37886 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f16d78662e3 in stree::collectGlobalNodes (this=0x69e81f0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:4966
    #12 0x00007f16d78666a4 in stree::factorize (this=0x69e81f0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:5042
    #13 0x00007f16d7875faf in U4Tree::Create (st=0x69e81f0, top=0xa8aef10, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:230
    #14 0x00007f16d781c0e8 in G4CXOpticks::setGeometry (this=0xc97a830, world=0xa8aef10) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:305
    #15 0x00007f16d781aaa1 in G4CXOpticks::SetGeometry (world=0xa8aef10) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:79
    #16 0x00007f16d781ad50 in G4CXOpticks::SetGeometry_JUNO (world=0xa8aef10, sd=0x6a8a4c0, jpmt=0xb963ed0, jlut=0xb995ee0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:117
    #17 0x00007f16d3d50ce2 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xa8aef10, sd=0x6a8a4c0, ppd=0x662f690, psd=0x678dc60, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #18 0x00007f16d3d14aa8 in LSExpDetectorConstruction::setupOpticks (this=0xa616c00, world=0xa8aef10) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #19 0x00007f16d3d14348 in LSExpDetectorConstruction::Construct (this=0xa616c00) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #20 0x00007f16e161092e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #21 0x00007f16e1610afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #22 0x00007f16e67e5b0b in DetSimAlg::initialize (this=0x663d120) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #23 0x00007f16eb537b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #24 0x00007f16eb54d09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #25 0x00007f16eb555447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #26 0x00007f16eb54d048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #27 0x00007f16e45d48d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #28 0x00007f16eb05a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #29 0x00007f16eb05a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #30 0x00007f16eb05f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #31 0x00007f16eb058182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #32 0x00007f170e359cc3 in _PyObject_MakeTpCall (tstate=0x7f170e779738 <_PyRuntime+166328>, callable=0x5ffcbe0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #33 0x00007f170e2fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #34 0x00007f170e44f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f170e87f020, tstate=0x7f170e779738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #35 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f1700749b00, func=0x7f170e0c09a0, tstate=0x7f170e779738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #36 PyEval_EvalCode (co=co
    entry=0x52ec00, globals=globals
    entry=0x7f1700749b00, locals=locals
    entry=0x7f1700749b00) at Python/ceval.c:1148
    #37 0x00007f170e4980ed in run_eval_code_obj (locals=0x7f1700749b00, globals=0x7f1700749b00, co=0x52ec00, tstate=0x7f170e779738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #38 run_mod (mod=<optimized out>, filename=filename
    entry=0x7f170e057360, globals=globals
    entry=0x7f1700749b00, locals=locals
    entry=0x7f1700749b00, flags=flags




::

    4949 inline void stree::collectGlobalNodes()
    4950 {
    4951     assert( rem.size() == 0u );
    4952     assert( tri.size() == 0u );
    4953 
    4954     for(int nidx=0 ; nidx < int(nds.size()) ; nidx++)
    4955     {
    4956         const snode& nd = nds[nidx] ;
    4957         assert( nd.index == nidx );
    4958         bool do_triangulate = is_triangulate(nd.lvid) ;
    4959         if( nd.repeat_index == 0 )
    4960         {
    4961             std::vector<snode>& dst = do_triangulate ? tri : rem  ;
    4962             dst.push_back(nd) ;
    4963         }
    4964         else
    4965         {
    4966             assert( do_triangulate == false && "triangulate solid is currently only supported for remainder nodes" );
    4967             // HMM: FOR TRI FACTOR NODES NEED TO OPERATE WITH THE SUBTREES : AS ALL OF THE FUTURE CSGSolid
    4968             // HAS TO BE TRI TOGETHER : SO CAN DO NOTHING HERE
    4969         }
    4970     }
    4971     if(level>0) std::cout
    4972        << "stree::collectGlobalNodes "
    4973        << descNodes()
    4974        << descForceTriangulateLVID()
    4975        << std::endl
    4976        ;
    4977 }
    4978 


Add some debug::

    4949 inline void stree::collectGlobalNodes()
    4950 {
    4951     assert( rem.size() == 0u );
    4952     assert( tri.size() == 0u );
    4953 
    4954     for(int nidx=0 ; nidx < int(nds.size()) ; nidx++)
    4955     {
    4956         const snode& nd = nds[nidx] ;
    4957         assert( nd.index == nidx );
    4958         bool do_triangulate = is_triangulate(nd.lvid) ;
    4959         bool do_triangulate_non_global = nd.repeat_index > 0 && do_triangulate ;
    4960 
    4961         if( do_triangulate_non_global ) std::cerr
    4962             << "stree::collectGlobalNodes"
    4963             << " nidx " << nidx
    4964             << " nd.lvid " << nd.lvid
    4965             << " soname[nd.lvid] " << soname[nd.lvid]
    4966             << " do_triangulate " << ( do_triangulate ? "YES" : "NO " )
    4967             << " do_triangulate_non_global " << ( do_triangulate_non_global ? "YES" : "NO " )
    4968             << "\n"
    4969             ;
    4970 
    4971 
    4972         if( nd.repeat_index == 0 )
    4973         {
    4974             std::vector<snode>& dst = do_triangulate ? tri : rem  ;
    4975             dst.push_back(nd) ;
    4976         }
    4977         else
    4978         {
    4979 
    4980             assert( do_triangulate == false && "triangulate solid is currently only supported for remainder nodes" );
    4981             // HMM: FOR TRI FACTOR NODES NEED TO OPERATE WITH THE SUBTREES : AS ALL OF THE FUTURE CSGSolid
    4982             // HAS TO BE TRI TOGETHER : SO CAN DO NOTHING HERE
    4983         }
    4984     }
    4985     if(level>0) std::cout
    4986        << "stree::collectGlobalNodes "
    4987        << descNodes()
    4988        << descForceTriangulateLVID()
    4989        << std::endl
    4990        ;
    4991 }



::

    2026-01-08 16:27:13.453 INFO  [35087] [U4Tree::Create@227] ]new U4Tree
    2026-01-08 16:27:13.453 INFO  [35087] [U4Tree::Create@229] [stree::factorize
    stree::collectGlobalNodes nidx 383589 nd.lvid 343 soname[nd.lvid] PMT_8inch_pmt_solid do_triangulate YES do_triangulate_non_global YES
    python: /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:4980: void stree::collectGlobalNodes(): Assertion `do_triangulate == false && "triangulate solid is currently only supported for remainder nodes"' failed.
     *** Break *** abort



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 3 (Thread 0x7f60467ff640 (LWP 35106) "cuda00001c00008"):
    #0  0x00007f608110200f in poll () from /lib64/libc.so.6
    #1  0x00007f603ed1cb37 in ?? () from /lib64/libcuda.so.1
    #2  0x00007f603ee0bd77 in ?? () from /lib64/libcuda.so.1
    #3  0x00007f603ed08883 in ?? () from /lib64/libcuda.so.1
    #4  0x00007f608108a19a in start_thread () from /lib64/libc.so.6
    #5  0x00007f608110f240 in clone3 () from /lib64/libc.so.6

    Thread 2 (Thread 0x7f6056fff640 (LWP 35098) "python"):
    #0  0x00007f608108722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f608108996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f608164df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f6081950f38 <_PyRuntime+440>, cond=0x7f6081950f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x622f990) at Python/ceval_gil.h:231
    #4  0x00007f608164e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x622f990) at Python/ceval.c:521
    #5  0x00007f6081715894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f60815a88f2 in cfunction_vectorcall_O (func=0x7f60812df920, args=0x7f606b4b71e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f608155a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f60812df920, tstate=0x622f990) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f60812df920, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f60814fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f608164f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f606b4b7188, tstate=0x622f990) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x622f990, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f6081501e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f60737ef700, callargs=0x7f607377f0a0, func=0x7f6073783ce0, tstate=0x622f990) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f608164f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f606b4b7020, tstate=0x622f990) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x622f990, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f608155cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f6056ffeda8, callable=0x7f6073746de0, tstate=0x622f990) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f608195f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f6081713fe2 in thread_run (boot_raw=0x1105530) at ./Modules/_threadmodule.c:1124
    #20 0x00007f60816a87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f608108a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f608110f240 in clone3 () from /lib64/libc.so.6





PMT_8inch_pmt_solid : why is that getting marked to triangulate ?
---------------------------------------------------------------------

::

    (ok) A[blyth@localhost junosw]$ jgr PMT_8inch
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  IPMTElement* pmt_det_8inch = dynamic_cast<IPMTElement*>(det_elem("Hello8inchPMTManager/PMT_8inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  IPMTElement* pmt_det_8inch_BTM = dynamic_cast<IPMTElement*>(det_elem("Hello8inchPMTManager/PMT_8inch_BTM"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det = dynamic_cast<IPMTElement*>(det_elem("Hello8inchPMTManager/PMT_8inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    IPMTElement* mpmt_pmt = dynamic_cast<IPMTElement*>(det_elem("Ham8inchPMTManager/PMT_8inch"));
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        else if (volname == "PMT_8inch_body_phys") {
    (ok) A[blyth@localhost junosw]$ 



jcv LSExpDetectorConstruction::

    1410 
    1411   // Atm PMT Veto in water pool  
    1412   if (m_veto_pmt_pos_mode.size()!=0) {
    1413     IDetElementPos* veto_atm_pmt_detelem_pos = new JUNO::Cylinder::AtmPmtPosCylinder(m_scope);
    1414     IPMTElement* mcppmt_pmt = dynamic_cast<IPMTElement*>(det_elem("NNVTMCPPMTManager/PMT_20inch"));
    1415     m_pmt_mother = "OuterWaterAtmLpmtVeto";
    1416     bool veto_status = de_wp_det->inject(m_pmt_mother, mcppmt_pmt, veto_atm_pmt_detelem_pos);
    1417     assert (veto_status);
    1418   }
    1419 
    1420   // MPMT in water pool atmosphere  
    1421   if (m_veto_pmt_pos_mode.size()!=0) {
    1422     IDetElementPos* mpmt_detelem_pos = new JUNO::Cylinder::AtmPmtPosCylinder(m_scope, true); // true for MPMT
    1423     IPMTElement* mpmt_pmt = dynamic_cast<IPMTElement*>(det_elem("Ham8inchPMTManager/PMT_8inch"));
    1424     m_pmt_mother = "OuterWaterAtmMpmtVeto";  // Place MPMT in the same volume as ATM PMTs
    1425     bool mpmt_status = de_wp_det->inject(m_pmt_mother, mpmt_pmt, mpmt_detelem_pos);
    1426     assert (mpmt_status);
    1427   }
    1428 }


::

    118 void
    119 Ham8inchPMTManager::init_variables() {
    120     m_pmt_r = 101.*mm;
    121     m_pmt_h = 220.*mm;
    122     m_z_equator = 75.5*mm; // From top to equator
    123 
    124     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
    125     m_pmtsolid_maker = new R12860_PMTSolid(
    126                             m_pmt_r,
    127                             m_z_equator,
    128                             23*mm,
    129                             42.5*mm,
    130                             m_pmt_h,
    131                             62.*mm
    132                             );
    133 }
    134 



    233 void
    234 Ham8inchPMTManager::helper_make_solid()
    235 {
    236     pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    237     body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid");
    238     inner_solid= m_pmtsolid_maker->GetSolid(GetName()+"_inner_solid", -5*mm);
    239 
    240     G4double helper_sep_tube_r = m_pmt_r;
    241     G4double helper_sep_tube_h = m_z_equator;
    242     G4double helper_sep_tube_hh = helper_sep_tube_h/2;
    243 
    244     //G4double helper_sep_tube_r = 95.*mm;
    245     //G4double helper_sep_tube_h = 49.87*mm;
    246     //G4double helper_sep_tube_hh = m_z_equator-helper_sep_tube_h/2;
    247 
    248     // TODO: check the UNIT?
    249 
    250     G4VSolid * pInnerSep = new G4Tubs("Inner_Separator",
    251             0.,
    252             helper_sep_tube_r+1E-9*mm,
    253             helper_sep_tube_hh+1E-9*mm,
    254             0.,360.*degree);
    255     G4ThreeVector innerSepDispl(0.,0.,helper_sep_tube_hh-1E-9*mm);
    256     inner1_solid = new G4IntersectionSolid( GetName()
    257             + "_inner1_solid", inner_solid, pInnerSep, NULL, innerSepDispl);
    258     inner2_solid = new G4SubtractionSolid( GetName()
    259             + "_inner2_solid", inner_solid, pInnerSep, NULL, innerSepDispl);




::

    (ok) A[blyth@localhost opticks]$ jcv ellipse_intersect_circle
    2 files to edit
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh
    (ok) A[blyth@localhost junosw]$ 



    (ok) A[blyth@localhost junosw]$ jgr ellipse_intersect_circle
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc://  gcc ellipse_intersect_circle.cc -lm -lstdc++ -o /tmp/ellipse_intersect_circle  && /tmp/ellipse_intersect_circle
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc://  head -1 ellipse_intersect_circle.cc | perl -pe 's,//,,' - | sh
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc:#include "ellipse_intersect_circle.hh"
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh:ellipse_intersect_circle.hh
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh:    ana/ellipse_intersect_circle.hh
    ./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh:    ana/ellipse_intersect_circle.cc
    ./Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc:#include "ellipse_intersect_circle.hh"
    (ok) A[blyth@localhost junosw]$ 


::

    r1t: 101.001 mm
    r4t: 51.1993 mm
    r2t: 22.999 mm
    r3t: 42.501 mm
    h1t: 64.4877 mm
    h2t: 18.0123 mm
    h3t: 62.001 mm
     symbol : pmttube_solid_tube(scarf)
     name   : R12860_PMTSolidU_pmt_solid_2_Tube
     r4t    : 51.1993
     h2t/2  : 9.00616
     symbol  : pmttube_solid_1_2(bulb+neck) 
     name    : R12860_PMTSolidU_pmt_solid_1_2
     neck_dz : -73.4938
     symbol  : pmttube_solid_1_2_3((bulb+neck)+endtube) 
     name    : R12860_PMTSolidU_pmt_solid
     endtube_dz : -113.501


::

                              (51.19,0,9.00616-73.4938)
           +-----------------+
           |                 |
           |        +        | 
           |                 |
           +-----------------+
      (-51.19,0,-9.00616-73.4938)



Scarf dots::

         BBOX=-51.19,0,-82.4999,51.19,0,-64.48764 KLUDGE=1 cxt_min.sh pdb
         BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764 KLUDGE=1 cxt_min.sh pdb
         BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764,51.19,0,-82.4999 KLUDGE=1 cxt_min.sh pdb



torus dots::

     symbol : pmttube_solid_tube(scarf)
     name   : R12860_PMTSolidU_pmt_solid_2_Tube
     r4t    : 51.1993
     h2t/2  : 9.00616
     symbol  : pmttube_solid_torus(scarfSub) 
     name    : R12860_PMTSolidU_pmt_solid_2_Torus
     r2t     : 22.999
     r2t+r3t : 65.5
     symbol  : pmttube_solid_part2 
     name    : R12860_PMTSolidU_pmt_solid_part2
     -h2t/2  : -9.00616(neck-torus-dz)
     symbol  : pmttube_solid_1_2(bulb+neck) 
     name    : R12860_PMTSolidU_pmt_solid_1_2
     neck_dz : -73.4938
     total_torus_dz : -82.5
     symbol  : pmttube_solid_1_2_3((bulb+neck)+endtube) 
     name    : R12860_PMTSolidU_pmt_solid
     endtube_dz : -113.501


scarf dots and torus dots::

     LINE=-65.5,0,-82.5,0,0,0 LINE2=65.5,0,-82.5,0,0,0 POINT=-65.5,0,-82.5,65.5,0,-82.5 BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764,51.19,0,-82.4999   KLUDGE=1 cxt_min.sh pdb

work out the geometry via lines and dots on the simtrace::

     LINE=-65.5,0,-82.5,0,0,0 LINE2=65.5,0,-82.5,0,0,0 POINT=-65.5,0,-82.5,65.5,0,-82.5 BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764,51.19,0,-82.4999   KLUDGE=1 cxt_min.sh pdb
     LINE=-65.5,0,-82.5,0,0,0 LINE2=65.5,0,-82.5,0,0,0 POINT=-65.5,0,-82.5,65.5,0,-82.5 BBOX=-51.19,0,-82.4999,51.19,0,-64.48764,-51.19,0,-64.48764,51.19,0,-82.4999 POINTSIZE=5 KLUDGE=1 cxt_min.sh pdb




