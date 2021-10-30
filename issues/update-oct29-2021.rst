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





warnings to follow up
------------------------

::

    2021-10-30 02:47:55.350 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@87] [ WITH_G4OPTICKS opticksMode 3
    2021-10-30 02:47:55.351 FATAL [51280] [G4Opticks::initSkipGencode@357] OPTICKS_SKIP_GENCODE m_skip_gencode_count 3
    2021-10-30 02:47:55.351 FATAL [51280] [G4Opticks::initSkipGencode@362]  m_skip_gencode[0] 0 INVALID
    2021-10-30 02:47:55.351 FATAL [51280] [G4Opticks::initSkipGencode@362]  m_skip_gencode[1] 0 INVALID
    2021-10-30 02:47:55.351 FATAL [51280] [G4Opticks::initSkipGencode@362]  m_skip_gencode[2] 0 INVALID

    // fixed this : header default  0,0,0 fallback was inadvertantly used 


    2021-10-30 02:47:55.351 INFO  [51280] [G4Opticks::G4Opticks@351] ctor : DISABLE FPE detection : as it breaks OptiX launches
    2021-10-30 02:47:55.351 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@100]  embedded_commandline_extra --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge
    2021-10-30 02:47:56.145 INFO  [51280] [G4Opticks::InitOpticks@216] 
    # BOpticksKey::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.3dbec4dc3bdef47884fe48af781a179d

    2021-10-30 02:47:56.146 INFO  [51280] [G4Opticks::EmbeddedCommandLine@135] Using ecl :[ --compute --embedded --xanalytic --save --natural --printenabled --pindex 0] OPTICKS_EMBEDDED_COMMANDLINE
    2021-10-30 02:47:56.146 INFO  [51280] [G4Opticks::EmbeddedCommandLine@136]  mode(Pro/Dev/Asis) D using "dev" (development) commandline with full event saving 
    2021-10-30 02:47:56.146 INFO  [51280] [G4Opticks::EmbeddedCommandLine@141] Using extra1 argument :[--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge]
    2021-10-30 02:47:56.146 INFO  [51280] [G4Opticks::EmbeddedCommandLine@151] Using eclx envvar :[--skipsolidname mask_PMT_20inch_vetosMask_virtual,NNVTMCPPMT_body_solid,HamamatsuR12860_body_solid_1_9,PMT_20inch_veto_body_solid_1_2 --rtx 1 --cvd 1] OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
    2021-10-30 02:47:56.146 INFO  [51280] [G4Opticks::InitOpticks@236] instanciate Opticks using embedded commandline only 
     --compute --embedded --xanalytic --save --natural --printenabled --pindex 0  --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge --skipsolidname mask_PMT_20inch_vetosMask_virtual,NNVTMCPPMT_body_solid,HamamatsuR12860_body_solid_1_9,PMT_20inch_veto_body_solid_1_2 --rtx 1 --cvd 1
    2021-10-30 02:47:56.149 ERROR [51280] [Opticks::postconfigureCVD@3117]  --cvd [1] option internally sets CUDA_VISIBLE_DEVICES [1]
    2021-10-30 02:47:56.152 INFO  [51280] [G4Opticks::translateGeometry@934] ( CGDML /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml
    2021-10-30 02:47:56.189 INFO  [51280] [BFile::preparePath@836] created directory /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-10-30 02:47:56.189 INFO  [51280] [CGDML::write@372] write to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml
    G4GDML: Writing '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    G4GDML: Writing '/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml' done !
    2021-10-30 02:47:58.473 INFO  [51280] [G4Opticks::translateGeometry@936] ) CGDML 
    2021-10-30 02:47:58.473 INFO  [51280] [G4Opticks::translateGeometry@940] ( CGDMLKludge /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin.gdml --gdmlkludge
    2021-10-30 02:47:59.613 INFO  [51280] [CGDMLKludge::CGDMLKludge@61] num_truncated_matrixElement 1 num_constants 2
    2021-10-30 02:47:59.613 INFO  [51280] [CGDMLKludge::CGDMLKludge@75] writing dstpath /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml
    2021-10-30 02:48:00.005 INFO  [51280] [G4Opticks::translateGeometry@942] kludge_path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/origin_CGDMLKludge.gdml
    2021-10-30 02:48:00.005 INFO  [51280] [G4Opticks::translateGeometry@943] ) CGDMLKludge 
    2021-10-30 02:48:00.005 INFO  [51280] [G4Opticks::translateGeometry@951] ( GGeo instanciate
    2021-10-30 02:48:00.008 INFO  [51280] [G4Opticks::translateGeometry@954] ) GGeo instanciate 
    2021-10-30 02:48:00.008 INFO  [51280] [G4Opticks::translateGeometry@956] ( GGeo populate
    2021-10-30 02:48:00.069 INFO  [51280] [X4PhysicalVolume::convertMaterials@312]  num_mt 20
       0 :                             LS :  num_prop  19               RINDEX              GROUPVEL              RAYLEIGH             ABSLENGTH         FASTCOMPONENT         SLOWCOMPONENT        REEMISSIONPROB       OpticalCONSTANT         GammaCONSTANT         AlphaCONSTANT       NeutronCONSTANT          PPOABSLENGTH     PPOREEMISSIONPROB          PPOCOMPONENT       PPOTIMECONSTANT       bisMSBABSLENGTH  bisMSBREEMISSIONPROB       bisMSBCOMPONENT    bisMSBTIMECONSTANT 
       1 :                          Steel :  num_prop   1            ABSLENGTH 
       2 :                          Tyvek :  num_prop   1            ABSLENGTH 
       3 :                            Air :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
       4 :                   Scintillator : 
       5 :                    TiO2Coating : 
       6 :                       Adhesive : 
       7 :                      Aluminium : 
       8 :                           Rock :  num_prop   1            ABSLENGTH 
       9 :             LatticedShellSteel :  num_prop   1            ABSLENGTH 
      10 :                        Acrylic :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      11 :                          PE_PA :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      12 :                     StrutSteel :  num_prop   2         REFLECTIVITY             ABSLENGTH 
      13 :                    AcrylicMask :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      14 :               CDReflectorSteel :  num_prop   2         REFLECTIVITY             ABSLENGTH 
      15 :                         Vacuum :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      16 :                          Pyrex :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      17 :                          Water :  num_prop   4               RINDEX              GROUPVEL              RAYLEIGH             ABSLENGTH 
      18 :                      vetoWater :  num_prop   3               RINDEX              GROUPVEL             ABSLENGTH 
      19 :                       Galactic : 

    2021-10-30 02:48:00.075 ERROR [51280] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Scintillator
    2021-10-30 02:48:00.076 ERROR [51280] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt TiO2Coating
    2021-10-30 02:48:00.077 ERROR [51280] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Adhesive
    2021-10-30 02:48:00.078 ERROR [51280] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Aluminium
    2021-10-30 02:48:00.091 ERROR [51280] [X4MaterialTable::init@118] PROCEEDING TO convert material with no mpt Galactic
    2021-10-30 02:48:00.099 INFO  [51280] [X4PhysicalVolume::convertMaterials@321]  used_materials.size 20 num_material_with_efficiency 0
    2021-10-30 02:48:00.099 INFO  [51280] [GMaterialLib::dumpSensitiveMaterials@1258] X4PhysicalVolume::convertMaterials num_sensitive_materials 0
    2021-10-30 02:48:00.099 INFO  [51280] [X4PhysicalVolume::collectScintillatorMaterials@415]  found 1 scintillator materials  
    2021-10-30 02:48:00.099 INFO  [51280] [GScintillatorLib::Summary@51] X4PhysicalVolume::collectScintillatorMaterials GScintillatorLib.getNumRaw  1 GScintillatorLib.getNumRawOriginal  1
    2021-10-30 02:48:00.099 INFO  [51280] [GPropertyLib::dumpRaw@937] X4PhysicalVolume::collectScintillatorMaterials
    2021-10-30 02:48:00.099 INFO  [51280] [GPropertyLib::dumpRaw@942]  component LS
    2021-10-30 02:48:00.099 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 GROUPVEL range: 53.4699 : 206.241
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 18
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@227]  np_maxdiff  a    18 b    18
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    0 av    79.9898 bv    79.9898 ab          0
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    1 av    120.023 bv    124.808 ab     4.7845
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    2 av     129.99 bv    134.802 ab    4.81234
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    3 av    139.984 bv    144.808 ab     4.8231
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    4 av    149.975 bv    154.816 ab    4.84092
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    5 av     159.98 bv    164.829 ab    4.84916
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    6 av    169.981 bv    174.835 ab    4.85386
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    7 av    179.974 bv    184.844 ab    4.86997
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    8 av    189.985 bv    194.852 ab    4.86682
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i    9 av    199.974 bv    239.982 ab    40.0071
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   10 av        300 bv    344.572 ab    44.5721
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   11 av      404.7 bv    419.674 ab    14.9747
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   12 av      435.8 bv    459.533 ab    23.7336
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   13 av    486.001 bv    514.257 ab    28.2557
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   14 av    546.001 bv    566.686 ab    20.6858
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   15 av    589.001 bv     635.81 ab    46.8085
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   16 av      690.7 bv    741.299 ab     50.599
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@242]  i   17 av    799.898 bv    799.898 ab          0
    2021-10-30 02:48:00.100 INFO  [51280] [np_maxdiff@251]  maxdiff 50.599
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 11
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 RAYLEIGH range: 546.429 : 321429
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 11
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 11
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 497
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 ABSLENGTH range: 0.00296154 : 125372
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 497
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 497
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 FASTCOMPONENT range: 0 : 1
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 SLOWCOMPONENT range: 0 : 1
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 28
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 REEMISSIONPROB range: 0 : 0.8022
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 28
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 28
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 GammaCONSTANT range: 0.028 : 0.707
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 AlphaCONSTANT range: 0.0812 : 0.4982
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 NeutronCONSTANT range: 0.064 : 0.614
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 4
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 770
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOABSLENGTH range: 0.02 : 1.3029e+07
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 770
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 770
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 15
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOREEMISSIONPROB range: 0 : 0.93
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 15
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 15
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 200
    2021-10-30 02:48:00.100 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 PPOCOMPONENT range: 0 : 0.0187
    2021-10-30 02:48:00.100 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 200
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 200
    2021-10-30 02:48:00.100 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 375
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBABSLENGTH range: 27.42 : 1.5e+08
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 375
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 375
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 23
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBREEMISSIONPROB range: 0 : 0.932
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 23
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 23
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  RINDEX range: 1.4536 : 1.793 bisMSBCOMPONENT range: 0 : 1
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 18 blen 275
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 18 blen 275
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 PPOTIMECONSTANT constant: 1.6
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 2
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 bisMSBTIMECONSTANT constant: 1.4
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 2
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 2
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 SCINTILLATIONYIELD constant: 11522
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 761
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-10-30 02:48:00.101 FATAL [51280] [GProperty<T>::make_table@492] GProperty<T>::make_table domain mismatch  OpticalCONSTANT constant: 1 RESOLUTIONSCALE constant: 1
    2021-10-30 02:48:00.101 INFO  [51280] [GProperty<T>::hasSameDomain@294] GProperty<T>::hasSameDomain alen 1 blen 761
    2021-10-30 02:48:00.101 WARN  [51280] [GProperty<T>::hasSameDomain@302]  length mismatch  alen 1 blen 761
    2021-10-30 02:48:00.099 INFO  [51280] [GPropertyLib::dumpRaw@943]  table GPropertyMap<T>::make_table vprops 16 cprops 5 dprops 0 eprops 0 fprops 0 gprops 0
                  domain              RINDEX            GROUPVEL            RAYLEIGH           ABSLENGTH       FASTCOMPONENT       SLOWCOMPONENT      REEMISSIONPROB       GammaCONSTANT       AlphaCONSTANT     NeutronCONSTANT        PPOABSLENGTH   PPOREEMISSIONPROB        PPOCOMPONENT     bisMSBABSLENGTHbisMSBREEMISSIONPROB     bisMSBCOMPONENT
                 79.9898              1.4536             206.241             546.429          0.00296154                   0                   0                 0.4               0.028              0.0812               0.064                0.02               0.651                   0               42.26              0.6524                   0
                 120.023              1.4536             199.323             546.429          0.00296154                   0                   0                 0.4                0.06              0.1467                0.09                0.02               0.651                   0               42.26              0.6524                   0
                  129.99              1.5545             186.282             546.429          0.00296154                   0                   0                 0.4               0.205              0.2739               0.232                0.02               0.651                   0               41.13              0.6524                   0
                 139.984              1.6642             173.954             4885.71             1.42154            0.002269            0.002269                0.42               0.707              0.4982               0.614                0.02               0.651                   0               40.36              0.6524            0.002269
                 149.975              1.7826             167.688             19285.7             1.62885            0.002153            0.002153                0.45                   0                   0                   0                0.02               0.651                   0               39.63              0.6524            0.002153
                  159.98               1.793             53.4699               27000             1.83615            0.001981            0.001981                 0.8        1.63042e-322        1.63042e-322        1.63042e-322                0.02                0.93                   0               38.37               0.932            0.001981
                 169.981              1.5545             148.255             39857.1             2.07308            0.001887            0.001887              0.8006        6.95332e-310        6.95332e-310        6.95332e-310                0.02                0.93                   0               37.71               0.932            0.001887
                 179.974               1.527             190.671             64285.7             2.28038            0.002218            0.002218              0.8004        3.64822e-315        3.64823e-315        3.64823e-315                0.02                0.93                   0               36.32               0.932            0.002218
                 189.985              1.6176              185.28              109286             2.60615            0.001909            0.001909              0.8022        1.97626e-323        1.97626e-323        1.97626e-323                0.02                0.93                   0               35.73               0.932            0.001909
                 199.974              1.6185             166.595              192857             2.81346            0.001965            0.001965              0.6353        2.42092e-322        2.42092e-322        2.42092e-322                0.02                0.93                   0               35.04               0.932            0.001965
                     300              1.5264              186.81              321429             3.02077             0.00169             0.00169              0.4165         3.12303e-06         2.27711e-06         3.37832e-06                0.02                0.93              0.0003               34.92               0.932             0.00169
                   404.7              1.4988             194.453        4.79244e-322             3.19846            0.001809            0.001809              0.3004         1.62923e-05         1.39238e-05         1.62709e-05                0.02                0.93              0.0003               34.69               0.932            0.001809
                   435.8              1.4955             195.919             546.429             3.40577            0.001994            0.001994              0.2354         8.21087e-05         7.02858e-05         7.89708e-05                0.02                   0              0.0002               34.59               0.932            0.001994
                 486.001              1.4915             195.281             546.429             3.58346            0.002311            0.002311              0.2203         0.000269531         0.000285349          0.00027552                0.02                   0              0.0002               34.69               0.932            0.002311
                 546.001              1.4861              198.51             546.429             3.73154             0.00205             0.00205              0.1969                   0                   0                   0                0.02                   0              0.0002               34.92               0.932             0.00205
                 589.001              1.4842              198.74             4885.71             3.90923            0.002102            0.002102              0.1936        3.21143e-322        3.21143e-322        3.21143e-322                0.02        2.42092e-322              0.0001               35.15               0.932            0.002102
                   690.7                1.48             200.934             19285.7             4.08692            0.002259            0.002259              0.1712        4.94066e-324                   0        4.94066e-324                0.02        6.95332e-310              0.0001               35.61               0.932            0.002259
                 799.898              1.4781             201.062               27000               4.235            0.002578            0.002578              0.1417         3.6463e-315        3.64806e-315        3.64822e-315                0.02        6.95314e-310              0.0001                36.2               0.932            0.002578
                            domain               OpticalCONSTANT               PPOTIMECONSTANT            bisMSBTIMECONSTANT            SCINTILLATIONYIELD               RESOLUTIONSCALE
                       0.000826561                             1                           1.6                           1.4                         11522                             1

    2021-10-30 02:48:00.101 INFO  [51280] [NPY<T>::compare@2356]  a 275,2
    2021-10-30 02:48:00.102 INFO  [51280] [NPY<T>::compare@2357]  b 275,2
    2021-10-30 02:48:00.102 INFO  [51280] [NPY<T>::compare@2366]  ni 275 nv 2 dumplimit 100 epsilon 0 mode A
    2021-10-30 02:48:00.102 INFO  [51280] [NPY<T>::compare@2407]  mismatch_items 0
    2021-10-30 02:48:00.102 INFO  [51280] [X4PhysicalVolume::createScintillatorGeant4InterpolatedICDF@460]  num_scint 1 slow_en 275,2 fast_en 275,2 num_bins 4096 hd_factor 20 material_name LS g4icdf 3,4096,1
    2021-10-30 02:48:00.114 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@608]  parent_mtName Rock daughter_mtName Air
    2021-10-30 02:48:00.114 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@613]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                       pExpHall pv2                       pTopRock bs 0 no-prior-border-surface-adding-implicit 
    2021-10-30 02:48:00.117 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@608]  parent_mtName Tyvek daughter_mtName vetoWater
    2021-10-30 02:48:00.117 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@613]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                pOuterWaterPool pv2                    pPoolLining bs 0x2c8c0a10 preexisting-border-surface-NOT-adding-implicit 
    2021-10-30 02:48:00.117 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@608]  parent_mtName Tyvek daughter_mtName Water
    2021-10-30 02:48:00.117 INFO  [51280] [X4PhysicalVolume::convertImplicitSurfaces_r@613]  RINDEX_NoRINDEX 1 NoRINDEX_RINDEX 0 pv1                    pInnerWater pv2               pCentralDetector bs 0x2c8bddd0 preexisting-border-surface-NOT-adding-implicit 
    2021-10-30 02:48:00.134 INFO  [51280] [GSurfaceLib::dumpImplicitBorderSurfaces@765] X4PhysicalVolume::convertSurfaces
     num_implicit_border_surfaces 1 edgeitems 100
    GBS::                                                  Implicit_RINDEX_NoRINDEX_pExpHall_pTopRock pv1:                                 pExpHall pv2:                                 pTopRock

    2021-10-30 02:48:00.137 INFO  [51280] [GSurfaceLib::dumpSurfaces@907] X4PhysicalVolume::convertSurfaces num_surfaces 40 edgeitems 100
     index : 0  is_sensor : N type : bordersurface        name : CDTyvekSurface                                     bpv1 pOuterWaterPool bpv2 pCentralDetector .
     index : 1  is_sensor : N type : bordersurface        name : CDInnerTyvekSurface                                bpv1 pInnerWater bpv2 pCentralDetector .
     index : 2  is_sensor : N type : bordersurface        name : VETOTyvekSurface                                   bpv1 pOuterWaterPool bpv2 pPoolLining .
     index : 3  is_sensor : Y type : bordersurface        name : PMT_20inch_photocathode_logsurf1                   bpv1 PMT_20inch_inner1_phys bpv2 PMT_20inch_body_phys .
     index : 4  is_sensor : Y type : bordersurface        name : PMT_20inch_photocathode_logsurf2                   bpv1 PMT_20inch_body_phys bpv2 PMT_20inch_inner1_phys .
     index : 5  is_sensor : N type : bordersurface        name : PMT_20inch_mirror_logsurf1                         bpv1 PMT_20inch_inner2_phys bpv2 PMT_20inch_body_phys .
     index : 6  is_sensor : N type : bordersurface        name : PMT_20inch_mirror_logsurf2                         bpv1 PMT_20inch_body_phys bpv2 PMT_20inch_inner2_phys .
     index : 7  is_sensor : Y type : bordersurface        name : HamamatsuR12860_PMT_20inch_photocathode_logsurf1   bpv1 HamamatsuR12860_PMT_20inch_inner1_phys bpv2 HamamatsuR12860_PMT_20inch_body_phys .
     index : 8  is_sensor : Y type : bordersurface        name : HamamatsuR12860_PMT_20inch_photocathode_logsurf2   bpv1 HamamatsuR12860_PMT_20inch_body_phys bpv2 HamamatsuR12860_PMT_20inch_inner1_phys .
     index : 9  is_sensor : N type : bordersurface        name : HamamatsuR12860_PMT_20inch_mirror_logsurf1         bpv1 HamamatsuR12860_PMT_20inch_inner2_phys bpv2 HamamatsuR12860_PMT_20inch_body_phys .
     index : 10 is_sensor : N type : bordersurface        name : HamamatsuR12860_PMT_20inch_mirror_logsurf2         bpv1 HamamatsuR12860_PMT_20inch_body_phys bpv2 HamamatsuR12860_PMT_20inch_inner2_phys .
     index : 11 is_sensor : Y type : bordersurface        name : NNVTMCPPMT_PMT_20inch_photocathode_logsurf1        bpv1 NNVTMCPPMT_PMT_20inch_inner1_phys bpv2 NNVTMCPPMT_PMT_20inch_body_phys .
     index : 12 is_sensor : Y type : bordersurface        name : NNVTMCPPMT_PMT_20inch_photocathode_logsurf2        bpv1 NNVTMCPPMT_PMT_20inch_body_phys bpv2 NNVTMCPPMT_PMT_20inch_inner1_phys .
     index : 13 is_sensor : N type : bordersurface        name : NNVTMCPPMT_PMT_20inch_mirror_logsurf1              bpv1 NNVTMCPPMT_PMT_20inch_inner2_phys bpv2 NNVTMCPPMT_PMT_20inch_body_phys .
     index : 14 is_sensor : N type : bordersurface        name : NNVTMCPPMT_PMT_20inch_mirror_logsurf2              bpv1 NNVTMCPPMT_PMT_20inch_body_phys bpv2 NNVTMCPPMT_PMT_20inch_inner2_phys .
     index : 15 is_sensor : Y type : bordersurface        name : PMT_20inch_veto_photocathode_logsurf1              bpv1 PMT_20inch_veto_inner1_phys bpv2 PMT_20inch_veto_body_phys .
     index : 16 is_sensor : Y type : bordersurface        name : PMT_20inch_veto_photocathode_logsurf2              bpv1 PMT_20inch_veto_body_phys bpv2 PMT_20inch_veto_inner1_phys .
     index : 17 is_sensor : N type : bordersurface        name : PMT_20inch_veto_mirror_logsurf1                    bpv1 PMT_20inch_veto_inner2_phys bpv2 PMT_20inch_veto_body_phys .
     index : 18 is_sensor : N type : bordersurface        name : PMT_20inch_veto_mirror_logsurf2                    bpv1 PMT_20inch_veto_body_phys bpv2 PMT_20inch_veto_inner2_phys .
     index : 19 is_sensor : Y type : bordersurface        name : PMT_3inch_photocathode_logsurf1                    bpv1 PMT_3inch_inner1_phys bpv2 PMT_3inch_body_phys .
     index : 20 is_sensor : Y type : bordersurface        name : PMT_3inch_photocathode_logsurf2                    bpv1 PMT_3inch_body_phys bpv2 PMT_3inch_inner1_phys .
     index : 21 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf1                          bpv1 PMT_3inch_inner2_phys bpv2 PMT_3inch_body_phys .
     index : 22 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf2                          bpv1 PMT_3inch_body_phys bpv2 PMT_3inch_inner2_phys .
     index : 23 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf3                          bpv1 PMT_3inch_cntr_phys bpv2 PMT_3inch_body_phys .
     index : 24 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf4                          bpv1 PMT_3inch_body_phys bpv2 PMT_3inch_cntr_phys .
     index : 25 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf5                          bpv1 PMT_3inch_inner1_phys bpv2 PMT_3inch_inner2_phys .
     index : 26 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf6                          bpv1 PMT_3inch_inner2_phys bpv2 PMT_3inch_inner1_phys .
     index : 27 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf7                          bpv1 PMT_3inch_cntr_phys bpv2 PMT_3inch_inner2_phys .
     index : 28 is_sensor : N type : bordersurface        name : PMT_3inch_absorb_logsurf8                          bpv1 PMT_3inch_inner2_phys bpv2 PMT_3inch_cntr_phys .
     index : 29 is_sensor : N type : bordersurface        name : UpperChimneyTyvekSurface                           bpv1 pUpperChimneyLS bpv2 pUpperChimneyTyvek .
     index : 30 is_sensor : N type : skinsurface          name : StrutAcrylicOpSurface                              sslv lSteel .
     index : 31 is_sensor : N type : skinsurface          name : Strut2AcrylicOpSurface                             sslv lSteel2 .
     index : 32 is_sensor : N type : skinsurface          name : HamamatsuMaskOpticalSurface                        sslv HamamatsuR12860lMaskTail .
     index : 33 is_sensor : N type : skinsurface          name : NNVTMaskOpticalSurface                             sslv NNVTMCPPMTlMaskTail .
     index : 34 is_sensor : N type : skinsurface          name : Steel_surface                                      sslv lLowerChimneySteel .
     index : 35 is_sensor : N type : bordersurface        name : Implicit_RINDEX_NoRINDEX_pExpHall_pTopRock         bpv1 pExpHall bpv2 pTopRock .
     index : 36 is_sensor : Y type : testsurface          name : perfectDetectSurface                               .
     index : 37 is_sensor : N type : testsurface          name : perfectAbsorbSurface                               .
     index : 38 is_sensor : N type : testsurface          name : perfectSpecularSurface                             .
     index : 39 is_sensor : N type : testsurface          name : perfectDiffuseSurface                              .
    2021-10-30 02:48:00.137 INFO  [51280] [GPropertyLib::dumpSensorIndices@1066] X4PhysicalVolume::convertSurfaces  NumSensorIndices 11 ( 3 4 7 8 11 12 15 16 19 20 36  ) 
    2021-10-30 02:48:00.295 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 

