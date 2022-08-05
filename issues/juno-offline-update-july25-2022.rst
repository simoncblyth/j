juno-offline-update-july25-2022
==================================

* reverted working copy changes to MaskManagers : the changes are safe in jps

  * see :doc:`MaskManagers`


Follow along the installation again

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation

* preq
* jlibs 

  * libmore hang for datafiles, ctrl-c out of it 
  * libonnxruntime another hang, ctrl-c out of it  


Plough on::

    je
    bash junoenv sniper


    jo 
    svn up

    ./build_Debug.sh




j/PMTSim uses om for building
-------------------------------

So it installs into Opticks install dirs::

    -- Installing: /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/pmtsim/pmtsim-targets.cmake
    -- Installing: /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/pmtsim/pmtsim-targets-debug.cmake
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/pmtsim/pmtsim-config.cmake
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/lib64/cmake/pmtsim/pmtsim-config-version.cmake
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/include/PMTSim/PMTSim.hh
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/include/PMTSim/P4Volume.hh
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/include/PMTSim/PMTSIM_API_EXPORT.hh
    -- Up-to-date: /data/blyth/junotop/ExternalLibs/opticks/head/include/PMTSim/SCanvas.hh


* This means that there is no way to prevent it being found by find_package. 
* This means that when offline depends on Opticks proj that find_package(PMTSim) it will be found

There is also nameclash risk with original PMTSim 

* DONE : changed PMTSIM_STANDALONE to be PRIVATE, that seems to fix the offline build

* PERHAPS : should rename j/PMTSim to StandlonePMTSim OR jPMTSim to avoid confusion


PMTSIM_STANDALONE flag leaking into offline CMake build : try making it PRIVATE
----------------------------------------------------------------------------------


::

    In file included from /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:25:
    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh:12:10: fatal error: IGeomManager.h: No such file or directory
     #include "IGeomManager.h"
              ^~~~~~~~~~~~~~~~
    compilation terminated.


HUH : PMTSIM_STANDALONE should not be switched on in standard build::

     10 
     11 #ifdef PMTSIM_STANDALONE
     12 #include "IGeomManager.h"
     13 #else
     14 #include "SniperKernel/ToolBase.h"
     15 #include "DetSimAlg/IPMTElement.h"
     16 #include "Geometry/IPMTParamSvc.h"
     17 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
     18 #endif


    N[blyth@localhost offline]$ jgr PMTSIM_STANDALONE 
    ./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/ZSolid.h:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:#ifdef PMTSIM_STANDALONE
    ./build/Generator/NuSolGen/CMakeFiles/NuSolGen.dir/flags.make:CXX_DEFINES = -DBOOST_ATOMIC_DYN_LINK -DBOOST_ATOMIC_NO_LIB -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_FILESYSTEM_NO_LIB -DBOOST_PROGRAM_OPTIONS_DYN_LINK -DBOOST_PROGRAM_OPTIONS_NO_LIB -DBOOST_REGEX_DYN_LINK -DBOOST_REGEX_NO_LIB -DBOOST_SYSTEM_DYN_LINK -DBOOST_SYSTEM_NO_LIB -DG4INTY_USE_XT -DG4MULTITHREADED -DG4UI_USE -DG4UI_USE_TCSH -DG4USE_STD11 -DG4VERBOSE -DG4VIS_USE -DG4VIS_USE_OPENGL -DG4VIS_USE_OPENGLX -DG4VIS_USE_RAYTRACERX -DG4_STORE_TRAJECTORY -DNuSolGen_EXPORTS -DOPTICKS_BRAP -DOPTICKS_CFG4 -DOPTICKS_CUDARAP -DOPTICKS_G4OK -DOPTICKS_GGEO -DOPTICKS_NPY -DOPTICKS_OKCONF -DOPTICKS_OKCORE -DOPTICKS_OKGEO -DOPTICKS_OKOP -DOPTICKS_OXRAP -DOPTICKS_PMTSIM -DOPTICKS_SYSRAP -DOPTICKS_THRAP -DOPTICKS_X4 -DPMTSIM_STANDALONE -DSNIPER_VERSION_2 -DWITH_BOOST_ASIO -DWITH_G4OPTICKS -DWITH_PLOG -DWITH_PMTSIM -DWITH_STTF
    ./build/Generator/GenGenie/CMakeFiles/GenGenie.dir/flags.make:CXX_DEFINES = -DBOOST_ATOMIC_DYN_LINK -DBOOST_ATOMIC_NO_LIB -DBOOST_FILESYSTEM_DYN_LINK -DBOOST_FILESYSTEM_NO_LIB


