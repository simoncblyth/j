way_capture_boundary_pos
=============================

FIXED : Issue getting boundary_pos zeros following geometry update
--------------------------------------------------------------------

The issue was caused by a change in volume name from the old "pAcylic" to new "pAcrylic"

::

    2021-04-11 03:19:03.690 INFO  [387404] [OEvent::downloadHits@485]  nhit 2894 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-11 03:19:03.690 INFO  [387404] [OEvent::downloadHiys@519]  nhiy 2894 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    2021-04-11 03:19:03.690 FATAL [387404] [G4Opticks::propagateOpticalPhotons@1152]  m_way_enabled num_hiys 2894
     junoSD_PMT_v2_Opticks::EndOfEvent.propagateOpticalPhotons  eventID 2 num_gensteps 65 num_photons 11068 num_hit 2894 way_enabled 1 waymask 3
    0      gp.x -18095.87  gp.y 489.71     gp.z 6571.12    gp.R 19258.24   pmt 5841    SI|SD|BT|EX          otk 6      oti11.26    bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    1      gp.x -17238.81  gp.y -1016.21   gp.z -8570.35   gp.R 19278.49   pmt 12763   SI|SD|BT|EX          otk 6      oti6.42     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    2      gp.x -15682.93  gp.y -8572.11   gp.z -7334.10   gp.R 19319.01   pmt 12192   SI|SD|BT|EX          otk 6      oti3.17     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    3      gp.x 13329.51   gp.y -12943.02  gp.z 5284.92    gp.R 19316.52   pmt 6312    SI|RE|SD|BT|EC       otk 6      oti11.82    bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    4      gp.x -14393.66  gp.y -6396.46   gp.z 11085.91   gp.R 19261.09   pmt 3558    SI|SC|SD|BT|EC       otk 6      oti8.11     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00      
    5      gp.x 9684.62    gp.y 7512.89    gp.z -14875.38  gp.R 19274.66   pmt 15717   SI|SD|BT|EX          otk 6      oti5.37     bti 0.00     bp.x 0.00       bp.y 0.00       bp.z 0.00       bp.R 0.00   



