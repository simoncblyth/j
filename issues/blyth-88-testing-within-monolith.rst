blyth-88-testing-within-monolith
===================================

How to do this ?
------------------

Perhaps via Opticks enabled ana-manager that brings U4Recorder/sysrap style 
functionality into the monolith ? 

Essentially need to hookup the U4Recorder event/track/step listeners 
into the monolith ones ?



Review the old G4OpticksAnaMgr
--------------------------------

Start by reviewing what the old "--opticks-anamgr" does::

   jcv JUNODetSimModule




    0495         # == opticks ==
     496         grp_pmt_op.add_argument("--opticks-mode", type=int, dest="opticks_mode", default=0,
     497                                 help=mh("Control Opticks GPU Optical simulation"))
     498         grp_pmt_op.add_argument("--opticks-anamgr", action="store_true", dest="opticks_anamgr", default=False,
     499                                 help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays.")     )
     500 

    1989         # == opticks
    1990         if args.opticks_mode > 0 and args.opticks_anamgr:
    1991             print("appending G4OpticksAnaMgr to AnaMgrList")
    1992             detsimfactory.property("AnaMgrList").append("G4OpticksAnaMgr")
    1993             g4ok_anamgr = sim_conf.tool("G4OpticksAnaMgr")
    1994             g4ok_anamgr.setLogLevel(4)
    1995         pass

jcv G4OpticksAnaMgr::

     28 #ifdef WITH_G4OPTICKS
     29 void G4OpticksAnaMgr::BeginOfRunAction(const G4Run* run) {  BeginOfRun() ;  m_recorder->BeginOfRunAction(run);       }
     30 void G4OpticksAnaMgr::EndOfRunAction(const G4Run* run) {           m_recorder->EndOfRunAction(run);         }
     31 void G4OpticksAnaMgr::BeginOfEventAction(const G4Event* evt) {     m_recorder->BeginOfEventAction(evt);     }
     32 void G4OpticksAnaMgr::EndOfEventAction(const G4Event* evt) {       m_recorder->EndOfEventAction(evt);       }
     33 void G4OpticksAnaMgr::PreUserTrackingAction(const G4Track* trk) {  m_recorder->PreUserTrackingAction(trk);  }
     34 void G4OpticksAnaMgr::PostUserTrackingAction(const G4Track* trk) { m_recorder->PostUserTrackingAction(trk); }
     35 void G4OpticksAnaMgr::UserSteppingAction(const G4Step* step) {     m_recorder->UserSteppingAction(step);    }
     36 #else


* HMM maybe new G4CXOpticksAnaMgr to replace the G4OpticksAnaMgr

      
Looks like Essentially need to update the opticks-anamgr to the U4 way of working 
-----------------------------------------------------------------------------------------

YES: but also need the initialization/finalization done by U4SimulateTest.cc

* probably need to encapsulate some of what U4SimulateTest.cc does 
  into headers so can do that from the monolith 

* so can start standalone by cleaning up the main 

* DONE : tidied up U4SimulateTest.cc/U4Recorder.cc using U4App.h to prepare for use of U4Recorder from an AnaMgr 

* cannot use U4SimulateTest struct within monolith, need to work with the monolith controlled G4RunManager
* similarly cannot use U4RecorderTest.h:U4RecorderTest (not U4App.h)

Plugging into the anamgr dont have clear initialize/finalize hooks other than BeginOfRun/EndOfRun ?
Or perhaps should use BeginOfEvent/EndOfEvent as SEvt needs saving at that cadence. 

::

    123 U4RecorderTest::U4RecorderTest(G4RunManager* runMgr)
    124     :
    125     fPrimaryMode(PrimaryMode()),
    126     fRecorder(new U4Recorder),
    127     fGun(fPrimaryMode == 'G' ? InitGun() : nullptr),
    128     fPV(nullptr)
    129 {



WIP: Create U4RecorderAnaMgr using U4Recorder+SEvt, starting from G4OpticksAnaMgr 
--------------------------------------------------------------------------------------

::

    epsilon:junosw blyth$ jcv G4OpticksAnaMgr
    2 files to edit
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc
    epsilon:junosw blyth$ cd 

Trivial pass thru from U4RecorderAnaMgr to U4Recorder::

    epsilon:junosw blyth$ jcv U4RecorderAnaMgr
    2 files to edit
    ./Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc
    epsilon:junosw blyth$ 


HMM:

* Where to hold the SEvt ? U4Recorder::setEvt ? 
* Does U4Recorder need to know AnaMgr involved ? 


Looks like hookup only at python level::

    epsilon:junosw blyth$ jgr G4OpticksAnaMgr | grep -v G4OpticksAnaMgr.hh | grep -v G4OpticksAnaMgr.cc 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    * this mode of operation is typically used together with the G4OpticksAnaMgr allowing the Geant4 propagation
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:     G4OpticksAnaMgr and G4OpticksRecorder to save the entire Geant4 optical propagations in OpticksEvent format 
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:                                help=mh("Enable G4OpticksAnaMgr for optional use of G4OpticksRecorder saving Geant4 optical propagations into OpticksEvent NumPy arrays."))
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            print("appending G4OpticksAnaMgr to AnaMgrList")    
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("AnaMgrList").append("G4OpticksAnaMgr")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            g4ok_anamgr = sim_conf.tool("G4OpticksAnaMgr")
    epsilon:junosw blyth$ 


::

    1989         # == opticks
    1990         if args.opticks_mode > 0 and args.opticks_anamgr:
    1991             print("appending U4RecorderAnaMgr to AnaMgrList")   
    1992             detsimfactory.property("AnaMgrList").append("U4RecorderAnaMgr")
    1993             g4ok_anamgr = sim_conf.tool("U4RecorderAnaMgr")
    1994             g4ok_anamgr.setLogLevel(4)
    1995         pass


jxv:ntds3 




