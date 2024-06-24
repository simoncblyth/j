remaining-geometry-diffs
============================


jok-tds::

    174    NOXJ=${NOXJ:-1}
    175    case $NOXJ in
    176       0) opts="$opts" ;;
    177       1) opts="$opts --debug-disable-xj" ;;
    178    esac
    179 
    180    NOSJ=${NOSJ:-1}
    181    case $NOSJ in
    182       0) opts="$opts" ;;
    183       1) opts="$opts --debug-disable-sj" ;;
    184    esac
    185 
    186    NOFA=${NOFA:-1}
    187    case $NOFA in
    188       0) opts="$opts" ;;
    189       1) opts="$opts --debug-disable-fa" ;;
    190    esac


JUNODetSimModule::


    2067     --additionacrylic-simplify-csg 
    2068         Simplify CSG modelling avoiding CSG subtraction for daughters, see AdditionAcrylicConstruction

    2081     --debug-disable-xj
    2082         USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCD_Sticks
    2083 
    2084     --debug-disable-sj
    2085         USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCD_Sticks : typically disables solidSJReceiverFastern
    2086 
    2087     --debug-disable-fa
    2088         USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCD_Sticks : typically disables FastenerAcrylic uni1



::

    [blyth@localhost junosw]$ jgr JUNO_DEBUG_
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  bool debug_disable_sticks = getenv("JUNO_DEBUG_DISABLE_STICKS") == nullptr ? false : true ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  bool DEBUG_DISABLE_FA = getenv("JUNO_DEBUG_DISABLE_FA") == nullptr ? false : true ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  bool DEBUG_DISABLE_XJ = getenv("JUNO_DEBUG_DISABLE_XJ") == nullptr ? false : true ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  bool DEBUG_DISABLE_SJ = getenv("JUNO_DEBUG_DISABLE_SJ") == nullptr ? false : true ; 
    [blyth@localhost junosw]$ 



no-guide_tube
--------------

additionacrylic-simplify-csg
-------------------------------


debug-disable-xj
-----------------

jcv LSExpDetectorConstruction::

    1415   bool DEBUG_DISABLE_XJ = getenv("JUNO_DEBUG_DISABLE_XJ") == nullptr ? false : true ;
    1416   if(DEBUG_DISABLE_XJ)
    1417   {
    1418       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-xj " << G4endl ;
    1419   }
    1420   else
    1421   {
    1422       // XJ
    1423       setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    1424       setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    1425   }

     152   m_xjanchor_name = "XJanchor";
     153   m_xjfixture_name = "XJfixture";

    [blyth@localhost data]$ wc -l *.csv
       56 XJanchor.csv


    jcv XJanchorConstruction
    jcv XJfixtureConstruction



debug-disable-sj
-----------------


jcv LSExpDetectorConstruction::

    1428   bool DEBUG_DISABLE_SJ = getenv("JUNO_DEBUG_DISABLE_SJ") == nullptr ? false : true ;
    1429   if(DEBUG_DISABLE_SJ)
    1430   {
    1431       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-sj " << G4endl ;
    1432   }
    1433   else
    1434   {
    1435       // SJ
    1436       setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);

    1437       setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);

    1438       setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);

    1439       setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);

    1440   }


    0154   m_sjclsanchor_name = "SJCLSanchor";
     155   m_sjfixture_name = "SJFixture";
     156   m_sjreceiver_name = "SJReceiver";
     157   m_sjreceiver_fastener_name = "SJReceiverFastern";
     158   m_pmt_mother = "lWaterPool";
     159   m_mask_mother = "lMaskVirtual";



    [blyth@localhost data]$ wc -l *.csv
        2 SJCLSanchor.csv
       36 SJFixturePos.csv
        8 SJReceiverPos.csv
        8 SJReceiverPos.csv

       39 Guide_Tube.csv
      370 Strut_Acrylic.csv
      590 Strut_Anchor_Acrylic.csv
      220 StrutBar2_Acrylic.csv
       56 XJanchor.csv
     1321 total
    [blyth@localhost data]$ 


    jcv SJCLSanchorConstruction
    jcv SJFixtureConstruction
    jcv SJReceiverConstruction
    jcv SJReceiverFasternConstruction 





