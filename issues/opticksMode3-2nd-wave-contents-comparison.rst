opticksMode3-2nd-wave-contents-comparison
===========================================

Context
--------

* Previous :doc:`opticksMode3-contents-comparison`


Overview
-------------

* WIP : investigate deviant histories
* TODO : insitu simtrace, to give backdrop for onephotonplot


Standalone Comparison Workflow
--------------------------------

::

    ~/opticks/g4cx/tests/G4CXTest.sh 


Insitu Comparison Workflow
-----------------------------

After C4 updates::

    jo
    ./build_Debug.sh 

* HMM: if that finds an old C4 will need to clean build


config, run, pullback, ana, repeat::

    jxv               # laptop, for example change "ntds" ipho stats to 10k 
    jxscp             # laptop, scp jx.bash to remote 

    jxf               # workstation, pick up updated jx.bash functions 
    ntds3_noxj        # workstation, run opticksMode:3 doing both optical simulations in one invokation
    jxf ; ntds3_noxj  # workstation : generally need to do both 


    GEOM              # check the GEOM setting is eg V1J009 for current full geom (not FewPMT for standalone geom)
    GEOM tmpget       # laptop, pullback the paired SEvt 
    jxn               # laptop, cd to /Users/blyth/j/ntds
    ./ntds3.sh        # laptop, run analysis ntds3.py loading two SEvt into ipython for comparison, plotting 




2nd wave : After the normalized normal ellipsoid fix 
---------------------------------------------------------

