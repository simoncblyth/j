summary of 3/100 fails
========================

::

    single-muon-group1.854925_23.err
    single-muon-group1.854925_23.out
    single-muon-group1.854925_45.err
    single-muon-group1.854925_45.out
    single-muon-group1.854925_91.err
    single-muon-group1.854925_91.out




Higher Stats Fail
-----------------------

single-muon-group2.862361_34.out
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

     decay 2 gammas 0.510999
    2025-09-29 14:01:08.325 FATAL [4160861] [SEvt::setNumPhoton@2310]  num_photon/M 1000 evt.max_photon/M 1000 num_photon 1000000079 evt.max_photon 1000000000
    WARNING - Attempt to delete the physical volume store while geometry closed !
    WARNING - Attempt to delete the logical volume store while geometry closed !
    WARNING - Attempt to delete the solid store while geometry closed !
    WARNING - Attempt to delete the region store while geometry closed !


single-muon-group2.862361_34.err
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    449 #9  0x000015411322871b in __assert_fail_base.cold () from /lib64/libc.so.6
    450 #10 0x0000154113237386 in __assert_fail () from /lib64/libc.so.6
    451 #11 0x00001540da149896 in SEvt::setNumPhoton (this=0xdd98d10, num_photon=1000000079) at /home/blyth/opticks/sysrap/SEvt.cc:2316
    452 #12 0x00001540da14954b in SEvt::addGenstep (this=0xdd98d10, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2275
    453 #13 0x00001540da1456b0 in SEvt::AddGenstep (q=...) at /home/blyth/opticks/sysrap/SEvt.cc:1355
    454 #14 0x00001540dc6f32d2 in U4::CollectGenstep_DsG4Scintillation_r4695 (aTrack=0xc6e3a1e0, aStep=0x7d89a60, numPhotons=854, scnt=0, ScintillationTime=4.5999999999999996) at /home/blyth/opticks/u4/U4.cc:170
    455 #15 0x00001540d90ca7fc in DsG4Scintillation::PostStepDoIt (this=0x2fd362b0, aTrack=..., aStep=...) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:601
    456 #16 0x00001540e25f3519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    457 #17 0x00001540e25f391b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so




DataModelWriterWithSplit/fill_hits_tmpl
------------------------------------------

::

     40     void fill_hits_tmpl(G4THitsCollection<T>* col, JM::SimEvt* dst) {
     41         int n_hit = col->entries();
     42         // m_nPhotons = n_hit;
     43         int count = 0;
     44         for (int i = m_start_idx; (i < n_hit and count < m_hitcol_max);
     45                 ++m_start_idx, ++i, ++count) {
     46             // create new hit
     47             // The PMT Hit can be from WP (Water Pool) or CD (Central
     48             // Detector). 
     49             // Please use the copy no to distinguish the PMT.
     50             int copyno = (*col)[i]->GetPMTID();
     51             JM::SimPMTHit* jm_hit = 0;
     52             // FIXME: hard code the copy no
     53             if (PMT::IsCD(copyno)) {
     54                 // TODO because in current Data Model, the 3inch and the 20inch
     55                 // PMTs are in the same collection.
     56                 jm_hit = dst->addCDHit();
     57             } else if (PMT::IsWP(copyno)) {
     58                 jm_hit = dst->addWPHit();
     59             }

     /////////// SOMETHING IS CAUSING jm_hit TO BE NULL
     /////////// RESULTING IN FAILURE ON LINE 60
     /////////// THAT COULD BE AN UNEXPECTED copyno OR CPU MEMORY ERROR

     60             jm_hit->setPMTID( (*col)[i]->GetPMTID() );
     61             jm_hit->setNPE( (*col)[i]->GetCount() );
     62             jm_hit->setHitTime( (*col)[i]->GetTime() );
     63             jm_hit->setTrackID( (*col)[i]->GetProducerID() );
     64             jm_hit->setLocalTheta( (*col)[i]->GetTheta() );
     65             jm_hit->setLocalPhi( (*col)[i]->GetPhi() );
     66 
     67         }
     68     }




::

    139     SimPMTHit* SimEvt::addCDHit() {
    140         SimPMTHit* hit = new SimPMTHit;
    141         m_cd_hits.push_back(hit);
    142         ++m_nhits;
    143         return hit;
    144     }
    145 
    146     SimPMTHit* SimEvt::addWPHit() {
    147         SimPMTHit* hit = new SimPMTHit;
    148         m_wp_hits.push_back(hit);
    149         ++m_nhits_wp;
    150         return hit;
    151     }





