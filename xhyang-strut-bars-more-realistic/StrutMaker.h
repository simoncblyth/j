#pragma once

#include "G4SystemOfUnits.hh"
#include "G4Polycone.hh"

struct StrutMaker
{
    static constexpr const char* NAME = "sStrut" ;
    static G4VSolid* Make(const char* name);

    struct RRZ { double rInner, rOuter, zPlane ; };
    static G4VSolid* MakePolycone(const char* name, const std::vector<RRZ>& rrz);



    static G4VSolid* StrutAcrylicConstruction_Complex(  const char* name, double m_lengthStrut);
    static G4VSolid* StrutAcrylicConstruction_Simple(   const char* name, double m_lengthStrut);

    static G4VSolid* StrutAcrylicConstruction_Complex_VERBOSE(const char* name, double m_lengthStrut);
    static G4VSolid* StrutAcrylicConstruction_Simple_VERBOSE( const char* name, double m_lengthStrut);


    static G4VSolid* StrutBar2AcrylicConstruction_Complex(const char* name, double m_lengthStrut);
    static G4VSolid* StrutBar2AcrylicConstruction_Simple( const char* name, double m_lengthStrut);

    static G4VSolid* StrutBar2AcrylicConstruction_Complex_VERBOSE(const char* name, double m_lengthStrut);
    static G4VSolid* StrutBar2AcrylicConstruction_Simple_VERBOSE( const char* name, double m_lengthStrut);

};

inline G4VSolid* StrutMaker::Make(const char* name)
{
    G4VSolid* solid = nullptr ;
    double m_lengthStrut =  1548*mm ;

    if(strcmp(name,"StrutAcrylicConstruction_Complex")   == 0)   solid = StrutAcrylicConstruction_Complex(    NAME, m_lengthStrut);
    if(strcmp(name,"StrutAcrylicConstruction_Simple")   == 0)    solid = StrutAcrylicConstruction_Simple(     NAME, m_lengthStrut);

    if(strcmp(name,"StrutAcrylicConstruction_Complex_VERBOSE") == 0) solid = StrutAcrylicConstruction_Complex_VERBOSE(NAME, m_lengthStrut);
    if(strcmp(name,"StrutAcrylicConstruction_Simple_VERBOSE") == 0)  solid = StrutAcrylicConstruction_Simple_VERBOSE( NAME, m_lengthStrut);


    if(strcmp(name,"StrutBar2AcrylicConstruction_Complex")   == 0)   solid = StrutBar2AcrylicConstruction_Complex(    NAME, m_lengthStrut);
    if(strcmp(name,"StrutBar2AcrylicConstruction_Simple")   == 0)    solid = StrutBar2AcrylicConstruction_Simple(     NAME, m_lengthStrut);

    if(strcmp(name,"StrutBar2AcrylicConstruction_Complex_VERBOSE")   == 0)   solid = StrutBar2AcrylicConstruction_Complex_VERBOSE( NAME, m_lengthStrut);
    if(strcmp(name,"StrutBar2AcrylicConstruction_Simple_VERBOSE")   == 0)    solid = StrutBar2AcrylicConstruction_Simple_VERBOSE(  NAME, m_lengthStrut);

    return solid ;
}

inline G4VSolid* StrutMaker::MakePolycone(const char* name, const std::vector<RRZ>& rrz)
{
    int numZPlanes = rrz.size();

    std::vector<double> rInner ;
    std::vector<double> rOuter ;
    std::vector<double> zPlane ;

    for(size_t i=0 ; i < numZPlanes ; i++)
    {
        const RRZ& x = rrz[i];
        rInner.push_back(x.rInner);
        rOuter.push_back(x.rOuter);
        zPlane.push_back(x.zPlane);
    }

    G4VSolid* solid = new G4Polycone(
                        name,
                        0*deg,
                        360*deg,
                        numZPlanes,
                        zPlane.data(),
                        rInner.data(),
                        rOuter.data());
    return solid ;
}


