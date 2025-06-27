ISSUES
==========

* B side WP_PMT input photons get minimal intersects

  * :doc:`InputPhotonsCheck/InputPhotonsCheck_WP`
  * only geometry "seen" by input photons on B side is sOuterWaterPool 
  * this is bizarre as B side works fine from other positions ? 
  * TODO: default gamma near WP_PMT


* Geant4 track label compatibility to enable opticksMode:3 and 
  EPH monitoring to not force switching off all other AnaMgr 
  than the U4RecorderAnaMgr
  
  * careful track labels are used all over the place (eg C4)
    and within JUNOSW often without the precaution of using dynamic_cast 
    so the track info can easily cause crashes  

* gitlab runner with GPU to enable starting a collection of 
  many automated A:B tests 

* Chimney : major detector geometry overhaul


* running with array recording eg with DebugLite is prone to VRAM OOM
  requining manual setting of eg::

        export OPTICKS_MAX_SLOT=M10

  * need to automatically reduce MAX_SLOT when running with array recording
  * :doc:`muon/OOM_with_debug_arrays_enabled`



FIXED ISSUES
--------------

* FIXED : muon record animation debug : bizarre moving line issue. Why photons 
  resulting from muon have issue but other animations do not ?

  * HMM: working animations have all? been input photon running
  * DONE: numerical look as muon photon records and animation::

         ~/j/muon/muon.sh pdb

  * TODO: try default gamma animation

  * :doc:`muon/muon_propagation_animation_shakedown` 


