junoPMTOpticalModel_vs_CustomBoundaryART_propagation_time_discrepancy.rst
============================================================================




Try to reproduce this, 2022/12/14
-----------------------------------

::

    u4t
    N=0 ./U4SimtraceTest.sh
    N=1 ./U4SimtraceTest.sh


* script name changed to 
* geometry changed from single PMT to two PMTs 


Add one_pmt two_pmt layout switch to hamaLogicalPMT.sh 

From looking back at github which is a month or so behind, it seems the one_pmt layout was using all defaults.

* https://github.com/simoncblyth/opticks/blob/master/u4/tests/U4PMTFastSimTest.sh

Also needed to control the photon generation within 
a layout switch : different geometry needs different source 
position and direction. 

This manages to find again the old familiar N=0 726 big bouncer:: 

    t.record[726,:n[726],0]   ## show step record points for PID 726  
    [[-113.       0.     200.       0.   ]
     [-113.       0.     170.163    0.137]
     [-112.83     0.     164.918    0.164]
     [-112.83     0.     164.917    0.164]
     [-135.824    0.       0.       1.012]
     [-156.577    0.    -148.846    1.778]
     [ -95.       0.    -104.211    2.166]
     [-238.764    0.      -0.       3.071]
     [-248.807    0.       7.28     3.112]
     [  53.205    0.     180.727    4.274]
     [ 214.06     0.       0.       5.507]
     [ 245.605    0.     -35.443    5.749]
     [  95.       0.     -99.428    6.583]
     [ 177.724    0.    -134.574    7.041]
     [ 160.533    0.       0.       7.732]
     [ 141.059    0.     152.451    8.245]
     [-138.46     0.       0.       9.867]
     [-239.66     0.     -55.195   10.455]
     [   0.427    0.       0.      11.71 ]
     [ 237.91     0.      54.596   12.523]]


Combined Simtrace and Simulate plotting formerly used xxv.sh 

With new U4SimtraceTest.sh need to set the FOCUS as now 
the Simtrace does all the geometry::

    FOCUS=0,10,185 N=0 ./U4SimtraceTest.sh ana
    FOCUS=0,10,185 N=1 ./U4SimtraceTest.sh ana

    FOCUS=0,10,185 N=0 APID=726 ./U4SimtraceTest.sh ana



Revive rerunning over in:

* opticks/notes/issues/U4SimulateTest_g4state_rerunning_not_aligning_big_bouncer_anymore.rst



Formerly
------------

::

    u4t 
    N=0 ./U4PMTFastSimTest.sh
    N=1 ./U4PMTFastSimTest.sh

    ./U4PMTFastSimTest.sh ncf


Time Difference
-----------------

