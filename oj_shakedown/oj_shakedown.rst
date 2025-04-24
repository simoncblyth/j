oj_shakedown
=============

Using oj/oj.sh from oj repo (and ok/ok.sh from ok repo) for envsetup and test control
----------------------------------------------------------------------------------------

::

     git@code.ihep.ac.cn:blyth/oj.git
     git@code.ihep.ac.cn:blyth/ok.git


check some jok.bash validations with oj release on A
--------------------------------------------------------

0. DONE : viz : generalize cxr_min.sh and install it, making to work with released executables and geometry
1. WIP : cxt_min.sh : try to make simtrace work from distrib
2. input photons
3. torch running
4. OPTICKS_INTEGRATION_MODE 3 : U4Recorder A and B
5. get opticks-t to succeed from install tree


oj script running issues
-------------------------

* FIXED mixed GEOM :doc:`oj_shakedown_G4CXTest_raindrop_geom_mixup` 


oj cxt_min.sh simtrace
-------------------------

* not going to include matplotlib/pyvista : thats left to the user, but 
  document how to use external ipython/python executables together 
  with OJ release 

HMM : little sense testing simtrace at OJ level, instead cycle at OK level





repeat those release checks on GPU cluster : start from okjob.sh
------------------------------------------------------------------







