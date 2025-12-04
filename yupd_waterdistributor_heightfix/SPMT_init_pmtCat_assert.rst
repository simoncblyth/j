SPMT_init_pmtCat_assert
========================









::

     772 void SPMT::init_pmtCat()
     773 {
     774     bool expected_type  = pmtCat && pmtCat->uifc == 'i' && pmtCat->ebyte == 4 ;
     775     bool expected_shape = pmtCat && pmtCat->shape.size() == 2 && pmtCat->shape[0] == num.ALL && pmtCat->shape[1] == 2 ;
     776 
     777     if(!expected_shape || !expected_type) std::cerr
     778        << "SPMT::init_pmtCat"
     779        << " expected_type " << ( expected_type ? "YES" : "NO " )
     780        << " expected_shape[first-dim-is-num.ALL] " << ( expected_shape ? "YES" : "NO " )
     781        << " pmtCat.shape[0] " << pmtCat->shape[0]
     782        << " num.ALL " << num.ALL
     783        << " pmtCat " << ( pmtCat ? pmtCat->sstr() : "-" )
     784        << " num " << num.desc()
     785        << "\n"
     786        ;
     787 
     788     if(!pmtCat) return ;
     789     assert( expected_type );
     790     assert( expected_shape );
     791     assert( pmtCat_v );
     792 }
     793 
     794 


::

    SPMT::init_pmtNum pmtNum.sstr -
    SPMT::init_pmtCat expected_type YES expected_shape[first-dim-is-num.ALL] NO  pmtCat.shape[0] 45965 num.ALL 0 pmtCat (45965, 2, ) num [SPMT_Num.desc
    m_nums_cd_lpmt     :      0
    m_nums_cd_spmt     :      0
    m_nums_wp_lpmt     :      0
    m_nums_wp_atm_lpmt :      0
    m_nums_wp_wal_pmt  :      0
    m_nums_wp_atm_mpmt :      0
    ALL                :      0
    SUM                :      0
    SUM==ALL           :    YES
    ]SPMT_Num.desc









s_bb::IncludeAABB 
 inital_aabb  [-1219.998,-246.607,-20273.000,1219.998,246.607,-18603.000]
 other_aabb   [797.408,-185.574,-18224.473,873.866,-109.116,-17754.473]COMBINE
 updated_aabb [-1219.998,-246.607,-20273.000,1219.998,246.607,-17754.473]
s_bb::IncludeAABB 
 inital_aabb  [-1219.998,-246.607,-20273.000,1219.998,246.607,-17754.473]
 other_aabb   [-38.229,-38.229,-17873.000, 38.229, 38.229,-17403.000]COMBINE
 updated_aabb [-1219.998,-246.607,-20273.000,1219.998,246.607,-17403.000]
s_bb::IncludeAABB 
 inital_aabb  [-1219.998,-246.607,-20273.000,1219.998,246.607,-17403.000]
 other_aabb   [-873.866,109.116,-18224.473,-797.408,185.574,-17754.473]COMBINE
 updated_aabb [-1219.998,-246.607,-20273.000,1219.998,246.607,-17403.000]

]CSGImport::importPrim.dump_LVID:1 node.lvid 124 LVID -1 name Waterdistributor_2 soname Waterdistributor_2
2025-12-01 12:08:49.373 INFO  [2752590] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
SPMT::init_pmtNum pmtNum.sstr -
SPMT::init_pmtCat expected_type YES expected_shape[first-dim-is-num.ALL] NO  pmtCat.shape[0] 45965 num.ALL 0 pmtCat (45965, 2, ) num [SPMT_Num.desc
m_nums_cd_lpmt     :      0
m_nums_cd_spmt     :      0
m_nums_wp_lpmt     :      0
m_nums_wp_atm_lpmt :      0
m_nums_wp_wal_pmt  :      0
m_nums_wp_atm_mpmt :      0
ALL                :      0
SUM                :      0
SUM==ALL           :    YES
]SPMT_Num.desc

