Custom4_dev_setup_on_workstation
===================================

Development via releases and the clumsy junoenv machinery is too painful.
Need something like do on laptop. 

Added::

     build_into_junosw.sh

But need to adapt packages/custom4.sh to not try to download tarballs 
when using untagged versions. HMM: maybe should call the VERSION "head" 
like opticks does.  
Nope that wont work because its a package, just do it manually.


Manual setup of next Custom4 release 0.1.7 on workstation : to facilitate quick updating without releases
------------------------------------------------------------------------------------------------------------

Workflow:

1. laptop: "c4 ; ./rsync_put.sh" sync Custom4 repo from laptop to workstation
2. workstation: "c4 ; ./build_into_junosw.sh" build and install Custom4 into /data/blyth/junotop/ExternalLibs/custom4/VERSION
3. workstation: manually prep the VERSION scripts based on prior VERSION, eg::

    N[blyth@localhost custom4]$ pwd
    /data/blyth/junotop/ExternalLibs/custom4
    N[blyth@localhost custom4]$ cp 0.1.6/bashrc 0.1.7/
    N[blyth@localhost custom4]$ cp 0.1.6/tcshrc 0.1.7/
    N[blyth@localhost custom4]$ perl -pi -e 's/0.1.6/0.1.7/g' 0.1.7/bashrc
    N[blyth@localhost custom4]$ perl -pi -e 's/0.1.6/0.1.7/g' 0.1.7/tcshrc

4. workstation: "jt ; vi bashrc.sh" set the version of Custom4 in jre (juno-runtime-environment) to the next VERSION just installed 




Opticks packages that actually depend on Custom4
--------------------------------------------------

::

    epsilon:opticks blyth$ find . -name CMakeLists.txt -exec grep -l Custom4 {} \;
    ./CSGOptiX/CMakeLists.txt
    ./qudarap/CMakeLists.txt
    ./qudarap/tests/CMakeLists.txt
    ./u4/CMakeLists.txt
    ./u4/tests/CMakeLists.txt
    ./examples/UseCustom4/CMakeLists.txt
    epsilon:opticks blyth$ 


    epsilon:opticks blyth$ om-subs
    okconf
    sysrap
    boostrap
    npy
    optickscore
    ggeo
    extg4
    ana
    analytic
    bin
    CSG
    CSG_GGeo
    GeoChain
    qudarap   ## everything from here needs to be rebuilt 
    gdxml
    u4
    CSGOptiX
    g4cx
    epsilon:opticks blyth$ 


Although dont really need to clean build everything, there 
is not an easy way to clean build from qudarap onwards, so just clean build::

    o
    om-
    om-clean
    om-conf
    oo


bash junoenv libs all custom4 : output as reference for the paths
--------------------------------------------------------------------

::

    === junoenv-external-libs: juno-ext-libs-check-is-reused custom4
    === junoenv-external-libs: juno-ext-libs-all custom4
    ==== juno-ext-libs-get:
    [custom4-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: v0.1.6.tar.gz already exists
    ==== juno-ext-libs-conf:
    [custom4-conf] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6/custom4-build /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [custom4-conf] -- Custom4_VERBOSE      : YES 
    [custom4-conf] -- Geant4_FOUND         : 1 
    [custom4-conf] -- Geant4_VERSION       : 10.4.2 
    [custom4-conf] -- Geant4_INCLUDE_DIRS  : /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4;/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Xercesc/3.2.2/include 
    [custom4-conf] -- Geant4_DEFINITIONS   : -DG4_STORE_TRAJECTORY;-DG4VERBOSE;-DG4UI_USE;-DG4VIS_USE;-DG4MULTITHREADED 
    [custom4-conf] -- Geant4_LIBRARIES     : G4Tree;G4FR;G4GMocren;G4visHepRep;G4RayTracer;G4VRML;G4vis_management;G4modeling;G4interfaces;G4persistency;G4analysis;G4error_propagation;G4readout;G4physicslists;G4run;G4event;G4tracking;G4parmodels;G4processes;G4digits_hits;G4track;G4particles;G4geometry;G4materials;G4graphics_reps;G4intercoms;G4global;G4zlib 
    [custom4-conf] -- Geant4_BUILD_TYPE    : Release 
    [custom4-conf] -- Geant4_CXX_FLAGS     : -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 (recommended)
    [custom4-conf] -- Geant4_CXXSTD        : c++11  (standard used to compile Geant4) 
    [custom4-conf] -- Geant4_TLS_MODEL     : global-dynamic  (only set if install has multithreading support)
    [custom4-conf] -- Geant4_INCLUDE_DIR   : /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4  (expected ending: include/Geant4) 
    [custom4-conf] -- Custom4_GEANT4_PREFIX     : /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno      (derived from INCLUDE_DIR) 
    [custom4-conf] -- Custom4_GEANT4_CONFIG_BIN : /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config 
    [custom4-conf] -- Custom4_GEANT4_CFLAGS     : -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic  -DG4MULTITHREADED -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/include        (from geant4-config --cflags : with -std=c++11 removed) 
    [custom4-conf] -- Custom4_GEANT4_LIBRARIES  : -L/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../lib64 -lG4OpenGL -lG4gl2ps -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -L/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/lib -lCLHEP-2.4.1.0 -lG4zlib  (from geant4-config --libs) 
    [custom4-conf] -- Configuring done
    [custom4-conf] -- Generating done
    [custom4-conf] -- Build files have been written to: /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6/custom4-build
    [custom4-conf] === juno-ext-libs-custom4-conf- CUSTOM4_CMAKE_BUILD_TYPE :
    [custom4-conf] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-make:
    [custom4-make] ===== juno-ext-libs-PKG-make: call juno-ext-libs-custom4-make-
    [custom4-make] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6/custom4-build /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [custom4-make] ===== juno-ext-libs-custom4-make-: make -j48
    [custom4-make] Consolidate compiler generated dependencies of target Custom4
    [custom4-make] [100%] Built target Custom4
    [custom4-make] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-install:
    [custom4-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-custom4-install-
    [custom4-install] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6/custom4-build /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [custom4-install] ===== juno-ext-libs-custom4-install-: make install
    [custom4-install] [100%] Built target Custom4
    [custom4-install] Install the project...
    [custom4-install] -- Install configuration: "Release"
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/lib64/libCustom4.so
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4OpBoundaryProcess.hh
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4IPMTAccessor.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4CustomART.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4CustomART_Debug.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4MultiLayrStack.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4Touchable.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4TrackInfo.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4Track.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4Pho.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4GS.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4Sys.h
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/lib64/Custom4-0.1.6/Custom4Config.cmake
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/lib64/Custom4-0.1.6/Custom4ConfigVersion.cmake
    [custom4-install] -- Up-to-date: /data/blyth/junotop/ExternalLibs/custom4/0.1.6/include/Custom4/C4Version.h
    [custom4-install] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.6 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-setup:
    [custom4-setup] /data/blyth/junotop/ExternalLibs/custom4/0.1.6 /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [custom4-setup] /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 


