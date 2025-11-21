zhenning_double_muon
=====================


::

    A[blyth@localhost j]$ ~/j/zhenning_double_muon/detsim.sh prof

    → /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_Nov21_type1/SProf.txt
      Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000  2025-11-21 09:33:24.351   1021.46    492.48  SEvt__Init_RUN_META
     29.910277  29.910277  2025-11-21 09:33:54.261   6392.31   1367.20  CSGOptiX__Create_HEAD
     31.074642   1.164365  2025-11-21 09:33:55.425   8507.83   1957.64  CSGOptiX__Create_TAIL
    105.959381  74.884739  2025-11-21 09:35:10.310  11070.82   4531.71  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    105.959463   0.000082  2025-11-21 09:35:10.310  11070.82   4531.71  A000_QSim__simulate_HEAD
    105.959495   0.000032  2025-11-21 09:35:10.310  11070.82   4531.71  A000_SEvt__BeginOfRun
    105.959614   0.000119  2025-11-21 09:35:10.310  11070.82   4531.71  A000_SEvt__beginOfEvent_FIRST_EGPU
    105.959638   0.000024  2025-11-21 09:35:10.310  11070.82   4531.71  A000_SEvt__setIndex
    106.041314   0.081676  2025-11-21 09:35:10.392  11124.29   4584.93  A000_QSim__simulate_LBEG
    106.041346   0.000032  2025-11-21 09:35:10.392  11124.29   4584.93  A000_QSim__simulate_PRUP
    106.096336   0.054990  2025-11-21 09:35:10.447  28756.29   4585.36  A000_QSim__simulate_PREL
    129.069087  22.972751  2025-11-21 09:35:33.420  28756.29   4589.74  A000_QSim__simulate_POST
    130.881841   1.812754  2025-11-21 09:35:35.232  30433.04   6267.61  A000_QSim__simulate_DOWN
    130.881886   0.000045  2025-11-21 09:35:35.232  30433.04   6267.61  A000_QSim__simulate_LEND
    130.881907   0.000021  2025-11-21 09:35:35.232  30433.04   6267.61  A000_QSim__simulate_PCAT
    130.881952   0.000045  2025-11-21 09:35:35.232  30433.04   6267.61  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    130.881958   0.000006  2025-11-21 09:35:35.232  30433.04   6267.61  A000_QSim__simulate_TAIL
    130.882164   0.000206  2025-11-21 09:35:35.233  30433.04   6267.61  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectNormHits_HEAD
    361.986401 231.104237  2025-11-21 09:39:26.337  32167.43   7986.68  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectNormHits_TAIL
    361.986489   0.000088  2025-11-21 09:39:26.337  32167.43   7986.68  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    361.986933   0.000444  2025-11-21 09:39:26.337  32167.43   7986.68  A000_QSim__reset_HEAD
    361.987260   0.000327  2025-11-21 09:39:26.338  32113.96   7933.31  A000_SEvt__endIndex
    361.991311   0.004051  2025-11-21 09:39:26.342  30437.21   6256.55  A000_SEvt__EndOfRun

    362-129 = 233   ## WHERE DOES INIT END ?
    362-106 = 256


    → /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_Nov21/SProf.txt
      Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
    --------------------------------------------------------------------------------------------
      0.000000   0.000000  2025-11-21 12:36:48.201   1021.45    495.26  SEvt__Init_RUN_META
     29.526024  29.526024  2025-11-21 12:37:17.727   6392.32   1370.30  CSGOptiX__Create_HEAD
     30.625968   1.099944  2025-11-21 12:37:18.827   8507.21   1956.85  CSGOptiX__Create_TAIL
    105.704191  75.078223  2025-11-21 12:38:33.905  11070.20   4530.69  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
    105.704275   0.000084  2025-11-21 12:38:33.905  11070.20   4530.69  A000_QSim__simulate_HEAD
    105.704308   0.000033  2025-11-21 12:38:33.906  11070.20   4530.69  A000_SEvt__BeginOfRun
    105.704429   0.000121  2025-11-21 12:38:33.906  11070.20   4530.69  A000_SEvt__beginOfEvent_FIRST_EGPU
    105.704454   0.000025  2025-11-21 12:38:33.906  11070.20   4530.69  A000_SEvt__setIndex
    105.778959   0.074505  2025-11-21 12:38:33.980  11123.66   4583.91  A000_QSim__simulate_LBEG
    105.778994   0.000035  2025-11-21 12:38:33.980  11123.66   4583.91  A000_QSim__simulate_PRUP
    105.824323   0.045329  2025-11-21 12:38:34.026  22451.66   4584.34  A000_QSim__simulate_PREL
    128.803983  22.979660  2025-11-21 12:38:57.005  22451.66   4589.16  A000_QSim__simulate_POST
    128.974622   0.170639  2025-11-21 12:38:57.176  86965.45   4690.45  A000_QSim__simulate_DOWN
    128.974661   0.000039  2025-11-21 12:38:57.176  86965.45   4690.45  A000_QSim__simulate_LEND
    128.974683   0.000022  2025-11-21 12:38:57.176  86965.45   4690.45  A000_QSim__simulate_PCAT
    128.974727   0.000044  2025-11-21 12:38:57.176  86965.45   4690.45  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
    128.974733   0.000006  2025-11-21 12:38:57.176  86965.45   4690.45  A000_QSim__simulate_TAIL
    128.974917   0.000184  2025-11-21 12:38:57.176  86965.45   4690.45  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
    128.974980   0.000063  2025-11-21 12:38:57.176  86965.45   4690.45  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_HEAD
    129.385055   0.410075  2025-11-21 12:38:57.586  87280.89   4991.67  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_TAIL
    129.385091   0.000036  2025-11-21 12:38:57.586  87280.89   4991.67  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
    129.385097   0.000006  2025-11-21 12:38:57.586  87280.89   4991.67  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
    129.385562   0.000465  2025-11-21 12:38:57.587  87281.02   4991.67  A000_QSim__reset_HEAD
    129.385854   0.000292  2025-11-21 12:38:57.587  87227.55   4938.33  A000_SEvt__endIndex
    129.386519   0.000665  2025-11-21 12:38:57.588  87129.76   4840.53  A000_SEvt__EndOfRun
    A[blyth@localhost j]$



HMM : "hitlitemerged" looks to be "10x" (depends where to draw line between init and events) compared to "hit"
----------------------------------------------------------------------------------------------------------------

* TODO: add some more SProf profile points so can see more clearly where init ends and event begins
* TODO: how to get some insight into vanilla running ?

::

    In [2]: 362-106
    Out[2]: 256

    In [3]: 129-106
    Out[3]: 23

    In [4]: 256/23
    Out[4]: 11.130434782608695



