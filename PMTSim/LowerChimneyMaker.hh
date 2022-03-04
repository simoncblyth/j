#ifndef LowerChimneyMaker_hh
#define LowerChimneyMaker_hh

/* This class is used to create a Ball with Chimney.
 * It is a Tube plus the Ball
 *
 * For the LS in the container, a sphere+tube is a good solid.
 * Because we can modify the top surface.
 */
#include <string>
class G4VSolid;


class LowerChimneyMaker {
public:
    LowerChimneyMaker(double BlokerZ);
    ~LowerChimneyMaker();

    G4VSolid* getSolidLogical();
    G4VSolid* getSolidTyvek();
    G4VSolid* getSolidAcrylic();
    G4VSolid* getSolidSteel();
    G4VSolid* getSolidLS();
    G4VSolid* getSolidCBlocker();
    


public:

    double m_TubeH;
    double m_BlockerZ; // ZOffsetTo0
    
    double m_WPHeight;
public:
    
    double m_TubeInnerR;//=0.4*m;
    double m_TubeAcrylicOuterR;//=m_TubeInnerR+m_Acrylic_thickness;
    double m_TubeSteelR;//=m_TubeInnerR+m_Acrylic_thickness;
    double m_TubeTyvekR;//=m_TubeInnerR+m_Acrylic_thickness;

    
    double m_Inner_Box_Length;    //=1.8*m;
    double m_Inner_Box_Wideth;    //=1.0*m;
    double m_Inner_Box_Height;    //=22.*cm;
    double m_upperSteelTubeH;//=30.*cm;
    double m_lowerSteelTubeH;//=10.*cm;
    
    double m_Tyvek_thickness;//=2.0*mm;
    double m_Acrylic_thickness;//=12.*cm;
    double m_Steel_thickness;//=5.*cm;
    double m_Blocker_thickness;//=3.0*mm;
    
    double m_upperTyvekTubeH;
    double m_lowerTyvekTubeH;
//    double m_Blocker_2_SteelBtm; 
//    double m_upperAcrylicHeight; 
    
    
};
#endif
