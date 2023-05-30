//--------------------------------------------------------------------------
//                            junoSD_PMT_v2
//
// PMTs are difined as sensitive detector. They collect hits on them.
// The data members of hits are set up here using the information of G4Step.
// -------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified by: Weili Zhong, 2006/03/01
// -------------------------------------------------------------------------



#include "junoSD_PMT_v2.hh"
#include "junoHit_PMT.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4Track.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include <cassert>
#include "NormalTrackInfo.hh"
#include "G4OpticalPhoton.hh"
#include "Randomize.hh"
#include "G4DataInterpolation.hh"
#include "G4VProcess.hh"
#include "G4OpBoundaryProcess.hh"
#include "C4OpBoundaryProcess.hh"
#include "C4Touchable.h"

#include "G4ProcessManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

#include "junoSD_PMT_v2_Opticks.hh"
#include "PMTEfficiency.hh"
#include "PMTEfficiencyTable.hh"

#ifdef WITH_G4CXOPTICKS_DEBUG
#include "U4Touchable.h"
#include "U4Debug.hh"
#include "U4Hit_Debug.hh"
#include "U4PhotonInfo.h"
#endif

#include "IPMTSimParamSvc/IPMTSimParamSvc.h"  // simcat category enum 
#include "Geometry/PMTParamSvc.h"             // parcat category enum
#include "Geometry/PMT.h"

using namespace CLHEP;

////////////////////////////////////////////////////////////////////////////////

#ifdef WITH_G4CXOPTICKS
#include "PMTSim/junoSD_PMT_v2_Debug.h"
#include "C4Track.h"
#include "SLOG.hh"
#include "SEvt.hh"
#include "SProfile.h"
#include "U4Touchable.h"

template<>
std::vector<SProfile<16>> SProfile<16>::RECORD = {}  ;   

const plog::Severity junoSD_PMT_v2::LEVEL = SLOG::EnvLevel("junoSD_PMT_v2", "DEBUG"); 
#endif


junoSD_PMT_v2::junoSD_PMT_v2(const std::string& name, int opticksMode)
    :
    G4VSensitiveDetector(name),
    hitCollection(0), 
    hitCollection_muon(0), 
    hitCollection_opticks(0), 
    m_eventID(-1),
    m_opticksMode(opticksMode),
    m_category_type('S'),    // S:simcat P:parcat
    m_PMTEfficiency(PMTEfficiency::Make()),  
    m_PMTEfficiencyTable(new PMTEfficiencyTable(m_PMTEfficiency)),  
#ifdef WITH_G4CXOPTICKS
    m_jpmt_dbg(new junoSD_PMT_v2_Debug), 
    m_eph(EPH::UNSET), 
    m_label_id(-1),
    m_profile(new SProfile<16>),
#endif
    m_jpmt_opticks(new junoSD_PMT_v2_Opticks(this))
{
    G4String HCname;
    collectionName.insert(HCname="hitCollection");
    collectionName.insert(HCname="hitCollectionMuon");
    if(m_opticksMode > 0)
    {
        collectionName.insert(HCname="hitCollectionOpticks");
    }

    m_debug = true;
    m_time_window = 1; // 1ns

    m_pmthitmerger = 0;
    m_pmthitmerger_opticks = 0;
    m_hit_type = 1; // 1 for normal, 2 for muon

    m_qescale = 1.0/0.8 ;  // scale back for 0.8 QE-scale in LsExpDetectorConstruction
    m_qescale_optical_model = 1.0/0.5;

    m_angle_response = 1.0;

    m_ce_flat_value = 0.9;

    MCP20inch_m_ce_flat_value = 0.85;
    MCP8inch_m_ce_flat_value = 0.85;
    Ham20inch_m_ce_flat_value = 0.95;
    Ham8inch_m_ce_flat_value = 0.7;
    HZC9inch_m_ce_flat_value = 0.67;

    MCP20inch_m_EAR_value = 1.;
    MCP8inch_m_EAR_value = 1.;
    Ham20inch_m_EAR_value = 0.93;
    Ham8inch_m_EAR_value = 0.88;
    HZC9inch_m_EAR_value = 0.92;

    m_disable = false;
    m_enable_optical_model = false;

    // 20inchfunc (1D)
    // FIXME: following are not used in current code
    m_ce_func_str = "0.9*[0]/(1+[1]*exp(-[2]*x))";
    //OLD
    //m_ce_func_params.push_back(1.006); // p0
    //m_ce_func_params.push_back(0.9023);// p1
    //m_ce_func_params.push_back(0.1273);// p2

    //NEW from the PMT test benches at Zhongshan
    m_ce_func_params.push_back(0.9194); // p0
    m_ce_func_params.push_back(0.504);  // p1
    m_ce_func_params.push_back(0.08076);// p2

    //These fit the Hamamatsu CE better..
    //m_ce_func_params.push_back(1.02557);// p0
    //m_ce_func_params.push_back(6.77639);// p1
    //m_ce_func_params.push_back(0.16419);// p2

    m_ce_func = 0;
    m_merge_count = 0 ; 
}

