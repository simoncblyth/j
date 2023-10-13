review_geometry_skips_exactly_which_solids
============================================


Deferred geometry:

+--------------------+-----------------------------------------------------------------------------+
| --no-guide_tube    |  OptiX 7.1 has curves which might allow G4Torus translation (dev. needed)   |   
+--------------------+-----------------------------------------------------------------------------+
| --debug-disable-xj |  XJfixture(xjfc) XJanchor(xjac)                                             |   
+--------------------+-----------------------------------------------------------------------------+   
| --debug-disable-sj |  SJCLSanchor(sjcl) SJFixture(sjfx) SJReceiver(sjrc) SJReceiverFastern(sjrf) |    
+--------------------+-----------------------------------------------------------------------------+   
| --debug-disable-fa |  FastenerAcrylic(facr)                                                      | 
+--------------------+-----------------------------------------------------------------------------+

::

    GEOM=xjfcSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    GEOM=xjacSolid ~/opticks/u4/tests/U4Mesh_test2.sh

    GEOM=sjclSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    GEOM=sjfxSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    GEOM=sjrcSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    GEOM=sjrfSolid ~/opticks/u4/tests/U4Mesh_test2.sh

    GEOM=facrSolid ~/opticks/u4/tests/U4Mesh_test2.sh





jgr DISABLE_XJ : jcv LSExpDetectorConstruction
------------------------------------------------

::

    1413   if(DEBUG_DISABLE_XJ)
    1414   {
    1415       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-xj " << G4endl ;
    1416   }
    1417   else
    1418   {
    1419       // XJ
    1420       setupAnchor(m_xjanchor_name  , m_xjanchor_mother , m_xjanchor_pos_file,cd_det);
    1421       setupAnchor(m_xjfixture_name , m_xjfixture_mother , m_xjanchor_pos_file,cd_det);
    1422   }
    1423 


XJanchorConstruction : xjac
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+-------------------------+----------------------------+
| m_xjanchor_name         | "XJanchor"                 | 
+-------------------------+----------------------------+
| m_xjanchor_mother       | "lWaterPool"               |
+-------------------------+----------------------------+
| class                   | jcv XJanchorConstruction   |
+-------------------------+----------------------------+
| j/PMTSim solid GEOM     | xjacSolid                  |       
+-------------------------+----------------------------+
| j/PMTSim logical GEOM   | xjacLogical                |  
+-------------------------+----------------------------+

Visualize polygonized using pyvista with::

    GEOM=xjacSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## shallow bowl with huge sphere upper curve 


XJfixtureConstruction : xjfc
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+-------------------------+--------------------------------+
| m_xjfixture_name        | "XJfixture"                    |
+-------------------------+--------------------------------+
| m_xjfixture_mother      | "lWaterPool"                   |
+-------------------------+--------------------------------+
| class                   |  jcv XJfixtureConstruction     |
+-------------------------+--------------------------------+
| j/PMTSim GEOM           |  xjfcSolid,xjfcLogical         |
+-------------------------+--------------------------------+

::

    GEOM=xjfcSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## space station washer on altar 

    GEOM=xjfcDownUni4 ~/opticks/u4/tests/U4Mesh_test2.sh
    ## space station : washer and 4 boxes 

    GEOM=xjfcUpUni1 ~/opticks/u4/tests/U4Mesh_test2.sh
    ## altar : union of two boxes (no-anticoincidence avoidance)

    GEOM=xjfcUpUni2 ~/opticks/u4/tests/U4Mesh_test2.sh
    ## altar with notch box subtracted 

Summary of boolean tree extracted by reading the code::

   Solid:U
      DownUni4:U
         DownUni3:U
            DownUni2:U  
               DownUni1:U
                  Down1:Tubs   (HMM: CAUTION THIS BECOMES SUBTRACTION) 
                  Down2:Box  
               Down2:Box 
            Down3:Box
         Down3:Box
      UpUni2:SUB
         UpUni1:U
            Up1:BOX
            Up2:BOX
         Up3:BOX


Thinking about how to convert parts of boolean trees into compound listnodes, 
and the complexities of anti-coincidence, automation is just unfeasible. 
It needs to be a rather manual adjustment of a geometry with markup
via hints within the solid names. 

