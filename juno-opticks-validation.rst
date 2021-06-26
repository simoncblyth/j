juno-opticks-validation
=========================


update building a handful of pkgs will eventually fail
---------------------------------------------------------

At which point do a fuller build::

    je ; bash junoenv offline


P/O env : outdated path
-----------------------------

$JUNOTOP/bashrc.sh::

    O[blyth@localhost ~]$ cat $JUNOTOP/bashrc.sh
    export JUNOTOP=/home/blyth/junotop
    export CMTPROJECTPATH=/home/blyth/junotop:${CMTPROJECTPATH}
    source /home/blyth/junotop/ExternalLibs/Opticks/0.0.0-rc1/bashrc
    source /home/blyth/junotop/ExternalLibs/Python/2.7.17/bashrc
    source /home/blyth/junotop/ExternalLibs/Boost/1.72.0/bashrc



seem something similar before : trying to expand a non-existing event ?
--------------------------------------------------------------------------


Hmm, need to handle --nosave::

    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@213] ]BOpticksResource::Get
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@214] 
    # BOpticksKey::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.fe48b4d359786b95505117280fb5aac1

    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@217] GDMLAuxUserinfoGeospecificOptions [(null)]
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::EmbeddedCommandLine@133] Using ecl :[ --compute --embedded --xanalytic --production --nosave] OPTICKS_EMBEDDED_COMMANDLINE
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::EmbeddedCommandLine@134]  mode(Pro/Dev/Asis) P using "pro" (production) commandline without event saving 
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::EmbeddedCommandLine@139] Using extra1 argument :[--way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge]
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::EmbeddedCommandLine@149] Using eclx envvar :[--align] OPTICKS_EMBEDDED_COMMANDLINE_EXTRA
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@220] EmbeddedCommandLine : [ --compute --embedded --xanalytic --production --nosave  --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge --align]
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@222] [ok
    2021-06-09 03:58:34.472 INFO  [119517] [G4Opticks::InitOpticks@234] instanciate Opticks using embedded commandline only 
     --compute --embedded --xanalytic --production --nosave  --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge --align
    2021-06-09 03:58:34.474 INFO  [119517] [G4Opticks::InitOpticks@238] ]ok
    2021-06-09 03:58:34.474 INFO  [119517] [G4Opticks::InitOpticks@240] [ok.configure

    ...


    2021-06-09 04:00:29.862 INFO  [119517] [CManager::BeginOfEventAction@138]  not calling presave, creating OpticksEvent 
    2021-06-09 04:00:29.862 INFO  [119517] [CManager::BeginOfEventAction@144]  mocking BeginOfGenstep as have input photon primaries CEvent::DescPrimary numPrim 8 numberOfInputPhotons 8
     0 CPrimaryVertex::DescinputPhoton t0      0.100 pos [     -0.577    -0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577    -0.577    -0.577]  kEn 0.000 nm 440.000
     1 CPrimaryVertex::DescinputPhoton t0      0.200 pos [      0.577    -0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577    -0.577    -0.577]  kEn 0.000 nm 440.000
     2 CPrimaryVertex::DescinputPhoton t0      0.300 pos [     -0.577     0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577     0.577    -0.577]  kEn 0.000 nm 440.000
     3 CPrimaryVertex::DescinputPhoton t0      0.400 pos [      0.577     0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577     0.577    -0.577]  kEn 0.000 nm 440.000
     4 CPrimaryVertex::DescinputPhoton t0      0.500 pos [     -0.577    -0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577    -0.577     0.577]  kEn 0.000 nm 440.000
     5 CPrimaryVertex::DescinputPhoton t0      0.600 pos [      0.577    -0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577    -0.577     0.577]  kEn 0.000 nm 440.000
     6 CPrimaryVertex::DescinputPhoton t0      0.700 pos [     -0.577     0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577     0.577     0.577]  kEn 0.000 nm 440.000
     7 CPrimaryVertex::DescinputPhoton t0      0.800 pos [      0.577     0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577     0.577     0.577]  kEn 0.000 nm 440.000

    2021-06-09 04:00:29.862 INFO  [119517] [CManager::BeginOfGenstep@191]  gentype T num_photons 8
    2021-06-09 04:00:29.862 FATAL [119517] [CWriter::expand@125]  Cannot expand as CWriter::initEvent has not been called, check CManager logging 
    2021-06-09 04:00:29.862 INFO  [119517] [CWriter::BeginOfGenstep@151]  m_ctx._gentype [T] m_ctx._genstep_index 0 m_ctx._genstep_num_photons 8 m_ni 0
    Begin of Event --> 0
    2021-06-09 04:00:29.862 INFO  [119517] [G4OpticksRecorder::PreUserTrackingAction@122] 
    2021-06-09 04:00:30.099 INFO  [119517] [G4OpticksRecorder::UserSteppingAction@133] 
    python: /home/blyth/opticks/cfg4/CCtx.cc:100: unsigned int CCtx::step_limit() const: Assertion `_ok_event_init' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6







::

    2021-06-09 03:38:32.667 INFO  [86305] [CGenstepCollector::collectTorchGenstep@620]  torch_emitsource pass along  oac GS_EMITSOURCE  aux 0x2febfb0
    2021-06-09 03:38:32.667 INFO  [86305] [CManager::BeginOfEventAction@126]  m_mode 3
    2021-06-09 03:38:32.668 INFO  [86305] [CManager::BeginOfEventAction@135]  mocking BeginOfGenstep as have input photon primaries CEvent::DescPrimary numPrim 8 numberOfInputPhotons 8
     0 CPrimaryVertex::DescinputPhoton t0      0.100 pos [     -0.577    -0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577    -0.577    -0.577]  kEn 0.000 nm 440.000
     1 CPrimaryVertex::DescinputPhoton t0      0.200 pos [      0.577    -0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577    -0.577    -0.577]  kEn 0.000 nm 440.000
     2 CPrimaryVertex::DescinputPhoton t0      0.300 pos [     -0.577     0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577     0.577    -0.577]  kEn 0.000 nm 440.000
     3 CPrimaryVertex::DescinputPhoton t0      0.400 pos [      0.577     0.577    -0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577     0.577    -0.577]  kEn 0.000 nm 440.000
     4 CPrimaryVertex::DescinputPhoton t0      0.500 pos [     -0.577    -0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577    -0.577     0.577]  kEn 0.000 nm 440.000
     5 CPrimaryVertex::DescinputPhoton t0      0.600 pos [      0.577    -0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577    -0.577     0.577]  kEn 0.000 nm 440.000
     6 CPrimaryVertex::DescinputPhoton t0      0.700 pos [     -0.577     0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [     -0.577     0.577     0.577]  kEn 0.000 nm 440.000
     7 CPrimaryVertex::DescinputPhoton t0      0.800 pos [      0.577     0.577     0.577]  numberOfParticle  1 pdgCode   20022 dir [      0.577     0.577     0.577]  kEn 0.000 nm 440.000

    2021-06-09 03:38:32.668 INFO  [86305] [CManager::BeginOfGenstep@182]  gentype T num_photons 8

    Program received signal SIGSEGV, Segmentation fault.
    (gdb) bt
    #0  0x00007fffedbe0ff8 in std::vector<int, std::allocator<int> >::size() const () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #1  0x00007fffd5f9b962 in NPYBase::getNumItems (this=0x0, ifr=0, ito=1) at /home/blyth/opticks/npy/NPYBase.cpp:538
    #2  0x00007fffd600dfad in NPY<unsigned long long>::expand (this=0x0, extra_items=8) at /home/blyth/opticks/npy/NPY.cpp:492
    #3  0x00007fffcdcc62ac in CWriter::expand (this=0x14c231040, gs_photons=8) at /home/blyth/opticks/cfg4/CWriter.cc:117
    #4  0x00007fffcdcc6352 in CWriter::BeginOfGenstep (this=0x14c231040) at /home/blyth/opticks/cfg4/CWriter.cc:136
    #5  0x00007fffcdcbb573 in CRecorder::BeginOfGenstep (this=0x14c230ec0) at /home/blyth/opticks/cfg4/CRecorder.cc:169
    #6  0x00007fffcdce6cbf in CManager::BeginOfGenstep (this=0x14bd4c3c0, genstep_index=0, gentype=84 'T', num_photons=8, offset=0) at /home/blyth/opticks/cfg4/CManager.cc:187
    #7  0x00007fffcdce68ee in CManager::BeginOfEventAction (this=0x14bd4c3c0, event=0x2a73100) at /home/blyth/opticks/cfg4/CManager.cc:141
    #8  0x00007fffcdfaac26 in G4OpticksRecorder::BeginOfEventAction (this=0x252db30, event=0x2a73100) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:86
    #9  0x00007fffc05b5678 in G4OpticksAnaMgr::BeginOfEventAction (this=0x252da90, evt=0x2a73100) at ../src/G4OpticksAnaMgr.cc:31
    #10 0x00007fffc1d3e2c8 in MgrOfAnaElem::BeginOfEventAction (this=0x7fffc1f49440 <MgrOfAnaElem::instance()::s_mgr>, evt=0x2a73100) at ../src/MgrOfAnaElem.cc:46
    #11 0x00007fffc2584353 in LSExpEventAction::BeginOfEventAction (this=0x324b7b0, evt=0x2a73100) at ../src/LSExpEventAction.cc:66
    #12 0x00007fffd0621875 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #13 0x00007fffc27d6760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #14 0x00007fffc1d36a3c in DetSimAlg::execute (this=0x2515510) at ../src/DetSimAlg.cc:112
    #15 0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #16 0x00007fffef13d568 in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #17 0x00007fffef137f49 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so




"P" : OPTICKS_TOP defined and CMTEXTRATAGS=opticks
------------------------------------------------------


::

    epsilon:~ blyth$ t P
    P(){ TERM=${TERM}@tag:P,dbg:${DBG:-0} _P }

    epsilon:ana blyth$ t _P
    _P () 
    { 
        ssh P;
        [ $? -ne 0 ] && echo \"ssh P\" gives connection refused if ssh tunnel \"tun\" is not running
    }


::

    je
    bash junoenv offline
    bash junoenv opticks touchbuild


After updating the python::

   P[blyth@localhost offline]$ ( cd Examples/Tutorial/cmt ; make )


switching between CMTEXTRATAGS=opticks and not : doing a clean will often be needed when transitioning
---------------------------------------------------------------------------------------------------------

* otherwise compilation objects expecting or not expecting symbols will be surprised causing link failures 

::

    jo 
    cd Simulation/DetSimV2/AnalysisCode/cmt

    cmt config 
    cmt make clean 

    O[blyth@localhost cmt]$ cmt make clean 
    #CMT---> Info: Execute action make => gmake bin=../Linux-x86_64/ clean
    #CMT---> (constituents.make) Starting AnalysisCodeclean
    #CMT---> (constituents.make) Starting makeclean
    #CMT---> (constituents.make) makeclean done
    #CMT---> removing objects AnalysisCode
    #CMT---> removing library AnalysisCode
    #CMT---> (constituents.make) AnalysisCodeclean done
    #CMT---> AnalysisCodeclean
    #CMT---> allclean ok.
    #CMT---> removing ../Linux-x86_64/cmt_build_library_links.stamp
    O[blyth@localhost cmt]$ 


    O[blyth@localhost cmt]$ CMTEXTRATAGS=opticks cmt config
    O[blyth@localhost cmt]$ cmt make clean
    O[blyth@localhost cmt]$ cmt make

    CMTEXTRATAGS=opticks cmt show tags


Rebuilding with use of Opticks, with manual touch build::

    O[blyth@localhost cmt]$ touch ../src/G4OpticksAnaMgr.cc 

    CMTEXTRATAGS=opticks cmt config
    CMTEXTRATAGS=opticks cmt make 

    # simpler to just export CMTEXTRATAGS=opticks as it does not seem to get lodged into tags via config


Detecting whether the lib is using Opticks symbols and linking to Opticks libraries using "nm" and "ldd"::

    O[blyth@localhost cmt]$ nm ../Linux-x86_64/libAnalysisCode.so | c++filt | grep G4OpticksRecorder
                      U G4OpticksRecorder::G4OpticksRecorder()

    O[blyth@localhost cmt]$ ldd ../Linux-x86_64/libAnalysisCode.so | grep opticks
        libG4OK.so => /home/blyth/local/opticks/lib64/libG4OK.so (0x00007fe4b305a000)
        libOpticksCore.so => /home/blyth/local/opticks/lib64/libOpticksCore.so (0x00007fe4b1a57000)
        libNPY.so => /home/blyth/local/opticks/lib64/libNPY.so (0x00007fe4b1476000)
        libSysRap.so => /home/blyth/local/opticks/lib64/libSysRap.so (0x00007fe4b11cb000)
        libCFG4.so => /home/blyth/local/opticks/lib64/libCFG4.so (0x00007fe4af0c1000)
        libExtG4.so => /home/blyth/local/opticks/lib64/../lib64/libExtG4.so (0x00007fe4ab5c3000)
        libOKOP.so => /home/blyth/local/opticks/lib64/../lib64/libOKOP.so (0x00007fe4ab31b000)
        libOptiXRap.so => /home/blyth/local/opticks/lib64/../lib64/libOptiXRap.so (0x00007fe4aa8e3000)
        libOpticksGeo.so => /home/blyth/local/opticks/lib64/../lib64/libOpticksGeo.so (0x00007fe4aa6bb000)
        libGGeo.so => /home/blyth/local/opticks/lib64/../lib64/libGGeo.so (0x00007fe4aa26c000)
        libThrustRap.so => /home/blyth/local/opticks/lib64/../lib64/libThrustRap.so (0x00007fe4a9cc0000)
        libBoostRap.so => /home/blyth/local/opticks/lib64/../lib64/libBoostRap.so (0x00007fe4a98e2000)
        libCUDARap.so => /home/blyth/local/opticks/lib64/../lib64/libCUDARap.so (0x00007fe4a9183000)
        libOKConf.so => /home/blyth/local/opticks/lib64/../lib64/libOKConf.so (0x00007fe4a4849000)
        liboptix.so.6.5.0 => /home/blyth/local/opticks/lib64/../externals/OptiX/lib64/liboptix.so.6.5.0 (0x00007fe4a4558000)
        liboptixu.so.6.5.0 => /home/blyth/local/opticks/lib64/../externals/OptiX/lib64/liboptixu.so.6.5.0 (0x00007fe4a4192000)
        liboptix_prime.so.6.5.0 => /home/blyth/local/opticks/lib64/../externals/OptiX/lib64/liboptix_prime.so.6.5.0 (0x00007fe4a32ad000)
    O[blyth@localhost cmt]$ 





build tips
--------------

* connecting with "P" (rather than "O") has CMTEXTRATAGES=opticks set



::

    export CMTEXTRATAGS=opticks      ##  no need with "P"

    epsilon:offline blyth$ svn.py put | grep PhysiSim | sh 



    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/AnalysisCode/cmt    ## this was for dynamic_cast of TrackInfo in the InteresingAnaMgr before switched that off 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PhysiSim/cmt        ## added trackInfo to S + C 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PMTSim/cmt          ## Initialize invoke setInputPhotons,  EndOfEvent 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/DetSimOptions/cmt   ## setup geometry  

    CMTEXTRATAGS=opticks jok-touchbuild- Examples/Tutorial/cmt                   ## python machinery needs to be installed

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/GenTools/cmt                 ## GtOpticksTool for running with input photons




    BP=GenTools::execute tds3

    when adding " -g " under CMTEXTTRATAGS opticks need to remember to touch the class are interested in having symbols for


    BP=G4Track::SetUserInformation tds3



::

    O
    jre
    jok-g4o


    O[blyth@localhost cmt]$ ls -l /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks*
    lrwxrwxrwx. 1 blyth blyth 67 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so -> ../../../Simulation/DetSimV2/G4Opticks/Linux-x86_64/libG4Opticks.so
    -rw-rw-r--. 1 blyth blyth 87 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so.cmtref
    O[blyth@localhost cmt]$ date
    Fri May 21 21:23:38 CST 2021


tidy up : after moving the G4OpticksAnaMgr into AnalysisCode have 4 pkgs to remove
------------------------------------------------------------------------------------

::

    epsilon:DetSimV2 blyth$ l
    total 8
    0 drwxr-xr-x  11 blyth  staff  352 Jun  8 12:48 ..
    0 drwxr-xr-x   7 blyth  staff  224 Jun  8 12:48 TopTracker
    0 drwxr-xr-x   6 blyth  staff  192 Jun  8 12:48 AnalysisCode
    0 drwxr-xr-x  27 blyth  staff  864 Jun  8 12:48 .
    8 -rw-r--r--   1 blyth  staff  581 Jun  8 12:48 CMakeLists.txt
    0 drwxr-xr-x   6 blyth  staff  192 Jun  8 12:48 PMTSim
    0 drwxr-xr-x   7 blyth  staff  224 Jun  8 12:48 PhysiSim
    0 drwxr-xr-x   6 blyth  staff  192 Jun  8 12:48 VoxelMethod
    0 drwxr-xr-x   7 blyth  staff  224 Jun  8 12:48 GenSim
    0 drwxr-xr-x   7 blyth  staff  224 May 24 12:50 MCParamsSvc
    0 drwxr-xr-x   6 blyth  staff  192 May 24 12:50 OPSimulator
    0 drwxr-xr-x   5 blyth  staff  160 Jan 25 14:15 DetSimMTUtil
    0 drwxr-xr-x   7 blyth  staff  224 Jan 25 14:15 DetSimMT

    0 drwxr-xr-x   4 blyth  staff  128 May 24 12:06 G4Opticks     
    0 drwxr-xr-x   7 blyth  staff  224 May 20  2020 G4DAEChroma
    0 drwxr-xr-x   3 blyth  staff   96 May 20  2020 Opticks
    0 drwxr-xr-x   6 blyth  staff  192 May 20  2020 DAE

    0 drwxr-xr-x   8 blyth  staff  256 May 20  2020 MCGlobalTimeSvc
    0 drwxr-xr-x   7 blyth  staff  224 May 20  2020 CalibUnit
    0 drwxr-xr-x   7 blyth  staff  224 May 20  2020 DetSimAlg
    0 drwxr-xr-x   3 blyth  staff   96 May 20  2020 DetSimPolicy
    0 drwxr-xr-x   9 blyth  staff  288 May 20  2020 DetSimOptions
    0 drwxr-xr-x  19 blyth  staff  608 May 20  2020 OpticalProperty
    0 drwxr-xr-x   7 blyth  staff  224 May 20  2020 Chimney
    0 drwxr-xr-x   6 blyth  staff  192 May 20  2020 G4Svc
    0 drwxr-xr-x   6 blyth  staff  192 May 20  2020 SimUtil
    0 drwxr-xr-x   6 blyth  staff  192 May 20  2020 CentralDetector



DetSimV2/Opticks was an ancient hookup method
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    package Opticks

    macro Opticks_home "`opticks-config --prefix`"

    set OPTICKSDATAROOT "$(Opticks_home)/opticksdata"

    macro Opticks_cppflags " `opticks-config --cflags` "
    macro Opticks_linkopts " `opticks-config --libs` "



relocate G4OpticksAnaMgr into AnalysisCode : will get into standard list and simplify the python
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    epsilon:DetSimV2 blyth$ cp G4Opticks/src/G4OpticksAnaMgr.hh AnalysisCode/include/
    epsilon:DetSimV2 blyth$ cp G4Opticks/src/G4OpticksAnaMgr.cc AnalysisCode/src/


jcv JUNODetSimModule::

    1212     def init_opticks(self, task, args):
    1213         if args.opticks_anamgr:
    1214             import os   # why this needed ?
    1215             g4ok_root = os.environ.get("G4OPTICKSROOT",None)
    1216             if g4ok_root is None:
    1217                 msg = "--opticks-anamgr can only be used when non-standard G4Opticks package is built and setup, defining G4OPTICKSROOT "
    1218                 log.fatal(msg)
    1219                 assert 0, msg
    1220             else:
    1221                 log.info("[loadDll libG4Opticks.so --opticks-anamgr ")
    1222                 Sniper.loadDll("libG4Opticks.so")
    1223                 log.info("]loadDll libG4Opticks.so")
    1224             pass
    1225         else:
    1226             log.info(" not loading libG4Opticks.so as --opticks-anamgr not requested" )
    1227         pass





Sun Jun 5 2021 : metadata issue : getting zeros for g4evt 
------------------------------------------------------------

* maybe because CGenstepCollector gets reset before g4evt save is done, 
  presumably from okevt cleanup ?

* the collector is equally relevant to both g4evt and okevt : so should not reset it 
  under auspices of one or other event 

  * its not, G4Opticks::reset/G4Opticks::resetCollectors does the honours
  * the problem is that the SD EndOfEvent comes before the CManager::EndOfEvent
    so G4Opticks::reset is called too soon 


See::

    jcv junoSD_PMT_v2_Opticks

    // the SD::EndOfEvent comes before the CManager::EndOfEvent 
    // resulting in the reset happening before g4evt gets saved 
    // which messes with the metadata ?

    088 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent* /*HCE*/)
    089 {
    ...
    140     int merged_count(0);
    141     for(int idx=0 ; idx < int(num_hit) ; idx++)
    142     {
    143         g4ok->getHit(idx,&hit, hit_extra_ptr );
    144 
    145         collectHit(&hit, hit_extra_ptr, merged_count );
    146 
    147         if(idx < 20) dumpHit(idx, &hit, hit_extra_ptr );
    148     }
    149     g4ok->reset();
    150 
    151     LOG(info)
    152        << "]"
    153        << " num_hit " << num_hit
    154        << ( merged_count > 0 ? " MERGED " : "" )
    155        << " merged_count  " << merged_count
    156        << " m_merged_total " << m_merged_total
    157        << " m_opticksMode " << m_opticksMode
    158        ;




::

    15     gp.x 13469.46   gp.y 7262.24    gp.z -11872.47  gp.R 19368.07   pmt 14337   SI|SD|BT|EX          otk 5      oti17.49    bti 107.85   bp.x 12389.23   bp.y 6668.57    bp.z -10935.70  bp.R 17820.00  
    16     gp.x 4931.81    gp.y -12214.17  gp.z 14199.94   gp.R 19368.71   pmt 2146    SI|SD|BT|EC          otk 5      oti1.08     bti 92.61    bp.x 4546.33    bp.y -11250.32  bp.z 13050.43   bp.R 17820.00  
    17     gp.x 8418.11    gp.y 14242.98   gp.z -9853.94   gp.R 19256.87   pmt 13474   SI|RE|SC|SD|BT|EX    otk 5      oti8.30     bti 122.72   bp.x 5940.87    bp.y 13887.19   bp.z -9455.39   bp.R 17820.00  
    18     gp.x -12562.76  gp.y 12848.17   gp.z 7191.51    gp.R 19355.01   pmt 5406    SI|RE|SD|BT|EC       otk 5      oti9.26     bti 101.54   bp.x -11570.63  bp.y 11834.31   bp.z 6604.69    bp.R 17820.00  
    19     gp.x 3971.13    gp.y -7194.90   gp.z 17475.10   gp.R 19311.02   pmt 743     SI|SD|BT|EC          otk 5      oti7.04     bti 98.97    bp.x 3672.46    bp.y -6651.38   bp.z 16119.08   bp.R 17820.00  
    2021-06-06 22:57:51.279 FATAL [388229] [CGenstepCollector::reset@104]  num_gs 0
    2021-06-06 22:57:51.279 FATAL [388229] [G4Opticks::reset@536]  m_way_enabled reset m_hiys 
    2021-06-06 22:57:51.279 INFO  [388229] [junoSD_PMT_v2_Opticks::EndOfEvent@151] ] num_hit 3596 merged_count  0 m_merged_total 0 m_opticksMode 3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5073 hitCollection_muon 0 hitCollection_opticks 0
    2021-06-06 22:57:51.279 INFO  [388229] [CManager::EndOfEventAction@154]  m_mode 3
    2021-06-06 22:57:51.279 INFO  [388229] [CManager::EndOfEventAction@157]  _number_of_input_photons 0
    2021-06-06 22:57:51.280 INFO  [388229] [CManager::save@262]  m_mode 3
    2021-06-06 22:57:51.280 INFO  [388229] [CManager::save@266]  m_mode 3 numPhotons 0
    2021-06-06 22:57:51.280 INFO  [388229] [CManager::save@274]  --save g4evt numPhotons 0
    2021-06-06 22:57:51.280 INFO  [388229] [OpticksEvent::setNumPhotons@306] NOT RESIZING 0
    2021-06-06 22:57:51.280 INFO  [388229] [OpticksEvent::save@1869] /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1
    2021-06-06 22:57:51.280 INFO  [388229] [OpticksEvent::save@1874]  id: 0 typ: natural tag: -1 det: g4live cat: NULL udet: g4live num_photons: 0 num_source : 0  genstep NULL nopstep 0,4,4 photon 11278,4,4 debug 0,1,4 way 0,2,4 source NULL record 11278,10,2,4 phosel 0,1,4 recsel 0,10,1,4 sequence 11278,1,2 seed 0,1,1 hit 0,4,4 dir /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1
    2021-06-06 22:57:51.280 INFO  [388229] [OpticksEvent::saveHitData@1945]  num_hit 0 ht 0,4,4 tag -1
    2021-06-06 22:57:51.280 INFO  [388229] [OpticksEvent::saveHiyData@1976]  num_hiy 0 hy 0,2,4 tag -1
    2021-06-06 22:57:51.283 INFO  [388229] [OpticksEvent::saveIndex@2685] SKIP as not indexed 
    2021-06-06 22:57:51.288 INFO  [388229] [OpticksEvent::makeReport@2070] tagdir /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1
    2021-06-06 22:57:51.288 INFO  [388229] [OpticksEvent::saveReport@2188] [ /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1
    2021-06-06 22:57:51.289 INFO  [388229] [OpticksEvent::saveReport@2192] ] /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1
    2021-06-06 22:57:51.289 INFO  [388229] [OpticksEvent::saveReport@2188] [ /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1/20210606_225746
    2021-06-06 22:57:51.290 INFO  [388229] [OpticksEvent::saveReport@2192] ] /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-1/20210606_225746
    2021-06-06 22:57:51.290 INFO  [388229] [OpticksRun::resetEvent@239] [
    2021-06-06 22:57:51.290 INFO  [388229] [OpticksEvent::resetBuffers@1198] [



junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*)  is called from G4VSensitiveDetector::EndOfEvent::

    1027 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
    1028 {
    1029 
    1030 #ifdef WITH_G4OPTICKS
    1031     if(m_opticksMode > 0)
    1032     {
    1033         // Opticks GPU optical photon simulation and bulk hit population is done here 
    1034         m_jpmt_opticks->EndOfEvent(HCE);
    1035     }
    1036 #endif
    1037 
    1038     //if(m_debug) {
    1039     {



    087 void G4OpticksRecorder::EndOfEventAction(const G4Event* event)
     88 {
     89     LOG(LEVEL);
     90     m_manager->EndOfEventAction(event);
     91 
     92     // *G4Opticks::reset* needs to happen at end of event, but it should 
     93     // be done from user code at higher level as it dictates when things 
     94     // the user will need to access like hits
     95     // get reset
     96     //
     97     //   G4Opticks* g4ok = G4Opticks::Get(); 
     98     //   g4ok->reset();   
     99     //
    100 
    101 }


g4-cls G4EventManager::

    099 void G4EventManager::DoProcessing(G4Event* anEvent)
    100 {
    ...
    261 
    262   if(sdManager)
    263   { sdManager->TerminateCurrentEvent(currentEvent->GetHCofThisEvent()); }
    264 
    265   if(userEventAction) userEventAction->EndOfEventAction(currentEvent);
    266 
    267   stateManager->SetNewState(G4State_GeomClosed);
    268   currentEvent = nullptr;
    269   abortRequested = false;
    270 }
    271 

* SD always gets EndOfEvent before userEventAction


g4-cls G4SDManager::

    116 void G4SDManager::TerminateCurrentEvent(G4HCofThisEvent* HCE)
    117 {
    118   treeTop->Terminate(HCE);
    119 }
    120 

g4-cls G4SDStructure::

    204 void G4SDStructure::Terminate(G4HCofThisEvent*HCE)
    205 {
    206   // Broadcast to subdirectories.
    207   for(auto st : structure)
    208   { st->Terminate(HCE); }
    209   // Terminate all detectors in this directory.
    210   for(auto dt : detector)
    211   { if(dt->isActive()) dt->EndOfEvent(HCE); }
    212 }
    213 




Sun Jun 6 2021 : CRecorder/CWriter machinery starting to work in dynamic running (gensteps one-by-one) 
----------------------------------------------------------------------------------------------------------------

* issue with m_g4evt missing metadata still forces use of -C,--nocompare

::

    epsilon:j blyth$ ab.sh 1 -C

    In [1]: ab.a.seqhis_ana.table[:30]                                                                                                                                                                        
    Out[1]: 
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    0020           8cccc2        0.007          80        [6 ] SI BT BT BT BT SA
    0021          8ccc662        0.007          78        [7 ] SI SC SC BT BT BT SA
    0022         4cccccc2        0.006          72        [8 ] SI BT BT BT BT BT BT AB
    0023         7ccc6662        0.006          68        [8 ] SI SC SC SC BT BT BT SD
    0024          49cccc2        0.006          66        [7 ] SI BT BT BT BT DR AB
    0025          8ccc652        0.006          63        [7 ] SI RE SC BT BT BT SA
    0026          4ccccc2        0.005          62        [7 ] SI BT BT BT BT BT AB
    0027          7ccc562        0.005          61        [7 ] SI SC RE BT BT BT SD
    0028          7cccc62        0.005          59        [7 ] SI SC BT BT BT BT SD
    0029          8ccc552        0.005          57        [7 ] SI RE RE BT BT BT SA
    .                              11278         1.00 

    In [2]: ab.b.seqhis_ana.table[:30]                                                                                                                                                                        
    Out[2]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.148        1665        [2 ] SI AB
    0001           7cccc2        0.118        1336        [6 ] SI BT BT BT BT SD
    0002          7cccc62        0.053         599        [7 ] SI SC BT BT BT BT SD
    0003           8cccc2        0.052         583        [6 ] SI BT BT BT BT SA
    0004              452        0.047         534        [3 ] SI RE AB
    0005             8cc2        0.041         464        [4 ] SI BT BT SA
    0006          7cccc52        0.038         432        [7 ] SI RE BT BT BT BT SD
    0007              462        0.033         367        [3 ] SI SC AB
    0008          8cccc62        0.022         249        [7 ] SI SC BT BT BT BT SA
    0009         7cccc662        0.020         230        [8 ] SI SC SC BT BT BT BT SD
    0010            8cc62        0.016         186        [5 ] SI SC BT BT SA
    0011         7cccc652        0.015         172        [8 ] SI RE SC BT BT BT BT SD
    0012          8cccc52        0.015         168        [7 ] SI RE BT BT BT BT SA
    0013               41        0.013         144        [2 ] CK AB
    0014            8ccc2        0.013         143        [5 ] SI BT BT BT SA
    0015             4552        0.013         142        [4 ] SI RE RE AB
    0016            8cc52        0.012         138        [5 ] SI RE BT BT SA
    0017         7cccc552        0.012         138        [8 ] SI RE RE BT BT BT BT SD
    0018             4cc2        0.011         127        [4 ] SI BT BT AB
    0019             4662        0.011         121        [4 ] SI SC SC AB
    0020             4652        0.010         112        [4 ] SI RE SC AB
    0021         8cccc652        0.008          94        [8 ] SI RE SC BT BT BT BT SA
    0022         8cccc662        0.008          93        [8 ] SI SC SC BT BT BT BT SA
    0023        7cccc6662        0.007          79        [9 ] SI SC SC SC BT BT BT BT SD
    0024            4cc62        0.006          71        [5 ] SI SC BT BT AB
    0025           8cc662        0.006          64        [6 ] SI SC SC BT BT SA
    0026        7cccc6652        0.005          60        [9 ] SI RE SC SC BT BT BT BT SD
    0027           8cc652        0.005          56        [6 ] SI RE SC BT BT SA
    0028         8cccc552        0.005          54        [8 ] SI RE RE BT BT BT BT SA
    0029          7ccccc2        0.005          53        [7 ] SI BT BT BT BT BT SD
    .                              11278         1.00 

    In [3]:                                                                             




cleanup issue : this was a result of jackson-pollock-ing process memory due to bad record_id
--------------------------------------------------------------------------------------------------

* the problem moved around at every invokation 

::

    (gdb) 
    #0  0x00007fffeee342ad in ?? () from /lib64/libstdc++.so.6
    #1  0x00007fffeee96b63 in std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string() () from /lib64/libstdc++.so.6
    #2  0x00007fffd6069632 in NPYBase::~NPYBase (this=0x178bd0350, __in_chrg=<optimized out>) at /home/blyth/opticks/npy/NPYBase.cpp:479
    #3  0x00007fffd61108fe in NPY<unsigned long long>::~NPY (this=0x178bd0350, __in_chrg=<optimized out>) at /home/blyth/opticks/npy/NPY.hpp:100
    #4  0x00007fffd611092e in NPY<unsigned long long>::~NPY (this=0x178bd0350, __in_chrg=<optimized out>) at /home/blyth/opticks/npy/NPY.hpp:100
    #5  0x00007fffcdd977a2 in CWriter::clearOnestep (this=0x14bd47e40) at /home/blyth/opticks/cfg4/CWriter.cc:213
    #6  0x00007fffcdd9759a in CWriter::EndOfGenstep (this=0x14bd47e40) at /home/blyth/opticks/cfg4/CWriter.cc:200
    #7  0x00007fffcdd8bdb2 in CRecorder::EndOfGenstep (this=0x14bd47cd0) at /home/blyth/opticks/cfg4/CRecorder.cc:189
    #8  0x00007fffcddb67b0 in CManager::EndOfGenstep (this=0x14bd47b30) at /home/blyth/opticks/cfg4/CManager.cc:184
    #9  0x00007fffcddb658b in CManager::BeginOfGenstep (this=0x14bd47b30, gentype=83 'S', num_photons=34) at /home/blyth/opticks/cfg4/CManager.cc:156
    #10 0x00007fffce075d34 in G4OpticksRecorder::BeginOfGenstep (this=0x25314a0, gentype=83 'S', num_photons=34) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:72
    #11 0x00007fffce06d332 in G4Opticks::BeginOfGenstep (this=0x4cde850, gentype=83 'S', numPhotons=34) at /home/blyth/opticks/g4ok/G4Opticks.cc:1395
    #12 0x00007fffd09c1488 in DsG4Scintillation::PostStepDoIt (this=0x14d791890, aTrack=..., aStep=...) at ../src/DsG4Scintillation.cc:622
    #13 0x00007fffd04ac379 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so


getting worse : after trying to log in CTrackInfo dtor
---------------------------------------------------------

::

    2021-06-02 04:11:58.552 INFO  [267386] [G4OpticksRecorder::PostUserTrackingAction@114] 
    2021-06-02 04:11:58.552 INFO  [267386] [CManager::PostUserTrackingAction@287] 
    2021-06-02 04:11:58.552 INFO  [267386] [CRecorder::postTrack@215] 
    2021-06-02 04:11:58.552 INFO  [267386] [CRecorder::postTrackWriteSteps@462] [
    2021-06-02 04:11:58.552 INFO  [267386] [CRecorder::postTrackWriteSteps@470]  NOT USE_CUSTOM_BOUNDARY 
    2021-06-02 04:11:58.552 INFO  [267386] [CWriter::writeStepPoint_@313]  target_record_id 2
    2021-06-02 04:11:58.552 INFO  [267386] [CWriter::writeStepPoint_@313]  target_record_id 2
    2021-06-02 04:11:58.552 INFO  [267386] [CWriter::writePhoton@427]  target_record_id 2
    2021-06-02 04:11:58.552 INFO  [267386] [CRecorder::postTrackWriteSteps@673] ]

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffce8c3477 in G4Track::~G4Track() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4track.so


    (gdb) bt
    #0  0x00007fffce8c3477 in G4Track::~G4Track() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4track.so
    #1  0x00007fffd06ecd9d in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #2  0x00007fffc26ac760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #3  0x00007fffc1c0da3c in DetSimAlg::execute (this=0x250f920) at ../src/DetSimAlg.cc:112
    #4  0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #5  0x00007fffef13d568 in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #6  0x00007fffef137f49 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #7  0x00007fffef6c013e in _object* boost::python::detail::invoke<boost::python::to_python_value<bool const&>, bool (Task::*)(), boo


onestep crazy
---------------

::


    (gdb) bt
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd609a671 in NPY<short>::add (this=0x2a72df0, other=0x178bd1190) at /home/blyth/opticks/npy/NPY.cpp:450
    #5  0x00007fffcd4718e5 in CWriter::EndOfGenstep (this=0x14bd47e30) at /home/blyth/opticks/cfg4/CWriter.cc:188
    #6  0x00007fffcd4662fe in CRecorder::EndOfGenstep (this=0x14bd47cc0) at /home/blyth/opticks/cfg4/CRecorder.cc:189
    #7  0x00007fffcd4906a4 in CManager::EndOfGenstep (this=0x14bd47b30) at /home/blyth/opticks/cfg4/CManager.cc:183
    #8  0x00007fffcd49049c in CManager::BeginOfGenstep (this=0x14bd47b30, gentype=83 'S', num_photons=34) at /home/blyth/opticks/cfg4/CManager.cc:155
    #9  0x00007fffce075d34 in G4OpticksRecorder::BeginOfGenstep (this=0x2531050, gentype=83 'S', num_photons=34) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:72
    #10 0x00007fffce06d332 in G4Opticks::BeginOfGenstep (this=0x4cdeb10, gentype=83 'S', numPhotons=34) at /home/blyth/opticks/g4ok/G4Opticks.cc:1395
    #11 0x00007fffd09c12af in DsG4Scintillation::PostStepDoIt (this=0x14d791890, aTrack=..., aStep=...) at ../src/DsG4Scintillation.cc:614
    #12 0x00007fffd04ac379 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #13 0x00007fffd04ac7ff in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #14 0x00007fffd04a98a5 in G4SteppingManager::Stepping() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #15 0x00007fffd04b50fd in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #16 0x00007fffd06ecb53 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #17 0x00007fffc26ad760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so


    (gdb) p m_records_buffer->getShapeString(0)
    $4 = "2,10,2,4"
    (gdb) p m_onestep_records->getShapeString(0)
    $5 = "44951221,118554398,2142957450,67108865"
    (gdb) 




EndOfGenstep moved to BeginOfGenstep : hmm needs some detection that nothing to do for first call
----------------------------------------------------------------------------------------------------

::

    095     // *_genstep_index* 
     96     //     starts at -1 and is reset to -1 by CG4Ctx::setEvent, incremented by CG4Ctx::BeginOfGenstep 
     97     //     giving a zero based local index of genstep within the event
     98     // 
     99     int      _genstep_index ;
    100     




::

    (gdb) bt
    #0  0x00007fffedd83ff8 in std::vector<int, std::allocator<int> >::size() const () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #1  0x00007fffd6069752 in NPYBase::getNumItems (this=0x0, ifr=0, ito=1) at /home/blyth/opticks/npy/NPYBase.cpp:538
    #2  0x00007fffd609a4e9 in NPY<short>::add (this=0x2a72df0, other=0x0) at /home/blyth/opticks/npy/NPY.cpp:441
    #3  0x00007fffcd471858 in CWriter::EndOfGenstep (this=0x14bd47e30) at /home/blyth/opticks/cfg4/CWriter.cc:185
    #4  0x00007fffcd4662fe in CRecorder::EndOfGenstep (this=0x14bd47cc0) at /home/blyth/opticks/cfg4/CRecorder.cc:191
    #5  0x00007fffcd4905f8 in CManager::EndOfGenstep (this=0x14bd47b30) at /home/blyth/opticks/cfg4/CManager.cc:180
    #6  0x00007fffcd4903f0 in CManager::BeginOfGenstep (this=0x14bd47b30, gentype=83 'S', num_photons=2) at /home/blyth/opticks/cfg4/CManager.cc:153
    #7  0x00007fffce075d34 in G4OpticksRecorder::BeginOfGenstep (this=0x2531050, gentype=83 'S', num_photons=2) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:72
    #8  0x00007fffce06d332 in G4Opticks::BeginOfGenstep (this=0x4cdeb10, gentype=83 'S', numPhotons=2) at /home/blyth/opticks/g4ok/G4Opticks.cc:1395
    #9  0x00007fffd09c12af in DsG4Scintillation::PostStepDoIt (this=0x14d791890, aTrack=..., aStep=...) at ../src/DsG4Scintillation.cc:614
    #10 0x00007fffd04ac379 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #11 0x00007fffd04ac7ff in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so





CRecorder::postTrackWriteSteps finding null buffer
-------------------------------------------------------

* EndOfGenstep needs to be after all the corresponding postTrack of the genstep 
* hmm could do with a genstep index to ensure this 
* hmm "RE RE RE" secondaries can have secondaries recursively, 
  unclear how to signal completion of genstep track/step collection until start another genstep or end the event 
* lifecycle problem 

::

    (gdb) bt 
    #0  0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6cfaa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6cf21a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcd47292c in CWriter::writeStepPoint_ (this=0x14bd47e30, point=0x178bd1190, photon=...) at /home/blyth/opticks/cfg4/CWriter.cc:308
    #5  0x00007fffcd472795 in CWriter::writeStepPoint (this=0x14bd47e30, point=0x178bd1190, flag=2, material=1, last=false) at /home/blyth/opticks/cfg4/CWriter.cc:261
    #6  0x00007fffcd4693de in CRecorder::WriteStepPoint (this=0x14bd47cc0, point=0x178bd1190, flag=2, material=1, boundary_status=Undefined, last=false)
        at /home/blyth/opticks/cfg4/CRecorder.cc:702
    #7  0x00007fffcd468bf6 in CRecorder::postTrackWriteSteps (this=0x14bd47cc0) at /home/blyth/opticks/cfg4/CRecorder.cc:604
    #8  0x00007fffcd467178 in CRecorder::postTrack (this=0x14bd47cc0) at /home/blyth/opticks/cfg4/CRecorder.cc:220
    #9  0x00007fffcd491d64 in CManager::postTrack (this=0x14bd47b30) at /home/blyth/opticks/cfg4/CManager.cc:277
    #10 0x00007fffcd491cd8 in CManager::PostUserTrackingAction (this=0x14bd47b30, track=0x178bd1db0) at /home/blyth/opticks/cfg4/CManager.cc:259
    #11 0x00007fffce075da5 in G4OpticksRecorder::PostUserTrackingAction (this=0x2531050, track=0x178bd1db0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:107
    #12 0x00007fffc28b48de in G4OpticksAnaMgr::PostUserTrackingAction (this=0x250f3d0, trk=0x178bd1db0) at ../src/G4OpticksAnaMgr.cc:34
    #13 0x00007fffc1c17700 in MgrOfAnaElem::PostUserTrackingAction (this=0x7fffc1e22440 <MgrOfAnaElem::instance()::s_mgr>, trk=0x178bd1db0) at ../src/MgrOfAnaElem.cc:67
    #14 0x00007fffc2462964 in LSExpTrackingAction::PostUserTrackingAction (this=0x3247230, aTrack=0x178bd1db0) at ../src/LSExpTrackingAction.cc:48
    #15 0x00007fffd04b514d in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so



start genstep crash
-----------------------

Could be CWriter debug code checking prior target buffers, that are now stale.



jcv DsG4Scintillation::

     594 #ifdef WITH_G4OPTICKS
     595         unsigned opticks_photon_offset = G4Opticks::Get()->getNumPhotons();
     596         bool valid_opticks_genstep = Num > 0 && !flagReemission ;
     597         CTrackInfo* tkui = dynamic_cast<CTrackInfo*>(aTrack.GetUserInformation()) ;
     598 
     599         if(valid_opticks_genstep)
     600         {   
     601             if(m_opticksMode & 1)
     602             {   
     603                 G4Opticks::Get()->collectGenstep_DsG4Scintillation_r3971(
     604                     &aTrack,
     605                     &aStep,
     606                     Num,
     607                     scnt,
     608                     slowerRatio,
     609                     slowTimeConstant,
     610                     slowerTimeConstant,
     611                     ScintillationTime
     612                 );
     613             }  
     614             G4Opticks::Get()->BeginOfGenstep('S', Num );
     615         }





::


    Flag SCINTILLATION valid 1
    2021-06-01 18:18:18.617 INFO  [279883] [CWriter::initGenstep@144]  gentype [S] num_onestep_photons 2 m_target_records 0,10,2,4 m_target_photons 0,4,4 m_target_history 0,1,2
    2021-06-01 18:18:18.618 DEBUG [279883] [DsG4Scintillation::PostStepDoIt@797]  S:genloop  i 0 opticks_photon_offset 0 opticks_photon_id 0 Num 2
    2021-06-01 18:18:18.618 DEBUG [279883] [DsG4Scintillation::PostStepDoIt@797]  S:genloop  i 1 opticks_photon_offset 0 opticks_photon_id 0 Num 2
    2021-06-01 18:18:18.618 INFO  [279883] [CManager::EndOfGenstep@143]  gentype S num_photons 2
    2021-06-01 18:18:18.618 FATAL [279883] [CG4Ctx::setGenstepEnd@326] gentype [S] num_photons 2
    2021-06-01 18:18:18.618 INFO  [279883] [CWriter::writeGenstep@195]  gentype [S] num_onestep_photons 2
    2021-06-01 18:18:18.618 INFO  [279883] [CWriter::writeGenstep@200] bef.add ONESTEP(CPU style) m_history_buffer 0,1,2 m_photons_buffer 0,4,4 m_records_buffer 0,10,2,4
    2021-06-01 18:18:18.618 INFO  [279883] [CWriter::writeGenstep@208] aft.add ONESTEP(CPU style) m_history_buffer 2,1,2 m_photons_buffer 2,4,4 m_records_buffer 2,10,2,4
    2021-06-01 18:18:18.618 INFO  [279883] [G4Opticks::collectGenstep_DsG4Scintillation_r3971@1508]  numPhotons 1
    2021-06-01 18:18:18.618 INFO  [279883] [CManager::BeginOfGenstep@134]  gentype S num_photons 1
    2021-06-01 18:18:18.618 FATAL [279883] [CG4Ctx::setGenstep@318] gentype [S] num_photons 1
    2021-06-01 18:18:18.618 INFO  [279883] [CG4Ctx::setGen@381]  gen 2 OpticksGenstep::GenType G4Scintillation_1042 OpticksFlags::SourceType G4Scintillation_1042 OpticksFlags::Flag SCINTILLATION valid 1

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffd606b39e in NPYBase::getItemShape (this=0x178bd21a0, ifr=0) at /home/blyth/opticks/npy/NPYBase.cpp:1029
    1029	        ss << m_shape[i]  ;
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007fffd606b39e in NPYBase::getItemShape (this=0x178bd21a0, ifr=0) at /home/blyth/opticks/npy/NPYBase.cpp:1029
    #1  0x00007fffd606b32f in NPYBase::getShapeString (this=0x178bd21a0, ifr=0) at /home/blyth/opticks/npy/NPYBase.cpp:1021
    #2  0x00007fffcd470fea in CWriter::initGenstep (this=0x14bd48e30, gentype=83 'S', num_onestep_photons=1) at /home/blyth/opticks/cfg4/CWriter.cc:149
    #3  0x00007fffcd465ffe in CRecorder::BeginOfGenstep (this=0x14bd48cc0, gentype=83 'S', num_photons=1) at /home/blyth/opticks/cfg4/CRecorder.cc:169
    #4  0x00007fffcd49038e in CManager::BeginOfGenstep (this=0x14bd48b30, gentype=83 'S', num_photons=1) at /home/blyth/opticks/cfg4/CManager.cc:138
    #5  0x00007fffce075c79 in G4OpticksRecorder::BeginOfGenstep (this=0x2531050, gentype=83 'S', num_photons=1) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:71
    #6  0x00007fffce06d332 in G4Opticks::BeginOfGenstep (this=0x4cdeb10, gentype=83 'S', numPhotons=1) at /home/blyth/opticks/g4ok/G4Opticks.cc:1395
    #7  0x00007fffd09c130f in DsG4Scintillation::PostStepDoIt (this=0x14d792890, aTrack=..., aStep=...) at ../src/DsG4Scintillation.cc:614
    #8  0x00007fffd04ac379 in G4SteppingManager::InvokePSDIP(unsigned long) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #9  0x00007fffd04ac7ff in G4SteppingManager::InvokePostStepDoItProcs() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #10 0x00007fffd04a98a5 in G4SteppingManager::Stepping() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #11 0x00007fffd04b50fd in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #12 0x00007fffd06ecb53 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #13 0x00007fffc26ad760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #14 0x00007fffc1c0ea3c in DetSimAlg::execute (this=0x250f970) at ../src/DetSimAlg.cc:112


::

    (gdb) f 2
    #2  0x00007fffcd470fea in CWriter::initGenstep (this=0x14bd48e30, gentype=83 'S', num_onestep_photons=1) at /home/blyth/opticks/cfg4/CWriter.cc:149
    149	        << " m_target_history " << m_target_history->getShapeString()
    (gdb) p m_target_history
    $1 = (NPY<unsigned long long> *) 0x178bd21a0
    (gdb) p *m_target_history 


Crazy shape array, stale array pointer ?



null input photons crash easily fixed
--------------------------------------------

::

    (gdb) bt
    #0  0x00007fffedd83ff8 in std::vector<int, std::allocator<int> >::size() const () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #1  0x00007fffd6069752 in NPYBase::getNumItems (this=0x0, ifr=0, ito=1) at /home/blyth/opticks/npy/NPYBase.cpp:538
    #2  0x00007fffc966f412 in OpticksGenstep::MakeInputPhotonCarrier (ip=0x0, tagoffset=0) at /home/blyth/opticks/optickscore/OpticksGenstep.cc:379
    #3  0x00007fffce06f268 in G4Opticks::setInputPhotons (this=0x4cdeb10, input_photons=0x0) at /home/blyth/opticks/g4ok/G4Opticks.cc:1944
    #4  0x00007fffc215acb8 in junoSD_PMT_v2_Opticks::Initialize (this=0x34b03d0) at ../src/junoSD_PMT_v2_Opticks.cc:75
    #5  0x00007fffc2155c1d in junoSD_PMT_v2::Initialize (this=0x34b0430, HCE=0x2a6d600) at ../src/junoSD_PMT_v2.cc:188
    #6  0x00007fffcddd2a97 in G4SDStructure::Initialize(G4HCofThisEvent*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4digits_hits.so
    #7  0x00007fffcddd0f5b in G4SDManager::PrepareNewEvent() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4digits_hits.so
    #8  0x00007fffd06ec85c in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #9  0x00007fffc26ad760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #10 0x00007fffc1c0ea3c in DetSimAlg::execute (this=0x250f970) at ../src/DetSimAlg.cc:112
    #11 0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #12 0x00007fffef13d568 in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #13 0x00007fffef137f49 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so





TODO
------

* make the event output directory controllable by dedicated envvar, 
  tds3ip events clearly belong in a different tree

* see on 



Suspect OpticksRun::creatEvent without gensteps is a source of the sizing issue
----------------------------------------------------------------------------------

Now that have the carrier genstep, need to use that.  Will need to set ArrayContextIndex.::

    unsigned tagoffset = gensteps ? gensteps->getArrayContentIndex() : 0 ;  // eg eventID

Not so hasty, having the carrier genstep very early is only the case with input photons.
With ordinary S+C Geant4 need to be able to operate with CRecorder/CWriter 
dynamically growing the event genstep by genstep.

FOUND FIX : the cause what that OpticksRun::setGensteps lacked ctrl so it was diddling with m_g4evt
sizing which caused problem for dynamic CRecorder/CWriter genstep-by-genstep operation. Because the
g4evt was resized.::

    In [3]: bls                                                                                                                                                                                               
    Out[3]: 
    TO BT BT BT BT SA
    TO SC BT BT BT SA
    TO BT BT BT BT SD
    TO AB
    TO SC SC BT BT BT BT SD
    TO BT BT BT BT SA
    TO BT BT AB
    TO SC BT BT BR SA

    In [4]: als                                                                                                                                                                                               
    Out[4]: 
    TO BT BT BT SA
    TO BT BT BT SD
    TO BT BT BT SA
    TO BT BT BT SD
    TO BT BT BT SD
    TO BT BT BT SD
    TO BT BT BT SA
    TO AB



Perhaps need to G4Opticks::setInputPhotons earlier than from junoSD_PMT_v2_Opticks::EndOfEvent
-------------------------------------------------------------------------------------------------


::

    065 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent* /*HCE*/)
     66 {
     67     if(m_pmthitmerger_opticks == nullptr)
     68     {
     69         m_pmthitmerger_opticks = m_jpmt->getMergerOpticks();
     70     }
     71 
     72     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     73     G4int eventID = event->GetEventID() ;
     74 
     75     G4Opticks* g4ok = G4Opticks::Get() ;
     76 
     77     unsigned num_gensteps = g4ok->getNumGensteps();
     78     unsigned num_photons = g4ok->getNumPhotons();
     79 
     80     if(num_gensteps == 0 )
     81     {
     82         // hmm this grabbing from the input is kinda cheating, 
     83         // should really re-constitute from the G4Event  primaries
     84         // but input_photons.py is just for debugging, so I judge this
     85         // to be accepatble
     86         const GtOpticksTool* tool = GtOpticksTool::Get();
     87         NPY<float>* input_photons = tool ? tool->getInputPhotons() : nullptr ;
     88 
     89         LOG(info)
     90             << " no gensteps collected, looking for input photons "
     91             << " input_photons " << input_photons
     92             ;
     93 
     94         g4ok->setInputPhotons(input_photons);
     95     }
     96 
     97 
     98     LOG(info)
     99         << "["
    100         << " eventID " << eventID
    101         << " m_opticksMode " << m_opticksMode
    102         << " numGensteps " << num_gensteps
    103         << " numPhotons " << num_photons
    104         ;
    105 
    106     g4ok->propagateOpticalPhotons(eventID);




With G4+OK input photons and EVTMAX 1/2/5, getting 16 photon G4 evt (when expect 8 CubeCorners) and those beyond 8 are gibberish
-----------------------------------------------------------------------------------------------------------------------------------

* setting the carrier genstep causes OpticksEvent::resize up to 8
* subsequently that gets bumped to unwanted 16 via the add 

::


    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::setGensteps@308] gensteps 1,6,4
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGensteps@353]  m_gensteps 0x130f970a0 oac.desc gs0 : GS_EMITSOURCE  numSet:1 oac.numSet 1
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGensteps@361]  oac_label GS_EMBEDDED
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGenstepData@546] NOT adding oac_label GS_EMBEDDED as preexisting labels present: GS_EMITSOURCE  numSet:1
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGenstepData@559] Run evt Evt /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/2 20210531_233652 /home/blyth/junotop/ExternalLibs/Python/2.7.17/bin/python2.7 g4evt Evt /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-2 20210531_233652 /home/blyth/junotop/ExternalLibs/Python/2.7.17/bin/python2.7 shape 1,6,4 oac : GS_EMITSOURCE  numSet:1
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGenstepData@602]  Keys  OpticksGenstep_TORCH: 5 OpticksGenstep_G4Cerenkov_1042: 1 OpticksGenstep_G4Scintillation_1042: 2 OpticksGenstep_DsG4Cerenkov_r3971: 3 OpticksGenstep_DsG4Scintillation_r3971: 4 OpticksGenstep_G4GUN: 10
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::importGenstepData@612]  counts  [  label          7 num_photons          8 ]  [      total         8 ] 
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksEvent::setNumPhotons@301] RESIZING 8
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksEvent::resize@1293]  num_photons 8 num_records 80 maxrec 10 /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/-2
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksEvent::setNumPhotons@301] RESIZING 8
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksEvent::resize@1293]  num_photons 8 num_records 80 maxrec 10 /home/blyth/local/opticks/evtbase/source/evt/g4live/natural/2
    2021-05-31 23:36:52.844 INFO  [450884] [OpticksRun::setupSourceData@413] GS_EMITSOURCE emitsource 8,4,4




    2021-05-31 23:36:52.826 FATAL [450884] [G4Opticks::reset@531]  m_way_enabled reset m_hiys 
    2021-05-31 23:36:52.826 INFO  [450884] [junoSD_PMT_v2_Opticks::EndOfEvent@142] ] num_hit 4 merged_count  0 m_merged_total 0 m_opticksMode 3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5 hitCollection_muon 0 hitCollection_opticks 0
    2021-05-31 23:36:52.826 INFO  [450884] [CManager::EndOfEventAction@118] 
    2021-05-31 23:36:52.826 INFO  [450884] [CManager::EndOfEventAction@122]  mocking EndOfGenstep as have input photon primaries 
    2021-05-31 23:36:52.826 INFO  [450884] [CManager::EndOfGenstep@143]  gentype T num_photons 8
    2021-05-31 23:36:52.826 FATAL [450884] [CG4Ctx::setGenstepEnd@326] gentype [T] num_photons 8
    2021-05-31 23:36:52.826 INFO  [450884] [CWriter::writeGenstep@160]  gentype [T] num_onestep_photons 8
    2021-05-31 23:36:52.826 INFO  [450884] [CWriter::writeGenstep@163] bef.add ONESTEP(CPU style) m_history_buffer 8,1,2 m_photons_buffer 8,4,4 m_records_buffer 8,10,2,4
    ????  hmm: probably omitted to clear these buffers ???

    2021-05-31 23:36:52.826 INFO  [450884] [CWriter::writeGenstep@169] aft.add ONESTEP(CPU style) m_history_buffer 16,1,2 m_photons_buffer 16,4,4 m_records_buffer 16,10,2,4
    ?????

    2021-05-31 23:36:52.826 INFO  [450884] [CManager::save@217]  --save g4evt numPhotons 8
    2021-05-31 23:36:52.826 INFO  [450884] [OpticksEvent::setNumPhotons@306] NOT RESIZING 8





G4Opticks::setInputPhotons the carrier gensteps are getting mis-labeled as GS_EMBEDDED causing allowed gencodes fail
-----------------------------------------------------------------------------------------------------------------------

* fixed this by not-resetting labels when already present 

::

    (gdb) bt
    #3  0x00007fffe6936252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffeef4f132 in G4StepNPY::checkGencodes (this=0x23b86c40) at /home/blyth/opticks/npy/G4StepNPY.cpp:322
    #5  0x00007fffef3ab3d1 in OpticksRun::importGenstepData (this=0x708ab0, gs=0x8e0e580, oac_label=0x7fffef427142 "GS_EMBEDDED") at /home/blyth/opticks/optickscore/OpticksRun.cc:569
    #6  0x00007fffef3aa3e9 in OpticksRun::importGensteps (this=0x708ab0) at /home/blyth/opticks/optickscore/OpticksRun.cc:353
    #7  0x00007fffef3aa20a in OpticksRun::setGensteps (this=0x708ab0, gensteps=0x8e0e580) at /home/blyth/opticks/optickscore/OpticksRun.cc:312
    #8  0x00007fffef3a9238 in OpticksRun::createEvent (this=0x708ab0, gensteps=0x8e0e580, ctrl=43 '+') at /home/blyth/opticks/optickscore/OpticksRun.cc:93
    #9  0x00007ffff06b9f58 in OpMgr::propagate (this=0x8e10230) at /home/blyth/opticks/okop/OpMgr.cc:135
    #10 0x00007ffff7bc2009 in G4Opticks::propagateOpticalPhotons (this=0x6e1350, eventID=0) at /home/blyth/opticks/g4ok/G4Opticks.cc:1154
    #11 0x0000000000405516 in G4OKTest::propagate (this=0x7fffffff8aa0, eventID=0) at /home/blyth/opticks/g4ok/tests/G4OKTest.cc:375
    #12 0x000000000040622b in main (argc=1, argv=0x7fffffff8db8) at /home/blyth/opticks/g4ok/tests/G4OKTest.cc:508
    (gdb) 





Changing NoRINDEX to yield SA (instead of NA) avoids the zeroing
---------------------------------------------------------------------

::

    epsilon:j blyth$ ab.sh 1 --nocompare


    In [1]: b.seqhis_ana.table                                                                                                                                                                          
    Out[1]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                                  8         1.00 
    0000           8ccccd        0.250           2        [6 ] TO BT BT BT BT SA
    0001         7cccc66d        0.125           1        [8 ] TO SC SC BT BT BT BT SD
    0002           8ccc6d        0.125           1        [6 ] TO SC BT BT BT SA
    0003           8bcc6d        0.125           1        [6 ] TO SC BT BT BR SA
    0004           7ccccd        0.125           1        [6 ] TO BT BT BT BT SD
    0005             4ccd        0.125           1        [4 ] TO BT BT AB
    0006               4d        0.125           1        [2 ] TO AB
    .                                  8         1.00 

    In [2]: b.rpostr()                                                                                                                                                                                  
    Out[2]: 
    A([[    0.    , 17700.5687, 17821.0886, 19343.4453, 19343.4453, 19349.7885,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   891.213 , 17699.9078, 17820.2621, 17869.0345, 20049.994 ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19273.6706, 19273.6706, 19276.8422,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   542.3396,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 10681.8698, 10931.8877, 17700.8247, 17819.5562, 19320.488 , 19320.488 , 19325.6158,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19295.8717, 19295.8717, 19302.2148,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 18055.7852,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  5515.3716, 17699.9085, 17819.9794, 19385.9602, 20050.2072,     0.    ,     0.    ,     0.    ,     0.    ]])

    In [3]: bls                                                                                                                                                                                         
    Out[3]: 
    TO BT BT BT BT SA
    TO SC BT BT BT SA
    TO BT BT BT BT SD
    TO AB
    TO SC SC BT BT BT BT SD
    TO BT BT BT BT SA
    TO BT BT AB
    TO SC BT BT BR SA

        
::

    epsilon:j blyth$ ab.sh 2 --nocompare

    In [1]: bls                                                                                                                                                                                         
    Out[1]: 
    TO AB
    TO SC BT BT BT SA
    TO SC AB
    TO RE RE RE SC BT BT SC BT BT
    TO RE RE SC SC SC BT BT BT BT
    TO BT BT BT BT SD
    TO BT BT BT BT SA
    TO SC SC AB

    In [2]: b.rpostr()                                                                                                                                                                                  
    Out[2]: 
    A([[    0.    ,  2892.4778,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  4215.0252, 17700.5793, 17819.7398, 17854.2641, 20050.2638,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 15175.9937, 14426.6828,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  2451.6287,  2401.0524,  2293.4526,  2117.6657, 17700.0623, 17819.3464, 18256.8615, 17820.29  , 17700.5538],
       [    0.    , 12048.8193, 11961.9554,  9429.9378, 16127.7335, 16686.6426, 17700.8922, 17819.2802, 19326.6594, 19326.6594],
       [    0.    , 17700.5687, 17821.0886, 19295.8717, 19295.8717, 19302.2148,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19292.7001, 19292.7001, 19296.9289,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   862.6688,  5856.1724, 14363.5445,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ]])

    In [3]:                    





20m : why does reaching the tyvek cause photon history seqhis/seqmat to get zeroed ?
---------------------------------------------------------------------------------------

* probably meeting Tyvek:NoRINDEX needs to be handled with SA rather than NA
* hmm is it a surface ? What is RELECTIVITY of the Tyvek ?


jcv LSExpDetectorConstruction_Opticks::

     17 #ifdef WITH_G4OPTICKS
     18 /**
     19 LSExpDetectorConstruction_Opticks::Setup
     20 ------------------------------------------
     21 
     22 1. pass geometry to Opticks, translate it to GPU and return sensor placements 
     23 2. use the placements to pass sensor data : efficiencies, categories, identifiers
     24 3. pass theta dependent efficiency tables for all sensor categories
     25 
     26 
     27 
     28 
     29                              |--------- 2230 ----------------|-- 120--|
     30                              20050                           17820    17700
     31                           / /                               /         /
     32                          / /                               /         /
     33                         / pInnerWater                     /         /
     34                        / /                               /         /
     35                       / /                  (0)          /         /
     36                      pTyvek                  \         pAcrylic  /
     37                     / /                       \       /         /
     38                    / /                         \     /         pTarget:LS
     39                   / /                           \   /         /
     40                  / /                             \ /         /
     41                 / /                              (1)        /
     42                / /                               / \       /
     43               / /                               /   \     /
     44              / /                               /     \   /         
     45             / /                               /       \ /
     46            / /                          Wa   /  Ac    (2)             
     47           / /                               /         / \
     48          / /                               /         /   \
     49         / /                               /         /     \        LS    
     50 



2: ditto : genstep chunking giving correct number of photons but getting bad flag ?0?
----------------------------------------------------------------------------------------


::

    bls[:10]
    TO AB
    ?0?              ## zeroed history photon is again the one that has got to radius > 20m
    TO SC AB
    TO RE RE RE SC BT BT SC BT BT
    TO RE RE SC SC SC BT BT BT BT
    TO BT BT BT BT SD
    TO BT BT BT BT SA
    TO SC SC AB

    In [1]: b.rpostr()                                                                                                                                                                                  
    Out[1]: 
    A([[    0.    ,  2892.4778,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  4215.0252, 17700.5793, 17819.7398, 17854.2641, **20050.2638**,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 15175.9937, 14426.6828,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  2451.6287,  2401.0524,  2293.4526,  2117.6657, 17700.0623, 17819.3464, 18256.8615, 17820.29  , 17700.5538],
       [    0.    , 12048.8193, 11961.9554,  9429.9378, 16127.7335, 16686.6426, 17700.8922, 17819.2802, 19326.6594, 19326.6594],
       [    0.    , 17700.5687, 17821.0886, 19295.8717, 19295.8717, 19302.2148,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19292.7001, 19292.7001, 19296.9289,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   862.6688,  5856.1724, 14363.5445,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ]])

    In [2]:                                

    In [1]: b.rpostt()                                                                                                                                                                                  
    Out[1]: 
    A([[  0.1099,  14.9052,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ],
       [  0.1831,  21.7902, 117.6672, 118.3264, 118.5095, 128.8003,   0.    ,   0.    ,   0.    ,   0.    ],
       [  0.293 ,  78.0053,  98.9166,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ],
       [  0.4028,  15.7109,  19.7394,  23.6213,  27.8329, 116.3488, 117.008 , 119.0222, 121.659 , 122.4281],
       [  0.5127,  62.5141,  64.5283,  92.288 , 165.0929, 205.8168, 211.6031, 212.2623, 220.0629, 220.0629],
       [  0.586 ,  91.2626,  91.8851,  98.6969,  98.6969,  98.6969,   0.    ,   0.    ,   0.    ,   0.    ],
       [  0.6958,  91.3724,  91.9584,  98.7701,  98.7701,  98.7701,   0.    ,   0.    ,   0.    ,   0.    ],
       [  0.8057,   5.2004,  31.3852,  76.101 ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ,   0.    ]])





    In [2]: x = np.array([  7379.3756,  17911.9236,  -5169.2251])   

    In [5]: np.sqrt(np.sum(x*x))                                                                                                                                                                        
    Out[5]: 20050.26382451319




::

    In [2]: b.seqhis_ana.table                                                                                                                                                                          
    Out[2]: 
    all_seqhis_ana
    .                     cfo:-  -2:g4live:source 
    .                                  8         1.00 
    0000       cccc66655d        0.125           1        [10] TO RE RE SC SC SC BT BT BT BT
    0001       cc6cc6555d        0.125           1        [10] TO RE RE RE SC BT BT SC BT BT
    0002           8ccccd        0.125           1        [6 ] TO BT BT BT BT SA
    0003           7ccccd        0.125           1        [6 ] TO BT BT BT BT SD
    0004             466d        0.125           1        [4 ] TO SC SC AB
    0005              46d        0.125           1        [3 ] TO SC AB
    0006               4d        0.125           1        [2 ] TO AB
    0007                0        0.125           1        [1 ] ?0?
    .                                  8         1.00 

    In [3]: bls                                                                                                                                                                                         
    Out[3]: 
    TO AB
    ?0?                   record_id:1
    TO SC AB
    TO RE RE RE SC BT BT SC BT BT
    TO RE RE SC SC SC BT BT BT BT
    TO BT BT BT BT SD
    TO BT BT BT BT SA
    TO SC SC AB


    In [8]: b.rpost_(slice(0,10))                                                                                                                                                                       
    Out[8]: 
    A([[[     0.    ,      0.    ,      0.    ,      0.1099],
        [ -1669.9728,  -1669.9728,  -1669.9728,     14.9052],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]],


       BELOW IS THE  ?0? : WHICH IS ODD AS IT APPEARS TO HAVE A FULL HISTORY 

       [[     0.    ,      0.    ,      0.    ,      0.1831],
        [  2433.5459,  -2433.5459,  -2433.5459,     21.7902],
        [  6817.2246,  15617.542 ,  -4788.3541,    117.6672],
        [  6846.5224,  15734.7331,  -4804.8341,    118.3264],
        [  6853.8469,  15769.5242,  -4808.4964,    118.5095],
        [  7379.3756,  17911.9236,  -5169.2251,    128.8003],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]],

       [[     0.    ,      0.    ,      0.    ,      0.293 ],
        [ -8761.8641,   8761.8641,  -8761.8641,     78.0053],
        [-11133.1523,   6958.2202,  -5980.4071,     98.9166],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]],

       [[     0.    ,      0.    ,      0.    ,      0.4028],
        [  1415.4485,   1415.4485,  -1415.4485,     15.7109],
        [  1386.1507,   1366.0085,  -1406.2929,     19.7394],
        [  1342.204 ,   1223.1819,  -1400.7996,     23.6213],
        [   921.0486,    650.0443,  -1792.6572,     27.8329],
        [  6786.0958, -14192.938 ,  -8111.8198,    116.3488],
        [  6826.3802, -14297.3113,  -8155.7665,    117.008 ],
        [  6974.7002, -14681.8445,  -8313.242 ,    119.0222],
        [  7102.8779, -14313.7913,  -7888.4243,    121.659 ],
        [  7124.8512, -14213.0802,  -7780.3888,    122.4281]],

       [[     0.    ,      0.    ,      0.    ,      0.5127],
        [ -6956.389 ,  -6956.389 ,   6956.389 ,     62.5141],
        [ -6998.5046,  -6795.2513,   6923.4291,     64.5283],
        [ -3193.4568,  -8229.0109,   3317.9724,     92.288 ],
        [  -924.7108,  -2058.1683,  15969.1153,    165.0929],
        [   -42.1155,   5852.2294,  15626.6976,    205.8168],
        [    34.7911,   5725.8827,  16749.1684,    211.6031],
        [    43.9467,   5711.2339,  16879.1772,    212.2623],
        [   168.4622,   5436.5673,  18545.4878,    220.0629],
        [   168.4622,   5436.5673,  18545.4878,    220.0629]],

       [[     0.    ,      0.    ,      0.    ,      0.586 ],
        [ 10219.4281, -10219.4281,  10219.4281,     91.2626],
        [ 10289.0103, -10289.0103,  10289.0103,     91.8851],
        [ 11140.4767, -11140.4767,  11140.4767,     98.6969],
        [ 11140.4767, -11140.4767,  11140.4767,     98.6969],
        [ 11144.1389, -11144.1389,  11144.1389,     98.6969],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]],

       [[     0.    ,      0.    ,      0.    ,      0.6958],
        [-10219.4281,  10219.4281,  10219.4281,     91.3724],
        [-10289.0103,  10289.0103,  10289.0103,     91.9584],
        [-11138.6456,  11138.6456,  11138.6456,     98.7701],
        [-11138.6456,  11138.6456,  11138.6456,     98.7701],
        [-11142.3078,  11140.4767,  11140.4767,     98.7701],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]],

       [[     0.    ,      0.    ,      0.    ,      0.8057],
        [   498.0621,    498.0621,    498.0621,      5.2004],
        [  2970.0613,   1100.4975,   4925.6874,     31.3852],
        [  8088.0154,   5290.0784,  10625.9346,     76.101 ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ],
        [     0.    ,      0.    ,      0.    ,      0.    ]]])





1: genstep chunking giving correct number of photons but getting bad flag ?0?
--------------------------------------------------------------------------------

Bad photons have reached further, out to radius >20m::

    bls[:10]
    TO BT BT BT BT SA
    ?0?
    TO BT BT BT BT SD
    TO AB
    TO SC SC BT BT BT BT SD
    TO BT BT BT BT SA
    TO BT BT AB
    ?0?

    In [1]: b.rpostr()                                                                                                                                                                                  
    Out[1]: 
    A([[    0.    , 17700.5687, 17821.0886, 19343.4453, 19343.4453, 19349.7885,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   891.213 , 17699.9078, 17820.2621, 17869.0345, **20049.994** ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19273.6706, 19273.6706, 19276.8422,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,   542.3396,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 10681.8698, 10931.8877, 17700.8247, 17819.5562, 19320.488 , 19320.488 , 19325.6158,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 19295.8717, 19295.8717, 19302.2148,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    , 17700.5687, 17821.0886, 18055.7852,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ,     0.    ],
       [    0.    ,  5515.3716, 17699.9085, 17819.9794, 19385.9602, **20050.2072**,     0.    ,     0.    ,     0.    ,     0.    ]])

    In [2]:                                      



::

    ab.sh 1 --nocompare

    In [2]: bls                                                                                                                                                                                         
    Out[2]: 
    TO BT BT BT BT SA
    ?0?                        record_id:1
    TO BT BT BT BT SD
    TO AB
    TO SC SC BT BT BT BT SD
    TO BT BT BT BT SA
    TO BT BT AB
    ?0?                        record_id:7

    In [3]: b.seqhis_ana.table                                                                                                                                                                          
    Out[3]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                                  8         1.00 
    0000           8ccccd        0.250           2        [6 ] TO BT BT BT BT SA
    0001                0        0.250           2        [1 ] ?0?
    0002         7cccc66d        0.125           1        [8 ] TO SC SC BT BT BT BT SD
    0003           7ccccd        0.125           1        [6 ] TO BT BT BT BT SD
    0004             4ccd        0.125           1        [4 ] TO BT BT AB
    0005               4d        0.125           1        [2 ] TO AB
    .                                  8         1.00 



When checking with logging, must look for the record_id to match with the order of the output arrays, 
as processing order and output order are not the same.

record_id:1 ends with NoRINDEX::

    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setTrack@422]  _track_id 1 track.GetGlobalTime 0.2 _parent_id -1 _pdg_encoding 20022 _optical 1 _process_manager CProMgr n:[5] (0) name Transportation left -1 (1) name Scintillation left -1 (2) name OpAbsorption left -1 (3) name OpRayleigh left -1 (4) name OpBoundary left -1
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setTrackOptical@495]  _record_id 1 _primary_id 1 _reemtrack 0 tkui_gentype T _track.GetGlobalTime 0.2
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setGen@380]  gen 6 OpticksGenstep::GenType fabricated OpticksFlags::SourceType fabricated OpticksFlags::Flag TORCH valid 1
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                           Detection _boundary_status                       NotAtBoundary
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                       NotAtBoundary _boundary_status                   FresnelRefraction
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                   FresnelRefraction _boundary_status                        SameMaterial
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                        SameMaterial _boundary_status                   FresnelRefraction
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.248 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                   FresnelRefraction _boundary_status                            NoRINDEX
    2021-05-30 21:53:38.248 INFO  [446990] [CManager::PostUserTrackingAction@243] 


record_id:7 ends with NoRINDEX::

    2021-05-30 21:53:38.243 INFO  [446990] [CG4Ctx::setTrack@422]  _track_id 7 track.GetGlobalTime 0.8 _parent_id -1 _pdg_encoding 20022 _optical 1 _process_manager CProMgr n:[5] (0) name Transportation left -1 (1) name Scintillation left -1 (2) name OpAbsorption left -1 (3) name OpRayleigh left -1 (4) name OpBoundary left -1
    2021-05-30 21:53:38.243 INFO  [446990] [CG4Ctx::setTrackOptical@495]  _record_id 7 _primary_id 7 _reemtrack 0 tkui_gentype T _track.GetGlobalTime 0.8
    2021-05-30 21:53:38.243 INFO  [446990] [CG4Ctx::setGen@380]  gen 6 OpticksGenstep::GenType fabricated OpticksFlags::SourceType fabricated OpticksFlags::Flag TORCH valid 1
    2021-05-30 21:53:38.243 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.243 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                           Undefined _boundary_status                       NotAtBoundary
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.244 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                       NotAtBoundary _boundary_status                   FresnelRefraction
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.244 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                   FresnelRefraction _boundary_status                   FresnelRefraction
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.244 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                   FresnelRefraction _boundary_status                   FresnelReflection
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.244 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                   FresnelReflection _boundary_status                        StepTooSmall
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::UserSteppingAction@345] 
    2021-05-30 21:53:38.244 INFO  [446990] [CG4Ctx::setStepOptical@597]  _prior_boundary_status                        StepTooSmall _boundary_status                            NoRINDEX
    2021-05-30 21:53:38.244 INFO  [446990] [CManager::PostUserTrackingAction@243] 


Q: what does one bad flag trash the whole history : seqhis and seqmat  ?

::

    In [10]: b.seqmat                                                                                                                                                                                   
    Out[10]: A([  14610353,          0,   14610353,         17, 3740250385,   14610353,      65457,          0], dtype=uint64)

    In [11]: b.seqhis                                                                                                                                                                                   
    Out[11]: A([   9227469,          0,    8178893,         77, 2093794925,    9227469,      19661,          0], dtype=uint64)




shakedown genstep chunking : onestep CRecorder/CWriter mode
--------------------------------------------------------------

::

    (gdb) p m_onestep_records->getShapeString(0)
    $2 = "8,10,2,4"
    (gdb) p m_records_buffer->getShapeString(0)
    $3 = "44516112,0,305,0,44514000,0,-150427432,32767,44513948,0,44513948,0,8,0,7,0,44513992,0,31102976,0,0,0,0,1,2,0,0,3,44514656,0,44514576,0,44508368,0,-1,-1,4132,0,44515344,0,-1,0,0,0,0,0,16777216,0,0,0,44"...
    (gdb) 




thoughts on input_photon testing using GtOpticksTool 
--------------------------------------------------------

Excellent debugging tool to be able to craft primary photons with ana/input_photons.py 
and hence know exactly what should be recorded.  

But the input opticals mean are using primary optical photons which are very 
different from standard primaries. So it would be easy to setup a CRecorder 
approach that works with this situation but not the real one.   

There is no C+S process involved generating the opticals, only S is 
relevant for the reemission handling. 

Even if you could implement input gensteps within Geant4 the same 
problem of unnatural primaries would presumably happen, but this 
is irrelevant anyhow as input gensteps would require hacking much more
of Geant4 than is acceptable (ie more than just C+S proc).  

Hence proceed with input photons but stay mindful of its 
artifical nature and avoid doing things that will break generality.  


thoughts on CRecorder static/dynamic modes : PLAN: adopt genstep-level-chunking using CG4Ctx::setGenstep
-----------------------------------------------------------------------------------------------------------------------

static(event-level-chunking) 
   used when have all the gensteps up front, so can allocate total photons 
   all at once

dynamic(photon-level-chunking)
   attempt at operating in a gather photons one by one manner, BUT this 
   is very fragile to keep working, possibly from G4Track order variation 

genstep-level-chunking 
   idea for a new way mode of CRecorder operation that can be used 
   without having all gensteps up front, all that need is to know the basics
   of the genstep : num_photons, genstep_offset

   * CG4Ctx::setGenstep(numPhotons, offset)

   * can fabricate setGenstep call for input_photons running  (which have no C+S)
     by detection of the primary opticals in CG4Ctx::setEvent 

   * so can allocate and collect all photons on a genstep
   * advantage with this mode is that can use it both in live running 
     and when operating from canned gensteps : so this mode can replace 
     both the above and be less fragile wrt the details of the G4 track ordering etc..



1 : miss 2 at recording stage
------------------------------------------

Observations:

* order is inverted compared to input photons
* 0.2 and 0.8 are missing 
* clear smoking gun for CRecorder messing up, should have 8 photons here 


::

    epsilon:opticks blyth$ ab.sh 1 --nocompare

    In [5]: b.rpost_(slice(0,1))                                                                                                                                                                        
    Out[5]: 
    A([[[0.    , 0.    , 0.    , 0.6958]],

       [[0.    , 0.    , 0.    , 0.586 ]],

       [[0.    , 0.    , 0.    , 0.5127]],

       [[0.    , 0.    , 0.    , 0.4028]],

       [[0.    , 0.    , 0.    , 0.293 ]],

       [[0.    , 0.    , 0.    , 0.1099]]])

    In [6]:                                                 




2 : several extras 
-------------------------

* evt 2 has same input photons at evt 1, but different random stream 
* again clear smoking gun for CRecorder messing up, should have 8 photons here 

::

    epsilon:opticks blyth$ ab.sh 2 --nocompare


    In [3]: bls[:100]                                                                                                                                                                                   
    Out[3]: 

    TO SC SC AB
    TO BT BT BT BT SA
    TO BT BT BT BT SD

    TO AB
    TO RE AB
    TO RE RE SC SC SC BT BT BT BT

    TO AB
    TO RE AB
    TO RE RE AB
    TO RE RE RE SC BT BT SC BT BT

    TO SC AB
    TO AB




    In [1]: b.rpost_(slice(0,1))                                                                                                                                                                        
    Out[1]: 
    A([[[0.    , 0.    , 0.    , 0.8057]],

       [[0.    , 0.    , 0.    , 0.6958]],

       [[0.    , 0.    , 0.    , 0.586 ]],


       [[0.    , 0.    , 0.    , 0.5127]],

       [[0.    , 0.    , 0.    , 0.5127]],

       [[0.    , 0.    , 0.    , 0.5127]],


       [[0.    , 0.    , 0.    , 0.4028]],

       [[0.    , 0.    , 0.    , 0.4028]],

       [[0.    , 0.    , 0.    , 0.4028]],

       [[0.    , 0.    , 0.    , 0.4028]],



       [[0.    , 0.    , 0.    , 0.293 ]],

       [[0.    , 0.    , 0.    , 0.1099]]])







What happens next after GenTools mutate-ing the HepMC::event ?
-----------------------------------------------------------------

jcv GenTools::

    073 bool
     74 GenTools::execute()
     75 {
    ...
    160     // increase the event number
    161     ++m_evtid;
    162     return register_data(event);
    163 }


    176 bool
    177 GenTools::register_data(HepMC::GenEvent* event)
    178 {
    179     JM::EvtNavigator* nav = new JM::EvtNavigator();
    180     LogDebug << "time stamp: '" << m_current_timestamp << "'." << std::endl;
    181     nav->setTimeStamp(m_current_timestamp);
    182 
    183     SniperPtr<IDataMemMgr> mMgr(*getParent(), "BufferMemMgr");
    184     mMgr->adopt(nav, "/Event");
    185 
    186     JM::GenHeader* gen_header = new JM::GenHeader;
    187     JM::GenEvent* gen_event = new JM::GenEvent;
    188     gen_event->setEvent(event);
    189 
    190     gen_header->setEvent(gen_event);
    191     nav->addHeader("/Event/Gen", gen_header);
    192     return true;
    193 }


::

    epsilon:offline blyth$ jgr /Event/Gen
    ./Simulation/GenTools/share/dump.py:    outputsvc.property("OutputStreams").set({"/Event/Gen": "sample_gen.root"})
    ./Simulation/GenTools/src/PostGenTools.cc:    JM::GenHeader* gen_header = dynamic_cast<JM::GenHeader*>(evt_nav->getHeader("/Event/Gen"));
    ./Simulation/GenTools/src/GenTools.cc:    nav->addHeader("/Event/Gen", gen_header);
    ./Simulation/DetSimV2/DetSimMTUtil/src/LSExpMTPrimaryGeneratorAction.cc:    JM::GenHeader* gen_header = dynamic_cast<JM::GenHeader*>(evt_nav->getHeader("/Event/Gen"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpPrimaryGeneratorAction.cc:    JM::GenHeader* gen_header = dynamic_cast<JM::GenHeader*>(evt_nav->getHeader("/Event/Gen"));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:        nav->copyHeader(evt_nav, "/Event/Gen", "/Event/Gen");
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            output_streams["/Event/Gen"] = args.output
    ./DataModel/GenEventV2/cmt/requirements:apply_pattern cint_dictionary files="../Event/GenHeader.h ../Event/GenEvent.h"
    ./DataModel/EDMUtil/src/JunoEDMDefinitions.cc:JUNO_BOOK_EDM(JM::GenHeader, JM::GenEvent, 100, /Event/Gen);
    epsilon:offline blyth$ 



LSExpPrimaryGeneratorAction load_gen_event HepMC::GenEvent and converts into G4Event in LSExpPrimaryGeneratorAction::GeneratePrimaries
-----------------------------------------------------------------------------------------------------------------------------------------


jcv LSExpPrimaryGeneratorAction::

    463 HepMC::GenEvent*
    464 LSExpPrimaryGeneratorAction::load_gen_event() {
    465     // FIXME: Don't know the scope
    466     SniperDataPtr<JM::NavBuffer>  navBuf(*m_scope, "/Event");
    467     if (navBuf.invalid()) {
    468         return 0;
    469     }
    470     JM::EvtNavigator* evt_nav = navBuf->curEvt();
    471     if (not evt_nav) {
    472         return 0;
    473     }
    474     JM::GenHeader* gen_header = dynamic_cast<JM::GenHeader*>(evt_nav->getHeader("/Event/Gen"));
    475     if (not gen_header) {
    476         return 0;
    477     }
    478     JM::GenEvent* gen_event = dynamic_cast<JM::GenEvent*>(gen_header->event());
    479     if (not gen_event) {
    480         return 0;
    481     }
    482     return gen_event->getEvent();
    483 }

::

    (gdb) b LSExpPrimaryGeneratorAction::load_gen_event

    (gdb) bt
    #0  LSExpPrimaryGeneratorAction::load_gen_event (this=0x32472a0) at ../src/LSExpPrimaryGeneratorAction.cc:466
    #1  0x00007fffc24664f9 in LSExpPrimaryGeneratorAction::GeneratePrimaries (this=0x32472a0, anEvent=0x2a6d340) at ../src/LSExpPrimaryGeneratorAction.cc:87
    #2  0x00007fffce2c7b3a in G4RunManager::GenerateEvent(int) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #3  0x00007fffc26b5737 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #4  0x00007fffc1c16a3c in DetSimAlg::execute (this=0x250ef50) at ../src/DetSimAlg.cc:112
    #5  0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #6  0x00007fffef13d568 in TaskWatchDog::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so



     73 void LSExpPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
     74 {
     75     // special case: no task in the MT mode
     76     if (m_isMT && !m_scope) {
     77         G4ParticleTable* particletbl = G4ParticleTable::GetParticleTable();
     78         G4ParticleDefinition* particle_def = particletbl->FindParticle(particleName);
     79         particleGun->SetParticleDefinition(particle_def);
     80         particleGun->GeneratePrimaryVertex(anEvent);
     81         return;
     82     }
     83 
     84     // normal case: load data from event data buffer
     85 
     86     HepMC::GenEvent* gep = 0;
     87     gep = load_gen_event();
     88     if (not gep) {
     89         // TODO raise an Error
     90         assert(gep);
     91         return;
     92     }
     93     if (SniperLog::logLevel() <= 2) {
     94         gep->print();
     95     }
     96 
     97     // set the event id
     98     anEvent->SetEventID( gep->event_number() );
     99 
    100     // Refer to G4DataHelpers in Dayabay
    101     // Loop over vertex first
    102     //     Loop over particles in vertex
    103 
    104     // Loop over vertices in the event
    105     HepMC::GenEvent::vertex_const_iterator
    106         iVtx = (*gep).vertices_begin(),
    107         doneVtx = (*gep).vertices_end();
    108     for (/*nop*/; doneVtx != iVtx; ++iVtx) {
    109         const HepMC::FourVector& v = (*iVtx)->position();
    110         G4PrimaryVertex* g4vtx = new G4PrimaryVertex(v.x(), v.y(), v.z(), v.t());
    111 
    112         // Loop over particles in the vertex
    113         HepMC::GenVertex::particles_out_const_iterator
    114             iPart = (*iVtx)->particles_out_const_begin(),
    115             donePart = (*iVtx)->particles_out_const_end();
    116         for (/*nop*/; donePart != iPart; ++iPart) {
    117 
    118             // Only keep particles that are important for tracking
    119             // Use status to pass messages.
    120             int istatus = (*iPart)->status();
    121             if (istatus == 0x1000) {
    122                 // NEW: the normal particle, need to use G4 to do radioactivity decay simulation
    123             } else if (istatus != 1) {
    124                 continue;
    125             }
    126 
    127             G4int pdgcode= (*iPart)-> pdg_id();
    128             // check the pdgid
    129             G4ParticleTable* particletbl = G4ParticleTable::GetParticleTable();
    130             G4ParticleDefinition* particle_def = particletbl->FindParticle(pdgcode);
    131 
    ...
    439 
    440             } else if (pdgcode == 20022) {
    441                 particle_def = G4OpticalPhoton::Definition();
    442             }
    443             //
    444             const HepMC::FourVector& p = (*iPart)->momentum();
    445             // TODO: What's the unit!
    446             G4PrimaryParticle* g4prim=new G4PrimaryParticle(particle_def, p.px(), p.py(), p.pz());
    447 
    448             HepMC::ThreeVector pol = (*iPart)->polarization().normal3d();
    449             g4prim->SetPolarization(pol.x(),pol.y(),pol.z());
    450 
    451             g4vtx->SetPrimary(g4prim);
    452         }
    453 
    454         if (SniperLog::logLevel() <= 2) {
    455             g4vtx->Print();
    456         }
    457 
    458         anEvent->AddPrimaryVertex(g4vtx);
    459 
    460     }
    461 }


Break on exit of LSExpPrimaryGeneratorAction::GeneratePrimaries::

    (gdb) b 461
    Breakpoint 7 at 0x7fffc2468059: file ../src/LSExpPrimaryGeneratorAction.cc, line 461.


    (gdb) p anEvent
    $14 = (G4Event *) 0x2a6d340
    (gdb) p anEvent->numberOfPrimaryVertex
    $15 = 8
    (gdb) 


::

    g4-cc G4VUserPrimaryGeneratorAction

    g4-cls G4RunManager


    429 G4Event* G4RunManager::GenerateEvent(G4int i_event)
    430 { 
    ...
    438   G4Event* anEvent = new G4Event(i_event);
    ...
    458   if(printModulo > 0 && anEvent->GetEventID()%printModulo == 0 )
    459   { G4cout << "--> Event " << anEvent->GetEventID() << " starts." << G4endl; }
    460   userPrimaryGeneratorAction->GeneratePrimaries(anEvent);
    461   return anEvent;
    462 }

    epsilon:offline blyth$ g4-cc GenerateEvent
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4WorkerRunManager.cc:      G4Exception("G4RunManager::GenerateEvent()", "Run0032", FatalException,
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4WorkerRunManager.cc:  currentEvent = GenerateEvent(i_event);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4WorkerRunManager.cc:G4Event* G4WorkerRunManager::GenerateEvent(G4int i_event)
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4RunManager.cc:  currentEvent = GenerateEvent(i_event);
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4RunManager.cc:G4Event* G4RunManager::GenerateEvent(G4int i_event)
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/run/src/G4RunManager.cc:    G4Exception("G4RunManager::GenerateEvent()", "Run0032", FatalException,
    epsilon:offline blyth$ 


    (gdb) bt
    #0  LSExpPrimaryGeneratorAction::GeneratePrimaries (this=0x32472a0, anEvent=0x2a6d340) at ../src/LSExpPrimaryGeneratorAction.cc:461
    #1  0x00007fffce2c7b3a in G4RunManager::GenerateEvent(int) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #2  0x00007fffc26b5737 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #3  0x00007fffc1c16a3c in DetSimAlg::execute (this=0x250ef50) at ../src/DetSimAlg.cc:112
    #4  0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so


    027 bool G4SvcRunManager::SimulateEvent(int i_event) {
     28     currentEvent = GenerateEvent(i_event);
     29     eventManager->ProcessOneEvent(currentEvent);
     30     AnalyzeEvent(currentEvent);
     31     UpdateScoring();
     32     StackPreviousEvent(currentEvent);
     33     currentEvent = 0;
     34 
     35     if(runAborted) return false;
     36     return true;
     37 
     38 }

    (gdb) b CG4Ctx::setEvent
    Breakpoint 8 at 0x7fffcd48f6ce: file /home/blyth/opticks/cfg4/CG4Ctx.cc, line 262.
    (gdb) c
    Continuing.
    junoSD_PMT_v2::Initialize

    Breakpoint 8, CG4Ctx::setEvent (this=0x14bd49b90, event=0x2a6d340) at /home/blyth/opticks/cfg4/CG4Ctx.cc:262
    262	    _event = const_cast<G4Event*>(event) ; 
    (gdb) p event->numberOfPrimaryVertex
    $16 = 8

    (gdb) b CG4Ctx::setTrack
    Breakpoint 9 at 0x7fffcd48fa58: file /home/blyth/opticks/cfg4/CG4Ctx.cc, line 356.


    (gdb) p _track->GetGlobalTime()
    $18 = 0.80000001192092896
    (gdb) 




HepMC::GenEvent
-------------------

* https://rivet.hepforge.org/code/hepmc.bak/classHepMC_1_1GenEvent.html

* http://th-www.if.uj.edu.pl/~erichter/TauAnalFrame/external/hepmc269-SRC/doc/HepMC2_user_manual.pdf

signalprocessvertex:(optional) pointer to the vertex defined as the signal process - allows fastnavigation to the core of the event




::


    (gdb) p event.print(std::cout)
    ________________________________________________________________________________
    GenEvent: #0 ID=0 SignalProcessGenVertex Barcode: 0
     Momenutm units:MEV          Position units:MM      
     Entries this event: 8 vertices, 8 particles.
     Beam Particles are not defined.
     RndmState(0)=
     Wgts(0)=
     EventScale -1 [energy] 	 alphaQCD=-1	 alphaQED=-1
                                        GenParticle Legend
            Barcode   PDG ID      ( Px,       Py,       Pz,     E ) Stat  DecayVtx
    ________________________________________________________________________________
    Vertex:-1        ID:0     (X,cT)=-5.77e-01,-5.77e-01,-5.77e-01,+1.00e-01
     O:1  10001    20022     -1.63e-06,-1.63e-06,-1.63e-06,+2.82e-06 1  
    Vertex:-2        ID:0     (X,cT)=+5.77e-01,-5.77e-01,-5.77e-01,+2.00e-01
     O:1  10002    20022     +1.63e-06,-1.63e-06,-1.63e-06,+2.82e-06 1  
    Vertex:-3        ID:0     (X,cT)=-5.77e-01,+5.77e-01,-5.77e-01,+3.00e-01
     O:1  10003    20022     -1.63e-06,+1.63e-06,-1.63e-06,+2.82e-06 1  
    Vertex:-4        ID:0     (X,cT)=+5.77e-01,+5.77e-01,-5.77e-01,+4.00e-01
     O:1  10004    20022     +1.63e-06,+1.63e-06,-1.63e-06,+2.82e-06 1  
    Vertex:-5        ID:0     (X,cT)=-5.77e-01,-5.77e-01,+5.77e-01,+5.00e-01
     O:1  10005    20022     -1.63e-06,-1.63e-06,+1.63e-06,+2.82e-06 1  
    Vertex:-6        ID:0     (X,cT)=+5.77e-01,-5.77e-01,+5.77e-01,+6.00e-01
     O:1  10006    20022     +1.63e-06,-1.63e-06,+1.63e-06,+2.82e-06 1  
    Vertex:-7        ID:0     (X,cT)=-5.77e-01,+5.77e-01,+5.77e-01,+7.00e-01
     O:1  10007    20022     -1.63e-06,+1.63e-06,+1.63e-06,+2.82e-06 1  
    Vertex:-8        ID:0     (X,cT)=+5.77e-01,+5.77e-01,+5.77e-01,+8.00e-01
     O:1  10008    20022     +1.63e-06,+1.63e-06,+1.63e-06,+2.82e-06 1  
    ________________________________________________________________________________
    $10 = void
    (gdb) 



    (gdb) p event   # after mutate
    $9 = (HepMC::GenEvent &) @0x250ca50: 
          {_vptr.GenEvent = 0x7fffd7679970 <vtable for HepMC::GenEvent+16>, 
            m_signal_process_id = 0, 
            m_event_number = 0, 
            m_mpi = -1, 
            m_event_scale = -1, 
            m_alphaQCD = -1, 
            m_alphaQED = -1, 
            m_signal_process_vertex = 0x0, 
            m_beam_particle_1 = 0x0, 
            m_beam_particle_2 = 0x0, 
            m_weights = {m_weights = std::vector of length 0, capacity 0, m_names = std::map with 0 elements}, 
            m_random_states = std::vector of length 0, capacity 0, 
            m_vertex_barcodes = std::map with 8 elements = 
                  {[-1] = 0x16945d150, 
                   [-2] = 0x16945d3c0, 
                   [-3] = 0x169460a60, 
                   [-4] = 0x169460cd0, 
                   [-5] = 0x169460f40, 
                   [-6] = 0x1694611b0, 
                   [-7] = 0x169461420, 
                   [-8] = 0x169461690}, 
            m_particle_barcodes = std::map with 8 elements = 
                 {[10001] = 0x16945d210, 
                  [10002] = 0x16945d480, 
                  [10003] = 0x169460b20, 
                  [10004] = 0x169460d90, 
                  [10005] = 0x169461000, 
                  [10006] = 0x169461270, 
                  [10007] = 0x1694614e0, 
                  [10008] = 0x169461750}, 
            m_cross_section = 0x0, 
            m_heavy_ion = 0x0, 
            m_pdf_info = 0x0, 
            m_momentum_unit = HepMC::Units::MEV, 
            m_position_unit = HepMC::Units::MM}
    (gdb) 



"make input photons distinguishable by offseting start positions by the initial direction and times by the index"
----------------------------------------------------------------------------------------------------------------------

::

    O[blyth@localhost opticks]$ rm -rf /home/blyth/.opticks/InputPhotons
    O[blyth@localhost opticks]$ input_photons.sh 
    /home/blyth/junotop/ExternalLibs/Opticks/0.0.0-rc1/bashrc: line 4: /home/blyth/junotop/ExternalLibs/Opticks/0.0.0-rc1/bin/opticks-setup.sh: No such file or directory
    mo .bashrc OPTICKS_MODE:dev O : ordinary opticks dev ontop of juno externals CMTEXTRATAGS:
    Python 3.7.7 (default, May  7 2020, 21:25:33) 
    Type 'copyright', 'credits' or 'license' for more information
    IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.
    [2021-05-29 02:26:01,794] p281180 {/home/blyth/opticks/ana/input_photons.py:107} INFO - seeding with 0 
    [2021-05-29 02:26:01,794] p281180 {/home/blyth/opticks/ana/input_photons.py:110} INFO - generate RandomSpherical10 
    [2021-05-29 02:26:01,795] p281180 {/home/blyth/opticks/ana/input_photons.py:153} INFO - creating folder /home/blyth/.opticks/InputPhotons 
    [2021-05-29 02:26:01,795] p281180 {/home/blyth/opticks/ana/input_photons.py:156} INFO - save RandomSpherical10 to /home/blyth/.opticks/InputPhotons/RandomSpherical10.npy and /home/blyth/.opticks/InputPhotons/RandomSpherical10.json 
    {'seed': 0, 'name': 'RandomSpherical10', 'num': 10, 'creator': 'input_photons.py'}
    [[ -0.774  -0.245   0.583   0.1    -0.774  -0.245   0.583   1.     -0.602   0.     -0.799 440.      0.      0.      0.      0.   ]
     [ -0.217  -0.975   0.058   0.2    -0.217  -0.975   0.058   1.     -0.258   0.     -0.966 440.      0.      0.      0.      0.   ]
     [ -0.791  -0.596   0.136   0.3    -0.791  -0.596   0.136   1.     -0.17    0.     -0.986 440.      0.      0.      0.      0.   ]
     [ -0.504  -0.146   0.851   0.4    -0.504  -0.146   0.851   1.     -0.86    0.     -0.51  440.      0.      0.      0.      0.   ]
     [ -0.456   0.237  -0.858   0.5    -0.456   0.237  -0.858   1.      0.883   0.     -0.469 440.      0.      0.      0.      0.   ]
     [ -0.343  -0.448  -0.826   0.6    -0.343  -0.448  -0.826   1.      0.923   0.     -0.384 440.      0.      0.      0.      0.   ]
     [ -0.26    0.108  -0.96    0.7    -0.26    0.108  -0.96    1.      0.965   0.     -0.262 440.      0.      0.      0.      0.   ]
     [  0.581  -0.469   0.665   0.8     0.581  -0.469   0.665   1.     -0.753   0.      0.658 440.      0.      0.      0.      0.   ]
     [  0.809  -0.188   0.556   0.9     0.809  -0.188   0.556   1.     -0.566   0.      0.824 440.      0.      0.      0.      0.   ]
     [ -0.5     0.45    0.74    1.     -0.5     0.45    0.74    1.     -0.829   0.     -0.56  440.      0.      0.      0.      0.   ]]
    [2021-05-29 02:26:01,800] p281180 {/home/blyth/opticks/ana/input_photons.py:107} INFO - seeding with 0 
    [2021-05-29 02:26:01,800] p281180 {/home/blyth/opticks/ana/input_photons.py:110} INFO - generate CubeCorners 
    [2021-05-29 02:26:01,800] p281180 {/home/blyth/opticks/ana/input_photons.py:156} INFO - save CubeCorners to /home/blyth/.opticks/InputPhotons/CubeCorners.npy and /home/blyth/.opticks/InputPhotons/CubeCorners.json 
    {'seed': 0, 'name': 'CubeCorners', 'num': 8, 'creator': 'input_photons.py'}
    [[ -0.577  -0.577  -0.577   0.1    -0.577  -0.577  -0.577   1.      0.707   0.     -0.707 440.      0.      0.      0.      0.   ]
     [  0.577  -0.577  -0.577   0.2     0.577  -0.577  -0.577   1.      0.707  -0.      0.707 440.      0.      0.      0.      0.   ]
     [ -0.577   0.577  -0.577   0.3    -0.577   0.577  -0.577   1.      0.707   0.     -0.707 440.      0.      0.      0.      0.   ]
     [  0.577   0.577  -0.577   0.4     0.577   0.577  -0.577   1.      0.707  -0.      0.707 440.      0.      0.      0.      0.   ]
     [ -0.577  -0.577   0.577   0.5    -0.577  -0.577   0.577   1.     -0.707   0.     -0.707 440.      0.      0.      0.      0.   ]
     [  0.577  -0.577   0.577   0.6     0.577  -0.577   0.577   1.     -0.707   0.      0.707 440.      0.      0.      0.      0.   ]
     [ -0.577   0.577   0.577   0.7    -0.577   0.577   0.577   1.     -0.707   0.     -0.707 440.      0.      0.      0.      0.   ]
     [  0.577   0.577   0.577   0.8     0.577   0.577   0.577   1.     -0.707   0.      0.707 440.      0.      0.      0.      0.   ]]




GtOpticksTool what calls mutate : where is 1/10 input photons lost ?
----------------------------------------------------------------------

::

    epsilon:offline blyth$ jgr mutate

    ./Simulation/GenDecay/src/GtDecayerator.h:    bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenDecay/src/GtDecayerator.cpp:GtDecayerator::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/GenTools/IGenTool.h:        virtual bool mutate(HepMC::GenEvent& event)=0;
    ./Simulation/GenTools/src/GtHepMCDumper.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtPelletronBeamerTool.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtHepEvtGenTool.cc:GtHepEvtGenTool::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/src/GtSNTool.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtPelletronBeamerTool.cc:GtPelletronBeamerTool::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/src/GtHepEvtGenTool.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtGstTool.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtPositionerTool.h:        bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtOpticksTool.cc:bool GtOpticksTool::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/src/GtOpticksTool.cc:    std::cout << "GtOpticksTool::mutate numPhotons " << numPhotons << std::endl ; 
    ./Simulation/GenTools/src/GtOpticksTool.cc:bool GtOpticksTool::mutate(HepMC::GenEvent& ){ return false ; }
    ./Simulation/GenTools/src/GtOPLoaderTool.cc:GtOPLoaderTool::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/src/GtTimeOffsetTool.cc:GtTimeOffsetTool::mutate(HepMC::GenEvent& event)
    ./Simulation/GenTools/src/GenTools.cc:    // mutate event
    ./Simulation/GenTools/src/GenTools.cc:            if ((*it)->mutate(*event)) {
    ./Simulation/GenTools/src/GenTools.cc:                // mutate failed
    ./Simulation/GenTools/src/GtOpScintTool.h:    bool mutate(HepMC::GenEvent& event);
    ./Simulation/GenTools/src/GtSNTool.cc:GtSNTool::mutate(HepMC::GenEvent& event) 
    ./Simulation/GenTools/src/GtOpScintTool.cc:GtOpScintTool::mutate(HepMC::GenEvent& event)

    epsilon:offline blyth$ jcv GenTools

    BP=GenTools::execute tds3


Opticks input photons enter via the source buffer and use dummy gensteps with gencode OpticksGenstep_EMITSOURCE
-------------------------------------------------------------------------------------------------------------------

::

    627     else if(gencode == OpticksGenstep_EMITSOURCE)
    628     {
    629         // source_buffer is input only, photon_buffer output only, 
    630         // photon_offset is same for both these buffers
    631         pload(p, source_buffer, photon_offset );
    632         s.flag = TORCH ;
    633 #ifdef WITH_REFLECT_CHEAT_DEBUG
    634         s.ureflectcheat = debug_control.w > 0u ? float(photon_id)/float(num_photon) : -1.f ;
    635 #endif
    636     }
    637 

oxrap/OEvent.cc::

    227 #ifdef WITH_SOURCE
    228     NPY<float>* source = evt->getSourceData() ;
    229     if(source)
    230     {
    231         OpticksBufferControl* sourceCtrl = evt->getSourceCtrl();
    232         m_sourceMarkDirty = sourceCtrl->isSet("BUFFER_COPY_ON_DIRTY") ;
    233         m_source_buffer = m_ocontext->createBuffer<float>( source, "source");
    234     }
    235     else
    236     {
    237         m_source_buffer = m_ocontext->createEmptyBufferF4();
    238     }
    239     m_context["source_buffer"]->set( m_source_buffer );
    240     m_source_buf = new OBuf("source", m_source_buffer);
    241 #endif
    242 

::

    epsilon:opticks blyth$ opticks-f setSource
    ./cfg4/CG4.cc:    if(so) evt->setSourceData(so, clone_); 
    ./optickscore/OpticksEvent.hh:       void setSourceData(NPY<float>* source_data_, bool clone_ );   // from CG4::postpropagate
    ./optickscore/OpticksEvent.cc:void OpticksEvent::setSourceData(NPY<float>* source_data_, bool clone_ )
    ./optickscore/OpticksEvent.cc:    OK_PROFILE("_OpticksEvent::setSourceData");
    ./optickscore/OpticksEvent.cc:        LOG(debug) << "OpticksEvent::setSourceData"
    ./optickscore/OpticksEvent.cc:    OK_PROFILE("_OpticksEvent::setSourceData_MultiViewNPY");  // NB dont use "." in the labels it messes up the ini
    ./optickscore/OpticksEvent.cc:    OK_PROFILE("OpticksEvent::setSourceData_MultiViewNPY");
    ./optickscore/OpticksEvent.cc:    OK_PROFILE("OpticksEvent::setSourceData");
    ./optickscore/OpticksRun.cc:        if(m_g4evt) m_g4evt->setSourceData( emitsource, m_clone ); 
    ./optickscore/OpticksRun.cc:        if(m_evt)   m_evt->setSourceData( emitsource, m_clone );
    ./optickscore/OpticksRun.cc:        m_evt->setSourceData( m_g4evt ? m_g4evt->getSourceData() : NULL, m_clone ) ;   
    ./npy/ViewNPY.cpp:from OpticksEvent::setSourceData
    ./npy/TorchStepNPY.hpp:       void setSourceLocal(const char* s );
    ./npy/TorchStepNPY.cpp:        case SOURCE         : setSourceLocal(s)    ;break;
    ./npy/TorchStepNPY.cpp:void TorchStepNPY::setSourceLocal(const char* s)
    epsilon:opticks blyth$ vi cfg4/CG4.cc
    epsilon:opticks blyth$ 



    373 /**     
    374 OpticksRun::setupSourceData
    375 -----------------------------
    376         
    377 This is invoked from OpticksRun::importGensteps, it is an 
    378 important part of how input source photons are provisioned
    379 to both simulations.
    380 
    381 **/
    382 void OpticksRun::setupSourceData()
    383 {   
    384     if(hasActionControl(m_gensteps, "GS_EMITSOURCE"))
    385     {   
    386         void* aux = m_gensteps->getAux();
    387         assert( aux );
    388         NPY<float>* emitsource = (NPY<float>*)aux ;
    389         
    390         if(m_g4evt) m_g4evt->setSourceData( emitsource, m_clone );
    391         if(m_evt)   m_evt->setSourceData( emitsource, m_clone );
    392 
    393         LOG(LEVEL) 
    394             << "GS_EMITSOURCE"
    395             << " emitsource " << emitsource->getShapeString()
    396             ;
    397     }
    398     else
    399     {
    400         NPY<float>* g4source = m_g4evt ? m_g4evt->getSourceData() : NULL ;
    401         m_evt->setSourceData( g4source, m_clone ) ;
    402     }
    403 }




10 ana/input_photons.py 
--------------------------

* how to get the normally genstep driven Opticks work with input photons from within JUNO offline ?

  * did this before in CFG4 using a standin genstep, but that approach not workable here as
    the source of genstep is C+S 
  * can add G4Opticks::setInputPhotons(NPY<float>*) but where to call that from 
    GtOpticksTool can leave a handy instance pointer to itself that 
   
 

* somehow G4 machinery looses one photon ?

::

    In [4]: b.seqhis_ana.table
    Out[4]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                                  9         1.00 
    0000           7ccccd        0.444           4        [6 ] TO BT BT BT BT SD
    0001               4d        0.333           3        [2 ] TO AB
    0002           8ccccd        0.111           1        [6 ] TO BT BT BT BT SA
    0003              4cd        0.111           1        [3 ] TO BT AB
    .                                  9         1.00 

    In [5]: bls
    Out[5]: 
    TO BT BT BT BT SD
    TO BT BT BT BT SD
    TO BT BT BT BT SD
    TO BT BT BT BT SD
    TO AB
    TO AB
    TO BT BT BT BT SA
    TO AB
    TO BT AB







Simulation/GenTools/cmt/requirements
----------------------------------------

::

    epsilon:offline blyth$ svn diff Simulation/GenTools/cmt/requirements
    Index: Simulation/GenTools/cmt/requirements
    ===================================================================
    --- Simulation/GenTools/cmt/requirements	(revision 4581)
    +++ Simulation/GenTools/cmt/requirements	(working copy)
    @@ -8,6 +8,11 @@
     use ROOT  v* Externals
     use Geant4 v* Externals
     
    +# The below sets blank macro values unless CMTEXTRATAGS envvar includes opticks, 
    +# thus it does no harm when the optional Opticks external is not installed.
    +use OpticksG4OK    v* Externals
    +
    +
     use BufferMemMgr v* CommonSvc
     use RandomSvc v* CommonSvc
     

In other pkgs the OpticksG4OK come in via DetSimPolicy Simulation/DetSimV2/DetSimPolicy/cmt/requirements
but GenTools does not depend on that for unknown reasons.





logging makes be unconvinced that SetTrackSecondariesFirst(true) 
--------------------------------------------------------------------

* code look shows that is is set by is specifically excluded at doing 
  anything with reemission : precisely when I need it 

::

    139 
    140     if (m_useScintillation && 1) { // DsG4 (with re-emission)
    141         DsG4Scintillation* scint = new DsG4Scintillation(m_opticksMode);
    142 
    143         scint->SetDoQuenching(m_enableQuenching);
    144         scint->SetBirksConstant1(m_birksConstant1);
    145         scint->SetBirksConstant2(m_birksConstant2);
    146         scint->SetGammaSlowerTimeConstant(m_gammaSlowerTime);
    147         scint->SetGammaSlowerRatio(m_gammaSlowerRatio);
    148         scint->SetNeutronSlowerTimeConstant(m_neutronSlowerTime);
    149         scint->SetNeutronSlowerRatio(m_neutronSlowerRatio);
    150         scint->SetAlphaSlowerTimeConstant(m_alphaSlowerTime);
    151         scint->SetAlphaSlowerRatio(m_alphaSlowerRatio);
    152         scint->SetDoReemission(m_doReemission);
    153         scint->SetDoReemissionOnly(m_doReemissionOnly);
    154         scint->SetDoBothProcess(m_doScintAndCeren);
    155         scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
    156         scint->SetPreQE(1./m_scintPhotonScaleWeight);
    157         scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
    158         scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
    159         scint->SetTrackSecondariesFirst(true);
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    160         scint->SetFlagDecayTimeFast(flagDecayTimeFast);
    161         scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
    162         scint->SetVerboseLevel(0);
    163 


::

    g4-cls G4Scintillation

    156         void SetTrackSecondariesFirst(const G4bool state);
    157         // If set, the primary particle tracking is interrupted and any
    158         // produced scintillation photons are tracked next. When all 
    159         // have been tracked, the tracking of the primary resumes.
    160 
    161         G4bool GetTrackSecondariesFirst() const;
    162         // Returns the boolean flag for tracking secondaries first.
    163 

    296         ////////////////////////////////////////////////////////////////
    297 
    298         aParticleChange.SetNumberOfSecondaries(fNumPhotons);
    299 
    300         if (fTrackSecondariesFirst) {
    301            if (aTrack.GetTrackStatus() == fAlive )
    302                   aParticleChange.ProposeTrackStatus(fSuspend);
    303         }
    304 
    305         ////////////////////////////////////////////////////////////////





    jcv DsG4Scintillation

    360 inline
    361 void DsG4Scintillation::SetTrackSecondariesFirst(const G4bool state)
    362 {
    363     fTrackSecondariesFirst = state;
    364 }
    365 
    366 inline
    367 G4bool DsG4Scintillation::GetTrackSecondariesFirst() const
    368 {
    369         return fTrackSecondariesFirst;
    370 }



     197 G4VParticleChange*
     198 DsG4Scintillation::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     199 
     ...
     470 
     471     aParticleChange.SetNumberOfSecondaries(NumTracks);
     472 
     473     if (fTrackSecondariesFirst) {
     474         if (!flagReemission)
     475             if (aTrack.GetTrackStatus() == fAlive )
     476                 aParticleChange.ProposeTrackStatus(fSuspend);
     477     }
     478 





running tips
--------------

::

     export CG4Ctx=INFO
     export DsG4Scintillation=INFO
     export LocalG4Cerenkov1042=INFO

     tds3




::

    opticks --input-photon-path 



thu may 27 2021 : JUNO-Opticks "gun" tracing with eye to adding "opticks_input_photon_source" standin for "gun"
------------------------------------------------------------------------------------------------------------------

* get path to input photon file by envvar for simplicity 

::

    jcv tut_detsim JUNOApplication JUNODetSimModule
    

* https://docs.python.org/3/library/argparse.html

::

    >>> # create the top-level parser
    >>> parser = argparse.ArgumentParser(prog='PROG')
    >>> parser.add_argument('--foo', action='store_true', help='foo help')
    >>> subparsers = parser.add_subparsers(help='sub-command help')
    >>>
    >>> # create the parser for the "a" command
    >>> parser_a = subparsers.add_parser('a', help='a help')
    >>> parser_a.add_argument('bar', type=int, help='bar help')
    >>>
    >>> # create the parser for the "b" command
    >>> parser_b = subparsers.add_parser('b', help='b help')
    >>> parser_b.add_argument('--baz', choices='XYZ', help='baz help')
    >>>
    >>> # parse some argument lists
    >>> parser.parse_args(['a', '12'])
    Namespace(bar=12, foo=False)
    >>> parser.parse_args(['--foo', 'b', '--baz', 'Z'])
    Namespace(baz='Z', foo=True)

 
::

     096         subparsers = parser.add_subparsers(help='Please select the generator mode',
      97                                            dest='gentool_mode')
      98         subparsers.required = True
      99         self.register_subparser_gun(subparsers, base_parser_positioner)
     100         self.register_subparser_photon(subparsers, base_parser_positioner)
     101         self.register_subparser_gendecay(subparsers, base_parser_positioner)


::

     619     def register_subparser_gun(self, subparsers, base_parser_positioner):
     620         parser_gun = subparsers.add_parser("gun", help="gun mode", parents=[base_parser_positioner])
     621         parser_gun.add_argument("--particles",default="gamma", nargs='+',
     622                                 help="Particles to do the simulation.")
     623         parser_gun.add_argument("--momentums",default=1.0, nargs='+',
     624                                 type=float, 
     625                                 help="Momentums(MeV) p1 p2 ....")
     626         parser_gun.add_argument("--momentums-mode", default="Fix",
     627                                     choices=["Fix", "Uniform", "Range", "Gaus"],
     628                                     help="different momentum modes")
     629         parser_gun.add_argument("--momentums-extra-params", nargs='+',
     630                                 type=float,
     631                                 help="Extra Momentums Parameters(MeV) p1 p2 .... when mode is different, meaning is different."
     632                                      " Uniform: [mom-param, mom+param];"
     633                                      " Range: [mom, param];"
     634                                      " Gaus: Gaus(mom, param);"
     635                                 )
     636         parser_gun.add_argument("--momentums-interp", default="Momentum",
     637                                     choices=["Momentum", "KineticEnergy", "TotalEnergy"],
     638                                     help="Interpret momentum.")
     639         parser_gun.add_argument("--positions",default=[(0,0,0)], nargs='+',
     640                                 type=float, action=MakeTVAction,
     641                                 help="Positions (mm) x1 y1 z1 x2 y2 z2 ....")
     642         parser_gun.add_argument("--times",default=None, nargs='+',
     643                                 type=float,
     644                                 help="Time (mm) t1 t2 ....")
     645         parser_gun.add_argument("--directions",default=None, nargs='+',
     646                                 type=float, action=MakeTVAction,
     647                                 help="If you don't set, the directions are randoms. "
     648                                      "Directions dx1 dy1 dz1 dx2 dy2 dz2 ....")

     649         parser_gun.add_argument("--opticks-input-photon-source-path", default=None,  
     650                                 help="overrides other gun options with input photons from .npy files" 
     651                                      " for Opticks debugging, requires compilation WITH_G4OPTICKS" )
     652     


::

     jgr momentums_extra_params

    epsilon:offline blyth$ jgr momentums_extra_params
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        if args.momentums_extra_params:
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            gun.property("particleMomentumParams").set(args.momentums_extra_params)
    epsilon:offline blyth$ 



Maybe create an opticks gentool, rather than overriding the existing gun.

Cannot use existing generators as for alignment purposes 
needs to operate without consuming any randoms. 


::

    epsilon:offline blyth$ jgr GtGunGenTool
    ./Simulation/GenTools/doc/README.rst:GtGunGenTool
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/src/GtGunGenTool.cc:#include "GtGunGenTool.h"
    ./Simulation/GenTools/src/GtGunGenTool.cc:DECLARE_TOOL(GtGunGenTool);
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::GtGunGenTool(const std::string& name)
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::~GtGunGenTool()
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::configure()
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::mutate(HepMC::GenEvent& event)
    ...
 

thu may 27 2021 : how to do JUNO-Opticks aligned running
-----------------------------------------------------------------


Previous aligned running was done in CFG4 in a fully controlled Geant4 
environment.  Doing it within JUNO Offline will require:

1. input photons : needs new development as need to work with JUNO-Offline 
   approach to generation  

   * how much of existing machinery cfg4/CInputPhotonSource is usable 
     in JUNO context ?  CInputPhotonSource < CSource < G4VPrimaryGenerator

   * investigate existing JUNO generators and see how to add
     a WITH_G4OPTICKS only generator based on CInputPhotonSoutce 

2. input random numbers : existing machinery CAlignEngine should 
   be directly usable as this is done at Geant4 level beneath the level 
   of the experiment  


thu may 27 2021 : the case for JUNO-Opticks aligned running 
-----------------------------------------------------------------


Initially I was planning to do statistical non-random-aligned comparisons first 
before reviving the random aligned but given the large differences 
I see in the histories I think the fastest way to resolve problems and debug the 
machinery maybe to start with the sledgehammer of random-aligned running.  

Random aligned running uses input photons so there is no consumption 
of random numbers to generate the photons and input random numbers. 
With random aligned running you need a “quiet" Geant4 environment in terms 
of the random numbers that Geant4 consumes.
You can configure Geant4 to use the sequence of random numbers that you give it.

Random aligned running is difficult to get working across many photons
because it means you need to understand every random number consumed by Geant4 
and have Opticks do the same.  While it is difficult to keep the simulations together 
for large numbers of photons due to edge case details of Geant4 doing complicated things it 
is not so difficult to do for a small number of photons : and those small numbers of photons 
can be exceedingly informative at finding discrepancies because you 
can make direct comparisons of every photon step unclouded by statistics.





thu may 27 2021 : brief description of current investigations 
----------------------------------------------------------------

Currently there are big differences, although as this stage the problems 
could be bugs in the bookkeeping machinery rather than the simulation. 

I use the convention of using +ve tags Opticks events and negated ones for Geant4 events 
In the below a (OK:1) and b (G4:-1) are two events being compared

Get into ipython and load two events (+1 and -1) using::

    ab.sh 1 —-nocompare   

        ## —nocompare currently as there are metadata bugs that need to be fixed
        ## before the comparison table will work 


For every step of the photon I record four bits (aka nibble) of history flag into 
a 64 bit unsigned long long called “seqhis” (there is also “seqmat” for materials)
So I record the history of up to 16 steps of the photon.   
Sorting these integers and counting how many there are of each gives 
a history table showing how many photons with each history.

The below table shows the hex of the seqhis and the fraction of that and the 
count with the label showing the step history in readable form

   SI : scintillation generation
   CK : cherenkov generation
   AB : bulk absorb 
   BT : boundary transmit 
   SD : surface detect  
   SA : surface absorb 
   SC : bulk scatter 
   RE : reemission    


In [1]: a.seqhis_ana.table[:20]
Out[1]: 
all_seqhis_ana
.                     cfo:-  1:g4live:source 
.                              11278         1.00 
0000               42        0.147        1653        [2 ] SI AB
0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
0004              452        0.037         422        [3 ] SI RE AB
0005              462        0.035         392        [3 ] SI SC AB
0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
0011               41        0.013         142        [2 ] CK AB
0012             4662        0.012         137        [4 ] SI SC SC AB
0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
0014             4cc2        0.012         130        [4 ] SI BT BT AB
0015             4552        0.011         124        [4 ] SI RE RE AB
0016             4652        0.011         121        [4 ] SI RE SC AB
0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
.                              11278         1.00 


### G4 in the below has much more AB that OK above : MAYBE RE-JOIN not working properly 
### G4 has one extra “BT” on the way to SD : that is the virtual PMT container that is 
### skipped from GPU geometry (perhaps will put that back to match this)

In [2]: b.seqhis_ana.table[:20]
Out[2]: 
all_seqhis_ana
.                     cfo:-  -1:g4live:source    
.                              11278         1.00 
0000               42        0.315        3555        [2 ] SI AB
0001              452        0.099        1122        [3 ] SI RE AB
0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
0003              462        0.043         480        [3 ] SI SC AB
0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
0006             4552        0.028         314        [4 ] SI RE RE AB
0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
0008               41        0.022         246        [2 ] CK AB
0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
0011             4662        0.013         150        [4 ] SI SC SC AB
0012             4652        0.013         146        [4 ] SI RE SC AB
0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
0015             4562        0.010         111        [4 ] SI SC RE AB
0016             4cc2        0.008          95        [4 ] SI BT BT AB
0017            45552        0.008          93        [5 ] SI RE RE RE AB
0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
.                              11278         1.00 

In [3]: 



As the G4 machinery (event B) has only been up and running for a day or so, 
I don’t believe what I am seeing yet. It needs debugging.

In particular reemission is quite complicated because there is a fundamental 
difference regarding how the simulation is done on GPU and CPU that has to be 
handled in order to do the bookkeeping in the same way.

In JUNO Offline Geant4 reemission is handled as a secondary track 
but in Opticks a fraction of the AB (bulk absorbed) gets RE (reemitted).
This means that for Geant4 events to be matched in the above way 
you have to join together the secondary reemission  photons with their parents
across multiple generations of reemission.
I call that REJOIN-ing. The machinery to do that is fragile,  
I am currently debugging this.

If the REJOIN-ing is done wrong then you join the wrong photons together and 
mess up the histories. That could well be happening. 

Note that the above is just the start of the table the full table 
has many more lines with all the possible histories of the photons.





metadata numPhotons double counting ?
-----------------------------------------

::



::

    epsilon:offline blyth$ opticks-f setNumPhotons
    ...
    ./cfg4/CManager.cc:            g4evt->setNumPhotons( numPhotons, resize ); 
    ...


    142 void CManager::EndOfEventAction(const G4Event*)
    143 {
    144     LOG(LEVEL);
    145 
    146     char ctrl = '-' ;
    147     plog::Severity level = info ;
    148     if(m_ok->isSave())
    149     {
    150         unsigned numPhotons = m_ctx->getNumTrackOptical() ;
    151         //   this doesnt account for reemission REJOIN, so it will be too high 
    152         
    153         OpticksEvent* g4evt = m_ok->getEvent(ctrl) ;
    154         
    155         if(g4evt)
    156         {   
    157             LOG(level) << " --save g4evt numPhotons " << numPhotons ;
    158             bool resize = false ; 
    159             g4evt->setNumPhotons( numPhotons, resize );
    160             
    161             m_ok->saveEvent(ctrl);
    162             m_ok->resetEvent(ctrl);
    163         }
    164     }
    165     else
    166     {   
    167         LOG(level) << " NOT saving as no --save " ;
    168     }
    169 }


wed may 26 2021 : with first try at REJOIN : but suspect non-sequential RE messing up REJOIN
-----------------------------------------------------------------------------------------------


* "SI AB" : G4 - OK : 3555 - 1653 = 1902
* "CK AB" : G4 - OK : 246 - 142 = 104

Because Opticks does RE as a fraction of AB... 
does that mean should adjust the absorption_distance. 
Surely not, as this has matched before. 

First check simpler things like dumping absorption distance etc..

* Also "CK AB" also lots less with OK.  
* Note that "CK AB" still has reemission prob 

::

    132     if (absorption_distance <= scattering_distance)
    133     {   
    134         if (absorption_distance <= s.distance_to_boundary)
    135         {   
    136             p.time += absorption_distance/speed ;   
    137             p.position += absorption_distance*p.direction;
    138             
    139             const float& reemission_prob = s.material1.w ;  
    140             float u_reemit = reemission_prob == 0.f ? 2.f : curand_uniform(&rng);  // avoid consumption at absorption when not scintillator
    141             
    142             if (u_reemit < reemission_prob)
    143             {   
    144                 // no materialIndex input to reemission_lookup as both scintillators share same CDF 
    145                 // non-scintillators have zero reemission_prob
    146                 p.wavelength = reemission_lookup(curand_uniform(&rng));
    147                 p.direction = uniform_sphere(&rng);
    148                 p.polarization = normalize(cross(uniform_sphere(&rng), p.direction));
    149                 p.flags.i.x = 0 ;   // no-boundary-yet for new direction
    150                 
    151                 s.flag = BULK_REEMIT ;
    152                 return CONTINUE;
    153             }   
    154             else
    155             {   
    156                 s.flag = BULK_ABSORB ;
    157                 return BREAK;
    158             }
    159         }
    160         //  otherwise sail to boundary  
    161     }
    162     else







Counts with RE in any slot fairly close::

    In [38]: np.where(are)[0].shape
    Out[38]: (3724,)

    In [39]: np.where(bre)[0].shape
    Out[39]: (3956,)




::

    epsilon:j blyth$ ab.sh 1 --nocompare

    In [4]: a.seqhis_ana.table[:20]   ##  
    Out[4]: 
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [5]: b.seqhis_ana.table[:20]    ## G4 lots more "SI AB" and "CK AB" 
    Out[5]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.315        3555        [2 ] SI AB
    0001              452        0.099        1122        [3 ] SI RE AB
    0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
    0003              462        0.043         480        [3 ] SI SC AB
    0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
    0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
    0006             4552        0.028         314        [4 ] SI RE RE AB
    0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
    0008               41        0.022         246        [2 ] CK AB
    0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
    0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
    0011             4662        0.013         150        [4 ] SI SC SC AB
    0012             4652        0.013         146        [4 ] SI RE SC AB
    0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
    0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
    0015             4562        0.010         111        [4 ] SI SC RE AB
    0016             4cc2        0.008          95        [4 ] SI BT BT AB
    0017            45552        0.008          93        [5 ] SI RE RE RE AB
    0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
    0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
    .                              11278         1.00 





wed may 26 2021 : review reemission and REJOIN-ing
------------------------------------------------------

::


    246 /**
    247 CRecorder::Record
    248 --------------------
    ...
    259 * see notes/issues/reemission_review.rst
    260 
    261 Rejoining happens on output side not in the crec CStp list.
    262 
    263 The rejoins of AB(actually RE) tracks with reborn secondaries 
    264 are done by writing two (or more) sequences of track steps  
    265 into the same record_id in the record buffer at the 
    266 appropriate non-zeroed slot.
    267 
    268 WAS a bit confused by this ...
    269  
    270 This assumes that the REJOINing track will
    271 be the one immediately after the original AB. 
    272 By virtue of the Cerenkov/Scintillation process setting:
    273 
    274      SetTrackSecondariesFirst(true)
    275   
    276 If not so, this will "join" unrelated tracks ?
    277 (Really? remember it has random access into record buffer
    278 using record_id)
    279 
    280 TODO: find how to check this is the case and assert on it
    281 
    289 **/





tue numPhotons metadata out of whack with evt ?
------------------------------------------------

::

    epsilon:ana blyth$ js.py /tmp/blyth/opticks/source/evt/g4live/natural/*/parameters.json --keys Tag,NumPhotons
    /tmp/blyth/opticks/source/evt/g4live/natural/-1/parameters.json
    Tag                  : -1
    NumPhotons           : 17384
    /tmp/blyth/opticks/source/evt/g4live/natural/-2/parameters.json
    Tag                  : -2
    NumPhotons           : 17815
    /tmp/blyth/opticks/source/evt/g4live/natural/0/parameters.json
    Tag                  : -
    NumPhotons           : -
    /tmp/blyth/opticks/source/evt/g4live/natural/1/parameters.json
    Tag                  : 1
    NumPhotons           : 11278
    /tmp/blyth/opticks/source/evt/g4live/natural/2/parameters.json
    Tag                  : 2
    NumPhotons           : 11632
    epsilon:ana blyth$ 


This might be explained by the REJOIN-ing not working yet, leading to the reemission
photons being added to the total for G4.  


::

    In [11]: 17384 - 11278
    Out[11]: 6106


Every RE in OK:1 may be leading a separate "photon" in G4:-1 

* need to count RE nibbles, not photons
* number of RE nibbles 5406 is in the ballpark 

* also the truncation will be different as when the photons are split 
  at each RE they will not be truncated as much in G4:-1 


::

    In [1]: a.seqhis_ana.seq_any_count_nibble("RE")
    Out[1]: 5406

    In [2]: a.seqhis_ana.seq_any_count_nibble("SI")
    Out[2]: 11015

    In [3]: a.seqhis_ana.seq_any_count_nibble("CK")
    Out[3]: 263

    In [4]: b.seqhis_ana.seq_any_count_nibble("RE")
    Out[4]: 0



The truth is *11278*::

    epsilon:ana blyth$ gs.sh 1 
    [2021-05-25 18:54:48,089] p84123 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/1/gs.npy shape (66, 6, 4) 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:102} INFO - check_pdgcode
          11 :         e- : 62 
          22 :      gamma : 4 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:116} INFO - check_ranges
     tr     0.7426     3.5089 
     xr   -15.7261    77.3296 
     yr   -90.1411   401.1544 
     zr  -537.4855  -206.4406 

::

    ab.sh 1 --nocompare


    In [3]: a.seqhis_ana.table[:20]
    Out[3]: 
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [4]: b.seqhis_ana.table[:20]
    Out[4]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.494        5570        [2 ] SI AB                ##
    0001           7cccc2        0.131        1474        [6 ] SI BT BT BT BT SD
    0002              462        0.066         745        [3 ] SI SC AB             ##
    0003           8cccc2        0.056         635        [6 ] SI BT BT BT BT SA
    0004          7cccc62        0.056         635        [7 ] SI SC BT BT BT BT SD
    0005          8cccc62        0.026         288        [7 ] SI SC BT BT BT BT SA
    0006         7cccc662        0.022         247        [8 ] SI SC SC BT BT BT BT SD
    0007               41        0.022         246        [2 ] CK AB                ##  
    0008             4662        0.021         234        [4 ] SI SC SC AB          ##
    0009             4cc2        0.013         144        [4 ] SI BT BT AB           
    0010         8cccc662        0.009          97        [8 ] SI SC SC BT BT BT BT SA
    0011        7cccc6662        0.007          75        [9 ] SI SC SC SC BT BT BT BT SD
    0012            4cc62        0.006          71        [5 ] SI SC BT BT AB
    0013            46662        0.006          70        [5 ] SI SC SC SC AB
    0014          7ccccc2        0.006          68        [7 ] SI BT BT BT BT BT SD
    0015              4c2        0.005          62        [3 ] SI BT AB
    0016         7ccccc62        0.004          42        [8 ] SI SC BT BT BT BT BT SD
    0017          8ccccc2        0.004          42        [7 ] SI BT BT BT BT BT SA
    0018        8cccc6662        0.004          40        [9 ] SI SC SC SC BT BT BT BT SA
    0019             4c62        0.003          35        [4 ] SI SC BT AB
    .                              11278         1.00 




Observations:

1. lots less BULK_ABSORB in OK:1 cf G4:-1 

   * consistent with many of the extra G4 "AB" going on to be RE-emitted
     and appearing as extra photons with G4 

   * counts for G4 histories ending with AB are elevated compared to OK, again reemission   

2. no RE:reemission in G4:-1

3. extra BT in G4 vs OK (virtual hatbox?)
4. G4 small CK/SI mismatches genstep : MUST BE A BUG  



After first try at REJOIN::

  

    In [5]: b.seqhis_ana.table[:20]
    Out[5]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.315        3555        [2 ] SI AB
    0001              452        0.099        1122        [3 ] SI RE AB
    0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
    0003              462        0.043         480        [3 ] SI SC AB
    0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
    0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
    0006             4552        0.028         314        [4 ] SI RE RE AB
    0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
    0008               41        0.022         246        [2 ] CK AB
    0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
    0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
    0011             4662        0.013         150        [4 ] SI SC SC AB
    0012             4652        0.013         146        [4 ] SI RE SC AB
    0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
    0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
    0015             4562        0.010         111        [4 ] SI SC RE AB
    0016             4cc2        0.008          95        [4 ] SI BT BT AB
    0017            45552        0.008          93        [5 ] SI RE RE RE AB
    0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
    0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
    .                              11278         1.00 


* now get RE
* but still more AB 
* TODO: check the REJOIN points, suspicion of non-sequential 


How to check are REJOIN-in the correct tracks  ?
----------------------------------------------------

::

    In [26]: als[:2]
    Out[26]: 
    SI BT BT BT SD
    SI RE AB

    In [27]: bls[:2]
    Out[27]: 
    SI AB
    SI SC SC BT BT BT BR BT BT SC

    In [28]: a.rpost_(slice(0,10))[0]
    Out[28]: 
    A([[    60.4266,    113.5289,   -419.3243,      5.6764],
       [-16342.6618,   6793.4202,    184.9422,     96.939 ],
       [-16454.3596,   6839.198 ,    188.6044,     97.5616],
       [-17860.6525,   7410.5045,    243.5377,    104.5198],
       [-17866.1458,   7414.1667,    243.5377,    104.5564],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ]])

    In [29]: b.rpost_(slice(0,10))[0]
    Out[29]: 
    A([[    60.4266,    113.5289,   -419.3243,      4.9074],
       [-11856.4409,   1254.3107,   -413.831 ,     66.213 ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ]])




Find psel with RE in any slot::


    In [31]: a.seqhis_ana.seq_any("RE")
    Out[31]: array([False,  True, False, ..., False, False, False])

    In [32]: b.seqhis_ana.seq_any("RE")
    Out[32]: array([False, False, False, ...,  True, False, False])

    In [33]: are = a.seqhis_ana.seq_any("RE")

    In [34]: bre = b.seqhis_ana.seq_any("RE")

    In [35]: np.where(are)
    Out[35]: (array([    1,     4,     5, ..., 11262, 11263, 11266]),)

    In [36]: np.where(are)[0]
    Out[36]: array([    1,     4,     5, ..., 11262, 11263, 11266])

    In [37]: np.where(bre)[0]
    Out[37]: array([    3,     4,     6, ..., 11262, 11264, 11275])


Counts with RE in any slot fairly close::

    In [38]: np.where(are)[0].shape
    Out[38]: (3724,)

    In [39]: np.where(bre)[0].shape
    Out[39]: (3956,)

Find the histories of single photons::

    In [47]: afl = a.seqhis_ana.af.label

    In [48]: a.seqhis
    Out[48]: A([      511170,         1106,           66, ...,           66,           66, 871019341410], dtype=uint64)

    In [50]: afl(511170)
    Out[50]: 'SI BT BT BT SD'

    In [51]: a.seqhis[are]
    Out[51]: A([     1106,     19538,    288082, ...,      1106, 130860626,     17746], dtype=uint64)

    In [52]: afl(1106)
    Out[52]: 'SI RE AB'

    In [53]: afl(19538)
    Out[53]: 'SI RE BT AB'

    In [54]: afl(288082)
    Out[54]: 'SI RE RE SC AB'






RE
----

::

    In [11]: bre = b.seqhis_ana.seq_any("RE")

    In [12]: np.count_nonzero(bre)
    Out[12]: 0

    In [13]: are = a.seqhis_ana.seq_any("RE")

    In [14]: np.count_nonzero(are)
    Out[14]: 3724



small CK/SI mismatch : BUT should not happen, must be a bug  : G4:-1  -9:CK +9:SI 
-----------------------------------------------------------------------------------------------

* gensteps are in common so the counts of CK and SI much match 

::

    In [15]: ack = a.seqhis_ana.seq_any("CK")

    In [16]: np.count_nonzero(ack)
    Out[16]: 263

    In [1]: a.seqhis_ana.seq_any_count("CK")
    Out[1]: 263                                 ## CORRECT : MATCHES GS

    In [7]: a.seqhis_ana.seq_startswith_count("SI")
    Out[7]: 11015                               ## CORRECT : MATCHES GS



    epsilon:ana blyth$ gs.sh 1 
    [2021-05-25 20:31:30,264] p86263 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 20:31:30,265] p86263 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/1/gs.npy shape (66, 6, 4) 
    [2021-05-25 20:31:30,265] p86263 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 



    In [17]: bck = b.seqhis_ana.seq_any("CK")

    In [18]: np.count_nonzero(bck)
    Out[18]: 254                    ## <<<< G4:-1 : MISSING 9 CK PHOTONS 

    In [2]: b.seqhis_ana.seq_any_count("CK")
    Out[2]: 254


    In [8]: b.seqhis_ana.seq_startswith_count("SI")
    Out[8]: 11024                  ###   HUH :  +9 RELATIVE TO GS

    In [9]: b.seqhis_ana.seq_startswith_count("CK")
    Out[9]: 254                    ###    HUH : -9 RELATIVE TO GS   




    epsilon:ana blyth$ gs.sh -1 
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['-1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/-1/gs.npy shape (66, 6, 4) 
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 








    In [1]: a.seqhis_ana.seq_startswith_count("CK")
    Out[1]: 263

    In [2]: b.seqhis_ana.seq_startswith_count("CK")
    Out[2]: 254

    In [5]: a.seqhis_ana.seq_any_count("SI")
    Out[5]: 11015

    In [6]: 11015+263
    Out[6]: 11278

    In [7]: b.seqhis_ana.seq_startswith_count("SI")
    Out[7]: 11024



    In [8]: a.seqhis_ana.seq_startswith_count("SI")
    Out[8]: 11015

    In [9]: b.seqhis_ana.seq_startswith_count("CK")
    Out[9]: 254

    In [10]: 11024+254
    Out[10]: 11278





UserInfo clash : fixed with dynamic_cast
------------------------------------------

::

    epsilon:offline blyth$ jgr SetUserInformation
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:            aSecondaryTrack->SetUserInformation(new CTrackInfo( opticks_record_id, 'S' ) );
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:      aSecondaryTrack->SetUserInformation(new CTrackInfo( opticks_record_id, 'C' ) );

    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:                (*secondaries)[i]->SetUserInformation(infoNew);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        trk_michael->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:                (*secondaries)[i]->SetUserInformation(infoNew);


::

    (gdb) bt
    #0  0x00007fffedd850ff in void __gnu_cxx::new_allocator<int>::construct<int, int const&>(int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #1  0x00007fffedd83ee8 in std::enable_if<std::allocator_traits<std::allocator<int> >::__construct_helper<int, int const&>::value, void>::type std::allocator_traits<std::allocator<int> >::_S_construct<int, int const&>(std::allocator<int>&, int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #2  0x00007fffedd82021 in decltype (_S_construct({parm#1}, {parm#2}, (forward<int const&>)({parm#3}))) std::allocator_traits<std::allocator<int> >::construct<int, int const&>(std::allocator<int>&, int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #3  0x00007fffedd80c10 in std::vector<int, std::allocator<int> >::push_back(int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #4  0x00007fffc04ae1b8 in NormalTrackInfo::markTracedAncestors (this=0x17911ba30, trkid=10) at /home/blyth/junotop/offline/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:33
    #5  0x00007fffc04ad8f6 in InteresingProcessAnaMgr::saveSecondaryInit (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:537
    #6  0x00007fffc04ad4d8 in InteresingProcessAnaMgr::saveNeutronCapture (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:450
    #7  0x00007fffc04ab299 in InteresingProcessAnaMgr::PreUserTrackingAction (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:162
    #8  0x00007fffc1c29598 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffc1e34440 <MgrOfAnaElem::instance()::s_mgr>, trk=0x17911c770) at ../src/MgrOfAnaElem.cc:60
    #9  0x00007fffc247222c in LSExpTrackingAction::PreUserTrackingAction (this=0x3386ed0, aTrack=0x17911c770) at ../src/LSExpTrackingAction.cc:37
    #10 0x00007fffd17a008e in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #11 0x00007fffd19d7b53 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #12 0x00007fffc26be760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #13 0x00007fffc1c21a3c in DetSimAlg::execute (this=0x250de70) at ../src/DetSimAlg.cc:112


No dynamic_cast::

    521 void
    522 InteresingProcessAnaMgr::saveSecondaryInit(const G4Track* aTrack) {
    523     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    524     if ((not info)) {
    525         return;
    526     }




recollections
---------------

1. need to make G4 do secondaries first for re-emission REJOIN-ing to work
2. G4Track stopAndKill must be used to truncate the G4 simulation in the same way as Opticks bouncemax
3. reem "gensteps" are excluded:: 

     586         if((m_opticksMode & 1) && Num > 0 && !flagReemission)
     587         {
     588 #ifdef WITH_G4OPTICKS
     589             G4Opticks::Get()->collectGenstep_DsG4Scintillation_r3971(
     590                  &aTrack,



Avoided some Geant4 bug with::

    153 void Ctx::setTrackOptical(const G4Track* track)
    154 {
    155     const_cast<G4Track*>(track)->UseGivenVelocity(true);
    156 



G4 OpticksEvent missing gs.npy
----------------------------------

An organizational issue, as gensteps are by definition common to both simulations

::

    epsilon:ana blyth$ find /tmp/blyth/opticks/source/evt/g4live/natural -name gs.npy 
    /tmp/blyth/opticks/source/evt/g4live/natural/1/gs.npy
    /tmp/blyth/opticks/source/evt/g4live/natural/3/gs.npy
    /tmp/blyth/opticks/source/evt/g4live/natural/2/gs.npy
    epsilon:ana blyth$ 




bookending photon generation
---------------------------------

Bookending the photon generation corresponding to each genstep, will 
allow the CRecorder collected photons to be labelled with a genstep 
index so can then see the correspondence between the same single gensteps 
in each simulation without having to restrict running to a single genstep.
This also identifies the gentype. 

Hmm not directly. The geant4 photon generation loop creates secondary tracks 
and collects them into the G4VParticleChange that is returned by eg L4Cerenkov::PostStepDoIt
so in order to match need to plant info into these secondaries.


numPhotons mismatch : a total no-no : clearly a bug 
--------------------------------------------------------

* after adding CTrackInfo instrumentation gentype is now to be trusted
* maybe event mingling problem, are now not getting 1,2 written 


::

    epsilon:offline blyth$ evtbase.sh    ## rsync the events from P 
    from P:/home/blyth/local/opticks/evtbase/source/evt/g4live/natural to /tmp/blyth/opticks/source/evt/g4live/natural    


    epsilon:offline blyth$ evt.sh -1 2>/dev/null        ## seeing around 50% more in G4 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              15833         1.00 
    0000               42        0.497        7875        [2 ] SI AB
    0001           7cccc2        0.133        2099        [6 ] SI BT BT BT BT SD
    0002              462        0.066        1042        [3 ] SI SC AB
    0003          7cccc62        0.058         912        [7 ] SI SC BT BT BT BT SD
    0004           8cccc2        0.056         888        [6 ] SI BT BT BT BT SA
    0005          8cccc62        0.025         398        [7 ] SI SC BT BT BT BT SA
    0006         7cccc662        0.022         346        [8 ] SI SC SC BT BT BT BT SD
    0007             4662        0.020         320        [4 ] SI SC SC AB
    0008               41        0.016         248        [2 ] CK AB
    0009             4cc2        0.013         200        [4 ] SI BT BT AB
    0010         8cccc662        0.008         133        [8 ] SI SC SC BT BT BT BT SA
    0011        7cccc6662        0.008         120        [9 ] SI SC SC SC BT BT BT BT SD
    0012            46662        0.007         104        [5 ] SI SC SC SC AB
    0013          7ccccc2        0.006         100        [7 ] SI BT BT BT BT BT SD
    0014            4cc62        0.006          99        [5 ] SI SC BT BT AB
    0015              4c2        0.005          84        [3 ] SI BT AB
    0016         7ccccc62        0.004          60        [8 ] SI SC BT BT BT BT BT SD
    0017          8ccccc2        0.003          54        [7 ] SI BT BT BT BT BT SA
    0018        8cccc6662        0.003          52        [9 ] SI SC SC SC BT BT BT BT SA
    0019             4c62        0.003          48        [4 ] SI SC BT AB
    .                              15833         1.00 

    In [1]: epsilon:offline blyth$ evt.sh 1 2>/dev/null
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [1]: 





running shakedown
--------------------


tds2 with "--opticks-anamgr" to feed G4OpticksRecorder with G4Run G4Event G4Track G4Step::

    O[blyth@localhost cmt]$ t tds2
    tds2 () 
    { 
        : run with opticks disabled, but with Opticks provided intrumentation used to save info from Geant4 in OpticksEvent format files;
        local opts="--opticks-mode 2 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 --opticks-anamgr";
        tds- $opts gun $*
    }


::

    epsilon:offline blyth$ svn commit -m "pass G4 objects from detsim/G4OpticksAnaMgr to opticks/g4ok/G4OpticksRecorder, so can develop in Opticks repo"
    Sending        Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.cc
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.hh
    Transmitting file data ...done
    Committing transaction...
    Committed revision 4596.




Do not see output from G4OpticksAnaMgr although it is in the AnaMgrList, I recall getting this before

jnu/opticks-junoenv-runtime.rst


::

    BP=LSExpRunAction::BeginOfRunAction tds2


::

     30 void MgrOfAnaElem::BeginOfRunAction(const G4Run* run) {
     31     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     32     {
     33           val->BeginOfRunAction(run);
     34     }
     35 }
     36 void MgrOfAnaElem::EndOfRunAction(const G4Run* run){
     37     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     38     {
     39           val->EndOfRunAction(run);
     40     }
     41 


::

    (gdb) p m_order
    $2 = std::vector of length 10, capacity 16 = {0x250c090, 0x250d9f0, 0x2533030, 0x2aa76c0, 0x2ebc060, 0x300a890, 0x7fffbf507010, 0x2eabe00, 0x29bd680, 0x25337e0}
    (gdb) p m_anamgrs
    $3 = std::map with 10 elements = {["DataModelWriterWithSplit"] = 0x2533030, ["DepositEnergyAnaMgr"] = 0x300a890, ["DepositEnergyTTAnaMgr"] = 0x7fffbf507010, ["G4OpticksAnaMgr"] = 0x250c090, 
      ["GenEvtInfoAnaMgr"] = 0x2ebc060, ["InteresingProcessAnaMgr"] = 0x2eabe00, ["NormalAnaMgr"] = 0x2aa76c0, ["OpticalParameterAnaMgr"] = 0x29bd680, ["RadioAnaMgr"] = 0x250d9f0, 
      ["TimerAnaMgr"] = 0x25337e0}
    (gdb) 


Getting the output now, but not WITH_G4OPTICKS::

    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 


::

    epsilon:~ blyth$ cat $JUNOTOP/ExternalInterface/Externals/OpticksG4OK/cmt/requirements
    package OpticksG4OK

    macro OpticksG4OK_home "" \
              opticks " \`opticks-config --prefix\` "

    macro OpticksG4OK_cppflags "" \
              opticks  " \`opticks-config --cflags G4OK\` -DWITH_G4OPTICKS "

    macro OpticksG4OK_linkopts "" \
              opticks " \`opticks-config --libs G4OK\` " 



Package dependency tree must include OpticksG4OK::

    epsilon:offline blyth$ jgr OpticksG4OK
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:use OpticksG4OK    v* Externals


    epsilon:offline blyth$ jgr DetSimPolicy
    ./Simulation/DetSimV2/SimUtil/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PhysiSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/G4DAEChroma/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CMakeLists.txt:#add_subdirectory(DetSimPolicy)
    ./Simulation/DetSimV2/G4Opticks/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PMTSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimAlg/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/MCParamsSvc/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/GenSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/TopTracker/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CalibUnit/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/Chimney/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimOptions/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CentralDetector/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:package DetSimPolicy
    ./Simulation/DetSimV2/OPSimulator/cmt/requirements:use DetSimPolicy  v* Simulation/DetSimV2
    ./Simulation/DetSimV2/DAE/cmt/requirements:use DetSimPolicy v* Simulation/DetSimV2
    ./Simulation/DetSimV2/G4Svc/cmt/requirements:use DetSimPolicy    v*   Simulation/DetSimV2
    ./Simulation/DetSimV2/AnalysisCode/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    epsilon:offline blyth$ 


    O[blyth@localhost cmt]$ pwd
    /home/blyth/junotop/offline/Simulation/DetSimV2/G4Opticks/cmt
    O[blyth@localhost cmt]$ 

    O[blyth@localhost cmt]$ cmt show macro_value OpticksG4OK_cppflags
    O[blyth@localhost cmt]$ CMTEXTRATAGS=opticks cmt show macro_value OpticksG4OK_cppflags
     -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -DOPTICKS_G4OK -DOPTICKS_CFG4 -DOPTICKS_X4 -DOPTICKS_OKOP -DOPTICKS_OKGEO -DOPTICKS_THRAP -DOPTICKS_GGEO -DOPTICKS_OKCORE -DOPTICKS_NPY -DOPTICKS_OKCONF -DOPTICKS_SYSRAP -DWITH_STTF -DWITH_PLOG -DOPTICKS_BRAP -DWITH_BOOST_ASIO -DOPTICKS_CUDARAP -DOPTICKS_OXRAP -I/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/bin/../include/Geant4 -I/home/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/include -I/home/blyth/local/opticks/include/G4OK -I/home/blyth/local/opticks/include/CFG4 -I/home/blyth/local/opticks/include/ExtG4 -I/home/blyth/local/opticks/include/OKOP -I/home/blyth/local/opticks/include/OpticksGeo -I/home/blyth/local/opticks/include/ThrustRap -I/home/blyth/local/opticks/include/GGeo -I/home/blyth/local/opticks/include/OpticksCore -I/home/blyth/local/opticks/externals/include -I/home/blyth/local/opticks/include/NPY -I/home/blyth/local/opticks/include/OKConf -I/home/blyth/local/opticks/externals/glm/glm -I/home/blyth/local/opticks/include/SysRap -I/home/blyth/local/opticks/include/BoostRap -I/home/blyth/local/opticks/include/CUDARap -I/home/blyth/local/opticks/include/OptiXRap -I/home/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include -I/home/blyth/local/opticks/externals/plog/include -I/home/blyth/local/opticks/externals/include/nljson -I/usr/local/cuda/include -I/home/blyth/local/opticks/externals/OptiX_650/include -std=c++11 -DWITH_G4OPTICKS 
    O[blyth@localhost cmt]$ 






tds3 : duplicate material
----------------------------

CMaterialBridge was assuming that all geant4 materials are in GMaterialLib.  That is no longer
the case, since have moved to carrying only materials that are used by geometry. This 
change from a few months ago was for consistency with GDML exports, and for running from 
GDML exports.


::

    tds3
    ...

    2021-05-24 20:00:38.481 INFO  [339226] [OGeo::convert@302] [ nmm 10
    2021-05-24 20:00:39.749 INFO  [339226] [OGeo::convert@321] ] nmm 10
    2021-05-24 20:00:39.813 ERROR [339226] [cuRANDWrapper::setItems@154] CAUTION : are resizing the launch sequence 
    python: /home/blyth/opticks/cfg4/CMaterialBridge.cc:88: void CMaterialBridge::initMap(): Assertion `m_ixtoname.size() == nmat && "there is probably a duplicated material name"' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6cfaa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6cf21a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffce68fd12 in CMaterialBridge::initMap (this=0x14bf072a0) at /home/blyth/opticks/cfg4/CMaterialBridge.cc:88
    #5  0x00007fffce68f650 in CMaterialBridge::CMaterialBridge (this=0x14bf072a0, mlib=0x155cb820) at /home/blyth/opticks/cfg4/CMaterialBridge.cc:41
    #6  0x00007fffcf2b710e in G4OpticksRecorder::setGeometry (this=0x2537030, ggeo_=0x155cb2b0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:61
    #7  0x00007fffcf2abe76 in G4Opticks::setGeometry (this=0x4e9e6f0, ggeo=0x155cb2b0) at /home/blyth/opticks/g4ok/G4Opticks.cc:674
    #8  0x00007fffcf2ab7f6 in G4Opticks::setGeometry (this=0x4e9e6f0, world=0x33fe7e0) at /home/blyth/opticks/g4ok/G4Opticks.cc:598
    #9  0x00007fffc23c3a5d in LSExpDetectorConstruction_Opticks::Setup (world=0x33fe7e0, sd_=0x35f73d0, opticksMode=3) at ../src/LSExpDetectorConstruction_Opticks.cc:105
    #10 0x00007fffc23b443e in LSExpDetectorConstruction::Construct (this=0x31f7e40) at ../src/LSExpDetectorConstruction.cc:387
    #11 0x00007fffcf505253 in G4RunManager::InitializeGeometry() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #12 0x00007fffcf504fda in G4RunManager::Initialize() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #13 0x00007fffc1b79826 in DetSimAlg::initialize (this=0x25150b0) at ../src/DetSimAlg.cc:80
    #14 0x00007fffef12d5e0 in DleSupervisor::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #15 0x00007fffef13801e in Task::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #16 0x00007fffef141832 in TopTask::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #17 0x00007fffef13d26a in TaskWatchDog::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #18 0x00007fffef137f35 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #19 0x00007fffef6c013e in _object* boost::python::detail::invoke<boost::python::to_python_value<bool const&>, bool (Task::*)(), boost::python::arg_from_python<Task&> >(boost::python::detail::invoke_tag_<false, true>, boost::python::to_python_value<bool const&> const&, bool (Task::*&)(), boost::python::arg_from_python<Task&>&) ()
       from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #20 0x00007fffef6beb32 in boost::python::detail::caller_arity<1u>::impl<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> >::operator()(_object*, _object*) ()
       from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #21 0x00007fffef6bde93 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #22 0x00007fffef3773d1 in boost::python::objects::function::call(_object*, _object*) const () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #23 0x00007fffef377738 in boost::detail::function::void_function_ref_invoker0<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #24 0x00007fffef381023 in boost::python::handle_exception_impl(boost::function0<void>) () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #25 0x00007fffef376013 in function_call () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #26 0x00007ffff7a09c53 in PyObject_Call (func=func@entry=0x702260, arg=arg@entry=0x7fffee1942d0, kw=kw@entry=0x0) at Objects/abstract.c:2544
    #27 0x00007ffff7abfce6 in do_call (nk=<optimized out>, na=<optimized out>, pp_stack=0x7fffffff7180, func=<optimized out>) at Python/ceval.c:4593






bad flag : boundary_status not handled : NRI 
--------------------------------------------------------------------------

* how to avoid the annoying USE_CUSTOM_BOUNDARY compile time switch ???

OpStatus.cc::

     80 std::string OpStatus::OpBoundaryAbbrevString(const G4OpBoundaryProcessStatus status)
     81 {   
     ..
     99         case NoRINDEX:s="NRI";break;



::

    2021-05-24 21:20:32.756 INFO  [11533] [CRecorder::postTrackWriteSteps@422] [
    2021-05-24 21:20:32.756 INFO  [11533] [CRecorder::postTrackWriteSteps@430]  NOT USE_CUSTOM_BOUNDARY 
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 FATAL [11533] [OpStatus::OpPointFlag@365]  boundary flag zero  bst 14
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 0 processName Transportation
    2021-05-24 21:20:32.756 FATAL [11533] [CRecorder::postTrackWriteSteps@497]  num 4 i 3 postFlag zero  prior_boundary_status 2 boundary_status 14 next_boundary_status 0 postStage 2 premat 15 postmat 3
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 WARN  [11533] [CRecorder::WriteStepPoint@670]  boundary_status not handled : NRI
    2021-05-24 21:20:32.756 FATAL [11533] [CPhoton::add@100]  _badflag 0
    python: /home/blyth/opticks/cfg4/CPhoton.cc:103: void CPhoton::add(unsigned int, unsigned int): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6cfaa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6cf21a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffce761ad1 in CPhoton::add (this=0x14bf00668, flag=0, material=3) at /home/blyth/opticks/cfg4/CPhoton.cc:103
    #5  0x00007fffce7632d9 in CWriter::writeStepPoint (this=0x14bf007a0, point=0x179122d30, flag=0, material=3, last=false) at /home/blyth/opticks/cfg4/CWriter.cc:167
    #6  0x00007fffce75aa0a in CRecorder::WriteStepPoint (this=0x14bf00630, point=0x179122d30, flag=0, material=3, boundary_status=NoRINDEX, last=false) at /home/blyth/opticks/cfg4/CRecorder.cc:673
    #7  0x00007fffce75a346 in CRecorder::postTrackWriteSteps (this=0x14bf00630) at /home/blyth/opticks/cfg4/CRecorder.cc:594
    #8  0x00007fffce758900 in CRecorder::postTrack (this=0x14bf00630) at /home/blyth/opticks/cfg4/CRecorder.cc:193
    #9  0x00007fffce78154c in CManager::postTrack (this=0x14bf00830) at /home/blyth/opticks/cfg4/CManager.cc:207
    #10 0x00007fffce7814c0 in CManager::PostUserTrackingAction (this=0x14bf00830, track=0x179157620) at /home/blyth/opticks/cfg4/CManager.cc:189
    #11 0x00007fffcf3647c2 in G4OpticksRecorder::PostUserTrackingAction (this=0x250d6d0, track=0x179157620) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:104
    #12 0x00007fffc28c88de in G4OpticksAnaMgr::PostUserTrackingAction (this=0x250d780, trk=0x179157620) at ../src/G4OpticksAnaMgr.cc:34
    #13 0x00007fffc1c2d700 in MgrOfAnaElem::PostUserTrackingAction (this=0x7fffc1e38440 <MgrOfAnaElem::instance()::s_mgr>, trk=0x179157620) at ../src/MgrOfAnaElem.cc:67
    #14 0x00007fffc2476252 in LSExpTrackingAction::PostUserTrackingAction (this=0x3387090, aTrack=0x179157620) at ../src/LSExpTrackingAction.cc:48
    #15 0x00007fffd17a314d in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so




Quite a few "not done"
-------------------------

::

    2021-05-24 22:19:55.120 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1549 photon CPhoton slot_constrained 4 seqhis                ecc61 seqmat                3fb11 is_flag_done N is_done N action POST_SAVE  i 4 num 4
    2021-05-24 22:19:55.120 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1550 photon CPhoton slot_constrained 3 seqhis                 ecc1 seqmat                 3fb1 is_flag_done N is_done N action POST_SAVE  i 3 num 3
    2021-05-24 22:19:55.121 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1551 photon CPhoton slot_constrained 3 seqhis                 ecc1 seqmat                 3fb1 is_flag_done N is_done N action POST_SAVE  i 3 num 3
    [[ junoSD_PMT_v2_Opticks::EndOfEvent  eventID 0 m_opticksMode 3 numGensteps 66 numPhotons 11278




CManager::EndOfEventAction assert OpticksEvent NULL
-------------------------------------------------------

Looks like the GPU event creation stomps on the g4evt that was created previously.

Rearranged OpticksRun to be more g4/ok symmetric and not do such stomping.




::

    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5073 hitCollection_muon 0 hitCollection_opticks 0
    2021-05-24 21:49:12.372 INFO  [49312] [G4OpticksRecorder::EndOfEventAction@91] 
    2021-05-24 21:49:12.372 INFO  [49312] [CManager::EndOfEventAction@145] 
    2021-05-24 21:49:12.372 INFO  [49312] [CManager::EndOfEventAction@149]  --save 

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffca94e72e in OpticksEvent::setNumPhotons (this=0x0, num_photons=17384, resize_=false) at /home/blyth/opticks/optickscore/OpticksEvent.cc:295
    295	    m_num_photons = num_photons ; 
    (gdb) bt
    #0  0x00007fffca94e72e in OpticksEvent::setNumPhotons (this=0x0, num_photons=17384, resize_=false) at /home/blyth/opticks/optickscore/OpticksEvent.cc:295
    #1  0x00007fffce78114f in CManager::EndOfEventAction (this=0x14bf00830) at /home/blyth/opticks/cfg4/CManager.cc:154
    #2  0x00007fffcf3645e6 in G4OpticksRecorder::EndOfEventAction (this=0x250d6d0, event=0x17910ddd0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:92
    #3  0x00007fffc28c886e in G4OpticksAnaMgr::EndOfEventAction (this=0x250d780, evt=0x17910ddd0) at ../src/G4OpticksAnaMgr.cc:32
    #4  0x00007fffc1c2d430 in MgrOfAnaElem::EndOfEventAction (this=0x7fffc1e38440 <MgrOfAnaElem::instance()::s_mgr>, evt=0x17910ddd0) at ../src/MgrOfAnaElem.cc:53
    #5  0x00007fffc2470e00 in LSExpEventAction::EndOfEventAction (this=0x3385780, evt=0x17910ddd0) at ../src/LSExpEventAction.cc:76
    #6  0x00007fffd19db045 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #7  0x00007fffc26c2760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #8  0x00007fffc1c25a3c in DetSimAlg::execute (this=0x250dd20) at ../src/DetSimAlg.cc:112
    #9  0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so


evt.sh shape mismatch for "so" with g4evt -1
------------------------------------------------




::

    cd ~/opticks/ana
    ./evtbase.sh    # rsync from remote 

    ./ab.sh 
    ./evt.sh 
    ..

    [{tagdir_             :nload.py  :118} INFO     - tagdir_ det g4live typ natural tag -1 layout 2 DEFAULT_DIR_TEMPLATE $OPTICKS_EVENT_BASE/$0/evt/$1/$2/$3 
    [{load_               :nload.py  :276} INFO     -  path /tmp/blyth/opticks/source/evt/g4live/natural/-1/so.npy size 80 
    [{check_shapes        :evt.py    :408} INFO     - stems : ['ox', 'rx', 'ph', 'so', 'ps', 'rs'] 
    [{check_shapes        :evt.py    :414} INFO     - stem ox a.shape (11278, 4, 4) a.oshape (11278, 4, 4)  
    [{check_shapes        :evt.py    :414} INFO     - stem rx a.shape (11278, 10, 2, 4) a.oshape (11278, 10, 2, 4)  
    [{check_shapes        :evt.py    :414} INFO     - stem ph a.shape (11278, 1, 2) a.oshape (11278, 1, 2)  
    [{check_shapes        :evt.py    :414} INFO     - stem so a.shape (0, 4, 4) a.oshape (0, 4, 4)  
    [{check_shapes        :evt.py    :443} CRITICAL - oshape_mismatch : ['so']  file_photons 11278 
    ---------------------------------------------------------------------------
    AssertionError                            Traceback (most recent call last)



CK/SI seem off
-----------------


evt.sh 1::

    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 


evt.sh -1::

    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               41        0.516        5816        [2 ] CK AB
    0001           7cccc1        0.131        1476        [6 ] CK BT BT BT BT SD
    0002              461        0.066         745        [3 ] CK SC AB
    0003           8cccc1        0.056         637        [6 ] CK BT BT BT BT SA
    0004          7cccc61        0.056         635        [7 ] CK SC BT BT BT BT SD
    0005          8cccc61        0.026         288        [7 ] CK SC BT BT BT BT SA
    0006         7cccc661        0.022         247        [8 ] CK SC SC BT BT BT BT SD
    0007             4661        0.021         235        [4 ] CK SC SC AB
    0008             4cc1        0.013         146        [4 ] CK BT BT AB
    0009         8cccc661        0.009          97        [8 ] CK SC SC BT BT BT BT SA
    0010        7cccc6661        0.007          75        [9 ] CK SC SC SC BT BT BT BT SD
    0011            4cc61        0.006          71        [5 ] CK SC BT BT AB
    0012            46661        0.006          70        [5 ] CK SC SC SC AB
    0013          7ccccc1        0.006          68        [7 ] CK BT BT BT BT BT SD
    0014              4c1        0.006          63        [3 ] CK BT AB
    0015          8ccccc1        0.004          42        [7 ] CK BT BT BT BT BT SA
    0016         7ccccc61        0.004          42        [8 ] CK SC BT BT BT BT BT SD
    0017        8cccc6661        0.004          40        [9 ] CK SC SC SC BT BT BT BT SA
    0018             4c61        0.003          35        [4 ] CK SC BT AB
    0019       7cccc66661        0.003          29        [10] CK SC SC SC SC BT BT BT BT SD
    .                              11278         1.00





