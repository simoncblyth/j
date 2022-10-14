# ~/j/j.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/j.bash
[ "$DBG" == "1" ] && dbg_head $BASH_SOURCE



j-usage(){ cat << EOU
Common source for JUNO high level bash functions
====================================================


* https://code.ihep.ac.cn/JUNO/offline/junosw/


How to test compilation without Opticks ? 
------------------------------------------

1. vi $JUNOTOP/bashrc.sh           ## comment the opticks source line 
2. close terminal session and start a new one
3. get into env : jre  (the "o" command should not be found, showing opticks not hookedup)
4. redo the build : "jo ; ./build_Debug.sh" this will compile without WITH_G4CXOPTICKS/WITH_G4OPTICKS
5. ntds3 should fail at DetSim0Svc::initializeOpticks 
6. ntds0 should complete 


Adding documentation
-----------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/tree/main/Doc/oum
* https://code.ihep.ac.cn/JUNO/offline/junosw/-/tree/main/Doc/oum/source/appendix
* https://juno.ihep.ac.cn/~offline/Doc/user-guide/appendix/oum.html


Thoughts on optimizing workflow
----------------------------------

Having branches live for the shortest possible time avoids 
having to deal with merge issues. 

* So build up changes in working copy, and only when a change is 
  ready to go, create the branch and do the commits and make 
  the merge request all within a short time. 

* Also working at a time when other people are not helps with this. 
  17:00 BST is 00:00 CST : so aim to do such uploading admin 
  in the evening to have a quiet repo



JUNOSW Workflow for getting local changes into main 
-----------------------------------------------------

Web interface setup
~~~~~~~~~~~~~~~~~~~~~~~

If have lots of changes, decide how to group them into issues/branches. 


1. create issue describing what will do using webinterface

   * https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues

2. create branch to hold the changes for review using web interface

   * https://code.ihep.ac.cn/JUNO/offline/junosw/-/branches
   * blyth-22-simplify-Cerenkov-genstep-collection
   * https://code.ihep.ac.cn/JUNO/offline/junosw/-/tree/blyth-22-simplify-Cerenkov-genstep-collection

   * blyth-10-standalone-mask-geometry-debug-interface

   * note, do not create the merge request yet : will do that after making some commits onto the branch 


Working copy setup
~~~~~~~~~~~~~~~~~~~~~~~~~

* FIRST UPDATE main :  with "git pull" : suspect that the need to rebase might be due to forgetting to do this 

Even if I already have some working copy changes (against main branch) 
can still switch to the branch just created via web interface.

* this leave working copy changes asis (but if there are lots of them could use stash for safety)



Examples::

   * git checkout -b blyth-22-simplify-Cerenkov-genstep-collection 
   * git checkout -b blyth-23-update-plog-logging-in-Opticks-integrated-simulation-packages
   * git checkout -b blyth-24-DsG4Scintillation-debug-machinery
   * git checkout -b blyth-10-standalone-mask-geometry-debug-interface
    
    N[blyth@localhost junosw]$ git checkout -b blyth-22-simplify-Cerenkov-genstep-collection 
    Switched to a new branch 'blyth-22-simplify-Cerenkov-genstep-collection'

    N[blyth@localhost junosw]$ git checkout -b blyth-10-standalone-mask-geometry-debug-interface
    Switched to a new branch 'blyth-10-standalone-mask-geometry-debug-interface'

    epsilon:junosw blyth$ git checkout -b blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual
    M	Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    Switched to a new branch 'blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual'




4. now make a series of commits to the branch, prefix commit messages "WIP: #22 "  or "WIP: #23 "
   keep each commit small such that can describe the change succinctly in commit message.

   * WIP will indicate the MR is still under developement. 
   * For your final commit, you just just remove WIP.
   * As pipeline is triggered when you sync the repository, so you can wait to push the commits until it is ready.
   * But we could also add some special rules to disable the pipeline, you can see the example in JUNOSW:
   * https://code.ihep.ac.cn/JUNO/offline/junosw/-/blob/main/.gitlab-ci.yml#L20


Build up the commits, each with related changes that make sense (and compile) together.::

    git diff ..
    git add  ..
    git diff ..
    git add ..
    git commit -m "WIP: #22 add Utilities/EGet header for grabbing values from environment, prepare to use this from PhysiSim "

Note, there is no need to push after every commit. Do that after a sequence of commits, when ready for the pipelines to run. 

    git commit -m "WIP: #22 use EGet::Get<int> for envvar control of process verboseLevel, add genstep collection to G4Cerenkov_modified and move to using that in opticksMode 3 instead of LocalG4Cerenkov1042 " 



::

    N[blyth@localhost junosw]$ git push 
    fatal: The current branch blyth-22-simplify-Cerenkov-genstep-collection has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-22-simplify-Cerenkov-genstep-collection

    N[blyth@localhost junosw]$ git push --set-upstream origin blyth-22-simplify-Cerenkov-genstep-collection
    To code.ihep.ac.cn:JUNO/offline/junosw
     ! [rejected]        blyth-22-simplify-Cerenkov-genstep-collection -> blyth-22-simplify-Cerenkov-genstep-collection (fetch first)
    error: failed to push some refs to 'code.ihep.ac.cn:JUNO/offline/junosw'
    hint: Updates were rejected because the remote contains work that you do
    hint: not have locally. This is usually caused by another repository pushing
    hint: to the same ref. You may want to first integrate the remote changes
    hint: (e.g., 'git pull ...') before pushing again.
    hint: See the 'Note about fast-forwards' in 'git push --help' for details.
    N[blyth@localhost junosw]$ 


    epsilon:junosw blyth$ git push --set-upstream origin blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual
    Counting objects: 7, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (7/7), done.
    Writing objects: 100% (7/7), 936 bytes | 936.00 KiB/s, done.
    Total 7 (delta 6), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       dad6f3d..bd1e2ad  blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual -> blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual
    Branch blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual set up to track remote branch blyth-32-NNVTMaskManager-fix-MaskTail-overlap-MaskVirtual from origin.
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 






    N[blyth@localhost junosw]$ git pull 
    remote: Enumerating objects: 23, done.
    remote: Counting objects: 100% (23/23), done.
    remote: Compressing objects: 100% (17/17), done.
    remote: Total 23 (delta 12), reused 16 (delta 6), pack-reused 0
    Unpacking objects: 100% (23/23), 5.66 KiB | 263.00 KiB/s, done.
    From code.ihep.ac.cn:JUNO/offline/junosw
     * [new branch]      J22.2.x                                       -> origin/J22.2.x
     * [new branch]      blyth-22-simplify-Cerenkov-genstep-collection -> origin/blyth-22-simplify-Cerenkov-genstep-collection
       4efaaf7..91d0968  main                                          -> origin/main
     * [new tag]         J22.2.0-rc0                                   -> J22.2.0-rc0
    There is no tracking information for the current branch.
    Please specify which branch you want to merge with.
    See git-pull(1) for details.

        git pull <remote> <branch>

    If you wish to set tracking information for this branch you can do so with:

        git branch --set-upstream-to=origin/<branch> blyth-22-simplify-Cerenkov-genstep-collection

    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    hint: You have divergent branches and need to specify how to reconcile them.
    hint: You can do so by running one of the following commands sometime before
    hint: your next pull:
    hint: 
    hint:   git config pull.rebase false  # merge (the default strategy)
    hint:   git config pull.rebase true   # rebase
    hint:   git config pull.ff only       # fast-forward only
    hint: 
    hint: You can replace "git config" with "git config --global" to set a default
    hint: preference for all repositories. You can also pass --rebase, --no-rebase,
    hint: or --ff-only on the command line to override the configured default per
    hint: invocation.
    fatal: Need to specify how to reconcile divergent branches.
    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git config pull.ff only  
    N[blyth@localhost junosw]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    fatal: Not possible to fast-forward, aborting.
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git config pull.rebase false
    N[blyth@localhost junosw]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    fatal: Not possible to fast-forward, aborting.
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git config pull.rebase true
    N[blyth@localhost junosw]$ git pull origin main
    error: cannot pull with rebase: You have unstaged changes.
    error: please commit or stash them.
    N[blyth@localhost junosw]$ 


Same problem again, push is rejected due to another repo having pushed::

    N[blyth@localhost PMTSim]$ git push 
    fatal: The current branch blyth-10-standalone-mask-geometry-debug-interface has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-10-standalone-mask-geometry-debug-interface

    N[blyth@localhost PMTSim]$ git push --set-upstream origin blyth-10-standalone-mask-geometry-debug-interface
    To code.ihep.ac.cn:JUNO/offline/junosw
     ! [rejected]        blyth-10-standalone-mask-geometry-debug-interface -> blyth-10-standalone-mask-geometry-debug-interface (fetch first)
    error: failed to push some refs to 'code.ihep.ac.cn:JUNO/offline/junosw'
    hint: Updates were rejected because the remote contains work that you do
    hint: not have locally. This is usually caused by another repository pushing
    hint: to the same ref. You may want to first integrate the remote changes
    hint: (e.g., 'git pull ...') before pushing again.
    hint: See the 'Note about fast-forwards' in 'git push --help' for details.

    N[blyth@localhost PMTSim]$ git pull 
    remote: Enumerating objects: 101, done.
    remote: Counting objects: 100% (28/28), done.
    remote: Total 101 (delta 28), reused 28 (delta 28), pack-reused 73
    Receiving objects: 100% (101/101), 27.50 KiB | 5.50 MiB/s, done.
    Resolving deltas: 100% (55/55), completed with 17 local objects.
    From code.ihep.ac.cn:JUNO/offline/junosw
     * [new branch]      IOConsiderSplit                                   -> origin/IOConsiderSplit
     * [new branch]      blyth-10-standalone-mask-geometry-debug-interface -> origin/blyth-10-standalone-mask-geometry-debug-interface
     * [new branch]      luoxj-UpdatePSDToolsTraining-branch               -> origin/luoxj-UpdatePSDToolsTraining-branch
       537668f..1b26cb0  main                                              -> origin/main
    There is no tracking information for the current branch.
    Please specify which branch you want to rebase against.
    See git-pull(1) for details.

        git pull <remote> <branch>

    If you wish to set tracking information for this branch you can do so with:

        git branch --set-upstream-to=origin/<branch> blyth-10-standalone-mask-geometry-debug-interface

    N[blyth@localhost PMTSim]$ 

    N[blyth@localhost PMTSim]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    fatal: Not possible to fast-forward, aborting.
    N[blyth@localhost PMTSim]$ 





The changes remaining are all related to logging changes::

    N[blyth@localhost junosw]$ jo
    /data/blyth/junotop/junosw
    On branch blyth-22-simplify-Cerenkov-genstep-collection
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
        modified:   Simulation/GenTools/src/GtOpticksTool.cc

    Untracked files:
      (use "git add <file>..." to include in what will be committed)
        Simulation/DetSimV2/PMTSim/PMTSim/
        Simulation/DetSimV2/PMTSim/src/OK_PMTSIM_LOG.cc
        Simulation/DetSimV2/PhysiSim/PhysiSim/
        Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git stash 
    Saved working directory and index state WIP on blyth-22-simplify-Cerenkov-genstep-collection: 58b435f WIP: #22 use EGet::Get<int> for envvar control of process verboseLevel, add genstep collection to G4Cerenkov_modified and move to using that in opticksMode 3 instead of LocalG4Cerenkov1042
    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git s
    On branch blyth-22-simplify-Cerenkov-genstep-collection
    Untracked files:
      (use "git add <file>..." to include in what will be committed)
        Simulation/DetSimV2/PMTSim/PMTSim/
        Simulation/DetSimV2/PMTSim/src/OK_PMTSIM_LOG.cc
        Simulation/DetSimV2/PhysiSim/PhysiSim/
        Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc

    nothing added to commit but untracked files present (use "git add" to track)
    N[blyth@localhost junosw]$ l Simulation/DetSimV2/PMTSim/PMTSim/
    total 4
    0 drwxrwxr-x. 2 blyth blyth  30 Oct  3 03:22 .
    4 -rw-rw-r--. 1 blyth blyth 568 Oct  3 02:51 OK_PMTSIM_LOG.hh
    0 drwxrwxr-x. 5 blyth blyth  68 Sep 30 23:10 ..


    N[blyth@localhost junosw]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    fatal: Not possible to fast-forward, aborting.
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git help pull 
    N[blyth@localhost junosw]$ git pull --rebase origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    Successfully rebased and updated refs/heads/blyth-22-simplify-Cerenkov-genstep-collection.
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ 

    N[blyth@localhost PMTSim]$ git config pull.rebase true
    N[blyth@localhost PMTSim]$ git pull origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    fatal: Not possible to fast-forward, aborting.
    N[blyth@localhost PMTSim]$ 
    N[blyth@localhost PMTSim]$ git pull --rebase origin main
    From code.ihep.ac.cn:JUNO/offline/junosw
     * branch            main       -> FETCH_HEAD
    Successfully rebased and updated refs/heads/blyth-10-standalone-mask-geometry-debug-interface.
    N[blyth@localhost PMTSim]$ 
    N[blyth@localhost PMTSim]$ 
    N[blyth@localhost PMTSim]$ git push 
    fatal: The current branch blyth-10-standalone-mask-geometry-debug-interface has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-10-standalone-mask-geometry-debug-interface

    N[blyth@localhost PMTSim]$ git push --set-upstream origin blyth-10-standalone-mask-geometry-debug-interface
    Enumerating objects: 54, done.
    Counting objects: 100% (54/54), done.
    Delta compression using up to 48 threads
    Compressing objects: 100% (40/40), done.
    Writing objects: 100% (40/40), 13.06 KiB | 1.00 MiB/s, done.
    Total 40 (delta 33), reused 0 (delta 0), pack-reused 0
    remote: 
    remote: To create a merge request for blyth-10-standalone-mask-geometry-debug-interface, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-10-standalone-mask-geometry-debug-interface
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw
       1b26cb0..32b2d18  blyth-10-standalone-mask-geometry-debug-interface -> blyth-10-standalone-mask-geometry-debug-interface
    Branch 'blyth-10-standalone-mask-geometry-debug-interface' set up to track remote branch 'blyth-10-standalone-mask-geometry-debug-interface' from 'origin'.
    N[blyth@localhost PMTSim]$ 









    N[blyth@localhost junosw]$ git push --set-upstream origin blyth-22-simplify-Cerenkov-genstep-collection
    Enumerating objects: 34, done.
    Counting objects: 100% (34/34), done.
    Delta compression using up to 48 threads
    Compressing objects: 100% (20/20), done.
    Writing objects: 100% (22/22), 3.13 KiB | 535.00 KiB/s, done.
    Total 22 (delta 14), reused 0 (delta 0), pack-reused 0
    remote: 
    remote: To create a merge request for blyth-22-simplify-Cerenkov-genstep-collection, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-22-simplify-Cerenkov-genstep-collection
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw
       91d0968..c46d86a  blyth-22-simplify-Cerenkov-genstep-collection -> blyth-22-simplify-Cerenkov-genstep-collection
    Branch 'blyth-22-simplify-Cerenkov-genstep-collection' set up to track remote branch 'blyth-22-simplify-Cerenkov-genstep-collection' from 'origin'.
    N[blyth@localhost junosw]$ 














    N[blyth@localhost junosw]$ git stash show
     .../include/LSExpDetectorConstruction_Opticks.hh   |  8 +++
     .../DetSimV2/DetSimOptions/src/DetSim0Svc.cc       |  4 ++
     .../src/LSExpDetectorConstruction_Opticks.cc       | 11 +--
     .../DetSimV2/PMTSim/include/junoSD_PMT_v2.hh       |  6 ++
     .../PMTSim/include/junoSD_PMT_v2_Opticks.hh        |  5 +-
     Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc    | 80 +++++++++++++++++-----
     .../DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc   | 51 ++++++++------
     .../DetSimV2/PhysiSim/src/DsG4Scintillation.cc     | 37 +++++++---
     .../DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc   |  7 +-
     Simulation/GenTools/src/GtOpticksTool.cc           | 10 +--
     10 files changed, 154 insertions(+), 65 deletions(-)
    N[blyth@localhost junosw]$ 

    N[blyth@localhost junosw]$ git stash apply 
    On branch blyth-22-simplify-Cerenkov-genstep-collection
    Your branch is up to date with 'origin/blyth-22-simplify-Cerenkov-genstep-collection'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
        modified:   Simulation/GenTools/src/GtOpticksTool.cc

    Untracked files:
      (use "git add <file>..." to include in what will be committed)
        Simulation/DetSimV2/PMTSim/PMTSim/
        Simulation/DetSimV2/PMTSim/src/OK_PMTSIM_LOG.cc
        Simulation/DetSimV2/PhysiSim/PhysiSim/
        Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ 



Following a merge tidy up the obsolete branch
-------------------------------------------------

Now following the merge of the MR, tidy up : by deleting the now merged branch.

1. hop to main: git checkout main   (working copy changes are safe)

2. list branches, and delete the old one::
     
    N[blyth@localhost junosw]$ git branch 
      blyth-22-simplify-Cerenkov-genstep-collection
    * main

    N[blyth@localhost junosw]$ git branch -d blyth-22-simplify-Cerenkov-genstep-collection
    warning: deleting branch 'blyth-22-simplify-Cerenkov-genstep-collection' that has been merged to
             'refs/remotes/origin/blyth-22-simplify-Cerenkov-genstep-collection', but not yet merged to HEAD.
    Deleted branch blyth-22-simplify-Cerenkov-genstep-collection (was c46d86a).
    N[blyth@localhost junosw]$ 


Another example::

    N[blyth@localhost junosw]$ git branch 
      blyth-23-update-plog-logging-in-Opticks-integrated-simulation-packages
    * main
    N[blyth@localhost junosw]$ git branch -d blyth-23-update-plog-logging-in-Opticks-integrated-simulation-packages
    Deleted branch blyth-23-update-plog-logging-in-Opticks-integrated-simulation-packages (was 003c978).
    N[blyth@localhost junosw]$ 


Another::

    N[blyth@localhost junosw]$ git checkout main 
    Switched to branch 'main'
    Your branch is behind 'origin/main' by 15 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)
    N[blyth@localhost junosw]$ git pull 
    remote: Enumerating objects: 18, done.
    remote: Counting objects: 100% (18/18), done.
    remote: Compressing objects: 100% (9/9), done.
    remote: Total 18 (delta 9), reused 15 (delta 9), pack-reused 0
    Unpacking objects: 100% (18/18), 3.54 KiB | 191.00 KiB/s, done.
    From code.ihep.ac.cn:JUNO/offline/junosw
       1b26cb0..5bbe1b4  main       -> origin/main
    Updating 537668f..5bbe1b4
    Fast-forward
     .gitlab-ci.yml                                                 |  21 ++++-
     Examples/Tutorial/tests/test_detsim.py                         |  80 ++++++++++++-------
     Examples/Tutorial/tests/test_sim2rec.py                        |   2 +-
     RootIO/RootIOSvc/RootIOSvc/RootOutputSvc.h                     |   2 +
     RootIO/RootIOSvc/src/RootOutputSvc.cc                          |   5 ++
     RootIO/RootIOTools/CMakeLists.txt                              |   1 +
     RootIO/RootIOTools/share/merge.py                              |  37 +++++----
     RootIO/RootIOTools/share/merge_old.py                          |  38 +++++++++
     RootIO/RootIOTools/src/HaddAlg.cc                              |  73 +++++++++++++++++
     RootIO/RootIOTools/src/HaddAlg.h                               |  24 ++++++
     Simulation/DetSimV2/MCParamsSvc/python/MCParamsSvc/__init__.py |   7 ++
     Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh     |  43 +++++++++-
     Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh          |  52 +++++++++++-
     Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh     |   5 ++
     Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc         | 436 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++-------
     Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc    |  74 +++++++++--------
     Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc            |  51 +++++++-----
     Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc              | 398 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++------
     Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc                |  14 +---
     Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc          |  52 ++++++++----
     Simulation/ElecSimV3/ElecSimAlg/src/ElecSimSvc.cc              |  35 +++++++--
     21 files changed, 1263 insertions(+), 187 deletions(-)
     create mode 100644 RootIO/RootIOTools/share/merge_old.py
     create mode 100644 RootIO/RootIOTools/src/HaddAlg.cc
     create mode 100644 RootIO/RootIOTools/src/HaddAlg.h
     create mode 100644 Simulation/DetSimV2/MCParamsSvc/python/MCParamsSvc/__init__.py
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git branch 
      blyth-10-standalone-mask-geometry-debug-interface
    * main

    N[blyth@localhost junosw]$ git branch -d blyth-10-standalone-mask-geometry-debug-interface
    Deleted branch blyth-10-standalone-mask-geometry-debug-interface (was 32b2d18).

    N[blyth@localhost junosw]$ git s
    On branch main
    Your branch is up to date with 'origin/main'.

    nothing to commit, working tree clean
    N[blyth@localhost junosw]$ 




