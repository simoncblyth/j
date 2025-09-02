ljbb-yupd-water-distributor-SEGV
==================================


::

    A[blyth@localhost junosw]$ cat oj_translate_debug.sh 
    #!/bin/bash

    cd $(dirname $(realpath $BASH_SOURCE))
    source InstallArea/envset.sh

    export U4Tree__SOLID_DEBUG=1
    export U4Solid__IsFlaggedName=WaterDistributer


    source dbg__.sh

    dbg__ $(which python) $(which tut_detsim.py) --opticks-mode 1 --evtmax 0 gun















::

    Begin Upper UpperChimney Construction
    junotoptask:DetSimAlg.UpperChimney.makeUpperChimneyLogicalandPhysical  INFO: UpperChimney: solidUpperChimney: 0xc287610
    Top Chimney Position: -3100 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Injecting Upper Water Distributer...

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    (gdb) bt
    #0  0x00007fffe9870759 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #1  0x00007fffbdd3a854 in ExpHallConstruction::inject (this=0xa550910, motherName="lExpHall", other=0x6672b40, pos=0x6889850) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc:84
    #2  0x00007fffbdd651b0 in LSExpDetectorConstruction::setupUpperWaterDistributer (this=0xa2bc280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1977
    #3  0x00007fffbdd59757 in LSExpDetectorConstruction::Construct (this=0xa2bc280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:321
    #4  0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #5  0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #6  0x00007fffd485eb1b in DetSimAlg::initialize (this=0x66d6c60) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #7  0x00007fffd0adeb56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffd0af409b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    ...
    (gdb) 




	
    (gdb) p de_waterdistributer
    $2 = (IDetElement *) 0x6672b40
    (gdb) p pos_waterdistributer
    $3 = (IDetElementPos *) 0x6889850
    (gdb) f 1
    #1  0x00007fffbdd3a854 in ExpHallConstruction::inject (this=0xa550910, motherName="lExpHall", other=0x6672b40, pos=0x6889850) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc:84
    84	            daughtervol->GetName()+"_phys",
    (gdb) list 
    79	    
    80	       while (pos->hasNext()) {
    81	        new G4PVPlacement(
    82	            pos->next(),
    83	            daughtervol,
    84	            daughtervol->GetName()+"_phys",
    85	            mothervol,
    86	            false,
    87	            copyno++
    88	    //        true
    (gdb) p pos
    $4 = (IDetElementPos *) 0x6889850
    (gdb) p mothervol
    $5 = (G4LogicalVolume *) 0xa550ea0
    (gdb) f 0
    #0  0x00007fffe9870759 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, char const*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    (gdb) p daughtervol
    No symbol "daughtervol" in current context.
    (gdb) p daughtervol
    No symbol "daughtervol" in current context.
    (gdb) f 1
    #1  0x00007fffbdd3a854 in ExpHallConstruction::inject (this=0xa550910, motherName="lExpHall", other=0x6672b40, pos=0x6889850) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc:84
    84	            daughtervol->GetName()+"_phys",
    (gdb) p daughtervol
    $6 = (G4LogicalVolume *) 0x1d000002ec
    (gdb) p daughtervol->GetName()
    Couldn't find method G4LogicalVolume::GetName
    (gdb) 



::

  	G4PVPlacement (G4RotationMatrix *pRot, const G4ThreeVector &tlate, G4LogicalVolume *pCurrentLogical, const G4String &pName, G4LogicalVolume *pMotherLogical, G4bool pMany, G4int pCopyNo, G4bool pSurfChk=false)
 	G4PVPlacement (const G4Transform3D &Transform3D, G4LogicalVolume *pCurrentLogical, const G4String &pName, G4LogicalVolume *pMotherLogical, G4bool pMany, G4int pCopyNo, G4bool pSurfChk=false)
 	G4PVPlacement (G4RotationMatrix *pRot, const G4ThreeVector &tlate, const G4String &pName, G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother, G4bool pMany, G4int pCopyNo, G4bool pSurfChk=false)
 	G4PVPlacement (const G4Transform3D &Transform3D, const G4String &pName, G4LogicalVolume *pLogical, G4VPhysicalVolume *pMother, G4bool pMany, G4int pCopyNo, G4bool pSurfChk=false)


Using temporary G4String where reference expected "const G4String &pName" is unhealthy, so::

+      assert( daughtervol );
+      GString daughtervol_name = daughtervol->GetName();  
+      daughtervol_name += "_phys" ; 
+
        while (pos->hasNext()) {
         new G4PVPlacement(
             pos->next(),
             daughtervol,
-            daughtervol->GetName()+"_phys",
+            daughtervol_name,
             mothervol,
             false,
             copyno++




Bad PV in U4Tree.h : HUH seems not to repeat
----------------------------------------------

::

    Thread 1 (Thread 0x7f1f7cdec5c0 (LWP 856855) "python"):
    #0  0x00007f1f7c4d85ff in wait4 () from /lib64/libc.so.6
    #1  0x00007f1f7c44b283 in do_system () from /lib64/libc.so.6
    #2  0x00007f1f6e6f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f1f7c66cf73 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f1f6e6f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f1f45f64854 in G4VPhysicalVolume::GetLogicalVolume (this=0x54) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4VPhysicalVolume.icc:49
    #7  0x00007f1f45f97b7d in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0x54) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:432
    #8  0x00007f1f45f97bc2 in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0xd672540) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:434
    #9  0x00007f1f45f97bc2 in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0xb9c7370) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:434
    #10 0x00007f1f45f97bc2 in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0xb9c65c0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:434
    #11 0x00007f1f45f97bc2 in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0xb9c6670) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:434
    #12 0x00007f1f45f97bc2 in U4Tree::initMaterials_r (this=0xd6eaa50, pv=0xb9b9bb0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:434
    #13 0x00007f1f45f97533 in U4Tree::initMaterials (this=0xd6eaa50) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:343
    #14 0x00007f1f45f96bdc in U4Tree::init (this=0xd6eaa50) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:285
    #15 0x00007f1f45f9690f in U4Tree::U4Tree (this=0xd6eaa50, st_=0xb28b8c0, top_=0xb9b9bb0, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #16 0x00007f1f45f95e56 in U4Tree::Create (st=0xb28b8c0, top=0xb9b9bb0, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #17 0x00007f1f45f3fffe in G4CXOpticks::setGeometry (this=0xda3a6a0, world=0xb9b9bb0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #18 0x00007f1f45f3e929 in G4CXOpticks::SetGeometry (world=0xb9b9bb0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #19 0x00007f1f45f3ebd8 in G4CXOpticks::SetGeometry_JUNO (world=0xb9b9bb0, sd=0x7c73270, jpmt=0xd6ac990, jlut=0xd78b370) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #20 0x00007f1f42d94ba6 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xb9b9bb0, sd=0x7c73270, ppd=0x7a709f0, psd=0x7a71d30, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #21 0x00007f1f42d5a352 in LSExpDetectorConstruction::setupOpticks (this=0xb5c8c50, world=0xb9b9bb0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #22 0x00007f1f42d59bf3 in LSExpDetectorConstruction::Construct (this=0xb5c8c50) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393



Rerun with debug reach different error : from lack of G4CutTubs handling
-------------------------------------------------------------------------

::

    dbg__ $(which python) $(which tut_detsim.py) --opticks-mode 1 --evtmax 0 gun


    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc1031f4c in U4Solid::init_Constituents (this=0x7ffffffe58f0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:410
    #6  0x00007fffc1031d56 in U4Solid::init (this=0x7ffffffe58f0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #7  0x00007fffc1031c28 in U4Solid::U4Solid (this=0x7ffffffe58f0, solid_=0xaba8c70, lvid_=99, depth_=2, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #8  0x00007fffc1031b34 in U4Solid::Convert (solid=0xaba8c70, lvid=99, depth=2, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #9  0x00007fffc1032f32 in U4Solid::init_MultiUnion (this=0x7ffffffe5bb0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:690
    #10 0x00007fffc1031ed0 in U4Solid::init_Constituents (this=0x7ffffffe5bb0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:403
    #11 0x00007fffc1031d56 in U4Solid::init (this=0x7ffffffe5bb0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #12 0x00007fffc1031c28 in U4Solid::U4Solid (this=0x7ffffffe5bb0, solid_=0xaba8920, lvid_=99, depth_=1, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #13 0x00007fffc1031b34 in U4Solid::Convert (solid=0xaba8920, lvid=99, depth=1, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #14 0x00007fffc1032f32 in U4Solid::init_MultiUnion (this=0x7ffffffe5e70) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:690
    #15 0x00007fffc1031ed0 in U4Solid::init_Constituents (this=0x7ffffffe5e70) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:403
    #16 0x00007fffc1031d56 in U4Solid::init (this=0x7ffffffe5e70) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #17 0x00007fffc1031c28 in U4Solid::U4Solid (this=0x7ffffffe5e70, solid_=0xaba3850, lvid_=99, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #18 0x00007fffc1031b34 in U4Solid::Convert (solid=0xaba3850, lvid=99, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #19 0x00007fffc10379de in U4Tree::initSolid (this=0xc618580, so=0xaba3850, lvid=99) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:703
    #20 0x00007fffc1037936 in U4Tree::initSolid (this=0xc618580, lv=0xabc0850) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #21 0x00007fffc10378cc in U4Tree::initSolids_r (this=0xc618580, pv=0xabc0930) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:664
    #22 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xaba3780) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #23 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xac0a520) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #24 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xac0a4c0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #25 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xabc2010) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #26 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xac0a7d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #27 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xab1f8e0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #28 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xab1f800) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #29 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xab1f720) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #30 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xab77df0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #31 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xa5b0eb0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #32 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xa5b0f10) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #33 0x00007fffc1037867 in U4Tree::initSolids_r (this=0xc618580, pv=0xa59eb90) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #34 0x00007fffc10376e4 in U4Tree::initSolids (this=0xc618580) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #35 0x00007fffc1035ed8 in U4Tree::init (this=0xc618580) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #36 0x00007fffc103590f in U4Tree::U4Tree (this=0xc618580, st_=0x6927ff0, top_=0xa59eb90, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #37 0x00007fffc1034e56 in U4Tree::Create (st=0x6927ff0, top=0xa59eb90, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #38 0x00007fffc0fdeffe in G4CXOpticks::setGeometry (this=0xc2d21b0, world=0xa59eb90) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #39 0x00007fffc0fdd929 in G4CXOpticks::SetGeometry (world=0xa59eb90) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #40 0x00007fffc0fddbd8 in G4CXOpticks::SetGeometry_JUNO (world=0xa59eb90, sd=0x9dd7750, jpmt=0xc2936e0, jlut=0xc2c3580) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #41 0x00007fffbdd94ba6 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xa59eb90, sd=0x9dd7750, ppd=0x65f6ed0, psd=0x6679690, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #42 0x00007fffbdd5a352 in LSExpDetectorConstruction::setupOpticks (this=0xa1a8440, world=0xa59eb90) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #43 0x00007fffbdd59bf3 in LSExpDetectorConstruction::Construct (this=0xa1a8440) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #44 0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #45 0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #46 0x00007fffd485eb1b in DetSimAlg::initialize (this=0x65f3a50) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80





another SEGV
------------------

::

    Begin Upper UpperChimney Construction
    junotoptask:DetSimAlg.UpperChimney.makeUpperChimneyLogicalandPhysical  INFO: UpperChimney: solidUpperChimney: 0xcccd8a0
    Top Chimney Position: -3100 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Injecting Upper Water Distributer...
     *** Break *** segmentation violation

    Thread 1 (Thread 0x7f3af88555c0 (LWP 1295680) "python"):
    #0  0x00007f3af7ed85ff in wait4 () from /lib64/libc.so.6
    #1  0x00007f3af7e4b283 in do_system () from /lib64/libc.so.6
    #2  0x00007f3aea0f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f3aea3e10f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f3aea0f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f3ac4cfbd24 in G4LogicalVolume::GetFieldManager() const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #7  0x00007f3ac4cfdb89 in G4LogicalVolume::AddDaughter(G4VPhysicalVolume*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #8  0x00007f3ac4e4b859 in G4PVPlacement::G4PVPlacement(HepGeom::Transform3D const&, G4LogicalVolume*, G4String const&, G4LogicalVolume*, bool, int, bool) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #9  0x00007f3abe73a8fa in ExpHallConstruction::inject (this=0xb022980, motherName="lExpHall", other=0x70e4a60, pos=0x7401f10) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc:93
    #10 0x00007f3abe765238 in LSExpDetectorConstruction::setupUpperWaterDistributer (this=0xac6afc0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1977
    #11 0x00007f3abe7597df in LSExpDetectorConstruction::Construct (this=0xac6afc0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:321
    #12 0x00007f3ac760e92e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #13 0x00007f3ac760eafc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #14 0x00007f3acfd39b1b in DetSimAlg::initialize (this=0x7093160) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #15 0x00007f3ad35d0b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007f3ad35e609b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007f3ad35ee447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007f3ad35e6048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #19 0x00007f3ace5d48d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #20 0x00007f3ad505a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #21 0x00007f3ad505a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #22 0x00007f3ad505f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #23 0x00007f3ad5058182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #24 0x00007f3af8359cc3 in _PyObject_MakeTpCall (tstate=0x7f3af8779738 <_PyRuntime+166328>, callable=0x6a6a4c0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #25 0x00007f3af82fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #26 0x00007f3af844f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f3af8860020, tstate=0x7f3af8779738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #27 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f3aea744f40, func=0x7f3af80c09a0, tstate=0x7f3af8779738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #28 PyEval_EvalCode (co=co



::

    cd ~/junosw
    source InstallArea/envset.sh
    dbg__ $(which python) $(which tut_detsim.py) --opticks-mode 1 --evtmax 0 gun



init_MultiUnion
---------------------

::

    #6  0x00007f2e3588b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #7  0x00007f2e3583e686 in raise () from /lib64/libc.so.6
    #8  0x00007f2e35828833 in abort () from /lib64/libc.so.6
    #9  0x00007f2e3582875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #10 0x00007f2e358373c6 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f2dff418fc7 in U4Solid::init_MultiUnion (this=0x7ffc49aa3e50) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:702
    #12 0x00007f2dff417e38 in U4Solid::init_Constituents (this=0x7ffc49aa3e50) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:409
    #13 0x00007f2dff417cba in U4Solid::init (this=0x7ffc49aa3e50) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #14 0x00007f2dff417b8c in U4Solid::U4Solid (this=0x7ffc49aa3e50, solid_=0xb4da480, lvid_=99, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #15 0x00007f2dff417a98 in U4Solid::Convert (solid=0xb4da480, lvid=99, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #16 0x00007f2dff41dde4 in U4Tree::initSolid (this=0xcf64630, so=0xb4da480, lvid=99) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:703
    #17 0x00007f2dff41dd3c in U4Tree::initSolid (this=0xcf64630, lv=0xb4f7480) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #18 0x00007f2dff41dcd2 in U4Tree::initSolids_r (this=0xcf64630, pv=0xb4f7560) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:664
    #19 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb4da3b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #20 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb541150) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #21 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb5410f0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #22 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb4f8c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #23 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb541400) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #24 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb456510) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #25 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb456430) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #26 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb456350) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #27 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xb4aea20) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #28 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xaee7ae0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #29 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xaee7b40) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #30 0x00007f2dff41dc6d in U4Tree::initSolids_r (this=0xcf64630, pv=0xaed5490) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #31 0x00007f2dff41daea in U4Tree::initSolids (this=0xcf64630) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #32 0x00007f2dff41c2de in U4Tree::init (this=0xcf64630) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #33 0x00007f2dff41bd15 in U4Tree::U4Tree (this=0xcf64630, st_=0xa296ef0, top_=0xaed5490, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #34 0x00007f2dff41b25c in U4Tree::Create (st=0xa296ef0, top=0xaed5490, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #35 0x00007f2dff3c400e in G4CXOpticks::setGeometry (this=0xcf57190, world=0xaed5490) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #36 0x00007f2dff3c2939 in G4CXOpticks::SetGeometry (world=0xaed5490) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #37 0x00007f2dff3c2be8 in G4CXOpticks::SetGeometry_JUNO (world=0xaed5490, sd=0x6ff7180, jpmt=0xcbca470, jlut=0xcbf9800) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #38 0x00007f2dfc194c76 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xaed5490, sd=0x6ff7180, ppd=0x6f18820, psd=0x6f7eca0, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Optick



GG


    2025-09-02 09:46:14.215 INFO  [2791336] [U4Tree::init@295] -initSolids
    [U4Tree::initSolids
    sn::increase_zmax_ lvid 51 _zmax -1400.00 dz    1.00 new_zmax -1399.00
    sn::decrease_zmin_ lvid 51 _zmin -1000.00 dz    1.00 new_zmin -1001.00
    sn::increase_zmax_ lvid 52 _zmax -1400.00 dz    1.00 new_zmax -1399.00
    sn::decrease_zmin_ lvid 52 _zmin -1000.00 dz    1.00 new_zmin -1001.00
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    sn::CutCylinder
     R  65.000000
     dz 497.056275
     _pz_nrm_x   0.382683
     _pz_nrm_y   0.000000
     _pz_nrm_z   0.923880

     pz_nrm_x   0.382683
     pz_nrm_y   0.000000
     pz_nrm_z   0.923880

     _nz_nrm_x   0.382683
     _nz_nrm_y   0.000000
     _nz_nrm_z  -0.923880

     nz_nrm_x   0.382683
     nz_nrm_y   0.000000
     nz_nrm_z  -0.923880

     pdz -26.923882
     pdz_expect NO 
     zmax 470.132393

     ndz -156.923882
     ndz_expect NO 
     zmin -340.132393
    python: /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:702: void U4Solid::init_MultiUnion(): Assertion `p && p->is_primitive()' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc1031fc7 in U4Solid::init_MultiUnion (this=0x7ffffffea690) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:702
    #6  0x00007fffc1030e38 in U4Solid::init_Constituents (this=0x7ffffffea690) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:409
    #7  0x00007fffc1030cba in U4Solid::init (this=0x7ffffffea690) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #8  0x00007fffc1030b8c in U4Solid::U4Solid (this=0x7ffffffea690, solid_=0xab93410, lvid_=99, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #9  0x00007fffc1030a98 in U4Solid::Convert (solid=0xab93410, lvid=99, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #10 0x00007fffc1036de4 in U4Tree::initSolid (this=0xc610100, so=0xab93410, lvid=99) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:703
    #11 0x00007fffc1036d3c in U4Tree::initSolid (this=0xc610100, lv=0xabb0720) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #12 0x00007fffc1036cd2 in U4Tree::initSolids_r (this=0xc610100, pv=0xabb0800) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:664
    #13 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xab93340) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #14 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa3f0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #15 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa390) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #16 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xabb1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #17 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa6a0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #18 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f4a0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #19 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f3c0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #20 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f2e0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #21 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xab679b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #22 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xa5a0a70) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #23 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xa5a0ad0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #24 0x00007fffc1036c6d in U4Tree::initSolids_r (this=0xc610100, pv=0xa58e420) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #25 0x00007fffc1036aea in U4Tree::initSolids (this=0xc610100) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #26 0x00007fffc10352de in U4Tree::init (this=0xc610100) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #27 0x00007fffc1034d15 in U4Tree::U4Tree (this=0xc610100, st_=0x9c46360, top_=0xa58e420, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #28 0x00007fffc103425c in U4Tree::Create (st=0x9c46360, top=0xa58e420, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #29 0x00007fffc0fdd00e in G4CXOpticks::setGeometry (this=0xc60aad0, world=0xa58e420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #30 0x00007fffc0fdb939 in G4CXOpticks::SetGeometry (world=0xa58e420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #31 0x00007fffc0fdbbe8 in G4CXOpticks::SetGeometry_JUNO (world=0xa58e420, sd=0x6518ca0, jpmt=0xc2832c0, jlut=0xc2b2650) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #32 0x00007fffbdd94c76 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xa58e420, sd=0x6518ca0, ppd=0x666b090, psd=0x666bee0, pmtscan=0x0)




skip assert for primitive muni constituents
-------------------------------------------------

::

     ./oj_translate_debug.sh 


     pdz -13.669048
     pdz_expect NO 
     zmax 483.387227

     ndz -79.669048
     ndz_expect NO 
     zmin -417.387227
    U4Solid::init_MultiUnion
    [U4MultiUnion::Desc
     name WaterDistributer
     sub_num 11
       0 : WaterDistributer_II
       1 : WaterDistributer_I
       2 : WaterDistributer_III
       3 : Hole_0
       4 : Hole_1
       5 : Hole_2
       6 : Hole_3
       7 : Hole_4
       8 : Hole_5
       9 : Hole_6
      10 : Hole_7
    ]U4MultiUnion::Desc
     i     2 p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000  -235.0000     0.0000     1.0000.

    sn::setAABB_LeafFrame : FATAL NOT IMPLEMENTED :  typecode 124 CSG::Name(typecode) cutcylinder
    python: /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5100: void sn::setAABB_LeafFrame(): Assertion `0' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 


    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc101a29a in sn::setAABB_LeafFrame (this=0xd4b8630) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5100
    #6  0x00007fffc101a3d0 in sn::setAABB_TreeFrame_All (this=0xd4bf8c0) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5153
    #7  0x00007fffc101a632 in sn::postconvert (this=0xd4bf8c0, lvid=99) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5194
    #8  0x00007fffc1031222 in U4Solid::init_Tree (this=0x7ffffffea690) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:441
    #9  0x00007fffc1030f16 in U4Solid::init (this=0x7ffffffea690) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:382
    #10 0x00007fffc1030ddc in U4Solid::U4Solid (this=0x7ffffffea690, solid_=0xab93410, lvid_=99, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #11 0x00007fffc1030ce8 in U4Solid::Convert (solid=0xab93410, lvid=99, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #12 0x00007fffc1037184 in U4Tree::initSolid (this=0xc610100, so=0xab93410, lvid=99) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:703
    #13 0x00007fffc10370dc in U4Tree::initSolid (this=0xc610100, lv=0xabb0720) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #14 0x00007fffc1037072 in U4Tree::initSolids_r (this=0xc610100, pv=0xabb0800) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:664
    #15 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xab93340) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #16 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa3f0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #17 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa390) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #18 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xabb1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #19 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xabfa6a0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #20 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f4a0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #21 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f3c0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #22 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xab0f2e0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #23 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xab679b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #24 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xa5a0a70) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #25 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xa5a0ad0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #26 0x00007fffc103700d in U4Tree::initSolids_r (this=0xc610100, pv=0xa58e420) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #27 0x00007fffc1036e8a in U4Tree::initSolids (this=0xc610100) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #28 0x00007fffc103567e in U4Tree::init (this=0xc610100) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #29 0x00007fffc10350b5 in U4Tree::U4Tree (this=0xc610100, st_=0x9c46360, top_=0xa58e420, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267




::

    ]stree::postcreate
    2025-09-02 10:50:13.424 INFO  [2804401] [U4Tree::Create@245] ]stree::postcreate
    [Detaching after vfork from child process 2804429]
    python: /home/blyth/opticks/CSG/CSGImport.cc:319: CSGPrim* CSGImport::importPrim(int, const snode&): Assertion `ln == 0 || ln == 1' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    (gdb) bt
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc04fdc2a in CSGImport::importPrim (this=0x1ffac9b0, primIdx=2345, node=...) at /home/blyth/opticks/CSG/CSGImport.cc:319
    #6  0x00007fffc04fd3d6 in CSGImport::importSolidGlobal (this=0x1ffac9b0, ridx=0, ridx_type=82 'R') at /home/blyth/opticks/CSG/CSGImport.cc:179
    #7  0x00007fffc04fcdb7 in CSGImport::importSolid (this=0x1ffac9b0) at /home/blyth/opticks/CSG/CSGImport.cc:90
    #8  0x00007fffc04fcbcd in CSGImport::import (this=0x1ffac9b0) at /home/blyth/opticks/CSG/CSGImport.cc:55
    #9  0x00007fffc0449fed in CSGFoundry::importSim (this=0xa18e690) at /home/blyth/opticks/CSG/CSGFoundry.cc:1707
    #10 0x00007fffc044f60a in CSGFoundry::CreateFromSim () at /home/blyth/opticks/CSG/CSGFoundry.cc:2990
    #11 0x00007fffc0fdd345 in G4CXOpticks::setGeometry (this=0xc60aad0, world=0xa58e420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:312
    #12 0x00007fffc0fdb949 in G4CXOpticks::SetGeometry (world=0xa58e420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #13 0x00007fffc0fdbbf8 in G4CXOpticks::SetGeometry_JUNO (world=0xa58e420, sd=0x6518ca0, jpmt=0xc2832c0, jlut=0xc2b2650) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #14 0x00007fffbdd94c76 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xa58e420, sd=0x6518ca0, ppd=0x666b090, psd=0x666bee0, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #15 0x00007fffbdd5a448 in LSExpDetectorConstruction::setupOpticks (this=0xa1dfba0, world=0xa58e420) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #16 0x00007fffbdd59ce9 in LSExpDetectorConstruction::Construct (this=0xa1dfba0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #17 0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #18 0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #19 0x00007fffd485eb1b in DetSimAlg::initialize (this=0x66a1ca0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #20 0x00007fffd0adeb56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007fffd0af409b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #22 0x00007fffd0afc447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


    (gdb) f 5
    #5  0x00007fffc04fdc2a in CSGImport::importPrim (this=0x1ffac9b0, primIdx=2345, node=...) at /home/blyth/opticks/CSG/CSGImport.cc:319
    319	    assert( ln == 0 || ln == 1 ); // simplify initial impl
    (gdb) p ln
    $1 = 4
    (gdb) 







    2025-09-02 11:35:57.594 INFO  [3383976] [U4Tree::Create@247] ]stree::postcreate
    [Detaching after vfork from child process 3384003]
    [CSGImport::importPrim.dump_LVID:1 node.lvid 100 idx_rc 0 LVID -1 name WaterDistributer_1 soname WaterDistributer_1 primIdx 2345 bn 1(binary nodes) ln(subset of bn) 4 ln_expect NO  num_sub_total 35
    [rt.render

    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 0 MINIMAL
                                                                                                          o        
                                                                                                                   
                         o                          o                          o     o  o  o  o  o  o  o     o     
                                                                                                                   
    o  o  o  o  o  o  o     o  o  o  o  o  o  o  o     o  o  o  o  o  o  o  o     o                                
                                                                                                                   
                                                                                                                   
                                                                                                                   

    preorder  sn::desc_order [478 451 443 444 445 446 447 448 449 450 460 452 453 454 455 456 457 458 459 469 461 462 463 464 465 466 467 468 470 471 472 473 474 475 476 477 ]
    inorder   sn::desc_order [443 444 445 446 447 448 449 451 450 452 453 454 455 456 457 458 460 459 461 462 463 464 465 466 467 469 468 470 471 472 473 474 475 476 478 477 ]
    postorder sn::desc_order [443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 ]
     ops = operators(0) 0
     CSG::MaskDesc(ops) : 
     is_positive_form() : YES


    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 1 TYPECODE
                                                                                                          11       
                                                                                                                   
                         11                         11                         11    105105105105105105105   105   
                                                                                                                   
    124124124124124124124   124124124124124124124124   124124124124124124124124   124                              
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 2 DEPTH
                                                                                                          0        
                                                                                                                   
                         1                          1                          1     1  1  1  1  1  1  1     1     
                                                                                                                   
    2  2  2  2  2  2  2     2  2  2  2  2  2  2  2     2  2  2  2  2  2  2  2     2                                
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 3 SUBDEPTH
                                                                                                          0        
                                                                                                                   
                         0                          0                          0     0  0  0  0  0  0  0     0     
                                                                                                                   
    0  0  0  0  0  0  0     0  0  0  0  0  0  0  0     0  0  0  0  0  0  0  0     0                                
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 4 TYPETAG
                                                                                                          co       
                                                                                                                   
                         co                         co                         co    cy cy cy cy cy cy cy    cy    
                                                                                                                   
    cu cu cu cu cu cu cu    cu cu cu cu cu cu cu cu    cu cu cu cu cu cu cu cu    cu                               
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 5 PID
                                                                                                          478      
                                                                                                                   
                         451                        460                        469   470471472473474475476   477   
                                                                                                                   
    443444445446447448449   450452453454455456457458   459461462463464465466467   468                              
                                                                                                                   
                                                                                                                   
                                                                                                                   

    preorder  sn::desc_order [478 451 443 444 445 446 447 448 449 450 460 452 453 454 455 456 457 458 459 469 461 462 463 464 465 466 467 468 470 471 472 473 474 475 476 477 ]
    inorder   sn::desc_order [443 444 445 446 447 448 449 451 450 452 453 454 455 456 457 458 460 459 461 462 463 464 465 466 467 469 468 470 471 472 473 474 475 476 478 477 ]
    postorder sn::desc_order [443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 ]
     ops = operators(0) 0
     CSG::MaskDesc(ops) : 
     is_positive_form() : YES


    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 6 NOTE
                                                                                                          0        
                                                                                                                   
                         0                          0                          0     0  0  0  0  0  0  0     0     
                                                                                                                   
    0  0  0  0  0  0  0     0  0  0  0  0  0  0  0     0  0  0  0  0  0  0  0     0                                
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 7 PARENT
                                                                                                          -2       
                                                                                                                   
                         478                        478                        478   478478478478478478478   478   
                                                                                                                   
    451451451451451451451   451460460460460460460460   460469469469469469469469   469                              
                                                                                                                   
                                                                                                                   
                                                                                                                   



    sn::desc pid  478 idx  478 typecode  11 num_node  36 num_leaf  32 maxdepth  2 is_positive_form Y lvid 100 tag co
    sn::render mode 8 IDX
                                                                                                          478      
                                                                                                                   
                         451                        460                        469   470471472473474475476   477   
                                                                                                                   
    443444445446447448449   450452453454455456457458   459461462463464465466467   468                              
                                                                                                                   
                                                                                                                   
                                                                                                                   


    ]rt.render
    .CSGImport::importPrim dumping as ln > 0 : solid contains listnode
    python: /home/blyth/opticks/CSG/CSGImport.cc:406: CSGPrim* CSGImport::importPrim(int, const snode&): Assertion `sub_offset == bn + num_sub_total' failed.

    (gdb) 






::

     i  96 (sn)root.lvid  96 soname_raw[i] GLb3.bt09_FlangeI_Web_FlangeII root2_match YES
     i  97 (sn)root.lvid  97 soname_raw[i] GLb3.bt10_FlangeI_Web_FlangeII root2_match YES
     i  98 (sn)root.lvid  98 soname_raw[i] GLb3.bt11_FlangeI_Web_FlangeII root2_match YES

     i  99 (sn)root.lvid  99 soname_raw[i] WaterDistributer root2_match YES
     i 100 (sn)root.lvid 100 soname_raw[i] WaterDistributer root2_match YES

     i 101 (sn)root.lvid 101 soname_raw[i] solidSJCLSanchor root2_match YES
     i 102 (sn)root.lvid 102 soname_raw[i] solidSJFixture root2_match YES
     i 103 (sn)root.lvid 103 soname_raw[i] solidSJReceiver root2_match YES
     i 104 (sn)root.lvid 104 soname_raw[i] solidSJReceiverFastern root2_match YES
     i 105 (sn)root.lvid 105 soname_raw[i] sTarget_T root2_match YES
     i 106 (sn)root.lvid 106 soname_raw[i] sAcrylic_T root2_match YES
     i 107 (sn)root.lvid 107 soname_raw[i] sBotChimneySSEnclosureLS_PartI_II_III root2_match YES
     i 108 (sn)root.lvid 108 soname_raw[i] sBotChimneySSEnclosure_PartI_II_III root2_match YES
     i 109 (sn)root.lvid 109 soname_raw[i] sStrut root2_match YES







U4Solid dumping : lvid 99
-----------------------------

::

    [U4Solid::init  99/0/Mul/ -1/1 lvid/depth/tag/root/level WaterDistributer
    [U4Solid::init_MultiUnion { 99/0/Mul/ -1/1}  level 1 name WaterDistributer hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 11
    [U4MultiUnion::Desc
     name WaterDistributer
     sub_num 11
       0 : WaterDistributer_II
       1 : WaterDistributer_I
       2 : WaterDistributer_III
       3 : Hole_0
       4 : Hole_1
       5 : Hole_2
       6 : Hole_3
       7 : Hole_4
       8 : Hole_5
       9 : Hole_6
      10 : Hole_7
    ]U4MultiUnion::Desc

    [U4Solid::init  99/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion { 99/1/Mul/ -1/1}  level 1 name WaterDistributer_II hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_II
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/407/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/408/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/409/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/410/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/411/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/412/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/413/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/414/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init  99/1/Mul/415/1
    -U4Solid::init_MultiUnion i     0 sub_name WaterDistributer_II p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion { 99/1/Mul/ -1/1}  level 1 name WaterDistributer_I hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_I
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/416/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/417/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/418/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/419/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/420/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/421/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/422/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/423/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init  99/1/Mul/424/1
    -U4Solid::init_MultiUnion i     1 sub_name WaterDistributer_I p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000   235.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion { 99/1/Mul/ -1/1}  level 1 name WaterDistributer_III hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_III
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/425/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/426/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/427/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/428/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/429/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/430/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/431/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/2/TuC/ -1/1  
    ]U4Solid::init  99/2/TuC/432/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init  99/1/Mul/433/1
    -U4Solid::init_MultiUnion i     2 sub_name WaterDistributer_III p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000  -235.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/434/1
    -U4Solid::init_MultiUnion i     3 sub_name Hole_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/435/1
    -U4Solid::init_MultiUnion i     4 sub_name Hole_1 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      -848.5281  -848.5281     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/436/1
    -U4Solid::init_MultiUnion i     5 sub_name Hole_2 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
        -0.0000 -1200.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/437/1
    -U4Solid::init_MultiUnion i     6 sub_name Hole_3 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
       848.5281  -848.5281     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/438/1
    -U4Solid::init_MultiUnion i     7 sub_name Hole_4 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      1200.0000    -0.0000     0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/439/1
    -U4Solid::init_MultiUnion i     8 sub_name Hole_5 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
       848.5281   848.5281    -0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/440/1
    -U4Solid::init_MultiUnion i     9 sub_name Hole_6 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
         0.0000  1200.0000    -0.0000     1.0000.

    [U4Solid::init  99/1/Tub/ -1/1  
    ]U4Solid::init  99/1/Tub/441/1
    -U4Solid::init_MultiUnion i    10 sub_name Hole_7 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      -848.5281   848.5281    -0.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init  99/0/Mul/442/1


U4Solid dumping : lvid 100
-----------------------------


::

    [U4Solid::init 100/0/Mul/ -1/1 lvid/depth/tag/root/level WaterDistributer
    [U4Solid::init_MultiUnion {100/0/Mul/ -1/1}  level 1 name WaterDistributer hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 11
    [U4MultiUnion::Desc
     name WaterDistributer
     sub_num 11
       0 : WaterDistributer_II
       1 : WaterDistributer_I
       2 : WaterDistributer_III
       3 : Hole_0
       4 : Hole_1
       5 : Hole_2
       6 : Hole_3
       7 : Hole_4
       8 : Hole_5
       9 : Hole_6
      10 : Hole_7
    ]U4MultiUnion::Desc

    [U4Solid::init 100/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion {100/1/Mul/ -1/1}  level 1 name WaterDistributer_II hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_II
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/443/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/444/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/445/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/446/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/447/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/448/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/449/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/450/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init 100/1/Mul/451/1
    -U4Solid::init_MultiUnion i     0 sub_name WaterDistributer_II p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion {100/1/Mul/ -1/1}  level 1 name WaterDistributer_I hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_I
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/452/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/453/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/454/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/455/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/456/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/457/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/458/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/459/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init 100/1/Mul/460/1
    -U4Solid::init_MultiUnion i     1 sub_name WaterDistributer_I p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000   235.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Mul/ -1/1  
    [U4Solid::init_MultiUnion {100/1/Mul/ -1/1}  level 1 name WaterDistributer_III hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 8
    [U4MultiUnion::Desc
     name WaterDistributer_III
     sub_num 8
       0 : CutTube_0
       1 : CutTube_1
       2 : CutTube_2
       3 : CutTube_3
       4 : CutTube_4
       5 : CutTube_5
       6 : CutTube_6
       7 : CutTube_7
    ]U4MultiUnion::Desc

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/461/1
    -U4Solid::init_MultiUnion i     0 sub_name CutTube_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/462/1
    -U4Solid::init_MultiUnion i     1 sub_name CutTube_1 p_expect YES
    .
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.7071     0.0000     0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/463/1
    -U4Solid::init_MultiUnion i     2 sub_name CutTube_2 p_expect YES
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/464/1
    -U4Solid::init_MultiUnion i     3 sub_name CutTube_3 p_expect YES
    .
        -0.7071     0.0000    -0.7071     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.7071     0.0000    -0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/465/1
    -U4Solid::init_MultiUnion i     4 sub_name CutTube_4 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
         0.0000     0.0000    -1.0000     0.0000.
     -1200.0000     0.0000    -0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/466/1
    -U4Solid::init_MultiUnion i     5 sub_name CutTube_5 p_expect YES
    .
        -0.7071     0.0000     0.7071     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000    -0.7071     0.0000.
        -0.0000     0.0000  1200.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/467/1
    -U4Solid::init_MultiUnion i     6 sub_name CutTube_6 p_expect YES
    .
        -0.0000     0.0000     1.0000     0.0000.
        -0.0000     1.0000     0.0000     0.0000.
        -1.0000     0.0000    -0.0000     0.0000.
      1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/2/TuC/ -1/1  
    ]U4Solid::init 100/2/TuC/468/1
    -U4Solid::init_MultiUnion i     7 sub_name CutTube_7 p_expect YES
    .
         0.7071     0.0000     0.7071     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.7071     0.0000     0.7071     0.0000.
         0.0000     0.0000 -1200.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init 100/1/Mul/469/1
    -U4Solid::init_MultiUnion i     2 sub_name WaterDistributer_III p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000  -235.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/470/1
    -U4Solid::init_MultiUnion i     3 sub_name Hole_0 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
     -1200.0000     0.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/471/1
    -U4Solid::init_MultiUnion i     4 sub_name Hole_1 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      -848.5281  -848.5281     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/472/1
    -U4Solid::init_MultiUnion i     5 sub_name Hole_2 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
        -0.0000 -1200.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/473/1
    -U4Solid::init_MultiUnion i     6 sub_name Hole_3 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
       848.5281  -848.5281     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/474/1
    -U4Solid::init_MultiUnion i     7 sub_name Hole_4 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      1200.0000    -0.0000     0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/475/1
    -U4Solid::init_MultiUnion i     8 sub_name Hole_5 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
       848.5281   848.5281    -0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/476/1
    -U4Solid::init_MultiUnion i     9 sub_name Hole_6 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
         0.0000  1200.0000    -0.0000     1.0000.

    [U4Solid::init 100/1/Tub/ -1/1  
    ]U4Solid::init 100/1/Tub/477/1
    -U4Solid::init_MultiUnion i    10 sub_name Hole_7 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      -848.5281   848.5281    -0.0000     1.0000.

    ]U4Solid::init_MultiUnion level 1
    ]U4Solid::init 100/0/Mul/478/1




Why two lvid 99 and 100 when look the same ?
-----------------------------------------------

::


    (ok) A[blyth@localhost opticks]$ jgr WaterDistributer
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:#ifndef UpperWaterDistributer_hh
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:#define UpperWaterDistributer_hh
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:class UpperWaterDistributer : public IDetElement,
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    UpperWaterDistributer(const std::string& name);
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    ~UpperWaterDistributer();
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    void makeUpperWaterDistributerLogicalandPhysical();
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    G4VSolid*          solidUpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    G4LogicalVolume*   logicUpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh:    bool m_use_UpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributerPlacement.hh:class UpperWaterDistributerPlacement: public IDetElementPos,
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributerPlacement.hh:    UpperWaterDistributerPlacement(const std::string& name);
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributerPlacement.hh:    ~UpperWaterDistributerPlacement();

    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    WaterdistributerlooppipeMaker* pipeMaker = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I, TubeR_type_II, TubeR_type_I);
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    G4LogicalVolume* logicMultiUnion = new G4LogicalVolume(pipeSolid, PVDF, "LogicWaterDistributer");
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:        "PhysWaterDistributer",
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    WaterdistributerlooppipeMaker* pipeMaker_partII = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I - 5 *mm, TubeR_type_II - 5 *mm, TubeR_type_I - 5 *mm);
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    G4LogicalVolume* logicMultiUnion_partII = new G4LogicalVolume(pipeSolid_partII, Water, "LogicWaterDistributer_partII");
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:        "PhysWaterDistributer_partII",
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:        "PhysWaterDistributer",

    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:#include "UpperWaterDistributerPlacement.hh"
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:DECLARE_TOOL(UpperWaterDistributerPlacement);
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:UpperWaterDistributerPlacement::UpperWaterDistributerPlacement(const std::string& name) 
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:UpperWaterDistributerPlacement::~UpperWaterDistributerPlacement() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:UpperWaterDistributerPlacement::hasNext() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:UpperWaterDistributerPlacement::next() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc:void UpperWaterDistributerPlacement::init() {

    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc:    auto solid_I = helper_Waterdistributerlooppipe("WaterDistributer_I",distance, TubeR_I);
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc:    auto solid_II = helper_Waterdistributerlooppipe("WaterDistributer_II",distance, TubeR_II);
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc:    auto solid_III = helper_Waterdistributerlooppipe("WaterDistributer_III",distance, TubeR_III);

    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:#include "UpperWaterDistributer.hh"
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:DECLARE_TOOL(UpperWaterDistributer);
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::UpperWaterDistributer(const std::string& name)
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    logicUpperWaterDistributer(nullptr)
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    declProp("UseUpperWaterDistributer", m_use_UpperWaterDistributer=true);//Default: upper chimney is enabled
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::~UpperWaterDistributer() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::getLV() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    if (logicUpperWaterDistributer) {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        return logicUpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    if (m_use_UpperWaterDistributer) {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        G4cout<<"Begin Upper UpperWaterDistributer Construction"<<G4endl;
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        makeUpperWaterDistributerLogicalandPhysical();
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    logicUpperWaterDistributer -> SetVisAttributes(ct_visatt);
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    return logicUpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::inject(std::string motherName, IDetElement* other, IDetElementPos* /*pos*/) {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    if ( motherName == "lUpperWaterDistributer" ) {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        mothervol = logicUpperWaterDistributer;
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::initVariables() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    //TopToWater=m_UpperWaterDistributerTopToWater*m;
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:UpperWaterDistributer::initMaterials() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:void UpperWaterDistributer::makeUpperWaterDistributerLogicalandPhysical() {
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    logicUpperWaterDistributer = new G4LogicalVolume(
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        "lUpperWaterDistributer"
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    G4OpticalSurface* steel_surface = new G4OpticalSurface("WaterDistributerOpticalSurface");
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    new G4LogicalSkinSurface("Steel_surface",logicUpperWaterDistributer,steel_surface);

    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     void setupUpperWaterDistributer();

    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        return self.tool("UpperWaterDistributer")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        return self.tool("UpperWaterDistributerPlacement")

    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    WaterdistributerlooppipeMaker* pipeMaker = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I, TubeR_type_II, TubeR_type_I);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4LogicalVolume* logicMultiUnion = new G4LogicalVolume(pipeSolid, PVDF, "LogicWaterDistributer");
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        "PhysWaterDistributer",
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    WaterdistributerlooppipeMaker* pipeMaker_partII = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I - 5 *mm, TubeR_type_II - 5 *mm, TubeR_type_I - 5 *mm);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4LogicalVolume* logicMultiUnion_partII = new G4LogicalVolume(pipeSolid_partII, Water, "LogicWaterDistributer_partII");
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        "PhysWaterDistributer_partII",
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        "PhysWaterDistributer",
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4LogicalVolume* logicUpperWaterDistributer = new G4LogicalVolume(
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        "lUpperWaterDistributer"
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:            logicUpperWaterDistributer,
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:            "pUpperWaterDistributer",
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    logicUpperWaterDistributer -> SetVisAttributes(ct_visatt);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4OpticalSurface* steel_surface = new G4OpticalSurface("WaterDistributerOpticalSurface");
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    new G4LogicalSkinSurface("Steel_surface",logicUpperWaterDistributer,steel_surface);

    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  setupUpperWaterDistributer();
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:LSExpDetectorConstruction::setupUpperWaterDistributer()
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    wd_tool_name = "UpperWaterDistributer";
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    pos_tool_name = "UpperWaterDistributerPlacement";
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:        G4cout << "Can't find the UpperWaterDistributer(" << wd_tool_name << ")" << std::endl;

    ./oj_translate_debug.sh:export U4Solid__IsFlaggedName=WaterDistributer
    (ok) A[blyth@localhost junosw]$ 




The two WaterDistributer (lvid 99 and 100) solids differ only in TubeRadii the outer being PVDF and inner Water
------------------------------------------------------------------------------------------------------------------


jcv WaterPoolConstruction::

     815 void WaterPoolConstruction::makeWaterDistributorPartILogicalandPhysical() {
     816     G4double pipe_radius = 159.0/2 * mm;
     817     G4double A_length = 2780 * mm;
     818 
     ...
     856 
     857     WaterdistributerlooppipeMaker* pipeMaker = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I, TubeR_type_II, TubeR_type_I);
     858     G4VSolid* pipeSolid = pipeMaker->getSolid();
     859 
     860     G4LogicalVolume* logicMultiUnion = new G4LogicalVolume(pipeSolid, PVDF, "LogicWaterDistributer");
     861 
     862     G4VPhysicalVolume* physiMultiUnion =new G4PVPlacement(
     863         rotate,
     864         G4ThreeVector(0, 0, 21409),
     865         logicMultiUnion,
     866         "PhysWaterDistributer",
     867         logicWaterPool,
     868         false,
     869         3);
     870 
     871     G4VisAttributes* visAttr1 = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
     872     visAttr1 -> SetForceAuxEdgeVisible(true);
     873     logicMultiUnion->SetVisAttributes(visAttr1);
     874 
     875     WaterdistributerlooppipeMaker* pipeMaker_partII = new WaterdistributerlooppipeMaker("WaterDistributer", TubeR_type_I - 5 *mm, TubeR_type_II - 5 *mm, TubeR_type_I - 5 *mm);
     876     G4VSolid* pipeSolid_partII = pipeMaker_partII->getSolid();
     877     G4LogicalVolume* logicMultiUnion_partII = new G4LogicalVolume(pipeSolid_partII, Water, "LogicWaterDistributer_partII");
     878 
     879     new G4PVPlacement(
     880         0,
     881         G4ThreeVector(0, 0, 0),
     882         logicMultiUnion_partII,
     883         "PhysWaterDistributer_partII",
     884         logicMultiUnion,
     885         false,
     886         0);
     887 
     888     G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
     889     visAttr->SetForceSolid(true);
     890     logicMultiUnion_partII->SetVisAttributes(visAttr);
     891 
     892     G4OpticalSurface* pvdf_surface = new G4OpticalSurface("PVDFOpticalSurface");
     893     pvdf_surface->SetModel(unified);
     894     pvdf_surface->SetType(dielectric_dielectric);
     895     pvdf_surface->SetFinish(ground);
     896     pvdf_surface->SetSigmaAlpha(0.1);
     897 
     898     G4MaterialPropertiesTable* pvdf_mt = new G4MaterialPropertiesTable();
     899 
     900     const G4int nEntries = 4;
     901     G4double photonEnergy[nEntries] = {1.55 * eV, 6.20 * eV, 10.33 * eV, 15.5 * eV};
     902 
     903     G4double refractiveIndex[nEntries] = {1.42, 1.42, 1.42, 1.42};


WaterdistributerlooppipeMaker : HUH : why make a multiunion of multiunions ? 
-------------------------------------------------------------------------------


jcv WaterdistributerlooppipeMaker::



U4SolidMakerTest.sh
---------------------

~/o/u4/tests/U4SolidMakerTest.sh


cxr_min.sh
------------

::

    tarting program: /data1/blyth/local/opticks_Debug/lib/CSGOptiXRenderInteractiveTest 
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    [Detaching after vfork from child process 438173]
    CSGOptiXRenderInteractiveTest: /home/blyth/opticks/sysrap/SBitSet.h:248: static void SBitSet::ParseSpec(unsigned int, bool*, const char*): Assertion `upos < num_bits' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff4a8b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff4a3e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff4a28833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff4a2875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff4a373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007ffff593fc52 in SBitSet::ParseSpec (num_bits=319, bits=0x11600050, 
        spec=0x7fffffffe5a4 "t:,sWorld,sBottomRock,sTopRock,sExpHall,sExpRockBox,sDomeRockBox,sTopRock_domeAir,sTopRock_dome,sDomeRockBox,sAirTT,PoolCoversub,sAirGap,sDeadWater_shell,sTyvek_shell,sOuterWaterPool,sPoolLining,sTarg"...)
        at /home/blyth/opticks/sysrap/SBitSet.h:248
    #6  0x00007ffff593ff05 in SBitSet::parse_spec (this=0x14390400, 
        spec=0x7fffffffe5a4 "t:,sWorld,sBottomRock,sTopRock,sExpHall,sExpRockBox,sDomeRockBox,sTopRock_domeAir,sTopRock_dome,sDomeRockBox,sAirTT,PoolCoversub,sAirGap,sDeadWater_shell,sTyvek_shell,sOuterWaterPool,sPoolLining,sTarg"...)
        at /home/blyth/opticks/sysrap/SBitSet.h:356
    #7  0x00007ffff593fa88 in SBitSet::Create (num_bits=319, 
        spec=0x7fffffffe5a4 "t:,sWorld,sBottomRock,sTopRock,sExpHall,sExpRockBox,sDomeRockBox,sTopRock_domeAir,sTopRock_dome,sDomeRockBox,sAirTT,PoolCoversub,sAirGap,sDeadWater_shell,sTyvek_shell,sOuterWaterPool,sPoolLining,sTarg"...)
        at /home/blyth/opticks/sysrap/SBitSet.h:158
    #8  0x00007ffff593dca8 in SGeoConfig::ELV (id=0x12d89ef0) at /home/blyth/opticks/sysrap/SGeoConfig.cc:211
    #9  0x00007ffff764f760 in CSGFoundry::Load () at /home/blyth/opticks/CSG/CSGFoundry.cc:3034
    #10 0x0000000000491c1d in CSGOptiXRenderInteractiveTest::CSGOptiXRenderInteractiveTest (this=0x7fffffffb1a0) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:106
    #11 0x0000000000445e64 in main (argc=1, argv=0x7fffffffb348) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:206
    (gdb) 




::

     BFOLD_RECORD_SLICE :  
                    _CUR : GEOM/J25_4_0_opticks_Debug/cxr_min/wp_atm_lpmt 
    2025-09-02 21:02:45.442 FATAL [3026753] [CSGNode::setAABBLocal@491]  not implemented for tc 125 CSG::Name(tc) notsupported
    CSGOptiXRenderInteractiveTest: /home/blyth/opticks/CSG/CSGNode.cc:492: void CSGNode::setAABBLocal(): Assertion `0' failed.
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh: line 335: 3026753 Aborted                 (core dumped) $bin
    /data1/blyth/local/opticks_Debug/bin/cxr_min.sh run error
    (ok) A[blyth@localhost opticks]$ 



