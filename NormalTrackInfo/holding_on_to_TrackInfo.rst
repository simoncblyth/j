
67 void junoSD_PMT::SimpleHit( const ParamsForSD_PMT& params )
 68 {
 69   if (m_merge_flag) {
 70       bool ok = doMerge(params);
 71       if (ok) {
 72           return;
 73       }
 74   }
 75   // create new juno hit photon, the way of recording photo hits on PMTs
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
116   G4int idx = hitCollection->insert(hit_photon);
117   if (m_merge_flag) {
118       m_pmtid2idincol.insert( std::pair<int, int>( params.ipmt, idx-1 ) );
119   }



