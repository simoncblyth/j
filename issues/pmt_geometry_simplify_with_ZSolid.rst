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


Incorporation : lots of unused variable warnings as assert is optimized away in Release mode 
-----------------------------------------------------------------------------------------------

Lots of ZSolid warnings because it looks like assert is being removed in Release mode.

* https://stackoverflow.com/questions/22140520/how-to-enable-assert-in-cmake-release-mode

Manage to reproduce many of the warnings in standalone j/PMTSim with::

    epsilon:PMTSim blyth$ OPTICKS_BUILDTYPE=Release om-conf
    epsilon:PMTSim blyth$ touch ZSolid.cc ; om



Incorporation : Runtime fail after adding new sources
--------------------------------------------------------

::

    [Ellipse_Intersect_Circle 
    ]Ellipse_Intersect_Circle (  139.6247,  -158.1783) 
    [ ZSolid::ApplyZCutTree zcut    183.225 pmt_delta      0.001 body_delta     -4.999 inner_delta     -5.000 zcut+pmt_delta    183.226 zcut+body_delta    178.226 zcut+inner_delta    178.225
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python: symbol lookup error: /data/blyth/junotop/offline/InstallArea/lib64/libPMTSim.so: undefined symbol: _ZN6ZSolid13ApplyZCutTreeEPK8G4VSoliddb
    [Inferior 1 (process 434128) exited with code 0177]


This is because offline PKG uses dirty listing of sources so CMake cannot detect added source files at make time, 
have to manually configure again in order for CMake to notice that there are new sources.




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









