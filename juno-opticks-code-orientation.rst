juno-opticks-code-orientation
=================================

It is important for you to start to get familiar with the code, so you can do more than just 
say there are differences and start to investigate causes.
Also once you are able to find your way around the code you can 
answer your own questions. 

Lets take a look at the code using the jgr and jcv bash functions.

Notice the default argument of jgr is G4OPTICKS, so it finds all the sources 
in the Offline relevant to Opticks 

::

    epsilon:offline blyth$ t jgr
    jgr () 
    { 
        cd_func $JUNOTOP/offline;
        jgr- $*;
        : search files with the query string and show matches - skips are made to avoid cmt garbage
    }
    epsilon:offline blyth$ t jgr-
    jgr- () 
    { 
        find . ! -path "./.svn/*" -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh' -type f -exec grep -H "${1:-G4OPTICKS}" {} \;
    }
    epsilon:offline blyth$ t jgr
    jgr () 
    { 
        cd_func $JUNOTOP/offline;
        jgr- $*;
        : search files with the query string and show matches - skips are made to avoid cmt garbage
    }
    epsilon:offline blyth$ 


Another useful function is jcv, that allows you to look at a all files 
with a particular stem. For example::

         
    epsilon:offline blyth$ jcv junoSD_PMT_v2_Opticks
    2 files to edit
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    epsilon:offline blyth$ 


    epsilon:offline blyth$ t jcv
    jcv () 
    { 
        cd_func $JUNOTOP/offline;
        jcv- $*;
        : edit files identified by stem
    }
    epsilon:offline blyth$ t jcv-
    jcv- () 
    { 
        local fi=$(jcl $* | sort);
        [ "$fi" != "" ] && vi $fi;
        echo $fi | tr " " "\n"
    }
    epsilon:offline blyth$ t jcl
    jcl () 
    { 
        local f="";
        for name in $*;
        do
            f="$f -name $name.* -o ";
        done;
        find . \( $f -false \) -a ! -path './*/Linux-x86_64/*'
    }
    epsilon:offline blyth$ 



In the below I explain the important files to be familiar with, 
use commands like the below to study the sources::
  
    jcv DsG4Scintillation
    icv junoSD_PMT_v2_Opticks

    epsilon:offline blyth$ jgr    

    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:               << " FATAL : non-zero opticksMode requires compilation -DWITH_G4OPTICKS " 
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:           << " FATAL : non-zero opticksMode requires compilation -DWITH_G4OPTICKS “ 

    ## these are where the gensteps are collected

    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:               << " non-zero opticksMode requires compilation -DWITH_G4OPTICKS “ 

    ## this is where the above scintillation and cerenkov processes are configured

    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:#ifdef WITH_G4OPTICKS

    ## this class invokes the Opticks GPU propagation and handles the returned hits
    ## converting them into junoHit_PMT 



