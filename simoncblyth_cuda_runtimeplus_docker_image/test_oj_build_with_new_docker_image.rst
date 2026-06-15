test_oj_build_with_new_docker_image
=====================================

::


     ~/sandbox/docker-mock-gitlab-ci.sh exec



    c1: warning: command-line option '-Wno-non-virtual-dtor' is valid for C++/ObjC++ but not for C
    cc1: warning: command-line option '-Woverloaded-virtual' is valid for C++/ObjC++ but not for C
    In file included from /junosw/Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:4,
                     from /junosw/Simulation/DetSimV2/G4Svc/src/IG4Svc.cc:1:
    /junosw/Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:4:10: fatal error: G4RunManager.hh: No such file or directory
        4 | #include "G4RunManager.hh"
          |          ^~~~~~~~~~~~~~~~~
    compilation terminated.
    gmake[2]: *** [Simulation/DetSimV2/G4Svc/CMakeFiles/G4SvcLib.dir/build.make:76: Simulation/DetSimV2/G4Svc/CMakeFiles/G4SvcLib.dir/src/IG4Svc.cc.o] Error 1
    gmake[1]: *** [CMakeFiles/Makefile2:7152: Simulation/DetSimV2/G4Svc/CMakeFiles/G4SvcLib.dir/all] Error 2
    gmake[1]: *** Waiting for unfinished jobs....
    /junosw/Utilities/cJSON/src/cJSON.c: In function 'cJSON_strcasecmp':



Some mixed up path before that::

    - Found ZLIB: /usr/lib64/libz.so (found version "1.2.11")
    -- Found GSL: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7/include (found version "2.7")
    Found ROOT: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libCore.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libImt.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libRIO.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libNet.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libHist.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libGraf.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libGraf3d.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libGpad.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libROOTDataFrame.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libTree.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libTreePlayer.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libRint.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libPostscript.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libMatrix.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libPhysics.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libMathCore.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libThread.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libMultiProc.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libROOTVecOps.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libEG.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libEve.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libGeom.so;/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libMathMore.so
    testing GEANT4_CFLAGS... -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic  -DG4MULTITHREADED -I/junosw/build/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV//cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/CLHEP/2.4.7.1/include
    -- CMAKE_CURRENT_LIST_FILE        : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4ConfigVersion.cmake        
    -- PACKAGE_FIND_NAME              : Custom4              
    -- PACKAGE_FIND_VERSION           :            
    -- PACKAGE_FIND_VERSION_MAJOR     : 0     
    -- PACKAGE_FIND_VERSION_MINOR     : 0     


::

      -DG4MULTITHREADED 
      -I/junosw/build/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV//cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/../include/Geant4 
      -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/CLHEP/2.4.7.1/include



cmake/legacy/JUNODependencies.cmake::

     72 ## Geant4
     73 find_package(Geant4 REQUIRED ui_all vis_all)
     74 include_directories($ENV{JUNO_EXTLIB_Geant4_HOME}/include/geant4)
     75 find_program(GEANT4_CONFIG_EXECUTABLE geant4-config
     76     PATHS $ENV{JUNO_EXTLIB_Geant4_HOME}/bin)
     77 execute_process(
     78     COMMAND ${GEANT4_CONFIG_EXECUTABLE} --cflags
     79     OUTPUT_VARIABLE GEANT4_CFLAGS
     80     OUTPUT_STRIP_TRAILING_WHITESPACE
     81 )
     82 # remove c++11 from command line
     83 string(REPLACE "-std=c++11" "" GEANT4_CFLAGS ${GEANT4_CFLAGS})
     84 message("testing GEANT4_CFLAGS... ${GEANT4_CFLAGS}")
     85 add_definitions(${GEANT4_CFLAGS})
     86 


::

    bash-5.1$ ls -alst $JUNO_EXTLIB_Geant4_HOME/include/Geant4/
    total 17106
    137 drwxr-xr-x.  3 975 975 139264 Oct 21  2024 .
      3 -rw-r--r--.  1 975 975   2534 Oct 21  2024 G4ASCIITree.hh
      3 -rw-r--r--.  1 975 975   2624 Oct 21  2024 G4ASCIITreeMessenger.hh
      4 -rw-r--r--.  1 975 975   3365 Oct 21  2024 G4ASCIITreeSceneHandler.hh
      3 -rw-r--r--.  1 975 975   2062 Oct 21  2024 G4ASCIITreeViewer.hh
      6 -rw-r--r--.  1 975 975   5334 Oct 21  2024 G4AdjointCrossSurfChecker.hh
      6 -rw-r--r--.  1 975 975   5662 Oct 21  2024 G4AdjointSteppingAction.hh
      6 -rw-r--r--.  1 975 975   5207 Oct 21  2024 G4AdjointTrackingAction.hh
      3 -rw-r--r--.  1 975 975   2835 Oct 21  2024 G4ArrowModel.hh
      3 -rw-r--r--.  1 975 975   2342 Oct 21  2024 G4AttFilterUtils.hh
      7 -rw-r--r--.  1 975 975   7093 Oct 21  2024 G4AttValueFilterT.hh
      7 -rw-r--r--.  1 975 975   7128 Oct 21  2024 G4AttributeFilterT.hh
      3 -rw-r--r--.  1 975 975   2897 Oct 21  2024 G4AxesModel.hh
      3 -rw-r--r--.  1 975 975   2886 Oct 21  2024 G4BoundingSphereScene.hh
      4 -rw-r--r--.  1 975 975   3297 Oct 21  2024 G4CallbackModel.hh
      3 -rw-r--r--.  1 975 975   2262 Oct 21  2024 G4DAWNFILE.hh