3. pull the upstream updates

    N[blyth@localhost junosw]$ git pull 
    error: cannot pull with rebase: You have unstaged changes.
    error: please commit or stash them.
    N[blyth@localhost junosw]$ git stash    # clear decks of local changes, other than untracked which are still lying around
    N[blyth@localhost junosw]$ git pull     # now can pull from upstream
    N[blyth@localhost junosw]$ git stash apply   # get back local changes 


* so now are back on main branch with local changes ready to be incorporated in another branch 
* check can build OK : jx-touch 







Installation instructions are still using SVN ?
-------------------------------------------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
* https://code.ihep.ac.cn/JUNO/offline/junoenv

junosw #10 : prefix commits "WIP: #10 "
---------------------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues/10


Tao advice
------------



::

    Hi Simon,

    OK, I see your issue now.

    BTW: when you make commit, you can add "WIP:" so that the CI will run without testing jobs. 
    Tao


::

    Hi Simon,

    For your changes, you could create a new issue first. As Gitlab support cross
    reference, you can then associate a merge request to this issue. You can use
    #42 to ref issue-42 in the merge request, then the issue will be associated
    with the merge request automatically.

    About the developer's workflow: due to the fork projects could not use the
    gitlab runners to run CI, we suggest developers to create a branch in junosw
    official repository. Then you can create a merge request after you have this
    branch.  People will review your code and the merge your merge request. 

    Do you think is that clear?
    Tao


IHEP git setup
---------------

0. access instructions using un:j/pw:j 

* https://juno.ihep.ac.cn/~offline/Doc/user-guide/appendix/tools.html#git-a-version-control-system

1. add id_rsa.pub key from Precision workstation into gitlab web interface 

   * https://code.ihep.ac.cn/-/profile

2. check the key from precision workstation::

    N[blyth@localhost ~]$ ssh -T git@code.ihep.ac.cn
    Welcome to GitLab, @blyth!
    N[blyth@localhost ~]$ 

3. check from epsilon before and after adding "Epsilon.Laptop.blyth" key thru web interface::

    epsilon:opticks blyth$ ssh -T git@code.ihep.ac.cn
    git@code.ihep.ac.cn: Permission denied (publickey).

    epsilon:~ blyth$ ssh -T git@code.ihep.ac.cn
    Welcome to GitLab, @blyth!

4. check clone from Precision and Epsilon::

    N[blyth@localhost ~]$ git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git
    Cloning into 'junosw'...
    remote: Enumerating objects: 3614, done.
    remote: Counting objects: 100% (26/26), done.
    remote: Compressing objects: 100% (26/26), done.
    remote: Total 3614 (delta 10), reused 0 (delta 0), pack-reused 3588
    Receiving objects: 100% (3614/3614), 6.38 MiB | 11.16 MiB/s, done.
    Resolving deltas: 100% (637/637), done.
    N[blyth@localhost ~]$ 
    N[blyth@localhost ~]$ l junosw/
    total 68
     0 drwxrwxr-x.  8 blyth blyth  163 Sep 22 17:10 .git
     4 drwxrwxr-x. 25 blyth blyth 4096 Sep 22 17:10 .
     4 drwxrwxr-x.  3 blyth blyth 4096 Sep 22 17:10 cmake
     4 -rw-rw-r--.  1 blyth blyth 1749 Sep 22 17:10 setup.sh
     4 -rwxrwxr-x.  1 blyth blyth  681 Sep 22 17:10 build_Doc.sh
    ..

    epsilon:~ blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git
    Cloning into 'junosw'...
    remote: Enumerating objects: 3614, done.
    remote: Counting objects: 100% (26/26), done.
    remote: Compressing objects: 100% (26/26), done.
    remote: Total 3614 (delta 10), reused 0 (delta 0), pack-reused 3588
    Receiving objects: 100% (3614/3614), 6.38 MiB | 268.00 KiB/s, done.
    Resolving deltas: 100% (637/637), done.
    epsilon:~ blyth$ l junosw/
    total 72
     0 drwxr-xr-x   13 blyth  staff    416 Sep 22 10:11 .git
     8 -rw-r--r--    1 blyth  staff   1749 Sep 22 10:11 setup.sh
     0 drwxr-xr-x   33 blyth  staff   1056 Sep 22 10:11 .
     0 drwxr-xr-x   13 blyth  staff    416 Sep 22 10:11 cmake
     8 -rwxr-xr-x    1 blyth  staff     63 Sep 22 10:11 build_RelWithDebInfo.sh
     8 -rwxr-xr-x    1 blyth  staff    681 Sep 22 10:11 build_Doc.sh


5. move junosw under junotop on Epsilon (this is just for looking at code, not building) and change jo bash function::

    epsilon:~ blyth$ mv junosw junotop/
    epsilon:~ blyth$ t jo
    jo () 
    { 
        cd_func $JUNOTOP/junosw && pwd && git status
    }




IHEP Git instructions
------------------------

Clone code from official repository::

    git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git

Clone code from user repository (you should fork the official repository)::

    git clone git@code.ihep.ac.cn:YOURNAME/junosw.git

Add additional repository (mine is an alias name, then following the user repository)::

    git remote add mine git@code.ihep.ac.cn:YOURNAME/junosw.git

Sync local repository and remote repository (sync the local main branch)::

    git push mine main   # push your local changes to a branch in remote repository
    git pull origin main # merge the remote branch main into local repository

Switch branch::

    git checkout main          # switch to an existing branch
    git checkout -b new-branch # creatie a new branch
    git branch -d new-branch   # delete a branch




JUNO Offline Moved to Git : Mail from Tao : Sep 16, 2022
-----------------------------------------------------------

Dear all,

Both JUNOSW and TAOSW are migrated to git:

    JUNOSW: https://code.ihep.ac.cn/JUNO/offline/junosw
    TAOSW: https://code.ihep.ac.cn/JUNO/offline/taosw

We encourage users and developers use the issues system in gitlab:

    For JUNOSW: https://code.ihep.ac.cn/JUNO/offline/junosw/-/issues
    For TAOSW: https://code.ihep.ac.cn/JUNO/offline/taosw/-/issues

You can find instructions to use git in OUM:

    https://juno.ihep.ac.cn/~offline/Doc/user-guide/appendix/tools.html#git-a-version-control-system

    * un/pw j/j worked

Here is a quickstart:

If you are the first time to use IHEP gitlab, you need to register a public key before use it. Then you can clone the code:

    git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git

If you don't setup a public key yet, you can clone code with your IHEP SSO account:

    https://code.ihep.ac.cn/JUNO/offline/junosw.git

After you get the code, you need to use new exteral libraries (J22.2.x) to build them:

    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/setup.sh
    ./build.sh

For learning git, you can have a look at following materials:

    HSF Software Training Center: https://hepsoftwarefoundation.org/training/curriculum.html
    Git book: https://git-scm.com/book/en/v2

If you have any permission problems, please feel free to send me mail. 
Tao




Yuxiang JUNOLight
--------------------

* https://code.ihep.ac.cn/huyuxiang/ls_sim
* https://code.ihep.ac.cn/huyuxiang/ls_sim/-/blob/main/LS_Sim/src/LSDetectorConstruction_Opticks.cc
* https://code.ihep.ac.cn/huyuxiang/ls_sim/-/blob/main/LS_Sim/src/LSDetectorConstruction.cc


PMTSim
---------

* https://juno.ihep.ac.cn/trac/browser/offline/trunk/Simulation/DetSimV2/PMTSim/src


::

   cd ; git clone git@github.com:simoncblyth/j.git ; echo "source \$HOME/j/j.bash" >> .bash_profile 


Was surprised that this worked::

    epsilon:tmp blyth$ git clone https://code.ihep.ac.cn/huyuxiang/qmultifilmlut
    Cloning into 'qmultifilmlut'...
    warning: redirecting to https://code.ihep.ac.cn/huyuxiang/qmultifilmlut.git/
    remote: Enumerating objects: 1610, done.
    remote: Total 1610 (delta 0), reused 0 (delta 0), pack-reused 1610
    Receiving objects: 100% (1610/1610), 2.03 MiB | 190.00 KiB/s, done.
    Resolving deltas: 100% (583/583), done.
    epsilon:tmp blyth$ 
    epsilon:tmp blyth$ 
    epsilon:tmp blyth$ l qmultifilmlut/
    total 16
     0 drwxr-xr-x   13 blyth  wheel   416 May 25 10:49 .git
     0 drwxr-xr-x    7 blyth  wheel   224 May 25 10:49 trunk
     0 drwxr-xr-x    9 blyth  wheel   288 May 25 10:49 .
     0 drwxr-xr-x  207 blyth  wheel  6624 May 25 10:49 sysrap
     0 drwxr-xr-x   96 blyth  wheel  3072 May 25 10:49 qudarap
     0 drwxr-xr-x    7 blyth  wheel   224 May 25 10:49 j
    16 -rw-r--r--    1 blyth  wheel  6280 May 25 10:49 README.md
     0 drwxr-xr-x   91 blyth  wheel  2912 May 25 10:49 CSGOptiX
     0 drwxrwxrwt   35 root   wheel  1120 May 25 10:49 ..
    epsilon:tmp blyth$ 


    




The paper on the intrinsic energy resolution of liquid scintillator has been published online, https://doi.org/10.1088/1748-0221/17/04/P04018. The energy resolution of liquid scintillator has become a little confusing. This issue needs further exploration, and it is not only a matter of our LS group, but the simulation and the physics group should pay attention.

--
best regards
Xilei Sun
IHEP



Dear All,

To avoid massive data transfer between /eos/juno and /hpcfs,   /ets/juno is accessable on Slurm GPU worker nodes now,  access to /eos/juno is available with xrootd in job scripts.

Users can use the following method to access file in /eos/juno:  TFile *filein = TFile::Open("root://junoeos01.ihep.ac.cn//eos_absolute_path_filein_name.root")

More  details can refer to the user manual: http://afsapply.ihep.ac.cn/cchelp/en/experiments/JUNO/

Thanks a lot for you support and understanding.

Best regards,
Computing Center







fyi, we have uploaded the NY video of JUNO (english) on youtube
Maxim

https://www.youtube.com/watch?v=ONXeTieQte4

-- 