inline G4VSolid* StrutMaker::StrutAcrylicConstruction_Complex(const char* name, double m_lengthStrut)
{
    G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
    const G4double step = 0*mm;      // A small step for sharp radius changes

    std::vector<RRZ> rrz = {
          {  0.0*mm,            85.0/2.0*mm,        z_top                    }, // Z0: Start of the initial thin
          {  0.0*mm,            85.0/2.0*mm,        z_top - 49.0*mm          }, // Z1: End of initial thin rod
          {  0.0*mm,            103.0/2.0*mm,       z_top - 49.0*mm - step   }, // Start of First nud
          {  0.0*mm,            103.0/2.0*mm,       z_top - 66.0*mm          }, // End of First nud (49+17)
          {  0.0*mm,            130.0/2.0*mm,       z_top - 66.0*mm - step   }, // Z2: Start of thick solid secti
          {  0.0*mm,            130.0/2.0*mm,       z_top - 138.0*mm         }, // Z3: End of thick solid section
          {  92.0/2.0*mm,       130.0/2.0*mm,       z_top - 138.0*mm - step  }, // Z4: Start of hollow section
          {  92.0/2.0*mm,       130.0/2.0*mm,       z_top - 309.0*mm         }, // Z5: End of hollow section (138
          {  0.0*mm,            130.0/2.0*mm,       z_top - 309.0*mm - step  }, // Z6: Start of second thick soli
          {  0.0*mm,            130.0/2.0*mm,       z_top - 516.0*mm         }, // Z7: End of second thick solid
          {  0.0*mm,            126.0/2.0*mm,       z_top - 516.0*mm - step  }, // Start of secdon nud
          {  0.0*mm,            126.0/2.0*mm,       z_top - 550.0*mm         }, // End of second nud (516+34)
          {  0.0*mm,            85.0/2.0*mm,        z_top - 550.0*mm - step  }, // Z8: Start of thin rod
          {  0.0*mm,            85.0/2.0*mm,        -z_top + 94 + 34         }, // Z9: End of the thin rod
          {  0.0*mm,            126.0/2.0*mm,       -z_top + 94 + 34 - step  }, // Start of third nud
          {  0.0*mm,            126.0/2.0*mm,       -z_top + 94              }, // End of third nud
          {  0.0*mm,            130.0/2.0*mm,       -z_top + 94 -step        }, // Z10: Start of the thick rod of
          {  0.0*mm,            130.0/2.0*mm,       -z_top                   }  // Z11: The thick end of the rod
        };
    return MakePolycone(name, rrz);
}

inline G4VSolid* StrutMaker::StrutAcrylicConstruction_Simple(const char* name, double m_lengthStrut)
{
    G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
    const G4double step = 0*mm;      // A small step for sharp radius changes

    std::vector<RRZ> rrz = {
          {  0.0*mm,            85.0/2.0*mm,        z_top                    }, // Z0: Start of the initial thin
          {  0.0*mm,            85.0/2.0*mm,        z_top - 49.0*mm          }, // Z1: End of initial thin rod
          {  0.0*mm,            103.0/2.0*mm,       z_top - 49.0*mm - step   }, // Start of First nud
        //{  0.0*mm,            103.0/2.0*mm,       z_top - 66.0*mm          }, // End of First nud (49+17)
        //{  0.0*mm,            130.0/2.0*mm,       z_top - 66.0*mm - step   }, // Z2: Start of thick solid secti
        //{  0.0*mm,            130.0/2.0*mm,       z_top - 138.0*mm         }, // Z3: End of thick solid section
        //{  92.0/2.0*mm,       130.0/2.0*mm,       z_top - 138.0*mm - step  }, // Z4: Start of hollow section
        //{  92.0/2.0*mm,       130.0/2.0*mm,       z_top - 309.0*mm         }, // Z5: End of hollow section (138
        //{  0.0*mm,            130.0/2.0*mm,       z_top - 309.0*mm - step  }, // Z6: Start of second thick soli
        //{  0.0*mm,            130.0/2.0*mm,       z_top - 516.0*mm         }, // Z7: End of second thick solid
        //{  0.0*mm,            126.0/2.0*mm,       z_top - 516.0*mm - step  }, // Start of secdon nud
          {  0.0*mm,            126.0/2.0*mm,       z_top - 550.0*mm         }, // End of second nud (516+34)
          {  0.0*mm,            85.0/2.0*mm,        z_top - 550.0*mm - step  }, // Z8: Start of thin rod
          {  0.0*mm,            85.0/2.0*mm,        -z_top + 94 + 34         }, // Z9: End of the thin rod
          {  0.0*mm,            126.0/2.0*mm,       -z_top + 94 + 34 - step  }, // Start of third nud
        //{  0.0*mm,            126.0/2.0*mm,       -z_top + 94              }, // End of third nud
        //{  0.0*mm,            130.0/2.0*mm,       -z_top + 94 -step        }, // Z10: Start of the thick rod of
          {  0.0*mm,            130.0/2.0*mm,       -z_top                   }  // Z11: The thick end of the rod
        };
    return MakePolycone(name, rrz);
}


