G4CXTest_GEOM
==============


Overview
-------------

HMM: when just cycling on Opticks could start from CFBase with CSGOptiXSMTest
avoiding the translation but when using both Geant4 and Opticks need to start from GDML.
See :doc:`cxs_min_shakedown` for that. 


Workflow
----------

Workstation::

   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh info
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh
   LOG=1 ~/opticks/g4cx/tests/G4CXTest_GEOM.sh

Laptop::

   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh info
   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh grab
   PICK=A ~/opticks/g4cx/tests/G4CXTest_GEOM.sh ana
   PICK=B ~/opticks/g4cx/tests/G4CXTest_GEOM.sh ana
   PICK=AB ~/opticks/g4cx/tests/G4CXTest_GEOM.sh ana


FIXED : Issue 1 : missing real PMTAccessor 
----------------------------------------------

Placeholder accessor give qe 1 and::

    2023-11-21 11:21:08.669 INFO  [382763] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 1000
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.6525 _qe 1 stack.art.A (aka An) 0.605144
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
 
* missing real PMTAccessor when operating without j/PMTSim 

  * looks like no alternative to use j/PMTSim with G4CXTest 
    in order to use the parts of junosw that can furnish the PMT info needed

  * HMM: but already access this info on GPU via SPMT/QPMT
  * YES but SPMT/QPMT they get their info from the PMTAccessor 
  * maybe if could persist at SPMT stage could avoid j/PMTSIM

Implemented SPMTAccessor.h to provide the C4IPMTAccessor interface 
on top of SPMT.h 

FIXED : Issue 1.1  : energy units in SPMTAccessor API
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The added SPMTAccessor.h  avoids the error message from "theEfficiency > 1."
but are getting very few "SD" on the B side. So something wrong with 
what the SPMTAccessor is providing ?::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT BT BT SA      ' ' 0' '    79    184' '41.9202' '     5      2']
     [' 1' 'TO AB                        ' ' 1' '    99    133' ' 4.9828' '     2      9']
     [' 2' 'TO BT BT BT BT BT BT SD      ' ' 2' '   118      0' '118.0000' '    13     -1']
     [' 3' 'TO SC BT BT BT BT BT BT SA   ' ' 3' '    27     69' '18.3750' '    39      1']
     [' 4' 'TO SC AB                     ' ' 4' '    31     43' ' 1.9459' '    17     19']
     [' 5' 'TO SC BT BT BT BT BT BT SD   ' ' 5' '    35      2' '29.4324' '    20    365']
     [' 6' 'TO SC SC BT BT BT BT BT BT SA' ' 6' '     9     26' ' 8.2571' '    82      3']


* HMM: using debug C4 is the surest way for find the issue, but before doing 
  try just dumping from the SPMTAccessor side


