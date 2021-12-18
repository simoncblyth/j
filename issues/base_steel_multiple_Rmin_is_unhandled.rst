base_steel_multiple_Rmin_is_unhandled
=======================================


::

    2021-12-18 03:21:53.008 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lTarget soname sTarget [--x4skipsolidname] n
    2021-12-18 03:21:53.011 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lAcrylic soname sAcrylic [--x4skipsolidname] n
    2021-12-18 03:21:53.014 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lSteel soname sStrut [--x4skipsolidname] n
    2021-12-18 03:21:53.015 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lSteel2 soname sStrut [--x4skipsolidname] n
    2021-12-18 03:21:53.016 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lSteel soname sStrutBallhead [--x4skipsolidname] n
    2021-12-18 03:21:53.017 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lFasteners soname uni1 [--x4skipsolidname] n
    2021-12-18 03:21:53.029 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lUpper soname base_steel [--x4skipsolidname] n
    2021-12-18 03:21:53.030 FATAL [68153] [X4Solid::convertPolycone@1375]  multiple Rmin is unhandled base_steel
    2021-12-18 03:21:53.030 ERROR [68153] [X4Solid::convertPolycone@1409]  convertPolycone_duplicate_py_inner_omission 1
    2021-12-18 03:21:53.031 ERROR [68153] [NNodeNudger::init@95] NNodeNudger::brief root.treeidx  95 num_prim  2 num_coincidence  1 num_nudge  1 
    2021-12-18 03:21:53.033 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lAddition soname uni_acrylic1 [--x4skipsolidname] n
    2021-12-18 03:21:53.033 ERROR [68153] [NNodeNudger::init@95] NNodeNudger::brief root.treeidx  96 num_prim  3 num_coincidence  3 num_nudge  1 
    2021-12-18 03:21:53.038 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname lXJanchor soname solidXJanchor [--x4skipsolidname] n
    2021-12-18 03:21:53.040 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname NNVTMCPPMTlMask soname NNVTMCPPMTsMask [--x4skipsolidname] n
    2021-12-18 03:21:53.046 INFO  [68153] [X4PhysicalVolume::convertSolid@951]  lvname NNVTMCPPMTlMaskTail soname NNVTMCPPMTTail [--x4skipsolidname] n


::

    epsilon:issues blyth$ jgr base_steel
    ./Simulation/DetSimV2/CentralDetector/include/UpperAcrylicConstruction.hh:     G4VSolid* base_steel;
    ./Simulation/DetSimV2/CentralDetector/src/UpperAcrylicConstruction.cc:        base_steel = new G4Polycone("base_steel",0.0*deg,360.0*deg,504,ZUpper,RminUpper,RmaxUpper);
    ./Simulation/DetSimV2/CentralDetector/src/UpperAcrylicConstruction.cc:        base_steel = new G4Polycone("base_steel",0.0*deg,360.0*deg,4,ZUpper4,RminUpper4,RmaxUpper4);
    ./Simulation/DetSimV2/CentralDetector/src/UpperAcrylicConstruction.cc:            base_steel,
    epsilon:offline blyth$ 


Visualize G4 intersects with xxs.sh::

    x4
    GEOM=PolyconeWithMultipleRmin ./xxs.sh 


See the converted geom::

    EYE=1,1,0.5 ./cxr_geochain.sh 




jcv UpperAcrylicConstruction::

     14 class UpperAcrylicConstruction : public IDetElement,
     15                         public ToolBase{
     16 
     17 public:
     18     G4LogicalVolume* getLV();
     19     bool inject(std::string motherName, IDetElement* other, IDetElementPos* pos);
     20 
     21     UpperAcrylicConstruction(const std::string& name);
     22     ~UpperAcrylicConstruction();
     23 
     24 private:
     25     void initMaterials();
     26     void initVariables();
     27 
     28     void makeUpperLogical();
     29 
     30 private:
     31 
     32      G4VSolid* base_steel;
     33      G4LogicalVolume* logicUpper;
     34 
     35 private:
     36      G4Material* Steel;
     37 
     38 private:
     39      double ZUpper[504];
     40      double RminUpper[504];
     41      double RmaxUpper[504];
     42 
     43 private:
     44     std::string option;
     45 
     46 };
     47 #endif


     15 UpperAcrylicConstruction::UpperAcrylicConstruction(const std::string& name)
     16     : ToolBase(name)
     17 {
     18     logicUpper = 0;
     19     initVariables();
     20 
     21     declProp("option", option="simple");
     22 }   
     23 

::

    097     } else if (option=="simple") {
     98 
     99         static double ZUpper4[4];
    100         static double RminUpper4[4];
    101         static double RmaxUpper4[4];
    102 
    103         ZUpper4[0] = 0*mm;   RminUpper4[0] = 43.*mm; RmaxUpper4[0] = 195.*mm;
    104         ZUpper4[1] = -15*mm; RminUpper4[1] = 43.*mm; RmaxUpper4[1] = 195.*mm;
    105         ZUpper4[2] = -15*mm; RminUpper4[2] = 55.5*mm; RmaxUpper4[2] = 70.*mm;
    106         ZUpper4[3] = -101*mm; RminUpper4[3] = 55.5*mm; RmaxUpper4[3] = 70.*mm;
    107 
    108         base_steel = new G4Polycone("base_steel",0.0*deg,360.0*deg,4,ZUpper4,RminUpper4,RmaxUpper4);
    109     }
    110     logicUpper = new G4LogicalVolume(
    111             base_steel,
    112             Steel,
    113             "lUpper",
    114             0,
    115             0,
    116             0);
    117   G4VisAttributes* addition_visatt = new G4VisAttributes(G4Colour(1.0, 0, 1.0));
    118   addition_visatt -> SetForceWireframe(true);
    119   addition_visatt -> SetForceAuxEdgeVisible(true);
    120   //fasteners_visatt -> SetForceSolid(true);
    121   //fasteners_visatt -> SetForceLineSegmentsPerCircle(4);
    122   logicUpper -> SetVisAttributes(addition_visatt);

