02mar2022_name_change
=========================

Name change again::

    tds3dbg
    ...
    2022-03-03 18:40:02.623 INFO  [309126] [G4Opticks::translateGeometry@965] ( GGeo::postDirectTranslation 
    2022-03-03 18:40:02.623 INFO  [309126] [GGeo::prepare@668] [
    2022-03-03 18:40:02.623 FATAL [309126] [OpticksDbg::postgeometrySkipSolidName@289]  failed to find solid with name starting [NNVTMCPPMT_PMT_20inch_body_solid_1_2]
    2022-03-03 18:40:02.624 ERROR [309126] [OpticksDbg::postgeometrySkipSolidName@303]  --skipsolidname NNVTMCPPMT_PMT_20inch_body_solid_1_2,HamamatsuR12860_PMT_20inch_body_solid_1_4,PMT_20inch_veto_body_solid_1_2 solidname.size 3 soidx.size 2 (soidx list used by Opticks::isSkipSolidIdx / GInstancer::labelRepeats_r )  notfound 1
    2022-03-03 18:40:02.625 INFO  [309126] [GGeo::prepareVolumes@1374] [ creating merged meshes from the volume tree 
    2022-03-03 18:40:17.016 INFO  [309126] [GInstancer::dumpDigests@530] before sort
     i          0 pdig         159961bde1896fe286c02b4c3f05c8c9 ndig      25600 first 0x82b5be40 first.nidx     194249


::


    2022-03-03 18:39:44.961 INFO  [309126] [X4PhysicalVolume::dumpLV@1215]  m_lvidx.size() 139 m_lvlist.size() 139 edgeitems 100
     i     0 idx     0 lvname                                           lDomeAir soname                                   sTopRock_domeAir
     i     1 idx     1 lvname                                          lDomeRock soname                                      sTopRock_dome
     i     2 idx     2 lvname                                       lDomeRockBox soname                                       sDomeRockBox
     i     3 idx     3 lvname                                         lPoolCover soname                                       PoolCoversub
     i     4 idx     4 lvname                                    lUpperChimneyLS soname                                      Upper_LS_tube
     i     5 idx     5 lvname                                 lUpperChimneySteel soname                                   Upper_Steel_tube
     i     6 idx     6 lvname                                 lUpperChimneyTyvek soname                                   Upper_Tyvek_tube
     i     7 idx     7 lvname                                      lUpperChimney soname                                      Upper_Chimney
     i     8 idx     8 lvname                                               lBar soname                                               sBar
     i     9 idx     9 lvname                                           lCoating soname                                               sBar
     i    10 idx    10 lvname                                         lPanelTape soname                                         sPanelTape
     i    11 idx    11 lvname                                             lPanel soname                                             sPanel
     i    12 idx    12 lvname                                           lPlanef_ soname                                             sPlane
     i    13 idx    13 lvname                                           lWallff_ soname                                              sWall
     i    14 idx    14 lvname                                             lAirTT soname                                             sAirTT
     i    15 idx    15 lvname                                           lExpHall soname                                           sExpHall
     i    16 idx    16 lvname                                        lExpRockBox soname                                        sExpRockBox
     i    17 idx    17 lvname                                           lTopRock soname                                           sTopRock
     i    18 idx    18 lvname                               GLw1.up10_up11_HBeam soname                GLw1.up10_up11_FlangeI_Web_FlangeII
     i    19 idx    19 lvname                               GLw1.up09_up10_HBeam soname                GLw1.up09_up10_FlangeI_Web_FlangeII
     ...
     i    88 idx    88 lvname                                  ZC2.A03_A03_HBeam soname                   ZC2.A03_A03_FlangeI_Web_FlangeII
     i    89 idx    89 lvname                                  ZC2.A05_A05_HBeam soname                   ZC2.A05_A05_FlangeI_Web_FlangeII
     i    90 idx    90 lvname                                       lSJCLSanchor soname                                   solidSJCLSanchor
     i    91 idx    91 lvname                                         lSJFixture soname                                     solidSJFixture
     i    92 idx    92 lvname                                        lSJReceiver soname                                    solidSJReceiver
     i    93 idx    93 lvname                                 lSJReceiverFastern soname                             solidSJReceiverFastern
     i    94 idx    94 lvname                                            lTarget soname                                            sTarget
     i    95 idx    95 lvname                                           lAcrylic soname                                           sAcrylic
     i    96 idx    96 lvname                                             lSteel soname                                             sStrut
     i    97 idx    97 lvname                                            lSteel2 soname                                             sStrut
     i    98 idx    98 lvname                                             lSteel soname                                     sStrutBallhead
     i    99 idx    99 lvname                                         lFasteners soname                                               uni1
     i   100 idx   100 lvname                                             lUpper soname                                         base_steel
     i   101 idx   101 lvname                                          lAddition soname                                       uni_acrylic1
     i   102 idx   102 lvname                                          lXJanchor soname                                      solidXJanchor
     i   103 idx   103 lvname                                         lXJfixture soname                                     solidXJfixture

     i   104 idx   104 lvname                                    NNVTMCPPMTlMask soname                                    NNVTMCPPMTsMask
     i   105 idx   105 lvname                                NNVTMCPPMTlMaskTail soname                                     NNVTMCPPMTTail
     i   106 idx   106 lvname                   NNVTMCPPMT_PMT_20inch_inner1_log soname            NNVTMCPPMT_PMT_20inch_inner1_solid_head
     i   107 idx   107 lvname                   NNVTMCPPMT_PMT_20inch_inner2_log soname            NNVTMCPPMT_PMT_20inch_inner2_solid_head
     i   108 idx   108 lvname                     NNVTMCPPMT_PMT_20inch_body_log soname              NNVTMCPPMT_PMT_20inch_body_solid_head
     i   109 idx   109 lvname                          NNVTMCPPMT_PMT_20inch_log soname               NNVTMCPPMT_PMT_20inch_pmt_solid_head
     i   110 idx   110 lvname                             NNVTMCPPMTlMaskVirtual soname                            NNVTMCPPMTsMask_virtual

     i   111 idx   111 lvname                               HamamatsuR12860lMask soname                               HamamatsuR12860sMask
     i   112 idx   112 lvname                           HamamatsuR12860lMaskTail soname                                HamamatsuR12860Tail
     i   113 idx   113 lvname              HamamatsuR12860_PMT_20inch_inner1_log soname          HamamatsuR12860_PMT_20inch_inner1_solid_I
     i   114 idx   114 lvname              HamamatsuR12860_PMT_20inch_inner2_log soname        HamamatsuR12860_PMT_20inch_inner2_solid_1_4
     i   115 idx   115 lvname                HamamatsuR12860_PMT_20inch_body_log soname          HamamatsuR12860_PMT_20inch_body_solid_1_4
     i   116 idx   116 lvname                     HamamatsuR12860_PMT_20inch_log soname           HamamatsuR12860_PMT_20inch_pmt_solid_1_4
     i   117 idx   117 lvname                        HamamatsuR12860lMaskVirtual soname                       HamamatsuR12860sMask_virtual

     i   118 idx   118 lvname                               PMT_3inch_inner1_log soname                  PMT_3inch_inner1_solid_ell_helper
     i   119 idx   119 lvname                               PMT_3inch_inner2_log soname                  PMT_3inch_inner2_solid_ell_helper
     i   120 idx   120 lvname                                 PMT_3inch_body_log soname                PMT_3inch_body_solid_ell_ell_helper
     i   121 idx   121 lvname                                 PMT_3inch_cntr_log soname                               PMT_3inch_cntr_solid
     i   122 idx   122 lvname                                      PMT_3inch_log soname                                PMT_3inch_pmt_solid
     i   123 idx   123 lvname                               lLowerChimneyAcrylic soname                                    sChimneyAcrylic
     i   124 idx   124 lvname                                    lLowerChimneyLS soname                                         sChimneyLS
     i   125 idx   125 lvname                                 lLowerChimneySteel soname                                      sChimneySteel
     i   126 idx   126 lvname                                      lLowerChimney soname                                         sWaterTube
     i   127 idx   127 lvname                                        lInnerWater soname                                        sInnerWater
     i   128 idx   128 lvname                                     lReflectorInCD soname                                     sReflectorInCD
     i   129 idx   129 lvname                          mask_PMT_20inch_vetolMask soname                          mask_PMT_20inch_vetosMask
     i   130 idx   130 lvname                         PMT_20inch_veto_inner1_log soname                       PMT_20inch_veto_inner1_solid
     i   131 idx   131 lvname                         PMT_20inch_veto_inner2_log soname                       PMT_20inch_veto_inner2_solid
     i   132 idx   132 lvname                           PMT_20inch_veto_body_log soname                     PMT_20inch_veto_body_solid_1_2
     i   133 idx   133 lvname                                PMT_20inch_veto_log soname                      PMT_20inch_veto_pmt_solid_1_2
     i   134 idx   134 lvname                   mask_PMT_20inch_vetolMaskVirtual soname                  mask_PMT_20inch_vetosMask_virtual
     i   135 idx   135 lvname                                    lOuterWaterPool soname                                    sOuterWaterPool
     i   136 idx   136 lvname                                        lPoolLining soname                                        sPoolLining
     i   137 idx   137 lvname                                           lBtmRock soname                                        sBottomRock
     i   138 idx   138 lvname                                             lWorld soname                                             sWorld
    2022-03-03 18:39:44.962 INFO  [309126] [X4PhysicalVolume::convertSolids@887] ]




