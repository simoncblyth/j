opticks_with_cmake_offline
=============================


Finding and linking against Opticks::G4OK 
---------------------------------------------

cmake/JUNODependencies.cmake::


    set(G4OK_FOUND NO)
    find_package(G4OK CONFIG)
    if(G4OK_FOUND)
        message(STATUS "G4OK_FOUND" )
        compile_definitions(WITH_G4OPTICKS)
    else()
        message(STATUS "NOT-G4OK_FOUND" )
    endif()
    message(STATUS "cmake/JUNODependencies.cmake : G4OK_FOUND:${G4OK_FOUND}" )


Hmm: Also need Opticks::G4OK on target link lines 
but offline does not do targets so much. 
Maybe expedient to use the old "global" style of CMake
for the libs as well as the compile_definitions.

But it might be the case that the automatic CMake recursive handling 
does not work when using the old style approach. 

* https://stackoverflow.com/questions/31969547/what-is-the-difference-between-include-directories-and-target-include-directorie


Actually looking closer cmake/Modules/PKG.cmake does create targets. 


jm-cmake jm FAILs to find Sniper headers but "bash junoenv offline" works 
-----------------------------------------------------------------------------

::

    O[blyth@localhost junoenv]$ t jm-cmake
    jm-cmake () 
    { 
        : using build layout from $JUNOTOP/junoenv/junoenv-offline.sh junoenv-offline-compile-cmake;
        local sdir=$JUNOTOP/offline;
        local bdir=$JUNOTOP/offline/build;
        local idir=$JUNOTOP/offline/InstallArea;
        [ ! -d $sdir -o ! -d $bdir -o ! -d $idir ] && echo $msg use "bash junoenv offline" first && return 1;
        cd $bdir;
        cmake $sdir -DCMAKE_INSTALL_PREFIX=$idir -DCMAKE_CXX_STANDARD=17
    }
    O[blyth@localhost junoenv]$ t jm
    jm () 
    { 
        : j/j.bash;
        local bdir=$(jm-bdir);
        cd $bdir;
        [ $? -ne 0 ] && echo bdir error && return 1;
        make;
        [ $? -ne 0 ] && echo make error && return 2;
        make install;
        [ $? -ne 0 ] && echo install error && return 3;
        return 0
    }
    O[blyth@localhost junoenv]$ 


Notably there is no Sniper in the CMAKE_PREFIX_PATH::

    O[blyth@localhost junoenv]$ echo $CMAKE_PREFIX_PATH | tr ":" "\n"
    /data/blyth/junotop/ExternalLibs/frontier/2.9.1
    /data/blyth/junotop/ExternalLibs/pacparser/1.3.7
    /data/blyth/junotop/ExternalLibs/python-yaml/5.4.1.1
    /data/blyth/junotop/ExternalLibs/libyaml/0.2.4
    /data/blyth/junotop/ExternalLibs/mysql-connector-cpp/1.1.12
    /data/blyth/junotop/ExternalLibs/mysql-connector-c/6.1.9
    /data/blyth/junotop/ExternalLibs/libmore/0.8.3
    /data/blyth/junotop/ExternalLibs/talys/1.95
    /data/blyth/junotop/ExternalLibs/nuwro/19.02.2
    /data/blyth/junotop/ExternalLibs/genie/3.00.06
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno
    /data/blyth/junotop/ExternalLibs/HepMC/2.06.09
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06
    /data/blyth/junotop/ExternalLibs/xrootd/5.3.1
    /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0
    /data/blyth/junotop/ExternalLibs/CMT/v1r26
    /data/blyth/junotop/ExternalLibs/tbb/2019_U8
    /data/blyth/junotop/ExternalLibs/pythia6/6.4.28
    /data/blyth/junotop/ExternalLibs/LHAPDF/6.3.0
    /data/blyth/junotop/ExternalLibs/libxml2/2.9.12
    /data/blyth/junotop/ExternalLibs/log4cpp/1.1.3
    /data/blyth/junotop/ExternalLibs/sqlite3/3.35.5
    /data/blyth/junotop/ExternalLibs/fftw3/3.3.8
    /data/blyth/junotop/ExternalLibs/gsl/2.5
    /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2
    /data/blyth/junotop/ExternalLibs/Git/2.33.0
    /data/blyth/junotop/ExternalLibs/Cmake/3.21.2
    /data/blyth/junotop/ExternalLibs/Boost/1.77.0
    /data/blyth/junotop/ExternalLibs/python-numpy/1.21.2
    /data/blyth/junotop/ExternalLibs/python-cython/0.29.24
    /data/blyth/junotop/ExternalLibs/python-pip/21.2.4
    /data/blyth/junotop/ExternalLibs/python-setuptools/58.0.4
    /data/blyth/junotop/ExternalLibs/Python/3.8.12

    /data/blyth/junotop/ExternalLibs/opticks/head
    /data/blyth/junotop/ExternalLibs/opticks/head/externals
    /home/blyth/local/opticks/externals/OptiX_650
    O[blyth@localhost junoenv]$ 


