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

#ifdef PMTFASTSIM_STANDALONE
#include "F4.hh"
#include "JPMT.h"
#include "Layr.h"

#include "OpticalSystem.h"
#include "Matrix.h"
#include "Layer.h"

#include "SLOG.hh"
#include "SEvt.hh"
#include "SFastSim_Debug.hh"
#include "STrackInfo.h"
#include "SOpBoundaryProcess.hh"

#include "spho.h"

#include "SPhoton_Debug.h"
template<> std::vector<SPhoton_Debug<'A'>> SPhoton_Debug<'A'>::record = {} ;

#include "SUniformRand.h"
typedef SUniformRand<CLHEP::HepRandom> UUniformRand ; 

#endif

#ifndef PMTFASTSIM_STANDALONE
#include "SniperKernel/SniperPtr.h"
#include "SniperKernel/SniperLog.h"
#include "SniperKernel/SvcFactory.h"
#include "SniperKernel/SniperException.h"
#include <boost/filesystem.hpp>
#endif
#include <complex>


junoPMTOpticalModel::junoPMTOpticalModel(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
    : 
    G4VFastSimulationModel(modelName, envelope)
{
    DoIt_count = 0 ; 
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

#ifdef PMTFASTSIM_STANDALONE
    ModelTrigger_count = 0 ; 
    jpmt = new JPMT ; 
#endif

    InitOpticalParameters(envelope_phys);

    m_multi_film_model = new MultiFilmModel(4);

}
#ifdef PMTFASTSIM_STANDALONE

const plog::Severity junoPMTOpticalModel::LEVEL       = SLOG::EnvLevel("junoPMTOpticalModel", "DEBUG" ); 

void junoPMTOpticalModel::Save(const char* fold)
{
    // this is a workaround allowing SPhoton_Debug.h to stay headeronly 
    SPhoton_Debug<'A'>::Save(fold);   
}


#endif

junoPMTOpticalModel::~junoPMTOpticalModel(){}

G4bool junoPMTOpticalModel::IsApplicable(const G4ParticleDefinition & particleType)
{
    return (&particleType == G4OpticalPhoton::OpticalPhotonDefinition());
}








/**
junoPMTOpticalModel::ModelTrigger 
-------------------------------------

Current Bizarre Geometry and Trigger

* 2 Pyrex  : pmt_solid, body_solid
* 2 Vacuum : inner1, inner2 

                   
            ...          ... 
       ... |                  ...
     ...   |  inner1              ...
    ...    +                      ...
    +++---------------------------+++
    ...                           ...
     ...     inner2              ...
       ...                    ...
             ...         ...


whereAmI == kInGlass:true   (actually kNotUpperVacuum and from early exit NotLowerVacuum)

     dist1 kInfinity :  
         ray does not intersect inner1     -> false

     dist1 > dist2:true   
         ray hits inner2 before inner1  -> false

     dist1 > dist2:false
         equal distance or inner1 is closer -> true   

     SUMMARY : FROM GLASS THE 1ST INTERSECT NEEDS TO BE INNER1

whereAmI == kInGlass:false    (actually kUpperVacuum )

     requires _inner2_solid->DistanceToIn  to be kInfinity -> true 
     this means that the ray is heading back to the photocathode 
     but thats a clumsy way of doing it

     SUMMARY : FROM UPPERVAC MUST NOT INTERSECT LOWERVAC 
**/

G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
{
    G4bool ret = ModelTrigger_(fastTrack) ; // use wrapper to cope with spagetti returns
#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL) << " ModelTrigger_count " << std::setw(3) << ModelTrigger_count << " Result : " << ( ret ? "YES" : "NO" ) ;  
    ModelTrigger_count += 1 ; 
#endif
    return ret ; 

}
G4bool junoPMTOpticalModel::ModelTrigger_(const G4FastTrack &fastTrack)
{
#ifdef PMTFASTSIM_STANDALONE
     /*
     LOG(LEVEL)
         << F4::Desc(fastTrack, "Hdr,Vec" )
         << F4::DescDist(fastTrack, nullptr) 
         << std::endl
         << F4::DescDist(fastTrack, _inner1_solid ) 
         << std::endl
         << F4::DescDist(fastTrack, _inner2_solid ) 
         << std::endl 
         ;
     */
#endif

    if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner2_phys)
    {
#ifdef PMTFASTSIM_STANDALONE
        LOG(LEVEL) << " NOT inner2_phys EARLY EXIT " ;  
        // backwards photons have to get out of inner2 before get passed this early exit   
#endif
        return false;
    }

    envelope_solid = fastTrack.GetEnvelopeSolid();

    pos     = fastTrack.GetPrimaryTrackLocalPosition();
    dir     = fastTrack.GetPrimaryTrackLocalDirection();
    pol     = fastTrack.GetPrimaryTrackLocalPolarization();
    time    = fastTrack.GetPrimaryTrack()->GetGlobalTime();
    energy  = fastTrack.GetPrimaryTrack()->GetKineticEnergy();


    if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner1_phys){  
        whereAmI = kInVacuum;   // SCB: should be kUpperVacuum
    }else{
        whereAmI = kInGlass;    // SCB: should be kNotUpperVacuum
    }