Somehow an absolute path is incorrectly assumed to be a relative one



::


    find_package(Geant4 REQUIRED)

    get_filename_component(Custom4_GEANT4_PREFIX "${Geant4_INCLUDE_DIR}/../.." ABSOLUTE) ## DUH : Geant4 does not provide PREFIX
    find_program(Custom4_GEANT4_CONFIG_BIN geant4-config PATHS ${Custom4_GEANT4_PREFIX}/bin)
    execute_process(
         COMMAND ${Custom4_GEANT4_CONFIG_BIN} --cflags
         OUTPUT_VARIABLE Custom4_GEANT4_CFLAGS                                   ## the cflags has the correct include directory
         OUTPUT_STRIP_TRAILING_WHITESPACE
        )   




Traced this to a bug in geant4-config : it does not handle default HOME=/
---------------------------------------------------------------------------

HOME was set to "/" because are using "--user" to use a host user within the 
container to avoid permission problems::

    180 docker_run()
    181 {
    182    : docker_run - starting container with mounts from host into container
    183    type $FUNCNAME
    184 
    185    info
    186 
    187    local dop=$(docker_opticks_prefix)
    188    : dop docker_opticks_prefix mount only needed for fast cycle debug
    189 
    190    local host_user_id="$(id -u):$(id -g)"
    191 
    192    docker run --rm -it \
    193       $(docker_run_opts) \
    194       --name $(docker_nam) \
    195       --user "$host_user_id" \
    196       -v /cvmfs/juno.ihep.ac.cn:/cvmfs/juno.ihep.ac.cn:ro \
    197       -v /cvmfs/opticks.ihep.ac.cn:/cvmfs/opticks.ihep.ac.cn:ro \
    198       -v $HOME/junosw:/junosw \
    199       -v $dop:$dop \
    200       $(docker_ref)
    201 
    202    docker ps -a
    203 }



From inside the container::

    bash-5.1$ which geant4-config            
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ readlink $(which geant4-config)
    bash-5.1$ readlink /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ pwd
    /junosw
    bash-5.1$ script=$(which geant4-config)
    bash-5.1$ echo $script 
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ echo ${script##/}
    cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ echo ${script##~}
    cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ echo $HOME
    /
    bash-5.1$ calldir=`pwd`
    bash-5.1$ echo $calldir/$script
    /junosw//cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4-config
    bash-5.1$ ls /juno/   
    ls: cannot access '/juno/': No such file or directory
    bash-5.1$ ls /junosw
    Analysis		CMakeLists.user.txt.template  DQM	   Detector	 Generator	OEC		RootIO	    XmlObjDesc	    build_Doc.sh	     oj_build_.log	     sample_detsim.root
    CMakeLists.default.txt	Calibration		      DataModel    Doc		 IADAnalysis	Production	Simulation  build	    build_RelWithDebInfo.sh  oj_initialize.sh	     sample_detsim_user.root
    CMakeLists.online.txt	Classification		      DataQuality  EventDisplay  InstallArea	RawDataIO	Utilities   build.sh	    cmake		     oj_initialize_debug.sh  setup.sh
    CMakeLists.txt		CommonSvc		      Database	   Examples	 InstallConfig	Reconstruction	Validation  build_Debug.sh  junorun		     python3.11.log
    bash-5.1$ export HOME=/junosw
    bash-5.1$ geant4-config --prefix
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bin/..





After HOME=/junosw workaround build completes inside the container
-----------------------------------------------------------------------


::

    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/XOD.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/RootDict.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNODependencies.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOOnlineDependencies.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOVersionDefinition.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOSetupScripts.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOCommonDefinitions.cmake
    -- Installing: /junosw/InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/lib64/cmake/junosw/JUNOInstallOfflineSetup.cmake


YEP, but thats just a plain build.sh run without the script generation and geometry conversion::

    A[blyth@localhost junosw]$ l InstallArea/blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/
    total 72
     0 drwxr-xr-x.   6 blyth blyth    92 Jun 15 10:51 .
     4 drwxr-xr-x.  97 blyth blyth  4096 Jun 15 10:51 include
    20 drwxr-xr-x.   3 blyth blyth 16384 Jun 15 10:51 lib64
     8 drwxr-xr-x. 129 blyth blyth  4096 Jun 15 10:51 python
     4 drwxr-xr-x.   2 blyth blyth  4096 Jun 15 10:51 bin
    16 -rw-r--r--.   1 blyth blyth 14839 Jun 15 10:39 setup.csh
    16 -rw-r--r--.   1 blyth blyth 14839 Jun 15 10:39 setup.sh
     4 drwxr-xr-x.  11 blyth blyth  4096 Jun 15 10:37 ..




