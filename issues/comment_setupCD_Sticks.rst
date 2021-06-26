comment_setupCD_Sticks
========================


::

    epsilon:offline blyth$ jgr lAddition
    ./Simulation/DetSimV2/CentralDetector/src/AdditionAcrylicConstruction.cc:    if(motherName == "lAddition")
    ./Simulation/DetSimV2/CentralDetector/src/AdditionAcrylicConstruction.cc:            "lAddition",



::


    0555 void
     556 LSExpDetectorConstruction::setupCentralDetector()
     557 {
     558   // construct the Central Detector
     559   IDetElement* cd_det = 0;
     560   if (m_cd_name == "DetSim0" or m_cd_name == "DetSim1" or m_cd_name == "DetSim2") {
     561       std::string new_name = m_cd_name + "Construction";
     562       cd_det = det_elem(new_name);
     563   }
     564 
     565   assert(cd_det);
     566 
     567   de_cd_det = cd_det;
     568 
     569   if (m_cd_name == "DetSim1"){
     570     m_strut_name = "StrutAcrylic";
     571     m_strut2_name="StrutBar2Acrylic";
     572     m_strutballhead_name="StrutBallheadAcrylic";
     573     m_fastener_name = "FastenerAcrylic";
     574     m_pmt_mother = "20inchInnerWater";
     575     m_strut_mother = "lWaterPool";
     576     m_fastener_mother = "lWaterPool";
     577   }else if (m_cd_name == "DetSim2"){
     578     m_strut_name = "StrutBalloon";
     ...

    1359 void
    1360 LSExpDetectorConstruction::setupCD_Sticks(IDetElement* cd_det) {
    ....
    1402 //----------------------------------//
    1403 IDetElement* strutballhead_det = 0;
    1404  IDetElementPos* strutballhead_detelem_pos = 0;
    1405  if (m_strut_name == "StrutAcrylic"){
    1406
    1407    if(m_strutballhead_name == "StrutBallheadAcrylic"){
    1408       std::string new_name = m_strutballhead_name + "Construction";
    1409       strutballhead_det = det_elem(new_name);
    1410       strutballhead_r = strutballhead_r_acrylic;
    1411     }
    1412    assert (strutballhead_det);
    1413    strutballhead_detelem_pos = new JUNO::Ball::HexagonPosBall(m_fastener_pos_file,strutballhead_r,false);
    1414   assert (strutballhead_detelem_pos);
    1415   bool strutballhead_status = cd_det->inject(m_strut_mother, strutballhead_det, strutballhead_detelem_pos);
    1416   assert (strutballhead_status);
    1417   //std::cout<<"stick2 are added in DetSim1"<<std::endl;
    1418  }
    1419   //
    1420 
    1421 
    1422 
    1423 
    1424 
    1425 //--------------------------------------------------------------------
    1426   IDetElement* fastener_det = 0;
    1427   if (m_fastener_name == "FastenerAcrylic") {
    1428       std::string new_name = m_fastener_name + "Construction";
    1429       fastener_det = det_elem(new_name);
    1430       assert(fastener_det);
    1431       IDetElementPos* fastener_detelem_pos = 0;
    1432       fastener_detelem_pos = new JUNO::Ball::HexagonPosBall(m_fastener_pos_file,fastener_r,false);
    1433       assert (fastener_detelem_pos);
    1434       bool fastener_status = cd_det->inject(m_fastener_mother, fastener_det, fastener_detelem_pos);
    1435       assert (fastener_status);
    1436   } else if (m_fastener_name == "FastenerBalloon") {



::

    svn diff Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc

       // === construct Sticks ===
    +
    +#ifdef WITH_G4OPTICKS
    +  LOG(LEVEL) << " OPTICKS DEBUGGING : SKIP LSExpDetectorConstruction::setupCD_Sticks " ; 
    +#else
       setupCD_Sticks(cd_det);
    +#endif



