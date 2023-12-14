overview
=========

Current Scripts
-----------------

::

   ~/opticks/sysrap/tests/sreport.sh 

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh

   LIFECYCLE=1 ~/opticks/g4cx/tests/G4CXTest_GEOM.sh

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


DONE : RunMeta recording of initialization, total time
---------------------------------------------------------

* run level (initialization, total time) stamps 
* HMM: how/where to get initialization times into runmeta ? 

::

   BP=SEvt::EndOfRun ~/j/okjob.sh 



PAUSE : revisit ~/j/okjob.sh with opticksMode 0,1,2 following lifecycle changes
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


OIM:1::

    NPFold::LoadNoData("/home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0")
    [sstampfold_report.run (1, )
     sstampfold_report.run.descMetaKV 
    NP::descMetaKV
               SEvt__Init_RUN_META :                               1701169873098353,880244,304188 :            0 : 2023-11-28T19:11:13.098353
                  SEvt__BeginOfRun :                            1701170021294552,10966808,4116388 :  148,196,199 : 2023-11-28T19:13:41.294552
     SEvt__beginOfEvent_FIRST_ECPU :                            1701170021294667,10966808,4116392 :  148,196,314 : 2023-11-28T19:13:41.294667
     SEvt__beginOfEvent_FIRST_EGPU :                            1701170021555760,11099780,4231124 :  148,457,407 : 2023-11-28T19:13:41.555760
        SEvt__endOfEvent_LAST_ECPU :                            1701170028403990,15950472,4237252 :  155,305,637 : 2023-11-28T19:13:48.403990
        SEvt__endOfEvent_LAST_EGPU :                            1701170028741358,15950472,4237252 :  155,643,005 : 2023-11-28T19:13:48.741358
                    SEvt__EndOfRun :                            1701170028741703,15950472,4237252 :  155,643,350 : 2023-11-28T19:13:48.741703

     sstampfold_report.run.descMetaKVS 
    NP::descMetaKVS
               SEvt__Init_RUN_META :      1701169873098353,880244,304188    2023-11-28T19:11:13.098353           0            
                  SEvt__BeginOfRun :   1701170021294552,10966808,4116388    2023-11-28T19:13:41.294552 148,196,199 148,196,199
     SEvt__beginOfEvent_FIRST_ECPU :   1701170021294667,10966808,4116392    2023-11-28T19:13:41.294667 148,196,314         115
     SEvt__beginOfEvent_FIRST_EGPU :   1701170021555760,11099780,4231124    2023-11-28T19:13:41.555760 148,457,407     261,093
        SEvt__endOfEvent_LAST_ECPU :   1701170028403990,15950472,4237252    2023-11-28T19:13:48.403990 155,305,637   6,848,230
        SEvt__endOfEvent_LAST_EGPU :   1701170028741358,15950472,4237252    2023-11-28T19:13:48.741358 155,643,005     337,368
                    SEvt__EndOfRun :   1701170028741703,15950472,4237252    2023-11-28T19:13:48.741703 155,643,350         345
    ]sstampfold_report.run 


OIM:3::

    sstampfold_report.run.descMetaKVS 
    NP::descMetaKVS
               SEvt__Init_RUN_META :      1701170623369659,880244,304216    2023-11-28T19:23:43.369659           0            
                  SEvt__BeginOfRun :   1701170772822060,10966924,4116380    2023-11-28T19:26:12.822060 149,452,401 149,452,401
     SEvt__beginOfEvent_FIRST_ECPU :   1701170772822156,10966924,4116384    2023-11-28T19:26:12.822156 149,452,497          96
     SEvt__beginOfEvent_FIRST_EGPU :   1701170773988756,11100632,4239468    2023-11-28T19:26:13.988756 150,619,097   1,166,600
        SEvt__endOfEvent_LAST_ECPU :   1701170786703766,15951820,4246988    2023-11-28T19:26:26.703766 163,334,107  12,715,010
        SEvt__endOfEvent_LAST_EGPU :   1701170786831256,15951820,4246988    2023-11-28T19:26:26.831256 163,461,597     127,490
                    SEvt__EndOfRun :   1701170786831408,15951820,4246988    2023-11-28T19:26:26.831408 163,461,749         152
    ]sstampfold_report.run 




