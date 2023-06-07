skip_solidXJfixture_at_junosw_level
=====================================

0-based 103 solidXJfixture culprit : how to switch it off at junosw level ?
---------------------------------------------------------------------------------

::

    epsilon:junosw blyth$ jgl solidXJfixture 
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc



::

    jcv LSExpDetectorConstruction
    jcv XJfixtureConstruction
    jcv XJanchorConstruction



JUNO_DEBUG_DISABLE_STICKS
~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    epsilon:junosw blyth$ jgr JUNO_DEBUG_DISABLE_STICKS
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  bool debug_disable_sticks = getenv("JUNO_DEBUG_DISABLE_STICKS") == nullptr ? false : true ; 


     567   // === construct Sticks ===
     568   bool debug_disable_sticks = getenv("JUNO_DEBUG_DISABLE_STICKS") == nullptr ? false : true ;
     569   if( debug_disable_sticks )
     570   {
     571       G4cout << "LSExpDetectorConstruction::setupCentralDetector setupCD_Sticks DISABLED BY OPTION --debug-disable-sticks " << G4endl      ;
     572   }
     573   else
     574   {
     575       G4cout << "[ LSExpDetectorConstruction::setupCentralDetector proceed with setupCD_Sticks " << G4endl ;
     576       setupCD_Sticks(cd_det);
     577       G4cout << "] LSExpDetectorConstruction::setupCentralDetector completed setupCD_Sticks " << G4endl ;
     578   }



LSExpDetectorConstruction::setupCD_Sticks
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



::

    0150   m_xjanchor_name = "XJanchor";
     151   m_xjfixture_name = "XJfixture";
     152   m_sjclsanchor_name = "SJCLSanchor";
     153   m_sjfixture_name = "SJFixture";
     154   m_sjreceiver_name = "SJReceiver";

    0156   m_pmt_mother = "lWaterPool";
     157   m_mask_mother = "lMaskVirtual";
     158   m_strut_mother = "lWaterPool";
     159   m_fastener_mother = "lWaterPool";
     160   m_upper_mother = "lWaterPool";
     161   m_addition_mother = "lWaterPool";
     162   m_xjanchor_mother = "lWaterPool";
     163   m_xjfixture_mother = "lWaterPool";
     164   m_sjclsanchor_mother = "lTarget";
     165   m_sjfixture_mother = "lTarget";
     166   m_sjreceiver_mother = "lTarget";
     167   m_sjreceiver_fastener_mother = "lTarget";
     168 



    1399 
    1400 //----------------------------------------------------------------------//
    1401   // XJ
    1402   setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    1403   setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    1404   // SJ
    1405   setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);
    1406   setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);
    1407   setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    1408   setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);
    1409 
    1410 //-----------------------END--------------------------------------------//
    1411 
    1412 }


    1414 void LSExpDetectorConstruction::setupAnchor(std::string anchor_name , std::string anchor_mother_name,  std::string anchor_pos_file ,      IDetElement * cd_det){
    1415 
    1416     IDetElement* anchor_det = nullptr;
    1417     std::string new_name = anchor_name + "Construction";
    1418     anchor_det = det_elem(new_name);
    1419     assert(anchor_det);
    1420     IDetElementPos* anchor_detelem_pos = nullptr;
    1421     G4double anchor_r = anchor_det->geom_info("PosR") ;
    1422     anchor_detelem_pos = new JUNO::Ball::HexagonPosBall(anchor_pos_file,anchor_r,false);
    1423     assert (anchor_detelem_pos);
    1424     bool anchor_det_status = cd_det->inject(anchor_mother_name, anchor_det, anchor_detelem_pos );
    1425     assert(anchor_det_status);
    1426     
    1427     LogInfo<<"anchor_name = " << new_name <<"   "
    1428            <<"anchor_r =  "   << anchor_r <<" mm  "
    1429            <<"anchor_pos_file = "<<anchor_pos_file << std::endl;
    1430 
    1431 }




