Fastener_asis_sibling_soup
===========================

Links
--------


* this : ~/j/setupCD_Sticks_Fastener/Fastener_asis_sibling_soup.rst
* prior : ~/o/notes/issues/G4CXTest_GEOM_deviant_simple_history_TO_BT_BT_SA_at_1000_per_1M_level.rst

* this : https://github.com/simoncblyth/j/blob/main/setupCD_Sticks_Fastener/Fastener_asis_sibling_soup.rst
* prior : https://bitbucket.org/simoncblyth/opticks/src/master/notes/issues/G4CXTest_GEOM_deviant_simple_history_TO_BT_BT_SA_at_1000_per_1M_level.rst



Issue : Unexpected boundaries indicate borked hierarchy
--------------------------------------------------------------

:: 

    P[blyth@localhost issues]$ PICK=AB HSEL="TO BT BT SA" ~/o/G4CXTest_GEOM.sh ana 

    In [23]: np.c_[np.unique( ra[:,3,3,0].view(np.uint32) >> 16, return_counts=True )]
    Out[23]: 
    array([[   99, 14137],            ## Tyvek//CDInnerTyvekSurface/Water
           [  107,  3828],            ## Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lFasteners_phys//Steel
           [  108,  1857]])           ## Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lUpper_phys//Steel


    P[blyth@localhost tests]$ ~/o/bin/bd_names.sh | grep Water
    ...
    96   vetoWater/Implicit_RINDEX_NoRINDEX_pWaterPool_ZC2.A03_A03_HBeam_phys//LatticedShellSteel
    97   vetoWater/Implicit_RINDEX_NoRINDEX_pWaterPool_ZC2.A05_A05_HBeam_phys//LatticedShellSteel
    99   Tyvek//CDInnerTyvekSurface/Water
    100  Water///Acrylic
    104  Water/StrutAcrylicOpSurface//StrutSteel
    105  Water/Strut2AcrylicOpSurface//StrutSteel
    106  Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lSteel_phys//Steel
    107  Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lFasteners_phys//Steel
    108  Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lUpper_phys//Steel
    109  Water///PE_PA
    110  Water///Water
    111  Water///AcrylicMask
    112  Water/HamamatsuMaskOpticalSurface//CDReflectorSteel
    113  Water///Pyrex
    122  Water/NNVTMaskOpticalSurface//CDReflectorSteel
    130  Water/Implicit_RINDEX_NoRINDEX_PMT_3inch_log_phys_PMT_3inch_cntr_phys//Steel



lFasteners : Expected the Steel to be within Acrylic not Water
------------------------------------------------------------------

::

    P[blyth@localhost opticks]$ jgr lFasteners
    ./Doc/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + lFasteners_phys : 480
    ./Doc/oum/source/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + lFasteners_phys : 480
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:      "lFasteners",
    P[blyth@localhost junosw]$ 


::

    P[blyth@localhost junosw]$ jcv LSExpDetectorConstruction
    2 files to edit
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc



Review Fastener Geometry
----------------------------


