#include "junoPMTOpticalModel.hh"

#include "Randomize.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4VPhysicalVolume.hh"
#include "G4GeometryTolerance.hh"
#include "G4PhysicalConstants.hh"
#include "G4ParticleDefinition.hh"
#include "G4VSensitiveDetector.hh"
#include "G4MaterialPropertiesTable.hh"

#ifndef PMTSIM_STANDALONE
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SvcFactory.h"
#include "SniperKernel/SniperException.h"
#include <boost/filesystem.hpp>
#endif
#include <complex>

junoPMTOpticalModel::junoPMTOpticalModel(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
    : G4VFastSimulationModel(modelName, envelope)
{
    _photon_energy  = 0.;
    _wavelength     = 0.;
    _aoi            = 0.;
    _n1             = 0.;
    _n2             = 0.;
    _k2             = 0.;
    _n3             = 0.;
    _k3             = 0.;
    _n4             = 0.;
    _qe             = 0.;

    _sin_theta1     = 0.;
    _cos_theta1     = 0.;
    _sin_theta4     = G4complex(0., 0.);
    _cos_theta4     = G4complex(0., 0.);
    
    fR_s            = 0.;
    fT_s            = 0.;
    fR_p            = 0.;
    fT_p            = 0.;
    fR_n            = 0.;
    fT_n            = 0.;

    n_glass         = 0.;
    n_coating       = 0.;
    k_coating       = 0.;
    d_coating       = 0.;
    n_photocathode  = 0.;
    k_photocathode  = 0.;
    d_photocathode  = 0.;
    n_vacuum        = 1.;

    time            = 0.;
    energy          = 0.;
    pos             = G4ThreeVector(0., 0., 0.);
    dir             = G4ThreeVector(0., 0., 0.);
    pol             = G4ThreeVector(0., 0., 0.);
    norm            = G4ThreeVector(0., 0., 0.);
    
    whereAmI        = OutOfRegion;

    InitOpticalParameters(envelope_phys);

#ifndef PMTSIM_STANDALONE
    // temporary exclude
    m_multi_film_model = new MultiFilmModel(4);
#endif

}

junoPMTOpticalModel::~junoPMTOpticalModel()
{
}

G4bool junoPMTOpticalModel::IsApplicable(const G4ParticleDefinition & particleType)
{
    return (&particleType == G4OpticalPhoton::OpticalPhotonDefinition());
}

G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
{

    if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner2_phys){
        return false;
    }

    envelope_solid = fastTrack.GetEnvelopeSolid();

    pos     = fastTrack.GetPrimaryTrackLocalPosition();
    dir     = fastTrack.GetPrimaryTrackLocalDirection();
    pol     = fastTrack.GetPrimaryTrackLocalPolarization();
    time    = fastTrack.GetPrimaryTrack()->GetGlobalTime();
    energy  = fastTrack.GetPrimaryTrack()->GetKineticEnergy();

    if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner1_phys){
        whereAmI = kInVacuum;
    }else{
        whereAmI = kInGlass;
    }

#ifndef PMTSIM_STANDALONE
    if(whereAmI == kInGlass){
        dist1 = _inner1_solid->DistanceToIn(pos, dir);
        dist2 = _inner2_solid->DistanceToIn(pos, dir);

        if(dist1 == kInfinity){
            return false;
        }else if(dist1>dist2){
            return false;
        }else{
            return true;
        }
    }else{
        dist1 = _inner1_solid->DistanceToOut(pos, dir);
        dist2 = _inner2_solid->DistanceToIn(pos, dir);

        if(dist2 == kInfinity){
            return true;
        }
    }
    return false;

#else
    dist1 = whereAmI == kInGlass ? _inner1_solid->DistanceToIn(pos, dir) : _inner1_solid->DistanceToOut(pos, dir);
    dist2 = whereAmI == kInGlass ? _inner2_solid->DistanceToIn(pos, dir) : _inner2_solid->DistanceToIn(pos, dir) ;

    bool ret =  whereAmI == kInGlass ?
                       (( dist1 == kInfinity || dist1 > dist2 ) ? false : true )
                :
                       (( dist2 == kInfinity ) ? true : false ) 
                ; 


