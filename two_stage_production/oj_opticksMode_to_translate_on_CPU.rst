oj_opticksMode_to_translate_on_CPU
====================================

Get "tut_detsim.py --opticks-mode 1 --evtmax 0 gun" to work without GPU ? Or add another mode ? 
--------------------------------------------------------------------------------------------------



jcv JUNODetSimModule::

    0422         # == opticks ==
     423         default_opticks_mode = 1 if "OPTICKS_PREFIX" in os.environ else 0
     424         grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=default_opticks_mode,
     425                                 help=mh("Control Opticks GPU Optical simulation"))
     426         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     427                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
     428 
    ....
    1798         detsimfactory.property("OpticksMode").set(args.opticks_mode)



    A[blyth@localhost junosw]$ jgr OpticksMode
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:            phy_process.property("OpticksMode").set(args.opticks_mode)  # see DsPhysConsOptical
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        detsimfactory.property("OpticksMode").set(args.opticks_mode)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmtsdmgr.property("OpticksMode").set(args.opticks_mode)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        op_process.property("OpticksMode").set(args.opticks_mode)  # see DsPhysConsOptical
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    phy_process.property("OpticksMode").set(0)  # see DsPhysConsOptical
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    pmtsdmgr.property("OpticksMode").set(0)
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     void setOpticksMode(int opticksMode) {m_opticksMode = opticksMode ;}
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("OpticksMode", m_opticksMode=0);
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    dc->setOpticksMode(m_opticksMode);
    ./Simulation/DetSimV2/DetSimOptions/src/JUNOPhyParaTool.cc:    declProp("OpticksMode", m_opticksMode=0);
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        int getOpticksMode() const { return m_opticksMode ; }
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("OpticksMode", m_opticksMode=0);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    m_opticksMode(jpmt->getOpticksMode()),
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh:  void SetOpticksMode(const G4int opticksMode); 
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh:  G4int GetOpticksMode() const ;  
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh:void G4Cerenkov_modified::SetOpticksMode(const G4int opticksMode)
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh:G4int G4Cerenkov_modified::GetOpticksMode() const 
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh:  G4int fOpticksMode;
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("OpticksMode", m_opticksMode=0);
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:            cerenkov->SetOpticksMode(m_opticksMode); 
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:             fOpticksMode(opticksMode)
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  if(is_opticks_genstep && (fOpticksMode & 1 ))
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  if(is_opticks_genstep && (fOpticksMode & 1 ))
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  if(fOpticksMode == 0 || (fOpticksMode & 2))
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  }  // endif  (fOpticksMode == 0 || (fOpticksMode & 2))
    A[blyth@localhost junosw]$ 


L : non-CUDA running for translation
---------------------------------------