#ifndef PMTFASTSIM_STANDALONE
    if(whereAmI == kInGlass){  // kNotUpperVacuum
        dist1 = _inner1_solid->DistanceToIn(pos, dir);
        dist2 = _inner2_solid->DistanceToIn(pos, dir);

        if(dist1 == kInfinity){
            return false;
        }else if(dist1>dist2){
            return false;
        }else{
            return true;
        }
    }else{                    // kUpperVacuum 
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


    SFastSim_Debug dbg ; 

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

    int photon_id = F4::PhotonId(fastTrack) ; 
    dbg.PhotonId = double(photon_id) ; 
  
    dbg.add() ; 

    LOG(LEVEL) 
        << "junoPMTOpticalModel::ModelTrigger"
        << " photon_id " << std::setw(6) << photon_id       
        << " ret " << ret
        ;  
   
    return ret ; 
#endif
}





/**
junoPMTOpticalModel::DoIt
---------------------------

1. get track, lookup pmtid, pmtcat 
2. lookup refractive indices and qe 
3. prep the stack params, in order depending on whereAmI
4. advance pos along dir by dist1, and advance time appropriately for the refractive index 


**/
void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
{
    _photon_energy  = energy;    // SCB : strange place to do this here, better to do it where the energy comes from 
    _wavelength     = twopi*hbarc/energy;

    const G4Track* track = fastTrack.GetPrimaryTrack();
    int pmtid  = get_pmtid(track);

#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL) << " DoIt_count " << DoIt_count << "  pmtid " << pmtid ; 
    setEnergyThickness(energy); 
#else
    n_glass    = _rindex_glass->Value(_photon_energy);

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
#ifdef PMTFASTSIM_STANDALONE
    G4ThreeVector surface_normal = norm ;  
    minus_cos_theta = dir*norm ;  // NB before the flips 
#endif

    if(whereAmI == kInGlass){
        norm *= -1.0;
    }
    _cos_theta1 = dir*norm;

    if(_cos_theta1 < 0.){
        _cos_theta1 = -_cos_theta1;
        norm = -norm;
    }

    /**
    SCB : nasty multiple flips to normal vector, 
          simpler to have separate oriented_normal 
          and keep the original geometrical normal as fixed 
          and pointing outwards
    **/

    _aoi = acos(_cos_theta1)*360./twopi;

    CalculateCoefficients();

  
    // E_s2 : S-vs-P power fraction : signs make no difference as squared
    G4double E_s2 = _sin_theta1 > 0. ? (pol*dir.cross(norm))/_sin_theta1 : 0. ; 
    E_s2 *= E_s2;


    LOG(LEVEL)
        << " DoIt_count " << DoIt_count 
        << " _sin_theta1 " << std::fixed << std::setw(10) << std::setprecision(5) << _sin_theta1 
        << " norm " << norm 
        << " pol*dir.cross(norm) " << std::fixed << std::setw(10) << std::setprecision(5) << pol*dir.cross(norm)
        << " E_s2 " << std::fixed << std::setw(10) << std::setprecision(5) << E_s2 
        ; 

    /**
    _sin_theta1 comes from sqrt(1.- _cos_theta1*_cos_theta1) 
    so it cannot be negative, but it will be zero at normal incidence 
    where -cos(theta) is -1 and +1 and where dir.cross(norm) will be very small 
    This is just expressing that S and P loose meaning at normal incidence
    so setting E_s2 to 0 artifically picks P for normal incidence.
    
    BUT that doesnt matter as s/p coeffs are equal at normal incidence anyhow::

        fA_s = fA_p 
        fR_s = fR_p 
        fT_s = fT_p 

    Initially though this  E_s2 calc was assuming are on Pyrex side of the border, 
    but thats not the case because the _sin_theta1 can be for either side 

    TODO: compare with  qsim.h propagate_at_boundary + G4OpBoundaryProcess 
    **/

    G4double T = fT_s*E_s2 + fT_p*(1.0-E_s2);
    G4double R = fR_s*E_s2 + fR_p*(1.0-E_s2);
    G4double A = 1.0 - (T+R);
    G4double An = 1.0 - (fT_n+fR_n);
    G4double D = _qe/An;  // TODO: get some explanation for this 


    LOG(LEVEL)
        << " DoIt_count " << DoIt_count 
        << " E_s2 " << std::fixed << std::setw(10) << std::setprecision(5) << E_s2
        << " fT_s " << std::fixed << std::setw(10) << std::setprecision(5) << fT_s 
        << " 1-E_s2 " << std::fixed << std::setw(10) << std::setprecision(5) << (1.-E_s2)
        << " fT_p " << std::fixed << std::setw(10) << std::setprecision(5) << fT_p 
        << " T " << std::fixed << std::setw(10) << std::setprecision(5) << T
        ;

    LOG(LEVEL)
        << " DoIt_count " << DoIt_count 
        << " E_s2 " << std::fixed << std::setw(10) << std::setprecision(5) << E_s2
        << " fR_s " << std::fixed << std::setw(10) << std::setprecision(5) << fR_s 
        << " 1-E_s2 " << std::fixed << std::setw(10) << std::setprecision(5) << (1.-E_s2)
        << " fR_p " << std::fixed << std::setw(10) << std::setprecision(5) << fR_p 
        << " R " << std::fixed << std::setw(10) << std::setprecision(5) << R
        << " A " << std::fixed << std::setw(10) << std::setprecision(5) << A
        ;



    //  SCB 
    //
    //  1.  note than fT_n fR_n do not flip the stack (unlike fT_s fTp fR_s fR_p which do flip the stack)
    //  2.  Q: Why does detection use _qe/An (why reciprocal and why indep of aoi and without flipping stack) 
    //         but everything else uses angular dependent A,R,T ?
    //
    //      A: Presumably anything can be justified based on what the definition of the QE input is, 
    //         and the fact that "backwards" _qe gets set to zero anyhow. 
    //  
    //         NOT CONVINCED BY THAT : AS escape_fac will be > 1 for An < _qe
    //         which would mean that rand_escape < escape_fac always 
    //
    //         When An is small (little absorption) eg 0.1 escape fac gets scaled to _qe*10 
    //         which then gets compared to rand_escape a random number in [0,1]
    //         SO THAT WOULD MEAN THE LESS ABSORPTION THE MORE DETECTION : WHICH IS SURELY WRONG 
    //         _qe*An would surely be more reasonable ? 
    //
    //         TODO: incorporate An into LayrTest.py plotting    
 
    //
    if(D > 1.)
    {
        G4cout<<"junoPMTOpticalModel: QE is larger than absorption coeff."<<G4endl;
    }

    G4double u0 = G4UniformRand(); 
    G4double u1 = G4UniformRand();

    /**  
       0         A         A+R         1
       |---------+----------+----------|  u0
          D/A         R          T
          u1
    **/

    char status = '?' ;
    if(      u0 < A)    status = u1 < D ? 'D' : 'A' ; 
    else if( u0 < A+R)  status = 'R' ; 
    else                status = 'T' ;  

    int u0_idx = UUniformRand::Find(u0, SEvt::UU);     
    int u1_idx = UUniformRand::Find(u1, SEvt::UU);   
       
    LOG(LEVEL) 
         << " u0 " << UUniformRand::Desc(u0, SEvt::UU) 
         << " u0_idx " << u0_idx 
         << " A "   << std::setw(10) << std::fixed << std::setprecision(4) << A 
         << " A+R " << std::setw(10) << std::fixed << std::setprecision(4) << (A+R) 
         << " T "   << std::setw(10) << std::fixed << std::setprecision(4) << T 
         << " status " 
         << status 
         << " DECISION " 
         ;    
    LOG(LEVEL) 
         << " u1 " << UUniformRand::Desc(u1, SEvt::UU ) 
         << " u1_idx " << u1_idx 
         << " D " << std::setw(10) << std::fixed << std::setprecision(4) << D 
         ;    


    if( status == 'A' || status == 'D' )
    {
        fastStep.ProposeTrackStatus(fStopAndKill);
        if(status == 'D' ) fastStep.ProposeTotalEnergyDeposited(_photon_energy);
    }
    else if( status == 'R' || status == 'T' )
    {
        switch(status)
        {
            case 'R': Reflect() ; break ; 
            case 'T': Refract() ; break ; 
        } 
        if( status == 'T' ) whereAmI =  whereAmI == kInGlass ? kInVacuum : kInGlass ; 
        UpdateTrackInfo(fastStep);
    }


#ifdef PMTFASTSIM_STANDALONE
    SPhoton_Debug<'A'> dbg ; 

    LOG(LEVEL)
       << " time " << time 
       << " dbg.Count " << dbg.Count()
       << " dbg.Name "  << dbg.Name()
       ;  

    dbg.pos  = pos ; 
    dbg.time = time ;  
   
    dbg.mom = dir ;  
    dbg.iindex = u0_idx ; 

    dbg.pol = pol ;  
    dbg.wavelength = _wavelength/nm ; 

    dbg.nrm = surface_normal ;  
    dbg.spare = 0. ; 

    // HMM: want to incorporate u0 from u4/InstrumentedG4OpBoundaryProcess but no access from here
    // so added SOpBoundaryProcess : so can talk to InstrumentedG4OpBoundaryProcess 
    // without depending on u4 
    SOpBoundaryProcess* bop = SOpBoundaryProcess::Get(); 
    dbg.u0 = bop->getU0() ; 
    dbg.u0_idx = bop->getU0_idx() ; 
  
    dbg.add(); 


    spho* label = STrackInfo<spho>::GetRef(track);  
    LOG_IF(fatal, !label) 
        << " all photon tracks must be labelled " 
        << " track " << track 
        << std::endl  
        << STrackInfo<spho>::Desc(track) 
        ; 

    assert( label ); 
    label->uc4.w = status ; 


    LOG(LEVEL)
        << "junoPMTOpticalModel::DoIt"
        << " dir " << dir 
        << " norm " << norm
        << " _cos_theta1  " << _cos_theta1 
        << " _sin_theta1  " << _sin_theta1 
        << " E_s2 " << E_s2
        << " (fT_s+fT_p)/2 " << (fT_s+fT_p)/2.
        << " (fR_s+fR_p)/2 " << (fR_s+fR_p)/2.
        << " _aoi " << _aoi 
        << " T " << T 
        << " R " << R 
        << " A " << A 
        << " status " << status 
        ; 

    Stack<double,4> stack ; 
    getCurrentStack(stack); 

    LOG(LEVEL)
        << "junoPMTOpticalModel::DoIt"
        << " status " 
        << status
        << " stack.art "
        << std::endl 
        << stack.art
        //<< std::endl 
        //<< " stack "
        //<< std::endl 
        //<< stack 
        ; 
#endif

    DoIt_count += 1 ; 
    return;
}

