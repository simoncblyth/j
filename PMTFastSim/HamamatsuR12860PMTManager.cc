
#ifdef PMTFASTSIM_STANDALONE
#define LogInfo  std::cout 
#define LogError std::cerr 
#include "junoPMTOpticalModel.hh"
#else
//#include <boost/python.hpp>
#include "junoPMTOpticalModel.hh"
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/ToolFactory.h"
#endif

#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4Tubs.hh"
#include "G4IntersectionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4SDManager.hh"
#include "G4Polycone.hh"

#include "HamamatsuR12860PMTManager.hh"
#include "Hamamatsu_R12860_PMTSolid.hh"
#include "ZSolid.h"

using namespace CLHEP;

#ifdef PMTFASTSIM_STANDALONE
#else
DECLARE_TOOL(HamamatsuR12860PMTManager);
#endif

G4LogicalVolume* HamamatsuR12860PMTManager::getLV() 
{
    if(!m_logical_pmt) init();
    return m_logical_pmt;
}

G4LogicalVolume* HamamatsuR12860PMTManager::getLV(const char* name)
{
    if(!m_logical_pmt) init();
    G4LogicalVolume* lv = nullptr ;  
    if(StartsWithPrefix(name, "LogicalPMT")) lv = m_logical_pmt ; 
    if(StartsWithPrefix(name, "PMTLog"))     lv = pmt_log ; 
    if(StartsWithPrefix(name, "BodyLog"))    lv = body_log ; 
    if(StartsWithPrefix(name, "InnerLog"))   lv = inner_log ; 
    if(StartsWithPrefix(name, "Inner1Log"))  lv = inner1_log ; 
    if(StartsWithPrefix(name, "Inner2Log"))  lv = inner2_log ; 

    if(StartsWithPrefix(name, "DynodeLog"))  lv = dynode_log ; 
    if(StartsWithPrefix(name, "LogicalCover")) lv = m_logical_cover ; 
    return lv ; 
}

G4PVPlacement* HamamatsuR12860PMTManager::getPV(const char* name)
{
    if(!m_logical_pmt) init();
    G4PVPlacement* pv = nullptr ; 
    if(StartsWithPrefix(name, "BodyPhys"))   pv = body_phys ; 
    if(StartsWithPrefix(name, "InnerPhys"))  pv = inner_phys ; 
    if(StartsWithPrefix(name, "Inner1Phys")) pv = inner1_phys ; 
    if(StartsWithPrefix(name, "Inner2Phys")) pv = inner2_phys ; 
    if(StartsWithPrefix(name, "DynodePhys")) pv = dynode_phys ; 
    return pv ; 
}

/**


   PV            LV                SOLID          MATERIAL         MOTHER


                 m_logical_pmt     pmt_solid      GlassMat

   body_phys     body_log          body_solid     GlassMat        m_logical_pmt
                      
   inner1_phys   inner1_log        inner1_solid   PMT_Vacuum      body_log

   inner2_phys   inner2_log        inner2_solid   PMT_Vacuum      body_log

**/






G4double HamamatsuR12860PMTManager::GetPMTRadius() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_pmt_r;
}

G4double HamamatsuR12860PMTManager::GetPMTHeight() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_pmt_h;
}

G4double HamamatsuR12860PMTManager::GetZEquator() {
    if (!getLV()) {
        LogError << "Can't initialize PMT." << std::endl;;
    }
    return m_z_equator;
}

G4ThreeVector HamamatsuR12860PMTManager::GetPosInPMT() {
    G4ThreeVector rndm_pos;
    return rndm_pos;
}

// Constructor
HamamatsuR12860PMTManager::HamamatsuR12860PMTManager(const G4String& plabel )
    :
#ifdef PMTFASTSIM_STANDALONE
    IGeomManager(plabel),
#else
    ToolBase(plabel), 
    m_label(plabel),
