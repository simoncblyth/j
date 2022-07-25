MaskManagers
=================


For a long time have had uncommitted SVN change::

    N[blyth@localhost ~]$ jre
    === j-runtime-env-:
    === j-runtime-env-:
    /data/blyth/junotop/offline
    M       Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    M       Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost offline]$ 

Need to revisit this and commit before can work on updating 
the integration to use the new workflow. 

The changes are 

1. addition of debugging getLV code
2. substantive uncoincide additions
3. documenation text 


::

    epsilon:j blyth$ find . -name HamamatsuMaskManager.* -o -name NNVTMaskManager.* 
    ./PMTSim/HamamatsuMaskManager.cc
    ./PMTSim/NNVTMaskManager.cc
    ./PMTSim/NNVTMaskManager.hh
    ./PMTSim/HamamatsuMaskManager.hh
    epsilon:j blyth$ 







