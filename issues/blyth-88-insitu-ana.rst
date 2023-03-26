blyth-88-insitu-ana
=====================

j/ntds/ntds.sh 
---------------


HMM is this a(N=0) or b(N=1)::

    epsilon:ntds blyth$ ./ntds.sh 
    CSGFoundry.CFBase returning None, note:via NO envvars 
    ERROR CSGFoundry.CFBase returned None OR non-existing CSGFoundry dir so cannot CSGFoundry.Load
    Fold : symbol                              a base /tmp/blyth/opticks/GEOM/ntds2/ALL/000 
    U4SimulateTest symbol a pid -1 opt  off [0. 0. 0.]

    In [1]: a
    Out[1]: U4SimulateTest symbol a pid -1 opt  off [0. 0. 0.]

    In [2]: a.qtab
    Out[2]: 
    array([[b'1507', b'11', b'SI AB                                                                                           '],
           [b'528', b'7', b'SI BT BT BT BT BT BT SD                                                                         '],
           [b'510', b'26', b'SI BT BT BT BT BT BT SA                                                                         '],
           [b'447', b'0', b'SI RE AB                                                                                        '],
           [b'320', b'5', b'SI SC AB                                                                                        '],
           [b'287', b'30', b'SI SC BT BT BT BT BT BT SD                                                                      '],
           [b'225', b'29', b'SI SC BT BT BT BT BT BT SA                                                                      '],
           [b'168', b'83', b'SI RE BT BT BT BT BT BT SA                                                                      '],
           [b'167', b'65', b'SI RE BT BT BT BT BT BT SD                                                                      '],
           [b'142', b'8', b'SI BT BT SA                                                                                     '],
           [b'133', b'162', b'SI RE RE AB                                                                                     '],
           [b'97', b'15', b'SI BT BT AB                                                                                     '],
           [b'97', b'9', b'SI SC SC AB                                                                                     '],
           [b'89', b'118', b'SI RE SC AB                                                                                     '],
           [b'89', b'122', b'SI SC SC BT BT BT BT BT BT SD                                                                   '],
           [b'78', b'23', b'SI BT BT BT BT BT BT BT SA                                                                      '],
           [b'74', b'39', b'SI SC SC BT BT BT BT BT BT SA                                                                   '],
           [b'71', b'79', b'SI BT BT BT BT BT BT BT SR SA                                                                   '],
           [b'69', b'28', b'SI RE SC BT BT BT BT BT BT SA                                                                   '],
           [b'64', b'190', b'SI RE SC BT BT BT BT BT BT SD                                                                   ']], dtype='|S96')

    In [3]:                                               


Plotting a few things shows no clangers yet
---------------------------------------------

::

    MODE=2 ./ntds.sh 
    MODE=3 ./ntds.sh 


DONE : need insitu metadata to identify the POM/PMT quadrant from the fold
-----------------------------------------------------------------------------

* also need to control the SEvt output to go into different fold for VERSION 0/1

* VERSION envvar should change the SEvt reldir automatically 
  in SEvt::HighLevelCreate which is invoked by U4Recorder::U4Recorder


HUH seems that did not happen::

    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 28
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 28 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@151:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2055:  dir /tmp/blyth/opticks/GEOM/ntds2/ALL/000
    SEvt::gatherHit@1784:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@669: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully



