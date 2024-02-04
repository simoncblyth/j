U4HitGet_CPU_memory_leak_suspected
====================================


::

    epsilon:u4 blyth$ jgr U4HitGet 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#include "U4HitGet.h"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        U4HitGet::FromEvt_EGPU(hit, idx);   
    epsilon:junosw blyth$ 




U4HitGet::FromEvt_EGPU
------------------------


Cannot update until fix the unorderd map issue
-----------------------------------------------------

::

    n file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'void _PMTSimParamData::populate_SPMT()':
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:143:32: warning: implicitly-declared 'constexpr PmtSimData_SPMT& PmtSimData_SPMT::operator=(const PmtSimData_SPMT&)' is deprecated [-Wdeprecated-copy]
      143 |         data.pd_map_SPMT[id] = spmt ;
          |                                ^~~~
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:42,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:368:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h:29:3: note: because 'PmtSimData_SPMT' has user-provided 'PmtSimData_SPMT::PmtSimData_SPMT(const PmtSimData_SPMT&)'
       29 |   PmtSimData_SPMT(const PmtSimData_SPMT &others)
          |   ^~~~~~~~~~~~~~~
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h: In member function 'NPFold* _PMTSimParamData::serialize() const':
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:219:52: error: cannot convert 'std::unordered_map<int, int>' to 'const std::map<int, int>&'
      219 |     NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ;
          |                                               ~~~~~^~~~~~~~~~~~~~~~~~
          |                                                    |
          |                                                    std::unordered_map<int, int>
    In file included from /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPFold.h:91,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:5,
                     from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NPX.h:583:55: note:   initializing argument 1 of 'static NP* NPX::ArrayFromMap(const std::map<int, S>&, bool) [with T = int; S = int]'
      583 | inline NP* NPX::ArrayFromMap( const std::map<int, S>& m, bool contiguous_key )
          |                               ~~~~~~~~~~~~~~~~~~~~~~~~^
    In file included from /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:37,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:369:
    /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:220:51: error: cannot convert 'std::unordered_map<int, int>' to 'const std::map<int, int>&'
      220 |     NP* pmtCat = NPX::ArrayFromDiscoMap<int>(data.m_all_pmt_category) ;
          |                                              ~~~~~^~~~~~~~~~~~~~~~~~
          |                                                   |
          |                                                   std::unordered_map<int, int>






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

Can hit_photon be deleted after merger saveHit ? NO:: 

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


* the above "new junoHit_PMT" looks like a leak, but it is not because
  the hitCollection that the hit is added to is registered with Geant4,
  so the G4HCofThisEvent::~G4HCofThisEvent imvokes the delete of the hit
  

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


* HMM DONT SEE WHERE HITS ARE GETTING DELETED : GEANT4 DOES IT, AS DETERMINED WITH GDB


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


::

    jre
    N[blyth@localhost j]$ BP="junoHit_PMT::operator new,junoHit_PMT::operator delete" ~/j/okjob.sh 


    (gdb) f 6
    #6  0x00007fffd0e36818 in G4RunManager::StackPreviousEvent(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    (gdb) f 5
    #5  0x00007fffd0d95873 in G4Event::~G4Event() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    (gdb) f 4
    #4  0x00007fffced2616b in G4HCofThisEvent::~G4HCofThisEvent() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    (gdb) f 3
    #3  0x00007fffc77d7c4c in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xa58d6b30, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:168
    168	}
    (gdb) f 2
    #2  0x00007fffc77d7bda in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xa58d6b30, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:165
    165	  { delete (*theHitsCollection)[i]; }
    (gdb) f 1
    #1  0x00007fffc77ca2ee in junoHit_PMT::~junoHit_PMT (this=0xb1c3ff30, __in_chrg=<optimized out>) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoHit_PMT.cc:32
    warning: Source file is more recent than executable.
    32	{;}
    (gdb) 




Yuxiang found that not doing the below reduces the leak::


    183     U4Hit hit ;
    184     U4HitExtra hit_extra ;
    185     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    186     for(int idx=0 ; idx < int(num_hit) ; idx++)
    187     {
    188         U4HitGet::FromEvt_EGPU(hit, idx);
    189         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    190         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    191     }
    192 
    193     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;



