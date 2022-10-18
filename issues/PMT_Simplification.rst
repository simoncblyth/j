PMT_Simplification
=====================

::

     80 G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
     81 {
     82 
     83     if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner2_phys){
     84         return false;
     85     }

     // HMM ? so photons dont bounce from inner2 ?




jcv HamamatsuR12860PMTManager::

     340 void HamamatsuR12860PMTManager::helper_make_solid()
     341 {  
     342     double pmt_delta = 1E-3*mm ;
     343     double inner_delta =  -5*mm ;
     344     double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ;
     345    
     346     double zcut = m_pmt_equator_to_bottom ;
     347 
     348     Hamamatsu_R12860_PMTSolid* maker = m_pmtsolid_maker ;
     349     pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
     350     body_solid   = maker->GetSolid(GetName() + "_body_solid",   body_delta , ' ');
     351     inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' ');  // no longer used
     352     inner1_solid = maker->GetSolid(GetName() + "_inner1_solid", inner_delta, 'H');
     353     inner2_solid = maker->GetSolid(GetName() + "_inner2_solid", inner_delta, 'T');
     354 




     308 void HamamatsuR12860PMTManager::init_pmt()
     309 {
     310   helper_make_solid();
     311   helper_make_logical_volume();
     312   helper_make_physical_volume();
     313 
     314   if(m_enable_optical_model || m_plus_dynode)
     315   {
     316       helper_make_dynode_volume();
     317   }
     318 
     319   helper_make_optical_surface();
     320 
     321   if(m_enable_optical_model)
     322   {
     323       helper_fast_sim();
     324   }
     325 
     326   helper_vis_attr();
     327 }


     975 void
     976 HamamatsuR12860PMTManager::helper_fast_sim()
     977 {
     978 #ifdef PMTSIM_STANDALONE
     979 #else
     980     G4Region* body_region = new G4Region(this->GetName()+"_body_region");
     981     body_log->SetRegion(body_region);
     982     body_region->AddRootLogicalVolume(body_log);
     983 
     984     junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
     985                                                                    body_phys, body_region);
     986 

