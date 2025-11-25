


::

    (ok) A[blyth@localhost u4]$ opticks-f SetFabricatedLabel
    ./u4/U4Track.h:    static void SetFabricatedLabel(const G4Track* track);
    ./u4/U4Track.h:inline void U4Track::SetFabricatedLabel(const G4Track* track)
    ./u4/U4Recorder.cc:the U4Track::SetFabricatedLabel method is below used to creates a label based entirely
    ./u4/U4Recorder.cc:    U4Track::SetFabricatedLabel<C4Pho>(track);
    ./u4/U4Recorder.cc:    U4Track::SetFabricatedLabel<spho>(track);
    (ok) A[blyth@localhost opticks]$ u4


    A[blyth@localhost NormalTrackInfo]$ jgr U4Recorder
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                print("appending U4RecorderAnaMgr to AnaMgrList in opticks_mode %d " % args.opticks_mode )    
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                print("IGNORING: --opticks-anamgr option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )    

    2323         # == opticks
    2324         if args.opticks_anamgr:
    2325             if args.opticks_mode in [2,3]:
    2326                 print("appending U4RecorderAnaMgr to AnaMgrList in opticks_mode %d " % args.opticks_mode )
    2327                 detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    2328                 g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    2329                 g4ok_anamgr.setLogLevel(4)
    2330             elif args.opticks_mode in [0,1]:
    2331                 print("IGNORING: --opticks-anamgr option AS U4RecorderAnaMgr is not compatible with opticks_mode %d " % args.opticks_mode )
    2332             else:
    2333                 print("UNEXPECTED opticks_mode %s " % args.opticks_mode )
    2334             pass
    2335         pass


