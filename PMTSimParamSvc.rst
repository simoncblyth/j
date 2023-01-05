PMTSimParamSvc.rst
====================


Objective : Get Expt Specific annotations like PMT info into Opticks and to GPU 
----------------------------------------------------------------------------------

HMM: how to organize expt specific "annotations" here ? such as collecting 
juno PMTSimParamSvc data into SSim under keys such as "juno/PMTSimParamSvc/pd_vector"

Need to access the pd_vector and the SSim from the non-Opticks glue code
and thereby append the extra detector specific arrays to the SSim/NPFold such 
that it automatically gets persisted. Natural place to do that is immediately after calling 
G4CXOpticks::SetGeometry. But the G4CXOpticks::setGeometry does the save, 
so adding to SSim after that would not be saved. 
This is not worth adding more primary API for, so just add an alternative envvar control 
"firstsimulate_saveGeometry" to save later.:: 

   jcv LSExpDetectorConstruction_Opticks 

Then can add annotations to SSim following translation and still get that persisted.


map serialization machinery 
------------------------------

NEXT:

1. position expts from PMTSimParamSvc/map_convert_test.sh  into NP
2. use that from LSExpDetectorConstruction::setupOpticks or LSExpDetectorConstruction_Opticks::Setup


::

     365 void LSExpDetectorConstruction::setupOpticks( G4VPhysicalVolume* physiWorld )
     366 {
     367     G4cout 
     368       << __FILE__ << ":" << __LINE__ << " completed construction of physiWorld "
     369       << " m_opticksMode " << m_opticksMode
     370       << G4endl
     371       ; 
     372     
     373     LSExpDetectorConstruction_Opticks::Setup( physiWorld, m_sd, m_opticksMode );
     374     
     375     // HMM : maybe move below into _Opticks for clarity 
     376  
     377     SniperPtr<IPMTParamSvc> _pp(*m_scope, "PMTParamSvc");
     378     if(_pp.invalid()) exit(EXIT_FAILURE); 
     379     PMTParamSvc* pp = dynamic_cast<PMTParamSvc*>( _pp.data() );
     380     
     381     SniperPtr<IPMTSimParamSvc> _ps(*m_scope, "PMTSimParamSvc");
     382     if(_ps.invalid()) exit(EXIT_FAILURE);
     383     PMTSimParamSvc* ps = dynamic_cast<PMTSimParamSvc*>( _ps.data() );
     384     
     385     G4cout 
     386       << __FILE__ << ":" << __LINE__ << " collecting PMT param annotations into Opticks SSim "
     387       << " m_opticksMode " << m_opticksMode
     388       << " pp " << pp
     389       << " ps " << ps
     390       << G4endl
     391       ;  
     392     
     393     const std::vector<PmtSimData>& pd_vector = ps->getPmtSimData() ;
     394     NP* pd = NP::Make<double>( pd_vector.size(), sizeof(PmtSimData)/sizeof(double) );
     395     pd->read2( pd_vector.data() );
     396 
     397     SSim::Add("juno/PMTSimParamSvc/pd_vector", pd);
     398     
     399 
     400     
     401 }   





Establish Where to grab the PMTSimParamSvc data
-------------------------------------------------

At the first event is a possibility, because junoSD_PMT_v2 holds pointer to PMTSimParamSvc::

    jcv junoSD_PMT_v2
    jcv junoSD_PMT_v2_Opticks

    junoSD_PMT_v2_Opticks::Initialize


Otherwise doing after geometry translation is possible, then would need to 
access PMTSimParamSvc just like the PMT managers do::

    jcv HamamatsuR12860PMTManager


Rearrange the Opticks setup
------------------------------

