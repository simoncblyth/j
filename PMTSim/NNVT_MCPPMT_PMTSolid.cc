#include "NNVT_MCPPMT_PMTSolid.hh"

#include "G4Ellipsoid.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"

#include <cassert>


/**
Explanation of the CSG modelling of the PMT
---------------------------------------------

Points on the below figure.

    A : apex, top of the bulb
    E : center of bulb ellipsoid
    F : edge of ellipsoid on equator
    T : centers of the torus cross section circles  
    B : center bottom of the endtube
    C : edge of endtube
    N : top of the neck cylinder
    M : bottom of the neck cylinder
    P : edge of the neck tube, on the line joining E and T (ellipsoid to torus circle centers) 
    D : torus circle touching endtube 

Distances and angles 

    AE      : m_Htop       : from apex to center of ellipsoid bulb (the equator)
    EF      : m_R          : xy radius of ellipsoid
    BM, CD  : m_Hbtm       : height of the endtube 
    BC, MD  : m_Rbtm       : radius of endtube 
    MQ, NP  : m_Rtubetorus : radius of neck tube   :  m_Rtubetorus[MQ] = m_Rbtm[MD]+m_Rtorus[DT] - m_Rtorus*sin(m_theta)[QT]
    DT      : m_Rtorus     : raidus of torus cross-section circle
    AB      : m_H          : overall height 
    MT      : m_Rbtm + m_Rtorus
    PQ,NM   : m_Htubetorus = m_Rtorus*cos(m_theta)
    QT      : m_Rtorus*sin(m_theta)
    EM      : m_Heq2torus = m_H - m_Htop - m_Hbtm 
    MT/EM   : tan(m_theta) :  
    NEP     : m_theta      :  3 similar triangles 
    MET     : m_theta      : 
    QPT     : m_theta      : 


Three part structure with ellipsoid bulb and cylinder endtube
connected via a neck. The shape of the neck is defined by a cylinder 
with a torus subtracted leaving a beautiful curved neck, see the curve 
DP in the below figure. 

As torus intersections are exceedly computationally expensive on GPU
a simpler alternative polycone neck can be used instead, replacing 
the beautiful curve DP with a straight line forming a polycone neck
with a single cone.


                                      |
                                      |                        
    - - - - - - - - - - - - - -.- * * A * * . - - - - - - - - - - - - - - - - - - - - - - - - - - - 
                          *           |            *                          ^            
                    *                 |                                       |
                  *                   |                     *                 |
                *                     |                        *              |
              *                       | m_Htop                   *           m_Htop
            *                         |                            *          |
           *                          |      `                      *         |
          *                           |                              *        |
         *                            |                               *       |
    - - -F- - - - - - - - - - - - - - E - - - - - - - - - - - - - - - F - - - v- - - - - - - - - - 
         *                           /|\                              *       ^
          *                         / | \                            *        |
           *                       /  |__\                          *         |
            *                     /   | m_theta                    *          |
              *                  /    |    \                     *            |
                *               /     |     \                  *              |
                   *           /      |      \               *             m_Heq2torus = m_H - m_Htop - m_Hbtm      
                      *       /       |       \            *                  |
                         *   /        |        \       *                      |
   _  _  _  _  _  _ .  . .  P_________N_________P _. . _. _  _  _  _  _  _  _ | _  _  _  _  _  _
                 .         /|.        |        .|\          .                 |     ^
               .          / | .       |       . | \           .               |     |      
             .           /  |  .      |      .  |  \            .             |   m_Htubetorus = m_Rtorus*cos(m_theta); 
            .           /   |   .     |     .   |   \            .            |     | 
           .           /    |    .    |    .    |    \            .           |     |
   _ _ _ _ ._ _ _ _ _ T_____|____D____M____D____Q_____T _ _ _ _ _ . _ _ _ _ _ v _ _ V__ _ _ _ _ _ 
           .                     .    |<-->.<m_Rtorus>|            .          ^
            .                   .|    |    |.                    .            |
                               . |    |    | .                  .             |
              .               .  |    |    |   .              .               |
                .           .    |    |    |     .          .                 |
                   .  .  .       |    |    |        .  .  .                  m_Hbtm
                                 |    |    |                                  |
                                 |    |    |                                  |
                                 |    |    |                                  |    
   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ C____B____C _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _v_ _ _ _ _ _ _ _ _ _ 
                                      |<-->|
                                      | m_Rbtm
                                      |    | 
                                     



**/


