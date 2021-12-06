precision-cvmfs-offline-build
=================================


* after cvmfs working on precision 
* move aside the old ExternalLibs 


Setup to reuse shared JUNO 830 compiler and externals
-------------------------------------------------------

.bashrc add OLDTOP next to JUNOTOP::

     40 #export JUNOTOP=$HOME/junotop
     41 export JUNOTOP=/data/$USER/junotop
     42 export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs
     43 

::

    O[blyth@localhost ~]$ env | grep JUNO_
    JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs
    JUNO_BINUTILS_PREFIX=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28
    JUNO_GCC_PREFIX=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0
    O[blyth@localhost ~]$ 


    O[blyth@localhost junoenv]$ t jlibs_reuse
    jlibs_reuse () 
    { 
        [ -z "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires envvar JUNO_EXTLIB_OLDTOP && return 1;
        [ ! -d "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires directory JUNO_EXTLIB_OLDTOP $JUNO_EXTLIB_OLDTOP && return 2;
        local libs=$(jlibs-);
        for lib in $libs;
        do
            echo $lib;
            bash junoenv libs reuse $lib || return 1;
        done;
        return 0
    }
    O[blyth@localhost junoenv]$ 


::

    je
    bash junoenv env   # nope must resetup to rewrite the bashrc.sh 
    
    O[blyth@localhost junoenv]$ bash junoenv env resetup



* bash junoenv sniper : now completes using the shared gcc and externals


tds0
------

::

    O[blyth@localhost junoenv]$ t tds0
    tds0 () 
    { 
        : run with opticks disabled;
        local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 ";
        tds- $opts gun $*
    }


    ModuleNotFoundError: No module named 'Tutorial'
    [Inferior 1 (process 336397) exited with code 01]
    Missing separate debuginfos, use: debuginfo-install glibc-2.17-307.el7.1.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64
    (gdb) quit


::

    -- Installing: /data/blyth/junotop/offline/InstallArea/python/JunoTest/__init__.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOElecSimModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNODetSimModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOCommonModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOUtils.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOEventRecModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOWaveRecModule.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py
    -- Installing: /data/blyth/junotop/offline/InstallArea/python/Tutorial/__init__.py



runtime setup different with CMake build ?::


    O[blyth@localhost junoenv]$ j-runtime-env-
    === j-runtime-env-:
    -bash: /data/blyth/junotop/sniper/SniperRelease/cmt/setup.sh: No such file or directory
    -bash: /data/blyth/junotop/offline/JunoRelease/cmt/setup.sh: No such file or directory
    === j-runtime-env-:
    O[blyth@localhost junoenv]$ 


::

    O[blyth@localhost junoenv]$ PYTHONPATH=/data/blyth/junotop/offline/InstallArea/python python -c "from Tutorial import JUNOApplication"
    Traceback (most recent call last):
      File "<string>", line 1, in <module>
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/__init__.py", line 4, in <module>
        from .JUNOApplication import JUNOApplication
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 6, in <module>
        import Sniper
    ModuleNotFoundError: No module named 'Sniper'
    O[blyth@localhost junoenv]$ 


    O[blyth@localhost junoenv]$ l /data/blyth/junotop/sniper/InstallArea/python/
    total 12
    0 drwxrwxr-x. 7 blyth blyth 100 Dec  4 01:01 ..
    0 drwxrwxr-x. 6 blyth blyth 160 Dec  4 01:01 .
    0 drwxr-xr-x. 2 blyth blyth  63 Dec  4 01:01 SniperPyUsages
    0 drwxr-xr-x. 2 blyth blyth  54 Dec  4 01:01 SniperProfiling
    0 drwxr-xr-x. 2 blyth blyth  49 Dec  4 01:01 RootWriter
    0 drwxr-xr-x. 2 blyth blyth  71 Dec  4 01:01 Sniper
    4 -rw-r--r--. 1 blyth blyth  67 Oct 29 09:04 SniperCoreUsages.py
    4 -rw-r--r--. 1 blyth blyth  65 Oct 29 09:04 SniperPython.py
    4 -rw-r--r--. 1 blyth blyth  66 Oct 29 09:04 SniperRootUsages.py



Hmm stomping on PYTHONPATH or missed a setupscript::

    O[blyth@localhost junoenv]$ echo $PYTHONPATH
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib:/home/blyth
    O[blyth@localhost junoenv]$ gip PYTHONPATH
    /home/blyth/.bash_profile:export PYTHONPATH=$PYTHONPATH:$(opticks-fold)
    /home/blyth/vip/vip.bash:   local vars="VIP_MODE OPTICKS_TOP CMAKE_PREFIX_PATH PKG_CONFIG_PATH PATH LD_LIBRARY_PATH PYTHONPATH MANPATH CPATH"
    /home/blyth/.opticks_config:# PYTHONPATH is needed to allow python scripts to "import opticks"
    /home/blyth/.opticks_config:export PYTHONPATH=$(dirname $OPTICKS_HOME)        
    O[blyth@localhost junoenv]$ 

    O[blyth@localhost junoenv]$ jgr PYTHONPATH
    ./cmake/JUNOSetupScripts.cmake:    "export PYTHONPATH=@CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_LIBDIR@:\${PYTHONPATH}\n"
    ./cmake/JUNOSetupScripts.cmake:    "export PYTHONPATH=@CMAKE_INSTALL_PREFIX@/python:\${PYTHONPATH}\n"
    ./cmake/JUNOSetupScripts.cmake:    "setenv PYTHONPATH @CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_LIBDIR@:\${PYTHONPATH}\n"
    ./cmake/JUNOSetupScripts.cmake:    "setenv PYTHONPATH @CMAKE_INSTALL_PREFIX@/python:\${PYTHONPATH}\n"

::

    O[blyth@localhost junotop]$ find . -name setup.sh.in
    ./offline/build/setup.sh.in
    O[blyth@localhost junotop]$ cat offline/build/setup.sh.in
    #!/bin/bash
    # Generated by cmake 
    export CMAKE_PREFIX_PATH=@CMAKE_INSTALL_PREFIX@:${CMAKE_PREFIX_PATH}
    export PATH=@CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_BINDIR@:${PATH}
    export LD_LIBRARY_PATH=@CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_LIBDIR@:${LD_LIBRARY_PATH}
    export PYTHONPATH=@CMAKE_INSTALL_PREFIX@/@CMAKE_INSTALL_LIBDIR@:${PYTHONPATH}
    export PYTHONPATH=@CMAKE_INSTALL_PREFIX@/python:${PYTHONPATH}

    export XMLOBJDESCROOT=/data/blyth/junotop/offline/XmlObjDesc
    export BASEEVENTROOT=/data/blyth/junotop/offline/DataModel/BaseEvent
    export EDMUTILROOT=/data/blyth/junotop/offline/DataModel/EDMUtil
    export CLHEPDICTROOT=/data/blyth/junotop/offline/DataModel/Dict/CLHEPDict
    export HEPMCDICTROOT=/data/blyth/junotop/offline/DataModel/Dict/HepMCDict
    export CONTEXTROOT=/data/blyth/junotop/offline/DataModel/Context
    export EVTNAVIGATORROOT=/data/blyth/junotop/offline/DataModel/EvtNavigator
    export DATAREGISTRITIONSVCROOT=/data/blyth/junotop/offline/DataModel/DataRegistritionSvc
    export GENEVENTV2ROOT=/data/blyth/junotop/offline/DataModel/GenEventV2
    export SIMEVENTV2ROOT=/data/blyth/junotop/offline/DataModel/SimEventV2
    export ELECEVENTROOT=/data/blyth/junotop/offline/DataModel/ElecEvent
    export ELECTRUTHROOT=/data/blyth/junotop/offline/DataModel/ElecTruth
    ...


    O[blyth@localhost junotop]$ jgr setup.sh.in
    ./cmake/JUNOSetupScripts.cmake:file(WRITE ${CMAKE_BINARY_DIR}/setup.sh.in
    ./cmake/JUNOSetupScripts.cmake:    file(APPEND ${CMAKE_BINARY_DIR}/setup.sh.in
    ./cmake/JUNOSetupScripts.cmake:    file(APPEND ${CMAKE_BINARY_DIR}/setup.sh.in
    ./cmake/JUNOSetupScripts.cmake:        file(APPEND ${CMAKE_BINARY_DIR}/setup.sh.in
    ./cmake/JUNOInstallOfflineSetup.cmake:configure_file("${CMAKE_CURRENT_BINARY_DIR}/setup.sh.in" "${CMAKE_CURRENT_BINARY_DIR}/setup.sh"
    ./build/CMakeFiles/Makefile.cmake:  "setup.sh.in"


    O[blyth@localhost junotop]$ find . -name setup.sh 
    ./setup.sh  
       # cmt world

    ./ExternalInterface/Externals/OpticksG4OK/cmt/setup.sh
    ./ExternalInterface/Externals/Python/cmt/setup.sh
    ./ExternalInterface/Externals/Geant4/cmt/setup.sh
    ./ExternalInterface/Externals/More/cmt/setup.sh
    ./ExternalInterface/Externals/ROOT/cmt/setup.sh
    ./ExternalInterface/Externals/MySQL/cmt/setup.sh
    ./ExternalInterface/Externals/Boost/cmt/setup.sh
    ./ExternalInterface/Externals/TBB/cmt/setup.sh
    ./ExternalInterface/Externals/CLHEP/cmt/setup.sh
    ./ExternalInterface/Externals/HepMC/cmt/setup.sh
    ./ExternalInterface/Externals/Xercesc/cmt/setup.sh
    ./ExternalInterface/EIRelease/cmt/setup.sh

    ./ExternalLibs_broken/Build/pip-20.3.4/tools/travis/setup.sh
    ./ExternalLibs_broken/Build/boost_1_75_0/libs/filesystem/example/test/setup.sh
    ./ExternalLibs_broken/CMT/v1r26/mgr/setup.sh
    ./ExternalLibs_broken/CMT/v1r26/src/setup.sh

    ./sniper/InstallArea/share/sniper/setup.sh
    ./offline/setup.sh
    ./offline/Simulation/GenDecay/doc/setup.sh
    ./offline/Generator/NuSolGen/app/setup.sh
    ./offline/build/setup.sh
    ./offline/InstallArea/setup.sh



    O[blyth@localhost junotop]$ cat offline/InstallArea/setup.sh
    #!/bin/bash
    # Generated by cmake 
    export CMAKE_PREFIX_PATH=/data/blyth/junotop/offline/InstallArea:${CMAKE_PREFIX_PATH}
    export PATH=/data/blyth/junotop/offline/InstallArea/bin:${PATH}
    export LD_LIBRARY_PATH=/data/blyth/junotop/offline/InstallArea/lib64:${LD_LIBRARY_PATH}
    export PYTHONPATH=/data/blyth/junotop/offline/InstallArea/lib64:${PYTHONPATH}
    export PYTHONPATH=/data/blyth/junotop/offline/InstallArea/python:${PYTHONPATH}

    export XMLOBJDESCROOT=/data/blyth/junotop/offline/XmlObjDesc
    export BASEEVENTROOT=/data/blyth/junotop/offline/DataModel/BaseEvent
    export EDMUTILROOT=/data/blyth/junotop/offline/DataModel/EDMUtil
    export CLHEPDICTROOT=/data/blyth/junotop/offline/DataModel/Dict/CLHEPDict




::

    O[blyth@localhost junotop]$ t j-runtime-env-
    j-runtime-env- () 
    { 
        : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont;
        local msg="=== $FUNCNAME: ";
        echo $msg;
        source $JUNOTOP/bashrc.sh;
        local sniper_cmt_setup=$JUNOTOP/sniper/SniperRelease/cmt/setup.sh;
        if [ -f $sniper_cmt_setup ]; then
            CMTEXTRATAGS= source $sniper_cmt_setup;
            source $JUNOTOP/offline/JunoRelease/cmt/setup.sh;
        else
            source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh;
            source $JUNOTOP/offline/InstallArea/setup.sh;
        fi;
        echo $msg
    }
    O[blyth@localhost junotop]$ 




Hmm ExternalLibs rejig means that OPTICKS_PREFIX not existing::

    O[blyth@localhost ~]$ echo $OPTICKS_PREFIX
    /data/blyth/junotop/ExternalLibs/opticks/head

    O[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/opticks/
    ls: cannot access /data/blyth/junotop/ExternalLibs/opticks/: No such file or directory
    O[blyth@localhost ~]$ mkdir -p $OPTICKS_PREFIX
    O[blyth@localhost ~]$ 



Hmm with reused externals cannot write to /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig/Boost.pc::


    O[blyth@localhost junoenv]$ bash junoenv opticks


    ############## boost ###############

    === boost-pc : creating dir /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig
    mkdir: cannot create directory '/data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig': Read-only file system
    === boost-pc : /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig/Boost.pc
    /data/blyth/junotop/opticks/externals/boost.bash: line 873: /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig/Boost.pc: No such file or directory
    === opticks-pc- : RC 1 from func boost : ABORTING
    === opticks-full : ERR from opticks-full-externals
    ==== junoenv-opticks-command: from opticks-git clone /data/opticks_download_cache/opticksaux.git rc 2
    ==== junoenv-opticks-command: error from function opticks-git clone /data/opticks_download_cache/opticksaux.git
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: rc 2



::

    epsilon:junoenv blyth$ t opticks-full-externals
    opticks-full-externals () 
    { 
        local msg="=== $FUNCNAME :";
        echo $msg START $(date);
        local rc;
        echo $msg installing the below externals into $(opticks-prefix)/externals;
        opticks-externals;
        opticks-externals-install;
        rc=$?;
        [ $rc -ne 0 ] && return $rc;
        echo $msg config-ing the preqs;
        opticks-preqs;
        opticks-preqs-pc;
        rc=$?;
        [ $rc -ne 0 ] && return $rc;
        echo $msg config-ing the foreign;
        opticks-foreign;
        opticks-foreign-pc;
        rc=$?;
        [ $rc -ne 0 ] && return $rc;
        echo $msg DONE $(date);
        return 0
    }

    epsilon:junoenv blyth$ opticks-externals
    bcm
    glm
    glfw
    glew
    gleq
    imgui
    plog
    opticksaux
    nljson

    epsilon:junoenv blyth$ opticks-preqs
    cuda
    optix

    epsilon:junoenv blyth$ opticks-foreign
    boost
    clhep
    xercesc
    g4


    epsilon:junoenv blyth$ t opticks-foreign-pc
    opticks-foreign-pc () 
    { 
        opticks-pc- $(opticks-foreign)
    }
    epsilon:junoenv blyth$ t opticks-pc-
    opticks-pc- () 
    { 
        echo $FUNCNAME;
        local msg="=== $FUNCNAME :";
        local funcs=$*;
        local func;
        for func in $funcs;
        do
            printf "\n\n\n############## %s ###############\n\n\n" $func;
            $func-;
            $func-pc;
            rc=$?;
            [ $rc -ne 0 ] && echo $msg RC $rc from func $func : ABORTING && return $rc;
        done;
        return 0
    }
    epsilon:junoenv blyth$ 



    O[blyth@localhost junotop]$ boost-
    O[blyth@localhost junotop]$ boost-pc-path
    /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/pkgconfig/Boost.pc
    O[blyth@localhost junotop]$ 



Try without opticks-foreign-pc:: 

    1538 opticks-full-externals()
    1539 {
    1540     local msg="=== $FUNCNAME :"
    1541     echo $msg START $(date)
    1542     local rc
    1543 
    1544     echo $msg installing the below externals into $(opticks-prefix)/externals
    1545     opticks-externals
    1546     opticks-externals-install
    1547     rc=$?
    1548     [ $rc -ne 0 ] && return $rc
    1549 
    1550     echo $msg config-ing the preqs 
    1551     opticks-preqs
    1552     opticks-preqs-pc
    1553     rc=$?
    1554     [ $rc -ne 0 ] && return $rc
    1555 
    1556     echo $msg config-ing the foreign
    1557     opticks-foreign
    1558     #opticks-foreign-pc
    1559     rc=$?
    1560     [ $rc -ne 0 ] && return $rc
    1561 
    1562     echo $msg DONE $(date)
    1563     return 0
    1564 }


bash junoenv opticks : warnings and errors
---------------------------------------------


sysrap::

    === om-one-or-all install : sysrap          /home/blyth/opticks/sysrap                                   /data/blyth/junotop/ExternalLibs/opticks/head/build/sysrap   
    -- The C compiler identification is GNU 8.3.0
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/gcc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring SysRap
    CMake Warning (dev) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/FindCUDA.cmake:723 (option):
      Policy CMP0077 is not set: option() honors normal variables.  Run "cmake
      --help-policy CMP0077" for policy details.  Use the cmake_policy command to
      set the policy and suppress this warning.

      For compatibility with older versions of CMake, option is clearing the
      normal variable 'CUDA_PROPAGATE_HOST_FLAGS'.
    Call Stack (most recent call first):
      CMakeLists.txt:24 (find_package)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    CMake Warning (dev) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/FindCUDA.cmake:729 (option):
      Policy CMP0077 is not set: option() honors normal variables.  Run "cmake
      --help-policy CMP0077" for policy details.  Use the cmake_policy command to
      set the policy and suppress this warning.

      For compatibility with older versions of CMake, option is clearing the
      normal variable 'CUDA_VERBOSE_BUILD'.
    Call Stack (most recent call first):
      CMakeLists.txt:24 (find_package)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed




cudarap::

    === om-visit-one : cudarap         /home/blyth/opticks/cudarap                                  /data/blyth/junotop/ExternalLibs/opticks/head/build/cudarap  
    === om-one-or-all install : cudarap         /home/blyth/opticks/cudarap                                  /data/blyth/junotop/ExternalLibs/opticks/head/build/cudarap  
    -- The C compiler identification is GNU 8.3.0
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working C compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/gcc - skipped
    -- Detecting C compile features
    -- Detecting C compile features - done
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Configuring CUDARap
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      CMakeLists.txt:15 (find_package)


    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
    -- Looking for pthread_create in pthreads


    [100%] Built target cfloat4x4Test
    -- Configuring CUDARap
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      CMakeLists.txt:15 (find_package)


    -- Use examples/UseOpticksCUDA/CMakeLists.txt for testing FindOpticksCUDA.cmake
    --   CUDA_TOOLKIT_ROOT_DIR   : /usr/local/cuda 
    --   CUDA_SDK_ROOT_DIR       : CUDA_SDK_ROOT_DIR-NOTFOUND 
    --   CUDA_VERSION            : 10.1 



    -- Configuring ThrustRap
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
    -- Looking for pthread_create in pthreads
    -- Looking for pthread_create in pthreads - not found
    -- Looking for pthread_create in pthread
    -- Looking for pthread_create in pthread - found
    -- Found Threads: TRUE  
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:18 (find_dependency)
      CMakeLists.txt:14 (find_package)


    -- Found CUDA: /usr/local/cuda (found version "10.1") 
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:20 (find_dependency)
      CMakeLists.txt:14 (find_package)


    -- bcm_auto_pkgconfig_each LIB:Threads::Threads : MISSING LIB_PKGCONFIG_NAME 
    -- Configuring ThrustRapTest
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /data/blyth/junotop/ExternalLibs/opticks/head/build/thrustrap
    === om-make-one : thrustrap       /home/blyth/opticks/thrustrap                                /data/blyth/junotop/ExternalLibs/opticks/head/build/thrustrap 
    [ 10%] Building NVCC (Device) object CMakeFiles/ThrustRap.dir/ThrustRap_generated_TBufPair_.cu.o
    [ 10%] Building NVCC (Device) object CMakeFiles/ThrustRap.dir/ThrustRap_generated_TUtil_.cu.o
    [ 10%] Building NVCC (Device) object CMakeFiles/ThrustRap.dir/ThrustRap_generated_TRngBuf_.cu.o



    -- Configuring ThrustRap
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:18 (find_dependency)
      CMakeLists.txt:14 (find_package)


    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:20 (find_dependency)
      CMakeLists.txt:14 (find_package)


    -- bcm_auto_pkgconfig_each LIB:Threads::Threads : MISSING LIB_PKGCONFIG_NAME 
    -- Configuring ThrustRapTest
    -- Configuring done


    -- Found Threads: TRUE  
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:18 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      CMakeLists.txt:19 (find_package)


    -- Found CUDA: /usr/local/cuda (found version "10.1") 
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:20 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      CMakeLists.txt:19 (find_package)


    -- flags:+ANGULAR_ENABLED,+WAY_ENABLED outfile:/data/blyth/junotop/ExternalLibs/opticks/head/build/optixrap/generate_+ANGULAR_ENABLED,+WAY_ENABLED.cu
    -- flags:+ANGULAR_ENABLED,-WAY_ENABLED outfile:/data/blyth/junotop/ExternalLibs/opticks/head/build/optixrap/generate_+ANGULAR_ENABLED,-WAY_ENABLED.cu


    [100%] Built target reemissionTest
    -- Configuring OptiXRap
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- /home/blyth/opticks/cmake/Modules/FindOptiX.cmake : OptiX_VERBOSE     : ON 
    -- /home/blyth/opticks/cmake/Modules/FindOptiX.cmake : OptiX_INSTALL_DIR : /home/blyth/local/opticks/externals/OptiX_650 
    -- FindOptiX.cmake.OptiX_MODULE          : /home/blyth/opticks/cmake/Modules/FindOptiX.cmake
    -- FindOptiX.cmake.OptiX_FOUND           : YES
    -- FindOptiX.cmake.OptiX_VERSION         : 60500
    -- FindOptiX.cmake.OptiX_INCLUDE         : /home/blyth/local/opticks/externals/OptiX_650/include
    -- FindOptiX.cmake.OptiX_LIBDIR          : /home/blyth/local/opticks/externals/OptiX_650/lib64
    -- FindOptiX.cmake.optix_LIBRARY         : /home/blyth/local/opticks/externals/OptiX_650/lib64/liboptix.so
    -- FindOptiX.cmake.optixu_LIBRARY        : /home/blyth/local/opticks/externals/OptiX_650/lib64/liboptixu.so
    -- FindOptiX.cmake.optix_prime_LIBRARY   : /home/blyth/local/opticks/externals/OptiX_650/lib64/liboptix_prime.so
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:18 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      CMakeLists.txt:19 (find_package)


    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:20 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      CMakeLists.txt:19 (find_package)


    -- flags:+ANGULAR_ENABLED,+WAY_ENABLED outfile:/data/blyth/junotop/ExternalLibs/opticks/head/build/optixrap/generate_+ANGULAR_ENABLED,+WAY_ENABLED.cu
    -- flags:+ANGULAR_ENABLED,-WAY_ENABLED outfile:/data/blyth/junotop/ExternalLibs/opticks/head/build/optixrap/generate_+ANGULAR_ENABLED,-W


    -- Configuring OKOP
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.


    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- Looking for pthread.h
    -- Looking for pthread.h - found
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD
    -- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
    -- Looking for pthread_create in pthreads
    -- Looking for pthread_create in pthreads - not found
    -- Looking for pthread_create in pthread
    -- Looking for pthread_create in pthread - found
    -- Found Threads: TRUE  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-gencode=arch=compute_70,code=sm_70;-std=c++11;-O2;--use_fast_math;-Xcudafe --diag_suppress=esa_on_defaulted_function_ignored  
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:18 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/optixrap/optixrap-config.cmake:14 (find_dependency)
      CMakeLists.txt:12 (find_package)


    -- Found CUDA: /usr/local/cuda (found version "10.1") 
    -- FindOpticksCUDA.cmake:with-policy-CMP0077
    CMake Deprecation Warning at /home/blyth/opticks/cmake/Modules/FindOpticksCUDA.cmake:33 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cudarap/cudarap-config.cmake:20 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/thrustrap/thrustrap-config.cmake:18 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/optixrap/optixrap-config.cmake:14 (find_dependency)
      CMakeLists.txt:12 (find_package)


    -- OpticksCUDAFlags.cmake : COMPUTE_CAPABILITY : 70
    -- OpticksCUDAFlags.cmake : CUDA_NVCC_FLAGS    : -Xcompiler -fPIC;-genc



    -- OpticksCompilationFlags.cmake : CMAKE_CXX_STANDARD_REQUIRED : on 
    -- Configuring done
    CMake Warning (dev) at tests/CMakeLists.txt:17 (add_executable):
      Policy CMP0115 is not set: Source file extensions must be explicit.  Run
      "cmake --help-policy CMP0115" for policy details.  Use the cmake_policy
      command to set the policy and suppress this warning.

      File:

        /home/blyth/opticks/okop/tests/dirtyBufferTest.cc
    This warning is for project developers.  Use -Wno-dev to suppress it.

    CMake Warning (dev) at tests/CMakeLists.txt:17 (add_executable):
      Policy CMP0115 is not set: Source file extensions must be explicit.  Run
      "cmake --help-policy CMP0115" for policy details.  Use the cmake_policy
      command to set the policy and suppress this warning.

      File:

        /home/blyth/opticks/okop/tests/compactionTest.cc
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- Generating done
    -- Build files have been written to: /data/blyth/junotop/ExternalLibs/opticks/head/build/okop


    -- Configuring OKOP
    CMake Deprecation Warning at CMakeLists.txt:7 (cmake_policy):
      The OLD behavior for policy CMP0077 will be removed from a future version
      of CMake.

      The cmake-policies(7) manual explains that the OLD behaviors of all
      policies are deprecated and that a policy should be set to OLD only under
      specific short-term circumstances.  Projects should be ported to the NEW
      behavior and not rely on setting a policy to OLD.



    [ 69%] Building CXX object tests/CMakeFiles/X4MaterialPropertyVectorTest.dir/X4MaterialPropertyVectorTest.cc.o
    [ 70%] Building CXX object tests/CMakeFiles/X4MaterialPropertiesTableTest.dir/X4MaterialPropertiesTableTest.cc.o
    [ 71%] Linking CXX executable CLHEPVersionInteger
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/CLHEPVersionInteger] Error 1
    make[1]: *** [tests/CMakeFiles/CLHEPVersionInteger.dir/all] Error 2
    make[1]: *** Waiting for unfinished jobs....
    [ 71%] Linking CXX executable X4GeometryMakerTest
    [ 71%] Linking CXX executable X4DumpTest
    [ 72%] Linking CXX executable X4NameOrderTest
    [ 73%] Linking CXX executable X4EntityTest
    [ 73%] Linking CXX executable X4Test
    [ 74%] Linking CXX executable X4MaterialWaterStandaloneTest
    [ 75%] Linking CXX executable X4IntersectSolidTest
    [ 76%] Linking CXX executable X4MeshTest
    [ 77%] Linking CXX executable X4PhysicsVectorTest
    [ 78%] Linking CXX executable X4SolidListTest
    [ 78%] Linking CXX executable X4IntersectVolumeTest
    [ 79%] Linking CXX executable X4MaterialWaterTest
    [ 79%] Linking CXX executable X4MaterialPropertyVectorTest
    [ 80%] Linking CXX executable X4MaterialTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4DumpTest] Error 1
    [ 81%] Linking CXX executable X4MaterialTableTest
    make[1]: *** [tests/CMakeFiles/X4DumpTest.dir/all] Error 2
    make[2]: *** [tests/X4GeometryMakerTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4GeometryMakerTest.dir/all] Error 2
    [ 82%] Linking CXX executable PhysicsFreeVectorTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4Test] Error 1
    make[1]: *** [tests/CMakeFiles/X4Test.dir/all] Error 2
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4EntityTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4EntityTest.dir/all] Error 2
    [ 83%] Linking CXX executable X4GDMLReadDefineTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4NameOrderTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4NameOrderTest.dir/all] Error 2
    [ 84%] Linking CXX executable X4SolidLoadTest
    [ 85%] Linking CXX executable X4MaterialPropertiesTableTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MaterialWaterStandaloneTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MaterialWaterStandaloneTest.dir/all] Error 2
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    [ 85%] Linking CXX executable X4PhysicalConstantsTest
    make[2]: *** [tests/X4IntersectSolidTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4IntersectSolidTest.dir/all] Error 2
    [ 86%] Linking CXX executable X4ThreeVectorTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MeshTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MeshTest.dir/all] Error 2
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4SolidListTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4SolidListTest.dir/all] Error 2
    [ 87%] Linking CXX executable X4CSGTest
    [ 87%] Linking CXX executable X4PhysicalVolumeTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4IntersectVolumeTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4IntersectVolumeTest.dir/all] Error 2
    [ 88%] Linking CXX executable X4AffineTransformTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4PhysicsVectorTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4PhysicsVectorTest.dir/all] Error 2
    [ 89%] Linking CXX executable X4GDMLReadStructureTest
    [ 90%] Linking CXX executable G4MaterialPropertyVectorTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MaterialWaterTest] Error 1
    make[2]: *** [tests/X4MaterialPropertyVectorTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MaterialWaterTest.dir/all] Error 2
    make[1]: *** [tests/CMakeFiles/X4MaterialPropertyVectorTest.dir/all] Error 2
    [ 91%] Linking CXX executable X4GDMLReadStructure2Test
    [ 93%] Linking CXX executable X4PolyconeTest
    [ 93%] Linking CXX executable X4ScintillationTest
    [ 94%] Linking CXX executable X4SolidExtentTest
    [ 95%] Linking CXX executable X4Transform3DTest
    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/X4MaterialTest] Error 1
    make[1]: *** [tests/CMakeFiles/X4MaterialTest.dir/all] Error 2




