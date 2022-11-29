junoPMTOpticalModelSimple
============================

Prior :doc:`junoPMTOpticalModel`

* NEXT : Need to get junoPMTOpticalModelSimple operational, and then compare it to original


::

    U4Recorder::Check_TrackStatus_Flag@485:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 2) BT                0              ccd nib  3 TO BT BT
    U4Recorder::UserSteppingAction_Optical@471: ]
    U4Recorder::UserSteppingAction_Optical@393: [
    U4StepPoint::Flag@175:  failed to define flag for StepPoint  G4StepStatus fExclusivelyForcedProc proc fast_sim_man procName fast_sim_man
    U4Recorder::UserSteppingAction_Optical@444:  ERR flag zero : post U4StepPoint::Desc proc 5 procName fast_sim_man procNameRaw fast_sim_man status 6 statusName fExclusivelyForcedProc bstat 2 bstatName FresnelRefraction flag 0 flagName .
    Assertion failed: (flag > 0), function UserSteppingAction_Optical, file /Users/blyth/opticks/u4/U4Recorder.cc, line 445.
    Process 87976 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
        frame #0: 0x00007fff70412b66 libsystem_kernel.dylib`__pthread_kill + 10
    libsystem_kernel.dylib`__pthread_kill:
    ->  0x7fff70412b66 <+10>: jae    0x7fff70412b70            ; <+20>
        0x7fff70412b68 <+12>: movq   %rax, %rdi
        0x7fff70412b6b <+15>: jmp    0x7fff70409ae9            ; cerror_nocancel
        0x7fff70412b70 <+20>: retq   
    Target 0: (U4PMTFastSimTest) stopped.
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff70412b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff705dd080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff7036e1ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff703361ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x0000000100264207 libU4.dylib`void U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(this=0x0000000107e9a6e0, step=0x0000000107e70880) at U4Recorder.cc:445
        frame #5: 0x0000000100263a66 libU4.dylib`void U4Recorder::UserSteppingAction<InstrumentedG4OpBoundaryProcess>(this=0x0000000107e9a6e0, step=0x0000000107e70880) at U4Recorder.cc:99
        frame #6: 0x0000000100035991 U4PMTFastSimTest`U4RecorderTest::UserSteppingAction(this=0x0000000107e9bd20, step=0x0000000107e70880) at U4RecorderTest.h:162
        frame #7: 0x00000001000359cc U4PMTFastSimTest`non-virtual thunk to U4RecorderTest::UserSteppingAction(this=0x0000000107e9bd20, step=0x0000000107e70880) at U4RecorderTest.h:0
        frame #8: 0x000000010221bf06 libG4tracking.dylib`G4SteppingManager::Stepping(this=0x0000000107e706f0) at G4SteppingManager.cc:243
        frame #9: 0x000000010223286f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x0000000107e706b0, apValueG4Track=0x0000000107981780) at G4TrackingManager.cc:126
        frame #10: 0x00000001020f871a libG4event.dylib`G4EventManager::DoProcessing(this=0x0000000107e70620, anEvent=0x00000001079805c0) at G4EventManager.cc:185
        frame #11: 0x00000001020f9c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x0000000107e70620, anEvent=0x00000001079805c0) at G4EventManager.cc:338
        frame #12: 0x00000001020059e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x0000000107e70440, i_event=0) at G4RunManager.cc:399
        frame #13: 0x0000000102005815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x0000000107e70440, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #14: 0x0000000102003cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x0000000107e70440, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #15: 0x0000000100039803 U4PMTFastSimTest`U4PMTFastSimTest::U4PMTFastSimTest(this=0x00007ffeefbfe2e8) at U4PMTFastSimTest.cc:33
        frame #16: 0x00000001000398a5 U4PMTFastSimTest`U4PMTFastSimTest::U4PMTFastSimTest(this=0x00007ffeefbfe2e8) at U4PMTFastSimTest.cc:32
        frame #17: 0x0000000100039dd9 U4PMTFastSimTest`main(argc=1, argv=0x00007ffeefbfe6a0) at U4PMTFastSimTest.cc:49
        frame #18: 0x00007fff702c2015 libdyld.dylib`start + 1
    (lldb) 





The old big bouncer::

    In [4]: t.record[726].reshape(-1,16)                                                                                                                                             
    Out[4]: 
    0 ###([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    1 ###  [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    2      [-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    3      [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    4 ###  [-135.824,    0.   ,    0.   ,    1.012,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    5      [-156.577,    0.   , -148.846,    1.778,    0.81 ,    0.   ,    0.587,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    6      [ -95.   ,    0.   , -104.211,    2.166,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    7      [-238.764,    0.   ,   -0.   ,    3.071,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    8      [-248.807,    0.   ,    7.28 ,    3.112,    0.867,    0.   ,    0.498,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    9      [  53.205,    0.   ,  180.727,    4.274,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    10 ### [ 214.06 ,    0.   ,    0.   ,    5.507,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    11     [ 245.605,    0.   ,  -35.443,    5.749,   -0.92 ,    0.   ,   -0.391,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    12     [  95.   ,    0.   ,  -99.428,    6.583,    0.92 ,    0.   ,   -0.391,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    13     [ 177.724,    0.   , -134.574,    7.041,   -0.127,    0.   ,    0.992,    0.   ,   -0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    14 ??? [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    15     [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    16 ### [-138.46 ,    0.   ,    0.   ,    9.867,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    17     [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    18     [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    19 ### [ 237.91 ,    0.   ,   54.596,   12.523,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
    20     [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)


CF with junoPMTOpticalModelSimple:: 

    In [2]: extra.reshape(-1,16)                                                                                                                                                                              
    Out[2]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,   -0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,   -0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)








