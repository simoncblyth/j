muon_gun_eventID_4_crash_investigation
========================================


::

    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 1 hitCollection 5394 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-06-18 01:58:49.627954000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-06-18 01:58:49.631968000Z
    end of event action 
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (4) 
    junoSD_PMT_v2::Initialize eventID 4
    Begin of Event --> 4
     *** Break *** segmentation violation


    The lines below might hint at the cause of the crash. If you see question
    marks as part of the stack trace, try to recompile with debugging information
    enabled and export CLING_DEBUG=1 environment variable before running.
    You may get help by asking at the ROOT forum https://root.cern/forum
    preferably using the command (.forum bug) in the ROOT prompt.
    Only if you are really convinced it is a bug in ROOT then please submit a
    report at https://root.cern/bugs or (preferably) using the command (.gh bug) in
    the ROOT prompt. Please post the ENTIRE stack trace
    from above as an attachment in addition to anything else
    that might help us fixing this issue.
    ===========================================================
    #6  0x00007f120152e0e2 in DepositEnergyAnaMgr::UserSteppingAction (this=0x70120d0, step=0x6e206e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc:168
    #7  0x00007f1213dc2062 in MgrOfAnaElem::UserSteppingAction (this=0xa81c830, step=0x6e206e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:74
    #8  0x00007f1200dc6963 in LSExpSteppingAction::UserSteppingAction (this=0xab38750, fStep=0x6e206e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpSteppingAction.cc:56
    #9  0x00007f120d725235 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007f120d73070f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #11 0x00007f120d76b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #12 0x00007f122338468e in G4SvcRunManager::SimulateEvent (this=0x6c25470, i_event=4) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #13 0x00007f1213db6d3e in DetSimAlg::execute (this=0x6c6f020) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #14 0x00007f121b3e64b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007f121b3eabbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007f121b3e6054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007f120fbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #18 0x00007f122222a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007f122222a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007f122222f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #21 0x00007f1222228182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #22 0x00007f123a959cc3 in _PyObject_MakeTpCall (tstate=0x7f123ad79738 <_PyRuntime+166328>, callable=0x667c060, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #23 0x00007f123a8fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #24 0x00007f123aa4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f123af8f020, tstate=0x7f123ad79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #25 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f122cd41680, func=0x7f122cd46020, tstate=0x7f123ad79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #26 PyEval_EvalCode (co=co
    ...
    **************************************************
    Terminating @ localhost.localdomain on Wed Jun 18 09:59:46 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    A[blyth@localhost muon]$ 