::

     540 SEvt* SEvt::HighLevelCreate() // static
     541 {
     542     SEvt* evt = nullptr ;
     543 
     544     int g4state_rerun_id = SEventConfig::G4StateRerun();
     545     bool rerun = g4state_rerun_id > -1 ;
     546 
     547     const char* alldir = ssys::replace_envvar_token("ALL${VERSION}") ;
     548     const char* alldir0 = "ALL0" ;
     549     const char* seldir = ssys::replace_envvar_token("SEL${VERSION}") ;
     550 
     551     LOG(info)
     552         << " g4state_rerun_id " << g4state_rerun_id
     553         << " alldir " << alldir
     554         << " alldir0 " << alldir0
     555         << " seldir " << seldir
     556         << " rerun " << rerun
     557         ;
     558 
     559     if(rerun == false)
     560     { 
     561         evt = SEvt::Create();
     562         evt->setReldir(alldir);
     563     } 



* try doing this at bash level in ntds3::

::

    568    export OPTICKS_EVENT_MODE=StandardFullDebug
    569    export OPTICKS_MAX_BOUNCE=31
    570 
    571    export POM=${POM:-1}
    572    export VERSION=${N:-1}
    573    export LAYOUT="POM $POM VERSION $VERSION"
    574 
    575    local opts=""
    576    opts="$opts --opticks-mode $mode"
    577    opts="$opts --no-guide_tube"
    578    opts="$opts --additionacrylic-simplify-csg"
    579 
    580    #case $LSM in   ## pass into UseLSOpticalModel : NOT YET EXPLORED
    581    #   0) opts="$opts --old-optical-model"  ;;
    582    #   1) opts="$opts --new-optical-model"  ;;
    583    #esac 
    584 
    585    case $POM in     ## pass into UsePMTOpticalModel
    586       0) opts="$opts --no-pmt-optical-model"  ;;
    587       1) opts="$opts --pmt-optical-model"     ;;
    588    esac
    589 
    590    case $VERSION in  ## pass into UsePMTNaturalGeometry
    591       0) opts="$opts --pmt-unnatural-geometry" ;;
    592       1) opts="$opts --pmt-natural-geometry"   ;;
    593    esac
    594 
    595    opts="$opts --evtmax $evtmax"
    596    opts="$opts $(anamgr) "



::

    In [3]: a.f.photon_meta
    Out[3]: 
    SCRIPT:ntds2
    ${GEOM}_GEOMList:GEOM_GEOMList


Looks like problem with spaces in metadata::

    In [4]: a.f.photon_meta.lines
    Out[4]: ['SCRIPT:ntds2', 'LAYOUT:POM', 'VERSION:1', '${GEOM}_GEOMList:GEOM_GEOMList']


::

    1639 const char* SEvt::ENVMETA = R"LITERAL(
    1640 SCRIPT
    1641 CHECK
    1642 LAYOUT
    1643 TEST
    1644 VERSION
    1645 GEOM
    1646 EXECUTABLE
    1647 ${GEOM}_GEOMList
    1648 )LITERAL" ;
    1649 
    1650 // HIGHER ORDER KEYS WITH TOKENS ARE HANDLED IN ssys::_getenv
    1651 
    1652 void SEvt::AddEnvMeta( NP* a ) // static
    1653 {
    1654     if(a == nullptr) return ;
    1655     typedef std::pair<std::string, std::string> KV ;
    1656     std::vector<KV> kvs ;
    1657     ssys::getenv_(kvs, ENVMETA);
    1658     a->set_meta_kv(kvs) ;
    1659 }
    1660 
    1661 NP* SEvt::makePhoton() const
    1662 {
    1663     NP* p = NP::Make<float>( evt->num_photon, 4, 4 );
    1664     AddEnvMeta(p) ; 
    1665     return p ; 
    1666 }   




insitu metadata into photon array : getting truncation : FIXED ssys.h BUG
----------------------------------------------------------------------------

::

    In [3]: a.f.photon_meta
    Out[3]: 
    SCRIPT:ntds2
    LAYOUT:POM
    VERSION:1
    COMMANDLINE:gdb
    ${GEOM}_GEOMList:GEOM_GEOMList

    In [4]: a.f.photon_meta.lines
    Out[4]: 
    ['SCRIPT:ntds2',
     'LAYOUT:POM',
     'VERSION:1',
     'COMMANDLINE:gdb',
     '${GEOM}_GEOMList:GEOM_GEOMList']


    In [5]: t.photon_meta.COMMANDLINE
    Out[5]: ['gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun']

    In [6]: t.photon_meta 
    Out[6]: 
    SCRIPT:ntds2
    LAYOUT:POM 1 VERSION 1
    VERSION:1
    COMMANDLINE:gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun
    ${GEOM}_GEOMList:GEOM_GEOMList





SEvt reldir being stomped ? Unexpected SEvt instanciation 
-------------------------------------------------------------

Looks like SEvt::setReldir is done::

     559     // this runs early, at U4Recorder instanciation, which is before logging is setup it seems 
     560     std::cout
     561         << "SEvt::HighLevelCreate"
     562         << " g4state_rerun_id " << g4state_rerun_id
     563         << " alldir " << alldir
     564         << " alldir0 " << alldir0
     565         << " seldir " << seldir
     566         << " rerun " << rerun
     567         << std::endl
     568         ;
     569 
     570 
     571     if(rerun == false)
     572     {
     573         evt = SEvt::Create();
     574         evt->setReldir(alldir);
     575     }
     576     else