DONE : compare initialization times, and A simulate times
-----------------------------------------------------------

+------+------------------------------------------+---------+--------------------------------------------------------------------+ 
|  idx |  script                                  | init(s) |                                                                    |
+======+==========================================+=========+====================================================================+
|  1   |  ~/j/okjob.sh                            |   149   |                                                                    |
+------+------------------------------------------+---------+--------------------------------------------------------------------+
|  2   |  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh   |   127   |  CAN USE FOR TORCH COMPARISON, NOT GENERAL GENSTEP                 |
+------+------------------------------------------+---------+--------------------------------------------------------------------+
|  3   |  ~/opticks/CSGOptiX/cxs_min.sh           |     2   |  OPTICKS_INPUT_GENSTEP from okjob.sh                               |
+------+------------------------------------------+---------+--------------------------------------------------------------------+

Establishing correspondence between 1A and 3A is important because of the fast turnaround of 3A

* now getting perfect photon + hit match between 1A and 3A  
* A timings are close between 1 and 3 


FIXED : BY CLEAN JUNOSW BUILD : investigate difference in hit counts between 1 and 3 
------------------------------------------------------------------------------------------

* presumably this was due to NP.hh version shear

Workstation::

    ~/j/okjob.sh
    ~/opticks/CSGOptiX/cxs_min.sh

Laptop::

    ~/j/okjob.sh grab
    ~/opticks/CSGOptiX/cxs_min.sh grab

    ~/opticks/CSGOptiX/cxs_min.sh ana
    ~/opticks/CSGOptiX/cxs_min.sh report

    ~/j/okjob.sh ana
    ~/j/okjob.sh report



TODO : integration hit check and clean up : following lifecycle changes
--------------------------------------------------------------------------

::

   jcv junoSD_PMT_v2_Opticks


TODO : all three running types via okjob.sh ? to enable testing on L
--------------------------------------------------------------------------



FIXED : subcounts table broken for G4CXTest_GEOM.sh because Geant4 side has no hit.npy
---------------------------------------------------------------------------------------

* :doc:`lack-of-B-side-hit`

Appears to be limitation B side needs photons, so switch to HitAndPhoton mode::

    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh report 
    JOB=N1 ~/opticks/sysrap/tests/sstampfold_report.sh 
    JOB=N2 ~/opticks/sysrap/tests/sstampfold_report.sh 

    JOB=N1 ~/opticks/sysrap/tests/sstampfold_report.sh build_runo



DONE : event-by-event changing photon count in  ~/opticks/CSGOptiX/cxs_min.sh torch running 
----------------------------------------------------------------------------------------------

* aiming for time/memory vs photon count plots 

* DONE sstr::ParseIntSpecList
* DONE SEventConfig::NumPhoton(0)   OPTICKS_NUM_PHOTON=M1,2 SEventConfigTest 
* DONE SEvent::MakeGenstep using above  

::

   ~/opticks/CSGOptiX/cxs_min.sh
   ~/opticks/CSGOptiX/cxs_min.sh ana


DONE : compare cxs_min.sh StandardFullDebug and Minimal 
---------------------------------------------------------

::

   VERSION=0 ~/opticks/CSGOptiX/cxs_min.sh   ## Minimal
   VERSION=1 ~/opticks/CSGOptiX/cxs_min.sh   ## HitOnly
   VERSION=2 ~/opticks/CSGOptiX/cxs_min.sh   ## HitAndPhoton
   VERSION=99 ~/opticks/CSGOptiX/cxs_min.sh  ## StandardFullDebug 

