InputPhotonsCheck_WP_virtualwrapper_touching
================================================


ipcv::

    223     elif [ "$TEST" == "WP_PMT_SEMI" ]; then
    224
    225        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    226        opticks_input_photon=SemiCircleXZ_R-500_100k_f8.npy
    227        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    228        observation=""



Using SemiCircle input photons onto WP_PMT gives OK CHI2
BUT quite a few BZERO (Opticks-only) histories


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    58.2633 ndf 64.0000 sum/ndf     0.9104 </span> ]
    TO BT BT BT BT SA                                                                                :   26918  26986 :     0.0858 : Y :       2      2 :    
    TO BT BT BT BT EC                                                                                :   25676  25837 :     0.5032 : Y :      15     27 :    
    TO BT BT BT BT BT SR SA                                                                          :   10281  10314 :     0.0529 : Y :      57    205 :    
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9972  10021 :     0.1201 : Y :    1668   1665 :    
    TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    8187   8225 :     0.0880 : Y :    7251   7262 :    
    TO BT BT BT BT BT SA                                                                             :    2686   2623 :     0.7476 : Y :      32     19 :    
    TO BT BT BT BT BT SR BR SR SA                                                                    :    2418   2400 :     0.0672 : Y :    7328   7099 :    
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    2047   1929 :     3.5020 : Y :    9325   9317 :    
    TO BT BT BT BT EX                                                                                :    1896   1862 :     0.3076 : Y :       7      3 :    
    TO BT BT BT BT BT SR BR SA                                                                       :     823    816 :     0.0299 : Y :    3687   3693 :    
    TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     740    712 :     0.5399 : Y :    8209   8570 :    
    TO BT BT BT BT BT SR SR SA                                                                       :     632    660 :     0.6068 : Y :      83    116 :    
    TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     576    632 :     2.5960 : Y :    8515   8566 :    
    TO AB                                                                                            :     587    592 :     0.0212 : Y :      25     96 :    
    TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     456    419 :     1.5646 : Y :    3695   4870 :    
    TO BT BT BT BT BR BT BT BT BT AB                                                                 :     355    351 :     0.0227 : Y :     374     23 :    
    TO BT BT BT BT AB                                                                                :     298    309 :     0.1993 : Y :     199    239 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT SA                                                     :     297    266 :     1.7069 : Y :    5807   5807 :    
    TO BT BR BT SA                                                                                   :     270    291 :     0.7861 : Y :    2273   1760 :    
    TO BT BT BR BT BT SA                                                                             :     279    270 :     0.1475 : Y :    3312   1779 :    
    TO BT BT BT BR BT BT BT SA                                                                       :     244    234 :     0.2092 : Y :    2006   1988 :    
    TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     200    192 :     0.1633 : Y :    8372   9199 :    
    TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     178    181 :     0.0251 : Y :    8682   8350 :    
    TO BT BT BT BT BT SR BR SR BR SA                                                                 :     177    176 :     0.0028 : Y :    7958   7788 :    
    TO BT BT BT BT BT SR SR BR SR SA                                                                 :     159    163 :     0.0497 : Y :     999    917 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT SA                                               :     126    138 :     0.5455 : Y :    3697   3692 :    
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT EC                                               :     111    133 :     1.9836 : Y :    3733   3698 :    
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SA                                                  :     101    121 :     1.8018 : Y :    2557   2542 :    
    TO BT BT BT BT BT SR SR BR SR BT BT BT BT BT SA                                                  :     102    114 :     0.6667 : Y :    1424   1389 :    
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT SA                                            :      92    112 :     1.9608 : Y :     781    786 :    
    ...
    </pre>

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    TO BT BT BT SA                                                                                   :      45     -1 :     0.0000 : N :       3     -1 : BZERO C2EXC  
    TO BT BT BT EC                                                                                   :      38     -1 :     0.0000 : N :   49757     -1 : BZERO C2EXC  
    TO BT BT BT BT SR SA                                                                             :      17     -1 :     0.0000 : N :   49855     -1 : BZERO C2EXC  
    TO BT BT BT BT BT SR SR SR AB                                                                    :      17     -1 :     0.0000 : N :     706     -1 : BZERO C2EXC  
    TO BT BT BT BT SR BT BT BT BT BT SA                                                              :      15     -1 :     0.0000 : N :   49881     -1 : BZERO C2EXC  
    TO BT BT BT BR BT BT BT BT SA                                                                    :      11     -1 :     0.0000 : N :   49853     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc
    </pre>






EVT::

    elif [ "$EVT_CHECK" == "wp_pmt_semi_ipc" ]; then

        export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_SemiCircleXZ_R-500_100k_f8/A000
        export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_SemiCircleXZ_R-500_100k_f8/B000

        #export AFOLD_RECORD_SLICE="TO BT BT BT SA"    # just apex and waist
        #export AFOLD_RECORD_SLICE="TO BT BT BT EC"    # just apex and waist on one side 
        #export AFOLD_RECORD_SLICE="TO BT BT BT SA,TO BT BT BT EC"   # just apex and waist
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT SR SA"   # from apex crosses vacuum SR on bottom and absorbed in way out
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT BT SR SR SR AB"    # in close to waist bounce before absorbed on base
        #export AFOLD_RECORD_SLICE="TO BT BT BT BT SR BT BT BT BT BT SA"  # in thru apex, SR at bottom retrace path out the apex
        #export AFOLD_RECORD_SLICE="TO BT BT BT BR BT BT BT BT SA"    ## in thru apex, reflect before vacuum, and retrace path out 





Viz all those Opticks only histories shows all at apex OR waist.

Adding a BT makes the reason clear::

        export AFOLD_RECORD_SLICE="TO BT BT BT BT SA"
        export BFOLD_RECORD_SLICE="TO BT BT BT BT SA"




branch : blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
--------------------------------------------------------------------------------------------

From branch with::

     43    export WaterPoolConstruction__CONFIG=3                              # HIERARCHY
     44    export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10                  # default 1.e-3
     45    export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10        # default 0.05
     46    export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10             # default 0.05
     47    export R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05




