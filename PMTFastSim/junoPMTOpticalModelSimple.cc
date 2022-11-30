
#include "G4OpticalPhoton.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


#include "SLOG.hh"
#include "JPMT.h"
#include "Layr.h"

#include "spho.h"
#include "STrackInfo.h"
#include "junoPMTOpticalModelSimple.hh"

const plog::Severity junoPMTOpticalModelSimple::LEVEL = SLOG::EnvLevel("junoPMTOpticalModelSimple", "DEBUG" ); 


junoPMTOpticalModelSimple::junoPMTOpticalModelSimple(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
    : 
    G4VFastSimulationModel(modelName, envelope),
    jpmt(new JPMT),    // actually dont need one per FastSim model, a single JPMT for entire geometry would be OK
    ModelTrigger_count(0)
{
}

G4bool junoPMTOpticalModelSimple::IsApplicable(const G4ParticleDefinition & particleType)
{
    return (&particleType == G4OpticalPhoton::OpticalPhotonDefinition());
}


/**
junoPMTOpticalModelSimple::ModelTrigger 
-----------------------------------------

Simple Geometry and ModelTrigger : using single inner vacuum which is envelope

* 1 Pyrex "pmt", 1 Vacuum "inner"
* use Vacuum as the FastSim region
* trigger when intersect the innner at +ve Z position

::
                           
                  Y  .          . Y
                . |              /   .         +Z
              .   |             /       .
             .    +            /          .
   ----------+          inner /           +----------
             .               /           .
              .             +-----------N
                .                    .        -Z
                     .          .

**/

G4bool junoPMTOpticalModelSimple::ModelTrigger(const G4FastTrack &fastTrack)
{
    G4double z = fastTrack.GetPrimaryTrackLocalPosition().z() ; 
    const G4Track* track = fastTrack.GetPrimaryTrack();
    G4VPhysicalVolume* pv = track->GetVolume() ; 
    G4VPhysicalVolume* nv = track->GetNextVolume() ; 
    G4bool ret = z > 0. ;

    LOG(LEVEL) 
         << " ModelTrigger_count " << std::setw(3) << ModelTrigger_count 
         << " z " << std::setw(10) << std::setprecision(4) << z 
         << " Result : " << ( ret ? "YES" : "NO" ) 
         << " pv " << ( pv ? pv->GetName() : "-" )
         << " nv " << ( nv ? nv->GetName() : "-" )
         ;  

    ModelTrigger_count += 1 ; 
    return ret ; 
}

void junoPMTOpticalModelSimple::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
{
    const G4Track* track = fastTrack.GetPrimaryTrack();

    G4ThreeVector position = fastTrack.GetPrimaryTrackLocalPosition();
    G4ThreeVector direction = fastTrack.GetPrimaryTrackLocalDirection();
    G4ThreeVector polarization = fastTrack.GetPrimaryTrackLocalPolarization();

    G4VSolid* envelope_solid = fastTrack.GetEnvelopeSolid();
    G4ThreeVector surface_normal = envelope_solid->SurfaceNormal(position);
    // fastTrack is just a track that has been localised with affine transform of envelope

    G4double energy  = track->GetKineticEnergy();

    G4double wavelength = twopi*hbarc/energy ;
    G4double energy_eV = energy/eV ;
    G4double wavelength_nm = wavelength/nm ;

    G4double minus_cos_theta = direction*surface_normal ; 
    G4ThreeVector oriented_normal = ( minus_cos_theta < 0. ? 1. : -1. )*surface_normal ; 
    // oriented opposite to photon direction, textbook style  

    int pmtcat = JPMT::HAMA ;  // TODO: pmtcat ctor argument ? HMM: NNVT_HiQE ?
    //double _qe = 0.5 ; 
    double _qe = 0.0 ; 

    StackSpec<double> spec ; 
    spec.d0  = 0. ; 
    spec.d1  = jpmt->get_thickness_nm( pmtcat, JPMT::L1 );  
    spec.d2  = jpmt->get_thickness_nm( pmtcat, JPMT::L2 ); 
    spec.d3 = 0. ; 

    spec.n0r = jpmt->get_rindex( pmtcat, JPMT::L0, JPMT::RINDEX, energy_eV ); 
    spec.n0i = jpmt->get_rindex( pmtcat, JPMT::L0, JPMT::KINDEX, energy_eV );

    spec.n1r = jpmt->get_rindex( pmtcat, JPMT::L1, JPMT::RINDEX, energy_eV );
    spec.n1i = jpmt->get_rindex( pmtcat, JPMT::L1, JPMT::KINDEX, energy_eV );

    spec.n2r = jpmt->get_rindex( pmtcat, JPMT::L2, JPMT::RINDEX, energy_eV ); 
    spec.n2i = jpmt->get_rindex( pmtcat, JPMT::L2, JPMT::KINDEX, energy_eV ); 

    spec.n3r = jpmt->get_rindex( pmtcat, JPMT::L3, JPMT::RINDEX, energy_eV ); 
    spec.n3i = jpmt->get_rindex( pmtcat, JPMT::L3, JPMT::KINDEX, energy_eV );

    Stack<double,4> stack(      wavelength_nm, minus_cos_theta, spec );  // NB stack is flipped for minus_cos_theta > 0. 
    Stack<double,4> stackNormal(wavelength_nm, -1.            , spec );  // minus_cos_theta -1. means normal incidence and stack not flipped


    LOG(LEVEL)
        << " position " << position
        << " direction " << direction
        << " polarization " << polarization
        << " surface_normal " << surface_normal 
        ; 

    // NB stack is flipped for mct > 0, 
    // so layr 0/3 will always be first/last  
    // ie layr 0 is incident side, which may be Pyrex or Vacuum side

    double _n0         = stack.ll[0].n.real() ; 
    double _sin_theta0 = stack.ll[0].st.real() ; 
    double _cos_theta0 = stack.ll[0].ct.real() ;

    double _n3         = stack.ll[3].n.real() ; 
    double _cos_theta3 = stack.ll[3].ct.real() ;
 
    double E_s2 = _sin_theta0 > 0. ? (polarization*direction.cross(oriented_normal))/_sin_theta0 : 0. ; 
    E_s2 *= E_s2;

    double fT_s = stack.art.T_s ; 
    double fT_p = stack.art.T_p ; 
    double fR_s = stack.art.R_s ; 
    double fR_p = stack.art.R_p ; 

    double fT_n = stackNormal.art.T ; 
    double fR_n = stackNormal.art.R ; 

    double one = 1.0 ; 
    double T = fT_s*E_s2 + fT_p*(one-E_s2);
    double R = fR_s*E_s2 + fR_p*(one-E_s2);
    double A = one - (T+R);
    double An = one - (fT_n+fR_n);
    double detect_fraction = _qe/An;

    LOG_IF(error, detect_fraction > 1.) 
         << " detect_fraction > 1. : " << detect_fraction 
         << " _qe " << _qe
         << " An " << An 
         ;  

    double u0 = G4UniformRand();  
    double u1 = G4UniformRand();

    char status = '?' ;
    if(     u0 < A)    status = u1 < detect_fraction ? 'D' : 'A' ; 
    else if(u0 < A+R)  status = 'R' ; 
    else               status = 'T' ; 


    // the below is copying junoPMTOpticalModel (TODO: need to compare with G4OpBoundaryProcess)
    if( status == 'R' )
    {
        direction    -= 2.*(direction*oriented_normal)*oriented_normal ;   
        polarization -= 2.*(polarization*oriented_normal)*oriented_normal ;
    }
    else if( status == 'T' )
    {
        direction = (_cos_theta3 - _cos_theta0*_n0/_n3)*oriented_normal + (_n0/_n3)*direction;
        polarization = (polarization-(polarization*direction)*direction).unit();
    }



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
        << " T " << std::setw(10) << std::fixed << std::setprecision(4) << T 
        << " R " << std::setw(10) << std::fixed << std::setprecision(4) << R
        << " A " << std::setw(10) << std::fixed << std::setprecision(4) << A 
        << " u0 " << std::setw(10) << std::fixed << std::setprecision(4) << u0 
        << " u1 " << std::setw(10) << std::fixed << std::setprecision(4) << u1
        << " status " << status 
        ; 

    // fastStep is the particle change interface for FastSim

    if( status == 'A' )
    {
        fastStep.ProposeTrackStatus(fStopAndKill);
    }
    else if( status == 'D' )
    {
        fastStep.ProposeTrackStatus(fStopAndKill);
        fastStep.ProposeTotalEnergyDeposited(energy);
    }
    else if( status == 'R' || status == 'T' )
    {
        fastStep.SetPrimaryTrackFinalMomentum(direction);
        fastStep.SetPrimaryTrackFinalPolarization(polarization);
        fastStep.ForceSteppingHitInvocation();   // WHAT DOES THIS DO ? Enables SD probably 
    }

    fastTrack.GetPrimaryTrack()->GetStep()->GetPostStepPoint()->SetStepStatus(fGeomBoundary);
    // avoids G4StepStatus fExclusivelyForcedProc 


}



/**
junoPMTOpticalModelSimple::DoIt
---------------------------------

minus_cos_theta < 0 
    direction is against the normal (inwards)  
    photon from Pyrex side

minus_cos_theta > 0 
    direction is with the normal (outwards)  
    photon from Vacuum side



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

TODO: compare with  qsim.h propagate_at_boundary 


1.  note than fT_n fR_n do not flip the stack (unlike fT_s fTp fR_s fR_p which do flip the stack)
2.  Q: Why does detection use _qe/An (why reciprocal and why indep of aoi and without flipping stack) 
    but everything else uses angular dependent A,R,T ?
    
    A: Presumably anything can be justified based on what the definition of the QE input is, 
    and the fact that "backwards" _qe gets set to zero anyhow. 
    
    NOT CONVINCED BY THAT : AS escape_fac will be > 1 for An < _qe
    which would mean that rand_escape < escape_fac always 
    
    When An is small (little absorption) eg 0.1 escape fac gets scaled to _qe*10 
    which then gets compared to rand_escape a random number in [0,1]
    SO THAT WOULD MEAN THE LESS ABSORPTION THE MORE DETECTION : WHICH IS SURELY WRONG 
    _qe*An would surely be more reasonable ? 
    
    TODO: incorporate An into LayrTest.py plotting    

**/

