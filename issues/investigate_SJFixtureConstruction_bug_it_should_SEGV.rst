investigate_SJFixtureConstruction_bug_it_should_SEGV
=======================================================


Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc::

    097     G4UnionSolid* solidSJFixture = nullptr;
     98 
     99     if (m_simplify_calib_anchor){
    100 
    101     solidSJFixture_up   = new G4Box("solidSJFixture_up", 20.*mm, 7.*mm, 13/2.*mm);
    102     solidSJFixture_down = new G4Cons("solidSJFixture_down", 0.*mm, 25.*mm, 0.*mm, 20.*mm, 5.*mm, 0.*deg, 360.*deg);   // to subtract the ball
    103 
    104     solidSJFixture = new G4UnionSolid("solidSJFixture",solidSJFixture_down, solidSJFixture_up, 0, G4ThreeVector(0.*mm, 0*mm,11.5*mm));
    105     }
    106 
    107     else{
    108 
    109     solidSJFixture_up   = new G4Box("solidSJFixture_up", 20.*mm, 7.*mm, 13/2.*mm);
    110     solidSJFixture_down = new G4Cons("solidSJFixture_down", 0.*mm, 30.*mm, 0.*mm, 20.*mm, 10.*mm, 0.*deg, 360.*deg);   // to subtract the ball
    111     solidSJFixture_box = new G4Box("solidSJFixture_box", 17780.*mm, 17780.*mm, 17780.*mm);
    112     solidSJFixture_ball = new G4Sphere("solidSJFixture_ball", 0.*mm, m_radLS, 0.*deg, 360.*deg, 0.*deg, 180.*deg);
    113     G4SubtractionSolid* solidSphere_sub = new G4SubtractionSolid("solidSphere_sub", solidSJFixture_box, solidSJFixture_ball);
    114     G4SubtractionSolid* solidSJFixture_sub = new G4SubtractionSolid("solidSJFixture_sub",solidSJFixture_down, solidSJFixture_sub, 0, G4ThreeVector(0.*mm, 0*mm, m_radLS     - 0.025*mm  /*17699.975*mm*/ ));
    115     solidSJFixture = new G4UnionSolid("solidSJFixture",solidSJFixture_sub, solidSJFixture_up, 0, G4ThreeVector(0.*mm, 0*mm,16.5*mm));
    116 
    117     }
    

Line 114 uses uninitialized local variable "solidSJFixture_sub" 
which will usually be nullptr so a SEGV would be expected. 



Does that mean that m_simplify_calib_anchor always true explaining lack of SEGV ?  YES
----------------------------------------------------------------------------------------

::

     19 SJFixtureConstruction::SJFixtureConstruction(const std::string& name)
     20     : ToolBase(name)
     21 {
     22     logicSJFixture = 0;
     23 
     24     m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;
     25     initVariables();
     26 
     27 }

::

    N[blyth@localhost junosw]$ jgr JUNO_SIMPLIFY_CALIB_ANCHOR
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"]="Enable"
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        elif "JUNO_SIMPLIFY_CALIB_ANCHOR" in os.environ:
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            os.environ.pop("JUNO_SIMPLIFY_CALIB_ANCHOR")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            print("unset key : JUNO_SIMPLIFY_CALIB_ANCHOR ")       
    ./Simulation/DetSimV2/CentralDetector/src/SJCLSanchorConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    ./Simulation/DetSimV2/CentralDetector/src/SJReceiverConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    ./Simulation/DetSimV2/CentralDetector/src/XJanchorConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ; 
    ./Simulation/DetSimV2/CentralDetector/src/SJFixtureConstruction.cc:    m_simplify_calib_anchor = getenv("JUNO_SIMPLIFY_CALIB_ANCHOR") == nullptr ? false : true ;    
    ./Simulation/DetSimV2/DetSimMT/share/run.py:    os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"] = "Enable"
    N[blyth@localhost junosw]$ 


::


    0276         grp_calib_unit.add_argument("--simplify-calib-anchor", dest="simplify_calib_anchor", action="store_true", help=mh(""))
    0277         grp_calib_unit.add_argument("--no-simplify-calib-anchor", dest="simplify_calib_anchor", action="store_false", help=mh(""))
    0278         grp_calib_unit.set_defaults( simplify_calib_anchor = True )
    ....
    2051         #==========  simplify calib anchor ============#
    2052         if args.simplify_calib_anchor:
    2053             os.environ["JUNO_SIMPLIFY_CALIB_ANCHOR"]="Enable"
    2054         elif "JUNO_SIMPLIFY_CALIB_ANCHOR" in os.environ:
    2055             os.environ.pop("JUNO_SIMPLIFY_CALIB_ANCHOR")
    2056             print("unset key : JUNO_SIMPLIFY_CALIB_ANCHOR ")
    2057 

I added that switch long ago, but I dont recall setting the default to True ? 


Repeat the setting in standalone test, get a flat bottom::

   GEOM=sjfxSolid ~/opticks/u4/tests/U4Mesh_test2.sh



    
