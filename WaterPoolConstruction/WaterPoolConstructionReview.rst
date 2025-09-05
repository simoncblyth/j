WaterPoolConstructionReview
==============================


WaterPoolConstruction::getLV
------------------------------

The CONFIG split is a maintenance problem as have to near-duplicate
geometry between the two impl::

     103 WaterPoolConstruction::getLV() {
     104     
     105 
     106     if (theLV) {
     107         return theLV ;
     108     }
     109     initVariables();
     110     initMaterials();
     111 
     112     if(CONFIG == HIERARCHY )
     113     {
     114         makeWPLogical_hierarchy();      
     115         theLV = logicAirGap ;           
     116     }
     117     else                                
     118     {                                   
     119         // WP
     120         makeWPLogical();               
     121         // + : Air gap at the top surface of the WP
     122         makeAirGapLogical();
     123         makeAirGapPhysical();
     124         // + : Dead Water around the pool 
     125         makeDeadWaterLogical();
     126         makeDeadWaterPhysical();
     127         // + : Cylindrical Tyvek around the pool 
     128         makeCylTyvekLogical();
     129         makeCylTyvekPhysical();
     130               
     131         // Water Distributor
     132         makeWaterDistributorPartILogicalandPhysical();
     133 
     134         makeAirGapWaterDistributorLogicalandPhysical();
     135 
     136         makeWaterDistributorPartIILogical();
     137         makeWaterDistributorPartIIPhysical();
     138    
     139         makeWaterDistributorPartIIILogicalandPhysical();
     140 
     141         // makeWaterDistributorPartIIILogical(); 
     142         // makeWaterDistributorPartIIIPhysical();
     143 
     144         theLV = logicWaterPool ;  
     145     }
     146 
     147 #ifndef PMTSIM_STANDALONE
     148     if (m_enabledLatticedShell) { makeLatticedShell(); }
     149 #endif
     150 
     151     makeWaterAttLenMeasureEquip();
     152 
     153     return theLV  ;
     154 }


non-HIERARCHY WaterPoolConstruction::makeWPLogical
----------------------------------------------------

+----+-----------------------------------------+------------------+
|    | member/name                             |                  |
+====+=========================================+==================+
| SO | solidWaterPool/sOuterWaterPool          | 2 plane Polycone |
+----+-----------------------------------------+------------------+
| LV | logicWaterPool/lOuterWaterPool          |  MT:vetoWater    |
+----+-----------------------------------------+------------------+
| PV | NONE/NONE                               |  LV:LOCAL ROOT   |
+----+-----------------------------------------+------------------+


non-HIERARCHY WaterPoolConstruction::makeAirGapLogical
--------------------------------------------------------

big cylinder with small cylinder subtracted
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

solidAirGap_cyl/sAirGap_cyl : G4Tubs
solidAirGap_hole/sAirGap_hole : G4Tubs
solidAirGap/sAirGap : G4SubtractionSolid (solidAirGap_cyl - solidAirGap_hole)


union of 2 torus and tubs for piping
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

torus1/torus1 : G4Torus
torus2/torus2 : G4Torus
S_pipe/S_shape : G4UnionSolid (torus1 + torus2)

pipeA/pipeA : G4Tubs
S_pipe_with_A/S_pipe_with_A : G4UnionSolid ( S_pipe + pipeA )


big cylinder with piping subtracted
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

solidAirGap/sAirGap_minus_Spipe : G4SubtractionSolid ( solidAirGap - S_pipe_with_A*3 )


logicAirGap/lAirGap : G4LogicalVolume ( SO:solidAirGap MT:Air )





non-HIERARCHY WaterPoolConstruction::makeDeadWaterLogical
-------------------------------------------------------------

solidDeadWater_shell/sDeadWater_shell : G4Polycone (4 planes)







observation
~~~~~~~~~~~~

Geant4 volumes contained within others replace the material of the
mother. This so called hierarchy approach gives you a much simpler
and faster geometry as you avoid lots of subtractions plus you avoid 
duplication between the shape of the holes and the shape of 
what you put in the holes. The duplication is avoided because what you
place in the mother volume is automatically "making holes" without
any code. 

