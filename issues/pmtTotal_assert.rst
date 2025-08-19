pmtTotal_assert
===================


A local.sh testing::


    A[blyth@localhost junosw]$ t ljbb
    ljbb () 
    { 
        : ~/local.sh;
        : use this in fresh tab to setup env and perform the build;
        local_oj_build;
        oj_build
    }


Assert during geometry convert::

    A[blyth@localhost junosw]$ ljbb
    ...

    updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 109 LVID -1 name uni1_0 soname uni1_0
    2025-08-18 11:48:20.503 INFO  [1218889] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000 SEventConfig::MaxCurand 1000000000
    python: /home/blyth/opticks/sysrap/SPMT.h:532: void SPMT::init_total(): Assertion `total.ALL == ALL' failed.
     *** Break *** abort


    #9  0x00007fc6fb82875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007fc6fb8373c6 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007fc6c2ba679d in SPMT::init_total (this=0x2dbb0d20) at /home/blyth/opticks/sysrap/SPMT.h:532
    #12 0x00007fc6c2ba633e in SPMT::init (this=0x2dbb0d20) at /home/blyth/opticks/sysrap/SPMT.h:482
    #13 0x00007fc6c2ba6247 in SPMT::SPMT (this=0x2dbb0d20, jpmt_=0x2dbc6f20) at /home/blyth/opticks/sysrap/SPMT.h:444
    #14 0x00007fc6c2b8a0d9 in SSim::get_spmt (this=0xce06f00) at /home/blyth/opticks/sysrap/SSim.cc:347
    #15 0x00007fc6c2b8a26e in SSim::get_spmt_f (this=0xce06f00) at /home/blyth/opticks/sysrap/SSim.cc:371
    #16 0x00007fc6c306dbb9 in QSim::UploadComponents (ssim=0xce06f00) at /home/blyth/opticks/qudarap/QSim.cc:196
    #17 0x00007fc6c502f2c2 in CSGOptiX::InitSim (ssim=0xce06f00) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:283
    #18 0x00007fc6c502f90d in CSGOptiX::Create (fd=0x213df550) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:354
    #19 0x00007fc6c53a8ab4 in G4CXOpticks::setGeometry_ (this=0xce0f490, fd_=0x213df550) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:377
    #20 0x00007fc6c53a88ad in G4CXOpticks::setGeometry (this=0xce0f490, fd_=0x213df550) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:344



::

     095 struct SPMT_Total
      96 {
      97     static constexpr const int FIELDS = 4 ;
      98 
      99     int CD_LPMT ;
     100     int SPMT ;
     101     int WP ;
     102     int ALL ;
     103 
     104     std::string desc() const ;
     105 };
     106 
     107 inline std::string SPMT_Total::desc() const
     108 {
     109     std::stringstream ss ;
     110     ss << "SPMT_Total"
     111        << " CD_LPMT:" << std::setw(6) << CD_LPMT
     112        << " SPMT:" << std::setw(6) << SPMT
     113        << " WP:" << std::setw(6) << WP
     114        << " ALL:" << std::setw(6) << ALL
     115        ;
     116     std::string str = ss.str() ;
     117     return str ;
     118 }


Removed assert on the SUM while updating totals::

     507 inline void SPMT::init_total()
     508 {
     509     if( PMTSimParamData == nullptr )
     510     {
     511         std::cout << "SPMT::init_total exit as PMTSimParamData is NULL\n" ;
     512         return ;
     513     }
     514     assert( PMTSimParamData );
     515     const NP* pmtTotal_ = PMTSimParamData->get("pmtTotal") ; // (4,)
     516 
     517     assert( pmtTotal_ && pmtTotal_->uifc == 'i' && pmtTotal_->ebyte == 4 );
     518     assert( pmtTotal_->shape.size() == 1 && pmtTotal_->shape[0] == SPMT_Total::FIELDS );
     519     assert( pmtTotal_->names.size() == SPMT_Total::FIELDS );
     520 
     521     const int* pmtTotal_v = pmtTotal_->cvalues<int>();
     522 
     523     std::vector<std::string> xnames = {"PmtTotal", "PmtTotal_SPMT", "PmtTotal_WP", "PmtTotal_ALL" };
     524     assert( pmtTotal_->names == xnames );
     525 
     526     total.CD_LPMT = pmtTotal_v[0] ;
     527     total.SPMT = pmtTotal_v[1] ;
     528     total.WP = pmtTotal_v[2] ;
     529     total.ALL = pmtTotal_v[3] ;
     530 
     531     int SUM = total.CD_LPMT + total.SPMT + total.WP ;
     532 
     533     std::cout << "SPMT::init_total " << total.desc() << "\n" << " SUM " << SUM << "\n" ;
     534  
     535     //assert( total.ALL == SUM );
     536     assert( total.CD_LPMT == 17612 );
     537     assert( total.SPMT == 25600 ) ;
     538     assert( total.WP == 2400 ) ;
     539     
     540     assert( s_pmt::NUM_CD_LPMT == total.CD_LPMT );
     541     assert( s_pmt::NUM_SPMT == total.SPMT );
     542     assert( s_pmt::NUM_WP == total.WP );
     543     assert( s_pmt::NUM_CD_LPMT_AND_WP == total.CD_LPMT + total.WP );
     544 }


jcv PMTSimParamData::

     64     int                            m_PmtTotal_WP_ATM_lpmt ;
     65     int                            m_PmtTotal_WP_WAL_pmt ;



::

    503 inline NP* _PMTSimParamData::serialize_pmtTotal() const
    504 {
    505     NPX::KV<int> kv ;
    506     kv.add("PmtTotal",      data.m_PmtTotal);
    507     kv.add("PmtTotal_SPMT", data.m_PmtTotal_SPMT );
    508     kv.add("PmtTotal_WP",   data.m_PmtTotal_WP );
    509     kv.add("PmtTotal_ALL",  data.m_PmtTotal_ALL );
    510     return kv.values() ;
    511 }
    512 inline void _PMTSimParamData::import_pmtTotal(const NP* pmtTotal )
    513 {
    514     data.m_PmtTotal      = pmtTotal->get_named_value<int>("PmtTotal",      -1) ;
    515     data.m_PmtTotal_SPMT = pmtTotal->get_named_value<int>("PmtTotal_SPMT", -1) ;
    516     data.m_PmtTotal_WP   = pmtTotal->get_named_value<int>("PmtTotal_WP",   -1) ;
    517     data.m_PmtTotal_ALL  = pmtTotal->get_named_value<int>("PmtTotal_ALL",  -1) ;
    518 }



After avoid the SUM assert::


    updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 109 LVID -1 name uni1_0 soname uni1_0
    2025-08-18 14:20:54.375 INFO  [1478884] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000 SEventConfig::MaxCurand 1000000000
    SPMT::init_total SPMT_Total CD_LPMT: 17612 SPMT: 25600 WP:  2400 ALL: 45965
     SUM 45612
    python: /home/blyth/opticks/sysrap/SPMT.h:651: void SPMT::init_qeScale(): Assertion `qeScale->shape[0] == s_pmt::NUM_CD_LPMT + s_pmt::NUM_SPMT + s_pmt::NUM_WP' failed.
     *** Break *** abort


    #8  0x00007ff9bdc28833 in abort () from /lib64/libc.so.6
    #9  0x00007ff9bdc2875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007ff9bdc373c6 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007ff984f87c09 in SPMT::init_qeScale (this=0x2eacc1a0) at /home/blyth/opticks/sysrap/SPMT.h:651
    #12 0x00007ff984fa6362 in SPMT::init (this=0x2eacc1a0) at /home/blyth/opticks/sysrap/SPMT.h:485
    #13 0x00007ff984fa6247 in SPMT::SPMT (this=0x2eacc1a0, jpmt_=0x2eae0d00) at /home/blyth/opticks/sysrap/SPMT.h:444
    #14 0x00007ff984f8a0d9 in SSim::get_spmt (this=0xdd20140) at /home/blyth/opticks/sysrap/SSim.cc:347
    #15 0x00007ff984f8a26e in SSim::get_spmt_f (this=0xdd20140) at /home/blyth/opticks/sysrap/SSim.cc:371
    #16 0x00007ff98546dbb9 in QSim::UploadComponents (ssim=0xdd20140) at /home/blyth/opticks/qudarap/QSim.cc:196
    #17 0x00007ff98734f2c2 in CSGOptiX::InitSim (ssim=0xdd20140) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:283
    #18 0x00007ff98734f90d in CSGOptiX::Create (fd=0xbc01390) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:354
    #19 0x00007ff9876c8ab4 in G4CXOpticks::setGeometry_ (this=0xdd5cac0, fd_=0xbc01390) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:377
    #20 0x00007ff9876c88ad in G4CXOpticks::setGeometry (this=0xdd5cac0, fd_=0xbc01390) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:344
    #21 0x00007ff9876c84c1 in G4CXOpticks::setGeometry (this=0xdd5cac0, world=0xbffdd00) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:317
    #22 0x00007ff9876c6929 in G4CXOpticks::SetGeometry (world=0xbffdd00) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #23 0x00007ff9876c6bd8 in G4CXOpticks::SetGeometry_JUNO (world=0xbffdd00, sd=0x8051140, jpmt=0xdc907b0, jlut=0xdd1f530) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #24 0x00007ff9845994cc in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xbffdd00, sd=0x8051140, ppd=0x800a230, psd=0x815b4c0, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #25 0x00007ff98455efd2 in LSExpDetectorConstruction::setupOpticks (this=0xbc2a7a0, world=0xbffdd00) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:464
    #26 0x00007ff98455e872 in LSExpDetectorConstruction::Construct (this=0xbc2a7a0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:385


