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

::

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
    Out[3]: 37.942661

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