inline G4VSolid* StrutMaker::StrutAcrylicConstruction_Complex_VERBOSE(const char* name, double m_lengthStrut)
{
        // Using G4Polycone to build a shaft with multiple sections of diameter, including hollow inner section.
        // There are 2 thick sections, 3 nuds, 1 hollow section inside thick section,
        // 1 long thin section in the middle, 1 short thin section at start.

        // --- Main Body of the Strut ---
        const G4int numZPlanes = 18;
        G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
        const G4double step = 0*mm;      // A small step for sharp radius changes

        // Z planes for the main body, must be strictly decreasing.
        G4double zPlane[numZPlanes] = {
            z_top,                          // Z0: Start of the initial thin rod                    
            z_top - 49.0*mm,                // Z1: End of initial thin rod
            z_top - 49.0*mm - step,         // Start of First nud
            z_top - 66.0*mm,                // End of First nud (49+17)
            z_top - 66.0*mm - step,         // Z2: Start of thick solid section
            z_top - 138.0*mm,               // Z3: End of thick solid section (66+72)
            z_top - 138.0*mm - step,        // Z4: Start of hollow section
            z_top - 309.0*mm,               // Z5: End of hollow section (138+171)
            z_top - 309.0*mm - step,        // Z6: Start of second thick solid section
            z_top - 516.0*mm,               // Z7: End of second thick solid section (309+207)
            z_top - 516.0*mm - step,        // Start of secdon nud
            z_top - 550.0*mm,               // End of second nud (516+34)
            z_top - 550.0*mm - step,        // Z8: Start of thin rod
            -m_lengthStrut / 2.0 + 94 + 34,  // Z9: End of the thin rod
            -m_lengthStrut / 2.0 + 94 + 34 - step, // Start of third nud
            -m_lengthStrut / 2.0 + 94,            // End of third nud
            -m_lengthStrut / 2.0 + 94 -step,// Z10: Start of the thick rod of the strut
            -m_lengthStrut / 2.0            // Z11: The thick end of the rod                      
        };

        G4double rInner[numZPlanes] = {
            0.0*mm,           // Z0, Z1: Initial thin rod
            0.0*mm,
            0.0*mm,           // Start of First nud
            0.0*mm,
            0.0*mm,           // Z2, Z3: First thick solid section
            0.0*mm,
            92.0/2.0*mm,      // Z4, Z5: Hollow section
            92.0/2.0*mm,
            0.0*mm,           // Z6, Z7: Second thick solid section
            0.0*mm,
            0.0*mm,           // Start of Second nud
            0.0*mm,
            0.0*mm,           // Z8, Z9: Main Thin rod
            0.0*mm,
            0.0*mm,           // Start of third nud
            0.0*mm,
            0.0*mm,           // Start of thick end rod
            0.0*mm        
        };

        G4double rOuter[numZPlanes] = {
            85.0/2.0*mm,      // Z0, Z1
            85.0/2.0*mm,
            103.0/2.0*mm,     // Start of First nud
            103.0/2.0*mm,
            130.0/2.0*mm,     // Z2, Z3
            130.0/2.0*mm,
            130.0/2.0*mm,     // Z4, Z5
            130.0/2.0*mm,
            130.0/2.0*mm,     // Z6, Z7
            130.0/2.0*mm,
            126.0/2.0*mm,     // Start of Second nud
            126.0/2.0*mm,
            85.0/2.0*mm,      // Z8, Z9: Main Thin rod
            85.0/2.0*mm,
            126.0/2.0*mm,      // Start of third nud
            126.0/2.0*mm,
            130.0/2.0*mm,      // Start of thick end rod
            130.0/2.0*mm       
        };
        // Use the G4Polycone constructor for hollow objects
        G4VSolid* solid = new G4Polycone(
                        name,
                        0*deg,
                        360*deg,
                        numZPlanes,
                        zPlane,
                        rInner,
                        rOuter);
     return solid ;
}

