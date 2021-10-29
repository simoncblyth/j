Sticks
=========


LSExpDetectorConstruction::setupCD_Sticks  : class review
--------------------------------------------------------------------------------------------------

* "jcv LSExpDetectorConstruction"
* bizarre way of building a geometry using so many classes


Sticks using m_strut_pos_file
---------------------------------

jcv StrutAcrylicConstruction::

    132         solidStrut = new G4Tubs(
    133                         "sStrut",
    134                         m_radStrut_in,
    135                         m_radStrut_out,
    136                         m_lengthStrut/2,
    137                         0*deg,
    138                         360*deg);
    139     
    140     
    141         logicStrut = new G4LogicalVolume(
    142                         solidStrut,
    143                         Steel,
    144                         "lSteel",
    145                         0,
    146                         0,
    147                         0);
    148         G4cout<< "m_radStrut = "<<m_radStrut_out<<G4endl;


    JUNO::Ball::HexagonPosBall(m_strut_pos_file,strut_r,false)


Sticks using m_strut2_pos_file
---------------------------------

jcv StrutBar2AcrylicConstruction::

    124         solidStrut = new G4Tubs(
    125                         "sStrut",
    ###  NOTE DUPLICATED SOLID NAME
    126                         m_radStrut_in,
    127                         m_radStrut_out,
    128                         m_lengthStrut/2,
    129                         0*deg,
    130                         360*deg);
    131     
    132     
    133         logicStrut = new G4LogicalVolume(
    134                         solidStrut,
    135                         Steel,
    136                         "lSteel2",
    137                         0,
    138                         0,
    139                         0);



    JUNO::Ball::HexagonPosBall(m_strut2_pos_file,strut2_r,false)

    StrutBar2AcrylicConstruction is very similar to StrutAcrylicConstruction
    it is very poor style to duplicate a class and then make a small change.
    It is much clearer and easier to maintain to simply add arguments to the ctor. 


Sticks using m_fastener_pos_file
-----------------------------------

jcv StrutBallheadAcrylicConstruction::

    G4Orb("sStrutBallhead")
    JUNO::Ball::HexagonPosBall(m_fastener_pos_file,strutballhead_r,false)

jcv FastenerAcrylicConstruction "Greek temple"::

    "uni1" : union of G4Tubs "IonRing" and 8 "screw"
    
    G4Tubs("IonRing",123*mm,206.2*mm,7*mm,0.0*deg,360.0*deg); 
    G4Tubs("screw",0,13*mm,50.*mm,0.0*deg,360.0*deg);

    JUNO::Ball::HexagonPosBall(m_fastener_pos_file,fastener_r,false)

jcv UpperAcrylicConstruction::

    G4Polycone("base_steel",0.0*deg,360.0*deg,4,ZUpper4,RminUpper4,RmaxUpper4)

    JUNO::Ball::HexagonPosBall(m_fastener_pos_file,upper_r,false)

jcv AdditionAcrylicConstruction::

    uni_acrylic3 : familiar abomination of CSG subtraction   

    115         solidAddition_down = new G4Polycone("solidAddition_down",0.0*deg,360.0*deg,3,ZNodes3,RminNodes3,RmaxNodes3);
    117     }
    119     
    122     solidAddition_up = new G4Sphere("solidAddition_up",0*mm,17820*mm,0.0*deg,360.0*deg,0.0*deg,180.*deg);
    124     uni_acrylic1 = new G4SubtractionSolid("uni_acrylic1",solidAddition_down,solidAddition_up,0,G4ThreeVector(0*mm,0*mm,+17820.0*mm));
    125     
    126     solidAddition_up1 = new G4Tubs("solidAddition_up1",120*mm,208*mm,15.2*mm,0.0*deg,360.0*deg);
    127     uni_acrylic2 = new G4SubtractionSolid("uni_acrylic2",uni_acrylic1,solidAddition_up1,0,G4ThreeVector(0.*mm,0.*mm,-20*mm));
    128     solidAddition_up2 = new G4Tubs("solidAddition_up2",0,14*mm,52.5*mm,0.0*deg,360.0*deg);
    129     
    130     for(int i=0;i<8;i++)
    131     {
    132     uni_acrylic3 = new G4SubtractionSolid("uni_acrylic3",uni_acrylic2,solidAddition_up2,0,G4ThreeVector(164.*cos(i*pi/4)*mm,164.*sin(i*pi/4)*mm,-87.5));
    133     uni_acrylic2 = uni_acrylic3;
    135     }
    138     logicAddition = new G4LogicalVolume(
    139             uni_acrylic2,// solidAddition_down,
    140             Acrylic,
    141             "lAddition",
    142             0,
    143             0,
    144             0);


    JUNO::Ball::HexagonPosBall(m_fastener_pos_file,addition_r,false)


