prep_branches_for_junosw_mods
================================

::

    epsilon:opticks blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping
    Your branch is up-to-date with 'origin/blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Detector/Geometry/Geometry/PMTCategory.h
             PMTCategory::NameMap static

        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
             updates for Opticks SEvt rejig to support opticksMode:3 CPU/GPU comparison 

        modified:   Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
             desc method   

        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
             descDetail method

        modified:   Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
             desc method   

        modified:   Simulation/DetSimV2/PMTSim/include/Tub3inchPMTV3Manager.hh
             make it PMTSIM_STANDALONE compliant, add e-control Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM
            
        modified:   Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh


        modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
        modified:   Simulation/GenTools/src/GtOpticksTool.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ 



