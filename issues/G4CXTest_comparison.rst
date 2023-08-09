G4CXTest_comparison (formerly called G4CXAppTest) : CPU/GPU comparison of single PMT simulation
================================================================================================

Context
--------

* previous :doc:`G4CXTest_shakedown`


Standalone bi-simulation workflow
-----------------------------------

::

    o ; ./bin/rsync_put.sh             # laptop
    o ; oo                             # workstation  
    gxt ; ./G4CXTest.sh                # workstation
    gxt ; ./G4CXTest.sh grab           # laptop
    PICK=AB MODE=2 ./G4CXTest.sh ana   # laptop

    GEOM get # laptop


* When updating qsim.h need to build both qu and cx 


Initial issues
---------------

1. Looks like B (on workstation) is POM:0 with photons not entering PMT with Custom4 "0.1.5"
2. Bizarrely B on laptop looks more normal POM:1 with current Custom4 "0.1.6" 

   * this was because the older C4 on workstation still had the old E_s2 polarization bug 

3. A has no SD, so no hits, missing GBndLib__SENSOR_BOUNDARY_LIST ?

   * after rejig of U4SensorIdentifierDefault::getGlobalIdentity now get SD and hits, but discrepant 


Overview
----------

* DONE : U4SensorIdentifierDefault::getGlobalIdentity rejig giving SD and hits to A and avoiding lpmtid -1  
* DONE : GPU side PIDX dumping single photons down to ARTE level  
* DONE : CPU side PIDX dumping single photons down to ARTE level, dev on laptop  
* DONE : tag Custom4 0.1.6 and get that going on workstation (with E_s2 bug fixed), with a clean build 
* DONE : arrange more convenient Custom4 updating on workstation to facilitate debugging 

  * ~/j/issues/Custom4_dev_setup_on_workstation.rst 




HMM : seems are picking up unintended ancient Custom4 header
---------------------------------------------------------------

::

    N[blyth@localhost include]$ pwd
    /data/blyth/junotop/ExternalLibs/opticks/head/include
    N[blyth@localhost include]$ l
    total 52
     0 drwxrwxr-x.  2 blyth blyth  237 Aug  6 23:38 Custom4
    12 drwxrwxr-x.  2 blyth blyth 8192 Aug  6 23:14 SysRap
     0 drwxrwxr-x.  2 blyth blyth  122 Aug  6 23:13 OKConf
     4 drwxrwxr-x.  2 blyth blyth 4096 Aug  6 23:05 U4
     0 drwxrwxr-x.  2 blyth blyth   73 Aug  6 03:24 G4CX
     ...

