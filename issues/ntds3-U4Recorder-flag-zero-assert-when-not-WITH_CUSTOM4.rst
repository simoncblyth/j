FIXED : ntds3-U4Recorder-flag-zero-assert-when-not-WITH_CUSTOM4
=================================================================

Overview
----------

FIXED by adding explicitly "find_package(Custom4 CONFIG)" to Opticks/U4 
as it was impliciting depending on the "j/PMTSim" to find Custom4. 


Issue
-------

Following Opticks stray dependency cleanup and updated Custom4 looks
to be a loss of WITH_CUSTOM4 preprocessor macro 
causing flag zero assert in U4Recorder

In retrospect the onset could have been caused simply by a clean build
without a subsequnent build of j/PMTSim.::


    (gdb) f 4
    #4  0x00007fffd2c8ea57 in U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess> (this=0xb21af0, step=0xad91a0)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:944
    944	    assert( flag > 0 ); 
    (gdb) list
    939	            << " flag " << OpticksPhoton::Flag(flag) 
    940	            ; 
    941	    }
    942	
    943	    LOG_IF(error, flag == 0) << " ERR flag zero : post " << U4StepPoint::Desc<T>(post) ; 
    944	    assert( flag > 0 ); 
    945	
    946	    bool PIDX_DUMP = ulabel.id == PIDX && PIDX_ENABLED ; 
    947	    bool is_fake = false ; 
    948	    unsigned fakemask = 0 ;
    (gdb) 


    (gdb) f 5
    #5  0x00007fffd2c83ca0 in U4Recorder::UserSteppingAction (this=0xb21af0, step=0xad91a0)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:314
    314	     UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(step);
    (gdb) list
    309	#if defined(WITH_CUSTOM4)
    310	     UserSteppingAction_Optical<C4OpBoundaryProcess>(step); 
    311	#elif defined(WITH_PMTSIM)
    312	     UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(step); 
    313	#else
    314	     UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(step);
    315	#endif
    316	}
    317	
    318	
    (gdb) 


Check custom4 setup::

    N[blyth@localhost junotop]$ grep custom4 $JUNOTOP/bashrc.sh 
    source /data/blyth/junotop/ExternalLibs/custom4/0.1.9/bashrc

    N[blyth@localhost junosw]$ echo $CMAKE_PREFIX_PATH  | tr ":" "\n" | grep custom4
    /data/blyth/junotop/ExternalLibs/custom4/0.1.9

::

    N[blyth@localhost junosw]$ jgr WITH_CUSTOM4
    ./cmake/legacy/JUNODependencies.cmake:    set(CUSTOM4_DEFINITIONS ${Custom4_DEFINITIONS})   # -DWITH_CUSTOM4 for compiling
    N[blyth@localhost junosw]$ 


Delete build folder and build again. That shows custom4 is definitely there::

    -- CMAKE_CURRENT_LIST_FILE     : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64/Custom4-0.1.9/Custom4ConfigVersion.cmake    
    -- PACKAGE_VERSION             : 0.1.9            
    -- PACKAGE_VERSION_EXACT       :       
    -- PACKAGE_VERSION_COMPATIBLE  : TRUE 
    -- PACKAGE_VERSION_UNSUITABLE  :  
    -- Custom4_VERBOSE       : ON 
    -- Custom4_FOUND         : YES 
    -- Custom4_VERSION       : 0.1.9 
    -- Custom4_PREFIX        : /data/blyth/junotop/ExternalLibs/custom4/0.1.9 
    -- Custom4_INCLUDE_DIR   : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/include/Custom4 
    -- Custom4_INCLUDE_DIRS  : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/include/Custom4 
    -- Custom4_CFLAGS        : -I/data/blyth/junotop/ExternalLibs/custom4/0.1.9/include/Custom4 
    -- Custom4_DEFINITIONS   : -DWITH_CUSTOM4 
    -- Custom4_LIBRARY_DIR   : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64 
    -- Custom4_LIBRARY_PATH  : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64/Custom4-0.1.9/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64/Custom4-0.1.9 
    -- CUSTOM4_LIBRARIES   : -L/data/blyth/junotop/ExternalLibs/custom4/0.1.9/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/data/blyth/junotop/ExternalLibs/custom4/0.1.9/include/Custom4


HMM. But whats important for U4Recorder 
is it needs to be found for the opticks build.

The use of U4Recorder in js+ok is configured by "--opticks-mode 3"



Clean build Opticks : investigating WITH_CUSTOM4
---------------------------------------------------

::

    o
    om-clean
    om-conf    # HMM u4 seems not finding CUSTOM4


::

    epsilon:opticks blyth$ opticks-fl WITH_CUSTOM4
    ./sysrap/tests/SPMT_test.sh
    ./sysrap/SPMT.h    ## header only so responsibility passes to the .cc that includes SPMT.h

    ./qudarap/QPMT.cc
    ./qudarap/CMakeLists.txt    ## this does find_package(Custom4 CONFIG)
    ./qudarap/qpmt.h
    ./qudarap/tests/QPMT_MockTest.sh
    ./qudarap/tests/QSim_MockTest.sh
    ./qudarap/tests/QPMT_Test.sh
    ./qudarap/tests/QSim_MockTest.cc
    ./qudarap/QPMT.cu
    ./qudarap/QPMT_MOCK.h
    ./qudarap/qsim.h


    ./u4/U4Physics.cc
    ./u4/CMakeLists.txt         ## ADDED EXPLICT find_package(Custom4 CONFIG)
    ./u4/U4OpBoundaryProcess.h
    ./u4/U4Track.h
    ./u4/tests/U4Custom4Test.cc
    ./u4/U4StepPoint.cc
    ./u4/U4Recorder.cc
    ./u4/U4.cc
    ./examples/UseCustom4/UseCustom4.cc


    ./g4cx/G4CXOpticks.cc
    epsilon:opticks blyth$ 



::

    epsilon:junosw blyth$ jgl U4Recorder
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw blyth$ 


U4RecorderAnaMgr
   * instanciates U4Recorder instance and feeds Geant4 objects to it
   * is configured with "--opticks-anamgr" option (HMM --opticks-u4recorder-anamgr would be better)






