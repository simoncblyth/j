oj_client/shakdown.rst : building JUNOSW against Client Opticks
================================================================


clean OpticksClient build
-------------------------------

::

    lo_client
    o
    om-cleaninstall


clean OJ build againt OpticksClient : "ljclient ljbb0c"
---------------------------------------------------------

::

    ljclient ljbb0c


update OJ build against OpticksClient without geometry init
----------------------------------------------------------------

::

    ljclient ljbb0




runtime
--------

Use ENVSET from lo to check pointing at the desired installation, then::

    ljrt
    EVTMAX=100 ljrt



TODO : test client OJ build on lxlogin - non-GPU node
------------------------------------------------------



Issue 0 : improve "Found CURL" logging : not so easy
-----------------------------------------------------

::

    -- Custom4_LIBRARY_PATH  : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so 
    -- Custom4_LIBRARIES     : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4 
    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- Found CURL: /usr/lib64/libcurl.so (found suitable version "7.76.1", minimum required is "7.76.1")
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : PLog_INCLUDE_DIR :/data1/blyth/local/opticks_Client/externals/plog/include 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_TARGET   :Opticks::G4CX 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_FOUND    :YES 
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : Opticks_FOUND:YES
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : ENV{OPTICKS_PREFIX}:/data1/blyth/local/opticks_Client
    Found libonnxruntime /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3/lib64/libonnxruntime.so




Issue 1 : reldir inconsistency
---------------------------------

Issue 2 : WITH_G4CXOPTICKS signalling : fail to find things like CURL were hidden
----------------------------------------------------------------------------------------

::

    321 bool DetSim0Svc::initializeOpticks()
    322 {
    323     dumpOpticks("DetSim0Svc::initializeOpticks");
    324     assert( m_opticksMode > 0);
    325 
    326 #ifdef WITH_G4CXOPTICKS
    327     // TODO: arrange logging setup earlier than this 
    328     OPTICKS_ELOG("DetSim0Svc_CXOK");
    329     OK_PMTSIM_LOG_(0) ;
    330     OK_PHYSISIM_LOG_(0) ;
    331 #else
    332     LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS " << std::endl ;
    333     assert(0);
    334 #endif
    335     return true ;
    336 }



