muon_crash_source_ideas
==========================

EPH labelling was done in all opticksMode, that 
could cause problems for other users of Geant4 UserTrackInformation.
I would have expected to get problems from that 
for all event types though, why muon has more of a problem ?


Non-optical crossings explain the former track info crash
---------------------------------------------------------------

Actually in opticksMode:1 why is junoSD_PMT_v2::ProcessHits 
being called at all ? There should be no CPU side photons ?
Maybe from non-photons landing on detectors destined to
be is_hit:false ? 

YES : confirmed this from SProcessHits_EPH::desc 
also the low stats of non-optical crossings explains why 
only got the problems with muon.


~/j/zhanghaosen/Muon_Test2/run/run1_5.sh : check EPH stats
------------------------------------------------------------

::

    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2025-06-25 10:46:38.047 INFO  [310536] [QSim::simulate@430]  eventID      0 igs (109951, 6, 4, ) MaxSlot 262000000 MaxSlot/M 262 sslice::Desc(igs_slice)
    sslice::Desc num_slice 1 TotalPhoton 28703618
                    start  stop   offset    count 
       0 : sslice {     0,109951,       0,28703618}
                    start  stop   offset    count 
     num_slice 1
    2025-06-25 10:46:38.047 INFO  [310536] [QSim::simulate@448]    0 : sslice {     0,109951,       0,28703618}
    //qcerenkov::wavelength_sampled_bndtex idx 5309732 sampledRI   1.791 cosTheta   0.905 sin2Theta   0.182 wavelength 158.254 count 55 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 9706831 sampledRI   1.787 cosTheta   0.922 sin2Theta   0.150 wavelength 153.729 count 75 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 16527759 sampledRI   1.790 cosTheta   0.907 sin2Theta   0.177 wavelength 157.431 count 56 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 24044276 sampledRI   1.754 cosTheta   0.950 sin2Theta   0.098 wavelength 147.401 count 52 matline 39 
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder NO  eph_meta -
    [SProcessHits_EPH::desc
                                     ProcessHits_count         387
                                      ProcessHits_true           0
                                     ProcessHits_false         387
                                     SaveNormHit_count           0
                                     SaveMuonHit_count           0
                                             EPH_UNSET           0
                                              EPH_NDIS           0
                                              EPH_NOPT         387
                                             EPH_NEDEP           0
                                            EPH_NBOUND           0
                                             EPH_NPROC           0
                                           EPH_NDETECT           0
                                           EPH_NDECULL           0
                                            EPH_YMERGE           0
                                             EPH_YSAVE           0
                                          EPH_SAVENORM           0
                                          EPH_SAVEMUON           0
                Initialize_G4HCofThisEvent_opticksMode           1
                      Initialize_G4HCofThisEvent_count           1
                           EndOfEvent_Simulate_eventID           0
                             EndOfEvent_Simulate_count           1
                          EndOfEvent_Simulate_EGPU_hit     4765712
                     EndOfEvent_hitCollection_entries0           0
                     EndOfEvent_hitCollection_entries1     1978638
                  EndOfEvent_hitCollectionAlt_entries0           0
                  EndOfEvent_hitCollectionAlt_entries1           0
                      EndOfEvent_Simulate_merged_count     2787074
                     EndOfEvent_Simulate_savehit_count     1978638    ## 2787074 + 1978638 = 4765712
                      EndOfEvent_Simulate_merged_total     2787074
                     EndOfEvent_Simulate_savehit_total     1978638
    ]SProcessHits_EPH::desc

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 1978638 hitCollectionAlt -1 hcMuon 0 GPU YES



::

    A[blyth@localhost junosw]$ jgr EndOfEvent_Simulate_EGPU_hit
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    m_eph_stats->EndOfEvent_Simulate_EGPU_hit = num_hit ;




BP=junoSD_PMT_v2::ProcessHits ~/j/zhanghaosen/Muon_Test2/run/run1_5.sh
-------------------------------------------------------------------------



