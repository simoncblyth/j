OPTICKS_INTEGRATION_MODE_3_U4Recorder_revive
=============================================



Fixed : just by bash level command changes
----------------------------------------------

Issue : changing to OIM 3 not writing B000 event ? 
----------------------------------------------------

::

    P[blyth@localhost ALL0]$ jok-;jok-tds-gdb


::

    P[blyth@localhost ALL0]$ pwd
    /data/blyth/opticks/GEOM/J_2024aug27/jok-tds/ALL0
    P[blyth@localhost ALL0]$ l
    total 3160
       4 -rw-r--r--. 1 blyth blyth     455 Nov  8 17:28 sample_detsim_user.root
       4 -rw-rw-r--. 1 blyth blyth    1504 Nov  8 17:28 run_meta.txt
       4 -rw-rw-r--. 1 blyth blyth     132 Nov  8 17:28 run.npy
    3144 -rw-r--r--. 1 blyth blyth 3213546 Nov  8 17:25 jok-tds.log
       0 drwxrwxr-x. 3 blyth blyth     103 Nov  8 17:25 .
       4 drwxr-xr-x. 2 blyth blyth    4096 Oct 31 16:21 A000
       0 drwxrwxr-x. 3 blyth blyth      18 Aug 27 10:17 ..
    P[blyth@localhost ALL0]$ 



Hmm probably pilot error, 

* missing some control for U4RecorderAnaMgr to kick in ?


jcv JUNODetSimModule::
i

    0526         # == opticks ==
     527         grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=0,
     528                                 help=mh("Control Opticks GPU Optical simulation"))
     529         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     530                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
     531 


    2229     def init_detsim_anamgr(self, task, args, sim_conf):
    2230         detsimfactory = sim_conf.detsimfactory()
    2231 
    2232         # == reset the anamgr list to data model writer ==
    2233         detsimfactory.property("AnaMgrList").set([])
    2234         # == op simulator interface ==
    2235         if args.deferred_op:
    2236             detsimfactory.property("AnaMgrList").append("OPSimAnaMgr")
    2237             deferred_opsim_anamgr = sim_conf.tool("OPSimAnaMgr")
    2238             deferred_opsim_anamgr.property("TestingRatio").set(args.deferred_op_testing_ratio)
    2239         # == opticks
    2240         if args.opticks_anamgr:
    2241             if args.opticks_mode in [2,3]:
    2242                 print("appending U4RecorderAnaMgr to AnaMgrList in opticks_mode %d " % args.opticks_mode )
    2243                 detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2244                 g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2245                 g4ok_anamgr.setLogLevel(4)
    2246             elif args.opticks_mode in [0,1]:
    2247                 print("IGNORING: --opticks-anamgr option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )
    2248             else:
    2249                 print("UNEXPECTED opticks_mode %s " % args.opticks_mode )
    2250             pass
    2251         pass



Bump up the logging 
---------------------

::

    P[blyth@localhost ALL0]$ jok-;LOG=1 jok-tds-gdb

