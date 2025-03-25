no-anamgr
===========


* suspect that not having any anamgr may be over-draconian in opticksMode 1 
* WIP: review J+Opticks use of G4 track info to see if can loosen requirements

  * looks like primary use of g4 track info is for tracing thru reemission generations
    
    * that is not relevant to opticksMode:1 



::

     57 no-anamgr(){ cat << EOU
     58 --no-anamgr-normal
     59 --no-anamgr-genevt
     60 --no-anamgr-edm-v2
     61 --no-anamgr-grdm
     62 --no-anamgr-deposit
     63 --no-anamgr-deposit-tt
     64 --no-anamgr-interesting-process
     65 --no-anamgr-optical-parameter
     66 --no-anamgr-timer
     67 EOU
     68    : --opticks-anamgr attempts to switch on U4RecorderAnaMgr - BUT THAT NEEDS opticksMode 2 or 3
     69 }  
     70 
     71 no-anamgr(){ echo -n ; } # override
     72 
     73 
     74 logging(){
     75     type $FUNCNAME
     76     export QEvent=INFO
     77 } 
     78 [ -n "$LOG" ] && logging
     79 
     80 
     81 if [ "${arg/test0}" != "$arg" ]; then 
     82     echo gdb -ex r --args $(which python) $(which tut_detsim.py) --evtmax 10 $(no-anamgr) --opticks-mode 1 gun 
     83          gdb -ex r --args $(which python) $(which tut_detsim.py) --evtmax 10 $(no-anamgr) --opticks-mode 1 gun 
     84 fi 



