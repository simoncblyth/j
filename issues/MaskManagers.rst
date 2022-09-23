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


WIP : get setup into git and new working approach
---------------------------------------------------

::

    epsilon:junotop blyth$ mv junoenv junoenv_svn 
    epsilon:junotop blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
    Cloning into 'junoenv'...
    remote: Enumerating objects: 313, done.
    remote: Total 313 (delta 0), reused 0 (delta 0), pack-reused 313
    Receiving objects: 100% (313/313), 153.61 KiB | 131.00 KiB/s, done.
    Resolving deltas: 100% (170/170), done.
    epsilon:junotop blyth$ 

::

    045 function junoenv-offline-checkout {
     46     # checkout all code
     47     local msg="==== $FUNCNAME: "
     48     local repourl=$1; shift
     49     local dstname=$1; shift
     50     local revision=$1; shift
     51 
     52     echo $msg checkout the code $repourl 
     53     # check
     54     git clone $repourl $dstname || exit -1
     55     cd $dstname && git checkout $revision || exit -1
     56 }


    106 function junoenv-offline {
    107     local msg="=== $FUNCNAME: "
    108     # the main handler in this script
    109     local branchname=${1:-$(junoenv-offline-default-branch)}
    110     local revision=${2:-}
    111     # check version
    112     junoenv-offline-version $branchname
    113     if [ "$?" != "0" ]; then
    114         echo $msg branchesname ret: $?
    115         return 1
    116     fi
    117 
    118 
    119     local url=$(junoenv-offline-url $branchname)
    120     echo $msg $?
    121     echo $msg URL: $url
    122     # change directory to $JUNOTOP
    123     pushd $JUNOTOP >& /dev/null
    124     junoenv-offline-checkout $url $(junoenv-offline-name) $revision
    125     junoenv-offline-preq
    126     junoenv-offline-compile
    127     popd
    128 
    129 }