JUNO : config way capture
----------------------------

Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc::


     17 #ifdef WITH_G4OPTICKS
     18 /**
     19 LSExpDetectorConstruction_Opticks::Setup
     20 ------------------------------------------
     21 
     22 1. pass geometry to Opticks, translate it to GPU and return sensor placements 
     23 2. use the placements to pass sensor data : efficiencies, categories, identifiers
     24 3. pass theta dependent efficiency tables for all sensor categories
     25 
     26 
     27 
     28 
     29                              |--------- 2230 ----------------|-- 120--|
     30                              20050                           17820    17700
     31                           / /                               /         /
     32                          / /                               /         /
     33                         / pInnerWater                     /         /
     34                        / /                               /         /
     35                       / /                  (0)          /         /
     36                      pTyvek                  \         pAcrylic  /
     37                     / /                       \       /         /
     38                    / /                         \     /         pTarget:LS
     39                   / /                           \   /         /
     40                  / /                             \ /         /
     41                 / /                              (1)        /
     42                / /                               / \       /
     43               / /                               /   \     /
     44              / /                               /     \   /         
     45             / /                               /       \ /
     46            / /                          Wa   /  Ac    (2)             
     47           / /                               /         / \
     48          / /                               /         /   \
     49         / /                               /         /     \        LS    
     50 
     51 **/
     52 
     53 
     54 G4Opticks* LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd_, int opticksMode )  // static
     55 {
     56     if( opticksMode == 0 ) return nullptr ;
     57     LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ;
     58 
     59     assert(world);
     60 
     61     // 1. pass geometry to Opticks, translate it to GPU and return sensor placements  
     62 
     63     G4Opticks* g4ok = new G4Opticks ;
     64 
     65     bool outer_volume = true ;
     66     bool profile = true ;
     67 
     68     // waymask selects whether to match on pvname and/or boundary for the recorder boundary position
     69     const char* geospecific_default =   "--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3" ; // (1): gives radius 17820
     70     //const char* geospecific_default = "--way --pvname pTarget  --boundary Acrylic///LS --waymask 3" ;      // (2): gives radius 17700
     71     const char* embedded_commandline_extra = SSys::getenvvar("LSXDC_GEOSPECIFIC", geospecific_default ) ; // see OGeo::initWayControl
     72 
     73     LOG(info) << " embedded_commandline_extra " << embedded_commandline_extra ;
     74     g4ok->setPlacementOuterVolume(outer_volume);
     75     g4ok->setProfile(profile);
     76     g4ok->setEmbeddedCommandLineExtra(embedded_commandline_extra);
     77     g4ok->setGeometry(world);
     78 
     79     const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements() ;
     80     unsigned num_sensor = sensor_placements.size();
     81 
     82     // 2. use the placements to pass sensor data : efficiencies, categories, identifiers  
     83 




DYB : Configuring way capture
-----------------------------------


Combining both boundary and pvname should be able to reproduce what is needed::

    --boundary Water///Acrylic --pvname pInnerWater
    --pvname /dd/Geometry/AD/lvOIL#pvOAV0xbf8f6380x3eeda30



Try --boundary MineralOil///LiquidScintillator
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    OGeo=INFO OKTest --save --pvname  /dd/Geometry/AD/lvSST#pvOIL0xc2415100x3f0b6a0  --boundary MineralOil///LiquidScintillator
    2020-12-09 20:23:59.501 INFO  [5114983] [OGeo::initWayControl@250]  way_control.x (node) 3155 way_control.y (boundary) 43 way_control.z 0 way_control.w 0


Just way_control selecting on boundary giving far fewer entries than expected::

    run ~/opticks/ana/way_buffer.py  

    In [9]: wy[wy[:,0] != 0.]                                                                                                                                                                                                                 
    Out[9]: 
    array([[ -17287.121 , -798545.3   ,   -5065.5293,       0.1   ],
           [ -18034.482 , -799721.25  ,   -4941.7017,       0.1   ]],
          dtype=float32)

    In [10]: wy.shape                                                                                                                                                                                                                         
    Out[10]: (10000, 4)

    In [11]: np.where(wy[:,0] != 0 )                                                                                                                                                                                                          
    Out[11]: (array([4449, 5370]),)


Examination of the record boundary and material sequence together with the history should be informative.


Try --boundary MineralOil///Acrylic
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    OGeo=INFO OKTest --save  --boundary MineralOil///Acrylic
    ...
    2020-12-09 20:57:32.958 INFO  [5140883] [OGeo::initWayControl@250]  way_control.x (node) -1 way_control.y (boundary) 21 way_control.z 0 way_control.w 0




OpticksCfg : --pvname --boundary --material
---------------------------------------------

::

    0172     m_pvname(""),
     173     m_boundary(""),
     174     m_material("Water")

     608    m_desc.add_options()
     609        ("pvname", boost::program_options::value<std::string>(&m_pvname), "name of PV volume selected for some purpose" );
     610 
     611    m_desc.add_options()
     612        ("boundary", boost::program_options::value<std::string>(&m_boundary), "name of boundary selected for some purpose" );
     613 
     614    m_desc.add_options()
     615        ("material", boost::program_options::value<std::string>(&m_material), "name of material used for some purpose" );
     616 


    2182 template <class Listener>
    2183 const std::string& OpticksCfg<Listener>::getPVName() const
    2184 {
    2185     return m_pvname ;
    2186 }
    2187 
    2188 template <class Listener>
    2189 const std::string& OpticksCfg<Listener>::getBoundary() const
    2190 {
    2191     return m_boundary ;
    2192 }
    2193 
    2194 template <class Listener>
    2195 const std::string& OpticksCfg<Listener>::getMaterial() const
    2196 {
    2197     return m_material ;
    2198 }


::

    epsilon:offline blyth$ find . -name '*.cc' -exec grep -H G4Opticks {} \;

    Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc



    054 G4Opticks* LSExpDetectorConstruction_Opticks::Setup(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd_, int opticksMode )  // static
     55 {
     56     if( opticksMode == 0 ) return nullptr ;
     57     LOG(info) << "[ WITH_G4OPTICKS opticksMode " << opticksMode  ;
     58 
     59     assert(world);
     60 
     61     // 1. pass geometry to Opticks, translate it to GPU and return sensor placements  
     62 
     63     G4Opticks* g4ok = new G4Opticks ;
     64 
     65     bool outer_volume = true ;
     66     bool profile = true ;
     67 
     68     // waymask selects whether to match on pvname and/or boundary for the recorder boundary position
     69     const char* geospecific_default = "--way --pvname pAcylic  --boundary Water///Acrylic --waymask 3" ; // (1): gives radius 17820
     70     //const char* geospecific_default = "--way --pvname pTarget  --boundary Acrylic///LS --waymask 3" ;      // (2): gives radius 17700
     71     const char* embedded_commandline_extra = SSys::getenvvar("LSXDC_GEOSPECIFIC", geospecific_default ) ; // see OGeo::initWayControl
     72 
     73     LOG(info) << " embedded_commandline_extra " << embedded_commandline_extra ;
     74     g4ok->setPlacementOuterVolume(outer_volume);
     75     g4ok->setProfile(profile);
     76     g4ok->setEmbeddedCommandLineExtra(embedded_commandline_extra);
     77     g4ok->setGeometry(world);
     78 
     79     const std::vector<G4PVPlacement*>& sensor_placements = g4ok->getSensorPlacements() ;
     80     unsigned num_sensor = sensor_placements.size();



::

     250 void OGeo::initWayControl()
     251 {
     252     int node     = m_ggeo->getFirstNodeIndexForPVName();   // --pvname pInnerWater 
     253     int boundary = m_ggeo->getSignedBoundary() ;           // --boundary Water///Acrylic  
     254     unsigned waymask = m_ok->getWayMask() ;    // --waymask 0/1/2/3   controls way_select 
     255 
     256     optix::int4 way_control = optix::make_int4(node,boundary,0,waymask);
     257     LOG(LEVEL)
     258         << " way_control.x (node) " << way_control.x
     259         << " way_control.y (boundary) " << way_control.y
     260         << " way_control.z " << way_control.z
     261         << " way_control.w (waymask) " << way_control.w
     262         ;
     263     m_context["way_control"]->setInt(way_control);
     264 }
     265 

::

    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::InitOpticks@212] 
    # BOpticksKey::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.85d8514854333c1a7c3fd50cc91507dc

    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::EmbeddedCommandLine@131] Using ecl :[ --compute --embedded --xanalytic --production --nosave] OPTICKS_EMBEDDED_COMMANDLINE
    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::EmbeddedCommandLine@132]  mode(Pro/Dev/Asis) P using "pro" (production) commandline without event saving 
    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::EmbeddedCommandLine@137] Using extra1 argument :[--way --pvname pAcylic  --boundary Water///Acrylic --waymask 3]
    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::EmbeddedCommandLine@147] Using eclx envvar :[--gdmlkludge] OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
    2021-04-11 03:15:29.669 INFO  [387404] [G4Opticks::InitOpticks@232] instanciate Opticks using embedded commandline only 
     --compute --embedded --xanalytic --production --nosave  --way --pvname pAcylic  --boundary Water///Acrylic --waymask 3 --gdmlkludge
    2021-04-11 03:15:29.670 INFO  [387404] [Opticks::init@441] COMPUTE_MODE compute_requested  forced_compute  hostname localhost.localdomain
    2021-04-11 03:15:29.670 INFO  [387404] [Opticks::init@450]  mandatory keyed access to geometry, opticksaux 


    2021-04-11 03:16:29.354 INFO  [387404] [GNodeLib::getFirstNodeIndexForPVName@316]  pvname pAcylic nidxs.size() 0 nidx -1
    2021-04-11 03:16:29.354 INFO  [387404] [OGeo::initWayControl@257]  way_control.x (node) -1 way_control.y (boundary) 17 way_control.z 0 way_control.w (waymask) 3
    2021-04-11 03:16:29.354 INFO  [387404] [OGeo::init@240] OGeo  top Sbvh ggg Sbvh assembly Sbvh instance Sbvh


::

    310 int GNodeLib::getFirstNodeIndexForPVName(const char* pvname) const
    311 {
    312     if( pvname == NULL ) return -1 ;
    313     std::vector<unsigned> nidxs ;
    314     getNodeIndicesForPVName(nidxs, pvname);
    315     int nidx = nidxs.size() > 0 ? nidxs[0] : -1 ;
    316     LOG(info)
    317         << " pvname " << pvname
    318         << " nidxs.size() " << nidxs.size()
    319         << " nidx " << nidx
    320         ;
    321     return nidx ;
    322 }



::

    kcd
    O[blyth@localhost 1]$ cd GNodeLib
    O[blyth@localhost GNodeLib]$ vim -R all_volume_PVNames.txt


     67838 ZC2.A05_A05_HBeam_phys
     67839 ZC2.A05_A05_HBeam_phys
     67840 ZC2.A05_A05_HBeam_phys
     67841 pCentralDetector
     67842 pInnerWater
     67843 pAcrylic
     67844 pTarget
     67845 lSJCLSanchor_phys
     67846 lSJCLSanchor_phys
     67847 lSJFixture_phys
     67848 lSJFixture_phys
     67849 lSJFixture_phys


