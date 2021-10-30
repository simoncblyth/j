#ifndef HamamatsuR12860PMTManager_hh
#define HamamatsuR12860PMTManager_hh

/*
 * This is the implementation of Hamamatsu R12860.
 * See JUNO-doc-XXX.
 *
 * -- Tao Lin, 2017/05/29
 */

#ifdef STANDALONE
#include "globals.hh"
class G4LogicalVolume ; 
#include "G4ThreeVector.hh"
#else
#include "SniperKernel/ToolBase.h"
#include "DetSimAlg/IPMTElement.h"
#include "Geometry/IPMTParamSvc.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"
#endif

class G4OpticalSurface;
class G4Material;
class G4VSensitiveDetector;
class G4PVPlacement;
class G4VSolid;
class G4Tubs;

class Hamamatsu_R12860_PMTSolid;

#ifdef STANDALONE
class HamamatsuR12860PMTManager {
#else
class HamamatsuR12860PMTManager: public IPMTElement,
                                 public ToolBase {
#endif
public:
    // Interface
    G4LogicalVolume* getLV();
    G4double GetPMTRadius();
    G4double GetPMTHeight();
    G4double GetZEquator();
    G4ThreeVector GetPosInPMT();

public:
    // Constructor
    HamamatsuR12860PMTManager
    (const G4String& plabel // label -- subvolume names are derived from this
    );
    ~HamamatsuR12860PMTManager();
private:
    void init();

    void init_material();
    void init_variables();
    void init_mirror_surface();
    void init_pmt();
    void init_fast_cover();

    G4String GetName() { return m_label;}

    void ConstructPMT_UsingTorusStack();
private:
    G4String m_label;

    /* solid maker */
    Hamamatsu_R12860_PMTSolid* m_pmtsolid_maker;
    /* solid related */
    void helper_make_solid();
    // * pmt solid (a little big than body solid)
    //   * body solid
    //     + inner1
    //     + inner2
    G4VSolid* pmt_solid; 
    G4VSolid* body_solid;
    G4VSolid* inner_solid;
    G4VSolid* inner1_solid;
    G4VSolid* inner2_solid;
    G4Tubs* dynode_solid;
    G4double hh_dynode;
    G4double z_dynode;
    /* logical volumes */
    void helper_make_logical_volume();
    G4LogicalVolume* body_log;
    G4LogicalVolume* inner1_log;
    G4LogicalVolume* inner2_log;
    G4LogicalVolume* dynode_log;
    /* physical volumes */
    void helper_make_physical_volume();
    G4PVPlacement* body_phys;
    G4PVPlacement* inner1_phys;
    G4PVPlacement* inner2_phys;
    G4PVPlacement* dynode_phys;
    /* pmtparamsvc */
#ifdef STANDALONE
#else
    IPMTParamSvc* m_pmt_param_svc;
    /* pmtsimparamsvc */
    IPMTSimParamSvc* m_pmt_sim_param_svc;
#endif
    /* dynode volumes */
    void helper_make_dynode_volume();
    /* optical surface */
    void helper_make_optical_surface();
    /* fast simulation */
    void helper_fast_sim();
    /* visual attribute */
    void helper_vis_attr();
private:
    G4LogicalVolume* m_logical_pmt;

    G4OpticalSurface* m_mirror_opsurf;

    G4OpticalSurface* Photocathode_opsurf;
    G4Material* GlassMat;
    G4Material* PMT_Vacuum;
    G4Material* DynodeMat;
    G4Material* MaskMat;
    G4VSensitiveDetector *m_detector;

private:
    // Cover Related
    G4LogicalVolume* m_logical_cover;

    G4Material* m_cover_mat;
    bool m_simplify_csg ; 
    bool m_fast_cover;
    bool m_enable_optical_model;
    std::string m_cover_mat_str;
private:
    G4double m_z_equator;
    G4double m_pmt_r;
    G4double m_pmt_h;

private:
    // If m_useRealSurface is true, the PMT should insert into the surface.
    // In order to optimize the speed, just reduce the size of the PMT.
    //
    //        |    -
    //        |  /   \
    //    ------- P M T
    //    ------- 19.434m
    //        |  \   /
    //        |    -
    //      Tyvek  |
    //     19.629m
    bool m_useRealSurface;


};

#endif
