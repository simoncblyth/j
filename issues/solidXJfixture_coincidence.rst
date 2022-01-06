solidXJfixture_coincidence
=============================


Internal coincidences
-----------------------

* cxs clearly showing several lines of spurious coincidences within solidXJfixture and solidXJanchor 
  


Checking the 64 non-instanced solidXJfixture:0 :1 ... :63 
-------------------------------------------------------------

::
 
    cx
    ./cxr_arglist.sh 

Which is using::

    EYE=2,-1,-1 UP=1,0,0 TMIN=0.1 CAM=1 MOI=$MOI ARGLIST=$path ./cxr.sh



* :0 and :1 appear to be on top of each other but rotated 

* :2 :3 :4 :5 :6 7: look obscured or overlapped by something

* :8 to :32 externally look as expected

* :36 :40 nearby some other structure

* :37 not visible, obscured by something

* :41 partially obscured/overlapped 

* :50 :52 looks like obscured by stick

* :55 obscured by large disc structure (which is the foot of the stick)

* :58 looks overlapped by large disc structure

* :61 obscured/overlapped by sticks 



:55 obscured by large stick plunger
-------------------------------------

Backing away at same angle of view clearly shows the stick::

    EYE=2,-1,-1 UP=1,0,0 TMIN=0.1 CAM=1 MOI=solidXJfixture:55:-3 ./cxr_view.sh 

    EYE=4,-2,-2 UP=1,0,0 TMIN=0.1 CAM=1 MOI=solidXJfixture:55:-3 ./cxr_view.sh 

    EYE=8,-4,-4 UP=1,0,0 TMIN=0.1 CAM=1 MOI=solidXJfixture:55:-3 ./cxr_view.sh 


* bug in positioning of solidXJfixture and/or sticks ? or Opticks translation bug ?


checking cxs with :55 getting unexpected TT names sBar sPanelTape : naming bug ?
----------------------------------------------------------------------------------

* yes : fixed cxs.sh names after updating CSGFoundry on laptop::

   cx
   ./cf_grab.sh 



XJfixtureConstructionPR_0
----------------------------

::

    240 elif [ "$GEOM" == "XJfixtureConstructionPR_0" ]; then
    241 
    242     moi="solidXJfixture:0:-3"
    243     #    R:T:P        larger side of grid becomes horizontal : hence  PR  (not RP)
    244     cegs=9:0:16:100
    245     gridscale=0.10

    ISEL=0 ./cxs.sh 
 

solidSJReceiver  looks separated, checking with xxs.sh shows that is is separated

XJfixtureConstructionTR_0 shows the chimney opening of sTarget with the fixture in the 
middle of the gap.

jgr sTarget finds several, so check GDML origin_CGDMLKludge_12dec2021.gdml::

      1679     <sphere aunit="deg" deltaphi="360" deltatheta="180" lunit="mm" name="sTarget_bottom_ball0x57f5d10" rmax="17700" rmin="0" startphi="0" starttheta="0"/>
      1680     <tube aunit="deg" deltaphi="360" lunit="mm" name="sTarget_top_tube0x57f5ea0" rmax="400" rmin="0" startphi="0" z="124.520351230938"/>
      1681     <union name="sTarget0x57f5fb0">
      1682       <first ref="sTarget_bottom_ball0x57f5d10"/>
      1683       <second ref="sTarget_top_tube0x57f5ea0"/>
      1684       <position name="sTarget0x57f5fb0_pos" unit="mm" x="0" y="0" z="17757.7398243845"/>
      1685     </union>

::

    epsilon:offline blyth$ jgr _top_tube
    ./Simulation/DetSimV2/PMTSim/src/ExplosionProofSolid.cc:      solidname+"_top_tube",
    ./Simulation/DetSimV2/CentralDetector/src/RoundBottomFlaskSolidMaker.cc:                                        m_solid_name+"_top_tube",

::

    jcv RoundBottomFlaskSolidMaker


confusing, too much happening::

    EYE=0,-1,0 UP=1,0,0 TMIN=0.1 MOI=solidXJfixture:0:-3 ./cxr_view.sh 
    EYE=0,-4,0 UP=1,0,0 TMIN=0.1 MOI=solidXJfixture:0:-3 ./cxr_view.sh 





Annoying that cannot find users by normal C++ searching 
-----------------------------------------------------------