#include <cmath>
using namespace CLHEP;
NNVT_MCPPMT_PMTSolid::NNVT_MCPPMT_PMTSolid()
  : m_R(254.*mm), m_H(570.*mm), m_Htop(184.*mm), 
    m_Hbtm(172.50*mm), m_Rbtm(50.*mm), m_Rtorus(43.*mm), 
    m_polycone_neck(getenv("JUNO_PMT20INCH_POLYCONE_NECK") == NULL ? false : true)
{
  m_Heq2torus = m_H - m_Htop - m_Hbtm;
  m_theta = atan((m_Rbtm+m_Rtorus)/(m_Heq2torus));
  m_Htubetorus = m_Rtorus*cos(m_theta);
  m_Rtubetorus = m_Rbtm+m_Rtorus - m_Rtorus*sin(m_theta);

  m_z_lower = m_H - m_Htop; // from equator to bottom, default value
  m_z_lower_head = m_Heq2torus - m_Htubetorus;
  m_z_lower_neck = m_Heq2torus;
  m_z_lower_tail = m_H - m_Htop;


 G4cout 
     << "NNVT_MCPPMT_PMTSolid::NNVT_MCPPMT_PMTSolid"
     << " m_polycone_neck " << m_polycone_neck 
     << ( m_polycone_neck ? " --pmt20inch-polycone-neck ENABLED " : " " )
     << G4endl 
     ;

}



G4VSolid*
NNVT_MCPPMT_PMTSolid::GetSolid(G4String solidname, double thickness, char mode) {
  double R = m_R + thickness;
  //double H = m_H + thickness*2;
  double Htop = m_Htop + thickness;

  double Hbtm = m_Hbtm + thickness;
  double Rbtm = m_Rbtm + thickness;

  double Rtorus = m_Rtorus - thickness;

  double Htubetorus = Rtorus*cos(m_theta);
  double Rtubetorus = m_Rbtm+m_Rtorus - m_Rtorus*sin(m_theta);


  double zLower = m_z_lower + thickness; // m_z_lower (>0): from equator to the cut bottom 

  if (zLower < m_z_lower_head) {
      G4cout << "Creating solid " << solidname
             << " with only head. "
             << " zLower: " << zLower
             << " z_lower_head: " << m_z_lower_head
             << G4endl;
  } else if (zLower < m_z_lower_neck) {
      G4cout << "Creating solid " << solidname
             << " with head+neck. "
             << " zLower: " << zLower
             << " z_lower_neck: " << m_z_lower_neck
             << G4endl;
  } else {
      G4cout << "Creating solid " << solidname
             << " with head+neck+tail. "
             << " zLower: " << zLower
             << " z_lower_tail: " << m_z_lower_tail
             << G4endl;
  }
  

  // PART I:
  G4VSolid* pmttube_solid_part1 = NULL;
  pmttube_solid_part1 = construct_head(solidname, 
                                       R,
                                       Htop,
                                       mode);
  if( pmttube_solid_part1 == NULL )
  {
      G4cout  
          << "NNVT_MCPPMT_PMTSolid::GetSolid"
          << " FATAL : INVALID MODDE [" << mode << "]"
          << G4endl 
          ;
      assert(0); 
  } 
 

 

  // return pmttube_solid_part1;

  // PART II:
  G4VSolid* pmttube_solid_part2 = NULL ;  
  pmttube_solid_part2 = construct_neck(solidname,
                                       Rtubetorus,
                                       Htubetorus,
                                       Rtorus,
                                       Rbtm,
                                       mode);


  // return pmttube_solid_part2;
  // PART III:
  G4VSolid* pmttube_solid_end_tube = NULL;
  pmttube_solid_end_tube = construct_tail(solidname,
                                          Rbtm,
                                          Hbtm);
  //return pmttube_solid_end_tube;
  // I+II
  G4UnionSolid* pmttube_solid_1_2 = new G4UnionSolid(
                                            solidname+"_1_2",
                                            pmttube_solid_part1,
                                            pmttube_solid_part2,
                                            0,
                                            G4ThreeVector(0, 0, -m_Heq2torus+Htubetorus/2)
                                            );
  // return pmttube_solid_1_2;
  // I+II + III 
  G4UnionSolid* pmttube_solid_1_2_3 = new G4UnionSolid(
                                            solidname,
                                            pmttube_solid_1_2,
                                            pmttube_solid_end_tube,
                                            0,
                                            G4ThreeVector(0,0, 
                                                -(m_Heq2torus+Hbtm*0.50))
                                            );





    G4VSolid* u_pmt_solid = NULL ; 
  /**
       mode
       ' '      : full PMT solid 

       'H' head : just top half of bulb ellipsoid without any body attached

       'T' tail : almost full PMT solid, but with just the bottom half of 
                  ellipsoid bulb attached to the normal body
  **/

    switch(mode)
    {
       case ' ':u_pmt_solid = pmttube_solid_1_2_3 ; break ;   
       case 'H':u_pmt_solid = pmttube_solid_part1 ; break ;  
       case 'T':u_pmt_solid = pmttube_solid_1_2_3 ; break ;  
       default: u_pmt_solid = NULL                ; break ;       
    }
    
    if(u_pmt_solid == NULL)
    {
        G4cout 
            << "NNVT_MCPPMT_PMTSolid::GetSolid"
            << " FATAL : INVALID MODE [" << mode << "]"
            << G4endl 
            ;
        assert(0); 
    }
    return u_pmt_solid;

}


