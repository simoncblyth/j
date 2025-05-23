Chimney
=========




Chimney code
---------------

::

    [blyth@localhost js]$ jgl Chimney
    ./Detector/Geometry/Geometry/CdGeom.h
    ./Detector/Geometry/src/CdGeom.cc
    ./Detector/Identifier/ChangeLog
    ./Detector/Parameter/Parameter/CdGeomPar.h
    ./Detector/Parameter/Parameter/ChimGeomPar.h
    ./Detector/Parameter/Parameter/TTGeomPar.h
    ./Detector/Parameter/data/Dimensions.txt
    ./Detector/Parameter/src/CdGeomPar.cc
    ./Detector/Parameter/src/ChimGeomPar.cc
    ./Detector/Parameter/src/TTGeomPar.cc
    ./Doc/detsim/anaelement.md
    ./Doc/detsim/geomelem.md
    ./Doc/detsim/structures.md
    ./Doc/oum/source/detsim/anaelement.md
    ./Doc/oum/source/detsim/geomelem.md
    ./Doc/oum/source/detsim/structures.md
    ./Doc/oum/source/releasenotes/J25.3.md
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ./Examples/Tutorial/share/mac/GtPosGeoMapping.yaml
    ./Examples/Tutorial/share/opticks_juno.sh
    ./Reconstruction/TTTracking/src/TtLikelihood.cc
    ./Reconstruction/TTTracking/src/TtLikelihood.h
    ./Simulation/DetSimV2/CMakeLists.txt
    ./Simulation/DetSimV2/CentralDetector/include/PrototypeConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/include/RoundBottomFlaskSolidMaker.hh
    ./Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    ./Simulation/DetSimV2/CentralDetector/src/PrototypeConstruction.cc
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    ./Simulation/DetSimV2/Chimney/CMakeLists.txt

    ./Simulation/DetSimV2/Chimney/include/LowerChimney.hh
    ./Simulation/DetSimV2/Chimney/include/LowerChimneyMaker.hh
    ./Simulation/DetSimV2/Chimney/include/LowerChimneyPlacement.hh
    ./Simulation/DetSimV2/Chimney/src/LowerChimney.cc
    ./Simulation/DetSimV2/Chimney/src/LowerChimneyMaker.cc
    ./Simulation/DetSimV2/Chimney/src/LowerChimneyPlacement.cc

    ./Simulation/DetSimV2/Chimney/include/UpperChimneyMaker.hh
    ./Simulation/DetSimV2/Chimney/include/UpperChimneyPlacement.hh
    ./Simulation/DetSimV2/Chimney/src/UpperChimney.cc
    ./Simulation/DetSimV2/Chimney/src/UpperChimneyMaker.cc
    ./Simulation/DetSimV2/Chimney/src/UpperChimneyPlacement.cc

    ./Simulation/DetSimV2/DetSimOptions/CMakeLists.txt
    ./Simulation/DetSimV2/DetSimOptions/include/DetSim0Svc.hh
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis.py
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/TopTracker/include/TopTrackerConstruction.hh
    ./Simulation/DetSimV2/TopTracker/share/make_std_TT.py
    ./Simulation/DetSimV2/TopTracker/src/TopTrackerConstruction.cc
    A[blyth@localhost junosw]$ 



jcv UpperChimney
------------------

::

    053 G4VSolid* UpperChimneyMaker::getSolidUpperChimney(){
     54     
     55     G4Tubs* tube= new G4Tubs(
     56                              "Upper_Chimney",
     57                              0,   // pRMin,
     58                              m_TubeSteelOuterR+5.0*mm,   // pRMax,
     59                              m_TopToWater*m/2., // pDz,
     60                              0*deg,     // pSPhi,
     61                              360*deg    // pDPhi
     62                              );
     63     
     64     
     65     
     66     return tube;
     67 }



    114 void UpperChimney::makeUpperChimneyLogicalandPhysical(){
    115     UpperChimneyMaker UpperChimney(m_TopToWater);
    116 
    117     solidUpperChimney=UpperChimney.getSolidUpperChimney();
    118     solidUpperChimneyLS=UpperChimney.getSolidALS();
    119     solidUpperChimneySteel=UpperChimney.getSolidBSteel();
    120 
    121     logicUpperChimney=new G4LogicalVolume(solidUpperChimney,
    122                                       Air,
    123                                       "lUpperChimney",
    124                                       0,
    125                                       0,
    126                                       0);
    127 
    128 
    129     logicUpperChimneyLS = new G4LogicalVolume(solidUpperChimneyLS,
    130                                       (m_fillwater)?Water:LS,
    131                                       "lUpperChimneyLS",
    132                                       0,
    133                                       0,
    134                                       0);
    135 
    136 
    137     logicUpperChimneySteel= new G4LogicalVolume(solidUpperChimneySteel,
    138                                                   Steel,
    139                                                   "lUpperChimneySteel",
    140                                                   0,
    141                                                   0,
    142                                                   0);
    143 
    144     physiUpperChimneyLS = new G4PVPlacement(0,              // no rotation
    145                                       //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
    146                                       G4ThreeVector(0,0,0), // at (x,y,z)
    147                                       logicUpperChimneyLS,    // its logical volume
    148                                       "pUpperChimneyLS",       // its name
    149                                       logicUpperChimneySteel,  // its mother  volume
    150                                       false,           // no boolean operations
    151                                       0);              // no particular field
    152 
    153 
    154     physiUpperChimneySteel = new G4PVPlacement(0,              // no rotation
    155                                                G4ThreeVector(0,0,0 ), // at (x,y,z)
    156                                                logicUpperChimneySteel,    // its logical volume
    157                                                "pUpperChimneySteel",       // its name
    158                                                logicUpperChimney,  // its mother  volume
    159                                                false,           // no boolean operations
    160                                                0);              // no particular field
    161 }



::

           +---------------------------+-------------------------+------------------------+
           |    PV                     |     LV                  |     MLV                |
           |    symbol(name)           |     symbol(mat)[solid]  |     symbol             |
           |                           |                         |                        |
           +===========================+=========================+========================+
           |                           |                         |                        | 
           |                           |  logicUpperChimney      |                        |
           |                           |  (Air)                  |                        |
           |                           |  [Upper_Chimney]
           +---------------------------+-------------------------+------------------------+
           |                           |                         |                        |   
           |   physiUpperChimneySteel  |  logicUpperChimneySteel | logicUpperChimney      | 
           |    "pUpperChimneySteel"   |  (Steel)                |                        |
           |                           |  [Upper_Steel_tube]     |                        | 
           +---------------------------+-------------------------+------------------------+
           |                           |                         |                        |                           
           |   physiUpperChimneyLS     |  logicUpperChimneyLS    | logicUpperChimneySteel |
           |    "pUpperChimneyLS"      |  (LS)                   |                        |
           |                           |  [Upper_LS_tube]        |                        |
           +---------------------------+-------------------------+------------------------+




Viz one by one::

    FULLSCREEN=0 ELV=Upper_Chimney MOI=Upper_Chimney:0:-1 EYE=3,3,0 cxr_min.sh
           filled tube

    FULLSCREEN=0 ELV=Upper_Steel_tube MOI=Upper_Steel_tube:0:-1 EYE=3,3,0 cxr_min.sh
           filled tube

    FULLSCREEN=0 ELV=Upper_LS_tube MOI=Upper_LS_tube:0:-1 EYE=3,3,0 cxr_min.sh
           filled tube


All three::

    FULLSCREEN=0 ELV=Upper_Chimney,Upper_Steel_tube,Upper_LS_tube MOI=Upper_LS_tube:0:-1 EYE=3,3,0 cxr_min.sh
            filled tube ... cannot viz the diff between them [coincidence recipe?]

::

 
          Air
            Steel   
                LS 








LowerChimney
-------------

