fill_hits_segv
=================


Overview
-----------

When enable "--anamgr-edm-v2" get SEGV at event 117::

    250 jok-anamgr(){ cat << EOU
    251 $(: --opticks-anamgr)
    252 --no-anamgr-normal
    253 --no-anamgr-genevt
    254 --anamgr-edm-v2
    255 --no-anamgr-grdm
    256 --no-anamgr-deposit
    257 --no-anamgr-deposit-tt
    258 --no-anamgr-interesting-process
    259 --no-anamgr-optical-parameter
    260 --no-anamgr-timer
    261 EOU
    262    : --opticks-anamgr attempts to switch on U4RecorderAnaMgr - BUT THAT NEEDS opticksMode 2 or 3
    263 }


The cause is that the writer is not expecting SPMT hits resulting in nullptr jm_hit::

    Simulation/DetSimV2/AnalysisCode/include/DataModelWriter.hh

    071             for (int i = 0; i < n_hit; ++i) {
     72                 // create new hit
     73                 // The PMT Hit can be from WP (Water Pool) or CD (Central
     74                 // Detector). 
     75                 // Please use the copy no to distinguish the PMT.
     76                 int copyno = (*col)[i]->GetPMTID();
     77                 JM::SimPMTHit* jm_hit = 0;
     78                 // FIXME: hard code the copy no
     79                 if (PMT::IsCD(copyno)) {
     80                     // TODO because in current Data Model, the 3inch and the 20inch
     81                     // PMTs are in the same collection.
     82                     jm_hit = dst->addCDHit();
     83                 } else if (PMT::IsWP(copyno)) {
     84                     jm_hit = dst->addWPHit();
     85                 }



Issue
------

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (117) 
    junoSD_PMT_v2::Initialize eventID 117
    Begin of Event --> 117
    2023-12-18 23:04:32.172 INFO  [160405] [QSim::simulate@376]  eventID 117 dt    0.009218 ph       8753 ph/M          0 ht       1673 ht/M          0 reset_ NO 
    2023-12-18 23:04:32.194 INFO  [160405] [SEvt::save@3953] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A117 [genstep,hit]
    junoSD_PMT_v2::EndOfEvent eventID 117 opticksMode 1 hitCollection 1673 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2023-12-18 15:04:32.196154000Z

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc82abda5 in DataModelWriterWithSplit::fill_hits(JM::SimEvt*, G4Event const*) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    (gdb) bt
    #0  0x00007fffc82abda5 in DataModelWriterWithSplit::fill_hits(JM::SimEvt*, G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    #1  0x00007fffc82adbf9 in DataModelWriterWithSplit::EndOfEventAction(G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    #2  0x00007fffc7f4a558 in MgrOfAnaElem::EndOfEventAction(G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libDetSimAlg.so
    #3  0x00007fffd1169242 in G4EventManager::DoProcessing(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #4  0x00007fffc8426630 in G4SvcRunManager::SimulateEvent(int) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libG4SvcLib.so
    #5  0x00007fffc7f4063a in DetSimAlg::execute() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libDetSimAlg.so
    #6  0x00007fffd4e42511 in Task::execute() ()



jcv DataModelWriterWithSplit::

    301 void
    302 DataModelWriterWithSplit::fill_hits(JM::SimEvt* dst, const G4Event* evt)
    303 {
    304 
    305     LogDebug << "Begin Fill Hits" << std::endl;
    306     G4SDManager * SDman = G4SDManager::GetSDMpointer();
    307     G4int CollID = SDman->GetCollectionID("hitCollection");
    308 
    309     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    310     junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    311     // muon hit type
    312     CollID = SDman->GetCollectionID("hitCollectionMuon");
    313     junoHit_PMT_muon_Collection* col_muon = (junoHit_PMT_muon_Collection*)(HCE->GetHC(CollID));
    314     // TT hits
    315     CollID = SDman->GetCollectionID("hitCollectionTT");
    316     junoHit_TT_Collection* col_tt = (junoHit_TT_Collection*)(HCE->GetHC(CollID));
    317 
    318     if (col_muon) {
    319         fill_hits_tmpl(col_muon, dst);
    320     }
    321 
    322     // fill evt data
    323     // int totPE = 0;
    324     if (col) {
    325         fill_hits_tmpl(col, dst);
    326     }
    327 
    328     // fill Top-Tracker hits
    329     if (col_tt) {
    330       fill_hits_tt(col_tt, dst);
    331     }
    332     LogDebug << "End Fill Hits" << std::endl;
    333 
    334 }


::

    epsilon:junosw blyth$ jgr fill_hits_tmpl
    ./Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh:    void fill_hits_tmpl(G4THitsCollection<T>* col, JM::SimEvt* dst) {
    ./Simulation/DetSimV2/AnalysisCode/include/DataModelWriter.hh:    void fill_hits_tmpl(G4THitsCollection<T>* col, JM::SimEvt* dst) {
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:        fill_hits_tmpl(col, dst);
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:        fill_hits_tmpl(col_muon, dst);
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:        fill_hits_tmpl(col_muon, dst);
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:        fill_hits_tmpl(col, dst);


::

    (gdb) f 1
    #1  0x00007fffc7bdd40d in DataModelWriterWithSplit::fill_hits_tmpl<junoHit_PMT> (this=0x5e2ffa0, col=0xa58ae038, dst=0xc1aa9d90)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/include/DataModelWriterWithSplit.hh:60
    60	            jm_hit->setPMTID( (*col)[i]->GetPMTID() );
    (gdb) list
    55	                // PMTs are in the same collection.
    56	                jm_hit = dst->addCDHit();
    57	            } else if (PMT::IsWP(copyno)) {
    58	                jm_hit = dst->addWPHit();
    59	            }
    60	            jm_hit->setPMTID( (*col)[i]->GetPMTID() );
    61	            jm_hit->setNPE( (*col)[i]->GetCount() );
    62	            jm_hit->setHitTime( (*col)[i]->GetTime() );
    63	            jm_hit->setTrackID( (*col)[i]->GetProducerID() );
    64	            jm_hit->setLocalTheta( (*col)[i]->GetTheta() );
    (gdb) p jm_hit 
    $1 = (JM::SimPMTHit *) 0x0
    (gdb) p copyno
    $2 = 325600
    (gdb) 



sensor_identifier OFF BY ONE ? 
---------------------------------

::

    375     /**
    376     sqat4::setIdentity
    377     -------------------
    378 
    379     Canonical usage from CSGFoundry::addInstance  where sensor_identifier gets +1 
    380     with 0 meaning not a sensor. 
    381     **/
    382 
    383     QAT4_METHOD void setIdentity(int ins_idx, int gas_idx, int sensor_identifier_1, int sensor_index )
    384     {
    385         assert( sensor_identifier_1 >= 0 );
    386 
    387         q0.i.w = ins_idx ;             // formerly unsigned and "+ 1"
    388         q1.i.w = gas_idx ;
    389         q2.i.w = sensor_identifier_1 ;   // now +1 with 0 meaning not-a-sensor 
    390         q3.i.w = sensor_index ;
    391     }


::

    1888 /**
    1889 CSGFoundry::addInstance
    1890 ------------------------
    1891 
    1892 Used from CSGCopy::copy/CSGCopy::copySolidInstances 
    1893 when copying a loaded CSGFoundry to apply a selection
    1894 
    1895 stree.h/snode.h uses sensor_identifier -1 to indicate not-a-sensor, but 
    1896 that is not convenient on GPU due to OptixInstance.instanceId limits.
    1897 Hence here make transition by adding 1 and treating 0 as not-a-sensor. 
    1898 
    1899 **/
    1900 
    1901 void CSGFoundry::addInstance(const float* tr16, int gas_idx, int sensor_identifier, int sensor_index, bool firstcall )
    1902 {
    1903     int sensor_identifier_u = 0 ;
    1904 
    1905     if( firstcall )
    1906     {
    1907         assert( sensor_identifier >= -1 );
    1908         sensor_identifier_u = sensor_identifier + 1 ;
    1909     }
    1910     else
    1911     {
    1912         assert( sensor_identifier >= 0 );
    1913         sensor_identifier_u = sensor_identifier  ;
    1914     }
    1915     assert( sensor_identifier_u >= 0 );
    1916 
    1917 
    1918     qat4 instance(tr16) ;  // identity matrix if tr16 is nullptr 
    1919     int ins_idx = int(inst.size()) ;
    1920 
    1921     instance.setIdentity( ins_idx, gas_idx, sensor_identifier_u, sensor_index );
    1922 
    1923     LOG(debug)
    1924         << " firstcall " << ( firstcall ? "YES" : "NO " )
    1925         << " ins_idx " << ins_idx