junoSD_PMT_v2::~junoSD_PMT_v2()
{
    delete m_PMTEfficiency ;
    delete m_PMTEfficiencyTable ;
    delete m_jpmt_opticks ;
}



void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
{
    const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ; 
    m_eventID = event->GetEventID() ; 

    m_merge_count = 0 ; 
    if (m_debug) {
        G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
    }
    hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);

    // changed from a static variable to a normal variable by Jillings, August 2, 2006
    int HCID = -1;
    if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection);
    HCE->AddHitsCollection( HCID, hitCollection ); 

    HCID = -1;
    if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection_muon);
    HCE->AddHitsCollection( HCID, hitCollection_muon ); 

    m_pmtid2idincol.clear();
    assert( m_pmtid2idincol.size() == 0 );

    if (m_pmthitmerger) {
        if (m_hit_type == 1) {
            m_pmthitmerger->init(hitCollection);
        } else if (m_hit_type == 2) {
            // TODO
            m_pmthitmerger->init(hitCollection_muon);
        } else {
            G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
        }
    }
    // make sure the PMT merger exists.
    assert(m_pmthitmerger);


    if(m_opticksMode > 0) // for now, a separate collection for GPU hits 
    {
        hitCollection_opticks = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[2]);
        HCID = -1;
        if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection_opticks);
        HCE->AddHitsCollection( HCID, hitCollection_opticks );
        assert(m_pmthitmerger_opticks); 
        if (m_hit_type == 1) {
            m_pmthitmerger_opticks->init(hitCollection_opticks);
        } else {
            G4cout << "FATAL : unknown hit type [" << m_hit_type << "]" << G4endl;
            assert(0); 
        }
    }

#ifdef WITH_G4CXOPTICKS
    m_jpmt_opticks->Initialize(HCE, m_eventID);    
#endif

}

/**
junoSD_PMT_v2::getMergerOpticks
---------------------------------

HMM : this is only used from junoSD_PMT_v2_Opticks : SO MOVE IT THERE ?


--opticks-mode 0  

   * merger : nullptr
   * "0b00", no Opticks involvement, standard Geant4 and hits 

--opticks-mode 1  

   * merger : m_pmthitmerger : Opticks GPU hits are placed into the standard hitCollection
   * "0b01", replace Geant4 optical photon simulation with Opticks GPU propagation
   * Opticks GPU hits are loaded into standard detsim .root files
   * can enable detailed instrumentation of the Opticks propagation and save into OpticksEvent NumPy arrays (+ve tags)

--opticks-mode 2 

    * merger : nullptr  : there are no opticks GPU hits in this mode
   * "0b10", only Geant4 CPU propagation 
   * can enable detailed instrumentation of the Geant4 propagation and save into OpticksEvent NumPy arrays (-ve tags)
   * in principal this mode could be used without a GPU  

--opticks-mode 3

   * merger : m_pmthitmerger_opticks
   * "0b11", both Geant4 CPU + Opticks GPU optical propagations 
   * can enable detailed instrumentation of both Opticks and Geant4 propagations 
   * the propagations can be saved into OpticksEvent NumPy arrays with OK:+ve and G4:-ve tags
   * currently the somewhat arbitrary choice is for the CPU hits to go into the standard hit collection
   * these hits are however rather irrelevant as the point of "bool(m_opticksMode&2)" is to use 
     G4OpticksAnaMgr and G4OpticksRecorder to save the entire Geant4 optical propagations in OpticksEvent format 
     allowing Opticks analysis and visualization machinery to be applied to the Geant4 propagation 

Opticks SEvt can store every step point of every photon, not just the final photons that are regarded as hits, 
this makes them much more useful for debugging and validation than just looking at hits 

**/

PMTHitMerger* junoSD_PMT_v2::getMergerOpticks() const 
{  
    PMTHitMerger* merger = nullptr ; 
    if( m_opticksMode == 0 )
    {
        merger = nullptr ; 
    }
    else if( m_opticksMode == 1 )   // only opticks : so opticks hits use standard merger
    {
        merger = m_pmthitmerger ;  
    } 
    else if( m_opticksMode == 2 )   // only geant4 (but with opticks instrumentation) : so use standard merger
    {
        merger = nullptr ;  
    } 
    else if( m_opticksMode == 3 )   // both opticks and geant4 (just for debug comparisons)  
    {
        merger = m_pmthitmerger_opticks ;  
    }
    return merger ; 
}







template <typename T>
T* junoSD_PMT_v2::GetOpBoundaryProcess()  // static
{
    T* bp = nullptr ; 
    G4ProcessManager* mgr = G4OpticalPhoton::OpticalPhoton()->GetProcessManager() ;
    G4int pmax = mgr ? mgr->GetPostStepProcessVector()->entries() : 0 ; 
    G4ProcessVector* pvec = mgr ? mgr->GetPostStepProcessVector(typeDoIt) : nullptr ;

    for (int i=0; i < pmax ; i++) 
    {   
        G4VProcess* p = (*pvec)[i];
        T* t = dynamic_cast<T*>(p);
        if(t) 
        {   
            bp = t ; 
            break;
        }   
    }   
    return bp ; 
}