Reach qeScale->shape[0] assert::

    0647 void SPMT::init_qeScale()
     648 {
     649     if(!qeScale) return ;
     650     assert( qeScale && qeScale->uifc == 'f' && qeScale->ebyte == 8 );
     651     assert( qeScale->shape[0] == s_pmt::NUM_CD_LPMT + s_pmt::NUM_SPMT + s_pmt::NUM_WP  );
     652     assert( qeScale_v );
     653 }


Avoid that, adding debug. Observe that have 353 more entries in qeScale::

    In [1]: 45965 - 45612
    Out[1]: 353

::

    s_bb::IncludeAABB 
     inital_aabb  [-206.200,-206.200,-135.000,206.200,206.200,-13.000]
     other_aabb   [102.966,-128.966,-135.000,128.966,-102.966,-35.000]COMBINE
     updated_aabb [-206.200,-206.200,-135.000,206.200,206.200,-13.000]

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 109 LVID -1 name uni1_0 soname uni1_0
    2025-08-18 15:00:25.390 INFO  [1896107] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000 SEventConfig::MaxCurand 1000000000
    SPMT::init_total SPMT_Total CD_LPMT: 17612 SPMT: 25600 WP:  2400 ALL: 45965
     SUM 45612
    SPMT::init_qeScale qeScale.sstr (45965, 1, ) qeScale_shape_expect NO  expect_qeScale_items 45612
    [s_pmt::desc
                      NUM_CAT      3
                     NUM_LAYR      4
                     NUM_PROP      2
                  NUM_CD_LPMT  17612
                     NUM_SPMT  25600
                       NUM_WP   2400
           NUM_CD_LPMT_AND_WP  20012
                      NUM_ALL  45612
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


    2025-08-18 15:00:25.706 INFO  [1896107] [G4CXOpticks::setGeometry@320] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    2025-08-18 15:00:25.706 INFO  [1896107] [G4CXOpticks::SaveGeometry@594]  save to dir /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug configured via envvar G4CXOpticks__SaveGeometry_DIR
    2025-08-18 15:00:25.706 INFO  [1896107] [G4CXOpticks::saveGeometry@552] [ /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug
    G4CXOpticks::saveGeometry [ /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug
    2025-08-18 15:00:25.712 INFO  [1896107] [U4GDML::write@292]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    2025-08-18 15:00:25.712 INFO  [1896107] [U4GDML::write_@319] [



check qeScale serialization and usage
----------------------------------------

jcv _PMTSimParamData::

    250 inline NPFold* _PMTSimParamData::serialize() const
    251 {
    252     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    253     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;
    254     NP* lpmtCat = NPX::ArrayFromMapUnordered<int, int>(data.m_map_pmt_category) ;
    255     NP* pmtCat = NPX::ArrayFromDiscoMapUnordered<int>(data.m_all_pmt_category) ;
    256     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;



s_pmt.h updates for 6 PMT types
---------------------------------

::

    (ok) A[blyth@localhost opticks]$ git commit -m "start adding support for three more PMT types WP_ATM_LPMT WP_ATM_MPMT WP_WAL_PMT"
    [master 2201e3e11] start adding support for three more PMT types WP_ATM_LPMT WP_ATM_MPMT WP_WAL_PMT



qudarap qpmt.h qsim.h usage of s_pmt.h
----------------------------------------


::

    (ok) A[blyth@localhost qudarap]$ grep s_pmt *.* | grep -v ::NUM
    qpmt.h:#include "s_pmt.h"
    qpmt.h:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    qpmt.h:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    qpmt.h:    int spmtidx = s_pmt::spmtidx_from_pmtid(spmtid);
    qpmt.h:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    qpmt.h:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);  // lpmtidx:-1 FOR SPMT, BUT THAT SHOULD NEVER HAPPEN
    qpmt.h:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    QPMT.hh:#include "s_pmt.h"
    QPMT.hh:    int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    QPMT.hh:        int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);
    QPMT.hh:        int spmtidx = s_pmt::spmtidx_from_pmtid(spmtid);
    qsim.h:        if( s_pmt::is_spmtid(pmtid) )
    qsim.h:    if(lpmtid < s_pmt::OFFSET_CD_LPMT || lpmtid >= s_pmt::OFFSET_WP_PMT_END )
    (ok) A[blyth@localhost qudarap]$ 



