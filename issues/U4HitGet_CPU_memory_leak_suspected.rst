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


Changed j/okjob.sh to use current (not the release).


Try hit operator breaking::

   jre 
   BP="junoHit_PMT::operator new" ~/j/okjob.sh 
   BP="junoHit_PMT::operator delete" ~/j/okjob.sh 


Methods with spaces dont work, need to define the break point manually::

    Function "junoHit_PMT::operator" not defined.
    Breakpoint 1 (junoHit_PMT::operator) pending.
    Function "new" not defined.
    Breakpoint 2 (new) pending.
    Num     Type           Disp Enb Address    What
    1       breakpoint     keep y   <PENDING>  junoHit_PMT::operator
    2       breakpoint     keep y   <PENDING>  new


::

    (gdb) b "junoHit_PMT::operator new"
    Breakpoint 3 at 0x7fffc7722890 (4 locations)
    (gdb) r


::


    Thread 1 "python" hit Breakpoint 3, 0x00007fffc7722890 in junoHit_PMT::operator new(unsigned long)@plt () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    (gdb) bt
    #0  0x00007fffc7722890 in junoHit_PMT::operator new(unsigned long)@plt () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    #1  0x00007fffc77de189 in junoSD_PMT_v2_Opticks::convertHit (this=0x8c16950, hit=0x7ffffffec340, hit_extra=0x0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:245
    #2  0x00007fffc77de12f in junoSD_PMT_v2_Opticks::collectHit (this=0x8c16950, hit=0x7ffffffec340, hit_extra=0x0, merged_count=@0x7ffffffec418: 0, savehit_count=@0x7ffffffec414: 0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:223
    #3  0x00007fffc77ddbc8 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x8c16950, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:189
    #4  0x00007fffc77dd7ba in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x8c16950, eventID=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:145
    #5  0x00007fffc77db1c1 in junoSD_PMT_v2::EndOfEvent (this=0x8c16070, HCE=0xa58d5840) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1093
    #6  0x00007fffced1d0da in G4SDStructure::Terminate(G4HCofThisEvent*) ()

    (gdb) b "junoHit_PMT::operator delete"
    Breakpoint 4 at 0x7fffc771f470 (4 locations)
    (gdb) 




Geant4 handles hit deletion in G4HCofThisEvent dtor, presumably as the hitCollection was registered with the G4Event::

    (gdb) d 3
    (gdb) c
    Continuing.
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 1701 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0

    Thread 1 "python" hit Breakpoint 4, 0x00007fffc771f470 in junoHit_PMT::operator delete(void*)@plt () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    (gdb) bt
    #0  0x00007fffc771f470 in junoHit_PMT::operator delete(void*)@plt () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    #1  0x00007fffc77ca2ee in junoHit_PMT::~junoHit_PMT (this=0xb1c424d0, __in_chrg=<optimized out>) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoHit_PMT.cc:32
    #2  0x00007fffc77d7bda in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xa58d5c40, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:165
    #3  0x00007fffc77d7c4c in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xa58d5c40, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:168
    #4  0x00007fffced2616b in G4HCofThisEvent::~G4HCofThisEvent() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #5  0x00007fffd0d95873 in G4Event::~G4Event() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffd0e36818 in G4RunManager::StackPreviousEvent(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007fffc7deb6db in G4SvcRunManager::SimulateEvent (this=0x58ca480, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:32
    #8  0x00007fffc75d1d3e in DetSimAlg::execute (this=0x5e05250) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #9  0x00007fffd4e01511 in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



