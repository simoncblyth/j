compilation-feb2022
=====================


[ 10%] Building CXX object Calibration/CondDB/CMakeFiles/CondDB.dir/src/IOV.cc.o
/data/blyth/junotop/offline/Calibration/CondDB/src/CondDBSvc.cc:7:10: fatal error: SniperKernel/SharedElemFactory.h: No such file or directory
 #include "SniperKernel/SharedElemFactory.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [Calibration/CondDB/CMakeFiles/CondDB.dir/src/CondDBSvc.cc.o] Error 1
make[2]: *** Waiting for unfinished jobs....


::

    N[blyth@localhost junotop]$ find . -name '*.cc' -exec grep -H SharedElemFactory {} \;
    ./offline/Detector/Geometry/src/PMTParamSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Detector/Geometry/src/RecGeomSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Simulation/DetSimV2/MCParamsSvc/src/MCParamsFileSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Simulation/SimSvc/SpmtElecConfigSvc/src/SpmtElecConfigSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Calibration/PMTCalibSvc/src/PMTCalibSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    ./offline/Calibration/CondDB/src/CondDBSvc.cc:#include "SniperKernel/SharedElemFactory.h"
    N[blyth@localhost junotop]$ 
    N[blyth@localhost junotop]$ 



SharedElemFactory.h is in the 2.1 tarball::

    rw-rw-r-- root/root      1550 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/NamedElement.h
    -rw-rw-r-- root/root      4274 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/Property.h
    -rw-rw-r-- root/root      2936 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/PropertyMgr.h
    -rw-rw-r-- root/root      2207 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/RefBase.h
    -rw-rw-r-- root/root      3414 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/SharedElemFactory.h
    -rw-rw-r-- root/root      1702 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/Sniper.h
    -rw-rw-r-- root/root      1872 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/SniperContext.h
    -rw-rw-r-- root/root      2399 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/SniperDataPtr.h
    -rw-rw-r-- root/root      1530 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/SniperException.h
    -rw-rw-r-- root/root     10660 2022-01-04 14:15 sniper-2.1/SniperKernel/SniperKernel/SniperJSON.h

But it does not get installed::

    N[blyth@localhost sniper]$ l InstallArea/include/SniperKernel/
    total 152
     0 drwxrwxr-x. 6 blyth blyth    87 Mar  1 23:57 ..
     4 drwxr-xr-x. 2 blyth blyth  4096 Mar  1 23:57 .
     4 -rw-r--r--. 1 blyth blyth  2004 Oct 29 09:04 AlgBase.h
     4 -rw-r--r--. 1 blyth blyth   957 Oct 29 09:04 AlgFactory.h
     4 -rw-r--r--. 1 blyth blyth  2918 Oct 29 09:04 DataBuffer.h
     4 -rw-r--r--. 1 blyth blyth  1382 Oct 29 09:04 DataMemSvc.h
     4 -rw-r--r--. 1 blyth blyth  1390 Oct 29 09:04 DeclareDLE.h
     4 -rw-r--r--. 1 blyth blyth  2639 Oct 29 09:04 DLElement.h
     4 -rw-r--r--. 1 blyth blyth  2106 Oct 29 09:04 DleSupervisor.h
     4 -rw-r--r--. 1 blyth blyth  2825 Oct 29 09:04 ExecUnit.h
     4 -rw-r--r--. 1 blyth blyth   910 Oct 29 09:04 IDataBlock.h
     4 -rw-r--r--. 1 blyth blyth  1488 Oct 29 09:04 IIncidentHandler.h
     4 -rw-r--r--. 1 blyth blyth  2217 Oct 29 09:04 Incident.h
     4 -rw-r--r--. 1 blyth blyth  1903 Oct 29 09:04 JSONParser.h
     4 -rw-r--r--. 1 blyth blyth  1550 Oct 29 09:04 NamedElement.h
     8 -rw-r--r--. 1 blyth blyth  4274 Oct 29 09:04 Property.h
     4 -rw-r--r--. 1 blyth blyth  2936 Oct 29 09:04 PropertyMgr.h
     4 -rw-r--r--. 1 blyth blyth  2207 Oct 29 09:04 RefBase.h
     4 -rw-r--r--. 1 blyth blyth  1872 Oct 29 09:04 SniperContext.h
     4 -rw-r--r--. 1 blyth blyth  2399 Oct 29 09:04 SniperDataPtr.h
     4 -rw-r--r--. 1 blyth blyth  1530 Oct 29 09:04 SniperException.h
     4 -rw-r--r--. 1 blyth blyth  1484 Oct 29 09:04 Sniper.h
    12 -rw-r--r--. 1 blyth blyth 10660 Oct 29 09:04 SniperJSON.h
     4 -rw-r--r--. 1 blyth blyth  2600 Oct 29 09:04 SniperLog.h
     4 -rw-r--r--. 1 blyth blyth  1821 Oct 29 09:04 SniperPtr.h
     4 -rw-r--r--. 1 blyth blyth  1562 Oct 29 09:04 SniperRunState.h
     4 -rw-r--r--. 1 blyth blyth  1185 Oct 29 09:04 SniperTimer.h
     4 -rw-r--r--. 1 blyth blyth   477 Oct 29 09:04 SniperTimerSvc.h
     4 -rw-r--r--. 1 blyth blyth  1155 Oct 29 09:04 SvcBase.h
     4 -rw-r--r--. 1 blyth blyth   939 Oct 29 09:04 SvcFactory.h
     4 -rw-r--r--. 1 blyth blyth  2372 Oct 29 09:04 Task.h
     4 -rw-r--r--. 1 blyth blyth  2282 Oct 29 09:04 TaskWatchDog.h
     4 -rw-r--r--. 1 blyth blyth  1171 Oct 29 09:04 ToolBase.h
     4 -rw-r--r--. 1 blyth blyth   957 Oct 29 09:04 ToolFactory.h
     4 -rw-r--r--. 1 blyth blyth  1759 Oct 29 09:04 TopTask.h
     4 -rw-r--r--. 1 blyth blyth  1830 Oct 29 09:04 Workflow.h
    N[blyth@localhost sniper]$ 
    N[blyth@localhost sniper]$ 





