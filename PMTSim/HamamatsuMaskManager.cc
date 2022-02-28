
#include "HamamatsuMaskManager.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Ellipsoid.hh"
#include "G4Polycone.hh"
#include "G4VisAttributes.hh"
#include "G4RegionStore.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"


#ifdef PMTSIM_STANDALONE

#include <iostream>
#include <iomanip>

#define LogInfo  std::cout 
#define LogError std::cerr 

#else
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/ToolFactory.h"
DECLARE_TOOL(HamamatsuMaskManager);
#endif

using namespace CLHEP;

HamamatsuMaskManager::HamamatsuMaskManager(const std::string& name)
    :
#ifdef PMTSIM_STANDALONE
    m_objName(name),
#else
    ToolBase(name),
#endif
     logicMaskTail(NULL), physiMaskTail(NULL)
    , LAB(NULL), Acrylic(NULL), Water(NULL), AcrylicMask(NULL), Steel(NULL)
{
#ifdef PMTSIM_STANDALONE
    m_buffer_material = "Water" ; 
    htop_thickness=8.*mm ; 
    htop_gap=2.*mm ;
    requator_thickness=8.*mm ; 
    requator_gap=2.*mm ;
    m_useRealSurface=true ; 
    m_useRealMaskTail=true ; 
    m_useMaskTailOpSurface=true ; 
#else
    declProp("BufferMaterial", m_buffer_material = "Water");
    declProp("TopThickness", htop_thickness=8.*mm);
    declProp("TopGap", htop_gap=2.*mm); // gap between PMT and Mask at top

    declProp("EquatorThickness", requator_thickness=8.*mm); // thickness at equator
    declProp("EquatorGap", requator_gap=2.*mm); // gap between PMT and Mask at equator

    declProp("UseRealSurface", m_useRealSurface=true);
    declProp("UseRealMaskTail", m_useRealMaskTail=true);
    declProp("UseMaskTailOpSurface", m_useMaskTailOpSurface=true);

#endif
    logicMaskVirtual = 0;

    MAGIC_virtual_thickness = 0.05*mm;
}

HamamatsuMaskManager::~HamamatsuMaskManager() {

}

G4LogicalVolume* 
HamamatsuMaskManager::getLV() {
    if (logicMaskVirtual) {
        return logicMaskVirtual;
    }
    initVariables();
    initMaterials();

    makeMaskOutLogical();

    makeMaskLogical();
    makeMaskPhysical();

    if (m_useRealMaskTail) {
        makeMaskTailLogical();
        makeMaskTailPhysical();
    }

    if (m_useRealMaskTail and m_useMaskTailOpSurface) {
        makeMaskTailOpSurface();
    }

    // logicMaskVirtual = logicMask;
    
    return logicMaskVirtual;
}

G4double
HamamatsuMaskManager::GetPMTRadius() {
    return mask_radiu_virtual;
}

G4double
HamamatsuMaskManager::GetPMTHeight() {
    return height_virtual;
}

G4double
HamamatsuMaskManager::GetZEquator() {
    return mask_radiu_virtual;
}
#ifdef PMTSIM_STANDALONE
#else
bool
HamamatsuMaskManager::inject(std::string motherName, IDetElement* other, IDetElementPos* /*pos*/) {
    // initialize self.
    getLV();
    // Get the mother volume in current DetElem.
    G4LogicalVolume* mothervol = 0;
    if ( motherName == "lMaskVirtual" ) {
        mothervol = logicMaskVirtual;
    }
    if (not mothervol) {
        // don't find the volume.
        LogError << "Can't find the mother volume " << motherName << std::endl;
        return false;
    }

    // retrieve the daughter's LV
    inner_pmt = dynamic_cast<IPMTElement*>(other);
    G4LogicalVolume* daughtervol = other->getLV();

    if (not daughtervol) {
        LogError << "Can't find the daughter volume " << std::endl;
        return false;
    }

    int copyno = 0;
    new G4PVPlacement(0,
            G4ThreeVector(0,0,0) ,
            daughtervol,
            daughtervol->GetName()+"_phys",
            mothervol,
            false,
            copyno++
            );

    G4cout<<" Mask = "<<copyno<<G4endl;
    
    return true;
}
#endif

