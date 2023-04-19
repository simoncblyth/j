blyth-88-resolve-merge-conflicts-or-change-branch-to-avoid
=============================================================


Issue
--------


GitLab UI says:

   Merge blocked: merge conflicts must be resolved.      [Resolve Locally]  [*Resolve conflicts*]  

   Merge details

   The source branch is 42 commits behind the target branch
   1 commit and 1 merge commit will be added to main (squashes 50 commits).
   Source branch will be deleted.

   Mentions issue #88 


Refs
--------

* https://docs.gitlab.com/ee/user/project/merge_requests/conflicts.html#resolve-conflicts-from-the-command-line
* https://gitlab.com/gitlab-org/gitlab/-/issues/347154


Rebase vs Merge
-------------------

* BUT: I just want to handle a single file with conflicts, so that stuff is not relevant


Investigations
------------------

TIP: do this simulatenously on laptop (for main) and on workstation (for my branch)
so can run the same command against the two branches to get familiar with the diffs. 

::

    epsilon:junosw blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.

    epsilon:junosw blyth$ git log b4e0^.. --name-status


List the files with changes in common that might cause conflit::

    git diff b4e0.. cmake/JUNODependencies.cmake        # added NuWro, added Custom4 : expect auto-merging would work 



    epsilon:junosw blyth$ git diff b4e0.. Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    diff --git a/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h b/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    index ec62299..c6e299a 100644
    --- a/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    +++ b/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    @@ -229,9 +229,14 @@ PMTSimParamData::get_pmtContiguousIndex
     inline int PMTSimParamData::get_pmtContiguousIndex(int pmtid) const
     {
         int idx = -1 ;  
    -    if(      pmtid < kOFFSET_WP_PMT ) idx = pmtid ;    // LPMT 
    -    else if( pmtid < kOFFSET_CD_SPMT) idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    -    else                              idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    +    if(PMT::IsCD(pmtid) and PMT::Is20inch(pmtid)) {
    +        idx = pmtid ;    // LPMT 
    +    } else if(PMT::IsWP(pmtid)) {
    +        idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    +    } else if (PMT::IsCD(pmtid) and PMT::Is3inch(pmtid)){
    +        idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    +    }
    +
         return idx ;     
     }
     
    epsilon:junosw blyth$ 


HMM, my changes are marginal (just debug, notes) can just drop them : ADOPT MAIN INTO MY BRANCH


DONE : Work out what are the changed files in common
--------------------------------------------------------

Previously (from my email on April 6th):: 

    Another question, my branch blyth-88 for the PMT geometry pivot is now rather old, 
    diff below. 

    I expect commits to main like your copy number changes will be changing
    some of the same lines that my branch does.

    Comparing my branch with main I think the below may
    need manual attention to bring together the changes. 

    Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                       |  24 ++- 
    Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc                             | 138 ++++++++--------
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h           |  11 +-

    Do you recommend me to make such preparations in my branch ?  
    Or do you prefer to do that resolution when doing the merge ? 


    epsilon:junosw blyth$ branch=blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ git diff --name-status main..$branch 
    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    A       Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    A       Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    M       Simulation/DetSimV2/PMTSim/CMakeLists.txt
    A       Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h
    A       Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
    M       Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    A       Simulation/DetSimV2/PMTSim/include/ModelTrigger_Debug.h
    M       Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    M       Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
    M       Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    M       Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    M       Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    M       Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    M       Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    M       Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    M       Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    M       Simulation/DetSimV2/PhysiSim/CMakeLists.txt
    M       Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    M       Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    A       Simulation/DetSimV2/SimUtil/SimUtil/S4Touchable.h
    M       Simulation/GenTools/GenTools/GtOpticksTool.h
    M       Simulation/GenTools/src/GtOpticksTool.cc
    M       Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/MultiFilmModel.h
    A       Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/_TComplex.h
    M       Simulation/SimSvc/MultiFilmSimSvc/src/Material.h
    M       Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.h
    M       Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
    M       Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
    A       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/IPMTAccessor.h
    A       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    M       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    M       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h
    M       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h
    M       Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
    M       Utilities/EGet/EGet/EGet.h
    M       cmake/JUNODependencies.cmake
    epsilon:junosw blyth$ 



Now fetch origin and check again::

    epsilon:junosw blyth$ git fetch origin
    epsilon:junosw blyth$ git branch 
    * blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
      main
    epsilon:junosw blyth$ git checkout main
    Switched to branch 'main'
    Your branch is behind 'origin/main' by 14 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)
    epsilon:junosw blyth$ git pull 
    ...


