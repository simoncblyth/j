opticksMode_0_has_TrackInfo_dtor_runtime_issue
================================================


::

    iunotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2025-11-24 19:34:45.622 [junoSD_PMT_v2::Initialize eventID 0
    2025-11-24 19:34:45.623 ]junoSD_PMT_v2::Initialize eventID 0
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

    Thread 3 (Thread 0x7f82541ff640 (LWP 3380612) "cuda00001c00008"):
    #0  0x00007f828e70200f in poll () from /lib64/libc.so.6
    #1  0x00007f8248f1cb37 in ?? () from /lib64/libcuda.so.1
    #2  0x00007f824900bd77 in ?? () from /lib64/libcuda.so.1
    #3  0x00007f8248f08883 in ?? () from /lib64/libcuda.so.1
    #4  0x00007f828e68a19a in start_thread () from /lib64/libc.so.6
    #5  0x00007f828e70f240 in clone3 () from /lib64/libc.so.6

    Thread 2 (Thread 0x7f82645ff640 (LWP 3380603) "python"):
    #0  0x00007f828e68722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f828e68996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f828ec4df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f828ef50f38 <_PyRuntime+440>, cond=0x7f828ef50f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x74a3ec0) at Python/ceval_gil.h:231
    #4  0x00007f828ec4e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x74a3ec0) at Python/ceval.c:521
    #5  0x00007f828ed15894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f828eba88f2 in cfunction_vectorcall_O (func=0x7f828e9a79c0, args=0x7f828e8791e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f828eb5a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f828e9a79c0, tstate=0x74a3ec0) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f828e9a79c0, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f828eafe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f828ec4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f828e879188, tstate=0x74a3ec0) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x74a3ec0, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f828eb01e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f8280de32c0, callargs=0x7f8280deebf0, func=0x7f8280d774c0, tstate=0x74a3ec0) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f828ec4f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f828e879020, tstate=0x74a3ec0) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x74a3ec0, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f828eb5cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f82645feda8, callable=0x7f8280efa8e0, tstate=0x74a3ec0) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f828ef5f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f828ed13fe2 in thread_run (boot_raw=0x749eea0) at ./Modules/_threadmodule.c:1124
    #20 0x00007f828eca87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f828e68a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f828e70f240 in clone3 () from /lib64/libc.so.6

    Thread 1 (Thread 0x7f828efc04c0 (LWP 3380567) "python"):
    #0  0x00007f828e6d8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f828e64b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f82808f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f828e84c0f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f82808f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f828e69a28e in free () from /lib64/libc.so.6
    #7  0x00007f8262d7ca81 in __gnu_cxx::new_allocator<int>::deallocate (this=0xc6957aa8, __p=0x1030000000000, __t=18446672880331653120) at /usr/include/c++/11/ext/new_allocator.h:145
    #8  0x00007f8262d7bd26 in std::allocator_traits<std::allocator<int> >::deallocate (__a=..., __p=0x1030000000000, __n=18446672880331653120) at /usr/include/c++/11/bits/alloc_traits.h:496
    #9  0x00007f8262d7a7e8 in std::_Vector_base<int, std::allocator<int> >::_M_deallocate (this=0xc6957aa8, __p=0x1030000000000, __n=18446672880331653120) at /usr/include/c++/11/bits/stl_vector.h:354
    #10 0x00007f8262d7b79e in std::_Vector_base<int, std::allocator<int> >::~_Vector_base (this=0xc6957aa8, __in_chrg=<optimized out>) at /usr/include/c++/11/bits/stl_vector.h:335
    #11 0x00007f8262d7b893 in std::vector<int, std::allocator<int> >::~vector (this=0xc6957aa8, __in_chrg=<optimized out>) at /usr/include/c++/11/bits/stl_vector.h:683
    #12 0x00007f82625aad14 in NormalTrackInfo::~NormalTrackInfo (this=0xc6957a90, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:59
    #13 0x00007f82625aad3c in NormalTrackInfo::~NormalTrackInfo (this=0xc6957a90, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:59
    #14 0x00007f82617702fa in G4Track::~G4Track() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4track.so
    #15 0x00007f82617f4795 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #16 0x00007f827a34768e in G4SvcRunManager::SimulateEvent (this=0x811d870, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #17 0x00007f8266fe6d3e in DetSimAlg::execute (this=0x811dc70) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #18 0x00007f826bd4d4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #19 0x00007f826bd51bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #20 0x00007f826bd4d054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007f8264dd48d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #22 0x00007f826b85a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #23 0x00007f826b85a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #24 0x00007f826b85f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85









