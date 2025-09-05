WaterDistributer/pipeA
========================

::

    A[blyth@localhost env]$ jgr pipeA
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    // Construct pipeA (straight pipe) with G4Polycone
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    G4Polycone* pipeA = new G4Polycone("pipeA", 0, 360*deg, 2, zPlaneA, rInnerA, rOuterA);
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:            pipeA,
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:    G4Tubs* pipeA = new G4Tubs("pipeA", 0, pipe_radius, A_length/2, 0, 360*deg);
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        pipeA,
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc:        pipeA,
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Tubs* pipeA = new G4Tubs("pipeA", 0, pipe_radius, A_length/2, 0, 360*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        pipeA,
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Polycone* pipeA = new G4Polycone("pipeA", 0, 360*deg, 2, zPlaneA, rInnerA, rOuterA);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4LogicalVolume* logicPipeA = new G4LogicalVolume(pipeA, Steel, "logicPipeA");
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    G4Tubs* pipeA = new G4Tubs("pipeA", 0, pipe_radius, A_length/2, 0, 360*deg);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:        pipeA,
    A[blyth@localhost junosw]$ 



jcv DetSim1Construction
---------------------------

::

     509 G4VSolid*
     510 DetSim1Construction::helper_subtract_water_distributor(G4VSolid* solid_input) {
     511     G4VSolid* solid_output = solid_input;
     512     G4String name = solid_input->GetName() + "SubWaterDistributor";
     513 


     619 void
     620 DetSim1Construction::makeOuterReflectorLogical() {
     621     RoundBottomFlaskSolidMaker rbfs("sOuterReflectorInCD",
     622                                     m_radOuterReflector,             // 
     623                                     m_radReflectorChimney,      // 
     624                                     m_heightWP/2 + m_waterPoolHeightplus,
     625                                     m_radReflectorBotChimney,   //
     626                                     m_ChimneyBotToCenter, // todo
     627                                     TOPTOEQUATORH,
     628                                     BOTTOEQUATORH);
     629     solidOuterReflector = rbfs.getSolid();
     630     solidOuterReflector = helper_subtract_water_distributor(solidOuterReflector);
     631 
     632     logicOuterReflector = new G4LogicalVolume(solidOuterReflector,
     633                                          Tyvek,
     634                                          "lOuterReflectorInCD",
     635                                          0,
     636                                          0,
     637                                          0);





jcv UpperWaterDistributer

jcv WaterPoolConstruction