#endif
    m_pmtsolid_maker(0),
    pmtOpticalModel(nullptr),
    pmt_solid(nullptr), 
    body_solid(nullptr), 
    inner_solid(nullptr),
    inner1_solid(nullptr), 
    inner2_solid(nullptr), 
    uncut_pmt_solid(nullptr),
    uncut_body_solid(nullptr),
    uncut_inner_solid(nullptr),
    uncut_inner2_solid(nullptr),
    dynode_solid(nullptr),
    pmt_log(nullptr), 
    body_log(nullptr), 
    inner_log(nullptr), 
    inner1_log(nullptr), 
    inner2_log(nullptr), 
    dynode_log(nullptr),
    body_phys(nullptr), 
    inner_phys(nullptr), 
    inner1_phys(nullptr), 
    inner2_phys(nullptr), 
    dynode_phys(nullptr), 
    m_logical_pmt(nullptr), 
    m_mirror_opsurf(nullptr),
    Photocathode_opsurf(nullptr),
    GlassMat(nullptr), 
    PMT_Vacuum(nullptr), 
    DynodeMat(nullptr),
    m_detector(nullptr),
    m_logical_cover(nullptr), 
    m_cover_mat(nullptr),
    m_simple(getenv("JUNO_PMT20INCH_SIMPLE") == nullptr ? false : true),
    m_plus_dynode(getenv("JUNO_PMT20INCH_PLUS_DYNODE") == nullptr ? false : true),
    m_profligate_tail_cut(getenv("JUNO_PMT20INCH_PROFLIGATE_TAIL_CUT") == nullptr ? false : true ),
    m_pmt_equator_to_bottom(0.)
{
    declProp("FastCover", m_fast_cover=false);
    declProp("FastCoverMaterial", m_cover_mat_str="Water");
    declProp("UsePMTOpticalModel", m_enable_optical_model=true); // SCB: TODO: switch to enum to handle different types of model  
    declProp("UseRealSurface", m_useRealSurface=true );
}

std::string HamamatsuR12860PMTManager::desc() const 
{
    std::stringstream ss ; 
    ss
         << std::setw(30) << "HamamatsuR12860PMTManager"
         << " m_simple "        << ( m_simple   ? "Y" : "N" )
         << " m_plus_dynode "    << ( m_plus_dynode    ? "Y" : "N" )
         << " m_useRealSurface " << ( m_useRealSurface ? "Y" : "N" )
         << " m_profligate_tail_cut " << ( m_profligate_tail_cut ? "Y" : "N" )
         ;

    std::string s = ss.str(); 
    return s ; 
}





HamamatsuR12860PMTManager::~HamamatsuR12860PMTManager() {
    if (m_pmtsolid_maker) {
        delete m_pmtsolid_maker;
    }
}
    

// Helper Methods
void HamamatsuR12860PMTManager::init() {
#ifdef PMTFASTSIM_STANDALONE
    std::cout << "HamamatsuR12860PMTManager::init" << std::endl ; 
#else
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    m_detector = SDman->FindSensitiveDetector("PMTSDMgr");

    bool expect = m_detector != nullptr ; 
    assert(expect);
    if(!expect) exit(EXIT_FAILURE); 
    
#endif
    init_material();
    init_variables();
    init_mirror_surface();
    init_pmt();

    if (m_fast_cover) {
        init_fast_cover();
    }
}

void
HamamatsuR12860PMTManager::init_material() {

     GlassMat = G4Material::GetMaterial("Pyrex");
     PMT_Vacuum = G4Material::GetMaterial("Vacuum"); 
     DynodeMat = G4Material::GetMaterial("Steel");

     Photocathode_opsurf =  new G4OpticalSurface(GetName()+"_Photocathode_opsurf");
     Photocathode_opsurf->SetType(dielectric_metal); // ignored if RINDEX defined
     //Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode")->GetMaterialPropertiesTable() );

#ifdef PMTFASTSIM_STANDALONE
     std::cout 
          << "HamamatsuR12860PMTManager::init_material" 
          << " GlassMat " << ( GlassMat ? "Y" : "N" )
          << " PMT_Vacuum " << ( PMT_Vacuum ? "Y" : "N" )
          << " DynodeMat " << ( DynodeMat ? "Y" : "N" )
          << std::endl 
          ; 

     G4Material* mat = G4Material::GetMaterial("photocathode_Ham20inch"); 
     Photocathode_opsurf->SetMaterialPropertiesTable(mat ? mat->GetMaterialPropertiesTable() : nullptr ) ;  
#else
     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_Ham20inch")->GetMaterialPropertiesTable() );
#endif
     if (m_fast_cover) {
         m_cover_mat = G4Material::GetMaterial(m_cover_mat_str);
         assert(m_cover_mat);
     }
}


void HamamatsuR12860PMTManager::init_variables() {
    m_pmt_r = 254.*mm;
    m_pmt_h = 640.*mm;
    m_z_equator = 190.*mm; // From top to equator

    // Reduce the height of PMT
    // Tao Lin, 09 Aug 2021
    if (m_useRealSurface) {
        const double radInnerWaterRealSurface = 19.629*m;
        const double r = m_pmt_r + 1.*cm; // 1cm is the mask
        double pmt_eq_to_bottom = sqrt(radInnerWaterRealSurface*radInnerWaterRealSurface
                                       -r*r) - 19.434*m; // at z equator


        // then, subtract the thickness of mask
        pmt_eq_to_bottom -= 10.*mm;

        // avoid the overlap between PMT tail and innerWater
        const double safety_distance = 1.*cm;
        pmt_eq_to_bottom -= safety_distance;


        m_pmt_equator_to_bottom = pmt_eq_to_bottom ; 

        double pmt_h = pmt_eq_to_bottom + m_z_equator ;
        LogInfo << "Option RealSurface is enabled in Central Detector. "
                << " Reduce the m_pmt_h from "
                << m_pmt_h << " to " << pmt_h
                << std::endl;


        std::cout 
           << " radInnerWaterRealSurface " << radInnerWaterRealSurface
           << " r " << r 
           << " pmt_eq_to_bottom  " << pmt_eq_to_bottom 
           << " orig m_pmt_h " << m_pmt_h
           << " new m_pmt_h " << pmt_h  
           << " m_pmt_equator_to_bottom  " << m_pmt_equator_to_bottom 
           << std::endl 
           ;

        m_pmt_h = pmt_h;
    }
    m_pmtsolid_maker = new Hamamatsu_R12860_PMTSolid();
}

