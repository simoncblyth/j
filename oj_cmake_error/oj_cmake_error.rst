FIXED : oj_cmake_error/oj_cmake_error.rst
================================================

Issue : Opticks build against customized version of Custom4 does not CI build
--------------------------------------------------------------------------------

::

    CMake Error in Simulation/DetSimV2/PMTSim/CMakeLists.txt:
      Imported target "Opticks::G4CX" includes non-existent path
        "/data1/blyth/local/custom4_Debug/0.1.8/include/Custom4"
      in its INTERFACE_INCLUDE_DIRECTORIES.  Possible reasons include:
      * The path was deleted, renamed, or moved to another location.
      * An install or uninstall procedure did not complete successfully.
      * The installation package was faulty and references files it does not
      provide.


Look where the Custom4 version is hiding within Opticks release
-----------------------------------------------------------------

::

    (ok) A[blyth@localhost opticks_Debug]$ find lib64/cmake -type f -exec grep -h Custom4 {} \;
      INTERFACE_LINK_LIBRARIES "Opticks::G4;Opticks::SysRap;CLHEP::CLHEP;Opticks::OpticksXercesC;Opticks::GDXML;Custom4::Custom4"
    # Library: Custom4::Custom4
    find_dependency(Custom4)
      INTERFACE_INCLUDE_DIRECTORIES "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8/include/Custom4;${_IMPORT_PREFIX}/include/QUDARap"
      INTERFACE_INCLUDE_DIRECTORIES "/usr/local/cuda-12.4/targets/x86_64-linux/include;${_IMPORT_PREFIX}/externals/glm/glm;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8/include/Custom4;${_IMPORT_PREFIX}/include/SysRap"
    (ok) A[blyth@localhost opticks_Debug]$ find lib64/cmake -type f -exec grep -H Custom4 {} \;
    lib64/cmake/u4/u4-targets.cmake:  INTERFACE_LINK_LIBRARIES "Opticks::G4;Opticks::SysRap;CLHEP::CLHEP;Opticks::OpticksXercesC;Opticks::GDXML;Custom4::Custom4"
    lib64/cmake/u4/u4-config.cmake:# Library: Custom4::Custom4
    lib64/cmake/u4/u4-config.cmake:find_dependency(Custom4)
    lib64/cmake/qudarap/qudarap-targets.cmake:  INTERFACE_INCLUDE_DIRECTORIES "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8/include/Custom4;${_IMPORT_PREFIX}/include/QUDARap"
    lib64/cmake/sysrap/sysrap-targets.cmake:  INTERFACE_INCLUDE_DIRECTORIES "/usr/local/cuda-12.4/targets/x86_64-linux/include;${_IMPORT_PREFIX}/externals/glm/glm;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8/include/Custom4;${_IMPORT_PREFIX}/include/SysRap"
    (ok) A[blyth@localhost opticks_Debug]$ 



Solution : a clean rebuild and release v0.5.0 against the standard Custom4 from /cvmfs
------------------------------------------------------------------------------------------


Change c4 prefix in ~/j/local.sh to use the default::

    112 local_c4_prefix_default()
    113 {
    114     echo /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
    115 }
    116 local_c4_prefix()
    117 {
    118     echo $(local_c4_prefix_default)
    119     #echo /data1/blyth/local/custom4_Debug/0.1.8
    120 }


Do a full rebuild:: 

    om-prefix-clean   ## with newly enhanced deeper clean 

    local_ok_build

    opticks-full




