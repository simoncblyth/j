#include <vector>
#include <string>

#include "Geometry/PMTParamData.h"
#include "Geometry/_PMTParamData.h"
#include "PMTSimParamSvc/PMTSimParamData.h"
#include "PMTSimParamSvc/_PMTSimParamData.h"

#include "LSExpDetectorConstruction_Opticks.hh"

#ifdef WITH_G4CXOPTICKS

#include "G4CXOpticks.hh"
#include "SSim.hh"
#include "SLOG.hh"

#else

#include <iostream>

#endif

#ifdef WITH_G4CXOPTICKS
void LSExpDetectorConstruction_Opticks::Setup(
          int opticksMode,
          const G4VPhysicalVolume* world, 
          const G4VSensitiveDetector* sd, 
          PMTParamData* ppd, 
          PMTSimParamData* psd
          )
{
    LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ; 
    if( opticksMode == 0 ) return ; 

    G4CXOpticks::SetGeometry(world) ; 

    _PMTParamData    _ppd(*ppd) ; 
    _PMTSimParamData _psd(*psd) ; 

    NPFold* j = new NPFold ; 
    j->add_subfold( "PMTParamData",    _ppd.serialize() );
    j->add_subfold( "PMTSimParamData", _psd.serialize() );

    SSim::AddSubfold("juno", j );

    G4CXOpticks::SaveGeometry(); 

    LOG(info) << "] WITH_G4CXOPTICKS " ; 
}
#elif WITH_G4OPTICKS
/**
LSExpDetectorConstruction_Opticks::Setup
------------------------------------------

1. pass geometry to Opticks, translate it to GPU and return sensor placements 
2. use the placements to pass sensor data : efficiencies, categories, identifiers
3. pass theta dependent efficiency tables for all sensor categories




                             |--------- 2230 ----------------|-- 120--|
                             20050                           17820    17700
                          / /                               /         /
                         / /                               /         /
                        / pInnerWater                     /         /
                       / /                               /         /
                      / /                  (0)          /         /
                     pTyvek                  \         pAcrylic  /
                    / /                       \       /         /
                   / /                         \     /         pTarget:LS
                  / /                           \   /         /
                 / /                             \ /         /
                / /                              (1)        /
               / /                               / \       /
              / /                               /   \     /
             / /                               /     \   /         
            / /                               /       \ /
           / /                          Wa   /  Ac    (2)             
          / /                               /         / \
         / /                               /         /   \
        / /                               /         /     \        LS    




The below examles of geospecific options control which boundary_pos is captured 
into the way buffer and saved with hits "hiy". Using::

      --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge    # (1): gives radius 17820
      --way --pvname pTarget  --boundary Acrylic///LS --waymask 3  --gdmlkludge      # (2): gives radius 17700

*way*
    enables way point recording 

*pvname*
    potential input to control which way boundary position to record

*boundary*
    potential input to control which way boundary position to record

*waymask* 
    selects whether to match on pvname and/or boundary for the recorder boundary position see OGeo::initWayControl


*gdmlkludge*
   applies kludge to exported origin.gdml creating origin_CGDMLKludge.gdml with a few fixes:

   1. define/matrix with truncated values are trimmed to even to make them parseable
   2. define/constant are converted to define/matrix 

   The "--gdmlkludge" option is needed to avoid GDML parse failures that cause around 8 opticks-t tests to fail.

**/


void LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd_, int opticksMode )  // static
{
    if( opticksMode == 0 ) return ; 
    LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ; 

    assert(world); 

    // 1. pass geometry to Opticks, translate it to GPU and return sensor placements  

    G4Opticks* g4ok = new G4Opticks ; 

    bool outer_volume = true ; 
    bool profile = true ; 

    const char* geospecific_default =   "--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge" ;  // (1): gives radius 17820
    const char* embedded_commandline_extra = SSys::getenvvar("LSXDC_GEOSPECIFIC", geospecific_default ) ;   
    LOG(info) << " embedded_commandline_extra " << embedded_commandline_extra ;

    g4ok->setPlacementOuterVolume(outer_volume); 
    g4ok->setProfile(profile); 
    g4ok->setEmbeddedCommandLineExtra(embedded_commandline_extra);
    g4ok->setGeometry(world); 

    const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements() ;       
    unsigned num_sensor = sensor_placements.size(); 

    // 2. use the placements to pass sensor data : efficiencies, categories, identifiers  

    const junoSD_PMT_v2* sd = dynamic_cast<const junoSD_PMT_v2*>(sd_) ;  
    assert(sd) ; 

    LOG(info) << "[ setSensorData num_sensor " << num_sensor ; 
    for(unsigned i=0 ; i < num_sensor ; i++)
    {
        const G4PVPlacement* pv = sensor_placements[i] ; // i is 0-based unlike sensor_index
        unsigned sensor_index = 1 + i ; // 1-based 
        assert(pv); 
        G4int copyNo = pv->GetCopyNo();  
        int pmtid = copyNo ; 
        int pmtcat = 0 ; // sd->getPMTCategory(pmtid); 
        float efficiency_1 = sd->getQuantumEfficiency(pmtid); 
        float efficiency_2 = sd->getEfficiencyScale() ; 

        g4ok->setSensorData( sensor_index, efficiency_1, efficiency_2, pmtcat, pmtid ); 
    }
    LOG(info) << "] setSensorData num_sensor " << num_sensor ; 

    // 3. pass theta dependent efficiency tables for all sensor categories 

    PMTEfficiencyTable* pt = sd->getPMTEfficiencyTable(); 
    assert(pt);

    const std::vector<int>& shape = pt->getShape(); 
    const std::vector<float>& data = pt->getData(); 

    int   theta_steps = pt->getThetaSteps();  
    float theta_min = pt->getThetaMin(); 
    float theta_max = pt->getThetaMax();
    LOG(info) 
         << "[ setSensorAngularEfficiency "
         << " theta_steps " << theta_steps 
         << " theta_min " << theta_min
         << " theta_max " << theta_max
         ; 
  
    g4ok->setSensorAngularEfficiency(shape, data, theta_steps, theta_min, theta_max); 
    LOG(info) << "] setSensorAngularEfficiency " ;

    g4ok->saveSensorLib("$TMP/LSExpDetectorConstruction__SetupOpticks/SensorLib") ; // just for debug 

    LOG(info) << "] WITH_G4OPTICKS " ; 
}

#else
void LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume*, const G4VSensitiveDetector*, int )
{
    std::cout << "LSExpDetectorConstruction_Opticks::Setup NOOP " << std::endl ;  
}
#endif











