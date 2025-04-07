two_stage_production/non_optical_first_stage
===============================================



--optical --deferred-op
-------------------------

::

    P[blyth@localhost junosw]$ jcv JUNODetSimModule
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py

    0381         grp_pmt_op.add_argument("--optical", dest="useoptical", default=True, action=argparse.BooleanOptionalAction, help=mh("Enable Optical Progress"))
     382         grp_pmt_op.add_argument("--cerenkov-only", dest="cerenkov_only", action="store_true", help=mh("Only enable Cerenkov generation. Note: Reemission is also enabled."))
     383         grp_pmt_op.set_defaults(cerenkov_only=False)

    0411         # == OP simulator: deferred OP simulation ==
     412         grp_pmt_op.add_argument("--deferred-op", dest="deferred_op", default=False, action="store_true", help=mh("Enable deferred Optical simulation"))
     413         grp_pmt_op.add_argument("--deferred-op-testing-ratio", type=float, default=1.0,
     414                                 help=mh("The ratio will be used to invoke the OP simulator randomly"))
     415 
     416         # pre-select FC/PC events
     417         grp_pmt_op.add_argument("--preselect", default=None, choices=["None", "FC", "PC", "PCStop", "PCThrough", "LS"], help="Pre-select the FC/PC/PCStop/PCThrough events")


    2483         # disable the optical progress
    2484         op_process = sim_conf.optical_process()
    2485         op_process.property("OpticksMode").set(args.opticks_mode)  # see DsPhysConsOptical
    2486         op_process.property("UseCerenkov").set(args.cerenkov)
    2487         op_process.property("UseCerenkovType").set(args.cerenkov_type)
    2488         op_process.property("UseAbsorption").set(args.opabs)
    2489         op_process.property("UseRayleigh").set(args.opsct)
    2490         if not args.useoptical or args.voxel_fast_sim:
    2491             print("Disable Optical Process")
    2492             op_process.property("UseScintillation").set(False)
    2493             op_process.property("UseCerenkov").set(False)
    2494         if args.cerenkov_only:
    2495             print("Enable Cerenkov. (note: Scintillation is used to do reemission only)")
    2496             op_process.property("UseScintillation").set(True)
    2497             op_process.property("UseCerenkov").set(True)
    2498             op_process.property("ScintDoReemissionOnly").set(True)
    2499 
    2500         # For testing of OPSimulator only
    2501         if args.deferred_op or args.preselect != None:
    2502             op_process.property("UseScintillation").set(True)
    2503             # op_process.property("UseCerenkov").set(False)
    2504             op_process.property("UseCerenkov").set(True)
    2505             op_process.property("CerenPhotonStack").set(False)
    2506             op_process.property("ScintDoReemissionOnly").set(True)
    2507 


CerenPhotonStack
------------------


::

    P[blyth@localhost junosw]$ jgr CerenPhotonStack
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("CerenPhotonStack").set(False)
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:                phy_process.property("CerenPhotonStack").set(False)
    ./Simulation/DetSimV2/DetSimOptions/include/JUNOPhyParaTool.hh:    // Property: CerenPhotonStack
    ./Simulation/DetSimV2/DetSimOptions/src/JUNOPhyParaTool.cc:    declProp("CerenPhotonStack", m_cerenPhotonStack = true);
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h:    // Property: CerenPhotonStack
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("CerenPhotonStack", m_cerenPhotonStack = true);
    P[blyth@localhost junosw]$ 


ScintDoReemissionOnly
----------------------

::

    P[blyth@localhost junosw]$ jgr ScintDoReemissionOnly
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("ScintDoReemissionOnly").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("ScintDoReemissionOnly").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:                phy_process.property("ScintDoReemissionOnly").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:                phy_process.property("ScintDoReemissionOnly").set(True)
    ./Simulation/DetSimV2/DetSimOptions/include/JUNOPhyParaTool.hh:    /// ScintDoReemissionOnly: Do reemission in scintilator only
    ./Simulation/DetSimV2/DetSimOptions/src/JUNOPhyParaTool.cc:    declProp("ScintDoReemissionOnly", m_doReemissionOnly = false);
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h:    /// ScintDoReemissionOnly: Do reemission in scintilator only
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("ScintDoReemissionOnly", m_doReemissionOnly = false);


DsPhysConsOptical
------------------


