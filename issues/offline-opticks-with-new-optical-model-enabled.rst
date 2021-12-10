offline-opticks-with-new-optical-model-enabled
================================================


Currently need to use --disable-pmt-optical-model now added to tds3
---------------------------------------------------------------------


::

    TODO: suggest "--new-optical-model" is too unspecific a name and too similar 


    0340         # add new optical model
     341 
     342         grp_pmt_op.add_argument("--new-optical-model", dest="new_optical_model", action="store_true",
     343                       help=mh("Use the new optical model."))
     344         grp_pmt_op.add_argument("--old-optical-model", dest="new_optical_model", action="store_false",
     345                       help=mh("Use the old optical model"))
     346         grp_pmt_op.set_defaults(new_optical_model=False)
     347 

    0407         # == use new pmt optical model or not ==
     408         grp_pmt_op.add_argument("--enable-pmt-optical-model", dest="pmt_optical_model", action="store_true")
     409         grp_pmt_op.add_argument("--disable-pmt-optical-model", dest="pmt_optical_model", action="store_false")
     410         grp_pmt_op.set_defaults(pmt_optical_model=True)


    1523             if args.new_optical_model:
    1524                 op_process.property("UseAbsReemit").set(True)
    1525                 op_process.property("UseScintSimple").set(True)
    1526             else:
    1527                 op_process.property("UseAbsReemit").set(False)
    1528                 op_process.property("UseScintSimple").set(False)
    1529             # pmt optical model

    1530             if args.pmt_optical_model:
    1531                 op_process.property("UsePMTOpticalModel").set(True)


    1532            # op_process.property("UseAbsReemit").set(args.absreemit)




    epsilon:offline blyth$ jgr UsePMTOpticalModel
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=false); // just the fast simulation
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=true); // just the fast simulation
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        #op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_any.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:            pmtmgr.property("UsePMTOpticalModel").set(True)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("UsePMTOpticalModel", m_pmt_optical_model = "old");
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                op_process.property("UsePMTOpticalModel").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                detsimfactory.property("UsePMTOpticalModel").set("new")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                detsimfactory.property("UsePMTOpticalModel").set("old")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                pmtsdmgr.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    epsilon:offline blyth$ 




tds3 does this too
--------------------

::

    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize
    2021-12-10 22:53:32.919 INFO  [67699] [junoSD_PMT_v2_Opticks::Initialize@87]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 g4ok 0x71adf50
    Begin of Event --> 0
    2021-12-10 22:53:32.928 FATAL [67699] [CManager::setStep@487]  boundary_status zero 
    2021-12-10 22:53:32.933 WARN  [67699] [OpStatus::OpPointFlag@393]  OpPointFlag ZERO   proceesDefinedStep? fast_sim_man stage COLLECT status GeomBoundary
    python: /home/blyth/opticks/cfg4/OpStatus.cc:398: static unsigned int OpStatus::OpPointFlag(const G4StepPoint*, G4OpBoundaryProcessStatus, CStage::CStage_t): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd40c2008 in OpStatus::OpPointFlag (point=0x7ffd48f968a0, bst=SameMaterial, stage=CStage::COLLECT) at /home/blyth/opticks/cfg4/OpStatus.cc:398
    #5  0x00007fffd40d164b in CRecorder::postTrackWriteSteps (this=0x1de7dffa0) at /home/blyth/opticks/cfg4/CRecorder.cc:550
    #6  0x00007fffd40d0067 in CRecorder::postTrack (this=0x1de7dffa0) at /home/blyth/opticks/cfg4/CRecorder.cc:214
    #7  0x00007fffd40fdc7c in CManager::postTrack (this=0x1de7dfd00) at /home/blyth/opticks/cfg4/CManager.cc:335
    #8  0x00007fffd40fdbe8 in CManager::PostUserTrackingAction (this=0x1de7dfd00, track=0x7ffd48f64d20) at /home/blyth/opticks/cfg4/CManager.cc:303
    #9  0x00007fffd45fa0d0 in G4OpticksRecorder::PostUserTrackingAction (this=0xb306e0, track=0x7ffd48f64d20) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:137
    #10 0x00007fffcaa641a8 in G4OpticksAnaMgr::PostUserTrackingAction (this=0xb57ec0, trk=0x7ffd48f64d20)
        at /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:34
    #11 0x00007fffcb215ee5 in MgrOfAnaElem::PostUserTrackingAction (this=0x7fffcb424b00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x7ffd48f64d20)
        at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:67
    #12 0x00007fffcad87eef in LSExpTrackingAction::PostUserTrackingAction (this=0x56d6190, aTrack=0x7ffd48f64d20)
        at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:48
    #13 0x00007fffdf28e7f0 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #14 0x00007fffdf4c5399 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #15 0x00007fffcafdb4a1 in G4SvcRunManager::SimulateEvent (this=0x854b30, i_event=0) at /data/blyth/junotop/offline/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #16 0x00007fffcb208edb in DetSimAlg::execute (this=0xb30b50) at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimAlg/src









