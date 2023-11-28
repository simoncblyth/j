overview
=========

Current Scripts
-----------------

::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh
   ~/j/jok.bash 
   ~/j/okjob.sh 

::

     jcv junoSD_PMT_v2_Opticks


DONE : revisit opticks-t
--------------------------

DONE : okdist updates
------------------------

DONE : forked opticks to opticks_ancient on bitbucket
--------------------------------------------------------

* https://bitbucket.org/simoncblyth/opticks_ancient/

Description of opticks_ancient on bitbuket::

    This opticks_ancient fork of opticks done Nov 3 2023 is to provide an easily
    visible record of inactive opticks packages that are soon to be removed from
    the primary opticks repository


DONE : created and tested binary release standalone opticks distribution 
----------------------------------------------------------------------------

DONE : more release GPU job tests : output checks beyond just ctest
---------------------------------------------------------------------

DONE : upload binary opticks distrib to /cvmfs/opticks.ihep.ac.cn  : just a mechanics test
-------------------------------------------------------------------------------------------

DONE :  generalized oktar.py for packing .opticks GEOM, curandState ...
-------------------------------------------------------------------------------------------

* decide on naming convention : probably follow juno+opticks release name 
  to reflect the geometry 

HMM : does a shared .opticks belong in /cvmfs OR /hpcfs ? 

Probably /hpcfs because for running large numbers of 
photons it needs to be big::

    /hpcfs/juno/junogpu/opticks/  ?   


DONE : .opticks location flexibility without changing HOME ?  
-------------------------------------------------------------

Split relatively "fixed" .opticks which make sense to be shared
from more transient .opticksrc that makes less sense to share.  

.opticks::

  GEOM
  rngcache  
  InputPhotons
  precooked

.opticksrc::

  scontext 


DONE : scontest_test investigate scontext/sdevice.bin of zero length 
-----------------------------------------------------------------------

DONE : building against the binary release : in examples/UseRelease
---------------------------------------------------------------------

Expt in R:BuildAgainstRelease and examples/UseRelease

HMM : maybe should include some source examples with the binary release ? 



DONE : consider if it make sense to include custom4 and optix7.5 into the opticks binary release ? 
----------------------------------------------------------------------------------------------------

custom4
   NO : it should not be included because junosw depends on that too, hence
   to ensure are using the same external and avoid version shear crashes need 
   to keep it separate so it gets configured once only  

optix7.5
   NO : just two directories with ~16 headers, this could be included 
   because the expectation is that only opticks depends on it 
   
   * BUT IT IS CLEARER TO JUST TO REFER TO SEPARATE /cvmfs WITH OPTIX  


DONE : switch from disc beam to surface of sphere radial generation
----------------------------------------------------------------------

* OLD:~/opticks/optixrap/cu/torchstep.h 
* ~/opticks/sysrap/tests/storch_test.sh 


DONE : get G4CXTest_GEOM operational with JUNO geometry for fast cycle 
------------------------------------------------------------------------

Follow approach of g4cx/tests/G4CXTest_raindrop.sh with g4cx/tests/G4CXTest_GEOM.sh

* :doc:`G4CXTest_GEOM`

* ~/opticks/g4cx/tests/G4CXTest_GEOM.sh


FIXED : Lifecycle Issue in tds3 gun running with jok-tds
-----------------------------------------------------------

* :doc:`EventAction_SensitiveDetector_SEvt_Lifecycle_issue`


DONE : get cxs_min.sh to do the same as the A side of G4CXTest_GEOM.sh : check match
---------------------------------------------------------------------------------------

Currently using input photons. Need to switch it to same torch as G4CXTest_GEOM. 
Hmm factor off the torch setup ?::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/CSGOptiX/cxs_min.sh ana 
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh


See :doc:`cxs_min_shakedown`



DONE : use NPFold stamp summary : sstampfold_report in jok.bash jobscript
-----------------------------------------------------------------------------


FIXED : ~/j/issues/jok_tds_discrepant_cerenkov.rst
-----------------------------------------------------

Needed to change the mtline mapping to creation not loading


DONE : revisit cxs_min.sh following lifecycle changes
-------------------------------------------------------------------------

::

    ~/opticks/CSGOptiX/cxs_min.sh 
    ~/opticks/CSGOptiX/cxs_min.sh report


* uses CSGOptiX::SimulateMain
* it stays working as using standard-ish genstep machinery 

::

    ~/opticks/CSGOptiX/cxs_min.sh 

    0169 void CSGOptiX::SimulateMain() // static
     170 {
     171     SEventConfig::SetRGModeSimulate();
     172     CSGFoundry* fd = CSGFoundry::Load();
     173     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     ...
     180     for(int i=0 ; i < SEventConfig::NumEvent() ; i++)
     181     {
     182         cx->simulate(i); 
     183     }   
     184 }   


DONE : revisit G4CXTest_GEOM following lifecycle changes
-------------------------------------------------------------------------