debug-disable-fa : 590 FastenerAcrylicConstruction IonRing and 8 screws
---------------------------------------------------------------------------

jcv LSExpDetectorConstruction::

    1384   bool DEBUG_DISABLE_FA = getenv("JUNO_DEBUG_DISABLE_FA") == nullptr ? false : true ;
    1385   if(DEBUG_DISABLE_FA)
    1386   {
    1387       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-fa " << G4endl ;
    1388   }
    1389   else
    1390   {
    1391       if (m_fastener_name == "FastenerAcrylic") {
    1392          setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);
    1393       } else if (m_fastener_name == "FastenerBalloon") {
    1394           // no fastener in Balloon Option
    1395       }
    1396   }


::

    [blyth@localhost junosw]$ jgr setFastenerPosFile
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    dc->setFastenerPosFile(m_fastener_pos_file);
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     void setFastenerPosFile(const std::string& pos_file) {m_fastener_pos_file=pos_file;}
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    dc->setFastenerPosFile(m_fastener_pos_file);
    [blyth@localhost junosw]$ 










Finding PosFiles
------------------

::

    033 DetSim0Svc::DetSim0Svc(const std::string& name)
     34     : SvcBase(name)
     35 {
     36     declProp("AnaMgrList", m_ana_list);
     37     declProp("CDName", m_cd_name="DetSim1");
     38     declProp("PMTName", m_pmt_name="PMTMask");
     39     declProp("LPMTExtra", m_extra_lpmt="ONE"); // ONE or TWO
     40     declProp("3inchPMTName", m_3inchpmt_name="Tub3inchV3");
     41     // NOTE: to do the elec simulation, please scale the QE
     42     declProp("ElecSimPMTQEScale", m_pmt_qe_scale_for_elec=1.0);
     43     declProp("StrutName", m_strut_name="StrutAcrylic");
     44     declProp("FastenerName", m_fastener_name="FastenerAcrylic");
     45     declProp("PMTMother", m_pmt_mother="lWaterPool");
     46     declProp("StrutMother", m_strut_mother="lWaterPool");
     47     declProp("FastenerMother", m_fastener_mother="lWaterPool");
     48     declProp("PMTPosMode", m_pmt_pos_mode="FileMode");
     49 
     50     declProp("3inchPMTPosFile", m_3inch_pmt_pos_file);
     51     declProp("3inchPMTPosOffset", m_3inch_pmt_pos_offset=-50.0);
     52     declProp("StrutPosFile", m_strut_pos_file);
     53     declProp("Strut2PosFile", m_strut2_pos_file);
     54     declProp("FastenerPosFile", m_fastener_pos_file);
     55     declProp("XJanchorPosFile", m_xjanchor_pos_file);
     56     declProp("SJCLSanchorPosFile", m_sjclsanchor_pos_file);
     57     declProp("SJReceiverPosFile", m_sjreceiver_pos_file);
     58     declProp("SJFixturePosFile", m_sjfixture_pos_file);


    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("Strut2PosFile").set(DetSimOptions.data_load("StrutBar2_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("FastenerPosFile").set(DetSimOptions.data_load("Strut_Anchor_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("XJanchorPosFile").set(DetSimOptions.data_load("XJanchor.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJCLSanchorPosFile").set(DetSimOptions.data_load("SJCLSanchor.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJReceiverPosFile").set(DetSimOptions.data_load("SJReceiverPos.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJFixturePosFile").set(DetSimOptions.data_load("SJFixturePos.csv"))

     22 import os
     23 def data_load(filename):
     24     # Load the data located in $DETSIMOPTIONSROOT/data
     25     detroot = os.environ["DETSIMOPTIONSROOT"]
     26     if not detroot:
     27         raise Exception("Can't get $DETSIMOPTIONSROOT")
     28     f = os.path.join(detroot, "data",  filename)
     29     if not os.path.exists(f):
     30         raise Exception("Can't get $DETSIMOPTIONSROOT/data/%s"%filename)
     31 
     32     return f


    [blyth@localhost DetSimOptions]$ echo $DETSIMOPTIONSROOT
    /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions
    [blyth@localhost DetSimOptions]$ 

    [blyth@localhost DetSimOptions]$ l $DETSIMOPTIONSROOT/data/
    total 48
     0 drwxrwxr-x. 7 blyth blyth   93 May 24 16:17 ..
     0 drwxrwxr-x. 2 blyth blyth  206 May 22 17:20 .
     4 -rw-rw-r--. 1 blyth blyth  800 May 22 17:20 Guide_Tube.csv
     4 -rw-rw-r--. 1 blyth blyth   29 May 22 17:20 SJCLSanchor.csv
     4 -rw-rw-r--. 1 blyth blyth  552 May 22 17:20 SJFixturePos.csv
     4 -rw-rw-r--. 1 blyth blyth  118 May 22 17:20 SJReceiverPos.csv
     8 -rw-rw-r--. 1 blyth blyth 6465 May 22 17:20 Strut_Acrylic.csv
    12 -rw-rw-r--. 1 blyth blyth 9989 May 22 17:20 Strut_Anchor_Acrylic.csv
     8 -rw-rw-r--. 1 blyth blyth 4114 May 22 17:20 StrutBar2_Acrylic.csv
     4 -rw-rw-r--. 1 blyth blyth  911 May 22 17:20 XJanchor.csv
    [blyth@localhost DetSimOptions]$ 

    [blyth@localhost data]$ wc -l *.csv
       39 Guide_Tube.csv
        2 SJCLSanchor.csv
       36 SJFixturePos.csv
        8 SJReceiverPos.csv
      370 Strut_Acrylic.csv
      590 Strut_Anchor_Acrylic.csv
      220 StrutBar2_Acrylic.csv
       56 XJanchor.csv
     1321 total
    [blyth@localhost data]$ 



JUNO_SIMPLIFY_CALIB_ANCHOR
---------------------------

::



    epsilon:presentation blyth$ jgr JUNO_SIMPLIFY_CALIB_ANCHOR
    ./Simulation/DetSimV2/CentralDetector/src/XJanchorConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ; 
    ./Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    Binary file ./Simulation/DetSimV2/CentralDetector/src/.SJCLSanchorConstruction.cc.swp matches
    ./Simulation/DetSimV2/CentralDetector/src/SJCLSanchorConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    ./Simulation/DetSimV2/CentralDetector/src/SJReceiverConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    ./Simulation/DetSimV2/DetSimMT/share/run.py:    os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"] = "Enable"
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"]="Enable"
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        elif "JUNO_SIMPLIFY_CALIB_ANCHOR" in os.environ:
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            os.environ.pop("JUNO_SIMPLIFY_CALIB_ANCHOR")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            print("unset key : JUNO_SIMPLIFY_CALIB_ANCHOR ")       
    epsilon:junosw blyth$ 



jcv JUNODetSimModule::

    0276         grp_calib_unit.add_argument("--simplify-calib-anchor", dest="simplify_calib_anchor", action="store_true", help=mh(""))
     277         grp_calib_unit.add_argument("--no-simplify-calib-anchor", dest="simplify_calib_anchor", action="store_false", help=mh(""))
     278         grp_calib_unit.set_defaults( simplify_calib_anchor = True )


    2213         #==========  simplify calib anchor ============#
    2214         if args.simplify_calib_anchor:
    2215             os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"]="Enable"
    2216         elif "JUNO_SIMPLIFY_CALIB_ANCHOR" in os.environ:
    2217             os.environ.pop("JUNO_SIMPLIFY_CALIB_ANCHOR")
    2218             print("unset key : JUNO_SIMPLIFY_CALIB_ANCHOR ")
    2219 

