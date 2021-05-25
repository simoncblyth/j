juno-opticks-validation
=========================


build tips
--------------


::

    export CMTEXTRATAGS=opticks      ## bash junoenv sets this, but its not a standard pkg 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/G4Opticks/cmt 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PhysiSim/cmt
        ## added trackInfo to S + C 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PMTSim/cmt


    jok-touchbuild- Simulation/DetSimV2/AnalysisCode/cmt 



    jok-touchbuild- Examples/Tutorial/cmt    ## to install the python machinery 
    # jok-g4o


::

    O
    jre
    jok-g4o


    O[blyth@localhost cmt]$ ls -l /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks*
    lrwxrwxrwx. 1 blyth blyth 67 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so -> ../../../Simulation/DetSimV2/G4Opticks/Linux-x86_64/libG4Opticks.so
    -rw-rw-r--. 1 blyth blyth 87 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so.cmtref
    O[blyth@localhost cmt]$ date
    Fri May 21 21:23:38 CST 2021



running tips
--------------

::

     export CG4Ctx=INFO
     export DsG4Scintillation=INFO
     export LocalG4Cerenkov1042=INFO

     tds3


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