* https://juno.ihep.ac.cn/trac/changeset/5228/offline




N[blyth@localhost junotop]$ l sniper/InstallArea/include/SniperKernel/Shared*
ls: cannot access sniper/InstallArea/include/SniperKernel/Shared*: No such file or directory
N[blyth@localhost junotop]$ 






[ 27%] Generating src/BTestEventBDict.cxx, src/BTestEventBDict.rootmap, src/BTestEventBDict_rdict.pcm
[ 27%] Generating src/TestHeaderADict.cxx, src/TestHeaderADict.rootmap, src/TestHeaderADict_rdict.pcm
[ 27%] Generating src/ClusterInfoEventDict.cxx, src/ClusterInfoEventDict.rootmap, src/ClusterInfoEventDict_rdict.pcm
[ 27%] Linking CXX shared library ../../../lib/libCalibUnit.so
Warning in <Unimplemented pragma statement - it has no effect: %s
>: CLHEP::HepLorentzVectorall_function at /data/blyth/junotop/offline/DataModel/Dict/CLHEPDict/src/CLHEPIncLinkDef.h:10:54

Error at line 1 - too many ( in function prototype!
function at /data/blyth/junotop/offline/DataModel/Dict/CLHEPDict/src/CLHEPIncLinkDef.h:69:69

Warning in <Unimplemented pragma statement - it has no effect: %s
>: HepMCoff at /data/blyth/junotop/offline/DataModel/GenEventV2/src/GenEventLinkDef.h:5:27

Warning in <Unimplemented pragma statement - it has no effect: %s
>: HepMCoff at /data/blyth/junotop/offline/DataModel/GenEventV2/src/GenHeaderLinkDef.h:5:27

[ 27%] Linking CXX shared library ../../../lib/libTopTracker.so




172 function run-build() {
173     local installdir=$(install-dir)
174     local blddir=$(build-dir)
175     check-build-dir
176     check-install-dir
177 
178     pushd $blddir
179 
180     cmake .. $(check-var-enabled graphviz) \
181              $(check-var-enabled withoec) \
182              -DCMAKE_CXX_STANDARD=17 \
183              -DCMAKE_BUILD_TYPE=$(cmake-build-type) \
184              -DCMAKE_INSTALL_PREFIX=$installdir \
185                      || error: "ERROR Found during cmake stage. "
186 
187     make || error: "ERROR Found during make stage. "
188     make install || error: "ERROR Found during make install stage. "
189 
190     popd
191 }
i

143 function install-dir() {
144     local installdir=${JUNO_OFFLINE_SOURCE_DIR}/InstallArea
145 
146     # allow users to override the directory name of blddir
147     if [ -n "$JUNO_OFFLINE_INSTALLDIR" ]; then
148         installdir=${JUNO_OFFLINE_INSTALLDIR}
149     fi
150 
151     echo $installdir
152 }





N[blyth@localhost junoenv]$ vi junoenv-sniper.sh 
N[blyth@localhost junoenv]$ 
N[blyth@localhost junoenv]$ bash junoenv sniper
= The junoenv is in /data/blyth/junotop/junoenv
= main
= THE JUNOTOP is /data/blyth/junotop
= THE JUNOENVDIR is /data/blyth/junotop/junoenv
== setup-juno-basic-preq: ================================================================
== setup-juno-basic-preq: GLOBAL Environment Variables:
== setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
== setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs"
== setup-juno-basic-preq: $JUNOARCHIVEGET: ""
== setup-juno-basic-preq: $JUNOARCHIVEURL: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
== setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
== setup-juno-basic-preq: ================================================================
== setup-juno-sniper
=== junoenv-sniper: 0
=== junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.1.tar.gz
=== junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.tar.gz
==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.1.tar.gz
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:--  0:00:53 --:--:--     0




cd /tmp
curl -L -O https://github.com/SNiPER-Framework/sniper/archive/v2.1.tar.gz
mv v2.1.tar.gz sniper-v2.1.tar.gz



j-sniper-curl-scp(){

   : workaround GFW firewall github blockage 
   local msg="=== $FUNCNAME :"

   . $JUNOTOP/junoenv/junoenv-sniper.sh 
   local version=$(junoenv-sniper-version)
   local url=$(junoenv-sniper-url $version)
   local base=$(basename $url)
   local name=sniper-$base

   cd /tmp
   [ ! -f "$name" ] && curl -L $url && mv $base $name 
   local cmd="scp $name P:junotop/"

   echo $msg url $url 
  
   echo $cmd 
   eval $cmd 
}



N[blyth@localhost junoenv]$ l  /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/
total 152
 0 drwxrwxr-x. 6 blyth blyth    87 Dec  4 01:01 ..
 4 drwxr-xr-x. 2 blyth blyth  4096 Dec  4 01:01 .
 4 -rw-r--r--. 1 blyth blyth  2004 Oct 29 09:04 AlgBase.h
 4 -rw-r--r--. 1 blyth blyth   957 Oct 29 09:04 AlgFactory.h
 4 -rw-r--r--. 1 blyth blyth  2918 Oct 29 09:04 DataBuffer.h
 4 -rw-r--r--. 1 blyth blyth  1382 Oct 29 09:04 DataMemSvc.h
 4 -rw-r--r--. 1 blyth blyth  1390 Oct 29 09:04 DeclareDLE.h
 4 -rw-r--r--. 1 blyth blyth  2639 Oct 29 09:04 DLElement.h
 4 -rw-r--r--. 1 blyth blyth  2106 Oct 29 09:04 DleSupervisor.h
 4 -rw-r--r--. 1 blyth blyth  2825 Oct 29 09:04 ExecUnit.h
 4 -rw-r--r--. 1 blyth blyth   910 Oct 29 09:04 IDataBlock.h
 4 -rw-r--r--. 1 blyth blyth  1488 Oct 29 09:04 IIncidentHandler.h
 4 -rw-r--r--. 1 blyth blyth  2217 Oct 29 09:04 Incident.h
 4 -rw-r--r--. 1 blyth blyth  1903 Oct 29 09:04 JSONParser.h
 4 -rw-r--r--. 1 blyth blyth  1550 Oct 29 09:04 NamedElement.h
 8 -rw-r--r--. 1 blyth blyth  4274 Oct 29 09:04 Property.h
 4 -rw-r--r--. 1 blyth blyth  2936 Oct 29 09:04 PropertyMgr.h
 4 -rw-r--r--. 1 blyth blyth  2207 Oct 29 09:04 RefBase.h
 4 -rw-r--r--. 1 blyth blyth  1872 Oct 29 09:04 SniperContext.h
 4 -rw-r--r--. 1 blyth blyth  2399 Oct 29 09:04 SniperDataPtr.h
 4 -rw-r--r--. 1 blyth blyth  1530 Oct 29 09:04 SniperException.h
 4 -rw-r--r--. 1 blyth blyth  1484 Oct 29 09:04 Sniper.h
12 -rw-r--r--. 1 blyth blyth 10660 Oct 29 09:04 SniperJSON.h
 4 -rw-r--r--. 1 blyth blyth  2600 Oct 29 09:04 SniperLog.h
 4 -rw-r--r--. 1 blyth blyth  1821 Oct 29 09:04 SniperPtr.h
 4 -rw-r--r--. 1 blyth blyth  1562 Oct 29 09:04 SniperRunState.h
 4 -rw-r--r--. 1 blyth blyth  1185 Oct 29 09:04 SniperTimer.h
 4 -rw-r--r--. 1 blyth blyth   477 Oct 29 09:04 SniperTimerSvc.h
 4 -rw-r--r--. 1 blyth blyth  1155 Oct 29 09:04 SvcBase.h
 4 -rw-r--r--. 1 blyth blyth   939 Oct 29 09:04 SvcFactory.h
 4 -rw-r--r--. 1 blyth blyth  2372 Oct 29 09:04 Task.h
 4 -rw-r--r--. 1 blyth blyth  2282 Oct 29 09:04 TaskWatchDog.h
 4 -rw-r--r--. 1 blyth blyth  1171 Oct 29 09:04 ToolBase.h
 4 -rw-r--r--. 1 blyth blyth   957 Oct 29 09:04 ToolFactory.h
 4 -rw-r--r--. 1 blyth blyth  1759 Oct 29 09:04 TopTask.h
 4 -rw-r--r--. 1 blyth blyth  1830 Oct 29 09:04 Workflow.h
N[blyth@localhost junoenv]$ 



/data/blyth/junotop/mt.sniper/build /data/blyth/junotop/mt.sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
-- cmake version 3.21.2
-- The CXX compiler identification is GNU 8.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found Python: /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8 (found suitable version "3.8.12", minimum required is "3.8.12") found components: Interpreter 
-- Found SNiPER: /data/blyth/junotop/sniper/InstallArea/lib64/cmake/SNiPER/SNiPERConfig.cmake (Required is at least version "2.1") 
CMake Error at CMakeLists.txt:13 (find_package):
  By not providing "FindTBB.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "TBB", but
  CMake did not find one.

  Could not find a package configuration file provided by "TBB" (requested
  version 2020.0) with any of the following names:

    TBBConfig.cmake
    tbb-config.cmake

  Add the installation prefix of "TBB" to CMAKE_PREFIX_PATH or set "TBB_DIR"
  to a directory containing one of the above files.  If "TBB" provides a
  separate development package or SDK, be sure it has been installed.


-- Configuring incomplete, errors occurred!
See also "/data/blyth/junotop/mt.sniper/build/CMakeFiles/CMakeOutput.log".
N[blyth@localhost junoenv]$ 
N[blyth@localhost junoenv]$ 


[ 68%] Building CXX object Detector/Geometry/CMakeFiles/Geometry.dir/src/RecGeomSvc.cc.o
[ 68%] Building CXX object Examples/CorAnalysis/CMakeFiles/CorAnalysis.dir/src/CorBuildAlg.cc.o
[ 70%] Built target GenTools
In file included from /data/blyth/junotop/offline/Utilities/MtUtilities/src/FillGlobalBuffer.cc:1:
/data/blyth/junotop/offline/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
 #include "SniperMuster/GlobalStream.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
In file included from /data/blyth/junotop/offline/Utilities/MtUtilities/src/PruneGlobalBuffer.cc:1:
/data/blyth/junotop/offline/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
 #include "SniperMuster/GlobalStream.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
/data/blyth/junotop/offline/Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:3:34: warning: extra tokens at end of #include directive
 #include "G4PhysicalConstants.hh"`
                                  ^
In file included from /data/blyth/junotop/offline/Utilities/MtUtilities/src/MtNavBufferMgr.cc:1:
/data/blyth/junotop/offline/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
 #include "SniperMuster/GlobalStream.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [Utilities/MtUtilities/CMakeFiles/MtUtilities.dir/src/FillGlobalBuffer.cc.o] Error 1
make[2]: *** Waiting for unfinished jobs....
make[2]: *** [Utilities/MtUtilities/CMakeFiles/MtUtilities.dir/src/PruneGlobalBuffer.cc.o] Error 1





bash junoenv env resetup
   scrubs the opticks hookup

bash junoenv opticks hookup 
    puts it back 





Hi Simon,

Jiaheng had updated the SNiPER and there are incompatible interfaces compared to the previous version. So you need to "svn update" junoenv and re-install the TBB, sniper and mt.sniper. 
If you could use the CVMFS, please use following JUNOTOP:

    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x
Sorry for the inconvenience. 
Tao




N[blyth@localhost junoenv]$ echo $JUNO_EXTLIB_OLDTOP
/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs
N[blyth@localhost junoenv]$ gip JUNO_EXTLIB_OLDTOP
/home/blyth/.bashrc:export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs
/home/blyth/j/j.bash:     28     export JUNO_EXTLIB_OLDTOP=$(reuse-junotop)/ExternalLibs
/home/blyth/j/j.bash:    797     # = check the environment variable $JUNO_EXTLIB_OLDTOP =
/home/blyth/j/j.bash:    798     if [ -z "$JUNO_EXTLIB_OLDTOP" ];
/home/blyth/j/j.bash:    800         echo $msg Please set the ENVIRONMENT VARIABLE called \$JUNO_EXTLIB_OLDTOP first1>&2
/home/blyth/j/j.bash:    803     if [ ! -d "$JUNO_EXTLIB_OLDTOP" ];
/home/blyth/j/j.bash:    805         echo $msg The \$JUNO_EXTLIB_OLDTOP \"$JUNO_EXTLIB_OLDTOP\" does not exist.
/home/blyth/j/j.bash:    811     local oldpath=$JUNO_EXTLIB_OLDTOP/$(juno-ext-libs-${pkg}-name)/$(juno-ext-libs-${pkg}-version)
/home/blyth/j/j.bash:        plants symbolic links for ExternalLibs assuming JUNO_EXTLIB_OLDTOP points to the dir
/home/blyth/j/j.bash:    export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs 
/home/blyth/j/j.bash:   [ -z "$JUNO_EXTLIB_OLDTOP" ]   && echo $FUNCNAME requires envvar JUNO_EXTLIB_OLDTOP && return 1
/home/blyth/j/j.bash:   [ ! -d "$JUNO_EXTLIB_OLDTOP" ] && echo $FUNCNAME requires directory JUNO_EXTLIB_OLDTOP $JUNO_EXTLIB_OLDTOP  && return 2
N[blyth@localhost junoenv]$ 



So update JUNO_EXTLIB_OLDTOP

 40 #export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs
 41 export JUNO_EXTLIB_OLDTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs
 42 

N[blyth@localhost ~]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/tbb/2020.3/
total 5
1 drwxr-xr-x. 4 cvmfs cvmfs   80 Jan  5 17:48 .
2 -rw-r--r--. 1 cvmfs cvmfs 1029 Jan  5 17:48 bashrc
1 drwxr-xr-x. 3 cvmfs cvmfs  195 Jan  5 17:48 lib
2 -rw-r--r--. 1 cvmfs cvmfs 1442 Jan  5 17:48 tcshrc
1 drwxr-xr-x. 3 cvmfs cvmfs   28 Jan  5 17:45 ..
1 drwxr-xr-x. 4 cvmfs cvmfs   43 Jan  5 10:08 include
N[blyth@localhost ~]$ 




963     # check dir first
964 
965     echo $msg command: $cmd
966     echo $msg packages: $packages
967     local pkgver=""
968     for pkgver in $packages
969     do
970         # using @ to seperate pkg anv ver.
971         local pkgverarr=($(echo $pkgver | tr "@" "\n"))
972         local pkg=${pkgverarr[0]}
973         local ver=${pkgverarr[1]}
974         # create version function first
975         is_list_mode || echo $msg create function juno-ext-libs-${pkg}-version- to override default
976         if [ -n "$ver" ]; then
977             juno-ext-libs-create-PKG-version $pkg $ver
978         fi
979         # check the initial status
980         is_list_mode || echo $msg juno-ext-libs-check-init $pkg
981         juno-ext-libs-check-init $pkg || exit $?
982         # check whether the library is reused or not.
983         is_list_mode || echo $msg juno-ext-libs-check-is-reused $pkg
984         juno-ext-libs-check-is-reused $pkg || is_list_mode || continue
985         is_list_mode || echo $msg juno-ext-libs-$cmd $pkg
986         juno-ext-libs-$cmd $pkg
987     done
988 
989 }



