#ifndef NNVT_MCPPMT_PMTSolid_hh
#define NNVT_MCPPMT_PMTSolid_hh

/* Implemantation of NNVT MCP-PMT geometry.
 * 
 * -- Tao Lin, 2017/05/29
 *
 * Optimization of NNVT MCP-PMT geometry with automatic cutting of the bottom part. 
 * The idea is dividing the PMT solid into different parts. 
 * Then comparing the part with the z-lower (from z-equator to bottom).
 *
 *   1. top    (184.   -> z1 -> Z)
 *   2. neck   (Z      -> z2 -> -213.5)
 *   3. bottom (-213.5 -> z3 -> -386.)
 *
 * if z-lower is in [Z, 0), then only solid 1 is built;
 * if z-lower is in [-213.5, Z), then solid 1+2 is built;
 * if z_lower is in [-386.0, -213.5), then solid 1+2+3 is built. 
 *
 * -- Tao Lin, 2021/10/31
 *
 */

#include "globals.hh"
class G4VSolid;

class NNVT_MCPPMT_PMTSolid {
public:
  // We fix the whole geometry parameters. 
  // Developers could use thickness to get different dimension.
  NNVT_MCPPMT_PMTSolid();

  G4VSolid* GetSolid(G4String solidname, double thickness=0.0, char mode=' ');

private:
  // Some key parameters
  // m_R: Radius: 254.mm
  // m_H: Height: 570.mm
  // m_Htop: Height from top to equator: 184.mm
  // m_Hbtm: Height from bottom of torus to bottom: 172.50mm
  // m_Rbtm: 50.mm
  // m_Rtorus: 43.mm
  // 
  // m_Heq2torus: Height from equator to torus = m_H - m_Htop - m_Hbtm
  // m_Htubetorus: tube-torus part height
  // m_Rtubetorus: tube-torus part radius
  //
  //               '<--- 254 --->'
  //         ..  --|--  ..         <- top
  //     *                   *
  //   *                       *
  // |                           | <- equator              PART I: ellipse
  //   *                       *
  //     *  .             .  *     <- ellipse and torus
  //          .         .          Radius of torus: 43.0   PART II: Tube-Torus
  //          .         .      -   <- torus and tube
  //          '         '      ^
  //          |         |    172.50                        PART III: Tube
  //          |         |      v
  //           ----|----       -   <- bottom
  //               ' 50 '

  double m_R;
  double m_H;
  double m_Htop;
  double m_Hbtm;
  double m_Rbtm;
  double m_Rtorus;
  bool   m_polycone_neck; 
 
  double m_Heq2torus; 
  double m_theta;
  double m_Htubetorus;
  double m_Rtubetorus;

private:
  double m_z_lower; // this is an variable to decide solid 1, solid 1+2 or solid 1+2+3

  // below are three sea-level at head/neck, neck/tail, tail
  // from zequator
  double m_z_lower_head;
  double m_z_lower_neck;
  double m_z_lower_tail;

  // in order to avoid updating the members, add const in the methods. 
  G4VSolid* construct_head(G4String solidname, 
                           double R,      // R of ellipsoid
                           double Htop,   // height of ellipsoid
                           char mode) const;

  G4VSolid* construct_neck(G4String solidname,
                           double Rtubetorus, 
                           double Htubetorus,
                           double Rtorus,     // swipe
                           double Rbtm, // the r at bottom
                           char mode) const;

  G4VSolid* obsolete_construct_torus_neck(G4String solidname,
                           double Rtubetorus, 
                           double Htubetorus,
                           double Rtorus,     // swipe
                           double Rbtm, // the r at bottom
                           char mode) const;

  G4VSolid* construct_tail(G4String solidname,
                           double Rbtm,
                           double Hbtm) const;

};

#endif
