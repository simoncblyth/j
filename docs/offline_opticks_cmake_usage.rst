offline_opticks_cmake_usage
==============================

Remove Opticks from Offline CMake build
-----------------------------------------

1. remove the opticks hookup line from $JUNOTOP/bashrc.sh::

   jm-unhookup  # short for "cd $JUNOTOP/junoenv ; bash junoenv opticks unhookup" 

2. exit session and start a new one to avoid mixing of environments 
3. source the JUNO runtime environment::

   jre    

Which is short for::

    source $JUNOTOP/bashrc.sh;
    local sniper_cmt_setup=$JUNOTOP/sniper/SniperRelease/cmt/setup.sh;
    if [ -f $sniper_cmt_setup ]; then
        CMTEXTRATAGS= source $sniper_cmt_setup;
        source $JUNOTOP/offline/JunoRelease/cmt/setup.sh;
    else
        source $JUNOTOP/sniper/InstallArea/bashrc;
        source $JUNOTOP/offline/InstallArea/setup.sh;
    fi;

Dump the environment, to verify the opticks prefixes are not present::

    jr  

    jr () 
    { 
        echo CMAKE_PREFIX_PATH;
        echo $CMAKE_PREFIX_PATH | tr ":" "\n";
        echo OPTICKS_PREFIX $OPTICKS_PREFIX
    }


4. redo the CMake config and build::

   jo                       ## cd $JUNOTOP/offline
   ./build.sh               ## defaults to Release build 
   ./build_Debug.sh    
   ./build_RelWithDebInfo.sh    


5. test the runtime by running tut_detsim.py::

   tds0 


Add Opticks to the Offline CMake build
-------------------------------------------

1. add the opticks hookup line to $JUNOTOP/bashrc.sh::

   jm-hookup  # short for "cd $JUNOTOP/junoenv ; bash junoenv opticks hookup" 

2. exit session and start a new one to avoid mixing of environments 

3. source the JUNO runtime environment and dump it to check Opticks prefixes are present::

   jre    
   jr

4. redo the CMake config and build::

   jo          ## cd $JUNOTOP/offline

   ./build.sh        ## defaults to Release build 
   ./build_Debug.sh 

5. test the runtime by running tut_detsim.py::

   tds3



Building with other CMAKE_BUILD_TYPE than the default of Release
-------------------------------------------------------------------


Check the current CMAKE_BUILD_TYPE by looking the the cache, and rebuild to change it::

    N[blyth@localhost offline]$ grep CMAKE_BUILD_TYPE  build/CMakeCache.txt 
    CMAKE_BUILD_TYPE:STRING=Release

    N[blyth@localhost offline]$ JUNO_CMAKE_BUILD_TYPE=Debug ./build.sh 

    N[blyth@localhost offline]$ grep CMAKE_BUILD_TYPE  build/CMakeCache.txt 
    CMAKE_BUILD_TYPE:STRING=Debug

    N[blyth@localhost offline]$ ./build.sh           ## Release is the default 
    N[blyth@localhost offline]$ grep CMAKE_BUILD_TYPE  build/CMakeCache.txt 
    CMAKE_BUILD_TYPE:STRING=Release



::

    N[blyth@localhost offline]$ cat build_Debug.sh 
    #!/bin/bash

    JUNO_CMAKE_BUILD_TYPE=Debug ./build.sh




Reuse of geometry geocache from integrated Offline + Opticks running, eg from tds3
--------------------------------------------------------------------------------------

Peruse the logging from eg tsd3 running to find OPTICKS_KEY export line and add that to eg .bashrc beside
the mandatory Opticks envvars is an appropriate place.


Copy geometry GDML to laptop for checking geometry translation
----------------------------------------------------------------

Peruse logging to find path to the GDML file.

::

    epsilon:opticks blyth$ opticks-cd
    epsilon:opticks blyth$ pwd
    /usr/local/opticks

    epsilon:opticks blyth$ scp P:/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml .
    epsilon:opticks blyth$ mv origin_CGDMLKludge.gdml origin_CGDMLKludge_11dec2021.gdml

    epsilon:opticks blyth$ scp P:/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml .
    epsilon:opticks blyth$ mv origin.gdml origin_11dec2021.gdml














