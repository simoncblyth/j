blyth-88-another-dry-run-merge-in-tmp-junosw-check2
========================================================



Transient clone /tmp/junosw_check2
-------------------------------------

::

    epsilon:tmp blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git junosw_check2
    epsilon:tmp blyth$ cd junosw_check2

    epsilon:junosw_check2 blyth$ branch=blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw_check2 blyth$ git checkout -b $branch origin/$branch


chomp cmake/JUNODependencies.cmake
-------------------------------------

::

    epsilon:junosw_check2 blyth$ perl -pi -e 'chomp if eof' cmake/JUNODependencies.cmake

    epsilon:junosw_check2 blyth$ git diff 
    diff --git a/cmake/JUNODependencies.cmake b/cmake/JUNODependencies.cmake
    index fe4d2ab..badbe94 100644
    --- a/cmake/JUNODependencies.cmake
    +++ b/cmake/JUNODependencies.cmake
    @@ -192,4 +192,4 @@ if(NUWRO_LIBRARIES)
     else()
         set(NuWro_Found FALSE)
     endif()
    -link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    +link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    \ No newline at end of file
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ git add . 
    epsilon:junosw_check2 blyth$ git commit -m "chomp the eol at end of cmake/JUNODependencies.cmake as seems to cause merge conflict"
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 0b8f5cb] chomp the eol at end of cmake/JUNODependencies.cmake as seems to cause merge conflict
     1 file changed, 1 insertion(+), 1 deletion(-)
    epsilon:junosw_check2 blyth$ 

    epsilon:junosw_check2 blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.


Dry run merge : only one conflict after the chomp
----------------------------------------------------

::

    epsilon:junosw_check2 blyth$ git merge --no-ff --no-commit $branch 
    Auto-merging cmake/JUNODependencies.cmake
    Auto-merging Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    Auto-merging Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    CONFLICT (content): Merge conflict in Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Automatic merge failed; fix conflicts and then commit the result.
    epsilon:junosw_check2 blyth$ 

    epsilon:junosw_check2 blyth$ git status
    On branch main
    Your branch is up-to-date with 'origin/main'.

    You have unmerged paths.
      (fix conflicts and run "git commit")
      (use "git merge --abort" to abort the merge)

    Changes to be committed:

        new file:   Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
        new file:   Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
        modified:   Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
        ...

    Unmerged paths:
      (use "git add <file>..." to mark resolution)

        both modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py


Examples/Tutorial/python/Tutorial/JUNODetSimModule.py :  Changes too close to each other ?
--------------------------------------------------------------------------------------------

::

    1357         ok = gt.createTool("GtOpticksTool/ok")
    1358         objName = ok.objName()
    1359         gt.property("GenToolNames").set([objName])
    1360         log.info("setup_generator_opticks : objName:[%s]" % (objName) )
    1361 
    1362     def setup_generator_nuwro(self, task, args):
    1363         import GenTools
    1364         gt = task.createAlg("GenTools")
    1365         import Sniper
    1366         Sniper.loadDll("libGenNuWro.so")
    1367         nuwro_gen = gt.createTool("NuWroEvGen/nuwro")
    1368         path = args.input
    1369         nuwro_gen.property("NuWroConfigFile").set(path)
    1370         gt.property("GenToolNames").set([nuwro_gen.objName()])
    1371 
    1372 
    1373 <<<<<<< HEAD
    1374     def setup_generator_nuwro(self, task, args):
    1375         import GenTools
    1376         gt = task.createAlg("GenTools")
    1377         import Sniper
    1378         Sniper.loadDll("libGenNuWro.so")
    1379         nuwro_gen = gt.createTool("NuWroEvGen/nuwro")
    1380         path = args.input
    1381         nuwro_gen.property("NuWroConfigFile").set(path)
    1382         gt.property("GenToolNames").set([nuwro_gen.objName()])
    1383 
    1384 
    1385 =======
    1386 >>>>>>> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    1387     def setup_generator_photon(self, task, args):
    1388         import GenTools
    1389         from GenTools import makeTV
    1390         gt = task.createAlg("GenTools")



Abort the dry run merge 
--------------------------

::

    epsilon:junosw_check2 blyth$ git merge --abort 
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ git status
    On branch main
    Your branch is up-to-date with 'origin/main'.

    nothing to commit, working tree clean
    epsilon:junosw_check2 blyth$ 



Review the Examples/Tutorial/python/Tutorial/JUNODetSimModule.py changes
---------------------------------------------------------------------------

main adds setup_generator_nuwro just after setup_generator_opticks::

    epsilon:junosw_check2 blyth$ git diff b4e0.. -- Examples/Tutorial/python/Tutorial/JUNODetSimModule.py

 
    @@ -1327,7 +1349,17 @@ class JUNODetSimModule(JUNOModule):
             pass
             gt.property("GenToolNames").set([objName])
     
    -    
    +    def setup_generator_nuwro(self, task, args):
    +        import GenTools
    +        gt = task.createAlg("GenTools")
    +        import Sniper
    +        Sniper.loadDll("libGenNuWro.so")
    +        nuwro_gen = gt.createTool("NuWroEvGen/nuwro")
    +        path = args.input
    +        nuwro_gen.property("NuWroConfigFile").set(path)
    +        gt.property("GenToolNames").set([nuwro_gen.objName()])
    +
    +



::

    epsilon:junosw_check2 blyth$ t branch 
    branch () 
    { 
        echo blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess;
        : .bash_profile
    }
    epsilon:junosw_check2 blyth$ git checkout $(branch)
    Already on 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is ahead of 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess' by 1 commit.
      (use "git push" to publish your local commits)
    epsilon:junosw_check2 blyth$ 




::

    epsilon:junosw_check2 blyth$ git add . 
    epsilon:junosw_check2 blyth$ git commit -m "relocate setup_generator_opticks in attempt to avoid merge conflict"
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 50fdede] relocate setup_generator_opticks in attempt to avoid merge conflict
     1 file changed, 37 insertions(+), 33 deletions(-)
    epsilon:junosw_check2 blyth$ 


Back to main and try dry run merge again
-------------------------------------------


::

    epsilon:junosw_check2 blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ git status 
    On branch main
    Your branch is up-to-date with 'origin/main'.

    nothing to commit, working tree clean
    epsilon:junosw_check2 blyth$ git merge --no-ff --no-commit $(branch) 
    Auto-merging cmake/JUNODependencies.cmake
    Auto-merging Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    Auto-merging Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    CONFLICT (content): Merge conflict in Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Automatic merge failed; fix conflicts and then commit the result.
    epsilon:junosw_check2 blyth$ 


Huh moving the setup_generator_opticks makes no difference::

    1325         # Note: by default, we choose fixed position instead of using positioner
    1326         self.helper_positioner(args, gt, None)
    1327 
    1328 
    1329     def setup_generator_nuwro(self, task, args):
    1330         import GenTools
    1331         gt = task.createAlg("GenTools")
    1332         import Sniper
    1333         Sniper.loadDll("libGenNuWro.so")
    1334         nuwro_gen = gt.createTool("NuWroEvGen/nuwro")
    1335         path = args.input
    1336         nuwro_gen.property("NuWroConfigFile").set(path)
    1337         gt.property("GenToolNames").set([nuwro_gen.objName()])
    1338 
    1339 
    1340 <<<<<<< HEAD
    1341     def setup_generator_nuwro(self, task, args):
    1342         import GenTools
    1343         gt = task.createAlg("GenTools")
    1344         import Sniper
    1345         Sniper.loadDll("libGenNuWro.so")
    1346         nuwro_gen = gt.createTool("NuWroEvGen/nuwro")
    1347         path = args.input
    1348         nuwro_gen.property("NuWroConfigFile").set(path)
    1349         gt.property("GenToolNames").set([nuwro_gen.objName()])
    1350 
    1351 
    1352 =======
    1353 >>>>>>> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    1354     def setup_generator_photon(self, task, args):
    1355         import GenTools


This makes me think there are some funny chars involved, but dont see any with ":set list" 

Abort the merge::

    epsilon:junosw_check2 blyth$ git merge --abort 
    epsilon:junosw_check2 blyth$ git s
    On branch main
    Your branch is up-to-date with 'origin/main'.

    nothing to commit, working tree clean
    epsilon:junosw_check2 blyth$ 
    epsilon:junosw_check2 blyth$ 


Back to branch and scrub that last commit 
-----------------------------------------------

::

    epsilon:junosw_check2 blyth$ git checkout $(branch)
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    Your branch is ahead of 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess' by 2 commits.
      (use "git push" to publish your local commits)
    epsilon:junosw_check2 blyth$ 


Scrub the last commit (ok as this is a scratch clone and are not doing any push from here)::

    git reset --hard HEAD^ 

    epsilon:junosw_check2 blyth$ vi Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw_check2 blyth$ git show main:Examples/Tutorial/python/Tutorial/JUNODetSimModule.py > /tmp/JUNODetSimModule.py



