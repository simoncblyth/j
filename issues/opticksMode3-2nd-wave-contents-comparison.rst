opticksMode3-2nd-wave-contents-comparison
===========================================

Context
--------

* Previous :doc:`opticksMode3-contents-comparison`
* Next :doc:`3inch_PMT_geometry`


Overview
-------------

* DONE : investigate deviant histories : most problems now from photons ending on 3inch PMT 
* DONE : tub3 Manager incorporated into "jps" j/PMTSim PMTSIM_STANDALONE 

  * MODE=2 FOCUS=0,0,80 ~/opticks/u4/tests/U4SimtraceTest.sh ana 

* DONE : gxt G4CXTest.sh standalone examination of 3inch PMT (target the side especially) 

  * found virtual Water wrapper 1e-3mm from the Pyrex, increased to 1mm 
  * found that Water///Steel border not absorbing, enabled U4Tree osur implicits to get it to work 


* TODO : get plab labelling to work and mark points more clearly 
* TODO : construct query to find photon indices of PMT 3inch SD where the photon comes in backwards, lack of identity in B problematic  


* TODO : insitu simtrace, to give cleaner backdrop for onephotonplot

* TODO : insitu A-B bi-simtrace, to give another way to find discrepant geometry
         expect small(epsilon sized, 1e-3/4) deviations in degenerate regions of geometry 
         (although small the deviations should be larger than float/double 1e-5/6 level) 



Insitu Comparison Workflow
-----------------------------

After C4 updates::

    jo
    ./build_Debug.sh    ## when change directories, needs fully clean rebuild

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



3inch targetting
------------------

::

    PICK=AB MODE=2 FOCUS=0,0,100 APID=0 BPID=0 ~/opticks/g4cx/tests/G4CXTest.sh ana


Selecting histories with 3inch not involved
----------------------------------------------

* ~/opticks/notes/issues/sphoton_float_one_in_int32_1_3_iindex_slot.rst
* ~/opticks/notes/issues/iindex_making_sense_of_it.rst

HMM in ~/j/ntds/ntds3.py succeed to select A photons with histories that
do not touch any 3 inch PMT using the iindex info. 

But problem is cannot do the same for B (as it doesnt have the iindex yet) 
so cannot do an ana/qcf.py QCF A/B comparison that excludes 3 inch PMTs 


Morton Code Geomerty selection
-------------------------------