Looks like the formerly mis-spelled "pAcylic" has been corrected to "pAcrylic" 

* THIS IS SMOKING GUN CAUSE FOR ALL THE boundary_pos zeros 


After setting LSXDC_GEOSPECIFIC in tds to use the newly corrected::

    853    
    854    local geospecific_default="--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3"
    855    export LSXDC_GEOSPECIFIC=${geospecific_default}
    856 
    857    local script=$JUNOTOP/offline/Examples/Tutorial/share/tut_detsim.py
    85

    [New Thread 0x7ffde27fc700 (LWP 416613)]
    2021-04-11 03:34:58.495 INFO  [414792] [GNodeLib::getFirstNodeIndexForPVName@316]  pvname pAcrylic nidxs.size() 1 nidx 67842
    2021-04-11 03:34:58.495 INFO  [414792] [OGeo::initWayControl@257]  way_control.x (node) 67842 way_control.y (boundary) 17 way_control.z 0 way_control.w (waymask) 3
    2021-04-11 03:34:58.495 INFO  [414792] [OGeo::init@240] OGeo  top Sbvh ggg Sbvh assembly Sbvh instance Sbvh
    2021-04-11 03:34:58.495 INFO  [414792] [GGeoLib::dump@385] OGeo::convert GGeoLib numMergedMesh 10 ptr 0x158368b0











Initial Investigations
-------------------------



Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh::

     30     public:
     31         inline G4int GetOriginalTrackID() const {return originalTrackID;}
    
     // no setter 
 

Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc::

     20 NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
     21 {
     22     originalTrackID = aTrack->GetTrackID();
     23 
     24     // phys
     25     phys_michael_electron = 0;
     26     phys_neutron_capture = 0;
     27     phys_decay_mode = 0;
     28     from_cerenkov =false;
     29     is_reemission =false;
     30 
     31     m_op_is_original_op = false;
     32     m_op_start_time = 0;
     33 }
     34 
     35 NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
     36 {
     37     originalTrackID = aTrackInfo->originalTrackID;
     38     tracedAncestors = aTrackInfo->tracedAncestors;
     39 
     40     // phys
     41     phys_michael_electron = 0;
     42     phys_neutron_capture = 0;
     43     phys_decay_mode = 0;
     44 
     45     from_cerenkov = aTrackInfo->from_cerenkov;
     46     is_reemission = aTrackInfo->is_reemission;
     47 
     48     m_op_is_original_op = false;
     49     m_op_start_time = aTrackInfo->m_op_start_time;
     50 
     51     pos_at_boundary = aTrackInfo->pos_at_boundary;
     52 }

     // trackinfo for the secondary adopts that of the parent 

     // NormalTrackInfo::originalTrackID 
     //     for NTI constructed from G4Track it is G4Track::GetTrackID
     //     for NTI constructed from that the value is passed down the lineage
     //



Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc::

    307 void
    308 NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    309 
    310   if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0)
    311     {
    312         NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    313         G4Track* theTrack = (G4Track*)aTrack;
    314         theTrack->SetUserInformation(anInfo);
    315     }
    316     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    317 

    ///  Looks like only the primary has the honour of an NTI instanciated 
    ///  from the G4Track 


::

    1113     collectScintillationStep(
    1114 
    1115          OpticksGenstep_G4Scintillation_1042,           // (int)gentype       (0) 
    1116          aTrack->GetTrackID(),                          // (int)ParenttId     
    1117          aMaterial->GetIndex(),                         // (int)MaterialIndex
    1118          numPhotons,                                    // (int)NumPhotons
    1119 


Gensteps contain this in 2nd slot (4*0+1)::

    epsilon:g4ok blyth$ grep -B 2 -A 2 GetTrackID *.cc
    G4Opticks.cc-
    G4Opticks.cc-         OpticksGenstep_G4Scintillation_1042,           // (int)gentype       (0) 
    G4Opticks.cc:         aTrack->GetTrackID(),                          // (int)ParenttId     
    G4Opticks.cc-         aMaterial->GetIndex(),                         // (int)MaterialIndex
    G4Opticks.cc-         numPhotons,                                    // (int)NumPhotons
    --
    --
    G4Opticks.cc-
    G4Opticks.cc-         OpticksGenstep_DsG4Scintillation_r3971,        // (int)gentype       (0) 
    G4Opticks.cc:         aTrack->GetTrackID(),                          // (int)ParenttId     
    G4Opticks.cc-         aMaterial->GetIndex(),                         // (int)MaterialIndex
    G4Opticks.cc-         numPhotons,                                    // (int)NumPhotons
    --
    --
    G4Opticks.cc-
    G4Opticks.cc-         OpticksGenstep_G4Cerenkov_1042,                // (int)gentype       (0)
    G4Opticks.cc:         aTrack->GetTrackID(),                          // (int)ParenttId     
    G4Opticks.cc-         aMaterial->GetIndex(),                         // (int)MaterialIndex
    G4Opticks.cc-         numPhotons,                                    // (int)NumPhotons
    epsilon:g4ok blyth$ 
    epsilon:g4ok blyth$ 


Genstep arrays can contain many items, do I want to do this association CPU side. 
Actually the WAY buffer cannot fit in a quad, have to spill to two so easiest to 
just collect GPU side.





Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc::

    431     G4VUserTrackInformation* trkinfo = track->GetUserInformation();
    432     if (trkinfo) {
    433         NormalTrackInfo* normaltrk = dynamic_cast<NormalTrackInfo*>(trkinfo);
    434         if (normaltrk) {
    435             producerID = normaltrk->GetOriginalTrackID();
    436             is_from_cerenkov = normaltrk->isFromCerenkov();
    437             is_reemission = normaltrk->isReemission();
    438 
    439             t_start = normaltrk->getOriginalOPStartTime();
    440 
    441             is_original_op = normaltrk->isOriginalOP();
    442             boundary_pos = normaltrk->getBoundaryPos();
    443         }
    444     }


 
Opticks equivalents ?::

   m_op_is_original_op = does not have REEMISSION in flags 
    



Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc::

    352 void
    353 NormalAnaMgr::PostUserTrackingAction(const G4Track* aTrack) {
    354 
    355    if (aTrack->GetParentID() == 0) {
    356         // this is the primary particle
    357         const G4ThreeVector& pos = aTrack->GetPosition();
    358         LogDebug << "!!!Primary Track " << aTrack->GetTrackID() << ": ";
    359         LogDebug << "+ " << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
    360         LogDebug << "+ " << aTrack->GetKineticEnergy() << std::endl;
    361     }
    362     G4TrackingManager* tm = G4EventManager::GetEventManager()
    363                                             -> GetTrackingManager();
    364     G4TrackVector* secondaries = tm->GimmeSecondaries();
    365     if(secondaries)
    366     {
    367         NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());

    /// from the point of view of the secondaries 
    ///
    ///     aTrack:parent 
    ///     info:parentInfo
    ///

    368 
    369         if (!info) {
    370              return;
    371         }
    372 
    373         size_t nSeco = secondaries->size();
    374         if(nSeco>0)
    375         {   
    376             for(size_t i=0;i<nSeco;i++)
    377             {
    378                 
    379                 // make sure the secondaries' track info is empty
    380                 // if already attached track info, skip it.
    381                 if ((*secondaries)[i]->GetUserInformation()) {
    382                     LogDebug << "The secondary already has user track info. skip creating new one" << std::endl;
    383                     continue;
    384                 }
    385                 NormalTrackInfo* infoNew = new NormalTrackInfo(info);
    386                if(m_flag_hitinfo==true)
    387                {
    388                 // cerekov tag
    389                 if ((*secondaries)[i]->GetCreatorProcess() 
    390                     and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
    391                     infoNew->setFromCerenkov();
    392                     LogDebug << "### infoNew->setFromCerenkov()" << std::endl;
    393                 }
    394                 // reemission tag
    395                 // + parent track is an OP
    396                 // + secondary is also an OP
    397                 // + the creator process is Scintillation
    398                 if (aTrack->GetDefinition() == G4OpticalPhoton::Definition()
    399                     and (*secondaries)[i]->GetDefinition() == G4OpticalPhoton::Definition()
    400                     and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Scintillation") {
    401                     infoNew->setReemission();
    402                 }
    403                 // original optical photon tag 
    404                 if (aTrack->GetDefinition() != G4OpticalPhoton::Definition() 
    405                     and (*secondaries)[i]->GetDefinition() == G4OpticalPhoton::Definition()
    406                     ) {
    407                     LogDebug << "------ original OP" << std::endl;
    408                     infoNew->setOriginalOP();
    409                 }
    410                 }
    411                 // save parent track info
    412                 infoNew->setParentName(aTrack->GetDefinition()->GetParticleName());
    413                 
    414                 (*secondaries)[i]->SetUserInformation(infoNew);
    415             }
    416         }
    417     }
    418  
    419 
    420 }




