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

   jo          ## cd $JUNOTOP/offline

   ./build.sh 


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
   ./build.sh 

5. test the runtime by running tut_detsim.py::

   tds3



TODO: maybe avoid with/without opticks flip-flip rebuilding by having separate InstallArea for these two configs ?
--------------------------------------------------------------------------------------------------------------------