inline G4VSolid* StrutMaker::StrutAcrylicConstruction_Simple_VERBOSE(const char* name, double m_lengthStrut)
{
    // --- Main Body of the Strut ---
        const G4int numZPlanes = 8;
        G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
        const G4double step = 0*mm;      // A small step for sharp radius changes
        
        // --- Main Body of the Strut (Simplified Solid Model) ---
        // Final corrected version. This structure preserves all critical turning points
        // from the complex model to prevent R/Z segment crossing errors,
        // while removing steps and the inner radius for simplification.
        // Z planes for the main body, must be strictly decreasing.
        G4double zPlane[numZPlanes] = {
            z_top,                          // Z0: Start of the initial thin rod
            z_top - 49.0*mm,                // Z1: End of initial thin rod
            z_top - 49.0*mm - step,         // Start of First nud
            // z_top - 66.0*mm,                // End of First nud (49+17)
            // z_top - 66.0*mm - step,         // Z2: Start of thick solid section
            // z_top - 138.0*mm,               // Z3: End of thick solid section (66+72)
            // z_top - 138.0*mm - step,        // Z4: Start of hollow section
            // z_top - 309.0*mm,               // Z5: End of hollow section (138+171)
            // z_top - 309.0*mm - step,        // Z6: Start of second thick solid section
            // z_top - 516.0*mm,               // Z7: End of second thick solid section (309+207)
            // z_top - 516.0*mm - step,        // Start of secdon nud
            z_top - 550.0*mm,               // End of second nud (516+34)
            z_top - 550.0*mm - step,        // Z8: Start of thin rod
            -m_lengthStrut / 2.0 + 94 + 34,  // Z9: End of the thin rod
            -m_lengthStrut / 2.0 + 94 + 34 - step, // Start of third nud
            // -m_lengthStrut / 2.0 + 94,            // End of third nud
            // -m_lengthStrut / 2.0 + 94 -step,// Z10: Start of the thick rod of the strut
            -m_lengthStrut / 2.0            // Z11: The thick end of the rod
        };

        G4double rInner[numZPlanes] = {
            0.0*mm,           // Z0, Z1: Initial thin rod
            0.0*mm,
            0.0*mm,           // Start of First nud
            // 0.0*mm,
            // 0.0*mm,           // Z2, Z3: First thick solid section
            // 0.0*mm,
            // 92.0/2.0*mm,      // Z4, Z5: Hollow section
            // 92.0/2.0*mm,
            // 0.0*mm,           // Z6, Z7: Second thick solid section
            // 0.0*mm,
            // 0.0*mm,           // Start of Second nud
            0.0*mm,
            0.0*mm,           // Z8, Z9: Main Thin rod
            0.0*mm,
            0.0*mm,           // Start of third nud
            // 0.0*mm,
            // 0.0*mm,           // Start of thick end rod
            0.0*mm
        };

        G4double rOuter[numZPlanes] = {
            85.0/2.0*mm,      // Z0, Z1
            85.0/2.0*mm,
            130.0/2.0*mm,     // Start of First nud
            // 103.0/2.0*mm,
            // 130.0/2.0*mm,     // Z2, Z3
            // 130.0/2.0*mm,
            // 130.0/2.0*mm,     // Z4, Z5
            // 130.0/2.0*mm,
            // 130.0/2.0*mm,     // Z6, Z7
            // 130.0/2.0*mm,
            // 126.0/2.0*mm,     // Start of Second nud
            130.0/2.0*mm,
            85.0/2.0*mm,      // Z8, Z9: Main Thin rod
            85.0/2.0*mm,
            130.0/2.0*mm,      // Start of third nud
            // 126.0/2.0*mm,
            // 130.0/2.0*mm,      // Start of thick end rod
            130.0/2.0*mm
        };
        // Use the G4Polycone constructor for hollow objects
        G4VSolid* solid = new G4Polycone(
                        name,
                        0*deg, 
                        360*deg,
                        numZPlanes,
                        zPlane,
                        rInner,
                        rOuter);
       return solid ;
}














inline G4VSolid* StrutMaker::StrutBar2AcrylicConstruction_Complex(const char* name, double m_lengthStrut)
{
    G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
    const G4double step = 0*mm;      // A small step for sharp radius changes
    std::vector<RRZ> rrz = {
                {     0.0*mm,            60.0/2.0*mm,        z_top                   }, // Z0: Start of the initial thin rod                       
                {     0.0*mm,            60.0/2.0*mm,        z_top - 50.0*mm         }, // Z1: End of initial thin rod
                {     0.0*mm,            103.0/2.0*mm,       z_top - 50.0*mm - step  }, // Start of First nud
                {     0.0*mm,            103.0/2.0*mm,       z_top - 67.0*mm         }, // End of First nud (50+17)
                {     0.0*mm,            105.0/2.0*mm,       z_top - 67.0*mm - step  }, // Z2: Start of thick solid section
                {     0.0*mm,            105.0/2.0*mm,       z_top - 138.0*mm        }, // Z3: End of thick solid section (67+71)
                {     66.0/2.0*mm,       105.0/2.0*mm,       z_top - 138.0*mm - step }, // Z4: Start of hollow section
                {     66.0/2.0*mm,       105.0/2.0*mm,       z_top - 303.0*mm        }, // Z5: End of hollow section (138+165)
                {     0.0*mm,            105.0/2.0*mm,       z_top - 303.0*mm - step }, // Z6: Start of second thick solid section
                {     0.0*mm,            105.0/2.0*mm,       z_top - 477.0*mm        }, // Z7: End of second thick solid section (303+174)
                {     0.0*mm,            103.0/2.0*mm,       z_top - 477.0*mm - step }, // Start of secdon nud
                {     0.0*mm,            103.0/2.0*mm,       z_top - 511.0*mm        }, // End of second nud (477+34)
                {     0.0*mm,            60.0/2.0*mm,        z_top - 511.0*mm - step }, // Z8: Start of the thin strut
                {     0.0*mm,            60.0/2.0*mm,        -z_top + 80 + 34        }, // Z9: End of the thin strut
                {     0.0*mm,            103.0/2.0*mm,       -z_top + 80 + 34 - step }, // Start of third nud
                {     0.0*mm,            103.0/2.0*mm,       -z_top + 80             }, // End of third nud
                {     0.0*mm,            105.0/2.0*mm,       -z_top + 80 -step       }, // Z10: Start of the thick rod of the strut
                {     0.0*mm,            105.0/2.0*mm,       -z_top                  }  // Z11: The thick end of the strut                         
        };
    return MakePolycone(name, rrz);
}

inline G4VSolid* StrutMaker::StrutBar2AcrylicConstruction_Simple(const char* name, double m_lengthStrut)
{
    G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
    const G4double step = 0*mm;      // A small step for sharp radius changes
    std::vector<RRZ> rrz = {
               {   0.0*mm,    60.0/2.0*mm,     z_top                   },  // Z0: Start of the initial thin rod
               {   0.0*mm,    60.0/2.0*mm,     z_top - 50.0*mm         },  // Z1: End of initial thin rod
               {   0.0*mm,    105.0/2.0*mm,    z_top - 50.0*mm - step  },  // Start of First nud
               {   0.0*mm,    105.0/2.0*mm,    z_top - 511.0*mm        },  // End of second nud (477+34)
               {   0.0*mm,    60.0/2.0*mm,     z_top - 511.0*mm - step },  // Z8: Start of the thin strut
               {   0.0*mm,    60.0/2.0*mm,     -z_top + 80 + 34        },  // Z9: End of the thin strut
               {   0.0*mm,    105.0/2.0*mm,    -z_top + 80 + 34 - step },  // Start of third nud
               {   0.0*mm,    105.0/2.0*mm,    -z_top                  }   // Z11: The thick end of the strut    
        };
    return MakePolycone(name, rrz);
}



inline G4VSolid* StrutMaker::StrutBar2AcrylicConstruction_Simple_VERBOSE(const char* name, double m_lengthStrut)
{
        const G4int numZPlanes = 8;
        G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
        const G4double step = 0*mm;      // A small step for sharp radius changes

        // Z planes for the main body, must be strictly decreasing.
        G4double zPlane[numZPlanes] = {
            z_top,                          // Z0: Start of the initial thin rod
            z_top - 50.0*mm,                // Z1: End of initial thin rod
            z_top - 50.0*mm - step,         // Start of First nud
            z_top - 511.0*mm,               // End of second nud (477+34)
            z_top - 511.0*mm - step,        // Z8: Start of the thin strut
            -m_lengthStrut / 2.0 + 80 + 34,  // Z9: End of the thin strut
            -m_lengthStrut / 2.0 + 80 + 34 - step, // Start of third nud
            -m_lengthStrut / 2.0            // Z11: The thick end of the strut     
        };

        G4double rInner[numZPlanes] = {
            0.0*mm,           // Z0, Z1: Initial thin rod
            0.0*mm,
            0.0*mm,           // Start of First nud
            0.0*mm,
            0.0*mm,           // Z8, Z9: Main Thin rod
            0.0*mm,
            0.0*mm,           // Start of third nud
            0.0*mm
        };

        G4double rOuter[numZPlanes] = {
            60.0/2.0*mm,      // Z0, Z1
            60.0/2.0*mm,
            105.0/2.0*mm,     // Start of First nud
            105.0/2.0*mm,
            60.0/2.0*mm,      // Z8, Z9: Main Thin rod
            60.0/2.0*mm,
            105.0/2.0*mm,      // Start of third nud
            105.0/2.0*mm,
        };

        G4VSolid* solid = new G4Polycone(
                        name,
                        0*deg, 
                        360*deg,
                        numZPlanes,
                        zPlane,
                        rInner,
                        rOuter);

       return solid ;
}



