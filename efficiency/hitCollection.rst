hitCollection
==================

Overview
-----------

* previous :doc:`efficiency_review`

TODO
------

* DONE : how to deal with CPU+GPU hits in opticksMode:3 

  * collect into hitCollectionAlt
  * provide way of writing that with --anamgr-hitcollection hitCollectionAlt  

* check opticksMode:1 bookkeeping

* scrub SD from flagmask, same in A and B side 

* switch SD to EC flag, same in A and B side

* export OPTICKS_HIT_MASK=EC into opticks_juno.sh 






Maybe could save twice in opticksMode 3 ? 
--------------------------------------------


::

    A[blyth@localhost junosw]$ jgr junoHit_PMT_Collection
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/MuonToySim.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool init(junoHit_PMT_Collection* hitcol);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:  junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:// junoHit_PMT_Collection is a vector of hits
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT.hh:    junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection*      getHitCollection(){      return hitCollection ; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::init(junoHit_PMT_Collection* hitcol) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc:  hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    A[blyth@localhost junosw]$ 


000 check
----------

::

    2025-06-12 13:29:37.706 INFO  [3923862] [QEvent::gatherPhoton@610] [ evt.num_photon 1000000 p.sstr (1000000, 4, 4, ) evt.photon 0x7ffd40000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    SProcessHits_EPH::desc
                 ProcessHits_count 2542310
                  ProcessHits_true  363159
                 ProcessHits_false 2179151
                 SaveNormHit_count  363159
                 SaveMuonHit_count       0
                         EPH_UNSET       0
                          EPH_NDIS       0
                          EPH_NOPT       0
                         EPH_NEDEP 2156552
                        EPH_NBOUND    5153
                         EPH_NPROC       0
                       EPH_NDETECT       0
                       EPH_NDECULL   17446
                        EPH_YMERGE       0
                         EPH_YSAVE       0
                      EPH_SAVENORM  363159
                      EPH_SAVEMUON       0
    Initialize_G4HCofThisEvent_opticksMode       3
    Initialize_G4HCofThisEvent_count       1
       EndOfEvent_Simulate_eventID       0
         EndOfEvent_Simulate_count       1
      EndOfEvent_Simulate_EGPU_hit  360362
    EndOfEvent_hitCollection_entries0  363159
    EndOfEvent_hitCollection_entries1  363159
    EndOfEvent_hitCollectionAlt_entries0       0
    EndOfEvent_hitCollectionAlt_entries1  360362
    EndOfEvent_Simulate_merged_count       0
    EndOfEvent_Simulate_savehit_count  360362
    EndOfEvent_Simulate_merged_total       0
    EndOfEvent_Simulate_savehit_total  360362



::

    SABHit  a_nhit : (  360362 +-  600 )  b_nhit:(   363159 +-  602 )  a/b: (  0.992 +-  0.003 )  b/a: (  1.008 +-  0.003)  [assume uncorr.]




Need Alt merger for hitCollectionAlt
---------------------------------------

::



    jgl PMTHitMerger 

    (ok) A[blyth@localhost opticks]$ jgl PMTHitMerger
    ./Simulation/DetSimV2/AnalysisCode/include/MuonFastSimVoxel.hh
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc
    ./Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Opticks.hh
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh
    ./Simulation/DetSimV2/PMTSim/include/PMTSDMgr.hh
    ./Simulation/DetSimV2/PMTSim/include/.junoSD_PMT_v2.hh.swp
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    (ok) A[blyth@localhost junosw]$ 






DataModelWriter::fill_hits uses hardcoded collection names : hitCollection and hitCollectionMuon
-------------------------------------------------------------------------------------------------

* both hitCollection and hitCollectionMuon are combined into JM::SimEvt* dst

::

    jcv DataModelWriter

    113 void
    114 DataModelWriter::fill_hits(JM::SimEvt* dst, const G4Event* evt)
    115 {
    116 
    117     LogDebug << "Begin Fill Hits" << std::endl;
    118 
    119     // header level 
    120     m_nPhotons = 0;
    121     m_timewindow = 0;
    122     m_nPhotons_muon = 0;
    123     m_timewindow_muon = 0;
    124 
    125     G4SDManager * SDman = G4SDManager::GetSDMpointer();
    126     G4int CollID = SDman->GetCollectionID("hitCollection");
    127     junoHit_PMT_Collection* col = 0;
    128     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    129     if (!HCE) {
    130         LogError << "No hits collection found." << std::endl;
    131         return;
    132     }
    133     if (CollID >= 0) {
    134         col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    135     }
    136     if (col) {
    137         fill_hits_tmpl(col, dst);
    138     }
    139     // muon hit type
    140     CollID = SDman->GetCollectionID("hitCollectionMuon");
    141     junoHit_PMT_muon_Collection* col_muon = 0;
    142     if (CollID >= 0) {
    143         col_muon = (junoHit_PMT_muon_Collection*)(HCE->GetHC(CollID));
    144     }
    145     if (col_muon) {
    146         fill_hits_tmpl(col_muon, dst);
    147     }
    148 
    149     // fill evt data
    150     // int totPE = 0;
    151     LogDebug << "End Fill Hits" << std::endl;
    152 
    153 }

 
    A[blyth@localhost junosw]$ jgl DataModelWriter
    ./Doc/detsim/anaelement.md
    ./Doc/oum/source/detsim/anaelement.md
    ./Doc/oum/source/quickstart/quickstart.md
    ./Doc/oum/source/releasenotes/J22.2.md
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ./RootIO/RootIOTools/src/SimEventMerger.cc
    ./Simulation/DetSimV2/AnalysisCode/include/DataModelWriter.hh
    ./Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    ./Simulation/DetSimV2/DetSimOptions/share/examples/OPLoader/pyjob_muon_only_op.py
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py
    A[blyth@localhost junosw]$ 




jcv DataModelWriterWithSplit "hitCollection" hardcoded string appears twice
-----------------------------------------------------------------------------

* potential approach is to declProp the "hitCollection" string into m_hitCollectionCD
  that has disadvantage of having to run twice to get both collections despite them 
  both being available in mode 3 

::

    304 void
    305 DataModelWriterWithSplit::fill_hits(JM::SimEvt* dst, const G4Event* evt)
    306 {
    307 
    308     LogDebug << "Begin Fill Hits" << std::endl;
    309     G4SDManager * SDman = G4SDManager::GetSDMpointer();
    310     G4int CollID = SDman->GetCollectionID("hitCollection");
    311 
    312     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    313     junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    314     // muon hit type
    315     CollID = SDman->GetCollectionID("hitCollectionMuon");
    316     junoHit_PMT_muon_Collection* col_muon = (junoHit_PMT_muon_Collection*)(HCE->GetHC(CollID));
    317     // TT hits
    318     CollID = SDman->GetCollectionID("hitCollectionTT");
    319     junoHit_TT_Collection* col_tt = (junoHit_TT_Collection*)(HCE->GetHC(CollID));
    320 
    321     if (col_muon) {
    322         fill_hits_tmpl(col_muon, dst);
    323     }
    324 
    325     // fill evt data
    326     // int totPE = 0;
    327     if (col) {
    328         fill_hits_tmpl(col, dst);
    329     }
    330 
    331     // fill Top-Tracker hits
    332     if (col_tt) {
    333       fill_hits_tt(col_tt, dst);
    334     }
    335     LogDebug << "End Fill Hits" << std::endl;
    336 
    337 }



    095 void
     96 DataModelWriterWithSplit::EndOfEventAction(const G4Event* evt) {
     97     // == retrieve the geant4 collection ==
     98     G4SDManager * SDman = G4SDManager::GetSDMpointer();
     99     G4int CollID = SDman->GetCollectionID("hitCollection");
    100 
    101     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    102     junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    103     if (not col) {
    104         LogWarn << "Not Hit found" << std::endl;
    105         return;
    106     }
    107     int n_hit = col->entries();
    108    // if(n_hit==0)
    109   //     {col=0;}
    110 
    111     CollID = SDman->GetCollectionID("hitCollectionMuon");
    112     junoHit_PMT_muon_Collection* col_muon = (junoHit_PMT_muon_Collection*)(HCE->GetHC(CollID));
    113     if (col_muon) {
    114         LogDebug << "size of muon hit collection: " << col_muon->entries()
    115                  << std::endl;
    116         n_hit += col_muon->entries();
    117     }




jcv JUNODetSimModule : DataModelWriterWithSplit
--------------------------------------------------

::

    2270         # == edm (event data model) ==
    2271         # == if split mode enable, disable others ==   
    2272         if args.anamgr_edm:
    2273             detsimfactory.property("AnaMgrList").append("DataModelWriter")
    2274         elif args.anamgr_edm_v2:
    2275             detsimfactory.property("AnaMgrList").append(
    2276                                         "DataModelWriterWithSplit",
    2277                                         )
    2278             dmwws = sim_conf.tool("DataModelWriterWithSplit")
    2279             dmwws.property("SaveSimTrack").set(args.anamgr_simtrack)
    2280             if args.splitevent:
    2281                 dmwws.property("disable_split").set(False)
    2282                 if args.event_split_maxhits:
    2283                     dmwws.property("HitsMax").set(args.event_split_maxhits)
    2284                 else:
    2285                     dmwws.property("HitsMax").set(10000)
    2286             else:
    2287                 if args.event_split_maxhits != None: #Force to add option --output-split when using --split-maxhits
    2288                     assert 0, "Error ! : --event-split should be set."
    2289                 dmwws.property("disable_split").set(True)



jcv JUNODetSimModule : --output
----------------------------------



