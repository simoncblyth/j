jdiff_jPMTSIM_changes
=========================

DONE : review j/PMTSim changes and get some of them into JUNOSW branches
--------------------------------------------------------------------------

HMM: j/PMTSim having a separate sources that are manually synced like
are doing below is not a longterm solution..

Want to be able to do the Opticks PMTSim build based off the 
junosw sources. So move the local copies aside::

    epsilon:PMTSim blyth$ mkdir aside
    epsilon:PMTSim blyth$ mv HamamatsuMaskManager.hh aside/
    epsilon:PMTSim blyth$ mv HamamatsuMaskManager.cc aside/

And try j/PMTSim CMake building with some JUNOTOP sources::

     17 include_directories($ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/include)
     18 
     19 set(SOURCES)
     20 set(HEADERS)
     21 
     22 list(APPEND SOURCES
     23      
     24      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
     25      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
     26      
     27      # TRYING to move to having common sources for junosw/PMTSim and j/PMTSim : just different options
     28      #HamamatsuMaskManager.cc
     29      #NNVTMaskManager.cc
     30      
     31      NNVTMCPPMTManager.cc
     32      HamamatsuR12860PMTManager.cc
     33      Hamamatsu_R12860_PMTSolid.cc
     34      NNVT_MCPPMT_PMTSolid.cc
     35      
     36      LowerChimney.cc
     37      LowerChimneyMaker.cc
     38      
     39      
     40      PMTSim.cc
     41      P4Volume.cc
     42      ZSolid.cc
     43      MaterialSvc.cc
     44      DetectorConstruction.cc
     45 )    






::

    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh 

    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh

    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    epsilon:junosw blyth$ scp P:junotop/junosw/Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh Simulation/DetSimV2/PMTSim/include/





* blyth-10-standalone-mask-geometry-debug-interface


Group changes into a few commits. 


::

    epsilon:PMTSim blyth$ jdiff NNVTMCPPMTManager
    epsilon:PMTSim blyth$ jdiff HamamatsuR12860PMTManager

    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh /Users/blyth/j/PMTSim/NNVTMCPPMTManager.hh                 ## NONE
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.hh ## NONE

    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc /Users/blyth/j/PMTSim/NNVTMCPPMTManager.cc     
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.cc
    ## Change debug interface to use CamelCase as underscores used now used to delimit options


::

    On branch blyth-10-standalone-mask-geometry-debug-interface
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
        modified:   Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ git add . 
    N[blyth@localhost junosw]$ git commit -m "WIP: #10 change PMT geom debug interface to use CamelCase names as underscores now used to delimit options"
    [blyth-10-standalone-mask-geometry-debug-interface 3acec42] WIP: #10 change PMT geom debug interface to use CamelCase names as underscores now used to delimit options
     2 files changed, 74 insertions(+), 51 deletions(-)
    N[blyth@localhost junosw]$ 




     

    jcopyback HamamatsuMaskManager
    




    epsilon:PMTSim blyth$ jdiff HamamatsuMaskManager
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh /Users/blyth/j/PMTSim/HamamatsuMaskManager.hh
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc /Users/blyth/j/PMTSim/HamamatsuMaskManager.cc
    ## add PMTSIM_STANDALONE debug interface giving standalone access to Geant4 solids and volumes 

    epsilon:PMTSim blyth$ jdiff NNVTMaskManager
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh /Users/blyth/j/PMTSim/NNVTMaskManager.hh
    diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc /Users/blyth/j/PMTSim/NNVTMaskManager.cc
    epsilon:PMTSim blyth$ 

    ## set default uncoincide to 1mm



    N[blyth@localhost PMTSim]$ jcopyback HamamatsuMaskManager
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.hh /data/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.cc /data/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    N[blyth@localhost PMTSim]$ jcopyback HamamatsuMaskManager | sh 

    N[blyth@localhost PMTSim]$ jcopyback NNVTMaskManager
    cp /home/blyth/j/PMTSim/NNVTMaskManager.hh /data/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    cp /home/blyth/j/PMTSim/NNVTMaskManager.cc /data/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost PMTSim]$ jcopyback NNVTMaskManager | sh 
    N[blyth@localhost PMTSim]$ 











    epsilon:PMTSim blyth$ diff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.cc
    ## NO CHANGE 
    epsilon:PMTSim blyth$ vimdiff /Users/blyth/junotop/junosw/./Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.hh
    ## PMTSIM_API_EXPORT 