inline G4VSolid* StrutMaker::StrutBar2AcrylicConstruction_Complex_VERBOSE(const char* name, double m_lengthStrut)
{
        const G4int numZPlanes = 18;
        G4double z_top = m_lengthStrut / 2.0; // The end close to the detector
        const G4double step = 0*mm;      // A small step for sharp radius changes

        // Z planes for the main body, must be strictly decreasing.
        G4double zPlane[numZPlanes] = {
            z_top,                          // Z0: Start of the initial thin rod                         
            z_top - 50.0*mm,                // Z1: End of initial thin rod
            z_top - 50.0*mm - step,         // Start of First nud
            z_top - 67.0*mm,                // End of First nud (50+17)
            z_top - 67.0*mm - step,         // Z2: Start of thick solid section
            z_top - 138.0*mm,               // Z3: End of thick solid section (67+71)
            z_top - 138.0*mm - step,        // Z4: Start of hollow section
            z_top - 303.0*mm,               // Z5: End of hollow section (138+165)
            z_top - 303.0*mm - step,        // Z6: Start of second thick solid section
            z_top - 477.0*mm,               // Z7: End of second thick solid section (303+174)
            z_top - 477.0*mm - step,        // Start of secdon nud
            z_top - 511.0*mm,               // End of second nud (477+34)
            z_top - 511.0*mm - step,        // Z8: Start of the thin strut
            -m_lengthStrut / 2.0 + 80 + 34,  // Z9: End of the thin strut
            -m_lengthStrut / 2.0 + 80 + 34 - step, // Start of third nud
            -m_lengthStrut / 2.0 + 80,            // End of third nud
            -m_lengthStrut / 2.0 + 80 -step,// Z10: Start of the thick rod of the strut
            -m_lengthStrut / 2.0            // Z11: The thick end of the strut                            
        };

        G4double rInner[numZPlanes] = {
            0.0*mm,           // Z0, Z1: Initial thin rod
            0.0*mm,
            0.0*mm,           // Start of First nud
            0.0*mm,
            0.0*mm,           // Z2, Z3: First thick solid section
            0.0*mm,
            66.0/2.0*mm,      // Z4, Z5: Hollow section
            66.0/2.0*mm,
            0.0*mm,           // Z6, Z7: Second thick solid section
            0.0*mm,
            0.0*mm,           // Start of Second nud
            0.0*mm,
            0.0*mm,           // Z8, Z9: Main Thin rod
            0.0*mm,
            0.0*mm,           // Start of third nud
            0.0*mm,
            0.0*mm,           // Start of thick end rod
            0.0*mm            
        };

        G4double rOuter[numZPlanes] = {
            60.0/2.0*mm,      // Z0, Z1
            60.0/2.0*mm,
            103.0/2.0*mm,     // Start of First nud
            103.0/2.0*mm,
            105.0/2.0*mm,     // Z2, Z3
            105.0/2.0*mm,
            105.0/2.0*mm,     // Z4, Z5
            105.0/2.0*mm,
            105.0/2.0*mm,     // Z6, Z7
            105.0/2.0*mm,
            103.0/2.0*mm,     // Start of Second nud
            103.0/2.0*mm,
            60.0/2.0*mm,      // Z8, Z9: Main Thin rod
            60.0/2.0*mm,
            103.0/2.0*mm,      // Start of third nud
            103.0/2.0*mm,
            105.0/2.0*mm,      // Start of thick end rod
            105.0/2.0*mm,       
        };

       G4VSolid* solid = new G4Polycone(
                        name,
                        0*deg, 
                        360*deg,
                        numZPlanes,
                        zPlane,
                        rInner,
                        rOuter);

       return solid ;
}