/**
junoSD_PMT_v2::ProcessHits  [ SCB ,  Wang Yaoguang ]
-------------------------------------------------------

To understand the operation of ProcessHits it is necessary to be aware of two switches:

1. *UsePmtSimSvc* option (m_use_pmtsimsvc) controls BOTH the approach used to model PMT efficiency AND the use of PMTSimParamSvc, 
   disabled with --no-use-pmtsimsvc
2. new optical model switch (m_enable_optical_model) disabled with --disable-pmt-optical-model

Note that when disabling the PMTSimParamSvc with --no-use-pmtsimsvc you must also disable 
the new PMT optical model with --disable-pmt-optical-model

m_use_pmtsimsvc:true
~~~~~~~~~~~~~~~~~~~~~~~~~

default approach 
* PMTSimParsvc provides both *qe* and *ce*  
* Geant4 EFFICIENCY G4MaterialPropertyVector values are set to 1. in LSExpDetectorConstructionMaterial.icc 

This approach simplifies the efficiency modelling by doing it all with PMTSimParsvc

m_use_pmtsimsvc:false 
~~~~~~~~~~~~~~~~~~~~~~~~~

* non default legacy approach, used via option --no-use-pmtsimsvc
* Geant4 EFFICIENCY G4MaterialPropertyVector hold the QE(energy) values implemented in LSExpDetectorConstructionMaterial.icc 

This approach splits the modelling of efficiencies between Geant4 and ProcessHits

m_enable_optical_model:false
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

When G4OpBoundaryProcessStatus is not Detection there is an early exit from ProcessHits, which 
means that only photons directly incident onto the sensitive photocathode can become hits
when the new PMT optical model is not enabled  

m_enable_optical_model:true
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* no requirements on G4OpBoundaryProcessStatus
* qe of large PMTs is set to 1
* For the new PMT optical model, optical processes on 
  photocathode are handled by junoPMTOpticalModel, in 
  which QE of LPMTs has been considered. So, it's set to 1.0 here.


NB ProcessHits often runs multiple times per photon
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ProcessHits may run 0,1,>1 times per photon, so care is
required to match m_eph counts with per photon SD flag counts.

When ProcessHits runs more than once for a photon it looks like the 
above will stomp, but that is not the full story as the label values 
will get copied into the step point level aux by U4Recorder before stomping happens. 
So can use NumPy like "np.max(a.eph, axis=1)" to get a photon level eph from 
the SEvt arrays which can be compared with photon level SD flag counts. 
The maximum eph from all step points is appropriate due to the EPH enum order. 

**/   

