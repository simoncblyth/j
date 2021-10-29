

    O[blyth@localhost junoenv]$ bash junoenv opticks touchbuild


    #CMT---> (constituents.make) DetSimOptionscompile done
    #CMT---> (constituents.make) Starting DetSimOptionsinstall
    #CMT---> building static library ../Linux-x86_64/libDetSimOptions.a
    #CMT---> building shared library ../Linux-x86_64/libDetSimOptions.so
    DetSimOptionstemp_shlib/LSExpDetectorConstruction.o: In function `LSExpDetectorConstruction::setupCD_PMTs()':
    /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/cmt/../src/LSExpDetectorConstruction.cc:1214: undefined reference to `JUNO::Ball::HexagonPosBall::HexagonPosBall(Task*, bool)'
    /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/cmt/../src/LSExpDetectorConstruction.cc:1185: undefined reference to `JUNO::Ball::HexagonPosBall::HexagonPosBall(Task*, bool)'
    DetSimOptionstemp_shlib/LSExpDetectorConstruction.o: In function `LSExpDetectorConstruction::setupWP_PMTs()':
    /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/cmt/../src/LSExpDetectorConstruction.cc:1240: undefined reference to `JUNO::Ball::VetoPmtPosBall::VetoPmtPosBall(Task*)'
    collect2: error: ld returned 1 exit status
    make[2]: *** [../Linux-x86_64/libDetSimOptions.so] Error 1


Try full build::

    O[blyth@localhost junoenv]$ bash junoenv offline


::

    #--------------------------------------------------------------
    # Now trying [cmt make] in /data/blyth/junotop/offline/Simulation/ElecSimV3/ElecSimAlg/cmt (118/131)
    #--------------------------------------------------------------
    #CMT---> Info: Execute action make => gmake bin=../Linux-x86_64/ 
    #CMT---> (Makefile.header) Rebuilding ../Linux-x86_64/Linux-x86_64.make
    #CMT---> (constituents.make) Rebuilding library links
    #CMT---> (constituents.make) Building ElecSimAlg.make
    #CMT---> (constituents.make) Building ElecSimAlg_python.make
    #CMT---> Info: Document ElecSimAlg_python
    #CMT---> Info: Library ElecSimAlg
    #CMT---> (constituents.make) Starting ElecSimAlg_python
    #CMT---> (constituents.make) Starting ElecSimAlgprototype
    gmake[2]: `ElecSimAlgprototype' is up to date.
    Installing files from ../python to /data/blyth/junotop/offline/InstallArea
    #CMT---> (constituents.make) ElecSimAlgprototype done
    #CMT---> (constituents.make) Starting ElecSimAlgcompile
    #CMT---> (ElecSimAlg.make) Rebuilding ../Linux-x86_64/ElecSimAlg_dependencies.make
    #CMT---> Info: calculating dependencies for ../src/SPMTTool.cc
    installation done
    #CMT---> (constituents.make) ElecSimAlg_python done
    #CMT---> Info: calculating dependencies for ../src/MMTriggerToolLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/AbcBoard.cc
    #CMT---> Info: calculating dependencies for ../src/ElecSimSvc.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerToolLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/PMTTool.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerSimAlg.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerToolSpmt.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerHandlerWPLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerVFLToolLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/AbcBoardSvc.cc
    #CMT---> Info: calculating dependencies for ../src/EventKeeper.cc
    #CMT---> Info: calculating dependencies for ../src/AnaAlg.cc
    #CMT---> Info: calculating dependencies for ../src/PMTSimAlg.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerHandlerLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/Trigger.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerToolWPLpmt.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerHandlerSpmt.cc
    #CMT---> Info: calculating dependencies for ../src/ElecSimAlg.cc
    #CMT---> Info: calculating dependencies for ../src/IPMTTool.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerHandlerTT.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerToolTT.cc
    #CMT---> Info: calculating dependencies for ../src/TriggerTT_L1.cc
    #CMT---> compiling ../src/SPMTTool.cc
    #CMT---> compiling ../src/MMTriggerToolLpmt.cc
    #CMT---> compiling ../src/AbcBoard.cc
    #CMT---> compiling ../src/ElecSimSvc.cc
    #CMT---> compiling ../src/TriggerToolLpmt.cc
    #CMT---> compiling ../src/TriggerSimAlg.cc
    #CMT---> compiling ../src/PMTTool.cc
    #CMT---> compiling ../src/TriggerToolSpmt.cc
    #CMT---> compiling ../src/TriggerHandlerWPLpmt.cc
    #CMT---> compiling ../src/TriggerVFLToolLpmt.cc
    #CMT---> compiling ../src/AbcBoardSvc.cc
    #CMT---> compiling ../src/EventKeeper.cc
    #CMT---> compiling ../src/AnaAlg.cc
    #CMT---> compiling ../src/PMTSimAlg.cc
    #CMT---> compiling ../src/TriggerHandlerLpmt.cc
    #CMT---> compiling ../src/TriggerToolWPLpmt.cc
    #CMT---> compiling ../src/Trigger.cc
    #CMT---> compiling ../src/TriggerHandlerSpmt.cc
    #CMT---> compiling ../src/ElecSimAlg.cc
    #CMT---> compiling ../src/IPMTTool.cc
    #CMT---> compiling ../src/TriggerHandlerTT.cc
    #CMT---> compiling ../src/TriggerTT_L1.cc
    #CMT---> compiling ../src/TriggerToolTT.cc
    In file included from ../src/TriggerTT_L1.cc:1:0:
    ../src/TriggerTT_L1.h:35:40: error: 'NULL' was not declared in this scope
       bool HasTrigger(int * trigger_time = NULL);
                                            ^
    gmake[2]: *** [../Linux-x86_64/TriggerTT_L1.o] Error 1
    gmake[2]: *** Waiting for unfinished jobs....
    In file included from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/include/boost/python/exceptio



