branch-blyth-OJ-pmt-hit-type-2-for-muon-hits.rst
===================================================


What is needed to add pmt-hit-type 2 
-----------------------------------------

jcv junoHit_PMT_muon junoHit_PMT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "junoHit_PMT_muon" is a subset of "junoHit_PMT" so in principal not difficult to support::

     44   private:
     45     G4int pmtID;         // the ID of the PMT the photon hits
     46     G4double time;       // the time when photon hitting PMT
     47     G4int iHitCount;     // the Number of p.e. from a Hit
     48     G4float localtheta;  // the photon local theth
     49     G4float localphi;    // the photon local phi



How to support muon hits in Opticks ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


1. junoSD_PMT_v2_Opticks::collectHit needs to branch on hit_type::

    int hit_type = m_jpmt->getHitType();


    289 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    290 {
    291     bool merged = m_merger->getMergeFlag() ? m_merger->doMerge(hit->sensor_identifier, hit->time) : false ;
    292     if(merged)
    293     {
    294         merged_count += 1 ;
    295     }
    296     else
    297     {
    298         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    299         savehit_count += 1 ;
    300         m_merger->saveHit(hit_photon);
    301     }
    302 }

2. need junoSD_PMT_v2_Opticks::convertHit_Lite that returns junoHit_PMT_muon




Where is non-Opticks saveHit ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost junosw]$ jgr saveHit
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh: *                  2. saveHit, if not merge, create new hit and put it into collection
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT* hit);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT_muon* hit);
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT_muon* hit_photon) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        m_merger->saveHit(hit_photon);



