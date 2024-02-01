U4HitGet_CPU_memory_leak_suspected
====================================


::

    epsilon:u4 blyth$ jgr U4HitGet 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#include "U4HitGet.h"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        U4HitGet::FromEvt_EGPU(hit, idx);   
    epsilon:junosw blyth$ 


::

    236 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    237 {
    238     G4CXOpticks* gx = G4CXOpticks::Get() ;
    239     gx->simulate(eventID) ;
    240 
    241     unsigned num_hit = SEvt::GetNumHit_EGPU() ;
    242 
    243     LOG(LEVEL)
    244         << " eventID " << eventID
    245         << " " << gx->descSimulate()
    246         << " num_hit " << num_hit
    247         ;
    248 
    249     int merged_count(0);
    250     int savehit_count(0);
    251     std::stringstream ss ;
    252 
    253     bool way_enabled = false ;
    254     U4Hit hit ;
    255     U4HitExtra hit_extra ;
    256     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    257     for(int idx=0 ; idx < int(num_hit) ; idx++)
    258     {
    259         U4HitGet::FromEvt_EGPU(hit, idx);
    260         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    261         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    262     }
    263 
    264     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;
    265 
    266     LOG(LEVEL)
    267         << "]"
    268         << " num_hit " << num_hit
    269         << ( merged_count > 0 ? " MERGED " : "" )
    270         << " merged_count  " << merged_count
    271         << " savehit_count  " << savehit_count
    272         << " m_merged_total " << m_merged_total
    273         << " m_savehit_total " << m_savehit_total
    274         << " m_opticksMode " << m_opticksMode
    275         ;
    276 
    277     m_merged_total += merged_count ;
    278     m_savehit_total += savehit_count ;
    279 
    280     TerminateEvent();
    281 }



U4HitGet::FromEvt_EGPU
------------------------




junoSD_PMT_v2_Opticks::collectHit
-----------------------------------

::

    320 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    321 {
    322     assert( m_pmthitmerger_opticks );
    323     bool merged = false ;
    324     if(m_pmthitmerger_opticks->getMergeFlag())
    325     {
    326         merged = m_pmthitmerger_opticks->doMerge(hit->sensor_identifier, hit->time);
    327     }
    328     if(merged)
    329     {
    330         merged_count += 1 ;
    331     }
    332     else
    333     {
    334         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    335         savehit_count += 1 ;
    336         m_pmthitmerger_opticks->saveHit(hit_photon);
    337     }
    338 }

Can hit_photon be deleted after merger saveHit ?:: 

    354 junoHit_PMT* junoSD_PMT_v2_Opticks::convertHit(const U4Hit* hit, const U4HitExtra* hit_extra ) const
    355 {
    356     junoHit_PMT* hit_photon = new junoHit_PMT();
    357 
    358     bool originalOP = !hit->is_reemission ;
    359     double edep = twopi*hbarc / hit->wavelength ;  // TODO:check units match with CPU hits 
    360 
    361     hit_photon->SetKineticEnergy(edep);
    362     hit_photon->SetOriginalOP(originalOP);
    363     hit_photon->SetCount(1);
    ...
    389     return hit_photon ;
    390 }


Nope, saveHit inserts hit_photon pointer into hitCollection (the owner?)::

     79 bool
     80 PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
     81   if (not hasNormalHitType()) {
     82     std::cerr << "WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted."
     83           << std::endl;
     84     return false;
     85   }
     86 
     87   if (m_merge_flag) {
     88     int pmtid = hit_photon->GetPMTID();
     89     std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.find(pmtid);
     90     if (pmt == m_PMThit.end()) {
     91       m_PMThit[pmtid].clear();
     92       m_PMThit[pmtid].push_back(hit_photon);
     93     }
     94     else pmt->second.push_back(hit_photon);
     95   }
     96   hitCollection->insert(hit_photon);
     97 
     98   return true;
     99 }



hitCollection instanciated for each event::

     175 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     176 {
     177     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     178     m_eventID = event->GetEventID() ;
     179 
     180     m_merge_count = 0 ;
     181     if (m_debug) {
     182         G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
     183     }
     184     hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
     185     hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);
     186 


jcv junoHit_PMT::

    146 // junoHit_PMT_Collection is a vector of hits
    147 typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;


    151 inline void* junoHit_PMT::operator new(size_t)
    152 {
    153   void *aHit;
    154   if (!junoHit_PMT_Allocator) {
    155       junoHit_PMT_Allocator = new G4Allocator<junoHit_PMT>;
    156   }
    157   aHit = (void *) junoHit_PMT_Allocator->MallocSingle();
    158   return aHit;
    159 }
    160 
    161 inline void junoHit_PMT::operator delete(void *aHit)
    162 {
    163   junoHit_PMT_Allocator->FreeSingle((junoHit_PMT*) aHit);
    164 }


* HMM DONT SEE WHERE HITS ARE GETTING DELETED 
* TODO: BT="junoHit_PMT::operator delete"


g4-cls G4THitsCollection::

    098       inline G4int insert(T* aHit)
    099       {
    100           if (!anHCAllocator_G4MT_TLS_) anHCAllocator_G4MT_TLS_ = new G4Allocator<G4HitsCollection>;
    101           std::vector<T*>*theHitsCollection = (std::vector<T*>*)theCollection;
    102         theHitsCollection->push_back(aHit);
    103         return theHitsCollection->size();
    104       }
    105       //  Insert a hit object. Total number of hit objects stored in this
    106       // collection is returned.


Where does hitCollection dealloc ?::

    107     private:
    108         junoHit_PMT_Collection* hitCollection;
    109         junoHit_PMT_muon_Collection* hitCollection_muon;


Look for other usage::

    jepsilon:issues blyth$ jgr saveHit 
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh: *                  2. saveHit, if not merge, create new hit and put it into collection
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT* hit);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT_muon* hit);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        m_pmthitmerger_opticks->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);                   
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT_muon* hit_photon) {
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    epsilon:junosw blyth$ 


