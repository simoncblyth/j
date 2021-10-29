update-oct29-2021
=====================

Lots of offline updates recently.::

    je ; bash junoenv offline




::

    #CMT---> (constituents.make) AnalysisCodecompile done
    #CMT---> (constituents.make) Starting AnalysisCodeinstall
    #CMT---> building static library ../Linux-x86_64/libAnalysisCode.a
    #CMT---> building shared library ../Linux-x86_64/libAnalysisCode.so
    AnalysisCodetemp_shlib/G4OpticksAnaMgr.o: In function `G4OpticksAnaMgr::saveScintillationIntegral(char const*, char const*) const':
    /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/cmt/../src/G4OpticksAnaMgr.cc:106: undefined reference to `X4PhysicsOrderedFreeVector::X4PhysicsOrderedFreeVector(G4PhysicsOrderedFreeVector*)'
    /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/cmt/../src/G4OpticksAnaMgr.cc:107: undefined reference to `NPY<double>* X4PhysicsOrderedFreeVector::convert<double>()'
    collect2: error: ld returned 1 exit status
    gmake[2]: *** [../Linux-x86_64/libAnalysisCode.so] Error 1
    gmake[1]: *** [AnalysisCodeinstall] Error 2
    gmake: *** [all] Error 2
    #CMT---> Error: execution failed : make
    #CMT---> Error: execution error : cmt make


Fixed shadow warnings::

    In file included from ../src/G4OpticksAnaMgr.cc:64:
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh: In member function 'void NP::read(const T*)':
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh:2798:50: warning: declaration of 'data' shadows a member of 'NP' [-Wshadow]
     template <typename T> void NP::read(const T* data)
                                                      ^
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh:210:23: note: shadowed declaration is here
         std::vector<char> data ;
                           ^~~~
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh: In member function 'void NP::read2(const T*)':
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh:2814:51: warning: declaration of 'data' shadows a member of 'NP' [-Wshadow]
     template <typename T> void NP::read2(const T* data)
                                                       ^
    /data/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/NP.hh:210:23: note: shadowed declaration is here
         std::vector<char> data ;
                           ^~~~


Fallout from 1100, fix with namechange to X4Array::

    vi /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/cmt/../src/G4OpticksAnaMgr.cc +106

    100 void  G4OpticksAnaMgr::saveScintillationIntegral(const char* dir, const char* name) const
    101 {
    102     DsG4Scintillation* scint = getScintillationProcess() ;
    103     int scnt = 0 ;
    104     int materialIndex = 1 ;
    105     G4PhysicsOrderedFreeVector* ScintillationIntegral =  scint->getScintillationIntegral(scnt, materialIndex );
    106     X4PhysicsOrderedFreeVector* xvec = new X4PhysicsOrderedFreeVector(ScintillationIntegral);
    107     NPY<double>* d = xvec->convert<double>(); ;
    108     d->save(dir, name);


runtime::


    tds3
    ...

    junotoptask:PMTSimParamSvc.initialize  INFO: db_type: File
    junotoptask:PMTSimParamSvc.init_default  INFO: Retrieve PMTParamSvc successfully.
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:MCParamsSvc.GetPath ERROR: Path /data/blyth/junotop/data/Simulation/DetSim/PMTProperty/Dynode/CE does not exist.
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: basic_string::_S_construct null not valid
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0

    (gdb) 



    je ; bash junoenv offline-data





::

    junotoptask:DetSim1Construction.initVariables  INFO: m_radReflector:     19631
    junotoptask:DetSim1Construction.initVariables  INFO: m_radReflectorChimney:532
    [ LSExpDetectorConstruction::setupCentralDetector proceed with setupCD_Sticks 
    junotoptask:StrutAcrylicConstruction.initVariables  INFO: m_useRealSurface is 1
    junotoptask:StrutAcrylicConstruction.initVariables  INFO: Option RealSurface is enabled in Central Detector.  Reduce m_lengthStrut from 1807.6 to: 1552.05
    m_radStrut = 42.5
    SNiPER:NonDLE.setupCD_Sticks    INFO: Note: strut_r is queried from geom_info, the value is 18852.9, the hardcoded value is 18980.7
    PMT_Acrylic_Number = 370
    junotoptask:StrutBar2AcrylicConstruction.initVariables  INFO: Option RealSurface is enabled in Central Detector.  Reduce m_lengthStrut from 1913.6 to: 1552.08
    m_radStrut = 30
    SNiPER:NonDLE.setupCD_Sticks    INFO: Note: strut2_r is queried from geom_info, the value is 18852.9, the hardcoded value is 19033.7
    PMT_Acrylic_Number = 220
    m_rad = 50
    PMT_Acrylic_Number = 590
    PMT_Acrylic_Number = 590
    PMT_Acrylic_Number = 590
    PMT_Acrylic_Number = 590
    PMT_Acrylic_Number = 56
    PMT_Acrylic_Number = 56
    Veto_PMT_Number = -29998
    Veto_PMT_Number = -29964
    Veto_PMT_Number = -29992
    Veto_PMT_Number = -29992
    ] LSExpDetectorConstruction::setupCentralDetector completed setupCD_Sticks 
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    SNiPER:NonDLE.setupReflectorInCD  INFO: m_isCDInnerReflectorEnabled is 1, so the reflector from inner water to tyvek will be setup. 
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameter

