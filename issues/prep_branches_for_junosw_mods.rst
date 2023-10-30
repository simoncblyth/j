prep_branches_for_junosw_mods 
======================================

TODO : update junoenv Custom4 version
-------------------------------------------



Git mechanics of getting working copy changes into multiple branches
----------------------------------------------------------------------

* https://stackoverflow.com/questions/1394797/move-existing-uncommitted-work-to-a-new-branch-in-git


1. decide on splits (which changes in which branch) and branch names
2. create the first branch

* forced to do jsw+ok integration changes first, as those needed to compile with latest opticks


Remainder of mods from laptop to get into main repo
------------------------------------------------------

::

    epsilon:local blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping
    Your branch is up-to-date with 'origin/blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)


        modified:   Simulation/DetSimV2/CentralDetector/include/FastenerAcrylicConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface

        modified:   Simulation/DetSimV2/CentralDetector/include/SJCLSanchorConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/SJCLSanchorConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface, some added G4VSolid members

        modified:   Simulation/DetSimV2/CentralDetector/include/SJFixtureConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc
        * NOT SO STRAIGHTFORWARD DUE TO BUGS IN ORIGINAL 

        modified:   Simulation/DetSimV2/CentralDetector/include/SJReceiverConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/SJReceiverConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface, some added G4VSolid members

        modified:   Simulation/DetSimV2/CentralDetector/include/SJReceiverFasternConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface, some added G4VSolid members

        modified:   Simulation/DetSimV2/CentralDetector/include/XJanchorConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/XJanchorConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface, some added G4VSolid members
       
        modified:   Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc
        * straightforward addition of PMTSIM_STANDALONE interface



    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        scp.sh



Git Mechanics
---------------

Do the below on both laptop and workstation::

    get fetch origin  # pick up the web interface added branch off main 
    branch=blyth-add-standalone-debug-interface-to-seven-fixture-solids
    git checkout -b $branch origin/$branch

On laptop apply the stash into the branch::

    epsilon:junosw blyth$ git stash apply 
    Auto-merging Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc
    CONFLICT (content): Merge conflict in Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ git status
    On branch blyth-add-standalone-debug-interface-to-seven-fixture-solids
    Your branch is up-to-date with 'origin/blyth-add-standalone-debug-interface-to-seven-fixture-solids'.

    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

        modified:   Simulation/DetSimV2/CentralDetector/include/FastenerAcrylicConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/SJCLSanchorConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/SJFixtureConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/SJReceiverConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/SJReceiverFasternConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/XJanchorConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
        modified:   Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc
        modified:   Simulation/DetSimV2/CentralDetector/src/SJCLSanchorConstruction.cc
        modified:   Simulation/DetSimV2/CentralDetector/src/SJReceiverConstruction.cc
        modified:   Simulation/DetSimV2/CentralDetector/src/SJReceiverFasternConstruction.cc
        modified:   Simulation/DetSimV2/CentralDetector/src/XJanchorConstruction.cc
        modified:   Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc

    Unmerged paths:
      (use "git reset HEAD <file>..." to unstage)
      (use "git add <file>..." to mark resolution)

        both modified:   Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc

    epsilon:junosw blyth$ 
             




Noddy Approach : AS TOO MANY OLD CHANGES TO INCORPORATE
----------------------------------------------------------

::

    N[blyth@localhost junotop]$ mv junosw junosw_dirty
    N[blyth@localhost junotop]$ 
    N[blyth@localhost junotop]$ 
    N[blyth@localhost junotop]$ cd junosw_dirty/
    N[blyth@localhost junosw_dirty]$ git remote -v
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw (fetch)
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw (push)
    N[blyth@localhost junosw_dirty]$ 



Add branch in web interface
------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/branches

::

    branch=blyth-




MERGED : Update JUNOSW Opticks integration to work with current Opticks API
------------------------------------------------------------------------------

