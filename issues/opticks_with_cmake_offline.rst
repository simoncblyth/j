opticks_with_cmake_offline
=============================


Ended up with
-----------------

cmake/JUNODependencies.cmake::
 
    ## Opticks
    if(DEFINED ENV{OPTICKS_PREFIX})
       set(Opticks_VERBOSE YES)
       set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{JUNOTOP}/opticks/cmake/Modules")
       find_package(Opticks MODULE)
       message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
    endif()




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


"bash junoenv opticks hookup" needs to do the below and other PATH setup::

  export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:/data/blyth/junotop/ExternalLibs/opticks/head

::

    N[blyth@localhost junotop]$ cat $JUNOTOP/bashrc.sh
    export JUNOTOP=/data/blyth/junotop
    export CMTPROJECTPATH=/data/blyth/junotop:${CMTPROJECTPATH}
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.8.12/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.0.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/21.2.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.24/bashrc
    source /data/blyth/junotop/ExternalLibs/python-numpy/1.21.2/bashrc
    ...
    source /data/blyth/junotop/ExternalLibs/pacparser/1.3.7/bashrc
    source /data/blyth/junotop/ExternalLibs/frontier/2.9.1/bashrc
    source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Mon Dec 6 20:49:40 CST 2021
    N[blyth@localhost junotop]$ 


Hookup line can stay the same, need to add CMake support to the bashrc content::

    N[blyth@localhost junotop]$ cat /data/blyth/junotop/ExternalLibs/opticks/head/bashrc

    if [ -s "/data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh" ]; then 

        # get CMTEXTRATAGS to contain the string opticks switching on WITH_G4OPTICKS macro in offline compilation
        if [ -z "$CMTEXTRATAGS" ]; then   # not yet defined
            CMTEXTRATAGS="opticks"
        elif [ "${CMTEXTRATAGS/opticks}" == "${CMTEXTRATAGS}" ]; then  # defined but without opticks
            CMTEXTRATAGS=:opticks
        fi 
        export CMTEXTRATAGS


        if [ -n "$VERBOSE" ]; then 
           source /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh 
        else
           source /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh > /dev/null
        fi  

    else
        if [ -n "$VERBOSE" ]; then 
            echo script /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh does not exist 
        fi
    fi 





Is there a convention for CMAKE_MODULE_PATH directories to avoid specifying it ?
---------------------------------------------------------------------------------

Seems not. In any case would need to use symbolic link trickery as the path is ../cmake/Modules
relative to the opticks pkg dirs. 


::

    epsilon:offline blyth$ t om-cmake
    om-cmake () 
    { 
        local sdir=$1;
        local bdir=$PWD;
        [ "$sdir" == "$bdir" ] && echo ERROR sdir and bdir are the same $sdir && return 1000;
        local rc;
        cmake $sdir -G "$(om-cmake-generator)" -DCMAKE_BUILD_TYPE=$(opticks-buildtype) -DOPTICKS_PREFIX=$(om-prefix) -DCMAKE_INSTALL_PREFIX=$(om-prefix) -DCMAKE_MODULE_PATH=$(om-home)/cmake/Modules;
        rc=$?;
        return $rc
    }
    epsilon:offline blyth$ 



Hmm : looks like CMAKE_PREFIX_PATH is already there in opticks-setup.sh but there is no CMAKE_MODULE_PATH setup
-----------------------------------------------------------------------------------------------------------------

* https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Useful-Variables
* https://cmake.org/cmake/help/latest/manual/cmake-env-variables.7.html

CMAKE_MODULE_PATH not mentioned as envvar 

Hmm opticks is a bunch of proj so need to do some work for find the Modules 
from each proj without spelling it out on commandline::

   list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake/Modules)

Hmm actually that is not so easy because the natural place to put that 
is in cmake/Modules/OpticksBuildOptions.cmake but thats a chicken-and-egg situation.


Add the extra to jm-cmake and append to CMAKE_MODULE_PATH in opticks-setup.sh 
---------------------------------------------------------------------------------

::

    jm-cmake(){   
       : j/j.bash using build layout from $JUNOTOP/junoenv/junoenv-offline.sh  junoenv-offline-compile-cmake
       : see j/opticks_with_cmake_offline.rst

       local sdir=$(jm-sdir)
       local bdir=$(jm-bdir)
       local idir=$(jm-idir)
       [ ! -d $sdir -o ! -d $bdir -o ! -d $idir ] && echo $msg use "bash junoenv offline" first  && return 1 
       cd $bdir

       local extra=""
       if [ -n "$CMAKE_MODULE_PATH" ]; then 
           extra="-DCMAKE_MODULE_PATH=$CMAKE_MODULE_PATH"
       fi

       cmake $sdir \
             -DCMAKE_INSTALL_PREFIX=$idir \
             -DCMAKE_CXX_STANDARD=17 \
             $extra

    }


::

    N[blyth@localhost build]$ echo $OPTICKS_PREFIX
    /data/blyth/junotop/ExternalLibs/opticks/head
    N[blyth@localhost build]$ export CMAKE_MODULE_PATH=$OPTICKS_PREFIX/cmake/Modules:$CMAKE_MODULE_PATH
    N[blyth@localhost build]$ unset CMAKE_MODULE_PATH ; export CMAKE_MODULE_PATH=$JUNOTOP/opticks/cmake/Modules:$CMAKE_MODULE_PATH



TODO: read up on CMake include path resolution


Hmm the installed Modules are very old::

    N[blyth@localhost junotop]$ l $OPTICKS_PREFIX/cmake/Modules/
    total 116
     4 drwxrwxr-x. 2 blyth blyth 4096 May 10  2020 .
     8 -rw-r--r--. 1 blyth blyth 4608 May  9  2020 FindOpticksXercesC.cmake
     8 -rw-r--r--. 1 blyth blyth 4258 May  7  2020 OpticksBuildOptions.cmake
     4 -rw-r--r--. 1 blyth blyth 3558 May  7  2020 EchoTarget.cmake
     8 -rw-r--r--. 1 blyth blyth 4686 May  7  2020 FindG4.cmake
     4 -rw-r--r--. 1 blyth blyth 1194 May  7  2020 FindGLM.cmake
     4 -rw-r--r--. 1 blyth blyth 2014 May  7  2020 FindImGui.cmake
     4 -rw-r--r--. 1 blyth blyth 2759 May  7  2020 FindOpenMesh.cmake
     4 -rw-r--r--. 1 blyth blyth 1863 May  7  2020 FindOpticksAssimp.cmake
     8 -rw-r--r--. 1 blyth blyth 5140 May  7  2020 FindOpticksCUDA.cmake
     4 -rw-r--r--. 1 blyth blyth 1652 May  7  2020 FindOpticksGLEW.cmake
     8 -rw-r--r--. 1 blyth blyth 4282 May  7  2020 FindOpticksGLFW.cmake
    12 -rw-r--r--. 1 blyth blyth 9359 May  7  2020 FindOptiX.cmake
     4 -rw-r--r--. 1 blyth blyth 1150 May  7  2020 FindPLog.cmake
     0 drwxrwxr-x. 3 blyth blyth   21 Oct 10  2019 ..
     4 -rw-r--r--. 1 blyth blyth 2452 Oct  9  2019 TopMetaTarget.cmake
     4 -rw-r--r--. 1 blyth blyth 3022 Apr 10  2019 OpticksCXXFlags.cmake
     4 -rw-r--r--. 1 blyth blyth  964 Aug 12  2018 OpticksCUDAFlags.cmake
     8 -rw-rw-r--. 1 blyth blyth 4123 Jul  5  2018 OpticksConfigureConfigScript.cmake
     4 -rw-rw-r--. 1 blyth blyth  143 Jul  5  2018 FindPPM.cmake
     4 -rw-rw-r--. 1 blyth blyth  461 Jul  5  2018 FindNonExisting.cmake
     4 -rw-rw-r--. 1 blyth blyth  257 Jul  5  2018 EnvBuildOptions.cmake

