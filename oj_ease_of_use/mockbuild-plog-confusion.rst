mockbuild-plog-confusion
==========================


::

    ~/sandbox/docker-mock-gitlab-ci.sh run

    ~/sandbox/docker-mock-gitlab-ci.sh exec




exec : CMake Issue : version mixup : should be v0.3.3
-----------------------------------------------------------

::


    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    Found libonnxruntime /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/libonnxruntime/1.17.3/lib64/libonnxruntime.so
    -- /data1/blyth/local/opticks_Debug/Opticks-v0.3.3/x86_64--gcc11-geant4_10_04_p02-dbg/cmake/Modules/FindOpticks.cmake : PLog_INCLUDE_DIR :/data1/blyth/local/opticks_Debug/Opticks-v0.3.1/x86_64--gcc11-geant4_10_04_p02-dbg/externals/plog/include 
    -- /data1/blyth/local/opticks_Debug/Opticks-v0.3.3/x86_64--gcc11-geant4_10_04_p02-dbg/cmake/Modules/FindOpticks.cmake : Opticks_TARGET   :Opticks::G4CX 
    -- /data1/blyth/local/opticks_Debug/Opticks-v0.3.3/x86_64--gcc11-geant4_10_04_p02-dbg/cmake/Modules/FindOpticks.cmake : Opticks_FOUND    :YES 
    -- /home/juno/junosw/cmake/legacy/JUNODependencies.cmake : Opticks_FOUND:YES
    XOD_PREFIX: /home/juno/junosw/XmlObjDesc


    ...


    -- Configuring done (41.4s)
    CMake Error in Generator/GenGenie/CMakeLists.txt:
      Imported target "Opticks::G4CX" includes non-existent path

        "/data1/blyth/local/opticks_Debug/Opticks-v0.3.1/x86_64--gcc11-geant4_10_04_p02-dbg/externals/plog/include"

      in its INTERFACE_INCLUDE_DIRECTORIES.  Possible reasons include:

      * The path was deleted, renamed, or moved to another location.

      * An install or uninstall procedure did not complete successfully.

      * The installation package was faulty and references files it does not
      provide.





fixed by cleaning the build before the exec
---------------------------------------------

::

    ~/sandbox/docker-mock-gitlab-ci.sh run

    cd ~/junosw && sudo rm -rf build InstallArea  ## for clean build test 

    ~/sandbox/docker-mock-gitlab-ci.sh exec



