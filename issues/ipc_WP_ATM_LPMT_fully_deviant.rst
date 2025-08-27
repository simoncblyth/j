ipc_WP_ATM_LPMT_fully_deviant
=================================

overview
----------

After overhaul, getting GPU hits but no CPU ones from ipc.
The photons do not notice the PMT.
Something wrong with the Geant4 geometry ?




AtmPmtPosCylinder 
--------------------

::

    (ok) A[blyth@localhost junosw]$ find . -name '*.cc' -exec grep -H AtmPmtPosCylinder {} \;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:#include "AtmPmtPosCylinder.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    IDetElementPos* veto_atm_pmt_detelem_pos = new JUNO::Cylinder::AtmPmtPosCylinder(m_scope);
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:#include "AtmPmtPosCylinder.hh"
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::AtmPmtPosCylinder(Task* scope)
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::~AtmPmtPosCylinder() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::hasNext() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::next() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::initialize() {
    (ok) A[blyth@localhost junosw]$ 


::

    1374 void
    1375 LSExpDetectorConstruction::setupWP_PMTs() {
    1376 
    1377   //put veto pmts into water pool
    1378   IDetElement* glob_info = det_elem("GlobalGeomInfo");
    1379   G4double waterpool_r = glob_info->geom_info("WaterPool.R");
    1380   G4double waterpool_h = glob_info->geom_info("WaterPool.H");
    1381   G4double vetopmt_interval = 2*m;
    1382   IDetElementPos* veto_pmt_detelem_pos = 0;
    1383   if (m_veto_pmt_pos_mode == "CalMode") {
    1384       veto_pmt_detelem_pos = new JUNO::Cylinder::CalPositionCylinder(
    1385               waterpool_r,
    1386               waterpool_h,
    1387               pmt_det_veto->GetPMTRadius(),
    1388               pmt_det_veto->GetPMTHeight(),
    1389               vetopmt_interval);
    1390   } else if (m_veto_pmt_pos_mode == "FileMode") {
    1391    veto_pmt_detelem_pos = new JUNO::Ball::VetoPmtPosBall(m_scope);
    1392   }
    1393   assert (veto_pmt_detelem_pos);
    1394  std::cout << "WP PMT Position Mode: " << m_veto_pmt_pos_mode << std::endl;
    1395   // If the string m_veto_pmt_pos_mode is empty, don't place any PMTs.
    1396   if (m_veto_pmt_pos_mode.size()!=0) {
    1397       assert (veto_pmt_detelem_pos);
    1398       m_pmt_mother = "OuterWaterVeto";
    1399       bool veto_status = de_wp_det->inject(m_pmt_mother, pmt_det_veto, veto_pmt_detelem_pos);
    1400       assert (veto_status);
    1401   }
    1402 
    1403   // Atm PMT Veto in water pool  
    1404   if (m_veto_pmt_pos_mode.size()!=0) {
    1405     IDetElementPos* veto_atm_pmt_detelem_pos = new JUNO::Cylinder::AtmPmtPosCylinder(m_scope);
    1406     IPMTElement* mcppmt_pmt = dynamic_cast<IPMTElement*>(det_elem("NNVTMCPPMTManager/PMT_20inch"));
    1407     m_pmt_mother = "OuterWaterAtmVeto";
    1408     bool veto_status = de_wp_det->inject(m_pmt_mother, mcppmt_pmt, veto_atm_pmt_detelem_pos);
    1409     assert (veto_status);
    1410   }
    1411 }


::

    A[blyth@localhost junosw]$ find . -name '*.cc'  -exec grep -H OuterWaterVeto {} \;
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    if ( motherName == "lWaterPool" or motherName =="OuterWaterVeto" or motherName == "3inchInnerWater" or motherName == "20inchInnerWater") {
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      m_pmt_mother = "OuterWaterVeto";
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:| OuterWaterVeto   |  logicWaterPool  | kOFFSET_WP_PMT  |   true           |
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    } else if (motherName == "OuterWaterVeto") {
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    } else if (motherName == "OuterWaterVeto"){
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    if(motherName == "OuterWaterVeto") {
    A[blyth@localhost junosw]$ 

    A[blyth@localhost junosw]$ find . -name '*.cc'  -exec grep -H OuterWaterAtmVeto {} \;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    m_pmt_mother = "OuterWaterAtmVeto";
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    }else if (motherName == "OuterWaterAtmVeto") {
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    } else if (motherName == "OuterWaterAtmVeto") {
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    } else if (motherName == "OuterWaterAtmVeto") {
    A[blyth@localhost junosw]$ 



::

     161 bool
     162 WaterPoolConstruction::inject(std::string motherName, IDetElement* other, IDetElementPos* pos) {
     163     // = Outer Water Pool =
     164     // == CD ==
     165     // == Veto PMTs ==
     166     assert( theLV && logicWaterPool );
     167 
     168     G4LogicalVolume* mothervol = 0;
     169     G4int copyno = 0;
     170     bool is_20inch_pmt = false;
     171 
     172     if (motherName == "lWaterPool") {
     173         // place CD
     174         mothervol = logicWaterPool ;
     175     } else if (motherName == "OuterWaterVeto") {
     176         // place Veto PMTs
     177         mothervol = logicWaterPool ;
     178         copyno = kOFFSET_WP_PMT;
     179         is_20inch_pmt = true;
     180     }else if (motherName == "OuterWaterAtmVeto") {
     181         // place Atm PMTs
     182         mothervol = theLV ;
     183         copyno = kOFFSET_WP_ATM_LPMT;
     184         is_20inch_pmt = true;
     185     }
     186 
     187     if (not mothervol) {
     188         // don't find the volume.
     189         LogError << "Can't find the mother volume named " << motherName << std::endl;
     190         return false;
     191     }


Looks like another theLV bug::

    diff --git a/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc b/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    index 1f10b1f5..63eea363 100644
    --- a/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    +++ b/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    @@ -179,7 +179,7 @@ WaterPoolConstruction::inject(std::string motherName, IDetElement* other, IDetEl
             is_20inch_pmt = true;
         }else if (motherName == "OuterWaterAtmVeto") {
             // place Atm PMTs
    -        mothervol = theLV ;
    +        mothervol = logicWaterPool ;
             copyno = kOFFSET_WP_ATM_LPMT;
             is_20inch_pmt = true;
         }








shakedown
-----------

Before instancing,  ipcv::

    250     elif [ "$TEST" == "WP_ATM_LPMT" ]; then
    251 
    252        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    253        opticks_input_photon=SideZX_X300_100k_f8.npy
    254        opticks_input_photon_frame=PMT_20inch_pmt_solid_head:7:-2   ## EXPECTING TO HIT MOSTLY pmtid:52402 phi:179.25 
    255        observation="one of the 12*29 = 348"
    256        #
    257        #  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPATMLPMT.csv
    258        #  7 52402,1,0,4,1,3,2,0,1185,2,-21078.2,275.9287,20163,90,179.25,PA1801-1022,NNVT
    259        #   AT FAR -ve X POINT TOWARDS +X (APPROXIMATELY) 
    260 


After instancing, ipcv::

    250     elif [ "$TEST" == "WP_ATM_LPMT" ]; then
    251 
    252        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    253 
    254        ## BEFORE INSTANCING THE 348
    255        ##opticks_input_photon=SideZX_X300_100k_f8.npy
    256        ##opticks_input_photon_frame=PMT_20inch_pmt_solid_head:7:-2   ## EXPECTING TO HIT MOSTLY pmtid:52402 phi:179.25 
    257 
    258        ## AFTER INSTANCING THE 348
    259        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    260        opticks_input_photon_frame=PMT_20inch_pmt_solid_head:0:$(( 5 + 2 ))   ## EXPECTING TO HIT MOSTLY pmtid:52402 phi:179.25 
    261        observation="one of the 12*29 = 348"
    262        #
    263        #  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPATMLPMT.csv
    264        #  7 52402,1,0,4,1,3,2,0,1185,2,-21078.2,275.9287,20163,90,179.25,PA1801-1022,NNVT
    265        #   AT FAR -ve X POINT TOWARDS +X (APPROXIMATELY) 



Before instancing, ipc::

    //qsim::propagate_at_surface_CustomART pidx   96365 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96366 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96367 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96368 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96369 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96371 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96372 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96374 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96376 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96377 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96378 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96379 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96380 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96381 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96382 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96383 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx    4484 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    2025-08-25 16:41:59.914 INFO  [2340397] [QEvent::gatherPhoton@647] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc
                                     ProcessHits_count              0              0.000000    /M 
                                      ProcessHits_true              0              0.000000    /M 
                                     ProcessHits_false              0              0.000000    /M 
                                     SaveNormHit_count              0              0.000000    /M 
                                     SaveMuonHit_count              0              0.000000    /M 


After instancing, ipc::

    //qsim::propagate_at_surface_CustomART pidx   96966 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96967 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96968 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96969 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96970 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96971 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96972 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96973 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96974 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96975 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96976 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96978 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96979 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96980 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96981 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96982 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96983 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96984 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96985 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96986 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96987 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96988 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96989 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96990 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96991 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96864 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96865 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96866 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96867 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96868 lpmtid 52402 : ERROR UNEXPECTED LPMTID : NAN_ABORT 


After overhaul, get GPU hits but no CPU ones, ipc::

    2025-08-26 17:19:56.482 INFO  [3782458] [QSim::simulate@450]    0 : sslice {       0,       1,         0,    100000}  0.100000
    2025-08-26 17:19:56.537 INFO  [3782458] [QEvent::gatherPhoton@647] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc
                                     ProcessHits_count              0              0.000000    /M 
                                      ProcessHits_true              0              0.000000    /M 
                                     ProcessHits_false              0              0.000000    /M 
                                     SaveNormHit_count              0              0.000000    /M 
                                     SaveMuonHit_count              0              0.000000    /M 
                                             EPH_UNSET              0              0.000000    /M 
                                              EPH_NDIS              0              0.000000    /M 
                                              EPH_NOPT              0              0.000000    /M 
                                             EPH_NEDEP              0              0.000000    /M 
                                            EPH_NBOUND              0              0.000000    /M 
                                             EPH_NPROC              0              0.000000    /M 
                                           EPH_NDETECT              0              0.000000    /M 
                                           EPH_NDECULL              0              0.000000    /M 
                                            EPH_YMERGE              0              0.000000    /M 
                                             EPH_YSAVE              0              0.000000    /M 
                                          EPH_SAVENORM              0              0.000000    /M 
                                          EPH_SAVEMUON              0              0.000000    /M 

                Initialize_G4HCofThisEvent_opticksMode              3              0.000003    /M 
                      Initialize_G4HCofThisEvent_count              1              0.000001    /M 
                           EndOfEvent_Simulate_eventID              0              0.000000    /M 
                             EndOfEvent_Simulate_count              1              0.000001    /M 

                          EndOfEvent_Simulate_EGPU_hit          29165              0.029165    /M 
                     EndOfEvent_hitCollection_entries0              0              0.000000    /M 
                     EndOfEvent_hitCollection_entries1              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries1          29165              0.029165    /M 

                      EndOfEvent_Simulate_merged_count              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_count          29165              0.029165    /M 
                        SUM_merged_count_savehit_count          29165              0.029165    /M 

                      EndOfEvent_Simulate_merged_total              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_total          29165              0.029165    /M 
                        SUM_merged_total_savehit_total          29165              0.029165    /M 



    SABHit  a_nhit : (   29165 +-  170 )  b_nhit:(        0 +-    0 )  a/b: (  0.000 +-  0.000 )  b/a: (  0.000 +-  0.000)  [assume uncorr.]


        <pre class="mypretiny">
        [sseq_index_ab::desc  [CHI2 <span class="r">  sum  1441.8837 ndf  1.0000 sum/ndf  1441.8837 </span> ]
        TO SA                                                                                            :      -1  98075 :     0.0000 : N :      -1      0 : AZERO C2EXC  
        TO BT SA                                                                                         :   32372     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
        TO BT EC                                                                                         :   28779     -1 :     0.0000 : N :       5     -1 : BZERO C2EXC  
        TO BT BR BT SA                                                                                   :    8429     -1 :     0.0000 : N :       1     -1 : BZERO C2EXC  
        TO BT BT SR SA                                                                                   :    6409     -1 :     0.0000 : N :   10387     -1 : BZERO C2EXC  
        TO BT BT SA                                                                                      :    4649     -1 :     0.0000 : N :    8505     -1 : BZERO C2EXC  
        TO BT BT SR BT BT SA                                                                             :    3771     -1 :     0.0000 : N :   20278     -1 : BZERO C2EXC  
        TO AB                                                                                            :     182   1925 :  1441.8837 : Y :      25    102 : <span class="r">DEVIANT</span>   
        TO BT EX                                                                                         :    1902     -1 :     0.0000 : N :       4     -1 : BZERO C2EXC  
        TO BT BR BT AB                                                                                   :    1471     -1 :     0.0000 : N :     725     -1 : BZERO C2EXC  
        TO BT BT SR BR SR SA                                                                             :    1239     -1 :     0.0000 : N :   21065     -1 : BZERO C2EXC  
        TO BT BT SR BR SA                                                                                :    1012     -1 :     0.0000 : N :   20287     -1 : BZERO C2EXC  
        TO BT BT SR SR SA                                                                                :     901     -1 :     0.0000 : N :   10418     -1 : BZERO C2EXC  
        TO BT BT SR BT BT AB                                                                             :     875     -1 :     0.0000 : N :   20219     -1 : BZERO C2EXC  
        TO BR SA                                                                                         :     667     -1 :     0.0000 : N :      14     -1 : BZERO C2EXC  
        TO BT BT SR SR SR SA                                                                             :     408     -1 :     0.0000 : N :   10351     -1 : BZERO C2EXC  
        TO BT BT SR BR SR SR SA                                                                          :     332     -1 :     0.0000 : N :   22895     -1 : BZERO C2EXC  
        TO BT AB                                                                                         :     326     -1 :     0.0000 : N :     227     -1 : BZERO C2EXC  
        TO BT BT SR SR BT BT SA                                                                          :     301     -1 :     0.0000 : N :   17085     -1 : BZERO C2EXC  
        TO BT BT SR BR SR BT BT SA                                                                       :     263     -1 :     0.0000 : N :   21174     -1 : BZERO C2EXC  
        TO BT BT SR BR SR SR BT BT SA                                                                    :     229     -1 :     0.0000 : N :   22765     -1 : BZERO C2EXC  
        TO BT BT SR SR SR BT BT SA                                                                       :     186     -1 :     0.0000 : N :   12231     -1 : BZERO C2EXC  
        TO BT BT SR BR SR BT BT AB                                                                       :     172     -1 :     0.0000 : N :   22352     -1 : BZERO C2EXC  
        TO BT BR BT BT BT BT BT SA                                                                       :     167     -1 :     0.0000 : N :   49275     -1 : BZERO C2EXC  



After another WaterPoolConstruction theLV fix::

    2025-08-26 19:46:17.211 INFO  [4047497] [QEvent::gatherPhoton@647] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc
                                     ProcessHits_count         237515              0.237515    /M 
                                      ProcessHits_true          28909              0.028909    /M 
                                     ProcessHits_false         208606              0.208606    /M 
                                     SaveNormHit_count          28909              0.028909    /M 
                                     SaveMuonHit_count              0              0.000000    /M 
                                             EPH_UNSET              0              0.000000    /M 
                                              EPH_NDIS              0              0.000000    /M 
                                              EPH_NOPT              0              0.000000    /M 
                                             EPH_NEDEP         206257              0.206257    /M 
                                            EPH_NBOUND            416              0.000416    /M 
                                             EPH_NPROC              0              0.000000    /M 
                                           EPH_NDETECT              0              0.000000    /M 
                                           EPH_NDECULL           1933              0.001933    /M 
                                            EPH_YMERGE              0              0.000000    /M 
                                             EPH_YSAVE              0              0.000000    /M 
                                          EPH_SAVENORM          28909              0.028909    /M 
                                          EPH_SAVEMUON              0              0.000000    /M 

                Initialize_G4HCofThisEvent_opticksMode              3              0.000003    /M 
                      Initialize_G4HCofThisEvent_count              1              0.000001    /M 
                           EndOfEvent_Simulate_eventID              0              0.000000    /M 
                             EndOfEvent_Simulate_count              1              0.000001    /M 

                          EndOfEvent_Simulate_EGPU_hit          29165              0.029165    /M 
                     EndOfEvent_hitCollection_entries0          28909              0.028909    /M 
                     EndOfEvent_hitCollection_entries1          28909              0.028909    /M 
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries1          29165              0.029165    /M 

                      EndOfEvent_Simulate_merged_count              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_count          29165              0.029165    /M 
                        SUM_merged_count_savehit_count          29165              0.029165    /M 

                      EndOfEvent_Simulate_merged_total              0              0.000000    /M 
                     EndOfEvent_Simulate_savehit_total          29165              0.029165    /M 
                        SUM_merged_total_savehit_total          29165              0.029165    /M 

    SProcessHits_EPH::NOTES
    ------------------------

    ProcessHits_count
    ProcessHits_true
    ProcessHits_false
        number of calls to *SProcessHits_EPH::add* and sub-counts where is_hit is true/false,
        done from junoSD_PMT_v2::ProcessHits

    SaveNormHit_count
    SaveMuonHit_count
        counts collected from junoSD_PMT_v2::SaveNormHit junoSD_PMT_v2::SaveMuonHit

    All 7 EndOfEvent_Simulate values are collected from junoSD_PMT_v2_Opticks::EndOfEvent_Simulate

    EndOfEvent_Simulate_EGPU_hit
        Opticks GPU num_hit returned from SEvt::GetNumHit_EGPU() immediately following G4CXOpticks::simulate call

    EndOfEvent_Simulate_merged_count
    EndOfEvent_Simulate_savehit_count
        The sum of merged_count and savehit_count should sum to EGPU_hit in opticksMode:1

    EndOfEvent_Simulate_merged_total
    EndOfEvent_Simulate_savehit_total
        The totals sum over all events

    EndOfEvent_hitCollection_entries0
    EndOfEvent_hitCollection_entries1
    EndOfEvent_hitCollectionAlt_entries0
    EndOfEvent_hitCollectionAlt_entries1
        entries into hitCollection and hitCollectionAlt before and after the
        call to junoSD_PMT_v2_Opticks::EndOfEvent.
        This is recorded from junoSD_PMT_v2::EndOfEvent.

        In all cases entries0 are expected to be zero with entries1
        for the active collection matching the savehit_count

        For opticksMode:1 only hitCollection should be active,
        it contains the GPU originated hits.

        For opticksMode:3 both hitCollection and hitCollectionAlt should
        be active with hitCollection containing CPU hits and
        hitCollectionAlt containing GPU hits.

    ]SProcessHits_EPH::desc

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 28909 hitCollectionAlt 29165 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           87.18700       87.18700     0.00000      
    DetSimAlg                1           3638.46094     3638.46094   0.07929      
    Sum of junotoptask       1           3725.87207     3725.87207   0.56184      
    #############################################################################



    SABHit  a_nhit : (   29165 +-  170 )  b_nhit:(    28909 +-  170 )  a/b: (  1.009 +-  0.012 )  b/a: (  0.991 +-  0.012)  [assume uncorr.]


    ]----- repr(abh) 
    PICK=A MODE=3  ~/j/jtds/jtds.sh 
    INFO:__main__:a:sevt has sframe giving _W2M 
    W2M_OVERRIDE (from manual INST_FRAME, no longer typical)
     None
    _W2M(from a.f.sframe.w2m, now standard)
     [[    0.        0.013     1.        0.   ]
     [   -0.        1.       -0.013     0.   ]
     [   -1.       -0.        0.        0.   ]
     [20163.        0.    21080.004     1.   ]]
    W2M
     [[    0.        0.013     1.        0.   ]
     [   -0.        1.       -0.013     0.   ]
     [   -1.       -0.        0.        0.   ]
     [20163.        0.    21080.004     1.   ]]
    transform gpos (from photon or hit array) to lpos using W2M : ie into target frame : GLOBAL 0 
    transform gpoi (from record array) to lpoi using W2M : ie into target frame : GLOBAL 0 
    pvplt_plotter WSIZE:array([2560, 1440])
    add_points green for the upoi : record points 
    add_points red  for the upos : photon/hit points 

    In [1]:                                                                                                                                                                                                                                            
    Do you really want to exit ([y]/n)? y
    /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh - using externally configured GEOM J25_4_0_opticks_Debug
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              FOLD : /tmp/blyth/opticks/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
       sseq_index_ab__desc_NUM_MAX :  
        sseq_index_ab__desc_HISWID :  
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_WP_ATM_LPMT/A000 
                             BFOLD : /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_WP_ATM_LPMT/B000 
    [sseq_index_test.cc
    a_path $AFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_WP_ATM_LPMT/A000/seq.npy a_seq (100000, 2, 2, )
    b_path $BFOLD/seq.npy /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_WP_ATM_LPMT/B000/seq.npy b_seq (100000, 2, 2, )
    sseq_index_test__DEBUG:0
     t0 1756209669970002
     t1 1756209669980529 (t1 - t0)    10527 0.010527
     t2 1756209669990913 (t2 - t1)    10384 0.010384
     t3 1756209669991685 (t3 - t2)      772 0.000772

    .. raw:: html

        <pre class="mypretiny">
        [sseq_index_ab::desc  [CHI2 <span class="r">  sum    90.2123 ndf 79.0000 sum/ndf     1.1419 </span> ]
        TO BT SA                                                                                         :   32372  32402 :     0.0139 : Y :       0      1 :   
        TO BT EC                                                                                         :   28779  28484 :     1.5197 : Y :       5      9 :   
        TO BT BR BT SA                                                                                   :    8429   8757 :     6.2600 : Y :       1      2 :   
        TO BT BT SR SA                                                                                   :    6409   6293 :     1.0594 : Y :   10387  10411 :   
        TO BT BT SA                                                                                      :    4649   4770 :     1.5544 : Y :    8505   8573 :   
        TO BT BT SR BT BT SA                                                                             :    3771   3818 :     0.2911 : Y :   20278  20223 :   
        TO BT EX                                                                                         :    1902   1905 :     0.0024 : Y :       4     43 :   
        TO BT BR BT AB                                                                                   :    1471   1503 :     0.3443 : Y :     725    498 :   
        TO BT BT SR BR SR SA                                                                             :    1239   1177 :     1.5911 : Y :   21065  21056 :   
        TO BT BT SR BR SA                                                                                :    1012    987 :     0.3127 : Y :   20287  20259 :   
        TO BT BT SR SR SA                                                                                :     901    931 :     0.4913 : Y :   10418  10409 :   
        TO BT BT SR BT BT AB                                                                             :     875    911 :     0.7256 : Y :   20219  20237 :   
        TO BR SA                                                                                         :     667    574 :     6.9694 : Y :      14      0 :   
        TO BT BT SR SR SR SA                                                                             :     408    346 :     5.0981 : Y :   10351  10341 :   
        TO BT BT SR BR SR SR SA                                                                          :     332    353 :     0.6438 : Y :   22895  21011 :   
        TO BT AB                                                                                         :     326    349 :     0.7837 : Y :     227    287 :   
        TO BT BT SR BR SR BT BT SA                                                                       :     263    308 :     3.5464 : Y :   21174  21140 :   
        TO BT BT SR SR BT BT SA                                                                          :     301    291 :     0.1689 : Y :   17085  17092 :   
        TO BT BT SR BR SR SR BT BT SA                                                                    :     229    233 :     0.0346 : Y :   22765  22739 :   
        TO BT BT SR SR SR BT BT SA                                                                       :     186    204 :     0.8308 : Y :   12231  12227 :   
        TO AB                                                                                            :     182    189 :     0.1321 : Y :      25     58 :   
        TO BT BT SR BR SR BT BT AB                                                                       :     172    172 :     0.0000 : Y :   22352  21308 :   
        TO BT BR BT BT BT BT BT SA                                                                       :     167    166 :     0.0030 : Y :   49275  49236 :   
        TO BT BT SR BR SR BR SR SA                                                                       :     156    142 :     0.6577 : Y :   21052  21251 :   
        TO BT BR BT BT BT SA                                                                             :     114    147 :     4.1724 : Y :   49132  49135 :   
        TO BT BR BT BT BT BT BT EC                                                                       :     112    141 :     3.3241 : Y :   50725  49263 :   
        TO BT BT SR BT BT BT BT BT BT SA                                                                 :      98    121 :     2.4155 : Y :   35365  35370 :   
        TO BT BT SR SR SR BR SA                                                                          :      92    117 :     2.9904 : Y :   12205  12249 :   
        TO BT BR BT BT SR BT SA                                                                          :     116    115 :     0.0043 : Y :   91663  91651 :   
        TO BT BT SR BR SR BR SA                                                                          :     114    115 :     0.0044 : Y :   21110  21396 :   
        TO BT BT SR SR SR SR SA                                                                          :     113    114 :     0.0044 : Y :   10345  10398 :   
        TO BT BT SR SR BR SR SR SA                                                                       :      96    113 :     1.3828 : Y :   18306  18286 :   







Have changed the window and overhauled s_pmt.h SPMT.h etc for WP_ATM_LPMT WP_WAL_PMT::

    1813     // formerly excluded Custom4 hits onto WP PMTs see ~/j/issues/jok-tds-mu-running-NOT-A-SENSOR-warnings.rst
    1814     if(lpmtid < s_pmt::OFFSET_CD_LPMT || lpmtid >= s_pmt::OFFSET_WP_PMT_END )
    1815     {
    1816         flag = NAN_ABORT ;
    1817 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1818         printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d : ERROR UNEXPECTED LPMTID : NAN_ABORT \n", ctx.pidx, lpmtid );
    1819 #endif
    1820         return BREAK ;
    1821     }
    1822 


s_pmt.h::

 68         OFFSET_WP_PMT      = 50000,
 69         OFFSET_WP_PMT_END  = 52400,
 70         OFFSET_WP_ATM_LPMT = 52400,
 71         OFFSET_WP_ATM_LPMT_END = 52748,
 72         OFFSET_WP_ATM_MPMT     = 53000,
 73         OFFSET_WP_ATM_MPMT_END = 53600,
 74         OFFSET_WP_WAL_PMT      = 54000,
 75         OFFSET_WP_WAL_PMT_END  = 54005
 76     };


WIP, extend SPMT and QPMT testing to the 348+5::

    1813     // formerly excluded Custom4 hits onto WP PMTs see ~/j/issues/jok-tds-mu-running-NOT-A-SENSOR-warnings.rst
    1814     if(lpmtid < s_pmt::OFFSET_CD_LPMT || lpmtid >= s_pmt::OFFSET_WP_PMT_END )
    1815     {
    1816         flag = NAN_ABORT ;
    1817 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1818         printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d : ERROR UNEXPECTED LPMTID : NAN_ABORT \n", ctx.pidx, lpmtid );
    1819 #endif
    1820         return BREAK ;
    1821     }
    1822 
    1823 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1824     if( ctx.pidx_debug )
    1825     printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d wl %8.4f mct %8.4f dpcmn %8.4f pmt %p pre-ATQC \n",
    1826            ctx.pidx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, pmt );
    1827 #endif
    1828 
    1829     float ATQC[4] = {} ;
    1830 
    1831 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1832     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ctx.pidx, ctx.pidx_debug );
    1833 #else
    1834     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    1835 #endif
    1836 
    1837 





Before instancing::

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum  2119.0019 ndf  1.0000 sum/ndf  2119.0019 </span> ]
    TO SA                                                                                            :      -1  97878 :     0.0000 : N :      -1      0 : AZERO C2EXC  
    TO BT NA                                                                                         :   92737     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
    TO BR SA                                                                                         :    6539     -1 :     0.0000 : N :      24     -1 : BZERO C2EXC  
    TO AB                                                                                            :       1   2122 :  2119.0019 : Y :   93313     59 : <span class="r">DEVIANT</span>   
    TO BR AB                                                                                         :     412     -1 :     0.0000 : N :      16     -1 : BZERO C2EXC  
    TO BT AB                                                                                         :     272     -1 :     0.0000 : N :     239     -1 : BZERO C2EXC  
    TO BR BT BT BT BT BT BT EC                                                                       :       4     -1 :     0.0000 : N :    1029     -1 : C2EXC  
    TO BR BT BT BT BT BT BT BT SA                                                                    :       3     -1 :     0.0000 : N :     673     -1 : C2EXC  
    TO BR BT BT BT BT AB                                                                             :       2     -1 :     0.0000 : N :    1437     -1 : C2EXC  
    TO BR BT BT BT BT BT BR BT BT BT BT SA                                                           :       2     -1 :     0.0000 : N :    1512     -1 : C2EXC  
    TO BR BT BT BT BT BT BT SA                                                                       :       2     -1 :     0.0000 : N :    1023     -1 : C2EXC  
    TO BR BT BT BR BT BT SA                                                                          :       2     -1 :     0.0000 : N :     531     -1 : C2EXC  
    TO BR BT BT BT BT EC                                                                             :       2     -1 :     0.0000 : N :    1479     -1 : C2EXC  




After instancing::

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum  1441.8837 ndf  1.0000 sum/ndf  1441.8837 </span> ]
    TO BT NA                                                                                         :   98693     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
    TO SA                                                                                            :      -1  98075 :     0.0000 : N :      -1      0 : AZERO C2EXC  
    TO AB                                                                                            :     182   1925 :  1441.8837 : Y :      25    102 : <span class="r">DEVIANT</span>   
    TO BR SA                                                                                         :     667     -1 :     0.0000 : N :      14     -1 : BZERO C2EXC  
    TO BT AB                                                                                         :     326     -1 :     0.0000 : N :     227     -1 : BZERO C2EXC  
    TO BR AB                                                                                         :      48     -1 :     0.0000 : N :    1545     -1 : BZERO C2EXC  
    TO SC SA                                                                                         :      23     -1 :     0.0000 : N :     280     -1 : BZERO C2EXC  
    TO BR BT SR BT SA                                                                                :      14     -1 :     0.0000 : N :   92394     -1 : BZERO C2EXC  
    TO SC BT NA                                                                                      :      13     -1 :     0.0000 : N :    2775     -1 : BZERO C2EXC  