::

    epsilon:junoenv blyth$  grep CMAKE_PREFIX_PATH *.*
    junoenv-external-libs.sh:export CMAKE_PREFIX_PATH=\${JUNO_EXTLIB_${pkg}_HOME}:\${CMAKE_PREFIX_PATH}
    junoenv-external-libs.sh:if ( \$?CMAKE_PREFIX_PATH == 0 ) then
    junoenv-external-libs.sh:    setenv CMAKE_PREFIX_PATH ""
    junoenv-external-libs.sh:setenv CMAKE_PREFIX_PATH \${JUNO_EXTLIB_${pkg}_HOME}:\${CMAKE_PREFIX_PATH}
    junoenv-opticks.sh:system PATH envvars including PATH, LD_LIBRARY_PATH, CMAKE_PREFIX_PATH etc.. that enable 
    junoenv-sniper.sh:export CMAKE_PREFIX_PATH=\${JUNO_SNiPER_HOME}:\${CMAKE_PREFIX_PATH}
    junoenv-sniper.sh:if ( \$?CMAKE_PREFIX_PATH == 0 ) then
    junoenv-sniper.sh:    setenv CMAKE_PREFIX_PATH ""
    junoenv-sniper.sh:setenv CMAKE_PREFIX_PATH \${JUNO_SNiPER_HOME}:\${CMAKE_PREFIX_PATH}
    epsilon:junoenv blyth$ 


* junoenv-sniper-compile-cmake-create-setup-scripts writes a $JUNOTOP/sniper/InstallArea/bashrc 

    176 function junoenv-sniper-compile-cmake {
    177     local msg="==== $FUNCNAME: "
    178     pushd $(juno-top-dir) >& /dev/null
    179     if [ -d "$(junoenv-sniper-name)" ]; then
    180         pushd $(junoenv-sniper-name)
    181 
    182         # create the build directory
    183         [ -d "build" ] || mkdir build || exit -1
    184         # create the install directory
    185         [ -d "InstallArea" ] || mkdir InstallArea || exit -1
    186         local installprefix=$(juno-top-dir)/sniper/InstallArea
    187         # start the build and install of sniper
    188         pushd build
    189 
    190         cmake .. -DCMAKE_INSTALL_PREFIX=$installprefix -DCMAKE_CXX_STANDARD=17 || exit -1
    191         make || exit -1
    192         make install || exit -1
    193 
    194         popd # build
    195 
    196         # goto InstallArea and create setup scripts
    197         pushd InstallArea
    198         junoenv-sniper-compile-cmake-create-setup-scripts
    199         popd # InstallArea
    200 
    201         popd # $(junoenv-sniper-name)
    202     fi
    203     popd >& /dev/null
    204 
    205 }




Its non-standard for the CMAKE_PREFIX_PATH to be the libdir ?::

    O[blyth@localhost j]$ cat $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh 
    #!/bin/bash

    export LD_LIBRARY_PATH=/data/blyth/junotop/sniper/InstallArea/lib64:$LD_LIBRARY_PATH
    export PATH=/data/blyth/junotop/sniper/InstallArea/bin:$PATH
    export CMAKE_PREFIX_PATH=/data/blyth/junotop/sniper/InstallArea/lib64:$CMAKE_PREFIX_PATH
    export SNIPER_INIT_FILE=/data/blyth/junotop/sniper/InstallArea/share/sniper/.init.json

    if [ "xpython" != "x" ]; then
        if [ -d "/data/blyth/junotop/sniper/InstallArea/python" ]; then
            export PYTHONPATH=/data/blyth/junotop/sniper/InstallArea/python:$PYTHONPATH
        fi
    fi


