compare_workstation_to_v100_cluster_timings
==============================================


Cluster (avoiding double launch)
------------------------------------

::

    T0="2026/03/30 15:00" T1="2026/03/30 16:30" ojr  proi  ##   confirmed single launch of all 4 tests

::

    U[blyth@lxlogin004 oj]$ T0="2026/03/30 15:00" T1="2026/03/30 16:30" ojp  proi
                       BASH_SOURCE : /hpcfs/juno/junogpu/blyth/oj/oj.bash
                            OJ_DIR : /hpcfs/juno/junogpu/blyth/oj
                               PWD : /hpcfs/juno/junogpu/blyth/oj
                            ENVSET : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.6.3/el9_amd64_gcc11/2026_03_26/envset.sh
                       ENVSET_NAME : OJ_063
                        TESTSCRIPT : doublemuon/doublemuon.sh
                    TESTSCRIPT_ARG : run
                   TESTSCRIPT_NAME : oj_doublemuon_doublemuon
                             TESTS : hit hitmerged hitlite hitlitemerged
                              TEST : hitlitemerged
                           LOGBASE : /hpcfs/juno/junogpu/blyth/log
                           LOGROOT : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon
                           LOGFOLD : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon/2026-03-30-1614
                            LOGDIR : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon/2026-03-30-1614/OJ_063_ok1_hitlitemerged_seed42_evtmax1
                          IDENTITY : OJ_063_ok1_hitlitemerged_seed42_evtmax1
    Identity                                             Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)    Sub TAIL→RESET(s)    VM(MB)  RSS(MB)  Comment
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    hit/A000_QSim                                         256.759   985.801733           213.532201             5.869275           766.060973   28461.14  8139.27  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517  # slice=1,max_slot_M=180
    hitlite/A000_QSim                                     254.166   770.216419           213.178687             1.472494           555.304696   17412.29  5350.53  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517  # slice=1,max_slot_M=180
    hitmerged/A000_QSim                                   258.779   230.352919           213.334257             1.551070            15.197918   91963.07  6657.50  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=6698244  # slice=1,max_slot_M=180
    hitlitemerged/A000_QSim                               253.462   214.627446           212.892030             0.384215             1.028643   81983.82  4930.09  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=6698244  # slice=1,max_slot_M=180


Comparing duration cluster/workstation::

    In [1]: import numpy as np
    In [2]: a = np.array([985,770,230,214])
    In [3]: b = np.array([215,170,30,24])
    In [4]: a/b
    Out[4]: array([4.58139535, 4.52941176, 7.66666667, 8.91666667])

Kernel time PREL->POST, workstation factor of 9 faster as expected (RTX advantage)::

    In [5]: 213/23
    Out[5]: 9.26086956521739

Everything else : workstation factor of 2-3 faster.

For hitlitemerged, overheads are less than 1 percent of kernel time::

    In [7]: 212.892030/214.627446
    Out[7]: 0.9919142866751535



HMM: NEED THE no-opticks number on cluster
-------------------------------------------

* it was ~7000s on workstation (117min, ~2 hrs)
* expect 21000s on cluster (350min, ~6 hrs)


If meets that expection::

    In [14]: 21000/215
    Out[14]: 97.67441860465117



Workstation (no contention, no double launch)
------------------------------------------------


::

   A[blyth@localhost detsim]$ pwd   # LOGROOT defaults to invoking directory
    /data1/blyth/tmp/j/zhenning_double_muon/detsim

    A[blyth@localhost detsim]$ T0="2025-12-04 16:00" T1="2025-12-04 18:00" ~/o/bin/SProf.sh proi
    Identity                                             Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)    Sub TAIL→RESET(s)    VM(MB)  RSS(MB)  Comment
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    hit/A000_QSim                                         106.466   215.560469            22.996241             1.949322           190.446287   32168.83  7971.96  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    hitlite/A000_QSim                                     106.462   170.226838            23.108319             0.484299           146.471936   32499.61  5361.86  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    hitmerged/A000_QSim                                   106.770    30.400825            22.988498             0.543559             6.713401   88292.85  6634.07  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029  # slice=1,max_slot_M=150
    hitlitemerged/A000_QSim                               107.263    23.835564            23.097717             0.181023             0.404235   87284.29  4988.84  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029


