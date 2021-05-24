juno-opticks-validation
=========================

::

    export CMTEXTRATAGS=opticks      ## bash junoenv 
    jok-touchbuild- Simulation/DetSimV2/G4Opticks/cmt 

    jok-touchbuild- Examples/Tutorial/cmt
    # jok-g4o


::

    O
    jre
    jok-g4o


    O[blyth@localhost cmt]$ ls -l /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks*
    lrwxrwxrwx. 1 blyth blyth 67 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so -> ../../../Simulation/DetSimV2/G4Opticks/Linux-x86_64/libG4Opticks.so
    -rw-rw-r--. 1 blyth blyth 87 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so.cmtref
    O[blyth@localhost cmt]$ date
    Fri May 21 21:23:38 CST 2021



tds2 with "--opticks-anamgr" to feed G4OpticksRecorder with G4Run G4Event G4Track G4Step::

    O[blyth@localhost cmt]$ t tds2
    tds2 () 
    { 
        : run with opticks disabled, but with Opticks provided intrumentation used to save info from Geant4 in OpticksEvent format files;
        local opts="--opticks-mode 2 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 --opticks-anamgr";
        tds- $opts gun $*
    }


::

    epsilon:offline blyth$ svn commit -m "pass G4 objects from detsim/G4OpticksAnaMgr to opticks/g4ok/G4OpticksRecorder, so can develop in Opticks repo"
    Sending        Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.cc
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.hh
    Transmitting file data ...done
    Committing transaction...
    Committed revision 4596.




Examples/Tutorial/python/Tutorial/JUNODetSimModule.py::

    .  |     +--[RootOutputSvc]OutputSvc
       |     |     +--[Var]LogLevel   = 3
       |     |     +--[Var]OutputStreams = {/Event/Gen:sample_detsim.root, /Event/Sim:sample_detsim.root}
    junotoptask.find                WARN: Cann't find Object InputSvc
    junotoptask.find                WARN: Cann't find Object OutputSvc
    junotoptask:PMTParamSvc.init_file  INFO: Loading parameters from file: /home/blyth/junotop/data/Simulation/ElecSim/pmtdata.txt
    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /home/blyth/junotop/offline/Simulation/DetSimV2/TopTracker/include/CrossTalk.txt
    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /home/blyth/junotop/offline/Simulation/DetSimV2/TopTracker/include/ChannelPosition.txt
    junotoptask:PMTSimParamSvc.initialize  INFO: PMTSimParamSvc is initializing!
    junotoptask:PMTSimParamSvc.initialize  INFO: db_type: File
    junotoptask:PMTSimParamSvc.init_file  INFO: Loading parameters from file: /home/blyth/junotop/data/Simulation/ElecSim/PmtData_Lpmt.root
    Detaching after fork from child process 340538.
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 2 WITH_G4OPTICKS 
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr G4OpticksAnaMgr
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr RadioAnaMgr
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr DataModelWriterWithSplit
    junotoptask:DetSimAlg.createTool  INFO: AlgBase::createTool toolName NormalAnaMgr tag NormalAnaMgr objName NormalAnaMgr result 0x29eb078
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr NormalAnaMgr
    junotoptask:DetSimAlg.createTool  INFO: AlgBase::createTool toolName GenEvtInfoAnaMgr tag GenEvtInfoAnaMgr objName GenEvtInfoAnaMgr result 0x2ebbde8
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr GenEvtInfoAnaMgr
    junotoptask:DetSimAlg.createTool  INFO: AlgBase::createTool toolName DepositEnergyAnaMgr tag DepositEnergyAnaMgr objName DepositEnergyAnaMgr result 0x300a618
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr DepositEnergyAnaMgr
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr DepositEnergyTTAnaMgr
    junotoptask:DetSimAlg.createTool  INFO: AlgBase::createTool toolName InteresingProcessAnaMgr tag InteresingProcessAnaMgr objName InteresingProcessAnaMgr result 0x2a14438
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr InteresingProcessAnaMgr
    junotoptask:DetSimAlg.createTool  INFO: AlgBase::createTool toolName OpticalParameterAnaMgr tag OpticalParameterAnaMgr objName OpticalParameterAnaMgr result 0x2ea2858
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr OpticalParameterAnaMgr
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr TimerAnaMgr



Do not see output from G4OpticksAnaMgr although it is in the AnaMgrList, I recall getting this before

jnu/opticks-junoenv-runtime.rst


::

    BP=LSExpRunAction::BeginOfRunAction tds2