.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    60.5086 ndf 65.0000 sum/ndf     0.9309 </span> ]
    TO BT BT BT BT SA                                                                                :   26964  26997 :     0.0202 : Y :       2      2 :   
    TO BT BT BT BT EC                                                                                :   25721  25839 :     0.2701 : Y :      12     27 :   
    TO BT BT BT BT BT SR SA                                                                          :   10292  10313 :     0.0214 : Y :      23    205 :   
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9983  10018 :     0.0612 : Y :    1668   1664 :   
    TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    8210   8225 :     0.0137 : Y :    7311   7262 :   
    TO BT BT BT BT BT SA                                                                             :    2689   2612 :     1.1185 : Y :       6     19 :   
    TO BT BT BT BT BT SR BR SR SA                                                                    :    2420   2400 :     0.0830 : Y :    7328   7099 :   
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    2052   1929 :     3.8003 : Y :    9325   9317 :   
    TO BT BT BT BT EX                                                                                :    1900   1853 :     0.5886 : Y :       1      3 :   
    TO BT BT BT BT BT SR BR SA                                                                       :     824    821 :     0.0055 : Y :    3687   3693 :   
    TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     744    712 :     0.7033 : Y :    8209   8570 :   
    TO BT BT BT BT BT SR SR SA                                                                       :     631    661 :     0.6966 : Y :      83    116 :   
    TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                               :     576    632 :     2.5960 : Y :    8515   8566 :   
    TO AB                                                                                            :     587    589 :     0.0034 : Y :      25     96 :   
    TO BT BT BT BT BT SR BT BT BT BT BT AB                                                           :     456    420 :     1.4795 : Y :    3695   4870 :   
    TO BT BT BT BT BR BT BT BT BT AB                                                                 :     355    347 :     0.0912 : Y :     374     23 :   
    TO BT BT BT BT AB                                                                                :     298    309 :     0.1993 : Y :     199    239 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT SA                                                     :     297    266 :     1.7069 : Y :    5807   5807 :   
    TO BT BR BT SA                                                                                   :     270    291 :     0.7861 : Y :    2273   1759 :   
    TO BT BT BR BT BT SA                                                                             :     279    270 :     0.1475 : Y :    3312   1778 :   
    TO BT BT BT BR BT BT BT SA                                                                       :     241    234 :     0.1032 : Y :    2006   1987 :   
    TO BT BT BT BT BT SR BR SR BR SR BR SR SA                                                        :     201    192 :     0.2061 : Y :    8372   9199 :   
    TO BT BT BT BT BT SR BR SR BR SR BR SR BT BT BT BT BT SA                                         :     178    181 :     0.0251 : Y :    8682   8350 :   
    TO BT BT BT BT BT SR BR SR BR SA                                                                 :     177    176 :     0.0028 : Y :    7958   7788 :   
    TO BT BT BT BT BT SR SR BR SR SA                                                                 :     158    163 :     0.0779 : Y :     999    920 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT SA                                               :     127    141 :     0.7313 : Y :    3697   3692 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT BT BT EC                                               :     111    130 :     1.4979 : Y :    3733   3698 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SA                                                  :     102    124 :     2.1416 : Y :    2557   2541 :   
    TO BT BT BT BT BT SR SR BR SR BT BT BT BT BT SA                                                  :     102    114 :     0.6667 : Y :    1420   1388 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT SA                                            :      94    110 :     1.2549 : Y :     818    780 :   
    TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT BT EC                                            :      90     91 :     0.0055 : Y :     815    824 :   
    TO BT BT AB                                                                                      :      88     74 :     1.2099 : Y :    2589    300 :   
    TO BT BT BT BT BR BT BT BT BT BT BT SA                                                           :      83     72 :     0.7806 : Y :    1124   1119 :   
    TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :      83     66 :     1.9396 : Y :      27     53 :   
    TO BT BT BT BT BT SR SR SR SA                                                                    :      69     81 :     0.9600 : Y :      46     69 :   
    TO BT BT BT BT BR BT BT BT BT BT BT BT BT EC                                                     :      75     75 :     0.0000 : Y :      17      7 :   
    TO BT BT BT BT BT SR BR SR BT BT BT BT BT AB                                                     :      68     71 :     0.0647 : Y :    9746   8998 :   
    TO BT AB                                                                                         :      70     64 :     0.2687 : Y :    9600   9585 :   
    TO BT BT BT BT BT SR BT BT BT BT BT BT BT AB                                                     :      64     69 :     0.1880 : Y :    4724   5907 :   
    TO BT BT BT BT BT SR BR BR SR SA                                                                 :      46     67 :     3.9027 : Y :    3740   3856 :   
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    TO BT BT BT BT BT SR SR SR AB                                                                    :      17     -1 :     0.0000 : N :     489     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc
    </pre>



ipc env_sab
--------------