void junoPMTOpticalModel::CalculateCoefficients()
{
    G4complex one(1., 0.);
    _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1); // SCB: _sin_theta1 constrained 0.->1. inclusive
    _sin_theta4 = _n1 * _sin_theta1/_n4;
    _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);

    m_multi_film_model->SetWL(_wavelength/nm); // SCB: changed to nm (from m) NB unit must match thickness
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


    // CROSS CHECK 
    {
        StackSpec<double,4> spec ;

        spec.ls[0].d  = 0. ;
        spec.ls[1].d  = _d2 ; 
        spec.ls[2].d  = _d3 ; 
        spec.ls[3].d = 0. ;

        spec.ls[0].nr = _n1 ; 
        spec.ls[0].ni = 0. ; 

        spec.ls[1].nr = _n2 ; 
        spec.ls[1].ni = _k2 ; 

        spec.ls[2].nr = _n3 ; 
        spec.ls[2].ni = _k3 ; 

        spec.ls[3].nr = _n4 ; 
        spec.ls[3].ni = 0 ; 

        Stack<double,4> stack(_wavelength/nm, -_cos_theta1, spec );

        LOG(LEVEL) 
            << " DoIt_count " << DoIt_count
            << " stack crossheck "
            << stack
            ; 
    } 


    // SCB: HUH NormalART coeff do not flip the stack, but the above do  
    // the equivalent with Layr.h:Stack is to use minus_cos_theta=-1. 

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

