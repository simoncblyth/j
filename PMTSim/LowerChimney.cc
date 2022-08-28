
#ifdef PMTSIM_STANDALONE
#else
#include <boost/python.hpp>
#endif

//#include "Dimensions.hh"
#include "LowerChimney.hh"
#include "LowerChimneyMaker.hh"
#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"

using namespace CLHEP;

#ifdef PMTSIM_STANDALONE

#else

#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/ToolFactory.h"
#include "SniperKernel/SniperLog.h"

#include "DetSimAlg/DetSimAlg.h"
#include "DetSimAlg/IDetElement.h"

DECLARE_TOOL(LowerChimney);

#endif



LowerChimney::LowerChimney(const std::string& name)
    :
#ifdef PMTSIM_STANDALONE
#else
    ToolBase(name),
#endif
solidLowerChimney(0),        logicLowerChimney(0),
solidLowerChimneyTyvek(0),    logicLowerChimneyTyvek(0),    physiLowerChimneyTyvek(0),
solidLowerChimneyAcrylic(0), logicLowerChimneyAcrylic(0),   physiLowerChimneyAcrylic(0),
solidLowerChimneySteel(0),   logicLowerChimneySteel(0),     physiLowerChimneySteel(0),
solidLowerChimneyLS(0),      logicLowerChimneyLS(0),        physiLowerChimneyLS(0),
solidLowerChimneyBlocker(0), logicLowerChimneyBlocker(0),   physiLowerChimneyBlocker(0),
LS(0), Air(0), Acrylic(0), Water(0), Tyvek(0), Steel(0)
{
  //  declProp("UseLowerChimney", m_lower_chimney=false );
  //  declProp("BlockerZ", m_Blocker2Btm=0);
  //  declProp("Reflectivity", m_reflectivity=0 );

#ifdef PMTSIM_STANDALONE
    m_lower_chimney=true ; 

    //m_use_shutter=false ;    // HUH: the default makes no solids or volumes
    m_use_shutter=true ; 

    m_Blocker2Btm=0.3 ;
    m_reflectivity=0.4 ;
#else
    declProp("UseLowerChimney", m_lower_chimney=true);//Default: Chimney is enabled.
    declProp("UseShutter", m_use_shutter=false);//Default: Chimney is enabled.
    declProp("BlockerZ", m_Blocker2Btm=0.3);  // Default: Blocker is 0.3m from the top of the CD
    declProp("Reflectivity", m_reflectivity=0.4 );// Default: Reflectivity of the inner chimney is 0.1 
#endif

}

LowerChimney::~LowerChimney() {

}

G4LogicalVolume* LowerChimney::getLV(const char* name)
{
   G4LogicalVolume* lv = nullptr ; 
   if(strcmp(name, "logicLowerChimney") == 0 )          lv = logicLowerChimney ; 
   if(strcmp(name, "logicLowerChimneyTyvek") == 0 )     lv = logicLowerChimneyTyvek ; 
   if(strcmp(name, "logicLowerChimneyAcrylic") == 0 )   lv = logicLowerChimneyAcrylic ; 
   if(strcmp(name, "logicLowerChimneySteel") == 0 )     lv = logicLowerChimneySteel ; 
   if(strcmp(name, "logicLowerChimneyLS") == 0 )        lv = logicLowerChimneyLS ; 
   if(strcmp(name, "logicLowerChimneyBlocker") == 0 )   lv = logicLowerChimneyBlocker ; 
   if( lv == nullptr ) dump("LowerChimney::getLV FAILED"); 
   return lv ; 
}
G4PVPlacement*  LowerChimney::getPV(const char* name)
{
   G4VPhysicalVolume* pv = nullptr ; 
   if(strcmp(name, "physiLowerChimney") == 0 )          pv = nullptr ; 
   if(strcmp(name, "physiLowerChimneyTyvek") == 0 )     pv = physiLowerChimneyTyvek ; 
   if(strcmp(name, "physiLowerChimneyAcrylic") == 0 )   pv = physiLowerChimneyAcrylic ; 
   if(strcmp(name, "physiLowerChimneySteel") == 0 )     pv = physiLowerChimneySteel ; 
   if(strcmp(name, "physiLowerChimneyLS") == 0 )        pv = physiLowerChimneyLS ; 
   if(strcmp(name, "physiLowerChimneyBlocker") == 0 )   pv = physiLowerChimneyBlocker ; 

   G4PVPlacement* pv_ = dynamic_cast<G4PVPlacement*>(pv);  
   if( pv_ == nullptr ) dump("LowerChimney::getPV FAILED"); 
   return pv_ ; 
}