/*
    U4FastSim_Debug dbg ; 

    dbg.posx = pos.x(); 
    dbg.posy = pos.y(); 
    dbg.posz = pos.z(); 
    dbg.time = time ; 

    dbg.dirx = dir.x(); 
    dbg.diry = dir.y(); 
    dbg.dirz = dir.z(); 
    dbg.dist1 = dist1  ; 

    dbg.polx = pol.x(); 
    dbg.poly = pol.y(); 
    dbg.polz = pol.z(); 
    dbg.dist2 = dist2  ; 
 
    dbg.ModelTrigger = double(ret) ; 
    dbg.whereAmI = double(whereAmI) ;  
    dbg.c = 0. ; 
    dbg.d = 0. ; 
  
    dbg.add() ; 
*/
   
    return ret ; 
#endif
}




void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
{
    _photon_energy  = energy;
    _wavelength     = twopi*hbarc/energy;

    const G4Track* track = fastTrack.GetPrimaryTrack();

#ifndef PMTSIM_STANDALONE
    n_glass    = _rindex_glass->Value(_photon_energy);

    int pmtid  = get_pmtid(track);
    int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);

    _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);

    n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;

    n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;
#endif


    if(whereAmI == kInGlass){
        _n1 = n_glass;
        _n2 = n_coating;
        _k2 = k_coating;
        _d2 = d_coating;
        _n3 = n_photocathode;
        _k3 = k_photocathode;
        _d3 = d_photocathode;
        _n4 = n_vacuum;
    }else{
        _n1 = n_vacuum;
        _n2 = n_photocathode;
        _k2 = k_photocathode;
        _d2 = d_photocathode;
        _n3 = n_coating;
        _k3 = k_coating;
        _d3 = d_coating;
        _n4 = n_glass;

        _qe = 0.;
    }
    pos  += dist1*dir;
    time += dist1*_n1/c_light;

    UpdateTrackInfo(fastStep);

    fastTrack.GetPrimaryTrack()->GetStep()
        ->GetPostStepPoint()->SetStepStatus(fGeomBoundary);

    norm = _inner1_solid->SurfaceNormal(pos);
    if(whereAmI == kInGlass){
        norm *= -1.0;
    }

    _cos_theta1 = dir*norm;

    if(_cos_theta1 < 0.){
        _cos_theta1 = -_cos_theta1;
        norm = -norm;
    }
    _aoi = acos(_cos_theta1)*360./twopi;

    CalculateCoefficients();

    G4double T  = 0.;
    G4double R  = 0.;
    G4double A  = 0.;
    G4double An = 0.;
    G4double escape_fac = 0.;
    G4double E_s2 = 0.;

    if(_sin_theta1 > 0.){
        E_s2 = (pol*dir.cross(norm))/_sin_theta1;
        E_s2 *= E_s2;
    }else{
        E_s2 = 0.;
    }

    T = fT_s*E_s2 + fT_p*(1.0-E_s2);
    R = fR_s*E_s2 + fR_p*(1.0-E_s2);
    A = 1.0 - (T+R);

    An = 1.0 - (fT_n+fR_n);
    escape_fac  = _qe/An;

    if(escape_fac > 1.){
        G4cout<<"junoPMTOpticalModel: QE is larger than absorption coeff."<<G4endl;
    }

    G4double rand_absorb = G4UniformRand();
    G4double rand_escape = G4UniformRand();

    if(rand_absorb < A){
        // absorbed
        fastStep.ProposeTrackStatus(fStopAndKill);
        if(rand_escape<escape_fac){
        // detected
            fastStep.ProposeTotalEnergyDeposited(_photon_energy);
        }
    }else if(rand_absorb < A+R){
        // fastStep.ProposeTrackStatus(fStopAndKill);
        // reflected
        Reflect();
        UpdateTrackInfo(fastStep);
    }else{
        // fastStep.ProposeTrackStatus(fStopAndKill);
        // transmitted
        Refract();
        if(whereAmI == kInGlass){
            whereAmI = kInVacuum;
        }else{
            whereAmI = kInGlass;
        }
        UpdateTrackInfo(fastStep);
    }

    return;
}