FastenerAcrylicConstruction : Steel : "uni1" ring and 8 cylinders
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    142 void
    143 FastenerAcrylicConstruction::makeFastenerLogical() {
    ...
    182     G4VSolid* theSolid = muni == nullptr ?
    183                                   uni_Addition
    184                               :
    185                                   new G4UnionSolid( "uni1", IonRing, muni, 0, G4ThreeVector(0.,0.,0.) )
    186                               ;
    187 
    188 
    189       logicFasteners = new G4LogicalVolume(
    190       theSolid,
    191       Steel,
    192       "lFasteners",
    193       0,
    194       0,
    195       0);
    196 



    P[blyth@localhost junosw]$ jok-;BP=FastenerAcrylicConstruction::makeFastenerLogical jok-tds-gdb

    (gdb) bt
    #0  0x00007fffbe079310 in FastenerAcrylicConstruction::makeFastenerLogical()@plt () from /data/blyth/junotop/junosw/InstallArea/lib64/libCentralDetector.so
    #1  0x00007fffbe08a163 in FastenerAcrylicConstruction::getLV (this=0x9a081d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:52
    #2  0x00007fffbe08184f in DetSim1Construction::inject (this=0x6c04670, motherName="lWaterPool", other=0x9a081d0, pos=0x999d680)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:123
    #3  0x00007fffbe323ed9 in LSExpDetectorConstruction::setupAnchor (this=0x96ff650, anchor_name="FastenerAcrylic", anchor_mother_name="lWaterPool", 
        anchor_pos_file="/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv", cd_det=0x6c04670)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1467
    #4  0x00007fffbe323282 in LSExpDetectorConstruction::setupCD_Sticks (this=0x96ff650, cd_det=0x6c04670) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1403
    #5  0x00007fffbe31b97c in LSExpDetectorConstruction::setupCentralDetector (this=0x96ff650) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:589
    #6  0x00007fffbe31a261 in LSExpDetectorConstruction::Construct (this=0x96ff650) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:266
    #7  0x00007fffcc18795e in G4RunManager::InitializeGeometry() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007fffcc187b2c in G4RunManager::Initialize() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x00007fffbdab3b1b in DetSimAlg::initialize (this=0x6c040a0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #10 0x00007fffcf84fb56 in DleSupervisor::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffcf8650fb in Task::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffcf86d4a7 in TopTask::initialize() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffcf8650a8 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



    ) f 6
    #6  0x00007fffbe31a261 in LSExpDetectorConstruction::Construct (this=0x96ff650) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:266
    266           setupCentralDetector();
    (gdb) f 5
    #5  0x00007fffbe31b97c in LSExpDetectorConstruction::setupCentralDetector (this=0x96ff650) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:589
    589       setupCD_Sticks(cd_det);
    (gdb) f 4
    #4  0x00007fffbe323282 in LSExpDetectorConstruction::setupCD_Sticks (this=0x96ff650, cd_det=0x6c04670) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1403
    1403             setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);    

    (gdb) f 4
    #4  0x00007fffbe323282 in LSExpDetectorConstruction::setupCD_Sticks (this=0x96ff650, cd_det=0x6c04670) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1403
    1403             setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);    
    (gdb) p m_fastener_name
    $1 = "FastenerAcrylic"
    (gdb) p m_fastener_mother
    $2 = "lWaterPool"
    (gdb) p m_fastener_pos_file
    $3 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv"
    (gdb) 



    (gdb) list
    1398          G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-fa " << G4endl ; 
    1399      }
    1400      else
    1401      { 
    1402          if (m_fastener_name == "FastenerAcrylic") {
    1403             setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);    
    1404          } else if (m_fastener_name == "FastenerBalloon") {
    1405              // no fastener in Balloon Option
    1406          }
    1407      }
    (gdb) f 3
    #3  0x00007fffbe323ed9 in LSExpDetectorConstruction::setupAnchor (this=0x96ff650, anchor_name="FastenerAcrylic", anchor_mother_name="lWaterPool", 
        anchor_pos_file="/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv", cd_det=0x6c04670)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1467
    1467        bool anchor_det_status = cd_det->inject(anchor_mother_name, anchor_det, anchor_detelem_pos );
    (gdb) list
    1462        assert(anchor_det);
    1463        IDetElementPos* anchor_detelem_pos = nullptr;
    1464        G4double anchor_r = anchor_det->geom_info("PosR") ;  
    1465        anchor_detelem_pos = new JUNO::Ball::HexagonPosBall(anchor_pos_file,anchor_r,false);
    1466        assert (anchor_detelem_pos);
    1467        bool anchor_det_status = cd_det->inject(anchor_mother_name, anchor_det, anchor_detelem_pos );
    1468        assert(anchor_det_status);
    1469         
    1470        LogInfo<<"anchor_name = " << new_name <<"   "
    1471               <<"anchor_r =  "   << anchor_r <<" mm  "
    (gdb) f 2
    #2  0x00007fffbe08184f in DetSim1Construction::inject (this=0x6c04670, motherName="lWaterPool", other=0x9a081d0, pos=0x999d680)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:123
    123         daughtervol = other->getLV();
    (gdb) list
    118         LogInfo << "-> Get Hamamatsu R12860: " << pmt_elem_r12860 << std::endl;
    119         LogInfo << "-> Get NNVT MCPPMT: " << pmt_elem_nnvt << std::endl;
    120  
    121     } else {
    122 
    123         daughtervol = other->getLV();
    124 
    125         if (not daughtervol) {
    126             return false;
    127         }
    (gdb) f 1
    #1  0x00007fffbe08a163 in FastenerAcrylicConstruction::getLV (this=0x9a081d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:52
    52      makeFastenerLogical();
    (gdb) list
    47      if (logicFasteners) {
    48          return logicFasteners;
    49      }
    50      initMaterials();
    51  
    52      makeFastenerLogical();
    53  
    54      return logicFasteners;
    55  }
    56  
    (gdb) 





    1372 void
    1373 LSExpDetectorConstruction::setupCD_Sticks(IDetElement* cd_det) {
    1378   setupAnchor(m_strut_name  , m_strut_mother , m_strut_pos_file, cd_det);

    (gdb) p m_strut_name
    $4 = "StrutAcrylic"

    (gdb) p m_strut_mother
    $6 = "lWaterPool"


    (gdb) p m_strut_pos_file
    $11 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv"
    ## 370 theta,phi values 


    1383  if (m_strut_name == "StrutAcrylic"){
    1384      if(m_strut2_name == "StrutBar2Acrylic"){
    1385        setupAnchor(m_strut2_name  , m_strut_mother , m_strut2_pos_file, cd_det);
    1386      }
    1387 


    (gdb) p m_strut2_name
    $5 = "StrutBar2Acrylic"

    (gdb) p m_strut_mother
    $6 = "lWaterPool"

    (gdb) p m_strut2_pos_file
    $7 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv"
    ## 220 theta,phi values



    
    1388      if(m_strutballhead_name == "StrutBallheadAcrylic"){
    1389        setupAnchor(m_strutballhead_name , m_strut_mother , m_fastener_pos_file , cd_det);
    1390      }
    1402       if (m_fastener_name == "FastenerAcrylic") {
    1403          setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);
    1406       }
    1410   if (m_upper_name == "UpperAcrylic") {
    1411      setupAnchor(m_upper_name , m_upper_mother , m_fastener_pos_file , cd_det);
    1412   } 
    1416   if (m_addition_name == "AdditionAcrylic") {
    1417       setupAnchor(m_addition_name , m_addition_mother , m_fastener_pos_file , cd_det);
    1418 
    1419   } 



    (gdb) p m_fastener_pos_file
    $3 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv"
    ## 590 theta,phi values



    (gdb) p m_strutballhead_name
    $8 = "StrutBallheadAcrylic"

    (gdb) p m_fastener_name
    $1 = "FastenerAcrylic"

    (gdb) p m_upper_name
    $15 = "UpperAcrylic"

    (gdb) p m_addition_name
    $10 = "AdditionAcrylic"



    (gdb) p m_strut_mother
    $6 = "lWaterPool"

    (gdb) p m_fastener_mother
    $2 = "lWaterPool"

    (gdb) p m_upper_mother
    $13 = "lWaterPool"

    (gdb) p m_addition_mother
    $14 = "lWaterPool"






    1432   {
    1433       // XJ
    1434       setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    1435       setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    1436   }
    1437 
    1445   {
    1446       // SJ
    1447       setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);
    1448       setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);

    1449       setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    1450       setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);

    1451   }
    1454 
    1455 }