Time difference to debug. Complicated by needing to map out the Fakes in a::


    In [10]: ar[:,:3].reshape(-1,12)
    Out[10]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-135.824,    0.   ,    0.   ,    1.012,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-156.577,    0.   , -148.846,    1.778,    0.81 ,    0.   ,    0.587,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [ -95.   ,    0.   , -104.211,    2.166,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-238.764,    0.   ,   -0.   ,    3.071,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-248.807,    0.   ,    7.28 ,    3.112,    0.867,    0.   ,    0.498,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [  53.205,    0.   ,  180.727,    4.274,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 214.06 ,    0.   ,    0.   ,    5.507,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 245.605,    0.   ,  -35.443,    5.749,   -0.92 ,    0.   ,   -0.391,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ],
           [  95.   ,    0.   ,  -99.428,    6.583,    0.92 ,    0.   ,   -0.391,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 177.724,    0.   , -134.574,    7.041,   -0.127,    0.   ,    0.992,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ],
           [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [-138.46 ,    0.   ,    0.   ,    9.867,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 237.91 ,    0.   ,   54.596,   12.523,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)




    In [11]: br[:,:3].reshape(-1,12)
    Out[11]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-156.577,    0.   , -148.846,    1.22 ,    0.81 ,    0.   ,    0.587,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [ -95.   ,    0.   , -104.211,    1.474,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-248.807,    0.   ,    7.28 ,    2.108,    0.867,    0.   ,    0.498,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [  53.206,    0.   ,  180.727,    3.269,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 245.605,    0.   ,  -35.443,    4.235,   -0.92 ,    0.   ,   -0.391,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ],
           [  95.   ,    0.   ,  -99.428,    4.781,    0.92 ,    0.   ,   -0.391,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 177.724,    0.   , -134.574,    5.08 ,   -0.127,    0.   ,    0.992,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ],
           [ 141.059,    0.   ,  152.451,    6.046,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [-239.66 ,    0.   ,  -55.195,    7.492,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ 237.91 ,    0.   ,   54.597,    9.127,   -0.846,    0.   ,   -0.533,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [  50.   ,    0.   ,  -63.74 ,    9.867,    0.846,    0.   ,   -0.533,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [  58.352,    0.   ,  -69.   ,    9.9  ,    0.846,    0.   ,   -0.533,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)

    In [12]:             



Use mapping to exclude the fakes and compare common points::

    31 # mapping from new to old point index for PID 726 big bouncer
    32 b2a = np.array([ 0,1,3,5,6,8,9,11,12,13,15,17,19 ])

    u4t
    ./U4PMTFastSimTest.sh ncf 

    In [1]: abr.reshape(-1,8)
    Out[1]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   , -113.   ,    0.   ,  200.   ,    0.   ],
           [-113.   ,    0.   ,  170.163,    0.137, -113.   ,    0.   ,  170.163,    0.137],
           [-112.83 ,    0.   ,  164.917,    0.164, -112.83 ,    0.   ,  164.917,    0.164],
           [-156.577,    0.   , -148.846,    1.778, -156.577,    0.   , -148.846,    1.22 ],
           [ -95.   ,    0.   , -104.211,    2.166,  -95.   ,    0.   , -104.211,    1.474],
           [-248.807,    0.   ,    7.28 ,    3.112, -248.807,    0.   ,    7.28 ,    2.108],
           [  53.205,    0.   ,  180.727,    4.274,   53.206,    0.   ,  180.727,    3.269],
           [ 245.605,    0.   ,  -35.443,    5.749,  245.605,    0.   ,  -35.443,    4.235],
           [  95.   ,    0.   ,  -99.428,    6.583,   95.   ,    0.   ,  -99.428,    4.781],
           [ 177.724,    0.   , -134.574,    7.041,  177.724,    0.   , -134.574,    5.08 ],
           [ 141.059,    0.   ,  152.451,    8.245,  141.059,    0.   ,  152.451,    6.046],
           [-239.66 ,    0.   ,  -55.195,   10.455, -239.66 ,    0.   ,  -55.195,    7.492],
           [ 237.91 ,    0.   ,   54.596,   12.523,  237.91 ,    0.   ,   54.597,    9.127]], dtype=float32)



* positions match closely, times are way off 

Time divergence increases:: 

    In [6]: abr[:,0,3] - abr[:,1,3]
    Out[6]: array([ 0.   ,  0.   , -0.   ,  0.558,  0.692,  1.004,  1.004,  1.514,  1.802,  1.96 ,  2.199,  2.963,  3.397], dtype=float32)
    ##              0       1       2        3       4      5        6       7       8      9       10      11      12

    In [7]: np.c_[abr.reshape(-1,8), abr[:,0,3] - abr[:,1,3]]
    Out[7]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   , -113.   ,    0.   ,  200.   ,    0.   ,    0.   ],
           [-113.   ,    0.   ,  170.163,    0.137, -113.   ,    0.   ,  170.163,    0.137,    0.   ],
           [-112.83 ,    0.   ,  164.917,    0.164, -112.83 ,    0.   ,  164.917,    0.164,   -0.   ],
           [-156.577,    0.   , -148.846,    1.778, -156.577,    0.   , -148.846,    1.22 ,    0.558],
           [ -95.   ,    0.   , -104.211,    2.166,  -95.   ,    0.   , -104.211,    1.474,    0.692],
           [-248.807,    0.   ,    7.28 ,    3.112, -248.807,    0.   ,    7.28 ,    2.108,    1.004],
           [  53.205,    0.   ,  180.727,    4.274,   53.206,    0.   ,  180.727,    3.269,    1.004],
           [ 245.605,    0.   ,  -35.443,    5.749,  245.605,    0.   ,  -35.443,    4.235,    1.514],
           [  95.   ,    0.   ,  -99.428,    6.583,   95.   ,    0.   ,  -99.428,    4.781,    1.802],
           [ 177.724,    0.   , -134.574,    7.041,  177.724,    0.   , -134.574,    5.08 ,    1.96 ],
           [ 141.059,    0.   ,  152.451,    8.245,  141.059,    0.   ,  152.451,    6.046,    2.199],
           [-239.66 ,    0.   ,  -55.195,   10.455, -239.66 ,    0.   ,  -55.195,    7.492,    2.963],
           [ 237.91 ,    0.   ,   54.596,   12.523,  237.91 ,    0.   ,   54.597,    9.127,    3.397]], dtype=float32)


