G4CXTest_shakedown
=========================

Context
----------

* next :doc:`G4CXTest_comparison`



Build and run initial issues : NOTE WAS FORMERLY CALLED G4CXAppTest.sh 
------------------------------------------------------------------------

::

    epsilon:tests blyth$ BP=U::DirList ./G4CXTest.sh 

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x000000010036edaa libU4.dylib`U::DirList(names=size=0, path="/Users/blyth/.opticks/GEOM/J007/CSGFoundry/SSim/juno/PMTSimParamData/PMTSimParamData", ext=0x0000000000000000, exclude=false) at NPU.hh:908
        frame #1: 0x0000000100453038 libU4.dylib`NPFold::load_dir(this=0x000000010c654910, base="/Users/blyth/.opticks/GEOM/J007/CSGFoundry/SSim/juno/PMTSimParamData/PMTSimParamData") at NPFold.h:1248
        frame #2: 0x00000001004521a7 libU4.dylib`NPFold::load(this=0x000000010c654910, base="/Users/blyth/.opticks/GEOM/J007/CSGFoundry/SSim/juno/PMTSimParamData/PMTSimParamData") at NPFold.h:1318
        frame #3: 0x0000000100452070 libU4.dylib`NPFold::Load_(base="/Users/blyth/.opticks/GEOM/J007/CSGFoundry/SSim/juno/PMTSimParamData/PMTSimParamData") at NPFold.h:335
        frame #4: 0x0000000100451aac libU4.dylib`NPFold::Load(base_="$PMTSimParamData_BASE/PMTSimParamData/PMTSimParamData") at NPFold.h:355
        frame #5: 0x00000001004519b4 libU4.dylib`_PMTSimParamData::load(this=0x00007ffeefbfcf10, fold="$PMTSimParamData_BASE/PMTSimParamData/PMTSimParamData") at _PMTSimParamData.h:203
        frame #6: 0x0000000100450e46 libU4.dylib`_PMTSimParamData::Load(data=0x000000010c654620, base="$PMTSimParamData_BASE/PMTSimParamData", relp="PMTSimParamData") at _PMTSimParamData.h:60
        frame #7: 0x000000010044fa17 libU4.dylib`PMTAccessor::LoadData(base="$PMTSimParamData_BASE/PMTSimParamData", relp="PMTSimParamData") at PMTAccessor.h:107
        frame #8: 0x000000010044f5de libU4.dylib`U4Physics::CreateBoundaryProcess() at U4Physics.cc:270
        frame #9: 0x000000010044db1f libU4.dylib`U4Physics::ConstructOp(this=0x000000010c2000a0) at U4Physics.cc:227
        frame #10: 0x000000010044c171 libU4.dylib`U4Physics::ConstructProcess(this=0x000000010c2000a0) at U4Physics.cc:49
        frame #11: 0x0000000102a9d5dc libG4run.dylib`G4VUserPhysicsList::Construct(this=0x000000010c2000a0) at G4VUserPhysicsList.hh:419
        frame #12: 0x0000000102a9d368 libG4run.dylib`G4RunManagerKernel::InitializePhysics(this=0x000000010c164b70) at G4RunManagerKernel.cc:616
        frame #13: 0x0000000102a7c64a libG4run.dylib`G4RunManager::InitializePhysics(this=0x000000010c164a00) at G4RunManager.cc:605
        frame #14: 0x0000000102a7c445 libG4run.dylib`G4RunManager::Initialize(this=0x000000010c164a00) at G4RunManager.cc:567
        frame #15: 0x000000010004a98e G4CXAppTest`G4CXApp::G4CXApp(this=0x000000010c1902e0, runMgr=0x000000010c164a00) at G4CXApp.h:147
        frame #16: 0x000000010004aa8d G4CXAppTest`G4CXApp::G4CXApp(this=0x000000010c1902e0, runMgr=0x000000010c164a00) at G4CXApp.h:140
        frame #17: 0x000000010004c54e G4CXAppTest`G4CXApp::Create() at G4CXApp.h:267
        frame #18: 0x000000010004ca09 G4CXAppTest`main(argc=1, argv=0x00007ffeefbfe620) at G4CXAppTest.cc:35