G4VSolid*     LowerChimney::getSolid(const char* name)
{
   G4VSolid* so = nullptr ; 
   if(strcmp(name, "solidLowerChimney") == 0 )          so = solidLowerChimney ; 
   if(strcmp(name, "solidLowerChimneyTyvek") == 0 )     so = solidLowerChimneyTyvek ; 
   if(strcmp(name, "solidLowerChimneyAcrylic") == 0 )   so = solidLowerChimneyAcrylic ; 
   if(strcmp(name, "solidLowerChimneySteel") == 0 )     so = solidLowerChimneySteel ; 
   if(strcmp(name, "solidLowerChimneyLS") == 0 )        so = solidLowerChimneyLS ; 
   if(strcmp(name, "solidLowerChimneyBlocker") == 0 )   so = solidLowerChimneyBlocker ; 
   if( so == nullptr ) dump("LowerChimney::getSolid FAILED"); 
   return so ; 
}

NP* LowerChimney::getValues(const char* prefix) 
{
    return nullptr ;  
}


void LowerChimney::dump(const char* msg) const 
{
    std::cout 
        << msg 
        << std::endl 
        << " solidLowerChimney " << solidLowerChimney
        << std::endl 
        << " solidLowerChimneyTyvek " << solidLowerChimneyTyvek
        << std::endl 
        << " solidLowerChimneyAcrylic " << solidLowerChimneyAcrylic
        << std::endl 
        << " solidLowerChimneySteel " << solidLowerChimneySteel
        << std::endl 
        << " solidLowerChimneyBlocker " << solidLowerChimneyBlocker
        << std::endl 
        ;
}



G4LogicalVolume* 
LowerChimney::getLV() {

    std::cout << "LowerChimney::getLV" << std::endl ; 

    if (logicLowerChimney) {
        return logicLowerChimney;
    }
//    initVariables();
    initMaterials();
//    G4cout<<"Chimney Option: "<<m_use_chimney_opt<<"!!!!!!!!!!!!!"<<G4endl;

    if (m_lower_chimney and m_use_shutter) {
        G4cout<<"Begin Lower Chimney Construction"<<G4endl;

    makeLowerChimneyLogicalAndPhysical();
    setupLowerChimneyReflectorInCD();
//    setupBlockerReflectorInCD();
    }
	if( m_lower_chimney and !m_use_shutter){
		G4cout<<"Update Chimney without shutter box"<<G4endl;
    	makeNoShutterLowerChimneyLogicalAndPhysical();
	}


    return logicLowerChimney;
} 
#ifdef PMTSIM_STANDALONE
#else
bool
LowerChimney::inject(std::string motherName, IDetElement* other, IDetElementPos* /* pos */) {
    // Get the mother volume in current DetElem.
    G4LogicalVolume* mothervol = 0;
    if ( motherName == "lLowerChimney" ) {
        mothervol = logicLowerChimney;
    }
    if (not mothervol) {
        // don't find the volume.
        return false;
    }
    
    // retrieve the daughter's LV
    G4LogicalVolume* daughtervol = other->getLV();
    
    if (not daughtervol) {
        return false;
    }
    
    G4cout << "WARNING: LowerChimney::inject is not implemented yet. "
           << "The volume placed in LowerChimney will be omitted" << G4endl;

    return true;
}
#endif


//    void
//    LowerChimney::initVariables() {
//        SniperPtr<DetSimAlg> detsimalg(getScope(), "DetSimAlg");
//        if (detsimalg.invalid()) {
//            std::cout << "Can't Load DetSimAlg" << std::endl;
//            assert(0);
//        }
//        ToolBase* t = detsimalg->findTool("GlobalGeomInfo");
//        assert(t);
//        IDetElement* globalinfo = dynamic_cast<IDetElement*>(t);
        
