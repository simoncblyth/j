opticksMode3-contents-comparison
=================================

Context
--------

* Previous :doc:`opticksMode3-components-comparison`
* Offshoots :

  * ~/opticks/notes/issues/sphoton_iindex_identity_CPU_GPU_difference.rst

* NEXT : after fixing the normalized normal ellipsoid bug, and other issues from G4CXTest.sh cycles

  * ~/opticks/notes/issues/opticksMode3-2nd-wave-contents-comparison.rst 


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


Nature of discrepancy
------------------------

* A:GPU has lots more splash around back of PMT, possibly just more reflection off Pyrex///Vacuum causing lots of bounce around


Ideas to pin down history discrepancies
-----------------------------------------

BIG GUNS:

* DONE : implemented standalone FewPMT/storch fast cycle comparison machinery : g4cx/tests/G4CXTest.sh
* implement aux collection GPU side 
* random aligned comparison, again relatively straightforward with standalone 

TARGET PRACTICE:

* point source input photons downwards from mid-Pyrex, upwards from mid-Vacuum 
  (focus on special surface, most likely cause of issue as most complicated)

ISOLATION OF THE ISSUE:

* check POM:0 (expect match, if so it confirm issues as special surface deviation)

SINGLE PHOTON FOLLOWING: 

* DONE : PIDX dumping and single photon plotting eg "MODE=2 PIDX=552 ~/opticks/g4cx/tests/G4CXTest.sh tra"

SMALL POTATOES:

* DONE : check pmtid match : are A and B using same PMT efficiency ?
* DONE : history comparison, look for histories only in A or B 
* DONE : general plotting of photon/record/hit 



g4cx/tests/G4CXTest.cc
---------------------------

* FIXED : complication from U4VPrimaryGenertor.h/SGenerate/MOCK_CURAND
* DONE : avoid by making the MOCK_CURAND block smaller and providing CPU SGenerate.h using srng.h 



10k input photn look
------------------------