Look at my branch since the last common commit::

    git log b4e0^..       # the ^ includes the changes of that common commit 
    git diff b4e0^..
    git diff b4e0.. --name-status   # names status of files with changes since common ancestor


::

    N[blyth@localhost junosw]$ mkdir /tmp/conflict
    N[blyth@localhost junosw]$ git diff b4e0.. --name-only > /tmp/conflict/branch.log

    epsilon:junosw blyth$ mkdir /tmp/conflict 
    epsilon:junosw blyth$ git diff b4e0.. --name-only > /tmp/conflict/main.log 
    epsilon:junosw blyth$ scp P:/tmp/conflict/branch.log /tmp/conflict/

    epsilon:conflict blyth$ grep -xF -f branch.log main.log 

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h       ### DONE : adopt main
    Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                   ### DONE : manual combine
    cmake/JUNODependencies.cmake                                            ### DOME : manual combine 

    Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc                         ### needs line-by-line





DONE : Adopt main version of PMTSimParamData.h onto branch
--------------------------------------------------------------

::

    epsilon:junosw blyth$ git add . 
    epsilon:junosw blyth$ git commit -m "adopt the main version of PMTSimParamData.h using PMT::IsCD etc.. onto the branch to avoid conflict"
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess d2e596e] adopt the main version of PMTSimParamData.h using PMT::IsCD etc.. onto the branch to avoid conflict
     1 file changed, 8 insertions(+), 21 deletions(-)
    epsilon:junosw blyth$ git push 
    Counting objects: 7, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (7/7), done.
    Writing objects: 100% (7/7), 1002 bytes | 1002.00 KiB/s, done.
    Total 7 (delta 4), reused 0 (delta 0)
    remote: 
    remote: View merge request for blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/180
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       d00617f..d2e596e  blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ 





DONE : manual combine for the easy two
---------------------------------------------

Make copies of the versions from main::

    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch main
    Your branch is up-to-date with 'origin/main'.

    nothing to commit, working tree clean
    epsilon:junosw blyth$ jo

    epsilon:junosw blyth$ mkdir /tmp/conflict/main
    epsilon:junosw blyth$ cp cmake/JUNODependencies.cmake /tmp/conflict/main/
    epsilon:junosw blyth$ cp Examples/Tutorial/python/Tutorial/JUNODetSimModule.py /tmp/conflict/main/

    epsilon:junosw blyth$ git checkout $branch 
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.
    epsilon:junosw blyth$ 

::

     vimdiff cmake/JUNODependencies.cmake /tmp/conflict/main/JUNODependencies.cmake

     # zR to unfold all 

     vimdiff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py /tmp/conflict/main/JUNODetSimModule.py



::

    epsilon:junosw blyth$ git add . 
    epsilon:junosw blyth$ git commit -m "bring changes from main since last common commit b4e0 over into the branch, in attempt to avoid merge conflict for these two files"
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 4426a20] bring changes from main since last common commit b4e0 over into the branch, in attempt to avoid merge conflict for these two files
     2 files changed, 63 insertions(+), 6 deletions(-)
    epsilon:junosw blyth$ git push 
    Counting objects: 9, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (8/8), done.
    Writing objects: 100% (9/9), 1.80 KiB | 1.80 MiB/s, done.
    Total 9 (delta 7), reused 0 (delta 0)
    remote: 
    remote: View merge request for blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/180
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       d2e596e..4426a20  blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ 



DONE : junoSD_PMT_v2.cc line-by-line combination (in the branch)
-------------------------------------------------------------------

* my changes are instrumentation and clean up


git diff b4e0.. Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
  
      main : lots of use of PMT:: and reformating 

::

    epsilon:junosw blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw blyth$ cp Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc /tmp/conflict/

    epsilon:junosw blyth$ git checkout $branch 
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.
    epsilon:junosw blyth$ 


**aim of the game is to make the diff with main simpler : such that the gitlab merge can succeed**

::

    epsilon:junosw blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw blyth$ jcv junoSD_PMT_v2
    2 files to edit
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    epsilon:junosw blyth$ diff Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc /tmp/conflict/junoSD_PMT_v2.cc
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git checkout $branch 
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ vimdiff Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc /tmp/conflict/junoSD_PMT_v2.cc



DONE : find common ancestor commit between branch and main with "git lga"
----------------------------------------------------------------------------