Repeated Step Point ? Lots of them
-------------------------------------

U4Recorder may be double-step recording with natural geometry. 
Perhaps from a SlowSim step point then FastSim step point at same position ?

::

    In [6]: t.record[2,:5]
    Out[6]: 
    array([[[-74.467, -46.371, 200.   ,   0.   ],
            [  0.   ,   0.   ,  -1.   ,   0.   ],
            [  0.529,  -0.849,  -0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-74.467, -46.371, 178.31 ,   0.099],
            [  0.02 ,   0.013,  -1.   ,   0.   ],
            [  0.529,  -0.849,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-74.362, -46.306, 173.173,   0.126],
            [ -0.086,  -0.053,  -0.995,   0.   ],
            [  0.529,  -0.849,  -0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-74.362, -46.306, 173.173,   0.126],
            [ -0.086,  -0.053,  -0.995,   0.   ],
            [  0.529,  -0.849,  -0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]]], dtype=float32)




::

    U4VPrimaryGenerator::GeneratePrimaries ph (1000, 4, 4, )
    U4RecorderTest::GeneratePrimaries@144: ]
    U4Recorder::BeginOfEventAction@93: 
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   999 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   998 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   997 seq.desc_seqhis                 0           8cbccd nib  6 TO BT BT BR BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   996 seq.desc_seqhis                 0        8cccccccd nib  9 TO BT BT BT BT BT BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   995 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   994 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   993 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   992 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   991 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   990 seq.desc_seqhis                 0            8cccd nib  5 TO BT BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   989 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   988 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   987 seq.desc_seqhis                 0            8bbcd nib  5 TO BT BR BR SA




::

    state = np.array([ 
    2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 
    535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 
    287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066, 
    335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64 )

    U4Recorder::PreUserTrackingAction_Optical@226: ]
    U4Recorder::UserSteppingAction_Optical@393: [
    U4Recorder::UserSteppingAction_Optical@412:  first_point, track 0x7f8b0a6a48d0
    SEvt::pointPhoton@1274: (  726, 0) TO                0                d nib  1 TO
    U4Recorder::UserSteppingAction_Optical@453: U4StepPoint::DescPositionTime (   -113.000      0.000    170.163      0.137)
    U4Recorder::Check_TrackStatus_Flag@491:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 1) BT                0               cd nib  2 TO BT
    U4Recorder::UserSteppingAction_Optical@477: ]
    U4Recorder::UserSteppingAction_Optical@393: [
    U4Recorder::UserSteppingAction_Optical@453: U4StepPoint::DescPositionTime (   -112.830      0.000    164.917      0.164)
    U4Recorder::Check_TrackStatus_Flag@491:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 2) BT                0              ccd nib  3 TO BT BT
    U4Recorder::UserSteppingAction_Optical@477: ]
    junoPMTOpticalModelSimple::ModelTrigger@68:  ModelTrigger_count   0 z      164.9 Result : YES
    junoPMTOpticalModelSimple::DoIt@122:  position (-112.83,0,164.917) direction (-0.138092,0,-0.990419) polarization (0,-1,0) surface_normal (-0.353306,0,0.935508)
    junoPMTOpticalModelSimple::DoIt@216:  T 0.254981 R 0.0358249 A 0.709195 status A
    U4Recorder::UserSteppingAction_Optical@393: [
    U4Recorder::UserSteppingAction_Optical@443:  DEFER_FSTRACKINFO  fstrackinfo_stat A flag SURFACE_ABSORB
    U4Recorder::UserSteppingAction_Optical@453: U4StepPoint::DescPositionTime (   -112.830      0.000    164.917      0.164)
    U4Recorder::Check_TrackStatus_Flag@491:  step.tstat fStopAndKill SURFACE_ABSORB from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 3) SA                0             8ccd nib  4 TO BT BT SA
    U4Recorder::UserSteppingAction_Optical@477: ]
    U4Recorder::PostUserTrackingAction@96: 
    U4Recorder::PostUserTrackingAction_Optical@304: [
    U4Recorder::PostUserTrackingAction_Optical@307: fStopAndKill
    U4Recorder::PostUserTrackingAction_Optical@330:  label.id   726 seq.desc_seqhis                 0             8ccd nib  4 TO BT BT SA
    U4Recorder::PostUserTrackingAction_Optical@344: ]



    state = np.array([ 
    2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 
    535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 
    287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066, 
    335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64 )

    U4Recorder::PreUserTrackingAction_Optical@226: ]
    U4Recorder::UserSteppingAction_Optical@393: [
    U4Recorder::UserSteppingAction_Optical@412:  first_point, track 0x7fec22d4c4d0
    SEvt::pointPhoton@1274: (  726, 0) TO                0                d nib  1 TO
    U4Recorder::UserSteppingAction_Optical@453: U4StepPoint::DescPositionTime (   -113.000      0.000    170.163      0.137)
    U4Recorder::Check_TrackStatus_Flag@491:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 1) BT                0               cd nib  2 TO BT
    U4Recorder::UserSteppingAction_Optical@477: ]
    U4Recorder::UserSteppingAction_Optical@393: [
    U4Recorder::UserSteppingAction_Optical@453: U4StepPoint::DescPositionTime (   -112.830      0.000    164.918      0.164)
    U4Recorder::Check_TrackStatus_Flag@491:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    SEvt::pointPhoton@1274: (  726, 2) BT                0              ccd nib  3 TO BT BT
    U4Recorder::UserSteppingAction_Optical@477: ]
    junoPMTOpticalModel::ModelTrigger_@267: junoPMTOpticalModel::ModelTrigger photon_id    726 ret 1
    junoPMTOpticalModel::ModelTrigger@161:  ModelTrigger_count   0 Result : YES
    junoPMTOpticalModel::DoIt@301: junoPMTOpticalModel::DoIt pmtid 0
    junoPMTOpticalModel::setEnergyThickness@786: junoPMTOpticalModel::setEnergyThickness energy 2.952e-06 energy_eV 2.952 _wavelength  0.00042 _wavelength/nm  420 n_glass 1.48426 n_coating 1.94133 k_coating 0 n_photocathode 2.27348 k_photocathode 1.40706
    junoPMTOpticalModel::UpdateTrackInfo@556: 