void
HamamatsuMaskManager::initVariables() {
/* 
 * NOTE: The virtual mask outside is to speedup detector construction

out --_
MASK    htop_thickness
 in --_
    **_ htop_gap            gap 
PMT ^                        ^ thickness
    |                    PMT | MASK
   H = 184                  * \  \
    |                        * \  \
---- EQUATOR -- R = 254.mm -->* |  | BELOW is Tubs
    |                        *^ |  | ^
    |                       * | |  | |
H = 523-184               **  | |  | |
    |                   **    | |  | |
......................................
......................................
PMT |     |               H_in  |  | H_out
    v_____|                   | |  | |
gap                           | |  | |
    __________________________v_|  | |
    _______________________________| v
*/     



    mask_radiu_in = 254.*mm + requator_gap;
    mask_radiu_out = mask_radiu_in + requator_thickness;
    mask_radiu_virtual = mask_radiu_out + MAGIC_virtual_thickness;
    htop_in = 190.*mm + htop_gap;
    htop_out = htop_in + htop_thickness;

    height_in = (640.-190.)*mm + 5.*mm;
    height_out = height_in + 10*mm;
    height_virtual = height_out + MAGIC_virtual_thickness;
    
    gap = 0.1 *mm;

    // Reduce the height of PMT
    // Tao Lin, 09 Aug 2021
    if (m_useRealSurface) {
        const double radInnerWaterRealSurface = 19.629*m;
        const double m_pmt_r = 254.*mm + 1.*cm;
        double pmt_eq_to_bottom = sqrt(radInnerWaterRealSurface*radInnerWaterRealSurface
                                       -m_pmt_r*m_pmt_r) - 19.434*m; // at z equator

        // avoid the overlap between PMT tail and innerWater
        const double safety_distance = 1.*cm;
        pmt_eq_to_bottom -= safety_distance;

        double h_to_bottom = pmt_eq_to_bottom;
        LogInfo << "Option RealSurface is enabled in Central Detector. "
                << " Reduce the height_in from "
                << height_in << " to " << h_to_bottom
                << " Reduce the height_out from "
                << height_out << " to " << h_to_bottom
                << std::endl;
        height_in = h_to_bottom;
        height_out = h_to_bottom;
        height_virtual = h_to_bottom;
    }

    // if the real mask tail is used, then the height of the tube need to be further reduced.
    // query the h_below_equator from the ParamRealMaskHead.
    // Tao Lin, 10 Aug 2021
    if (m_useRealMaskTail) {

        if (m_useRealSurface) {
            LogInfo << "Reduce the paramRealMaskTail.height from "
                    << paramRealMaskTail.height
                    << " to " << (height_virtual - paramRealMaskHead.h_below_equator)
                    << std::endl;
            paramRealMaskTail.height = height_virtual - paramRealMaskHead.h_below_equator;
        }

        if (paramRealMaskHead.h_below_equator < height_in) {
            LogInfo << "Switch height_in from " << height_in
                    << " to " << paramRealMaskHead.h_below_equator
                    << std::endl;
            height_in = paramRealMaskHead.h_below_equator;
        }
        if (paramRealMaskHead.h_below_equator < height_out) {
            LogInfo << "Switch height_out from " << height_out
                    << " to " << paramRealMaskHead.h_below_equator
                    << std::endl;
            height_out = paramRealMaskHead.h_below_equator;
        }


    }

}

void 
HamamatsuMaskManager::initMaterials() {
    LAB = G4Material::GetMaterial("LAB");
    Water = G4Material::GetMaterial("Water");
    Acrylic = G4Material::GetMaterial("Acrylic");
    AcrylicMask = G4Material::GetMaterial("AcrylicMask");
    Steel = G4Material::GetMaterial("CDReflectorSteel");
}

void
HamamatsuMaskManager::makeMaskOutLogical() {
    // BELOW is using 4 zplanes
    
    G4double zPlane[] = {
                        -height_virtual,
                        0, // at equator
                        htop_out/2, // at half H_front
                        htop_out + MAGIC_virtual_thickness
                        };
    G4double rInner[] = {0.,
                         0., // at equator
                         0., // at half H_front
                         0.};
    G4double rOuter[] = {mask_radiu_virtual,
                         mask_radiu_virtual, // at equator
                         mask_radiu_virtual, // at half H_front
                         mask_radiu_virtual/2}; // reduce the front R


    SolidMaskVirtual = new G4Polycone(
				objName()+"sMask_virtual",
                                0,
                                360*deg,
                                // 2,
                                4,
                                zPlane,
                                rInner,
                                rOuter
                                );

    G4Material* BufferMaterials = Water;
    if (m_buffer_material=="LAB") {
        BufferMaterials = LAB;
    }
 
    logicMaskVirtual = new G4LogicalVolume(
            SolidMaskVirtual, 
            BufferMaterials, 
            objName()+"lMaskVirtual",
            0,
            0,
            0);
    G4cout<< " BufferMaterial = "<< BufferMaterials << G4endl; 
    G4VisAttributes* maskout_visatt = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
    maskout_visatt -> SetForceWireframe(true);  
    maskout_visatt -> SetForceAuxEdgeVisible(true);
    maskout_visatt -> SetForceSolid(true);
    maskout_visatt -> SetForceLineSegmentsPerCircle(64);
    // maskout_visatt -> SetVisibility(false);
    logicMaskVirtual -> SetVisAttributes(maskout_visatt);
}


/**
HamamatsuMaskManager::makeMaskLogical
---------------------------------------

::


      +hz   +-----------+                     +-----------+            zoff + new_hz 
            |           |                     |           |
            |           |                     |           |
            |           |                     |           |
            |           |                     |           |
            |           |                     |           |
      0     +-----------+ - - - - - - - - - - - - - - - - - - -          
            |           |                     |___________| _ _ _ _ _ _ zoff _ _ _ _ _ _ 
            |           |                     |           |
            |           |                     |           |
            |           |                     |           |
            |           |                     |           |
      -hz   +-----------+ - - - - - - - - - - - - - - - - - - -
                                              |           | 
                                              |           |
      -hz - uncoincide                        +~~~~~~~~~~~+            zoff - new_hz

      (uncoincide +ve)

Add and subtract the line equations::

       +hz                = zoff + new_hz 
       -hz - uncoincide   = zoff - new_hz

           -uncoincide    = 2*zoff      => zoff = -uncoincide/2 

         2*hz + uncoincide = 2*new_hz   => new_hz = hz + uncoincide/2        



Both Top_in G4Ellipsoid and Bottom_in G4Tubs extend down to the same coincident Z edge. 
Hence need to extend them both downwards.   

For the G4Tubs that means increasing hz to new_hz = hz + uncoincide/2 and changing zoff by -uncoincide/2 

For the G4Ellipsoid that means extending downwards the pzBottomCut from -height_out to -(height_out + uncoincide)


**/