Compared to the source::

    N[blyth@localhost junotop]$ l $JUNOTOP/opticks/cmake/Modules/
    total 148
     4 drwxrwxr-x. 5 blyth blyth 4096 Dec  6 04:22 .
     8 -rw-rw-r--. 1 blyth blyth 4637 Dec  6 04:22 OpticksBuildOptions.cmake
     8 -rw-rw-r--. 1 blyth blyth 5593 Dec  6 03:58 FindOpticksCUDA.cmake
     8 -rw-rw-r--. 1 blyth blyth 4745 Oct 25 21:41 OpticksCXXFlags.cmake
     0 drwxrwxr-x. 5 blyth blyth   73 Jul  6 23:09 ..
     4 drwxrwxr-x. 2 blyth blyth 4096 Jul  6 23:09 old
     4 drwxrwxr-x. 2 blyth blyth 4096 Jul  6 23:09 inactive
     0 drwxrwxr-x. 3 blyth blyth   34 Jul  6 23:09 include
     8 -rw-rw-r--. 1 blyth blyth 4123 Jul  6 23:09 OpticksConfigureConfigScript.cmake
     4 -rw-rw-r--. 1 blyth blyth 2452 Jul  6 23:09 TopMetaTarget.cmake
     4 -rw-rw-r--. 1 blyth blyth  971 Jul  6 23:09 FindNLJSON.cmake
     4 -rw-rw-r--. 1 blyth blyth  461 Jul  6 23:09 FindNonExisting.cmake
     4 -rw-rw-r--. 1 blyth blyth 2759 Jul  6 23:09 FindOpenMesh.cmake
     4 -rw-rw-r--. 1 blyth blyth 1863 Jul  6 23:09 FindOpticksAssimp.cmake
     4 -rw-rw-r--. 1 blyth blyth 1652 Jul  6 23:09 FindOpticksGLEW.cmake
     8 -rw-rw-r--. 1 blyth blyth 4282 Jul  6 23:09 FindOpticksGLFW.cmake
     8 -rw-rw-r--. 1 blyth blyth 5149 Jul  6 23:09 FindOpticksOptiX.cmake
     8 -rw-rw-r--. 1 blyth blyth 5468 Jul  6 23:09 FindOpticksXercesC.cmake
    12 -rw-rw-r--. 1 blyth blyth 9467 Jul  6 23:09 FindOptiX.cmake
     4 -rw-rw-r--. 1 blyth blyth 1150 Jul  6 23:09 FindPLog.cmake
     8 -rw-rw-r--. 1 blyth blyth 6679 Jul  6 23:09 OpticksCMakeTraverse.cmake
     4 -rw-rw-r--. 1 blyth blyth 1185 Jul  6 23:09 OpticksCUDAFlags.cmake
     4 -rw-rw-r--. 1 blyth blyth 3558 Jul  6 23:09 EchoTarget.cmake
     4 -rw-rw-r--. 1 blyth blyth  257 Jul  6 23:09 EnvBuildOptions.cmake
     4 -rw-rw-r--. 1 blyth blyth  654 Jul  6 23:09 FindBoostAsio.cmake
     8 -rw-rw-r--. 1 blyth blyth 5555 Jul  6 23:09 FindG4.cmake
     4 -rw-rw-r--. 1 blyth blyth 1194 Jul  6 23:09 FindGLM.cmake
     4 -rw-rw-r--. 1 blyth blyth 2014 Jul  6 23:09 FindImGui.cmake
    N[blyth@localhost junotop]$ 




jm-cmake failing with Opticks found in CMAKE_PREFIX_PATH due to lack of CMAKE_MODULE_PATH on cmake command line
-------------------------------------------------------------------------------------------------------------------


::

    N    # plain vanilla environment on P 
    jre
    jm-cmake


    eom.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathMore.so
    -- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found suitable version "3.8.12", minimum required is "3.8.12") found components: Interpreter 
    CMake Error at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      No "FindG4.cmake" found in CMAKE_MODULE_PATH.
    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:107 (find_package)
      CMakeLists.txt:36 (include)


    CMake Warning (dev) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      FindG4.cmake must either be part of this project itself, in this case
      adjust CMAKE_MODULE_PATH so that it points to the correct location inside
      its source tree.

      Or it must be installed by a package which has already been found via
      find_package().  In this case make sure that package has indeed been found
      and adjust CMAKE_MODULE_PATH to contain the location where that package has
      installed FindG4.cmake.  This must be a location provided by that package.
      This error in general means that the buildsystem of this project is relying
      on a Find-module without ensuring that it is actually available.

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:107 (find_package)
      CMakeLists.txt:36 (include)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/offline/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost build]$ 




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

    O[blyth@localhost ~]$ cat $JUNOTOP/bashrc.sh
    export JUNOTOP=/data/blyth/junotop
    export CMTPROJECTPATH=/data/blyth/junotop:${CMTPROJECTPATH}
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.8.12/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.0.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/21.2.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.24/bashrc
    source /data/blyth/junotop/ExternalLibs/python-numpy/1.21.2/bashrc
    source /data/blyth/junotop/ExternalLibs/Boost/1.77.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Cmake/3.21.2/bashrc
    source /data/blyth/junotop/ExternalLibs/Git/2.33.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/bashrc
    source /data/blyth/junotop/ExternalLibs/gsl/2.5/bashrc
    source /data/blyth/junotop/ExternalLibs/fftw3/3.3.8/bashrc
    source /data/blyth/junotop/ExternalLibs/sqlite3/3.35.5/bashrc
    source /data/blyth/junotop/ExternalLibs/log4cpp/1.1.3/bashrc
    source /data/blyth/junotop/ExternalLibs/libxml2/2.9.12/bashrc
    source /data/blyth/junotop/ExternalLibs/LHAPDF/6.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/pythia6/6.4.28/bashrc
    source /data/blyth/junotop/ExternalLibs/tbb/2019_U8/bashrc
    source /data/blyth/junotop/ExternalLibs/CMT/v1r26/bashrc
    source /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/bashrc
    source /data/blyth/junotop/ExternalLibs/xrootd/5.3.1/bashrc
    source /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bashrc
    source /data/blyth/junotop/ExternalLibs/HepMC/2.06.09/bashrc
    source /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /data/blyth/junotop/ExternalLibs/genie/3.00.06/bashrc
    source /data/blyth/junotop/ExternalLibs/nuwro/19.02.2/bashrc
    source /data/blyth/junotop/ExternalLibs/talys/1.95/bashrc
    source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    source /data/blyth/junotop/ExternalLibs/mysql-connector-c/6.1.9/bashrc
    source /data/blyth/junotop/ExternalLibs/mysql-connector-cpp/1.1.12/bashrc
    source /data/blyth/junotop/ExternalLibs/libyaml/0.2.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-yaml/5.4.1.1/bashrc
    source /data/blyth/junotop/ExternalLibs/pacparser/1.3.7/bashrc
    source /data/blyth/junotop/ExternalLibs/frontier/2.9.1/bashrc
    source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Sat Dec 4 04:30:39 CST 2021
    O[blyth@localhost ~]$ 



