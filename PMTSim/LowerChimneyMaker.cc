#include "Dimensions.hh"
#include "LowerChimneyMaker.hh"
#include "G4VSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"
#include <cassert>
#include <cmath>

LowerChimneyMaker::LowerChimneyMaker(double BlokerZ)
       {

           m_BlockerZ=BlokerZ*m;    // blocker center to chimney bottom
           m_WPHeight=WPHeight;
           
           m_TubeH=WPHeight/2.- ChimBtm_2_Center;

           m_Tyvek_thickness  =Tyvek_thickness  ;
           m_Acrylic_thickness=Acrylic_thickness;
           m_Steel_thickness  =Steel_thickness  ;
           m_Blocker_thickness=Blocker_thickness;
           
           m_TubeInnerR=TubeInnerR;
           m_TubeTyvekR=m_TubeInnerR+Tyvek_thickness;
           m_TubeAcrylicOuterR= m_TubeTyvekR + Acrylic_thickness;
           m_TubeSteelR=m_TubeTyvekR+ Steel_thickness;
           
           m_Inner_Box_Length=Inner_Box_Length;
           m_Inner_Box_Wideth=Inner_Box_Wideth;
           m_Inner_Box_Height=Inner_Box_Height;

         //  m_upperSteelTubeH = m_TubeH - m_BlockerZ - m_Inner_Box_Height
         //                              -m_Tyvek_thickness - m_Steel_thickness; 
           m_lowerSteelTubeH = lowerSteelTubeH ;
         
           //m_upperTyvekTubeH = m_TubeH - m_BlockerZ - m_Inner_Box_Height;
           //m_lowerTyvekTubeH = m_lowerSteelTubeH + m_Tyvek_thickness + m_Steel_thickness;
           // double CD_R=17.7*m+Acrylic_thickness;
           // double ChimBtm_2_Center=sqrt(CD_R*CD_R-TubeAcrylicOuterR*TubeAcrylicOuterR);

           //m_Blocker_2_SteelBtm= m_Inner_Box_Height/2 + m_Steel_thickness + m_lowerSteelTubeH;
           //m_TubeH=WPHeight/2.- m_BlockerZ + m_Blocker_2_Btm;
           //m_upperAcrylicHeight=m_TubeH -m_Inner_Box_Height -m_Steel_thickness*2. -m_lowerSteelTubeH -m_upperSteelTubeH;

           
       }
                           LowerChimneyMaker::~LowerChimneyMaker(){}



G4VSolid*
LowerChimneyMaker::getSolidLogical(){
    G4Tubs* tube= new G4Tubs(
                             "upper_tubeTyvek_tube",
                            0,      // pRMin,
                             m_TubeAcrylicOuterR+1.*cm, // pDz,
                             m_TubeH/2.,   // pRMax,
                             0*deg,     // pSPhi,
                             360*deg    // pDPhi
                             );

    double m_Box_Length=m_Inner_Box_Length+m_Tyvek_thickness;
    double m_Box_Wideth=m_Inner_Box_Wideth+m_Tyvek_thickness;
    double m_Box_Height=m_Inner_Box_Height+m_Tyvek_thickness;
    G4Box* middlebox= new G4Box(
                                "upper_tubeTyvek_box",
                                m_Box_Length/2.+m_Steel_thickness,
                                m_Box_Wideth/2.+m_Steel_thickness,
                                m_Box_Height/2.+m_Steel_thickness);

    G4UnionSolid* outer = new G4UnionSolid(
                                "upper_tubeTyvek",
                                tube,
                                middlebox,
                                0,
                                G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2)
                                );

    return outer;
}

