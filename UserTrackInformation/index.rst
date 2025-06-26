UserTrackInformation : How to make TrackInfo usage cohabit ?
===============================================================


Overview
--------

* adding C4Pho.h label to NormalTrackInfo.h within WITH_G4CXOPTICKS initially is straightforward
  as WITH_CUSTOM4 is standard for JUNOSW

  * how to set placeholder ?
  * how to set from the processes ?
   
* BUT: not so easy to adapt opticks/U4Recorder to use that from a dependency point of view

  * BUT: may be able to focus the change into JUNOSW/U4RecorderAnaMgr
    in such a way to reduce the changes needed to U4Recorder. Perhaps 
    can change from (G4Track*)trk parameter to (int4*)label 



jcv U4RecorderAnaMgr
-----------------------

On earlier branch::

    [blyth@localhost junosw]$ git s
    On branch blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
    Your branch is up to date with 'origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration'.

    nothing to commit, working tree clean
    A[blyth@localhost junosw]$ 


    [blyth@localhost junosw]$ git l -n5
    commit 22ee7520d9f22046aacc6c07e4cb0e92e102e480 (HEAD -> blyth-NormalTrackInfo-C4Pho-label-Opticks-integration, origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Sat Jun 7 16:40:23 2025 +0800

        changing NormalTrackInfo has difficulties, so defer the spearate label approach

    M       Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    M       Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc



    int* U4RecorderAnaMgr::LabelData( const G4Track* trk )  // static
    +{
    +#ifdef WITH_NORMAL_LABEL
    +    NormalTrackInfo* ui = (NormalTrackInfo*)(trk->GetUserInformation());
    +    int* label_data =  ui ? ui->getLabelData() : nullptr ;
    +#else
    +    int* label_data = nullptr ; 
    +#endif
    +    return label_data ;
    +}





u4/U4Recorder has int* arg label interface to workaround dependency conundrum
---------------------------------------------------------------------------------

::

    113     void PreUserTrackingAction(const G4Track* );
    114     void PostUserTrackingAction(const G4Track* );
    115 
    116     void PreUserTrackingAction_( const G4Track*, int* label );
    117     void PostUserTrackingAction_(const G4Track*, int* label );
    118 
    119     void PreUserTrackingAction_Optical(const G4Track*);
    120     void PreUserTrackingAction_Optical_(const G4Track*, int* label );




Create branch : blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
------------------------------------------------------------------------

::

    (ok) A[blyth@localhost junosw]$ git checkout blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
    branch 'blyth-NormalTrackInfo-C4Pho-label-Opticks-integration' set up to track 'origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration'.
    Switched to a new branch 'blyth-NormalTrackInfo-C4Pho-label-Opticks-integration'


     21 U4RecorderAnaMgr::~U4RecorderAnaMgr()
     22 {
     23 #ifdef WITH_G4CXOPTICKS
     24     delete m_recorder ; 
     25 #endif
     26 }
     27     
     28 #ifdef WITH_G4CXOPTICKS
     29 void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* run) {         m_recorder->BeginOfRunAction(run);       }
     30 void U4RecorderAnaMgr::EndOfRunAction(const G4Run* run) {           m_recorder->EndOfRunAction(run);         }
     31     
     32 void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* evt) {    /*m_recorder->BeginOfEventAction(evt);*/  }
     33 void U4RecorderAnaMgr::EndOfEventAction(const G4Event* evt) {      /*m_recorder->EndOfEventAction(evt);*/    }
     34 // see G4CXOpticks::SensitiveDetector_Initialize
     35 // see G4CXOpticks::SensitiveDetector_EndOfEvent 
     36     
     37 void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* trk) {  m_recorder->PreUserTrackingAction(trk);  }
     38 void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction(trk); }
     39 void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
     40 #else
     41 void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* ) {} 
     42 void U4RecorderAnaMgr::EndOfRunAction(const G4Run* ) {} 
     43 void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* ) {}
     44 void U4RecorderAnaMgr::EndOfEventAction(const G4Event* ) {}
     45 void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* ) {}
     46 void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* ) {}
     47 void U4RecorderAnaMgr::UserSteppingAction(const G4Step* ) {}
     48 #endif
     49 