For example in the above the all union tree formed by DownUni4 
which is composed of four box and a tubs looks like an obvious listnode. 
BUT actually its not so easy, the Tubs is not atomic in Opticks it is a cylinder 
with inner cylinder subtracted. So would need to rearrange the geometry 
definition to do that subtraction separately in order to give a good union 
clump (including full cylinder and four boxes) to become the listnode. 
Which then gets a smaller cylinder subtracted. 

Maybe could do initial expt within Geant4 using G4MultiUnion ?

jcv XJfixtureConstruction::

    110 // fixture part
    111     solidXJfixture_down1 = new G4Tubs("solidXJfixture_down1", 25.*mm, 45.*mm, 13./2*mm, 0.*deg, 360.*deg);
    112     solidXJfixture_down2 = new G4Box("solidXJfixture_down2", 10.*mm, 11.5*mm, 13/2.*mm);
    113     solidXJfixture_down_uni1 = new G4UnionSolid("solidXJfixture_down_uni1", solidXJfixture_down1, solidXJfixture_down2, 0, G4ThreeVector(52.*mm, 0.*mm, 0.*mm));
    114     solidXJfixture_down_uni2 = new G4UnionSolid("solidXJfixture_down_uni2", solidXJfixture_down_uni1, solidXJfixture_down2, 0, G4ThreeVector(-52.*mm, 0.*mm, 0.*mm));
    115     solidXJfixture_down3 = new G4Box("solidXJfixture_down3", 15.*mm, 15.*mm, 13/2.*mm);
    116     solidXJfixture_down_uni3 = new G4UnionSolid("solidXJfixture_down_uni3", solidXJfixture_down_uni2, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, 50.*mm, 0.*mm));
    117     solidXJfixture_down_uni4 = new G4UnionSolid("solidXJfixture_down_uni4", solidXJfixture_down_uni3, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, -50.*mm, 0.*mm));
    118 
    119 // cover part
    120     solidXJfixture_up1 = new G4Box("solidXJfixture_up1", 15.*mm, 40.*mm, 17/2.*mm);
    121     solidXJfixture_up2 = new G4Box("solidXJfixture_up2", 15.*mm, 65*mm, 5.*mm);
    122     solidXJfixture_up_uni1 = new G4UnionSolid("solidXJfixture_up_uni1", solidXJfixture_up1, solidXJfixture_up2, 0, G4ThreeVector(0.*mm, 0.*mm, 13.5*mm));
    123 
    124     solidXJfixture_up3 = new G4Box("solidXJfixture_up3", 20.*mm, 11*mm, 11.*mm);
    125     solidXJfixture_up_uni2 = new G4SubtractionSolid("solidXJfixture_up_uni2",solidXJfixture_up_uni1, solidXJfixture_up3 ,0, G4ThreeVector(0.*mm, 0.*mm, 17/2.0*mm));//make a hole     
    126 
    127 // union 
    128     solidXJfixture = new G4UnionSolid("solidXJfixture", solidXJfixture_down_uni4, solidXJfixture_up_uni2, 0, G4ThreeVector(0.*mm, 0.*mm, -25.*mm));
    129 







jgr DISABLE_SJ : jcv LSExpDetectorConstruction
------------------------------------------------


