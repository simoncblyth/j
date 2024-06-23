initRayleigh_standard_nullptr : June 13 2024
=================================================


* j/jok.bash added NOREPORT skipping of jok-report thats used from jok-tds-gdb 

::

    jsw
    jok-
    jok-tds-gdb


    #49 0x00007ffff7c265b7 in pymain_main (args=0x7fffffff4bd0) at Modules/main.c:707
    #50 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:731
    #51 0x00007ffff6b20555 in __libc_start_main () from /lib64/libc.so.6
    #52 0x000000000040108e in _start ()
    (gdb) f 5
    #5  0x00007fffcd2d00d5 in G4CXOpticks::SetGeometry (world=0x97b0d10) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:58
    58      g4cx->setGeometry(world); 
    (gdb) f 4
    #4  0x00007fffcd2d1913 in G4CXOpticks::setGeometry (this=0xaef6540, world=0x97b0d10) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:250
    250     tr = U4Tree::Create(st, world, SensorIdentifier ) ;
    (gdb) f 3
    #3  0x00007fffcd315546 in U4Tree::Create (st=0xaef5cb0, top=0x97b0d10, sid=0x0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:210
    210     U4Tree* tree = new U4Tree(st, top, sid ) ;
    (gdb) f 2
    #2  0x00007fffcd315877 in U4Tree::U4Tree (this=0xaef6590, st_=0xaef5cb0, top_=0x97b0d10, sid_=0x0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:241
    241     init(); 
    (gdb) f 1
    #1  0x00007fffcd31590a in U4Tree::init (this=0xaef6590) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:254
    254     initRayleigh(); 
    (gdb) f 0 
    #0  0x00007fffcd315f36 in U4Tree::initRayleigh (this=0xaef6590) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:377
    377     st->standard->rayleigh = rayleigh_table ? ra yleigh_table->tab : nullptr  ; 
    (gdb) p rayleigh_table
    $1 = (U4PhysicsTable<G4OpRayleigh> *) 0xaef5c70
    (gdb) p rayleigh_table->tab
    $2 = (NP *) 0xaea3e20
    (gdb) p rayleigh_table->tab->shape
    $3 = std::vector of length 3, capacity 4 = {45, 37, 2}
    (gdb) p st
    $4 = (stree *) 0xaef5cb0
    (gdb) p st->standard
    $5 = (sstandard *) 0x0

    (gdb) p st
    $6 = (stree *) 0xaef5cb0
    (gdb) 


standard null points to header version mismatch::

     668 inline stree::stree()
     669     :
     670     level(ssys::getenvint("stree_level", 0)),
     671     force_triangulate_solid(ssys::getenvvar(stree__force_triangulate_solid,nullptr)),
     672     sensor_count(0),
     673     subs_freq(new sfreq),
     674     _csg(new s_csg),
     675     standard(new sstandard),
     676     material(new NPFold),
     677     surface(new NPFold),
     678     mesh(new NPFold)
     679 {
     680     init();
     681 }


Probably need clean build, recently changing stree.h for integrated triangles.  
Is stree.h hidden from point of view of JUNOSW ? It should be its deep in, should just need opticks rebuild::

    opticks-full-make



YEP: fixed get back to expected tree height fail::

    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffc5a131d3 in st::complete_binary_tree_nodes (height=64) at /data/blyth/opticks_Debug/include/SysRap/st.h:25
    #5  0x00007fffc5a156d0 in sn::getLVBinNode (this=0xb40dfd0) at /data/blyth/opticks_Debug/include/SysRap/sn.h:3635
    #6  0x00007fffc5a159ae in sn::getLVNodesComplete (this=0xb40dfd0, nds=std::vector of length 0, capacity 0) at /data/blyth/opticks_Debug/include/SysRap/sn.h:3743
    #7  0x00007fffc5a1583e in sn::GetLVNodesComplete (nds=std::vector of length 0, capacity 0, lvid=19) at /data/blyth/opticks_Debug/include/SysRap/sn.h:3709
    #8  0x00007fffc5a0886c in CSGImport::importPrim (this=0x155e8a90, primIdx=206, node=...) at /home/blyth/opticks/CSG/CSGImport.cc:254
    #9  0x00007fffc5a0828a in CSGImport::importSolidRemainder (this=0x155e8a90, ridx=0, rlabel=0x7fffffff2730 "r0") at /home/blyth/opticks/CSG/CSGImport.cc:136
    #10 0x00007fffc5a08002 in CSGImport::importSolid (this=0x155e8a90) at /home/blyth/opticks/CSG/CSGImport.cc:92
    #11 0x00007fffc5a07e1d in CSGImport::import (this=0x155e8a90) at /home/blyth/opticks/CSG/CSGImport.cc:55
    #12 0x00007fffc5989901 in CSGFoundry::importSim (this=0x155fbf40) at /home/blyth/opticks/CSG/CSGFoundry.cc:1591
    #13 0x00007fffc598ef18 in CSGFoundry::CreateFromSim () at /home/blyth/opticks/CSG/CSGFoundry.cc:2887
    #14 0x00007fffcd2d19f7 in G4CXOpticks::setGeometry (this=0xaef7350, world=0x97b1a70) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:256
    #15 0x00007fffcd2d00d5 in G4CXOpticks::SetGeometry (world=0x97b1a70) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:58
    #16 0x00007fffbe3dd3ef in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0x97b1a70, sd=0x995ad20, ppd=0x6588030, psd=0x656cac0, pmtscan=0x0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:56
    #17 0x00007fffbe3b25f2 in LSExpDetectorConstruction::setupOpticks (this=0x95bf610, world=0x97b1a70) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:454
    #18 0x00007fffbe3b1ec0 in LSExpDetectorConstruction::Construct (this=0x95bf610) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:375
    #19 0x00007fffcc1a495e in G4RunManager::InitializeGeometry() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #20 0x00007fffcc1a4b2c in G4RunManager::Initialize() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #21 0x00007fffbdc4ab1b in DetSimAlg::initialize (this=0x6c01230) at /data/blyth/junotop/junosw/Sim



Add NUM_HOLE=0 for 4 loops in "jcv WaterPoolConstruction" then::

     jo
     ./build_Debug.sh 


     jok-tds-gdb