::

    ZC2.A03_A03.try_init_model      INFO: Initialize model ZC2
    ZC2.A05_A05.try_init_model      INFO: Initialize model ZC2
    setup_calib_unit exit as not enabled
    appending U4RecorderAnaMgr to AnaMgrList
     g4state_rerun_id -1 alldir ALL1 alldir0 ALL0 seldir SEL1 rerun 0
    [2023-03-26 22:42:22,916] p276744 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1675} INFO - PMTName PMTMask --pmt20inch-name 
    [2023-03-26 22:42:22,916] p276744 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1676} INFO - LPMTExtra TWO-mask --pmt20inch-extra 


::

    U4Recorder::EndOfEventAction@151:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2066:  dir /tmp/blyth/opticks/GEOM/ntds2/ALL/000
    SEvt::gatherHit@1795:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@679: 


But reldir seems to have been overridden or ignored as not logged above and no corresponding outputs::

    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/ntds2/
    total 0
    0 drwxr-xr-x. 3 blyth blyth 17 Mar 26 19:36 .
    0 drwxr-xr-x. 3 blyth blyth 19 Mar 26 19:36 ..
    0 drwxr-xr-x. 3 blyth blyth 17 Mar 26 19:36 ALL
    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/ntds2/ALL/
    total 4
    4 drwxr-xr-x. 2 blyth blyth 4096 Mar 26 20:59 000
    0 drwxr-xr-x. 3 blyth blyth   17 Mar 26 19:36 .
    0 drwxr-xr-x. 3 blyth blyth   17 Mar 26 19:36 ..
    N[blyth@localhost ~]$ l /tmp/blyth/opticks/GEOM/ntds2/ALL/000/
    total 58016
        4 -rw-rw-r--. 1 blyth blyth     2704 Mar 26 22:47 gs.npy
      156 -rw-rw-r--. 1 blyth blyth   157088 Mar 26 22:47 pho.npy
        4 -rw-rw-r--. 1 blyth blyth       21 Mar 26 22:47 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Mar 26 22:47 sframe.npy
      156 -rw-rw-r--. 1 blyth blyth   158944 Mar 26 22:47 pho0.npy




Add reldir debug::


    ZC2.A03_A03.try_init_model      INFO: Initialize model ZC2
    ZC2.A05_A05.try_init_model      INFO: Initialize model ZC2
    setup_calib_unit exit as not enabled
    appending U4RecorderAnaMgr to AnaMgrList
    SEvt::HighLevelCreate g4state_rerun_id -1 alldir ALL1 alldir0 ALL0 seldir SEL1 rerun 0
    SEvt::setReldir reldir ALL1
    [2023-03-26 23:27:12,182] p290986 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1675} INFO - PMTName PMTMask --pmt20inch-name 
    [2023-03-26 23:27:12,182] p290986 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1676} INFO - LPMTExtra TWO-mask --pmt20inch-extra 


More reldir debug shows there are at least 2 SEvt instance when one expected::

    ZC2.A03_A03.try_init_model      INFO: Initialize model ZC2
    ZC2.A05_A05.try_init_model      INFO: Initialize model ZC2
    setup_calib_unit exit as not enabled
    appending U4RecorderAnaMgr to AnaMgrList
    SEvt::HighLevelCreate g4state_rerun_id -1 alldir ALL1 alldir0 ALL0 seldir SEL1 rerun 0
    SEvt::setReldir reldir ALL1 this 0x0xb4fae0
    [2023-03-26 23:55:36,737] p317939 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1675} INFO - PMTName PMTMask --pmt20inch-name 
    [2023-03-26 23:55:36,737] p317939 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1676} INFO - LPMTExtra TWO-mask --pmt20inch-extra 




    SEvt::save@2017: SGeo::DefaultDir $DefaultOutputDir
    SEvt::save@2107:  dir /tmp/blyth/opticks/GEOM/ntds2/ALL/000
    SEvt::save@2108: SEvt::descOutputDir dir_ $DefaultOutputDir dir  /tmp/blyth/opticks/GEOM/ntds2/ALL/000 reldir ALL with_index Y index 0 this 0x0x74137a0

                  SCRIPT :                                                                                                ntds2
                  LAYOUT :                                                                                      POM 1 VERSION 1
                 VERSION :                                                                                                    1
             COMMANDLINE : gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 2 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-natural-geometry --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer gun
        ${GEOM}_GEOMList :                                                                                        GEOM_GEOMList
    SEvt::gatherHit@1821:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@681: 


