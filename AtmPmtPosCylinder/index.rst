AtmPmtPosCylinder
=======================


jcv CopyNumber::

     11 
     12 //  #include "Identifier/CopyNumber.hh"
     13 
     14 enum PMTID_OFFSET_DETSIM {
     15   kOFFSET_CD_LPMT=0,     kOFFSET_CD_LPMT_END=17612, // CD-LPMT
     16   kOFFSET_CD_SPMT=20000, kOFFSET_CD_SPMT_END=45600,  // CD-SPMT
     17   kOFFSET_WP_PMT=50000,  kOFFSET_WP_PMT_END=52400,  // WP-LPMT
     18   kOFFSET_WP_ATM_LPMT=52400,  kOFFSET_WP_ATM_LPMT_END=52748, //WP-Atmosphere-LPMT
     19   kOFFSET_WP_ATM_MPMT=53000,  kOFFSET_WP_ATM_MPMT_END=53600,  //WP-Atmosphere-MPMT (Medium, 8 inch)
     20   kOFFSET_WP_WAL_PMT=54000,  kOFFSET_WP_WAL_PMT_END=54005 //WP-Water-attenuation-length
     21 
     22 };
     23 


Outward pointing PMTs that should be pointed inwards::

     43 void
     44 AtmPmtPosCylinder::initialize() {
     45     SniperPtr<IPMTParamSvc> pmtParamSvc(*m_scope, "PMTParamSvc");
     46     if (pmtParamSvc.invalid())
     47     {
     48         LogError << "Can't Locate  PMTParamSvc." << std::endl;
     49         assert(0);
     50     }
     51     
     52     for (int i = kOFFSET_WP_ATM_LPMT; i<kOFFSET_WP_ATM_LPMT+pmtParamSvc->get_NTotal_WP_ATM_LPMT(); i++) // kOFFSET_WP_PMT=30000
     53     {
     54         G4double x = pmtParamSvc->getPMTX(i);
     55         G4double y = pmtParamSvc->getPMTY(i);
     56         G4double z = pmtParamSvc->getPMTZ(i);
     57         G4double theta = pmtParamSvc->getPMTTheta(i);
     58         G4double phi = pmtParamSvc->getPMTPhi(i);
     59 
     60         theta = theta * deg;
     61         phi = phi * deg;
     62         // Positions and rotations for regular PMT
     63         // construct G4Transform3D
     64         G4ThreeVector pos(x, y, z);
     65         G4RotationMatrix rot;
     66         rot.rotateY(theta);
     67         rot.rotateZ(phi);
     68         G4Transform3D trans(rot, pos);
     69         m_position.push_back(trans);
     70     }
     71 }
     72 
     73 }
     74 
     75 }


::

    A[blyth@localhost junosw]$ jgr AtmPmtPosCylinder
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:#include "AtmPmtPosCylinder.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:    IDetElementPos* veto_atm_pmt_detelem_pos = new JUNO::Cylinder::AtmPmtPosCylinder(m_scope);
    ./Simulation/DetSimV2/SimUtil/include/AtmPmtPosCylinder.hh:#ifndef AtmPmtPosCylinder_hh
    ./Simulation/DetSimV2/SimUtil/include/AtmPmtPosCylinder.hh:#define AtmPmtPosCylinder_hh
    ./Simulation/DetSimV2/SimUtil/include/AtmPmtPosCylinder.hh:class AtmPmtPosCylinder: public IDetElementPos{
    ./Simulation/DetSimV2/SimUtil/include/AtmPmtPosCylinder.hh:    AtmPmtPosCylinder(Task* scope);
    ./Simulation/DetSimV2/SimUtil/include/AtmPmtPosCylinder.hh:    ~AtmPmtPosCylinder();
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:#include "AtmPmtPosCylinder.hh"
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::AtmPmtPosCylinder(Task* scope)
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::~AtmPmtPosCylinder() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::hasNext() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::next() {
    ./Simulation/DetSimV2/SimUtil/src/AtmPmtPosCylinder.cc:AtmPmtPosCylinder::initialize() {
    A[blyth@localhost junosw]$ 




::


     359 float PMTParamSvc::getPMTX(int pmtid) const
     360 {
     361   if (is20inch(pmtid) || is3inch(pmtid) || isWP(pmtid))
     362   {
     363     return m_pmt_x.at(pmtid);
     364   }
     365   else
     366   {
     367     std::cout << "Wrong PMT id input: " << pmtid << std::endl;
     368     return 0;
     369   }
     370 }
     371 
     372 float PMTParamSvc::getPMTY(int pmtid) const
     373 {
     374   if (is20inch(pmtid) || is3inch(pmtid) || isWP(pmtid))
     375   {
     376     return m_pmt_y.at(pmtid);
     377   }
     378   else
     379   {
     380     std::cout << "Wrong PMT id input: " << pmtid << std::endl;
     381     return 0;
     382   }
     383 }
     384 
     385 float PMTParamSvc::getPMTZ(int pmtid) const
     386 {
     387   if (is20inch(pmtid) || is3inch(pmtid) || isWP(pmtid))
     388   {
     389     return m_pmt_z.at(pmtid);
     390   }
     391   else
     392   {
     393     std::cout << "Wrong PMT id input: " << pmtid << std::endl;
     394     return 0;
     395   }
     396 }
     397
     398 float PMTParamSvc::getPMTTheta(int pmtid) const
     399 {
     400   if (is20inch(pmtid) || is3inch(pmtid) || isWP(pmtid))
     401   {
     402     return m_pmt_theta.at(pmtid);
     403   }
     404   else
     405   {
     406     std::cout << "Wrong PMT id input: " << pmtid << std::endl;
     407     return 0;
     408   }
     409 }
     410 
     411 float PMTParamSvc::getPMTPhi(int pmtid) const
     412 {
     413   if (is20inch(pmtid) || is3inch(pmtid) || isWP(pmtid))
     414   {
     415     return m_pmt_phi.at(pmtid);
     416   }
     417   else
     418   {
     419     std::cout << "Wrong PMT id input: " << pmtid << std::endl;
     420     return 0;
     421   }
     422 }


::

     596 bool PMTParamSvc::init_file()
     597 {
     598   std::string dir_path = "/data/Detector/Geometry/";
     599 
     600   if (m_file_cd_lpmt_pos_path.empty())
     601   {
     602     m_file_cd_lpmt_pos_path = getFilePath(dir_path + "PMTPos_CD_LPMT.csv");
     603   }
     604 
     605   if (m_file_cd_lpmt_type_path.empty())
     606   {
     607     m_file_cd_lpmt_type_path = getFilePath(dir_path + "PMTType_CD_LPMT.csv");
     608   }
     609 
     610   if (m_file_cd_spmt_pos_path.empty())
     611   {
     612     m_file_cd_spmt_pos_path = getFilePath(dir_path + "PMTPos_CD_SPMT.csv");
     613   }
     614 
     615   if (m_file_cd_spmt_type_path.empty())
     616   {
     617     m_file_cd_spmt_type_path = getFilePath(dir_path + "PMTType_CD_SPMT.csv");
     618   }
     619 
     620   if (m_file_wp_lpmt_pos_path.empty())
     621   {
     622     m_file_wp_lpmt_pos_path = getFilePath(dir_path + "PMTPos_WP_LPMT.csv");
     623   }
     624 
     625   if (m_file_wp_lpmt_type_path.empty())
     626   {
     627     m_file_wp_lpmt_type_path = getFilePath(dir_path + "PMTType_WP_LPMT.csv");
     628   }
     629 
     630   if (m_file_cd_lpmt_pos_shift_path.empty())
     631   {
     632     m_file_cd_lpmt_pos_shift_path = getFilePath(dir_path + "PMTPos_Shift_CD_LPMT.csv");
     633   }
     634 
     635   if (m_file_cd_spmt_pos_shift_path.empty())
     636   {
     637     m_file_cd_spmt_pos_shift_path = getFilePath(dir_path + "PMTPos_Shift_CD_SPMT.csv");
     638   }
     639 
     640   if (m_file_wp_lpmt_pos_shift_path.empty())
     641   {
     642     m_file_wp_lpmt_pos_shift_path = getFilePath(dir_path + "PMTPos_Shift_WP_LPMT.csv");
     643   }







::

    A[blyth@localhost junosw]$ head -10 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    #Position file for Veto PMT in WP Sphere.     
    ##Updated by Yuning Su (suyn26 AT mail2.sysu.edu.cn) in 20250425.     
    #A total of 2399 PMTs were actually installed in Sphere. More detail in https://docs.ihep.ac.cn/link/AR573CA85D4A004CE8B5AC50662739AB3F.     
    #CopyNo X Y Z Orientation_theta Orientation_phi
    50000 -1487.68 -114.12 20502 4.1624 -175.6134
    50001 -1205.3 -879.478 20502 4.1624 -143.8827
    50002 -576.011 -735.794 20502 2.6096 -128.0554
    50003 -351.185 -1450.14 20502 4.1624 -103.6134
    50004 463.9748 -1418.08 20502 4.1624 -71.8827
    50005 348.5799 -875.192 20502 2.6309 -68.2831

    A[blyth@localhost junosw]$ tail -10 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    52390 568.2732 -1379.58 -20502 175.8376 -67.6124
    52391 1208.891 -874.502 -20502 175.8376 -35.8817
    52392 796.4313 -503.122 -20502 177.3692 -32.2814
    52393 1487.665 114.1461 -20502 175.8376 4.3876
    52394 1205.269 879.4874 -20502 175.8376 36.1183
    52395 724.6081 601.978 -20502 177.3692 39.7186
    52396 351.1543 1450.127 -20502 175.8376 76.3876
    52397 -463.994 1418.055 -20502 175.8376 108.1183
    52398 -348.599 875.1647 -20502 177.3692 111.7186
    52399 -1270.64 782.0814 -20502 175.8376 148.3876
    A[blyth@localhost junosw]$ 


::

    (ok) A[blyth@localhost junosw]$ l /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.?/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    119 -rw-rw-r--. 1 cvmfs cvmfs 121496 Aug  4 20:38 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.3/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    119 -rw-rw-r--. 1 cvmfs cvmfs 121496 Jul 15 00:06 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.2/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    119 -rw-rw-r--. 1 cvmfs cvmfs 121496 May 31 22:13 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    119 -rw-rw-r--. 1 cvmfs cvmfs 121496 May 31 22:13 /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.1/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv

    (ok) A[blyth@localhost junosw]$ md5sum /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.?/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    a58297bf2fa97b05c50bb8b9d079b344  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    a58297bf2fa97b05c50bb8b9d079b344  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.1/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    a58297bf2fa97b05c50bb8b9d079b344  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.2/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv
    a58297bf2fa97b05c50bb8b9d079b344  /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.3/dbdata/offline-data/Detector/Geometry/PMTPos_WP_LPMT.csv





Debug : its getting values from IDService not the csv
--------------------------------------------------------

::

    A[blyth@localhost ~]$ BP=PMTParamSvc::initialize ipc

    (gdb) p m_db_type
    No symbol "m_db_type" in current context.
    (gdb) b 101
    Breakpoint 2 at 0x7fffc02afa26: file /home/blyth/junosw/Detector/Geometry/src/PMTParamSvc.cc, line 102.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 2, PMTParamSvc::initialize (this=0x666f6f0) at /home/blyth/junosw/Detector/Geometry/src/PMTParamSvc.cc:102
    102	  st = init_default();
    (gdb) p m_db_type
    $1 = "IDService"
    (gdb) 

    (gdb) b PMTParamSvc::init_IDService_WP_ATM_LPMT



    (gdb) list 1202
    1197	bool PMTParamSvc::init_IDService_WP_ATM_LPMT(){
    1198	  for (unsigned int copyno = kOFFSET_WP_ATM_LPMT; copyno < kOFFSET_WP_ATM_LPMT_END; copyno ++){
    1199	     m_nums_wp_atm_lpmt++;
    1200	     Identifier id = idServ ->copyNo2Id(copyno);
    1201	     // Position
    1202	     m_pmt_x[copyno] =  idServ ->id2X(id);
    1203	     m_pmt_y[copyno] =  idServ ->id2Y(id);
    1204	     m_pmt_z[copyno] =  idServ ->id2Z(id);
    1205	     m_pmt_theta[copyno] =  idServ ->id2Ori_Theta(id);
    1206	     m_pmt_phi[copyno] =  idServ ->id2Ori_Phi(id);
    (gdb) list 1210
    1205	     m_pmt_theta[copyno] =  idServ ->id2Ori_Theta(id);
    1206	     m_pmt_phi[copyno] =  idServ ->id2Ori_Phi(id);
    1207	     m_pmt_psi[copyno] = 0.0;
    1208	     // Type
    1209	     int PMTType = idServ ->id2Type(id);
    1210	
    1211	     if (PMTType == kPMT_Hamamatsu){m_pmt_categories[copyno] = kPMT_Hamamatsu;}
    1212	     else if (PMTType == kPMT_NNVT){m_pmt_categories[copyno] = kPMT_NNVT;}
    1213	     else if (PMTType == kPMT_NNVT_HighQE){m_pmt_categories[copyno] = kPMT_NNVT_HighQE;}
    1214	     else if (PMTType == kPMT_HZC){m_pmt_categories[copyno] = kPMT_HZC;}
    (gdb) b 1209
    Breakpoint 5 at 0x7fffc02b5fb8: file /home/blyth/junosw/Detector/Geometry/src/PMTParamSvc.cc, line 1209.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 5, PMTParamSvc::init_IDService_WP_ATM_LPMT (this=0x666f6f0) at /home/blyth/junosw/Detector/Geometry/src/PMTParamSvc.cc:1209
    1209	     int PMTType = idServ ->id2Type(id);
    (gdb) p copyno
    $4 = 52400
    (gdb) p m_pmt_x[copyno]
    Attempt to take address of value not located in memory.
    (gdb) p this->m_pmt_x
    $5 = std::unordered_map with 45613 elements = {[52400] = -21034.9004, [52399] = -1270.64001, [52398] = -348.598999, [52397] = -463.993988, [52396] = 351.154297, [52395] = 724.608093, [52394] = 1205.26904, [52393] = 1487.66504, 
      [52392] = 796.431274, [52391] = 1208.89099, [52390] = 568.273193, [52389] = -232.386002, [52388] = -458.132996, [52387] = -1136.44995, [52386] = -940.054016, [52385] = -1492.03003, [52384] = -2391.45996, [52383] = -2034.05005, 
      [52382] = -3188.3999, [52381] = -2854.98999, [52380] = -2521.57007, [52379] = -1134.32996, [52378] = -556.072998, [52377] = -1629.94995, [52376] = -1090.52002, [52375] = -551.078003, [52374] = 556.072998, [52373] = 1134.30701, 
      [52372] = 551.078796, [52371] = 1090.48706, [52370] = 1629.91003, [52369] = 2034.07703, [52368] = 2391.41992, [52367] = 2521.6189, [52366] = 2854.96899, [52365] = 3188.3291, [52364] = 2735.13208, [52363] = 2735.09204, 
      [52362] = 3528.98706, [52361] = 3528.94897, [52360] = 3528.91406, [52359] = 2391.45996, [52358] = 2034.052, [52357] = 3188.40088, [52356] = 2854.99097, [52355] = 2521.57397, [52354] = 1134.33203, [52353] = 556.072693, 
      [52352] = 1629.95496, [52351] = 1090.52295, [52350] = 551.07843, [52349] = -556.072998, [52348] = -1134.31006, [52347] = -551.078979, [52346] = -1090.48999, [52345] = -1629.91003, [52344] = -2034.07996, [52343] = -2391.41992, 
      [52342] = -2521.62012, [52341] = -2854.96997, [52340] = -3188.33008, [52339] = -2735.12988, [52338] = -2735.09009, [52337] = -3528.98999, [52336] = -3528.94995, [52335] = -3528.90991, [52334] = -5199.9502, [52333] = -4856.52979, 
      [52332] = -4300.83984, [52331] = -3557.18994, [52330] = -2658.08008, [52329] = -1766.55005, [52328] = -555.685974, [52327] = 555.666016, [52326] = 1642.75195, [52325] = 2658.04297, [52324] = 3557.16406, [52323] = 4624.81299, 
      [52322] = 4856.51709, [52321] = 5199.9458, [52320] = 5316.12012, [52319] = 5199.9541, [52318] = 4856.5249, [52317] = 4624.83789, [52316] = 3557.17896, [52315] = 2658.0769, [52314] = 1642.79004, [52313] = 555.705688, 
      [52312] = -555.666016, [52311] = -1766.51001, [52310] = -2658.06006, [52309] = -3557.15991, [52308] = -4300.81982, [52307] = -4856.50977, [52306] = -5199.9502, [52305] = -5716.6001, [52304] = -7026.81982, [52303] = -7757.06982, 
      [52302] = -6562.72998, [52301] = -7244.39014...}
    (gdb) p this->m_pmt_x[copyno]
    Attempt to take address of value not located in memory.
    (gdb) p this->m_pmt_x[52400]
    Attempt to take address of value not located in memory.
    (gdb) p this->m_pmt_y
    $6 = std::unordered_map with 45613 elements = {[52400] = 1378.698, [52399] = 782.081421, [52398] = 875.164673, [52397] = 1418.05505, [52396] = 1450.12695, [52395] = 601.978027, [52394] = 879.487427, [52393] = 114.146103, 
      [52392] = -503.122009, [52391] = -874.502014, [52390] = -1379.57996, [52389] = -912.924011, [52388] = -1419.95996, [52387] = -966.773987, [52386] = -61.0965004, [52385] = -3.08119988, [52384] = 1361.72205, [52383] = 1853.58496, 
      [52382] = 1615.41296, [52381] = 2074.24902, [52380] = 2533.0979, [52379] = 2507.32202, [52378] = 2695.16699, [52377] = 3180.99194, [52376] = 3356.22412, [52375] = 3531.46289, [52374] = 2695.20898, [52373] = 2507.28711, 
      [52372] = 3531.54004, [52371] = 3356.23608, [52370] = 3180.92993, [52369] = 1853.61902, [52368] = 1361.70898, [52367] = 2533.15991, [52366] = 2074.28003, [52365] = 1615.38904, [52364] = 304.008698, [52363] = -303.996002, 
      [52362] = 567.19873, [52361] = 0.0189999994, [52360] = -567.174988, [52359] = -1361.71997, [52358] = -1853.57996, [52357] = -1615.41003, [52356] = -2074.25, [52355] = -2533.1001, [52354] = -2507.32007, [52353] = -2695.16992, 
      [52352] = -3180.98999, [52351] = -3356.21997, [52350] = -3531.45996, [52349] = -2695.20996, [52348] = -2507.29004, [52347] = -3531.54004, [52346] = -3356.23999, [52345] = -3180.92993, [52344] = -1853.62, [52343] = -1361.70996, 
      [52342] = -2533.15991, [52341] = -2074.28003, [52340] = -1615.39001, [52339] = -304.009003, [52338] = 303.995911, [52337] = -567.198975, [52336] = -0.0189999994, [52335] = 567.175415, [52334] = 1105.28296, [52333] = 2162.24292, 
      [52332] = 3124.72095, [52331] = 3950.63403, [52330] = 4603.88477, [52329] = 5436.80176, [52328] = 5286.99805, [52327] = 5287, [52326] = 5055.93701, [52325] = 4603.90479, [52324] = 3950.65991, [52323] = 3360.1499, [52322] = 2162.26099, 
      [52321] = 1105.30298, [52320] = 0.0198999997, [52319] = -1105.26001, [52318] = -2162.23999, [52317] = -3360.12012, [52316] = -3950.6499, [52315] = -4603.87988, [52314] = -5055.91992, [52313] = -5287, [52312] = -5287, 
      [52311] = -5436.81982, [52310] = -4603.89014, [52309] = -3950.65991, [52308] = -3124.75, [52307] = -2162.28003, [52306] = -1105.30005, [52305] = -0.0212999992, [52304] = 1493.56799, [52303] = 1650.52905, [52302] = 2921.88794, 
      [52301] = 3227.24609...}
    (gdb) p this->m_pmt_z
    $7 = std::unordered_map with 45613 elements = {[52400] = 20163, [52399] = -20502, [52398] = -20502, [52397] = -20502, [52396] = -20502, [52395] = -20502, [52394] = -20502, [52393] = -20502, [52392] = -20502, [52391] = -20502, 
      [52390] = -20502, [52389] = -20502, [52388] = -20502, [52387] = -20502, [52386] = -20502, [52385] = -20502, [52384] = -20365.5, [52383] = -20365.5, [52382] = -20240.4004, [52381] = -20240.4004, [52380] = -20240.4004, 
      [52379] = -20365.5, [52378] = -20365.5, [52377] = -20240.4004, [52376] = -20240.4004, [52375] = -20240.4004, [52374] = -20365.5, [52373] = -20365.5, [52372] = -20240.4004, [52371] = -20240.4004, [52370] = -20240.4004, 
      [52369] = -20365.5, [52368] = -20365.5, [52367] = -20240.4004, [52366] = -20240.4004, [52365] = -20240.4004, [52364] = -20365.5, [52363] = -20365.5, [52362] = -20240.4004, [52361] = -20240.4004, [52360] = -20240.4004, 
      [52359] = -20365.5, [52358] = -20365.5, [52357] = -20240.4004, [52356] = -20240.4004, [52355] = -20240.4004, [52354] = -20365.5, [52353] = -20365.5, [52352] = -20240.4004, [52351] = -20240.4004, [52350] = -20240.4004, 
      [52349] = -20365.5, [52348] = -20365.5, [52347] = -20240.4004, [52346] = -20240.4004, [52345] = -20240.4004, [52344] = -20365.5, [52343] = -20365.5, [52342] = -20240.4004, [52341] = -20240.4004, [52340] = -20240.4004, 
      [52339] = -20365.5, [52338] = -20365.5, [52337] = -20240.4004, [52336] = -20240.4004, [52335] = -20240.4004, [52334] = -19854.9004, [52333] = -19854.9004, [52332] = -19854.9004, [52331] = -19854.9004, [52330] = -19854.9004, 
      [52329] = -19750.3008, [52328] = -19854.9004, [52327] = -19854.9004, [52326] = -19854.9004, [52325] = -19854.9004, [52324] = -19854.9004, [52323] = -19750.3008, [52322] = -19854.9004, [52321] = -19854.9004, [52320] = -19854.9004, 
      [52319] = -19854.9004, [52318] = -19854.9004, [52317] = -19750.3008, [52316] = -19854.9004, [52315] = -19854.9004, [52314] = -19854.9004, [52313] = -19854.9004, [52312] = -19854.9004, [52311] = -19750.3008, [52310] = -19854.9004, 
      [52309] = -19854.9004, [52308] = -19854.9004, [52307] = -19854.9004, [52306] = -19854.9004, [52305] = -19750.3008, [52304] = -19246.9004, [52303] = -18954.4004, [52302] = -19246.9004, [52301] = -18954.4004...}
    (gdb) p this->m_pmt_theta
    $8 = std::unordered_map with 45613 elements = {[52400] = 90, [52399] = 175.837601, [52398] = 177.369202, [52397] = 175.837601, [52396] = 175.837601, [52395] = 177.369202, [52394] = 175.837601, [52393] = 175.837601, [52392] = 177.369202, 
      [52391] = 175.837601, [52390] = 175.837601, [52389] = 177.369202, [52388] = 175.837601, [52387] = 175.837601, [52386] = 177.369202, [52385] = 175.837601, [52384] = 172.304306, [52383] = 172.304398, [52382] = 169.985306, 
      [52381] = 170.109802, [52380] = 169.985504, [52379] = 172.304306, [52378] = 172.304398, [52377] = 169.985306, [52376] = 170.109802, [52375] = 169.985504, [52374] = 172.304306, [52373] = 172.304398, [52372] = 169.985306, 
      [52371] = 170.109802, [52370] = 169.985504, [52369] = 172.304306, [52368] = 172.304398, [52367] = 169.985306, [52366] = 170.109802, [52365] = 169.985504, [52364] = 172.304306, [52363] = 172.304398, [52362] = 169.985306, 
      [52361] = 170.109802, [52360] = 169.985504, [52359] = 172.304306, [52358] = 172.304398, [52357] = 169.985306, [52356] = 170.109802, [52355] = 169.985504, [52354] = 172.304306, [52353] = 172.304398, [52352] = 169.985306, 
      [52351] = 170.109802, [52350] = 169.985504, [52349] = 172.304306, [52348] = 172.304398, [52347] = 169.985306, [52346] = 170.109802, [52345] = 169.985504, [52344] = 172.304306, [52343] = 172.304398, [52342] = 169.985306, 
      [52341] = 170.109802, [52340] = 169.985504, [52339] = 172.304306, [52338] = 172.304398, [52337] = 169.985306, [52336] = 170.109802, [52335] = 169.985504, [52334] = 165.010696, [52333] = 165.010696, [52332] = 165.010696, 
      [52331] = 165.010696, [52330] = 165.010696, [52329] = 163.857193, [52328] = 165.010696, [52327] = 165.010696, [52326] = 165.010696, [52325] = 165.010696, [52324] = 165.010696, [52323] = 163.857193, [52322] = 165.010696, 
      [52321] = 165.010696, [52320] = 165.010696, [52319] = 165.010696, [52318] = 165.010696, [52317] = 163.857193, [52316] = 165.010696, [52315] = 165.010696, [52314] = 165.010696, [52313] = 165.010696, [52312] = 165.010696, 
      [52311] = 163.857193, [52310] = 165.010696, [52309] = 165.010696, [52308] = 165.010696, [52307] = 165.010696, [52306] = 165.010696, [52305] = 163.857193, [52304] = 159.532196, [52303] = 157.294998, [52302] = 159.532196, 
      [52301] = 157.295105...}

    (gdb) p this->m_pmt_phi
    $9 = std::unordered_map with 45613 elements = {[52400] = 176.25, [52399] = 148.387604, [52398] = 111.718597, [52397] = 108.118301, [52396] = 76.3876038, [52395] = 39.7186012, [52394] = 36.1183014, [52393] = 4.38759995, 
      [52392] = -32.2813988, [52391] = -35.8816986, [52390] = -67.6123962, [52389] = -104.281403, [52388] = -107.881699, [52387] = -139.612305, [52386] = -176.281403, [52385] = -179.881699, [52384] = 150.342407, [52383] = 137.657806, 
      [52382] = 153.130798, [52381] = 144.000305, [52380] = 134.869293, [52379] = 114.3423, [52378] = 101.657799, [52377] = 117.130699, [52376] = 108.000298, [52375] = 98.8694, [52374] = 78.3423996, [52373] = 65.6577988, 
      [52372] = 81.1307983, [52371] = 72.0002975, [52370] = 62.8694, [52369] = 42.3423996, [52368] = 29.6578007, [52367] = 45.1307983, [52366] = 36.0003014, [52365] = 26.8694, [52364] = 6.34240007, [52363] = -6.3421998, [52362] = 9.13080025, 
      [52361] = 0.000300000014, [52360] = -9.13059998, [52359] = -29.6576004, [52358] = -42.3420982, [52357] = -26.8691006, [52356] = -35.9996986, [52355] = -45.1306, [52354] = -65.6576004, [52353] = -78.3422012, [52352] = -62.8692017, 
      [52351] = -71.9997025, [52350] = -81.1306, [52349] = -101.6576, [52348] = -114.342201, [52347] = -98.8692017, [52346] = -107.999702, [52345] = -117.1306, [52344] = -137.6577, [52343] = -150.342194, [52342] = -134.869202, 
      [52341] = -143.999695, [52340] = -153.1306, [52339] = -173.657593, [52338] = 173.657806, [52337] = -170.869202, [52336] = -179.999695, [52335] = 170.8694, [52334] = 168, [52333] = 156.000198, [52332] = 144.000198, [52331] = 132.000198, 
      [52330] = 120.000198, [52329] = 108.000198, [52328] = 96, [52327] = 84.0001984, [52326] = 72.0001984, [52325] = 60.0001984, [52324] = 48.0001984, [52323] = 36.0001984, [52322] = 24, [52321] = 12.0002003, [52320] = 0.000199999995, 
      [52319] = -11.9996996, [52318] = -23.9997997, [52317] = -35.9998016, [52316] = -48, [52315] = -59.9998016, [52314] = -71.9998016, [52313] = -83.9998016, [52312] = -95.9998016, [52311] = -107.999802, [52310] = -120, 
      [52309] = -131.999802, [52308] = -143.999802, [52307] = -155.999802, [52306] = -167.999802, [52305] = -179.999802, [52304] = 168.000198, [52303] = 167.9879, [52302] = 156.000198, [52301] = 155.9879...}
    (gdb) 



IDService just reading some other files
-----------------------------------------

::

     54 bool IDService::initMap()
     55 {
     56     std::cout << "IDMapping Service is initializing!" << std::endl;
     57     // if Path is not set, using the default one.
     58     std::string pathCDL = CdLCsvFileName;
     59     std::string pathCDS = CdSCsvFileName;
     60     std::string pathWPV = WpVCsvFileName;
     61     std::string pathWPWAL = WpWALCsvFileName;
     62     std::string pathWPATML = WpATMLCsvFileName;
     63 
     64     if (pathCDL.empty()) {
     65         pathCDL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDLPMT_latest.csv");
     66     }
     67     if (pathCDS.empty()) {
     68         pathCDS = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDSPMT_latest.csv");
     69     }
     70     if (pathWPV.empty()) {
     71         pathWPV = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPVPMT_latest.csv");
     72     }
     73     if (pathWPWAL.empty()) {
     74         pathWPWAL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPWALPMT_latest.csv");
     75     }
     76     if (pathWPATML.empty()) {
     77         pathWPATML = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPATMLPMT_latest.csv");
     78     }
     79     setCdLCsvFileName(pathCDL);
     80     setCdSCsvFileName(pathCDS);
     81     setWpVCsvFileName(pathWPV);
     82     setWpWALCsvFileName(pathWPWAL);
     83     setWpATMLCsvFileName(pathWPATML);
     84 
     85     cdReadCsvAndMap(CdLCsvFileName);
     86     cdReadCsvAndMap(CdSCsvFileName);
     87     wpReadCsvAndMap(WpVCsvFileName);
     88     wpReadCsvAndMap(WpWALCsvFileName);
     89     wpReadCsvAndMap(WpATMLCsvFileName);
     90     return true;
     91 }


     BP=IDService::initMap ipc



    Thread 1 "python" hit Breakpoint 1, IDService::initMap (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:56
    56	    std::cout << "IDMapping Service is initializing!" << std::endl;
    (gdb) bt
    #0  IDService::initMap (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:56
    #1  0x00007fffc405c920 in operator() (__closure=0x7ffffffef688) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:41
    #2  0x00007fffc405fad6 in std::__invoke_impl<void, IDService::init()::<lambda()> >(std::__invoke_other, struct {...} &&) (__f=...) at /usr/include/c++/11/bits/invoke.h:61
    #3  0x00007fffc405fa0b in std::__invoke<IDService::init()::<lambda()> >(struct {...} &&) (__fn=...) at /usr/include/c++/11/bits/invoke.h:96
    #4  0x00007fffc405f957 in operator() (__closure=0x7ffffffef640) at /usr/include/c++/11/mutex:776
    #5  0x00007fffc405fa35 in operator() (__closure=0x0) at /usr/include/c++/11/mutex:712
    #6  0x00007fffc405fa46 in _FUN () at /usr/include/c++/11/mutex:712
    #7  0x00007ffff748e9f8 in __pthread_once_slow () from /lib64/libc.so.6
    #8  0x00007fffc405c636 in __gthread_once (__once=0x7fffc407f664 <IDService::init()::initFlag>, __func=0x7fffe92da800 <__once_proxy>) at /usr/include/c++/11/x86_64-redhat-linux/bits/gthr-default.h:700
    #9  0x00007fffc405f99c in std::call_once<IDService::init()::<lambda()> >(std::once_flag &, struct {...} &&) (__once=..., __f=...) at /usr/include/c++/11/mutex:783
    #10 0x00007fffc405c9ac in IDService::init (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:40
    #11 0x00007fffc02afb00 in PMTParamSvc::initialize (this=0x666f6f0) at /home/blyth/junosw/Detector/Geometry/src/PMTParamSvc.cc:114
    #12 0x00007fffd0adeb56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    ...
    (gdb) f 0
    #0  IDService::initMap (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:56
    56	    std::cout << "IDMapping Service is initializing!" << std::endl;
    (gdb) list
    51	    return &instance;
    52	}
    53	
    54	bool IDService::initMap()
    55	{
    56	    std::cout << "IDMapping Service is initializing!" << std::endl;
    57	    // if Path is not set, using the default one.
    58	    std::string pathCDL = CdLCsvFileName;
    59	    std::string pathCDS = CdSCsvFileName;
    60	    std::string pathWPV = WpVCsvFileName;
    (gdb) list
    61	    std::string pathWPWAL = WpWALCsvFileName;
    62	    std::string pathWPATML = WpATMLCsvFileName;
    63	
    64	    if (pathCDL.empty()) {
    65	        pathCDL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDLPMT_latest.csv");
    66	    }
    67	    if (pathCDS.empty()) {
    68	        pathCDS = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDSPMT_latest.csv");
    69	    }
    70	    if (pathWPV.empty()) {
    (gdb) b 64
    Breakpoint 2 at 0x7fffc405cb38: file /home/blyth/junosw/Detector/Identifier/src/IDService.cc, line 64.
    (gdb) c
    Continuing.
    IDMapping Service is initializing!

    Thread 1 "python" hit Breakpoint 2, IDService::initMap (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:64
    64	    if (pathCDL.empty()) {
    (gdb) p pathCDL
    $1 = ""
    (gdb) p pathCDS
    $2 = ""
    (gdb) p pathWPV
    $3 = ""
    (gdb) p pathWPWAL
    $4 = ""
    (gdb) p pathWPATML
    $5 = ""
    (gdb) list
    59	    std::string pathCDS = CdSCsvFileName;
    60	    std::string pathWPV = WpVCsvFileName;
    61	    std::string pathWPWAL = WpWALCsvFileName;
    62	    std::string pathWPATML = WpATMLCsvFileName;
    63	
    64	    if (pathCDL.empty()) {
    65	        pathCDL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDLPMT_latest.csv");
    66	    }
    67	    if (pathCDS.empty()) {
    68	        pathCDS = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDSPMT_latest.csv");
    (gdb) list 70
    65	        pathCDL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDLPMT_latest.csv");
    66	    }
    67	    if (pathCDS.empty()) {
    68	        pathCDS = JUNO::Path::resolve("/data/Detector/Identifier/pmt_CDSPMT_latest.csv");
    69	    }
    70	    if (pathWPV.empty()) {
    71	        pathWPV = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPVPMT_latest.csv");
    72	    }
    73	    if (pathWPWAL.empty()) {
    74	        pathWPWAL = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPWALPMT_latest.csv");
    (gdb) list 
    75	    }
    76	    if (pathWPATML.empty()) {
    77	        pathWPATML = JUNO::Path::resolve("/data/Detector/Identifier/pmt_WPATMLPMT_latest.csv");
    78	    }
    79	    setCdLCsvFileName(pathCDL);
    80	    setCdSCsvFileName(pathCDS);
    81	    setWpVCsvFileName(pathWPV);
    82	    setWpWALCsvFileName(pathWPWAL);
    83	    setWpATMLCsvFileName(pathWPATML);
    84	
    (gdb) b 79
    Breakpoint 3 at 0x7fffc405ce71: file /home/blyth/junosw/Detector/Identifier/src/IDService.cc, line 79.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 3, IDService::initMap (this=0x7fffc407f680 <IDService::getIdServ()::instance>) at /home/blyth/junosw/Detector/Identifier/src/IDService.cc:79
    79	    setCdLCsvFileName(pathCDL);
    (gdb) p pathCDL
    $6 = "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_CDLPMT.csv"
    (gdb) p pathCDS
    $7 = "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_CDSPMT.csv"
    (gdb) p pathWPV
    $8 = "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPVPMT.csv"
    (gdb) p pathWPWAL
    $9 = "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPWALPMT.csv"
    (gdb) p pathWPATML
    $10 = "/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPATMLPMT.csv"
    (gdb) 




/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Detector/Identifier/pmt_20250422_WPATMLPMT.csv::


      1 #Mapping file for ATM LPMTs in WP Wall.
      2 #Updated by Yuning Su (suyn26 AT mail2.sysu.edu.cn) in 20250218.
      3 #A total of 348 PMTs were actually installed in Wall, more detail in https://docs.ihep.ac.cn/link/AR573CA85D4A004CE8B5AC50662739AB3F.
      4 #CopyNo, SphereOrWall(0=Sphere  1=Wall), NorthOrSouth(0=North  1=South), LayerNo, WindowNo, PositionNo, Design_type(1=H  2=NNVT), LargeOrSmall(0=Large  1=Small), GCU, Channel(0-2), X, Y, Z, Orientation_theta, Orientation_phi, SNnumber,     PMTType
      5 52400,1,0,4,1,1,2,0,1185,0,-21034.9,1378.698,20163,90,176.25,PA1805-1232,HighQENNVT
      6 52401,1,0,4,1,2,2,0,1185,1,-21063.7,827.5969,20163,90,177.75,PA1706-39,NNVT
      7 52402,1,0,4,1,3,2,0,1185,2,-21078.2,275.9287,20163,90,179.25,PA1801-1022,NNVT
      8 52403,1,0,4,1,4,2,0,5873,2,-21078.2,-275.929,20163,90,-179.25,PA1804-1021,HighQENNVT
      9 52404,1,0,4,1,5,2,0,5873,1,-21063.7,-827.597,20163,90,-177.75,PA1907-2021,HighQENNVT
     10 52405,1,0,4,1,6,2,0,5873,0,-21034.9,-1378.7,20163,90,-176.25,PA1707-1419,NNVT
     11 52406,1,0,4,2,1,2,0,2407,0,-20861.9,-3024.82,20163,90,-171.75,PA1711-1541,NNVT
     12 52407,1,0,4,2,2,2,0,2407,1,-20775.5,-3569.89,20163,90,-170.25,PA1710-1190,NNVT
     13 52408,1,0,4,2,3,2,0,2407,2,-20675,-4112.5,20163,90,-168.75,PA1807-1093,HighQENNVT
     14 52409,1,0,4,2,4,2,0,2906,2,-20560.2,-4652.3,20163,90,-167.25,PA2008-1257,HighQENNVT
     15 52410,1,0,4,2,5,2,0,2906,1,-20431.4,-5188.91,20163,90,-165.75,PA1905-5014,HighQENNVT
     16 52411,1,0,4,2,6,2,0,2906,0,-20288.6,-5721.96,20163,90,-164.25,PA2001-1084,HighQENNVT
     17 52412,1,0,4,3,1,2,0,1948,0,-19777.1,-7296.15,20163,90,-159.75,PA1804-2109F,NNVT
     18 52413,1,0,4,3,2,2,0,1948,1,-19579.3,-7811.35,20163,90,-158.25,PA1704-12,NNVT
     19 52414,1,0,4,3,3,2,0,1948,2,-19368.1,-8321.2,20163,90,-156.75,PA2008-1194,HighQENNVT
     20 52415,1,0,4,3,4,2,0,1751,2,-19143.7,-8825.35,20163,90,-155.25,PA2007-1309,HighQENNVT
     21 52416,1,0,4,3,5,2,0,1751,1,-18906.1,-9323.45,20163,90,-153.75,PA1711-1258,NNVT
     22 52417,1,0,4,3,6,2,0,1751,0,-18655.5,-9815.15,20163,90,-152.25,PA1708-1399,NNVT
     23 52418,1,0,4,5,1,2,0,1899,0,-15099.6,-14709.4,20163,90,-135.75,PA1909-1234,HighQENNVT
     24 52419,1,0,4,5,2,2,0,1899,1,-14709.4,-15099.6,20163,90,-134.25,PA1805-2404,HighQENNVT
     25 52420,1,0,4,5,3,2,0,1899,2,-14309.1,-15479.5,20163,90,-132.75,PA1805-1230,HighQENNVT
     26 52421,1,0,4,5,4,2,0,7458,2,-13899,-15848.8,20163,90,-131.2499,PA1905-1079,HighQENNVT


    337 52732,1,0,3,28,3,2,0,1433,2,-16890.4,12612.68,18483,90,143.25,PA1706-488,NNVT
    338 52733,1,0,3,28,4,2,0,1184,2,-17214.8,12166.22,18483,90,144.75,PA1611-253,NNVT
    339 52734,1,0,3,28,5,2,0,1184,1,-17527.4,11711.42,18483,90,146.25,PA1808-1217,HighQENNVT
    340 52735,1,0,3,28,6,2,0,1184,0,-17827.9,11248.59,18483,90,147.7499,PA2003-2551,HighQENNVT
    341 52736,1,0,3,29,1,2,0,1102,0,-18655.5,9815.154,18483,90,152.25,PA1805-1229,HighQENNVT
    342 52737,1,0,3,29,2,2,0,1102,1,-18906.1,9323.446,18483,90,153.75,PA1712-1381,NNVT
    343 52738,1,0,3,29,3,2,0,1102,2,-19143.7,8825.347,18483,90,155.25,PA1801-1674,NNVT
    344 52739,1,0,3,29,4,2,0,5376,2,-19368.1,8321.2,18483,90,156.75,PA1911-2001,HighQENNVT
    345 52740,1,0,3,29,5,2,0,5376,1,-19579.3,7811.351,18483,90,158.25,PA1805-1226,HighQENNVT
    346 52741,1,0,3,29,6,2,0,5376,0,-19777.1,7296.148,18483,90,159.75,PA1702-1799,NNVT
    347 52742,1,0,3,30,1,2,0,1182,0,-20288.6,5721.965,18483,90,164.25,PA1706-588,NNVT
    348 52743,1,0,3,30,2,2,0,1182,1,-20431.4,5188.911,18483,90,165.75,PA2004-1239,HighQENNVT
    349 52744,1,0,3,30,3,2,0,1182,2,-20560.2,4652.302,18483,90,167.25,PA1705-549,NNVT
    350 52745,1,0,3,30,4,2,0,3102,2,-20675,4112.504,18483,90,168.75,PA1805-1166,HighQENNVT
    351 52746,1,0,3,30,5,2,0,3102,1,-20775.5,3569.888,18483,90,170.25,PA1803-1478,NNVT
    352 52747,1,0,3,30,6,2,0,3102,0,-20861.9,3024.824,18483,90,171.75,PA1707-1739,NNVT