Maybe need resetup::

    O[blyth@localhost junoenv]$ bash junoenv env resetup


* seems to be pilot error, using N and then running jre followed by jm-cmake jm works



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




Packages depending on Opticks
--------------------------------

::

    Simulation/GenTools/CMakeLists.txt
    Simulation/DetSimV2/PhysiSim/CMakeLists.txt
    Simulation/DetSimV2/PMTSim/CMakeLists.txt
    Simulation/DetSimV2/DetSimOptions/CMakeLists.txt
    Simulation/DetSimV2/AnalysisCode/CMakeLists.txt 


::

    Simulation/GenTools/CMakeLists.txt

    include (PKG)
    PKG(GenTools
        DEPENDS
            GenEventV2
            BufferMemMgr
            MCGlobalTimeSvc
            SNiPER::RootWriterLib
            EG
            # == FIXME ==
            G4geometry
            Boost::regex

            $<$<BOOL:${WITH_G4OPTICKS}>:Opticks::G4OK>
    )


    Simulation/DetSimV2/PhysiSim/CMakeLists.txt

    001 include (PKG)
      2 PKG (PhysiSim
      3     NOAUX # don't load all the cc files from src
      4     FILES
      5         src/DsG4Scintillation.cc 
      6         src/LocalG4Cerenkov1042.cc 
      7         src/DsPhysConsOptical.cc
      8         src/DsWrapPhysConsOptical.cc
      9         src/DsWrapPhysConsIon.cc
     10         src/DsG4HadronPhysicsQGSP_BERT_HP.cc 
     11         src/DsG4NeutronPHPBuilder.cc 
     12         src/DsG410NNDCParticleHPCaptureFS.cc 
     13         src/DsG410GdParticleHPCaptureFS.cc 
     14         src/DsG4ParticleHPCapture.cc 
     15         src/DsG4GdCaptureGammas.cc 
     16         src/DsG4EmLivermorePhysics.cc 
     17         src/G4Positronium.cc 
     18         src/G4PositroniumFormation.cc 
     19         src/G4PositroniumDecayChannel2G.cc 
     20         src/G4PositroniumDecayChannel3G.cc 
     21         src/DsG4NNDCCaptureGammas.cc 
     22         src/DsG4EmLivermorePhysics.cc
     23         src/DsG4ScintSimple.cc 
     24         src/DsG4OpAbsReemit.cc 
     25         src/G4Cerenkov_modified.cc 
     26     
     27     DEPENDS
     28         DetSimAlg
     29         MCParamsSvc
     30 
     31     SETENV
     32         DAYA_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
     33 )


    Simulation/DetSimV2/PMTSim/CMakeLists.txt

    001 
      2 include (PKG)
      3 PKG (PMTSim
      4     DEPENDS
      5         SimUtil
      6         IPMTSimParamSvc
      7         Geometry
      8         MultiFilmSimSvc
      9         MCParamsSvc
     10 )

    Simulation/DetSimV2/DetSimOptions/CMakeLists.txt

    001 include (PKG)
      2 
      3 PKG(DetSimOptions
      4     DEPENDS
      5         AnalysisCode
      6 
      7         CentralDetector
      8         TopTracker
      9         Chimney
     10         CalibUnit
     11 
     12         PhysiSim
     13         PMTSim
     14         SimUtil
     15         MCParamsSvc
     16 
     17         DetSimAlg
     18 
     19         ${GEANT4_LIBRARIES}
     20 )


    Simulation/DetSimV2/AnalysisCode/CMakeLists.txt 

    001 include (PKG)
      2 PKG(AnalysisCode
      3     DEPENDS
      4         PMTSim
      5         SimUtil
      6         DetSimAlg
      7         OPSimulator
      8 
      9         GenTools
     10 
     11         SimEventV2
     12         EvtNavigator
     13 
     14         JunoTimer
     15 
     16         DataRegistritionSvc
     17 
     18         Boost::filesystem Boost::system
     19         Geom
     20 )



    PKG(RecCdMuonAlg
        DEPENDS
        RecEvent
        CalibEvent
        Identifier
        Geometry
        EvtNavigator
        DataRegistritionSvc
        BufferMemMgr
        SNiPER::RootWriterLib
        $<$<BOOL:${WITH_OEC}>:EvtStore>
        $<$<BOOL:${WITH_OEC}>:EvtDataTypes>
        $<$<BOOL:${WITH_OEC}>:OECEvent>
    )


CMake Generator Expressions
-----------------------------

* https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html

* $<BOOL:${WITH_OEC}>   converts WITH_OEC string to 0 or 1 yielding 0 when empty/0/OFF/... 

* $<condition:true_string>
   Evaluates to true_string if condition is 1. Otherwise evaluates to the empty string.


* $<1:EvtStore>
* $<0:EvtStore>


Try::

    $<$<BOOL:${WITH_G4OPTICKS}>:Opticks::G4OK>



::

    epsilon:offline blyth$ find . -type f -exec grep -H WITH_G4OPTICKS {} \; | grep -v .svn 
    ./Simulation/GenTools/src/GtOpticksTool.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/GenTools/src/GtOpticksTool.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/GenTools/src/GtOpticksTool.cc:        << "GtOpticksTool::configure  WITH_G4OPTICKS"
    ./Simulation/GenTools/src/GtOpticksTool.cc:        << "GtOpticksTool::configure  NOT WITH_G4OPTICKS"
    ./Simulation/GenTools/src/GtOpticksTool.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/GenTools/src/GtOpticksTool.h: *                  This class needs to be compiled -DWITH_G4OPTICKS to do anything useful, 

    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:               << " non-zero opticksMode requires compilation -DWITH_G4OPTICKS " 

    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS_CHECK_EFFICIENCY
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc:#ifdef WITH_G4OPTICKS



    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:       << " WITH_G4OPTICKS "
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:       << " **NOT** WITH_G4OPTICKS " 

    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:       << " WITH_G4OPTICKS "
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:       << " **NOT** WITH_G4OPTICKS " 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:    LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:    LOG(info) << "] WITH_G4OPTICKS " ; 

    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:#ifdef WITH_G4OPTICKS



::

    N[blyth@localhost build]$ jm-cmake
    === jm-cmake : cmd cmake /data/blyth/junotop/offline -DCMAKE_INSTALL_PREFIX=/data/blyth/junotop/offline/InstallArea -DCMAKE_CXX_STANDARD=17 -DCMAKE_MODULE_PATH=/data/blyth/junotop/opticks/cmake/Modules:
    -- Build type: Release
    -- CMAKE_C_FLAGS_RELEASE: -O3 -DNDEBUG
    -- CMAKE_CXX_FLAGS_RELEASE: -O3 -DNDEBUG
    -- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found version "3.8.12") found components: Interpreter Development Development.Module Development.Embed 
    Found Python /data/blyth/junotop/ExternalLibs/Python/3.8.12/lib/libpython3.8.so
    Found Boost: Boost::python;Boost::filesystem;Boost::system;Boost::regex
    Found XercesC: /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/lib/libxerces-c.so
    The XercesC found target: XercesC::XercesC
    Found ROOT: /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libCore.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libImt.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRIO.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libNet.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libHist.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf3d.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGpad.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTDataFrame.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTree.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTreePlayer.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRint.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPostscript.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMatrix.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPhysics.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathCore.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libThread.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMultiProc.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTVecOps.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEG.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEve.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGeom.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathMore.so
    -- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found suitable version "3.8.12", minimum required is "3.8.12") found components: Interpreter 
    CMake Error at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      No "FindG4.cmake" found in CMAKE_MODULE_PATH.
    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:107 (find_package)
      CMakeLists.txt:36 (include)


    CMake Warning (dev) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      FindG4.cmake must either be part of this project itself, in this case
      adjust CMAKE_MODULE_PATH so that it points to the correct location inside
      its source tree.

      Or it must be installed by a package which has already been found via
      find_package().  In this case make sure that package has indeed been found
      and adjust CMAKE_MODULE_PATH to contain the location where that package has
      installed FindG4.cmake.  This must be a location provided by that package.
      This error in general means that the buildsystem of this project is relying
      on a Find-module without ensuring that it is actually available.

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:107 (find_package)
      CMakeLists.txt:36 (include)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/offline/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost build]$ 
    N[blyth@localhost build]$ t jm-cmake
    jm-cmake () 
    { 
        : j/j.bash using build layout from $JUNOTOP/junoenv/junoenv-offline.sh junoenv-offline-compile-cmake;
        : see j/opticks_with_cmake_offline.rst;
        local msg="=== $FUNCNAME :";
        local sdir=$(jm-sdir);
        local bdir=$(jm-bdir);
        local idir=$(jm-idir);
        [ ! -d $sdir -o ! -d $bdir -o ! -d $idir ] && echo $msg use "bash junoenv offline" first && return 1;
        cd $bdir;
        local cmd=$(jm-cmake- $sdir $idir);
        echo $msg cmd $cmd;
        eval $cmd
    }
    N[blyth@localhost build]$ 



::

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")



Passing multiple dirs in CMAKE_MODULE_PATH into CMake is a pain ad need to escape semicolons::

    cmake /data/blyth/junotop/offline \
        -DCMAKE_INSTALL_PREFIX=/data/blyth/junotop/offline/InstallArea \
        -DCMAKE_CXX_STANDARD=17 \
        -DCMAKE_MODULE_PATH=/data/blyth/junotop/opticks/cmake/Modules\;one\;two\;three






Huh from $JUNOTOP/junoenv/junoenv-offline.sh::

    083 function junoenv-offline-compile-cmake {
     84     local msg="==== $FUNCNAME: "
     85     pushd $(juno-top-dir) >& /dev/null
     86 
     87     if [ -d "$(junoenv-offline-name)" ]; then
     88         pushd $(junoenv-offline-name)
     89 
     90         # create the build directory
     91         [ -d "build" ] || mkdir build || exit -1
     92         # create the install directory
     93         [ -d "InstallArea" ] || mkdir InstallArea || exit -1
     94         local installprefix=$(juno-top-dir)/$(junoenv-offline-name)/InstallArea
     95         # start the build and install of sniper
     96         pushd build
     97         cmake .. -DCMAKE_INSTALL_PREFIX=$installprefix -DCMAKE_CXX_STANDARD=17 || exit -1
     98         make || exit -1
     99         make install || exit -1
    100         popd # build
    101 
    102         popd # $(junoenv-offline-name)
    103     fi
    104 
    105     popd >& /dev/null # $(juno-top-dir)
    106 }


But from $JUNOTOP/offline/build.sh::

    168 function run-build() {
    169     local installdir=$(install-dir)
    170     local blddir=$(build-dir)
    171     check-build-dir
    172     check-install-dir
    173 
    174     pushd $blddir
    175 
    176     cmake .. $(check-var-enabled graphviz) \
    177              $(check-var-enabled withoec) \
    178              -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=$installdir || error: "ERROR Found during cmake stage. "
    179 
    180     make || error: "ERROR Found during make stage. "
    181     make install || error: "ERROR Found during make install stage. "
    182 
    183     popd
    184 }


::

    O[blyth@localhost build]$ cmake /data/blyth/junotop/offline -DCMAKE_INSTALL_PREFIX=/data/blyth/junotop/offline/InstallArea -DCMAKE_CXX_STANDARD=17 -DCMAKE_MODULE_PATH=/data/blyth/junotop/opticks/cmake/Modules\;one\;two\;three
    -- Build type: Release
    -- CMAKE_C_FLAGS_RELEASE: -O3 -DNDEBUG
    -- CMAKE_CXX_FLAGS_RELEASE: -O3 -DNDEBUG
    -- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found version "3.8.12") found components: Interpreter Development Development.Module Development.Embed 
    Found Python /data/blyth/junotop/ExternalLibs/Python/3.8.12/lib/libpython3.8.so
    Found Boost: Boost::python;Boost::filesystem;Boost::system;Boost::regex
    Found XercesC: /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/lib/libxerces-c.so
    The XercesC found target: XercesC::XercesC
    Found ROOT: /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libCore.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libImt.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRIO.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libNet.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libHist.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGraf3d.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGpad.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTDataFrame.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTree.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libTreePlayer.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libRint.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPostscript.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMatrix.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libPhysics.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathCore.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libThread.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMultiProc.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libROOTVecOps.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEG.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libEve.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libGeom.so;/data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib/libMathMore.so
    -- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found suitable version "3.8.12", minimum required is "3.8.12") found components: Interpreter 
    --  _dir /data/blyth/junotop/opticks/cmake/Modules 
    --  _dir one 
    --  _dir two 
    --  _dir three 
    --  _dir /data/blyth/junotop/offline/cmake/Modules/ 
    -- OPTICKS_PREFIX           : 
    -- GLM_MODULE_DIR           : 
    -- GLM_MODULE_DIRDIR        : 
    -- GLM_MODULE_DIRDIRDIR     : 
    -- CMAKE_CURRENT_SOURCE_DIR : /data/blyth/junotop/offline
    -- GLM_MODULE               : /data/blyth/junotop/opticks/cmake/Modules/FindGLM.cmake
    -- GLM_INCLUDE_DIR          : GLM_INCLUDE_DIR-NOTFOUND 
    -- GLM_FOUND                : NO
    CMake Error at /data/blyth/junotop/opticks/cmake/Modules/FindGLM.cmake:32 (message):
      GLM NOT FOUND
    Call Stack (most recent call first):
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/npy/npy-config.cmake:26 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/optickscore/optickscore-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/ggeo/ggeo-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/extg4/extg4-config.cmake:10 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:10 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:115 (find_package)
      CMakeLists.txt:36 (include)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/offline/build/CMakeFiles/CMakeOutput.log".
    O[blyth@localhost build]$ 



Finding GLM requires an CMake OPTICKS_PREFIX var::

     01 
      2 
      3 set(GLM_MODULE "${CMAKE_CURRENT_LIST_FILE}")
      4 #set(GLM_VERBOSE OFF)
      5 
      6 find_path(
      7     GLM_INCLUDE_DIR
      8     NAMES "glm/glm.hpp"
      9     PATHS "${OPTICKS_PREFIX}/externals/glm/glm"
     10 )
     11 




::

    jm-cmake-(){   

       local sdir=$1
       local idir=$2

       local extra=""
       if [ -d "$JUNOTOP/opticks" ]; then 
           extra="$extra -DCMAKE_MODULE_PATH=$JUNOTOP/opticks/cmake/Modules"
       fi
       if [ -n "$OPTICKS_PREFIX" ]; then 
           extra="$extra -DOPTICKS_PREFIX=$OPTICKS_PREFIX"
       fi

       cat << EOC
       cmake $sdir \
             -DCMAKE_INSTALL_PREFIX=$idir \
             -DCMAKE_CXX_STANDARD=17 \
             $extra

    EOC
    }




::


    [ 53%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/GtPositionerTool.cc.o
    [ 53%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/GtTimeOffsetTool.cc.o
    [ 53%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/PostGenTools.cc.o
    [ 53%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/binding.cc.o
    /data/blyth/junotop/offline/Examples/FirstAlg/src/FirstAlg.cc:10:2: error: #error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
     #error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
      ^~~~~
    /data/blyth/junotop/offline/Simulation/GenTools/src/GtOpticksTool.cc:12:10: fatal error: PLOG.hh: No such file or directory
     #include "PLOG.hh"
              ^~~~~~~~~
    compilation terminated.
    make[2]: *** [Simulation/GenTools/CMakeFiles/GenTools.dir/src/GtOpticksTool.cc.o] Error 1
    make[2]: *** Waiting for unfinished jobs....
    In file included from /data/blyth/junotop/offline/Utilities/InputReviser/src/InputReviser.cc:1:
    /data/blyth/junotop/offline/Utilities/InputReviser/InputReviser/InputReviser.h:17:21: warning:   by ‘virtual int InputReviser::fire(Task&)’ [-Woverloaded-virtual]
             virtual int fire(Task& domain);
                         ^~~~


Simulation/GenTools/CMakeLists.txt::

     01 include (PKG)
      2 PKG(GenTools
      3     DEPENDS
      4         GenEventV2
      5         BufferMemMgr
      6         MCGlobalTimeSvc
      7         SNiPER::RootWriterLib
      8         EG
      9         # == FIXME ==
     10         G4geometry
     11         Boost::regex
     12 
     13         $<$<BOOL:${G4OK_FOUND}>:Opticks::G4OK> 
     14 )
     15 



::

    [ 64%] Building CXX object Simulation/GenDecay/CMakeFiles/GenDecay.dir/src/NucUtil.cpp.o
    /data/blyth/junotop/offline/Examples/FirstAlg/src/FirstAlg.cc:10:2: error: #error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
     #error "OPTICKS is enabled. Maybe you are set the envvar CMTEXTRATAGS=opticks"
      ^~~~~
    In file included from /data/blyth/junotop/offline/Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:75:
    /data/blyth/junotop/offline/Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh:57:10: fatal error: plog/Severity.h: No such file or directory
     #include "plog/Severity.h"
              ^~~~~~~~~~~~~~~~~
    compilation terminated.




So is finding opticks headers but failing to find headers from opticks externals::


    [ 64%] Linking CXX shared library ../../lib/libNuSolGen.so
    In file included from /data/blyth/junotop/offline/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:69:
    /data/blyth/junotop/offline/Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h:74:10: fatal error: plog/Severity.h: No such file or directory
     #include "plog/Severity.h"
              ^~~~~~~~~~~~~~~~~


up the verbosity::

    -- PLog_MODULE : /data/blyth/junotop/opticks/cmake/Modules/FindPLog.cmake
    -- FindPLog.cmake : PLog_MODULE      : /data/blyth/junotop/opticks/cmake/Modules/FindPLog.cmake 
    -- FindPLog.cmake : OPTICKS_PREFIX   : /data/blyth/junotop/ExternalLibs/opticks/head 
    -- FindPLog.cmake : PLog_INCLUDE_DIR : /data/blyth/junotop/ExternalLibs/opticks/head/externals/plog/include 
    -- FindPLog.cmake : PLog_FOUND       : YES  


The Opticks::PLog target with INTERFACE_INCLUDE_DIRECTORIES is setup in opticks/cmake/Modules/FindPLog.cmake::

     14 
     15 find_path(
     16     PLog_INCLUDE_DIR
     17     NAMES "plog/Log.h"
     18     PATHS "${OPTICKS_PREFIX}/externals/plog/include"
     19 )
     20 
     21 
     22 if(PLog_INCLUDE_DIR)
     23    set(PLog_FOUND "YES")
     24 else()
     25    set(PLog_FOUND "NO")
     26 endif()
     27 
     28 set(_tgt Opticks::PLog)
     29 
     30 set(PLog_targets)
     31 
     32 if(PLog_FOUND AND NOT TARGET ${_tgt})
     33 
     34     add_library(${_tgt} INTERFACE IMPORTED)
     35 
     36     set_property( TARGET ${_tgt} PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${PLog_INCLUDE_DIR}" )
     37     set_property( TARGET ${_tgt} PROPERTY INTERFACE_PKG_CONFIG_NAME "PLog" )
     38 
     39     list(APPEND PLog_targets "PLog")
     40 
     41 endif()
     42 
     43 if(PLog_VERBOSE)
     44     message(STATUS "FindPLog.cmake : PLog_MODULE      : ${PLog_MODULE} ")
     45     message(STATUS "FindPLog.cmake : OPTICKS_PREFIX   : ${OPTICKS_PREFIX} ")
     46     message(STATUS "FindPLog.cmake : PLog_INCLUDE_DIR : ${PLog_INCLUDE_DIR} ")
     47     message(STATUS "FindPLog.cmake : PLog_FOUND       : ${PLog_FOUND}  ")
     48 endif()


Perhaps am omitting to add Opticks::PLog dependency line somewhere ?


Try kludging it, in cmake/JUNODependencies.cmake::

    106 ## Opticks
    107 foreach(_dir ${CMAKE_MODULE_PATH})
    108     message(STATUS "CMAKE_MODULE_PATH  _dir ${_dir} ")
    109 endforeach()
    110 message(STATUS " CMAKE_PREFIX_PATH : $ENV{CMAKE_PREFIX_PATH} ")
    111 foreach(_dir $ENV{CMAKE_PREFIX_PATH})
    112     message(STATUS "CMAKE_PREFIX_PATH  _dir ${_dir} ")
    113 endforeach()
    114 set(PLog_VERBOSE ON)
    115 
    116 find_package(G4OK CONFIG QUIET)
    117 if(G4OK_FOUND)
    118    add_compile_definitions(WITH_G4OPTICKS)
    119 
    120    message( STATUS " PLog_INCLUDE_DIR:${PLog_INCLUDE_DIR} ")
    121    include_directories(${PLog_INCLUDE_DIR})  ## WHY NOT AUTO ? 
    122 
    123 endif()
    124 message(STATUS "cmake/JUNODependencies.cmake : G4OK_FOUND:${G4OK_FOUND}" )
    125 




After being sure to clean, get to different error.  Suspect that need to clean and reconfig to effect CMake changes.::

    jm 
    make clean 
    jm-cmake
    jm 


::

    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:22:10: fatal error: GtOpticksTool.h: No such file or directory
     #include "GtOpticksTool.h"
              ^~~~~~~~~~~~~~~~~

         ^

::

    N[blyth@localhost offline]$ vi /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc 
    N[blyth@localhost offline]$ find . -name GtOpticksTool.h 
    ./Simulation/GenTools/src/GtOpticksTool.h
    N[blyth@localhost offline]$ 


/data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/CMakeLists.txt::

     01 
      2 include (PKG)
      3 PKG (PMTSim
      4     DEPENDS
      5         SimUtil
      6         IPMTSimParamSvc
      7         Geometry
      8         MultiFilmSimSvc
      9         MCParamsSvc
     10 
     11         $<$<BOOL:${G4OK_FOUND}>:Opticks::G4OK>  
     12 )

/data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/cmt/requirements::


     01 package PMTSim
      2 
      3 use SniperRelease   v*
      4 use DetSimPolicy    v*  Simulation/DetSimV2
      5 use SimUtil         v*  Simulation/DetSimV2
      6 # use GenSim          v*  Simulation/DetSimV2
      7 use Geometry        v*  Detector
      8 
      9 use DetSimAlg       v*  Simulation/DetSimV2
     10 use IPMTSimParamSvc  v*  Simulation/SimSvc
     11 use MultiFilmSimSvc  v*  Simulation/SimSvc
     12 
     13 use GenTools        v*  Simulation
     14 
     15 
     16 library PMTSim *.cc
     17 macro_append PMTSim_cppflags " -I$(PMTSIMROOT)/../SimUtil/include "
     18 # macro_append PMTSim_cppflags " -I$(PMTSIMROOT)/../GenSim/include "
     19 
     20 apply_pattern linker_library library=PMTSim
     21 include_dirs "$(PMTSIMROOT)/include"
     22 macro_append PMTSim_cppflags "" opticks " -g "



Hmm looks like headers from src are not being installed::

    N[blyth@localhost offline]$ l InstallArea/include/GenTools/
    total 12
    4 drwxrwxr-x. 44 blyth blyth 4096 Dec  4 01:07 ..
    0 drwxr-xr-x.  2 blyth blyth   48 Dec  4 01:07 .
    4 -rw-r--r--.  1 blyth blyth  590 Dec  4 01:05 GenEventBuffer.h
    4 -rw-r--r--.  1 blyth blyth  240 Dec  4 01:05 IGenTool.h
    N[blyth@localhost offline]$ 

Gentools are mostly used from python::

    N[blyth@localhost offline]$ jgr \"Gt
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        gun_pos = gt.createTool("GtPositionerTool")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        gun = gt.createTool("GtGunGenTool/gun")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        ok = gt.createTool("GtOpticksTool/ok")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        gun = gt.createTool("GtOpScintTool/gun")
    ...
    ./Simulation/GenDecay/src/DecayRates.cpp://            throw GaudiException(err.str(),"GtDecayerator::DecayRates",StatusCode::FAILURE);
    ./Simulation/GenDecay/src/DecayRates.cpp://        throw GaudiException(err.str(),"GtDecayerator::DecayRates",StatusCode::FAILURE);
    ./Simulation/GenDecay/src/GtDecayerator.cpp:#include "GtDecayerator.h"

    // NOPE: GtDecayerator.h comes from Simulation/GenDecay/src/

    ./Simulation/GenDecay/share/pyjob.py:era = gt.createTool("GtDecayerator")
    ./Simulation/GenDecay/share/pyjob.py:toffset = gt.createTool("GtTimeOffsetTool")
    Binary file ./Simulation/ElecSimV3/ElecSimAlg/share/pmt_tof_map.root matches
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtHepEvtGenTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtPelletronBeamerTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtSNTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtNeutronTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    dumper = gt.createTool("GtHepMCDumper")
    ./Simulation/GenTools/src/GtPositionerTool.cc:#include "GtPositionerTool.h"
    ./Simulation/GenTools/src/GtGstTool.cc:#include "GtGstTool.h"
    ./Simulation/GenTools/src/GtTimeOffsetTool.cc:#include "GtTimeOffsetTool.h"


* fixed this by moving the GtOpticksTool.h into GenTools so it gets installed


::

    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc: In member function ‘virtual G4bool junoSD_PMT_v2::ProcessHits(G4Step*, G4TouchableHistory*)’:
    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:411:113: error: ‘volname’ was not declared in this scope
             if(m_ce_mode == "20inch") m_PMTEfficiencyCheck->addHitRecord( pmtID, global_pos, local_pos, qe, ce, de, volname, ce_cat);
                                                                                                                     ^~~~~~~
    In file 

* commented this out 



::

    [ 98%] Building CXX object Simulation/DetSimV2/AnalysisCode/CMakeFiles/AnalysisCode.dir/src/MuFastnProcessAnaMgr.cc.o
    [ 98%] Building CXX object Simulation/DetSimV2/AnalysisCode/CMakeFiles/AnalysisCode.dir/src/PrintG4TrackAnaMgr.cc.o
    /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:56:10: fatal error: X4PhysicsOrderedFreeVector.hh: No such file or directory
     #include "X4PhysicsOrderedFreeVector.hh"
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* this is an opticks change 

Its better to use the typedef, for Geant4 version change handling::

     62 typedef G4PhysicsOrderedFreeVector G4MaterialPropertyVector;




Hmm now seems to build with opticks and tds3 runs... but trying to switch off Opticks use not working
--------------------------------------------------------------------------------------------------------

* huh : deleting the build dir doesnt return to no-opticks

::
 
   jo
   rm -rf build
   mkdir build
   jm-cmake 0 


The problem is that are still finding G4OK because CMAKE_PREFIX_PATH contains the OPTICKS_PREFIX::

   find_package(G4OK CONFIG QUIET)





::

    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/python-cython/0.29.24 
    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/python-pip/21.2.4 
    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/python-setuptools/58.0.4 
    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/Python/3.8.12 
    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/opticks/head 
    -- CMAKE_PREFIX_PATH  _prefix /data/blyth/junotop/ExternalLibs/opticks/head/externals 
    -- CMAKE_PREFIX_PATH  _prefix /home/blyth/local/opticks/externals/OptiX_650 
    CMake Error at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      No "FindG4.cmake" found in CMAKE_MODULE_PATH.
    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:119 (find_package)
      CMakeLists.txt:36 (include)


    CMake Warning (dev) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package):
      FindG4.cmake must either be part of this project itself, in this case
      adjust CMAKE_MODULE_PATH so that it points to the correct location inside
      its source tree.

      Or it must be installed by a package which has already been found via
      find_package().  In this case make sure that package has indeed been found
      and adjust CMAKE_MODULE_PATH to contain the location where that package has
      installed FindG4.cmake.  This must be a location provided by that package.
      This error in general means that the buildsystem of this project is relying
      on a Find-module without ensuring that it is actually available.

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/cfg4/cfg4-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2/share/cmake-3.21/Modules/CMakeFindDependencyMacro.cmake:47 (find_package)
      /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/g4ok/g4ok-config.cmake:8 (find_dependency)
      cmake/JUNODependencies.cmake:119 (find_package)
      CMakeLists.txt:36 (include)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/offline/build/CMakeFiles/CMakeOutput.log".
    See also "/data/blyth/junotop/offline/build/CMakeFiles/CMakeError.log".
    N[blyth@localhost build]$ 



How to switch Opticks config ON/OFF ?
---------------------------------------

* need to control the runtime environment 

* hmm: would be better not to hookup opticks in $JUNOTOP/bashrc.sh
  instead leave it separate like sniper


::


    N[blyth@localhost offline]$ t j-runtime-env-
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
            source $JUNOTOP/sniper/InstallArea/bashrc;
            source $JUNOTOP/offline/InstallArea/setup.sh;
        fi;
        echo $msg
    }
    N[blyth@localhost offline]$ cat $JUNOTOP/bashrc.sh
    export JUNOTOP=/data/blyth/junotop
    export CMTPROJECTPATH=/data/blyth/junotop:${CMTPROJECTPATH}
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.8.12/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.0.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/21.2.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.24/bashrc
    source /data/blyth/junotop/ExternalLibs/python-numpy/1.21.2/bashrc
    source /data/blyth/junotop/ExternalLibs/Boost/1.77.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Cmake/3.21.2/bashrc
    source /data/blyth/junotop/ExternalLibs/Git/2.33.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Xercesc/3.2.2/bashrc
    source /data/blyth/junotop/ExternalLibs/gsl/2.5/bashrc
    source /data/blyth/junotop/ExternalLibs/fftw3/3.3.8/bashrc
    source /data/blyth/junotop/ExternalLibs/sqlite3/3.35.5/bashrc
    source /data/blyth/junotop/ExternalLibs/log4cpp/1.1.3/bashrc
    source /data/blyth/junotop/ExternalLibs/libxml2/2.9.12/bashrc
    source /data/blyth/junotop/ExternalLibs/LHAPDF/6.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/pythia6/6.4.28/bashrc
    source /data/blyth/junotop/ExternalLibs/tbb/2019_U8/bashrc
    source /data/blyth/junotop/ExternalLibs/CMT/v1r26/bashrc
    source /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/bashrc
    source /data/blyth/junotop/ExternalLibs/xrootd/5.3.1/bashrc
    source /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bashrc
    source /data/blyth/junotop/ExternalLibs/HepMC/2.06.09/bashrc
    source /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /data/blyth/junotop/ExternalLibs/genie/3.00.06/bashrc
    source /data/blyth/junotop/ExternalLibs/nuwro/19.02.2/bashrc
    source /data/blyth/junotop/ExternalLibs/talys/1.95/bashrc
    source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    source /data/blyth/junotop/ExternalLibs/mysql-connector-c/6.1.9/bashrc
    source /data/blyth/junotop/ExternalLibs/mysql-connector-cpp/1.1.12/bashrc
    source /data/blyth/junotop/ExternalLibs/libyaml/0.2.4/bashrc
    source /data/blyth/junotop/ExternalLibs/python-yaml/5.4.1.1/bashrc
    source /data/blyth/junotop/ExternalLibs/pacparser/1.3.7/bashrc
    source /data/blyth/junotop/ExternalLibs/frontier/2.9.1/bashrc
    source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Mon Dec 6 20:49:40 CST 2021
    N[blyth@localhost offline]$ 

Hmm but already have a way to remove the hookup::

    N[blyth@localhost junoenv]$ bash junoenv opticks unhookup

And then start a new session + jre to avoid mixage between envs.


Hmm : how to cleanly fail to find G4OK 
----------------------------------------

* currently after switching off the opticks prefixes in CMAKE_PREFIX_PATH the 
  failed attempt to find G4OK results in an error...

* need a cleaner way to fail

* the WITH_OPTICKS switch in the below is a workaround for that : by detecting 
  if the opticks prefixes are in the CMAKE_PREFIX_PATH prior to the cmake command 
  line and pass in the decision WITH_OPTICKS 

* suspect CMake caching might be involved with a failure to switch 
  opticks use off


$JUNOTOP/offline/cmake/JUNODependencies.cmake::

    ## Opticks
    set(G4OK_FOUND NO)
    if(${WITH_OPTICKS})
        foreach(_dir ${CMAKE_MODULE_PATH})
            message(STATUS "CMAKE_MODULE_PATH  _dir ${_dir} ") 
        endforeach() 

        set(_prefix_list)
        string(REPLACE ":" ";" _prefix_list $ENV{CMAKE_PREFIX_PATH})
        foreach(_prefix ${_prefix_list})
            message(STATUS "CMAKE_PREFIX_PATH  _prefix ${_prefix} ") 
        endforeach() 

        find_package(G4OK CONFIG QUIET)

        if(G4OK_FOUND)
           add_compile_definitions(WITH_G4OPTICKS)
           message( STATUS " PLog_INCLUDE_DIR:${PLog_INCLUDE_DIR} ")
           include_directories(${PLog_INCLUDE_DIR})  ## WHY NOT AUTOMATIC ? Maybe because plog is header only ?
        endif()
    endif()
    message(STATUS "cmake/JUNODependencies.cmake : WITH_OPTICKS:${WITH_OPTICKS} G4OK_FOUND:${G4OK_FOUND}" )



::

    N[blyth@localhost offline]$ t jm-cmake-
    jm-cmake- () 
    { 
        : opticks ON/OFF switch based on contents of CMAKE_PREFIX_PATH;
        local mode=${1:-1};
        local bdir=$(jm-bdir);
        local sdir=$(jm-sdir);
        local idir=$(jm-idir);
        local cmake_has_opticks=$(jm-cmake-has-opticks);
        local extra="";
        if [ "$cmake_has_opticks" == "1" ]; then
            if [ -d "$JUNOTOP/opticks/cmake/Modules" ]; then
                extra="$extra -DCMAKE_MODULE_PATH=$JUNOTOP/opticks/cmake/Modules";
            fi;
            if [ -n "$OPTICKS_PREFIX" ]; then
                extra="$extra -DOPTICKS_PREFIX=$OPTICKS_PREFIX";
            fi;
        fi;
        cat  <<EOC
       cmake $sdir          -DCMAKE_INSTALL_PREFIX=$idir          -DCMAKE_CXX_STANDARD=17          $extra

    EOC

    }



Back to Opticks to try to encapsulate this setup into ~/opticks/cmake/Modules/FindOpticks.cmake
-------------------------------------------------------------------------------------------------

* fixed this by adding "include(GNUInstallDirs)" 

Getting errors from the BCM generated properties::


    CMake Error at /usr/local/opticks/lib/cmake/g4ok/properties-g4ok-targets.cmake:6 (set_target_properties):
      set_target_properties called with incorrect number of arguments.
    Call Stack (most recent call first):
      /usr/local/opticks/lib/cmake/g4ok/g4ok-config.cmake:15 (include)
      /Users/blyth/opticks/cmake/Modules/FindOpticks.cmake:32 (find_package)
      CMakeLists.txt:10 (find_package)


    CMake Error at /usr/local/opticks/lib/cmake/g4ok/properties-g4ok-targets.cmake:7 (set_target_properties):
      set_target_properties called with incorrect number of arguments.
    Call Stack (most recent call first):
      /usr/local/opticks/lib/cmake/g4ok/g4ok-config.cmake:15 (include)
      /Users/blyth/opticks/cmake/Modules/FindOpticks.cmake:32 (find_package)
      CMakeLists.txt:10 (find_package)


::

      1 
      2 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_PKG_CONFIG_NAME G4OK)
      3 
      4 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_INSTALL_CONFIGFILE_BCM ${CMAKE_CURRENT_LIST_FILE})
      5 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_INSTALL_CONFIGDIR_BCM ${CMAKE_CURRENT_LIST_DIR})
      6 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_INSTALL_LIBDIR_BCM ${CMAKE_INSTALL_LIBDIR})
      7 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_INSTALL_INCLUDEDIR_BCM ${CMAKE_INSTALL_INCLUDEDIR})
      8 set_target_properties(Opticks::G4OK PROPERTIES INTERFACE_INSTALL_PREFIX_BCM ${CMAKE_INSTALL_PREFIX})



