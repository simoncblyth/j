
update
=========


Up the branch
-------------

::

    (ok) A[blyth@localhost junosw]$ git status
    On branch yupd-water-distributor
    Your branch is behind 'origin/yupd-water-distributor' by 7 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)

    nothing to commit, working tree clean
    (ok) A[blyth@localhost junosw]$ git pull
    Updating 12b13323..d933eb64
    Fast-forward
     Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                                                                |   5 +-
     Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh                                                   |  15 +-
     Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributer.hh => UpperWaterdistributor.hh}                   |  24 ++-
     Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributerPlacement.hh => UpperWaterdistributorPlacement.hh} |   6 +-
     Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh                                         |  38 -----
     Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh                                         |  58 +++++++
     Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh                                             |  54 ++++++
     Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc                                                       | 340 +++++++++++++++++++++++--------------
     Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc                                                         |   5 +
     Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributer.cc => UpperWaterdistributor.cc}                       |  48 +++---
     Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributerPlacement.cc => UpperWaterdistributorPlacement.cc}     |  14 +-
     Simulation/DetSimV2/CentralDetector/src/{WaterdistributerlooppipeMaker.cc => WaterdistributorlooppipeMaker.cc}       |  17 +-
     Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc                                                 | 269 ++++++++++++++++++++++++++++++
     Simulation/DetSimV2/Chimney/include/UpperChimneyMaker.hh                                                             |   1 +
     Simulation/DetSimV2/Chimney/src/UpperChimney.cc                                                                      |   8 +-
     Simulation/DetSimV2/Chimney/src/UpperChimneyPlacement.cc                                                             |  16 +-
     Simulation/DetSimV2/DetSimOptions/include/GlobalGeomInfo.hh                                                          |   1 +
     Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh                                               |   8 +-
     Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh                                                   |  10 +-
     Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py                                                |  14 +-
     Simulation/DetSimV2/DetSimOptions/src/GlobalGeomInfo.cc                                                              |   8 +-
     Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc                                                   |  28 ++--
     Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc                                                       | 775 ++++++++++++++++++++++---------------------------------------------------------------
     Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstructionLatticeShell.icc                                          |   2 +-
     Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc                                                         |  13 ++
     25 files changed, 934 insertions(+), 843 deletions(-)
     rename Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributer.hh => UpperWaterdistributor.hh} (55%)
     rename Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributerPlacement.hh => UpperWaterdistributorPlacement.hh} (75%)
     delete mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh
     create mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
     create mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
     rename Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributer.cc => UpperWaterdistributor.cc} (75%)
     rename Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributerPlacement.cc => UpperWaterdistributorPlacement.cc} (78%)
     rename Simulation/DetSimV2/CentralDetector/src/{WaterdistributerlooppipeMaker.cc => WaterdistributorlooppipeMaker.cc} (85%)
     create mode 100644 Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
    (ok) A[blyth@localhost junosw]$ 


first ljbb test: without any changes : completes OK : but took ~1hr
--------------------------------------------------------------------

::

    Terminating @ localhost.localdomain on Fri Sep 26 14:42:37 2025


second ljbb test: with default WaterPoolConstruction__CONFIG
---------------------------------------------------------------

::

    15:24

::

    A[blyth@localhost junosw]$ find . -name opticks_juno.sh
    ./Examples/Tutorial/share/opticks_juno.sh
    ./InstallArea/bin/opticks_juno.sh

    A[blyth@localhost junosw]$ vi Examples/Tutorial/share/opticks_juno.sh

    A[blyth@localhost junosw]$ git diff Examples/Tutorial/share/opticks_juno.sh
    diff --git a/Examples/Tutorial/share/opticks_juno.sh b/Examples/Tutorial/share/opticks_juno.sh
    index b6616a29..52cc1a80 100644
    --- a/Examples/Tutorial/share/opticks_juno.sh
    +++ b/Examples/Tutorial/share/opticks_juno.sh
    @@ -40,7 +40,9 @@ oj_geomsetup()
        for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done


    -   export WaterPoolConstruction__CONFIG=3                              # HIERARCHY
    +   #export WaterPoolConstruction__CONFIG=3                              # HIERARCHY
    +   unset WaterPoolConstruction__CONFIG
    +
        export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10                  # default 1.e-3
        export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10        # default 0.05
        export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10             # default 0.05




