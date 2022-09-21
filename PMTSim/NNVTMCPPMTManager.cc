
#include <iostream>
#include <iomanip>

#include "NNVTMCPPMTManager.hh"
#include "NNVT_MCPPMT_PMTSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh" // for boolean solids
#include "G4SubtractionSolid.hh" // for boolean solids
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh" // for G4VisAttributes::Invisible
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4Polycone.hh"
#include "G4SDManager.hh"

#include "X4SolidTree.hh"

#ifdef PMTSIM_STANDALONE

#define LogInfo  std::cout 
#define LogError std::cerr 

#else

//#include <boost/python.hpp>
#include "junoPMTOpticalModel.hh"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/ToolFactory.h"

#endif

using namespace CLHEP;


#ifdef PMTSIM_STANDALONE
#else
DECLARE_TOOL(NNVTMCPPMTManager);
#endif

G4LogicalVolume* NNVTMCPPMTManager::getLV() 
{
    if(!m_logical_pmt) init();
    return m_logical_pmt;
}
NP* NNVTMCPPMTManager::getValues(const char* prefix)
{
    return nullptr ; 
}

G4LogicalVolume* NNVTMCPPMTManager::getLV(const char* name)
{
    if(!m_logical_pmt) init();
    G4LogicalVolume* lv = nullptr ; 
    if(StartsWithPrefix(name, "LogicalPmt")) lv = m_logical_pmt ;
    if(StartsWithPrefix(name, "BodyLog"))    lv = body_log ;
    if(StartsWithPrefix(name, "Inner1Log"))  lv = inner1_log ;
    if(StartsWithPrefix(name, "Inner2Log"))  lv = inner2_log ;

    if(StartsWithPrefix(name, "DynodeLog"))  lv = dynode_log ;
    if(StartsWithPrefix(name, "LogicalCover")) lv = m_logical_cover ;

    if(lv == nullptr)
    {
        std::cout << "NNVTMCPPMTManager::getLV failed for name [" << name << "]" << std::endl ;  
    }
    return lv ;
}

G4PVPlacement* NNVTMCPPMTManager::getPV(const char* name)
{
    if(!m_logical_pmt) init();
    G4PVPlacement* pv = nullptr ;
    if(StartsWithPrefix(name, "BodyPhys"))   pv = body_phys ;
    if(StartsWithPrefix(name, "Inner1Phys")) pv = inner1_phys ;
    if(StartsWithPrefix(name, "Inner2Phys")) pv = inner2_phys ;
    if(StartsWithPrefix(name, "DynodePhys")) pv = dynode_phys ;

    if(pv == nullptr)
    {
        std::cout << "NNVTMCPPMTManager::getPV failed for name [" << name << "]" << std::endl ;  
    }
    return pv ;
}

G4double NNVTMCPPMTManager::GetPMTRadius() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_pmt_r;
}

G4double NNVTMCPPMTManager::GetPMTHeight() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_pmt_h;
}

G4double NNVTMCPPMTManager::GetZEquator() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_z_equator;
}

G4ThreeVector NNVTMCPPMTManager::GetPosInPMT() {
    G4ThreeVector rndm_pos;
    return rndm_pos;
}

NNVTMCPPMTManager::NNVTMCPPMTManager(const G4String& plabel)
    : 
#ifdef PMTSIM_STANDALONE
    IGeomManager(plabel), 
#else
    ToolBase(plabel), 