U4HitGet is just shuffling content from two stack sphoton to a stack U4Hit 
so no leaking is possible ? (NOT SO SURE NOW : SPROF ANALYSIS IS POINTING HERE)::

     27 inline void U4HitGet::ConvertFromPhoton(U4Hit& hit,  const sphoton& global, const sphoton& local, const sphit& ht )
     28 {
     29     hit.zero();
     30 
     31     U4ThreeVector::FromFloat3( hit.global_position,      global.pos );
     32     U4ThreeVector::FromFloat3( hit.global_direction,     global.mom );
     33     U4ThreeVector::FromFloat3( hit.global_polarization,  global.pol );
     34 
     35     hit.time = double(global.time) ;
     36     hit.weight = 1. ;
     37     hit.wavelength = double(global.wavelength);
     38 
     39     U4ThreeVector::FromFloat3( hit.local_position,      local.pos );
     40     U4ThreeVector::FromFloat3( hit.local_direction,     local.mom );
     41     U4ThreeVector::FromFloat3( hit.local_polarization,  local.pol );
     42 
     43     hit.sensorIndex = ht.sensor_index ;
     44     hit.sensor_identifier = ht.sensor_identifier ;
     45     hit.nodeIndex = -1 ;
     46 
     47     hit.boundary = global.boundary() ;
     48     hit.photonIndex = global.idx() ;
     49     hit.flag_mask = global.flagmask ;
     50     hit.is_cerenkov = global.is_cerenkov() ;
     51     hit.is_reemission = global.is_reemit() ;
     52 }
     53 
     54 
     55 inline void U4HitGet::FromEvt_EGPU(U4Hit& hit, unsigned idx ){ FromEvt(hit, idx, SEvt::EGPU); }
     56 inline void U4HitGet::FromEvt_ECPU(U4Hit& hit, unsigned idx ){ FromEvt(hit, idx, SEvt::ECPU); }
     57 inline void U4HitGet::FromEvt(U4Hit& hit, unsigned idx, int eidx )
     58 {
     59     sphoton global ; 
     60     sphoton local ;
     61 
     62     SEvt* sev = SEvt::Get(eidx);
     63     sev->getHit( global, idx);
     64 
     65     sphit ht ;  // extra hit info : iindex, sensor_identifier, sensor_index
     66     sev->getLocalHit( ht, local,  idx);
     67 
     68     ConvertFromPhoton(hit, global, local, ht );
     69 }
     70 


::

    4193 void SEvt::getHit(sphoton& p, unsigned idx) const
    4194 {
    4195     const NP* hit = getHit();
    4196     sphoton::Get(p, hit, idx );
    4197 }


    4243 void SEvt::getLocalHit(sphit& ht, sphoton& lp, unsigned idx) const
    4244 {
    4245     getHit(lp, idx);   // copy *idx* hit from NP array into sphoton& lp struct 
    4246 
    4247     sframe fr ;
    4248     getPhotonFrame(fr, lp);
    4249     fr.transform_w2m(lp);
    4250 
    4251     ht.iindex = fr.inst() ;
    4252     ht.sensor_identifier = fr.sensor_identifier() - 1 ;
    4253     ht.sensor_index = fr.sensor_index();
    4254 }
    4255 
    4256 /**
    4257 SEvt::getPhotonFrame
    4258 ---------------------
    4259 
    4260 Note that this relies on the photon iindex which 
    4261 may not be set for photons ending in some places. 
    4262 It should always be set for photons ending on PMTs
    4263 assuming properly instanced geometry. 
    4264 
    4265 **/
    4266 
    4267 void SEvt::getPhotonFrame( sframe& fr, const sphoton& p ) const
    4268 {
    4269     assert(cf);
    4270     cf->getFrame(fr, p.iindex);
    4271     fr.prepare();
    4272 }



    383 /**
    384 G4CXOpticks::reset
    385 ---------------------
    386 
    387 This needs to be called after invoking G4CXOpticks::simulate
    388 when argument reset:false has been used in order to allow copy hits 
    389 from the opticks/SEvt into other collections prior to invoking 
    390 the reset. 
    391 
    392 **/
    393 
    394 void G4CXOpticks::reset(int eventID)
    395 {
    396     LOG_IF(fatal, NoGPU) << "NoGPU SKIP" ;
    397     if(NoGPU) return ;
    398 
    399     assert( SEventConfig::IsRGModeSimulate() );
    400     assert(qs);
    401 
    402     unsigned num_hit_0 = SEvt::GetNumHit_EGPU() ;
    403     LOG(LEVEL) << "[ " << eventID << " num_hit_0 " << num_hit_0  ;
    404 
    405     qs->reset(eventID);
    406 
    407     unsigned num_hit_1 = SEvt::GetNumHit_EGPU() ;
    408     LOG(LEVEL) << "] " << eventID << " num_hit_1 " << num_hit_1  ;
    409 }
    410 


    0392 /**
     393 QSim::reset
     394 ------------
     395 
     396 When *QSim::simulate* is called with argument *reset:true* the
     397 *QSim::reset* method is called automatically to clean 
     398 up the SEvt after saving any configured arrays.
     399 
     400 When *QSim::simulate* is called with argument *reset:false*
     401 (in order to copy gathered arrays into non-Opticks collections)  
     402 the *QSim::reset* method must be called to avoid a memory leak. 
     403 
     404 **/
     405 void QSim::reset(int eventID)
     406 {
     407     sev->endOfEvent(eventID);
     408     LOG_IF(info, SEvt::LIFECYCLE) << "] eventID " << eventID ;
     409 }



