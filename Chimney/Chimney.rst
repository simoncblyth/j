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