::

    [2026-04-27 11:19:26,494] p3288108 {/home/blyth/junosw/InstallArea/Client_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/python/Tutorial/JUNOApplication.py:222} INFO - JUNOApplication.run toptask.run
    junotoptask.find                WARN: Cann't find Object InputSvc
    junotoptask.find                WARN: Cann't find Object OutputSvc
    IDMapping Service is initializing!
    junotoptask:PMTParamSvc.init_IDService  INFO: CD LPMT Num: 17612	CD SPMT Num: 25600	WP LPMT Num: 2400	WP ATM LPMT Num: 348	WP ATM MPMT Num: 600	WP WAL PMT Num: 5
    junotoptask:PMTParamSvc.init_PMT_R  INFO: CD LPMT Mean R: 19433.93164 mm	CD SPMT Mean R: 19384.00000 mm
    junotoptask:PMTParamSvc.init_PMT_R  INFO: CD LPMT Mean R: 19433.93164 mm (unshifted)	CD SPMT Mean R: 19384.00000 mm  (unshifted)
    junotoptask:PMTParamSvc.initialize  INFO:   0 (kPMT_NNVT) :   4710
      1 (kPMT_Hamamatsu) :   4955
      2 (kPMT_HZC) :  25600
      3 (kPMT_NNVT_HighQE) :  10700
      4 (kPMT_DYB8inch) :    600

    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/data/Detector/Geometry/TopTracker/CrossTalk.txt
    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/data/Detector/Geometry/TopTracker/ChannelPosition.txt
    junotoptask:PMTSimParamSvc.initialize  INFO: PMTSimParamSvc is initializing!
    junotoptask:PMTSimParamSvc.initialize  INFO: db_type: File
    junotoptask:PMTSimParamSvc.init_default  INFO: Retrieve PMTParamSvc successfully.
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.Dynode.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/Dynode/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.MCP.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/MCP/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.WP_PMT.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/WP_PMT/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.DYB8inch.CE will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/DYB8inch/CE
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.HZC_3inch.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/HZC_3inch/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.WP_PMT.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/WP_PMT/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.ARC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/ARC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.ARC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/ARC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.PHC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/PHC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.PHC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/PHC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.ARC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/ARC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.ARC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/ARC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.PHC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/PHC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.PHC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/PHC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.ARC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/ARC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.ARC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/ARC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.PHC_RINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/PHC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.PHC_KINDEX will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/PHC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.DYB8inch.QE_shape will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/DYB8inch/QE_shape
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.THICKNESS will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/THICKNESS
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.THICKNESS will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/THICKNESS
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.THICKNESS will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/THICKNESS
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.R12860.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/R12860/scale
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP/scale
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.NNVTMCP_HiQE.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/scale
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.DYB8inch.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/DYB8inch/scale
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.HZC_3inch.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/HZC_3inch/scale
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: PMTProperty.WP_PMT.scale will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/DetSim/PMTProperty/WP_PMT/scale
    junotoptask:PMTSimParamSvc.init_PMTParamSvc  INFO: m_PmtTotal_WP: 2400
    junotoptask:PMTSimParamSvc.init_PMTParamSvc  INFO: m_PmtTotal_WP_ATM_lpmt: 348
    junotoptask:PMTSimParamSvc.init_PMTParamSvc  INFO: m_PmtTotal_WP_ATM_mpmt: 600
    junotoptask:PMTSimParamSvc.init_PMTParamSvc  INFO: m_PmtTotal_WP_WAL_pmt: 5
    junotoptask:PMTSimParamSvc.init_file_common_LPMT  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    junotoptask:PMTSimParamSvc.init_file_common_LPMT_MCP  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT_model.root
    junotoptask:PMTSimParamSvc.init_file_CD_SPMT  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
    junotoptask:PMTSimParamSvc.init_file_common_LPMT  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_WP_LPMT.root
    junotoptask:PMTSimParamSvc.init_file_common_LPMT  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_WP_ATM_LPMT.root
    junotoptask:PMTSimParamSvc.init_file_WP_ATM_MPMT  INFO: Loading 8inch MPMT parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_WP_MPMT.root
    junotoptask:PMTSimParamSvc.init_file_WP_ATM_MPMT  INFO: 8inch MPMT [0]: PMT ID=53000 PDE=24.36000% (will be /100.00000) TTS=2.89000 DCR=1.38000
    junotoptask:PMTSimParamSvc.init_file_WP_ATM_MPMT  INFO: 8inch MPMT [1]: PMT ID=53001 PDE=24.95000% (will be /100.00000) TTS=2.75000 DCR=0.57000
    junotoptask:PMTSimParamSvc.init_file_WP_ATM_MPMT  INFO: 8inch MPMT [2]: PMT ID=53002 PDE=24.82000% (will be /100.00000) TTS=2.66600 DCR=0.72000
    junotoptask:PMTSimParamSvc.init_file_WP_ATM_MPMT  INFO: Loaded 600 8inch MPMT PMTs 
    junotoptask:PMTSimParamSvc.init_file_common_LPMT  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_WP_WAL_LPMT.root
    PMTSimParamSvc::descTotal
     m_PmtTotal (CD-LPMT)            17612
     pd_vector.size (CD+WP LPMT)     20365
     m_PmtTotal_SPMT                 25600
     pd_map_SPMT.size                25600
     m_PmtTotal_WP_ATM_mpmt          600
     pd_map_WP_ATM_MPMT.size         600
     m_PmtTotal_WP                   2400
     m_PmtTotal_ALL                  46565
     m_all_pmtID.size                46565
     pd_vector (CD_LPMT) beginIdx:   0 pmtid: 0
     pd_vector (CD_LPMT) endIdx:     17611 pmtid: 17611
     pd_vector (WP_LPMT) startIdx:   17612 pmtid: 50000
     pd_vector (WP_LPMT) endIdx:     20011 pmtid: 52399
     pd_vector (WP_ATM_LPMT) startIdx: 20012 pmtid: 52400
     pd_vector (WP_ATM_LPMT) endIdx:   20359 pmtid: 52747
     pd_vector (WP_WAL_PMT) startIdx: 20360 pmtid: 54000
     pd_vector (WP_WAL_PMT) endIdx:   20364 pmtid: 54004
     m_all_pmtID (CD_LPMT) beginIdx: 0 pmtid: 0
     m_all_pmtID (CD_LPMT) endIdx:   17611 pmtid: 17611
     m_all_pmtID (WP_LPMT) startIdx: 17612 pmtid: 50000
     m_all_pmtID (WP_LPMT) endIdx:   20011 pmtid: 52399
     m_all_pmtID (WP_ATM_LPMT) startIdx: 20012 pmtid: 52400
     m_all_pmtID (WP_ATM_LPMT) endIdx:   20359 pmtid: 52747
     m_all_pmtID (WP_WAL_PMT) startIdx: 20360 pmtid: 54000
     m_all_pmtID (WP_WAL_PMT) endIdx:   20364 pmtid: 54004
     m_all_pmtID (CD_SPMT) beginIdx: 20365 pmtid: 20000
     m_all_pmtID (CD_SPMT) endIdx:   45964 pmtid: 45599
     m_all_pmtID (WP_ATM_MPMT) startIdx: 45965 pmtid: 53599
     m_all_pmtID (WP_ATM_MPMT) endIdx:   46564 pmtid: 53540
     m_all_pmt_catvec.size()         46565


    junotoptask:PMTSimParamSvc.initialize  INFO: Initialize CD-LPMT sPE histograms from file: 
    junotoptask:PMTSimParamSvc.Load_APData  INFO: Loading afterpulse data from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/dbdata/offline-data/Simulation/SimSvc/PMTSimParamSvc/AfterPulseParam.root
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 1 **NOT** WITH_G4CXOPTICKS 
    junotoptask:DetSim0Svc.initializeOpticks ERROR:  FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS 
    python: /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:333: bool DetSim0Svc::initializeOpticks(): Assertion `0' failed.
     *** Break *** abort



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 2 (Thread 0x7f43929ff640 (LWP 3288118) "python"):
    #0  0x00007f43bca8722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f43bca8996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f43bd04df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f43bd350f38 <_PyRuntime+440>, cond=0x7f43bd350f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x1dae1a0) at Python/ceval_gil.h:231




Looking back at the log::

    -- Custom4_CMAKE_PATH    : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8/Custom4Config.cmake 
    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- CUSTOM4_LIBRARIES   : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4
    -- Found Python: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bin/python (found suitable version "3.11.10", minimum required is "3.11.10") found components: Interpreter
    CMake Warning at cmake/legacy/JUNODependencies.cmake:173 (find_package):
      No "FindOpticks.cmake" found in CMAKE_MODULE_PATH.
    Call Stack (most recent call first):
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)


    CMake Warning (dev) at cmake/legacy/JUNODependencies.cmake:173 (find_package):
      FindOpticks.cmake must either be part of this project itself, in this case
      adjust CMAKE_MODULE_PATH so that it points to the correct location inside
      its source tree.

      Or it must be installed by a package which has already been found via
      find_package().  In this case make sure that package has indeed been found
      and adjust CMAKE_MODULE_PATH to contain the location where that package has
      installed FindOpticks.cmake.  This must be a location provided by that
      package.  This error in general means that the buildsystem of this project
      is relying on a Find-module without ensuring that it is actually available.

    Call Stack (most recent call first):
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)
    This warning is for project developers.  Use -Wno-dev to suppress it.

    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : Opticks_FOUND:0
    Found libonnxruntime /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3/lib64/libonnxruntime.so
    -- Using ROOT::EGPythia6 from ROOT
    -- MKL library not found. MKL support will be disabled.
    XOD_PREFIX: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/XmlObjDesc
    -- Using default package lists





FindOpticks.cmake::

    #[=[
    FindOpticks.cmake
    ===================

    Hmm: could keep the G4OK internal/implicit for simplicity as do not need 
    the flexibility to access other "COMPONENTS" currently. 

    Testing this from ~/opticks/examples/UseOpticks/go.sh 


    opticks/cmake/Modules/FindOpticks.cmake used from offline/cmake/JUNODependencies.cmake::

        ## Opticks
        if(DEFINED ENV{OPTICKS_PREFIX})
           set(Opticks_VERBOSE YES)
           set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{OPTICKS_PREFIX}/cmake/Modules")
           find_package(Opticks QUIET MODULE)
           message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
        endif()

    Then subsequently packages needing Opticks headers must add dependency line::

        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}> 


    #]=]

    set(Opticks_MODULE  "${CMAKE_CURRENT_LIST_FILE}")
    include(GNUInstallDirs)
    set(OPTICKS_PREFIX $ENV{OPTICKS_PREFIX})

    if(Opticks_VERBOSE)
        message(STATUS "${Opticks_MODULE} : Opticks_VERBOSE     : ${Opticks_VERBOSE} ")
        message(STATUS "${Opticks_MODULE} : ENV(OPTICKS_PREFIX) : $ENV{OPTICKS_PREFIX} ")
        message(STATUS "${Opticks_MODULE} : OPTICKS_PREFIX      : ${OPTICKS_PREFIX} ")

        foreach(_dir ${CMAKE_MODULE_PATH})
            message(STATUS "${Opticks_MODULE} : CMAKE_MODULE_PATH _dir : ${_dir} ")
        endforeach() 

        set(_prefix_list)
        string(REPLACE ":" ";" _prefix_list $ENV{CMAKE_PREFIX_PATH})
        foreach(_prefix ${_prefix_list})
            message(STATUS "${Opticks_MODULE} : CMAKE_PREFIX_PATH _prefix : ${_prefix} ")
        endforeach() 
    endif()

    #find_package(G4OK CONFIG QUIET)
    find_package(G4CX CONFIG QUIET)

    if(G4CX_FOUND)
        add_compile_definitions(WITH_G4CXOPTICKS)
        #add_compile_definitions(WITH_G4CXOPTICKS_DEBUG)

        if(Opticks_VERBOSE)
            message(STATUS "${Opticks_MODULE} : PLog_INCLUDE_DIR :${PLog_INCLUDE_DIR} ")
        endif()
        include_directories(${PLog_INCLUDE_DIR})  ## WHY NOT AUTOMATIC ? Maybe because plog is header only ?




Fixed above issue by adding the cmake/Modules to what the opticks build installs into prefix, but smth no correct with the find
----------------------------------------------------------------------------------------------------------------------------------

::

    -- Custom4_CMAKE_DIR     : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64/Custom4-0.1.8 
    -- CUSTOM4_LIBRARIES   : -L/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/lib64 -lCustom4
    -- CUSTOM4_DEFINITIONS : -DWITH_CUSTOM4
    -- CUSTOM4_CFLAGS      : -I/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/include/Custom4
    -- Found Python: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bin/python (found suitable version "3.11.10", minimum required is "3.11.10") found components: Interpreter
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_VERBOSE     : YES 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : ENV(OPTICKS_PREFIX) : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : OPTICKS_PREFIX      : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /home/blyth/junosw/cmake/legacy/Modules/ 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/cmake/modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_MODULE_PATH _dir : /data1/blyth/local/opticks_Client/cmake/Modules 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/mt.sniper/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/healpix/3.83 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libmore/0.8.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gemini/juno_master_20260408 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gibuu/r2023_02_juno 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/talys/1.95 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/nuwro/21.09.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/genie/3.04.02 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HepMC/2.06.11 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/xrootd/5.7.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/CLHEP/2.4.7.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/tbb/2020.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pythia6/6.4.28 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/LHAPDF/6.3.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libxml2/2.9.12 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/log4cpp/1.1.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HDF5/1.14.3 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/frontier/2.10.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pacparser/1.4.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-cpp/1.1.12 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-c/6.1.9 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/eigen/3.4.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/fftw3/3.3.10 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Xercesc/3.2.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libyaml/0.2.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-numpy/1.26.4 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-cython/3.0.8 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-pip/23.3.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-setuptools/69.5.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Cmake/3.30.5 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/git-lfs/3.4.1 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Git/2.46.2 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client/externals 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/opticks.ihep.ac.cn/external/OptiX_800 
    -- cmake/Modules/OpticksCUDAFlags.cmake : using default OPTICKS_CUDA_NVCC_DIALECT variable c++17
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_TARGET   : 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_FOUND    :NO 
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : Opticks_FOUND:NO
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : ENV{OPTICKS_PREFIX}:/data1/blyth/local/opticks_Client
    Found libonnxruntime /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3/lib64/libonnxruntime.so
    -- Using ROOT::EGPythia6 from ROOT
    -- MKL library not found. MKL support will be disabled.
    XOD_PREFIX: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/junosw/XmlObjDesc
    -- Using default package lists
    Package XmlObjDesc: no target found. 
    -- EDMUtil will use addition files: src/BookEDM.cc;src/EDMManager.cc;src/InputElementKeeper.cc;src/InputFileManager.cc;src/JunoEDMDefinitions.cc;src/PassiveStream.cc;src/RootFileInter.cc;src/SmartRefTable.cc;src/SmartRefTableImpl.cc
    EDM EDMUtil will not use XOD
    EDM CLHEPDict will not use XOD



FindOpticks.cmake must have failed to find G4CX
---------------------------------------------------

::

     47 #find_package(G4OK CONFIG QUIET)
     48 find_package(G4CX CONFIG QUIET)
     49 
     50 if(G4CX_FOUND)
     51     add_compile_definitions(WITH_G4CXOPTICKS)
     52     #add_compile_definitions(WITH_G4CXOPTICKS_DEBUG)
     53 
     54     if(Opticks_VERBOSE)
     55         message(STATUS "${Opticks_MODULE} : PLog_INCLUDE_DIR :${PLog_INCLUDE_DIR} ")
     56     endif()
     57     include_directories(${PLog_INCLUDE_DIR})  ## WHY NOT AUTOMATIC ? Maybe because plog is header only ?
     58 
     59     set(Opticks_TARGET "Opticks::G4CX")
     60     set(Opticks_FOUND "YES")
     61 
     62 else()
     63     set(Opticks_FOUND "NO")
     64 endif()



Debug vs Client
~~~~~~~~~~~~~~~~

::

    (ok) A[blyth@localhost opticks]$ l /data1/blyth/local/opticks_Debug/lib64/cmake/g4cx/
    total 32
    4 drwxr-xr-x.  2 blyth blyth 4096 Apr 23 15:25 .
    4 drwxr-xr-x. 10 blyth blyth 4096 Apr 23 15:25 ..
    4 -rw-r--r--.  1 blyth blyth  336 Apr 23 15:25 g4cx-config.cmake
    4 -rw-r--r--.  1 blyth blyth 2762 Apr 23 15:25 g4cx-config-version.cmake
    8 -rw-r--r--.  1 blyth blyth 4172 Apr 23 15:25 g4cx-targets.cmake
    4 -rw-r--r--.  1 blyth blyth  819 Apr 23 15:25 g4cx-targets-debug.cmake
    4 -rw-r--r--.  1 blyth blyth  606 Apr 23 15:25 properties-g4cx-targets.cmake
    (ok) A[blyth@localhost opticks]$ 


    (ok) A[blyth@localhost opticks]$ l /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/
    total 32
    4 drwxr-xr-x. 8 blyth blyth 4096 Apr 23 19:04 ..
    4 drwxr-xr-x. 2 blyth blyth 4096 Apr 23 16:23 .
    4 -rw-r--r--. 1 blyth blyth  335 Apr 23 16:22 g4cx-config.cmake
    8 -rw-r--r--. 1 blyth blyth 4168 Apr 23 16:22 g4cx-targets.cmake
    4 -rw-r--r--. 1 blyth blyth  819 Apr 23 16:22 g4cx-targets-debug.cmake
    4 -rw-r--r--. 1 blyth blyth  606 Apr 23 16:22 properties-g4cx-targets.cmake
    4 -rw-r--r--. 1 blyth blyth 2762 Apr 23 16:22 g4cx-config-version.cmake
    (ok) A[blyth@localhost opticks]$ 




::

    (ok) A[blyth@localhost g4cx]$ cat /data1/blyth/local/opticks_Debug/lib64/cmake/g4cx/g4cx-config.cmake

    # PROJECT_NAME G4CX
    # TOPMATTER


    include(CMakeFindDependencyMacro)
    # Library: Opticks::CSG
    find_dependency(CSG)
    # Library: Opticks::U4
    find_dependency(U4)
    # Library: Opticks::CSGOptiX
    find_dependency(CSGOptiX)

    include("${CMAKE_CURRENT_LIST_DIR}/g4cx-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/properties-g4cx-targets.cmake")
    (ok) A[blyth@localhost g4cx]$ 
    (ok) A[blyth@localhost g4cx]$ 



    (ok) A[blyth@localhost g4cx]$ cat /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/g4cx-config.cmake

    # PROJECT_NAME G4CX
    # TOPMATTER


    include(CMakeFindDependencyMacro)
    # Library: Opticks::CSG
    find_dependency(CSG)
    # Library: Opticks::U4
    find_dependency(U4)
    # Library: CURL::libcurl
    find_dependency(CURL 8.12.1)

    include("${CMAKE_CURRENT_LIST_DIR}/g4cx-targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/properties-g4cx-targets.cmake")
    (ok) A[blyth@localhost g4cx]$ 
    (ok) A[blyth@localhost g4cx]$ 





::


    Removing the QUIET I see other problems than CURL::
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /data1/blyth/local/opticks_Client/externals 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : CMAKE_PREFIX_PATH _prefix : /cvmfs/opticks.ihep.ac.cn/external/OptiX_800 
    -- cmake/Modules/OpticksCUDAFlags.cmake : using default OPTICKS_CUDA_NVCC_DIALECT variable c++17
    CMake Warning at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package):
      By not providing "FindNLJSON.cmake" in CMAKE_MODULE_PATH this project has
      asked CMake to find a package configuration file provided by "NLJSON", but
      CMake did not find one.

      Could not find a package configuration file provided by "NLJSON" with any
      of the following names:

        NLJSONConfig.cmake
        nljson-config.cmake

      Add the installation prefix of "NLJSON" to CMAKE_PREFIX_PATH or set
      "NLJSON_DIR" to a directory containing one of the above files.  If "NLJSON"
      provides a separate development package or SDK, be sure it has been
      installed.
    Call Stack (most recent call first):
      /data1/blyth/local/opticks_Client/lib64/cmake/sysrap/sysrap-config.cmake:26 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package)
      /data1/blyth/local/opticks_Client/lib64/cmake/csg/csg-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package)
      /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/g4cx-config.cmake:8 (find_dependency)
      /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake:49 (find_package)
      cmake/legacy/JUNODependencies.cmake:173 (find_package)
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)


    CMake Warning at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package):
      Found package configuration file:

        /data1/blyth/local/opticks_Client/lib64/cmake/sysrap/sysrap-config.cmake

      but it set SysRap_FOUND to FALSE so package "SysRap" is considered to be
      NOT FOUND.  Reason given by package:

      SysRap could not be found because dependency NLJSON could not be found.

    Call Stack (most recent call first):
      /data1/blyth/local/opticks_Client/lib64/cmake/csg/csg-config.cmake:8 (find_dependency)
      /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package)
      /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/g4cx-config.cmake:8 (find_dependency)
      /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake:49 (find_package)
      cmake/legacy/JUNODependencies.cmake:173 (find_package)
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)


    CMake Warning at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Cmake/3.30.5/share/cmake-3.30/Modules/CMakeFindDependencyMacro.cmake:76 (find_package):
      Found package configuration file:

        /data1/blyth/local/opticks_Client/lib64/cmake/csg/csg-config.cmake

      but it set CSG_FOUND to FALSE so package "CSG" is considered to be NOT
      FOUND.  Reason given by package:

      CSG could not be found because dependency SysRap could not be found.

    Call Stack (most recent call first):
      /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/g4cx-config.cmake:8 (find_dependency)
      /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake:49 (find_package)
      cmake/legacy/JUNODependencies.cmake:173 (find_package)
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)


    CMake Warning at /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake:49 (find_package):
      Found package configuration file:

        /data1/blyth/local/opticks_Client/lib64/cmake/g4cx/g4cx-config.cmake

      but it set G4CX_FOUND to FALSE so package "G4CX" is considered to be NOT
      FOUND.  Reason given by package:

      G4CX could not be found because dependency CSG could not be found.

    Call Stack (most recent call first):
      cmake/legacy/JUNODependencies.cmake:173 (find_package)
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:55 (include)


    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_TARGET   : 
    -- /data1/blyth/local/opticks_Client/cmake/Modules/FindOpticks.cmake : Opticks_FOUND    :NO 
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : Opticks_FOUND:NO
    -- /home/blyth/junosw/cmake/legacy/JUNODependencies.cmake : ENV{OPTICKS_PREFIX}:/data1/blyth/local/opticks_Client
    Found libonnxruntime /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3/lib64/libonnxruntime.so




::

    (ok) A[blyth@localhost sysrap]$ l /data1/blyth/local/opticks_Debug/externals/include/nljson/
    total 916
    908 -rw-r--r--. 1 blyth blyth 926233 Jul  2  2025 json.hpp
      4 drwxr-xr-x. 2 blyth blyth   4096 Jul  2  2025 .
      4 drwxr-xr-x. 5 blyth blyth   4096 Jul  2  2025 ..
    (ok) A[blyth@localhost sysrap]$ l /data1/blyth/local/opticks_Client/externals/include/nljson/
    total 916
    908 -rw-r--r--. 1 blyth blyth 926233 Apr 23 16:21 json.hpp
      4 drwxr-xr-x. 2 blyth blyth   4096 Apr 23 16:21 .
      4 drwxr-xr-x. 5 blyth blyth   4096 Apr 23 16:21 ..
    (ok) A[blyth@localhost sysrap]$ 



I skipped the FindNLJSON.cmake::

    (ok) A[blyth@localhost sysrap]$ l  /data1/blyth/local/opticks_Client/cmake/Modules/
    total 100
     4 drwxr-xr-x. 2 blyth blyth 4096 Apr 27 14:47 .
     4 -rw-r--r--. 1 blyth blyth 2351 Apr 27 14:41 FindOpticks.cmake
     4 drwxr-xr-x. 3 blyth blyth 4096 Apr 27 14:02 ..
     8 -rw-r--r--. 1 blyth blyth 5043 Dec 10 11:19 OpticksCXXFlags.cmake
     4 -rw-r--r--. 1 blyth blyth 3301 Apr 22  2025 OpticksCUDAFlags.cmake
     4 -rw-r--r--. 1 blyth blyth 3558 Aug 29  2024 EchoTarget.cmake
     8 -rw-r--r--. 1 blyth blyth 5746 Aug 29  2024 FindG4.cmake
     4 -rw-r--r--. 1 blyth blyth 1194 Aug 29  2024 FindGLM.cmake
     4 -rw-r--r--. 1 blyth blyth 2014 Aug 29  2024 FindImGui.cmake
     8 -rw-r--r--. 1 blyth blyth 5593 Aug 29  2024 FindOpticksCUDA.cmake
     4 -rw-r--r--. 1 blyth blyth 1652 Aug 29  2024 FindOpticksGLEW.cmake
     8 -rw-r--r--. 1 blyth blyth 4282 Aug 29  2024 FindOpticksGLFW.cmake
     8 -rw-r--r--. 1 blyth blyth 7553 Aug 29  2024 FindOpticksXercesC.cmake
    12 -rw-r--r--. 1 blyth blyth 9467 Aug 29  2024 FindOptiX.cmake
     4 -rw-r--r--. 1 blyth blyth 1150 Aug 29  2024 FindPLog.cmake
     8 -rw-r--r--. 1 blyth blyth 4637 Aug 29  2024 OpticksBuildOptions.cmake
     4 -rw-r--r--. 1 blyth blyth 2452 Aug 29  2024 TopMetaTarget.cmake
    (ok) A[blyth@localhost sysrap]$ l  /data1/blyth/local/opticks_Debug/cmake/Modules/
    total 140
     4 drwxr-xr-x. 3 blyth blyth 4096 Apr 23 15:25 ..
     4 drwxr-xr-x. 2 blyth blyth 4096 Dec 10 11:19 .
     8 -rw-r--r--. 1 blyth blyth 5043 Dec 10 11:19 OpticksCXXFlags.cmake
     4 -rw-r--r--. 1 blyth blyth 3301 Apr 22  2025 OpticksCUDAFlags.cmake
     4 -rw-r--r--. 1 blyth blyth 3558 Aug 29  2024 EchoTarget.cmake
     4 -rw-r--r--. 1 blyth blyth  257 Aug 29  2024 EnvBuildOptions.cmake
     8 -rw-r--r--. 1 blyth blyth 5746 Aug 29  2024 FindG4.cmake
     4 -rw-r--r--. 1 blyth blyth 1194 Aug 29  2024 FindGLM.cmake
     4 -rw-r--r--. 1 blyth blyth 2014 Aug 29  2024 FindImGui.cmake
     4 -rw-r--r--. 1 blyth blyth  971 Aug 29  2024 FindNLJSON.cmake
     4 -rw-r--r--. 1 blyth blyth  461 Aug 29  2024 FindNonExisting.cmake
     4 -rw-r--r--. 1 blyth blyth 1863 Aug 29  2024 FindOpticksAssimp.cmake
     4 -rw-r--r--. 1 blyth blyth 2251 Aug 29  2024 FindOpticks.cmake
     8 -rw-r--r--. 1 blyth blyth 5593 Aug 29  2024 FindOpticksCUDA.cmake
     4 -rw-r--r--. 1 blyth blyth 1652 Aug 29  2024 FindOpticksGLEW.cmake
     8 -rw-r--r--. 1 blyth blyth 4282 Aug 29  2024 FindOpticksGLFW.cmake
     8 -rw-r--r--. 1 blyth blyth 5149 Aug 29  2024 FindOpticksOptiX.cmake
     8 -rw-r--r--. 1 blyth blyth 7553 Aug 29  2024 FindOpticksXercesC.cmake
    12 -rw-r--r--. 1 blyth blyth 9467 Aug 29  2024 FindOptiX.cmake
     4 -rw-r--r--. 1 blyth blyth 1150 Aug 29  2024 FindPLog.cmake
     8 -rw-r--r--. 1 blyth blyth 4637 Aug 29  2024 OpticksBuildOptions.cmake
     8 -rw-r--r--. 1 blyth blyth 6679 Aug 29  2024 OpticksCMakeTraverse.cmake
     8 -rw-r--r--. 1 blyth blyth 4123 Aug 29  2024 OpticksConfigureConfigScript.cmake
     4 -rw-r--r--. 1 blyth blyth 2452 Aug 29  2024 TopMetaTarget.cmake
    (ok) A[blyth@localhost sysrap]$ 




Issue 3 : Improve runtime logging : less verbose - more control - clearer whats happening
------------------------------------------------------------------------------------------- 

::

    BP=SEvt::addGenstep ljrt






::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-05-06 16:40:03.686 [junoSD_PMT_v2::Initialize eventID 0
    2026-05-06 16:40:03.687 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2026-05-06 16:40:03.689 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SProf::Write DISABLED, enable[export SProf__WRITE=1] disable[unset SProf__WRITE]
    SClientSimulator::simulate  eventID 0 reset 0 hc (6, 4, 4, ) dt 0.00376
    SClientSimulator::simulate  eventID 0 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder NO  eph_meta -
    [SProcessHits_EPH::desc
                                     ProcessHits_count              0              0.000000    /M 
                                      ProcessHits_true              0              0.000000    /M 
                                     ProcessHits_false              0              0.000000    /M 
                                     SaveNormHit_count              0              0.000000    /M 
                                     SaveMuonHit_count              0              0.000000    /M 
                                             EPH_UNSET              0              0.000000    /M 
                                              EPH_NDIS              0              0.000000    /M 
                                              EPH_NOPT              0              0.000000    /M 
                                             EPH_NEDEP              0              0.000000    /M 
                                            EPH_NBOUND              0              0.000000    /M 
                                             EPH_NPROC              0              0.000000    /M 
                                           EPH_NDETECT              0              0.000000    /M 
                                           EPH_NDECULL              0              0.000000    /M 
                                            EPH_YMERGE              0              0.000000    /M 
                                             EPH_YSAVE              0              0.000000    /M 
                                          EPH_SAVENORM              0              0.000000    /M 
                                          EPH_SAVEMUON              0              0.000000    /M 

                Initialize_G4HCofThisEvent_opticksMode              1              0.000001    /M 
                      Initialize_G4HCofThisEvent_count              1              0.000001    /M 
                           EndOfEvent_Simulate_eventID              0              0.000000    /M 
                             EndOfEvent_Simulate_count              0              0.000000    /M 

                          EndOfEvent_Simulate_EGPU_hit              0              0.000000    /M 
                     EndOfEvent_hitCollection_entries0              0              0.000000    /M 
                     EndOfEvent_hitCollection_entries1              6              0.000006    /M 
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries1              0              0.000000    /M 

                      EndOfEvent_Simulate_merged_count              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_count              0              0.000000    /M 
                        SUM_merged_count_savehit_count              0              0.000000    /M 

                      EndOfEvent_Simulate_merged_total              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_total              0              0.000000    /M 
                        SUM_merged_total_savehit_total              0              0.000000    /M 

    SProcessHits_EPH::NOTES
    ------------------------

    ProcessHits_count
    ProcessHits_true
    ProcessHits_false
        number of calls to *SProcessHits_EPH::add* and sub-counts where is_hit is true/false,
        done from junoSD_PMT_v2::ProcessHits

    SaveNormHit_count
    SaveMuonHit_count
        counts collected from junoSD_PMT_v2::SaveNormHit junoSD_PMT_v2::SaveMuonHit

    All 7 EndOfEvent_Simulate values are collected from junoSD_PMT_v2_Opticks::EndOfEvent_Simulate

    EndOfEvent_Simulate_EGPU_hit
        Opticks GPU num_hit returned from SEvt::GetNumHit_EGPU() immediately following G4CXOpticks::simulate call

    EndOfEvent_Simulate_merged_count
    EndOfEvent_Simulate_savehit_count
        The sum of merged_count and savehit_count should sum to EGPU_hit in opticksMode:1

    EndOfEvent_Simulate_merged_total
    EndOfEvent_Simulate_savehit_total
        The totals sum over all events

    EndOfEvent_hitCollection_entries0
    EndOfEvent_hitCollection_entries1
    EndOfEvent_hitCollectionAlt_entries0
    EndOfEvent_hitCollectionAlt_entries1
        entries into hitCollection and hitCollectionAlt before and after the
        call to junoSD_PMT_v2_Opticks::EndOfEvent.
        This is recorded from junoSD_PMT_v2::EndOfEvent.

        In all cases entries0 are expected to be zero with entries1
        for the active collection matching the savehit_count

        For opticksMode:1 only hitCollection should be active,
        it contains the GPU originated hits.

        For opticksMode:3 both hitCollection and hitCollectionAlt should
        be active with hitCollection containing CPU hits and
        hitCollectionAlt containing GPU hits.

    ]SProcessHits_EPH::desc

    2026-05-06 16:40:03.753 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 6 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 08:40:03.753352000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 08:40:03.778193000Z
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 90.80800 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 90.80700 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.24600        1.24600      0.00000      
    DetSimAlg                1           92.96900       92.96900     0.00784      
    Sum of junotoptask       1           94.21900       94.21900     0.02021      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1







::

    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-05-06 17:11:04.077 [junoSD_PMT_v2::Initialize eventID 0
    2026-05-06 17:11:04.079 ]junoSD_PMT_v2::Initialize eventID 0

    Begin of Event --> 0
    2026-05-06 17:11:04.080 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SProf::Write DISABLED, enable[export SProf__WRITE=1] disable[unset SProf__WRITE]
    SClientSimulator::simulate  eventID 0 reset 0 hc (6, 4, 4, ) dt 0.00261
    SClientSimulator::simulate  eventID 0 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.105 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 6 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.105648000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.132120000Z
    end of event action 


    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    2026-05-06 17:11:04.132 [junoSD_PMT_v2::Initialize eventID 1
    2026-05-06 17:11:04.133 ]junoSD_PMT_v2::Initialize eventID 1
    Begin of Event --> 1
    2026-05-06 17:11:04.134 [junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 1 reset 0 hc (6, 4, 4, ) dt 0.00317
    SClientSimulator::simulate  eventID 1 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.142 ]junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 1 hitCollection 6 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.142134000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.142317000Z
    end of event action 

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (2) 
    2026-05-06 17:11:04.142 [junoSD_PMT_v2::Initialize eventID 2
    2026-05-06 17:11:04.142 ]junoSD_PMT_v2::Initialize eventID 2
    Begin of Event --> 2
    2026-05-06 17:11:04.143 [junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 2 reset 0 hc (20, 4, 4, ) dt 0.00279
    SClientSimulator::simulate  eventID 2 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.151 ]junoSD_PMT_v2::EndOfEvent eventID 2 opticksMode 1 hitCollection 20 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.151082000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.151230000Z
    end of event action 


    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (3) 
    2026-05-06 17:11:04.151 [junoSD_PMT_v2::Initialize eventID 3
    2026-05-06 17:11:04.151 ]junoSD_PMT_v2::Initialize eventID 3
    Begin of Event --> 3
    2026-05-06 17:11:04.152 [junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 3 reset 0 hc (28, 4, 4, ) dt 0.00625
    SClientSimulator::simulate  eventID 3 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.163 ]junoSD_PMT_v2::EndOfEvent eventID 3 opticksMode 1 hitCollection 28 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.163197000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.163378000Z
    end of event action 

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (4) 
    2026-05-06 17:11:04.163 [junoSD_PMT_v2::Initialize eventID 4
    2026-05-06 17:11:04.164 ]junoSD_PMT_v2::Initialize eventID 4
    Begin of Event --> 4
    2026-05-06 17:11:04.165 [junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 4 reset 0 hc (33, 4, 4, ) dt 0.00450
    SClientSimulator::simulate  eventID 4 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.174 ]junoSD_PMT_v2::EndOfEvent eventID 4 opticksMode 1 hitCollection 33 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.174718000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.174875000Z
    end of event action 


    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (5) 
    2026-05-06 17:11:04.174 [junoSD_PMT_v2::Initialize eventID 5
    2026-05-06 17:11:04.175 ]junoSD_PMT_v2::Initialize eventID 5
    Begin of Event --> 5
    2026-05-06 17:11:04.176 [junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 5 reset 0 hc (35, 4, 4, ) dt 0.00455
    SClientSimulator::simulate  eventID 5 match_settings YES client_settings [HitCompOneName:hit,PhotonCompOneName:photon] server_settings [HitCompOneName:hit,PhotonCompOneName:photon] match_digest YES client_digest [79f17049c1f5806abe058cf4449eb712] server_digest [79f17049c1f5806abe058cf4449eb712]
    2026-05-06 17:11:04.185 ]junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 1 hitCollection 35 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-05-06 09:11:04.185540000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-05-06 09:11:04.185679000Z
    end of event action 

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (6) 
    2026-05-06 17:11:04.185 [junoSD_PMT_v2::Initialize eventID 6
    2026-05-06 17:11:04.186 ]junoSD_PMT_v2::Initialize eventID 6
    Begin of Event --> 6
    2026-05-06 17:11:04.186 [junoSD_PMT_v2::EndOfEvent eventID 6 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SClientSimulator::simulate  eventID 6 reset 0 hc (37, 4, 4, ) dt 0.00524