::

    N[blyth@localhost junosw]$ branch=blyth-Opticks-integration-updates-for-current-API
    N[blyth@localhost junosw]$ git checkout -b $branch origin/$branch 
    M	Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    M	Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    M	Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    M	Simulation/GenTools/src/GtOpticksTool.cc
    Branch blyth-Opticks-integration-updates-for-current-API set up to track remote branch blyth-Opticks-integration-updates-for-current-API from origin.
    Switched to a new branch 'blyth-Opticks-integration-updates-for-current-API'
    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git commit -m "update junosw+opticks integration for latest Opticks API, especially generalized opticks/SEvt"
    [blyth-Opticks-integration-updates-for-current-API f8f1715] update junosw+opticks integration for latest Opticks API, especially generalized opticks/SEvt
     4 files changed, 65 insertions(+), 48 deletions(-)

    N[blyth@localhost junosw]$ git push 
    Counting objects: 29, done.
    Delta compression using up to 48 threads.
    Compressing objects: 100% (15/15), done.
    Writing objects: 100% (15/15), 2.27 KiB | 0 bytes/s, done.
    Total 15 (delta 13), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-Opticks-integration-updates-for-current-API, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-Opticks-integration-updates-for-current-API
    remote: 
    To git@code.ihep.ac.cn:JUNO/offline/junosw
       27d86b9..f8f1715  blyth-Opticks-integration-updates-for-current-API -> blyth-Opticks-integration-updates-for-current-API
    N[blyth@localhost junosw]$ 

Ticket 122
------------

Comparison of DetSim optical simulation with Opticks reveals some more
near-degenerate LPMT and SPMT geometry

Comparing DetSim optical simulation with Opticks using input photons targeting
LPMT and SPMT reveal some differences in optical histories due to
near-degenerate surfaces mostly from 1e-3 mm offsets that are too small for
reliable float precision distinction. The proposed fix to be implemented in a
branch associated with this ticket is to add envvar controls to change the
relevant geometry offsets and assuming no knock-on issues are encountered to
adjust defaults to avoid the degenerate geometry and bring the DetSim and
Opticks simulations into agreement.  The geometry changes envisaged are very
small and should have no meaningful impact on simulation results.

blyth-122-add-envvar-offset-controls-for-PMT-geometry-to-avoid-degeneracy


Review Changes : Decide how to split
-----------------------------------------------------

* separated things into three 

0. Update JUNOSW Opticks integration to work with current Opticks API
1. PMT Serialization Machinery Simplifications, Testing
2. Geometry envvar controls and changes to defaults that avoid degenerate PMT surfaces

* BEST TO DO LEAST IMPACTFUL FIRST 
* HMM : MAY NEED TO COORDINATE WITH CUSTOM4 UPDATE ? 
* NB OTHER COVID ISOLATION STANDALONE CHANGES ON LAPTOP :doc:`prep_branches_second_wave`

Progress
---------

* done one merge : to allow junosw to work with current Opticks
* DONE : another MR is pending : regarding PMT serialization updates, making it fully standalone and adding tests
* also need to update junoenv custom4 version 
* and beyond that I have at least two further merge requests in my pipeline

  1. envvar controls of SPMT and LPMT geometry offsets + change defaults 
     (mostly changing offsets from 1e-3 mm to 0.1 mm) : that avoids near-degeneracy 
     in the geometry and allows DetSim and Opticks to agree (at least in current input photon tests)

  2. while I was in covid isolation, I did not have internet access : so I worked locally 
     on my laptop on the difficult geometry making those solids standalone testable.
     This change has no impact on the simulation : it just allows these 4 or 5 solids 
     to be easily tested standalone.  



DONE : Review Custom4 : Oct 7 2023 : added tag 
-------------------------------------------------------------------------------

* Last tag from https://github.com/simoncblyth/customgeant4/tags is 0.1.6
* On N are using untagged next version "0.1.7" via working copy junoenv change (changed from 0.1.4)

je:packages/custom4.sh::

    .function juno-ext-libs-custom4-version-default {
    -    echo 0.1.4
    +    #echo 0.1.5
    +    #echo 0.1.6
    +    echo 0.1.7    # untagged next version from Custom4/build_into_junosw.sh 
     }


Need to tidy this up.  

* Does the Custom4 version impact the rest of the commits are aiming to make. 
* HMM: am leaping from 0.1.4 to 0.1.7 (or 0.1.8) so need to check whats changed

  * from RELEASE_NOTES.rst looks like mainly bug fix with no API change 

::

    N[blyth@localhost customgeant4]$ l /data/blyth/junotop/ExternalLibs/custom4/
    total 4
    0 drwxrwxr-x.  4 blyth blyth   62 Aug  7 00:44 0.1.7
    0 drwxrwxr-x.  4 blyth blyth   62 Aug  7 00:38 0.1.6
    0 drwxrwxr-x.  7 blyth blyth   71 Aug  7 00:16 .
    0 drwxrwxr-x.  4 blyth blyth   62 Jul  2 22:51 0.1.5
    0 drwxrwxr-x.  4 blyth blyth   62 Apr 11 02:54 0.1.4
    0 drwxrwxr-x.  4 blyth blyth   62 Apr  8 03:10 0.1.3
    4 drwxrwxr-x. 39 blyth blyth 4096 Mar 24  2023 ..
    N[blyth@localhost customgeant4]$ 




