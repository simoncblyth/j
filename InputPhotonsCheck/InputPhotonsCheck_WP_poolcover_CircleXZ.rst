InputPhotonsCheck_WP_poolcover_CircleXZ
==========================================


Setup CircleXZ input photons near poolcover, ipcv::

    188     elif [ "$TEST" == "POOLCOVER" ]; then
    189 
    190       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    191       #opticks_input_photon=UpXZ1000_f8.npy
    192       opticks_input_photon=CircleXZ_R500_100k_f8.npy
    193       #opticks_input_photon=CircleXZ_R10_361_f8.npy
    194       #opticks_input_photon_frame=3345.569,20623.73,21500
    195       opticks_input_photon_frame=3345.569,20623.73,21000
    196       #export PIDX=99999
    197 



After first FIX::

    sseq_index_test.cc
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000/seq.npy a_seq (100000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000/seq.npy b_seq (100000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1751464231536135
     t1 1751464231542298 (t1 - t0)     6163 0.006163
     t2 1751464231547771 (t2 - t1)     5473 0.005473
     t3 1751464231547825 (t3 - t2)       54 0.000054
    AB
    [sseq_index_ab::desc u_size 86 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum    49.8171 ndf  9.0000 sum/ndf     5.5352 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO SA                                                                                            :   85301  85454 :     0.1371 : Y :       0      0 :   
        TO AB                                                                                            :   13861  13716 :     0.7624 : Y :       1      1 :   
    :r:`TO BT BT BT BT SA                                                                                :     154    224 :    12.9630 : Y :   71432  71433 : DEVIANT  `
    :r:`TO BT BT SA                                                                                      :      79    131 :    12.8762 : Y :   71342  71342 : DEVIANT  `
        TO BT BT BT BT EC                                                                                :      96    117 :     2.0704 : Y :   71553  71555 :   
    :r:`TO BT BT AB                                                                                      :      63    108 :    11.8421 : Y :   71358  71344 : DEVIANT  `
        TO BT BT BT BT BT SA                                                                             :      64     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
        TO BT BT BT SA                                                                                   :      59     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
        TO BT BT BT BT AB                                                                                :      40     59 :     3.6465 : Y :   71440  71432 :   
        TO BT BT BR BT BT SA                                                                             :      30     40 :     1.4286 : Y :   71537  71534 :   
        TO BT BT BT AB                                                                                   :      39      1 :     0.0000 : N :   71392  73345 : C2EXC  
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     35 :     4.0909 : Y :   71583  71580 :   
        TO BT BT BT BT BT AB                                                                             :      23     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
        TO BT BR BT SA                                                                                   :      12     17 :     0.0000 : N :   71532  71537 : C2EXC  
        TO BT BT BT BR BT BT BT SA                                                                       :      10     13 :     0.0000 : N :   71561  71549 : C2EXC  
        TO BT BT BT BT BR BT BT SA                                                                       :       7     12 :     0.0000 : N :   71824  71825 : C2EXC  
        TO BT BT BT BT EX                                                                                :       5     10 :     0.0000 : N :   71609  71586 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT BT SA                                                              :      10     -1 :     0.0000 : N :   71575     -1 : C2EXC  
        TO BT BT BT BT BT BT SA                                                                          :       3      9 :     0.0000 : N :   73056  72037 : C2EXC  
        TO BT BT BT BR BT SA                                                                             :       7      6 :     0.0000 : N :   71823  71822 : C2EXC  
        TO BT BT BT BR BT BT SA                                                                          :       7     -1 :     0.0000 : N :   71566     -1 : C2EXC  
        TO BT BT BT BT BT BR BT BT SA                                                                    :       6     -1 :     0.0000 : N :   71826     -1 : C2EXC  
        TO BT BT BR BT SA                                                                                :       6     -1 :     0.0000 : N :   71755     -1 : C2EXC  
        TO BT BT BR BR BR BT BT SA                                                                       :       1      6 :     0.0000 : N :   71538  71539 : C2EXC  
        TO BT BT BT BT BT BT EC                                                                          :       3      5 :     0.0000 : N :   73281  73281 : C2EXC  
        TO BT BT BT BT BR BT BR BT SA                                                                    :       4     -1 :     0.0000 : N :   71638     -1 : C2EXC  
        TO BT BT BT BT BR BT BT BT SA                                                                    :       4     -1 :     0.0000 : N :   71732     -1 : C2EXC  
        TO BT AB                                                                                         :       3      2 :     0.0000 : N :   71659  73136 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT SA                                                                 :       2      3 :     0.0000 : N :   73277  71837 : C2EXC  
        TO BT SC BT SA                                                                                   :      -1      2 :     0.0000 : N :      -1  71976 : C2EXC  
        TO BT BT BT BR BR BR BT BT AB                                                                    :       2     -1 :     0.0000 : N :   72044     -1 : C2EXC  
        TO BT BT BT BT BT BT BR BT BT BT BT SA                                                           :      -1      2 :     0.0000 : N :      -1  73279 : C2EXC  
        TO BT BT BT BT BT BT BT EC                                                                       :       2     -1 :     0.0000 : N :   73282     -1 : C2EXC  
        TO BT BT BT BT BT BT BT SA                                                                       :       2     -1 :     0.0000 : N :   73278     -1 : C2EXC  
        TO BT BT BT BR BT BT BT AB                                                                       :      -1      2 :     0.0000 : N :      -1  73062 : C2EXC  
        TO BT BT BR BT BT AB                                                                             :       2      2 :     0.0000 : N :   71753  72046 : C2EXC  
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :      -1      2 :     0.0000 : N :      -1  71696 : C2EXC  
        TO BT BT BT BT BR BT BT BR BT BT SA                                                              :       1      2 :     0.0000 : N :   73095  71614 : C2EXC  
        TO BT BR BT AB                                                                                   :       2      2 :     0.0000 : N :   71531  71533 : C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 86 NUM_MAX 40 num 86 opt AZERO mode 1
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 86 NUM_MAX 40 num 86 opt BZERO mode 2
        TO BT BT BT BT BT SA                                                                             :      64     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
        TO BT BT BT SA                                                                                   :      59     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
        TO BT BT BT BT BT AB                                                                             :      23     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 86 NUM_MAX 40 num 86 opt DEVIANT mode 5
    :r:`TO BT BT BT BT SA                                                                                :     154    224 :    12.9630 : Y :   71432  71433 : DEVIANT  `
    :r:`TO BT BT SA                                                                                      :      79    131 :    12.8762 : Y :   71342  71342 : DEVIANT  `
    :r:`TO BT BT AB                                                                                      :      63    108 :    11.8421 : Y :   71358  71344 : DEVIANT  `
    ]sseq_index_ab::desc

    ]sseq_index_test.cc
    pvplt MODE:2 
    [sseq_index_test.py




ipc env_sab::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO SA                                                                                          ' ' 0' ' 85301  85454' ' 0.1371' '     0      0']
     [' 1' 'TO AB                                                                                          ' ' 1' ' 13861  13716' ' 0.7624' '     1      1']

     [' 2' 'TO BT BT BT BT SA                                                                              ' ' 2' '   154    224' '12.9630' ' 71432  71433']
     [' 3' 'TO BT BT SA                                                                                    ' ' 3' '    79    131' '12.8762' ' 71342  71342']

     [' 4' 'TO BT BT BT BT EC                                                                              ' ' 4' '    96    117' ' 2.0704' ' 71553  71555']
     [' 5' 'TO BT BT AB                                                                                    ' ' 5' '    63    108' '11.8421' ' 71358  71344']
     [' 6' 'TO BT BT BT BT BT SA                                                                           ' ' 6' '    64      0' '64.0000' ' 71455     -1']
     [' 7' 'TO BT BT BT BT AB                                                                              ' ' 7' '    40     59' ' 3.6465' ' 71440  71432']
     [' 8' 'TO BT BT BT SA                                                                                 ' ' 8' '    59      0' '59.0000' ' 71352     -1']
     [' 9' 'TO BT BT BR BT BT SA                                                                           ' ' 9' '    30     40' ' 1.4286' ' 71537  71534']
     ['10' 'TO BT BT BT AB                                                                                 ' '10' '    39      1' '36.1000' ' 71392  73345']
     ['11' 'TO BT BT BT BT BT EC                                                                           ' '11' '    38      0' '38.0000' ' 71554     -1']
     ['12' 'TO BT BT BT BT BR BT BT BT BT SA                                                               ' '12' '    20     35' ' 4.0909' ' 71583  71580']
     ['13' 'TO BT BT BT BT BT AB                                                                           ' '13' '    23      0' ' 0.0000' ' 71434     -1']
     ['14' 'TO BT BR BT SA                                                                                 ' '14' '    12     17' ' 0.0000' ' 71532  71537']
     ['15' 'TO BT BT BT BR BT BT BT SA                                                                     ' '15' '    10     13' ' 0.0000' ' 71561  71549']
     ['16' 'TO BT BT BT BT BR BT BT SA                                                                     ' '16' '     7     12' ' 0.0000' ' 71824  71825']
     ['17' 'TO BT BT BT BT EX                                                                              ' '17' '     5     10' ' 0.0000' ' 71609  71586']
     ['18' 'TO BT BT BT BT BT BR BT BT BT BT SA                                                            ' '18' '    10      0' ' 0.0000' ' 71575     -1']
     ['19' 'TO BT BT BT BT BT BT SA                                                                        ' '19' '     3      9' ' 0.0000' ' 73056  72037']
     ['20' 'TO BT BT BT BR BT BT SA                                                                        ' '20' '     7      0' ' 0.0000' ' 71566     -1']
     ['21' 'TO BT BT BT BR BT SA                                                                           ' '21' '     7      6' ' 0.0000' ' 71823  71822']
     ['22' 'TO BT BT BR BR BR BT BT SA                                                                     ' '22' '     1      6' ' 0.0000' ' 71538  71539']
     ['23' 'TO BT BT BR BT SA                                                                              ' '23' '     6      0' ' 0.0000' ' 71755     -1']
     ['24' 'TO BT BT BT BT BT BR BT BT SA                                                                  ' '24' '     6      0' ' 0.0000' ' 71826     -1']
     ['25' 'TO BT BT BT BT BT BT EC                                                                        ' '25' '     3      5' ' 0.0000' ' 73281  73281']
     ['26' 'TO BT BT BT BT BR BT BR BT SA                                                                  ' '26' '     4      0' ' 0.0000' ' 71638     -1']
     ['27' 'TO BT BT BT BT BR BT BT BT SA                                                                  ' '27' '     4      0' ' 0.0000' ' 71732     -1']
     ['28' 'TO BT AB                                                                                       ' '28' '     3      2' ' 0.0000' ' 71659  73136']
     ['29' 'TO BT BT BT BT BT BR BT BT BT SA                                                               ' '29' '     2      3' ' 0.0000' ' 73277  71837']
     ['30' 'TO BT SC BT SA                                                                                 ' '30' '     0      2' ' 0.0000' '    -1  71976']
     ['31' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '31' '     0      2' ' 0.0000' '    -1  71696']
     ['32' 'TO BT BT BT BR BT BT BT AB                                                                     ' '32' '     0      2' ' 0.0000' '    -1  73062']
     ['33' 'TO BT BT BT BT BR BT BT BR BT BT SA                                                            ' '33' '     1      2' ' 0.0000' ' 73095  71614']
     ['34' 'TO BT BT BT BR BR BR BT BT AB                                                                  ' '34' '     2      0' ' 0.0000' ' 72044     -1']
     ['35' 'TO BT BT BT BT BT BT BT SA                                                                     ' '35' '     2      0' ' 0.0000' ' 73278     -1']
     ['36' 'TO BT BT BT BT BT BT BT EC                                                                     ' '36' '     2      0' ' 0.0000' ' 73282     -1']
     ['37' 'TO BT BT BT BT BT BT BR BT BT BT BT SA                                                         ' '37' '     0      2' ' 0.0000' '    -1  73279']
     ['38' 'TO BT BT BR BT BT AB                                                                           ' '38' '     2      2' ' 0.0000' ' 71753  72046']
     ['39' 'TO BT BR BT AB                                                                                 ' '39' '     2      2' ' 0.0000' ' 71531  71533']]



BZERO might be informative
-------------------------------

::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [[' 6' 'TO BT BT BT BT BT SA                                                                           ' ' 6' '    64      0' '64.0000' ' 71455     -1']
     [' 8' 'TO BT BT BT SA                                                                                 ' ' 8' '    59      0' '59.0000' ' 71352     -1']
     ['11' 'TO BT BT BT BT BT EC                                                                           ' '11' '    38      0' '38.0000' ' 71554     -1']
     ['13' 'TO BT BT BT BT BT AB                                                                           ' '13' '    23      0' ' 0.0000' ' 71434     -1']]


    AB
    [sseq_index_ab::desc u_size 86 NUM_MAX 40 num 86 opt BZERO mode 2
        TO BT BT BT BT BT SA                                                                             :      64     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
        TO BT BT BT SA                                                                                   :      59     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
        TO BT BT BT BT BT AB                                                                             :      23     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc



"TO BT BT BT SA"  : crossing virtual wrapper of WP_PMT : would expect 2 BT not 3 ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    In [2]: w = a.q_startswith("TO BT BT BT SA") ; w
    Out[2]: 
    array([71352, 71355, 71357, 71362, 71372, 71373, 71374, 71380, 71384, 71393, 71405, 71407, 71409, 71411, 71427, 71431, 72062, 72064, 72078, 72084, 72085, 72090, 72092, 72094, 72106, 72962, 72964,
           72971, 72977, 72995, 73000, 73004, 73020, 73384, 73387, 73388, 73391, 73645, 73652, 73661, 73665, 73669, 73674, 73681, 73686, 73695, 73699, 73701, 73712, 73715, 73716, 73723, 73728, 73733,
           73742, 73745, 73750, 73754, 73767])


Those are clipping a PMT in the middle on the way from the top of pool to the  bottom,
with the first two BT very close to each other::

    In [6]: a.f.record[w,:5,0]
    Out[6]: 
    array([[[  3231.987,  20623.73 ,  20513.072,      0.1  ],
            [ -1666.483,  20623.73 ,   -486.647,     99.512],
            [ -1666.495,  20623.73 ,   -486.698,     99.512],
            [ -1670.96 ,  20623.73 ,   -505.842,     99.603],
            [ -6586.672,  20623.73 , -21579.48 ,    199.365]],

           [[  3232.078,  20623.73 ,  20513.05 ,      0.1  ],
            [ -1662.498,  20623.73 ,   -487.871,     99.513],
            [ -1662.51 ,  20623.73 ,   -487.924,     99.514],
            [ -1668.199,  20623.73 ,   -512.333,     99.629],
            [ -6586.664,  20623.732, -21615.752,    199.528]],

           [[  3232.139,  20623.73 ,  20513.037,      0.1  ],
            [ -1659.851,  20623.73 ,   -488.727,     99.515],
            [ -1659.862,  20623.73 ,   -488.777,     99.515],
            [ -1666.363,  20623.73 ,   -516.686,     99.647],
            [ -6586.671,  20623.73 , -21640.02 ,    199.637]],

           [[  3232.292,  20623.73 ,  20513.   ,      0.1  ],
            [ -1653.256,  20623.73 ,   -490.974,     99.518],
            [ -1653.27 ,  20623.73 ,   -491.035,     99.518],
            [ -1661.761,  20623.73 ,   -527.54 ,     99.691],
            [ -6574.87 ,  20623.73 , -21650.   ,    199.669]],

           [[  3232.598,  20623.73 ,  20512.93 ,      0.1  ],
            [ -1640.194,  20623.73 ,   -496.014,     99.527],
            [ -1640.212,  20623.73 ,   -496.095,     99.527],
            [ -1652.542,  20623.73 ,   -549.253,     99.779],
            [ -6546.626,  20623.729, -21650.   ,    199.64 ]],

           ...,

           [[  3306.112,  20623.73 ,  20501.559,      0.1  ],
            [  1644.053,  20623.73 ,   -494.406,     97.199],
            [  1644.049,  20623.73 ,   -494.464,     97.199],
            [  1636.767,  20623.73 ,   -586.454,     97.624],
            [   -30.642,  20623.732, -21650.   ,    195.035]],

           [[  3306.206,  20623.73 ,  20501.553,      0.1  ],
            [  1648.262,  20623.73 ,   -492.74 ,     97.189],
            [  1648.255,  20623.73 ,   -492.826,     97.19 ],
            [  1641.801,  20623.73 ,   -574.555,     97.568],
            [   -22.552,  20623.734, -21649.998,    195.033]],

           [[  3306.363,  20623.73 ,  20501.54 ,      0.1  ],
            [  1655.256,  20623.73 ,   -490.195,     97.175],
            [  1655.249,  20623.73 ,   -490.283,     97.176],
            [  1650.173,  20623.73 ,   -554.822,     97.474],
            [    -9.071,  20623.725, -21649.998,    195.028]],

           [[  3306.488,  20623.73 ,  20501.53 ,      0.1  ],
            [  1660.835,  20623.73 ,   -488.356,     97.165],
            [  1660.83 ,  20623.73 ,   -488.411,     97.165],
            [  1656.863,  20623.73 ,   -539.02 ,     97.399],
            [     1.716,  20623.74 , -21650.   ,    195.024]],

           [[  3306.895,  20623.73 ,  20501.498,      0.1  ],
            [  1678.894,  20623.73 ,   -483.188,     97.135],
            [  1678.888,  20623.73 ,   -483.277,     97.135],
            [  1678.521,  20623.73 ,   -488.001,     97.157],
            [    36.765,  20623.74 , -21650.   ,    195.011]]], shape=(59, 5, 4), dtype=float32)

    In [7]: 



    In [8]: a.f.record[w,:5,3,0].view(np.uint32) >> 16
    Out[8]: 
    array([[  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],
           [  0, 295, 295, 295,  25],


Clipping the virtual wrapper of the PMT::

    In [9]: cf.sim.stree.standard.bd_names[295]
    Out[9]: np.str_('vetoWater///Water')

    In [10]: cf.sim.stree.standard.bd_names[25]
    Out[10]: np.str_('Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater')


    MOI=1678.888,20623.73,-483.277,500 ssst.sh


    In [12]: a.f.record[w,:5,3,1].view(np.uint32)
    Out[12]: 
    array([[    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51231, 51231, 51231,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51230, 51230, 51230,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51003, 51003, 51003,     0],
           [    0, 51225, 51225, 51225,     0],
           [    0, 51225, 51225, 51225,     0],
           [    0, 51225, 51225, 51225,     0],
           [    0, 51225, 51225, 51225,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0],
           [    0, 51224, 51224, 51224,     0]], dtype=uint32)









Before "WaterPoolConstruction2" FIX, ipc env_chi2::

    [sseq_index_test.cc
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000/seq.npy a_seq (100000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000/seq.npy b_seq (100000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1751455593420587
     t1 1751455593427498 (t1 - t0)     6911 0.006911
     t2 1751455593437784 (t2 - t1)    10286 0.010286
     t3 1751455593437853 (t3 - t2)       69 0.000069
    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1923.0197 ndf 12.0000 sum/ndf   160.2516 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT SA                                                                                         :   38156  44430 :   476.6313 : Y :    3160   3160 : DEVIANT  `
        TO SA                                                                                            :   39084  39241 :     0.3147 : Y :       0      0 :   
    :r:`TO AB                                                                                            :   17552  13928 :   417.1975 : Y :       1     40 : DEVIANT  `
        TO BR SA                                                                                         :    3607     -1 :     0.0000 : N :    3163     -1 : BZERO C2EXC  
    :r:`TO BT AB                                                                                         :      97   1250 :   986.9406 : Y :    3833   3202 : DEVIANT  `
        TO BR AB                                                                                         :     662     -1 :     0.0000 : N :    4203     -1 : BZERO C2EXC  
        TO BT BR SA                                                                                      :      -1    317 :     0.0000 : N :      -1   3303 : AZERO C2EXC  
        TO BT BT BT BT EC                                                                                :      96    145 :     9.9627 : Y :   71553  71574 :   
        TO BT BT BT BT SA                                                                                :     112    129 :     1.1992 : Y :   71372  71556 :   
        TO BT BT AB                                                                                      :     125    104 :     1.9258 : Y :   71358  71346 :   
        TO BT BT BT AB                                                                                   :      86    117 :     4.7340 : Y :   71362  71368 :   
        TO BT BT BT BT AB                                                                                :      79     64 :     1.5734 : Y :   71432  71432 :   
        TO BT BT BT BT BT AB                                                                             :      41     71 :     8.0357 : Y :   71434  71434 :   
        TO BT BT BT BT BT SA                                                                             :      55     -1 :     0.0000 : N :   71448     -1 : BZERO C2EXC  
    :r:`TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     51 :    13.5352 : Y :   71583  71566 : DEVIANT  `
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
        TO BT BT BR BT BT SA                                                                             :      29     37 :     0.9697 : Y :   71537  71538 :   
        TO BT BT BT SA                                                                                   :      16      2 :     0.0000 : N :   71352  71365 : C2EXC  
        TO BT BT BT BR BT BT BT SA                                                                       :      10     12 :     0.0000 : N :   71561  71571 : C2EXC  
        TO BT BR BT SA                                                                                   :      12     12 :     0.0000 : N :   71532  71557 : C2EXC  
        TO BT BT BT BT BR BT BT SA                                                                       :       7     10 :     0.0000 : N :   71824  71825 : C2EXC  
        TO BT BT BT BT EX                                                                                :       5      9 :     0.0000 : N :   71609  71903 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT BT SA                                                              :       9     -1 :     0.0000 : N :   71575     -1 : C2EXC  
        TO BT BT SA                                                                                      :       4      9 :     0.0000 : N :   71342  71343 : C2EXC  
        TO BT BT BT BR BT BT SA                                                                          :       7     -1 :     0.0000 : N :   71566     -1 : C2EXC  
        TO BT BT BT BR BT SA                                                                             :       7      4 :     0.0000 : N :   71823  71822 : C2EXC  
        TO BT BT BT BT BT BT SA                                                                          :       6      7 :     0.0000 : N :   71509  71548 : C2EXC  
        TO BT BT BR BT SA                                                                                :       6     -1 :     0.0000 : N :   71755     -1 : C2EXC  
        TO BT BT BT BT BT BR BT BT SA                                                                    :       6     -1 :     0.0000 : N :   71826     -1 : C2EXC  
        TO BT BT BR BT BT AB                                                                             :       2      6 :     0.0000 : N :   71753  71755 : C2EXC  
        TO BT BT BT BT BT BT EC                                                                          :       3      5 :     0.0000 : N :   73281  73280 : C2EXC  
        TO BT BT BT BT BR BR BR BT BT SA                                                                 :       1      4 :     0.0000 : N :   71834  71826 : C2EXC  
        TO BT BT BT BT BR BT BR BT SA                                                                    :       4     -1 :     0.0000 : N :   71638     -1 : C2EXC  
        TO BT BT BT BT BR BT BT BT SA                                                                    :       4     -1 :     0.0000 : N :   71732     -1 : C2EXC  
        TO BT BT BR BR BR BT BT SA                                                                       :       1      3 :     0.0000 : N :   71538  71759 : C2EXC  
        TO BT BT BT BT BT BR BT BT BT SA                                                                 :       2      2 :     0.0000 : N :   73277  73292 : C2EXC  
        TO BT BT BT BT BT BT BT SA                                                                       :       2     -1 :     0.0000 : N :   73278     -1 : C2EXC  
        TO BT BT BT BT BT BT BT EC                                                                       :       2     -1 :     0.0000 : N :   73282     -1 : C2EXC  
        TO BT BT BT BR BR BR BT BT AB                                                                    :       2     -1 :     0.0000 : N :   72044     -1 : C2EXC  
        TO BT BT BR BR BR BR BR BT BT BT BT BT BT EC                                                     :      -1      2 :     0.0000 : N :      -1  72051 : C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt AZERO mode 1
        TO BT BR SA                                                                                      :      -1    317 :     0.0000 : N :      -1   3303 : AZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt BZERO mode 2
        TO BR SA                                                                                         :    3607     -1 :     0.0000 : N :    3163     -1 : BZERO C2EXC  
        TO BR AB                                                                                         :     662     -1 :     0.0000 : N :    4203     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SA                                                                             :      55     -1 :     0.0000 : N :   71448     -1 : BZERO C2EXC  
        TO BT BT BT BT BT EC                                                                             :      38     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 104 NUM_MAX 40 num 104 opt DEVIANT mode 5
    :r:`TO BT SA                                                                                         :   38156  44430 :   476.6313 : Y :    3160   3160 : DEVIANT  `
    :r:`TO AB                                                                                            :   17552  13928 :   417.1975 : Y :       1     40 : DEVIANT  `
    :r:`TO BT AB                                                                                         :      97   1250 :   986.9406 : Y :    3833   3202 : DEVIANT  `
    :r:`TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     51 :    13.5352 : Y :   71583  71566 : DEVIANT  `
    ]sseq_index_ab::desc

    ]sseq_index_test.cc
    pvplt MODE:2 



EVT::

     58     elif [ "$check" == "poolcover_ipc" ]; then
     59 
     60         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000
     61         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000




alt-A alt-B alt-T alt-M examine the record animation with ssst.sh
-------------------------------------------------------------------

B side has no immediate BR reflection, A side does that lots : but apex hole.

EVT::

     58     elif [ "$check" == "poolcover_ipc" ]; then
     59 
     60         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000
     61         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000
     62 
     63         export AFOLD_RECORD_SLICE="TO BR SA"



ipc env_pdb::

    In [14]: a.f.record[w,:3,3,0].view(np.uint32) >> 16
    Out[14]: 
    array([[ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           ...,
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25],
           [ 0, 24, 25]], shape=(3607, 3), dtype=uint32)



    In [15]: w = a.q_startswith("TO BR SA") ; w
    Out[15]: array([ 3163,  3165,  3168,  3170,  3171, ..., 48936, 48939, 48951, 48954, 48956], shape=(3607,))



    In [18]: np.unique( a.f.record[w,1,3,0].view(np.uint32) >> 16, return_counts=True )
    Out[18]: (array([24], dtype=uint32), array([3607]))

    In [19]: np.unique( a.f.record[w,2,3,0].view(np.uint32) >> 16, return_counts=True )
    Out[19]: (array([25], dtype=uint32), array([3607]))


HMM those boundaries look the wrong way around::

    In [20]: cf.sim.stree.standard.bd_names[24]
    Out[20]: np.str_('DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek')

    In [21]: cf.sim.stree.standard.bd_names[25]
    Out[21]: np.str_('Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater')

    In [23]: cf.sim.stree.standard.bd_names[23]
    Out[23]: np.str_('Air///DeadWater')

    In [24]: cf.sim.stree.standard.bd_names[26]
    Out[24]: np.str_('vetoWater/Implicit_RINDEX_NoRINDEX_pWaterPool_GZ1.A01_02_HBeam_phys//LatticedShellSteel')



BP=WaterPoolConstruction::makeWPLogical_hierarchy ipc
---------------------------------------------------------

jcv WaterPoolConstruction2::

   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  solid             |    z0                                                       |      z1                                                     |     r                                                |   
   +====================+=============================================================+=============================================================+======================================================+
   |  sAirGap           |   -m_heightWP/2                                             |    m_heightWP/2 + m_airGapThickness                         |   m_radWP    *COIN*                                  |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sDeadWater_shell  |   -m_heightWP/2                                             |    m_heightWP/2                                             |   m_radWP    *COIN*                                  |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sTyvek_shell      |   -m_heightWP/2 + m_deadWaterThickness - m_tyvekThickness   |    m_heightWP/2 - m_deadWaterThickness +  m_tyvekThickness  |   m_radWP - m_deadWaterThickness + m_tyvekThickness  |
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+
   |  sOuterWaterPool   |   -m_heightWP/2                                             |    m_heightWP/2                                             |   m_radWP - m_deadWaterThickness                     |   
   +--------------------+-------------------------------------------------------------+-------------------------------------------------------------+------------------------------------------------------+


::

    (gdb) p m_heightWP
    $1 = 43500
    (gdb) p m_heightWP/2
    $2 = 21750
    (gdb) p m_airGapThickness
    $3 = 500
    (gdb) p m_radWP
    $4 = 21750
    (gdb) p m_deadWaterThickness
    $5 = 100
    (gdb) p m_tyvekThickness
    $6 = 2
    (gdb) 
  

                                                                                                                    + m_radWP - m_deadWaterThickness
                                                                                                                    : 
                                                                                                                    :
                                                                                                                    : + m_radWP - m_deadWaterThickness + m_tyvekThickness
                                                                                                                    : :
                                                                                                                    : :   + m_radWP
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                                                                    : :   :
                                                                    0                                               : :   :
               +-----------Air--------------------------------------|-----------------------------------------------:-:---+     m_heightWP/2 + m_airGapThickness
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               |                                                    |                                               : :   |
               +---------DeadWater----------------------------------|-----------------------------------------------:-:---+     m_heightWP/2
               |                                                    |                                               : :   |    
               |   +------Tyvek-------------------------------------|-----------------Tyvek-------------------------:-+   |     m_heightWP/2 - m_deadWaterThickness + m_tyvekThickness 
               |   | +-------vetoWater------------------------------|-----------------------------------------------+ |   |     m_heightWP/2 - m_deadWaterThickness  (TOFIX)
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |   
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | |                                              |                                               | |   |
               |   | +------vetoWater-------------------------------|------------------vetoWater--------------------+ |   |    -m_heightWP/2 + m_deadWaterThickness - m_tyvekThickness
               |   +-----Tyvek--------------------------------------|-------------------------------------------------+   |    -m_heightWP/2 + m_deadWaterThickness (TOFIX)
               |                                                    |                                                     |    
               +---------DeadWater----------------------------------|-----------------------------------------------------+    -m_heightWP/2
                                                                    0 

Expect Air DeadWater coincidence should not matter as stopped at Tyv.


