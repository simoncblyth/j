jok-tds-GtOpticksTool__configure-input-photons-something-is-missing-error
================================================================================


Issue : jok-tds with input photon running fails with something is missing error message
------------------------------------------------------------------------------------------


FIX approach
---------------

1. remove HighLevel SEvt distinction
2. simplify LSExpDetectorConstruction_Opticks::Setup using G4CXOpticks::SetGeometry_JUNO which invokes SEvt::CreateOrReuse 
3. found that needed to then change GtOpticksTool::mutate to do the input photon checking as the configure happens before SEvt instanciated



Where should instanciation happen ?
-------------------------------------

::

    BP=SEvt::SEvt ~/opticks/CSGOptiX/cxs_min.sh

    (gdb) bt
    #0  0x00007ffff6ee10e0 in SEvt::SEvt()@plt () from /data/blyth/opticks_Debug/lib/../lib64/libSysRap.so
    #1  0x00007ffff6f93d34 in SEvt::Create (ins=0) at /home/blyth/opticks/sysrap/SEvt.cc:1056
    #2  0x00007ffff6f9409f in SEvt::CreateOrReuse (idx=0) at /home/blyth/opticks/sysrap/SEvt.cc:1114
    #3  0x00007ffff6f9449f in SEvt::CreateOrReuse () at /home/blyth/opticks/sysrap/SEvt.cc:1160
    #4  0x00007ffff79cb4e4 in CSGFoundry::AfterLoadOrCreate () at /home/blyth/opticks/CSG/CSGFoundry.cc:3701
    #5  0x00007ffff79c873e in CSGFoundry::Load () at /home/blyth/opticks/CSG/CSGFoundry.cc:3064
    #6  0x00007ffff7bfe3c7 in CSGOptiX::SimulateMain () at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:166
    #7  0x0000000000404a75 in main (argc=1, argv=0x7fffffff48a8) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXSMTest.cc:13
    (gdb) 


::

    3686 /**
    3687 CSGFoundry::AfterLoadOrCreate
    3688 -------------------------------
    3689 
    3690 Called from some high level methods eg: CSGFoundry::Load
    3691 
    3692 The idea behind this is to auto connect SEvt with the frame 
    3693 from the geometry.
    3694 
    3695 **/
    3696 
    3697 void CSGFoundry::AfterLoadOrCreate() // static
    3698 {
    3699     CSGFoundry* fd = CSGFoundry::Get();
    3700 
    3701     SEvt::CreateOrReuse() ;   // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE
    3702 
    3703     if(!fd) return ;
    3704 
    3705     sframe fr = fd->getFrameE() ;
    3706     LOG(LEVEL) << fr ;
    3707     SEvt::SetFrame(fr); // now only needs to be done once to transform input photons
    3708 
    3709 }



Running from persisted rather than live geometry is a bit different, but still expect CSGFoundry::AfterLoadOrCreate
to be called from live geometry. 

It isnt being called. 

::

    P[blyth@localhost junosw]$ opticks-f AfterLoadOrCreate
    ./CSG/CSGFoundry.h:    static void AfterLoadOrCreate(); 
    ./CSG/CSGFoundry.cc:    AfterLoadOrCreate(); 
    ./CSG/CSGFoundry.cc:CSGFoundry::AfterLoadOrCreate
    ./CSG/CSGFoundry.cc:void CSGFoundry::AfterLoadOrCreate() // static
    ./CSGOptiX/CSGOptiX.cc:done in the main is now moved into CSGFoundry::AfterLoadOrCreate
    ./CSGOptiX/CSGOptiX.cc:TODO: see CSGFoundry::AfterLoadOrCreate for maybe auto frame hookup
    P[blyth@localhost opticks]$ 



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
     31     bool opticksMode_valid = opticksMode > -1 && opticksMode <= 3 && integrationMode == opticksMode ;
     32     LOG_IF(fatal, !opticksMode_valid )
     33         << " UNEXPECTED "
     34         << " opticksMode " << opticksMode
     35         << " integrationMode " << integrationMode
     36         ;
     37     assert( opticksMode_valid );
     38 
     39     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     40     const NP* lut = SerializeMultiFilmLUT();
     41     assert(lut);
     42 
     43     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     44     if( opticksMode == 0 )
     45     {
     46         SEvt::HighLevelCreateOrReuse(SEvt::ECPU);    // U4RecorderAnaMgr not active in opticksMode:0 
     47         SSim::Create();                              // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
     48         SSim::AddExtraSubfold("jpmt", jpmt );
     49     }
     50     else if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
     51     {
     52         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ;
     53         //if(opticksMode == 1) SEvt::HighLevelCreateOrReuse(SEvt::ECPU);    // U4RecorderAnaMgr not active in opticksMode:0 
     54         SSim::AddExtraSubfold("jpmt", jpmt );  // needs to be before SetGeometry 
     55         SSim::AddMultiFilm(snam::MULTIFILM, lut);
     56         G4CXOpticks::SetGeometry(world) ;
     57 
     58         G4CXOpticks::SaveGeometry();
     59         //std::cout << ssim->desc();
     60     }
     61     LOG(info) << "] WITH_G4CXOPTICKS " ;
     62     DebugMultiFilmTable();
     63 }