Geant4 performance favors deep trees of volumes with simple
solids rather than less-deep trees of volumes with very complicated solids.
Opticks GPU geometries translated from Geant4 also favor the same
thing because the acceleration structure (BVH:bounding-volume-hierarchy) 
is based on bounding boxes of all the volumes, so having more volumes
generally allows the acceleration structure to "index" the geometry
better. Also having cheap intersects from simpler solids 
within those volumes is a further performance bonus.

Finding an intersection with a big CSG tree of constituent solids 
requires recursive intersection tests with all the constituent 
solids in the tree. The bigger the tree the slower that will be and
the more prone to intersect precision errors, especially when G4Torus
is included. 

Consider the PMTs : there is no subtraction of holes in the Pyrex 
to place the Vacuum. Using the Geant4 hierarchy feature is a much
better way to implement the geometry. 

Because hierarchy results in simpler solid shapes and less duplication
its much easier to translate to Opticks for GPU running.

Contrast the complexity of WaterPoolConstruction.cc 
with the simplicity of WaterPoolConstruction2.icc  
WaterPoolConstruction::makeWPLogical_hierarchy
which makes almost the same geometry in much
less code without any subtractions.

::

            logicAirGap                          Air
               logicDeadWater                    DeadWater
                   logicTyvekFilm                Tyvek
                        logicWaterPool           vetoWater


Currently WaterPoolConstruction::getLV branches on
the CONFIG variable to choose between impls.
That causes a maintenance problem. Because it requires
duplication of effort to when there are changes.
It would be much better if we could switch to the 
HIERARCHY approach and avoid all the complex geometry.

I tried the Opticks translation of yupd-water-distributor
and note that the WaterDistributer has some overlap with
the PMTs at the corners. But because Opticks
has to use HIERARCHY config I cannot be sure that
the problem is not due to differences between the impls. 
Also makeWPLogical_hierarchy has not yet been updated
so only the WaterDistributer within the CD appears.

So, how to solve this maintenance problem ?
I would suggest you examine WaterPoolConstruction2.cc
and see if you think you could try implementing the WaterDistributer
in a simpler heirarchical way. 

Also to consider for future is how to handle the upper Chimney
within a heirachical geometry. 



::

     102 G4LogicalVolume*
     103 WaterPoolConstruction::getLV() {
     104 
     105 
     106     if (theLV) {
     107         return theLV ;
     108     }
     109     initVariables();
     110     initMaterials();
     111 
     112     if(CONFIG == HIERARCHY )
     113     {
     114         makeWPLogical_hierarchy();
     115         theLV = logicAirGap ;
     116     }
     117     else
     118     {
     119         // WP
     120         makeWPLogical();
     121         // + : Air gap at the top surface of the WP
     122         makeAirGapLogical();
     123         makeAirGapPhysical();
     124         // + : Dead Water around the pool 
     125         makeDeadWaterLogical();
     126         makeDeadWaterPhysical();
     127         // + : Cylindrical Tyvek around the pool 
     128         makeCylTyvekLogical();
     129         makeCylTyvekPhysical();
     130 
     131         // Water Distributor
     132         makeWaterDistributorPartILogicalandPhysical();
     133 
     134         makeAirGapWaterDistributorLogicalandPhysical();
     135 
     136         makeWaterDistributorPartIILogical();
     137         makeWaterDistributorPartIIPhysical();
     138 
     139         makeWaterDistributorPartIIILogicalandPhysical();
     140 
     141         // makeWaterDistributorPartIIILogical();
     142         // makeWaterDistributorPartIIIPhysical();
     143 
     144         theLV = logicWaterPool ;
     145     }
     146 
     147 #ifndef PMTSIM_STANDALONE
     148     if (m_enabledLatticedShell) { makeLatticedShell(); }
     149 #endif
     150 
     151     makeWaterAttLenMeasureEquip();
     152 
     153     return theLV  ;