#endif
    m_label(plabel),
    m_pmtsolid_maker(0),
    pmt_solid(NULL), body_solid(NULL), inner_solid(NULL),
    inner1_solid(NULL), inner2_solid(NULL), dynode_solid(NULL),
      body_log(NULL), inner1_log(NULL), inner2_log(NULL), dynode_log(NULL),
      body_phys(NULL), inner1_phys(NULL), inner2_phys(NULL), 
      dynode_phys(NULL), m_logical_pmt(NULL), m_mirror_opsurf(NULL),
      Photocathode_opsurf(NULL),
      GlassMat(NULL), PMT_Vacuum(NULL), DynodeMat(NULL),
      MaskMat(NULL), m_detector(NULL),
      m_logical_cover(NULL), m_cover_mat(NULL),
      m_simplify_csg(getenv("JUNO_PMT20INCH_SIMPLIFY_CSG") == NULL ? false : true),
      m_plus_dynode(getenv("JUNO_PMT20INCH_PLUS_DYNODE") == NULL ? false : true),
      m_profligate_tail_cut(getenv("JUNO_PMT20INCH_PROFLIGATE_TAIL_CUT") == NULL ? false : true ),
      m_pmt_equator_to_bottom(0.)
{
#ifdef PMTSIM_STANDALONE
    m_fast_cover = false ; 
    m_cover_mat_str = "Water" ; 
    m_enable_optical_model = false ;  
    m_useRealSurface = getenv("JUNO_PMT20INCH_NOT_USE_REAL_SURFACE") == NULL ? true : false  ;
#else
    declProp("FastCover", m_fast_cover=false);
    declProp("FastCoverMaterial", m_cover_mat_str="Water");
    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    declProp("UseRealSurface", m_useRealSurface=true);
#endif

}

std::string NNVTMCPPMTManager::desc() const 
{
    std::stringstream ss ; 
    ss 
         << std::setw(30) << "NNVTMCPPMTManager"
         << " m_simplify_csg "   << ( m_simplify_csg   ? "Y" : "N" )
         << " m_plus_dynode "    << ( m_plus_dynode    ? "Y" : "N" )
         << " m_useRealSurface " << ( m_useRealSurface ? "Y" : "N" )
         << " m_profligate_tail_cut " << ( m_profligate_tail_cut ? "Y" : "N" )
         ;
    std::string s = ss.str(); 
    return s ; 
}


NNVTMCPPMTManager::~NNVTMCPPMTManager() 
{
    if (m_pmtsolid_maker) {
        delete m_pmtsolid_maker;
    }
}
    

void NNVTMCPPMTManager::init() 
{
#ifdef PMTSIM_STANDALONE
#else
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    m_detector = SDman->FindSensitiveDetector("PMTSDMgr");
    assert(m_detector);
#endif
    init_material();
    init_variables();
    init_mirror_surface();
    init_pmt();

    if (m_fast_cover) {
        init_fast_cover();
    }
}

void NNVTMCPPMTManager::init_material() 
{
     GlassMat = G4Material::GetMaterial("Pyrex");
     PMT_Vacuum = G4Material::GetMaterial("Vacuum"); 
     DynodeMat = G4Material::GetMaterial("Steel");

     Photocathode_opsurf =  new G4OpticalSurface(GetName()+"_Photocathode_opsurf");
     Photocathode_opsurf->SetType(dielectric_metal); // ignored if RINDEX defined
     //Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode")->GetMaterialPropertiesTable() );
     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_MCP20inch")->GetMaterialPropertiesTable() );

     if (m_fast_cover) {
         m_cover_mat = G4Material::GetMaterial(m_cover_mat_str);
         assert(m_cover_mat);
     }
}

void NNVTMCPPMTManager::init_variables() 
{
    m_pmt_r = 254.*mm;
    m_pmt_h = 570.*mm;
    m_z_equator = 184.*mm; // From top to equator

    // Reduce the height of PMT
    // Tao Lin, 09 Aug 2021
    if (m_useRealSurface) {
        const double radInnerWaterRealSurface = 19.629*m;
        const double r = m_pmt_r + 1.*cm; // 1cm is the mask
        double pmt_eq_to_bottom = sqrt(radInnerWaterRealSurface*radInnerWaterRealSurface
                                       -r*r) - 19.434*m; // at z equator
        // then, subtract the thickness of mask
        pmt_eq_to_bottom -= 10.*mm;

        m_pmt_equator_to_bottom = pmt_eq_to_bottom ;

        double pmt_h = pmt_eq_to_bottom + m_z_equator ;
        LogInfo << "Option RealSurface is enabled in Central Detector. "
                << " Reduce the m_pmt_h from "
                << m_pmt_h << " to " << pmt_h
                << std::endl;
        m_pmt_h = pmt_h;
    }


    LogInfo 
#ifdef PMTSIM_STANDALONE
#else
         << " scope:tag/objName " << scope() << tag() << "/" << objName() 
#endif
         << " GetName() " << GetName()
         <<  std::endl
         ;

    m_pmtsolid_maker = new NNVT_MCPPMT_PMTSolid();

}