non-Opticks junoSD_PMT_v2::ProcessHits handles hits one by one ? Is there just one merger ? YES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The single merger is init with normal or muon hit collection, and subsequently
expects to be given only that corresponding type of hit::

    186 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
    187 {
    ...
     218     if (m_pmthitmerger) {
     219         if (m_hit_type == 1) {
     220             m_pmthitmerger->init(hitCollection);
     221         } else if (m_hit_type == 2) {
     222             // TODO
     223             m_pmthitmerger->init(hitCollection_muon);
     224         } else {
     225             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     226         }
     227     }
     228     // make sure the PMT merger exists.
     229     assert(m_pmthitmerger);
     230  


     378 #ifdef WITH_G4CXOPTICKS_EPH
     379 G4bool junoSD_PMT_v2::ProcessHits_(G4Step * step,G4TouchableHistory*)
     380 #else
     381 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     382 #endif
     383 {




     515     if (m_pmthitmerger and m_pmthitmerger->getMergeFlag()) {
     516         // == if merged, just return true. That means just update the hit
     517         // NOTE: only the time and count will be update here, the others
     518         //       will not filled.
     519         bool ok = m_pmthitmerger->doMerge(pmtID, hittime);
     520         if (ok) {
     521             m_merge_count += 1 ;
     522 
     523 #ifdef WITH_G4CXOPTICKS_EPH
     524             m_eph = EPH::YMERGE ;
     525 #endif
     526             return true;
     527         }
     528     }
     529    // = save the hit in the collection
     ...
     531     if (m_hit_type == 1) {
     532 
     533        SaveNormHit(pmtID, local_pos, global_pos, hittime, track, edep);
     534 #ifdef WITH_G4CXOPTICKS_EPH
     535        m_eph = EPH::SAVENORM ;
     536 #endif
     537 
     538     } else if (m_hit_type == 2) {
     539         SaveMuonHit(pmtID, local_pos, hittime);
     540 #ifdef WITH_G4CXOPTICKS_EPH
     541         m_eph = EPH::SAVEMUON ;
     542 #endif
     543     }
     544 
     545     return true;
     546 }
     547 





Where does hit conversion happen
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    Thread 1 "python" hit Breakpoint 2.1, PMTHitMerger::saveHit (this=0xaa6fcc0, hit_photon=0xd1ef2120) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    81	in /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc
    (gdb) bt
    #0  PMTHitMerger::saveHit (this=0xaa6fcc0, hit_photon=0xd1ef2120) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    #1  0x00007fffbd60c3fb in junoSD_PMT_v2_Opticks::collectHit (this=0xaa87530, hit=0x7ffffffedf60, hit_extra=0x0, merged_count=@0x7ffffffee038: 0, savehit_count=@0x7ffffffee034: 1)
        at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:300
    #2  0x00007fffbd60b8d8 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xaa87530, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:219
    #3  0x00007fffbd60b4ca in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xaa87530, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:175
    #4  0x00007fffbd5fbf1f in junoSD_PMT_v2::EndOfEvent (this=0x9dd8340, HCE=0xd1a084c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1129
    #5  0x00007fffc4d720fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #6  0x00007fffc672ea80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #7  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65c6a00, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #8  0x00007fffd485ed3e in DetSimAlg::execute (this=0x66be8d0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #9  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so

::

    289 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    290 {
    291     bool merged = m_merger->getMergeFlag() ? m_merger->doMerge(hit->sensor_identifier, hit->time) : false ;
    292     if(merged)
    293     {
    294         merged_count += 1 ;
    295     }
    296     else
    297     {
    298         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    299         savehit_count += 1 ;
    300         m_merger->saveHit(hit_photon);
    301     }
    302 }






    318 junoHit_PMT* junoSD_PMT_v2_Opticks::convertHit(const U4Hit* hit, const U4HitExtra* hit_extra ) const
    319 {
    320     junoHit_PMT* hit_photon = new junoHit_PMT();
    321 
    322     bool originalOP = !hit->is_reemission ;
    323     double edep = twopi*hbarc / hit->wavelength ;  // TODO:check units match with CPU hits
    324 
    325     hit_photon->SetKineticEnergy(edep);
    326     hit_photon->SetOriginalOP(originalOP);
    327     hit_photon->SetCount(1);
    328 
    329     hit_photon->SetWavelength(hit->wavelength);
    330     hit_photon->SetPMTID(hit->sensor_identifier);
    331     hit_photon->SetWeight(hit->weight);
    332     hit_photon->SetTime(hit->time);
    333 
    334     hit_photon->SetPosition(hit->local_position);
    335     hit_photon->SetTheta(   hit->local_position.theta());
    336     hit_photon->SetPhi(     hit->local_position.phi());
    337     hit_photon->SetMomentum(hit->local_direction);
    338     hit_photon->SetPolarization(hit->local_polarization);
    339 
    340     hit_photon->SetGlobalPosition(hit->global_position);
    341     hit_photon->SetGlobalMomentum(hit->global_direction);
    342     hit_photon->SetGlobalPolarization(hit->global_polarization);
    343 
    344     hit_photon->SetFromCerenkov(hit->is_cerenkov);
    345     hit_photon->SetReemission(hit->is_reemission);
    346 
    347     if(hit_extra)
    348     {
    349         hit_photon->SetProducerID(hit_extra->origin_trackID);
    350         hit_photon->SetOriginalOPStartT(hit_extra->origin_time);
    351         hit_photon->SetBoundaryPosition(hit_extra->boundary_pos);
    352     }
    353     return hit_photon ;
    354 }



pmt hit type branching
~~~~~~~~~~~~~~~~~~~~~~~~~~


::

     450         grp_pmt_op.add_argument("--pmt-hit-type", type=int, default=1, choices=[1,2],
     451                             help=mh("1 for normal hit, 2 for muon"))

    A[blyth@localhost jiabin-simulation-PMTHitMerger-missing-hitcol]$ jgr pmt_hit_type
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        pmtsdmgr.property("HitType").set(args.pmt_hit_type)

    A[blyth@localhost junosw]$ jgr HitType

    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        pmtsdmgr.property("HitType").set(args.pmt_hit_type)
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    pmtsdmgr.property("HitType").set(2)

    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    if (m_pmthitmerger->hasNormalHitType()) {
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    } else if (m_pmthitmerger->hasMuonHitType()) {

    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasNormalHitType() { return hitCollection != 0; }
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasMuonHitType() { return hitCollection_muon != 0; }
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasNormalHitType()) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasMuonHitType()) {

    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setHitType(int i) { m_hit_type = i; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        int getHitType() { return m_hit_type; }

    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("HitType", m_hit_type=1);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setHitType(m_hit_type);
           ## just passes m_hit_type along to junoSD_PMT_v2



jcv junoSD_PMT_v2
~~~~~~~~~~~~~~~~~~~~

m_hit_type:1
    m_pmthitmerger init with (junoHit_PMT_Collection)hitCollection     

m_hit_type:2
    m_pmthitmerger init with (junoHit_PMT_muon_Collection)hitCollection_muon     


::

     186 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     187 {
     188     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     189     m_eventID = event->GetEventID() ;
     190 
     191     m_merge_count = 0 ;
     192     if (m_debug) {
     193         G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
     194     }
     195     hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
     196     hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);
     197     if(m_opticksMode == 3) hitCollectionAlt = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[2]);
     198 
     ...

     218     if (m_pmthitmerger) {
     219         if (m_hit_type == 1) {
     220             m_pmthitmerger->init(hitCollection);
     221         } else if (m_hit_type == 2) {
     222             // TODO
     223             m_pmthitmerger->init(hitCollection_muon); 
     224         } else {
     225             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     226         }
     227     }
     228     // make sure the PMT merger exists.
     229     assert(m_pmthitmerger);
     230 
     231     if (m_pmthitmergerAlt && hitCollectionAlt )
     232     {
     233         if (m_hit_type == 1)
     234         {
     235             m_pmthitmergerAlt->init(hitCollectionAlt);
     236         }
     237         else
     238         {
     239             G4cout << "FATAL : hitCollectionAlt cannot handle hit type [" << m_hit_type << "]" << G4endl;
     240             assert(0);
     241         }
     242     }









