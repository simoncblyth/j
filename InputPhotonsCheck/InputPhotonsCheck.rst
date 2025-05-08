InputPhotonsCheck
==================


At 10k input photon level no issues::

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