Sticks using m_xjanchor_pos_file
-----------------------------------

jcv XJanchorConstruction::

    G4UnionSolid("solidXJanchor",solidXJanchor_sub, solidXJanchor_up, 0, G4ThreeVector(0.*mm, 0*mm,-16.5*mm));

    //solidXJanchor_up   = new G4Cons("solidXJanchor_up", 0.*mm, 31.7*mm, 0.*mm, 25*mm, 13./2*mm, 0.*deg, 360.0*deg);
    solidXJanchor_up   = new G4Tubs("solidXJanchor_up", 0.*mm, 25.*mm, 13./2*mm, 0.*deg, 360.*deg);
    solidXJanchor_down = new G4Cons("solidXJanchor_down", 0.*mm, 47.*mm, 0.*mm, 73.*mm, 10.*mm, 0.*deg, 360.*deg);   // to subtract the ball
    //solidXJanchor_down = new G4Cons("solidXJanchor_down", 0.*mm, 47.*mm, 0.*mm, 60.*mm, 5.*mm, 0.*deg, 360.*deg); // original size
    solidXJanchor_ball = new G4Sphere("solidXJanchor_ball", 0.*mm, 17820.*mm, 0.*deg, 360.*deg, 0.*deg, 180.*deg); 
    G4SubtractionSolid* solidXJanchor_sub = new G4SubtractionSolid("solidXJanchor_sub",solidXJanchor_down, solidXJanchor_ball, 0, G4ThreeVector(0.*mm, 0*mm,  17820.*mm));
    G4UnionSolid* solidXJanchor = new G4UnionSolid("solidXJanchor",solidXJanchor_sub, solidXJanchor_up, 0, G4ThreeVector(0.*mm, 0*mm,-16.5*mm));
    logicXJanchor = new G4LogicalVolume(
        solidXJanchor,
        Acrylic,
        "lXJanchor",
        0,  
        0,  
        0); 

    ## another one that subtracts acrylic sphere 

    JUNO::Ball::HexagonPosBall(m_xjanchor_pos_file,xjanchor_r,false);


jcv XJfixtureConstruction::

    // fixture part
    solidXJfixture_down1 = new G4Tubs("solidXJfixture_down1", 25.*mm, 45.*mm, 13./2*mm, 0.*deg, 360.*deg);
    solidXJfixture_down2 = new G4Box("solidXJfixture_down2", 10.*mm, 11.5*mm, 13/2.*mm);
    solidXJfixture_down_uni1 = new G4UnionSolid("solidXJfixture_down_uni1", solidXJfixture_down1, solidXJfixture_down2, 0, G4ThreeVector(52.*mm, 0.*mm, 0.*mm));
    solidXJfixture_down_uni2 = new G4UnionSolid("solidXJfixture_down_uni2", solidXJfixture_down_uni1, solidXJfixture_down2, 0, G4ThreeVector(-52.*mm, 0.*mm, 0.*mm));
    solidXJfixture_down3 = new G4Box("solidXJfixture_down3", 15.*mm, 15.*mm, 13/2.*mm);
    solidXJfixture_down_uni3 = new G4UnionSolid("solidXJfixture_down_uni3", solidXJfixture_down_uni2, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, 50.*mm, 0.*mm));
    solidXJfixture_down_uni4 = new G4UnionSolid("solidXJfixture_down_uni4", solidXJfixture_down_uni3, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, -50.*mm, 0.*mm));

    // cover part
    solidXJfixture_up1 = new G4Box("solidXJfixture_up1", 15.*mm, 40.*mm, 17/2.*mm);    
    solidXJfixture_up2 = new G4Box("solidXJfixture_up2", 15.*mm, 65*mm, 5.*mm);
    solidXJfixture_up_uni = new G4UnionSolid("solidXJfixture_up_uni", solidXJfixture_up1, solidXJfixture_up2, 0, G4ThreeVector(0.*mm, 0.*mm, 13.5*mm));

    // union 
    solidXJfixture = new G4UnionSolid("solidXJfixture", solidXJfixture_down_uni4, solidXJfixture_up_uni, 0, G4ThreeVector(0.*mm, 0.*mm, -25.*mm));

    logicXJfixture = new G4LogicalVolume(
        solidXJfixture,
        //Acrylic,
        PE_PA,
        "lXJfixture",
        0,  
        0,  
        0); 


    JUNO::Ball::HexagonPosBall(m_xjanchor_pos_file,xjfixture_r,false)



Sticks using m_sjclsanchor_pos_file
---------------------------------------

jcv SJCLSanchorConstruction::

    solidSJCLSanchor_up   = new G4Box("solidSJCLSanchor_up", 25.*mm, 20.*mm, 13/2.*mm);
    solidSJCLSanchor_down = new G4Cons("solidSJCLSanchor_down", 0.*mm, 73.*mm, 0.*mm, 47.*mm, 10.*mm, 0.*deg, 360.*deg);   // to subtract the ball
    solidSJCLSanchor_box = new G4Box("solidSJCLSanchor_box", 17780.*mm, 17780.*mm, 17780.*mm);
    solidSJCLSanchor_ball = new G4Sphere("solidSJCLSanchor_ball", 0.*mm, 17700.*mm, 0.*deg, 360.*deg, 0.*deg, 180.*deg); 
    G4SubtractionSolid* solidSphere_sub = new G4SubtractionSolid("solidSphere_sub", solidSJCLSanchor_box, solidSJCLSanchor_ball);
    G4SubtractionSolid* solidSJCLSanchor_sub = new G4SubtractionSolid("solidSJCLSanchor_sub",solidSJCLSanchor_down, solidSphere_sub, 0, G4ThreeVector(0.*mm, 0*mm,  17699.938*mm));
    G4UnionSolid* solidSJCLSanchor = new G4UnionSolid("solidSJCLSanchor",solidSJCLSanchor_sub, solidSJCLSanchor_up, 0, G4ThreeVector(0.*mm, 0*mm,16.5*mm));
    logicSJCLSanchor = new G4LogicalVolume(
        solidSJCLSanchor,
        Acrylic,
        "lSJCLSanchor",
        0,  
        0,  
        0); 


    subtracts big sphere of radius 17700mm, different from above subtraction of 17820mm

    big ball and box subtractions

    JUNO::Ball::HexagonPosBall(m_sjclsanchor_pos_file,sjclsanchor_r,false); 


Sticks using m_sjfixture_pos_file
------------------------------------

jcv SJFixtureConstruction::

    solidSJFixture_up   = new G4Box("solidSJFixture_up", 20.*mm, 7.*mm, 13/2.*mm);
    solidSJFixture_down = new G4Cons("solidSJFixture_down", 0.*mm, 30.*mm, 0.*mm, 20.*mm, 10.*mm, 0.*deg, 360.*deg);   // to subtract the ball
    solidSJFixture_box = new G4Box("solidSJFixture_box", 17780.*mm, 17780.*mm, 17780.*mm);
    solidSJFixture_ball = new G4Sphere("solidSJFixture_ball", 0.*mm, 17700.*mm, 0.*deg, 360.*deg, 0.*deg, 180.*deg); 
    G4SubtractionSolid* solidSphere_sub = new G4SubtractionSolid("solidSphere_sub", solidSJFixture_box, solidSJFixture_ball);
    G4SubtractionSolid* solidSJFixture_sub = new G4SubtractionSolid("solidSJFixture_sub",solidSJFixture_down, solidSJFixture_ball, 0, G4ThreeVector(0.*mm, 0*mm,  -17699.975*mm));
    G4UnionSolid* solidSJFixture = new G4UnionSolid("solidSJFixture",solidSJFixture_sub, solidSJFixture_up, 0, G4ThreeVector(0.*mm, 0*mm,16.5*mm));
    logicSJFixture = new G4LogicalVolume(
        solidSJFixture,
        Acrylic,
        "lSJFixture",
        0,  
        0,  
        0); 


     JUNO::Ball::HexagonPosBall(m_sjfixture_pos_file,sjfixture_r,false)


Sticks using m_sjreceiver_pos_file
------------------------------------