Try bringing in the old setup_generator_opticks with new name and moving the updated method away from setup_generator_nuwro
-------------------------------------------------------------------------------------------------------------------------------

::

    epsilon:junosw_check2 blyth$ git add . 
    epsilon:junosw_check2 blyth$ git commit -m "retain OLD_METHOD_LEFT_HERE_TO_AVOID_MERGE_CONFLICT_setup_generator_opticks and add new setup_generator_opticks elsewhere to avoid merge conflict with setup_generator_nuwro "
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 1e3b538] retain OLD_METHOD_LEFT_HERE_TO_AVOID_MERGE_CONFLICT_setup_generator_opticks and add new setup_generator_opticks elsewhere to avoid merge conflict with setup_generator_nuwro
     1 file changed, 46 insertions(+), 27 deletions(-)
    epsilon:junosw_check2 blyth$ 



Then back to main and try the merge again : it works this time : so trash the clone
---------------------------------------------------------------------------------------

::

    epsilon:junosw_check2 blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw_check2 blyth$     

    epsilon:junosw_check2 blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw_check2 blyth$ git merge --no-ff --no-commit $(branch)
    Auto-merging cmake/JUNODependencies.cmake
    Auto-merging Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    Auto-merging Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Automatic merge went well; stopped before committing as requested
    epsilon:junosw_check2 blyth$ 

    epsilon:junosw_check2 blyth$ git status
    On branch main
    Your branch is up-to-date with 'origin/main'.

    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

        modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
        new file:   Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
        new file:   Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
        modified:   Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/DetSimV2/PMTSim/CMakeLists.txt
        new file:   Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h
        new file:   Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
        modified:   Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
        new file:   Simulation/DetSimV2/PMTSim/include/ModelTrigger_Debug.h
        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
        modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   Simulation/DetSimV2/PhysiSim/CMakeLists.txt
        modified:   Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
        modified:   Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
        modified:   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
        modified:   Simulation/GenTools/GenTools/GtOpticksTool.h
        modified:   Simulation/GenTools/src/GtOpticksTool.cc
        modified:   Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/MultiFilmModel.h
        new file:   Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/_TComplex.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/Material.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
        new file:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Utilities/EGet/EGet/EGet.h
        modified:   cmake/JUNODependencies.cmake

    epsilon:junosw_check2 blyth$ 

    epsilon:junosw_check2 blyth$ git merge --abort 
    fatal: There is no merge to abort (MERGE_HEAD missing).
    epsilon:junosw_check2 blyth$ 


Cannot abort the merge as there isnt one, so reset HEAD::

    epsilon:junosw_check2 blyth$ git reset HEAD
    Unstaged changes after reset:
    M	Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M	Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    M	Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
    M	Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    M	Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    M	Simulation/DetSimV2/PMTSim/CMakeLists.txt
    M	Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    M	Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    M	Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
    M	Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    M	Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    M	Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    M	Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    M	Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
    M	Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
    M	Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    M	Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    M	Simulation/DetSimV2/PhysiSim/CMakeLists.txt
    M	Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
    M	Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    M	Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    M	Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    M	Simulation/GenTools/GenTools/GtOpticksTool.h
    M	Simulation/GenTools/src/GtOpticksTool.cc
    M	Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/MultiFilmModel.h
    M	Simulation/SimSvc/MultiFilmSimSvc/src/Material.h
    M	Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.h
    M	Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
    M	Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
    M	Utilities/EGet/EGet/EGet.h
    M	cmake/JUNODependencies.cmake
    epsilon:junosw_check2 blyth$ 



But that leaves lots of things in wc::

    epsilon:junosw_check2 blyth$ git s
    On branch main
    Your branch is up-to-date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
        modified:   Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
        modified:   Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/DetSimV2/PMTSim/CMakeLists.txt
        modified:   Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
        modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   Simulation/DetSimV2/PhysiSim/CMakeLists.txt
        modified:   Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
        modified:   Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
        modified:   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
        modified:   Simulation/GenTools/GenTools/GtOpticksTool.h
        modified:   Simulation/GenTools/src/GtOpticksTool.cc
        modified:   Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/MultiFilmModel.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/Material.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/Matrix.h
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/MultiFilmModel.cc
        modified:   Simulation/SimSvc/MultiFilmSimSvc/src/OpticalSystem.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Utilities/EGet/EGet/EGet.h
        modified:   cmake/JUNODependencies.cmake

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
        Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
        Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h
        Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
        Simulation/DetSimV2/PMTSim/include/ModelTrigger_Debug.h
        Simulation/SimSvc/MultiFilmSimSvc/MultiFilmSimSvc/_TComplex.h
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw_check2 blyth$ 

So trash the clone::

    rm -rf /tmp/junosw_check2 