::

    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh 
    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh report 


    ~/opticks/notes/issues/G4CXTest_GEOM_num_photon_assert.rst


DONE : revisit opticks-t following lifecycle changes : 0/208 FAIL
-------------------------------------------------------------------

::

    opticks-t


WIP : revisit ~/j/okjob.sh with opticksMode 0,1,2 following lifecycle changes
----------------------------------------------------------------------------------

::

    OIM=1 ~/j/okjob.sh 
    OIM=2 ~/j/okjob.sh 
    OIM=3 ~/j/okjob.sh 

    GUN=2 ~/j/okjob.sh 

    ~/j/okjob.sh grab 
    ~/j/okjob.sh ana
    ~/j/okjob.sh init
    ~/j/okjob.sh report

* comparing 1 and 2 will give overall speedup, 
  compare that with speedup from opticksMode 3 


TODO : cross comparison of the A times, run profile stamps to measure gross timings 
----------------------------------------------------------------------------------------

+------+------------------------------------------+---------+--------------------------------------------------------------------+ 
|  idx |  script                                  | init(s) |                                                                    |
+======+==========================================+=========+====================================================================+
|  1   |  ~/j/okjob.sh                            |   149   |                                                                    |
+------+------------------------------------------+---------+--------------------------------------------------------------------+
|  2   |  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh   |   127   |  NOT SO USEFUL AS DID NOT IMPL GEANT4 BOOT FROM GENERAL GENSTEPS   |
+------+------------------------------------------+---------+--------------------------------------------------------------------+
|  3   |  ~/opticks/CSGOptiX/cxs_min.sh           |     2   |                                                                    |
+------+------------------------------------------+---------+--------------------------------------------------------------------+

Establishing correspondence between 1A and 3A is important because of the fast turnaround of 3A

* use gensteps from 1 as OPTICKS_INPUT_GENSTEP to 3


TODO : integratin hit check and clean up
-------------------------------------------

::

   jcv junoSD_PMT_v2_Opticks


TODO : RunMeta recording of initialization, total time
---------------------------------------------------------

* run level (initialization, total time) stamps 
* HMM: how/where to get initialization times into runmeta ? 




TODO : all three running types via okjob.sh ? 
-----------------------------------------------




TODO : L test
----------------


TODO : enhance sstampfold_report and sprof_fold_report 
---------------------------------------------------------------------------

Whats missing:

* BOA:B/A listing  
* photon counts summary 
* switches like PRODUCTION 
* improve plotting 
* summary grabbing 
* develop memory profile event-to-event presentation 
* look for leaks 



TODO : pump up the statistics while looking for leaks
--------------------------------------------------------


TODO : InputGensteps and InputPhotons different for a sequence of events, by folder config ?
-----------------------------------------------------------------------------------------------




TODO : check cost of the anamgr 
---------------------------------

Switching off the anamgr bound to speed up Geant4 running::

    jok-anamgr(){ cat << EOU
    --opticks-anamgr
    --no-anamgr-normal
    --no-anamgr-genevt
    --no-anamgr-edm-v2
    --no-anamgr-grdm
    --no-anamgr-deposit
    --no-anamgr-deposit-tt
    --no-anamgr-interesting-process
    --no-anamgr-optical-parameter
    --no-anamgr-timer
    EOU
       : opticks-anamgr is used by the U4Recorder
    }




TODO : CMake separate Debug and Release build tree ? Debug "release" ? 
-----------------------------------------------------------------------------

* https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20Debug%20and%20Release.html

::

    cd debug
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cmake --build .
    cd ../release
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cmake --build .



WIP : investigate slow sevt.py SAB chi2 comparison, maybe need to do that in C++ ?
--------------------------------------------------------------------------------------

* ~/opticks/thrustrap/TSparse_.cu : already have GPU impl of part of the task 

* check old OpIndexer 


TODO : junosw + opticks : profile iteration
-------------------------------------------

* mode:3 iterating with input photons giving factor of only 100x so far 
* iteration is hampered by 2-3min delay to initialize junosw


TODO : try nvidia profiling machinery
-------------------------------------------

TODO : junosw minor MR, custom4 update again (for C4Version.h) 
-----------------------------------------------------------------


TODO : junosw+opticks release : using opticks from /cvmfs/opticks.ihep.ac.cn 
------------------------------------------------------------------------------------

* would be best if the existing scripts can do this::
 
  /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh  

The above script is very high level : so no change needed

The junoenv scripts need small changes to get opticks from release dir 
on /cvmfs/opticks.ihep.ac.cn instead of getting from tarball or git clone 

::

   in principal the opticks build could be done via normal junoenv
   but thats not convenient while opticks needs frequent changes,
   so start with it separate 



TODO : workaround the github fork into same organization limitation 
----------------------------------------------------------------------

* simply add opticks_ancient and push ? 

TODO : tidy up opticks inactive packages 
---------------------------------------------


TODO : check using opticks python functionality from the release
------------------------------------------------------------------

Convert G4CXTest_raindrop.sh into a "user example" 