::

    1457 void LSExpDetectorConstruction::setupAnchor(std::string anchor_name , std::string anchor_mother_name,  std::string anchor_pos_file , IDetElement * cd_det){
    1458 
    1459     IDetElement* anchor_det = nullptr;
    1460     std::string new_name = anchor_name + "Construction";
    1461     anchor_det = det_elem(new_name);
    1462     assert(anchor_det);

    1463     IDetElementPos* anchor_detelem_pos = nullptr;
    1464     G4double anchor_r = anchor_det->geom_info("PosR") ;
    1465     anchor_detelem_pos = new JUNO::Ball::HexagonPosBall(anchor_pos_file,anchor_r,false);
    1466     assert (anchor_detelem_pos);

    1467     bool anchor_det_status = cd_det->inject(anchor_mother_name, anchor_det, anchor_detelem_pos );
    1468     assert(anchor_det_status);
    1469     
    1470     LogInfo<<"anchor_name = " << new_name <<"   "
    1471            <<"anchor_r =  "   << anchor_r <<" mm  "
    1472            <<"anchor_pos_file = "<<anchor_pos_file << std::endl;
    1473 
    1474 }

    1. get (IDetElement)anchor_det
    2. create (IDetElementPos)anchor_detelem_pos using the PosR from (IDetElement)anchor_det
    3. inject into cd_det both those 

    


Thinking how to implement LSExpDetectorConstruction::setupFastenerHierarchical
------------------------------------------------------------------------------------

::

    jcv DetSim1Construction





Review Current
---------------

Struts::

   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | Construction          |  Material        |  Solid            |   LV           | Geometry                  |
   +=======================+==================+===================+================+===========================+
   | StrutAcrylic          |   StrutSteel     |  sStrut           |  lSteel        | tube                      |
   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | StrutBar2Acrylic      |   StrutSteel     |  sStrut           |  lSteel2       | tube                      | 
   +-----------------------+------------------+-------------------+----------------+---------------------------+

   Due to duplicate sStrut named solids in geometry Opticks uniqued the names with _0 _1

   MOI=sStrut_0:0:-1 ~/o/cx.sh 
   MOI=sStrut_0:369:-1 ~/o/cx.sh 

   MOI=sStrut_1:0:-1 ~/o/cx.sh 
   MOI=sStrut_1:219:-1 ~/o/cx.sh 

   Note that 370+220 = 590 matching the fastener count. 

Q: How come 370 sStrut but 590 fasteners ? Every fastener needs a strut ?::

   (gdb) p m_strut_pos_file
   $11 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv"

   (gdb) p m_fastener_pos_file
   $3 = "/data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv"

   P[blyth@localhost data]$ wc -l *
      370 Strut_Acrylic.csv                 ##
      220 StrutBar2_Acrylic.csv             ## 
      590 Strut_Anchor_Acrylic.csv

A: Two sStrut Construction classes are used with two pos files : 220+370 = 590  


Fasteners::

   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | Construction          |  Material        |  Solid            |   LV           | Geometry                  |
   +=======================+==================+===================+================+===========================+
   | FastenerAcrylic       |   Steel          |  uni1             |  lFasteners    | Ring+8 screws *inside AA* |
   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | StrutBallheadAcrylic  |   Steel          |  sStrutBallhead   |  lSteel        | Orb                       | 
   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | UpperAcrylic          |   Steel          |  base_steel       |  lUpper        | Polycone 4rz              | 
   +-----------------------+------------------+-------------------+----------------+---------------------------+
   | AdditionAcrylic       |   Acrylic        |  uni_acrylic1     |  lAddition     | Polycone-BigSphere        | 
   +-----------------------+------------------+-------------------+----------------+---------------------------+


Currently 590 instances of these four are injected separately into cd_det. 
What I want to do is to inject 590 instances of one combo volume this combo volume 
could be a virtual water cylinder ? But this is not practical because of the shape.

So instead of doing that just focussing on fixing the bad hierarchy by injecting lFasteners into lAddition
Need a pos that offsets in R ? 