/**
junoPMTOpticalModel::InitOpticalParameters
--------------------------------------------

Called from ctor with envelope_phys being passed in as ctor argument 
coming for eg HamamatsuR12860PMTManager::helper_fast_sim where 
it is body_phys (the 2nd Pyrex volume)  

Current four volume geometry ~features two fake boundaries
(Pyrex/Pyrex and Vacuum/Vacuum) plus has one coincident face
and two nearly coincident: the 2nd Pyrex and inner1-Vacuum and inner2-Vacuum 
are separated by only 1e-3 mm):: 

UsePMTOpticalModel:1

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

UsePMTOpticalModel:0

     +---------------pmt-Pyrex----------------+
     | +-------------body-Pyrex-------------+ |
     | |                                    | |
     | |                                    | |
     | |     +------------------------+     | |
     | |     |                        |     | |
     | |     |                        |     | |
     | |     |        inner1-Vacuum   |     |-|
     | |     |                        |     |1e-3
     | |     |                        |     | |
     | |     +~~coincident~face~~~~~~~+     | |
     | |     |                        |     | |
     | |     |                        |     | |
     | |     |        inner2-Vacuum   |     | |
     | |     |                        |     | |
     | |     |                        |     | |
     | |     +------------------------+     | |
     | |                                    | |
     | |                                    | |
     | +------------------------------------+ |
     +----------------------------------------+





Using square PMT as difficult to draw ellipsoids in ascii. 
**/

