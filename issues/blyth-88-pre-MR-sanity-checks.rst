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



TODO : review opticksMode:2 vs opticksMode:0 code difference, and vary that
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



TODO : tidy up debug instrumentation
----------------------------------------------

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

    1114 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
    1115 {
    1116 #ifdef WITH_G4CXOPTICKS_DEBUG
    1117     // relocated here rather than within _Opticks as want to check 
    1118     // for differences between opticksMode
    1119     // Needs to be prior to m_jpmt_opticks->EndOfEvent(HCE) for saving genstep labels
    1120     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
    1121     G4int eventID = event->GetEventID() ;
    1122     U4Debug::Save(eventID);
    1123 #endif
    1124 



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



TODO : get opticksMode:2 to run without geometry translation
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
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 0 m_opticksMode 2 gpu_simulation  NO  hitCollection 1872 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 1 m_opticksMode 2 gpu_simulation  NO  hitCollection 1793 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 2 m_opticksMode 2 gpu_simulation  NO  hitCollection 1765 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 3 m_opticksMode 2 gpu_simulation  NO  hitCollection 1716 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 4 m_opticksMode 2 gpu_simulation  NO  hitCollection 1760 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 5 m_opticksMode 2 gpu_simulation  NO  hitCollection 1713 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 6 m_opticksMode 2 gpu_simulation  NO  hitCollection 1671 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 7 m_opticksMode 2 gpu_simulation  NO  hitCollection 1833 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 8 m_opticksMode 2 gpu_simulation  NO  hitCollection 1749 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1134:  eventID 9 m_opticksMode 2 gpu_simulation  NO  hitCollection 1719 hitCollection_muon 0 hitCollection_opticks 0
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





WIP : Debug Random consumption mis-alignement between opticksMode:0 and 2
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



HMM:: where is the SEvt::save invoked ?
--------------------------------------------

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


TODO : find where opticksMode:0 and opticksMode:2 put the randoms to different use
--------------------------------------------------------------------------------------

Hmm S4RandomArray can return consumption indices that can associate with junctures in the code. 