jcv junoPMTOpticalModel::

    021 junoPMTOpticalModel::junoPMTOpticalModel(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
     22     : G4VFastSimulationModel(modelName, envelope)
     23 {       


     24 enum EWhereAmI { OutOfRegion, kInGlass, kInVacuum };
     25 
     26 class junoPMTOpticalModel : public G4VFastSimulationModel
     27 {
     28     public:
     29         junoPMTOpticalModel(G4String, G4VPhysicalVolume*, G4Region*);
     30         ~junoPMTOpticalModel();
     31 
     32         virtual G4bool IsApplicable(const G4ParticleDefinition&);
     33         virtual G4bool ModelTrigger(const G4FastTrack&);
     34         virtual void DoIt(const G4FastTrack&, G4FastStep&);
     35 
     36         void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
     37         IPMTSimParamSvc* getPMTSimParamSvc() const { return m_PMTSimParSvc; }
     38 
     39         void setPMTParamSvc(IPMTParamSvc* svc) { m_PMTParamSvc = svc; }
     40         IPMTParamSvc* getPMTParamSvc() const { return m_PMTParamSvc; }
     41    
     42     private:
     43         G4MaterialPropertyVector* _rindex_glass;
     44         G4MaterialPropertyVector* _rindex_vacuum;
     45 
     46         G4VSolid* _inner1_solid;
     47         G4VSolid* _inner2_solid;
     48         G4VSolid* envelope_solid;
     49 
     50         G4VPhysicalVolume* _inner1_phys;
     51         G4VPhysicalVolume* _inner2_phys;
     52 


    281 void junoPMTOpticalModel::InitOpticalParameters(G4VPhysicalVolume* envelope_phys)
    282 {
    283     G4LogicalVolume* envelope_log
    284         = envelope_phys->GetLogicalVolume();
    285     G4MaterialPropertiesTable* glass_pt
    286         = envelope_log->GetMaterial()->GetMaterialPropertiesTable();
    287 
    288     _rindex_glass   = glass_pt->GetProperty("RINDEX");
    289     _inner1_phys    = envelope_log->GetDaughter(0);
    290     _inner1_solid   = _inner1_phys->GetLogicalVolume()->GetSolid();
    291     _rindex_vacuum  = _inner1_phys->GetLogicalVolume()->GetMaterial()
    292                                   ->GetMaterialPropertiesTable()->GetProperty("RINDEX");
    293 
    294     _inner2_phys    = envelope_log->GetDaughter(1);
    295     _inner2_solid   = _inner2_phys->GetLogicalVolume()->GetSolid();
    296 }



::

     616 void HamamatsuR12860PMTManager::helper_make_physical_volume()
     617 {
     618 
     619     G4ThreeVector equatorTranslation(0.,0.,m_z_equator);
     620     G4ThreeVector noTranslation(0.,0.,0.);
     621 
     622     // place outer solids in envelope
     623     body_phys= new G4PVPlacement
     624         ( 0,                   // no rotation
     625           noTranslation,  // puts body equator in right place
     626           body_log,            // the logical volume
     627           GetName()+"_body_phys", // a name for this physical volume
     628           m_logical_pmt,                // the mother volume
     629           false,               // no boolean ops
     630           0 );                 // copy number
     631 
     632     // place inner solids in outer solid (vacuum)
     633     inner1_phys= new G4PVPlacement
     634         ( 0,                   // no rotation
     635           noTranslation,       // puts face equator in right place
     636           GetName()+"_inner1_phys",         // a name for this physical volume
     637           inner1_log,                    // the logical volume
     638           body_phys,           // the mother volume
     639           false,               // no boolean ops
     640           0 );                 // copy number
     641     inner2_phys= new G4PVPlacement
     642         ( 0,                   // no rotation
     643           noTranslation,       // puts face equator in right place
     644           GetName()+"_inner2_phys",         // a name for this physical volume
     645           inner2_log,                    // the logical volume
     646           body_phys,           // the mother volume
     647           false,               // no boolean ops
     648           0 );                 // copy number
     649 }






g4-cls G4Region::

    099 class G4Region
    100 {
    101   typedef std::vector<G4LogicalVolume*> G4RootLVList;
    ...
    249   private:
    250 
    251     G4String fName;
    252 
    253     G4RootLVList fRootVolumes;
    254     G4MaterialList fMaterials;
    255     G4MaterialCoupleMap fMaterialCoupleMap;
    256 
    257     G4bool fRegionMod;
    258     G4ProductionCuts* fCut;
    259 



    114     void AddRootLogicalVolume(G4LogicalVolume* lv);
    115     void RemoveRootLogicalVolume(G4LogicalVolume* lv, G4bool scan=true);
    116       // Add/remove root logical volumes and set/reset their
    117       // daughters flags as regions. They also recompute the
    118       // materials list for the region.



    137 G4FastSimulationManager* G4Region::GetFastSimulationManager() const
    138 { 
    139   return G4MT_fsmanager;
    140 }



    284 // *******************************************************************
    285 // AddRootLogicalVolume:
    286 //  - Adds a root logical volume and sets its daughters flags as
    287 //    regions. It also recomputes the materials list for the region.
    288 // *******************************************************************
    289 //
    290 void G4Region::AddRootLogicalVolume(G4LogicalVolume* lv)
    291 {
    292   // Check the logical volume is not already in the list
    293   //
    294   G4RootLVList::iterator pos;
    295   pos = std::find(fRootVolumes.begin(),fRootVolumes.end(),lv);
    296   if (pos == fRootVolumes.end())
    297   {
    298     // Insert the root volume in the list and set it as root region
    299     //
    300     fRootVolumes.push_back(lv);
    301     lv->SetRegionRootFlag(true);
    302   }
    303 
    304   // Scan recursively the tree of daugther volumes and set regions
    305   //
    306   ScanVolumeTree(lv, true);
    307 
    308   // Set region as modified
    309   //
    310   fRegionMod = true;
    311 }



g4-cls G4LogicalVolume::

    310     inline G4bool IsRootRegion() const;
    311       // Replies if the logical volume represents a root region or not.
    312     inline void SetRegionRootFlag(G4bool rreg);
    313       // Sets/unsets the volume as a root region for cuts.
    314     inline G4bool IsRegion() const;
    315       // Replies if the logical volume is part of a cuts region or not.
    316     inline void SetRegion(G4Region* reg);
    317       // Sets/unsets the volume as cuts region.
    318     inline G4Region* GetRegion() const;
    319       // Return the region to which the volume belongs, if any.
    320     inline void PropagateRegion();
    321       // Propagates region pointer to daughters.


    308 inline
    309 void G4LogicalVolume::PropagateRegion()
    310 {
    311   fRegion->ScanVolumeTree(this, true);
    312 }



::

    epsilon:junosw blyth$ g4-cc ModelTrigger
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc://      2) for these, loops on the ModelTrigger() methods to find out 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:  // Loops on the ModelTrigger() methods
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    // Asks the ModelTrigger method if it must be trigged now.
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    if(fApplicableModelList[iModel]->ModelTrigger(fFastTrack)) {
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    if(fApplicableModelList[iModel]->AtRestModelTrigger(fFastTrack))
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:    case OneModelTrigger:
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:      G4cout << "OneModelTrigger" << G4endl;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:    case NoModelTrigger:
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:      G4cout << "NoModelTrigger" << G4endl;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/parameterisations/gflash/src/GFlashShowerModel.cc:G4bool GFlashShowerModel::ModelTrigger(const G4FastTrack & fastTrack )
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ 



