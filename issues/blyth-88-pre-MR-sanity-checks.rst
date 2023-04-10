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



TODO : investigate why opticksMode:2 is not matching opticksMode:0 
-----------------------------------------------------------------------

* all it takes is for the random streams to get out of line 