//        m_heightWP =42.5*m;
//        TopToWater=m_ChimneyTopToWater*m;
//        GateCenter=m_BlockerZ*m;
        
//    }
    
    void
    LowerChimney::initMaterials() {
        LS = G4Material::GetMaterial("LS");
        Water = G4Material::GetMaterial("Water");
        Acrylic = G4Material::GetMaterial("Acrylic");
        Tyvek = G4Material::GetMaterial("Tyvek");
        Steel= G4Material::GetMaterial("Steel");
        Air= G4Material::GetMaterial("Air");
    }


void LowerChimney::makeLowerChimneyLogicalAndPhysical(){
    LowerChimneyMaker chim(m_Blocker2Btm);
   
    solidLowerChimneyTyvek    = chim.getSolidTyvek();
    solidLowerChimneyAcrylic  = chim.getSolidAcrylic();
    solidLowerChimneySteel    = chim.getSolidSteel();
    solidLowerChimneyLS       = chim.getSolidLS();
    solidLowerChimneyBlocker  = chim.getSolidCBlocker();
    solidLowerChimney    = chim.getSolidLogical();

    //double offsetTyvek= chim.m_TubeH - chim.m_upperAcrylicHeight/2. - chim.m_TubeH/2.;
    double offsetTyvek= 0; 
    double AcrylicH=m_Blocker2Btm*m-chim.m_Inner_Box_Height/2.0-chim.m_Tyvek_thickness-chim.m_Steel_thickness - chim.m_lowerSteelTubeH;
    double offsetAcrylic=AcrylicH/2.-chim.m_TubeH/2.;

    double offsetLS=0;
    double offsetSteel=0;
    double offsetBlocker=m_Blocker2Btm*m-chim.m_TubeH/2.;




    logicLowerChimney        = new G4LogicalVolume(solidLowerChimney,
                                            Water,
                                            "lLowerChimney",
                                            0,
                                            0,
                                            0);    
    G4VisAttributes* visatt = new G4VisAttributes(G4Colour(0.9, 0.0, 0.0));
    visatt -> SetForceWireframe(true);  
    visatt -> SetForceAuxEdgeVisible(true);
    //visatt -> SetForceSolid(true);
    //visatt -> SetForceLineSegmentsPerCircle(4);
    logicLowerChimney -> SetVisAttributes(visatt);


    logicLowerChimneyTyvek   = new G4LogicalVolume(solidLowerChimneyTyvek,
                                            Tyvek,
                                            "lLowerChimneyTyvek",
                                            0,
                                            0,
                                            0);    

    logicLowerChimneyAcrylic = new G4LogicalVolume(solidLowerChimneyAcrylic,
                                            Acrylic,
                                            "lLowerChimneyAcrylic",
                                            0,
                                            0,
                                            0);    

    logicLowerChimneySteel   = new G4LogicalVolume(solidLowerChimneySteel,
                                            Steel,
                                            "lLowerChimneySteel",
                                            0,
                                            0,
                                            0);    

    logicLowerChimneyLS      = new G4LogicalVolume(solidLowerChimneyLS,
                                            LS,
                                            "lLowerChimneyLS",
                                            0,
                                            0,
                                            0);    

    logicLowerChimneyBlocker  = new G4LogicalVolume(solidLowerChimneyBlocker,
                                            Steel,
                                     //       LS,
                                     //    Black Acrylic not defined 
                                            "lLowerChimneyBlocker",
                                            0,
                                            0,
                                            0);    


physiLowerChimneyTyvek    = new G4PVPlacement(0,              // no rotation
                                      //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
                                      G4ThreeVector(0,0,offsetTyvek), // at (x,y,z)
                                      logicLowerChimneyTyvek,    // its logical volume
                                      "pLowerChimneyTyvek",       // its name
                                      logicLowerChimney,  // its mother  volume
                                      false,           // no boolean operations
                                      0);
physiLowerChimneyAcrylic    = new G4PVPlacement(0,              // no rotation
                                      //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
                                      G4ThreeVector(0,0,offsetAcrylic), // at (x,y,z)
                                      logicLowerChimneyAcrylic,    // its logical volume
                                      "pLowerChimneyAcrylic",       // its name
                                      logicLowerChimney,  // its mother  volume
                                      false,           // no boolean operations
                                      0);
physiLowerChimneySteel       = new G4PVPlacement(0,              // no rotation
                                      //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
                                      G4ThreeVector(0,0,offsetSteel), // at (x,y,z)
                                      logicLowerChimneySteel,    // its logical volume
                                      "pLowerChimneySteel",       // its name
                                      logicLowerChimney,  // its mother  volume
                                      false,           // no boolean operations
                                      0);
physiLowerChimneyLS          = new G4PVPlacement(0,              // no rotation
                                      //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
                                      G4ThreeVector(0,0,offsetLS), // at (x,y,z)
                                      logicLowerChimneyLS,    // its logical volume
                                      "pLowerChimneyLS",       // its name
                                      logicLowerChimney,  // its mother  volume
                                      false,           // no boolean operations
                                      0);
physiLowerChimneyBlocker       = new G4PVPlacement(0,              // no rotation
                                      //G4ThreeVector(0,0,GateCenter+m_heightWP/2), // at (x,y,z)
                                      G4ThreeVector(0,0,offsetBlocker), // at (x,y,z)
                                      logicLowerChimneyBlocker,    // its logical volume
                                      "pLowerChimneyBlocker",       // its name
                                      logicLowerChimneyLS,  // its mother  volume
                                      false,           // no boolean operations
                                      0);

}
void
LowerChimney::setupLowerChimneyReflectorInCD()
{
//        G4PhysicalVolumeStore* store = G4PhysicalVolumeStore::GetInstance();

//        G4VPhysicalVolume* chimney_acrylic = store->GetVolume("pLowerChimneyAcrylic");
//        G4VPhysicalVolume* chimney_tyvek = store->GetVolume("pLowerChimneyTyvek");

        assert(physiLowerChimneyAcrylic and physiLowerChimneyTyvek);

        G4OpticalSurface* tyvek_surface = new G4OpticalSurface("ChimneyTyvekOpticalSurface");
        G4LogicalBorderSurface* TyvekSurface = new G4LogicalBorderSurface("ChimneyTyvekSurface",
                                                 physiLowerChimneyAcrylic, physiLowerChimneyTyvek, tyvek_surface);
        assert(TyvekSurface);

        G4MaterialPropertiesTable* tyvek_mt = new G4MaterialPropertiesTable();
        tyvek_surface->SetModel(unified);
        tyvek_surface->SetType(dielectric_metal);
        tyvek_surface->SetFinish(ground);
        tyvek_surface->SetSigmaAlpha(0.2);
        double TyvekEnergy[4] = {1.55*eV, 6.20*eV, 10.33*eV, 15.5*eV};
        //double TyvekReflectivity[4] = {0.98, 0.98, 0.98, 0.98};
        double TyvekReflectivity[4] = {m_reflectivity,m_reflectivity,m_reflectivity,m_reflectivity};
        tyvek_mt->AddProperty("REFLECTIVITY", TyvekEnergy, TyvekReflectivity, 4);
        tyvek_surface->SetMaterialPropertiesTable(tyvek_mt);
}

