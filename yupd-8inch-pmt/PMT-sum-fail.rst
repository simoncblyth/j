After switch to polycone neck get further
==========================================


ljbb::

    2026-01-09 15:22:54.041 INFO  [2554828] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    python: /home/blyth/opticks/sysrap/SPMT.h:627: void SPMT::init_total(): Assertion `total.ALL == total.SUM()' failed.
     *** Break *** abort


    #6  0x00007f28b868bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #7  0x00007f28b863eb46 in raise () from /lib64/libc.so.6
    #8  0x00007f28b8628833 in abort () from /lib64/libc.so.6
    #9  0x00007f28b862875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007f28b8637886 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f287f3d5bf9 in SPMT::init_total (this=0x377d21a0) at /home/blyth/opticks/sysrap/SPMT.h:627
    #12 0x00007f287f3d549c in SPMT::init (this=0x377d21a0) at /home/blyth/opticks/sysrap/SPMT.h:538
    #13 0x00007f287f3d53a1 in SPMT::SPMT (this=0x377d21a0, jpmt_=0x37805020) at /home/blyth/opticks/sysrap/SPMT.h:500
    #14 0x00007f287f3ab06d in SSim::get_spmt (this=0xd856bd0) at /home/blyth/opticks/sysrap/SSim.cc:383
    #15 0x00007f287f3ab202 in SSim::get_spmt_f (this=0xd856bd0) at /home/blyth/opticks/sysrap/SSim.cc:407
    #16 0x00007f287fc707ef in QSim::UploadComponents (ssim=0xd856bd0) at /home/blyth/opticks/qudarap/QSim.cc:199
    #17 0x00007f2881c3bb2e in CSGOptiX::InitSim (ssim=0xd856bd0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:276
    #18 0x00007f2881c3c17e in CSGOptiX::Create (fd=0x273462a0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:353
    #19 0x00007f2881fcb10c in G4CXOpticks::CreateSimulator (fd=0x273462a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:419
    #20 0x00007f2881fcaba8 in G4CXOpticks::setGeometry_ (this=0xd8c0e80, fd_=0x273462a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:380
    #21 0x00007f2881fca9a1 in G4CXOpticks::setGeometry (this=0xd8c0e80, fd_=0x273462a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:347
    #22 0x00007f2881fca5ab in G4CXOpticks::setGeometry (this=0xd8c0e80, world=0xb7f47a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:320
    #23 0x00007f2881fc8aa1 in G4CXOpticks::SetGeometry (world=0xb7f47a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:79
    #24 0x00007f2881fc8d50 in G4CXOpticks::SetGeometry_JUNO (world=0xb7f47a0, sd=0x75c1230, jpmt=0xc8aa380, jlut=0xd8560a0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:117
    #25 0x00007f287e550ce2 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xb7f47a0, sd=0x75c1230, ppd=0x7599b30, psd=0x7674190, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #26 0x00007f287e514aa8 in LSExpDetectorConstruction::setupOpticks (this=0xb55c1f0, world=0xb7f47a0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #27 0x00007f287e514348 in LSExpDetectorConstruction::Construct (this=0xb55c1f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #28 0x00007f288780792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #29 0x00007f2887807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #30 0x00007f288f09bb0b in DetSimAlg::initialize (this=0x75ecfe0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #31 0x00007f2893dd0b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so


Add SPMT.h debug when the assert it tripped::

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 126 LVID -1 name Waterdistributor_2 soname Waterdistributor_2
    2026-01-09 15:40:49.723 INFO  [3296207] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    SPMT::init_total x_total_ALL NO [SPMT_Total.desc
             CD_LPMT  17612
                SPMT  25600
                  WP   2400
         WP_ATM_LPMT    348
         WP_ATM_MPMT      0
          WP_WAL_PMT      5
                 ALL  46565
                SUM:  45965
          SUM()==ALL    NO 
           SUM()-ALL   -600
    ]SPMT_Total.desc

    python: /home/blyth/opticks/sysrap/SPMT.h:635: void SPMT::init_total(): Assertion `x_total_ALL' failed.
     *** Break *** abort



Found a zero::

    503 inline NP* _PMTSimParamData::serialize_pmtTotal() const
    504 {
    505     NPX::KV<int> kv ;
    506     kv.add("PmtTotal",      data.m_PmtTotal);
    507     kv.add("PmtTotal_SPMT", data.m_PmtTotal_SPMT );
    508     kv.add("PmtTotal_WP",   data.m_PmtTotal_WP );
    509     kv.add("PmtTotal_WP_ATM_LPMT", data.m_PmtTotal_WP_ATM_lpmt );
    510     kv.add("PmtTotal_WP_ATM_MPMT", 0 );
    511     kv.add("PmtTotal_WP_WAL_PMT",  data.m_PmtTotal_WP_WAL_pmt );
    512     kv.add("PmtTotal_ALL",  data.m_PmtTotal_ALL );
    513     return kv.values() ;
    514 }




Fixing that, get further::

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 126 LVID -1 name Waterdistributor_2 soname Waterdistributor_2
    2026-01-09 16:02:54.587 INFO  [122149] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    SPMT::init_pmtNum pmtNum.sstr (6, ) init_pmtNum_FAKE_WHEN_MISSING 1
    [SPMT::init_pmtNum
    [SPMT_Num.desc
    m_nums_cd_lpmt     :  17612
    m_nums_cd_spmt     :  25600
    m_nums_wp_lpmt     :   2400
    m_nums_wp_atm_lpmt :    348
    m_nums_wp_wal_pmt  :      5
    m_nums_wp_atm_mpmt :    600
    ALL                :  46565
    SUM                :  46565
    SUM==ALL           :    YES
    ]SPMT_Num.desc
    ]SPMT::init_pmtNum
    SPMT::init_qeScale qeScale.sstr (46565, 1, ) qeScale_shape_expect NO  expect_qeScale_items 45965
    [s_pmt::desc
                      NUM_CAT      3
                     NUM_LAYR      4
                     NUM_PROP      2
                  NUM_CD_LPMT  17612
                     NUM_SPMT  25600
                       NUM_WP   2400
              NUM_WP_ATM_LPMT    348
              NUM_WP_ATM_MPMT    600
               NUM_WP_WAL_PMT      5
           NUM_CD_LPMT_AND_WP  20012
                      NUM_ALL  46565
                  NUM_LPMTIDX  20965
            NUM_CONTIGUOUSIDX  46565
         NUM_OLDCONTIGUOUSIDX  46565
               OFFSET_CD_LPMT      0
           OFFSET_CD_LPMT_END  17612
               OFFSET_CD_SPMT  20000
           OFFSET_CD_SPMT_END  45600
                OFFSET_WP_PMT  50000
            OFFSET_WP_PMT_END  52400
           OFFSET_WP_ATM_LPMT  52400
       OFFSET_WP_ATM_LPMT_END  52748
           OFFSET_WP_ATM_MPMT  53000
       OFFSET_WP_ATM_MPMT_END  53600
            OFFSET_WP_WAL_PMT  54000
        OFFSET_WP_WAL_PMT_END  54005
    ]s_pmt::desc
    python: /home/blyth/opticks/sysrap/SPMT.h:886: void SPMT::init_qeScale(): Assertion `qeScale_shape_expect' failed.
     *** Break *** abort


Introduce WITH_MPMT to SPMT.h to handle different branches needs.


Making portrait::

   CAM=orthographic ZOOM=0.4 EYE=0,2,0 cxr_min.sh