::

    cd ~/junosw  # js
    ./oj_initialize.sh



    2025-09-26 15:28:38.907 INFO  [793211] [U4Tree::init@289] -initMaterials_NoRINDEX
    2025-09-26 15:28:38.907 INFO  [793211] [U4Tree::init@292] -initScint
    2025-09-26 15:28:38.907 INFO  [793211] [U4Tree::init@295] -initSurfaces
    2025-09-26 15:28:38.910 INFO  [793211] [U4Tree::init@298] -initSolids
    [U4Tree::initSolids
    sn::increase_zmax_ lvid 23 _zmax -21650.00 dz    1.00 new_zmax -21649.00
    sn::setBB BAD BOUNDING BOX 
     x0 -0 x1 0
     y0 -0 y1 0
     z0 -21652 z1 -21650
    python: /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2718: void sn::setBB(double, double, double, double, double, double): Assertion `!bad_bbox' failed.
     *** Break *** abort


    The lines below might hint at the cause of the crash. If you see question
    marks as part of the stack trace, try to recompile with debugging information
    enabled and export CLING_DEBUG=1 environment variable before running.
    You may get help by asking at the ROOT forum https://root.cern/forum
    preferably using the command (.forum bug) in the ROOT prompt.
    Only if you are really convinced it is a bug in ROOT then please submit a
    report at https://root.cern/bugs or (preferably) using the command (.gh bug) in
    the ROOT prompt. Please post the ENTIRE stack trace
    from above as an attachment in addition to anything else
    that might help us fixing this issue.
    ===========================================================
    #6  0x00007fede588bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #7  0x00007fede583eb46 in raise () from /lib64/libc.so.6
    #8  0x00007fede5828833 in abort () from /lib64/libc.so.6
    #9  0x00007fede582875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007fede5837886 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007fedaf296376 in sn::setBB (this=0xd4ae420, x0=-0, y0=-0, z0=-21652, x1=0, y1=0, z1=-21650) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2718
    #12 0x00007fedaf296d1a in sn::Cylinder (radius=0, z1=-21652, z2=-21650) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2846
    #13 0x00007fedaf25d1e2 in U4Polycone::collectPrims (this=0x7ffc3f31fd60, prims=std::vector of length 0, capacity 0, outside=false) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:455















    #14 0x00007fedaf2b30fa in U4Polycone::init_inner (this=0x7ffc3f31fd60) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:401
    #15 0x00007fedaf2b2a24 in U4Polycone::init (this=0x7ffc3f31fd60) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:270
    #16 0x00007fedaf2b278f in U4Polycone::U4Polycone (this=0x7ffc3f31fd60, polycone_=0xb6fbf40, lvid_=23, depth_=3, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:236
    #17 0x00007fedaf2b1cd8 in U4Polycone::Convert (polycone=0xb6fbf40, lvid=23, depth=3, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:151
    #18 0x00007fedaf2b5f8b in U4Solid::init_Polycone (this=0x7ffc3f320080) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:879
    #19 0x00007fedaf2b41e2 in U4Solid::init_Constituents (this=0x7ffc3f320080) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:406
    #20 0x00007fedaf2b408e in U4Solid::init (this=0x7ffc3f320080) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #21 0x00007fedaf2b3f60 in U4Solid::U4Solid (this=0x7ffc3f320080, solid_=0xb6fbf40, lvid_=23, depth_=3, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #22 0x00007fedaf2b3e6c in U4Solid::Convert (solid=0xb6fbf40, lvid=23, depth=3, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #23 0x00007fedaf2b6683 in U4Solid::init_BooleanSolid (this=0x7ffc3f3202d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:1047
    #24 0x00007fedaf2b63b2 in U4Solid::init_SubtractionSolid (this=0x7ffc3f3202d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:946
    #25 0x00007fedaf2b4244 in U4Solid::init_Constituents (this=0x7ffc3f3202d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:413
    #26 0x00007fedaf2b408e in U4Solid::init (this=0x7ffc3f3202d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #27 0x00007fedaf2b3f60 in U4Solid::U4Solid (this=0x7ffc3f3202d0, solid_=0xb6fdac0, lvid_=23, depth_=2, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #28 0x00007fedaf2b3e6c in U4Solid::Convert (solid=0xb6fdac0, lvid=23, depth=2, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #29 0x00007fedaf2b6683 in U4Solid::init_BooleanSolid (this=0x7ffc3f320520) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:1047
    #30 0x00007fedaf2b63b2 in U4Solid::init_SubtractionSolid (this=0x7ffc3f320520) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:946
    #31 0x00007fedaf2b4244 in U4Solid::init_Constituents (this=0x7ffc3f320520) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:413
    #32 0x00007fedaf2b408e in U4Solid::init (this=0x7ffc3f320520) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #33 0x00007fedaf2b3f60 in U4Solid::U4Solid (this=0x7ffc3f320520, solid_=0xb6fdb70, lvid_=23, depth_=1, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #34 0x00007fedaf2b3e6c in U4Solid::Convert (solid=0xb6fdb70, lvid=23, depth=1, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #35 0x00007fedaf2b6683 in U4Solid::init_BooleanSolid (this=0x7ffc3f320770) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:1047
    #36 0x00007fedaf2b63b2 in U4Solid::init_SubtractionSolid (this=0x7ffc3f320770) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:946
    #37 0x00007fedaf2b4244 in U4Solid::init_Constituents (this=0x7ffc3f320770) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:413
    #38 0x00007fedaf2b408e in U4Solid::init (this=0x7ffc3f320770) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #39 0x00007fedaf2b3f60 in U4Solid::U4Solid (this=0x7ffc3f320770, solid_=0xb6fdd00, lvid_=23, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #40 0x00007fedaf2b3e6c in U4Solid::Convert (solid=0xb6fdd00, lvid=23, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #41 0x00007fedaf2ba486 in U4Tree::initSolid (this=0xd2440e0, so=0xb6fdd00, lvid=23) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:713
    #42 0x00007fedaf2ba3de in U4Tree::initSolid (this=0xd2440e0, lv=0xb6fde90) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:681
    #43 0x00007fedaf2ba374 in U4Tree::initSolids_r (this=0xd2440e0, pv=0xb6fc3b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:674
    #44 0x00007fedaf2ba30f in U4Tree::initSolids_r (this=0xd2440e0, pv=0xb79a530) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #45 0x00007fedaf2ba30f in U4Tree::initSolids_r (this=0xd2440e0, pv=0xb18d7d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #46 0x00007fedaf2ba30f in U4Tree::initSolids_r (this=0xd2440e0, pv=0xb18d830) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #47 0x00007fedaf2ba30f in U4Tree::initSolids_r (this=0xd2440e0, pv=0xb17b180) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #48 0x00007fedaf2ba07f in U4Tree::initSolids (this=0xd2440e0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:614
    #49 0x00007fedaf2b8864 in U4Tree::init (this=0xd2440e0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:299
    #50 0x00007fedaf2b829b in U4Tree::U4Tree (this=0xd2440e0, st_=0x75addd0, top_=0xb17b180, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:270
    #51 0x00007fedaf2b77c4 in U4Tree::Create (st=0x75addd0, top=0xb17b180, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:226
    #52 0x00007fedaf25f05e in G4CXOpticks::setGeometry (this=0xd23fa90, world=0xb17b180) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #53 0x00007fedaf25d989 in G4CXOpticks::SetGeometry (world=0xb17b180) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #54 0x00007fedaf25dc38 in G4CXOpticks::SetGeometry_JUNO (world=0xb17b180, sd=0xadccfa0, jpmt=0xd0eb870, jlut=0xd11de40) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #55 0x00007fedac198676 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xb17b180, sd=0xadccfa0, ppd=0x716df30, psd=0x71da810, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #56 0x00007fedac15d48c in LSExpDetectorConstruction::setupOpticks (this=0xada3080, world=0xb17b180) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #57 0x00007fedac15cd2c in LSExpDetectorConstruction::Construct (this=0xada3080) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #58 0x00007fedb8a0792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #59 0x00007fedb8a07afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so


Some deep polycone with zero radius causing bad BB::

    429 void U4Polycone::collectPrims(std::vector<sn*>& prims,  bool outside  )
    430 {
    431     // loop over pairs of planes
    432     for( unsigned i=1 ; i < rz.size() ; i++ )
    433     {
    434         const RZ& rz1 = rz[i-1] ;   // zplane struct rmin, rmax, z
    435         const RZ& rz2 = rz[i] ;
    436         double r1 = outside ? rz1.rmax : rz1.rmin ;
    437         double r2 = outside ? rz2.rmax : rz2.rmin ;
    438         double z1 = rz1.z ;
    439         double z2 = rz2.z ;
    440 
    441         if( z1 == z2 )
    442         {
    443             if(level > 0) std::cerr << "U4Polycone::collectPrims skipping prim as z2 == z1  " << std::endl ;
    444             continue ;
    445         }
    446 
    447 
    448         bool z_ascending = z2 > z1 ;
    449         assert(z_ascending);
    450         if(!z_ascending) std::raise(SIGINT);
    451 
    452         bool is_cylinder = r1 == r2 ;
    453         int idx = -1 ;
    454 
    455         sn* pr = is_cylinder ? sn::Cylinder(r2, z1, z2 ) : sn::Cone( r1, z1, r2, z2 ) ;
    456         pr->lvid = lvid ;  // so this before setting root for debug purposes
    457         prims.push_back(pr);
    458         idx = pr->index() ;
    459 
    460         if( level > 0 ) std::cerr
    461              << "U4Polycone::collectPrims"
    462              << " outside " << ( outside ? "YES" : "NO " )
    463              << " idx " << idx
    464              << " is_cylinder " << ( is_cylinder ? "YES" : "NO " )
    465              << std::endl
    466              ;
    467     }
    468 }




::

    2025-09-26 15:50:40.502 INFO  [802119] [U4Tree::init@289] -initMaterials_NoRINDEX
    2025-09-26 15:50:40.502 INFO  [802119] [U4Tree::init@292] -initScint
    2025-09-26 15:50:40.502 INFO  [802119] [U4Tree::init@295] -initSurfaces
    2025-09-26 15:50:40.505 INFO  [802119] [U4Tree::init@298] -initSolids
    [U4Tree::initSolids
    sn::increase_zmax_ lvid 23 _zmax -21650.00 dz    1.00 new_zmax -21649.00
    U4Polycone::collectPrims ERROR - CYLINDER PAIR UNEXPECTED ZERO r2  lvid 23 r2_nonzero NO  num_rz 4 i 1
    U4Polycone::desc lvid 23 depth 3 level -1 enable_nudge YES num 4 rz 4
     num_R_inner   2 R_inner_min          0 R_inner_max      21650
     num_R_outer   1 R_outer_min      21652 R_outer_max      21652
     num_Z         3 Z_min           -21652 Z_max            22000
     has_inner YES root  -1 label NOT-WITH-SND
      0 RZ      0.000  21652.000 -21652.000
      1 RZ      0.000  21652.000 -21650.000
      2 RZ  21650.000  21652.000 -21650.000
      3 RZ  21650.000  21652.000  22000.000

    python: /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:471: void U4Polycone::collectPrims(std::vector<sn*>&, bool): Assertion `r2_nonzero' failed.
     *** Break *** abort

::


             2
            +-+                                                                   +-+  22000
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            | |                                                                   | |
            + +-------------------------------+-----------------------------------+ +  -21650
            +---------------------------------+-------------------------------------+  -21652


Reproduced the error with "Mug" in U4Polycone_test.sh::

    (ok) A[blyth@localhost tests]$ ./U4Polycone_test.sh dbg
    gdb -ex r --args /data1/blyth/tmp/U4Polycone_test/U4Polycone_test
    Fri Sep 26 04:53:12 PM CST 2025
    GNU gdb (AlmaLinux) 14.2-4.1.el9_6
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
    Reading symbols from /data1/blyth/tmp/U4Polycone_test/U4Polycone_test...
    Starting program: /data1/blyth/tmp/U4Polycone_test/U4Polycone_test 
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    [ sn::sn sn::id pid -1 idx -1
    ] sn::sn sn::id pid -1 idx -1
    s_pa::s_pa pid -1
    s_bb::s_bb pid -1
    U4Polycone::collectPrims outside YES idx -1 is_cylinder YES
    U4Polycone::collectPrims skipping prim as z2 == z1  
    [ sn::sn sn::id pid -1 idx -1
    ] sn::sn sn::id pid -1 idx -1
    s_pa::s_pa pid -1
    s_bb::s_bb pid -1
    U4Polycone::collectPrims outside YES idx -1 is_cylinder YES
    U4Polycone::init_outer. num_outer_prim 2
    sn::increase_zmax_ lvid 0 _zmax -21650.00 dz    1.00 new_zmax -21649.00

    sn::ZNudgeOverlapJoints  lvid 0 num_prim 2 enable YES level 2
    sn::ZDesc prims(-1 -1 ) 
     idx  -1 tag  cy zmin     -21652 zmax     -21650 rperp_at_zmin      21652 rperp_at_zmax      21652
     idx  -1 tag  cy zmin     -21650 zmax      22000 rperp_at_zmin      21652 rperp_at_zmax      21652

    sn::ZNudgeOverlapJoint (0,1)  lower_zmax -21650 upper_zmin -21650 z_coincident_joint YES enable YES upper_rperp_at_zmin 21652 lower_rperp_at_zmax 21652
    sn::ZNudgeOverlapJoints lvid 0 !(lower_rperp_at_zmax > upper_rperp_at_zmin) : lower->increase_zmax( dz )   : expand lower up into bigger upper 
    [ sn::sn sn::id pid -1 idx -1
    ] sn::sn sn::id pid -1 idx -1
    U4Polycone::init_inner 
    U4Polycone::collectPrims ERROR - CYLINDER PAIR UNEXPECTED ZERO r2  lvid 0 r2_nonzero NO  num_rz 4 i 1
    U4Polycone::desc lvid 0 depth 0 level 1 enable_nudge YES num 4 rz 4
     num_R_inner   2 R_inner_min          0 R_inner_max      21650
     num_R_outer   1 R_outer_min      21652 R_outer_max      21652
     num_Z         3 Z_min           -21652 Z_max            22000
     has_inner YES root  -1 label NOT-WITH-SND
      0 RRZ      0.000  21652.000 -21652.000
      1 RRZ      0.000  21652.000 -21650.000
      2 RRZ  21650.000  21652.000 -21650.000
      3 RRZ  21650.000  21652.000  22000.000

    U4Polycone_test: /home/blyth/opticks/u4/tests/../U4Polycone.h:471: void U4Polycone::collectPrims(std::vector<sn*>&, bool): Assertion `r2_nonzero' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-168.el9_6.23.x86_64
    (gdb) 





cxr_min.sh
------------

::

    [Detaching after vfork from child process 831596]
    2025-09-26 18:39:44.203 FATAL [831591] [CSGNode::setAABBLocal@496]  not implemented for tc 124 CSG::Name(tc) cutcylinder
    CSGOptiXRenderInteractiveTest: /home/blyth/opticks/CSG/CSGNode.cc:497: void CSGNode::setAABBLocal(): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff4a8bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-168.el9_6.23.x86_64 libX11-1.7.0-11.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64
    (gdb) bt
    #0  0x00007ffff4a8bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff4a3eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff4a28833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff4a2875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff4a37886 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007ffff76324e9 in CSGNode::setAABBLocal (this=0x1527c3a0) at /home/blyth/opticks/CSG/CSGNode.cc:497
    #6  0x00007ffff76f124b in CSGCopy::copyNode (this=0x7fffffff9920, prim_bb=..., nodeIdx=254) at /home/blyth/opticks/CSG/CSGCopy.cc:370
    #7  0x00007ffff76f0e18 in CSGCopy::copyPrimNodes (this=0x7fffffff9920, prim_bb=..., spr=0x1369ab60) at /home/blyth/opticks/CSG/CSGCopy.cc:299
    #8  0x00007ffff76f0a9b in CSGCopy::copySolidPrim (this=0x7fffffff9920, solid_bb=..., dPrimOffset=0, sso=0x1344d750) at /home/blyth/opticks/CSG/CSGCopy.cc:254
    #9  0x00007ffff76f0603 in CSGCopy::copy (this=0x7fffffff9920) at /home/blyth/opticks/CSG/CSGCopy.cc:181
    #10 0x00007ffff76efa53 in CSGCopy::Select (src=0x134477f0, elv=0x146a3070) at /home/blyth/opticks/CSG/CSGCopy.cc:54
    #11 0x00007ffff764fef5 in CSGFoundry::CopySelect (src=0x134477f0, elv=0x146a3070) at /home/blyth/opticks/CSG/CSGFoundry.cc:3086
    #12 0x00007ffff764f7ac in CSGFoundry::Load () at /home/blyth/opticks/CSG/CSGFoundry.cc:3035
    #13 0x000000000049285b in CSGOptiXRenderInteractiveTest::CSGOptiXRenderInteractiveTest (this=0x7fffffffaed0) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:106
    #14 0x0000000000445e64 in main (argc=1, argv=0x7fffffffb078) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:206
    (gdb) 

::

    (gdb) f 5
    #5  0x00007ffff76324e9 in CSGNode::setAABBLocal (this=0x1527c3a0) at /home/blyth/opticks/CSG/CSGNode.cc:497
    497	        assert(0);
    (gdb) list
    492	        setAABB( UNBOUNDED_DEFAULT_EXTENT );
    493	    }
    494	    else
    495	    {
    496	        LOG(fatal) << " not implemented for tc " << tc << " CSG::Name(tc) " << CSG::Name(tc) ;
    497	        assert(0);
    498	        setAABB( 0.f );
    499	    }
    500	}
    501	
    (gdb) 


::

    A[blyth@localhost junosw]$ find . -name 'opticks_juno.sh'
    ./Examples/Tutorial/share/opticks_juno.sh
    ./InstallArea/bin/opticks_juno.sh
    A[blyth@localhost junosw]$ cp Examples/Tutorial/share/opticks_juno.sh InstallArea/bin/opticks_juno.sh
    A[blyth@localhost junosw]$ ./oj_initialize.sh 



Some frame names outdated::

    [mask_PMT_20inch_vetosMask_virtual]
    [sOuterWaterPool]
    [sPoolLining]
    [sBottomRock]
    [sWorld]
    ]stree::desc_soname
    stree::has_frame FATAL parse_spec failed  q_spec [sChimneyAcrylic:0:-1] parse_rc -1
    SScene::addFrames FAIL to find frame  spec [sChimneyAcrylic:0:-1]
     line [sChimneyAcrylic:0:-1                       #  6]
    [CSGImport::importPrim.dump_LVID:1 node.lvid 38 idx_rc 0 LVID -1 name Waterdistributor_1 soname Waterdistributor_1 primIdx 221 bn 1(binary nodes) ln(subset of bn) 1 ln_expect YES num_sub_total 11
    [rt.render