::

    1425   bool DEBUG_DISABLE_SJ = getenv("JUNO_DEBUG_DISABLE_SJ") == nullptr ? false : true ;
    1426   if(DEBUG_DISABLE_SJ)
    1427   {
    1428       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-sj " << G4endl ;
    1429   }
    1430   else
    1431   {
    1432       // SJ
    1433       setupAnchor(m_sjclsanchor_name , m_sjclsanchor_mother,  m_sjclsanchor_pos_file, cd_det);
    1434       setupAnchor(m_sjfixture_name , m_sjfixture_mother, m_sjfixture_pos_file, cd_det);
    1435       setupAnchor(m_sjreceiver_name , m_sjreceiver_mother, m_sjreceiver_pos_file, cd_det);
    1436       setupAnchor(m_sjreceiver_fastener_name , m_sjreceiver_fastener_mother, m_sjreceiver_pos_file , cd1437   }
    1438   


+--------------------------+-------------------------------+
| m_sjclsanchor_name       | "SJCLSanchor"                 |
+--------------------------+-------------------------------+
| m_sjclsanchor_mother     | "lTarget"                     |
+--------------------------+-------------------------------+
| class                    | jcv SJCLSanchorConstruction   |
+--------------------------+-------------------------------+
| j/PMTSim GEOM            | sjclSolid, sjclLogical        |
+--------------------------+-------------------------------+

::

    GEOM=sjclSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## flat box atop inverted flying saucer

    GEOM=sjclSphereSub ~/opticks/u4/tests/U4Mesh_test2.sh
    ## huge box with sphere cut away concentrically inside  

    GEOM=sjclDown ~/opticks/u4/tests/U4Mesh_test2.sh
    ## simple "pyramidal" cone

    GEOM=sjclSub ~/opticks/u4/tests/U4Mesh_test2.sh
    ## bizarrely expensive dustbin lid 

    AGEOM=sjclSub BGEOM=sjclDown  ~/opticks/u4/tests/U4Mesh_test2.sh ana 



+--------------------------+-------------------------------+
| m_sjfixture_name         | "SJFixture"                   | 
+--------------------------+-------------------------------+
| m_sjfixture_mother       |  "lTarget"                    |
+--------------------------+-------------------------------+
| class                    |  jcv SJFixtureConstruction    |  
+--------------------------+-------------------------------+
| j/PMTSim GEOM            | sjfxSolid                     | 
+--------------------------+-------------------------------+

Issues

1. compilation warnings : using uninitialized 
2. SEGV if run without JUNO_SIMPLIFY_CALIB_ANCHOR=1

::

    GEOM=sjfxSolid JUNO_SIMPLIFY_CALIB_ANCHOR=1  ~/opticks/u4/tests/U4Mesh_test2.sh
    ## bar sitting on cone (slapdash look) 



+--------------------------+-------------------------------+
| m_sjreceiver_name        |  "SJReceiver"                 |
+--------------------------+-------------------------------+
| m_sjreceiver_mother      |  "lTarget"                    |
+--------------------------+-------------------------------+
| class                    |  jcv SJReceiverConstruction   |
+--------------------------+-------------------------------+
| j/PMTSim GEOM            |  sjrcSolid                    | 
+--------------------------+-------------------------------+


::

    GEOM=sjrcSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## cylinder ontop of inverted flying saucer



+------------------------------+------------------------------------+
| m_sjreceiver_fastener_name   |  "SJReceiverFastern"               |
+------------------------------+------------------------------------+
| m_sjreceiver_fastener_mother |  "lTarget"                         |
+------------------------------+------------------------------------+
| class                        | jcv SJReceiverFasternConstruction  | 
+------------------------------+------------------------------------+
| j/PMTSim GEOM                |  sjrfSolid                         |
+------------------------------+------------------------------------+

::

    GEOM=sjrfSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## altar on top of spacestation 



jgr DISABLE_FA : jcv LSExpDetectorConstruction
-------------------------------------------------

::

    1381   bool DEBUG_DISABLE_FA = getenv("JUNO_DEBUG_DISABLE_FA") == nullptr ? false : true ;
    1382   if(DEBUG_DISABLE_FA)
    1383   {
    1384       G4cout << "LSExpDetectorConstruction::setupCD_Sticks --debug-disable-fa " << G4endl ;
    1385   }
    1386   else
    1387   {
    1388       if (m_fastener_name == "FastenerAcrylic") {
    1389          setupAnchor(m_fastener_name , m_fastener_mother , m_fastener_pos_file , cd_det);
    1390       } else if (m_fastener_name == "FastenerBalloon") {
    1391           // no fastener in Balloon Option
    1392       }
    1393   }



+---------------------+------------------------------------+
| m_fastener_name     |   FastenerAcrylic                  |
+---------------------+------------------------------------+
| m_fastener_mother   |  "lWaterPool"                      |
+---------------------+------------------------------------+
| class               | jcv FastenerAcrylicConstruction    |
+---------------------+------------------------------------+
| j/PMTSim GEOM       |  facrSolid                         |
+---------------------+------------------------------------+

::

    GEOM=facrSolid ~/opticks/u4/tests/U4Mesh_test2.sh
    ## annulus and 8 floating screws


