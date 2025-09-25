

(ok) A[blyth@localhost junosw]$ git status
On branch yupd-water-distributor
Your branch is behind 'origin/yupd-water-distributor' by 7 commits, and can be fast-forwarded.
  (use "git pull" to update your local branch)

nothing to commit, working tree clean
(ok) A[blyth@localhost junosw]$ git pull
Updating 12b13323..d933eb64
Fast-forward
 Examples/Tutorial/python/Tutorial/JUNODetSimModule.py                                                                |   5 +-
 Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh                                                   |  15 +-
 Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributer.hh => UpperWaterdistributor.hh}                   |  24 ++-
 Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributerPlacement.hh => UpperWaterdistributorPlacement.hh} |   6 +-
 Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh                                         |  38 -----
 Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh                                         |  58 +++++++
 Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh                                             |  54 ++++++
 Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc                                                       | 340 +++++++++++++++++++++++--------------
 Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc                                                         |   5 +
 Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributer.cc => UpperWaterdistributor.cc}                       |  48 +++---
 Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributerPlacement.cc => UpperWaterdistributorPlacement.cc}     |  14 +-
 Simulation/DetSimV2/CentralDetector/src/{WaterdistributerlooppipeMaker.cc => WaterdistributorlooppipeMaker.cc}       |  17 +-
 Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc                                                 | 269 ++++++++++++++++++++++++++++++
 Simulation/DetSimV2/Chimney/include/UpperChimneyMaker.hh                                                             |   1 +
 Simulation/DetSimV2/Chimney/src/UpperChimney.cc                                                                      |   8 +-
 Simulation/DetSimV2/Chimney/src/UpperChimneyPlacement.cc                                                             |  16 +-
 Simulation/DetSimV2/DetSimOptions/include/GlobalGeomInfo.hh                                                          |   1 +
 Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh                                               |   8 +-
 Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh                                                   |  10 +-
 Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py                                                |  14 +-
 Simulation/DetSimV2/DetSimOptions/src/GlobalGeomInfo.cc                                                              |   8 +-
 Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc                                                   |  28 ++--
 Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc                                                       | 775 ++++++++++++++++++++++---------------------------------------------------------------
 Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstructionLatticeShell.icc                                          |   2 +-
 Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc                                                         |  13 ++
 25 files changed, 934 insertions(+), 843 deletions(-)
 rename Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributer.hh => UpperWaterdistributor.hh} (55%)
 rename Simulation/DetSimV2/CentralDetector/include/{UpperWaterDistributerPlacement.hh => UpperWaterdistributorPlacement.hh} (75%)
 delete mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh
 create mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
 create mode 100644 Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
 rename Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributer.cc => UpperWaterdistributor.cc} (75%)
 rename Simulation/DetSimV2/CentralDetector/src/{UpperWaterDistributerPlacement.cc => UpperWaterdistributorPlacement.cc} (78%)
 rename Simulation/DetSimV2/CentralDetector/src/{WaterdistributerlooppipeMaker.cc => WaterdistributorlooppipeMaker.cc} (85%)
 create mode 100644 Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
(ok) A[blyth@localhost junosw]$ 


