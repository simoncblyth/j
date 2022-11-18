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
#include "JPMT.h"
#include "Layr.h"

#include "OpticalSystem.h"
#include "Matrix.h"
#include "Layer.h"

#include "SLOG.hh"
#include "SFastSim_Debug.hh"
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

#ifdef PMTFASTSIM_STANDALONE
    INSTANCE = this ; 
    jpmt = new JPMT ; 
#endif

    InitOpticalParameters(envelope_phys);

    m_multi_film_model = new MultiFilmModel(4);

}
#ifdef PMTFASTSIM_STANDALONE
const plog::Severity junoPMTOpticalModel::LEVEL = SLOG::EnvLevel("junoPMTOpticalModel", "DEBUG" ); 
junoPMTOpticalModel* junoPMTOpticalModel::INSTANCE = nullptr ; 
#endif

junoPMTOpticalModel::~junoPMTOpticalModel(){}

G4bool junoPMTOpticalModel::IsApplicable(const G4ParticleDefinition & particleType)
{
    bool ret = (&particleType == G4OpticalPhoton::OpticalPhotonDefinition());
#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL) << "junoPMTOpticalModel::IsApplicable " << ret ;  
#endif
    return ret ; 
}

#ifdef PMTFASTSIM_STANDALONE
const char* junoPMTOpticalModel::EInside_( EInside in ) // static
{
    const char* s = nullptr ;
    switch(in)
    {
        case kOutside: s = kOutside_ ; break ; 
        case kSurface: s = kSurface_ ; break ; 
        case kInside:  s = kInside_  ; break ; 
    }                     
    return s ;
}   
G4double junoPMTOpticalModel::Distance_(const G4VSolid* solid, const G4ThreeVector& pos, const G4ThreeVector& dir, EInside* in ) // static
{
    EInside inside = solid->Inside(pos) ;
    if(in) *in = inside ; 
    G4double t = kInfinity ; 
    switch(inside)
    {   
        case kInside:  t = solid->DistanceToOut( pos, dir ) ; break ; 
        case kSurface: t = solid->DistanceToOut( pos, dir ) ; break ; 
        case kOutside: t = solid->DistanceToIn(  pos, dir ) ; break ; 
        default:  assert(0) ; 
    }   
    return t ; 
}
std::string junoPMTOpticalModel::DescDist(const G4FastTrack &fastTrack, const G4VSolid* solid_ ) // static
{
    const G4VSolid* solid = solid_ ? solid_ : fastTrack.GetEnvelopeSolid();
    G4ThreeVector lpos = fastTrack.GetPrimaryTrackLocalPosition();
    G4ThreeVector ldir = fastTrack.GetPrimaryTrackLocalDirection();

    EInside inside = kOutside ;
    G4double dist = Distance_(solid, lpos, ldir, &inside ); 
    G4String solidName = solid->GetName() ; // this return by value always surprises me 
   
    std::stringstream ss ; 

    ss << "DescDist" 
       << " " << std::setw(20) << solidName
       ; 

    if( dist == kInfinity ) 
    {
        ss << " " << std::setw(10) << " MISS " ; 
    }
    else   
    {
        G4ThreeVector dpos = lpos+dist*ldir ; 
        ss << " " << std::fixed << std::setprecision(4) << std::setw(10) << dist
           << " " << std::setw(15) << EInside_(inside) 
           << " dpos " << std::setw(20) << dpos 
           ;
    }
    std::string s = ss.str() ; 
    return s ; 
}

std::string junoPMTOpticalModel::Desc(const G4FastTrack &fastTrack, const char* opt) // static
{
    const G4Track* primaryTrack = fastTrack.GetPrimaryTrack() ; 
    const G4VSolid* envelopeSolid = fastTrack.GetEnvelopeSolid();
    G4String envelopeSolidName = envelopeSolid->GetName() ; // this return by value always surprises me 
    const G4VPhysicalVolume* volume = primaryTrack->GetVolume() ; 
    const G4String& volumeName = volume->GetName() ; 

    std::stringstream ss ; 
    ss << "junoPMTOpticalModel::Desc" << std::endl ; 

    if( opt && strstr(opt, "Hdr" )) ss
        << " Hdr " 
        << std::endl
        << " primaryTrack " << primaryTrack
        << " envelopeSolid " << envelopeSolid
        << " envelopeSolidName " << envelopeSolidName
        << " volume " << volume
        << " volumeName " << volumeName
        << std::endl
        ;

    G4ThreeVector lpos = fastTrack.GetPrimaryTrackLocalPosition();
    G4ThreeVector ldir = fastTrack.GetPrimaryTrackLocalDirection();
    G4ThreeVector lpol = fastTrack.GetPrimaryTrackLocalPolarization();

    if( opt && strstr(opt, "Vec" )) ss
        << " Vec " 
        << std::endl
        << " lpos " << lpos << std::endl 
        << " ldir " << ldir << std::endl 
        << " lpol " << lpol << std::endl 
        << std::endl 
        ;

    std::string s = ss.str(); 
    return s ; 
}

#endif