ssst.sh 
-----------

A side bounce off the PMT with no hits::

    //qsim::propagate_at_surface_CustomART pidx   96376 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96377 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96378 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96379 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96380 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96381 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96382 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96383 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx    4484 lpmtid -1 : ERROR UNEXPECTED LPMTID : NAN_ABORT 
 

Hmm qsim.h expects all PMT to be instanced ? But 29*12 = 348 is less than the default stree instancing cut of 500. 

    1760 /**
    1761 qsim::propagate_at_surface_CustomART
    1762 -------------------------------------
    1763 
    1764 lpmtid:-1
    1765    indicates "not-a-sensor", that occurring at this juncture would
    1766    indicate a sensor_identity issue as CustomART special surfaces
    1767    are expected to always have sensor identities
    1768 
    1769 
    1770 Where ctx.prd->identity() comes from ? Where is the "+ 1" done ?
    1771 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    1772 
    1773 1. SBT::collectInstances sets OptixInstance::instanceId from sqat4::get_IAS_OptixInstance_instanceId
    1774    aka "sensor_identifier"
    1775 
    1776 2. CSGFoundry::addInstance for firstcall:true does the "+1" as done by CSGFoundry::addInstanceVector
    1777 
    1778 3. original access to the copyno from Geant4 in U4SensorIdentifierDefault::getInstanceIdentity
    1779    which is used from U4Tree::identifySensitiveInstances to populate the stree.h snode::sensor_id
    1780 
    1781 **/
    1782 
    1783 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, RNG& rng, sctx& ctx) const
    1784 {
    1785 
    1786     sphoton& p = ctx.p ;
    1787     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal
    1788     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor
    1789     const float lposcost = ctx.prd->lposcost() ;  // local frame intersect position cosine theta
    1790 
    1791 




B side : photons pass thru PMT as if not there (with some absorbed on way) and get absorbed onto wall. 
That is similar to the former issue of incorrect heirarchy.



::

    In [3]: a.f.record.shape
    Out[3]: (100000, 32, 4, 4)

    In [4]: a.f.record[:,0,0]
    Out[4]: 
    array([[-20772.762,    275.858,  20163.   ,      0.1  ],
           [-20772.762,    275.858,  20163.002,      0.1  ],
           [-20772.762,    275.858,  20163.006,      0.1  ],
           [-20772.762,    275.858,  20163.008,      0.1  ],
           [-20772.762,    275.858,  20163.01 ,      0.1  ],
           ...,
           [-20772.762,    275.858,  20412.99 ,      0.1  ],
           [-20772.762,    275.858,  20412.992,      0.1  ],
           [-20772.762,    275.858,  20412.994,      0.1  ],
           [-20772.762,    275.858,  20412.998,      0.1  ],
           [-20772.762,    275.858,  20413.   ,      0.1  ]], shape=(100000, 4), dtype=float32)

    In [5]: a.f.record[:,1,0]
    Out[5]: 
    array([[-20894.191,    275.858,  20163.   ,      0.505],
           [-20894.191,    275.858,  20163.002,      0.505],
           [-20894.191,    275.858,  20163.006,      0.505],
           [-20894.191,    275.858,  20163.008,      0.505],
           [-20894.191,    275.858,  20163.01 ,      0.505],
           ...,
           [-21045.625,    275.858,  20412.99 ,      1.01 ],
           [-21045.635,    275.858,  20412.992,      1.01 ],
           [-21045.64 ,    275.858,  20412.994,      1.01 ],
           [-21045.656,    275.858,  20412.998,      1.011],
           [-21045.668,    275.858,  20413.   ,      1.011]], shape=(100000, 4), dtype=float32)



stree__FREQ_CUT 300
--------------------


Factorization is different::

    (ok) A[blyth@localhost CSGFoundry]$ cat mmlabel.txt 
    2540:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    4:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:base_steel
    3:uni_acrylic1
    130:sPanel
    1:sStrut_0
    6:PMT_20inch_pmt_solid_head
    322:solidSJCLSanchor



But maybe not sensors?::

    ]
    [stree::desc_sensor_nd
     edge            0
     num_nd          384793
     num_nd_sensor   45965
     num_sid         45965
    ...
     nidx  66517 i      1 sensor_id      0 sensor_index      1 sensor_name      4
     nidx  66525 i      2 sensor_id      0 sensor_index      2 sensor_name      4
     nidx  66533 i      3 sensor_id      0 sensor_index      3 sensor_name      4
     nidx  66541 i      4 sensor_id      0 sensor_index      4 sensor_name      4
     nidx 244933 i  17616 sensor_id  17611 sensor_index  17616 sensor_name      2
     nidx 244945 i  17617 sensor_id  20000 sensor_index  17617 sensor_name      0
     nidx 244950 i  17618 sensor_id  20001 sensor_index  17618 sensor_name      0
     nidx 244955 i  17619 sensor_id  20002 sensor_index  17619 sensor_name      0
     nidx 372940 i  43216 sensor_id  45599 sensor_index  43216 sensor_name      0
     nidx 373105 i  43217 sensor_id  50000 sensor_index  43217 sensor_name      3
     nidx 373109 i  43218 sensor_id  50001 sensor_index  43218 sensor_name      3
     nidx 373113 i  43219 sensor_id  50002 sensor_index  43219 sensor_name      3
    ]stree::desc_sensor_nd
    stree::desc_sensor_id sensor_id.size 45965
    [
          0 sid        0
          1 sid        0
          2 sid        0
          3 sid        0
          4 sid        0
          5 sid        0
          6 sid        1
          7 sid        2
          8 sid        3
          9 sid        4
    ...
      17616 sid    17611
      17617 sid    20000
      17618 sid    20001
      17619 sid    20002
      43216 sid    45599
      43217 sid    50000
      43218 sid    50001
      43219 sid    50002
      45956 sid    52739
      45957 sid    52740
      45958 sid    52741
      45959 sid    52742
      45960 sid    52743
      45961 sid    52744
      45962 sid    52745
      45963 sid    52746
      45964 sid    52747
    ]]stree::postcreate
    2025-08-25 19:26:59.363 INFO  [2815315] [U4Tree::Create@245] ]stree::postcreate




