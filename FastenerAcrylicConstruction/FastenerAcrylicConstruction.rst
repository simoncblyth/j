FastenerAcrylicConstruction
============================


NEXT
-----

* try temporary kludge change to 1 column : as sanity check  
* review listnode impl : work out how to enable


j/PMTSim
-----------

j/PMTSim/PMTSim.cc::

     784         m_facr = new FastenerAcrylicConstruction(FACR_STR) ;
     785         m_facr->getLV();


jcv FastenerAcrylicConstruction.

+------------------+-----------------------------------------+
| j/PMTSim label   |  member/name                            |
+==================+=========================================+
| facrLogical      |  logicFasteners/lFasteners              |   
+------------------+-----------------------------------------+
| facrSolid        |  uni_Addition/uni1                      | 
+------------------+-----------------------------------------+

::

    GEOM=facrSolid ~/o/u4/tests/U4Mesh_test2.sh grab
    GEOM=facrSolid ~/o/u4/tests/U4Mesh_test2.sh ana 


G4VSolid : union of non-overlapping 
--------------------------------------


annulus IonRing
    G4Tubs with non-zero rmin

    * Opticks translation is cyl-cyl CSG subtraction of 

8 G4Tubs screws with zero rmin

    * the screws do not overlap : 


U4TreeCreateSSimTest.sh to create tree+scene from GEOM and vizualize the scene triangulated 
--------------------------------------------------------------------------------------------

::

   GEOM ## set to facrLogical

   ~/o/u4/tests/U4TreeCreateSSimTest.sh

   SCENE=3 ~/o/sysrap/tests/ssst.sh 


Try to visualize analytic : with 8 column its no show, but trimesh fallback appears
-----------------------------------------------------------------------------------------

::

   GEOM ## check set to facrLogical 

   ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh   ## do the conversion to CSGFoundry 


Add CFBaseFromGEOM config for CSGFoundry::Load::

     34 # NB CFBase directory is expected to contain CSGFoundry 
     35 if [ "$GEOM" == "facrLogical" ]; then
     36     export ${GEOM}_CFBaseFromGEOM=/tmp/blyth/opticks/G4CXOpticks_setGeometry_Test
     37 else

Analytic viz::

     ~/o/CSGOptiX/cxr_min.sh     # the box is empty (with 8 column Stonehenge)

Configure trimesh fallback using the CSGFoundry/mmlabel.txt string::

    141 if [ -n "$TRIMESH" ]; then
    142 
    155    trimesh=3:Rock_solid
    156 
    157    export OPTICKS_SOLID_TRIMESH=$trimesh
    158 fi
    159 

Fallback trimesh viz::

     TRIMESH=1 ~/o/CSGOptiX/cxr_min.sh   # now the box contains triangulated stonehenge



sanity check reduce to one column : it appears in both ana and tri
----------------------------------------------------------------------

rebuild j/PMTSim lib::

    jcv FastenerAcrylicConstruction
    jps
    om   

Recreate stree+scene::

   ~/o/u4/tests/U4TreeCreateSSimTest.sh clean
   ~/o/u4/tests/U4TreeCreateSSimTest.sh 
    
Viz triangulated::

   SCENE=3 ~/o/sysrap/tests/ssst.sh    ## confirm one triangulated column 

Recreate CSGFoundry::

   ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh clean 
   ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh

Viz analytic::

   ~/o/CSGOptiX/cxr_min.sh              ## one analytic column appears 
    TRIMESH=1 ~/o/CSGOptiX/cxr_min.sh   ## fallback one column trimesh appears


How to switch on listnode ?
-----------------------------




