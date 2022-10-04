U4Scintillation_Debug_opticksMode_deviation
=============================================

Issue
---------

Original motivation for U4Scintillation_Debug was investigating a lack of scint gensteps. 
Whilst looking into that notice deviation between opticksMode 0 and 3.  

Would expect opticksMode 0 and 3 to have exact same steps in DsG4Scintillation 
but notice a deviation ?  Is there some difference in random consumption ? 
First event starts matches then deviates after 35 scint steps. 

opticksMode:0
    as if thre is no Opticks there
opticksMode:3
    both CPU and GPU propagations, the CPU ones should be the same as opticksMode:0

Hmm although am looking at Scintillation the culprit may well be 
a difference in Cerenkov random consumption between the modes. 
Check this by arranging for Cerenkov to be the same in the two modes.

* NB : remember the simulations will have different numbers of hits unless align the randoms 
* YES : but the input steps should always match between opticksMode, as that happens before the "fork"  


Switch on WITH_G4CXOPTICKS_DEBUG from opticks/cmake/Modules/FindOpticks.cmake
---------------------------------------------------------------------------------

* hmm : a less disruptive way of doing this would be good

::

    N[blyth@localhost DetSimOptions]$ l /tmp/u4debug/ntds3/000/
    total 16
    4 -rw-rw-r--. 1 blyth blyth  256 Oct  5 00:44 gsl.npy
    4 -rw-rw-r--. 1 blyth blyth  640 Oct  5 00:44 U4Cerenkov_Debug.npy
    4 -rw-rw-r--. 1 blyth blyth  352 Oct  5 00:44 U4Hit_Debug.npy
    4 -rw-rw-r--. 1 blyth blyth 3136 Oct  5 00:44 U4Scintillation_Debug.npy
    0 drwxr-xr-x. 2 blyth blyth  105 Sep 30 00:03 .






Like-with-like hit comparison could do with a reverse convert from JUNO hits into sphoton 
-------------------------------------------------------------------------------------------

YES: but photon-photon A-B comparison is more useful and already exists. 




Compare logging between opticksMode
---------------------------------------

