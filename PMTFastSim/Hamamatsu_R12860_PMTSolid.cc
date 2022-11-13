#include "Hamamatsu_R12860_PMTSolid.hh"

#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"

#include "ellipse_intersect_circle.hh"

#include <cmath>
using namespace CLHEP;

Hamamatsu_R12860_PMTSolid::Hamamatsu_R12860_PMTSolid()
    :
    m_obsolete_torus_neck(getenv("JUNO_PMT20INCH_OBSOLETE_TORUS_NECK") == nullptr ? false : true)
{
   G4cout 
       << "Hamamatsu_R12860_PMTSolid::Hamamatsu_R12860_PMTSolid"
       << G4endl 
       ;

    m1_h = 190.;
    m1_r = 254.;

    m2_h = 5.; // -5 -> 0;
    m2_r = m1_r;

    m3_h = 190.; // ?
    m3_r = 254.;

    //               R_1
    //         ._______________
    //       .    .            |
    //     . theta .           |
    //   ._________.___________|
    //     Rtorus    R_2

    m4_torus_r = 80.; // ?
    m4_torus_angle = 45.*deg; // ?

    m4_r_2 = 254./2;
    m4_r_1 = (m4_r_2+m4_torus_r) - m4_torus_r*cos(m4_torus_angle);

    m4_h = m4_torus_r*sin(m4_torus_angle) + 5.0*mm;

    m5_r = m4_r_2;
    m5_h = 65.;


    //
    //             m6_r
    //        .............|  (-275.)
    //        .            |
    //         .           |  m6_h
    //           .         |
    //              .......|  (..?..)
    //               m7_r

    m6_r = m5_r;
    m6_h = 190./2;
    m7_r = 75./2; // omit the torus for simplicity

    m8_r = 75./2;

    // (x/m6_r)^2 + (y/m6_h)^2 = 1
    // x = m8_r = 75/2
    // -> y = sqrt( (254^2-75^2)/254^2 * 190^2/4 )
    // >>> ( (254.**2-75.**2)/254.**2 * 190.**2/4 ) ** 0.5
    // 90.764151727223648
    // m8_h = 145-y = 55
    m8_h = 55.+15.;

    m9_r = 51.50/2;
    m9_h = 30.;

}


