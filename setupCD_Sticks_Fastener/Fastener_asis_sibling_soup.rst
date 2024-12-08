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


