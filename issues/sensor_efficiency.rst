sensor_efficiency
====================

Objective
----------

Update Opticks collection of sensor efficiencies to allow DE culling on GPU.

Summary
----------

JUNO PMT wavelength dependent efficiency is carried in surface properties, 
which get translated into Opticks/GGeo/GSurfaceLib leading to wavelength 
dependent entries in the GPU boundary texture. 

The efficiencies collected by Opticks need to be the factor excluding 
the energy dependent part.  So that Opticks can reproduce the 
efficiency calculation done in ProcessHits. 


Old Opticks Efficiency Collection
-------------------------------------

jcv LSExpDetectorConstruction_Opticks::

    116     for(unsigned i=0 ; i < num_sensor ; i++)
    117     {
    118         const G4PVPlacement* pv = sensor_placements[i] ; // i is 0-based unlike sensor_index
    119         unsigned sensor_index = 1 + i ; // 1-based 
    120         assert(pv); 
    121         G4int copyNo = pv->GetCopyNo();  
    122         int pmtid = copyNo ; 
    123         int pmtcat = 0 ; // sd->getPMTCategory(pmtid); 
    124         float efficiency_1 = sd->getQuantumEfficiency(pmtid); 
    125         float efficiency_2 = sd->getEfficiencyScale() ; 
    126 
    127         g4ok->setSensorData( sensor_index, efficiency_1, efficiency_2, pmtcat, pmtid ); 
    128     }


    1049 double junoSD_PMT_v2::getEfficiencyScale() const
    1050 {
    1051     return m_angle_response ;
    1052 }

    0987 double junoSD_PMT_v2::getQuantumEfficiency(int pmtID) const
     988 {   
     989     double eff_pde = 1.;
     990     double qe_calc = 1.;
     991     double qescale = m_qescale ;
     992     
     993     if(pmtID<18000)
     994     {   
     995         qescale = m_enable_optical_model ? m_qescale_optical_model : m_qescale ;
     996         
     997         eff_pde = m_PMTSimParsvc->get_pde(pmtID);
     998         if( m_PMTParamsvc->isHamamatsu(pmtID))
     999         {   
    1000             qe_calc = eff_pde / eff_ce_Hamamatsu;
    1001         } 
    1002         else if ( m_PMTParamsvc->isHighQENNVT(pmtID) )
    1003         {   
    1004             qe_calc = eff_pde / eff_ce_NNVT_HiQE;
    1005         } 
    1006         else if ( m_PMTParamsvc->isNormalNNVT(pmtID) )
    1007         {   
    1008             qe_calc = eff_pde / eff_ce_NNVT_Normal;
    1009         }
    1010     }
    1011     else if(pmtID<300000)
    1012     {   
    1013         qe_calc = 0.3;
    1014     } 
    1015     else if(pmtID>=300000)
    1016     {   
    1017         qe_calc = m_PMTSimParsvc->get_QE(pmtID);
    1018     } 
    1019     return qescale*qe_calc ;
    1020 }



Use of EFFICIENCY s.surface.x in Opticks (pre 7)
-----------------------------------------------------

