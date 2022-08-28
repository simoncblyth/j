#ifndef LowerChimney_hh
#define LowerChimney_hh

#ifdef PMTSIM_STANDALONE
#include "IGeomManager.h"
#else
#include "SniperKernel/ToolBase.h"
#include "DetSimAlg/IDetElement.h"
#endif


#include "globals.hh"

class G4Box;
class G4Sphere;
class G4Tubs;
class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;

#ifdef PMTSIM_STANDALONE
class LowerChimney : public IGeomManager {
#else
class LowerChimney : public IDetElement,
                     public ToolBase{
#endif
public:
    G4LogicalVolume* getLV();

#ifdef PMTSIM_STANDALONE
#else
    bool inject(std::string motherName, IDetElement* other, IDetElementPos* pos);
#endif


    LowerChimney(const std::string& name);
    ~LowerChimney();


public:
     // debug interface
    G4LogicalVolume* getLV(const char* name); 
    G4PVPlacement*   getPV(const char* name);  
    G4VSolid*        getSolid(const char* name); 
    NP*              getValues(const char* prefix) ; 
    void dump(const char* msg) const ; 

private:

    void initMaterials();
//    void initVariables();

    void makeLowerChimneyLogicalAndPhysical();
    void setupLowerChimneyReflectorInCD();
	void makeNoShutterLowerChimneyLogicalAndPhysical();
//    void setupBlockerReflectorInCD();

 

private:

/////////
    G4VSolid*  solidLowerChimney;
    G4LogicalVolume* logicLowerChimney;

    G4VSolid*  solidLowerChimneyTyvek ;
    G4LogicalVolume* logicLowerChimneyTyvek;
    G4VPhysicalVolume* physiLowerChimneyTyvek;

    G4VSolid*  solidLowerChimneyAcrylic;
    G4LogicalVolume* logicLowerChimneyAcrylic;
    G4VPhysicalVolume* physiLowerChimneyAcrylic;

    G4VSolid*  solidLowerChimneySteel  ;
    G4LogicalVolume* logicLowerChimneySteel;
    G4VPhysicalVolume* physiLowerChimneySteel;

    G4VSolid*  solidLowerChimneyLS     ;
    G4LogicalVolume* logicLowerChimneyLS;
    G4VPhysicalVolume* physiLowerChimneyLS;

    G4VSolid*  solidLowerChimneyBlocker;
    G4LogicalVolume* logicLowerChimneyBlocker;
    G4VPhysicalVolume* physiLowerChimneyBlocker;
///////////////////////



private:

    G4Material* LS;           // Target material
    G4Material* Air;         
    G4Material* Acrylic;         
    G4Material* Water;
    G4Material* Tyvek;
    G4Material* Steel;
private:
    double m_Blocker2Btm;
    double m_reflectivity;
private:
    // properties
 //   bool m_use_chimney;
//    bool m_upper_chimney;
    bool m_lower_chimney;
    bool m_use_shutter;
};

#endif