////
G4VSolid*
LowerChimneyMaker::getSolidTyvek(){
    double m_Box_Length=m_Inner_Box_Length;
    double m_Box_Wideth=m_Inner_Box_Wideth;
    double m_Box_Height=m_Inner_Box_Height;
    
    
    G4Tubs* tmptube0= new G4Tubs(
                                "tmp_tubeTyvek0",
                                0,      // pRMin,
                                m_TubeTyvekR,   // pRMax,
                                m_TubeH/2., // pDz,
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );
    G4Tubs* tmptube= new G4Tubs(
                                "tmp_tubeTyvek",
                                m_TubeInnerR,      // pRMin,
                                m_TubeTyvekR,   // pRMax,
                                m_TubeH/2., // pDz,
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );

    G4Box* middlebox= new G4Box(
                                "middleboxTyvek",
                                m_Box_Length/2.+m_Tyvek_thickness,
                                m_Box_Wideth/2.+m_Tyvek_thickness,
                                m_Box_Height/2.+m_Tyvek_thickness);
    G4Box* middle_innerbox= new G4Box(
                                      "middle_innerboxTyvek",
                                      (m_Box_Length)/2.,
                                      (m_Box_Wideth)/2.,
                                      (m_Box_Height)/2.);

    G4SubtractionSolid* tyvektube =new G4SubtractionSolid(
                                                       "tyvekTube",
                                                       tmptube,
                                                       middle_innerbox,
                                                       0,
                                                       G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2.)
                                                       );

    G4SubtractionSolid* box =new G4SubtractionSolid(
                                                      "subbox0",
                                                      middlebox,
                                                      middle_innerbox,
                                                      0,
                                                      G4ThreeVector(0, 0,0)
                                                      );
    
    G4SubtractionSolid* solid0 =new G4SubtractionSolid(
                                                       "subbox",
                                                       box,
                                                       tmptube0,
                                                       0,
                                                       G4ThreeVector(0, 0,0)
                                                       );
    
    G4UnionSolid* solid1 = new G4UnionSolid(
                                            "unionLS1",
                                            tyvektube,
                                            solid0,
                                            0,
                                            G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2.)
                                            );
    return solid1;

}
////
G4VSolid*
LowerChimneyMaker::getSolidAcrylic(){

    double lowerAcrylicH=m_BlockerZ-m_Inner_Box_Height/2.-m_Tyvek_thickness-m_Steel_thickness - m_lowerSteelTubeH;
    G4Tubs* acrylictube= new G4Tubs(
                                "AcrylicTube",
                                m_TubeTyvekR,      // pRMin,
                                m_TubeAcrylicOuterR,   // pRMax, /////
                                lowerAcrylicH/2., 
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );
    return acrylictube;
}

G4VSolid*
LowerChimneyMaker::getSolidSteel(){
    double m_Box_Length=m_Inner_Box_Length+m_Tyvek_thickness;
    double m_Box_Wideth=m_Inner_Box_Wideth+m_Tyvek_thickness;
    double m_Box_Height=m_Inner_Box_Height+m_Tyvek_thickness;
    double lowerAcrylicH=m_BlockerZ-m_Inner_Box_Height/2.-m_Tyvek_thickness-m_Steel_thickness - m_lowerSteelTubeH;
    
    G4Tubs* tmptube0= new G4Tubs(
                                "tmp_tubeSteel0",
                                0,      // pRMin,
                                m_TubeTyvekR,   // pRMax, /////
                                m_TubeH/2., // pDz,
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );
    G4Tubs* tmptube1= new G4Tubs(
                                "tmp_tubeSteel1",
                                0,      // pRMin,
                                m_TubeSteelR+5*mm,   // pRMax, /////
                                lowerAcrylicH/2., 
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                ); 
    G4Tubs* tmptube= new G4Tubs(
                                "tmp_tubeSteel",
                                m_TubeTyvekR,      // pRMin,
                                m_TubeSteelR,   // pRMax, /////
                                m_TubeH/2., // pDz,
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );

    G4Box* middlebox= new G4Box(
                                "middleboxSteel",
                                m_Box_Length/2.+m_Steel_thickness,
                                m_Box_Wideth/2.+m_Steel_thickness,
                                m_Box_Height/2.+m_Steel_thickness);
    G4Box* middle_innerbox= new G4Box(
                                      "middle_innerboxSteel",
                                      (m_Box_Length)/2.,
                                      (m_Box_Wideth)/2.,
                                      (m_Box_Height)/2.);

    G4SubtractionSolid* steeltube0 =new G4SubtractionSolid(
                                                       "steelTube0",
                                                       tmptube,
                                                       middlebox,
                                                       0,
                                                       G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2.)
                                                       );
    G4SubtractionSolid* steeltube =new G4SubtractionSolid(
                                                       "steelTube",
                                                       steeltube0,
                                                       tmptube1,
                                                       0,
                                                       G4ThreeVector(0, 0, lowerAcrylicH/2.-m_TubeH/2.)
                                                       );

    G4SubtractionSolid* box =new G4SubtractionSolid(
                                                      "subbox0",
                                                      middlebox,
                                                      middle_innerbox,
                                                      0,
                                                      G4ThreeVector(0, 0,0)
                                                      );
    
    G4SubtractionSolid* solid0 =new G4SubtractionSolid(
                                                       "subbox",
                                                       box,
                                                       tmptube0,
                                                       0,
                                                       G4ThreeVector(0, 0,0)
                                                       );
    
    G4UnionSolid* solid1 = new G4UnionSolid(
                                            "unionSteel",
                                            steeltube,
                                            solid0,
                                            0,
                                            G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2.)
                                            );
    return solid1;
}