::

     232 QSim::QSim()
     233     :
     234     base(QBase::Get()),
     235     event(new QEvent),
     236     sev(event->sev),


     095 QEvent::QEvent()
      96     :
      97     sev(SEvt::Get_EGPU()),
      98     selector(sev ? sev->selector : nullptr),
      99     evt(sev ? sev->evt : nullptr),
     100     d_evt(QU::device_alloc<sevent>(1,"QEvent::QEvent/sevent")),
     101     gs(nullptr),
     102     input_photon(nullptr),
     103     upload_count(0)
     104 {




Observations : note that SEvt_ECPU is not reset here. Its up to U4Recorder 
to manage that.  BUT that should not be used in production/measuement running anyhow.  


Plotting the leak with sysrap/tests/sleak.sh 
----------------------------------------------

::

    DRM=1 YLIM=0,3 ~/o/sysrap/tests/sleak.sh ana 

* RSS per event leak is around 2 MB 
* it jumps around within 0.2 MB range 
* it declines gradually across the 1000 events measured

BUT the place the profiles are collected (see below)
is misleading because the end stamp profile is before the reset

So instead compare just start stamps from event to event
to give DRM.  This gives a per event CPU leak of 
about 2.2 MB in 0.2MB range that is flat across the 1000 events.  


jcv junoSD_PMT_v2_Opticks::

    162 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    163 {
    164     G4CXOpticks* gx = G4CXOpticks::Get() ;
    165 
    166     bool reset_ = false ;
    167     gx->simulate(eventID, reset_ ) ;
    168 
    169     assert( m_merger );
    170 
    171     std::stringstream ss ;
    172     unsigned num_hit = SEvt::GetNumHit_EGPU() ;
    173     LOG(LEVEL)
    174         << "[ eventID " << eventID
    175         << " " << gx->descSimulate()
    176         << " num_hit " << num_hit
    177         ;
    178 
    179     int merged_count(0);
    180     int savehit_count(0);
    181     bool way_enabled = false ;
    182 
    183     U4Hit hit ;
    184     U4HitExtra hit_extra ;
    185     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    186     for(int idx=0 ; idx < int(num_hit) ; idx++)
    187     {
    188         U4HitGet::FromEvt_EGPU(hit, idx);
    189         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    190         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    191     }
    192 
    193     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;
    194 
    195     LOG(LEVEL)
    196         << "]"
    197         << " num_hit " << num_hit
    198         << ( merged_count > 0 ? " MERGED " : "" )
    199         << " merged_count  " << merged_count
    200         << " savehit_count  " << savehit_count
    201         << " m_merged_total " << m_merged_total
    202         << " m_savehit_total " << m_savehit_total
    203         << " m_opticksMode " << m_opticksMode
    204         ;
    205 
    206     m_merged_total += merged_count ;
    207     m_savehit_total += savehit_count ;
    208 
    209 
    210     gx->reset(eventID) ;
    211 }


    0348 double QSim::simulate(int eventID, bool reset_)
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
     360 
     361     SProf::Add("QSim__simulate_PREL");
     362 
     363     sev->t_PreLaunch = sstamp::Now() ;
     364     double dt = rc == 0 && cx != nullptr ? cx->simulate_launch() : -1. ;  //SCSGOptiX protocol
     365     sev->t_PostLaunch = sstamp::Now() ;
     366     sev->t_Launch = dt ;
     367 
     368     SProf::Add("QSim__simulate_POST");
     369 
     370     sev->gather();
     371 
     372     SProf::Add("QSim__simulate_DOWN");
     373 
     374     int num_ht = sev->getNumHit() ;   // NB from fold, so requires hits array gathering to be configured to get non-zero 
     375     int num_ph = event->getNumPhoton() ;
     376 
     377     LOG_IF(info, SEvt::MINIMAL)
     378         << " eventID " << eventID
     379         << " dt " << std::setw(11) << std::fixed << std::setprecision(6) << dt
     380         << " ph " << std::setw(10) << num_ph
     381         << " ph/M " << std::setw(10) << num_ph/M
     382         << " ht " << std::setw(10) << num_ht
     383         << " ht/M " << std::setw(10) << num_ht/M
     384         << " reset_ " << ( reset_ ? "YES" : "NO " )
     385         ;
     386 
     387     if(reset_) reset(eventID) ;
     388     SProf::Add("QSim__simulate_TAIL");
     389     return dt ;
     390 }




