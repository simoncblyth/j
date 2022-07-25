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

1. addition of debugging getLV code and PMTSim standalone instrumentation : changes to header and imp
2. substantive uncoincide additions
3. documenation text 


How do the SVN WC changes compare with j ?
----------------------------------------------

::

    epsilon:j blyth$ find . -name HamamatsuMaskManager.* -o -name NNVTMaskManager.* 
    ./PMTSim/HamamatsuMaskManager.cc
    ./PMTSim/NNVTMaskManager.cc
    ./PMTSim/NNVTMaskManager.hh
    ./PMTSim/HamamatsuMaskManager.hh
    epsilon:j blyth$ 


No difference::

    N[blyth@localhost PMTSim]$ jdiff HamamatsuMaskManager NNVTMaskManager
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh /home/blyth/j/PMTSim/HamamatsuMaskManager.hh
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh /home/blyth/j/PMTSim/NNVTMaskManager.hh
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc /home/blyth/j/PMTSim/HamamatsuMaskManager.cc
    diff /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc /home/blyth/j/PMTSim/NNVTMaskManager.cc
    N[blyth@localhost PMTSim]$ jdiff HamamatsuMaskManager NNVTMaskManager | sh 
    N[blyth@localhost PMTSim]$ 

The SVN working copy can safely be reverted as the jps versions match them::

    N[blyth@localhost PMTSim]$ jcopyback HamamatsuMaskManager NNVTMaskManager 
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    cp /home/blyth/j/PMTSim/NNVTMaskManager.hh /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    cp /home/blyth/j/PMTSim/HamamatsuMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    cp /home/blyth/j/PMTSim/NNVTMaskManager.cc /data/blyth/junotop/offline/./Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost PMTSim]$ 


Source SVN has probably been updated ?
----------------------------------------

* 5 months ago changes in .cc from lintao 

* 5306 WIP: try to reduce the radius at front using 4 zplanes (bottom:R, 
* 5305 WIP: in order to avoid the overlap between water and tail of PMT, 
* 5302 WIP: debug the overlap problem in the virtual volumes.

* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc

No changes in header since 11 months:

* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
* https://juno.ihep.ac.cn/trac/log/offline/trunk/Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh


* https://juno.ihep.ac.cn/trac/changeset/5302/offline
 
  * changing visatt

* https://juno.ihep.ac.cn/trac/changeset/5305/offline

  * pmt_eq_to_bottom 1cm change done in quadriplicate

* https://juno.ihep.ac.cn/trac/changeset/5306/offline

  * "// BELOW is using 4 zplanes"




revert the WC changes
-------------------------

Looking at my versions it looks like the lintao changes are already there 

* so I can revert the WC, update svn and compare again and it should be possible 
  to jcopyback : if not I just have to make the changes again 


::

    N[blyth@localhost offline]$ jo
    /data/blyth/junotop/offline
    M       Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    M       Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    M       Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
    Reverted 'Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh
    Reverted 'Simulation/DetSimV2/PMTSim/include/NNVTMaskManager.hh'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    Reverted 'Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc'
    N[blyth@localhost offline]$ svn revert Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    Reverted 'Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc'
    N[blyth@localhost offline]$ jo
    /data/blyth/junotop/offline
    N[blyth@localhost offline]$ 





