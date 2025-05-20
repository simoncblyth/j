InputPhotonsCheck
==================


At 10k input photon targetting single PMT, no issues::

    ## config input photon running
    export SEvt__INPUT_PHOTON_DIR=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
    export OPTICKS_INPUT_PHOTON=RainXZ_Z230_10k_f8.npy
    export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000


::

    ] envset Thu May 8 02:47:15 PM CST 2025
    /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox
             BASH_SOURCE :  /home/blyth/j/InputPhotonsCheck/InputPhotonsCheck.sh
                  defarg :  env_info_run_ana
                     arg :  env_info_chi2
                     TMP :  /tmp/blyth/opticks
                    GEOM :  J25_3_0_Opticks_v0_4_1
                  LOGDIR :  /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox
                   AFOLD :  /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000
                   BFOLD :  /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_Opticks_v0_4_1
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              FOLD : /tmp/blyth/opticks/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : A000 
                             BFOLD : B000 
    a_path $AFOLD/seq.npy A000/seq.npy a_seq (10000, 2, 2, )
    b_path $BFOLD/seq.npy B000/seq.npy b_seq (10000, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u_size 1708 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum    14.7866 ndf 25.0000 sum/ndf     0.5915 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SD                                                                                :    3529   3539 :     0.0141 : Y :       0      5 :   
        TO BT BT BT BT SA                                                                                :    2601   2566 :     0.2371 : Y :       2      1 :   
        TO BT BT BT BT BT SR SA                                                                          :     612    629 :     0.2329 : Y :    1126   1038 :   
        TO BT BT BT BT BT SA                                                                             :     480    477 :     0.0094 : Y :     867    880 :   
        TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :     123    103 :     1.7699 : Y :    1049   1755 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :     111     96 :     1.0870 : Y :    2130   2101 :   
        TO BT BT AB                                                                                      :     101     85 :     1.3763 : Y :      47    127 :   
        TO BT BT BT BT BT SR BR SA                                                                       :      82     99 :     1.5967 : Y :    2262   2120 :   
        TO BT BT BT BT BT SR SR SA                                                                       :      90     81 :     0.4737 : Y :    1037   1063 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                     :      63     68 :     0.1908 : Y :    2306   2027 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                     :      61     65 :     0.1270 : Y :     804    932 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :      57     54 :     0.0811 : Y :     926    910 :   
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :      52     53 :     0.0095 : Y :    1072   1201 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                         :      41     45 :     0.1860 : Y :    1317   1182 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                         :      43     36 :     0.6203 : Y :    1889   1656 :   
        TO BT BT BT BT BT SR SR SR SA                                                                    :      40     34 :     0.4865 : Y :    1093   1107 :   
        TO BT BT BT BT AB                                                                                :      40     35 :     0.3333 : Y :     199     21 :   
        TO BT BT BT BT BT SR BR SR SR SA                                                                 :      35     38 :     0.1233 : Y :    2295   2287 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                      :      35     32 :     0.1343 : Y :    1780   1645 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                   :      33     25 :     1.1034 : Y :    2457   2337 :   
        TO BT BT BT BT BR BT BT BT BT BT SA                                                              :      22     33 :     2.2000 : Y :      84     70 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :      28     33 :     0.4098 : Y :       6      0 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                        :      32     25 :     0.8596 : Y :    2378   1179 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                      :      26     29 :     0.1636 : Y :    1776   1999 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                :      29     22 :     0.9608 : Y :    2399   2474 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SD                                                           :      14     25 :     0.0000 : N :     551    515 : C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                   :      23     17 :     0.0000 : N :    2557  



Push up the stats::

    A[blyth@localhost InputPhotons]$ l RainXZ_Z230_*_f8.npy
       126 -rw-r--r--. 1 cvmfs cvmfs    128128 Aug 29  2024 RainXZ_Z230_1000_f8.npy
        13 -rw-r--r--. 1 cvmfs cvmfs     12928 Aug 29  2024 RainXZ_Z230_100_f8.npy
     12501 -rw-r--r--. 1 cvmfs cvmfs  12800128 Aug 29  2024 RainXZ_Z230_100k_f8.npy
      1251 -rw-r--r--. 1 cvmfs cvmfs   1280128 Aug 29  2024 RainXZ_Z230_10k_f8.npy
    125001 -rw-r--r--. 1 cvmfs cvmfs 128000128 Aug 29  2024 RainXZ_Z230_1M_f8.npy
       126 -rw-r--r--. 1 cvmfs cvmfs    128128 Aug 29  2024 RainXZ_Z230_X700_1000_f8.npy
        13 -rw-r--r--. 1 cvmfs cvmfs     12928 Aug 29  2024 RainXZ_Z230_X700_100_f8.npy
      1251 -rw-r--r--. 1 cvmfs cvmfs   1280128 Aug 29  2024 RainXZ_Z230_X700_10k_f8.npy





1M level shows one deviant::

    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_Opticks_v0_4_1
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              FOLD : /tmp/blyth/opticks/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000 
                             BFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000 
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000/seq.npy a_seq (1000000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000/seq.npy b_seq (1000000, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1227.2949 ndf 859.0000 sum/ndf     1.4287 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SD                                                                                :  356885 357488 :     0.5090 : Y :       0      5 :   
        TO BT BT BT BT SA                                                                                :  255653 256646 :     1.9248 : Y :       2      0 :   
        TO BT BT BT BT BT SR SA                                                                          :   63147  62781 :     1.0638 : Y :  103587 103558 :   
        TO BT BT BT BT BT SA                                                                             :   47129  46746 :     1.5626 : Y :   83494  85319 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :   11875  11701 :     1.2842 : Y :  209959 209806 :   
    :r:`TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :   10673  10028 :    20.0969 : Y :   47733  41206 : DEVIANT  `
        TO BT BT BT BT BT SR BR SA                                                                       :    9626   9635 :     0.0042 : Y :  201988 202019 :   
        TO BT BT BT BT BT SR SR SA                                                                       :    9185   9013 :     1.6257 : Y :  103570 103692 :   
        TO BT BT AB                                                                                      :    8706   8470 :     3.2427 : Y :      47    346 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                     :    6173   6240 :     0.3616 : Y :  202359 203005 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                     :    5852   5815 :     0.1173 : Y :   79688  79686 :   
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :    5081   5133 :     0.2647 : Y :    2399   2284 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :    4662   4746 :     0.7500 : Y :   73002  90925 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                         :    4208   4150 :     0.4025 : Y :  115560 115602 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                      :    4100   4050 :     0.3067 : Y :  161586 161681 :   
        TO BT BT BT BT BT SR SR SR SA                                                                    :    3783   3804 :     0.0581 : Y :  103559 103554 :   
        TO BT BT BT BT BT SR BR SR SR SA                                                                 :    3492   3459 :     0.1567 : Y :  209806 209811 :   
        TO BT BT BT BT AB                                                                                :    3394   3353 :     0.2491 : Y :     199    174 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                         :    3270   3227 :     0.2846 : Y :  115605 115560 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                      :    3127   3249 :     2.3344 : Y :  162042 161477 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                        :    3083   3035 :     0.3766 : Y :  161794 163817 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                   :    2741   2632 :     2.2112 : Y :  233152 233189 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                :    2523   2608 :     1.4081 : Y :  233371 233345 :   
        TO BT BT BT BT BR BT BT BT BT BT SA                                                              :    2339   2354 :     0.0479 : Y :    6691   6667 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                   :    2143   2127 :     0.0600 : Y :  233404 233135 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                :    2076   1965 :     3.0490 : Y :  233451 233178 :   
        TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :    1955   2070 :     3.2857 : Y :  218156 210569 :   
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC AB                                                  :    2012   2028 :     0.0634 : Y :  233260 233162 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    1936   1958 :     0.1243 : Y :       6     12 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SD                                                           :    1899   1924 :     0.1635 : Y :   50395  50401 :   
        TO BT BT BT BT BT SR BR SR BR SR SA                                                              :    1698   1731 :     0.3176 : Y :  210255 210222 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD                                   :    1342   1295 :     0.8377 : Y :  161888 161864 :   
        TO AB                                                                                            :    1302   1326 :     0.2192 : Y :      25    233 :   
        TO BT BT BT BT BR BT BT BT BT BT AB                                                              :    1181   1125 :     1.3599 : Y :   28909  74910 :   
        TO BT BT BT BT BT SR BR SR BR SA                                                                 :    1164   1142 :     0.2099 : Y :  210325 210705 :   
        TO BT BT BT BR BT BT BT BT SA                                                                    :    1151   1110 :     0.7435 : Y :       4      3 :   
        TO BT BT BT BT BT SR SR BR SA                                                                    :    1132   1070 :     1.7457 : Y :  170569 170579 :   
        TO BT BT BT BT BT SR SR SR BR SA                                                                 :    1040   1101 :     1.7380 : Y :  122029 121897 :   
        TO BT BT BR BT BT BT SA                                                                          :    1100   1026 :     2.5757 : Y :      16     20 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SA                                   :    1059   1043 :     0.1218 : Y :  164395 164568 :   
    ]sseq_index_ab::desc


    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 40 num 40 opt AZERO mode 1
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 40 num 40 opt BZERO mode 2
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 40 num 40 opt DEVIANT mode 5
    :r:`TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :   10673  10028 :    20.0969 : Y :   47733  41206 : DEVIANT  `
    ]sseq_index_ab::desc






::

    A[blyth@localhost InputPhotonsCheck]$ source ~/j/InputPhotonsCheck/InputPhotonsCheck.sh pdb
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: Put a ';' at the end of a line to suppress the printing of output.
    [from opticks.ana.p import * 
    [ana/p.py:from opticks.CSG.CSGFoundry import CSGFoundry 
    ]ana/p.py:from opticks.CSG.CSGFoundry import CSGFoundry 
    [ana/p.py:cf = CSGFoundry.Load()
    CSGFoundry.CFBase returning [/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_Opticks_v0_4_1], note:[via GEOM,J25_3_0_Opticks_v0_4_1_CFBaseFromGEOM] 
    ]ana/p.py:cf = CSGFoundry.Load()
    ]from opticks.ana.p import * 
    INST_FRAME -1 : using default sframe saved with the sevt
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$AFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol a pid -1 opt  off [0. 0. 0.] 
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$BFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000 
    [--- ab = SAB(a,b) ----
    INFO:opticks.ana.pvplt:[
    INFO:opticks.ana.qcf:QCF.__init__ qcf.aqu 
    INFO:opticks.ana.qcf:QCF.__init__ qcf.bqu 
    INFO:opticks.ana.qcf:QCF.__init__ ] qu loop
    INFO:opticks.ana.pvplt:]
    ]--- ab = SAB(a,b) ----
    [----- repr(ab) 
    sli: slice(None, 40, None) 
    SAB
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000 
    a

    CMDLINE:/home/blyth/j/InputPhotonsCheck/oj3ana.py
    a.base:/tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/A000

      : a.genstep                                          :            (1, 6, 4) : 0:29:51.403784 
      : a.photon                                           :      (1000000, 4, 4) : 0:29:51.403784 
      : a.record                                           :  (1000000, 32, 4, 4) : 0:29:51.258784 
      : a.record_meta                                      :                    1 : 0:29:50.715784 
      : a.seq                                              :      (1000000, 2, 2) : 0:29:50.314785 
      : a.hit                                              :       (405237, 4, 4) : 0:29:50.303785 
      : a.domain                                           :            (2, 4, 4) : 0:29:50.293785 
      : a.inphoton                                         :      (1000000, 4, 4) : 0:29:50.293785 
      : a.seqnib                                           :           (1000000,) : 0:29:50.271785 
      : a.seqnib_table                                     :              (33, 1) : 0:29:50.270785 
      : a.NPFold_index                                     :                 (9,) : 0:29:50.270785 
      : a.NPFold_meta                                      :                   25 : 0:29:50.270785 
      : a.NPFold_names                                     :                 (0,) : 0:29:50.270785 
      : a.sframe                                           :            (4, 4, 4) : 0:29:50.270785 
      : a.sframe_meta                                      :                    5 : 0:29:50.270785 

     min_stamp : 2025-05-08 15:17:22.986575 
     max_stamp : 2025-05-08 15:17:24.119574 
     dif_stamp : 0:00:01.132999 
     age_stamp : 0:29:50.270785 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000 
    b

    CMDLINE:/home/blyth/j/InputPhotonsCheck/oj3ana.py
    b.base:/tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox/B000

      : b.genstep                                          :            (1, 6, 4) : 0:29:55.201012 
      : b.photon                                           :      (1000000, 4, 4) : 0:29:55.200012 
      : b.record                                           :  (1000000, 32, 4, 4) : 0:29:55.171012 
      : b.record_meta                                      :                    1 : 0:29:54.628012 
      : b.seq                                              :      (1000000, 2, 2) : 0:29:54.214013 
      : b.hit                                              :       (410016, 4, 4) : 0:29:54.205013 
      : b.domain                                           :            (2, 4, 4) : 0:29:54.198013 
      : b.inphoton                                         :      (1000000, 4, 4) : 0:29:54.197012 
      : b.seqnib                                           :           (1000000,) : 0:29:54.178013 
      : b.seqnib_table                                     :              (33, 1) : 0:29:54.177012 
      : b.NPFold_index                                     :                 (9,) : 0:29:54.177012 
      : b.NPFold_meta                                      :                   54 : 0:29:54.177012 
      : b.NPFold_names                                     :                 (0,) : 0:29:54.176013 
      : b.sframe                                           :            (4, 4, 4) : 0:29:54.176013 
      : b.sframe_meta                                      :                    5 : 0:29:54.176013 

     min_stamp : 2025-05-08 15:17:19.189577 
     max_stamp : 2025-05-08 15:17:20.214576 
     dif_stamp : 0:00:01.024999 
     age_stamp : 0:29:54.176013 
    ab.qcf.aqu
    qcf.aqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'356885' b'0' b'TO BT BT BT BT SD                                                                               ']
     [b'255653' b'2' b'TO BT BT BT BT SA                                                                               ']
     [b'63147' b'103587' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'47129' b'83494' b'TO BT BT BT BT BT SA                                                                            ']
     [b'11875' b'209959' b'TO BT BT BT BT BT SR BR SR SA                                                                   ']
     [b'10673' b'47733' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'9626' b'201988' b'TO BT BT BT BT BT SR BR SA                                                                      ']
     [b'9185' b'103570' b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'8706' b'47' b'TO BT BT AB                                                                                     ']
     [b'6173' b'202359' b'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                    ']]
    ab.qcf.bqu
    qcf.bqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'357488' b'5' b'TO BT BT BT BT SD                                                                               ']
     [b'256646' b'0' b'TO BT BT BT BT SA                                                                               ']
     [b'62781' b'103558' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'46746' b'85319' b'TO BT BT BT BT BT SA                                                                            ']
     [b'11701' b'209806' b'TO BT BT BT BT BT SR BR SR SA                                                                   ']
     [b'10028' b'41206' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'9635' b'202019' b'TO BT BT BT BT BT SR BR SA                                                                      ']
     [b'9013' b'103692' b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'8470' b'346' b'TO BT BT AB                                                                                     ']
     [b'6240' b'203005' b'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                    ']]
    a.CHECK :  
    b.CHECK :  
    ab.qcf[:40]
    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum :  1694.8748 c2n :  1105.0000 c2per:     1.5338  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  1694.87/1105:1.534 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '356885 357488' ' 0.5090' '     0      5']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '255653 256646' ' 1.9248' '     2      0']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' ' 63147  62781' ' 1.0638' '103587 103558']
     [' 3' 'TO BT BT BT BT BT SA                                                                           ' ' 3' ' 47129  46746' ' 1.5626' ' 83494  85319']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 4' ' 11875  11701' ' 1.2842' '209959 209806']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' ' 10673  10028' '20.0969' ' 47733  41206']
     [' 6' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 6' '  9626   9635' ' 0.0042' '201988 202019']
     [' 7' 'TO BT BT BT BT BT SR SR SA                                                                     ' ' 7' '  9185   9013' ' 1.6257' '103570 103692']
     [' 8' 'TO BT BT AB                                                                                    ' ' 8' '  8706   8470' ' 3.2427' '    47    346']
     [' 9' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                   ' ' 9' '  6173   6240' ' 0.3616' '202359 203005']
     ['10' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '10' '  5852   5815' ' 0.1173' ' 79688  79686']
     ['11' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '11' '  5081   5133' ' 0.2647' '  2399   2284']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '12' '  4662   4746' ' 0.7500' ' 73002  90925']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                       ' '13' '  4208   4150' ' 0.4025' '115560 115602']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                    ' '14' '  4100   4050' ' 0.3067' '161586 161681']
     ['15' 'TO BT BT BT BT BT SR SR SR SA                                                                  ' '15' '  3783   3804' ' 0.0581' '103559 103554']
     ['16' 'TO BT BT BT BT BT SR BR SR SR SA                                                               ' '16' '  3492   3459' ' 0.1567' '209806 209811']
     ['17' 'TO BT BT BT BT AB                                                                              ' '17' '  3394   3353' ' 0.2491' '   199    174']
     ['18' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA                                       ' '18' '  3270   3227' ' 0.2846' '115605 115560']
     ['19' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                    ' '19' '  3127   3249' ' 2.3344' '162042 161477']
     ['20' 'TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                      ' '20' '  3083   3035' ' 0.3766' '161794 163817']
     ['21' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                 ' '21' '  2741   2632' ' 2.2112' '233152 233189']
     ['22' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                              ' '22' '  2523   2608' ' 1.4081' '233371 233345']
     ['23' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '23' '  2339   2354' ' 0.0479' '  6691   6667']
     ['24' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                 ' '24' '  2143   2127' ' 0.0600' '233404 233135']
     ['25' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                              ' '25' '  2076   1965' ' 3.0490' '233451 233178']
     ['26' 'TO BT BT BT BT BT SR BT BT BT BT BT AB                                                         ' '26' '  1955   2070' ' 3.2857' '218156 210569']
     ['27' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC AB                                                ' '27' '  2012   2028' ' 0.0634' '233260 233162']
     ['28' 'TO BT BT BT BT BR BT BT BT BT SA                                                               ' '28' '  1936   1958' ' 0.1243' '     6     12']
     ['29' 'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                         ' '29' '  1899   1924' ' 0.1635' ' 50395  50401']
     ['30' 'TO BT BT BT BT BT SR BR SR BR SR SA                                                            ' '30' '  1698   1731' ' 0.3176' '210255 210222']
     ['31' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD                                 ' '31' '  1342   1295' ' 0.8377' '161888 161864']
     ['32' 'TO AB                                                                                          ' '32' '  1302   1326' ' 0.2192' '    25    233']
     ['33' 'TO BT BT BT BT BR BT BT BT BT BT AB                                                            ' '33' '  1181   1125' ' 1.3599' ' 28909  74910']
     ['34' 'TO BT BT BT BT BT SR BR SR BR SA                                                               ' '34' '  1164   1142' ' 0.2099' '210325 210705']
     ['35' 'TO BT BT BT BR BT BT BT BT SA                                                                  ' '35' '  1151   1110' ' 0.7435' '     4      3']
     ['36' 'TO BT BT BT BT BT SR SR BR SA                                                                  ' '36' '  1132   1070' ' 1.7457' '170569 170579']
     ['37' 'TO BT BT BT BT BT SR SR SR BR SA                                                               ' '37' '  1040   1101' ' 1.7380' '122029 121897']
     ['38' 'TO BT BT BR BT BT BT SA                                                                        ' '38' '  1100   1026' ' 2.5757' '    16     20']
     ['39' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT BT BT SA                                 ' '39' '  1059   1043' ' 0.1218' '164395 164568']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [['339' 'TO BT BT BT BT BR BT BT BT BT BT BT SR SA                                                      ' '339' '    74      0' '74.0000' ' 35337     -1']
     ['369' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SR SA                                                ' '369' '    65      0' '65.0000' '788480     -1']
     ['374' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SR SA                                                ' '374' '    65      0' '65.0000' ' 73030     -1']
     ['707' 'TO BT BR BT BT BT SR SA                                                                        ' '707' '    29      0' ' 0.0000' '  5181     -1']
     ['711' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                                ' '711' '    29      0' ' 0.0000' ' 83174     -1']
     ['788' 'TO BT BT BR BT BT BT BT SR SA                                                                  ' '788' '    26      0' ' 0.0000' ' 19944     -1']
     ['886' 'TO BT BT BT BR BT BT BT BT BT SR SA                                                            ' '886' '    22      0' ' 0.0000' ' 25447     -1']
     ['1413' 'TO BT BT BT BT BT SR AB                                                                        ' '1413' '    13      0' ' 0.0000' '388300     -1']
     ['1439' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BR SA                                             ' '1439' '    13      0' ' 0.0000' '229666     -1']
     ['1467' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BR BT SA                                          ' '1467' '    13      0' ' 0.0000' '229433     -1']
     ['1581' 'TO BT BT BT BT BT SR SR BR BT BT BT BT BT BT BT SR SA                                          ' '1581' '    12      0' ' 0.0000' '175126     -1']
     ['1591' 'TO BT BR BT BT BT BT BT SR SA                                                                  ' '1591' '    12      0' ' 0.0000' ' 50447     -1']
     ['1688' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BR SR SA                                 ' '1688' '    11      0' ' 0.0000' '641533     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    [['507' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BR BT BT SA                                             ' '507' '     0     44' '44.0000' '    -1  73909']
     ['1163' 'TO BT BT BT BT BT SR BT BT BT BT BT BT BT SR SR SR BT BT BT BT BT BT SA                        ' '1163' '     0     17' ' 0.0000' '    -1 788476']
     ['1376' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR BT AB                                    ' '1376' '     0     14' ' 0.0000' '    -1 832043']
     ['1540' 'TO BT BT BT BT BR BT BT BT BT BT BT SR SR SR SR SR BT BT BT BT BT BT SA                        ' '1540' '     0     12' ' 0.0000' '    -1  35675']
     ['1600' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR BT BT BR BT BT BR BT BT BR BT BT BR BT BT' '1600' '     0     12' ' 0.0000' '    -1 832801']
     ['1657' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR AB                                       ' '1657' '     0     11' ' 0.0000' '    -1 831725']]
    ]----- repr(ab) 
    PICK=A MODE=2  ~/j/jtds/jtds.sh 
    INFO:opticks.ana.pvplt:a:sevt has sframe giving _W2M 
    W2M_OVERRIDE (from manual INST_FRAME, no longer typical)
     None
    _W2M(from a.f.sframe.w2m, now standard)
     [[   -0.081    -0.995    -0.055     0.   ]
     [   -0.823     0.098    -0.559     0.   ]
     [    0.562     0.       -0.827     0.   ]
     [   -0.005    -0.    19434.002     1.   ]]
    W2M
     [[   -0.081    -0.995    -0.055     0.   ]
     [   -0.823     0.098    -0.559     0.   ]
     [    0.562     0.       -0.827     0.   ]
     [   -0.005    -0.    19434.002     1.   ]]
    transform gpos (from photon or hit array) to lpos using W2M : ie into target frame : GLOBAL 0 
    transform gpoi (from record array) to lpoi using W2M : ie into target frame : GLOBAL 0 

    In [1]: 




FIXED : AZERO BZERO from pdb not showing in chi2 ? But start of table looks exactly the same ?
------------------------------------------------------------------------------------------------

Probably some different cut ? Work out why in detail by persisting the AB table in a common format from both::

     53 unset sseq_index_ab__desc_NUM_MAX
     54 #export sseq_index_ab__desc_NUM_MAX=40

YEP, problem from handling of NUM_MAX that needs to be different or ignored in AZERO and BZERO modes
to see them all.::

    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 0 num 54363 opt AZERO mode 1
        TO BT BT BT BT BR BT BT BT BT BT BT BT BR BT BT SA                                               :      -1     44 :     0.0000 : N :      -1  73909 : AZERO C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SR SR SR BT BT BT BT BT BT SA                          :      -1     17 :     0.0000 : N :      -1 788476 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR BT AB                                      :      -1     14 :     0.0000 : N :      -1 832043 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR BT BT BR BT BT BR BT BT BR BT BT BR BT BT  :      -1     12 :     0.0000 : N :      -1 832801 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SR SR SR SR SR BT BT BT BT BT BT SA                          :      -1     12 :     0.0000 : N :      -1  35675 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BR AB                                         :      -1     11 :     0.0000 : N :      -1 831725 : AZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 54363 NUM_MAX 0 num 54363 opt BZERO mode 2
        TO BT BT BT BT BR BT BT BT BT BT BT SR SA                                                        :      74     -1 :     0.0000 : N :   35337     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SR SA                                                  :      65     -1 :     0.0000 : N :  788480     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SR SA                                                  :      65     -1 :     0.0000 : N :   73030     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                                  :      29     -1 :     0.0000 : N :   83174     -1 : BZERO C2EXC  
        TO BT BR BT BT BT SR SA                                                                          :      29     -1 :     0.0000 : N :    5181     -1 : BZERO C2EXC  
        TO BT BT BR BT BT BT BT SR SA                                                                    :      26     -1 :     0.0000 : N :   19944     -1 : BZERO C2EXC  
        TO BT BT BT BR BT BT BT BT BT SR SA                                                              :      22     -1 :     0.0000 : N :   25447     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BR BT SA                                            :      13     -1 :     0.0000 : N :  229433     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BR SA                                               :      13     -1 :     0.0000 : N :  229666     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR AB                                                                          :      13     -1 :     0.0000 : N :  388300     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR BR BT BT BT BT BT BT BT SR SA                                            :      12     -1 :     0.0000 : N :  175126     -1 : BZERO C2EXC  
        TO BT BR BT BT BT BT BT SR SA                                                                    :      12     -1 :     0.0000 : N :   50447     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BR SR SA                                   :      11     -1 :     0.0000 : N :  641533     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc



Try RandomSpherical1M from sTarget 
------------------------------------

::

    A[blyth@localhost InputPhotonsCheck]$ ipc chi2
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_Opticks_v0_4_1
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              FOLD : /tmp/blyth/opticks/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox_sTarget_RandomSpherical1M_f8/A000 
                             BFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox_sTarget_RandomSpherical1M_f8/B000 
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox_sTarget_RandomSpherical1M_f8/A000/seq.npy a_seq (1000000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox_sTarget_RandomSpherical1M_f8/B000/seq.npy b_seq (1000000, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u_size 127133 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1897.5539 ndf 1629.0000 sum/ndf     1.1649 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO AB                                                                                            :  111833 112335 :     1.1242 : Y :       0      5 :   
        TO BT BT BT BT BT BT SD                                                                          :  101967 101730 :     0.2757 : Y :      14      3 :   
        TO BT BT BT BT BT BT SA                                                                          :   80729  80729 :     0.0000 : Y :      11      1 :   
        TO SC BT BT BT BT BT BT SD                                                                       :   45851  46377 :     2.9999 : Y :       5     17 :   
        TO SC AB                                                                                         :   41715  41634 :     0.0787 : Y :      16     46 :   
        TO SC BT BT BT BT BT BT SA                                                                       :   37206  37170 :     0.0174 : Y :      29     39 :   
        TO BT BT SA                                                                                      :   23450  23528 :     0.1295 : Y :      56     21 :   
        TO SC SC BT BT BT BT BT BT SD                                                                    :   17502  17472 :     0.0257 : Y :      37      4 :   
        TO BT BT BT BT BT BT BT SR SA                                                                    :   15713  15715 :     0.0001 : Y :      46      6 :   
        TO SC SC AB                                                                                      :   14643  14608 :     0.0419 : Y :      51    132 :   
        TO BT BT BT BT BT BT BT SA                                                                       :   14436  14280 :     0.8475 : Y :      82     73 :   
        TO BT BT AB                                                                                      :   14182  14412 :     1.8500 : Y :     180     43 :   
        TO SC SC BT BT BT BT BT BT SA                                                                    :   14256  14197 :     0.1223 : Y :       3     58 :   
        TO BT BT BT SA                                                                                   :   13445  13126 :     3.8298 : Y :     104     23 :   
        TO BT BT BT BT SD                                                                                :    9228   9221 :     0.0027 : Y :     327    404 :   
        TO BT BT DR BT SA                                                                                :    8208   8225 :     0.0176 : Y :      30     41 :   
        TO SC BT BT AB                                                                                   :    7473   7215 :     4.5319 : Y :      84     71 :   
        TO SC BT BT BT BT BT BT BT SA                                                                    :    7022   7154 :     1.2291 : Y :       9     82 :   
        TO BT BT BT BT BT BT BT SR SR SA                                                                 :    6706   6779 :     0.3952 : Y :      54      7 :   
        TO SC BT BT SA                                                                                   :    6584   6596 :     0.0109 : Y :     143    168 :   
        TO SC BT BT BT BT BT BT BT SR SA                                                                 :    6347   6192 :     1.9160 : Y :     106    373 :   
        TO SC SC SC BT BT BT BT BT BT SD                                                                 :    6240   6303 :     0.3164 : Y :     167    154 :   
        TO BT AB                                                                                         :    5846   6124 :     6.4565 : Y :     382     91 :   
        TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                               :    5497   5644 :     1.9396 : Y :     103    469 :   
        TO SC SC SC BT BT BT BT BT BT SA                                                                 :    5064   5053 :     0.0120 : Y :     418     69 :   
        TO SC SC SC AB                                                                                   :    4929   4933 :     0.0016 : Y :     146    252 :   
        TO BT BT BT BT BT BT BT SD                                                                       :    4590   4743 :     2.5082 : Y :     675    266 :   
        TO RE AB                                                                                         :    4612   4601 :     0.0131 : Y :     729     15 :   
        TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                               :    4501   4393 :     1.3114 : Y :      70     37 :   
        TO SC BT BT BT SA                                                                                :    4304   4383 :     0.7184 : Y :     190     31 :   
        TO SC BT BT BT BT SD                                                                             :    3637   3746 :     1.6092 : Y :      87    492 :   
        TO SC BT AB                                                                                      :    3147   3383 :     8.5292 : Y :     508    489 :   
        TO BT BT BT BT AB                                                                                :    3259   3221 :     0.2228 : Y :     267    908 :   
        TO SC SC BT BT AB                                                                                :    3082   3008 :     0.8992 : Y :      36     76 :   
        TO SC SC BT BT BT BT BT BT BT SA                                                                 :    2791   2864 :     0.9424 : Y :      33    152 :   
        TO SC BT BT BT BT BT BT BT SD                                                                    :    2768   2745 :     0.0960 : Y :     456    121 :   
        TO SC BT BT BT BT SA                                                                             :    2689   2485 :     8.0433 : Y :     102    305 :   
        TO BT BT BT BT BT BT BT SR SR SR SA                                                              :    2524   2511 :     0.0336 : Y :      50    177 :   
        TO SC BT BT BT BT BT BT BT SR SR SA                                                              :    2380   2383 :     0.0019 : Y :     139    109 :   
        TO SC SC BT BT SA                                                                                :    2203   2280 :     1.3226 : Y :    1379    490 :   
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 127133 NUM_MAX 40 num 40 opt AZERO mode 1
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 127133 NUM_MAX 40 num 40 opt BZERO mode 2
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 127133 NUM_MAX 40 num 40 opt DEVIANT mode 5
    ]sseq_index_ab::desc

    pvplt MODE:2 
    f




    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum :  2608.4727 c2n :  2074.0000 c2per:     1.2577  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  2608.47/2074:1.258 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO AB                                                                                          ' ' 0' '111833 112335' ' 1.1242' '     0      5']
     [' 1' 'TO BT BT BT BT BT BT SD                                                                        ' ' 1' '101967 101730' ' 0.2757' '    14      3']
     [' 2' 'TO BT BT BT BT BT BT SA                                                                        ' ' 2' ' 80729  80729' ' 0.0000' '    11      1']
     [' 3' 'TO SC BT BT BT BT BT BT SD                                                                     ' ' 3' ' 45851  46377' ' 2.9999' '     5     17']
     [' 4' 'TO SC AB                                                                                       ' ' 4' ' 41715  41634' ' 0.0787' '    16     46']
     [' 5' 'TO SC BT BT BT BT BT BT SA                                                                     ' ' 5' ' 37206  37170' ' 0.0174' '    29     39']
     [' 6' 'TO BT BT SA                                                                                    ' ' 6' ' 23450  23528' ' 0.1295' '    56     21']
     [' 7' 'TO SC SC BT BT BT BT BT BT SD                                                                  ' ' 7' ' 17502  17472' ' 0.0257' '    37      4']
     [' 8' 'TO BT BT BT BT BT BT BT SR SA                                                                  ' ' 8' ' 15713  15715' ' 0.0001' '    46      6']
     [' 9' 'TO SC SC AB                                                                                    ' ' 9' ' 14643  14608' ' 0.0419' '    51    132']
     ['10' 'TO BT BT BT BT BT BT BT SA                                                                     ' '10' ' 14436  14280' ' 0.8475' '    82     73']
     ['11' 'TO BT BT AB                                                                                    ' '11' ' 14182  14412' ' 1.8500' '   180     43']
     ['12' 'TO SC SC BT BT BT BT BT BT SA                                                                  ' '12' ' 14256  14197' ' 0.1223' '     3     58']
     ['13' 'TO BT BT BT SA                                                                                 ' '13' ' 13445  13126' ' 3.8298' '   104     23']
     ['14' 'TO BT BT BT BT SD                                                                              ' '14' '  9228   9221' ' 0.0027' '   327    404']
     ['15' 'TO BT BT DR BT SA                                                                              ' '15' '  8208   8225' ' 0.0176' '    30     41']
     ['16' 'TO SC BT BT AB                                                                                 ' '16' '  7473   7215' ' 4.5319' '    84     71']
     ['17' 'TO SC BT BT BT BT BT BT BT SA                                                                  ' '17' '  7022   7154' ' 1.2291' '     9     82']
     ['18' 'TO BT BT BT BT BT BT BT SR SR SA                                                               ' '18' '  6706   6779' ' 0.3952' '    54      7']
     ['19' 'TO SC BT BT SA                                                                                 ' '19' '  6584   6596' ' 0.0109' '   143    168']
     ['20' 'TO SC BT BT BT BT BT BT BT SR SA                                                               ' '20' '  6347   6192' ' 1.9160' '   106    373']
     ['21' 'TO SC SC SC BT BT BT BT BT BT SD                                                               ' '21' '  6240   6303' ' 0.3164' '   167    154']
     ['22' 'TO BT AB                                                                                       ' '22' '  5846   6124' ' 6.4565' '   382     91']
     ['23' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                             ' '23' '  5497   5644' ' 1.9396' '   103    469']
     ['24' 'TO SC SC SC BT BT BT BT BT BT SA                                                               ' '24' '  5064   5053' ' 0.0120' '   418     69']
     ['25' 'TO SC SC SC AB                                                                                 ' '25' '  4929   4933' ' 0.0016' '   146    252']
     ['26' 'TO BT BT BT BT BT BT BT SD                                                                     ' '26' '  4590   4743' ' 2.5082' '   675    266']
     ['27' 'TO RE AB                                                                                       ' '27' '  4612   4601' ' 0.0131' '   729     15']
     ['28' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                             ' '28' '  4501   4393' ' 1.3114' '    70     37']
     ['29' 'TO SC BT BT BT SA                                                                              ' '29' '  4304   4383' ' 0.7184' '   190     31']
     ['30' 'TO SC BT BT BT BT SD                                                                           ' '30' '  3637   3746' ' 1.6092' '    87    492']
     ['31' 'TO SC BT AB                                                                                    ' '31' '  3147   3383' ' 8.5292' '   508    489']
     ['32' 'TO BT BT BT BT AB                                                                              ' '32' '  3259   3221' ' 0.2228' '   267    908']
     ['33' 'TO SC SC BT BT AB                                                                              ' '33' '  3082   3008' ' 0.8992' '    36     76']
     ['34' 'TO SC SC BT BT BT BT BT BT BT SA                                                               ' '34' '  2791   2864' ' 0.9424' '    33    152']
     ['35' 'TO SC BT BT BT BT BT BT BT SD                                                                  ' '35' '  2768   2745' ' 0.0960' '   456    121']
     ['36' 'TO SC BT BT BT BT SA                                                                           ' '36' '  2689   2485' ' 8.0433' '   102    305']
     ['37' 'TO BT BT BT BT BT BT BT SR SR SR SA                                                            ' '37' '  2524   2511' ' 0.0336' '    50    177']
     ['38' 'TO SC BT BT BT BT BT BT BT SR SR SA                                                            ' '38' '  2380   2383' ' 0.0019' '   139    109']
     ['39' 'TO SC SC BT BT SA                                                                              ' '39' '  2203   2280' ' 1.3226' '  1379    490']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [['294' 'TO BT BT BT BT BR SR SA                                                                        ' '294' '   183      0' '183.0000' '  4232      0']
     ['969' 'TO BT BT BT BT BR SA                                                                           ' '969' '    42      0' '42.0000' ' 18984      0']
     ['1500' 'TO SC BT BT BT BT BR SR SA                                                                     ' '1500' '    25      0' ' 0.0000' '  7924      0']
     ['1779' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                          ' '1779' '    21      0' ' 0.0000' ' 20777      0']
     ['2864' 'TO BT BT BT BT BR BR BR BT AB                                                                  ' '2864' '    12      0' ' 0.0000' '301580      0']
     ['3128' 'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT BT SD                                       ' '3128' '    11      0' ' 0.0000' '  5351      0']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    []
    ]----- repr(ab) 
    [--- abh = SABHit(a,b) ----
    ]--- abh = SABHit(a,b) ----
    [----- repr(abh) 


    SABHit  a_nhit :  254080  b_nhit:  259079  a/b_nhit:  0.981  b/a_nhit:  1.020 


    ]----- repr(abh) 



Notable that with OPTICKS_MAX_BOUNCE 31 that get 2% less hits with Opticks than with Geant4.


Try with OPTICKS_MAX_BOUNCE 63 : doing this required SEventConfig+SEvt rejig 
------------------------------------------------------------------------------

Increase in OPTICKS_MAX_BOUNCE makes the hit difference reduce to 2 per mille::

    SABHit  a_nhit :  258596  b_nhit:  259079  a/b_nhit:  0.998  b/a_nhit:  1.002 

Which is in agreement::

    SABHit  a_nhit : (  258576 +-  508 )  b_nhit:(   259079 +-  508 )  a/b: (  0.998 +-  0.004 )  b/a: (  1.002 +-  0.004)  [assume uncorr.]


Got that after some rejig::

    unoSD_PMT_v2::Initialize eventID 0
    2025-05-13 16:34:58.726 INFO  [617343] [U4Recorder::BeginOfEventAction_@333]  eventID 0
    Begin of Event --> 0
    2025-05-13 16:34:59.342 FATAL [617343] [SEvt::rjoinSeqCheck@2758]  flag_xor FAIL   

    python: /home/blyth/opticks/sysrap/SEvt.cc:2759: void SEvt::rjoinSeqCheck(unsigned int) const: Assertion `flag_xor' failed.

    (gdb) bt
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc313ebf3 in SEvt::rjoinSeqCheck (this=0x6971c60, seq_flag=0) at /home/blyth/opticks/sysrap/SEvt.cc:2759
    #6  0x00007fffc313e116 in SEvt::rjoinPhoton (this=0x6971c60, label=...) at /home/blyth/opticks/sysrap/SEvt.cc:2633
    #7  0x00007fffc55f93ca in U4Recorder::PreUserTrackingAction_Optical (this=0x6971c30, track=0x1119f7550) at /home/blyth/opticks/u4/U4Recorder.cc:482
    #8  0x00007fffc55f8a24 in U4Recorder::PreUserTrackingAction (this=0x6971c30, track=0x1119f7550) at /home/blyth/opticks/u4/U4Recorder.cc:379
    #9  0x00007fffc23a493e in U4RecorderAnaMgr::PreUserTrackingAction (this=0x66cdda0, trk=0x1119f7550) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:37
    #10 0x00007fffcf354d92 in MgrOfAnaElem::PreUserTrackingAction (this=0x8ee3c50, trk=0x1119f7550) at /home/blyth/junosw/Simulat


::

    2746 void SEvt::rjoinSeqCheck(unsigned seq_flag) const
    2747 {
    2748     dbg->rjoinSeqCheck++ ;
    2749 
    2750     bool flag_AB = seq_flag == BULK_ABSORB ;
    2751     bool flag_MI = seq_flag == MISS ;
    2752     bool flag_xor = flag_AB ^ flag_MI ;
    2753 
    2754     if(flag_AB)  dbg->rjoinSeqCheck_flag_AB++ ;
    2755     if(flag_MI)  dbg->rjoinSeqCheck_flag_MI++ ;
    2756     if(flag_xor) dbg->rjoinSeqCheck_flag_xor++ ;
    2757 
    2758     LOG_IF(fatal, !flag_xor) << " flag_xor FAIL " << OpticksPhoton::Abbrev(seq_flag) << std::endl ;
    2759     assert( flag_xor );
    2760 }


Observe that get very diffent chimney behavior : so try to plant input photon there : but seems not to work
----------------------------------------------------------------------------------------------------------------


::

     MOI=sChimneyLS:0:-1 cxr_min.sh   ## succeeds to visualize the Chimney


BUT not working for transforming input photons::

    2025-05-13 21:49:28.489 INFO  [924651] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000 SEventConfig::MaxCurand 1000000000
    2025-05-13 21:49:28.737 INFO  [924651] [CSGTarget::getFrameComponents@227] (gord == -1) qptr transform will not be set, typically defaulting to identity 
    2025-05-13 21:49:28.737 INFO  [924651] [SEvt::transformInputPhoton@694]  SEvt__transformInputPhoton_VERBOSE  SEventConfig::IsRGModeSimulate 1 hasInputPhoton 1 proceed YES
    sframe::desc inst 0 frs sChimneyLS:0:-1
     ekvid sframe_OPTICKS_INPUT_PHOTON_FRAME_sChimneyLS_0_-1 ek OPTICKS_INPUT_PHOTON_FRAME ev sChimneyLS:0:-1
     ce  ( 0.000, 0.000,19787.000,1963.000)  is_zero 0
     m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000, 0.000, 1.000) 
     w2m ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000, 0.000, 1.000) 
     midx  137 mord    0 gord   -1
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier        0 sensor_index      0
     propagate_epsilon    0.05000 is_hostside_simtrace NO


    2025-05-13 21:49:29.192 INFO  [924651] [SEvt::transformInputPhoton@694]  SEvt__transformInputPhoton_VERBOSE  SEventConfig::IsRGModeSimulate 1 hasInputPhoton 1 proceed YES
    sframe::desc inst 0 frs sChimneyLS:0:-1
     ekvid sframe_OPTICKS_INPUT_PHOTON_FRAME_sChimneyLS_0_-1 ek OPTICKS_INPUT_PHOTON_FRAME ev sChimneyLS:0:-1
     ce  ( 0.000, 0.000,19787.000,1963.000)  is_zero 0
     m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000, 0.000, 1.000) 
     w2m ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000, 0.000, 1.000) 
     midx  137 mord    0 gord   -1
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier        0 sensor_index      0
     propagate_epsilon    0.05000 is_hostside_simtrace NO


    2025-05-13 21:49:29.657 INFO  [924651] [G4CXOpticks::setGeometry@318] CSGOptiX::Desc Version 7 WITH_CUSTOM4 
    2025-05-13 21:49:29.658 INFO  [924651] [LSExpDetectorConstruction_Opticks::Setup@49] ] WITH_G4CXOPTICKS 
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/dat


Pilot error need sChimneyLS:0:-2

* currently uncertain why need -2 for input photons but -1 for viz


Very different chimney behaviour 
----------------------------------

::

    /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_opticks_Debug
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              FOLD : /tmp/blyth/opticks/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_RandomSpherical1M_f8/A000 
                             BFOLD : /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_RandomSpherical1M_f8/B000 
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_RandomSpherical1M_f8/A000/seq.npy a_seq (1000000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_RandomSpherical1M_f8/B000/seq.npy b_seq (1000000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1747205779941109
     t1 1747205780069075 (t1 - t0)   127966 0.127966
     t2 1747205780199244 (t2 - t1)   130169 0.130169
     t3 1747205780221659 (t3 - t2)    22415 0.022415
    AB
    [sseq_index_ab::desc u_size 29671 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum 65549.1643 ndf 349.0000 sum/ndf   187.8200 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO SA                                                                                            :  566110 560907 :    24.0202 : Y :       1      4 : DEVIANT  `
    :r:`TO DR SA                                                                                         :  208221 204093 :    41.3287 : Y :       0      1 : DEVIANT  `
    :r:`TO DR DR SA                                                                                      :   75235  73331 :    24.4014 : Y :      21     18 : DEVIANT  `
    :r:`TO DR DR DR SA                                                                                   :   26978  26182 :    11.9190 : Y :      50      0 : DEVIANT  `
    :r:`TO AB                                                                                            :   15306   5305 :  4852.7486 : Y :      25      2 : DEVIANT  `
    :r:`TO SC SA                                                                                         :    1492  10571 :  6833.1461 : Y :     146     32 : DEVIANT  `
        TO DR DR DR DR SA                                                                                :    9477   9216 :     3.6442 : Y :      22    274 :   
    :r:`TO BT BT AB                                                                                      :    8089    180 :  7564.6730 : Y :     133   4259 : DEVIANT  `
    :r:`TO DR AB                                                                                         :    7624   2665 :  2390.0944 : Y :     973    160 : DEVIANT  `
    :r:`TO DR SC SA                                                                                      :     744   5297 :  3431.5195 : Y :     794    200 : DEVIANT  `
    :r:`TO BT BT BT SA                                                                                   :     111   4086 :  3764.7427 : Y :    1351    133 : DEVIANT  `
    :r:`TO SC DR SA                                                                                      :     537   3888 :  2537.6725 : Y :    6600   1176 : DEVIANT  `
    :r:`TO DR BT BT AB                                                                                   :    3496    314 :  2657.5129 : Y :     164   3389 : DEVIANT  `
        TO DR DR DR DR DR SA                                                                             :    3314   3180 :     2.7650 : Y :     117     41 :   
    :r:`TO DR DR AB                                                                                      :    2895   1000 :   921.9576 : Y :    1507   4523 : DEVIANT  `
    :r:`TO BT BT SA                                                                                      :     259   2557 :  1875.2855 : Y :    1248    199 : DEVIANT  `




AB comparison with storch photons ? 
-------------------------------------

It is limiting to be restricted to the canned input photons, 
but getting storch generation to work insitu just for debugging 
is a too much effort. So as a workaround could pre-generate 
input photons from torch gensteps using SGenerate::GeneratePhotons
and use the input photon machinery.


::

    A[blyth@localhost ~]$ opticks-f SGenerate.h
    ./g4cx/tests/G4CXApp.h:#include "SGenerate.h"
    ./sysrap/CMakeLists.txt:    SGenerate.h
    ./sysrap/SGenerate.h:SGenerate.h
    ./sysrap/SGenerate.h:the MOCK_CURAND macro the method was moved to this header only SGenerate.h  
    ./sysrap/SGenstep.h:sysrap/SGenerate.h
    ./sysrap/tests/SGenerate__test.cc:#include "SGenerate.h"
    ./sysrap/tests/SGenerate_test.cc:#include "SGenerate.h"
    ./u4/U4VPrimaryGenerator.h:         << "compile with MOCK_CURAND to use SGenerate.h curand on CPU" << std::endl 
    A[blyth@localhost opticks]$ 




Chimney
-----------

::

    A[blyth@localhost CSGFoundry]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug/CSGFoundry
    A[blyth@localhost CSGFoundry]$ grep Chimney  meshname.txt 
    Upper_Chimney
    sBotChimneySSEnclosureLS_PartI_II_III
    sBotChimneySSEnclosure_PartI_II_III
    sChimneyAcrylic
    sChimneyLS
    sChimneySteel

    A[blyth@localhost CSGFoundry]$ grep Chimney  tessname.txt 
    #Upper_Chimney
    #sBotChimneySSEnclosureLS_PartI_II_III
    #sBotChimneySSEnclosure_PartI_II_III
    #sChimneyAcrylic
    #sChimneyLS
    #sChimneySteel
    A[blyth@localhost CSGFoundry]$ 



Add Chimney bookmarks to framespec
--------------------------------------

::

    ]CSGImport::importPrim.dump_LVID:1 node.lvid 105 LVID -1 name uni1_0 soname uni1_0
    NPFold::add_ FATAL : have_key_already [Hama_0_0.npy]
    NPFold::descKeys kk.size 29 [Hama_0_0.npy]  [NNVT_0_0.npy]  [Hama_0_1000.npy]  [NNVT_0_1000.npy]  [sDeadWater_0_-1.npy]  [sChimneyLS_0_-1.npy]  [sChimneyAcrylic_0_-1.npy]  [sChimneySteel_0_-1.npy]  [Upper_Chimney_0_-1.npy]  [sBotChimneySSEnclosureLS_PartI_II_III_0_-1.npy]  [sBotChimneySSEnclosure_PartI_II_III_0_-1.npy]  [GZ1.A06_07_FlangeI_Web_FlangeII_15_-1.npy]  [GZ1.B06_07_FlangeI_Web_FlangeII_15_-1.npy]  [solidXJfixture_0_-1.npy]  [solidXJfixture_20_-1.npy]  [solidXJfixture_40_-1.npy]  [solidXJfixture_55_-1.npy]  [solidXJanchor_0_-1.npy]  [solidXJanchor_20_-1.npy]  [solidXJanchor_40_-1.npy]  [solidXJanchor_55_-1.npy]  [solidSJCLSanchor_0_-1.npy]  [solidSJFixture_0_-1.npy]  [solidSJReceiver_0_-1.npy]  [solidSJReceiverFastern_0_-1.npy]  [sSurftube_0V1_0_0_-1.npy]  [sSurftube_38V1_0_0_-1.npy]  [sSurftube_38V1_1_0_-1.npy]  [solidXJfixture_27_-1.npy] python: /home/blyth/opticks/sysrap/NPFold.h:1628: void NPFold::add_(const char*, const NP*): Assertion `!have_key_already' failed.
     *** Break *** abort



Updating local OJ build
~~~~~~~~~~~~~~~~~~~~~~~~

After making changes in ~/junosw eg to Examples/Tutorial/share/opticks_juno.sh
update OJ with:

1. open new tab with empty env and setup and invoke the OJ build::

    local_oj_build # ljb
    oj_build

2. open new tab with empty env and setup and invoke the OJ Opticks geom config::

    local_oj_local # ljl
    oj_local


Frame dir::

    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug/CSGFoundry/SSim/scene/frame/



"MOI=sChimneyLS:0:-1 cxr_min.sh" works but "MOI=sChimneyLS:0:-2 cxr_min.sh" does not ? WHY ?
---------------------------------------------------------------------------------------------- 

::

    A[blyth@localhost CSGFoundry]$ MOI=sChimneyLS:0:-2 cxr_min.sh 
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh - External GEOM setup detected
                     External_CFBaseFromGEOM : J25_3_0_opticks_Debug_CFBaseFromGEOM 
        J25_3_0_opticks_Debug_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug 
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh : USING EXTERNALLY SETUP GEOMETRY ENVIRONMENT : EG FROM OJ DISTRIBUTION
                     bin : CSGOptiXRenderInteractiveTest 
               which_bin : /data1/blyth/local/opticks_Debug/lib/CSGOptiXRenderInteractiveTest 
                    GEOM : J25_3_0_opticks_Debug 
                     MOI : sChimneyLS:0:-2 
                     EMM :  
                     ELV :  
                    TMIN : 0.5 
                     EYE : 1,0,0 
                    LOOK : 0,0,0 
                      UP : 0,0,1 
                    ZOOM : 1 
                  LOGDIR : /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/CSGOptiXRenderInteractiveTest 
                    BASE : /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/CSGOptiXRenderInteractiveTest 
                    PBAS : /tmp/blyth/opticks/ 
              NAMEPREFIX : cxr_min__eye_1,0,0__zoom_1__tmin_0.5_ 
            OPTICKS_HASH :  
                 TOPLINE : ESCALE=extent EYE=1,0,0 TMIN=0.5 MOI=sChimneyLS:0:-2 ZOOM=1 CAM=perspective cxr_min.sh  
                 BOTLINE : Thu May 15 01:40:49 PM CST 2025 
    CUDA_VISIBLE_DEVICES :  
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh : run : delete prior LOG CSGOptiXRenderInteractiveTest.log
    stree::get_frame_instanced FAIL missing_transform  lvid 137 lvid_ordinal 0 repeat_ordinal -2 w2m NO  m2w NO  ii -1
    stree::get_frame FAIL q_spec[sChimneyLS:0:-2]
     THIS CAN BE CAUSED BY NOT USING REPEAT_ORDINAL -1 (LAST OF TRIPLET) FOR GLOBAL GEOMETRY 
    CSGOptiXRenderInteractiveTest: /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:1864: sfr stree::get_frame(const char*) const: Assertion `get_rc == 0' failed.
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh: line 245: 1756844 Aborted                 (core dumped) $bin
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh run error
    A[blyth@localhost CSGFoundry]$ 



::

    A[blyth@localhost CSGFoundry]$ MOI=sChimneyLS:0:-2 cxr_min.sh dbg
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh - External GEOM setup detected
                     External_CFBaseFromGEOM : J25_3_0_opticks_Debug_CFBaseFromGEOM 
        J25_3_0_opticks_Debug_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug 
    ...
    stree::get_frame_instanced FAIL missing_transform  lvid 137 lvid_ordinal 0 repeat_ordinal -2 w2m NO  m2w NO  ii -1
    stree::get_frame FAIL q_spec[sChimneyLS:0:-2]
     THIS CAN BE CAUSED BY NOT USING REPEAT_ORDINAL -1 (LAST OF TRIPLET) FOR GLOBAL GEOMETRY 
    CSGOptiXRenderInteractiveTest: /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:1864: sfr stree::get_frame(const char*) const: Assertion `get_rc == 0' failed.

    #4  0x00007ffff4c373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x000000000046f995 in stree::get_frame (this=0x510220, q_spec=0x7fffffff1ec2 "sChimneyLS:0:-2") at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:1864
    #6  0x0000000000444393 in main (argc=1, argv=0x7fffffff0108) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:85
    (gdb) 


Hmm failing to stree::get_frame prior to render loop::

    080     const char* MOI = ssys::getenvvar("MOI", "0:0:-1" );  // default lvid 0 in remainder 
     81     const char* PFX = "EXTENT:" ;
     82     float extent = sstr::StartsWith(MOI, PFX) ? sstr::To<float>( MOI + strlen(PFX) ) : 0.f ;
     83     // this extent handling is primarily for use with simple single solid test geometries
     84 
     85     sfr mfr = extent > 0.f ? sfr::MakeFromExtent<float>(extent) :  st->get_frame(MOI);    // HMM: what about when start from CSGMaker geometry ? 
     86     mfr.set_idx(-2);                 // maybe should start from stree/snode/sn geometry with an streemaker.h ?  
     87     // moved stree::get_frame prior to popping up the window, so failures 
     88     // from bad MOI dont cause hang 



    1828 inline sfr stree::get_frame(const char* q_spec ) const
    1829 {
    1830     int lvid ;
    1831     int lvid_ordinal ;
    1832     int repeat_ordinal ;
    1833     int parse_rc = parse_spec( lvid, lvid_ordinal, repeat_ordinal, q_spec );
    1834 
    1835     if(parse_rc != 0) std::cerr
    1836         << "stree::get_frame"
    1837         << " FATAL parse_spec failed "
    1838         << " q_spec [" << ( q_spec ? q_spec : "-" ) << "]"
    1839         << " parse_rc " << parse_rc
    1840         << "\n"
    1841         ;
    1842     assert( parse_rc == 0 );
    1843 
    1844     sfr f ;
    1845     f.set_name(q_spec);
    1846 
    1847 
    1848     [[maybe_unused]] int get_rc = 0 ;
    1849     if( repeat_ordinal == -1 )
    1850     {
    1851         get_rc = get_frame_global(  f,  lvid, lvid_ordinal, repeat_ordinal );
    1852     }
    1853     else
    1854     {
    1855         get_rc = get_frame_instanced(f,  lvid, lvid_ordinal, repeat_ordinal );
    1856     }
    1857 
    1858     if(get_rc != 0 ) std::cerr
    1859         << "stree::get_frame FAIL q_spec[" << ( q_spec ? q_spec : "-" ) << "]\n"
    1860         << " THIS CAN BE CAUSED BY NOT USING REPEAT_ORDINAL -1 (LAST OF TRIPLET) FOR GLOBAL GEOMETRY "
    1861         << "\n"
    1862         ;
    1863 
    1864     assert( get_rc == 0 );
    1865     return f ;
    1866 }