::

    A[blyth@localhost sop]$ T0="2025-12-04 16:00" T1="2025-12-04 18:00" LOGROOT=/data1/blyth/tmp/j/zhenning_double_muon/detsim REPORT=1 ~/o/bin/SProf.sh proi
      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2025-12-04 16:07:25.334  1024.60   493.44 SEvt__Init_RUN_META
     30.755473  30.755473 2025-12-04 16:07:56.090  6394.04  1368.74 CSGOptiX__Create_HEAD
     32.047164   1.291691 2025-12-04 16:07:57.382  8509.56  1955.52 CSGOptiX__Create_TAIL
    106.465519  74.418355 2025-12-04 16:09:11.800 11099.55  4542.50 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    106.465588   0.000069 2025-12-04 16:09:11.800 11099.55  4542.50 A000_QSim__simulate_HEAD
    106.465623   0.000035 2025-12-04 16:09:11.800 11099.55  4542.50 A000_SEvt__BeginOfRun
    106.465743   0.000120 2025-12-04 16:09:11.800 11099.55  4542.50 A000_SEvt__beginOfEvent_FIRST_EGPU
    106.465769   0.000026 2025-12-04 16:09:11.800 11099.55  4542.50 A000_SEvt__setIndex
    106.571435   0.105666 2025-12-04 16:09:11.906 11153.01  4595.72 A000_QSim__simulate_LBEG
    106.571472   0.000037 2025-12-04 16:09:11.906 11153.01  4595.72 A000_QSim__simulate_PRUP
    106.634089   0.062617 2025-12-04 16:09:11.969 28785.01  4596.59 A000_QSim__simulate_PREL
    129.630330  22.996241 2025-12-04 16:09:34.965 28785.01  4601.41 A000_QSim__simulate_POST
    131.579652   1.949322 2025-12-04 16:09:36.914 30461.76  6279.35 A000_QSim__simulate_DOWN
    131.579698   0.000046 2025-12-04 16:09:36.914 30461.76  6279.35 A000_QSim__simulate_LEND
    131.579721   0.000023 2025-12-04 16:09:36.914 30461.76  6279.35 A000_QSim__simulate_PCAT
    131.579765   0.000044 2025-12-04 16:09:36.914 30461.76  6279.35 A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    131.579770   0.000005 2025-12-04 16:09:36.914 30461.76  6279.35 A000_QSim__simulate_TAIL
    131.579950   0.000180 2025-12-04 16:09:36.914 30461.76  6279.35 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
    131.580014   0.000064 2025-12-04 16:09:36.914 30461.76  6279.35 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_HEAD
    322.025602 190.445588 2025-12-04 16:12:47.360 32168.83  7971.96 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_TAIL # hit=27471928,merged=21062899,save=6409029
    322.025669   0.000067 2025-12-04 16:12:47.360 32168.83  7971.96 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
    322.025677   0.000008 2025-12-04 16:12:47.360 32168.83  7971.96 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    322.026057   0.000380 2025-12-04 16:12:47.360 32168.83  7971.96 A000_QSim__reset_HEAD
    322.026391   0.000334 2025-12-04 16:12:47.361 32115.37  7918.59 A000_SEvt__endIndex
    322.030447   0.004056 2025-12-04 16:12:47.365 30438.62  6241.84 A000_SEvt__EndOfRun
    Identity                                             Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)    Sub TAIL→RESET(s)    VM(MB)  RSS(MB)  Comment
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    hit/A000_QSim                                         106.466   215.560469            22.996241             1.949322           190.446287   32168.83  7971.96  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928

    ## 322.026057 - 106.465588 = 215.56046



      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2025-12-04 16:15:54.245  1023.13   496.45 SEvt__Init_RUN_META
     29.961488  29.961488 2025-12-04 16:16:24.206  6393.96  1375.03 CSGOptiX__Create_HEAD
     31.212086   1.250598 2025-12-04 16:16:25.457  8509.47  1960.28 CSGOptiX__Create_TAIL
    106.462371  75.250285 2025-12-04 16:17:40.707 11099.45  4545.73 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    106.462438   0.000067 2025-12-04 16:17:40.707 11099.45  4545.73 A000_QSim__simulate_HEAD
    106.462471   0.000033 2025-12-04 16:17:40.707 11099.45  4545.73 A000_SEvt__BeginOfRun
    106.462645   0.000174 2025-12-04 16:17:40.707 11099.45  4545.73 A000_SEvt__beginOfEvent_FIRST_EGPU
    106.462671   0.000026 2025-12-04 16:17:40.707 11099.45  4545.73 A000_SEvt__setIndex
    106.561261   0.098590 2025-12-04 16:17:40.806 11152.91  4598.96 A000_QSim__simulate_LBEG
    106.561297   0.000036 2025-12-04 16:17:40.806 11152.91  4598.96 A000_QSim__simulate_PRUP
    106.624614   0.063317 2025-12-04 16:17:40.869 31728.91  4599.39 A000_QSim__simulate_PREL
    129.732933  23.108319 2025-12-04 16:18:03.977 31728.91  4604.21 A000_QSim__simulate_POST
    130.217232   0.484299 2025-12-04 16:18:04.462 32148.10  5024.47 A000_QSim__simulate_DOWN
    130.217271   0.000039 2025-12-04 16:18:04.462 32148.10  5024.47 A000_QSim__simulate_LEND
    130.217293   0.000022 2025-12-04 16:18:04.462 32148.10  5024.47 A000_QSim__simulate_PCAT
    130.217334   0.000041 2025-12-04 16:18:04.462 32148.10  5024.47 A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    130.217340   0.000006 2025-12-04 16:18:04.462 32148.10  5024.47 A000_QSim__simulate_TAIL
    130.217641   0.000301 2025-12-04 16:18:04.462 32148.10  5024.47 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
    130.217711   0.000070 2025-12-04 16:18:04.462 32148.10  5024.47 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_HEAD
    276.688824 146.471113 2025-12-04 16:20:30.933 32499.61  5361.86 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_TAIL # hit=27471928,merged=21062899,save=6409029
    276.688881   0.000057 2025-12-04 16:20:30.933 32499.61  5361.86 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
    276.688888   0.000007 2025-12-04 16:20:30.933 32499.61  5361.86 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    276.689276   0.000388 2025-12-04 16:20:30.934 32499.61  5361.86 A000_QSim__reset_HEAD
    276.689602   0.000326 2025-12-04 16:20:30.934 32446.15  5308.67 A000_SEvt__endIndex
    276.691025   0.001423 2025-12-04 16:20:30.936 32026.96  4889.48 A000_SEvt__EndOfRun
    hitlite/A000_QSim                                     106.462   170.226838            23.108319             0.484299           146.471936   32499.61  5361.86  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2025-12-04 16:20:53.651  1023.25   495.63 SEvt__Init_RUN_META
     30.937038  30.937038 2025-12-04 16:21:24.588  6394.08  1377.59 CSGOptiX__Create_HEAD
     32.213934   1.276896 2025-12-04 16:21:25.865  8509.61  1965.09 CSGOptiX__Create_TAIL
    107.262853  75.048919 2025-12-04 16:22:40.913 11099.59  4552.83 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    107.262921   0.000068 2025-12-04 16:22:40.913 11099.59  4552.83 A000_QSim__simulate_HEAD
    107.262955   0.000034 2025-12-04 16:22:40.914 11099.59  4552.83 A000_SEvt__BeginOfRun
    107.263078   0.000123 2025-12-04 16:22:40.914 11099.59  4552.83 A000_SEvt__beginOfEvent_FIRST_EGPU
    107.263104   0.000026 2025-12-04 16:22:40.914 11099.59  4552.83 A000_SEvt__setIndex
    107.367226   0.104122 2025-12-04 16:22:41.018 11153.05  4606.05 A000_QSim__simulate_LBEG
    107.367261   0.000035 2025-12-04 16:22:41.018 11153.05  4606.05 A000_QSim__simulate_PRUP
    107.415403   0.048142 2025-12-04 16:22:41.066 22481.05  4606.93 A000_QSim__simulate_PREL
    130.513120  23.097717 2025-12-04 16:23:04.164 22481.05  4611.74 A000_QSim__simulate_POST
    130.694143   0.181023 2025-12-04 16:23:04.345 86994.84  4713.71 A000_QSim__simulate_DOWN
    130.694182   0.000039 2025-12-04 16:23:04.345 86994.84  4713.71 A000_QSim__simulate_LEND
    130.694203   0.000021 2025-12-04 16:23:04.345 86994.84  4713.71 A000_QSim__simulate_PCAT
    130.694244   0.000041 2025-12-04 16:23:04.345 86994.84  4713.71 A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
    130.694250   0.000006 2025-12-04 16:23:04.345 86994.84  4713.71 A000_QSim__simulate_TAIL
    130.694408   0.000158 2025-12-04 16:23:04.345 86994.84  4713.71 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
    130.694467   0.000059 2025-12-04 16:23:04.345 86994.84  4713.71 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_HEAD
    131.098066   0.403599 2025-12-04 16:23:04.749 87284.16  4988.84 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_TAIL # hit=6409029
    131.098102   0.000036 2025-12-04 16:23:04.749 87284.16  4988.84 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
    131.098108   0.000006 2025-12-04 16:23:04.749 87284.16  4988.84 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    131.098485   0.000377 2025-12-04 16:23:04.749 87284.29  4988.84 A000_QSim__reset_HEAD
    131.098769   0.000284 2025-12-04 16:23:04.749 87230.82  4935.50 A000_SEvt__endIndex
    131.099464   0.000695 2025-12-04 16:23:04.750 87133.03  4837.70 A000_SEvt__EndOfRun
    hitlitemerged/A000_QSim                               107.263    23.835564            23.097717             0.181023             0.404235   87284.29  4988.84  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2025-12-04 17:11:37.343  1023.01   492.82 SEvt__Init_RUN_META
     29.918053  29.918053 2025-12-04 17:12:07.262  6393.87  1376.53 CSGOptiX__Create_HEAD
     31.164170   1.246117 2025-12-04 17:12:08.508  8509.39  1964.82 CSGOptiX__Create_TAIL
    106.770381  75.606211 2025-12-04 17:13:24.114 11099.38  4550.71 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    106.770446   0.000065 2025-12-04 17:13:24.114 11099.38  4550.71 A000_QSim__simulate_HEAD
    106.770477   0.000031 2025-12-04 17:13:24.114 11099.38  4550.71 A000_SEvt__BeginOfRun
    106.770616   0.000139 2025-12-04 17:13:24.114 11099.38  4550.71 A000_SEvt__beginOfEvent_FIRST_EGPU
    106.770643   0.000027 2025-12-04 17:13:24.114 11099.38  4550.71 A000_SEvt__setIndex
    106.877424   0.106781 2025-12-04 17:13:24.221 11152.84  4603.94 A000_QSim__simulate_LBEG
    106.877463   0.000039 2025-12-04 17:13:24.221 11152.84  4603.94 A000_QSim__simulate_PRUP
    106.925702   0.048239 2025-12-04 17:13:24.269 21840.84  4604.38 A000_QSim__simulate_PREL
    129.914200  22.988498 2025-12-04 17:13:47.258 21840.84  4608.75 A000_QSim__simulate_POST
    130.457759   0.543559 2025-12-04 17:13:47.801 86648.02  5004.11 A000_QSim__simulate_DOWN
    130.457808   0.000049 2025-12-04 17:13:47.801 86648.02  5004.11 A000_QSim__simulate_LEND # slice=1,max_slot_M=150
    130.457829   0.000021 2025-12-04 17:13:47.801 86648.02  5004.11 A000_QSim__simulate_PCAT
    130.457865   0.000036 2025-12-04 17:13:47.801 86648.02  5004.11 A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
    130.457870   0.000005 2025-12-04 17:13:47.801 86648.02  5004.11 A000_QSim__simulate_TAIL
    130.458047   0.000177 2025-12-04 17:13:47.802 86648.02  5004.11 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
    130.458106   0.000059 2025-12-04 17:13:47.802 86648.02  5004.11 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_HEAD
    137.170865   6.712759 2025-12-04 17:13:54.514 88292.85  6634.07 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_TAIL # hit=6409029
    137.170900   0.000035 2025-12-04 17:13:54.514 88292.85  6634.07 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
    137.170909   0.000009 2025-12-04 17:13:54.514 88292.85  6634.07 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    137.171271   0.000362 2025-12-04 17:13:54.515 88292.85  6634.07 A000_QSim__reset_HEAD
    137.171567   0.000296 2025-12-04 17:13:54.515 88239.39  6580.73 A000_SEvt__endIndex
    137.172888   0.001321 2025-12-04 17:13:54.516 87848.21  6189.55 A000_SEvt__EndOfRun
    hitmerged/A000_QSim                                   106.770    30.400825            22.988498             0.543559             6.713401   88292.85  6634.07  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029  # slice=1,max_slot_M=150
    A[blyth@localhost sop]$ 