::

    2. I use the latest j.bash repository and I run the tds3gun

    However, it break down:


    2021-12-08 20:46:51.554 INFO  [250874] [junoSD_PMT_v2_Opticks::Initialize@87]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 g4ok 0x734cb80
    Begin of Event --> 0
    2021-12-08 20:46:51.562 FATAL [250874] [CManager::setStep@487]  boundary_status zero 
    2021-12-08 20:46:51.566 WARN  [250874] [OpStatus::OpPointFlag@393]  OpPointFlag ZERO   proceesDefinedStep? fast_sim_man stage COLLECT status GeomBoundary
    python: /home/ihep/juno-cmake-version/JUNOSOFT/opticks/cfg4/OpStatus.cc:398: static unsigned int OpStatus::OpPointFlag(const G4StepPoint*, G4OpBoundaryProcessStatus, CStage::CStage_t): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in __GI_raise (sig=sig@entry=6) at ../nptl/sysdeps/unix/sysv/linux/raise.c:55
    55   return INLINE_SYSCALL (tgkill, 3, pid, selftid, sig);
    Missing separate debuginfos, use: debuginfo-install readline-6.2-11.el7.x86_64
    (gdb) quit
    A debugging session is active.
    and I try to fix it thus I check the code in  /home/ihep/juno-cmake-version/JUNOSOFT/opticks/cfg4/OpStatus.cc:398 

    the error code is following:


       else
        {
            LOG(warning) << " OpPointFlag ZERO  "
                         << " proceesDefinedStep? " << processName
                         << " stage " << CStage::Label(stage)
                         << " status " << OpStepString(status)
                         ;
            assert(0);
        }
    It seems strange that why it go into this branch. 




Hi Yuxiang, 

2021-12-08 20:46:51.566 WARN  [250874] [OpStatus::OpPointFlag@393]  OpPointFlag ZERO   proceesDefinedStep? fast_sim_man stage COLLECT status GeomBoundary


Presumably this is because of the new optical model is now default.

The new optical model uses Geant4 “fast simulation” which Opticks recording of Geant4 propagations 
(part of which is the below code) has never been tested with.  
Getting asserts is to be expected whenever code is used in such a new situation.

So to avoid you will need to disable the new optical model for now.

Simon


::

    342 #ifdef USE_CUSTOM_BOUNDARY
    343 unsigned int OpStatus::OpPointFlag(const G4StepPoint* point, const Ds::DsG4OpBoundaryProcessStatus bst, CStage::CStage_t stage)
    344 #else
    345 unsigned int OpStatus::OpPointFlag(const G4StepPoint* point, const G4OpBoundaryProcessStatus bst, CStage::CStage_t stage)
    346 #endif
    347 {
    348     G4StepStatus status = point->GetStepStatus()  ;
    349     // TODO: cache the relevant process objects, so can just compare pointers ?
    350     const G4VProcess* process = point->GetProcessDefinedStep() ;
    351     const G4String& processName = process ? process->GetProcessName() : "NoProc" ;
    352 
    353     bool transportation = strcmp(processName,"Transportation") == 0 ;
    354     bool scatter = strcmp(processName, "OpRayleigh") == 0 ;
    355     bool absorption = strcmp(processName, "OpAbsorption") == 0 ;
    356 
    357     unsigned flag(0);
    358 
    359     // hmm stage and REJOINing look kinda odd here, do elsewhere ?
    360     // moving it first, breaks seqhis matching for multi-RE lines 
    361 
    362     if(absorption && status == fPostStepDoItProc )
    363     {
    364         flag = BULK_ABSORB ;
    365     }
    366     else if(scatter && status == fPostStepDoItProc )
    367     {
    368         flag = BULK_SCATTER ;
    369     }
    370     else if( stage == CStage::REJOIN )
    371     {
    372         flag = BULK_REEMIT ;
    373     }
    374     else if(transportation && status == fGeomBoundary )
    375     {
    376         flag = OpStatus::OpBoundaryFlag(bst) ; // BOUNDARY_TRANSMIT/BOUNDARY_REFLECT/NAN_ABORT/SURFACE_ABSORB/SURFACE_DETECT/SURFACE_DREFLECT/SURFACE_SREFLECT
    377 
    378         if(flag == 0)
    379         {
    380             LOG(fatal)
    381                 << " boundary flag zero "
    382                 << " bst " << bst
    383                 ;
    384         }
    385 
    386     }
    387     else if(transportation && status == fWorldBoundary )
    388     {
    389         flag = MISS ;
    390     }
    391     else
    392     {
    393         LOG(warning) << " OpPointFlag ZERO  "
    394                      << " proceesDefinedStep? " << processName
    395                      << " stage " << CStage::Label(stage)
    396                      << " status " << OpStepString(status)
    397                      ;
    398         assert(0);
    399     }
    400 
    401     LOG(LEVEL) << " flag " << flag << " processName " << processName ;
    402 
    403     return flag ;
    404 }
