Calib_GuideTube_Construction/Calib_GuideTube_Construction.rst
================================================================

::

     jcv Calib_GuideTube_Construction


Two sets of nested G4Torus (Teflon and Water) volumes split in phi::

    45     enum {GT_number = 39}


Both sets have same Rtor Rmin 0. and Rmax differs::

     49 //     G4Torus(const G4String      &pName
     50 //             G4double      pRmin
     51 //             G4double      pRmax
     52 //             G4double      pRtor
     53 //             G4double      pSPhi
     54 //             G4double      pDPhi )
     55 //



meshname : why getting twice the number of torii expected from glance at code ?
---------------------------------------------------------------------------------

::

    [blyth@localhost CSGFoundry]$ grep Surftube meshname.txt | wc -l 
    156

    [blyth@localhost CSGFoundry]$ grep sSurftube meshname.txt | wc -l 
    78

    [blyth@localhost CSGFoundry]$ grep svacSurftube meshname.txt | wc -l 
    78


HMM: why the 0,1 doubling up::

    [blyth@localhost CSGFoundry]$ grep sSurftube meshname.txt 
    sSurftube_0V1_0
    sSurftube_1V1_0
    sSurftube_2V1_0
    sSurftube_3V1_0
    sSurftube_4V1_0
    ...
    sSurftube_34V1_0
    sSurftube_35V1_0
    sSurftube_36V1_0
    sSurftube_37V1_0
    sSurftube_38V1_0
    sSurftube_0V1_1
    sSurftube_1V1_1
    sSurftube_2V1_1
    sSurftube_3V1_1
    sSurftube_4V1_1
    ...
    sSurftube_35V1_1
    sSurftube_36V1_1
    sSurftube_37V1_1
    sSurftube_38V1_1