void NNVTMCPPMTManager::init_mirror_surface() 
{
    if ( m_mirror_opsurf == NULL ) {
        // construct a static mirror surface with idealized properties
        m_mirror_opsurf =  new G4OpticalSurface(GetName()+"_Mirror_opsurf");
        m_mirror_opsurf->SetFinish(polishedfrontpainted); // needed for mirror
        m_mirror_opsurf->SetModel(glisur); 
        m_mirror_opsurf->SetType(dielectric_metal); 
        m_mirror_opsurf->SetPolish(0.999);              // a guess -- FIXME
        G4MaterialPropertiesTable* propMirror= NULL;
        G4Material *matMirror = G4Material::GetMaterial("PMT_Mirror");
        if (matMirror) {
            propMirror= matMirror->GetMaterialPropertiesTable();
        }
        if ( propMirror == NULL ) {
            G4cout << "Warning: setting PMT mirror reflectivity to 0.9999 "
                   << "because no PMT_Mirror material properties defined" << G4endl;
            propMirror= new G4MaterialPropertiesTable();
            propMirror->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
            //propMirror->AddEntry("REFLECTIVITY", twopi*hbarc/(800.0e-9*m), 0.9999);
            //propMirror->AddEntry("REFLECTIVITY", twopi*hbarc/(200.0e-9*m), 0.9999);
            propMirror->AddEntry("REFLECTIVITY", 1.55*eV, 0.92);
            propMirror->AddEntry("REFLECTIVITY", 15.5*eV, 0.92);
        }
        m_mirror_opsurf->SetMaterialPropertiesTable( propMirror );

    }

}

void NNVTMCPPMTManager::init_pmt()
{
    helper_make_solid();  
    helper_make_logical_volume();
    helper_make_physical_volume();

    if(m_enable_optical_model || m_plus_dynode)
    {
        helper_make_mcp_volume();
    }
    helper_make_optical_surface();

    if(m_enable_optical_model)
    {
        helper_fast_sim();
    }
    helper_vis_attr();
}

/**
NNVTMCPPMTManager::helper_make_solid
-------------------------------------

Initial implementation "Reduce the size when real surface is enabled." done by Tao Lin, 09 Aug 2021

Adoption of more efficienct actual CSG tree cutting done by Simon Blyth, Nov 2021

**/

void NNVTMCPPMTManager::helper_make_solid() 
{
    double pmt_delta = 1E-3*mm ;
    double inner_delta = -5*mm ; 

    double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ; 
    // TODO: find out why body_delta depends on m_enable_optical_model and add comment about that 

    double zcut = m_pmt_equator_to_bottom ;

    NNVT_MCPPMT_PMTSolid* maker = m_pmtsolid_maker ; 
    pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
    body_solid   = maker->GetSolid(GetName() + "_body_solid",   body_delta , ' ');
    inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' ');
    inner1_solid = maker->GetSolid(GetName() + "_inner1_solid", inner_delta, 'H'); // head
    inner2_solid = maker->GetSolid(GetName() + "_inner2_solid", inner_delta, 'T'); // tail

    uncut_pmt_solid = pmt_solid ; 
    uncut_body_solid = body_solid ; 
    uncut_inner2_solid = inner2_solid ; 

    if (m_useRealSurface && m_profligate_tail_cut == false) 
    {
        std::cout 
            << "[ X4SolidTree::ApplyZCutTree"
            << " zcut " << std::setw(10) << std::fixed << std::setprecision(3) << zcut 
            << " pmt_delta " << std::setw(10) << std::fixed << std::setprecision(3) << pmt_delta 
            << " body_delta " << std::setw(10) << std::fixed << std::setprecision(3) << body_delta 
            << " inner_delta " << std::setw(10) << std::fixed << std::setprecision(3) << inner_delta 
            << " zcut+pmt_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + pmt_delta 
            << " zcut+body_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + body_delta 
            << " zcut+inner_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + inner_delta 
            << std::endl ; 

        pmt_solid    = X4SolidTree::ApplyZCutTree( pmt_solid   , -(zcut + pmt_delta)   );
        body_solid   = X4SolidTree::ApplyZCutTree( body_solid  , -(zcut + body_delta)  );
        inner2_solid = X4SolidTree::ApplyZCutTree( inner2_solid, -(zcut + inner_delta) );

        std::cout << "] X4SolidTree::ApplyZCutTree zcut " << zcut << std::endl ; 
    }
    else if (m_useRealSurface && m_profligate_tail_cut == true)
    {
        helper_make_solid_profligate_tail_cut() ; 
    } 
}




