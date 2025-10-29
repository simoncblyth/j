SPMT__init_lcqs_copyno_pmtid_assert
====================================


release with fix
------------------

::

    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.6/el9_amd64_gcc11/2025_10_29/envset.sh





ljbb reproduce
---------------

::

    Thread 1 (Thread 0x7f10e861f5c0 (LWP 2360947) "python"):
    #0  0x00007f10e7cd8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f10e7c4b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f10d9ef6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f10e7e8cf73 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f10d9ef4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f10e7c8bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #7  0x00007f10e7c3eb46 in raise () from /lib64/libc.so.6
    #8  0x00007f10e7c28833 in abort () from /lib64/libc.so.6
    #9  0x00007f10e7c2875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007f10e7c37886 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f10aefba6f2 in SPMT::init_lcqs (this=0x355aca60) at /home/blyth/opticks/sysrap/SPMT.h:960
    #12 0x00007f10aefb8cae in SPMT::init (this=0x355aca60) at /home/blyth/opticks/sysrap/SPMT.h:494
    #13 0x00007f10aefb8b4a in SPMT::SPMT (this=0x355aca60, jpmt_=0x36c019a0) at /home/blyth/opticks/sysrap/SPMT.h:445
    #14 0x00007f10aef91391 in SSim::get_spmt (this=0xce721e0) at /home/blyth/opticks/sysrap/SSim.cc:383
    #15 0x00007f10aef91526 in SSim::get_spmt_f (this=0xce721e0) at /home/blyth/opticks/sysrap/SSim.cc:407
    #16 0x00007f10af46f5ef in QSim::UploadComponents (ssim=0xce721e0) at /home/blyth/opticks/qudarap/QSim.cc:196
    #17 0x00007f10b137aafa in CSGOptiX::InitSim (ssim=0xce721e0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:276
    #18 0x00007f10b137b14a in CSGOptiX::Create (fd=0x2686b710) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:353
    #19 0x00007f10b16febfc in G4CXOpticks::setGeometry_ (this=0xcf93f40, fd_=0x2686b710) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:391
    #20 0x00007f10b16fe9f5 in G4CXOpticks::setGeometry (this=0xcf93f40, fd_=0x2686b710) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:358
    #21 0x00007f10b16fe609 in G4CXOpticks::setGeometry (this=0xcf93f40, world=0xaec8ae0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:331
    #22 0x00007f10b16fcac1 in G4CXOpticks::SetGeometry (world=0xaec8ae0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:80
    #23 0x00007f10b16fcd70 in G4CXOpticks::SetGeometry_JUNO (world=0xaec8ae0, sd=0xa701c50, jpmt=0xce3eff0, jlut=0xce715c0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:118
    #24 0x00007f10ae598726 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xaec8ae0, sd=0xa701c50, ppd=0x6fadd10, psd=0x6fae740, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #25 0x00007f10ae55d4a0 in LSExpDetectorConstruction::setupOpticks (this=0xaadbf20, world=0xaec8ae0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #26 0x00007f10ae55cd40 in LSExpDetectorConstruction::Construct (this=0xaadbf20) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #27 0x00007f10b74b692e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #28 0x00007f10b74b6afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so





local test with g4cx/tests/G4CXTest_GEOM.sh
---------------------------------------------


Change GEOM to pick up the recent geometry::

     41 if [ "$GEOM" == "J25_4_0_Opticks_v0_5_5" ]; then
     42     export ${GEOM}_CFBaseFromGEOM=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.5/el9_amd64_gcc11/2025_10_24/.opticks/GEOM/$GEOM

then::

    g4cx/tests/G4CXTest_GEOM.sh