::

     365 void LSExpDetectorConstruction::setupOpticks( G4VPhysicalVolume* physiWorld )
     366 {
     367     SniperPtr<IPMTParamSvc> _pp(*m_scope, "PMTParamSvc");
     368     if(_pp.invalid()) exit(EXIT_FAILURE);
     369     PMTParamSvc* pp = dynamic_cast<PMTParamSvc*>( _pp.data() );
     370 
     371     SniperPtr<IPMTSimParamSvc> _ps(*m_scope, "PMTSimParamSvc");
     372     if(_ps.invalid()) exit(EXIT_FAILURE);
     373     PMTSimParamSvc* ps = dynamic_cast<PMTSimParamSvc*>( _ps.data() );
     374 
     375     G4cout
     376       << __FILE__ << ":" << __LINE__ << " completed construction of physiWorld "
     377       << " m_opticksMode " << m_opticksMode
     378       <<< " pp " << pp
     379       <<< " ps " << ps
     380       << G4endl
     381       ;
     382 
     383     LSExpDetectorConstruction_Opticks::Setup( physiWorld, m_sd, m_opticksMode );
     384 }



 
YUCKY Sniper 
-------------

HamamatsuR12860PMTManager::helper_fast_sim::

    1000     m_pmt_sim_param_svc = 0;
    1001     LogInfo << "Retrieving PMTSimParamSvc." << std::endl;
    1002     SniperPtr<IPMTSimParamSvc> simsvc(*getParent(), "PMTSimParamSvc");
    1003     if(simsvc.invalid()){
    1004         LogError << "Can't get PMTSimParamSvc. We can't initialize PMT." << std::endl;
    1005         assert(0);
    1006         exit(EXIT_FAILURE);
    1007     }else{
    1008         LogInfo <<"Retrieve PMTSimParamSvc successfully." << std::endl;
    1009         m_pmt_sim_param_svc = simsvc.data();
    1010     }
       
    033 #ifdef PMTSIM_STANDALONE
     34 #include "PMTSIM_API_EXPORT.hh"
     35 class PMTSIM_API HamamatsuR12860PMTManager : public IGeomManager {
     36 #else
     37 class HamamatsuR12860PMTManager: public IPMTElement,
     38                                  public ToolBase {
     39 #endif
     40 public:




Accessing the Svc from LSExpDetectorConstruction_Opticks
-------------------------------------------------------------

::

      6 struct LSExpDetectorConstruction_Opticks
      7 {
      8     static void Setup(const G4VPhysicalVolume* world, const G4VSensitiveDetector* sd_, int opticksMode );
      9 };




::

    175 G4VUserDetectorConstruction*
    176 DetSim0Svc::createDetectorConstruction()
    177 {
    178     LSExpDetectorConstruction* dc = new LSExpDetectorConstruction;
    179     dc->setScope(dynamic_cast<Task*>(getParent()));
    180     dc->setCDEnabled(m_cd_enabled);
    181     dc->setCDName(m_cd_name);

    062      void setScope(Task* scope) {m_scope = scope;}
     63      Task* getScope() {return m_scope;}




Pointless Sniper Complication : Why do I need to be concered with my current context in order to access a service ?
-----------------------------------------------------------------------------------------------------------------------

::

    epsilon:sniper blyth$ cd $JUNOTOP/sniper
    epsilon:sniper blyth$ find . -name ToolBase.h
    ./SniperKernel/SniperKernel/ToolBase.h
    epsilon:sniper blyth$ find . -name DLElement.h 
    ./SniperKernel/SniperKernel/DLElement.h
    epsilon:sniper blyth$ find . -name SniperPtr.h
    ./SniperKernel/SniperKernel/SniperPtr.h



    025 class ToolBase : public DLElement
     26 {
     27     public :
     28 
     29         ToolBase(const std::string& name);
     30 
     31         virtual ~ToolBase() = default;
     32 
     33         virtual bool initialize();
     34         virtual bool finalize();
     35 };
     36 

    029 class DLElement : public NamedElement
     30 {
     31     public :
     32 
     33         DLElement(const std::string& name);
     34         virtual ~DLElement();
     35 
     36         // pure virtual interfaces
     37         virtual bool initialize() = 0;
     38         virtual bool finalize() = 0;
     39 
     40         // return the tag flag: should be the derived concrete class name
     41         const std::string& tag() { return m_tag; }
     42 
     43         // get the parent (Task) pointer
     44         Task* getParent() { return m_par; }
     45 
     46         // get the root node (Task) pointer of the DLElements' tree
     47         Task* getRoot();
     48 
     49         // set the tag
     50         void setTag(const std::string& tag_) { m_tag = tag_; }
     51 
     52         // set the parent (Task) pointer
     53         void setParent(Task* parent);
     54 