void NNVTMCPPMTManager::helper_make_solid_profligate_tail_cut()
{
    std::cout << "NNVTMCPPMTManager::helper_make_solid_profligate_tail_cut" << std::endl ; 
    // inner2 
    G4double helper_sep_tube_r = m_pmt_r;
    const double tail_height = m_pmt_h - m_z_equator;
    const double tail_half_height = tail_height / 2;
    const G4ThreeVector cut_tail_displacement(0., 0., -tail_half_height);
    G4VSolid* cut_tail_solid = new G4Tubs("CutTail_NNVTMCPPMT_Solid",
                                          0.,
                                          helper_sep_tube_r+1E-9*mm,
                                          tail_half_height,
                                          0., 360.*degree);
    inner2_solid = new G4IntersectionSolid( GetName() + "_inner2_tail_solid",
                                            inner2_solid,
                                            cut_tail_solid,
                                            NULL,
                                            cut_tail_displacement);

    // pmt solid
    const double pmt_height = m_pmt_h;
    const double pmt_half_height = pmt_height / 2;
    const G4ThreeVector cut_pmt_displacement(0., 0., m_z_equator-pmt_half_height);
    G4VSolid* cut_pmt_solid = new G4Tubs("CutPMT_NNVTMCPPMT_Solid",
                                          0.,
                                          helper_sep_tube_r+1E-9*mm,
                                          pmt_half_height,
                                          0., 360.*degree);
    pmt_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
                                            pmt_solid,
                                            cut_pmt_solid,
                                            NULL,
                                            cut_pmt_displacement);

    // body solid
    const double body_height = m_pmt_h;
    const double body_half_height = body_height / 2;
    const G4ThreeVector cut_body_displacement(0., 0., m_z_equator-pmt_half_height);
    G4VSolid* cut_body_solid = new G4Tubs("CutBody_NNVTMCPPMT_Solid",
                                          0.,
                                          helper_sep_tube_r+1E-9*mm,
                                          body_half_height,
                                          0., 360.*degree);
    body_solid = new G4IntersectionSolid( GetName() + "_pmt_cut_solid",
                                            body_solid,
                                            cut_body_solid,
                                            NULL,
                                            cut_body_displacement);
}
 






bool NNVTMCPPMTManager::StartsWithPrefix(const char* name, const char* prefix)  // static
{
    return strlen(name) >= strlen(prefix) && strncmp( name, prefix, strlen(prefix)) == 0 ;    
}

G4VSolid* NNVTMCPPMTManager::getSolid(const char* name)
{
    if(!m_logical_pmt) 
    {
        std::cout << "[ NNVTMCPPMTManager::getSolid init " << name << std::endl;
        init();
        std::cout << "] NNVTMCPPMTManager::getSolid init " << name << std::endl;
    }

    G4VSolid* so = nullptr ;
    if(StartsWithPrefix(name, "PMTSolid"))    so = pmt_solid ;
    if(StartsWithPrefix(name, "BodySolid"))   so = body_solid ;
    if(StartsWithPrefix(name, "InnerSolid"))  so = inner_solid ;
    if(StartsWithPrefix(name, "Inner1Solid")) so = inner1_solid ;
    if(StartsWithPrefix(name, "Inner2Solid")) so = inner2_solid ;
    if(StartsWithPrefix(name, "DynodeSolid")) so = dynode_solid ;

    if(StartsWithPrefix(name, "UncutPMTSolid"))    so = uncut_pmt_solid ;
    if(StartsWithPrefix(name, "UncutBodySolid"))   so = uncut_body_solid ;
    if(StartsWithPrefix(name, "UncutInner2Solid")) so = uncut_inner2_solid ;

    return so ;
}