Uncommitted addition of options --debug-disable-xj --debug-disable-sj --no-toptask-show
-----------------------------------------------------------------------------------------

::

    N[blyth@localhost j]$ t ntds0_noxj
    ntds0_noxj () 
    { 
        local gpfx=V;
        GPFX=${GPFX:-$gpfx};
        export EVTMAX=1;
        NOXJ=1 GEOM=${GPFX}1J009 ntds0
    }


    esac;
    case ${NOXJ:-0} in 
        0)
            opts="$opts"
        ;;
        1)
            opts="$opts --debug-disable-xj"
        ;;
    esac;
    case ${NOSJ:-0} in 
        0)
            opts="$opts"
        ;;
        1)
            opts="$opts --debug-disable-sj"
        ;;
    esac;
    opts="$opts --evtmax $evtmax";
    if [ "$mode" == "0" ]; then
        opts="$opts $(anamgr-none) ";
    else
        opts="$opts $(anamgr) ";
    fi;





::

    epsilon:junosw blyth$ git --no-pager diff 
    diff --git a/Detector/Geometry/Geometry/_PMTParamData.h b/Detector/Geometry/Geometry/_PMTParamData.h
    index 6c7bdaa..24d4507 100644
    --- a/Detector/Geometry/Geometry/_PMTParamData.h
    +++ b/Detector/Geometry/Geometry/_PMTParamData.h
    @@ -1,6 +1,7 @@
     #pragma once
     
     #include "PMTParamData.h"
    +#include "PMT.h"
     
     #if defined(WITH_NP) || defined(WITH_G4CXOPTICKS)
     #include "NPFold.h"
    diff --git a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    index f2cae1a..eeb0c5c 100644
    --- a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    +++ b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    @@ -1910,8 +1910,14 @@ class JUNODetSimModule(JUNOModule):
         --pmt20inch-profligate-tail-cut
             USE ONLY FOR DEBUGGING : Revert to profligate G4IntersectionSolid "cutting" that substantially adds complexity and breaks Opticks 
     
    -    --debug-disable-sticks         
    -        USE ONLY FOR DEBUGGING : Changes CD geometry by skipping the sticks, see LSExpDetectorConstruction::setupCentralDetector
    +    --debug-disable-sticks
    +        USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCentralDetector
    +
    +    --debug-disable-xj
    +        USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCD_Sticks
    +
    +    --debug-disable-sj
    +        USE ONLY FOR DEBUGGING : see LSExpDetectorConstruction::setupCD_Sticks
     
         --pmt20inch-plus-dynode
             USE ONLY FOR DEBUGGING : Adds PMT dynode geometry even when not using new PMT optical model, eg to check dynode does not impinge
    diff --git a/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc b/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    index 5a65743..5a67f53 100644
    --- a/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    +++ b/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    @@ -1398,14 +1398,34 @@ LSExpDetectorConstruction::setupCD_Sticks(IDetElement* cd_det) {
       }
     
     //----------------------------------------------------------------------//
    -  // XJ
    -  setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    -  setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    -  // SJ
    -  setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);  
    -  setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);
    -  setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    -  setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);
    +
    +
    +  bool DEBUG_DISABLE_XJ = getenv("JUNO_DEBUG_DISABLE_XJ") == nullptr ? false : true ; 
    +  if(DEBUG_DISABLE_XJ)
    +  {
    +      G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-xj " << G4endl ; 
    +  }
    +  else
    +  {
    +      // XJ
    +      setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    +      setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    +  }
    +
    +
    +  bool DEBUG_DISABLE_SJ = getenv("JUNO_DEBUG_DISABLE_SJ") == nullptr ? false : true ; 
    +  if(DEBUG_DISABLE_SJ)
    +  {
    +      G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-sj " << G4endl ; 
    +  }
    +  else
    +  {
    +      // SJ
    +      setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);  
    +      setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);
    +      setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    +      setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd_det);
    +  }
     
     //-----------------------END--------------------------------------------//
     
    epsilon:junosw blyth$ 