u4/tests/FewPMT.sh::

    155 # standalone access to PMT data 
    156 #export PMTSimParamData_BASE=$HOME/.opticks/GEOM/J007/CSGFoundry/SSim/juno
    157 export PMTSimParamData_BASE=$HOME/.opticks/GEOM/V1J009/CSGFoundry/SSim/extra/jpmt
    158 



::

    epsilon:tests blyth$ l $HOME/.opticks/GEOM/V1J009/CSGFoundry/SSim/extra/jpmt/PMTSimParamData/
    total 9184
       8 -rw-rw-r--   1 blyth  staff      131 Jul 31 13:47 NPFold_index.txt
       8 -rw-rw-r--   1 blyth  staff      144 Jul 31 13:47 pmtTotal.npy
       8 -rw-rw-r--   1 blyth  staff       48 Jul 31 13:47 pmtTotal_names.txt
    2816 -rw-rw-r--   1 blyth  staff  1440992 Jul 31 13:47 lpmtData.npy
       8 -rw-rw-r--   1 blyth  staff       26 Jul 31 13:47 spmtData_meta.txt
    4008 -rw-rw-r--   1 blyth  staff  2048128 Jul 31 13:47 spmtData.npy
       8 -rw-rw-r--   1 blyth  staff      148 Jul 31 13:47 pmtCatName.npy
       8 -rw-rw-r--   1 blyth  staff       64 Jul 31 13:47 pmtCatName_names.txt
     360 -rw-rw-r--   1 blyth  staff   182576 Jul 31 13:47 pmtCatVec.npy





::

    2023-08-05 00:07:01.724 INFO  [88872] [SEvt::clear_except@1396] SEvt::clear_except
    2023-08-05 00:07:01.724 ERROR [88872] [G4CXApp::SaveMeta@252]  NULL savedir 
    2023-08-05 00:07:01.724 INFO  [88872] [G4CXApp::EndOfEventAction@227] not-(WITH_PMTSIM and POM_DEBUG)
    2023-08-05 00:07:01.724 INFO  [88872] [G4CXOpticks::simulate@450] [
    2023-08-05 00:07:01.724 INFO  [88872] [G4CXOpticks::simulate@451] G4CXOpticks::desc sim 0x2209e30 tr 0x232d500 wd 0x22cee60 gg 0x238c4a0 fd 0x28adda0 cx Y qs Y
    2023-08-05 00:07:01.725 INFO  [88872] [SEvt::clear@1375] SEvt::clear
    terminate called after throwing an instance of 'sutil::CUDA_Exception'
      what():  CUDA error on synchronize with error 'an illegal memory access was encountered' (/data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:926)

    ./G4CXAppTest.sh: line 77: 88872 Aborted                 (core dumped) $bin
    ./G4CXAppTest.sh : run error
    N[blyth@localhost tests]$ 


::

    2023-08-05 00:09:18.038 INFO  [89010] [QSim::UploadComponents@144]   propcom null, snam::PROPCOM propcom.npy
    2023-08-05 00:09:18.039 ERROR [89010] [QSim::UploadComponents@151]  icdf null, snam::ICDF icdf.npy
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::UploadComponents@166] QCerenkov fold - icdf_ - icdf - tex 0
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::UploadComponents@177]  NO QPMT instance  spmt_f NO  qpmt NO 
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::UploadComponents@183] QPMT<float> WITH_CUSTOM4  INSTANCE:NO  
     spmt_f NO  qpmt NO 
    2023-08-05 00:09:18.039 INFO  [89010] [QEvent::QEvent@82] 
    2023-08-05 00:09:18.039 INFO  [89010] [QEvent::init@106]  QEvent::init calling SEvt/setCompProvider 
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::QSim@245] QSim::desc
     this 0x37a6c10 INSTANCE 0x0 QEvent.hh:event 0x37a52c0 qsim.h:sim 0x0
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::init@285] QSim::desc
     this 0x37a6c10 INSTANCE 0x37a6c10 QEvent.hh:event 0x37a52c0 qsim.h:sim 0x37a6bc0
    2023-08-05 00:09:18.039 INFO  [89010] [QSim::init@286] 
    QSim::descComponents
     (QBase)base             YES
     (QEvent)event           YES
     (SEvt)sev               YES
     (QRng)rng               YES
     (QScint)scint           NO 
     (QCerenkov)cerenkov     YES
     (QBnd)bnd               YES
     (QOptical)optical       YES
     (QDebug)debug_          YES
     (QProp)prop             NO 
     (QPMT)pmt               NO 
     (QMultiFilm)multifilm   NO 
     (qsim)sim               YES
     (qsim)d_sim             YES
     (qdebug)dbg             YES
     (qdebug)d_dbg           YES

    2023-08-05 00:09:18.134 INFO  [89010] [G4CXOpticks::setGeometry_@354] ] CSGOptiX::Create 