/**


      1_4 (Union)                   bulb + neck  

          1_3 (Union)               bulb with stretched equator 

              1_2 (Union)                    

                  I  (Ellipsoid)    upper half 
                  II (Tubs)         thin equator    (pushed down : -m2_h/2  -2.5 ) 
                    
              III (Ellipsoid)       lower half      (pushed down :  -m2_h   -5.0 ) 

          IV  (Subtraction)         neck            (pushed down : -210.*mm + m4_h/2 )    
      
              IV_tube  (Tubs) 
              IV_torus (Torus)                      (pushed down :  -m4_h/2 ) 
                 


Output from opticks/ana/gpmt.py 

solid HamamatsuR12860_PMT_20inch_body_solid_
*:0 [141] Union 1_9                              : right_xyz:0.0/0.0/-420.000
l:1    [139] Union 1_8                           : right_xyz:0.0/0.0/-385.000
l:2       [137] Union 1_6                        : right_xyz:0.0/0.0/-275.000
l:3          [135] Union 1_5                     : right_xyz:0.0/0.0/-242.500
l:4             [133] Union 1_4                  : right_xyz:0.0/0.0/-179.216
l:5                [129] Union 1_3               : right_xyz:0.0/0.0/-5.000
l:6                   [127] Union 1_2            : right_xyz:0.0/0.0/-2.500
l:7                      [125] Ellipsoid I       : xyz 0.0,0.0,0.000               :  ax/by/cz 254.000/254.000/190.000  zcut1  0.000 zcut2 190.000  
r:7                      [126] Tube II           : xyz 0.0,0.0,5.000               :  rmin 0.0 rmax 254.000 hz  2.500 
r:6                   [128] Ellipsoid III        : xyz 0.0,0.0,0.000               :  ax/by/cz 254.000/254.000/190.000  zcut1 -190.000 zcut2  0.000  
r:5                [132] Subtraction IV          : right_xyz:0.0/0.0/-30.784
l:6                   [130] Tube IV_tube         : xyz 0.0,0.0,61.569              :  rmin 0.0 rmax 150.431 hz 30.784 
r:6                   [131] Torus IV_torus       : xyz 0.0,0.0,0.000               :  rmin  0.000 rmax 80.000 rtor 207.000  
r:4             [134] Tube V                     : xyz 0.0,0.0,65.000              :  rmin 0.0 rmax 127.000 hz 32.500 
r:3          [136] Ellipsoid VI                  : xyz 0.0,0.0,0.000               :  ax/by/cz 127.000/127.000/95.000  zcut1 -90.000 zcut2  0.000  
r:2       [138] Tube VIII                        : xyz 0.0,0.0,70.000              :  rmin 0.0 rmax 37.500 hz 35.000 
r:1    [140] Polycone IX                         : xyz 0.0,0.0,0.000               :  zp_num  2 z:[0.0, -30.0] rmax:[25.75] rmin:[0.0]  


Second constituent of boolean combinations feel the z-shifts. 
Because IV_torus is second of Subtraction IV and that is second of 1_4 (bulb+neck) 
the torus gets two shifts ending up at : -210.*mm + m4_h/2 - m4_h/2 = -210.*mm  

     -210.+m4_h/2.  = -179.2157

Considering the replacement neck, because the ellipse circle intersect is done in the 
1_9 frame "absolute" top frame have to convert back into the 1_4 frame by 
adding  
  
The absolute ellipse circle intersect is (142.9671,-162.0446) but 
need to subtract off the neck offset from the z to get back into the neck frame.

     -162.0446 - (-210.+m4_h/2.) 
     17.171128752538095

**/



