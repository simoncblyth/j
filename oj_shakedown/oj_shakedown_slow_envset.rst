oj_shakedown_slow_envset
===========================


TODO : detect geant4 env already setup in opticks bashrc before doing the slow search for geant4 


::

     01 #!/bin/bash
      2 # generated from .gitlab-ci.yml of 
      3 # .gitlab-ci/oj_helper.sh EMIT_ENVSET
      4 
      5 echo [ envset $(date)
      6 HERE=$(dirname $(realpath $BASH_SOURCE))
      7 DEFAULT_PREFIX=$HERE
      8 PREFIX=${OJ_PREFIX:-$DEFAULT_PREFIX}
      9 
     10 echo [ ENV.bash
     11 t0=$(date +%s)
     12 source $PREFIX/ENV.bash             ## define JUNOTOP and JUNO_OPTICKS_PREFIX 
     13 t1=$(date +%s)
     14 echo ] ENV.bash $(( $t1 - $t0 ))
     15 
     16 echo [ JUNOTOP/setup.sh
     17 t0=$(date +%s)
     18 source $JUNOTOP/setup.sh            ## hookup many JUNOSW externals excluding Opticks
     19 t1=$(date +%s)
     20 echo ] JUNOTOP/setup.sh $(( $t1 - $t0 ))
     21 echo [ JUNO_OPTICKS_PREFIX/bashrc
     22 t0=$(date +%s)
     23 source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals
     24 t1=$(date +%s)
     25 echo ] JUNO_OPTICKS_PREFIX/bashrc $(( $t1 - $t0 ))
     26 
     27 echo [ oj_geomsetup
     28 t0=$(date +%s)
     29 source $PREFIX/bin/opticks_juno.sh  ## oj bash functions 
     30 oj_geomsetup
     31 t1=$(date +%s)
     32 echo ] oj_geomsetup $(( $t1 - $t0 ))
     33 
     34 export CMAKE_PREFIX_PATH=$PREFIX:${CMAKE_PREFIX_PATH}
     35 export PATH=$PREFIX/bin:${PATH}
     36 export LD_LIBRARY_PATH=$PREFIX/lib64:${LD_LIBRARY_PATH}
     37 export PYTHONPATH=$PREFIX/lib64:${PYTHONPATH}
     38 export PYTHONPATH=$PREFIX/python:${PYTHONPATH}
     39 
     40 echo ] envset $(date)






