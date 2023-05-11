totalPE
=========

::

    epsilon:junosw blyth$ jgl totalPE
    ./Analysis/BasicDist/share/pyjob.py
    ./Analysis/BasicDist/src/BasicDistAlg.h
    ./Analysis/BasicDist/src/BasicDistAlg.cc
    ./Simulation/DetSimV2/DetSimMTUtil/src/GlobalDetSimOutAlg.cc
    ./Simulation/DetSimV2/DetSimMTUtil/src/GlobalDetSimOutAlg.h
    ./Simulation/DetSimV2/AnalysisCode/include/NormalAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc
    ./Examples/Tutorial/share/RecAnalysis/uniform/RecAnalysis.c
    ./Examples/Tutorial/share/RecAnalysis/center/RecAnalysis.c
    ./Examples/Tutorial/share/SimAnalysis/totalPE_3inch.C
    ./Examples/Tutorial/share/SimAnalysis/SimAnalysisMu.C
    ./Examples/Tutorial/share/SimAnalysis/totalPE_20inch.C
    ./Examples/Tutorial/share/SimAnalysis/env
    ./Examples/Tutorial/share/CalibAnalysis/CalibAnalysisMu.C
    ./Doc/detsim/quickstart2.md
    ./Doc/oum/source/quickstart/quickstart2.md
    ./Reconstruction/RecMuon/WPChargeClusterRec/src/WPChargeClusterRec.cc
    ./Reconstruction/OMILREC/src/OMILREC.cc
    ./Validation/JunoTest/production/IBD-BasicDistribution/BasicDistribution.cc
    epsilon:junosw blyth$ 


::

    196 void
    197 NormalAnaMgr::EndOfEventAction(const G4Event* evt) {
    198 
    199 
    200 
    201     G4SDManager * SDman = G4SDManager::GetSDMpointer();
    202     G4int CollID = SDman->GetCollectionID("hitCollection");
    203 
    204     junoHit_PMT_Collection* col = 0;
    205     G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    206     if (!HCE or CollID<0) {
    207         LogError << "No hits collection found." << std::endl;
    208     } else {
    209         col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    210     }
    211 
    212     int totPE = 0;
    213     if (col) {
    214         int n_hit = col->entries();
    215         m_nPhotons = n_hit;
    216        // if (n_hit > 2000000) { m_nPhotons = 2000000; }
    217         for (int i = 0; i < n_hit; ++i) {
    218             totPE += (*col)[i]->GetCount();
    219 
    220 
    221             int copyno = (*col)[i]->GetPMTID();
    222             if(copyno < 30000){
    223                 m_cd_lpmt_totalPE += (*col)[i]->GetCount();
    224                 m_cd_totalPE += (*col)[i]->GetCount();
    225 
    226                 if( m_pmt_param_svc -> isHamamatsu(copyno)){
    227                          m_cd_hamamatsu_totalPE += (*col)[i]->GetCount();
    228                    }
    229                    else{
    230                          m_cd_nnvt_totalPE  += (*col)[i]->GetCount();
    231                    }
    232 
    233                }
    234              else if( copyno >= 300000 ){
    235 
    236                  m_cd_totalPE += (*col)[i]->GetCount();
    237                  m_cd_spmt_totalPE += (*col)[i]->GetCount();
    238              }



Enable normal anamgr for OPTICKS_MODE 0
-------------------------------------------






