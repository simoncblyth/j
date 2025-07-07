ISSUES
==========


* Geant4 track label compatibility to enable opticksMode:3 and 
  EPH monitoring to not force switching off all other AnaMgr 
  than the U4RecorderAnaMgr
  
  * careful track labels are used all over the place (eg C4)
    and within JUNOSW often without the precaution of using dynamic_cast 
    so the track info can easily cause crashes  


* cxr_min.sh zdepth issue, made plain with::

   export SGLFW_Evt__shader_name=rec_line_strip


* running with array recording eg with DebugLite is prone to VRAM OOM
  requiring manual setting of eg::

        export OPTICKS_MAX_SLOT=M10

  * automatically reduce MAX_SLOT when running with array recording
  * :doc:`muon/OOM_with_debug_arrays_enabled`



* gitlab runner from GPU node to enable starting a collection of automated A:B tests 

* Chimney : major detector geometry overhaul



IDEA for Screenshot workflow 
-------------------------------

* viz scripts write file ~/.opticks/VIZCTX.sh containing::

    export VIZCTX=GEOM/$GEOM/$SCRIPTNAME/$TEST/$CHECK
    export VIZCTX_STAMP=seconds_since_epoch


* hit button for Screenshot
* ~/Pictures/pic.sh sources the ~/.opticks/VIZCTX.sh and tries to associate the 



WP_WALL WP_ATM addition caused SPMT.h assert
----------------------------------------------

::

    503 inline NP* _PMTSimParamData::serialize_pmtTotal() const
    504 {
    505     NPX::KV<int> kv ;
    506     kv.add("PmtTotal",      data.m_PmtTotal);
    507     kv.add("PmtTotal_SPMT", data.m_PmtTotal_SPMT );
    508     kv.add("PmtTotal_WP",   data.m_PmtTotal_WP );
    509     kv.add("PmtTotal_ALL",  data.m_PmtTotal_ALL );
    510     return kv.values() ;
    511 }


FIXED ISSUES
--------------


* FIXED : speed discrepancy for some photons bounced off PMT_20inch_veto:0:1000 
  heading up towards pool cover

  * looking into this its due to overlapping vetoWater-Tyvek-DeadWater
  * "jcv WaterPoolConstruction2"
  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP_poolcover_deviant`
  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP_poolcover_CircleXZ`


* FIXED : :doc:`oj_cmake_error/oj_cmake_error` by clean release v0.5.0 with standard C4

* FIXED : WP PMT : more SA on A side
 
  * Caused by another SPMT.h qeScale_v indexing bug
  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP_10percent_more_SA_for_A` 
  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP`
  * :doc:`WaterPoolConstruction/WaterPoolConstruction`


* FIXED : B side WP_PMT input photons get minimal intersects

  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP`
  * only geometry "seen" by input photons on B side is sOuterWaterPool 
  * this is bizarre as B side works fine from other positions ? 
  * suspect this must be caused by the WaterPoolConstruction_CONFIG=3 
    changing heirarchy in way that the PMT injection does not like ?  
  * TODO: default gamma near WP_PMT
  * :doc:`WaterPoolConstruction/WaterPoolConstruction`


* FIXED : muon record animation debug : bizarre moving line issue. Why photons 
  resulting from muon have issue but other animations do not ?

  * HMM: working animations have all? been input photon running
  * DONE: numerical look as muon photon records and animation::

         ~/j/muon/muon.sh pdb

  * TODO: try default gamma animation

  * :doc:`muon/muon_propagation_animation_shakedown` 


