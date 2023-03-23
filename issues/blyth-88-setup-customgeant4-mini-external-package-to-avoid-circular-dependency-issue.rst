blyth-88-setup-customgeant4-mini-external-package-to-avoid-circular-dependency-issue
=======================================================================================

* prior :doc:`blyth-88-testing-within-monolith`

Simplest and most extensible Approach is : split off external mini-package CustomGeant4 used by both junosw and opticks
-------------------------------------------------------------------------------------------------------------------------


::

    CustomG4OpBoundaryProcess.hh
    CustomG4OpBoundaryProcess.cc
    CustomART.h
    CustomART_Debug.h   ## currently inside PMTSIM_STANDALONE : probably need to bring that out 

Arhh CustomART.h currently includes::

     72 #include "G4ThreeVector.hh"

     73 #include "PMTSimParamSvc/IPMTAccessor.h"
     // protocol header, no includes 

     74 #include "MultiLayrStack.h"     
     // only standard includes

     75 #include "SimUtil/S4Touchable.h"
     // utility only standard and Geant4 includes

     77 #ifdef PMTSIM_STANDALONE
     78 #include "SLOG.hh"
     79 #include "CustomART_Debug.h"
     80 #endif


Collecting everything into https://github.com/simoncblyth/customgeant4 with C4 prefix. 

::

    git clone git@github.com:simoncblyth/customgeant4.git 


* https://github.com/simoncblyth/customgeant4


junoenv machinery to build/install C4 
---------------------------------------

::

    epsilon:customgeant4 blyth$ je
    /Users/blyth/junotop/junoenv
    epsilon:junoenv blyth$ put.sh 
    scp /Users/blyth/junotop/junoenv/packages/customgeant4.sh P:junotop/junoenv/packages/customgeant4.sh
    epsilon:junoenv blyth$ 

::

    bash junoenv libs get customgeant4


    bash junoenv libs

    * all
    * get
    * conf
    * make
    * install
    * setup
    * reuse
    * list
    * vlist


Need to work out how the vlist version sets works::

    N[blyth@localhost junoenv]$ bash junoenv libs all customgeant4
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop
    == setup-juno-basic-preq: $JUNO_EXTLIB_COLLECTION: ""
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
    == setup-juno-basic-preq: ================================================================
    == setup-juno-external-libs
    === junoenv-external-libs: command: all
    === junoenv-external-libs: packages: customgeant4
    === junoenv-external-libs: create function juno-ext-libs-customgeant4-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init customgeant4
    ==== juno-ext-libs-check-init: setup dependencies for customgeant4
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup customgeant4: create function juno-ext-libs-customgeant4-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup customgeant4: source /data/blyth/junotop/junoenv/packages/customgeant4.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup customgeant4: After source: customgeant4
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup geant4: create function juno-ext-libs-geant4-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup geant4: source /data/blyth/junotop/junoenv/packages/geant4.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup geant4: After source: geant4
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: After source: python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: status: 0 python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: can not find /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    ==== juno-ext-libs-dependencies-setup-rec-impl: ### setup python: Please install python first.
    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Python/
    total 4
    4 drwxrwxr-x. 37 blyth blyth 4096 Sep 27 19:18 ..
    0 drwxrwxr-x.  2 blyth blyth   20 Sep 27 17:05 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Sep 27 17:05 3.8.12 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Python/3.8.12
    N[blyth@localhost junoenv]$ 


Aside while working out how to use the old vlist collection
-----------------------------------------------------------------

Looking for python that isnt there, need to use the vlist collections::

    N[blyth@localhost junoenv]$ cd collections/
    N[blyth@localhost collections]$ l
    total 12
    4 drwxrwxr-x. 11 blyth blyth 4096 Sep 28 21:30 ..
    0 drwxrwxr-x.  2 blyth blyth   36 Sep 27 17:05 .
    4 -rw-rw-r--.  1 blyth blyth 2062 Sep 27 17:05 22.1.sh
    4 -rw-rw-r--.  1 blyth blyth 2063 Sep 27 17:05 22.2.sh
    N[blyth@localhost collections]$ cat 22.1.sh
    function juno-ext-libs-git-version- { echo 2.34.1 ; } 


    N[blyth@localhost collections]$ grep python-version *.sh
    22.1.sh:function juno-ext-libs-python-version- { echo 3.8.12 ; } 
    22.2.sh:function juno-ext-libs-python-version- { echo 3.9.14 ; } 

::

    287 jx-extlib-collection()
    288 {
    289    local ccbase=$(jx-ccbase)
    290    local collection
    291    case $ccbase in
    292        /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) collection=22.1  ;;  
    293        /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120) collection=22.2 ;;
    294    esac
    295    export JUNO_EXTLIB_COLLECTION=$JUNOTOP/junoenv/collections/$collection.sh
    296 }
    297 

    epsilon:junoenv blyth$ find . -type f -exec grep -H COLLECTION {} \;
    ./junoenv:    echo $msg \$JUNO_EXTLIB_COLLECTION: \"$JUNO_EXTLIB_COLLECTION\"
    ./junoenv:    if [ -n "$JUNO_EXTLIB_COLLECTION" ]; then
    ./junoenv:        echo $msg "Loading EXTLIB versions from $JUNO_EXTLIB_COLLECTION"
    ./junoenv:        if [ ! -f "$JUNO_EXTLIB_COLLECTION" ]; then
    ./junoenv:            echo $msg "Can't find JUNO_EXTLIB_COLLECTION: $JUNO_EXTLIB_COLLECTION"
    ./junoenv:        source $JUNO_EXTLIB_COLLECTION
    epsilon:junoenv blyth$ 


    ## HMM: SHOULD DO THE BELOW WHERE JUNOTOP IS SET

    export JUNO_EXTLIB_COLLECTION=$JUNOTOP/junoenv/collections/22.1.sh 

::

     37 # ~/.bashrc
     38 export JUNOTOP=/data/$USER/junotop
     39 export JUNO_EXTLIB_COLLECTION=$JUNOTOP/junoenv/collections/22.1.sh   ## config old set of versions for junoenv to use
     40 



