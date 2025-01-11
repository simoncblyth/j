jok-tds-mu-running
===================

GUN4 214 Gev
--------------

Running with default OIM=3 taking far too long for 
a shakedown cycle, so start with OIM=1 just to see
the number of photons quickly as find opticks config
and momemntum at which can reasonably test largish
events without taking too long on the B side.::

    jok-;TEST=GUN4 OIM=1 jok-tds-gdb


    322    local gun3="gun --particles gamma --momentums 22.23 --momentums-interp KineticEnergy --positions 0 0 0"
    323    local gun4="gun --particles mu- --momentums 214000 --positions 0 0 0"   ## 214 GeV
    324    local gun5="gun --particles mu- --momentums  50000 --positions 0 0 0"   ##  50 GeV
    325    ## --momentums in MeV 
    326 
    327    jok-tds-inputphoton-unset 
    328 
    329    local trgs=""     ## "trgs" are arguments after the opts : eg "gun" or "opticks" 
    330    case $TEST in
    331      GUN0) trgs="$trgs $gun0" ;  jok-tds-inputphoton ;;
    332      GUN1) trgs="$trgs $gun1"  ;;
    333      GUN2) trgs="$trgs $gun2"  ;;
    334      GUN3) trgs="$trgs $gun3"  ;;
    335      GUN4) trgs="$trgs $gun4"  ;;
    336      GUN5) trgs="$trgs $gun5"  ;;
    337    esac



17 hours so far for 31M : have 8M to go
----------------------------------------

::

    31/17 = 1.82M per hour : 4-5 hrs more : so total time will be around 24hrs 


Check photon count from OIM:1 gensteps
---------------------------------------

::

    P[blyth@localhost A000]$ f
    Python 3.7.7 (default, May  7 2020, 21:25:33) 
    Type 'copyright', 'credits' or 'license' for more information
    IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.genstep                                          :       (147081, 6, 4) : 2:51:44.990420 
      : f.hit                                              :      (7188954, 4, 4) : 2:51:44.916420 
      : f.NPFold_index                                     :                 (2,) : 2:51:41.518401 
      : f.NPFold_meta                                      :                   25 : 2:51:41.517401 
      : f.NPFold_names                                     :                 (0,) : 2:51:41.517401 
      : f.sframe                                           : NO ATTR  2:51:41.517401 
      : f.sframe_meta                                      :                    5 : 2:51:41.517401 

     min_stamp : 2025-01-09 16:45:06.941630 
     max_stamp : 2025-01-09 16:45:10.414649 
     dif_stamp : 0:00:03.473019 
     age_stamp : 2:51:41.517401 

    In [1]: gs = f.genstep

    In [2]: gs.shape
    Out[2]: (147081, 6, 4)

    In [3]: gs[:,0,3].view(np.int32).sum()/1e6
    Out[3]: 37.942661   ## almost 38M photons 

    In [4]: gs[:,0,3].view(np.int32).max()
    Out[4]: 2257

    In [5]: gs[:,0,3].view(np.int32).min()
    Out[5]: 1

    In [6]: np.c_[np.unique(gs[:,0,3].view(np.int32), return_counts=True)]
    Out[6]: 
    array([[   1, 3191],
           [   2, 2011],
           [   3, 1464],
           [   4, 1216],
           [   5, 1072],
           ...,
           [2107,    1],
           [2127,    1],
           [2132,    1],
           [2162,    1],
           [2257,    1]])

    In [11]: f.hit.shape[0]/gs[:,0,3].view(np.int32).sum()
    Out[11]: 0.18946889360237543



Issue 1 : FIXED : config for lots of photons 
---------------------------------------------

With Philox should be G1 one billion::

      64 #if defined(RNG_XORWOW)
      65 const char* SEventConfig::_MaxCurandDefault = "M3" ;
      66 const char* SEventConfig::_MaxSlotDefault = "M3" ;
      67 const char* SEventConfig::_MaxGenstepDefault = "M3" ;
      68 const char* SEventConfig::_MaxPhotonDefault = "M3" ;
      69 const char* SEventConfig::_MaxSimtraceDefault = "M3" ;
      70 
      71 #elif defined(RNG_PHILOX) || defined(RNG_PHILITEOX)
      72 const char* SEventConfig::_MaxCurandDefault = "G1" ; // nominal 1-billion states, as Philox has no need for curandState loading  
      73 const char* SEventConfig::_MaxSlotDefault = "0" ;     // see SEventConfig::SetDevice : set according to VRAM  
      74 const char* SEventConfig::_MaxGenstepDefault = "M10" ;  // adhoc  
      75 const char* SEventConfig::_MaxPhotonDefault = "G1" ;
      76 const char* SEventConfig::_MaxSimtraceDefault = "G1" ;
      77 #endif
      78 



