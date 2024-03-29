FIXED : lack_hits_at_j_level_but_are_there_at_SEvt_level
==========================================================

Overview
---------

FIX was to reposition the SEvt::gather invokation up to QSim::simulate 
immediately after the launch : so the hits are available for 
copying prior to QSim::simulate_end is called. 


HMM : tis a when to gather issue
-----------------------------------

Inbetween the QSim::simulate and QSim::simulate_end calls 
the arrays need to have been gathered. 
So need to split the gather from the save. 


::

    void SEvt::save(const char* dir_)
    {
        LOG_IF(info, LIFECYCLE) << id() ;
        gather();


    void SEvt::endOfEvent(int eventID)
    {
        LOG_IF(error, gather_done) << " gather_done SKIP eventID " << eventID ; 
        if(gather_done) return ; 

        setStage(SEvt__endOfEvent); 
        LOG_IF(info, LIFECYCLE) << id() ; 
        sprof::Stamp(p_SEvt__endOfEvent_0);  

        endIndex(eventID);   // eventID is 0-based 
        endMeta(); 

        save();              // gather and save SEventConfig configured arrays
        clear_output(); 
        clear_genstep(); 


::

     348 double QSim::simulate(int eventID, bool end)
     349 {   
     350     SProf::Add("QSim__simulate_HEAD");
     351     
     352     LOG_IF(info, SEvt::LIFECYCLE) << "[ eventID " << eventID ;
     353     if( event == nullptr ) return -1. ;
     354     
     355     sev->beginOfEvent(eventID);  // set SEvt index and tees up frame gensteps for simtrace and input photon simulate running
     356     
     357     int rc = event->setGenstep() ;    // QEvent 
     358     LOG_IF(error, rc != 0) << " QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate " ;
     359     
     360     SProf::Add("QSim__simulate_PREL");
     361     
     362     sev->t_PreLaunch = sstamp::Now() ; 
     363     double dt = rc == 0 && cx != nullptr ? cx->simulate_launch() : -1. ;  //SCSGOptiX protocol
     364     sev->t_PostLaunch = sstamp::Now() ;
     365     sev->t_Launch = dt ;
     366     
     367     SProf::Add("QSim__simulate_POST");
     368     
     369     sev->gather();
     370     
     371     SProf::Add("QSim__simulate_TAIL");







Issue
--------


::

    2023-12-15 14:06:11.349 ERROR [364146] [G4CXOpticks::SensitiveDetector_Initialize@531]  eventID 4
    2023-12-15 14:06:11.349 INFO  [364146] [U4Recorder::BeginOfEventAction_@292]  eventID 4
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 4 LEVEL 5:DEBUG
    Begin of Event --> 4
    2023-12-15 14:06:11.351 INFO  [364146] [U4Recorder::PreUserTrackingAction_Optical@392]  modulo 100000 : ulabel.id 0
    2023-12-15 14:06:12.395 ERROR [364146] [G4CXOpticks::SensitiveDetector_EndOfEvent@581]  eventID 4
    2023-12-15 14:06:12.451 INFO  [364146] [SEvt::save@3942] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/B004 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 4 opticksMode 3 with m_jpmt_dbg YES
    2023-12-15 14:06:12.477 INFO  [364146] [QSim::simulate@371]  eventID 4 dt    0.010011 ph       9044 ph/M          0 end NO 
    junoSD_PMT_v2_Opticks::EndOfEvent_Simulate] num_hit 0 merged_count  0 savehit_count  0 m_merged_total 0 m_savehit_total 0 m_opticksMode 3
    2023-12-15 14:06:12.530 INFO  [364146] [SEvt::save@3942] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A004 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 3 hitCollection 1649 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (5) 
    junoSD_PMT_v2::Initialize eventID 5
    2023-12-15 14:06:12.565 ERROR [364146] [G4CXOpticks::SensitiveDetector_Initialize@531]  eventID 5
    2023-12-15 14:06:12.565 INFO  [364146] [U4Recorder::BeginOfEventAction_@292]  eventID 5
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 5 LEVEL 5:DEBUG
    Begin of Event --> 5
    2023-12-15 14:06:12.566 INFO  [364146] [U4Recorder::PreUserTrackingAction_Optical@392]  modulo 100000 : ulabel.id 0
    2023-12-15 14:06:12.566 INFO  [364146] [U4Recorder::PreUserTrackingAction_Optical@392]  modulo 100000 : ulabel.id 0
    2023-12-15 14:06:13.552 ERROR [364146] [G4CXOpticks::SensitiveDetector_EndOfEvent@581]  eventID 5
    2023-12-15 14:06:13.610 INFO  [364146] [SEvt::save@3942] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/B005 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 5 opticksMode 3 with m_jpmt_dbg YES
    2023-12-15 14:06:13.636 INFO  [364146] [QSim::simulate@371]  eventID 5 dt    0.009305 ph       9336 ph/M          0 end NO 
    junoSD_PMT_v2_Opticks::EndOfEvent_Simulate] num_hit 0 merged_count  0 savehit_count  0 m_merged_total 0 m_savehit_total 0 m_opticksMode 3
    2023-12-15 14:06:13.690 INFO  [364146] [SEvt::save@3942] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A005 genstep,photon,record,seq,hit,domain,inphoton
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 3 hitCollection 1621 hcMuon 0 hcOpticks 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (6) 
    junoSD_PMT_v2::Initialize eventID 6


::

     705 /**
     706 QEvent::getNumHit  TODO:rejig 
     707 -----------------------------------
     708 
     709 HMM: applies selector to the GPU photon array, thats surprising 
     710 for a "get" method... TODO: maybe rearrange to do that once only 
     711 at the gatherHit stage and subsequently just get the count from 
     712 SEvt::fold 
     713 
     714 **/
     715 
     716 
     717 unsigned QEvent::getNumHit() const
     718 {
     719     assert( evt->photon );
     720     assert( evt->num_photon );
     721 
     722     evt->num_hit = SU::count_if_sphoton( evt->photon, evt->num_photon, *selector );
     723 
     724     LOG(LEVEL) << " evt.photon " << evt->photon << " evt.num_photon " << evt->num_photon << " evt.num_hit " << evt->num_hit ;
     725     return evt->num_hit ;
     726 }