J::

    A[blyth@localhost junosw]$ jgr UserTrackInformation
    ./Simulation/DetSimV2/PMTSim/include/IToolForSD_PMT.h:#include "G4VUserTrackInformation.hh"
    ./Simulation/DetSimV2/PMTSim/include/IToolForSD_PMT.h:    G4VUserTrackInformation* trackInfo;
    ./Simulation/DetSimV2/PMTSim/src/dywPMTOpticalModel.cc:            G4VUserTrackInformation* trkinfo = prmtrk->GetUserInformation();



    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc:  G4VUserTrackInformation* trkinfo = params.trackInfo;


        075   // create new juno hit photon, the way of recording photo hits on PMTs
         76   junoHit_PMT* hit_photon = new junoHit_PMT();
         77   hit_photon->SetPMTID((int)params.ipmt);
         78   hit_photon->SetWeight((int)params.weight);
         79   hit_photon->SetTime((double) params.time );
         80   hit_photon->SetWavelength((double)params.wavelength);
         81   hit_photon->SetKineticEnergy((double) params.kineticEnergy );
         82   hit_photon->SetPosition(params.position);
         83   hit_photon->SetMomentum(params.momentum);
         84   hit_photon->SetPolarization(params.polarization);
         85   hit_photon->SetCount( params.iHitPhotonCount );
         86   // = User can handle the track info here =
         87   G4VUserTrackInformation* trkinfo = params.trackInfo;
         88 
         89     double t_start = 0.0; // the generated time of primary optical photon
         90     G4ThreeVector p_start;
         91     G4bool is_from_cerenkov = false;
         92     G4bool is_reemission = false;
         93     int producerID = params.producerID;
         94     bool is_original_op = false;
         95     if (trkinfo) {
         96         // try to load
         97 
         98         NormalTrackInfo* normaltrk = dynamic_cast<NormalTrackInfo*>(trkinfo);
         99         if (normaltrk) {
        100             producerID = normaltrk->GetOriginalTrackID();
        101             is_from_cerenkov = normaltrk->isFromCerenkov();
        102             is_reemission = normaltrk->isReemission();
        103 
        104             t_start = normaltrk->getOriginalOPStartTime();
        105 
        106             is_original_op = normaltrk->isOriginalOP();
        107         }
        108     }
        109 
        110   hit_photon->SetProducerID(producerID);
        111   hit_photon->SetFromCerenkov(is_from_cerenkov);
        112   hit_photon->SetReemission(is_reemission);
        113   hit_photon->SetOriginalOP(is_original_op);
        114   hit_photon->SetOriginalOPStartT(t_start);
        115 




    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    G4VUserTrackInformation* trkinfo = track->GetUserInformation();


         862 void junoSD_PMT_v2::SaveNormHit(int pmtID, G4ThreeVector local_pos, G4ThreeVector global_pos,double hittime, G4Track *  track ,double edep){
         863 
         864 #ifdef WITH_G4CXOPTICKS_DEBUG
         865       m_jpmt_dbg->SaveNormHit_count += 1 ;
         866 #endif
         867 
         868     const G4AffineTransform& trans = track->GetTouchable()->GetHistory()->GetTopTransform();
         869 
         870     // == momentum and polarization
         871     G4ThreeVector local_pol = trans.TransformAxis(track->GetPolarization());
         872     local_pol = local_pol.unit();
         873     G4ThreeVector local_dir = trans.TransformAxis(track->GetMomentum());
         874     local_dir = local_dir.unit();
         875 
         876     // == wavelength 
         877     double wavelength = twopi*hbarc / edep;
         878 
         879     // == additional information from User Track information
         880     int producerID = -1;
         881     bool is_from_cerenkov = false;
         882     bool is_reemission = false;
         883     bool is_original_op = false;
         884     double t_start = 0;
         885     G4ThreeVector boundary_pos;
         886     G4VUserTrackInformation* trkinfo = track->GetUserInformation();
         887     if (trkinfo) {
         888         NormalTrackInfo* normaltrk = dynamic_cast<NormalTrackInfo*>(trkinfo);
         889         if (normaltrk) {
         890             // if there are traced ancestors, use the track id of final state.
         891             producerID = normaltrk->GetOriginalTrackID();
         892             if (normaltrk->getTracedAncestors().size()
         893                 && normaltrk->getTracedAncestors().back() != -1) {
         894                 producerID = normaltrk->getTracedAncestors().back();
         895             }
         896 
         897             is_from_cerenkov = normaltrk->isFromCerenkov();
         898             is_reemission = normaltrk->isReemission();
         899 
         900             t_start = normaltrk->getOriginalOPStartTime();
         901 
         902             is_original_op = normaltrk->isOriginalOP();
         903             boundary_pos = normaltrk->getBoundaryPos();
         904         }
         905     }
         906 




    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:  G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:      G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;

        292 #ifdef WITH_G4CXOPTICKS
        293   bool is_opticks_genstep = fNumPhotons > 0 ;
        294   G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
        295   assert( a_ui == nullptr );  // should always be null, as process C is not applicable to RE-photons



    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:#include "G4VUserTrackInformation.hh"
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:class NormalTrackInfo: public G4VUserTrackInformation {
           Looks pretty normal, no clever handling for multiple users of TrackInfo



O:

    (ok) A[blyth@localhost junosw]$ opticks-fl STrackInfo
    ./sysrap/CMakeLists.txt
    ./sysrap/SFastSimOpticalModel.hh
    ./sysrap/STrackInfo.h
    ./u4/InstrumentedG4OpBoundaryProcess.cc

         101 #include "SEvt.hh"
         102 #include "SSys.hh"
         103 //#include "U4PhotonInfo.h"  // TODO: should be STrackInfo<spho> now
         104 const int InstrumentedG4OpBoundaryProcess::PIDX = SSys::getenvint("PIDX", -1) ;
         105 
         106 #ifdef WITH_CUSTOM4
         107 #include "C4TrackInfo.h"
         108 #include "C4Pho.h"
         109 #else
         110 #include "STrackInfo.h"
         111 #include "spho.h"
         112 #endif
         113 #endif

         418 G4VParticleChange* InstrumentedG4OpBoundaryProcess::PostStepDoIt_(const G4Track& aTrack, const G4Step& aStep)
         419 {
         420     //[head
         421 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
         422     // formerly used U4PhotonInfo::GetIndex to pick up the label set 
         423     // in U4Recorder::PreUserTrackingAction_Optical for initially unlabelled input photons
         424     // pidx = U4PhotonInfo::GetIndex(&aTrack);    // TODO: now needs to be STrackInfo<spho>
         425 #ifdef WITH_CUSTOM4
         426     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(&aTrack);
         427     pidx = label->id ;
         428 #else
         429     spho* label = STrackInfo<spho>::GetRef(&aTrack);
         430     pidx = label->id ;
         431 #endif
         432     pidx_dump = pidx == PIDX ;
         433 #endif

         Using the label to access pidx and hence pidx_dump  



    ./u4/U4Track.h
    ./u4/tests/U4TrackInfoTest.cc
    ./u4/tests/U4TrackTest.cc
    ./u4/U4Recorder.cc

         451     spho ulabel = {} ;
         452     PreUserTrackingAction_Optical_GetLabel(ulabel, track);
         ...

         530 void U4Recorder::PreUserTrackingAction_Optical_GetLabel( spho& ulabel, const G4Track* track )
         531 {
         532 #ifdef WITH_CUSTOM4
         533     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
         534 #else
         535     spho* label = STrackInfo<spho>::GetRef(track);
         536 #endif
         537 
         538     if( label == nullptr ) // happens with torch gensteps and input photons
         539     {
         540         PreUserTrackingAction_Optical_FabricateLabel(track) ;
         541 #ifdef WITH_CUSTOM4
         542         label = C4TrackInfo<C4Pho>::GetRef(track);
         543 #else
         544         label = STrackInfo<spho>::GetRef(track);
         545 #endif
         546     }
         547     assert( label && label->isDefined() );
         548 
         549 #ifdef WITH_CUSTOM4
         550     assert( C4Pho::N == spho::N );
         551 #endif
         552     std::array<int,spho::N> a_label ;
         553     label->serialize(a_label) ;
         554 
         555     ulabel.load(a_label);
         556 
         557     // serialize/load provides firebreak between C4Pho and spho
         558     // so the SEvt doesnt need to depend on CUSTOM4
         559 }


         561 void U4Recorder::PreUserTrackingAction_Optical_FabricateLabel( const G4Track* track )
         562 {
         563     int rerun_id = SEventConfig::G4StateRerun() ;
         564     if( rerun_id > -1 )
         565     {
         566         LOG(LEVEL) << " setting rerun_id " << rerun_id ;
         567         G4Track* _track = const_cast<G4Track*>(track) ;
         568         U4Track::SetId(_track, rerun_id) ;
         569     }
         570 
         571 #ifdef WITH_CUSTOM4
         572     U4Track::SetFabricatedLabel<C4Pho>(track);
         573 #else
         574     U4Track::SetFabricatedLabel<spho>(track);
         575 #endif
         576 
         577 #ifdef WITH_CUSTOM4
         578     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
         579 #else
         580     spho* label = STrackInfo<spho>::GetRef(track);
         581 #endif
         582     assert(label) ;




    ./u4/U4.cc

         28 #ifdef WITH_CUSTOM4
         29 #include "C4GS.h"
         30 #include "C4Pho.h"
         31 #include "C4TrackInfo.h"
         32 #else
         33 #include "spho.h"
         34 #include "STrackInfo.h"
         35 #endif

         42 /**
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
         71 



WITH_CUSTOM4 is standard within JUNOSW, but not for Opticks::

    (ok) A[blyth@localhost junosw]$ jgr- WITH_CUSTOM4
    ./cmake/legacy/JUNODependencies.cmake:    set(CUSTOM4_DEFINITIONS ${Custom4_DEFINITIONS})   # -DWITH_CUSTOM4 for compiling
    ./python3.11.log:2025-03-26 11:12:32.561 INFO  [576358] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 14:41:07.937 INFO  [95368] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 14:42:35.277 INFO  [95409] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 15:47:22.226 INFO  [96848] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 15:53:57.132 INFO  [97083] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 16:15:44.081 INFO  [97796] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-04-07 16:18:37.592 INFO  [97896] [G4CXOpticks::setGeometry@329] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    ./python3.11.log:2025-05-20 10:25:48.794 INFO  [2397428] [G4CXOpticks::setGeometry@318] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    (ok) A[blyth@localhost junosw]$ 


C4 is used bare. jgl C4::

    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/R12860OnlyFrontPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./Simulation/SimSvc/MultiFilmLUTMakerSvc/MultiFilmLUTMakerSvc/MultiFilmLUTMakerSvc.hh
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc








