cxs_min_shakedown
==================

Workflow
----------

::

    ~/opticks/CSGOptiX/cxs_min.sh info
    ~/opticks/CSGOptiX/cxs_min.sh info_run
    LOG=1 ~/opticks/CSGOptiX/cxs_min.sh info_run
    ~/opticks/CSGOptiX/cxs_min.sh grab
    ~/opticks/CSGOptiX/cxs_min.sh ana



DONE : get cxs_min.sh to do the same as the A side of G4CXTest_GEOM.sh : check match
---------------------------------------------------------------------------------------

Currently using input photons. Need to switch it to same torch as G4CXTest_GEOM. 
Hmm factor off the torch setup ?::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/CSGOptiX/cxs_min.sh ana 

   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh


::

    epsilon:~ blyth$ EVT=p003 ~/opticks/CSGOptiX/cxs_min.sh info
                    GEOM : J23_1_0_rc3_ok0 
                  LOGDIR : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest 
                    BASE : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest 
            OPTICKS_HASH :  
                     CVD :  
    CUDA_VISIBLE_DEVICES : 1 
                    SDIR : /Users/blyth/opticks/CSGOptiX 
                    FOLD : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL/p003 
                     LOG :  
                    NEVT :  


    epsilon:tests blyth$ ~/opticks/g4cx/tests/G4CXTest_GEOM.sh info
                                           BASH_SOURCE : /Users/blyth/opticks/g4cx/tests/G4CXTest_GEOM.sh 
                                                  SDIR : /Users/blyth/opticks/g4cx/tests 
                                                  GEOM : J23_1_0_rc3_ok0 
                        J23_1_0_rc3_ok0_CFBaseFromGEOM : /Users/blyth/.opticks/GEOM/J23_1_0_rc3_ok0 
                              J23_1_0_rc3_ok0_GDMLPath : /Users/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin.gdml 
                                               VERSION : 0 
                                                   TMP : /data/blyth/opticks 
                                                  BASE : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0 
                                                 AFOLD : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/G4CXTest/ALL0/p001 
                                                 BFOLD : /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/G4CXTest/ALL0/n001 
                                                   CVD :  
                                  CUDA_VISIBLE_DEVICES :  
                                                script : /Users/blyth/opticks/g4cx/tests/G4CXTest_GEOM.py 
    epsilon:tests blyth$ 




Compare A side of G4CXTest_GEOM.sh with cxs_min.sh : CLOSE BUT NOT THE SAME ?
---------------------------------------------------------------------------------





::

    In [1]: a
    Out[1]: SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/G4CXTest/ALL0/p001

    In [2]: b
    Out[2]: SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL/p001


They start together::

    In [3]: a.q[:10]
    Out[3]:
    array([[b'TO BT BT BT BT BR BT BT BT BT BT DR BT SR BT BT BT BT BT BT BT BT SR BT SA                      '],
           [b'TO SC SC BT BR BT BT BR BT BT BR BT SC SC AB                                                    '],
           [b'TO AB                                                                                           '],
           [b'TO RE RE BT BT DR BT BT BT BT SA                                                                '],
           [b'TO SC AB                                                                                        '],
           [b'TO BT BT BT BT BT BT SA                                                                         '],
           [b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT SA                                                 '],
           [b'TO BT BT BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                               '],
           [b'TO SC BT AB                                                                                     '],
           [b'TO RE AB                                                                                        ']], dtype='|S96')

    In [4]: b.q[:10]
    Out[4]:
    array([[b'TO BT BT BT BT BR BT BT BT BT BT DR BT SR BT BT BT BT BT BT BT BT SR BT SA                      '],
           [b'TO SC SC BT BR BT BT BR BT BT BR BT SC SC AB                                                    '],
           [b'TO AB                                                                                           '],
           [b'TO RE RE BT BT DR BT BT BT BT SA                                                                '],
           [b'TO SC AB                                                                                        '],
           [b'TO BT BT BT BT BT BT SA                                                                         '],
           [b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT SA                                                 '],
           [b'TO BT BT BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                               '],
           [b'TO SC BT AB                                                                                     '],
           [b'TO RE AB                                                                                        ']], dtype='|S96')


::

    In [10]: np.where( a.q != b.q )[0]
    Out[10]: array([   68,   104,   168,   175,   190, ..., 99954, 99960, 99964, 99981, 99996])

    In [11]: np.where( a.q != b.q )[0].shape
    Out[11]: (3533,)

    In [12]: a.q.shape
    Out[12]: (100000, 1)

::

    In [21]: np.c_[a.q[w,0],b.q[w,0]][:500]
    Out[21]:
    array([[b'TO SC SC BT BT BT BT BT BT BT SR BT BT BT BT BT BT BR BR BT BT BT BT BT BT BT BT SD             ',
            b'TO SC SC BT BT BT BT BT BT BT SR BT BT BT BT BT BT BT BT RE RE SC SC AB                         '],
           [b'TO BT BT BT BT BT BT BT SR BR SR BT BT BT BT BT BT BT SC SC AB                                  ',
            b'TO BT BT BT BT BT BT BT SA                                                                      '],
           [b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT BR BT BT BT BT BT BT SA                            ',
            b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT SA                                                 '],
           [b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT BT SR SR SA                                  ',
            b'TO SC BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT BT SA                                        '],
           [b'TO RE RE BT BT BT BT BT BT BT BT SA                                                             ',
            b'TO RE RE BT BT BT DR BT BT AB                                                                   '],
           [b'TO SC SC BT BT BT BT BT BT BT SD                                                                ',
            b'TO SC SC BT BT BT BR BT BT BT BT SR BT BT BT BT SA                                              '],
           [b'TO SC BT BT BT BT BT BT BT BT BT SA                                                             ',


::

    In [30]: a.f.record[68,:10] - b.f.record[68,:10]
    Out[30]: 
    array([[[ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],

           [[ 0.   ,  0.   , -0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],

           [[-0.001,  0.   ,  0.   , -0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],

           [[ 0.   ,  0.   , -0.002,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],

           [[-0.001,  0.   ,  0.   ,  0.   ],
            [ 0.   , -0.   , -0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],

           [[-0.001,  0.   ,  0.   ,  0.   ],
            [ 0.   , -0.   , -0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ]],







::

    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh ana

    101 #export BFOLD=$EVTBASE/ALL$VERSION/n001
    102 export BFOLD=$TMP/GEOM/$GEOM/CSGOptiXSMTest/ALL/p001  ## TMP OVERRIDE


    QCF qcf :
    a.q 100000 b.q 100000 lim slice(None, None, None)
    c2sum :   215.8253 c2n :   361.0000 c2per:     0.5979  C2CUT:   30
    c2sum/c2n:c2per(C2CUT)  215.83/361:0.598 (30) pv[1.00,> 0.05 : null-hyp ]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison
    [[' 0' 'TO AB                                                                                          ' ' 0' ' 12596  12596' ' 0.0000' '     2      2']
     [' 1' 'TO BT BT BT BT BT BT SD                                                                        ' ' 1' '  7070   7070' ' 0.0000' '    18     18']
     [' 2' 'TO BT BT BT BT BT BT SA                                                                        ' ' 2' '  5645   5645' ' 0.0000' '     5      5']
     [' 3' 'TO SC AB                                                                                       ' ' 3' '  5211   5211' ' 0.0000' '     4      4']
     [' 4' 'TO SC BT BT BT BT BT BT SD                                                                     ' ' 4' '  3497   3497' ' 0.0000' '    58     58']
     [' 5' 'TO SC BT BT BT BT BT BT SA                                                                     ' ' 5' '  3005   3017' ' 0.0239' '   124    124']
     [' 6' 'TO SC SC AB                                                                                    ' ' 6' '  1964   1964' ' 0.0000' '   137    137']
     [' 7' 'TO RE AB                                                                                       ' ' 7' '  1867   1867' ' 0.0000' '     9      9']
     [' 8' 'TO BT BT SA                                                                                    ' ' 8' '  1852   1852' ' 0.0000' '    71     71']
     [' 9' 'TO SC SC BT BT BT BT BT BT SD                                                                  ' ' 9' '  1534   1534' ' 0.0000' '    19     19']
     ['10' 'TO SC SC BT BT BT BT BT BT SA                                                                  ' '10' '  1320   1326' ' 0.0136' '    24     24']
     ['11' 'TO BT BT AB                                                                                    ' '11' '  1148   1148' ' 0.0000' '    72     72']
     ['12' 'TO BT AB                                                                                       ' '12' '   895    895' ' 0.0000' '    36     36']
     ['13' 'TO BT BT BT BT BT BT BT SR SA                                                                  ' '13' '   658    881' '32.3125' '    16     16']
     ['14' 'TO BT BT BT BT BT BT BT SA                                                                     ' '14' '   743    879' '11.4032' '   176    104']
     ['15' 'TO SC SC SC AB                                                                                 ' '15' '   802    802' ' 0.0000' '    90     90']
     ['16' 'TO RE BT BT BT BT BT BT SD                                                                     ' '16' '   759    759' ' 0.0000' '   197    197']
     ['17' 'TO SC RE AB                                                                                    ' '17' '   734    734' ' 0.0000' '   110    110']
     ['18' 'TO RE BT BT BT BT BT BT SA                                                                     ' '18' '   675    679' ' 0.0118' '    48     48']
     ['19' 'TO SC BT BT AB                                                                                 ' '19' '   638    639' ' 0.0008' '   153    153']
     ['20' 'TO SC BT BT SA                                                                                 ' '20' '   592    596' ' 0.0135' '   120    120']
     ['21' 'TO SC SC SC BT BT BT BT BT BT SD                                                               ' '21' '   593    593' ' 0.0000' '   145    145']
     ['22' 'TO BT BT BT BT SD                                                                              ' '22' '   585    585' ' 0.0000' '    13     13']
     ['23' 'TO BT BT BT SA                                                                                 ' '23' '   566    566' ' 0.0000' '   745    745']
     ['24' 'TO SC BT BT BT BT BT BT BT SA                                                                  ' '24' '   485    563' ' 5.8053' '    20     20']
     ['25' 'TO RE RE AB                                                                                    ' '25' '   562    562' ' 0.0000' '   267    267']
     ['26' 'TO SC BT AB                                                                                    ' '26' '   535    536' ' 0.0009' '     8      8']
     ['27' 'TO BT BT DR BT SA                                                                              ' '27' '   533    533' ' 0.0000' '   600    600']
     ['28' 'TO SC SC SC BT BT BT BT BT BT SA                                                               ' '28' '   495    498' ' 0.0091' '    23     23']
     ['29' 'TO SC BT BT BT BT BT BT BT SR SA                                                               ' '29' '   332    426' '11.6570' '   243    243']
     ['30' 'TO BT BT BT BT BT BT BT SR SR SA                                                               ' '30' '   298    385' '11.0820' '   286    373']
     ['31' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                             ' '31' '   384    384' ' 0.0000' '   362    362']
     ['32' 'TO RE SC AB                                                                                    ' '32' '   350    350' ' 0.0000' '    54     54']
     ['33' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                             ' '33' '   325    327' ' 0.0061' '    22     22']
     ['34' 'TO SC RE BT BT BT BT BT BT SD                                                                  ' '34' '   314    314' ' 0.0000' '   292    292']
     ['35' 'TO BT BT BT BT BT BT BT SD                                                                     ' '35' '   313    313' ' 0.0000' '   181    181']
     ['36' 'TO SC SC BT BT AB                                                                              ' '36' '   304    305' ' 0.0016' '   636    636']
     ['37' 'TO BT BT BT BT AB                                                                              ' '37' '   291    291' ' 0.0000' '   225    225']
     ['38' 'TO SC BT BT BT BT SD                                                                           ' '38' '   291    291' ' 0.0000' '   224    224']
     ['39' 'TO RE SC BT BT BT BT BT BT SA                                                                  ' '39' '   276    277' ' 0.0018' '   781    781']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    []

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    []


SR : looks implicated