New junoSD_PMT_v2::ProcessHits  that does not label in m_opticksMode:1
------------------------------------------------------------------------

::

     349 #ifdef WITH_G4CXOPTICKS_EPH
     350 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     351 {
     352     G4bool is_hit = ProcessHits_(step, nullptr) ;
     353     m_eph_stats->add( m_eph, is_hit ); // increment counters
     354 
     355     bool set_eph_track_label = m_opticksMode != 1 && m_eph_nolabel == false ;
     356     if(set_eph_track_label)
     357     {
     358         G4Track* track = step->GetTrack() ;
     359 
     360         C4Track::SetLabelEph(track, m_eph);
     361         C4Track::IncrementLabelExt(track) ;
     362 
     363         int label_id = C4Track::GetLabelID(track);
     364         LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     365     }
     366 
     367     return is_hit ;
     368 }
     369 
     370 SProcessHits_EPH* junoSD_PMT_v2::getProcessHits_EPH() const
     371 {
     372     return m_eph_stats ;
     373 }
     374 
     375 
     376 #endif



Old junoSD_PMT_v2::ProcessHits that always does eph labelling of tracks
---------------------------------------------------------------------------

::


     347 #ifdef WITH_G4CXOPTICKS_EPH
     348 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     349 {
     350     G4bool is_hit = ProcessHits_(step, nullptr) ;
     351     m_eph_stats->add( m_eph, is_hit );
     352 
     353     G4Track* track = step->GetTrack() ;
     354     int label_id = C4Track::GetLabelID(track);
     355 
     356     C4Track::SetLabelEph(track, m_eph);
     357     C4Track::IncrementLabelExt(track) ;
     358 
     359     LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     360 
     361     return is_hit ;
     362 }
     363 
     364 SProcessHits_EPH* junoSD_PMT_v2::getProcessHits_EPH() const
     365 {
     366     return m_eph_stats ;
     367 }
     368 
     369 
     370 #endif


     70 inline void C4Track::SetLabelValue(const G4Track* track, int i, int val )
     71 {
     72     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
     73     if(label == nullptr) return ;
     74     label->set_value(i, val );
     75 }
     76 inline void C4Track::IncrementLabelValue(const G4Track* track, int i )
     77 {
     78     C4Pho* label = C4TrackInfo<C4Pho>::GetRef(track);
     79     if(label == nullptr) return ;
     80     label->increment_value(i);
     81 }
     82 
     83 inline int C4Track::GetLabelGen(const G4Track* track){ return GetLabelValue(track, GEN) ; }
     84 inline int C4Track::GetLabelEph(const G4Track* track){ return GetLabelValue(track, EPH) ; }
     85 inline int C4Track::GetLabelExt(const G4Track* track){ return GetLabelValue(track, EXT) ; }
     86 inline int C4Track::GetLabelFlg(const G4Track* track){ return GetLabelValue(track, FLG) ; }
     87 
     88 inline void C4Track::SetLabelGen(const G4Track* track, int gen ){ SetLabelValue(track, GEN, gen ) ; }
     89 inline void C4Track::SetLabelEph(const G4Track* track, int eph ){ SetLabelValue(track, EPH, eph ) ; }
     90 inline void C4Track::SetLabelExt(const G4Track* track, int ext ){ SetLabelValue(track, EXT, ext ) ; }
     91 inline void C4Track::SetLabelFlg(const G4Track* track, int flg ){ SetLabelValue(track, FLG, flg ) ; }
     92 
     93 inline void C4Track::IncrementLabelGen(const G4Track* track){ IncrementLabelValue(track, GEN ); }
     94 inline void C4Track::IncrementLabelEph(const G4Track* track){ IncrementLabelValue(track, EPH ); }
     95 inline void C4Track::IncrementLabelExt(const G4Track* track){ IncrementLabelValue(track, EXT ); }
     96 inline void C4Track::IncrementLabelFlg(const G4Track* track){ IncrementLabelValue(track, FLG ); }
     97 