::

    epsilon:opticks blyth$ opticks-f PMTSIM_STANDALONE
    ./extg4/X4SolidTree.hh:#ifdef PMTSIM_STANDALONE
    epsilon:opticks blyth$ 

The only such switch is j/PMTSim/CMakeLists.txt, changed it from PUBLIC to PRIVATE::

     55 target_compile_definitions( ${name} PRIVATE OPTICKS_PMTSIM PMTSIM_STANDALONE )

Opticks use of j/PMTSIM should not be leaking into the standard build. 


::

    epsilon:opticks blyth$ find . -name CMakeLists.txt -exec grep -H PMTSIM {} \;
    ./extg4/CMakeLists.txt:    target_compile_definitions( ${name} PUBLIC WITH_PMTSIM )
    ./extg4/tests/CMakeLists.txt:set(PMTSIM_TEST_SOURCES
    ./extg4/tests/CMakeLists.txt:foreach(TEST_CC_SRC ${PMTSIM_TEST_SOURCES})
    ./extg4/tests/CMakeLists.txt:       target_compile_definitions( ${TGT} PUBLIC WITH_PMTSIM )
    ./GeoChain/CMakeLists.txt:   target_compile_definitions( ${name} PUBLIC WITH_PMTSIM )
    ./g4ok/tests/CMakeLists.txt:set(PMTSIM_TEST_SOURCES
    ./g4ok/tests/CMakeLists.txt:foreach(TEST_CC_SRC ${PMTSIM_TEST_SOURCES})
    ./g4ok/tests/CMakeLists.txt:       target_compile_definitions( ${TGT} PUBLIC WITH_PMTSIM )
    ./u4/CMakeLists.txt:    target_compile_definitions( ${name} PUBLIC WITH_PMTSIM )
    epsilon:opticks blyth$ 


extg4/CMakeLists.txt::

    050 find_package(PMTSim CONFIG)


    222 if(PMTSim_FOUND)
    223     target_link_libraries( ${name} PUBLIC Opticks::PMTSim )
    224     target_compile_definitions( ${name} PUBLIC WITH_PMTSIM )
    225 endif()
    226 
    227 

HMM : this could be name clash with the real PMTSim ? 




OpticksFlags::FlagMask -> OpticksPhoton::FlagMask
------------------------------------------------------

::

    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc: In member function 'void junoSD_PMT_v2_Opticks::dumpHit(unsigned int, const G4OpticksHit*, const G4OpticksHitExtra*) const':
    /data/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:314:50: error: 'FlagMask' is not a member of 'OpticksFlags'
             << " " << std::setw(20) << OpticksFlags::FlagMask(hit->flag_mask, true)
                                                      ^~~~~~~~
    [ 94%] Built target GenDecay
    make[2]: *** [Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/src/junoSD_PMT_v2_Opticks.cc.o] Error 1
    make[2]: *** Waiting for unfinished jobs....
    [ 94%] Built target GenGenie
    make[1]: *** [Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/all] Error 2
    make: *** [all] Error 2
    ERROR: ERROR Found during make stage. 

::

    N[blyth@localhost offline]$ jcv junoSD_PMT_v2_Opticks




opticks connection
---------------------

.bashrc::

     44 export OPTICKS_CUDA_PREFIX=/usr/local/cuda
     45 
     46 export OPTICKS_OPTIX6_PREFIX=/home/blyth/local/opticks/externals/OptiX_650
     47 export OPTICKS_OPTIX7_PREFIX=/home/blyth/local/opticks/externals/OptiX_700
     48 export OPTICKS_OPTIX_PREFIX=$OPTICKS_OPTIX7_PREFIX
     49 
     50 export OPTICKS_COMPUTE_CAPABILITY=70
     51 


* where are the Opticks packages hooked up ? 

  * cmake/Modulues/FindOpticks.cmake does find_package(G4OK ...
  * DONE: changed to G4CX  

* what was the special arrangement ? 

  1. symbolic "opticks" link from HOME into the junoenv managed opticks 

::

    opticks -> /data/blyth/junotop/opticks




    
