EventAction_SensitiveDetector_SEvt_Lifecycle_issue
=====================================================


Players
---------

::

    jcv G4OpticksAnaMgr  ## THIS SHOULD BE REMOVED
    jcv U4RecorderAnaMgr

    jcv junoSD_PMT_v2_Opticks


Geant4+SEvt Lifecycle issue
--------------------------------

Below shows the ordering is::
    
    G4VSensitiveDetector::Initialize      ... junoSD_PMT_v2_Opticks::Initialize
    G4UserEventAction::BeginOfEventAction ... U4Recorder::BeginOfEventAction

    G4VSensitiveDetector::EndOfEvent          junoSD_PMT_v2_Opticks::EndOfEvent
    G4UserEventAction::EndOfEventAction ...   U4Recorder::EndOfEventAction

* tracking and stepping have to be handled in the Actions
* hits are needed in SensitiveDetector EndOfEvent

That causes complications as SEvt mechanics has 
to be split across both::

    *Action*
    "SensDet"


HOW TO FIX ?

Make the below dummies, or remove the calls from U4RecorderAnaMgr::

    U4Recorder::BeginOfEventAction
    U4Recorder::EndOfEventAction

Call the actual methods when U4Recorder detected from
a pair of new SensitiveDetector methods in G4CXOpticks:: 

    junoSD_PMT_v2_Opticks::Initialize
         G4CXOpticks::SensitiveDetector_Initialize 
             U4Recorder::BeginOfEventAction_

    junoSD_PMT_v2_Opticks::EndOfEvent
         G4CXOpticks::SensitiveDetector_EndOfEvent
             U4Recorder::EndOfEventAction_
 


Fragile ugly "kick sibling" kludge that kinda worked
--------------------------------------------------------

::

    void SEvt::beginOfEvent(int eventID)
    {
        setStage(SEvt__beginOfEvent); 
        sprof::Stamp(p_SEvt__beginOfEvent_0);  
        int index_ = 1+eventID ;  
        LOG(LEVEL) << " index_ " << index_ ; 
        setIndex(index_);      // also sets t_BeginOfEvent stamp 


        /*   
        // kicking the sibling is a kludge that 
        // G4CXOpticks::SensitiveDetector_EndOfEvent 
        //should avoid

        if(isEGPU()) 
        {
            SEvt* ecpu = getSibling() ; 
            if(ecpu->getIndex() == index_ )
            {
                LOG_IF(info, LIFECYCLE) << id() << " KICK ECPU SIBLING : " << ecpu->id() ; 
                ecpu->endOfEvent(eventID) ; 
            }
            else
            {
                LOG_IF(info, LIFECYCLE) << id() << " ECPU SIBLING NOT SAME INDEX : " << ecpu->id() ; 
            }
        }
        */

        LOG_IF(info, LIFECYCLE) << id() ; 

        clear(); 

        addFrameGenstep();     // needed for simtrace and input photon running
        sprof::Stamp(p_SEvt__beginOfEvent_1);  
    }







U4RecorderAnaMgr
------------------