/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4MTHepRandom.hh::

    114   static CLHEP::HepRandomEngine * getTheEngine();
    115   // Returns a pointer to the underlying algorithm object.




Some macro setting that Geant4 is sensitive to needs to match the 
setting used for Geant4 users compilation 

::

    epsilon:include blyth$ g4-cls Randomize
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02
    vi -R source/externals/clhep/include/CLHEP/Random/Randomize.h source/global/HEPRandom/include/Randomize.hh
    2 files to edit
    epsilon:include blyth$ 


    O[blyth@localhost lib64]$ nm libG4global.so | c++filt | grep Random
                     U CLHEP::HepRandom::getTheEngine()
                     U CLHEP::HepRandom::createInstance()


::      

     32 #include <CLHEP/Random/Randomize.h>
     33 
     34 #if __clang__
     35   #if ((defined(G4MULTITHREADED) && !defined(G4USE_STD11)) || \
     36       !__has_feature(cxx_thread_local)) || !__has_feature(c_atomic)
     37     #define CLANG_NOSTDTLS
     38   #endif
     39 #endif
     40 
     41 #if (defined(G4MULTITHREADED) && \
     42     (!defined(G4USE_STD11) || (defined(CLANG_NOSTDTLS) || defined(__INTEL_COMPILER))))
     43 
     44 // MT needs special Random Number distribution classes
     45 //
     46 #include "G4MTHepRandom.hh"
     47 #include "G4MTRandBit.hh"
     48 #include "G4MTRandExponential.hh"
     49 #include "G4MTRandFlat.hh"
     50 #include "G4MTRandGamma.hh"
     51 #include "G4MTRandGauss.hh"
     52 #include "G4MTRandGaussQ.hh"
     53 #include "G4MTRandGeneral.hh"
     54 
     55 // NOTE: G4RandStat MT-version is missing, but actually currently
     56 // never used in the G4 source
     57 //
     58 #define G4RandFlat G4MTRandFlat
     59 #define G4RandBit G4MTRandBit
     60 #define G4RandGamma G4MTRandGamma
     61 #define G4RandGauss G4MTRandGaussQ
     62 #define G4RandExponential G4MTRandExponential
     63 #define G4RandGeneral G4MTRandGeneral
     64 #define G4Random G4MTHepRandom
     65 
     66 #define G4UniformRand() G4MTHepRandom::getTheEngine()->flat()
     67 //
     68 //#include "G4UniformRandPool.hh"
     69 //#define G4UniformRand() G4UniformRandPool::flat()
     70 // Currently not be used in G4 source
     71 //
     72 #define G4RandFlatArray G4MTRandFlat::shootArray
     73 #define G4RandFlatInt G4MTRandFlat::shootInt
     74 #define G4RandGeneralTmp G4MTRandGeneral
     75 
     76 #else // Sequential mode or supporting C++11 standard
     77 
     78 // Distributions used ...
     79 //
     80 #include <CLHEP/Random/RandFlat.h>
     81 #include <CLHEP/Random/RandBit.h>
     82 #include <CLHEP/Random/RandGamma.h>
     83 #include <CLHEP/Random/RandGaussQ.h>



