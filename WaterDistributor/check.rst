check
========



::

    A[blyth@localhost junosw]$ js
    /home/blyth/junosw
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (fetch)
    origin	git@code.ihep.ac.cn:JUNO/offline/junosw.git (push)
    On branch yupd-water-distributor
    Your branch is up to date with 'origin/yupd-water-distributor'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Examples/Tutorial/share/opticks_juno.sh
        modified:   oj_initialize.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    A[blyth@localhost junosw]$ vi Examples/Tutorial/share/opticks_juno.sh
    A[blyth@localhost junosw]$ 
    A[blyth@localhost junosw]$ find . -name opticks_juno.sh
    ./Examples/Tutorial/share/opticks_juno.sh
    ./InstallArea/bin/opticks_juno.sh
    A[blyth@localhost junosw]$ cp Examples/Tutorial/share/opticks_juno.sh InstallArea/bin/opticks_juno.sh
    A[blyth@localhost junosw]$ ./oj_initialize.sh 


Issue 1 : looks like Waterdistributor_0/1/2/3 is a split union with parts at top and bottom of CD !
------------------------------------------------------------------------------------------------------

See no sign of split union. But the approach is sharing the same solid pointer between
upper and lower LV. Which looks suspect. 
Turned out to be due to duplicated CSGPrim name.

::

    (ok) A[blyth@localhost J25_4_0_opticks_Debug]$ grep multiUnion\ name=\"Waterdistributor0x origin.gdml 
        <multiUnion name="Waterdistributor0xb47aad0">
        <multiUnion name="Waterdistributor0xb45d9f0">
        <multiUnion name="Waterdistributor0xb457a60">
        <multiUnion name="Waterdistributor0xab2e720">
    (ok) A[blyth@localhost J25_4_0_opticks_Debug]$ 




::

    A[blyth@localhost junosw]$ jgl Waterdistributor
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ./Examples/Tutorial/share/opticks_juno.sh
    ./Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterdistributor.hh
    ./Simulation/DetSimV2/CentralDetector/include/UpperWaterdistributorPlacement.hh
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterdistributor.cc
    ./Simulation/DetSimV2/CentralDetector/src/UpperWaterdistributorPlacement.cc
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorlooppipeMaker.cc
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    A[blyth@localhost junosw]$ 


jcv WaterdistributorlooppipeMaker : MultiUnion of three rings of cut tubes with vertical joins
-----------------------------------------------------------------------------------------------

::

     29 class WaterdistributorlooppipeMaker {
     30 public:
     31     G4VSolid* getSolid() const;
     32 
     33     WaterdistributorlooppipeMaker(const std::string& name,
     34         double TubeR_type_I,
     35         double TubeR_type_II,
     36         double holeR);
     37                     
     38     G4VSolid* helper_Waterdistributorlooppipe(const std::string& name,
     39                                double distance,
     40                                double TubeR);
     41     
     42     G4VSolid* m_solid;
     43     
     44     static G4VSolid* CreateSolid( 
     45         const std::string& type,
     46         double TubeR_type_I,
     47         double TubeR_type_II,
     48         double holeR,
     49         double length, 
     50         double offset,
     51         double torus_radius, 
     52         double angle,
     53         int    part
     54     );
     55 
     56 };



::

    (ok) A[blyth@localhost junosw]$ jgl WaterdistributorlooppipeMaker
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorlooppipeMaker.cc

    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
          29 #include "WaterdistributorlooppipeMaker.hh"     HEADED INCLUDED BUT NOT USED ? 


    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc


    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    (ok) A[blyth@localhost junosw]$ 


jcv WaterdistributorpipeMaker
-------------------------------