::

    epsilon:offline blyth$ jgr XJfixtureConstruction
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh:#ifndef XJfixtureConstruction_hh
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh:#define XJfixtureConstruction_hh
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh:class XJfixtureConstruction : public IDetElement,
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh:    XJfixtureConstruction(const std::string& name);
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh:    ~XJfixtureConstruction();
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:#include "XJfixtureConstruction.hh"
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:DECLARE_TOOL(XJfixtureConstruction);
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:XJfixtureConstruction::XJfixtureConstruction(const std::string& name)
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:XJfixtureConstruction::~XJfixtureConstruction() {
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:XJfixtureConstruction::getLV() {
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:XJfixtureConstruction::inject(std::string  motherName , IDetElement* other, IDetElementPos* pos) {
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:void XJfixtureConstruction::initVariables(){;}
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:void XJfixtureConstruction::initMaterials(){
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:void XJfixtureConstruction::makeXJfixtureLogical(){
    epsilon:offline blyth$ 
    epsilon:offline blyth$ 

    epsilon:offline blyth$ jgl XJfixture
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/CentralDetector/include/XJfixtureConstruction.hh
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc

 
jcv LSExpDetectorConstruction::

     147   m_strut_name = "StrutAcrylic"; 
     148   m_strut2_name="StrutBar2Acrylic";
     149   m_strutballhead_name="StrutBallheadAcrylic";
     150   m_fastener_name = "FastenerAcrylic";
     151   m_upper_name = "UpperAcrylic";
     152   m_addition_name = "AdditionAcrylic";
     153   m_xjanchor_name = "XJanchor";
     154   m_xjfixture_name = "XJfixture";
     155   m_sjclsanchor_name = "SJCLSanchor";
     156   m_sjfixture_name = "SJFixture";
     157   m_sjreceiver_name = "SJReceiver";
     158   m_sjreceiver_fastener_name = "XJfixture";
     159   m_pmt_mother = "lWaterPool";
     160   m_mask_mother = "lMaskVirtual";
     161   m_strut_mother = "lWaterPool";
     162   m_fastener_mother = "lWaterPool"; 
     163   m_upper_mother = "lWaterPool";
     164   m_addition_mother = "lWaterPool";
     165   m_xjanchor_mother = "lWaterPool";
     166   m_xjfixture_mother = "lWaterPool";
     167   m_sjclsanchor_mother = "lTarget";
     168   m_sjfixture_mother = "lTarget";
     169   m_sjreceiver_mother = "lTarget";
     170   m_sjreceiver_fastener_mother = "lTarget";


jcv DetSim0Svc::

    195     dc->setXJanchorPosFile(m_xjanchor_pos_file);
    196     dc->setXJfixturePosFile(m_xjanchor_pos_file);
    197     dc->setSJCLSanchorPosFile(m_sjclsanchor_pos_file);
    198     dc->setSJReceiverPosFile(m_sjreceiver_pos_file);
    199     dc->setSJFixturePosFile(m_sjfixture_pos_file);


::

    0449 void
     450 LSExpDetectorConstruction::setupCentralDetector()
     451 {
     452   // construct the Central Detector
     453   IDetElement* cd_det = 0;
     454   if (m_cd_name == "DetSim0" or m_cd_name == "DetSim1" or m_cd_name == "DetSim2") {
     455       std::string new_name = m_cd_name + "Construction";
     456       cd_det = det_elem(new_name);
     457   }
    ...

jcv DetSim0Construction::

     38 bool
     39 DetSim0Construction::inject(std::string motherName, IDetElement* other, IDetElementPos* pos) {

     //  places copies of other->getLV() at the positions obtained from pos
     //  into the logical of the DetSim0Construction object 
     //

     40     // Get the mother volume in current DetElem.
     41     G4LogicalVolume* mothervol = 0;
     42     if ( motherName == "lTarget" ) {
     43         mothervol = logicTarget;
     44     }
     45     if (not mothervol) {
     46         // don't find the volume.
     47         return false;
     48     }
     49 
     50     // retrieve the daughter's LV
     51     G4LogicalVolume* daughtervol = other->getLV();
     52 
     53     if (not daughtervol) {
     54         return false;
     55     }
     56 
     57     int copyno = 0;
     58     while (pos->hasNext()) {
     59         new G4PVPlacement(
     60             pos->next(),
     61             daughtervol,
     62             daughtervol->GetName()+"_phys",
     63             mothervol,
     64             false,
     65             copyno++
     66                 );
     67     }
     68 
     69 
     70     return true;
     71 }





    1286 void
    1287 LSExpDetectorConstruction::setupCD_Sticks(IDetElement* cd_det) {
    ...

    1407   IDetElement* xjanchor_det = 0;
    1408   if (m_xjanchor_name == "XJanchor") {
    1409       std::string new_name = m_xjanchor_name + "Construction";
    1410       xjanchor_det = det_elem(new_name);
    1411       assert(xjanchor_det);
    1412       IDetElementPos* xjanchor_detelem_pos = 0;
    1413       xjanchor_detelem_pos = new JUNO::Ball::HexagonPosBall(m_xjanchor_pos_file,xjanchor_r,false);
    1414       assert (xjanchor_detelem_pos);
    1415       bool xjanchor_status = cd_det->inject(m_xjanchor_mother, xjanchor_det, xjanchor_detelem_pos);
    1416       assert (xjanchor_status);
    1417   }
    1418 
    1419 
    1420   IDetElement* xjfixture_det = 0;
    1421   if (m_xjfixture_name == "XJfixture") {
    1422       std::string new_name = m_xjfixture_name + "Construction";
    ////
    //// obfuscation  : making the string harder to find
    ////
    1423       xjfixture_det = det_elem(new_name);
    1424       assert(xjfixture_det);
    1425       IDetElementPos* xjfixture_detelem_pos = 0;
    1426       xjfixture_detelem_pos = new JUNO::Ball::HexagonPosBall(m_xjanchor_pos_file,xjfixture_r,false);
     
    ////  NB fixture using xjanchor file 
    ///   

    1427       assert (xjfixture_detelem_pos);
    1428       bool xjfixture_status = cd_det->inject(m_xjfixture_mother, xjfixture_det, xjfixture_detelem_pos);
    1429       assert (xjfixture_status);
    1430   }
    1431 


::

     17 class HexagonPosBall: public IDetElementPos {
     18 public:
     19     // this r is the distance between center of ball
     20     // and the center of PMT Equator
     21     HexagonPosBall(G4String filename, G4double r, G4bool lpmt);
     22     HexagonPosBall(Task* scope, G4bool lpmt);
     23     ~HexagonPosBall();
     24 
     25     G4bool hasNext();
     26     G4Transform3D next();
     27 private:
     28     void initialize();
     29     void initialize(G4bool lpmt);
     30 private:
     31     G4String m_filename;
     32     G4double m_ball_r;
     33     std::vector< G4Transform3D > m_position;
     34     std::vector< G4Transform3D >::iterator m_position_iter;
     35 
     36     G4bool lpmt_flag;
     37     Task* m_scope;
     38 };


     24 HexagonPosBall::HexagonPosBall(G4String filename, G4double r, G4bool lpmt)
     25     : m_filename(filename), m_ball_r(r),lpmt_flag(lpmt) {
     26     initialize();
     27     m_position_iter = m_position.begin();
     28 }
     29 
     30 HexagonPosBall::HexagonPosBall(Task* scope, G4bool lpmt)
     31     : m_scope(scope), lpmt_flag(lpmt){
     32     initialize(lpmt);
     33     m_position_iter = m_position.begin();
     34 }
     35 




::

    epsilon:offline blyth$ jgr sjreceiver_fastener_r 
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     G4double sjreceiver_fastener_r;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:  sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      sjreceiver_fastener_detelem_pos = new JUNO::Ball::HexagonPosBall(m_sjreceiver_pos_file,sjreceiver_fastener_r,false);

::

     125 
     126   strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
     127   fastener_r = 17820.*mm + 20.*mm; //17826. *mm;
     128   addition_r = 17820. *mm;
     129   upper_r = 17820.*mm + 140.*mm;
     130   xjanchor_r = 17820.*mm ;
     131   xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm;
     132   sjclsanchor_r = 17699.938*mm;
     133   sjfixture_r = 17699.975*mm;
     134   sjreceiver_r = 17699.938*mm;
     135   sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
     136   m_cd_name = "DetSim1";
     137   m_cd_enabled = true;
     138   m_wp_enabled = true;
     139   m_tt_enabled = true;
     140   m_tt_name = "TT_OPERA";
     141   // m_pmt_name = "OnlyPMT";
     142   m_pmt_name = "PMTMask";
     143   m_extra_lpmt = "ONE";
     144   m_3inchpmt_name = "Tub3inchV3";
     145   m_3inchpmt_pos_offset = -50.0*mm;
     146   m_veto_pmt_name = "R12860OnlyFrontMask";
     147   m_strut_name = "StrutAcrylic";
     148   m_strut2_name="StrutBar2Acrylic";
     149   m_strutballhead_name="StrutBallheadAcrylic";
     150   m_fastener_name = "FastenerAcrylic";
     151   m_upper_name = "UpperAcrylic";
     152   m_addition_name = "AdditionAcrylic";
     153   m_xjanchor_name = "XJanchor";
     154   m_xjfixture_name = "XJfixture";

     155   m_sjclsanchor_name = "SJCLSanchor";
     156   m_sjfixture_name = "SJFixture";
     157   m_sjreceiver_name = "SJReceiver";
     158   m_sjreceiver_fastener_name = "XJfixture";
     159   m_pmt_mother = "lWaterPool";
     160   m_mask_mother = "lMaskVirtual";
     161   m_strut_mother = "lWaterPool";
     162   m_fastener_mother = "lWaterPool";
     163   m_upper_mother = "lWaterPool";
     164   m_addition_mother = "lWaterPool";
     165   m_xjanchor_mother = "lWaterPool";
     166   m_xjfixture_mother = "lWaterPool";

     167   m_sjclsanchor_mother = "lTarget";
     168   m_sjfixture_mother = "lTarget";
     169   m_sjreceiver_mother = "lTarget";
     170   m_sjreceiver_fastener_mother = "lTarget";
     171 


::

    epsilon:offline blyth$ jgr setXJanchorPosFile
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc:    dc->setXJanchorPosFile(m_xjanchor_pos_file);
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh:     void setXJanchorPosFile(const std::string& pos_file) {m_xjanchor_pos_file=pos_file;}
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    dc->setXJanchorPosFile(m_xjanchor_pos_file);
    epsilon:offline blyth$ 

    031 DetSim0Svc::DetSim0Svc(const std::string& name)
     32     : SvcBase(name)
     33 {
     34     declProp("AnaMgrList", m_ana_list);
     35     declProp("CDName", m_cd_name="DetSim1");
     36     declProp("PMTName", m_pmt_name="PMTMask");
     37     declProp("LPMTExtra", m_extra_lpmt="ONE"); // ONE or TWO
     38     declProp("3inchPMTName", m_3inchpmt_name="Tub3inchV3");
     39     // NOTE: to do the elec simulation, please scale the QE
     40     declProp("ElecSimPMTQEScale", m_pmt_qe_scale_for_elec=1.0);
     41     declProp("StrutName", m_strut_name="StrutAcrylic");
     42     declProp("FastenerName", m_fastener_name="FastenerAcrylic");
     43     declProp("PMTMother", m_pmt_mother="lWaterPool");
     44     declProp("StrutMother", m_strut_mother="lWaterPool");
     45     declProp("FastenerMother", m_fastener_mother="lWaterPool");
     46     declProp("PMTPosMode", m_pmt_pos_mode="FileMode");
     47     declProp("PMTPosFile", m_pmt_pos_file);
     48     declProp("3inchPMTPosFile", m_3inch_pmt_pos_file);
     49     declProp("3inchPMTPosOffset", m_3inch_pmt_pos_offset=-50.0);
     50     declProp("StrutPosFile", m_strut_pos_file);
     51     declProp("Strut2PosFile", m_strut2_pos_file);
     52     declProp("FastenerPosFile", m_fastener_pos_file);
     53     declProp("XJanchorPosFile", m_xjanchor_pos_file);
     54     declProp("SJCLSanchorPosFile", m_sjclsanchor_pos_file);
     55     declProp("SJReceiverPosFile", m_sjreceiver_pos_file);
     56     declProp("SJFixturePosFile", m_sjfixture_pos_file);
     57 


    jgr PosFile





    ./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    #detsim0.property("FastenerPosFile").set("strut.csv")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        #self._factory.property("PMTPosFile").set(DetSimOptions.data_load("PMTPos_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        #self._factory.property("StrutPosFile").set(DetSimOptions.data_load("Strut_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        #self._factory.property("FastenerPosFile").set(DetSimOptions.data_load("Strut_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("StrutPosFile").set(DetSimOptions.data_load("Strut_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("Strut2PosFile").set(DetSimOptions.data_load("StrutBar2_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("FastenerPosFile").set(DetSimOptions.data_load("Strut_Anchor_Acrylic.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("XJanchorPosFile").set(DetSimOptions.data_load("XJanchor.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJCLSanchorPosFile").set(DetSimOptions.data_load("SJCLSanchor.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJReceiverPosFile").set(DetSimOptions.data_load("SJReceiverPos.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJFixturePosFile").set(DetSimOptions.data_load("SJFixturePos.csv"))
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("PMTPosFile").set("")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("StrutPosFile").set("")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("Strut2PosFile").set("")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("FastenerPosFile").set("")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("XJanchorPosFile").set("")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        self._factory.property("SJCLSanchorPosFile").set("")

::

     09 class ConfAcrylic(object):
     10 
     11     def __init__(self, task):
     12         self._task = task
     13 
     14         self._g4svc = None
     15         self._factory = None
     16         self._detsimalg = None
     17         self._mask = None
     18 
     19         self._geom = None
     20         self._gdml = None
     21         self._dae = None
     22 
     23         self._pmtsd_mgr = None
     24         self._optical_process = None
     25         self._em_process = None
     26         self._ion_process = None
     27 
     28     def configure(self):
     29         # == G4Svc ==
     30         self._g4svc = self._task.createSvc("G4Svc")
     31 
     32         # == DetSimOptions ==
     33         self._factory = self._task.createSvc("DetSim0Svc")
     34         self._factory.property("AnaMgrList").set(["DataModelWriter",
     35                                                   "GenEvtInfoAnaMgr",
     36                                                   "NormalAnaMgr",
     37                                                   "DepositEnergyAnaMgr",
     38                                                   "InteresingProcessAnaMgr"])
     39         self._factory.property("CDName").set("DetSim1")
     40         self._factory.property("StrutPosFile").set(DetSimOptions.data_load("Strut_Acrylic.csv"))
     41         self._factory.property("Strut2PosFile").set(DetSimOptions.data_load("StrutBar2_Acrylic.csv"))
     42         self._factory.property("FastenerPosFile").set(DetSimOptions.data_load("Strut_Anchor_Acrylic.csv"))
     43         self._factory.property("XJanchorPosFile").set(DetSimOptions.data_load("XJanchor.csv"))
     44         self._factory.property("SJCLSanchorPosFile").set(DetSimOptions.data_load("SJCLSanchor.csv"))
     45         self._factory.property("SJReceiverPosFile").set(DetSimOptions.data_load("SJReceiverPos.csv"))
     46         self._factory.property("SJFixturePosFile").set(DetSimOptions.data_load("SJFixturePos.csv"))
     47 

Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py::

     21 # == load data from default directory ==
     22 import os
     23 def data_load(filename):
     24     # Load the data located in $DETSIMOPTIONSROOT/data
     25     detroot = os.environ["DETSIMOPTIONSROOT"]
     26     if not detroot:
     27         raise Exception("Can't get $DETSIMOPTIONSROOT")
     28     f = os.path.join(detroot, "data",  filename)
     29     if not os.path.exists(f):
     30         raise Exception("Can't get $DETSIMOPTIONSROOT/data/%s"%filename)
     31 
     32     return f
     33 

::

    $DETSIMOPTIONSROOT/data/XJanchor.csv

    N[blyth@localhost offline]$ echo $DETSIMOPTIONSROOT
    /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions

    N[blyth@localhost data]$ l
    total 1072
      0 drwxrwxr-x. 8 blyth blyth    104 Dec  7 20:43 ..
      0 drwxrwxr-x. 2 blyth blyth    261 Dec  4 01:05 .
      8 -rw-rw-r--. 1 blyth blyth   7570 Dec  4 01:05 Strut_Anchor_Acrylic.csv
      4 -rw-rw-r--. 1 blyth blyth   3014 Dec  4 01:05 StrutBar2_Acrylic.csv
      4 -rw-rw-r--. 1 blyth blyth    911 Dec  4 01:05 XJanchor.csv
    468 -rw-rw-r--. 1 blyth blyth 475579 Dec  4 01:05 Det1PMTPos_new.csv
      4 -rw-rw-r--. 1 blyth blyth     17 Dec  4 01:05 SJCLSanchor.csv
    468 -rw-rw-r--. 1 blyth blyth 475579 Dec  4 01:05 PMTPos_Balloon.csv
      4 -rw-rw-r--. 1 blyth blyth    412 Dec  4 01:05 SJFixturePos.csv
      8 -rw-rw-r--. 1 blyth blyth   4556 Dec  4 01:05 Strut_Acrylic.csv
    100 -rw-rw-r--. 1 blyth blyth 100331 Dec  4 01:05 Strut_Balloon.csv
      4 -rw-rw-r--. 1 blyth blyth     68 Dec  4 01:05 SJReceiverPos.csv
    N[blyth@localhost data]$ pwd
    /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data
    N[blyth@localhost data]$ 




::

    epsilon:data blyth$ pwd
    /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data


    epsilon:data blyth$ svn log -v .  
    ------------------------------------------------------------------------
    r5004 | qianzhen | 2021-09-30 02:32:51 +0100 (Thu, 30 Sep 2021) | 1 line
    Changed paths:
       M /trunk/Examples/Tutorial/python/Tutorial/JUNOEventRecModule.py
       M /trunk/Examples/Tutorial/python/Tutorial/JUNOWaveRecModule.py
       M /trunk/Reconstruction/IntegralPmtRec/src/IntegralPmtRec.cc
       M /trunk/Reconstruction/IntegralPmtRec/src/IntegralPmtRec.h
       M /trunk/Simulation/DetSimV2/DetSimMT/share/run.py
       D /trunk/Simulation/DetSimV2/DetSimOptions/data/3inch_pos.csv
       D /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic.csv
       D /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv
       D /trunk/Simulation/DetSimV2/DetSimOptions/data/vetoPmt_pos.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfBalloon.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
       M /trunk/Simulation/ElecSimV3/ElecSimAlg/src/MMTriggerToolLpmt.cc

    remove the use and discription of the old pmt pos files
    ------------------------------------------------------------------------
    r4811 | haoqi | 2021-07-07 05:36:02 +0100 (Wed, 07 Jul 2021) | 1 line
    Changed paths:
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/vetoPmt_pos.csv

    add veto PMTs real position file
    ------------------------------------------------------------------------
    r4289 | huyuxiang | 2021-01-07 04:02:46 +0000 (Thu, 07 Jan 2021) | 1 line
    Changed paths:
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv

    add ball head of strut
    ------------------------------------------------------------------------
    r4288 | huyuxiang | 2021-01-07 04:01:54 +0000 (Thu, 07 Jan 2021) | 1 line
    Changed paths:
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
       M /trunk/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/pyvis.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc

    add ball head of strut
    ------------------------------------------------------------------------
    r4280 | huyuxiang | 2021-01-06 03:56:31 +0000 (Wed, 06 Jan 2021) | 1 line
    Changed paths:
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/include/DetSim0Svc.hh
       M /trunk/Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
       M /trunk/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/pyjob_balloon.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/pyvis.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py
       M /trunk/Simulation/DetSimV2/DetSimOptions/share/vis.mac
       M /trunk/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
       M /trunk/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc

    Modified strut
    ------------------------------------------------------------------------
    r3803 | miaoyu | 2020-03-14 02:45:46 +0000 (Sat, 14 Mar 2020) | 1 line
    Changed paths:
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/3inch_pos.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv

    PMT Position Update
    ------------------------------------------------------------------------
    r3791 | miaoyu | 2020-03-12 07:15:00 +0000 (Thu, 12 Mar 2020) | 1 line
    Changed paths:
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv

    SJ XJ node pos file
    ------------------------------------------------------------------------
    r3790 | miaoyu | 2020-03-12 07:14:05 +0000 (Thu, 12 Mar 2020) | 1 line
    Changed paths:
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/3inch_pos.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv

    PMT Pos Files
    ------------------------------------------------------------------------
    r3693 | miaoyu | 2019-12-16 15:43:44 +0000 (Mon, 16 Dec 2019) | 1 line
    Changed paths:
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv

    nodes positions update
    ------------------------------------------------------------------------
    r3591 | miaoyu | 2019-08-27 10:51:48 +0100 (Tue, 27 Aug 2019) | 1 line
    Changed paths:
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/3inch_pos.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction.hh
       M /trunk/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc

    updat lpmt and acrylic nodes placement
    ------------------------------------------------------------------------
    r2025 | lintao | 2016-07-21 05:25:01 +0100 (Thu, 21 Jul 2016) | 1 line
    Changed paths:
       A /trunk/Simulation/DetSimV2/DetSimOptions/data/PMTPos_Acrylic_with_chimney.csv
       M /trunk/Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py





Huh expecting one of these to have 64 lines::

    epsilon:data blyth$ wc -l *.csv
       36612 Det1PMTPos_new.csv
       36612 PMTPos_Balloon.csv
           2 SJCLSanchor.csv
          36 SJFixturePos.csv
           8 SJReceiverPos.csv
         220 StrutBar2_Acrylic.csv
         371 Strut_Acrylic.csv
         591 Strut_Anchor_Acrylic.csv
        4602 Strut_Balloon.csv
          56 XJanchor.csv
       79110 total
    epsilon:data blyth$ 

::

    epsilon:data blyth$ cat SJCLSanchor.csv
    0 44 90
    0 14 270
    epsilon:data blyth$ cat SJReceiverPos.csv
    0 0 150
    1 0 210
    2 58 30
    3 58 90
    4 58 150
    5 58 210
    6 58 270
    7 58 330
    epsilon:data blyth$ 


cx geocache_grab.sh 
-------------------------

::

    epsilon:CSGOptiX blyth$ gip OPTICKS_KEYDIR_GRABBED
    /Users/blyth/.opticksdev_config:export OPTICKS_KEYDIR_GRABBED=.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    /Users/blyth/.opticksdev_config:gkcd(){ echo OPTICKS_KEYDIR_GRABBED $OPTICKS_KEYDIR_GRABBED ; cd $HOME/$OPTICKS_KEYDIR_GRABBED ; pwd ;   : ~/.opticksdev_config ;  }
    epsilon:CSGOptiX blyth$ gkcd
    OPTICKS_KEYDIR_GRABBED .opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    /Users/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    epsilon:1 blyth$ pwd
    /Users/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    epsilon:1 blyth$ 



::

    epsilon:GNodeLib blyth$ grep fixture all_volume_LVNames.txt | wc -l 
          64

    epsilon:GNodeLib blyth$ grep fixture all_volume_PVNames.txt | wc -l 
          64


::

      3105     <volume name="lSJCLSanchor0x595bdb0">
      3106       <materialref ref="Acrylic0x572bb00"/>
      3107       <solidref ref="solidSJCLSanchor0x595bb90"/>
      3108     </volume>
      3109     <volume name="lSJFixture0x5960240">
      3110       <materialref ref="Acrylic0x572bb00"/>
      3111       <solidref ref="solidSJFixture0x5960020"/>
      3112     </volume>
      3113     <volume name="lSJReceiver0x595f5a0">
      3114       <materialref ref="Acrylic0x572bb00"/>
      3115       <solidref ref="solidSJReceiver0x595f380"/>
      3116     </volume>
      3117     <volume name="lXJfixture0x5958a70">
      3118       <materialref ref="PE_PA0x57451a0"/>
      3119       <solidref ref="solidXJfixture0x5958850"/>
      3120     </volume>


::

      3354       <physvol name="lXJfixture_phys0x5962300">
      3355         <volumeref ref="lXJfixture0x5958a70"/>
      3356         <position name="lXJfixture_phys0x5962300_pos" unit="mm" x="0" y="0" z="17683.438"/>
      3357         <rotation name="lXJfixture_phys0x5962300_rot" unit="deg" x="180" y="0" z="-30"/>
      3358       </physvol>
      3359       <physvol copynumber="1" name="lXJfixture_phys0x5964740">
      3360         <volumeref ref="lXJfixture0x5958a70"/>
      3361         <position name="lXJfixture_phys0x5964740_pos" unit="mm" x="0" y="0" z="17683.438"/>
      3362         <rotation name="lXJfixture_phys0x5964740_rot" unit="deg" x="-180" y="0" z="30"/>
      3363       </physvol>
      3364       <physvol copynumber="2" name="lXJfixture_phys0x5964820">
      3365         <volumeref ref="lXJfixture0x5958a70"/>
      3366         <position name="lXJfixture_phys0x5964820_pos" unit="mm" x="12987.2685003242" y="7498.2029647001" z="9370.7944540735"/>
      3367         <rotation name="lXJfixture_phys0x5964820_rot" unit="deg" x="-141.334348593975" y="47.2591746481021" z="-132.547177129057"/>
      3368       </physvol>



Why two sets of lXJfixture_phys ?


8+56 = 64::

    epsilon:1 blyth$ grep lXJfixture_phys0x origin.gdml | grep physvol
          <physvol name="lXJfixture_phys0x5962300">
          <physvol copynumber="1" name="lXJfixture_phys0x5964740">
          <physvol copynumber="2" name="lXJfixture_phys0x5964820">
          <physvol copynumber="3" name="lXJfixture_phys0x5964900">
          <physvol copynumber="4" name="lXJfixture_phys0x5962480">
          <physvol copynumber="5" name="lXJfixture_phys0x5962560">
          <physvol copynumber="6" name="lXJfixture_phys0x5962640">
          <physvol copynumber="7" name="lXJfixture_phys0x5962720">
          <physvol name="lXJfixture_phys0x5958b90">
          <physvol copynumber="1" name="lXJfixture_phys0x5958bf0">
          <physvol copynumber="2" name="lXJfixture_phys0x5958cd0">
          <physvol copynumber="3" name="lXJfixture_phys0x5958db0">
          <physvol copynumber="4" name="lXJfixture_phys0x5958e90">
          <physvol copynumber="5" name="lXJfixture_phys0x5958f70">
          <physvol copynumber="6" name="lXJfixture_phys0x5959050">
          <physvol copynumber="7" name="lXJfixture_phys0x5959130">
          <physvol copynumber="8" name="lXJfixture_phys0x5955790">
          <physvol copynumber="9" name="lXJfixture_phys0x5955870">
          <physvol copynumber="10" name="lXJfixture_phys0x5955950">
          <physvol copynumber="11" name="lXJfixture_phys0x5955a30">
          <physvol copynumber="12" name="lXJfixture_phys0x5955b10">
          <physvol copynumber="13" name="lXJfixture_phys0x5955bf0">
          <physvol copynumber="14" name="lXJfixture_phys0x5955cd0">
          <physvol copynumber="15" name="lXJfixture_phys0x5955db0">
          <physvol copynumber="16" name="lXJfixture_phys0x5955e90">
          <physvol copynumber="17" name="lXJfixture_phys0x5955f70">
          <physvol copynumber="18" name="lXJfixture_phys0x5956050">
          <physvol copynumber="19" name="lXJfixture_phys0x5956130">
          <physvol copynumber="20" name="lXJfixture_phys0x5956210">
          <physvol copynumber="21" name="lXJfixture_phys0x59562f0">
          <physvol copynumber="22" name="lXJfixture_phys0x59563d0">
          <physvol copynumber="23" name="lXJfixture_phys0x59564b0">
          <physvol copynumber="24" name="lXJfixture_phys0x5956590">
          <physvol copynumber="25" name="lXJfixture_phys0x5956670">
          <physvol copynumber="26" name="lXJfixture_phys0x5956750">
          <physvol copynumber="27" name="lXJfixture_phys0x5956830">
          <physvol copynumber="28" name="lXJfixture_phys0x5956910">
          <physvol copynumber="29" name="lXJfixture_phys0x59569f0">
          <physvol copynumber="30" name="lXJfixture_phys0x5956ad0">
          <physvol copynumber="31" name="lXJfixture_phys0x5956bb0">
          <physvol copynumber="32" name="lXJfixture_phys0x5956c90">
          <physvol copynumber="33" name="lXJfixture_phys0x5956d70">
          <physvol copynumber="34" name="lXJfixture_phys0x5956e50">
          <physvol copynumber="35" name="lXJfixture_phys0x5956f30">
          <physvol copynumber="36" name="lXJfixture_phys0x5957010">
          <physvol copynumber="37" name="lXJfixture_phys0x59570f0">
          <physvol copynumber="38" name="lXJfixture_phys0x59571d0">
          <physvol copynumber="39" name="lXJfixture_phys0x59572b0">
          <physvol copynumber="40" name="lXJfixture_phys0x5957390">
          <physvol copynumber="41" name="lXJfixture_phys0x5957470">
          <physvol copynumber="42" name="lXJfixture_phys0x5957550">
          <physvol copynumber="43" name="lXJfixture_phys0x5957630">
          <physvol copynumber="44" name="lXJfixture_phys0x5957710">
          <physvol copynumber="45" name="lXJfixture_phys0x59577f0">
          <physvol copynumber="46" name="lXJfixture_phys0x59578d0">
          <physvol copynumber="47" name="lXJfixture_phys0x595aa10">
          <physvol copynumber="48" name="lXJfixture_phys0x595aaf0">
          <physvol copynumber="49" name="lXJfixture_phys0x595abd0">
          <physvol copynumber="50" name="lXJfixture_phys0x595acb0">
          <physvol copynumber="51" name="lXJfixture_phys0x595ad90">
          <physvol copynumber="52" name="lXJfixture_phys0x595ae70">
          <physvol copynumber="53" name="lXJfixture_phys0x595af50">
          <physvol copynumber="54" name="lXJfixture_phys0x595b030">
          <physvol copynumber="55" name="lXJfixture_phys0x595b110">
    epsilon:1 blyth$ 


::

    epsilon:~ blyth$ jgr lXJfixture
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:    if(motherName == "lXJfixture")
    ./Simulation/DetSimV2/CentralDetector/src/XJfixtureConstruction.cc:        "lXJfixture",
    epsilon:offline blyth$ 


::

    epsilon:PosFile blyth$ i pos.py 
                      StrutPosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv 
                     Strut2PosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv 
                   FastenerPosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv 
                   XJanchorPosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv 
                SJCLSanchorPosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv 
                 SJReceiverPosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv 
                  SJFixturePosFile /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv 
              (370,)  :         StrutPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv 
              (220,)  :        Strut2PosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv 
              (590,)  :      FastenerPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv 
               (56,)  :      XJanchorPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv 
                (2,)  :   SJCLSanchorPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv 
                (8,)  :    SJReceiverPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv 
               (36,)  :     SJFixturePosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv 

    In [1]: 8+56                     

::

    In [2]: pfs                                                                                                                                                                                               
    Out[2]: 
    {'StrutPosFile':           (370,)  :         StrutPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Acrylic.csv ,
     'Strut2PosFile':           (220,)  :        Strut2PosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/StrutBar2_Acrylic.csv ,
     'FastenerPosFile':           (590,)  :      FastenerPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/Strut_Anchor_Acrylic.csv ,
     'XJanchorPosFile':            (56,)  :      XJanchorPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/XJanchor.csv ,
     'SJCLSanchorPosFile':             (2,)  :   SJCLSanchorPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJCLSanchor.csv ,
     'SJReceiverPosFile':             (8,)  :    SJReceiverPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv ,
     'SJFixturePosFile':            (36,)  :     SJFixturePosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJFixturePos.csv }

    In [3]: pfs["SJReceiverPosFile"]                                                                                                                                                                          
    Out[3]:             (8,)  :    SJReceiverPosFile : /Users/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/data/SJReceiverPos.csv 

    In [4]: pfs["SJReceiverPosFile"].a                                                                                                                                                                        
    Out[4]: array([(0,  0, 150), (1,  0, 210), (2, 58,  30), (3, 58,  90), (4, 58, 150), (5, 58, 210), (6, 58, 270), (7, 58, 330)], dtype=[('copyNo', '<i8'), ('theta', '<i8'), ('phi', '<i8')])




     125 
     126   strut_r_balloon =17715. *mm + 700 *mm + 5. *mm;
     127   fastener_r = 17820.*mm + 20.*mm; //17826. *mm;
     128   addition_r = 17820. *mm;
     129   upper_r = 17820.*mm + 140.*mm;
     130   xjanchor_r = 17820.*mm ;
     131   xjfixture_r = 17820.*mm + 10.*mm + 13./2*mm;
     132   sjclsanchor_r = 17699.938*mm;
     133   sjfixture_r = 17699.975*mm;
     134   sjreceiver_r = 17699.938*mm;
     135   sjreceiver_fastener_r = 17699.938*mm - 10.*mm - 13./2*mm;
     136   m_cd_name = "DetSim1";
     137   m_cd_enabled = true;
 

    In [1]: 17699.938 - 10. - 13./2                                                                                                                                                                           
    Out[1]: 17683.438



      3354       <physvol name="lXJfixture_phys0x5962300">
      3355         <volumeref ref="lXJfixture0x5958a70"/>
      3356         <position name="lXJfixture_phys0x5962300_pos" unit="mm" x="0" y="0" z="17683.438"/>
      3357         <rotation name="lXJfixture_phys0x5962300_rot" unit="deg" x="180" y="0" z="-30"/>
      3358       </physvol>
      3359       <physvol copynumber="1" name="lXJfixture_phys0x5964740">
      3360         <volumeref ref="lXJfixture0x5958a70"/>
      3361         <position name="lXJfixture_phys0x5964740_pos" unit="mm" x="0" y="0" z="17683.438"/>
      3362         <rotation name="lXJfixture_phys0x5964740_rot" unit="deg" x="-180" y="0" z="30"/>
      3363       </physvol>
      3364       <physvol copynumber="2" name="lXJfixture_phys0x5964820">
      3365         <volumeref ref="lXJfixture0x5958a70"/>
      3366         <position name="lXJfixture_phys0x5964820_pos" unit="mm" x="12987.2685003242" y="7498.2029647001" z="9370.7944540735"/>
      3367         <rotation name="lXJfixture_phys0x5964820_rot" unit="deg" x="-141.334348593975" y="47.2591746481021" z="-132.547177129057"/>
      3368       </physvol>
      3369       <physvol copynumber="3" name="lXJfixture_phys0x5964900">
      3370         <volumeref ref="lXJfixture0x5958a70"/>
      3371         <position name="lXJfixture_phys0x5964900_pos" unit="mm" x="9.18265026007717e-13" y="14996.4059294002" z="9370.7944540735"/>
      3372         <rotation name="lXJfixture_phys0x5964900_rot" unit="deg" x="-122" y="0" z="-90"/>
      3373       </physvol>
      3374       <physvol copynumber="4" name="lXJfixture_phys0x5962480">
      3375         <volumeref ref="lXJfixture0x5958a70"/>
      3376         <position name="lXJfixture_phys0x5962480_pos" unit="mm" x="-12987.2685003242" y="7498.2029647001" z="9370.7944540735"/>
      3377         <rotation name="lXJfixture_phys0x5962480_rot" unit="deg" x="-141.334348593975" y="-47.2591746481021" z="-47.452822870943"/>
      3378       </physvol>
      3379       <physvol copynumber="5" name="lXJfixture_phys0x5962560">
      3380         <volumeref ref="lXJfixture0x5958a70"/>
      3381         <position name="lXJfixture_phys0x5962560_pos" unit="mm" x="-12987.2685003242" y="-7498.2029647001" z="9370.7944540735"/>
      3382         <rotation name="lXJfixture_phys0x5962560_rot" unit="deg" x="141.334348593975" y="-47.2591746481021" z="47.4528228709431"/>
      3383       </physvol>
      3384       <physvol copynumber="6" name="lXJfixture_phys0x5962640">
      3385         <volumeref ref="lXJfixture0x5958a70"/>
      3386         <position name="lXJfixture_phys0x5962640_pos" unit="mm" x="-2.75479507802315e-12" y="-14996.4059294002" z="9370.7944540735"/>
      3387         <rotation name="lXJfixture_phys0x5962640_rot" unit="deg" x="122" y="0" z="90"/>
      3388       </physvol>
      3389       <physvol copynumber="7" name="lXJfixture_phys0x5962720">
      3390         <volumeref ref="lXJfixture0x5958a70"/>
      3391         <position name="lXJfixture_phys0x5962720_pos" unit="mm" x="12987.2685003241" y="-7498.2029647001" z="9370.7944540735"/>
      3392         <rotation name="lXJfixture_phys0x5962720_rot" unit="deg" x="141.334348593975" y="47.2591746481021" z="132.547177129057"/>
      3393       </physvol>
      3394     </volume>




jcv LSExpDetectorConstruction::

    1419 
    1420   IDetElement* xjfixture_det = 0;
    1421   if (m_xjfixture_name == "XJfixture") {
    1422       std::string new_name = m_xjfixture_name + "Construction";
    1423       xjfixture_det = det_elem(new_name);
    1424       assert(xjfixture_det);
    1425       IDetElementPos* xjfixture_detelem_pos = 0;
    1426       xjfixture_detelem_pos = new JUNO::Ball::HexagonPosBall(m_xjanchor_pos_file,xjfixture_r,false);
    1427       assert (xjfixture_detelem_pos);
    1428       bool xjfixture_status = cd_det->inject(m_xjfixture_mother, xjfixture_det, xjfixture_detelem_pos);
    1429       assert (xjfixture_status);
    1430   }
    1431 
    ....

    1472   IDetElement* sjreceiver_fastener_det = 0;
    1473   if (m_sjreceiver_fastener_name == "XJfixture") {
    1474       std::string new_name = m_sjreceiver_fastener_name + "Construction";
    1475       sjreceiver_fastener_det = det_elem(new_name);
    1476       assert(sjreceiver_fastener_det);
    1477       IDetElementPos* sjreceiver_fastener_detelem_pos = 0;
    1478       sjreceiver_fastener_detelem_pos = new JUNO::Ball::HexagonPosBall(m_sjreceiver_pos_file,sjreceiver_fastener_r,false);
    1479       assert (sjreceiver_fastener_detelem_pos);
    1480       bool sjreceiver_fastener_status = cd_det->inject(m_sjreceiver_fastener_mother, sjreceiver_fastener_det, sjreceiver_fastener_detelem_pos);
    1481       assert (sjreceiver_fastener_status);
    1482   }
    1483 
    1484 


XJfixtureConstruction gets used twice with m_xjanchor_pos_file and m_sjreceiver_pos_file ? 
But with different mother (lTarget and lWaterPool) and radius ?

   

::

    0149   m_strutballhead_name="StrutBallheadAcrylic";
     150   m_fastener_name = "FastenerAcrylic";
     151   m_upper_name = "UpperAcrylic";
     152   m_addition_name = "AdditionAcrylic";
     153   m_xjanchor_name = "XJanchor";
     154   m_xjfixture_name = "XJfixture";
     155   m_sjclsanchor_name = "SJCLSanchor";
     156   m_sjfixture_name = "SJFixture";
     157   m_sjreceiver_name = "SJReceiver";
     158   m_sjreceiver_fastener_name = "XJfixture";
     159   m_pmt_mother = "lWaterPool";
     160   m_mask_mother = "lMaskVirtual";
     161   m_strut_mother = "lWaterPool";
     162   m_fastener_mother = "lWaterPool";
     163   m_upper_mother = "lWaterPool";
     164   m_addition_mother = "lWaterPool";
     165   m_xjanchor_mother = "lWaterPool";
     166   m_xjfixture_mother = "lWaterPool";
     167   m_sjclsanchor_mother = "lTarget";
     168   m_sjfixture_mother = "lTarget";
     169   m_sjreceiver_mother = "lTarget";
     170   m_sjreceiver_fastener_mother = "lTarget";




