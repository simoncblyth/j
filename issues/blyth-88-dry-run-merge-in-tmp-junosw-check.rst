blyth-88-dry-run-merge-in-tmp-junosw-check
=============================================



DONE : dry run merge in /tmp/junosw_check : has conflict in 2 files : abort the dry run merge
------------------------------------------------------------------------------------------------

::

    epsilon:junosw blyth$ git remote -v
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (fetch)
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (push)
    epsilon:junosw blyth$ cd /tmp
    epsilon:tmp blyth$ 
    epsilon:tmp blyth$ 
    epsilon:tmp blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junosw.git junosw_check
    Cloning into 'junosw_check'...
    remote: Enumerating objects: 8168, done.
    remote: Counting objects: 100% (8037/8037), done.
    remote: Compressing objects: 100% (4461/4461), done.
    remote: Total 8168 (delta 3359), reused 7581 (delta 3045), pack-reused 131
    Receiving objects: 100% (8168/8168), 14.92 MiB | 200.00 KiB/s, done.
    Resolving deltas: 100% (3410/3410), done.
    epsilon:tmp blyth$ 

    epsilon:junosw_check blyth$ git branch 
    * main

    epsilon:junosw_check blyth$ git branch -a
    * main
      remotes/origin/62-how-to-save-the-reconstructed-muon-secondary-particle-information-such-as-energy-vertex-position
      remotes/origin/HEAD -> origin/main
      remotes/origin/J22.2.x
      remotes/origin/TtRecTrack
      remotes/origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
      remotes/origin/gonchar-pmttable-vector
      remotes/origin/jiangwei_Deconvolution2Tool
      remotes/origin/labit_74-spmtcalibalg-consumes-lots-of-time-for-high-energy-events
      remotes/origin/lintao-add-a-dummy-feature
      remotes/origin/lintao-paradb-application
      remotes/origin/liuzhen-elecsim_waveform_saving
      remotes/origin/main
      remotes/origin/muon-edm-update
      remotes/origin/mywang-darknoise
      remotes/origin/mywang-oecsteering
      remotes/origin/quzhenning-oum_modify_for_gengenie
      remotes/origin/quzhenning-slitalg-branch
      remotes/origin/reviewCdLpmtQSpecMuonRecTool
      remotes/origin/tut-EDM
      remotes/origin/wuchx-ID-static
      remotes/origin/wuchx-IDtest
      remotes/origin/wuchx-IDtest-all
      remotes/origin/wudr_updateMuonGenerator
      remotes/origin/zhangyongpeng_atmo_info
      remotes/origin/zhangyongpeng_deposit_voxel
      remotes/origin/zhangyp-oum-oec-updated
      remotes/origin/zhangyu-CDwaterClippingmuon-track
    epsilon:junosw_check blyth$ 
    epsilon:junosw_check blyth$ 

    epsilon:junosw_check blyth$ git --version
    git version 2.14.3 (Apple Git-98)

    epsilon:junosw_check blyth$ branch=blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    epsilon:junosw_check blyth$ git checkout -b $branch origin/$branch
    Branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess set up to track remote branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess from origin.
    Switched to a new branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'


    epsilon:junosw_check blyth$ git branch 
    * blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
      main
    epsilon:junosw_check blyth$ 

    epsilon:junosw_check blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.

    epsilon:junosw_check blyth$ git merge --no-ff --no-commit $branch 
    Auto-merging cmake/JUNODependencies.cmake
    CONFLICT (content): Merge conflict in cmake/JUNODependencies.cmake
    Auto-merging Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    Auto-merging Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    CONFLICT (content): Merge conflict in Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Automatic merge failed; fix conflicts and then commit the result.
    epsilon:junosw_check blyth$ 


    epsilon:junosw_check blyth$ git status
    On branch main
    Your branch is up-to-date with 'origin/main'.

    You have unmerged paths.
      (fix conflicts and run "git commit")
      (use "git merge --abort" to abort the merge)

    Changes to be committed:

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

    Unmerged paths:
      (use "git add <file>..." to mark resolution)

        both modified:   Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
        both modified:   cmake/JUNODependencies.cmake

    epsilon:junosw_check blyth$ 



Mystifying fails::

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
    1391         # optical photon gun (using LS emission spectrum)
    1392         gun = gt.createTool("GtOpScintTool/gun")
    1393         gun.property("PhotonsPerEvent").set(args.totalphotons)
    1394         gun.property("cosThetaLower").set(args.cos_theta_lower)
    1395         gun.property("cosThetaUpper").set(args.cos_theta_upper)
    1396    
    1397         # Some user need to fix the wavelength
    1398         if args.fixed_energy:
    1399             gun.property("EnergyMode").set("Fixed")
    1400             gun.property("FixedEnergy").set(args.fixed_energy)
    1401             gun.property("TimeMode").set("Fixed")


