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




Same Again ? but i thought that was fixed ?
----------------------------------------------

::

    commit bf77b63635363dd4799883f3a984a5a9f48bdd70
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Tue Dec 19 19:40:42 2023 +0800

        try to fix the off-by-one sensor_identifier bug

    M       sysrap/SEvt.cc
    M       u4/U4Tree.h



::

    Begin of Event --> 116
    2024-01-19 15:32:27.108 INFO  [306385] [QSim::simulate@376]  eventID 116 dt    0.009264 ph       9204 ph/M          0 ht       1748 ht/M          0 reset_ NO 
    2024-01-19 15:32:27.133 INFO  [306385] [SEvt::save@3953] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A116 [genstep,hit]
    junoSD_PMT_v2::EndOfEvent eventID 116 opticksMode 1 hitCollection 1748 hcMuon 0 GPU YES
    hitCollectionTT.size: 0 userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2024-01-19 07:32:27.134933000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2024-01-19 07:32:27.137078000Z
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (117) 
    junoSD_PMT_v2::Initialize eventID 117
    Begin of Event --> 117
    2024-01-19 15:32:27.148 INFO  [306385] [QSim::simulate@376]  eventID 117 dt    0.009222 ph       8753 ph/M          0 ht       1673 ht/M          0 reset_ NO 
    2024-01-19 15:32:27.172 INFO  [306385] [SEvt::save@3953] /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/A117 [genstep,hit]
    junoSD_PMT_v2::EndOfEvent eventID 117 opticksMode 1 hitCollection 1673 hcMuon 0 GPU YES
    hitCollectionTT.size: 0 userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2024-01-19 07:32:27.173474000Z

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc8288da5 in DataModelWriterWithSplit::fill_hits(JM::SimEvt*, G4Event const*) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    (gdb) 


    #0  0x00007fffc8288da5 in DataModelWriterWithSplit::fill_hits(JM::SimEvt*, G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    #1  0x00007fffc828abf9 in DataModelWriterWithSplit::EndOfEventAction(G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libAnalysisCode.so
    #2  0x00007fffc7f27558 in MgrOfAnaElem::EndOfEventAction(G4Event const*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libDetSimAlg.so
    #3  0x00007fffd1164242 in G4EventManager::DoProcessing(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #4  0x00007fffc8403630 in G4SvcRunManager::SimulateEvent(int) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libG4SvcLib.so
    #5  0x00007fffc7f1d63a in DetSimAlg::execute() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/junosw/InstallArea/lib64/libDetSimAlg.so
    #6  0x00007fffd4e3e511 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd4e42c1d in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffd4e3e0b4 in Task::run() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd4ef8943 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120_opticks/Pre-Release/J23.1.0-rc6/sniper/InstallArea/python/Sniper/libSniperPython.so
    #10 0x00007fffd4de65d5 in boost::python::objects::function::call(_object*, _object*) const ()





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

::

    367 inline void sframe::set_identity(int ins, int gas, int sensor_identifier, int sensor_index ) // formerly set_ins_gas_ias
    368 {
    369     aux.q0.i.x = ins ;
    370     aux.q0.i.y = gas ;
    371     aux.q0.i.z = sensor_identifier ;
    372     aux.q0.i.w = sensor_index  ;
    373 }
    374 inline int sframe::ins() const { return aux.q0.i.x ; }
    375 inline int sframe::gas() const { return aux.q0.i.y ; }
    376 inline int sframe::sensor_identifier() const { return aux.q0.i.z ; }
    377 inline int sframe::sensor_index() const {      return aux.q0.i.w ; }
    378 


::

    057 inline void U4HitGet::FromEvt(U4Hit& hit, unsigned idx, int eidx )
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

    4216 void SEvt::getLocalHit(sphit& ht, sphoton& lp, unsigned idx) const
    4217 {
    4218     getHit(lp, idx);   // copy *idx* hit from NP array into sphoton& lp struct 
    4219 
    4220     sframe fr ;
    4221     getPhotonFrame(fr, lp);
    4222     fr.transform_w2m(lp);
    4223 
    4224     ht.iindex = fr.inst() ;
    4225     ht.sensor_identifier = fr.sensor_identifier();
    4226     ht.sensor_index = fr.sensor_index();
    4227 }




::

    399 /**
    400 CSGImport::importInst
    401 ---------------------------
    402 
    403 The CSGFoundry calls should parallel CSG_GGeo_Convert::addInstances
    404 the source is the stree instead of GGeo/GMergedMesh etc..
    405 
    406 **/
    407 
    408 void CSGImport::importInst()
    409 {
    410     fd->addInstanceVector( st->inst_f4 );
    411 }


::

    1935 /**
    1936 CSGFoundry::addInstanceVector
    1937 ------------------------------
    1938 
    1939 stree.h/snode.h uses sensor_identifier -1 to indicate not-a-sensor, but 
    1940 that is not convenient on GPU due to OptixInstance.instanceId limits.
    1941 Hence here make transition by adding 1 and treating 0 as not-a-sensor, 
    1942 with the sqat4::incrementSensorIdentifier method
    1943 
    1944 **/
    1945 
    1946 void CSGFoundry::addInstanceVector( const std::vector<glm::tmat4x4<float>>& v_inst_f4 )
    1947 {
    1948     assert( inst.size() == 0 );
    1949     int num_inst = v_inst_f4.size() ;
    1950 
    1951     for(int i=0 ; i < num_inst ; i++)
    1952     {
    1953         const glm::tmat4x4<float>& inst_f4 = v_inst_f4[i] ;
    1954         const float* tr16 = glm::value_ptr(inst_f4) ;
    1955         qat4 instance(tr16) ;
    1956         instance.incrementSensorIdentifier() ; // GPU side needs 0 to mean "not-a-sensor"
    1957         inst.push_back( instance );
    1958     }
    1959 }
    1960 



