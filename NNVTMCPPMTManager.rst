NNVTMCPPMTManager
==================

Considered simplifying this to remove the near degenerate +0.001*mm 
that causes a "BT BT" on CRecorder that in Opticks is just "BT".
But subsequently decided its simpler to just detect and postSkip 
the Geant4 two-step in CRecorder::postTrackWriteSteps


Original LV/PV structure and m_simplify_csg variation
---------------------------------------------------------------------------

* The original LV/PV structure has two Pyrex solids that differ only by a "thickness" param change of 1E-3*mm 
* When m_simplify_csg=true the outer of those two near degenerate Pyrex solids is dropped  
  esentially by changing m_logical_pmt from pmt_log to body_log  


LV-Solid-Material association
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

     A:  "_log"         : pmt_log (LV)      /   pmt_solid   / GlassMat               ( m_logical_pmt = pmt_log , when m_simplify_csg=false )

     B:  "_body_log"    : body_log (LV)      /  body_solid   / GlassMat      [SD]    ( m_logical_pmt = body_log , when m_simplify_csg=true )

     C:  "_inner1_log"  : inner1_log (LV)    /  inner1_solid /  PMT_Vacuum   [SD]

     D:  "_inner2_log"  : inner2_log (LV)    /  inner2_solid /  PMT_Vacuum     


PV-LV association
~~~~~~~~~~~~~~~~~~~~~~

::


     A:  "_log"         : pmt_log (LV) /   pmt_solid   / GlassMat         ( m_logical_pmt = pmt_log, when m_simplify_csg=false )

     
             "_body_phys"  :  body_phys (PV)    

             B:  "_body_log"    : body_log (LV)      /  body_solid   / GlassMat      [SD]       ( m_logical_pmt = body_log , when m_simplify_csg=true )

             
                  "_inner1_phys" : inner1_phys
 
                  C:  "_inner1_log"  : inner1_log (LV)    /  inner1_solid /  PMT_Vacuum   [SD]


                  "_inner2_phys" : inner2_phys

                  D:  "_inner2_log"  : inner2_log (LV)    /  inner2_solid /  PMT_Vacuum     



Initially the below used two different G4PVPlacement ctors:

* body_phys uses the 1st ctor with 4th argument name after the logical volume and mother LV specified by LV 
* inner1_phys and inner2_phys use a bizarre ctor with 3rd argument name and mother LV specified by its PV 
  (no kidding, what have those G4 guys been smoking)  

Have rationalized to use the first, more sensible ctor for all three.

**/