::

    189 # define NuWro_Found if NuWro_LIBRARIES is not empty$
    190 if(NUWRO_LIBRARIES)$
    191     set(NuWro_Found TRUE)$
    192 else()$
    193     set(NuWro_Found FALSE)$
    194 endif()$
    195 <<<<<<< HEAD$
    196 link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)$
    197 =======$
    198 link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)$
    199 >>>>>>> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess$


::

    epsilon:junosw_check blyth$ vi Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw_check blyth$ vi cmake/JUNODependencies.cmake
    epsilon:junosw_check blyth$ 
    epsilon:junosw_check blyth$ git merge --abort 
    epsilon:junosw_check blyth$ git status 
    On branch main
    Your branch is up-to-date with 'origin/main'.

    nothing to commit, working tree clean
    epsilon:junosw_check blyth$ 




Problem seems related to a lack of eol in main:cmake/JUNODependencies.cmake
---------------------------------------------------------------------------------

main::

    158 # define NuWro_Found if NuWro_LIBRARIES is not empty
    159 if(NUWRO_LIBRARIES)
    160     set(NuWro_Found TRUE)
    161 else()
    162     set(NuWro_Found FALSE)
    163 endif()
    164 link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    "cmake/JUNODependencies.cmake" [noeol] 164L, 4962C

branch::

    189 # define NuWro_Found if NuWro_LIBRARIES is not empty
    190 if(NUWRO_LIBRARIES)
    191     set(NuWro_Found TRUE)
    192 else()
    193     set(NuWro_Found FALSE)
    194 endif()
    195 link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    "cmake/JUNODependencies.cmake" 195L, 6375C




::

    epsilon:junosw_check blyth$ git checkout $branch 
    epsilon:junosw_check blyth$ git diff main -- Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    epsilon:junosw_check blyth$ git difftool main -- Examples/Tutorial/python/Tutorial/JUNODetSimModule.py

    ## looks like the engine is confused by 




    epsilon:junosw_check blyth$ vi cmake/JUNODependencies.cmake
    epsilon:junosw_check blyth$ git s
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   cmake/JUNODependencies.cmake

    no changes added to commit (use "git add" and/or "git commit -a")

    no changes added to commit
    epsilon:junosw_check blyth$ git add . 
    epsilon:junosw_check blyth$ git commit -m "merge fail appears to be related to lack of eol at end of cmake/JUNODependencies.cmake so try adding a blank line"
    [blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess 36907a2] merge fail appears to be related to lack of eol at end of cmake/JUNODependencies.cmake so try adding a blank line
     1 file changed, 1 insertion(+)
    epsilon:junosw_check blyth$ 




Try the dry run merge again with the blank line : doesnt work 
--------------------------------------------------------------

::

    epsilon:junosw_check blyth$ git branch 
    * blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
      main
    epsilon:junosw_check blyth$ git checkout main
    Switched to branch 'main'
    Your branch is up-to-date with 'origin/main'.
    epsilon:junosw_check blyth$ 


    epsilon:junosw_check blyth$ git merge --no-ff --no-commit  $branch 
    Auto-merging cmake/JUNODependencies.cmake
    CONFLICT (content): Merge conflict in cmake/JUNODependencies.cmake
    Auto-merging Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    Auto-merging Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    CONFLICT (content): Merge conflict in Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Automatic merge failed; fix conflicts and then commit the result.
    epsilon:junosw_check blyth$ 




::

    .
     endif()
    -link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    +link_directories($ENV{JUNO_EXTLIB_nuwro_HOME}/lib)
    \ No newline at end of file
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git diff $branch -- cmake/JUNODependencies.cmake 



Chomp the eol of cmake/JUNODependencies.cmake in the branch
--------------------------------------------------------------

::

    epsilon:junosw blyth$ perl -pi -e 'chomp if eof' cmake/JUNODependencies.cmake


    epsilon:junosw blyth$ git status
    On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Your branch is up-to-date with 'origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   cmake/JUNODependencies.cmake

    no changes added to commit (use "git add" and/or "git commit -a")


    epsilon:junosw blyth$ git diff 
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
    epsilon:junosw blyth$ 



Start again
--------------

::

    epsilon:junosw_check blyth$ cd ..
    epsilon:tmp blyth$ rm -rf junosw_check