249 function juno-ext-libs-check-is-reused {
250     local msg="==== $FUNCNAME: "
251     # just check the install prefix is a soft link or not
252     local pkg=$1
253     local newpath=$(juno-ext-libs-${pkg}-install-dir)
254     if [[ -L "$newpath" && -d "$newpath" ]];
255     then
256         echo $msg The installation prefix for $pkg: \"$newpath\" is a soft link. 1>&2
257         echo $msg It can be a reused library. 1>&2
258         return 1
259     else
260         return 0
261     fi
262 }



How to update a reuse... 


N[blyth@localhost ExternalLibs]$ cd tbb
N[blyth@localhost tbb]$ l
total 4
4 drwxrwxr-x. 37 blyth blyth 4096 Mar  2 17:41 ..
0 drwxrwxr-x.  2 blyth blyth   21 Dec  4 00:55 .
0 lrwxrwxrwx.  1 blyth blyth   95 Dec  4 00:55 2019_U8 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/tbb/2019_U8
N[blyth@localhost tbb]$ pwd
/data/blyth/junotop/ExternalLibs/tbb


N[blyth@localhost ExternalLibs]$ l Cmake/
total 4
0 drwxrwxr-x.  5 blyth blyth   69 Mar  2 17:46 3.22.1
0 drwxrwxr-x.  3 blyth blyth   34 Mar  2 17:42 .
4 drwxrwxr-x. 37 blyth blyth 4096 Mar  2 17:41 ..
0 lrwxrwxrwx.  1 blyth blyth   96 Dec  4 00:55 3.21.2 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/Cmake/3.21.2
N[blyth@localhost ExternalLibs]$ l tbb/
total 4
4 drwxrwxr-x. 37 blyth blyth 4096 Mar  2 17:41 ..
0 drwxrwxr-x.  2 blyth blyth   21 Dec  4 00:55 .
0 lrwxrwxrwx.  1 blyth blyth   95 Dec  4 00:55 2019_U8 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J21v2r0-branch/ExternalLibs/tbb/2019_U8
N[blyth@localhost ExternalLibs]$ 