HMM : I did some morton code based geometry selection before, that 
has the advantage of working for both A and B equally so could you that to 


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

    [['38' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT BT AB      3 inch side degenerate              ' '38' '    91      0' '91.0000' ' 16654     -1']
     ['43' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT AB         DITTO                               ' '43' '    83      0' '83.0000' ' 15529     -1']
     ['56' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SD         backwards 3inch SD                  ' '56' '    56      0' '56.0000' ' 26920     -1']

     ['63' 'TO BT BT BT SA         EXPLAINED : APEX NEAR VIRTUAL/MASK 0.05 MM COINCIDENCE                  ' '63' '    42      0' '42.0000' ' 49820     -1']
     ['75' 'TO BT BT BT SD         EXPLAINED : APEX NEAR VIRTUAL/MASK 0.05 MM COINCIDENCE                  ' '75' '    34      0' '34.0000' ' 49823     -1']
            THIS WOULD CAUSE A SMALL DEFICIT IN "TO BT BT BT BT SA/SA" BUT STATS SO HIGH FOR THAT DO NOT NOTICE

     ['81' 'TO BT BT BT BT BT BT BT BT BT BT BT AB                 LOOKS LIKE B-ONLY 77 with AB not SA     ' '81' '    31      0' '31.0000' '  9297     -1']
     ['93' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SA    onto 3inch backwards : dont see degen    ' '93' '    26      0' ' 0.0000' ' 27573     -1']
     ['106' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SD    onto 3inch backwards : no degen            ' '106' '    22      0' ' 0.0000' ' 26717     -1']
     ['135' 'TO BT BT BT BT BR BT BT BT BT DR BT DR AB          NOT 3INCH                                  ' '135' '    13      0' ' 0.0000' '   162     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [['18' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA        EXPLAINED DEGENERATE 3inch SIDE      ' '18' '     0    197' '197.0000' '    -1  15508']
     ['26' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA              DITTO                                ' '26' '     0    161' '161.0000' '    -1  26558']
     ['77' 'TO BT BT BT BT BT BT BT BT BT BT BT SA       NICE SYMMETRY : AGAIN DEGENERACY ONTO 3inch       ' '77' '     0     33' '33.0000' '    -1   9210']]
              [-------------][-------------][     ]
                 5BT in          5BT out      

    key                            :       a :       b :     a/b :     b/a : (a-b)^2/(a+b) 
    PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh 
    suptitle:PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh  ## A : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001  
    suptitle:PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh  ## B : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001  

    In [1]:    



* most of the "only" involve the 3inch PMT, especially its side 
* apex issue from virtual/mask coincidence


A only : 135 : TO BT BT BT BT BR BT BT BT BT DR BT DR AB  : in, BR at vac border, DR off backing, AB at back of LPMT
------------------------------------------------------------------------------------------------------------------------

::

    In [4]: a.q_startswith("TO BT BT BT BT BR BT BT BT BT DR BT DR AB")
    Out[4]: array([  162,   165,   225,   285,   295,   392,   403,   552,   712, 99752, 99882, 99917, 99995])

    PICK=A MODE=2 APID=162  ~/j/ntds/ntds3.sh 




A only : 106 : TO [BT BT BT BT BT] SR SR [BT BT BT BT BT] BT BT SD 
-----------------------------------------------------------------------

::

    In [1]: a.q_startswith('TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT SD')
    Out[1]: array([26717, 26771, 26804, 26877, 72519, 72521, 72522, 72523, 72526, 72562, 72563, 72604, 72605, 72630, 72634, 72701, 72722, 72726, 72736, 72741, 72790, 72857])

    PICK=A MODE=2 APID=26717  ~/j/ntds/ntds3.sh   # in/bounce/out/onto 3inch backwards, no degen



A only : 93 : TO [BT BT BT BT BT] SR SR [BT BT BT BT BT] BT BT BT SA  : onto 3inch backwards
----------------------------------------------------------------------------------------------

::

    In [1]: a.q_startswith("TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SA")
    Out[1]: array([27573, 27578, 27600, 27627, 27630, 27636, 27641, 27645, 27647, 27665, 27682, 27690, 27729, 71602, 71658, 71660, 71671, 71673, 71706, 71714, 71743, 71746, 71784, 71785, 71808, 71810])

    PICK=A MODE=2 APID=27573  ~/j/ntds/ntds3.sh   # in/bounce/out/onto 3inch backwards, no degen
    PICK=A MODE=2 APID=71810  ~/j/ntds/ntds3.sh   # in/bounce/out/onto 3inch backwards, no degen



A only : 81 : TO [BT BT BT BT BT] [BT BT BT BT BT] BT AB
--------------------------------------------------------

* AHHA : THIS HISTORY IS VERY MUCH LIKE 77 in the B onlys, except this ends in "AB" and that ends "SA" 

  * TODO : check whats happening with the 3inch PMT side, how come AB in one and SA in another 
    (HMM: this might be missing implicit ?) 


::

    In [1]: a.q_startswith("TO BT BT BT BT BT BT BT BT BT BT BT AB")
    Out[1]: 
    array([ 9297,  9620,  9758,  9829,  9911,  9954, 10015, 10047, 10207, 10307, 89331, 89372, 89383, 89384, 89387, 89406, 89490, 89545, 89549, 89715, 89740, 89787, 89842, 89935, 89968, 90103, 90104,
           90126, 90305, 90420, 90515])

    PICK=A MODE=2 APID=9297  ~/j/ntds/ntds3.sh 
        



A only : 56 : TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SD : 3inch PMT backwards SD 
----------------------------------------------------------------------------------------------

::

    In [3]: a.q_startswith("TO BT BT BT BT BT SR SR BT BT BT BT BT BT BT BT SD")
    Out[3]: 
    array([26920, 26951, 27000, 27078, 27103, 27110, 27114, 27130, 27139, 27178, 27180, 27182, 27221, 27237, 27288, 27317, 27332, 27333, 27342, 27364, 27366, 27368, 27412, 27454, 27470, 27512, 27533,
           71822, 71879, 71896, 71909, 71914, 71926, 71928, 71966, 72004, 72010, 72032, 72137, 72158, 72169, 72170, 72216, 72227, 72293, 72297, 72301, 72334, 72344, 72358, 72376, 72391, 72395, 72418,
           72433, 72487])

    PICK=A MODE=2 APID=26920  ~/j/ntds/ntds3.sh    ## HMM : 3inch SD with photon coming in from the back after exiting LPMT 
    PICK=A MODE=2 APID=27533  ~/j/ntds/ntds3.sh    ## HMM these are 3inch SD  


* TODO: construct query to find photon indices of PMT 3inch SD where the photon comes in backwards 


A only : TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT AB  : IMMEDIATE BULK_ABSORB INTO SIDE OF 3inch 
----------------------------------------------------------------------------------------------------------

::

    In [1]: a.q_startswith("TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT AB")
    Out[1]: 
    array([15529, 15556, 15567, 15578, 15639, 15648, 15650, 15880, 15913, 16073, 16234, 16299, 16398, 16588, 20206, 20298, 20326, 20381, 20401, 20444, 20476, 20485, 20487, 20507, 20546, 20552, 20557,
           20651, 20656, 20676, 20681, 20697, 20709, 20724, 20729, 20807, 79184, 79220, 79226, 79228, 79259, 79261, 79364, 79501, 79553, 79562, 79587, 79639, 79695, 79727, 79728, 79757, 79841, 79954,
           80019, 80033, 80034, 80044, 80060, 80070, 83345, 83441, 83442, 83452, 83509, 83518, 83546, 83658, 83761, 83785, 83801, 83856, 83859, 83879, 83936, 83983, 84010, 84105, 84252, 84429, 84530,
           84614, 84624])

    PICK=A MODE=2 APID=15529 ~/j/ntds/ntds3.sh  

    In [2]: np.diff(a.l,axis=0)       
    Out[2]: 
    array([[   0.   ,    0.   ,  -60.511,    0.   ],
           [  -0.   ,    0.   ,  -17.991,    0.   ],
           [   0.581,    0.   ,   -9.134,    0.   ],
           [  -0.007,   -0.   ,   -2.403,    0.   ],
           [   0.327,   -0.   ,   -5.804,    0.   ],
           [ -60.947,    0.   , -205.575,    0.   ],
           [ 137.399,   -0.001,  -46.619,    0.   ],
           [ -71.756,    0.   ,  -24.347,    0.   ],
           [ -16.878,   -0.   ,  267.327,    0.   ],
           [ 432.546,   -0.001, -120.009,    0.   ],
           [   5.032,    0.   ,   -0.859,    0.   ],
           [   2.009,    0.001,   -0.383,    0.   ],
           [   8.029,    0.   ,   -1.352,    0.   ],
           [   0.069,   -0.   ,   -0.013,    0.   ],
           [  19.839,   -0.   ,   -3.757,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ]])   ## BULK_ABSORB IMMEDIATELY INTO 3inch PMT SIDE


    In [2]: np.diff(a.l, axis=0)
    Out[2]: 
    array([[  -0.   ,    0.   ,  -43.742,    0.   ],
           [  -0.   ,   -0.   ,  -21.795,    0.   ],
           [  -0.45 ,   -0.   ,   -8.753,    0.   ],
           [   0.004,   -0.001,   -2.259,    0.   ],
           [  -0.251,   -0.   ,   -5.522,    0.   ],
           [  56.273,   -0.   , -257.072,    0.   ],
           [-110.8  ,    0.001,   14.333,    0.   ],
           [ 134.106,    0.   ,   17.349,    0.   ],
           [-100.081,    0.001,  235.687,    0.   ],
           [-374.057,    0.001, -125.333,    0.   ],
           [  -5.293,   -0.   ,   -0.687,    0.   ],
           [  -2.127,    0.   ,   -0.353,    0.   ],
           [  -8.399,    0.   ,   -1.054,    0.   ],
           [  -3.199,    0.   ,   -0.524,    0.   ],
           [ -34.747,    0.   ,   -5.697,    0.   ],
           [  -0.003,    0.   ,   -0.   ,    0.   ]])





A only : TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT BT AB
-----------------------------------------------------------------

::

    In [1]: a.q_startswith("TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT BT AB")
    Out[1]: 
    array([16654, 16713, 16718, 16763, 16807, 16812, 16915, 17054, 17189, 17196, 17227, 17250, 17287, 17321, 17412, 18878, 18951, 19076, 19096, 19149, 19199, 19215, 19318, 19359, 19361, 19394, 19433,
           19482, 19485, 19546, 19586, 19593, 19607, 19676, 19704, 19708, 19750, 19756, 19763, 19769, 19777, 19807, 19829, 19852, 19926, 19948, 19979, 20017, 20040, 80170, 80186, 80442, 80466, 80489,
           80503, 80653, 80663, 80702, 80731, 80742, 80762, 80810, 80863, 80993, 81016, 81072, 81073, 81126, 81219, 81329, 81472, 81563, 82125, 82212, 82279, 82298, 82311, 82355, 82414, 82563, 82631,
           82725, 82754, 82808, 82871, 82882, 83030, 83093, 83106, 83107, 83163])

    PICK=A MODE=2 APID=16654 ~/j/ntds/ntds3.sh  

    In [2]: np.diff(a.l,axis=0)
    Out[2]: 
    array([[   0.   ,    0.   ,  -56.249,    0.   ],
           [   0.   ,    0.   ,  -18.685,    0.   ],
           [   0.543,    0.   ,   -9.022,    0.   ],
           [  -0.006,   -0.001,   -2.357,    0.   ],
           [   0.306,   -0.   ,   -5.721,    0.   ],
           [ -60.154,   -0.   , -220.561,    0.   ],
           [ 131.04 ,    0.001,  -25.453,    0.   ],
           [ -93.184,   -0.   ,  -18.1  ,    0.   ],
           [   9.878,   -0.001,  255.28 ,    0.   ],
           [ 424.   ,    0.002,  -99.086,    0.   ],
           [   5.198,   -0.   ,   -0.408,    0.   ],
           [   2.087,    0.   ,   -0.223,    0.   ],
           [   8.272,   -0.   ,   -0.621,    0.   ],
           [   2.8  ,    0.   ,   -0.295,    0.   ],
           [  18.559,    0.   ,   -1.952,    0.   ],
           [   0.833,    0.   ,   -0.088,    0.   ],
           [   0.003,    0.   ,   -0.001,    0.   ]])





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

    PICK=B MODE=2 BPID=84584 ~/j/ntds/ntds3.sh    ## 


    In [2]: np.diff(b.l, axis=0 )   ## PICK=B MODE=2 BPID=84584 ~/j/ntds/ntds3.sh 
    Out[2]: 
    array([[   0.   ,   -0.   ,  -60.944,    0.   ],
           [  -0.   ,    0.001,  -17.933,    0.   ],
           [  -0.584,   -0.001,   -9.148,    0.   ],
           [   0.007,    0.001,   -2.406,    0.   ],
           [  -0.33 ,   -0.   ,   -5.812,    0.   ],
           [  61.004,    0.   , -203.963,    0.   ],
           [-138.02 ,   -0.   ,  -49.108,    0.   ],
           [  69.34 ,    0.   ,  -24.671,    0.   ],
           [  19.492,   -0.   ,  268.765,    0.   ],
           [-432.826,    0.001, -123.368,    0.   ],
           [  -5.007,    0.   ,   -0.924,    0.   ],
           [  -2.   ,    0.   ,   -0.406,    0.   ],
           [  -8.   ,    0.   ,   -1.459,    0.   ],
           [  -0.05 ,    0.   ,   -0.01 ,    0.   ],
           [ -35.309,   -0.001,   -7.176,    0.   ],
           [  -0.002,   -0.   ,   -0.   ,    0.   ]])   ## degeneracy onto -X side 3inch PMT 

::

    In [5]: b.qpid
    Out[5]: 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA'

    In [4]: b.g   # looks like the issue is coincident layers at side of 3inch PMT 
    Out[4]: 
    array([[-12015.394,   9480.969,  11600.203,      1.   ],
           ...
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
           [ 283.833,   -0.   ,    2.012,    1.   ],   ##
           [ 283.836,   -0.   ,    2.012,    1.   ]])  ##


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



B Only : TO BT BT BT BT BT BT BT BT BT BT BT SA  : In/out oblique Vacuum skimmers 
-----------------------------------------------------------------------------------

* nice pure BT symmetrical history : 5BT to get in 5BT to get out, then ending in very close BT/SA 



::

    In [4]: b.q_startswith("TO BT BT BT BT BT BT BT BT BT BT BT SA")
    Out[4]: 
    array([ 9210,  9296,  9320,  9382,  9443,  9472,  9776,  9826,  9836,  9963, 10133, 10183, 10260, 89376, 89415, 89424, 89486, 89494, 89495, 89533, 89602, 89607, 89610, 89680, 89876, 89915, 89925,
           89979, 90083, 90269, 90279, 90539, 90544])


* expect A would have that with one less BT : dont see it 

::

    In [2]: a.q_startswith("TO BT BT BT BT BT BT BT BT BT BT SA")
    Out[2]: array([10332, 10377, 10384, 10527, 10614, 89186, 89192])

    PICK=A MODE=2 APID=10332 ~/j/ntds/ntds3.sh   ## HMM those miss the 3inch 



Something funny with the first.  But a sampling of the rest have familiar 3inch PMT side degeneracy issue. 

::

    PICK=B MODE=2 BPID=9210 ~/j/ntds/ntds3.sh


    In [2]: np.diff(b.l, axis=0)
    Out[2]: 
    array([[  0.   ,   0.   , -84.455,   0.   ],
           [ -0.   ,   0.   , -18.551,   0.   ],
           [  0.888,  -0.   , -10.075,   0.   ],
           [ -0.017,   0.   ,  -2.796,   0.   ],
           [  0.514,   0.   ,  -6.536,   0.   ],
           [-35.36 ,   0.   , -53.023,   0.   ],
           [ -6.212,   0.   ,  -2.125,   0.   ],
           [ -2.548,  -0.   ,  -1.115,   0.   ],
           [ -9.551,   0.   ,  -3.174,   0.   ],
           [ -7.815,   0.   ,  -3.351,   0.   ],
           [-30.183,   0.   , -12.942,   0.   ],
           [ -4.476,  -0.   ,  -1.919,   0.   ]])   ## DONT SEE DEGENERACY ?



    PICK=B MODE=2 BPID=9296 ~/j/ntds/ntds3.sh

    In [3]: np.diff(b.l, axis=0)
    Out[3]: 
    array([[ -0.   ,  -0.   , -84.13 ,   0.   ],
           [  0.   ,   0.   , -18.482,   0.   ],
           [  0.882,   0.   , -10.057,   0.   ],
           [ -0.016,  -0.001,  -2.787,   0.   ],
           [  0.511,  -0.   ,  -6.521,   0.   ],
           [-37.552,  -0.   , -57.921,   0.   ],
           [ -6.134,  -0.   ,  -2.294,   0.   ],
           [ -2.508,   0.   ,  -1.182,   0.   ],
           [ -9.434,   0.   ,  -3.436,   0.   ],
           [ -6.28 ,  -0.   ,  -2.901,   0.   ],
           [-34.753,  -0.   , -16.055,   0.   ],
           [ -0.002,  -0.   ,  -0.   ,   0.   ]])   ## THIS ONE HAS DEGENERCY 





B Only : "TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA"
---------------------------------------------------------

::

    In [1]: w = b.q_startswith("TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA")

    In [2]: w
    Out[2]: 
    array([26558, 26570, 26572, 26577, 26593, 26597, 26604, 26610, 26613, 26640, 26644, 26647, 26683, 26808, 26864, 26870, 26922, 26926, 26973, 26986, 27004, 27013, 27017, 27034, 27048, 27059, 27117,
           27142, 27144, 27182, 27184, 27277, 27293, 27295, 27304, 27330, 27384, 27391, 27416, 27436, 27465, 27466, 27469, 27487, 27489, 27512, 27535, 27539, 27558, 27582, 27590, 27600, 27666, 27701,
           27706, 27713, 27715, 27733, 27746, 27754, 71554, 71575, 71583, 71603, 71617, 71626, 71629, 71642, 71647, 71658, 71666, 71680, 71685, 71727, 71752, 71759, 71782, 71828, 71830, 71886, 71899,
           71901, 71910, 71926, 71955, 71983, 71989, 72014, 72018, 72057, 72080, 72105, 72115, 72120, 72133, 72156, 72159, 72228, 72229, 72231, 72239, 72267, 72281, 72322, 72396, 72398, 72420, 72423,
           72425, 72429, 72443, 72472, 72496, 72503, 72514, 72617, 72625, 72666, 72690, 72692, 72738, 72744, 72762, 72782, 72789, 72794, 72818, 72835, 72840, 72851, 72887, 72893, 72913, 72930, 72938,
           72962, 72990, 73020, 73033, 73034, 73084, 73086, 73096, 73108, 73137, 73149, 73181, 73195, 73201, 73249, 73251, 73262, 73299, 73302, 73327, 73335, 73336, 73343, 73364, 73380, 73392])




::

    PICK=B MODE=2 BPID=26558 ~/j/ntds/ntds3.sh

    In [4]: np.diff(b.l, axis=0) 
    Out[4]: 
    array([[   0.   ,    0.   ,  -29.95 ,    0.   ],
            ..
           [  -0.168,   -0.   ,    0.075,    0.   ],
           [ -34.802,    0.001,   15.291,    0.   ],
           [  -0.002,   -0.001,    0.001,    0.   ]])   ##  NEAR DEGENERACY IN LAST TWO POINTS AT -X 3inch PMT SIDE : ZOOMING CAN SEE KINK 


    PICK=B MODE=2 BPID=73033 ~/j/ntds/ntds3.sh

    In [2]: np.diff(b.l, axis=0)
    Out[2]: 
    array([[   0.   ,    0.   ,  -29.95 ,    0.   ],
           ..
           [  19.502,    0.   ,    9.144,    0.   ],
           [   0.002,   -0.   ,    0.001,    0.   ]])   ## DITTO AT +X 3inch PMT 


* TODO: standalone examination of 3inch PMT 



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