void NNVTMCPPMTManager::obsolete_inner_cut()
{
    G4double helper_sep_tube_r = m_pmt_r;
    G4double helper_sep_tube_h = m_z_equator;
    G4double helper_sep_tube_hh = helper_sep_tube_h/2;

    G4VSolid * pInnerSep = new G4Tubs("Inner_Separator",
            0.,
            helper_sep_tube_r+1E-9*mm,
            helper_sep_tube_hh+1E-9*mm,
            0.,360.*degree);
    G4ThreeVector innerSepDispl(0.,0.,helper_sep_tube_hh-1E-9*mm);
    inner1_solid = new G4IntersectionSolid( GetName()
            + "_inner1_solid", inner_solid, pInnerSep, NULL, innerSepDispl);
    inner2_solid = new G4SubtractionSolid( GetName()
            + "_inner2_solid", inner_solid, pInnerSep, NULL, innerSepDispl);
}




void NNVTMCPPMTManager::helper_make_logical_volume()
{
    body_log= new G4LogicalVolume
        ( body_solid,
          GlassMat,
          GetName()+"_body_log" );

    m_logical_pmt = new G4LogicalVolume
        ( pmt_solid,
          GlassMat,
          GetName()+"_log" );

    body_log->SetSensitiveDetector(m_detector);

    inner1_log= new G4LogicalVolume
        ( inner1_solid,
          PMT_Vacuum,
          GetName()+"_inner1_log" );
    inner1_log->SetSensitiveDetector(m_detector);

    inner2_log= new G4LogicalVolume
        ( inner2_solid,
          PMT_Vacuum,
          GetName()+"_inner2_log" );

    /*
    dynode_log= new G4LogicalVolume
        ( dynode_solid,
          Dynode_mat,
          GetName()+"_dynode_log" );
          */

}

void
NNVTMCPPMTManager::helper_make_physical_volume()
{
    
    G4ThreeVector equatorTranslation(0.,0.,m_z_equator);
    G4ThreeVector noTranslation(0.,0.,0.);

    // place outer solids in envelope
    body_phys= new G4PVPlacement
        ( 0,                   // no rotation
          noTranslation,  // puts body equator in right place
          body_log,            // the logical volume
          GetName()+"_body_phys", // a name for this physical volume
          m_logical_pmt,                // the mother volume
          false,               // no boolean ops
          0 );                 // copy number

    // place inner solids in outer solid (vacuum)
    inner1_phys= new G4PVPlacement
        ( 0,                   // no rotation
          noTranslation,       // puts face equator in right place
          GetName()+"_inner1_phys",         // a name for this physical volume
          inner1_log,                    // the logical volume
          body_phys,           // the mother volume
          false,               // no boolean ops
          0 );                 // copy number
    inner2_phys= new G4PVPlacement
        ( 0,                   // no rotation
          noTranslation,       // puts face equator in right place
          GetName()+"_inner2_phys",         // a name for this physical volume
          inner2_log,                    // the logical volume
          body_phys,           // the mother volume
          false,               // no boolean ops
          0 );                 // copy number
    /*
    // place dynode in stem/back
    dynode_phys = new G4PVPlacement
        ( 0,
          G4ThreeVector(0.0, 0.0, this->z_dynode - hh_dynode),
          GetName()+"_dynode_phys",
          dynode_log,
          inner2_phys,
          false,
          0 );

          */
}

