#ifndef junoPMTOpticalModel_h
#define junoPMTOPticalModel_h 1

#include "G4Step.hh"
#include "G4VSolid.hh"
#include "G4Material.hh"
#include "G4StepPoint.hh"
#include "G4FastTrack.hh"
#include "G4Navigator.hh"
#include "G4TouchableHandle.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VFastSimulationModel.hh"
#include "G4MaterialPropertyVector.hh"
#include "G4Track.hh"


#ifdef PMTSIM_STANDALONE
#include "JPMT.h"
#include "MultiFilmModel.h"
#else

#include "TGraph.h"
#include "SniperKernel/SvcBase.h"
#include "Geometry/PMTParamSvc.h"
#include "MultiFilmSimSvc/MultiFilmModel.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"
#include "Geometry/IPMTParamSvc.h"

#endif

enum EWhereAmI { OutOfRegion, kInGlass, kInVacuum };

class junoPMTOpticalModel : public G4VFastSimulationModel
{
    public:
        junoPMTOpticalModel(G4String, G4VPhysicalVolume*, G4Region*); 
        ~junoPMTOpticalModel();

        virtual G4bool IsApplicable(const G4ParticleDefinition&);
        virtual G4bool ModelTrigger(const G4FastTrack&);
        virtual void DoIt(const G4FastTrack&, G4FastStep&);

#ifndef PMTSIM_STANDALONE
        void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
        IPMTSimParamSvc* getPMTSimParamSvc() const { return m_PMTSimParSvc; }

        void setPMTParamSvc(IPMTParamSvc* svc) { m_PMTParamSvc = svc; }
        IPMTParamSvc* getPMTParamSvc() const { return m_PMTParamSvc; }
#endif
    
    private:
        G4MaterialPropertyVector* _rindex_glass;
        G4MaterialPropertyVector* _rindex_vacuum;

        G4VSolid* _inner1_solid;
        G4VSolid* _inner2_solid;
        G4VSolid* envelope_solid;

        G4VPhysicalVolume* _inner1_phys;
        G4VPhysicalVolume* _inner2_phys;

        G4double _photon_energy;
        G4double _wavelength;
        G4double _aoi;
        G4double _n1;
        G4double _n2, _k2, _d2;
        G4double _n3, _k3, _d3;
        G4double _n4;
        G4double _qe;
        G4double n_glass;
        G4double n_vacuum;
        G4double n_coating;
        G4double k_coating;
        G4double d_coating;
        G4double n_photocathode;
        G4double k_photocathode;
        G4double d_photocathode;

        G4double _sin_theta1;
        G4double _cos_theta1;
        G4complex _sin_theta4;
        G4complex _cos_theta4;
        
        G4double fR_s;
        G4double fT_s;
        G4double fR_p;
        G4double fT_p;
        G4double fR_n;
        G4double fT_n;

        G4double time;
        G4double dist1;
        G4double dist2;
        G4double energy;
        G4ThreeVector pos;
        G4ThreeVector dir;
        G4ThreeVector pol;
        G4ThreeVector norm;

        EWhereAmI whereAmI;
        
#ifdef PMTSIM_STANDALONE
        JPMT* jpmt ; 
#else
        IPMTParamSvc* m_PMTParamSvc;
        IPMTSimParamSvc* m_PMTSimParSvc;
#endif
        MultiFilmModel* m_multi_film_model;

        void CalculateCoefficients();

#ifdef PMTSIM_STANDALONE
        void setEnergy( double energy );
        void setMinusCosTheta(double minus_cos_theta );
     public:
        void CalculateCoefficients(double energy, double minus_cos_theta );
     private:
#endif
        
        void Reflect();
        void Refract();

        void InitOpticalParameters(G4VPhysicalVolume* envelope_phys);
        void UpdateTrackInfo(G4FastStep &fastStep);

        int get_pmtid(const G4Track* track);
};

#endif