Cause : SEvt::HasInputPhoton giving false because SEvt having not been instanciated
--------------------------------------------------------------------------------------

::

    jcv GtOpticksTool

::

    075 bool GtOpticksTool::configure()
     76 {
     77     bool ret = false  ;
     78 #ifdef WITH_G4CXOPTICKS
     79     ret = SEvt::HasInputPhoton() ;
     80     if(ret == false) std::cerr
     81        << "GtOpticksTool::configure WITH_G4CXOPTICKS"
     82        << " : ERROR : something is missing "
     83        << std::endl
     84        << SEvt::DescHasInputPhoton()
     85        << std::endl
     86        << configure_FAIL_NOTES
     87        ;
     88 #else
     89     std::cerr
     90         << "GtOpticksTool::configure NOT WITH_G4CXOPTICKS"
     91         << " ret " << ( ret ? "true" : "false" )
     92         << std::endl
     93         ;
     94 #endif
     95     return ret ;
     96 }


    1747 bool SEvt::HasInputPhoton(int idx)
    1748 {
    1749     return Exists(idx) ? Get(idx)->hasInputPhoton() : false ;
    1750 }
    1751 bool SEvt::HasInputPhoton()
    1752 {
    1753     return HasInputPhoton(EGPU) || HasInputPhoton(ECPU) ;
    1754 }
    1755 


    1765 std::string SEvt::DescHasInputPhoton()  // static
    1766 {
    1767     std::stringstream ss ;
    1768     ss
    1769        <<  "SEvt::DescHasInputPhoton()  "
    1770        << " SEventConfig::IntegrationMode " << SEventConfig::IntegrationMode()
    1771        << " SEvt::HasInputPhoton(EGPU) " << HasInputPhoton(EGPU)
    1772        << " SEvt::HasInputPhoton(ECPU) " << HasInputPhoton(ECPU)
    1773        << std::endl
    1774        << "SEvt::Brief"
    1775        << std::endl
    1776        << SEvt::Brief()
    1777        << std::endl
    1778        << "SEvt::DescInputPhoton(EGPU)"
    1779        << SEvt::DescInputPhoton(EGPU)
    1780        << "SEvt::DescInputPhoton(ECPU)"
    1781        << SEvt::DescInputPhoton(ECPU)
    1782        << std::endl
    1783        ;
    1784     std::string str = ss.str();
    1785     return str ;
    1786 }




Looks like missing SEvt instanciation, or the tool config happening before geometry converted
-------------------------------------------------------------------------------------------------

::

    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 1 WITH_G4CXOPTICKS 
    junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr FixLightVelAnaMgr
    junotoptask:SniperProfiling.initialize  INFO: 
    GtOpticksTool::configure WITH_G4CXOPTICKS : ERROR : something is missing 
    SEvt::DescHasInputPhoton()   SEventConfig::IntegrationMode 1 SEvt::HasInputPhoton(EGPU) 0 SEvt::HasInputPhoton(ECPU) 0
    SEvt::Brief
    SEvt::Brief  SEvt::Exists(0) N SEvt::Exists(1) N
     SEvt::Get(0)->brief() -
     SEvt::Get(1)->brief() -

    SEvt::DescInputPhoton(EGPU)-SEvt::DescInputPhoton(ECPU)-


    GtOpticksTool::configure_FAIL_NOTES
    =====================================

    GtOpticksTool integrates junosw with Opticks input photon 
    machinery including the frame targetting functionality using 
    the Opticks translated Geant4 geometry.  

    Getting this to work requires:

    1. compilation WITH_G4CXOPTICKS
    2. SEvt::Exists true, this typically requires 
       an opticksNode greater than zero, configure with 
       the tut_detsim.py option "--opticks-mode 1/2/3"  
    3. OPTICKS_INPUT_PHOTONS envvar identifying an 
       existing .npy file containing the photons

    To disable use of GtOpticksTool input photons simply replace 
    the "opticks" argument on the tut_detsim.py commandline 
    with for example "gun". 


    junotoptask:GenTools.initialize  INFO: configure tool "ok" failed
    junotoptaskalgorithms.initialize ERROR: junotoptask:GenTools initialize failed
    [2024-10-31 10:48:04,677] p271603 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:201} INFO - ]JUNOApplication.run
    [Thread 0x7fffd03dd700 (LWP 271741) exited]
    junotoptask.finalize            WARN: try to finalize within error
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully





shakedown
--------------