console::

    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2022-10-04 21:31:40.559 INFO  [454769] [junoSD_PMT_v2::EndOfEvent@1136] [ m_opticksMode  3
    2022-10-04 21:31:40.559 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 0 m_opticksMode 3
    2022-10-04 21:31:40.590 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@190]  eventID 0 num_genstep 8 num_photon 198 num_hit 27 way_enabled 0
    2022-10-04 21:31:40.591 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@260] 
         0 gp.x  -13840.08 gp.y   -8162.24 gp.z  -10659.09 gp.R   19281.76 pmt   13743          CK|RE|SD|BT
         1 gp.x  -13331.45 gp.y   -7860.98 gp.z  -11652.90 gp.R   19372.99 pmt   14076          CK|RE|SD|BT
         2 gp.x   -7827.26 gp.y  -16841.33 gp.z    5141.73 gp.R   19270.02 pmt    6269          CK|RE|SD|BT
         3 gp.x    4013.39 gp.y   18846.77 gp.z    -557.95 gp.R   19277.43 pmt    9155          CK|RE|SD|BT
         4 gp.x   11006.93 gp.y    1139.18 gp.z   15895.42 gp.R   19367.88 pmt    1389       CK|RE|SC|SD|BT
         5 gp.x    7690.82 gp.y   -3541.02 gp.z  -17384.95 gp.R   19337.11 pmt   16847             CK|SD|BT
         6 gp.x    4684.89 gp.y   -5573.78 gp.z  -17938.22 gp.R   19359.62 pmt   16987             CK|SD|BT
         7 gp.x  -12764.92 gp.y    4749.99 gp.z  -13713.54 gp.R   19327.88 pmt   15195             CK|SD|BT
         8 gp.x   -5851.42 gp.y  -10440.19 gp.z   15212.75 gp.R   19356.25 pmt    1731          CK|RE|SD|BT
         9 gp.x    -691.47 gp.y   -7847.75 gp.z   17595.27 gp.R   19278.46 pmt     667          CK|RE|SD|BT
        10 gp.x   -9707.40 gp.y  -10428.95 gp.z   13029.62 gp.R   19307.19 pmt    2738          CK|RE|SD|BT
        11 gp.x  -15516.48 gp.y  -10178.67 gp.z    5478.87 gp.R   19349.02 pmt    6063          CK|RE|SD|BT
        12 gp.x    -122.60 gp.y   13468.08 gp.z  -13786.96 gp.R   19273.94 pmt   15324             CK|SD|BT
        13 gp.x   -4878.42 gp.y     572.70 gp.z  -18668.98 gp.R   19304.35 pmt   17368          CK|RE|SD|BT
        14 gp.x   -8272.88 gp.y      -5.72 gp.z  -17387.26 gp.R   19255.06 pmt   16808          CK|RE|SD|BT
        15 gp.x   -9965.39 gp.y   -7149.86 gp.z  -14860.47 gp.R   19268.18 pmt   15659       CK|RE|SC|SD|BT
        16 gp.x   -2736.98 gp.y  -18782.29 gp.z   -3344.45 gp.R   19273.07 pmt   10332          CK|SC|SD|BT
        17 gp.x  -17931.17 gp.y    5115.71 gp.z   -5171.71 gp.R   19350.55 pmt   11367          CK|RE|SD|BT
        18 gp.x  -18328.21 gp.y    3982.93 gp.z    4665.50 gp.R   19327.54 pmt    6660          CK|RE|SD|BT
        19 gp.x   -9390.79 gp.y   -5545.32 gp.z  -15898.02 gp.R   19279.12 pmt   16170             CK|SD|BT



    2022-10-04 21:31:40.591 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@262] ] num_hit 27 merged_count  0 savehit_count  27 m_merged_total 0 m_savehit_total 0 m_opticksMode 3
    2022-10-04 21:31:40.591 INFO  [454769] [junoSD_PMT_v2_Opticks::TerminateEvent@314]  invoking SEvt::Clear as no U4Recorder detected 
    2022-10-04 21:31:40.592 INFO  [454769] [junoSD_PMT_v2::EndOfEvent@1142] ] m_opticksMode  3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 41 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    Begin of Event --> 1
    2022-10-04 21:31:40.609 INFO  [454769] [junoSD_PMT_v2::EndOfEvent@1136] [ m_opticksMode  3
    2022-10-04 21:31:40.609 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 1 m_opticksMode 3
    2022-10-04 21:31:40.619 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@190]  eventID 1 num_genstep 7 num_photon 174 num_hit 28 way_enabled 0
    2022-10-04 21:31:40.620 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@260] 
         0 gp.x     840.38 gp.y   19245.69 gp.z    1502.42 gp.R   19322.53 pmt    8114             CK|SD|BT
         1 gp.x  -13430.50 gp.y   -7767.71 gp.z  -11408.74 gp.R   19258.11 pmt   14076          CK|RE|SD|BT
         2 gp.x  -14922.10 gp.y   11530.04 gp.z    4201.58 gp.R   19320.04 pmt    6864          CK|RE|SD|BT
         3 gp.x  -15151.85 gp.y    5609.26 gp.z   10628.09 gp.R   19339.04 pmt    3868          CK|RE|SD|BT
         4 gp.x   10853.07 gp.y    1425.27 gp.z   15936.91 gp.R   19334.06 pmt    1390       CK|RE|SC|SD|BT
         5 gp.x   11710.61 gp.y   14482.46 gp.z   -5129.43 gp.R   19318.16 pmt   11299             CK|SD|BT
         6 gp.x  -17505.01 gp.y    6837.48 gp.z   -4430.66 gp.R   19308.22 pmt   10926          CK|RE|SD|BT
         7 gp.x    5155.31 gp.y   17928.19 gp.z   -5137.70 gp.R   19349.24 pmt   11313       CK|RE|SC|SD|BT
         8 gp.x   -4309.12 gp.y    6244.47 gp.z   17786.38 gp.R   19336.94 pmt     640          CK|RE|SD|BT
         9 gp.x   18004.06 gp.y   -1181.39 gp.z    6883.82 gp.R   19311.37 pmt    5532          CK|RE|SD|BT
        10 gp.x   -6796.09 gp.y  -17821.26 gp.z    2825.18 gp.R   19281.23 pmt    7360       CK|RE|SC|SD|BT
        11 gp.x     402.42 gp.y   13634.73 gp.z   13677.00 gp.R   19316.53 pmt    2522             CK|SD|BT
        12 gp.x    -375.25 gp.y   -7398.15 gp.z   17840.73 gp.R   19317.48 pmt     590          CK|RE|SD|BT
        13 gp.x    3970.24 gp.y   18829.30 gp.z   -2085.23 gp.R   19355.97 pmt    9813          CK|RE|SD|BT
        14 gp.x     613.82 gp.y    5148.76 gp.z  -18582.24 gp.R   19292.12 pmt   17353          CK|RE|SD|BT
        15 gp.x   -9336.95 gp.y  -10053.78 gp.z   13517.45 gp.R   19260.80 pmt    2424          CK|RE|SD|BT
        16 gp.x  -15324.87 gp.y   -9948.44 gp.z    6100.48 gp.R   19262.37 pmt    5860          CK|RE|SD|BT
        17 gp.x    6492.38 gp.y  -17771.98 gp.z    3689.73 gp.R   19277.15 pmt    6953       CK|RE|SC|SD|BT
        18 gp.x  -10800.15 gp.y   15883.43 gp.z   -2041.98 gp.R   19315.70 pmt    9841          CK|RE|SD|BT
        19 gp.x   11743.43 gp.y   12659.67 gp.z    8629.24 gp.R   19303.86 pmt    4771             CK|SD|BT

    2022-10-04 21:31:40.620 INFO  [454769] [junoSD_PMT_v2_Opticks::EndOfEvent@262] ] num_hit 28 merged_count  0 savehit_count  28 m_merged_total 0 m_savehit_total 27 m_opticksMode 3
    2022-10-04 21:31:40.620 INFO  [454769] [junoSD_PMT_v2_Opticks::TerminateEvent@314]  invoking SEvt::Clear as no U4Recorder detected 
    2022-10-04 21:31:40.620 INFO  [454769] [junoSD_PMT_v2::EndOfEvent@1142] ] m_opticksMode  3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 36 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 2           7.12800        3.56400      3.16100      
    DetSimAlg                2           93.24000       46.62000     19.13000     
    Sum of junotoptask       2           100.50200      50.25100     22.35000     
    #############################################################################