::

     29 struct PlacedSolid {
     30     G4VSolid* solid;
     31     G4ThreeVector pos;
     32     G4RotationMatrix rot;
     33     int copy_no;
     34     std::string log_name;
     35     std::string phy_name;
     36 };
     37 
     38 class WaterdistributorpipeMaker {
     39 public:
     40     static std::vector<PlacedSolid> MakeStraightPipePartI();    // "WaterDistributorPipeInner"
     41     static std::vector<PlacedSolid> MakeStraightPipePartII();   // "WaterDistributorPipeOuter"
     42     static std::vector<PlacedSolid> MakeStraightPipePartIII();  // "WaterDistributorPipePartIII"

     43     static std::vector<PlacedSolid> MakeConnectingCutTubes(double m_heightWP, double m_waterPoolHeightplus);
     44     static std::vector<PlacedSolid> MakeAirGapWaterDistributorPipe(double m_airGapThickness);
     45     static std::vector<PlacedSolid> MakeWaterDistributorPolycone(double m_heightWP);
     46     static std::vector<PlacedSolid> MakeWaterDistributorPolyconeInner(double m_heightWP);
     47 
     48     static std::vector<PlacedSolid> MakeLoopDistributer();
     49     static PlacedSolid MakeWaterDistributorPartIIIUnion(double m_lowerchimney_rotangle);
     50 };



::

    248 std::vector<PlacedSolid> WaterdistributorpipeMaker::MakeLoopDistributer() {
    249     std::vector<PlacedSolid> result;
    250 
    251     G4double TubeR_type_I = 38 * mm;
    252     G4double TubeR_type_II = 70 * mm;
    253     G4RotationMatrix rot;
    254     rot.rotateX(90 * deg);
    255     rot.rotateZ(-10 * deg);
    256 
    257     WaterdistributorlooppipeMaker* pipeMaker = new WaterdistributorlooppipeMaker("Waterdistributor", TubeR_type_I, TubeR_type_II, TubeR_type_I);
    258     G4VSolid* solid_outer = pipeMaker->getSolid();
    259 
    260     result.push_back({solid_outer, G4ThreeVector(0, 0, 21409), rot, 0, "LogicWaterdistributor", "PhysWaterdistributor"});
    261 
    262     WaterdistributorlooppipeMaker* pipeMaker_inner = new WaterdistributorlooppipeMaker(
    263         "Waterdistributor", TubeR_type_I - 5 * mm, TubeR_type_II - 5 * mm, TubeR_type_I - 5 * mm
    264     );
    265     G4VSolid* solid_inner = pipeMaker_inner->getSolid();
    266     result.push_back({solid_inner, G4ThreeVector(0, 0, 0), G4RotationMatrix(), 0, "LogicWaterdistributor_partII", "PhysWaterdistributor_partII"});
    267 
    268     return result;
    269 }