::

    epsilon:include blyth$ opticks-f G4MULTITHREADED
    ./cfg4/tests/CMakeLists.txt:    #add_compile_definitions(G4MULTITHREADED)
    ./cfg4/tests/G4OrbTest.cc:     #if ((defined(G4MULTITHREADED) && !defined(G4USE_STD11)) || \
    ./cfg4/tests/G4OrbTest.cc:   #if defined(G4MULTITHREADED) 
    ./cfg4/tests/G4OrbTest.cc:   ss << " G4MULTITHREADED " ;  
    ./cfg4/tests/G4OrbTest.cc:   ss << " NOT-G4MULTITHREADED " ;  
    ./cfg4/tests/G4OrbTest.cc:   #if (defined(G4MULTITHREADED) && \
    ./cfg4/tests/G4OrbTest.cc:   ss << " G4MULTITHREADED and ( !G4USE_STD11  or CLANG_NOSTDTLS or __INTEL_COMPILER ) " ;  
    ./cfg4/tests/G4OrbTest.cc:   ss << " NOT [  G4MULTITHREADED and ( !G4USE_STD11  or CLANG_NOSTDTLS or __INTEL_COMPILER ) ] " ;  
    ./examples/UseGeant4Engine/CMakeLists.txt:#add_compile_definitions(G4MULTITHREADED)
    ./examples/Geant4/OpNovice/OpNovice.cc:#ifdef G4MULTITHREADED
    ./examples/Geant4/OpNovice/OpNovice.cc:#ifdef G4MULTITHREADED
    ./examples/Geant4/OpNovice/OpNovice.cc:#ifdef G4MULTITHREADED
    ./examples/Geant4/OpNovice/OpNovice.cc:#ifdef G4MULTITHREADED
    epsilon:opticks blyth$ 