void 
NNVTMCPPMTManager::helper_make_mcp_volume()
{
    G4double thickness  = 1.*mm;
    G4double edge_hz    = 10.*mm;

    G4double mcp_r      = 20.0*mm;
    G4double mcp_hz     = 1.*mm;

    G4double plate_r    = 47.9*mm;
    G4double plate_hz   = 5.*mm;

    G4double tube_r     = plate_r-5.*mm;
    G4double tube_hz    = 60.0*mm;

    G4double shield_r   = 45.0*mm;
    G4double shield_hz  = 1.*mm;
    G4double shield_d   = 213.5*mm;

    G4double dist       = 116.*mm;

    G4VisAttributes *visAtt;
    G4bool fCheckOverlaps = false;
    /* MCP STRUCTURE */
    // PART I
    G4VSolid *edge_solid = new G4Tubs
        ( GetName() + "_edge_solid",
          plate_r - thickness,
          plate_r,
          edge_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *edge_log = new G4LogicalVolume
        ( edge_solid,
          DynodeMat,
          GetName() + "_edge_log" );

    visAtt = new G4VisAttributes(G4Color::Red());
    edge_log->SetVisAttributes(visAtt);

    G4PVPlacement *edge_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist-edge_hz),
          edge_log,
          GetName() + "_edge_phy",
          inner2_log,
          false,
          0,
          fCheckOverlaps );

    // PART II
    G4VSolid *plate_solid = new G4Tubs
        ( GetName() + "_plate_solid",
          mcp_r,
          plate_r,
          plate_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *plate_log = new G4LogicalVolume
        ( plate_solid,
          DynodeMat,
          GetName() + "_plate_log" );

    plate_log->SetVisAttributes(visAtt);

    G4PVPlacement *plate_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+plate_hz),
          plate_log,
          GetName() + "_plate_phy",
          inner2_log,
          false,
          0,
          fCheckOverlaps );

    // PART III
    //    
    // Note:
    //     The backend of tube need to be cut when the PMT back is cut
    // 27th Oct 2021, Tao Lin
    //

    if (m_useRealSurface) {
        // the 5mm is the thickness of PMT
        double new_tube_hz = (m_pmt_h-m_z_equator-5.*mm-(dist+2*plate_hz))/2;
        LogInfo << "Option RealSurface is enabed. Reduce the height of tube_hz from "
                << tube_hz << " to " << new_tube_hz << std::endl;
        tube_hz = new_tube_hz; // reduce from 120mm to ~60mm. so the z will be at ~180mm.
    }
   
    G4VSolid *tube_solid = new G4Tubs
        ( GetName() + "_tube_solid",
          tube_r-thickness,
          tube_r,
          tube_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *tube_log = new G4LogicalVolume
        ( tube_solid,
          DynodeMat,
          GetName() + "_tube_log" );

    visAtt = new G4VisAttributes(G4Color::Yellow());
    tube_log->SetVisAttributes(visAtt);

    G4PVPlacement *tube_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+plate_hz*2+tube_hz),
          tube_log,
          GetName() + "_tube_phy",
          inner2_log,
          false,
          0,
          fCheckOverlaps );

    // PART VI

    G4VSolid *mcp_solid = new G4Tubs
        ( GetName() + "_mcp_solid",
          0.,
          mcp_r,
          mcp_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *mcp_log = new G4LogicalVolume
        ( mcp_solid,
          DynodeMat,
          GetName() + "_mcp_log" );

    visAtt = new G4VisAttributes(G4Color::Green());
    mcp_log->SetVisAttributes(visAtt);

    G4PVPlacement *mcp_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+plate_hz*2+mcp_hz),
          mcp_log,
          GetName() + "_mcp_phy",
          inner2_log,
          false,
          0,
          fCheckOverlaps );

    // PART V
    //
    // Note: when the PMT back is cut, just disable this part.
    // 27th Oct 2021, Tao Lin
    G4PVPlacement *shield_phy = nullptr;
    if (!m_useRealSurface) {
        G4VSolid *shield_solid = new G4Tubs
            ( GetName() + "_shield_solid",
              tube_r,
              shield_r,
              shield_hz,
              0.,
              2.*M_PI );

        G4LogicalVolume *shield_log = new G4LogicalVolume
            ( shield_solid,
              DynodeMat,
              GetName() + "_shield_log" );

        visAtt = new G4VisAttributes(G4Color::Blue());
        shield_log->SetVisAttributes(visAtt);

        shield_phy = new G4PVPlacement
            ( 0,
              -G4ThreeVector(0., 0., shield_d+shield_hz),
              shield_log,
              GetName() + "_shield_phy",
              inner2_log,
              false,
              0,
              fCheckOverlaps );
    }

    /* OPTICAL SURFACE */
    // PLATE SURFACE
    G4MaterialPropertiesTable *plateSurfaceMPT = new G4MaterialPropertiesTable();
    plateSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    plateSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.65);
    plateSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.65);

    G4OpticalSurface *plateOpSurface = new G4OpticalSurface("plateOpSurface");
    plateOpSurface->SetType(dielectric_metal);
    plateOpSurface->SetModel(glisur);
    plateOpSurface->SetPolish(0.999);
    plateOpSurface->SetMaterialPropertiesTable(plateSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_mcp_plate_opsurface", inner2_phys, plate_phy, plateOpSurface);

    // EDGE SURFACE
    G4MaterialPropertiesTable *edgeSurfaceMPT = new G4MaterialPropertiesTable();
    edgeSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    edgeSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.65);
    edgeSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.65);
    
    G4OpticalSurface *edgeOpSurface = new G4OpticalSurface("edgeOpSurface");
    edgeOpSurface->SetType(dielectric_metal);
    edgeOpSurface->SetModel(glisur);
    edgeOpSurface->SetPolish(0.999);
    edgeOpSurface->SetMaterialPropertiesTable(edgeSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_mcp_edge_opsurface", inner2_phys, edge_phy, edgeOpSurface);

    // TUBE SURFACE
    G4MaterialPropertiesTable *tubeSurfaceMPT = new G4MaterialPropertiesTable();
    tubeSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    tubeSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.65);
    tubeSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.65);
    
    G4OpticalSurface *tubeOpSurface = new G4OpticalSurface("tubeOpSurface");
    tubeOpSurface->SetType(dielectric_metal);
    tubeOpSurface->SetModel(glisur);
    tubeOpSurface->SetPolish(0.999);
    tubeOpSurface->SetMaterialPropertiesTable(tubeSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_mcp_tube_opsurface", inner2_phys, tube_phy, tubeOpSurface);

    // MCP SURFACE
    G4MaterialPropertiesTable *mcpSurfaceMPT = new G4MaterialPropertiesTable();
    mcpSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    mcpSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.);
    mcpSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.);
    
    G4OpticalSurface *mcpOpSurface = new G4OpticalSurface("mcpOpSurface");
    mcpOpSurface->SetType(dielectric_metal);
    mcpOpSurface->SetModel(glisur);
    mcpOpSurface->SetPolish(0.999);
    mcpOpSurface->SetMaterialPropertiesTable(mcpSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_mcp_opsurface", inner2_phys, mcp_phy, mcpOpSurface);
    if (shield_phy) { // only if shield_phy exists, enable the OP surface
        new G4LogicalBorderSurface(GetName()+"_shield_opsurface", inner2_phys, shield_phy, mcpOpSurface);
    }
}

