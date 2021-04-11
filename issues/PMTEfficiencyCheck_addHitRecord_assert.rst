PMTEfficiencyCheck_addHitRecord_assert
==========================================



When you meet a problem the first thing you should do is 
take a look at the code where the error occurs.::


    epsilon:offline blyth$ find . -name PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    epsilon:offline blyth$ vi Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    epsilon:offline blyth$ 

::

     53 #ifdef WITH_G4OPTICKS
     54 void PMTEfficiencyCheck::addHitRecord(int pmtID, const G4ThreeVector& global_pos, const G4ThreeVector& local_pos, double qe, double ce, double de, const std::string& volname, int ce_cat )
     55 {
     56     unsigned volIdx = getVolnameIndex(volname);
     57     // NB volIdx uses the standard list of volname, not the one being collected below which is in an uncontrolled order 
     58 
     59     std::vector<std::string>& u = m_uvolname ;
     60     if(std::find(u.begin(), u.end(), volname ) == u.end()) u.push_back(volname); // collect unique volnames 
     61 
     62     double theta = local_pos.theta() ;
     63     double qe2 = m_jpmt->getQuantumEfficiency(pmtID);
     64     double ce2 = m_jpmt->getCollectionEfficiency(theta, pmtID);
     65     double de2 = m_jpmt->getDetectionEfficiency(theta, pmtID);
     66 
     67     double epsilon = 1e-10 ;
     68     bool qe_match = std::abs(qe - qe2) < epsilon ;
     69     bool ce_match = std::abs(ce - ce2) < epsilon ;
     70     bool de_match = std::abs(de - de2) < epsilon ;
     71 
     72     assert( qe_match );
     73     assert( ce_match );
     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




Hu Yuxiang report
---------------------

::

    Hi simon,

          I did use the below commad line to install Opticks.

              bash junoenv opticks

         I updated the opticks  on your advice and it can simulate gamma event with low energy. 
         When I want to simulate high energy event such as muon with 215GeV energy, it breaks down!


    1.  the command is :

    python tut_detsim.py --seed 10 --evtmax 1 --opticks-mode 1 --pmt20inch-polycone-neck    --no-guide_tube  gun  --particles mu- --momentums 215000


    the error is :


    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0)
    junoSD_PMT_v2::Initialize
    Begin of Event --> 0
    python: ../src/PMTEfficiencyCheck.cc:73: void PMTEfficiencyCheck::addHitRecord(int, const G4ThreeVector&, const G4ThreeVector&, double, double, double, const string&, int): Assertion `ce_match' failed.
     *** Break *** abort
    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 1 (Thread 0x7f03b92c5740 (LWP 39823)):

    #0  0x00007f03b7cca4b9 in waitpid () from /lib64/libc.so.6
    #1  0x00007f03b7c47f62 in do_system () from /lib64/libc.so.6
    #2  0x00007f03b7c48311 in system () from /lib64/libc.so.6
    #3  0x00007f03ae944364 in TUnixSystem::StackTrace() () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libCore.so
    #4  0x00007f03a9c00f2f in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libcppyy_backend3_8.so
    #5  0x00007f03ae946a8b in TUnixSystem::DispatchSignals(ESignals) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libCore.so
    #6  <signal handler called>
    #7  0x00007f03b7c3b387 in raise () from /lib64/libc.so.6
    #8  0x00007f03b7c3ca78 in abort () from /lib64/libc.so.6
    #9  0x00007f03b7c341a6 in __assert_fail_base () from /lib64/libc.so.6
    #10 0x00007f03b7c34252 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f038045a803 in PMTEfficiencyCheck::addHitRecord (this=0x6595600, pmtID=pmtID
    entry=13411, global_pos=..., local_pos=..., qe=qe
    entry=0.36854931192660545, ce=ce
    entry=1, de=de
    entry=0.36854931192660545, volname="HamamatsuR12860_PMT_20inch_inner1_phys", ce_cat=0) at ../src/PMTEfficiencyCheck.cc:73
    #12 0x00007f038044477d in junoSD_PMT_v2::ProcessHits (this=0x6594c10, step=<optimized out>) at ../src/junoSD_PMT_v2.cc:373
    #13 0x00007f0390f9999c in G4SteppingManager::Stepping() () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so

    #14 0x00007f0390fa510d in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #15 0x00007f03911dcb53 in G4EventManager::DoProcessing(G4Event*) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #16 0x00007f0380927ba0 in G4SvcRunManager::SimulateEvent(int) () from /home/ihep/juno/JUNO-SOFT/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #17 0x00007f037ffa3d9b in DetSimAlg::execute (this=0x539bbd0) at ../src/DetSimAlg.cc:112
    #18 0x00007f03b0e05381 in Task::execute() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #19 0x00007f03b0e0bbe5 in TaskWatchDog::run() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #20 0x00007f03b0e04d68 in Task::run() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so


    2.  From your last reply, you mentioned the argument "--cerenkov-type  original". I use this argument in order to avoid the current hang problem. Did  you mean that if I use Opticks then I don't need to care about the current hang problem with G4Cerenkov_modified because Opticks will use its own G4Cerenkov ? 