run_meta.txt mechanics
------------------------


run_meta.txt::

    OPTICKS_OPTIX_PREFIX:/home/blyth/local/opticks/externals/OptiX_750
    OPTICKS_EVENT_MODE:Hit
    OPTICKS_CUDA_PREFIX:/usr/local/cuda-11.7
    GPUMeta:1:NVIDIA_TITAN_RTX
    QSim__Switches:CONFIG_Debug,NOT-CONFIG_RelWithDebInfo,NOT-CONFIG_Release,NOT-CONFIG_MinSizeRel,NOT-PRODUCTION,WITH_CHILD,WITH_CUSTOM4,PLOG_LOCAL,DEBUG_PIDX,DEBUG_TAG,
    C4Version:TBD
    SEvt__BeginOfRun:1706773751309994,10408748,3571356
    SEvt__beginOfEvent_FIRST_EGPU:1706773751310085,10408748,3571356
    SEvt__setIndex_A000:1706773751310208,10408748,3571360
    SEvt__endIndex_A000:1706773751368214,10707316,3578172
    SEvt__setIndex_A001:1706773751374769,10707316,3578244


::

    1844 void SEvt::setIndex(int index_arg)
    1845 {
    1846     assert( index_arg >= 0 );
    1847     index = SEventConfig::EventIndex(index_arg) ;  // may be offset by OPTICKS_START_INDEX
    1848     t_BeginOfEvent = sstamp::Now();                // moved here from the static 
    1849 
    1850     setRunProf_Annotated("SEvt__setIndex_" );
    1851 }
    1852 void SEvt::endIndex(int index_arg)
    1853 {
    1854     int index_expected = SEventConfig::EventIndex(index_arg) ;
    1855     bool consistent = index_expected == index ;
    1856     LOG_IF(fatal, !consistent)
    1857          << " index_arg " << index_arg
    1858          << " index_expected " << index_expected
    1859          << " index " << index
    1860          << " consistent " << ( consistent ? "YES" : "NO " )
    1861          ;
    1862     assert( consistent );
    1863     t_EndOfEvent = sstamp::Now();
    1864 
    1865     setRunProf_Annotated("SEvt__endIndex_" );
    1866 }

    1437 void SEvt::setRunProf_Annotated(const char* hdr) const
    1438 {
    1439     std::string eid = getIndexString_(hdr) ;
    1440     SetRunMeta<std::string>( eid.c_str(), sprof::Now() );
    1441 }

    1407 void SEvt::SetRunMeta(const char* k, T v )
    1408 {
    1409     RUN_META->set_meta<T>(k, v );
    1410 }




DONE: Persist those SProf::Add stamps, they should be informative  
------------------------------------------------------------------------------

::

     70 inline void SProf::Add(const char* name)
     71 {
     72     sprof prof ;
     73     sprof::Stamp(prof);
     74     Add(name, prof);
     75 }