G4VSolid* Hamamatsu_R12860_PMTSolid::GetSolid(G4String solidname, double thickness, char mode)
{
    G4VSolid* pmt_solid = NULL;

    double P_I_R = m1_r + thickness;
    double P_I_H = m1_h + thickness;

    G4VSolid* solid_I = new G4Ellipsoid(
					solidname+"_I",
					P_I_R,
					P_I_R,
					P_I_H,
					0, // pzBottomCut -> equator
					P_I_H // pzTopCut -> top
					);

    G4VSolid* solid_II = new G4Tubs(
					solidname+"_II",
					0.0,
					P_I_R,
					m2_h/2,
					0.*deg,
					360.*deg
					);
    G4cout << __FILE__ << ":" <<  __LINE__ << G4endl;
    // I+II

    if( mode == ' ' || mode == 'H' )   // head mode 'H' doesnt care, as solid_I is returned  
    {
        pmt_solid = new G4UnionSolid(
				 solidname+"_1_2",
				 solid_I,     // upper hemi-ellipsoid
				 solid_II,    // thin equatorial cylinder, pushed down in z, top at z=0
				 0,
				 G4ThreeVector(0,0,-m2_h/2)
				 );  
    }
    else if( mode == 'T' )   // tail mode 'T' starts from the thin equatorial cylinder
    {
        // reproduce the solid_II G4Tubs thin equatorial cylinder with a G4Polycone 
        // as need to offset from symmetry about z=0 to match position without
        // being a boolean righthandside. m2_h/2 is ZHalfLength

        G4double phiStart = 0.00*deg ; 
        G4double phiTotal = 360.00*deg ;
        G4int numZPlanes = 2 ; 
        G4double zPlane[] = { -m2_h            , 0.0  } ;  
        G4double rInner[] = {  0.0             , 0.0   } ;  
        G4double rOuter[] = {  P_I_R           , P_I_R  } ;    

        pmt_solid = new G4Polycone(
                                   solidname+"_1_2",
                                   phiStart,
                                   phiTotal,
                                   numZPlanes,
                                   zPlane,
                                   rInner,
                                   rOuter
                                   ); 
    }


    G4VSolid* solid_III = new G4Ellipsoid(
					  solidname+"_III",
					  P_I_R,
					  P_I_R,
					  P_I_H,
					  -P_I_H,
					  0);

    // +III
    pmt_solid = new G4UnionSolid(
				 solidname+"_1_3",
				 pmt_solid,
				 solid_III,
				 0,
				 G4ThreeVector(0,0,-m2_h)
				 );


    G4VSolid* solid_IV = nullptr ; 
    if( m_obsolete_torus_neck )
    {   
        solid_IV = construct_obsolete_torus_neck( solidname, thickness ); 
    }
    else
    {
        solid_IV = construct_polycone_neck( solidname, P_I_R, P_I_H, thickness ); 
    }


    // +IV
    pmt_solid = new G4UnionSolid(
				 solidname+"_1_4",
				 pmt_solid,
				 solid_IV,
				 0,
				 G4ThreeVector(0,0,-210.*mm+m4_h/2)
				 );

    G4VSolid* solid_V = new G4Tubs(
				   solidname+"_V",
				   0.0,
				   m5_r+thickness,
				   m5_h/2,
				   0.0*deg,
				   360.0*deg
				   );
    // +V
    pmt_solid = new G4UnionSolid(
				 solidname+"_1_5",
				 pmt_solid,
				 solid_V,
				 0,
				 G4ThreeVector(0,0,-210.*mm-m5_h/2)
				 );


    double P_VI_R = m6_r + thickness;
    double P_VI_H = 95.*mm + thickness;
    G4VSolid* solid_VI = new G4Ellipsoid(
					 solidname+"_VI",
					 P_VI_R,
					 P_VI_R,
					 P_VI_H,
					 -90.*mm,
					 0);

    // +VI
    pmt_solid = new G4UnionSolid(
    				 solidname+"_1_6",
    				 pmt_solid,
    				 solid_VI,
    				 0,
    				 G4ThreeVector(0,0,-275.*mm)
    				 );

    G4VSolid* solid_VIII = new G4Tubs(
				      solidname+"_VIII",
				      0.0,
				      m8_r+thickness,
				      m8_h/2,
				      0.0*deg,
				      360.0*deg
				      );
    // +VIII
    pmt_solid = new G4UnionSolid(
				 solidname+"_1_8",
				 pmt_solid,
				 solid_VIII,
				 0,
				 G4ThreeVector(0,0,-420.*mm+m8_h/2)
				 );

    double* r_IX_in = new double[2]; r_IX_in[0] = 0.0;            r_IX_in[1] = 0.0;
    double* r_IX = new double[2];    r_IX[0] = m9_r+thickness;    r_IX[1] = m9_r+thickness;
    double* z_IX = new double[2];    z_IX[0] = -(m9_h+thickness); z_IX[1] = 0;
    G4VSolid* solid_IX = new G4Polycone(
					solidname+"_IX",
					0.0*deg,
					360.*deg,
					2,
					z_IX,
					r_IX_in,
					r_IX
					);


    // +VIII
    pmt_solid = new G4UnionSolid(
				 solidname+"_1_9",
				 pmt_solid,
				 solid_IX,
				 0,
				 G4ThreeVector(0,0,-420.*mm)
				 );


    G4VSolid* u_pmt_solid = pmt_solid ; 

    switch(mode)
    {
       case ' ':u_pmt_solid = pmt_solid ; break ;
       case 'H':u_pmt_solid = solid_I   ; break ;
       case 'T':u_pmt_solid = pmt_solid ; break ;
       default: u_pmt_solid = NULL      ; break ;       
    }
    
    if(u_pmt_solid == NULL)
    {
        G4cout 
           << "Hamamatsu_R12860_PMTSolid::GetSolid"
           << " FATAL : INVALID MODE " << mode
           << G4endl 
           ;
       assert(0); 
       exit(EXIT_FAILURE);
    }

    return u_pmt_solid;
}