This one looks more reasonable::

    O[blyth@localhost j]$ cat $JUNOTOP/sniper/InstallArea/bashrc

    # Define JUNO_SNiPER_HOME
    if [ -z "${JUNOTOP}" ]; then
    export JUNO_SNiPER_HOME=/data/blyth/junotop/sniper/InstallArea
    else
    export JUNO_SNiPER_HOME=${JUNOTOP}/sniper/InstallArea
    fi

    export SNiPER_DIR=${JUNO_SNiPER_HOME}

    # Add to PATH
    export PATH=${JUNO_SNiPER_HOME}/bin:${PATH}

    # Add to LD_LIBRARY_PATH and PYTHONPATH
    export PYTHONPATH=${JUNO_SNiPER_HOME}/python:${PYTHONPATH}
    if [ -d ${JUNO_SNiPER_HOME}/lib ]; then
    export LD_LIBRARY_PATH=${JUNO_SNiPER_HOME}/lib:${LD_LIBRARY_PATH}
    export PYTHONPATH=${JUNO_SNiPER_HOME}/lib:${PYTHONPATH}
    fi
    if [ -d ${JUNO_SNiPER_HOME}/lib64 ]; then
    export LD_LIBRARY_PATH=${JUNO_SNiPER_HOME}/lib64:${LD_LIBRARY_PATH}
    export PYTHONPATH=${JUNO_SNiPER_HOME}/lib64:${PYTHONPATH}
    fi

    # Add to CPATH
    export CPATH=${JUNO_SNiPER_HOME}/include:${CPATH}

    # Add to CMAKE
    export CMAKE_PREFIX_PATH=${JUNO_SNiPER_HOME}:${CMAKE_PREFIX_PATH}







Opticks-Offline CMT setup
-----------------------------

Connection via CMT macros with contents from *opticks-config* script

::

    epsilon:DetSimPolicy blyth$ cat /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimPolicy/cmt/requirements 
    package DetSimPolicy
    # source the geant4 script first

    use Geant4 v* Externals
    use CLHEP v* Externals
    use Xercesc v* Externals

    # The below sets blank macro values unless CMTEXTRATAGS envvar includes opticks, 
    # thus it does no harm when the optional Opticks external is not installed.
    use OpticksG4OK    v* Externals

    # Enable the debug information in the library
    macro_append DetSimPolicy_cppflags " -g "


::

    epsilon:cmt blyth$ cat /Users/blyth/junotop/offline/Simulation/DetSimV2/Opticks/cmt/requirements 
    package Opticks

    macro Opticks_home "`opticks-config --prefix`"

    set OPTICKSDATAROOT "$(Opticks_home)/opticksdata"

    macro Opticks_cppflags " `opticks-config --cflags` "
    macro Opticks_linkopts " `opticks-config --libs` "



::

    epsilon:Simulation blyth$ find . -name requirements -exec grep -H Opticks {} \;
    ./GenTools/cmt/requirements:# thus it does no harm when the optional Opticks external is not installed.
    ./GenTools/cmt/requirements:use OpticksG4OK    v* Externals
    ./DetSimV2/Opticks/cmt/requirements:package Opticks
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_home "`opticks-config --prefix`"
    ./DetSimV2/Opticks/cmt/requirements:set OPTICKSDATAROOT "$(Opticks_home)/opticksdata"
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_cppflags " `opticks-config --cflags` "
    ./DetSimV2/Opticks/cmt/requirements:macro Opticks_linkopts " `opticks-config --libs` "
    ./DetSimV2/DetSimPolicy/cmt/requirements:# thus it does no harm when the optional Opticks external is not installed.
    ./DetSimV2/DetSimPolicy/cmt/requirements:use OpticksG4OK    v* Externals
    epsilon:Simulation blyth$ 


    epsilon:Simulation blyth$ find . -type f -exec grep -l WITH_G4OPTICKS {} \;
    ./GenTools/src/GtOpticksTool.cc
    ./GenTools/src/GtOpticksTool.h
    ./DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./DetSimV2/PhysiSim/include/DsG4Scintillation.h
    ./DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    ./DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    ./DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc



CMake should automate the recursive collection of libs and cflags done for CMT by opticks-config (based on pkgconfig)
------------------------------------------------------------------------------------------------------------------------

