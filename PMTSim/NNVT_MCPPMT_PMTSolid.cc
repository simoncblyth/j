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
             .           /  |  .      |      .  |  \            .             |   m_Htubetorus = m_Rtorus*cos(m_theta);      _____ head_neck_zoffset = -m_Heq2torus+Htubetorus/2
            .           /   |   .     |     .   |   \            .            |     | 
           .           /    |    .    |    .    |    \            .           |     |
   _ _ _ _ ._ _ _ _ _ T_____|____D____M____D____Q_____T _ _ _ _ _ . _ _ _ _ _ v _ _ V__ _ _ _ _ _ 
           .                     .    |<-->.<m_Rtorus>|            .          ^
            .                   .|    |    |.                    .            |
                               . |    |    | .                  .             |
              .               .  |    |    |   .              .               |
                .           .    |    |    |     .          .                 |                                              _____ head_neck_tail_zoffset = -(m_Heq2torus+Hbtm*0.50)  
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
    : 
    m_R(254.*mm), m_H(570.*mm), m_Htop(184.*mm), 
    m_Hbtm(172.50*mm), m_Rbtm(50.*mm), m_Rtorus(43.*mm),
    m_obsolete_torus_neck(getenv("JUNO_PMT20INCH_OBSOLETE_TORUS_NECK") == nullptr ? false : true)
{
    m_Heq2torus = m_H - m_Htop - m_Hbtm;                       // EM : equator to torus midline
    m_theta = atan((m_Rbtm+m_Rtorus)/(m_Heq2torus));           // MET : angle of axial triangle connecting center of bulb E, torus center T and point on axis M   
    m_Htubetorus = m_Rtorus*cos(m_theta);                      // PQ : height of neck 
    m_Rtubetorus = m_Rbtm+m_Rtorus - m_Rtorus*sin(m_theta);    // NP : radius at P where neck joins head

    G4cout 
        << "NNVT_MCPPMT_PMTSolid::NNVT_MCPPMT_PMTSolid"
        << G4endl 
        ;
}

/**
NNVT_MCPPMT_PMTSolid::GetSolid
---------------------------------

       mode
       ' '      : full PMT solid 

       'H' head : just top half of bulb ellipsoid without any body attached

       'T' tail : almost full PMT solid, but with just the bottom half of 
                  ellipsoid bulb attached to the normal body
**/

