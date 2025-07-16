index
=======


Zhenning reports GPU slurm job error
--------------------------------------


::

Total Number of UnknownVolume in CD is 39

LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 1 WITH_G4CXOPTICKS  proceeding to setup Opticks

LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan

U::Resolve token [MultiFilmLUTMakerSvc_DIR] does not resolve

NP::save failed to U::Resolve path_ $MultiFilmLUTMakerSvc_DIR/multifilm.npy

2025-07-16 09:27:31.822 INFO  [142619] [LSExpDetectorConstruction_Opticks::Setup@45] [ WITH_G4CXOPTICKS opticksMode 1 sd 0x61d4c90

SNiPER is stopped by Ctrl+C



**************************************************

Terminating @ gpu032.ihep.ac.cn on Wed Jul 16 09:27:32 2025

SNiPER::Context Running Mode = { BASIC }

SNiPER::Context SNiPER is stopped by Ctrl+C



I guess I may have missed setting some critical environment variables, but I'm
unsure how to verify this. Since I can submit the slurm job and the detector
simulation begins initializing (with normal log output), the issue likely isn’t
related to the SLURM cluster itself.

Regards,

Zhenning



Find where the message "SNiPER is stopped by Ctrl+C" comes from 
-----------------------------------------------------------------




::

    zeta:~ blyth$ cd /tmp
    zeta:tmp blyth$ git clone https://github.com/SNiPER-Framework/sniper.git
    Cloning into 'sniper'...
    remote: Enumerating objects: 1897, done.
    remote: Counting objects: 100% (317/317), done.
    remote: Compressing objects: 100% (125/125), done.
    remote: Total 1897 (delta 238), reused 193 (delta 190), pack-reused 1580 (from 1)
    Receiving objects: 100% (1897/1897), 383.10 KiB | 520.00 KiB/s, done.
    Resolving deltas: 100% (1281/1281), done.


    zeta:tmp blyth$ find sniper -type f -exec grep -H "SNiPER is stopped by Ctrl+C" {} \;
    sniper/SniperKernel/src/SniperCapsule.cc:        sniper_context->reg_msg("SNiPER is stopped by Ctrl+C");
    sniper/SniperKernel/src/SniperCapsule.cc:        std::cout << "SNiPER is stopped by Ctrl+C" << std::endl;
    zeta:tmp blyth$ 



sniper/SniperKernel/src/SniperCapsule.cc::

     24 //global variables
     25 Sniper::Context *sniper_context;
     26 
     27 //the function decalarations for library initialize and finalize
     28 void sniper_kernel_initialize() __attribute__((constructor));
     29 void sniper_kernel_finalize() __attribute__((destructor));
     30 
     31 //the function decalaration for signal handling
     32 void sniper_sig_handler(int signum);
     33 
     34 //definition of sniper_kernel_initialize
     35 void sniper_kernel_initialize()
     36 {
     37     sniper_context = new Sniper::Context();
     38     sigset(SIGINT, sniper_sig_handler);
     39 }
     40 
     41 //definition of sniper_kernel_finalize
     42 void sniper_kernel_finalize()
     43 {
     44     delete sniper_context;
     45 }
     46 
     47 //definition of sniper_sig_handler
     48 void sniper_sig_handler(int signum)
     49 {
     50     switch (signum)
     51     {
     52     case SIGINT:
     53         sniper_context->reg_msg("SNiPER is stopped by Ctrl+C");
     54         std::cout << "SNiPER is stopped by Ctrl+C" << std::endl;
     55         exit(0);
     56     default:; //pass
     57     }
     58 }



This shows the error is due to a SIGINT being thrown
-----------------------------------------------------

Question is why and what threw the SIGINT.  
This could be slurm signalling that the job has used too much time or memory.


Look for what could have thrown the SIGINT
-------------------------------------------

Trace the logging::

    2025-07-16 09:27:31.822 INFO  [142619] [LSExpDetectorConstruction_Opticks::Setup@45] [ WITH_G4CXOPTICKS opticksMode 1 sd 0x61d4c90

    SNiPER is stopped by Ctrl+C



jcv LSExpDetectorConstruction_Opticks::

     21 void LSExpDetectorConstruction_Opticks::Setup(
     22           int opticksMode,
     23           const G4VPhysicalVolume* world, 
     24           const G4VSensitiveDetector* sd, 
     25           PMTParamData* ppd, 
     26           PMTSimParamData* psd,
     27           NPFold* pmtscan 
     28           )
     29 {
     30     SEventConfig::SetIntegrationMode(opticksMode);
     31     int integrationMode = SEventConfig::IntegrationMode(); 
     32     bool opticksMode_valid = 
     33          ( opticksMode == 0 || opticksMode == 1 || opticksMode == 2 || opticksMode == 3 )  && opticksMode == integrationMode ; 
     34     LOG_IF(fatal, !opticksMode_valid ) 
     35         << " UNEXPECTED "
     36         << " opticksMode " << opticksMode 
     37         << " integrationMode " << integrationMode 
     38         ; 
     39     assert( opticksMode_valid );  
     40           
     41     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ; 
     42     const NP* jlut = SerializeMultiFilmLUT();
     43     assert(jlut);
     44           
     45     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ; 
     46           
     47     G4CXOpticks::SetGeometry_JUNO(world, sd, jpmt, jlut ); 
     48 
     49     LOG(info) << "] WITH_G4CXOPTICKS " ; 
     50     DebugMultiFilmTable();
     51 }         




     87 G4CXOpticks* G4CXOpticks::SetGeometry_JUNO(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd, NPFold* jpmt, const NP* jlut )
     88 {
     89     LOG(LEVEL) << "[" ;
     90 
     91     // boot SSim adding extra juno PMT info
     92     SSim::CreateOrReuse();   // done previously by G4CXOpticks::G4CXOpticks in opticksMode > 0 or here in opticksMode:0
     93     SSim::AddExtraSubfold("jpmt", jpmt );
     94     SSim::AddMultiFilm(snam::MULTIFILM, jlut);
     95 
     96     SEvt::CreateOrReuse() ;  // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE (which via above assert matches opticksMode)
     97 
     98 
     99     int opticksMode = SEventConfig::IntegrationMode();
    100     if(opticksMode == 0 || opticksMode == 2) SetNoGPU() ;
    101 
    102     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
    103 
    104     G4CXOpticks* gx = nullptr ;
    105 
    106     if( opticksMode == 0 || opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
    107     {
    108         gx = SetGeometry(world) ;
    109         SaveGeometry();
    110     }
    111 
    112     LOG(LEVEL) << "]" ;
    113     return gx ;
    114 }


Opticks logging can be switched on for relevant classes with the below envvar exports, 
so I added the below after the sourcing of envset.sh::


    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.0/el9_amd64_gcc11/2025_07_07/envset.sh


    logging(){
       type $FUNCNAME
       export G4CXOpticks=INFO
       export SSim=INFO
       export SEvt=INFO
       export SEventConfig=INFO
    }
    logging  # add logging for debug of "SNiPER is stopped by Ctrl+C" ie SIGINT