void
HamamatsuR12860PMTManager::init_mirror_surface() {
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

/**
HamamatsuR12860PMTManager::init_pmt
------------------------------------

* dynode geometry serves no purpose with the old optical model when  *m_enable_optical_model=false*

* *m_plus_dynode* adds the dynode geometry even when *m_enable_optical_model* is false, this is
  for debugging only : such as to check if the dynode geometry fits inside the cut PMT 


**/

void HamamatsuR12860PMTManager::init_pmt() 
{

#ifdef PMTFASTSIM_STANDALONE
  std::cout 
      << "HamamatsuR12860PMTManager::init_pmt" 
      << " m_enable_optical_model " << m_enable_optical_model
      << " m_plus_dynode " << m_plus_dynode
      << std::endl 
      ;  
#endif


  helper_make_solid();  
  helper_make_logical_volume();
  helper_make_physical_volume();




  if(m_enable_optical_model || m_plus_dynode)
  {
      helper_make_dynode_volume();
  }

  helper_make_optical_surface();

  if(m_enable_optical_model)
  {
      helper_fast_sim();
  }
  
  helper_vis_attr();
}

/**
HamamatsuR12860PMTManager::helper_make_solid
----------------------------------------------

Tail cutting when real surface is enabled was first implemented by Tao Lin, 09 Aug 2021

* TODO: find out why body_delta depends on m_enable_optical_model and add comment about that 
* ancient TODO: face of tube 100 um from front of cylinder

**/

void HamamatsuR12860PMTManager::helper_make_solid() 
{
    double pmt_delta = 1E-3*mm ; 
    double inner_delta =  -5*mm ;  
    double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ; 

    double zcut = m_pmt_equator_to_bottom ; 

    Hamamatsu_R12860_PMTSolid* maker = m_pmtsolid_maker ; 

    if(m_simple == false)
    {
        pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
        body_solid   = maker->GetSolid(GetName() + "_body_solid",   body_delta , ' ');
        //inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' '); 
        inner1_solid = maker->GetSolid(GetName() + "_inner1_solid", inner_delta, 'H');
        inner2_solid = maker->GetSolid(GetName() + "_inner2_solid", inner_delta, 'T');

        uncut_pmt_solid = pmt_solid ; 
        uncut_body_solid = body_solid ; 
        uncut_inner2_solid = inner2_solid ; 
    }
    else
    {
        pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
        inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' ');  

        uncut_pmt_solid = pmt_solid ; 
        uncut_inner_solid = inner_solid ; 
    }


    if (m_useRealSurface && m_profligate_tail_cut == false ) 
    {
        std::cout 
            << "[ ZSolid::ApplyZCutTree"
            << " zcut " << std::setw(10) << std::fixed << std::setprecision(3) << zcut 
            << " pmt_delta " << std::setw(10) << std::fixed << std::setprecision(3) << pmt_delta 
            << " body_delta " << std::setw(10) << std::fixed << std::setprecision(3) << body_delta 
            << " inner_delta " << std::setw(10) << std::fixed << std::setprecision(3) << inner_delta 
            << " zcut+pmt_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + pmt_delta 
            << " zcut+body_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + body_delta 
            << " zcut+inner_delta " << std::setw(10) << std::fixed << std::setprecision(3) << zcut + inner_delta 
            << std::endl ; 

        if(pmt_solid)    pmt_solid    = ZSolid::ApplyZCutTree( pmt_solid   , -(zcut + pmt_delta)   );
        if(body_solid)   body_solid   = ZSolid::ApplyZCutTree( body_solid  , -(zcut + body_delta)  );
        if(inner_solid)  inner_solid = ZSolid::ApplyZCutTree(  inner_solid,  -(zcut + inner_delta) );
        if(inner2_solid) inner2_solid = ZSolid::ApplyZCutTree( inner2_solid, -(zcut + inner_delta) );

        std::cout << "] ZSolid::ApplyZCutTree zcut " << zcut << std::endl ; 
    }
    else if (m_useRealSurface && m_profligate_tail_cut == true )
    {
         helper_make_solid_profligate_tail_cut();
    } 
}

/**
HamamatsuR12860PMTManager::helper_make_solid_profligate_tail_cut
------------------------------------------------------------------

"Cutting" PMT via G4IntersectionSolid actually increases the CSG nodes
to model the geometry and forces every single intersect onto the solid to 
traverse many useless "cutaway" nodes despite there being no interest in 
finding the intersects with them.  Although this approach is easy to do 
it is incredibly inefficient as it means that you get to pay for the price 
of the convenience of solid definition easily many millions of times per event. 

This contrasts with the above approach that uses ZSolid::ApplyZCutTree that 
actually cuts the CSG tree, leading to a significant simplification.

**/

void HamamatsuR12860PMTManager::helper_make_solid_profligate_tail_cut()
{
    // inner2 
    std::cout << "HamamatsuR12860PMTManager::helper_make_solid_profligate_tail_cut" << std::endl ; 

    G4double helper_sep_tube_r = m_pmt_r;
    const double tail_height = m_pmt_h - m_z_equator;
    const double tail_half_height = tail_height / 2;
    const G4ThreeVector cut_tail_displacement(0., 0., -tail_half_height);
    G4VSolid* cut_tail_solid = new G4Tubs( GetName() + "_CutTail_HamaPMT_Solid",
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

    G4VSolid* cut_pmt_solid = new G4Tubs( GetName() + "_CutPMT_HamaPMT_Solid",
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
    G4VSolid* cut_body_solid = new G4Tubs( GetName() + "_body_solid_intubs",
                                          0.,
                                          helper_sep_tube_r+1E-9*mm,
                                          body_half_height,
                                          0., 360.*degree);
    body_solid = new G4IntersectionSolid( GetName() + "_body_solid_cut",
                                            body_solid,
                                            cut_body_solid,
                                            NULL,
                                            cut_body_displacement);



}



void HamamatsuR12860PMTManager::dump(const char* msg)  // cannot be const as getSolid may init
{
    std::vector<const char*> names = {
        "pmt_solid",
        "body_solid",
        "inner_solid",
        "inner1_solid",
        "inner2_solid",
        "dynode_solid",
        "uncut_pmt_solid",
        "uncut_body_solid",
        "uncut_inner2_solid"
    };

    std::cout << msg << std::endl ; 
    for(unsigned i=0 ; i < names.size() ; i++)
    {
        const char* name = names[i]; 
        const G4VSolid* solid = getSolid(name) ;  
        std::cout 
            << " name " << std::setw(20) << name
            << " solid " << std::setw(20) << solid
            << std::endl 
            ;
    }
}


bool HamamatsuR12860PMTManager::StartsWithPrefix(const char* name, const char* prefix)  // static
{
    bool match = strlen(name) >= strlen(prefix) && strncmp( name, prefix, strlen(prefix)) == 0 ;   
    if(false) std::cout 
        << "HamamatsuR12860PMTManager::StartsWithPrefix" 
        << " name[" << name << "]" 
        << " prefix[" << prefix << "]" 
        << " strlen(name) " << strlen(name)
        << " strlen(prefix) " << strlen(prefix)
        << " match " << match
        << std::endl 
        ;

    return match ; 
}


G4VSolid*  HamamatsuR12860PMTManager::getSolid(const char* name)
{
    if(!m_logical_pmt) 
    {
        std::cout << "[ HamamatsuR12860PMTManager::getSolid " << name << std::endl; 
        init();
        std::cout << "] HamamatsuR12860PMTManager::getSolid " << name << std::endl; 
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
    if(StartsWithPrefix(name, "UncutInnerSolid"))  so = uncut_inner_solid ; 
    if(StartsWithPrefix(name, "UncutInner2Solid")) so = uncut_inner2_solid ; 

    if( so == nullptr ) std::cerr << "HamamatsuR12860PMTManager::getSolid gives null name[" << name << "]" << std::endl ; 


    return so ; 
}

junoPMTOpticalModel* HamamatsuR12860PMTManager::getPMTOpticalModel(const char* name) 
{
    std::cout 
        << "HamamatsuR12860PMTManager::getPMTOpticalModel"
        << " name " << ( name ? name : "-" )
        << " pmtOpticalModel " << ( pmtOpticalModel ? "Y" : "N" ) 
        << std::endl 
        ;
    return pmtOpticalModel ; 
}



void HamamatsuR12860PMTManager::obsolete_inner_cut()
{
    assert(0); 
    exit(EXIT_FAILURE); 

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

/**

   LV                SOLID          MATERIAL


   m_logical_pmt     pmt_solid      GlassMat

   body_log          body_solid     GlassMat 

   inner1_log        inner1_solid   PMT_Vacuum

   inner2_log        inner2_solid   PMT_Vacuum

**/


void
HamamatsuR12860PMTManager::helper_make_logical_volume()
{
    pmt_log = new G4LogicalVolume
        ( pmt_solid,
          GlassMat,
          GetName()+"_log" );

    body_log= new G4LogicalVolume
        ( body_solid,
          GlassMat,
          GetName()+"_body_log" );

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

    m_logical_pmt = pmt_log ; 
}



/**


   PV            LV                SOLID          MATERIAL         MOTHER


                 m_logical_pmt     pmt_solid      GlassMat

   body_phys     body_log          body_solid     GlassMat        m_logical_pmt
                      
   inner1_phys   inner1_log        inner1_solid   PMT_Vacuum      body_phys

   inner2_phys   inner2_log        inner2_solid   PMT_Vacuum      body_phys

**/

void HamamatsuR12860PMTManager::helper_make_physical_volume()
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
}

/**
HamamatsuR12860PMTManager::helper_make_dynode_volume
------------------------------------------------------

Creates solids, logical volumes and physical volumes placing them within *inner2_log* 

**/

void HamamatsuR12860PMTManager::helper_make_dynode_volume()
{
    G4LogicalVolume* parent_log = inner2_log ;  


    G4double thickness  = 1.*mm;

    G4double plate_r    = 103.*mm;
    G4double plate_hz   = 1.*mm;
    
    G4double innedge_r  = 50.*mm;
    G4double edge_hz    = 20.*mm;

    G4double innring_r  = 65.*mm;
    G4double innring_hz = 1.*mm;
    
    G4double grid_r     = 40.*mm;
    G4double grid_hz    = 1.*mm;

    G4double tube_r     = 95.*mm;
    G4double tube_hz    = 80.*mm;

    G4double dist       = 50.*mm;
    
    G4double shield_r   = 150.4*mm;
    G4double shield_d   = (210.-61.56)*mm;

    G4VisAttributes *visAtt;

    /* PLATE ON TOP */
    // PART I
    G4Tubs *plate_solid = new G4Tubs
        ( GetName() + "_plate_solid",
          grid_r,
          plate_r,
          plate_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *plate_log = new G4LogicalVolume
        ( plate_solid,
          DynodeMat,
          GetName() + "_plate_log" );

    visAtt = new G4VisAttributes(G4Color::Red());
    plate_log->SetVisAttributes(visAtt);

    G4PVPlacement *plate_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz*2+plate_hz),
          plate_log,
          GetName() + "_plate_phy",
          parent_log,
          false,
          0,
          false );
    
    // PART II
    G4Tubs *outer_edge_solid = new G4Tubs
        ( GetName() + "_outer_edge_solid",
          plate_r - thickness,
          plate_r,
          edge_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *outer_edge_log = new G4LogicalVolume
        ( outer_edge_solid,
          DynodeMat,
          GetName() + "_outer_edge_log" );
    
    outer_edge_log->SetVisAttributes(visAtt);

    G4PVPlacement *outer_edge_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz),
          outer_edge_log,
          GetName() + "_outer_edge_phy",
          parent_log,
          false,
          0,
          false );


    // PART III
    G4Tubs *inner_edge_solid = new G4Tubs
        ( GetName() + "_inner_edge_solid",
          innedge_r - thickness,
          innedge_r,
          edge_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *inner_edge_log = new G4LogicalVolume
        ( inner_edge_solid,
          DynodeMat,
          GetName() + "_inner_edge_log" );

    inner_edge_log->SetVisAttributes(visAtt);

    G4PVPlacement *inner_edge_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz),
          inner_edge_log,
          GetName() + "_inner_edge_phy",
          parent_log,
          false,
          0,
          false );

    // PART IV
    G4Tubs *inner_ring_solid = new G4Tubs
        ( GetName() + "_inner_ring_solid",
          innedge_r,
          innring_r,
          innring_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *inner_ring_log = new G4LogicalVolume
        ( inner_ring_solid,
          DynodeMat,
          GetName() + "_inner_ring_log" );

    inner_ring_log->SetVisAttributes(visAtt);

    G4PVPlacement *inner_ring_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz),
          inner_ring_log,
          GetName() + "_inner_ring_phy",
          parent_log,
          false,
          0,
          false );

    /* THE CYLINDRICAL TUBE AT BOTTOM */
    // Note: The backend of the tube need to be cut when the PMT back is cut
    //       -- 27th Oct 2021, Tao Lin
    if (m_useRealSurface) {
        // the 5mm is the thickness of PMT
        double new_tube_hz = (m_pmt_h-m_z_equator-5.*mm-(dist+edge_hz*2+plate_hz*2))/2;
        LogInfo << "Option RealSurface is enabed. Reduce the height of tube_hz from "
                << tube_hz << " to " << new_tube_hz << std::endl;
        tube_hz = new_tube_hz; // reduce from 160mm to ~90. so the z will be at ~180mm.
    }


    G4Tubs *tube_solid = new G4Tubs
        ( GetName() + "_dynode_tube_solid",
          tube_r - thickness,
          tube_r,
          tube_hz,
          0.,
          2.*M_PI );

    G4LogicalVolume *tube_log = new G4LogicalVolume
        ( tube_solid,
          DynodeMat,
          GetName() + "_dynode_tube_log" );
    
    visAtt = new G4VisAttributes(G4Color::Yellow());
    tube_log->SetVisAttributes(visAtt);

    G4PVPlacement *tube_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz*2+plate_hz*2+tube_hz),
          tube_log,
          GetName() + "_dynode_tube_phy",
          parent_log,
          false,
          0,
          false );

    // GRID
    G4Tubs *grid_solid = new G4Tubs
        ( GetName() + "_grid_solid",
          0.,
          grid_r,
          grid_hz,
          0.,
          2.*M_PI );
    
    G4LogicalVolume *grid_log = new G4LogicalVolume
        ( grid_solid,
          DynodeMat,
          GetName() + "_grid_log" );
    
    visAtt = new G4VisAttributes(G4Color::Green());
    grid_log->SetVisAttributes(visAtt);

    G4PVPlacement *grid_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., dist+edge_hz*2+grid_hz),
          grid_log,
          GetName() + "_grid_phy",
          parent_log,
          false,
          0,
          false );

    // SHIELD
    G4Tubs *shield_solid = new G4Tubs
        ( GetName() + "_shield_solid",
          tube_r,
          shield_r-3.8*mm,
          thickness,
          0.,
          2.*M_PI);

    G4LogicalVolume *shield_log = new G4LogicalVolume
        ( shield_solid,
          DynodeMat,
          GetName() + "_shield_log" );
    
    visAtt = new G4VisAttributes(G4Color::Blue());
    shield_log->SetVisAttributes(visAtt);

    G4PVPlacement *shield_phy = new G4PVPlacement
        ( 0,
          -G4ThreeVector(0., 0., shield_d+5.*mm),
          shield_log,
          GetName() + "_shield_phy",
          parent_log,
          false,
          0,
          false );

    /* OPTICAL SURFACE */
    // PLATE SURFACE
    G4MaterialPropertiesTable *plateSurfaceMPT = new G4MaterialPropertiesTable();
    plateSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    plateSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.20);
    plateSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.20);

    G4OpticalSurface *plateOpSurface = new G4OpticalSurface("plateOpSurface");
    plateOpSurface->SetType(dielectric_metal);
    plateOpSurface->SetModel(glisur);
    plateOpSurface->SetPolish(0.999);
    plateOpSurface->SetMaterialPropertiesTable(plateSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_dynode_plate_opsurface", inner2_phys, plate_phy, plateOpSurface);
    new G4LogicalBorderSurface(GetName()+"_inner_ring_opsurface", inner2_phys, inner_ring_phy, plateOpSurface);

    // EDGE SURFACE
    G4MaterialPropertiesTable *edgeSurfaceMPT = new G4MaterialPropertiesTable();
    edgeSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    edgeSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.65);
    edgeSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.65);

    G4OpticalSurface *edgeOpSurface = new G4OpticalSurface("outerEdgeOpSurface");
    edgeOpSurface->SetType(dielectric_metal);
    edgeOpSurface->SetModel(glisur);
    edgeOpSurface->SetPolish(0.999);
    edgeOpSurface->SetMaterialPropertiesTable(edgeSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_outer_edge_opsurface", inner2_phys, outer_edge_phy, edgeOpSurface);
    new G4LogicalBorderSurface(GetName()+"_inner_edge_opsurface", inner2_phys, inner_edge_phy, edgeOpSurface);

    // CYLINDRICAL TUBE SURFACE
    G4MaterialPropertiesTable *tubeSurfaceMPT = new G4MaterialPropertiesTable();
    tubeSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    tubeSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.65);
    tubeSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.65);

    G4OpticalSurface *tubeOpSurface = new G4OpticalSurface("tubeOpSurface");
    tubeOpSurface->SetType(dielectric_metal);
    tubeOpSurface->SetModel(glisur);
    tubeOpSurface->SetPolish(0.999);
    tubeOpSurface->SetMaterialPropertiesTable(tubeSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_dynode_tube_opsurface", inner2_phys, tube_phy, tubeOpSurface);

    // GRID SURFACE
    G4MaterialPropertiesTable *gridSurfaceMPT = new G4MaterialPropertiesTable();
    gridSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    gridSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.);
    gridSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.);

    G4OpticalSurface *gridOpSurface = new G4OpticalSurface("gridOpSurface");
    gridOpSurface->SetType(dielectric_metal);
    gridOpSurface->SetModel(glisur);
    gridOpSurface->SetPolish(0.999);
    gridOpSurface->SetMaterialPropertiesTable(gridSurfaceMPT);

    new G4LogicalBorderSurface(GetName()+"_grid_opsurface", inner2_phys, grid_phy, gridOpSurface);

    // SHIELD SURFACE
    G4MaterialPropertiesTable *shieldSurfaceMPT = new G4MaterialPropertiesTable();
    shieldSurfaceMPT->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    shieldSurfaceMPT->AddEntry("REFLECTIVITY", 1.55*eV, 0.0);
    shieldSurfaceMPT->AddEntry("REFLECTIVITY", 15.5*eV, 0.0);

    G4OpticalSurface *shieldOpSurface = new G4OpticalSurface("shieldOpSurface");
    shieldOpSurface->SetType(dielectric_metal);
    shieldOpSurface->SetModel(glisur);
    shieldOpSurface->SetPolish(0.999);
    shieldOpSurface->SetMaterialPropertiesTable(shieldSurfaceMPT);
    
    new G4LogicalBorderSurface(GetName()+"_shield_opsurface", inner2_phys, shield_phy, shieldOpSurface);
}

