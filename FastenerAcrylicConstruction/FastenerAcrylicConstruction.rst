FastenerAcrylicConstruction
============================


NEXT
-----

* DONE: try temporary kludge change to 1 column : as sanity check  
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



Added LocalFastenerAcrylicConstruction1,2,3,4,5,6,7,8,...
-----------------------------------------------------------

Did this in::

   U4VolumeMaker
   USolidMaker



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




Check with GEOM LocalFastenerAcrylicConstruction2
-----------------------------------------------------------

::

    GEOM ## set to LocalFastenerAcrylicConstruction2  

    ~/o/u4/tests/U4TreeCreateSSimTest.sh clean
    ~/o/u4/tests/U4TreeCreateSSimTest.sh  
    SCENE=3 ~/o/sysrap/tests/ssst.sh run   ## confirm two triangulated column 

Reorganized the "setGeometry" outputs to be under a "$GEOM" folder
so can detect a setGeometry run from cxr_min.sh::

    ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh clean 
    ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh

    ~/o/CSGOptiX/cxr_min.sh    ##  confirm two analytic columns


Check with GEOM LocalFastenerAcrylicConstruction3
-----------------------------------------------------------

Reorganized U4TreeCreateSSimTest.sh to save to FOLD within {GEOM} 
to retain multiple geometries and reduce the need to keep cleaning.
Can just change {GEOM}.

Also reorganize ssst.sh to read SSim/scene from under {GEOM}

::

    GEOM ## set to LocalFastenerAcrylicConstruction3

    ~/o/u4/tests/U4TreeCreateSSimTest.sh    ## populate+persist SSim/SScene+stree

    SCENE=3 ~/o/sysrap/tests/ssst.sh run   ## confirm three triangulated column 
       
    ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh
    ~/o/CSGOptiX/cxr_min.sh    ##  confirm three analytic columns



Check with GEOM LocalFastenerAcrylicConstruction4 then 5 then 6 then 7
--------------------------------------------------------------------------

::

    GEOM ## set to LocalFastenerAcrylicConstruction4 then 5 6 7 

    ~/o/u4/tests/U4TreeCreateSSimTest.sh       ## populate+persist SSim/SScene+stree
    SCENE=3 ~/o/sysrap/tests/ssst.sh run       ## confirm 4 5 6 7  triangulated column 

    ~/o/g4cx/tests/G4CXOpticks_setGeometry_Test.sh    ## create CSGFoundry geom 
    ~/o/CSGOptiX/cxr_min.sh    ##  confirm 4 5 6 WITH-7 THE BOX IS EMPTY   analytic columns


Return to Largest that works LocalFastenerAcrylicConstruction6 
----------------------------------------------------------------




Reviewing listnode over in o
-----------------------------

~/o/notes/issues/listnode_review.rst