void
NNVTMCPPMTManager::helper_make_optical_surface()
{
    new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf1",
            inner1_phys, body_phys,
            Photocathode_opsurf);
    new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf2",
            body_phys, inner1_phys,
            Photocathode_opsurf);
    new G4LogicalBorderSurface(GetName()+"_mirror_logsurf1",
            inner2_phys, body_phys,
            m_mirror_opsurf);
    new G4LogicalBorderSurface(GetName()+"_mirror_logsurf2",
            body_phys, inner2_phys,
            m_mirror_opsurf);
}

void
NNVTMCPPMTManager::helper_fast_sim()
{

#ifdef PMTSIM_STANDALONE
#else

    G4Region* body_region = new G4Region(this->GetName()+"_body_region");
    body_log->SetRegion(body_region);
    body_region->AddRootLogicalVolume(body_log);

    junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
                                                                   body_phys, body_region);

    m_pmt_param_svc = 0;
    LogInfo << "Retrieving PMTParamSvc." << std::endl;
    SniperPtr<IPMTParamSvc> parsvc(*getParent(), "PMTParamSvc");
    if(parsvc.invalid()){
        LogError << "Can't get PMTParamSvc. We can't initialize PMT." << std::endl;
        assert(0);
        exit(EXIT_FAILURE);
    }else{
        LogInfo << "Retrieve PMTParamSvc successfully." << std::endl;
        m_pmt_param_svc = parsvc.data();
    }
    pmtOpticalModel->setPMTParamSvc(m_pmt_param_svc);

    m_pmt_sim_param_svc = 0;
    LogInfo << "Retrieving PMTParamSvc." << std::endl;
    SniperPtr<IPMTSimParamSvc> simsvc(*getParent(), "PMTSimParamSvc");
    if(simsvc.invalid()){
        LogError << "Can't get PMTSimParamSvc. We can't initialize PMT." << std::endl;
        assert(0);
        exit(EXIT_FAILURE);
    }else{
        LogInfo <<"Retrieve PMTSimParamSvc successfully." << std::endl;
        m_pmt_sim_param_svc = simsvc.data();
    }
    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);

    // We don't support the original PMT optical model in this new class.
    // new dywPMTOpticalModel( GetName()+"_optical_model", 
    //        body_phys, body_region);