Flip the Simple approach with::

    export hama_UseNaturalGeometry=0
    export hama_UseNaturalGeometry=1


Without::

    fastTrack.GetPrimaryTrack()->GetStep()
        ->GetPostStepPoint()->SetStepStatus(fGeomBoundary);

Get::

    U4Recorder::UserSteppingAction_Optical@393: [
    U4StepPoint::Flag@175:  failed to define flag for StepPoint  G4StepStatus fExclusivelyForcedProc proc fast_sim_man procName fast_sim_man
    U4Recorder::UserSteppingAction_Optical@450:  ERR flag zero : post U4StepPoint::Desc proc 5 procName fast_sim_man procNameRaw fast_sim_man status 6 statusName fExclusivelyForcedProc bstat 2 bstatName FresnelRefraction flag 0 flagName .
    Assertion failed: (flag > 0), function UserSteppingAction_Optical, file /Users/blyth/opticks/u4/U4Recorder.cc, line 451.
    ./U4PMTFastSimTest.sh: line 87: 92403 Abort trap: 6           $bin
    ./U4PMTFastSimTest.sh run error
    epsilon:tests blyth$ 


Maybe the reason for fake same material volumes is because cannot stop the ordinary G4OpBoundary running 
before the FastSim ? 

HMM: if thats the case, there is perhaps a way to define G4Region associated with "ghost volumes" ?


::

    123 inline void G4FastStep::ForceSteppingHitInvocation()
    124 {
    125   ProposeSteppingControl(NormalCondition);
    126 }





Maybe its being kicked from SlowSlim to FastSim and not going anyhere ?

:: 

    In [6]: seqhis_(t.seq[328,0])
    Out[6]: ['TO BT BT BT BT BR BT SA', '?0?']





    In [5]: t.record[328,:10]                                                                                                                                    
    Out[5]: 
    array([[[  86.   ,    0.   ,  200.   ,    0.   ],
            [   0.   ,    0.   ,   -1.   ,    0.   ],
            [  -0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  86.   ,    0.   ,  178.779,    0.097],
            [  -0.024,    0.   ,   -1.   ,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  85.879,    0.   ,  173.649,    0.123],
            [   0.098,    0.   ,   -0.995,    0.   ],
            [   0.   ,   -1.   ,   -0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  85.879,    0.   ,  173.649,    0.123],
            [   0.002,    0.   ,   -1.   ,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  85.879,    0.   ,  173.649,    0.123],
            [  -0.066,    0.   ,   -0.998,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  85.879,    0.   ,  173.649,    0.123],
            [   0.45 ,    0.   ,    0.893,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[  88.165,    0.   ,  178.188,    0.14 ],
            [   0.467,    0.   ,    0.884,    0.   ],
            [  -0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[ 522.064,    0.   , 1000.   ,    4.403],
            [   0.467,    0.   ,    0.884,    0.   ],
            [   0.   ,   -1.   ,    0.   ,  420.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ]],

           [[   0.   ,    0.   ,    0.   ,    0.   ],
            [   0.   ,    0.   ,    0.   ,    0.   ],

