pmt_geometry_simplify_with_ZSolid
====================================


* hmm ZSolid and ZCanvas should be private headers, so change to .h to signify that 

::

    epsilon:PMTSim blyth$ ./grab_back.sh 
    cp /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuR12860PMTManager.hh
    cp /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/Hamamatsu_R12860_PMTSolid.hh
    cp /Users/blyth/j/PMTSim/NNVTMCPPMTManager.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMCPPMTManager.hh
    cp /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVT_MCPPMT_PMTSolid.hh
    cp /Users/blyth/j/PMTSim/ellipse_intersect_circle.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.cc
    cp /Users/blyth/j/PMTSim/ellipse_intersect_circle.hh /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/ellipse_intersect_circle.hh
    cp /Users/blyth/j/PMTSim/HamamatsuR12860PMTManager.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    cp /Users/blyth/j/PMTSim/Hamamatsu_R12860_PMTSolid.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc
    cp /Users/blyth/j/PMTSim/NNVTMCPPMTManager.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    cp /Users/blyth/j/PMTSim/NNVT_MCPPMT_PMTSolid.cc /Users/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc
    cp ZSolid.h /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZSolid.h
    cp ZSolid.cc /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZSolid.cc
    cp ZCanvas.h /Users/blyth/junotop/offline/Simulation/DetSimV2/PMTSim/src/ZCanvas.h
    epsilon:PMTSim blyth$ 


* DONE : STANDALONE is too generic, swited to PMTSIM_STANDALONE 

* TODO: replace python switches JUNO_PMT20INCH_POLYCONE_NECK -> JUNO_PMT20INCH_OBSOLETE_TORUS_NECK 
 

Review of Code Changes (using eg "jdiff Hamamatsu_R12860_PMTSolid")
----------------------------------------------------------------------

Hamamatsu_R12860_PMTSolid and NNVT_MCPPMT_PMTSolid

    Polycone neck now becomes the default, old obsolete torus neck can be 
    still be used via python option.  

    1. add ability to be compiled standalone with macro -DPMTSIM_STANDALONE 

    2. replace m_polycone_neck with the converse m_obsolete_torus_neck 

    3. factorize out methods : construct_polycone_neck construct_obsolete_torus_neck


HamamatsuR12860PMTManager and NNVTMCPPMTManager

    1. add ability to be compiled standalone with macro -DPMTSIM_STANDALONE 

    2. add debug interface providing access to consituent solids and volumes 

    3. add m_plus_dynode and m_profligate_tail_cut

    4. add member m_pmt_equator_to_bottom to allow splitting into methods

    5. reorganize helper_make_solid using ZSolid cutting 









TODO:

* review the code changes 

* add the python switches to control these:: 

  1. JUNO_PMT20INCH_PROFLIGATE_TAIL_CUT


* PMT geometry changes are not only relevant to opticks running 

  * so first check without opticks in the build  
  * :doc:`../docs/offline_opticks_cmake_usage`