void
HamamatsuMaskManager::makeMaskLogical() {
    
    /* 
    G4Sphere*  Top_out = new G4Sphere(
            "Top_Sphere",
            0*mm, 
            mask_radiu_out, 
            0*deg,
            360*deg, 
            0*deg,
            90*deg 
            );
    */
    Top_out = new G4Ellipsoid(
            objName()+"Top_Sphere",
            mask_radiu_out, // pxSemiAxis
            mask_radiu_out, // pySemiAxis
            htop_out,  // pzSemiAxis
            -height_out, // XXX, // pzBottomCut
            htop_out // XXX  // pzTopCut
            );

    Bottom_out = new G4Tubs(
            objName()+"Bottom_Tube",
            0*mm,   
            mask_radiu_out,  
            height_out/2,  
            0*deg, 
            360*deg);

    Mask_out = new G4UnionSolid
        (objName()+"sMask_out",
         Top_out ,
         Bottom_out ,
         0,
         G4ThreeVector(0,0,-height_out/2 + gap)    ) ;

    /* 
    G4Sphere*  Top_in = new G4Sphere(
            "Top_Sphere_in",
            0*mm, 
            mask_radiu_in, 
            0*deg,
            360*deg, 
            0*deg,
            90*deg 
            );
    */
    G4double uncoincide_z = 1.*mm ;  
    Top_in = new G4Ellipsoid(
            objName()+"Top_Sphere_in",
            mask_radiu_in, // pxSemiAxis
            mask_radiu_in, // pySemiAxis
            htop_in,  // pzSemiAxis
            -(height_in + uncoincide_z)  , // XXX, // pzBottomCut
            htop_in // XXX  // pzTopCut
            );


    Bottom_in = new G4Tubs(
            objName()+"Bottom_Tube_in",
            0*mm,   
            mask_radiu_in,  
            height_in/2 + uncoincide_z/2 ,  
            0*deg, 
            360*deg);


    Mask_in = new G4UnionSolid
        (objName()+"sMask_in",
         Top_in ,
         Bottom_in ,
         0,
         G4ThreeVector(0,0,-height_in/2 + gap - uncoincide_z/2 )    ) ;


#ifdef PMTSIM_STANDALONE
    std::cout << "HamamatsuMaskManager::makeMaskLogical objName [" << objName() << "]" << std::endl ; 
    std::cout 
        << "Top_in Ellipsoid "
        << " pzSemiAxis: htop_in "     << std::fixed << std::setw(10) << std::setprecision(4) << htop_in  
        << " pzBottomCut: -height_in " << std::fixed << std::setw(10) << std::setprecision(4) << -height_in
        << " pzTopCut: htop_in "       << std::fixed << std::setw(10) << std::setprecision(4) << htop_in
        << std::endl 
        ;
    std::cout 
        << "Bottom_in Tubs "
        << " height_in/2 "     << std::fixed << std::setw(10) << std::setprecision(4) << height_in/2  
        << std::endl 
        ;
    std::cout
        << "Mask_in Union "
        << " -height_in/2 + gap " << std::fixed << std::setw(10) << std::setprecision(4) << -height_in/2 + gap 
        << " -height_in/2       " << std::fixed << std::setw(10) << std::setprecision(4) << -height_in/2
        << " gap " << std::fixed << std::setw(10) << std::setprecision(4) << gap 
        << std::endl 
        ;
#endif

    solidMask = new G4SubtractionSolid(
            objName()+"sMask",
            Mask_out,
            Mask_in,
            0,
            G4ThreeVector(0,0,0)
            );
    
    logicMask = new G4LogicalVolume(
            solidMask, 
            //Acrylic,
            AcrylicMask, 
            objName()+"lMask",
            0,
            0,
            0);
    G4VisAttributes* mask_visatt = new G4VisAttributes(G4Colour(1.0, 0, 1.0));
    mask_visatt -> SetForceWireframe(true);  
    mask_visatt -> SetForceAuxEdgeVisible(true);
    //mask_visatt -> SetForceSolid(true);
    //mask_visatt -> SetForceLineSegmentsPerCircle(4);
    logicMask -> SetVisAttributes(mask_visatt);
}




void
HamamatsuMaskManager::makeMaskPhysical() {
#ifdef PMTSIM_STANDALONE
    std::cout << "HamamatsuMaskManager::makeMaskPhysical objName [" << objName() << "]" << std::endl ; 
#endif
    physiMask = new G4PVPlacement(0,              // no rotation
            G4ThreeVector(0,0,0), // at (x,y,z)
            logicMask,    // its logical volume 
            objName()+"pMask",       // its name
            logicMaskVirtual,  // its mother  volume
            false,           // no boolean operations
            0);              // no particular field
}