::

    QCF qcf :  
    a.q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum :    64.5549 c2n :    72.0000 c2per:     0.8966  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  64.55/72:0.897 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                                                              ' ' 0' ' 26964  26997' ' 0.0202' '     2      2']
     [' 1' 'TO BT BT BT BT EC                                                                              ' ' 1' ' 25721  25839' ' 0.2701' '    12     27']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' ' 10292  10313' ' 0.0214' '    23    205']
     [' 3' 'TO BT BT BT BT BR BT BT BT BT SA                                                               ' ' 3' '  9983  10018' ' 0.0612' '  1668   1664']
     [' 4' 'TO BT BT BT BT BT SR BT BT BT BT BT SA                                                         ' ' 4' '  8210   8225' ' 0.0137' '  7311   7262']
     [' 5' 'TO BT BT BT BT BT SA                                                                           ' ' 5' '  2689   2612' ' 1.1185' '     6     19']
     [' 6' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 6' '  2420   2400' ' 0.0830' '  7328   7099']
     [' 7' 'TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                   ' ' 7' '  2052   1929' ' 3.8003' '  9325   9317']
     [' 8' 'TO BT BT BT BT EX                                                                              ' ' 8' '  1900   1853' ' 0.5886' '     1      3']
     [' 9' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 9' '   824    821' ' 0.0055' '  3687   3693']
     ['10' 'TO BT BT BT BT BT SR BR SR BR SR SA                                                            ' '10' '   744    712' ' 0.7033' '  8209   8570']
     ['11' 'TO BT BT BT BT BT SR SR SA                                                                     ' '11' '   631    661' ' 0.6966' '    83    116']
     ['12' 'TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                             ' '12' '   576    632' ' 2.5960' '  8515   8566']
     ['13' 'TO AB                                                                                          ' '13' '   587    589' ' 0.0034' '    25     96']
     ['14' 'TO BT BT BT BT BT SR BT BT BT BT BT AB                                                         ' '14' '   456    420' ' 1.4795' '  3695   4870']
     ['15' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '15' '   355    347' ' 0.0912' '   374     23']
     ['16' 'TO BT BT BT BT AB                                                                              ' '16' '   298    309' ' 0.1993' '   199    239']



C2CUT=40 ipc sab : matches the C++ : HMM MAYBE SHOULD USE SAME ENVVAR AND DEFAULT FOR C++ AND PY  ? 
------------------------------------------------------------------------------------------------------

::

    QCF qcf :  
    a.q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum :    60.5086 c2n :    65.0000 c2per:     0.9309  C2CUT:   40 
    c2sum/c2n:c2per(C2CUT)  60.51/65:0.931 (40) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                                                              ' ' 0' ' 26964  26997' ' 0.0202' '     2      2']
     [' 1' 'TO BT BT BT BT EC                                                                              ' ' 1' ' 25721  25839' ' 0.2701' '    12     27']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' ' 10292  10313' ' 0.0214' '    23    205']
     [' 3' 'TO BT BT BT BT BR BT BT BT BT SA                                                               ' ' 3' '  9983  10018' ' 0.0612' '  1668   1664']
     [' 4' 'TO BT BT BT BT BT SR BT BT BT BT BT SA                                                         ' ' 4' '  8210   8225' ' 0.0137' '  7311   7262']
     [' 5' 'TO BT BT BT BT BT SA                                                                           ' ' 5' '  2689   2612' ' 1.1185' '     6     19']
     [' 6' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 6' '  2420   2400' ' 0.0830' '  7328   7099']
     [' 7' 'TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                   ' ' 7' '  2052   1929' ' 3.8003' '  9325   9317']
     [' 8' 'TO BT BT BT BT EX                                                                              ' ' 8' '  1900   1853' ' 0.5886' '     1      3']
     [' 9' 'TO BT BT BT BT BT SR BR SA                                                                     ' ' 9' '   824    821' ' 0.0055' '  3687   3693']
     ['10' 'TO BT BT BT BT BT SR BR SR BR SR SA                                                            ' '10' '   744    712' ' 0.7033' '  8209   8570']
     ['11' 'TO BT BT BT BT BT SR SR SA                                                                     ' '11' '   631    661' ' 0.6966' '    83    116']
     ['12' 'TO BT BT BT BT BT SR BR SR BR SR BT BT BT BT BT SA                                             ' '12' '   576    632' ' 2.5960' '  8515   8566']
     ['13' 'TO AB                                                                                          ' '13' '   587    589' ' 0.0034' '    25     96']
     ['14' 'TO BT BT BT BT BT SR BT BT BT BT BT AB                                                         ' '14' '   456    420' ' 1.4795' '  3695   4870']
     ['15' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '15' '   355    347' ' 0.0912' '   374     23']


    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [['74' 'TO BT BT BT BT BT SR SR SR AB                                                                  ' '74' '    17      0' ' 0.0000' '   489     -1']]


    In [1]: wa = a.q_startswith("TO BT BT BT BT BT SR SR SR AB") ; wa.shape
    Out[1]: (17,)

    In [2]: wa
    Out[2]: array([  489,   649,   706,   731,  1204,  1257,  1281,  1566,  1684,  1689,  1834, 98163, 98165, 98290, 98340, 99171, 99351])



Check the B histories of those photons::

    In [3]: b.q[wa]
    Out[3]: 
    array([[b'TO BT BT BT BT BR BT BT BT BT BT BR BT SA                                                       '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT SA                                                          '],
           [b'TO BT BT BT BT BT SR SR BR SR BT BT BT BT BT AB                                                 '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT EX                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO AB                                                                                           ']], dtype='|S96')

    In [4]: 


Look at near histories on A side::

    In [9]: wa = a.q_startswith("TO BT BT BT BT BT SR SR SR" ) ; wa.shape
    Out[9]: (467,)

    In [14]: atab = np.c_[np.unique(a.q[wa],return_counts=True)]

    In [20]: atab[np.argsort(atab[:,1].astype(int))][::-1]
    Out[20]: 
    array([[b'TO BT BT BT BT BT SR SR SR SA                                                                   ', b'69'],
           [b'TO BT BT BT BT BT SR SR SR SR SA                                                                ', b'34'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SA                                                             ', b'20'],
           [b'TO BT BT BT BT BT SR SR SR AB                                                                   ', b'17'],
           [b'TO BT BT BT BT BT SR SR SR BR SR SA                                                             ', b'13'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT EC                                        ', b'12'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT SA                                        ', b'10'],
           [b'TO BT BT BT BT BT SR SR SR SR BT BT BT BT BT BT BT BT BT SA                                     ', b'9'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SA                                                          ', b'9'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BR BT BT BT BT SA                         ', b'8'],
           [b'TO BT BT BT BT BT SR SR SR BR SA                                                                ', b'8'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SR SA                                                       ', b'8'],
           [b'TO BT BT BT BT BT SR SR SR BR AB                                                                ', b'7'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT SA                                           ', b'7'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT SA                                     ', b'7'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SR SR SR SA                                                 ', b'6'],
           [b'TO BT BT BT BT BT SR SR SR SR SR BT BT BT BT BT BT BT BT BT EC                                  ', b'6'],


Ditto on B side::

    In [21]: wb = b.q_startswith("TO BT BT BT BT BT SR SR SR" ) ; wb.shape
    Out[21]: (380,)

    In [22]: btab = np.c_[np.unique(b.q[wb],return_counts=True)]

    In [23]: btab[np.argsort(btab[:,1].astype(int))][::-1]
    Out[23]: 
    array([[b'TO BT BT BT BT BT SR SR SR SA                                                                   ', b'81'],
           [b'TO BT BT BT BT BT SR SR SR SR SA                                                                ', b'35'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SA                                                             ', b'20'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT EC                                        ', b'12'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT SA                                        ', b'12'],
           [b'TO BT BT BT BT BT SR SR SR BR SR SA                                                             ', b'11'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SA                                                          ', b'9'],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT SA                      ', b'8'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SR SR SA                                                    ', b'6'],
           [b'TO BT BT BT BT BT SR SR SR BR SR BR SR SA                                                       ', b'6'],
           [b'TO BT BT BT BT BT SR SR SR SR BT BT BT BT BT BT BT BT BT SA                                     ', b'6'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SR SR SR SR SR SA                                           ', b'6'],
           [b'TO BT BT BT BT BT SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR SR ', b'5'],
           [b'TO BT BT BT BT BT SR SR SR SR BR SR SA                                                          ', b'5'],
           [b'TO BT BT BT BT BT SR SR SR BR SA                                                                ', b'5'],


HMM : NEED MORE STATS TO SEE WHATS GOIN DOWN : IS THE AB WITHIN Pyrex ? SAME ABSLEN ? 





Look for the coincidence in code
---------------------------------

::


    (ok) A[blyth@localhost opticks]$ jgr 20inch_veto
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    (ok) A[blyth@localhost junosw]$ 

    2020         # == enable or disable PMTs in WP ==
    2021         if not args.pmt_optical_model:
    2022             pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    2023             pmt_det_veto.property("UsePMTOpticalModel").set(args.pmt_optical_model)



    1188 void LSExpDetectorConstruction::setupPMT(G4VSensitiveDetector* not_a_leak) {
    1189 
    ...
    1271   // Veto PMT
    1272   if (m_veto_pmt_name == "R12860OnlyFront") {
    1273       pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    1274       assert (pmt_det_veto);
    1275       auto lv = pmt_det_veto->getLV();
    1276       assert (lv);
    1277   } else if (m_veto_pmt_name == "R12860OnlyFrontMask") {
    1278       IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    1279       IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    1280       if (t && mask) {
    1281           // build
    1282           mask->getLV();
    1283           t->getLV();
    1284           pmt_det_veto = dynamic_cast<IPMTElement*>(mask);
    1285           pmt_det_veto->inject("lMaskVirtual", t, 0);
    1286       }
    1287 
    1288       assert(pmt_det_veto);
    1289   } else {
    1290       G4cerr << "Failed to find the VetoPMT named " << m_veto_pmt_name << G4endl;
    1291       assert (pmt_det_veto);
    1292   }


    BP=LSExpDetectorConstruction::setupPMT ipc

    (gdb) p m_pmt_name
    $1 = "PMTMask"
    (gdb) p m_extra_lpmt
    $2 = "TWO-mask"
    (gdb) p m_veto_pmt_name 
    $3 = "R12860OnlyFrontMask"
    (gdb) 


    jcv R12860OnlyFrontPMTManager
    jcv R12860OnlyFrontMaskManager



    153 void
    154 R12860OnlyFrontPMTManager::init_variables() {
    155     m_pmt_r = 254.*mm;
    156     m_pmt_h = 523.*mm;
    157     m_z_equator = 184.*mm; // From top to equator
    158 
    159     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
    160     m_pmtsolid_maker = new R12860OnlyFront_PMTSolid(
    161                             m_pmt_r,
    162                             m_z_equator, // z front
    163                             -10.*mm       // z back (guess). NOTE: it should be nagative.
    164                             );
    165 }


    466 void
    467 R12860OnlyFrontPMTManager::init_cover() {
    468     // solid
    469     double thickness = 1E-3*mm;
    470     G4double zPlane[] = {
    471                         (m_z_equator-m_pmt_h)+thickness,
    472                         m_z_equator+thickness 
    473                         };
    474     G4double rInner[] = {0.,
    475                          0.};
    476     G4double rOuter[] = {m_pmt_r + thickness,
    477                          m_pmt_r + thickness};
    478 
    479     G4VSolid* cover_solid = new G4Polycone(
    480                                 GetName()+"Tubs",
    481                                 0,
    482                                 360*deg,
    483                                 2,
    484                                 zPlane,
    485                                 rInner,
    486                                 rOuter
    487                                 );
    488     // volume
    489     G4LogicalVolume* cover_lv = new G4LogicalVolume
    490         ( cover_solid,
    491           m_cover_mat,
    492           GetName()+"_cover");
    493     // place pmt into the cover
    494     G4ThreeVector noTranslation(0.,0.,0.);
    495     new G4PVPlacement
    496         (0,
    497          noTranslation,
    498          m_logical_pmt,
    499          GetName()+"_cover_phys",
    500          cover_lv,
    501          false,
    502          0
    503         );
    504     
    505     m_logical_pmt = cover_lv;



GEOM cf::

    298 mask_PMT_20inch_vetosMask
    301 mask_PMT_20inch_vetosMask_virtual

    299 PMT_20inch_veto_inner_solid_1_2
    300 PMT_20inch_veto_pmt_solid_1_2



    257 R12860OnlyFrontPMTManager::helper_make_solid()
    258 {
    259     if(m_UsePMTOpticalModel == false)
    260     {
    ...
    281     }
    282     else
    283     {
    284         pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    285         inner_solid = m_pmtsolid_maker->GetSolid(GetName() + "_inner_solid", -5*mm);
    286     }
    287 

    153 void
    154 R12860OnlyFrontPMTManager::init_variables() {
    155     m_pmt_r = 254.*mm;
    156     m_pmt_h = 523.*mm;
    157     m_z_equator = 184.*mm; // From top to equator
    158 
    159     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
    160     m_pmtsolid_maker = new R12860OnlyFront_PMTSolid(
    161                             m_pmt_r,
    162                             m_z_equator, // z front
    163                             -10.*mm       // z back (guess). NOTE: it should be nagative.
    164                             );
    165 }





BP=R12860OnlyFrontPMTManager::helper_make_solid ipc
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (gdb) p m_UsePMTOpticalModel
    $1 = true

    (gdb) p this->GetName()
    $2 = {<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >> = "PMT_20inch_veto", <No data fields>}

    (gdb) p m_pmtsolid_maker
    $3 = (R12860OnlyFront_PMTSolid *) 0xac9f2a0

    (gdb) p m_fast_cover
    $4 = false





    013 #include <cmath>
     14 using namespace CLHEP;
     15 double R12860OnlyFront_PMTSolid::delta_torlerance = 1E-2*mm;
     16 
     17 R12860OnlyFront_PMTSolid::R12860OnlyFront_PMTSolid(
     18         double R1, double zfront, double zback)
     19     : m_R1(R1), m_zfront(zfront), m_zback(zback) {
     20     G4cout << __FILE__ << ":" << __LINE__ << std::endl;
     21 }
     22 
     23 G4VSolid*
     24 R12860OnlyFront_PMTSolid::GetSolid(G4String solidname, double thickness) {
     25     // Calculate Parameter first
     26     double r1t = m_R1 + thickness;
     27     double zft = m_zfront + thickness; // front
     28     double zbt = m_zback - thickness;  // back. Because m_zback<0
     29 
     30     // Show variables
     31     G4cout << "r1t: " << r1t/mm << " mm" << G4endl;
     32     G4cout << "zft: " << zft/mm << " mm" << G4endl;
     33     G4cout << "zbt: " << zbt/mm << " mm" << G4endl;
     34     // Construct the PMT Solid
     35     // * PART 1
     36     // G4Sphere* pmttube_solid_sphere = new G4Sphere(
     37     //                                         solidname+"_1_Sphere",
     38     //                                         0*mm, // R min
     39     //                                         r1t, // R max
     40     //                                         0*deg, // Start Phi
     41     //                                         360*deg, // Delta Phi
     42     //                                         0*deg, // Start Theta
     43     //                                         180*deg  // Delta Theta
     44     //                                         );
     45     G4Ellipsoid* pmttube_solid_sphere = new G4Ellipsoid(
     46                                             solidname+"_1_Front_Ellipsoid",
     47                                             r1t, // pxSemiAxis
     48                                             r1t, // pySemiAxis
     49                                             zft, // pzSemiAxis
     50                                             zbt, // cut at bottom
     51                                             zft  // cut at top
     52                                             );
     53     // * PART 2




HMM : virtual wrapper different from the mask ?
---------------------------------------------------


::

     22 R12860OnlyFrontMaskManager::R12860OnlyFrontMaskManager(const std::string& name)
     23     : ToolBase(name)
     24 {
     25     declProp("BufferMaterial", m_buffer_material = "Water");
     26     declProp("TopThickness", htop_thickness=8.*mm);
     27     declProp("TopGap", htop_gap=2.*mm); // gap between PMT and Mask at top
     28 
     29     declProp("EquatorThickness", requator_thickness=8.*mm); // thickness at equator
     30     declProp("EquatorGap", requator_gap=2.*mm); // gap between PMT and Mask at equator
     31 
     32     logicMaskVirtual = 0;
     33 
     34     MAGIC_virtual_thickness = 0.05*mm;
     35 }




Finding corners and apex with POINT
--------------------------------------


::

    GSGRID=1 PRIMTAB=1 GRID=1 GLOBAL=0 POINT=264.05,0,-24.9,264,0,-24.9,264.05,0,-25.05,-264.05,0,-24.9,-264,0,-24.9,-264.05,0,-25.05,0,0,184,0,0,186,0,0,194,0,0,194.05 POINTSIZE=20 cxt_min.sh pdb


    In [3]: p = np.fromstring("264.05,0,-24.9,264,0,-24.9,264.05,0,-25.05,-264.05,0,-24.9,-264,0,-24.9,-264.05,0,-25.05,0,0,184,0,0,186,0,0,194,0,0,194.05",sep=",").reshape(-1,3)

    In [4]: p
    Out[4]: 
    array([[ 264.05,    0.  ,  -24.9 ],
           [ 264.  ,    0.  ,  -24.9 ],
           [ 264.05,    0.  ,  -25.05],
           [-264.05,    0.  ,  -24.9 ],
           [-264.  ,    0.  ,  -24.9 ],
           [-264.05,    0.  ,  -25.05],
           [   0.  ,    0.  ,  184.  ],
           [   0.  ,    0.  ,  186.  ],
           [   0.  ,    0.  ,  194.  ],
           [   0.  ,    0.  ,  194.05]])



Clearance of 0.050 is not enough, need twice that: 0.100



Follow the pattern
------------------


::

     43    export WaterPoolConstruction__CONFIG=3                        # HIERARCHY
     44    export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3
     45    export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05
     46    export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05


blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
--------------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost junosw]$ js
    /home/blyth/junosw
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (fetch)
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (push)
    On branch blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM
    Your branch is up to date with 'origin/blyth-add-envvar-control-R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Examples/Tutorial/share/opticks_juno.sh
        modified:   Simulation/DetSimV2/PMTSim/include/R12860OnlyFrontMaskManager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/R12860OnlyFrontMaskManager.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    (ok) A[blyth@localhost junosw]$ 





Redo TEST=POOLCOVER ipc : LITTLE DIFFERENCE
-----------------------------------------------


::

    TEST=POOLCOVER ipc env_pdb




.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    65.7112 ndf  9.0000 sum/ndf     7.3012 </span> ]
    TO SA                                                                                            :   85301  85453 :     0.1353 : Y :       0      0 :   
    TO AB                                                                                            :   13861  13716 :     0.7624 : Y :       1      3 :   
    TO BT BT BT BT SA                                                                                :     143    224 :    17.8774 : Y :   71432  71433 : <span class="r">DEVIANT</span>   
    TO BT BT SA                                                                                      :      72    132 :    17.6471 : Y :   71342  71341 : <span class="r">DEVIANT</span>   
    TO BT BT BT BT EC                                                                                :      90    117 :     3.5217 : Y :   71553  71555 :   
    TO BT BT AB                                                                                      :      58    108 :    15.0602 : Y :   71358  71344 : <span class="r">DEVIANT</span>   
    TO BT BT BT BT BT SA                                                                             :      71     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
    TO BT BT BT SA                                                                                   :      68     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
    TO BT BT BT BT AB                                                                                :      40     59 :     3.6465 : Y :   71440  71432 :   
    TO BT BT BT BT BT EC                                                                             :      45     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
    TO BT BT BR BT BT SA                                                                             :      26     40 :     2.9697 : Y :   71537  71534 :   
    TO BT BT BT AB                                                                                   :      38      1 :     0.0000 : N :   71392  73345 : C2EXC  
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     35 :     4.0909 : Y :   71583  71580 :   
    TO BT BT BT BT BT AB                                                                             :      27     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
    TO BT BR BT SA                                                                                   :      11     17 :     0.0000 : N :   71532  71537 : C2EXC  
    TO BT BT BT BR BT BT BT SA                                                                       :      10     13 :     0.0000 : N :   71561  71549 : C2EXC  
    TO BT BT BT BT BR BT BT SA                                                                       :       5     12 :     0.0000 : N :   71835  71825 : C2EXC  
    TO BT BT BT BT BT BR BT BT BT BT SA                                                              :      11     -1 :     0.0000 : N :   71575     -1 : BZERO C2EXC  
    TO BT BT BT BT EX                                                                                :       5     10 :     0.0000 : N :   71609  71586 : C2EXC  


::

    In [3]: wa = a.q_startswith("TO BT BT BT BT SA") ; wa.shape
    Out[3]: (143,)

    In [4]: wb = b.q_startswith("TO BT BT BT BT SA") ; wb.shape
    Out[4]: (224,)


    In [5]: wa = a.q_startswith("TO BT BT BT BT BT SA") ; wa.shape
    Out[5]: (71,)

    In [6]: wb = b.q_startswith("TO BT BT BT BT BT SA") ; wb.shape
    Out[6]: (0,)


The B histories of those 5xBT are 4xBT::

    In [8]: np.unique(b.q[wa],return_counts=True)
    Out[8]: 
    (array([b'TO AB                                                                                           ',
            b'TO BT AB                                                                                        ',
            b'TO BT BT BR BT BT SA                                                                            ',
            b'TO BT BT BT BT AB                                                                               ',
            b'TO BT BT BT BT BR BT BT BT BT SA                                                                ',
            b'TO BT BT BT BT EC                                                                               ',
            b'TO BT BT BT BT EX                                                                               ',
            b'TO BT BT BT BT SA                                                                               '], dtype='|S96'),
     array([24,  1,  1,  6,  2, 12,  2,

::


    In [13]: w54 = np.flatnonzero( np.logical_and( np.char.startswith(a.q, "TO BT BT BT BT BT SA".encode("utf-8")), np.char.startswith(b.q, "TO BT BT BT BT SA".encode("utf-8")) )) ; w54
    Out[13]: array([71464, 71485, 71663, 71678, 71690, 71780, 71782, 71798, 71799, 71803, 71810, 71914, 71918, 71919, 71975, 71978, 72019, 72026, 72032, 73149, 73212, 73344, 73372])


    In [4]: w54 = ab.q_and("TO BT BT BT BT BT SA", "TO BT BT BT BT SA") ; w54
    Out[4]: array([71464, 71485, 71663, 71678, 71690, 71780, 71782, 71798, 71799, 71803, 71810, 71914, 71918, 71919, 71975, 71978, 72019, 72026, 72032, 73149, 73212, 73344, 73372])



Add SAB method for that::

   def q_and(self, a_prefix, b_prefix):
        """  
        :param a_prefix: eg TO BT BT BT BT BT SA
        :param b_prefix: eg TO BT BT BT BT SA
        :return wab: indices where self.a.q startswith a_prefix and self.b.q startswith b_prefix

        For example with input photons which start exactly the same this 
        provides a way to look at history migration, eg an extra BT on one side 
        compared to the other
        """
        return np.flatnonzero( np.logical_and( np.char.startswith(self.a.q, a_prefix.encode("utf-8")), np.char.startswith(self.b.q, b_prefix.encode("utf-8")) ))


i
::


    In [11]: t54 = np.c_[a.f.record[w54,:7,0],b.f.record[w54,:7,0]] ; t54
    Out[11]: 
    array([[[  3235.416,  20623.73 ,  20512.285,      0.1  ,   3235.416,  20623.73 ,  20512.285,      0.1  ],
            [ -1188.089,  20623.73 ,    926.728,     92.668,  -1188.132,  20623.73 ,    926.537,     92.669],
            [ -1188.132,  20623.73 ,    926.537,     92.669,  -1251.53 ,  20623.73 ,    645.835,     93.995],
            [ -1251.53 ,  20623.73 ,    645.835,     93.995,  -1529.175,  20623.73 ,   -583.467,     99.806],
            [ -1529.175,  20623.73 ,   -583.467,     99.806,  -1567.19 ,  20623.73 ,   -751.785,    100.601],
            [ -1567.193,  20623.73 ,   -751.799,    100.601,  -6287.166,  20623.73 , -21650.   ,    199.373],
            [ -6287.166,  20623.73 , -21649.998,    199.373,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3236.06 ,  20623.73 ,  20512.14 ,      0.1  ,   3236.06 ,  20623.73 ,  20512.14 ,      0.1  ],
            [ -1153.963,  20623.73 ,    954.78 ,     92.507,  -1154.008,  20623.73 ,    954.579,     92.508],
            [ -1154.008,  20623.73 ,    954.579,     92.508,  -1232.439,  20623.73 ,    605.175,     94.159],
            [ -1232.439,  20623.73 ,    605.175,     94.159,  -1507.233,  20623.73 ,   -619.022,     99.943],
            [ -1507.233,  20623.73 ,   -619.022,     99.943,  -1547.467,  20623.73 ,   -798.263,    100.79 ],
            [ -1547.467,  20623.73 ,   -798.263,    100.79 ,  -6228.037,  20623.73 , -21650.   ,    199.313],
            [ -6228.038,  20623.736, -21650.002,    199.313,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3241.523,  20623.73 ,  20510.945,      0.1  ,   3241.523,  20623.73 ,  20510.945,      0.1  ],
            [  -912.608,  20623.73 ,    985.094,     92.133,   -912.621,  20623.73 ,    985.032,     92.133],
            [  -912.621,  20623.73 ,    985.032,     92.133,   -937.285,  20623.73 ,    869.103,     92.68 ],
            [  -937.284,  20623.73 ,    869.106,     92.68 ,   -940.252,  20621.441,    855.941,     92.75 ],
            [  -940.251,  20621.443,    855.944,     92.75 ,   -941.301,  20621.545,    850.982,     92.774],
            [  -941.301,  20621.545,    850.982,     92.774,   -943.339,  20620.098,    841.893,     92.822],
            [  -943.339,  20620.1  ,    841.894,     92.822,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3241.984,  20623.73 ,  20510.848,      0.1  ,   3241.984,  20623.73 ,  20510.848,      0.1  ],
            [  -894.467,  20623.73 ,    977.667,     92.149,   -894.483,  20623.73 ,    977.592,     92.149],
            [  -894.483,  20623.73 ,    977.592,     92.149,   -919.146,  20623.73 ,    861.13 ,     92.698],
            [  -919.145,  20623.73 ,    861.133,     92.698,   -922.29 ,  20621.377,    847.848,     92.77 ],
            [  -922.289,  20621.377,    847.852,     92.77 ,   -923.364,  20621.488,    842.715,     92.794],
            [  -923.363,  20621.488,    842.719,     92.794,   -925.523,  20619.992,    833.511,     92.843],
            [  -925.522,  20619.992,    833.514,     92.843,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3242.352,  20623.73 ,  20510.77 ,      0.1  ,   3242.352,  20623.73 ,  20510.77 ,      0.1  ],
            [  -880.165,  20623.73 ,    970.707,     92.167,   -880.192,  20623.73 ,    970.577,     92.167],
            [  -880.192,  20623.73 ,    970.577,     92.167,   -905.042,  20623.73 ,    852.793,     92.722],
            [  -905.041,  20623.73 ,    852.799,     92.722,   -908.361,  20621.283,    839.332,     92.795],
            [  -908.36 ,  20621.283,    839.337,     92.795,   -909.478,  20621.408,    833.942,     92.82 ],
            [  -909.477,  20621.408,    833.947,     92.82 ,   -911.76 ,  20619.842,    824.567,     92.87 ],
            [  -911.759,  20619.842,    824.575,     92.87 ,      0.   ,      0.   ,      0.   ,      0.   ]],

           ...,

           [[  3252.888,  20623.73 ,  20508.664,      0.1  ,   3252.888,  20623.73 ,  20508.664,      0.1  ],
            [  -718.337,  20623.73 ,   -544.286,     98.87 ,   -718.354,  20623.73 ,   -544.378,     98.871],
            [  -718.354,  20623.73 ,   -544.378,     98.871,   -740.634,  20623.73 ,   -662.493,     99.425],
            [  -740.635,  20623.73 ,   -662.498,     99.425,   -745.251,  20620.195,   -677.84 ,     99.509],
            [  -745.252,  20620.195,   -677.843,     99.509,   -747.349,  20620.986,   -690.863,     99.57 ],
            [  -747.35 ,  20620.988,   -690.866,     99.57 ,   -750.758,  20618.334,   -702.175,     99.632],
            [  -750.76 ,  20618.334,   -702.184,     99.632,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3287.572,  20623.73 ,  20503.375,      0.1  ,   3287.572,  20623.73 ,  20503.375,      0.1  ],
            [  1010.078,  20623.73 ,   1001.34 ,     90.62 ,   1010.064,  20623.73 ,   1001.223,     90.62 ],
            [  1010.064,  20623.73 ,   1001.223,     90.62 ,    995.682,  20623.73 ,    878.071,     91.192],
            [   995.682,  20623.73 ,    878.073,     91.192,    994.199,  20621.44 ,    864.66 ,     91.262],
            [   994.2  ,  20621.44 ,    864.661,     91.262,    993.61 ,  20621.54 ,    859.638,     91.286],
            [   993.611,  20621.54 ,    859.638,     91.286,    992.583,  20620.094,    850.389,     91.333],
            [   992.583,  20620.094,    850.392,     91.333,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3289.538,  20623.73 ,  20503.148,      0.1  ,   3289.538,  20623.73 ,  20503.148,      0.1  ],
            [  1088.71 ,  20623.73 ,    987.381,     90.642,   1088.701,  20623.73 ,    987.303,     90.642],
            [  1088.701,  20623.73 ,    987.303,     90.642,   1073.491,  20623.73 ,    852.422,     91.268],
            [  1073.49 ,  20623.73 ,    852.421,     91.268,   1071.283,  20621.092,    838.333,     91.343],
            [  1071.284,  20621.094,    838.336,     91.343,   1070.641,  20621.246,    832.346,     91.371],
            [  1070.641,  20621.248,    832.35 ,     91.371,   1069.127,  20619.537,    822.468,     91.422],
            [  1069.127,  20619.537,    822.47 ,     91.422,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3293.661,  20623.73 ,  20502.701,      0.1  ,   3293.661,  20623.73 ,  20502.701,      0.1  ],
            [  1242.377,  20623.73 ,    850.633,     91.192,   1242.362,  20623.73 ,    850.495,     91.193],
            [  1242.362,  20623.73 ,    850.495,     91.193,   1213.863,  20623.73 ,    577.465,     92.459],
            [  1213.863,  20623.73 ,    577.465,     92.459,   1095.246,  20623.73 ,   -558.935,     97.726],
            [  1095.246,  20623.73 ,   -558.936,     97.726,   1054.283,  20623.73 ,   -951.375,     99.545],
            [  1054.283,  20623.73 ,   -951.374,     99.545,  -1106.241,  20623.73 , -21650.   ,    195.489],
            [ -1106.24 ,  20623.73 , -21650.   ,    195.489,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3294.536,  20623.73 ,  20502.611,      0.1  ,   3294.536,  20623.73 ,  20502.611,      0.1  ],
            [  1267.648,  20623.73 ,    747.738,     91.652,   1267.598,  20623.73 ,    747.251,     91.655],
            [  1267.598,  20623.73 ,    747.252,     91.655,   1260.113,  20623.73 ,    674.303,     91.993],
            [  1260.113,  20623.73 ,    674.302,     91.993,   1128.858,  20623.73 ,   -604.966,     97.921],
            [  1128.858,  20623.73 ,   -604.966,     97.921,   1097.284,  20623.73 ,   -912.696,     99.347],
            [  1097.285,  20623.73 ,   -912.695,     99.347,  -1030.403,  20623.73 , -21650.   ,    195.453],

    In [19]: t54[15:20]
    Out[19]: 
    array([[[ 3251.222, 20623.73 , 20508.982,     0.1  ,  3251.222, 20623.73 , 20508.982,     0.1  ],
            [ -785.251, 20623.73 ,  -498.308,    98.72 ,  -785.267, 20623.73 ,  -498.392,    98.72 ],
            [ -785.267, 20623.73 ,  -498.391,    98.72 ,  -802.939, 20623.73 ,  -590.362,    99.152],
            [ -802.939, 20623.73 ,  -590.365,    99.152,  -805.879, 20621.592,  -603.309,    99.221],
            [ -805.879, 20621.592,  -603.31 ,    99.221,  -806.784, 20621.69 ,  -608.105,    99.244],
            [ -806.784, 20621.688,  -608.106,    99.244,  -808.787, 20620.338,  -617.048,    99.291],
            [ -808.787, 20620.338,  -617.049,    99.291,     0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3252.487, 20623.73 , 20508.74 ,     0.1  ,  3252.487, 20623.73 , 20508.74 ,     0.1  ],
            [ -733.977, 20623.73 ,  -530.633,    98.822,  -733.996, 20623.73 ,  -530.734,    98.822],
            [ -733.996, 20623.73 ,  -530.734,    98.822,  -754.24 , 20623.73 ,  -637.574,    99.324],
            [ -754.24 , 20623.73 ,  -637.575,    99.324,  -758.209, 20620.81 ,  -652.036,    99.402],
            [ -758.21 , 20620.81 ,  -652.038,    99.402,  -759.53 , 20621.088,  -659.549,    99.438],
            [ -759.53 , 20621.086,  -659.55 ,    99.438,  -762.33 , 20619.1  ,  -669.947,    99.493],
            [ -762.331, 20619.098,  -669.949,    99.493,     0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3252.703, 20623.73 , 20508.7  ,     0.1  ,  3252.703, 20623.73 , 20508.7  ,     0.1  ],
            [ -725.516, 20623.73 ,  -537.768,    98.847,  -725.532, 20623.73 ,  -537.848,    98.847],
            [ -725.532, 20623.73 ,  -537.848,    98.847,  -746.733, 20623.73 ,  -650.012,    99.373],
            [ -746.733, 20623.73 ,  -650.012,    99.373,  -751.016, 20620.523,  -664.919,    99.455],
            [ -751.016, 20620.523,  -664.919,    99.455,  -752.594, 20620.951,  -674.211,    99.499],
            [ -752.595, 20620.951,  -674.218,    99.499,  -755.671, 20618.686,  -685.069,    99.557],
            [ -755.672, 20618.686,  -685.076,    99.557,     0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3252.888, 20623.73 , 20508.664,     0.1  ,  3252.888, 20623.73 , 20508.664,     0.1  ],
            [ -718.337, 20623.73 ,  -544.286,    98.87 ,  -718.354, 20623.73 ,  -544.378,    98.871],
            [ -718.354, 20623.73 ,  -544.378,    98.871,  -740.634, 20623.73 ,  -662.493,    99.425],
            [ -740.635, 20623.73 ,  -662.498,    99.425,  -745.251, 20620.195,  -677.84 ,    99.509],
            [ -745.252, 20620.195,  -677.843,    99.509,  -747.349, 20620.986,  -690.863,    99.57 ],
            [ -747.35 , 20620.988,  -690.866,    99.57 ,  -750.758, 20618.334,  -702.175,    99.632],
            [ -750.76 , 20618.334,  -702.184,    99.632,     0.   ,     0.   ,     0.   ,     0.   ]],

           [[ 3287.572, 20623.73 , 20503.375,     0.1  ,  3287.572, 20623.73 , 20503.375,     0.1  ],
            [ 1010.078, 20623.73 ,  1001.34 ,    90.62 ,  1010.064, 20623.73 ,  1001.223,    90.62 ],
            [ 1010.064, 20623.73 ,  1001.223,    90.62 ,   995.682, 20623.73 ,   878.071,    91.192],
            [  995.682, 20623.73 ,   878.073,    91.192,   994.199, 20621.44 ,   864.66 ,    91.262],
            [  994.2  , 20621.44 ,   864.661,    91.262,   993.61 , 20621.54 ,   859.638,    91.286],
            [  993.611, 20621.54 ,   859.638,    91.286,   992.583, 20620.094,   850.389,    91.333],
            [  992.583, 20620.094,   850.392,    91.333,     0.   ,     0.   ,     0.   ,     0.   ]]], dtype=float32)
            [ -1030.399,  20623.73 , -21649.998,    195.453,      0.   ,      0.   ,      0.   ,      0.   ]]], shape=(23, 7, 8), dtype=float32)



In every case the 2nd BT on A side is very close to the first BT on B side (double precision Geant4)

Possible explanation::

    Intersecting WP_PMT from 20,000mm away yields first intersect of lesser precision. Subsequent
    intersect in same direction from the first imprecise intersect is over a distance of less than
    0.5 mm getting very close to the double precision intersect from the B side. 
    

::

    In [24]: t54[0,2,:3]
    Out[24]: array([-1188.132, 20623.73 ,   926.537], dtype=float32)

    In [25]: t54[0,1,4:7]
    Out[25]: array([-1188.132, 20623.73 ,   926.537], dtype=float32)



    In [32]: d54 = np.linalg.norm(t54[:,2,:3] - t54[:,1,4:7],axis=1)   # distance ( 2nd A/BT => 1st B/BT)

    In [35]: d54 = np.linalg.norm(t54[:,2,:3] - t54[:,1,4:7],axis=1) ; (d54.max(),d54.min())
    Out[35]: (np.float32(0.00061035156), np.float32(0.0))


    In [36]: e54 = np.linalg.norm(t54[:,1,:3] - t54[:,1,4:7],axis=1) ; (e54.max(),e54.min())  # distance (1st A/BT => 1st B/BT)
    Out[36]: (np.float32(0.4897342), np.float32(0.051962286))

    In [37]: e54
    Out[37]: array([0.195, 0.206, 0.063, 0.077, 0.133, 0.052, 0.136, 0.055, 0.09 , 0.136, 0.059, 0.157, 0.07 , 0.112, 0.08 , 0.085, 0.103, 0.082, 0.094, 0.118, 0.079, 0.139, 0.49 ], dtype=float32)




::

    In [49]: a.f.record[w54,:7,0,3]
    Out[49]: 
    array([[  0.1  ,  92.668,  92.669,  93.995,  99.806, 100.601, 199.373],
           [  0.1  ,  92.507,  92.508,  94.159,  99.943, 100.79 , 199.313],
           [  0.1  ,  92.133,  92.133,  92.68 ,  92.75 ,  92.774,  92.822],
           [  0.1  ,  92.149,  92.149,  92.698,  92.77 ,  92.794,  92.843],
           [  0.1  ,  92.167,  92.167,  92.722,  92.795,  92.82 ,  92.87 ],
           [  0.1  ,  92.487,  92.487,  94.185,  99.143, 100.649, 198.513],
           [  0.1  ,  92.499,  92.5  ,  94.173,  99.127, 100.665, 198.507],
           [  0.1  ,  92.613,  92.614,  94.057,  99.016, 100.777, 198.466],
           [  0.1  ,  92.621,  92.622,  94.049,  99.01 , 100.783, 198.464],
           [  0.1  ,  92.655,  92.656,  94.014,  98.987, 100.807, 198.453],
           [  0.1  ,  92.723,  92.723,  93.946,  98.949, 100.845, 198.435],
           [  0.1  ,  98.684,  98.684,  99.117,  99.185,  99.206,  99.252],
           [  0.1  ,  98.682,  98.683,  99.112,  99.18 ,  99.201,  99.247],
           [  0.1  ,  98.682,  98.682,  99.111,  99.179,  99.2  ,  99.245],
           [  0.1  ,  98.715,  98.715,  99.145,  99.214,  99.236,  99.283],
           [  0.1  ,  98.72 ,  98.72 ,  99.152,  99.221,  99.244,  99.291],
           [  0.1  ,  98.822,  98.822,  99.324,  99.402,  99.438,  99.493],
           [  0.1  ,  98.847,  98.847,  99.373,  99.455,  99.499,  99.557],
           [  0.1  ,  98.87 ,  98.871,  99.425,  99.509,  99.57 ,  99.632],
           [  0.1  ,  90.62 ,  90.62 ,  91.192,  91.262,  91.286,  91.333],
           [  0.1  ,  90.642,  90.642,  91.268,  91.343,  91.371,  91.422],
           [  0.1  ,  91.192,  91.193,  92.459,  97.726,  99.545, 195.489],
           [  0.1  ,  91.652,  91.655,  91.993,  97.921,  99.347, 195.453]], dtype=float32)

    In [50]: a.f.record[w54,:7,3,1].view(np.int32)
    Out[50]: 
    array([[    0, 51007, 51007, 51007, 51231, 51231,     0],
           [    0, 51007, 51007, 51007, 51231, 51231,     0],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51003, 51003, 51003, 51003, 51003, 51003],
           [    0, 51003, 51003, 51003, 51003, 51003, 51003],
           [    0, 51003, 51003, 51003, 51225, 51225,     0],
           [    0, 51003, 51003, 51003, 51225, 51225,     0]], dtype=int32)




DONE :  make connection between sensor_id with single photon viz
---------------------------------------------------------------------



EVT::

    116     elif [ "$EVT_CHECK" == "poolcover_ipc" ]; then
    117
    118         export AFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/A000
    119         export BFOLD=/tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_3345.569,20623.73,21000_CircleXZ_R500_100k_f8/B000

    128         where=/tmp/w54.npy[0:1]    ## w54 = ab.q_and("TO BT BT BT BT BT SA", "TO BT BT BT BT SA")    A:5xBT B:4xBT
    129         export AFOLD_RECORD_SLICE=$where
    130         export BFOLD_RECORD_SLICE=$where

ssst.sh::

    T0=200 T1=201 ssst.sh   ## high T so no anim





::

    TEST=POOLCOVER SAB=1 ipc env_pdb

    In [1]: w54 = ab.q_and("TO BT BT BT BT BT SA", "TO BT BT BT BT SA") ; w54
    Out[1]: array([71464, 71485, 71663, 71678, 71690, 71780, 71782, 71798, 71799, 71803, 71810, 71914, 71918, 71919, 71975, 71978, 72019, 72026, 72032, 73149, 73212, 73344, 73372])


    


    In [2]: t54 = np.c_[a.f.record[w54,:7,0],b.f.record[w54,:7,0]] ; t54
    Out[2]: 
    array([[[  3235.416,  20623.73 ,  20512.285,      0.1  ,   3235.416,  20623.73 ,  20512.285,      0.1  ],
            [ -1188.089,  20623.73 ,    926.728,     92.668,  -1188.132,  20623.73 ,    926.537,     92.669],
            [ -1188.132,  20623.73 ,    926.537,     92.669,  -1251.53 ,  20623.73 ,    645.835,     93.995],
            [ -1251.53 ,  20623.73 ,    645.835,     93.995,  -1529.175,  20623.73 ,   -583.467,     99.806],
            [ -1529.175,  20623.73 ,   -583.467,     99.806,  -1567.19 ,  20623.73 ,   -751.785,    100.601],
            [ -1567.193,  20623.73 ,   -751.799,    100.601,  -6287.166,  20623.73 , -21650.   ,    199.373],
            [ -6287.166,  20623.73 , -21649.998,    199.373,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3236.06 ,  20623.73 ,  20512.14 ,      0.1  ,   3236.06 ,  20623.73 ,  20512.14 ,      0.1  ],
            [ -1153.963,  20623.73 ,    954.78 ,     92.507,  -1154.008,  20623.73 ,    954.579,     92.508],
            [ -1154.008,  20623.73 ,    954.579,     92.508,  -1232.439,  20623.73 ,    605.175,     94.159],
            [ -1232.439,  20623.73 ,    605.175,     94.159,  -1507.233,  20623.73 ,   -619.022,     99.943],
            [ -1507.233,  20623.73 ,   -619.022,     99.943,  -1547.467,  20623.73 ,   -798.263,    100.79 ],
            [ -1547.467,  20623.73 ,   -798.263,    100.79 ,  -6228.037,  20623.73 , -21650.   ,    199.313],
            [ -6228.038,  20623.736, -21650.002,    199.313,      0.   ,      0.   ,      0.   ,      0.   ]],


    In [4]: a.f.record[w54,:7,3,1].view(np.int32)   ## 0:means not-a-sensor, so this is sensor_id+1 as zero is valid
    Out[4]:
    array([[    0, 51007, 51007, 51007, 51231, 51231,     0],
           [    0, 51007, 51007, 51007, 51231, 51231,     0],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51007, 51007, 51007],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51007, 51007, 51007, 51230, 51230,     0],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51230, 51230, 51230, 51230, 51230, 51230],
           [    0, 51003, 51003, 51003, 51003, 51003, 51003],
           [    0, 51003, 51003, 51003, 51003, 51003, 51003],
           [    0, 51003, 51003, 51003, 51225, 51225,     0],
           [    0, 51003, 51003, 51003, 51225, 51225,     0]], dtype=int32)

    In [5]: a.f.record[w54,:7,3,1].view(np.int32) - 1  ## subtract 1 to give sensor_id, with -1 now meaning not-a-sensor
    Out[5]:
    array([[   -1, 51006, 51006, 51006, 51230, 51230,    -1],
           [   -1, 51006, 51006, 51006, 51230, 51230,    -1],
           [   -1, 51006, 51006, 51006, 51006, 51006, 51006],
           [   -1, 51006, 51006, 51006, 51006, 51006, 51006],
           [   -1, 51006, 51006, 51006, 51006, 51006, 51006],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51006, 51006, 51006, 51229, 51229,    -1],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51229, 51229, 51229, 51229, 51229, 51229],
           [   -1, 51002, 51002, 51002, 51002, 51002, 51002],
           [   -1, 51002, 51002, 51002, 51002, 51002, 51002],
           [   -1, 51002, 51002, 51002, 51224, 51224,    -1],
           [   -1, 51002, 51002, 51002, 51224, 51224,    -1]], dtype=int32)


MOI::

     60 #moi=PMT_20inch_veto:0:1000  # gord:1000 [0...] GAS-ordinal selection of the instance transform to use
     61 moi=PMT_20inch_veto:0:$((  51006 - 50000))
     62 #moi=PMT_20inch_veto:0:$((  51230 - 50000))
     63 #moi=sOuterWaterPool:0:-2




Take look at some other discrepant histories
---------------------------------------------


::

    .q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum :   284.8138 c2n :    13.0000 c2per:    21.9088  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  284.81/13:21.909 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO SA                                                                  ' ' 0' ' 85301  85453' ' 0.1353' '     0      0']
     [' 1' 'TO AB                                                                  ' ' 1' ' 13861  13716' ' 0.7624' '     1      3']

     [' 2' 'TO BT BT BT BT SA                                                      ' ' 2' '   143    224' '17.8774' ' 71432  71433']
     [' 6' 'TO BT BT BT BT BT SA                                                   ' ' 6' '    71      0' '71.0000' ' 71455     -1']
                                                                                  143 + 71 =  214 

 
     [' 3' 'TO BT BT SA                                                            ' ' 3' '    72    132' '17.6471' ' 71342  71341']
     [' 7' 'TO BT BT BT SA                                                         ' ' 7' '    68      0' '68.0000' ' 71352     -1']
                                                                                   72 + 68 =  140

     [' 4' 'TO BT BT BT BT EC                                                      ' ' 4' '    90    117' ' 3.5217' ' 71553  71555']
     [' 9' 'TO BT BT BT BT BT EC                                                   ' ' 9' '    45      0' '45.0000' ' 71554     -1']


     [' 5' 'TO BT BT AB                                                            ' ' 5' '    58    108' '15.0602' ' 71358  71344']
     ['11' 'TO BT BT BT AB                                                         ' '11' '    38      1' '35.1026' ' 71392  73345']

  
     [' 8' 'TO BT BT BT BT AB                                                      ' ' 8' '    40     59' ' 3.6465' ' 71440  71432']
     ['13' 'TO BT BT BT BT BT AB                                                   ' '13' '    27      0' ' 0.0000' ' 71434     -1']


     ['10' 'TO BT BT BR BT BT SA                                                   ' '10' '    26     40' ' 2.9697' ' 71537  71534']
     ['12' 'TO BT BT BT BT BR BT BT BT BT SA                                       ' '12' '    20     35' ' 4.0909' ' 71583  71580']


     ['14' 'TO BT BR BT SA                                                         ' '14' '    11     17' ' 0.0000' ' 71532  71537']
     ['15' 'TO BT BT BT BR BT BT BT SA                                             ' '15' '    10     13' ' 0.0000' ' 71561  71549']
     ['16' 'TO BT BT BT BT BR BT BT SA                                             ' '16' '     5     12' ' 0.0000' ' 71835  71825']



w32 : looks like same story of first imprecise intersect followed by precise one matching Geant4
--------------------------------------------------------------------------------------------------

::

    In [18]: w32 = ab.q_and("TO BT BT BT SA", "TO BT BT SA" ) ; w32
    Out[18]: array([71352, 71355, 71373, 71380, 71411, 71427, 71431, 72078, 72090, 72092, 72094, 72100, 72106, 72111, 72962, 72994, 73000, 73387, 73388, 73391, 73403, 73645, 73665, 73686, 73699, 73716])


    In [27]: t32 = np.c_[a.f.record[w32,:5,0],b.f.record[w32,:5,0]] ; t32
    Out[27] 
    array([[[  3231.987,  20623.73 ,  20513.072,      0.1  ,   3231.987,  20623.73 ,  20513.072,      0.1  ],
            [ -1666.469,  20623.73 ,   -486.588,     99.512,  -1666.483,  20623.73 ,   -486.649,     99.512],
            [ -1666.483,  20623.73 ,   -486.649,     99.512,  -1671.172,  20623.73 ,   -506.75 ,     99.607],
            [ -1671.176,  20623.73 ,   -506.767,     99.607,  -6586.671,  20623.73 , -21579.479,    199.365],
            [ -6586.673,  20623.73 , -21579.484,    199.365,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3232.078,  20623.73 ,  20513.05 ,      0.1  ,   3232.078,  20623.73 ,  20513.05 ,      0.1  ],
            [ -1662.484,  20623.73 ,   -487.814,     99.513,  -1662.499,  20623.73 ,   -487.875,     99.513],
            [ -1662.499,  20623.73 ,   -487.875,     99.513,  -1668.413,  20623.73 ,   -513.252,     99.634],
            [ -1668.406,  20623.73 ,   -513.223,     99.633,  -6586.671,  20623.73 , -21615.787,    199.528],
            [ -6586.666,  20623.732, -21615.762,    199.528,      0.   ,      0.   ,      0.   ,      0.   ]],

           [[  3232.629,  20623.73 ,  20512.922,      0.1  ,   3232.629,  20623.73 ,  20512.922,      0.1  ],
            [ -1638.882,  20623.73 ,   -496.497,     99.528,  -1638.904,  20623.73 ,   -496.592,     99.528],
            [ -1638.904,  20623.73 ,   -496.592,     99.528,  -1651.829,  20623.73 ,   -552.333,     99.792],
            [ -1651.826,  20623.73 ,   -552.323,     99.792,  -6543.802,  20623.73 , -21650.   ,    199.637],
            [ -6543.803,  20623.732, -21650.002,    199.637,      0.   ,      0.   ,      0.   ,      0.   ]],



    In [28]: d32 = np.linalg.norm(a.f.record[w32,2,0,:3] - b.f.record[w32,1,0,:3],axis=1) ; (d32.max(),d32.min())  # from A:2 => B:1
    Out[28]: (np.float32(0.0011137871), np.float32(0.0))

    In [29]: d32
    Out[29]: 
    array([0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.001, 0.   , 0.   , 0.   , 0.   , 0.   , 0.001, 0.   , 0.   , 0.   , 0.   , 0.   ],
          dtype=float32)

    In [30]: d32*1000
    Out[30]: 
    array([0.153, 0.061, 0.092, 0.092, 0.122, 0.122, 0.183, 0.086, 0.061, 0.   , 0.061, 0.122, 0.061, 0.   , 1.114, 0.086, 0.   , 0.122, 0.173, 0.273, 0.732, 0.386, 0.183, 0.   , 0.061, 0.061],
          dtype=float32)






    In [36]: e32 = np.linalg.norm(a.f.record[w32,1,0,:3] - b.f.record[w32,1,0,:3],axis=1) ; (e32.max(),e32.min())   # A:1 => B:1
    Out[36]: (np.float32(1.2345868), np.float32(0.05777428))

    In [37]: e32
    Out[37]: 
    array([0.063, 0.063, 0.097, 0.062, 0.08 , 0.077, 0.116, 0.071, 0.072, 0.076, 0.138, 0.07 , 0.2  , 0.058, 1.235, 0.061, 0.082, 0.181, 0.077, 0.114, 0.086, 0.212, 0.135, 0.193, 0.077, 0.089],
          dtype=float32)





improving intersect precision for long rays
---------------------------------------------

~/opticks/notes/issues/refine_intersect_precision_for_long_rays.rst