/**
Hamamatsu_R12860_PMTSolid::construct_polycone_neck
-----------------------------------------------------

Ellipse_Intersect_Circle gives "absolute" frame intersect of ellipse and circle.
The intersect is found by brute force checking whether up to 1M points 
anti-clockwise around the ellipse are within the circle. 
The first ellipse point encountered that is inside the circle is 
taken as an approximation (a very good one) for the desired intersect.

In general a circle and an ellipse can intersect at 0,1,2,3 or 4 points
This simple numerical intersection is assumming there are 2 intersects.

**/

G4VSolid* Hamamatsu_R12860_PMTSolid::construct_polycone_neck(G4String solidname, double P_I_R, double P_I_H, double thickness )
{
    G4VSolid* solid_IV = nullptr ; 

    // "absolute" frame ellipse params 
    double e_cx = 0. ; 
    double e_cy = -m2_h ;   // lower ellipsoid half is pushed down a little : -5 
    double e_ax = P_I_R ;   
    double e_ay = P_I_H ;   

    // "absolute" frame torus circle params 
    double c_cx = m4_torus_r + m4_r_2 ;      // 207.  torus_x 
    double neck_offset_z = -210. + m4_h/2 ;  // see _1_4 below
    double c_cy = neck_offset_z -m4_h/2 ;    // -210. torus_z  (see _1_4 below)
    double c_r = m4_torus_r-thickness ;      //       torus_r 

    int n = 1000000 ; 
    bool verbose = false ; 
    printf("[Ellipse_Intersect_Circle \n");
    Ellipse_Intersect_Circle ec = Ellipse_Intersect_Circle::make( e_cx, e_cy, e_ax, e_ay, c_cx, c_cy, c_r, n, verbose );  
    printf("]Ellipse_Intersect_Circle (%10.4f, %10.4f) \n", ec.intersect.p[0].x, ec.intersect.p[0].y );  
    // intersect coordinates in  "absolute" relative to top Union 1_9 frame 

    double ec_r = ec.intersect.p[0].x ; 
    double ec_z = ec.intersect.p[0].y - neck_offset_z ;  // get back into neck frame 


    {
        G4double phiStart = 0.00*deg ; 
        G4double phiTotal = 360.00*deg ;
        G4int numZPlanes = 2 ; 
        G4double zPlane[] = {  -m4_h/2         , ec_z  } ;  
        G4double rInner[] = {  0.0             , 0.0   } ;  
        G4double rOuter[] = {  m5_r + thickness, ec_r  } ;    

        // m4_r_2 == m5_r : 
        // m5_r + thickness : matches radius of the tubs beneath

        G4Polycone* _solid_IV = new G4Polycone(
                                 solidname+"_IV",
                                 phiStart,
                                 phiTotal,
                                 numZPlanes,
                                 zPlane,
                                 rInner,
                                 rOuter
                                 ); 

        solid_IV = (G4VSolid*)_solid_IV ;
    }
    return solid_IV ; 
}


G4VSolid* Hamamatsu_R12860_PMTSolid::construct_obsolete_torus_neck(G4String solidname, double thickness )
{
    G4VSolid* solid_IV_tube = new G4Tubs(
                     solidname+"_IV_tube",
                     0.0,
                     m4_r_1,
                     m4_h/2,
                     0.0*deg,
                     360.0*deg
                     );
    G4VSolid* solid_IV_torus = new G4Torus(
                       solidname+"_IV_torus",
                       0.*mm,
                       m4_torus_r-thickness, // R
                       m4_torus_r+m4_r_2, // swept radius
                       0.0*deg,
                       360.0*deg);
    G4VSolid* solid_IV = new G4SubtractionSolid(
                        solidname+"_IV",
                        solid_IV_tube,
                        solid_IV_torus,
                        0,
                        G4ThreeVector(0,0,-m4_h/2)
                        );

    return solid_IV ; 
}


