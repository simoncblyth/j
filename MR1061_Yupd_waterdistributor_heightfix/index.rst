MR1061_Yupd_waterdistributor_heightfix/index
================================================


jcv DetSim1Construction



jcv WaterPoolConstruction



::

    A[blyth@localhost opticks]$ jgr m_waterDistributorLoopTopZ
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    double m_waterDistributorLoopTopZ = 18935*mm;     // Top position of water distributor looppipe
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:            new G4PVPlacement(G4Transform3D(p.rot, G4ThreeVector(0, 0, m_waterDistributorLoopTopZ)), logicLoopOuter, "pWaterDistributorLoopOuterCD_I", logicInnerWaterPool, false, p.copy_no);
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    double m_waterDistributorLoopTopZ = 21409*mm;     // Top position of water distributor loop
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:            new G4PVPlacement(G4Transform3D(p.rot, G4ThreeVector(0, 0, m_waterDistributorLoopTopZ)), logicLoopOuter, p.phy_name, logicWaterPool, false, p.copy_no);



::

    https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1061/diffs?commit_id=b898c6647b5e4d35dbce57dde92152f89ccb63f5



DetSim1Construction::

     18935 -> 18905 -> 18831

           18905 - 18935 =  -30
           18831 - 18905 =  -74
           18831 - 18935 = -104 

WaterPoolConstruction::

     21409 -> 21379 -> 21305

         21379 - 21409 =   -30
         21305 - 21379 =   -74
         21305 - 21409 =  -104  


Compare Z levels : WaterPoolConstruction - DetSim1Construction::

     21409 - 18935 = 2474
     21379 - 18905 = 2474
     21305 - 18831 = 2474 