::

    [blyth@localhost sysrap]$ jgr sChimneySteel
    ./Examples/Tutorial/share/opticks_juno.sh:sChimneySteel:0:-1                         #  7
    ./Simulation/DetSimV2/Chimney/src/LowerChimney.cc:    G4Tubs* solidChimneySteel = new G4Tubs("sChimneySteel",

    [blyth@localhost junosw]$ jgr sWaterTube
    ./Simulation/DetSimV2/Chimney/src/LowerChimney.cc:    G4Tubs* solidWaterTube = new G4Tubs("sWaterTube",




Viz one by one::

    FULLSCREEN=0 ELV=sChimneySteel MOI=sChimneySteel:0:-1 EYE=3,3,0 cxr_min.sh
           ## appears as long cylindrical tube with thin edge

    FULLSCREEN=0 ELV=sChimneyLS MOI=sChimneyLS:0:-1 EYE=3,3,0 cxr_min.sh
           ## appears as a filled cylinder  

    FULLSCREEN=0 ELV=sChimneyAcrylic MOI=sChimneyAcrylic:0:-1 EYE=3,3,0 cxr_min.sh
           ## appears as a squat cylindrical tube with a fat edge  

    FULLSCREEN=0 ELV=sWaterTube MOI=sWaterTube:0:-1 EYE=3,3,0 cxr_min.sh
           ## appears as a filled cylinder  
            


Viz combination::

    FULLSCREEN=0 ELV=sChimneyAcrylic,sChimneySteel MOI=sChimneyAcrylic:0:-1 EYE=3,3,0 cxr_min.sh
          ## the outside of the long Steel tube lines up with the inside of the acrylic


    FULLSCREEN=0 ELV=sChimneyAcrylic,sChimneySteel,sWaterTube MOI=sChimneyAcrylic:0:-1 EYE=3,3,0 cxr_min.sh




::
                        
                         sChimneySteel 
                +        +
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                +        +
             +--+        +--+
             |  |        |  |            
             |  |        |  |            
             |  |        |  |            
             |  |        |  |            
             +--+        +--+
       sChimneyAcrylic


All three::

    FULLSCREEN=0 ELV=sChimneyAcrylic,sChimneySteel,sChimneyLS MOI=sChimneyAcrylic:0:-1 EYE=3,3,0 cxr_min.sh


::

                          
                          sChimneyLS
                         / sChimneySteel 
                        /  /
                ++------++
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                +|      |+
             +--+|      |+--+
             |  ||      ||  |            
             |  ||      ||  |            
             |  ||      ||  |            
             |  ||      ||  |            
             +--++------++--+
            /
       sChimneyAcrylic




All four::

    FULLSCREEN=0 ELV=sChimneyAcrylic,sChimneySteel,sChimneyLS,sWaterTube,Upper_Chimney MOI=sChimneyAcrylic:0:-1 EYE=3,3,0 cxr_min.sh
           Upper_Chimney lines up the the lower three with a big gap between them.  




::

                       Upper_Chimney
                +--------+
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                |        |
                +--------+

                          
                          sChimneyLS
                         / sChimneySteel 
                        /  /
                ++------++
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                ||      ||
                +|      |+
             +--+|      |+--+
             |  ||      ||  |            
             |  ||      ||  |            
             |  ||      ||  |            
             |  ||      ||  |            
             +--++------++--+
            /
       sChimneyAcrylic




::

    271 void LowerChimney::makeNoShutterLowerChimneyLogicalAndPhysical(){
    272     // TODO: need to optimize this part. following are copied from Dimensions.hh
    273     const double WPHeight=43.5*m;   // water pool height
    274     const double Acrylic_thickness=12.4*cm;// thickness of the acrylic ball
    275     const double Acrylic_thickness_chimney=8*cm;// thickness of the acrylic tube of the chimney
    276     const double TubeInnerR=0.4*m;        // inner R of acrylic tube.
    277     const double TubeAcrylicOuterR=TubeInnerR+Acrylic_thickness_chimney;
    278 
    279     const double CD_R=17.7*m+Acrylic_thickness;
    280     //const double ChimBtm_2_Center=sqrt(CD_R*CD_R-TubeAcrylicOuterR*TubeAcrylicOuterR);
    281     const double ChimBtm_2_Center=CD_R;
    282     const double LowerTubeH=WPHeight/2.- ChimBtm_2_Center; // height of lower chimney

              LowerTubeH :   43.5/2. - (17.7 + 0.124) = 3.9260 m
              m_TubeH/2  :  LowerTubeH/2 : 1.963 m


    283 
    284     // double m_TubeH = 393*cm;    // height of chimney under the water is 393*cm
    285     double m_TubeH = LowerTubeH;
    286     double m_Acrylic_H = 87.6*cm;


               876 / 2 = 438.0 mm


    287     G4Tubs* solidWaterTube = new G4Tubs("sWaterTube",
    288                                         0,
    289                                         TubeAcrylicOuterR,
    290                                         m_TubeH/2.0,
    291                                         0,
    292                                         360*deg
    293                                         );
    294 
    295     logicLowerChimney = new G4LogicalVolume(solidWaterTube,
    296                                             Water,
    297                                             "lLowerChimney",
    298                                             0,
    299                                             0,
    300                                             0);
    301 
    302     G4Tubs* solidChimneyAcrylic = new G4Tubs("sChimneyAcrylic",
    303                                              TubeInnerR,
    304                                              TubeAcrylicOuterR,
    305                                              m_Acrylic_H/2.0,
    306                                              0,
    307                                              360*deg
    308                                              );
    309 
    310     logicLowerChimneyAcrylic = new G4LogicalVolume(solidChimneyAcrylic,
    311                                                    Acrylic,
    312                                                    "lLowerChimneyAcrylic",
    313                                                    0,
    314                                                    0,
    315                                                    0);
    316 
    317     G4Tubs* solidChimneyLS = new G4Tubs("sChimneyLS",
    318                                         0,
    319                                         TubeInnerR,
    320                                         m_TubeH/2.0,
    321                                         0,
    322                                         360*deg
    323                                         );
    324 
    325     logicLowerChimneyLS = new G4LogicalVolume(solidChimneyLS,
    326                                               (m_fillwater)?Water:LS,
    327                                               "lLowerChimneyLS",
    328                                               0,
    329                                               0,
    330                                               0);
    331 
    332     G4Tubs* solidChimneySteel = new G4Tubs("sChimneySteel",
    333                                            40*cm,   // TODO
    334                                            40.5*cm, // TODO
    335                                            (m_TubeH-m_Acrylic_H)/2.0,
    336                                            0,
    337                                            360*deg
    338                                            );
    339 
    340     logicLowerChimneySteel = new G4LogicalVolume(solidChimneySteel,
    341                                                  Steel,
    342                                                  "lLowerChimneySteel",
    343                                                  0,
    344                                                  0,
    345                                                  0);
    346 
    347     physiLowerChimneyAcrylic = new G4PVPlacement(0,              // no rotation
    348                                                  G4ThreeVector(0,0,(m_Acrylic_H-m_TubeH)/2.0), // at (x,y,z)
    349                                                  logicLowerChimneyAcrylic,    // its logical volume
    350                                                  "pLowerChimneyAcrylic",       // its name
    351                                                  logicLowerChimney,  // its mother  volume
    352                                                  false,           // no boolean operations
    353                                                  0);
    354 
    355     physiLowerChimneyLS = new G4PVPlacement(0,              // no rotation
    356                                             G4ThreeVector(0,0,0), // at (x,y,z)
    357                                             logicLowerChimneyLS,    // its logical volume
    358                                             "pLowerChimneyLS",       // its name
    359                                             logicLowerChimney,  // its mother  volume
    360                                             false,           // no boolean operations
    361                                             0);
    362 
    363     physiLowerChimneySteel = new G4PVPlacement(0,              // no rotation
    364                                                G4ThreeVector(0,0,m_Acrylic_H/2.0), // at (x,y,z)
    365                                                logicLowerChimneySteel,    // its logical volume
    366                                                "pLowerChimneySteel",       // its name
    367                                                logicLowerChimney,  // its mother  volume
    368                                                false,           // no boolean operations
    369                                                0);
    370 
    371 
    372     G4OpticalSurface* steel_surface = new G4OpticalSurface("ChimneySteelOpticalSurface");
    373     G4MaterialPropertiesTable* steel_mt = new G4MaterialPropertiesTable();
    374 
    375     if(m_isgroundsurface){
    376             std::cout<<"Set ground surface"<<std::endl;
    377             steel_surface->SetModel(unified);
    378             steel_surface->SetType(dielectric_metal);
    379             steel_surface->SetFinish(ground);
    380             steel_surface->SetSigmaAlpha(0.2);
    381     }
    382     else{
    383             std::cout<<"Set polished surface"<<std::endl;
    384             steel_surface->SetModel(glisur);
    385             steel_surface->SetType(dielectric_metal);
    386             steel_surface->SetFinish(polished);
    387     }
    388 
    389     double SteelEnergy[4] = {1.55*eV, 6.20*eV, 10.33*eV, 15.5*eV};
    390     double SteelReflectivity[4] = {m_reflectivity,m_reflectivity,m_reflectivity,m_reflectivity};
    391     steel_mt->AddProperty("REFLECTIVITY", SteelEnergy, SteelReflectivity, 4);
    392     steel_surface->SetMaterialPropertiesTable(steel_mt);
    393     new G4LogicalSkinSurface("Steel_surface",logicLowerChimneySteel,steel_surface);
    394 
    395 }




     +--------------------------------+----------------------------------------+--------------------------+
     |                                |                                        |                          |
     |                                |                                        |                          |
     |   PV symbol "name"             |      LV                                |       MLV                |
     |                                |                                        |                          |
     +================================+========================================+==========================+
     |                                |                                        |                          |
     |   -                            |    logicLowerChimney                   |                          |
     |                                |    "lLowerChimney"                     |                          | 
     |                                |    [Water]                             |                          |
     |                                |    solidWaterTube                      |                          |
     |                                |    "sWaterTube"                        |                          |
     |                                |    tubs_R: 0->TubeAcrylicOuterR        |                          |
     |                                |                  (40+8 cm)             |                          |
     |                                |    tubs_dz: m_TubeH/2.0                |                          |
     |                                |                                        |                          |
     +--------------------------------+----------------------------------------+--------------------------+
     |                                |                                        |                          |
     |   physiLowerChimneySteel       |  logicLowerChimneySteel                |   logicLowerChimney      |
     |   "pLowerChimneySteel"         |  "lLowerChimneySteel"                  |                          |
     |                                |  [Steel]                               |                          |
     |                                |  solidChimneySteel                     |                          |
     |                                |  "sChimneySteel"                       |                          |
     |                                |  tubs_R 40->40.5 cm radius             |                          |
     |                                |        (m_TubeH-m_Acrylic_H)/2.0       |                          |  
     |                                |                                        |                          |
     +--------------------------------+----------------------------------------+--------------------------+
     |                                |                                        |                          |  
     |   physiLowerChimneyLS          |  logicLowerChimneyLS                   |  logicLowerChimney       |
     |   "pLowerChimneyLS"            |  "lLowerChimneyLS"                     |                          |
     |                                |  [LS]                                  |                          |
     |                                |  solidChimneyLS                        |                          |
     |                                |  "sChimneyLS"                          |                          |
     |                                |     tubs 0->TubeInnerR(40cm)           |                          |
     |                                |          m_TubeH/2.0                   |                          |
     |                                |                                        |                          |
     +--------------------------------+----------------------------------------+--------------------------+
     |                                |                                        |                          |  
     |  physiLowerChimneyAcrylic      |   logicLowerChimneyAcrylic             |  logicLowerChimney       |
     |   "pLowerChimneyAcrylic"       |   "lLowerChimneyAcrylic"               |                          |
     |                                |   [Acrylic]                            |                          |
     |                                |   solidChimneyAcrylic                  |                          |
     |                                |   "sChimneyAcrylic"                    |                          |        
     |                                |   tubs: TubeInnerR->TubeAcrylicOuterR  |                          |
     |                                |            40cm -> 48cm                |                          |
     |                                |           m_Acrylic_H/2.0              |                          |  
     |                                |                                        |                          |  
     +--------------------------------+----------------------------------------+--------------------------+








Chimney from meshname.txt
---------------------------

::

    A[blyth@localhost CSGFoundry]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug/CSGFoundry
    A[blyth@localhost CSGFoundry]$ grep Chimney  meshname.txt 
    Upper_Chimney

    sChimneyAcrylic
    sChimneyLS
    sChimneySteel

    sBotChimneySSEnclosure_PartI_II_III
    sBotChimneySSEnclosureLS_PartI_II_III



    005 Upper_LS_tube
      6 Upper_Steel_tube
      7 Upper_Chimney

    137 sChimneyAcrylic
    138 sChimneyLS
    139 sChimneySteel
    140 sWaterTube


::

    ELV=sChimneyAcrylic,sChimneyLS,sChimneySteel,sWaterTube,Upper_Chimney,Upper_LS_tube,Upper_Steel_tube cxr_min.sh




jcv UpperChimneyMaker
----------------------

UpperChimneyMaker.hh
   header with both UpperChimneyMaker and UpperChimney


jcv UpperChimneyPlacement
--------------------------




generate +Z input photons suitable for sChimneyLS dimensions
----------------------------------------------------------------


~/o/sysrap/tests/SGenerate__test.sh::

     41 #src=sphere
     42 src=disc
     43 
     44 if [ "$src" == "sphere" ]; then
     45     export storch_FillGenstep_type=sphere
     46     export storch_FillGenstep_radius=100    # +ve for outwards
     47     export storch_FillGenstep_pos=0,0,0
     48     export storch_FillGenstep_distance=1.00 # frac_twopi control of polarization phase(tangent direction)
     49 
     50 elif [ "$src" == "disc" ]; then
     51 
     52     export storch_FillGenstep_type=disc
     53     export storch_FillGenstep_radius=399       # 400-1 within radius of sChimneyLS
     54     export storch_FillGenstep_zenith=0,1       # radial range scale
     55     export storch_FillGenstep_azimuth=0,1      # phi segment twopi fraction
     56     export storch_FillGenstep_mom=0,0,1
     57     export storch_FillGenstep_pos=0,0,-1963    # -1963  start on the lower edge of sChimneyLS  
     58 
     59 fi

Push start position down to avoid starting on a boundary::

     41 #src=sphere
     42 src=disc
     43 
     44 if [ "$src" == "sphere" ]; then
     45     export storch_FillGenstep_type=sphere
     46     export storch_FillGenstep_radius=100    # +ve for outwards
     47     export storch_FillGenstep_pos=0,0,0
     48     export storch_FillGenstep_distance=1.00 # frac_twopi control of polarization phase(tangent direction)
     49 
     50 elif [ "$src" == "disc" ]; then
     51 
     52     export storch_FillGenstep_type=disc
     53     export storch_FillGenstep_radius=399       # 1mm less than sChimneyLS outer radius
     54     export storch_FillGenstep_zenith=0,1       # radial range scale
     55     export storch_FillGenstep_azimuth=0,1      # phi segment twopi fraction
     56     export storch_FillGenstep_mom=0,0,1
     57     export storch_FillGenstep_pos=0,0,-2063   # -1963-100  below the base of sChimneyLS
     58 
     59 fi
     60 




ipcv : config to use those as the input photons
-------------------------------------------------

::

    097 
     98     ## config input photon running
     99     #export SEvt__INPUT_PHOTON_DIR=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
    100     #export SEvt__INPUT_PHOTON_DIR=/home/blyth/.opticks/InputPhotons
    101     export SEvt__INPUT_PHOTON_DIR=/data1/blyth/tmp/SGenerate__test
    102 
    103     #opticks_input_photon=RainXZ_Z230_10k_f8.npy
    104     #opticks_input_photon=RainXZ_Z230_1M_f8.npy
    105     #opticks_input_photon=RandomSpherical1M_f8.npy
    106     #opticks_input_photon=SGenerate_ph_disc_M1.npy
    107     opticks_input_photon=SGenerate_ph_disc_K1.npy  ## see 
    108 
    109     #opticks_input_photon_frame=NNVT:0:1000
    110     #opticks_input_photon_frame=sTarget
    111     opticks_input_photon_frame=sChimneyLS:0:-2
    112 
    113     export OPTICKS_INPUT_PHOTON=${opticks_input_photon}
    114     export OPTICKS_INPUT_PHOTON_FRAME=${opticks_input_photon_frame}
    115     export SEvt__transformInputPhoton_VERBOSE=1
    116 
    117     ## below env adapts the output directory for .npy arrays
    118     ## OPTICKS_EVENT_NAME is required to contain strings such as "Debug" and "Philox"
    119     ## when those correspond to the build config as checked by sbuild::Matches
    120     export OPTICKS_SCRIPT=InputPhotonsCheck
    121     export OPTICKS_EVENT_NAME=DebugPhilox_${OPTICKS_INPUT_PHOTON_FRAME}_${OPTICKS_INPUT_PHOTON/.npy}



Run the A:B input photon check::

   ipc 


ipc chi2::

    AB
    [sseq_index_ab::desc u_size 108 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   770.1862 ndf  2.0000 sum/ndf   385.0931 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT BT AB                                                                                      :     645     33 :   552.4248 : Y :       3     12 : DEVIANT  `
        TO BT BT BT SA                                                                                   :      -1    551 :     0.0000 : N :      -1      4 : AZERO C2EXC  
    :r:`TO AB                                                                                            :     329     44 :   217.7614 : Y :       0      0 : DEVIANT  `
        TO BT BT SC SA                                                                                   :      -1     71 :     0.0000 : N :      -1      2 : AZERO C2EXC  
        TO SC SA                                                                                         :      -1     51 :     0.0000 : N :      -1     27 : AZERO C2EXC  
        TO BT BR BT BT AB                                                                                :      -1     21 :     0.0000 : N :      -1      3 : AZERO C2EXC  
        TO BT BT SC DR SA                                                                                :      -1     19 :     0.0000 : N :      -1     33 : AZERO C2EXC  


Starting 100mm lower gives extra BT, but otherwise little difference::

    AB
    [sseq_index_ab::desc u_size 134 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   751.5819 ndf  2.0000 sum/ndf   375.7909 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT BT BT AB                                                                                   :     641     35 :   543.2485 : Y :       2     16 : DEVIANT  `
        TO BT BT BT BT SA                                                                                :      -1    510 :     0.0000 : N :      -1      0 : AZERO C2EXC  
    :r:`TO BT AB                                                                                         :     319     44 :   208.3333 : Y :       0     13 : DEVIANT  `
        TO BT SC SA                                                                                      :      -1     64 :     0.0000 : N :      -1      7 : AZERO C2EXC  
        TO BT BT BT SC SA                                                                                :      -1     50 :     0.0000 : N :      -1     71 : AZERO C2EXC  

Even lower, not much difference::

    AB
    [sseq_index_ab::desc u_size 159 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   751.9264 ndf  2.0000 sum/ndf   375.9632 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT BT BT AB                                                                                   :     626     33 :   533.6100 : Y :       2      2 : DEVIANT  `
        TO BT BT BT BT SA                                                                                :      -1    473 :     0.0000 : N :      -1      0 : AZERO C2EXC  
    :r:`TO BT AB                                                                                         :     316     38 :   218.3164 : Y :       0      4 : DEVIANT  `
        TO BT BT BT SC SA                                                                                :      -1     79 :     0.0000 : N :      -1     15 : AZERO C2EXC  
        TO BT SC SA                                                                                      :      -1     57 :     0.0000 : N :      -1     24 : AZERO C2EXC  
        TO BT BT BT SC DR SA                                                                             :      -1     28 :     0.0000 : N :      -1     26 : AZERO C2EXC  


The "TO BT AB" deviation looks like coincident surfaces at top of LowerChimney giving wrong material props. 

::

    In [6]: w = a.q_startswith("TO BT AB") ; len(w)
    Out[6]: 316



For fast dev cycle and PIDX dumping get cxs_min.sh to "repeat" A side of ipc
--------------------------------------------------------------------------------

::

    441 elif [ "$OPTICKS_RUNNING_MODE" == "SRM_INPUT_PHOTON" ]; then
    442 
    443     ## cf with ipcv : ~/j/InputPhotonsCheck/InputPhotonsCheck.sh
    444 
    445     #sevt__input_photon_dir=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
    446     #sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    447     #sevt__input_photon_dir=/data1/blyth/tmp/SGenerate__test
    448     sevt__input_photon_dir=$TMP/SGenerate__test
    449 
    450     #opticks_input_photon=RainXZ_Z195_1000_f8.npy      ## ok
    451     #opticks_input_photon=RainXZ_Z230_1000_f8.npy      ## ok
    452     #opticks_input_photon=RainXZ_Z230_10k_f8.npy       ## ok
    453     #opticks_input_photon=RainXZ_Z230_100k_f8.npy
    454     #opticks_input_photon=RainXZ_Z230_X700_10k_f8.npy  ## X700 to illuminate multiple PMTs
    455     #opticks_input_photon=GridXY_X700_Z230_10k_f8.npy
    456     #opticks_input_photon=GridXY_X1000_Z1000_40k_f8.npy
    457     opticks_input_photon=SGenerate_ph_disc_K1.npy
    458 
    459     #opticks_input_photon_frame=-1
    460     #opticks_input_photon_frame=sWorld:0:0
    461     #opticks_input_photon_frame=NNVT:0:0
    462     #opticks_input_photon_frame=NNVT:0:50
    463     #opticks_input_photon_frame=NNVT:0:1000
    464     #opticks_input_photon_frame=PMT_20inch_veto:0:1000
    465     #opticks_input_photon_frame=sChimneyAcrylic
    466     #opticks_input_photon_frame=sTarget
    467     opticks_input_photon_frame=sChimneyLS:0:-2
    468 
    469     # SEventConfig
    470     export SEvt__INPUT_PHOTON_DIR=${SEvt__INPUT_PHOTON_DIR:-$sevt__input_photon_dir}
    471     export OPTICKS_INPUT_PHOTON=${OPTICKS_INPUT_PHOTON:-$opticks_input_photon};
    472     export OPTICKS_INPUT_PHOTON_FRAME=${OPTICKS_INPUT_PHOTON_FRAME:-$opticks_input_photon_frame}
    473 
    474     vars="$vars SEvt__INPUT_PHOTON_DIR OPTICKS_INPUT_PHOTON OPTICKS_INPUT_PHOTON_FRAME"



Change EVT.sh to use the cxs_min.sh AFOLD
---------------------------------------------

::

     01 #!/bin/bash 
      2 usage(){ cat << EON
      3 ~/.opticks/GEOM/EVT.sh
      4 ========================
      5 
      6 EON
      7 }
      8 
      9 if [ "$GEOM" == "J25_3_0_opticks_Debug" ]; then
     10     afold_0=/tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_SGenerate_ph_disc_K1/A000
     11     afold_1=/data1/blyth/tmp/GEOM/J25_3_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon/A000
     12     bfold=/tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_SGenerate_ph_disc_K1/B000
     13     export AFOLD=${AFOLD:-$afold_1}
     14     export BFOLD=${BFOLD:-$bfold}
     15 fi
     16 



Add desc to cxr_min.sh showing the EVT.sh change for AFOLD
------------------------------------------------------------

::

    [CSGOptiXRenderInteractiveTest::desc
     ar
    [SRecordInfo.desc
     lpath [/data1/blyth/tmp/GEOM/J25_3_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon/A000/record.npy]
                     mn (-8715.662,-8589.153,-760.825, 0.000) 
                     mx (18643.098,5138.156,21750.006,174.987) 
                     ce (4963.718,-1725.499,10494.591,13679.380) 
            record.sstr (1000, 32, 4, 4, )
           record_first 0
           record_count 32000
    ]SRecordInfo.desc

     br
    [SRecordInfo.desc
     lpath [/tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_SGenerate_ph_disc_K1/B000/record.npy]
                     mn (-23494.199,-21004.648,-21750.004, 0.000) 
                     mx (19887.502,18617.275,48357.656,388.847) 
                     ce (-1803.349,-1193.687,13303.826,35053.828) 
            record.sstr (1000, 32, 4, 4, )
           record_first 0
           record_count 32000
    ]SRecordInfo.desc


SABTest.sh SABTest.py also using EVT.sh to set AFOLD BFOLD
-----------------------------------------------------------

::

    A[blyth@localhost ~]$ SAB=1 SABTest.sh pdb


    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT AB                                                                                 ' ' 0' '   626     33' '533.6100' '     2      2']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '     0    473' '473.0000' '    -1      0']

     [' 2' 'TO BT AB                                                                                       ' ' 2' '   316     38' '218.3164' '     0      4']
                                                                              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     10x more AB in A than B : that must be incorrect material 


     [' 3' 'TO BT BT BT SC SA                                                                              ' ' 3' '     0     79' '79.0000' '    -1     15']
     [' 4' 'TO BT SC SA                                                                                    ' ' 4' '     0     57' '57.0000' '    -1     24']
     [' 5' 'TO BT BT BT SC DR SA                                                                           ' ' 5' '     0     28' ' 0.0000' '    -1     26']
     [' 6' 'TO BT BT BR BT BT AB                                                                           ' ' 6' '     0     21' ' 0.0000' '    -1     12']




    In [3]: w = a.q_startswith("TO BT AB") ; len(w)
    Out[3]: 316


    In [5]: a
    Out[5]: SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data1/blyth/tmp/GEOM/J25_3_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon/A000 

    In [6]: b
    Out[6]: SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/J25_3_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_sChimneyLS:0:-2_SGenerate_ph_disc_K1/B000 


    In [13]: a.f.record[w,:3,3,0].view(np.int32) >> 16   ## boundary for "TO BT AB"
    Out[13]: 
    array([[  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],
           [  0, 137,  24],


    A[blyth@localhost standard]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_3_0_opticks_Debug/CSGFoundry/SSim/stree/standard

    A[blyth@localhost standard]$ cat.py -s 137,24 bnd_names.txt 
    137  Water///LS
    24   DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek


Would have expected LS///LS for first boundary ? 


SMOKING GUN : A side thinks Tyvek what should be LS (due to coincident surface)
---------------------------------------------------------------------------------

Actually coincident boundaries at top and bottom of LowerChimney comprehensively 
mess up simulation within LowerChimney. 

::

    In [17]: a.q[:10]
    Out[17]: 
    array([[b'TO BT AB                                                                                        '],
           [b'TO BT AB                                                                                        '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT AB                                                                                        '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT BT BT AB                                                                                  '],
           [b'TO BT BT BT AB                                                                                  ']], dtype='|S96')

    In [18]: w[:10]
    Out[18]: array([ 0,  1,  6, 15, 16, 18, 20, 21, 22, 23])



PIDX dumping : omits boundary index and detail on material lookups needed to confirm Tyvek diagnosis
-------------------------------------------------------------------------------------------------------

::

    A[blyth@localhost ~]$ PIDX=0 cxs_min.sh run


    2025-05-21 14:12:47.057 INFO  [2700602] [QSim::simulate@436] sslice {    0,    1,      0,   1000}

    //qsim.propagate.head idx 0 : bnc 0 cosTheta -1.00000000 
    //qsim.propagate.head idx 0 : mom = np.array([0.00000000,0.00000000,1.00000000]) ; lmom = 1.00000000  
    //qsim.propagate.head idx 0 : pos = np.array([  34.96954,  40.37925,17324.00000]) ; lpos = 17324.08203125 
    //qsim.propagate.head idx 0 : nrm = np.array([(0.00000000,0.00000000,-1.00000000]) ; lnrm = 1.00000000  
    //qsim.propagate_to_boundary.head idx 0 : u_absorption 0.88052022 logf(u_absorption) -0.12724234 absorption_length 37213.9219 absorption_distance 4735.186523 
    //qsim.propagate_to_boundary.head idx 0 : post = np.array([  34.96954,  40.37925,17324.00000,   0.00000]) 
    //qsim.propagate_to_boundary.head idx 0 : distance_to_boundary   500.0000 absorption_distance  4735.1865 scattering_distance 163243.1875 
    //qsim.propagate_to_boundary.head idx 0 : u_scattering     0.3990 u_absorption     0.8805 
    //qsim.propagate_to_boundary.tail.SAIL idx 0 : post = np.array([  34.96954,  40.37925,17824.00000,   2.29318]) ;  sail_time_delta =    2.29318   
    //qsim.propagate.body idx 0 bounce 0 command 3 flag 0 s.optical.x 0 s.optical.y 1 
    //qsim.propagate.body.WITH_CUSTOM4 idx 0  BOUNDARY ems 1 lposcost   1.000 
    //propagate_at_boundary.DEBUG_PIDX ctx.idx 0 base 0x7f0574c00000 base.pidx 0 
    //qsim.propagate_at_boundary.head idx 0 : theTransmittance = -1.00000000 
    //qsim.propagate_at_boundary.head idx 0 : nrm = np.array([0.00000000,0.00000000,-1.00000000]) ; lnrm = 1.00000000  
    //qsim.propagate_at_boundary.head idx 0 : pos = np.array([  34.96954,  40.37925,17824.00000]) ; lpos = 17824.08007812 
    //qsim.propagate_at_boundary.head idx 0 : mom0 = np.array([0.00000000,0.00000000,1.00000000]) ; lmom0 = 1.00000000 
    //qsim.propagate_at_boundary.head idx 0 : pol0 = np.array([0.75592810,-0.65465462,0.00000000]) ; lpol0 = 1.00000000 
    //qsim.propagate_at_boundary.head idx 0 : n1,n2,eta = (1.35398555,1.49711537,0.90439630) 
    //qsim.propagate_at_boundary.head idx 0 : c1 = 1.00000000 ; normal_incidence = 1 
    //qsim.propagate_at_boundary.body idx 0 : TransCoeff = 0.99747986 ; n1c1 = 1.35398555 ; n2c2 = 1.49711537 
    //qsim.propagate_at_boundary.body idx 0 : E2_t = np.array([0.00000000,0.94979841]) ; lE2_t = 0.94979841 
    //qsim.propagate_at_boundary.body idx 0 : A_trans = np.array([0.75592810,-0.65465462,0.00000000]) ; lA_trans = 1.00000000 
    //qsim.propagate_at_boundary.body idx 0 : u_reflect     0.7357 TransCoeff     0.9975 reflect 0 
    //qsim.propagate_at_boundary.body idx 0 : mom0 = np.array([0.00000000,0.00000000,1.00000000]) ; lmom0 = 1.00000000 
    //qsim.propagate_at_boundary.body idx 0 : pos = np.array([  34.96954,  40.37925,17824.00000]) ; lpos = 17824.08007812 
    //qsim.propagate_at_boundary.body idx 0 : nrm = np.array([0.00000000,0.00000000,-1.00000000]) ; lnrm = 1.00000000 
    //qsim.propagate_at_boundary.body idx 0 : n1 = 1.35398555 ; n2 = 1.49711537 ; eta = 0.90439630  
    //qsim.propagate_at_boundary.body idx 0 : c1 = 1.00000000 ; eta_c1 = 0.90439630 ; c2 = 1.00000000 ; eta_c1__c2 = -0.09560370 
    //qsim.propagate_at_boundary.tail idx 0 : reflect 0 tir 0 TransCoeff     0.9975 u_reflect     0.7357 
    //qsim.propagate_at_boundary.tail idx 0 : mom1 = np.array([0.00000000,0.00000000,1.00000000]) ; lmom1 = 1.00000000  
    //qsim.propagate_at_boundary.tail idx 0 : pol1 = np.array([0.75592810,-0.65465462,0.00000000]) ; lpol1 = 1.00000000 
    //qsim.propagate.tail idx 0 bounce 0 command 2 flag 2048 ctx.s.optical.y(ems) 1 

    //qsim.propagate.head idx 0 : bnc 1 cosTheta 1.00000000 
    //qsim.propagate.head idx 0 : mom = np.array([0.00000000,0.00000000,1.00000000]) ; lmom = 1.00000000  
    //qsim.propagate.head idx 0 : pos = np.array([  34.96954,  40.37925,17824.00000]) ; lpos = 17824.08007812 
    //qsim.propagate.head idx 0 : nrm = np.array([(0.00000000,0.00000000,1.00000000]) ; lnrm = 1.00000000  
    //qsim.propagate_to_boundary.head idx 0 : u_absorption 0.97224122 logf(u_absorption) -0.02815131 absorption_length 10000.0000 absorption_distance 281.513062 
    //qsim.propagate_to_boundary.head idx 0 : post = np.array([  34.96954,  40.37925,17824.00000,   2.29318]) 
    //qsim.propagate_to_boundary.head idx 0 : distance_to_boundary  3828.0000 absorption_distance   281.5131 scattering_distance 501730574336.0000 
    //qsim.propagate_to_boundary.head idx 0 : u_scattering     0.6055 u_absorption     0.9722 
    //qsim.propagate_to_boundary.body.BULK_ABSORB idx 0 : post = np.array([  34.96954,  40.37925,18105.51367,   3.23220]) ; absorb_time_delta = 0.93902653   
    //qsim.propagate.body idx 0 bounce 1 command 1 flag 8 s.optical.x 0 s.optical.y 1 
    //qsim.propagate.tail idx 0 bounce 1 command 1 flag 8 ctx.s.optical.y(ems) 1 
    2025-05-21 14:12:47.081 INFO  [2700602] [QEvent::gatherPhoton@613] [ evt.num_photon 1000 p.sstr (1000, 4, 4, ) evt.photon 0x7f0540000000
    2025-05-21 14:12:47.084 INFO  [2700602] [QSim::simulate@472]  eventID 0 tot_dt    0.003033 tot_ph       1000 tot_ph/M   0.001000 tot_ht          1 tot_ht/M   0.000001 tot_ht/tot_ph   0.001000 reset_ YES
    2025-05-21 14:12:47.085 INFO  [2700602] [SEvt::save@4021] /data1/blyth/tmp/GEOM/J25_3_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon/A000 [genstep,photon,record,seq,hit,domain,inphoton]
    2025-05-21 14:12:47.090 INFO  [2700602] [QSim::simulate@487] 
    SEvt__MINTIME


Add some fill_state PIDX debug
---------------------------------

::

    //qbnd.fill_state idx 0 boundary 137 line 548 wavelength   420.0000 m1_line 548 m2_line 551 su_line 549 s.optical.x 0  
    //qbnd.fill_state idx 0 boundary 137 s.index.x(m1_index) 17 s.index.y(m2_index) 5 s.index.z(su_index) 0 

    //qbnd.fill_state idx 0 boundary 24 line 96 wavelength   420.0000 m1_line 99 m2_line 96 su_line 98 s.optical.x 0  
    //qbnd.fill_state idx 0 boundary 24 s.index.x(m1_index) 11 s.index.y(m2_index) 13 s.index.z(su_index) 0 

Correct 1-based to 0-based, see sstandard::make_optical::

    //qbnd.fill_state idx 0 boundary 137 line 548 wavelength   420.0000 m1_line 548 m2_line 551 su_line 549 s.optical.x 0  
    //qbnd.fill_state idx 0 boundary 137 [s.index.x-1](m1_index) 16 [s.index.y-1](m2_index) 4 [s.index.z-1](su_index) -1 

    //qbnd.fill_state idx 0 boundary 24 line 96 wavelength   420.0000 m1_line 99 m2_line 96 su_line 98 s.optical.x 0  
    //qbnd.fill_state idx 0 boundary 24 [s.index.x-1](m1_index) 10 [s.index.y-1](m2_index) 12 [s.index.z-1](su_index) -1 


HMM those indices look off-by-one::

    A[blyth@localhost standard]$ cat.py mat_names.txt 
    0    Air
    1    Rock
    2    Galactic
    3    Steel
    4    *LS*
    5    Scintillator
    6    TiO2Coating
    7    Adhesive
    8    Aluminium
    9    LatticedShellSteel
    10   *Tyvek*
    11   vetoWater
    12   *DeadWater*
    13   Acrylic
    14   PE_PA
    15   StrutSteel
    16   *Water*
    17   AcrylicMask
    18   CDReflectorSteel
    19   Vacuum
    20   Pyrex
    21   Teflon
    22   Black_HDPE


Q: Where does the Tyvek come in ?


Simtrace cxt_min.sh not obeying MOI 
---------------------------------------

::

     587 double QSim::simtrace(int eventID)
     588 {
     589     sev->beginOfEvent(eventID);
     590 
     591     NP* igs = sev->makeGenstepArrayFromVector();
     592     int rc = event->setGenstepUpload_NP(igs) ;
     593 
     594     LOG_IF(error, rc != 0) << " QEvent::setGenstep ERROR : no gensteps collected : will skip cx.simtrace " ;
     595 
     596     sev->t_PreLaunch = sstamp::Now() ;
     597     double dt = rc == 0 && cx != nullptr ? cx->simtrace_launch() : -1. ;
     598     sev->t_PostLaunch = sstamp::Now() ;
     599     sev->t_Launch = dt ;
     600 
     601     // see ~/o/notes/issues/cxt_min_simtrace_revival.rst
     602     sev->gather();
     603 
     604     sev->topfold->concat();
     605     sev->topfold->clear_subfold();
     606 
     607     sev->endOfEvent(eventID);
     608 
     609     return dt ;
     610 }



Investigate simtrace frame control 
------------------------------------



BP=SFrameGenstep::MakeCenterExtentGenstep cxt_min.sh 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    (gdb) bt
    #0  SFrameGenstep::MakeCenterExtentGenstep (ce=..., cegs=std::vector of length 8, capacity 8 = {...}, gridscale=0.100000001, geotran=0x1352fbd0, ce_offset=std::vector of length 1, capacity 1 = {...}, ce_scale=true)
        at /home/blyth/opticks/sysrap/SFrameGenstep.cc:322
    #1  0x00007ffff5af8699 in SFrameGenstep::MakeCenterExtentGenstep_FromFrame (fr=...) at /home/blyth/opticks/sysrap/SFrameGenstep.cc:202
    #2  0x00007ffff5b35538 in SEvt::addInputGenstep (this=0xf14b7f0) at /home/blyth/opticks/sysrap/SEvt.cc:760
    #3  0x00007ffff5b38a01 in SEvt::beginOfEvent (this=0xf14b7f0, eventID=0) at /home/blyth/opticks/sysrap/SEvt.cc:1557
    #4  0x00007ffff606f106 in QSim::simtrace (this=0x1352dd80, eventID=0) at /home/blyth/opticks/qudarap/QSim.cc:589
    #5  0x00007ffff7e46177 in CSGOptiX::simtrace (this=0x13541ef0, eventID=0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:721
    #6  0x00007ffff7e42b25 in CSGOptiX::SimtraceMain () at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:158
    #7  0x0000000000404a75 in main (argc=1, argv=0x7fffffffba08) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXTMTest.cc:13
    (gdb) 

    (gdb) f 2
    #2  0x00007ffff5b35538 in SEvt::addInputGenstep (this=0xf14b7f0) at /home/blyth/opticks/sysrap/SEvt.cc:760
    760	        NP* gs = SFrameGenstep::MakeCenterExtentGenstep_FromFrame(frame);
    (gdb) l
    755	        {
    756	            LOG(LEVEL) << " non-default frs " << frs << " passed to SEvt::SetReldir " ;
    757	            SEventConfig::SetEventReldir(frs);
    758	        }
    759	
    760	        NP* gs = SFrameGenstep::MakeCenterExtentGenstep_FromFrame(frame);
    761	        LOG(LEVEL) << " simtrace gs " << ( gs ? gs->sstr() : "-" ) ;
    762	        addGenstep(gs);
    763	
    764	        if(frame.is_hostside_simtrace()) setFrame_HostsideSimtrace();
    (gdb) 



BP=SEvt::setFrame SEvt__FRAME=1 cxt_min.sh
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (gdb) bt
    #0  SEvt::setFrame (this=0xf14b7f0, fr=...) at /home/blyth/opticks/sysrap/SEvt.cc:668
    #1  0x00007ffff5b37a16 in SEvt::SetFrame (fr=...) at /home/blyth/opticks/sysrap/SEvt.cc:1201
    #2  0x00007ffff7652641 in CSGFoundry::AfterLoadOrCreate () at /home/blyth/opticks/CSG/CSGFoundry.cc:3721
    #3  0x00007ffff764fc0c in CSGFoundry::Load () at /home/blyth/opticks/CSG/CSGFoundry.cc:3092
    #4  0x00007ffff7e42b00 in CSGOptiX::SimtraceMain () at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:156
    #5  0x0000000000404a75 in main (argc=1, argv=0x7fffffffb9f8) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXTMTest.cc:13
    (gdb) 

::

    3698 /**
    3699 CSGFoundry::AfterLoadOrCreate
    3700 -------------------------------
    3701 
    3702 Called from some high level methods eg: CSGFoundry::Load
    3703 
    3704 The idea behind this is to auto connect SEvt with the frame
    3705 from the geometry.
    3706 
    3707 HMM: not called after Create, see CSGOptiX::initFrame
    3708 
    3709 **/
    3710 
    3711 void CSGFoundry::AfterLoadOrCreate() // static
    3712 {
    3713     CSGFoundry* fd = CSGFoundry::Get();
    3714 
    3715     SEvt::CreateOrReuse() ;   // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE
    3716 
    3717     if(!fd) return ;
    3718 
    3719     sframe fr = fd->getFrameE() ;
    3720     LOG(LEVEL) << fr ;
    3721     SEvt::SetFrame(fr); // now only needs to be done once to transform input photons
    3722 
    3723 }


    3660 sframe CSGFoundry::getFrameE() const
    3661 {
    3662     bool VERBOSE = ssys::getenvbool(getFrameE_VERBOSE) ;
    3663     LOG(LEVEL) << "[" << getFrameE_VERBOSE << "] " << VERBOSE ;
    3664 
    3665     sframe fr = {} ;
    3666 
    3667     if(ssys::getenvbool("INST"))
    3668     {
    3669         int INST = ssys::getenvint("INST", 0);
    3670         LOG_IF(info, VERBOSE) << " INST " << INST ;
    3671         getFrame(fr, INST ) ;
    3672 
    3673         fr.set_ekv("INST");
    3674     }
    3675     else if(ssys::getenvbool("MOI"))
    3676     {
    3677         const char* MOI = ssys::getenvvar("MOI", nullptr) ;
    3678         LOG_IF(info, VERBOSE) << " MOI " << MOI ;
    3679         fr = getFrame() ;
    3680         fr.set_ekv("MOI");
    3681     }
    3682     else
    3683     {
    3684         const char* ipf_ = SEventConfig::InputPhotonFrame();  // OPTICKS_INPUT_PHOTON_FRAME
    3685         const char* ipf = ipf_ ? ipf_ : "0" ;
    3686         LOG_IF(info, VERBOSE) << " ipf " << ipf ;
    3687         fr = getFrame(ipf);
    3688 
    3689         fr.set_ekv(SEventConfig::kInputPhotonFrame, ipf );
    3690     }
    3691 
    3692 
    3693     return fr ;
    3694 }


Problem was using MOI of sChimneyLS:0:-1 when need sChimneyLS:0:-2 to get the frame transforms. 

Now can cycle on the below to see 2D matplotlib cross sections::

    (ok) A[blyth@localhost CSGOptiX]$ MOI
    (ok) A[blyth@localhost CSGOptiX]$ cxt_min.sh 


Hmm would be good to color the simtrace intersects with boundary/material indices
-------------------------------------------------------------------------------------

::

    431     trace(
    432         params.handle,
    433         pos,
    434         mom,
    435         params.tmin,
    436         params.tmax,
    437         prd,
    438         params.vizmask
    439     );
    440 
    441     evt->add_simtrace( idx, p, prd, params.tmin );
    442     // not photon_idx, needs to go from zero for photons from a slice of genstep array
    443 }

::

    sevent::add_simtrace : fills simtrace[idx] with values from p, prd  
    --------------------------------------------------------------------

    NB simtrace "photon" *a* is very different from real sphoton.

    a.q0.f
        prd.q0.f normal, distance, aka "isect" 
    a.q1
        intersect position from pos+t*dir, 0.
    a.q2
        initial pos, prd.boundary (formerly tmin)
    a.q3 
        initial dir, prd.identity



    +----+----------------+----------------+----------------+----------------+--------------------------+
    | q  |      x         |      y         |     z          |      w         |  notes                   |
    +====+================+================+================+================+==========================+
    |    |  nrm.x         |  nrm.y         |  nrm.z         |  t/distance    | surface normal at isect, |
    | q0 |                |                |                |                | ray trace distance       |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  pos.x         |  pos.y         | pos.z          |  tmin          | intersect_position, tmin |
    | q1 |                |                |                |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  pos0.x        |  pos0.y        |  pos0.z        | (unsigned)     | origin_position,boundary |
    | q2 |                |                |                | boundary       |                          |
    |    |                |                |                | (2,3)          |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    | dir0.x         |  dir0.y        |  dir0.z        | (unsigned)     | initial direction, id    |
    | q3 | (3,0)          |                |                | identity       |                          |
    |    |                |                |                | (3,3)          |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+

    NB : simtrace has almost totally different content and layout compared with photon and record






There is old and over complicated machinery that does this kinda thing::

    ana/feature.py
    ana/simtrace_plot.py
    CSGOptix/tests/CSGOptiXSimtraceTest.py

::

    lob
    lco

    cxt_min.sh pdb

::

    In [4]: bn = st[:,2,3].view(np.int32) ; bn
    Out[4]: array([116, 116, 103, 103, 103, ...,  24,  24,  24,  54,  24], shape=(1254000,), dtype=int32)


    In [6]: bn_u, bn_n, bn_x = np.unique(bn, return_counts=True, return_index=True)

    In [7]: np.c_[bn_u, bn_n, bn_x]
    Out[7]: 
    array([[     24,   24005,  160543],
           [     25,   24050,   17001],
           [     54,   24000,   89521],
           [     55,   14003,   78195],
           [     78,   14018,   43155],
           [     79,   14000,    8292],
           [     80,   14005,    1383],
           [     81,   14274,     716],
           [     82,   16616,      89],
           [    101,   14002,  164646],
           [    102,     144,   24680],
           [    103,       2,  216135],
           [    104,  538502,    4275],
           [    116,       0,  217008],
           [    117,  430001,    1027],
           [    118,  396070,     970],
           [    119,  228055,     984],
           [    120,  126000,   18932],
           [    121,  126010,     700],
           [    122,  126025,     647],
           [    123,  126019,     120],
           [    124,  126008,      60],
           [    125,  128000,    1418],
           [    126,  126003,     345],
           [    127,  126054,    1778],
           [    128,   52003,    1489],
           [    129,   12000,   16919],
           [    130, 1076039,     289],
           [    131, 1076022,     302],
           [    132, 1076056,     412],
           [    133, 1076046,      78],
           [    136,  236071,       2],
           [    138,  532000,  123299],
           [    295,   24026,   46590],
           [    296,  330000,   12000]])



::

    In [14]: np.c_[bn_u, bn_n, bn_x, cf.bdn[bn_u]]
    Out[14]: 
    array([['24', '24005', '160543', 'DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek'],
           ['25', '24050', '17001', 'Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater'],
           ['54', '24000', '89521', 'Air/CDTyvekSurface//Tyvek'],
           ['55', '14003', '78195', 'Tyvek//Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pCentralDetector/Water'],
           ['78', '14018', '43155', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_GLb3.up11_HBeam_phys//LatticedShellSteel'],
           ['79', '14000', '8292', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_GLb4.up10_HBeam_phys//LatticedShellSteel'],
           ['80', '14005', '1383', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_GLb3.up09_HBeam_phys//LatticedShellSteel'],
           ['81', '14274', '716', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_GLb2.up08_HBeam_phys//LatticedShellSteel'],
           ['82', '16616', '89', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_GLb2.up07_HBeam_phys//LatticedShellSteel'],
           ['101', '14002', '164646', 'Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pInnerReflector//Tyvek'],
           ['102', '144', '24680', 'Tyvek//CDInnerTyvekSurface/Water'],
           ['103', '2', '216135', 'Water///Acrylic'],
           ['104', '538502', '4275', 'Acrylic///LS'],
           ['116', '0', '217008', 'Water///Water'],
           ['117', '430001', '1027', 'Water///AcrylicMask'],
           ['118', '396070', '970', 'Water/HamamatsuMaskOpticalSurface//CDReflectorSteel'],
           ['119', '228055', '984', 'Water///Pyrex'],
           ['120', '126000', '18932', 'Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum'],
           ['121', '126010', '700', 'Vacuum/HamamatsuR12860_PMT_20inch_dynode_plate_opsurface//Steel'],
           ['122', '126025', '647', 'Vacuum/HamamatsuR12860_PMT_20inch_outer_edge_opsurface//Steel'],
           ['123', '126019', '120', 'Vacuum/HamamatsuR12860_PMT_20inch_inner_edge_opsurface//Steel'],
           ['124', '126008', '60', 'Vacuum/HamamatsuR12860_PMT_20inch_inner_ring_opsurface//Steel'],
           ['125', '128000', '1418', 'Vacuum/HamamatsuR12860_PMT_20inch_dynode_tube_opsurface//Steel'],
           ['126', '126003', '345', 'Vacuum/HamamatsuR12860_PMT_20inch_grid_opsurface//Steel'],
           ['127', '126054', '1778', 'Vacuum/HamamatsuR12860_PMT_20inch_shield_opsurface//Steel'],
           ['128', '52003', '1489', 'Water/NNVTMaskOpticalSurface//CDReflectorSteel'],
           ['129', '12000', '16919', 'Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum'],
           ['130', '1076039', '289', 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_edge_opsurface//Steel'],
           ['131', '1076022', '302', 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_plate_opsurface//Steel'],
           ['132', '1076056', '412', 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_tube_opsurface//Steel'],
           ['133', '1076046', '78', 'Vacuum/NNVTMCPPMT_PMT_20inch_mcp_opsurface//Steel'],
           ['136', '236071', '2', 'Water/Implicit_RINDEX_NoRINDEX_PMT_3inch_log_phys_PMT_3inch_cntr_phys//Steel'],
           ['138', '532000', '123299', 'Water/Steel_surface//Steel'],
           ['295', '24026', '46590', 'Air///Water'],
           ['296', '330000', '12000', 'Pyrex/PMT_20inch_veto_photocathode_mirror_logsurf/PMT_20inch_veto_photocathode_mirror_logsurf/Vacuum']], dtype='<U122')

    In [15]: 


Plotting only intersects from one BND::

     1013  BND=DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek ./cxt_min.sh pdb
     1014  BND=Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater ./cxt_min.sh pdb

Add regexp selection of boundaries::

    BND='DeadWater/.*/Tyvek$' ./cxt_min.sh pdb





cxt_min.sh Water/Tyvek/Water
---------------------------------


red:magenta:tomato::

         .akk :   .u       .n       .x : .b 
          red :  116  1216557        0 : Water///Water 
      magenta :  101   980127    14002 : Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pInnerReflector//Tyvek 
       tomato :  102   252625      144 : Tyvek//CDInnerTyvekSurface/Water 
         .akk :   .u       .n       .x : .b 


magenta/tomato : thin layer of Tyvek with Water on both sides

* coincident at top
* very close on sides


::

        .
                                         |
                     +---+---mag+tom---------------------+------+---+
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                     |   |    <-|                        |->    |   |
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |
                  mag  tom     red                      red   tom   mag 
                     |   |      |                        |      |   |
                     |   |      |                        |      |   |  
                     | <-|    Wa|Wa                    Wa|Wa    |   |-> Water     (normal points "outside" shape)
                     |   |      |                        |      |   |
                  Wa |Ty |Wa    |                        |      |   |
                   <-|   |      |                        |   Wa |Ty | Wa
                     |   |      |                        |      |-> |
                     |   |      |                        |      |   |
       --------------+   |      |                        |      |   +-------------------
                         |      |                        |      |                then curving down around circle
       ------------------+      |                        |      +-----------------------  
                                |                        |
                                |                        |
                                |                        |
                                |                        |
                                |                        |
                              
                                    
                             
                            
::

    A[blyth@localhost CSGOptiX]$ jgr CDInnerTyvekSurface
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:                                                                                  "CDInnerTyvekSurface", 
                                  
                           
     648        // The optical surface from inner water to tyvek.
     649        if (m_isCDInnerReflectorEnabled) {
     650            LogInfo << "m_isCDInnerReflectorEnabled is " << m_isCDInnerReflectorEnabled
     651                    << ", so the reflector from inner water to tyvek will be setup. "
     652                    << std::endl;
     653            G4OpticalSurface* inner_tyvek_surface = new G4OpticalSurface("CDInnerTyvekOpticalSurface");
     654            inner_tyvek_surface->SetMaterialPropertiesTable(G4Material::GetMaterial("CDReflectorSteel")->GetMaterialPropertiesTable());
     655            inner_tyvek_surface->SetModel(unified);
     656            inner_tyvek_surface->SetType(dielectric_metal);
     657            inner_tyvek_surface->SetFinish(ground);
     658            inner_tyvek_surface->SetSigmaAlpha(0.2);
     659 
     660            G4LogicalBorderSurface* innerTyvekSurface = new G4LogicalBorderSurface(
     661                                                                                   "CDInnerTyvekSurface",
     662                                                                                   cd_inner_water,
     663                                                                                   cd_inner_reflector,
     664                                                                                   inner_tyvek_surface);
     665 
     666        }




::

    [IdentityTable
    array([[       0, 16599110,        2],
           [       1,   165400,       11],
           [   50009,   123227,   748005],
           [      14,    82701,   722011],
           [   50001,    64583,    24047],
           [   50008,    49640,   750030],
           [      42,    38092,       15],
           [      56,    37860,   722014],
           [      21,    34524,       54],
           [      41,    28329,       10],
           [      32,    24117,   722013],
           [      87,    22458,   722000],
           [      70,    22073,        8],
           [     145,    10592,       46],
           [     125,    10564,   722049],
           [     168,     7173,   722035],
           [     146,     6809,       18],
           [   50071,     6402,   752074],
           [   50056,     5369,    24026],
           [     243,     4764,        0],
           [     217,     4713,   722081],
           [     273,     4242,   722268],
           [     244,     4121,       17],
           [     490,     3864,       53],
           [     454,     3751,   722057],
           [     335,     3524,   722068],
           [     759,     3500,   722231],
           [     418,     3437,       81],
           [     367,     3361,       70],
           [     714,     3296,        1],
           [     960,     3266,   722004],
           [    1388,     3003,   724089],
           [    1183,     2933,   722310],
           [     908,     2932,      223],
           [     531,     2761,   722188],
           [    1126,     2745,       56],
           [    1324,     2637,      262],
           [    1644,     2255,   726178],
           [     393,     2193,   722468],
           [    1580,     2036,       19],
           [    1905,     1641,   728047],
           [   32674,     1397,   723864],
           [    1961,     1349,       66],
           [   32194,     1341,      515],
           [    2174,     1241,   730157],
           [   32834,     1116,   722574],
           [   32192,     1064,      137],
           [    2245,      966,      105],
           [     419,      963,      774],
           [    1779,      926,   726147],
           [    1708,      827,      332],
           [   32740,      819,   722293],
           [   32159,      794,     1013],
           [   31411,      763,   722260],
           [   30779,      737,      802],
           [   50116,      676,   796323],
           [    2325,      627,   732256],
           [    2484,      611,   732636],
           [    2033,      604,   729078],
           [    2246,      592,      167],
           [    1962,      487,      238],
           [   31430,      484,   724620],
           [   30706,      442,      684],
           [   50086,      439,    30203],
           [   30786,      413,      366],
           [   31403,      361,   724468],
           [   32036,      309,      128],
           [   32832,      285,   723433],
           [    2643,      273,   736004],
           [    2563,      269,     1241],



Better simtrace identification for global ? With CSGPrim idx ?  
---------------------------------------------------------------

GAS idx and inst idx are no help... need identity within the 
global GAS. Presumably via CSGPrim idx ? 
Yes added globalPrimIdx to Binding and passed it out. 

But is the globalPrimIdx useful at stree level ? 
Can get name from the primname.txt