::

    N[blyth@localhost include]$ l Custom4/
    total 96
     0 drwxrwxr-x.  2 blyth blyth   237 Aug  6 23:38 .
     0 drwxrwxr-x. 19 blyth blyth   243 Jul  2 03:02 ..
     4 -rw-r--r--.  1 blyth blyth   718 Jul  2 03:02 C4CustomART_Debug.h
    16 -rw-r--r--.  1 blyth blyth 12430 Jul  2 03:02 C4CustomART.h
     4 -rw-r--r--.  1 blyth blyth  2079 Jul  2 03:02 C4GS.h
    24 -rw-r--r--.  1 blyth blyth 23517 Jul  2 03:02 C4MultiLayrStack.h
    12 -rw-r--r--.  1 blyth blyth 12262 Jul  2 03:02 C4OpBoundaryProcess.hh
     8 -rw-r--r--.  1 blyth blyth  6105 Jul  2 03:02 C4Pho.h
     4 -rw-r--r--.  1 blyth blyth   442 Jul  2 03:02 C4Sys.h
     8 -rw-r--r--.  1 blyth blyth  5415 Jul  2 03:02 C4Touchable.h
     8 -rw-r--r--.  1 blyth blyth  5483 Jul  2 03:02 C4Track.h
     4 -rw-r--r--.  1 blyth blyth  3831 Jul  2 03:02 C4TrackInfo.h
     4 -rw-r--r--.  1 blyth blyth   453 Mar 24 00:03 C4IPMTAccessor.h
    N[blyth@localhost include]$ pwd
    /data/blyth/junotop/ExternalLibs/opticks/head/include
    N[blyth@localhost include]$ 


    N[blyth@localhost head]$ l lib64/*Custom4*
    496 -rwxr-xr-x. 1 blyth blyth 507352 Jul  2 03:02 lib64/libCustom4.so

    lib64/Custom4-0.1.4:
    total 16
    4 drwxrwxr-x. 5 blyth blyth 4096 Aug  6 23:19 ..
    0 drwxrwxr-x. 2 blyth blyth   86 Jul  2 03:02 .
    4 -rw-r--r--. 1 blyth blyth  142 Jul  2 03:02 C4Version.h
    4 -rw-r--r--. 1 blyth blyth 2238 Jul  2 03:02 Custom4Config.cmake
    4 -rw-r--r--. 1 blyth blyth 3678 Jul  2 03:02 Custom4ConfigVersion.cmake
    N[blyth@localhost head]$ 
    N[blyth@localhost head]$ rm lib64/libCustom4.so
    N[blyth@localhost head]$ rm -rf lib64/Custom4-0.1.4
    N[blyth@localhost head]$ l lib/*Custom4*


Now observe that Custom4 lacking debug symbols
------------------------------------------------

::

    BP=C4CustomART::doIt ./G4CXAppTest.sh 




::

    (gdb) f 1
    #1  0x00007fffec576e4c in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.6/lib64/libCustom4.so
    (gdb) f 0
    #0  0x00007fffec57a6c0 in C4CustomART::doIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.6/lib64/libCustom4.so
    (gdb) list
    Line number 23 out of range; /data/blyth/junotop/opticks/g4cx/tests/G4CXAppTest.cc has 22 lines.
    (gdb) 




DONE : Adopt Custom4 0.1.6 (fixing E_s2 bug) : are getting closer : but still sizable discreps
--------------------------------------------------------------------------------------------------

::

    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :   469.0703 c2n :    26.0000 c2per:    18.0412  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  469.07/26:18.041 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '  3647   3859' ' 5.9877' '   136    128']
     [' 1' 'TO BT SA                                                                                       ' ' 1' '  3127   3264' ' 2.9368' '   134    123']
     [' 2' 'TO BT BT SR SA                                                                                 ' ' 2' '   544    488' ' 3.0388' '  1641   1204']
     [' 3' 'TO BT BT SR BT BT SA                                                                           ' ' 3' '   407    435' ' 0.9311' '  2657   2162']
     [' 4' 'TO BT BT SA                                                                                    ' ' 4' '   416    435' ' 0.4242' '  1635   1049']
     [' 5' 'TO BT BR BT SA                                                                                 ' ' 5' '   212    315' '20.1309' '  1678    133']
     [' 6' 'TO SA                                                                                          ' ' 6' '   228    224' ' 0.0354' '     0      0']
     [' 7' 'TO BR SA                                                                                       ' ' 7' '   150    104' ' 8.3307' '   116    116']
     [' 8' 'TO BT BT SR BR SR SA                                                                           ' ' 8' '    94    117' ' 2.5071' '  3107   2316']
     [' 9' 'TO BT BT SR BR SA                                                                              ' ' 9' '    53    111' '20.5122' '  2708   2186']



After rejig of U4SensorIdentifierDefault::getGlobalIdentity
--------------------------------------------------------------

::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '  4391   5108' '54.1203' '   136    127']
     [' 1' 'TO BT SA                                                                                       ' ' 1' '  3760   4474' '61.9135' '   134    129']
     [' 2' 'TO BT BR BT SA                                                                                 ' ' 2' '   257     25' '190.8652' '  1678    150']
     [' 3' 'TO BT BT SR SA                                                                                 ' ' 3' '   230      0' '230.0000' '  1641     -1']
     [' 4' 'TO SA                                                                                          ' ' 4' '   228    224' ' 0.0354' '     0      0']
     [' 5' 'TO BT BT SA                                                                                    ' ' 5' '   180      3' '171.1967' '  1882   4853']
     [' 6' 'TO BT BT SR BT BT SA                                                                           ' ' 6' '   179      0' '179.0000' '  2684     -1']
     [' 7' 'TO BR SA                                                                                       ' ' 7' '   150    104' ' 8.3307' '   116    116']
     [' 8' 'TO BT BT SR BR SR SA                                                                           ' ' 8' '    54      0' '54.0000' '  3322     -1']
     [' 9' 'TO BT AB                                                                                       ' ' 9' '    49     26' ' 7.0533' '   201    438']
     ['10' 'TO BT BR BR BR BR BR SA                                                                        ' '10' '    48      0' '48.0000' '   326     -1']
     ['11' 'TO BT BR BR BR BR SA                                                                           ' '11' '    42      0' '42.0000' '   135     -1']
     ['12' 'TO BT BT SR BR SA                                                                              ' '12' '    36      0' '36.0000' '  3383     -1']
     ['13' 'TO BT BR BR BR BR BR BR SA                                                                     ' '13' '    36      0' '36.0000' '   805     -1']
     ['14' 'TO BT BT SR BR SR SR SA                                                                        ' '14' '    26      0' ' 0.0000' '  3418     -1']
     ['15' 'TO BT BR BR SD                                                                                 ' '15' '    22      0' ' 0.0000' '  1352     -1']
     ['16' 'TO BT BT SR BR SR BT BT SA                                                                     ' '16' '    20      0' ' 0.0000' '  3734     -1']
     ['17' 'TO AB                                                                                          ' '17' '    15     19' ' 0.4706' '    39     14']
     ['18' 'TO BT BT SR SR SR SR SR SR BR BR BR BR SA                                                      ' '18' '    18      0' ' 0.0000' '  2270     -1']


This is still with Custom4 0.1.5

::

    In [2]: a.f.NPFold_meta
    Out[2]: 
    source:G4CXOpticks::init_SEvt
    creator:G4CXAppTest
    stamp:1691263497354932
    stampFmt:2023-08-06T03:24:57.354932
    uname:Linux localhost.localdomain 3.10.0-957.10.1.el7.x86_64 #1 SMP Mon Mar 18 15:06:45 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
    HOME:/home/blyth
    USER:blyth
    PWD:/data/blyth/junotop/opticks/g4cx/tests
    CHECK:rain_line
    LAYOUT:one_pmt
    VERSION:0
    GEOM:FewPMT
    ${GEOM}_GEOMList:nnvtLogicalPMT
    C4Version:0.1.5

    In [3]: b.f.NPFold_meta
    Out[3]: 
    source:U4Recorder::init_SEvt
    creator:G4CXAppTest
    stamp:1691263495165218
    stampFmt:2023-08-06T03:24:55.165218
    uname:Linux localhost.localdomain 3.10.0-957.10.1.el7.x86_64 #1 SMP Mon Mar 18 15:06:45 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
    HOME:/home/blyth
    USER:blyth
    PWD:/data/blyth/junotop/opticks/g4cx/tests
    CHECK:rain_line
    LAYOUT:one_pmt
    VERSION:0
    GEOM:FewPMT
    ${GEOM}_GEOMList:nnvtLogicalPMT
    C4Version:0.1.5


NEXT : tag Custom4 0.1.6 and get that operational on workstation 
-------------------------------------------------------------------

Differences between 0.1.5 and currently untagged "0.1.6" 

* polarization E_s2 bug fix could have cause large changes
* BUT why the A/B difference : would have expected the bug to 
  have equal effect on A and B ? 


::

    epsilon:~ blyth$ cd /usr/local/opticks_externals/custom4/
    epsilon:custom4 blyth$ diff -r --brief 0.1.5 0.1.6 
    Files 0.1.5/include/Custom4/C4MultiLayrStack.h and 0.1.6/include/Custom4/C4MultiLayrStack.h differ
    Files 0.1.5/include/Custom4/C4Version.h and 0.1.6/include/Custom4/C4Version.h differ
    Only in 0.1.5/lib: Custom4-0.1.5
    Only in 0.1.6/lib: Custom4-0.1.6
    Files 0.1.5/lib/libCustom4.dylib and 0.1.6/lib/libCustom4.dylib differ
    epsilon:custom4 blyth$ 

    epsilon:custom4 blyth$ diff 0.1.5/include/Custom4/C4MultiLayrStack.h 0.1.6/include/Custom4/C4MultiLayrStack.h 
    602a603,614
    >       
    >     /*
    >     BUG FIX July 2023: 
    >         using norm(stst) to give sin_theta*sin_theta is incorrect
    >         because stst is already squared and the norm squares it again 
    >         Found that bug, because it leads to SF of 2. which is nonsensical (SF must be from 0. to 1. ) 
    >         which gave a polarization specific A of greater than 1. 
    >           
    >     BUG: const F E_s2 = norm(stst)   > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/norm(stst) : zero ;
    >     OK : const F E_s2 = l0.st.real() > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/(l0.st.real()*l0.st.real()) : zero ;
    >     */
    >     const F E_s2 = stst.real() > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/stst.real() : zero ;
    604d615
    <     const F E_s2 = norm(stst) > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/norm(stst) : zero ;
    607a619,624
    > #ifdef MOCK_CURAND_DEBUG
    >     printf("//stack.calc dot_pol_cross_mom_nrm %7.3f norm(stst) %7.3f l0.st (%7.3f,%7.3f) E_s2 %7.3f \n", 
    >             dot_pol_cross_mom_nrm, norm(stst), l0.st.real(), l0.st.imag(), E_s2 ); 
    > #endif
    > 
    > 





Single photon PIDX debug 
--------------------------