::

    (ok) A[blyth@localhost junosw]$ jgr MakeLoopDistributer
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh:    static std::vector<PlacedSolid> MakeLoopDistributer();
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:std::vector<PlacedSolid> WaterdistributorpipeMaker::MakeLoopDistributer() {
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    (ok) A[blyth@localhost junosw]$ 



::

    1083 void
    1084 DetSim1Construction::makeWaterdistributorLooppipe()
    1085 {
    1086     G4LogicalVolume* logicLoopOuter = nullptr;
    1087     G4LogicalVolume* logicLoopInner = nullptr;
    1088     G4RotationMatrix rot;
    1089 
    1090     auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    1091     for (size_t i = 0; i < loop_vec.size(); ++i) {
    1092         const auto& p = loop_vec[i];
    1093         if(i==0) {
    1094             logicLoopOuter = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
    1095 
    1096             G4VisAttributes* visAttr1 = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    1097             visAttr1->SetForceAuxEdgeVisible(true);
    1098             logicLoopOuter->SetVisAttributes(visAttr1);
    1099 
    1100             new G4PVPlacement(G4Transform3D(p.rot, G4ThreeVector(0, 0, 18935)), logicLoopOuter, "pWaterDistributorLoopOuterCD_I", logicInnerWaterPool, false, p.copy_no);
    1101 
    1102             rot = p.rot;
    1103         } else {
    1104             logicLoopInner = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
    1105 
    1106             G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
    1107             visAttr->SetForceSolid(true);
    1108             logicLoopInner->SetVisAttributes(visAttr);
    1109             new G4PVPlacement(G4Transform3D(p.rot, p.pos), logicLoopInner, p.phy_name,logicLoopOuter, false, p.copy_no);
    1110         }
    1111     }
    1112 
    1113     new G4PVPlacement(G4Transform3D(rot, G4ThreeVector(0, 0, -18838)), logicLoopOuter, "pWaterDistributorLoopOuterCD_II", logicInnerWaterPool, false, 1);
    1114 
    1115     G4OpticalSurface* pvdf_surface = new G4OpticalSurface("PVDFOpticalSurface");
    1116     pvdf_surface->SetModel(unified);
    1117     pvdf_surface->SetType(dielectric_dielectric);
    1118     pvdf_surface->SetFinish(ground);
    1119     pvdf_surface->SetSigmaAlpha(0.1);
    1120 
    1121     G4MaterialPropertiesTable* pvdf_mt = new G4MaterialPropertiesTable();
    1122     const G4int nEntries = 4;
    1123     G4double photonEnergy[nEntries] = {1.55 * eV, 6.20 * eV, 10.33 * eV, 15.5 * eV};



::

     892 void WaterPoolConstruction::makeAllWaterDistributor() {
     ...


     951     // ====== Waterdistributor Loop Pipe ======
     952     G4LogicalVolume* logicLoopOuter = nullptr;
     953     G4LogicalVolume* logicLoopInner = nullptr;
     954     G4RotationMatrix rot;
     955 
     956     auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
     957     for (size_t i = 0; i < loop_vec.size(); ++i) {
     958         const auto& p = loop_vec[i];
     959         if(i==0) {
     960             logicLoopOuter = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
     961 
     962             G4VisAttributes* visAttr1 = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
     963             visAttr1->SetForceAuxEdgeVisible(true);
     964             logicLoopOuter->SetVisAttributes(visAttr1);
     965 
     966             new G4PVPlacement(G4Transform3D(p.rot, p.pos), logicLoopOuter, p.phy_name, logicWaterPool, false, p.copy_no);
     967 
     968             rot = p.rot;
     969         } else {
     970             logicLoopInner = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
     971 
     972             G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
     973             visAttr->SetForceSolid(true);
     974             logicLoopInner->SetVisAttributes(visAttr);
     975             new G4PVPlacement(G4Transform3D(G4RotationMatrix(), p.pos), logicLoopInner, p.phy_name, logicLoopOuter, false, p.copy_no);
     976         }
     977     }
     978 
     979     new G4PVPlacement(G4Transform3D(rot, G4ThreeVector(0, 0, -21312)), logicLoopOuter, "pWaterDistributorLoopOuter_II", logicWaterPool, false, 1);
     980 
     981     G4OpticalSurface* pvdf_surface = new G4OpticalSurface("PVDFOpticalSurface");
     982     pvdf_surface->SetModel(unified);
     983     pvdf_surface->SetType(dielectric_dielectric);
     984     pvdf_surface->SetFinish(ground);
     985     pvdf_surface->SetSigmaAlpha(0.1);









Changes
--------

::

    A[blyth@localhost junosw]$ git l -n20
    commit d933eb64cb9136cc3ec7eba35eb338856272ae97 (HEAD -> yupd-water-distributor, origin/yupd-water-distributor)
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Fri Sep 19 19:13:32 2025 +0800

        Added the flange to the upper chimney

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit 3412db5691c55fec565302c63fad132a0340e376
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Sep 16 20:30:48 2025 +0800

        Update the optical properties of the looppipe, set new absorption length and reflectivity.

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit 602b5d8bcb0f7bb3139a9b450ebaaca0da209460
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Sep 16 16:49:26 2025 +0800

        Add Acrylic-related variables and WaterDistributor OpticalSurface

    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/include/UpperWaterdistributor.hh
    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit 0aa1ea9034d0e0e1da0842cfee2731dddad828b5
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Mon Sep 15 21:12:10 2025 +0800

        Add UpperWaterdistributor and related classes for water distribution simulation
        
        - Implemented UpperWaterdistributor class to create a water distributor with chimney.
        - Added UpperWaterdistributorPlacement class for positioning the water distributor.
        - Created WaterdistributorlooppipeMaker and WaterdistributorpipeMaker classes for generating pipe geometries.
        - Defined methods for constructing various pipe parts and connecting tubes.
        - Included necessary G4 classes and materials for solid geometry creation.
        - Established visual attributes for the water distributor components.
        - Integrated initialization and material setup in UpperWaterdistributor.

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    R067    Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh    Simulation/DetSimV2/CentralDetector/include/UpperWaterdistributor.hh
    R075    Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributerPlacement.hh   Simulation/DetSimV2/CentralDetector/include/UpperWaterdistributorPlacement.hh
    D       Simulation/DetSimV2/CentralDetector/include/WaterdistributerpipeMaker.hh
    R082    Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh    Simulation/DetSimV2/CentralDetector/include/WaterdistributorlooppipeMaker.hh
    A       Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    R075    Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc        Simulation/DetSimV2/CentralDetector/src/UpperWaterdistributor.cc
    R078    Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc       Simulation/DetSimV2/CentralDetector/src/UpperWaterdistributorPlacement.cc
    D       Simulation/DetSimV2/CentralDetector/src/WaterdistributerpipeMaker.cc
    R085    Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc        Simulation/DetSimV2/CentralDetector/src/WaterdistributorlooppipeMaker.cc
    A       Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
    M       Simulation/DetSimV2/Chimney/src/UpperChimney.cc
    M       Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc

    commit d8a32b51a428530fea1818e56c69801a1c25853b
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Sun Sep 14 21:30:58 2025 +0800

        Add the constructor for the straight pipe and update relevant logic to support the new pipe type.

    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    A       Simulation/DetSimV2/CentralDetector/include/WaterdistributerpipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    A       Simulation/DetSimV2/CentralDetector/src/WaterdistributerpipeMaker.cc
    M       Simulation/DetSimV2/DetSimOptions/src/GlobalGeomInfo.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    M       Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc

    commit 326df792c018da8927e90e3208e46f8dd7c7d884
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Thu Sep 11 15:13:52 2025 +0800

        Enhance simulation geometry and parameters
        
        - Adjusted the z-position of specific bottom pillars in HBeamConstruction to raise them by 100mm for improved alignment.
        - Introduced a new method in WaterdistributerlooppipeMaker to create various solid types including loop, pipeA, and S_shape, enhancing the flexibility of water distribution geometry.
        - Added a new member variable for air gap thickness in UpperChimneyMaker and updated related calculations in UpperChimney to account for this thickness.
        - Modified UpperChimneyPlacement to incorporate air gap thickness when calculating the z-position of the chimney.
        - Updated GlobalGeomInfo to include a new parameter for lower chimney rotation angle, ensuring accurate geometry representation.
        - Commented out dead water and tyvek logical and physical construction in WaterPoolConstruction to streamline the simulation setup.
        - Refactored WaterPoolConstruction to utilize a MultiUnion for water distributor components, improving the organization and efficiency of the geometry.
        - Simplified the logic for creating lattice shell in WaterPoolConstructionLatticeShell by removing unnecessary configuration checks.

    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    M       Simulation/DetSimV2/Chimney/include/UpperChimneyMaker.hh
    M       Simulation/DetSimV2/Chimney/src/UpperChimney.cc
    M       Simulation/DetSimV2/Chimney/src/UpperChimneyPlacement.cc
    M       Simulation/DetSimV2/DetSimOptions/include/GlobalGeomInfo.hh
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/src/GlobalGeomInfo.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstructionLatticeShell.icc

    commit 8108b8ba07651ec3ab5a44a5eaf67b474089904d
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Mon Sep 8 15:16:20 2025 +0800

        Enable material property table settings for the PVDF surface.

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit 12b13323b20c0729a73d0a321c2d094a982ddabc
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Sep 2 20:20:45 2025 +0800

        Initialize the solidUpperWaterDistributer and logicUpperWaterDistributer pointers in the UpperWaterDistributer class to nullptr

    M       Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh

    commit f9996d83eb5077ec1692ee602412b486f150d3c8
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Sep 2 20:17:07 2025 +0800

        Update the optical surface settings of the water distrubutor, replace G4LogicalBorderSurface with G4LogicalSkinSurface, and clean up the relevant code.

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit c7dd2824558edaf3af8e14d6bf59ce15f098f471
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Sun Aug 31 18:42:14 2025 +0800

        Clean up the code, remove unused member variables and comments

    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc

    commit 545f101f448b6ec1aa7e41d38cc5510010cd99f8
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Sun Aug 31 18:10:18 2025 +0800

        Update the pool construction logic, adjust the z-coordinate calculation method, and remove unnecessary comments.

    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc

    commit 7aeded2d34172539a4c08f9ce02d40e607ce7d14
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Sun Aug 31 16:41:53 2025 +0800

        Clean up the code, remove unnecessary comments and visualization attribute settings

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    M       Simulation/DetSimV2/SimUtil/src/HexagonPosBall.cc
    M       Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc

    commit a224dff40df3ae852e74e440daf873609c9f2fd4
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Thu Aug 28 19:40:21 2025 +0800

        Add G4LogicalSkinSurface to replace G4LogicalBorderSurface, and clean up the related code.

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc

    commit 183c069a9f21d3c0515b96c12c60428988c129ee
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Thu Aug 28 15:26:12 2025 +0800

        Clean up the code, remove unused attributes and comments

    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    M       Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    M       Simulation/DetSimV2/Chimney/src/LowerChimney.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    M       Simulation/DetSimV2/SimUtil/src/HexagonPosBall.cc

    commit 7e1f30f03bd4d27cc46235e193f44df22c771619
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Wed Aug 27 16:41:22 2025 +0800

        An intermediate update

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    A       Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributer.hh
    A       Simulation/DetSimV2/CentralDetector/include/UpperWaterDistributerPlacement.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    A       Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributer.cc
    A       Simulation/DetSimV2/CentralDetector/src/UpperWaterDistributerPlacement.cc
    M       Simulation/DetSimV2/Chimney/include/Dimensions.hh
    M       Simulation/DetSimV2/Chimney/src/LowerChimney.cc
    M       Simulation/DetSimV2/Chimney/src/UpperChimney.cc
    M       Simulation/DetSimV2/DetSimOptions/include/GlobalGeomInfo.hh
    M       Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    M       Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/GlobalGeomInfo.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    M       Simulation/DetSimV2/SimUtil/src/HexagonPosBall.cc
    M       Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc

    commit 4998094d4f13bd7308a55de20499ffcc1ece287d
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Fri Apr 18 19:33:59 2025 +0800

        Updated the optical interface of PVDF

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc

    commit dff345a15615fcffcc84a38fc2e9198b562398fe
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Fri Apr 18 10:20:49 2025 +0800

        multiunion geometry needs to call the Voxelize() method

    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc

    commit 7cc9a0fd1a3f59358415f9212165096f67b5b315
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Thu Apr 17 19:58:30 2025 +0800

        update the waterdistributor geometry

    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    A       Simulation/DetSimV2/CentralDetector/include/WaterdistributerlooppipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    A       Simulation/DetSimV2/CentralDetector/src/WaterdistributerlooppipeMaker.cc
    M       Simulation/DetSimV2/Chimney/src/LowerChimney.cc
    M       Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/src/ExpHallConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    M       Simulation/DetSimV2/DetSimOptions/src/RockConstruction.cc
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc



