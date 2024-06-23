WaterPoolConstruction_pillars
===============================

Guesswork and hints from Tao

* A:inner circle of pillars
* B:outer circle of pillars

* 01,02,03,04,05,06,07  vertical layers (07 at bottom)

* GZ1 verticals : 6 verticals between 7 layers always within A:inner or B:outer
* ZC2 cross pieces joining levels : horizontal and angled


WaterPoolConstruction::

    571 PillarData all_pillar_data[] = {
    572     {"GZ1.A01_02"},                
    573     {"GZ1.A02_03"},
    575     {"GZ1.A03_04"},
    576     {"GZ1.A04_05"},
    577     {"GZ1.A05_06"},
    578     {"GZ1.A06_07"},        //<== inner? vertical at bottom of pillar   
    ///                            GZ1.A0(n)_0(n+1): 6 inner? verticals
    579 
    580     {"GZ1.B01_02"},
    581     {"GZ1.B02_03"},
    582     {"GZ1.B03_04"},
    583     {"GZ1.B04_05"},
    584     {"GZ1.B05_06"},
    585     {"GZ1.B06_07"},        //<== outer? vertical at bottom of pillar 
    ///                            GZ1.B0(n)_0(n+1): 6 outer? verticals
    586 
    587     {"ZC2.A02_B02"},
    589     {"ZC2.A03_B03"},
    590     {"ZC2.A04_B04"},
    591     {"ZC2.A05_B05"},
    592     {"ZC2.A06_B06"},    
    //                             ZC2.A0(n)-B0(n) n=02,03,04,05,06   5 horizontal inner->outer cross pieces  
    //                             none at top and bottom
    593 
    594     {"ZC2.A02_B03"},
    596     {"ZC2.A03_B04"},
    597     {"ZC2.A04_B05"},
    598     {"ZC2.A05_B06"},
    599     {"ZC2.A06_B07"},      //<== angled inner-outer cross piece at bottom [TO SKIP]  
    //                             ZC2.A0(n)_B0(n+1)  5 angled inner->outer cross pieces  [from mid to lower]
    //                             
    600 
    601     {"ZC2.B01_B01"},    
    602     {"ZC2.B03_B03"},
    603     {"ZC2.B05_B05"},     
    //                             ZC2.B0(n)-B0(n)   3 horizontal outer cross pieces   [upper]
    604 
    605     {"ZC2.A03_A03"},     
    606     {"ZC2.A05_A05"},     
    //                             ZC2.A0(n)-A0(n)   2 horizontal inner cross pieces    [upper]
    607 
    608     {"END"}
    609 };