offline/cmake/JUNODependencies.cmake::

     49 ## CLHEP
     50 include_directories($ENV{JUNO_EXTLIB_CLHEP_HOME}/include)
     51 find_library(CLHEP_LIBRARIES CLHEP
     52     HINTS $ENV{JUNO_EXTLIB_CLHEP_HOME}/lib
     53 )
     54 link_directories($ENV{JUNO_EXTLIB_CLHEP_HOME}/lib)
     55 
     56 ## Geant4
     57 find_package(Geant4 REQUIRED ui_all vis_all)
     58 include_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/include/geant4)
     59 find_program(GEANT4_CONFIG_EXECUTABLE geant4-config
     60     PATHS $ENV{JUNO_EXTLIB_Geant4_HOME}/bin)
     61 execute_process(
     62     COMMAND ${GEANT4_CONFIG_EXECUTABLE} --cflags
     63     OUTPUT_VARIABLE GEANT4_CFLAGS
     64     OUTPUT_STRIP_TRAILING_WHITESPACE
     65 )
     66 add_definitions(${GEANT4_CFLAGS})
     67 
     68 execute_process(
     69     COMMAND ${GEANT4_CONFIG_EXECUTABLE} --libs
     70     OUTPUT_VARIABLE GEANT4_LIBRARIES
     71     OUTPUT_STRIP_TRAILING_WHITESPACE
     72 )
     73 link_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/lib)


::

    O[blyth@localhost lib64]$ geant4-config --cflags
    -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -I/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/CLHEP/2.4.1.0/include
    O[blyth@localhost lib64]$ 


To get extg4 test executables to compile with reused Geant4 from cvmfs have to add compile definitions::

    G4MULTITHREADED G4USE_STD11 






