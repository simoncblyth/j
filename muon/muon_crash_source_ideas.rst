muon_crash_source_ideas
==========================

EPH labelling is done in all opticksMode, that 
could cause problems for other users of Geant4 UserTrackInformation.
I would have expected to get problems from that 
for all event types though, why muon has more of a problem ?



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