libmore-data fail : judged harmless as coming from cvmfs link anyhow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HUH: libmore-data-install trying to rsync to cvmfs? ::

    === juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: After source: libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: status: 0 libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused libmore-data
    === junoenv-external-libs: juno-ext-libs-all libmore-data
    ==== juno-ext-libs-get:
    [libmore-data-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: ensdf-files-20140630.tar already exists
    ==== juno-ext-libs-conf:
    ==== juno-ext-libs-make:
    ==== juno-ext-libs-install:
    [libmore-data-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-libmore-data-install-
    [libmore-data-install] sending incremental file list
    [libmore-data-install] rsync: chgrp "/data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/." failed: Read-only file system (30)
    [libmore-data-install] ./
    [libmore-data-install] ar001.ens.bz2
    [libmore-data-install] ar001h.ens.bz2
    [libmore-data-install] ar001nn.ens.bz2
    [libmore-data-install] ar002.ens.bz2


    Last login: Fri Sep 23 19:08:47 2022 from lxslc714.ihep.ac.cn
    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/
    total 24458
    113 drwxr-xr-x. 2 cvmfs cvmfs 114688 Mar  4  2022 .
      4 -rw-r--r--. 1 cvmfs cvmfs   3529 Mar  4  2022 ar28614.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1110 Mar  4  2022 ar286cn.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2941 Mar  4  2022 ar28714.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1875 Mar  4  2022 ar28715.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2809 Mar  4  2022 ar28814.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1942 Mar  4  2022 ar28815.ens.bz2
      5 -rw-r--r--. 1 cvmfs cvmfs   4791 Mar  4  2022 ar28914.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2396 Mar  4  2022 ar28915.ens.bz2

The 0.8.3 is link to cvmfs::

    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/
    total 4
    4 drwxrwxr-x. 38 blyth blyth 4096 Jul 25 18:30 ..
    0 drwxrwxr-x.  2 blyth blyth   19 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 0.8.3 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/libmore/0.8.3
    N[blyth@localhost ~]$ 

Note that libonnxruntime has large number of github submodules::

    == junoenv-external-libs: juno-ext-libs-check-is-reused libonnxruntime
    === junoenv-external-libs: juno-ext-libs-all libonnxruntime
    ==== juno-ext-libs-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get: clone https://github.com/microsoft/onnxruntime
    [libonnxruntime-conf] Cloning into 'libonnxruntime-1.11.1'...
    [libonnxruntime-conf] Submodule 'cmake/external/FP16' (https://github.com/Maratyszcza/FP16.git) registered for path 'cmake/external/FP16'
    [libonnxruntime-conf] Submodule 'cmake/external/SafeInt/safeint' (https://github.com/dcleblanc/SafeInt.git) registered for path 'cmake/external/SafeInt/safeint'
    [libonnxruntime-conf] Submodule 'cmake/external/XNNPACK' (https://github.com/google/XNNPACK.git) registered for path 'cmake/external/XNNPACK'
    [libonnxruntime-conf] Submodule 'cmake/external/cub' (https://github.com/NVlabs/cub.git) registered for path 'cmake/external/cub'
    [libonnxruntime-conf] Submodule 'cmake/external/cxxopts' (https://github.com/jarro2783/cxxopts.git) registered for path 'cmake/external/cxxopts'
    [libonnxruntime-conf] Submodule 'cmake/external/date' (https://github.com/HowardHinnant/date.git) registered for path 'cmake/external/date'
    [libonnxruntime-conf] Submodule 'cmake/external/dlpack' (https://github.com/dmlc/dlpack.git) registered for path 'cmake/external/dlpack'
    [libonnxruntime-conf] Submodule 'cmake/external/eigen' (https://gitlab.com/libeigen/eigen.git) registered for path 'cmake/external/eigen'
    [libonnxruntime-conf] Submodule 'cmake/external/emsdk' (https://github.com/emscripten-core/emsdk.git) registered for path 'cmake/external/emsdk'
    [libonnxruntime-conf] Submodule 'cmake/external/flatbuffers' (https://github.com/google/flatbuffers.git) registered for path 'cmake/external/flatbuffers'

Even though it looks to have hung checking ps shows that some progress is being made, with movement between submodules::

    N[blyth@localhost ~]$ ps aux | grep blyth



WIP : review all changes from jps that want to be in offline
--------------------------------------------------------------

jdiff HamamatsuR12860PMTManager

   * switch to CamelCase lv/pv/solid names in debug interface as underscore used to delimit options
   * proper base class setup for now non-pure-virtual IGeomManager (providing eg getValues debug method)
   * reduce code differences with and without PMTSIM_STANDALONE (due to new IGeomManager dummy declProp)

jdiff NNVTMCPPMTManager

   * switch to CamelCase lv/pv/solid names in debug interface as underscore used to delimit options
   * proper base class setup for now non-pure-virtual IGeomManager (providing eg getValues debug method)
    
jdiff NNVTMaskManager

   * add IGeomManager base class with PMTSIM_STANDALONE macro providing debug access to Geant4 objects 
   * add debug interface getLV getPV getSolid by name, and private members for Geant4 objects 
   * use private members instead of method scope variables for Geant4 objects
   * within PMTSIM_STANDALONE addValue collection of values for debug access as NP array via IGeomManager base class  
   * add MaskIn_uncoincide_z to avoid coincidence 
   * add TailInnerI_uncoincide_z to avoid coincidence

jdiff HamamatsuMaskManager

   * add IGeomManager base class with PMTSIM_STANDALONE macro providing debug access to Geant4 objects 
   * add debug interface getLV getPV getSolid by name, and private members for Geant4 objects 
   * use private members instead of method scope variables for Geant4 objects
   * within PMTSIM_STANDALONE addValue collection of values for debug access as NP array via IGeomManager base class  
   * add MaskIn_uncoincide_z to avoid coincidence 
   * add TailInnerI_uncoincide_z to avoid coincidence 


Branch title : blyth-PMTSIM_STANDALONE-debug-interface-for-mask-managers-and-uncoincide-mask-subtractions



ZSolid vs X4SolidTree
------------------------

Why did I make the change from ZSolid to X4SolidTree withinn jps ?

* this is presumably because PMTSim depends on SysRap which has SCanvas.h already 
  
  * BUT: as offline dev so inconvenient compared to Opticks it is expedient 
    just to throw away code put into offline : not regarding it as part of the 
    ongoing history of the versions within Opticks

  * SO : that means to use different names within offline and opticks

* HMM: it was a mistake to change names within jps:j/PMTSim  
* should regard jps as temporary development ground for visiting classes from offline
  and keep them distinct from Opticks : with minimal changes

* regard ZSolid/ZCanvas as names of version included with offline
* keep X4SolidTree.hh as distinct other class kept with extg4 

Sort this out by:

1. changing the X4SolidTree name back to ZSolid : to reduce differences
2. review differences between jps and jo and decide if any diffs should be 
   incorporated into offline 




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





