lxslc7-opticks-build
========================

default gcc cannot cxx17
---------------------------

::

    -- Configuring done
    CMake Error in CMakeLists.txt:
      Target "OKConf" requires the language dialect "CXX17" , but CMake does not
      know the compile flags to use to enable it.


Use devtoolset-8 to provide gcc 8.3.1 and cxx17::

      1 # ~/.bashrc
      2 [ "$DBG" == "1" ] && dbg_head $BASH_SOURCE
      3 
      4 # TODO: common linux setup scripts obtained from repo
      5 source /opt/rh/devtoolset-8/enable
      6 
      7 export G=/hpcfs/juno/junogpu/blyth   ## have to duplicate as scp seems to only run .bashrc ? 
      8 export JUNOTOP=$G/junotop



default L7 cmake version is too old to build opticks
-------------------------------------------------------

So need to update junoenv offline and hookup to the newer cmake that is installed via junoenv before rebuilding opticks on L7


::

    L7[blyth@lxslc710 opticks]$ om-cleaninstall
    rm -rf /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/opticks/head/build/okconf && mkdir -p /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/opticks/head/build/okconf
    === om-visit-one : okconf          /hpcfs/juno/junogpu/blyth/junotop/opticks/okconf             /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/opticks/head/build/okconf 
    === om-one-or-all cleaninstall : okconf          /hpcfs/juno/junogpu/blyth/junotop/opticks/okconf             /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/opticks/head/build/okconf 
    CMake Error: Error in cmake code at
    /hpcfs/juno/junogpu/blyth/junotop/opticks/okconf/CMakeLists.txt:12:
    Parse error.  Expected "(", got newline with text "
    ".


    L7[blyth@lxslc710 opticks]$ cmake --version
    cmake version 2.8.12.2
    L7[blyth@lxslc710 opticks]$ which cmake
    /usr/bin/cmake


    epsilon:opticks blyth$ cmake --version
    cmake version 3.17.1

    CMake suite maintained and supported by Kitware (kitware.com/cmake).
    epsilon:opticks blyth$ which cmake
    /opt/local/bin/cmake
    epsilon:opticks blyth$ 