::

    107 DepositEnergyAnaMgr::UserSteppingAction(const G4Step* step) {
    108     if (not simtracksvc) {
    109         return;
    110     }
    111 
    ...
    160     const std::vector<G4int>& ancestors = trackinfo->getTracedAncestors();
    161     // std::cout << "current track: " << track->GetTrackID() << std::endl;
    162     // for (auto trkid: ancestors) { // in the previous implementation, accumulate all
    163     //     std::cout << " -> " << trkid << std::endl;
    164     // }
    165     int trkid = -1;
    166     if (ancestors.size()) {
    167         // only get the last ancestor
    168         trkid = ancestors.back();
    169     } else if (prmtrkid) {
    170         // if no ancestors, maybe a primary track
    171         trkid = prmtrkid;
    172     } else {
    173         // other cases...
    174         LogError << "trkid is not assigned. "
    175                  << " ancestors.size(): " << ancestors.size()
    176                  << " prmtrkid: " << prmtrkid
    177                  << " current position: " << pos
    178                  << " edep: " << edep
    179                  << std::endl;
    180     }



Running with "--no-anamgr-deposit" gives another error from RootFileWriter::close::

    Begin of Event --> 4
    junotoptask.execute            ERROR: std::bad_array_new_length
    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-18 10:27:05,151] p2024503 {/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
     *** Break *** segmentation violation

    ...

    #7  0x00007f688ae70eae in RootFileWriter::close (this=0x54bcfb0) at /builds/JUNO/offline/junosw/RootIO/RootIOUtil/src/RootFileWriter.cc:274
    #8  0x00007f688aec8761 in RootOutputStream::close (this=0x54bcf50) at /builds/JUNO/offline/junosw/RootIO/RootIOSvc/src/RootOutputStream.cc:50
    #9  0x00007f688aec9597 in RootOutputSvc::finalize (this=0x7090cf0) at /builds/JUNO/offline/junosw/RootIO/RootIOSvc/src/RootOutputSvc.cc:62
    #10 0x00007f68a1fd0d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007f68a1fe5d7a in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007f68a1fe9611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007f68a1fe9bb8 in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f68a1fe6f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007f68a1fe7049 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007f68a1fd1513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007f68a1fd16aa in DleSupervisor::~DleSupervisor() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007f68a1fed6c2 in TopTask::~TopTask() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


        270 bool RootFileWriter::close()
        271 {
        272     if (!m_initialized) return true;
        273     // Reset current directory
        274     m_dir->cd();
        ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        275     // Write trees and lazy-loading data
        276     m_headerTree->write();
        277     m_headerTree->writeUID(m_file);
        278     String2TreeHandle::iterator it, end = m_eventTrees.end();
        279     for (it = m_eventTrees.begin(); it != end; ++it) {
        280         it->second->write();
        281         it->second->writeUID(m_file);
        282         JM::TreeMetaData* md = it->second->getTreeMetaData();
        283         if (md) {
        284             m_treeMetaDatas.push_back(md);
        285         }
        286         delete it->second;
        287     }



Suspect the RootFileWriter::close error came later, at cleanup : original issue was from "std::bad_array_new_length"


added "catch throw" to "dbg__" reveals the "std::bad_array_new_length" exception comes from NormalTrackInfo::NormalTrackInfo NormalAnaMgr::PostUserTrackingAction
-------------------------------------------------------------------------------------------------------------------------------------------------------------------


::

    2025-06-18 13:42:29.637 INFO  [2035546] [U4::GenPhotonAncestor@325] C4Pho (gs:ix:id:gn   1 288    0[  0,  0,  0,  0])
    2025-06-18 13:42:29.637 INFO  [2035546] [U4::CollectGenstep_G4Cerenkov_modified@291] C4GS: idx26396 pho   184 off 6353695 typ   18
    2025-06-18 13:42:29.637 INFO  [2035546] [U4::GenPhotonAncestor@325] C4Pho (gs:ix:id:gn   1 277    0[  0,  0,  0,  0])
    2025-06-18 13:42:29.637 INFO  [2035546] [U4::GenPhotonAncestor@325] C4Pho (gs:ix:id:gn   1 277    0[  0,  0,  0,  0])

    Thread 1 "python" hit Catchpoint 1 (exception thrown), 0x00007fffe92ad7c2 in __cxa_throw () from /lib64/libstdc++.so.6

    (gdb) bt
    #0  0x00007fffe92ad7c2 in __cxa_throw () from /lib64/libstdc++.so.6
    #1  0x00007fffe92a4328 in std::__throw_bad_array_new_length() () from /lib64/libstdc++.so.6
    #2  0x00007fffc7c99a2b in __gnu_cxx::new_allocator<int>::allocate (this=0xc52bed48, __n=18446250942744494080) at /usr/include/c++/11/ext/new_allocator.h:116
    #3  0x00007fffc7c98cae in std::allocator_traits<std::allocator<int> >::allocate (__a=..., __n=18446250942744494080) at /usr/include/c++/11/bits/alloc_traits.h:464
    #4  0x00007fffc7c97730 in std::_Vector_base<int, std::allocator<int> >::_M_allocate (this=0xc52bed48, __n=18446250942744494080) at /usr/include/c++/11/bits/stl_vector.h:346
 
    #5  0x00007fffc7c9aa6a in std::vector<int, std::allocator<int> >::_M_allocate_and_copy<__gnu_cxx::__normal_iterator<int const*, std::vector<int, std::allocator<int> > > > (this=0xc52bed48, 
        __n=18446250942744494080, __first=<error reading variable: Cannot access memory at address 0x7020000000000>, __last=non-dereferenceable iterator for std::vector)
        at /usr/include/c++/11/bits/stl_vector.h:1511
    #6  0x00007fffc7c9a0c2 in std::vector<int, std::allocator<int> >::operator= (this=0xc52bed48, __x=std::vector of length -493130965057536, capacity -493130965057536 = {...})
        at /usr/include/c++/11/bits/vector.tcc:226
 

     38 NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
     39 {
     40     originalTrackID = aTrackInfo->originalTrackID;
     41     tracedAncestors = aTrackInfo->tracedAncestors;
            ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


    #7  0x00007fffc7470404 in NormalTrackInfo::NormalTrackInfo (this=0xc52bed30, aTrackInfo=0xc52c0f30) at /home/blyth/junosw/Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:41




    #8  0x00007fffbd976556 in NormalAnaMgr::PostUserTrackingAction (this=0x9b38b10, aTrack=0xc5177cd0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:405
    #9  0x00007fffd4869efa in MgrOfAnaElem::PostUserTrackingAction (this=0xa17eb60, trk=0xc5177cd0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:67
    #10 0x00007fffbddc6b71 in LSExpTrackingAction::PostUserTrackingAction (this=0xa49a2d0, aTrack=0xc5177cd0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:48
    #11 0x00007fffc6730a70 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #12 0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x66bb0e0, i_event=4) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x00007fffd485ed3e in DetSimAlg::execute (this=0x661f6d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #19 0x00007fffde30b515 in boost::python::objects::function::call(_object*, _object*) const ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007fffde30b728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #21 0x00007fffde310443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #22 0x00007fffde309182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #23 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fe9260, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #24 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #25 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #26 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e5480, func=0x7ffff7e649a0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #27 PyEval_EvalCode (co=co@entry=0x4cf2c0, globals=globals@entry=0x7ffff76e5480, locals=locals@entry=0x7ffff76e5480) at Python/ceval.c:1148
    #28 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e5480, globals=0x7ffff76e5480, co=0x4cf2c0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #29 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7dfb0c0, globals=globals@entry=0x7ffff76e5480, locals=locals@entry=0x7ffff76e5480, flags=flags@entry=0x7fffffff0148, 
        arena=arena@entry=0x7ffff7de6b70) at Python/pythonrun.c:1762
    #30 0x00007ffff7a998ab in pyrun_file (flags=0x7fffffff0148, closeit=<optimized out>, locals=0x7ffff76e5480, globals=0x7ffff76e5480, start=257, filename=0x7ffff7dfb0c0, fp=0x409140) at Python/pythonrun.c:1657
    #31 _PyRun_SimpleFileObject (fp=fp@entry=0x409140, filename=filename@entry=0x7ffff7dfb0c0, closeit=closeit@entry=1, flags=flags@entry=0x7fffffff0148) at Python/pythonrun.c:440
    #32 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x409140, filename=filename@entry=0x7ffff7dfb0c0, closeit=closeit@entry=1, flags=flags@entry=0x7fffffff0148) at Python/pythonrun.c:79
    #33 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7dfb0c0, program_name=0x7ffff7e2a550) at Modules/main.c:360
    #34 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #35 pymain_run_python (exitcode=0x7fffffff0144) at Modules/main.c:605
    #36 Py_RunMain () at Modules/main.c:684
    #37 0x00007ffff7ab95b7 in pymain_main (args=0x7fffffff0250) at Modules/main.c:714
    #38 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #39 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #40 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #41 0x0000000000401075 in _start ()
    (gdb) 


    369 void
    370 NormalAnaMgr::PostUserTrackingAction(const G4Track* aTrack) {
    371 
    372     if (aTrack->GetParentID() == 0) {
    373         // this is the primary particle
    374         const G4ThreeVector& pos = aTrack->GetPosition();
    375         LogDebug << "!!!Primary Track " << aTrack->GetTrackID() << ": ";
    376         LogDebug << "+ " << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
    377         LogDebug << "+ " << aTrack->GetKineticEnergy() << std::endl;
    378     }
    379     G4TrackingManager* tm = G4EventManager::GetEventManager()
    380         -> GetTrackingManager();
    381     G4TrackVector* secondaries = tm->GimmeSecondaries();
    382     // if there is no secondaries, do nothing.
    383     if(not secondaries) {
    384         return;
    385     }
    386 
    387     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ no dynamic_cast

    388 
    389     if (!info) {
    390         return;
    391     }
    392 
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


    (gdb) p nSeco
    $4 = 13
    (gdb) p aTrack
    $5 = (const G4Track *) 0xc5177cd0
    (gdb) p aTrack->GetUserInformation()
    $6 = (G4VUserTrackInformation *) 0xc52c0f30
    (gdb) p dynamic_cast<NormalTrackInfo>(aTrack->GetUserInformation())
    Argument to dynamic_cast must be a pointer or reference type
    (gdb) p dynamic_cast<NormalTrackInfo*>(aTrack->GetUserInformation())
    Couldn't determine value's most derived type for dynamic_cast
    (gdb) 

    (gdb) p *aTrack
    $11 = {fCurrentStepNumber = 39, fPosition = {static ToleranceTicks = 100, data = {-243.90845851000202, 4618.8544944555561, 18874.811021540885}}, fGlobalTime = 21.880630419729776, 
      fLocalTime = 4.7303101436689046, fTrackLength = 1418.1113050728338, fParentID = 582, fTrackID = 13216, fVelocity = 299.79245800000001, fpTouchable = {fObj = 0xc50b7a00}, fpNextTouchable = {
        fObj = 0xc50b7a00}, fpOriginTouchable = {fObj = 0xc50b7a80}, fpDynamicParticle = 0xc5177568, fTrackStatus = fStopAndKill, fBelowThreshold = false, fGoodForTracking = false, 
      fStepLength = 3.2680454779791548, fWeight = 1, fpStep = 0x695cac0, fVtxPosition = {static ToleranceTicks = 100, data = {29.909447838033127, 5070.828980938626, 19283.495795975603}}, fVtxMomentumDirection = {
        static ToleranceTicks = 100, data = {0.072316927184717342, -0.20229507271415115, -0.97665089238588043}}, fVtxKineticEnergy = 3.8053770779117686, fpLVAtVertex = 0xa57f0f0, fpCreatorProcess = 0x2f16e300, 
      fCreatorModelIndex = 24, fpUserInformation = 0xc52c0f30, prev_mat = 0x0, groupvel = 0x0, prev_velocity = 0, prev_momentum = 0, is_OpticalPhoton = false, useGivenVelocity = false, 
      fpAuxiliaryTrackInformationMap = 0x0}



::

    gdb) f 8
    #8  0x00007fffbd976556 in NormalAnaMgr::PostUserTrackingAction (this=0x9b38b10, aTrack=0xc5177cd0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:405
    405	        NormalTrackInfo* infoNew = new NormalTrackInfo(info);
    (gdb) list
    400	        // if already attached track info, skip it.
    401	        if ((*secondaries)[i]->GetUserInformation()) {
    402	            LogDebug << "The secondary already has user track info. skip creating new one" << std::endl;
    403	            continue;
    404	        }
    405	        NormalTrackInfo* infoNew = new NormalTrackInfo(info);
    406	        
    407	
    408	        if(m_flag_hitinfo) {
    409	            // cerekov tag
    (gdb) p i
    $1 = 0
    (gdb) p info
    $2 = (NormalTrackInfo *) 0xc52c0f30
    (gdb) p *info
    $3 = {<G4VUserTrackInformation> = {<No data fields>}, originalTrackID = 1, tracedAncestors = std::vector of length -493130965057536, capacity -493130965057536 = {
        <error reading variable: Cannot access memory at address 0x7020000000000>
    (gdb) 



Issue looks like dud UserTrackInformation
-------------------------------------------

::

    A[blyth@localhost j]$ BP=G4Track::SetUserInformation muon/muon_gun.sh


Where set ?
--------------

::

    (gdb) bt
    #0  0x00007fffbd906680 in G4Track::SetUserInformation(G4VUserTrackInformation*) const@plt () from /home/blyth/junosw/InstallArea/lib64/libAnalysisCode.so
    #1  0x00007fffbd975ed7 in NormalAnaMgr::PreUserTrackingAction (this=0x687d8f0, aTrack=0xc50b53b0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:332
    #2  0x00007fffd4869d92 in MgrOfAnaElem::PreUserTrackingAction (this=0xa15a060, trk=0xc50b53b0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #3  0x00007fffbddc6b47 in LSExpTrackingAction::PreUserTrackingAction (this=0xa497ee0, aTrack=0xc50b53b0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #4  0x00007fffc6730880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x65c6650, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x65d36f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #8  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihe


    (gdb) f 1
    #1  0x00007fffbd975ed7 in NormalAnaMgr::PreUserTrackingAction (this=0x687d8f0, aTrack=0xc50b53b0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:332
    332	        theTrack->SetUserInformation(anInfo);
    (gdb) p anInfo
    $1 = (NormalTrackInfo *) 0xc50aa5a0
    (gdb) list
    327	NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    328	
    329	    if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0) {
    330	        NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    331	        G4Track* theTrack = (G4Track*)aTrack;
    332	        theTrack->SetUserInformation(anInfo);
    333	    }
    334	    NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    335	
    336	    if (!info) {
    (gdb) 



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
    355         }
    356     
    357         // An example: Get the parent particle name from track info
    358         // if (info && aTrack->GetDefinition()!=G4OpticalPhoton::Definition()) {
    359         //     // const G4String& parent_name = info->getParentName();
    360         //     // G4cout << " The parent of " << aTrack->GetDefinition()->GetParticleName()
    361         //     //        << " is " << parent_name
    362         //     //        << G4endl;
    363         // }
    364 
    365     }
    366 
    367 }   


setting TrackInfo
----------------------

::

    (gdb) f 1
    #1  0x00007fffbd975ed7 in NormalAnaMgr::PreUserTrackingAction (this=0x687d8f0, aTrack=0xc50b53b0) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:332
    332	        theTrack->SetUserInformation(anInfo);
    (gdb) p anInfo
    $1 = (NormalTrackInfo *) 0xc50aa5a0
    (gdb) list
    327	NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    328	
    329	    if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0) {
    330	        NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    331	        G4Track* theTrack = (G4Track*)aTrack;
    332	        theTrack->SetUserInformation(anInfo);
    333	    }
    334	    NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    335	
    336	    if (!info) {
    (gdb) 



::

    A[blyth@localhost junosw]$ jgr tracedAncestors
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        inline const std::vector<G4int>& getTracedAncestors() const { return tracedAncestors; }
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        std::vector<G4int> tracedAncestors;
    ./Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc:    tracedAncestors = aTrackInfo->tracedAncestors;
    A[blyth@localhost junosw]$ 


    A[blyth@localhost junosw]$ jgr TracedAncestors
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc:    const std::vector<G4int>& ancestors = trackinfo->getTracedAncestors();
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        info->markTracedAncestors(aTrack->GetTrackID());
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        // info->markTracedAncestors(aTrack->GetParentID());
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        // if (info->getTracedAncestors().size()) {
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        //     jm_trk->setAncestorID(info->getTracedAncestors()[0]);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:            if (normaltrk->getTracedAncestors().size()
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:                && normaltrk->getTracedAncestors().back() != -1) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:                producerID = normaltrk->getTracedAncestors().back();
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        inline void markTracedAncestors(G4int trkid) { tracedAncestors.push_back(trkid); }
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        inline const std::vector<G4int>& getTracedAncestors() const { return tracedAncestors; }
    A[blyth@localhost junosw]$ 








empty dtor : does that prevent cleanup ?
--------------------------------------------

::

    59 NormalTrackInfo::~NormalTrackInfo(){;} 

::

    1239 inline void NP::clear()
    1240 {
    1241     data.clear();
    1242     data.shrink_to_fit();
    1243     shape[0] = 0 ;
    1244 }


