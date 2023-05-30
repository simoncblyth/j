
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "junoSD_PMT_v2.hh"
#include "junoSD_PMT_v2_Opticks.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

using CLHEP::twopi ; 
using CLHEP::hbarc ; 
using CLHEP::eV ; 
using CLHEP::MeV ; 

#include "junoHit_PMT.hh"
#include "PMTHitMerger.hh"


#ifdef WITH_G4CXOPTICKS
#include "PMTSim/junoSD_PMT_v2_Debug.h"
#include "GenTools/GtOpticksTool.h"
#include "OpticksPhoton.hh"
#include "SLOG.hh"

#include "G4CXOpticks.hh"
#include "SEvt.hh"
#include "ssys.h"
#include "U4Hit.h"
#include "U4HitGet.h"
#include "U4Recorder.hh"
#include "SProfile.h"
#include "NP.hh"

const plog::Severity junoSD_PMT_v2_Opticks::LEVEL = SLOG::EnvLevel("junoSD_PMT_v2_Opticks", "DEBUG") ; 
#endif


#ifdef WITH_G4CXOPTICKS_DEBUG
#include "U4Debug.hh"
#include "S4RandomArray.h"
#endif


bool junoSD_PMT_v2_Opticks::gpu_simulation() const 
{ 
#ifdef WITH_G4CXOPTICKS
    return m_opticksMode == 1 || m_opticksMode == 3 ;  
#else
    return false ; 
#endif
}


junoSD_PMT_v2_Opticks::junoSD_PMT_v2_Opticks( junoSD_PMT_v2* jpmt )
    :
    m_jpmt(jpmt),
#ifdef WITH_G4CXOPTICKS
    m_jpmt_dbg(jpmt->getProcessHitsDebug()),
#else
    m_jpmt_dbg(nullptr),
#endif
    m_opticksMode(jpmt->getOpticksMode()),
    m_pmthitmerger_opticks(nullptr),
    m_event_total(0),
    m_genstep_total(0),
    m_photon_total(0),
    m_hit_total(0),
    m_merged_total(0),
    m_savehit_total(0) 
{
}

std::string junoSD_PMT_v2_Opticks::desc() const
{
    std::stringstream ss ; 
    ss
        << "junoSD_PMT_v2_Opticks::desc"
#ifdef WITH_G4CXOPTICKS
        << " WITH_G4CXOPTICKS " 
#else
        << " not-WITH_G4CXOPTICKS " 
#endif
        << " m_opticksMode " << m_opticksMode
        << " m_event_total " << m_event_total
        << " m_genstep_total " << m_genstep_total
        << " m_photon_total " << m_photon_total
        << " m_hit_total " << m_hit_total
        << " m_merged_total " << m_merged_total
        << " m_savehit_total " << m_savehit_total
        ;
    std::string str = ss.str() ; 
    return str ; 
}

junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks()
{
#ifdef WITH_G4CXOPTICKS
    LOG(LEVEL) << desc() ; 
#else
    std::cerr << desc() << std::endl ; 
#endif
}

/**
junoSD_PMT_v2_Opticks::Initialize
-----------------------------------

HMM: this grabbing from the input is kinda cheating, 
should really re-constitute from the G4Event  primaries
but input_photons.py is just for debugging, so I judge this
to be accepatble.

Actually Opticks has its own way to setup input photons
so perhaps can remove the GtOpticksTool that duplicates this. 

**/

#ifdef WITH_G4CXOPTICKS
void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
{
    SEvt::TimerStart() ; 

    std::cerr
        << "junoSD_PMT_v2_Opticks::Initialize"
        << " opticksMode " << m_opticksMode
        << " eventID " << eventID
        << " LEVEL " << LEVEL << ":" << plog::severityToString(LEVEL) 
        << std::endl 
        ; 
}



/**
junoSD_PMT_v2_Opticks::EndOfEvent
----------------------------------

This is called from junoSD_PMT_v2::EndOfEvent only for opticksMode 1 or 3
when GPU simulation is done.  


1. sets m_pmthitmerger_opticks using  junoSD_PMT_v2::getMergerOpticks with result depending on m_opticksMode 

   * crucially the hitcollection associated with the hitmerger determines 
     where the Opticks GPU hits will end up, only when using the standard hitCollection 
     will they go on to the next stage ElecSim

2. performs GPU optical photon propagation 

3. gets hits from G4Opticks, converts them into JUNO PMT hits, collects them with m_pmthitmerger_opticks

**/


void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
{
    if(m_pmthitmerger_opticks == nullptr) m_pmthitmerger_opticks = m_jpmt->getMergerOpticks(); 
    bool gpu_sim = gpu_simulation(); 

    LOG(LEVEL) << "[ " << m_jpmt->desc() ; 

    SEvt::SetIndex(eventID);  

    EndOfEvent_Debug(eventID) ; 

    if(gpu_sim) 
    {
        EndOfEvent_Simulate(eventID) ; 
    }


    LOG(LEVEL) << "] " << m_jpmt->desc() ; 
}

/**
junoSD_PMT_v2_Opticks::EndOfEvent_Debug
---------------------------------------

Note the use of SEvt::SaveExtra rather than SEvt::AddArray
in the below as want the metadata to be available in all modes 
including opticksMode:0 which does not have U4Recorder active
and does not normally save SEvt. 

Switch off the WITH_G4CXOPTICKS_DEBUG block by 
changing ~/opticks/cmake/Modules/FindOpticks.cmake 

**/
void junoSD_PMT_v2_Opticks::EndOfEvent_Debug(int eventID )
{
    std::cerr 
        << "junoSD_PMT_v2_Opticks::EndOfEvent_Debug"
        << " eventID " << eventID
        << " opticksMode " << m_opticksMode
        << " with m_jpmt_dbg " << ( m_jpmt_dbg ? "YES" : "NO " )
        << std::endl
        ;

    if( m_jpmt_dbg != nullptr )
    {
        NP* jsdpmt = m_jpmt_dbg->get_meta_array(m_opticksMode, eventID ) ;  // junoSD_PMT_v2_Debug
        jsdpmt->set_meta<int>("VERSION", ssys::getenvint("VERSION", -1) ); 
        jsdpmt->set_meta<double>("SEvt__TimerDone", SEvt::TimerDone() ); 
        jsdpmt->set_meta<uint64_t>("SEvt__TimerStartCount", SEvt::TimerStartCount() ); 
        SEvt::SaveExtra("junoSD_PMT_v2_Opticks.npy", jsdpmt ); 

        LOG(LEVEL) << m_jpmt_dbg->desc() ; 
        m_jpmt_dbg->zero();  
    }

    SEvt::SaveExtra( "junoSD_PMT_v2_SProfile.npy", SProfile<16>::Array() ); 
    SProfile<16>::Clear(); 

#ifdef WITH_G4CXOPTICKS_DEBUG
    U4Debug::Save(eventID);   

    if( m_opticksMode == 0 || m_opticksMode == 2 )
    {  
        S4RandomArray* s4ra = SEvt::GetRandomArray() ; 
        NP* ra = s4ra ? s4ra->serialize() : nullptr ; 
        if(ra)
        {
             SEvt::SaveExtra(S4RandomArray::NAME, ra) ; 
             s4ra->clear(); 
        }
    }

#endif
}


void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
{
    unsigned num_genstep = SEvt::GetNumGenstepFromGenstep(); 
    unsigned num_photon  = SEvt::GetNumPhotonFromGenstep(); 

    G4CXOpticks::Get()->simulate() ; 

    unsigned num_hit = SEvt::GetNumHit() ; 
    bool way_enabled = false ; 

    LOG(LEVEL)
        << " eventID " << eventID
        << " num_genstep " << num_genstep
        << " num_photon " << num_photon
        << " num_hit " << num_hit
        << " way_enabled " << way_enabled 
        ;

    int merged_count(0);
    int savehit_count(0);
    std::stringstream ss ; 

    U4Hit hit ;
    U4HitExtra hit_extra ;
    U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    for(int idx=0 ; idx < int(num_hit) ; idx++)
    {
        U4HitGet::FromEvt(hit, idx);   
        collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
        if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    }

    LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;   

    LOG(LEVEL)
        << "]"
        << " num_hit " << num_hit
        << ( merged_count > 0 ? " MERGED " : "" )
        << " merged_count  " << merged_count
        << " savehit_count  " << savehit_count
        << " m_merged_total " << m_merged_total 
        << " m_savehit_total " << m_savehit_total 
        << " m_opticksMode " << m_opticksMode
        ;

    m_event_total += 1 ; 
    m_genstep_total += num_genstep ; 
    m_photon_total += num_photon ; 
    m_hit_total += num_hit ; 
    m_merged_total += merged_count ; 
    m_savehit_total += savehit_count ; 

    TerminateEvent(); 
}


/**
junoSD_PMT_v2_Opticks::TerminateEvent
---------------------------------------

Geant4 SD EndOfEvent is always invoked before userEventAction EndOfEvent (see g4-cls G4EventManager). 
Because of this it is too soon to invoke G4Opticks::reset here when G4OpticksRecorder is active.
For example resetting here would cause the CGenstepGollector to be cleared before g4evt OpticksEvent::save 
is done by G4OpticksRecorder/CManager, that would causes g4evt metadata to be messed up.

But, having a userEventAction is entirely optional for analysis/debug with the G4OpticksRecorder 
but the SD is always present. So some detection is used to determine whether to reset from here.

When G4OpticksRecorder::Get() indicates the recorder is not instanciated 
the G4Opticks::reset is invoked here, otherwise it should be invoked 
from G4OpticksRecorder::TerminateEvent.

HMM: perhaps can remove the recorder from here, as that is a validation 
exercise that needs to be done within Opticks ?

**/