The span 5->6(new) 8->9(old) is purely FastSim->FastSim, the time divergence does not increase there.
So the time discrepancy is happening in transitions between SlowSim and FastSim 

Distance between point i and i+1::

    In [21]: dist_ = lambda r,i:np.sqrt(np.sum( (r[i+1,0,:3]-r[i,0,:3])*(r[i+1,0,:3]-r[i,0,:3]) ))

    In [22]: dist_(br,0)
    Out[22]: 29.83699

    In [23]: dist_(br,1)
    Out[23]: 5.2487307

    In [24]: dist_(br,2)
    Out[24]: 316.7985

::

    r1dist_ = lambda r,i:np.sqrt(np.sum( (r[i+1,0,:3]-r[i,0,:3])*(r[i+1,0,:3]-r[i,0,:3]) ))
    r1time_ = lambda r,i:r[i+1,0,3] - r[i,0,3]
    r1speed_ = lambda r,i:r1dist_(r,i)/r1time_(r,i)


Do that in a vectorized way, as stepping point to doing this for array of multiple records::

    rvstep_ = lambda r:np.diff(r[:,0,:3],axis=0 )   
    rvdist_ = lambda r:np.sqrt(np.sum(np.diff(r[:,0,:3],axis=0 )*np.diff(r[:,0,:3],axis=0 ),axis=1)) 
    rvtime_ = lambda r:np.diff(r[:,0,3])
    rvspeed_ = lambda r:np.sqrt(np.sum(np.diff(r[:,0,:3],axis=0 )*np.diff(r[:,0,:3],axis=0 ),axis=1))/np.diff(r[:,0,3])




Lots of Pyrex speed inside PMT, where Vacuum speed expected::

    In [45]: for i in range(19): print(r1speed_(ar,i))
    218.03813   # 0->1    Water
    196.21465   # 1->2    Pyrex
    202.53773   # 2->3    Fake->FastSim : imprecise short hop 1e-3mm in Pyrex
    196.21484   # 3->4    FastSim->Fake : OOPS : Still Pyrex speed
    196.21487   # 4->5 
    196.21486   # 5->6 
    196.21486   # 6->7 
    299.7922    # 7->8    Fake->FastSim 
    299.79245   # 8->9    FastSim->FastSim  
    196.21486   # 9->10   FastSim->Fake  : HUH back to Pyrex on leaving FastSim 
    196.21503   # 10->11 
    196.21489   # 11->12
    196.21475   # 12->13 
    196.21498   # 13->13 
    299.79214   # 14->15  Fake->FastSim
    196.21487   # 15->16  FastSim->Fake  : Again back to Pyrex speed on leaving FastSim
    196.21515   # 16->17 
    196.21481   # 17->18
    299.79245   # 18->19  Fake->FastSim 