Locate SEvt instanciations
----------------------------

::

    N[blyth@localhost opticks]$ BP=SEvt::SEvt ntds2


First is the expected U4Recorder one::

    Breakpoint 1, SEvt::SEvt (this=0xb50190) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:83
    83	    numphoton_genstep_max(0u)
    (gdb) bt
    #0  SEvt::SEvt (this=0xb50190) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:83
    #1  0x00007fffcf6758c6 in SEvt::Create () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:525
    #2  0x00007fffcf675b95 in SEvt::HighLevelCreate () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:573
    #3  0x00007fffd29be971 in U4Recorder::U4Recorder (this=0xb26f00) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:129
    #4  0x00007fffceb647f5 in U4RecorderAnaMgr::U4RecorderAnaMgr (this=0x932340, name=...)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:14
    #5  0x00007fffceb66625 in SniperCreateDLE_T<U4RecorderAnaMgr> (name=...) at /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/DeclareDLE.h:38
    #6  0x00007fffed6aa66c in DLEFactory::create(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) ()
       from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so

Second instance from LSExpDetectorConstruction_Opticks::Setup::

    START TO construct Calibration Units. 
    LSExpDetectorConstruction::setupOpticks completed construction of physiWorld  m_opticksMode 2 WITH_G4CXOPTICKS  proceeding to setup Opticks 
    LSExpDetectorConstruction::setupOpticks ekey LSExpDetectorConstruction__setupOpticks_pmtscan no pmtscan 
    LSExpDetectorConstruction_Opticks::Setup@25: [ WITH_G4CXOPTICKS opticksMode 2 sd 0x5bd1b30
    LSExpDetectorConstruction_Opticks::Setup@48:  opticksMode 2 : Ordinary Geant4 running but with some Opticks instrumentation for debugging 

    Breakpoint 1, SEvt::SEvt (this=0x7413b70) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:83
    83	    numphoton_genstep_max(0u)
    (gdb) bt
    #0  SEvt::SEvt (this=0x7413b70) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:83
    #1  0x00007fffcf6758c6 in SEvt::Create () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:525
    #2  0x00007fffcee67df4 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=2, world=0x59e4d50, sd=0x5bd1b30, ppd=0x921700, psd=0x924100, pmtscan=0x0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:49
    #3  0x00007fffcee4af04 in LSExpDetectorConstruction::setupOpticks (this=0x57fea00, world=0x59e4d50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:452
    #4  0x00007fffcee4a84c in LSExpDetectorConstruction::Construct (this=0x57fea00)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:373
    #5  0x00007fffdbf5ecbe in G4RunManager::InitializeGeometry() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #6  0x00007fffdbf5eb2c in G4RunManager::Initialize() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so

::

     16 void LSExpDetectorConstruction_Opticks::Setup(
     17           int opticksMode,
     18           const G4VPhysicalVolume* world,
     19           const G4VSensitiveDetector* sd,
     20           PMTParamData* ppd,
     21           PMTSimParamData* psd,
     22           NPFold* pmtscan
     23           )
     24 {
     25     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     26     if( opticksMode == 0 ) 
     27     { 
     28         LOG(info) << " opticksMode 0 : no setup needed " ; 
     29     }  
     30     else if( opticksMode == 1 || opticksMode == 3 )
     31     { 
     32         G4CXOpticks::SetGeometry(world) ; 
     33 
     34         _PMTParamData    _ppd(*ppd) ; 
     35         _PMTSimParamData _psd(*psd) ; 
     36 
     37         NPFold* j = new NPFold ; 
     38         j->add_subfold( "PMTParamData",    _ppd.serialize() );
     39         j->add_subfold( "PMTSimParamData", _psd.serialize() );
     40         if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     41 
     42         SSim::AddSubfold("juno", j );
     43 
     44         G4CXOpticks::SaveGeometry();
     45     }
     46     else if ( opticksMode == 2 )
     47     {
     48         LOG(info) << " opticksMode 2 : Ordinary Geant4 running but with some Opticks instrumentation for debugging " ;
     49         SEvt* evt = SEvt::Create();
     50         LOG_IF(fatal, evt == nullptr) << " FAILED TO SEvt::Create " ;
     51     }
     52     LOG(info) << "] WITH_G4CXOPTICKS " ;
     53 }
     54 #endif



TODO : POM=1 PMT=0/1 INSITU COMPARISON
-----------------------------------------