/**

Current four volume geometry ~features two fake boundaries
(Pyrex/Pyrex and Vacuum/Vacuum) plus has one coincident face
and two nearly coincident: the 2nd Pyrex and inner1-Vacuum and inner2-Vacuum 
are separated by only 1e-3 mm):: 


     +---------------pmt-Pyrex----------------+
     |                                        |
     |                                        |
     |     +----------body-Pyrex--------+     |
     |     | +------------------------+ |     |
     |     | |                        | |     |
     |     | |                        | |     |
     |     | |        inner1-Vacuum   |-|     |
     |     | |                        |1e-3   |
     |     | |                        | |     |
     |     | +~~coincident~face~~~~~~~+ |     |
     |     | |                        | |     |
     |     | |                        | |     |
     |     | |        inner2-Vacuum   | |     |
     |     | |                        | |     |
     |     | |                        | |     |
     |     | +------------------------+ |     |
     |     +----------------------------+     |
     |                                        |
     |                                        |
     +----------------------------------------+


Q: When m_enable_optical_model=true is photocathode_logsurf doing anything ?
A: I think not, because body volume is handled by FastSim when ModelTrigger:true
   which will be the case for body<->inner1

   * so does this mean can set the mirror_logsurf for the entire PMT such 
     that ModelTrigger:false will get the same behaviour       


HMM: notice that the optical surface is not with the pmt-Pyrex but the body-Pyrex

* photocathode_logsurf1,2 : inner1_phys<->body_phys
* mirror_logsurf11,2 : inner2_phys<->body_phys

**/

void
HamamatsuR12860PMTManager::helper_make_optical_surface()
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
HamamatsuR12860PMTManager::helper_fast_sim()
{

    G4Region* body_region = new G4Region(this->GetName()+"_body_region");
    body_log->SetRegion(body_region);
    body_region->AddRootLogicalVolume(body_log);

    pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
                                                                   body_phys, body_region);

#ifdef PMTFASTSIM_STANDALONE
    std::cout 
        << "HamamatsuR12860PMTManager::helper_fast_sim" 
        << "  pmtOpticalModel " << pmtOpticalModel 
        << std::endl 
        ; 
#endif



#ifndef PMTFASTSIM_STANDALONE
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
    LogInfo << "Retrieving PMTSimParamSvc." << std::endl;
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
HamamatsuR12860PMTManager::helper_vis_attr()
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
HamamatsuR12860PMTManager::init_fast_cover() {
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