#ifdef WITH_G4CXOPTICKS
G4bool junoSD_PMT_v2::ProcessHits(G4Step* step,G4TouchableHistory*)
{
    SEvt::AddProcessHitsStamp(0); 

    G4Track* track = step->GetTrack() ;    
    m_label_id = C4Track::GetLabelID(track); 

    m_profile->zero(); 
    m_profile->idx = m_label_id ; 

    G4bool is_hit = ProcessHits_(step, nullptr) ; 
    m_jpmt_dbg->add( m_eph, is_hit ); 

    C4Track::SetLabelEph(track, m_eph);  
    C4Track::IncrementLabelExt(track) ; 

    LOG_IF(LEVEL, (m_label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ; 

    m_profile->add(); 
    SEvt::AddProcessHitsStamp(1); 
    return is_hit ; 
}

junoSD_PMT_v2_Debug* junoSD_PMT_v2::getProcessHitsDebug() const 
{
    return m_jpmt_dbg ; 
}


#endif 

#ifdef WITH_G4CXOPTICKS
G4bool junoSD_PMT_v2::ProcessHits_(G4Step * step,G4TouchableHistory*)
#else
G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
#endif
{
#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(0); 
#endif

    if (m_disable) {
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NDIS ;  
#endif
        return false;
    }

    // TODO: now it only support the single PE.
    // = only accept the optical photon
    G4Track* track = step->GetTrack();
    if (track->GetDefinition() != G4OpticalPhoton::Definition()) {
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NOPT ;  
#endif
        return false;
    }


    //G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    double edep = step->GetTotalEnergyDeposit();
    // = only when the photon is detected by the surface, the edep is non-zero.
    // = the QE is already applied in the OpBoundaryProcess::DoAbsorption
    if (edep<=0.0) {
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NEDEP ;  
#endif
        return false;
    }




    // LT
    // = Due to update of Geant4, now OpAbsorption will also cause non-zero edep.
    // = Hence we need to check the OP boundary.
    G4bool isOnBoundary = (postStepPoint->GetStepStatus() == fGeomBoundary);
    if (not isOnBoundary) {
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NBOUND ;  
#endif
        return false;
    }



    static G4ThreadLocal C4OpBoundaryProcess* boundary_proc = GetOpBoundaryProcess<C4OpBoundaryProcess>() ; 

    if (!boundary_proc) {
        G4cout << "Can't locate OpBoundaryProcess." << G4endl;
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NPROC ;  
#endif
        return false;
    }




    if (!m_enable_optical_model) {
       G4OpBoundaryProcessStatus theStatus = Undefined;
       theStatus = boundary_proc->GetStatus();
       if (theStatus != Detection) {
#ifdef WITH_G4CXOPTICKS
           m_eph = EPH::NDETECT ;  
#endif
           return false;
       }
    }

    // TODO: get CE and angle response from data.
    // = decide the CE (collection efficiency)
    // = the CE can be different at different position
    // == position
    const G4AffineTransform& trans = track->GetTouchable()->GetHistory()->GetTopTransform();

    const G4ThreeVector& global_pos = postStepPoint->GetPosition();

    G4ThreeVector local_pos = trans.TransformPoint(global_pos);

    double qe = 1;
    double ce = 1;
    // == get the copy number -> pmt id




#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(1); 
#endif

    const G4VTouchable* touch = track->GetTouchable();
    int pmtID_1 = touch->GetReplicaNumber(1) ; 
    if(pmtID_1 <= 0) pmtID_1 = touch->GetReplicaNumber(2) ; 
    int pmtID = pmtID_1 ;  

#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(2); 
#endif

#ifdef WITH_G4CXOPTICKS
    //int pmtID_2 = U4Touchable::AncestorReplicaNumber(touch) ; 
#endif

#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(3); 
#endif

    //int pmtID = get_pmtid(track);

#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(4); 
#endif

    /**
    G4VTouchable::GetReplicaNumer(1)
        works for NEW LPMT, SPMT 
    G4VTouchable::GetReplicaNumer(2)
        works for OLD LPMT, WPMT 

    https://github.com/simoncblyth/j/blob/main/issues/blyth-88-get_pmtid_from_track_50us.rst

    TODO: arrange singular PMT PV to have copynumber -1, distinguishing them from 0 which is a valid pmtid
    **/

#ifdef WITH_G4CXOPTICKS

    /*
    bool pmtID_consistent = pmtID_1 == pmtID && pmtID_2 == pmtID ;  
    if( pmtID_consistent == false || pmtID == 0 || pmtID == 30000 || pmtID == 300000)
    {
        std::cout 
            << "junoSD_PMT_v2::ProcessHits"
            << " pmtID " << pmtID     
            << " pmtID_1 " << pmtID_1     
            << " pmtID_2 " << pmtID_2     
            << " consistent " << ( pmtID_consistent ? "YES" : "NO " )
            << " pv " << track->GetVolume()->GetName()
            << std::endl
            ;     
        std::cout 
            << "junoSD_PMT_v2::ProcessHits" 
            << std::endl
            << U4Touchable::Desc(touch)
            << std::endl
            ;
    }
    assert( pmtID_consistent ); 
    */

#endif
        
           
    


    // = final DE = QE * CE, 
    // but QE is already applied (this is old implementation,
    // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
    // = DE: Detection Efficiency
    if(m_use_pmtsimsvc){
        qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);

        ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());

     }
     else{
        std::string volname = track->GetVolume()->GetName();		
	GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     }



    double f_angle_response = 1.0;
    double de = qe*ce*f_angle_response ;
    if (de>1.0){
        std::cout<<"junoSD_PMT_v2:: de is larger than 1.0"<<std::endl;
    }
    bool de_cull = G4UniformRand() > de ; 

























    if (de_cull) {
#ifdef WITH_G4CXOPTICKS
        m_eph = EPH::NDECULL ;  
#endif
        return false;
    }
    // ========================================================================
    // create the transient PMT Hit Object
    // ========================================================================
    // == hit time
    double hittime = postStepPoint->GetGlobalTime();
    // ========================================================================
    // Save the Hit into hit collection
    // * without merge
    // * with merge
    //   + This is for the muon simulation or some events with a lot of hits
    //   + some values can't merge.
    //   + the flags such as producerID, is from cerenkov, is from scintillation,
    //     is reemission, is original op will be not right
    // ========================================================================
    // = check the merge flag first
    if (m_pmthitmerger and m_pmthitmerger->getMergeFlag()) {
        // == if merged, just return true. That means just update the hit
        // NOTE: only the time and count will be update here, the others 
        //       will not filled.
        bool ok = m_pmthitmerger->doMerge(pmtID, hittime);
        if (ok) {
            m_merge_count += 1 ; 

#ifdef WITH_G4CXOPTICKS
            m_eph = EPH::YMERGE ;  
#endif
            return true;
        }
    }



   // = save the hit in the collection
   
    if (m_hit_type == 1) { 
        SaveNormHit(pmtID, local_pos, global_pos, hittime, track, edep);
    } else if (m_hit_type == 2) {   
        SaveMuonHit(pmtID, local_pos, hittime);
    }  


#ifdef WITH_G4CXOPTICKS
    m_profile->stamp(5); 
#endif

    return true;  
}





void junoSD_PMT_v2::clear(){}

void junoSD_PMT_v2::DrawAll(){} 

void junoSD_PMT_v2::PrintAll(){} 

void junoSD_PMT_v2::SimpleHit(const ParamsForSD_PMT&){}

