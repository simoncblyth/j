FastenerAcrylicConstruction
============================


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


