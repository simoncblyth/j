#ifndef HamamatsuMaskManager_hh
#define HamamatsuMaskManager_hh

/*
 * This mask is designed for NNVT MCT-PMT.
 */

#ifdef PMTSIM_STANDALONE
#include "IGeomManager.h"
#include "G4SystemOfUnits.hh"
#else
#include "SniperKernel/ToolBase.h"
#include "DetSimAlg/IPMTElement.h"
#endif

#include "G4ThreeVector.hh"
#include "globals.hh"

class G4VSolid;
class G4Box;
class G4Sphere;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4PVPlacement ; 

#ifdef PMTSIM_STANDALONE
#include "PMTSIM_API_EXPORT.hh"
class PMTSIM_API HamamatsuMaskManager : public IGeomManager  {
#else

class HamamatsuMaskManager : public IPMTElement,
                             public ToolBase{
#endif
public:
    G4LogicalVolume* getLV();
    G4double GetPMTRadius();
    G4double GetPMTHeight();
    G4double GetZEquator();

#ifdef PMTSIM_STANDALONE
    const std::string& objName() { return m_objName; }
#else
    G4ThreeVector GetPosInPMT();
    bool inject(std::string motherName, IDetElement* other, IDetElementPos* pos);
#endif

    HamamatsuMaskManager(const std::string& name);
#ifdef PMTSIM_STANDALONE
    virtual ~HamamatsuMaskManager();
#else
    ~HamamatsuMaskManager();
#endif

    // debug interface
    G4LogicalVolume* getLV(const char* name);
    G4PVPlacement*   getPV(const char* name);
    G4VSolid*        getSolid(const char* name);
    NP*              getValues(const char* prefix); 

private:

    void initMaterials();
    void initVariables();

    // + WP: Water Pool
    void makeMaskOutLogical();

    void makeMaskLogical();
    void makeMaskPhysical();

    void makeMaskTailLogical();
    void makeMaskTailPhysical();
    void makeMaskTailOpSurface();

private:

#ifdef PMTSIM_STANDALONE
    const std::string& m_objName;
#endif
    
    G4VSolid*           Top_Virtual ;   
    G4VSolid*           Bottom_Virtual; 
    G4VSolid*           Mask_Virtual;   
    G4VSolid*           SolidMaskVirtual;   
    G4LogicalVolume*    logicMaskVirtual;
  
    // [  makeMaskLogical
    G4VSolid*           Top_out ;   
    G4VSolid*           Bottom_out;  
    G4VSolid*           Mask_out;   
    
    G4VSolid*           Top_in ;   
    G4VSolid*           Bottom_in;   
    G4VSolid*           Mask_in;   
    G4VSolid*           solidMask;   
    
    G4LogicalVolume*    logicMask;   
    // ]  makeMaskLogical


    // [ makeMaskPhysical
    G4VPhysicalVolume*  physiMask;   
    // ] makeMaskPhysical


    // [ makeMaskTailLogical
    G4VSolid* Tail_outer_I_Ellipsoid ;
    G4VSolid* Tail_outer_I_Tube ;
    G4VSolid* Tail_outer_I  ;
    G4VSolid* Tail_outer_II_Tube ; 
    G4VSolid* Tail_outer ; 
    G4VSolid* Tail_inner_I_Ellipsoid ; 
    G4VSolid* Tail_inner_I_Tube ; 
    G4VSolid* Tail_inner_I ; 
    G4VSolid* Tail_inner_II_Tube ; 
    G4VSolid* Tail_inner ; 
    G4VSolid* solidMaskTail ; 
    // ] makeMaskTailLogical





    G4LogicalVolume*    logicMaskTail;   
    G4VPhysicalVolume*  physiMaskTail;   

private:
    G4Material* LAB;           
    G4Material* Acrylic;         
    G4Material* Water;
    G4Material* AcrylicMask;
    G4Material* Steel;
private:
    double mask_radiu_in;
    double mask_radiu_out;
    double mask_radiu_virtual;
    double htop_in;
    double htop_out;
    double htop_thickness;
    double htop_gap;
    double requator_thickness;
    double requator_gap;
    double height_virtual;
    double height_in;
    double height_out;
    double gap;

    double MAGIC_virtual_thickness;

    std::string m_buffer_material;

#ifdef PMTSIM_STANDALONE
#else
    IPMTElement* inner_pmt;
#endif

private:
    /*
     If m_useRealSurface is true, the PMT should insert into the surface.
     In order to optimize the speed, just reduce the size of the PMT.
    
            |    -
            |  /   \
        ------- P M T
        ------- 19.434m
            |  \   /
            |    -
          Tyvek  |
         19.629m
    */
    bool m_useRealSurface;

    /*
     If m_useRealMaskTail is true, the tail of the mask is not a simple tube.
     the shape will be close to the PMT. 
    
           - - -
         /       \
         |       |  <--- this head part is the acrylic
         -\     /-  <--- this tail part is the steel      -- r1
            | |                                           -- r2
    */

    struct ParamRealMaskHead {
        double h_top_equator;   // from top to equator
        double h_below_equator; // below the equator
        double r;               // radius at the equator

        ParamRealMaskHead() {
            h_top_equator = 200.*CLHEP::mm; // inner of the mask
            h_below_equator = 40.*CLHEP::mm;
            r = (254.+10.)*CLHEP::mm;
        }
    } paramRealMaskHead;

    struct ParamRealMaskTail {
        double edge_height; // the top part
        double dummy_height; // in the real design, the bottom of PMT is at outside of mask.
                             // use this dummy_height to let mask contain the PMT.
        double height; // from top to bottom, including the dummy_height
        double r1;
        double dummy_extra_r2; // to avoid the overlapping, increase a bit
        double r2;

        ParamRealMaskTail() {
            edge_height = 0.3*CLHEP::mm;
            dummy_height = 30*CLHEP::mm;
            height = 320.*CLHEP::mm + dummy_height;
            r1 = 265.*CLHEP::mm;
            
            dummy_extra_r2 = 15.*CLHEP::mm;
            r2 = 134.*CLHEP::mm+dummy_extra_r2;
        }
    } paramRealMaskTail;

    bool m_useRealMaskTail;
    bool m_useMaskTailOpSurface;

};

#endif