N[blyth@localhost junoenv]$ bash junoenv libs reuse cmake
= The junoenv is in /data/blyth/junotop/junoenv
= main
= THE JUNOTOP is /data/blyth/junotop
= THE JUNOENVDIR is /data/blyth/junotop/junoenv
== setup-juno-basic-preq: ================================================================
== setup-juno-basic-preq: GLOBAL Environment Variables:
== setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
== setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
== setup-juno-basic-preq: $JUNOARCHIVEGET: ""
== setup-juno-basic-preq: $JUNOARCHIVEURL: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
== setup-juno-basic-preq: $CMTEXTRATAGS: ""
== setup-juno-basic-preq: ================================================================
== setup-juno-external-libs
=== junoenv-external-libs: command: reuse
=== junoenv-external-libs: packages: cmake
=== junoenv-external-libs: create function juno-ext-libs-cmake-version- to override default
=== junoenv-external-libs: juno-ext-libs-check-init cmake
==== juno-ext-libs-check-init: setup dependencies for cmake
==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: create function juno-ext-libs-cmake-version- to override default
==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: source /data/blyth/junotop/junoenv/packages/cmake.sh
==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: After source: cmake
=== junoenv-external-libs: juno-ext-libs-check-is-reused cmake
=== junoenv-external-libs: juno-ext-libs-reuse cmake
==== juno-ext-libs-reuse: cmake oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Cmake/3.22.1
==== juno-ext-libs-reuse: cmake newpath: /data/blyth/junotop/ExternalLibs/Cmake/3.22.1
N[blyth@localhost junoenv]$ 