::

    s_bb::IncludeAABB 
     inital_aabb  [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
     other_aabb   [102.966,-128.966,-135.000,128.966,-102.966,-35.000]COMBINE
     updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 105 LVID -1 name uni1_0 soname uni1_0
    [Detaching after vfork from child process 3500356]
    [New Thread 0x7fffc26e4640 (LWP 3500508)]
    [Detaching after vfork from child process 3500509]
    [Detaching after fork from child process 3500510]
    [Detaching after fork from child process 3500526]
    [Detaching after fork from child process 3500539]
    [Detaching after fork from child process 3500551]
    Traceback (most recent call last):
      File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Tue/bin/tut_detsim.py", line 53, in <module>
        juno_application.run()
      File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Tue/python/Tutorial/JUNOApplication.py", line 224, in run
        self.toptask.run()
    RuntimeError: CUDA call (cudaMalloc(reinterpret_cast<void**>( &d_array ), size ) ) failed with error: 'no CUDA-capable device is detected' (/home/blyth/opticks/qudarap/QU.cc:142)

    junotoptask:detsimiotask.terminate  WARN: invalid state tranform ((StartUp)) => ((EndUp))
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc59f0508 in JunoTimer::number_of_measurements (this=0x0) at /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h:32
    32  /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h: Directory not empty.
    (gdb) bt
    #0  0x00007fffc59f0508 in JunoTimer::number_of_measurements (this=0x0) at /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h:32
    #1  0x00007fffc33a4958 in TimerAnaMgr::EndOfRunAction (this=0x67872e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/TimerAnaMgr.cc:43
    #2  0x00007fffcf35495a in MgrOfAnaElem::EndOfRunAction (this=0x8e10110, run=0x0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:39
    #3  0x00007fffc37c98c5 in LSExpRunAction::EndOfRunAction (this=0x914de30, aRun=0x0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpRunAction.cc:73
    #4  0x00007fffcb0095ed in G4RunManager::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #5  0x00007fffe0385727 in G4SvcRunManager::finalizeRM (this=0x6652770) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #6  0x00007fffcf349e9f in DetSimAlg::finalize (this=0x667fb00) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #7  0x00007fffd4215d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffd422ad6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd422e611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd422ebb8 in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd422bf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/sniper/InstallArea/lib64/libSnipe



U[blyth@lxlogin001 oj]$ QU=INFO source oj.sh::

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 105 LVID -1 name uni1_0 soname uni1_0
    [Detaching after vfork from child process 3596546]
    2025-04-02 18:09:05.180 INFO  [3584408] [QU::UploadArray@126]  num_items 1 size 8 label QBase::init/d_base
    [New Thread 0x7fffc26e4640 (LWP 3598065)]
    [Detaching after vfork from child process 3598079]



A : repro with CUDA_VISIBLE_DEVICES=1 to deliberately mimic no GPU
-----------------------------------------------------------------------

::

    A[blyth@localhost oj]$ export CUDA_VISIBLE_DEVICES=1
    A[blyth@localhost oj]$ LOG=1 oj

  

    s_bb::IncludeAABB 
     inital_aabb  [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
     other_aabb   [-128.966,-128.966,-135.000,-102.966,-102.966,-35.000]COMBINE
     updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
    s_bb::IncludeAABB 
     inital_aabb  [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
     other_aabb   [-13.000,-177.000,-135.000, 13.000,-151.000,-35.000]COMBINE
     updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
    s_bb::IncludeAABB 
     inital_aabb  [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
     other_aabb   [102.966,-128.966,-135.000,128.966,-102.966,-35.000]COMBINE
     updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 105 LVID -1 name uni1_0 soname uni1_0
    [Detaching after vfork from child process 40241]
    2025-04-02 18:17:34.590 INFO  [40193] [QU::UploadArray@126]  num_items 1 size 8 label QBase::init/d_base
    Traceback (most recent call last):
      File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Tue/bin/tut_detsim.py", line 53, in <module>
        juno_application.run()
      File "/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.2.3_Opticks-v0.3.3/el9_amd64_gcc11/Tue/python/Tutorial/JUNOApplication.py", line 224, in run
        self.toptask.run()
    RuntimeError: CUDA call (cudaMalloc(reinterpret_cast<void**>( &d_array ), size ) ) failed with error: 'no CUDA-capable device is detected' (/home/blyth/opticks/qudarap/QU.cc:142)

    [Thread 0x7fffcd4ff640 (LWP 40215) exited]
    junotoptask:detsimiotask.terminate  WARN: invalid state tranform ((StartUp)) => ((EndUp))
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc10ad508 in JunoTimer::number_of_measurements (this=0x0) at /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h:32
    warning: 32 /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h: No such file or directory
    (gdb) 

     


A : handling ZERO VISIBLE DEVICES
-------------------------------------

::

    A[blyth@localhost sysrap]$ ~/o/sysrap/tests/scontext_test.sh run
    0:NVIDIA_RTX_5000_Ada_GenerationA[blyth@localhost sysrap]$ 
    A[blyth@localhost sysrap]$ 
    A[blyth@localhost sysrap]$ 
    A[blyth@localhost sysrap]$ export CUDA_VISIBLE_DEVICES=1
    A[blyth@localhost sysrap]$ ~/o/sysrap/tests/scontext_test.sh run
    scontext::initConfig : ZERO VISIBLE DEVICES - CHECK CUDA_VISIBLE_DEVICES envvar 
    A[blyth@localhost sysrap]$ 

SEventConfig::SetDevice not called when none found::

    087 inline void scontext::initConfig()
     88 {
     89     int numdev = visible_devices.size();
     90 
     91     if(numdev == 0)
     92     {
     93         std::cerr << "scontext::initConfig : ZERO VISIBLE DEVICES - CHECK CUDA_VISIBLE_DEVICES envvar \n" ;
     94     }
     95     else if(numdev > 1)
     96     {
     97         std::cerr << "scontext::initConfig : MORE THAN ONE VISIBLE DEVICES - CHECK CUDA_VISIBLE_DEVICES envvar \n" ;
     98     }
     99     else if(numdev == 1)
    100     {
    101         int idev = 0 ;
    102         std::string name = device_name(idev);
    103         size_t vram = totalGlobalMem_bytes(idev);
    104         // HMM: could just handover the sdevice struct ?
    105         SEventConfig::SetDevice(vram, name);
    106     }
    107 }




envset Mockup on P
-------------------

::

    P[blyth@localhost junosw]$ cd /data/blyth/junotop/junosw
    P[blyth@localhost junosw]$ ln -s InstallArea JLocal
    P[blyth@localhost blyth]$ export JUNOTOP=/data/blyth/junotop/junosw/JLocal

    P[blyth@localhost junosw]$ echo $OPTICKS_PREFIX
    /data/blyth/opticks_Debug
    P[blyth@localhost junosw]$ cd /data/blyth/
    P[blyth@localhost blyth]$ ln -s opticks_Debug OLocal

    P[blyth@localhost opticks_Debug]$ ln -s . shim
    P[blyth@localhost blyth]$ export JUNO_OPTICKS_PREFIX=/data/blyth/OLocal/shim
     
    P[blyth@localhost junosw]$ source .gitlab-ci/oj_helper.sh EMIT_ENV > InstallArea/ENV.bash
    P[blyth@localhost junosw]$ source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallArea/envset.sh