::

    011 /**
     12 junoSD_PMT_v2_Opticks
     13 =======================
     14 
     15 Invokes Opticks GPU optical photon simulation at the EndOfEvent.
     16 
     17 **/
     18 class junoSD_PMT_v2_Opticks
     19 {
     20     public:
     21         junoSD_PMT_v2_Opticks( junoSD_PMT_v2* jpmt);
     22         virtual ~junoSD_PMT_v2_Opticks();
     23 
     24 #ifdef WITH_G4OPTICKS
     25     public:
     26         void EndOfEvent(G4HCofThisEvent*);
     27     private:
     28         void collectHit(const G4OpticksHit* hit, const G4OpticksHitExtra* hit_extra, int& merged_count );
     29         void dumpHit(unsigned idx, const G4OpticksHit* hit, const G4OpticksHitExtra* hit_extra ) const ;
     30         junoHit_PMT* convertHit(const G4OpticksHit* hit, const G4OpticksHitExtra* hit_extra ) const ;
     31 #endif
     32     private:
     33         junoSD_PMT_v2*        m_jpmt ;
     34         int                   m_opticksMode ;
     35         PMTHitMerger*         m_pmthitmerger_opticks ;
     36     private:
     37         unsigned              m_event_total ;
     38         unsigned              m_genstep_total ;
     39         unsigned              m_photon_total ;
     40         unsigned              m_hit_total ;
     41         unsigned              m_merged_total ;
     42 };
        

    127 void junoSD_PMT_v2_Opticks::collectHit(const G4OpticksHit* hit, const G4OpticksHitExtra* hit_extra, int& merged_count )
    128 {
    129     assert( m_pmthitmerger_opticks );
    130     bool merged = false ;
    131     if(m_pmthitmerger_opticks->getMergeFlag())
    132     {
    133         merged = m_pmthitmerger_opticks->doMerge(hit->sensor_identifier, hit->time);
    134     }
    135     if(merged)
    136     {
    137         merged_count += 1 ;
    138     }
    139     else
    140     {
    141         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    142         m_pmthitmerger_opticks->saveHit(hit_photon);
    143     }
    144 }


