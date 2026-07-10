review "new" optical (LS) model
================================



Overview
--------

The "three species LS model" is not yet merged into JUNOSW,
but nevertheless need to prepare Opticks - such that the delay
between merging and making the new model default and Opticks
supporting it is not too long.



Questions
----------

1. how to modify qsim.h to flexibly support triplicate model
2. how to retain the LS species state, sysrap/sphoton.h set_species/get_species
3. how to create the layered texture


 

Opticks Preparations for "Three Species LS Model"
---------------------------------------------------

Added::

     qudarap/QTexLayered.h
     qudarap/QScintThree.h
     qudarap/tests/QScintThree_test.sh


Refs
-----

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1292



Old Look at initial iteration
------------------------------


::

    A[blyth@localhost junosw]$ jgr DsG4OpAbsReemit

    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:#ifndef DsG4OpAbsReemit_h
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:#define DsG4OpAbsReemit_h
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h: * For LS, there are LAB, PPO and bis-MSB. Create DsG4OpAbsReemit for each
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:class DsG4OpAbsReemit: public G4VDiscreteProcess
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:    DsG4OpAbsReemit(const G4String& label = "PPO",
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:    ~DsG4OpAbsReemit();
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:G4bool DsG4OpAbsReemit::IsApplicable(const G4ParticleDefinition& aParticleType)
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:G4PhysicsTable* DsG4OpAbsReemit::GetIntegralTable() const
    ./Simulation/DetSimV2/PhysiSim/include/DsG4OpAbsReemit.h:void DsG4OpAbsReemit::DumpPhysicsTable() const

    ./Simulation/DetSimV2/PhysiSim/include/DsG4ScintSimple.h:// It rigorously excludes optical photon re-emission (delegated to DsG4OpAbsReemit).

    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:#include "DsG4OpAbsReemit.h"
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:DsG4OpAbsReemit::DsG4OpAbsReemit(const G4String& label, const G4String& processName, G4ProcessType type)
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:DsG4OpAbsReemit::~DsG4OpAbsReemit()
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:DsG4OpAbsReemit::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:G4double DsG4OpAbsReemit::GetMeanFreePath(const G4Track& aTrack,
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:void DsG4OpAbsReemit::BuildThePhysicsTable()

    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#include "DsG4OpAbsReemit.h"
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    DsG4OpAbsReemit* absreemit_PPO = 0;
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    DsG4OpAbsReemit* absreemit_bisMSB = 0;
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:        absreemit_PPO = new DsG4OpAbsReemit("PPO");
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:        absreemit_bisMSB = new DsG4OpAbsReemit("bisMSB");
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    // We use a custom "Bulk" DsG4OpAbsReemit to intercept all absorption events.
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:            DsG4OpAbsReemit* bulk_absorb = new DsG4OpAbsReemit("Bulk", "OpAbsorption");
    ./Simulation/DetSimV2/PhysiSim/CMakeLists.txt:        src/DsG4OpAbsReemit.cc 

    A[blyth@localhost junosw]$ 





Q: What combinations of UseScintillation UseScintSimple UseAbsorption UseAbsReemit make sense ?
   The code needs to enforce that only the intended sensible combinations of these options are used.




::

    jcv DsPhysConsOptical


    054     declProp("UseScintillation", m_useScintillation=true);
     55     declProp("UseScintSimple", m_useScintSimple=false);
     56     declProp("UseRayleigh", m_useRayleigh=true);
     57     declProp("UseAbsorption", m_useAbsorption=true);
     58     declProp("UseAbsReemit", m_useAbsReemit=false);
     59     declProp("UseFastMu300nsTrick", m_useFastMu300nsTrick=false);
     60     declProp("ScintillationYieldFactor", m_ScintillationYieldFactor = 1.0);



    249     DsG4OpAbsReemit* absreemit_PPO = 0;
    250     DsG4OpAbsReemit* absreemit_bisMSB = 0;
    251     if (m_useAbsReemit){
    252         absreemit_PPO = new DsG4OpAbsReemit("PPO");
    253         absreemit_bisMSB = new DsG4OpAbsReemit("bisMSB");
    254         absreemit_PPO->SetVerboseLevel(0);
    255         absreemit_bisMSB->SetVerboseLevel(0);
    256     }
    257 
    258     // === Hijack the Standard Absorption ===
    259     // We use a custom "Bulk" DsG4OpAbsReemit to intercept all absorption events.
    260     G4VProcess* absorb = 0;
    261     if (m_useAbsorption) {
    262         if (m_useAbsReemit) { 
    263             // New Optical Model
    264             DsG4OpAbsReemit* bulk_absorb = new DsG4OpAbsReemit("Bulk", "OpAbsorption");
    265             bulk_absorb->SetLABNRParams(m_lab2ppo_prob, m_lab2bis_prob, m_lab2ppo_tau, m_lab2bis_tau);
    266             absorb = bulk_absorb;
    267         } else {
    268             // Old Optical Model
    269             absorb = new G4OpAbsorption();
    270         }
    271     }
    272 






jcv DsG4OpAbsReemit
----------------------


::

     39     DsG4OpAbsReemit(const G4String& label = "PPO",
     40                         const G4String& processName = "OpAbsReemit",
     41                         G4ProcessType type = fOptical
     42                         );


      7 DsG4OpAbsReemit::DsG4OpAbsReemit(const G4String& label, const G4String& processName, G4ProcessType type)
      8   : G4VDiscreteProcess(processName + (label=="Bulk" ? "" : ("_" + label)), type)



+-------------------+---------------------+
| symbol            |   process name      |
+===================+=====================+
| bulk_absorb       |  OpAbsorption       |
+-------------------+---------------------+
| absreemit_PPO     |  OpAbsReemit_PPO    |
+-------------------+---------------------+
| absreemit_bisMSB  |  OpAbsReemit_bisMSB |
+-------------------+---------------------+
 


* Bulk process 


::


    247 void DsG4OpAbsReemit::BuildThePhysicsTable()
    248 {
    249     // Avoid double initialization
    250     if (theIntegralTable || theBulkPPOIntegralTable || theBulkBisIntegralTable) return;
    251 
    252     const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();
    253     G4int numOfMaterials = G4Material::GetNumberOfMaterials();
    254 
    255     // Allocate physics tables depending on process mode
    256     if (m_label == "Bulk") {
    257         theBulkPPOIntegralTable = new G4PhysicsTable(numOfMaterials);
    258         theBulkBisIntegralTable = new G4PhysicsTable(numOfMaterials);
    259     } else {
    260         theIntegralTable = new G4PhysicsTable(numOfMaterials);
    261     }







Three component model
-----------------------

::

     7 DsG4OpAbsReemit::DsG4OpAbsReemit(const G4String& label, const G4String& processName, G4ProcessType type)
      8   : G4VDiscreteProcess(processName + (label=="Bulk" ? "" : ("_" + label)), type)
      9 {
     10   SetProcessSubType(fOpWLS);
     11     
     12   theIntegralTable = nullptr;
     13   theBulkPPOIntegralTable = nullptr;
     14   theBulkBisIntegralTable = nullptr;
     15     
     16   G4cout << GetProcessName() << " by " << label << " is created " << G4endl;
     17     
     18   m_label = label;
     19   m_label_abslen = (label=="Bulk" ? "ABSLENGTH" : label+"ABSLENGTH");
     20   m_label_reemiprob = label+"REEMISSIONPROB";
     21   m_label_component = label+"COMPONENT";   // maybe fast/slow
     22   m_label_timeconst = label+"TIMECONSTANT";// maybe fast/slow
     23 
     24   BuildThePhysicsTable();
     25 }   



Labels of basis properties of DsG4OpAbsReemit::

     m_label_abslen     BulkABSLENGTH         PPOABSLENGTH          bisMSBABSLENGTH
     m_label_reemiprob  BulkREEMISSIONPROB    PPOREEMISSIONPROB     bisMSBREEMISSIONPROB
     m_label_component  BulkCOMPONENT         PPOCOMPONENT          bisMSBCOMPONENT
     m_label_timeconst  BulkTIMECONSTANT      PPOTIMECONSTANT       bisMSBTIMECONSTANT


* HUH: am missing the "Bulk" props ?



::

    068     // === Inject LAB Non-Radiative (NR) parameters ===
     69     void SetLABNRParams(double p_ppo, double p_bis, double tau_ppo, double tau_bis) {
     70         m_lab2ppo_prob = p_ppo;
     71         m_lab2bis_prob = p_bis;
     72         m_lab2ppo_tau = tau_ppo;
     73         m_lab2bis_tau = tau_bis;
     74     }
     75 
     76 private:
     77 
     78     void BuildThePhysicsTable();
     79     // Is the integral table;
     80 
     81 protected:
     82 
     83     // -------------------------------------------------------------
     84     // Physical tables caching the Cumulative Distribution Functions
     85     // -------------------------------------------------------------
     86     G4PhysicsTable* theIntegralTable;        // For standard labeled processes (e.g., PPO only)
     87     G4PhysicsTable* theBulkPPOIntegralTable; // Cached CDF for Bulk mode LAB -> PPO
     88     G4PhysicsTable* theBulkBisIntegralTable; // Cached CDF for Bulk mode LAB -> bis-MSB
     89 
     90     G4String m_label; // indicate PPO, bisMSB, LAB
     91     // some labels
     92     G4String m_label_abslen;
     93     G4String m_label_reemiprob;
     94     G4String m_label_component;
     95     G4String m_label_timeconst;
     96 
     97     // NR Parameters
     98     double m_lab2ppo_prob;
     99     double m_lab2bis_prob;
    100     double m_lab2ppo_tau;
    101     double m_lab2bis_tau;
    102 };








UseAbsReemit
-------------

::

    A[blyth@localhost junosw]$ jgr UseAbsReemit
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:                phy_process.property("UseAbsReemit").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimModule.py:                phy_process.property("UseAbsReemit").set(False)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("UseAbsReemit").set(True)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("UseAbsReemit").set(False)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:       # op_process.property("UseAbsReemit").set(args.absreemit)
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    phy_process.property("UseAbsReemit").set(False)
    ./Simulation/DetSimV2/DetSimOptions/src/JUNOPhyParaTool.cc:    declProp("UseAbsReemit", m_useAbsReemit=false);
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("UseAbsReemit", m_useAbsReemit=false);
    A[blyth@localhost junosw]$ 



    0426         # add new optical model
     427 
     428         grp_pmt_op.add_argument("--new-optical-model", dest="new_optical_model", action="store_true",
     429                       help=mh("Use the new optical model."))
     430         grp_pmt_op.add_argument("--old-optical-model", dest="new_optical_model", action="store_false",
     431                       help=mh("Use the old optical model"))
     432         grp_pmt_op.set_defaults(new_optical_model=False)
     433 



    2833         op_process.property("UseQuenching").set(args.quenching)
    2834         # new optical model
    2835         if args.new_optical_model:
    2836             op_process.property("UseAbsReemit").set(True)
    2837             op_process.property("UseScintSimple").set(True)
    2838         else:
    2839             op_process.property("UseAbsReemit").set(False)
    2840             op_process.property("UseScintSimple").set(False)
    2841         # pmt optical model
    2842         op_process.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    2843         op_process.property("UsePMTNaturalGeometry").set(args.pmt_natural_geometry)
    2844        # op_process.property("UseAbsReemit").set(args.absreemit)




opticks qudarap reem
----------------------

::

    (ok) A[blyth@localhost qudarap]$ grep reem *.*
    qbnd.h:    s.material1 = boundary_lookup( wavelength, m1_line, 0);   // refractive_index, absorption_length, scattering_length, reemission_prob
    qbnd.h:    s.material2 = boundary_lookup( wavelength, m2_line, 0);   // refractive_index, (absorption_length, scattering_length, reemission_prob) only m2:refractive index actually used
    qscint.h:    QSCINT_METHOD void    reemit(   sphoton& p, RNG& rng, float scintillationTime) const ;
    qscint.h:    // sets direction, polarization and wavelength as needed by both generate and reemit
    qscint.h:qscint::reemit_photon
    qscint.h:As reemission happens inside scintillators for photons arising from Cerenkov (or Torch)
    qscint.h:gensteps need to special case the handing of the reemission scintillationTime somehow
    qscint.h:inline QSCINT_METHOD void qscint::reemit(sphoton& p, RNG& rng, float scintillationTime) const
    qsim.h:|   BULK_REEMIT       |   CONTINUE       |  time, position, direction, polarization, wavelength    | advance to reemit position with everything changed    |
    qsim.h:    const float& reemission_prob = s.material1.w ;
    qsim.h:            float u_reemit = reemission_prob == 0.f ? 2.f : curand_uniform(&rng);  // avoid consumption at absorption when not scintillator
    qsim.h:            if( u_reemit != 2.f ) tagr.add( stag_to_ree, u_reemit) ;
    qsim.h:            if (u_reemit < reemission_prob)
    QState.hh:    float m1_reemission_prob = 0.f ; 
    QState.hh:    float m2_reemission_prob = 0.f ; 
    QState.hh:    s.material1 = make_float4( m1_refractive_index, m1_absorption_length, m1_scattering_length, m1_reemission_prob ); 
    QState.hh:    s.material2 = make_float4( m2_refractive_index, m2_absorption_length, m2_scattering_length, m2_reemission_prob );  
    QTex.cc:   eg reemission generation need normalized
    (ok) A[blyth@localhost qudarap]$ 



Only one reem prob::

     717 
     718 inline QSIM_METHOD int qsim::propagate_to_boundary(unsigned& flag, RNG& rng, sctx& ctx)
     719 {
     720     sphoton& p = ctx.p ;
     721     const sstate& s = ctx.s ;
     722 
     723     const float& absorption_length = s.material1.y ;
     724     const float& scattering_length = s.material1.z ;
     725     const float& reemission_prob = s.material1.w ;
     726     const float& group_velocity = s.m1group2.x ;
     727     const float& distance_to_boundary = ctx.prd->q0.f.w ;
     728 
     729 
     730 #if !defined(PRODUCTION) && defined(DEBUG_TAG)
     731     float u_to_sci = curand_uniform(&rng) ;  // purely for alignment with G4
     732     float u_to_bnd = curand_uniform(&rng) ;  // purely for alignment with G4
     733 #endif
     734     float u_scattering = curand_uniform(&rng) ;
     735     float u_absorption = curand_uniform(&rng) ;
     736 
     737 #if !defined(PRODUCTION) && defined(DEBUG_TAG)
     738     stagr& tagr = ctx.tagr ;
     739     tagr.add( stag_to_sci, u_to_sci);
     740     tagr.add( stag_to_bnd, u_to_bnd);
     741     tagr.add( stag_to_sca, u_scattering);
     742     tagr.add( stag_to_abs, u_absorption);
     743 #endif
     744 






where opticks populates the reemission texture : QScint, QSim
--------------------------------------------------------------

* HMM: maybe NP->NPFold here to handle sometimes triplication

::

     171     const NP* icdf = ssim->get_icdf();
     172     if( icdf == nullptr )
     173     {
     174         LOG(error) << " icdf null, snam::ICDF " << snam::ICDF ;
     175     }
     176     else
     177     {
     178         unsigned hd_factor = 20u ;  // 0,10,20
     179         QScint* scint = new QScint( icdf, hd_factor); // custom high-definition inverse CDF for scintillation generation
     180         LOG(LEVEL) << scint->desc();
     181     }
     182 


::

     302 const NP* SSim::get_bnd() const {      return get(snam::BND);  }
     303 const NP* SSim::get_optical() const {  return get(snam::OPTICAL);  }
     304 const NP* SSim::get_propcom() const {  return get(snam::PROPCOM);  }
     305 const NP* SSim::get_icdf() const {     return get(snam::ICDF);  }


::

     07 struct snam
      8 {    
      9     static constexpr const char* WAVELENGTH = "wavelength.npy" ;
     10     static constexpr const char* ENERGY = "energy.npy" ;
     11     static constexpr const char* RAYLEIGH = "rayleigh.npy" ;
     12     static constexpr const char* MAT = "mat.npy" ;
     13     static constexpr const char* SUR = "sur.npy" ;
     14     static constexpr const char* BD = "bd.npy" ;
     15     static constexpr const char* BND = "bnd.npy" ;
     16     static constexpr const char* OPTICAL = "optical.npy" ;
     17     static constexpr const char* ICDF = "icdf.npy" ;
     18 
     19     static constexpr const char* MULTIFILM = "multifilm.npy" ;
     20     static constexpr const char* PROPCOM = "propcom.npy" ;
     21 
     22     static const char* get(const std::vector<std::string>& names, int idx ) ;
     23     static std::string Desc(const std::vector<std::string>& names);




Where is SSim icdf populated ? U4Scint
---------------------------------------


::

     36 struct U4Scint
     37 {
     38     static constexpr const bool VERBOSE = false ;
     39     static constexpr const char* PROPS = "SLOWCOMPONENT,FASTCOMPONENT,REEMISSIONPROB" ;
     40     static U4Scint* Create(const NPFold* materials );
     41 
     42     const NPFold* scint ;
     43     const char* name ;
     44 
     45     const NP* fast ;
     46     const NP* slow ;
     47     const NP* reem ;
     48 
     49     const double epsilon ;
     50     int mismatch_0 ;
     51     int mismatch_1 ;
     52     int mismatch ;
     53 
     54     const G4MaterialPropertyVector* theFastLightVector ;
     55     const G4MaterialPropertyVector* theSlowLightVector ;
     56     const G4MaterialPropertyVector* ScintillationIntegral ;
     57 
     58     const NP* icdf ;
     59 
     60     const int num_wlsamp ;
     61     const NP* wlsamp ;
     62 
     63 
     64     U4Scint(const NPFold* fold, const char* name);
     65     void init();
     66 



::

    111 inline U4Scint::U4Scint(const NPFold* scint_, const char* name_)
    112     :
    113     scint(scint_),
    114     name(strdup(name_)),
    115     fast(scint->get("FASTCOMPONENT")),
    116     slow(scint->get("SLOWCOMPONENT")),
    117     reem(scint->get("REEMISSIONPROB")),
    118     epsilon(0.),
    119     mismatch_0(NP::DumpCompare<double>(fast, slow, 0, 0, epsilon)),
    120     mismatch_1(NP::DumpCompare<double>(fast, slow, 1, 1, epsilon)),
    121     mismatch(mismatch_0+mismatch_1),
    122     theFastLightVector(U4MaterialPropertyVector::FromArray(fast)),
    123     theSlowLightVector(U4MaterialPropertyVector::FromArray(slow)),
    124     ScintillationIntegral(Integral(theFastLightVector)),
    125     icdf(nullptr),
    126     num_wlsamp(ssys::getenvint("U4Scint__num_wlsamp", 0)),
    127     wlsamp(nullptr)
    128 {
    129     init();
    130 }
    131 
    132 inline void U4Scint::init()
    133 {
    134     if(mismatch > 0 ) std::cerr
    135         << " mismatch_0 " << mismatch_0
    136         << " mismatch_1 " << mismatch_1
    137         << " mismatch " << mismatch
    138         << std::endl
    139         ;
    140     assert( mismatch == 0 );
    141 
    142     int num_bins = 4096 ;
    143     int hd_factor = 20 ;
    144     icdf = createGeant4InterpolatedInverseCDF(num_bins, hd_factor, name) ;
    145     wlsamp = createWavelengthSamples(num_wlsamp) ;
    146 }
    147 






::


     342 inline void U4Tree::initMaterials()
     343 {
     344     LOG_IF(info, material_debug > 0 ) << "[" ;
     345 
     346     initMaterials_r(top);
     347     st->material = U4Material::MakePropertyFold(materials);
     348 
     349     std::map<std::string, G4PhysicsVector*> prop_override ;
     350 
     351     G4PhysicsVector* Water_RAYLEIGH = rayleigh_table->find("Water") ;
     352     if(Water_RAYLEIGH) prop_override["Water/RAYLEIGH"] = Water_RAYLEIGH ;
     353 
     354     st->standard->mat = U4Material::MakeStandardArray(materials, prop_override) ;
     355 
     356     LOG_IF(info, material_debug > 0 ) << "]" ;
     357 }




     372 /**
     373 U4Tree::initScint
     374 ------------------
     375 
     376 **/
     377 
     378 inline void U4Tree::initScint()
     379 {
     380     scint = U4Scint::Create(st->material) ;
     381     if(scint)
     382     {
     383         st->standard->icdf = scint->icdf ;
     384     }
     385 }
     386 





    036 struct U4Scint
     37 {
     38     static constexpr const bool VERBOSE = false ;
     39     static constexpr const char* PROPS = "SLOWCOMPONENT,FASTCOMPONENT,REEMISSIONPROB" ;
     40     static U4Scint* Create(const NPFold* materials );
     41 

    093 inline U4Scint* U4Scint::Create(const NPFold* materials ) // static 
     94 {
     95     std::vector<const NPFold*> subs ;
     96     std::vector<std::string> names ;
     97     materials->find_subfold_with_all_keys( subs, names, PROPS );
     98 
     99     int num_subs = subs.size();
    100     int num_names = names.size() ;
    101     assert( num_subs == num_names );
    102 
    103     const char* name = num_names > 0 ? names[0].c_str() : nullptr ;
    104     const NPFold* sub = num_subs > 0 ? subs[0] : nullptr ;
    105     bool with_scint = name && sub ;
    106 
    107     return with_scint ? new U4Scint(sub, name) : nullptr ;
    108 }    



Hmm will need U4ScintThree.h


::

    (ok) A[blyth@localhost material]$ find LS -type f
    LS/RINDEX.npy
    LS/GROUPVEL.npy
    LS/RAYLEIGH.npy

    LS/ABSLENGTH.npy
    LS/REEMISSIONPROB.npy
    LS/FASTCOMPONENT.npy
    LS/SLOWCOMPONENT.npy

    LS/PPOABSLENGTH.npy
    LS/PPOREEMISSIONPROB.npy
    LS/PPOCOMPONENT.npy
    LS/PPOTIMECONSTANT.npy

    LS/bisMSBABSLENGTH.npy
    LS/bisMSBREEMISSIONPROB.npy
    LS/bisMSBCOMPONENT.npy
    LS/bisMSBTIMECONSTANT.npy



    LS/OpticalCONSTANT.npy
    LS/GammaCONSTANT.npy
    LS/AlphaCONSTANT.npy
    LS/NeutronCONSTANT.npy

    LS/NPFold_index.txt
    LS/NPFold_names.txt



Three component scint, how to do that ? Will need scint tex in triplicate
--------------------------------------------------------------------------

* hmm need to add accessors to the integral tables

* target_<props> strings for this track start at native ones of the process

  * HMM: that default starting point is GPU problematic, as it means every photon
    within the scintillator will need a 0,1,2 label (2bits) indicating 
    which component of the scint is being interacted with and hence
    which of the three tex is native

* target_<props> for m_label:Bulk may randomly switch to PPO or bisMSB

  * this is like the material seen by the photon randomly changing into another material
  * but do not? hold onto that state as it immediately impacts the reemission probability used directly





::

    066     // =================================================================
     67     // New LS Optical Model PLUS 16038-v1: Non-Radiative Transfer Logic
     68     // =================================================================
     69     G4String target_component = m_label_component;
     70     G4String target_timeconst = m_label_timeconst;
     71     G4String target_reemiprob = m_label_reemiprob;
     72     G4double tau_nr = 0.0;
     73     std::string micro_proc_name = "OpAbsReemit_" + m_label;
     74 
     75     if (m_label == "Bulk") {
     76         if (!aMaterialPropertiesTable->GetProperty("PPOCOMPONENT")) {
     77             return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
     78         }
     79 
     80         G4double rand_fate = G4UniformRand();
     81         if (rand_fate < m_lab2ppo_prob) {
     82             target_component = "PPOCOMPONENT";
     83             target_timeconst = "PPOTIMECONSTANT";
     84             target_reemiprob = "PPOREEMISSIONPROB";
     85             tau_nr = m_lab2ppo_tau;
     86             micro_proc_name = "OpAbsReemit_LAB_NR_PPO";
     87         } else if (rand_fate < m_lab2ppo_prob + m_lab2bis_prob) {
     88             target_component = "bisMSBCOMPONENT";
     89             target_timeconst = "bisMSBTIMECONSTANT";
     90             target_reemiprob = "bisMSBREEMISSIONPROB";
     91             tau_nr = m_lab2bis_tau;
     92             micro_proc_name = "OpAbsReemit_LAB_NR_bisMSB";
     93         } else {
     94             return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep); // NR failed (heat)
     95         }
     96     }
     97     // =================================================================
     98 
     99     // Evaluate quantum efficiency (Re-emission probability)
    100     const G4MaterialPropertyVector* reemit_prob_vec =
    101         aMaterialPropertiesTable->GetProperty(target_reemiprob.c_str());
    102     if (!reemit_prob_vec) {
    103         return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    104     }
    105     G4double p_reemission = reemit_prob_vec->Value(aTrack.GetKineticEnergy());
    106     if (G4UniformRand() >= p_reemission) {
    107         return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep); // Photon lost
    108     }
    109 
    110     if (verboseLevel>0) {
    111         G4cout << "*** will be re-emitted by: " << m_label << " **" << G4endl;
    112     }
    113 
    114     G4int NumPhotons = 1;



where to find 2 bits for "scint species" ? sphoton.h boundary does not need 15b
---------------------------------------------------------------------------------

Choice between boundary, flag and flagmask.  Boundary has least complications.::

      02 /**
       3 sphoton.h
       4 ============
       5 
       6 +----+-------------------------+------------------+-----------------+---------------------+------------------------------+
       7 | q  |               x         |        y         |      z          |           w         |  notes                       |
       8 +====+=========================+==================+=================+=====================+==============================+
       9 |    |           pos.x         |    pos.y         |   pos.z         |       time          |                              |
      10 | q0 |                         |                  |                 |                     |                              |
      11 |    |                         |                  |                 |                     |                              |
      12 +----+-------------------------+------------------+-----------------+---------------------+------------------------------+
      13 |    |           mom.x         |    mom.y         |  mom.z          |   u:hitcount_iindex |                              |
      14 | q1 |                         |                  |                 |      16b       16b  |                              |
      15 |    |                         |                  |                 | (1,3)               |                              |
      16 +----+-------------------------+------------------+-----------------+---------------------+------------------------------+
      17 |    |           pol.x         |    pol.y         |   pol.z         |       wavelength    |                              |
      18 | q2 |                         |                  |                 |                     |                              |
      19 |    |                         |                  |                 |                     |                              |
      20 +----+-------------------------+------------------+-----------------+---------------------+------------------------------+
      21 |    | u:orient_boundary_flag  |  u:identity      | u:index         |     u:flagmask      |                              |
      22 | q3 |    1b     15b      16b  |    8b 24b        |                 |                     |                              |
      23 |    |                         |  8b:extend index |                 |                     |                              |
      24 |    | (3,0)                   | (3,1)            | (3,2)           | (3,3)               |                              |
      25 +----+-------------------------+------------------+-----------------+---------------------+------------------------------+
      26 


Current 450 bnd, so no problem to reduce from 15 to 13 bits::

    In [1]: 0x1 << 15
    Out[1]: 32768

    In [2]: 0x1 << 13
    Out[2]: 8192



::

    CMDLINE:/data1/blyth/local/opticks_Debug/bin/f.py
    f.base:.

      : f.wavelength                                       :               (761,) : 5 days, 5:33:17.905113 
      : f.energy                                           :               (761,) : 5 days, 5:33:17.905113 
      : f.rayleigh                                         :          (47, 37, 2) : 5 days, 5:33:17.905113 
      : f.rayleigh_meta                                    :                    1 : 5 days, 5:33:17.905113 
      : f.rayleigh_names                                   :                (47,) : 5 days, 5:33:17.905113 
      : f.mat                                              :      (24, 2, 761, 4) : 5 days, 5:33:17.905113 
      : f.mat_meta                                         :                    1 : 5 days, 5:33:17.905113 
      : f.mat_names                                        :                (24,) : 5 days, 5:33:17.905113 
      : f.sur                                              :     (361, 2, 761, 4) : 5 days, 5:33:17.905113 
      : f.sur_names                                        :               (361,) : 5 days, 5:33:17.899113 
      : f.bd                                               :             (450, 4) : 5 days, 5:33:17.899113 
      : f.bd_names                                         :               (450,) : 5 days, 5:33:17.899113 
      : f.bnd                                              :  (450, 4, 2, 761, 4) : 5 days, 5:33:17.899113 
      : f.bnd_meta                                         :                    4 : 5 days, 5:33:17.874113 
      : f.bnd_names                                        :               (450,) : 5 days, 5:33:17.874113 
      : f.optical                                          :          (450, 4, 4) : 5 days, 5:33:17.874113 
      : f.icdf                                             :         (3, 4096, 1) : 5 days, 5:33:17.874113 
      : f.icdf_meta                                        :                    5 : 5 days, 5:33:17.874113 
      : f.icdf_names                                       :                 (1,) : 5 days, 5:33:17.874113 
      : f.NPFold_index                                     :                 (9,) : 5 days, 5:33:17.874113 
      : f.NPFold_names                                     :                 (0,) : 5 days, 5:33:17.874113 

     min_stamp : 2026-04-08 09:51:41.676382 
     max_stamp : 2026-04-08 09:51:41.707382 
     dif_stamp : 0:00:00.031000 
     age_stamp : 5 days, 5:33:17.874113 

    In [1]: f.bnd_names
    Out[1]: 
    array(['Galactic///Galactic', 'Galactic///Rock', 'Rock///Galactic', 'Rock//Implicit_RINDEX_NoRINDEX_pDomeAir_pDomeRock/Air', 'Rock///Rock', 'Rock//Implicit_RINDEX_NoRINDEX_pExpHall_pExpRockBox/Air',
           'Air/Implicit_RINDEX_NoRINDEX_pExpHall_pPoolCover//Steel', 'Air///Air', 'Air/Implicit_RINDEX_NoRINDEX_lUpperChimney_phys_pUpperChimneySteel//Steel', 'Steel//UpperChimneySteelSurface/LS',
           'Air/Steel_surface//Steel', 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_1ff__pPanel_0_f_//Aluminium', 'Aluminium///Adhesive', 'Adhesive///TiO2Coating', 'TiO2Coating///Scintillator',
           'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_1ff__pPanel_1_f_//Aluminium', 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_1ff__pPanel_2_f_//Aluminium',
           'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_1ff__pPanel_3_f_//Aluminium', 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_1ff__pPanel_0_f_//Aluminium',
           'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_1ff__pPanel_1_f_//Aluminium', 'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_1ff__pPanel_2_f_//Aluminium',
           'Air/Implicit_RINDEX_NoRINDEX_pPlane_1_1ff__pPanel_3_f_//Aluminium', 'Air/Implicit_RINDEX_NoRINDEX_pPlane_0_ff__pPanel_0_f_//Aluminium',




Geant4 picks between the three processes based on DsG4OpAbsReemit::GetMeanFreePath m_label_abslen
---------------------------------------------------------------------------------------------------

* how to find an equivalent way to probalistically assign photon in scintillator to a "scint species"


* this is doing an energy dependent lookup

::

    220 G4double DsG4OpAbsReemit::GetMeanFreePath(const G4Track& aTrack,
    221         G4double ,
    222         G4ForceCondition* )
    223 {
    224     const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();
    225     const G4Material* aMaterial = aTrack.GetMaterial();
    226 
    227     G4double thePhotonEnergy = aParticle->GetTotalEnergy();
    228     G4MaterialPropertiesTable* aMaterialPropertyTable;
    229     G4MaterialPropertyVector* AttenuationLengthVector;
    230 
    231     G4double AttenuationLength = DBL_MAX;
    232 
    233     aMaterialPropertyTable = aMaterial->GetMaterialPropertiesTable();
    234 
    235     if ( aMaterialPropertyTable ) {
    236         AttenuationLengthVector = aMaterialPropertyTable->
    237             GetProperty(m_label_abslen.c_str());
    238         if ( AttenuationLengthVector ){
    239              AttenuationLength = AttenuationLengthVector->
    240                 Value (thePhotonEnergy);
    241         }
    242     }
    243 
    244     return AttenuationLength;
    245 }




Gemini Q
---------

I am considering how to extend the Opticks GPU implementation of LS
reemission/absorption into a 3 component model with (LAB, PPO, bisMSB) and
using probabilites for transition from LAB->PPO, LAB->bisMSB.  I think this
will require every photon within the scintillator to maintain a 2bit 0/1/2
"scintillation species" index using three scintillation icdf textures for
reemission wavelength lookup.   Unlike Geant4, Opticks does not have separate
processes - it has to do the equivalent by random throws etc..  How do you
suggest the scintillation species index is initialized ?



Gemini A
---------

This is an interesting architectural shift. In a standard Geant4 setup, you
would typically have separate `G4Scintillation` processes or multiple `WLS`
processes, each with its own time constant and spectrum. Moving this to the GPU
in **Opticks** means you have to bake that logic into the generation and
reemission kernels.

To handle a 3-component model (LAB, PPO, bis-MSB) where transitions like $LAB
\to PPO$ or $LAB \to bis\text{-}MSB$ occur, the initialization of the "species
index" depends on whether the photon is being **generated** (initial
scintillation) or **reemitted** (wavelength shifting).

Here is a suggested strategy for initializing and updating that 2-bit index:

---

## 1. Primary Scintillation Initialization
When a charged particle deposits energy, the number of photons generated is
usually determined by the total light yield of the mixture. However, the
*initial* species that "hosts" the scintillation must be determined by the
relative concentrations and quantum efficiencies.

* **The Method:** Use a **composition-weighted random throw** at the moment of generation.
* **Implementation:** * Define the relative probabilities $P_{LAB}$, $P_{PPO}$, and $P_{bisMSB}$ based on their molar concentrations and scintillation yields.
    * In the generation kernel, throw a uniform random number $\eta \in [0, 1]$.
    * Assign the index:
        * **0 (LAB):** if $0 \le \eta < P_{LAB}$
        * **1 (PPO):** if $P_{LAB} \le \eta < P_{LAB} + P_{PPO}$
        * **2 (bis-MSB):** if $P_{LAB} + P_{PPO} \le \eta < 1$

* **Texture Lookup:** Use this index to select the appropriate `iCDF` for the initial emission wavelength.

## 2. Reemission/Absorption Transition Logic
This is where your 3-component model lives. When a photon is absorbed by the
scintillator, it doesn't just disappear; it has a probability of being
reemitted by any of the three components.

### The "Transfer Matrix" Approach
Since you mentioned probabilities for transitions (e.g., $LAB \to PPO$), you
should initialize the new index based on a **conditional probability matrix**.
If a photon was just absorbed while traveling through the liquid scintillator:

1.  **Identify the Absorber:** First, determine which component absorbed the
photon. This is usually proportional to the absorption coefficient
$\mu_i(\lambda)$ of each component at the current wavelength.

2.  **Determine the Outcome:** Once the "absorbing species" is identified, use
your transition probabilities to decide if it is reemitted and by which
species.



## 3. Data Structure: Packing the 2-bit Index
In the Opticks `Photon` or `Step` buffer, you are likely constrained by 32-bit alignments. 

* **Initialization Location:** The index should be initialized in the
`generate.cu` (for primary photons) and updated in the `propagate.cu` (for
reemission) kernels.

* **Bit-Packing:** You can pack this 2-bit index into the `flags` uint or the `boundary` integer. For example, using the lower 2 bits of an unused float-as-int field:
    ```cuda
    // Example: Packing into the 2 least significant bits of a flag
    p.flags = (p.flags & ~0x3) | (species_index & 0x3);
    ```

## 4. Selection via Multiple iCDF Textures
Since GPU memory is sensitive to branching, avoid `if/else` blocks for the three species. Instead:

* **Texture Array:** Use a 2D texture array or a layered texture where the `z`-coordinate (layer) is your species index.
* **Execution:** ```cuda
    float wavelength = tex2DLayered(reemission_icdf_tex, random_sample, species_index);
    ```
    This keeps the execution highly parallel and avoids divergent branching across threads.

---

### Summary of Initialization Points

| Event | Logic for Index Initialization |
| :--- | :--- |
| **Initial Scintillation** | Weighted by molar concentration/yield of components. |
| **Reemission (WLS)** | Weighted by the transition probability $P(i \to j)$ from the absorbing species $i$ to the emitting species $j$. |
| **Absorption (No Reemission)** | Photon is terminated; index initialization is irrelevant. |

Would you like to explore how to calculate the absorption-weighted probabilities for the species index when the absorption spectra overlap?



Gemini Q
----------

Geant4 picking between processes would use GetMeanFreePath which does an energy
dependent lookup in the attenuation length vectors eg of the three different
species. That should be equivalent to molar concentration/yield of the
components ?


Gemini A
----------

You’ve hit on the exact point where the Geant4 "macro-view" meets the Opticks
"micro-view." While they are physically equivalent in the long run, the
implementation logic differs because of how they handle the competition between
processes.

To answer directly: **Yes, it is equivalent**, but with a specific nuance
regarding how Geant4 handles the "Total" cross-section versus how you must
handle individual "Species" on the GPU.

---

## 1. The Geant4 Equivalence
In Geant4, if you have three separate absorption processes (one for LAB, PPO,
and bis-MSB), each has its own $\lambda_i(E)$. Geant4 doesn't actually "sum"
the concentrations first; it asks each process for its mean free path:

$$\lambda_{total} = \left( \sum \frac{1}{\lambda_i} \right)^{-1}$$

Because the probability of a process winning is proportional to $1/\lambda_i$,
the "winner" is naturally picked according to the relative strengths of the
absorption cross-sections. Since cross-section $\sigma$ is proportional to
molar concentration, the "molar concentration/yield" weighting you suggested
for Opticks is the **mathematical equivalent** of Geant4's race condition.

## 2. Implementing this in Opticks (GPU)
Since Opticks usually uses a single "Absorption Length" property for a material
to decide *if* a photon dies, you have to "de-mux" that interaction to decide
*which* species was responsible.

### Step A: The Absorption Race
Instead of one $1/\lambda$, you now have:
$$\text{Total Absorption Power} = \frac{1}{\lambda_{LAB}} + \frac{1}{\lambda_{PPO}} + \frac{1}{\lambda_{bisMSB}}$$

In your GPU kernel, when a "Discrete" absorption event is triggered, you
initialize the **Species Index** by throwing a random number against the
relative ratios:

$$P(\text{species}_i) = \frac{1/\lambda_i}{\sum (1/\lambda_j)}$$

### Step B: The Transition (Reemission)
Once the index is initialized to the "Absorbing Species," you then apply the
Quantum Efficiency ($QE$) or Transfer Probability to see if it reemits. 


* If **LAB** absorbs, it might transfer energy to **PPO** (Index changes $0 \to 1$).
* If **PPO** absorbs, it might emit a photon (Index stays $1$) or stay dark.



## 3. Why "Species Index" is better than "Process Index"
In Geant4, a process is a verb (e.g., `Scintillation`). In your Opticks model,
the **Species Index** is a noun (the state of the photon's environment). 

By maintaining the `0/1/2` index:
1. **Scintillation Generation:** You pick an index based on energy deposition sharing (Yield $\times$ Concentration).
2. **Absorption:** You pick an index based on the "winner" of the $\lambda$ competition.
3. **Reemission:** You use the current index to look up the correct `iCDF` texture for the new wavelength.

## 4. Efficiency Note for Opticks

To avoid doing three separate texture lookups for $\lambda_{LAB, PPO, bisMSB}$
at every step (which would be slow), you can pre-calculate a **Total Absorption
Length** for the material and a **Fractional Abundance** texture:

* **Texture 1:** $\lambda_{total}(E)$
* **Texture 2:** A 3-channel "Selector" texture containing the ratios: 
  $$\left[ \frac{\mu_{LAB}}{\mu_{total}}, \frac{\mu_{PPO}}{\mu_{total}}, \frac{\mu_{bisMSB}}{\mu_{total}} \right]$$

This way, the GPU only does one "is it absorbed?" check. If yes, it does one
"who did it?" check using the Selector texture to set the species index.

Does this "Selector Texture" approach align with how you've structured your current Opticks GPU buffers?




Elaborate on the selector texture... that will be wavelength dependent ? By mu you mean 1/lambda ?
-----------------------------------------------------------------------------------------------------


Yes, precisely. In the context of photonics and Geant4 physics, $\mu$ (the
attenuation coefficient) is the inverse of the mean free path:

$$\mu = \frac{1}{\lambda}$$

Because $\mu$ is directly proportional to the cross-section and the density of
the molecules, it is **additive**. If you have three species in a single
medium, the total absorption power of that medium is the sum of the individual
parts:

$$\mu_{total}(\lambda) = \mu_{LAB}(\lambda) + \mu_{PPO}(\lambda) + \mu_{bisMSB}(\lambda)$$

---

## The Wavelength-Dependent Selector Texture

Since each of those three components has a unique absorption spectrum, their
relative "strength" changes depending on the photon's wavelength. For example,
LAB might dominate absorption at 250 nm, while PPO takes over at 300 nm.

To implement this efficiently in Opticks without doing three separate lookups,
you would bake a **Selector Texture**.

### 1. Data Structure

The texture would be a 1D or 2D lookup (where the $x$-axis is
wavelength/energy). Each "pixel" would contain 3 values (like an RGB texture)
representing the **normalized probability** of each species winning the
absorption race:

* **Channel R:** $P_{LAB}(\lambda) = \frac{\mu_{LAB}(\lambda)}{\mu_{total}(\lambda)}$
* **Channel G:** $P_{PPO}(\lambda) = \frac{\mu_{PPO}(\lambda)}{\mu_{total}(\lambda)}$
* **Channel B:** $P_{bisMSB}(\lambda) = \frac{\mu_{bisMSB}(\lambda)}{\mu_{total}(\lambda)}$



### 2. The GPU Execution Flow

In your `propagate.cu` kernel, when the "Absorption" condition is met
(determined by the total absorption length), you do the following:

1.  **Sample the Selector:** `float3 probs = tex1Dfetch(selector_tex, wavelength);`
2.  **Throw a Random Number:** `float rand = curand_uniform(&rng);`
3.  **Determine Species:**
    * If `rand < probs.x`, Species = **0 (LAB)**.
    * Else if `rand < (probs.x + probs.y)`, Species = **1 (PPO)**.
    * Else, Species = **2 (bisMSB)**.

## Why this is equivalent to Geant4
In Geant4, the probability of process $i$ occurring is:
$$P_i = \frac{1/\lambda_i}{\sum 1/\lambda_j}$$

By using the selector texture, you are exactly mimicking this "competition."
You are simply pre-calculating the ratios so the GPU doesn't have to do
divisions and multiple property lookups at runtime.

## Transition vs. Absorption

Since you are modeling a chain ($LAB \to PPO \to bisMSB$), the **Species
Index** you initialize here tells you who currently "holds" the energy. 

* If the **Species Index** is 0 (LAB), you then check your transition probability (e.g., a constant or another texture lookup) to see if it shifts to 1 (PPO).
* If a transition occurs, you update the `species_index` in your photon buffer.
* When it finally decides to reemit, you use that index to pick the **reemission iCDF** (the spectrum).

---

### Implementation Tip: iCDF Layers
If you use a **Layered Texture** for your iCDFs, your lookup becomes a single line of code where the `species_index` acts as the layer selector:

```cuda
// species_index: 0=LAB, 1=PPO, 2=bisMSB
float new_wavelength = tex2DLayered(reemission_icdf_atlas, rand_sample, species_index);
```

This keeps your GPU threads "convergent"—they are all executing the same
instruction, just reading from different memory layers based on their specific
photon's state.

Does your current wavelength-shifting model in Opticks already use a single
iCDF, or are you currently branching based on material?





You suggest float2 because the three probabilities sum to 1 making the third superfluous ?
--------------------------------------------------------------------------------------------



Spot on. Since you have a constrained system where $P_{LAB} + P_{PPO} +
P_{bisMSB} = 1.0$, storing all three is technically redundant and wastes 33% of
the bandwidth for that specific fetch.

By using a `float2` (or a `half2` if you want to be even more aggressive with
memory), you save space and reduce the cache footprint.

## How to structure the `float2` logic

In your pre-processing stage (when you generate the texture), you would store:
* **x**: $P_{LAB}$
* **y**: $P_{PPO}$

Then, in your CUDA kernel, the third probability is implicit:

```cuda
float2 p = tex1Dfetch<float2>(selector_tex, wavelength);
float u = curand_uniform(&rng);

if (u < p.x) {
    species_index = 0; // LAB
} else if (u < (p.x + p.y)) {
    species_index = 1; // PPO
} else {
    species_index = 2; // bisMSB (the remainder)
}
```

## Why this is robust

This approach is actually "safer" than storing all three. If you store three
floats ($x, y, z$), floating-point rounding errors might result in a sum like
$1.0000001$ or $0.9999999$. This can cause edge-case bugs (e.g., a random throw
of $0.99999995$ failing all checks). 

By using the `else` for the final species, you guarantee that **every**
absorption event is assigned to a species, even if the math at the very edge of
the wavelength range is slightly fuzzy.

## Memory Alignment Note

While `float2` is mathematically efficient, keep an eye on your **texture alignment**:

* `float4` lookups are often "free" on NVIDIA hardware because the memory
controller is optimized for 128-bit fetches. 

* If you find you have other wavelength-dependent data (like the **Quantum
Efficiency** of the overall mixture or a **reemission probability**), you might
want to pack those into the `.z` and `.w` channels of a `float4` rather than
leaving them empty. 

> **Optimization Idea:** If you store $(P_{LAB})$ in `.x` and $(P_{LAB} +
P_{PPO})$ in `.y`, you can save an addition operation inside the kernel.

Are you planning to handle the LAB $\to$ PPO $\to$ bisMSB non-radiative energy
transfer as a constant probability, or will those transitions also be
wavelength-dependent?




The transfers probabilities are constants.  
But will need three reemission wavelength tex and three reemission probability
lookups ? Or how would you suggest to implement those ? float3 tex ? 




Since your transfer probabilities are constants, you can simplify the logic significantly. You effectively have two distinct "questions" to answer once a photon is absorbed:

1.  **Who absorbed it?** (Wavelength-dependent, handled by your `float2` selector texture).
2.  **Does it reemit, and from which species?** (Handled by your constant transfer probabilities).

Here is the most efficient way to implement this on the GPU, avoiding unnecessary texture fetches.

---

## 1. The Probability Lookup: Use a `float4`
Since you mentioned needing reemission probabilities, I suggest packing everything into a single **`float4` Selector Texture**. This minimizes memory "trips" (latency) which is usually the biggest bottleneck in Opticks.

Store it like this:
* **`.x`**: $P_{LAB}(\lambda)$ (Relative absorption probability)
* **`.y`**: $P_{LAB}(\lambda) + P_{PPO}(\lambda)$ (Cumulative absorption probability for fast branching)
* **`.z`**: *Total Scintillator QE* or *Absorption Strength* (If needed)
* **`.w`**: *Unused or Wavelength-dependent transition modifier*

## 2. Handling the 3-Component Reemission
Once you have the **Absorbing Species Index** (0, 1, or 2) from the texture, you use your constant transfer probabilities to determine the **Emitting Species Index**.

Because these are constants, **do not use a texture.** Use a small constant-memory array or `switch` logic in the kernel. This is much faster than a texture fetch.

### Suggested Kernel Logic:
```cuda
// 1. Identify who absorbed the photon
float4 select = tex1Dfetch<float4>(selector_tex, wavelength);
float u1 = curand_uniform(&rng);

int absorbing_species = 0;
if (u1 < select.x)      absorbing_species = 0; // LAB
else if (u1 < select.y) absorbing_species = 1; // PPO
else                    absorbing_species = 2; // bisMSB

// 2. Determine if/where it reemits (Constant Transition Logic)
float u2 = curand_uniform(&rng);
int emitting_species = -1; // -1 = Killed/Absorbed

if (absorbing_species == 0) { // LAB
    if (u2 < P_LAB_PPO)      emitting_species = 1; // Transferred to PPO
    else if (u2 < P_LAB_MSB) emitting_species = 2; // Transferred to bisMSB
    // else emitting_species stays -1 (True absorption)
} 
else if (absorbing_species == 1) { // PPO
    if (u2 < QE_PPO)         emitting_species = 1; // PPO reemits
}
else { // bisMSB
    if (u2 < QE_MSB)         emitting_species = 2; // bisMSB reemits
}
```

## 3. The Wavelength Reemission: `tex2DLayered`
Now that you have the `emitting_species` index (0, 1, or 2), you need the new wavelength.

Instead of three separate textures, use **one Layered Texture (`cudaTextureObject_t`)**. 
* **Layer 0:** LAB iCDF
* **Layer 1:** PPO iCDF
* **Layer 2:** bisMSB iCDF

This is the "gold standard" for GPU performance here. Every thread calls the same function, and the hardware handles the layer offset:

```cuda
if (emitting_species >= 0) {
    // Reuse your HD logic here if needed, but pass emitting_species as the layer
    wavelength = sample_layered_icdf(u3, emitting_species); 
}
```

## Why this is better than a `float3` texture:
1.  **Memory Coalescing:** One `float4` fetch is often faster than a `float3` because it is perfectly aligned to 128-bit memory boundaries.
2.  **Branching vs. Fetching:** Doing a few `if/else` checks on **constants** is nearly free on modern GPUs (especially if the constants are in `__constant__` memory). Fetching from a texture is expensive (high latency).
3.  **Simplicity:** You only have one "Species Index" to track in your photon buffer.

**Summary of assets needed:**
1.  **Selector Texture (`float4`)**: 1D texture indexed by wavelength.
2.  **iCDF Atlas (Layered 2D Texture)**: Contains the three reemission spectra.
3.  **Constant Buffer**: Stores your $LAB \to PPO$ transition probabilities.




My thoughts
------------

* scint_species_texture














tex2D
------

::

    (ok) A[blyth@localhost opticks]$ opticks-f tex2D
    ./ana/twhite.py:     44     return tex2D(source_texture, ui, 0.5f );  // line 0
    ./examples/UseOptiXTexture/UseOptiXTexture.cc:tex1D, tex2D and tex3D functions.
    ./examples/UseOptiXTextureLayered/UseOptiXTextureLayered.cc:tex1D, tex2D and tex3D functions.
    ./externals/cuda.bash:cuda-samples-tex2D(){  cuda-samples-find tex2D ; }
    ./externals/optixnote.bash:     82   prd_radiance.result = make_float3( tex2D(envmap, u, v) );
    ./ggeo/GSourceLib.hh:     54     return tex2D(source_texture, ui, 0.5f );  // line 0
    ./optixrap/cu/boundary_lookup.h:    float4 val = tex2D(boundary_texture, x, y );
    ./optixrap/cu/boundary_lookup.h:    float4 val = tex2D(boundary_texture, x, y );
    ./optixrap/cu/color_lookup.h:    uchar4 col = tex2D(color_texture, line+0.5f, 0.5f );  
    ./optixrap/cu/reemission_lookup.h:    return tex2D(reemission_texture, ui, 0.5f );  // line 0
    ./optixrap/cu/source_lookup.h:    return tex2D(source_texture, ui, 0.5f );  // line 0
    ./optixrap/tests/cu/boundaryTest.cu:    float4 val = tex2D(boundary_texture, x, y );
    ./optixrap/tests/cu/texTest.cu: //   float val = tex2D(some_texture, x, y );
    ./optixrap/tests/cu/textureTest.cu:    return tex2D(reemission_texture, ui, 0.5f );  // line 0
    ./qudarap/QBnd.cu:    q.f = tex2D<float4>( tex, x, y );     
    ./qudarap/QBnd_MOCK.h:        q.f = tex2D<float4>( tex, x, y );     
    ./qudarap/QMultiFilm.cu:    float4 v = tex2D<float4>( tex, x, y );     
    ./qudarap/QScint.cu:    float v = tex2D<float>( tex, x, y );     
    ./qudarap/QTex.cu:    uchar4 c = tex2D<uchar4>(texObj, tu+0.5f, tv+0.5f);
    ./qudarap/QTexLookup.cu:    T v = tex2D<T>( tex, x, y );
    ./qudarap/qmultifilm.h:    float4 value = tex2D<float4>(tex,x,y);
    ./qudarap/tests/QSim_MockTest.cc:1. tex2D lookups 
    ./qudarap/tests/QSim_MockTest.cc:Mocking tex2D lookups is not so common. See::
    ./qudarap/qscint.h:    return tex2D<float>(scint_tex, u0, y0 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, u0*10.f , y1 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, (u0 - 0.9f)*10.f , y2 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, u0,  y0 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, u0*20.f , y1 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, (u0 - 0.95f)*20.f , y2 );
    ./qudarap/qscint.h:        wl = tex2D<float>(scint_tex, u0,  y0 );
    ./qudarap/qbnd.h:    float4 props = tex2D<float4>( boundary_tex, x, y );
    ./qudarap/qbnd.h:    float4 props = tex2D<float4>( boundary_tex, x, y );
    ./qudarap/QCerenkov.cu:    float v = tex2D<float>( tex, x, y );
    ./qudarap/qsim.h:1. get more of the below to work on CPU with mocked curand (and in future mocked tex2D and cudaTextureObject_t )
    ./sysrap/s_mock_texture.h:    template<typename T> T tex2D( cudaTextureObject_t t, float x, float y ) const  ; 
    ./sysrap/s_mock_texture.h:inline T MockTextureManager::tex2D( cudaTextureObject_t t, float x, float y ) const 
    ./sysrap/s_mock_texture.h:template<typename T> T tex2D(cudaTextureObject_t t, float x, float y )
    ./sysrap/s_mock_texture.h:             << "s_mock_texture.h/tex2D : FATAL : null MockTextureManager "
    ./sysrap/s_mock_texture.h:    return mgr->tex2D<T>( t, x, y ); 
    ./sysrap/tests/SIMGStandaloneTest.cu:    uchar4 c = tex2D<uchar4>(texObj, tu+0.5f, tv+0.5f); 
    ./sysrap/tests/s_mock_texture_test.cc:        float4 payload = tex2D<float4>(obj, x, y ) ;
    ./sysrap/tests/s_mock_texture_test.cc:        bb[idx] = tex2D<float4>(obj, x, y ) ;
    ./sysrap/tests/s_mock_texture_test.cc:        bb[idx] = tex2D<float4>(obj, x, y ) ;
    ./sysrap/tests/s_mock_texture_test.cc:    float4 props = tex2D<float4>(obj, x, y );  
    (ok) A[blyth@localhost opticks]$ 






time smear
------------

::

    144 
    145     // =================================================================
    146     // Cascaded Exponential Delay
    147     // =================================================================
    148     if (tau_nr > 0.0) {
    149         deltaTime += G4RandExponential::shoot(tau_nr);
    150     }
    151 
    152     const G4MaterialPropertyVector* timeconst_vec =
    153         aMaterialPropertiesTable->GetProperty(target_timeconst.c_str());
    154     if (timeconst_vec) {
    155         G4double tau_rad = timeconst_vec->Value(aTrack.GetKineticEnergy());
    156         if (tau_rad > 0.0) deltaTime += G4RandExponential::shoot(tau_rad);
    157     }





* https://apc.u-paris.fr/~franco/g4doxy/html/Randomize_8hh-source.html



::

    00034 // Distributions used ...
    00035 //
    00036 #include <CLHEP/Random/RandFlat.h>
    00037 #include <CLHEP/Random/RandBit.h>
    00038 #include <CLHEP/Random/RandGamma.h>
    00039 #include <CLHEP/Random/RandGaussQ.h>
    00040 #include <CLHEP/Random/RandPoissonQ.h>
    00041 #include <CLHEP/Random/RandExponential.h>
    00042 #include <CLHEP/Random/RandGeneral.h>
    00043 
    00044 #define G4RandStat CLHEP::HepStat
    00045 #define G4RandFlat CLHEP::RandFlat
    00046 #define G4RandBit CLHEP::RandBit
    00047 #define G4RandGamma CLHEP::RandGamma
    00048 #define G4RandGauss CLHEP::RandGaussQ
    00049 #define G4RandExponential CLHEP::RandExponential
    00050 #define G4RandGeneral CLHEP::RandGeneral
    00051 #define G4Random CLHEP::HepRandom
    00052 
    00053 #define G4UniformRand() CLHEP::HepRandom::getTheEngine()->flat()
    00054 



* https://apc.u-paris.fr/~franco/g4doxy4.10/html/_rand_exponential_8cc_source.html


::

   45 double RandExponential::shoot(double mean) {
   46   return -std::log(HepRandom::getTheEngine()->flat())*mean;
   47 }




current qudarap reemission impl
--------------------------------

* 1st decide between::

     BULK_ABSORB
     BULK_SCATTER
     "SAIL_TO_BOUNDARY"

* considers reemission only within the  




::

     718 inline QSIM_METHOD int qsim::propagate_to_boundary(unsigned& flag, RNG& rng, sctx& ctx)
     719 {
     720     sphoton& p = ctx.p ;
     721     const sstate& s = ctx.s ;
     722 
     723     const float& absorption_length = s.material1.y ;
     724     const float& scattering_length = s.material1.z ;
     725     const float& reemission_prob = s.material1.w ;
     726     const float& group_velocity = s.m1group2.x ;
     727     const float& distance_to_boundary = ctx.prd->q0.f.w ;

     734     float u_scattering = curand_uniform(&rng) ;
     735     float u_absorption = curand_uniform(&rng) ;

     751     float scattering_distance = -scattering_length*logf(u_scattering);
     752     float absorption_distance = -absorption_length*logf(u_absorption);



     778     if (absorption_distance <= scattering_distance)
     779     {
     780         if (absorption_distance <= distance_to_boundary)
     781         {
     782             p.time += absorption_distance/group_velocity ;
     783             p.pos  += absorption_distance*(p.mom) ;
     784 
     785 
     786 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
     787             float absorb_time_delta = absorption_distance/group_velocity ;
     788             if( ctx.pidx == base->pidx )
     789             {
     790             printf("//qsim.propagate_to_boundary.body.BULK_ABSORB pidx %7lld : post = np.array([%10.5f,%10.5f,%10.5f,%10.5f]) ; absorb_time_delta = %10.8f   \n",
     791                     ctx.pidx, p.pos.x, p.pos.y, p.pos.z, p.time, absorb_time_delta  );
     792 
     793             }
     794 #endif
     795 
     796             float u_reemit = reemission_prob == 0.f ? 2.f : curand_uniform(&rng);  // avoid consumption at absorption when not scintillator
     797 
     798 
     799 #if !defined(PRODUCTION) && defined(DEBUG_TAG)
     800             if( u_reemit != 2.f ) tagr.add( stag_to_ree, u_reemit) ;
     801 #endif
     802 
     803 
     804             if (u_reemit < reemission_prob)
     805             {
     806                 float u_re_wavelength = curand_uniform(&rng);
     807                 float u_re_mom_ph = curand_uniform(&rng);
     808                 float u_re_mom_ct = curand_uniform(&rng);
     809                 float u_re_pol_ph = curand_uniform(&rng);
     810                 float u_re_pol_ct = curand_uniform(&rng);
     811 
     812                 p.wavelength = scint->wavelength(u_re_wavelength);
     813                 p.mom = uniform_sphere(u_re_mom_ph, u_re_mom_ct);
     814                 p.pol = normalize(cross(uniform_sphere(u_re_pol_ph, u_re_pol_ct), p.mom));