HBeamConstruction::

    171 double
    172 HBeamConstruction::geom_info(const std::string& param) {
    173     if (param == "H") {
    174         return m_H;
    175     } else if (param == "B") {
    176         return m_B;
    177     } else if (param == "tw") {
    178         return m_tw;
    179     } else if (param == "tf") {
    180         return m_tf;
    181     } else if (param == "L") {
    182         return m_L;
    183     } else if (param == "theta") {
    184         return m_theta;
    185     } else if (param == "direct_theta") {
    186         return m_direct_theta;
    187     } else if (param == "R") {
    188         return m_radial;
    189     } else if (param == "z") {
    190         return m_z;
    191     } else {
    192         LogError << "Unknown parameter: " << param << std::endl;
    193     }
    194     return 0.0;
    195 }



    335 struct PillarData {
    336     std::string name; // model.label
    337     double theta; // rotation?
    338     double direct_theta; // without rotate 90deg. rotate, y axis
    339     double L;     // mm
    340     // others?
    341     double radial;
    342     double z;
    343 };


    404     m_theta = p_pillar->theta;
    405     m_direct_theta = p_pillar->direct_theta;
    406     m_L = p_pillar->L;
    407 
    408     m_radial = p_pillar->radial;
    409     m_z = p_pillar->z;
    410 }


    345 static const PillarData pillar_data[] = {
    346     {"BEGIN", 0, 0, 0, 0, 0},
    347 
    348     {"GZ1.A01_02", atan(1108.831/2885.), 0., 3090.749, 20200.863-1108.831/2, -6099-2885./2},
    349     {"GZ1.A02_03", atan(1516.734/2693.), 0., 3090.749, 20200.863-1108.831-1516.734/2, -8984.-2693./2},
    350 
    351     {"GZ1.A03_04", 3.362*deg, 0., 2522.342, 20200.863-3200.+574.435/8*7, -11677-2518./2},
    352     {"GZ1.A04_05", 3.362*deg, 0., 2522.342, 20200.863-3200.+574.435/8*5, -14195-2518./2},
    353     {"GZ1.A05_06", 3.362*deg, 0., 2522.342, 20200.863-3200.+574.435/8*3, -16713-2518./2},
    354     {"GZ1.A06_07", 3.362*deg, 0., 2522.342, 20200.863-3200.+574.435/8*1, -19231-2518./2},

    355 
    356     {"GZ1.B01_02", 0.0, 0., 2885., 20200.863, -6099.-2885./2},
    357     {"GZ1.B02_03", 0.0, 0., 2693., 20200.863, -8984.-2693./2},

    358     {"GZ1.B03_04", 0.0, 0., 2518., 20200.863, -11677-2518./2},
    359     {"GZ1.B04_05", 0.0, 0., 2518., 20200.863, -14195-2518./2},
    360     {"GZ1.B05_06", 0.0, 0., 2518., 20200.863, -16713-2518./2},
    361     {"GZ1.B06_07", 0.0, 0., 2518., 20200.863, -19231-2518./2},


    362 
    363     {"ZC2.A02_B02", 90.*deg, 0., 1108.831, 20200.863-1108.831/2, -8984},
    364 
    365     {"ZC2.A03_B03", 90.*deg, 0., 3200.-574.435/4*4, 20199.-(3200.-574.435/4*4)/2, -11677},
    366     {"ZC2.A04_B04", 90.*deg, 0., 3200.-574.435/4*3, 20199.-(3200.-574.435/4*3)/2, -14195},
    367     {"ZC2.A05_B05", 90.*deg, 0., 3200.-574.435/4*2, 20199.-(3200.-574.435/4*2)/2, -16713},
    368     {"ZC2.A06_B06", 90.*deg, 0., 3200.-574.435/4*1, 20199.-(3200.-574.435/4*1)/2, -19231},
    369 
    370     {"ZC2.A02_B03", -atan(1108.831/2693.), 0., 2912.345, 20200.863-1108.831/2, -8984.-2693./2},
    371 
    372     {"ZC2.A03_B04", -atan((3200.-574.435/4*4)/2518.), 0., sqrt(pow(3200.-574.435/4*4, 2)+pow(2518., 2)), 20199.-(3200.-574.435/4*4)/2, -11677-2518./2},
    373     {"ZC2.A04_B05", -atan((3200.-574.435/4*3)/2518.), 0., sqrt(pow(3200.-574.435/4*3, 2)+pow(2518., 2)), 20199.-(3200.-574.435/4*3)/2, -14195-2518./2},
    374     {"ZC2.A05_B06", -atan((3200.-574.435/4*2)/2518.), 0., sqrt(pow(3200.-574.435/4*2, 2)+pow(2518., 2)), 20199.-(3200.-574.435/4*2)/2, -16713-2518./2},
    375     {"ZC2.A06_B07", -atan((3200.-574.435/4*1)/2518.), 0., sqrt(pow(3200.-574.435/4*1, 2)+pow(2518., 2)), 20199.-(3200.-574.435/4*1)/2, -19231-2518./2},
    376 
    377     {"ZC2.B01_B01", 0., 90.*deg, 4223.130, 20090.201, -6099},
    378     {"ZC2.B03_B03", 0., 90.*deg, 4223.130, 20090.201, -11677},
    379     {"ZC2.B05_B05", 0., 90.*deg, 4223.130, 20090.201, -16713},
    380 
    381     {"ZC2.A03_A03", 0., 90.*deg, 3673.848, 17477.166, -11677},
    382     {"ZC2.A05_A05", 0., 90.*deg, 3613.804, 17191.522, -16713},
    383 
    384     {"END", 0, 0, 0, 0, 0}
    385 };



Inner pillars are tilted::

    In [7]: np.cos(3.362*np.pi/180)*2522.342
    Out[7]: 2518.0009027456135


Outer pillars are vertical::

    In [8]: np.cos(0.*np.pi/180)*2518
    Out[8]: 2518.0

Looks like can scale the length by same factor.