10k clearly large history deviation::

    epsilon:ntds blyth$ ./ntds3.sh 
             BASH_SOURCE : ./ntds3.sh 
                     arg : info_ana 
                    GEOM : V1J009 
                    BASE : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1 
                   AFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
                   BFOLD : /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    CSGFoundry.CFBase returning [/Users/blyth/.opticks/GEOM/V1J009], note:[via GEOM] 

    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    at           virt-mask-mask-pyrex
     [[b'4154' b'150' b'TO BT BT BT BT SA               ABSORB ON SPECIAL                                               ']
     [b'3531' b'151'  b'TO BT BT BT BT SD               DETECT ON SPECIAL                                               ']
     [b'416' b'1997'  b'TO BT BT BT BT BT SA            TRANSMIT THRU SPECIAL, ABSORBED ON SURFACE INSIDE               ']
     [b'109' b'1731'  b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'79' b'26'     b'TO BT BT AB                     ABSORB IN MASK                                                  ']
     [b'65' b'11'     b'TO BT BT BR BR BR BR BR BT SA                                                                   ']
     [b'58' b'13'     b'TO BT BT BR BR BR BR BT SA                                                                      ']
     [b'45' b'2211'   b'TO BT BT BT BT BR BT BT BT BT BT BT AB    REFLECT OFF SPECIAL                                   ']
     [b'40' b'1741'   b'TO BT BT BT BT BR BT BT BT BT AB                                                                ']
     [b'37' b'16'     b'TO BT BT BR BR BR BR BR BR BT SA                                                                ']
     [b'36' b'651'    b'TO BT BT BT BT AB                      ABSORBED IN PYREX                                                         ']
     [b'33' b'1110'   b'TO BT BT BT BT BR BR SA                                                                         ']
     [b'29' b'1793'   b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'28' b'28'     b'TO BT BT BR BR BR BR BR BT DR BT DR AB                                                          ']
     [b'27' b'1696'   b'TO BT BT BT BT BT SR SR SR SA                                                                   ']]
    bt
     [[b'5220' b'0'   b'TO BT BT BT BT SA                                                                               ']
     [b'4193' b'4'    b'TO BT BT BT BT SD                                                                               ']
     [b'138' b'2896'  b'TO BT BT BT BT BT SA                                                                            ']
     [b'89' b'255'    b'TO BT BT AB                                                                                     ']
     [b'41' b'773'    b'TO BT BT BT BT AB                                                                               ']
     [b'24' b'1'      b'TO BT BT BR BT BT BT SA                                                                         ']
     [b'23' b'201'    b'TO AB                                                                                           ']
     [b'20' b'40'     b'TO BT BT BT BR BT BT BT BT SA                                                                   ']
     [b'18' b'106'    b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             ']
     [b'11' b'244'    b'TO BT BT BR BT BT BT BT SA                                                                      ']
     [b'10' b'307'    b'TO BT BT BT BR BT BT BT BT BT SA                                                                ']
     [b'10' b'390'    b'TO BT BT BR BT BT BT BT SD                                                                      ']
     [b'8' b'232'     b'TO BT BR BT BT BT SD                                                                            ']
     [b'8' b'8'       b'TO BT BT BT BT BR BT BT BT BT SA                                                                ']
     [b'7' b'445' b'TO BT BT BT BR BT BT BT BT BT SD                                                                ']]



DONE : wheel in history point visualization, starting from cxs_min.py for simple beginnings
--------------------------------------------------------------------------------------------

Clearly more intersects around the rear of the PMT in A::

    jxn 
    PICK=AB MODE=2 SEL=1 ./ntds3.sh 



DONE : 100k comparison 
--------------------------

100k : Looks like B is doing very little reflection, but A is doing lots of that causing 
lots more longer histories in A.   Perhaps missing absorber surface somewhere ?

* SEE SECTION BELOW FOLLOWING FIXES (FROM ~/opticks/g4cx/tests/G4CXTest.sh cycles)


::

    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    at
     [[b'42212' b'1454'      b'TO BT BT BT BT SA                                                                               ']
     [b'34714' b'1453'       b'TO BT BT BT BT SD                                                                               ']
     [b'4426' b'15323'       b'TO BT BT BT BT BT SA                                                                            ']
     [b'1143' b'15511'       b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'884' b'26'           b'TO BT BT AB                                                                                     ']
     [b'634' b'17885'        b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'631' b'83'           b'TO BT BT BR BR BR BR BR BT SA                                                                   ']
     [b'544' b'58'           b'TO BT BT BR BR BR BR BT SA                                                                      ']
     [b'393' b'16093'        b'TO BT BT BT BT BR BT BT BT BT AB                                                                ']
     [b'310' b'10262'        b'TO BT BT BT BT BR BR SA                                                                         ']
     [b'306' b'1816'         b'TO BT BT BT BT AB                                                                               ']
     [b'302' b'108'          b'TO BT BT BR BR BR BR BR BR BT SA                                                                ']
     [b'283' b'15629'        b'TO BT BT BT BT BT SR SR SA                                                                      ']
     [b'283' b'148'          b'TO BT BT BR BR BR BR BR BT DR BT DR AB                                                          ']
     [b'265' b'22335'        b'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                     ']]
    bt
     [[b'51964' b'0'         b'TO BT BT BT BT SA                                                                               ']
     [b'42514' b'4'          b'TO BT BT BT BT SD                                                                               ']
     [b'1370' b'25269'       b'TO BT BT BT BT BT SA                                                                            ']
     [b'866' b'36'           b'TO BT BT AB                                                                                     ']
     [b'351' b'111'          b'TO BT BT BT BT AB                                                                               ']
     [b'209' b'38'           b'TO BT BT BR BT BT BT SA                                                                         ']
     [b'205' b'197'          b'TO BT BT BT BR BT BT BT BT SA                                                                   ']
     [b'203' b'1031'         b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             ']
     [b'124' b'101'          b'TO AB                                                                                           ']
     [b'108' b'3776'         b'TO BT BT BR BT BT BT BT SD                                                                      ']
     [b'106' b'2302'         b'TO BT BR BT BT BT SD                                                                            ']
     [b'94' b'920'           b'TO BT BR BT BT BT SA                                                                            ']
     [b'88' b'23286'         b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'77' b'33709'         b'TO BT BT BT BT BT SR BR SA                                                                      ']
     [b'75' b'2338'          b'TO BT BT BR BT BT BT BT SA                                                                      ']]
    SAB
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 
    a

    CMDLINE:/Users/blyth/j/ntds/ntds3.py
    a.base:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001

      : a.sframe_meta                                      :                    5 : 0:01:16.130042 
      : a.genstep                                          :            (1, 6, 4) : 0:05:58.915506 
      : a.photon_meta                                      :                    3 : 0:05:19.844710 
      : a.hit                                              :        (36697, 4, 4) : 0:05:53.748805 
      : a.junoSD_PMT_v2_Opticks_names                      :                (10,) : 0:05:50.614518 
      : a.seq                                              :       (100000, 2, 2) : 0:01:16.133143 
      : a.record_meta                                      :                    1 : 0:01:17.346771 
      : a.NPFold_meta                                      :                   16 : 0:07:21.021088 
      : a.record                                           :   (100000, 32, 4, 4) : 0:01:17.351726 
      : a.domain                                           :            (2, 4, 4) : 0:07:21.020659 
      : a.sframe                                           :            (4, 4, 4) : 0:01:16.130646 
      : a.inphoton                                         :       (100000, 4, 4) : 0:05:50.616073 
      : a.flat                                             :         (100000, 64) : 0:05:58.916741 
      : a.NPFold_index                                     :                (10,) : 0:07:21.021464 
      : a.prd                                              :   (100000, 32, 2, 4) : 0:03:44.764685 
      : a.junoSD_PMT_v2_Opticks_meta                       :                   20 : 0:05:50.615076 
      : a.photon                                           :       (100000, 4, 4) : 0:05:19.845801 
      : a.domain_meta                                      :                    4 : 0:07:21.020271 
      : a.tag                                              :          (100000, 4) : 0:01:15.625632 
      : a.junoSD_PMT_v2_Opticks                            :                 (1,) : 0:05:50.615502 

     min_stamp : 2023-08-03 17:02:45.733991 
     max_stamp : 2023-08-03 17:08:51.129823 
     dif_stamp : 0:06:05.395832 
     age_stamp : 0:01:15.625632 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001 
    b

    CMDLINE:/Users/blyth/j/ntds/ntds3.py
    b.base:/tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/n001

      : b.sframe_meta                                      :                    5 : 0:07:24.844951 
      : b.genstep                                          :            (1, 6, 4) : 0:09:15.530917 
      : b.photon_meta                                      :                    3 : 0:08:43.103568 
      : b.hit                                              :        (43143, 4, 4) : 0:09:04.907607 
      : b.junoSD_PMT_v2_Opticks_names                      :                (10,) : 0:09:02.661102 
      : b.seq                                              :       (100000, 2, 2) : 0:07:24.846244 
      : b.record_meta                                      :                    1 : 0:07:24.979647 
      : b.pho0                                             :          (100000, 4) : 0:09:00.802977 
      : b.NPFold_meta                                      :                   14 : 0:09:49.289997 
      : b.record                                           :   (100000, 32, 4, 4) : 0:07:24.986203 
      : b.domain                                           :            (2, 4, 4) : 0:09:15.612963 
      : b.sframe                                           :            (4, 4, 4) : 0:07:24.845623 
      : b.inphoton                                         :       (100000, 4, 4) : 0:09:02.663148 
      : b.sup                                              :       (100000, 6, 4) : 0:07:21.040917 
      : b.pho                                              :          (100000, 4) : 0:09:01.518295 
      : b.flat                                             :         (100000, 64) : 0:09:15.531716 
      : b.NPFold_index                                     :                (12,) : 0:09:49.290687 
      : b.prd                                              :   (100000, 32, 2, 4) : 0:08:42.661925 
      : b.junoSD_PMT_v2_Opticks_meta                       :                   20 : 0:09:02.661706 
      : b.photon                                           :       (100000, 4, 4) : 0:08:43.104222 
      : b.gs                                               :               (1, 4) : 0:09:15.530478 
      : b.aux                                              :   (100000, 32, 4, 4) : 0:09:15.616713 
      : b.domain_meta                                      :                    4 : 0:09:15.611955 
      : b.tag                                              :          (100000, 4) : 0:07:21.022699 
      : b.junoSD_PMT_v2_Opticks                            :                 (1,) : 0:09:02.662281 

     min_stamp : 2023-08-03 17:00:17.465501 
     max_stamp : 2023-08-03 17:02:45.733489 
     dif_stamp : 0:02:28.267988 
     age_stamp : 0:07:21.022699 
    qcf.aqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'42212' b'1454' b'TO BT BT BT BT SA                                                                               ']
     [b'34714' b'1453' b'TO BT BT BT BT SD                                                                               ']
     [b'4426' b'15323' b'TO BT BT BT BT BT SA                                                                            ']
     [b'1143' b'15511' b'TO BT BT BT BT BT SR SA                                                                         ']
     [b'884' b'26' b'TO BT BT AB                                                                                     ']
     [b'634' b'17885' b'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                          ']
     [b'631' b'83' b'TO BT BT BR BR BR BR BR BT SA                                                                   ']
     [b'544' b'58' b'TO BT BT BR BR BR BR BT SA                                                                      ']
     [b'393' b'16093' b'TO BT BT BT BT BR BT BT BT BT AB                                                                ']
     [b'310' b'10262' b'TO BT BT BT BT BR BR SA                                                                         ']]
    qcf.bqu : np.c_[n,x,u][o][lim] : uniques in descending count order with first index x
    [[b'51964' b'0' b'TO BT BT BT BT SA                                                                               ']
     [b'42514' b'4' b'TO BT BT BT BT SD                                                                               ']
     [b'1370' b'25269' b'TO BT BT BT BT BT SA                                                                            ']
     [b'866' b'36' b'TO BT BT AB                                                                                     ']
     [b'351' b'111' b'TO BT BT BT BT AB                                                                               ']
     [b'209' b'38' b'TO BT BT BR BT BT BT SA                                                                         ']
     [b'205' b'197' b'TO BT BT BT BR BT BT BT BT SA                                                                   ']
     [b'203' b'1031' b'TO BT BT BT BT BR BT BT BT BT BT SA                                                             ']
     [b'124' b'101' b'TO AB                                                                                           ']
     [b'108' b'3776' b'TO BT BT BR BT BT BT BT SD                                                                      ']]
    QCF qcf :  
    a.q 100000 b.q 100000 lim slice(None, None, None) 
    c2sum : 13556.7305 c2n :    98.0000 c2per:   138.3340  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  13556.73/98:138.334 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                                                              ' ' 0' ' 42212  51964' '1009.8274' '  1454      0']
     [' 1' 'TO BT BT BT BT SD                                                                              ' ' 1' ' 34714  42514' '787.7972' '  1453      4']
     [' 2' 'TO BT BT BT BT BT SA                                                                           ' ' 2' '  4426   1370' '1611.3071' ' 15323  25269']
     [' 3' 'TO BT BT BT BT BT SR SA                                                                        ' ' 3' '  1143     88' '904.1633' ' 15511  23286']

     [' 4' 'TO BT BT AB                                                                                    ' ' 4' '   884    866' ' 0.1851' '    26     36']

     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' '   634     10' '604.6211' ' 17885  31780']
     [' 6' 'TO BT BT BR BR BR BR BR BT SA                                                                  ' ' 6' '   631      0' '631.0000' '    83     -1']
     [' 7' 'TO BT BT BR BR BR BR BT SA                                                                     ' ' 7' '   544      0' '544.0000' '    58     -1']
     [' 8' 'TO BT BT BT BT BR BT BT BT BT AB                                                               ' ' 8' '   393      2' '387.0405' ' 16093  65924']

     [' 9' 'TO BT BT BT BT AB                                                                              ' ' 9' '   306    351' ' 3.0822' '  1816    111']

     ['10' 'TO BT BT BT BT BR BR SA                                                                        ' '10' '   310     11' '278.5078' ' 10262    156']
     ['11' 'TO BT BT BR BR BR BR BR BR BT SA                                                               ' '11' '   302      0' '302.0000' '   108     -1']
     ['12' 'TO BT BT BR BR BR BR BR BT DR BT DR AB                                                         ' '12' '   283      0' '283.0000' '   148     -1']
     ['13' 'TO BT BT BT BT BT SR SR SA                                                                     ' '13' '   283     15' '241.0201' ' 15629  23681']
     ['14' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                    ' '14' '   265      5' '250.3704' ' 22335  28833']
     ['15' 'TO BT BR BT BT AB                                                                              ' '15' '   249      6' '231.5647' '     1  19821']
     ['16' 'TO BT BT BR BR BR BR BR BT DR BT SA                                                            ' '16' '   245      0' '245.0000' '    89     -1']
     ['17' 'TO BT BT BT BT BR BR SD                                                                        ' '17' '   245      9' '219.2756' ' 10326     52']
     ['18' 'TO BT BT BR BR BR BR BT DR BT DR AB                                                            ' '18' '   242      0' '242.0000' '   155     -1']
     ['19' 'TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                      ' '19' '   237      1' '234.0168' ' 22425  54344']
     ['20' 'TO BT BT BR BR BR BR BT DR BT SA                                                               ' '20' '   228      0' '228.0000' '   114     -1']
     ['21' 'TO BT BT BR BT BT BT SA                                                                        ' '21' '     0    209' '209.0000' '    -1     38']
     ['22' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                    ' '22' '   208      5' '193.4695' ' 22447  31454']
     ['23' 'TO BT BT BT BR BT BT BT BT SA                                                                  ' '23' '     0    205' '205.0000' '    -1    197']
     ['24' 'TO BT BT BT BT BR BT BT BT BT BT SA                                                            ' '24' '     4    203' '191.3092' ' 15831   1031']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [[' 6' 'TO BT BT BR BR BR BR BR BT SA                                                                  ' ' 6' '   631      0' '631.0000' '    83     -1']
     [' 7' 'TO BT BT BR BR BR BR BT SA                                                                     ' ' 7' '   544      0' '544.0000' '    58     -1']
     ['11' 'TO BT BT BR BR BR BR BR BR BT SA                                                               ' '11' '   302      0' '302.0000' '   108     -1']
     ['12' 'TO BT BT BR BR BR BR BR BT DR BT DR AB                                                         ' '12' '   283      0' '283.0000' '   148     -1']
     ['16' 'TO BT BT BR BR BR BR BR BT DR BT SA                                                            ' '16' '   245      0' '245.0000' '    89     -1']
     ['18' 'TO BT BT BR BR BR BR BT DR BT DR AB                                                            ' '18' '   242      0' '242.0000' '   155     -1']
     ['20' 'TO BT BT BR BR BR BR BT DR BT SA                                                               ' '20' '   228      0' '228.0000' '   114     -1']
     ['31' 'TO BT BT BR BR BR BR BR BR BT DR BT DR AB                                                      ' '31' '   142      0' '142.0000' '    23     -1']
     ['32' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                   ' '32' '   142      0' '142.0000' ' 16582     -1']
     ['33' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                                   ' '33' '   136      0' '136.0000' ' 16529     -1']
     ['34' 'TO BT BT BR BR AB                                                                              ' '34' '   128      0' '128.0000' '    41     -1']
     ['35' 'TO BT BT BR BR BR BR BR BR BR BT SA                                                            ' '35' '   128      0' '128.0000' '   111     -1']
     ['39' 'TO BT BT BR BR BR BR BR BR BT DR BT SA                                                         ' '39' '    90      0' '90.0000' '   306     -1']
     ['42' 'TO BT BT BT BT BT SR SR SR SR SA                                                               ' '42' '    82      0' '82.0000' ' 23146     -1']
     ['44' 'TO BT BT BT BT BR BR BR BR BR BT BR BT DR AB                                                   ' '44' '    76      0' '76.0000' '  3852     -1']
     ['47' 'TO BT BT BR BR BR BT DR AB                                                                     ' '47' '    66      0' '66.0000' '     5     -1']
     ['48' 'TO BT BT BR BR BR BR BR BR BR BT DR BT SA                                                      ' '48' '    64      0' '64.0000' '   133     -1']
     ['50' 'TO BT BT BT BT BR BR BR BR BR BT BR BT SA                                                      ' '50' '    63      0' '63.0000' '  3762     -1']
     ['51' 'TO BT BT BT BR BT BR BR BR BR BT SA                                                            ' '51' '    61      0' '61.0000' '  1965     -1']
     ['55' 'TO BT BT BT SA                                                                                 ' '55' '    51      0' '51.0000' ' 49820     -1']
     ['56' 'TO BT BT BR BR BR BR BR BR BR BT DR BT DR AB                                                   ' '56' '    51      0' '51.0000' '   106     -1']
     ['57' 'TO BT BT BR BR BR BT SA                                                                        ' '57' '    50      0' '50.0000' '     0     -1']
     ['58' 'TO BT BT BT BT BR BR AB                                                                        ' '58' '    48      0' '48.0000' '  2887     -1']
     ['62' 'TO BT BT BT BT BR BR BR BR BR BR BT BR BT SA                                                   ' '62' '    46      0' '46.0000' '  3632     -1']
     ['63' 'TO BT BT BT BT BR BR BR BR BR BR BT BR BT DR AB                                                ' '63' '    46      0' '46.0000' '  3862     -1']
     ['64' 'TO BT BT BT BT BR AB                                                                           ' '64' '    44      0' '44.0000' '  1829     -1']
     ['66' 'TO BT BT BR BR BR BR BR BR BR BR BT SA                                                         ' '66' '    43      0' '43.0000' '   151     -1']
     ['71' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BT DR AB                                                ' '71' '    40      0' '40.0000' '  4065     -1']
     ['72' 'TO BT BT BT SD                                                                                 ' '72' '    39      0' '39.0000' ' 49823     -1']
     ['79' 'TO BT BT BT BT BR BR BR BR BR BR BR BR DR AB                                                   ' '79' '    34      0' '34.0000' '  3123     -1']
     ['80' 'TO BT BT BT BT BR BR BR BR BR BR BR SA                                                         ' '80' '    34      0' '34.0000' '  1842     -1']
     ['82' 'TO BT BT BT BR BT BR BR BR BR BR BT SA                                                         ' '82' '    33      0' '33.0000' '  1848     -1']
     ['83' 'TO BT BT BT BT BR BT BT BT BT BT BT SD                                                         ' '83' '    33      0' '33.0000' ' 15341     -1']
     ['84' 'TO BT BT BT BT BR BR BR BR BR BR BR BT BR BT DR AB                                             ' '84' '    32      0' '32.0000' '  5155     -1']
     ['85' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT AB                                                   ' '85' '    32      0' '32.0000' ' 22020     -1']
     ['89' 'TO BT BT BR BR BR BR BT DR AB                                                                  ' '89' '    31      0' '31.0000' '   100     -1']
     ['90' 'TO BT BT BR BR BR AB                                                                           ' '90' '    31      0' '31.0000' '     9     -1']
     ['91' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT BT SA                                 ' '91' '    30      0' ' 0.0000' ' 24263     -1']
     ['93' 'TO BT BT BT BT BR BT BT BT BT BT BT BT AB                                                      ' '93' '    30      0' ' 0.0000' ' 15377     -1']
     ['94' 'TO BT BT BT BT BR BT BT BT BT BR BT BT BT BT SA                                                ' '94' '    30      0' ' 0.0000' ' 21676     -1']
     ['96' 'TO BT BT BT BT BR BR BR BR BT BR BT DR AB                                                      ' '96' '    30      0' ' 0.0000' '  2055     -1']
     ['97' 'TO BT BT BT BT BR BR BR BR BR BR BR BR SA                                                      ' '97' '    29      0' ' 0.0000' '  3050     -1']
     ['98' 'TO BT BT BT BT BR BR BR BR BR BR BR BT BR BT SA                                                ' '98' '    29      0' ' 0.0000' '  4671     -1']
     ['99' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC SC BT BT BT BT BT BT SD                              ' '99' '    29      0' ' 0.0000' ' 23075     -1']
     ['100' 'TO BT BT BT BR BT BR BR BR BR BT DR BT DR AB                                                   ' '100' '    28      0' ' 0.0000' '  2521     -1']
     ['101' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BR BT DR AB                                       ' '101' '    27      0' ' 0.0000' '  6366     -1']
     ['102' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT BR BR SA                              ' '102' '    27      0' ' 0.0000' ' 22796     -1']
     ['103' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR DR AB                                                ' '103' '    27      0' ' 0.0000' '  1944     -1']
     ['104' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BT SA                                                   ' '104' '    27      0' ' 0.0000' '  4921     -1']
     ['106' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SA                                             ' '106' '    26      0' ' 0.0000' ' 16333     -1']
     ['107' 'TO BT BT BT BT BR BR BR BR BR BR BR DR AB                                                      ' '107' '    26      0' ' 0.0000' '  1467     -1']
     ['108' 'TO BT BT BT BT BR BR BR BR BT BR BT SA                                                         ' '108' '    25      0' ' 0.0000' '  2165     -1']
     ['109' 'TO BT BT BT BT BT SR SR SR SR SR SA                                                            ' '109' '    25      0' ' 0.0000' ' 16830     -1']
     ['111' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT AB                                             ' '111' '    24      0' ' 0.0000' ' 23609     -1']
     ['112' 'TO BT BT BT BR BT BR AB                                                                        ' '112' '    24      0' ' 0.0000' '  1491     -1']
     ['113' 'TO BT BT BT BR BT BR BR BR BT SA                                                               ' '113' '    24      0' ' 0.0000' '  1741     -1']
     ['114' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BT DR AB                                          ' '114' '    24      0' ' 0.0000' '  5035     -1']
     ['115' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BT DR AB                                             ' '115' '    24      0' ' 0.0000' '  4731     -1']
     ['116' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BT SA                                             ' '116' '    23      0' ' 0.0000' '  4086     -1']
     ['117' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BT SA                                                ' '117' '    23      0' ' 0.0000' '  5690     -1']
     ['118' 'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SA                                             ' '118' '    22      0' ' 0.0000' ' 21902     -1']
     ['121' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT BT SD                                 ' '121' '    22      0' ' 0.0000' ' 27434     -1']
     ['122' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR SA                                                   ' '122' '    22      0' ' 0.0000' '  2626     -1']
     ['125' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR SA                                                ' '125' '    21      0' ' 0.0000' '  3044     -1']
     ['128' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT AB                                             ' '128' '    20      0' ' 0.0000' ' 25680     -1']
     ['129' 'TO BT BT BR BR BR BR BR BT DR BT AB                                                            ' '129' '    19      0' ' 0.0000' '   357     -1']
     ['130' 'TO BT BT BR BR BR BR BR BT BT SA                                                               ' '130' '    19      0' ' 0.0000' '   120     -1']
     ['131' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BR BT SA                                          ' '131' '    18      0' ' 0.0000' '  4841     -1']
     ['132' 'TO BT BT BT BT BR BR BR BR BR BT BR BR BR SA                                                   ' '132' '    18      0' ' 0.0000' '  3193     -1']
     ['134' 'TO BT BT BR BR BR BR BR BR BR BR BR BT SA                                                      ' '134' '    18      0' ' 0.0000' '   101     -1']
     ['135' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT BR BR SD                              ' '135' '    17      0' ' 0.0000' ' 30668     -1']
     ['136' 'TO BT BT BT BT BR BT BT BR BR BR BR BR BR BR BT SA                                             ' '136' '    17      0' ' 0.0000' ' 14763     -1']
     ['137' 'TO BT BT BT BR BT BR BR BR BR BT DR BT SA                                                      ' '137' '    17      0' ' 0.0000' '  1778     -1']
     ['141' 'TO BT BT BT BT BR BT BT BR BR BR BR BR BR BT SA                                                ' '141' '    17      0' ' 0.0000' ' 15226     -1']
     ['142' 'TO BT BT BR BR BR BR BR BR BR BR BT DR BT SA                                                   ' '142' '    17      0' ' 0.0000' '   812     -1']
     ['144' 'TO BT BT BT BT BR BR BR BR BR DR AB                                                            ' '144' '    17      0' ' 0.0000' '  1642     -1']
     ['145' 'TO BT BT BT BT BR BR BR BR BR BR SA                                                            ' '145' '    17      0' ' 0.0000' '  1518     -1']
     ['146' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR DR AB                                             ' '146' '    17      0' ' 0.0000' '  3047     -1']
     ['148' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BR BR SA                                 ' '148' '    17      0' ' 0.0000' ' 21821     -1']
     ['150' 'TO BT BT BR BR BR BR BR BT DR BT BT BT DR AB                                                   ' '150' '    17      0' ' 0.0000' '   355     -1']
     ['151' 'TO BT BT BT BT BR BT BT BR BR BR AB                                                            ' '151' '    17      0' ' 0.0000' ' 14541     -1']
     ['153' 'TO BT BT BT BT BR BT BT BT BT BT BT SA                                                         ' '153' '    16      0' ' 0.0000' ' 15698     -1']
     ['154' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT SD                                          ' '154' '    16      0' ' 0.0000' ' 24935     -1']
     ['155' 'TO BT BT BT BT BR BT BT BT BT BT BT BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR BR' '155' '    16      0' ' 0.0000' ' 17997     -1']
     ['157' 'TO BT BT BT BR BT BR BR BR BR BR BR BT SA                                                      ' '157' '    15      0' ' 0.0000' '  1803     -1']
     ['158' 'TO BT BT BT BR BR BR BR BR BR BT SA                                                            ' '158' '    15      0' ' 0.0000' '  2133     -1']
     ['159' 'TO BT BT BT BT BR BR BR BR BR BR DR AB                                                         ' '159' '    15      0' ' 0.0000' '  1584     -1']
     ['160' 'TO BT BT BT BR BT BR BR BT DR AB                                                               ' '160' '    14      0' ' 0.0000' '  1494     -1']
     ['161' 'TO BT BT BT BT BR BR BR BR BR BR BR BT DR AB                                                   ' '161' '    14      0' ' 0.0000' '  4556     -1']
     ['162' 'TO BT BT BT BT BR BR BR BR BR BR BR BT SA                                                      ' '162' '    14      0' ' 0.0000' '  3936     -1']
     ['163' 'TO BT BT BR BR BR BR BR BR BR BR BT DR BT DR AB                                                ' '163' '    14      0' ' 0.0000' '   414     -1']
     ['164' 'TO BT BT BR BR BR BT BR BR BT DR AB                                                            ' '164' '    14      0' ' 0.0000' '   591     -1']
     ['165' 'TO BT BT BR BR BR BT BR BR BT SA                                                               ' '165' '    14      0' ' 0.0000' '   158     -1']
     ['166' 'TO BT BT BR BR BR BR BR BT DR BT BT BT SA                                                      ' '166' '    14      0' ' 0.0000' '   413     -1']
     ['167' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT SA                                    ' '167' '    14      0' ' 0.0000' ' 31262     -1']
     ['168' 'TO BT BT BT BT BR BR BR BR BR SA                                                               ' '168' '    14      0' ' 0.0000' '  1497     -1']
     ['169' 'TO BT BT BT BR BT BR BR BR BR BR BT DR BT DR AB                                                ' '169' '    14      0' ' 0.0000' '  2639     -1']
     ['170' 'TO BT BT BT BT BR BR BR BR BR BR BT BR BR BR BR SA                                             ' '170' '    13      0' ' 0.0000' '  4648     -1']
     ['171' 'TO BT BT BT BT BR BR BR BR BR BR BT BR BR BR BR BT DR AB                                       ' '171' '    13      0' ' 0.0000' '  8837     -1']
     ['173' 'TO BT BT BT BR BT BR BR BR BT DR AB                                                            ' '173' '    13      0' ' 0.0000' '  1745     -1']
     ['174' 'TO BT BT BT BR BT BR BR BR BR BR BT DR BT SA                                                   ' '174' '    13      0' ' 0.0000' '  3444     -1']
     ['175' 'TO BT BT BR BR BR BR BT BT SA                                                                  ' '175' '    13      0' ' 0.0000' '    40     -1']
     ['176' 'TO BT BT BR BR BR BR BT DR BT BT BT SA                                                         ' '176' '    13      0' ' 0.0000' '   208     -1']
     ['177' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BR DR AB                                          ' '177' '    13      0' ' 0.0000' '  7731     -1']
     ['178' 'TO BT BT BT BR BT BR BR BT SA                                                                  ' '178' '    13      0' ' 0.0000' '  1533     -1']
     ['179' 'TO BT BR BT BT BR BT BT BT BT BT SR BR BR BR BR SA                                             ' '179' '    13      0' ' 0.0000' '  2689     -1']
     ['180' 'TO BT BT BT BT BR BT BT BT BT BT BT SC SC SC SC BT BT BT BT BT BT SD                           ' '180' '    13      0' ' 0.0000' ' 28537     -1']
     ['181' 'TO BT BT BR BR BR BR AB                                                                        ' '181' '    13      0' ' 0.0000' ' 10962     -1']
     ['182' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT BT SR SA                              ' '182' '    12      0' ' 0.0000' ' 34611     -1']
     ['183' 'TO BT BT BT BT BR BT BT BT BT SC BT BT BT BT SA                                                ' '183' '    12      0' ' 0.0000' ' 20004     -1']
     ['184' 'TO BT BT BR BR BR BR BR BR BR BR BR BR BT SA                                                   ' '184' '    12      0' ' 0.0000' '   255     -1']
     ['186' 'TO BT BT BT BR BR BR BR BR BR BT DR AB                                                         ' '186' '    12      0' ' 0.0000' '  2327     -1']
     ['187' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT AB                                          ' '187' '    12      0' ' 0.0000' ' 25469     -1']
     ['188' 'TO BT BT BT BT BR BR BR BR BR BT BR AB                                                         ' '188' '    12      0' ' 0.0000' '  2667     -1']
     ['189' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BT BR BT SA                                             ' '189' '    12      0' ' 0.0000' '  5541     -1']
     ['190' 'TO BT BT BT BT BR BR BR BR BR BR BR BR BR BR BR BR BT DR AB                                    ' '190' '    12      0' ' 0.0000' '  4741     -1']
     ['193' 'TO BT BT BT BT BR BT BT BT BT BT BT RE RE AB                                                   ' '193' '    11      0' ' 0.0000' ' 24721     -1']
     ['194' 'TO BT BT BT BT BR BT BT BT BT BT BT RE BT BT BT BT BT BT SA                                    ' '194' '    11      0' ' 0.0000' ' 24644     -1']
     ['199' 'TO BT BT BT BT BT SR SR SR SR SR SR SA                                                         ' '199' '    11      0' ' 0.0000' ' 16685     -1']
     ['201' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT SD                                 ' '201' '    11      0' ' 0.0000' ' 22214     -1']
     ['202' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BR BR SD                                 ' '202' '    11      0' ' 0.0000' ' 25493     -1']
     ['203' 'TO BT BT BT BT BR BT BT BR BR BR BR BR BR BR BR BT SA                                          ' '203' '    11      0' ' 0.0000' ' 15242     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [['21'  'TO BT BT BR BT BT BT SA                                                                        ' '21' '     0    209' '209.0000' '    -1     38']
     ['23'  'TO BT BT BT BR BT BT BT BT SA                                                                  ' '23' '     0    205' '205.0000' '    -1    197']
     ['95'  'TO BT BT BT BT BR BT BT BT BT SA                                                               ' '95' '     0     30' ' 0.0000' '    -1     23']
     ['124' 'TO BT BR BT BT BT BT SA                                                                        ' '124' '     0     21' ' 0.0000' '    -1   4726']
     ['126' 'TO BT BT BT BT BR BT BT BT BT DR BT SA                                                         ' '126' '     0     21' ' 0.0000' '    -1     17']
     ['192' 'TO BT BT BT BR BT BT BT SA                                                                     ' '192' '     0     12' ' 0.0000' '    -1     21']]
    key                            :       a :       b :     a/b :     b/a : (a-b)^2/(a+b) 
    STARTING PVPLT_PLOTTER ... THERE COULD BE A WINDOW WAITING FOR YOU TO CLOSE



Examine some photons from A and B with simple history
--------------------------------------------------------

* hmm iindex discrep ? 

::

    In [8]: AIDX = 26 ; BIDX = 36

    In [9]: a.q[AIDX]
    Out[9]: array([b'TO BT BT AB                                                                                     '], dtype='|S96')

    In [10]: b.q[BIDX]
    Out[10]: array([b'TO BT BT AB                                                                                     '], dtype='|S96')

::

    In [3]: a.f.record[AIDX,:4]
    Out[3]: 
    array([[[-12052.834,   9510.512,  11538.432,      0.1  ],
            [    -0.621,      0.49 ,      0.611,      1.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]],

           [[-12126.936,   9568.983,  11611.312,      0.65 ],
            [    -0.621,      0.49 ,      0.611,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,     -0.   ,      0.   ]],

           [[-12155.639,   9591.632,  11639.541,      0.863],
            [    -0.527,      0.415,      0.728,      0.   ],
            [    -0.619,     -0.785,     -0.   ,    440.   ],
            [     0.   ,      0.   ,     -0.   ,      0.   ]],

           [[-12158.013,   9593.505,  11642.822,      0.886],
            [    -0.527,      0.415,      0.728,      0.   ],
            [    -0.619,     -0.785,     -0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]]], dtype=float32)

    In [4]: b.f.record[BIDX,:4]
    Out[4]: 
    array([[[-12052.811,   9510.493,  11538.472,      0.1  ],
            [    -0.621,      0.49 ,      0.611,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]],

           [[-12126.889,   9568.946,  11611.328,      0.65 ],
            [    -0.621,      0.49 ,      0.611,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]],

           [[-12155.546,   9591.559,  11639.513,      0.862],
            [    -0.523,      0.413,      0.745,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]],

           [[-12160.796,   9595.701,  11646.99 ,      0.914],
            [    -0.523,      0.413,      0.745,      0.   ],
            [    -0.619,     -0.785,      0.   ,    440.   ],
            [     0.   ,      0.   ,      0.   ,      0.   ]]], dtype=float32)

    In [5]: a.q[26]
    Out[5]: array([b'TO BT BT AB                                                                                     '], dtype='|S96')

    In [6]: b.q[36]
    Out[6]: array([b'TO BT BT AB                                                                                     '], dtype='|S96')





