InputPhotonsCheck_WP_revisited
=================================

ipcv::

    175     elif [ "$TEST" == "WP_PMT" ]; then
    176 
    177        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    178        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    179        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    180        observation=" A and B"
    181 
    182        #export U4Recorder__EndOfRunAction_Simtrace=1
    183        #export U4Simtrace__level=2
    184 
    185        export C4OpBoundaryProcess__PIDX_ENABLED=1
    186        export PIDX=99999
    187 




::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 29735 hitCollectionAlt 29562 hcMuon 0 GPU YES


    SABHit  a_nhit : (   29562 +-  171 )  b_nhit:(    29735 +-  172 )  a/b: (  0.994 +-  0.012 )  b/a: (  1.006 +-  0.012)  [assume uncorr.]




    [sseq_index_test.cc
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/A000/seq.npy a_seq (100000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/B000/seq.npy b_seq (100000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1751550906200269
     t1 1751550906211408 (t1 - t0)    11139 0.011139
     t2 1751550906223079 (t2 - t1)    11671 0.011671
     t3 1751550906223625 (t3 - t2)      546 0.000546
    AB
    [sseq_index_ab::desc u_size 829 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum    54.3135 ndf 59.0000 sum/ndf     0.9206 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SA                                                                                :   30563  30508 :     0.0495 : Y :       2      0 :   
        TO BT BT BT BT EC                                                                                :   29246  29398 :     0.3940 : Y :       1      5 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9661   9850 :     1.8308 : Y :       6     45 :   
        TO BT BT BT BT BT SR SA                                                                          :    7688   7783 :     0.5833 : Y :   10622  10391 :   
        TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    6782   6904 :     1.0875 : Y :   10830  10837 :   
        TO BT BT BT BT BT SA                                                                             :    2060   1940 :     3.6000 : Y :    8707   8511 :   
        TO BT BT BT BT EX                                                                                :    1982   1863 :     3.6830 : Y :       0      2 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :    1739   1735 :     0.0046 : Y :   20717  20579 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    1552   1514 :     0.4710 : Y :   20911  20910 :   
        TO BT BT BT BT BT SR BR SA                                                                       :     911    876 :     0.6855 : Y :   10942  10869 :   
        TO BT BT BR BT BT SA                                                                             :     677    678 :     0.0007 : Y :      16     23 :   
        TO BT BT BT BR BT BT BT SA                                                                       :     594    595 :     0.0008 : Y :       4      4 :   
        TO BT BR BT SA                                                                                   :     511    496 :     0.2234 : Y :      23     34 :   
        TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     507    483 :     0.5818 : Y :   21826  21843 :   
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :     463    471 :     0.0685 : Y :    6761   2288 :   
        TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     377    392 :     0.2926 : Y :   22327  22020 :   
        TO BT BT BT BT AB                                                                                :     324    380 :     4.4545 : Y :     199    759 :   
        TO BT BT BT BT BT SR BR BT BT BT BT BT SA                                                        :     361    356 :     0.0349 : Y :   10840  10864 :   
        TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     190    160 :     2.5714 : Y :   11341  12271 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :     174    158 :     0.7711 : Y :    7625   7626 :   
        TO BT BT BT BT BT SR BR BR SA                                                                    :     131    143 :     0.5255 : Y :   11507  10818 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     137    131 :     0.1343 : Y :   22020  22567 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT EC                                                     :     121    130 :     0.3227 : Y :    7674   7732 :   
        TO BT BT BT BT BT SR BR SR BR SA                                                                 :     127    115 :     0.5950 : Y :   20904  20900 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     123    109 :     0.8448 : Y :   23131  22059 :   
        TO BT BT BT BT BT SR BR BR SR SA                                                                 :     106    112 :     0.1651 : Y :   14935  14875 :   
        TO BT BT AB                                                                                      :     101    101 :     0.0000 : Y :    1167    180 :   
        TO BT BT BT BT BT SR BR BR SR BT BT BT BT BT SA                                                  :      90     95 :     0.1351 : Y :   15183  15103 :   
        TO BT AB                                                                                         :      79     93 :     1.1395 : Y :     239    195 :   
        TO BT BT BT BT BT SR BR BR BT BT BT BT BT SA                                                     :      72     80 :     0.4211 : Y :   10967  10947 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SA                                                           :      78     65 :     1.1818 : Y :    9625   9626 :   
        TO AB                                                                                            :      77     68 :     0.5586 : Y :     597   2112 :   
        TO BT BT BT BT BT BT BT BT BT BT SA                                                              :      64     56 :     0.5333 : Y :    8997   8867 :   
        TO BT BT BT BT BT BR SR SA                                                                       :      53     35 :     3.6818 : Y :    8953   8827 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT AB                                                     :      46     52 :     0.3673 : Y :   21023  20942 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BT BT SA                                      :      52     41 :     1.3011 : Y :    7753   7963 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SR BR SR SA                                                  :      44     39 :     0.3012 : Y :   22509  23521 :   
        TO BT BT BT BT BT SR BR BR BR SA                                                                 :      39     43 :     0.1951 : Y :   10872  11046 :   
        TO BT BT BT BT BT SR BR BR BR SR SA                                                              :      41     30 :     1.7042 : Y :   12303  12483 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SA                                                           :      40     35 :     0.3333 : Y :   22320  22225 :   
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 829 NUM_MAX 40 num 829 opt AZERO mode 1
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 829 NUM_MAX 40 num 829 opt BZERO mode 2
        TO BT BT BT SA                                                                                   :      28     -1 :     0.0000 : N :   49842     -1 : BZERO C2EXC  
        TO BT BT BT EC                                                                                   :      21     -1 :     0.0000 : N :   49852     -1 : BZERO C2EXC  
        TO BT BT BT BT SR SA                                                                             :      16     -1 :     0.0000 : N :   49855     -1 : BZERO C2EXC  
        TO BT BT BT BR BT BT BT BT SA                                                                    :      15     -1 :     0.0000 : N :   49848     -1 : BZERO C2EXC  
        TO BT BT BT BT SR BT BT BT BT BT SA                                                              :      14     -1 :     0.0000 : N :   49844     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc




    In [4]: w = a.q_startswith("TO BT BT BT SA") ; w
    Out[4]: 
    array([49842, 49843, 49845, 49847, 49854, 49862, 49863, 49865, 49869, 49875, 49876, 49887, 49898, 49906, 49909, 49910, 49919, 49920, 49941, 49944, 49949, 49952, 49953, 49956, 49961, 49962, 49964,
           49982])






