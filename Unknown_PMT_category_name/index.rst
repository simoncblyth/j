init_IDService
===============

HMM: this error could be from mixing J25.3 and J25.4 



::

    A[blyth@localhost junosw]$ jgr init_IDService_WP_PMT
    ./Detector/Geometry/src/PMTParamSvc.cc:  st_IDService_WP_PMT = init_IDService_WP_PMT();
    ./Detector/Geometry/src/PMTParamSvc.cc:bool PMTParamSvc::init_IDService_WP_PMT(){
    ./Detector/Geometry/src/PMTParamSvc.h:  bool init_IDService_WP_PMT();
    A[blyth@localhost junosw]$ 


::

    1079 bool PMTParamSvc::init_IDService_CD_LPMT(){
    1080   for (unsigned int copyno = kOFFSET_CD_LPMT; copyno < kOFFSET_CD_LPMT_END; copyno ++){
    1081      m_nums_cd_lpmt++;
    1082      Identifier id = idServ ->copyNo2Id(copyno);
    1083      // Position
    1084      m_pmt_x[copyno] =  idServ ->id2X(id);
    1085      m_pmt_y[copyno] =  idServ ->id2Y(id);
    1086      m_pmt_z[copyno] =  idServ ->id2Z(id);
    1087      m_pmt_theta[copyno] =  idServ ->id2Ori_Theta(id);
    1088      m_pmt_phi[copyno] =  idServ ->id2Ori_Phi(id);
    1089      m_pmt_psi[copyno] = 0.0;
    1090      // Type
    1091      int PMTType = idServ ->id2Type(id);
    1092 
    1093      if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    1094      else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    1095      else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    1096      else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    1097      else{LogError << "Unknown PMT category name: " << kPMT_Unknown << std::endl;
    1098           m_pmt_categories[copyno] = kPMT_Unknown;}
    1099   }
    1100   return true;
    1101 }


    0071 bool PMTParamSvc::initialize() {
      72   bool st;
      73 
      74   // init the ranges
      75   st = init_ranges();
      76   if (!st) { return st; }
      77 
      78   // init global info
      79   st = init_default();
      80   if (!st) { return st; }
      81 
      82   // FILE MODE
      83   if (m_db_type == "File") {
      84     st = init_file();
      85   } else if (m_db_type == "ROOT") {
      86 
      87   } else if (m_db_type == "MySQL") {
      88 
      89   } else if (m_db_type == "IDService") {
      90     idServ = IDService::getIdServ();
      91     idServ -> init();
      92     st = init_IDService();
      93   }
      94 
      95   bool isValidPMT = (is20inch(m_construct_center_pmtid) or is3inch(m_construct_center_pmtid) or isWP(m_construct_center_pmtid));
      96   if(m_distance_to_center_pmt > 0 and isValidPMT ){
      97     if(m_pmt_constructed_ranges.size()==0){
      98        init_vis_nearby_pmt();
      99     }
     100   }
     101 
     102   return st;
     103 }



     016 PMTParamSvc::PMTParamSvc(const std::string& name)
      17     :
      18     SvcBase(name),
      19     m_db_type("IDService"), //IDService is default, another avaliable option is File.
      20     m_pmt_categories(data.m_pmt_categories),
      21     m_file_cd_lpmt_pos_path(),
      22     m_file_cd_lpmt_type_path(),
      23     m_file_cd_spmt_pos_path(),
      24     m_file_cd_spmt_type_path(),
      25     m_file_wp_lpmt_pos_path(),
      26     m_file_wp_lpmt_type_path()
      27 {
      28   declProp("DBType", m_db_type);
      29   declProp("Path_CD_LPMT_Pos", m_file_cd_lpmt_pos_path);
      30   declProp("Path_CD_LPMT_Type", m_file_cd_lpmt_type_path);
      31   declProp("Path_CD_SPMT_Pos", m_file_cd_spmt_pos_path);


::

    1062     def init_geometry_and_parameters(self, task, args):
    1063         import Geometry
    1064         pmt_param_svc = task.createSvc("PMTParamSvc")
    1065 
    1066         if args.ranges_pmt_enabled:
    1067             l = args.ranges_pmt_enabled.split(",")
    1068             l = [int(i) for i in l if i.isdigit()]
    1069             pmt_param_svc.property("Ranges_PMT_Enabled").set(l)
    1070 
    1071         if args.ranges_pmt_constructed:
    1072             l = args.ranges_pmt_constructed.split(",")
    1073             l = [int(i) for i in l if i.isdigit()]
    1074             pmt_param_svc.property("Ranges_PMT_Constructed").set(l)
    1075 
    1076         pmt_param_svc.property("Construct_Center_PMTID").set(args.construct_center_pmtid)
    1077         pmt_param_svc.property("Distance_To_Center_PMT").set(args.distance_to_center_pmt)
    1078         pmt_param_svc.property("DBType").set(args.pmt_dbtype)
    1079 
    1080         tt_geom_svc = task.createSvc("TTGeomSvc")
    1081 
    1082         import PMTSimParamSvc
    1083         print(" == PMTSimParamSvc == ")
    1084         pmt_sim_param_svc = task.createSvc("PMTSimParamSvc")
    1085         pmt_sim_param_svc.property("DBType").set(args.dbtype)
    1086         pmt_sim_param_svc.property("PDEValue").set(args.PDEValue)
    1087 


    0353 
     354         parser.add_argument("--pmt-dbtype", default="IDService", help="PMTParam db type", choices=["IDService", "File"])
     355 





::

    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_CD_SPMT ERROR: Unknown PMT category name: -1
    ...
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService_WP_PMT ERROR: Unknown PMT category name: -1
    junotoptask:PMTParamSvc.init_IDService  INFO: CD LPMT Num: 17612	CD SPMT Num: 25600	WP LPMT Num: 2400
    junotoptask:PMTParamSvc.init_PMT_R  INFO: CD LPMT Mean R: 19433.93164 mm	CD SPMT Mean R: 19384.00000 mm
    junotoptask:PMTParamSvc.init_PMT_R  INFO: CD LPMT Mean R: 19433.93164 mm (unshifted)	CD SPMT Mean R: 19384.00000 mm  (unshifted)
    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/data/Detector/Geometry/TopTracker/CrossTalk.txt
    junotoptask:TTGeomSvc.init_file  INFO: Loading parameters from file: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/data/Detector/Geometry/TopTracker/ChannelPosition.txt
    junotoptask:PMTSimParamSvc.initialize  INFO: PMTSimParamSvc is initializing!
    junotoptask:PMTSimParamSvc.initialize  INFO: db_type: File
    junotoptask:PMTSimParamSvc.init_default  INFO: Retrieve PMTParamSvc successfully.




    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbdf75445 in LSExpDetectorConstruction::setupCD_PMTs (this=0xa26c260) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1342
    #6  0x00007fffbdf6cfd8 in LSExpDetectorConstruction::Construct (this=0xa26c260) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:290
    #7  0x00007fffc6c6292e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007fffc6c62afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x00007fffcf349b1b in DetSimAlg::initialize (this=0x671dbe0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #10 0x00007fffd4215b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd422b09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffd4233447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd422b048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so