::

    In [3]: a.f.record[:,0,0]
    Out[3]: 
    array([[ 260.   ,    0.   ,  195.   ,    0.   ],
           [ 259.948,    0.   ,  195.   ,    0.   ],
           [ 259.896,    0.   ,  195.   ,    0.   ],
           [ 259.844,    0.   ,  195.   ,    0.   ],
           [ 259.792,    0.   ,  195.   ,    0.   ],
           ...,
           [-259.74 ,    0.   ,  195.   ,    0.   ],
           [-259.792,    0.   ,  195.   ,    0.   ],
           [-259.844,    0.   ,  195.   ,    0.   ],
           [-259.896,    0.   ,  195.   ,    0.   ],
           [-259.948,    0.   ,  195.   ,    0.   ]], dtype=float32)

    In [5]: a.f.record[5000,0]
    Out[5]: 
    array([[  0.,   0., 195.,   0.],
           [  0.,   0.,  -1.,   0.],
           [ -0.,  -1.,  -0., 420.],
           [  0.,   0.,   0.,   0.]], dtype=float32)

    In [6]: a.f.record[5001,0]
    Out[6]: 
    array([[ -0.052,   0.   , 195.   ,   0.   ],
           [  0.   ,   0.   ,  -1.   ,   0.   ],
           [ -0.   ,  -1.   ,  -0.   , 420.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)


    In [7]: a.q[5000]
    Out[7]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [8]: a.q[5001]
    Out[8]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [9]: a.q[5000-10:5000+10]
    Out[9]: 
    array([[b'TO BT BT SA                                                                                     '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SA                                                                                     ']], dtype='|S96')


    In [9]: a.q[5000-10:5000+10]
    Out[9]: 
    array([[b'TO BT BT SA                                                                                     '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SA                                                                                     ']], dtype='|S96')

    In [10]: b.f.record[5000,0]
    Out[10]: 
    array([[  0.,   0., 195.,   0.],
           [  0.,   0.,  -1.,   0.],
           [ -0.,  -1.,  -0., 420.],
           [  0.,   0.,   0.,   0.]], dtype=float32)

    In [11]: b.q[5000-10:5000+10]
    Out[11]: 
    array([[b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        ']], dtype='|S96')



    In [14]: a.q[5001]
    Out[14]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [13]: b.q[5001]
    Out[13]: array([b'TO BT SD                                                                                        '], dtype='|S96')



Pick PIDX 5001 : Aim to dump ART values to see whats up
----------------------------------------------------------

::

    //qsim.propagate idx 5001 bnc 0 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.92535669 logf(u_absorption) -0.07757594 absorption_length 37213.9219 absorption_distance 2886.905029 
    //qsim.propagate idx 5001 bounce 0 command 3 flag 0 s.optical.x 0 s.optical.y 1 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 1 
    //qsim.propagate_at_boundary idx 5001 nrm   (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_at_boundary idx 5001 mom_0 (    0.0000     0.0000    -1.0000) 
    //qsim.propagate_at_boundary idx 5001 pol_0 (   -0.0000    -1.0000    -0.0000) 
    //qsim.propagate_at_boundary idx 5001 c1     1.0000 normal_incidence 0 
    //qsim.propagate_at_boundary idx 5001 normal_incidence 0 p.pol (   -0.0000,   -1.0000,   -0.0000) p.mom (    0.0000,    0.0000,   -1.0000) o_normal (   -0.0001,    0.0000,    1.0000)
    //qsim.propagate_at_boundary idx 5001 TransCoeff     0.9979 n1c1     1.3540 n2c2     1.4843 E2_t (   -0.9541,    0.0000) A_trans (    0.0000,    1.0000,    0.0000) 
    //qsim.propagate_at_boundary idx 5001 u_reflect     0.5400 TransCoeff     0.9979 reflect 0 
    //qsim.propagate_at_boundary idx 5001 reflect 0 tir 0 TransCoeff     0.9979 u_reflect     0.5400 
    //qsim.propagate_at_boundary idx 5001 mom_1 (    0.0000     0.0000    -1.0000) 
    //qsim.propagate_at_boundary idx 5001 pol_1 (    0.0000    -1.0000     0.0000) 
    //qsim.propagate idx 5001 bnc 1 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.81189805 logf(u_absorption) -0.20838045 absorption_length  1562.9586 absorption_distance 325.690002 
    //qsim.propagate idx 5001 bounce 1 command 3 flag 0 s.optical.x 7 s.optical.y 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 lposcost   1.000 
    //qsim.propagate_at_surface_CustomART idx 5001 ARTE (   0.565   0.223   0.777   0.000 ) u_theAbsorption    0.369 action 1 

* SMOKING GUN : ARE GETTING theEfficiency zero 

::

    //qsim.propagate_at_boundary idx 5001 pol_1 (    0.0000    -1.0000     0.0000) 
    //qsim.propagate idx 5001 bnc 1 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.81189805 logf(u_absorption) -0.20838045 absorption_length  1562.9586 absorption_distance 325.690002 
    //qsim.propagate idx 5001 bounce 1 command 3 flag 0 s.optical.x 7 s.optical.y 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 lposcost   1.000 
    //qsim::propagate_at_surface_CustomART p.mom                 (  0.000   0.000  -1.000) 
    //qsim::propagate_at_surface_CustomART p.pol                 (  0.000  -1.000   0.000) 
    //qsim::propagate_at_surface_CustomART normal                ( -0.000   0.000   1.000) 
    //qsim::propagate_at_surface_CustomART cross_mom_nrm         (  0.000   0.000   0.000) 
    //qsim::propagate_at_surface_CustomART dot_pol_cross_mom_nrm:  -0.000 
    //qsim::propagate_at_surface_CustomART minus_cos_theta         -1.000 
    //qsim::propagate_at_surface_CustomART idx 5001 lpmtid -1 wl 420.000 mct  -1.000 dpcmn  -0.000 ARTE (   0.565   0.223   0.777   0.000 ) 
    //qsim.propagate_at_surface_CustomART idx 5001 lpmtid -1 ARTE (   0.565   0.223   0.777   0.000 ) u_theAbsorption    0.369 action 1 
    2023-08-05 20:53:31.051 INFO  [207652] [QEvent::gatherComponent@643] [ cmp 2


* HMM : lpmtid -1 

::

    1469 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, curandStateXORWOW& rng, sctx& ctx) const
    1470 {
    1471     const sphoton& p = ctx.p ;
    1472     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal 
    1473     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor  
    1474     float minus_cos_theta = dot(p.mom, *normal); 
    1475     float dot_pol_cross_mom_nrm = dot(p.pol,cross(p.mom,*normal)) ;
    1476     

    447 extern "C" __global__ void __closesthit__ch()
    448 {
    449     unsigned iindex = optixGetInstanceIndex() ;    // 0-based index within IAS
    450     unsigned instance_id = optixGetInstanceId() ;  // user supplied instanceId, see IAS_Builder::Build 
    451     unsigned prim_idx = optixGetPrimitiveIndex() ; // GAS_Builder::MakeCustomPrimitivesBI_11N  (1+index-of-CSGPrim within CSGSolid/GAS)
    452 
    453     //unsigned identity = (( prim_idx & 0xffff ) << 16 ) | ( instance_id & 0xffff ) ; 
    454     unsigned identity = instance_id ;  // CHANGED July 2023, as now carrying sensor_identifier, see sysrap/sqat4.h 
    455 

    366     QAT4_METHOD int get_IAS_OptixInstance_instanceId() const
    367     {
    368         //const unsigned& ins_idx = q0.u.w ;  
    369         //return ins_idx ; 
    370         const int& sensor_identifier = q2.i.w ;
    371         assert( sensor_identifier >= 0 );  // 0 means not a sensor GPU side, so subtract 1 to get actual sensorId
    372         return sensor_identifier ;
    373     }


* DONE: added protection against not-a-sensor (from identity 0) which yields lpmtid -1 
* TODO: find why getting not-a-sensor


ems
-----


::

     08 enum {
      9     smatsur_Material                       = 0,
     10     smatsur_NoSurface                      = 1,
     11     smatsur_Surface                        = 2,
     12     smatsur_Surface_zplus_sensor_A         = 3,
     13     smatsur_Surface_zplus_sensor_CustomART = 4,
     14     smatsur_Surface_zminus                 = 5
     15 
     16 };


DONE : Added qsim.h handling for lpmtid < 0 
-------------------------------------------------

* ~/opticks/notes/issues/qsim_propagate_at_surface_CustomART_NOT-A-SENSOR_error.rst


DONE : rejig U4SensorIdentifierDefault::getGlobalIdentity 
-----------------------------------------------------------

* now depends on (pv,ppv) to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST
* this was needed because the small FewPMT geometry with 1 PMT is purely global with no instances 

::

    epsilon:opticks blyth$ git commit -m "rejig U4SensorIdentifierDefault::getGlobalIdentity to depend on pv ppv to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST "
    [master 151de19ce] rejig U4SensorIdentifierDefault::getGlobalIdentity to depend on pv ppv to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST
     13 files changed, 274 insertions(+), 32 deletions(-)
     create mode 100644 u4/U4Boundary.h
    epsilon:opticks blyth$ git push 


This avoids the lpmtid -1 






rain_line : Generated Input Positions dont match exactly
------------------------------------------------------------

::

    In [31]: xa = a.f.record[:,0,0,0]
    In [32]: xb = b.f.record[:,0,0,0]

    In [42]: np.c_[xa,xb,(xa-xb)*1e6][np.abs(xa-xb)>40e-6]
    Out[42]: 
    array([[-138.424, -138.424,  -45.776],
           [-139.152, -139.152,  -45.776],
           [-139.88 , -139.88 ,  -45.776],
           [-140.608, -140.608,  -45.776],
           [-141.336, -141.336,  -45.776],
           [-142.064, -142.064,  -45.776],
           [-146.068, -146.068,  -45.776],
           [-146.796, -146.796,  -45.776],
           [-147.524, -147.524,  -45.776],
           [-148.252, -148.252,  -45.776],
           [-148.98 , -148.98 ,  -45.776],
           [-149.708, -149.708,  -45.776],
           [-170.924, -170.924,  -45.776],
           [-171.652, -171.652,  -45.776],



    In [30]: np.c_[a.f.record[:,0,0,0],b.f.record[:,0,0,0],(a.f.record[:,0,0,0]-b.f.record[:,0,0,0])*1e6][1000:1010]
    Out[30]: 
    array([[208.   , 208.   ,   0.   ],
           [207.948, 207.948,   0.   ],
           [207.896, 207.896,   0.   ],
           [207.844, 207.844,   0.   ],
           [207.792, 207.792,   0.   ],
           [207.74 , 207.74 ,   0.   ],
           [207.688, 207.688,   0.   ],
           [207.636, 207.636, -15.259],
           [207.584, 207.584,   0.   ],
           [207.532, 207.532,   0.   ]], dtype=float32)


    In [43]: xab = np.abs(xa-xb)
    In [46]: np.unique(xab*1e6, return_counts=True )
    Out[46]: 
    (array([ 0.   , 15.259, 15.497, 15.736, 16.212, 17.166, 19.073, 22.888, 30.518, 30.994, 31.471, 32.425, 34.332, 38.147, 45.776, 61.035], dtype=float32),
     array([5026, 1787,   60,   29,   30,   29,   24,   20, 2736,   62,   33,   32,   34,   42,   54,    2]))



rain_point : target the apex : agrees
---------------------------------------

u4/tests/storch_FillGenstep.sh::

    +    elif [ "$CHECK" == "rain_point" ]; then
    +
    +        ttype=point
    +        pos=0,0,195    ## 190 grazes HAMA apex
    +        mom=0,0,-1   
    +        radius=0  


::

    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :     6.5909 c2n :     6.0000 c2per:     1.0985  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)   6.59/6:1.098 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD         ' ' 0' '  3452   3445' ' 0.0071' '     4      1']
     [' 1' 'TO BT BT SA      ' ' 1' '  3249   3323' ' 0.8332' '     2      2']
     [' 2' 'TO BT SA         ' ' 2' '  2970   2945' ' 0.1057' '     1      0']
     [' 3' 'TO BT BR BT SA   ' ' 3' '   261    240' ' 0.8802' '     0    133']
     [' 4' 'TO BT AB         ' ' 4' '    43     25' ' 4.7647' '    75    176']
     [' 5' 'TO BR SA         ' ' 5' '    20     20' ' 0.0000' '   159    170']
     [' 6' 'TO AB            ' ' 6' '     2      1' ' 0.0000' '   336    371']
     [' 7' 'TO SC SA         ' ' 7' '     1      0' ' 0.0000' '  7203     -1']
     [' 8' 'TO BT BR BT SC SA' ' 8' '     1      0' ' 0.0000' '  2359     -1']
     [' 9' 'TO BT BR AB      ' ' 9' '     1      1' ' 0.0000' '  3918   4419']]




DONE : revive simtrace so can use it as backdrop for single photon plotting
----------------------------------------------------------------------------

Developing in::

    G4CXSimtraceMinTest.sh 
    G4CXSimtraceMinTest.py


rain_point_xpositive_100 : vertically down offset at x +100
--------------------------------------------------------------

::

     60     elif [ "${CHECK:0:21}" == "rain_point_xpositive_" ]; then
     61 
     62         xpos=${CHECK:21}
     63         ttype=point
     64         pos=$xpos,0,195    ## 190 grazes HAMA apex
     65         mom=0,0,-1  
     66         radius=0 
     67 


::

    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :   989.9877 c2n :    17.0000 c2per:    58.2346  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  989.99/17:58.235 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                        ' ' 0' '  3470   3483' ' 0.0243' '     4      4']
     [' 1' 'TO BT SA                                                                        ' ' 1' '  2989   3094' ' 1.8124' '     1      1']
     [' 2' 'TO BT BT SR SA                                                                  ' ' 2' '  1267    864' '76.2126' '     2      8']
     [' 3' 'TO BT BT SR BT BT SA                                                            ' ' 3' '  1154    915' '27.6080' '    24      0']
     [' 4' 'TO BT BT SR BR SR SA                                                            ' ' 4' '   167    303' '39.3532' '   162     28']
     [' 5' 'TO BT BT SR BR SR BT BT SA                                                      ' ' 5' '     0    294' '294.0000' '    -1     40']
     [' 6' 'TO BT BR BT SA                                                                  ' ' 6' '   280    287' ' 0.0864' '     0    123']
     [' 7' 'TO BT BT SA                                                                     ' ' 7' '   242    243' ' 0.0021' '     7     33']
     [' 8' 'TO BT BT SR BR SR BR SR BT BT SA                                                ' ' 8' '     0    114' '114.0000' '    -1     13']
     [' 9' 'TO BT BT SR BR SR BR SR SA                                                      ' ' 9' '     0    113' '113.0000' '    -1     14']
     ['10' 'TO BT BT SR BR SR SR SA                                                         ' '10' '   111      0' '111.0000' '    62     -1']
     ['11' 'TO BT BT SR BR SA                                                               ' '11' '    34     79' '17.9204' '    31    228']
     ['12' 'TO BT BT SR BR SR SR SR SR SA                                                   ' '12' '    77      0' '77.0000' '   127     -1']
     ['13' 'TO BT BT SR BR SR SR SR SR BT BT SA                                             ' '13' '    72      0' '72.0000' '    69     -1']
     ['14' 'TO BT AB                                                                        ' '14' '    43     22' ' 6.7846' '    75    357']
     ['15' 'TO BT BT SR BR SR BR SR BR SR SA                                                ' '15' '     0     39' '39.0000' '    -1    173']
     ['16' 'TO BT BT SR BR SR BR SA                                                         ' '16' '     0     28' ' 0.0000' '    -1    785']
     ['17' 'TO BR SA                                                                        ' '17' '    23     26' ' 0.1837' '   159     38']
     ['18' 'TO BT BT SR BR SR BR SR BR SR BT BT SA                                          ' '18' '     0     22' ' 0.0000' '    -1      9']
     ['19' 'TO BT BT SR BR SR BR SR BR SR BR SR SA                                          ' '19' '     0     19' ' 0.0000' '    -1    394']
     ['20' 'TO BT BT SR BT BR SD                                                            ' '20' '    13      0' ' 0.0000' '  1181     -1']
     ['21' 'TO BT BT SR BR SR BR SR BR SR BR SR BT BT SA                                    ' '21' '     0     11' ' 0.0000' '    -1    405']
     ['22' 'TO BT BT SR BR SR SR SR SA                                                      ' '22' '     8      0' ' 0.0000' '   119     -1']
     ['23' 'TO BT BT SR BR SR BR SR BR SA                                                   ' '23' '     0      7' ' 0.0000' '    -1    459']
     ['24' 'TO BT BT SR BR SR BR SR BR SR BR SR BR SR SA                                    ' '24' '     0      6' ' 0.0000' '    -1    627']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [['10' 'TO BT BT SR BR SR SR SA                                                         ' '10' '   111      0' '111.0000' '    62     -1']
     ['12' 'TO BT BT SR BR SR SR SR SR SA                                                   ' '12' '    77      0' '77.0000' '   127     -1']
     ['13' 'TO BT BT SR BR SR SR SR SR BT BT SA                                             ' '13' '    72      0' '72.0000' '    69     -1']
     ['20' 'TO BT BT SR BT BR SD                                                            ' '20' '    13      0' ' 0.0000' '  1181     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [[' 5' 'TO BT BT SR BR SR BT BT SA                                                      ' ' 5' '     0    294' '294.0000' '    -1     40']
     [' 8' 'TO BT BT SR BR SR BR SR BT BT SA                                                ' ' 8' '     0    114' '114.0000' '    -1     13']
     [' 9' 'TO BT BT SR BR SR BR SR SA                                                      ' ' 9' '     0    113' '113.0000' '    -1     14']
     ['15' 'TO BT BT SR BR SR BR SR BR SR SA                                                ' '15' '     0     39' '39.0000' '    -1    173']
     ['16' 'TO BT BT SR BR SR BR SA                                                         ' '16' '     0     28' ' 0.0000' '    -1    785']
     ['18' 'TO BT BT SR BR SR BR SR BR SR BT BT SA                                          ' '18' '     0     22' ' 0.0000' '    -1      9']
     ['19' 'TO BT BT SR BR SR BR SR BR SR BR SR SA                                          ' '19' '     0     19' ' 0.0000' '    -1    394']
     ['21' 'TO BT BT SR BR SR BR SR BR SR BR SR BT BT SA                                    ' '21' '     0     11' ' 0.0000' '    -1    405']]
    PICK=AB MODE=0 SEL=0 ./G4CXAppTest.sh ana 



* Use onephotonplot implemented above to investigate

::

    In [1]: a.q_startswith("TO BT BT SR BR SR SR SA")
    Out[1]: 
    array([  62,  236,  267,  319,  349,  446,  589,  672,  751,  812,  837,  933,  972, 1043, 1068, 1098, 1327, 1336, 1433, 1514, 1713, 1742, 1910, 1948, 1959, 2155, 2157, 2238, 2303, 2366, 2519, 2557,
           3052, 3297, 3420, 3438, 3580, 3645, 3674, 3761, 3770, 3817, 3827, 3863, 3881, 4015, 4061, 4144, 4194, 4552, 4569, 4740, 4808, 4896, 4902, 4952, 5057, 5080, 5090, 5105, 5199, 5283, 5308, 5419,
           5465, 5519, 5651, 5670, 5724, 5871, 5927, 6005, 6072, 6137, 6288, 6473, 6595, 6620, 6675, 6936, 6983, 7071, 7105, 7189, 7215, 7274, 7288, 7416, 7433, 7561, 7590, 7765, 7966, 8138, 8155, 8277,
           8358, 8409, 8489, 8710, 8723, 8889, 8987, 9188, 9270, 9463, 9742, 9815, 9854, 9892, 9930])


    MODE=2 APID=62 ./G4CXSimtraceMinTest.sh   ## bounce around inside ending just under lip 




    In [1]: a.q_startswith("TO BT BT SR BR SR SR SR SR SA")
    Out[1]: 
    array([ 127,  204,  263,  757,  891,  996, 1007, 1452, 1646, 1922, 2071, 2379, 2461, 2530, 2544, 2555, 2633, 2755, 2819, 2870, 2871, 2910, 3479, 3496, 3521, 3560, 3614, 3734, 3785, 3926, 4042, 4081,
           4166, 4465, 4607, 4861, 5013, 5043, 5340, 5413, 5823, 5845, 6118, 6234, 6395, 6489, 6626, 6666, 6889, 6976, 7044, 7049, 7323, 7353, 7430, 7449, 7487, 7533, 7851, 8014, 8166, 8178, 8544, 8609,
           8706, 8790, 8924, 9325, 9347, 9378, 9416, 9512, 9525, 9625, 9722, 9819, 9976])


    MODE=2 APID=127 ./G4CXSimtraceMinTest.sh   ## bouce around inside passing the lip and ending by absorbing on inside of special surface



::

    In [1]: a.q_startswith("TO BT BT SR BR SR SR SR SR BT BT SA")
    Out[1]: 
    array([  69,   80,  406,  461,  724,  882,  905,  910, 1029, 1077, 1121, 1300, 1465, 1702, 1836, 1932, 2130, 2284, 2354, 2562, 2724, 2877, 3076, 3089, 3100, 3216, 3391, 3514, 3515, 3712, 3854, 4279,
           4455, 4583, 4925, 5188, 5257, 5298, 5327, 5390, 5644, 5792, 5830, 5994, 6009, 6013, 6039, 6145, 6170, 6172, 6311, 6513, 6574, 6590, 6594, 6606, 6722, 6732, 6814, 7260, 7281, 7396, 7490, 7529,
           7775, 8181, 8716, 8922, 8967, 9047, 9282, 9655])

    MODE=2 APID=69 ./G4CXSimtraceMinTest.sh  ## bounce around inside, passes lip, escapes before absorbed on rock 



::

    In [1]: a.q_startswith("TO BT BT SR BT BR SD") 
    Out[1]: array([1181, 2624, 4152, 4509, 4590, 4969, 7352, 7727, 8196, 8348, 8861, 9671, 9945])


::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [['10' 'TO BT BT SR BR SR SR SA                                                         ' '10' '   111      0' '111.0000' '    62     -1']
     ['12' 'TO BT BT SR BR SR SR SR SR SA                                                   ' '12' '    77      0' '77.0000' '   127     -1']
     ['13' 'TO BT BT SR BR SR SR SR SR BT BT SA                                             ' '13' '    72      0' '72.0000' '    69     -1']
     ['20' 'TO BT BT SR BT BR SD                                                            ' '20' '    13      0' ' 0.0000' '  1181     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [[' 5' 'TO BT BT SR BR SR BT BT SA                                                      ' ' 5' '     0    294' '294.0000' '    -1     40']
     [' 8' 'TO BT BT SR BR SR BR SR BT BT SA                                                ' ' 8' '     0    114' '114.0000' '    -1     13']
     [' 9' 'TO BT BT SR BR SR BR SR SA                                                      ' ' 9' '     0    113' '113.0000' '    -1     14']
     ['15' 'TO BT BT SR BR SR BR SR BR SR SA                                                ' '15' '     0     39' '39.0000' '    -1    173']
     ['16' 'TO BT BT SR BR SR BR SA                                                         ' '16' '     0     28' ' 0.0000' '    -1    785']
     ['18' 'TO BT BT SR BR SR BR SR BR SR BT BT SA                                          ' '18' '     0     22' ' 0.0000' '    -1      9']
     ['19' 'TO BT BT SR BR SR BR SR BR SR BR SR SA                                          ' '19' '     0     19' ' 0.0000' '    -1    394']
     ['21' 'TO BT BT SR BR SR BR SR BR SR BR SR BT BT SA                                    ' '21' '     0     11' ' 0.0000' '    -1    405']]



::

   MODE=2 BPID=40 APID=10 ./G4CXSimtraceMinTest.sh 



::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                        ' ' 0' '  3470   3483' ' 0.0243' '     4      4']
     [' 1' 'TO BT SA                                                                        ' ' 1' '  2989   3094' ' 1.8124' '     1      1']

     [' 2' 'TO BT BT SR SA                                                                  ' ' 2' '  1267    864' '76.2126' '     2      8']

     [' 3' 'TO BT BT SR BT BT SA                                                            ' ' 3' '  1154    915' '27.6080' '    24      0']
     [' 4' 'TO BT BT SR BR SR SA                                                            ' ' 4' '   167    303' '39.3532' '   162     28']
     [' 5' 'TO BT BT SR BR SR BT BT SA                                                      ' ' 5' '     0    294' '294.0000' '    -1     40']
     [' 6' 'TO BT BR BT SA                                                                  ' ' 6' '   280    287' ' 0.0864' '     0    123']

     [' 7' 'TO BT BT SA                                                                     ' ' 7' '   242    243' ' 0.0021' '     7     33']

     [' 8' 'TO BT BT SR BR SR BR SR BT BT SA                                                ' ' 8' '     0    114' '114.0000' '    -1     13']
     [' 9' 'TO BT BT SR BR SR BR SR SA                                                      ' ' 9' '     0    113' '113.0000' '    -1     14']
     ['10' 'TO BT BT SR BR SR SR SA                                                         ' '10' '   111      0' '111.0000' '    62     -1']
     ['11' 'TO BT BT SR BR SA                                                               ' '11' '    34     79' '17.9204' '    31    228']
     ['12' 'TO BT BT SR BR SR SR SR SR SA                                                   ' '12' '    77      0' '77.0000' '   127     -1']
     ['13' 'TO BT BT SR BR SR SR SR SR BT BT SA                                             ' '13' '    72      0' '72.0000' '    69     -1']
     ['14' 'TO BT AB                                                                        ' '14' '    43     22' ' 6.7846' '    75    357']




::

    [' 2' 'TO BT BT SR SA                                                                  ' ' 2' '  1267    864' '76.2126' '     2      8']

    MODE=2 APID=2 BPID=8 ./G4CXSimtraceMinTest.sh 


Slight difference in the angle coming from the last BT (on special surface) gets lever armed 
into a big difference that results in a bunch of different bounce histories.::

    [' 7' 'TO BT BT SA                                                                     ' ' 7' '   242    243' ' 0.0021' '     7     33']

    MODE=2 APID=7 BPID=33 ./G4CXSimtraceMinTest.sh 


HMM: the sharpness of the pencil beam position is at odds with trying 
to match calcs at different precisions.

How to confirm this interpretation ?

* use MOCK_CUDA to do the qsim calcs in float/double precision on CPU and compare that with A and B 
* ie is all the difference down to float/double ?

How to do comparisons in the light of this ?

* avoid pencil beams, instead compare using broad beams 



::

    In [1]: a.r
    Out[1]: 
    array([[[ 100.   ,    0.   ,  195.   ,    0.   ],
            [   0.   ,    0.   ,   -1.   ,    0.   ],
            [  -0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 100.   ,    0.   ,  169.141,    0.119],
            [  -0.027,    0.   ,   -0.999,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,   -0.   ,    0.   ]],

           [[  99.86 ,    0.   ,  163.974,    0.145],
            [   0.118,    0.   ,   -0.98 ,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,   -0.   ,    0.   ]],

           [[ 137.602,    0.   , -149.185,    1.21 ],
            [   0.118,    0.   ,   -0.98 ,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]]], dtype=float32)

    In [2]: b.r
    Out[2]: 
    array([[[ 100.   ,    0.   ,  195.   ,    0.   ],
            [   0.   ,    0.   ,   -1.   ,    0.   ],
            [  -0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 100.   ,    0.   ,  169.141,    0.119],
            [  -0.027,    0.   ,   -1.   ,      nan],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  99.86 ,    0.   ,  163.975,    0.145],
            [   0.114,    0.   ,   -0.993,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 135.899,    0.   , -149.99 ,    1.199],
            [   0.114,    0.   ,   -0.993,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]]], dtype=float32)



rain_line
------------

* A:has double line around the Pyrex suggesting must be more issues than just precision difference, 
  these are probably from photons that TIR-ride around the Pyrex : but why doesnt that happen 
  for B:Geant4 too ? 


::

    PICK=AB MODE=2 ./G4CXAppTest.sh ana


    a.CHECK : rain_line 
    b.CHECK : rain_line 
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :   469.0703 c2n :    26.0000 c2per:    18.0412  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  469.07/26:18.041 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '  3647   3859' ' 5.9877' '   136    128']
     [' 1' 'TO BT SA                                                                                       ' ' 1' '  3127   3264' ' 2.9368' '   134    123']
     [' 2' 'TO BT BT SR SA                                                                                 ' ' 2' '   544    488' ' 3.0388' '  1641   1204']
     [' 3' 'TO BT BT SR BT BT SA                                                                           ' ' 3' '   407    435' ' 0.9311' '  2657   2162']
     [' 4' 'TO BT BT SA                                                                                    ' ' 4' '   416    435' ' 0.4242' '  1635   1049']
     [' 5' 'TO BT BR BT SA                                                                                 ' ' 5' '   212    315' '20.1309' '  1678    133']
     [' 6' 'TO SA                                                                                          ' ' 6' '   228    224' ' 0.0354' '     0      0']
     [' 7' 'TO BR SA                                                                                       ' ' 7' '   150    104' ' 8.3307' '   116    116']
     [' 8' 'TO BT BT SR BR SR SA                                                                           ' ' 8' '    94    117' ' 2.5071' '  3107   2316']
     [' 9' 'TO BT BT SR BR SA                                                                              ' ' 9' '    53    111' '20.5122' '  2708   2186']
     ['10' 'TO BT BR BR SD                                                                                 ' '10' '    75      2' '69.2078' '  1319    229']
     ['11' 'TO BT BT SR SR SA                                                                              ' '11' '    55     74' ' 2.7984' '  1685   1206']
     ['12' 'TO BT BR BR SA                                                                                 ' '12' '    70      2' '64.2222' '  1327   8857']
     ['13' 'TO BT BR BR BR BR BR BR SA                                                                     ' '13' '    65      0' '65.0000' '   802     -1']
     ['14' 'TO BT BR BR BR BR BR SA                                                                        ' '14' '    56      0' '56.0000' '   326     -1']
     ['15' 'TO BT BT SR BR SR BT BT SA                                                                     ' '15' '    30     53' ' 6.3735' '  3761   2324']
     ['16' 'TO BT AB                                                                                       ' '16' '    49     29' ' 5.1282' '   201    363']
     ['17' 'TO BT BT SR SR SR SR SR SR BR BR BR BR SA                                                      ' '17' '    46      0' '46.0000' '  2215     -1']
     ['18' 'TO BT BT SR BR SR SR SA                                                                        ' '18' '    43     32' ' 1.6133' '  2877   2571']
     ['19' 'TO BT BR BR BR BR SA                                                                           ' '19' '    40      0' '40.0000' '   135     -1']
     ['20' 'TO BT BT SR SR SR SA                                                                           ' '20' '    35     25' ' 1.6667' '  1717   1355']
     ['21' 'TO BT BR BR BR BR BR BR BR BR SA                                                               ' '21' '    31      0' '31.0000' '  1099     -1']
     ['22' 'TO BT BT SR SR BT BT SA                                                                        ' '22' '     1     29' ' 0.0000' '  4310   1858']
     ['23' 'TO BT BT SR BR SR SR BT BT SA                                                                  ' '23' '    25     29' ' 0.2963' '  2870   2408']
     ['24' 'TO BT BT SR SR SR BT BT SA                                                                     ' '24' '     0     26' ' 0.0000' '    -1   1385']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [['13' 'TO BT BR BR BR BR BR BR SA                                                                     ' '13' '    65      0' '65.0000' '   802     -1']
     ['14' 'TO BT BR BR BR BR BR SA                                                                        ' '14' '    56      0' '56.0000' '   326     -1']
     ['17' 'TO BT BT SR SR SR SR SR SR BR BR BR BR SA                                                      ' '17' '    46      0' '46.0000' '  2215     -1']
     ['19' 'TO BT BR BR BR BR SA                                                                           ' '19' '    40      0' '40.0000' '   135     -1']
     ['21' 'TO BT BR BR BR BR BR BR BR BR SA                                                               ' '21' '    31      0' '31.0000' '  1099     -1']
     ['27' 'TO BT BR BR BR BR BR BR BR SA                                                                  ' '27' '    24      0' ' 0.0000' '   840     -1']
     ['28' 'TO BT BT SR SR SR SR SR SR SR BR BR BR BR SA                                                   ' '28' '    23      0' ' 0.0000' '  2076     -1']
     ['30' 'TO BT BT SR SR SR SR SR SR BR BR BR SA                                                         ' '30' '    20      0' ' 0.0000' '  2071     -1']
     ['31' 'TO BT BT SR SR SR SR SR SR SR BR BR BR SA                                                      ' '31' '    20      0' ' 0.0000' '  2049     -1']
     ['33' 'TO BT BR BR BR BR BR BR BR BR BR SA                                                            ' '33' '    18      0' ' 0.0000' '  1335     -1']
     ['36' 'TO BT BT SR SR SR SR SR SR BR BR BR BR BR SA                                                   ' '36' '    12      0' ' 0.0000' '  2219     -1']
     ['40' 'TO BT BT SR SR SR SR SR SR SR SR BR BR BR SA                                                   ' '40' '    11      0' ' 0.0000' '  1935     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [['24' 'TO BT BT SR SR SR BT BT SA                                                                     ' '24' '     0     26' ' 0.0000' '    -1   1385']
     ['37' 'TO BT BT SR SR SR BR BT BT SA                                                                  ' '37' '     0     12' ' 0.0000' '    -1   1537']
     ['38' 'TO BT BT SR SR BR SR SR SA                                                                     ' '38' '     0     12' ' 0.0000' '    -1   1960']
     ['39' 'TO BT BT SR SR SR BR SA                                                                        ' '39' '     0     11' ' 0.0000' '    -1   1581']
     ['41' 'TO BT BT SR SR BR SA                                                                           ' '41' '     0     11' ' 0.0000' '    -1   1864']]



Hmm : a slight difference in rindex might explain could explain the small angle difference
----------------------------------------------------------------------------------------------


How to implement a double precision test of qsim ?
-----------------------------------------------------

CSG/ct.sh using CSG/tests/CSGSimtraceTest.cc 
    CSG intersect calcs on CPU using CSGQuery.cc making use of csg_intersect_tree.h intersect_prim



Q : Does float/double explain this rain_point_xpositive_100 difference for "TO BT BT SA" ?
---------------------------------------------------------------------------------------------

* SA positions at back hemi are a few mm offset after one crossing of the PMT 
 
  * would be surprised if that is from float/double
  * OR: is it down to a small rindex diff ?

::

    APID=7 BPID=33 MODE=2 ~/opticks/g4cx/tests/G4CXTest.sh tra


Do better that that find accidental history match (a lazy form of random alignment!)::

    In [5]: np.where( np.logical_and( a.q == b.q, np.char.startswith(a.q, b"TO BT BT SA") ))                                                     
    Out[5]: 
    (array([ 552, 1829, 4840, 6094, 6494, 6789, 9827]),
     array([0, 0, 0, 0, 0, 0, 0]))

Encapsulate that::

    In [2]: ab.q_startswith("TO BT BT SA")
    Out[2]: 
    (array([ 552, 1829, 4840, 6094, 6494, 6789, 9827]),
     array([0, 0, 0, 0, 0, 0, 0]))




    APID=552 BPID=552 MODE=2 ~/opticks/g4cx/tests/G4CXTest.sh tra



::

    N[blyth@localhost tests]$ PIDX=7 ./G4CXTest.sh 

    In [1]: a.pid                                                                                                                                                
    Out[1]: 552

    In [2]: b.pid                                                                                                                                                
    Out[2]: 552

    In [3]: a.r                                                                                                                                                  
    Out[3]: 
    array([[[ 100.   ,    0.   ,  195.   ,    0.   ],
            [   0.   ,    0.   ,   -1.   ,    0.   ],
            [  -0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 100.   ,    0.   ,  169.141,    0.119],
            [  -0.027,    0.   ,   -0.999,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,   -0.   ,    0.   ]],

           [[  99.86 ,    0.   ,  163.974,    0.145],
            [   0.118,    0.   ,   -0.98 ,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,   -0.   ,    0.   ]],

           [[ 137.602,    0.   , -149.185,    1.21 ],
            [   0.118,    0.   ,   -0.98 ,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]]], dtype=float32)

    In [4]: b.r                                                                                                                                                  
    Out[4]: 
    array([[[ 100.   ,    0.   ,  195.   ,    0.   ],
            [   0.   ,    0.   ,   -1.   ,    0.   ],
            [  -0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 100.   ,    0.   ,  169.141,    0.119],
            [  -0.027,    0.   ,   -1.   ,      nan],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  99.86 ,    0.   ,  163.975,    0.145],
            [   0.114,    0.   ,   -0.993,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 135.899,    0.   , -149.99 ,    1.199],
            [   0.114,    0.   ,   -0.993,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]]], dtype=float32)

    In [5]: a.r - b.r                                                                                                                                            
    Out[5]: 
    array([[[ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   , -0.   ,  0.   ]],

           [[ 0.   ,  0.   ,  0.   , -0.   ],
            [ 0.   ,  0.   ,  0.   ,    nan],
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   , -0.   ,  0.   ]],

           [[ 0.   ,  0.   , -0.   ,  0.   ],
            [ 0.004,  0.   ,  0.013,  0.   ],   ## FIRST LARGE DEVIATION : DIRECTION INSIDE Vacuum 
            [ 0.   ,  0.   ,  0.   ,  0.   ],
            [ 0.   ,  0.   , -0.   ,  0.   ]],

           [[ 1.703,  0.   ,  0.805,  0.011],
            [ 0.004,  0.   ,  0.013,  0.   ],
            [ 0.   ,  0.   , -0.   ,  0.   ],
            [ 0.   ,  0.   , -0.   ,  0.   ]]], dtype=float32)

    In [6]:                                                 


::

    C4OpBoundaryProcess::DielectricDielectric Rindex1 1.35398554 Rindex2 1.48426314
    C4OpBoundaryProcess::DielectricDielectric Rindex1 1.48426314 Rindex2 1.00000100 

    //qsim.propagate_at_boundary idx 552 (n1,n2,eta) (1.35398555 1.48426318 0.91222739) 
    //qsim.propagate_at_boundary idx 552 (n1,n2,eta) (1.48426318 1.00000095 1.48426175) 


    1.48426314  1.00000100
    1.48426318  1.00000095

    epsilon:tests blyth$ D=1.48426314 ~/opticks/sysrap/tests/float_double_test.sh 
     d 1.48426314
     f 1.48426318

    epsilon:tests blyth$ D=1.00000100 ~/opticks/sysrap/tests/float_double_test.sh 
     d 1.00000100
     f 1.00000095

::

     857     p.mom = reflect
     858                     ?
     859                        p.mom + 2.0f*c1*oriented_normal
     860                     :
     861                        eta*(p.mom) + (eta*c1 - c2)*oriented_normal
     862                     ;


::

    //qsim.propagate_at_boundary idx 552 p.mom (-0.02701617 0.00000000 -0.99930429)  
    //qsim.propagate_at_boundary idx 552 o_nrm (0.28830180 0.00000000 0.91605818)  
    //qsim.propagate_at_boundary idx 552 eta 1.48426175 eta*c1 1.37028480 c2 0.82136923 (eta*c1 - c2) 0.54891557 
    //qsim.propagate_at_boundary idx 552 reflect 0 tir 0 TransCoeff     0.9207 u_reflect     0.1287 
    //qsim.propagate_at_boundary idx 552 mom_1 (    0.1182     0.0000    -0.9804) 


::

    In [1]: mom = np.array([-0.02701617,0.00000000,-0.99930429])

    In [2]: mom
    Out[2]: array([-0.027,  0.   , -0.999])

    In [3]: eta = 1.48426175

    In [4]: mom*eta
    Out[4]: array([-0.04 ,  0.   , -1.483])

    In [5]: o_nrm = np.array([0.28830180,0.00000000,0.91605818])

    In [6]: eta_c1__c2 = 0.54891557

    In [8]: mom1 = mom*eta + o_nrm*eta_c1__c2

    In [10]: np.set_printoptions(precision=9)

    In [11]: mom1
    Out[11]: array([ 0.118154279,  0.         , -0.980390536])


    C4OpBoundaryProcess::DielectricDielectric Rindex1 1.48426314 Rindex2 1.00000100
    C4OpBoundaryProcess::PostStepDoIt.Y.DiDi PIDX 552 mom [0.11403715,0.00000000,-0.99347649]

* HMM: THAT LOOKS TOO BIG OF A DIFFERENCE FOR float/double : TODO : CHECK THE NORMAL 


Add C4 debug dumping the mom, pol
------------------------------------

* split normal debug off into ~/opticks/notes/issues/intersect_leaf_normals_from_Ellipsoid_not_normalized.rst