::

    161 void
    162 Calib_GuideTube_Construction::makeSurftubeLogical() {
    163     for (int i = 0; i < GT_number; i++)
    164     {
    165         solidSurftube[i] = new G4Torus("sSurftube_"+std::to_string(i)+m_guidetube_option,
    166                                     0*mm,
    167                                     19.05/2.0*mm,
    168                                     m_rad_guidetube + m_rad_guidetube_Plus[i]*mm,
    169                                     m_torus_swipe_phi_Start[i]*deg,
    170                                     m_torus_swipe_phi_Delta[i]*deg
    171                                     );
    172     }




::

    [blyth@localhost CSGFoundry]$ grep svacSurftube meshname.txt 
    svacSurftube_0V1_0
    svacSurftube_1V1_0
    svacSurftube_2V1_0
    svacSurftube_3V1_0
    svacSurftube_4V1_0
    ...
    svacSurftube_35V1_0
    svacSurftube_36V1_0
    svacSurftube_37V1_0
    svacSurftube_38V1_0
    svacSurftube_0V1_1
    svacSurftube_1V1_1
    svacSurftube_2V1_1
    svacSurftube_3V1_1
    svacSurftube_4V1_1
    ...
    svacSurftube_34V1_1
    svacSurftube_35V1_1
    svacSurftube_36V1_1
    svacSurftube_37V1_1
    svacSurftube_38V1_1







jgr Surftube
--------------

::

    [blyth@localhost CSGFoundry]$ jgr Surftube
    ./Doc/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + lSurftube_phys : 1
    ./Doc/oum/source/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + lSurftube_phys : 1
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    void makeSurftubeLogical();
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    void makevacSurftubeLogical();
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    void makevacSurftubePhysical();
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4Torus*> solidSurftube = std::vector<G4Torus*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4LogicalVolume*> logicSurftube = std::vector<G4LogicalVolume*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4Torus*> solidvacSurftube = std::vector<G4Torus*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4LogicalVolume*> logicvacSurftube = std::vector<G4LogicalVolume*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    std::vector<G4VPhysicalVolume*> physivacSurftube = std::vector<G4VPhysicalVolume*>(GT_number,0);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    makeSurftubeLogical();
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        makevacSurftubeLogical();
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        makevacSurftubePhysical();
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    logicSurftube[counter] -> SetVisAttributes(ct_visatt);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    return logicSurftube[counter];
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makeSurftubeLogical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        solidSurftube[i] = new G4Torus("sSurftube_"+std::to_string(i)+m_guidetube_option,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    logicSurftube[i] = new G4LogicalVolume(solidSurftube[i],
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:                                        "lSurftube_"+std::to_string(i)+m_guidetube_option,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        new G4LogicalSkinSurface("Tube_surf_"+std::to_string(i)+m_guidetube_option,logicSurftube[i],TubeSurface);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makevacSurftubeLogical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        solidvacSurftube[i] = new G4Torus("svacSurftube_"+std::to_string(i)+m_guidetube_option,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    logicvacSurftube[i] = new G4LogicalVolume(solidvacSurftube[i],
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:                                        "lvacSurftube_"+std::to_string(i)+m_guidetube_option,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makevacSurftubePhysical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:    physivacSurftube[i] = new G4PVPlacement(0,
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:                                      logicvacSurftube[i],    // its logical volume 
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:                                      "pvacSurftube_"+std::to_string(i)+m_guidetube_option,       // its name
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:                                      logicSurftube[i],  // its mother  volume
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:        physiSourceEnclosure_shell = new G4PVPlacement(trans_enclosure,logicSourceEnclosure_shell, "pSourceEnclosure_shell", logicvacSurftube[source_ID], false,0);
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:            if (daughter_name.find("Surftube") != std::string::npos) {
    ./Simulation/DetSimV2/DetSimOptions/share/vis_guidetube.mac:/vis/geometry/set/visibility lSurftubeV1_0 0 true
    ./Simulation/DetSimV2/DetSimOptions/share/vis_guidetube.mac:/vis/geometry/set/visibility lSurftubeV1_1 0 true
    [blyth@localhost junosw]$ 


csv
-----

::

    092 void
     93 Calib_GuideTube_Construction::GT_Parameters() {
     94 
     95 //get parameter path
     96     std::string f_path = JUNO::Path::resolve("junosw/Simulation/DetSimV2/DetSimOptions/data/Guide_Tube.csv");
     97 
     98 //input parameters
     99     std::ifstream fin(f_path.c_str());
    100     std::string tmp_line;
    101     int GT_ID;       // col 1
    102     double Phi_Start;     // col 2
    103     double Phi_Delta;     // col 3
    104     double Radius_Plus;     // col 4
    105 
    106     while (fin.good())
    107     {
    108         std::getline(fin, tmp_line);
    109         if (fin.fail())
    110         {
    111             break;
    112         }
    113 
    114         std::stringstream ss;
    115         ss << tmp_line;
    116 
    117         ss >> GT_ID;
    118         ss >> Phi_Start;
    119         m_torus_swipe_phi_Start[GT_ID] = Phi_Start;
    120         ss >> Phi_Delta;
    121         m_torus_swipe_phi_Delta[GT_ID] = Phi_Delta;
    122         ss >> Radius_Plus;
    123         m_rad_guidetube_Plus[GT_ID] = Radius_Plus;
    124     }
    125 
    126 }


::

    In [24]: d
    Out[24]: 
    array([[   0.  ,    2.  ,   12.5 ,   23.15],
           [   1.  ,   14.5 ,    5.  ,   74.55],
           [   2.  ,   19.5 ,    2.  ,   23.15],
           [   3.  ,   21.5 ,    5.  ,   65.95],
           [   4.  ,   26.5 ,    3.  ,   23.15],
           [   5.  ,   29.5 ,    2.  ,    0.  ],
           [   6.  ,   31.5 ,    2.  ,   15.75],
           [   7.  ,   33.5 ,    2.  ,   23.15],
           [   8.  ,   35.5 ,    6.  ,    0.  ],
           [   9.  ,   41.5 ,    2.  ,   23.15],
           [  10.  ,   43.5 ,    6.  ,    0.  ],
           [  11.  ,   49.5 ,    2.  ,   23.15],
           [  12.  ,   51.5 ,    6.  ,    0.  ],
           [  13.  ,   57.5 ,    3.  ,   23.15],
           [  14.  ,   60.5 ,    6.  ,    0.  ],
           [  15.  ,   66.5 ,    2.  ,   23.15],
           [  16.  ,   68.5 ,    6.  ,    0.  ],
           [  17.  ,   74.5 ,    2.  ,   23.15],
           [  18.  ,   76.5 ,    6.  ,    0.  ],
           [  19.  ,   82.5 ,   15.  ,   23.15],
           [  20.  ,   97.5 ,    6.  ,    0.  ],
           [  21.  ,  103.5 ,    2.  ,   23.15],
           [  22.  ,  105.5 ,    6.  ,    0.  ],
           [  23.  ,  111.5 ,    2.  ,   23.15],
           [  24.  ,  113.5 ,    6.  ,    0.  ],
           [  25.  ,  119.5 ,    3.  ,   23.15],
           [  26.  ,  122.5 ,    6.  ,    0.  ],
           [  27.  ,  128.5 ,    2.  ,   23.15],
           [  28.  ,  130.5 ,    6.  ,    0.  ],
           [  29.  ,  136.5 ,    2.  ,   23.15],
           [  30.  ,  138.5 ,    6.  ,    0.  ],
           [  31.  ,  144.5 ,    2.  ,   23.15],
           [  32.  ,  146.5 ,    2.  ,   15.75],
           [  33.  ,  148.5 ,    2.  ,    0.  ],
           [  34.  ,  150.5 ,    3.  ,   23.15],
           [  35.  ,  153.5 ,    5.  ,   65.95],
           [  36.  ,  158.5 ,    2.  ,   23.15],
           [  37.  ,  160.5 ,    5.  ,   74.55],
           [  38.  ,  165.5 ,    6.  ,   23.15]])





Why _0 _1 ?
---------------


::

    [blyth@localhost data]$ jgr Calib_GuideTube
    ./Doc/oum/source/detsim/calib.md:The geometry of GT neutron source is written in `$CALIBUNIT/src/Calib_GuideTube_Construction.cc`. 
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        # old one: Calib_GuideTube
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        guide_tube_option = "Calib_GuideTube_V1"
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        if guide_tube_option == "Calib_GuideTube_V1":
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            guide_tube_v1_0 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_0")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            guide_tube_v1_1 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_1")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            guide_tube_place_v1_0 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_0")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            guide_tube_place_v1_1 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_1")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        elif guide_tube_option == "Calib_GuideTube" and args.GT_source_theta:
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            guide_tube_source_place = detsimalg.createTool("Calib_GuideTube_Construction")
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:#ifndef Calib_GuideTube_Construction_hh
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:#define Calib_GuideTube_Construction_hh
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:class Calib_GuideTube_Construction: public IDetElement,
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    Calib_GuideTube_Construction(const std::string& name);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Construction.hh:    ~Calib_GuideTube_Construction();
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Placement.hh:#ifndef Calib_GuideTube_Placement_hh
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Placement.hh:#define Calib_GuideTube_Placement_hh
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Placement.hh:class Calib_GuideTube_Placement: public IDetElementPos,
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Placement.hh:    Calib_GuideTube_Placement(const std::string& name);
    ./Simulation/DetSimV2/CalibUnit/include/Calib_GuideTube_Placement.hh:    ~Calib_GuideTube_Placement();
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:#include "Calib_GuideTube_Placement.hh"
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:DECLARE_TOOL(Calib_GuideTube_Placement);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:Calib_GuideTube_Placement::Calib_GuideTube_Placement(const std::string& name) 
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:Calib_GuideTube_Placement::~Calib_GuideTube_Placement() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:Calib_GuideTube_Placement::hasNext() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:Calib_GuideTube_Placement::next() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Placement.cc:Calib_GuideTube_Placement::init() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:#include "Calib_GuideTube_Construction.hh"
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:DECLARE_TOOL(Calib_GuideTube_Construction);
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::Calib_GuideTube_Construction(const std::string& name)
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::~Calib_GuideTube_Construction() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::getLV() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::inject(std::string motherName, IDetElement* other, IDetElementPos* pos) {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::GT_Parameters() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::initVariables() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::initMaterials() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makeSurftubeLogical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::SetGuideTubeReflectivity() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makevacSurftubeLogical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makevacSurftubePhysical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makeSourceEnclosureLogical() {
    ./Simulation/DetSimV2/CalibUnit/src/Calib_GuideTube_Construction.cc:Calib_GuideTube_Construction::makeSourceEnclosurePhysical() {
    Binary file ./Simulation/DetSimV2/CalibUnit/src/.Calib_GuideTube_Construction.cc.swp matches
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    declProp("CalibUnitName", m_cu_name="Calib_GuideTube");  // so Guide Tube is enabled
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    detsim0.property("CalibUnitName").set("Calib_GuideTube_V1") # this is default one
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    detsim0.property("CalibUnitExtras").set([#"Calib_GuideTube_V1_0", 
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:                                             #"Calib_GuideTube_V1_1"
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    guide_tube_v1_0 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_0")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    guide_tube_v1_1 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_1")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    guide_tube_place_v1_0 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_0")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    guide_tube_place_v1_1 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_1")
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("CalibUnitName", m_cu_name="Calib_GuideTube");  // so Guide Tube is enabled
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:        if (m_calibunit_name=="Calib_GuideTube_V1") {
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:            m_calibunit_name = "Calib_GuideTube_V1_0";
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:            m_calibunit_name = "Calib_GuideTube_V1_1";
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      } else if(m_calibunit_name == "Calib_GuideTube"){
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:          cu_tool_name = "Calib_GuideTube_Construction"; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:          pos_tool_name = "Calib_GuideTube_Placement";
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      } else if(m_calibunit_name == "Calib_GuideTube_V1_0"){ 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:          cu_tool_name = "Calib_GuideTube_Construction_V1_0";  
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:          pos_tool_name = "Calib_GuideTube_Placement_V1_0"; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      } else if(m_calibunit_name == "Calib_GuideTube_V1_1"){ 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:          cu_tool_name = "Calib_GuideTube_Construction_V1_1";  
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:           pos_tool_name = "Calib_GuideTube_Placement_V1_1"; 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  if(m_calibunit_name != "Calib_GuideTube" 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:     && m_calibunit_name != "Calib_GuideTube_V1_0" 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:     && m_calibunit_name != "Calib_GuideTube_V1_1") {
    [blyth@localhost junosw]$




There are 2::

    2447         if guide_tube_option == "Calib_GuideTube_V1":
    2448             guide_tube_v1_0 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_0")
    2449             guide_tube_v1_0.property("Option").set("V1_0")
    2450 
    2451             if args.GT_source_theta > 0:
    2452                 guide_tube_v1_0.property("Theta").set(args.GT_source_theta)
    2453                 guide_tube_v1_0.property("UseSource").set(True)
    2454 
    2455             guide_tube_v1_1 = detsimalg.createTool("Calib_GuideTube_Construction/Calib_GuideTube_Construction_V1_1")
    2456             guide_tube_v1_1.property("Option").set("V1_1")
    2457 
    2458             if args.GT_source_theta < 0:
    2459                 guide_tube_v1_1.property("Theta").set(args.GT_source_theta)
    2460                 guide_tube_v1_1.property("UseSource").set(True)
    2461 
    2462             import math
    2463 
    2464             # the default guide tube is constructed at -x-z plane. 
    2465             # V1_0: 123.40 deg. Rotate from 90 to 123.40, hence 123.40-90
    2466             # V1_1: 267.40 deg. Rotate from 90 to 267.40, hence 267.40-90
    2467    
    2468             guide_tube_place_v1_0 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_0")
    2469             # guide_tube_place_v1_0.property("Phi").set(-(90.+2.6)*math.pi/180.)
    2470             guide_tube_place_v1_0.property("Phi").set((123.40-90.0)*math.pi/180.)
    2471    
    2472             guide_tube_place_v1_1 = detsimalg.createTool("Calib_GuideTube_Placement/Calib_GuideTube_Placement_V1_1")
    2473             # guide_tube_place_v1_1.property("Phi").set((303.4-180.)*math.pi/180.)
    2474             guide_tube_place_v1_1.property("Phi").set((267.40-90.0)*math.pi/180.)
    2475    


