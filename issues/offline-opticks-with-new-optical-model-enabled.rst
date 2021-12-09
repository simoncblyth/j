offline-opticks-with-new-optical-model-enabled
================================================

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