N[blyth@localhost junoenv]$ bash junoenv libs reuse tbb
= The junoenv is in /data/blyth/junotop/junoenv
= main
= THE JUNOTOP is /data/blyth/junotop
= THE JUNOENVDIR is /data/blyth/junotop/junoenv
== setup-juno-basic-preq: ================================================================
== setup-juno-basic-preq: GLOBAL Environment Variables:
== setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
== setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
== setup-juno-basic-preq: $JUNOARCHIVEGET: ""
== setup-juno-basic-preq: $JUNOARCHIVEURL: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
== setup-juno-basic-preq: $CMTEXTRATAGS: ""
== setup-juno-basic-preq: ================================================================
== setup-juno-external-libs
=== junoenv-external-libs: command: reuse
=== junoenv-external-libs: packages: tbb
=== junoenv-external-libs: create function juno-ext-libs-tbb-version- to override default
=== junoenv-external-libs: juno-ext-libs-check-init tbb
==== juno-ext-libs-check-init: setup dependencies for tbb
==== juno-ext-libs-dependencies-setup-rec-impl: # setup tbb: create function juno-ext-libs-tbb-version- to override default
==== juno-ext-libs-dependencies-setup-rec-impl: # setup tbb: source /data/blyth/junotop/junoenv/packages/tbb.sh
==== juno-ext-libs-dependencies-setup-rec-impl: # setup tbb: After source: tbb
==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: create function juno-ext-libs-cmake-version- to override default
==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: source /data/blyth/junotop/junoenv/packages/cmake.sh
==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: After source: cmake
==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: status: 0 cmake
==== juno-ext-libs-dependencies-setup-rec-impl: ## setup cmake: source /data/blyth/junotop/ExternalLibs/Cmake/3.22.1/bashrc
=== junoenv-external-libs: juno-ext-libs-check-is-reused tbb
=== junoenv-external-libs: juno-ext-libs-reuse tbb
==== juno-ext-libs-reuse: tbb oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/tbb/2020.3
==== juno-ext-libs-reuse: tbb newpath: /data/blyth/junotop/ExternalLibs/tbb/2020.3
N[blyth@localhost junoenv]$ 




