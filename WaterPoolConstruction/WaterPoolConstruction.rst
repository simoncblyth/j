j/WaterPoolConstruction/WaterPoolConstruction.rst
=======================================================



blyth-WaterPoolConstruction-fix-theLV-injection-bug-for-HIERARCHY-CONFIG
-------------------------------------------------------------------------






Suspect issue with CONFIG:3 geometry : from lack of WP PMT intersects
-----------------------------------------------------------------------

::

    A[blyth@localhost junosw]$ jgr PMT_20inch_veto
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    A[blyth@localhost junosw]$ 


Look at the code of placement of WP PMTs.


Placement of WaterPoolConstruction
-------------------------------------

::

    1959 void
    1960 LSExpDetectorConstruction::setupOuterWaterPool()
    1961 {
    1962     de_wp_det = det_elem("WaterPoolConstruction");
    1963     assert(de_wp_det);
    1964     // place the water pool into bottom rock or the world.
    1965     if (de_bottom_rock == 0) {
    1966         new G4PVPlacement(0, // no rotation
    1967                           G4ThreeVector(0,0,0), // at (x,y,z)
    1968                           de_wp_det -> getLV(),    // its logical volume
    1969                           "pOuterWaterPool",   // its name
    1970                           logicWorld,      // its mother  volume
    1971                           false,           // no boolean operation|     s
    1972                           0);              // no particular field
    1973     } else {
    1974         de_bottom_rock->inject("lPoolLining", de_wp_det, 0);
    1975     }
    1976 }



LSExpDetectorConstruction::setupWP_PMTs
--------------------------------------------

One place where the WaterPoolConstruction::inject is used::

    1367 void
    1368 LSExpDetectorConstruction::setupWP_PMTs() {
    1369 
    1370   //put veto pmts into water pool
    1371   IDetElement* glob_info = det_elem("GlobalGeomInfo");
    1372   G4double waterpool_r = glob_info->geom_info("WaterPool.R");
    1373   G4double waterpool_h = glob_info->geom_info("WaterPool.H");
    1374   G4double vetopmt_interval = 2*m;
    1375   IDetElementPos* veto_pmt_detelem_pos = 0;
    1376   if (m_veto_pmt_pos_mode == "CalMode") {
    1377       veto_pmt_detelem_pos = new JUNO::Cylinder::CalPositionCylinder(
    1378               waterpool_r,
    1379               waterpool_h,
    1380               pmt_det_veto->GetPMTRadius(),
    1381               pmt_det_veto->GetPMTHeight(),
    1382               vetopmt_interval);
    1383   } else if (m_veto_pmt_pos_mode == "FileMode") {
    1384    veto_pmt_detelem_pos = new JUNO::Ball::VetoPmtPosBall(m_scope);
    1385   }
    1386   assert (veto_pmt_detelem_pos);
    1387  std::cout << "WP PMT Position Mode: " << m_veto_pmt_pos_mode << std::endl;
    1388   // If the string m_veto_pmt_pos_mode is empty, don't place any PMTs.
    1389   if (m_veto_pmt_pos_mode.size()!=0) {
    1390       assert (veto_pmt_detelem_pos);
    1391       m_pmt_mother = "OuterWaterVeto";
    1392       bool veto_status = de_wp_det->inject(m_pmt_mother, pmt_det_veto, veto_pmt_detelem_pos);
    1393       assert (veto_status);
    1394   }
    1395 }






jcv WaterPoolConstruction2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    144     /**
    145             logicAirGap                          Air
    146                logicDeadWater                    DeadWater
    147                    logicTyvekFilm                Tyvek
    148                         logicWaterPool           vetoWater
    149 
    150     **/
    151 
    152     // HMM: the order these associations are done should not matter ?
    153 
    154     // place logicDeadWater within logicAirGap
    155     new G4PVPlacement(0, G4ThreeVector(0, 0, 0),logicDeadWater,"pDeadWater",logicAirGap , false, 0);
    156 
    157     // place logicTyvekFilm within logicDeadWater
    158     new G4PVPlacement(0, G4ThreeVector(0, 0, 0),logicTyvekFilm,"pTyvekFilm",logicDeadWater , false, 0);
    159 
    160     // place logicWaterPool within logicTyvekFilm
    161     new G4PVPlacement(0, G4ThreeVector(0, 0, 0),logicWaterPool,"pWaterPool",logicTyvekFilm , false, 0);
    162 
    163 }