ConfAcrylic.py::


    217         # pillar
    218         data_pillar = [
    219             ("GZ1.A01_02", ()),
    220             ("GZ1.A02_03", ()),
    221             ("GZ1.A03_04", ()),
    222             ("GZ1.A04_05", ()),
    223             ("GZ1.A05_06", ()),
    224             ("GZ1.A06_07", ()),

    225             ("GZ1.B01_02", ()),
    226             ("GZ1.B02_03", ()),
    227             ("GZ1.B03_04", ()),
    228             ("GZ1.B04_05", ()),
    229             ("GZ1.B05_06", ()),
    230             ("GZ1.B06_07", ()),

    231             ("ZC2.A02_B02", ()),
    232             ("ZC2.A03_B03", ()),
    233             ("ZC2.A04_B04", ()),
    234             ("ZC2.A05_B05", ()),
    235             ("ZC2.A06_B06", ()),

    236             ("ZC2.A02_B03", ()),
    237             ("ZC2.A03_B04", ()),
    238             ("ZC2.A04_B05", ()),
    239             ("ZC2.A05_B06", ()),
    240             ("ZC2.A06_B07", ()),

    241             ("ZC2.B01_B01", ()),
    242             ("ZC2.B03_B03", ()),
    243             ("ZC2.B05_B05", ()),

    244             ("ZC2.A03_A03", ()),
    245             ("ZC2.A05_A05", ()),
    246         ]
    247 





Which volume is the bottom of the leg ?
--------------------------------------------

* looks like the inner and outer verticals at bottom of pillar are::

   GZ1.A06_07
   GZ1.B06_07


* cross pieces at bottom of pillar::

   ZC2.A06_B07   

::

   export ConfAcrylic__data_pillar_fix=1 