::

     39 DsPhysConsOptical::DsPhysConsOptical(const G4String& name): G4VPhysicsConstructor(name)
     40                                                             , ToolBase(name)
     41 {   
     42     declProp("OpticksMode", m_opticksMode=0);
     43     declProp("CerenMaxPhotonsPerStep", m_cerenMaxPhotonPerStep = 300);
     44     declProp("CerenPhotonStack", m_cerenPhotonStack = true);
     45     
     46     declProp("ScintDoReemission", m_doReemission = true);
     47     declProp("ScintDoScintAndCeren", m_doScintAndCeren = true);
     48     declProp("ScintDoReemissionOnly", m_doReemissionOnly = false);
     49     
     50     declProp("UseCerenkov", m_useCerenkov=true);
     51     declProp("UseCerenkovType", m_useCerenkovType="modified");
     52     declProp("ApplyWaterQe", m_applyWaterQe=true);



::

    192     if (m_useScintillation && 1) { // DsG4 (with re-emission)
    193         DsG4Scintillation* scint = new DsG4Scintillation(m_opticksMode);
    194 
    195         scint->SetDoQuenching(m_enableQuenching);
    196         scint->SetBirksConstant1(m_birksConstant1);
    197         scint->SetBirksConstant2(m_birksConstant2);
    198         scint->SetDoReemission(m_doReemission);
    199         scint->SetDoReemissionOnly(m_doReemissionOnly);
    200         scint->SetDoBothProcess(m_doScintAndCeren);
    201         scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
    202         scint->SetPreQE(1./m_scintPhotonScaleWeight);
    203         scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
    204         scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
    205         scint->SetTrackSecondariesFirst(true);
    206         scint->SetFlagDecayTimeFast(flagDecayTimeFast);
    207         scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
    208         scint->SetVerboseLevel(EGet::Get<int>("DsG4Scintillation_verboseLevel",0));



::

    163     if (m_useCerenkov)
    164     {
    165         if (m_useCerenkovType == "modified") {
    166             G4Cerenkov_modified* cerenkov = new G4Cerenkov_modified() ;
    167             cerenkov->SetMaxNumPhotonsPerStep(m_cerenMaxPhotonPerStep);
    168             cerenkov->SetStackPhotons(m_cerenPhotonStack);
    169             cerenkov->SetTrackSecondariesFirst(m_doTrackSecondariesFirst);
    170             cerenkov->SetOpticksMode(m_opticksMode);
    171             cerenkov->SetVerboseLevel(EGet::Get<int>("G4Cerenkov_modified_verboseLevel",0));
    172             cerenkov_ = cerenkov ;
    173         } else if (m_useCerenkovType == "original") {
    174             G4Cerenkov* cerenkov = new G4Cerenkov() ;
    175             cerenkov->SetMaxNumPhotonsPerStep(m_cerenMaxPhotonPerStep);
    176             cerenkov->SetStackPhotons(m_cerenPhotonStack);
    177             cerenkov->SetTrackSecondariesFirst(m_doTrackSecondariesFirst);
    178             cerenkov->SetVerboseLevel(EGet::Get<int>("G4Cerenkov_verboseLevel",0));
    179             cerenkov_ = cerenkov ;
    180         } else {
    181             G4cerr << __FILE__ << ":" << __LINE__
    182                    << " Unknown m_useCerenkovType: '"
    183                    << m_useCerenkovType << "'"
    184                    << G4endl;
    185             assert(0);
    186         }
    187 



    268 inline
    269 void G4Cerenkov_modified::SetStackPhotons(const G4bool stackingFlag)
    270 {
    271         fStackingFlag = stackingFlag;
    272 }


    0331   // if stacking is false, then stop the generation of Cerenkov photons
     332   if (!fStackingFlag) {
     333      aParticleChange.SetNumberOfSecondaries(0);
     334 
     335      return pParticleChange;
     336   }
     337 
     338 
     339 
     340 #ifdef WITH_G4CXOPTICKS
     341 #ifdef WITH_G4CXOPTICKS_DEBUG
     342   dbg.BetaInverse = BetaInverse ;
     343   dbg.step_length = step_length ;
     344   dbg.MeanNumberOfPhotons = MeanNumberOfPhotons ;
     345   dbg.fNumPhotons = fNumPhotons ;
     346   dbg.add();
     347 #endif
     348   /**
     349   opticksMode:1 
     350       skip the below generation loop by setting uNumPhotons to zero, 
     351       as are doing generation and propagation on GPU 
     352   opticksMode:3 
     353       proceed with the below generation loop despite also 
     354       doing that on GPU 
     355 
     356   **/
     357 
     358   bool is_opticks_genstep = fNumPhotons > 0 ;
     359   G4VUserTrackInformation* a_ui = aTrack.GetUserInformation() ;
     360   assert( a_ui == nullptr );  // should always be null, as process C is not applicable to RE-photons
     361 
     362   if(is_opticks_genstep && (m_opticksMode ==  1 || m_opticksMode == 3 ))
     363   {
     364       U4::CollectGenstep_G4Cerenkov_modified(
     365           &aTrack,
     366           &aStep,
     367           fNumPhotons,
     368           BetaInverse,
     369           Pmin,
     370           Pmax,
     371           maxCos,
     372           maxSin2,
     373           MeanNumberOfPhotons1,
     374           MeanNumberOfPhotons2
     375       );




    223         void SetDoReemissionOnly(bool tf = true) { doReemissionOnly = tf; }
    224         bool GetDoReemissionOnly() { return doReemissionOnly; }



    360 inline
    361 G4bool DsG4Scintillation::IsApplicable(const G4ParticleDefinition& aParticleType)
    362 {
    363         if (aParticleType.GetParticleName() == "opticalphoton"){
    364            return true;
    365         } else if (doReemissionOnly) {
    366            // if only do reemission, don't allow other particles to call it.
    367            return false;
    368         } else {
    369            return true;
    370         }
    371 }