opticksMode:0::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 14 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    Begin of Event --> 1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 8 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################





Pinning Cerenkov to be the same in two modes
-----------------------------------------------

::

    123 void DsPhysConsOptical::ConstructProcess()
    124 {
    125     SetParameters();
    126 
    127     G4VProcess* cerenkov_ = 0;
    128 
    129     LogInfo<<"check: m_useCerenKov == "<< m_useCerenkov <<std::endl;
    130     LogInfo<<"check: m_useScintillation == "<< m_useScintillation  <<std::endl;
    131     LogInfo<<"check:  m_useScintSimple == "<<  m_useScintSimple <<std::endl;
    132     if (m_useCerenkov) {
    133         if( m_opticksMode == 0 || m_opticksMode == 3 )  // SCB:TMP add m_opticksMode 3, checking mode consistency
    134         {
    135             if (m_useCerenkovType == "modified") {
    136                 G4Cerenkov_modified* cerenkov = new G4Cerenkov_modified() ;
    137                 cerenkov->SetMaxNumPhotonsPerStep(m_cerenMaxPhotonPerStep);
    138                 cerenkov->SetStackPhotons(m_cerenPhotonStack);



TODO: move genstep collection into G4Cerenkov_modified and effect opticksMode action inside there
----------------------------------------------------------------------------------------------------


After pinning Cerenkov as shown above get a mode match for Scintillation
---------------------------------------------------------------------------

::

    epsilon:tests blyth$ ./U4Scintillation_Debug.sh 
    a00 /tmp/ntds0/000/U4Scintillation_Debug.npy (47, 8) 
    a01 /tmp/ntds0/001/U4Scintillation_Debug.npy (51, 8) 
    a30 /tmp/ntds3/000/U4Scintillation_Debug.npy (44, 8) 
    a31 /tmp/ntds3/001/U4Scintillation_Debug.npy (46, 8) 
    b00 /tmp/scintcheck/ntds0/000/U4Scintillation_Debug.npy (47, 8) 
    b01 /tmp/scintcheck/ntds0/001/U4Scintillation_Debug.npy (51, 8) 
    b30 /tmp/scintcheck/ntds3/000/U4Scintillation_Debug.npy (47, 8) 
    b31 /tmp/scintcheck/ntds3/001/U4Scintillation_Debug.npy (51, 8) 


    In [1]: np.all( b00 == b30 )
    Out[1]: True

    In [2]: np.all( b01 == b31 )
    Out[2]: True





Observing the deviation
-------------------------

First event starts matched between modes and then diverges after around 35 steps::

    epsilon:tests blyth$ ./U4Scintillation_Debug.sh 
    a00 /tmp/ntds0/000/U4Scintillation_Debug.npy (47, 8) 
    a30 /tmp/ntds3/000/U4Scintillation_Debug.npy (44, 8) 

    a01 /tmp/ntds0/001/U4Scintillation_Debug.npy (51, 8) 
    a31 /tmp/ntds3/001/U4Scintillation_Debug.npy (46, 8) 

    In [1]:                                 


    In [11]: a30[:40] - a00[:40]
    Out[11]: 
    array([[  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ,   0.   ,  -0.   ,   0.   ,   0.   ],
           [  0.039,   0.156,  -0.064,  -0.   ,   0.   ,   0.006,   0.   ,   0.   ],
           [  0.068,   0.285,  -0.037,   0.   ,   0.   ,   0.005,   0.   ,   0.   ],
           [ 11.511, -17.731,  -6.895,   0.078,   0.   ,  -0.031,   0.   ,   0.   ],
           [  0.059,  -0.08 ,   0.416,  -0.002,   0.   ,   0.005,   0.   ,   0.   ],
           [  0.288,  -0.029,   0.204,  -0.001,   0.   ,  -0.   ,   0.   ,   0.   ]])

::

    In [6]: np.all( b00[:34] == b30[:34] )
    Out[6]: False

    In [7]: np.all( b00[:33] == b30[:33] )
    Out[7]: True



    In [17]: chk = lambda i:(b00[i],b30[i],1e9*(b00[i]-b30[i]))

    In [20]: chk(33)                                                                                                                                                                                          
    Out[20]: 
    (array([  53.854,  -89.508, -212.887,    0.817, 9846.   ,    0.022,    0.   ,    0.   ]),
     array([  53.854,  -89.508, -212.887,    0.817, 9846.   ,    0.022,    0.   ,    0.   ]),
     array([ 0.   ,  0.   ,  0.   ,  0.   ,  0.   , -4.579,  0.   ,  0.   ]))

    In [21]: chk(34)                                                                                                                                                                                          
    Out[21]: 
    (array([  53.991,  -89.643, -213.075,    0.818, 9846.   ,    0.018,    0.   ,    0.   ]),
     array([  53.991,  -89.643, -213.075,    0.818, 9846.   ,    0.018,    0.   ,    0.   ]),
     array([    0.   ,     0.   ,     0.   ,     0.   ,     0.   , 20897.486,     0.   ,     0.   ]))

    In [22]: chk(20)                                                                                                                                                                                          
    Out[22]: 
    (array([  57.432,  112.899, -305.613,    2.693, 9846.   ,    0.   ,    0.   ,    0.   ]),
     array([  57.432,  112.899, -305.613,    2.693, 9846.   ,    0.   ,    0.   ,    0.   ]),
     array([0., 0., 0., 0., 0., 0., 0., 0.]))

    In [23]:                                                       



First value to observe as deviated between modes is MeanNumberOfTracks::

     22 struct U4_API U4Scintillation_Debug
     23 {
     24     static const plog::Severity LEVEL ;
     25     static std::vector<U4Scintillation_Debug> record ;
     26     static constexpr const unsigned NUM_QUAD = 2u ;
     27     static constexpr const char* NAME = "U4Scintillation_Debug.npy" ;
     28     static constexpr int LIMIT = 10000 ;
     29     static constexpr const char* EKEY = "U4Scintillation_Debug_SaveDir" ;
     30     static const char* SaveDir ;
     31     static void Save(const char* dir);
     32     static void EndOfEvent(int eventID);
     33 
     34     double posx ;
     35     double posy ;
     36     double posz ;
     37     double time ;
     38 
     39     double ScintillationYield ;
     40     double MeanNumberOfTracks ;
     41     double NumTracks ;
     42     double Spare ;
     43 
     44     void add();
     45 };






2nd event starts different::

    In [4]: a31[:10]
    Out[4]: 
    array([[   0.   ,    0.   ,    0.   ,    0.   , 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 168.427,  149.446,  -42.151,    0.764, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 148.257,  161.436,  -46.566,    0.844, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  90.507,   96.319,  -90.784,    1.169, 9846.   ,    0.   ,    0.   ,    0.   ],
           [  67.806,   35.521,  -77.489,    1.39 , 9846.   ,    0.   ,    0.   ,    0.   ],
           [  75.365,   33.046,  -70.015,    1.427, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 121.865,   54.626, -126.45 ,    1.681, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -37.232,  101.664, -238.894,    2.35 , 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -33.838,  130.477, -280.668,    2.519, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ -19.609,  162.758, -271.009,    2.641, 9846.   ,    0.   ,    0.   ,    0.   ]])

    In [5]: a01[:10]
    Out[5]: 
    array([[   0.   ,    0.   ,    0.   ,    0.   , 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 283.662,  150.353,  326.141,    1.527, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 322.588,  183.266,  344.402,    1.707, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 349.046,  235.23 ,  374.167,    1.926, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 252.809,  184.465,  378.6  ,    2.289, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 253.828,  209.124,  358.778,    2.394, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 251.024,  237.018,  361.219,    2.488, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 229.093,  266.752,  310.241,    2.698, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 282.134,  212.965,  272.794,    2.979, 9846.   ,    0.   ,    0.   ,    0.   ],
           [ 465.702,   64.132,  370.269,    3.832, 9846.   ,    0.   ,    0.   ,    0.   ]])

