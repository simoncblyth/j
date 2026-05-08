lxlogin_suspect_oj_build_flakey_with_client_opticks
=====================================================

* Failure right at cmake 99% ... probable OOM with the linker ? 
* Looks like this is a resource issue with a massive cmake build on lxlogin that by default uses "-j$(nproc)" ie "-j64".
* Reducing cores to one succeeds, but takes several hours to build::

    export NJOBS=1
    ljclient ljbb0c

* Gemini suggests to use "-j32".
* Non-client succeeds, maybe just depending on lxlogin load from other users at crucial big memory stage of the build::

    -- Installing: /hpcfs/juno/junogpu/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOVersionDefinition.cmake
    -- Installing: /hpcfs/juno/junogpu/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOSetupScripts.cmake
    -- Installing: /hpcfs/juno/junogpu/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOCommonDefinitions.cmake
    -- Installing: /hpcfs/juno/junogpu/blyth/junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOInstallOfflineSetup.cmake
    ~/junosw
    Thu May  7 16:13:16 CST 2026
                           JUNOTOP : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1 
               JUNO_OPTICKS_PREFIX : /hpcfs/juno/junogpu/blyth/local/opticks_Debug 
                          _JUNOTOP : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1 
              _JUNO_OPTICKS_PREFIX : /hpcfs/juno/junogpu/blyth/local/opticks_Debug 
                            _J_VER : J26.1.1 
                            _O_VER : opticks_Debug 
                           _OJ_VER : J26.1.1_opticks_Debug 
                          _OJ_SLUG : J26_1_1_opticks_Debug 
                           _J_ARCH : el9_amd64_gcc11 
                      _DAY_OF_WEEK : Thu 
                                d1 : Thu May  7 04:13:16 PM CST 2026 
                                s1 : 1068 
                           JUNOTOP : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1 
               JUNO_OPTICKS_PREFIX : /hpcfs/juno/junogpu/blyth/local/opticks_Debug 
                          _JUNOTOP : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1 
              _JUNO_OPTICKS_PREFIX : /hpcfs/juno/junogpu/blyth/local/opticks_Debug 
                            _J_VER : J26.1.1 
                            _O_VER : opticks_Debug 
                           _OJ_VER : J26.1.1_opticks_Debug 
                          _OJ_SLUG : J26_1_1_opticks_Debug 
                           _J_ARCH : el9_amd64_gcc11 
                      _DAY_OF_WEEK : Thu 
                                d1 : Thu May  7 04:13:16 PM CST 2026 
                                s1 : 1068 
                                d2 : Thu May  7 04:13:18 PM CST 2026 
                                s2 : 2 
    L[blyth@lxlogin004 junosw]$ ljbb0c






