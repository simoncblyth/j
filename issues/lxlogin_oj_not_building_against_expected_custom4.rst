FIXED : lxlogin_oj_not_building_against_expected_custom4
===========================================================


HMM: this is todo with the fragile path rewriting..

Fixed by updating stale local_c4_prefix_default - also added 
staleness check to catch it sooner next time.


::

    L[blyth@lxlogin004 ~]$ ljclient ljbb0c
    /hpcfs/juno/junogpu/blyth/j/local.sh ljclient running fn ljbb0c with JUNO_OPTICKS_CONFIG Client
    Using fftw3 as the backend for fftw3-proxy
    Setup Official junosw (CMake version)
              BASH_SOURCE : /hpcfs/juno/junogpu/blyth/j/JUNOTOP/JUNOTOP_change_paths.sh 
             BASH_VERSION : 5.1.8(1)-release 
                 FUNCNAME : JUNOTOP_change_paths 
                        1 : custom4 
                        2 : /hpcfs/juno/junogpu/blyth/local/custom4_Debug/0.1.9 
                    xname : custom4 
                   _xhome :  
                    xhome : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8 
                    yhome : /hpcfs/juno/junogpu/blyth/local/custom4_Debug/0.1.9 
                   change : YES 
    /hpcfs/juno/junogpu/blyth/j/local.sh : PREFIX_RELDIR_WITH_JUNO_OPTICKS_CONFIG 1
    /hpcfs/juno/junogpu/blyth/j/local.sh : JUNO_OPTICKS_CONFIG Client
    /hpcfs/juno/junogpu/blyth/j/local.sh : JUNO_OFFLINE_RELDIR Client_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    /hpcfs/juno/junogpu/blyth/j/local.sh : JUNO_OFFLINE_BLDDIR /hpcfs/juno/junogpu/blyth/junosw/build/Client_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    /hpcfs/juno/junogpu/blyth/j/local.sh : JUNO_OFFLINE_INSTALLDIR /hpcfs/juno/junogpu/blyth/junosw/InstallArea/Client_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV
    === opticks-setup-        add     append                 PATH /usr/local/cuda-12.4/bin
    === opticks-setup-        add     append                 PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/bin
    === opticks-setup-        add     append                 PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/lib
    === opticks-setup-        add     append           PYTHONPATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/py
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    === opticks-setup-      nodir     append      PKG_CONFIG_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/lib64/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals/lib64/pkgconfig
    === opticks-setup-        add     append      LD_LIBRARY_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/lib64
    === opticks-setup-        add     append      LD_LIBRARY_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals/lib64
    === opticks-setup-      nodir     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib64
    /hpcfs/juno/junogpu/blyth/local/opticks_Client/bashrc - USE DETECTED GEANT4 ENVIRONMENT
    oj_build is a function
    oj_build () 
    { 
        : ~/j/local.sh;
        local vv="";
        local d0=$(date);
        vv="$vv d0";
        [ -n "$OJ_BUILD_CLEAN" ] && oj_build_clean;
        oj_build_info;
        oj_build_pre;










    -- PACKAGE_FIND_VERSION_MAX_TWEAK :  
    -- PACKAGE_FIND_VERSION_MAX_COUNT :  
    -- PACKAGE_FIND_VERSION_COMPLETE  :   
    -- CMAKE_CURRENT_LIST_FILE     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4ConfigVersion.cmake    
    -- PACKAGE_VERSION             : 0.1.8            
    -- PACKAGE_VERSION_EXACT       :       
    -- PACKAGE_VERSION_COMPATIBLE  : TRUE 
    -- PACKAGE_VERSION_UNSUITABLE  :  
    -- Custom4_VERBOSE       : ON 
    -- Custom4_FOUND         : YES 
    -- Custom4_VERSION       : 0.1.8 
    -- Custom4_PREFIX        : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8 
    -- Custom4_INCLUDE_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_INCLUDE_DIRS  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_CFLAGS        : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_DEFINITIONS   : -DWITH_CUSTOM4 
    -- Custom4_LIBRARY_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 
    -- Custom4_LIBRARY_PATH  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- CUSTOM4_LIBRARIES   : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4
    -- Found SQLite3: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5/include (found version "3.38.5")
    -- Found Python: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bin/python (found suitable version "3.11.10", minimum required is "3.11.10") found components: Interpreter
    -- Found SNiPER: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/cmake/SNiPER/SNiPERConfig.cmake
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_VERBOSE     : YES 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : ENV(OPTICKS_PREFIX) : /hpcfs/juno/junogpu/blyth/local/opticks_Client 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : OPTICKS_PREFIX      : /hpcfs/juno/junogpu/blyth/local/opticks_Client 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /hpcfs/juno/junogpu/blyth/junosw/cmake/legacy/Modules/ 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/InstallArea 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/mt.sniper/InstallArea 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/healpix/3.83 
    -- /hpcfs/juno/junogpu/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3 



CMAKE_PREFIX_PATH path changing did not work somehow on lxlogin::

    L[blyth@lxlogin004 ~]$ ljclient ljbb0c
    ...

    - Custom4_LIBRARY_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 
    -- Custom4_LIBRARY_PATH  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- CUSTOM4_LIBRARIES   : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4
    ^C
    L[blyth@lxlogin004 junosw]$ echo $CMAKE_PREFIX_PATH | tr ":" "\n"
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/InstallArea
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/mt.sniper/InstallArea
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/healpix/3.83
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libmore/0.8.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gemini/juno_master_20260408
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gibuu/r2023_02_juno
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/talys/1.95
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/nuwro/21.09.2
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/genie/3.04.02
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HepMC/2.06.11
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/xrootd/5.7.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/CLHEP/2.4.7.1
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/tbb/2020.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pythia6/6.4.28
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/LHAPDF/6.3.0
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libxml2/2.9.12
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/log4cpp/1.1.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HDF5/1.14.3
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/frontier/2.10.2
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pacparser/1.4.2
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-cpp/1.1.12
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-c/6.1.9
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/eigen/3.4.0
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/fftw3/3.3.10
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Xercesc/3.2.4
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libyaml/0.2.4
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-numpy/1.26.4
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-cython/3.0.8
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-pip/23.3.1
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-setuptools/69.5.1
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Cmake/3.30.5
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/git-lfs/3.4.1
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Git/2.46.2

    /hpcfs/juno/junogpu/blyth/local/opticks_Client
    /hpcfs/juno/junogpu/blyth/local/opticks_Client/externals
    /cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    L[blyth@lxlogin004 junosw]$ 



HUH, get same issue on workstation. Recent change must have broken the fragile path changing::


    -- PACKAGE_FIND_VERSION_MAX       :        
    -- PACKAGE_FIND_VERSION_MAX_MAJOR :  
    -- PACKAGE_FIND_VERSION_MAX_MAXOR :  
    -- PACKAGE_FIND_VERSION_MAX_PATCH :  
    -- PACKAGE_FIND_VERSION_MAX_TWEAK :  
    -- PACKAGE_FIND_VERSION_MAX_COUNT :  
    -- PACKAGE_FIND_VERSION_COMPLETE  :   
    -- CMAKE_CURRENT_LIST_FILE     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4ConfigVersion.cmake    
    -- PACKAGE_VERSION             : 0.1.8            
    -- PACKAGE_VERSION_EXACT       :       
    -- PACKAGE_VERSION_COMPATIBLE  : TRUE 
    -- PACKAGE_VERSION_UNSUITABLE  :  
    -- Custom4_VERBOSE       : ON 
    -- Custom4_FOUND         : YES 
    -- Custom4_VERSION       : 0.1.8 
    -- Custom4_PREFIX        : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8 
    -- Custom4_INCLUDE_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_INCLUDE_DIRS  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_CFLAGS        : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4 
    -- Custom4_DEFINITIONS   : -DWITH_CUSTOM4 
    -- Custom4_LIBRARY_DIR   : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 
    -- Custom4_LIBRARY_PATH  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- CUSTOM4_LIBRARIES   : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4
    -- Found SQLite3: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5/include (found version "3.38.5")
    -- Found Python: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bin/python (found suitable version "3.11.10", minimum required is "3.11.10") found components: Interpreter
    -- Found SNiPER: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/cmake/SNiPER/SNiPERConfig.cmake
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_VERBOSE     : YES 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : ENV(OPTICKS_PREFIX) : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : OPTICKS_PREFIX      : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /home/blyth/junosw/cmake/legacy/Modules/ 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /data1/blyth/local/opticks_Client/cmake/Modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/mt.sniper/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/healpix/3.83 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libmore/0.8.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gemini/juno_master_20260408 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gibuu/r2023_02_juno 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/talys/1.95 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/nuwro/21.09.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/genie/3.04.02 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HepMC/2.06.11 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/xrootd/5.7.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/CLHEP/2.4.7.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/tbb/2020.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pythia6/6.4.28 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/LHAPDF/6.3.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libxml2/2.9.12 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/log4cpp/1.1.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HDF5/1.14.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/frontier/2.10.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pacparser/1.4.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-cpp/1.1.12 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-c/6.1.9 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/eigen/3.4.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/fftw3/3.3.10 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Xercesc/3.2.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libyaml/0.2.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-numpy/1.26.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-cython/3.0.8 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-pip/23.3.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-setuptools/69.5.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Cmake/3.30.5 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/git-lfs/3.4.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Git/2.46.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client/externals 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/opticks.ihep.ac.cn/external/OptiX_800 
    -- cmake/Modules/OpticksCUDAFlags.cmake : using default OPTICKS_CUDA_NVCC_DIALECT variable c++17
    -- CMAKE_CURRENT_LIST_FILE        : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4ConfigVersion.cmake        
    -- PACKAGE_FIND_NAME              : Custom4              
    -- PACKAGE_FIND_VERSION           :            
    -- PACKAGE_FIND_VERSION_MAJOR     : 0     
    -- PACKAGE_FIND_VERSION_MINOR     : 0     
    -- PACKAGE_FIND_VERSION_PATCH     : 0     
    -- PACKAGE_FIND_VERSION_TWEAK     : 0     
    -- PACKAGE_FIND_VERSION_COUNT     : 0     
    -- PACKAGE_FIND_VERSION_RANGE     :      
    -- PACKAGE_FIND_VERSION_RANGE_MIN :  
    -- PACKAGE_FIND_VERSION_RANGE_MAX :  
    -- PACKAGE_FIND_VERSION_MIN       :        
    -- PACKAGE_FIND_VERSION_MIN_MAJOR :  
    -- PACKAGE_FIND_VERSION_MIN_MINOR :  
    -- PACKAGE_FIND_VERSION_MIN_PATCH :  
    -- PACKAGE_FIND_VERSION_MIN_TWEAK :  
    -- PACKAGE_FIND_VERSION_MIN_COUNT :  
    -- PACKAGE_FIND_VERSION_MAX       :        



Probably the default has changed causing fail to change::

    A[blyth@localhost j]$ local_c4_prefix
    /data1/blyth/local/custom4_Debug/0.1.9

    A[blyth@localhost j]$ local_c4_prefix_default
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8


YEP: default now looks to be::

    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8