::

    epsilon:~ blyth$ PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh 
             BASH_SOURCE : /Users/blyth/j/ntds/ntds3.sh 
                     arg : info_ana 
                    name : ntds3 
                    SDIR : /Users/blyth/j/ntds 
                    GEOM : V1J009 
                    BASE : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1 
                   AFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
                   BFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
                  script : /Users/blyth/j/ntds/ntds3.py 
    [from opticks.sysrap.sevt import SEvt, SAB
    [from opticks.ana.p import * 
    CSGFoundry.CFBase returning [/Users/blyth/.opticks/GEOM/V1J009], note:[via GEOM] 
    ]from opticks.ana.p import * 
    ]from opticks.sysrap.sevt import SEvt, SAB
    GLOBAL:0 MODE:2 SEL:1
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$AFOLD',) quiet:1
    INFO:opticks.ana.fold:Fold.Load args ('/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1',) quiet:1
    INFO:opticks.ana.pvplt:init_ee with_photon_meta:1 with_ff:0
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol a pid -1 opt  off [0. 0. 0.] 
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$BFOLD',) quiet:1
    INFO:opticks.ana.fold:Fold.Load args ('/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1',) quiet:1
    INFO:opticks.ana.pvplt:init_ee with_photon_meta:1 with_ff:0
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SAB
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
    a

    CMDLINE:/Users/blyth/j/ntds/ntds3.py
    a.base:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001

      : a.sframe_meta                                      :                    5 : 0:20:21.370568 
      : a.genstep                                          :            (1, 6, 4) : 0:23:06.830835 
      : a.photon_meta                                      :                    3 : 0:22:49.114505 
      : a.hit                                              :        (33290, 4, 4) : 0:23:03.369161 
      : a.junoSD_PMT_v2_Opticks_names                      :                (10,) : 5 days, 2:30:07.887272 
      : a.seq                                              :       (100000, 2, 2) : 0:20:21.373362 
      : a.record_meta                                      :                    1 : 0:20:21.840463 
      : a.NPFold_meta                                      :                   16 : 0:24:03.773101 
      : a.record                                           :   (100000, 32, 4, 4) : 0:20:21.841077 
      : a.domain                                           :            (2, 4, 4) : 0:24:03.772529 
      : a.sframe                                           :            (4, 4, 4) : 0:20:21.372873 
      : a.inphoton                                         :       (100000, 4, 4) : 0:23:03.341695 
      : a.flat                                             :         (100000, 64) : 0:23:06.844094 
      : a.NPFold_index                                     :                (10,) : 0:24:03.775714 
      : a.prd                                              :   (100000, 32, 2, 4) : 0:21:54.418358 
      : a.junoSD_PMT_v2_Opticks_meta                       :                   20 : 5 days, 2:30:07.887830 
      : a.photon                                           :       (100000, 4, 4) : 0:22:49.121336 
      : a.domain_meta                                      :                    4 : 0:24:03.771584 
      : a.tag                                              :          (100000, 4) : 0:20:20.925973 
      : a.junoSD_PMT_v2_Opticks                            :                 (1,) : 5 days, 2:30:07.888256 

     min_stamp : 2023-08-03 17:04:16.139953 
     max_stamp : 2023-08-08 19:14:03.102236 
     dif_stamp : 5 days, 2:09:46.962283 
     age_stamp : 0:20:20.925973 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    b

    CMDLINE:/Users/blyth/j/ntds/ntds3.py
    b.base:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001

      : b.sframe_meta                                      :                    5 : 0:24:06.948332 
      : b.genstep                                          :            (1, 6, 4) : 0:26:06.376217 
      : b.photon_meta                                      :                    3 : 0:25:43.535983 
      : b.hit                                              :        (33253, 4, 4) : 0:26:02.877315 
      : b.junoSD_PMT_v2_Opticks_names                      :                (10,) : 0:26:00.829846 
      : b.seq                                              :       (100000, 2, 2) : 0:24:06.949519 
      : b.record_meta                                      :                    1 : 0:24:07.396263 
      : b.pho0                                             :          (100000, 4) : 0:25:58.536046 
      : b.NPFold_meta                                      :                   16 : 0:26:28.183645 
      : b.record                                           :   (100000, 32, 4, 4) : 0:24:07.396692 
      : b.domain                                           :            (2, 4, 4) : 0:26:06.676448 
      : b.sframe                                           :            (4, 4, 4) : 0:24:06.948896 
      : b.inphoton                                         :       (100000, 4, 4) : 0:26:00.831235 
      : b.sup                                              :       (100000, 6, 4) : 0:24:03.795332 
      : b.pho                                              :          (100000, 4) : 0:25:59.736530 
      : b.flat                                             :         (100000, 64) : 0:26:06.376612 
      : b.NPFold_index                                     :                (12,) : 0:26:28.184006 
      : b.prd                                              :   (100000, 32, 2, 4) : 0:25:42.877011 
      : b.junoSD_PMT_v2_Opticks_meta                       :                   20 : 0:26:00.830209 
      : b.photon                                           :       (100000, 4, 4) : 0:25:43.536418 
      : b.gs                                               :               (1, 4) : 0:26:06.375830 
      : b.aux                                              :   (100000, 32, 4, 4) : 0:26:06.677057 
      : b.domain_meta                                      :                    4 : 0:26:06.675917 
      : b.tag                                              :          (100000, 4) : 0:24:03.776799 
      : b.junoSD_PMT_v2_Opticks                            :                 (1,) : 0:26:00.830802 

     min_stamp : 2023-08-08 19:07:55.844837 
     max_stamp : 2023-08-08 19:10:20.252044 
     dif_stamp : 0:02:24.407207 
     age_stamp : 0:24:03.776799 
    qcf.aqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'37494' b'8' b'TO BT BT BT BT SA                                                                               ']
     [b'30866' b'4' b'TO BT BT BT BT SD                                                                               ']
     [b'12382' b'9412' b'TO BT BT BT BT BT SA                                                                            ']
     [b'3810' b'11059' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'1998' b'10899' b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'884' b'26' b'TO BT BT AB                                                                                     ']
     [b'572' b'14725' b'TO BT BT BT BT BT SR SR SR SA                                                                   ']
     [b'473' b'3182' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'327' b'7444' b'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                    ']
     [b'326' b'5262' b'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                          ']]
    qcf.bqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'37425' b'3' b'TO BT BT BT BT SA                                                                               ']
     [b'30874' b'4' b'TO BT BT BT BT SD                                                                               ']
     [b'12477' b'9096' b'TO BT BT BT BT BT SA                                                                            ']
     [b'3794' b'10892' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'1996' b'10879' b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'893' b'28' b'TO BT BT AB                                                                                     ']
     [b'563' b'14727' b'TO BT BT BT BT BT SR SR SR SA                                                                   ']
     [b'440' b'4895' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'352' b'46' b'TO BT BT BT BT AB                                                                               ']
     [b'342' b'5279' b'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                          ']]
    a.CHECK :  
    b.CHECK :  
    QCF qcf :  
    a.q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum :  2063.4768 c2n :   114.0000 c2per:    18.1007  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  2063.48/114:18.101 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                                                              ' ' 0' ' 37494  37425' ' 0.0635' '     8      3']
     [' 1' 'TO BT BT BT BT SD                                                                              ' ' 1' ' 30866  30874' ' 0.0010' '     4      4']
     [' 2' 'TO BT BT BT BT BT SA                                                                           ' ' 2' ' 12382  12477' ' 0.3630' '  9412   9096']
     [' 3' 'TO BT BT BT BT BT SR SA                                                                        ' ' 3' '  3810   3794' ' 0.0337' ' 11059  10892']
     [' 4' 'TO BT BT BT BT BT SR SR SA                                                                     ' ' 4' '  1998   1996' ' 0.0010' ' 10899  10879']
     [' 5' 'TO BT BT AB                                                                                    ' ' 5' '   884    893' ' 0.0456' '    26     28']
     [' 6' 'TO BT BT BT BT BT SR SR SR SA                                                                  ' ' 6' '   572    563' ' 0.0714' ' 14725  14727']
     [' 7' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 7' '   473    440' ' 1.1928' '  3182   4895']
     [' 8' 'TO BT BT BT BT AB                                                                              ' ' 8' '   319    352' ' 1.6230' '   651     46']
     [' 9' 'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                         ' ' 9' '   326    342' ' 0.3832' '  5262   5279']
     ['10' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '10' '   327    332' ' 0.0379' '  7444   7463']
     ['11' 'TO BT BT BT BT BT SR BR SA                                                                     ' '11' '   309    328' ' 0.5667' ' 33584  33575']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '14' '   311    263' ' 4.0139' '  8147   8138']
     ['15' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' '15' '   279    264' ' 0.4144' '   646    940']
     ['16' 'TO BT BT BT BT BT SR SR SR BR SA                                                               ' '16' '   212    240' ' 1.7345' ' 14749  14746']

     ## manually clump together the discrepant histories 
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT AB                                                            ' '12' '   321     52' '193.9973' '  1021  17293']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '13' '    24    318' '252.7368' '  4471   1017']
     ['17' 'TO BT BT BR BT BT BT SA                                                                        ' '17' '    10    238' '209.6129' '  2991     17']
     ['18' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA                                             ' '18' '     0    197' '197.0000' '    -1  15508']
     ['19' 'TO BT BT BT BR BT BT BT BT SA                                                                  ' '19' '     9    194' '168.5961' '  3510    194']
     ['21' 'TO BT BT BT BR BT BT BT BT AB                                                                  ' '21' '   187      4' '175.3351' '   206  22156']
     ['22' 'TO BT BT BR BT BT BT AB                                                                        ' '22' '   183      3' '174.1935' '     2  39342']


     ['20' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD                                       ' '20' '   190    171' ' 1.0000' ' 16931  17569']
     ['23' 'TO BT BT BT BT BT SR SR SR BR BR SR SA                                                         ' '23' '   168    166' ' 0.0120' ' 15414  15495']
     ['24' 'TO BT BT BT BT BT BR SR SA                                                                     ' '24' '   148    164' ' 0.8205' '  9351   9255']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [['38' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT BT AB                                          ' '38' '    91      0' '91.0000' ' 16654     -1']
     ['43' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT AB                                             ' '43' '    83      0' '83.0000' ' 15529     -1']
     ['56' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SD                                             ' '56' '    56      0' '56.0000' ' 26920     -1']

     ['63' 'TO BT BT BT SA         EXPLAINED : APEX NEAR VIRTUAL/MASK 0.05 MM COINCIDENCE                  ' '63' '    42      0' '42.0000' ' 49820     -1']
     ['75' 'TO BT BT BT SD         EXPLAINED : APEX NEAR VIRTUAL/MASK 0.05 MM COINCIDENCE                  ' '75' '    34      0' '34.0000' ' 49823     -1']
            THIS WOULD CAUSE A SMALL DEFICIT IN "TO BT BT BT BT SA/SA" BUT STATS SO HIGH FOR THAT DO NOT NOTICE

     ['81' 'TO BT BT BT BT BT BT BT BT BT BT BT AB                                                         ' '81' '    31      0' '31.0000' '  9297     -1']
     ['93' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SA                                             ' '93' '    26      0' ' 0.0000' ' 27573     -1']
     ['106' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SD                                                ' '106' '    22      0' ' 0.0000' ' 26717     -1']
     ['135' 'TO BT BT BT BT BR BT BT BT BT DR BT DR AB                                                      ' '135' '    13      0' ' 0.0000' '   162     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [['18' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA                                             ' '18' '     0    197' '197.0000' '    -1  15508']
     ['26' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA                                                   ' '26' '     0    161' '161.0000' '    -1  26558']
     ['77' 'TO BT BT BT BT BT BT BT BT BT BT BT SA                                                         ' '77' '     0     33' '33.0000' '    -1   9210']]
    key                            :       a :       b :     a/b :     b/a : (a-b)^2/(a+b) 
    PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh 
    suptitle:PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh  ## A : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001  
    suptitle:PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh  ## B : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001  

    In [1]:    



Investigate B only history
------------------------------

::

    In [1]: b
    Out[1]: SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001

    In [2]: b.q_startswith("TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA") 
    Out[2]: 
    array([15508, 15592, 15597, 15634, 15636, 15689, 15883, 15887, 15990, 15998, 16009, 16015, 16078, 16084, 16113, 16220, 16228, 16252, 16262, 16424, 16527, 16770, 16807, 16836, 16916, 16928, 16943,
           17128, 17190, 17209, 17218, 17222, 17268, 17279, 17298, 17302, 17339, 17397, 17409, 17474, 18854, 19038, 19065, 19108, 19144, 19147, 19187, 19201, 19228, 19286, 19433, 19434, 19460, 19498,
           19522, 19548, 19565, 19590, 19715, 19744, 19793, 19800, 19856, 19901, 19946, 19963, 19991, 20061, 20135, 20320, 20428, 20450, 20465, 20520, 20565, 20595, 20628, 20663, 20674, 20706, 20726,
           20795, 20843, 20845, 20865, 20871, 79144, 79175, 79189, 79191, 79193, 79206, 79244, 79245, 79247, 79342, 79525, 79528, 79599, 79625, 79644, 79730, 79775, 79801, 79822, 79826, 79842, 79896,
           79930, 79977, 79987, 79997, 80005, 80011, 80024, 80043, 80109, 80281, 80293, 80296, 80316, 80332, 80343, 80422, 80436, 80455, 80528, 80531, 80655, 80696, 80895, 80993, 81039, 81071, 81171,
           81175, 81301, 81319, 81360, 81390, 81418, 81480, 81612, 82164, 82175, 82257, 82445, 82498, 82560, 82598, 82711, 82719, 82753, 82794, 82835, 82851, 82892, 82920, 82972, 83038, 83081, 83255,
           83276, 83278, 83380, 83389, 83428, 83429, 83432, 83457, 83458, 83564, 83765, 83779, 83786, 83804, 83827, 83831, 84012, 84015, 84044, 84061, 84077, 84085, 84196, 84211, 84218, 84311, 84345,
           84365, 84438, 84440, 84506, 84507, 84529, 84532, 84584])


bounce around, escape, absorbed onto 3inch side::

    PICK=B MODE=3 BPID=15508 ~/j/ntds/ntds3.sh  
    PICK=B MODE=2 BPID=15592 ~/j/ntds/ntds3.sh   ## note intersect close to coincidence region of of virtual and mask 
    PICK=B MODE=2 BPID=15597 ~/j/ntds/ntds3.sh 
    PICK=B MODE=2 BPID=15634 ~/j/ntds/ntds3.sh 

::

    In [5]: b.qpid
    Out[5]: 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA'

    In [4]: b.g   # looks like the issue is coincident layers at side of 3inch PMT 
    Out[4]: 
    array([[-12015.394,   9480.969,  11600.203,      1.   ],
           [-12052.747,   9510.443,  11636.94 ,      1.   ],
           [-12063.962,   9519.292,  11647.971,      1.   ],
           [-12069.354,   9523.548,  11654.003,      1.   ],
           [-12070.847,   9524.726,  11655.463,      1.   ],
           [-12074.292,   9527.443,  11659.262,      1.   ],
           [-12232.155,   9652.009,  11737.595,      1.   ],
           [-12194.1  ,   9621.98 ,  11873.028,      1.   ],
           [-12244.479,   9661.733,  11829.167,      1.   ],
           [-12086.099,   9536.76 ,  11655.136,      1.   ],
           [-11951.555,   9430.596,  12068.791,      1.   ],
           [-11949.63 ,   9429.077,  12073.28 ,      1.   ],
           [-11948.887,   9428.491,  12075.1  ,      1.   ],
           [-11945.804,   9426.058,  12082.249,      1.   ],
           [-11945.747,   9426.014,  12082.387,      1.   ],
           [-11938.449,   9420.255,  12100.203,      1.   ],    ## suspicious degenerates 
           [-11938.448,   9420.254,  12100.205,      1.   ]])   ## at side of 3inch PMT 

    In [1]: b.l                                                                                                                                                                   
    Out[1]: 
    array([[-171.83 ,    0.   ,  229.999,    1.   ],
           [-171.83 ,    0.   ,  169.885,    1.   ],
           [-171.83 ,    0.001,  151.837,    1.   ],
           [-171.253,    0.   ,  142.713,    1.   ],
           [-171.259,   -0.   ,  140.316,    1.   ],
           [-170.934,    0.   ,  134.521,    1.   ],
           [-231.825,    0.   ,  -72.52 ,    1.   ],
           [ -95.   ,    0.   , -116.917,    1.   ],
           [-168.937,    0.   , -140.908,    1.   ],
           [-183.391,    0.   ,  125.138,    1.   ],
           [ 248.767,   -0.   ,    7.996,    1.   ],
           [ 253.819,   -0.   ,    7.193,    1.   ],
           [ 255.838,   -0.001,    6.83 ,    1.   ],
           [ 263.897,    0.   ,    5.57 ,    1.   ],
           [ 264.05 ,   -0.   ,    5.542,    1.   ],
           [ 283.833,   -0.   ,    2.012,    1.   ],
           [ 283.836,   -0.   ,    2.012,    1.   ]])


    In [4]: np.diff(b.l,axis=0)                                                                                                                                                   
    Out[4]: 
    array([[  -0.   ,   -0.   ,  -60.114,    0.   ],
           [   0.001,    0.001,  -18.048,    0.   ],
           [   0.576,   -0.001,   -9.124,    0.   ],
           [  -0.006,   -0.   ,   -2.397,    0.   ],
           [   0.325,    0.001,   -5.795,    0.   ],
           [ -60.89 ,   -0.   , -207.041,    0.   ],
           [ 136.825,   -0.   ,  -44.398,    0.   ],
           [ -73.937,    0.   ,  -23.991,    0.   ],
           [ -14.455,    0.   ,  266.047,    0.   ],
           [ 432.159,   -0.   , -117.142,    0.   ],
           [   5.052,   -0.   ,   -0.803,    0.   ],
           [   2.018,   -0.   ,   -0.363,    0.   ],
           [   8.059,    0.001,   -1.26 ,    0.   ],
           [   0.153,   -0.001,   -0.027,    0.   ],
           [  19.783,    0.   ,   -3.53 ,    0.   ],
           [   0.002,    0.   ,   -0.   ,    0.   ]])   NEAR DEGENERATE LAST TWO POINTS AT SIDE OF 3inch PMT 







    PICK=B MODE=2 BPID=9210 ~/j/ntds/ntds3.sh 




Simple histories present in A and not in B 
---------------------------------------------

::

    PICK=A MODE=2 SEL=1 APID=49820 ~/j/ntds/ntds3.sh

    ...

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [['38' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT BT AB                                          ' '38' '    91      0' '91.0000' ' 16654     -1']
     ['43' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT AB                                             ' '43' '    83      0' '83.0000' ' 15529     -1']
     ['56' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SD                                             ' '56' '    56      0' '56.0000' ' 26920     -1']

     ['63' 'TO BT BT BT SA                                                                                 ' '63' '    42      0' '42.0000' ' 49820     -1']
     ['75' 'TO BT BT BT SD                                                                                 ' '75' '    34      0' '34.0000' ' 49823     -1']

     ['81' 'TO BT BT BT BT BT BT BT BT BT BT BT AB                                                         ' '81' '    31      0' '31.0000' '  9297     -1']
     ['93' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SA                                             ' '93' '    26      0' ' 0.0000' ' 27573     -1']
     ['106' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SD                                                ' '106' '    22      0' ' 0.0000' ' 26717     -1']
     ['135' 'TO BT BT BT BT BR BT BT BT BT DR BT DR AB                                                      ' '135' '    13      0' ' 0.0000' '   162     -1']]


63:'TO BT BT BT SA' 75:'TO BT BT BT SD' : THESE ARE DUE TO APEX 0.05 mm COINCIDENCE BETWEEN VIRTUAL AND MASK 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    PICK=A MODE=2 SEL=1 APID=49820 ~/j/ntds/ntds3.sh   ## photon is close to apex which means the 

::

    In [1]: w0 = a.q_startswith("TO BT BT BT SA") ; w0                                                                                                                                      
    Out[1]: 
    array([49820, 49842, 49844, 49851, 49854, 49863, 49864, 49870, 49882, 49904, 49912, 49927, 49939, 49950, 49952, 49955, 49961, 49962, 49981, 49996, 50005, 50011, 50014, 50028, 50033, 50035, 50054,
           50055, 50057, 50061, 50090, 50092, 50112, 50113, 50114, 50134, 50137, 50146, 50164, 50171, 50172, 50174])

    In [2]: w1 = a.q_startswith("TO BT BT BT SD") ; w1                                                                                                                                     
    Out[2]: 
    array([49823, 49830, 49832, 49856, 49872, 49894, 49901, 49903, 49906, 49921, 49922, 49943, 49958, 49960, 49964, 49978, 49979, 49988, 50004, 50009, 50012, 50013, 50038, 50044, 50075, 50088, 50109,
           50110, 50145, 50147, 50149, 50155, 50156, 50165])


Notice the clumping in the indices, all those photons are very close to apex where the virtual and mask almost(?) coincide. 

* HMM: maybe should skip the virtual ? or try reducing ray trace epsilon ? 
* both those will cause other problems 

::

    In [11]: p0 = a.f.record[w0,:5,0] ; p0                                                                                                                                        
    Out[11]: 
    array([[[-11933.387,   9416.26 ,  11735.5  ,      0.1  ],
            [-11951.997,   9430.944,  11753.804,      0.238],
            [-11956.999,   9434.892,  11758.724,      0.28 ],
            [-11958.242,   9435.872,  11759.945,      0.289],
            [-11961.35 ,   9438.324,  11763.002,      0.314]],

           [[-11933.334,   9416.218,  11735.588,      0.1  ],
            [-11951.944,   9430.902,  11753.892,      0.238],
            [-11956.946,   9434.85 ,  11758.812,      0.28 ],
            [-11958.189,   9435.83 ,  11760.033,      0.289],
            [-11961.297,   9438.282,  11763.089,      0.314]],

    In [16]: g0 = p0.copy()  
    In [17]: g0[...,3] = 1 

    In [30]: l0 = np.dot( g0.reshape(-1,4), a.f.sframe.w2m ).reshape(-1,5,4)
    In [31]: l0                                                                                                                                                                   
    Out[31]: 
    array([[[ -0.898,   0.   , 230.   ,   1.   ],
            [ -0.899,   0.   , 200.049,   1.   ],
            [ -0.898,  -0.   , 191.998,   1.   ],
            [ -0.899,   0.   , 190.   ,   1.   ],
            [ -0.898,   0.   , 184.998,   1.   ]],

           [[ -0.788,   0.   , 230.   ,   1.   ],
            [ -0.787,   0.001, 200.049,   1.   ],
            [ -0.787,   0.   , 191.998,   1.   ],
            [ -0.788,   0.001, 189.998,   1.   ],
            [ -0.788,   0.001, 184.998,   1.   ]],

           ...

           [[ -0.018,   0.   , 229.998,   1.   ],
            [ -0.018,   0.   , 200.049,   1.   ],
            [ -0.018,   0.   , 192.   ,   1.   ],
            [ -0.018,  -0.   , 189.998,   1.   ],
            [ -0.017,  -0.   , 185.   ,   1.   ]],

           [[  0.027,  -0.   , 230.   ,   1.   ],
            [  0.028,   0.   , 200.047,   1.   ],
            [  0.028,   0.   , 192.   ,   1.   ],
            [  0.028,   0.   , 190.   ,   1.   ],
            [  0.028,   0.   , 184.998,   1.   ]],

           ...

           [[  0.862,  -0.001, 229.998,   1.   ],
            [  0.863,  -0.   , 200.049,   1.   ],
            [  0.862,  -0.   , 191.998,   1.   ],
            [  0.863,  -0.   , 189.998,   1.   ],
            [  0.864,  -0.001, 184.998,   1.   ]],

           [[  0.872,  -0.   , 230.   ,   1.   ],
            [  0.873,   0.   , 200.049,   1.   ],
            [  0.873,  -0.001, 191.998,   1.   ],
            [  0.873,  -0.001, 190.   ,   1.   ],
            [  0.874,  -0.   , 184.998,   1.   ]]], dtype=float32)



Zooming in on the MODE=2 plot shows near coincidence (0.05mm) near apex 

::

         -----------------------    230      TO   input photon start line

         ----------------------     200.050  BT   virtual envelope
         ^^^^^^^^^^^^^^^^^^^^^^     200.000  ~~   mask apex region 

               Mask 
  
         -----------------------    192     BT 


         ----------------------     190     BT  
               Pyrex 

         ----------------------     185     SA/SD  

               Vacuum 



