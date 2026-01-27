branch-cleanup/index
========================


I have a lots of branches some of which have been merged to main and some not. How to check the status of each and delete the ones that have been merged ?


initial 15 branches
----------------------

::

    (ok) A[blyth@localhost junosw]$ git branch 
      Chenjing-EMFcoilsgeometry
      blyth-DataModelWriterWithSplit-add-debug-and-protection-for-unexpected-pmtid
      blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
      blyth-OJ-pmt-hit-type-2-for-muon-hits
      blyth-add-optional-branch-name-after-InstallArea-and-build-dirs-plus-ci-JUNOTOP-to-JLatest
      blyth-fix-opticks-PMT-serialization-issue-from-partial-addition-of-600-MPMT
      blyth-gitlab-ci-oj_helper-collect-CI-envvars
      blyth-gitlab-ci-oj_helper-collect-CI-envvars-with-quotes
      blyth-oj-local-geometry-customization
    * main
      yangxuhui
      yupd-8inch-pmt
      yupd-water-distributor
      yupd_bottompipe_adjust
      yupd_geo_bugfix
      yupd_waterdistributor_heightfix
    (ok) A[blyth@localhost junosw]$ 


* search for corresponding MR in gitlab web interface using "source-branch" field
  to see the merge status then delete the ones that have been merged with::

   git branch -d yupd_waterdistributor_heightfix


after some cleanup down to 3
-------------------------------

(ok) A[blyth@localhost junosw]$ git branch
  Chenjing-EMFcoilsgeometry
  blyth-NormalTrackInfo-C4Pho-label-Opticks-integration
  blyth-OJ-pmt-hit-type-2-for-muon-hits
* main



Chenjing-EMFcoilsgeometry : STILL REVIEWING THIS ONE
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



blyth-NormalTrackInfo-C4Pho-label-Opticks-integration : do not find corresponding MR and looks aborted : WRONG DANGEROUS CAST APPROACH ANYHOW  
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* TODO: DELETE THIS AFTER THE SOMEWHAT RELATED blyth-OJ-pmt-hit-type-2-for-muon-hits BRANCH IS HANDLED

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/tree/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration?ref_type=heads

Just the one commit, but its using dangerous casts to NormalTrackInfo so not a good approach

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/commit/22ee7520d9f22046aacc6c07e4cb0e92e102e480


::


    2025-06-07 22ee7520 - (origin/blyth-NormalTrackInfo-C4Pho-label-Opticks-integration, blyth-NormalTrackInfo-C4Pho-label-Opticks-integration) changing NormalTrackInfo has difficulties, so defer the spearate label approach (8 months ago) <Simon C Blyth>
    *   2025-06-02 ada95832 - (tag: J25.4.0) Merge branch 'lintao/release/J25.4.0' into 'main' (8 months ago) <lintao@ihep.ac.cn>
    |\  
    | * 2025-06-02 95f8da8f - Release J25.4.0 (8 months ago) <lintao@ihep.ac.cn>
    |/  


::

    #ifdef WITH_NORMAL_LABEL
    void U4RecorderAnaMgr::PreUserTrackingAction( const G4Track* trk) { m_recorder->PreUserTrackingAction_(  trk, LabelData(trk)); }
    void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction_( trk, LabelData(trk)); }
    #else
    void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* ) {} 
    void U4RecorderAnaMgr::EndOfRunAction(const G4Run* ) {} 
    void U4RecorderAnaMgr::PreUserTrackingAction( const G4Track* trk) { m_recorder->PreUserTrackingAction(  trk ); }
    void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction( trk ); }
    #endif


    void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }

    int* U4RecorderAnaMgr::LabelData( const G4Track* trk )  // static
    {
    #ifdef WITH_NORMAL_LABEL
        NormalTrackInfo* ui = (NormalTrackInfo*)(trk->GetUserInformation());
        int* label_data =  ui ? ui->getLabelData() : nullptr ;
    #else
        int* label_data = nullptr ; 
    #endif
        return label_data ;
    }

    #else
    void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* ) {}
    void U4RecorderAnaMgr::EndOfRunAction(const G4Run* ) {}
    void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* ) {}
    void U4RecorderAnaMgr::EndOfEventAction(const G4Event* ) {}
    void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* ) {}
    void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* ) {}
    void U4RecorderAnaMgr::UserSteppingAction(const G4Step* ) {}
    int* U4RecorderAnaMgr::LabelData( const G4Track* trk ){ return nullptr ; }

    #endif