void junoSD_PMT_v2_Opticks::TerminateEvent()
{
    U4Recorder* recorder = U4Recorder::Get() ; 
    if( recorder == nullptr )
    {
        LOG(LEVEL) << " invoking SEvt::Clear as no U4Recorder detected " ; 
        SEvt::Clear();  
    }
    else
    {
        LOG(LEVEL) << " NOT invoking SEvt::Clear as U4Recorder detected, should do reset in U4Recorder::TerminateEvent" ; 
    }
}


void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
{
    assert( m_pmthitmerger_opticks ); 
    bool merged = false ; 
    if(m_pmthitmerger_opticks->getMergeFlag()) 
    {
        merged = m_pmthitmerger_opticks->doMerge(hit->sensor_identifier, hit->time);
    }
    if(merged)
    {
        merged_count += 1 ; 
    }
    else 
    {
        junoHit_PMT* hit_photon = convertHit(hit, hit_extra );  
        savehit_count += 1 ; 
        m_pmthitmerger_opticks->saveHit(hit_photon);
    }
}


/**
junoSD_PMT_v2_Opticks::convertHit
----------------------------------

originalOP
    All optical photons in Opticks start from gensteps of some other particle.
    Only optical photons that have reemission in their histories would correspond 
    to the Geant4 notion of being a secondary, although of course Opticks does not 
    do secondaries to handle reemission. Instead a portion of the bulk absorbed 
    are reborn in the same thread.

**/

junoHit_PMT* junoSD_PMT_v2_Opticks::convertHit(const U4Hit* hit, const U4HitExtra* hit_extra ) const
{
    junoHit_PMT* hit_photon = new junoHit_PMT();

    bool originalOP = !hit->is_reemission ; 
    double edep = twopi*hbarc / hit->wavelength ;  // TODO:check units match with CPU hits 

    hit_photon->SetKineticEnergy(edep);
    hit_photon->SetOriginalOP(originalOP);
    hit_photon->SetCount(1); 

    hit_photon->SetWavelength(hit->wavelength);
    hit_photon->SetPMTID(hit->sensor_identifier);
    hit_photon->SetWeight(hit->weight);
    hit_photon->SetTime(hit->time);

    hit_photon->SetPosition(hit->local_position);
    hit_photon->SetTheta(   hit->local_position.theta());
    hit_photon->SetPhi(     hit->local_position.phi());
    hit_photon->SetMomentum(hit->local_direction); 
    hit_photon->SetPolarization(hit->local_polarization); 

    hit_photon->SetGlobalPosition(hit->global_position);
    hit_photon->SetGlobalMomentum(hit->global_direction); 
    hit_photon->SetGlobalPolarization(hit->global_polarization); 

    hit_photon->SetFromCerenkov(hit->is_cerenkov);
    hit_photon->SetReemission(hit->is_reemission);

    if(hit_extra)
    {
        hit_photon->SetProducerID(hit_extra->origin_trackID);
        hit_photon->SetOriginalOPStartT(hit_extra->origin_time);
        hit_photon->SetBoundaryPosition(hit_extra->boundary_pos);
    }
    return hit_photon ; 
}

std::string junoSD_PMT_v2_Opticks::descHit(unsigned idx, const U4Hit* hit, const U4HitExtra* hit_extra ) const
{
    std::stringstream ss ; 
    ss
        << std::setw(6) << idx 
        << " gp.x " << std::setw(10) << std::fixed << std::setprecision(2) << hit->global_position.x()
        << " gp.y " << std::setw(10) << std::fixed << std::setprecision(2) << hit->global_position.y()
        << " gp.z " << std::setw(10) << std::fixed << std::setprecision(2) << hit->global_position.z()
        << " gp.R " << std::setw(10) << std::fixed << std::setprecision(2) << hit->global_position.mag()
        << " pmt "   << std::setw(7) << hit->sensor_identifier
        << " " << std::setw(20) << OpticksPhoton::FlagMask(hit->flag_mask, true)
        ;
    if(hit_extra)
    {
        ss
            << " otk " << std::setw(6) << hit_extra->origin_trackID
            << " oti" << std::setw(8) << std::fixed << std::setprecision(2) << hit_extra->origin_time
            << " bti "  << std::setw(8) << std::fixed << std::setprecision(2) << hit_extra->boundary_time
            << " bp.x " << std::setw(10) << std::fixed << std::setprecision(2) << hit_extra->boundary_pos.x()
            << " bp.y " << std::setw(10) << std::fixed << std::setprecision(2) << hit_extra->boundary_pos.y()
            << " bp.z " << std::setw(10) << std::fixed << std::setprecision(2) << hit_extra->boundary_pos.z()
            << " bp.R " << std::setw(10) << std::fixed << std::setprecision(2) << hit_extra->boundary_pos.mag()
            ; 
    }
    std::string desc = ss.str(); 
    return desc ; 
}
// end of whopper WITH_G4CXOPTICKS block 
#endif

