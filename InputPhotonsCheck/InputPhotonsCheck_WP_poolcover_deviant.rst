InputPhotonsCheck_WP_poolcover_deviant
========================================


Issue : deviant photons towards poolcover
--------------------------------------------

::

         
    SABHit  a_nhit : (   29562 +-  171 )  b_nhit:(    29680 +-  172 )  a/b: (  0.996 +-  0.012 )  b/a: (  1.004 +-  0.012)  [assume uncorr.]

    AB
    [sseq_index_ab::desc u_size 868 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   117.7114 ndf 60.0000 sum/ndf     1.9619 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SA                                                                                :   30563  30517 :     0.0346 : Y :       2      0 :   
        TO BT BT BT BT EC                                                                                :   29246  29368 :     0.2539 : Y :       1      4 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9621   9789 :     1.4541 : Y :       6      2 :   
        TO BT BT BT BT BT SR SA                                                                          :    7688   7791 :     0.6854 : Y :   10622  10360 :   
        TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    6782   6908 :     1.1597 : Y :   10830  10807 :   
        TO BT BT BT BT BT SA                                                                             :    2060   1949 :     3.0733 : Y :    8707   8505 :   
        TO BT BT BT BT EX                                                                                :    1982   1838 :     5.4283 : Y :       0     26 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :    1739   1734 :     0.0072 : Y :   20717  20592 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    1552   1515 :     0.4464 : Y :   20911  20924 :   
        TO BT BT BT BT BT SR BR SA                                                                       :     911    891 :     0.2220 : Y :   10942  10885 :   
        TO BT BT BR BT BT SA                                                                             :     674    678 :     0.0118 : Y :      16      9 :   
        TO BT BT BT BR BT BT BT SA                                                                       :     590    579 :     0.1035 : Y :       4      1 :   
        TO BT BR BT SA                                                                                   :     505    507 :     0.0040 : Y :      23     17 :   
        TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     507    484 :     0.5338 : Y :   21826  21759 :   
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :     498    453 :     2.1293 : Y :    6761   2423 :   
        TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     377    394 :     0.3748 : Y :   22327  22038 :   
        TO BT BT BT BT AB                                                                                :     324    393 :     6.6402 : Y :     199     12 :   
        TO BT BT BT BT BT SR BR BT BT BT BT BT SA                                                        :     361    347 :     0.2768 : Y :   10840  10800 :   
        TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     190    163 :     2.0652 : Y :   11341  11142 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :     174    161 :     0.5045 : Y :    7625   7708 :   
        TO BT BT BT BT BT SR BR BR SA                                                                    :     131    146 :     0.8123 : Y :   11507  10840 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     137    130 :     0.1835 : Y :   22020  22585 :   
        TO BT BT BT BT BT SR BR SR BR SA                                                                 :     127    115 :     0.5950 : Y :   20904  20914 :   
        TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     123    109 :     0.8448 : Y :   23131  22077 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT EC                                                     :     121    118 :     0.0377 : Y :    7674   7660 :   
        TO BT BT BT BT BT SR BR BR SR SA                                                                 :     106    110 :     0.0741 : Y :   14935  14899 :   
        TO BT BT AB                                                                                      :     101     96 :     0.1269 : Y :    1167    605 :   
        TO BT BT BT BT BT SR BR BR SR BT BT BT BT BT SA                                                  :      90     97 :     0.2620 : Y :   15183  15037 :   
        TO BT AB                                                                                         :      79     88 :     0.4850 : Y :     239    698 :   
        TO BT BT BT BT BT SR BR BR BT BT BT BT BT SA                                                     :      71     78 :     0.3289 : Y :   10967  10970 :   
        TO AB                                                                                            :      77     68 :     0.5586 : Y :     597   2247 :   
        TO BT BT BT BT BT BT BT BT BT BT SA                                                              :      64     43 :     4.1215 : Y :    8997   8646 :   
    :r:`TO BT BT BT BT BR BT BT BT BT BT SA                                                              :       5     62 :    48.4925 : Y :   10019   9967 : DEVIANT  `
        TO BT BT BT BT BR BT BT BT BT BT BT SA                                                           :      54     44 :     1.0204 : Y :   90018  10563 :   
        TO BT BT BT BT BT BR SR SA                                                                       :      53     38 :     2.4725 : Y :    8953   9042 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT AB                                                     :      46     53 :     0.4949 : Y :   21023  20870 :


::

    In [3]: wa = a.q_startswith("TO BT BT BT BT BR BT BT BT BT BT SA") ; wa
    Out[3]: array([10019, 10064, 10325, 10394, 10511])

    In [4]: wb = b.q_startswith("TO BT BT BT BT BR BT BT BT BT BT SA") ; wb
    Out[4]: 
    array([ 9967,  9969,  9976,  9993, 10001, 10003, 10005, 10008, 10025, 10029, 10037, 10048, 10060, 10066, 10083, 10104, 10115, 10120, 10144, 10149, 10167, 10171, 10195, 10206, 10212, 10222, 10235,
           10244, 10252, 10261, 10276, 10281, 10292, 10304, 10305, 10307, 10326, 10329, 10332, 10335, 10336, 10339, 10346, 10350, 10364, 10370, 10392, 10395, 10415, 10436, 10443, 10453, 10484, 10493,
           10503, 10506, 10520, 10534, 10538, 10541, 10542, 10560])



    In [6]: a.f.record[wa,:13,0]
    Out[6]: 
    array([[[ 3316.5  , 20444.42 ,   939.328,     0.1  ],
            [ 3310.747, 20408.957,   938.046,     0.266],
            [ 3299.972, 20342.531,   935.644,     0.576],
            [ 3298.408, 20332.895,   934.492,     0.627],
            [ 3297.98 , 20330.254,   934.41 ,     0.639],
            [ 3296.971, 20324.037,   933.724,     0.671],
            [ 3297.06 , 20324.582,   940.036,     0.704],
            [ 3297.064, 20324.607,   942.711,     0.716],
            [ 3297.214, 20325.537,   952.492,     0.767],
            [ 3297.323, 20326.21 ,   999.24 ,     0.982],
            [ 3345.569, 20623.73 , 21652.   ,    69.88 ],
            [ 3345.738, 20624.773, 21750.   ,    70.332],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.501, 20444.428,   939.103,     0.1  ],
            [ 3310.749, 20408.965,   937.821,     0.266],
            [ 3300.004, 20342.729,   935.426,     0.575],
            [ 3298.442, 20333.1  ,   934.277,     0.626],
            [ 3298.014, 20330.46 ,   934.195,     0.638],
            [ 3297.006, 20324.25 ,   933.51 ,     0.67 ],
            [ 3297.097, 20324.812,   939.816,     0.703],
            [ 3297.103, 20324.846,   942.486,     0.715],
            [ 3297.258, 20325.8  ,   952.258,     0.766],
            [ 3297.39 , 20326.62 ,   999.255,     0.982],
            [ 3355.733, 20686.396, 21652.002,    69.883],
            [ 3355.938, 20687.658, 21750.   ,    70.335],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.509, 20444.473,   937.799,     0.1  ],
            [ 3310.756, 20409.01 ,   936.517,     0.266],
            [ 3300.187, 20343.86 ,   934.161,     0.57 ],
            [ 3298.633, 20334.275,   933.029,     0.621],
            [ 3298.208, 20331.66 ,   932.947,     0.633],
            [ 3297.206, 20325.482,   932.273,     0.665],
            [ 3297.313, 20326.143,   938.53 ,     0.697],
            [ 3297.326, 20326.22 ,   941.183,     0.709],
            [ 3297.506, 20327.328,   950.889,     0.759],
            [ 3297.779, 20329.01 ,   999.341,     0.983],
            [ 3414.078, 21046.145, 21652.   ,    69.915],
            [ 3414.486, 21048.658, 21750.   ,    70.367],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.511, 20444.484,   937.454,     0.1  ],
            [ 3310.758, 20409.023,   936.172,     0.266],
            [ 3300.235, 20344.154,   933.826,     0.569],
            [ 3298.683, 20334.584,   932.699,     0.619],
            [ 3298.259, 20331.973,   932.617,     0.631],
            [ 3297.259, 20325.805,   931.946,     0.663],
            [ 3297.37 , 20326.49 ,   938.191,     0.695],
            [ 3297.385, 20326.58 ,   940.838,     0.707],
            [ 3297.571, 20327.729,   950.526,     0.758],
            [ 3297.882, 20329.645,   999.364,     0.983],
            [ 3429.383, 21140.299, 21652.   ,    69.927],
            [ 3429.844, 21143.14 , 21750.   ,    70.379],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.514, 20444.506,   936.87 ,     0.1  ],
            [ 3310.761, 20409.043,   935.587,     0.266],
            [ 3300.316, 20344.656,   933.259,     0.567],
            [ 3298.767, 20335.105,   932.139,     0.617],
            [ 3298.344, 20332.502,   932.057,     0.629],
            [ 3297.346, 20326.35 ,   931.39 ,     0.661],
            [ 3297.465, 20327.078,   937.614,     0.693],
            [ 3297.482, 20327.19 ,   940.249,     0.705],
            [ 3297.679, 20328.404,   949.908,     0.755],
            [ 3298.056, 20330.725,   999.403,     0.984],
            [ 3455.128, 21299.307, 21652.002,    69.951],
            [ 3455.679, 21302.701, 21750.   ,    70.403],
            [    0.   ,     0.   ,     0.   ,     0.   ]]], dtype=float32)




    In [21]: b.f.record[wb[:5],:13,0]
    Out[21]: 
    array([[[ 3316.499, 20444.41 ,   939.588,     0.1  ],
            [ 3310.746, 20408.947,   938.305,     0.266],
            [ 3299.935, 20342.303,   935.896,     0.577],
            [ 3298.37 , 20332.656,   934.741,     0.628],
            [ 3297.941, 20330.012,   934.659,     0.64 ],
            [ 3296.931, 20323.787,   933.97 ,     0.673],
            [ 3297.016, 20324.312,   940.292,     0.705],
            [ 3297.019, 20324.326,   942.973,     0.717],
            [ 3297.165, 20325.225,   952.768,     0.768],
            [ 3297.247, 20325.732,   999.222,     0.982],
            [ 3334.009, 20552.262, 21750.   ,    96.653],
            [ 3334.895, 20557.72 , 22250.   ,    98.959],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.499, 20444.41 ,   939.578,     0.1  ],
            [ 3310.746, 20408.947,   938.295,     0.266],
            [ 3299.936, 20342.312,   935.886,     0.577],
            [ 3298.372, 20332.666,   934.731,     0.628],
            [ 3297.943, 20330.021,   934.649,     0.64 ],
            [ 3296.933, 20323.797,   933.961,     0.672],
            [ 3297.018, 20324.322,   940.282,     0.705],
            [ 3297.021, 20324.338,   942.963,     0.717],
            [ 3297.167, 20325.236,   952.757,     0.768],
            [ 3297.25 , 20325.75 ,   999.223,     0.982],
            [ 3334.464, 20555.07 , 21750.   ,    96.653],
            [ 3335.361, 20560.596, 22250.   ,    98.959],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.499, 20444.412,   939.543,     0.1  ],
            [ 3310.746, 20408.947,   938.26 ,     0.266],
            [ 3299.941, 20342.342,   935.852,     0.577],
            [ 3298.377, 20332.697,   934.698,     0.628],
            [ 3297.948, 20330.055,   934.616,     0.64 ],
            [ 3296.938, 20323.83 ,   933.927,     0.672],
            [ 3297.024, 20324.357,   940.248,     0.705],
            [ 3297.027, 20324.375,   942.928,     0.717],
            [ 3297.173, 20325.28 ,   952.72 ,     0.768],
            [ 3297.26 , 20325.814,   999.225,     0.982],
            [ 3336.051, 20564.898, 21750.   ,    96.654],
            [ 3336.986, 20570.658, 22250.   ,    98.959],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.5  , 20444.414,   939.458,     0.1  ],
            [ 3310.747, 20408.951,   938.175,     0.266],
            [ 3299.954, 20342.418,   935.77 ,     0.577],
            [ 3298.389, 20332.775,   934.616,     0.627],
            [ 3297.961, 20330.133,   934.534,     0.64 ],
            [ 3296.952, 20323.912,   933.847,     0.672],
            [ 3297.038, 20324.445,   940.164,     0.704],
            [ 3297.042, 20324.467,   942.843,     0.716],
            [ 3297.19 , 20325.379,   952.631,     0.767],
            [ 3297.285, 20325.969,   999.231,     0.982],
            [ 3339.934, 20588.723, 21750.   ,    96.655],
            [ 3340.961, 20595.055, 22250.   ,    98.961],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3316.5  , 20444.416,   939.418,     0.1  ],     # 0 
            [ 3310.747, 20408.953,   938.135,     0.266],     # 1
            [ 3299.959, 20342.453,   935.731,     0.577],     # 2
            [ 3298.395, 20332.812,   934.578,     0.627],     # 3
            [ 3297.967, 20330.17 ,   934.496,     0.64 ],     # 4
            [ 3296.958, 20323.95 ,   933.809,     0.672],     # 5 
            [ 3297.045, 20324.488,   940.125,     0.704],     # 6  
            [ 3297.048, 20324.51 ,   942.803,     0.716],     # 7
            [ 3297.197, 20325.428,   952.589,     0.767],     # 8
            [ 3297.297, 20326.043,   999.234,     0.982],     # 9 
            [ 3341.745, 20599.938, 21750.   ,    96.656],
            [ 3342.816, 20606.537, 22250.   ,    98.961],
            [    0.   ,     0.   ,     0.   ,     0.   ]]], dtype=float32)









