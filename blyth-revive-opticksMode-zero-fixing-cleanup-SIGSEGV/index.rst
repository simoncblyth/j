blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/index
============================================================

Overview : MERGED 2026 Jun 22
---------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1233

Changes
---------

::

    A[blyth@localhost junosw]$ git branch
    * blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
      main
    A[blyth@localhost junosw]$ git lg -n10
    * 2026-06-18 aa9e875f - (HEAD -> blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV, origin/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV) try to avoid gitlab-ci git complaining about dubious ownership and not giving the branch with a before_script (5 days ago) <Simon C Blyth>
    * 2026-06-18 37e1dca3 - dummy commit to trigger a new gitlab-ci pipeline build using Opticks vLatest v0.6.6 together with the simoncblyth/junosw:el9.4-cuda13.1-opticks docker image (5 days ago) <Simon C Blyth>
    * 2026-06-15 7f127c0e - update docker image for JUNOSW+Opticks build to simoncblyth/junosw:el9.4-cuda13.1-opticks which is now based off the junosw/base:el9-9.4 image just adding cuda 13.1 (8 days ago) <Simon C Blyth>
    * 2026-05-07 5767e9d3 - propagate JUNO_OPTICKS_CONFIG from build env into runtime env, use JUNO_OPTICKS_CONFIG together with the junosw branch to control the OPTICKS_PREFIX to build OJ against, reduce runtime verbosity (7 weeks ago) <Simon C Blyth>
    * 2026-04-13 354f77a3 - skip geometry conversion in opticksMode:0 as opticks geometry not needed in that case (2 months ago) <Simon C Blyth>
    * 2026-04-13 cabf1712 - remove hit expected_shape assert, as need to complete SEvt array saving in order to debug lack of hits (2 months ago) <Simon C Blyth>
    * 2026-04-13 ce275685 - change to --anamgr-opticks following naming convention of other anamgr, add TUT_DETSIM_HARD_EXIT for opticks running only which often avoids a termination cleanup error (2 months ago) <Simon C Blyth>
    *   2026-04-01 57db7c38 - (origin/main, origin/HEAD) Merge branch 'xhyang_New_Optical_Model' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\  
    | * 2026-04-01 52b25748 - Xhyang new optical model (3 months ago) <xhyang@ihep.ac.cn>
    |/  
    *   2026-04-01 bf797e1e - Merge branch 'xhyang_New_Optical_Model' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\  
    A[blyth@localhost junosw]$ 