FIXED BY INCREASING STATS TO 1M : Issue 1.2 : poor A/B chi2 from low stats 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    QCF qcf :  
    a.q 1000 b.q 1000 lim slice(None, None, None) 
    c2sum :    20.7502 c2n :     9.0000 c2per:     2.3056  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  20.75/9:2.306 (30) pv[1.00,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO AB                        ' ' 0' '    99    133' ' 4.9828' '     2      9']
     [' 1' 'TO BT BT BT BT BT BT SD      ' ' 1' '   118    111' ' 0.2140' '    13     26']
     [' 2' 'TO BT BT BT BT BT BT SA      ' ' 2' '    79     73' ' 0.2368' '     5      2']
     [' 3' 'TO SC AB                     ' ' 3' '    31     43' ' 1.9459' '    17     19']
     [' 4' 'TO SC BT BT BT BT BT BT SA   ' ' 4' '    27     36' ' 1.2857' '    39     12']
     [' 5' 'TO SC BT BT BT BT BT BT SD   ' ' 5' '    35     35' ' 0.0000' '    20      1']
     [' 6' 'TO SC SC SC BT BT BT BT BT BT' ' 6' '    26      8' ' 9.5294' '     1     29']
     [' 7' 'TO BT BT BT BT BT BT BR BT BT' ' 7' '    25     20' ' 0.5556' '    38      8']
     [' 8' 'TO SC SC BT BT BT BT BT BT BT' ' 8' '    20     12' ' 2.0000' '    68     84']

::

    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum :  2273.9155 c2n :  2121.0000 c2per:     1.0721  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  2273.92/2121:1.072 (30) pv[1.00,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO AB                                                 0' '127200 127884' ' 1.8341' '     2      5']
     [' 1' 'TO BT BT BT BT BT BT SD                               1' ' 92833  92195' ' 2.1999' '    13      0']
     [' 2' 'TO BT BT BT BT BT BT SA                               2' ' 89528  89253' ' 0.4230' '     5      6']
     [' 3' 'TO SC AB                                              3' ' 51873  51498' ' 1.3604' '    17     54']
     [' 4' 'TO SC BT BT BT BT BT BT SD                            4' ' 36363  36639' ' 1.0435' '    20     17']
     [' 5' 'TO SC BT BT BT BT BT BT SA                            5' ' 30106  30371' ' 1.1612' '    39    106']
     [' 6' 'TO SC SC AB                                           6' ' 19904  20118' ' 1.1443' '   137      2']
     [' 7' 'TO RE AB                                              7' ' 18402  18096' ' 2.5655' '     9     32']
     [' 8' 'TO SC SC BT BT BT BT BT BT SD                         8' ' 15674  15451' ' 1.5977' '    19     11']
     [' 9' 'TO SC SC BT BT BT BT BT BT SA                         9' ' 12991  12881' ' 0.4677' '    82     36']
     ['10' 'TO BT BT AB                                          10' ' 11611  11786' ' 1.3089' '    55      8']
     ['11' 'TO BT BT SA                                          11' ' 10072  10313' ' 2.8492' '   203    140']
     ['12' 'TO BT AB                                             12' '  9410   9351' ' 0.1855' '    36     80']
     ['13' 'TO SC SC SC AB                                       13' '  7706   7375' ' 7.2648' '   107    192']
     ['14' 'TO RE BT BT BT BT BT BT SD                           14' '  7557   7503' ' 0.1936' '    25     14']
     ['15' 'TO RE BT BT BT BT BT BT SA                           15' '  7268   7140' ' 1.1371' '    48     75']
     ['16' 'TO SC RE AB                                          16' '  7129   7154' ' 0.0438' '   110    268']
     ['17' 'TO SC BT BT AB                                       17' '  6614   6704' ' 0.6082' '   153    123']
     ['18' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SD   18' '  6671   6674' ' 0.0007' '    38    230']
     ['19' 'TO SC SC SC BT BT BT BT BT BT SD                     19' '  6087   6271' ' 2.7396' '   114     51']
     ['20' 'TO SC BT BT SA                                       20' '  5720   5928' ' 3.7143' '   169    155']
     ['21' 'TO SC BT AB                                          21' '  5509   5833' ' 9.2555' '     8    288']
     ['22' 'TO RE RE AB                                          22' '  5585   5588' ' 0.0008' '   267     19']
     ['23' 'TO SC SC SC BT BT BT BT BT BT SA                     23' '  5239   5148' ' 0.7972' '     1    143']
     ['24' 'TO BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA   24' '  4946   4903' ' 0.1877' '    53    575']
     ['25' 'TO SC BT BT BT BT BT BT BT SA                        25' '  4581   4569' ' 0.0157' '   279    529']
     ['26' 'TO BT BT DR BT SA                                    26' '  4565   4519' ' 0.2329' '     0    373']
     ['27' 'TO BT BT BT BT AB                                    27' '  3957   3966' ' 0.0102' '   225      3']



Issue 3 : SAB(a,b) python history comparison taking long time with many different histories
---------------------------------------------------------------------------------------------




FIXED : Issue 4 : NPFold hit assert on 2nd event
---------------------------------------------------

::

    2023-11-23 17:28:23.367 INFO  [45616] [SEvt::save@3404]  dir /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/G4CXTest/ALL0/n001 index 1 instance 1 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    2023-11-23 17:28:26.720 INFO  [45616] [U4Recorder::EndOfEventAction@314]  savedir -
    2023-11-23 17:28:27.879 INFO  [45616] [SEvt::save@3404]  dir /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/G4CXTest/ALL0/p001 index 1 instance 0 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    2023-11-23 17:28:29.494 INFO  [45616] [G4CXApp::GeneratePrimaries@238] [ fPrimaryMode T
    2023-11-23 17:28:29.495 INFO  [45616] [SEvent::MakeGensteps@65] num_ph 100000 dump 0
    U4VPrimaryGenerator::GeneratePrimaries ph (100000, 4, 4, )
    2023-11-23 17:28:29.571 INFO  [45616] [G4CXApp::GeneratePrimaries@252] ]
    2023-11-23 17:28:29.571 INFO  [45616] [U4Recorder::BeginOfEventAction@288]  eventID 1
    2023-11-23 17:28:29.596 INFO  [45616] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 100000
    2023-11-23 17:28:36.958 INFO  [45616] [U4Recorder::PreUserTrackingAction_Optical@378]  modulo 100000 : ulabel.id 0
    2023-11-23 17:28:36.958 INFO  [45616] [U4Recorder::MakeMetaArray@676] U4Recorder::DescFakes  
    U4Recorder::FAKES_SKIP NO 
    U4Recorder::FAKES      YES
    FAKES.size             0

    NPFold::add_ FATAL : have_key_already hit.npy
    G4CXTest: /home/blyth/junotop/opticks/sysrap/NPFold.h:853: void NPFold::add_(const char*, const NP*): Assertion `!have_key_already' failed.
    /home/blyth/opticks/g4cx/tests/G4CXTest_GEOM.sh: line 138: 45616 Aborted                 (core dumped) $bin
    /home/blyth/opticks/g4cx/tests/G4CXTest_GEOM.sh : run error
    N[blyth@localhost opticks]$ 
     

::

     840 /**
     841 NPFold::add_
     842 --------------
     843 
     844 This lower level method does not add DOT_NPY to keys
     845 
     846 **/
     847 inline void NPFold::add_(const char* k, const NP* a)
     848 {
     849     if(verbose_) std::cerr << "NPFold::add_ [" << k  << "]" <<  std::endl ;
     850 
     851     bool have_key_already = std::find( kk.begin(), kk.end(), k ) != kk.end() ;
     852     if(have_key_already) std::cerr << "NPFold::add_ FATAL : have_key_already " << k << std::endl ;
     853     assert( !have_key_already );
     854 
     855     kk.push_back(k);
     856     aa.push_back(a);
     857 }


::

    (gdb) bt
    #0  0x00007ffff2766387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff2767a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff275f1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff275f252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007ffff3e0ee8e in NPFold::add_ (this=0x6c6510, k=0x7ffffffefc80 "hit.npy", a=0x4820ade0) at /home/blyth/junotop/opticks/sysrap/NPFold.h:853
    #5  0x00007ffff3e0ed1a in NPFold::add (this=0x6c6510, k=0x7ffff3f51f69 "hit", a=0x4820ade0) at /home/blyth/junotop/opticks/sysrap/NPFold.h:837
    #6  0x00007ffff3e5014e in SEvt::gather_components (this=0x6c5cd0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:2986
    #7  0x00007ffff3e5079d in SEvt::gather (this=0x6c5cd0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3038
    #8  0x00007ffff3e51c0d in SEvt::save (this=0x6c5cd0, dir_=0x7ffff3f4de62 "$DefaultOutputDir") at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3391
    #9  0x00007ffff3e5086a in SEvt::save (this=0x6c5cd0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3119
    #10 0x00007ffff3e47ee3 in SEvt::endOfEvent (this=0x6c5cd0, eventID=1) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1282
    #11 0x00007ffff7cfc8f6 in U4Recorder::EndOfEventAction (this=0x6c5b30, event=0x359643b0) at /home/blyth/junotop/opticks/u4/U4Recorder.cc:311
    #12 0x000000000040a189 in G4CXApp::EndOfEventAction (this=0x6c5a20, event=0x359643b0) at /home/blyth/junotop/opticks/g4cx/tests/G4CXApp.h:266
    #13 0x00007ffff7037242 in G4EventManager::DoProcessing(G4Event*) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #14 0x00007ffff70d6a9f in G4RunManager::DoEventLoop(int, char const*, int) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #15 0x00007ffff70d44de in G4RunManager::BeamOn(int, char const*, int) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #16 0x000000000040a7a1 in G4CXApp::BeamOn (this=0x6c5a20) at /home/blyth/junotop/opticks/g4cx/tests/G4CXApp.h:317
    #17 0x000000000040a8ad in G4CXApp::Main () at /home/blyth/junotop/opticks/g4cx/tests/G4CXApp.h:324
    #18 0x000000000040aa37 in main (argc=1, argv=0x7fffffff2188) at /home/blyth/junotop/opticks/g4cx/tests/G4CXTest.cc:16
    (gdb) 

::

    epsilon:opticks blyth$ opticks-f ADHOC
    ./sysrap/SEvt.cc:        fold->clear(); // ADHOC
    ./sysrap/SEvt.cc:        fold->clear();  // ADHOC : TRY TO HANDLE U4Recorder DUPLICATE KEY ISSUE
    epsilon:opticks blyth$ 


::

Looks like should move genstep tee up to lower level in SEvt::addFrameGenstep, 
instead of up in CSGOptiX::SimulateMain::

     169 void CSGOptiX::SimulateMain() // static
     170 {
     171     SEventConfig::SetRGModeSimulate();
     172     CSGFoundry* fd = CSGFoundry::Load();
     173     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     174 
     175     LOG(info)
     176         << " " << SEventConfig::kNumEvent    << "=" << SEventConfig::NumEvent()
     177         << " " << SEventConfig::kRunningMode << "=" << SEventConfig::RunningModeLabel()
     178         << " SEventConfig::IsRunningModeTorch() " << ( SEventConfig::IsRunningModeTorch() ? "YES" : "NO " )
     179         ;
     180 
     181     for(int i=0 ; i < SEventConfig::NumEvent() ; i++)
     182     {
     183         if(SEventConfig::IsRunningModeTorch()) SEvt::AddTorchGenstep();
     184         cx->simulate(i);
     185     }
     186 }














Review the PMT info journey : PMTSimParamSvc/Data -> SPMT -> QPMT 
---------------------------------------------------------------------

Methods needed::

    305     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    306     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    307     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
    308     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    309 
    310     std::array<double,16> a_spec ;
    311     accessor->get_stackspec(a_spec, pmtcat, energy_eV );




    
FIXED : Issue 2 : standalone optical starting from GDML lacks sensor association
----------------------------------------------------------------------------------

Fix avoids:: 

    2023-11-21 11:21:08.800 INFO  [382763] [U4Recorder::EndOfEventAction@314]  savedir -
    //qsim::propagate_at_surface_CustomART idx     515 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     522 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     526 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     527 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     528 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     610 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 


* operating from GDML means that sensor info lost  

  * maybe this is because a geometry import from GDML is happening ? 
    NOPE, its a creation from GDML : not an import from SSim/stree

  * grabbing the GEOM from the CSGFoundry written live should avoid this issue ?

    * that will only work for the A side, not the B side : unless fixup 
      the sensor info later

  * so need the GDML for Geant4 and the pre-cooked CSGFoundry for Opticks 
    instead of creating the CSGFoundry again ? 

    * need to find a way to get the GDML to carry the sensor info : using GDML aux for example  





Review SensitiveDetector association and GDMLAux
---------------------------------------------------


::

    epsilon:u4 blyth$ grep GetSensitive *.*
    InstrumentedG4OpBoundaryProcess.cc:    G4VSensitiveDetector* sd = aStep.GetPostStepPoint()->GetSensitiveDetector();
    U4Recorder.cc:    235                                    GetSensitiveDetector();
    U4SensorIdentifierDefault.h:    G4VSensitiveDetector* sd = lv->GetSensitiveDetector() ;
    U4Touchable.h:        //const G4VSensitiveDetector* dsd = dlv->GetSensitiveDetector(); 
    U4Touchable.h:        //const G4VSensitiveDetector* msd = mlv->GetSensitiveDetector(); 
    U4Tree.h:Initially tried to simply use lv->GetSensitiveDetector() to 



U4SensorIdentifierDefault : has a kludge for global sensors, 
but not for instanced. Those rely on un-denuded Geant4 geometry
with Sensitive intact. 

g4cx/tests/G4CXTest.sh::

    137 export U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST=$(cat << EOL
    138 
    139     Pyrex/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/HamamatsuR12860_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    140     Pyrex/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/NNVTMCPPMT_PMT_20inch_photocathode_mirror_logsurf/Vacuum
    141     Pyrex/PMT_3inch_photocathode_logsurf2/PMT_3inch_photocathode_logsurf1/Vacuum
    142     Pyrex/PMT_20inch_veto_photocathode_logsurf2/PMT_20inch_veto_photocathode_logsurf1/Vacuum
    143 
    144     Pyrex/nnvt_photocathode_mirror_logsurf/nnvt_photocathode_mirror_logsurf/Vacuum
    145 
    146 EOL
    147 )

Could do the same with INSTANCED : but still that will not fix Geant4 lacking sensitive::

    epsilon:qudarap blyth$ jgr SetSensitiveDetector
    ./Simulation/DetSimV2/PMTSim/src/Hello3inchPMTManager.cc:    body_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/Hello3inchPMTManager.cc:    inner1_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/dyw_PMT_LogicalVolume.cc:  body_log->SetSensitiveDetector(detector);
    ./Simulation/DetSimV2/PMTSim/src/dyw_PMT_LogicalVolume.cc:  inner1_log->SetSensitiveDetector(detector);
    ./Simulation/DetSimV2/PMTSim/src/dyw_PMT_LogicalVolume.cc:  face_log->SetSensitiveDetector(detector);
    ./Simulation/DetSimV2/PMTSim/src/dyw_PMT_LogicalVolume.cc:  face_interior_log->SetSensitiveDetector(detector);
    ./Simulation/DetSimV2/PMTSim/src/Hello8inchPMTManager.cc:    body_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/Hello8inchPMTManager.cc:    inner1_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/R12860TorusPMTManager.cc:    body_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/R12860TorusPMTManager.cc:    inner1_log->SetSensitiveDetector(m_detector);
    ./Simulation/DetSimV2/PMTSim/src/MCP20inchPMTManager.cc:    body_log->SetSensitiveDetector(m_detector);

jcv HamamatsuR12860PMTManager::

   G4VSensitiveDetector *m_detector; 

   205     G4SDManager* SDman = G4SDManager::GetSDMpointer();
   206     m_detector = SDman->FindSensitiveDetector("PMTSDMgr");

jcv PMTSDMgr



::

   opticks-f GDMLAux
   .. loads in old workflow, none in new ...


So the parser gives access to a map of lv with aux info::

    169 BMeta* X4GDML::getLVMeta() const
    170 {
    171     const G4GDMLAuxMapType* auxmap = m_parser->GetAuxMap();
    172     if( auxmap->size() == 0 ) return NULL ;
    173 
    174     BMeta* lvmeta = new BMeta ;
    175 
    176     typedef G4GDMLAuxMapType::const_iterator MIT ;
    177     typedef G4GDMLAuxListType::const_iterator VIT ;
    178 
    179     for (MIT mit = auxmap->begin(); mit != auxmap->end(); mit++)
    180     {
    181         G4LogicalVolume* lv = mit->first ;
    182         G4GDMLAuxListType ls = mit->second ;
    183         const G4String& lvname = lv->GetName();
    184 

Could create placeholder G4VSensitiveDetector and 
associate that with the marked lv after loading the GDML.

How to programmatically add. 

g4-cls G4GDMLParser::

    117    inline G4GDMLMatrix GetMatrix(const G4String& name) const;
    118    inline G4LogicalVolume* GetVolume(const G4String& name) const;
    119    inline G4VPhysicalVolume* GetWorldVolume(const G4String& setupName="Default") const;
    120    inline G4GDMLAuxListType GetVolumeAuxiliaryInformation(G4LogicalVolume* lvol) const;
    121    inline const G4GDMLAuxMapType* GetAuxMap() const;
    122    inline const G4GDMLAuxListType* GetAuxList() const;
    123    inline void AddAuxiliary(G4GDMLAuxStructType myaux);
    124    inline void StripNamePointers() const;
     
::

    179 inline
    180 void G4GDMLParser::AddAuxiliary(G4GDMLAuxStructType myaux)
    181 {
    182   return writer->AddAuxiliary(myaux);
    183 }
    184 

    211 inline void G4GDMLParser::SetSDExport(G4bool flag)
    212 {
    213   writer->SetSDExport(flag);
    214 }






    126    inline void SetOverlapCheck(G4bool);
    127    inline void SetRegionExport(G4bool);
    128    inline void SetEnergyCutsExport(G4bool);

    129    inline void SetSDExport(G4bool);
    130 

    136    // Methods for Writer
    137    //
    138    inline void AddModule(const G4VPhysicalVolume* const physvol);
    139    inline void AddModule(const G4int depth);
    140    inline void SetAddPointerToName(G4bool set);
    141    inline void AddVolumeAuxiliary(G4GDMLAuxStructType myaux, const G4LogicalVolume* const lvol);
    142 


g4-cls G4GDMLWriteStructure::

    633 void
    634 G4GDMLWriteStructure::SetSDExport(G4bool fsd)
    635 {
    636   sdexport = fsd;
    637 }

    640 void
    641 G4GDMLWriteStructure::ExportSD(const G4LogicalVolume* const lvol)
    642 {  
    643   G4VSensitiveDetector* sd = lvol->GetSensitiveDetector();
    644    
    645   if(sd)
    646     {                               
    647       G4String SDname = sd->GetName();
    648       
    649       G4GDMLAuxStructType SDinfo = {"SensDet", SDname, "", 0};
    650       AddVolumeAuxiliary(SDinfo, lvol);
    651     }
    652 }  



Confirm creation
-------------------


::

    LOG=1 BP=sn::increase_zmax_  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh dbg

    (gdb) bt
    #0  0x00007ffff7f08ec0 in sn::increase_zmax_(double)@plt () from /data/blyth/junotop/ExternalLibs/opticks/head/lib/../lib64/libG4CX.so
    #1  0x00007ffff7f367b0 in sn::increase_zmax (this=0x199a170, dz=1) at /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sn.h:2594
    #2  0x00007ffff7f366ac in sn::ZNudgeOverlapJoint (lvid=95, i=1, lower=0x199a170, upper=0x199a350, enable=true, out=0x0)
        at /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sn.h:2537
    #3  0x00007ffff7f3627a in sn::ZNudgeOverlapJoints (lvid=95, prims=..., enable=true) at /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/sn.h:2426
    #4  0x00007ffff7f4760f in U4Polycone::init_outer (this=0x7fffffff0490) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Polycone.h:414
    #5  0x00007ffff7f47094 in U4Polycone::init (this=0x7fffffff0490) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Polycone.h:302
    #6  0x00007ffff7f46e35 in U4Polycone::U4Polycone (this=0x7fffffff0490, polycone_=0x9990d0, lvid_=95, depth_=0, level_=-1)
        at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Polycone.h:276
    #7  0x00007ffff7f4637e in U4Polycone::Convert (polycone=0x9990d0, lvid=95, depth=0, level=-1) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Polycone.h:176
    #8  0x00007ffff7f493e3 in U4Solid::init_Polycone (this=0x7fffffff0780) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Solid.h:707
    #9  0x00007ffff7f4843e in U4Solid::init_Constituents (this=0x7fffffff0780) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Solid.h:396
    #10 0x00007ffff7f4827a in U4Solid::init (this=0x7fffffff0780) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Solid.h:354
    #11 0x00007ffff7f4814d in U4Solid::U4Solid (this=0x7fffffff0780, solid_=0x9990d0, lvid_=95, depth_=0, level_=-1)
        at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Solid.h:341
    #12 0x00007ffff7f4808f in U4Solid::Convert (solid=0x9990d0, lvid=95, depth=0, level=-1) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Solid.h:319
    #13 0x00007ffff7f4bd40 in U4Tree::initSolid (this=0x18b03f0, so=0x9990d0, lvid=95) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:566
    #14 0x00007ffff7f4bc98 in U4Tree::initSolid (this=0x18b03f0, lv=0x9d6a70) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:525
    #15 0x00007ffff7f4bc2e in U4Tree::initSolids_r (this=0x18b03f0, pv=0xa380f0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:518
    #16 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x160f180) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #17 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x16b2ad0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #18 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x17835c0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #19 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x1783760) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #20 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x17838d0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #21 0x00007ffff7f4bbc9 in U4Tree::initSolids_r (this=0x18b03f0, pv=0x72c7d0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:515
    #22 0x00007ffff7f4bb6b in U4Tree::initSolids (this=0x18b03f0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:509
    #23 0x00007ffff7f4af1a in U4Tree::init (this=0x18b03f0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:255
    #24 0x00007ffff7f4ae4b in U4Tree::U4Tree (this=0x18b03f0, st_=0x72dbf0, top_=0x72c7d0, sid_=0x0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:235
    #25 0x00007ffff7f4ab1a in U4Tree::Create (st=0x72dbf0, top=0x72c7d0, sid=0x0) at /home/blyth/junotop/ExternalLibs/opticks/head/include/U4/U4Tree.h:204
    #26 0x00007ffff7f0e41d in G4CXOpticks::setGeometry (this=0x18b0540, world=0x72c7d0) at /home/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:248
    #27 0x00007ffff7f0cbdf in G4CXOpticks::SetGeometry (world=0x72c7d0) at /home/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:63
    #28 0x0000000000408ae8 in G4CXApp::Construct (this=0x6c1a00) at /home/blyth/junotop/opticks/g4cx/tests/G4CXApp.h:175
    #29 0x00007ffff70e3a8e in G4RunManager::InitializeGeometry() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #30 0x00007ffff70e3c5c in G4RunManager::Initialize() ()




G4CXTest_GEOM shakedown
--------------------------


::

    N[blyth@localhost tests]$ ./G4CXTest_GEOM.sh
                                           BASH_SOURCE : ./G4CXTest_GEOM.sh 
                                                  GEOM : V1J011 
                                 V1J011_CFBaseFromGEOM : /home/blyth/.opticks/GEOM/V1J011 
                                       V1J011_GDMLPath : /home/blyth/.opticks/GEOM/V1J011/origin.gdml 
                                               VERSION : 0 
                                                   TMP : /home/blyth/tmp 
                                                 AFOLD : /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/p001 
                                                 BFOLD : /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/n001 
                                               evtfold : /home/blyth/tmp/GEOM/V1J011 
                                                   CVD :  
                                  CUDA_VISIBLE_DEVICES : 1 
    2023-11-21 11:19:17.039 INFO  [382763] [G4CXApp::Create@270] U4Recorder::Switches
    WITH_CUSTOM4
    NOT:WITH_PMTSIM
    NOT:PMTSIM_STANDALONE
    PRODUCTION

    2023-11-21 11:21:08.666 INFO  [382763] [U4Recorder::BeginOfRunAction@253] 
    2023-11-21 11:21:08.667 INFO  [382763] [G4CXApp::GeneratePrimaries@201] [ fPrimaryMode T
    U4VPrimaryGenerator::GeneratePrimaries ph (1000, 4, 4, )
    2023-11-21 11:21:08.668 INFO  [382763] [G4CXApp::GeneratePrimaries@215] ]
    2023-11-21 11:21:08.669 INFO  [382763] [U4Recorder::BeginOfEventAction@288]  eventID 0
    2023-11-21 11:21:08.669 INFO  [382763] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 1000
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.6525 _qe 1 stack.art.A (aka An) 0.605144
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281


Looks like standalone running is using placeholder _qe of 1. that 
leads to theEfficiency > 1. ::

    305     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    306     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    307     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
    308     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    309 
    310     std::array<double,16> a_spec ;
    311     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    312 
    313     const double* ss = a_spec.data() ;
    314 
    315     Stack<double,4> stack ;
    316 
    317     theEfficiency = zero ;
    318     if( minus_cos_theta < zero ) // only ingoing photons 
    319     {
    320         stack.calc( wavelength_nm, minus_one, zero, ss, 16u );
    321         theEfficiency = _qe/stack.art.A ;    // aka escape_fac
    322 
    323         bool expect = theEfficiency <= 1. ;
    324         if(!expect) std::cerr
    325             << "C4CustomART::doIt"
    326             << " FATAL "
    327             << " ERR: theEfficiency > 1. : " << theEfficiency
    328             << " _qe " << _qe
    329             << " stack.art.A (aka An) " << stack.art.A
    330             << std::endl
    331             ;
    332         assert( expect );
    333     }
    334     stack.calc( wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, ss, 16u );



::

    2023-11-21 17:21:57.205 INFO  [57614] [G4CXApp::Construct@168] ]
    2023-11-21 17:21:57.205 INFO  [57614] [SSim::AddExtraSubfold@36]  k jpmt dir $PMTSimParamData_BASE
    U::Resolve token [PMTSimParamData_BASE] does not resolve 
    2023-11-21 17:21:57.205 INFO  [57614] [SSim::AddExtraSubfold@45]  DOESNT EXIST : SKIP 
    2023-11-21 17:21:57.205 INFO  [57614] [SSim::init@159] [ new scontext
    2023-11-21 17:21:57.250 INFO  [57614] [SSim::init@161] ] new scontext

::

    epsilon:j blyth$ opticks-f PMTSimParamData_BASE
    ./u4/U4Physics.cc:    const char* path = "$PMTSimParamData_BASE" ;  // directory with PMTSimParamData subfolder
    ./u4/tests/U4PMTAccessorTest.sh:export PMTSimParamData_BASE=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData
    ./u4/tests/U4PMTFastSimTest.sh:export PMTSimParamData_BASE=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData
    ./u4/tests/FewPMT_test.cc:    const char* path = "$PMTSimParamData_BASE" ; 
    ./u4/tests/FewPMT.sh:#export PMTSimParamData_BASE=$HOME/.opticks/GEOM/J007/CSGFoundry/SSim/juno
    ./u4/tests/FewPMT.sh:export PMTSimParamData_BASE=$HOME/.opticks/GEOM/V1J009/CSGFoundry/SSim/extra/jpmt
    ./g4cx/tests/G4CXTest.sh:vars="BASH_SOURCE SDIR U4TDIR BINDIR GEOM bin ana tra geomscript BASE FOLD AFOLD BFOLD TFOLD PMTSimParamData_BASE" 
    ./g4cx/tests/G4CXApp.h:    SSim::AddExtraSubfold("jpmt", "$PMTSimParamData_BASE" ); 
    epsilon:opticks blyth$ 

Add to GEOM::

    jpmt=$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/extra/jpmt
    if [ -d "$jpmt" ]; then 
        export PMTSimParamData_BASE=$jpmt
    fi

::

    2023-11-21 20:41:39.223 INFO  [371699] [G4CXApp::Construct@166]  fPV lWorld0x9aaefb0_PV
    2023-11-21 20:41:39.223 INFO  [371699] [G4CXApp::Construct@168] ]
    2023-11-21 20:41:39.223 INFO  [371699] [SSim::AddExtraSubfold@36]  k jpmt dir $PMTSimParamData_BASE
    2023-11-21 20:41:39.229 INFO  [371699] [SSim::AddExtraSubfold@40]  fold YES
    2023-11-21 20:41:39.229 INFO  [371699] [SSim::init@159] [ new scontext
    2023-11-21 20:41:39.279 INFO  [371699] [SSim::init@161] ] new scontext
    2023-11-21 20:41:39.279 INFO  [371699] [SSim::init@163] scontext::desc [1:NVIDIA_TITAN_RTX]


HMM : TODO trace the _qe::

    2023-11-21 20:43:28.240 INFO  [371699] [U4Recorder::BeginOfEventAction@288]  eventID 0
    2023-11-21 20:43:28.241 INFO  [371699] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 1000
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.6525 _qe 1 stack.art.A (aka An) 0.605144
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281


But first a clean build, as update builds have some phlogiston in them.::

    2023-11-21 11:21:08.797 INFO  [382763] [U4Recorder::PreUserTrackingAction_Optical@378]  modulo 100000 : ulabel.id 0
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    2023-11-21 11:21:08.798 INFO  [382763] [U4Recorder::MakeMetaArray@676] U4Recorder::DescFakes  
    U4Recorder::FAKES_SKIP NO 
    U4Recorder::FAKES      YES
    FAKES.size             0

    NPFold::copy keylist hit count 0 kk.size 2 meta source:U4Recorder::init_SEvt
    creator:G4CXTest
    stamp:1700536757087432
    stampFmt:2023-11-21T11:19:17.087432
    uname:Linux localhost.localdomain 3.10.0-957.10.1.el7.x86_64 #1 SMP Mon Mar 18 15:06:45 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
    CUDA_VISIBLE_DEVICES:1
    HOME:/home/blyth
    USER:blyth
    PWD:/home/blyth/junotop/opticks/g4cx/tests
    VERSION:0
    GEOM:V1J011
    ${GEOM}_GEOMList:V1J011_GEOMList
    C4Version:TBD
    site:SEvt::endMeta
    hitmask:64
    index:1
    instance:1
    p_SEvt__beginOfEvent_0:1700536868669039,7470012,1001808
    p_SEvt__beginOfEvent_1:1700536868669120,7470012,1001972
    p_SEvt__endOfEvent_0:1700536868798350,7470844,1003188

    2023-11-21 11:21:08.799 INFO  [382763] [SEvt::save@3404]  dir /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/n001 index 1 instance 1 OPTICKS_SAVE_COMP  hit
    2023-11-21 11:21:08.800 INFO  [382763] [U4Recorder::EndOfEventAction@314]  savedir -
    //qsim::propagate_at_surface_CustomART idx     515 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     522 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     526 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     527 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     528 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     610 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     611 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     612 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     615 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     622 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     624 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx     626 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 


::

    1752 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, curandStateXORWOW& rng, sctx& ctx) const
    1753 {
    1754 
    1755     const sphoton& p = ctx.p ;
    1756     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal 
    1757     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor  
    1758     float minus_cos_theta = dot(p.mom, *normal);
    1759     float dot_pol_cross_mom_nrm = dot(p.pol,cross(p.mom,*normal)) ;
    1760 
    1761 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1762     if( ctx.idx == base->pidx )
    1763     {
    1764     float3 cross_mom_nrm = cross(p.mom, *normal) ;
    1765     printf("//qsim::propagate_at_surface_CustomART idx %7d : mom = np.array([%10.8f,%10.8f,%10.8f]) ; lmom = %10.8f \n",
    1766        ctx.idx, p.mom.x, p.mom.y, p.mom.z, length(p.mom) );
    1767     printf("//qsim::propagate_at_surface_CustomART idx %7d : pol = np.array([%10.8f,%10.8f,%10.8f]) ; lpol = %10.8f \n",
    1768        ctx.idx, p.pol.x, p.pol.y, p.pol.z, length(p.pol) );
    1769     printf("//qsim::propagate_at_surface_CustomART idx %7d : nrm = np.array([%10.8f,%10.8f,%10.8f]) ; lnrm = %10.8f \n",
    1770        ctx.idx, normal->x, normal->y, normal->z, length(*normal) );
    1771     printf("//qsim::propagate_at_surface_CustomART idx %7d : cross_mom_nrm = np.array([%10.8f,%10.8f,%10.8f]) ; lcross_mom_nrm = %10.8f  \n",
    1772            ctx.idx, cross_mom_nrm.x, cross_mom_nrm.y, cross_mom_nrm.z, length(cross_mom_nrm)  );
    1773     printf("//qsim::propagate_at_surface_CustomART idx %7d : dot_pol_cross_mom_nrm = %10.8f \n", ctx.idx, dot_pol_cross_mom_nrm );
    1774     printf("//qsim::propagate_at_surface_CustomART idx %7d : minus_cos_theta = %10.8f \n", ctx.idx, minus_cos_theta );
    1775     }
    1776 #endif
    1777 
    1778     if(lpmtid < 0 )
    1779     {
    1780         flag = NAN_ABORT ;
    1781 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1782         //if( ctx.idx == base->pidx ) 
    1783         printf("//qsim::propagate_at_surface_CustomART idx %7d lpmtid %d : ERROR NOT-A-SENSOR : NAN_ABORT \n", ctx.idx, lpmtid );
    1784 #endif
    1785         return BREAK ;
    1786     }









    //qsim::propagate_at_surface_CustomART idx     154 lpmtid -1 : ERROR NOT-A-SENSOR : NAN_ABORT 
    2023-11-21 11:21:08.827 INFO  [382763] [SEvt::save@3404]  dir /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/p001 index 1 instance 0 OPTICKS_SAVE_COMP  hit
    Python 3.7.7 (default, May  7 2020, 21:25:33) 
    Type 'copyright', 'credits' or 'license' for more information
    IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.
    [from opticks.ana.p import * 
    CSGFoundry.CFBase returning [/home/blyth/.opticks/GEOM/V1J011], note:[via GEOM] 
    ]from opticks.ana.p import * 
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$AFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol a pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/p001 
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ('$BFOLD',) quiet:1
    sevt.init W2M
     None
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/n001 
    [--- ab = SAB(a,b) ----
    ]--- ab = SAB(a,b) ----
    [----- repr(ab) 
    SAB
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/p001 
    a

    CMDLINE:/data/blyth/junotop/opticks/g4cx/tests/G4CXTest_GEOM.py
    a.base:/home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/p001

      : a.NPFold_index                                     :                 (1,) : 0:00:01.899962 
      : a.hit                                              :            (9, 4, 4) : 0:00:01.899962 
      : a.NPFold_meta                                      :                   28 : 0:00:01.899962 
      : a.sframe                                           :            (4, 4, 4) : 0:00:01.899962 
      : a.sframe_meta                                      :                    5 : 0:00:01.899962 

     min_stamp : 2023-11-21 11:21:08.827064 
     max_stamp : 2023-11-21 11:21:08.827064 
     dif_stamp : 0:00:00 
     age_stamp : 0:00:01.899962 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/n001 
    b

    CMDLINE:/data/blyth/junotop/opticks/g4cx/tests/G4CXTest_GEOM.py
    b.base:/home/blyth/tmp/GEOM/V1J011/G4CXTest/ALL0/n001

      : b.NPFold_index                                     :                 (0,) : 0:00:01.928298 
      : b.NPFold_meta                                      :                   27 : 0:00:01.928298 
      : b.pho0                                             :            (1000, 4) : 0:00:01.928298 
      : b.pho                                              :            (1000, 4) : 0:00:01.928298 
      : b.gs                                               :               (1, 4) : 0:00:01.928298 
      : b.sframe                                           :            (4, 4, 4) : 0:00:01.927298 
      : b.sframe_meta                                      :                    5 : 0:00:01.927298 

     min_stamp : 2023-11-21 11:21:08.799064 
     max_stamp : 2023-11-21 11:21:08.800064 
     dif_stamp : 0:00:00.001000 
     age_stamp : 0:00:01.927298 
    a.CHECK :  
    b.CHECK :  
    ]----- repr(ab) 
    np.c_[np.unique(a.q, return_counts=True)] 
    [[None 1]]
    np.c_[np.unique(b.q, return_counts=True)] 
    [[None 1]]
    PICK=A MODE=3  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh 



::

    152 G4VPhysicalVolume* G4CXApp::Construct()
    153 {
    ...
    164     G4VPhysicalVolume* pv = const_cast<G4VPhysicalVolume*>(pv_);
    165     fPV = pv ;
    166     LOG(LEVEL) << " fPV " << ( fPV ? fPV->GetName() : "ERR-NO-PV" ) ;
    167 
    168     LOG(info) << "]" ;
    169 
    170     // Collect extra JUNO PMT info only when persisted NPFold exists.
    171     SSim::AddExtraSubfold("jpmt", "$PMTSimParamData_BASE" );
    172 

     34 void SSim::AddExtraSubfold(const char* k, const char* dir) // static
     35 {
     36     LOG(LEVEL) << " k " << k << " dir " << dir ;
     37     if(NPFold::Exists(dir))
     38     {
     39         NPFold* fold = NPFold::Load(dir) ;
     40         LOG(LEVEL) << " fold " << ( fold ? "YES" : "NO " ) ;
     41         AddExtraSubfold(k, fold );
     42     }
     43     else
     44     {
     45         LOG(LEVEL) << " DOESNT EXIST : SKIP " ;
     46     }
     47 }





DONE : standalone QPMT/SPMT shakedown 
---------------------------------------

::

    N[blyth@localhost ~]$ LOG=1 ~/opticks/g4cx/tests/G4CXTest_GEOM.sh




    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## in A but not B 
    [[' 0' 'TO BT BT BT BT BT BT NA      ' ' 0' '   229      0' '229.0000' '     5     -1']
     [' 3' 'TO SC BT BT BT BT BT BT NA   ' ' 3' '    98      0' '98.0000' '     6     -1']
     [' 6' 'TO SC SC BT BT BT BT BT BT NA' ' 6' '    42      0' '42.0000' '    19     -1']
     [' 9' 'TO RE BT BT BT BT BT BT NA   ' ' 9' '    29      0' ' 0.0000' '    10     -1']
     ['15' 'TO SC RE BT BT BT BT BT BT NA' '15' '    16      0' ' 0.0000' '    49     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## in B but not A 
    [[' 1' 'TO BT BT BT BT BT BT SD      ' ' 1' '     0    177' '177.0000' '    -1      0']
     [' 4' 'TO SC BT BT BT BT BT BT SD   ' ' 4' '     0     63' '63.0000' '    -1      4']
     [' 7' 'TO BT BT BT BT BT BT BR BT BT' ' 7' '     0     31' '31.0000' '    -1     10']
     ['14' 'TO RE BT BT BT BT BT BT SD   ' '14' '     0     17' ' 0.0000' '    -1     23']
     ['19' 'TO SC BT BT BT BT BT BT BT SR' '19' '     0     11' ' 0.0000' '    -1     34']]
    ]----- repr(ab) 



Hmm QPMT looks to be there::

    2023-11-21 21:14:09.609 INFO  [435781] [QPMT<T>::init_lcqs@126]  src_lcqs (17612, 2, ) lcqs (17612, 2, )
    2023-11-21 21:14:09.609 INFO  [435781] [QSim::UploadComponents@187] QPMT<float> WITH_CUSTOM4  INSTANCE:YES QPMT::desc
                           rindex (24, 15, 2, )
                          qeshape (3, 44, 2, )
                        thickness (3, 4, 1, )
                             lcqs (17612, 2, )
                  pmt.rindex_prop 0x7feb12603c00
                 pmt.qeshape_prop 0x7feb12604400
                    pmt.thickness 0x7feb12604600
                         pmt.lcqs 0x7feb12604800
                            d_pmt 0x7feb12627000

     spmt_f YES qpmt YES
    2023-11-21 21:14:09.610 INFO  [435781] [QSim::QSim@249] QSim::desc
     this 0x11b750b0 INSTANCE 0x0 QEvent.hh:event 0x11b4ef70 qsim.h:sim 0x0
    2023-11-21 21:14:09.610 INFO  [435781] [QSim::init@289] QSim::desc
     this 0x11b750b0 INSTANCE 0x11b750b0 QEvent.hh:event 0x11b4ef70 qsim.h:sim 0x11b74370
    2023-11-21 21:14:09.610 INFO  [435781] [QSim::init@290] 
    QSim::descComponents
     (QBase)base             YES
     (QEvent)event           YES
     (SEvt)sev               YES
     (QRng)rng               YES
     (QScint)scint           YES
     (QCerenkov)cerenkov     YES
     (QBnd)bnd               YES
     (QOptical)optical       YES
     (QDebug)debug_          YES
     (QProp)prop             YES
     (QPMT)pmt               YES
     (QMultiFilm)multifilm   NO 
     (qsim)sim               YES
     (qsim)d_sim             YES
     (qdebug)dbg             YES
     (qdebug)d_dbg           YES


Maybe the old sensor labelling chestnut ? 


DONE : Chase the C4 accessor
-------------------------------

::

    2023-11-21 21:15:43.951 INFO  [435781] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 1000
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.6525 _qe 1 stack.art.A (aka An) 0.605144
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281
    C4CustomART::doIt FATAL  ERR: theEfficiency > 1. : 1.56671 _qe 1 stack.art.A (aka An) 0.638281

::

    293 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    294 {
    295     G4double zero = 0. ;
    296     G4double minus_one = -1. ;
    297     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    298     G4double dot_pol_cross_mom_nrm = OldPolarization*OldMomentum.cross(theRecoveredNormal) ;
    299 
    300     G4double energy = thePhotonMomentum ;
    301     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    302     G4double energy_eV = energy/CLHEP::eV ;
    303     G4double wavelength_nm = wavelength/CLHEP::nm ;
    304 
    305     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    306     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    307     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
    308     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    309 
    310     std::array<double,16> a_spec ;
    311     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    312 
    313     const double* ss = a_spec.data() ;
    314 
    315     Stack<double,4> stack ;
    316 
    317     theEfficiency = zero ;
    318     if( minus_cos_theta < zero ) // only ingoing photons 
    319     {
    320         stack.calc( wavelength_nm, minus_one, zero, ss, 16u );
    321         theEfficiency = _qe/stack.art.A ;    // aka escape_fac
    322 
    323         bool expect = theEfficiency <= 1. ;
    324         if(!expect) std::cerr
    325             << "C4CustomART::doIt"
    326             << " FATAL "
    327             << " ERR: theEfficiency > 1. : " << theEfficiency
    328             << " _qe " << _qe
    329             << " stack.art.A (aka An) " << stack.art.A
    330             << std::endl
    331             ;
    332         assert( expect );
    333     }
    334     stack.calc( wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, ss, 16u );
    335 

The assert has been Release compiled away. 

C4 is Release compiled so debug doesnt help
----------------------------------------------


::

   LOG=1 BP=C4CustomART::doIt  ~/opticks/g4cx/tests/G4CXTest_GEOM.sh dbg 


::

    2023-11-21 21:34:22.919 INFO  [6677] [G4CXApp::GeneratePrimaries@215] ]
    2023-11-21 21:34:22.919 INFO  [6677] [U4Recorder::BeginOfEventAction@288]  eventID 0
    2023-11-21 21:34:22.920 INFO  [6677] [SEvt::hostside_running_resize_@1866] resizing photon 0 to evt.num_photon 1000

    Thread 1 "G4CXTest" hit Breakpoint 1, 0x00007ffff4b4b1d0 in C4CustomART::doIt(G4Track const&, G4Step const&)@plt () from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    (gdb) bt
    #0  0x00007ffff4b4b1d0 in C4CustomART::doIt(G4Track const&, G4Step const&)@plt ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #1  0x00007ffff4b54062 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3.dc1/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #2  0x00007ffff70018d9 in G4SteppingManager::InvokePSDIP(unsigned long) ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007ffff7001ccb in G4SteppingManager::InvokePostStepDoItProcs() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007ffff6fff53e in G4SteppingManager::Stepping() ()
       from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007ffff700aaaf in G4TrackingManager::ProcessOneTrack(G4Track*) ()







::

    287 /**
    288 U4Physics::CreateBoundaryProcess
    289 ---------------------------------
    290 
    291 Looks like this needs updating now that it
    292 is normal to use WITH_CUSTOM4 within junosw+opticks
    293 without using WITH_PMTSIM
    294 
    295 **/
    296 
    297 G4VProcess* U4Physics::CreateBoundaryProcess()  // static 
    298 {
    299     G4VProcess* proc = nullptr ;
    300 
    301 #if defined(WITH_PMTSIM) && defined(WITH_CUSTOM4)
    302     const char* path = "$PMTSimParamData_BASE" ;  // directory with PMTSimParamData subfolder
    303     const PMTSimParamData* data = PMTAccessor::LoadData(path) ;
    304     LOG(LEVEL) << "load path "  << path << " giving PMTSimParamData.data: " << ( data ? "YES" : "NO" ) ;
    305     //LOG_IF(LEVEL, data != nullptr ) << *data ; 
    306 
    307     const PMTAccessor* pmt = PMTAccessor::Create(data) ;
    308     const C4IPMTAccessor* ipmt = pmt ;
    309     proc = new C4OpBoundaryProcess(ipmt);
    310 
    311     LOG(LEVEL) << "create C4OpBoundaryProcess :  WITH_CUSTOM4 WITH_PMTSIM " ;
    312 
    313 #elif defined(WITH_CUSTOM4)
    314     const U4PMTAccessor* pmt = new U4PMTAccessor ;
    315     const C4IPMTAccessor* ipmt = pmt ;
    316     proc = new C4OpBoundaryProcess(ipmt);
    317     LOG(LEVEL) << "create C4OpBoundaryProcess :  WITH_CUSTOM4 NOT:WITH_PMTSIM " ;
    318 #else
    319     proc = new InstrumentedG4OpBoundaryProcess();
    320     LOG(LEVEL) << "create InstrumentedG4OpBoundaryProcess : NOT (WITH_PMTSIM and WITH_CUSTOM4) " ;
    321 #endif
    322     return proc ;
    323 }
    324 


::

    2023-11-21 21:48:42.083 INFO  [31640] [U4Physics::ConstructOp@225] G4OpAbsorption_DISABLE      : 0
    2023-11-21 21:48:42.083 INFO  [31640] [U4Physics::ConstructOp@226] G4OpRayleigh_DISABLE        : 0
    2023-11-21 21:48:42.083 INFO  [31640] [U4Physics::ConstructOp@227] G4OpBoundaryProcess_DISABLE : 0
    2023-11-21 21:48:42.083 INFO  [31640] [U4Physics::CreateBoundaryProcess@317] create C4OpBoundaryProcess :  WITH_CUSTOM4 NOT:WITH_PMTSIM 
    2023-11-21 21:48:42.083 INFO  [31640] [U4Physics::ConstructOp@250]  fBoundary 0x35aaf5f0



Missing the PMTAccessor::

    371 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    372 {
    373     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    374 
    375     if(psps_ptr.invalid())
    376     {
    377         std::cout << "invalid" << std::endl ;
    378         return nullptr ;
    379     }
    380 
    381     IPMTSimParamSvc* ipsps = psps_ptr.data();
    382     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    383 
    384     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    385     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    386     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    387 
    388     return boundproc ;
    389 }


HMM: tis looking like will need to use j/PMTSim to 
slip in the bits of junosw needed to furnish the PMT 
data to the otherwise standalone G4CXTest ? 


Bingo : its the mock standin accessor : as no PMTSim
---------------------------------------------------------

::

     01 #pragma once
      2 /**
      3 U4PMTAccessor.h
      4 ================
      5 
      6 This is a mock standin for "jcv PMTAccessor" 
      7 for usage WITH_CUSTOM4 NOT:WITH_PMTSIM
      8 
      9 **/
     10 
     11 #ifdef WITH_CUSTOM4
     12 #include "C4IPMTAccessor.h"
     13 
     14 struct U4PMTAccessor : public C4IPMTAccessor
     15 {   
     16     static constexpr const char* TypeName = "U4PMTAccessor" ;
     17     
     18     // C4IPMTAccessor interface 
     19     int    get_num_lpmt() const ; 
     20     double get_pmtid_qe( int pmtid, double energy ) const ;
     21     double get_qescale(  int pmtid ) const ;
     22     int    get_pmtcat( int pmtid  ) const ;  
     23     void   get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const ;
     24     const char* get_typename() const ;
     25 
     26 };
     27     
     28 
     29 inline int U4PMTAccessor::get_num_lpmt() const
     30 {   
     31     return 1000 ;
     32 }
     33 inline double U4PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const 
     34 {
     35     return 1. ; 
     36 }   





Could be the GDML sensor chestnut again : YES, it was that too
-------------------------------------------------------------------

::

    [stree::postcreate
    stree::desc_sensor
     sensor_id.size 0
     sensor_count 0
     sensor_name.size 0
    sensor_name[
    ]
    [stree::desc_sensor_nd
     edge            0
     num_nd          386112
     num_nd_sensor   0
     num_sid         0
    ]stree::desc_sensor_nd
    stree::desc_sensor_id sensor_id.size 0
    [