branch:: 

    * 2ab30fa - fix without Opticks build fail with preprocessor macros in PMTAccessor::LoadPMTSimParamData, quell some compilation warnings (8 weeks ago) <Simon C Blyth>
    * fce28c0 - start integration of CustomG4OpBoundaryProcess using IPMTAccessor/PMTAccessor connector created from PMTSimParamData struct obtained from the PMTSimParamSvc (8 
    weeks ago) <Simon C Blyth>
    * e843201 - change classname to CustomG4OpBoundaryProcess for clarity (8 weeks ago) <Simon C Blyth>
    * 636e78a - bring in original Geant4 1042 G4OpBoundaryProcess under different name, ready for customization (8 weeks ago) <Simon C Blyth>

    ///////////////////////////////////

    *   b4e0089 - Merge branch 'yangyixiang_junosw_OnlineBuilding' into 'main' (8 weeks ago) <lintao@ihep.ac.cn>
    |\  
    | * 75ec43a - Add building test to CI/CD for online OEC (8 weeks ago) <yangyixiang@ihep.ac.cn>
    * |   580e219 - Merge branch 'quzhenning-FCPC-preselect-gentool' into 'main' (8 weeks ago) <lintao@ihep.ac.cn>
    |\ \  
    | |/  
    |/|   
    | * c9f9007 - A gentool to pre-select FC events of atmospheric neutrino (8 weeks ago) <quzn@ihep.ac.cn>
    |/  


main::


    * |   45a145e - Merge branch 'huyuxiang-update-dccomputing-oum-branch' into 'main' (7 weeks ago) <lintao@ihep.ac.cn>
    |\ \  
    | |/  
    |/|   
    | * 562c88f - update the script of detsim in dccomputing suggested by Xuefeng. (7 weeks ago) <huyuxiang@ihep.ac.cn>
    |/  

    ////////////////////////////////

    *   b4e0089 - Merge branch 'yangyixiang_junosw_OnlineBuilding' into 'main' (8 weeks ago) <lintao@ihep.ac.cn>
    |\  
    | * 75ec43a - Add building test to CI/CD for online OEC (8 weeks ago) <yangyixiang@ihep.ac.cn>
    * |   580e219 - Merge branch 'quzhenning-FCPC-preselect-gentool' into 'main' (8 weeks ago) <lintao@ihep.ac.cn>
    |\ \  
    | |/  


    15c8a1 Updates for variables used to record time and memory consumptions for some algorithms
    5680660 Merge branch 'lintao-add-radiodecay-tracks' into 'main'
    ea8dd70 WIP: optimize simulation framework to better support radioactivity decay.
    abdf390 (origin/98-slow-performance-and-warnings-in-running-tut_elec2rec-py-script-with-the-latest-gitlab-software) Merge branch 'issue-93-oec-initialization-bug' into 'main'
    d32c2ce Issue 93 oec initialization bug
    60269a7 Merge branch 'dingxf-nusol-bugfix-issue-85' into 'main'
    43ddf9b bug fix for solar neutrino generator #85
    45a145e Merge branch 'huyuxiang-update-dccomputing-oum-branch' into 'main'
    562c88f update the script of detsim in dccomputing suggested by Xuefeng.
    b4e0089 Merge branch 'yangyixiang_junosw_OnlineBuilding' into 'main'
    75ec43a Add building test to CI/CD for online OEC
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git --no-pager log b4e0^.. --pretty="oneline" --abbrev-commit


DONE : look at changes in main
---------------------------------

::

    epsilon:junosw blyth$ git log b4e0^.. Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    commit 1e84f1b6f2f5af8d3f21afe0a270701aa0d327f8
    Author: lintao@ihep.ac.cn <lintao@ihep.ac.cn>
    Date:   Fri Mar 31 06:49:33 2023 +0000

        WIP: start to improve the copy number related code.

    commit ea8dd70c054ae2e64949f38847c5ced283e879d5
    Author: lintao@ihep.ac.cn <lintao@ihep.ac.cn>
    Date:   Tue Mar 28 00:50:51 2023 +0000

        WIP: optimize simulation framework to better support radioactivity decay.
    epsilon:junosw blyth$ 

::

    git diff b4e0^..ea8d Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc  ## just formatting
    git diff ea8d..1e84 Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc   ## PMT::Is and more formatting


DONE : look at changes in branch
------------------------------------