G4VSolid*
NNVT_MCPPMT_PMTSolid::construct_head(G4String solidname, 
                                     double R,       // R of ellipsoid
                                     double Htop,    // height of ellipsoid
                                     char mode) const {
  G4Ellipsoid* pmttube_solid_part1 = NULL ; 

  // ' ' : full ellipsoid
  // 'H' : "head" top z-hemi-ellipsoid
  // 'T' : "tail" bottom z-hemi-ellipsoid

  switch(mode)
  { 
     case ' ': pmttube_solid_part1 = new G4Ellipsoid(
                                            solidname+"_1_Ellipsoid",
                                            R,       // pxSemiAxis
                                            R,       // pySemiAxis
                                            Htop     // pzSemiAxis
                                            );  break ; 
     case 'H': pmttube_solid_part1 = new G4Ellipsoid(
                                            solidname+"_1_Ellipsoid",
                                            R,       // pxSemiAxis
                                            R,       // pySemiAxis
                                            Htop,    // pzSemiAxis
                                            0,       // pzBottomCut -> equator
                                            Htop     // pzTopCut -> top
                                            );  break ; 
     case 'T': pmttube_solid_part1 = new G4Ellipsoid(
                                            solidname+"_1_Ellipsoid",
                                            R,       // pxSemiAxis
                                            R,       // pySemiAxis
                                            Htop,    // pzSemiAxis
                                            -Htop,   // pzBottomCut -> bottom
                                            0        // pzTopCut -> equator
                                            );  break ; 
      default: pmttube_solid_part1 = NULL ; break ; 
  }

  return pmttube_solid_part1;
}

G4VSolid*
NNVT_MCPPMT_PMTSolid::construct_neck(G4String solidname,
                                     double Rtubetorus, 
                                     double Htubetorus,
                                     double Rtorus,     // swipe
                                     double Rbtm, // the r at bottom
                                     char mode) const {
  G4VSolid* pmttube_solid_part2 = NULL ;

  if(m_polycone_neck == false)
  {

      G4Tubs* pmttube_solid_tube = new G4Tubs(
                                        solidname+"_2_Tube",
                                        0*mm,  /* inner */ 
                                        Rtubetorus, /* pmt_r */ 
                                        Htubetorus/2, /* part 2 h */ 
                                        0*deg, 
                                        360*deg);
      G4Torus* pmttube_solid_torus = new G4Torus(
                                            solidname+"_2_Torus",
                                            0*mm,  // R min
                                            Rtorus, // R max
                                            (m_Rbtm+m_Rtorus), // Swept Radius
                                            0.00*deg,
                                            360.00*deg);
      G4SubtractionSolid* pmttube_solid_part2_ = new G4SubtractionSolid(
                                                solidname+"_part2",
                                                pmttube_solid_tube,
                                                pmttube_solid_torus,
                                                0,
                                                G4ThreeVector(0,0,-Htubetorus/2)
                                                );

      pmttube_solid_part2 = (G4VSolid*)pmttube_solid_part2_ ; 

  } 
  else
  {
      G4double phiStart = 0.00*deg ; 
      G4double phiTotal = 360.00*deg ;
      G4int numZPlanes = 2 ; 
      G4double zPlane[] = { -Htubetorus/2, Htubetorus/2 } ;  
      G4double rInner[] = {  0.0         , 0.0   } ;  
      G4double rOuter[] = {  Rbtm        , Rtubetorus   } ;  

      G4Polycone* pmttube_solid_part2_ = new G4Polycone(
                                                solidname+"_part2",
                                                phiStart,
                                                phiTotal,
                                                numZPlanes,
                                                zPlane,
                                                rInner,
                                                rOuter
                                                ); 

      pmttube_solid_part2 = (G4VSolid*)pmttube_solid_part2_ ; 
  } 
  return pmttube_solid_part2;
}

G4VSolid*
NNVT_MCPPMT_PMTSolid::construct_tail(G4String solidname,
                                     double Rbtm,
                                     double Hbtm) const {
  G4Tubs* pmttube_solid_end_tube = new G4Tubs(
                                    solidname+"_3_EndTube",
                                    0*mm,  /* inner */ 
                                    Rbtm, //21*cm/2, /* pmt_r */ 
                                    Hbtm/2, //30*cm/2, /* pmt_h */ 
                                    0*deg, 
                                    360*deg);
  return pmttube_solid_end_tube;
}
