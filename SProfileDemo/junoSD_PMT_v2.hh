//--------------------------------------------------------------------------
//                            junoSD_PMT_v2
//
// PMTs are difined as sensitive detector. They collect hits on them.
// The data members of hits are set up here using the information of G4Step.
// -------------------------------------------------------------------------
// Author: Liang Zhan, 2006/01/27
// Modified by: Weili Zhong, 2006/03/01
// -------------------------------------------------------------------------

#ifndef junoSD_PMT_v2_h
#define junoSD_PMT_v2_h 1

#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"
#include "junoHit_PMT.hh"
#include "junoHit_PMT_muon.hh"
#include "IToolForSD_PMT.h"
#include "PMTHitMerger.hh"
#include <map>
#include <vector>
#include <string>
#include <TF1.h>

#include "Geometry/PMTParamSvc.h"
#include "IPMTSimParamSvc/IPMTSimParamSvc.h"
//#include "PMTSimParamSvc/PMTSimParamSvc.h"
//////////////////////////////////////////////////////////////////////////

class G4Step;
class G4Track;
class G4HCofThisEvent;

class PMTEfficiency ; 
class PMTEfficiencyTable ; 

class junoSD_PMT_v2_Opticks ; 

#ifdef WITH_G4CXOPTICKS
#include <string>
#include <sstream>
#include <iomanip>
#include "plog/Severity.h"
struct junoSD_PMT_v2_Debug ;
template<int N> struct SProfile ; 
#endif


class junoSD_PMT_v2 : public G4VSensitiveDetector, public IToolForSD_PMT
{
    public:
        junoSD_PMT_v2(const std::string& name, int opticksMode);
        ~junoSD_PMT_v2();

        void Initialize(G4HCofThisEvent*HCE);

        template <typename T>
        static T* GetOpBoundaryProcess(); 

#ifdef WITH_G4CXOPTICKS
        G4bool ProcessHits_(G4Step*aStep,G4TouchableHistory*ROhist);
        junoSD_PMT_v2_Debug* getProcessHitsDebug() const ;  
#endif
        G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);

        void clear();
        void DrawAll();
        void PrintAll();
        void SimpleHit( const ParamsForSD_PMT& );

        void setCEMode(const std::string& mode);
        void setCEFlatValue(double v) {m_ce_flat_value = v;}
        void setMergeFlag(bool f) { m_merge_flag = f; }
        void setMergeWindows(double t) { m_time_window = t; }
        void setMerger(PMTHitMerger* phm) { m_pmthitmerger=phm; }
        void setMergerOpticks(PMTHitMerger* phm) { m_pmthitmerger_opticks=phm; }
        void setPMTParamSvc(PMTParamSvc* para){ m_PMTParamsvc=para; }
        void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }

        PMTParamSvc*     getPMTParamSvc() const { return m_PMTParamsvc ; }
        IPMTSimParamSvc* getPMTSimParamSvc() const { return m_PMTSimParsvc ; }
        PMTHitMerger*    getMergerOpticks() const ;  


        void setHitType(int i) { m_hit_type = i; }
        int getHitType() { return m_hit_type; }
        int getOpticksMode() const { return m_opticksMode ; }

        void disableSD() { m_disable = true; }
        void enableSD() { m_disable = false; }

        void setCEFunc(const std::string& func, const std::vector<double>& param);

        void enableOpticalModel() { m_enable_optical_model = true; }

    private:
        int get_pmtid(G4Track*);
        double get_ce(const std::string& volname, const G4ThreeVector& localpos, bool pmt_type, bool qe_type, int& ce_cat);

        bool GetQEandCEByOldWay(double & qe , double & ce , int pmtID, std::string volname, G4ThreeVector local_pos);
	
        void SaveNormHit(int pmtID, G4ThreeVector local_pos, G4ThreeVector global_pos,double hittime , G4Track *  track ,double edep);
	
        void SaveMuonHit(int pmtID, G4ThreeVector local_pos,double hittime);
    private:
        junoHit_PMT_Collection* hitCollection;
        junoHit_PMT_muon_Collection* hitCollection_muon;
        junoHit_PMT_Collection* hitCollection_opticks ;
    private:
        int m_eventID ; 
        bool m_debug;
        std::string m_ce_mode;
        double m_qescale ; 
        double m_qescale_optical_model ; 
        double m_angle_response ; 

        // if flat mode enabled, this is used to set the fixed number
        double m_ce_flat_value;
        double MCP20inch_m_ce_flat_value;
        double MCP8inch_m_ce_flat_value;
        double Ham20inch_m_ce_flat_value;
        double Ham8inch_m_ce_flat_value;
        double HZC9inch_m_ce_flat_value;

        double MCP20inch_m_EAR_value;
        double MCP8inch_m_EAR_value;
        double Ham20inch_m_EAR_value;
        double Ham8inch_m_EAR_value;
        double HZC9inch_m_EAR_value;

        // 20inchfunc mode, function mode
        std::string m_ce_func_str;
        std::vector<double> m_ce_func_params;
        TF1* m_ce_func;

        //  20inch mode, interpolation mode
        double m_eff_ce_Hamamatsu = 0.872;
        double m_eff_ce_NNVT_Normal = 0.916;
        double m_eff_ce_NNVT_HiQE = 0.957;

        // flag to enable/disable the sensitive detector
        // disable is true, means disable the SD.
        bool m_disable;

        bool m_enable_optical_model;
    private:
        // ========================================================================
        // merge related
        // ========================================================================
        // = merge flag 
        bool m_merge_flag;
        int  m_merge_count ; 
        // = the time window is used when merge is enabled.
        double m_time_window;

        typedef std::multimap<int, int> PMTID2COLIDS;
        typedef std::pair< PMTID2COLIDS::iterator, PMTID2COLIDS::iterator > PMTITER;
        PMTID2COLIDS m_pmtid2idincol;

        // new merger
        PMTHitMerger* m_pmthitmerger;
        PMTHitMerger* m_pmthitmerger_opticks;
        PMTParamSvc* m_PMTParamsvc;
        IPMTSimParamSvc* m_PMTSimParsvc;
        // ========================================================================
        // Hit Collection switcher
        // * normal, junoHit_PMT
        // * for muon, junoHit_PMT_muon
        // ========================================================================
        G4int m_hit_type;
        G4int m_opticksMode; 
        char  m_category_type ; 

    private:
        PMTEfficiency*         m_PMTEfficiency ;  
        PMTEfficiencyTable*    m_PMTEfficiencyTable ; 
#ifdef WITH_G4CXOPTICKS
        static const  plog::Severity LEVEL ; 
        junoSD_PMT_v2_Debug* m_jpmt_dbg  ; 
        int                  m_eph  ;  // ProcessHits enumeration
        int                  m_label_id ;  // photon label  
        SProfile<16>*        m_profile ; 
#endif
        junoSD_PMT_v2_Opticks* m_jpmt_opticks ; 
    public:
        double              getQuantumEfficiency(int pmtID) const ;
        double              getCollectionEfficiency(double theta, int pmtID) const ;  
        double              getEfficiencyScale() const ; 
        double              getDetectionEfficiency(double theta, int pmtID) const ;  
    public:
        PMTEfficiencyTable* getPMTEfficiencyTable() const  ;
    public:
        void                EndOfEvent(G4HCofThisEvent*HCE);
    private:
       bool m_use_pmtsimsvc;
    public:
       void setUsePmtSimSvc(bool f){ m_use_pmtsimsvc = f ; }
    public:
       bool gpu_simulation() const ; 
       std::string desc() const ; 

};

#endif

