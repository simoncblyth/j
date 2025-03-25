OPTICKS_INTEGRATION_MODE
=========================


::


    LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 1 WITH_G4CXOPTICKS  proceeding to setup Opticks 
    LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan 
    2025-03-24 10:01:00.661 FATAL [3539889] [LSExpDetectorConstruction_Opticks::Setup@33]  UNEXPECTED  opticksMode 1 integrationMode -1
    python: /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:38: static void LSExpDetectorConstruction_Opticks::Setup(int, const G4VPhysicalVolume*, const G4VSensitiveDetector*, PMTParamData*, PMTSimParamData*, NPFold*): Assertion `opticksMode_valid' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc3359df4 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0x90830d0, sd=0x92910c0, ppd=0x67ba2d0, psd=0x67bb4b0, pmtscan=0x0)
        at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:38
    #6  0x00007fffc3329bf6 in LSExpDetectorConstruction::setupOpticks (this=0x8dfde80, world=0x90830d0)
        at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:457
    #7  0x00007fffc3329496 in LSExpDetectorConstruction::Construct (this=0x8dfde80) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:378
    #8  0x00007fffcb46392e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x00007fffcb463afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.2.3/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #10 0x00007fffcf349b1b in DetSimAlg::initialize (this=0x695e420) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80

::

     21 void LSExpDetectorConstruction_Opticks::Setup(
     22           int opticksMode,
     23           const G4VPhysicalVolume* world,
     24           const G4VSensitiveDetector* sd,
     25           PMTParamData* ppd,
     26           PMTSimParamData* psd,
     27           NPFold* pmtscan
     28           )
     29 {
     30     int integrationMode = SEventConfig::IntegrationMode();
     31     bool opticksMode_valid =
     32          ( opticksMode == 0 || opticksMode == 1 || opticksMode == 2 || opticksMode == 3 )  && opticksMode == integrationMode ;
     33     LOG_IF(fatal, !opticksMode_valid )
     34         << " UNEXPECTED "
     35         << " opticksMode " << opticksMode
     36         << " integrationMode " << integrationMode
     37         ;
     38     assert( opticksMode_valid );




python level is too late ? have to do it before load any opticks libs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost junosw]$ git diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    diff --git a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    index 1fcac098..c8c7c9ed 100644
    --- a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    +++ b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    @@ -1795,6 +1795,7 @@ class JUNODetSimModule(JUNOModule):
             log.info("LPMTExtra %s --pmt20inch-extra " % args.pmt20inch_extra)
     
             detsimfactory.property("OpticksMode").set(args.opticks_mode)
    +        os.environ["OPTICKS_INTEGRATION_MODE"] = args.opticks_mode
     
             #--------------------------------------------------------------------#    
             if args.new_optical_model:
    A[blyth@localhost junosw]$ 






::

    A[blyth@localhost junosw]$ git diff Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    diff --git a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    index 1fcac098..a33c530c 100644
    --- a/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    +++ b/Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    @@ -420,7 +420,8 @@ class JUNODetSimModule(JUNOModule):
     
             #     
             # == opticks ==
    -        grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=0,
    +        default_opticks_mode = 1 if "OPTICKS_PREFIX" in os.environ else 0
    +        grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=default_opticks_mode,
                                     help=mh("Control Opticks GPU Optical simulation"))
             grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
                                     help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
    @@ -1795,6 +1796,7 @@ class JUNODetSimModule(JUNOModule):
             log.info("LPMTExtra %s --pmt20inch-extra " % args.pmt20inch_extra)
     
             detsimfactory.property("OpticksMode").set(args.opticks_mode)
    +        os.environ["OPTICKS_INTEGRATION_MODE"] = args.opticks_mode
     
             #--------------------------------------------------------------------#    
             if args.new_optical_model:
    A[blyth@localhost junosw]$ 