Can the extras on the CMake command line be avoided ?
----------------------------------------------------------

If the cmake/Modules were installed could automatically determine the OPTICKS_PREFIX from the
find result. But have to tell CMake where to look anyhow. 

The prefix in use can be determined from the CMAKE_PREFIX_PATH ... where is that coming 
from. 

$JUNOTOP/bashrc.sh hookup line::

   source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Tue Dec 7 19:32:37 CST 2021

From the setup...

    # mandatory envvars from buildenv propagated into userenv via this setup
    export OPTICKS_PREFIX=/data/blyth/junotop/ExternalLibs/opticks/head

So that means can rely on OPTICKS_PREFIX envvar 




::

    N[blyth@localhost build]$ find /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf/properties-okconf-targets.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf/okconf-targets.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf/okconf-targets-debug.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf/okconf-config.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/okconf/okconf-config-version.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/sysrap
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/sysrap/properties-sysrap-targets.cmake
    /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/sysrap/sysrap-targets.cmake



::

    ## Opticks
    if(DEFINED ENV{OPTICKS_PREFIX})
       set(Opticks_VERBOSE YES)
       set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{JUNOTOP}/opticks/cmake/Modules")
       find_package(Opticks QUIET MODULE)
       message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
    endif()



runtime error following opticks switch off not followed by a rebuild
-------------------------------------------------------------------------

