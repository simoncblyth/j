#ifndef Dimensions_hh 
#define Dimensions_hh
#include "G4LogicalVolume.hh"
using namespace CLHEP;
// general  
//const double WPHeight=42.5*m;   // water pool height
const double WPHeight=43.5*m;   // water pool height

// for both upper and lower chimney
const double Tyvek_thickness=2.0*mm; // thickness of the reflector/absorbsion tyvek.
const double Acrylic_thickness=12.4*cm;// thickness of the acrylic tube of the chimney
const double TubeInnerR=0.4*m;        // inner R of acrylic tube.
const double TubeAcrylicOuterR=TubeInnerR+Acrylic_thickness;
const double TubeTyvekR=TubeInnerR+Acrylic_thickness;

// for upper chimney
const double UpperTubeH = 3.5*m; //  upper chimney height;
const double expHallZ=11*m;

// for lower chimney

const double TubeSteelR=TubeInnerR+Acrylic_thickness; //inner R of steel tube of the lower chimney
const double Steel_thickness=5.*mm;// steel box/tube thickness **** please update ! ******
const double upperSteelTubeH=30.*cm; // steel tube above the steel box od lower chimney
const double lowerSteelTubeH=10.*cm; // steel tube under the steel box od lower chimney

const double Inner_Box_Length=2.0*m; // dimensions of the steel box: inner length
const double Inner_Box_Wideth=1.0*m; // dimensions of the steel box: inner width 
const double Inner_Box_Height=21.0*cm;// dimensions of the steel box: inner height 

const double CD_R=17.7*m+Acrylic_thickness;
//const double ChimBtm_2_Center=sqrt(CD_R*CD_R-TubeAcrylicOuterR*TubeAcrylicOuterR);
const double ChimBtm_2_Center=CD_R;
const double LowerTubeH=WPHeight/2.- ChimBtm_2_Center; // height of lower chimney
//const double LowerTubeH=WPHeight/2.- CD_R; // height of lower chimney
const double Blocker_thickness=1.0*mm; //thickness of  blocker in the center of the steel box.
const double Blocker_length=47.0*cm; //thickness of  blocker in the center of the steel box.
const double Blocker_width=1.0*m; //thickness of  blocker in the center of the steel box.

#endif