This was a false message, now fixed:: 

    1191     if(deltaPhi_segment_enabled == false)
    1192     {
    1193         if(has_deltaPhi == true) LOG(LEVEL) << " skipped has_deltaPhi == false assert " ;
    1194         //assert( !has_deltaPhi ); 
    1195     }   

    
    2021-10-30 02:48:00.295 FATAL [51280] [X4Solid::convertPolycone@1234]  multiple Rmin is unhandled base_steel
    2021-10-30 02:48:00.295 ERROR [51280] [X4Solid::convertPolycone@1268]  convertPolycone_duplicate_py_inner_omission 1
    2021-10-30 02:48:00.295 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx  95 num_prim  2 num_coincidence  1 num_nudge  1 
    2021-10-30 02:48:00.297 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.298 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx  96 num_prim 13 num_coincidence 67 num_nudge  1 
    2021-10-30 02:48:00.306 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.307 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx  96 num_prim 13 num_coincidence 67 num_nudge  1 
    2021-10-30 02:48:00.331 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.331 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx 101 num_prim  4 num_coincidence  2 num_nudge  1 
    2021-10-30 02:48:00.334 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.334 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx 102 num_prim  4 num_coincidence  2 num_nudge  1 
    2021-10-30 02:48:00.344 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.372 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.385 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.385 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.385 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.385 FATAL [51280] [NTreeBalance<T>::create_balanced@101] balancing trees of this structure not implemented

Now using treeidx for identification and dumping the tree for unable_to_balance trees. 

    2021-10-30 02:48:00.385 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx 108 num_prim  8 num_coincidence  5 num_nudge  2 
    2021-10-30 02:48:00.396 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:48:00.397 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 

    2021-10-30 02:48:00.397 FATAL [51280] [NTreeBalance<T>::create_balanced@101] balancing trees of this structure not implemented



    2021-10-30 02:48:00.397 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx 109 num_prim  9 num_coincidence  6 num_nudge  2 
    2021-10-30 02:48:33.428 WARN  [51280] [X4Mesh::polygonize@177] BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges

Passed in lvIdx for identification of the solid with polygonization issues. 

    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    ...
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges


    2021-10-30 02:48:33.431 FATAL [51280] [NTreeBalance<T>::create_balanced@101] balancing trees of this structure not implemented
    2021-10-30 02:48:33.431 ERROR [51280] [NNodeNudger::init@85] NNodeNudger::brief root.treeidx 110 num_prim  9 num_coincidence  5 num_nudge  2 
    2021-10-30 02:49:06.875 WARN  [51280] [X4Mesh::polygonize@177] BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges
    BooleanProcessor::createPolyhedron : too many edges

    2021-10-30 02:49:06.877 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:06.971 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:06.972 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.096 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.099 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.101 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.103 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.105 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.119 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 
    2021-10-30 02:49:07.119 FATAL [51280] [X4Solid::convertPolycone@1193]  skipped !has_deltaPhi assert 

    2021-10-30 02:49:07.121 INFO  [51280] [X4PhysicalVolume::dumpLV@1179]  m_lvidx.size() 133 m_lvlist.size() 133 edgeitems 100
     i 0     idx 0     lvname lUpperChimneyLS                                    soname Upper_LS_tube                                     
     i 1     idx 1     lvname lUpperChimneySteel                                 soname Upper_Steel_tube                                  
     i 2     idx 2     lvname lUpperChimneyTyvek                                 soname Upper_Tyvek_tube                                  
     i 3     idx 3     lvname lUpperChimney                                      soname Upper_Chimney                                     
     i 4     idx 4     lvname lBar                                               soname sBar                                              
     i 5     idx 5     lvname lCoating                                           soname sBar                                              
     i 6     idx 6     lvname lPanelTape                                         soname sPanelTape                                        
     i 7     idx 7     lvname lPanel                                             soname sPanel                                            
     i 8     idx 8     lvname lPlanef_                                           soname sPlane                                            
     i 9     idx 9     lvname lWallff_                                           soname sWall                                             
     i 10    idx 10    lvname lAirTT                                             soname sAirTT                                            
     i 11    idx 11    lvname lExpHall                                           soname sExpHall                                          
     i 12    idx 12    lvname lTopRock                                           soname sTopRock                                          
     i 13    idx 13    lvname GLw1.up10_up11_HBeam                               soname GLw1.up10_up11_FlangeI_Web_FlangeII               
     i 14    idx 14    lvname GLw1.up09_up10_HBeam                               soname GLw1.up09_up10_FlangeI_Web_FlangeII               
     i 15    idx 15    lvname GLw1.up08_up09_HBeam                               soname GLw1.up08_up09_FlangeI_Web_FlangeII               
     i 16    idx 16    lvname GLw1.up07_up08_HBeam                               soname GLw1.up07_up08_FlangeI_Web_FlangeII               
     i 17    idx 17    lvname GLw1.up06_up07_HBeam                               soname GLw1.up06_up07_FlangeI_Web_FlangeII               
     i 18    idx 18    lvname GLw1.up05_up06_HBeam                               soname GLw1.up05_up06_FlangeI_Web_FlangeII               
     i 19    idx 19    lvname GLw1.up04_up05_HBeam                               soname GLw1.up04_up05_FlangeI_Web_FlangeII               
     i 20    idx 20    lvname GLw1.up03_up04_HBeam                               soname GLw1.up03_up04_FlangeI_Web_FlangeII               
     i 21    idx 21    lvname GLw1.up02_up03_HBeam                               soname GLw1.up02_up03_FlangeI_Web_FlangeII               
     i 22    idx 22    lvname GLw1.up01_up02_HBeam                               soname GLw1.up01_up02_FlangeI_Web_FlangeII               
     i 23    idx 23    lvname GLw2.equ_up01_HBeam                                soname GLw2.equ_up01_FlangeI_Web_FlangeII                
     i 24    idx 24    lvname GLw2.equ_bt01_HBeam                                soname GLw2.equ_bt01_FlangeI_Web_FlangeII                
     i 25    idx 25    lvname GLw3.bt01_bt02_HBeam                               soname GLw3.bt01_bt02_FlangeI_Web_FlangeII               
     i 26    idx 26    lvname GLw3.bt02_bt03_HBeam                               soname GLw3.bt02_bt03_FlangeI_Web_FlangeII               
     i 27    idx 27    lvname GLw2.bt03_bt04_HBeam                               soname GLw2.bt03_bt04_FlangeI_Web_FlangeII               
     i 28    idx 28    lvname GLw2.bt04_bt05_HBeam                               soname GLw2.bt04_bt05_FlangeI_Web_FlangeII               
     i 29    idx 29    lvname GLw1.bt05_bt06_HBeam                               soname GLw1.bt05_bt06_FlangeI_Web_FlangeII               
     i 30    idx 30    lvname GLw1.bt06_bt07_HBeam                               soname GLw1.bt06_bt07_FlangeI_Web_FlangeII               
     i 31    idx 31    lvname GLw1.bt07_bt08_HBeam                               soname GLw1.bt07_bt08_FlangeI_Web_FlangeII               
     i 32    idx 32    lvname GLw1.bt08_bt09_HBeam                               soname GLw1.bt08_bt09_FlangeI_Web_FlangeII               
     i 33    idx 33    lvname GLw1.bt09_bt10_HBeam                               soname GLw1.bt09_bt10_FlangeI_Web_FlangeII               
     i 34    idx 34    lvname GLw1.bt10_bt11_HBeam                               soname GLw1.bt10_bt11_FlangeI_Web_FlangeII               
     i 35    idx 35    lvname GLb3.up11_HBeam                                    soname GLb3.up11_FlangeI_Web_FlangeII                    
     i 36    idx 36    lvname GLb4.up10_HBeam                                    soname GLb4.up10_FlangeI_Web_FlangeII                    
     i 37    idx 37    lvname GLb3.up09_HBeam                                    soname GLb3.up09_FlangeI_Web_FlangeII                    
     i 38    idx 38    lvname GLb2.up08_HBeam                                    soname GLb2.up08_FlangeI_Web_FlangeII                    
     i 39    idx 39    lvname GLb2.up07_HBeam                                    soname GLb2.up07_FlangeI_Web_FlangeII                    
     i 40    idx 40    lvname GLb2.up06_HBeam                                    soname GLb2.up06_FlangeI_Web_FlangeII                    
     i 41    idx 41    lvname GLb1.up05_HBeam                                    soname GLb1.up05_FlangeI_Web_FlangeII                    
     i 42    idx 42    lvname GLb1.up04_HBeam                                    soname GLb1.up04_FlangeI_Web_FlangeII                    
     i 43    idx 43    lvname GLb1.up03_HBeam                                    soname GLb1.up03_FlangeI_Web_FlangeII                    
     i 44    idx 44    lvname GLb1.up02_HBeam                                    soname GLb1.up02_FlangeI_Web_FlangeII                    
     i 45    idx 45    lvname GLb1.up01_HBeam                                    soname GLb1.up01_FlangeI_Web_FlangeII                    
     i 46    idx 46    lvname GLb2.equ_HBeam                                     soname GLb2.equ_FlangeI_Web_FlangeII                     
     i 47    idx 47    lvname GLb2.bt01_HBeam                                    soname GLb2.bt01_FlangeI_Web_FlangeII                    
     i 48    idx 48    lvname GLb1.bt02_HBeam                                    soname GLb1.bt02_FlangeI_Web_FlangeII                    
     i 49    idx 49    lvname GLb2.bt03_HBeam                                    soname GLb2.bt03_FlangeI_Web_FlangeII                    
     i 50    idx 50    lvname GLb2.bt04_HBeam                                    soname GLb2.bt04_FlangeI_Web_FlangeII                    
     i 51    idx 51    lvname GLb1.bt05_HBeam                                    soname GLb1.bt05_FlangeI_Web_FlangeII                    
     i 52    idx 52    lvname GLb1.bt06_HBeam                                    soname GLb1.bt06_FlangeI_Web_FlangeII                    
     i 53    idx 53    lvname GLb1.bt07_HBeam                                    soname GLb1.bt07_FlangeI_Web_FlangeII                    
     i 54    idx 54    lvname GLb1.bt08_HBeam                                    soname GLb1.bt08_FlangeI_Web_FlangeII                    
     i 55    idx 55    lvname GLb3.bt09_HBeam                                    soname GLb3.bt09_FlangeI_Web_FlangeII                    
     i 56    idx 56    lvname GLb3.bt10_HBeam                                    soname GLb3.bt10_FlangeI_Web_FlangeII                    
     i 57    idx 57    lvname GLb3.bt11_HBeam                                    soname GLb3.bt11_FlangeI_Web_FlangeII                    
     i 58    idx 58    lvname GZ1.A01_02_HBeam                                   soname GZ1.A01_02_FlangeI_Web_FlangeII                   
     i 59    idx 59    lvname GZ1.A02_03_HBeam                                   soname GZ1.A02_03_FlangeI_Web_FlangeII                   
     i 60    idx 60    lvname GZ1.A03_04_HBeam                                   soname GZ1.A03_04_FlangeI_Web_FlangeII                   
     i 61    idx 61    lvname GZ1.A04_05_HBeam                                   soname GZ1.A04_05_FlangeI_Web_FlangeII                   
     i 62    idx 62    lvname GZ1.A05_06_HBeam                                   soname GZ1.A05_06_FlangeI_Web_FlangeII                   
     i 63    idx 63    lvname GZ1.A06_07_HBeam                                   soname GZ1.A06_07_FlangeI_Web_FlangeII                   
     i 64    idx 64    lvname GZ1.B01_02_HBeam                                   soname GZ1.B01_02_FlangeI_Web_FlangeII                   
     i 65    idx 65    lvname GZ1.B02_03_HBeam                                   soname GZ1.B02_03_FlangeI_Web_FlangeII                   
     i 66    idx 66    lvname GZ1.B03_04_HBeam                                   soname GZ1.B03_04_FlangeI_Web_FlangeII                   
     i 67    idx 67    lvname GZ1.B04_05_HBeam                                   soname GZ1.B04_05_FlangeI_Web_FlangeII                   
     i 68    idx 68    lvname GZ1.B05_06_HBeam                                   soname GZ1.B05_06_FlangeI_Web_FlangeII                   
     i 69    idx 69    lvname GZ1.B06_07_HBeam                                   soname GZ1.B06_07_FlangeI_Web_FlangeII                   
     i 70    idx 70    lvname ZC2.A02_B02_HBeam                                  soname ZC2.A02_B02_FlangeI_Web_FlangeII                  
     i 71    idx 71    lvname ZC2.A03_B03_HBeam                                  soname ZC2.A03_B03_FlangeI_Web_FlangeII                  
     i 72    idx 72    lvname ZC2.A04_B04_HBeam                                  soname ZC2.A04_B04_FlangeI_Web_FlangeII                  
     i 73    idx 73    lvname ZC2.A05_B05_HBeam                                  soname ZC2.A05_B05_FlangeI_Web_FlangeII                  
     i 74    idx 74    lvname ZC2.A06_B06_HBeam                                  soname ZC2.A06_B06_FlangeI_Web_FlangeII                  
     i 75    idx 75    lvname ZC2.A02_B03_HBeam                                  soname ZC2.A02_B03_FlangeI_Web_FlangeII                  
     i 76    idx 76    lvname ZC2.A03_B04_HBeam                                  soname ZC2.A03_B04_FlangeI_Web_FlangeII                  
     i 77    idx 77    lvname ZC2.A04_B05_HBeam                                  soname ZC2.A04_B05_FlangeI_Web_FlangeII                  
     i 78    idx 78    lvname ZC2.A05_B06_HBeam                                  soname ZC2.A05_B06_FlangeI_Web_FlangeII                  
     i 79    idx 79    lvname ZC2.A06_B07_HBeam                                  soname ZC2.A06_B07_FlangeI_Web_FlangeII                  
     i 80    idx 80    lvname ZC2.B01_B01_HBeam                                  soname ZC2.B01_B01_FlangeI_Web_FlangeII                  
     i 81    idx 81    lvname ZC2.B03_B03_HBeam                                  soname ZC2.B03_B03_FlangeI_Web_FlangeII                  
     i 82    idx 82    lvname ZC2.B05_B05_HBeam                                  soname ZC2.B05_B05_FlangeI_Web_FlangeII                  
     i 83    idx 83    lvname ZC2.A03_A03_HBeam                                  soname ZC2.A03_A03_FlangeI_Web_FlangeII                  
     i 84    idx 84    lvname ZC2.A05_A05_HBeam                                  soname ZC2.A05_A05_FlangeI_Web_FlangeII                  
     i 85    idx 85    lvname lSJCLSanchor                                       soname solidSJCLSanchor                                  
     i 86    idx 86    lvname lSJFixture                                         soname solidSJFixture                                    
     i 87    idx 87    lvname lSJReceiver                                        soname solidSJReceiver                                   
     i 88    idx 88    lvname lXJfixture                                         soname solidXJfixture                                    
     i 89    idx 89    lvname lTarget                                            soname sTarget                                           
     i 90    idx 90    lvname lAcrylic                                           soname sAcrylic                                          
     i 91    idx 91    lvname lSteel                                             soname sStrut                                            
     i 92    idx 92    lvname lSteel2                                            soname sStrut                                            
     i 93    idx 93    lvname lSteel                                             soname sStrutBallhead                                    
     i 94    idx 94    lvname lFasteners                                         soname uni1                                              
     i 95    idx 95    lvname lUpper                                             soname base_steel                                        
     i 96    idx 96    lvname lAddition                                          soname uni_acrylic3                                      
     i 97    idx 97    lvname lXJanchor                                          soname solidXJanchor                                     

     i 98    idx 98    lvname NNVTMCPPMTlMask                                    soname NNVTMCPPMTsMask                                   
     i 99    idx 99    lvname NNVTMCPPMTlMaskTail                                soname NNVTMCPPMTTail                                    
     i 100   idx 100   lvname NNVTMCPPMT_PMT_20inch_inner1_log                   soname NNVTMCPPMT_PMT_20inch_inner1_solid_1_Ellipsoid    
     i 101   idx 101   lvname NNVTMCPPMT_PMT_20inch_inner2_log                   soname NNVTMCPPMT_PMT_20inch_inner2_tail_solid           
     i 102   idx 102   lvname NNVTMCPPMT_PMT_20inch_body_log                     soname NNVTMCPPMT_PMT_20inch_pmt_cut_solid               
     i 103   idx 103   lvname NNVTMCPPMT_PMT_20inch_log                          soname NNVTMCPPMT_PMT_20inch_pmt_cut_solid               
     i 104   idx 104   lvname NNVTMCPPMTlMaskVirtual                             soname NNVTMCPPMTsMask_virtual                           

     i 105   idx 105   lvname HamamatsuR12860lMask                               soname HamamatsuR12860sMask                              
     i 106   idx 106   lvname HamamatsuR12860lMaskTail                           soname HamamatsuR12860Tail                               
     i 107   idx 107   lvname HamamatsuR12860_PMT_20inch_inner1_log              soname HamamatsuR12860_PMT_20inch_inner1_solid_I         
     i 108   idx 108   lvname HamamatsuR12860_PMT_20inch_inner2_log              soname HamamatsuR12860_PMT_20inch_inner2_tail_solid      
     i 109   idx 109   lvname HamamatsuR12860_PMT_20inch_body_log                soname HamamatsuR12860_PMT_20inch_pmt_cut_solid          
     i 110   idx 110   lvname HamamatsuR12860_PMT_20inch_log                     soname HamamatsuR12860_PMT_20inch_pmt_cut_solid          
     i 111   idx 111   lvname HamamatsuR12860lMaskVirtual                        soname HamamatsuR12860sMask_virtual                      

     i 112   idx 112   lvname PMT_3inch_inner1_log                               soname PMT_3inch_inner1_solid_ell_helper                 
     i 113   idx 113   lvname PMT_3inch_inner2_log                               soname PMT_3inch_inner2_solid_ell_helper                 
     i 114   idx 114   lvname PMT_3inch_body_log                                 soname PMT_3inch_body_solid_ell_ell_helper               
     i 115   idx 115   lvname PMT_3inch_cntr_log                                 soname PMT_3inch_cntr_solid                              
     i 116   idx 116   lvname PMT_3inch_log                                      soname PMT_3inch_pmt_solid                               

Name changes... need to look again at PMT geometry.

epsilon:extg4 blyth$ jgr _cut_solid 
./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:        pmt_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:        body_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:        pmt_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:        body_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
epsilon:offline blyth$ 

