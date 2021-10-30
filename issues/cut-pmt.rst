
Cutting PMT with CSG is a very expensive way to do things.
Why not just change a parameter ?


    308     // Reduce the size when real surface is enabled.
    309     // Tao Lin, 09 Aug 2021
    310     if (m_useRealSurface) {
    311         LogInfo << "Cut the tail of PMT. " << std::endl;
    312 
    313         // inner2 
    314         const double tail_height = m_pmt_h - m_z_equator;
    315         const double tail_half_height = tail_height / 2;
    316         const G4ThreeVector cut_tail_displacement(0., 0., -tail_half_height);
    317         G4VSolid* cut_tail_solid = new G4Tubs("CutTail_NNVTMCPPMT_Solid",
    318                                               0.,
    319                                               helper_sep_tube_r+1E-9*mm,
    320                                               tail_half_height,
    321                                               0., 360.*degree);
    322         inner2_solid = new G4IntersectionSolid( GetName() + "_inner2_tail_solid",
    323                                                 inner2_solid,
    324                                                 cut_tail_solid,
    325                                                 NULL,
    326                                                 cut_tail_displacement);
    327 
    328         // pmt solid
    329         const double pmt_height = m_pmt_h;
    330         const double pmt_half_height = pmt_height / 2;
    331         const G4ThreeVector cut_pmt_displacement(0., 0., m_z_equator-pmt_half_height);
    332         G4VSolid* cut_pmt_solid = new G4Tubs("CutPMT_NNVTMCPPMT_Solid",
    333                                               0.,
    334                                               helper_sep_tube_r+1E-9*mm,
    335                                               pmt_half_height,
    336                                               0., 360.*degree);
    337         pmt_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
    338                                                 pmt_solid,
    339                                                 cut_pmt_solid,
    340                                                 NULL,
    341                                                 cut_pmt_displacement);
    342 
    343         // body solid
    344         const double body_height = m_pmt_h;
    345         const double body_half_height = body_height / 2;
    346         const G4ThreeVector cut_body_displacement(0., 0., m_z_equator-pmt_half_height);
    347         G4VSolid* cut_body_solid = new G4Tubs("CutBody_NNVTMCPPMT_Solid",
    348                                               0.,
    349                                               helper_sep_tube_r+1E-9*mm,
    350                                               body_half_height,
    351                                               0., 360.*degree);
    352         body_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
    353                                                 body_solid,
    354                                                 cut_body_solid,
    355                                                 NULL,
    356                                                 cut_body_displacement);
    357 
    358 
    359     }


