review_scripts
=================

Overview
---------

This area contains initial development of scripts comparing
various ways to do detsim level simulation of double muons
based off original scripts from Zhenning.

In order to automate such comparisons in future
are trying to reproduce this as the "doublemuon"
TESTGROUP used by the ojt/ojtt ~/j/local.sh machinery.


Primary Scripts
----------------


detsim2.sh
   invokes detsim.sh with subshells for 2 TEST : hit hitlite

detsim4.sh
   invokes detsim.sh with subshells for 4 TEST : hit hitmerged hitlite hitlitemerged

detsim.sh
   tut_detsim.py runner with log and output file placement controls

genmuon.sh
    uses Muon.exe to generate a small double muon input file

double_muon_group17.sh
    slurm script from Zhenning which I used to extract much of
    the commandline options used in detsim.sh and genmuon.sh



Reproduce presented numbers
-----------------------------


Following some script improvements, reproducing the presented numbers from the SProf.txt profile files is automatic::

    A[blyth@localhost detsim]$ T0="2025-12-04 16:00" T1="2025-12-04 18:00" ~/o/bin/SProf.sh proi
    Identity                                             Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)    Sub TAIL→RESET(s)    VM(MB)  RSS(MB)  Comment
    ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    hit/A000_QSim                                         106.466   215.560469            22.996241             1.949322           190.446287   32168.83  7971.96  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    hitlite/A000_QSim                                     106.462   170.226838            23.108319             0.484299           146.471936   32499.61  5361.86  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
    hitlitemerged/A000_QSim                               107.263    23.835564            23.097717             0.181023             0.404235   87284.29  4988.84  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
    hitmerged/A000_QSim                                   106.770    30.400825            22.988498             0.543559             6.713401   88292.85  6634.07  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029  # slice=1,max_slot_M=150






Logs with SProf.txt 
--------------------
::

    A[blyth@localhost opticks]$ cd /data1/blyth/tmp/j/zhenning_double_muon/detsim/
    A[blyth@localhost detsim]$ l
    total 108
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  5 11:49 OJ_LOCAL_Dec04_ok0_hitlite_seed42_evtmax1_run
    4 drwxr-xr-x. 27 blyth blyth 4096 Dec  5 09:52 .
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  5 00:55 OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 22:36 J25_6_0_ok1_hitlite_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 22:33 J25_6_0_ok1_hit_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 17:13 OJ_LOCAL_Dec04_ok1_hitmerged_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 16:57 OJ_LOCAL_Dec04_ok1_hitlitemerged_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 16:57 OJ_LOCAL_Dec04_ok1_hit_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 16:57 OJ_LOCAL_Dec04_ok1_hitlite_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:24 OJ_LOCAL_Dec03_ok1_hitlite_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:24 OJ_LOCAL_Dec03_ok1_hitmerged_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:22 OJ_LOCAL_Dec03_ok1_hitlitemerged_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Dec03_ok1_hit_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov25_ok0_hit2_merge1_seed42_evtmax1
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov26_ok0_hit2_merge1_seed42_evtmax1_db2
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov25_ok0_hit2_merge1_seed42_evtmax1_run
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov27_ok0_hit2_merge1_seed42_evtmax1_db1
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov26_ok0_hit2_merge1_seed42_evtmax1_db1
    4 drwxr-xr-x.  2 blyth blyth 4096 Dec  4 15:13 OJ_LOCAL_Nov25_ok0_hit2_merge1_seed42_evtmax1_db1
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 23:19 OJ_LOCAL_Nov24_ok0_hit2_merge1_seed42_evtmax1
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 20:36 OJ_LOCAL_Nov24_ok1_hit2_merge1_seed42_evtmax1
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 17:01 OJ_Nov21
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 17:01 J25_6_0
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 17:01 OJ_LOCAL_Nov24_hit2_merge1_seed42_evtmax1
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 17:01 OJ_Nov21_type1
    4 drwxr-xr-x.  2 blyth blyth 4096 Nov 24 16:12 J25_6_0_hit2_merge1_seed42_evtmax1
    4 drwxr-xr-x.  3 blyth blyth 4096 Nov 21 20:27 ..