"additional" information including boundary_pos
-------------------------------------------------

* needs the normalanamgr which is not always enabled : so need
  to structure the Opticks equivalent in separate optional "way" buffers 
   

Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc::

    166 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
    167 {
    ...
    393     // == additional information from User Track information
    394     int producerID = -1;
    395     bool is_from_cerenkov = false;
    396     bool is_reemission = false;
    397     bool is_original_op = false;
    398     double t_start = 0;
    399     G4ThreeVector boundary_pos;
    ...
    401     G4VUserTrackInformation* trkinfo = track->GetUserInformation();
    402     if (trkinfo) {
    403         NormalTrackInfo* normaltrk = dynamic_cast<NormalTrackInfo*>(trkinfo);
    404         if (normaltrk) {
    405             producerID = normaltrk->GetOriginalTrackID();

    ///    Opticks equivalent : grab from genstep ?

    406             is_from_cerenkov = normaltrk->isFromCerenkov();
    407             is_reemission = normaltrk->isReemission();

    ///    Opticks equivalent : from p.flag 

    409             t_start = normaltrk->getOriginalOPStartTime();

    ///    Opticks equivalent : grab the time from the genstep ?

    410 
    411             is_original_op = normaltrk->isOriginalOP();  

    ///     Opticks equivalent : excluding reemission select original OP 
    ///      ( p.flag & REEMISSION == 0  )  

    412             boundary_pos = normaltrk->getBoundaryPos();

    ///     Need to implement this with "way_buffer"


    413         }
    414     }

::

    [blyth@localhost offline]$ jgl NormalTrackInfo
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh
    ./Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyCalibAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuFastnProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/OPSimAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/DepositEnergyTTAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc
    ./Simulation/DetSimV2/AnalysisCode/src/RadioAnaMgr.cc
    ./Doc/oum/source/detsim/structures.md
    ./Doc/oum/source/detsim/anaelement.md
    ./Doc/detsim/structures.md
    ./Doc/detsim/anaelement.md

    [blyth@localhost offline]$ jgr setBoundaryPos
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:        inline void setBoundaryPos(const G4ThreeVector& pos) { pos_at_boundary = pos; }
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:                info->setBoundaryPos(postpos);

    340 void
    341 NormalAnaMgr::UserSteppingAction(const G4Step* step) {
    ...
    379         G4StepPoint* prepoint = step->GetPreStepPoint();
    380         G4StepPoint* postpoint = step->GetPostStepPoint();
    381         // if(postpoint->GetStepStatus()==fGeomBoundary) {
    382         //     LogInfo << " * "
    383         //             << prepoint->GetPhysicalVolume()->GetName() << "/"
    384         //             << postpoint->GetPhysicalVolume()->GetName() << " "
    385         //             << std::endl;
    386         // }
    387         if(postpoint->GetStepStatus()==fGeomBoundary
    388         && prepoint->GetPhysicalVolume()
    389         && prepoint->GetPhysicalVolume()->GetName() == "pAcylic"
    390         && postpoint->GetPhysicalVolume()
    391         && postpoint->GetPhysicalVolume()->GetName() == "pInnerWater"
    392             ) {
    393             G4ThreeVector prepos = prepoint->GetPosition();
    394             G4ThreeVector postpos = postpoint->GetPosition();
    395             // LogInfo << " * "
    396             //         << prepoint->GetPhysicalVolume()->GetName() << "/"
    397             //         << postpoint->GetPhysicalVolume()->GetName() << " "
    398             //         << "(" << prepos.x() << ", " << prepos.y() << ", " << prepos.z() << "), "
    399             //         << "(" << postpos.x() << ", " << postpos.y() << ", " << postpos.z() << "), "
    400             //         << std::endl;
    401             // TODO use postpoint as the boundary between acrylic and water
    402             NormalTrackInfo* info = (NormalTrackInfo*)(track->GetUserInformation());
    403             if (info) {
    404                 info->setBoundaryPos(postpos);
    405             }
    406 
    407         }


::

    /**
    NormalAnaMgr::PreUserTrackingAction
    ------------------------------------

    1. instanciate NormalTrackInfo track UserInformation for tracks with ParentID 0 (primary)
    2. for opticalphoton which are originalOP and have a zero OriginalOPStartTime 
       setOriginalOPStartTime to the track global time

    **/

    236 void
    237 NormalAnaMgr::PreUserTrackingAction(const G4Track* aTrack) {
    238 
    239     if(aTrack->GetParentID()==0 && aTrack->GetUserInformation()==0)
    240     {   
    241         NormalTrackInfo* anInfo = new NormalTrackInfo(aTrack);
    242         G4Track* theTrack = (G4Track*)aTrack;
    243         theTrack->SetUserInformation(anInfo);
    244     }
    245     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    246 
    247     if (!info) {
    248         return;
    249     }
    250 
    251     if (aTrack->GetDefinition()->GetParticleName() == "opticalphoton"
    252             and aTrack->GetCreatorProcess()) {
    253         LogDebug << "###+++ "<< aTrack ->GetCreatorProcess()->GetProcessName() <<std::endl;
    254     }
    255 
    256     // original OP
    257     // set the info 
    258     if (aTrack->GetDefinition()->GetParticleName() == "opticalphoton"
    259             and info->isOriginalOP()
    260             and info->getOriginalOPStartTime() == 0.0) {
    261         // make sure this track info is not changed before.
    262         assert(info->getOriginalOPStartTime() == 0.0);
    263         LogDebug << "------ original OP" << std::endl;
    264         info->setOriginalOPStartTime(aTrack->GetGlobalTime());

    ///  Opticks genstep times collect eg G4Opticks::collectGenstep_DsG4Scintillation_r3971
    ///  the global time from the non-optical particle that is producing photons
    ///
    ///      G4double      t0 = pPreStepPoint->GetGlobalTime();
    /// 
    ///   that is not quite the same as the above which is the global time of the the first photon 
    ///   reading G4Cerenkov and G4Scintillation will presumably show



    265     }
    266 
    267     // An example: Get the parent particle name from track info
    268     if (info && aTrack->GetDefinition()!=G4OpticalPhoton::Definition()) {
    269         // const G4String& parent_name = info->getParentName();
    270         // G4cout << " The parent of " << aTrack->GetDefinition()->GetParticleName()
    271         //        << " is " << parent_name
    272         //        << G4endl;
    273     }
    274 }



    /**
    NormalAnaMgr::PostUserTrackingAction
    --------------------------------------

    Loop over secondaries from this track instanciating NormalTrackInfo 


    **/

    276 void
    277 NormalAnaMgr::PostUserTrackingAction(const G4Track* aTrack) {
    278     if (aTrack->GetParentID() == 0) {
    279         // this is the primary particle
    280         const G4ThreeVector& pos = aTrack->GetPosition();
    281         LogDebug << "!!!Primary Track " << aTrack->GetTrackID() << ": ";
    282         LogDebug << "+ " << pos.x() << " " << pos.y() << " " << pos.z() << std::endl;
    283         LogDebug << "+ " << aTrack->GetKineticEnergy() << std::endl;
    284     }
    285     G4TrackingManager* tm = G4EventManager::GetEventManager()
    286                                             -> GetTrackingManager();
    287     G4TrackVector* secondaries = tm->GimmeSecondaries();
    288     if(secondaries)
    289     {
    290         NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    291 
    292         if (!info) {
    293             return;
    294         }
    295 
    296         size_t nSeco = secondaries->size();
    297         if(nSeco>0)
    298         {
    299             for(size_t i=0;i<nSeco;i++)
    300             {
    301                 // make sure the secondaries' track info is empty
    302                 // if already attached track info, skip it.
    303                 if ((*secondaries)[i]->GetUserInformation()) {
    304                     LogDebug << "The secondary already has user track info. skip creating new one" << std::endl;
    305                     continue;
    306                 }
    307                 NormalTrackInfo* infoNew = new NormalTrackInfo(info);

             33 NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
             34 {
             35     originalTrackID = aTrackInfo->originalTrackID;
             36     tracedAncestors = aTrackInfo->tracedAncestors; 
             37 
             38     // phys
             39     phys_michael_electron = 0;
             40     phys_neutron_capture = 0;
             41     
             42     from_cerenkov = aTrackInfo->from_cerenkov;
             43     is_reemission = aTrackInfo->is_reemission; 
             44     
             45     m_op_is_original_op = false;
             46     m_op_start_time = aTrackInfo->m_op_start_time;
             47 
             48     pos_at_boundary = aTrackInfo->pos_at_boundary;
             49 }

             /// from_cerenkov and is_reemission are passed from a track to its secondaries 
             /// (Opticks equivalent is checking the or-wise accumulated photon flag)


    308                 // cerekov tag
    309                 if ((*secondaries)[i]->GetCreatorProcess()
    310                     and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
    311                     infoNew->setFromCerenkov();
    312                     LogDebug << "### infoNew->setFromCerenkov()" << std::endl;
    313                 }
    314                 // reemission tag
    315                 // + parent track is an OP
    316                 // + secondary is also an OP
    317                 // + the creator process is Scintillation
    318                 if (aTrack->GetDefinition()->GetParticleName() == "opticalphoton"
    319                     and (*secondaries)[i]->GetDefinition()->GetParticleName() == "opticalphoton"
    320                     and (*secondaries)[i]->GetCreatorProcess()->GetProcessName() == "Scintillation") {
    321                     infoNew->setReemission();
    322                 }
    323                 // original optical photon tag
    324                 if (aTrack->GetDefinition()->GetParticleName() != "opticalphoton"
    325                     and (*secondaries)[i]->GetDefinition()->GetParticleName() == "opticalphoton"
    326                     ) {
    327                     LogDebug << "------ original OP" << std::endl;
    328                     infoNew->setOriginalOP();
    329                 }

              ///  originalOP is the first optical photon coming from a non-optical photon
              ///  this does not get passed from a track to its secondaries so the Opticks 
              ///  equivalent is checking that the REEMISSION flag is not set in the photon flags 
              ///  because Opticks always starts from first photons and does not form secondaries.

    330 
    331                 // save parent track info
    332                 infoNew->setParentName(aTrack->GetDefinition()->GetParticleName());

              ///   you gotta be joking : a million names 

    333 
    334                 (*secondaries)[i]->SetUserInformation(infoNew);
    335             }
    336         }
    337     }
    338 }


::

    epsilon:offline blyth$ jcv NormalTrackInfo
    2 files to edit
    ./Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh
    ./Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc


NormalTrackInfo dupes info from parent NormalTrackInfo::


     09 NormalTrackInfo::NormalTrackInfo()
     10 {       
     11     originalTrackID = 0;
     12     // phys
     13     phys_michael_electron = 0; 
     14     phys_neutron_capture = 0;
     15     from_cerenkov =false;
     16     is_reemission =false;
     17 }       
     18 
     19 NormalTrackInfo::NormalTrackInfo(const G4Track* aTrack)
     20 {       
     21     originalTrackID = aTrack->GetTrackID();
     22         
     23     // phys
     24     phys_michael_electron = 0;
     25     phys_neutron_capture = 0;
     26     from_cerenkov =false;
     27     is_reemission =false;
     28         
     29     m_op_is_original_op = false;
     30     m_op_start_time = 0;
     31 }
     32         
     33 NormalTrackInfo::NormalTrackInfo(const NormalTrackInfo* aTrackInfo)
     34 {
     35     originalTrackID = aTrackInfo->originalTrackID;
     36     tracedAncestors = aTrackInfo->tracedAncestors; 
     37 
     38     // phys
     39     phys_michael_electron = 0;
     40     phys_neutron_capture = 0;
     41     
     42     from_cerenkov = aTrackInfo->from_cerenkov;
     43     is_reemission = aTrackInfo->is_reemission; 
     44     
     45     m_op_is_original_op = false;
     46     m_op_start_time = aTrackInfo->m_op_start_time;
     47 
     48     pos_at_boundary = aTrackInfo->pos_at_boundary;
     49 }



Duplicating OriginalOPStartTime : need to collect the as generated p.time before bounce loop
-----------------------------------------------------------------------------------------------

g4-cls G4Cerenkov::

    358       G4double delta = rand * aStep.GetStepLength();
    359 
    360       G4double deltaTime = delta / (pPreStepPoint->GetVelocity()+
    361                                       rand*(pPostStepPoint->GetVelocity()-
    362                                             pPreStepPoint->GetVelocity())*0.5);
    363 
    364       G4double aSecondaryTime = t0 + deltaTime;
    365 

Opticks duplicates with generate_cerenkov_photon.

So just need to grab a copy of p.time prior to the bounce loop.








Investigate geocache to find an Opticks equivalent for this
-------------------------------------------------------------

::

    # Opticks::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.e7b204fa62c028f3d23c102bc554dcbb
    export OPTICKS_IDPATH=/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/e7b204fa62c028f3d23c102bc554dcbb/1

in ~/.opticks_config make sure have the desired OPTICKS_KEY::

    144 ok_juno0(){
    145    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.e7b204fa62c028f3d23c102bc554dcbb
    146    export OPTICKS_KEYDIR=$(geocache-keydir)  # derived from OPTICKS_KEY
    147    export GC=/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/e7b204fa62c028f3d23c102bc554dcbb/1
    148    export OPTICKS_DEFAULT_TARGET=62590  # po
    149 }
    150 
    151 ok_juno(){
    152    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.e7b204fa62c028f3d23c102bc554dcbb
    153 }
    154 
    155 ok_dyb(){
    156   export OPTICKS_KEY=OKX4Test.X4PhysicalVolume.World0xc15cfc00x40f7000_PV.5aa828335373870398bf4f738781da6c
    157   export OPTICKS_KEYDIR=$(geocache-keydir)  # derived from OPTICKS_KEY
    158   export OPTICKS_DEFAULT_TARGE=3154
    159 }
    160 
    161 #ok_dyb
    162 ok_juno



Identity quad including Node index of the next boundary available for every rtTrace in the cu/generate.cu bounce loop::

    [blyth@localhost ggeo]$ GNodeLibTest --pvname pAcylic
    2020-12-08 01:16:29.768 INFO  [259241] [BOpticksKey::SetKey@77]  spec DetSim0Svc.X4PhysicalVolume.pWorld.e7b204fa62c028f3d23c102bc554dcbb
    ...
    2020-12-08 01:16:30.109 INFO  [259241] [GNodeLib::dumpVolumes@816] targetted volumes(**) OR volumes with extent greater than 5000 mm 
     **       0                                                                lWorld        ce   0.000   0.000   0.000 60000.000 
              1                                                              lTopRock        ce   0.000   0.000 32550.000 27000.000 
              2                                                              lExpHall        ce   0.000   0.000 31050.000 24000.000 
              7                                                                lAirTT        ce   0.000   0.000 25952.000 24000.000 
          65717                                                              lBtmRock        ce   0.000   0.000 -1500.000 24750.000 
          65718                                                           lPoolLining        ce   0.000   0.000  -1.500 21753.000 
          65719                                                       lOuterWaterPool        ce   0.000   0.000   0.000 21750.000 
          65720                                                        lReflectorInCD        ce   0.000   0.000 849.015 20901.016 
          65721                                                           lInnerWater        ce   0.000   0.000 850.015 20900.016 
          65722                                                              lAcrylic        ce   0.000   0.000   0.009 17820.008 
          65723                                                               lTarget        ce   0.000   0.000  60.007 17760.008 
    2020-12-08 01:16:30.187 INFO  [259241] [test_getNodeIndicesForPVName@130]  pvname pAcylic
    2020-12-08 01:16:30.187 INFO  [259241] [GNodeLib::dumpNodes@297] test_getNodeIndicesForPVName nidxs.size 1
     i     0 nidx  65722 pv                                            pAcylic lv                                           lAcrylic       ce   0.000   0.000   0.009 17820.008 
    [blyth@localhost ggeo]$ 


    [blyth@localhost ggeo]$ GNodeLibTest --pvname pInnerWater
    ...
    2020-12-08 01:18:46.088 INFO  [262624] [test_getNodeIndicesForPVName@130]  pvname pInnerWater
    2020-12-08 01:18:46.089 INFO  [262624] [GNodeLib::dumpNodes@297] test_getNodeIndicesForPVName nidxs.size 1
     i     0 nidx  65721 pv                                        pInnerWater lv                                        lInnerWater       ce   0.000   0.000 850.015 20900.016 


Manual way is 1-based::

     O ; kcd ; grep -n pAcylic -C 5  GNodeLib/PVNames.txt    ## CAUTION 1-based 

    65718-pBtmRock
    65719-pPoolLining
    65720-pOuterWaterPool
    65721-pCentralDetector
    65722-pInnerWater
    65723:pAcylic
    65724-pTarget
    65725-lSJCLSanchor_phys
    65726-lSJCLSanchor_phys
    65727-lSJFixture_phys
    65728-lSJFixture_phys
    [blyth@localhost GNodeLib]$ 

Hmm can implement another target volume "--marktarget pAcylic" 
that gets converted into a nodeIndex and passed to Opticks.

Use python3 as that has numpy, unlike the junoenv python2.7::

    [blyth@localhost ana]$ python3 blib.py 
     nbnd  35 nmat  39 nsur  34 
      0 :   1 : Galactic///Galactic 
      1 :   2 : Galactic///Rock 
      2 :   3 : Rock///Air 
      3 :   4 : Air///Air 
      4 :   5 : Air///LS 
      5 :   6 : Air///Steel 
      6 :   7 : Air///Tyvek 
      7 :   8 : Air///Aluminium 
      8 :   9 : Aluminium///Adhesive 
      9 :  10 : Adhesive///TiO2Coating 
     10 :  11 : TiO2Coating///Scintillator 
     11 :  12 : Rock///Tyvek 
     12 :  13 : Tyvek//VETOTyvekSurface/vetoWater 
     13 :  14 : vetoWater/CDTyvekSurface//Tyvek 
     14 :  15 : Tyvek///Water 
     15 :  16 : Water///Acrylic 
     16 :  17 : Acrylic///LS 
     17 :  18 : LS///Acrylic 
     18 :  19 : LS///PE_PA 
     19 :  20 : Water///Steel 
     20 :  21 : Water///PE_PA 
     21 :  22 : Water///Water 
     22 :  23 : Water///Pyrex 
     23 :  24 : Pyrex///Pyrex 
     24 :  25 : Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum 
     25 :  26 : Pyrex/NNVTMCPPMT_PMT_20inch_mirror_logsurf2/NNVTMCPPMT_PMT_20inch_mirror_logsurf1/Vacuum 
     26 :  27 : Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum 
     27 :  28 : Pyrex/HamamatsuR12860_PMT_20inch_mirror_logsurf2/HamamatsuR12860_PMT_20inch_mirror_logsurf1/Vacuum 
     28 :  29 : Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum 
     29 :  30 : Pyrex/PMT_3inch_absorb_logsurf2/PMT_3inch_absorb_logsurf1/Vacuum 
     30 :  31 : Water///LS 
     31 :  32 : Water/Steel_surface/Steel_surface/Steel 
     32 :  33 : vetoWater///Water 
     33 :  34 : Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum 
     34 :  35 : Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum 
    [blyth@localhost ana]$ 

Opticks boundaries are defined in terms of the names of materials and surfaces.  That 
might not be specific enough to match what is needed.::

    [blyth@localhost ~]$ jgr pAcylic
    ./Simulation/DetSimV2/CentralDetector/src/PrototypeConstruction.cc:                                     "pAcylic",       // its name
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:                                     "pAcylic",       // its name
    ./Simulation/DetSimV2/CentralDetector/src/DetSim2Construction.cc:            "pAcylic",       // its name
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        && prepoint->GetPhysicalVolume()->GetName() == "pAcylic"
    ./Doc/oum/source/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + pAcylic : 1
    ./Doc/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + pAcylic : 1
    [blyth@localhost offline]$ 

Use of boundary indices is a basic Opticks optimization that allows getting 
everything from the texture. So the Opticks native way to is to check the signed 1-based boundary integer.::

    306 __device__ void propagate_at_boundary_geant4_style( Photon& p, State& s, curandState &rng)
    307 {
    308     // see g4op-/G4OpBoundaryProcess.cc annotations to follow this
    309 
    310     const float n1 = s.material1.x ;
    311     const float n2 = s.material2.x ;
    312     const float eta = n1/n2 ;


::

    281 unsigned GVolume::getShapeIdentity() const
    282 {
    283     return OpticksShape::Encode( getMeshIndex(), getBoundary() );
    284 }


    In [1]: i = np.load("all_volume_identity.npy")

    In [2]: i
    Out[2]: 
    array([[       0,        0,  3670016,        0],
           [       1,        1,   786433,        0],
           [       2,        2,   720898,        0],
           ...,
           [  316323, 67723011,  3276823,        0],
           [  316324, 67723012,  3145761,    45612],
           [  316325, 67723013,  3211298,        0]], dtype=uint32)

    In [3]: i.shape
    Out[3]: (316326, 4)

    In [4]: i[:,2] & 0xffff
    Out[4]: array([ 0,  1,  2, ..., 23, 33, 34], dtype=uint32)

    In [5]: b = i[:,2] & 0xffff


::

    [blyth@localhost GNodeLib]$ ~/opticks/ana/boundary_counts.py 
     0 :      1 : Galactic///Galactic 
     1 :      2 : Galactic///Rock 
     2 :      1 : Rock///Air 
     3 :    191 : Air///Air 
     4 :      1 : Air///LS 
     5 :      1 : Air///Steel 
     6 :      1 : Air///Tyvek 
     7 :    504 : Air///Aluminium 
     8 :    504 : Aluminium///Adhesive 
     9 :  32256 : Adhesive///TiO2Coating 
    10 :  32256 : TiO2Coating///Scintillator 
    11 :      1 : Rock///Tyvek 
    12 :      1 : Tyvek//VETOTyvekSurface/vetoWater 
    13 :      1 : vetoWater/CDTyvekSurface//Tyvek 
    14 :      1 : Tyvek///Water 
    15 :  20660 : Water///Acrylic         ##### -> +(15+1)
    16 :      1 : Acrylic///LS 
    17 :     46 : LS///Acrylic 
    18 :      8 : LS///PE_PA 
    19 :  27370 : Water///Steel 
    20 :     56 : Water///PE_PA 
    21 :  43213 : Water///Water 
    22 :  45612 : Water///Pyrex 
    23 :  20012 : Pyrex///Pyrex 
    24 :  12612 : Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum 
    25 :  12612 : Pyrex/NNVTMCPPMT_PMT_20inch_mirror_logsurf2/NNVTMCPPMT_PMT_20inch_mirror_logsurf1/Vacuum 
    26 :   5000 : Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum 
    27 :   5000 : Pyrex/HamamatsuR12860_PMT_20inch_mirror_logsurf2/HamamatsuR12860_PMT_20inch_mirror_logsurf1/Vacuum 
    28 :  25600 : Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum 
    29 :  25600 : Pyrex/PMT_3inch_absorb_logsurf2/PMT_3inch_absorb_logsurf1/Vacuum 
    30 :      1 : Water///LS 
    31 :      1 : Water/Steel_surface/Steel_surface/Steel 
    32 :   2400 : vetoWater///Water 
    33 :   2400 : Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum 
    34 :   2400 : Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum 
    [blyth@localhost GNodeLib]$ 


Sign of the boundary should be +ve as the ray direction is in the same hemisphere as the normal to the acrylic sphere surface::

     52 RT_PROGRAM void closest_hit_propagate()
     53 {
     54      const float3 n = normalize(rtTransformNormal(RT_OBJECT_TO_WORLD, geometricNormal)) ;
     55      float cos_theta = dot(n,ray.direction);
     56 
     57      prd.distance_to_boundary = t ;   // standard semantic attrib for this not available in raygen, so must pass it
     58 
     59      unsigned boundaryIndex = ( instanceIdentity.z & 0xffff ) ;
     60      prd.boundary = cos_theta < 0.f ? -(boundaryIndex + 1) : boundaryIndex + 1 ;
     61      prd.identity = instanceIdentity ;
     62      prd.surface_normal = cos_theta > 0.f ? -n : n ;


Loadsa Water///Acrylic only one Acrylic///LS 

Can very efficiently capture position at which photons exit the LS, but not so easy 
to capture the position where photons exit pAcylic and enter pInnerWater as that 
cannot be done from the boundary alone.  Actually it is not difficult just need to check identity.x (nodeIndex)

It would seem to me that the LS exit point is more fundamental anyhow ? Yes : but need to try to 
duplicate initially and its easily changed.


Adding GBndLib::getBoundary
-----------------------------

::

      GBndLibTest --boundary Water///Acrylic


      GBndLibTest --boundary Acrylic///LS
      GBndLibTest --boundary -Acrylic///LS


      33 : Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
      34 : Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum

::
 
    GBndLibTest: /home/blyth/opticks/ggeo/GPropertyLib.cc:399: unsigned int GPropertyLib::getIndex(const char*): Assertion `isClosed() && " must close the lib before the indices can be used, as preference sort order may be applied at the close"' failed.

    (gdb) bt
    #3  0x00007ffff42f8252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007ffff7abca38 in GPropertyLib::getIndex (this=0x639b60, shortname=0x737ef8 "Acrylic") at /home/blyth/opticks/ggeo/GPropertyLib.cc:399
    #5  0x00007ffff7ae074b in GBnd::init (this=0x7fffffff9cc0, flip_=false) at /home/blyth/opticks/ggeo/GBnd.cc:70
    #6  0x00007ffff7ae0406 in GBnd::GBnd (this=0x7fffffff9cc0, spec_=0x62f598 "Acrylic///LS", flip_=false, mlib_=0x639b60, slib_=0x6b7850, dbgbnd_=false) at /home/blyth/opticks/ggeo/GBnd.cc:35
    #7  0x00007ffff7ae31d8 in GBndLib::getBoundary (this=0x6384b0, spec=0x62f598 "Acrylic///LS") at /home/blyth/opticks/ggeo/GBndLib.cc:394
    #8  0x0000000000403d58 in test_getBoundary (blib=0x6384b0) at /home/blyth/opticks/ggeo/tests/GBndLibTest.cc:67
    #9  0x00000000004043c2 in main (argc=3, argv=0x7fffffffa918) at /home/blyth/opticks/ggeo/tests/GBndLibTest.cc:118
    (gdb) 

    2020-12-08 03:25:27.130 INFO  [526] [GItemList::dump@265] names_
       0 : Galactic///Galactic
       1 : Galactic///Rock
       2 : Rock///Air
       3 : Air///Air
       4 : Air///LS
       5 : Air///Steel
       6 : Air///Tyvek
       7 : Air///Aluminium
       8 : Aluminium///Adhesive
       9 : Adhesive///TiO2Coating
      10 : TiO2Coating///Scintillator
      11 : Rock///Tyvek
      12 : Tyvek//VETOTyvekSurface/vetoWater
      13 : vetoWater/CDTyvekSurface//Tyvek
      14 : Tyvek///Water
      15 : Water///Acrylic
      16 : Acrylic///LS
      17 : LS///Acrylic
      18 : LS///PE_PA
      19 : Water///Steel
      20 : Water///PE_PA
      21 : Water///Water
      22 : Water///Pyrex
      23 : Pyrex///Pyrex
      24 : Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_logsurf2/NNVTMCPPMT_PMT_20inch_photocathode_logsurf1/Vacuum
      25 : Pyrex/NNVTMCPPMT_PMT_20inch_mirror_logsurf2/NNVTMCPPMT_PMT_20inch_mirror_logsurf1/Vacuum
      26 : Pyrex/HamamatsuR12860_PMT_20inch_photocathode_logsurf2/HamamatsuR12860_PMT_20inch_photocathode_logsurf1/Vacuum
      27 : Pyrex/HamamatsuR12860_PMT_20inch_mirror_logsurf2/HamamatsuR12860_PMT_20inch_mirror_logsurf1/Vacuum
      28 : Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
      29 : Pyrex/PMT_3inch_absorb_logsurf2/PMT_3inch_absorb_logsurf1/Vacuum
      30 : Water///LS
      31 : Water/Steel_surface/Steel_surface/Steel
      32 : vetoWater///Water
      33 : Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
      34 : Pyrex/PMT_20inch_veto_mirror_logsurf2/PMT_20inch_veto_mirror_logsurf1/Vacuum
    2020-12-08 03:25:27.130 INFO  [526] [test_getBoundary@69]  spec -Acrylic///LS boundary 4294967295
    2020-12-08 03:25:27.130 INFO  [526] [test_getSignedBoundary@82]  spec -Acrylic///LS boundary -17
    [blyth@localhost ggeo]$ 
    [blyth@localhost ggeo]$ GBndLibTest --boundary -Acrylic///LS


::

    SLOW: tests taking longer that 15 seconds
      1  /1   Test #1  : OKG4Test.OKG4Test                             Child aborted***Exception:     16.61  
      2  /2   Test #2  : IntegrationTests.tboolean.box                 ***Failed                      18.22  


    FAILS:  4   / 444   :  Wed Dec  9 06:59:00 2020   
      2  /5   Test #2  : OKTest.OKTest                                 Child aborted***Exception:     14.39  
      1  /1   Test #1  : OKG4Test.OKG4Test                             Child aborted***Exception:     16.61  
      1  /2   Test #1  : G4OKTest.G4OKTest                             ***Exception: SegFault         13.39  
      2  /2   Test #2  : IntegrationTests.tboolean.box                 ***Failed                      18.22  
    [blyth@localhost optixrap]$ 

::

    2020-12-09 07:00:27.748 INFO  [269207] [OpSeeder::seedPhotonsFromGenstepsViaOptiX@174] SEEDING TO SEED BUF  
    2020-12-09 07:00:30.025 INFO  [269207] [OPropagator::prelaunch@195] 0 : (0;0,0) 
    2020-12-09 07:00:30.025 INFO  [269207] [BTimes::dump@177] OPropagator::prelaunch
                  validate000                 0.004872
                   compile000              7.00001e-06
                 prelaunch000                  2.25163
    2020-12-09 07:00:30.026 INFO  [269207] [OPropagator::launch@266] LAUNCH NOW   printLaunchIndex ( -1 -1 -1) -
    terminate called after throwing an instance of 'optix::Exception'
      what():  Unknown error (Details: Function "RTresult _rtContextLaunch2D(RTcontext, unsigned int, RTsize, RTsize)" caught exception: Encountered a CUDA error: cudaDriver().CuMemcpyDtoHAsync( dstHost, srcDevice, byteCount, hStream.get() ) returned (700): Illegal address)

    Program received signal SIGABRT, Aborted.
    0x00007fffec64b387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libselinux-2.5-14.1.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libxcb-1.13-1.el7.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) quit