::

    epsilon:tests blyth$ opticks-f SProf::Write 
    ./CSGOptiX/CSGOptiX.cc:    SProf::Write("run_meta.txt", true ); // append:true 
    ./sysrap/SProf.hh:inline void SProf::Write(const char* path, bool append)
    ./sysrap/tests/SProfTest.cc:    SProf::Write(path, append ); 
    epsilon:opticks blyth$ 

HMM, that SProf::Write not called in okjob.sh running ?::

     176 int CSGOptiX::SimulateMain() // static
     177 {
     178     SProf::Add("CSGOptiX__SimulateMain_HEAD");
     179     SEventConfig::SetRGModeSimulate();
     180     CSGFoundry* fd = CSGFoundry::Load();
     181     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     182     for(int i=0 ; i < SEventConfig::NumEvent() ; i++) cx->simulate(i);
     183     SProf::UnsetTag();
     184     SProf::Add("CSGOptiX__SimulateMain_TAIL");
     185     SProf::Write("run_meta.txt", true ); // append:true 
     186     cx->write_Ctx_log();
     187     delete cx ;
     188     return 0 ;
     189 }


So added to SEvt::EndOfRun writing to SEvt__EndOfRun_SProf.txt::

    N[blyth@localhost opticks]$ l  /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/*.txt
    264 -rw-rw-r--. 1 blyth blyth 270109 Feb  2 14:45 /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/SEvt__EndOfRun_SProf.txt
    108 -rw-rw-r--. 1 blyth blyth 109451 Feb  2 14:45 /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/run_meta.txt
    N[blyth@localhost opticks]$ 


::

    N[blyth@localhost opticks]$ head -20 /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/SEvt__EndOfRun_SProf.txt
    CSGOptiX__Create_HEAD:1706856131162134,1344488,702820
    CSGOptiX__Create_TAIL:1706856133080141,8005220,1152840
    QSim__simulate_HEAD:1706856261841716,10408836,3563396
    QSim__simulate_PREL:1706856261862137,10703748,3563552
    QSim__simulate_POST:1706856261873605,10703748,3565912
    QSim__simulate_DOWN:1706856261876336,10706792,3567648
    QSim__simulate_TAIL:1706856261876411,10706792,3567840
    QSim__simulate_HEAD:1706856261907753,10707320,3570280
    QSim__simulate_PREL:1706856261908198,10707320,3570284
    QSim__simulate_POST:1706856261918355,10707320,3570284
    QSim__simulate_DOWN:1706856261918881,10707320,3570284
    QSim__simulate_TAIL:1706856261918925,10707320,3570384
    QSim__simulate_HEAD:1706856262460651,10709564,3572520
    QSim__simulate_PREL:1706856262461868,10709564,3572536
    QSim__simulate_POST:1706856262471989,10709564,3572536
    QSim__simulate_DOWN:1706856262472863,10709564,3572536
    QSim__simulate_TAIL:1706856262472950,10709564,3572536
    QSim__simulate_HEAD:1706856262506952,10711680,3574708
    QSim__simulate_PREL:1706856262507408,10711680,3574720
    QSim__simulate_POST:1706856262517386,10711680,3574720

    N[blyth@localhost opticks]$ tail -20 /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/SEvt__EndOfRun_SProf.txt
    QSim__simulate_HEAD:1706856302966867,12892796,5755584
    QSim__simulate_PREL:1706856302967647,12892796,5755668
    QSim__simulate_POST:1706856302978336,12892796,5755668
    QSim__simulate_DOWN:1706856302978816,12892796,5755668
    QSim__simulate_TAIL:1706856302978861,12892796,5755668
    QSim__simulate_HEAD:1706856303008511,12895052,5757844
    QSim__simulate_PREL:1706856303009291,12895052,5757928
    QSim__simulate_POST:1706856303018606,12895052,5757928
    QSim__simulate_DOWN:1706856303019094,12895052,5757928
    QSim__simulate_TAIL:1706856303019137,12895052,5757928
    QSim__simulate_HEAD:1706856303047602,12897224,5760012
    QSim__simulate_PREL:1706856303048400,12897224,5760096
    QSim__simulate_POST:1706856303058612,12897224,5760096
    QSim__simulate_DOWN:1706856303059093,12897224,5760096
    QSim__simulate_TAIL:1706856303059137,12897224,5760096
    QSim__simulate_HEAD:1706856303088191,12899444,5762232
    QSim__simulate_PREL:1706856303088957,12899444,5762316
    QSim__simulate_POST:1706856303098586,12899444,5762316
    QSim__simulate_DOWN:1706856303099059,12899444,5762320
    QSim__simulate_TAIL:1706856303099104,12899444,5762320
    N[blyth@localhost opticks]$ 

Grab that::

    epsilon:issues blyth$ ~/j/okjob.sh scpmeta
    run_meta.txt                        100%  107KB  80.8KB/s   00:01    
    SEvt__EndOfRun_SProf.txt            100%  264KB 147.1KB/s   00:01    
    epsilon:issues blyth$ 



Analyse the QSim__simulate stamps with sysrap/tests/sprof.sh
--------------------------------------------------------------

::

    In [5]: fold.SEvt__EndOfRun_SProf_txt_names.reshape(-1,5)
    Out[5]:
    array([['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ...,
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL']], dtype='<U19')


::

    In [7]: rp[:100,:,2]
    Out[7]:
    array([[3563396, 3563552, 3565912, 3567648, 3567840],
           [3570280, 3570284, 3570284, 3570284, 3570384],
           [3572520, 3572536, 3572536, 3572536, 3572536],
           [3574708, 3574720, 3574720, 3574720, 3574824],
           [3577040, 3577052, 3577052, 3577052, 3577052],
           [3579188, 3579204, 3579204, 3579204, 3579300],
           [3581416, 3581432, 3581432, 3581432, 3581432],
           [3583596, 3583612, 3583612, 3583612, 3583708],
           [3585832, 3585848, 3585848, 3585848, 3585944],
           [3588080, 3588100, 3588100, 3588100, 3588100],
           [3590300, 3590316, 3590316, 3590316, 3590316],
           [3592472, 3592488, 3592488, 3592488, 3592584],
           [3594716, 3594732, 3594732, 3594732, 3594732],
           [3596936, 3596956, 3596956, 3596956, 3596956],
           [3599112, 3599128, 3599128, 3599128, 3599224],
           [3601320, 3601336, 3601336, 3601336, 3601424],
           [3603428, 3603444, 3603444, 3603444, 3603536],
           [3605592, 3605608, 3605608, 3605608, 3605700],
           [3607828, 3607848, 3607848, 3607848, 3607940],


Not much RS increment across these 5 stamp::

    In [12]: rp[:100,:,2] - rp[:100,0,2,np.newaxis]
    Out[12]:
    array([[   0,  156, 2516, 4252, 4444],
           [   0,    4,    4,    4,  104],
           [   0,   16,   16,   16,   16],
           [   0,   12,   12,   12,  116],
           [   0,   12,   12,   12,   12],
           [   0,   16,   16,   16,  112],
           [   0,   16,   16,   16,   16],
           [   0,   16,   16,   16,  112],
           [   0,   16,   16,   16,  112],
           [   0,   20,   20,   20,   20],
           [   0,   16,   16,   16,   16],
           [   0,   16,   16,   16,  112],
           [   0,   16,   16,   16,   16],
           [   0,   20,   20,   20,   20],
           [   0,   16,   16,   16,  112],
           [   0,   16,   16,   16,  104],
           [   0,   16,   16,   16,  108],
           [   0,   16,   16,   16,  108],
           [   0,   20,   20,   20,  112],
           [   0,   20,   20,   20,  112],


    In [13]: rp[-100:,:,2] - rp[-100:,0,2,np.newaxis]
    Out[13]:
    array([[ 0, 64, 64, 64, 64],
           [ 0, 64, 64, 64, 64],
           [ 0, 68, 68, 68, 68],
           [ 0, 68, 68, 68, 68],
           [ 0, 68, 68, 68, 68],
           [ 0, 64, 64, 64, 64],
           [ 0, 68, 68, 68, 68],
           [ 0, 64, 64, 64, 64],
           [ 0, 64, 64, 64, 64],
           [ 0, 68, 68, 68, 68],
           [ 0, 68, 68, 68, 68],
           [ 0, 68, 68, 68, 68],
           [ 0, 64, 64, 64, 64],


Comparing the HEAD VM shows the 2 MB leak is elsewhere::

    In [18]: np.diff(rp[:,0,2])
    Out[18]: 
    array([6884, 2240, 2188, 2332, 2148, 2228, 2180, 2236, 2248, 2220, 2172, 2244, 2220, 2176, 2208, 2108, 2164, 2236, 2172, 2252, 2220, 2196, 2248, 2184, 2212, 2196, 2164, 2232, 2216, 2184, 2192, 2232,
           2212, 2208, 2256, 2268, 2272, 2260, 2180, 2232, 2092, 2192, 2132, 2128, 2152, 2132, 2172, 2116, 2108, 2144, 2268, 2192, 2156, 2128, 2232, 2252, 2140, 2128, 2236, 2216, 2192, 2160, 2252, 2204,
           2168, 2244, 2244, 2132, 2144, 2240, 2192, 2200, 2248, 2236, 2252, 2200, 2200, 2124, 2096, 2144, 2200, 2204, 2244, 2168, 2148, 2204, 2256, 2312, 2232, 2140, 2184, 2248, 2156, 2144, 2168, 2140,
           2208, 2228, 2204, 2184, 2180, 2176, 2156, 2160, 2188, 2188, 2280, 2188, 2148, 2248, 2260, 2236, 2212, 2352, 2188, 2204, 2188, 2092, 2208, 2200, 2176, 2188, 2228, 2244, 2208, 2248, 2256, 2084,


This shows can find it by adding more SProf::Add stamps in suitable locations. 

DONE : added 2 more stamps to QSim__reset
--------------------------------------------

::

    In [6]: rp[:100,:,2] - rp[:100,0,2,np.newaxis]
    Out[6]:
    array([[   0,  204, 2380, 4440, 4484, 6852, 6860],
           [   0,   32,   32,   32,  132, 2200, 2264],
           [   0,    0,    0,    0,    0, 2160, 2168],
           [   0,    0,    0,    0,  100, 2304, 2316],
           [   0,    0,    0,    0,    0, 1944, 2136],
           [   0,    0,    0,    0,   92, 2116, 2208],
           [   0,    0,    0,    0,    0, 2048, 2160],
           [   0,    0,    0,    0,   92, 2152, 2216],
           [   0,    0,    0,    0,   96, 2188, 2232],
           [   0,    0,    0,    0,    0, 2084, 2204],
           [   0,    0,    0,    0,    0, 2076, 2156],
           [   0,    0,    0,    0,   92, 2200, 2228],
           [   0,    0,    0,    0,    0, 2108, 2196],
           [   0,    4,    4,    4,    4, 2108, 2160],
           [   0,    0,    0,    0,   92, 1932, 2188],
           [   0,    0,    0,    0,   88, 1928, 2088],
           [   0,    0,    0,    0,   88, 1932, 2144],
           [   0,    0,    0,    0,   92, 2200, 2220],
           [   0,    0,    0,    0,   88, 1932, 2156],
           [   0,    0,    0,    0,   92, 2200, 2232],
           [   0,    0,    0,    0,    0, 2104, 2200],
           [   0,    0,    0,    0,    0, 2108, 2180],
           [   0,    0,    0,    0,   92, 2200, 2228],
           [   0,    0,    0,    0,    0, 2104, 2164],
           [   0,    0,    0,    0,   92, 1936, 2192],
           [   0,    0,    0,    0,    0, 2108, 2164],


    In [8]: fold.SEvt__EndOfRun_SProf_txt_names.reshape(-1,7)
    Out[8]:
    array([['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ...,
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL'],
           ['QSim__simulate_HEAD', 'QSim__simulate_PREL', 'QSim__simulate_POST', 'QSim__simulate_DOWN', 'QSim__simulate_TAIL', 'QSim__reset_HEAD', 'QSim__reset_TAIL_DUMMY_LAST']], dtype='<U27')

    In [9]:                         


Big increment is between QSim__simulate_TAIL and QSim__reset_HEAD 
and it notable the the reset is not decreasing RS like 



Workflow for locating the 2MB leak
-------------------------------------

1. add SProf::Add to relevant methods
2. update opticks on workstation 
3. workstation: ~/j/okjob.sh 
4. laptop: ~/j/okjob.sh scpmeta # copy over SEvt__EndOfRun_SProf.txt
5. laptop: ~/o/sysrap/tests/sprof.sh # convert SEvt__EndOfRun_SProf.txt into array and analyse



Q: Is the leak jumping around in 0.2 MB range proportional to the number of hits in each event ?
--------------------------------------------------------------------------------------------------

TODO: SEvt dumping with memory totals
---------------------------------------