void junoPMTOpticalModel::CalculateCoefficients()
{
    G4complex one(1., 0.);
    _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1);
    _sin_theta4 = _n1 * _sin_theta1/_n4;
    _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);

    m_multi_film_model->SetWL(_wavelength/m);
    m_multi_film_model->SetAOI(_aoi);

    m_multi_film_model->SetLayerPar(0, _n1);
    m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    m_multi_film_model->SetLayerPar(3, _n4);
    ART art1 = m_multi_film_model->GetART();
    fR_s = art1.R_s;
    fT_s = art1.T_s;
    fR_p = art1.R_p;
    fT_p = art1.T_p;

    m_multi_film_model->SetLayerPar(0, n_glass);
    m_multi_film_model->SetLayerPar(1, n_coating, k_coating, d_coating);
    m_multi_film_model->SetLayerPar(2, n_photocathode, k_photocathode, d_photocathode);
    m_multi_film_model->SetLayerPar(3, n_vacuum);
    ART art2 = m_multi_film_model->GetNormalART();
    fR_n = art2.R;
    fT_n = art2.T;
}

void junoPMTOpticalModel::UpdateTrackInfo(G4FastStep &fastStep)
{
    fastStep.SetPrimaryTrackFinalTime(time);
    fastStep.SetPrimaryTrackFinalPosition(pos);
    fastStep.SetPrimaryTrackFinalMomentum(dir);
    fastStep.SetPrimaryTrackFinalPolarization(pol);
    fastStep.ForceSteppingHitInvocation();
}

void junoPMTOpticalModel::InitOpticalParameters(G4VPhysicalVolume* envelope_phys)
{
    G4LogicalVolume* envelope_log 
        = envelope_phys->GetLogicalVolume();
    G4MaterialPropertiesTable* glass_pt 
        = envelope_log->GetMaterial()->GetMaterialPropertiesTable();
    
    _rindex_glass   = glass_pt->GetProperty("RINDEX");
    _inner1_phys    = envelope_log->GetDaughter(0);
    _inner1_solid   = _inner1_phys->GetLogicalVolume()->GetSolid();
    _rindex_vacuum  = _inner1_phys->GetLogicalVolume()->GetMaterial()
                                  ->GetMaterialPropertiesTable()->GetProperty("RINDEX");

    _inner2_phys    = envelope_log->GetDaughter(1);
    _inner2_solid   = _inner2_phys->GetLogicalVolume()->GetSolid();
}

void junoPMTOpticalModel::Reflect()
{
    dir -= 2.*(dir*norm)*norm;
    pol -= 2.*(pol*norm)*norm;
}

void junoPMTOpticalModel::Refract()
{
    dir = (real(_cos_theta4) - _cos_theta1*_n1/_n4)*norm + (_n1/_n4)*dir;
    pol = (pol-(pol*dir)*dir).unit();
}

int junoPMTOpticalModel::get_pmtid(const G4Track* track) {
    int ipmt= -1;
    {
        const G4VTouchable* touch= track->GetTouchable();
        int nd= touch->GetHistoryDepth();
        int id=0;
        for (id=0; id<nd; id++) {
            if (touch->GetVolume(id)==track->GetVolume()) {
                int idid=1;
                G4VPhysicalVolume* tmp_pv=NULL;
                for (idid=1; idid < (nd-id); ++idid) {
                    tmp_pv = touch->GetVolume(id+idid);

                    G4LogicalVolume* mother_vol = tmp_pv->GetLogicalVolume();
                    G4LogicalVolume* daughter_vol = touch->GetVolume(id+idid-1)->
                        GetLogicalVolume();
                    int no_daugh = mother_vol -> GetNoDaughters();
                    if (no_daugh > 1) {
                        int count = 0;
                        for (int i=0; (count<2) &&(i < no_daugh); ++i) {
                            if (daughter_vol->GetName()
                                    ==mother_vol->GetDaughter(i)->GetLogicalVolume()->GetName()) {
                                ++count;
                            }
                        }
                        if (count > 1) {
                            break;
                        }
                    }
                }
                ipmt= touch->GetReplicaNumber(id+idid-1);
                break;
            }
        }
        if (ipmt < 0) {
            G4Exception("junoPMTOpticalModel: could not find envelope -- where am I !?!", // issue
                    "", //Error Code
                    FatalException, // severity
                    "");
        }
    }

    return ipmt;
}
