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