jcv SJReceiverConstruction::

    088     solidSJReceiver_up = new G4Tubs("solidXJanchor_up", 0.*mm, 25.*mm, 13./2*mm, 0.*deg, 360.*deg);
     89     solidSJReceiver_down = new G4Cons("solidSJReceiver_down", 0.*mm, 73.*mm, 0.*mm, 47.*mm, 10.*mm, 0.*deg, 360.*deg);   // to subtract the ball
     91     solidSJReceiver_box = new G4Box("solidSJReceiver_box", 17780.*mm, 17780.*mm, 17780.*mm);
     92     solidSJReceiver_ball = new G4Sphere("solidSJReceiver_ball", 0.*mm, 17700.*mm, 0.*deg, 360.*deg, 0.*deg, 180.*deg);
     93     G4SubtractionSolid* solidSphere_sub = new G4SubtractionSolid("solidSphere_sub", solidSJReceiver_box, solidSJReceiver_ball);
     94     G4SubtractionSolid* solidSJReceiver_sub = new G4SubtractionSolid("solidSJReceiver_sub",solidSJReceiver_down, solidSJReceiver_ball, 0, G4ThreeVector(0.*mm, 0*mm,  17699.938*mm));
     95     G4UnionSolid* solidSJReceiver = new G4UnionSolid("solidSJReceiver",solidSJReceiver_sub, solidSJReceiver_up, 0, G4ThreeVector(0.*mm, 0*mm,16.5*mm));
     96     logicSJReceiver = new G4LogicalVolume(
     97         solidSJReceiver,
     98         Acrylic,
     99         "lSJReceiver",
    100         0,
    101         0,
    102         0);

    JUNO::Ball::HexagonPosBall(m_sjreceiver_pos_file,sjreceiver_r,false)


jcv XJfixtureConstruction::

    085 // fixture part
     86     solidXJfixture_down1 = new G4Tubs("solidXJfixture_down1", 25.*mm, 45.*mm, 13./2*mm, 0.*deg, 360.*deg);
     87     solidXJfixture_down2 = new G4Box("solidXJfixture_down2", 10.*mm, 11.5*mm, 13/2.*mm);
     88     solidXJfixture_down_uni1 = new G4UnionSolid("solidXJfixture_down_uni1", solidXJfixture_down1, solidXJfixture_down2, 0, G4ThreeVector(52.*mm, 0.*mm, 0.*mm));
     89     solidXJfixture_down_uni2 = new G4UnionSolid("solidXJfixture_down_uni2", solidXJfixture_down_uni1, solidXJfixture_down2, 0, G4ThreeVector(-52.*mm, 0.*mm, 0.*mm));
     90     solidXJfixture_down3 = new G4Box("solidXJfixture_down3", 15.*mm, 15.*mm, 13/2.*mm);
     91     solidXJfixture_down_uni3 = new G4UnionSolid("solidXJfixture_down_uni3", solidXJfixture_down_uni2, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, 50.*mm, 0.*mm));
     92     solidXJfixture_down_uni4 = new G4UnionSolid("solidXJfixture_down_uni4", solidXJfixture_down_uni3, solidXJfixture_down3, 0, G4ThreeVector(0.*mm, -50.*mm, 0.*mm));
     93 
     94 // cover part
     95     solidXJfixture_up1 = new G4Box("solidXJfixture_up1", 15.*mm, 40.*mm, 17/2.*mm);
     96     solidXJfixture_up2 = new G4Box("solidXJfixture_up2", 15.*mm, 65*mm, 5.*mm);
     97     solidXJfixture_up_uni = new G4UnionSolid("solidXJfixture_up_uni", solidXJfixture_up1, solidXJfixture_up2, 0, G4ThreeVector(0.*mm, 0.*mm, 13.5*mm));
     98     
     99 // union 
    100     solidXJfixture = new G4UnionSolid("solidXJfixture", solidXJfixture_down_uni4, solidXJfixture_up_uni, 0, G4ThreeVector(0.*mm, 0.*mm, -25.*mm));
    101     
    102     logicXJfixture = new G4LogicalVolume(
    103         solidXJfixture,
    104         //Acrylic,
    105         PE_PA,
    106         "lXJfixture",
    107         0,
    108         0,
    109         0);

    JUNO::Ball::HexagonPosBall(m_sjreceiver_pos_file,sjreceiver_fastener_r,false)