void junoPMTOpticalModel::InitOpticalParameters(G4VPhysicalVolume* envelope_phys)
{
    G4LogicalVolume* envelope_log 
        = envelope_phys->GetLogicalVolume();
    G4MaterialPropertiesTable* glass_pt 
        = envelope_log->GetMaterial()->GetMaterialPropertiesTable();
    
    // SCB: when shift to single inner vacuum as envelope will need to GetMotherLogical to access the pyrex 

    _rindex_glass   = glass_pt->GetProperty("RINDEX");
    _inner1_phys    = envelope_log->GetDaughter(0);
    _inner1_solid   = _inner1_phys->GetLogicalVolume()->GetSolid();
    _rindex_vacuum  = _inner1_phys->GetLogicalVolume()->GetMaterial()
                                  ->GetMaterialPropertiesTable()->GetProperty("RINDEX");

    _inner2_phys    = envelope_log->GetDaughter(1);
    _inner2_solid   = _inner2_phys->GetLogicalVolume()->GetSolid();

#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL)
        << " envelope_log " << envelope_log
        << " glass_pt " << glass_pt
        << " _rindex_glass " << _rindex_glass
        << " _inner1_phys " << _inner1_phys
        << " _inner1_solid " << _inner1_solid
        << " _rindex_vacuum " << _rindex_vacuum
        << " _inner2_phys " << _inner2_phys
        << " _inner2_solid " << _inner2_solid
        ;
#endif

}

/**
junoPMTOpticalModelSimple::InitOpticalParameters
---------------------------------------------------

Two volume geometry featuring no fake boundaries and 
no coincident faces. Inner upper hemi is selected by "z > 0",
it is the simplest (and hence fastest) possible geometry::

     +---------------pmt-Pyrex----------------+
     |                                        |
     |                                        |
     |                                        |
     |       +~-~-~inner-Vacuum-~-~-~-+       |
     |       !                        !       |
     |       !       z > 0            !       |
     |       !                        !       |      
     |       !                        !       |      
     |       !                        !       |      
     |       +    -      -    -   -   +       |
     |       |                        |       |
     |       |                        |       |
     |       |                        |       |
     |       |                        |       |
     |       |                        |       |
     |       +------------------------+       |
     |                                        |
     |                                        |
     |                                        |
     +----------------------------------------+

**/


/**
junoPMTOpticalModel::Reflect 
-----------------------------

Comparing to qsim::propagate_at_boundary (port of G4OpBoundaryProcess) 
this is not the same polarization in both Reflect and Refract. 

TODO: numerical comparison, see how big the difference 

**/

void junoPMTOpticalModel::Reflect()
{
    dir -= 2.*(dir*norm)*norm;
    pol -= 2.*(pol*norm)*norm;
}

/**
junoPMTOpticalModel::Refract
-----------------------------

When going from higher index (Pyrex) to lower index (Vacuum) 
the refraction should be away from the normal.

When going from lower index (Vacuum) to higher index (Pyrex) 
the refraction should be towards the normal.

**/