::

    SPMT::init_qeScale qeScale.sstr (45965, 1, ) qeScale_shape_expect YES expect_qeScale_items 45965
    [s_pmt::desc
                      NUM_CAT      3
                     NUM_LAYR      4
                     NUM_PROP      2
                  NUM_CD_LPMT  17612
                     NUM_SPMT  25600
                       NUM_WP   2400
              NUM_WP_ATM_LPMT    348
              NUM_WP_ATM_MPMT      0
               NUM_WP_WAL_PMT      5
           NUM_CD_LPMT_AND_WP  20012
                      NUM_ALL  45965
                  NUM_LPMTIDX  20365
            NUM_CONTIGUOUSIDX  45965
         NUM_OLDCONTIGUOUSIDX  45965
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
    SPMT::init_lcqs
     i/lpmtidx  20360
     lpmtidx2  20360
     oldcontiguousidx  45960
     s_pmt::NUM_OLDCONTIGUOUSIDX  45965
     s_pmt::NUM_LPMTIDX  20365
     pmtid  54000
     copyno  53000
     cat      4
     copyno_pmtid_consistent NO 
    G4CXTest: /home/blyth/opticks/sysrap/SPMT.h:964: void SPMT::init_lcqs(): Assertion `copyno_pmtid_consistent' failed.
    g4cx/tests/G4CXTest_GEOM.sh: line 421: 3087625 Aborted                 (core dumped) $bin
    g4cx/tests/G4CXTest_GEOM.sh run error
    (ok) A[blyth@localhost opticks]$ 



Reproduce with SPMT_test.sh::

    /home/blyth/opticks/sysrap/tests/SPMT_test.sh : build OK
    SPMT::init_pmtCat expected_type YES expected_shape[first-dim-same-as-total.ALL] NO  pmtCat (46565, 2, ) total [SPMT_Total
             CD_LPMT  17612
                SPMT  25600
                  WP   2400
         WP_ATM_LPMT    348
         WP_ATM_MPMT      0
          WP_WAL_PMT      5
                 ALL  45965
                SUM:  45965
            SUM==ALL    YES
    ]SPMT_Total


Looks like the MPMT::

    In [19]: 45965 - 46565
    Out[19]: -600




    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno[pmtCat_v]  53000 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT_test: ../SPMT.h:959: void SPMT::init_lcqs(): Assertion `copyno_pmtid_consistent' failed.
    /home/blyth/opticks/sysrap/tests/SPMT_test.sh: line 77: 3098098 Aborted                 (core dumped) $bin
    /home/blyth/opticks/sysrap/tests/SPMT_test.sh run error


cat 4 PMT fail::

    SPMT::init_lcqs i/lpmtidx  20340 lpmtidx2  20340 oldcontiguousidx  45940 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52728 copyno  52728 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20341 lpmtidx2  20341 oldcontiguousidx  45941 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52729 copyno  52729 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20342 lpmtidx2  20342 oldcontiguousidx  45942 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52730 copyno  52730 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20343 lpmtidx2  20343 oldcontiguousidx  45943 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52731 copyno  52731 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20344 lpmtidx2  20344 oldcontiguousidx  45944 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52732 copyno  52732 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20345 lpmtidx2  20345 oldcontiguousidx  45945 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52733 copyno  52733 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20346 lpmtidx2  20346 oldcontiguousidx  45946 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52734 copyno  52734 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20347 lpmtidx2  20347 oldcontiguousidx  45947 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52735 copyno  52735 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20348 lpmtidx2  20348 oldcontiguousidx  45948 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52736 copyno  52736 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20349 lpmtidx2  20349 oldcontiguousidx  45949 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52737 copyno  52737 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20350 lpmtidx2  20350 oldcontiguousidx  45950 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52738 copyno  52738 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20351 lpmtidx2  20351 oldcontiguousidx  45951 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52739 copyno  52739 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20352 lpmtidx2  20352 oldcontiguousidx  45952 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52740 copyno  52740 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20353 lpmtidx2  20353 oldcontiguousidx  45953 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52741 copyno  52741 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20354 lpmtidx2  20354 oldcontiguousidx  45954 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52742 copyno  52742 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20355 lpmtidx2  20355 oldcontiguousidx  45955 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52743 copyno  52743 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20356 lpmtidx2  20356 oldcontiguousidx  45956 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52744 copyno  52744 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20357 lpmtidx2  20357 oldcontiguousidx  45957 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52745 copyno  52745 cat      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20358 lpmtidx2  20358 oldcontiguousidx  45958 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52746 copyno  52746 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20359 lpmtidx2  20359 oldcontiguousidx  45959 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52747 copyno  52747 cat      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno  53000 cat      4 copyno_pmtid_consistent NO 
    SPMT_test: ../SPMT.h:953: void SPMT::init_lcqs(): Assertion `copyno_pmtid_consistent' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff788bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-168.el9_6.23.x86_64
    (gdb) bt
    #0  0x00007ffff788bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff783eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7828833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff782875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff7837886 in __assert_fail () from /lib64/libc.so.6
    #5  0x000000000042f937 in SPMT::init_lcqs (this=0x4b0cf0) at ../SPMT.h:953
    #6  0x000000000042e226 in SPMT::init (this=0x4b0cf0) at ../SPMT.h:494
    #7  0x000000000042e0c1 in SPMT::SPMT (this=0x4b0cf0, jpmt_=0x483ba0) at ../SPMT.h:445
    #8  0x000000000042db9b in SPMT::CreateFromJPMT (path_=0x0) at ../SPMT.h:409
    #9  0x0000000000405a17 in main (argc=1, argv=0x7fffffffb508) at SPMT_test.cc:5
    (gdb) 







pmtCat : array order is simply numerically ascending in pmtid key
-------------------------------------------------------------------

::

     85 inline NP* _PMTParamData::serialize_pmtCat() const
     86 {
     87     NP* pmtCat = NPX::ArrayFromDiscoMapUnordered<int>(data.m_pmt_categories);
     88     return pmtCat ;
     89 }
     90 inline void _PMTParamData::import_pmtCat(const NP* pmtCat)
     91 {
     92     NPX::DiscoMapUnorderedFromArray<int>(data.m_pmt_categories, pmtCat );
     93 }


pmtCat
---------

Trace pmtCat::

    A[blyth@localhost issues]$ jgr _PMTParamData
    ./Detector/Geometry/Geometry/_PMTParamData.h:struct _PMTParamData
    ./Detector/Geometry/Geometry/_PMTParamData.h:    _PMTParamData( PMTParamData& data ); 
    ./Detector/Geometry/Geometry/_PMTParamData.h:_PMTParamData::_PMTParamData( PMTParamData& data_ )
    ./Detector/Geometry/Geometry/_PMTParamData.h:inline void _PMTParamData::populate()
    ./Detector/Geometry/Geometry/_PMTParamData.h:inline void _PMTParamData::save(const char* fold) const 
    ./Detector/Geometry/Geometry/_PMTParamData.h:inline void _PMTParamData::load(const char* fold) 
    ./Detector/Geometry/Geometry/_PMTParamData.h:inline NPFold* _PMTParamData::serialize() const 
    ./Detector/Geometry/Geometry/_PMTParamData.h:inline void _PMTParamData::import( const NPFold* f )
    ./Detector/Geometry/tests/PMTParamData_test.cc:#include "_PMTParamData.h"
    ./Detector/Geometry/tests/PMTParamData_test.cc:    _PMTParamData _d0(d0) ; 
    ./Detector/Geometry/tests/PMTParamData_test.cc:    _PMTParamData _d1(d1) ; 
    ./Detector/Geometry/tests/PMTParamData_test.cc:    _PMTParamData _d0(d0) ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "Geometry/_PMTParamData.h"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:    _PMTParamData    _ppd(*ppd) ; 
    A[blyth@localhost junosw]$ 



pmtCat is serialized directly from the PMTParamData::m_pmt_categories
using numerically ascending pmt identifier order::

    In [1]: f.pmtCat
    Out[1]: 
    array([[    0,     1],
           [    1,     3],
           [    2,     1],
           [    3,     3],
           [    4,     1],
           ...,
           [54000,     3],
           [54001,     0],
           [54002,     0],
           [54003,     0],
           [54004,     0]], shape=(46565, 2), dtype=int32)

    In [2]: pwd
    Out[2]: '/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.5/el9_amd64_gcc11/2025_10_24/.opticks/GEOM/J25_4_0_Opticks_v0_5_5/CSGFoundry/SSim/extra/jpmt/PMTParamData'

    In [3]: f.pmtCat[:17612]
    Out[3]: 
    array([[    0,     1],
           [    1,     3],
           [    2,     1],
           [    3,     3],
           [    4,     1],
           ...,
           [17607,     1],
           [17608,     3],
           [17609,     1],
           [17610,     1],
           [17611,     1]], shape=(17612, 2), dtype=int32)


    In [5]: f.pmtCat[17612:17612+25600]
    Out[5]: 
    array([[20000,     2],
           [20001,     2],
           [20002,     2],
           [20003,     2],
           [20004,     2],
           ...,
           [45595,     2],
           [45596,     2],
           [45597,     2],
           [45598,     2],
           [45599,     2]], shape=(25600, 2), dtype=int32)

    In [6]: np.all( f.pmtCat[17612:17612+25600][:,1] == 2 )
    Out[6]: np.True_


    In [8]: f.pmtCat[17612+25600:17612+25600+2400]
    Out[8]: 
    array([[50000,     3],
           [50001,     0],
           [50002,     0],
           [50003,     3],
           [50004,     0],
           ...,
           [52395,     0],
           [52396,     3],
           [52397,     3],
           [52398,     3],
           [52399,     0]], shape=(2400, 2), dtype=int32)

    In [10]: f.pmtCat[17612+25600+2400:17612+25600+2400+348]
    Out[10]: 
    array([[52400,     3],
           [52401,     0],
           [52402,     0],
           [52403,     3],
           ..
           [52744,     0],
           [52745,     3],
           [52746,     0],
           [52747,     0]], dtype=int32)


    In [18]: f.pmtCat[17612+25600+2400+348:17612+25600+2400+348+600]  ## 600 MPMT with cat 4
    Out[18]: 
    array([[53000,     4],
           [53001,     4],
           [53002,     4],
           [53003,     4],
           [53004,     4],
           ...,
           [53595,     4],
           [53596,     4],
           [53597,     4],
           [53598,     4],
           [53599,     4]], shape=(600, 2), dtype=int32)

    In [17]: f.pmtCat[17612+25600+2400+348+600:]
    Out[17]: 
    array([[54000,     3],
           [54001,     0],
           [54002,     0],
           [54003,     0],
           [54004,     0]], dtype=int32)

Ordering is::

    CD_LPMT        17612 
    CD_SPMT        25600 
    WP_LPMT        2400
    WP_ATM_PMT     348
    WP_ATM_MPMT    600
    WP_ATM_WAL     5





::

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




Where did the MPMT come from?
--------------------------------

::

    A[blyth@localhost junosw]$ jgr m_pmt_categories
    ./Detector/Geometry/Geometry/_PMTParamData.h:    for(int i=0 ; i < 17612 ; i++) data.m_pmt_categories[i] = i % 4 ; 
    ./Detector/Geometry/Geometry/_PMTParamData.h:    for(int i=kOFFSET_CD_SPMT ; i < kOFFSET_CD_SPMT_END ; i++) data.m_pmt_categories[i] = 5 ; 
    ./Detector/Geometry/Geometry/_PMTParamData.h:    f->add("pmtCat", NPX::ArrayFromDiscoMapUnordered<int>(data.m_pmt_categories));
    ./Detector/Geometry/Geometry/_PMTParamData.h:    NPX::DiscoMapUnorderedFromArray<int>(data.m_pmt_categories, pmtCat );
    ./Detector/Geometry/Geometry/PMTParamData.h:    std::unordered_map<int, int> m_pmt_categories ;
    ./Detector/Geometry/Geometry/PMTParamData.h:    unsigned ni = d.m_pmt_categories.size() ;  
    ./Detector/Geometry/Geometry/PMTParamData.h:       << " m_pmt_categories.size " << ni
    ./Detector/Geometry/Geometry/PMTParamData.h:    MII::const_iterator it = d.m_pmt_categories.begin() ; 
    ./Detector/Geometry/src/PMTParamSvc.cc:    m_pmt_categories(data.m_pmt_categories),
    ./Detector/Geometry/src/PMTParamSvc.cc:    return m_pmt_categories.at(pmtID);
    ./Detector/Geometry/src/PMTParamSvc.cc:     count_cat(catmap, m_pmt_categories);  
    ./Detector/Geometry/src/PMTParamSvc.cc:  if (m_pmt_categories.count(pmtid)==0)
    ./Detector/Geometry/src/PMTParamSvc.cc:    return is20inch(pmtid) and m_pmt_categories.at(pmtid) == kPMT_NNVT;
    ./Detector/Geometry/src/PMTParamSvc.cc:  if (m_pmt_categories.count(pmtid)==0)
    ./Detector/Geometry/src/PMTParamSvc.cc:    return is20inch(pmtid) and (m_pmt_categories.at(pmtid) == kPMT_NNVT or m_pmt_categories.at(pmtid) == kPMT_NNVT_HighQE);
    ./Detector/Geometry/src/PMTParamSvc.cc:  if (m_pmt_categories.count(pmtid)==0)
    ./Detector/Geometry/src/PMTParamSvc.cc:    return is20inch(pmtid) and m_pmt_categories.at(pmtid) == kPMT_Hamamatsu;
    ./Detector/Geometry/src/PMTParamSvc.cc:  if (m_pmt_categories.count(pmtid)==0)
    ./Detector/Geometry/src/PMTParamSvc.cc:    return !isHamamatsu(pmtid) and m_pmt_categories.at(pmtid) == kPMT_NNVT_HighQE;
    ./Detector/Geometry/src/PMTParamSvc.cc:         /*and m_pmt_categories[pmtid] == kPMT_HZC*/ // for now, all 3inch PMTs are HZC
    ./Detector/Geometry/src/PMTParamSvc.cc:    if (m_pmt_categories.find(pmtid) != m_pmt_categories.end())
    ./Detector/Geometry/src/PMTParamSvc.cc:    // save into m_pmt_categories
    ./Detector/Geometry/src/PMTParamSvc.cc:      m_pmt_categories[pmtid] = kPMT_Hamamatsu;
    ./Detector/Geometry/src/PMTParamSvc.cc:      m_pmt_categories[pmtid] = kPMT_NNVT;
    ./Detector/Geometry/src/PMTParamSvc.cc:      m_pmt_categories[pmtid] = kPMT_NNVT_HighQE;
    ./Detector/Geometry/src/PMTParamSvc.cc:      m_pmt_categories[pmtid] = kPMT_HZC;
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    ./Detector/Geometry/src/PMTParamSvc.cc:     else if (PMTType == kPMT_DYB8inch){m_pmt_categories[copyno] = kPMT_DYB8inch;}
    ./Detector/Geometry/src/PMTParamSvc.cc:          m_pmt_categories[copyno] = kPMT_Unknown;}
    ./Detector/Geometry/src/PMTParamSvc.h:  std::unordered_map<int, int>& m_pmt_categories; // 
    ./Detector/Geometry/src/PMTParamSvc.h:  const std::unordered_map<int, int>& getPMTCategoryMap() const { return m_pmt_categories ; } 
    A[blyth@localhost junosw]$ 


::

     550 int PMTParamSvc::get_NTotal_WP_ATM_LPMT() const
     551 {
     552   return m_nums_wp_atm_lpmt;
     553 }
     554 
     555 int PMTParamSvc::get_NTotal_WP_WAL_PMT() const
     556 {
     557   return m_nums_wp_wal_pmt;
     558 }
     559 
     560 int PMTParamSvc::get_NTotal_WP_ATM_MPMT() const
     561 {
     562   return m_nums_wp_atm_mpmt;
     563 }



SPMT_test shows 5 PMTs with the inconsistency
-----------------------------------------------

Fact that are 5 of them strongly suggests they should be the WAL PMTs with 54000:54005
so the pmtCat_v/copyno is correct and the pmtid

::

    1013     for(int i=0 ; i < s_pmt::NUM_LPMTIDX ; i++ )
    1014     {
    1015         // outcome depends crucially on the implicit order of lpmtidx from s_pmt.h
    1016         int lpmtidx = i ;
    1017         int pmtid = s_pmt::pmtid_from_lpmtidx( lpmtidx );
    1018         int lpmtidx2 = s_pmt::lpmtidx_from_pmtid( pmtid );
    1019         assert( lpmtidx == lpmtidx2 );
    1020 
    1021         // pmtCat from _PMTParamData uses oldcontiguous order : CD_LPMT, SPMT, WP, WP_ATM_LPMT, WP_WAL_PMT
    1022         int oldcontiguousidx = s_pmt::oldcontiguousidx_from_pmtid( pmtid );
    1023         assert( oldcontiguousidx < s_pmt::NUM_OLDCONTIGUOUSIDX );
    1024 
    1025         // seems pmtCat has the 600 MPMT added : which is contrary
    1026         int copyno = pmtCat_v[2*oldcontiguousidx+0] ;
    1027         int cat    = pmtCat_v[2*oldcontiguousidx+1] ;
    1028         bool copyno_pmtid_consistent = copyno == pmtid ;
    1029 








::

    ok) A[blyth@localhost opticks]$ sysrap/tests/SPMT_test.sh
                       BASH_SOURCE : sysrap/tests/SPMT_test.sh 
                      BASH_VERSION : 5.1.8(1)-release 
                            defarg : info_build_run_pdb 
                               arg : info_build_run_pdb 
                              name : SPMT_test 
                              GEOM : J25_4_0_opticks_Debug 
                               TMP : /data1/blyth/tmp 
                              FOLD : /data1/blyth/tmp/SPMT_test 
                       CUDA_PREFIX : /usr/local/cuda 
                               bin : /data1/blyth/tmp/SPMT_test/SPMT_test 
                            script : SPMT_test.py 
                              TEST : testfold 
                       SPMT__level :  
    sysrap/tests/SPMT_test.sh : build OK
    SPMT::init_pmtNum pmtNum.sstr -
    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  53000 copyno[pmtCat_v]  54000 cat[pmtCat_v]      3 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20361 lpmtidx2  20361 oldcontiguousidx  45961 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  53001 copyno[pmtCat_v]  54001 cat[pmtCat_v]      0 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20362 lpmtidx2  20362 oldcontiguousidx  45962 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  53002 copyno[pmtCat_v]  54002 cat[pmtCat_v]      0 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20363 lpmtidx2  20363 oldcontiguousidx  45963 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  53003 copyno[pmtCat_v]  54003 cat[pmtCat_v]      0 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20364 lpmtidx2  20364 oldcontiguousidx  45964 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  53004 copyno[pmtCat_v]  54004 cat[pmtCat_v]      0 copyno_pmtid_consistent NO 
    SPMT_test.main SPMT::desc
    jpmt.loaddir /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt
    rindex (3, 4, 2, 15, 2, )
    thickness (3, 4, 1, )
    qeshape (3, 44, 2, )
    s_qeshape (1, 61, 2, )
    s_qescale (25600, 1, )
    cetheta (3, 10, 2, )
    cecosth (3, 10, 2, )
    lcqs (20365, 2, )

    [ SPMT::make_testfold 
    SPMT::get_lpmtcat_from_lpmtidx 
    SPMT::get_qescale_from_lpmtidx 




Repeated ljbb not picking up change to PMT serialization adding pmtNum : so get bolshy
----------------------------------------------------------------------------------------

In new session::

    A[blyth@localhost junosw]$ find InstallArea -name libDetSimOptions.so
    InstallArea/lib64/libDetSimOptions.so
    A[blyth@localhost junosw]$ rm InstallArea/lib64/libDetSimOptions.so
    A[blyth@localhost junosw]$ ljbb







Suspect some of above testing using update build that did not fully update until zapped the lib
-------------------------------------------------------------------------------------------------

* that would explain the flip-flop experience with the 600 MPMT

ljbb::

    2025-10-28 16:33:21.168 INFO  [3316068] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    SPMT::init_pmtNum pmtNum.sstr (6, )
    [SPMT::init_pmtNum
    [SPMT_Num
      m_nums_cd_lpmt  17612
      m_nums_cd_spmt  25600
      m_nums_wp_lpmt   2400
    m_nums_wp_atm_lpmt    348
    m_nums_wp_wal_pmt      5
    m_nums_wp_atm_mpmt    600
                 ALL  46565
                SUM:  46565
            SUM==ALL    YES
    ]SPMT_Num
    ]SPMT::init_pmtNum
    SPMT::init_pmtCat expected_type YES expected_shape[first-dim-same-as-total.ALL] NO  pmtCat (46565, 2, ) total [SPMT_Total
             CD_LPMT  17612
                SPMT  25600
                  WP   2400
         WP_ATM_LPMT    348
         WP_ATM_MPMT      0
          WP_WAL_PMT      5
                 ALL  45965
                SUM:  45965
            SUM==ALL    YES
    ]SPMT_Total

    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno[pmtCat_v]  53000 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20361 lpmtidx2  20361 oldcontiguousidx  45961 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54001 copyno[pmtCat_v]  53001 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20362 lpmtidx2  20362 oldcontiguousidx  45962 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54002 copyno[pmtCat_v]  53002 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20363 lpmtidx2  20363 oldcontiguousidx  45963 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54003 copyno[pmtCat_v]  53003 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20364 lpmtidx2  20364 oldcontiguousidx  45964 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54004 copyno[pmtCat_v]  53004 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    2025-10-28 16:33:21.505 INFO  [3316068] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest 7f69f317d34b7af58b4a07460ef20d39 dynamic 7f69f317d34b7af58b4a07460ef20d39
    2025-10-28 16:33:21.505 INFO  [3316068] [G4CXOpticks::setGeometry@334] CSGOptiX::Desc Version 7 WITH_CUSTOM4 