/**
HamamatsuMaskManager::makeMaskTailLogical
-------------------------------------------

MaskTail coincidence spurious intersects happen 
across the opening of the bowl. 

   +-+ . . . . . . . .+-+ 
    \ \              / /
     \ \            / /
      \ \__________/ / 
       \____________/



To avoid coincident faces in the subtraction 
need to expand "Tail_inner_I_Tube" (hmskTailInnerITube) G4Tubs 
upwards without changing the position of its of lower edge.
Hence increase the half-size in Z from *hz* to *new_hz* and 
simultaneously shifting upwards by the same amount (*zoff*) 
to keep the lower edge at same z position::


       +hz + uncoincide - - - - - - - +~~~~~~~~~+ - -    zoff + new_hz  - - -
                                      |         |
                                      |         |
       +hz  +---------+ - - - - - - - | - - - - | - - - - - - - - - - - - - -
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |               |_________|        zoff 
            |         |               |         |
        0 --|---------| - - - - - - - - - - - - - - - - - - - - - - - - - - -
            |         |               |         |
            |         |               |         |
            |         |               |         |                                
            |         |               |         |
            |         |               |         |
       -hz  +---------+ - - - - - - - +---------+ - - -  zoff - new_hz  - - -


Add the line equations::

      hz + uncoincide = zoff + new_hz

      -hz             = zoff - new_hz 

           => uncoincide = 2*zoff       =>   zoff = uncoincide/2


Subtract the line equations::
     
        2 hz + uncoincide = 2*new_hz    ==>  new_hz = hz + uncoincide/2 


+-----------------------------+------------------------------+--------------------------------------------------------------------------+
|  GEOM                       |  Member                      | Note                                                                     |
+=============================+==============================+==========================================================================+
| hmskTailOuterIEllipsoid     |  Tail_outer_I_Ellipsoid      |  -Z : less than hemi-ellipsoid                                           |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailOuterITube          |  Tail_outer_I_Tube           |  thin disc cylinder                                                      |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailOuterI              |  Tail_outer_I                |  less than hemi-ellipsoid union with the disc making lip on top          |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailOuterIITube         |  Tail_outer_II_Tube          |  substantial squat cylinder, forms the base                              |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailOuter               |  Tail_outer                  |  solid bowl with lip and squat cylinder base                             |       
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailInner               |  Tail_inner                  |  looks the same as the Outer                                             |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskTailInnerITube          |  Tail_inner_I_Tube           |  thin disc cylinder, upper edge was coincident                           |
+-----------------------------+------------------------------+--------------------------------------------------------------------------+
| hmskSolidMaskTail           |  solidMaskTail               |  hollowed out bowl, correct way up                                       | 
+-----------------------------+------------------------------+--------------------------------------------------------------------------+

**/