::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists(0) Y SEvt::Exists(1) N
     SEvt::Get(0)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     SEvt::Get(1)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )
    GtOpticksTool::mutate event_number 0 numPhotons 10000
     idx 0 event.event_number 0 wavelength_nm 440.00 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 1 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 2 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 3 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 4 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 5 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 6 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 7 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    2024-10-31 15:36:05.305 INFO  [333855] [junoSD_PMT_v2_Opticks::Initialize@106]  opticksMode 1 eventID 0 LEVEL 4:INFO
    Begin of Event --> 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    (gdb) bt
    #0  0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #1  0x00007fffc644f3d0 in G4MultiUnion::InsideWithExclusion(CLHEP::Hep3Vector const&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #2  0x00007fffc644742d in G4DisplacedSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #3  0x00007fffc6455e37 in G4UnionSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #4  0x00007fffc641cbc3 in G4Navigator::LocateGlobalPointAndSetup(CLHEP::Hep3Vector const&, CLHEP::Hep3Vector const*, bool, bool) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #5  0x00007fffc77b8ccb in G4Transportation::PostStepDoIt(G4Track const&, G4Step const&) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #6  0x00007fffcc0ab679 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffcc0aba7b in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffcc0a92b4 in G4SteppingManager::Stepping() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffcc0b487f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffcc0f056d in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffbe3f568e in G4SvcRunManager::SimulateEvent (this=0x6554510, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #12 0x00007fffbdabdd3e in DetSimAlg::execute (this=0x6c046d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #13 0x00007fffcf865511 in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffcf869c1d in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffcf8650b4 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



Problem with G4MultiUnion ?::

    P[blyth@localhost issues]$ jgr G4MultiUnion
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:#include "G4MultiUnion.hh"
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:   combine screws into G4MultiUnion and union that with the IonRing 
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:    G4MultiUnion* muni = nullptr ;  
    ./Simulation/DetSimV2/CentralDetector/src/FastenerAcrylicConstruction.cc:        muni = new G4MultiUnion(name) ;
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:#include "G4MultiUnion.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4MultiUnion* solidDeadWater_multiunion_holes = CONFIG == MULTIUNION_HOLES ? new G4MultiUnion("sDeadWater_multiunion_holes") : nullptr ;
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4MultiUnion* solidTyvek_multiunion_holes = CONFIG == MULTIUNION_HOLES ? new G4MultiUnion("sTyvek_multiunion_holes") : nullptr ;
    P[blyth@localhost junosw]$ 



::

    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists(0) Y SEvt::Exists(1) N
     SEvt::Get(0)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     SEvt::Get(1)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )
    GtOpticksTool::mutate event_number 0 numPhotons 10000
     idx 0 event.event_number 0 wavelength_nm 440.00 energy/eV      2.818 post[  -3191.910  10522.318  15746.385] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 1 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.898  10522.279  15746.413] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 2 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.886  10522.239  15746.441] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 3 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.874  10522.200  15746.469] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 4 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.862  10522.160  15746.497] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 5 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.850  10522.121  15746.525] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 6 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.838  10522.081  15746.554] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 7 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.826  10522.042  15746.581] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 8 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.814  10522.002  15746.609] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
     idx 9 event.event_number 0 wavelength_nm 440.000 energy/eV      2.818 post[  -3191.802  10521.963  15746.638] dir[     -0.163      0.538      0.827] pol[     -0.957     -0.290      0.000]
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    2024-10-31 15:56:49.458 INFO  [371510] [junoSD_PMT_v2_Opticks::Initialize@106]  opticksMode 1 eventID 0 LEVEL 4:INFO
    Begin of Event --> 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    (gdb) bt
    #0  0x00007fffc651c260 in G4Voxelizer::GetCandidatesVoxelArray(CLHEP::Hep3Vector const&, std::vector<int, std::allocator<int> >&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #1  0x00007fffc644f3d0 in G4MultiUnion::InsideWithExclusion(CLHEP::Hep3Vector const&, G4SurfBits*) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #2  0x00007fffc644742d in G4DisplacedSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #3  0x00007fffc6455e37 in G4UnionSolid::Inside(CLHEP::Hep3Vector const&) const () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #4  0x00007fffc641cbc3 in G4Navigator::LocateGlobalPointAndSetup(CLHEP::Hep3Vector const&, CLHEP::Hep3Vector const*, bool, bool) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so
    #5  0x00007fffc77b8ccb in G4Transportation::PostStepDoIt(G4Track const&, G4Step const&) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #6  0x00007fffcc0ab679 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffcc0aba7b in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffcc0a92b4 in G4SteppingManager::Stepping() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffcc0b487f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffcc0f056d in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #11 0x00007fffbe3f568e in G4SvcRunManager::SimulateEvent (this=0x6554510, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #12 0x00007fffbdabdd3e in DetSimAlg::execute (this=0x6c046d0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112



Try removing the FastenerAcrylicConstruction muni by switching to FAC_ASIS works:: 

    152    local FAC_ASIS=0                   # geometry is present but does not render
    153    local FAC_MULTIUNION_CONTIGUOUS=1 
    154    local FAC_MULTIUNION_DISCONTIGUOUS=2
    155    #export FastenerAcrylicConstruction__CONFIG=$FAC_MULTIUNION_DISCONTIGUOUS
    156    export FastenerAcrylicConstruction__CONFIG=$FAC_ASIS
    157    #export U4Solid__IsFlaggedType=G4MultiUnion