::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    python: /builds/JUNO/offline/junosw/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:360: virtual G4VParticleChange* G4Cerenkov_modified::PostStepDoIt(const G4Track&, const G4Step&): Assertion `a_ui == nullptr' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748ba6c in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) bt
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc307ae6a in G4Cerenkov_modified::PostStepDoIt (this=0x2265eda0, aTrack=..., aStep=...) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:360
    #6  0x00007fffcae31519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffcae3191b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffcae2f154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffcae3a70f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffcb3c7565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffe32a768e in G4SvcRunManager::SimulateEvent (this=0x67f0d40, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29




::

    A[blyth@localhost junosw]$ find . -name '*.cc' -exec grep -l WITH_G4CXOPTICKS {} \;
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./Simulation/DetSimV2/PMTSim/src/OK_PMTSIM_LOG.cc
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc
    ./Simulation/GenTools/src/GtOpticksTool.cc
    ./Simulation/SimSvc/MultiFilmLUTMakerSvc/src/MultiFilmLUTMakerSvc.cc
    A[blyth@localhost junosw]$ 




::

     358   bool is_opticks_genstep = fNumPhotons > 0 ;
     359   G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
     360   assert( a_ui == nullptr );  // should always be null, as process C is not applicable to RE-photons
     361 
     362   if(is_opticks_genstep && (m_opticksMode ==  1 || m_opticksMode == 3 ))
     363   {
     364       U4::CollectGenstep_G4Cerenkov_modified(
     365           &aTrack,
     366           &aStep,
     367           fNumPhotons,
     368           BetaInverse,
     369           Pmin,
     370           Pmax,
     371           maxCos,
     372           maxSin2,
     373           MeanNumberOfPhotons1,
     374           MeanNumberOfPhotons2
     375       );
     376       if(m_opticksMode == 1)
     377       {
     378           // in opticksMode:1 stop the generation of Cerenkov photons
     379           aParticleChange.SetNumberOfSecondaries(0);
     380           return pParticleChange;
     381       }
     382   }
     383 #endif
     384 
     385   ////////////////////////////////////////////////////////////////
     386 
     387   aParticleChange.SetNumberOfSecondaries(fNumPhotons);





Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc::

     559 #ifdef WITH_G4CXOPTICKS
     560     U4::GenPhotonAncestor(&aTrack);
     561 #endif
     562 
     563 //-------------------------------------------------//
     564 
     565     for(size_t scnt = 0 ; scnt < nscnt ; scnt++){
     566 
     567          G4double ScintillationTime = 0.*ns;



::

    042 /**
     43 U4 private state
     44 --------------------
     45 
     46 Here are holding the state of the genstep collection in translation-unit-local static variables. 
     47 
     48 An alternative more o.o. approach would be to use a U4Private/U4Impl struct
     49 that a U4 instance holds a pointer to and passes along messages to.  
     50 That is like the PImpl pattern : pointer to implementation.
     51 
     52 * https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/
     53 * https://www.cppstories.com/2018/01/pimpl/
     54 
     55 HMM: perhapa this state belongs better within SEvt together with the full gensteps ?
     56 
     57 **/
     58 
     59 
     60 #ifdef WITH_CUSTOM4
     61 static C4GS gs = {} ;            // updated by eg U4::CollectGenstep_DsG4Scintillation_r4695 prior to each photon generation loop 
     62 static C4Pho ancestor = {} ;     // updated by U4::GenPhotonAncestor prior to the photon generation loop(s)
     63 static C4Pho pho = {} ;          // updated by U4::GenPhotonBegin at start of photon generation loop
     64 static C4Pho secondary = {} ;    // updated by U4::GenPhotonEnd   at end of photon generation loop 
     65 #else
     66 static sgs gs = {} ;            // updated by eg U4::CollectGenstep_DsG4Scintillation_r4695 prior to each photon generation loop 
     67 static spho ancestor = {} ;     // updated by U4::GenPhotonAncestor prior to the photon generation loop(s)
     68 static spho pho = {} ;          // updated by U4::GenPhotonBegin at start of photon generation loop
     69 static spho secondary = {} ;    // updated by U4::GenPhotonEnd   at end of photon generation loop 
     70 #endif



    300 /**
    301 U4::GenPhotonAncestor
    302 ----------------------
    303 
    304 NB this is called prior to generation loops to get the ancestor spho.h label 
    305 
    306 This label is needed for BOTH Scintillation and Cerenkov in order for photon G4Track 
    307 labelling done by U4::GenPhotonEnd to work. 
    308 
    309 When the track has no user info the ancestor is set to spho::Placeholder label {-1,-1,-1,-1}. 
    310 
    311 If the call to U4::GenPhotonAncestor is omitted from the Scintillation OR Cerenkov 
    312 PostStepDoIt then the ancestor will default to {0,0,0,0} : that will cause 
    313 unexpected labels. 
    314 
    315 **/
    316 
    317 void U4::GenPhotonAncestor( const G4Track* aTrack )
    318 {
    319 #ifdef WITH_CUSTOM4
    320     ancestor = C4TrackInfo<C4Pho>::Get(aTrack) ;
    321 #else
    322     ancestor = STrackInfo<spho>::Get(aTrack) ;
    323 #endif
    324     if(dump) std::cout << "U4::GenPhotonAncestor " << ancestor.desc() << std::endl ;
    325     LOG(LEVEL) << ancestor.desc() ;
    326 }


::

    018 template<typename T>
     19 struct C4TrackInfo : public G4VUserTrackInformation
     20 {   
     21     T label  ;
     22     
     23     C4TrackInfo(const T& label);
     24     std::string desc() const ;
     25     
     26     static C4TrackInfo<T>* GetTrackInfo(const G4Track* track); 
     27     static C4TrackInfo<T>* GetTrackInfo_dynamic(const G4Track* track);
     28     static bool Exists(const G4Track* track); 
     29     static T  Get(   const G4Track* track);   // by value 
     30     static T* GetRef(const G4Track* track);   // by reference, allowing inplace changes
     31     static std::string Desc(const G4Track* track);
     32     
     33     static void Set(G4Track* track, const T& label );
     34 };




