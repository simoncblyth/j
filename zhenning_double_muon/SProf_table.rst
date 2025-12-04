


Timings for one double muon event, ~150M photons, 28M hit, 6.4M mergedHit [28/6.4=4.3]


+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
| [seconds]       |   Method                   | Collect+(CPUMerge) |   Kernel Time   | Download+(GPUMerge)  | Total (no-init)    |
|                 |                            |                    |   PREL:POST     |   POST:DOWN          |                    |
+=================+============================+====================+=================+======================+====================+
|  hit            |  CollectFullHits_cpumerged | 190.445588         |  22.996241      |   1.949322           |  215.560469        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitmerged      |  CollectFullHits_premerged |  6.712759   (x28)  |  22.988498      |   0.543559   (x3.5)  |   30.400825        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitlite        |  CollectMuonHits_cpumerge  | 146.471113         |  23.108319      |   0.484299           |  170.226838        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitlitemerged  |  CollectMuonHits_premerged |   0.403599 (x366)  |  23.097717      |   0.181023   (x2.6)  |   23.835564        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+


* no significant kernel time differences
* huge reduction in hit collection time (x28,x366) by merging hits on GPU [2.5min -> 0.4 seconds]
* significant reductions in download overheads by merging hits on GPU

GPU hit merging doubly beneficial:

1. reduced overhead, as less to download from GPU
2. almost eliminates CPU post processing for "hitlitemerged"









→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hit_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.466   215.560469        22.996241 (PREL→POST)         1.949322 (POST→DOWN) 32168.83  7971.96  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlite_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.462   170.226838        23.108319 (PREL→POST)         0.484299 (POST→DOWN) 32499.61  5361.86  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlitemerged_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  107.263    23.835564        23.097717 (PREL→POST)         0.181023 (POST→DOWN) 87284.29  4988.84  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitmerged_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.770    30.400825        22.988498 (PREL→POST)         0.543559 (POST→DOWN) 88292.85  6634.07  # slice=1,max_slot_M=150
A[blyth@localhost zhenning_double_muon]$ 













A[blyth@localhost j]$ T0="2025-12-04 16:00" zhenning_double_muon/detsim.sh prof
                            t0 : 120 minutes ago
                            T0 : 2025-12-04 16:00
                            mt : 2025-12-04 16:00:00
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hit_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:07:25.334   1024.60    493.44  SEvt__Init_RUN_META
 30.755473  30.755473  2025-12-04 16:07:56.090   6394.04   1368.74  CSGOptiX__Create_HEAD
 32.047164   1.291691  2025-12-04 16:07:57.382   8509.56   1955.52  CSGOptiX__Create_TAIL
106.465519  74.418355  2025-12-04 16:09:11.800  11099.55   4542.50  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.465588   0.000069  2025-12-04 16:09:11.800  11099.55   4542.50  A000_QSim__simulate_HEAD
106.465623   0.000035  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__BeginOfRun
106.465743   0.000120  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__beginOfEvent_FIRST_EGPU
106.465769   0.000026  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__setIndex
106.571435   0.105666  2025-12-04 16:09:11.906  11153.01   4595.72  A000_QSim__simulate_LBEG
106.571472   0.000037  2025-12-04 16:09:11.906  11153.01   4595.72  A000_QSim__simulate_PRUP
106.634089   0.062617  2025-12-04 16:09:11.969  28785.01   4596.59  A000_QSim__simulate_PREL
129.630330  22.996241  2025-12-04 16:09:34.965  28785.01   4601.41  A000_QSim__simulate_POST
131.579652   1.949322  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_DOWN
131.579698   0.000046  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_LEND
131.579721   0.000023  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_PCAT
131.579765   0.000044  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
131.579770   0.000005  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_TAIL
131.579950   0.000180  2025-12-04 16:09:36.914  30461.76   6279.35  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
131.580014   0.000064  2025-12-04 16:09:36.914  30461.76   6279.35  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_HEAD
322.025602 190.445588  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_TAIL # hit=27471928,merged=21062899,save=6409029
322.025669   0.000067  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
322.025677   0.000008  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
322.026057   0.000380  2025-12-04 16:12:47.360  32168.83   7971.96  A000_QSim__reset_HEAD
322.026391   0.000334  2025-12-04 16:12:47.361  32115.37   7918.59  A000_SEvt__endIndex
322.030447   0.004056  2025-12-04 16:12:47.365  30438.62   6241.84  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlite_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:15:54.245   1023.13    496.45  SEvt__Init_RUN_META
 29.961488  29.961488  2025-12-04 16:16:24.206   6393.96   1375.03  CSGOptiX__Create_HEAD
 31.212086   1.250598  2025-12-04 16:16:25.457   8509.47   1960.28  CSGOptiX__Create_TAIL
