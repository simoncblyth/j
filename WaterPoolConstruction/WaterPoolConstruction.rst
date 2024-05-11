j/WaterPoolConstruction/WaterPoolConstruction.rst
=======================================================


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