How does PMT do this ? NNVTMaskManager just hardcodes the PVPlacmenent within the inject 

    
Opticks viz commandlines for the 590 instances of each::

    MOI=uni1:0:0 ~/o/cx.sh
    MOI=uni1:0:589 ~/o/cx.sh

    MOI=sStrutBallhead:0:0 ~/o/cx.sh
    MOI=sStrutBallhead:0:589 ~/o/cx.sh

    MOI=base_steel:0:0 ~/o/cx.sh
    MOI=base_steel:0:589 ~/o/cx.sh

    MOI=uni_acrylic1:0:0 ~/o/cx.sh
    MOI=uni_acrylic1:0:589 ~/o/cx.sh





After cleanup Sticks/Fastener impl
--------------------------------------

::

    junotoptask:DetSimAlg.StrutAcrylicConstruction.initVariables  INFO: Option RealSurface is enabled in Central Detector.  Reduce m_lengthStrut from 1807.60000 to: 1548.05399
    m_radStrut = 42.5
    Total Number of lSteel in CD is 370
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutAcrylic   anchor_r =  18854.92700 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv
    junotoptask:DetSimAlg.StrutBar2AcrylicConstruction.initVariables  INFO: Option RealSurface is enabled in Central Detector.  Reduce m_lengthStrut from 1913.60000 to: 1548.07707
    m_radStrut = 30
    Total Number of lSteel2 in CD is 220
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutBar2Acrylic   anchor_r =  18854.93854 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv
    in det_elemStrutBallheadAcrylicConstruction not found. Try to create it.
    m_rad = 50
    Total Number of lSteel in CD is 590
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutBallheadAcrylic   anchor_r =  18030.90000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    in det_elemFastenerAcrylicConstruction not found. Try to create it.
    Total Number of lFasteners in CD is 590
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = FastenerAcrylic   anchor_r =  17844.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    in det_elemUpperAcrylicConstruction not found. Try to create it.
    Total Number of lUpper in CD is 590
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = UpperAcrylic   anchor_r =  17964.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    in det_elemAdditionAcrylicConstruction not found. Try to create it.
    Total Number of lAddition in CD is 590
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = AdditionAcrylic   anchor_r =  17824.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    in det_elemSJCLSanchorConstruction not found. Try to create it.
    Total Number of lSJCLSanchor in CD is 2
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJCLSanchor   anchor_r =  17694.89800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv
    in det_elemSJFixtureConstruction not found. Try to create it.
    Total Number of lSJFixture in CD is 36
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJFixture   anchor_r =  17694.98200 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv
    in det_elemSJReceiverConstruction not found. Try to create it.
    Total Number of lSJReceiver in CD is 8
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJReceiver   anchor_r =  17694.89800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv
    in det_elemSJReceiverFasternConstruction not found. Try to create it.
    Total Number of lSJReceiverFastern in CD is 8
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJReceiverFastern   anchor_r =  17683.39800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv
    in det_elemXJanchorConstruction not found. Try to create it.
    use simplify xj anchor
    Total Number of lXJanchor in CD is 56
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = XJanchor   anchor_r =  17829.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv
    in det_elemXJfixtureConstruction not found. Try to create it.




::

    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutAcrylic         anchor_r =  18854.92700 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutBar2Acrylic     anchor_r =  18854.93854 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv

    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = StrutBallheadAcrylic anchor_r =  18030.90000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = FastenerAcrylic      anchor_r =  17844.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = UpperAcrylic         anchor_r =  17964.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = AdditionAcrylic      anchor_r =  17824.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv

    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJCLSanchor          anchor_r =  17694.89800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJFixture            anchor_r =  17694.98200 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJReceiver           anchor_r =  17694.89800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = SJReceiverFastern    anchor_r =  17683.39800 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv
    SNiPER:Unknown.setupAnchorPosition  INFO: anchor_name = XJanchor             anchor_r =  17829.00000 mm  anchor_pos_file = /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv


::

     07 class IDetElementPos {
      8 public:
      9     virtual G4bool hasNext()=0;
     10     virtual G4Transform3D next()=0;
     11     virtual ~IDetElementPos(){}
     12 };



Changes
-----------


::

    P[blyth@localhost junosw]$ jo
    /home/blyth/junotop/junosw
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
            ## add CONFIG enabling Opticks translation to listnode 
            ## without adopting G4MultiUnion in source geometry 

        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
            ## rationalize LSExpDetectorConstruction::setupCD_Sticks implementation
            ## ADD CONFIG to inject Fastener into AdditionAcrylic fixing hierarchy 

        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
            ## reposition high level setup into G4CXOpticks::SetGeometry_JUNO for ease of updating

        modified:   Simulation/GenTools/src/GtOpticksTool.cc       
        modified:   Simulation/GenTools/src/GtOpticksTool.h        
            ## remove input_photon configure check : thats too early for current Opticks

        modified:   Simulation/SimSvc/MultiFilmLUTMakerSvc/src/MultiFilmLUTMakerSvc.cc   
            ## reduce verbosity

    Untracked files:
      (use "git add <file>..." to include in what will be committed)
        Simulation/DetSimV2/SimUtil/include/AdditionAcrylic_FastenerPos.hh
        Simulation/DetSimV2/SimUtil/src/AdditionAcrylic_FastenerPos.cc



With HIERARCHY configured
----------------------------

With::



    164    local AAF_ASIS=0
    165    local AAF_HIERARCHY=1
    166    export LSExpDetectorConstruction__setupCD_Sticks_Fastener_CONFIG=$AAF_HIERARCHY