May be down to U4Recorder::EndOfEventAction not happening before 
simulate gets called.::

    010 U4RecorderAnaMgr::U4RecorderAnaMgr(const std::string& name)
     11     : 
     12     ToolBase(name),
     13 #ifdef WITH_G4CXOPTICKS
     14     m_recorder(new U4Recorder)
     15 #else
     16     m_recorder(nullptr)
     17 #endif
     18 {
     19 }
     20 
     21 U4RecorderAnaMgr::~U4RecorderAnaMgr()
     22 {
     23 #ifdef WITH_G4CXOPTICKS
     24     delete m_recorder ; 
     25 #endif
     26 }
     27     
     28 #ifdef WITH_G4CXOPTICKS
     29 void U4RecorderAnaMgr::BeginOfRunAction(const G4Run* run) {         m_recorder->BeginOfRunAction(run);       }
     30 void U4RecorderAnaMgr::EndOfRunAction(const G4Run* run) {           m_recorder->EndOfRunAction(run);         }
     31 void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* evt) {     m_recorder->BeginOfEventAction(evt);     }
     32 void U4RecorderAnaMgr::EndOfEventAction(const G4Event* evt) {       m_recorder->EndOfEventAction(evt);       }
     33 void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* trk) {  m_recorder->PreUserTrackingAction(trk);  }
     34 void U4RecorderAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction(trk); }
     35 void U4RecorderAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
     36 #else


    020 class U4RecorderAnaMgr: public IAnalysisElement,
    021                          public ToolBase {
    022 public:

    012 class IAnalysisElement {
     13 public:
     14     virtual ~IAnalysisElement() {}
     15 
     16     // Run Action
     17     virtual void BeginOfRunAction(const G4Run*) = 0;
     18     virtual void EndOfRunAction(const G4Run*) = 0;
     19     //
     20     // Event Action
     21     virtual void BeginOfEventAction(const G4Event*) = 0;
     22     virtual void EndOfEventAction(const G4Event*) = 0;
     23     //


jcv MgrOfAnaElem::

     13 class MgrOfAnaElem {
     14 public:
     15     static MgrOfAnaElem& instance();
     16 
     17     bool reg(const std::string& key, IAnalysisElement*);
     18     bool get(const std::string& key, IAnalysisElement*&);
     19 
     20     void BeginOfRunAction(const G4Run*);
     21     void EndOfRunAction(const G4Run*);
     22     void BeginOfEventAction(const G4Event*);
     23     void EndOfEventAction(const G4Event*);


jcv LSExpEventAction::

     41 class LSExpEventAction : public G4UserEventAction
     42 {
     43   public:
     44     LSExpEventAction();
     45    ~LSExpEventAction();
     46 
     47   public:
     48     void BeginOfEventAction(const G4Event* anEvent);
     49     void EndOfEventAction(const G4Event* anEvent);

     64 void LSExpEventAction::BeginOfEventAction(const G4Event* evt)
     65 {
     66   MgrOfAnaElem::instance().BeginOfEventAction(evt);
     67   //if(evt->GetEventID()%1000 == 0) G4cout << "Begin of Event --> " << evt->GetEventID() << G4endl;
     68   G4cout << "Begin of Event --> " << evt->GetEventID() << G4endl;
     69 
     70 }
     71 
     72 //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
     73 
     74 void LSExpEventAction::EndOfEventAction(const G4Event* evt)
     75 {
     76   MgrOfAnaElem::instance().EndOfEventAction(evt);
     77 
     78 }




Examination of G4EventManager establishes the order
----------------------------------------------------


Below shows the ordering is::
    
    G4VSensitiveDetector::Initialize
    G4UserEventAction::BeginOfEventAction

    G4VSensitiveDetector::EndOfEvent
    G4UserEventAction::EndOfEventAction



g4-cls G4EventManager::

    099 void G4EventManager::DoProcessing(G4Event* anEvent)
    100 {
    ...
    145   sdManager = G4SDManager::GetSDMpointerIfExist();
    146   if(sdManager)
    147   { currentEvent->SetHCofThisEvent(sdManager->PrepareNewEvent()); }
    148       
    149   if(userEventAction) userEventAction->BeginOfEventAction(currentEvent);
    ...
    262   if(sdManager)
    263   { sdManager->TerminateCurrentEvent(currentEvent->GetHCofThisEvent()); }
    264 
    265   if(userEventAction) userEventAction->EndOfEventAction(currentEvent);
    266 


    109 G4HCofThisEvent* G4SDManager::PrepareNewEvent()
    110 {
    111   G4HCofThisEvent* HCE = new G4HCofThisEvent(HCtable->entries());
    112   treeTop->Initialize(HCE);
    113   return HCE;
    114 }

    194 void G4SDStructure::Initialize(G4HCofThisEvent*HCE)
    195 {     
    196   // Broadcast to subdirectories.
    197   for(auto st : structure)
    198   { st->Initialize(HCE); }
    199   // Initialize all detectors in this directory.
    200   for(auto dt : detector)
    201   { if(dt->isActive()) dt->Initialize(HCE); }
    202 }     


g4-cls G4VSensitiveDetector::

     68   public: // with description
     69       virtual void Initialize(G4HCofThisEvent*);
     70       virtual void EndOfEvent(G4HCofThisEvent*);
     71       //  These two methods are invoked at the begining and at the end of each
     72       // event. The hits collection(s) created by this sensitive detector must
     73       // be set to the G4HCofThisEvent object at one of these two methods.





    116 void G4SDManager::TerminateCurrentEvent(G4HCofThisEvent* HCE)
    117 {
    118   treeTop->Terminate(HCE);
    119 }

    204 void G4SDStructure::Terminate(G4HCofThisEvent*HCE)
    205 {
    206   // Broadcast to subdirectories.
    207   for(auto st : structure)
    208   { st->Terminate(HCE); }
    209   // Terminate all detectors in this directory.
    210   for(auto dt : detector)
    211   { if(dt->isActive()) dt->EndOfEvent(HCE); }
    212 }





::

    junoSD_PMT_v2::Initialize (G4VSensitiveDetector)
      junoSD_PMT_v2_Opticks::Initialize
         [currently only doese SEvt::TimerStart] 

    junoSD_PMT_v2::EndOfEvent (G4VSensitiveDetector)
      junoSD_PMT_v2_Opticks::EndOfEvent
   




::

     50 class G4VSensitiveDetector
     51 {
     52 
     53   public: // with description
     54       G4VSensitiveDetector(G4String name);
     55       G4VSensitiveDetector(const G4VSensitiveDetector &right);
     56       // Constructors. The user's concrete class must use one of these constructors
     57       // by the constructor initializer of the derived class. The name of
     58       // the sensitive detector must be unique.
     59 
     60   public:
     61       virtual ~G4VSensitiveDetector();
     62 
     63       G4VSensitiveDetector & operator=(const G4VSensitiveDetector &right);
     64 
     65       G4int operator==(const G4VSensitiveDetector &right) const;
     66       G4int operator!=(const G4VSensitiveDetector &right) const;
     67 
     68   public: // with description
     69       virtual void Initialize(G4HCofThisEvent*);
     70       virtual void EndOfEvent(G4HCofThisEvent*);
     71       //  These two methods are invoked at the begining and at the end of each
     72       // event. The hits collection(s) created by this sensitive detector must