Cluster (potential resource contention, timings borked by double launch)
------------------------------------------------------------------------------

::

    U[blyth@lxlogin004 oj]$ T0="2026/03/27 1715" T1="2026/03/27 1815" ojp  proi
                       BASH_SOURCE : /hpcfs/juno/junogpu/blyth/oj/oj.bash
                            OJ_DIR : /hpcfs/juno/junogpu/blyth/oj
                               PWD : /hpcfs/juno/junogpu/blyth/oj
                            ENVSET : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.6.3/el9_amd64_gcc11/2026_03_26/envset.sh
                       ENVSET_NAME : OJ_063
                        TESTSCRIPT : doublemuon/doublemuon.sh
                    TESTSCRIPT_ARG : run 
                   TESTSCRIPT_NAME : oj_doublemuon_doublemuon
                             TESTS : hit hitmerged hitlite hitlitemerged
                              TEST : hitlitemerged
                           LOGBASE : /hpcfs/juno/junogpu/blyth/log
                           LOGROOT : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon
                           LOGFOLD : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon/2026-03-30-1450
                            LOGDIR : /hpcfs/juno/junogpu/blyth/log/oj/doublemuon/doublemuon/2026-03-30-1450/OJ_063_ok1_hitlitemerged_seed42_evtmax1
                          IDENTITY : OJ_063_ok1_hitlitemerged_seed42_evtmax1
    Identity                                             Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)    Sub TAIL→RESET(s)    VM(MB)  RSS(MB)  Comment
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    hit/A000_QSim                                         212.531   790.684166            17.570158             0.352908           566.574796   26509.23  8110.63  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517  # slice=2,max_slot_M=150
    hitlite/A000_QSim                                     212.823   671.097659            17.449883             0.086843           455.316210   16836.37  5326.62  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517  # slice=2,max_slot_M=150
    hitmerged/A000_QSim                                   213.208   230.450566            17.505566             0.190331            12.632002   90011.29  6657.35  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=6698244  # slice=2,max_slot_M=150
    hitlitemerged/A000_QSim                               212.569   215.162535            17.455669             0.047024             0.852799   81407.96  4926.58  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=6698244  # slice=2,max_slot_M=150