void LowerChimney::makeNoShutterLowerChimneyLogicalAndPhysical(){
    // TODO: need to optimize this part. following are copied from Dimensions.hh
    const double WPHeight=43.5*m;   // water pool height
    const double Acrylic_thickness=12.4*cm;// thickness of the acrylic tube of the chimney
    const double TubeInnerR=0.4*m;        // inner R of acrylic tube.
    const double TubeAcrylicOuterR=TubeInnerR+Acrylic_thickness;

    const double CD_R=17.7*m+Acrylic_thickness;
    //const double ChimBtm_2_Center=sqrt(CD_R*CD_R-TubeAcrylicOuterR*TubeAcrylicOuterR);
    const double ChimBtm_2_Center=CD_R;
    const double LowerTubeH=WPHeight/2.- ChimBtm_2_Center; // height of lower chimney

    // double m_TubeH = 393*cm;    // height of chimney under the water is 393*cm
    double m_TubeH = LowerTubeH;
    double m_Acrylic_H = 60*cm;
    G4Tubs* solidWaterTube = new G4Tubs("sWaterTube",
                                        0,
                                        TubeAcrylicOuterR,
                                        m_TubeH/2.0,
                                        0,									
                                        360*deg									
                                        );

    logicLowerChimney = new G4LogicalVolume(solidWaterTube,
                                            Water,
                                            "lLowerChimney",
                                            0,
                                            0,
                                            0);

    G4Tubs* solidChimneyAcrylic = new G4Tubs("sChimneyAcrylic",
                                             TubeInnerR,
                                             TubeAcrylicOuterR,
                                             m_Acrylic_H/2.0,
                                             0,									
                                             360*deg									
                                             );

    logicLowerChimneyAcrylic = new G4LogicalVolume(solidChimneyAcrylic,
                                                   Acrylic,
                                                   "lLowerChimneyAcrylic",
                                                   0,
                                                   0,
                                                   0);

    G4Tubs* solidChimneyLS = new G4Tubs("sChimneyLS",
                                        0,
                                        TubeInnerR,
                                        m_TubeH/2.0,
                                        0,									
                                        360*deg									
                                        );

    logicLowerChimneyLS = new G4LogicalVolume(solidChimneyLS,
                                              LS,
                                              "lLowerChimneyLS",
                                              0,
                                              0,
                                              0);

    G4Tubs* solidChimneySteel = new G4Tubs("sChimneySteel",
                                           40*cm,   // TODO
                                           40.5*cm, // TODO
                                           (m_TubeH-m_Acrylic_H)/2.0,
                                           0,									
                                           360*deg									
                                           );

    logicLowerChimneySteel = new G4LogicalVolume(solidChimneySteel,
                                                 Steel,
                                                 "lLowerChimneySteel",
                                                 0,
                                                 0,
                                                 0);
			
    physiLowerChimneyAcrylic = new G4PVPlacement(0,              // no rotation
                                                 G4ThreeVector(0,0,(m_Acrylic_H-m_TubeH)/2.0), // at (x,y,z)
                                                 logicLowerChimneyAcrylic,    // its logical volume
                                                 "pLowerChimneyAcrylic",       // its name
                                                 logicLowerChimney,  // its mother  volume
                                                 false,           // no boolean operations
                                                 0);

    physiLowerChimneyLS = new G4PVPlacement(0,              // no rotation
                                            G4ThreeVector(0,0,0), // at (x,y,z)
                                            logicLowerChimneyLS,    // its logical volume
                                            "pLowerChimneyLS",       // its name
                                            logicLowerChimney,  // its mother  volume
                                            false,           // no boolean operations
                                            0);

    physiLowerChimneySteel = new G4PVPlacement(0,              // no rotation
                                               G4ThreeVector(0,0,m_Acrylic_H/2.0), // at (x,y,z)
                                               logicLowerChimneySteel,    // its logical volume
                                               "pLowerChimneySteel",       // its name
                                               logicLowerChimney,  // its mother  volume
                                               false,           // no boolean operations
                                               0);


    G4OpticalSurface* steel_surface = new G4OpticalSurface("ChimneySteelOpticalSurface");
    G4MaterialPropertiesTable* steel_mt = new G4MaterialPropertiesTable();
    steel_surface->SetModel(unified);
    steel_surface->SetType(dielectric_metal);
    steel_surface->SetFinish(ground);
    steel_surface->SetSigmaAlpha(0.2);
    double SteelEnergy[4] = {1.55*eV, 6.20*eV, 10.33*eV, 15.5*eV};
    double SteelReflectivity[4] = {m_reflectivity,m_reflectivity,m_reflectivity,m_reflectivity};
    steel_mt->AddProperty("REFLECTIVITY", SteelEnergy, SteelReflectivity, 4);
    steel_surface->SetMaterialPropertiesTable(steel_mt);
    new G4LogicalSkinSurface("Steel_surface",logicLowerChimneySteel,steel_surface);

}