::

     11 
     12 //  #include "Identifier/CopyNumber.hh"
     13 
     14 enum PMTID_OFFSET_DETSIM {
     15   kOFFSET_CD_LPMT=0,     kOFFSET_CD_LPMT_END=17612, // CD-LPMT
     16   kOFFSET_CD_SPMT=20000, kOFFSET_CD_SPMT_END=45600,  // CD-SPMT
     17   kOFFSET_WP_PMT=50000,  kOFFSET_WP_PMT_END=52400,  // WP-LPMT
     18   kOFFSET_WP_ATM_LPMT=52400,  kOFFSET_WP_ATM_LPMT_END=52748, //WP-Atmosphere-LPMT
     19   kOFFSET_WP_ATM_MPMT=53000,  kOFFSET_WP_ATM_MPMT_END=53600,  //WP-Atmosphere-MPMT (Medium, 8 inch)
     20   kOFFSET_WP_WAL_PMT=54000,  kOFFSET_WP_WAL_PMT_END=54005 //WP-Water-attenuation-length
     21 
     22 };
     23 
     24 struct PMT
     25 {
     26     static bool IsCD(int pmtid);
     27     static bool IsWP(int pmtid);
     28     static bool IsWP_ATM(int pmtid);
     29     static bool IsWP_WAL(int pmtid);
     30     static bool Is20inch(int pmtid);
     31     static bool Is8inch(int pmtid);
     32     static bool Is3inch(int pmtid);
     33 };
     34 
     35 inline bool PMT::IsCD(int pmtid)
     36 {
     37     return (kOFFSET_CD_LPMT<=pmtid and pmtid<kOFFSET_CD_LPMT_END)
     38         or (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_CD_SPMT_END);
     39 }
     40 inline bool PMT::IsWP(int pmtid)
     41 {
     42     return (kOFFSET_WP_PMT<=pmtid and pmtid<kOFFSET_WP_PMT_END)
     43         or (kOFFSET_WP_ATM_LPMT<=pmtid and pmtid<kOFFSET_WP_ATM_LPMT_END)
     44         or (kOFFSET_WP_ATM_MPMT<=pmtid and pmtid<kOFFSET_WP_ATM_MPMT_END)
     45         or (kOFFSET_WP_WAL_PMT<=pmtid and pmtid<kOFFSET_WP_WAL_PMT_END);
     46 }
     47 inline bool PMT::IsWP_ATM(int pmtid)
     48 {
     49     return (kOFFSET_WP_ATM_LPMT<=pmtid and pmtid<kOFFSET_WP_ATM_LPMT_END)
     50         or (kOFFSET_WP_ATM_MPMT<=pmtid and pmtid<kOFFSET_WP_ATM_MPMT_END);
     51 }
     52 inline bool PMT::IsWP_WAL(int pmtid)
     53 {
     54     return (kOFFSET_WP_WAL_PMT<=pmtid and pmtid<kOFFSET_WP_WAL_PMT_END);









::

    305 void
    306 DataModelWriterWithSplit::fill_hits(JM::SimEvt* dst, const G4Event* evt)
    307 {
    308 
    309     LogDebug << "Begin Fill Hits" << std::endl;
    310     G4SDManager * SDman = G4SDManager::GetSDMpointer();
    311     G4int CollID = SDman->GetCollectionID(m_hitCollection);
    312 
    313     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    314     junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    315     // muon hit type
    316     CollID = SDman->GetCollectionID("hitCollectionMuon");
    317     junoHit_PMT_muon_Collection* col_muon = (junoHit_PMT_muon_Collection*)(HCE->GetHC(CollID));
    318     // TT hits
    319     CollID = SDman->GetCollectionID("hitCollectionTT");
    320     junoHit_TT_Collection* col_tt = (junoHit_TT_Collection*)(HCE->GetHC(CollID));
    321 
    322     if (col_muon) {
    323         fill_hits_tmpl(col_muon, dst);
    324     }
    325 
    326     // fill evt data
    327     // int totPE = 0;
    328     if (col) {
    329         fill_hits_tmpl(col, dst);

    ///    shovelling from junoHit_PMT_Collection into JM::SimEvt


    330     }
    331 
    332     // fill Top-Tracker hits
    333     if (col_tt) {
    334       fill_hits_tt(col_tt, dst);
    335     }
    336     LogDebug << "End Fill Hits" << std::endl;
    337 
    338 }








single-muon-group1.854925_23.err : null hit
----------------------------------------------

::

    #6  0x0000153a05711898 in JM::SimPMTHit::setPMTID (this=0x0, val=-1) at /builds/JUNO/offline/junosw/build/include/Event/SimPMTHit.h:72
    #7  0x0000153a0571aeb2 in DataModelWriterWithSplit::fill_hits_tmpl<junoHit_PMT> (this=0x7affa80, col=0xb71d8d20, dst=0x11c49faa0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh:60
    #8  0x0000153a05716e22 in DataModelWriterWithSplit::fill_hits (this=0x7affa80, dst=0x11c49faa0, evt=0xb811a5f0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:329
    #9  0x0000153a0571677d in DataModelWriterWithSplit::EndOfEventAction (this=0x7affa80, evt=0xb811a5f0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:288
    #10 0x0000153a136b1c2a in MgrOfAnaElem::EndOfEventAction (this=0xb6a09d0, evt=0xb811a5f0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53
    #11 0x0000153a05bbf20b in LSExpEventAction::EndOfEventAction (this=0xbe91690, evt=0xb811a5f0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpEventAction.cc:76
    #12 0x0000153a0e3f4a92 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x0000153a266a968e in G4SvcRunManager::SimulateEvent (this=0x7aa1920, i_event=2) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x0000153a136a6d3e in DetSimAlg::execute (this=0x7ab6ef0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x0000153a1814c4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #


single-muon-group1.854925_23.out : 763M photons
-------------------------------------------------


::

    2025-09-29 01:43:59.460 INFO  [4108108] [QSim::simulate@432]  eventID      2 igs (3354368, 6, 4, ) MaxSlot 264000000 MaxSlot/M 264 sslice::Desc(igs_slice)
    sslice::Desc num_slice 3 TotalPhoton  763498914 TotalPhoton/M 763.498914
                      start    stop     offset      count    count/M 
       0 : sslice {       0, 1162273,         0, 263998692}263.998692
       1 : sslice { 1162273, 2325353, 263998692, 263999934}263.999934
       2 : sslice { 2325353, 3354368, 527998626, 235500288}235.500288
                      start    stop     offset      count    count/M 
     num_slice 3
    2025-09-29 01:43:59.460 INFO  [4108108] [QSim::simulate@450]    0 : sslice {       0, 1162273,         0, 263998692}263.998692
    //qcerenkov::wavelength_sampled_bndtex idx 4856367 sampledRI   1.723 cosTheta   0.953 sin2Theta   0.092 wavelength 144.801 count 78 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 7162127 sampledRI   1.785 cosTheta   0.966 sin2Theta   0.068 wavelength 152.505 count 62 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 12910928 sampledRI   1.786 cosTheta   0.916 sin2Theta   0.160 wavelength 153.333 count 55 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 14676113 sampledRI   1.775 cosTheta   0.907 sin2Theta   0.178 wavelength 149.275 count 62 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 17174705 sampledRI   1.792 cosTheta   0.924 sin2Theta   0.145 wavelength 159.221 count 63 matline 39 
    ...
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 1 hitCollection 8767837 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-09-28 18:34:25.199296000Z
    WARNING - Attempt to delete the physical volume store while geometry closed !
    WARNING - Attempt to delete the logical volume store while geometry closed !
    WARNING - Attempt to delete the solid store while geometry closed !
    WARNING - Attempt to delete the region store while geometry closed !



single-muon-group1.854925_45.err : again null hit
----------------------------------------------------

::

    #6  0x0000145741911898 in JM::SimPMTHit::setPMTID (this=0x0, val=-1) at /builds/JUNO/offline/junosw/build/include/Event/SimPMTHit.h:72
    #7  0x000014574191aeb2 in DataModelWriterWithSplit::fill_hits_tmpl<junoHit_PMT> (this=0x807c2f0, col=0xb79a70b8, dst=0xfd5c3980) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh:60
    #8  0x0000145741916e22 in DataModelWriterWithSplit::fill_hits (this=0x807c2f0, dst=0xfd5c3980, evt=0xb874d9e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:329
    #9  0x000014574191677d in DataModelWriterWithSplit::EndOfEventAction (this=0x807c2f0, evt=0xb874d9e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:288
    #10 0x000014574e9f1c2a in MgrOfAnaElem::EndOfEventAction (this=0xbcdb650, evt=0xb874d9e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53
    #11 0x00001457411bf20b in LSExpEventAction::EndOfEventAction (this=0xc4cc910, evt=0xb874d9e0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpEventAction.cc:76
    #12 0x0000145749b6ba92 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x000014575fb6668e in G4SvcRunManager::SimulateEvent (this=0x80eeb40, i_event=5) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x000014574e9e6d3e in DetSimAlg::execute (this=0x813e220) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x000014575374d4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #

single-muon-group1.854925_45.out : 562M photons
----------------------------------------------------


::

    2025-09-29 02:26:08.172 INFO  [4128942] [QSim::simulate@432]  eventID      5 igs (2540372, 6, 4, ) MaxSlot 264000000 MaxSlot/M 264 sslice::Desc(igs_slice)
    sslice::Desc num_slice 3 TotalPhoton  562549378 TotalPhoton/M 562.549378
                      start    stop     offset      count    count/M 
       0 : sslice {       0, 1184719,         0, 263999288}263.999288
       1 : sslice { 1184719, 2403299, 263999288, 263999877}263.999877
       2 : sslice { 2403299, 2540372, 527999165,  34550213} 34.550213
                      start    stop     offset      count    count/M 
     num_slice 3
    2025-09-29 02:26:08.172 INFO  [4128942] [QSim::simulate@450]    0 : sslice {       0, 1184719,         0, 263999288}263.999288
    //qcerenkov::wavelength_sampled_bndtex idx 7857117 sampledRI   1.194 cosTheta   1.420 sin2Theta   0.000 wavelength  90.920 count 100 matline 39 
    //qcerenkov::wavelength_sampled_bndtex idx 15230229 sampledRI   1.784 cosTheta   0.921 sin2Theta   0.151 wavelength 151.083 count 61 matline 39 

    ...
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 1 hitCollection 9552919 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-09-28 19:17:42.836596000Z
    WARNING - Attempt to delete the physical volume store while geometry closed !
    WARNING - Attempt to delete the logical volume store while geometry closed !
    WARNING - Attempt to delete the solid store while geometry closed !
    WARNING - Attempt to delete the region store while geometry closed !
*


single-muon-group1.854925_91.err : null hit again
-----------------------------------------------------

::

    #6  0x0000147740d11898 in JM::SimPMTHit::setPMTID (this=0x0, val=-1) at /builds/JUNO/offline/junosw/build/include/Event/SimPMTHit.h:72
    #7  0x0000147740d1aeb2 in DataModelWriterWithSplit::fill_hits_tmpl<junoHit_PMT> (this=0x6c041c0, col=0xc5687ce8, dst=0xc825b770) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh:60
    #8  0x0000147740d16e22 in DataModelWriterWithSplit::fill_hits (this=0x6c041c0, dst=0xc825b770, evt=0xb6b162c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:329
    #9  0x0000147740d1677d in DataModelWriterWithSplit::EndOfEventAction (this=0x6c041c0, evt=0xb6b162c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:288
    #10 0x0000147752ce4c2a in MgrOfAnaElem::EndOfEventAction (this=0xa68e540, evt=0xb6b162c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53
    #11 0x00001477411bf20b in LSExpEventAction::EndOfEventAction (this=0xae7e630, evt=0xb6b162c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpEventAction.cc:76
    #12 0x0000147749b2ea92 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x00001477679e868e in G4SvcRunManager::SimulateEvent (this=0x6ae35a0, i_event=13) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x0000147752cd9d3e in DetSimAlg::execute (this=0x6ac4b00) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x000014775374d4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so




single-muon-group1.854925_91.out : 840M photon
---------------------------------------------------

::

    2025-09-29 04:21:55.657 INFO  [92280] [QSim::simulate@432]  eventID     13 igs (3837784, 6, 4, ) MaxSlot 264000000 MaxSlot/M 264 sslice::Desc(igs_slice)
    sslice::Desc num_slice 4 TotalPhoton  840188373 TotalPhoton/M 840.188373
                      start    stop     offset      count    count/M 
       0 : sslice {       0, 1193501,         0, 263999938}263.999938
       1 : sslice { 1193501, 2419716, 263999938, 263999107}263.999107
       2 : sslice { 2419716, 3628613, 527999045, 263999216}263.999216
       3 : sslice { 3628613, 3837784, 791998261,  48190112} 48.190112
                      start    stop     offset      count    count/M 
     num_slice 4
    2025-09-29 04:21:55.658 INFO  [92280] [QSim::simulate@450]    0 : sslice {       0, 1193501,         0, 263999938}263.999938
    //qcerenkov::wavelength_sampled_bndtex idx 5453681 sampledRI   1.652 cosTheta   0.995 sin2Theta   0.010 wavelength 138.815 count 52 matline 39 
   //qcerenkov::wavelength_sampled_bndtex idx 11440668 sampledRI   1.692 cosTheta   0.980 sin2Theta   0.040 wavelength 142.195 count 64 matline 39 
 

    junoSD_PMT_v2::EndOfEvent eventID 13 opticksMode 1 hitCollection 9489448 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 108	userhitCollectionTT.size: 54
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-09-28 21:23:00.783040000Z
    WARNING - Attempt to delete the physical volume store while geometry closed !
    WARNING - Attempt to delete the logical volume store while geometry closed !
    WARNING - Attempt to delete the solid store while geometry closed !
    WARNING - Attempt to delete the region store while geometry closed !


    /
