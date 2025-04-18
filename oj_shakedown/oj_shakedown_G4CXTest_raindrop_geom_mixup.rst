FIXED : oj_shakedown_G4CXTest_raindrop_geom_mixup
=====================================================


Changes to avoid in future:

* dont assert all spec frames are found in stree.h 
* do some unset in G4CXTest_raindrop.sh when mixed GEOM detected



Some frame lookup failed::

    A[blyth@localhost ~]$ oj info_env_test8

    ...

    ]stree::desc_soname
    stree::has_frame FATAL parse_spec failed  q_spec [Hama:0:0] parse_rc -1
    G4CXTest: /home/blyth/opticks/sysrap/stree.h:1895: bool stree::has_frame(const char*) const: Assertion `parse_rc == 0' failed.
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6/bin/G4CXTest_raindrop.sh: line 183: 702818 Aborted                 (core dumped) $bin
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6/bin/G4CXTest_raindrop.sh : run error
    /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_3_6/oj_sh
    -bash OJ_LOGDIR /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_3_6/oj_sh
    total 120
    116 -rw-r--r--. 1 blyth blyth 118506 Apr 17 15:45 sample_detsim_user.root




Problem is the OJ environment assumes the OJ geometry but here are 
trying to use a simple geometry. So end up with mixed config. 

::

    A[blyth@localhost ~]$ G4CXTest_raindrop.sh dbg
    gdb -ex r --args G4CXTest
    Thu Apr 17 04:02:04 PM CST 2025
    GNU gdb (AlmaLinux) 14.2-3.el9
    Copyright (C) 2023 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.
    Type "show copying" and "show warranty" for details.
    This GDB was configured as "x86_64-redhat-linux-gnu".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <https://www.gnu.org/software/gdb/bugs/>.
    Find the GDB manual and other documentation resources online at:
        <http://www.gnu.org/software/gdb/documentation/>.

    For help, type "help".
    Type "apropos word" to search for commands related to "word"...
    Reading symbols from G4CXTest...
    Starting program: /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.3.6/lib/G4CXTest 
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    2025-04-17 16:02:06.663 INFO  [702930] [G4CXApp::Create@338] U4Recorder::Switches
    WITH_CUSTOM4
    NOT:WITH_PMTSIM
    NOT:PMTSIM_STANDALONE
    NOT:PRODUCTION
    NOT:WITH_INSTRUMENTED_DEBUG


    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)
                           Copyright : Geant4 Collaboration
                          References : NIM A 506 (2003), 250-303
                                     : IEEE-TNS 53 (2006), 270-278
                                     : NIM A 835 (2016), 186-225
                                 WWW : http://geant4.org/
    **************************************************************

    [New Thread 0x7fffebbff000 (LWP 702943)]
    2025-04-17 16:02:06.792 INFO  [702930] [SEventConfig::SetDevice@1333] SEventConfig::DescDevice
    name                             : NVIDIA RTX 5000 Ada Generation
    totalGlobalMem_bytes             : 33796980736
    totalGlobalMem_GB                : 31
    HeuristicMaxSlot(VRAM)           : 262530128
    HeuristicMaxSlot(VRAM)/M         : 262
    HeuristicMaxSlot_Rounded(VRAM)   : 262000000
    MaxSlot/M                        : 1

    2025-04-17 16:02:06.792 INFO  [702930] [SEventConfig::SetDevice@1345]  Configured_MaxSlot/M 1 Final_MaxSlot/M 1 HeuristicMaxSlot_Rounded/M 262 changed NO  DeviceName NVIDIA RTX 5000 Ada Generation HasDevice YES
    (export OPTICKS_MAX_SLOT=0 # to use VRAM based HeuristicMaxPhoton) 
    [Detaching after vfork from child process 702947]
    G4CXApp::InitSensDet sdn PMTSDMgr sd YES
    U4SensitiveDetector::Desc INSTANCES YES num_instance 1
      0 : PMTSDMgr

    2025-04-17 16:02:07.349 INFO  [702930] [G4CXApp::Construct@165] [
    U4VolumeMaker::PV name RaindropRockAirWater
    2025-04-17 16:02:07.349 INFO  [702930] [G4CXApp::Construct@177]  fPV universe_pv
    2025-04-17 16:02:07.350 INFO  [702930] [G4CXApp::Construct@179] ]
    U::Resolve token [PMTSimParamData_BASE] does not resolve 

    2025-04-17 16:02:07.351 INFO  [702930] [U4Tree::Create@217] [new U4Tree
    2025-04-17 16:02:07.351 INFO  [702930] [U4Tree::init@274] -initRayleigh
    2025-04-17 16:02:07.351 INFO  [702930] [U4Tree::init@276] -initMaterials
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@278] -initMaterials_NoRINDEX
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@281] -initScint
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@284] -initSurfaces
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@287] -initSolids
    [U4Tree::initSolids
    ]U4Tree::initSolids
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@289] -initNodes
    2025-04-17 16:02:07.354 INFO  [702930] [U4Tree::init@291] -initSurfaces_Serialize
    2025-04-17 16:02:07.355 INFO  [702930] [U4Tree::init@294] -initStandard
    U4Tree::init U4Tree::desc
     st Y
     top Y
     sid Y
     level 0
     lvidx 4
     pvs 4
     materials 4
     surfaces 1
     solids 4
     enable_osur YES
     enable_isur YES

    2025-04-17 16:02:07.356 INFO  [702930] [U4Tree::Create@219] ]new U4Tree
    2025-04-17 16:02:07.356 INFO  [702930] [U4Tree::Create@221] [stree::factorize
    stree::FindForceTriangulateLVID name not found [solidSJCLSanchor]
    stree::FindForceTriangulateLVID name not found [solidSJFixture]
    stree::FindForceTriangulateLVID name not found [solidSJReceiver]
    stree::FindForceTriangulateLVID name not found [solidSJReceiverFastern]
    stree::FindForceTriangulateLVID name not found [solidXJanchor]
    stree::FindForceTriangulateLVID name not found [solidXJfixture]
    stree::FindForceTriangulateLVID name not found [svacSurftube_0V1_0]
    stree::FindForceTriangulateLVID name not found [svacSurftube_1V1_0]
    ...
    stree::FindForceTriangulateLVID name not found [svacSurftube_36V1_1]
    stree::FindForceTriangulateLVID name not found [sSurftube_36V1_1]
    stree::FindForceTriangulateLVID name not found [svacSurftube_37V1_1]
    stree::FindForceTriangulateLVID name not found [sSurftube_37V1_1]
    stree::FindForceTriangulateLVID name not found [svacSurftube_38V1_1]
    stree::FindForceTriangulateLVID name not found [sSurftube_38V1_1]
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@223] ]stree::factorize
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@225] [U4Tree::identifySensitive
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@227] ]U4Tree::identifySensitive
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@230] [stree::add_inst
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@232] ]stree::add_inst
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@237] [stree::postcreate
    [stree::postcreate
    stree::desc_sensor
     sensor_id.size 0
     sensor_count 0
     sensor_name.size 0
    sensor_name[
    ]
    [stree::desc_sensor_nd
     edge            0
     num_nd          4
     num_nd_sensor   0
     num_sid         0
    ]stree::desc_sensor_nd
    stree::desc_sensor_id sensor_id.size 0
    [
    ]]stree::postcreate
    2025-04-17 16:02:07.357 INFO  [702930] [U4Tree::Create@239] ]stree::postcreate
    stree::parse_spec FAILED to find lvid for q_soname [Hama]
    [stree::desc_soname
    [G4_WATER_solid]
    [G4_AIR_solid]
    [G4_Pb_solid]
    [VACUUM_solid]
    ]stree::desc_soname
    stree::has_frame FATAL parse_spec failed  q_spec [Hama:0:0] parse_rc -1
    G4CXTest: /home/blyth/opticks/sysrap/stree.h:1895: bool stree::has_frame(const char*) const: Assertion parse_rc == 0 failed.

    Thread 1 "G4CXTest" received signal SIGABRT, Aborted.
    0x00007ffff268b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff268b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff263e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff2628833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff262875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff26373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007ffff3554566 in stree::has_frame (this=0x780fd0, q_spec=0x7ffffffed110 "Hama:0:0") at /home/blyth/opticks/sysrap/stree.h:1895
    #6  0x00007ffff35603de in SScene::addFrames (this=0x7815a0, path=0x7ffff3658d30 "$SScene__initFromTree_addFrames", st=0x780fd0) at /home/blyth/opticks/sysrap/SScene.h:813
    #7  0x00007ffff355f2be in SScene::initFromTree (this=0x7815a0, st=0x780fd0) at /home/blyth/opticks/sysrap/SScene.h:209
    #8  0x00007ffff354642b in SSim::initSceneFromTree (this=0x780f70) at /home/blyth/opticks/sysrap/SSim.cc:183
    #9  0x00007ffff7e44f9c in G4CXOpticks::setGeometry (this=0x762f50, world=0x773dd0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:316
    #10 0x00007ffff7e43155 in G4CXOpticks::SetGeometry (world=0x773dd0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:58
    #11 0x0000000000409dac in G4CXApp::Construct (this=0x6cd180) at /home/blyth/opticks/g4cx/tests/G4CXApp.h:186
    #12 0x00007ffff700792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #13 0x00007ffff7007afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #14 0x0000000000409831 in G4CXApp::G4CXApp (this=0x6cd180, runMgr=0x670d30) at /home/blyth/opticks/g4cx/tests/G4CXApp.h:158
    #15 0x000000000040a889 in G4CXApp::Create () at /home/blyth/opticks/g4cx/tests/G4CXApp.h:341
    #16 0x000000000040ab11 in G4CXApp::Main () at /home/blyth/opticks/g4cx/tests/G4CXApp.h:354
    #17 0x000000000040acaf in main (argc=1, argv=0x7ffffffefcc8) at /home/blyth/opticks/g4cx/tests/G4CXTest.cc:13
    (gdb) 


    (gdb) f 7
    #7  0x00007ffff355f2be in SScene::initFromTree (this=0x7815a0, st=0x780fd0) at /home/blyth/opticks/sysrap/SScene.h:209
    209     addFrames("$SScene__initFromTree_addFrames", st );
    (gdb) f 6
    #6  0x00007ffff35603de in SScene::addFrames (this=0x7815a0, path=0x7ffff3658d30 "$SScene__initFromTree_addFrames", st=0x780fd0) at /home/blyth/opticks/sysrap/SScene.h:813
    813             bool has_frame = st->has_frame(spec);
    (gdb) 
    (gdb) f 5
    #5  0x00007ffff3554566 in stree::has_frame (this=0x780fd0, q_spec=0x7ffffffed110 "Hama:0:0") at /home/blyth/opticks/sysrap/stree.h:1895
    1895        assert( parse_rc == 0 ); 



    A[blyth@localhost ~]$ echo $SScene__initFromTree_addFrames
    /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Wed/.opticks/GEOM/J25_3_0_Opticks_v0_3_6/CSGFoundry/framespec.txt

    A[blyth@localhost ~]$ head -5 $SScene__initFromTree_addFrames
    Hama:0:0
    NNVT:0:0
    Hama:0:1000
    NNVT:0:1000
    sDeadWater:0:-1
    A[blyth@localhost ~]$ 