python: /home/blyth/opticks/sysrap/SPMT.h:790: void SPMT::init_pmtCat(): Assertion `expected_shape' failed.
 *** Break *** abort



===========================================================
There was a crash.
This is the entire stack trace of all threads:
===========================================================

Thread 5 (Thread 0x7fd3013fe640 (LWP 2752642) "cuda-EvtHandlr"):
#0  0x00007fd343d0200f in poll () from /lib64/libc.so.6
#1  0x00007fd301f1cb37 in ?? () from /lib64/libcuda.so.1
#2  0x00007fd30200bd77 in ?? () from /lib64/libcuda.so.1
#3  0x00007fd301f08883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fd343c8a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fd343d0f240 in clone3 () from /lib64/libc.so.6

Thread 4 (Thread 0x7fd301bff640 (LWP 2752641) "python"):
#0  0x00007fd343c8722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
#1  0x00007fd343c8996f in pthread_cond_timedwait

GLIBC_2.3.2 () from /lib64/libc.so.6
#2  0x00007fd301e69b5a in ?? () from /lib64/libcuda.so.1
#3  0x00007fd301f08883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fd343c8a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fd343d0f240 in clone3 () from /lib64/libc.so.6

Thread 3 (Thread 0x7fd309731640 (LWP 2752613) "cuda00001c00008"):
#0  0x00007fd343d0200f in poll () from /lib64/libc.so.6
#1  0x00007fd301f1cb37 in ?? () from /lib64/libcuda.so.1
#2  0x00007fd30200bd77 in ?? () from /lib64/libcuda.so.1
#3  0x00007fd301f08883 in ?? () from /lib64/libcuda.so.1
#4  0x00007fd343c8a19a in start_thread () from /lib64/libc.so.6
#5  0x00007fd343d0f240 in clone3 () from /lib64/libc.so.6

Thread 2 (Thread 0x7fd319bff640 (LWP 2752603) "python"):
#0  0x00007fd343c8722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
#1  0x00007fd343c8996f in pthread_cond_timedwait

GLIBC_2.3.2 () from /lib64/libc.so.6
#2  0x00007fd34424df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7fd344550f38 <_PyRuntime+440>, cond=0x7fd344550f08 <_PyRuntime+392>) at Python/condvar.h:73
#3  take_gil (tstate=tstate
entry=0x7882260) at Python/ceval_gil.h:231
#4  0x00007fd34424e43e in PyEval_RestoreThread (tstate=tstate
entry=0x7882260) at Python/ceval.c:521
#5  0x00007fd344315894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
#6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
#7  0x00007fd3441a88f2 in cfunction_vectorcall_O (func=0x7fd343fb77e0, args=0x7fd343e791e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
#8  0x00007fd34415a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7fd343fb77e0, tstate=0x7882260) at ./Include/internal/pycore_call.h:92
#9  PyObject_Vectorcall (callable=0x7fd343fb77e0, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
#10 0x00007fd3440fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
#11 0x00007fd34424f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7fd343e79188, tstate=0x7882260) at ./Include/internal/pycore_ceval.h:73
#12 _PyEval_Vector (tstate=0x7882260, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
#13 0x00007fd344101e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7fd3363ded40, callargs=0x7fd3363eeb00, func=0x7fd336377920, tstate=0x7882260) at Python/ceval.c:7349
#14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
#15 0x00007fd34424f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7fd343e79020, tstate=0x7882260) at ./Include/internal/pycore_ceval.h:73
#16 _PyEval_Vector (tstate=0x7882260, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
#17 0x00007fd34415cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7fd319bfeda8, callable=0x7fd336346d40, tstate=0x7882260) at ./Include/internal/pycore_call.h:92
#18 method_vectorcall (method=<optimized out>, args=0x7fd34455f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
#19 0x00007fd344313fe2 in thread_run (boot_raw=0x78aa2b0) at ./Modules/_threadmodule.c:1124
#20 0x00007fd3442a87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
#21 0x00007fd343c8a19a in start_thread () from /lib64/libc.so.6
#22 0x00007fd343d0f240 in clone3 () from /lib64/libc.so.6

Thread 1 (Thread 0x7fd3445ce740 (LWP 2752590) "python"):
#0  0x00007fd343cd8fff in wait4 () from /lib64/libc.so.6
#1  0x00007fd343c4b7e3 in do_system () from /lib64/libc.so.6
#2  0x00007fd335ef6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
#3  0x00007fd343e4c0f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
#4  0x00007fd335ef4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
#5  <signal handler called>
#6  0x00007fd343c8bedc in __pthread_kill_implementation () from /lib64/libc.so.6
#7  0x00007fd343c3eb46 in raise () from /lib64/libc.so.6
#8  0x00007fd343c28833 in abort () from /lib64/libc.so.6
#9  0x00007fd343c2875b in __assert_fail_base.cold () from /lib64/libc.so.6
#10 0x00007fd343c37886 in __assert_fail () from /lib64/libc.so.6
#11 0x00007fd30aa0f454 in SPMT::init_pmtCat (this=0x3823e960) at /home/blyth/opticks/sysrap/SPMT.h:790
#12 0x00007fd30aa39f96 in SPMT::init (this=0x3823e960) at /home/blyth/opticks/sysrap/SPMT.h:536
#13 0x00007fd30aa39e83 in SPMT::SPMT (this=0x3823e960, jpmt_=0x38270ec0) at /home/blyth/opticks/sysrap/SPMT.h:495
#14 0x00007fd30aa12145 in SSim::get_spmt (this=0xe4d21c0) at /home/blyth/opticks/sysrap/SSim.cc:383
#15 0x00007fd30aa122da in SSim::get_spmt_f (this=0xe4d21c0) at /home/blyth/opticks/sysrap/SSim.cc:407
#16 0x00007fd30b26f76f in QSim::UploadComponents (ssim=0xe4d21c0) at /home/blyth/opticks/qudarap/QSim.cc:199
#17 0x00007fd30d2e9ad4 in CSGOptiX::InitSim (ssim=0xe4d21c0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:276
#18 0x00007fd30d2ea124 in CSGOptiX::Create (fd=0x28eac9d0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:353
#19 0x00007fd30d66e10c in G4CXOpticks::CreateSimulator (fd=0x28eac9d0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:419
#20 0x00007fd30d66dba8 in G4CXOpticks::setGeometry_ (this=0xe5f22b0, fd_=0x28eac9d0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:380
#21 0x00007fd30d66d9a1 in G4CXOpticks::setGeometry (this=0xe5f22b0, fd_=0x28eac9d0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:347
#22 0x00007fd30d66d5ab in G4CXOpticks::setGeometry (this=0xe5f22b0, world=0xc527d20) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:320
#23 0x00007fd30d66baa1 in G4CXOpticks::SetGeometry (world=0xc527d20) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:79
#24 0x00007fd30d66bd50 in G4CXOpticks::SetGeometry_JUNO (world=0xc527d20, sd=0x85c5040, jpmt=0xe49efd0, jlut=0xe4d15a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:117
#25 0x00007fd309f9622c in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xc527d20, sd=0x85c5040, ppd=0x8599510, psd=0x859b1c0, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
#26 0x00007fd309f5a386 in LSExpDetectorConstruction::setupOpticks (this=0xc14f950, world=0xc527d20) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
#27 0x00007fd309f59c26 in LSExpDetectorConstruction::Construct (this=0xc14f950) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
#28 0x00007fd3133f492e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
#29 0x00007fd3133f4afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
#30 0x00007fd31c5e6b1b in DetSimAlg::initialize (this=0x85c7380) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
#31 0x00007fd321337b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#32 0x00007fd32134d09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#33 0x00007fd321355447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#34 0x00007fd32134d048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#35 0x00007fd31a3d48d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
#36 0x00007fd320e5a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#37 0x00007fd320e5a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#38 0x00007fd320e5f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#39 0x00007fd320e58182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#40 0x00007fd344159cc3 in _PyObject_MakeTpCall (tstate=0x7fd344579738 <_PyRuntime+166328>, callable=0x7f21a80, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
#41 0x00007fd3440fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
#42 0x00007fd34424f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7fd3446b8020, tstate=0x7fd344579738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
#43 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7fd336541040, func=0x7fd343f989a0, tstate=0x7fd344579738 <_PyRuntime+166328>) at Python/ceval.c:6434
#44 PyEval_EvalCode (co=co
entry=0x2423d40, globals=globals
entry=0x7fd336541040, locals=locals
entry=0x7fd336541040) at Python/ceval.c:1148
#45 0x00007fd3442980ed in run_eval_code_obj (locals=0x7fd336541040, globals=0x7fd336541040, co=0x2423d40, tstate=0x7fd344579738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
#46 run_mod (mod=<optimized out>, filename=filename
entry=0x7fd343f2f280, globals=globals
entry=0x7fd336541040, locals=locals
entry=0x7fd336541040, flags=flags
entry=0x7ffc777441d8, arena=arena