epsilon:offline blyth$ jcv HamamatsuMaskManager
2 files to edit
./Simulation/DetSimV2/PMTSim/include/HamamatsuMaskManager.hh
./Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
epsilon:offline blyth$ 




     i 117   idx 117   lvname lLowerChimneyAcrylic                               soname sChimneyAcrylic                                   
     i 118   idx 118   lvname lLowerChimneyLS                                    soname sChimneyLS                                        
     i 119   idx 119   lvname lLowerChimneySteel                                 soname sChimneySteel                                     
     i 120   idx 120   lvname lLowerChimney                                      soname sWaterTube                                        
     i 121   idx 121   lvname lInnerWater                                        soname sInnerWater                                       
     i 122   idx 122   lvname lReflectorInCD                                     soname sReflectorInCD                                    

     i 123   idx 123   lvname mask_PMT_20inch_vetolMask                          soname mask_PMT_20inch_vetosMask                         
     i 124   idx 124   lvname PMT_20inch_veto_inner1_log                         soname PMT_20inch_veto_inner1_solid                      
     i 125   idx 125   lvname PMT_20inch_veto_inner2_log                         soname PMT_20inch_veto_inner2_solid                      
     i 126   idx 126   lvname PMT_20inch_veto_body_log                           soname PMT_20inch_veto_body_solid_1_2                    
     i 127   idx 127   lvname PMT_20inch_veto_log                                soname PMT_20inch_veto_pmt_solid_1_2                     
     i 128   idx 128   lvname mask_PMT_20inch_vetolMaskVirtual                   soname mask_PMT_20inch_vetosMask_virtual                 

     i 129   idx 129   lvname lOuterWaterPool                                    soname sOuterWaterPool                                   
     i 130   idx 130   lvname lPoolLining                                        soname sPoolLining                                       
     i 131   idx 131   lvname lBtmRock                                           soname sBottomRock                                       
     i 132   idx 132   lvname lWorld                                             soname sWorld                                            

    2021-10-30 02:49:07.122 INFO  [51280] [X4PhysicalVolume::convertStructure@1289] [ creating large tree of GVolume instances
    2021-10-30 02:49:25.347 INFO  [51280] [X4PhysicalVolume::postConvert@215]  GGeo::getNumVolumes() 0 GGeo::getNumSensorVolumes() 0
     GGeo::getSensorBoundaryReport() 
     boundary  30 b+1  31 sensor_count  12612 Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum
     boundary  33 b+1  34 sensor_count   5000 Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum
     boundary  35 b+1  36 sensor_count  25600 Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
     boundary  40 b+1  41 sensor_count   2400 Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
                          sensor_total  45612

    2021-10-30 02:49:25.347 INFO  [51280] [X4PhysicalVolume::postConvert@225] GBndLib::getAddBoundaryReport edgeitems 100 num_boundary_add 42
     boundary   0 b+1   1 add_count      1 Galactic///Galactic
     boundary   1 b+1   2 add_count      2 Galactic///Rock
     boundary   2 b+1   3 add_count      1 Rock//Implicit_RINDEX_NoRINDEX_pExpHall_pTopRock/Air
     boundary   3 b+1   4 add_count    191 Air///Air
     boundary   4 b+1   5 add_count      1 Air///LS
     boundary   5 b+1   6 add_count      1 Air///Steel
     boundary   6 b+1   7 add_count      1 Air///Tyvek
     boundary   7 b+1   8 add_count    504 Air///Aluminium
     boundary   8 b+1   9 add_count    504 Aluminium///Adhesive
     boundary   9 b+1  10 add_count  32256 Adhesive///TiO2Coating
     boundary  10 b+1  11 add_count  32256 TiO2Coating///Scintillator
     boundary  11 b+1  12 add_count      1 Rock///Tyvek
     boundary  12 b+1  13 add_count      1 Tyvek//VETOTyvekSurface/vetoWater
     boundary  13 b+1  14 add_count   2120 vetoWater///LatticedShellSteel
     boundary  14 b+1  15 add_count      1 vetoWater/CDTyvekSurface//Tyvek
     boundary  15 b+1  16 add_count      1 Tyvek//CDInnerTyvekSurface/Water
     boundary  16 b+1  17 add_count   3048 Water///Acrylic
     boundary  17 b+1  18 add_count      1 Acrylic///LS
     boundary  18 b+1  19 add_count     46 LS///Acrylic
     boundary  19 b+1  20 add_count      8 LS///PE_PA
     boundary  20 b+1  21 add_count    370 Water/StrutAcrylicOpSurface/StrutAcrylicOpSurface/StrutSteel
     boundary  21 b+1  22 add_count    220 Water/Strut2AcrylicOpSurface/Strut2AcrylicOpSurface/StrutSteel
     boundary  22 b+1  23 add_count    590 Water/StrutAcrylicOpSurface/StrutAcrylicOpSurface/Steel
     boundary  23 b+1  24 add_count  26780 Water///Steel
     boundary  24 b+1  25 add_count     56 Water///PE_PA
     boundary  25 b+1  26 add_count  43213 Water///Water
     boundary  26 b+1  27 add_count  17612 Water///AcrylicMask
     boundary  27 b+1  28 add_count  12612 Water/NNVTMaskOpticalSurface/NNVTMaskOpticalSurface/CDReflectorSteel
     boundary  28 b+1  29 add_count  45612 Water///Pyrex
     boundary  29 b+1  30 add_count  20012 Pyrex///Pyrex
     boundary  30 b+1  31 add_count  12612 Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum
     boundary  31 b+1  32 add_count  12612 Pyrex/NNVTMCPPMT_PMT_20inch_mirror_logsurf2/NNVTMCPPMT_PMT_20inch_mirror_logsurf1/Vacuum
     boundary  32 b+1  33 add_count   5000 Water/HamamatsuMaskOpticalSurface/HamamatsuMaskOpticalSurface/CDReflectorSteel
     boundary  33 b+1  34 add_count   5000 Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum
     boundary  34 b+1  35 add_count   5000 Pyrex/HamamatsuR12860_PMT_20inch_mirror_logsurf2/HamamatsuR12860_PMT_20inch_mirror_logsurf1/Vacuum
     boundary  35 b+1  36 add_count  25600 Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
     boundary  36 b+1  37 add_count  25600 Pyrex/PMT_3inch_absorb_logsurf2/PMT_3inch_absorb_logsurf1/Vacuum
     boundary  37 b+1  38 add_count      1 Water///LS
     boundary  38 b+1  39 add_count      1 Water/Steel_surface/Steel_surface/Steel
     boundary  39 b+1  40 add_count   2400 vetoWater///Water
     boundary  40 b+1  41 add_count   2400 Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
     boundary  41 b+1  42 add_count   2400 Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum
                          add_total 336648

    2021-10-30 02:49:25.348 INFO  [51280] [G4Opticks::translateGeometry@958] ) GGeo populate
    2021-10-30 02:49:25.348 INFO  [51280] [G4Opticks::translateGeometry@960] ( GGeo::postDirectTranslation 
    2021-10-30 02:49:25.348 INFO  [51280] [GGeo::prepare@662] [
    2021-10-30 02:49:25.348 FATAL [51280] [OpticksDbg::postgeometrySkipSolidName@272]  failed to find solid with name starting [NNVTMCPPMT_body_solid]
    2021-10-30 02:49:25.348 FATAL [51280] [OpticksDbg::postgeometrySkipSolidName@272]  failed to find solid with name starting [HamamatsuR12860_body_solid_1_9]

Need to update the skipped solid names, after reviewing new geometry.


    2021-10-30 02:49:25.348 INFO  [51280] [GGeo::prepareVolumes@1274] [ creating merged meshes from the volume tree 
    2021-10-30 02:49:39.823 INFO  [51280] [GInstancer::dumpDigests@530] before sort
     i 0          pdig a656fc24f42883c6761ea775df0cf460         ndig 25600      first 0x8e854060 first.nidx 194244    
     i 1          pdig 59fae0d3a67f8c3b0001b9925953b549         ndig 12612      first 0x38eb2f20 first.nidx 70960     
     i 2          pdig 401cf27c927a3dfedf9a8d7408e08e95         ndig 5000       first 0x38ec6e50 first.nidx 70967     
     i 3          pdig bb0f3d54c61730c73154113995e2ce18         ndig 2400       first 0xbbc22bb0 first.nidx 322248    
     i 4          pdig 98dce83da57b0395e163467c9dae521b         ndig 590        first 0x37427bd0 first.nidx 68488     
     i 5          pdig f4b9ec30ad9f68f89b29639786cb62ef         ndig 590        first 0x378edda0 first.nidx 69078     
     i 6          pdig 812b4ba287f5ee0bc9d43bbf5bbe87fb         ndig 590        first 0x38095c60 first.nidx 69668     
     i 7          pdig 26657d5ff9020d2abefe558796b99584         ndig 590        first 0x3845ac40 first.nidx 70258     
     i 8          pdig 36986ef0e48b2696d09c93846c6b69d0         ndig 504        first 0x2df0c5e0 first.nidx 10        
    2021-10-30 02:49:40.690 INFO  [51280] [GInstancer::dumpDigests@530] after sort
     i 0          pdig a656fc24f42883c6761ea775df0cf460         ndig 25600      first 0x8e854060 first.nidx 194244    
     i 1          pdig 59fae0d3a67f8c3b0001b9925953b549         ndig 12612      first 0x38eb2f20 first.nidx 70960     
     i 2          pdig 401cf27c927a3dfedf9a8d7408e08e95         ndig 5000       first 0x38ec6e50 first.nidx 70967     
     i 3          pdig bb0f3d54c61730c73154113995e2ce18         ndig 2400       first 0xbbc22bb0 first.nidx 322248    
     i 4          pdig 98dce83da57b0395e163467c9dae521b         ndig 590        first 0x37427bd0 first.nidx 68488     
     i 5          pdig f4b9ec30ad9f68f89b29639786cb62ef         ndig 590        first 0x378edda0 first.nidx 69078     
     i 6          pdig 812b4ba287f5ee0bc9d43bbf5bbe87fb         ndig 590        first 0x38095c60 first.nidx 69668     
     i 7          pdig 26657d5ff9020d2abefe558796b99584         ndig 590        first 0x3845ac40 first.nidx 70258     
     i 8          pdig 36986ef0e48b2696d09c93846c6b69d0         ndig 504        first 0x2df0c5e0 first.nidx 10        
    2021-10-30 02:49:40.845 INFO  [51280] [GInstancer::findRepeatCandidates@346]  nall 133 repeat_min 400 vertex_min 0 num_repcan 9
    2021-10-30 02:49:40.845 INFO  [51280] [GInstancer::findRepeatCandidates@356]  num_all 133 num_repcan 9 dmax 30
     (**) candidates fulfil repeat/vert cuts   
     (##) selected survive contained-repeat disqualification 
     **      idx   0 pdig a87ff679a2f3e71d9181a67b7542122c ndig  32256 nprog      0 nvert      8 n pBar
     **      idx   1 pdig 4a891f9f9571ecb440f34c6f1d7a0ed1 ndig  32256 nprog      1 nvert     16 n pCoating_00_
     **  ##  idx   2 pdig a656fc24f42883c6761ea775df0cf460 ndig  25600 nprog      4 nvert    805 n PMT_3inch_log_phys
     **      idx   3 pdig 4b1cb7da6db35bed4afa338a44f0124c ndig  25600 nprog      2 nvert    489 n PMT_3inch_body_phys
     **      idx   4 pdig 7f6ffaa6bb0b408017b62254211691b5 ndig  25600 nprog      0 nvert    123 n PMT_3inch_inner1_phys
     **      idx   5 pdig 73278a4a86960eeb576a8fd4c9ec6997 ndig  25600 nprog      0 nvert    147 n PMT_3inch_inner2_phys
     **      idx   6 pdig 2b44928ae11fb9384c4cf38708677c48 ndig  25600 nprog      0 nvert     50 n PMT_3inch_cntr_phys
     **  ##  idx   7 pdig 59fae0d3a67f8c3b0001b9925953b549 ndig  12612 nprog      6 nvert   2699 n pLPMT_NNVT_MCPPMT
     **      idx   8 pdig 38b3eff8baf56627478ec76a704e9b52 ndig  12612 nprog      0 nvert    266 n NNVTMCPPMT_PMT_20inch_inner2_phys
     **      idx   9 pdig f899139df5e1059396431415e770c6dd ndig  12612 nprog      0 nvert    171 n NNVTMCPPMT_PMT_20inch_inner1_phys
     **      idx  10 pdig b7d436c03edd06c9609cc33835754c84 ndig  12612 nprog      2 nvert    893 n NNVTMCPPMT_PMT_20inch_body_phys
     **      idx  11 pdig d4b9a8568255c8a99ab0a45fe6d2959c ndig  12612 nprog      3 nvert   1349 n NNVTMCPPMT_PMT_20inch_log_phys
     **      idx  12 pdig ac627ab1ccbdb62ec96e702f07f6425b ndig  12612 nprog      0 nvert    602 n NNVTMCPPMTpMaskTail
     **      idx  13 pdig ed3d2c21991e3bef5e069713af9fa6ca ndig  12612 nprog      0 nvert    698 n NNVTMCPPMTpMask
     **      idx  14 pdig cd69b8467a68a0bb3ebdbe0ae5e3eb48 ndig   5000 nprog      2 nvert   1058 n HamamatsuR12860_PMT_20inch_body_phys
     **      idx  15 pdig a97da629b098b75c294dffdc3e463904 ndig   5000 nprog      0 nvert    171 n HamamatsuR12860_PMT_20inch_inner1_phys
     **      idx  16 pdig a3c65c2974270fd093ee8a9bf8ae7d0b ndig   5000 nprog      0 nvert    325 n HamamatsuR12860_PMT_20inch_inner2_phys
     **      idx  17 pdig 3473da416d6a5b02e98d06d0df4487c2 ndig   5000 nprog      3 nvert   1625 n HamamatsuR12860_PMT_20inch_log_phys
     **      idx  18 pdig f0935e4cd5920aa6c7c996a5ee53a70f ndig   5000 nprog      0 nvert    506 n HamamatsuR12860pMaskTail
     **      idx  19 pdig 65b9eea6e1cc6bb9f0cd2a47751a186f ndig   5000 nprog      0 nvert    698 n HamamatsuR12860pMask
     **  ##  idx  20 pdig 401cf27c927a3dfedf9a8d7408e08e95 ndig   5000 nprog      6 nvert   2879 n pLPMT_Hamamatsu_R12860
     **      idx  21 pdig 3def184ad8f4755ff269862ea77393dd ndig   2400 nprog      0 nvert    146 n PMT_20inch_veto_inner2_phys
     **  ##  idx  22 pdig bb0f3d54c61730c73154113995e2ce18 ndig   2400 nprog      5 nvert   1656 n mask_PMT_20inch_vetolMaskVirtual_phys
     **      idx  23 pdig 202cb962ac59075b964b07152d234b70 ndig   2400 nprog      0 nvert    566 n mask_PMT_20inch_vetopMask
     **      idx  24 pdig 87132fe10384708bce7faeee189012f9 ndig   2400 nprog      3 nvert   1040 n PMT_20inch_veto_log_phys
     **      idx  25 pdig ac048be1516e030bebc3c8cd421aa589 ndig   2400 nprog      2 nvert    726 n PMT_20inch_veto_body_phys
     **      idx  26 pdig c8ffe9a587b126f152ed3d89a146b445 ndig   2400 nprog      0 nvert    266 n PMT_20inch_veto_inner1_phys
     **  ##  idx  27 pdig 98dce83da57b0395e163467c9dae521b ndig    590 nprog      0 nvert    267 n lSteel_phys
     **  ##  idx  28 pdig f4b9ec30ad9f68f89b29639786cb62ef ndig    590 nprog      0 nvert    496 n lFasteners_phys
     **  ##  idx  29 pdig 812b4ba287f5ee0bc9d43bbf5bbe87fb ndig    590 nprog      0 nvert    192 n lUpper_phys
    2021-10-30 02:49:40.845 INFO  [51280] [GInstancer::dumpRepeatCandidates@422]  num_repcan 9 dmax 20
     pdig a656fc24f42883c6761ea775df0cf460 ndig 25600  nprog 4      placements 25600  n PMT_3inch_log_phys
     pdig 59fae0d3a67f8c3b0001b9925953b549 ndig 12612  nprog 6      placements 12612  n pLPMT_NNVT_MCPPMT
     pdig 401cf27c927a3dfedf9a8d7408e08e95 ndig 5000   nprog 6      placements 5000   n pLPMT_Hamamatsu_R12860
     pdig bb0f3d54c61730c73154113995e2ce18 ndig 2400   nprog 5      placements 2400   n mask_PMT_20inch_vetolMaskVirtual_phys
     pdig 98dce83da57b0395e163467c9dae521b ndig 590    nprog 0      placements 590    n lSteel_phys
     pdig f4b9ec30ad9f68f89b29639786cb62ef ndig 590    nprog 0      placements 590    n lFasteners_phys
     pdig 812b4ba287f5ee0bc9d43bbf5bbe87fb ndig 590    nprog 0      placements 590    n lUpper_phys
     pdig 26657d5ff9020d2abefe558796b99584 ndig 590    nprog 0      placements 590    n lAddition_phys
     pdig 36986ef0e48b2696d09c93846c6b69d0 ndig 504    nprog 129    placements 504    n pPanel_0_f_
    2021-10-30 02:49:42.348 FATAL [51280] [GInstancer::labelTree@635]  m_labels (count of non-zero setRepeatIndex) 333564 m_csgskiplv_count 4800 m_repeats_count 333564 m_globals_count 3084 total_count : 336648
    2021-10-30 02:49:47.434 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   0 geocode   T                  numVolumes       3084 numFaces      183096 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:47.587 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   1 geocode   T                  numVolumes          5 numFaces        1584 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:47.794 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   2 geocode   T                  numVolumes          7 numFaces        5368 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:47.982 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   3 geocode   T                  numVolumes          7 numFaces        5712 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.198 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   4 geocode   T                  numVolumes          4 numFaces        2564 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.349 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   5 geocode   T                  numVolumes          1 numFaces         528 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.500 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   6 geocode   T                  numVolumes          1 numFaces         960 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.651 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   7 geocode   T                  numVolumes          1 numFaces         384 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.799 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   8 geocode   T                  numVolumes          1 numFaces        1272 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:49:48.926 ERROR [51280] [GGeoLib::makeMergedMesh@330] mm index   9 geocode   T                  numVolumes        130 numFaces        1560 numITransforms           0 numITransforms*numVolumes           0 GParts N GPts Y
    2021-10-30 02:50:01.671 INFO  [51280] [GInstancer::dump@985] GGeo::prepareVolumes
    2021-10-30 02:50:01.671 INFO  [51280] [GInstancer::dumpMeshset@929]  numRepeats 9 numRidx 10 (slot 0 for global non-instanced) 
     ridx 0 ms 100 ( 0 1 2 3 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 97 117 118 119 120 121 122 129 130 131 132  ) 
     ridx 1 ms 5 ( 112 113 114 115 116  ) 
     ridx 2 ms 7 ( 98 99 100 101 102 103 104  ) 
     ridx 3 ms 7 ( 105 106 107 108 109 110 111  ) 
     ridx 4 ms 6 ( 123 124 125 126 127 128  ) 
     ridx 5 ms 1 ( 93  ) 
     ridx 6 ms 1 ( 94  ) 
     ridx 7 ms 1 ( 95  ) 
     ridx 8 ms 1 ( 96  ) 
     ridx 9 ms 4 ( 4 5 6 7  ) 
    2021-10-30 02:50:01.671 INFO  [51280] [GInstancer::dumpCSGSkips@961] 
     lvIdx 126 skip total : 2400 nodeIdx ( 322251 322257 322263 322269 322275 322281 322287 322293 322299 322305 322311 322317 322323 322329 322335 322341 322347 322353 322359 322365  ...  ) 
     lvIdx 128 skip total : 2400 nodeIdx ( 322248 322254 322260 322266 322272 322278 322284 322290 322296 322302 322308 322314 322320 322326 322332 322338 322344 322350 322356 322362  ...  ) 
    2021-10-30 02:50:01.671 INFO  [51280] [GGeo::prepareVolumes@1308] GNodeLib::descOriginMap m_origin2index.size 51023
    2021-10-30 02:50:01.671 INFO  [51280] [GGeo::prepareVolumes@1309] ]
    2021-10-30 02:50:01.889 INFO  [51280] [GGeo::prepare@683] ]
    2021-10-30 02:50:01.889 INFO  [51280] [GGeo::save@706] 
    GGeo::save GGeoLib numMergedMesh 10 ptr 0x2bf5c9b0
    mm index   0 geocode   T                  numVolumes       3084 numFaces      183096 numITransforms           1 numITransforms*numVolumes        3084 GParts N GPts Y
    mm index   1 geocode   T                  numVolumes          5 numFaces        1584 numITransforms       25600 numITransforms*numVolumes      128000 GParts N GPts Y
    mm index   2 geocode   T                  numVolumes          7 numFaces        5368 numITransforms       12612 numITransforms*numVolumes       88284 GParts N GPts Y
    mm index   3 geocode   T                  numVolumes          7 numFaces        5712 numITransforms        5000 numITransforms*numVolumes       35000 GParts N GPts Y
    mm index   4 geocode   T                  numVolumes          4 numFaces        2564 numITransforms        2400 numITransforms*numVolumes        9600 GParts N GPts Y
    mm index   5 geocode   T                  numVolumes          1 numFaces         528 numITransforms         590 numITransforms*numVolumes         590 GParts N GPts Y
    mm index   6 geocode   T                  numVolumes          1 numFaces         960 numITransforms         590 numITransforms*numVolumes         590 GParts N GPts Y
    mm index   7 geocode   T                  numVolumes          1 numFaces         384 numITransforms         590 numITransforms*numVolumes         590 GParts N GPts Y
    mm index   8 geocode   T                  numVolumes          1 numFaces        1272 numITransforms         590 numITransforms*numVolumes         590 GParts N GPts Y
    mm index   9 geocode   T                  numVolumes        130 numFaces        1560 numITransforms         504 numITransforms*numVolumes       65520 GParts N GPts Y
     num_remainder_volumes 3084 num_instanced_volumes 328764 num_remainder_volumes + num_instanced_volumes 331848 num_total_faces 203028 num_total_faces_woi 145789512 (woi:without instancing) 
       0 pts Y  GPts.NumPt  3084 lvIdx ( 132 12 11 3 0 1 2 10 9 8 ... 88 88 88 88 88 120 117 118 119)
       1 pts Y  GPts.NumPt     5 lvIdx ( 116 114 112 113 115)
       2 pts Y  GPts.NumPt     7 lvIdx ( 104 98 99 103 102 100 101)
       3 pts Y  GPts.NumPt     7 lvIdx ( 111 105 106 110 109 107 108)
       4 pts Y  GPts.NumPt     4 lvIdx ( 123 127 124 125)
       5 pts Y  GPts.NumPt     1 lvIdx ( 93)
       6 pts Y  GPts.NumPt     1 lvIdx ( 94)
       7 pts Y  GPts.NumPt     1 lvIdx ( 95)
       8 pts Y  GPts.NumPt     1 lvIdx ( 96)
       9 pts Y  GPts.NumPt   130 lvIdx ( 7 6 5 4 5 4 5 4 5 4 ... 4 5 4 5 4 5 4 5 4)

    2021-10-30 02:50:01.922 INFO  [51280] [GMeshLib::addAltMeshes@119]  num_indices_with_alt 3
    2021-10-30 02:50:01.922 INFO  [51280] [GMeshLib::addAltMeshes@129]  index with alt 88
    2021-10-30 02:50:01.922 INFO  [51280] [GMeshLib::addAltMeshes@129]  index with alt 94
    2021-10-30 02:50:01.922 INFO  [51280] [GMeshLib::addAltMeshes@129]  index with alt 96
    2021-10-30 02:50:01.922 INFO  [51280] [GMeshLib::dump@235] addAltMeshes meshnames 136 meshes 136
     i 0   aidx 0   midx 0   name Upper_LS_tube                                      mesh  nv     50 nf     96
     i 1   aidx 1   midx 1   name Upper_Steel_tube                                   mesh  nv     96 nf    192
     i 2   aidx 2   midx 2   name Upper_Tyvek_tube                                   mesh  nv     96 nf    192
     i 3   aidx 3   midx 3   name Upper_Chimney                                      mesh  nv     50 nf     96
     i 4   aidx 4   midx 4   name sBar                                               mesh  nv      8 nf     12
     i 5   aidx 4   midx 5   name sBar                                               mesh  nv      8 nf     12
     i 6   aidx 6   midx 6   name sPanelTape                                         mesh  nv      8 nf     12
     i 7   aidx 7   midx 7   name sPanel                                             mesh  nv      8 nf     12
     i 8   aidx 8   midx 8   name sPlane                                             mesh  nv      8 nf     12
     i 9   aidx 9   midx 9   name sWall                                              mesh  nv      8 nf     12
     i 10  aidx 10  midx 10  name sAirTT                                             mesh  nv     58 nf    108
     i 11  aidx 11  midx 11  name sExpHall                                           mesh  nv      8 nf     12
     i 12  aidx 12  midx 12  name sTopRock                                           mesh  nv      8 nf     12
     i 13  aidx 13  midx 13  name GLw1.up10_up11_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 14  aidx 14  midx 14  name GLw1.up09_up10_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 15  aidx 15  midx 15  name GLw1.up08_up09_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 16  aidx 16  midx 16  name GLw1.up07_up08_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 17  aidx 17  midx 17  name GLw1.up06_up07_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 18  aidx 18  midx 18  name GLw1.up05_up06_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 19  aidx 19  midx 19  name GLw1.up04_up05_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 20  aidx 20  midx 20  name GLw1.up03_up04_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 21  aidx 21  midx 21  name GLw1.up02_up03_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 22  aidx 22  midx 22  name GLw1.up01_up02_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 23  aidx 23  midx 23  name GLw2.equ_up01_FlangeI_Web_FlangeII                 mesh  nv     24 nf     36
     i 24  aidx 24  midx 24  name GLw2.equ_bt01_FlangeI_Web_FlangeII                 mesh  nv     24 nf     36
     i 25  aidx 25  midx 25  name GLw3.bt01_bt02_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 26  aidx 26  midx 26  name GLw3.bt02_bt03_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 27  aidx 27  midx 27  name GLw2.bt03_bt04_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 28  aidx 28  midx 28  name GLw2.bt04_bt05_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 29  aidx 29  midx 29  name GLw1.bt05_bt06_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 30  aidx 30  midx 30  name GLw1.bt06_bt07_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 31  aidx 31  midx 31  name GLw1.bt07_bt08_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 32  aidx 32  midx 32  name GLw1.bt08_bt09_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 33  aidx 33  midx 33  name GLw1.bt09_bt10_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 34  aidx 34  midx 34  name GLw1.bt10_bt11_FlangeI_Web_FlangeII                mesh  nv     24 nf     36
     i 35  aidx 35  midx 35  name GLb3.up11_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 36  aidx 36  midx 36  name GLb4.up10_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 37  aidx 37  midx 37  name GLb3.up09_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 38  aidx 38  midx 38  name GLb2.up08_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 39  aidx 39  midx 39  name GLb2.up07_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 40  aidx 40  midx 40  name GLb2.up06_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 41  aidx 41  midx 41  name GLb1.up05_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 42  aidx 42  midx 42  name GLb1.up04_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 43  aidx 43  midx 43  name GLb1.up03_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 44  aidx 44  midx 44  name GLb1.up02_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 45  aidx 45  midx 45  name GLb1.up01_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 46  aidx 46  midx 46  name GLb2.equ_FlangeI_Web_FlangeII                      mesh  nv     24 nf     36
     i 47  aidx 47  midx 47  name GLb2.bt01_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 48  aidx 48  midx 48  name GLb1.bt02_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 49  aidx 49  midx 49  name GLb2.bt03_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 50  aidx 50  midx 50  name GLb2.bt04_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 51  aidx 51  midx 51  name GLb1.bt05_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 52  aidx 52  midx 52  name GLb1.bt06_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 53  aidx 53  midx 53  name GLb1.bt07_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 54  aidx 54  midx 54  name GLb1.bt08_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 55  aidx 55  midx 55  name GLb3.bt09_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 56  aidx 56  midx 56  name GLb3.bt10_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 57  aidx 57  midx 57  name GLb3.bt11_FlangeI_Web_FlangeII                     mesh  nv     24 nf     36
     i 58  aidx 58  midx 58  name GZ1.A01_02_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 59  aidx 59  midx 59  name GZ1.A02_03_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 60  aidx 60  midx 60  name GZ1.A03_04_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 61  aidx 61  midx 61  name GZ1.A04_05_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 62  aidx 62  midx 62  name GZ1.A05_06_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 63  aidx 63  midx 63  name GZ1.A06_07_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 64  aidx 64  midx 64  name GZ1.B01_02_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 65  aidx 65  midx 65  name GZ1.B02_03_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 66  aidx 66  midx 66  name GZ1.B03_04_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 67  aidx 67  midx 67  name GZ1.B04_05_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 68  aidx 68  midx 68  name GZ1.B05_06_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 69  aidx 69  midx 69  name GZ1.B06_07_FlangeI_Web_FlangeII                    mesh  nv     24 nf     36
     i 70  aidx 70  midx 70  name ZC2.A02_B02_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 71  aidx 71  midx 71  name ZC2.A03_B03_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 72  aidx 72  midx 72  name ZC2.A04_B04_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 73  aidx 73  midx 73  name ZC2.A05_B05_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 74  aidx 74  midx 74  name ZC2.A06_B06_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 75  aidx 75  midx 75  name ZC2.A02_B03_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 76  aidx 76  midx 76  name ZC2.A03_B04_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 77  aidx 77  midx 77  name ZC2.A04_B05_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 78  aidx 78  midx 78  name ZC2.A05_B06_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 79  aidx 79  midx 79  name ZC2.A06_B07_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 80  aidx 80  midx 80  name ZC2.B01_B01_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 81  aidx 81  midx 81  name ZC2.B03_B03_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 82  aidx 82  midx 82  name ZC2.B05_B05_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 83  aidx 83  midx 83  name ZC2.A03_A03_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 84  aidx 84  midx 84  name ZC2.A05_A05_FlangeI_Web_FlangeII                   mesh  nv     24 nf     36
     i 85  aidx 85  midx 85  name solidSJCLSanchor                                   mesh  nv    105 nf    206
     i 86  aidx 86  midx 86  name solidSJFixture                                     mesh  nv     82 nf    156
     i 87  aidx 87  midx 87  name solidSJReceiver                                    mesh  nv    124 nf    240
     i 88  aidx 88  midx 88  name solidXJfixture                                     mesh  nv    176 nf    344
     i 89  aidx 89  midx 89  name sTarget                                            mesh  nv    362 nf    720
     i 90  aidx 90  midx 90  name sAcrylic                                           mesh  nv    362 nf    720
     i 91  aidx 91  midx 91  name sStrut                                             mesh  nv     50 nf     96
     i 92  aidx 91  midx 92  name sStrut                                             mesh  nv     50 nf     96
     i 93  aidx 93  midx 93  name sStrutBallhead                                     mesh  nv    267 nf    528
     i 94  aidx 94  midx 94  name uni1                                               mesh  nv    496 nf    960
     i 95  aidx 95  midx 95  name base_steel                                         mesh  nv    192 nf    384
     i 96  aidx 96  midx 96  name uni_acrylic3                                       mesh  nv    630 nf   1272
     i 97  aidx 97  midx 97  name solidXJanchor                                      mesh  nv    124 nf    240
     i 98  aidx 98  midx 98  name NNVTMCPPMTsMask                                    mesh  nv    698 nf   1392
     i 99  aidx 99  midx 99  name NNVTMCPPMTTail                                     mesh  nv    602 nf   1200
     i 100 aidx 100 midx 100 name NNVTMCPPMT_PMT_20inch_inner1_solid_1_Ellipsoid     mesh  nv    171 nf    336
     i 101 aidx 101 midx 101 name NNVTMCPPMT_PMT_20inch_inner2_tail_solid            mesh  nv    266 nf    528
     i 102 aidx 102 midx 102 name NNVTMCPPMT_PMT_20inch_pmt_cut_solid                mesh  nv    456 nf    908
     i 103 aidx 102 midx 103 name NNVTMCPPMT_PMT_20inch_pmt_cut_solid                mesh  nv    456 nf    908
     i 104 aidx 104 midx 104 name NNVTMCPPMTsMask_virtual                            mesh  nv     50 nf     96
     i 105 aidx 105 midx 105 name HamamatsuR12860sMask                               mesh  nv    698 nf   1392
     i 106 aidx 106 midx 106 name HamamatsuR12860Tail                                mesh  nv    506 nf   1008
     i 107 aidx 107 midx 107 name HamamatsuR12860_PMT_20inch_inner1_solid_I          mesh  nv    171 nf    336
     i 108 aidx 108 midx 108 name HamamatsuR12860_PMT_20inch_inner2_tail_solid       mesh  nv    325 nf    646
     i 109 aidx 109 midx 109 name HamamatsuR12860_PMT_20inch_pmt_cut_solid           mesh  nv    562 nf   1112
     i 110 aidx 109 midx 110 name HamamatsuR12860_PMT_20inch_pmt_cut_solid           mesh  nv    567 nf   1122
     i 111 aidx 111 midx 111 name HamamatsuR12860sMask_virtual                       mesh  nv     50 nf     96
     i 112 aidx 112 midx 112 name PMT_3inch_inner1_solid_ell_helper                  mesh  nv    123 nf    240
     i 113 aidx 113 midx 113 name PMT_3inch_inner2_solid_ell_helper                  mesh  nv    147 nf    288
     i 114 aidx 114 midx 114 name PMT_3inch_body_solid_ell_ell_helper                mesh  nv    219 nf    432
     i 115 aidx 115 midx 115 name PMT_3inch_cntr_solid                               mesh  nv     50 nf     96
     i 116 aidx 116 midx 116 name PMT_3inch_pmt_solid                                mesh  nv    266 nf    528
     i 117 aidx 117 midx 117 name sChimneyAcrylic                                    mesh  nv     96 nf    192
     i 118 aidx 118 midx 118 name sChimneyLS                                         mesh  nv     50 nf     96
     i 119 aidx 119 midx 119 name sChimneySteel                                      mesh  nv     96 nf    192
     i 120 aidx 120 midx 120 name sWaterTube                                         mesh  nv     50 nf     96
     i 121 aidx 121 midx 121 name sInnerWater                                        mesh  nv    362 nf    720
     i 122 aidx 122 midx 122 name sReflectorInCD                                     mesh  nv    362 nf    720
     i 123 aidx 123 midx 123 name mask_PMT_20inch_vetosMask                          mesh  nv    566 nf   1124
     i 124 aidx 124 midx 124 name PMT_20inch_veto_inner1_solid                       mesh  nv    266 nf    528
     i 125 aidx 125 midx 125 name PMT_20inch_veto_inner2_solid                       mesh  nv    146 nf    288
     i 126 aidx 126 midx 126 name PMT_20inch_veto_body_solid_1_2                     mesh  nv    314 nf    624
     i 127 aidx 127 midx 127 name PMT_20inch_veto_pmt_solid_1_2                      mesh  nv    314 nf    624
     i 128 aidx 128 midx 128 name mask_PMT_20inch_vetosMask_virtual                  mesh  nv     50 nf     96
     i 129 aidx 129 midx 129 name sOuterWaterPool                                    mesh  nv     50 nf     96
     i 130 aidx 130 midx 130 name sPoolLining                                        mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name sBottomRock                                        mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name sWorld                                             mesh  nv      8 nf     12
    2021-10-30 02:50:01.923 ERROR [51280] [GMeshLib::getMeshSimple@328]  mesh indices do not match  m_meshes index 133 mesh.index 88
     i 133 aidx 88  midx 88  name solidXJfixture                                     mesh  nv    176 nf    344
    2021-10-30 02:50:01.923 ERROR [51280] [GMeshLib::getMeshSimple@328]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx 94  midx 94  name uni1                                               mesh  nv    496 nf    960
    2021-10-30 02:50:01.923 ERROR [51280] [GMeshLib::getMeshSimple@328]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx 96  midx 96  name uni_acrylic3                                       mesh  nv    630 nf   1272
    2021-10-30 02:50:01.924 INFO  [51280] [BFile::preparePath@836] created directory /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GItemList
    2021-10-30 02:50:02.048 INFO  [51280] [BFile::preparePath@836] created directory /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GNodeLib
    2021-10-30 02:50:02.405 INFO  [51280] [BFile::preparePath@836] created directory /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GScintillatorLib/LS
    2021-10-30 02:50:02.408 INFO  [51280] [BFile::preparePath@836] created directory /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GScintillatorLib/LS_ori
    2021-10-30 02:50:02.411 INFO  [51280] [BMeta::dump@199] GGeo::saveCacheMeta
    {
        "GEOCACHE_CODE_VERSION": 15,
        "argline": "DetSim0Svc ",
        "cwd": "/tmp/blyth/opticks/tds",
        "location": "Opticks::updateCacheMeta",
        "rundate": "20211030_024756",
        "runfolder": "DetSim0Svc",
        "runlabel": "R1_cvd_1",
        "runstamp": 1635533276
    }
    GGeo::reportMeshUsage
     meshIndex, nvert, nface, nodeCount, nodeCount*nvert, nodeCount*nface, meshName 
      0    ( v50    f96    ) : 1       : 50         : 96         : Upper_LS_tube
      1    ( v96    f192   ) : 1       : 96         : 192        : Upper_Steel_tube
      2    ( v96    f192   ) : 1       : 96         : 192        : Upper_Tyvek_tube
      3    ( v50    f96    ) : 1       : 50         : 96         : Upper_Chimney
      4    ( v8     f12    ) : 32256   : 258048     : 387072     : sBar
      5    ( v8     f12    ) : 32256   : 258048     : 387072     : sBar
      6    ( v8     f12    ) : 504     : 4032       : 6048       : sPanelTape
      7    ( v8     f12    ) : 504     : 4032       : 6048       : sPanel
      8    ( v8     f12    ) : 126     : 1008       : 1512       : sPlane
      9    ( v8     f12    ) : 63      : 504        : 756        : sWall
      10   ( v58    f108   ) : 1       : 58         : 108        : sAirTT
      11   ( v8     f12    ) : 1       : 8          : 12         : sExpHall
      12   ( v8     f12    ) : 1       : 8          : 12         : sTopRock
      13   ( v24    f36    ) : 10      : 240        : 360        : GLw1.up10_up11_FlangeI_Web_FlangeII
      14   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up09_up10_FlangeI_Web_FlangeII
      15   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up08_up09_FlangeI_Web_FlangeII
      16   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up07_up08_FlangeI_Web_FlangeII
      17   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up06_up07_FlangeI_Web_FlangeII
      18   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up05_up06_FlangeI_Web_FlangeII
      19   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up04_up05_FlangeI_Web_FlangeII
      20   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up03_up04_FlangeI_Web_FlangeII
      21   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up02_up03_FlangeI_Web_FlangeII
      22   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.up01_up02_FlangeI_Web_FlangeII
      23   ( v24    f36    ) : 30      : 720        : 1080       : GLw2.equ_up01_FlangeI_Web_FlangeII
      24   ( v24    f36    ) : 30      : 720        : 1080       : GLw2.equ_bt01_FlangeI_Web_FlangeII
      25   ( v24    f36    ) : 30      : 720        : 1080       : GLw3.bt01_bt02_FlangeI_Web_FlangeII
      26   ( v24    f36    ) : 30      : 720        : 1080       : GLw3.bt02_bt03_FlangeI_Web_FlangeII
      27   ( v24    f36    ) : 30      : 720        : 1080       : GLw2.bt03_bt04_FlangeI_Web_FlangeII
      28   ( v24    f36    ) : 30      : 720        : 1080       : GLw2.bt04_bt05_FlangeI_Web_FlangeII
      29   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.bt05_bt06_FlangeI_Web_FlangeII
      30   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.bt06_bt07_FlangeI_Web_FlangeII
      31   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.bt07_bt08_FlangeI_Web_FlangeII
      32   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.bt08_bt09_FlangeI_Web_FlangeII
      33   ( v24    f36    ) : 30      : 720        : 1080       : GLw1.bt09_bt10_FlangeI_Web_FlangeII
      34   ( v24    f36    ) : 10      : 240        : 360        : GLw1.bt10_bt11_FlangeI_Web_FlangeII
      35   ( v24    f36    ) : 30      : 720        : 1080       : GLb3.up11_FlangeI_Web_FlangeII
      36   ( v24    f36    ) : 30      : 720        : 1080       : GLb4.up10_FlangeI_Web_FlangeII
      37   ( v24    f36    ) : 30      : 720        : 1080       : GLb3.up09_FlangeI_Web_FlangeII
      38   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.up08_FlangeI_Web_FlangeII
      39   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.up07_FlangeI_Web_FlangeII
      40   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.up06_FlangeI_Web_FlangeII
      41   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.up05_FlangeI_Web_FlangeII
      42   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.up04_FlangeI_Web_FlangeII
      43   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.up03_FlangeI_Web_FlangeII
      44   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.up02_FlangeI_Web_FlangeII
      45   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.up01_FlangeI_Web_FlangeII
      46   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.equ_FlangeI_Web_FlangeII
      47   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.bt01_FlangeI_Web_FlangeII
      48   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.bt02_FlangeI_Web_FlangeII
      49   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.bt03_FlangeI_Web_FlangeII
      50   ( v24    f36    ) : 30      : 720        : 1080       : GLb2.bt04_FlangeI_Web_FlangeII
      51   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.bt05_FlangeI_Web_FlangeII
      52   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.bt06_FlangeI_Web_FlangeII
      53   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.bt07_FlangeI_Web_FlangeII
      54   ( v24    f36    ) : 30      : 720        : 1080       : GLb1.bt08_FlangeI_Web_FlangeII
      55   ( v24    f36    ) : 30      : 720        : 1080       : GLb3.bt09_FlangeI_Web_FlangeII
      56   ( v24    f36    ) : 30      : 720        : 1080       : GLb3.bt10_FlangeI_Web_FlangeII
      57   ( v24    f36    ) : 30      : 720        : 1080       : GLb3.bt11_FlangeI_Web_FlangeII
      58   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A01_02_FlangeI_Web_FlangeII
      59   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A02_03_FlangeI_Web_FlangeII
      60   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A03_04_FlangeI_Web_FlangeII
      61   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A04_05_FlangeI_Web_FlangeII
      62   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A05_06_FlangeI_Web_FlangeII
      63   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.A06_07_FlangeI_Web_FlangeII
      64   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B01_02_FlangeI_Web_FlangeII
      65   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B02_03_FlangeI_Web_FlangeII
      66   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B03_04_FlangeI_Web_FlangeII
      67   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B04_05_FlangeI_Web_FlangeII
      68   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B05_06_FlangeI_Web_FlangeII
      69   ( v24    f36    ) : 30      : 720        : 1080       : GZ1.B06_07_FlangeI_Web_FlangeII
      70   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A02_B02_FlangeI_Web_FlangeII
      71   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A03_B03_FlangeI_Web_FlangeII
      72   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A04_B04_FlangeI_Web_FlangeII
      73   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A05_B05_FlangeI_Web_FlangeII
      74   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A06_B06_FlangeI_Web_FlangeII
      75   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A02_B03_FlangeI_Web_FlangeII
      76   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A03_B04_FlangeI_Web_FlangeII
      77   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A04_B05_FlangeI_Web_FlangeII
      78   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A05_B06_FlangeI_Web_FlangeII
      79   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A06_B07_FlangeI_Web_FlangeII
      80   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.B01_B01_FlangeI_Web_FlangeII
      81   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.B03_B03_FlangeI_Web_FlangeII
      82   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.B05_B05_FlangeI_Web_FlangeII
      83   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A03_A03_FlangeI_Web_FlangeII
      84   ( v24    f36    ) : 30      : 720        : 1080       : ZC2.A05_A05_FlangeI_Web_FlangeII
      85   ( v105   f206   ) : 2       : 210        : 412        : solidSJCLSanchor
      86   ( v82    f156   ) : 36      : 2952       : 5616       : solidSJFixture
      87   ( v124   f240   ) : 8       : 992        : 1920       : solidSJReceiver
      88   ( v176   f344   ) : 64      : 11264      : 22016      : solidXJfixture
      89   ( v362   f720   ) : 1       : 362        : 720        : sTarget
      90   ( v362   f720   ) : 1       : 362        : 720        : sAcrylic
      91   ( v50    f96    ) : 370     : 18500      : 35520      : sStrut
      92   ( v50    f96    ) : 220     : 11000      : 21120      : sStrut
      93   ( v267   f528   ) : 590     : 157530     : 311520     : sStrutBallhead
      94   ( v496   f960   ) : 590     : 292640     : 566400     : uni1
      95   ( v192   f384   ) : 590     : 113280     : 226560     : base_steel
      96   ( v630   f1272  ) : 590     : 371700     : 750480     : uni_acrylic3
      97   ( v124   f240   ) : 56      : 6944       : 13440      : solidXJanchor
      98   ( v698   f1392  ) : 12612   : 8803176    : 17555904   : NNVTMCPPMTsMask
      99   ( v602   f1200  ) : 12612   : 7592424    : 15134400   : NNVTMCPPMTTail
      100  ( v171   f336   ) : 12612   : 2156652    : 4237632    : NNVTMCPPMT_PMT_20inch_inner1_solid_1_Ellipsoid
      101  ( v266   f528   ) : 12612   : 3354792    : 6659136    : NNVTMCPPMT_PMT_20inch_inner2_tail_solid
      102  ( v456   f908   ) : 12612   : 5751072    : 11451696   : NNVTMCPPMT_PMT_20inch_pmt_cut_solid
      103  ( v456   f908   ) : 12612   : 5751072    : 11451696   : NNVTMCPPMT_PMT_20inch_pmt_cut_solid
      104  ( v50    f96    ) : 12612   : 630600     : 1210752    : NNVTMCPPMTsMask_virtual

      105  ( v698   f1392  ) : 5000    : 3490000    : 6960000    : HamamatsuR12860sMask
      106  ( v506   f1008  ) : 5000    : 2530000    : 5040000    : HamamatsuR12860Tail
      107  ( v171   f336   ) : 5000    : 855000     : 1680000    : HamamatsuR12860_PMT_20inch_inner1_solid_I
      108  ( v325   f646   ) : 5000    : 1625000    : 3230000    : HamamatsuR12860_PMT_20inch_inner2_tail_solid
      109  ( v562   f1112  ) : 5000    : 2810000    : 5560000    : HamamatsuR12860_PMT_20inch_pmt_cut_solid
      110  ( v567   f1122  ) : 5000    : 2835000    : 5610000    : HamamatsuR12860_PMT_20inch_pmt_cut_solid
      111  ( v50    f96    ) : 5000    : 250000     : 480000     : HamamatsuR12860sMask_virtual

      112  ( v123   f240   ) : 25600   : 3148800    : 6144000    : PMT_3inch_inner1_solid_ell_helper
      113  ( v147   f288   ) : 25600   : 3763200    : 7372800    : PMT_3inch_inner2_solid_ell_helper
      114  ( v219   f432   ) : 25600   : 5606400    : 11059200   : PMT_3inch_body_solid_ell_ell_helper
      115  ( v50    f96    ) : 25600   : 1280000    : 2457600    : PMT_3inch_cntr_solid
      116  ( v266   f528   ) : 25600   : 6809600    : 13516800   : PMT_3inch_pmt_solid
      117  ( v96    f192   ) : 1       : 96         : 192        : sChimneyAcrylic
      118  ( v50    f96    ) : 1       : 50         : 96         : sChimneyLS
      119  ( v96    f192   ) : 1       : 96         : 192        : sChimneySteel
      120  ( v50    f96    ) : 1       : 50         : 96         : sWaterTube
      121  ( v362   f720   ) : 1       : 362        : 720        : sInnerWater
      122  ( v362   f720   ) : 1       : 362        : 720        : sReflectorInCD
      123  ( v566   f1124  ) : 2400    : 1358400    : 2697600    : mask_PMT_20inch_vetosMask
      124  ( v266   f528   ) : 2400    : 638400     : 1267200    : PMT_20inch_veto_inner1_solid
      125  ( v146   f288   ) : 2400    : 350400     : 691200     : PMT_20inch_veto_inner2_solid
      126  ( v314   f624   ) : 2400    : 753600     : 1497600    : PMT_20inch_veto_body_solid_1_2
      127  ( v314   f624   ) : 2400    : 753600     : 1497600    : PMT_20inch_veto_pmt_solid_1_2
      128  ( v50    f96    ) : 2400    : 120000     : 230400     : mask_PMT_20inch_vetosMask_virtual
      129  ( v50    f96    ) : 1       : 50         : 96         : sOuterWaterPool
      130  ( v50    f96    ) : 1       : 50         : 96         : sPoolLining
      131  ( v50    f96    ) : 1       : 50         : 96         : sBottomRock
      132  ( v8     f12    ) : 1       : 8          : 12         : sWorld
     tot  node : 336648  vert : 74583016 face : 147517512
    2021-10-30 02:50:03.169 INFO  [51280] [GGeo::postDirectTranslationDump@637] GGeo::postDirectTranslationDump NOT --dumpsensor numSensorVolumes 45612
    2021-10-30 02:50:03.169 INFO  [51280] [G4Opticks::translateGeometry@962] ) GGeo::postDirectTranslation 
    2021-10-30 02:50:03.169 ERROR [51280] [G4Opticks::setGeometry@649] CAUTION : m_placement_outer_volume TRUE 
    2021-10-30 02:50:03.179 INFO  [51280] [G4Opticks::setGeometry@654]  GGeo: LIVE TRANSLATED  num_sensor 45612
    2021-10-30 02:50:03.183 ERROR [51280] [OpticksGen::initFromLegacyGensteps@205] SKIP as isNoInputGensteps OR isEmbedded  
    2021-10-30 02:50:03.257 INFO  [51280] [OContext::InitRTX@342]  --rtx 1 setting  ON
    Missing separate debuginfo for /lib64/libcuda.so
    Try: yum --enablerepo='*debug*' install /usr/lib/debug/.build-id/3e/1e7dd516361182d263c7713bd47eaa498bf0cd.debug
    [New Thread 0x7fffade4e700 (LWP 54986)]
    2021-10-30 02:50:03.426 INFO  [51280] [OContext::CheckDevices@226] 
    Device 0                      TITAN RTX ordinal 0 Compute Support: 7 5 Total Memory: 25396445184

    [New Thread 0x7ffe157fa700 (LWP 55107)]
    2021-10-30 02:50:04.107 INFO  [51280] [CDevice::Dump@265] Visible devices[1:TITAN_RTX]
    2021-10-30 02:50:04.107 INFO  [51280] [CDevice::Dump@269] idx/ord/mpc/cc:0/1/72/75  23.652 GB  TITAN RTX
    2021-10-30 02:50:04.107 INFO  [51280] [CDevice::Dump@265] All devices[0:TITAN_V 1:TITAN_RTX]
    2021-10-30 02:50:04.107 INFO  [51280] [CDevice::Dump@269] idx/ord/mpc/cc:0/0/80/70  11.784 GB  TITAN V
    2021-10-30 02:50:04.107 INFO  [51280] [CDevice::Dump@269] idx/ord/mpc/cc:1/1/72/75  23.652 GB  TITAN RTX
    2021-10-30 02:50:04.108 INFO  [51280] [NPY<T>::MakeFloat@2032]  nv 1024
    [New Thread 0x7ffe14ff9700 (LWP 55108)]
    [New Thread 0x7ffdddfff700 (LWP 55110)]
    2021-10-30 02:50:04.366 INFO  [51280] [NPY<T>::MakeFloat@2032]  nv 12288
    2021-10-30 02:50:04.437 INFO  [51280] [OGeo::init@240] OGeo  top Sbvh ggg Sbvh assembly Sbvh instance Sbvh
    2021-10-30 02:50:04.437 INFO  [51280] [OGeo::convert@298] 
    OGeo::convert GGeoLib numMergedMesh 10 ptr 0x2bf5c9b0
    mm index   0 geocode   T                  numVolumes       3084 numFaces      183096 numITransforms           1 numITransforms*numVolumes        3084 GParts Y GPts Y
    mm index   1 geocode   T                  numVolumes          5 numFaces        1584 numITransforms       25600 numITransforms*numVolumes      128000 GParts Y GPts Y
    mm index   2 geocode   T                  numVolumes          7 numFaces        5368 numITransforms       12612 numITransforms*numVolumes       88284 GParts Y GPts Y
    mm index   3 geocode   T                  numVolumes          7 numFaces        5712 numITransforms        5000 numITransforms*numVolumes       35000 GParts Y GPts Y
    mm index   4 geocode   T                  numVolumes          4 numFaces        2564 numITransforms        2400 numITransforms*numVolumes        9600 GParts Y GPts Y
    mm index   5 geocode   T                  numVolumes          1 numFaces         528 numITransforms         590 numITransforms*numVolumes         590 GParts Y GPts Y
    mm index   6 geocode   T                  numVolumes          1 numFaces         960 numITransforms         590 numITransforms*numVolumes         590 GParts Y GPts Y
    mm index   7 geocode   T                  numVolumes          1 numFaces         384 numITransforms         590 numITransforms*numVolumes         590 GParts Y GPts Y
    mm index   8 geocode   T                  numVolumes          1 numFaces        1272 numITransforms         590 numITransforms*numVolumes         590 GParts Y GPts Y
    mm index   9 geocode   T                  numVolumes        130 numFaces        1560 numITransforms         504 numITransforms*numVolumes       65520 GParts Y GPts Y
     num_remainder_volumes 3084 num_instanced_volumes 328764 num_remainder_volumes + num_instanced_volumes 331848 num_total_faces 203028 num_total_faces_woi 145789512 (woi:without instancing) 
       0 pts Y  GPts.NumPt  3084 lvIdx ( 132 12 11 3 0 1 2 10 9 8 ... 88 88 88 88 88 120 117 118 119)

Added SCount counting occurrences of each lvIdx to start looking into why repeats not being instanced. 

       1 pts Y  GPts.NumPt     5 lvIdx ( 116 114 112 113 115)
       2 pts Y  GPts.NumPt     7 lvIdx ( 104 98 99 103 102 100 101)

       3 pts Y  GPts.NumPt     7 lvIdx ( 111 105 106 110 109 107 108)

       4 pts Y  GPts.NumPt     4 lvIdx ( 123 127 124 125)
       5 pts Y  GPts.NumPt     1 lvIdx ( 93)
       6 pts Y  GPts.NumPt     1 lvIdx ( 94)
       7 pts Y  GPts.NumPt     1 lvIdx ( 95)
       8 pts Y  GPts.NumPt     1 lvIdx ( 96)
       9 pts Y  GPts.NumPt   130 lvIdx ( 7 6 5 4 5 4 5 4 5 4 ... 4 5 4 5 4 5 4 5 4)

    2021-10-30 02:50:04.437 INFO  [51280] [OGeo::convert@302] [ nmm 10
    2021-10-30 02:50:05.923 INFO  [51280] [OGeo::convert@321] ] nmm 10
    2021-10-30 02:50:05.938 INFO  [51280] [NPY<T>::MakeFloat@2032]  nv 1022784
    2021-10-30 02:50:06.086 ERROR [51280] [cuRANDWrapper::setItems@154] CAUTION : are resizing the launch sequence 
    2021-10-30 02:50:07.060 FATAL [51280] [ORng::setSkipAhead@155] skipahead 0
    2021-10-30 02:50:07.244 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@115] [ setSensorData num_sensor 45612
    2021-10-30 02:50:07.266 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@129] ] setSensorData num_sensor 45612
    2021-10-30 02:50:07.266 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@142] [ setSensorAngularEfficiency  theta_steps 90 theta_min 0 theta_max 1.5708
    2021-10-30 02:50:07.266 FATAL [51280] [Opticks::setAngularEnabled@1170]  angular_enabled 1
    2021-10-30 02:50:07.266 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@150] ] setSensorAngularEfficiency 
    2021-10-30 02:50:07.266 INFO  [51280] [G4Opticks::saveSensorLib@882]  saving to $TMP/LSExpDetectorConstruction__SetupOpticks/SensorLib/
    2021-10-30 02:50:07.266 INFO  [51280] [SensorLib::save@38] $TMP/LSExpDetectorConstruction__SetupOpticks/SensorLib/
    2021-10-30 02:50:07.267 INFO  [51280] [LSExpDetectorConstruction_Opticks::Setup@154] ] WITH_G4OPTICKS 
    ../src/LSExpDetectorConstruction.cc:383 completed construction of physiWorld  m_opticksMode 3
    /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5

    ================================================================
    2021-10-30 02:52:32.065 INFO  [51280] [CScint::Check@16]  pmanager 0x1b1c9d170 proc 0x1b3828f50
    2021-10-30 02:52:32.065 INFO  [51280] [CScint::Check@21] CProMgr n:[5] (0) name Transportation left -1 (1) name Scintillation left -1 (2) name OpAbsorption left -1 (3) name OpRayleigh left -1 (4) name OpBoundary left -1
    =======================================================================
    ======       Pre-compound/De-excitation Physics Parameters     ========
    =======================================================================
    Type of pre-compound inverse x-section              3
    Pre-compound model active                           1
    Pre-compound low energy (MeV)                       0.1
    Type of de-excitation inverse x-section             3
    Type of de-excitation factory                       Evaporation
    Number of de-excitation channels                    8
    Min excitation energy (keV)                         0.01
    Min energy per nucleon for multifragmentation (MeV) 1e+05
    Level density (1/MeV)                               0.1
    Time limit for long lived isomeres (ns)             1442.7
    Internal e- conversion flag                         1
    Store e- internal conversion data                   1
    Electron internal conversion ID                     0
    Correlated gamma emission flag                      0
    Max 2J for sampling of angular correlations         10
    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize
    2021-10-30 02:52:32.072 INFO  [51280] [junoSD_PMT_v2_Opticks::Initialize@86]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 g4ok 0x85e31c0
    Begin of Event --> 0
    2021-10-30 02:52:32.076 INFO  [51280] [PMTEfficiencyCheck::addHitRecord@88]  m_eventID 0 m_record_count 0
    2021-10-30 02:52:33.226 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@132] [ eventID 0 m_opticksMode 3 numGensteps 100 numPhotons 10965
    2021-10-30 02:52:33.227 INFO  [51280] [OpticksRun::createOKEvent@158]  tagoffset 0 skipaheadstep 0 skipahead 0
    2021-10-30 02:52:33.454 INFO  [51280] [SensorLib::checkSensorCategories@410] [ SensorLib closed Y loaded N sensor_data 45612,4 sensor_num 45612 sensor_angular_efficiency 5,91,1,1 num_category 5
    2021-10-30 02:52:33.465 INFO  [51280] [SensorLib::dumpCategoryCounts@448] SensorLib::checkSensorCategories
     category 0          count 45612     
    2021-10-30 02:52:33.465 INFO  [51280] [SensorLib::checkSensorCategories@443] ] SensorLib closed Y loaded N sensor_data 45612,4 sensor_num 45612 sensor_angular_efficiency 5,91,1,1 num_category 5
    2021-10-30 02:52:33.465 INFO  [51280] [SensorLib::close@381] SensorLib closed Y loaded N sensor_data 45612,4 sensor_num 45612 sensor_angular_efficiency 5,91,1,1 num_category 5
    2021-10-30 02:52:35.803 INFO  [51280] [OPropagator::prelaunch@202] 0 : (0;0,0) 
    OPropagator::prelaunch
                  validate000                 0.082639
                   compile000                  1.1e-05
                 prelaunch000                  2.04821

    2021-10-30 02:52:35.804 FATAL [51280] [ORng::setSkipAhead@155] skipahead 0
    [New Thread 0x7ffd660f7700 (LWP 59116)]
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit

A tree within Hama instance is exceeding limit.  Added primIdx dumping. j/issues/hama-exceeding-tree-limit.rst


    2021-10-30 02:52:35.992 INFO  [51280] [OPropagator::launch@285] 0 : (0;10965,1)  launch time 0.18734
    2021-10-30 02:52:35.992 INFO  [51280] [OpIndexer::indexSequenceCompute@237] OpIndexer::indexSequenceCompute
    2021-10-30 02:52:36.020 INFO  [51280] [OEvent::downloadHits@505]  nhit 4209 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-10-30 02:52:36.021 INFO  [51280] [OEvent::downloadHiys@539]  nhiy 4209 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-10-30 02:52:36.021 INFO  [51280] [OpticksEvent::save@1972] /tmp/blyth/opticks/source/evt/g4live/natural/1
    2021-10-30 02:52:36.037 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@156]  eventID 0 num_gensteps 100 num_photons 10965 num_hit 4209 way_enabled 1 waymask 3
    0      gp.x -17866.30  gp.y 7413.76    gp.z 243.97     gp.R 19344.98   pmt 8790    SI|SD|BT|EC          otk 1      oti5.41     bti 97.08    bp.x -16454.38  bp.y 6838.88    bp.z 188.40     bp.R 17820.00  
    1      gp.x 42.30      gp.y 14878.53   gp.z -12429.17  gp.R 19387.03   pmt 14714   SI|SD|BT|EX          otk 1      oti2.79     bti 92.31    bp.x 42.09      bp.y 13662.83   bp.z -11440.17  bp.R 17820.00  
    2      gp.x 1000.33    gp.y 19240.04   gp.z -980.20    gp.R 19290.95   pmt 9380    SI|RE|SD|BT|EC       otk 7      oti5.11     bti 96.64    bp.x 941.64     bp.y 17769.59   bp.z -952.55    bp.R 17820.00  
    3      gp.x 17527.64   gp.y 5232.22    gp.z -6078.35   gp.R 19275.39   pmt 11673   SI|SD|BT|EX          otk 7      oti2.78     bti 92.51    bp.x 16192.71   bp.y 4841.34    bp.z -5648.88   bp.R 17820.00  
    4      gp.x 8809.46    gp.y 17197.61   gp.z 1449.63    gp.R 19376.94   pmt 8099    SI|RE|SD|BT|EC       otk 7      oti19.55    bti 120.07   bp.x 8110.95    bp.y 15826.29   bp.z 1137.30    bp.R 17820.00  
    5      gp.x -4762.98   gp.y 15909.89   gp.z -9771.07   gp.R 19268.74   pmt 13499   SI|SC|SD|BT|EX       otk 7      oti3.52     bti 106.24   bp.x -4109.43   bp.y 14766.27   bp.z -9089.68   bp.R 17820.00  
    6      gp.x 9610.49    gp.y 7584.67    gp.z -14902.96  gp.R 19286.96   pmt 15717   SI|SD|BT|EX          otk 7      oti5.54     bti 94.63    bp.x 8867.22    bp.y 7004.01    bp.z -13779.28  bp.R 17820.00  
    7      gp.x -4817.19   gp.y -13829.88  gp.z -12515.52  gp.R 19264.19   pmt 14618   SI|SC|SD|BT|EX       otk 7      oti3.82     bti 146.30   bp.x -4093.20   bp.y -13459.57  bp.z -10937.92  bp.R 17820.00  
    8      gp.x -1460.36   gp.y -3641.53   gp.z 18901.83   gp.R 19304.73   pmt 153     SI|SD|BT|EC          otk 7      oti4.24     bti 97.56    bp.x -1283.48   bp.y -3404.90   bp.z 17444.53   bp.R 17820.00  
    9      gp.x 12043.22   gp.y -3645.82   gp.z -14641.81  gp.R 19305.80   pmt 15570   SI|SD|BT|EC          otk 7      oti5.14     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    10     gp.x 91.27      gp.y -1782.86   gp.z -19264.12  gp.R 19346.66   pmt 17576   SI|SC|SD|BT|EX       otk 7      oti9.30     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    11     gp.x -6939.18   gp.y -15936.39  gp.z 8456.85    gp.R 19329.75   pmt 4679    SI|SD|BT|EX          otk 7      oti2.06     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    12     gp.x -3224.16   gp.y 3235.02    gp.z 18795.55   gp.R 19342.53   pmt 236     SI|SD|BT|EX          otk 7      oti20.62    bti 113.80   bp.x -2970.04   bp.y 2996.95    bp.z 17313.28   bp.R 17820.00  
    13     gp.x 5347.01    gp.y 18016.62   gp.z 4366.24    gp.R 19293.86   pmt 6822    SI|SD|BT|EC          otk 7      oti17.00    bti 108.55   bp.x 4943.43    bp.y 16647.43   bp.z 3997.23    bp.R 17820.00  
    14     gp.x -731.54    gp.y -18875.13  gp.z -3757.59   gp.R 19259.42   pmt 10555   SI|SD|BT|EC          otk 7      oti1.95     bti 93.13    bp.x -671.99    bp.y -17457.65  bp.z -3511.57   bp.R 17820.00  
    15     gp.x -10897.08  gp.y 11863.11   gp.z 10559.72   gp.R 19261.04   pmt 3856    SI|RE|SD|BT|EX       otk 5      oti4.34     bti 110.23   bp.x -10025.60  bp.y 11031.77   bp.z 9764.21    bp.R 17820.00  
    16     gp.x 14126.12   gp.y 8075.94    gp.z 10435.72   gp.R 19330.61   pmt 3989    SI|SD|BT|EX          otk 5      oti11.32    bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    17     gp.x 12883.64   gp.y -1771.26   gp.z -14204.85  gp.R 19258.85   pmt 15432   SI|SD|BT|EC          otk 5      oti10.92    bti 100.81   bp.x 11914.11   bp.y -1644.07   bp.z -13149.27  bp.R 17820.00  
    18     gp.x 1988.51    gp.y 10892.54   gp.z -15883.77  gp.R 19362.23   pmt 16124   SI|SD|BT|EX          otk 5      oti1.13     bti 91.15    bp.x 1833.92    bp.y 10009.48   bp.z -14628.72  bp.R 17820.00  
    19     gp.x 13467.42   gp.y 7262.55    gp.z -11870.92  gp.R 19365.81   pmt 14337   SI|SD|BT|EC          otk 5      oti16.38    bti 106.68   bp.x 12389.23   bp.y 6668.57    bp.z -10935.70  bp.R 17820.00  
    2021-10-30 02:52:36.056 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@179] ] num_hit 4209 merged_count  0 m_merged_total 0 m_opticksMode 3
    2021-10-30 02:52:36.056 INFO  [51280] [junoSD_PMT_v2_Opticks::TerminateEvent@226]  NOT invoking G4Opticks::reset as G4OpticksRecorder detected, should do reset in G4OpticksRecorder::TerminateEvent
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5634 hitCollection_muon 0 hitCollection_opticks 0
    2021-10-30 02:52:36.056 INFO  [51280] [OpticksEvent::save@1972] /tmp/blyth/opticks/source/evt/g4live/natural/-1
    2021-10-30 02:52:36.082 FATAL [51280] [G4Opticks::reset@539]  m_way_enabled reset m_hiys 
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize
    2021-10-30 02:52:36.084 INFO  [51280] [junoSD_PMT_v2_Opticks::Initialize@86]  eventID 1 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 g4ok 0x85e31c0
    Begin of Event --> 1
    2021-10-30 02:52:36.980 INFO  [51280] [PMTEfficiencyCheck::addHitRecord@88]  m_eventID 1 m_record_count 10000
    2021-10-30 02:52:37.121 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@132] [ eventID 1 m_opticksMode 3 numGensteps 127 numPhotons 10840
    2021-10-30 02:52:37.122 INFO  [51280] [OpticksRun::createOKEvent@158]  tagoffset 1 skipaheadstep 0 skipahead 0
    2021-10-30 02:52:37.123 FATAL [51280] [ORng::setSkipAhead@155] skipahead 0

    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 9 numParts 511 perfect tree height 8 exceeds current limit
    // evaluative_csg repeat_index 3 tranOffset 18 numParts 511 perfect tree height 8 exceeds current limit




    2021-10-30 02:52:37.264 INFO  [51280] [OPropagator::launch@285] 0 : (0;10840,1)  launch time 0.140559
    2021-10-30 02:52:37.264 INFO  [51280] [OpIndexer::indexSequenceCompute@237] OpIndexer::indexSequenceCompute
    2021-10-30 02:52:37.276 INFO  [51280] [OEvent::downloadHits@505]  nhit 4211 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-10-30 02:52:37.277 INFO  [51280] [OEvent::downloadHiys@539]  nhiy 4211 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-10-30 02:52:37.277 INFO  [51280] [OpticksEvent::save@1972] /tmp/blyth/opticks/source/evt/g4live/natural/2
    2021-10-30 02:52:37.291 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@156]  eventID 1 num_gensteps 127 num_photons 10840 num_hit 4211 way_enabled 1 waymask 3
    0      gp.x -18162.20  gp.y 648.74     gp.z 6528.92    gp.R 19310.96   pmt 5841    SI|SD|BT|EX          otk 7      oti11.10    bti 103.94   bp.x -16764.92  bp.y 603.67     bp.z 6010.43    bp.R 17820.00  
    1      gp.x 1128.95    gp.y 19308.05   gp.z -823.13    gp.R 19358.54   pmt 9160    SI|RE|SD|BT|EX       otk 7      oti5.17     bti 97.06    bp.x 1067.88    bp.y 17770.23   bp.z -794.31    bp.R 17820.00  
    2      gp.x 8503.14    gp.y -17321.38  gp.z 314.19     gp.R 19298.50   pmt 8671    SI|SC|SD|BT|EC       otk 7      oti10.50    bti 160.02   bp.x 7435.46    bp.y -16194.64  bp.z 6.38       bp.R 17820.00  
    3      gp.x -2035.64   gp.y 18222.05   gp.z 6039.93    gp.R 19304.60   pmt 5999    SI|RE|SD|BT|EX       otk 7      oti7.52     bti 150.60   bp.x -1051.55   bp.y 16565.40   bp.z 6483.37    bp.R 17820.00  
    4      gp.x -14480.18  gp.y -6595.80   gp.z 11014.45   gp.R 19351.96   pmt 3558    SI|SC|SD|BT|EC       otk 7      oti8.16     bti 141.32   bp.x -13393.12  bp.y -7802.28   bp.z 8792.10    bp.R 17820.00  
    5      gp.x 8872.43    gp.y 17013.85   gp.z 1581.18    gp.R 19253.34   pmt 8099    SI|RE|SD|BT|EC       otk 7      oti19.61    bti 120.10   bp.x 8231.81    bp.y 15751.51   bp.z 1296.04    bp.R 17820.00  
    6      gp.x -4729.99   gp.y 16003.19   gp.z -9710.37   gp.R 19307.15   pmt 13499   SI|SC|SD|BT|EX       otk 7      oti3.58     bti 107.17   bp.x -4058.17   bp.y 14829.48   bp.z -9009.46   bp.R 17820.00  
    7      gp.x 9764.73    gp.y 7541.01    gp.z -14794.47  gp.R 19263.78   pmt 15717   SI|SD|BT|EX          otk 7      oti5.60     bti 95.14    bp.x 9035.34    bp.y 6969.14    bp.z -13687.44  bp.R 17820.00  
    8      gp.x -4750.78   gp.y -13931.74  gp.z -12478.99  gp.R 19297.37   pmt 14618   SI|SC|SD|BT|EX       otk 7      oti3.88     bti 146.80   bp.x -4004.33   bp.y -13553.55  bp.z -10854.44  bp.R 17820.00  
    9      gp.x 12214.19   gp.y -3652.20   gp.z -14452.17  gp.R 19271.48   pmt 15570   SI|SD|BT|EX          otk 7      oti5.20     bti 94.45    bp.x 11293.79   bp.y -3368.80   bp.z -13366.15  bp.R 17820.00  
    10     gp.x 8545.70    gp.y 13595.08   gp.z -10664.80  gp.R 19276.75   pmt 13834   SI|RE|SC|SD|BT|EC    otk 7      oti5.53     bti 102.09   bp.x 7109.65    bp.y 13196.00   bp.z -9636.95   bp.R 17820.00  
    11     gp.x 193.23     gp.y -1821.54   gp.z -19185.12  gp.R 19272.37   pmt 17576   SI|SC|SD|BT|EX       otk 7      oti9.37     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    12     gp.x -6752.73   gp.y -15986.50  gp.z 8676.77    gp.R 19402.41   pmt 4680    SI|SD|BT|EX          otk 7      oti1.98     bti 94.54    bp.x -6195.81   bp.y -14692.91  bp.z 7955.05    bp.R 17820.00  
    13     gp.x 5473.42    gp.y 17959.27   gp.z 4529.14    gp.R 19313.39   pmt 6602    SI|SD|BT|EX          otk 7      oti6.53     bti 98.04    bp.x 5065.11    bp.y 16571.93   bp.z 4155.51    bp.R 17820.00  
    14     gp.x 7939.87    gp.y 17661.36   gp.z -791.12    gp.R 19380.17   pmt 9148    SI|SD|BT|EC          otk 7      oti2.99     bti 94.04    bp.x 7314.64    bp.y 16232.18   bp.z -751.41    bp.R 17820.00  
    15     gp.x -10816.68  gp.y 12020.99   gp.z 10566.72   gp.R 19317.36   pmt 3856    SI|RE|SD|BT|EX       otk 7      oti5.30     bti 111.22   bp.x -9909.00   bp.y 11158.50   bp.z 9739.20    bp.R 17820.00  
    16     gp.x 12951.28   gp.y -1642.53   gp.z -14177.19  gp.R 19272.42   pmt 15432   SI|SD|BT|EC          otk 7      oti11.89    bti 101.32   bp.x 11973.35   bp.y -1512.52   bp.z -13111.20  bp.R 17820.00  
    17     gp.x 2087.62    gp.y 10904.70   gp.z -15755.73  gp.R 19274.69   pmt 16124   SI|SD|BT|EX          otk 7      oti2.09     bti 91.59    bp.x 1943.27    bp.y 10072.89   bp.z -14570.96  bp.R 17820.00  
    18     gp.x 3907.19    gp.y -3709.58   gp.z 18539.76   gp.R 19306.73   pmt 326     SI|SD|BT|EC          otk 7      oti2.90     bti 95.66    bp.x 3624.74    bp.y -3423.46   bp.z 17108.29   bp.R 17820.00  
    19     gp.x 13445.74   gp.y 7306.51    gp.z -11776.95  gp.R 19309.83   pmt 14337   SI|SD|BT|EC          otk 7      oti17.35    bti 106.90   bp.x 12406.53   bp.y 6735.94    bp.z -10874.63  bp.R 17820.00  
    2021-10-30 02:52:37.307 INFO  [51280] [junoSD_PMT_v2_Opticks::EndOfEvent@179] ] num_hit 4211 merged_count  0 m_merged_total 0 m_opticksMode 3
    2021-10-30 02:52:37.307 INFO  [51280] [junoSD_PMT_v2_Opticks::TerminateEvent@226]  NOT invoking G4Opticks::reset as G4OpticksRecorder detected, should do reset in G4OpticksRecorder::TerminateEvent
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5567 hitCollection_muon 0 hitCollection_opticks 0
    2021-10-30 02:52:37.307 INFO  [51280] [OpticksEvent::save@1972] /tmp/blyth/opticks/source/evt/g4live/natural/-2
    2021-10-30 02:52:37.332 FATAL [51280] [G4Opticks::reset@539]  m_way_enabled reset m_hiys 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-10-30 02:52:37.333 INFO  [51280] [G4Opticks::Finalize@290] G4Opticks.desc ok 0x99407e0 opmgr 0x192028df0 
    Opticks.desc
                 BOpticksKey  : KEYSOURCE
          spec (OPTICKS_KEY)  : DetSim0Svc.X4PhysicalVolume.pWorld.3dbec4dc3bdef47884fe48af781a179d
                     exename  : DetSim0Svc
             current_exename  : DetSim0Svc
                       class  : X4PhysicalVolume
                     volname  : pWorld
                      digest  : 3dbec4dc3bdef47884fe48af781a179d
                      idname  : DetSim0Svc_pWorld_g4live
                      idfile  : g4ok.gltf
                      idgdml  : g4ok.gdml
                      layout  : 1

    IdPath : /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1

    # BOpticksKey::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.3dbec4dc3bdef47884fe48af781a179d

    2021-10-30 02:52:37.333 FATAL [51280] [G4Opticks::dumpSkipGencode@387] OPTICKS_SKIP_GENCODE m_skip_gencode_count 3
    2021-10-30 02:52:37.333 FATAL [51280] [G4Opticks::dumpSkipGencode@393]  m_skip_gencode_totals[ 0]      0 INVALID
    2021-10-30 02:52:37.333 FATAL [51280] [G4Opticks::dumpSkipGencode@393]  m_skip_gencode_totals[ 0]      0 INVALID
    2021-10-30 02:52:37.333 FATAL [51280] [G4Opticks::dumpSkipGencode@393]  m_skip_gencode_totals[ 0]      0 INVALID
    2021-10-30 02:52:37.333 INFO  [51280] [G4Opticks::finalizeProfile@436] to set path to save the profile set envvar OPTICKS_PROFILE_PATH or use G4Opticks::setProfilePath  
    2021-10-30 02:52:37.333 INFO  [51280] [OpticksProfile::Report@526]  num_stamp 2 profile_leak_mb 0
    Time(s)                   t0 10356.037  t1 10357.291  dt 1.254      dt/(num_stamp-1) 1.254     
    VmSize(MB)                v0 23720.877  v1 23729.057  dv 8.180      dv/(num_stamp-1) 8.180     
    RSS(MB)                   r0 10338.756  r1 10346.708  dr 7.952      dr/(num_stamp-1) 7.952     
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 2
    Delete G4SvcRunManager
    2021-10-30 02:52:37.825 INFO  [51280] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@51]  m_opticksMode 3 m_opticksCtrl - m_event_total 2 m_genstep_total 227 m_photon_total 21805 m_hit_total 8420 m_merged_total 0 m_savegensteps 0 m_savehits 0

    **************************************************
    Terminating @ localhost.localdomain on Sat Oct 30 02:52:38 2021
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully

    [Thread 0x7fff1d7fa700 (LWP 55044) exited]
    [Thread 0x7ffdddfff700 (LWP 55110) exited]