::

    0174 
     175     const NPFold* spmt_f = ssim->get_spmt_f() ;
     176     QPMT<float>* qpmt = spmt_f ? new QPMT<float>(spmt_f) : nullptr ;
     177     LOG_IF(LEVEL, qpmt == nullptr )
     178         << " NO QPMT instance "
     179         << " spmt_f " << ( spmt_f ? "YES" : "NO " )
     180         << " qpmt " << ( qpmt ? "YES" : "NO " )
     181         ;


    227 /**
    228 SSim::get_jpmt
    229 ---------------
    230 
    231 Note that if the top fold does not have the JPMT_RELP "extra/jpmt"  subfold
    232 then this returns nullptr. 
    233 
    234 So that means must first call SSim::AddExtraSubfold
    235 
    236 **/
    237 
    238 const NPFold* SSim::get_jpmt() const
    239 {
    240     const NPFold* f = top ? top->find_subfold(JPMT_RELP) : nullptr ;
    241     return f ;
    242 }
    243 const SPMT* SSim::get_spmt() const
    244 {
    245     const NPFold* jpmt = get_jpmt();
    246     return jpmt ? new SPMT(jpmt) : nullptr ;
    247 }
    248 const NPFold* SSim::get_spmt_f() const
    249 {
    250     const SPMT* spmt = get_spmt() ;
    251     const NPFold* spmt_f = spmt ? spmt->serialize() : nullptr ;
    252     return spmt_f ;
    253 }