::

    A[blyth@localhost junosw]$ git l -n10
    commit aa9e875ff51bcbfc62079babb558e584b4d982a6 (HEAD -> blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV, origin/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Jun 18 17:04:59 2026 +0800

        try to avoid gitlab-ci git complaining about dubious ownership and not giving the branch with a before_script

    M       .gitlab-ci.yml

    commit 37e1dca39abd39b30ae34c6481fc56751203b82f
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Jun 18 15:00:36 2026 +0800

        dummy commit to trigger a new gitlab-ci pipeline build using Opticks vLatest v0.6.6 together with the simoncblyth/junosw:el9.4-cuda13.1-opticks docker image

    M       .gitlab-ci.yml

    commit 7f127c0e4ba8f2303de438ac6627a93f32eaf268
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Mon Jun 15 16:55:22 2026 +0800

        update docker image for JUNOSW+Opticks build to simoncblyth/junosw:el9.4-cuda13.1-opticks which is now based off the junosw/base:el9-9.4 image just adding cuda 13.1

    M       .gitlab-ci.yml

    commit 5767e9d3c181dd5fa875835314441f786bee60f2
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu May 7 14:26:37 2026 +0800

        propagate JUNO_OPTICKS_CONFIG from build env into runtime env, use JUNO_OPTICKS_CONFIG together with the junosw branch to control the OPTICKS_PREFIX to build OJ against, reduce runtime verbosity

    M       .gitlab-ci/oj_helper.sh
    M       Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    M       cmake/legacy/JUNODependencies.cmake
    M       oj_initialize.sh


    commit 354f77a30d317411811635471013aa2c4f9eb500
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Mon Apr 13 10:13:47 2026 +0800

        skip geometry conversion in opticksMode:0 as opticks geometry not needed in that case

    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc

    commit cabf1712238c8eb7166e62e8121c3160bc33ca12
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Mon Apr 13 10:12:47 2026 +0800

        remove hit expected_shape assert, as need to complete SEvt array saving in order to debug lack of hits

    M       Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc

    commit ce275685a0b4def98084fc0cfa4047bdc2eb2dbe
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Mon Apr 13 10:09:31 2026 +0800

        change to --anamgr-opticks following naming convention of other anamgr, add TUT_DETSIM_HARD_EXIT for opticks running only which often avoids a termination cleanup error

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Examples/Tutorial/share/tut_detsim.py




    commit 57db7c38cf71966260908fb0510141c8bc7032dc (origin/main, origin/HEAD)
    Merge: bf797e1e 52b25748
    Author: Tao Lin <lintao@ihep.ac.cn>
    Date:   Wed Apr 1 15:03:37 2026 +0000

        Merge branch 'xhyang_New_Optical_Model' into 'main'
        
        Xhyang new optical model
        



After merge : switch to main, delete the branch, update main, ljbbc
----------------------------------------------------------------------

::

    A[blyth@localhost junosw]$ git branch
    * blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
      main
    A[blyth@localhost junosw]$ 
    A[blyth@localhost junosw]$ 
    A[blyth@localhost junosw]$ git switch main
    Switched to branch 'main'
    Your branch is behind 'origin/main' by 20 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)
    A[blyth@localhost junosw]$ git branch -d blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    warning: deleting branch 'blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV' that has been merged to
             'refs/remotes/origin/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV', but not yet merged to HEAD
    Deleted branch blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV (was aa9e875f).
    A[blyth@localhost junosw]$ 
    A[blyth@localhost junosw]$ git branch
    * main
    A[blyth@localhost junosw]$ git pull
    remote: Enumerating objects: 3466, done.
    remote: Counting objects: 100% (3466/3466), done.
    remote: Compressing objects: 100% (1629/1629), done.
    remote: Total 3466 (delta 2100), reused 2699 (delta 1723), pack-reused 0 (from 0)
    Receiving objects: 100% (3466/3466), 2.18 MiB | 11.29 MiB/s, done.
    Resolving deltas: 100% (2100/2100), completed with 159 local objects.
    From code.ihep.ac.cn:JUNO/offline/junosw
       57db7c38..05d4af88  main                                                     -> origin/main
       c977fad9..fbb5309c  Shiqiang_COTILinearFitFix                                -> origin/Shiqiang_COTILinearFitFix
       0ea8c2b6..2c482403  Shiqiang_addStepLimit                                    -> origin/Shiqiang_addStepLimit
     * [new branch]        Shiqiang_addStepLimit_J26.1.2                            -> origin/Shiqiang_addStepLimit_J26.1.2
     * [new branch]        Shiqiang_addStepLimit_J26.1.2_G4.11                      -> origin/Shiqiang_addStepLimit_J26.1.2_G4.11
     * [new branch]        WFSP                                                     -> origin/WFSP
       ed1c2593..c477877b  akira-commissioning-4                                    -> origin/akira-commissioning-4
     * [new branch]        codex/empirical-tof-dynode-time-likelihood               -> origin/codex/empirical-tof-dynode-time-likelihood
     * [new branch]        codex/omilrecv2-npe-nonfinite-guard-j2630                -> origin/codex/omilrecv2-npe-nonfinite-guard-j2630
     * [new branch]        codex/omilrecv2-qres-dynode-time-likelihood              -> origin/codex/omilrecv2-qres-dynode-time-likelihood
     * [new branch]        codex/omilrecv2-tq-chimney-veto                          -> origin/codex/omilrecv2-tq-chimney-veto
       484de609..b0346b7d  deepsphere-onnx                                          -> origin/deepsphere-onnx
     * [new branch]        dingxf-omilrecv2                                         -> origin/dingxf-omilrecv2
     * [new branch]        fangwx-2beta                                             -> origin/fangwx-2beta
     + d821b496...e0ebfd9f fangwx-oec-ncluster                                      -> origin/fangwx-oec-ncluster  (forced update)
     * [new branch]        fangwx-oec-saveWpWaveform                                -> origin/fangwx-oec-saveWpWaveform
     * [new branch]        fangwx-omilrec-speed                                     -> origin/fangwx-omilrec-speed
     * [new branch]        fangwx-omilrec-update-mr                                 -> origin/fangwx-omilrec-update-mr
     * [new branch]        fangwx-periodic-prescale                                 -> origin/fangwx-periodic-prescale
     * [new branch]        fangwx-pmtcalibsvc-deconv                                -> origin/fangwx-pmtcalibsvc-deconv
     * [new branch]        feature/varying-rfrindex-zsplit                          -> origin/feature/varying-rfrindex-zsplit
     * [new branch]        fix_positioner_deex                                      -> origin/fix_positioner_deex
     * [new branch]        huanggh_omilrec_WeakSupvMLWaveRec                        -> origin/huanggh_omilrec_WeakSupvMLWaveRec
     * [new branch]        huanggh_omilrec_set_Theta_Free_in_QTMLE                  -> origin/huanggh_omilrec_set_Theta_Free_in_QTMLE
     * [new branch]        jiangyx_WP_SN_debug                                      -> origin/jiangyx_WP_SN_debug
     * [new branch]        jiangyx_oec_readfromomilrec                              -> origin/jiangyx_oec_readfromomilrec
     * [new branch]        jiangyx_update-oec-sn-selection                          -> origin/jiangyx_update-oec-sn-selection
     * [new branch]        jpamdeandre_TTTracking_V2                                -> origin/jpamdeandre_TTTracking_V2
       a9217c1d..2f96f102  jsz-globalbuffer-decouple                                -> origin/jsz-globalbuffer-decouple
     * [new branch]        jsz-globalbuffer-decouple-align-aptag-remove-flashertool -> origin/jsz-globalbuffer-decouple-align-aptag-remove-flashertool
       c3d7331b..a5f068c9  jsz_IAD                                                  -> origin/jsz_IAD
     * [new branch]        jvertex-valprod                                          -> origin/jvertex-valprod
     * [new branch]        llabit_DB_implement_in_spmtCalib                         -> origin/llabit_DB_implement_in_spmtCalib
     * [new branch]        luoxj/psdtools-input-alignment-clean                     -> origin/luoxj/psdtools-input-alignment-clean
     * [new branch]        new-jvertex-valprod                                      -> origin/new-jvertex-valprod
     * [new branch]        release/J26.3.2                                          -> origin/release/J26.3.2
     * [new branch]        shubing_EnergyCorrection                                 -> origin/shubing_EnergyCorrection
       6b4c0b91..b3c4bab8  thsrmd__Redesign-RecTools-RecMuonAlg                     -> origin/thsrmd__Redesign-RecTools-RecMuonAlg
     * [new branch]        tmp_Amber_doubleTrack                                    -> origin/tmp_Amber_doubleTrack
     * [new branch]        update_deex_tool                                         -> origin/update_deex_tool
     * [new branch]        weijy_dev                                                -> origin/weijy_dev
     * [new branch]        wenjiewu/charge_gate_time_likelihood                     -> origin/wenjiewu/charge_gate_time_likelihood
     * [new branch]        wenjiewu/omilrec_mc                                      -> origin/wenjiewu/omilrec_mc
     * [new branch]        wing_dev                                                 -> origin/wing_dev
     * [new branch]        xhyang_LS_New_Optical_Model_Proton-(III)                 -> origin/xhyang_LS_New_Optical_Model_Proton-(III)
     * [new branch]        xhyang_Test                                              -> origin/xhyang_Test
     * [new branch]        xyhong-monitortimeupdate                                 -> origin/xyhong-monitortimeupdate
     * [new branch]        yupd_add_fullchain_tutorial                              -> origin/yupd_add_fullchain_tutorial
     * [new branch]        yupd_add_path_cdlpmt                                     -> origin/yupd_add_path_cdlpmt
       8a0cee60..0c6d077c  yupd_innerwater_test                                     -> origin/yupd_innerwater_test
     * [new branch]        yupd_mingxia_fullchain_tutorial                          -> origin/yupd_mingxia_fullchain_tutorial
     * [new branch]        yupd_opsurface_change                                    -> origin/yupd_opsurface_change
     * [new branch]        yupd_ray_trace                                           -> origin/yupd_ray_trace
       56a8d83b..4da028ed  ze_TriggerMultiplicityPerPMT_8nsLimit                    -> origin/ze_TriggerMultiplicityPerPMT_8nsLimit
     * [new branch]        zhangez-1PETimePdfOnly-j26.2.0                           -> origin/zhangez-1PETimePdfOnly-j26.2.0
     * [new branch]        zhangez-addoption-UsedTnPENum                            -> origin/zhangez-addoption-UsedTnPENum
     * [new branch]        zhangez-omilrec-fixedR-option                            -> origin/zhangez-omilrec-fixedR-option
     * [new tag]           J26.3.2                                                  -> J26.3.2
     * [new tag]           J26.1.2                                                  -> J26.1.2
     * [new tag]           J26.2.0                                                  -> J26.2.0
     * [new tag]           J26.3.0                                                  -> J26.3.0
     * [new tag]           J26.3.1                                                  -> J26.3.1
    Updating ad833925..05d4af88
    Fast-forward
     .gitignore                                                                                                 |    2 +-
     .gitlab-ci.yml                                                                                             |    8 +-
     .gitlab-ci/oj_helper.sh                                                                                    |    7 +-
     Analysis/AtmoNuFCTagAlg/CMakeLists.txt                                                                     |    1 +
     Analysis/AtmoNuFCTagAlg/share/run.py                                                                       |    9 +-
     Analysis/AtmoNuFCTagAlg/src/AtmoNuFCTagAlg.cc                                                              |  322 ++++++++++++++++++---------------
     Analysis/AtmoNuFCTagAlg/src/AtmoNuFCTagAlg.h                                                               |   36 ++--
     Analysis/AtmoNuFCTagSvc/AtmoNuFCTagSvc/IAtmoNuFCTagSvc.h                                                   |    6 +
     Analysis/AtmoNuFCTagSvc/src/AtmoNuFCTagSvc.cc                                                              |   54 ++++++
     Analysis/AtmoNuFCTagSvc/src/AtmoNuFCTagSvc.h                                                               |    6 +
     Analysis/FlasherTagAlg/src/FlasherTagAlg.cc                                                                |   83 +++++++--
     Analysis/FlasherTagAlg/src/FlasherTagAlg.h                                                                 |    4 +-
     CMakeLists.txt                                                                                             |    4 +-
     Calibration/PMTCalibSvc/PMTCalibSvc/CondObjectType.hh                                                      |   79 ++++++++
     Calibration/PMTCalibSvc/src/PMTCalibSvc.cc                                                                 |   28 +--
     Calibration/PMTCalibSvc/src/PMTCalibSvc.h                                                                  |    5 +
     DataModel/AEDM/Event/AtmoNuFCHeader.h                                                                      |   37 +++-
     DataModel/EDMPath/EDMPath/EDMPath.hh                                                                       |    9 +
     Database/CondDB/src/CondDBSvc.cc                                                                           |  237 ++++++++++++++++++++----
     Database/CondDB/src/CondDBSvc.h                                                                            |   31 +++-
     Database/CondDB/src/CondDBUpdateEvtHdl.cc                                                                  |   21 ++-
     Database/CondDB/src/CondDBUpdateEvtHdl.hh                                                                  |    3 +-
     Doc/oum/source/detsim/calib.md                                                                             |   19 ++
     Doc/oum/source/detsim/figs/CLSMixedSourceGeometry.png                                                      |  Bin 0 -> 58473 bytes
     Doc/oum/source/index.rst                                                                                   |    2 +
     Doc/oum/source/releasenotes/J26.1.md                                                                       |   83 +++++++++
     Doc/oum/source/releasenotes/J26.2.md                                                                       |   40 +++++
     Doc/oum/source/releasenotes/J26.3.md                                                                       |   83 +++++++++
     Examples/OECEventAnalysis/OECEventAnalysis/AssembTool.h                                                    |    5 +-
     Examples/OECEventAnalysis/src/AssembTool.cc                                                                |   63 ++++---
     Examples/Tutorial/CMakeLists.txt                                                                           |    1 +
     Examples/Tutorial/python/Tutorial/JUNOCommonModule.py                                                      |  102 +++++++++--
     Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                                                      |   63 +++++--
     Examples/Tutorial/python/Tutorial/JUNOElecSimModule.py                                                     |    4 +-
     Examples/Tutorial/python/Tutorial/JUNOEventRecModule.py                                                    |  262 +++++++++++++++++++++++----
     Examples/Tutorial/python/Tutorial/JUNOTaggingModule.py                                                     |    8 +-
     Examples/Tutorial/python/Tutorial/JUNOWaveRecModule.py                                                     |   11 +-
     Examples/Tutorial/share/RecConfigs/evtrec_aedm_cdwpttchi2_steering.yaml                                    |   36 ++++
     Examples/Tutorial/share/RecConfigs/evtrec_aedm_reprod.yaml                                                 |   57 ++++++
     Examples/Tutorial/share/RecConfigs/evtrec_muon_edwin_v1.yaml                                               |   33 ++++
     Examples/Tutorial/share/RecConfigs/evtrec_muon_edwin_v2.yaml                                               |   32 ++++
     Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OEC.yaml                                   |    2 +-
     Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OEC_npecut.yaml                            |    2 +-
     Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OEC_woEcut.yaml                            |    2 +-
     Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OEC_woEcut_npecut.yaml                     |    2 +-
     Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OECtotalcharge_NNWaveRec.yaml              |   79 ++++++++
     Examples/Tutorial/share/RecConfigs/hemlrec_muon_amber_default.yaml                                         |    1 +
     Examples/Tutorial/share/RecConfigs/waverec_calib_reprod_NNWaveRec.yaml                                     |   12 ++
     Examples/Tutorial/share/mac/GtPosGeoMapping.yaml                                                           |    2 +
     Examples/Tutorial/share/opticks_juno.sh                                                                    |   23 +++
     Examples/Tutorial/share/tut_aedm.py                                                                        |   24 ++-
     Examples/Tutorial/share/tut_detsim.py                                                                      |   10 ++
     Generator/CMakeLists.txt                                                                                   |    4 +-
     Generator/GenDeex/CMakeLists.txt                                                                           |    1 +
     Generator/GenDeex/include/deex.h                                                                           |    3 +-
     Generator/GenDeex/src/deex.cc                                                                              |   41 ++++-
     Generator/GenGEMINI/CMakeLists.txt                                                                         |   38 ++++
     Generator/GenGEMINI/include/GenGEMINI.h                                                                    |   72 ++++++++
     Generator/GenGEMINI/src/GenGEMINI.cpp                                                                      | 1227 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     Generator/GenGEMINI/src/GenGEMINIApp.cpp                                                                   |  115 ++++++++++++
     Generator/GenGenie/share/runatmo.py                                                                        |    7 +
     Generator/GenGenie/src/GtGenieAtmoEvGenTool.cc                                                             |    1 +
     Generator/GenGenie/src/GtGenieAtmoEvGenTool.h                                                              |    1 +
     Generator/ProtonDecay/CMakeLists.txt                                                                       |    2 +
     Generator/ProtonDecay/src/ProtonDecayGen.cc                                                                |   43 +++--
     Generator/ProtonDecay/src/ProtonDecayGen.h                                                                 |   46 ++++-
     OEC/HECAlg/src/HECSnTool.cc                                                                                |    1 +
     OEC/OECTutorial/python/OECTutorial/JUNOOECModule.py                                                        |    2 +-
     OEC/OECTutorial/share/DummyCommonConfig_FullLSV2.json                                                      |    5 +-
     OEC/SNMonitorAlg/SNOnlineMonitor/src/SNOnlineMonitor.cc                                                    |   16 +-
     OEC/readFromRecAlg/src/readFromRecAlg.cc                                                                   |    8 +-
     OEC/readFromRecAlg/src/readFromRecAlg.h                                                                    |    2 +
     Reconstruction/CMakeLists.txt                                                                              |    1 +
     Reconstruction/Deconvolution/src/Deconvolution.cc                                                          |    6 +-
     Reconstruction/Deconvolution/src/Deconvolution.h                                                           |    1 +
     Reconstruction/EdwinRec/CMakeLists.txt                                                                     |    1 -
     Reconstruction/EdwinRec/src/EdwinRecAlg.cc                                                                 |  221 ++++++++++++++++++++---
     Reconstruction/EdwinRec/src/EdwinRecAlg.h                                                                  |   12 ++
     Reconstruction/EnergyCorrection/share/run.py                                                               |  150 ++++++++++++++++
     Reconstruction/EnergyCorrection/share/run.sh                                                               |   35 +++-
     Reconstruction/EnergyCorrection/src/EnergyCorrectionAlg.cc                                                 |  143 +++++++++++----
     Reconstruction/EnergyCorrection/src/EnergyCorrectionAlg.h                                                  |   11 +-
     Reconstruction/EnergyCorrection/src/RadialBiasEvtVertexCorrection.cc                                       |  233 ++++++++++++++++++++++++
     Reconstruction/HEMLRec/HEMLRec/HEMLRecTool.h                                                               |   16 +-
     Reconstruction/HEMLRec/HEMLRec/MuonAmberRecTool.h                                                          |    9 +
     Reconstruction/HEMLRec/share/run_amber.py                                                                  |   31 +++-
     Reconstruction/HEMLRec/share/run_amber_sd.sh                                                               |   28 +++
     Reconstruction/HEMLRec/share/run_amber_sd_200.sh                                                           |   54 ++++++
     Reconstruction/HEMLRec/src/HEMLRecAlg.cc                                                                   |   39 +++-
     Reconstruction/HEMLRec/src/HEMLRecAlg.h                                                                    |    1 +
     Reconstruction/HEMLRec/src/MuonAmberRecTool.cc                                                             |  259 +++++++++++++++++----------
     Reconstruction/HEMLRec/src/MuonPNClassifyRecTool.cc                                                        |    6 +-
     Reconstruction/OECWFrec/src/DeconvolutionTool.cc                                                           |    4 +-
     Reconstruction/OECWFrec/src/OECWFrec.cc                                                                    |   10 +-
     Reconstruction/OMILRECV2/CMakeLists.txt                                                                    |   18 ++
     Reconstruction/OMILRECV2/OMILRECV2/BulkOps.h                                                               |  113 ++++++++++++
     Reconstruction/OMILRECV2/OMILRECV2/IRecTool.h                                                              |   94 ++++++++++
     Reconstruction/OMILRECV2/OMILRECV2/NPEUnifCTool.h                                                          |   22 +++
     Reconstruction/OMILRECV2/OMILRECV2/OMILRECV2.h                                                             |  351 ++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/OMILRECV2/RecHelper.h                                                             |  112 ++++++++++++
     Reconstruction/OMILRECV2/python/OMILRECV2/__init__.py                                                      |    2 +
     Reconstruction/OMILRECV2/share/evtrec_reprod_steering_using_OEC_woEcut_V2.yaml                             |  104 +++++++++++
     Reconstruction/OMILRECV2/src/NPEUnifCTool.cc                                                               |   49 +++++
     Reconstruction/OMILRECV2/src/OMILRECV2.cc                                                                  |  646 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/OMILRECV2_calibration.cc                                                      |  145 +++++++++++++++
     Reconstruction/OMILRECV2/src/OMILRECV2_constants.h                                                         |   49 +++++
     Reconstruction/OMILRECV2/src/OMILRECV2_debug.cc                                                            |  319 +++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/OMILRECV2_fit.cc                                                              |  452 ++++++++++++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/OMILRECV2_geometry.cc                                                         |   95 ++++++++++
     Reconstruction/OMILRECV2/src/OMILRECV2_likelihood.cc                                                       |  115 ++++++++++++
     Reconstruction/OMILRECV2/src/PMTRealInputTool.cc                                                           |  357 +++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/PMTRealParaTool.cc                                                            |  355 ++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/PMTToyInputTool.cc                                                            |  406 ++++++++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/PMTToyParaTool.cc                                                             |  300 +++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/RecHelper.cc                                                                  |  449 ++++++++++++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_charge_ll.cc                                                          |  106 +++++++++++
     Reconstruction/OMILRECV2/src/omilrec_charge_ll.h                                                           |   39 ++++
     Reconstruction/OMILRECV2/src/omilrec_event_compute.cc                                                      |   95 ++++++++++
     Reconstruction/OMILRECV2/src/omilrec_event_compute.h                                                       |   36 ++++
     Reconstruction/OMILRECV2/src/omilrec_fcn.cc                                                                |  301 +++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_fcn.h                                                                 |  130 ++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_geometry.cc                                                           |   60 +++++++
     Reconstruction/OMILRECV2/src/omilrec_geometry.h                                                            |   23 +++
     Reconstruction/OMILRECV2/src/omilrec_likelihood.cc                                                         |  265 +++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_likelihood.h                                                          |   79 ++++++++
     Reconstruction/OMILRECV2/src/omilrec_minuit_setup.cc                                                       |   85 +++++++++
     Reconstruction/OMILRECV2/src/omilrec_minuit_setup.h                                                        |   22 +++
     Reconstruction/OMILRECV2/src/omilrec_npe.cc                                                                |   87 +++++++++
     Reconstruction/OMILRECV2/src/omilrec_npe.h                                                                 |   24 +++
     Reconstruction/OMILRECV2/src/omilrec_serialization.cc                                                      |  923 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_serialization.h                                                       |  177 ++++++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_time_pdf.cc                                                           |  146 +++++++++++++++
     Reconstruction/OMILRECV2/src/omilrec_time_pdf.h                                                            |   24 +++
     Reconstruction/QCtrRecAlg/QCtrRecAlg/IMixedPhaseVertexSvc.h                                                |   13 +-
     Reconstruction/QCtrRecAlg/src/JVertex.cc                                                                   |    4 +
     Reconstruction/QCtrRecAlg/src/MixedPhaseVertexSvc.cc                                                       |  531 +++++++++++++++++++++++++++++++++++++++++++++++++-----
     Reconstruction/QCtrRecAlg/src/MixedPhaseVertexSvc.h                                                        |   50 +++++-
     Reconstruction/QCtrRecAlg/src/QCtrRecAlg.cc                                                                |    2 +-
     Reconstruction/QCtrRecAlg/src/WaterPhaseVertex.cc                                                          |  258 +++++++++++++++++++++++----
     Reconstruction/QCtrRecAlg/src/WaterPhaseVertex.h                                                           |   18 ++
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/CdWpTtChi2RecTool.cpp                                         |    4 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/estimator/fht/map/WpTimeShiftCorrectionMap.hpp                |   16 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/estimator/fht_tt/FhtTtCorrMapEstimator.cpp                    |   41 +++--
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/estimator/fht_tt/FhtTtCorrMapEstimator.hpp                    |    8 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/estimator/optimizer/Optimizer.cpp                             |   10 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/estimator/tt/combinator/MaskHeightCartesianProdCombinator.cpp |   24 ++-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/initializer/Initializer.hpp                                   |    8 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/initializer/fht/ClusterMaxChargeInitializer.cpp               |    6 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/strategy/Factory.cpp                                          |   12 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/strategy/Factory.hpp                                          |    8 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/strategy/Registry.cpp                                         |    6 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/strategy/Registry.hpp                                         |    2 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/strategy/Strategy.cpp                                         |   16 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/transformer/WaterPhaseTransformer.cpp                         |   10 +-
     Reconstruction/RecMuon/CdWpTtChi2RecTool/src/utils/timer.hpp                                               |   12 +-
     Reconstruction/RecMuon/RecMuonAlg/CMakeLists.txt                                                           |    2 +-
     Reconstruction/RecMuon/RecMuonAlg/src/RecMuonAlg.cc                                                        |    9 +-
     Reconstruction/RecMuon/RecMuonAlg/src/RecMuonAlg.h                                                         |    4 +-
     Reconstruction/RecTools/RecTools/IEvtVertexCorrection.hh                                                   |   25 +++
     Reconstruction/TTCalib/src/TTCalibAlg.cc                                                                   |  177 +++++++++++++++++-
     Reconstruction/TTCalib/src/TTCalibAlg.h                                                                    |   33 +++-
     Reconstruction/TWNNWaveRec/src/TWNNWaveRec.cc                                                              |   71 ++++++--
     Reconstruction/TWNNWaveRec/src/TWNNWaveRec.h                                                               |   11 +-
     RootIO/RootIOTools/share/rootio-dump                                                                       |    2 +-
     RootIO/RootIOTools/src/DumpEDMAlg.cc                                                                       |   30 ++++
     Simulation/DetSimV2/AnalysisCode/include/OPSimAnaMgr_IBDSelection.hh                                       |   78 ++++++++
     Simulation/DetSimV2/AnalysisCode/src/OPSimAnaMgr_IBDSelection.cc                                           |  298 +++++++++++++++++++++++++++++++
     Simulation/DetSimV2/CalibUnit/share/ACU_source_weight_QuickConnector.gdml                                  |   11 +-
     Simulation/DetSimV2/CalibUnit/share/ACU_source_weight_QuickConnector_Ti.gdml                               |  209 +++++++++++-----------
     Simulation/DetSimV2/CalibUnit/share/AmC_ACU_source_weight_QuickConnector.gdml                              |   11 +-
     Simulation/DetSimV2/CalibUnit/share/AmC_ACU_source_weight_QuickConnector_thicker.gdml                      |   11 +-
     Simulation/DetSimV2/CalibUnit/share/AmC_ACU_source_weight_QuickConnector_thickest.gdml                     |   11 +-
     Simulation/DetSimV2/CalibUnit/share/CLS_mixed_source_AmC_Cs_Temperature_sensor.gdml                        |  582 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     Simulation/DetSimV2/CalibUnit/share/K40_ACU_source_weight_QuickConnector.gdml                              |   13 +-
     Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc                                |   40 ++++-
     Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc                                 |    7 +
     Simulation/DetSimV2/OPSimulator/src/G4OPSimulator.cc                                                       |  101 ++++++++---
     Simulation/DetSimV2/OPSimulator/src/G4OPSimulator.h                                                        |   15 +-
     Simulation/DetSimV2/OPSimulator/src/OPSimSvc.cc                                                            |    6 +-
     Simulation/DetSimV2/OPSimulator/src/OPSimSvc.h                                                             |    2 +
     Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc                                                    |    7 +-
     Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h                                                     |   39 ++--
     Simulation/DetSimV2/PhysiSim/include/DsG4ScintSimple.h                                                     |  372 +++++++++-----------------------------
     Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h                                                   |   21 ++-
     Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc                                                        |  399 ++++++++++++++++++++---------------------
     Simulation/DetSimV2/PhysiSim/src/DsG4ScintSimple.cc                                                        | 1187 ++++++++++++++++++++++++++----------------------------------------------------------------------------------------------
     Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc                                                      |  141 +++++++--------
     Simulation/ElecSimV3/ElecSimAlg/src/ElecSimSvc.cc                                                          |   60 +++++--
     Simulation/ElecSimV3/ElecSimAlg/src/ElecSimSvc.h                                                           |    5 +
     Simulation/ElecSimV3/ElecSimAlg/src/EvtMixingAlg.cc                                                        |   48 +++--
     Simulation/ElecSimV3/ElecSimAlg/src/EvtMixingAlg.h                                                         |    2 +-
     Simulation/ElecSimV3/ElecSimAlg/src/PMTSimAlg_new.cc                                                       |   66 +++++--
     Simulation/ElecSimV3/ElecSimAlg/src/PulseGen_Hamamatsu.cc                                                  |   12 +-
     Simulation/ElecSimV3/ElecSimAlg/src/PulseGen_NNVT.cc                                                       |   15 +-
     Simulation/ElecSimV3/ElecSimAlg/src/PulseGen_SPMT.cc                                                       |   11 +-
     Simulation/ElecSimV3/ElecSimAlg/src/TriggerSimAlg.cc                                                       |   43 ++++-
     Simulation/ElecSimV3/ElecSimAlg/src/TriggerSimAlg.h                                                        |    3 +
     Simulation/GenTools/CMakeLists.txt                                                                         |    4 +-
     Simulation/GenTools/src/GtGenDeexTool.cc                                                                   |   50 +++++-
     Simulation/GenTools/src/GtGenDeexTool.h                                                                    |    8 +-
     Utilities/DataPathHelper/DataPathHelper/bad_channel_path.h                                                 |    9 +-
     Utilities/DataPathHelper/src/bad_channel_path.cc                                                           |   19 +-
     Utilities/DataPathHelper/src/dcr_path.cc                                                                   |   30 +++-
     cmake/legacy/JUNODependencies.cmake                                                                        |    4 +
     oj_initialize.sh                                                                                           |    7 +-
     setup.sh                                                                                                   |    1 -
     206 files changed, 15028 insertions(+), 2489 deletions(-)
     create mode 100644 Calibration/PMTCalibSvc/PMTCalibSvc/CondObjectType.hh
     create mode 100755 Doc/oum/source/detsim/figs/CLSMixedSourceGeometry.png
     create mode 100644 Doc/oum/source/releasenotes/J26.2.md
     create mode 100644 Doc/oum/source/releasenotes/J26.3.md
     create mode 100644 Examples/Tutorial/share/RecConfigs/evtrec_aedm_cdwpttchi2_steering.yaml
     create mode 100644 Examples/Tutorial/share/RecConfigs/evtrec_aedm_reprod.yaml
     create mode 100644 Examples/Tutorial/share/RecConfigs/evtrec_muon_edwin_v1.yaml
     create mode 100644 Examples/Tutorial/share/RecConfigs/evtrec_muon_edwin_v2.yaml
     create mode 100755 Examples/Tutorial/share/RecConfigs/evtrec_reprod_steering_using_OECtotalcharge_NNWaveRec.yaml
     create mode 100755 Examples/Tutorial/share/RecConfigs/waverec_calib_reprod_NNWaveRec.yaml
     create mode 100644 Generator/GenGEMINI/CMakeLists.txt
     create mode 100644 Generator/GenGEMINI/include/GenGEMINI.h
     create mode 100644 Generator/GenGEMINI/src/GenGEMINI.cpp
     create mode 100644 Generator/GenGEMINI/src/GenGEMINIApp.cpp
     create mode 100644 Reconstruction/EnergyCorrection/share/run.py
     create mode 100644 Reconstruction/EnergyCorrection/src/RadialBiasEvtVertexCorrection.cc
     create mode 100755 Reconstruction/HEMLRec/share/run_amber_sd.sh
     create mode 100755 Reconstruction/HEMLRec/share/run_amber_sd_200.sh
     create mode 100644 Reconstruction/OMILRECV2/CMakeLists.txt
     create mode 100644 Reconstruction/OMILRECV2/OMILRECV2/BulkOps.h
     create mode 100644 Reconstruction/OMILRECV2/OMILRECV2/IRecTool.h
     create mode 100644 Reconstruction/OMILRECV2/OMILRECV2/NPEUnifCTool.h
     create mode 100644 Reconstruction/OMILRECV2/OMILRECV2/OMILRECV2.h
     create mode 100644 Reconstruction/OMILRECV2/OMILRECV2/RecHelper.h
     create mode 100644 Reconstruction/OMILRECV2/python/OMILRECV2/__init__.py
     create mode 100644 Reconstruction/OMILRECV2/share/evtrec_reprod_steering_using_OEC_woEcut_V2.yaml
     create mode 100644 Reconstruction/OMILRECV2/src/NPEUnifCTool.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_calibration.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_constants.h
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_debug.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_fit.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_geometry.cc
     create mode 100644 Reconstruction/OMILRECV2/src/OMILRECV2_likelihood.cc
     create mode 100644 Reconstruction/OMILRECV2/src/PMTRealInputTool.cc
     create mode 100644 Reconstruction/OMILRECV2/src/PMTRealParaTool.cc
     create mode 100644 Reconstruction/OMILRECV2/src/PMTToyInputTool.cc
     create mode 100644 Reconstruction/OMILRECV2/src/PMTToyParaTool.cc
     create mode 100644 Reconstruction/OMILRECV2/src/RecHelper.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_charge_ll.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_charge_ll.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_event_compute.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_event_compute.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_fcn.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_fcn.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_geometry.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_geometry.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_likelihood.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_likelihood.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_minuit_setup.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_minuit_setup.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_npe.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_npe.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_serialization.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_serialization.h
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_time_pdf.cc
     create mode 100644 Reconstruction/OMILRECV2/src/omilrec_time_pdf.h
     create mode 100644 Reconstruction/RecTools/RecTools/IEvtVertexCorrection.hh
     create mode 100644 Simulation/DetSimV2/AnalysisCode/include/OPSimAnaMgr_IBDSelection.hh
     create mode 100644 Simulation/DetSimV2/AnalysisCode/src/OPSimAnaMgr_IBDSelection.cc
     create mode 100644 Simulation/DetSimV2/CalibUnit/share/CLS_mixed_source_AmC_Cs_Temperature_sensor.gdml
    A[blyth@localhost junosw]$ 