void
HamamatsuMaskManager::makeMaskTailLogical() {
    // outer

    Tail_outer_I_Ellipsoid = new G4Ellipsoid(
            objName()+"Tail_outer_PartI_Ellipsoid",
            mask_radiu_out, // pxSemiAxis
            mask_radiu_out, // pySemiAxis
            htop_out,  // pzSemiAxis
            -(height_out+paramRealMaskTail.height), // pzBottomCut (TODO)
            -height_out // pzTopCut
            );

    Tail_outer_I_Tube = new G4Tubs(
            objName()+"Tail_outer_PartI_Tube",
            0*mm,   
            mask_radiu_out,  
            paramRealMaskTail.edge_height/2,  
            0*deg, 
            360*deg);

    Tail_outer_I = new G4UnionSolid
        (objName()+"Tail_outer_PartI",
         Tail_outer_I_Ellipsoid ,
         Tail_outer_I_Tube ,
         0,
         G4ThreeVector(0,0,-(height_out+paramRealMaskTail.edge_height/2))) ;

    Tail_outer_II_Tube = new G4Tubs
        (objName()+"Tail_outer_PartII",
         0*mm,
         paramRealMaskTail.r2,
         paramRealMaskTail.height/2,
         0*deg,
         360*deg);
                                           
    Tail_outer = new G4UnionSolid
        (objName()+"Tail_outer",
         Tail_outer_I,
         Tail_outer_II_Tube,
         0,
         G4ThreeVector(0.0, 0.0, -(height_out+paramRealMaskTail.height/2)));


    // inner

    Tail_inner_I_Ellipsoid = new G4Ellipsoid(
            objName()+"Tail_inner_PartI_Ellipsoid",
            mask_radiu_in, // pxSemiAxis
            mask_radiu_in, // pySemiAxis
            htop_in,  // pzSemiAxis
            -(height_out+paramRealMaskTail.height-htop_thickness), // pzBottomCut (TODO)
            -height_out // pzTopCut
            );

    G4double uncoincide_inner_z = 1.0*mm ;  // increase ZHalfLength by uncoincide_inner_z/2

    Tail_inner_I_Tube = new G4Tubs(
            objName()+"Tail_inner_PartI_Tube",
            0*mm,   
            mask_radiu_in,  
            paramRealMaskTail.edge_height/2 + uncoincide_inner_z/2 ,  
            0*deg, 
            360*deg);

    Tail_inner_I = new G4UnionSolid
        (objName()+"Tail_inner_PartI",
         Tail_inner_I_Ellipsoid ,
         Tail_inner_I_Tube ,
         0,
         G4ThreeVector(0,0,-(height_out+paramRealMaskTail.edge_height/2) + uncoincide_inner_z/2 )) ;

    // shift upwards by uncoincide_inner_z/2 to keep same lower edge position
    // despite the increased ZHalfLemgth 


#ifdef PMTSIM_STANDALONE
    if(false)
    {
        std::cout << "HamamatsuMaskManager::makeMaskTailLogical objName " << objName() << std::endl ; 
        std::cout 
             << " Tail_inner_I_Ellipsoid "
             << " htop_in " << std::fixed << std::setw(10) << std::setprecision(4) << htop_in 
             << " pzBottomCut: -(height_out+paramRealMaskTail.height-htop_thickness) " << std::fixed << std::setw(10) << std::setprecision(4) << -(height_out+paramRealMaskTail.height-htop_thickness)
             << " pzTopCut: -height_out "                                           << std::fixed << std::setw(10) << std::setprecision(4) << -height_out
             << std::endl 
             ; 
        std::cout 
             << " Tail_inner_PartI_Tube "
             << " hz: paramRealMaskTail.edge_height/2 " << std::fixed << std::setw(10) << std::setprecision(4) << paramRealMaskTail.edge_height/2 
             << std::endl 
             ;
    }
#endif


    Tail_inner_II_Tube = new G4Tubs
        (objName()+"Tail_inner_PartII",
         0*mm,
         paramRealMaskTail.r2 - requator_thickness,
         (paramRealMaskTail.height-htop_thickness)/2,
         0*deg,
         360*deg);
                                           
    Tail_inner = new G4UnionSolid
        (objName()+"Tail_inner",
         Tail_inner_I,
         Tail_inner_II_Tube,
         0,
         G4ThreeVector(0.0, 0.0, -(height_out+(paramRealMaskTail.height-htop_thickness)/2)));

    // outer - inner
    solidMaskTail = new G4SubtractionSolid(
            objName()+"Tail",
            Tail_outer,
            Tail_inner,
            0,
            G4ThreeVector(0,0,0)
            );

    // create logical volume
    logicMaskTail = new G4LogicalVolume(
            solidMaskTail, 
            Steel,
            objName()+"lMaskTail",
            0,
            0,
            0);
    G4VisAttributes* mask_visatt = new G4VisAttributes(G4Colour(113./255, 121./255, 126./255));
    mask_visatt -> SetForceWireframe(true);  
    mask_visatt -> SetForceAuxEdgeVisible(true);
    //mask_visatt -> SetForceSolid(true);
    //mask_visatt -> SetForceLineSegmentsPerCircle(4);
    logicMaskTail -> SetVisAttributes(mask_visatt);

}

void
HamamatsuMaskManager::makeMaskTailPhysical() {
    physiMaskTail = new G4PVPlacement(0,                    // no rotation
                                      G4ThreeVector(0,0,0), // at (x,y,z)
                                      logicMaskTail,        // its logical volume 
                                      objName()+"pMaskTail",// its name
                                      logicMaskVirtual,     // its mother  volume
                                      false,                // no boolean operations
                                      0);                   // no particular field
}

