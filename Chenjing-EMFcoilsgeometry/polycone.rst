



U4Polycone.h::

    337     double startPhi = ph->Start_angle/CLHEP::radian ;
    338     double deltaPhi = ph->Opening_angle/CLHEP::radian ;
    339     bool has_phi_segment = startPhi > 0. || deltaPhi < 2.0*CLHEP::pi  ;
    340     bool has_phi_segment_expect = has_phi_segment == false ;
    341     assert( has_phi_segment_expect );
    342     if(!has_phi_segment_expect) std::raise(SIGINT);
    343 }




::

    sn::increase_zmax_ lvid 65 _zmax  -33.50 dz    1.00 new_zmax  -32.50
    python: /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:341: void U4Polycone::init_RZ(): Assertion `has_phi_segment_expect' failed.
     *** Break *** abort

    #10 0x00007f80d1237886 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f809ad705e8 in U4Polycone::init_RZ (this=0x7ffd9ff891b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:341
    #12 0x00007f809ad70110 in U4Polycone::init (this=0x7ffd9ff891b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:261
    #13 0x00007f809ad6febd in U4Polycone::U4Polycone (this=0x7ffd9ff891b0, polycone_=0xbafd6f0, lvid_=82, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:236
    #14 0x00007f809ad6f406 in U4Polycone::Convert (polycone=0xbafd6f0, lvid=82, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:151
    #15 0x00007f809ad7375d in U4Solid::init_Polycone (this=0x7ffd9ff894d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:887
    #16 0x00007f809ad719b4 in U4Solid::init_Constituents (this=0x7ffd9ff894d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:406
    #17 0x00007f809ad71860 in U4Solid::init (this=0x7ffd9ff894d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:381
    #18 0x00007f809ad71732 in U4Solid::U4Solid (this=0x7ffd9ff894d0, solid_=0xbafd6f0, lvid_=82, depth_=0, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:368
    #19 0x00007f809ad7163e in U4Solid::Convert (solid=0xbafd6f0, lvid=82, depth=0, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:349
    #20 0x00007f809ad77c58 in U4Tree::initSolid (this=0xdf902b0, so=0xbafd6f0, lvid=82) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:713
    #21 0x00007f809ad77bb0 in U4Tree::initSolid (this=0xdf902b0, lv=0xbafeb40) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:681
    #22 0x00007f809ad77b46 in U4Tree::initSolids_r (this=0xdf902b0, pv=0xbafd630) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:674
    #23 0x00007f809ad77ae1 in U4Tree::initSolids_r (this=0xdf902b0, pv=0xc534f50) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #24 0x00007f809ad77ae1 in U4Tree::initSolids_r (this=0xdf902b0, pv=0xbb08460) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #25 0x00007f809ad77ae1 in U4Tree::initSolids_r (this=0xdf902b0, pv=0xbb084c0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #26 0x00007f809ad77ae1 in U4Tree::initSolids_r (this=0xdf902b0, pv=0xbaf5420) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #27 0x00007f809ad77851 in U4Tree::initSolids (this=0xdf902b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:614
    #28 0x00007f809ad76036 in U4Tree::init (this=0xdf902b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:299
    #29 0x00007f809ad75a6d in U4Tree::U4Tree (this=0xdf902b0, st_=0x7bd27b0, top_=0xbaf5420, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:270
    #30 0x00007f809ad74f96 in U4Tree::Create (st=0x7bd27b0, top=0xbaf5420, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:226
    #31 0x00007f809ad1b0e8 in G4CXOpticks::setGeometry (this=0xdc6b800, world=0xbaf5420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:305
    #32 0x00007f809ad19aa1 in G4CXOpticks::SetGeometry (world=0xbaf5420) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:79
    #33 0x00007f809ad19d50 in G4CXOpticks::SetGeometry_JUNO (world=0xbaf5420, sd=0xb619ce0, jpmt=0xdbfeb90, jlut=0xdc737f0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:117
    #34 0x00007f8097342414 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xbaf5420, sd=0xb619ce0, ppd=0x794f7a0, psd=0x78a9fa0, pmtscan=0x0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #35 0x00007f80973064a6 in LSExpDetectorConstruction::setupOpticks (this=0xb861960, world=0xbaf5420) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #36 0x00007f8097305d46 in LSExpDetectorConstruction::Construct (this=0xb861960) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393