::

    In [22]: a.q[wa]
    Out[22]: 
    array([[b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             ']], dtype='|S96')

    In [14]: a.f.record[wa,:13,3,0].view(np.uint32) >> 16
    Out[14]: 
    array([[  0, 295, 103, 103, 119, 296, 119, 103, 103, 295,  24,  25,   0],
           [  0, 295, 103, 103, 119, 296, 119, 103, 103, 295,  24,  25,   0],
           [  0, 295, 103, 103, 119, 296, 119, 103, 103, 295,  24,  25,   0],
           [  0, 295, 103, 103, 119, 296, 119, 103, 103, 295,  24,  25,   0],
           [  0, 295, 103, 103, 119, 296, 119, 103, 103, 295,  24,  25,   0]], dtype=uint32)

                                  0
                       vetoWater
                    --------------1---           9
                       Water
                    --------------2----       8
                       Acrylic
                    --------------3--      7
                       Water?
                    --------------4--  6
                       Pyrex
                    --------------5--
                       Vacuum


    In [18]: bdn = cf.sim.stree.standard.bd_names

    In [19]: bdn[a.f.record[wa,:13,3,0].view(np.uint32) >> 16]
    Out[19]: 
    array([['Galactic///Galactic',         # 0:TO
            'vetoWater///Water',           # 1:BT
            'Water///Acrylic',             # 2:BT
            'Water///Acrylic',             # 3:BT
            'Water///Pyrex',               # 4:BT
            'Pyrex/PMT_20inch_veto_photoca # 5:BR ..thode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum', 
            'Water///Pyrex',               # 6:BT  
            'Water///Acrylic',             # 7:BT
            'Water///Acrylic',             # 8:BT
            'vetoWater///Water',           # 9:BT   
            'DeadWater/Implicit_RINDEX_NoRI# BT NDEX_pDeadWater_pTyvekFilm//Tyvek',       MISSING vetoWater///DeadWater ? MUST BE COINCIDENCE
            'Tyvek//Implicit_RINDEX_NoRINDE# SA X_pWaterPool_pTyvekFilm/vetoWater', 
            'Galactic///Galactic'],

           ['Galactic///Galactic', 'vetoWater///Water', 'Water///Acrylic', 'Water///Acrylic', 'Water///Pyrex',
            'Pyrex/PMT_20inch_veto_photocathode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum', 'Water///Pyrex', 'Water///Acrylic', 'Water///Acrylic', 'vetoWater///Water',
            'DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek', 'Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater', 'Galactic///Galactic'],
           ['Galactic///Galactic', 'vetoWater///Water', 'Water///Acrylic', 'Water///Acrylic', 'Water///Pyrex',
            'Pyrex/PMT_20inch_veto_photocathode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum', 'Water///Pyrex', 'Water///Acrylic', 'Water///Acrylic', 'vetoWater///Water',
            'DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek', 'Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater', 'Galactic///Galactic'],
           ['Galactic///Galactic', 'vetoWater///Water', 'Water///Acrylic', 'Water///Acrylic', 'Water///Pyrex',
            'Pyrex/PMT_20inch_veto_photocathode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum', 'Water///Pyrex', 'Water///Acrylic', 'Water///Acrylic', 'vetoWater///Water',
            'DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek', 'Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater', 'Galactic///Galactic'],
           ['Galactic///Galactic', 'vetoWater///Water', 'Water///Acrylic', 'Water///Acrylic', 'Water///Pyrex',
            'Pyrex/PMT_20inch_veto_photocathode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum', 'Water///Pyrex', 'Water///Acrylic', 'Water///Acrylic', 'vetoWater///Water',
            'DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek', 'Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater', 'Galactic///Galactic']], dtype='<U122')







viz both those 5 + 62  shows both sets bouncing off in same direction up towards pool cover : but the 5 are faster
--------------------------------------------------------------------------------------------------------------------

EVT::

     38     elif [ "$check" == "wp_pmt_ipc" ]; then
     39 
     40         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/A000
     41         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/B000
     42          
     43         afold_record_slice="TO BT BT BT BT BR BT BT BT BT BT SA"
     44         bfold_record_slice="TO BT BT BT BT BR BT BT BT BT BT SA"
     45         export AFOLD_RECORD_SLICE="$afold_record_slice"
     46         export BFOLD_RECORD_SLICE="$bfold_record_slice"
     47     
     48     elif [ "$check" == "wp_pmt_cxs" ]; then




cxs_min.sh
------------

::

      elif [ "${TEST:12}" == "_poolcover" ]; then

          sevt__input_photon_dir=$HOME/.opticks/InputPhotons
          opticks_input_photon=UpXZ1000_f8.npy
          opticks_input_photon_frame=3345.569,20623.73,21500
          #export PIDX=99999

          export SEvt__transformInputPhoton_VERBOSE=1
          export CSGFoundry__getFrame_VERBOSE=1
          export CSGFoundry__getFrameE_VERBOSE=1


ipcv
------

::

    186     elif [ "$TEST" == "POOLCOVER" ]; then
    187 
    188       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    189       opticks_input_photon=UpXZ1000_f8.npy
    190       opticks_input_photon_frame=3345.569,20623.73,21500
    191       #export PIDX=99999