blyth-OJ-pmt-hit-type-2-for-muon-hits : NO CORRESPONDING MR
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



::

    (ok) A[blyth@localhost junosw]$ git lg blyth-OJ-pmt-hit-type-2-for-muon-hits
    * 2025-12-08 a65ea362 - (origin/blyth-OJ-pmt-hit-type-2-for-muon-hits, blyth-OJ-pmt-hit-type-2-for-muon-hits) temporarily skip setting OPTICKS_MODE_MERGE as want to compare performance with and without (7 weeks ago) <Simon C Blyth>
    * 2025-12-08 b2a6795d - switch to new FullHit impl removing pointless intermediary U4Hit (7 weeks ago) <Simon C Blyth>
    * 2025-12-01 cbe401b9 - start revival of opticksMode:0 for standard CPU simulation with some Opticks instrumentation (8 weeks ago) <Simon C Blyth>
    * 2025-12-01 03087ce2 - make it explicit that SEventConfig::ModeMerge dictates if the hits are premerged or not (8 weeks ago) <Simon C Blyth>
    * 2025-12-01 6dd97627 - explicitly restrict use of Geant4 track info to opticksMode 3 (8 weeks ago) <Simon C Blyth>
    * 2025-12-01 4b526503 - overhaul NormalTrackInfo and its usage, replacing all dangerous C-style casts with dynamic cast from static helper NormalTrackInfo::FromTrack, add standalone test and optional degug registry functionality (8 weeks ago) <Simon C Blyth>
    * 2025-12-01 e7ba84bd - replace all? python print with log.info for time stamping and consistency (8 weeks ago) <Simon C Blyth>
    * 2025-11-25 2319df6f - add JLog.h which provides J::Log for millisecond formatted time stamps (9 weeks ago) <Simon C Blyth>
    * 2025-11-25 f01f65a4 - enable Opticks hitlitemerged for pmt_hit_type:2 hitmerged not yet impl (9 weeks ago) <Simon C Blyth>
    * 2025-11-14 a5231d99 - add EndOfEvent_CollectMuonHits_premerged that handles hitlite arrays that have been merged already, old traditional PMTHitMerger approach is moved to EndOfEvent_CollectMuonHits_cpumerge (2 months ago) <Simon C Blyth>
    * 2025-11-14 e703d28a - improve python logging of the init methods, add init_opticks_environ that passes pmt hit type and merge window config to Opticks (2 months ago) <Simon C Blyth>
    * 2025-11-12 1fe32f2e - use new opticks photonlite/hitlite to implement junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits not yet assuming GPU hit merging (3 months ago) <Simon C Blyth>
    * 2025-11-04 deeae12d - working out whats needed to get muon hits from sphotonlite hitlite array (3 months ago) <Simon C Blyth>
    *   2025-10-29 429466da - Merge branch 'blyth-fix-opticks-PMT-serialization-issue-from-partial-addition-of-600-MPMT' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\  
    | * 2025-10-29 4976b4ff - Avoids Opticks PMT serialization inconsistency between PMTParamData and PMTSimParamData by collecting added pmtNum info from PMTParamData (3 months ago) <blyth@ihep.ac.cn>
    * |   2025-10-29 8abae80c - Merge branch 'lintao/reprod25c/enable-trigger-edm-in-esd' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\ \  
    | |/  
    |/|   
    | * 2025-10-29 0bacd2b5 - WIP: enable cd and wp trigger in ESD. (3 months ago) <Tao Lin>
    |/  
    *   2025-10-24 b0890f6f - Merge branch 'lintao/rootio-dump/skimming' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\  
    | * 2025-10-24 17da8cef - WIP: support skimming in rootio-dump (3 months ago) <lintao@ihep.ac.cn>
    |/  