::

    epsilon:issues blyth$ opticks-config --cflags G4OK | tr " " "\n"
    -DOPTICKS_G4OK
    -DOPTICKS_CFG4
    -DOPTICKS_X4
    -DG4USE_STD11
    -DG4UI_USE_TCSH
    -W
    -Wall
    -pedantic
    -Wno-non-virtual-dtor
    -Wno-long-long
    -Wwrite-strings
    -Wpointer-arith
    -Woverloaded-virtual
    -Wno-variadic-macros
    -Wshadow
    -pipe
    -Qunused-arguments
    -stdlib=libc++
    -DG4USE_STD11
    -std=c++11
    -DOPTICKS_OKOP
    -DOPTICKS_OXRAP
    -DOPTICKS_OKGEO
    -DOPTICKS_GGEO
    -DOPTICKS_THRAP
    -DOPTICKS_OKCORE
    -DOPTICKS_NPY
    -DOPTICKS_BRAP
    -DWITH_BOOST_ASIO
    -DOPTICKS_CUDARAP
    -DOPTICKS_SYSRAP
    -DWITH_STTF
    -DWITH_PLOG
    -DOPTICKS_OKCONF
    -I/usr/local/opticks_externals/g4_1042/bin/../include/Geant4
    -I/usr/local/opticks_externals/clhep/include
    -I/usr/local/opticks_externals/xercesc/include
    -I/usr/local/opticks/include/G4OK
    -I/usr/local/opticks/include/CFG4
    -I/usr/local/opticks/include/ExtG4
    -I/usr/local/opticks/include/OKOP
    -I/usr/local/opticks/include/OptiXRap
    -I/usr/local/opticks/include/OpticksGeo
    -I/usr/local/opticks/include/GGeo
    -I/usr/local/opticks/include/ThrustRap
    -I/usr/local/opticks/include/OpticksCore
    -I/usr/local/opticks/externals/include
    -I/usr/local/opticks/include/NPY
    -I/usr/local/opticks/include/BoostRap
    -I/usr/local/opticks/include/CUDARap
    -I/usr/local/cuda/include
    -I/usr/local/opticks/externals/glm/glm
    -I/usr/local/opticks/include/SysRap
    -I/usr/local/opticks/include/OKConf
    -I/usr/local/optix/include
    -I/usr/local/opticks/externals/glm/glm
    -I/usr/local/opticks/externals/plog/include
    -I/usr/local/opticks/externals/include/nljson
    -I/usr/local/cuda/include
    -std=c++11
    epsilon:issues blyth$ 




::

    epsilon:issues blyth$ opticks-config --libs G4OK | tr " " "\n"
    -L/usr/local/opticks_externals/g4_1042/bin/../lib
    -L/usr/local/opticks_externals/clhep/lib
    -L/usr/local/opticks_externals/xercesc/lib
    -L/usr/local/opticks/lib
    -L/usr/local/optix/lib64
    -L/usr/local/cuda/lib
    -lG4OK
    -lCFG4
    -lExtG4
    -lG4Tree
    -lG4FR
    -lG4GMocren
    -lG4visHepRep
    -lG4RayTracer
    -lG4VRML
    -lG4vis_management
    -lG4modeling
    -lG4interfaces
    -lG4persistency
    -lG4analysis
    -lG4error_propagation
    -lG4readout
    -lG4physicslists
    -lG4run
    -lG4event
    -lG4tracking
    -lG4parmodels
    -lG4processes
    -lG4digits_hits
    -lG4track
    -lG4particles
    -lG4geometry
    -lG4materials
    -lG4graphics_reps
    -lG4intercoms
    -lG4global
    -lCLHEP-2.4.1.0
    -lG4zlib
    -lxerces-c
    -lOKOP
    -lOptiXRap
    -loptix
    -loptixu
    -loptix_prime
    -lstdc++
    -lOpticksGeo
    -lGGeo
    -lThrustRap
    /Developer/NVIDIA/CUDA-9.1/lib/libcudart_static.a
    -Wl,-rpath,/usr/local/cuda/lib
    -lOpticksCore
    -lNPY
    -lstdc++
    -lBoostRap
    -lCUDARap
    /Developer/NVIDIA/CUDA-9.1/lib/libcudart_static.a
    -Wl,-rpath,/usr/local/cuda/lib
    -lSysRap
    -lstdc++
    -lcudart
    -lcurand
    -lOKConf
    epsilon:issues blyth$ 




How to hookup with new CMake offline ?
------------------------------------------

* TODO: study how ROOT/Geant4 etc.. are hooked up and try something similar : the difference being that Opticks is always optional 


