
Shakedown
============


Issue 1 : with CPho label added to NormalTrackInfo get SEGV from NormalTrackInfo::markTracedAncestors looks like uninitialized vector ?
--------------------------------------------------------------------------------------------------------------------------------------------

::

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0xc4c7a718, __p=0x4) at /usr/include/c++/11/ext/new_allocator.h:162
    (gdb) bt
    #0  0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0xc4c7a718, __p=0x4) at /usr/include/c++/11/ext/new_allocator.h:162
    #1  0x00007fffc7ca2594 in std::allocator_traits<std::allocator<int> >::construct<int, int const&> (__a=..., __p=0x4) at /usr/include/c++/11/bits/alloc_traits.h:516
    #2  0x00007fffc7ca182c in std::vector<int, std::allocator<int> >::push_back (this=0xc4c7a718, __x=@0x7ffffffef744: 3) at /usr/include/c++/11/bits/stl_vector.h:1192
    #3  0x00007fffbdf9fa82 in NormalTrackInfo::markTracedAncestors (this=0xc4c7a700, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:63
    #4  0x00007fffbdf9dd35 in InteresingProcessAnaMgr::saveSecondaryInit (this=0x68eb290, aTrack=0xc4c3b260) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:603
    #5  0x00007fffbdf9b53b in InteresingProcessAnaMgr::PreUserTrackingAction (this=0x68eb290, aTrack=0xc4c3b260) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:217
    #6  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa1bb110, trk=0xc4c3b260) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #7  0x00007fffbe784ebf in LSExpTrackingAction::PreUserTrackingAction (this=0xa4d6210, aTrack=0xc4c3b260) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #8  0x00007fffc6730880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x6561cb0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffd485ed3e in DetSimAlg::execute (this=0x678c3c0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #12 0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #16 0x00007fffde30b515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffde30b728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail



::

    (gdb) f 3
    #3  0x00007fffbdf9fa82 in NormalTrackInfo::markTracedAncestors (this=0xc4c7a700, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:63
    63	        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    (gdb) p tracedAncestors
    $1 = std::vector of length -1073741823, capacity -1073741811 = {Cannot access memory at address 0x100000000
    (gdb) 


    (gdb) f 3
    #3  0x00007fffbdf9fa82 in NormalTrackInfo::markTracedAncestors (this=0xc4c7a700, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:63
    63	        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    (gdb) p tracedAncestors
    $1 = std::vector of length -1073741823, capacity -1073741811 = {Cannot access memory at address 0x100000000
    (gdb) p this->originalTrackID
    $2 = 1
    (gdb) p this->originalVertexIDX
    $3 = -993548480
    (gdb) p this->m_flags
    $4 = std::bitset = {[0] = 1, [1] = 1, [3] = 1}
    (gdb) p this->m_op_start_time
    $5 = 4.886219168210935e+45
    (gdb) p this->pos_at_boundary
    $6 = {static ToleranceTicks = 100, data = {3.6070339537748138e-317, 0, 2.4209216646221081e-322}}
    (gdb) p this->m_parent_name
    $7 = {<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >> = "", <No data fields>}
    (gdb) p this->label
    $8 = {static N = 4, gs = 3104, ix = 0, id = 49, uc4 = {x = 0 '\000', y = 0 '\000', z = 0 '\000', w = 0 '\000'}}
    (gdb) 

    (gdb) p *this
    $9 = {<G4VUserTrackInformation> = {<No data fields>}, originalTrackID = 1, tracedAncestors = std::vector of length -1073741823, capacity -1073741811 = {<error reading variable: Cannot access memory at address 0x100000000>
    (gdb) 





::

     66         inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
     67         inline const std::vector<G4int>& getTracedAncestors() const { return tracedAncestors; }



::

    586 void
    587 InteresingProcessAnaMgr::saveSecondaryInit(const G4Track* aTrack) {
    588     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    589     if ((not info)) {
    590         return;
    591     }
    592     // Create SimTrack for the secondaries
    593     if (simtracksvc) {
    594         // NOTE: because pre tracking action could be invoked
    595         //       multiple times for the same track, we need to
    596         //       check whether the sim track already exists or not.
    597         if (simtracksvc->get(aTrack->GetTrackID())) {
    598             return;
    599         }
    600 
    601         // NOTE: The ancestor is used to control whether accumulate the edep
    602         //       to primary track or not.
    603         info->markTracedAncestors(aTrack->GetTrackID());
    604         // info->markTracedAncestors(aTrack->GetParentID());
    605         JM::SimTrack* jm_trk = new JM::SimTrack();


Rebuild
---------

::

    ljb  # local_oj_build
    oj_build

Rerun
-------

::

    tom


Same again::

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0xc4c45348, __p=0x4) at /usr/include/c++/11/ext/new_allocator.h:162
    162		{ ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
    (gdb) bt
    #0  0x00007fffc7ca2ab8 in __gnu_cxx::new_allocator<int>::construct<int, int const&> (this=0xc4c45348, __p=0x4) at /usr/include/c++/11/ext/new_allocator.h:162
    #1  0x00007fffc7ca2594 in std::allocator_traits<std::allocator<int> >::construct<int, int const&> (__a=..., __p=0x4) at /usr/include/c++/11/bits/alloc_traits.h:516
    #2  0x00007fffc7ca182c in std::vector<int, std::allocator<int> >::push_back (this=0xc4c45348, __x=@0x7ffffffef744: 3) at /usr/include/c++/11/bits/stl_vector.h:1192
    #3  0x00007fffbdf9fa82 in NormalTrackInfo::markTracedAncestors (this=0xc4c45330, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:66
    #4  0x00007fffbdf9dd35 in InteresingProcessAnaMgr::saveSecondaryInit (this=0x685edb0, aTrack=0xc4c05690) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:603
    #5  0x00007fffbdf9b53b in InteresingProcessAnaMgr::PreUserTrackingAction (this=0x685edb0, aTrack=0xc4c05690) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:217
    #6  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa17ed10, trk=0xc4c05690) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #7  0x00007fffbe784ebf in LSExpTrackingAction::PreUserTrackingAction (this=0xa499cd0, aTrack=0xc4c05690) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #8  0x00007fffc6730880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x654ae10, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffd485ed3e in DetSimAlg::execute (this=0x65bef40) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #12 0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so


tracedAncestors not init::

    (gdb) f 3
    #3  0x00007fffbdf9fa82 in NormalTrackInfo::markTracedAncestors (this=0xc4c45330, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:66
    66	        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    (gdb) p tracedAncestors
    $1 = std::vector of length -1073741823, capacity -1073741811 = {Cannot access memory at address 0x100000000
    (gdb) p *this
    $2 = {<G4VUserTrackInformation> = {<No data fields>}, originalTrackID = 1, tracedAncestors = std::vector of length -1073741823, capacity -1073741811 = {<error reading variable: Cannot access memory at address 0x100000000>
    (gdb) 


Try removing the G4Allocator usage for NormalTrackInfo 
-----------------------------------------------------------


No difference::

    (gdb) f 3
    #3  0x00007fffbdf9f9ae in NormalTrackInfo::markTracedAncestors (this=0xc4c413f0, trkid=3) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:66
    66	        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    (gdb) p tracedAncestors
    $1 = std::vector of length -1073741823, capacity -1073741811 = {Cannot access memory at address 0x100000000
    (gdb) 


::

    BP=NormalTrackInfo::NormalTrackInfo tom 


    (gdb) bt
    #0  NormalTrackInfo::NormalTrackInfo (this=0x6512610, aTrack=0xc4c014f0) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:27
    #1  0x00007fffbdfc6da0 in NormalAnaMgr::PreUserTrackingAction (this=0x9b39bf0, aTrack=0xc4c014f0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:330
    #2  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa1813f0, trk=0xc4c014f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #3  0x00007fffbe784ebf in LSExpTrackingAction::PreUserTrackingAction (this=0xa49c4f0, aTrack=0xc4c014f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #4  0x00007fffc6730880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x65dae90, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x654ef00) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #8  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


::

    326 void
    327 NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    328 
    329     if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0) {
    330         NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    331         G4Track* theTrack = (G4Track*)aTrack;
    332         theTrack->SetUserInformation(anInfo);
    333     }
    334     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    335 
    336     if (!info) {
    337         return;
    338     }
    339 
    340     // if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()
    341     //     and aTrack->GetCreatorProcess()) {
    342     //     LogDebug << "###+++ "<< aTrack ->GetCreatorProcess()->GetProcessName() <<std::endl; 
    343     // }
    344 
    345     // original OP
    346     // set the info 
    347     if(m_flag_hitinfo) {
    348         if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()
    349             and info->isOriginalOP()
    350             and info->getOriginalOPStartTime() == 0.0) {
    351             // make sure this track info is not changed before.
    352             assert(info->getOriginalOPStartTime() == 0.0);
    353             LogDebug << "------ original OP" << std::endl;
    354             info->setOriginalOPStartTime(aTrack->GetGlobalTime());



SetUserInformation
---------------------

::

    (ok) A[blyth@localhost junosw]$ find . -type f -exec grep -H SetUserInformation {} \;
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        trk_michael->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:                (*secondaries)[i]->SetUserInformation(infoNew);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        (*secondaries)[i]->SetUserInformation(infoNew);
    ./Simulation/DetSimV2/DetSimMT/src/tbbWorkerRunManager.cc:  anEvent->SetUserInformation(m_eui);
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Cerenkov.cc:	  //aSecondaryTrack->SetUserInformation(comp);
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Scintillation.cc:            //aSecondaryTrack->SetUserInformation(comp);
    ./Simulation/DetSimV2/OPSimulator/src/G4OPSimulator.cc:        theTrack->SetUserInformation(aninfo);
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Cerenkov.cc:	  //aSecondaryTrack->SetUserInformation(comp);
    ./Simulation/DetSimV2/PhysiSim/src/DsG4ScintSimple.cc:            //aSecondaryTrack->SetUserInformation(comp);
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:      aSecondaryTrack->SetUserInformation(CPhotonInfo::MakeCerenkov(gs, i));
    grep: ./build/Generator/GenDeex/GenDeexTest/CMakeFiles/GenDeexTest.dir/src/GenDeexTest.cc.o: binary file matches




Try removing the label, back to ordiginal NormalTrackInfo :  perhaps prior problem with build ? 
---------------------------------------------------------------------------------------------------

::

    @@ -16,6 +16,10 @@
     #include "G4Allocator.hh"
     #include "G4ThreeVector.hh"
     
    +//#ifdef WITH_G4CXOPTICKS
    +//#include "C4Pho.h"
    +//#endif
    +
     #include <vector>
     #include "G4ThreeVector.hh"
     
    +//#ifdef WITH_G4CXOPTICKS
    +//#include "C4Pho.h"
    +//#endif
    +
     #include <vector>
     #include <map>
     #include <bitset>
    @@ -47,9 +51,12 @@ class NormalTrackInfo: public G4VUserTrackInformation {
             NormalTrackInfo(const NormalTrackInfo* aTrackInfo);
             virtual ~NormalTrackInfo(); 
     
    -
    +#ifdef WITH_G4CXOPTICKS
    +#else
             inline void *operator new(size_t);
             inline void operator delete(void *aTrackInfo);
    +#endif
    +
             inline int operator ==(const NormalTrackInfo& right) const {
                 return (this==&right);
             }
    @@ -96,6 +103,13 @@ class NormalTrackInfo: public G4VUserTrackInformation {
             inline void setParentName(const G4String& parent_name) { m_parent_name = parent_name; }
             inline const G4String& getParentName() const { return m_parent_name; }
     
    +//#ifdef WITH_G4CXOPTICKS
    +        //inline int*   getLabelData(){    return label.data() ; }
    +//#endif
    +
         private:
             G4int originalTrackID;
             std::vector<G4int> tracedAncestors;
    @@ -121,8 +135,16 @@ class NormalTrackInfo: public G4VUserTrackInformation {
     
             // info of Parent Track
             G4String m_parent_name;
    +



    A[blyth@localhost junosw]$ git diff Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    diff --git a/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc b/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    index 2ea69f56..3bb7e9db 100644
    --- a/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    +++ b/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    @@ -2,8 +2,10 @@
     #include "NormalTrackInfo.hh"
     #include "G4ios.hh"
     
    +#ifdef WITH_G4CXOPTICKS
    +#else
     G4ThreadLocal G4Allocator<NormalTrackInfo>* aNormalTrackInformationAllocator = 0;
    -
    +#endif
     
     
     NormalTrackInfo::NormalTrackInfo()
    @@ -16,6 +18,10 @@ NormalTrackInfo::NormalTrackInfo()
         // phys_decay_mode = 0;
         // from_cerenkov =false;
         // is_reemission =false;
    +//#ifdef WITH_G4CXOPTICKS
    +    tracedAncestors = {} ; 
    +    //label = C4Pho::Placeholder(); 
    +//#endif
     }
     
     NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
    @@ -33,6 +39,11 @@ NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
     
         // m_op_is_original_op = false;
         m_op_start_time = 0;
    +
    +//#ifdef WITH_G4CXOPTICKS
    +    tracedAncestors = {} ; 
    +    //label = C4Pho::Placeholder(); 
    +//#endif
     }
     
     NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
    @@ -54,6 +65,11 @@ NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
         m_op_start_time = aTrackInfo->m_op_start_time;
     
         pos_at_boundary = aTrackInfo->pos_at_boundary;
    +
    +//#ifdef WITH_G4CXOPTICKS
    +    //label = aTrackInfo->label ; 
    +//#endif
    +
     }






NormalTrackInfo where is it set into the track ?
----------------------------------------------------

::

    A[blyth@localhost junosw]$ jgl NormalTrackInfo
    ./Doc/detsim/anaelement.md
    ./Doc/detsim/structures.md
    ./Doc/oum/source/detsim/anaelement.md
    ./Doc/oum/source/detsim/structures.md
    ./Simulation/DetSimV2/AnalysisCode/src/DepEnAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyCalibAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyTTAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyVoxelAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuFastnProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/OPSimAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/PreselAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/RadioAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/SelectNeutronProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    ./Simulation/DetSimV2/OPSimulator/src/G4OPSimulator.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh
    ./Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    A[blyth@localhost junosw]$ 





Try not using WITH_G4CXOPTICKS in NormalTrackInfo and adding initialization for tracedAncestors vector
-------------------------------------------------------------------------------------------------------


