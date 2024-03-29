blyth-88-pre-MR-sanity-checks
=================================


1. check gun running (ie not input photons) 
2. check non-opticks build and run 


IPHO 10k
----------

::

    QCF qcf 
    c2sum :    21.4588 c2n :    23.0000 c2per:     0.9330  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  21.46/23:0.933 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                              ' ' 0' '  3693   3751' ' 0.4519' '     0      0']
     [' 1' 'TO BT BT BT BT SD                                              ' ' 1' '  3145   3076' ' 0.7653' '     1      8']
     [' 2' 'TO BT BT BT BT BT SA                                           ' ' 2' '  1251   1211' ' 0.6499' '   957   1119']
     [' 3' 'TO BT BT BT BT BT SR SA                                        ' ' 3' '   385    395' ' 0.1282' '  1109   1208']
     [' 4' 'TO BT BT BT BT BT SR SR SA                                     ' ' 4' '   175    197' ' 1.3011' '  1098   1088']
     [' 5' 'TO BT BT AB                                                    ' ' 5' '    73     92' ' 2.1879' '   105     30']
     [' 6' 'TO BT BT BT BT BT SR SR SR SA                                  ' ' 6' '    66     64' ' 0.0308' '  1581   1540']
     [' 7' 'TO BT BT BT BT BR BT BT BT BT BT SA                            ' ' 7' '    59     54' ' 0.2212' '   112    143']
     [' 8' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                         ' ' 8' '    53     42' ' 1.2737' '  1694   1041']
     [' 9' 'TO BT BT BT BT AB                                              ' ' 9' '    44     36' ' 0.8000' '   120     45']
     ['10' 'TO BT BT BT BT BR BT BT BT BT BT SD                            ' '10' '    42     33' ' 1.0800' '   542    531']
     ['11' 'TO BT BT BT BT BR BT BT BT BT AB                               ' '11' '    38     23' ' 3.6885' '  1385   1490']
     ['12' 'TO BT BT BT BR BT BT BT BT SA                                  ' '12' '    23     34' ' 2.1228' '    62     32']
     ['13' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD                   ' '13' '    24     32' ' 1.1429' '   947    936']
     ['14' 'TO BT BT BT BT BT SR BR SA                                     ' '14' '    30     24' ' 0.6667' '  3358   3358']
     ['15' 'TO BT BT BT BT BT SR SR SR BR SA                               ' '15' '    26     27' ' 0.0189' '  1595   1580']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                   ' '16' '    26     18' ' 1.4545' '   971    963']
     ['17' 'TO BT BT BR BT BT BT SA                                        ' '17' '    23     25' ' 0.0833' '    13      5']
     ['18' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD       ' '18' '    22     16' ' 0.9474' '  1749   1710']
     ['19' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA                   ' '19' '    22     16' ' 0.9474' '  2662   2672']
     ['20' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA             ' '20' '    22     19' ' 0.2195' '  1583   1627']
     ['21' 'TO BT BT BT BT BR BT BT BT BT BT BT BT SA                      ' '21' '     7     21' ' 0.0000' '   794    401']
     ['22' 'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA    ' '22' '    19     15' ' 0.4706' '  1816   2191']
     ['23' 'TO BT BT BT BT BT BR SR SA                                     ' '23' '    18     13' ' 0.8065' '  1009   1012']
     ['24' 'TO BT BR BT BT SA                                              ' '24' '    17      9' ' 0.0000' '    90     17']]



DONE : gun running as test of C+S (rather than T:TORCH running with input photons exercise)
-----------------------------------------------------------------------------------------------

With gun running and comparison of different geometries the gensteps and hence 
numbers of photons will be different so it is not surprising that the level of
agreement degrades compared to input photons, because are at mercy of 
fluctuations impacting the gensteps and photons that are comparing.
Only way to cope with this is to up the statistics by looking 
at many events, so average out the fluctuations. 

Still worth looking at, as bugs often cause very different histories to appear
that would make the chi2 become very large.  

HMM: would like to see this for multiple events, to get idea of fluctuations

::

    QCF qcf 
    a.q 9930 b.q 9826 lim slice(0, 9826, None) 
    c2sum :    69.9798 c2n :    60.0000 c2per:     1.1663  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  69.98/60:1.166 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'SI AB                                     ' ' 0' '  1601   1582' ' 0.1134' '     8      5']
     [' 1' 'SI BT BT BT BT BT BT SD                   ' ' 1' '   529    550' ' 0.4087' '     6     51']
     [' 2' 'SI BT BT BT BT BT BT SA                   ' ' 2' '   462    480' ' 0.3439' '    67     13']
     [' 3' 'SI RE AB                                  ' ' 3' '   471    438' ' 1.1980' '    16      2']
     [' 4' 'SI SC AB                                  ' ' 4' '   312    306' ' 0.0583' '    15     59']
     [' 5' 'SI SC BT BT BT BT BT BT SD                ' ' 5' '   234    227' ' 0.1063' '    43     87']
     [' 6' 'SI SC BT BT BT BT BT BT SA                ' ' 6' '   221    193' ' 1.8937' '     1     50']
     [' 7' 'SI BT BT SA                               ' ' 7' '   176    175' ' 0.0028' '   154     61']
     [' 8' 'SI RE BT BT BT BT BT BT SA                ' ' 8' '   169    123' ' 7.2466' '    90    121']
     [' 9' 'SI RE BT BT BT BT BT BT SD                ' ' 9' '   154    161' ' 0.1556' '    18     12']
     ['10' 'SI RE RE AB                               ' '10' '   134    126' ' 0.2462' '    11    199']
     ['11' 'SI SC SC BT BT BT BT BT BT SD             ' '11' '    78    114' ' 6.7500' '    81    185']
     ['12' 'SI BT BT AB                               ' '12' '   104    111' ' 0.2279' '    19      9']
     ['13' 'SI SC SC AB                               ' '13' '    94    104' ' 0.5051' '     0     77']
     ['14' 'SI RE SC AB                               ' '14' '   100     97' ' 0.0457' '   102     19']
     ['15' 'SI SC SC BT BT BT BT BT BT SA             ' '15' '    50     88' '10.4638' '    58    296']
     ['16' 'SI BT BT BT BT BT BT BT SR SA             ' '16' '    77     85' ' 0.3951' '    12     97']
     ['17' 'SI BT BT BT BT BT BT BT SA                ' '17' '    83     62' ' 3.0414' '    71     29']
     ['18' 'SI RE SC BT BT BT BT BT BT SD             ' '18' '    81     79' ' 0.0250' '   251     41']
     ['19' 'SI RE SC BT BT BT BT BT BT SA             ' '19' '    71     73' ' 0.0278' '    76     79']
     ['20' 'SI RE RE BT BT BT BT BT BT SD             ' '20' '    69     67' ' 0.0294' '    52      3']
     ['21' 'SI BT BT BT SD                            ' '21' '    60     51' ' 0.7297' '   128    172']
     ['22' 'SI BT BT BT SA                            ' '22' '    56     46' ' 0.9804' '   686     37']
     ['23' 'SI BT BT DR BT SA                         ' '23' '    54     52' ' 0.0377' '    42    262']
     ['24' 'SI SC BT BT SA                            ' '24' '    42     53' ' 1.2737' '    88    126']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    []

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    []
    key                            :       a :       b :     a/b :     b/a : (a-b)^2/(a+b) 
    ProcessHits_count              :   11442 :   13519 :   0.846 :   1.182 : 172.827
    ProcessHits_true               :    1759 :    1872 :   0.940 :   1.064 :   3.517
    ProcessHits_false              :    9683 :   11647 :   0.831 :   1.203 : 180.839
    SaveNormHit_count              :    1759 :    1872 :   0.940 :   1.064 :   3.517
    SaveMuonHit_count              :       0 :       0 :   0.000 :   0.000 :   0.000
    UNSET                          :       0 :       0 :   0.000 :   0.000 :   0.000
    NDIS                           :       0 :       0 :   0.000 :   0.000 :   0.000
    NOPT                           :       0 :       0 :   0.000 :   0.000 :   0.000
    NEDEP                          :    9404 :   11366 :   0.827 :   1.209 : 185.337
    NBOUND                         :       0 :      40 :   0.000 :   0.000 :  40.000
    NPROC                          :       0 :       0 :   0.000 :   0.000 :   0.000
    NDETECT                        :       0 :       0 :   0.000 :   0.000 :   0.000
    NDECULL                        :     279 :     241 :   1.158 :   0.864 :   2.777
    YMERGE                         :       0 :       0 :   0.000 :   0.000 :   0.000
    YSAVE                          :    1759 :    1872 :   0.940 :   1.064 :   3.517
    opticksMode                    :       2 :       2 :   1.000 :   1.000 :   0.000






a : escape up the chimney 
----------------------------

::

    In [3]: a.f.photon[:,0,2] > 20000
    Out[3]: array([False, False, False, False, False, ..., False, False, False, False, False])

    In [4]: np.count_nonzero( a.f.photon[:,0,2] > 20000  )
    Out[4]: 1

    In [5]: np.where( a.f.photon[:,0,2] > 20000  ) 
    Out[5]: (array([9561]),)

    In [6]: a.q[9561]
    Out[6]: array([b'SI BT BT BT BT SA                                                                               '], dtype='|S96')

    In [7]: a.f.record[9561,:6,0] 
    Out[7]: 
    array([[  192.4  ,   192.246,  -268.788,     6.285],
           [  129.865,   147.576, 17824.   ,    98.702],
           [  116.296,   137.883, 21750.   ,   118.755],
           [  110.248,   133.563, 23500.   ,   127.694],
           [   98.623,   125.259, 25752.   ,   135.208],
           [   78.77 ,   111.077, 29598.2  ,   148.041]], dtype=float32)

    In [12]: a.n[9561]
    Out[12]: 6

    In [13]: np.c_[a.spec[9561,:6]]
    Out[13]: 
    array([['UNSET'],
           ['LS/LS:pTarget/pLowerChimneyLS'],
           ['LS/LS:pLowerChimneyLS/pUpperChimneyLS'],
           ['LS/Air:pUpperChimneyLS/pExpHall'],
           ['Air/Air:pExpHall/pTopTracker'],
           ['Air/Aluminium:pTopTracker/pPanel_2_f_']], dtype='<U94')




DONE : ProcessHits counts and chi2 comparison across 10 gun evt 
-------------------------------------------------------------------

epsilon:ntds blyth$ c2desc=1 ./ntds.sh cfm::

     000 : c2sum/c2n:c2per(C2CUT)  69.98/60:1.166 (30) 
     001 : c2sum/c2n:c2per(C2CUT)  73.96/65:1.138 (30) 
     002 : c2sum/c2n:c2per(C2CUT)  75.72/60:1.262 (30) 
     003 : c2sum/c2n:c2per(C2CUT)  74.17/60:1.236 (30) 
     004 : c2sum/c2n:c2per(C2CUT)  46.13/60:0.769 (30) 
     005 : c2sum/c2n:c2per(C2CUT)  44.76/64:0.699 (30) 
     006 : c2sum/c2n:c2per(C2CUT)  56.69/62:0.914 (30) 
     007 : c2sum/c2n:c2per(C2CUT)  68.89/64:1.076 (30) 
     008 : c2sum/c2n:c2per(C2CUT)  65.72/64:1.027 (30) 
     009 : c2sum/c2n:c2per(C2CUT)  80.63/61:1.322 (30) 


DONE : find clear way to present counts from 10 evt 
-----------------------------------------------------

Below is comparing the N=0 and N=1 geometries. 

epsilon:ntds blyth$ c2desc=1 ./ntds.sh cfm::

    In [1]: ytab.shape 
    Out[1]: (17, 2, 10)

    array([[[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],        
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[11442., 11179., 10993., 11962., 11236., 11463., 11474., 11346., 11283., 11353.],       ProcessHits_count 
            [13519., 13887., 14099., 13823., 13627., 14003., 13927., 14124., 13776., 14260.]],        
            
           [[ 1759.,  1825.,  1712.,  1823.,  1855.,  1810.,  1765.,  1782.,  1777.,  1802.],       ProcessHits_true 
            [ 1872.,  1793.,  1765.,  1716.,  1760.,  1713.,  1671.,  1833.,  1749.,  1719.]],        
            
           [[ 9683.,  9354.,  9281., 10139.,  9381.,  9653.,  9709.,  9564.,  9506.,  9551.],       ProcessHits_false 
            [11647., 12094., 12334., 12107., 11867., 12290., 12256., 12291., 12027., 12541.]],        
            
           [[ 1759.,  1825.,  1712.,  1823.,  1855.,  1810.,  1765.,  1782.,  1777.,  1802.],       SaveNormHit_count 
            [ 1872.,  1793.,  1765.,  1716.,  1760.,  1713.,  1671.,  1833.,  1749.,  1719.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       SaveMuonHit_count 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       UNSET 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NDIS 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NOPT 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[ 9404.,  9117.,  9003.,  9870.,  9147.,  9394.,  9463.,  9341.,  9242.,  9313.],       NEDEP 
            [11366., 11790., 12050., 11841., 11596., 12020., 11973., 12013., 11762., 12293.]],        
            
           [[    0.,     1.,     0.,     1.,     1.,     1.,     0.,     0.,     0.,     1.],       NBOUND 
            [   40.,    38.,    31.,    27.,    24.,    27.,    30.,    38.,    25.,    29.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NPROC 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NDETECT 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[  279.,   236.,   278.,   268.,   233.,   258.,   246.,   223.,   264.,   237.],       NDECULL 
            [  241.,   266.,   253.,   239.,   247.,   243.,   253.,   240.,   240.,   219.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       YMERGE 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[ 1759.,  1825.,  1712.,  1823.,  1855.,  1810.,  1765.,  1782.,  1777.,  1802.],       YSAVE 
            [ 1872.,  1793.,  1765.,  1716.,  1760.,  1713.,  1671.,  1833.,  1749.,  1719.]],        
            
           [[    2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.],       opticksMode 
            [    2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.]]])        













DONE : not WITH_G4CXOPTICKS check build and run
----------------------------------------------------

Oops. Cannot assert on m_track_label in C4. Bump to 0.1.4


::

    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    python: /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.3/C4OpBoundaryProcess.cc:203: virtual G4VParticleChange* C4OpBoundaryProcess::PostStepDoIt(const G4Track&, const G4Step&): Assertion `m_track_label' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd0eabb45 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) ()
    from /data/blyth/junotop/ExternalLibs/custom4/0.1.3/lib64/libCustom4.so
    #5  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) ()
    from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffdba8556b in G4SteppingManager::InvokePostStepDoItProcs() ()
    from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffdba82d3d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) ()
    from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffd2af245d in G4SvcRunManager::SimulateEvent (this=0x923670, i_event=0)
    at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29



DONE : not WITH_G4CXOPTICKS opticksMode:0 
----------------------------------------------------

Hit differences between N=0,1 are to be expected, as they correspond to different geometries 
from the PMT simplification which causes the randoms to get out of alignment so 
will come up with different gensteps and photons. 


N=0::

    Starting program: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 10 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun


    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1724 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1696 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1740 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1806 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1721 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1748 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1745 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1713 hitCollection_muon 0 hitCollection_opticks -1

N=1::

    Starting program: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 10 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun


    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1


BUT I would have expected to get the same counts with corresponding opticksMode:2 runs. 

These counts are similar to but not the same as WITH_G4CXOPTICKS. 
To try: build WITH_G4CXOPTICKS and then use opticksMode:0:: 

    [[ 1759.,  1825.,  1712.,  1823.,  1855.,  1810.,  1765.,  1782.,  1777.,  1802.],       YSAVE 
     [ 1872.,  1793.,  1765.,  1716.,  1760.,  1713.,  1671.,  1833.,  1749.,  1719.]],        


Compiling WITH_G4CXOPTICKS but then using opticksMode:0 gives the same counts as
when not compling WITH_G4CXOPTICKS and using opticksMode:0 
So that means opticksMode:0 is doing what it should do.

N=0::

    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1724 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1696 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1740 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1806 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1721 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1748 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1745 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1713 hitCollection_muon 0 hitCollection_opticks -1

N=1::

    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1



After adding below U4Recorder envvar control and not setting it opticksMode 2 now giving same hit counts as opticksMode 0::

    #export U4Recorder__UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft=1

::

    N[blyth@localhost mtds2]$ grep eventID mtds2.log
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 0 m_opticksMode 2  hitCollection 1722 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 1 m_opticksMode 2  hitCollection 1654 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 2 m_opticksMode 2  hitCollection 1702 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 3 m_opticksMode 2  hitCollection 1757 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 4 m_opticksMode 2  hitCollection 1791 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 5 m_opticksMode 2  hitCollection 1761 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 6 m_opticksMode 2  hitCollection 1690 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 7 m_opticksMode 2  hitCollection 1769 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 8 m_opticksMode 2  hitCollection 1763 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1137:  eventID 9 m_opticksMode 2  hitCollection 1820 hitCollection_muon 0 hitCollection_opticks 0
    N[blyth@localhost mtds2]$ 


DONE : After rejig and tidy up : still matching
---------------------------------------------------

::

    epsilon:mtds_0v2 blyth$ grep "EndOfEvent eventID" mtds0.tlog
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1 GPU NO

    epsilon:mtds_0v2 blyth$ grep "EndOfEvent eventID" mtds2.tlog
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 2 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 2 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 2 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 2 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 2 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 2 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 2 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 2 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 2 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 2 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    epsilon:mtds_0v2 blyth$ 



DONE : investigate why opticksMode:2 is not matching opticksMode:0 
-----------------------------------------------------------------------

::

    epsilon:issues blyth$ t mtds_0v2
    mtds_0v2 () 
    { 
        local logdir=/tmp/$FUNCNAME;
        mkdir -p $logdir;
        export TDS_LOG_COPYDIR=$logdir;
        export EVTMAX=10;
        mtds0;
        mtds2
    }




* HMM: there was Custom4 version shear, need to redo comparisons with all same versions

* all it takes is a single out of place random consumption for the random streams to get out of line 



DONE : review opticksMode:2 vs opticksMode:0 code difference, and vary that
--------------------------------------------------------------------------------------

The biggest difference is geometry translation. Thats lots of Geant4 code::

    LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 2 WITH_G4CXOPTICKS  proceeding to setup Opticks 
    LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan 
    LSExpDetectorConstruction_Opticks::Setup@25: [ WITH_G4CXOPTICKS opticksMode 2 sd 0x5bd1f40
    stree::add_inst i   0 gas_idx   1 nodes.size   25600
    stree::add_inst i   1 gas_idx   2 nodes.size   12615
    stree::add_inst i   2 gas_idx   3 nodes.size    4997
    stree::add_inst i   3 gas_idx   4 nodes.size    2400
    stree::add_inst i   4 gas_idx   5 nodes.size     590
    stree::add_inst i   5 gas_idx   6 nodes.size     590
    stree::add_inst i   6 gas_idx   7 nodes.size     590
    stree::add_inst i   7 gas_idx   8 nodes.size     590
    stree::add_inst i   8 gas_idx   9 nodes.size     504
    X4Solid::convertPolycone@1724: all_z_descending detected, reversing base_steel
    X4Solid::Polycone_MakeInner@1839:  EXPERIMENTAL num_R_inner > 1 handling base_steel num_R_inner 2
    X4Solid::Polycone_MakeInner@1845:  inner_prims.size 2





DONE : avoided expensive U4Recorder::ClassifyFake
----------------------------------------------------------------------------------------

U4Recorder::ClassifyFake is being run even when not used and is likely source of slowdown. 

Sample pause shows U4Recorder::ClassifyFake is culprit:: 

    (gdb) bt
    #0  0x00007ffff6a77bf5 in __strncmp_sse42 () from /lib64/libc.so.6
    #1  0x00007fffd29a3c13 in sstr::MatchEnd (s=0x61ba8e0 "NNVTMCPPMT_PMT_20inch_mcp_phy", q=0x7fffd29f8128 "body_phys")
        at /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sstr.h:86
    #2  0x00007fffd29a3b5e in sstr::Match_ (s=0x61ba8e0 "NNVTMCPPMT_PMT_20inch_mcp_phy", q=0x7fffd29f8128 "body_phys", mode=2)
        at /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sstr.h:70
    #3  0x00007fffd29a5940 in U4Volume::FindPV_r (pv=0x61ba880, qname=0x7fffd29f8128 "body_phys", mode=2, pvs=..., depth=4)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:63
    #4  0x00007fffd29a59bb in U4Volume::FindPV_r (pv=0x61b9b60, qname=0x7fffd29f8128 "body_phys", mode=2, pvs=..., depth=3)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #5  0x00007fffd29a59bb in U4Volume::FindPV_r (pv=0x61c1e30, qname=0x7fffd29f8128 "body_phys", mode=2, pvs=..., depth=2)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #6  0x00007fffd29a59bb in U4Volume::FindPV_r (pv=0x6322270, qname=0x7fffd29f8128 "body_phys", mode=2, pvs=..., depth=1)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #7  0x00007fffd29a59bb in U4Volume::FindPV_r (pv=0x5a8dca0, qname=0x7fffd29f8128 "body_phys", mode=2, pvs=..., depth=0)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #8  0x00007fffd29a588f in U4Volume::FindPV (start_pv=0x5a8dca0, qname=0x7fffd29f8128 "body_phys", mode=2) at /data/blyth/junotop/opticks/u4/U4Volume.h:56    #9  0x00007fffd29ae035 in U4Recorder::ClassifyFake (this=0xb270d0, step=0xade770, flag=2048, spec=0xae1fe0 "Water/Water:pInnerWater/pLPMT_NNVT_MCPPMT", 
        dump=false) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:1055
    #10 0x00007fffd29b414b in U4Recorder::UserSteppingAction_Optical<C4OpBoundaryProcess> (this=0xb270d0, step=0xade770)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:824
    #11 0x00007fffd29abe10 in U4Recorder::UserSteppingAction (this=0xb270d0, step=0xade770) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:228
    #12 0x00007fffcddfca32 in U4RecorderAnaMgr::UserSteppingAction (this=0x9391b0, step=0xade770)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35



DONE : investigated slowdown source is U4Touchable::HasMoreThanOneDaughterWithName
----------------------------------------------------------------------------------------

Repeated interrupts point to U4Touchable::ReplicaNumber U4Touchable::HasMoreThanOneDaughterWithName::

    gdb) c
    Continuing.
    ^C
    Program received signal SIGINT, Interrupt.
    G4VPhysicalVolume::GetLogicalVolume (this=0x6a30040) at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4VPhysicalVolume.icc:50
    50	}
    (gdb) bt
    #0  G4VPhysicalVolume::GetLogicalVolume (this=0x6a30040)
        at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4VPhysicalVolume.icc:50
    #1  0x00007fffd29b2020 in U4Touchable::HasMoreThanOneDaughterWithName (lv=0x5a8ce30, name=0x5a8d480 "lAcrylic")
        at /data/blyth/junotop/opticks/u4/U4Touchable.h:177
    #2  0x00007fffd29b1f09 in U4Touchable::ReplicaDepth (touch=0x2bc2240) at /data/blyth/junotop/opticks/u4/U4Touchable.h:140
    #3  0x00007fffd29b1d96 in U4Touchable::ReplicaNumber (touch=0x2bc2240) at /data/blyth/junotop/opticks/u4/U4Touchable.h:92
    #4  0x00007fffd29b3921 in U4Recorder::UserSteppingAction_Optical<C4OpBoundaryProcess> (this=0xb27090, step=0xade730)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:753
    #5  0x00007fffd29abd42 in U4Recorder::UserSteppingAction (this=0xb27090, step=0xade730) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:228
    #6  0x00007fffcddfca32 in U4RecorderAnaMgr::UserSteppingAction (this=0x939150, step=0xade730)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:35
    #7  0x00007fffce812009 in MgrOfAnaElem::UserSteppingAction (this=0x7fffcea20b00 <MgrOfAnaElem::instance()::s_mgr>, step=0xade730)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:74
    #8  0x00007fffce120fc7 in LSExpSteppingAction::UserSteppingAction (this=0x596c090, fStep=0xade730)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpSteppingAction.cc:56



    (gdb) bt
    #0  0x00007fffd29a8864 in std::vector<G4VPhysicalVolume*, std::allocator<G4VPhysicalVolume*> >::operator[] (this=0x5a8ce38, __n=10158)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/include/c++/8.3.0/bits/stl_vector.h:948
    #1  0x00007fffd29a39bd in G4LogicalVolume::GetDaughter (this=0x5a8ce30, i=10159)
        at /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4LogicalVolume.icc:98
    #2  0x00007fffd29b2010 in U4Touchable::HasMoreThanOneDaughterWithName (lv=0x5a8ce30, name=0x5a8d480 "lAcrylic")
        at /data/blyth/junotop/opticks/u4/U4Touchable.h:176
    #3  0x00007fffd29b1f09 in U4Touchable::ReplicaDepth (touch=0x2bc2330) at /data/blyth/junotop/opticks/u4/U4Touchable.h:140
    #4  0x00007fffd29b1d96 in U4Touchable::ReplicaNumber (touch=0x2bc2330) at /data/blyth/junotop/opticks/u4/U4Touchable.h:92
    #5  0x00007fffd29b3921 in U4Recorder::UserSteppingAction_Optical<C4OpBoundaryProcess> (this=0xb27090, step=0xade730)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:753
    #6  0x00007fffd29abd42 in U4Recorder::UserSteppingAction (this=0xb27090, step=0xade730) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:228
    #7  0x00007fffcddfca32 in U4RecorderAnaMgr::UserSteppingAction (this=0x939150, step=0xade730)


::

     724 template <typename T>
     725 void U4Recorder::UserSteppingAction_Optical(const G4Step* step)
     726 {
     727     const G4Track* track = step->GetTrack();
     728     G4VPhysicalVolume* pv = track->GetVolume() ;
     ...
     752     const G4VTouchable* touch = track->GetTouchable();
     753     current_photon.iindex = U4Touchable::ReplicaNumber(touch);  
     754     // doing replica number search for every step is rather expensive 
     755     // and pointless for steps inside scintillator



Instead of every step, try just doing for SA SD::

     772     unsigned flag = U4StepPoint::Flag<T>(post) ;
     773     bool is_boundary_flag = OpticksPhoton::IsBoundaryFlag(flag) ;  // SD SA DR SR BR BT 
     774     bool is_surface_flag = OpticksPhoton::IsSurfaceDetectOrAbsorbFlag(flag) ;  // SD SA
     775     if(is_boundary_flag) CollectBoundaryAux<T>(&current_aux) ;
     776 
     777 
     778 #ifdef U4RECORDER_EXPENSIVE_IINDEX
     779     // doing replica number search for every step is very expensive and often pointless
     780     // its the kind of thing to do only for low stats or simple geometry running 
     781     current_photon.iindex = U4Touchable::ReplicaNumber(touch, REPLICA_NAME_SELECT);
     782 #else
     783     current_photon.iindex = is_surface_flag ? U4Touchable::ReplicaNumber(touch, REPLICA_NAME_SELECT) : -2 ;
     784 #endif
     785 





DONE : added U4Recorder__REPLICA_NAME_SELECT to try avoiding slow and pointless searches
-------------------------------------------------------------------------------------------

* how to make that faster or optional ? doing it only for certain flags might be easy way


::

    (gdb) f 2
    #2  0x00007fffd29b2010 in U4Touchable::HasMoreThanOneDaughterWithName (lv=0x5a8ccf0, name=0x5a8d340 "lAcrylic")
        at /data/blyth/junotop/opticks/u4/U4Touchable.h:176
    176	        const G4VPhysicalVolume* kpv = lv->GetDaughter(k) ;
    (gdb) p k
    $1 = 25733
    (gdb) 


    169 inline bool U4Touchable::HasMoreThanOneDaughterWithName( const G4LogicalVolume* lv, const char* name)  // static
    170 {
    171     int num_dau = lv->GetNoDaughters();
    172     if(num_dau <= 1) return false ;
    173     int count = 0; 
    174     for (int k=0; k < num_dau ; ++k)
    175     {
    176         const G4VPhysicalVolume* kpv = lv->GetDaughter(k) ;
    177         const G4LogicalVolume*   klv = kpv->GetLogicalVolume() ;
    178         const char* klv_name = klv->GetName().c_str() ;
    179         if(strcmp(name, klv_name)==0) count += 1 ;
    180         if(count > 1) return true ;
    181     }
    182     return false ;
    183 }



Requiring SD fails to find any replica. So back out of that::

    U4Touchable::ReplicaDepth d 0 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 5490
    U4Touchable::ReplicaDepth d 1 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 5490
    U4Touchable::ReplicaDepth d 0 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 5490
    U4Touchable::ReplicaDepth d 1 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 5490
    U4Touchable::ReplicaDepth d 0 dlv_name PMT_3inch_log found 1
    U4Touchable::ReplicaNumber found 1 repno 315687
    U4Touchable::ReplicaDepth d 1 dlv_name PMT_3inch_log found 1
    U4Touchable::ReplicaNumber found 1 repno 315687
    U4Touchable::ReplicaDepth d 0 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 12224
    U4Touchable::ReplicaDepth d 1 dlv_name NNVTMCPPMTlMaskVirtual found 1
    U4Touchable::ReplicaNumber found 1 repno 12224
    U4Touchable::ReplicaDepth d 0 dlv_name NNVTMCPPMTlMaskVirtual found 1


::

    Target 0: (U4SimulateTest) stopped.
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff5582f080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff555c01ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x000000010626b3d5 libSysRap.dylib`qvals(vals=size=0, key="storch_FillGenstep_pos", fallback="0,0,-90", num_expect=3) at squad.h:457
        frame #5: 0x000000010626ad12 libSysRap.dylib`qvals(v=0x0000000117e1a130, key="storch_FillGenstep_pos", fallback="0,0,-90") at squad.h:510
        frame #6: 0x0000000106268f2a libSysRap.dylib`storch::FillGenstep(gs=0x0000000117e1a120, genstep_id=0, numphoton_per_genstep=10000) at storch.h:135
        frame #7: 0x0000000106268d3b libSysRap.dylib`void SEvent::FillGensteps<storch>(gs=0x0000000117e1a040, numphoton_per_genstep=10000) at SEvent.cc:69
        frame #8: 0x0000000106268c31 libSysRap.dylib`SEvent::MakeGensteps(gentype=6) at SEvent.cc:57
        frame #9: 0x0000000106268bae libSysRap.dylib`SEvent::MakeTorchGensteps() at SEvent.cc:45
        frame #10: 0x00000001062c396d libSysRap.dylib`SEvt::AddTorchGenstep() at SEvt.cc:725
        frame #11: 0x0000000100044765 U4SimulateTest`U4App::GeneratePrimaries(this=0x00000001076c8f00, event=0x0000000117e19c50) at U4App.h:193
        frame #12: 0x0000000100044d4c U4SimulateTest`non-virtual thunk to U4App::GeneratePrimaries(this=0x00000001076c8f00, event=0x0000000117e19c50) at U4App.h:0




DONE : get U4SimulateTest.sh to run from full GDML geom on laptop
--------------------------------------------------------------------

Not very useful for debugging due to very long voxelizing time. 



DONE : get opticksMode:2 to run without geometry translation
---------------------------------------------------------------

The geometry for opticksMode 2 only actually needed for input photon targetting.
So try doing without it. 

jcv LSExpDetectorConstruction_Opticks::

     30     else if( opticksMode == 2 )
     31     {
     32         LOG(info) << " opticksMode 2 : try no-opticks-geom running (NB input photons will not work) " ;
     33         SEvt::CreateOrReuse() ;
     34 
     35         _PMTParamData    _ppd(*ppd) ;
     36         _PMTSimParamData _psd(*psd) ; 
     37 
     38         NPFold* j = new NPFold ; 
     39         j->add_subfold( "PMTParamData",    _ppd.serialize() );
     40         j->add_subfold( "PMTSimParamData", _psd.serialize() );
     41         if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     42 
     43         SSim::AddSubfold("juno", j );
     44     }
     45     else if( opticksMode == 1 || opticksMode == 3 )
     46     { 
     47         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ; 
     48         G4CXOpticks::SetGeometry(world) ; 
     49 
     50         _PMTParamData    _ppd(*ppd) ; 
     51         _PMTSimParamData _psd(*psd) ; 
     52 


Motivation is to see if that brings opticksMode:2 hit counts into line with opticksMode:0 


::

    mtds2


    LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan 
    LSExpDetectorConstruction_Opticks::Setup@25: [ WITH_G4CXOPTICKS opticksMode 2 sd 0x5bd4b90
    LSExpDetectorConstruction_Opticks::Setup@32:  opticksMode 2 : try no-opticks-geom running (NB input photons will not work) 
    SSim::AddSubfold@41:  SSim::INSTANCE not intanciated yet 
    LSExpDetectorConstruction_Opticks::Setup@67: ] WITH_G4CXOPTICKS 


    N[blyth@localhost junosw]$ grep eventID /tmp/u4debug/mtds2/mtds2.log
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 0 m_opticksMode 2   hitCollection 1872 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 1 m_opticksMode 2   hitCollection 1793 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 2 m_opticksMode 2   hitCollection 1765 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 3 m_opticksMode 2   hitCollection 1716 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 4 m_opticksMode 2   hitCollection 1760 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 5 m_opticksMode 2   hitCollection 1713 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 6 m_opticksMode 2   hitCollection 1671 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 7 m_opticksMode 2   hitCollection 1833 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 8 m_opticksMode 2   hitCollection 1749 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 9 m_opticksMode 2   hitCollection 1719 hitCollection_muon 0 hitCollection_opticks 0
    N[blyth@localhost junosw]$ 

Not doing the translation makes no difference. 





DONE : flat debug to look for consumption difference between 0 and 2  
------------------------------------------------------------------------

The random consumption starts the same, as demonstrated with debug runs. 


::

    epsilon:junosw blyth$ g4-cls MixMaxRng 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02
    vi -R source/externals/clhep/include/CLHEP/Random/MixMaxRng.h source/externals/clhep/src/MixMaxRng.cc
    2 files to edit

::

    N[blyth@localhost junosw]$ BP=MixMaxRng::flat mtds2


HUH: not landing on any flat calls. 

::

    (gdb) info b
    Num     Type           Disp Enb Address            What
    1       breakpoint     keep y   <MULTIPLE>         
    1.1                         y     0x00007fffd920d4b0 <CLHEP::MixMaxRng::flat()>
    1.2                         y     0x00007fffd9686030 <CLHEP::MixMaxRng::flat()>
    1.3                         y     0x00007fffda2b0d60 <CLHEP::MixMaxRng::flat()>
    1.4                         y     0x00007fffdb84a080 <CLHEP::MixMaxRng::flat()>
    1.5                         y     0x00007fffdbcc2140 <CLHEP::MixMaxRng::flat()>
    1.6                         y     0x00007fffe441e710 in CLHEP::MixMaxRng::flat() 
                                                       at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Build/clhep-2.4.1.0/2.4.1.0/CLHEP/clhep-build/CLHEP/Random/MixMaxRng.h:67
    2       breakpoint     keep y   0x00007ffff69bd702 <malloc+82>
    3       breakpoint     keep y   <PENDING>          list
    (gdb) 


lldb has no trouble stopping with or without CLHEP::

    BP=CLHEP::MixMaxRng::flat ./U4SimulateTest.sh   


gdb needs the CLHEP::

    BP=CLHEP::MixMaxRng::flat mtds2


    ### Run : 0
    junotoptask.initialize          INFO: initialized

    Breakpoint 1, CLHEP::MixMaxRng::flat (this=0x7e2980)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Build/clhep-2.4.1.0/2.4.1.0/CLHEP/clhep-build/CLHEP/Random/MixMaxRng.h:67
    67	/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Build/clhep-2.4.1.0/2.4.1.0/CLHEP/clhep-build/CLHEP/Random/MixMaxRng.h: No such file or directory.
    (gdb) bt
    #0  CLHEP::MixMaxRng::flat (this=0x7e2980)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Build/clhep-2.4.1.0/2.4.1.0/CLHEP/clhep-build/CLHEP/Random/MixMaxRng.h:67
    #1  0x00007fffd390d250 in CLHEP::RandFlat::shoot (a=-1, b=1)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/include/CLHEP/Random/RandFlat.icc:51
    #2  0x00007fffd390cb52 in GtGunGenTool::getMomentum (this=0x94d170, p=1) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:393
    #3  0x00007fffd390c58f in GtGunGenTool::appendParticle (this=0x94d170, index_=0)
        at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:343
    #4  0x00007fffd390ba05 in GtGunGenTool::mutate (this=0x94d170, event=...) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:230
    #5  0x00007fffd38f9125 in GenTools::execute (this=0x94cc00) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GenTools.cc:120
    #6  0x00007fffed6c984a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffed6ce855 in TaskWatchDog::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffed6c9574 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so


First consumption with opticksMode:2::

    (gdb) list
    391	GtGunGenTool::getMomentum(double p)
    392	{
    393	    double costheta = CLHEP::RandFlat::shoot(-1, 1);
    394	    double phi = 360*CLHEP::RandFlat::shoot()*CLHEP::degree;
    395	    double sintheta = sqrt(1.-costheta*costheta);
    396	    HepMC::ThreeVector tv;
    397	    tv.setX(p*sintheta*cos(phi));
    398	    tv.setY(p*sintheta*sin(phi));
    399	    tv.setZ(p*costheta);
    400	
    (gdb) p costhera
    No symbol "costhera" in current context.
    (gdb) p costheta
    $1 = -0.92726075650479911
    (gdb) p phi
    $2 = 5.2481068618789912
    (gdb) p sintheta
    $3 = 0.37441619816208227
    (gdb) 


BP=CLHEP::MixMaxRng::flat mtds0::

    (gdb) bt
    #0  CLHEP::MixMaxRng::flat (this=0x7c7680)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Build/clhep-2.4.1.0/2.4.1.0/CLHEP/clhep-build/CLHEP/Random/MixMaxRng.h:67
    #1  0x00007fffd390d250 in CLHEP::RandFlat::shoot (a=-1, b=1)
        at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/include/CLHEP/Random/RandFlat.icc:51
    #2  0x00007fffd390cb52 in GtGunGenTool::getMomentum (this=0x94cfc0, p=1) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:393
    #3  0x00007fffd390c58f in GtGunGenTool::appendParticle (this=0x94cfc0, index_=0)
        at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:343
    #4  0x00007fffd390ba05 in GtGunGenTool::mutate (this=0x94cfc0, event=...) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GtGunGenTool.cc:230
    #5  0x00007fffd38f9125 in GenTools::execute (this=0x94cb10) at /data/blyth/junotop/junosw/Simulation/GenTools/src/GenTools.cc:120



    (gdb) list
    391	GtGunGenTool::getMomentum(double p)
    392	{
    393	    double costheta = CLHEP::RandFlat::shoot(-1, 1);
    394	    double phi = 360*CLHEP::RandFlat::shoot()*CLHEP::degree;
    395	    double sintheta = sqrt(1.-costheta*costheta);
    396	    HepMC::ThreeVector tv;
    397	    tv.setX(p*sintheta*cos(phi));
    398	    tv.setY(p*sintheta*sin(phi));
    399	    tv.setZ(p*costheta);
    400	
    (gdb) p costheta
    $1 = -0.92726075650479911
    (gdb) p phi
    $2 = 5.2481068618789912
    (gdb) p sintheta
    $3 = 0.37441619816208227
    (gdb) 





DONE : Debug Random consumption mis-alignement between opticksMode:0 and 2
--------------------------------------------------------------------------------

so the gun generation in opticksMode 0, 2 start the same. 

Tricky to debug as have very little info for opticksMode:0 

But could swap the engine in both cases one with consumption monitoring. 
To see where things get out of alignment. 

Developed S4RandomMonitor.h and S4RandomArray.h 
for low-dependency random monitoring and modified::

    LSExpDetectorConstruction_Opticks::Setup
    


::

     17 void LSExpDetectorConstruction_Opticks::Setup(
     18           int opticksMode,
     19           const G4VPhysicalVolume* world,
     20           const G4VSensitiveDetector* sd,
     21           PMTParamData* ppd,
     22           PMTSimParamData* psd,
     23           NPFold* pmtscan
     24           )
     25 {
     26     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     27     if( opticksMode == 0 || opticksMode == 2 )
     28     {
     29         LOG(info) << " opticksMode 0 or 2 : try no-opticks-geom running (NB input photons will not work) " ;
     30         SEvt* evt = SEvt::CreateOrReuse() ; // SEvt may have been created already by U4RecorderAnaMgr/U4Recorder 
     31         evt->random_array = new S4RandomArray ;  // DEBUGGING RANDOM CONSUMPTION : DONT LEAVE LIKE THIS  
     32           
     33         _PMTParamData    _ppd(*ppd) ;
     34         _PMTSimParamData _psd(*psd) ;
     35           
     36         NPFold* j = new NPFold ;
     37         j->add_subfold( "PMTParamData",    _ppd.serialize() );
     38         j->add_subfold( "PMTSimParamData", _psd.serialize() );
     39         if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     40 
     41         SSim::Create();
     42         SSim::AddSubfold("juno", j );
     43     }
     44     else if( opticksMode == 1 || opticksMode == 3 )
     45     { 
     46         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ; 
     47         G4CXOpticks::SetGeometry(world) ; 
     48 
     49         _PMTParamData    _ppd(*ppd) ; 
     50         _PMTSimParamData _psd(*psd) ; 
     51 
     52         NPFold* j = new NPFold ; 
     53         j->add_subfold( "PMTParamData",    _ppd.serialize() );
     54         j->add_subfold( "PMTSimParamData", _psd.serialize() );
     55         if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     56 
     57         SSim::AddSubfold("juno", j );



jcv junoSD_PMT_v2::

    junoSD_PMT_v2::EndOfEvent

    1145     if( m_opticksMode == 2 )
    1146     {
    1147         NP* jsdpmt = dbg.get_meta_array(m_opticksMode) ;
    1148         SEvt::AddArray("junoSD_PMT_v2.npy", jsdpmt );
    1149         LOG(info) << dbg.desc() ;
    1150         dbg.zero();
    1151     }
    1152 
    1153     if( m_opticksMode == 0 || m_opticksMode == 2 )
    1154     { 
    1155         S4RandomArray* s4ra = SEvt::GetRandomArray() ;
    1156         NP* ra = s4ra ? s4ra->serialize() : nullptr
    1157         if(ra) SEvt::AddArray("S4RandomArray.npy", ra );
    1158         if(s4ra) s4ra->clear();
    1159     }


::

    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd243ff14 in S4RandomArray::flatArray (this=0x7467360, size=16, vect=0x7941160)
        at /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/S4RandomArray.h:96
    #5  0x00007fffda5cc315 in G4UniversalFluctuation::SampleFluctuations(G4MaterialCutsCouple const*, G4DynamicParticle const*, double, double, double) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #6  0x00007fffda63830d in G4VEnergyLossProcess::AlongStepDoIt(G4Track const&, G4Step const&) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #7  0x00007fffdba84d0a in G4SteppingManager::InvokeAlongStepDoItProcs() ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffdba82b7f in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffce5d645d in G4SvcRunManager::SimulateEvent (this=0x924600, i_event=0)



HMM:: where is the SEvt::save invoked ? U4Recorder handles that for opticksMode > 0
----------------------------------------------------------------------------------------

U4Recorder::EndOfEventAction does the SEvt::Save and SEvt::Clear::

    epsilon:junosw blyth$ jgr SEvt.hh 
    ./Simulation/GenTools/src/GtOpticksTool.cc:#include "SEvt.hh"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#include "SEvt.hh"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#include "SEvt.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "SEvt.hh"
    epsilon:junosw blyth$ 


Get the recorder active for opticksMode:0 jcv JUNODetSimModule::

    1999         if args.opticks_mode > 0 and args.opticks_anamgr:
    2000             print("appending U4RecorderAnaMgr to AnaMgrList")
    2001             detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2002             g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2003             g4ok_anamgr.setLogLevel(4)
    2004         pass

    1999         if args.opticks_mode > -1 and args.opticks_anamgr:
    2000             print("appending U4RecorderAnaMgr to AnaMgrList")
    2001             detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2002             g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2003             g4ok_anamgr.setLogLevel(4)
    2004         pass


That runs into issues::

    gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf2534b3 in SEvt::beginPhoton (this=0xb50b30, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1277
    #5  0x00007fffd29ac4e6 in U4Recorder::PreUserTrackingAction_Optical (this=0xb27c80, track=0x9c3bbda0) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:287
    #6  0x00007fffd29abd4a in U4Recorder::PreUserTrackingAction (this=0xb27c80, track=0x9c3bbda0) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:217
    #7  0x00007fffcddfa9d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0xb509a0, trk=0x9c3bbda0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    #8  0x00007fffce810d39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffcea1fb00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x9c3bbda0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #9  0x00007fffce1200db in LSExpTrackingAction::PreUserTrackingAction (this=0x5964c30, aTrack=0x9c3bbda0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37


So add SEvt::SaveExtra to use some SEvt machinery without the full thing. 


Need to sort out the index and the reldir for opticksMode:0::

    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/mtds0/ALL/
    total 3932
    3932 -rw-rw-r--. 1 blyth blyth 4026104 Apr 12 02:45 S4RandomArray.npy
       0 drwxr-xr-x. 2 blyth blyth      31 Apr 12 02:45 .
       0 drwxr-xr-x. 3 blyth blyth      17 Apr 12 02:45 ..
    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/mtds2/
    total 0


    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/mtds2/ALL1/000/
    total 5980
       4 -rw-rw-r--.  1 blyth blyth    2208 Apr 12 01:04 gs.npy
     156 -rw-rw-r--.  1 blyth blyth  157344 Apr 12 01:04 pho.npy
       4 -rw-rw-r--.  1 blyth blyth      30 Apr 12 01:04 sframe_meta.txt
       4 -rw-rw-r--.  1 blyth blyth     384 Apr 12 01:04 sframe.npy
     160 -rw-rw-r--.  1 blyth blyth  160128 Apr 12 01:04 pho0.npy
      16 -rw-rw-r--.  1 blyth blyth   12608 Apr 12 01:04 genstep.npy
       4 -rw-rw-r--.  1 blyth blyth     523 Apr 12 01:04 photon_meta.txt
     616 -rw-rw-r--.  1 blyth blyth  628992 Apr 12 01:04 photon.npy
       4 -rw-rw-r--.  1 blyth blyth     114 Apr 12 01:04 U4R_meta.txt
       8 -rw-rw-r--.  1 blyth blyth    5606 Apr 12 01:04 U4R_names.txt
       4 -rw-rw-r--.  1 blyth blyth     132 Apr 12 01:04 U4R.npy
       4 drwxr-xr-x.  2 blyth blyth    4096 Apr 12 01:04 .
       4 -rw-rw-r--.  1 blyth blyth     221 Apr 12 01:04 junoSD_PMT_v2_meta.txt
       4 -rw-rw-r--.  1 blyth blyth     104 Apr 12 01:04 junoSD_PMT_v2_names.txt
       4 -rw-rw-r--.  1 blyth blyth     132 Apr 12 01:04 junoSD_PMT_v2.npy
       4 -rw-rw-r--.  1 blyth blyth      67 Apr 12 01:04 NPFold_index.txt
    4980 -rw-rw-r--.  1 blyth blyth 5098976 Apr 12 01:04 S4RandomArray.npy
       0 drwxr-xr-x. 12 blyth blyth     116 Apr 11 20:24 ..
    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/mtds2/ALL1/009/
    total 6108
       4 -rw-rw-r--.  1 blyth blyth    1920 Apr 12 01:04 gs.npy
     156 -rw-rw-r--.  1 blyth blyth  158336 Apr 12 01:04 pho.npy
       4 -rw-rw-r--.  1 blyth blyth      30 Apr 12 01:04 sframe_meta.txt
       4 -rw-rw-r--.  1 blyth blyth     384 Apr 12 01:04 sframe.npy



::

    epsilon:junosw blyth$ opticks-f SetReldir
    ./CSG/CSGSimtraceRerunTest.sh:FOLD=$BASE/ALL            # corresponds SEvt::save() with SEvt::SetReldir("ALL")
    ./CSG/CSGSimtraceSampleTest.sh:FOLD=$BASE/ALL            # corresponds SEvt::save() with SEvt::SetReldir("ALL")
    ./sysrap/SEvt.hh:    static void SetReldir(const char* reldir); 
    ./sysrap/SEvt.cc:// SetReldir can be used with the default SEvt::save() changing the last directory element before the index if present
    ./sysrap/SEvt.cc:void        SEvt::SetReldir(const char* reldir){ assert(INSTANCE) ; INSTANCE->setReldir(reldir) ; }
    ./u4/u4s.sh:reldir=$physdesc/$sel     # SEvt::SetReldir 
    ./g4cx/gxs.sh:FOLD=$BASE/ALL            # corresponds SEvt::save() with SEvt::SetReldir("ALL")
    ./g4cx/gxt.sh:FOLD=$BASE/${MOI:-ALL}    # corresponds SEvt::save() with SEvt::SetReldir("ALL")
    epsilon:opticks blyth$ 


Thats because the U4Recorder uses SEvt::HighLevelCreate::


     662 SEvt* SEvt::HighLevelCreate() // static
     663 {
     664     SEvt* evt = nullptr ;
     665 
     666     int g4state_rerun_id = SEventConfig::G4StateRerun();
     667     bool rerun = g4state_rerun_id > -1 ;
     668 
     669     const char* alldir = ssys::replace_envvar_token("ALL${VERSION}") ;
     670     const char* alldir0 = "ALL0" ;
     671     const char* seldir = ssys::replace_envvar_token("SEL${VERSION}") ;
     672 
     673     LOG(info)
     674         << " g4state_rerun_id " << g4state_rerun_id
     675         << " alldir " << alldir
     676         << " alldir0 " << alldir0
     677         << " seldir " << seldir
     678         << " rerun " << rerun
     679         ;
     680 
     681     // this runs early, at U4Recorder instanciation, which is before logging is setup it seems 
     682     std::cout
     683         << "SEvt::HighLevelCreate"
     684         << " g4state_rerun_id " << g4state_rerun_id
     685         << " alldir " << alldir
     686         << " alldir0 " << alldir0
     687         << " seldir " << seldir
     688         << " rerun " << rerun
     689         << std::endl
     690         ;
     691 
     692 
     693     if(rerun == false)
     694     {  
     695         evt = SEvt::Create();   
     696         evt->setReldir(alldir);





Comparing the randoms::


    EVT=000 ./mtds.sh ana


    In [2]: a.S4RandomArray.reshape(-1)
    Out[2]: array([0.036, 0.835, 0.829, 0.817, 0.514, ..., 0.271, 0.992, 0.423, 0.579, 0.138])

    In [3]: b.S4RandomArray.reshape(-1)
    Out[3]: array([0.036, 0.835, 0.829, 0.817, 0.514, ..., 0.335, 0.283, 0.058, 0.89 , 0.65 ])


    In [6]: aa[:10]
    Out[6]: array([0.036, 0.835, 0.829, 0.817, 0.514, 0.257, 0.732, 0.416, 0.698, 0.567])

    In [7]: bb[:10]
    Out[7]: array([0.036, 0.835, 0.829, 0.817, 0.514, 0.257, 0.732, 0.416, 0.698, 0.567])


    In [1]: aa.shape
    Out[1]: (502313,)

    In [2]: bb.shape
    Out[2]: (637356,)

    In [3]: bb[:len(aa)]
    Out[3]: array([0.036, 0.835, 0.829, 0.817, 0.514, ..., 0.271, 0.992, 0.423, 0.579, 0.138])

    In [4]: rbb = bb[:len(aa)]

    In [5]: np.all( rbb == aa )
    Out[5]: True


    In [8]: ebb = bb[len(aa):]

    In [9]: ebb[:10]
    Out[9]: array([0.126, 0.654, 0.842, 0.993, 0.806, 0.171, 0.134, 0.357, 0.342, 0.239])






    EVT=001 ./mtds.sh ana

    In [1]: aa[:10]
    Out[1]: array([0.126, 0.654, 0.842, 0.993, 0.806, 0.171, 0.134, 0.357, 0.342, 0.239])

    In [2]: bb[:10]
    Out[2]: array([0.567, 0.695, 0.09 , 0.321, 0.537, 0.104, 0.565, 0.939, 0.234, 0.668])


::

    epsilon:mtds blyth$ du -h /tmp/blyth/opticks/GEOM/mtds2/ALL1/00?/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/000/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/001/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/002/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/003/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/004/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/005/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/006/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/007/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/008/S4RandomArray.npy
    5.2M	/tmp/blyth/opticks/GEOM/mtds2/ALL1/009/S4RandomArray.npy
    epsilon:mtds blyth$ 
    epsilon:mtds blyth$ 
    epsilon:mtds blyth$ du -h /tmp/blyth/opticks/GEOM/mtds0/ALL1/00?/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/000/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/001/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/002/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/003/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/004/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/005/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/006/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/007/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/008/S4RandomArray.npy
    4.2M	/tmp/blyth/opticks/GEOM/mtds0/ALL1/009/S4RandomArray.npy
    epsilon:mtds blyth$ 


opticksMode:2 consuming 20-30% more randoms than opticksMode:0::
 
    ./mtds.sh : anascript :
    [[502313. 637356.]
     [490172. 649516.]
     [496152. 646331.]
     [495653. 640649.]
     [517912. 627135.]
     [511181. 640816.]
     [495720. 634956.]
     [498853. 635522.]
     [508416. 634975.]
     [503247. 653205.]]

    In [3]: ab[:,1]/ab[:,0]
    Out[3]: array([1.269, 1.325, 1.303, 1.293, 1.211, 1.254, 1.281, 1.274, 1.249, 1.298])


All the randoms in common are the same::

    In [3]: A.shape[0]
    Out[3]: 5019619

    In [4]: B.shape[0]
    Out[4]: 6400461

    In [5]: B[:len(A)]
    Out[5]: array([0.036, 0.835, 0.829, 0.817, 0.514, ..., 0.797, 0.396, 0.883, 0.95 , 0.997])

    In [6]: BB = B[:len(A)]

    In [7]: np.all( BB == A )
    Out[7]: True


FIXED : optickMode 0,2 Consumption difference
-------------------------------------------------

After preventing U4Recorder from clearing interaction lengths get same consumption::

     895     if(UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft)
     896     {
     897         U4Process::ClearNumberOfInteractionLengthLeft(*track, *step);
     898     }
     899 
     900     LOG(LEVEL) << "]" ;
     901 }


::

    epsilon:mtds blyth$ ./mtds.sh cfm 
             BASH_SOURCE : ./mtds.sh 
                     arg : cfm 
                  defarg : ana 
                     DIR : . 
            OPTICKS_MODE : 2 
                     EVT : %0.3d 
                   AGEOM : mtds0 
                   ABASE : /tmp/blyth/opticks/GEOM/mtds0 
                   AFOLD : /tmp/blyth/opticks/GEOM/mtds0/ALL1/%0.3d 
                   BGEOM : mtds2 
                   BBASE : /tmp/blyth/opticks/GEOM/mtds2 
                   BFOLD : /tmp/blyth/opticks/GEOM/mtds2/ALL1/%0.3d 
                       N :  
                 VERSION :  
                   UBASE :  
    ./mtds.sh : anascript :
    [[502313. 502313.]
     [490172. 490172.]
     [496152. 496152.]
     [495653. 495653.]
     [517912. 517912.]
     [511181. 511181.]
     [495720. 495720.]
     [498853. 498853.]
     [508416. 508416.]
     [503247. 503247.]]
    A:(5019619,) 
    B:(5019619,) 

    In [1]: np.all( A == B )                                                                                                        
    Out[1]: True






DONE : find where opticksMode:0 and opticksMode:2 put the randoms to different use
--------------------------------------------------------------------------------------

Hmm S4RandomArray can return consumption indices that can associate with junctures in the code. 

::

    108     /**
    109     export U4Recorder__UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft=1 
    110 
    111     This setting is not appropriate for gun running. It is only appropriate with 
    112     input photon running when doing optical only random aligned comparisons.
    113 
    114     This setting makes it easier to random align Opticks and Geant4 based optical simulations
    115     because it makes the Geant4 pattern of random consumption more regular. 
    116     However this has side effects:
    117 
    118     1. increases the randoms consumed by 20-30% (can check this with S4RandomArray.h) 
    119     2. changes the events simulated, as the randoms consumed are changed   
    120 
    121     **/
    122     static constexpr const char* UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft_ = "U4Recorder__UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft" ;
    123     static const bool UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft ;
    124 


    0895     if(UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft)
     896     {
     897         U4Process::ClearNumberOfInteractionLengthLeft(*track, *step);
     898     }
     899 
     900     LOG(LEVEL) << "]" ;
     901 }
     902 
     903 
     904 const bool U4Recorder::UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft = ssys::getenvbool(UserSteppingAction_Optical_ClearNumberOfInteractionLengthLeft_) ;
     905 
     906 




DONE : tidy up the extra debugging added, eg S4RandomArray collection
----------------------------------------------------------------------

::

    epsilon:opticks blyth$ jgr S4RandomArray 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#include "S4RandomArray.h"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        S4RandomArray* s4ra = SEvt::GetRandomArray() ; 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:             SEvt::SaveExtra(S4RandomArray::NAME, ra) ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "S4RandomArray.h"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        evt->random_array = new S4RandomArray ;      // DEBUGGING RANDOM CONSUMPTION : DONT LEAVE LIKE THIS  
    epsilon:junosw blyth$ 


DONE : tidy up debug in junoSD_PMT_v2 relocating most to junoSD_PMT_v2_Opticks
--------------------------------------------------------------------------------------




DONE : tidy up debug instrumentation, by disabling WITH_G4CXOPTICKS_DEBUG
-----------------------------------------------------------------------------

Also tidy up these, should not be there in opticksMode:0::

    U4Debug::Save eventID 0 dir /tmp/000 EKEY U4Debug_SaveDir
    U4Cerenkov_Debug::Save dir /tmp/000 num_record 6
    U4Scintillation_Debug::Save dir /tmp/000 num_record 54
    U4Hit_Debug::Save dir /tmp/000 num_record 0
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks -1
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0


::

    epsilon:ntds blyth$ jgr U4Debug
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#include "U4Debug.hh"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    U4Debug::Save(eventID);   
    epsilon:junosw blyth$ 

    epsilon:tmp blyth$ jgr U4Cerenkov_Debug
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#include "U4Cerenkov_Debug.hh"
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:  U4Cerenkov_Debug dbg ;  
    epsilon:junosw blyth$ 

    epsilon:junosw blyth$ jgr U4Scintillation_Debug
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#include "U4Scintillation_Debug.hh"
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:    U4Scintillation_Debug dbg ; 
    ./Doc/oum/source/releasenotes/J22.2.0.md:    * collect more debug fields into U4Scintillation_Debug hidden behind WITH_G4CXOPTICKS_DEBUG, plus avoid compilation warnings (see MR !24 and !27)
    epsilon:junosw blyth$ 


::

    1116 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
    1117 {
    1118     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
    1119     G4int eventID = event->GetEventID() ;
    1120 
    1121 #ifdef WITH_G4CXOPTICKS_DEBUG
    1122     /**
    1123     Switch this off this block by changing ~/opticks/cmake/Modules/FindOpticks.cmake 
    1124     Done here rather than within _Opticks in order to check for differences between opticksMode.
    1125     Needs to be prior to m_jpmt_opticks->EndOfEvent(HCE) for saving genstep labels
    1126     **/
    1127     U4Debug::Save(eventID);
    1128 #endif
    1129 



     342 #ifdef WITH_G4CXOPTICKS
     343   bool is_opticks_genstep = fNumPhotons > 0 ;
     344   G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
     345   assert( a_ui == nullptr );  // should always be null, as process C is not applicable to RE-photons
     346 
     347   if(is_opticks_genstep && (m_opticksMode & 1 ))
     348   {
     349       U4::CollectGenstep_G4Cerenkov_modified(
     350           &aTrack,
     351           &aStep,
     352           fNumPhotons,




DONE : reviewed WITH_G4CXOPTICKS_DEBUG and disabled it 
---------------------------------------------------------

::

    epsilon:j blyth$ jgr WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Doc/oum/source/releasenotes/J22.2.0.md:    * collect more debug fields into U4Scintillation_Debug hidden behind WITH_G4CXOPTICKS_DEBUG, plus avoid compilation warnings (see MR !24 and !27)
    epsilon:junosw blyth$ 




FIXED : cleanup junoSD_PMT_v2
-------------------------------

Instanciation order mixup::

    (gdb) f 3
    #3  0x00007fffd243ae6a in junoSD_PMT_v2_Opticks::EndOfEvent_Debug (this=0x5bc97a0, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:179
    179	        NP* jsdpmt = m_jpmt_dbg->get_meta_array(m_opticksMode, eventID ) ; 
    (gdb) p m_jpmt_dbg
    $1 = (junoSD_PMT_v2_Debug *) 0x409c3133bbdae631
    (gdb) p m_jpmt
    $2 = (junoSD_PMT_v2 *) 0x5bc8f90
    (gdb) f 2
    #2  0x00007fffd243dc83 in junoSD_PMT_v2_Debug::get_meta_array (this=0x409c3133bbdae631, opticksMode=0, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h:202
    202	    get_kvs(kvs); 
    (gdb) f 1
    #1  0x00007fffd243d647 in junoSD_PMT_v2_Debug::get_kvs (this=0x409c3133bbdae631, kvs=...)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h:177
    177	    kvs.push_back(KV("ProcessHits_count", ProcessHits_count)); 
    (gdb) 




DONE : Confirm the above matching and tidy ups with some mtds runs
-----------------------------------------------------------------------------------------

The below shows that adding the instrumentation does not change the events 
anymore, ie opticksMode:0 and opticksMode:2 are doing the same thing. 
BUT,  with opticksMode:2 have lots of info on every step point of every photon. 

::

    N[blyth@localhost junosw]$ t mtds_0v2
    mtds_0v2 () 
    { 
        local logdir=/tmp/$FUNCNAME;
        mkdir -p $logdir;
        export TDS_LOG_COPYDIR=$logdir;
        export EVTMAX=10;
        mtds0;
        mtds2;
        : initial thought was to keep the logs together with event;
        : BUT is rather convenient to keep them separate as grabbing log usually much faster than the full event
    }
    N[blyth@localhost junosw]$ 


    epsilon:mtds_0v2 blyth$ grep "junoSD_PMT_v2::EndOfEvent eventID" mtds0.tlog
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks -1 GPU NO
    epsilon:mtds_0v2 blyth$ 
    epsilon:mtds_0v2 blyth$ 
    epsilon:mtds_0v2 blyth$ grep "junoSD_PMT_v2::EndOfEvent eventID" mtds2.tlog
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 2 hitCollection 1722 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 2 hitCollection 1654 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 2 hitCollection 1702 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 2 hitCollection 1757 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 2 hitCollection 1791 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 2 hitCollection 1761 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 2 hitCollection 1690 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 2 hitCollection 1769 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 2 hitCollection 1763 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 2 hitCollection 1820 hitCollection_muon 0 hitCollection_opticks 0 GPU NO
    epsilon:mtds_0v2 blyth$ 


DONE : ntds2 gun running, chi2 check : revealed need to speedup fake skipping
---------------------------------------------------------------------------------

::

    N[blyth@localhost ntds2]$ t ntds2_cf
    ntds2_cf () 
    { 
        : ntds2 is Geant4 running with Opticks U4Recorder instrumentation;
        : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories;
        : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds;
        export EVTMAX=10;
        N=0 GEOM=V0J008 ntds2;
        [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1;
        N=1 GEOM=V1J008 ntds2;
        [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2;
        return 0
    }


* HMM: N=0 requires the slow Fake skipping 


DONE : speed up U4Recorder::ClassifyFake while keeping it workin
--------------------------------------------------------------------

* added maxdepth restriction on U4Volume::FindPV
* added start PV name must contain PMT before doing the expensive search 
* adder timing to U4Recorder::ClassifyFake

::

    (gdb) bt
    #0  0x00007fffd29a5a84 in U4Volume::FindPV_r (pv=0x6188bd0, qname=0x7fffd29f8100 "body_phys", mode=2, pvs=..., depth=3)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:63
    #1  0x00007fffd29a5aed in U4Volume::FindPV_r (pv=0x6198480, qname=0x7fffd29f8100 "body_phys", mode=2, pvs=..., depth=2)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #2  0x00007fffd29a5aed in U4Volume::FindPV_r (pv=0x6322920, qname=0x7fffd29f8100 "body_phys", mode=2, pvs=..., depth=1)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #3  0x00007fffd29a5aed in U4Volume::FindPV_r (pv=0x5a64ef0, qname=0x7fffd29f8100 "body_phys", mode=2, pvs=..., depth=0)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:65
    #4  0x00007fffd29a59c1 in U4Volume::FindPV (start_pv=0x5a64ef0, qname=0x7fffd29f8100 "body_phys", mode=2)
        at /data/blyth/junotop/opticks/u4/U4Volume.h:56
    #5  0x00007fffd29ae1b1 in U4Recorder::ClassifyFake (this=0xb29870, step=0xae0fa0, flag=256, 
        spec=0x244e7b470 "Water/Tyvek:pInnerWater/pCentralDetector", dump=false) at /data/blyth/junotop/optic


Attempt to speedup fake skipping has stopped it working::

    jxn
    ./ntds.sh grab_evt
    ./ntds.sh cf

    QCF qcf : a, b not same shape _aq (9791, 1) _bq (9980, 1) WILL LIMIT TO mn 9791  
    a.q 9791 b.q 9980 lim slice(0, 9791, None) 
    c2sum :  4298.1445 c2n :    69.0000 c2per:    62.2919  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  4298.14/69:62.292 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'SI AB                          ' ' 0' '  1558   1582' ' 0.1834' '     3     11']
     [' 1' 'SI BT BT BT BT BT BT BT SD     ' ' 1' '   548     33' '456.4974' '     0     92']
     [' 2' 'SI BT BT BT BT BT BT BT SA     ' ' 2' '   511     73' '328.5000' '    20    242']
     [' 3' 'SI BT BT BT BT BT BT SA        ' ' 3' '     0    473' '473.0000' '    -1      0']
     [' 4' 'SI BT BT BT BT BT BT SD        ' ' 4' '     0    464' '464.0000' '    -1     15']
     [' 5' 'SI RE AB                       ' ' 5' '   449    460' ' 0.1331' '     2     34']
     [' 6' 'SI SC AB                       ' ' 6' '   303    332' ' 1.3244' '     9     13']
     [' 7' 'SI SC BT BT BT BT BT BT BT SD  ' ' 7' '   232     17' '185.6426' '     4   1173']
     [' 8' 'SI SC BT BT BT BT BT BT SA     ' ' 8' '     6    230' '212.6102' '  3190     28']
     [' 9' 'SI SC BT BT BT BT BT BT BT SA  ' ' 9' '   218     35' '132.3676' '    27    309']
     ['10' 'SI SC BT BT BT BT BT BT SD     ' '10' '     1    189' '186.0211' '  4229      4']
     ['11' 'SI RE BT BT BT BT BT BT BT SD  ' '11' '   171      7' '151.1011' '    74   1480']



DONE : ntds_cfm : chi2 ok, timings need debug
--------------------------------------------------

::

    array([[[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],        
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[11274., 11012., 10851., 11422., 11372., 11151., 11535., 11250., 11123., 11001.],       ProcessHits_count 
            [13990., 13709., 13649., 13709., 14365., 14609., 13600., 13869., 14686., 14014.]],        
            
           [[ 1820.,  1724.,  1696.,  1740.,  1806.,  1721.,  1748.,  1745.,  1763.,  1713.],       ProcessHits_true 
            [ 1722.,  1654.,  1702.,  1757.,  1791.,  1761.,  1690.,  1769.,  1763.,  1820.]],        
            
           [[ 9454.,  9288.,  9155.,  9682.,  9566.,  9430.,  9787.,  9505.,  9360.,  9288.],       ProcessHits_false 
            [12268., 12055., 11947., 11952., 12574., 12848., 11910., 12100., 12923., 12194.]],        
            
           [[ 1820.,  1724.,  1696.,  1740.,  1806.,  1721.,  1748.,  1745.,  1763.,  1713.],       SaveNormHit_count 
            [ 1722.,  1654.,  1702.,  1757.,  1791.,  1761.,  1690.,  1769.,  1763.,  1820.]],        

           ...
           
           [[ 9214.,  9051.,  8905.,  9427.,  9326.,  9206.,  9531.,  9242.,  9131.,  9055.],       NEDEP 
            [11990., 11762., 11674., 11658., 12290., 12558., 11621., 11829., 12641., 11923.]],        
            
           [[    2.,     1.,     1.,     0.,     1.,     2.,     3.,     1.,     1.,     0.],       NBOUND 
            [   21.,    31.,    29.,    28.,    33.,    36.,    26.,    34.,    32.,    32.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NPROC 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       NDETECT 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[  238.,   236.,   249.,   255.,   239.,   222.,   253.,   262.,   228.,   233.],       NDECULL 
            [  257.,   262.,   244.,   266.,   251.,   254.,   263.,   237.,   250.,   239.]],        
            
           [[    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.],       YMERGE 
            [    0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.,     0.]],        
            
           [[ 1820.,  1724.,  1696.,  1740.,  1806.,  1721.,  1748.,  1745.,  1763.,  1713.],       YSAVE 
            [ 1722.,  1654.,  1702.,  1757.,  1791.,  1761.,  1690.,  1769.,  1763.,  1820.]],        
            
           [[    2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.],       opticksMode 
            [    2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.,     2.]],        
            
           [[    0.,     1.,     2.,     3.,     4.,     5.,     6.,     7.,     8.,     9.],       eventID 
            [    0.,     1.,     2.,     3.,     4.,     5.,     6.,     7.,     8.,     9.]],        
            
           [[   -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.],       SEvt__TimerDuration 
            [   -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.,    -1.]]])        

    c2tab
    array([[67.968, 54.336, 57.879, 50.578, 68.72 , 64.923, 60.431, 79.85 , 68.574, 60.395],
           [63.   , 62.   , 63.   , 69.   , 60.   , 63.   , 62.   , 66.   , 64.   , 64.   ],
           [ 1.079,  0.876,  0.919,  0.733,  1.145,  1.031,  0.975,  1.21 ,  1.071,  0.944]])

    c2per_tot:  0.9963  


DONE : event timers which work and persist in all opticksMode
--------------------------------------------------------------

* added SEvt::TIMER for this
* invoke and persist the duration in::

    junoSD_PMT_v2_Opticks::Initialize
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug

OOPS epoch counts not travelling, fixed stimer.h with system_clock and microseconds standardization


DONE : Getting VERSION into Metadata 
---------------------------------------

Its too opticks specific to grab the version envvar, better to grab the result of that.
But how to detect that from within the monolith ?::

    738    case $VERSION in  ## passed into UsePMTNaturalGeometry
    739       0) opts="$opts --pmt-unnatural-geometry" ;;
    740       1) opts="$opts --pmt-natural-geometry"   ;;
    741    esac

But this is just metadata, so simply grab the VERSION envvar : because there
is no simple place to grab the UsePMTNaturalGeometry from inside monolith. 

::

    epsilon:junosw blyth$ jgl UsePMTNaturalGeometry
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
    ./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw blyth$ 


DONE : without opticks build and run check using mtds0
---------------------------------------------------------

::

    epsilon:junosw blyth$ jgr junoSD_PMT_v2_Debug.h
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#include "PMTSim/junoSD_PMT_v2_Debug.h"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#include "PMTSim/junoSD_PMT_v2_Debug.h"
    epsilon:junosw blyth$ 

    EVTMAX=10 mtds0 

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1722 
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1654 
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1702 
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1757 
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1791 
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1761 
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1690 
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1769 
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1820 



DONE : put back opticksMode:2 geometry translation
----------------------------------------------------------

This is needed for input photon frame targetting


DONE : ntds2_cf gun running results looking good 
---------------------------------------------------

::

    jxn
    ./ntds.sh cfmeta 

    c_itab
    array([[[11274, 11012, 10851, 11422, 11372, 11151, 11535, 11250, 11123, 11001],       ProcessHits_count 
            [13990, 13709, 13649, 13709, 14365, 14609, 13600, 13869, 14686, 14014]],        
            
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       ProcessHits_true 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[ 9454,  9288,  9155,  9682,  9566,  9430,  9787,  9505,  9360,  9288],       ProcessHits_false 
            [12268, 12055, 11947, 11952, 12574, 12848, 11910, 12100, 12923, 12194]],        
            
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       SaveNormHit_count 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           ...
           
           [[ 9214,  9051,  8905,  9427,  9326,  9206,  9531,  9242,  9131,  9055],       NEDEP 
            [11990, 11762, 11674, 11658, 12290, 12558, 11621, 11829, 12641, 11923]],        
            
           [[    2,     1,     1,     0,     1,     2,     3,     1,     1,     0],       NBOUND 
            [   21,    31,    29,    28,    33,    36,    26,    34,    32,    32]],        
           
           ... 
           
           [[  238,   236,   249,   255,   239,   222,   253,   262,   228,   233],       NDECULL 
            [  257,   262,   244,   266,   251,   254,   263,   237,   250,   239]],        
            
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       YSAVE 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[    2,     2,     2,     2,     2,     2,     2,     2,     2,     2],       opticksMode 
            [    2,     2,     2,     2,     2,     2,     2,     2,     2,     2]],        
            
           [[    0,     1,     2,     3,     4,     5,     6,     7,     8,     9],       eventID 
            [    0,     1,     2,     3,     4,     5,     6,     7,     8,     9]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       VERSION 
            [    1,     1,     1,     1,     1,     1,     1,     1,     1,     1]]], dtype=uint64)        

    c_ftab
    array([[[2.517, 2.35 , 2.895, 2.816, 2.952, 2.344, 2.46 , 2.468, 2.845, 2.322],       SEvt__TimerDone 
            [2.654, 2.395, 2.562, 2.537, 2.427, 2.534, 2.5  , 2.531, 2.449, 2.605]]])        

    np.diff(c_ttab)/1e6   # seconds between event starts 

    [[[2.76  2.586 3.106 3.033 3.231 2.62  2.772 2.69  3.112]
      [3.026 2.71  2.858 2.842 3.094 2.874 2.836 2.841 2.708]]]

    np.c_[c_ttab[0,0].view('datetime64[us]'),c_ttab[0,1].view('datetime64[us]')] # event start times (UTC)  

    [['2023-04-14T13:16:14.802047' '2023-04-14T13:24:48.696600']
     ['2023-04-14T13:16:17.561901' '2023-04-14T13:24:51.722786']
     ['2023-04-14T13:16:20.147964' '2023-04-14T13:24:54.432912']
     ['2023-04-14T13:16:23.254430' '2023-04-14T13:24:57.290957']
     ['2023-04-14T13:16:26.286959' '2023-04-14T13:25:00.132612']
     ['2023-04-14T13:16:29.517541' '2023-04-14T13:25:03.226325']
     ['2023-04-14T13:16:32.137683' '2023-04-14T13:25:06.100191']
     ['2023-04-14T13:16:34.909899' '2023-04-14T13:25:08.935885']
     ['2023-04-14T13:16:37.599566' '2023-04-14T13:25:11.776996']
     ['2023-04-14T13:16:40.711695' '2023-04-14T13:25:14.485233']]

    c2tab  # c2sum, c2n, c2per for each event 

    array([[67.968, 54.336, 57.879, 50.578, 68.72 , 64.923, 60.431, 79.85 , 68.574, 60.395],
           [63.   , 62.   , 63.   , 69.   , 60.   , 63.   , 62.   , 66.   , 64.   , 64.   ],
           [ 1.079,  0.876,  0.919,  0.733,  1.145,  1.031,  0.975,  1.21 ,  1.071,  0.944]])

    c2per_tot:  0.9963  



DONE : check mtds_0v2 to see if opticksMode:0 metadata works
--------------------------------------------------------------

::

    N[blyth@localhost junosw]$ t mtds_0v2
    mtds_0v2 () 
    { 
        local logdir=/tmp/$FUNCNAME;
        mkdir -p $logdir;
        export TDS_LOG_COPYDIR=$logdir;
        export EVTMAX=10;
        mtds0;
        mtds2;
        : initial thought was to keep the logs together with event;
        : BUT is rather convenient to keep them separate as grabbing logs;
        : only is typically much faster than the full event when using U4Recorder
    }


HMM stimer stopped before started::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    python: /data/blyth/junotop/opticks/sysrap/stimer.h:198: void stimer::stop(): Assertion `is_started()' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf25d614 in stimer::stop (this=0x93b390) at /data/blyth/junotop/opticks/sysrap/stimer.h:198
    #5  0x00007fffcf25d4a8 in stimer::done (this=0x93b390) at /data/blyth/junotop/opticks/sysrap/stimer.h:174
    #6  0x00007fffcf247f5a in SEvt::TimerDone () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:38
    #7  0x00007fffd2436dc7 in junoSD_PMT_v2_Opticks::EndOfEvent_Debug (this=0x5b9a9a0, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:202
    #8  0x00007fffd2436bcd in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5b9a9a0, eventID=0)

::

    epsilon:junosw blyth$ jgl SEvt::Timer 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc

    121 #ifdef WITH_G4CXOPTICKS
    122 void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
    123 {
    124     const GtOpticksTool* tool = GtOpticksTool::Get();
    125     NP* input_photon = tool ? tool->getInputPhoton() : nullptr ;
    126     // if(input_photon) SEvt::SetInputPhoton(input_photon); // NO LONGER NEEDED AS BORN INTO SEvt ALREADY
    127 
    128     SEvt::TimerStart() ;
    129 


Cause is that Initialize was only called for opticksMode > 0. 



DONE : check the mtds_0v2 metadata
---------------------------------------

::

    mtds_0v2             # workstation  

    jxm                  # laptop 
    ./mtds.sh grab_evt 
    ./mtds.sh cfmeta
    ...

    msab.c_itab

    array([[[13990, 13709, 13649, 13709, 14365, 14609, 13600, 13869, 14686, 14014],       ProcessHits_count 
            [13990, 13709, 13649, 13709, 14365, 14609, 13600, 13869, 14686, 14014]],        
            
           [[ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820],       ProcessHits_true 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[12268, 12055, 11947, 11952, 12574, 12848, 11910, 12100, 12923, 12194],       ProcessHits_false 
            [12268, 12055, 11947, 11952, 12574, 12848, 11910, 12100, 12923, 12194]],        
            
           [[ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820],       SaveNormHit_count 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        

           ...            
           
           [[11990, 11762, 11674, 11658, 12290, 12558, 11621, 11829, 12641, 11923],       NEDEP 
            [11990, 11762, 11674, 11658, 12290, 12558, 11621, 11829, 12641, 11923]],        
            
           [[   21,    31,    29,    28,    33,    36,    26,    34,    32,    32],       NBOUND 
            [   21,    31,    29,    28,    33,    36,    26,    34,    32,    32]],        

           ...
           
           [[  257,   262,   244,   266,   251,   254,   263,   237,   250,   239],       NDECULL 
            [  257,   262,   244,   266,   251,   254,   263,   237,   250,   239]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       YMERGE 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820],       YSAVE 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       opticksMode 
            [    2,     2,     2,     2,     2,     2,     2,     2,     2,     2]],        
            
           [[    0,     1,     2,     3,     4,     5,     6,     7,     8,     9],       eventID 
            [    0,     1,     2,     3,     4,     5,     6,     7,     8,     9]],        
            
           [[    1,     1,     1,     1,     1,     1,     1,     1,     1,     1],       VERSION 
            [    1,     1,     1,     1,     1,     1,     1,     1,     1,     1]]], dtype=uint64)        

    msab.c_ftab

    array([[[1.508, 1.378, 1.406, 1.417, 1.448, 1.446, 1.404, 1.455, 1.453, 1.425],       SEvt__TimerDone 
            [2.609, 2.423, 2.311, 2.38 , 2.504, 2.452, 2.285, 2.49 , 2.472, 2.391]]])        

    np.diff(msab.c_ttab)/1e6   # seconds between event starts

    array([[[1.517, 1.384, 1.412, 1.437, 1.454, 1.452, 1.41 , 1.461, 1.459],
            [2.93 , 2.787, 2.615, 2.626, 2.795, 2.739, 2.538, 2.782, 2.753]]])

    np.c_[msab.c_ttab[0,0].view('datetime64[us]'),msab.c_ttab[0,1].view('datetime64[us]')] # event start times (UTC)

    array([['2023-04-14T14:29:57.887804', '2023-04-14T14:35:02.443557'],
           ['2023-04-14T14:29:59.404948', '2023-04-14T14:35:05.373744'],
           ['2023-04-14T14:30:00.788716', '2023-04-14T14:35:08.160317'],
           ['2023-04-14T14:30:02.200884', '2023-04-14T14:35:10.775255'],
           ['2023-04-14T14:30:03.637759', '2023-04-14T14:35:13.401414'],
           ['2023-04-14T14:30:05.091874', '2023-04-14T14:35:16.196078'],
           ['2023-04-14T14:30:06.543738', '2023-04-14T14:35:18.935097'],
           ['2023-04-14T14:30:07.953988', '2023-04-14T14:35:21.472602'],
           ['2023-04-14T14:30:09.415081', '2023-04-14T14:35:24.254354'],
           ['2023-04-14T14:30:10.873962', '2023-04-14T14:35:27.006993']], dtype='datetime64[us]')

    In [1]:                                    




DONE : ntds0_cf checking timings and ProcessHits metadata between N=0 and N=1
-------------------------------------------------------------------------------

::

    N[blyth@localhost opticks]$ t ntds0_cf
    ntds0_cf () 
    { 
        : ntds0 is Geant4 running with minimal Opticks instrumentation : just event timing;
        : this function runs simulation with N:0 and N:1 geometries allowing comparisons;
        : of event timings without the U4Recorder overheads;
        : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds;
        export EVTMAX=10;
        N=0 GEOM=V0J008 ntds0;
        [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1;
        N=1 GEOM=V1J008 ntds0;
        [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2;
        return 0
    }
    N[blyth@localhost opticks]$ 


    msab.c_itab

    array([[[11274, 11012, 10851, 11422, 11372, 11151, 11535, 11250, 11123, 11001],       ProcessHits_count 
            [13990, 13709, 13649, 13709, 14365, 14609, 13600, 13869, 14686, 14014]],        
            
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       ProcessHits_true 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[ 9454,  9288,  9155,  9682,  9566,  9430,  9787,  9505,  9360,  9288],       ProcessHits_false 
            [12268, 12055, 11947, 11952, 12574, 12848, 11910, 12100, 12923, 12194]],        
            
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       SaveNormHit_count 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
           ...            
           
           [[ 9214,  9051,  8905,  9427,  9326,  9206,  9531,  9242,  9131,  9055],       NEDEP 
            [11990, 11762, 11674, 11658, 12290, 12558, 11621, 11829, 12641, 11923]],        
            
           [[    2,     1,     1,     0,     1,     2,     3,     1,     1,     0],       NBOUND 
            [   21,    31,    29,    28,    33,    36,    26,    34,    32,    32]],        
           ...            
           
           [[  238,   236,   249,   255,   239,   222,   253,   262,   228,   233],       NDECULL 
            [  257,   262,   244,   266,   251,   254,   263,   237,   250,   239]],        
           ...
           
           [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       YSAVE 
            [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       opticksMode 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[    0,     1,     2,     3,     4,     5,     6,     7,     8,     9],       eventID 
            [    0,     1,     2,     3,     4,     5,     6,     7,     8,     9]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       VERSION 
            [    1,     1,     1,     1,     1,     1,     1,     1,     1,     1]]], dtype=uint64)        

    msab.c_ftab

    array([[[1.484, 1.339, 1.322, 1.341, 1.355, 1.333, 1.397, 1.367, 1.342, 1.323],       SEvt__TimerDone 
            [1.508, 1.377, 1.391, 1.405, 1.45 , 1.447, 1.46 , 1.555, 1.511, 1.438]]])        

    np.diff(msab.c_ttab)/1e6   # seconds between event starts

    array([[[1.491, 1.342, 1.324, 1.343, 1.358, 1.336, 1.399, 1.37 , 1.345],
            [1.517, 1.382, 1.396, 1.41 , 1.455, 1.452, 1.465, 1.561, 1.516]]])

    np.c_[msab.c_ttab[0].T].view('datetime64[us]') # SEvt start times (UTC)

    array([['2023-04-14T17:40:13.243457', '2023-04-14T17:48:47.043104'],
           ['2023-04-14T17:40:14.734679', '2023-04-14T17:48:48.560221'],
           ['2023-04-14T17:40:16.076959', '2023-04-14T17:48:49.942403'],
           ['2023-04-14T17:40:17.401160', '2023-04-14T17:48:51.338727'],
           ['2023-04-14T17:40:18.744211', '2023-04-14T17:48:52.748784'],
           ['2023-04-14T17:40:20.101999', '2023-04-14T17:48:54.203329'],
           ['2023-04-14T17:40:21.437751', '2023-04-14T17:48:55.655199'],
           ['2023-04-14T17:40:22.837172', '2023-04-14T17:48:57.120255'],
           ['2023-04-14T17:40:24.206710', '2023-04-14T17:48:58.680800'],
           ['2023-04-14T17:40:25.551737', '2023-04-14T17:49:00.196843']], dtype='datetime64[us]')

    In [1]:                            




DONE : POM=0 ntds2_cf with GridXY input photons
-------------------------------------------------

Added page to presentation, no surprises. 


DONE : no-Opticks build test
---------------------------------------

1. ``jt ; vi bashrc.sh``
2. reconnect session for the env change 
3. ``jo ; ./build_Debug.sh``  

Nuclear check (make sure no use of stale Opticks headers)::

    rm -rf build
    ./build_Debug.sh


DONE  : no-Opticks run test
---------------------------------------

HMM: input photons will not work like this.::

    N=0 ntds0 


SKIP : Arrange error message when trying to use GtOpticksTool opticks input photons without WITH_G4CXOPTICKS
----------------------------------------------------------------------------------------------------------------

* instead just detect attempted use of GtOpticksTool at python level 


How will using "opticks" rather than "gun" fail ? Very non-informatively::

    **************************************************
    Terminating @ localhost.localdomain on Mon Apr 17 20:09:42 2023
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context  ** junotoptask **  Terminated with Error

    (gdb) bt
    No stack.

::

    N[blyth@localhost sniper]$ find . -name '*.cc' -exec grep -H "Terminated" {} \;
    ./SniperKernel/src/SniperContext.cc:        return "SNiPER::Context Terminated Successfully";
    ./SniperKernel/src/TaskWatchDog.cc:        msg += " **  Terminated with Error";
    N[blyth@localhost sniper]$ pwd
    /data/blyth/junotop/sniper
    N[blyth@localhost sniper]$ 


SniperKernel/src/TaskWatchDog.cc::

    061 TaskWatchDog::~TaskWatchDog()
     62 {
     63     if (isErr())
     64     {
     65         std::string msg = " ** ";
     66         msg += m_task.scope();
     67         msg += m_task.objName();
     68         msg += " **  Terminated with Error";
     69         sniper_context->reg_msg(msg);
     70     }
     71 }

    250 void TaskWatchDog::setErr()
    251 {
    252     typedef Sniper::RunStateInt S_Int;
    253     m_stat = (RunState)((S_Int)(RunState::Error) | (S_Int)(m_stat));
    254 }
    255 
    256 bool TaskWatchDog::isErr()
    257 {
    258     typedef Sniper::RunStateInt S_Int;
    259     return ((S_Int)(m_stat) & (S_Int)(RunState::Error));
    260 }

    BP=TaskWatchDog::setErr 


    junotoptask:DetSim0Svc.initialize  WARN: No Analysis Element is found.
    junotoptask:SniperProfiling.initialize  INFO: 
    GtOpticksTool::configure NOT WITH_G4CXOPTICKS ret 0
    junotoptask:GenTools.initialize  INFO: configure tool "ok" failed
    junotoptaskalgorithms.initialize ERROR: junotoptask:GenTools initialize failed

    Breakpoint 1, 0x00007fffed6cc820 in TaskWatchDog::setErr() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    (gdb) bt
    #0  0x00007fffed6cc820 in TaskWatchDog::setErr() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #1  0x00007fffed6c960b in Task::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #2  0x00007fffed6d2187 in TopTask::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #3  0x00007fffed6cda2b in TaskWatchDog::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffed6c9568 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so

::

    COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks 2>&1 | tee ntds0.tlog  

    [2023-04-17 20:09:37,245] p438398 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1331} INFO - setup_generator_opticks : objName:[ok]



Hmm looks like the "--opticks-anamgr" just does nothing in opticksMode:0 WITH_G4CXOPTICKS or without.::
   
    ntds0_cf



DONE : Python level detection of trying to use GtOpticksTool without Opticks
------------------------------------------------------------------------------

::

    1306     def setup_generator_opticks(self, task, args):
    1307         """
    1308         Former declProp controls have been removed. 
    1309         Are now using Opticks input photon machinery in order to 
    1310         profit from its automated frame transformation of input photons.
    1311 
    1312         OPTICKS_INPUT_PHOTON
    1313            selects path to .npy array of shape (n,4,4) 
    1314            with the input photons, see ana/input_photons.sh 
    1315 
    1316         MOI/INST/OPTICKS_INPUT_PHOTON_FRAME
    1317            controls target frame, see CSGFoundry::getFrameE 
    1318 
    1319         To follow how the hookup and transformation works see::
    1320 
    1321             SEvt::GetInputPhoton 
    1322             G4CXOpticks::setupFrame
    1323             CSGFoundry::getFrameE
    1324 
    1325         """
    1326         noop = os.environ.get("OPTICKS_PREFIX", None) is None
    1327         if noop:
    1328             log.fatal("setup_generator_opticks : Opticks Input Photons cannot be used when not compiled WITH_G4CXOPTICKS")
    1329             log.fatal("lack of WITH_G4CXOPTICKS is inferred by lack of OPTICKS_PREFIX envvar") 
    1330             sys.exit(1)
    1331         pass
    1332         import GenTools
    1333         gt = task.createAlg("GenTools")
    1334         ok = gt.createTool("GtOpticksTool/ok")
    1335         objName = ok.objName()
    1336         gt.property("GenToolNames").set([objName])
    1337         log.info("setup_generator_opticks : objName:[%s]" % (objName) )



DONE : detect no-Opticks from OPTICKS_PREFIX in ntds functions 
--------------------------------------------------------------------

Best to follow junosw and check OPTICKS_PREFIX::

    [ -z "$OPTICKS_PREFIX" ] && echo no-opticks

See junosw/cmake/JUNODependencies::

    167 ## Opticks
    168 if(DEFINED ENV{OPTICKS_PREFIX})
    169    set(Opticks_VERBOSE YES)
    170    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{JUNOTOP}/opticks/cmake/Modules")
    171    find_package(Opticks MODULE)
    172    message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
    173 endif()

Although CMTEXTRATAGS not containing opticks is still possible for now::

    N[blyth@localhost junotop]$ cat /data/blyth/junotop/ExternalLibs/opticks/head/bashrc



DONE : ntds0_cf N=0,N=1 not-WITH_G4CXOPTICKS
------------------------------------------------

N=0 edited::

    Begin of Event --> 0
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1820 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1724 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1696 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1740 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1806 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1721 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1748 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1745 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1713 hcMuon 0 hcOpticks -1 GPU NO
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 10          8.81300        0.88130      2.12749      
    DetSimAlg                10          14009.81702    1400.98170   43.09796     
    Sum of junotoptask       10          14018.94995    1401.89500   45.05009     
    #############################################################################


N=1 edited::

    ### Run : 0
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1722 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1654 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1702 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1757 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1791 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1761 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1690 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1769 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1820 hcMuon 0 hcOpticks -1 GPU NO

Compare with the WITH_G4CXOPTICKS instrumented counts, matches::

    OPTICKS_MODE=0 ./ntds.sh grab_evt   ## just metadata, not full SEvt
    OPTICKS_MODE=0 ./ntds.sh cfmeta
       
       [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       14:YSAVE 
        [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
 

DONE : Rebuild WITH_G4CXOPTICKS and repeat ntds0_cf : should get the same counts as above
-----------------------------------------------------------------------------------------------

NB have to comment IPHO for this, so use gun running 


N=0 edited::

    Begin of Event --> 0
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1820 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1724 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1696 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1740 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1806 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1721 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1748 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1745 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1713 hcMuon 0 hcOpticks -1 GPU NO
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 10          8.36400        0.83640      2.01664      
    DetSimAlg                10          14370.85583    1437.08558   47.09499     
    Sum of junotoptask       10          14379.52612    1437.95261   48.97203     
    #############################################################################


N=1 edited::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 1722 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 0 hitCollection 1654 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 0 hitCollection 1702 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 0 hitCollection 1757 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 0 hitCollection 1791 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 0 hitCollection 1761 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 0 hitCollection 1690 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 7 opticksMode 0 hitCollection 1769 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 8 opticksMode 0 hitCollection 1763 hcMuon 0 hcOpticks -1 GPU NO
    junoSD_PMT_v2::EndOfEvent eventID 9 opticksMode 0 hitCollection 1820 hcMuon 0 hcOpticks -1 GPU NO
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 10          10.15400       1.01540      2.51906      
    DetSimAlg                10          13458.78601    1345.87860   66.33544     
    Sum of junotoptask       10          13469.27026    1346.92703   68.10973     
    #############################################################################



::

    OPTICKS_MODE=0 ./ntds.sh grab_evt
    OPTICKS_MODE=0 ./ntds.sh cfmeta
       
       [[ 1820,  1724,  1696,  1740,  1806,  1721,  1748,  1745,  1763,  1713],       14:YSAVE 
        [ 1722,  1654,  1702,  1757,  1791,  1761,  1690,  1769,  1763,  1820]],        
        
    array([[[1.559, 1.398, 1.394, 1.433, 1.443, 1.41 , 1.446, 1.439, 1.417, 1.399],        0:SEvt__TimerDone 
            [1.471, 1.346, 1.355, 1.373, 1.433, 1.311, 1.256, 1.269, 1.311, 1.294]]])        





DONE : Review changed files
------------------------------

::

    epsilon:junosw blyth$ git --no-pager diff 636e^  --name-status

    A   Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    A   Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc       # pass to opticks/u4/U4Recorder

    M   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py          # --pmt-natural-geometry simplified input photon generator

    M   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
    M   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc       # reworked opticksMode:0

    A   Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h
    A   Simulation/DetSimV2/PMTSim/include/ModelTrigger_Debug.h         # Debug structs 

    M   Simulation/DetSimV2/PMTSim/CMakeLists.txt                       # add EGet dep 

    A   Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h           # docs, OpSurface prefix @# rovider 
    M   Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    M   Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    M   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    M   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc             # m_UsePMTNaturalGeometry impl

    M   Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
    M   Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc           # PMTSIM_STANDALONE, add fixed ModelTriggerSimple  

    M   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    M   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc                 # C4OpBoundaryProcess adapt, ProcessHits instrumented

    M   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    M   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh     # remove old blocks, add debug 

    M   Simulation/DetSimV2/PhysiSim/CMakeLists.txt                     # Added deps : IPMTSimParamSvc, PMTSimParamSvc, CUSTOM4_LIBRARIES 

    M   Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    M   Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    M   Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc                         
    M   Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
    M   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc           # Remove old WITH_G4OPTICKS macro blocks 

    M   Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    M   Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc           # declProp UsePMTOpticalModel UsePMTNaturalGeometry, hookup C4OpBoundaryProcess

    M   Simulation/GenTools/GenTools/GtOpticksTool.h
    M   Simulation/GenTools/src/GtOpticksTool.cc                        # Re-implemented to use Opticks input photons, with frame targetting 

    A   Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/_TComplex.h   # TComplex typedef 
    M   Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/MultiFilmModel.h
    M   Simulation/SimSvc/MultiFilmSimSvc/src/Material.h
    M   Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.h
    M   Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
    M   Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc          # changed in PMTSIM_STANDALONE to remove ROOT dep 

    A   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h         # provide PMT data to custom boundary process 
    M   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h     # invalid pmtid check
    M   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h     # quell pad compilation warning
    M   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h     # quell pad compilation warning
    M   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h    # convenient static, incomplete check
    M   Utilities/EGet/EGet/EGet.h                                            # Avoid compilation warning 

    M   cmake/JUNODependencies.cmake                                          # Add Custom4 external 



::

    git diff 636e^  Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h 




DONE : Make the Merge Request, Update issue 88
---------------------------------------------------

* include links to the presentation 
* https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/88

::

    epsilon:junosw blyth$ git push 
    Counting objects: 14, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (13/13), done.
    Writing objects: 100% (14/14), 1.29 KiB | 1.29 MiB/s, done.
    Total 14 (delta 10), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       52f5353..d00617f  blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ 


DONE : Complete the presentation, adding concluding page, push to 3 sites
----------------------------------------------------------------------------

* DONE : include links to issue, branch, MR 



