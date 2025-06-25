InputPhotonsCheck_WP
=======================

::

    153     elif [ "$TEST" == "WP_PMT" ]; then
    154 
    155        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    156        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    157        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    158        observation="B side sees no hits, like diff geom, TODO:try B side simtrace"



Overview
-----------

* lack of identity info on B side makes this difficult to debug from record and photon arrays


Big gun : U4Recorder__EndOfRunAction_Simtrace
------------------------------------------------

::

     091 const bool U4Recorder::EndOfRunAction_Simtrace = ssys::getenvbool("U4Recorder__EndOfRunAction_Simtrace") ;


     310 void U4Recorder::setU4Tree(const U4Tree* _tree)
     311 {
     312     tree = _tree ;
     313 }
     314 
     315 
     316 
     317 void U4Recorder::BeginOfRunAction(const G4Run*)
     318 {
     319     LOG(LEVEL);
     320 }
     321 
     322 /**
     323 U4Recorder::EndOfRunAction
     324 ---------------------------
     325 
     326 **/
     327 void U4Recorder::EndOfRunAction(const G4Run*)
     328 {
     329     SEvt::SetRunMeta<int>("FAKES_SKIP", int(FAKES_SKIP) );
     330 
     331 
     332     LOG(LEVEL)
     333         << "[ U4Recorder__EndOfRunAction_Simtrace : " << ( EndOfRunAction_Simtrace ? "YES" : "NO " )
     334         ;
     335 
     336     if(EndOfRunAction_Simtrace)
     337     {
     338         U4Simtrace::EndOfRunAction(tree) ;
     339     }
     340 
     341     LOG(LEVEL)
     342         << "] U4Recorder__EndOfRunAction_Simtrace : " << ( EndOfRunAction_Simtrace ? "YES" : "NO " )
     343         ;
     344 }



     40 inline void U4Simtrace::Scan(const U4Tree* tree)
     41 {
     42     int level = ssys::getenvint(U4Simtrace__level, 0);
     43 
     44     int eventID = 998 ;
     45 
     46     SEvt* evt = SEvt::CreateSimtraceEvent();
     47     evt->beginOfEvent(eventID);
     48 
     49     int num_simtrace = int(evt->simtrace.size()) ;
     50     if(level > 0) std::cout << "[U4Simtrace::Scan num_simtrace " << num_simtrace <<  "\n" ;
     51 
     52     U4Navigator nav(tree);
     53 
     54     for(int i=0 ; i < num_simtrace ; i++)
     55     {
     56         quad4& p = evt->simtrace[i] ;
     57         nav.simtrace(p);
     58         if( level > 1 && i % 1000 == 0 ) std::cout << "-U4Simtrace::Scan " << nav.isect.desc() << "\n" ;
     59     }
     60     if(level > 0) std::cout << "-U4Simtrace::Scan nav.stats.desc\n" << nav.stats.desc() << "\n" ;
     61 
     62 
     63     evt->gather();        // follow QSim::simulate
     64     evt->topfold->concat();
     65     evt->topfold->clear_subfold();
     66 
     67     evt->endOfEvent(eventID);
     68 
     69     if(level > 0) std::cout << "]U4Simtrace::Scan num_simtrace " << num_simtrace <<  "\n" ;
     70 }





HMM doing simtrace after an input photon run asserts... TODO: make simtrace take precedence rather than asserting
--------------------------------------------------------------------------------------------------------------------------

