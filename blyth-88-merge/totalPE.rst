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




    epsilon:junosw blyth$ jgr junoHit_PMT_Collection
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:// junoHit_PMT_Collection is a vector of hits
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT.hh:    junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection* hitCollection_opticks ;
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool init(junoHit_PMT_Collection* hitcol);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:  junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc:  hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        hitCollection_opticks = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[2]);
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::init(junoHit_PMT_Collection* hitcol) {
    ./Simulation/DetSimV2/DetSimMTUtil/src/LSExpMTEventAction.cc:                junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/DetSimMTUtil/src/LSExpMTEventAction.cc:                    col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/MuonToySim.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    epsilon:junosw blyth$ 



jcv junoHit_PMT::

    022 class junoHit_PMT : public G4VHit
     23 {
     24   public:
     25     junoHit_PMT(G4int z);
    ...
    119     inline void SetPMTID(G4int z) { pmtID = z; }
    120     inline G4int GetPMTID() const { return pmtID; }
    121 




Enable normal anamgr for OPTICKS_MODE 0
-------------------------------------------

::

    608 ntds() 
    609 {
    ...
    815    if [ "$mode" == "0" ]; then
    816        opts="$opts $(anamgr-normal) "
    817    else
    818        opts="$opts $(anamgr) "
    819    fi


    538 anamgr-normal(){ cat << EOU
    539 --anamgr-normal
    540 --no-anamgr-genevt
    541 --no-anamgr-edm-v2
    542 --no-anamgr-grdm
    543 --no-anamgr-deposit
    544 --no-anamgr-deposit-tt
    545 --no-anamgr-interesting-process
    546 --no-anamgr-optical-parameter
    547 --no-anamgr-timer
    548 EOU
    549 }



::

    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 0 eventID 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    python: /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:345: virtual G4VParticleChange* G4Cerenkov_modified::PostStepDoIt(const G4Track&, const G4Step&): Assertion `a_ui == nullptr' failed.

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffccf266b9 in G4Cerenkov_modified::PostStepDoIt (this=0x9bed500, aTrack=..., aStep=...)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:345
    #5  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffdba8556b in G4SteppingManager::InvokePostStepDoItProcs() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffdba82d3d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffce5cc45d in G4SvcRunManager::SimulateEvent (this=0x927140, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29


::

    342	#ifdef WITH_G4CXOPTICKS
    343	  bool is_opticks_genstep = fNumPhotons > 0 ; 
    344	  G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
    345	  assert( a_ui == nullptr );  // should always be null, as process C is not applicable to RE-photons
    346	
    347	  if(is_opticks_genstep && (m_opticksMode & 1 ))
    348	  {
    349	      U4::CollectGenstep_G4Cerenkov_modified( 



HMM : need to rebuild without  WITH_G4CXOPTICKS


1. Comment opticks line in $JUNOTOP/bashrc.sh 
2. Recommnect
3. Checkout and build the branch without WITH_G4CXOPTICKS::

    N[blyth@localhost ~]$ jo
    /data/blyth/junotop/junosw
    # On branch main
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ git branch 
      blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    * main
    N[blyth@localhost junosw]$ git checkout blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    Switched to branch 'blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess'
    N[blyth@localhost junosw]$ git s
    # On branch blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ 
    N[blyth@localhost junosw]$ ./build_Debug.sh 




::

    N[blyth@localhost junosw]$ cd  /tmp/u4debug/ntds0/
    N[blyth@localhost ntds0]$ which root
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/bin/root
    N[blyth@localhost ntds0]$ root
       ------------------------------------------------------------------
      | Welcome to ROOT 6.24/06                        https://root.cern |
      | (c) 1995-2021, The ROOT Team; conception: R. Brun, F. Rademakers |
      | Built for linuxx8664gcc on Sep 02 2021, 14:20:23                 |
      | From tags/v6-24-06@v6-24-06                                      |
      | With g++ (GCC) 8.3.0                                             |
      | Try '.help', '.demo', '.license', '.credits', '.quit'/'.q'       |
       ------------------------------------------------------------------

    root [0] TFile* f = new TFile("sample_detsim_user.root")
    (TFile *) 0x3688b40
    root [1] f->ls()
    TFile**		sample_detsim_user.root	
     TFile*		sample_detsim_user.root	
      KEY: TTree	evt;1	evt
    root [5] TTree* e = (TTree*)f->Get("evt");
    root [7] e->ls()
    OBJ: TTree	evt	evt : 0 at: 0x3c33100
    root [8] e->Scan()
    ************************************************************************************************************
    *    Row   * evtID.evt * edep.edep * edepX.ede * edepY.ede * edepZ.ede * nPhotons. * totalPE.t * LpmtPE.Lp *
    ************************************************************************************************************
    *        0 *         0 * 1.0000001 * 49.224033 * -54.32510 * -242.2039 *        36 *        36 *         0 *
    ************************************************************************************************************
    (long long) 1
    root [9] 


    root [15] e->Scan("nPhotons:totalPE:LpmtPE:SpmtPE:NNVTPE:HamaPE:CDPE:WPPE")
    ************************************************************************************************************
    *    Row   *  nPhotons *   totalPE *    LpmtPE *    SpmtPE *    NNVTPE *    HamaPE *      CDPE *      WPPE *
    ************************************************************************************************************
    *        0 *        36 *        36 *         0 *        36 *         0 *         0 *        36 *         0 *
    ************************************************************************************************************
    (long long) 1


::

    N[blyth@localhost ntds0]$ cat ~/j/blyth-88-merge/ScanPE.C
    {
       TFile* f = new TFile("sample_detsim_user.root") ; 
       TTree* e = (TTree*)f->Get("evt"); 
       e->Scan("nPhotons:totalPE:LpmtPE:SpmtPE:NNVTPE:HamaPE:CDPE:WPPE"); 
    }

      

    N[blyth@localhost ntds0]$ root -l ~/j/blyth-88-merge/ScanPE.C 
    root [0] 
    Processing /home/blyth/j/blyth-88-merge/ScanPE.C...
    ************************************************************************************************************
    *    Row   *  nPhotons *   totalPE *    LpmtPE *    SpmtPE *    NNVTPE *    HamaPE *      CDPE *      WPPE *
    ************************************************************************************************************
    *        0 *        36 *        36 *         0 *        36 *         0 *         0 *        36 *         0 *
    ************************************************************************************************************
    root [1] 




HMM what could be wrong ?
---------------------------

1. Old way of getting QE and CE based on string names needs to be updated for volname changes


::
 
     479     if(m_use_pmtsimsvc){
     480         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     481         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     482      }
     483      else{
     484         std::string volname = track->GetVolume()->GetName();
     485     GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     486      }
     487 


ProcessHits debug : shows lots of edep 0  onto LPMT copyno
------------------------------------------------------------

::

   BP=junoSD_PMT_v2::ProcessHits ntds0



    (gdb) b 409
    Breakpoint 2 at 0x7fffd1925fc0: file /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc, line 409.
    (gdb) c
    Continuing.

    Breakpoint 2, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:409
    409	    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    (gdb) b 413
    Breakpoint 3 at 0x7fffd1925feb: file /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc, line 413.
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $2 = 0
    (gdb) p postStepPoint->GetStepStatus()
    $3 = fGeomBoundary
    (gdb) p get_pmtid(track)
    $4 = 5999




    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $8 = 0
    (gdb) p get_pmtid(track)
    $9 = 6266
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $10 = 0
    (gdb) p get_pmtid(track)
    $11 = 5425
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $12 = 0
    (gdb) p get_pmtid(track)
    $13 = 5425
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $14 = 0
    (gdb) p get_pmtid(track)
    $15 = 4378
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $16 = 0
    (gdb) p get_pmtid(track)
    $17 = 13509
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $18 = 0
    (gdb) p get_pmtid(track)
    $19 = 7294
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $20 = 0
    (gdb) p get_pmtid(track)
    $21 = 7294
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $22 = 0
    (gdb) p get_pmtid(track)
    $23 = 7294
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $24 = 0
    (gdb) p get_pmtid(track)
    $25 = 7294
    (gdb) c
    Continuing.

    Breakpoint 3, junoSD_PMT_v2::ProcessHits (this=0x5b7ee60, step=0xacad60) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:413
    413	    if (edep<=0.0) {
    (gdb) p edep
    $26 = 0
    (gdb) p get_pmtid(track)
    $27 = 16356
    (gdb) 


Where is edep set in old and new workflows ?
-----------------------------------------------

::

     408     //G4StepPoint* preStepPoint = step->GetPreStepPoint();
     409     G4StepPoint* postStepPoint = step->GetPostStepPoint();
     410     double edep = step->GetTotalEnergyDeposit();
     411     // = only when the photon is detected by the surface, the edep is non-zero.
     412     // = the QE is already applied in the OpBoundaryProcess::DoAbsorption
     413     if (edep<=0.0) {
     414 #ifdef WITH_G4CXOPTICKS
     415         m_eph = EPH::NEDEP ;
     416 #endif
     417         return false;
     418     }




Check C4, possibly are failing to pick up the efficiency and using zero ?
----------------------------------------------------------------------------

* BUT: this same code is used both for natural and unnatural PMT geometry ?

::

    321 inline
    322 void C4OpBoundaryProcess::DoAbsorption()
    323 {
    324               theStatus = Absorption;
    325 
    326               if ( G4BooleanRand(theEfficiency) ) {
    327 
    328                  // EnergyDeposited =/= 0 means: photon has been detected
    329                  theStatus = Detection;
    330                  aParticleChange.ProposeLocalEnergyDeposit(thePhotonMomentum);
    331               }
    332               else {
    333                  aParticleChange.ProposeLocalEnergyDeposit(0.0);
    334               }
    335 
    336               NewMomentum = OldMomentum;
    337               NewPolarization = OldPolarization;
    338 
    339 //              aParticleChange.ProposeEnergy(0.0);
    340               aParticleChange.ProposeTrackStatus(fStopAndKill);
    341 }


::

    251 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    252 {
    253     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    254     G4double energy = thePhotonMomentum ;
    255     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    256     G4double energy_eV = energy/CLHEP::eV ;
    257     G4double wavelength_nm = wavelength/CLHEP::nm ;
    258 
    259     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;
    262     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    263 
    264     std::array<double,16> a_spec ;
    265     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    266     StackSpec<double,4> spec ;
    267     spec.import( a_spec );
    268 
    269     Stack<double,4> stack(wavelength_nm, minus_cos_theta, spec );
    270 


jcv junoPMTOpticalModel::

    406 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
    407 {
    408     const G4Track* track = fastTrack.GetPrimaryTrack();
    409 
    410     _photon_energy  = energy;    // from ModelTrigger
    411     _wavelength     = twopi*hbarc/energy;
    412 
    413     int pmtid  = get_pmtid(track);
    414 
    415 #ifdef PMTSIM_STANDALONE
    ...
    452 #else
    453     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    454    
    455     n_glass         = _rindex_glass->Value(_photon_energy);
    456    
    457     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    458 
    459     n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    460     k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    461     d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;
    462 
    463     n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    464     k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    465     d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;
    466 #endif
    ...
    539 
    540     An = 1.0 - (fT_n+fR_n);
    541     escape_fac  = _qe/An;
    ...
    566     G4double rand_absorb = G4UniformRand();
    567     G4double rand_escape = G4UniformRand();
    568 
    569     if(rand_absorb < A){
    570         // absorbed
    571         fastStep.ProposeTrackStatus(fStopAndKill);
    572         if(rand_escape<escape_fac){
    573         // detected
    574             fastStep.ProposeTotalEnergyDeposited(_photon_energy);
    575         }
    576     }else if(rand_absorb < A+R){



Custom4 not built with debug symbols
---------------------------------------


::

    BP=C4CustomART::doIt ntds0

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    Breakpoint 1, 0x00007fffd0eb43b6 in C4CustomART::doIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.4/lib64/libCustom4.so
    (gdb) bt
    #0  0x00007fffd0eb43b6 in C4CustomART::doIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.4/lib64/libCustom4.so
    #1  0x00007fffd0eabbf6 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.4/lib64/libCustom4.so
    #2  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffdba8556b in G4SteppingManager::InvokePostStepDoItProcs() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007fffdba82d3d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so



    (gdb) list
    7	./Programs/python.c: No such file or directory.
    (gdb) f 0
    #0  0x00007fffd0eb43b6 in C4CustomART::doIt(G4Track const&, G4Step const&) () from /data/blyth/junotop/ExternalLibs/custom4/0.1.4/lib64/libCustom4.so
    (gdb) list
    7	in ./Programs/python.c
    (gdb) 


Need::

    -DCMAKE_BUILD_TYPE=Debug 


    143 function juno-ext-libs-custom4-conf- {
    144     # begin to configure
    145     if [ ! -d "custom4-build" ]; then
    146         mkdir custom4-build
    147     fi
    148     pushd custom4-build
    149     cmake .. -DCMAKE_INSTALL_PREFIX:PATH=$(juno-ext-libs-custom4-install-dir) -DCMAKE_BUILD_TYPE=${CUSTOM4_CMAKE_BUILD_TYPE:-Release} 
    150 
    151     # formerly needed  -DG4MULTITHREADED=ON
    152     # but now trying to grab cflags from the geant4-config 
    153     # to be consistent with the junosw geant4-config approach 
    154     popd
    155 }

::

    N[blyth@localhost junoenv]$ CUSTOM4_CMAKE_BUILD_TYPE=Debug bash junoenv libs all custom4



Now can see whats happening::


    (gdb) bt
    #0  C4CustomART::doIt (this=0x9cc1810, aTrack=...) at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4CustomART.h:300
    #1  0x00007fffd0eabbf6 in C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:513
    #2  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffdba8556b in G4SteppingManager::InvokePostStepDoItProcs() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so


    (gdb) f 0 
    #0  C4CustomART::doIt (this=0x9cc1810, aTrack=...) at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4CustomART.h:253
    253	    G4double minus_cos_theta = OldMomentum*theRecoveredNormal ; 
    (gdb) f 1
    #1  0x00007fffd0eabbf6 in C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:513
    513	                    m_custom_art->doIt(aTrack, aStep) ;  
    (gdb) f 2
    #2  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    (gdb) 



HMM, accessor giving crazy small _qe::

    (gdb) p _qe
    $1 = 7.0234395950208244e-319
    (gdb) p pmtid
    $2 = 5999
    (gdb) p energy
    $3 = 2.9395728335807777e-06
    (gdb) p energy_eV
    $4 = 2.9395728335807778
    (gdb) p accessor->get_pmtid_qe( pmtid, energy )
    $5 = 7.0234395950208244e-319
    (gdb) p accessor->get_pmtid_qe( pmtid, energy_eV )
    $6 = 2.4703282292062327e-323
    (gdb) 


    (gdb) b 300
    Breakpoint 4 at 0x7fffd0eb4783: file /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4CustomART.h, line 300.
    (gdb) c
    Continuing.

    Breakpoint 4, C4CustomART::doIt (this=0x9cc1810, aTrack=...) at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4CustomART.h:300
    300	    bool expect = theEfficiency <= 1. ; 
    (gdb) p theEfficiency 
    $12 = (G4double &) @0x9ca6ef0: 1.2473033075214358e-318
    (gdb) p An
    $13 = 0.5630903317577286
    (gdb) 


::

     119 C4OpBoundaryProcess::C4OpBoundaryProcess(
     120                                                const C4IPMTAccessor* accessor,
     121                                                const G4String& processName,
     122                                                G4ProcessType type)
     123              :
     124              G4VDiscreteProcess(processName, type),
     125              m_custom_status('U'),
     126              m_custom_art(new C4CustomART(
     127                                         accessor,
     128                                         theAbsorption,
     129                                         theReflectivity,
     130                                         theTransmittance,
     131                                         theEfficiency,
     132                                         theGlobalPoint,
     133                                         OldMomentum,



::

    (gdb) b 527
    Breakpoint 5 at 0x7fffd0eabbf6: file /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc, line 527.
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $14 = 1.2473033075214358e-318
    (gdb) 

    (gdb) d 1 2 3 4
    (gdb) i b 
    Num     Type           Disp Enb Address            What
    5       breakpoint     keep y   0x00007fffd0eabbf6 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) 
                                                       at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
        breakpoint already hit 2 times
    (gdb) 


    (gdb) p theEfficiency
    $20 = 1.2346255830491494e-318
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $21 = 1.1810441637576662e-318
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $22 = 0
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $23 = 1.0943603461948195e-318
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $24 = 1.2265130251444361e-318
    (gdb) c
    Continuing.

    Breakpoint 5, C4OpBoundaryProcess::PostStepDoIt (this=0x9ca6c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/ExternalLibs/Build/customgeant4-0.1.4/C4OpBoundaryProcess.cc:527
    527	                    type = dielectric_dielectric ;
    (gdb) p theEfficiency
    $25 = 1.2329408191968308e-318
    (gdb) 



jcv DsPhysConsOptical::

    367 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
    368 #include "PMTSimParamSvc/PMTSimParamData.h"
    369 #include "PMTSimParamSvc/PMTAccessor.h"
    370 
    371 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    372 {
    373     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    374 
    375     if(psps_ptr.invalid())
    376     {
    377         std::cout << "invalid" << std::endl ;
    378         return nullptr ;
    379     }
    380 
    381     IPMTSimParamSvc* ipsps = psps_ptr.data();
    382     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    383 
    384     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    385     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    386     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    387 
    388     return boundproc ;
    389 }
      

jcv PMTAccessor::

    156 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    157 {
    158     return data->get_pmtid_qe(pmtid, energy) ;
    159 }


    epsilon:junosw blyth$ jcv PMTSimParamData
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    epsilon:junosw blyth$ 


    176 inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const
    177 {
    178     int idx = get_pmtContiguousIndex(pmtid) ;
    179     int cat = m_all_pmt_catvec[idx] ;
    180     double qe = get_pmtcat_qe(cat, energy);
    181     double qe_scale = m_all_pmtID_qe_scale[idx] ;
    182     qe *= qe_scale ;
    183     assert(qe > 0 && qe < 1);
    184     return qe ;
    185 }


* TODO: handle idx -1 


::

    (gdb) b PMTSimParamData::get_pmtid_qe
    Breakpoint 6 at 0x7fffd113cddc: file /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h, line 178.
    (gdb) c
    Continuing.

    Breakpoint 6, PMTSimParamData::get_pmtid_qe (this=0x9271f0, pmtid=12359, energy=2.7790065809028911e-06)
        at /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:178
    178	    int idx = get_pmtContiguousIndex(pmtid) ; 
    (gdb) p pmtid
    $26 = 12359
    (gdb) 

Getting idx -1, unexpectedly::

    229 inline int PMTSimParamData::get_pmtContiguousIndex(int pmtid) const
    230 {
    231     int idx = -1 ;
    232     if(PMT::IsCD(pmtid) and PMT::Is20inch(pmtid)) {
    233         idx = pmtid ;    // LPMT 
    234     } else if(PMT::IsWP(pmtid)) {
    235         idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    236     } else if (PMT::IsCD(pmtid) and PMT::Is3inch(pmtid)){
    237         idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    238     }
    239 
    240     return idx ;
    241 }


::

    epsilon:fakes blyth$ jcv PMT
    ./Detector/Geometry/Geometry/PMT.h


::

     01 #pragma once
      2 
      3 enum PMTID_OFFSET_DETSIM {
      4   kOFFSET_CD_LPMT=0,
      5   kOFFSET_WP_PMT=30000,
      6   kOFFSET_CD_SPMT=300000
      7 };
      8 
      9 struct PMT
     10 {
     11     static bool IsCD(int pmtid);
     12     static bool IsWP(int pmtid);
     13     static bool Is20inch(int pmtid);
     14     static bool Is3inch(int pmtid);
     15 };
     16 
     17 inline bool PMT::IsCD(int pmtid)
     18 {
     19     return (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_WP_PMT)  or (kOFFSET_CD_SPMT<=pmtid);
     20 }
     21 inline bool PMT::IsWP(int pmtid)
     22 {
     23     return (kOFFSET_WP_PMT<=pmtid and pmtid<kOFFSET_CD_SPMT);
     24 }
     25 inline bool PMT::Is20inch(int pmtid)
     26 {
     27     return (pmtid<kOFFSET_CD_SPMT);
     28 }
     29 inline bool PMT::Is3inch(int pmtid)
     30 {
     31     return (kOFFSET_CD_SPMT<=pmtid);
     32 }


::

     19 struct PMT
     20 {
     21     static bool IsCD(int pmtid);
     22     static bool IsWP(int pmtid);
     23     static bool Is20inch(int pmtid);
     24     static bool Is3inch(int pmtid);
     25 };
     26 
     27 inline bool PMT::IsCD(int pmtid)
     28 {
     29     return (kOFFSET_CD_LPMT<=pmtid and pmtid<kOFFSET_CD_LPMT_END)
     30         or (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_CD_SPMT_END);
     31 }
     32 inline bool PMT::IsWP(int pmtid)
     33 {
     34     return (kOFFSET_WP_PMT<=pmtid and pmtid<kOFFSET_WP_PMT_END);
     35 }
     36 inline bool PMT::Is20inch(int pmtid)
     37 {
     38     return (kOFFSET_CD_LPMT<=pmtid and pmtid<kOFFSET_CD_LPMT_END)
     39         or (kOFFSET_WP_PMT<=pmtid and pmtid<kOFFSET_WP_PMT_END);
     40 }
     41 inline bool PMT::Is3inch(int pmtid)
     42 {
     43     return (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_CD_SPMT_END);
     44 }



Looks like changes to get the merge to succeed are expecting to use 
the fixed main:Detector/Geometry/Geometry/PMT.h not the unfixed 
one in the branch.::

    (gdb) p qe
    $27 = 6.3169751280324259e-319
    (gdb) p pmtid
    $28 = 12359
    (gdb) p idx
    $29 = -1
    (gdb) p PMT::IsCD(pmtid)
    $30 = false
    (gdb) p PMT::Is20inch(pmtid)
    $31 = true
    (gdb) p PMT::IsWP(pmtid)
    $32 = false
    (gdb) p PMT::Is3inch(pmtid)
    $33 = false
    (gdb) b PMT::IsCD
    Breakpoint 8 at 0x7fffd113cb8b: PMT::IsCD. (2 locations)
    (gdb) 


Grab the fixed PMT.h from the main into the branch::

    N[blyth@localhost junosw]$ git show main:Detector/Geometry/Geometry/PMT.h > Detector/Geometry/Geometry/PMT.h

    ./build_Debug.sh 


::

    BP=PMTSimParamData::get_pmtid_qe ntds0



::

    176	inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const 
    177	{
    178	    int idx = get_pmtContiguousIndex(pmtid) ; 
    179	    int cat = m_all_pmt_catvec[idx] ; 
    180	    double qe = get_pmtcat_qe(cat, energy);
    181	    double qe_scale = m_all_pmtID_qe_scale[idx] ; 
    182	    qe *= qe_scale ;
    (gdb) b 182
    Breakpoint 2 at 0x7fffd113ce8c: file /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h, line 182.
    (gdb) c
    Continuing.

    Breakpoint 2, PMTSimParamData::get_pmtid_qe (this=0x9271f0, pmtid=5999, energy=2.9395728335807777e-06)
        at /data/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:182
    182	    qe *= qe_scale ;
    (gdb) p idx
    $1 = 5999
    (gdb) p cat
    $2 = 3
    (gdb) p qe
    $3 = 0.27113287242806083
    (gdb) p qe_scale
    $4 = 1.0966810966810965
    (gdb) 



::

    N[blyth@localhost junosw]$ ~/j/blyth-88-merge/ScanPE.sh
    root [0] 
    Processing /home/blyth/j/blyth-88-merge/ScanPE.C...
    ************************************************************************************************************
    *    Row   *  nPhotons *   totalPE *    LpmtPE *    SpmtPE *    NNVTPE *    HamaPE *      CDPE *      WPPE *
    ************************************************************************************************************
    *        0 *      1722 *      1722 *      1680 *        42 *      1234 *       446 *      1722 *         0 *
    ************************************************************************************************************
    root [1] 