* SlowSim velocity stays at material2 of the last FresnelRefraction at point 1 (Water/Pyrex boundary) 
* Fake->FastSim and FastSim->FastSim velocity comes from manual propagation in the FastSim::DoIt  


With N=1 standard Geant4 gives lots of Vacuum speed propagation::

    In [46]: for i in range(19): print(r1speed_(br,i))
    218.03813   # 0->1
    196.21478   # 1->2
    299.79218   # 3 
    299.7922    # 4 
    299.79214   # 5 
    299.79218   # 6 
    299.79214   # 7 
    299.7921    # 8 
    299.79214   # 9 
    299.79227   # 10
    299.79218   # 11
    299.79214   # 12
    299.79224   # 13
    299.79114   # 14->15 ? 
    -9.127591   # 15 



I met similar issue before, that was fixed with::

    _track->UseGivenVelocity(true);

::

    143 void U4Recorder::PreUserTrackingAction_Optical(const G4Track* track)
    144 {
    145     bool resume_fSuspend = track == transient_fSuspend_track ;
    146     G4TrackStatus tstat = track->GetTrackStatus();
    147     LOG(LEVEL)
    148         << " track " << track
    149         << " status:" << U4TrackStatus::Name(tstat)
    150         << " resume_fSuspend " << ( resume_fSuspend ? "YES" : "NO" )
    151         ;
    152 
    153     assert( tstat == fAlive );
    154     LOG(LEVEL) << "[" ;
    155 
    156     G4Track* _track = const_cast<G4Track*>(track) ;
    157     _track->UseGivenVelocity(true); // notes/issues/Geant4_using_GROUPVEL_from_wrong_initial_material_after_refraction.rst
    158 


::

    epsilon:opticks blyth$ opticks-f UseGivenVelocity 
    ./cfg4/CCtx.cc:UseGivenVelocity(true)
    ./cfg4/CCtx.cc:    mtrack->UseGivenVelocity(true);
    ./cfg4/DsG4OpBoundaryProcess.cc:    //     G4Track::UseGivenVelocity is in force, that is done in CTrackingAction
    ./u4/U4Recorder.cc:    _track->UseGivenVelocity(true); // notes/issues/Geant4_using_GROUPVEL_from_wrong_initial_material_after_refraction.rst
    ./examples/Geant4/CerenkovMinimal/src/Ctx.cc:    const_cast<G4Track*>(track)->UseGivenVelocity(true);
    epsilon:opticks blyth$ 





Cause of wrong velocity with FastSim 
-----------------------------------------

Q : Why is Pyrex speed being used inside PMT for photon propagation with
    N=0 (FastSim) but the correct Vacuum speed with N=1 (CustomBoundaryART) ?

A : CustomBoundaryART is not using FastSim at all, just standard Geant4 
    with a CustomBoundary integrated into u4/InstrumentedG4OpBoundaryProcess
    so not surprising that N=1 has very standard propagation : because the 
    code is almost entirely standard Geant4 


* my suspicion is that wrong velocity is related to transitions between FastSim and SlowSim 
* Geant4 implements the SlowSim->FastSim handover by putting G4Track into fSuspend status 
  that subsequently gets set back to fAlive : have not pinned it down precisely 

Using the correct velocity requires quite a dance of passing 
it along and updating it that ordinary SlowSim/G4OpBoundaryProcess does. 
When using FastSim that does not run. So SlowSim velocity gets stuck at 
material2 of the last FresnelRefraction as SlowSim never saw any material 
transition. 


How to fix propagation velocity ?
--------------------------------------




What does G4Track::UseGivenVelocity actually do 
--------------------------------------------------

::

    190    G4bool   UseGivenVelocity() const;
    191    void     UseGivenVelocity(G4bool val);


    119 // velocity
    120    inline G4double G4Track::GetVelocity() const
    121    { return fVelocity; }
    122 
    123    inline void  G4Track::SetVelocity(G4double val)
    124    { fVelocity = val; }
    125 
    126    inline G4bool   G4Track::UseGivenVelocity() const
    127    { return  useGivenVelocity;}
    128 
    129    inline void     G4Track::UseGivenVelocity(G4bool val)
    130    { useGivenVelocity = val;}
    131 


    epsilon:j blyth$ g4-
    epsilon:j blyth$ g4-cc UseGivenVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/solidstate/phonon/src/G4VPhononProcess.cc:  sec->UseGivenVelocity(true);
    epsilon:j blyth$ 
    epsilon:j blyth$ g4-hh UseGivenVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4Track.hh:   G4bool   UseGivenVelocity() const; 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4Track.hh:   void     UseGivenVelocity(G4bool val);
    epsilon:j blyth$ 
    epsilon:j blyth$ g4-icc UseGivenVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4Track.icc:   inline G4bool   G4Track::UseGivenVelocity() const
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4Track.icc:   inline void     G4Track::UseGivenVelocity(G4bool val)
    epsilon:j blyth$ 
    epsilon:j blyth$ 

    epsilon:j blyth$ g4-cc useGivenVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:    useGivenVelocity(false),
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:    useGivenVelocity(false),
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:    useGivenVelocity(false),
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:   useGivenVelocity = right.useGivenVelocity; 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:  if (useGivenVelocity) return fVelocity;    
    epsilon:j blyth$ 



    221 ///////////////////
    222 G4double G4Track::CalculateVelocity() const
    223 ///////////////////
    224 {
    225   if (useGivenVelocity) return fVelocity;
    226 
    227   G4double velocity = c_light ;
    228 
    229   G4double mass = fpDynamicParticle->GetMass();
    230 
    231   // special case for photons
    232   if ( is_OpticalPhoton ) return CalculateVelocityForOpticalPhoton();
    233 
    234   // particles other than optical photon
    235   if (mass<DBL_MIN) {
    236     // Zero Mass
    237     velocity = c_light;
    238   } else {
    239     G4double T = (fpDynamicParticle->GetKineticEnergy())/mass;
    240     if (T > GetMaxTOfVelocityTable()) {
    241       velocity = c_light;
    242     } else if (T<DBL_MIN) {
    243       velocity =0.;
    244     } else if (T<GetMinTOfVelocityTable()) {
    245       velocity = c_light*std::sqrt(T*(T+2.))/(T+1.0);
    246     } else {
    247       velocity = velTable->Value(T);
    248     }
    249    
    250   }   
    251   return velocity ;
    252 }

If UseGivenVelocity is not set then does a GROUPVEL lookup for the material::

    254 ///////////////////
    255 G4double G4Track::CalculateVelocityForOpticalPhoton() const
    256 ///////////////////
    257 {
    258    
    259   G4double velocity = c_light ;
    260  
    261 
    262   G4Material* mat=0;
    263   G4bool update_groupvel = false;
    264   if ( fpStep !=0  ){
    265     mat= this->GetMaterial();         //   Fix for repeated volumes
    266   }else{
    267     if (fpTouchable!=0){
    268       mat=fpTouchable->GetVolume()->GetLogicalVolume()->GetMaterial();
    269     }
    270   }
    271   // check if previous step is in the same volume
    272     //  and get new GROUPVELOCITY table if necessary 
    273   if ((mat != 0) && ((mat != prev_mat)||(groupvel==0))) {
    274     groupvel = 0;
    275     if(mat->GetMaterialPropertiesTable() != 0)
    276       groupvel = mat->GetMaterialPropertiesTable()->GetProperty("GROUPVEL");
    277     update_groupvel = true;
    278   }
    279   prev_mat = mat;
    280  
    281   if  (groupvel != 0 ) {
    282     // light velocity = c/(rindex+d(rindex)/d(log(E_phot)))
    283     // values stored in GROUPVEL material properties vector
    284     velocity =  prev_velocity;
    285    
    286     // check if momentum is same as in the previous step
    287     //  and calculate group velocity if necessary 
    288     G4double current_momentum = fpDynamicParticle->GetTotalMomentum();
    289     if( update_groupvel || (current_momentum != prev_momentum) ) {
    290       velocity =
    291     groupvel->Value(current_momentum);
    292       prev_velocity = velocity;
    293       prev_momentum = current_momentum;
    294     }
    295   }  
    296  
    297   return velocity ;
    298 }
    299 


::

    epsilon:j blyth$ g4-cc GROUPVEL
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:// Updated:     2005-05-12 add SetGROUPVEL(), courtesy of
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  G4MaterialPropertyName.push_back(G4String("GROUPVEL"));
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  // if key is RINDEX, we calculate GROUPVEL - 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:      CalculateGROUPVEL();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  // if key is RINDEX, we calculate GROUPVEL -
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:      CalculateGROUPVEL();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:G4MaterialPropertyVector* G4MaterialPropertiesTable::CalculateGROUPVEL()
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  // check if "GROUPVEL" already exists
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  itr = MP.find(kGROUPVEL);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  // add GROUPVEL vector
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  // fill GROUPVEL vector using RINDEX values
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:    G4Exception("G4MaterialPropertiesTable::CalculateGROUPVEL()", "mat205",
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:      G4Exception("G4MaterialPropertiesTable::CalculateGROUPVEL()", "mat205",
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:        G4Exception("G4MaterialPropertiesTable::CalculateGROUPVEL()", "mat205",
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  this->AddProperty( "GROUPVEL", groupvel );
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:G4MaterialPropertyVector* G4MaterialPropertiesTable::SetGROUPVEL()
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  G4String message("SetGROUPVEL will be obsolete from the next release ");
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  message += "Use G4MaterialPropertiesTable::CalculateGROUPVEL() instead";
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  G4Exception("G4MaterialPropertiesTable::SetGROUPVEL()", "Obsolete",
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/src/G4MaterialPropertiesTable.cc:  return CalculateGROUPVEL();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:    //  and get new GROUPVELOCITY table if necessary 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:      groupvel = mat->GetMaterialPropertiesTable()->GetProperty("GROUPVEL");
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:    // values stored in GROUPVEL material properties vector
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/src/G4OpBoundaryProcess.cc:           Material2->GetMaterialPropertiesTable()->GetProperty(kGROUPVEL);
    epsilon:j blyth$ 





::

     539         aParticleChange.ProposeMomentumDirection(NewMomentum);
     540         aParticleChange.ProposePolarization(NewPolarization);
     541 
     542         if ( theStatus == FresnelRefraction || theStatus == Transmission ) {
     543            G4MaterialPropertyVector* groupvel =
     544            Material2->GetMaterialPropertiesTable()->GetProperty(kGROUPVEL);
     545            G4double finalVelocity = groupvel->Value(thePhotonMomentum);
     546            aParticleChange.ProposeVelocity(finalVelocity);
     547         }
     548 
     549         if ( theStatus == Detection && fInvokeSD ) InvokeSD(pStep);
     550 
     551         return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
     552 }


Hmm does ProposeVelocity imply UseGivenVelocity ? 


::


    epsilon:j blyth$ g4-cc ProposeVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/hadronic/processes/src/G4UCNBoundaryProcess.cc:  aParticleChange.ProposeVelocity(aTrack.GetVelocity());
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/hadronic/processes/src/G4UCNBoundaryProcess.cc:          aParticleChange.ProposeVelocity(std::sqrt(2*Enew/neutron_mass_c2)*c_light);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/hadronic/processes/src/G4UCNBoundaryProcess.cc:          aParticleChange.ProposeVelocity(std::sqrt(2*Enew/neutron_mass_c2)*c_light);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/electromagnetic/dna/management/src/G4ITTransportation.cc:    fParticleChange.ProposeVelocity(initialVelocity);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/electromagnetic/dna/management/src/G4ITTransportation.cc:      fParticleChange.ProposeVelocity(finalVelocity);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/src/G4OpBoundaryProcess.cc:        aParticleChange.ProposeVelocity(aTrack.GetVelocity());
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/src/G4OpBoundaryProcess.cc:           aParticleChange.ProposeVelocity(finalVelocity);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/solidstate/phonon/src/G4PhononReflection.cc:    aParticleChange.ProposeVelocity(vg);
    epsilon:j blyth$ 


    epsilon:j blyth$ g4-hh ProposeVelocity 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4ParticleChange.hh://   Add  Get/ProposeVelocity                       Apr 2011 H.Kurashige
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/include/G4ParticleChange.hh:    void ProposeVelocity(G4double finalVelocity);
    epsilon:j blyth$ 



ProposeVelocity at head and tail of G4OpBoundaryProcess::PostStepDoIt::


     169 G4VParticleChange*
     170 G4OpBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     171 {
     172         theStatus = Undefined;
     173 
     174         aParticleChange.Initialize(aTrack);
     175         aParticleChange.ProposeVelocity(aTrack.GetVelocity());
     ...
     539         aParticleChange.ProposeMomentumDirection(NewMomentum);
     540         aParticleChange.ProposePolarization(NewPolarization);
     541 
     542         if ( theStatus == FresnelRefraction || theStatus == Transmission ) {
     543            G4MaterialPropertyVector* groupvel =
     544            Material2->GetMaterialPropertiesTable()->GetProperty(kGROUPVEL);
     545            G4double finalVelocity = groupvel->Value(thePhotonMomentum);
     546            aParticleChange.ProposeVelocity(finalVelocity);
     547         }
     548 
     549         if ( theStatus == Detection && fInvokeSD ) InvokeSD(pStep);
     550 
     551         return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
     552 }


g4-cls G4ParticleChange::

    148     G4double GetVelocity() const;
    149     void ProposeVelocity(G4double finalVelocity);
    150     // Get/Propose the final velocity of the current particle.

    048 inline
     49  G4double G4ParticleChange::GetVelocity() const
     50 {
     51    return theVelocityChange;
     52 }
     53 
     54 inline
     55   void G4ParticleChange::ProposeVelocity(G4double finalVelocity)
     56 {
     57    theVelocityChange = finalVelocity;
     58    isVelocityChanged = true;
     59 }


    348 G4Step* G4ParticleChange::UpdateStepForPostStep(G4Step* pStep)
    349 {
    350   // A physics process always calculates the final state of the particle
    351 
    352   // Take note that the return type of GetMomentumChange is a
    353   // pointer to G4ParticleMometum. Also it is a normalized 
    354   // momentum vector.
    355 
    356   G4StepPoint* pPostStepPoint = pStep->GetPostStepPoint();
    357   G4Track* pTrack = pStep->GetTrack();
    358 
    359   // Set Mass/Charge
    360   pPostStepPoint->SetMass(theMassChange);
    361   pPostStepPoint->SetCharge(theChargeChange);
    362   pPostStepPoint->SetMagneticMoment(theMagneticMomentChange);
    363 
    364   // update kinetic energy and momentum direction
    365   pPostStepPoint->SetMomentumDirection(theMomentumDirectionChange);
    366   pPostStepPoint->SetKineticEnergy( theEnergyChange );
    367 
    368   // calculate velocity
    369   pTrack->SetKineticEnergy( theEnergyChange );
    370   if (!isVelocityChanged) {
    371     if(theEnergyChange > 0.0) {
    372       theVelocityChange = pTrack->CalculateVelocity();
    373     } else if(theMassChange > 0.0) {
    374       theVelocityChange = 0.0;
    375     }
    376   }
    377   pPostStepPoint->SetVelocity(theVelocityChange);
    378 

