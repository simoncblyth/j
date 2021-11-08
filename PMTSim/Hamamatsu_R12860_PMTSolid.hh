#ifndef Hamamatsu_R12860_PMTSolid_hh
#define Hamamatsu_R12860_PMTSolid_hh

/* Implemantation of Hamamatsu R12860 geometry.
 * 
 * -- Tao Lin, 2017/06/09
 */

#include "globals.hh"
#include <string>
#include <vector>

struct OldZSolidList ; 
class G4VSolid;

class Hamamatsu_R12860_PMTSolid {
public:
    Hamamatsu_R12860_PMTSolid();

    G4VSolid* GetSolid(       G4String solidname, double thickness=0.0, char mode=' ');
    const G4VSolid* GetZCutSolid(   G4String solidname, double zcut, double thickness=0.0, char mode=' ');

private:

    // Hamamatsu R12860 is divided into following part:
    // 1. Ellipsoid  (z: 0 -> 190)      D: 508.
    // 2. Tube       (z: -5 -> 0)       D: 508.
    // 3. Ellipsoid  (z: ? -> ?)        D: 508.
    // 4. Tube-Torus (z: -210 -> ?)
    // 5. Tube       (z: -275 -> -210)  D: 254.
    // 6. Ellipsoid  (z: ? -> -275)     D: 254.
    // 7. Tube-Torus (z: ? -> ?)
    // 8. Tube       (z: -420 -> ?)     D: 75.
    // 9. Tube (base)(z: -450 -> -420)  D: 51.50
    //10. multi tube (z: -470 -> -450)


    double m1_h;
    double m1_r;
    double m2_h;
    double m2_r;
    double m3_h;
    double m3_r;
    double m4_torus_r;
    double m4_torus_angle;
    double m4_r_1;
    double m4_r_2;
    double m4_h;
    double m5_r;
    double m5_h;
    double m6_r;
    double m6_h;
    double m7_r;
    double m8_r;
    double m8_h;
    double m9_r;
    double m9_h;

    bool m_polycone_neck ; 

    OldZSolidList* ozs ; 

};


#endif