That succeeds to grab but some errors::

    N[blyth@localhost junoenv]$ bash junoenv libs all customgeant4

    [customgeant4-conf] -- Geant4_FOUND   : 1 
    [customgeant4-conf] -- Geant4_VERSION : 10.4.2 
    [customgeant4-conf] -- Geant4_LIBRARIES : G4Tree;G4FR;G4GMocren;G4visHepRep;G4RayTracer;G4VRML;G4vis_management;G4modeling;G4interfaces;G4persistency;G4analysis;G4error_propagation;G4readout;G4physicslists;G4run;G4event;G4tracking;G4parmodels;G4processes;G4digits_hits;G4track;G4particles;G4geometry;G4materials;G4graphics_reps;G4intercoms;G4global;G4zlib 
    [customgeant4-conf] -- Geant4_INCLUDE_DIR : /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4 
    [customgeant4-conf] -- Configuring done
    [customgeant4-conf] -- Generating done
    [customgeant4-conf] -- Build files have been written to: /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1/customgeant4-build
    [customgeant4-conf] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-make:
    [customgeant4-make] ===== juno-ext-libs-PKG-make: call default
    [customgeant4-make] ===== juno-ext-libs-PKG-make: make -j48
    [customgeant4-make] make: *** No targets specified and no makefile found.  Stop.
    ==== juno-ext-libs-install:
    [customgeant4-install] ===== juno-ext-libs-PKG-install: call default
    [customgeant4-install] ===== juno-ext-libs-PKG-install: make install
    [customgeant4-install] make: *** No rule to make target `install'.  Stop.
    ==== juno-ext-libs-setup:
    [customgeant4-setup] /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1 /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [customgeant4-setup] /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 



    N[blyth@localhost junoenv]$ bash junoenv libs conf customgeant4     ## get/conf

    ## get,conf ok make,install have no targets 




    * all
    * get
    * conf
    * make
    * install
    * setup
    * reuse
    * list
    * vlist


make TLS mismatch
-------------------


::

    N[blyth@localhost junoenv]$ bash junoenv libs make customgeant4


    [customgeant4-make] ===== juno-ext-libs-PKG-make: call juno-ext-libs-customgeant4-make-
    [customgeant4-make] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1/customgeant4-build /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [customgeant4-make] ===== juno-ext-libs-customgeant4-make-: make -j48
    [customgeant4-make] [ 25%] Building CXX object CMakeFiles/C4.dir/C4OpBoundaryProcess.cc.o
    [customgeant4-make] [ 50%] Linking CXX shared library libC4.so
    [customgeant4-make] [ 50%] Built target C4
    [customgeant4-make] [ 75%] Building CXX object tests/CMakeFiles/C4OpBoundaryProcessTest.dir/C4OpBoundaryProcessTest.cc.o
    [customgeant4-make] [100%] Linking CXX executable C4OpBoundaryProcessTest
    [customgeant4-make] /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bin/ld: aTrackAllocator: TLS reference in /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so mismatches non-TLS reference in CMakeFiles/C4OpBoundaryProcessTest.dir/C4OpBoundaryProcessTest.cc.o
    [customgeant4-make] /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so: error adding symbols: Bad value
    [customgeant4-make] collect2: error: ld returned 1 exit status
    [customgeant4-make] make[2]: *** [tests/C4OpBoundaryProcessTest] Error 1
    [customgeant4-make] make[1]: *** [tests/CMakeFiles/C4OpBoundaryProcessTest.dir/all] Error 2
    [customgeant4-make] make: *** [all] Error 2
    [customgeant4-make] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 



* https://stackoverflow.com/questions/26257063/g4py-building-errors-with-tls-reference

::

    -DGEANT4_BUILD_MULTITHREADED=OFF



Some of the geant4 config needs to match::

    141 function juno-ext-libs-geant4-conf-10 {
    142     local msg="===== $FUNCNAME: "
    143     cmake .. \
    144         -DCMAKE_BUILD_TYPE=$(juno-ext-libs-geant4-buildtype) \
    145         -DCMAKE_INSTALL_PREFIX=$(juno-ext-libs-geant4-install-dir) \
    146         -DGEANT4_USE_GDML=ON \
    147         -DGEANT4_INSTALL_DATA=ON \
    148         -DGEANT4_USE_OPENGL_X11=ON \
    149         -DGEANT4_USE_RAYTRACER_X11=ON \
    150         -DGEANT4_BUILD_MULTITHREADED=ON \
    151         -DGEANT4_BUILD_TLS_MODEL=global-dynamic \
    152         -DXERCESC_ROOT_DIR=$(juno-ext-libs-xercesc-install-dir) \
    153         -DGEANT4_USE_SYSTEM_CLHEP=ON
    154 
    155 

Tried adding some of those, but get::

    [customgeant4-conf] CMake Warning:
    [customgeant4-conf]   Manually-specified variables were not used by the project:
    [customgeant4-conf] 
    [customgeant4-conf]     GEANT4_BUILD_MULTITHREADED
    [customgeant4-conf]     GEANT4_BUILD_TLS_MODEL
    [customgeant4-conf] 
    [customgeant4-conf] 


And the make TLS error is just the same::


    [customgeant4-make] 
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bin/ld: aTrackAllocator: TLS reference in /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so mismatches non-TLS reference in CMakeFiles/C4OpBoundaryProcessTest.dir/C4OpBoundaryProcessTest.cc.o
    [customgeant4-make] /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so: error adding symbols: Bad value
    [customgeant4-make] collect2: error: ld returned 1 exit status



::

    epsilon:junoenv blyth$ g4-cc aTrackAllocator
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/track/src/G4Track.cc:G4ThreadLocal G4Allocator<G4Track> *aTrackAllocator = 0;
    epsilon:junoenv blyth$ 


g4-cls G4Track # in icc and cc::

     34 extern G4TRACK_DLL G4ThreadLocal G4Allocator<G4Track> *aTrackAllocator;

     52 G4ThreadLocal G4Allocator<G4Track> *aTrackAllocator = 0;



g4-cls tls::

     36 #if defined (G4MULTITHREADED)
     37   #if ( defined(__MACH__) && defined(__clang__) && defined(__x86_64__) ) || \
     38       ( defined(__linux__) && defined(__clang__) )
     39     #if (defined (G4USE_STD11) && __has_feature(cxx_thread_local))
     40       #  define G4ThreadLocalStatic static thread_local
     41       #  define G4ThreadLocal thread_local
     42     #else
     43       #  define G4ThreadLocalStatic static __thread
     44       #  define G4ThreadLocal __thread
     45     #endif
     46   #elif ( (defined(__linux__) || defined(__MACH__)) && \
     47           !defined(__INTEL_COMPILER) && defined(__GNUC__) && (__GNUC__>=4 && __GNUC_MINOR__<9))
     48     #if defined (G4USE_STD11)
     49       #  define G4ThreadLocalStatic static __thread
     50       #  define G4ThreadLocal thread_local
     51     #else
     52       #  define G4ThreadLocalStatic static __thread
     53       #  define G4ThreadLocal __thread
     54     #endif
     ..
     87 #else
     88   #  define G4ThreadLocalStatic static
     89   #  define G4ThreadLocal 
     90 #endif




laptop::

    psilon:issues blyth$ which geant4-config
    /usr/local/opticks_externals/g4_1042/bin/geant4-config
    epsilon:issues blyth$ geant4-config
    Usage: geant4-config [--prefix] [--version] [--libs] [--cflags]
    epsilon:issues blyth$ geant4-config --version
    10.4.2
    epsilon:issues blyth$ geant4-config --prefix
    /usr/local/opticks_externals/g4_1042/bin/..
    epsilon:issues blyth$ geant4-config --libs
    -L/usr/local/opticks_externals/g4_1042/bin/../lib -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -L/usr/local/opticks_externals/clhep/lib -lCLHEP-2.4.1.0 -lG4zlib
    epsilon:issues blyth$ geant4-config --cflags
    -DG4UI_USE_TCSH -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -Qunused-arguments -stdlib=libc++ -DG4USE_STD11 -std=c++11 -I/usr/local/opticks_externals/g4_1042/bin/../include/Geant4 -I/usr/local/opticks_externals/clhep/include -I/usr/local/opticks_externals/xercesc/include
    epsilon:issues blyth$ 


workstation::

    N[blyth@localhost ~]$ jre
    === jx-runtime-env-:
    === jx-runtime-env-:
    /data/blyth/junotop/junosw
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up to date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    nothing to commit, working tree clean
    N[blyth@localhost junosw]$ which geant4-config
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    N[blyth@localhost junosw]$ 

    N[blyth@localhost junosw]$ geant4-config --cflags
    -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/include
    N[blyth@localhost junosw]$ 


So add "-DG4MULTITHREADED=ON" to package/customgeant4.sh but that gives::

    [customgeant4-conf] CMake Warning:
    [customgeant4-conf]   Manually-specified variables were not used by the project:
    [customgeant4-conf] 
    [customgeant4-conf]     G4MULTITHREADED
    [customgeant4-conf] 

And make gives the same error::

    N[blyth@localhost junoenv]$ bash junoenv libs make customgeant4
    ...

    [customgeant4-make] Consolidate compiler generated dependencies of target C4OpBoundaryProcessTest
    [customgeant4-make] [ 75%] Linking CXX executable C4OpBoundaryProcessTest
    [customgeant4-make] /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bin/ld: aTrackAllocator: TLS reference in /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so mismatches non-TLS reference in CMakeFiles/C4OpBoundaryProcessTest.dir/C4OpBoundaryProcessTest.cc.o
    [customgeant4-make] /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so: error adding symbols: Bad value
    [customgeant4-make] collect2: error: ld returned 1 exit status
    [customgeant4-make] make[2]: *** [tests/C4OpBoundaryProcessTest] Error 1
    [customgeant4-make] make[1]: *** [tests/CMakeFiles/C4OpBoundaryProcessTest.dir/all] Error 2
    [customgeant4-make] make: *** [all] Error 2


NEXT : Try to reproduce this error outside of junoenv 
--------------------------------------------------------

Arghh github ssh and https not working::

    N[blyth@localhost junoenv]$ cd
    N[blyth@localhost ~]$ git clone git@github.com:simoncblyth/customgeant4.git 
    Cloning into 'customgeant4'...
    ssh_exchange_identification: Connection closed by remote host
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    N[blyth@localhost ~]$ 

    N[blyth@localhost ~]$ git clone https://github.com/simoncblyth/customgeant4.git
    Cloning into 'customgeant4'...
    ^C
    N[blyth@localhost ~]$ 


Next day try again, and it works::

    N[blyth@localhost ~]$ git clone git@github.com:simoncblyth/customgeant4.git 
    Cloning into 'customgeant4'...
    remote: Enumerating objects: 52, done.
    remote: Counting objects: 100% (52/52), done.
    remote: Compressing objects: 100% (42/42), done.
    remote: Total 52 (delta 10), reused 46 (delta 7), pack-reused 0
    Receiving objects: 100% (52/52), 42.12 KiB | 0 bytes/s, done.
    Resolving deltas: 100% (10/10), done.
    N[blyth@localhost ~]$ 
    N[blyth@localhost ~]$ 




No connection to github : so Just edit in build dir 
-----------------------------------------------------


::

    N[blyth@localhost junotop]$ find . -name C4OpBoundaryProcess.hh
    ./ExternalLibs/Build/customgeant4-0.0.1/C4OpBoundaryProcess.hh

    N[blyth@localhost customgeant4-0.0.1]$ pwd
    /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1
    N[blyth@localhost customgeant4-0.0.1]$ l
    total 160
     0 drwxrwxr-x. 4 blyth blyth   118 Mar 23 00:54 customgeant4-build
     4 drwxrwxr-x. 4 blyth blyth  4096 Mar 22 23:16 .
     0 drwxrwxr-x. 3 blyth blyth    53 Mar 22 23:16 ..
     4 -rwxrwxr-x. 1 blyth blyth   904 Mar 22 21:18 build.sh
     4 -rw-rw-r--. 1 blyth blyth   269 Mar 22 21:18 C4CustomART_Debug.h
    16 -rw-rw-r--. 1 blyth blyth 14515 Mar 22 21:18 C4CustomART.h
     4 -rw-rw-r--. 1 blyth blyth   453 Mar 22 21:18 C4IPMTAccessor.h
    24 -rw-rw-r--. 1 blyth blyth 23870 Mar 22 21:18 C4MultiLayrStack.h
    60 -rw-rw-r--. 1 blyth blyth 61144 Mar 22 21:18 C4OpBoundaryProcess.cc
    16 -rw-rw-r--. 1 blyth blyth 12496 Mar 22 21:18 C4OpBoundaryProcess.hh
     8 -rw-rw-r--. 1 blyth blyth  4849 Mar 22 21:18 C4Touchable.h
     4 -rw-rw-r--. 1 blyth blyth  1270 Mar 22 21:18 CMakeLists.txt
     4 -rw-rw-r--. 1 blyth blyth   270 Mar 22 21:18 .gitignore
    12 -rw-rw-r--. 1 blyth blyth 11357 Mar 22 21:18 LICENSE
     0 drwxrwxr-x. 2 blyth blyth    96 Mar 22 21:18 tests
    N[blyth@localhost customgeant4-0.0.1]$ 

    N[blyth@localhost junoenv]$ bash junoenv libs conf customgeant4

After commenting "add_subdir(tests)" the "conf", "make", "install" all work::

    [customgeant4-install] [100%] Built target C4
    [customgeant4-install] Install the project...
    [customgeant4-install] -- Install configuration: ""
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/lib/libC4.so
    [customgeant4-install] -- Set runtime path of "/data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/lib/libC4.so" to ""
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4OpBoundaryProcess.hh
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4IPMTAccessor.h
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4CustomART.h
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4CustomART_Debug.h
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4MultiLayrStack.h
    [customgeant4-install] -- Installing: /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/C4Touchable.h
    [customgeant4-install] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.1 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 


 
"all" runs (doing: "get" "conf" "make" "install" "setup") maybe "setup" is doing nothing::

    ==== juno-ext-libs-setup:
    [customgeant4-setup] /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1 /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [customgeant4-setup] /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 


::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/
    total 8
    4 -rw-rw-r--. 1 blyth blyth 1501 Mar 23 01:15 tcshrc
    4 -rw-rw-r--. 1 blyth blyth 1088 Mar 23 01:15 bashrc
    0 drwxrwxr-x. 3 blyth blyth   16 Mar 23 01:13 include
    0 drwxrwxr-x. 4 blyth blyth   60 Mar 23 01:13 .
    0 drwxrwxr-x. 2 blyth blyth   22 Mar 23 01:13 lib
    0 drwxrwxr-x. 3 blyth blyth   19 Mar 22 23:16 ..
    N[blyth@localhost junoenv]$ 


Maybe the default setup is ok::

    N[blyth@localhost junoenv]$ cat /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/bashrc
    if [ -z "${JUNOTOP}" ]; then
    export JUNO_EXTLIB_customgeant4_HOME=/data/blyth/junotop/ExternalLibs/customgeant4/0.0.1
    else
    export JUNO_EXTLIB_customgeant4_HOME=${JUNOTOP}/ExternalLibs/customgeant4/0.0.1
    fi

    export PATH=${JUNO_EXTLIB_customgeant4_HOME}/bin:${PATH}
    if [ -d ${JUNO_EXTLIB_customgeant4_HOME}/lib ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_customgeant4_HOME}/lib:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_customgeant4_HOME}/lib/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_customgeant4_HOME}/lib/pkgconfig:${PKG_CONFIG_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_customgeant4_HOME}/lib64 ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_customgeant4_HOME}/lib64:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_customgeant4_HOME}/lib64/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_customgeant4_HOME}/lib64/pkgconfig:${PKG_CONFIG_PATH}
    fi
    export CPATH=${JUNO_EXTLIB_customgeant4_HOME}/include:${CPATH}
    export MANPATH=${JUNO_EXTLIB_customgeant4_HOME}/share/man:${MANPATH}

    # For CMake search path
    export CMAKE_PREFIX_PATH=${JUNO_EXTLIB_customgeant4_HOME}:${CMAKE_PREFIX_PATH}
    N[blyth@localhost junoenv]$ 



::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/lib/
    total 132
      0 drwxrwxr-x. 4 blyth blyth     60 Mar 23 01:13 ..
      0 drwxrwxr-x. 2 blyth blyth     22 Mar 23 01:13 .
    132 -rwxr-xr-x. 1 blyth blyth 132152 Mar 22 23:28 libC4.so
    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/
    total 0
    0 drwxrwxr-x. 2 blyth blyth 155 Mar 23 01:13 C4
    0 drwxrwxr-x. 3 blyth blyth  16 Mar 23 01:13 .
    0 drwxrwxr-x. 4 blyth blyth  60 Mar 23 01:13 ..
    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/include/C4/
    total 72
     0 drwxrwxr-x. 2 blyth blyth   155 Mar 23 01:13 .
     0 drwxrwxr-x. 3 blyth blyth    16 Mar 23 01:13 ..
     4 -rw-r--r--. 1 blyth blyth   269 Mar 22 21:18 C4CustomART_Debug.h
    16 -rw-r--r--. 1 blyth blyth 14515 Mar 22 21:18 C4CustomART.h
     4 -rw-r--r--. 1 blyth blyth   453 Mar 22 21:18 C4IPMTAccessor.h
    24 -rw-r--r--. 1 blyth blyth 23870 Mar 22 21:18 C4MultiLayrStack.h
    16 -rw-r--r--. 1 blyth blyth 12496 Mar 22 21:18 C4OpBoundaryProcess.hh
     8 -rw-r--r--. 1 blyth blyth  4849 Mar 22 21:18 C4Touchable.h
    N[blyth@localhost junoenv]$ 



HMM should the includes use the prefix ? Could eliminate the C4 prefix ? 

Geant4 uses prefix "Geant4", so keep the C4::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/
    total 17110
    137 drwxr-xr-x.  3 cvmfs cvmfs 139264 Mar  4  2022 .
      6 -rw-r--r--.  1 cvmfs cvmfs   5185 Mar  4  2022 G4AdjointAlongStepWeightCorrection.hh
      5 -rw-r--r--.  1 cvmfs cvmfs   5117 Mar  4  2022 G4AdjointForcedInteractionForGamma.hh
      8 -rw-r--r--.  1 cvmfs cvmfs   7373 Mar  4  2022 G4AdjointProcessEquivalentToDirectProcess.hh
      4 -rw-r--r--.  1 cvmfs cvmfs   3407 Mar  4  2022 G4BremsstrahlungCrossSectionHandler.hh
      3 -rw-r--r--.  1 cvmfs cvmfs   2840 Mar  4  2022 G4CameronGilbertPairingCorrections.hh





HMM resetup skips opticks and does not include customgeant4
---------------------------------------------------------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation

To update the $JUNOTOP/bashrc need to "bash junoenv env resetup" 

BUT thats skipping opticks::

   N[blyth@localhost junotop]$ cp bashrc.sh bashrc_keep.sh
   N[blyth@localhost junoenv]$ bash junoenv env resetup

    N[blyth@localhost junotop]$ diff bashrc_keep.sh bashrc.sh
    38d37
    < source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Tue Sep 27 19:24:34 CST 2022
    N[blyth@localhost junotop]$ vimdiff bashrc_keep.sh bashrc.sh
    2 files to edit
    N[blyth@localhost junotop]$ 


YEP: after a resetup would need to "bash junoenv opticks hookup" 
BUT customgeant4 must work without opticks anyhow.

So add "customgeant4" to junoenv-external-libs.sh after geant4::

    N[blyth@localhost junoenv]$ git status
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   junoenv-external-libs.sh

    Untracked files:
      (use "git add <file>..." to include in what will be committed)
        logs/
        packages/customgeant4.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junoenv]$ git diff junoenv-external-libs.sh
    diff --git a/junoenv-external-libs.sh b/junoenv-external-libs.sh
    index c7b3d2b..c6856c1 100644
    --- a/junoenv-external-libs.sh
    +++ b/junoenv-external-libs.sh
    @@ -936,6 +936,8 @@ function junoenv-external-libs-list {
         echo ROOT # hep
         echo hepmc  # simulation
         echo geant4 # simulation
    +    echo customgeant4 # simulation
    +
         echo genie # generator
         echo nuwro # generator
         echo talys # generator
    N[blyth@localhost junoenv]$ 


::

    N[blyth@localhost junotop]$ diff bashrc_keep.sh bashrc.sh
    31a32
    > source /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1/bashrc
    38d38
    < source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Tue Sep 27 19:24:34 CST 2022
    N[blyth@localhost junotop]$ 


Next need to try to use C4 from PhysiSim
-------------------------------------------

Where is Geant4 found and hooked up at CMake level.

cmake/JUNODependencies.cmake::

    ## CLHEP
    include_directories($ENV{JUNO_EXTLIB_CLHEP_HOME}/include)
    find_library(CLHEP_LIBRARIES CLHEP 
        HINTS $ENV{JUNO_EXTLIB_CLHEP_HOME}/lib
    )
    link_directories($ENV{JUNO_EXTLIB_CLHEP_HOME}/lib)

    ## Geant4
    find_package(Geant4 REQUIRED ui_all vis_all)                        ## this defines some vars that are overwritten below
    include_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/include/geant4)   ## case error : should be include/Geant4
    find_program(GEANT4_CONFIG_EXECUTABLE geant4-config
        PATHS $ENV{JUNO_EXTLIB_Geant4_HOME}/bin)
    execute_process(
        COMMAND ${GEANT4_CONFIG_EXECUTABLE} --cflags
        OUTPUT_VARIABLE GEANT4_CFLAGS                                   ## the cflags has the correct include directory 
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    # remove c++11 from command line
    string(REPLACE "-std=c++11" "" GEANT4_CFLAGS ${GEANT4_CFLAGS})
    message("testing GEANT4_CFLAGS... ${GEANT4_CFLAGS}")
    add_definitions(${GEANT4_CFLAGS})

    execute_process(
        COMMAND ${GEANT4_CONFIG_EXECUTABLE} --libs
        OUTPUT_VARIABLE GEANT4_LIBRARIES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    link_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/lib)               ## non-existing directory : should be lib64



The GEANT4_LIBRARIES has the correct libdir::

    N[blyth@localhost junotop]$ geant4-config --libs
    -L/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../lib64 -lG4OpenGL -lG4gl2ps -lG4Tree -lG4FR -lG4GMocren -lG4visHepRep -lG4RayTracer -lG4VRML -lG4vis_management -lG4modeling -lG4interfaces -lG4persistency -lG4analysis -lG4error_propagation -lG4readout -lG4physicslists -lG4run -lG4event -lG4tracking -lG4parmodels -lG4processes -lG4digits_hits -lG4track -lG4particles -lG4geometry -lG4materials -lG4graphics_reps -lG4intercoms -lG4global -L/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/lib -lCLHEP-2.4.1.0 -lG4zlib
    N[blyth@localhost junotop]$ 


/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bashrc::

    export JUNO_EXTLIB_Geant4_HOME=${JUNOTOP}/ExternalLibs/Geant4/10.04.p02.juno

Notice wrong case the include dir is capitalized::

     ${JUNOTOP}/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/

But the cflags has the correct include dir::

    N[blyth@localhost junotop]$ which geant4-config
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    N[blyth@localhost junotop]$ geant4-config --cflags
    -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/CLHEP/2.4.1.0/include
    N[blyth@localhost junotop]$ 



N[blyth@localhost junotop]$ l ${JUNOTOP}/ExternalLibs/Geant4/10.04.p02.juno/lib64/
total 50661
    1 drwxr-xr-x. 6 cvmfs cvmfs      114 Mar  4  2022 ..
    5 drwxr-xr-x. 4 cvmfs cvmfs     4096 Mar  4  2022 .
  287 -rwxr-xr-x. 1 cvmfs cvmfs   293200 Mar  4  2022 libG4error_propagation.so
 1169 -rwxr-xr-x. 1 cvmfs cvmfs  1196808 Mar  4  2022 libG4vis_management.so
    1 drwxr-xr-x. 3 cvmfs cvmfs      207 Mar  4  2022 Geant4-10.4.2
 5318 -rwxr-xr-x. 1 cvmfs cvmfs  5445056 Mar  4  2022 libG4analysis.so
  889 -rwxr-xr-x. 1 cvmfs cvmfs   909600 Mar  4  2022 libG4digits_hits.so
  562 -rwxr-xr-x. 1 cvmfs cvmfs   575304 Mar  4  2022 libG4event.so
  106 -rwxr-xr-x. 1 cvmfs cvmfs   108064 Mar  4  2022 libG4FR.so





Note that find_package Geant4 sets via lib64/Geant4-10.4.2/Geant4Config.cmake
the variables::

    Geant4_INCLUDE_DIRS
    Geant4_DEFINITIONS
    Geant4_LIBRARIES


HMM:

1. Geant4 target created by find_package seems not to be used. 
2. This is using very old non-target-based CMake style, piling up::

   include_directories
   link_directories
   add_definitions 


The PKG depends lists lib names OR package names it seems::

    epsilon:junosw blyth$ find . -name CMakeLists.txt -exec grep -H G4 {} \;
    ./Simulation/GenTools/CMakeLists.txt:        G4geometry
    ...
    ./Simulation/DetSimV2/CMakeLists.txt:add_subdirectory(G4Svc)
    ./Simulation/DetSimV2/DetSimAlg/CMakeLists.txt:        G4Svc
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:PKG (G4Svc
    ./Generator/NuSolGen/CMakeLists.txt:        G4particles
    ./Generator/GenGenie/CMakeLists.txt:        G4geometry
    ./Generator/GenGenie/CMakeLists.txt:        ${LOG4CPP_LIBRARIES}
    epsilon:junosw blyth$ 



::

      1 include (PKG)
      2 PKG (G4Svc
      3     DEPENDS
      4         ${GEANT4_LIBRARIES}
      5 )


Simulation/DetSimV2/CMakeLists.txt::

     01 # The order could be necessary
      2 
      3 add_subdirectory(G4Svc)              ## DEPENDS ${GEANT4_LIBRARIES} 
      4 add_subdirectory(DetSimAlg)          ## DEPENDS G4Svc
      5 add_subdirectory(SimUtil)            ## DEPENDS DetSimAlg Geometry SimEvent MCParamsSvc
      6 add_subdirectory(MCGlobalTimeSvc)    ## DEPENDS CLHEP
      7 add_subdirectory(MCParamsSvc)        ## DEPENDS Boost::filesystem Boost::system Rest ParaDB DBISvc dbi DatabaseSvc
      8 add_subdirectory(PMTSim)             ## DEPENDS SimUtil IPMTSimParamSvc Geometry MultiFilmSimSvc MCParamsSvc GenTools EGet "Opticks"
      9 add_subdirectory(PhysiSim)           ## DEPENDS DetSimAlg MCParamsSvc IPMTSimParamSvc PMTSimParamSvc SimUtil EGet "Opticks"
     10 add_subdirectory(OPSimulator)        ## DEPENDS DetSimAlg PhysiSim SimUtil
     11 add_subdirectory(VoxelMethod)        
     12 
     13 
     14 # Detector Geometry Related
     15 add_subdirectory(CalibUnit)
     16 add_subdirectory(CentralDetector)
     17 add_subdirectory(Chimney)
     18 add_subdirectory(TopTracker)
     19 
     20 
     21 # Applications
     22 add_subdirectory(AnalysisCode)
     23 add_subdirectory(DetSimOptions)
     24 
     25 
     26 # Multi-threading
     27 add_subdirectory(DetSimMT)
     28 add_subdirectory(DetSimMTUtil)

So the Geant4 dependeny is not via a target, its by naming libs via 
a chain of deps starting from "geant4-config --libs" output 
gathered by CMake::

     82 execute_process(
     83     COMMAND ${GEANT4_CONFIG_EXECUTABLE} --libs
     84     OUTPUT_VARIABLE GEANT4_LIBRARIES
     85     OUTPUT_STRIP_TRAILING_WHITESPACE
     86 )
     87 link_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/lib)


::
     
    090 
     91 if (DEFINED ENV{JUNO_EXTLIB_customgeant4_HOME})
     92    include_directories($ENV{JUNO_EXTLIB_customgeant4_HOME}/include/C4)
     93    link_directories($ENV{JUNO_EXTLIB_customgeant4_HOME}/lib)
     94    set(customgeant4_LIBRARIES C4)
     95    message(STATUS "${CMAKE_CURRENT_LIST_FILE} : configuring customgeant4 " )
     96 else()
     97    set(customgeant4_LIBRARIES)
     98    message(STATUS "${CMAKE_CURRENT_LIST_FILE} : NOT-configuring customgeant4 " )
     99 endif()


::

    epsilon:junosw blyth$ find . -name CMakeLists.txt -exec grep -H LIBRARIES {} \;
    ./Database/FrontierSvc/CMakeLists.txt:        ${FRONTIER_LIBRARIES}
    ./Database/dbi/CMakeLists.txt:        ${MYSQL_CONNECTOR_CPP_LIBRARIES}
    ./Database/dbi/CMakeLists.txt:        ${MYSQL_CONNECTOR_C_LIBRARIES}
    ./Database/dbi/CMakeLists.txt:	${SQLite3_LIBRARIES}
    ./Database/DatabaseSvc/CMakeLists.txt:        ${MYSQL_CONNECTOR_CPP_LIBRARIES}
    ./Database/DatabaseSvc/CMakeLists.txt:        ${MYSQL_CONNECTOR_C_LIBRARIES}
    ./EventDisplay/VisClient/CMakeLists.txt:#    ${ROOT_LIBRARIES}
    ./EventDisplay/VisClient/CMakeLists.txt:#    ${CLHEP_LIBRARIES}
    ./Simulation/GenDecay/CMakeLists.txt:find_library(MORE_LIBRARIES more
    ./Simulation/DetSimV2/DetSimOptions/CMakeLists.txt:        ${GEANT4_LIBRARIES}
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:        ${GEANT4_LIBRARIES}
    ./CommonSvc/RandomSvc/CMakeLists.txt:#    ${SNIPERKERNEL_LIBRARIES}
    ./CommonSvc/RandomSvc/CMakeLists.txt:#    ${ROOT_LIBRARIES}
    ./Generator/UnifiedGen/CommonXSec/CMakeLists.txt:        ${YAML_LIBRARIES}
    ./Generator/GenGenie/CMakeLists.txt:        ${GENIE_LIBRARIES}
    ./Generator/GenGenie/CMakeLists.txt:        ${LOG4CPP_LIBRARIES}
    ./Utilities/Rest/CMakeLists.txt:        ${CURL_LIBRARIES}
    ./Detector/Parameter/CMakeLists.txt:        ${GEANT4_LIBRARIES}
    ./Examples/ONNXRuntimeInference/CMakeLists.txt:        ${ONNXRUNTIME_LIBRARIES}
    ./DataModel/GenEvent/CMakeLists.txt:        ${HEPMC_LIBRARIES}
    epsilon:junosw blyth$ 



Is "find_package(Geant4" doing anything
----------------------------------------- 

::

    N[blyth@localhost junosw]$ echo $CMAKE_PREFIX_PATH | tr  ":" "\n"
    /data/blyth/junotop/junosw/InstallArea
    /data/blyth/junotop/mt.sniper/InstallArea
    /data/blyth/junotop/sniper/InstallArea/lib64
    /data/blyth/junotop/sniper/InstallArea
    /data/blyth/junotop/ExternalLibs/libonnxruntime/1.11.1
    /data/blyth/junotop/ExternalLibs/libmore/0.8.3
    /data/blyth/junotop/ExternalLibs/gibuu/r2021_01
    /data/blyth/junotop/ExternalLibs/talys/1.95
    /data/blyth/junotop/ExternalLibs/nuwro/19.02.2
    /data/blyth/junotop/ExternalLibs/genie/3.00.06
    /data/blyth/junotop/ExternalLibs/customgeant4/0.0.1
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno
    /data/blyth/junotop/ExternalLibs/HepMC/2.06.09
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06
    /data/blyth/junotop/ExternalLibs/xrootd/5.3.4
    /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0
    /data/blyth/junotop/ExternalLibs/tbb/2020.3


::

    N[blyth@localhost Geant4]$ cd /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Geant4/10.04.p02.juno
    N[blyth@localhost 10.04.p02.juno]$ find . -name '*.cmake'
    ./lib64/Geant4-10.4.2/Modules/FindTBB.cmake
    ./lib64/Geant4-10.4.2/Modules/FindAIDA.cmake
    ./lib64/Geant4-10.4.2/Modules/FindHepMC.cmake
    ./lib64/Geant4-10.4.2/Modules/FindPythia6.cmake
    ./lib64/Geant4-10.4.2/Modules/FindStatTest.cmake
    ./lib64/Geant4-10.4.2/Modules/IntelCompileFeatures.cmake
    ./lib64/Geant4-10.4.2/UseGeant4.cmake
    ./lib64/Geant4-10.4.2/Geant4Config.cmake
    ./lib64/Geant4-10.4.2/Geant4ConfigVersion.cmake
    ./lib64/Geant4-10.4.2/Geant4LibraryDepends.cmake
    ./lib64/Geant4-10.4.2/Geant4LibraryDepends-release.cmake
    ./share/Geant4-10.4.2/examples/extended/medical/DICOM/cmake/DownloadDICOMData.cmake
    ./share/Geant4-10.4.2/examples/extended/parallel/MPI/ctests-definitions.cmake
    ./share/Geant4-10.4.2/examples/extended/exoticphysics/phonon/ComparePhonon.cmake
    N[blyth@localhost 10.04.p02.juno]$ 


lib64/Geant4-10.4.2/Geant4Config.cmake::

     01 # - Geant4 CMake Configuration File for External Projects
      2 # This file is configured by Geant4 for use by an external project
      3 # This file is configured by Geant4's CMake system and SHOULD NOT BE EDITED
      4 #
      5 # It defines the following variables
      6 #  Geant4_INCLUDE_DIRS - include directories for Geant4
      7 #  Geant4_DEFINITIONS  - compile definitions needed to use Geant4
      8 #  Geant4_LIBRARIES    - libraries to link against
      9 #  Geant4_BUILD_TYPE   - Build type (e.g. "Release") used to build this
     10 #                        install. Only set if Geant4 was installed using
     11 #                        a single mode tool (e.g. make, ninja).
     12 #  Geant4_CXX_FLAGS    - Recommended CXX flags for the compiler used to
     13 #                        build the Geant4 libraries.
     14 #  Geant4_CXX_FLAGS_<CONFIG> - Recommended CXX flags for build mode CONFIG.
     15 #  Geant4_USE_FILE     - path to a CMake module which may be included to
     16 #                        help setup CMake variables
     17 #  Geant4_CXXSTD       - C++ Standard used to compile Geant4, e.g. c++98
     18 #  Geant4_TLS_MODEL    - Thread Local Storage model used. Only set if
     19 #                        the install provides multithreading support.
     20 #



DONE : Get Custom4 to generate Custom4Config.cmake : without using BCM
--------------------------------------------------------------------------

::

    epsilon:cmake blyth$ vi Templates/Geant4Config.cmake.in
    epsilon:cmake blyth$ 
    epsilon:cmake blyth$ pwd
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/cmake
    epsilon:cmake blyth$ 

    epsilon:Modules blyth$ grep Template *.cmake
    G4CMakeSettings.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/geant4_validate_sources.cmake.in
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/Geant4Config.cmake.in
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/Geant4ConfigVersion.cmake.in
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/UseGeant4.cmake
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/UseGeant4_internal.cmake
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/Geant4Config.cmake.in
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/Geant4ConfigVersion.cmake.in
    G4ConfigureCMakeHelpers.cmake:  ${PROJECT_SOURCE_DIR}/cmake/Templates/UseGeant4.cmake
    G4ConfigureGNUMakeHelpers.cmake:      ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4make-skeleton.in
    G4ConfigureGNUMakeHelpers.cmake:      ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4make-skeleton.in
    G4ConfigureGNUMakeHelpers.cmake:    ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4-env-skeleton.in
    G4ConfigurePkgConfigHelpers.cmake:      ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4-config.in
    G4ConfigurePkgConfigHelpers.cmake:      ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4-config.in
    G4ConfigurePkgConfigHelpers.cmake:    ${CMAKE_SOURCE_DIR}/cmake/Templates/geant4-config.in
    Geant4CPackBase.cmake:  cmake/Templates/CMakeCPackOptions.cmake.in
    Geant4InterfaceOptions.cmake:    set(Qt5_USE_FILE_IN "${PROJECT_SOURCE_DIR}/cmake/Templates/Geant4UseQt5.cmake.in")
    epsilon:Modules blyth$ 



After that rebuild on workstation
------------------------------------

::

    bash junoenv libs all custom4 

::

    [custom4-install] -- Install configuration: ""
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib/libCustom4.so
    [custom4-install] -- Set runtime path of "/data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib/libCustom4.so" to ""
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4OpBoundaryProcess.hh
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4IPMTAccessor.h
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4CustomART.h
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4CustomART_Debug.h
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4MultiLayrStack.h
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/include/Custom4/C4Touchable.h
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib64/Custom4-0.0.2/Custom4Config.cmake
    [custom4-install] -- Installing: /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib64/Custom4-0.0.2/Custom4ConfigVersion.cmake
    [custom4-install] /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.0.2 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-setup:
    [custom4-setup] /data/blyth/junotop/ExternalLibs/custom4/0.0.2 /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [custom4-setup] /data/blyth/junotop/ExternalLibs /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    N[blyth@localhost junoenv]$ 



FIXED : lib64 lib mixup by simplifications in c4/CMakeLists.txt
-----------------------------------------------------------------

::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib/
    total 132
      0 drwxrwxr-x. 5 blyth blyth     73 Mar 23 23:09 ..
      0 drwxrwxr-x. 2 blyth blyth     27 Mar 23 23:09 .
    132 -rwxr-xr-x. 1 blyth blyth 132344 Mar 23 23:09 libCustom4.so
    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib64/
    total 0
    0 drwxrwxr-x. 5 blyth blyth 73 Mar 23 23:09 ..
    0 drwxrwxr-x. 2 blyth blyth 67 Mar 23 23:09 Custom4-0.0.2
    0 drwxrwxr-x. 3 blyth blyth 27 Mar 23 23:09 .
    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/custom4/0.0.2/lib64/Custom4-0.0.2/
    total 8
    0 drwxrwxr-x. 2 blyth blyth  67 Mar 23 23:09 .
    0 drwxrwxr-x. 3 blyth blyth  27 Mar 23 23:09 ..
    4 -rw-r--r--. 1 blyth blyth 484 Mar 23 23:09 Custom4Config.cmake
    4 -rw-r--r--. 1 blyth blyth 904 Mar 23 23:09 Custom4ConfigVersion.cmake
    N[blyth@localhost junoenv]$ 


WIP : try to use the Custom4 headers and lib from PhysiSim
--------------------------------------------------------------

cmake/JUNODependencies.cmake::

    090 if (DEFINED ENV{JUNO_EXTLIB_custom4_HOME})
     91     set(Custom4_VERBOSE ON)
     92     find_package(Custom4 REQUIRED)
     93     #[=[
     94     message(STATUS "Custom4_FOUND         : ${Custom4_FOUND} ")
     95     message(STATUS "Custom4_VERSION       : ${Custom4_VERSION} ")
     96     message(STATUS "Custom4_PREFIX        : ${Custom4_PREFIX} ")
     97     message(STATUS "Custom4_INCLUDE_DIR   : ${Custom4_INCLUDE_DIR} ")
     98     message(STATUS "Custom4_INCLUDE_DIRS  : ${Custom4_INCLUDE_DIRS} ")
     99     message(STATUS "Custom4_DEFINITIONS   : ${Custom4_DEFINITIONS} ")
    100     message(STATUS "Custom4_LIBRARY_DIR   : ${Custom4_LIBRARY_DIR} ")
    101     message(STATUS "Custom4_LIBRARIES     : ${Custom4_LIBRARIES} ")
    102     message(STATUS "Custom4_CMAKE_PATH    : ${Custom4_CMAKE_PATH} ")
    103     message(STATUS "Custom4_CMAKE_DIR     : ${Custom4_CMAKE_DIR} ")
    104     #]=]
    105 
    106     set(CUSTOM4_LIBRARIES ${Custom4_LIBRARIES})
    107     message(STATUS "CUSTOM4_LIBRARIES : ${CUSTOM4_LIBRARIES}")
    108 endif()
        

header config : C4 omitted CFLAGS : added and bumped to 0.0.6
----------------------------------------------------------------

::

    /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:19:10: fatal error: C4OpBoundaryProcess.hh: No such file or directory
    #include "C4OpBoundaryProcess.hh"
              ^~~~~~~~~~~~~~~~~~~~~~~~
    compilation terminated.



After CFLAGS setup Running from PhysiSim build dir giving new error
-----------------------------------------------------------------------

::

    N[blyth@localhost PhysiSim]$ pwd
    /data/blyth/junotop/junosw/build/Simulation/DetSimV2/PhysiSim

    epsilon:junosw blyth$ jcv PMTAccessor
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    epsilon:junosw blyth$ 



HUH : build/Simulation completes : I was expecting link error because I didnt add ${CUSTOM4_LIBRARIES} to the CMakeLists.txt
-------------------------------------------------------------------------------------------------------------------------------