* geometry looks the same with ~/o/cx.sh
* boundaries have changed::

    P[blyth@localhost junosw]$ ~/o/bin/bd_names.sh | head -120 

    98   Air/CDTyvekSurface//Tyvek
    99   Tyvek//CDInnerTyvekSurface/Water
    100  Water///Acrylic
    101  Acrylic///LS
    102  LS///Acrylic
    103  LS///PE_PA
    104  Water/StrutAcrylicOpSurface//StrutSteel
    105  Water/Strut2AcrylicOpSurface//StrutSteel
    106  Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lSteel_phys//Steel
    107  Water/Implicit_RINDEX_NoRINDEX_pInnerWater_lUpper_phys//Steel
    108  Acrylic/Implicit_RINDEX_NoRINDEX_lAddition_phys_lFasteners_phys//Steel
    109  Water///PE_PA
    110  Water///Water
    111  Water///AcrylicMask
    112  Water/HamamatsuMaskOpticalSurface//CDReflectorSteel
    113  Water///Pyrex
    114  Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    115  Vacuum/HamamatsuR12860_PMT_20inch_dynode_plate_opsurface//Steel




Changes so far
-----------------

::

    P[blyth@localhost junosw]$ jo
    /home/blyth/junotop/junosw
    # On branch main
    # Changes not staged for commit:
    #   (use "git add <file>..." to update what will be committed)
    #   (use "git checkout -- <file>..." to discard changes in working directory)
    #
    #   modified:   Simulation/DetSimV2/CentralDetector/include/AdditionAcrylicConstruction.hh
    #   modified:   Simulation/DetSimV2/CentralDetector/src/AdditionAcrylicConstruction.cc
    #   modified:   Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
    #   modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    #   modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    #   modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    #   modified:   Simulation/GenTools/src/GtOpticksTool.cc
    #   modified:   Simulation/GenTools/src/GtOpticksTool.h
    #   modified:   Simulation/SimSvc/MultiFilmLUTMakerSvc/src/MultiFilmLUTMakerSvc.cc
    #
    # Untracked files:
    #   (use "git add <file>..." to include in what will be committed)
    #
    #   Simulation/DetSimV2/SimUtil/include/OnePosition.hh
    #   Simulation/DetSimV2/SimUtil/src/OnePosition.cc
    no changes added to commit (use "git add" and/or "git commit -a")
    P[blyth@localhost junosw]$ 



Ziyan now requests Water cylinders too  
------------------------------------------

So need::

   FastenerWater volume : 
   (delta enlarged outwards and inwards for annulus) 

   FastenerSteel volume

   inject FastenerSteel volume into FastenerWater with no position offset 
        
   inject FastenerWater into AdditionAcrylic (position offset-delta)




::



          
                           +---------------------------------------+
                          /                                         \ 
                         /                                           \ 
                        /    +------+                                 \
                       /     | +--+ |                                  \  
                      /      | |St|W|                                   \ 
                     /       | |  | |                                    \  
                    /        | +--+ |                                     \      
                   /         +------+                                      \ 
                  /                                                         \   
                 /                                       Acrylic             \                         
                /  +-------------------------------------------------+        \
               /   | +---------------------------------------------+ |         \
              /    | |                           Steel             |W|          \
             /     | +---------------------------------------------+ |           \ 
            /      +-------------------------------------------------+            \
           /                                                                       \
          +-------------------------------------------------------------------------+



Better to reuse the code changing param delta+material, 
perhaps via det_elem nobj mechanism
Seems nobj not designed for that. But still need to use it
to create separate instances of "FastenerConstruction" ?
By looking for non-existing tools called the string after slash::

    // the nobj is needed to create 
    IDetElement* fac_water_ = det_elem("FastenerConstruction/FastenerConstruction_Water") ; 
    FastenerConstruction* fac_water = dynamic_case<FastenerConstruction*>(fac_water_); 

    IDetElement* fac_steel_ = det_elem("FastenerConstruction/FastenerConstruction_Steel") ;
    FastenerConstruction* fac_steel = dynamic_case<FastenerConstruction*>(fac_steel_); 
 

::

    1117 IDetElement*
    1118 LSExpDetectorConstruction::det_elem(const std::string& name) {
    1119     SniperPtr<DetSimAlg> detsimalg(*m_scope, "DetSimAlg");
    1120     if (detsimalg.invalid()) {
    1121         std::cout << "Can't Load DetSimAlg" << std::endl;
    1122         assert(0);
    1123     }
    1124 
    1125     // get type/nobj
    1126     std::string type = name;
    1127     std::string nobj = name;
    1128     std::string::size_type pseg = name.find('/');
    1129     if ( pseg != std::string::npos ) {
    1130         type = type.substr(0, pseg);
    1131         nobj = nobj.substr(pseg+1, std::string::npos);
    1132     }
    1133 
    1134     ToolBase* t = 0;
    1135     // find the tool first
    1136     // create the tool if not exist
    1137     t = detsimalg->findTool(nobj);
    1138     if (not t) {
    1139         std::cout <<"in det_elem"<< name << " not found. Try to create it." << std::endl;
    1140         t = detsimalg->createTool(name);
    1141     }
    1142 
    1143     return dynamic_cast<IDetElement*>(t);
    1144 }





Need to instanciate and cast then change param then. 