#endif

}
void
NNVTMCPPMTManager::helper_vis_attr()
{  
    G4VisAttributes * visAtt;
    m_logical_pmt -> SetVisAttributes (G4VisAttributes::Invisible);
    // PMT glass
    // visAtt= new G4VisAttributes(G4Color(0.0,1.0,1.0,0.05));
    // body_log->SetVisAttributes( visAtt );
    body_log->SetVisAttributes( G4VisAttributes::Invisible );
    // dynode is medium gray
    visAtt= new G4VisAttributes(G4Color(0.5,0.5,0.5,1.0));
    //dynode_log->SetVisAttributes( visAtt );
    // (surface of) interior vacuum is clear orangish gray on top (PC),
    // silvery blue on bottom (mirror)
    // visAtt= new G4VisAttributes(G4Color(0.7,0.5,0.3,0.27));
    visAtt= new G4VisAttributes(G4Color(0.7,0.5,0.3, 1.0));
    visAtt -> SetForceSolid(true);
    inner1_log->SetVisAttributes (visAtt);
    // visAtt= new G4VisAttributes(G4Color(0.6,0.7,0.8,0.67));
    visAtt= new G4VisAttributes(G4Color(0.6,0.7,0.8,1.0));
    visAtt -> SetForceSolid(true);
    inner2_log->SetVisAttributes (visAtt);

}

void
NNVTMCPPMTManager::init_fast_cover() {
    // solid
    double thickness = 1E-3*mm;
    G4double zPlane[] = {
                        (m_z_equator-m_pmt_h)+thickness,
                        m_z_equator+thickness 
                        };
    G4double rInner[] = {0.,
                         0.};
    G4double rOuter[] = {m_pmt_r + thickness,
                         m_pmt_r + thickness};

    G4VSolid* cover_solid = new G4Polycone(
                                GetName()+"Tubs",
                                0,
                                360*deg,
                                2,
                                zPlane,
                                rInner,
                                rOuter
                                );
    // volume
    G4LogicalVolume* cover_lv = new G4LogicalVolume
        ( cover_solid,
          m_cover_mat,
          GetName()+"_cover");
    // place pmt into the cover
    G4ThreeVector noTranslation(0.,0.,0.);
    new G4PVPlacement
        (0,
         noTranslation,
         m_logical_pmt,
         GetName()+"_cover_phys",
         cover_lv,
         false,
         0
        );

    m_logical_pmt = cover_lv;
}