::

    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc:#ifdef WITH_G4OPTICKS

      ## you should know about this already, it checks the ProcessHit efficiencies
      ## match the ones Opticks collects  


    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4OPTICKS_CHECK_EFFICIENCY


     The below is where the GPU propagation is done and hits handled.
     Notice the output line from the logging that shows that hitCollection_opticks is filled.

    2021-04-27 19:43:46.681 INFO  [74863] [G4Opticks::resetCollectors@544] [
    2021-04-27 19:43:46.681 INFO  [74863] [G4Opticks::resetCollectors@555] ]
    2021-04-27 19:43:46.789 FATAL [74863] [G4Opticks::reset@526]  m_way_enabled reset m_hiys 
    ]] junoSD_PMT_v2_Opticks::EndOfEvent  num_hit 15774984 merged_count  0 m_merged_total 0 m_opticksMode 1
    junoSD_PMT_v2::EndOfEvent m_opticksMode 1 hitCollection 0 hitCollection_muon 0 hitCollection_opticks 15774984
    junotoptask:DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2021-04-27 11:43:46.841605000Z
    junotoptask:DataModelWriterWithSplit.EndOfEventAction  WARN: No Hit produced


     975 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
     976 {
     977 
     978 #ifdef WITH_G4OPTICKS
     979     if(m_opticksMode > 0)
     980     {
     981         // Opticks GPU optical photon simulation and bulk hit population is done here 
     982         m_jpmt_opticks->EndOfEvent(HCE);
     983     }
     984 #endif
     985 
     986     //if(m_debug) {
     987     {
     988         G4cout
     989             << "junoSD_PMT_v2::EndOfEvent"
     990             << " m_opticksMode " << m_opticksMode
     991             << " hitCollection " << hitCollection->entries()
     992             << " hitCollection_muon " << hitCollection_muon->entries()
     993             << " hitCollection_opticks " << (hitCollection_opticks?hitCollection_opticks->entries():0)
     994             << G4endl
     995             ;
     996     }
     997 
     998 #ifdef WITH_G4OPTICKS_CHECK_EFFICIENCY
     999     // efficiency checking does not use GPU, but it does use Opticks types 
    1000     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
    1001     G4int eventID = event->GetEventID() ;
    1002 
    1003     m_PMTEfficiencyCheck->EndOfEvent(eventID);
    1004 #endif
    1005 
    1006 }



    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:#ifdef WITH_G4OPTICKS

       ## this creates a separate pmthitmerger_opticks for Opticks

     jcv PMTSDMgr

     
     91     } else if (m_pmt_sd == "junoSD_PMT_v2") {
     92         junoSD_PMT_v2* sd = new junoSD_PMT_v2(objName(), m_opticksMode);
     93         // As a merger is attached to a specific SD, so also create new merger for the new SD.
     94         PMTHitMerger* pmthitmerger = new PMTHitMerger();
     95 #ifdef WITH_G4OPTICKS
     96         PMTHitMerger* pmthitmerger_opticks = new PMTHitMerger();
     97 #else
     98         PMTHitMerger* pmthitmerger_opticks = NULL ;
     99 #endif
    100 



    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:       << " WITH_G4OPTICKS "
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:       << " **NOT** WITH_G4OPTICKS “ 


    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ; 
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:       << " WITH_G4OPTICKS "
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:       << " **NOT** WITH_G4OPTICKS “ 


         ## Both of these are for initialize/finalize

       
    epsilon:offline blyth$ jcv DetFactorySvc
    2 files to edit
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.hh
    epsilon:offline blyth$ 


    220 bool DetFactorySvc::initializeOpticks()
    221 {   
    222     dumpOpticks("DetFactorySvc::initializeOpticks");
    223     assert( m_opticksMode > 0);
    224 
    225 #ifdef WITH_G4OPTICKS
    226     OPTICKS_ELOG("DetFactorySvc");
    227 #else
    228     LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ;
    229     assert(0);
    230 #endif
    231     return true ;
    232 }
    233 
    234 bool DetFactorySvc::finalizeOpticks()
    235 {   
    236     dumpOpticks("DetFactorySvc::finalizeOpticks");
    237     assert( m_opticksMode > 0);
    238 
    239 #ifdef WITH_G4OPTICKS
    240     G4Opticks::Finalize();
    241 #else
    242     LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4OPTICKS " << std::endl ;
    243     assert(0);
    244 #endif
    245     return true;
    246 }
    247 


    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#ifdef WITH_G4OPTICKS
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:    LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:    LOG(info) << "] WITH_G4OPTICKS " ; 


       ## This is an important one to be familiar with, it is where the command line for the embedded Opticks is setup 
       ## and the Geant4 geometry is passed to G4Opticks for translation 

    epsilon:offline blyth$ jcv LSExpDetectorConstruction_Opticks
    2 files to edit
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    epsilon:offline blyth$ 



    84 G4Opticks* LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd_, int opticksMode )  // static
     85 {
     86     if( opticksMode == 0 ) return nullptr ;
     87     LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ;
     88 
     89     assert(world);
     90 
     91     // 1. pass geometry to Opticks, translate it to GPU and return sensor placements  
     92 
     93     G4Opticks* g4ok = new G4Opticks ;
     94 
     95     bool outer_volume = true ;
     96     bool profile = true ;
     97 
     98     const char* geospecific_default =   "--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge" ;  // (1): gives radius 17820
     99     const char* embedded_commandline_extra = SSys::getenvvar("LSXDC_GEOSPECIFIC", geospecific_default ) ;
    100     LOG(info) << " embedded_commandline_extra " << embedded_commandline_extra ;
    101 
    102     g4ok->setPlacementOuterVolume(outer_volume);
    103     g4ok->setProfile(profile);
    104     g4ok->setEmbeddedCommandLineExtra(embedded_commandline_extra);
    105     g4ok->setGeometry(world);
    106 
    107     const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements() ;
    108     unsigned num_sensor = sensor_placements.size();
    109 
    110     // 2. use the placements to pass sensor data : efficiencies, categories, identifiers  
    111 
    112     const junoSD_PMT_v2* sd = dynamic_cast<const junoSD_PMT_v2*>(sd_) ;
    113     assert(sd) ;
    114 
           



    ./Examples/FirstAlg/cmt/requirements:             opticks " -DWITH_G4OPTICKS "
    ./Examples/FirstAlg/src/FirstAlg.cc:#ifdef WITH_G4OPTICKS

         ## This is not important, just some demo from Tao


    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            g4okbr_root = os.environ.get("G4OPTICKSBRIDGEROOT",None) 

         ## thus is part of the implementation of tut_detsim.py      

          