::

     23 #ifdef PMTSIM_STANDALONE
     24 #include "PMTSIM_API_EXPORT.hh"
     25 class FastenerAcrylicConstruction : public IGeomManager {
     26 #else
     27 class FastenerAcrylicConstruction : public IDetElement,
     28                             public ToolBase{
     29 #endif




::

    1630 IDetElement* LSExpDetectorConstruction::setupAnchorElement(std::string& anchor_name)
    1631 {
    1632     std::string de_name = anchor_name + "Construction";
    1633     IDetElement* de = det_elem(de_name);
    1634     return de ;
    1635 }



FIXED : Shakedown : dud material ? 
------------------------------------


::

    024-11-25 14:37:29.995 INFO  [455020] [LSExpDetectorConstruction_Opticks::Setup@44] [ WITH_G4CXOPTICKS opticksMode 3 sd 0x9af00a0
    ssys::getenvvar.is_path_prefixed  path $HOME/.opticks/GEOM/${GEOM}_meshname_stree__force_triangulate_solid.txt
    2024-11-25 14:37:29.996 INFO  [455020] [G4CXOpticks::SetGeometry_JUNO@89] [ WITH_G4CXOPTICKS opticksMode 3 sd 0x9af00a0
    2024-11-25 14:37:29.996 INFO  [455020] [U4Tree::Create@214] [new U4Tree
    2024-11-25 14:37:29.997 INFO  [455020] [U4Tree::init@270] -initRayleigh
    2024-11-25 14:37:29.997 INFO  [455020] [U4Tree::init@272] -initMaterials

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffcd2e0a68 in G4Material::GetIndex (this=0xc0c8c7bb7202b7f1) at /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4Material.hh:262
    262   inline size_t GetIndex() const {return fIndexInTable;}
    (gdb) bt
    #0  0x00007fffcd2e0a68 in G4Material::GetIndex (this=0xc0c8c7bb7202b7f1) at /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4Material.hh:262
    #1  0x00007fffcd30f661 in U4Tree::initMaterial (this=0xb013ae0, mt=0xc0c8c7bb7202b7f1) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:444
    #2  0x00007fffcd30f5d6 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x9a46d50) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:428
    #3  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x9a46ec0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #4  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x9a470d0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #5  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x9993340) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #6  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x99934f0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #7  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x992f300) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #8  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x98fce00) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #9  0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x98fce60) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #10 0x00007fffcd30f333 in U4Tree::initMaterials_r (this=0xb013ae0, pv=0x98e9ed0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:411
    #11 0x00007fffcd30edd2 in U4Tree::initMaterials (this=0xb013ae0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:322
    #12 0x00007fffcd30e67b in U4Tree::init (this=0xb013ae0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:273
    #13 0x00007fffcd30e46d in U4Tree::U4Tree (this=0xb013ae0, st_=0xb03af30, top_=0x98e9ed0, sid_=0x0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:257
    #14 0x00007fffcd30d9dc in U4Tree::Create (st=0xb03af30, top=0x98e9ed0, sid=0x0) at /data/blyth/opticks_Debug/include/U4/U4Tree.h:215
    #15 0x00007fffcd2c21cc in G4CXOpticks::setGeometry (this=0xb03a930, world=0x98e9ed0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:311


::

    NP::save failed to U::Resolve path_ $MultiFilmLUTMakerSvc_DIR/multifilm.npy
    2024-11-25 15:00:17.897 INFO  [51283] [LSExpDetectorConstruction_Opticks::Setup@44] [ WITH_G4CXOPTICKS opticksMode 3 sd 0x9af03b0
    ssys::getenvvar.is_path_prefixed  path $HOME/.opticks/GEOM/${GEOM}_meshname_stree__force_triangulate_solid.txt
    2024-11-25 15:00:17.899 INFO  [51283] [G4CXOpticks::SetGeometry_JUNO@89] [ WITH_G4CXOPTICKS opticksMode 3 sd 0x9af03b0
    2024-11-25 15:00:17.899 INFO  [51283] [U4Tree::Create@216] [new U4Tree
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::init@273] -initRayleigh
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::init@275] -initMaterials
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials@325] [
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pDomeAir lv lDomeAir num_child 0 mt Air
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pDomeRock lv lDomeRock num_child 1 mt Rock
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pDomeRockBox lv lDomeRockBox num_child 1 mt Galactic
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pPoolCover lv lPoolCover num_child 0 mt Steel
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pUpperChimneyLS lv lUpperChimneyLS num_child 0 mt LS
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pUpperChimneyTyvek lv lUpperChimneyTyvek num_child 0 mt Tyvek
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pBar lv lBar num_child 0 mt Scintillator
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pCoating_00_ lv lCoating num_child 1 mt TiO2Coating
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pPanelTape lv lPanelTape num_child 64 mt Adhesive
    2024-11-25 15:00:17.900 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pPanel_0_f_ lv lPanel num_child 1 mt Aluminium
    2024-11-25 15:00:17.907 INFO  [51283] [U4Tree::initMaterials_r@440]  pv GLw1.up10_up11_HBeam_phys lv GLw1.up10_up11_HBeam num_child 0 mt LatticedShellSteel
    2024-11-25 15:00:17.908 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pWaterPool lv lOuterWaterPool num_child 2090 mt vetoWater
    2024-11-25 15:00:17.908 INFO  [51283] [U4Tree::initMaterials_r@440]  pv pDeadWater lv lDeadWater num_child 1 mt DeadWater
    2024-11-25 15:00:17.908 INFO  [51283] [U4Tree::initMaterials_r@440]  pv lSJCLSanchor_phys lv lSJCLSanchor num_child 0 mt Acrylic
    2024-11-25 15:00:17.908 INFO  [51283] [U4Tree::initMaterials_r@440]  pv lSJReceiverFastern_phys lv lSJReceiverFastern num_child 0 mt PE_PA
    2024-11-25 15:00:17.908 INFO  [51283] [U4Tree::initMaterials_r@440]  pv lSteel_phys lv lSteel num_child 0 mt StrutSteel

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffef9f07a8 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string (this=0x7ffffffed040, __str=<error reading variable: Cannot access memory at address 0xc0c8c7bb7202b801>) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/download/gcc-11.2.0.build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/basic_string.h:459
    459 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/download/gcc-11.2.0.build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/basic_string.h: No such file or directory.
    (gdb) 


    2024-11-25 15:15:15.961 INFO  [100352] [U4Tree::initMaterials_r@446]  pv lSJReceiverFastern_phys lv lSJReceiverFastern num_child 0 mt PE_PA
    2024-11-25 15:15:15.961 INFO  [100352] [U4Tree::initMaterials_r@440]  pv lSteel_phys lv lSteel num_child 0
    2024-11-25 15:15:15.961 INFO  [100352] [U4Tree::initMaterials_r@446]  pv lSteel_phys lv lSteel num_child 0 mt StrutSteel
    2024-11-25 15:15:15.962 INFO  [100352] [U4Tree::initMaterials_r@440]  pv lFasteners_phys lv lFasteners num_child 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffef9f07a8 in std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string (this=0x7ffffffebe40, __str=<error reading variable: Cannot access memory at address 0xc0c8c7bb7202b801>) at /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/download/gcc-11.2.0.build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/basic_string.h:459
    459 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/download/gcc-11.2.0.build/x86_64-pc-linux-gnu/libstdc++-v3/include/bits/basic_string.h: No such file or directory.
    (gdb) 


Ordering?::

    AdditionAcrylicConstruction::initVariables m_radAcrylic 17824 rdelta_mm 0 m_rdelta 0 [AdditionAcrylicConstruction__rdelta_mm]  m_addition_pos 17824
    in det_elemFastenerConstruction/FastenerConstruction_Water not found. Try to create it.
    in det_elemFastenerConstruction/FastenerConstruction_Steel not found. Try to create it.
    FastenerConstruction::setMaterial  Steel:0xc0c0d703ec7a019d Water:0xc0c508eba41b31a3 theMaterial:0xc0c508eba41b31a3 name:Water 
    FastenerConstruction::setMaterial  Steel:0xc0c8c7bb7202b7f1 Water:0x9985ac0 theMaterial:0xc0c8c7bb7202b7f1 name:Steel 
    FastenerConstruction::initMaterials  Steel:0x989c7e0 Water:0x98ddfb0 
    FastenerConstruction::makeFastenerLogical  Steel:0x989c7e0 Water:0x98ddfb0 theMaterial:0xc0c508eba41b31a3 lvname:lFasteners 
    FastenerConstruction::initMaterials  Steel:0x989c7e0 Water:0x98ddfb0 
    FastenerConstruction::makeFastenerLogical  Steel:0x989c7e0 Water:0x98ddfb0 theMaterial:0xc0c8c7bb7202b7f1 lvname:lFasteners 
    LSExpDetectorConstruction::setupCD_Sticks_Fastener_Hierarchy  addition_PosR 17824 f_PosR 17844 f_dR 20 addition_lv YES f_water_lv YES f_steel_lv YES
    FastenerConstruction::inject daughtervol.Name :lFasteners
    FastenerConstruction::inject copyno = 1


FIXED by simplify the impl (removing the cached materials) and using setMaterialName.




WIP : remove --additionacrylic-simplify-csg option (making standard) plus make fastener heirarchy standard 
--------------------------------------------------------------------------------------------------------------

The "--additionacrylic-simplify-csg" is python SWITCH option that gets converted into 
internal envvar JUNO_ADDITIONACRYLIC_SIMPLIFY_CSG 

jcv JUNODetSimModule::

    1959     --additionacrylic-simplify-csg 
    1960         Simplify CSG modelling avoiding CSG subtraction for daughters, see AdditionAcrylicConstruction
    1961 

::

    P[blyth@localhost issues]$ jgr additionacrylic_simplify_csg
    P[blyth@localhost junosw]$ jgr JUNO_ADDITIONACRYLIC_SIMPLIFY_CSG 
    ./Simulation/DetSimV2/CentralDetector/src/AdditionAcrylicConstruction.cc:    m_simplify_csg = getenv("JUNO_ADDITIONACRYLIC_SIMPLIFY_CSG") == nullptr ? false : true ; 
    P[blyth@localhost junosw]$ 


jcv AdditionAcrylicConstruction::

    129    } else if (option=="simple") {
    130 
    131         double ZNodes3[3];
    132         double RminNodes3[3];
    133         double RmaxNodes3[3];
    134         ZNodes3[0] = 5.7*mm; RminNodes3[0] = 0*mm; RmaxNodes3[0] = 450.*mm;
    135         ZNodes3[1] = 0.0*mm; RminNodes3[1] = 0*mm; RmaxNodes3[1] = 450.*mm;
    136         ZNodes3[2] = -140.0*mm; RminNodes3[2] = 0*mm; RmaxNodes3[2] = 200.*mm;
    137 
    138         solidAddition_down = new G4Polycone("solidAddition_down",0.0*deg,360.0*deg,3,ZNodes3,RminNodes3,RmaxNodes3);
    139 
    140     }
    141 
    142 
    143 //    solidAddition_down = new G4Tubs("solidAddition_down",0,199.67*mm,140*mm,0.0*deg,360.0*deg);
    144 //    solidAddition_down = new G4Cons("solidAddition_down",0.*mm,450.*mm,0.*mm,200*mm,70.*mm,0.*deg,360.*deg);
    145     solidAddition_up = new G4Sphere("solidAddition_up",0*mm,m_radAcrylic,0.0*deg,360.0*deg,0.0*deg,180.*deg);
    146 
    147     uni_acrylic1 = new G4SubtractionSolid("uni_acrylic1",solidAddition_down,solidAddition_up,0,G4ThreeVector(0*mm,0*mm,+m_radAcrylic));
    148 
    149     solidAddition_up1 = new G4Tubs("solidAddition_up1",120*mm,208*mm,15.2*mm,0.0*deg,360.0*deg);
    150     uni_acrylic2 = new G4SubtractionSolid("uni_acrylic2",uni_acrylic1,solidAddition_up1,0,G4ThreeVector(0.*mm,0.*mm,-20*mm));
    151     solidAddition_up2 = new G4Tubs("solidAddition_up2",0,14*mm,52.5*mm,0.0*deg,360.0*deg);
    152 
    153     for(int i=0;i<8;i++)
    154     {
    155     uni_acrylic3 = new G4SubtractionSolid("uni_acrylic3",uni_acrylic2,solidAddition_up2,0,G4ThreeVector(164.*cos(i*pi/4)*mm,164.*sin(i*pi/4)*mm,-87.5));
    156     uni_acrylic2 = uni_acrylic3;
    157 
    158     }
    159 
    160 
    161     G4VSolid* solid = m_simplify_csg == false ? uni_acrylic2 : uni_acrylic1 ;


* HMM : THIS MEANS USING HEIRARCY FOR THE FastenerConstruction NEEDS TO FORCE USING --additionacrylic-simplify-csg to not subtract the voids 
* best way is to remove the option and hardcode the simplify-csg 


jump to new GEOM J_2024nov27
-------------------------------- 

Note that need some setup to do the triangulation::

    cp J_2024nov27/CSGFoundry/meshname.txt J_2024nov27_meshname_stree__force_triangulate_solid.txt

Tried triangulating everything, but that dont work::

    2024-11-27 16:51:22.439 INFO  [106291] [U4Tree::Create@218] ]new U4Tree
    2024-11-27 16:51:22.439 INFO  [106291] [U4Tree::Create@220] [stree::factorize
    python: /data/blyth/opticks_Debug/include/SysRap/stree.h:3774: void stree::collectGlobalNodes(): Assertion `do_force_triangulate == false && "force triangulate solid is currently only supported for remainder nodes"' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) 

     
Vim edits::

   :0,$s/^/#/g              # on all lines
   :138,293s/^#//g          # remove the # from the guidetube torus lines 
                            # plus manually remove the # for the XJ and SJ solids

::

    P[blyth@localhost GEOM]$ vimdiff J_2024aug27_meshname_stree__force_triangulate_solid.txt J_2024nov27_meshname_stree__force_triangulate_solid.txt


Also framespec bookmarks::

    P[blyth@localhost GEOM]$ cp J_2024aug27_framespec.txt J_2024nov27_framespec.txt  




create new branch : blyth-hierarchical-sticks-fastener-geometry-with-thin-water
---------------------------------------------------------------------------------

switch to the web interface created branch::

    git pull 
    git fetch 

    P[blyth@localhost junosw]$ git switch blyth-hierarchical-sticks-fastener-geometry-with-thin-water
    M   Simulation/DetSimV2/CentralDetector/include/AdditionAcrylicConstruction.hh
    M   Simulation/DetSimV2/CentralDetector/src/AdditionAcrylicConstruction.cc
    M   Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
    M   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    M   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    M   Simulation/GenTools/src/GtOpticksTool.cc
    M   Simulation/GenTools/src/GtOpticksTool.h
    M   Simulation/SimSvc/MultiFilmLUTMakerSvc/src/MultiFilmLUTMakerSvc.cc
    branch 'blyth-hierarchical-sticks-fastener-geometry-with-thin-water' set up to track 'origin/blyth-hierarchical-sticks-fastener-geometry-with-thin-water'.
    Switched to a new branch 'blyth-hierarchical-sticks-fastener-geometry-with-thin-water'
    P[blyth@localhost junosw]$ 



TODO : chi2 check from center ? G4CXTest_GEOM.sh  already doing that
-----------------------------------------------------------------------

::

    ~/o/G4CXTest_GEOM.sh 
    ~/o/G4CXTest_GEOM.sh chi2




TODO : Create MR
------------------

::

    remote: To create a merge request for blyth-hierarchical-sticks-fastener-geometry-with-thin-water, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-hierarchical-sticks-fastener-geometry-with-thin-water