::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2025-01-09 15:56:51.879 FATAL [42233] [SEvt::setNumPhoton@2150]  num_photon/M 1 evt.max_photon/M 1
    python: /home/blyth/opticks/sysrap/SEvt.cc:2151: void SEvt::setNumPhoton(unsigned int): Assertion `num_photon_allowed' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffbed63c37 in SEvt::setNumPhoton (this=0xaee9b60, num_photon=1000094) at /home/blyth/opticks/sysrap/SEvt.cc:2151
    #5  0x00007fffbed6394f in SEvt::addGenstep (this=0xaee9b60, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2115
    #6  0x00007fffbed5fe1a in SEvt::AddGenstep (q=...) at /home/blyth/opticks/sysrap/SEvt.cc:1232
    #7  0x00007fffbfd82611 in U4::CollectGenstep_G4Cerenkov_modified (aTrack=0xd642ac20, aStep=0x6bf21f0, numPhotons=146, betaInverse=1, pmin=1.55e-06, pmax=1.5500000000000001e-05, maxCos=0.5577244841048522, maxSin2=0.68894339982997643, 
        meanNumberOfPhotons1=251.49849616620472, meanNumberOfPhotons2=251.49849616620472) at /home/blyth/opticks/u4/U4.cc:282
    #8  0x00007fffbdb451a8 in G4Cerenkov_modified::PostStepDoIt (this=0x51908e10, aTrack=..., aStep=...) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:364
    #9  0x00007fffcc035679 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffcc035a7b in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.jun


Issue 2 : NOT A SENSOR showing up a lot from idx 36M : looks to be Custom4 surfaces on WP PMTs doing this
----------------------------------------------------------------------------------------------------------

* :doc:`jok-tds-mu-running-NOT-A-SENSOR-warnings`




Log excerpts from 214 GeV mu- 
-------------------------------

::

    jok-;TEST=GUN4 OIM=3 jok-tds-gdb

    ...
    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    2025-01-09 17:35:45.651 INFO  [210943] [U4Recorder::BeginOfEventAction_@333]  eventID 0
    Begin of Event --> 0
    2025-01-09 17:35:45.848 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 0
    2025-01-09 17:35:55.560 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 100000
    2025-01-09 17:36:06.055 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 200000
    2025-01-09 17:36:17.077 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 300000
    2025-01-09 17:36:28.858 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 400000
    2025-01-09 17:36:28.858 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 400000
    2025-01-09 17:36:41.374 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 500000
    2025-01-09 17:36:41.374 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 500000
     decay 2 gammas 0.510999
    2025-01-09 17:36:57.232 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 600000
    2025-01-09 17:37:13.247 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 700000
    2025-01-09 17:37:13.248 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 700000
    2025-01-09 17:37:13.248 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 700000
    2025-01-09 17:37:29.459 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 800000



    2025-01-10 19:12:24.648 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38100000
    2025-01-10 19:20:58.702 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38200000
    2025-01-10 19:20:58.702 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38200000
    2025-01-10 19:20:58.702 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38200000
    2025-01-10 19:29:51.350 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38300000
    2025-01-10 19:38:58.570 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38400000
    2025-01-10 19:38:58.570 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38400000
    2025-01-10 19:46:24.194 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38500000
    2025-01-10 19:53:59.955 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38600000
    2025-01-10 20:00:58.643 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38700000
    2025-01-10 20:07:45.001 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38800000
    2025-01-10 20:14:28.635 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 38900000
    2025-01-10 20:22:16.326 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39000000
    2025-01-10 20:31:46.704 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39100000
    2025-01-10 20:31:46.704 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39100000
    2025-01-10 20:41:25.697 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39200000
    2025-01-10 20:49:54.849 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39300000
    2025-01-10 20:57:39.120 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39400000
    2025-01-10 21:06:17.227 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39500000
    2025-01-10 21:31:13.588 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39600000
    2025-01-10 22:10:17.243 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39700000
    2025-01-10 22:47:46.648 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39800000
    2025-01-10 23:56:25.343 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 39900000
    2025-01-11 00:38:58.573 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40000000
    2025-01-11 01:54:54.368 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40100000
    2025-01-11 02:35:09.383 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40200000
    2025-01-11 03:12:18.300 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40300000
    2025-01-11 04:08:12.739 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40400000
    2025-01-11 04:51:19.370 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40500000
    2025-01-11 05:36:56.097 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40600000
    2025-01-11 06:19:15.680 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40700000
    2025-01-11 07:20:08.923 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40800000
    2025-01-11 08:05:14.707 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 40900000
    2025-01-11 08:45:52.304 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 41000000
    2025-01-11 09:24:38.024 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 41100000
    2025-01-11 10:20:23.271 INFO  [210943] [U4Recorder::PreUserTrackingAction_Optical@450]  modulo 100000 : ulabel.id 41200000
    2025-01-11 10:29:14.439 INFO  [210943] [QSim::simulate@395] sslice {    0,162103,      0,41223427}
    //qcerenkov::wavelength_sampled_bndtex idx 7063722 sampledRI   1.792 cosTheta   0.954 sin2Theta   0.091 wavelength 159.703 count 84 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 8891482 sampledRI   1.790 cosTheta   0.918 sin2Theta   0.157 wavelength 160.095 count 52 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 9222595 sampledRI   1.771 cosTheta   0.919 sin2Theta   0.155 wavelength 148.945 count 73 matline 35 
    //qsim::propagate_at_surface_CustomART idx 10746354 lpmtid 51727 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 11013291 lpmtid 50896 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qcerenkov::wavelength_sampled_bndtex idx 18208022 sampledRI   1.616 cosTheta   0.939 sin2Theta   0.118 wavelength 202.052 count 51 matline 35 
    //qsim::propagate_at_surface_CustomART idx 19644617 lpmtid 52023 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qcerenkov::wavelength_sampled_bndtex idx 19778937 sampledRI   1.789 cosTheta   0.953 sin2Theta   0.092 wavelength 155.868 count 72 matline 35 
    //qsim::propagate_at_surface_CustomART idx 25909056 lpmtid 52399 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qcerenkov::wavelength_sampled_bndtex idx 28460005 sampledRI   1.751 cosTheta   0.970 sin2Theta   0.059 wavelength 147.137 count 66 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 32433173 sampledRI   1.790 cosTheta   0.956 sin2Theta   0.087 wavelength 157.415 count 63 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 32685808 sampledRI   1.792 cosTheta   0.916 sin2Theta   0.162 wavelength 159.523 count 58 matline 35 
    //qsim::propagate_at_surface_CustomART idx 40024358 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40024510 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40024543 lpmtid 52315 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40024210 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40024036 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40023891 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40025824 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40024774 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 40025338 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 



    //qsim::propagate_at_surface_CustomART idx 41147998 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41146488 lpmtid 52267 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41143625 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41143521 lpmtid 52364 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41143244 lpmtid 52208 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41145315 lpmtid 52352 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41146387 lpmtid 52390 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41142739 lpmtid 51908 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41144678 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41144697 lpmtid 52264 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 41145805 lpmtid 52385 : ERROR NOT-A-SENSOR : NAN_ABORT 
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 14877616 hcMuon 0 GPU YES
    hitCollectionTT.size: 0 userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           3.62300        3.62300      0.00000      
    DetSimAlg                1           147266544.00000147266544.0000015230.37806  
    Sum of junotoptask       1           147266544.00000147266544.0000015230.37806  
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-01-11 10:30:12,263] p210943 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:201} INFO - ]JUNOApplication.run
    [Thread 0x7fffd03dd700 (LWP 211089) exited]
    Delete G4SvcRunManager

    **************************************************
    Terminating @ localhost.localdomain on Sat Jan 11 10:30:13 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Thread 0x7fffb1bac700 (LWP 212431) exited]
    [Thread 0x7fffb63e2700 (LWP 211464) exited]
    [Thread 0x7ffff7fcc740 (LWP 210943) exited]
    [Thread 0x7fffb1397700 (LWP 212432) exited]
    [New process 210943]
    [Inferior 1 (process 210943) exited normally]
    (gdb) 



run_meta.txt::

    SEvt__BeginOfRun:1736415345651805,11279336,4352596
    SEvt__beginOfEvent_FIRST_ECPU:1736415345651923,11279336,4352604
    SEvt__setIndex_B000:1736415345652041,11279336,4352608
    SEvt__endIndex_B000:1736562554371733,16616908,9660740
    SEvt__beginOfEvent_FIRST_EGPU:1736562554384938,16616908,9660836
    SEvt__setIndex_A000:1736562554385041,16616908,9660836
    SEvt__endIndex_A000:1736562605021046,36414560,12252640
    SEvt__EndOfRun:1736562609240667,35924216,11762312


    1736562554371733 - 1736415345652041 = 147208719692


    2025-01-09 17:35:45.651
    2025-01-11 10:29:14.439   # 48 - 7 = ~41 hrs 

    In [6]: 147208/(60*60)
    Out[6]: 40.89111111111111


    1736562605021046 - 1736562554385041 = 50636005


    In [9]: 147208719692/50636005
    Out[9]: 2907.1945879616687