G4VSolid*
LowerChimneyMaker::getSolidLS(){
    double m_Box_Length=m_Inner_Box_Length;
    double m_Box_Wideth=m_Inner_Box_Wideth;
    double m_Box_Height=m_Inner_Box_Height;
    
    double TubeR=m_TubeInnerR;
    
    G4Tubs* tube= new G4Tubs(
                            "LStube",
                            0,
                             TubeR,   // pRMax,
                             m_TubeH/2., // pDz,
                             0*deg,     // pSPhi,
                             360*deg    // pDPhi
                             );
    G4Box* box= new G4Box(
                          "middleboxLS",
                          m_Box_Length/2.,
                          m_Box_Wideth/2.,
                          m_Box_Height/2.);
    
    G4UnionSolid* solid1 = new G4UnionSolid(
                                            "unionLS1",
                                            tube,
                                            box,
                                            0,
                                            G4ThreeVector(0, 0, m_BlockerZ-m_TubeH/2)
                                            );
    
    
    return solid1;
}

////
G4VSolid* LowerChimneyMaker::getSolidCBlocker(){
//      m_Blocker_thickness=10*cm;
    G4Box* blocker= new G4Box(
                              "blocker",
                              (Blocker_length*2.0+5.0*mm)/2.0,
                              Blocker_width/2.,
                              m_Blocker_thickness/2.);
/*    G4Box* gap= new G4Box(
                              "blocker_gap",
                              5.*mm/2.0,
                              Blocker_width/2.0,
                              m_Blocker_thickness/2.);
*/
    G4Tubs* hole= new G4Tubs(
                                "wire_holes",
                                0,      // pRMin,
                                0.25*mm,   // pRMax,
                                m_Blocker_thickness*4, // pDz,
                                0*deg,     // pSPhi,
                                360*deg    // pDPhi
                                );
    G4Box* sidebox= new G4Box(
                              "blocker_side",
                             // 1.*mm/2.0,
                              m_Blocker_thickness/2.0,
                             // 5.*cm/2.0,
                              Blocker_width/2.0,
                              (m_Inner_Box_Height/2.0 -0.5*mm)/2.);

    G4SubtractionSolid* blocker_hole1 =new G4SubtractionSolid(
                                                       "Blocker-MiddleHole",
                                                       blocker, 
                                                       hole,
                                                       0,
                                                       G4ThreeVector(0, 0,0)
                                                       );
    G4SubtractionSolid* blocker_hole2 =new G4SubtractionSolid(
                                                       "Blocke-2Holes",
                                                       blocker_hole1, 
                                                       hole,
                                                       0,
                                                       G4ThreeVector(0,TubeInnerR-2.0*cm,0)
                                                       );
    G4SubtractionSolid* solid0 =new G4SubtractionSolid(
                                                       "Blocker-3Holes",
                                                       blocker_hole2, 
                                                       hole,
                                                       0,
                                                       G4ThreeVector(0, -(TubeInnerR-2.0*cm),0)
                                                       );
    G4UnionSolid* solid_left = new G4UnionSolid(
                                            "union1",
                                            solid0,
                                            sidebox,
                                            0,
                                            G4ThreeVector(-(Blocker_length+2.5*mm-0.5*mm),0,
                                                           -(m_Inner_Box_Height/2.0 -0.5*mm)/2.-0.5*mm )
                                            );
    G4UnionSolid* solid_left_right = new G4UnionSolid(
                                            "unionBlocker",
                                            solid_left,
                                            sidebox,
                                            0,
                                            G4ThreeVector((Blocker_length+2.5*mm-0.5*mm),0,
                                                           -(m_Inner_Box_Height/2.0 -0.5*mm)/2.-0.5*mm )
                                            );
    return solid_left_right;
}