::

    epsilon:junosw blyth$ git checkout $branch 
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.
    epsilon:junosw blyth$ 


    epsilon:junosw blyth$ git lg b4e0^.. Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    * 2023-04-14 63b8811 - opticksMode:0 now needs junoSD_PMT_v2_Opticks::Initialize to SEvt::TimerStart (4 days ago) <Simon C Blyth>
    * 2023-04-14 f12624a - add timing metadata to junoSD_PMT_v2_Opticks::EndOfEvent_Debug (4 days ago) <Simon C Blyth>
    * 2023-04-13 a516047 - move the debug into junoSD_PMT_v2_Opticks::EndOfEvent (5 days ago) <Simon C Blyth>
    * 2023-04-11 1dcf9f0 - debug difference between opticksMode:0 and opticksMode:2 with j/mtds/mtds.sh and jxv:mtds0 mtds2 find 20-30% more random consumption with 2 using S4RandomArray (7 days ago) <Simon C Blyth>
    * 2023-04-10 8a120f8 - checking without WITH_G4CXOPTICKS reveals an undefined (8 days ago) <Simon C Blyth>
    * 2023-04-10 efe89fa - zero junoSD_PMT_v2_Debug struct at EndOfEvent (8 days ago) <Simon C Blyth>
    * 2023-04-10 f245701 - ProcessHits logging LEVEL control within WITH_G4CXOPTICKS (8 days ago) <Simon C Blyth>
    * 2023-04-07 e174128 - higher level C4 using C4Track, remove old WITH_G4OPTICKS blocks (11 days ago) <Simon C Blyth>
    * 2023-03-31 a18eb58 - junoSD_PMT_v2::ProcessHits debug using EPH enumeration of ProcessHits returns (3 weeks ago) <Simon C Blyth>
    * 2023-03-26 da6a653 - avoid second SEvt instanciation in LSExpDetectorConstruction_Opticks when U4Recorder already instanciated it (3 weeks ago) <Simon C Blyth>
    * 2023-03-24 4624121 - more migration to Custom4 (4 weeks ago) <Simon C Blyth>
    epsilon:junosw blyth$ 




DONE : Check by comparing with the file from main
----------------------------------------------------

The diff should now be just my changes on top of the latest main::

    epsilon:junosw blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git show main:Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc > /tmp/conflict/junoSD_PMT_v2.cc 
    epsilon:junosw blyth$ vimdiff Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc /tmp/conflict/junoSD_PMT_v2.cc 


::

    epsilon:junosw blyth$ git add . 
    epsilon:junosw blyth$ git commit -m "adopt junoSD_PMT_v2.cc PMT::IsCD etc.. and format updates from main into branch, to give merge a better chance to succeed "
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 5b734ba] adopt junoSD_PMT_v2.cc PMT::IsCD etc.. and format updates from main into branch, to give merge a better chance to succeed
     1 file changed, 96 insertions(+), 83 deletions(-)
    epsilon:junosw blyth$ git push 
    Counting objects: 7, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (7/7), done.
    Writing objects: 100% (7/7), 1.27 KiB | 1.27 MiB/s, done.
    Total 7 (delta 6), reused 0 (delta 0)
    remote: 
    remote: View merge request for blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/180
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       4426a20..5b734ba  blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ 





HMM : Anything needed to make GitLab MR UI peachy, docs not clear 
---------------------------------------------------------------------

* https://docs.gitlab.com/ee/user/project/merge_requests/conflicts.html


Use experience from dry run merges to attempt to avoid merge conflict
------------------------------------------------------------------------

Use experience gleaned from dry run merges to craft a commit that 
should avoid  merge conflict.

* :doc:`blyth-88-dry-run-merge-in-tmp-junosw-check`
* :doc:`blyth-88-another-dry-run-merge-in-tmp-junosw-check2` 

::

    epsilon:junosw blyth$ git add . 
    epsilon:junosw blyth$ git commit -m "avoid merge conflict by renaming old method to WHEEL_IN_OLD_METHOD_TO_AVOID_MERGE_CONFLICT_setup_generator_opticks and chomp the eol on cmake/JUNODependencies.cmake see https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/106 "
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 9869e7d] avoid merge conflict by renaming old method to WHEEL_IN_OLD_METHOD_TO_AVOID_MERGE_CONFLICT_setup_generator_opticks and chomp the eol on cmake/JUNODependencies.cmake see https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/106
     2 files changed, 47 insertions(+), 28 deletions(-)
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git status
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is ahead of 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess' by 1 commit.
      (use "git push" to publish your local commits)

    nothing to commit, working tree clean
    epsilon:junosw blyth$ git push 
    Counting objects: 9, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (8/8), done.
    Writing objects: 100% (9/9), 1.16 KiB | 1.16 MiB/s, done.
    Total 9 (delta 7), reused 0 (delta 0)
    remote: 
    remote: View merge request for blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/180
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       a6cded9..9869e7d  blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw blyth$ 





