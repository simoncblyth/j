opticksMode
=============


::

    A[blyth@localhost junosw]$ jgl opticksMode
    ./Doc/oum/source/quickstart/quickstart.md
    ./Simulation/DetSimV2/DetSimOptions/include/DetSim0Svc.hh                         ##  (int)m_opticksMode member
    ./Simulation/DetSimV2/DetSimOptions/include/JUNOPhyParaTool.hh                    ##  (int)m_opticksMode member
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh          ##  setOpticksMode and (int)m_opticksMode member 
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh  ##  Setup argument 
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc                             ## declProp("OpticksMode", m_opticksMode=0);



    105 bool
    106 DetSim0Svc::initialize()
    107 {
    108     if(m_opticksMode > 0)
    109     {
    110         initializeOpticks();
    111     }
    112 
    113     MgrOfAnaElem& mgr = MgrOfAnaElem::instance();
    114     // register
    115     if (m_ana_list.size() == 0) {
    116         LogWarn << "No Analysis Element is found." << std::endl;
    117         // m_ana_list.push_back("NormalAnaMgr");
    118     }
    119     // TODO


    172 bool
    173 DetSim0Svc::finalize()
    174 {
    175     if(m_opticksMode > 0 )
    176     {
    177         finalizeOpticks();
    178     }
    179 
    180     return true;
    181 }

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
    337 
    338 bool DetSim0Svc::finalizeOpticks()
    339 {
    340     dumpOpticks("DetSim0Svc::finalizeOpticks");
    341     assert( m_opticksMode > 0);
    342 
    343 #ifdef WITH_G4CXOPTICKS
    344     G4CXOpticks::Finalize();
    345 #else
    346     LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS  " << std::endl ;
    347     assert(0);
    348 #endif
    349     return true;
    350 }







    ./Simulation/DetSimV2/DetSimOptions/src/JUNOPhyParaTool.cc                 ## declProp("OpticksMode", m_opticksMode=0);


    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc

         LSExpDetectorConstruction_Opticks::Setup( m_opticksMode, world, m_sd, pps_d, psps_d, pmtscan );



    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc


         Note the G4CXOpticks::SetGeometry_JUNO is called for all valid opticksMode 0/1/2/3

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




  
    ./Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h      ## get_meta_array method uses NP
    ./Simulation/DetSimV2/PMTSim/include/PMTSDMgr.hh               ## m_opticksMode member
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh          ## m_opticksMode member and get method 
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh  ## m_opticksMode member
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc                   ## instanciates junoSD_PMT_v2 with opticksMode argument
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc              ## 


        1090 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
        1091 {
        1092 #ifdef WITH_G4CXOPTICKS
        1093     m_jpmt_opticks->EndOfEvent(HCE, m_eventID );
        1094 #endif
        1095     G4cout << "junoSD_PMT_v2::EndOfEvent" << desc() << G4endl ;
        1096 }

        1098 bool junoSD_PMT_v2::gpu_simulation() const { return m_opticksMode == 1 || m_opticksMode == 3 ;  }


 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc


         165 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )    ## G4CXOpticks::simulate, collectHit, G4CXOpticks::reset



    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h           ## member  
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh        ## param
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h           ## param, member
    ./Simulation/DetSimV2/PhysiSim/include/G4Cerenkov_modified.hh        ## member, get/set
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc              ## pass opticksMode to processes
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc            ## 


        338   if(fOpticksMode == 0 || (fOpticksMode & 2))
        339   {
        340 
        341   for (G4int i = 0; i < fNumPhotons; i++) {
        342 



    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc



