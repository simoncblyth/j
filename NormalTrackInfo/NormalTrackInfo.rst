NormalTrackInfo
====================




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







Thread 1 "python" hit Breakpoint 1.2, NormalTrackInfo::NormalTrackInfo (this=0x6516fb0, aTrack=0xc4dd1050) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:22
22	NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 glibc-2.34-168.el9_6.23.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-11.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libcom_err-1.46.5-7.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libnsl2-2.0.0-1.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 pcre-8.44-4.el9.x86_64
(gdb) bt
#0  NormalTrackInfo::NormalTrackInfo (this=0x6516fb0, aTrack=0xc4dd1050) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:22
#1  0x00007fffbdd71710 in NormalAnaMgr::PreUserTrackingAction (this=0x99ead90, aTrack=0xc4dd1050) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:330
#2  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa2504a0, trk=0xc4dd1050) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
#3  0x00007fffbe1c255d in LSExpTrackingAction::PreUserTrackingAction (this=0xaa63370, aTrack=0xc4dd1050) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
#4  0x00007fffc69b9880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
#5  0x00007fffc69f4565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
#6  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65c3f30, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
#7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x684cae0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
#8  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#9  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#10 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#11 0x00007fffcccd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so




393     size_t nSeco = secondaries->size();
394     if(nSeco==0) {
395         return;
396     }
397     for(size_t i=0;i<nSeco;i++) {
398 
399         // make sure the secondaries' track info is empty
400         // if already attached track info, skip it.
401         if ((*secondaries)[i]->GetUserInformation()) {
402             LogDebug << "The secondary already has user track info. skip creating new one" << std::endl;
403             continue;
404         }
405         NormalTrackInfo* infoNew = new NormalTrackInfo(info);
406 
407 
408         if(m_flag_hitinfo) {
409             // cerekov tag
410             if ((*secondaries)[i]->GetCreatorProcess()
411                 and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
412                 infoNew->setFromCerenkov();
413                 LogDebug << "### infoNew->setFromCerenkov()" << std::endl;
414             }
415             // reemission tag
416             // + parent track is an OP
417             // + secondary is also an OP
418             // + the creator process is Scintillation
419             if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()
420                 and (*secondaries)[i]->GetDefinition() == G4OpticalPhoton::Definition()
421                 and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Scintillation") {
422                 infoNew->setReemission();
423             }
424             // original optical photon tag
425             if (aTrack->GetDefinition() != G4OpticalPhoton::Definition()
426                 and (*secondaries)[i]->GetDefinition() == G4OpticalPhoton::Definition()
427                 ) {
428                 LogDebug << "------ original OP" << std::endl;
429                 infoNew->setOriginalOP();
430             }
431         }
432         // save parent track info
433         infoNew->setParentName(aTrack->GetDefinition()->GetParticleName());
434 
435         (*secondaries)[i]->SetUserInformation(infoNew);
436     }
437 
438 
439 }
440 
441 void
442 NormalAnaMgr::UserSteppingAction(const G4Step* step) {