Dear colleagues, The JUNO software and computing move forward to a new stage in
which development, integration, testing, and  deployment are  happening at the
same time. We have noticed that more efforts are required to make things  go
smoothly. For this purpose, we decided to organize the JUNO Offline
Coordination (JOC) Meeting. The JOC meeting is supposed to be a one-hour
meeting taking place at 09:00 (Europe/Zurich), 16:00 (Beijing) every Thursday.
 
You may find more information about the meeting in the DocDB event:
 
https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?conferenceid=1021
 
Since we don’t want everyone to be disturbed by  the meeting announcement next
time, please login with the account, juno/jiangmen, and add your email to the
mailing list if you feel interested in this meeting:
 
https://juno.ihep.ac.cn/mailman/listinfo/offline_coordination
 
 
Best regards,
 
Giuseppe, Xingtao and Weidong










Mattermost
------------

Dear collaborators,

In the past there had been a few suggestions regarding having an instant
messaging tool to permit us rapid communication between ourselves. IHEP has
prepared an installation of mattermost for us which we can use for such a
purpose. Afte r a brief testing period we'd like to invite all collaborators to
join us at:
https://mattermost.ihep.ac.cn/signup_user_complete/?id=8diw658t67gkfjgwkn5awi7zgo

A few groups have already been created for the AFGs and offline group. You can
find them directly via the mattermost w eb interface, or join them directly via
the links provided in the Wiki:
https://juno.ihep.ac.cn/mediawiki/index.php/Analysis_Foundation_Groups#Mattermost_Team_and_Channels

With the IHEP installation, we have no limit to the number of messages that are
saved in mattermost so we can track th e full history of all conversations in
there, if that is needed at some point. Additionally, mattermost uses the IHEP
SSO, which makes it pretty convenient as no new login/password are required.

Let us know if you have any trouble getting started with mattermost!

Cheers, João Pedro for the ACC



GitHub Proxy
--------------

About the github access problem, my solution is connecting to an SSH server and setting up a proxy before installation:

$ type proxy-git-cern
proxy-git-cern is a function
proxy-git-cern ()
{
    ssh -f -N -D 37687 cern

    : -f got to background before call
    : -N do not execute remote command, useful for just forwarding ports
    : -D setup forwarding port 37687, allocates a socket 
    : cern the name of the remote machine in ssh_config
}

$ type proxy-setup-cern
proxy-setup-cern is a function
proxy-setup-cern ()
{
    local hn=localhost;
    local port=37687;
    export http_proxy=socks5://$hn:${port};
    export https_proxy=socks5://$hn:${port};
    export no_proxy=localhost,202.122.33.67,192.168.60.140,192.168.60.141,192.168.60.142,10.96.0.0/12,10.244.0.0/16;
    export HTTP_PROXY=${http_proxy};
    export HTTPS_PROXY=${https_proxy};
    export NO_PROXY=${no_proxy}

    : see man curl
    : NO_PROXY is list of hostname that should not go thru the proxy 

}

As socks5 is not supported by wget, so I had already modified junoenv to use cURL to download files. 
For the github ssh access, I had setup following in $HOME/.gitconfig:

[http "https://github.com"]
        proxy = socks5://localhost:37687


 



JUNO Collab Meeting 18-29 July 2022
-------------------------------------


I updated the WIKI page concerning the procedure and rules to proficiently use our resources @ CNAF.

These informations are summarized in the presentation here attached and can be extensively found at:
https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Account/CNAF
https://juno.ihep.ac.cn/mediawiki/index.php/Offline:SetupCNAF
https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Submitjob/CNAF
Please take a minute to read them!

For any question, feel free to write to me (alessandra.re@mi.infn.it)

Cheers,
Ale

OUM Docs
---------

* https://juno.ihep.ac.cn/~offline/Doc/user-guide/detsim/structures.html

* GPU Related Works : https://jupyter.ihep.ac.cn/GUrbwIBnRjeNypgn6BPg-w?view


Jan 2022 collaboration meeting event
--------------------------------------

https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?conferenceid=1001


JUNO CORE SW FDR : Mon Jan 17, 2022
---------------------------------------

FDR: the review comittee shall pay particular attentions on that if the
current core software design satisfies the various needs of future physics
analysis. The draft of charge letter is attached. 

* Charge letter doc-7783. 
* Agenda for the FDR: https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?sessionid=1625
* Live note https://jupyter.ihep.ac.cn/htaWZQnRSQmHSRKcy80C6g


Tue Jan 18 2022 : physics/offline session
--------------------------------------------

* https://us02web.zoom.us/j/86093951678?pwd=d1lBbHUrcWVhalcveEpZVG1odHJXdz09
* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?sessionid=1626




Tao demo-photon-generation
-----------------------------

* https://github.com/mirguest/demo-photon-generation

  git clone git@github.com:mirguest/demo-photon-generation.git 


Analysis_Foundation_Groups
----------------------------

Dear all,

The Data Production Group will be in charge of

MC Production
Physics Production
Keep Up Production / 1st round reconstruction
Data Quality Monitoring
Please find all the necessary information about Data Production group in the wiki page:

    https://juno.ihep.ac.cn/mediawiki/index.php/Analysis_Foundation_Groups/Data_production
For your convenience, here are a list of useful links:

Data Production Mailing list: valprod@juno.ihep.ac.cn
User forum (HyperNews) to request MC data production: valprod@hnjuno.ihep.ac.cn
subscribe here: http://hnjuno.ihep.ac.cn/HyperNews/get/valprod.html
Documentation: https://juno.ihep.ac.cn/~offline/Doc/data-production/
The source code of docs: https://code.ihep.ac.cn/JUNO/juno-afgs/data-production/docs
GitLab: https://code.ihep.ac.cn/JUNO/juno-afgs/data-production
Live Notes: https://jupyter.ihep.ac.cn/Z9b7Xp2hSmKVcEGzR6SUKg
If you are interested in any topics of our group, please subscribe the mailing list and send us emails.

Thank you!

Alessandra, Zhengyun and Tao


Dear all,
If you are interested in AFG simulation , please feel free to subscribe to the mailing list:      https://juno.ihep.ac.cn/mailman/listinfo/juno_sim
We will start a bi-weekly meeting to discuss simulation, the meeting link will be sent to:  juno_sim@juno.ihep.ac.cn .
Thanks.
Guofu, Cecile and Ziyan

Hi Yongpeng et al,

I'm afarid there is hyperlink under the URL you provided, if one clicks it, it directs to the calib_analysis list. 
Anyways, I re-copy it here: https://juno.ihep.ac.cn/mailman/listinfo/juno_oec

Btw, Please also add this mailing list info into the wiki page: 
https://juno.ihep.ac.cn/mediawiki/index.php/Analysis_Foundation_Groups

Regards,
Liangjian Wen


Dear all,

As we have presented last Friday, there are lots of important, interesting as well as challenging tasks related to reconstruction in JUNO.
If you are interested in any of them, please subscribe to our mailing list
https://juno.ihep.ac.cn/mailman/listinfo (juno_rec)

We have also prepared a wiki https://juno.ihep.ac.cn/mediawiki/index.php/Analysis_Foundation_Groups/Reconstruction#Group_Work_Organization
please update your contact info and areas of interest in the table.

Thank you very much!

Best
Wuming & Benda


CVMFS setup
--------------

* https://juno.ihep.ac.cn/trac/browser/offline/trunk/installation/junoenv/docker/Dockerfile-cvmfs



Install Link
---------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#install_offline_data


Page for updating

*  https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#Using_JunoENV


Tao /cvmfs Offline Scripts
-----------------------------

Yes, we also encounter such problem (ROOT not compatible with devtoolset) before. 
You can use the GCC 8.3.0 provided by JUNO. You can have a look at my installation 
script to see how to reuse the external libraries:

* /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh

BTW: As I mentioned in the last meeting, I had setup a new CVMFS repository for nightly build:

* /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b

The nightly build consists a shell script and a crontab:

    [junopub@cvmfspublisher ~]$ crontab -l
    25 17 * * * bash <<< "$(bash /cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh deployit)"


SCB: deployit emits to stdout a few commands including "cvmfs_server publish" 

The software is built in a container on the cvmfspublisher. The reason why I
use '<<<' is because the CVMFS will check any file belong this repository is
used or not. If the shell script is still used, then the publish will be
failed.  

If I remember correctly, you had the access to the opticks CVMFS
repository. So you can create a directory for such usage.  I think one missing
part is the CUDA is not included inside the container. I am not sure is that
easy to deploy it inside the container.  Maybe we can contact with Jingyan Shi
and Ran Du for the help. 


/cvmfs/juno_nightlies.ihep.ac.cn/centos7_amd64_gcc830/b/build-tools/build.sh


Reuse of ExternalLibs
------------------------