106.462371  75.250285  2025-12-04 16:17:40.707  11099.45   4545.73  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.462438   0.000067  2025-12-04 16:17:40.707  11099.45   4545.73  A000_QSim__simulate_HEAD
106.462471   0.000033  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__BeginOfRun
106.462645   0.000174  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__beginOfEvent_FIRST_EGPU
106.462671   0.000026  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__setIndex
106.561261   0.098590  2025-12-04 16:17:40.806  11152.91   4598.96  A000_QSim__simulate_LBEG
106.561297   0.000036  2025-12-04 16:17:40.806  11152.91   4598.96  A000_QSim__simulate_PRUP
106.624614   0.063317  2025-12-04 16:17:40.869  31728.91   4599.39  A000_QSim__simulate_PREL
129.732933  23.108319  2025-12-04 16:18:03.977  31728.91   4604.21  A000_QSim__simulate_POST
130.217232   0.484299  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_DOWN
130.217271   0.000039  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_LEND
130.217293   0.000022  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_PCAT
130.217334   0.000041  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
130.217340   0.000006  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_TAIL
130.217641   0.000301  2025-12-04 16:18:04.462  32148.10   5024.47  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
130.217711   0.000070  2025-12-04 16:18:04.462  32148.10   5024.47  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_HEAD
276.688824 146.471113  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_TAIL # hit=27471928,merged=21062899,save=6409029
276.688881   0.000057  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
276.688888   0.000007  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
276.689276   0.000388  2025-12-04 16:20:30.934  32499.61   5361.86  A000_QSim__reset_HEAD
276.689602   0.000326  2025-12-04 16:20:30.934  32446.15   5308.67  A000_SEvt__endIndex
276.691025   0.001423  2025-12-04 16:20:30.936  32026.96   4889.48  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlitemerged_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:20:53.651   1023.25    495.63  SEvt__Init_RUN_META
 30.937038  30.937038  2025-12-04 16:21:24.588   6394.08   1377.59  CSGOptiX__Create_HEAD
 32.213934   1.276896  2025-12-04 16:21:25.865   8509.61   1965.09  CSGOptiX__Create_TAIL
107.262853  75.048919  2025-12-04 16:22:40.913  11099.59   4552.83  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
107.262921   0.000068  2025-12-04 16:22:40.913  11099.59   4552.83  A000_QSim__simulate_HEAD
107.262955   0.000034  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__BeginOfRun
107.263078   0.000123  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__beginOfEvent_FIRST_EGPU
107.263104   0.000026  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__setIndex
107.367226   0.104122  2025-12-04 16:22:41.018  11153.05   4606.05  A000_QSim__simulate_LBEG
107.367261   0.000035  2025-12-04 16:22:41.018  11153.05   4606.05  A000_QSim__simulate_PRUP
107.415403   0.048142  2025-12-04 16:22:41.066  22481.05   4606.93  A000_QSim__simulate_PREL
130.513120  23.097717  2025-12-04 16:23:04.164  22481.05   4611.74  A000_QSim__simulate_POST
130.694143   0.181023  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_DOWN
130.694182   0.000039  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_LEND
130.694203   0.000021  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_PCAT
130.694244   0.000041  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
130.694250   0.000006  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_TAIL
130.694408   0.000158  2025-12-04 16:23:04.345  86994.84   4713.71  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
130.694467   0.000059  2025-12-04 16:23:04.345  86994.84   4713.71  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_HEAD
131.098066   0.403599  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_TAIL # hit=6409029
131.098102   0.000036  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
131.098108   0.000006  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
131.098485   0.000377  2025-12-04 16:23:04.749  87284.29   4988.84  A000_QSim__reset_HEAD
131.098769   0.000284  2025-12-04 16:23:04.749  87230.82   4935.50  A000_SEvt__endIndex
131.099464   0.000695  2025-12-04 16:23:04.750  87133.03   4837.70  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitmerged_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 17:11:37.343   1023.01    492.82  SEvt__Init_RUN_META
 29.918053  29.918053  2025-12-04 17:12:07.262   6393.87   1376.53  CSGOptiX__Create_HEAD
 31.164170   1.246117  2025-12-04 17:12:08.508   8509.39   1964.82  CSGOptiX__Create_TAIL
106.770381  75.606211  2025-12-04 17:13:24.114  11099.38   4550.71  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.770446   0.000065  2025-12-04 17:13:24.114  11099.38   4550.71  A000_QSim__simulate_HEAD
106.770477   0.000031  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__BeginOfRun
106.770616   0.000139  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__beginOfEvent_FIRST_EGPU
106.770643   0.000027  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__setIndex
106.877424   0.106781  2025-12-04 17:13:24.221  11152.84   4603.94  A000_QSim__simulate_LBEG
106.877463   0.000039  2025-12-04 17:13:24.221  11152.84   4603.94  A000_QSim__simulate_PRUP
106.925702   0.048239  2025-12-04 17:13:24.269  21840.84   4604.38  A000_QSim__simulate_PREL
129.914200  22.988498  2025-12-04 17:13:47.258  21840.84   4608.75  A000_QSim__simulate_POST
130.457759   0.543559  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_DOWN
130.457808   0.000049  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_LEND # slice=1,max_slot_M=150
130.457829   0.000021  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_PCAT
130.457865   0.000036  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
130.457870   0.000005  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_TAIL
130.458047   0.000177  2025-12-04 17:13:47.802  86648.02   5004.11  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
130.458106   0.000059  2025-12-04 17:13:47.802  86648.02   5004.11  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_HEAD
137.170865   6.712759  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_TAIL # hit=6409029
137.170900   0.000035  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
137.170909   0.000009  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
137.171271   0.000362  2025-12-04 17:13:54.515  88292.85   6634.07  A000_QSim__reset_HEAD
137.171567   0.000296  2025-12-04 17:13:54.515  88239.39   6580.73  A000_SEvt__endIndex
137.172888   0.001321  2025-12-04 17:13:54.516  87848.21   6189.55  A000_SEvt__EndOfRun
A[blyth@localhost j]$ 
A[blyth@localhost j]$ 