void junoPMTOpticalModel::Refract()
{
#ifdef PMTFASTSIM_STANDALONE

    LOG(LEVEL)
       << " time " << time 
       << " pos " << pos 
       << " norm " << norm 
       ;
    LOG(LEVEL)
       << " _n1 " << _n1 
       << " _n4 " << _n4 
       << " _cos_theta1 " << _cos_theta1
       << " _cos_theta4 " << _cos_theta4
       ;

    LOG(LEVEL)
       << " bef "
       << " dir " << dir 
       << " pol " << pol 
       ;
#endif

    dir = (real(_cos_theta4) - _cos_theta1*_n1/_n4)*norm + (_n1/_n4)*dir;
    pol = (pol-(pol*dir)*dir).unit();

#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL)
       << " aft "
       << " dir " << dir 
       << " pol " << pol 
       ;
#endif

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




#ifdef PMTFASTSIM_STANDALONE
/**
junoPMTOpticalModel::setEnergyThickness
-----------------------------------------

Does jpmt lookups depending on energy_eV setting n_glass, n_coating, d_coating, ... 

**/

void junoPMTOpticalModel::setEnergyThickness( double energy )
{
    _wavelength     = twopi*hbarc/energy;
    double energy_eV = energy/eV ; 
    int pmtcat = JPMT::HAMA ; 


    n_glass          = jpmt->get_rindex( pmtcat, JPMT::L0, JPMT::RINDEX, energy_eV ); 

    n_coating        = jpmt->get_rindex( pmtcat, JPMT::L1, JPMT::RINDEX, energy_eV ); 
    k_coating        = jpmt->get_rindex( pmtcat, JPMT::L1, JPMT::KINDEX, energy_eV ); 

    n_photocathode   = jpmt->get_rindex( pmtcat, JPMT::L2, JPMT::RINDEX, energy_eV ); 
    k_photocathode   = jpmt->get_rindex( pmtcat, JPMT::L2, JPMT::KINDEX, energy_eV ); 


    d_coating      = jpmt->get_thickness_nm( pmtcat, JPMT::L1 ); 
    d_photocathode = jpmt->get_thickness_nm( pmtcat, JPMT::L2 ); 

    LOG(LEVEL)
        << " energy " << energy
        << " energy_eV " << energy_eV
        << " _wavelength  " << _wavelength 
        << " _wavelength/nm  " << _wavelength/nm 
        << " n_glass " << n_glass
        << " n_coating " << n_coating
        << " k_coating " << k_coating
        << " n_photocathode " << n_photocathode
        << " k_photocathode " << k_photocathode
        ;
}

/**
junoPMTOpticalModel::setMinusCosTheta
---------------------------------------

Sets whereAmI based on the sign of minus_cos_theta
(hmm correct normal is vital). 

Populates _n1, _n2, _k2, _d2, ... depending on whereAmI.
The order is flipped when whereAmI is not kInVacuum.

**/

void junoPMTOpticalModel::setMinusCosTheta( double minus_cos_theta_ )
{
    minus_cos_theta = minus_cos_theta_ ;
    whereAmI = minus_cos_theta < 0. ? kInGlass : kInVacuum ; 
    _cos_theta1 = minus_cos_theta < 0. ? -minus_cos_theta : minus_cos_theta ; 
    _aoi = acos(_cos_theta1)*360./twopi;

    if(whereAmI == kInGlass)
    {
        _n1 = n_glass;
        _n2 = n_coating;
        _k2 = k_coating;
        _d2 = d_coating;
        _n3 = n_photocathode;
        _k3 = k_photocathode;
        _d3 = d_photocathode;
        _n4 = n_vacuum;
    }
    else
    {
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
} 

/**
junoPMTOpticalModel::getCurrentStack translating from m_multi_film_model
--------------------------------------------------------------------------

1. calls m_multi_film_model GetART which calls MultiFilmModel::Calculate
   which re-initializes the entire stack of layers. Thats bad design. 

2. populates the stack parameter with the ART and layers 
   translated from m_multi_film_model

**/

void junoPMTOpticalModel::getCurrentStack(Stack<double,4>& stack) const 
{
    ART art1 = m_multi_film_model->GetART(); // re does MultiFilmModel::Calculate
    double wavelength_nm =  m_multi_film_model->wavelength ; 

    ART_<double>& art = stack.art ; 
    Layr<double>& comp = stack.comp ; 
    Layr<double>* ll = &stack.ll[0] ; 

    art = {} ; 
    art.R_s = art1.R_s ; 
    art.R_p = art1.R_p ; 
    art.T_s = art1.T_s ; 
    art.T_p = art1.T_p ; 
    art.A_s = art1.A_s ; 
    art.A_p = art1.A_p ; 
    art.R   = art1.R ; 
    art.T   = art1.T ; 
    art.A   = art1.A ; 
    art.A_R_T = art1.A + art1.T + art1.R  ; 
    art.wl   = wavelength_nm ;
    art.mct  = minus_cos_theta ;   // from last DoIt

    comp = {} ; 
    comp.rs = m_multi_film_model->rs ; 
    comp.rp = m_multi_film_model->rp ; 
    comp.ts = m_multi_film_model->ts ; 
    comp.tp = m_multi_film_model->tp ; 

    Matrix* Ms = m_multi_film_model->Ms ; 
    Matrix* Mp = m_multi_film_model->Mp ; 

    comp.S.M00 = Ms->matrix.M00 ; 
    comp.S.M01 = Ms->matrix.M01 ; 
    comp.S.M10 = Ms->matrix.M10 ; 
    comp.S.M11 = Ms->matrix.M11 ;

    comp.P.M00 = Mp->matrix.M00 ; 
    comp.P.M01 = Mp->matrix.M01 ; 
    comp.P.M10 = Mp->matrix.M10 ; 
    comp.P.M11 = Mp->matrix.M11 ;

    std::vector<Layer*>& vlayers = m_multi_film_model->optical_system->layers ; 
    assert( vlayers.size() == 4 ); 

    // MultiFilmModel::Calculate

    for(int i=0 ; i < 4 ; i++)
    {
        Layr<double>& l = ll[i] ; 
        l = {} ; 

        Layer& layer = *vlayers[i] ; 
        ThinLayer* thin  = dynamic_cast<ThinLayer*>(&layer);

        l.d  = ( thin ? thin->thickness : 0. ) ;
        l.n  = layer.material->n ; 
        l.st = layer.parameter.sin_theta ;   
        l.ct = layer.parameter.cos_theta ;   

        l.rs = layer.parameter.rs_ij ;
        l.rp = layer.parameter.rp_ij ;
        l.ts = layer.parameter.ts_ij ;
        l.tp = layer.parameter.tp_ij ;
        
        Matrix* Ms = layer.Ms ; 
        Matrix* Mp = layer.Mp ; 

        l.S.M00 = Ms->matrix.M00 ; 
        l.S.M01 = Ms->matrix.M01 ;
        l.S.M10 = Ms->matrix.M10 ;
        l.S.M11 = Ms->matrix.M11 ;

        l.P.M00 = Mp->matrix.M00 ; 
        l.P.M01 = Mp->matrix.M01 ;
        l.P.M10 = Mp->matrix.M10 ;
        l.P.M11 = Mp->matrix.M11 ;
    } 
}


/**
junoPMTOpticalModel::CalculateCoefficients
--------------------------------------------

1. calls setEnergyThickness and setMinusCosTheta
2. loads m_multi_film_model with param 
3. calls getCurrentStack translating m_multi_film_model outputs into stack 
4. sets the output arguments, copying from the stack 

**/
void junoPMTOpticalModel::CalculateCoefficients(
      ART_<double>& art, 
      Layr<double>& comp, 
      Layr<double>* ll, 
      double energy, 
      double minus_cos_theta )
{
    setEnergyThickness(energy); 
    setMinusCosTheta(minus_cos_theta); 

    G4complex one(1., 0.);
    _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1);
    _sin_theta4 = _n1 * _sin_theta1/_n4;
    _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);

    m_multi_film_model->SetWL(_wavelength/nm);  // CHANGE TO MORE REASONABLE LENGTH UNITS : nm (not m)
    m_multi_film_model->SetAOI(_aoi);

    m_multi_film_model->SetLayerPar(0, _n1);
    m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    m_multi_film_model->SetLayerPar(3, _n4);

    Stack<double,4> stack ; 
    getCurrentStack(stack); 

    art = stack.art ; 
    comp = stack.comp ; 
    for(int i=0 ; i < 4 ; i++) ll[i] = stack.ll[i] ;  

    LOG(LEVEL)
         << " energy/eV " << energy/eV
         ;
}
// PMTFASTSIM_STANDALONE
#endif