::

    PMT::init_total [SPMT_Total
             CD_LPMT  17612
                SPMT  25600
                  WP   2400
         WP_ATM_LPMT    348
         WP_ATM_MPMT      0
          WP_WAL_PMT      5
                 ALL  45965
                SUM:  45965
            SUM==ALL    YES
    ]SPMT_Total


    In [4]: 17612+25600+2400+348+5
    Out[4]: 45965





After instancing WP_ATM_LPMT get the lpmtid : but it is not expected yet
-----------------------------------------------------------------------------



ATQC
------

::

    (ok) A[blyth@localhost tests]$ opticks-f ATQC
    ./qudarap/tests/QPMTTest.h:    qscan->add("atqc",    qpmt->mct_lpmtid_scan(qpmt_ATQC, mct_domain, lpmtid) ) ;
    ./qudarap/qsim.h:    printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d wl %8.4f mct %8.4f dpcmn %8.4f pmt %p pre-ATQC \n",
    ./qudarap/qsim.h:    float ATQC[4] = {} ;
    ./qudarap/qsim.h:    if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ctx.pidx, ctx.pidx_debug );
    ./qudarap/qsim.h:    if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    ./qudarap/qsim.h:    printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d wl %8.4f mct %8.4f dpcmn %8.4f lpc %8.4f ATQC ( %8.4f %8.4f %8.4f %8.4f  ) \n",
    ./qudarap/qsim.h:           ctx.pidx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ATQC[0], ATQC[1], ATQC[2], ATQC[3] );
    ./qudarap/qsim.h:    const float& theAbsorption        = ATQC[0];
    ./qudarap/qsim.h:    const float& theTransmittance     = ATQC[1];
    ./qudarap/qsim.h:    const float& theEfficiency        = ATQC[2];
    ./qudarap/qsim.h:    const float& collectionEfficiency = ATQC[3];
    ./qudarap/qsim.h:        printf("//qsim.propagate_at_surface_CustomART pidx %7d lpmtid %d ATQC ( %8.4f %8.4f %8.4f %8.4f ) u_theAbsorption  %7.3f action %d \n",
    ./qudarap/qsim.h:        ctx.pidx, lpmtid, ATQC[0], ATQC[1], ATQC[2], ATQC[3], u_theAbsorption, action  );
    ./qudarap/qsim.h:            printf("//qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx %7d lpmtid %d ATQC ( %8.4f %8.4f %8.4f %8.4f ) u_theEfficiency  %8.4f theEfficiency %8.4f flag %d \n",
    ./qudarap/qsim.h:                                                                    ctx.pidx, lpmtid, ATQC[0],ATQC[1], ATQC[2],ATQC[3],  u_theEfficiency,  theEfficiency, flag );
    ./qudarap/qsim.h:            printf("//qsim.propagate_at_surface_CustomART.CONTINUE pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) theTransmittance %7.3f  \n",
    ./qudarap/qsim.h:            ctx.pidx, lpmtid, ATQC[0], ATQC[1], ATQC[2], ATQC[3], theTransmittance  );
    ./qudarap/QPMT.hh:       case qpmt_ATQC:    lookup = NP::Make<T>( ni, nj, 4  )          ; break ;
    ./qudarap/qpmt_enum.h:  qpmt_ATQC,
    ./qudarap/qpmt_enum.h:    static constexpr const char* _qpmt_ATQC    = "qpmt_ATQC" ;
    ./qudarap/qpmt_enum.h:        case qpmt_ATQC:    s = _qpmt_ATQC    ; break ;
    ./qudarap/QPMT.cu:        else if( etype == qpmt_ATQC )
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_ATQC(payload, pmtid, wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, pidx, pidx_debug );
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_ATQC(payload, pmtid, wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    ./qudarap/QPMT.cu:        case qpmt_ATQC:
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_ATQC(  F* ATQC, int lpmtid, F wavelength_nm, F minus_cos_theta, F dot_pol_cross_mom_nrm, F lposcost, unsigned pidx, bool pidx_debug ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_ATQC(  F* ATQC  , int lpmtid, F wavelength_nm, F minus_cos_theta, F dot_pol_cross_mom_nrm, F lposcost ) const ;
    ./qudarap/qpmt.h:Currently called by qpmt::get_lpmtid_ATQC
    ./qudarap/qpmt.h:Potentially called by qpmt::get_lpmtid_ATQC
    ./qudarap/qpmt.h:qpmt::get_lpmtid_ATQC
    ./qudarap/qpmt.h:ATQC[0] A
    ./qudarap/qpmt.h:ATQC[1] T
    ./qudarap/qpmt.h:ATQC[2] Q
    ./qudarap/qpmt.h:ATQC[3] C
    ./qudarap/qpmt.h:inline QPMT_METHOD void qpmt<F>::get_lpmtid_ATQC(
    ./qudarap/qpmt.h:      F* ATQC
    ./qudarap/qpmt.h:    ATQC[3] = ce ;
    ./qudarap/qpmt.h:    //if(pidx_debug) printf("//qpmt.get_lpmtid_ATQC pidx %7d lpmtid %d energy_eV %8.4f _qe(spec[15]) %8.4f lposcost %8.4f ce %8.4f  \n", pidx, lpmtid, energy_eV, _qe, lposcost, ce );
    ./qudarap/qpmt.h:        ATQC[2] = _qe/stack.art.A ;
    ./qudarap/qpmt.h:        if(pidx_debug) printf("//qpmt.get_lpmtid_ATQC pidx %7d lpmtid %d energy_eV %8.4f _qe(spec[15]) %8.4f lposcost %8.4f ce %8.4f stack.art.A %8.4f _qe/stack.art.A=ATQC[2] %8.4f  ce=ATQC[3] %8.4f  \n",
    ./qudarap/qpmt.h:                                                      pidx, lpmtid, energy_eV, _qe, lposcost, ce, stack.art.A, ATQC[2], ATQC[3] );
    ./qudarap/qpmt.h:        ATQC[2] = zero ;
    ./qudarap/qpmt.h:    ATQC[0] = A ;         // aka theAbsorption
    ./qudarap/qpmt.h:    ATQC[1] = T/(one-A) ; // aka theTransmittance
    ./qudarap/qpmt.h:    std::cout << "//qpmt.get_lpmtid_ATQC stack.calc.2 " << std::endl ;
    ./qudarap/qpmt.h:    std::cout << "//qpmt.get_lpmtid_ATQC wavelength_nm " << wavelength_nm << std::endl ;
    ./qudarap/qpmt.h:    std::cout << "//qpmt.get_lpmtid_ATQC minus_cos_theta " << minus_cos_theta << std::endl ;
    ./qudarap/qpmt.h:    std::cout << "//qpmt.get_lpmtid_ATQC dot_pol_cross_mom_nrm " << dot_pol_cross_mom_nrm << std::endl ;
    ./qudarap/qpmt.h:    std::cout << "//qpmt.get_lpmtid_ATQC " << stack << std::endl ;
    (ok) A[blyth@localhost opticks]$ 