CONFIG:3 changes theLV
~~~~~~~~~~~~~~~~~~~~~~~

::

    094 G4LogicalVolume*
     95 WaterPoolConstruction::getLV() {
     96 
     97 
     98     if (theLV) {
     99         return theLV ;
    100     }
    101     initVariables();
    102     initMaterials();
    103 
    104     if(CONFIG == HIERARCHY )
    105     {
    106         makeWPLogical_hierarchy();
    107         theLV = logicAirGap ;
    108     }
    109     else
    110     {
    111         // WP
    112         makeWPLogical();
    113         // + : Air gap at the top surface of the WP
    114         makeAirGapLogical();
    115         makeAirGapPhysical();
    116         // + : Dead Water around the pool 
    117         makeDeadWaterLogical();
    118         makeDeadWaterPhysical();
    119         // + : Cylindrical Tyvek around the pool 
    120         makeCylTyvekLogical();
    121         makeCylTyvekPhysical();
    122 
    123         // Water Distributor
    124         makeWaterDistributorPartIILogical();
    125         makeWaterDistributorPartIIPhysical();
    126 
    127         // makeWaterDistributorPartIIILogical();
    128         // makeWaterDistributorPartIIIPhysical();
    129 
    130         theLV = logicWaterPool ;
    131     }



The use of theLV potential smoking gun in CONFIG:3
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    161 bool
    162 WaterPoolConstruction::inject(std::string motherName, IDetElement* other, IDetElementPos* pos) {
    163     // = Outer Water Pool =
    164     // == CD ==
    165     // == Veto PMTs ==
    166     assert( theLV );
    167 
    168     G4LogicalVolume* mothervol = 0;
    169     G4int copyno = 0;
    170     bool is_20inch_pmt = false;
    171 
    172     if (motherName == "lWaterPool") {
    173         // place CD
    174         mothervol = theLV ;
    175     } else if (motherName == "OuterWaterVeto") {
    176         // place Veto PMTs
    177         mothervol = theLV ;
               ^^^^^^^^^^^^^^^^^^^^^^  

    178         copyno = kOFFSET_WP_PMT;
    179         is_20inch_pmt = true;
    180     }
    181     if (not mothervol) {
    182         // don't find the volume.
    183         LogError << "Can't find the mother volume named " << motherName << std::endl;
    184         return false;
    185     }
    186 
    187     // if the placed daughters are 20inch PMT, but it is not enabled in wp,
    188     // just return.
    189     if (is_20inch_pmt and not m_pmt20inch_enabled) {
    190         LogInfo << "The 20inch PMTs are disabled in CD." << std::endl;
    191         return true;
    192     }
    193 



Another place where the WaterPoolConstruction::inject is used::

     541 void
     542 LSExpDetectorConstruction::setupCentralDetector()
     543 {
     544   // construct the Central Detector
     545   IDetElement* cd_det = 0;
     546   if (m_cd_name == "DetSim0" or m_cd_name == "DetSim1" or m_cd_name == "DetSim2") {
     547       std::string new_name = m_cd_name + "Construction";
     548       cd_det = det_elem(new_name);
     549   }
     551   assert(cd_det);
     552 
     553   de_cd_det = cd_det;
     ...
     574   // place the CD into bottom rock or into the world
     575   if (de_wp_det == 0) {
     576       assert(de_wp_det);
     577   } else {
     578       de_wp_det->inject("lWaterPool", de_cd_det, 0);
     579   }
     580 










Review code thinking about how to impl HIERARCHY
--------------------------------------------------

WaterPoolConstruction::makeWPLogical
    creates logicWaterPool G4Polycone of : material vetoWater

WaterPoolConstruction::makeAirGapLogical
    creates logicAirGap G4SubtractionSolid subtracting small cylinder from big one : material Air
        
WaterPoolConstruction::makeAirGapPhysical
    places logicAirGap within logicWaterPool

    logicWaterPool:vetoWater
        logicAirGap:Air

WaterPoolConstruction::makeDeadWaterLogical
    




Current flat sibling approach
------------------------------

Current flat sibling approach::

   vetoWater
      DeadWater : holes with vetoWater
      Tyvek     : holes with vetoWater
      Air
      Steel

* forces complex CSG shapes for DeadWater+Tyvek to avoid 
  overlaps between the siblings


Hierarchy approach 
--------------------

::

      DeadWater
         Air  
         Tyvek
            vetoWater 
               Steel 
               Steel
               ...

         Steel-pillar-feet    


      +---DeadWater-------------+   
      | +---Air---------------+ |
      | |                     | |
      | +---Tyvek-------------+ |    
      | | +----vetoWater----+ | |   
      | | |                 | | |   
      | | | +-+         +-+ | | |   
      | | | |Steel      | | | | |   
      | | | +-+         +-+ | | |   
      | | +-----------------+ | |   
      | +---------------------+ |   
      +-------------------------+   

* Profits from Geant4 daughter material overriding mother such 
  that DeadWater, Air, Tyvek and vetoWater can all be simple
  filled cylinders (G4Tubs/G4Polycone with inner radius zero)
  of for DeadWater/Tyvek/VetoWater progressively smaller radii 
  and heights.

* If the Steel pillars need to extend outside the vetoWater then
  could create small pillar "feet" cylinders within the DeadWater




WaterPoolConstruction::makeWPLogical
-------------------------------------

+----+-----------------------------------------+------------------+
|    | member/name                             |                  |
+====+=========================================+==================+
| SO | solidWaterPool/sOuterWaterPool          | 2 plane Polycone |
+----+-----------------------------------------+------------------+
| LV | logicWaterPool/lOuterWaterPool          |  MT:vetoWater    |
+----+-----------------------------------------+------------------+
| PV | NONE/NONE                               |  LV:LOCAL ROOT   |
+----+-----------------------------------------+------------------+


WaterPoolConstruction::makeAirGapLogical,Physical
---------------------------------------------------

* sAirGap is subtraction of sAirGap_cyl and sAirGap_hole

+----+-----------------------------------------+---------------------+
|    | member/name                             |                     |
+====+=========================================+=====================+
| SO | solidAirGap/sAirGap                     | Tubs-Tubs           |
+----+-----------------------------------------+---------------------+
| LV | logicAirGap/lAirGap                     |  MT:Air             |
+----+-----------------------------------------+---------------------+
| PV | NONE/pAirGap                            |  MLV:logicWaterPool |
+----+-----------------------------------------+---------------------+


WaterPoolConstruction::makeDeadWaterLogical,Physical
------------------------------------------------------

+----+-----------------------------------------+--------------------+
|    | member/name                             |                    | 
+====+=========================================+====================+
| SO | solidDeadWater/sDeadWater               |                    | 
+----+-----------------------------------------+--------------------+
| LV | logicDeadWater/lDeadWater               |  MT:DeadWater      | 
+----+-----------------------------------------+--------------------+
| PV | NONE/pDeadWater                         | MLV:logicWaterPool |  
+----+-----------------------------------------+--------------------+


Uses G4Polycone with 6 planes to create hollow cylinder
and then subtracts 61 holes, one at center top and 60 around the 
edge of the base in 30 pairs::  



     +---------------------+   +----------------+---+    1 plane 
     |                     |   |                    |
     +   +-----------------+   +----------------+   +    2 planes
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     +   +                   +                  +   +
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     |   |                                      |   |
     +   +--+  +---+  +------+------------------+   +    2 planes
     |      |  |   |  |                             |
     +------+  +---+  +------+----------------------+    1 plane 
    
                       

WaterPoolConstruction::makeCylTyvekLogical,Physical
------------------------------------------------------


* pTyvekFilm uses same SO/LV/PV construction technique as pDeadWater


+----+-----------------------------------------+--------------------+
|    | member/name                             |                    | 
+====+=========================================+====================+
| SO | solidTyvekFilm/sTyvekFilm               |                    | 
+----+-----------------------------------------+--------------------+
| LV | logicTyvekFilm/lTyvekFilm               |  MT:Tyvek          | 
+----+-----------------------------------------+--------------------+
| PV | NONE/pTyvekFilm                         | MLV:logicWaterPool |  
+----+-----------------------------------------+--------------------+



WaterPoolConstruction::makeLatticedShell
------------------------------------------

Three ShellData loops over::

   all_data_col
   all_data_layer
   all_pillar_data

All the placements have  mother-LV (MLV) logicWaterPool
Material is Steel for HBeamConstruction::

    jcv HBeamConstruction