/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh::


     10 function reuse-junotop() {
     11     echo /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch
     12 }
     13 
     14 function junotop() {
     15     echo /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0
     16 }
     17 
     18 function checkout-junoenv() {
     19     if [ -d "$(junotop)/junoenv" ];
     20     then
     21         return
     22     fi
     23     svn co https://juno.ihep.ac.cn/svn/offline/${JUNOENV_branches}/installation/junoenv
     24 }
     25 
     26 function setup-env() {
     27     export JUNOTOP=$(junotop)
     28     export JUNO_EXTLIB_OLDTOP=$(reuse-junotop)/ExternalLibs
     29     export ExternalInterface_version="trunk 33"
     30     export Sniper_version="2.0.3"
     31     export OfflineData_version="trunk 115"
     32     export Offline_version="tags/J21v2r0-Pre0" # TODO
     33 
     34     export JUNOENV_branches=trunk
     35     export JUNOENV_version=
     36 }
     37 
     38 function reuse-libs() {
     39     # bash junoenv libs reuse allpkgs
     40     bash junoenv libs reuse python
     41     bash junoenv libs reuse python-setuptools
     42     bash junoenv libs reuse python-pip
     43     bash junoenv libs reuse python-cython
     44     bash junoenv libs reuse python-numpy
       


junoenv-external-libs.sh::

    795 function juno-ext-libs-reuse {
    796     local msg="==== $FUNCNAME: "
    797     # = check the environment variable $JUNO_EXTLIB_OLDTOP =
    798     if [ -z "$JUNO_EXTLIB_OLDTOP" ];
    799     then 
    800         echo $msg Please set the ENVIRONMENT VARIABLE called \$JUNO_EXTLIB_OLDTOP first1>&2
    801         exit 1
    802     fi  
    803     if [ ! -d "$JUNO_EXTLIB_OLDTOP" ];
    804     then 
    805         echo $msg The \$JUNO_EXTLIB_OLDTOP \"$JUNO_EXTLIB_OLDTOP\" does not exist.
    806         exit 1
    807     fi  
    808     local pkg=$1
    809     # = get the installation directory for PKG =
    810     # here is the dir with version
    811     local oldpath=$JUNO_EXTLIB_OLDTOP/$(juno-ext-libs-${pkg}-name)/$(juno-ext-libs-${pkg}-version)
    812     local newpath=$(juno-ext-libs-${pkg}-install-dir)
    813     echo $msg $pkg oldpath: $oldpath
    814     echo $msg $pkg newpath: $newpath






HedgeDoc pages
------------------------------

* GPU related works
* https://jupyter.ihep.ac.cn/GUrbwIBnRjeNypgn6BPg-w?edit


jck
-----

* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc
* https://juno.ihep.ac.cn/trac/browser/offline/trunk/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc?annotate=blame
* https://juno.ihep.ac.cn/trac/changeset/4540/offline


Offline Trac Links
---------------------

* https://juno.ihep.ac.cn/trac/changeset/4353/offline


* https://juno.ihep.ac.cn/trac/search?q=r4090
* https://juno.ihep.ac.cn/trac/browser/offline/trunk/Simulation/DetSimV2/PMTSim#src

* https://juno.ihep.ac.cn/trac/changeset/31/cmtlibs
* https://juno.ihep.ac.cn/trac/browser/cmtlibs#trunk

* https://juno.ihep.ac.cn/trac/timeline


Documentation Links
-----------------------

* https://juno.ihep.ac.cn/~offline/Doc/user-guide/geometry/management.html

  Login with "juno" user works.


CVMFS Anaconda
---------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Anaconda

::

   source /cvmfs/juno.ihep.ac.cn/sw/anaconda/Anaconda3-2020.11-Linux-x86_64/bin/activate root622



Sniper Links
---------------

* https://github.com/SNiPER-Framework/sniper/releases/tag/v1.6
* https://github.com/SNiPER-Framework/sniper/commit/f66fafa399f7a46af5044b9a877b503277cdfb69
* https://juno.ihep.ac.cn/trac/browser/offline/trunk/installation/junoenv/junoenv-sniper.sh
* https://juno.ihep.ac.cn/trac/browser/cmtlibs/trunk/Externals/ROOT/cmt/requirements?rev=31

slack kanban
--------------

* https://juno-analysis.slack.com 
* https://juno.ihep.ac.cn/kanboard/

Example Paths
---------------

/junofs/users/lint/juno-release/J19v1r1-branch/jobs/geometry_acrylic.gdml

    still with torus 

Simon, this is Jilei's muon jobs: 

    /junofs/users/xujl/juno7/sim_results/J18v2r1/muon/twomu/optical/






Index
------

* https://bitbucket.org/simoncblyth/jnu/commits/
* http://juno.ihep.ac.cn/trac/timeline
* http://juno.ihep.ac.cn/mediawiki/index.php/InternalWeb
* http://juno.ihep.ac.cn/mediawiki/index.php/Offline_Software
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide
* https://juno.ihep.ac.cn/~offline/Doc/detsim/quickstart.html

*  http://juno.ihep.ac.cn/~offline/Doxygen/offline/html/files


OPTICKS_TOP envvar : a trick for Opticks developers working in peer-to-peer fashion 
---------------------------------------------------------------------------------------------

When OPTICKS_TOP is defined it overrides the opticks installation used by junoenv.
This makes it possible to use a separately installed Opticks installation.
 

/home/blyth/junotop/junoenv/junoenv-external-libs.sh::

    819 function junoenv-external-libs-list {
    820     local mode=$1
    821 
    822     [ -n "$OPTICKS_TOP" ] && echo opticks
    823 
    ### Ahem : should be checking CMTEXTRATAGS for opticks, not checking OPTICKS_TOP ?
    ### switched to :  [ "${CMTEXTRATAGS/opticks}" != "$CMTEXTRATAGS" ] && echo opticks

::

    096 function juno-ext-libs-opticks-generate-sh {
     97     local msg="====== $FUNCNAME :"
     98     local prefix=$(juno-ext-libs-opticks-install-dir)
     99     echo $msg replacing bashrc 
    100 
    101     # When OPTICKS_TOP is defined it overrides the opticks installation used by junoenv.
    102     # This makes it possible to use a separately installed Opticks installation.
    103 
    104 cat <<EOF > bashrc
    105 if [ -n "\${OPTICKS_TOP}" ]; then 
    106    source \${OPTICKS_TOP}/bin/opticks-setup.sh
    107 else
    108    source $prefix/bin/opticks-setup.sh
    109 fi
    110 EOF
    111 }
    112 function juno-ext-libs-opticks-generate-csh {
    113     local msg="SCB $FUNCNAME :"
    114     local prefix=$(juno-ext-libs-opticks-install-dir)
    115     echo $msg replacing tcshrc 
    116 
    117 cat <<EOF > tcshrc
    118 if [ -n "\${OPTICKS_TOP}" ]; then 
    119    source \${OPTICKS_TOP}/bin/opticks-setup.csh 
    120 else
    121    source $prefix/bin/opticks-setup.sh
    122 fi
    123 EOF
    124 }


Opticks JunoENV Links
----------------------

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#Install_Opticks_using_JunoENV
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation#building_the_offline_-DWITH_G4OPTICKS
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide/UsingOpticks


CMT Refs
----------

* https://svn.lal.in2p3.fr/projects/CMT/CMT/v1r10p20011126/doc/CMTDoc.html#Defining%20the%20user%20tags


Simulation
---------------

* http://juno.ihep.ac.cn/~offline/Doc/detsim/

* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Generator
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide
* https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Detsimuserguide/UsefulCommands
* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?conferenceid=236
* https://juno.ihep.ac.cn/cgi-bin/Dev_DocDB/DisplayMeeting?sessionid=381

cmt introspection
------------------

::

    cd ~/juno-tutorial
    source bashrc 
    cmt show packages 




EOU
}

j-env(){  echo -n ; }
j-dir(){ echo $(dirname $BASH_SOURCE) ; }
j-cd(){  cd $(j-dir) && pwd && git remote -v && git status ; }
j(){ j-cd ; }

ji(){ j-cd ; cd issues ; ls -lt | head -30 ;  }
j1(){ ji ; vi $(ls -1t | head -1) ; } 
j2(){ ji ; vi $(ls -1t | head -2 | tail -1) ; } 
jrst(){ j-cd ; vi $(ls -1t *.rst| head -1) ;  }


j-scp(){  
    local target=${1:-L7} 
    local cmd="scp $(j-dir)/j.bash $target:j/j.bash" 
    echo $cmd
    eval $cmd
}

jvi(){ vi $BASH_SOURCE ~/j/jx.bash && jfu ; }
jfu(){ source $BASH_SOURCE ; }



jm-help(){ cat << EON
jm-help : build offline using CMake machinery
================================================

jm-sdir : $(jm-sdir)
jm-bdir : $(jm-bdir)
jm-idir : $(jm-idir)

jm-scd jm-bcd jm-icd
    cd to respective dirs 

jm-cmake-has-opticks
    detect if CMAKE_PREFIX_PATH has the expected opticks prefixes 

jm-cmake- 
    emit to stdout the cmake commandline configuring with OR without Opticks depending on jm-cmake-has-opticks

jm-cmake
    after some directory checks runs the above cmake commandline 

jm-clean
    clean from the build directory 

jm-make
    make and install from from the CMake build directory 

jm
    short for jm-make 

EON
}


jm-junoenv-opticks(){
   local iwd=$PWD
   cd $JUNOTOP/junoenv
   bash junoenv opticks ${1:-info}
   cd $iwd
}

jm-hookup(){   jm-junoenv-opticks hookup   ; echo NOW start a new session to feel the effects ; }
jm-unhookup(){ jm-junoenv-opticks unhookup ; echo NOW start a new session to feel the effects ; }


jm-find-opticks-prefix(){
   local opticks_prefix
   local prefix
   for prefix in ${CMAKE_PREFIX_PATH//:/ } 
   do 
       [ -f "$prefix/include/OpticksCore/Opticks.hh" ] && opticks_prefix=$prefix
   done
   echo $opticks_prefix
}

jm-cmake-has-opticks(){

   : detecting opticks cmake prefixes within CMAKE_PREFIX_PATH
   : by existance of representative headers

   local with_opticks=0
   local with_opticks_package=0
   local with_opticks_externals=0
   local with_optix=0
   local prefix
   for prefix in ${CMAKE_PREFIX_PATH//:/ } 
   do 
       [ -f "$prefix/include/OpticksCore/Opticks.hh" ] && with_opticks_package=1  
       [ -f "$prefix/plog/include/plog/Severity.h" ]   && with_opticks_externals=1  
       [ -f "$prefix/include/optix.h" ]                && with_optix=1  
   done 

   if [ $with_opticks_package -eq 1 -a $with_opticks_externals -eq 1 -a $with_optix -eq 1 ]; then
       with_opticks=1
   fi 
   echo $with_opticks
}



j-curl-scp(){

   local msg="=== $FUNCNAME :"
   local url=$1
   local name=$2
   local dist=$(basename $url)

   cd /tmp
   [ ! -f "$name" ] && curl -L -O $url && mv $dist $name 
   local cmd="scp $name P:junotop/"

   echo $msg url $url name $name dist $dist 
   echo $msg $cmd 
   eval $cmd 

}


j-sniper-curl-scp(){

   : workaround GFW firewall github blockage 
   local msg="=== $FUNCNAME :"

   . $JUNOTOP/junoenv/junoenv-sniper.sh 

   local sv=$(junoenv-sniper-version)
   local mv=$(junoenv-mtsniper-version)

   local surl=$(junoenv-sniper-url $sv)
   local murl=$(junoenv-mtsniper-url $mv)

   local sbase=$(basename $surl)
   local sname=$(junoenv-sniper-name)-$sbase

   local mbase=$(basename $murl)
   local mname=sniper-$mbase     # duplicate bug in junoenv-sniper

   j-curl-scp $surl $sname
   j-curl-scp $murl $mname 
}



j-sniper-clean()
{
   cd $JUNOTOP/sniper || exit 1
   
   rm -rf build 
   rm -rf InstallArea
}



jm-bdir(){ echo $JUNOTOP/offline/build ; }
jm-idir(){ echo $JUNOTOP/offline/InstallArea ; }
jm-sdir(){ echo $JUNOTOP/offline  ; }

jm-bcd(){  cd $(jm-bdir) ; }
jm-icd(){  cd $(jm-idir) ; }
jm-scd(){  cd $(jm-sdir) ; }

jm-clean(){ 
   jm-bcd 
   make clean 
}

jm-cmake-extra(){   
   : opticks ON/OFF switch based on contents of CMAKE_PREFIX_PATH
   : DONE: avoided need for -DOPTICKS_PREFIX by setting from envvar in FindOpticks.cmake 
   : TODO: avoid need for -DCMAKE_MODULE_PATH by setting it based on OPTICKS_PREFIX envvar 
   :        this is needed separately because of chicken-and-egg issue

   local sdir=$(jm-sdir)
   local idir=$(jm-idir)

   local cmake_has_opticks=$(jm-cmake-has-opticks)
   local extra=""
   if [ "$cmake_has_opticks" == "1" ]; then 
       if [ -d "$JUNOTOP/opticks/cmake/Modules" ]; then 
           extra="$extra -DCMAKE_MODULE_PATH=$JUNOTOP/opticks/cmake/Modules"
       fi
    fi

   cat << EOC
   cmake $sdir \
         -DCMAKE_INSTALL_PREFIX=$idir \
         -DCMAKE_CXX_STANDARD=17 \
         $extra

EOC
}


jm-cmake-(){   
   : have moved the opticks ON/OFF switch inside the CMakeLists.txt based on OPTICKS_PREFIX envvar
   : in order to allow the JUNO standard cmake commandline to be used with no extras

   local sdir=$(jm-sdir)
   local idir=$(jm-idir)

   cat << EOC
   cmake $sdir \
         -DCMAKE_INSTALL_PREFIX=$idir \
         -DCMAKE_CXX_STANDARD=17 

EOC
}




jm-cmake(){   
   : j/j.bash using build layout from $JUNOTOP/junoenv/junoenv-offline.sh  junoenv-offline-compile-cmake
   : huh $JUNOTOP/offline/build.sh run-build has different cmake line withoec handling 
   : see j/opticks_with_cmake_offline.rst

   local msg="=== $FUNCNAME :"
   local sdir=$(jm-sdir)
   local bdir=$(jm-bdir)
   local idir=$(jm-idir)

   [ ! -d $sdir -o ! -d $bdir -o ! -d $idir ] && echo $msg use "bash junoenv offline" first  && return 1 

   jm-bcd

   local cmd=$(jm-cmake-)
   echo $msg cmd $cmd
   eval $cmd 
}

jm-make(){
   : j/j.bash 
 
   jm-bcd
   [ $? -ne 0 ] && echo bdir error && return 1 

   make 
   [ $? -ne 0 ] && echo make error && return 2

   make install
   [ $? -ne 0 ] && echo install error && return 3

   return 0 
}

jm(){ jm-make ; }




################### NAVIGATING  ###################################

jcv_(){ cat << EOC

JUNO Opticks Classes
-------------------------------


FastSimulationModel
~~~~~~~~~~~~~~~~~~~~~~

jcv junoPMTOpticalModel

    class junoPMTOpticalModel : public G4VFastSimulationModel

    epsilon:offline blyth$ jgl junoPMTOpticalModel.hh
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    ./Simulation/DetSimV2/PMTSim/src/MCP20inchPMTManager.cc       // NOT USED
    ./Simulation/DetSimV2/PMTSim/src/R12860PMTManager.cc          // NOT USED
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc



jcv MultiFilmModel
jcv OpticalSystem 
jcv Layer
jcv Matrix
jcv Material


::

    768 void
    769 HamamatsuR12860PMTManager::helper_fast_sim()
    770 {   
    771     G4Region* body_region = new G4Region(this->GetName()+"_body_region");
    772     body_log->SetRegion(body_region);
    773     body_region->AddRootLogicalVolume(body_log);
    774     
    775     junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
    776                                                                    body_phys, body_region);

    712 void
    713 NNVTMCPPMTManager::helper_fast_sim()
    714 {
    715     G4Region* body_region = new G4Region(this->GetName()+"_body_region");
    716     body_log->SetRegion(body_region);
    717     body_region->AddRootLogicalVolume(body_log);
    718 
    719     junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
    720                                                                    body_phys, body_region);


    021 junoPMTOpticalModel::junoPMTOpticalModel(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
     22     : G4VFastSimulationModel(modelName, envelope)
     23 {
     24     _photon_energy  = 0.;
     25     _wavelength     = 0.;
     ...
     63     whereAmI        = OutOfRegion;
     65     InitOpticalParameters(envelope_phys);
     67     m_multi_film_model = new MultiFilmModel(4);
     69 }


    281 void junoPMTOpticalModel::InitOpticalParameters(G4VPhysicalVolume* envelope_phys)
    282 {
    283     G4LogicalVolume* envelope_log
    284         = envelope_phys->GetLogicalVolume();
    285     G4MaterialPropertiesTable* glass_pt
    286         = envelope_log->GetMaterial()->GetMaterialPropertiesTable();
    287 
    288     _rindex_glass   = glass_pt->GetProperty("RINDEX");
    289     _inner1_phys    = envelope_log->GetDaughter(0);
    290     _inner1_solid   = _inner1_phys->GetLogicalVolume()->GetSolid();
    291     _rindex_vacuum  = _inner1_phys->GetLogicalVolume()->GetMaterial()
    292                                   ->GetMaterialPropertiesTable()->GetProperty("RINDEX");
    293 
    294     _inner2_phys    = envelope_log->GetDaughter(1);
    295     _inner2_solid   = _inner2_phys->GetLogicalVolume()->GetSolid();
    296 }




jgr HamamatsuMaskManager
~~~~~~~~~~~~~~~~~~~~~~~~~

jcv LSExpDetectorConstruction
jcv JUNODetSimModule

::

    epsilon:offline blyth$ jgr setPMTName
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    dc->setPMTName(m_pmt_name);
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     void setPMTName(const std::string& pmt_name) {m_pmt_name = pmt_name;}
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    dc->setPMTName(m_pmt_name);
    epsilon:offline blyth$ 

::

     31 DetSim0Svc::DetSim0Svc(const std::string& name)
     32     : SvcBase(name)
     33 {
     34     declProp("AnaMgrList", m_ana_list);
     35     declProp("CDName", m_cd_name="DetSim1");
     36     declProp("PMTName", m_pmt_name="PMTMask");
     37     declProp("LPMTExtra", m_extra_lpmt="ONE"); // ONE or TWO

    1609             detsimfactory.property("PMTName").set(args.pmt20inch_name)
    1610             detsimfactory.property("LPMTExtra").set(args.pmt20inch_extra)
    1611             if args.pmt20inch_name == "R12860":
    1612                 r12860 = sim_conf.tool("R12860PMTManager/PMT_20inch")
    1613                 r12860.property("FastCover").set(True)
    1614                 r12860.property("FastCoverMaterial").set("Water")
    1615             elif args.pmt20inch_name == "PMTMask":
    1616                 mask = sim_conf.tool("R12860MaskManager")
    1617                 mask.property("TopThickness").set(args.pmtmask_top_thick)
    1618             pass


    0312         grp_pmt_op.add_argument("--pmt20inch-name", default="PMTMask",
     313                                           choices = ["R12860", "OnlyPMT", "20inchPMT",
     314                                                    "R3600", "PMTMask",
     315                                                    "HamamatsuMask", "NNVTMask"
     316                                                    ],
     317                                           help=mh("20inch PMT name."))
     318 
     319         self.register_SWITCH_options(grp_pmt_op)
     320 
     321         grp_pmt_op.add_argument("--pmt20inch-extra", default="TWO-mask",
     322                                           choices = ["ONE", "TWO", "TWO-mask"],
     323                                           help=mh("ONE category or TWO categories of LPMT. TWO: pmts without mask. TWO-mask: pmts with mask"))
     324         grp_pmt_op.add_argument("--pmtmask-top-thick", default=10., type=float,



::

     450 LSExpDetectorConstruction::setupCentralDetector()
     451 { 
     452   // construct the Central Detector
     453   IDetElement* cd_det = 0;
     454   if (m_cd_name == "DetSim0" or m_cd_name == "DetSim1" or m_cd_name == "DetSim2") {
     455       std::string new_name = m_cd_name + "Construction";
     456       cd_det = det_elem(new_name);
     457   }
     458   

jcv DetSim1Construction::

    097     IPMTElement* pmt_elem_r12860 = 0; // R12860 w/ or w/o mask
     98     IPMTElement* pmt_elem_nnvt = 0; // NNVT w/ or w/o mask
     99     if (!other) {
    100         // retrieve
    101         // * get detsimalg 
    102         // * get pmt elem
    103         SniperPtr<DetSimAlg> detsimalg(*getParent(), "DetSimAlg");
    104         if (detsimalg.invalid()) {
    105             LogError << "Can't Load DetSimAlg" << std::endl;
    106             return false;
    107         }
    108         pmt_elem_r12860 = dynamic_cast<IPMTElement*>(detsimalg->findTool("HamamatsuR12860")); // need to define the official name
    109         pmt_elem_nnvt = dynamic_cast<IPMTElement*>(detsimalg->findTool("NNVTMCPPMT"));

    // WHY NO Manager ON THESE ? 


    110 
    111         LogInfo << "Mixing PMT mode: " << std::endl;
    112         LogInfo << "-> Get Hamamatsu R12860: " << pmt_elem_r12860 << std::endl;
    113         LogInfo << "-> Get NNVT MCPPMT: " << pmt_elem_nnvt << std::endl;
    114 
    115     } else {


    epsilon:sniper blyth$ find . -type f -exec grep -H findTool {} \;
    ./SniperKernel/SniperKernel/AlgBase.h:        ToolBase* findTool(const std::string& toolName);
    ./SniperKernel/SniperKernel/AlgBase.h:    return dynamic_cast<Type*>(this->findTool(toolName));
    ./SniperKernel/src/AlgBase.cc:            if ( 0 == this->findTool( result->objName() ) ) {
    ./SniperKernel/src/AlgBase.cc:ToolBase* AlgBase::findTool(const std::string& toolName)
    ./SniperKernel/src/binding/AlgBaseExp.cc:        .def("findTool",   &AlgBase::findTool,
    ./SniperKernel/src/DleSupervisor.cc:            return obj->findTool(name.substr(pseg+1, std::string::npos));
    epsilon:sniper blyth$ 

    061 ToolBase* AlgBase::findTool(const std::string& toolName)
     62 {
     63     auto it = m_tools.find(toolName);
     64     if ( it != m_tools.end() ) {
     65         return (*it).second;
     66     }
     67     //LogInfo << "cannot find tool: " << toolName << std::endl;
     68     return nullptr;
     69 }

    054 
     55         std::map<std::string, ToolBase*>  m_tools;
     56 };
     57 
     58 template<typename Type>
     59 Type* AlgBase::tool(const std::string& toolName)
     60 {
     61     return dynamic_cast<Type*>(this->findTool(toolName));
     62 }

    036 ToolBase* AlgBase::createTool(const std::string& toolName)
     37 {   
     38     DLElement* obj = DLEFactory::instance().create(toolName);
     39     if ( obj != 0 ) {
     40         ToolBase* result = dynamic_cast<ToolBase*>(obj);
     41         if ( result != 0 ) {
     42             if ( 0 == this->findTool( result->objName() ) ) {
     43                 result->setParent(this->getParent());
     44                 m_tools.insert(std::make_pair(result->objName(), result));
     45                 return result;
     46             }

    038 DLElement* DLEFactory::create(const std::string& name)
     39 {
     40     std::string type = name;
     41     std::string nobj = name;
     42     std::string::size_type pseg = name.find('/');
     43     if ( pseg != std::string::npos ) {
     44         type = type.substr(0, pseg);
     45         nobj = nobj.substr(pseg+1, std::string::npos);
     46     }
     47 
     48     Type2CreatorMap::iterator it = m_creators.find(type);
     49     if ( it != m_creators.end() ) {
     50         DLElement* result = (it->second)(nobj);
     51         result->setTag(type);
     52         return result;
     53     }

    049 
     50         typedef std::map<std::string, DLECreator> Type2CreatorMap;
     51 
     52         //standard constructor
     53         DLEFactory();
     54         ~DLEFactory();
     55 
     56         //members
     57         std::string      m_name;
     58         Type2CreatorMap  m_creators;



    1280     def init_detector_simulation(self, task, args):
    1281         import DetSimOptions
    1282         sim_conf = None
    1283         if args.detoption == "Acrylic":
    1284             from DetSimOptions.ConfAcrylic import ConfAcrylic
    1285             acrylic_conf = ConfAcrylic(task)
    1286             acrylic_conf.configure()
    1287             sim_conf = acrylic_conf
    ....
    1627             if args.pmt20inch_extra == "TWO":

    1628                 log.info("TWO . args.pmt20inch_extra %s " % args.pmt20inch_extra)
    1629                 nnvt_mcp_pmt = sim_conf.tool("NNVTMCPPMTManager/NNVTMCPPMT")
    1630                 nnvt_mcp_pmt.property("FastCover").set(True)
    1631                 nnvt_mcp_pmt.property("FastCoverMaterial").set("Water")
    1632                 nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1633 
    1634                 hamamatsu_pmt = sim_conf.tool("HamamatsuR12860PMTManager/HamamatsuR12860")
    1635                 hamamatsu_pmt.property("FastCover").set(True)
    1636                 hamamatsu_pmt.property("FastCoverMaterial").set("Water")
    1637                 hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)

    1638             elif args.pmt20inch_extra == "TWO-mask":

    //// THIS IS DEFAULT 

    1639                 log.info("TWO-mask . args.pmt20inch_extra %s " % args.pmt20inch_extra)
    1640                 nnvt_mcp_pmt = sim_conf.tool("NNVTMCPPMTManager/NNVTMCPPMT_PMT_20inch")
    1641                 nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1642                 nnvt_mcp_pmt.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1643 
    1644                 nnvt_mcp_mask = sim_conf.tool("NNVTMaskManager/NNVTMCPPMT")
    1645                 nnvt_mcp_mask.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1646                 nnvt_mcp_mask.property("UseRealMaskTail").set(args.real_mask_tail)
    1647                 nnvt_mcp_mask.property("UseMaskTailOpSurface").set(args.mask_tail_surface_enabled)
    1648    
    1649                 hamamatsu_pmt = sim_conf.tool("HamamatsuR12860PMTManager/HamamatsuR12860_PMT_20inch")
    1650                 hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1651                 hamamatsu_pmt.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1652 
    1653                 hamamatsu_mask = sim_conf.tool("HamamatsuMaskManager/HamamatsuR12860")       
    1654                 hamamatsu_mask.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1655                 hamamatsu_mask.property("UseRealMaskTail").set(args.real_mask_tail)
    1656                 hamamatsu_mask.property("UseMaskTailOpSurface").set(args.mask_tail_surface_enabled)
    1657 
    1658             else:


    //// THE OBJECT NAMES ARISING FROM THE BELOW ARE CONFUSING AS THEY DO NOT INCLUDE "Mask" 
    ////
    ////          nnvt_mcp_mask = sim_conf.tool("NNVTMaskManager/NNVTMCPPMT")
    ////          hamamatsu_mask = sim_conf.tool("HamamatsuMaskManager/HamamatsuR12860") 
    ////


    067     def tool(self, toolname):
     68         if not self._detsimalg:
     69             self.configure()
     70         if self._detsimalg.findTool(toolname):
     71             return self._detsimalg.findTool(toolname)
     72 
     73         return self._detsimalg.createTool(toolname)




jcv HamamatsuR12860PMTManager::

     31 #ifdef PMTSIM_STANDALONE
     32 #else
     33 DECLARE_TOOL(HamamatsuR12860PMTManager);
     34 #endif
      

jcv NNVTMCPPMTManager::

     40 #ifdef PMTSIM_STANDALONE 
     41 #else
     42 DECLARE_TOOL(NNVTMCPPMTManager);
     43 #endif

SniperKernel/SniperKernel/ToolFactory.h::

     22 #include "SniperKernel/DeclareDLE.h"
     23 #define DECLARE_TOOL(ToolClass) SNIPER_DECLARE_DLE(ToolClass)


::

     24 class DLElement;
     25 
     26 struct SniperBookDLE
     27 {
     28     SniperBookDLE() = delete;
     29     SniperBookDLE(const SniperBookDLE&) = delete;
     30     SniperBookDLE& operator=(const SniperBookDLE&) = delete;
     31 
     32     typedef DLElement* (*DLECreator)(const std::string&);
     33     SniperBookDLE(const std::string& type, DLECreator creator);
     34 };
     35 
     36 #define SNIPER_DECLARE_DLE(DLEClass) \
     37 DLElement* sniper_DLE_##DLEClass##_creator_(const std::string& name) { \
     38    return new DLEClass(name); \
     39 } \
     40 SniperBookDLE sniper_book_DLE_##DLEClass##_(#DLEClass, &sniper_DLE_##DLEClass##_creator_)
     41 




Simulation/DetSimV2/PhysiSim
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* C + S genstep collection 

jcv LocalG4Cerenkov1042
jcv DsG4Scintillation
jcv DsPhysConsOptical


Simulation/DetSimV2/PMTSim
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* sensitive detector, calling G4Opticks::propagate, handling hits 

jcv junoSD_PMT_v2
jcv junoSD_PMT_v2_Opticks
jcv PMTEfficiencyCheck
jcv PMTSDMgr


Simulation/DetSimV2/AnalysisCode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jcv G4OpticksAnaMgr      # top level passing to G4OpticksRecorder 


Simulation/DetSimV2/DetSimOptions
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jcv DetSim0Svc
jcv LSExpDetectorConstruction_Opticks

    1. invokes G4Opticks::setEmbeddedCommandLineExtra(embedded_commandline_extra) using 
       geospecific default argument : "--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge"
       which can be overridden with LSXDC_GEOSPECIFIC

    2. passes geometry to G4Opticks for translation 


Simulation/GenTools
~~~~~~~~~~~~~~~~~~~~~~~

jcv GtOpticksTool
 
    Input photons mutate 


Simulation/DetSimV2/AnalysisCode
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

jcv G4OpticksAnaMgr


Opticks Integration Classes
-----------------------------

jgr _Opticks

jcv junoSD_PMT_v2_Opticks
    Invokes Opticks GPU optical photon simulation at the EndOfEvent
    Hit handling, conversion 

jcv LSExpDetectorConstruction_Opticks 
    Setup function, geometry translation, collect efficiencies
 


JUNO Classes Particularly Pertinent to Opticks 
--------------------------------------------------

jcv tut_detsim
jcv JUNODetSimModule


jcv LSExpDetectorConstruction

   top level that skips : setupCD_Sticks(cd_det);

    +#ifdef WITH_G4OPTICKS
    +#include "PLOG.hh"
    +#endif


    +#ifdef WITH_G4OPTICKS
    +  LOG(fatal) << " OPTICKS DEBUGGING : SKIP LSExpDetectorConstruction::setupCD_Sticks " ; 
    +#else
       setupCD_Sticks(cd_det);
    +#endif




jcv StrutAcrylicConstruction

   sStrut : Steel 1:G4Tubs

jcv StrutBar2AcrylicConstruction

   sStrut : lSteel2 

jcv StrutBallheadAcrylicConstruction

   sStrutBallhead : lSteel : G4Orb   

jcv FastenerAcrylicConstruction

   uni1 : union of 1:IonRing + 8:screw G4Tubs

jcv UpperAcrylicConstruction

   base_steel : lUpper : G4Polycone 

jcv AdditionAcrylicConstruction

   ~/opticks_refs/computing_csg_tree_boundaries_as_algebraic_expressions.pdf
    

   1. solidAddition_down polycone z: 5.7,0,-140  rmax:450,450,200  : the outer 
   2. uni_acrylic1 : subtract the acrylic sphere 
   3. uni_acrylic2 : subtract ring tubs z:[ -4.8, -35.2] r:[120,208]
   4. uni_acrylic3 : subtract 8 rods 


   0110         double RmaxNodes3[3];
    111         ZNodes3[0] = 5.7*mm; RminNodes3[0] = 0*mm; RmaxNodes3[0] = 450.*mm;
    112         ZNodes3[1] = 0.0*mm; RminNodes3[1] = 0*mm; RmaxNodes3[1] = 450.*mm;
    113         ZNodes3[2] = -140.0*mm; RminNodes3[2] = 0*mm; RmaxNodes3[2] = 200.*mm;
    114 
    115         solidAddition_down = new G4Polycone("solidAddition_down",0.0*deg,360.0*deg,3,ZNodes3,RminNodes3,RmaxNodes3);

                       np.array( [ 5.7, 0.0, -140.0 ] )    # polycone z-levels 


    116 
    117     }
    118 
    119 
    120 //    solidAddition_down = new G4Tubs("solidAddition_down",0,199.67*mm,140*mm,0.0*deg,360.0*deg);
    121 //    solidAddition_down = new G4Cons("solidAddition_down",0.*mm,450.*mm,0.*mm,200*mm,70.*mm,0.*deg,360.*deg);
    122     solidAddition_up = new G4Sphere("solidAddition_up",0*mm,17820*mm,0.0*deg,360.0*deg,0.0*deg,180.*deg);
    123 
    124     uni_acrylic1 = new G4SubtractionSolid("uni_acrylic1",solidAddition_down,solidAddition_up,0,G4ThreeVector(0*mm,0*mm,+17820.0*mm));
              "polycone-sagitta"

    125 
    126     solidAddition_up1 = new G4Tubs("solidAddition_up1",120*mm,208*mm,15.2*mm,0.0*deg,360.0*deg);
                                                              rmin   rmax    hz

                         15.2*0.01 = 0.152 

                          np.array([15.2, -15.2])-20.  = array([ -4.8, -35.2])    ring tubs z-range

                          zz = np.array([15.2, -15.2])*1.01 - 20.0     = array([ -4.648, -35.352])



                    cx ; ISEL=0,1,2,3 ZZ=5.7,0.0,-140.0,-4.8,-35.2,-4.648,-35.352 ./cxs.sh py 

                    cx ; ISEL=0,1,2,3 ZZ=-4.648,-4.8,-35.2,-35.352 SZ=5.0 LOOK=-140.,0.,-20 ZOOM=5 ./cxs.sh py 




             recall that a cylinder with non-zero rmin is implemented as a CSG subtraction

                   fullcyl - smallcyl  = fullcyl intersect !smallcyl

             subtracting that may give spurious coincidence edge 


             BUT : X4Solid::convertTubs_cylinder  does expand the hz for subtracted by 0.01 


             opticks has excess of :  SI BT BT BT BT AB




    127     uni_acrylic2 = new G4SubtractionSolid("uni_acrylic2",uni_acrylic1,solidAddition_up1,0,G4ThreeVector(0.*mm,0.*mm,-20*mm));

                    

    128     solidAddition_up2 = new G4Tubs("solidAddition_up2",0,14*mm,52.5*mm,0.0*deg,360.0*deg);
               
                rod that keeps getting subtracted              rmin/rmax/zheight?

                          np.array([52.5, -52.5]) - 87.5 = array([ -35., -140.])    rods z-range 
 
                   

    129 
    130     for(int i=0;i<8;i++)
    131     {
    132     uni_acrylic3 = new G4SubtractionSolid("uni_acrylic3",uni_acrylic2,solidAddition_up2,0,G4ThreeVector(164.*cos(i*pi/4)*mm,164.*sin(i*pi/4)*mm,-87.5));
    133     uni_acrylic2 = uni_acrylic3;
    134 
    135     }



    epsilon:offline blyth$ jgl uni1
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc

jcv FastenerAcrylicConstruction

    179     // Update new acrylic nodes
    180     // YuMiao
    181     //
    182 
    183 
    184     G4Tubs *IonRing = new G4Tubs("IonRing",123*mm,206.2*mm,7*mm,0.0*deg,360.0*deg);

                   // np.array( [123.0, 206.2 ] )
                   // np.array([7, -7]) 
                   //     np.array([7, -7])  - 20  = np.array([-13, -27])


    185     G4Tubs* screw = new G4Tubs("screw",0,13*mm,50.*mm,0.0*deg,360.0*deg);

                   // np.array(  [0, 13.] )
                   // np.array(  [50, -50] )

    186     uni_Addition = IonRing;
    187     for(int i=0;i<8;i++)
    188     {
    189         G4UnionSolid* uni1 = new G4UnionSolid("uni1",uni_Addition, screw, 0, G4ThreeVector(164.*cos(i*pi/4)*mm, 164.*sin(i*pi/4)*mm,-65.0*mm));
    190         uni_Addition = uni1;

                 //  np.array(  [50, -50] ) - 65  = np.array([ -15, -115])

                 // observe  np.array( [ -35., -135. ] )    =    np.array([ -15, -115]) - 20.   


                 // LOOK=-164,0,-85 ZOOM=4 ISEL=0,1,2 ./cxs.sh 


    191     }
    192 
    193 
    194       logicFasteners = new G4LogicalVolume(
    195       uni_Addition,//solidFasteners, 
    196       Steel,
    197       "lFasteners",
    198       0,
    199       0,
    200       0);
    201 





jcv NNVTMCPPMTManager

    243 void
    244 NNVTMCPPMTManager::helper_make_solid()
    245 {   
    246     pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    247     
    248     double inner_delta = -5*mm ;
    249     if(!m_enable_optical_model)
    250     {
    251         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid");
    252     }
    253     else
    254     {
    255         // For the new PMT optical model. In fact, no impact on PMT geometry, just for safety
    256         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid", inner_delta+1E-3*mm);
    257     }
    258     inner_solid= m_pmtsolid_maker->GetSolid(GetName()+"_inner_solid", inner_delta );
    259     

    297 void
    298 NNVTMCPPMTManager::helper_make_logical_volume()
    299 {
    /// thickness: 0.
    300     body_log= new G4LogicalVolume
    301         ( body_solid,
    302           GlassMat,
    303           GetName()+"_body_log" );
    304 
    /// thickness: 1E-3*mm
    305     m_logical_pmt = new G4LogicalVolume
    306         ( pmt_solid,
    307           GlassMat,
    308           GetName()+"_log" );
    309 
    310     body_log->SetSensitiveDetector(m_detector);
    311 
    312     inner1_log= new G4LogicalVolume
    313         ( inner1_solid,
    314           PMT_Vacuum,
    315           GetName()+"_inner1_log" );
    316     inner1_log->SetSensitiveDetector(m_detector);
    317 
    318     inner2_log= new G4LogicalVolume
    319         ( inner2_solid,
    320           PMT_Vacuum,
    321           GetName()+"_inner2_log" );
    322 



    thickness  

    * pmt_solid  : 1E-3*mm      // < this is asking for trouble 
    * body_solid : 0. 


jcv NNVT_MCPPMT_PMTSolid
    my ascii-art diagram explaining the CSG modelling of the NNVT PMT Solid

    G4VSolid* GetSolid(G4String solidname, double thickness=0.0, char mode=' ');
    NG4VSolid* NVT_MCPPMT_PMTSolid::GetSolid(G4String solidname, double thickness, char mode) 


jcv HamamatsuR12860PMTManager

    239 void
    240 HamamatsuR12860PMTManager::helper_make_solid()
    241 {
    242     pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    243     double inner_delta =  -5*mm ;
    244     if(!m_enable_optical_model)
    245     {
    246         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid");
    247     }
    248     else
    249     {
    250         // For the new PMT optical model. In fact, no impact on PMT geometry, just for safety
    251         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid", inner_delta+1E-3*mm);
    252     }
    253 
    254     inner_solid= m_pmtsolid_maker->GetSolid(GetName()+"_inner_solid", inner_delta );
    255 

    * again thickness delta of 1E-3*mm 



jcv Hamamatsu_R12860_PMTSolid
   
    G4VSolid* GetSolid(G4String solidname, double thickness=0.0, char mode=' ');

jcv LSExpDetectorConstruction

    





EOC
}




# -false to end sequence of ors 
#
# HMM jcl jcld fails when the * shell expansion find the files in the invoking directory 
# as that messes up the find command
# double quoting the f gets some way but somehow messes up other things
# HENCE: use jcl jfi from top level where shell expansion will not find the files in the invoking directory 

jcld(){ local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ; echo find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 
jcl(){  local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ;      find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 
jfi(){  local f="" ; for name in $* ; do f="$f -name $name   -o " ; done ;      find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 


jps_add(){
    local extra
    for extra in $* 
    do 
        case $extra in
           *.hh) drel=Simulation/DetSimV2/PMTSim/include ;;
            *.h) drel=Simulation/DetSimV2/PMTSim/src     ;;   # local convention for private headers 
           *.cc) drel=Simulation/DetSimV2/PMTSim/src     ;;  
        esac
        echo cp $extra $JUNOTOP/offline/$drel/$extra 
    done
}



jcopy(){  
   : copy classes from offline into PWD 
   local dst=$PWD
   local src=$JUNOTOP/offline
   cd $src
   local rels=$(jcl $*)    # paths relative to PWD for all the class name arguments 
   local rel 
   local name 
   local path
   local cmd
   local spath

   for rel in $rels 
   do  
       name=$(basename $rel)
       path=$dst/$name

       if [ ! -f "$path" ]; then 
           cmd="cp $rel $path"
           echo $cmd
           eval $cmd 
       fi  
   done 
   cd $dst 
}


jcopyback_notes(){ cat <<EON

NB to actually do the copies must pipe the commands to sh 

::

    N[blyth@localhost offline]$ jps
    # On branch main
    nothing to commit, working directory clean

    N[blyth@localhost PMTSim]$ jcopyback HamamatsuMaskManager NNVTMaskManager
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    cp /home/blyth/j/PMTSim/NNVTMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    cp /home/blyth/j/PMTSim/NNVTMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc

EON
}

jcopyback(){
   : j/j.bash 
   : emit copy commands to copy classes from PWD eg from jps back into offline SVN 

   local iwd=$PWD
   local src=$iwd
   local dst=$JUNOTOP/junosw
   cd $dst

   local rels=$(jcl $* | sort )    # paths relative to PWD for all the class name arguments 
   local rel 
   local name 
   local path
   local cmd
   local spath
   local dpath

   for rel in $rels 
   do  
       name=$(basename $rel)
       spath=$src/$name
       dpath=$dst/$rel

       if [ -f "$spath" ]; then 
           cmd="cp $spath $dpath"
           echo $cmd
       fi  
   done 

   cd $iwd
}


jdiff(){

   : j/j.bash 
   : Compares files from current directory specified by stem arguments
   : to files with same stems found under JUNOTOP/junosw : formerly offline 
   : NB this must be run from the directory such as j/PMTSim with the modified files

   local iwd=$PWD
   local dst=$iwd
   local src=$JUNOTOP/junosw
   cd $src
   local rels=$(jcl $*)
   : rels are JUNOTOP/junosw relative paths 

   local rel 
   local name 
   local path
   local cmd
   local spath

   for rel in $rels 
   do  
       name=$(basename $rel)
       path=$dst/$name
       spath=$src/$rel
       if [ -f "$path" -a -f "$spath" ]; then 
           cmd="diff $spath $path"
           echo $cmd
       fi  
   done 
   cd $iwd   
   # tis impolite to leave function without returning to initial dir 
}


jlibs-usage(){ cat << EOU


    jlibs-
        lists all libs

    jlibs- ROOT:
        lists selection of libs starting from ROOT

    jlibs- ROOT+
        lists selection of libs starting from the lib after ROOT which is currently hepmc 


    jlibs
        build all libs

    jlibs ROOT:
        build selection of libs starting from ROOT

    jlibs ROOT+
        build selection of libs starting from the lib after ROOT which is currently hepmc 



    jlibs_reuse
        plants symbolic links for ExternalLibs assuming JUNO_EXTLIB_OLDTOP points to the dir

        This is especially useful on shared machines like lxslc7 where prior ExternalLibs
        are available and where building everything (especially ROOT) is really slow.


        ::

            cd $JUNOTOP ; mv ExternalLibs ExternalLibs_old

            L7[blyth@lxslc701 junotop]$ l ExternalLibs/Python/
            total 12
            4 drwxr-xr-x 35 blyth dyw 4096 Dec  3 02:59 ..
            4 drwxr-xr-x  2 blyth dyw 4096 Dec  3 02:58 .
            4 lrwxrwxrwx  1 blyth dyw   97 Dec  3 02:58 3.8.12 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Python/3.8.12
            L7[blyth@lxslc701 junotop]$ l ExternalLibs/Geant4/
            total 12
            4 drwxr-xr-x 35 blyth dyw 4096 Dec  3 02:59 ..
            4 drwxr-xr-x  2 blyth dyw 4096 Dec  3 02:59 .
            4 lrwxrwxrwx  1 blyth dyw  105 Dec  3 02:59 10.04.p02.juno -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Geant4/10.04.p02.juno
            L7[blyth@lxslc701 junotop]$ 



EOU
}

jlibs-()
{
   local arg=$1
   case $arg in
      *:) mode=: ; first=${arg/:*} ;;
      *+) mode=+ ; first=${arg/+*} ;;
   esac

   cd $JUNOTOP/junoenv;
   local libs=$(bash junoenv libs list | perl -ne 'm, (\S*)@, && print "$1\n"' -); 
   local sel=0   
   for sub in $libs;
   do
       [ -z "$arg" ] && sel=1 
       [ "${sub}" == "$first" -a "${mode}" == ":" ] && sel=1 
       [ "${sub}" == "$first" -a "${mode}" == "+" ] && sel=2 
       [ "$sel" == "1" ] && echo $sub
       [ "$sel" == "2" ] && sel=1
   done
}   

jlibs()
{
   local libs=$(jlibs-)
   for lib in $libs
   do
        echo $lib
        bash junoenv libs all $lib || return 1
   done
   return 0 
}


jdevtoolset8()
{
   source /opt/rh/devtoolset-8/enable
}

jcompiler()
{
    : devtoolset-8 gcc not supported by ROOT
    : so follow lint example from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-Pre0/quick-deploy-J21v2r0-Pre0.sh
    : and use JUNO gcc from cvmfs

    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc

    : sets    : JUNO_GCC_PREFIX, CC, CXX, FC
    : appends : PATH, LD_LIBRARY_PATH, MANPATH, INFOPATH
    :
    
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc

    : sets    : JUNO_BINUTILS_PREFIX
    : appends : PATH, LD_LIBRARY_PATH, MANPATH, INFOPATH
   
}

jlibs_oldtop()
{
    export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs 
}


j-sniper-hookup(){
   : curriously this is not how sniper is typically hooked up see j-runtime-env-
   cat << EOA >> $JUNOTOP/bashrc.sh 
source $JUNOTOP/sniper/InstallArea/bashrc
source $JUNOTOP/mt.sniper/InstallArea/bashrc
EOA
}


jlibs_reuse()
{
   [ -z "$JUNO_EXTLIB_OLDTOP" ]   && echo $FUNCNAME requires envvar JUNO_EXTLIB_OLDTOP && return 1
   [ ! -d "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires directory JUNO_EXTLIB_OLDTOP $JUNO_EXTLIB_OLDTOP  && return 2

   local libs=$(jlibs-)
   for lib in $libs
   do
        echo $lib
        bash junoenv libs reuse $lib || return 1
   done
   return 0 
}



jcv-(){ local fi=$(jcl $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }
jfv-(){ local fi=$(jfi $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }

jcv(){ cd $JUNOTOP/offline ; jcv- $* ; : edit files identified by stem ;  } 
jfv(){ cd $JUNOTOP/offline ; jfv- $* ; : list files identified by wildcard ; } 

jgr-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -H "${1:-G4OPTICKS}" {} \; ; } 
jgr(){ cd $JUNOTOP/offline ; jgr- $* ; : search files with the query string and show matches - skips are made to avoid cmt garbage ;  } 

jgl-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -l "${1:-G4OPTICKS}" {} \; ; }
jgl(){ cd $JUNOTOP/offline ; jgl- $* ; : search files with the query string and list matched paths - skips are made to avoid cmt garbage ; } 
 
jt(){ cd $JUNOTOP ; pwd ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/offline && pwd && git status ; } 

jk(){ cd $JUNOTOP/opticks && pwd && git status ; } 
js(){ cd $JUNOTOP/offline/Simulation/DetSimV2/$1 && pwd ; } 
jr(){ echo CMAKE_PREFIX_PATH ; echo $CMAKE_PREFIX_PATH | tr ":" "\n" ; echo OPTICKS_PREFIX $OPTICKS_PREFIX ;  } 

psi(){ js PMTSIM/src ; }
#jb(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/cmt && pwd ; } 
#jp(){ cd $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge/src/phys && pwd ; } 
td(){ vi $JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py ; }
jsd(){ jcv junoSD_PMT_v2 ; }
jdsm(){ jcv JUNODetSimModule ; }

jsdo(){ jcv junoSD_PMT_v2_Opticks ;  }
jsc(){ jcv DsG4Scintillation ; }
jck(){ jcv G4Cerenkov_modified ; }
jop(){ jcv DsPhysConsOptical ;  }
jac(){ jcv AdditionAcrylicConstruction ; }
jps(){  cd $HOME/j/PMTSim ; git status ; }
jpo(){  cd $HOME/j/PosFile ; git status ; }

#jcvv(){ jcv NNVT_MCPPMT_PMTSolid Hamamatsu_R12860_PMTSolid ; }
#jcvv(){ jcv Hamamatsu_R12860_PMTSolid ; }
jcvv(){ jcv NNVTMCPPMTManager NNVT_MCPPMT_PMTSolid HamamatsuR12860PMTManager Hamamatsu_R12860_PMTSolid ; }

gb(){ cd $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 && pwd ; } 

jf(){
   type jt
   type je
   type jo
   type js
   type psi
   type jb  
   type jp
   type td
   type gb  
}


jokc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}

j-find-(){ cat << EOC
find . -name '*.cc'  -exec grep -H G4OPTICKS {}  
find . -name '*.cc'  -exec grep -H g4opticks {} 
find . -name '*.cc'  -exec grep -H g4ok {} 
find . -name '*.py'  -exec grep -H opticks {} 
EOC
}

j-find(){
    local line
    cd $JUNOTOP/offline
    j-find- | while read line ; do 
        echo "$line \;"
        eval "$line \;"
    done 
}

################### INSTALLATION ###################################


j-install-url(){ echo https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation ; }
j-install-open(){ open $(j-install-url) ; }

j-install(){
    :   https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
    j-install-junotop
    [ $? -ne 0 ] && return 1 
    j-install-junoenv
    [ $? -ne 0 ] && return 2
    j-install-preq 
    [ $? -ne 0 ] && return 3
    j-install-libs 
    [ $? -ne 0 ] && return 4
    j-install-runtime
    [ $? -ne 0 ] && return 5
    j-install-cmtlibs
    [ $? -ne 0 ] && return 6
    j-install-sniper
    [ $? -ne 0 ] && return 7
    j-install-offline
    [ $? -ne 0 ] && return 8
    j-install-offline-data
    [ $? -ne 0 ] && return 9

    j-install-opticks          ## does nothing without pre-requisite envvars
    [ $? -ne 0 ] && return 10

    return 0 
}

j-install-junotop(){ 
    local msg="=== $FUNCNAME :"
    echo $msg JUNOTOP $JUNOTOP 
    [ -z "$JUNOTOP" ] && echo $msg JUNOTOP is not defined && return 1 
    mkdir -p $JUNOTOP ; 
    [ ! -d "$JUNOTOP" ] && echo $msg failed to create JUNOTOP dir && return 2
    return 0 
}
j-install-junoenv(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP
    if [ -d junoenv ]; then 
        echo junoenv directory already exists 
    else 
        svn co https://juno.ihep.ac.cn/svn/offline/trunk/installation/junoenv
    fi 
    [ ! -d junoenv ] && echo $msg failed to checkout junoenv && return 1 
    return 0
}
j-install-preq(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP/junoenv
    case $(uname -n) in
     lxslc*) echo $msg assuming preq are satisfied on $(uname -n)  ;;
          *) bash junoenv preq  ;;
    esac
}

j-install-libs-list(){          cd $JUNOTOP/junoenv ; bash junoenv libs list ; }
j-install-libs-all(){           j-install-libs-list | perl -ne 'm, (\S*)@, && print "$1\n"' - ; }
j-install-libs-installed(){     j-install-libs-list | perl -ne 'm, \[x\]\s*(\S*)@, && print "$1\n"' - ; }
j-install-libs-uninstalled(){   j-install-libs-list | perl -ne 'm, \[ \]\s*(\S*)@, && print "$1\n"' - ; }
j-install-lib-deps(){           j-install-libs-list | grep ${1}@ | perl -ne 'm,-\> (.*)$, && print "$1\n"' - ; }

j-install-item-in-list(){
    local item=$1 ; shift 
    local list=$*
    local x 
    for x in $list ; do  [ "$item" == "$x" ] && return 0  ; done
    return 1 
}

j-install-lib-canbuild(){
    : hmm need to accomodate the plus meaning optional perhaps ?
    local lib=$1
    local installed=$(j-install-libs-installed)
    local deps=$(j-install-lib-deps $lib)
    local dep
    for dep in $deps ; do 
        if [ "${dep:0:1}" != "+" ]; then     # skippin the + : is that appropriate 
            j-install-item-in-list $dep $installed 
            [ $? -eq 1 ] && echo $msg missing dependency $dep to build lib $lib && return 1 
        fi 
    done
    return 0 
}

j-install-lib(){
    local msg="=== $FUNCNAME :"
    local lib=$1


    local mkr=$JUNOTOP/junoenv/.j-libs/$lib
    mkdir -p $(dirname $mkr)
    if [ -f "$mkr" ]; then 
        printf "$msg skipping %-20s as mkr exists : $mkr \n" $lib 
    else
        j-install-lib-canbuild $lib
        [ $? -ne 0 ] && echo $msg cannot build lib $lib due to missing dependency && return 1

        bash junoenv libs all $lib 
        [ $? -ne 0 ] && echo $msg ERROR with lib $lib && return 1
        touch $mkr
    fi
}

j-install-libs(){
    local msg="=== $FUNCNAME :"
    echo $msg 
    cd $JUNOTOP/junoenv
    local libs=$(j-install-libs-all)
    for lib in $libs ; do 
        j-install-lib $lib
    done  
    return 0
}    

j-install-runtime-()
{
    local runtime=$JUNOTOP/bashrc.sh
    cd $JUNOTOP/junoenv
    bash junoenv env
    [ ! -s "$runtime" ] && echo $msg failed to create runtime env file $runtime && return 1
    return 0  
}
j-install-runtime()
{
    : setup the runtime environment script JUNOTOP/bashrc.sh 
    local runtime=$JUNOTOP/bashrc.sh
    if [ ! -s "$runtime" ]; then 
        j-install-runtime-
        [ $? -ne 0 ] && return 1 
    fi 
    source $runtime
    return 0 
}

j-install-runtime-resetup()
{
    : create JUNOTOP/bashrc.sh script that sets up the runtime environment usage of the externals
    local msg="=== $FUNCNAME :"

    cd $JUNOTOP/junoenv
    bash junoenv env resetup
    [ $? -ne 0 ] && echo $msg FAIL at env && return 1

    local runtime=$JUNOTOP/bashrc.sh
    source $runtime
}


j-install-cmtlibs()
{
    : building the interface between cmt and external libraries
    : checks out https://juno.ihep.ac.cn/svn/cmtlibs/trunk into $JUNOTOP/ExternalInterface
    :
    : https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation
    :
    : http://juno.ihep.ac.cn/svn/cmtlibs/trunk
    :    EIRelease/
    :    Externals/
    :    cmt/
    :

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv cmtlibs
    [ $? -ne 0 ] && echo $msg failed cmtlibs && return 1 

    cd $JUNOTOP/ExternalInterface/EIRelease/cmt/ && source setup.sh
    [ $? -ne 0 ] && echo $msg failed EIRelease setup && return 2 

    cd $JUNOTOP/junoenv

    return 0 
}

j-install-sniper()
{
    : building the sniper

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv sniper
    [ $? -ne 0 ] && echo $msg failed && return 1 

    cd $JUNOTOP/sniper/SniperRelease/cmt/ && source setup.sh
    [ $? -ne 0 ] && echo $msg failed && return 2

    return 0 
}


j-install-offline()
{
    : building the offline
    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv

    bash junoenv offline
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}

j-install-offline-data()
{
    : install offline data to $JUNOTOP/data

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv

    bash junoenv offline-data
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}


j-install-opticks-()
{
    : building the opticks

    local msg="=== $FUNCNAME :"
    cd $JUNOTOP/junoenv
    bash junoenv opticks
    [ $? -ne 0 ] && echo $msg failed && return 1 

    return 0 
}

j-install-opticks-envdump()
{
    local vars="OPTICKS_CUDA_PREFIX OPTICKS_OPTIX_PREFIX OPTICKS_COMPUTE_CAPABILITY"
    local var
    for var in $vars ; do printf "%-30s : %s \n" $var ${!var} ; done 
}

j-install-opticks()
{
    local msg="=== $FUNCNAME: "
    if 
        [ -n "$OPTICKS_CUDA_PREFIX" -a -d "$OPTICKS_CUDA_PREFIX" ] &&
        [ -n "$OPTICKS_OPTIX_PREFIX" -a -d "$OPTICKS_OPTIX_PREFIX" ] &&
        [ -n "$OPTICKS_COMPUTE_CAPABILITY" ] 
    then 
        echo $msg environment looks ready to install opticks   
        j-install-opticks-envdump
        j-install-opticks-
    else
        echo $msg environment is not ready to install opticks
        j-install-opticks-envdump
    fi 
}



j-install-issues(){ cat << EOI

EOI
}


#####################  OFFLINE UPDATING ##################

j-offline(){ 
    : building the offline
    cd $JUNOTOP/junoenv
    bash junoenv offline
}

j-opticks(){ 
    : controlling opticks
    cd $JUNOTOP/junoenv
    bash junoenv opticks $* 
}



j-offline-alt(){ 
    : from junoenv-offline.sh:junoenv-offline-compile which is called by "bash junoenv offline"
    cd $JUNOTOP/offline/JunoRelease/cmt
    cmt br cmt config
    source setup.sh
    cmt br cmt make   
}

j-make(){
   cmt br cmt config
   source setup.sh
   #cmt br cmt make 
   cmt make 
}

j-cmtdirs-(){
   : list cmt directories in dependency order without the usual cmt guff
   cd $JUNOTOP/offline/JunoRelease/cmt
   cmt br pwd | grep -v ^#
}
j-cmtdirs(){ 
   : list cmt directories in dependency order with package not found warnings elided 
   j-cmtdirs- 2>/dev/null 
}


################# jok : juno-opticks functions ##################

jok-cmtdirs(){
   : cmtdirs relative to JUNOTOP/offline in JunoRelease dependency order with files that contain WITH_G4OPTICKS

   local cache="$HOME/.jokdirs"
   if [ -f "$cache" ]; then 
       cat $cache
       return 0
   fi 
   local dirs=$(j-cmtdirs)
   local dir
   local sel=() 
   for dir in $dirs ; do 
       local ncc=$(find $dir/.. -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+ | wc -l)
       if [ $ncc -gt 0 ]; then 
           local rel=${dir/$JUNOTOP\/offline\/}
           sel+=($rel)
       fi
   done 

   local s 
   for s in ${sel[@]}; do echo $s ; done

   if [ ! -f "$cache" ]; then 
      for s in ${sel[@]}; do echo $s >> $cache ; done
   fi
}

jok-cmtdirs-manual(){ cat << EOP
Simulation/DetSimV2/DetSimPolicy/cmt
Simulation/DetSimV2/PhysiSim/cmt
Simulation/DetSimV2/DetSimAlg/cmt
Simulation/DetSimV2/DetSimOptions/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/G4OpticksBridge/cmt
EOP
}

jok-cmtdirs-notes(){ cat << EON

To update the list of dirs, use *jok-cmtdirs* after deleting the cache file::

    O[blyth@localhost opticks]$ rm $HOME/.jokdirs
    O[blyth@localhost opticks]$ jok-cmtdirs
    Simulation/DetSimV2/PhysiSim/cmt
    Simulation/GenTools/cmt
    Simulation/DetSimV2/PMTSim/cmt
    Simulation/DetSimV2/AnalysisCode/cmt
    Simulation/DetSimV2/DetSimOptions/cmt

Changes need to be manually included into $JUNOTOP/junoenv/junoenv-opticks.sh junoenv-opticks-touchbuild-cmtdirs::
Update the build with::

    O[blyth@localhost junoenv]$ bash junoenv opticks touchbuild
    
EON
}


jok-cmtdirs-eg(){ cat << EOX
Simulation/DetSimV2/PhysiSim/cmt
Simulation/GenTools/cmt
Simulation/DetSimV2/PMTSim/cmt
Simulation/DetSimV2/AnalysisCode/cmt
Simulation/DetSimV2/DetSimOptions/cmt
EOX
}

jok-cc(){
    : list offline .cc WITH_G4OPTICKS
    cd $JUNOTOP/offline
    find . -name '*.cc' -exec grep -l WITH_G4OPTICKS {} \+  
}




jok-all(){ jok-touchbuild- $(jok-cmtdirs) ; }
jok-phy(){ jok-touchbuild- Simulation/DetSimV2/PhysiSim/cmt ; }
jok-pmt(){ jok-touchbuild- Simulation/DetSimV2/PMTSim/cmt ; }
jok-dso(){ jok-touchbuild- Simulation/DetSimV2/DetSimOptions/cmt ; }
jok-g4o(){ jok-touchbuild- Simulation/DetSimV2/G4Opticks/cmt ; }


jok-touchbuild-(){
   : in all projects touch sources WITH_G4OPTICKS and rebuild using cmt Makefile

   local msg="=== $FUNCNAME :"
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS
   [ -z "$J_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE $FUNCNAME && return 2 

   local dir
   local rel
   echo $msg $*
   for rel in $* ; do 
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
   done

   for rel in $* ; do 

       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && continue
       cd $dir
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 

       : cmt dependency check doesnt notice CMTEXTRATAGS so must touch to force recompile
       : somehow clean is not working to force recompile

       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
   echo $msg CMTEXTRATAGS : $CMTEXTRATAGS

}
jok-make(){
   local rel 
   while read rel ; do  
       local dir=$JUNOTOP/offline/$rel
       [ ! -d "$dir" ] && echo $msg ERROR no such dir $dir && return 1
       cd $dir
       pwd
       printf "\n\n\n ================== $(pwd) ==============\n\n\n" 


       cmt config
       source setup.sh

       touch $(grep -l WITH_G4OPTICKS ../src/*.cc) 

       #make clean
       make  
       [ $? -ne 0 ] && echo $msg make ERROR && break        
   done
}

jok-dso(){ echo Simulation/DetSimV2/DetSimOptions/cmt | jok-make ; }



################### ENVIRONMENT ###################################

j-g4(){  echo $JUNOTOP/ExternalLibs/Build/geant4.10.04.p02 ; } 
j-okb(){ echo $JUNOTOP/offline/Simulation/DetSimV2/G4OpticksBridge ; }  # not currently used


j-runtime-env-notes(){  cat << EON

Below warning from SniperRelease line, probably not needed ?
Should come in frm JunoRelease as dependency ?

#CMT---> Warning: The tag opticks is not used in any tag expression. Please check spelling

EON
}

j-runtime-env-()
{
   : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont
   local msg="=== $FUNCNAME: "
   echo $msg
   source $JUNOTOP/bashrc.sh   # sources the bashrc of the JUNOTOP/ExternalLibs

   local sniper_cmt_setup=$JUNOTOP/sniper/SniperRelease/cmt/setup.sh
   if [ -f $sniper_cmt_setup ]; then
       CMTEXTRATAGS= source $sniper_cmt_setup
       source $JUNOTOP/offline/JunoRelease/cmt/setup.sh
   else 
       #source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh    # curious setting CMAKE_PREFIX_PATH to lib dir
       source $JUNOTOP/sniper/InstallArea/bashrc
       source $JUNOTOP/mt.sniper/InstallArea/bashrc
       source $JUNOTOP/offline/InstallArea/setup.sh 
   fi 

   echo $msg
}

j-runtime-env()
{
   : setup the runtime environment CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, LD_LIBRARY_PATH, PATH, MANPATH
   local msg="=== $FUNCNAME: "
   local var=J_RUNTIME_ENV
   if [ -n "${!var}" ]; then
       echo $msg skip as $var:${!var} use jre- or j-runtime-env- to force it 
   else 
       export $var=1 
       j-runtime-env-
   fi

}
jre(){  
   j-runtime-env 
   jo 
   if [ -n "$OPTICKS_PREFIX" ]; then
       : TODO add these settings to standard environment  

       opticks- 

       export PYTHONPATH=$PYTHONPATH:$JUNOTOP

   fi   
}
jre-(){ j-runtime-env- ; }



j-runtime-env-notes(){ cat << EON

$JUNOTOP/bashrc.sh
    invokes bashrc of all the externals including ~/junotop/ExternalLibs/Opticks/0.1.0/bashrc
    that contains only::

        source ${OPTICKS_TOP}/bin/opticks-setup.sh    

     TODO: avoid errors when have no OPTICKS_TOP

EON
}


################### RUNNING ###################################

okt(){
   type $FUNCNAME
   [ -z "$OPTICKS_KEY" ] && echo $msg MISSING MANDATORY OPTICKS_KEY envvar && return 1 
   [ "$(which OKTest 2>/dev/null)" == "" ] && echo $msg missing opticks env use : oe- && return 2 
   #elog

   local args="OKTest --xanalytic --save --dbggsload --dumphit --dbggsdir /tmp/blyth/opticks/dbggs --printenabled --pindex ${P:-1000} "

   local iwd=$PWD
   local dir=/tmp/okt
   mkdir -p $dir
   cd $dir

   gdb__ $args 
}

gdb__(){
   : j/j.bash prepares and invokes gdb - sets up breakpoints based on BP envvar containing space delimited symbols 
   if [ -z "$BP" ]; then
      H="" 
      B="" 
      T="-ex r" 
   else
      H="-ex \"set breakpoint pending on\""
      B="" 
      for bp in $BP ; do B="$B -ex \"break $bp\" " ; done
      T="-ex \"info break\" -ex r" 
   fi

   local runline="gdb $H $B $T --args $* "
   echo $runline
   date
   eval $runline 
   date
}



############################################# tds : tut_detsim.py runner #############################

tds-label(){
   local label="tds" 
   local arg 
   for arg in $* ; do
       case $arg in  
           --no-guide_tube)           label="${label}_ngt" ;;
           --pmt20inch-polycone-neck) label="${label}_pcnk" ;;
           --pmt20inch-simplify-csg)  label="${label}_sycg" ;;
       esac 
   done
   echo $label 
}


tds-elog-verbose(){
   : hmm opticks logging control - should be elsewhere ? no opticks is part of JUNO Offline - so it should be here
   export X4Solid=INFO
   export X4PhysicalVolume=INFO
   export GGeo=INFO
   export GMaterialLib=INFO
   export GPropertyLib=INFO
   export GGeoSensor=INFO
   export CGenstepCollector=INFO 
   export G4Opticks=INFO 
   export OKMgr=INFO
   export OKPropagator=INFO
   export OpMgr=INFO 
   export OpEngine=INFO 
   export OpticksRun=INFO 
   export OpticksGen=INFO
   export OEvent=INFO 
   export OPropagator=INFO 
   export OGeo=INFO
   export GMesh=INFO 
   export OContext=INFO
}

tds-elog-quiet(){
   export G4Opticks=INFO 
}

tds-ectrl-notes(){ cat << EON

Control via envvar is appropriate only for temporary debugging. 
Changes should be solidified into code ASAP, for example into 

   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc

EON
}

tds-ectrl(){
   local msg="=== $FUNCNAME :"
   #export OPTICKS_RESOURCE_LAYOUT=2

   #export OPTICKS_EMBEDDED_COMMANDLINE="pro"   # default  
   #export OPTICKS_EMBEDDED_COMMANDLINE="dev"  
   #export OPTICKS_EMBEDDED_COMMANDLINE=" --compute --embedded --xanalytic --save --natural --printenabled --pindex 0"

   local extra
   #extra="--dbggssave --dumphit --layout 100 --savesensor"
   #extra="--dbggdmlpath $dbggdmlpath" 
   #extra="--rngmax 100"
   extra="--rngmax 100 --skipsolidname NNVTMCPPMTsMask_virtual,HamamatsuR12860sMask_virtual,mask_PMT_20inch_vetosMask_virtual -e ~8, --rtx 1 --cvd 1"

   unset OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
   if [ -n "$extra" ]; then 
       export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="$extra"  
       echo $msg OPTICKS_EMBEDDED_COMMANDLINE_EXTRA ${OPTICKS_EMBEDDED_COMMANDLINE_EXTRA}
   fi    

   local lsxdc_geospecific
   #local lsxdc_geospecific="--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3  --gdmlkludge" 
    
   unset LSXDC_GEOSPECIFIC
   if [ -n "${lsxdc_geospecific}" ]; then  
       export LSXDC_GEOSPECIFIC=${lsxdc_geospecific} 
       echo $msg LSXDC_GEOSPECIFIC ${LSXDC_GEOSPECIFIC} 
   fi

   unset PMTEfficiencyCheck_dump
   unset PMTEfficiencyCheck_assert_match
   #export PMTEfficiencyCheck_dump=1 
   #export PMTEfficiencyCheck_assert_match=1 

}


tds-grab(){  
    local outbase=/tmp/$USER/opticks/tds
    mkdir -p $outbase
    local cmd="rsync -rtz --progress P:$outbase/ $outbase/"
    echo $cmd
    eval $cmd
    open $outbase
}



tds0(){
   : run with opticks disabled
   #local former_opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 " ;   
   local opts="--opticks-mode 0 --no-guide_tube --evtmax 2 " ;   
   tds- $opts gun $*
}

tds2(){
   : run with opticks disabled, but with Opticks provided intrumentation used to save info from Geant4 in OpticksEvent format files
   #local former_opts="--opticks-mode 2 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 --opticks-anamgr" ;   
   local opts="--opticks-mode 2 --no-guide_tube --evtmax 2 --opticks-anamgr" ;   
   tds- $opts gun $*
}

anamgr(){ cat << EOU
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
}


yuxiang()
{
   local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py 
   gdb --args \
       python $script \
       --opticks-mode 1 \
       --no-guide_tube \
       --pmt20inch-polycone-neck \
       --pmt20inch-simplify-csg \
       --evtmax 2 \
       --opticks-anamgr \
       --no-anamgr-normal \
       --no-anamgr-genevt \
       --no-anamgr-edm-v2 \
       --no-anamgr-grdm \
       --no-anamgr-deposit \
       --no-anamgr-deposit-tt \
       --no-anamgr-interesting-process \
       --no-anamgr-optical-parameter \
       --no-anamgr-timer \
       gun  
}



tds3mu(){
   : unsets ctrl evars that may be defined from other funcs
   export OPTICKS_EVENT_PFX=tds3mu
   unset INPUT_PHOTON_PATH

   local outdir="/tmp/G4OpticksAnaMgr" 
   mkdir -p $outdir
   export G4OpticksAnaMgr_outdir=$outdir

   tds3 --particles mu- --momentums 215000 
}


tds3gun(){
   : unsets ctrl evars that may be defined from other funcs
   export OPTICKS_EVENT_PFX=tds3gun
   unset INPUT_PHOTON_PATH

   local outdir="/tmp/G4OpticksAnaMgr" 
   mkdir -p $outdir
   export G4OpticksAnaMgr_outdir=$outdir

   tds3
}

tds3ip(){
   #local name="RandomSpherical10" 
   #local name="CubeCorners" 
   #local name="CubeCorners10x10" 
   #local name="CubeCorners100x100" 
   local name="InwardsCubeCorners17699"

   local path="$HOME/.opticks/InputPhotons/${name}.npy"
   #local path=/tmp/check_innerwater_bulk_absorb.npy 

   export OPTICKS_EVENT_PFX=tds3ip
   export INPUT_PHOTON_PATH=$path
   export INPUT_PHOTON_REPEAT=10000  
   : 100k repeat falls foul of Geant4 big primary slowdown  
   #export INPUT_PHOTON_WAVELENGTH=360,380,400,420,440,460,480
   export INPUT_PHOTON_WAVELENGTH=440
   export EVTMAX=7

   tds3 
}

tds3dbg()
{
   unset X4PhysicalVolume
   export X4PhysicalVolume=INFO
   export OGeo=INFO   # see if GParts::close is getting called in OGeo::makeAnalyticGeometry
   tds3
}



tds-old-skipsolidname(){ echo $(tds-old-skipsolidname-) | tr " " "," ; }
tds-old-skipsolidname-(){ cat << EON | grep -v ^#
#NNVTMCPPMTsMask_virtual
#HamamatsuR12860sMask_virtual
mask_PMT_20inch_vetosMask_virtual
NNVTMCPPMT_body_solid
HamamatsuR12860_body_solid_1_9
PMT_20inch_veto_body_solid_1_2
EON
}

tds-nohatbox-skipsolidname(){ echo $(tds-nohatbox-skipsolidname-) | tr " " "," ; }
tds-nohatbox-skipsolidname-(){ cat << EON | grep -v ^#

NNVTMCPPMTsMask_virtual
HamamatsuR12860sMask_virtual
mask_PMT_20inch_vetosMask_virtual

NNVTMCPPMT_PMT_20inch_body_solid_1_2
HamamatsuR12860_PMT_20inch_body_solid_1_4
PMT_20inch_veto_body_solid_1_2

EON
}

tds-skipsolidname(){ echo $(tds-skipsolidname-) | tr " " "," ; }
tds-skipsolidname-(){ cat << EON | grep -v ^#

NNVTMCPPMT_PMT_20inch_body_solid_1_2
HamamatsuR12860_PMT_20inch_body_solid_1_4
PMT_20inch_veto_body_solid_1_2

EON
}







tds3(){
   : both opticks and geant4 optical simulations with --opticks-anamgr to provide OpticksEvent G4OpticksRecorder instrumentation to the Geant4 simulation  
   : tds3 args now passed along to tut_detsim.py not the embedded opticks as previously 

   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-2}

   local opts="" 
   opts="$opts --opticks-mode 3"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"

   #opts="$opts --pmt20inch-polycone-neck"  ## FORMER OPTION NOW DEFAULT
   #opts="$opts --pmt20inch-simplify-csg"   ## FORMER OPTION NOW DEFAULT

   opts="$opts --disable-pmt-optical-model"

   opts="$opts --evtmax $evtmax"
   opts="$opts $(anamgr) "

   if [ -n "$DEBUG_DISABLE_STICKS" ]; then
       opts="$opts --debug-disable-sticks"
   fi 


   tds_ls
   tds_ctrl_ls 

   #export OPTICKS_EMBEDDED_COMMANDLINE="pro"   # default with --nosave   
   export OPTICKS_EMBEDDED_COMMANDLINE="dev"    # with --save 

   local extra
   #extra="--rngmax 100"
   extra="--skipsolidname $(tds-skipsolidname)"
   #extra="$extra -e ~8,"  
   extra="$extra --rtx 1"

   case $USER in 
      blyth) extra="$extra --cvd 1" ;;
   esac 

   local dindex=${DINDEX}
   local dbgseqhis=${DBGSEQHIS}
   local dbgseqmat=${DBGSEQMAT}

   if [ -n "$dindex" ]; then
      extra="$extra --dindex $dindex "
   fi 
   
   if [ -n "$dbgseqhis" ]; then
      extra="$extra --dbgseqhis $dbgseqhis "
   fi 

   if [ -n "$dbgseqmat" ]; then
      extra="$extra --dbgseqmat $dbgseqmat "
   fi


   unset OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
   if [ -n "$extra" ]; then 
       export OPTICKS_EMBEDDED_COMMANDLINE_EXTRA="$extra"  
       echo $msg OPTICKS_EMBEDDED_COMMANDLINE_EXTRA : ${OPTICKS_EMBEDDED_COMMANDLINE_EXTRA}
   else
       echo $msg OPTICKS_EMBEDDED_COMMANDLINE_EXTRA : not defined  
   fi    

   local input_photon_path=${INPUT_PHOTON_PATH} 
   local input_photon_repeat=${INPUT_PHOTON_REPEAT} 
   local input_photon_wavelength=${INPUT_PHOTON_WAVELENGTH} 

   local trgs=""
   if [ -n "${input_photon_path}" -a -f "${input_photon_path}" ]; then 
       trgs="$trgs opticks --input-photon-path ${input_photon_path}"
       if [ -n "${input_photon_repeat}" ]; then
           trgs="$trgs --input-photon-repeat ${input_photon_repeat}"
       fi 
       if [ -n "${input_photon_wavelength}" ]; then
           trgs="$trgs --input-photon-wavelength ${input_photon_wavelength}"
       fi 
   else
       trgs="$trgs gun"
   fi 

   echo $msg opts : $opts 
   echo $msg trgs : $trgs 
   echo $msg args : atrgs 

   tds- $opts $trgs $args
}


logging(){
   #export GGeo=INFO
   export G4CXOpticks=INFO
   #export GNodeLib=INFO
   #export SEvt=INFO
   export junoSD_PMT_v2_Opticks=INFO
}


ntds0(){ OPTICKS_MODE=0 ntds3 ; }  #0b00   Ordinary running without Opticks involved at all  
ntds1(){ OPTICKS_MODE=1 ntds3 ; }  #0b01   Running with only Opticks doing the optical propagation 
#ntds2(){ OPTICKS_MODE=2 ntds3 ; }  #0b10   Geant4 only with Opticks instrumentation (that was original idea) 
                                    #       but U4RecorderTest running superceeds that :  perhaps assert that this mode is not used 
ntds3()                            #0b11   Running with both Geant4 and Opticks optical propagation
{
   env | grep =INFO

   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-2}
   local mode=${OPTICKS_MODE:-3}

   export SCRIPT=${SCRIPT:-$FUNCNAME} 

   local opts="" 
   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --disable-pmt-optical-model"
   opts="$opts --evtmax $evtmax"
   opts="$opts $(anamgr) "

   if [ -n "$DEBUG_DISABLE_STICKS" ]; then
       opts="$opts --debug-disable-sticks"
   fi 

   local trgs=""
   trgs="$trgs gun"

   echo $msg opts : $opts 
   echo $msg trgs : $trgs 
   echo $msg args : atrgs 

   #BASE=/tmp/$USER/opticks/$SCRIPT   
   BASE=.opticks/$SCRIPT   

   case $(uname) in 
      Linux) tds- $opts $trgs $args  ;;
      Darwin) source $OPTICKS_HOME/bin/rsync.sh $BASE ;;
   esac

   env | grep =INFO
}



tds_ctrl(){ cat << EOV
INPUT_PHOTON_PATH
OPTICKS_EVENT_PFX
OPTICKS_EMBEDDED_COMMANDLINE
OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
EVTMAX
EOV
}
tds_ctrl_ls(){    VNAME=tds_ctrl tds_ls ; }
tds_ctrl_unset(){ VNAME=tds_ctrl tds_unset ; }




# logging evar control 
tds_log_(){ cat << EOV
G4Opticks
G4OpticksRecorder
CManager
#CRecorder
CGenstepCollector
CWriter
#CTrackInfo
#CCtx
OpticksRun
OpticksEvent
#CG4
EOV
}

tds_on(){  tds_log_ |  grep  -v ^\#  ; }
tds_off(){ tds_log_ |  grep  ^\#  | tr "\#" " " ;  }
tds_all(){ tds_on ; tds_off ; } 

tds_ls(){     for var in $(${VNAME:-tds_all}) ; do printf "%20s : [%s] \n"  $var ${!var} ; done ; } 
tds_export(){ for var in $(${VNAME:-tds_on})  ; do export $var=INFO                      ; done ; }   
tds_unset(){  for var in $(${VNAME:-tds_off}) ; do unset $var                            ; done ; } 
tds_log(){  
    : exports/unsets logging evars according to tds_log_ commenting  
    tds_export 
    tds_unset 
    tds_ls 
}   



tds-mu(){ tds --particles mu- --momentums 215000 ; }
tds(){ 
   #local opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --evtmax 2"  
   #local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --evtmax 2"  
   #local opts="--opticks-mode 1 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 10"  
   #local opts="--opticks-mode 1 --no-guide_tube --evtmax 2"  

   local opts="--opticks-mode 1 --no-guide_tube --evtmax 10"  

   tds-elog-quiet
   tds-ectrl 

   tds- $opts gun $*
}

tds-(){ 
   type $FUNCNAME
   local msg="=== $FUNCNAME :"

   if [ "${CMTEXTRATAGS/opticks}" != "${CMTEXTRATAGS}" ]; then 
       echo $msg CMTEXTRATAGS $CMTEXTRATAGS contains opticks
       #[ -z "$OPTICKS_TOP" ] && echo $msg OPTICKS_TOP is not defined && return 1
   fi

   [ -z "$J_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 
 
   local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py
   if [ -z "$BP" ]; then
      H="" 
      B="" 
      T="-ex r" 
   else
      H="-ex \"set breakpoint pending on\""
      B="" 
      for bp in $BP ; do B="$B -ex \"break $bp\" " ; done
      T="-ex \"info break\" -ex r" 
   fi

   local iwd=$PWD
   local dir=$(tds-dir)
   mkdir -p $dir
   cd $dir

   local runline
   if [ -n "$PDB" ]; then 
       runline="ipython --pdb $script $*"
   else
       runline="gdb $H $B $T --args python $script $*"
   fi 

   echo $runline
   date
   eval $runline 
   date
   cd $iwd

   tds-csg-ggeo-reminder

}

tds-gdb-(){
   local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py
   local runline="gdb --args python $script $*"
   echo $runline
   eval $runline
}



tds-csg-ggeo-reminder(){  cat << EOR
    
tds-csg-ggeo-reminder
=======================

Recall that creation of CSG/CSGFoundry geometries for CSGOptiX usage with NVIDIA OptiX 7 is **NOT YET AUTOMATED**.

Following tds running that changes geometry you must remember to:

1. update the OPTICKS_KEY envvar in .bash_profile etc.. if the 
   geometry change caused the key envvar digest to differ

2. run the conversion from geocache into CSG_GGeo which is 
   now housed within the geocache directory identified by OPTICKS_KEY::

      cd ~/opticks/CSG_GGeo   # cg 
      ./run.sh                # should takes less than 5 seconds even for large geometries

   * NB even when the OPTICKS_KEY is unchanged it is still necessary to 
     update the CSG geometry in order to propagate geometry changes into CSG 

   * after doing this renders created with the various CSGOptiX render scripts
     should reflect the updated geometry 


TODO: 
    automate cg running at bash level, as interim fix prior to being able to do it 
    properly at C++ level (which must wait until have made the leap to 7) 
    by autodetecting that the b7 opticks-build7 has been used and simply running 
    scripts at the tail of tds-  


EOR
}


tds-dir(){ echo /tmp/$USER/opticks/tds ; }
tds-cd(){ cd $(tds-dir) ; }


############################## tds runners with various breakpoints #########################

tdsA(){ BP=R12860PMTManager::R12860PMTManager     tds ; } 

tdsB-(){ cat << EOB
G4Torus::G4Torus
DetSim0Svc::createDetectorConstruction
R12860PMTManager::R12860PMTManager
EOB
}
tdsB(){ BP="$(tds2-)" tds ; }

tdsC-(){
   : breakpoint signatures of PMTSolid ctors
   local iwd=$PWD
   cd $JUNOTOP/offline/Simulation/DetSimV2/PMTSim/src
   ls -1 *_PMTSolid.cc | perl -p -e 's,(\S*).cc,$1::$1,' - 
   cd $iwd
}
tdsC(){ BP="$(tdsC-)" tds ; }

tdsD-(){ cat << EOB
DsG4Scintillation::PostStepDoIt
G4VUserPhysicsList::Construct
LSExpPhysicsList::ConstructProcess
G4OpticksAnaMgr::BeginOfRunAction
EOB
}

tdsD(){ BP="$(tdsD-)" tds ; }

tdsE-(){ cat << EOB
junoSD_PMT_v2::junoSD_PMT_v2
junoSD_PMT_v2::Initialize
junoSD_PMT_v2::ProcessHits
junoSD_PMT_v2::get_pmtid
junoSD_PMT_v2::EndOfEvent
EOB
}
tdsE(){ BP="$(tdsE-)" tds ; }


###########################################################################################

[ "$DBG" == "1" ] && dbg_tail $BASH_SOURCE
