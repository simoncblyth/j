precision-offline-build
===========================



::

    # Now trying [cmt make] in /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt (88/133)
    ...
    #CMT---> (constituents.make) RecWpMuonAlgcompile done
    #CMT---> (constituents.make) Starting RecWpMuonAlginstall
    #CMT---> building static library ../Linux-x86_64/libRecWpMuonAlg.a
    #CMT---> building shared library ../Linux-x86_64/libRecWpMuonAlg.so
    RecWpMuonAlgtemp_shlib/RecDummyWpTool.o: In function `RecDummyWpTool::reconstruct(RecTrks*)':
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecDummyWpTool.h:33: undefined reference to `RecTrks::addTrk(TVector3, TVector3, double, double, double, double, int)'
    RecWpMuonAlgtemp_shlib/RecWpMuonAlg.o: In function `RecWpMuonAlg::execute()':
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:123: undefined reference to `RecTrks::RecTrks()'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:128: undefined reference to `RecTrks::size()'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:130: undefined reference to `RecTrks::getStart(int)'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:131: undefined reference to `RecTrks::getEnd(int)'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:132: undefined reference to `RecTrks::getITime(int)'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:133: undefined reference to `RecTrks::getOTime(int)'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:137: undefined reference to `RecTrks::getQuality(int)'
    /data/blyth/junotop/offline/Reconstruction/RecWpMuonAlg/cmt/../src/RecWpMuonAlg.cc:138: undefined reference to `RecTrks::getNPE(int)'
    collect2: error: ld returned 1 exit status
    gmake[2]: *** [../Linux-x86_64/libRecWpMuonAlg.so] Error 1
    gmake[1]: *** [RecWpMuonAlginstall] Error 2
    gmake: *** [all] Error 2
    #CMT---> Error: execution failed : make
    #CMT---> Error: execution error : cmt make
    /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    O[blyth@localhost junoenv]$ 



    O[blyth@localhost junoenv]$ jgr RecTrks
    ./Reconstruction/LsqMuonRecTool/src/LsqMuonRecTool.cc:LsqMuonRecTool::reconstruct(RecTrks* trks){
    ./Reconstruction/LsqMuonRecTool/src/LsqMuonRecTool.h:    bool reconstruct(RecTrks*);
    ./Reconstruction/PoolMuonRecTool/src/PoolMuonRecTool.cc:PoolMuonRecTool::reconstruct(RecTrks* trks)
    ./Reconstruction/PoolMuonRecTool/src/PoolMuonRecTool.h:        bool reconstruct(RecTrks*); 
    ./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h:class RecTrks {
    ./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h:		RecTrks();
    ./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h:		~RecTrks();
    ./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h:        virtual bool reconstruct( RecTrks* ) = 0; 
    ./Reconstruction/RecCdMuonAlg/src/RecCdMuonAlg.cc:	  RecTrks* trks = new RecTrks();
    ./Reconstruction/RecCdMuonAlg/src/RecDummyTool.h:        bool reconstruct(RecTrks*) ;
    ./Reconstruction/RecCdMuonAlg/src/RecDummyTool.h:RecDummyTool::reconstruct(RecTrks* trks){
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:RecTrks::RecTrks() {}
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:RecTrks::~RecTrks() {}
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:int RecTrks::size() {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:TVector3 RecTrks::getStart(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:TVector3 RecTrks::getEnd(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:double RecTrks::getNPE(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:double RecTrks::getQuality(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:double RecTrks::getITime(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:double RecTrks::getOTime(int id) {
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:int RecTrks::getClusterNum(int id){
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc:void RecTrks::addTrk(TVector3 st, TVector3 ed, double it, double ot, double npe, double qua, int cluster_num) {
    ./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h:class RecTrks {
    ./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h:    RecTrks();
    ./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h:    ~RecTrks();
    ./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h:        virtual bool reconstruct( RecTrks* ) = 0; 
    ./Reconstruction/RecWpMuonAlg/src/RecWpMuonAlg.cc:    RecTrks* trks = new RecTrks();
    ./Reconstruction/RecWpMuonAlg/src/RecDummyWpTool.h:        bool reconstruct(RecTrks*) ;
    ./Reconstruction/RecWpMuonAlg/src/RecDummyWpTool.h:RecDummyWpTool::reconstruct(RecTrks* trks){
    ./Reconstruction/BundleRecByChargeTool/src/BundleRecTool.cc:bool BundleRecTool::reconstruct(RecTrks* trks){
    ./Reconstruction/BundleRecByChargeTool/src/BundleRecTool.h:            bool reconstruct(RecTrks*) ;
    ./Reconstruction/SpmtMuonRecTool/src/SpmtMuonRecTool.cc:SpmtMuonRecTool::reconstruct(RecTrks* trks)
    ./Reconstruction/SpmtMuonRecTool/src/SpmtMuonRecTool.h:        bool reconstruct(RecTrks*); 
    ./Reconstruction/ConeMuonRecTool/src/ConeMuonRecTool.cc:ConeMuonRecTool::reconstruct(RecTrks* trks)
    ./Reconstruction/ConeMuonRecTool/src/ConeMuonRecTool.h:        bool reconstruct(RecTrks*); 
    ./InstallArea/include/RecWpMuonAlg/IReconTool.h:class RecTrks {
    ./InstallArea/include/RecWpMuonAlg/IReconTool.h:    RecTrks();
    ./InstallArea/include/RecWpMuonAlg/IReconTool.h:    ~RecTrks();
    ./InstallArea/include/RecWpMuonAlg/IReconTool.h:        virtual bool reconstruct( RecTrks* ) = 0; 
    O[blyth@localhost offline]$ 



Curious there is no RecTrks header::

    O[blyth@localhost offline]$ jcv RecTrks
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc


./InstallArea/include/RecWpMuonAlg/IReconTool.h::

     06 # Description:  reference RecCdMuonAlg
      7 =============================================================================*/
      8 #ifndef IRECONTOOL_H
      9 #define IRECONTOOL_H
     10 #include "RecWpMuonAlg/PmtProp.h"
     11 #include "RecWpMuonAlg/Params.h"
     12 #include "TVector3.h"
     13 #include <vector>
     14 #include <algorithm>
     15 
     16 struct Trk {
     17   TVector3 st;
     18   TVector3 ed;
     19   double nPE;
     20   double quality;
     21   double iTime;
     22   double oTime;
     23   int cluster;
     24 };
     25 
     26 class RecTrks {
     27   public:
     28     RecTrks();
     29     ~RecTrks();
     30     int size();
     31     TVector3 getStart(int);
     32     TVector3 getEnd(int);
     33     double getNPE(int);
     34     double getQuality(int);
     35     double getITime(int);
     36     double getOTime(int);
     37     int getClusterNum(int);
     38     void addTrk(TVector3, TVector3, double, double, double, double, int);
     39   private:
     40     std::vector<Trk> Trks;
     41 };
     42 
     43 namespace JM{
     44     class RecHeader;
     45 }
     46 class IReconTool
     47 {
     48     public:
     49 
     50         virtual bool reconstruct( RecTrks* ) = 0;
     51 
     52         virtual bool configure(const Params*, const PmtTable*) = 0;
     53 
     54         virtual ~IReconTool(){};
     55 };
     56 #endif



Hmm unhealthy lots of IReconTool.h::

  1 %a   "./InstallArea/include/RecCdMuonAlg/IReconTool.h" line 1
  2      "./InstallArea/include/RecTimeLikeAlg/IReconTool.h" line 0
  3      "./InstallArea/include/RecWpMuonAlg/IReconTool.h" line 0
  4      "./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h" line 0
  5      "./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h" line 0


    O[blyth@localhost offline]$ find . -name IReconTool.h
    ./Reconstruction/RecCdMuonAlg/RecCdMuonAlg/IReconTool.h
    ./Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h
    ./InstallArea/include/RecWpMuonAlg/IReconTool.h

    O[blyth@localhost offline]$ vi Reconstruction/RecWpMuonAlg/RecWpMuonAlg/IReconTool.h
    O[blyth@localhost offline]$ find . -name RecTrks.cc
    ./Reconstruction/RecCdMuonAlg/src/RecTrks.cc
    O[blyth@localhost offline]$ 


RecTrks reorg https://juno.ihep.ac.cn/trac/changeset/5170/offline



Clearer build also fails at same place
----------------------------------------

::

    O[blyth@localhost offline]$ rm -rf InstallArea
    O[blyth@localhost junoenv]$ bash junoenv offline


Try CMake
------------

::

    O[blyth@localhost junotop]$ l sniper/SniperRelease/cmt/setup.sh
    4 -rw-rw-r--. 1 blyth blyth 953 Jul  7 16:43 sniper/SniperRelease/cmt/setup.sh

    O[blyth@localhost junoenv]$ jt
    /data/blyth/junotop
    O[blyth@localhost junotop]$ mv sniper/SniperRelease/cmt/setup.sh sniper/SniperRelease/cmt/setup.sh_old



::

    je
    bash junoenv libs all cmake

    jt
    rm -rf sniper mt.sniper

    je
    bash junoenv sniper




sniper fails with the old ROOT so try jlibs on Precision
------------------------------------------------------------


Curiously dont get the same ROOT fail as on lxslc7. 
Carefully looking at the log there is an error but it doesnt stop jlibs.

::

    ...

    === junoenv-external-libs: juno-ext-libs-check-is-reused ROOT
    === junoenv-external-libs: juno-ext-libs-all ROOT
    ==== juno-ext-libs-get:
    [ROOT-conf] ===== juno-ext-libs-PKG-get: Download
    [ROOT-conf]   % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
    [ROOT-conf]                                  Dload  Upload   Total   Spent    Left  Speed
    100   339  100   339    0     0    901      0 --:--:-- --:--:-- --:--:--   901
    100   337  100   337    0     0    447      0 --:--:-- --:--:-- --:--:--   447
    100  176M  100  176M    0     0   807k      0  0:03:43  0:03:43 --:--:-- 1081k
    ==== juno-ext-libs-conf:
    [ROOT-conf] ===== juno-ext-libs-PKG-conf: Uncompress the root_v6.24.06.source.tar.gz
    [ROOT-conf] tar -C root-6.24.06 -zxvf root_v6.24.06.source.tar.gz
    [ROOT-conf] root-6.24.06/
    [ROOT-conf] root-6.24.06/.ci/
    [ROOT-conf] root-6.24.06/.ci/copy_headers.sh
    [ROOT-conf] root-6.24.06/.ci/format_script.sh
    [ROOT-conf] root-6.24.06/.ci/tidy_script.sh
    [ROOT-conf] root-6.24.06/.clang-format
    [ROOT-conf] root-6.24.06/.clang-tidy

    ...
    [ROOT-conf] -- Detecting CXX compile features
    [ROOT-conf] -- Detecting CXX compile features - done
    [ROOT-conf] -- Found Git: /data/blyth/junotop/ExternalLibs/Git/2.33.0/bin/git (found version "2.33.0") 
    [ROOT-conf] -- Looking for Python
    [ROOT-conf] -- Could NOT find Python3 (missing: Python3_NumPy_INCLUDE_DIRS NumPy) (found version "3.8.12")
    [ROOT-conf] -- Found GCC. Major version 8, minor version 3
    [ROOT-conf] -- Looking for pthread.h
    ...

    [ROOT-make] [ 80%] Linking CXX shared library ../../lib/libMathCore.so
    [ROOT-make] cd /data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/root-build/math/mathcore && /data/blyth/junotop/ExternalLibs/Cmake/3.21.2/bin/cmake -E cmake_link_script CMakeFiles/MathCore.dir/link.txt --verbose=1
    [ROOT-make] /opt/rh/devtoolset-8/root/usr/bin/c++ -fPIC  -std=c++17 -Wno-implicit-fallthrough -Wno-noexcept-type -pipe  -Wshadow -Wall -W -Woverloaded-virtual -fsigned-char -pthread -O3 -DNDEBUG  -Wl,--no-undefined -Wl,--hash-style="both" -shared -Wl,-soname,libMathCore.so -o ../../lib/libMathCore.so CMakeFiles/MathCore.dir/src/AdaptiveIntegratorMultiDim.cxx.o CMakeFiles/MathCore.dir/src/BasicMinimizer.cxx.o CMakeFiles/MathCore.dir/src/BinData.cxx.o CMakeFiles/MathCore.dir/src/BrentMethods.cxx.o CMakeFiles/MathCore.dir/src/BrentMinimizer1D.cxx.o CMakeFiles/MathCore.dir/src/BrentRootFinder.cxx.o CMakeFiles/MathCore.dir/src/ChebyshevPol.cxx.o CMakeFiles/MathCore.dir/src/DataRange.cxx.o CMakeFiles/MathCore.dir/src/Delaunay2D.cxx.o CMakeFiles/MathCore.dir/src/DistSampler.cxx.o CMakeFiles/MathCore.dir/src/DistSamplerOptions.cxx.o CMakeFiles/MathCore.dir/src/Factory.cxx.o CMakeFiles/MathCore.dir/src/FitConfig.cxx.o CMakeFiles/MathCore.dir/src/FitData.cxx.o CMakeFiles/MathCore.dir/src/FitResult.cxx.o CMakeFiles/MathCore.dir/src/FitUtil.cxx.o CMakeFiles/MathCore.dir/src/Fitter.cxx.o CMakeFiles/MathCore.dir/src/GaussIntegrator.cxx.o CMakeFiles/MathCore.dir/src/GaussLegendreIntegrator.cxx.o CMakeFiles/MathCore.dir/src/GenAlgoOptions.cxx.o CMakeFiles/MathCore.dir/src/GoFTest.cxx.o CMakeFiles/MathCore.dir/src/Integrator.cxx.o CMakeFiles/MathCore.dir/src/IntegratorOptions.cxx.o CMakeFiles/MathCore.dir/src/MersenneTwisterEngine.cxx.o CMakeFiles/MathCore.dir/src/MinimTransformFunction.cxx.o CMakeFiles/MathCore.dir/src/MinimizerOptions.cxx.o CMakeFiles/MathCore.dir/src/MinimizerVariableTransformation.cxx.o CMakeFiles/MathCore.dir/src/MixMaxEngineImpl17.cxx.o CMakeFiles/MathCore.dir/src/MixMaxEngineImpl240.cxx.o CMakeFiles/MathCore.dir/src/MixMaxEngineImpl256.cxx.o CMakeFiles/MathCore.dir/src/ParameterSettings.cxx.o CMakeFiles/MathCore.dir/src/PdfFuncMathCore.cxx.o CMakeFiles/MathCore.dir/src/ProbFuncMathCore.cxx.o CMakeFiles/MathCore.dir/src/QuantFuncMathCore.cxx.o CMakeFiles/MathCore.dir/src/RandomFunctions.cxx.o CMakeFiles/MathCore.dir/src/RanluxppEngineImpl.cxx.o CMakeFiles/MathCore.dir/src/RichardsonDerivator.cxx.o CMakeFiles/MathCore.dir/src/RootFinder.cxx.o CMakeFiles/MathCore.dir/src/SparseData.cxx.o CMakeFiles/MathCore.dir/src/SpecFuncCephes.cxx.o CMakeFiles/MathCore.dir/src/SpecFuncCephesInv.cxx.o CMakeFiles/MathCore.dir/src/SpecFuncMathCore.cxx.o CMakeFiles/MathCore.dir/src/StdEngine.cxx.o CMakeFiles/MathCore.dir/src/TComplex.cxx.o CMakeFiles/MathCore.dir/src/TKDTree.cxx.o CMakeFiles/MathCore.dir/src/TKDTreeBinning.cxx.o CMakeFiles/MathCore.dir/src/TMath.cxx.o CMakeFiles/MathCore.dir/src/TRandom.cxx.o CMakeFiles/MathCore.dir/src/TRandom1.cxx.o CMakeFiles/MathCore.dir/src/TRandom2.cxx.o CMakeFiles/MathCore.dir/src/TRandom3.cxx.o CMakeFiles/MathCore.dir/src/TRandomGen.cxx.o CMakeFiles/MathCore.dir/src/TStatistic.cxx.o CMakeFiles/MathCore.dir/src/UnBinData.cxx.o CMakeFiles/MathCore.dir/src/triangle.c.o CMakeFiles/MathCore.dir/src/VectorizedTMath.cxx.o CMakeFiles/G__MathCore.dir/G__MathCore.cxx.o  -Wl,-rpath,/data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/root-build/lib: ../../lib/libImt.so -lpthread ../../lib/libMultiProc.so ../../lib/libNet.so ../../lib/libRIO.so ../../lib/libThread.so ../../lib/libCore.so -lpthread 
    [ROOT-make] make[2]: Leaving directory `/data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/root-build'
    [ROOT-make] [ 80%] Built target MathCore
    [ROOT-make] make[1]: Leaving directory `/data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06/root-build'
    [ROOT-make] make: *** [all] Error 2
    [ROOT-make] /data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06 /data/blyth/junotop/ExternalLibs/Build/root-6.24.06 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [ROOT-make] /data/blyth/junotop/ExternalLibs/Build/root-6.24.06 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    ==== juno-ext-libs-install:
    [ROOT-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-ROOT-install-
    [ROOT-install] /data/blyth/junotop/ExternalLibs/Build/root-6.24.06/root-6.24.06 /data/blyth/junotop/ExternalLibs/Build/root-6.24.06 /data/blyth/junotop/ExternalLibs/Build /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    [ROOT-install] ===== juno-ext-libs-ROOT-conf-env-setup: GSL=/data/blyth/junotop/ExternalLibs/gsl/2.5
    [ROOT-install] ===== juno-ext-libs-ROOT-conf-env-setup: FFTW3=/data/blyth/junotop/ExternalLibs/fftw3/3.3.8
    [ROOT-install] ===== juno-ext-libs-ROOT-conf-env-setup: XRDSYS=/data/blyth/junotop/ExternalLibs/xrootd/5.3.1
    [ROOT-install] ===== juno-ext-libs-ROOT-conf-env-setup: TBB=/data/blyth/junotop/ExternalLibs/tbb/2019_U8
    [ROOT-install] ===== juno-ext-libs-ROOT-conf-env-setup: PKG_CONFIG_PATH=/data/blyth/junotop/ExternalLibs/sqlite3/3.35.5/lib/p




nuwro hunk error::

    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup ROOT: status: 0 ROOT
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup ROOT: source /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bashrc
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bashrc: line 29: /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bin/thisroot.sh: No such file or directory
    === junoenv-external-libs: juno-ext-libs-check-is-reused nuwro
    === junoenv-external-libs: juno-ext-libs-all nuwro
    ==== juno-ext-libs-get:
    [nuwro-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: nuwro_19.02.2.tar.gz already exists
    ==== juno-ext-libs-conf:
    [nuwro-conf] patching file Makefile
    [nuwro-conf] Hunk #1 FAILED at 19.
    [nuwro-conf] 1 out of 1 hunk FAILED -- saving rejects to file Makefile.rej
    [nuwro-conf] patching file src/mb_nce.cc
    [nuwro-conf] patching file src/nuwro2rootracker.cc
    [nuwro-conf] Reversed (or previously applied) patch detected!  Assume -R? [n] 
    [nuwro-conf] Apply anyway? [n] 
    [nuwro-conf] Skipping patch.
    [nuwro-conf] 1 out of 1 hunk ignored -- saving rejects to file src/nuwro2rootracker.cc.rej
    ==== juno-ext-libs-make:


Partial ROOT build::


    ction -Wno-unused-but-set-variable -Wno-reorder  -DVERSION=\"\" -c src/rew/reweight_to.cc -o src/rew/reweight_to.o
    [nuwro-make] g++ `/data/blyth/junotop/ExternalLibs/ROOT/6.22.08/bin/root-config --cflags` -std=c++0x -fPIC -O2  -I src -Wl,--no-as-needed -Wall -Wno-unused-variable -Wno-sign-compare -Wno-unused-function -Wno-unused-but-set-variable -Wno-reorder  -DVERSION=\"\" -c src/rew/reweight_along.cc -o src/rew/reweight_along.o
    [nuwro-make] src/dis/fragmentation.cc:1:9: fatal error: TMCParticle.h: No such file or directory
    [nuwro-make]  #include<TMCParticle.h>
    [nuwro-make]          ^~~~~~~~~~~~~~~
    [nuwro-make] compilation terminated.
    [nuwro-make] make: *** [src/dis/fragmentation.o] Error 1
    [nuwro-make] make: *** Waiting for unfinished jobs....
    [nuwro-make] In file included from src/dis/resevent2.cc:24:
    [nuwro-make] src/dis/resevent2.h:4:10: fatal error: TPythia6.h: No such file or directory
    [nuwro-make]  #include <TPythia6.h>
    [nuwro-make]           ^~~~~~~~~~~~
    [nuwro-make] compilation terminated.
    [nuwro-make] make: *** [src/dis/resevent2.o] Error 1
    [nuwro-make] src/dis/fragmentation_cc.cc:8:9: fatal error: TMCParticle.h: No such file or directory
    [nuwro-make]  #include<TMCParticle.h>
    [nuwro-make]          ^~~~~~~~~~~~~~~


libmore patch issue too::

    === junoenv-external-libs: juno-ext-libs-all libmore
    ==== juno-ext-libs-get:
    [libmore-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: more-0.8.3.tar.bz2 already exists
    ==== juno-ext-libs-conf:
    [libmore-conf] ===== juno-ext-libs-libmore-apply-patch: Apply Patch /data/blyth/junotop/junoenv/packages/patches/libmore-0.8.3.patch
    [libmore-conf] patching file more/Makefile.am
    [libmore-conf] Reversed (or previously applied) patch detected!  Assume -R? [n] 
    [libmore-conf] Apply anyway? [n] 
    [libmore-conf] Skipping patch.
    [libmore-conf] 1 out of 1 hunk ignored -- saving rejects to file more/Makefile.am.rej
    [libmore-conf] patching file more/io/fdstreambuf.cc
    [libmore-conf] Reversed (or previously applied) patch detected!  Assume -R? [n] 
    [libmore-conf] Apply anyway? [n] 
    [libmore-conf] Skipping patch.
    [libmore-conf] 2 out of 2 hunks ignored -- saving rejects to file more/io/fdstreambuf.cc.rej
    [libmore-conf] patching file more/io/fstream.cc
    [libmore-conf] Reversed (or previously applied) patch detected!  Assume -R? [n] 
    [libmore-conf] Apply anyway? [n] 



sniper build still failing with ROOT errors::

    [ 54%] Building CXX object Examples/CoreUsages/CMakeFiles/SniperCoreUsages.dir/src/SvcAndToolAlg.cc.o
    [ 55%] Building CXX object SniperPython/CMakeFiles/SniperPythonLib.dir/lib/PyDataStore.cc.o
    [ 56%] Building CXX object SniperPython/CMakeFiles/SniperPythonLib.dir/lib/PyDataStoreSvc.cc.o
    In file included from /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/TString.h:28,
                     from /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/TNamed.h:26,
                     from /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/TDirectory.h:24,
                     from /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/TDirectoryFile.h:25,
                     from /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/TFile.h:27,
                     from /data/blyth/junotop/sniper/SniperUtil/RootWriter/lib/RootWriter.cc:20:
    /data/blyth/junotop/ExternalLibs/ROOT/6.22.08/include/ROOT/RStringView.hxx:32:84: error: conflicting declaration of template 'template<class _CharT, class _Traits> using basic_string_view = std::experimental::__ROOT::basic_string_view<_CharT, _Traits>'
        using basic_string_view = ::std::experimental::basic_string_view<_CharT,_Traits>;
                                                                                        ^
    In file included from /opt/rh/devtoolset-8/root/usr/include/c++/8/bits/basic_string.h:48,
                     from /opt/rh/devtoolset-8/root/usr/include/c++/8/string:52,
                     from /data/blyth/junotop/sniper/SniperKernel/SniperKernel/SniperLog.h:21,
                     from /data/blyth/junotop/sniper/SniperKernel/SniperKernel/NamedElement.h:21,
                     from /data/blyth/junotop/sniper/SniperKernel/SniperKernel/DLElement.h:21,
                     from /data/blyth/junotop/sniper/SniperKernel/SniperKernel/SvcBase.h:21,
                     from /data/blyth/junotop/sniper/SniperUtil/RootWriter/RootWriter/RootWriter.h:21,
                     from /data/blyth/junotop/sniper/SniperUtil/RootWriter/lib/RootWriter.cc:18:
    /opt/rh/devtoolset-8/root/usr/include/c++/8/string_view:71:11: note: previous declaration 'template<class _CharT, class _Traits> class std::basic_string_view'
         class basic_string_view
               ^~~~~~~~~~~~~~~~~