* easy fix is just to make before running after changing opticks on/off
* hmm: this may indicate that CMake is cleverer than CMT regarding staleness from changes to preprocessor macros 
* with CMT had to do a manual touchbuild after flipping the opticks switch   

::

    jm-cmake
    make
    make install 


    ='geom-geom-20pmt.root', voxel_merge_flag=False, voxel_merge_twin=1, voxel_npe_file='npehist3d_single.root', voxel_pmts_structs=True, voxel_quenching_scale=0.93, voxel_save_hits=True, voxel_time_file='dist_tres_single.root', wp_enabled=True, wp_latticed_enabled=True, wp_pmt_enabled=True)
    == ROOT IO Svc ==
    == Buffer Memory Management ==
    == Random Svc ==
    == Root Writer ==
     == PMTSimParamSvc == 
    GENTOOL MODE:  gun
    SNiPER:Unknown.loadDll         FATAL: libG4OK.so: cannot open shared object file: No such file or directory
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 87, in run
        module.init(self.toptask, self.args)
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNODetSimModule.py", line 124, in init
        self.init_gentools(toptask, args)
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNODetSimModule.py", line 912, in init_gentools
        self.setup_generator(task, args)
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNODetSimModule.py", line 1021, in setup_generator
        import GenTools
      File "/data/blyth/junotop/offline/InstallArea/python/GenTools/__init__.py", line 6, in <module>
        Sniper.loadDll("libGenTools.so")
    RuntimeError: Can't load DLL libGenTools.so
    junotoptask:detsimiotask.terminate  WARN: invalid state tranform ((Invalid)) => ((EndUp))
    junotoptask.terminate           WARN: invalid state tranform ((Invalid)) => ((EndUp))

    **************************************************
    Terminating @ localhost.localdomain on Tue Dec  7 22:08:36 2021
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Can't load DLL libGenTools.so

    [Inferior 1 (process 351819) exited with code 01]




HMM offline/cmake/Modules/PKG.cmake misuses AUX_SOURCE_DIRECTORY
------------------------------------------------------------------

* https://cmake.org/cmake/help/latest/command/aux_source_directory.html

It is tempting to use this command to avoid writing the list of source files
for a library or executable target. While this seems to work, there is no way
for CMake to generate a build system that knows when a new source file has been
added. Normally the generated build system knows when it needs to rerun CMake
because the CMakeLists.txt file is modified to add a new source. When the
source is just added to the directory without modifying this file, one would
have to manually rerun CMake to generate a build system incorporating the new
file.