::


    703     for (PillarData* p = all_pillar_data; p->name!="END"; ++p) {
    704         IDetElement* de = dynamic_cast<IDetElement*>(detsimalg->findTool(p->name));
    705         assert(de);
    706 
    707         G4LogicalVolume* daughtervol = de->getLV();
    708         assert(daughtervol);
    709 
    710         double R = de->geom_info("R");
    711         double z = de->geom_info("z");
    712         double theta = de->geom_info("theta");
    713         double direct_theta = de->geom_info("direct_theta");
    714         // if direct_theta is not zero, the beam is connect different column
    715         double start_phi = 6.*deg;
    716         if (direct_theta!=0.0) {
    717             start_phi = 0.;
    718         }
    719 
    720         for (int copyno = 0; copyno < 30; ++copyno) { // phi
    721             double phi = start_phi + copyno*12.*deg;
    722 
    723             double x = R * cos(phi);
    724             double y = R * sin(phi);
    725             LogInfo << "Pillars R, phi : " << copyno<<", "<<R<<", "<<phi<< std::endl;
    726 
    727 



C++ vs python in control
---------------------------

Tao suggest to remove the python 


::

    [blyth@localhost junosw]$ jgr GZ1.A01_02
    ./Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc:    {"GZ1.A01_02", atan(1108.831/2885.), 0., 3090.749, 20200.863-1108.831/2, -6099-2885./2},
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:            ("GZ1.A01_02", ()),
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:            ("GZ1.A01_02", ()),
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    {"GZ1.A01_02"},
    [blyth@localhost junosw]$ 




Try skipping the lower cross piece
--------------------------------------

::

    junotoptask:DetSimAlg.WaterPoolConstruction.makeLatticedShell  INFO: Pillars R, phi : 27, 18742.60875, 5.75959
    junotoptask:DetSimAlg.WaterPoolConstruction.makeLatticedShell  INFO: Pillars R, phi : 28, 18742.60875, 5.96903
    junotoptask:DetSimAlg.WaterPoolConstruction.makeLatticedShell  INFO: Pillars R, phi : 29, 18742.60875, 6.17847
    python: /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:705: void WaterPoolConstruction::makeLatticedShell(): Assertion `de' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffbe411a4a in WaterPoolConstruction::makeLatticedShell (this=0x6c01bf0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:705
    #5  0x00007fffbe40cab5 in WaterPoolConstruction::getLV (this=0x6c01bf0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:106
    #6  0x00007fffbe40b145 in BottomRockConstruction::inject (this=0x97b6e00, motherName="lPoolLining", other=0x6c01bf0, pos=0x0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/RockConstruction.cc:309
    #7  0x00007fffbe3bcf85 in LSExpDetectorConstruction::setupOuterWaterPool (this=0x95be4d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1685
    #8  0x00007fffbe3b1742 in LSExpDetectorConstruction::Construct (this=0x95be4d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:253
    #9  0x00007fffcc1a495e in G4RunManager::InitializeGeometry() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #10 0x00007fffcc1a4b2c in G4RunManager::Initialize() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #11 0x00007fffbdc4ab1b in DetSimAlg::initialize (this=0x6c00eb0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #12 0x00007fffcf84fb56 in DleSupervisor::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffcf8650fb in Task::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffcf86d4a7 in TopTask::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffcf8650a8 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fffcf91f943 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) ()
       from /home/blyth/junotop/sniper/InstallArea/python/Sniper/libSniperPython.so
    #17 0x00007fffcf80d5f5 in boost::python::objects::function::call(_object*, _object*) const () from /home/blyth/junotop/ExternalLibs/Boost/1.82.0/lib/libboost_python39.so.1.82.0
    #18 0x00007fffcf80d808 in boost::detail::function::void_function_ref_invoker0<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /home/blyth/junotop/ExternalLibs/Boost/1.82.0/lib/libboost_python39.so.1.82.0



::

    (gdb) list
    700     // =======================================================================
    701     // Pillars
    702     // =======================================================================
    703     for (PillarData* p = all_pillar_data; p->name!="END"; ++p) {
    704         IDetElement* de = dynamic_cast<IDetElement*>(detsimalg->findTool(p->name));
    705         assert(de);
    706 
    707         G4LogicalVolume* daughtervol = de->getLV();
    708         assert(daughtervol);
    709 
    (gdb) 


Need to change WaterPoolConstruction::

    -        assert(de);
    +        //assert(de);
    +        if(de == nullptr) continue ;  // SCB allow skipping pillar volumes at python level 
     



::

    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_radWP             : 21750.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_heightConcreteWP  : 44000.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_deadWaterThickness: 100.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_tyvekThickness    : 2.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_airGapThickness   : 500.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_digHoleRadius     : 536.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_outPillarR (TODO)    : 20200.00000
    junotoptask:DetSimAlg.WaterPoolConstruction.initVariables  INFO: Water Pool, m_innPillarR (TODO)    : 17000.00000


WIP : framespec targetting : why only default frame ? as didnt config it
---------------------------------------------------------------------------

::

    [blyth@localhost frame]$ l
    total 12
    4 -rw-rw-r--. 1 blyth blyth  16 Jun 14 16:02 NPFold_index.txt
    0 -rw-rw-r--. 1 blyth blyth   0 Jun 14 16:02 NPFold_names.txt
    4 -rw-rw-r--. 1 blyth blyth  40 Jun 14 16:02 MakeFromCE0_meta.txt
    4 -rw-rw-r--. 1 blyth blyth 512 Jun 14 16:02 MakeFromCE0.npy
    0 drwxr-xr-x. 2 blyth blyth 105 Jun 13 17:14 .
    0 drwxr-xr-x. 5 blyth blyth 143 Jun 13 17:14 ..
    [blyth@localhost frame]$ pwd
    /home/blyth/.opticks/GEOM/J_2024may20/CSGFoundry/SSim/scene/frame
    [blyth@localhost frame]$ 

::

    ]]stree::postcreate
    python: /home/blyth/opticks/sysrap/stree.h:1665: sfr stree::get_frame(const char*) const: Assertion `nd.repeat_ordinal == repeat_ordinal' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffc4fbdebb in stree::get_frame (this=0xaedadf0, q_spec=0x151e9670 "sDeadWater") at /home/blyth/opticks/sysrap/stree.h:1665
    #5  0x00007fffc4fc4a32 in SScene::addFrames (this=0xaedb4b0, path=0x7fffc50ac0b0 "$SScene__initFromTree_addFrames", st=0xaedadf0) at /home/blyth/opticks/sysrap/SScene.h:605
    #6  0x00007fffc4fc388d in SScene::initFromTree (this=0xaedb4b0, st=0xaedadf0) at /home/blyth/opticks/sysrap/SScene.h:161
    #7  0x00007fffc4fafdd7 in SSim::initSceneFromTree (this=0xaeda8b0) at /home/blyth/opticks/sysrap/SSim.cc:183
    #8  0x00007fffcd2d19f2 in G4CXOpticks::setGeometry (this=0xaeda6a0, world=0x97b0580) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:253
    #9  0x00007fffcd2d00d5 in G4CXOpticks::SetGeometry (world=0x97b0580) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:58
    #10 0x00007fffbe3dd3ef in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0x97b0580, sd=0x99470b0, ppd=0x6587710, psd=0x656c1a




    (gdb) f 4
    #4  0x00007fffc4fbdebb in stree::get_frame (this=0xaedadf0, q_spec=0x151e9670 "sDeadWater") at /home/blyth/opticks/sysrap/stree.h:1665
    1665        assert( nd.repeat_ordinal == repeat_ordinal ); 
    (gdb) p nd
    $1 = (const snode &) @0x7fffb7d5d010: {static NV = 15, index = 0, depth = 0, sibdex = -1, parent = -1, num_child = 2, first_child = 1, next_sibling = -1, lvid = 138, copyno = 0, sensor_id = -1, sensor_index = -1, repeat_index = 0, 
      repeat_ordinal = -1, boundary = 0, sensor_name = -1}
    (gdb) p nd.repeat_ordinal
    $2 = -1
    (gdb) p repeat_ordinal
    $3 = 0
    (gdb) 



DONE : MOI targetting needs to play nice with framespec ?
------------------------------------------------------------

Could add a key that jumps to the MOI frame





MULTIUNION_HOLES
--------------------

::

    118 jok-tds(){
    119    echo === $FUNCNAME  
    120    jok-init
    121 
    122 
    123    local ASIS=0              # no change : Opticks translation will assert with CSG tree height < MAX_TREE_DEPTH 
    124    local ZERO_HOLES=1        # adhoc just dont subtract the 30+30+1+1=62 holes : translation expected to succeed 
    125    local MULTIUNION_HOLES=2  # instead of subtracting the 62 holes one by one, collect into multiunion and subtract together
    126    local HIERARCHY=3         # NOT IMPLEMENTED
    127    export WaterPoolConstruction__CONFIG=$MULTIUNION_HOLES
    128    
    129    if [ "$WaterPoolConstruction__CONFIG" == "HIERARCHY" ]; then
    130        export ConfAcrylic__data_pillar_remove_bottom_angled_cross_piece=1
    131        export HBeamConstruction__try_init_model_pillar_shortleg_LSCALE=0.95
    132    fi  
    133    
    134    


    ]]stree::postcreate
    python: /home/blyth/opticks/sysrap/stree.h:1845: int stree::get_frame_remainder(sfr&, int, int, int) const: Assertion `ln == 0' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffc4fae115 in stree::get_frame_remainder (this=0xaf11270, f=..., lvid=19, lvid_ordinal=0, repeat_ordinal=-1) at /home/blyth/opticks/sysrap/stree.h:1845
    #5  0x00007fffc4fad973 in stree::get_frame (this=0xaf11270, q_spec=0x154b4fd0 "sDeadWater:0:-1") at /home/blyth/opticks/sysrap/stree.h:1718
    #6  0x00007fffc4fb5572 in SScene::addFrames (this=0xaf11940, path=0x7fffc509d368 "$SScene__initFromTree_addFrames", st=0xaf11270) at /home/blyth/opticks/sysrap/SScene.h:612
    #7  0x00007fffc4fb43cd in SScene::initFromTree (this=0xaf11940, st=0xaf11270) at /home/blyth/opticks/sysrap/SScene.h:161
    #8  0x00007fffc4f9fa2b in SSim::initSceneFromTree (this=0xaf10d30) at /home/blyth/opticks/sysrap/SSim.cc:183
    #9  0x00007fffcd2c8ab2 in G4CXOpticks::setGeometry (this=0xaf10c20, world=0x97b9cb0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:253
    #10 0x00007fffcd2c7195 in G4CXOpticks::SetGeometry (world=0x97b9cb0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:58
    #11 0x00007fffbe3cc49f in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0x97b9cb0, sd=0x9954320, ppd=0x65e2870, psd=0x65abee0, pmtscan=0x0)


    (gdb) f 4
    #4  0x00007fffc4fae115 in stree::get_frame_remainder (this=0xaf11270, f=..., lvid=19, lvid_ordinal=0, repeat_ordinal=-1) at /home/blyth/opticks/sysrap/stree.h:1845
    1845        assert( ln == 0 ); // simplify initial impl  : see CSGImport::importPrim 
    (gdb) list
    1840        std::vector<const sn*> lns ; 
    1841        sn::GetLVListnodes( lns, lvid );  
    1842        //int num_sub_total = sn::GetChildTotal( lns );  
    1843    
    1844        int ln = lns.size(); 
    1845        assert( ln == 0 ); // simplify initial impl  : see CSGImport::importPrim 
    1846    
    1847        std::ostream* out = nullptr ;
    1848        std::array<double,6> bb = {} ;
    1849    
    (gdb) 

    (gdb) p ln
    $1 = 1




Move this development from working copy into branch off current main 2024_jun14
--------------------------------------------------------------------------------

Before pull::


    [blyth@localhost junosw]$ git log -n1
    commit bbe66f02542211469a5cae78d90e492a8a1ae1fd (HEAD -> main, origin/main, origin/HEAD)
    Merge: 0f3add04 f8580d8e
    Author: Tao Lin <lintao@ihep.ac.cn>
    Date:   Mon May 20 02:55:40 2024 +0000

        Merge branch 'albert_waterpoolcxn_debug' into 'main'
        
        WaterPoolConstruction: add PMTSIM_STANDALONE for opticks testing
        
        See merge request JUNO/offline/junosw!420
    [blyth@localhost junosw]$ 


After pull::

    [blyth@localhost junosw]$ git l -n1
    commit 9febfa722a063d413aa8159fb206a750fbfbbc63 (HEAD -> main, origin/main, origin/HEAD)
    Merge: 6d39e851 621c2c2e
    Author: Tao Lin <lintao@ihep.ac.cn>
    Date:   Fri Jun 14 10:54:10 2024 +0000

        Merge branch 'zhangyp_oec_performance_check' into 'main'
        
        Zhangyp oec performance check
        
        See merge request JUNO/offline/junosw!451
    [blyth@localhost junosw]$ 


    [blyth@localhost ALL0]$ jo
    /home/blyth/junotop/junosw
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/CentralDetector/CMakeLists.txt
        modified:   Simulation/DetSimV2/CentralDetector/include/HBeamConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
        modified:   Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    [blyth@localhost junosw]$ 


Build::

    jo
    ./build_Debug.sh 


Web interface::

     https://code.ihep.ac.cn/JUNO/offline/junosw/-/branches


Create new branch from "main" using webinterface::

    jo 
    git fetch origin
    branch="blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation"

    git checkout -b $branch origin/$branch

::

    [blyth@localhost junosw]$ git fetch origin
    From code.ihep.ac.cn:JUNO/offline/junosw
     * [new branch]        blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation -> origin/blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation
    [blyth@localhost junosw]$ branch="blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation"
    [blyth@localhost junosw]$ git checkout -b $branch origin/$branch 
    M   Simulation/DetSimV2/CentralDetector/CMakeLists.txt
    M   Simulation/DetSimV2/CentralDetector/include/HBeamConstruction.hh
    M   Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc
    M   Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M   Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    M   Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    branch 'blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation' set up to track 'origin/blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation'.
    Switched to a new branch 'blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation'
    [blyth@localhost junosw]$ 
    [blyth@localhost junosw]$ 


    [blyth@localhost junosw]$ jo
    /home/blyth/junotop/junosw
    On branch blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation
    Your branch is up to date with 'origin/blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/CentralDetector/CMakeLists.txt
        modified:   Simulation/DetSimV2/CentralDetector/include/HBeamConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
        modified:   Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    [blyth@localhost junosw]$ 
    [blyth@localhost junosw]$ git push 
    Enumerating objects: 33, done.
    Counting objects: 100% (33/33), done.
    Delta compression using up to 48 threads
    Compressing objects: 100% (17/17), done.
    Writing objects: 100% (18/18), 10.24 KiB | 2.05 MiB/s, done.
    Total 18 (delta 11), reused 0 (delta 0), pack-reused 0
    remote: 
    remote: To create a merge request for blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw
       9febfa72..f8bd8cb2  blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation -> blyth-WaterPoolConstruction__CONFIG-to-fix-pillar-impingement-and-opticks-translation
    [blyth@localhost junosw]$ 






