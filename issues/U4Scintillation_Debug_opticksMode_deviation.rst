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

