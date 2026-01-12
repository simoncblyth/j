MPMT-related-fail
====================

When returning to this old branch yupd_bottompipe_adjust after changing MPMT handling for 
the newer branch yupd-8inch-pmt::



    ]CSGImport::importPrim.dump_LVID:1 node.lvid 127 LVID -1 name Waterdistributor_2 soname Waterdistributor_2
    2026-01-09 17:57:25.940 INFO  [1825852] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    python: /home/blyth/opticks/sysrap/SPMT.h:664: void SPMT::init_total(): Assertion `total.WP_ATM_MPMT == s_pmt::NUM_WP_ATM_MPMT' failed.
     *** Break *** abort

::

    2026-01-09 18:24:54.806 INFO  [246070] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    SPMT::init_pmtNum pmtNum.sstr (6, ) init_pmtNum_FAKE_WHEN_MISSING 1
    [SPMT::init_pmtNum
    [SPMT_Num.desc
     WITH_MPMT : NO
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
    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno[pmtCat_v]  53000 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    python: /home/blyth/opticks/sysrap/SPMT.h:1254: void SPMT::init_lcqs(): Assertion `copyno_pmtid_consistent' failed.
     *** Break *** abort



Commenting the assert, shows the mismatch is for the final 5. This allows the save to complete, so have more to debug::

    SPMT::init_lcqs i/lpmtidx  20345 lpmtidx2  20345 oldcontiguousidx  45945 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52733 copyno[pmtCat_v]  52733 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20346 lpmtidx2  20346 oldcontiguousidx  45946 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52734 copyno[pmtCat_v]  52734 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20347 lpmtidx2  20347 oldcontiguousidx  45947 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52735 copyno[pmtCat_v]  52735 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20348 lpmtidx2  20348 oldcontiguousidx  45948 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52736 copyno[pmtCat_v]  52736 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20349 lpmtidx2  20349 oldcontiguousidx  45949 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52737 copyno[pmtCat_v]  52737 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20350 lpmtidx2  20350 oldcontiguousidx  45950 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52738 copyno[pmtCat_v]  52738 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20351 lpmtidx2  20351 oldcontiguousidx  45951 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52739 copyno[pmtCat_v]  52739 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20352 lpmtidx2  20352 oldcontiguousidx  45952 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52740 copyno[pmtCat_v]  52740 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20353 lpmtidx2  20353 oldcontiguousidx  45953 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52741 copyno[pmtCat_v]  52741 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20354 lpmtidx2  20354 oldcontiguousidx  45954 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52742 copyno[pmtCat_v]  52742 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20355 lpmtidx2  20355 oldcontiguousidx  45955 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52743 copyno[pmtCat_v]  52743 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20356 lpmtidx2  20356 oldcontiguousidx  45956 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52744 copyno[pmtCat_v]  52744 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20357 lpmtidx2  20357 oldcontiguousidx  45957 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52745 copyno[pmtCat_v]  52745 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20358 lpmtidx2  20358 oldcontiguousidx  45958 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52746 copyno[pmtCat_v]  52746 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20359 lpmtidx2  20359 oldcontiguousidx  45959 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  52747 copyno[pmtCat_v]  52747 cat[pmtCat_v]      0 copyno_pmtid_consistent YES

    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  45960 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno[pmtCat_v]  53000 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20361 lpmtidx2  20361 oldcontiguousidx  45961 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54001 copyno[pmtCat_v]  53001 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20362 lpmtidx2  20362 oldcontiguousidx  45962 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54002 copyno[pmtCat_v]  53002 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20363 lpmtidx2  20363 oldcontiguousidx  45963 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54003 copyno[pmtCat_v]  53003 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 
    SPMT::init_lcqs i/lpmtidx  20364 lpmtidx2  20364 oldcontiguousidx  45964 s_pmt::NUM_OLDCONTIGUOUSIDX  45965 s_pmt::NUM_LPMTIDX  20365 pmtid  54004 copyno[pmtCat_v]  53004 cat[pmtCat_v]      4 copyno_pmtid_consistent NO 

                                                     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                                               WOOPS oldcontiguousidx EXCEEDING s_pmt::NUM_OLDCONTIGUOUSIDX     

    2026-01-09 19:40:34.204 INFO  [2191751] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest fa1cce096d0d46dd47f9dd98b583f6be dynamic fa1cce096d0d46dd47f9dd98b583f6be
    2026-01-09 19:40:34.205 INFO  [2191751] [G4CXOpticks::setGeometry@323] G4CXOpticks::desc sim Y tr Y wd Y fd Y cx Y cx.desc CSGOptiX::Desc Version 7 WITH_CUSTOM4 PIP  td:1 pv:2 av:2 WITH_PRD  
    2026-01-09 19:40:34.205 INFO  [2191751] [G4CXOpticks::SaveGeometry@616]  save to dir /home/blyth/junosw/InstallArea/yupd_bottompipe_adjust/.opticks/GEOM/J25_7_2_opticks_Debug configured via envvar G4CXOpticks__SaveGeometry_DIR
    2026-01-09 19:40:34.205 INFO  [2191751] [G4CXOpticks::saveGeometry@574] [ /home/blyth/junosw/InstallArea/yupd_bottompipe_adjust/.opticks/GEOM/J25_7_2_opticks_Debug


::

    In [5]: f.pmtCat.shape
    Out[5]: (46565, 2)

    In [6]: 46565-600
    Out[6]: 45965



After handling the flip-flop-MPMT better in s_pmt.h the copyno stay consistent without WITH_MPMT::

    SPMT::init_lcqs i/lpmtidx  20346 lpmtidx2  20346 oldcontiguousidx  45946 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52734 copyno[pmtCat_v]  52734 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20347 lpmtidx2  20347 oldcontiguousidx  45947 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52735 copyno[pmtCat_v]  52735 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20348 lpmtidx2  20348 oldcontiguousidx  45948 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52736 copyno[pmtCat_v]  52736 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20349 lpmtidx2  20349 oldcontiguousidx  45949 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52737 copyno[pmtCat_v]  52737 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20350 lpmtidx2  20350 oldcontiguousidx  45950 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52738 copyno[pmtCat_v]  52738 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20351 lpmtidx2  20351 oldcontiguousidx  45951 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52739 copyno[pmtCat_v]  52739 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20352 lpmtidx2  20352 oldcontiguousidx  45952 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52740 copyno[pmtCat_v]  52740 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20353 lpmtidx2  20353 oldcontiguousidx  45953 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52741 copyno[pmtCat_v]  52741 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20354 lpmtidx2  20354 oldcontiguousidx  45954 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52742 copyno[pmtCat_v]  52742 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20355 lpmtidx2  20355 oldcontiguousidx  45955 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52743 copyno[pmtCat_v]  52743 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20356 lpmtidx2  20356 oldcontiguousidx  45956 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52744 copyno[pmtCat_v]  52744 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20357 lpmtidx2  20357 oldcontiguousidx  45957 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52745 copyno[pmtCat_v]  52745 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20358 lpmtidx2  20358 oldcontiguousidx  45958 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52746 copyno[pmtCat_v]  52746 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20359 lpmtidx2  20359 oldcontiguousidx  45959 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  52747 copyno[pmtCat_v]  52747 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20360 lpmtidx2  20360 oldcontiguousidx  46560 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  54000 copyno[pmtCat_v]  54000 cat[pmtCat_v]      3 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20361 lpmtidx2  20361 oldcontiguousidx  46561 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  54001 copyno[pmtCat_v]  54001 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20362 lpmtidx2  20362 oldcontiguousidx  46562 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  54002 copyno[pmtCat_v]  54002 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20363 lpmtidx2  20363 oldcontiguousidx  46563 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  54003 copyno[pmtCat_v]  54003 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    SPMT::init_lcqs i/lpmtidx  20364 lpmtidx2  20364 oldcontiguousidx  46564 s_pmt::NUM_OLDCONTIGUOUSIDX  46565 s_pmt::NUM_LPMTIDX  20365 pmtid  54004 copyno[pmtCat_v]  54004 cat[pmtCat_v]      0 copyno_pmtid_consistent YES
    2026-01-09 20:58:53.032 INFO  [1653667] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest fa1cce096d0d46dd47f9dd98b583f6be dynamic fa1cce096d0d46dd47f9dd98b583f6be
    2026-01-09 20:58:53.032 INFO  [1653667] [G4CXOpticks::setGeometry@323] G4CXOpticks::desc sim Y tr Y wd Y fd Y cx Y cx.desc CSGOptiX::Desc Version 7 WITH_CUSTOM4 PIP  td:1 pv:2 av:2 WITH_PRD  



::

    2026-01-09 21:11:57.281 INFO  [3656604] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000000 SEventConfig::MaxCurand 1000000000000
    SPMT::init_pmtNum pmtNum.sstr (6, ) init_pmtNum_FAKE_WHEN_MISSING 1
    [SPMT::init_pmtNum
    [SPMT_Num.desc
     WITH_MPMT : NO
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