int junoSD_PMT_v2::get_pmtid(G4Track* track) {
    int ipmt= -1;
    // find which pmt we are in
    // The following doesn't work anymore (due to new geometry optimization?)
    //  ipmt=fastTrack.GetEnvelopePhysicalVolume()->GetMother()->GetCopyNo();
    // so we do this:
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
                    // continue to find
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

// ============================================================================
// = Collection Efficiency Related
// ============================================================================
// == change the Collection Efficiency Mode
void junoSD_PMT_v2::setCEMode(const std::string& mode) {
    m_ce_mode = mode;
}

/**
junoSD_PMT_v2::get_ce
------------------------

m_ce_mode:20inch,

     volname:PMT_20inch_body_phys                    pmt_type:true           -> s_ce_hamamatsu    (1)
     volname:PMT_20inch_body_phys                    pmt_type:false          -> s_ce_NNVT         (2)
     .... dont see thus volname ... 
 
     volname:HamamatsuR12860_PMT_20inch_body_phys                            -> s_ce_hamamatsu    (3)  (different to above)

     
     volname:NNVTMCPPMT_PMT_20inch_body_phys         !pmt_type && !qe_type   ->  s_ce_NNVT        (4)  (different to above)
     volname:NNVTMCPPMT_PMT_20inch_body_phys         !pmt_type &&  qe_type   ->  s_ce_NNVT_highQE (5) 


BUT currently pmt_type and qe_type are always true 

pmt_type:true  -> hama
pmt_type:false -> nnvt

qe_type:true   -> nnvt-hiqe
qe_type:false   -> nnvt-standard


**/
// == get the Collection Efficiency 

double junoSD_PMT_v2::get_ce(const std::string& volname, const G4ThreeVector& localpos, bool pmt_type, bool qe_type, int &ce_cat) {
    // volname:
    // * PMT_20inch_body_phys
    // * PMT_3inch_body_phys
    if (m_ce_mode == "None") {
        ce_cat = 1; 
        return 1.0;
    } else if (m_ce_mode == "20inch") {
        // only 20inch PMT will be affected
         //G4cout << volname << G4endl;
        if (volname == "PMT_20inch_body_phys") {
            // calculate the angle theta
            double theta = localpos.theta();
            // do interpolate
            static double s_theta_NNVT[] = {
                0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
                77.5*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_NNVT[] =    {
                0.9,    0.9,   0.845,     0.801,    0.775,    0.802,
                0.802,   0.771,    0.66,
            };
            static double s_theta_hamamatsu[] = {
                0.*deg, 13.*deg, 28.*deg, 41.*deg, 55.*deg, 66.*deg,
                79.*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_hamamatsu[] =    {
                0.873,    0.873,   0.888,     0.896,    0.881,    0.9,
                0.881,     0.627,    0.262,
            };
            static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);
            if(pmt_type){
                ce_cat = 2; 
                static G4DataInterpolation s_di(s_theta_hamamatsu, s_ce_hamamatsu, 9, 0., 0.);
            }
            else
            {
               ce_cat = 3 ; 
            }

             return s_di.CubicSplineInterpolation(theta);
        }
/*
        if (volname == "PMT_20inch_body_phys") {
            // calculate the angle theta
            double theta = localpos.theta();
            // do interpolate
            static double s_theta_NNVT[] = {
                0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
                77.5*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_NNVT[] =    {
                1.0,    1.0,    0.9453,     0.9105,     0.8931,     0.9255, 
                0.9274,     0.8841,     0.734,  
            };
            static double s_ce_NNVT_highQE[] = {
               1.0,     1.0,    0.9772,     0.9723,     0.9699,     0.9697, 
               0.9452,  0.9103,     0.734,   
            };

            static double s_theta_hamamatsu[] = {
                0.*deg, 13.*deg, 28.*deg, 41.*deg, 55.*deg, 66.*deg,
                79.*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_hamamatsu[] =    {
                0.911,    0.911,    0.9222,     0.9294,     0.9235,     0.93,
                0.9095, 0.6261, 0.2733, 
            };
            static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);
            if(pmt_type){
            static G4DataInterpolation s_di(s_theta_hamamatsu, s_ce_hamamatsu, 9, 0., 0.);
            }
            if(!pmt_type && qe_type) {
            static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT_highQE, 9, 0., 0.);
            }
             return s_di.CubicSplineInterpolation(theta);
        }
*/
        else if (volname == "HamamatsuR12860_PMT_20inch_body_phys") {
            double theta = localpos.theta();

            static double s_theta_hamamatsu[] = {
                0.*deg, 13.*deg, 28.*deg, 41.*deg, 55.*deg, 66.*deg,
                79.*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_hamamatsu[] =    {
                0.911,    0.911,    0.9222,     0.9294,     0.9235,     0.93,
                0.9095, 0.6261, 0.2733, 
            };
            static G4DataInterpolation s_di(s_theta_hamamatsu, s_ce_hamamatsu, 9, 0., 0.);  
            ce_cat = 4 ; 
            return s_di.CubicSplineInterpolation(theta);
        }


        else if (volname == "NNVTMCPPMT_PMT_20inch_body_phys") {
            // calculate the angle theta
            double theta = localpos.theta();
            // do interpolate
            static double s_theta_NNVT[] = {
                0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
                77.5*deg, 85.*deg, 90.*deg,
            };
            static double s_ce_NNVT[] =    {
                1.0,    1.0,    0.9453,     0.9105,     0.8931,     0.9255, 
                0.9274,     0.8841,     0.734,  
            };
            static double s_ce_NNVT_highQE[] = {
               1.0,     1.0,    0.9772,     0.9723,     0.9699,     0.9697, 
               0.9452,  0.9103,     0.734,   
            };

            if(!pmt_type && !qe_type){
                static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);

                ce_cat = 5 ; 
                return s_di.CubicSplineInterpolation(theta);
            }
            else if(!pmt_type && qe_type) {
                static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT_highQE, 9, 0., 0.);
                ce_cat = 6 ; 
                return s_di.CubicSplineInterpolation(theta);
            }
            ce_cat = 7 ;  
        }
        ce_cat = 8 ;   // hit onto some other volname

    } else if (m_ce_mode == "20inchflat"){
        // This is a flat mode which means no matter where the photon
        // hits, use the same CE.
        if (volname == "PMT_20inch_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            // -- 2015.10.10 Tao Lin <lintao@ihep.ac.cn>
            static double mean_val = m_ce_flat_value;
            ce_cat = 9 ; 
            return mean_val;
        }
    }else if (m_ce_mode == "flat"){
        // This is a flat mode which means no matter where the photon
        // hits, use the same CE.
        // G4cout << "PMT volume name : "<<volname << G4endl;
        if (volname == "R12860TorusPMTManager_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            static double Ham20inch_R12860_mean_val = Ham20inch_m_ce_flat_value*Ham20inch_m_EAR_value;
            ce_cat = 10 ; 
            return Ham20inch_R12860_mean_val;
        }
        else if (volname == "MCP20inchPMTManager_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            static double MCP20inch_mean_val = MCP20inch_m_ce_flat_value*MCP20inch_m_EAR_value;
            ce_cat = 11 ; 
            return MCP20inch_mean_val;
        }
        else if (volname == "Ham8inchPMTManager_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            static double Ham8inch_mean_val = Ham8inch_m_ce_flat_value*Ham8inch_m_EAR_value;
            ce_cat = 12 ; 
            return Ham8inch_mean_val;
        }
        else if (volname == "MCP8inchPMTManager_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            static double MCP8inch_mean_val = MCP8inch_m_ce_flat_value*MCP8inch_m_EAR_value;
            ce_cat = 13 ; 
            return MCP8inch_mean_val;
        }
        else if (volname == "HZC9inchPMTManager_body_phys") {
            // FIXME It's a fixed number here, we can make it a variable
            // if it is needed to be modified.
            static double HZC9inch_mean_val = HZC9inch_m_ce_flat_value*HZC9inch_m_EAR_value;
            ce_cat = 14 ; 
            return HZC9inch_mean_val;
        }
    }else if (m_ce_mode == "20inchfunc") {
        // In this mode, user needs to input:
        // 1. a function, which can be interpret by ROOT TF1.
        // 2. a list of parameters
        if (!m_ce_func) {
            G4cout << "WARNING: The CE Function is not defined." << G4endl;
            assert(m_ce_func);
        }
        // calculate the angle theta
        double theta = localpos.theta(); // unit: radians
        if (theta>CLHEP::halfpi) { theta = CLHEP::halfpi; }
        // convert angle
        // NOTE: the angle needs to be converted
        // 1. pi/2-theta
        // 2. radian -> degree
        theta = (CLHEP::halfpi-theta)/degree;
        ce_cat = 15 ; 
        return m_ce_func->Eval(theta);
    } else {
        ce_cat = 16 ; 
        G4cout << "WARNING: unknown CE mode " << m_ce_mode << G4endl;
    }
    return 1.0;
}

/*
junoSD_PMT_v2::GetQEandCEByOldWay 

 
return ce value and qe value by old implementation,thus it assumed that the QE has been operated through the G4OpBoundaryProcess at first when you want to use this method.

note: when you use --no-use-pmtsimsvc, you must add --disable-pmt-optical-model as well.

*/

bool junoSD_PMT_v2::GetQEandCEByOldWay(double & qe , double & ce , int pmtID,std::string volname, G4ThreeVector local_pos){
    
    // calculate QE from PDE from svc
   // double qe =1.;
    double eff_pde = 1.;
    double qe_calc = 1.;
    if(PMT::IsCD(pmtID) and PMT::Is20inch(pmtID)){
        eff_pde = m_PMTSimParsvc->get_pde(pmtID);
        if( m_PMTParamsvc->isHamamatsu(pmtID)) {
            qe_calc = eff_pde / m_eff_ce_Hamamatsu;
        } else if ( m_PMTParamsvc->isHighQENNVT(pmtID) ) {
            qe_calc = eff_pde / m_eff_ce_NNVT_HiQE;
        } else if ( m_PMTParamsvc->isNormalNNVT(pmtID) ) {
            qe_calc = eff_pde / m_eff_ce_NNVT_Normal;
        }
    }
    else if(PMT::IsWP(pmtID)) {
        qe_calc = 0.3;
    } else if(PMT::IsCD(pmtID) and PMT::Is3inch(pmtID)) {
        qe_calc = m_PMTSimParsvc->get_QE(pmtID);
    }                                                             
    qe = qe_calc*m_qescale ;  // <-- NB m_qescale depends on the last pmtID hit and m_enable_optical_model
      
    int ce_cat = 0 ;
    bool pmt_type = true;
    bool qe_type  = true;   
    if(PMT::IsCD(pmtID) and PMT::Is20inch(pmtID)){
        pmt_type = m_PMTParamsvc->isHamamatsu(pmtID) ;
        qe_type = m_PMTParamsvc->isHighQENNVT(pmtID) ;
    }
    ce = get_ce(volname, local_pos, pmt_type, qe_type, ce_cat );          


    return true ;                                               
}

void junoSD_PMT_v2::SaveNormHit(int pmtID, G4ThreeVector local_pos, G4ThreeVector global_pos,double hittime, G4Track *  track ,double edep){

#ifdef WITH_G4CXOPTICKS
      m_jpmt_dbg->SaveNormHit_count += 1 ; 
#endif
   
    const G4AffineTransform& trans = track->GetTouchable()->GetHistory()->GetTopTransform();

    // == momentum and polarization
    G4ThreeVector local_pol = trans.TransformAxis(track->GetPolarization());
    local_pol = local_pol.unit();
    G4ThreeVector local_dir = trans.TransformAxis(track->GetMomentum());
    local_dir = local_dir.unit();
      
    // == wavelength 
    double wavelength = twopi*hbarc / edep;
      
    // == additional information from User Track information
    int producerID = -1;
    bool is_from_cerenkov = false;
    bool is_reemission = false;
    bool is_original_op = false;
    double t_start = 0;
    G4ThreeVector boundary_pos;
    G4VUserTrackInformation* trkinfo = track->GetUserInformation();
    if (trkinfo) {
        NormalTrackInfo* normaltrk = dynamic_cast<NormalTrackInfo*>(trkinfo);
        if (normaltrk) {
            // if there are traced ancestors, use the track id of final state.
            producerID = normaltrk->GetOriginalTrackID();
            if (normaltrk->getTracedAncestors().size()
                && normaltrk->getTracedAncestors().back() != -1) {
                producerID = normaltrk->getTracedAncestors().back();
            }

            is_from_cerenkov = normaltrk->isFromCerenkov();
            is_reemission = normaltrk->isReemission();
                                                                           
            t_start = normaltrk->getOriginalOPStartTime();
                                                                           
            is_original_op = normaltrk->isOriginalOP();
            boundary_pos = normaltrk->getBoundaryPos();
        }
    }  



    junoHit_PMT* hit_photon = new junoHit_PMT();
    hit_photon->SetPMTID(pmtID);
    hit_photon->SetWeight(1.0);
    hit_photon->SetTime(hittime);
    hit_photon->SetWavelength(wavelength);
    hit_photon->SetKineticEnergy(edep);
    hit_photon->SetPosition(local_pos);
    hit_photon->SetTheta(local_pos.theta());
    hit_photon->SetPhi(local_pos.phi());
    hit_photon->SetMomentum(local_dir); 
    hit_photon->SetPolarization(local_pol); 
                                                                  
    hit_photon->SetGlobalPosition(global_pos);
    hit_photon->SetGlobalMomentum(track->GetMomentum()); 
    hit_photon->SetGlobalPolarization(track->GetPolarization()); 
                     
    hit_photon->SetCount(1); // FIXME
                                                
    hit_photon->SetProducerID(producerID);
    hit_photon->SetFromCerenkov(is_from_cerenkov);
    hit_photon->SetReemission(is_reemission);
    hit_photon->SetOriginalOP(is_original_op);
    hit_photon->SetOriginalOPStartT(t_start);
    hit_photon->SetBoundaryPosition(boundary_pos);

    // == insert                                      
    if (m_pmthitmerger) {
        m_pmthitmerger->saveHit(hit_photon);
    }

#ifdef WITH_G4CXOPTICKS_DEBUG
    LOG(LEVEL) << " pmtID "  << std::setw(7) << pmtID ; 
    U4Hit_Debug hit_dbg ; 
    hit_dbg.label = U4PhotonInfo::Get(track);
    hit_dbg.add();
#endif


}

void junoSD_PMT_v2::SaveMuonHit(int pmtID, G4ThreeVector local_pos,double hittime){

#ifdef WITH_G4CXOPTICKS
      m_jpmt_dbg->SaveMuonHit_count += 1 ; 
#endif
 
             
    // save the muon only
 
    junoHit_PMT_muon* hit_photon = new junoHit_PMT_muon();
    hit_photon->SetPMTID(pmtID);
    hit_photon->SetTime(hittime);
    hit_photon->SetCount(1); // FIXME
    hit_photon->SetTheta(local_pos.theta());
    hit_photon->SetPhi(local_pos.phi());
    if (m_pmthitmerger) {
        m_pmthitmerger->saveHit(hit_photon);                   
    }  
       
}

                     
void
junoSD_PMT_v2::setCEFunc(const std::string& func, const std::vector<double>& param)
{
    // detele origial function
    if (m_ce_func) {
        delete m_ce_func;
        m_ce_func = 0;
    }

    // Info:
    std::cout << "Following is the CE Function detail:" << std::endl;
    std::cout << "CE Function: " << func << std::endl;
    // angle from 0 to 90 deg.
    // angle is from equator
    m_ce_func = new TF1("ce", func.c_str(), 0, 90);
    std::cout << "CE Params: ";
    for (size_t i = 0; i < param.size(); ++i) {
        std::cout << param[i] << " "; 
        m_ce_func->SetParameter(i, param[i]);
    }
    std::cout << std::endl;
}



/**
junoSD_PMT_v2::getQuantumEfficiency
------------------------------------

Would be better for efficiency transitions to align with pmt category boundaries
so could then have a switch on the category. The reason it is better is that 
the categorization then happens in one place only (rather than being spead all over the code base)
making it easier to change.  Having selection smeared around means changing it will 
likely cause bugs. 

**/

double junoSD_PMT_v2::getQuantumEfficiency(int pmtID) const 
{
    double eff_pde = 1.;
    double qe_calc = 1.;
    double qescale = m_qescale ; 

    if(PMT::IsCD(pmtID) and PMT::Is20inch(pmtID))
    {
        qescale = m_enable_optical_model ? m_qescale_optical_model : m_qescale ; 

        eff_pde = m_PMTSimParsvc->get_pde(pmtID);
        if( m_PMTParamsvc->isHamamatsu(pmtID)) 
        {
            qe_calc = eff_pde / m_eff_ce_Hamamatsu;
        } 
        else if ( m_PMTParamsvc->isHighQENNVT(pmtID) ) 
        {
            qe_calc = eff_pde / m_eff_ce_NNVT_HiQE;
        } 
        else if ( m_PMTParamsvc->isNormalNNVT(pmtID) ) 
        {
            qe_calc = eff_pde / m_eff_ce_NNVT_Normal;
        }
    }
    else if(PMT::IsWP(pmtID)) 
    {
        qe_calc = 0.3;
    } 
    else if(PMT::IsCD(pmtID) and PMT::Is3inch(pmtID)) 
    {
        qe_calc = m_PMTSimParsvc->get_QE(pmtID);
    } 
    return qescale*qe_calc ; 
}




/**
junoSD_PMT_v2::getCollectionEfficiency
----------------------------------------

This method aims to replace get_ce using the m_PMTEfficiency
member that needed for the Opticks bulk collection of angular efficiencies.

Note that the parcat and simcat obtained by the below
are in a difference enum "languages"::

   int parcat = m_PMTParamsvc->getPMTCategory(pmtID); 
   int simcat = m_PMTSimParsvc->getPMTCategory(pmtID); 

After translating to allow comparison there is still a difference
regards HiQENNVT for thousands of PMTs, see ~/jnu/PMT.py 

**/
double junoSD_PMT_v2::getCollectionEfficiency(double theta, int pmtID) const 
{
    int simcat = (PMT::IsCD(pmtID) and PMT::Is20inch(pmtID)) ? m_PMTParamsvc->getPMTCategory(pmtID) : -1 ; 
    //assert(PMTEfficiency::GetPMTCategoryType() == 'S');
    return m_PMTEfficiency->getEfficiency(theta, simcat) ; 
}

double junoSD_PMT_v2::getEfficiencyScale() const 
{
    return m_angle_response ; 
}

double junoSD_PMT_v2::getDetectionEfficiency(double theta, int pmtID) const 
{
    double qe = getQuantumEfficiency(pmtID); 
    double ce = getCollectionEfficiency(theta, pmtID); 
    double es = getEfficiencyScale(); 
    double de = qe*ce*es; 
    return de ; 
}

PMTEfficiencyTable* junoSD_PMT_v2::getPMTEfficiencyTable() const 
{
    return m_PMTEfficiencyTable ; 
}


void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
{
#ifdef WITH_G4CXOPTICKS
    m_jpmt_opticks->EndOfEvent(HCE, m_eventID );    
#endif
    G4cout << "junoSD_PMT_v2::EndOfEvent" << desc() << G4endl ; 
}

bool junoSD_PMT_v2::gpu_simulation() const { return m_jpmt_opticks->gpu_simulation() ;  }

std::string junoSD_PMT_v2::desc() const 
{ 
    std::stringstream ss ; 
    ss << " eventID " << m_eventID 
       << " opticksMode " << m_opticksMode
       << " hitCollection " << hitCollection->entries()
       << " hcMuon " << hitCollection_muon->entries()  
       << " hcOpticks " << (hitCollection_opticks?hitCollection_opticks->entries():-1)
       << " GPU " << ( gpu_simulation() ? "YES" : "NO" )
       ;
    std::string str = ss.str(); 
    return str ; 
}