* changing the SEvt arrays that are gathered and saved has minimal effect on the measured event times
  so pick VERSION=2 HitAndPhoton for now : as one that doesnt write GB and yet still has some counts to check `


DONE : cxs_min.sh bump up to 3M and make photon vs time plots 
--------------------------------------------------------------------

::

    ~/opticks/CSGOptiX/cxs_min.sh report

    ~/opticks/sysrap/tests/sreport.sh 

    JOB=N3 ~/opticks/sysrap/tests/sreport.sh ana
        ## HMM: looking rather linear in the up to 3M range 


DONE : make plotting work from the _sreport folder alone
-----------------------------------------------------------

* seems thats working already : by design 

::

    ~/opticks/sysrap/tests/sreport.sh grab 
    ~/opticks/sysrap/tests/sreport.sh ana


DONE : cxs_min.sh bump up to 100M whilst working on subprofile reporting to look for leaks
---------------------------------------------------------------------------------------------

* leak plotting : see no sign of uptrend, but it is large  : normal CUDA large VM, RSS flat  

::

    ~/opticks/sysrap/tests/sreport.sh grab 
    ~/opticks/sysrap/tests/sreport.sh ana


DONE : repeat scan with  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh for A and B plots 
--------------------------------------------------------------------------------------------------

* only reached 80M due to memory leak apparent in ~/opticks/g4cx/tests/G4CXTest_GEOM.sh (not in cxs_min.sh)

::

    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh report



DONE : consolidated sstampfold_report and sprof_fold_report into sreport
---------------------------------------------------------------------------

Whats missing:

* DONE : improve plotting 
* DONE : summary grabbing 
* DONE : develop memory profile event-to-event presentation 

* DONE : photon/hit/record/... counts summary table 
* DONE : BOA:B/A listing  
* DONE : reposition context metadata to run, not each evt fold 
* DONE : include switches like PRODUCTION and other metadata like the GPU name in context metadata, not event fold 

* DONE : include collected counts in SEvt/NPFold metadata, as do not want to allways gather the large photons array
         (actually I added to gensteps metadata, but could be elsewhere too)




DONE : improve plots+report using context metadata
--------------------------------------------------------

* context metadata into titles
* add screenshot/saving 
* make reference set for presentation before any optimization attempts



TODO : G4CXTest prone to memory error : need to write run meta at end of every event
---------------------------------------------------------------------------------------


TODO : recheck EGPU event time match between the two scripts
--------------------------------------------------------------

::

   ~/opticks/CSGOptiX/cxs_min.sh info_env
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh info_env


::

    143
    529

    ~400



WIP : find G4CXTest leaks
-----------------------------

* :doc:`G4CXTest_find_the_leak`


WIP : QEvent/SEvent Lifecycle simplify : can ECPU/EGPU beginOfEvent vs setGenstep be made the save : to avoid confusion
---------------------------------------------------------------------------------------------------------------------------

1. QEvent::setGenstep : get direct from vecs, no intermediate NP, no clear
1. QSim::simulate  : move QEvent::setGenstep before SEvt::beginOfEvent

Split clearing::

    clear_genstep
    clear_output 

::

     ECPU.begin



     ECPU.end
     EGPU.begin


     EGPU.end


TODO: get rainbow going for fast cycle lifecycle shakedown 
-------------------------------------------------------------


DONE : OPTICKS_MAX_BOUNCE scanning
------------------------------------

* ~/opticks/notes/issues/OPTICKS_MAX_BOUNCE_scanning.rst


TODO : WITH_CUSTOM4 PRODUCTION SWITCH IMPACT
-----------------------------------------------


DONE : total time accounting + overall speedup machinery
----------------------------------------------------------

* collect+present launch times : relate those to total times : DO MORE THAN THAT:
* use cxs_min.sh for fast dev 

Get per event and total times into categories::

    init 
    
    upload
    kernel
    download
    save        ## thats a debugging activity 

    other       ## rest of event, will be small with cxs_min.sh 


* did this in::

   NP::MakeMetaKVS_ranges
   sysrap/tests/sreport.cc 
   ~/o/sreport.sh ana


TODO : Check perf with POM disabled NOT WITH_CUSTOM4
-------------------------------------------------------

* shorter photon histories, plus less resource kernel could easily give factor 3-4


TODO : NOT WITH_CUSTOM4 BUILD INTO SEPARATE FOLDER
----------------------------------------------------


* HUH: SLIGHTLY SLOWER NOT WITH_CUSTOM4
* TODO: compare seq between these 


TODO : compare Ctx log between Debug and Release
----------------------------------------------------

DONE : write the Ctx log to file
-----------------------------------


::

    N[blyth@localhost ALL1]$ cat CSGOptiX__Ctx.log
    [Ctx::GetLOG
    [ 4][       KNOBS]: All knobs on default.

    [ 4][  DISK CACHE]: Opened database: "/var/tmp/OptixCache_blyth/optix7cache.db"
    [ 4][  DISK CACHE]:     Cache data size: "44.0 MiB"
    [ 4][   DISKCACHE]: Cache hit for key: ptx-2347081-keydc3d249e4661531304a3dc0bc6f7eb89-sm_75-rtc1-drv515.43.04
    [ 4][COMPILE FEEDBACK]: 
    [ 4][COMPILE FEEDBACK]: Info: Pipeline has 1 module(s), 4 entry function(s), 3 trace call(s), 0 continuation callable call(s), 0 direct callable call(s), 3546 basic block(s) in entry functions, 41354 instruction(s) in entry functions, 7 non-entry function(s), 53 basic block(s) in non-entry functions, 627 instruction(s) in non-entry functions, no debug information

    ]Ctx::GetLOG
    N[blyth@localhost ALL1]$ 



WIP : HUNT FOR f64 IN PTX
----------------------------

* see ~/opticks/notes/issues/oxrap-hunt-for-f64-in-ptx.rst

::

    epsilon:opticks blyth$ opticks-ptx
                       BASH_SOURCE : /Users/blyth/opticks/opticks.bash 
                          FUNCNAME : opticks-ptx 
                               ptx : /tmp/CSGOptiX_generated_CSGOptiX7.cu.ptx 
                  num_printf_lines :       95 
                     num_f64_lines :      518 
    epsilon:opticks blyth$ 



TODO: OPTICKS_BUILDTYPE=Release into separate OPTICKS_PREFIX
------------------------------------------------------------------------

S:.opticks_build_config::

     export OPTICKS_BUILDTYPE=Release
     #export OPTICKS_BUILDTYPE=Debug
     export OPTICKS_PREFIX=/data/simon/local/opticks_${OPTICKS_BUILDTYPE}

S:.opticks_usage_config::

    #source /data/simon/local/opticks_Debug/bashrc
    source /data/simon/local/opticks_Release/bashrc     


      
Compare Release and Debug on S
---------------------------------

::

    JOB=N7 PLOT=Substamp_ALL_Etime_vs_Photon ~/o/sreport.sh
    JOB=S7 PLOT=Substamp_ALL_Etime_vs_Photon ~/o/sreport.sh


::

    [simon@localhost ~]$ opticks-ptx
                       BASH_SOURCE : /home/simon/opticks/opticks.bash 
                          FUNCNAME : opticks-ptx 
                               ptx : /data/simon/local/opticks_Release/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx 
                  num_printf_lines : 4 
                     num_f64_lines : 8 
    [simon@localhost ~]$ 


    [simon@localhost ~]$ opticks-ptx
                       BASH_SOURCE : /home/simon/opticks/opticks.bash 
                          FUNCNAME : opticks-ptx 
                               ptx : /data/simon/local/opticks_Debug/ptx/CSGOptiX_generated_CSGOptiX7.cu.ptx 
                  num_printf_lines : 95 
                     num_f64_lines : 518 
    [simon@localhost ~]$ 


TODO : sevent.h sctx.h need some production thinning 


   

DONE : Release build on S 
-----------------------------

* lots of warnings took ages to fix

runtime issue with sreport::

    export sreport_Creator__VERBOSE=1


::

    2023-12-08 22:20:53.731  731475385 : ]/home/simon/o/cxs_min.sh 
    [sreport.main  argv0 sreport dirp /data/simon/opticks/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL1 is_executable_sibling_path NO 
    [sreport.main : CREATING REPORT 
    [sreport_Creator::sreport_Creator
    -sreport_Creator::init.0
    -sreport_Creator::init.1
    -sreport_Creator::init.2
    -sreport_Creator::init.3
    NPFold::SubCommonKV MISSING KEY  num_sub 20 num_ukey 25t_setGenstep_0-
    /home/simon/o/cxs_min.sh sreport error
    [simon@localhost ~]$ 

HMM: the Release outputs missing the t_setGenstep keys, because of::

     185 int QEvent::setGenstep()  // onto device
     186 {   
     187     LOG_IF(info, SEvt::LIFECYCLE) << "[" ;
     188 
     189 #ifndef PRODUCTION 
     190     sev->t_setGenstep_0 = sstamp::Now();
     191 #endif

BUT sreport must have been reading metadata from a mix
of SEvt from Release and Debug runs leading to the 
inconsistency and key error. 

So the problem is fixed by cleaning up the output directories and
running again.


DONE : presentation of total time accounting in Ranges_SPAN 
-----------------------------------------------------------------------

::

   PLOT=Ranges_SPAN ~/o/sreport.sh


TODO : validation comparison : need seq.npy for histories
-------------------------------------------------------------


WIP : extend total time accounting to B with G4CXTest_GEOM.sh
----------------------------------------------------------------

* need SProf::Add on the B side 




DONE : ~/o/ana/amdahl.sh plot
---------------------------------

DONE : pure and simple times versus num TORCH photon all that way to 100M
----------------------------------------------------------------------------




TODO : check --optix-ir performance : see p42 of optix7-pdf
-------------------------------------------------------------

p43

To profile your code with Nsight Compute,11 enable --generate-line-info and set
debugLevel = OPTIX_COMPILE_DEBUG_LEVEL_MODERATE in both the
OptixModuleCompileOptions and OptixPipelineLinkOptions in your application host
code.

TODO : vary PIP compile options
--------------------------------

* forum optimization search 

* https://forums.developer.nvidia.com/t/optix-7-5-payload-type-mismatch-errors-when-using-optix-ir/218138




DONE : Illustrative hit plot
-----------------------------

DONE : hit time for large seqnib
----------------------------------

::

    ~/o/cxs_min.sh 

    VERSION=3  
    OPTICKS_EVENT_MODE=HitPhotonSeq
    OPTICKS_NUM_EVENT=10
    OPTICKS_NUM_PHOTON=H1:10
    OPTICKS_MAX_PHOTON=M1 

    ~/o/cxs_min.sh 
    ~/o/cxs_min.sh grab 

    PLOT=thit MODE=2 ~/o/cxs_min.sh 
    PLOT=thit MODE=2 EVT=A009 ~/o/cxs_min.sh




TODO : RTX 8000 test : it has 48G (so can extend to 400M, TITAN RTX limited to 200M)
--------------------------------------------------------------------------------------

* repeat cxs_min.sh and extend up to 400M (also compare to TITAN RTX)  


TODO : GPU cluster test
-------------------------




TODO : event-by-event changing photon count in ~/j/okjob.sh torch running ??
-------------------------------------------------------------------------------

* bit more tricky (mock curand) : but its works with input photons so it should be possible 
* maybe more hassle that its worth : as  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh  should be straightforward


TODO : impl InputGensteps and InputPhotons for a sequence of events, by folder config
---------------------------------------------------------------------------------------

* just need to load genstep/inphotons with the event index, quite similar to photon scanning of torch running 


TODO : check cost of the anamgr 
---------------------------------

Switching off the anamgr bound to speed up Geant4 running

* so to some extent the comparison is currently unfair 

::

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