Efficency comes from boundary texture::

   optixrap/cu/generate.cu
   optixrap/cu/state.h:fill_state

   0034 __device__ void fill_state( State& s, int boundary, uint4 identity, float wavelength )
     35 {
     36     // boundary : 1 based code, signed by cos_theta of photon direction to outward geometric normal
     37     // >0 outward going photon
     38     // <0 inward going photon
     39     //  
     40     // NB the line is above the details of the payload (ie how many float4 per matsur) 
     41     //    it is just 
     42     //                boundaryIndex*4  + 0/1/2/3     for OMAT/OSUR/ISUR/IMAT 
     43     //  
     44 
     45     int line = boundary > 0 ? (boundary - 1)*BOUNDARY_NUM_MATSUR : (-boundary - 1)*BOUNDARY_NUM_MATSUR  ;
     46         
     47     // pick relevant lines depening on boundary sign, ie photon direction relative to normal
     48     //      
     49     int m1_line = boundary > 0 ? line + IMAT : line + OMAT ;
     50     int m2_line = boundary > 0 ? line + OMAT : line + IMAT ;
     51     int su_line = boundary > 0 ? line + ISUR : line + OSUR ;
     52         
     53     //  consider photons arriving at PMT cathode surface
     54     //  geometry normals are expected to be out of the PMT 
     55     //  
     56     //  boundary sign will be -ve : so line+3 outer-surface is the relevant one
     57 
     58     s.material1 = boundary_lookup( wavelength, m1_line, 0);
     59     s.m1group2  = boundary_lookup( wavelength, m1_line, 1);
     60 
     61     s.material2 = boundary_lookup( wavelength, m2_line, 0);
     62     s.surface   = boundary_lookup( wavelength, su_line, 0);
     63 

   0679 __device__ int
    680 propagate_at_surface(Photon &p, State &s, curandState &rng)
    681 {
    682     float u_surface = curand_uniform(&rng);
    683 #ifdef WITH_ALIGN_DEV
    684     float u_surface_burn = curand_uniform(&rng);
    685 #endif
    686 
    687 #ifdef WITH_ALIGN_DEV_DEBUG
    688     rtPrintf("propagate_at_surface   u_OpBoundary_DiDiAbsorbDetectReflect:%.9g \n", u_surface);
    689     rtPrintf("propagate_at_surface   u_OpBoundary_DoAbsorption:%.9g \n", u_surface_burn);
    690 #endif
    691 
    692     if( u_surface < s.surface.y )   // absorb   
    693     {
    694         s.flag = SURFACE_ABSORB ;
    695         s.index.x = s.index.y ;   // kludge to get m2 into seqmat for BREAKERs
    696         return BREAK ;
    697     }
    698     else if ( u_surface < s.surface.y + s.surface.x )  // absorb + detect
    699     {
    700         s.flag = SURFACE_DETECT ;
    701         s.index.x = s.index.y ;   // kludge to get m2 into seqmat for BREAKERs
    702         return BREAK ;
    703     }
    704     else if (u_surface  < s.surface.y + s.surface.x + s.surface.w )  // absorb + detect + reflect_diffuse 
    705     {
    706         s.flag = SURFACE_DREFLECT ;
    707         propagate_at_diffuse_reflector_geant4_style(p, s, rng);
    708         return CONTINUE;
    709     }
    710     else
    711     {
    712         s.flag = SURFACE_SREFLECT ;
    713         //propagate_at_specular_reflector(p, s, rng );
    714         propagate_at_specular_reflector_geant4_style(p, s, rng );
    715         return CONTINUE;
    716     }
    717 }






Old way, jcv LSExpDetectorConstruction_Opticks::

    107     const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements() ;       
    108     unsigned num_sensor = sensor_placements.size(); 
    109 
    110     // 2. use the placements to pass sensor data : efficiencies, categories, identifiers  
    111 
    112     const junoSD_PMT_v2* sd = dynamic_cast<const junoSD_PMT_v2*>(sd_) ;  
    113     assert(sd) ; 
    114 
    115     LOG(info) << "[ setSensorData num_sensor " << num_sensor ; 
    116     for(unsigned i=0 ; i < num_sensor ; i++)
    117     {
    118         const G4PVPlacement* pv = sensor_placements[i] ; // i is 0-based unlike sensor_index
    119         unsigned sensor_index = 1 + i ; // 1-based 
    120         assert(pv);
    121         G4int copyNo = pv->GetCopyNo();
    122         int pmtid = copyNo ;
    123         int pmtcat = 0 ; // sd->getPMTCategory(pmtid); 
    124         float efficiency_1 = sd->getQuantumEfficiency(pmtid);
    125         float efficiency_2 = sd->getEfficiencyScale() ;
    126 
    127         g4ok->setSensorData( sensor_index, efficiency_1, efficiency_2, pmtcat, pmtid );
    128     }
    129     LOG(info) << "] setSensorData num_sensor " << num_sensor ;
    130 
    131     // 3. pass theta dependent efficiency tables for all sensor categories 
    132 



Trace cathode EFFICIENCY in offline
--------------------------------------

jgr EFFICIENCY 

jcv DsPhysConsOptical
    NOT using : Simulation/DetSimV2/PhysiSim/src/DsG4OpBoundaryProcess.cc


Photocathode materials are created::

    epsilon:offline blyth$ grep new\ G4Material\(\"photocathode Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
            Photocathode_mat = new G4Material("photocathode",density,1);
            Photocathode_mat_3inch = new G4Material("photocathode_3inch",density,1);
            Photocathode_mat_MCP20inch = new G4Material("photocathode_MCP20inch",density,1);
            Photocathode_mat_MCP8inch = new G4Material("photocathode_MCP8inch",density,1);
            Photocathode_mat_Ham20inch = new G4Material("photocathode_Ham20inch",density,1);
            Photocathode_mat_Ham8inch = new G4Material("photocathode_Ham8inch",density,1);
            Photocathode_mat_HZC9inch = new G4Material("photocathode_HZC9inch",density,1);

jcv LSExpDetectorConstructionMaterial::

     833     G4Material* Photocathode_mat_Ham20inch = G4Material::GetMaterial("photocathode_Ham20inch", any_warnings);
     834     if (Photocathode_mat_Ham20inch) {
     835         G4cout << "photocathode_Ham20inch is constructed from the GDML file" << G4endl;
     836     } else {
     837         G4cout << "photocathode_Ham20inch is constructed from the code" << G4endl;
     838         density = 5. *g/cm3; // true??
     839         Photocathode_mat_Ham20inch = new G4Material("photocathode_Ham20inch",density,1);
     840         Photocathode_mat_Ham20inch->AddElement(K, 1);
     841         G4MaterialPropertiesTable* PhotocathodeMPT_Ham20inch = new G4MaterialPropertiesTable();
     842 
     843         G4cout << "Setup photocathode_Ham20inch Material Tables from MCParamsSvc" << G4endl;
     844         helper_mpt(PhotocathodeMPT_Ham20inch, "RINDEX", mcgt.data(), "Material.photocathode_Ham20inch.RINDEX");
     845         helper_mpt(PhotocathodeMPT_Ham20inch, "KINDEX", mcgt.data(), "Material.photocathode_Ham20inch.KINDEX");
     846         helper_mpt(PhotocathodeMPT_Ham20inch, "REFLECTIVITY", mcgt.data(), "Material.photocathode_Ham20inch.REFLECTIVITY");
     847         helper_mpt(PhotocathodeMPT_Ham20inch, "THICKNESS", mcgt.data(), "Material.photocathode_Ham20inch.THICKNESS");
     848       
     849         IMCParamsSvc::map_s2d s_map;
     850         bool st = mcgt->Get("Material.photocathode_Ham20inch.scale", s_map);
     851         double scale_qe = 1.0;
     852         if (st && s_map.count("qe_before") && s_map.count("qe_after")&& s_map.count("pmt_qe_scale_for_elec"))
     853            {
     854                 scale_qe = s_map["qe_after"] / s_map["qe_before"] * 1.0/s_map["pmt_qe_scale_for_elec"];
     855                 G4cout << "Scale qe from " << s_map["qe_before"]
     856                      << " to " << s_map["qe_after"]
     857                        << " factor: " << scale_qe
     858                        <<" pmt_qe_scale_for_elec :"<< s_map["pmt_qe_scale_for_elec"]
     859                        << G4endl;
     860            }
     861       if(m_use_pmtsimsvc){
     862            helper_mpt(PhotocathodeMPT_Ham20inch, "EFFICIENCY", mcgt.data(), "Material.photocathode_Ham20inch.EFFICIENCY_v2");
     863         std::cout<<"we use new pmt sim svc!!"<<std::endl;
     864         }else{
     865 
     866       helper_mpt(PhotocathodeMPT_Ham20inch, "EFFICIENCY", mcgt.data(), "Material.photocathode_Ham20inch.EFFICIENCY",scale_qe);
     867         }
     868         PhotocathodeMPT_Ham20inch->DumpTable();
     869         Photocathode_mat_Ham20inch->SetMaterialPropertiesTable(PhotocathodeMPT_Ham20inch);
     870     }


Huh *m_use_pmtsimsvc* is setting the photocathode efficiency property to 1 at all energies and not using the scale ?::

    O[blyth@localhost data]$ cat Simulation/DetSim/Material/photocathode_Ham20inch/EFFICIENCY_v2
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    O[blyth@localhost data]$ 

This means that every photon will be detected according to Geant4::

    322 inline
    323 void G4OpBoundaryProcess::DoAbsorption()
    324 {
    325               theStatus = Absorption;
    326 
    327               if ( G4BooleanRand(theEfficiency) ) {
    328 
    329                  // EnergyDeposited =/= 0 means: photon has been detected
    330                  theStatus = Detection;
    331                  aParticleChange.ProposeLocalEnergyDeposit(thePhotonMomentum);
    332               }
    333               else {
    334                  aParticleChange.ProposeLocalEnergyDeposit(0.0);
    335               }
    336 
    337               NewMomentum = OldMomentum;
    338               NewPolarization = OldPolarization;
    339 
    340 //              aParticleChange.ProposeEnergy(0.0);
    341               aParticleChange.ProposeTrackStatus(fStopAndKill);
    342 }

::

    O[blyth@localhost data]$ cat Simulation/DetSim/Material/photocathode_Ham20inch/EFFICIENCY
    1.55   *eV    1e-05
    1.7714   *eV    1e-05
    1.7971   *eV    1e-05
    1.8235   *eV    1e-03
    1.8507   *eV    0.002
    1.8788   *eV    0.003
    1.9077   *eV    0.004
    1.9375   *eV    0.006
    1.9683   *eV    0.009
    2   *eV    0.013
    2.0328   *eV    0.019
    2.0667   *eV    0.026
    2.1017   *eV    0.035
    2.1379   *eV    0.043
    2.1754   *eV    0.054
    2.2143   *eV    0.064
    2.2545   *eV    0.076
    2.2963   *eV    0.091
    2.3396   *eV    0.117
    2.3846   *eV    0.156
    2.4314   *eV    0.188
    2.48   *eV    0.201
    2.5306   *eV    0.211
    2.5833   *eV    0.227
    2.6383   *eV    0.244
    2.6957   *eV    0.267
    2.7556   *eV    0.294
    2.8182   *eV    0.31
    2.8837   *eV    0.325
    2.9524   *eV    0.339
    3.0244   *eV    0.346
    3.1   *eV    0.355
    3.1795   *eV    0.356
    3.2632   *eV    0.352
    3.3514   *eV    0.348
    3.4444   *eV    0.329
    3.5429   *eV    0.291
    3.6471   *eV    0.201
    3.7576   *eV    0.092
    3.875   *eV    0.038
    4   *eV    0.015
    4.1333   *eV    1e-05
    15.5   *eV    1e-05
    O[blyth@localhost data]$ 


All EFFICIENCY_v2 are 1::

    O[blyth@localhost data]$ find . -name EFFICIENCY_v2
    ./Simulation/DetSim/Material/photocathode_3inch/EFFICIENCY_v2
    ./Simulation/DetSim/Material/photocathode_Ham20inch/EFFICIENCY_v2
    ./Simulation/DetSim/Material/photocathode_MCP20inch/EFFICIENCY_v2
    O[blyth@localhost data]$ find . -name EFFICIENCY_v2 -exec cat {} \;
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    O[blyth@localhost data]$ 


::

    epsilon:offline blyth$ jgr use_pmtsimsvc
    ./Simulation/DetSimV2/PMTSim/include/PMTSDMgr.hh:    bool m_use_pmtsimsvc;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:       bool m_use_pmtsimsvc;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:       void setUsePmtSimSvc(bool f){ m_use_pmtsimsvc = f ; }
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:     if(m_use_pmtsimsvc){
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("UsePmtSimSvc",m_use_pmtsimsvc = true);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setUsePmtSimSvc(m_use_pmtsimsvc);
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:    bool m_use_pmtsimsvc;
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:    void setUsePmtSimSvc(bool f ){ m_use_pmtsimsvc = f;}
    ./Simulation/DetSimV2/DetSimOptions/include/DetSim0Svc.hh:    bool m_use_pmtsimsvc;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:       if(m_use_pmtsimsvc){ 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        if(m_use_pmtsimsvc){
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:      if(m_use_pmtsimsvc){
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("UsePmtSimSvc",m_use_pmtsimsvc=true);
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    dc->setUsePmtSimSvc(m_use_pmtsimsvc);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  m_use_pmtsimsvc = true;
    epsilon:offline blyth$ 
    epsilon:offline blyth$ 




And the MPT from them is used for opsurf created in the PMTManager::

    epsilon:offline blyth$ jgl G4Material::GetMaterial\(\"photocathode 
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Cerenkov.cc
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Cerenkov.cc
    ./Simulation/DetSimV2/PMTSim/src/Hello3inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/Hello8inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/R12860TorusPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/MCP20inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV2Manager.cc
    ./Simulation/DetSimV2/PMTSim/src/R12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/Ham8inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/HZC9inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/HelloPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/MCP8inchPMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/R12860OnlyFrontPMTManager.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc
    ./Doc/detsim/examples/R12199PMTManager.cc
    ./Doc/oum/source/detsim/examples/R12199PMTManager.cc



jcv HamamatsuR12860PMTManager::

    122 void
    123 HamamatsuR12860PMTManager::init_material() {
    124 
    125      GlassMat = G4Material::GetMaterial("Pyrex");
    126      PMT_Vacuum = G4Material::GetMaterial("Vacuum");
    127      DynodeMat = G4Material::GetMaterial("Steel");
    128 
    129      Photocathode_opsurf =  new G4OpticalSurface(GetName()+"_Photocathode_opsurf");
    130      Photocathode_opsurf->SetType(dielectric_metal); // ignored if RINDEX defined
    131      //Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode")->GetMaterialPropertiesTable() );
    132      Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_Ham20inch")->GetMaterialPropertiesTable() );
    133 
    134      if (m_fast_cover) {
    135          m_cover_mat = G4Material::GetMaterial(m_cover_mat_str);
    136          assert(m_cover_mat);
    137      }
    138 }

    751 void
    752 HamamatsuR12860PMTManager::helper_make_optical_surface()
    753 {
    754     new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf1",
    755             inner1_phys, body_phys,
    756             Photocathode_opsurf);
    757     new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf2",
    758             body_phys, inner1_phys,
    759             Photocathode_opsurf);
    760     new G4LogicalBorderSurface(GetName()+"_mirror_logsurf1",
    761             inner2_phys, body_phys,
    762             m_mirror_opsurf);
    763     new G4LogicalBorderSurface(GetName()+"_mirror_logsurf2",
    764             body_phys, inner2_phys,
    765             m_mirror_opsurf);
    766 }













jsd::

     455     qe = qe_calc*m_qescale ;  // <-- NB m_qescale depends on the last pmtID hit and m_enable_optical_model
     456 
     457      if(m_use_pmtsimsvc){
     458         qe = m_enable_optical_model ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     459         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     460       //  std::cout<<"we use new pmt sim svc !!,we reset qe and ce"<<std::endl;
     461      }
     462 


m_PMTSimParsvc

63         void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }



::

    epsilon:issues blyth$ jgr setPMTSimParamSvc
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    epsilon:offline blyth$ 


jcv PMTSDMgr::

     59 G4VSensitiveDetector*
     60 PMTSDMgr::getSD()
     61 {
     62     m_pmt_param_svc = 0;
     64     SniperPtr<PMTParamSvc> svc(*getParent(), "PMTParamSvc");
     70         m_pmt_param_svc = svc.data();
     72 
     73     m_pmt_sim_param_svc = 0;
     75     SniperPtr<IPMTSimParamSvc> simsvc(*getParent(), "PMTSimParamSvc");
     81         m_pmt_sim_param_svc = simsvc.data();
     83 


jcv PMTSimParamSvc::

    1011 double PMTSimParamSvc::get_pmtcat_qe(int pmtcat, double energy){
    1012     double qe = -1 ;
    1013     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(pmtcat);
    1014     assert(vec);
    1015     qe = vec->Value(energy);
    1016     return qe;  
    1017 }
    1018 
    1019 double PMTSimParamSvc::get_pmtid_qe(int pmtid, double energy){
    1020 
    1021   int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid) ;
    1022   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1023   double qe = get_pmtcat_qe(pmtcat, energy);
    1024   double qe_scale = get_pmt_qe_scale(pmtid);
    1025   qe = qe*qe_scale;
    1026   assert(qe > 0 && qe < 1);
    1027   return qe;
    1028 }

    1091 G4MaterialPropertyVector*  PMTSimParamSvc::get_pmtcat_qe_vs_energy(int pmtcat){
    1092    assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1093    G4MaterialPropertyVector * vec = 0 ;
    1094     switch(pmtcat)
    1095     {   //FIXME:KPMT_Unknown represent WP pmt,which use normal NNVTMCP ?
    1096         case kPMT_Unknown:     { vec = m_QEshape_WP_PMT;
    1097                                } ; break ;
    1098         case kPMT_NNVT:        { vec = m_QEshape_NNVT;
    1099                                } ; break ;
    1100         case kPMT_Hamamatsu:   { vec = m_QEshape_R12860;
    1101                                } ; break ;
    1102         // kPMT_HZC : 3inch PMT.
    1103         case kPMT_HZC:         { vec = m_QEshape_HZC;
    1104                                } ; break ;
    1105        case kPMT_NNVT_HighQE: { vec = m_QEshape_NNVT_HiQE;                                                                                         } ; break ;
    1106     }
    1107    assert(vec);
    1113    return vec;
    1114 }

    0287   helper_pmt_mpt(m_QEshape_HZC, mcgt.data(),"PMTProperty.HZC_3inch.QE_shape");
     288   helper_pmt_mpt(m_QEshape_NNVT, mcgt.data(),"PMTProperty.NNVTMCP.QE_shape");
     289   helper_pmt_mpt(m_QEshape_NNVT_HiQE, mcgt.data(),"PMTProperty.NNVTMCP_HiQE.QE_shape");
     290   helper_pmt_mpt(m_QEshape_R12860, mcgt.data(),"PMTProperty.R12860.QE_shape");
     291   helper_pmt_mpt(m_QEshape_WP_PMT, mcgt.data(),"PMTProperty.WP_PMT.QE_shape");


    O[blyth@localhost data]$ find . -name QE_shape
    ./Simulation/DetSim/PMTProperty/R12860/QE_shape
    ./Simulation/DetSim/PMTProperty/NNVTMCP/QE_shape
    ./Simulation/DetSim/PMTProperty/WP_PMT/QE_shape
    ./Simulation/DetSim/PMTProperty/HZC_3inch/QE_shape
    ./Simulation/DetSim/PMTProperty/NNVTMCP_HiQE/QE_shape

    O[blyth@localhost data]$ cat Simulation/DetSim/PMTProperty/NNVTMCP/QE_shape
    1.55    *eV 0.014
    1.7714    *eV 0.014
    1.7971    *eV 0.013
    1.8235    *eV 0.012
    1.8507    *eV 0.013
    1.8788    *eV 0.012
    1.9077    *eV 0.015
    1.9375    *eV 0.018
    1.9683    *eV 0.022
    2    *eV 0.027
    2.0328    *eV 0.034
    2.0667    *eV 0.04
    2.1017    *eV 0.048
    2.1379    *eV 0.056
    2.1754    *eV 0.064
    2.2143    *eV 0.072
    2.2545    *eV 0.081
    2.2963    *eV 0.09
    2.3396    *eV 0.105
    2.3846    *eV 0.13
    2.4314    *eV 0.163
    2.48    *eV 0.176
    2.5306    *eV 0.183
    2.5833    *eV 0.195
    2.6383    *eV 0.206
    2.6957    *eV 0.221
    2.7556    *eV 0.239
    2.8182    *eV 0.252
    2.8837    *eV 0.263
    2.9524    *eV 0.273
    3.0244    *eV 0.28
    3.1    *eV 0.287
    3.1795    *eV 0.288
    3.2632    *eV 0.284
    3.3514    *eV 0.28
    3.4444    *eV 0.267
    3.5429    *eV 0.245
    3.6471    *eV 0.175
    3.7576    *eV 0.097
    3.875    *eV 0.044
    4    *eV 1e-03
    4.1333    *eV 1e-05
    15.5    *eV 1e-05

    O[blyth@localhost data]$ cat Simulation/DetSim/PMTProperty/R12860/QE_shape
    1.55   *eV    1e-05
    1.7714   *eV    1e-05
    1.7971   *eV    1e-05
    1.8235   *eV    1e-03
    1.8507   *eV    0.002
    1.8788   *eV    0.003
    1.9077   *eV    0.004
    1.9375   *eV    0.006
    1.9683   *eV    0.009
    2   *eV    0.013
    2.0328   *eV    0.019
    2.0667   *eV    0.026
    2.1017   *eV    0.035
    2.1379   *eV    0.043
    2.1754   *eV    0.054
    2.2143   *eV    0.064
    2.2545   *eV    0.076
    2.2963   *eV    0.091
    2.3396   *eV    0.117
    2.3846   *eV    0.156
    2.4314   *eV    0.188
    2.48   *eV    0.201
    2.5306   *eV    0.211
    2.5833   *eV    0.227
    2.6383   *eV    0.244
    2.6957   *eV    0.267
    2.7556   *eV    0.294
    2.8182   *eV    0.31
    2.8837   *eV    0.325
    2.9524   *eV    0.339
    3.0244   *eV    0.346
    3.1   *eV    0.355
    3.1795   *eV    0.356
    3.2632   *eV    0.352
    3.3514   *eV    0.348
    3.4444   *eV    0.329
    3.5429   *eV    0.291
    3.6471   *eV    0.201
    3.7576   *eV    0.092
    3.875   *eV    0.038
    4   *eV    0.015
    4.1333   *eV    1e-05
    15.5   *eV    1e-05
    O[blyth@localhost data]$ 