A side need same jpmt info as B side::

    264 G4VProcess* U4Physics::CreateBoundaryProcess()  // static 
    265 {
    266     G4VProcess* proc = nullptr ;
    267 
    268 #if defined(WITH_PMTSIM) && defined(WITH_CUSTOM4)
    269     const char* path = "$PMTSimParamData_BASE" ;  // directory with PMTSimParamData subfolder
    270     const PMTSimParamData* data = PMTAccessor::LoadData(path) ;
    271     LOG(LEVEL) << "load path "  << path << " giving PMTSimParamData.data: " << ( data ? "YES" : "NO" ) ;
    272     //LOG_IF(LEVEL, data != nullptr ) << *data ; 
    273 
    274     const PMTAccessor* pmt = PMTAccessor::Create(data) ;
    275     const C4IPMTAccessor* ipmt = pmt ;
    276     proc = new C4OpBoundaryProcess(ipmt);
    277 


Added jpmt::

    153 G4VPhysicalVolume* G4CXApp::Construct()
    154 {
    155     LOG(info) << "[" ;
    156     const G4VPhysicalVolume* pv_ = U4VolumeMaker::PV() ;
    157     LOG_IF(fatal, pv_ == nullptr) << " FAILED TO CREATE PV : CHECK GEOM envvar " ;
    158     if(pv_ == nullptr) std::raise(SIGINT) ;
    159 
    160     G4VPhysicalVolume* pv = const_cast<G4VPhysicalVolume*>(pv_);
    161     fPV = pv ;
    162     LOG(LEVEL) << " fPV " << ( fPV ? fPV->GetName() : "ERR-NO-PV" ) ;
    163 
    164     LOG(info) << "]" ;
    165 
    166     NPFold* jpmt = NPFold::Load("$PMTSimParamData_BASE") ; // directory with PMTSimParamData subfold
    167     SSim::AddExtraSubfold("jpmt", jpmt );  // needs to be before SetGeometry for SPMT/QPMT hookup  
    168 
    169     G4CXOpticks::SetGeometry(pv) ;
    170 
    171     return pv ;
    172 }


The two SEvt are persisted into the same folder as did not negate the index::

    2023-08-05 00:37:42.660 INFO  [116304] [SEvt::hostside_running_resize_@1768] resizing photon 0 to evt.num_photon 10000
    2023-08-05 00:37:43.174 INFO  [116304] [SEvt::save@3198]  dir /tmp/blyth/opticks/GEOM/FewPMT/G4CXAppTest/ALLVERSION/p001 index 1 instance 1 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    2023-08-05 00:37:43.231 INFO  [116304] [SEvt::clear_except@1396] SEvt::clear_except


    2023-08-05 00:37:43.337 INFO  [116304] [QEvent::gatherComponent@649] [ cmp 524288 proceed 1 a 0
    2023-08-05 00:37:43.337 FATAL [116304] [SEvt::gather_components@2882]  SKIP ASSERT : SHOULD NOW ALWAYS HAVE HIT ARRAY (EVEN IF EMPTY?)  AS HAVE SEvt::gatherHit  
    2023-08-05 00:37:43.337 INFO  [116304] [SEvt::save@3198]  dir /tmp/blyth/opticks/GEOM/FewPMT/G4CXAppTest/ALLVERSION/p001 index 1 instance 0 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    2023-08-05 00:37:43.370 INFO  [116304] [SEvt::clear_except@1396] SEvt::clear_except
    2023-08-05 00:37:43.370 INFO  [116304] [G4CXOpticks::simulate@458] ]



Remove SEvt::SetIndex statics::

    1212 /*
    1213 void SEvt::SetIndex(int index_)
    1214 { 
    1215     if(Exists(0)) Get(0)->setIndex(index_); 
    1216     if(Exists(1)) Get(1)->setIndex(-index_); 
    1217 }
    1218 
    1219 void SEvt::EndIndex(int index)
    1220 {
    1221     if(Exists(0)) Get(0)->endIndex(index); 
    1222     if(Exists(1)) Get(1)->endIndex(-index); 
    1223 }
    1224 */
    1225 


::

    1164 /**
    1165 SEvt::beginOfEvent  (former static SEvt::BeginOfEvent is removed)
    1166 -------------------------------------------------------------------
    1167 
    1168 Called for example from U4Recorder::BeginOfEventAction
    1169 Note that eventID from Geant4 is zero based but the 
    1170 index used for SEvt::SetIndex is 1-based to allow (+ve,-ve) pairs. 
    1171 
    1172 TODO: avoid that complication by just basing 
    1173 the output dir index prefix "p" or "n" depending on SEvt::instance 
    1174 which is either 0 or 1 (SEvt::EGPU or SEvt::ECPU)
    1175 
    1176 **/
    1177 
    1178 void SEvt::beginOfEvent(int eventID)
    1179 {
    1180     int index_ = 1+eventID ;
    1181     LOG(LEVEL) << " index_ " << index_ ;
    1182     setIndex(index_); 
    1183     addFrameGenstep();     // needed for simtrace and input photon running
    1184 }   



Where is insitu opticksMode:3 index negation done ? 

::

    epsilon:sysrap blyth$ opticks-f IntegrationMode
    ./sysrap/SEventConfig.hh:    static constexpr const char* kIntegrationMode = "OPTICKS_INTEGRATION_MODE" ; 
    ./sysrap/SEventConfig.hh:    static int         IntegrationMode(); 
    ./sysrap/SEventConfig.hh:    static void SetIntegrationMode(int mode);   // IntegrationMode configures the integration of Opticks and Framework 
    ./sysrap/SEventConfig.hh:    static int         _IntegrationModeDefault ; 
    ./sysrap/SEventConfig.hh:    static int         _IntegrationMode ; 
    ./sysrap/SEventConfig.cc:int         SEventConfig::_IntegrationModeDefault = -1 ;
    ./sysrap/SEventConfig.cc:int         SEventConfig::_IntegrationMode = SSys::getenvint(kIntegrationMode, _IntegrationModeDefault ); 
    ./sysrap/SEventConfig.cc:int         SEventConfig::IntegrationMode(){ return _IntegrationMode ; }
    ./sysrap/SEventConfig.cc:bool        SEventConfig::GPU_Simulation(){  return _IntegrationMode == 1 || _IntegrationMode == 3 ; }
    ./sysrap/SEventConfig.cc:bool        SEventConfig::CPU_Simulation(){  return _IntegrationMode == 2 || _IntegrationMode == 3 ; }
    ./sysrap/SEventConfig.cc:void SEventConfig::SetIntegrationMode(int mode){ _IntegrationMode = mode ; Check() ; }
    ./sysrap/SEventConfig.cc:   assert( _IntegrationMode >= -1 && _IntegrationMode <= 3 ); 
    ./sysrap/SEventConfig.cc:       << std::setw(25) << kIntegrationMode
    ./sysrap/SEventConfig.cc:       << std::setw(20) << " IntegrationMode " << " : " << IntegrationMode() 
    ./sysrap/SEvt.cc:Creates 0, 1 OR 2 SEvt depending on SEventConfig::IntegrationMode()::
    ./sysrap/SEvt.cc:    int integrationMode = SEventConfig::IntegrationMode() ; 
    ./sysrap/SEvt.cc:       << " SEventConfig::IntegrationMode " << SEventConfig::IntegrationMode()
    ./sysrap/SEvt.cc:    ss << std::setw(c1) << " SEventConfig::IntegrationMode "  << div << SEventConfig::IntegrationMode() << std::endl ; 
    epsilon:opticks blyth$ 

::

    [ 91%] Built target PhysiSim
    Consolidate compiler generated dependencies of target OPSimulator
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc: In member function 'void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int)':
    /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:158:11: error: 'SetIndex' is not a member of 'SEvt'
         SEvt::SetIndex(index);   // IS THIS NEEDED ? WHY ?
               ^~~~~~~~

::

    150 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
    151 {
    152     if(m_pmthitmerger_opticks == nullptr) m_pmthitmerger_opticks = m_jpmt->getMergerOpticks();
    153     bool gpu_sim = gpu_simulation();
    154 
    155     LOG(LEVEL) << "[ " << m_jpmt->desc() ;
    156 
    157     int index = 1+eventID ;
    158     SEvt::SetIndex(index);
    159    // IS THIS NEEDED ? WHY ? Presumably as want to save some debug stuff before the simulate that sets the index later
    160    // HOW TO AVOID THAT ? USE add_array SO DONT NEED TO CHANGE THE index ? 
    161 
    162     EndOfEvent_Debug(eventID) ;
    163 
    164     if(gpu_sim)
    165     {
    166         EndOfEvent_Simulate(eventID) ;
    167     }
    168 
    169 
    170     LOG(LEVEL) << "] " << m_jpmt->desc() ;
    171 }