G4VSolid* NNVT_MCPPMT_PMTSolid::GetSolid(G4String solidname, double thickness, char mode) 
{
    double R = m_R + thickness;
    double Htop = m_Htop + thickness;
    double Hbtm = m_Hbtm + thickness;
    double Rbtm = m_Rbtm + thickness;
    double Rtorus = m_Rtorus - thickness;

    double Htubetorus = Rtorus*cos(m_theta);
    double Rtubetorus = m_Rbtm+m_Rtorus - m_Rtorus*sin(m_theta);

    double head_neck_zoffset = -m_Heq2torus+Htubetorus*0.5 ;  
    double head_neck_tail_zoffset = -(m_Heq2torus+Hbtm*0.5) ;  

    G4VSolid* head = construct_head(solidname, R, Htop, mode); 
    G4VSolid* neck = construct_neck(solidname, Rtubetorus, Htubetorus, Rtorus, Rbtm, mode); 
    G4VSolid* tail = construct_tail(solidname, Rbtm, Hbtm); 

    G4UnionSolid* head_neck = new G4UnionSolid(
                                            solidname+"_1_2",
                                            head,
                                            neck,
                                            0,
                                            G4ThreeVector(0,0,head_neck_zoffset)
                                            );

    G4UnionSolid* head_neck_tail = new G4UnionSolid(
                                            solidname,
                                            head_neck,
                                            tail,
                                            0,
                                            G4ThreeVector(0,0,head_neck_tail_zoffset)
                                            );
    G4VSolid* u_pmt_solid = NULL ; 
    switch(mode)
    {
        case ' ':u_pmt_solid = head_neck_tail      ; break ;   
        case 'H':u_pmt_solid = head                ; break ;  
        case 'T':u_pmt_solid = head_neck_tail      ; break ;  
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


/**
NNVT_MCPPMT_PMTSolid::construct_head
----------------------------------------

mode::

    ' ' : full ellipsoid
    'H' : "head" top z-hemi-ellipsoid
    'T' : "tail" bottom z-hemi-ellipsoid

**/

G4VSolid* NNVT_MCPPMT_PMTSolid::construct_head(G4String solidname, 
                                     double R,       // R of ellipsoid
                                     double Htop,    // height of ellipsoid
                                     char mode) const {
  G4Ellipsoid* head = NULL ; 
  switch(mode)
  { 
     case ' ': head = new G4Ellipsoid(
                                      solidname+"_head",
                                      R,       // pxSemiAxis
                                      R,       // pySemiAxis
                                      Htop     // pzSemiAxis
                                      );  break ; 
     case 'H': head = new G4Ellipsoid(
                                      solidname+"_head",
                                      R,       // pxSemiAxis
                                      R,       // pySemiAxis
                                      Htop,    // pzSemiAxis
                                      0,       // pzBottomCut -> equator
                                      Htop     // pzTopCut -> top
                                      );  break ; 
     case 'T': head = new G4Ellipsoid(
                                      solidname+"_head",
                                      R,       // pxSemiAxis
                                      R,       // pySemiAxis
                                      Htop,    // pzSemiAxis
                                      -Htop,   // pzBottomCut -> bottom
                                      0        // pzTopCut -> equator
                                      );  break ; 
      default: head = NULL ; break ; 
  }

  if( head == NULL )
  {
      G4cout  
          << "NNVT_MCPPMT_PMTSolid::construct_head"
          << " FATAL : INVALID MODDE [" << mode << "]"
          << G4endl 
          ;
      assert(0); 
  }  

  return head;
}

G4VSolid* NNVT_MCPPMT_PMTSolid::construct_neck(G4String solidname,
                                     double Rtubetorus, 
                                     double Htubetorus,
                                     double Rtorus,     
                                     double Rbtm, 
                                     char mode) const 
{
    G4VSolid* neck = nullptr ; 
    if( m_obsolete_torus_neck == false )
    {
        neck = construct_polycone_neck( solidname, Rtubetorus, Htubetorus, Rtorus, Rbtm, mode ) ; 
    }
    else
    {   
        neck = construct_obsolete_torus_neck( solidname, Rtubetorus, Htubetorus, Rtorus, Rbtm, mode ) ;
    }
    return neck ; 
}

G4VSolid* NNVT_MCPPMT_PMTSolid::construct_polycone_neck(G4String solidname,
                                     double Rtubetorus, 
                                     double Htubetorus,
                                     double /*Rtorus*/,   
                                     double Rbtm, // the r at bottom
                                     char  /*mode*/) const 
{
    G4VSolid* neck = nullptr ;
    G4double phiStart = 0.00*deg ; 
    G4double phiTotal = 360.00*deg ;
    G4int numZPlanes = 2 ; 
    G4double zPlane[] = { -Htubetorus/2, Htubetorus/2 } ;  
    G4double rInner[] = {  0.0         , 0.0   } ;  
    G4double rOuter[] = {  Rbtm        , Rtubetorus   } ;  

    G4Polycone* neck_ = new G4Polycone(
                                      solidname+"_neck",
                                      phiStart,
                                      phiTotal,
                                      numZPlanes,
                                      zPlane,
                                      rInner,
                                      rOuter
                                      ); 

    neck = (G4VSolid*)neck_ ; 
    return neck ;
} 

G4VSolid* NNVT_MCPPMT_PMTSolid::construct_obsolete_torus_neck(G4String solidname,
                                     double Rtubetorus, 
                                     double Htubetorus,
                                     double Rtorus,     // swipe
                                     double /*Rbtm*/, // the r at bottom
                                     char /*mode*/) const 
{
    G4VSolid* neck = NULL ;
    G4Tubs* tube = new G4Tubs(
                                    solidname+"_2_Tube",
                                    0*mm,  /* inner */ 
                                    Rtubetorus, /* pmt_r */ 
                                    Htubetorus/2, /* part 2 h */ 
                                    0*deg, 
                                    360*deg);
    G4Torus* torus = new G4Torus(
                                        solidname+"_2_Torus",
                                        0*mm,  // R min
                                        Rtorus, // R max
                                        (m_Rbtm+m_Rtorus), // Swept Radius
                                        0.00*deg,
                                        360.00*deg);
    G4SubtractionSolid* neck_ = new G4SubtractionSolid(
                                            solidname+"_part2",
                                            tube,
                                            torus,
                                            0,
                                            G4ThreeVector(0,0,-Htubetorus/2)
                                            );

    neck = (G4VSolid*)neck_ ; 
    return neck ;
} 




G4VSolid*
NNVT_MCPPMT_PMTSolid::construct_tail(G4String solidname,
                                     double Rbtm,
                                     double Hbtm) const {
  G4Tubs* tail = new G4Tubs(
                            solidname+"_tail",
                            0*mm,  /* inner */ 
                            Rbtm, //21*cm/2, /* pmt_r */ 
                            Hbtm/2, //30*cm/2, /* pmt_h */ 
                            0*deg, 
                            360*deg);
  return tail ;
}