::

     30 void MgrOfAnaElem::BeginOfRunAction(const G4Run* run) {
     31     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     32     {
     33           val->BeginOfRunAction(run);
     34     }
     35 }
     36 void MgrOfAnaElem::EndOfRunAction(const G4Run* run){
     37     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     38     {
     39           val->EndOfRunAction(run);
     40     }
     41 


::

    (gdb) p m_order
    $2 = std::vector of length 10, capacity 16 = {0x250c090, 0x250d9f0, 0x2533030, 0x2aa76c0, 0x2ebc060, 0x300a890, 0x7fffbf507010, 0x2eabe00, 0x29bd680, 0x25337e0}
    (gdb) p m_anamgrs
    $3 = std::map with 10 elements = {["DataModelWriterWithSplit"] = 0x2533030, ["DepositEnergyAnaMgr"] = 0x300a890, ["DepositEnergyTTAnaMgr"] = 0x7fffbf507010, ["G4OpticksAnaMgr"] = 0x250c090, 
      ["GenEvtInfoAnaMgr"] = 0x2ebc060, ["InteresingProcessAnaMgr"] = 0x2eabe00, ["NormalAnaMgr"] = 0x2aa76c0, ["OpticalParameterAnaMgr"] = 0x29bd680, ["RadioAnaMgr"] = 0x250d9f0, 
      ["TimerAnaMgr"] = 0x25337e0}
    (gdb) 


Getting the output now, but not WITH_G4OPTICKS::

    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 


::

    epsilon:~ blyth$ cat $JUNOTOP/ExternalInterface/Externals/OpticksG4OK/cmt/requirements
    package OpticksG4OK

    macro OpticksG4OK_home "" \
              opticks " \`opticks-config --prefix\` "

    macro OpticksG4OK_cppflags "" \
              opticks  " \`opticks-config --cflags G4OK\` -DWITH_G4OPTICKS "

    macro OpticksG4OK_linkopts "" \
              opticks " \`opticks-config --libs G4OK\` " 



Package dependency tree must include OpticksG4OK::

    epsilon:offline blyth$ jgr OpticksG4OK
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:use OpticksG4OK    v* Externals


    epsilon:offline blyth$ jgr DetSimPolicy
    ./Simulation/DetSimV2/SimUtil/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PhysiSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/G4DAEChroma/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CMakeLists.txt:#add_subdirectory(DetSimPolicy)
    ./Simulation/DetSimV2/G4Opticks/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PMTSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimAlg/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/MCParamsSvc/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/GenSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/TopTracker/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CalibUnit/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/Chimney/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimOptions/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CentralDetector/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:package DetSimPolicy
    ./Simulation/DetSimV2/OPSimulator/cmt/requirements:use DetSimPolicy  v* Simulation/DetSimV2
    ./Simulation/DetSimV2/DAE/cmt/requirements:use DetSimPolicy v* Simulation/DetSimV2
    ./Simulation/DetSimV2/G4Svc/cmt/requirements:use DetSimPolicy    v*   Simulation/DetSimV2
    ./Simulation/DetSimV2/AnalysisCode/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    epsilon:offline blyth$ 


    O[blyth@localhost cmt]$ pwd
    /home/blyth/junotop/offline/Simulation/DetSimV2/G4Opticks/cmt
    O[blyth@localhost cmt]$ 

    O[blyth@localhost cmt]$ cmt show macro_value OpticksG4OK_cppflags
    O[blyth@localhost cmt]$ CMTEXTRATAGS=opticks cmt show macro_value OpticksG4OK_cppflags
     -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -DOPTICKS_G4OK -DOPTICKS_CFG4 -DOPTICKS_X4 -DOPTICKS_OKOP -DOPTICKS_OKGEO -DOPTICKS_THRAP -DOPTICKS_GGEO -DOPTICKS_OKCORE -DOPTICKS_NPY -DOPTICKS_OKCONF -DOPTICKS_SYSRAP -DWITH_STTF -DWITH_PLOG -DOPTICKS_BRAP -DWITH_BOOST_ASIO -DOPTICKS_CUDARAP -DOPTICKS_OXRAP -I/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/bin/../include/Geant4 -I/home/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/include -I/home/blyth/local/opticks/include/G4OK -I/home/blyth/local/opticks/include/CFG4 -I/home/blyth/local/opticks/include/ExtG4 -I/home/blyth/local/opticks/include/OKOP -I/home/blyth/local/opticks/include/OpticksGeo -I/home/blyth/local/opticks/include/ThrustRap -I/home/blyth/local/opticks/include/GGeo -I/home/blyth/local/opticks/include/OpticksCore -I/home/blyth/local/opticks/externals/include -I/home/blyth/local/opticks/include/NPY -I/home/blyth/local/opticks/include/OKConf -I/home/blyth/local/opticks/externals/glm/glm -I/home/blyth/local/opticks/include/SysRap -I/home/blyth/local/opticks/include/BoostRap -I/home/blyth/local/opticks/include/CUDARap -I/home/blyth/local/opticks/include/OptiXRap -I/home/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include -I/home/blyth/local/opticks/externals/plog/include -I/home/blyth/local/opticks/externals/include/nljson -I/usr/local/cuda/include -I/home/blyth/local/opticks/externals/OptiX_650/include -std=c++11 -DWITH_G4OPTICKS 
    O[blyth@localhost cmt]$ 