Delete all the symbolic lihk dirs in ExternalLibs


 jlibs_reusei





[ 62%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/HepEvt2HepMC.cc.o
In file included from /data/blyth/junotop/offline/Utilities/MtUtilities/src/FillGlobalBuffer.cc:1:
/data/blyth/junotop/offline/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
 #include "SniperMuster/GlobalStream.h"
          ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compilation terminated.
make[2]: *** [Utilities/MtUtilities/CMakeFiles/MtUtilities.dir/src/FillGlobalBuffer.cc.o] Error 1
make[1]: *** [Utilities/MtUtilities/CMakeFiles/MtUtilities.dir/all] Error 2
make[1]: *** Waiting for unfinished jobs....
[ 62%] Building CXX object Simulation/GenTools/CMakeFiles/GenTools.dir/src/PostGenTools.cc.o
[ 62%] Building CXX object Examples/RawAnalysis/CMakeFiles/RawAnalysis.dir/src/RawEvtAnalysis.cc.o
In file included from /data/blyth/junotop/offline/Utilities/InputReviser/src/InputReviser.cc:1:
/data/blyth/junotop/offline/Utilities/InputReviser/InputReviser/InputReviser.h:17:2





[ 50%] Built target SniperMuster
[100%] Built target MtIOExample
Install the project...
-- Install configuration: ""
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/share/mt.sniper/setup.sh
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster/GlobalBuffer.h
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster/GlobalStream.h
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster/GlobalStream4Any.h
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster/GlobalStreamBase.h
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/include/SniperMuster/ThreadAssistor.h
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/python/SniperMuster/libSniperMuster.so
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/python/SniperMuster
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/python/SniperMuster/__init__.py
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/share/run-MusterTest.py
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/lib64/libMtIOExample.so
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/python/MtIOExample.py
-- Up-to-date: /data/blyth/junotop/mt.sniper/InstallArea/share/run-MtIO.py
/data/blyth/junotop/mt.sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
/data/blyth/junotop/mt.sniper/InstallArea /data/blyth/junotop/mt.sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
/data/blyth/junotop/mt.sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
/data/blyth/junotop /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
N[blyth@localhost junoenv]$ 
N[blyth@localhost junoenv]$ 


