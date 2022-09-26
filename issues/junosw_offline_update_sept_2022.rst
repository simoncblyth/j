junosw_offline_update_sept_2022
==================================



::

    N[blyth@localhost ~]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/
    total 137
     5 drwxr-xr-x. 27 cvmfs cvmfs  4096 Sep 16 10:40 junosw
     1 drwxr-xr-x.  8 cvmfs cvmfs    28 Sep 16 10:39 .
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 bashrc.sh
     1 -rw-r--r--.  1 cvmfs cvmfs   908 Sep 12 21:42 setup.csh
     1 -rw-r--r--.  1 cvmfs cvmfs   911 Sep 12 21:42 setup.sh
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 tcshrc.csh
     1 drwxr-xr-x.  7 cvmfs cvmfs   207 Sep 12 21:22 mt.sniper
     5 drwxr-xr-x. 12 cvmfs cvmfs  4096 Sep 12 21:22 sniper
     1 drwxr-xr-x.  8 cvmfs cvmfs   138 Sep 12 20:38 data
    32 -rw-r--r--.  1 cvmfs cvmfs 32036 Sep 12 20:26 sniper-v0.9.1.tar.gz
    79 -rw-r--r--.  1 cvmfs cvmfs 80884 Sep 12 20:26 sniper-v2.2.2.tar.gz
     1 drwxrwxr-x.  3 cvmfs cvmfs    29 Sep 12 18:30 ..
     1 -rw-r--r--.  1 cvmfs cvmfs     0 Sep 12 18:30 .cvmfscatalog
     5 drwxr-xr-x.  9 cvmfs cvmfs  4096 Sep 12 18:20 junoenv
     1 drwxr-xr-x. 36 cvmfs cvmfs    27 Sep 12 18:19 ExternalLibs
    N[blyth@localhost ~]$ 


::

    bash junoenv libs reuse allpkgs


::

    N[blyth@localhost blyth]$ mv junotop junotop_old
    N[blyth@localhost blyth]$ mkdir junotop




WIP : get setup into git and new working approach
---------------------------------------------------

::

    epsilon:junotop blyth$ mv junoenv junoenv_svn 
    epsilon:junotop blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
    Cloning into 'junoenv'...
    remote: Enumerating objects: 313, done.
    remote: Total 313 (delta 0), reused 0 (delta 0), pack-reused 313
    Receiving objects: 100% (313/313), 153.61 KiB | 131.00 KiB/s, done.
    Resolving deltas: 100% (170/170), done.
    epsilon:junotop blyth$ 

::

    045 function junoenv-offline-checkout {
     46     # checkout all code
     47     local msg="==== $FUNCNAME: "
     48     local repourl=$1; shift
     49     local dstname=$1; shift
     50     local revision=$1; shift
     51 
     52     echo $msg checkout the code $repourl 
     53     # check
     54     git clone $repourl $dstname || exit -1
     55     cd $dstname && git checkout $revision || exit -1
     56 }


    106 function junoenv-offline {
    107     local msg="=== $FUNCNAME: "
    108     # the main handler in this script
    109     local branchname=${1:-$(junoenv-offline-default-branch)}
    110     local revision=${2:-}
    111     # check version
    112     junoenv-offline-version $branchname
    113     if [ "$?" != "0" ]; then
    114         echo $msg branchesname ret: $?
    115         return 1
    116     fi
    117 
    118 
    119     local url=$(junoenv-offline-url $branchname)
    120     echo $msg $?
    121     echo $msg URL: $url
    122     # change directory to $JUNOTOP
    123     pushd $JUNOTOP >& /dev/null
    124     junoenv-offline-checkout $url $(junoenv-offline-name) $revision
    125     junoenv-offline-preq
    126     junoenv-offline-compile
    127     popd
    128 
    129 }




libmore-data fail : judged harmless as coming from cvmfs link anyhow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HUH: libmore-data-install trying to rsync to cvmfs? ::

    === juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: After source: libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: status: 0 libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused libmore-data
    === junoenv-external-libs: juno-ext-libs-all libmore-data
    ==== juno-ext-libs-get:
    [libmore-data-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: ensdf-files-20140630.tar already exists
    ==== juno-ext-libs-conf:
    ==== juno-ext-libs-make:
    ==== juno-ext-libs-install:
    [libmore-data-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-libmore-data-install-
    [libmore-data-install] sending incremental file list
    [libmore-data-install] rsync: chgrp "/data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/." failed: Read-only file system (30)
    [libmore-data-install] ./
    [libmore-data-install] ar001.ens.bz2
    [libmore-data-install] ar001h.ens.bz2
    [libmore-data-install] ar001nn.ens.bz2
    [libmore-data-install] ar002.ens.bz2


    Last login: Fri Sep 23 19:08:47 2022 from lxslc714.ihep.ac.cn
    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/
    total 24458
    113 drwxr-xr-x. 2 cvmfs cvmfs 114688 Mar  4  2022 .
      4 -rw-r--r--. 1 cvmfs cvmfs   3529 Mar  4  2022 ar28614.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1110 Mar  4  2022 ar286cn.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2941 Mar  4  2022 ar28714.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1875 Mar  4  2022 ar28715.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2809 Mar  4  2022 ar28814.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1942 Mar  4  2022 ar28815.ens.bz2
      5 -rw-r--r--. 1 cvmfs cvmfs   4791 Mar  4  2022 ar28914.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2396 Mar  4  2022 ar28915.ens.bz2

The 0.8.3 is link to cvmfs::

    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/
    total 4
    4 drwxrwxr-x. 38 blyth blyth 4096 Jul 25 18:30 ..
    0 drwxrwxr-x.  2 blyth blyth   19 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 0.8.3 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/libmore/0.8.3
    N[blyth@localhost ~]$ 

Note that libonnxruntime has large number of github submodules::

    == junoenv-external-libs: juno-ext-libs-check-is-reused libonnxruntime
    === junoenv-external-libs: juno-ext-libs-all libonnxruntime
    ==== juno-ext-libs-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get: clone https://github.com/microsoft/onnxruntime
    [libonnxruntime-conf] Cloning into 'libonnxruntime-1.11.1'...
    [libonnxruntime-conf] Submodule 'cmake/external/FP16' (https://github.com/Maratyszcza/FP16.git) registered for path 'cmake/external/FP16'
    [libonnxruntime-conf] Submodule 'cmake/external/SafeInt/safeint' (https://github.com/dcleblanc/SafeInt.git) registered for path 'cmake/external/SafeInt/safeint'
    [libonnxruntime-conf] Submodule 'cmake/external/XNNPACK' (https://github.com/google/XNNPACK.git) registered for path 'cmake/external/XNNPACK'
    [libonnxruntime-conf] Submodule 'cmake/external/cub' (https://github.com/NVlabs/cub.git) registered for path 'cmake/external/cub'
    [libonnxruntime-conf] Submodule 'cmake/external/cxxopts' (https://github.com/jarro2783/cxxopts.git) registered for path 'cmake/external/cxxopts'
    [libonnxruntime-conf] Submodule 'cmake/external/date' (https://github.com/HowardHinnant/date.git) registered for path 'cmake/external/date'
    [libonnxruntime-conf] Submodule 'cmake/external/dlpack' (https://github.com/dmlc/dlpack.git) registered for path 'cmake/external/dlpack'
    [libonnxruntime-conf] Submodule 'cmake/external/eigen' (https://gitlab.com/libeigen/eigen.git) registered for path 'cmake/external/eigen'
    [libonnxruntime-conf] Submodule 'cmake/external/emsdk' (https://github.com/emscripten-core/emsdk.git) registered for path 'cmake/external/emsdk'
    [libonnxruntime-conf] Submodule 'cmake/external/flatbuffers' (https://github.com/google/flatbuffers.git) registered for path 'cmake/external/flatbuffers'

Even though it looks to have hung checking ps shows that some progress is being made, with movement between submodules::

    N[blyth@localhost ~]$ ps aux | grep blyth




fail : bash junoenv sniper
----------------------------

::

    N[blyth@localhost junoenv]$ source $JUNOTOP/bashrc.sh
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ bash junoenv sniper
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
    == setup-juno-basic-preq: ================================================================
    == setup-juno-sniper
    === junoenv-sniper: 0
    === junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
    === junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:00:01 --:--:--     0
      0     0    0 80884    0     0  31319      0 --:--:--  0:00:02 --:--:-- 85410
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-check-preq: Pre Requirement Check
    ==== junoenv-sniper-check-preq: source /data/blyth/junotop/bashrc.sh
    /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    /data/blyth/junotop/sniper/build /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    -- cmake version 3.24.1
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    CMake Error at /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
      Could NOT find Python3 (missing: Interpreter) (found version "3.8.12")

          Reason given by package: 
              Interpreter: Cannot run the interpreter "/data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8"

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:594 (_FPHSA_FAILURE_MESSAGE)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake:3203 (find_package_handle_standard_args)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake:490 (include)
      CMakeLists.txt:65 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost junoenv]$ 


::

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8: error while loading shared libraries: libpython3.8.so.1.0: cannot open shared object file: No such file or directory
    N[blyth@localhost junoenv]$ 



/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake::

    486 set (_PYTHON_PREFIX Python3)
    487 
    488 set (_Python3_REQUIRED_VERSION_MAJOR 3)
    489 
    490 include (${CMAKE_CURRENT_LIST_DIR}/FindPython/Support.cmake)
    491 
    492 if (COMMAND __Python3_add_library)
    493   macro (Python3_add_library)
    494     __Python3_add_library (Python3 ${ARGV})
    495   endmacro()
    496 endif()

/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake::



Huh sniper/CMake trying to use python 3.8.12 when 3.9.14 is available::

    N[blyth@localhost junoenv]$ cat $JUNOTOP/bashrc.sh 
    export JUNOTOP=/data/blyth/junotop
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Git/2.37.3/bashrc
    source /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.1.0/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/22.2.2/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.28/bashrc

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Python/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  6 blyth blyth   84 Sep 23 18:51 3.9.14
    0 drwxrwxr-x.  3 blyth blyth   34 Sep 23 18:49 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 3.8.12 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Python/3.8.12
    N[blyth@localhost junoenv]$ 

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3
    Python 3.9.14 (main, Sep 23 2022, 18:50:47) 
    [GCC 8.3.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> 


Probably update building not operational::

    N[blyth@localhost junotop]$ mv sniper sniper_old
    N[blyth@localhost junotop]$ mv mt.sniper mt.sniper_old


That gets further, failing at boost python::

    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found Python3: /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3.9 (found version "3.9.14") found components: Interpreter Development Development.Module Development.Embed 
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!


Hmm it would be easier to reuse sniper and all the external libs. 


::

    N[blyth@localhost sniper]$ cd build
    N[blyth@localhost build]$ cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
    -- cmake version 3.24.1
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost build]$ 



sniper/CMakeLists.txt is looking for Boost 1.67::

     57 # Config for Option USE_PYTHON
     58 if(USE_PYTHON)
     59     #python
     60     set(PyPkgName Python3)  #Use Python3 by default
     61     option(USE_PYTHON2 "Use Python2 instead of Python3" OFF)
     62     if(USE_PYTHON2)
     63         set(PyPkgName Python2)
     64     endif()
     65     find_package(${PyPkgName} COMPONENTS Interpreter Development REQUIRED)
     66     message(STATUS "python version ${${PyPkgName}_VERSION}")
     67     set(PYTHON_VERSION "${${PyPkgName}_VERSION}")
     68     set(PYTHON_INCLUDE_DIRS "${${PyPkgName}_INCLUDE_DIRS}")
     69     set(PYTHON_LIBRARY "${${PyPkgName}_LIBRARIES}")
     70     #boost.python
     71     set(Boost_USE_MULTITHREADED OFF)
     72     set(BoostPyVer "${${PyPkgName}_VERSION_MAJOR}${${PyPkgName}_VERSION_MINOR}")
     73     find_package(Boost 1.67 COMPONENTS python${BoostPyVer} REQUIRED)
     74     set(BOOST_PYTHON_LIBRARY "${Boost_PYTHON${BoostPyVer}_LIBRARY}")
     75     unset(BoostPyVer)
     76     #python install dir
     77     if(NOT CMAKE_INSTALL_PYTHONDIR)
     78         set(CMAKE_INSTALL_PYTHONDIR "python")
     79     endif()
     80     #...
     81     add_definitions(-DHAVE_PYTHON)
     82     unset(PyPkgName)
     83 endif()


::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Boost/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  2 blyth blyth   20 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   89 Mar  2  2022 1.78.0 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/
    total 2
    1 drwxr-xr-x. 37 cvmfs cvmfs 36 May 26 16:39 ..
    1 drwxr-xr-x.  4 cvmfs cvmfs 80 Mar  4  2022 1.78.0
    1 drwxr-xr-x.  3 cvmfs cvmfs 28 Jan  5  2022 .
    N[blyth@localhost junoenv]$ 






N[blyth@localhost build]$  cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
-- cmake version 3.24.1
-- python version 3.9.14
CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
  Found package configuration file:

    /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

  but it set boost_python_FOUND to FALSE so package "boost_python" is
  considered to be NOT FOUND.  Reason given by package:

  No suitable build variant has been found.

  The following variants have been tried and rejected:

  * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

  * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

Call Stack (most recent call first):
  /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
  /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
  CMakeLists.txt:73 (find_package)


-- Configuring incomplete, errors occurred!
See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
N[blyth@localhost build]$ 



::

    N[blyth@localhost Boost]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/*python*.*
    644 -rw-r--r--. 1 cvmfs cvmfs 659132 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.a
    334 -rwxr-xr-x. 1 cvmfs cvmfs 341264 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so.1.78.0
      1 lrwxrwxrwx. 1 cvmfs cvmfs     27 Jan  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so -> libboost_python38.so.1.78.0
    N[blyth@localhost Boost]$ 