Thank you for the code — now it's 100% clear what’s happening.

### Root Cause

You have **two `std::vector<G4int>` members** in `NormalTrackInfo`:

```cpp
std::vector<G4int> tracedAncestors;      // ← this one gets corrupted
```

and in the destructor line 59 you wrote:

```cpp
NormalTrackInfo::~NormalTrackInfo(){;}    // ← EMPTY DESTRUCTOR
```

But you **overrode `operator new` and `operator delete`** to use Geant4's `G4Allocator<NormalTrackInfo>`.

That is the **fatal combination**.

### Why this crashes exactly the way you see

- Geant4 creates thousands of `NormalTrackInfo` objects using your custom `operator new` → they go into the `G4Allocator` pool.
- When the track is deleted, Geant4 calls `operator delete` on the pointer → your `operator delete` runs → calls `G4Allocator::FreeSingle()`.
- But because you have a non-trivial member (`std::vector<G4int> tracedAncestors`), the compiler generates a destructor that destroys the vector.
- **Your empty destructor replaces the compiler-generated one**, so the vector is **never destroyed** → its internal pointers (data, size, capacity) are **never cleaned up**.
- Later, when the `G4Allocator` reuses that memory page for a new object (or anything else), the old vector bookkeeping still sits there.
- Eventually some `NormalTrackInfo` gets a memory chunk where the `tracedAncestors` vector’s size/capacity was overwritten with whatever garbage was written into that recycled memory → you see `size = 18446672880331653120` → boom in `~vector()` → `free()` → segfault.

This is an extremely common and insidious bug when people copy-paste the old Geant4 "UserInformation + G4Allocator" pattern without realizing that **as soon as you have any non-trivial member (like `std::vector`, `std::string`, etc.), you can no longer have an empty/user-defined destructor**.

### The fix (two choices)

#### Option 1 – Recommended (modern, clean, zero overhead)

**Remove the custom allocator entirely.**  
`G4Allocator` gives almost no benefit nowadays and causes endless headaches exactly like this.

Do this:

```cpp
// NormalTrackInfo.h
// DELETE these lines completely:
// inline void* operator new(size_t);
// inline void operator delete(void*);
// and the extern G4ThreadLocal G4Allocator<NormalTrackInfo>* aNormalTrackInformationAllocator;

// In NormalTrackInfo.cc, delete the entire operator new/delete implementation
// and delete the global/static allocator variable.
```

And just let it use normal `new`/`delete`. Performance difference is negligible, and you avoid all these bugs forever.

#### Option 2 – Keep G4Allocator (if you really want to)

Then you **must** let the compiler generate the destructor and call the vector’s destructor properly:

```cpp
// In the header, remove the user-defined destructor declaration entirely
// (or declare it = default)

// In the .cc file:
NormalTrackInfo::~NormalTrackInfo() = default;   // ← this is the key
```

Or at minimum:

```cpp
NormalTrackInfo::~NormalTrackInfo()
{
    // explicitly destroy the vector (only needed if you keep empty body)
    tracedAncestors.~vector<G4int>();
}
```

But again, **Option 1 is strongly preferred**.

### Bonus: your copy constructor is also broken

You have:

```cpp
tracedAncestors = aTrackInfo->tracedAncestors;
```

That’s fine, but you didn’t define a copy assignment operator, and you have other members (`m_parent_name`, etc.). Sooner or later you’ll hit the Rule of Three/Five.

Either:
- delete copy ctor and assignment (most Geant4 user info objects are not copied), or
- properly implement them, or
- `= default` them.

### TL;DR – Immediate fix

Delete these lines entirely (or comment them out):

```cpp
// Remove custom new/delete
inline void* NormalTrackInfo::operator new(size_t) { ... }
inline void NormalTrackInfo::operator delete(void *aTrackInfo) { ... }

// Remove the global allocator
extern G4ThreadLocal G4Allocator<NormalTrackInfo>* aNormalTrackInformationAllocator;
G4ThreadLocal G4Allocator<NormalTrackInfo>* aNormalTrackInformationAllocator = nullptr;
```

And change the destructor to:

```cpp
NormalTrackInfo::~NormalTrackInfo() = default;
```

Recompile, and your crash will vanish instantly.

This bug has bitten literally hundreds of Geant4 users over the last 15 years. You’re in good company. Welcome to the club!