void
HamamatsuMaskManager::makeMaskTailOpSurface(){
    G4OpticalSurface* mask_optical_surface = new G4OpticalSurface("opHamamatsuMask");
    mask_optical_surface->SetMaterialPropertiesTable(Steel->GetMaterialPropertiesTable());
    mask_optical_surface->SetModel(unified);
    mask_optical_surface->SetType(dielectric_metal);
    mask_optical_surface->SetFinish(ground);
    mask_optical_surface->SetSigmaAlpha(0.2);

    new G4LogicalSkinSurface("HamamatsuMaskOpticalSurface", logicMaskTail, mask_optical_surface);
}

#ifdef PMTSIM_STANDALONE
#else
G4ThreeVector
HamamatsuMaskManager::GetPosInPMT() {
    G4ThreeVector pos;
    if (inner_pmt) {
        pos = inner_pmt->GetPosInPMT();
    }
    return pos;
}
#endif


G4VSolid* HamamatsuMaskManager::getSolid(const char* name)
{
    if (logicMaskVirtual == nullptr ) 
    {
        std::cout << "HamamatsuMaskManager::getSolid booting with getLV " << name << std::endl ;  
        getLV(); 
    }

    G4VSolid* solid = nullptr ; 

    // [ makeMaskLogical
    if(strcmp(name, "TopOut") == 0 )     solid = Top_out ; 
    if(strcmp(name, "BottomOut") == 0 )  solid = Bottom_out ; 
    if(strcmp(name, "MaskOut") == 0 )    solid = Mask_out ; 
    if(strcmp(name, "TopIn") == 0 )      solid = Top_in ; 
    if(strcmp(name, "BottomIn") == 0 )   solid = Bottom_in ; 
    if(strcmp(name, "MaskIn") == 0 )     solid = Mask_in ; 
    if(strcmp(name, "SolidMask") == 0 )  solid = solidMask ; 
    // ] makeMaskLogical


    // [ makeMaskTailLogical
    if(strcmp(name,"TailOuterIEllipsoid") == 0 ) solid = Tail_outer_I_Ellipsoid  ;
    if(strcmp(name,"TailOuterITube") == 0 )      solid = Tail_outer_I_Tube ; 
    if(strcmp(name,"TailOuterI") == 0 )          solid = Tail_outer_I ; 
    if(strcmp(name,"TailOuterIITube") == 0 )     solid = Tail_outer_II_Tube ;  
    if(strcmp(name,"TailOuter") == 0 )           solid = Tail_outer ; 
    if(strcmp(name,"TailInnerIEllipsoid") == 0 ) solid = Tail_inner_I_Ellipsoid ; 
    if(strcmp(name,"TailInnerITube") == 0 )      solid = Tail_inner_I_Tube ; 
    if(strcmp(name,"TailInnerI") == 0 )          solid = Tail_inner_I ; 
    if(strcmp(name,"TailInnerIITube") == 0 )     solid = Tail_inner_II_Tube ; 
    if(strcmp(name,"TailInner") == 0 )           solid = Tail_inner ; 
    if(strcmp(name,"SolidMaskTail") == 0 )       solid = solidMaskTail ; 
    // ] makeMaskTailLogical
 
    return solid  ; 
}
G4LogicalVolume* HamamatsuMaskManager::getLV(const char* name)
{
    G4LogicalVolume* lv = nullptr ; 
    if(strcmp(name, "LogicMask") == 0 )     lv = logicMask ;      // makeMaskLogical
    if(strcmp(name, "LogicMaskTail") == 0 ) lv = logicMaskTail ;  // makeMaskTailLogical
    return lv ; 
}
G4PVPlacement*   HamamatsuMaskManager::getPV(const char* name)
{
    G4PVPlacement* pv = nullptr ;  
    if( strcmp(name, "PhysiMask") == 0 )     pv = dynamic_cast<G4PVPlacement*>(physiMask) ;     // makeMaskPhysical
    if( strcmp(name, "PhysiMaskTail") == 0 ) pv = dynamic_cast<G4PVPlacement*>(physiMaskTail) ; // makeMaskTailPhysical
    return pv ; 
}