/**
junoPMTOpticalModel::ModelTrigger 
-----------------------------------


Possible Cleaner Trigger : for single inner vacuum which is envelope
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Simply trigger when intersect position z is +ve  
* sign of dot product tells you which side of boundary

::
                           
                  Y  .          . Y
                . |              /   .
              .   |             /       .
             .    +            /          .
   ----------+          inner /           +----------
             .               /           .
              .             +-----------N
                .                    .
                     .          .


Current Bizarre Trigger
~~~~~~~~~~~~~~~~~~~~~~~~~

To miss inner2 the ray direction .z must be +ve 
So can replace two geometry queries with dir_local.z() > 0::

                   
             .          .
        . |                  .
      .   |  inner1              .
     .    +                      .
     +---------------------------+
     .                           .
      .     inner2              .
        .                    .
             .          .

Actually even better to use simple single inner vacuum then can 
simply base on the sign of the z of the envelope intersect 
position. Note its vacuum so no scattering or absorption in there. 


whereAmI == kInGlass:true   (actually kNotUpperVacuum and from early exit NotLowerVacuum)

     dist1 kInfinity :  
         ray does not intersect inner1     -> false

     dist1 > dist2:true   
         ray hits inner2 before inner1  -> false

     dist1 > dist2:false
         equal distance or inner1 is closer -> true   


whereAmI == kInGlass:false    (actually kUpperVacuum )

     requires _inner2_solid->DistanceToIn  to be kInfinity -> true 
     this means that the ray is heading back to the photocathode 
     but thats a clumsy way of doing it
**/

G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
{
#ifdef PMTFASTSIM_STANDALONE
     LOG(LEVEL)
         << Desc(fastTrack, "Hdr,Vec" )
         << DescDist(fastTrack, nullptr) 
         << std::endl
         << DescDist(fastTrack, _inner1_solid ) 
         << std::endl
         << DescDist(fastTrack, _inner2_solid ) 
         << std::endl 
         ;
#endif

    if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner2_phys)
    {
#ifdef PMTFASTSIM_STANDALONE
        LOG(LEVEL) << "junoPMTOpticalModel::ModelTrigger NOT inner2_phys EARLY EXIT " ;  
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
    dbg.d = 0. ; 
  
    dbg.add() ; 

#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL) << "junoPMTOpticalModel::ModelTrigger ret " << ret  ;  
#endif
   
    return ret ; 
#endif
}


#ifdef PMTFASTSIM_STANDALONE
void junoPMTOpticalModel::setEnergyThickness( double energy )
{
    _wavelength     = twopi*hbarc/energy;
    double energy_eV = energy/eV ; 

    n_glass          = jpmt->get_rindex( JPMT::HAMA, JPMT::L0, JPMT::RINDEX, energy_eV ); 

    n_coating        = jpmt->get_rindex( JPMT::HAMA, JPMT::L1, JPMT::RINDEX, energy_eV ); 
    k_coating        = jpmt->get_rindex( JPMT::HAMA, JPMT::L1, JPMT::KINDEX, energy_eV ); 
    d_coating  = jpmt->get_thickness_nm( JPMT::HAMA, JPMT::L1 ); 

    n_photocathode       = jpmt->get_rindex( JPMT::HAMA, JPMT::L2, JPMT::RINDEX, energy_eV ); 
    k_photocathode       = jpmt->get_rindex( JPMT::HAMA, JPMT::L2, JPMT::KINDEX, energy_eV ); 
    d_photocathode = jpmt->get_thickness_nm( JPMT::HAMA, JPMT::L2 ); 

    LOG(LEVEL)
        << "junoPMTOpticalModel::setEnergyThickness" 
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

void junoPMTOpticalModel::setMinusCosTheta( double minus_cos_theta_ )
{
    minus_cos_theta = minus_cos_theta_ ;
    whereAmI = minus_cos_theta < 0. ? kInGlass : kInVacuum ; 
    _cos_theta1 = minus_cos_theta < 0. ? -minus_cos_theta : minus_cos_theta ; 
    _aoi = acos(_cos_theta1)*360./twopi;

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
} 


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

    std::cout 
         << "junoPMTOpticalModel::CalculateCoefficients"
         << " energy/eV " << energy/eV
         << std::endl
         ;
}
#endif

void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
{
    _photon_energy  = energy;
    _wavelength     = twopi*hbarc/energy;

    const G4Track* track = fastTrack.GetPrimaryTrack();
    int pmtid  = get_pmtid(track);

#ifdef PMTFASTSIM_STANDALONE
    LOG(LEVEL) << "junoPMTOpticalModel::DoIt pmtid " << pmtid ; 
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
    if(whereAmI == kInGlass){
        norm *= -1.0;
    }

#ifdef PMTFASTSIM_STANDALONE
    minus_cos_theta = dir*norm ; 
    _cos_theta1 = minus_cos_theta ;
#else
    _cos_theta1 = dir*norm;
#endif

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


#ifdef PMTFASTSIM_STANDALONE
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
        ; 

    Stack<double,4> stack ; 
    getCurrentStack(stack); 

    LOG(LEVEL)
        << "junoPMTOpticalModel::DoIt"
        << " stack.art "
        << std::endl 
        << stack.art
        << std::endl 
        << " stack "
        << std::endl 
        << stack 
        ; 

#endif

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

#ifdef PMTFASTSIM_STANDALONE
    std::cout << "junoPMTOpticalModel::InitOpticalParameters"
              << " envelope_log " << envelope_log
              << " glass_pt " << glass_pt
              << " _rindex_glass " << _rindex_glass
              << " _inner1_phys " << _inner1_phys
              << " _inner1_solid " << _inner1_solid
              << " _rindex_vacuum " << _rindex_vacuum
              << " _inner2_phys " << _inner2_phys
              << " _inner2_solid " << _inner2_solid
              << std::endl 
              ;
#endif

}

void junoPMTOpticalModel::Reflect()
{
    dir -= 2.*(dir*norm)*norm;
    pol -= 2.*(pol*norm)*norm;
    // TODO: compare this pol with what G4OpBoundaryProcess would do 
}

void junoPMTOpticalModel::Refract()
{
    dir = (real(_cos_theta4) - _cos_theta1*_n1/_n4)*norm + (_n1/_n4)*dir;
    pol = (pol-(pol*dir)*dir).unit();
    // TODO: compare this pol with what G4OpBoundaryProcess would do 
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
