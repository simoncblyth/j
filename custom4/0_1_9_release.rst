0_1_9_release
===============






::

    A[blyth@localhost custom4_Debug]$ cd
    A[blyth@localhost ~]$ local_c4_build
    c4_build is a function
    c4_build () 
    { 
        : ~/j/local.sh;
        echo $BASH_SOURCE $FUNCNAME - BUILD NEEDED AS PREFIX IS NOT DEFAULT;
        local ff="local_c4_prefix local_c4_prefix_default";
        for f in $ff;
        do
            printf "%30s : %s\n" "$f" $(eval $f);
        done;
        cd $HOME/customgeant4;
        export CUSTOM4_PREFIX=$(local_c4_prefix);
        ./build_Debug.sh
    }
    A[blyth@localhost ~]$ local_c4_prefix
    /data1/blyth/local/custom4_Debug/0.1.9
    A[blyth@localhost ~]$ c4_build 
    /home/blyth/j/local.sh c4_build - BUILD NEEDED AS PREFIX IS NOT DEFAULT
                   local_c4_prefix : /data1/blyth/local/custom4_Debug/0.1.9
           local_c4_prefix_default : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
                              sdir : /home/blyth/customgeant4 
                              name : customgeant4 
                              BASE : /tmp/blyth/customgeant4 
                              bdir : /tmp/blyth/customgeant4/build_Debug/0.1.9 
                              idir :  
                               arg : info_install_bashrc 
                    OPTICKS_PREFIX :  
                    custom4_prefix : /data1/blyth/local/custom4_Debug/0.1.9 
                    CUSTOM4_PREFIX : /data1/blyth/local/custom4_Debug/0.1.9 
                           VERSION : 0.1.9 
                     VERSION_MAJOR : 0 
                     VERSION_MINOR : 1 
                     VERSION_PATCH : 9 
    /tmp/blyth/customgeant4/build_Debug/0.1.9
    -- The C compiler identification is GNU 11.5.0
    -- The CXX compiler identification is GNU 11.5.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /usr/bin/cc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Custom4_VERBOSE      : YES 
    -- Geant4_FOUND         : 1 
    -- Geant4_VERSION       : 10.4.2 
    -- Geant4_INCLUDE_DIRS  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Xercesc/3.2.4/include 
    -- Geant4_DEFINITIONS   : -DG4_STORE_TRAJECTORY;-DG4VERBOSE;-DG4UI_USE;-DG4VIS_USE;-DG4MULTITHREADED 
    -- Geant4_LIBRARIES     : G4Tree;G4FR;G4GMocren;G4visHepRep;G4RayTracer;G4VRML;G4vis_management;G4modeling;G4interfaces;G4persistency;G4analysis;G4error_propagation;G4readout;G4physicslists;G4run;G4event;G4tracking;G4parmodels;G4processes;G4digits_hits;G4track;G4particles;G4geometry;G4materials;G4graphics_reps;G4intercoms;G4global;G4zlib 
    -- Geant4_BUILD_TYPE    : Release 
    -- Geant4_CXX_FLAGS     : -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 (recommended)
    -- Geant4_CXXSTD        : c++11  (standard used to compile Geant4) 
    -- Geant4_TLS_MODEL     : global-dynamic  (only set if install has multithreading support)
    -- Geant4_INCLUDE_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4  (expected ending: include/Geant4) 
    -- Custom4_GEANT4_PREFIX     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno      (derived from INCLUDE_DIR) 
    -- Custom4_GEANT4_CONFIG_BIN : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config 
    -- Custom4_GEANT4_CFLAGS     : -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic  -DG4MULTITHREADED -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/CLHEP/2.4.7.1/include        (from geant4-config --cflags : with -std=c++11 removed) 
    -- Custom4_GEANT4_LIBRARIES  : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/bin/../lib64 -lG4OpenGL -lG4gl2ps -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/CLHEP/2.4.7.1/lib -lCLHEP-2.4.7.1 -lG4zlib  (from geant4-config --libs) 
    -- Custom4.CMAKE_BUILD_TYPE: Debug 
    -- Custom4.CMAKE_BUILD_TYPE.Debug.ENABLE C4_DEBUG_PIDX 
    -- Configuring done (0.3s)
    -- Generating done (0.0s)
    -- Build files have been written to: /tmp/blyth/customgeant4/build_Debug/0.1.9
    [ 50%] Building CXX object CMakeFiles/Custom4.dir/C4OpBoundaryProcess.cc.o
    [100%] Linking CXX shared library libCustom4.so
    [100%] Built target Custom4
    [100%] Built target Custom4
    Install the project...
    -- Install configuration: "Debug"
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/lib64/libCustom4.so
    -- Set runtime path of "/data1/blyth/local/custom4_Debug/0.1.9/lib64/libCustom4.so" to ""
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4OpBoundaryProcess.hh
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4IPMTAccessor.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4CustomART.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4CustomART_Debug.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4MultiLayrStack.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4Touchable.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4TrackInfo.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4Track.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4Pho.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4GS.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4Sys.h
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/lib64/Custom4-0.1.9/Custom4Config.cmake
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/lib64/Custom4-0.1.9/Custom4ConfigVersion.cmake
    -- Installing: /data1/blyth/local/custom4_Debug/0.1.9/include/Custom4/C4Version.h
    ./build.sh generate_bashrc writing to /data1/blyth/local/custom4_Debug/0.1.9/bashrc
    A[blyth@localhost customgeant4]$ 




