junosw_opticks_plog_appender
=============================


issue caused by including wrong plog version in release : NOW FIXED
---------------------------------------------------------------------

::

    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 3 WITH_G4CXOPTICKS 
    python: /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/externals/plog/include/plog/Logger.h:22: plog::Logger<instance>& plog::Logger<instance>::addAppender(plog::IAppender*) [with int instance = 0]: Assertion `appender != this' failed.
     *** Break *** abort

    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================
    #0  0x00007fb40737c46c in waitpid () from /lib64/libc.so.6
    #1  0x00007fb4072f9f62 in do_system () from /lib64/libc.so.6
    #2  0x00007fb4005b692c in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/ROOT/6.26.06/lib/libCore.so
    #3  0x00007fb400824ee3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/ROOT/6.26.06/lib/libcppyy_backend3_9.so
    #4  0x00007fb4005b3ea1 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/ROOT/6.26.06/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007fb4072ed387 in raise () from /lib64/libc.so.6
    #7  0x00007fb4072eea78 in abort () from /lib64/libc.so.6
    #8  0x00007fb4072e61a6 in __assert_fail_base () from /lib64/libc.so.6
    #9  0x00007fb4072e6252 in __assert_fail () from /lib64/libc.so.6
    #10 0x00007fb3d858356f in plog::Logger<0>::addAppender(plog::IAppender*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so
    #11 0x00007fb3d858313d in plog::Logger<0>& plog::init<0>(plog::Severity, plog::IAppender*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so
    #12 0x00007fb3d8123586 in void OK_PMTSIM_LOG::Init<0>(int, void*, void*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    #13 0x00007fb3d85812fd in DetSim0Svc::initializeOpticks() () from /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so
    #14 0x00007fb3d857ff5d in DetSim0Svc::initialize() () from /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so
    #15 0x00007fb3e55a8b56 in DleSupervisor::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fb3e55be0eb in Task::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so


Avoided the crash by commenting the log setup::

    N[blyth@localhost junosw]$ git diff Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    diff --git a/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc b/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    index 0534070..bbc8fd1 100644
    --- a/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    +++ b/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    @@ -308,8 +308,8 @@ bool DetSim0Svc::initializeOpticks()
     #ifdef WITH_G4CXOPTICKS
         // TODO: arrange logging setup earlier than this 
         OPTICKS_ELOG("DetSim0Svc_CXOK"); 
    -    OK_PMTSIM_LOG_(0) ;
    -    OK_PHYSISIM_LOG_(0) ;
    +    //OK_PMTSIM_LOG_(0) ;
    +    //OK_PHYSISIM_LOG_(0) ;
     #else
         LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS " << std::endl ; 
         assert(0); 
    N[blyth@localhost junosw]$ 

But that leads to debug messages appearing::

    2023-11-13 10:31:51.852 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0303000303000[  0,  3,  1,  0]) m_eph EPH_NEDEP
    2023-11-13 10:31:51.943 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0302000302000[  0,  3,  1,  0]) m_eph EPH_NEDEP
    2023-11-13 10:31:52.034 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0301000301000[  0,  3,  1,  0]) m_eph EPH_NEDEP
    2023-11-13 10:31:52.132 INFO  [125388] [U4Recorder::PreUserTrackingAction_Optical@374]  modulo 100000 : ulabel.id 300000
    2023-11-13 10:31:52.132 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0300000300000[  0,  3,  1,  0]) m_eph EPH_NEDEP
    2023-11-13 10:31:52.221 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0299000299000[  0,  3,  1,  0]) m_eph EPH_NEDEP
    2023-11-13 10:31:52.313 DEBUG [125388] [junoSD_PMT_v2::ProcessHits@371]  label C4Track::Desc C4Pho (gs:ix:id:gn   0298000298000[  0,  3,  1,  0]) m_eph EPH_NEDEP

::

     359 #ifdef WITH_G4CXOPTICKS
     360 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     361 {
     362     G4bool is_hit = ProcessHits_(step, nullptr) ;
     363     m_jpmt_dbg->add( m_eph, is_hit );
     364 
     365     G4Track* track = step->GetTrack() ;
     366     int label_id = C4Track::GetLabelID(track);
     367 
     368     C4Track::SetLabelEph(track, m_eph);
     369     C4Track::IncrementLabelExt(track) ;
     370 
     371     LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     372 
     373     return is_hit ;
     374 }
     375 




jcv OK_PMTSIM_LOG::

     25 template void OK_PMTSIM_LOG::Init<0>( int, void*, void* ); 
     26 template void OK_PMTSIM_LOG::Init<1>( int, void*, void* ); 

     07 //#define OK_PMTSIM_LOG_( IDX ) {  OK_PMTSIM_LOG::Initialize(plog::get<IDX>()->getMaxSeverity(), plog::get<IDX>(), nullptr ); }  
      8 #define OK_PMTSIM_LOG_( IDX ) {  OK_PMTSIM_LOG::Init<IDX>( info, plog::get<IDX>(), nullptr ) ; }
      9 


::

     24 #define SYSRAP_LOG__  {       SYSRAP_LOG::Initialize(SLOG::instance->prefixlevel_parse( info, "SYSRAP"), plog::get(), NULL );  } 
     25 #define SYSRAP_LOG_ {         SYSRAP_LOG::Initialize(plog::get()->getMaxSeverity(), plog::get(), NULL ); } 
     26 #define _SYSRAP_LOG( IDX ) {  SYSRAP_LOG::Init<IDX>( info, plog::get<IDX>(), nullptr ) ; }



Check the plog version in use
-------------------------------


Somehow the version of plog in the release is not my pinned one, looks to be an old one. From the download cache::

    /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/externals/plog/include/plog

This is my pinning fork, made sometime after Sep 2022::

    epsilon:plog blyth$ git remote -v
    origin	git@github.com:simoncblyth/plog.git (fetch)
    origin	git@github.com:simoncblyth/plog.git (push)
    epsilon:plog blyth$ git log -n1
    commit cb86692e6a4e7100729a071203a9aa96452ae791 (HEAD -> master, origin/master, origin/HEAD)
    Author: Sergey Podobry <sergey.podobry@gmail.com>
    Date:   Fri Sep 30 18:08:07 2022 +0300

        Fix building on C++ Builder 10.4 (#225)
    epsilon:plog blyth$ 


    epsilon:plog blyth$ find . -type f -exec grep -H PLOG_LOCAL {} \;
    ./include/plog/Util.h:#   elif defined(PLOG_LOCAL)
    ./README.md:|PLOG_LOCAL|Linux/Unix|Local|
    ./README.md:|PLOG_LOCAL|Windows|Local|
    ./README.md:*Important: don't forget to specify `PLOG_LOCAL` sharing mode on Linux/Unix systems for this sample.*
    ./samples/Chained/CMakeLists.txt:    target_compile_definitions(ChainedApp PRIVATE PLOG_LOCAL)
    ./samples/Chained/CMakeLists.txt:    target_compile_definitions(ChainedLib PRIVATE PLOG_LOCAL)
    ./samples/NotShared/CMakeLists.txt:    # define PLOG_LOCAL to make plog instances local (not shared between shared objects)
    ./samples/NotShared/CMakeLists.txt:    target_compile_definitions(NotSharedApp PRIVATE PLOG_LOCAL)
    ./samples/NotShared/CMakeLists.txt:    # define PLOG_LOCAL to make plog instances local (not shared between shared objects)
    ./samples/NotShared/CMakeLists.txt:    target_compile_definitions(NotSharedLib1 PRIVATE PLOG_LOCAL)
    ./samples/NotShared/CMakeLists.txt:    # define PLOG_LOCAL to make plog instances local (not shared between shared objects)
    ./samples/NotShared/CMakeLists.txt:    target_compile_definitions(NotSharedLib2 PRIVATE PLOG_LOCAL)
    ./samples/NotShared/NotSharedLib2/Main.cpp:    plog::init(plog::debug, "NotSharedLib2.txt"); // Initialize the logger. It will be visible only in this module and not in other modules because PLOG_LOCAL is defined.
    ./samples/NotShared/NotSharedApp/Main.cpp:    plog::init(plog::debug, "NotSharedApp.txt"); // Initialize the logger. It will be visible only in this module and not in other modules because PLOG_LOCAL is defined.
    ./samples/NotShared/NotSharedLib1/Main.cpp:    plog::init(plog::debug, "NotSharedLib1.txt"); // Initialize the logger. It will be visible only in this module and not in other modules because PLOG_LOCAL is defined.
    epsilon:plog blyth$ 



How did that happen ? Look into the download caches 
------------------------------------------------------

* seems all the cache have the ancient plog 
* DONE : updated the caches to have the desired plog and updated opticks-git-clone 

N::

    N[blyth@localhost opticks_download_cache]$ l
    total 9052
       0 drwxr-xr-x. 7 root  root       89 Nov 11 19:14 ..
       0 drwxr-xr-x. 6 blyth blyth     154 Nov  6 08:58 .
       0 drwxr-xr-x. 7 blyth blyth     138 Jul  6  2021 plog.git
       0 drwxr-xr-x. 7 blyth blyth     138 Jul  6  2021 imgui.git
       0 drwxr-xr-x. 7 blyth blyth     138 Jul  6  2021 gleq.git
       0 drwxr-xr-x. 7 blyth blyth     138 Jul  6  2021 bcm.git
     908 -rw-r--r--. 1 blyth blyth  926233 Jul  6  2021 json.hpp
     916 -rw-r--r--. 1 blyth blyth  935453 Jul  6  2021 glew-1.13.0.zip
    1404 -rw-r--r--. 1 blyth blyth 1434297 Jul  6  2021 glfw-3.3.2.zip
    5824 -rw-r--r--. 1 blyth blyth 5963606 Jul  6  2021 glm-0.9.9.5.zip
    N[blyth@localhost opticks_download_cache]$ 
    N[blyth@localhost opticks_download_cache]$ 
       

    N[blyth@localhost tt]$ git clone /data/opticks_download_cache/plog.git 
    Cloning into 'plog'...
    done.
    N[blyth@localhost tt]$ cd plog 
    N[blyth@localhost plog]$ git log -n2
    commit 04c2389fac6def5471d2c8ff87d16a67c9e4045d (HEAD -> master, origin/master, origin/HEAD)
    Author: Simon C Blyth <simon.c.blyth@gmail.com>
    Date:   Wed Apr 4 18:34:32 2018 +0800

        invert IF_LOG_ logic to avoid dangling else problem from "if(smth) LOG << bla "

    commit dcbcca75faccfbde3ba4aae85a185d042af5a185
    Author: Sergey Podobry <sergey.podobry@gmail.com>
    Date:   Mon Mar 26 10:52:42 2018 +0300

        Bump version to 1.1.4.
    N[blyth@localhost plog]$ 




laptop::

    epsilon:plog blyth$ git remote -v
    origin	/data/opticks_download_cache/plog.git (fetch)
    origin	/data/opticks_download_cache/plog.git (push)
    epsilon:plog blyth$ git log -n2
    commit 04c2389fac6def5471d2c8ff87d16a67c9e4045d (HEAD -> master, origin/master, origin/HEAD)
    Author: Simon C Blyth <simon.c.blyth@gmail.com>
    Date:   Wed Apr 4 18:34:32 2018 +0800

        invert IF_LOG_ logic to avoid dangling else problem from "if(smth) LOG << bla "

    commit dcbcca75faccfbde3ba4aae85a185d042af5a185
    Author: Sergey Podobry <sergey.podobry@gmail.com>
    Date:   Mon Mar 26 10:52:42 2018 +0300

        Bump version to 1.1.4.
    epsilon:plog blyth$ 


L7::

    L7[blyth@lxslc712 opticks_download_cache]$ mkdir -p /tmp/blyth/tt
    L7[blyth@lxslc712 opticks_download_cache]$ cd /tmp/blyth/tt
    L7[blyth@lxslc712 tt]$ git clone /hpcfs/juno/junogpu/blyth/local/opticks_download_cache/plog.git
    Cloning into 'plog'...
    done.
    L7[blyth@lxslc712 tt]$ 


AHHA : tis using very old pinned version with my modification::

    L7[blyth@lxslc712 plog]$ git log -n2
    commit 04c2389fac6def5471d2c8ff87d16a67c9e4045d
    Author: Simon C Blyth <simon.c.blyth@gmail.com>
    Date:   Wed Apr 4 18:34:32 2018 +0800

        invert IF_LOG_ logic to avoid dangling else problem from "if(smth) LOG << bla "

    commit dcbcca75faccfbde3ba4aae85a185d042af5a185
    Author: Sergey Podobry <sergey.podobry@gmail.com>
    Date:   Mon Mar 26 10:52:42 2018 +0300

        Bump version to 1.1.4.
    L7[blyth@lxslc712 plog]$ 


Updating the plog version in the release : fixes the issue
-------------------------------------------------------------

Did this by first updating all the download caches and then recreating the release at the same path.
Check that have the updated plog with::

    grep PLOG_LOCAL /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/externals/plog/include/plog/Util.h


plog/include/plog/Util.h::

     27 #else
     28 #   if defined(PLOG_GLOBAL)
     29 #       define PLOG_LINKAGE __attribute__ ((visibility ("default")))
     30 #   elif defined(PLOG_LOCAL)
     31 #       define PLOG_LINKAGE __attribute__ ((visibility ("hidden")))
     32 #       define PLOG_LINKAGE_HIDDEN PLOG_LINKAGE
     33 #   endif
     34 #   if defined(PLOG_EXPORT) || defined(PLOG_IMPORT)
     35 #       error "PLOG_EXPORT/PLOG_IMPORT is supported only on Windows"
     36 #   endif
     37 #endif
     38 