::

    hitmerged/A000_QSim                                   213.208   230.450566            17.505566             0.190331            12.632002   90011.29  6657.35  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=6698244  # slice=2,max_slot_M=150
      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2026-03-27 17:15:10.028   736.67   490.66 SEvt__Init_RUN_META
     82.937211  82.937211 2026-03-27 17:16:32.965  6157.20  1295.74 CSGOptiX__Create_HEAD
     93.283255  10.346044 2026-03-27 17:16:43.311  9554.50  1920.84 CSGOptiX__Create_TAIL
    212.822581 119.539326 2026-03-27 17:18:42.850 12118.30  4446.34 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    212.822642   0.000061 2026-03-27 17:18:42.850 12118.30  4446.34 A000_QSim__simulate_HEAD
    212.822679   0.000037 2026-03-27 17:18:42.850 12118.30  4446.34 A000_SEvt__BeginOfRun
    212.825619   0.002940 2026-03-27 17:18:42.853 12118.30  4446.34 A000_SEvt__beginOfEvent_FIRST_EGPU
    212.825670   0.000051 2026-03-27 17:18:42.853 12118.30  4446.34 A000_SEvt__setIndex
    213.029687   0.204017 2026-03-27 17:18:43.057 12177.85  4505.86 A000_QSim__simulate_LBEG
    213.029737   0.000050 2026-03-27 17:18:43.057 12177.85  4505.86 A000_QSim__simulate_PRUP
    213.053749   0.024012 2026-03-27 17:18:43.081 15985.85  4506.70 A000_QSim__simulate_PREL
    408.683061 195.629312 2026-03-27 17:21:58.711 15985.85  4511.48 A000_QSim__simulate_POST
    409.837954   1.154893 2026-03-27 17:21:59.866 16412.73  4939.23 A000_QSim__simulate_DOWN
    409.838011   0.000057 2026-03-27 17:21:59.866 16412.73  4939.23 A000_QSim__simulate_PRUP
    409.842553   0.004542 2026-03-27 17:21:59.870 16412.73  4939.23 A000_QSim__simulate_PREL
    427.292436  17.449883 2026-03-27 17:22:17.320 16412.73  4939.23 A000_QSim__simulate_POST
    427.379279   0.086843 2026-03-27 17:22:17.407 16444.54  4971.05 A000_QSim__simulate_DOWN
    427.379371   0.000092 2026-03-27 17:22:17.407 16444.54  4971.05 A000_QSim__simulate_LEND # slice=2,max_slot_M=150
    428.603945   1.224574 2026-03-27 17:22:18.632 16444.54  4971.04 A000_QSim__simulate_PCAT
    428.604070   0.000125 2026-03-27 17:22:18.632 16444.54  4971.04 A000_QSim__simulate_BRES # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517
    428.604091   0.000021 2026-03-27 17:22:18.632 16444.54  4971.04 A000_QSim__simulate_TAIL
    428.608379   0.004288 2026-03-27 17:22:18.636 16444.54  4971.04 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
    428.608496   0.000117 2026-03-27 17:22:18.636 16444.54  4971.04 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_HEAD
    883.913274 455.304778 2026-03-27 17:29:53.941 16836.37  5323.81 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_TAIL # hit=30060517,merged=23362273,save=6698244
    883.913808   0.000534 2026-03-27 17:29:53.941 16836.37  5323.81 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
    883.913824   0.000016 2026-03-27 17:29:53.941 16836.37  5323.81 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    883.920301   0.006477 2026-03-27 17:29:53.948 16836.37  5326.62 A000_QSim__reset_HEAD
    883.921094   0.000793 2026-03-27 17:29:53.949 16776.82  5267.59 A000_SEvt__endIndex
    883.927633   0.006539 2026-03-27 17:29:53.955 16318.14  4809.47 A000_SEvt__EndOfRun
    hitlite/A000_QSim                                     212.823   671.097659            17.449883             0.086843           455.316210   16836.37  5326.62  # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517  # slice=2,max_slot_M=150
      Delta(s)   Δprev(s) DateTime (+08)        VM(MB)  RSS(MB) Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000 2026-03-27 17:15:10.028   736.68   479.40 SEvt__Init_RUN_META
     82.813827  82.813827 2026-03-27 17:16:32.841  6157.19  1287.04 CSGOptiX__Create_HEAD
     93.314976  10.501149 2026-03-27 17:16:43.343  9554.49  1911.96 CSGOptiX__Create_TAIL
    212.531198 119.216222 2026-03-27 17:18:42.559 12118.30  4436.61 junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    212.531279   0.000081 2026-03-27 17:18:42.559 12118.30  4436.61 A000_QSim__simulate_HEAD
    212.531322   0.000043 2026-03-27 17:18:42.559 12118.30  4436.61 A000_SEvt__BeginOfRun
    212.534638   0.003316 2026-03-27 17:18:42.562 12118.30  4436.61 A000_SEvt__beginOfEvent_FIRST_EGPU
    212.534700   0.000062 2026-03-27 17:18:42.562 12118.30  4436.61 A000_SEvt__setIndex
    212.737948   0.203248 2026-03-27 17:18:42.766 12177.84  4496.13 A000_QSim__simulate_LBEG
    212.737998   0.000050 2026-03-27 17:18:42.766 12177.84  4496.13 A000_QSim__simulate_PRUP
    212.821582   0.083584 2026-03-27 17:18:42.849 22865.84  4496.69 A000_QSim__simulate_PREL
    409.196115 196.374533 2026-03-27 17:21:59.224 22865.84  4501.47 A000_QSim__simulate_POST
    413.856673   4.660558 2026-03-27 17:22:03.884 24573.36  6209.86 A000_QSim__simulate_DOWN
    413.856725   0.000052 2026-03-27 17:22:03.884 24573.36  6209.86 A000_QSim__simulate_PRUP
    413.861280   0.004555 2026-03-27 17:22:03.889 24573.36  6209.86 A000_QSim__simulate_PREL
    431.431438  17.570158 2026-03-27 17:22:21.459 24573.36  6209.86 A000_QSim__simulate_POST
    431.784346   0.352908 2026-03-27 17:22:21.812 24700.60  6337.10 A000_QSim__simulate_DOWN
    431.784441   0.000095 2026-03-27 17:22:21.812 24700.60  6337.10 A000_QSim__simulate_LEND # slice=2,max_slot_M=150
    436.640508   4.856067 2026-03-27 17:22:26.668 24700.59  6337.09 A000_QSim__simulate_PCAT
    436.640638   0.000130 2026-03-27 17:22:26.668 24700.59  6337.09 A000_QSim__simulate_BRES # numGenstepCollected=650377,numPhotonCollected=162472950,numHit=30060517
    436.640649   0.000011 2026-03-27 17:22:26.668 24700.59  6337.09 A000_QSim__simulate_TAIL
    436.644399   0.003750 2026-03-27 17:22:26.672 24700.59  6337.09 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
    436.644502   0.000103 2026-03-27 17:22:26.672 24700.59  6337.09 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_HEAD
    1003.214551 566.570049 2026-03-27 17:31:53.242 26509.23  8107.82 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_TAIL # hit=30060517,merged=23362273,save=6698244
    1003.214625   0.000074 2026-03-27 17:31:53.242 26509.23  8107.82 A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
    1003.214637   0.000012 2026-03-27 17:31:53.242 26509.23  8107.82 A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    1003.215445   0.000808 2026-03-27 17:31:53.243 26509.23  8110.63 A000_QSim__reset_HEAD
    1003.215903   0.000458 2026-03-27 17:31:53.244 26449.68  8051.14 A000_SEvt__endIndex
    1003.224896   0.008993 2026-03-27 17:31:53.253 24614.93  6216.96 A000_SEvt__EndOfRun
    hit/A000_QSim                                         212.531   790.684166            17.570158             0.352908           566.574796   26509.23  8110.63  # numGenstepCollected=650377,numPhotonCollected=162472