MERGED : PMT Serialization Machinery Simplifications, Testing
-----------------------------------------------------------------

After the merge tidied up the corresponding files from junosw_dirty using::

   git checkout file 
   rm file

So junosw_dirty should now be close to what need in the next branch. 

::

   branch=blyth-PMT-serialization-fully-standalone-and-add-tests

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/242


Copied into branch from junosw_dirty::

    #!/bin/bash -l 

    paths(){ cat << EOP
    Detector/Geometry/Geometry/PMTCategory.h
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh
    EOP
    }

    for path in $(paths) ; do  
       echo cp $path ../junosw/$path 
    done


::

    #modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    * include and use the Pyrex and Vacuum RINDEX serialized together with PMT data 
      in order to allow strict standalone PMT data access without 
      relying on Geant4 global material environment 

    #modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    * add loaddir metadata for debug 

    # modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    # * simplify JUNO+Opticks PMT serialization etc.. by using added Opticks features

    #modified:   Detector/Geometry/Geometry/PMTCategory.h
    * added PMTCategory::NameMap (HARMLESS)

    #modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
    * persisted file layout generalization, added debug  
    * use PMTCategory::NameMap to create pmtCatName

    #modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
    #modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh
    * testing standalone access to PMT data 

Adds::

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh
    * Standalone stack calc test using approach from Custom4/C4CustomART.h 

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh
    * load serialized PMT data into ipython for NumPy examination  



Runtime issue without the python changes
------------------------------------------

::

    tut_detsim.py: error: unrecognized arguments: --debug-disable-fa



Geometry envvar controls and changes to defaults that avoid degenerate PMT surfaces
-------------------------------------------------------------------------------------

::

    modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    * added control and action for "--debug-disable-fa"



    modified:   Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc

    modified:   Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    modified:   Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    * add ectrl MAGIC_virtual_thickness 
    * changed default from 0.05 to 0.10 (mm) 
    * HMM: DO I NEED AGREEMENT FOR INCREASED DEFAULT ? 

    modified:   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    * add descDetail, standalone access 

    modified:   Simulation/DetSimV2/PMTSim/include/Tub3inchPMTV3Manager.hh
    modified:   Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc
    * add PMTSIM_STANDALONE access and API 
    * add ectrl Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM
    * increased VIRTUAL_DELTA_MM default from 1e-3 to 0.1 



MERGED : Review changes as load into the branch blyth-122 : CONSERVATIVE NO CHANGE
------------------------------------------------------------------------------------


::

    N[blyth@localhost junosw_dirty]$ git status
    On branch blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping
    Your branch is up to date with 'origin/blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)

        modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
        * add --debug-disable-fa to disable FastenerAcrylic
        * impl skipping FastenerAcrylic

        modified:   Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
        * HamamatsuMaskManager__MAGIC_virtual_thickness_MM
        * INCREASE DEFAULT MAGIC 0.05->0.10 mm

        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
        * NNVTMaskManager__MAGIC_virtual_thickness_MM
        * INCREASE DEFAULT MAGIC 0.05->0.10 mm

        modified:   Simulation/DetSimV2/PMTSim/include/Tub3inchPMTV3Manager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc  
        * add PMTSIM_STANDALONE access and API 
        * add ectrl Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM
        * INCREASE DEFAULT DELTA 1e-3->0.10 mm

        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
        * add descDetail debug dump 

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw_dirty]$ 



These commits adds envvar controls that enable changing of 
the virtual wrapper offset thicknesses of the LPMT and SPMT
`
HamamatsuMaskManager__MAGIC_virtual_thickness_MM
NNVTMaskManager__MAGIC_virtual_thickness_MM
Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM
`
Also the defaults offsets are increased, 
LPMT increased from 0.05->0.10 mm and SPMT increased from 1.e-3->0.10 mm 

These changes avoid low level near degeneracy that prevent the Opticks 
simulation from matching Detsim.

Also the python option --debug-disable-fa is added to disable FastenerAcrylic


Geant4 vs Opticks simulations have been compared whilst making these changes, 
and the impact has been all positive with no known issues.  In case any problems
arise in future the code can be retained almost asis with just 
the default values of the offsets changed. 


