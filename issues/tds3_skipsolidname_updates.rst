tds3_skipsolidname_updates
============================



::

    2021-12-18 01:58:21.237 INFO  [55054] [G4Opticks::translateGeometry@963] ) GGeo populate
    2021-12-18 01:58:21.237 INFO  [55054] [G4Opticks::translateGeometry@965] ( GGeo::postDirectTranslation 
    2021-12-18 01:58:21.237 INFO  [55054] [GGeo::prepare@667] [
    2021-12-18 01:58:21.238 FATAL [55054] [OpticksDbg::postgeometrySkipSolidName@289]  failed to find solid with name starting [NNVTMCPPMT_body_solid]
    2021-12-18 01:58:21.238 FATAL [55054] [OpticksDbg::postgeometrySkipSolidName@289]  failed to find solid with name starting [HamamatsuR12860_body_solid_1_9]
    2021-12-18 01:58:21.239 INFO  [55054] [GGeo::prepareVolumes@1293] [ creating merged meshes from the volume tree 
    2021-12-18 01:58:35.260 INFO  [55054] [GInstancer::dumpDigests@530] before sort
     i          0 pdig         a656fc24f42883c6761ea775df0cf460 ndig      25600 first 0x8a13d230 first.nidx     194244




    2021-12-18 03:05:17.767 INFO  [67655] [G4Opticks::translateGeometry@963] ) GGeo populate
    2021-12-18 03:05:17.767 INFO  [67655] [G4Opticks::translateGeometry@965] ( GGeo::postDirectTranslation 
    2021-12-18 03:05:17.767 INFO  [67655] [GGeo::prepare@667] [
    2021-12-18 03:05:17.768 FATAL [67655] [OpticksDbg::postgeometrySkipSolidName@289]  failed to find solid with name starting [NNVTMCPPMT_body_solid]
    2021-12-18 03:05:17.768 FATAL [67655] [OpticksDbg::postgeometrySkipSolidName@289]  failed to find solid with name starting [HamamatsuR12860_body_solid_1_9]
    2021-12-18 03:05:17.768 ERROR [67655] [OpticksDbg::postgeometrySkipSolidName@303]  --skipsolidname mask_PMT_20inch_vetosMask_virtual,NNVTMCPPMT_body_solid,HamamatsuR12860_body_solid_1_9,PMT_20inch_veto_body_solid_1_2 solidname.size 4 soidx.size 2 (soidx list used by Opticks::isSkipSolidIdx / GInstancer::labelRepeats_r )  notfound 2
    2021-12-18 03:05:17.769 INFO  [67655] [GGeo::prepareVolumes@1293] [ creating merged meshes from the volume tree 
    2021-12-18 03:05:31.946 INFO  [67655] [GInstancer::dumpDigests@530] before sort
     i          0 pdig         a656fc24f42883c6761ea775df0cf460 ndig      25600 first 0x8a111550 first.nidx     194244
     i          1 pdig         59fae0d3a67f8c3b0001b9925953b549 ndig      12612 first 0x371e0c10 first.nidx      70960



As was::

    tds-skipsolidname(){ echo $(tds-skipsolidname-) | tr " " "," ; }

    tds-skipsolidname-(){ cat << EON | grep -v ^#
    #NNVTMCPPMTsMask_virtual
    #HamamatsuR12860sMask_virtual
    mask_PMT_20inch_vetosMask_virtual
    NNVTMCPPMT_body_solid
    HamamatsuR12860_body_solid_1_9
    PMT_20inch_veto_body_solid_1_2
    EON
    }


Update::

    tds-skipsolidname-(){ cat << EON | grep -v ^#

    NNVTMCPPMTsMask_virtual
    HamamatsuR12860sMask_virtual
    mask_PMT_20inch_vetosMask_virtual

    NNVTMCPPMT_PMT_20inch_body_solid_1_2
    HamamatsuR12860_PMT_20inch_body_solid_1_4
    PMT_20inch_veto_body_solid_1_2

    EON
    }



::

     i  93 aidx  93 midx  93 name                                     sStrutBallhead mesh  nv    267 nf    528
     i  94 aidx  94 midx  94 name                                               uni1 mesh  nv    496 nf    960
     i  95 aidx  95 midx  95 name                                         base_steel mesh  nv    192 nf    384
     i  96 aidx  96 midx  96 name                                       uni_acrylic1 mesh  nv    122 nf    240
     i  97 aidx  97 midx  97 name                                      solidXJanchor mesh  nv    124 nf    240
     i  98 aidx  98 midx  98 name                                    NNVTMCPPMTsMask mesh  nv    698 nf   1392
     i  99 aidx  99 midx  99 name                                     NNVTMCPPMTTail mesh  nv    602 nf   1200
     i 100 aidx 100 midx 100 name            NNVTMCPPMT_PMT_20inch_inner1_solid_head mesh  nv    171 nf    336
     i 101 aidx 101 midx 101 name             NNVTMCPPMT_PMT_20inch_inner2_solid_1_2 mesh  nv    290 nf    576
     i 102 aidx 102 midx 102 name               NNVTMCPPMT_PMT_20inch_body_solid_1_2 mesh  nv    410 nf    816     ####
     i 103 aidx 103 midx 103 name                NNVTMCPPMT_PMT_20inch_pmt_solid_1_2 mesh  nv    410 nf    816     
     i 104 aidx 104 midx 104 name                            NNVTMCPPMTsMask_virtual mesh  nv     50 nf     96     #### hatbox
     i 105 aidx 105 midx 105 name                               HamamatsuR12860sMask mesh  nv    698 nf   1392
     i 106 aidx 106 midx 106 name                                HamamatsuR12860Tail mesh  nv    506 nf   1008
     i 107 aidx 107 midx 107 name          HamamatsuR12860_PMT_20inch_inner1_solid_I mesh  nv    171 nf    336
     i 108 aidx 108 midx 108 name        HamamatsuR12860_PMT_20inch_inner2_solid_1_4 mesh  nv    301 nf    598
     i 109 aidx 109 midx 109 name          HamamatsuR12860_PMT_20inch_body_solid_1_4 mesh  nv    447 nf    886     ####
     i 110 aidx 110 midx 110 name           HamamatsuR12860_PMT_20inch_pmt_solid_1_4 mesh  nv    447 nf    886
     i 111 aidx 111 midx 111 name                       HamamatsuR12860sMask_virtual mesh  nv     50 nf     96     #### hatbox
     i 112 aidx 112 midx 112 name                  PMT_3inch_inner1_solid_ell_helper mesh  nv    123 nf    240
     i 113 aidx 113 midx 113 name                  PMT_3inch_inner2_solid_ell_helper mesh  nv    147 nf    288
     i 114 aidx 114 midx 114 name                PMT_3inch_body_solid_ell_ell_helper mesh  nv    219 nf    432
     i 115 aidx 115 midx 115 name                               PMT_3inch_cntr_solid mesh  nv     50 nf     96
     i 116 aidx 116 midx 116 name                                PMT_3inch_pmt_solid mesh  nv    266 nf    528
     i 117 aidx 117 midx 117 name                                    sChimneyAcrylic mesh  nv     96 nf    192
     i 118 aidx 118 midx 118 name                                         sChimneyLS mesh  nv     50 nf     96
     i 119 aidx 119 midx 119 name                                      sChimneySteel mesh  nv     96 nf    192
     i 120 aidx 120 midx 120 name                                         sWaterTube mesh  nv     50 nf     96
     i 121 aidx 121 midx 121 name                                        sInnerWater mesh  nv    362 nf    720
     i 122 aidx 122 midx 122 name                                     sReflectorInCD mesh  nv    362 nf    720
     i 123 aidx 123 midx 123 name                          mask_PMT_20inch_vetosMask mesh  nv    566 nf   1124
     i 124 aidx 124 midx 124 name                       PMT_20inch_veto_inner1_solid mesh  nv    266 nf    528
     i 125 aidx 125 midx 125 name                       PMT_20inch_veto_inner2_solid mesh  nv    146 nf    288
     i 126 aidx 126 midx 126 name                     PMT_20inch_veto_body_solid_1_2 mesh  nv    314 nf    624
     i 127 aidx 127 midx 127 name                      PMT_20inch_veto_pmt_solid_1_2 mesh  nv    314 nf    624
     i 128 aidx 128 midx 128 name                  mask_PMT_20inch_vetosMask_virtual mesh  nv     50 nf     96
     i 129 aidx 129 midx 129 name                                    sOuterWaterPool mesh  nv     50 nf     96
     i 130 aidx 130 midx 130 name                                        sPoolLining mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name                                        sBottomRock mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name                                             sWorld mesh  nv      8 nf     12





::

    258 void OpticksDbg::postgeometrySkipSolidName()
    259 {   
    260     LOG(LEVEL) << "[" ;
    261     assert(m_cfg); 
    262     m_geo = m_ok->getGeo();
    263     assert(m_geo);
    264     
    265     const std::string& skipsolidname = m_cfg->getSkipSolidName() ;
    266     
    267     std::vector<std::string> solidname ; 
    268     SStr::Split(skipsolidname.c_str(), ',', solidname );
    269     
    270     LOG(LEVEL) 
    271         << " skipsolidname " << skipsolidname 
    272         << " solidname.size " << solidname.size()
    273         ;
    274     
    275     std::vector<unsigned>& soidx = m_skipsolididx ;
    276     
    277     unsigned notfound = 0 ;
    278     
    279     for(int i=0 ; i < int(solidname.size()) ; i++)
    280     {   
    281         const std::string& sn = solidname[i];
    282         bool startswith = true ; 
    283         int midx = m_geo->getMeshIndexWithName(sn.c_str(), startswith) ;
    284         bool found = midx > 0 ;    // looks like cannot find first 
    285         
    286         if(!found)
    287         {   
    288             notfound += 1 ;
    289             LOG(fatal) 
    290                 << " failed to find solid with name starting [" << sn << "]" ;
    291                 ;
    292         }
    293         else
    294         {   
    295             LOG(LEVEL) 
    296                 << " found sn [" << sn << "]" 
    297                 << " midx "  << std::setw(4) << midx
    298                 ;
    299             soidx.push_back(midx);
    300         }
    301     }
    302     
    303     LOG(notfound == 0 ? LEVEL : error) 
    304         << " --skipsolidname " << skipsolidname 
    305         << " solidname.size " << solidname.size()
    306         << " soidx.size " << soidx.size()
    307         << " (soidx list used by Opticks::isSkipSolidIdx / GInstancer::labelRepeats_r ) "
    308         << " notfound " << notfound
    309         ;
    310 
    311 
    312     LOG(LEVEL) << "]" ;