Issue 1 : max_slot M150 causing splitting and borking timing comparison
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    2026-03-30 11:41:20.402 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    5423 2026-03-30 11:41:20.405 ERROR [605381] [SEvt::addGenstep@2397]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this  
    5424 2026-03-30 11:41:20.590 INFO  [605381] [QSim::simulate@465]  eventID      0 igs (650377, 6, 4, ) tot_ph_0 162472950 tot_ph_0/M 162 xxl YES MaxSlot 150000000 MaxSlot/M 150 sslice::Desc(igs_slice)
    5425 sslice::Desc num_slice 2 TotalPhoton  162472950 TotalPhoton/M 162.472950
    5426                   start    stop     offset      count    count/M 
    5427    0 : sslice {       0,  598380,         0, 149999934}149.999934
    5428    1 : sslice {  598380,  650377, 149999934,  12473016} 12.473016
    5429                   start    stop     offset      count    count/M 
    5430  num_slice 2
    5431 //qcerenkov::wavelength_sampled_bndtex idx 5106033 sampledRI



Issue 2 : is there contention ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    U[blyth@lxlogin004 oj]$ ojq
                 JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
             3123874_0       gpu oj_doubl    blyth  R       8:06      1 gpu015
             3123874_1       gpu oj_doubl    blyth  R       8:06      1 gpu015
             3123874_2       gpu oj_doubl    blyth  R       8:06      1 gpu016
             3123874_3       gpu oj_doubl    blyth  R       8:06      1 gpu016