::

    A[blyth@localhost ALL0_DebugPhilox]$ source /home/blyth/junosw/InstallArea/envset.sh
    [ envset Thu May 8 02:30:03 PM CST 2025
    [ ENV.bash
    ] ENV.bash 1
    [ JUNOTOP/setup.sh
    Setup Official junosw (CMake version)
    ] JUNOTOP/setup.sh 7
    [ JUNO_OPTICKS_PREFIX/bashrc
    === opticks-setup-       skip     append                 PATH /usr/local/cuda-12.4/bin
    === opticks-setup-       skip     append                 PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/bin
    === opticks-setup-       skip     append                 PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/lib
    === opticks-setup-       skip     append           PYTHONPATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/py
    === opticks-setup-       skip     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1
    === opticks-setup-       skip     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/externals
    === opticks-setup-       skip     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    === opticks-setup-      nodir     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/lib/pkgconfig
    === opticks-setup-       skip     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/lib64/pkgconfig
    === opticks-setup-       skip     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/externals/lib/pkgconfig
    === opticks-setup-       skip     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/externals/lib64/pkgconfig
    === opticks-setup-       skip     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/lib
    === opticks-setup-       skip     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/lib64
    === opticks-setup-       skip     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/externals/lib
    === opticks-setup-       skip     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.1/externals/lib64
    === opticks-setup-      nodir     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib
    === opticks-setup-       skip     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib64
    === opticks-setup-geant4- : sourcing /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4.sh
    ] JUNO_OPTICKS_PREFIX/bashrc 9
    [ oj_geomsetup
    oj_geomsetup is a function
    oj_geomsetup () 
    { 
        : extra env settings needed by Opticks-JUNOSW geometry conversion;
        : NB this is sourced from envset.sh so needs to be appropriate to every usage;
        : not just the .gitlab-ci.yml one off first runs;
        if [ -n "$OJ_VERBOSE" ]; then
            type $FUNCNAME;
        fi;
        export GEOM=$OJ_SLUG;
        export OJ_PREFIX=$(dirname $(dirname $(realpath $BASH_SOURCE)));
        export OJ_GEOMDIR=$OJ_PREFIX/.opticks/GEOM/${GEOM};
        export ${GEOM}_CFBaseFromGEOM=${OJ_GEOMDIR};
        export CSGOptiXRenderInteractiveTest__FRAME_HOP=1;
        export stree__force_triangulate_solid="filepath:${OJ_GEOMDIR}/CSGFoundry/tessname.txt";
        export SScene__initFromTree_addFrames=${OJ_GEOMDIR}/CSGFoundry/framespec.txt;
        local vv="FUNCNAME OJ_SLUG GEOM BASH_SOURCE OJ_PREFIX OJ_GEOMDIR ${GEOM}_CFBaseFromGEOM stree__force_triangulate_solid SScene__initFromTree_addFrames";
        for v in $vv;
        do
            printf "%30s : %s\n" "$v" "${!v}";
        done;
        export WaterPoolConstruction__CONFIG=3;
        export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10;
        export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10;
        export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10;
        unset U4Mesh__NumberOfRotationSteps_DUMP;
        export U4Mesh__NumberOfRotationSteps_DUMP=1;
        export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480;
        : NumberOfRotationSteps operates at the level of the full torus;
        : rather than the small segment of the torus, so quite a large number of rotation;
        : steps is needed to prevent the tesselated guidetube from impinging into the acrylic;
        return 0
    }
                          FUNCNAME : oj_geomsetup
                           OJ_SLUG : J25_3_0_Opticks_v0_4_1
                              GEOM : J25_3_0_Opticks_v0_4_1
                       BASH_SOURCE : /home/blyth/junosw/InstallArea/bin/opticks_juno.sh
                         OJ_PREFIX : /home/blyth/junosw/InstallArea
                        OJ_GEOMDIR : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_Opticks_v0_4_1
    J25_3_0_Opticks_v0_4_1_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_Opticks_v0_4_1
    stree__force_triangulate_solid : filepath:/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_Opticks_v0_4_1/CSGFoundry/tessname.txt
    SScene__initFromTree_addFrames : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_Opticks_v0_4_1/CSGFoundry/framespec.txt
    ] oj_geomsetup 1
    ] envset Thu May 8 02:30:23 PM CST 2025
    A[blyth@localhost ALL0_DebugPhilox]$ 




Nine seconds from opticks-setup-find-geant4-prefix which does not need to be done::

    A[blyth@localhost ALL0_DebugPhilox]$ date ; opticks-setup-find-geant4-prefix ; date
    Thu May  8 02:35:50 PM CST 2025
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno
    Thu May  8 02:35:59 PM CST 2025



Its searching the jumbo CMAKE_PREFIX_PATH::


    A[blyth@localhost ALL0_DebugPhilox]$ t opticks-setup-find-geant4-prefix
    opticks-setup-find-geant4-prefix () 
    { 
        opticks-setup-find-config-prefix Geant4
    }
    A[blyth@localhost ALL0_DebugPhilox]$ t opticks-setup-find-config-prefix
    opticks-setup-find-config-prefix () 
    { 
        : mimick CMake "find_package name CONFIG" identifing the first prefix in the path;
        local name=${1:-Geant4};
        local prefix="";
        local rc=0;
        local ifs=$IFS;
        IFS=:;
        for pfx in $CMAKE_PREFIX_PATH;
        do
            : protect cmds that can give non-zero rc from "set -e" via pipeline but catch the rc;
            rc=1;
            ls --color=auto -1 $pfx/lib*/$name-*/${name}Config.cmake 2> /dev/null 1>&2 && rc=$?;
            [ $rc -eq 0 ] && prefix=$pfx && break;
            ls --color=auto -1 $pfx/lib*/cmake/$name-*/${name}Config.cmake 2> /dev/null 1>&2 && rc=$?;
            [ $rc -eq 0 ] && prefix=$pfx && break;
            ls --color=auto -1 $pfx/lib*/cmake/$name/${name}Config.cmake 2> /dev/null 1>&2 && rc=$?;
            [ $rc -eq 0 ] && prefix=$pfx && break;
        done;
        IFS=$ifs;
        echo $prefix
    }



doing the below gets it down to 3 seconds::

     22 t0=$(date +%s)
     23 #source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals
     24 CMAKE_PREFIX_PATH= source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals
     25 
     26 t1=$(date +%s)
     27 echo ] JUNO_OPTICKS_PREFIX/bashrc $(( $t1 - $t0 ))