::

    2025-06-24 21:12:18.144 INFO  [3292039] [SEvt::transformInputPhoton@724]  SEvt__transformInputPhoton_VERBOSE  SEventConfig::IsRGModeSimulate 0 hasInputPhoton 1 proceed NO 
    sframe::desc inst 0 frs PMT_20inch_veto:0:1000
     ekvid sframe_OPTICKS_INPUT_PHOTON_FRAME_PMT_20inch_veto_0_1000 ek OPTICKS_INPUT_PHOTON_FRAME ev PMT_20inch_veto:0:1000
     ce  (3294.766,20310.441,734.451,261.940)  is_zero 0
     m2w ( 0.006, 0.035,-0.999, 0.000) (-0.987, 0.160, 0.000, 0.000) ( 0.160, 0.986, 0.036, 0.000) (3280.836,20224.570,731.346, 1.000) 
     w2m ( 0.006,-0.987, 0.160, 0.000) ( 0.035, 0.160, 0.986, 0.000) (-0.999,-0.000, 0.036, 0.000) (-0.004,-0.010,-20502.000, 1.000) 
     midx  301 mord    0 gord 1000
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier        0 sensor_index      0
     propagate_epsilon    0.05000 is_hostside_simtrace YES


    2025-06-24 21:12:18.146 FATAL [3292039] [SEvt::addGenstep@2103] input_photon_with_normal_genstep 1 MIXING input photons with other gensteps is not allowed  for example avoid defining OPTICKS_INPUT_PHOTON when doing simtrace
    python: /home/blyth/opticks/sysrap/SEvt.cc:2108: sgs SEvt::addGenstep(const quad6&): Assertion `input_photon_with_normal_genstep == false' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6


    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbe745d21 in SEvt::addGenstep (this=0xd1113260, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2108
    #6  0x00007fffbe745924 in SEvt::addGenstep (this=0xd1113260, a=0xcb893be0) at /home/blyth/opticks/sysrap/SEvt.cc:2071
    #7  0x00007fffbe74048a in SEvt::addInputGenstep (this=0xd1113260) at /home/blyth/opticks/sysrap/SEvt.cc:799
    #8  0x00007fffbe74390b in SEvt::beginOfEvent (this=0xd1113260, eventID=998) at /home/blyth/opticks/sysrap/SEvt.cc:1610
    #9  0x00007fffc0ee308b in U4Simtrace::Scan (tree=0x0) at /home/blyth/opticks/u4/U4Simtrace.h:47
    #10 0x00007fffc0ee301e in U4Simtrace::EndOfRunAction (tree=0x0) at /home/blyth/opticks/u4/U4Simtrace.h:36
    #11 0x00007fffc0ed1d12 in U4Recorder::EndOfRunAction (this=0x6801580) at /home/blyth/opticks/u4/U4Recorder.cc:338
    #12 0x00007fffbd999e22 in U4RecorderAnaMgr::EndOfRunAction (this=0x65e1b80, run=0xb95b0400) at /home/blyth/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:36
    #13 0x00007fffd486995a in MgrOfAnaElem::EndOfRunAction (this=0xa280950, run=0xb95b0400) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:39




jcv GtOpticksTool 
-------------------

Difficult to see anything special on the B side : perplexing 

* its the same code preparing the input photons ? 



Getting ZERO B side hits : looks like different (empty) geometry on B side ? 
------------------------------------------------------------------------------

::

    
    In [4]: a.f.inphoton[0]
    Out[4]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

    In [5]: b.f.inphoton[0]
    Out[5]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

    In [6]: np.all( a.f.inphoton == b.f.inphoton )
    Out[6]: np.True_


    vn [14]: a.f.record[0,:5,0]
    Out[14]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [ 3310.461, 20407.191,   988.109,     0.22 ],
           [ 3289.384, 20277.26 ,   983.411,     0.827],
           [ 3287.088, 20263.111,   980.263,     0.903],
           [ 3285.897, 20255.768,   980.413,     0.937]], dtype=float32)

    In [17]: b.f.record[0,:5,0]
    Out[17]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [ -523.403, -3226.422,   133.483,   110.716],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)




    In [15]: a.f.record[0,:5,1]
    Out[15]: 
    array([[-0.16 , -0.986, -0.036,  0.   ],
           [-0.16 , -0.986, -0.036,  0.   ],
           [-0.156, -0.964, -0.214,  0.   ],
           [-0.16 , -0.987,  0.02 ,  0.   ],
           [-0.156, -0.964, -0.216,  0.   ]], dtype=float32)

    In [20]: b.f.record[0,:5,1]
    Out[20]: 
    array([[-0.16 , -0.986, -0.036,  0.   ],
           [-0.16 , -0.986, -0.036,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ]], dtype=float32)



identity for PMT_20inch_veto:0:1000  that is 1+pmtid : 1+50000+1000
-----------------------------------------------------------------------

::

    In [35]:  a.f.record[:,:12,3,1].view(np.int32)
    Out[35]: 
    array([[    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ..., 51001, 51001, 51001, 51001, 51001],
           ...,
           [    0, 51001, 51001, 51001, 51001, ..., 51001, 51001, 51001, 51001, 51001],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001,     0,     0,     0, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0]], shape=(100000, 12), dtype=int32)


    In [38]: np.all( b.f.record[:,:12,3,1].view(np.int32) == 0 )
    Out[38]: np.True_


iindex
---------

::

    In [30]: a.f.record[:,:12,1,3].view(np.int32)
    Out[30]: 
    array([[    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ..., 44213, 44213, 44213, 44213, 44213],
           ...,
           [    0, 44213, 44213, 44213, 44213, ..., 44213, 44213, 44213, 44213, 44213],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213,     0,     0,     0, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0]], shape=(100000, 12), dtype=int32)

    In [31]: a.q
    Out[31]: 
    array([[b'TO BT BT BT BT EX                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BR BT BT BR BT BT BT EX                                                             '],
           ...,
           [b'TO BT BT BT BR BT BT BR BT BT BT SA                                                             '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BR SA                                                                                        '],
           [b'TO BT BT BT BT EC                                                                               ']], shape=(100000, 1), dtype='|S96')


    ## HMM iindex not set on B side anyhow ? 

    In [33]: b.f.record[:,:,1,3].view(np.int32).max()
    Out[33]: np.int32(0)

    In [34]: b.f.record[:,:,1,3].view(np.int32).min()
    Out[34]: np.int32(0)

    In [10]: b.q
    Out[10]: 
    array([[b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           ...,
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO SA                                                                                           '],
           [b'TO SA                                                                                           ']], shape=(100000, 1), dtype='|S96')








