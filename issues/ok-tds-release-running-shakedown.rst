ok-tds-release-running-shakedown
==================================

::

    N
    jre
    ok-tds   



Issue 1 : improve spath.h handling of DefaultOutputDir, switch to OPTICKS_SCRIPT 
----------------------------------------------------------------------------------

::

    N[blyth@localhost junosw]$ l /tmp/blyth/opticks/GEOM/python3.9/ALLVERSION/p001/
    total 125096
        4 -rw-rw-r--. 1 blyth blyth      143 Nov 13 15:55 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Nov 13 15:55 sframe.npy
        4 -rw-rw-r--. 1 blyth blyth      856 Nov 13 15:55 NPFold_meta.txt
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 13 15:55 inphoton.npy
        4 -rw-rw-r--. 1 blyth blyth       57 Nov 13 15:55 domain_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      256 Nov 13 15:55 domain.npy
       60 -rw-rw-r--. 1 blyth blyth    59328 Nov 13 15:55 hit.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 13 15:55 photon.npy
        4 -rw-rw-r--. 1 blyth blyth      224 Nov 13 15:55 genstep.npy
        4 -rw-rw-r--. 1 blyth blyth       55 Nov 13 15:55 NPFold_index.txt
        0 drwxr-xr-x. 4 blyth blyth       65 Nov 13 10:32 ..


HMM: should GEOM be automated from junosw prespective ? 

* thats not possible until after no longer need envvar kludges 
  although can manually use the release name within the GEOM

::

    N[blyth@localhost opticks]$ l /data/blyth/opticks/GEOM/UNRESOLVED_TOKEN_GEOM/ok-tds/ALLVERSION/n001/
    total 180092
        0 drwxr-xr-x. 2 blyth blyth      252 Nov 14 15:23 .
        4 -rw-rw-r--. 1 blyth blyth      144 Nov 14 15:23 gs.npy
        4 -rw-rw-r--. 1 blyth blyth      143 Nov 14 15:23 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Nov 14 15:23 sframe.npy
    15628 -rw-rw-r--. 1 blyth blyth 16000128 Nov 14 15:23 pho.npy
    15628 -rw-rw-r--. 1 blyth blyth 16000128 Nov 14 15:23 pho0.npy
        4 -rw-rw-r--. 1 blyth blyth      639 Nov 14 15:23 NPFold_meta.txt
        4 -rw-rw-r--. 1 blyth blyth       57 Nov 14 15:23 domain_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      256 Nov 14 15:23 domain.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 14 15:23 inphoton.npy
    23796 -rw-rw-r--. 1 blyth blyth 24366464 Nov 14 15:23 hit.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 14 15:23 photon.npy
        0 drwxr-xr-x. 4 blyth blyth       30 Nov 14 15:23 ..
        4 -rw-rw-r--. 1 blyth blyth      224 Nov 14 15:23 genstep.npy
        4 -rw-rw-r--. 1 blyth blyth       55 Nov 14 15:23 NPFold_index.txt
    N[blyth@localhost opticks]$ 


With spath.h need to explicitly create the output dirs
---------------------------------------------------------

::

    2023-11-14 15:41:23.394 INFO  [61679] [G4CXOpticks::saveGeometry@536] [ /home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0
    2023-11-14 15:41:23.403 INFO  [61679] [U4GDML::write@187]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    Traceback (most recent call last):
      File "/home/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 21, in <module>
        juno_application.run()
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 184, in run
        self.toptask.run()
    RuntimeError: unidentifiable C++ exception



Shared QCurandStates : generalized spath.h in spath::_ResolvePathGeneralized 
-------------------------------------------------------------------------------

Making it sensitive to envvar allows config of a shared location, eg on /cvmfs/opticks.ihep.ac.cn::

    ${OPTICKS_RNGDir:-$HOME/.opticks/rngcache/RNG}


Shared InputPhotons ?
------------------------


::

    epsilon:opticks blyth$ opticks-f /InputPhotons
    ./ana/input_photons.sh:into the directory ~/.opticks/InputPhotons::
    ./ana/input_photons.sh:ls -alst ~/.opticks/InputPhotons
    ./ana/input_photons.py:    DEFAULT_BASE = os.path.expanduser("~/.opticks/InputPhotons")
    ./bin/OPTICKS_INPUT_PHOTON_.sh:        abspath=$HOME/.opticks/InputPhotons/$path
    ./sysrap/tests/storch_test.sh:odir=$HOME/.opticks/InputPhotons/storch
    ./sysrap/tests/stranTest.cc:     const char* path = SPath::Resolve("$HOME/.opticks/InputPhotons" , name, NOOP ); 
    ./sysrap/SEvt.cc:const char* SEvt::INPUT_PHOTON_DIR = ssys::getenvvar("SEvt__INPUT_PHOTON_DIR", "$HOME/.opticks/InputPhotons") ; 
    ./sysrap/SEvt.cc:   of $HOME/.opticks/InputPhotons. 


    ./g4ok/tests/G4OKTest.sh:path=$HOME/.opticks/InputPhotons/$name.npy
    ./npy/tests/NPY7Test.cc:   NPY<float>* ip = NPY<float>::load("$HOME/.opticks/InputPhotons/InwardsCubeCorners1.npy"); 
    epsilon:opticks blyth$ 




DONE : jok-tds config debug SEvt and compare them : 100k input photons give chi2 match
-----------------------------------------------------------------------------------------

FIXED : Special surface flag zeros giving spaces in histories : was missing WITH_CUSTOM4 at qsim.h level
-----------------------------------------------------------------------------------------------------------

* :doc:`jok-tds-flag-zeros-at-PMT-special-surface-from-missing-WITH_CUSTOM4`

FIXED : Thrust warning : unexpected as should be using c++17 
--------------------------------------------------------------

* CUDA flags were set in CSGOptiX when should be using the common ones


TODO : setup source build environment on L : check jok-tds on GPU cluster
----------------------------------------------------------------------------

WIP : Generalize : ~/j/.junosw_build_config so it can work on both N and L 

FIXED : Missing data, using symbolic link to cvmfs::

    junotoptask:PMTSimParamSvc.helper_pmt_mpt ERROR: empty material property: PMTProperty.NNVTMCP_HiQE.ARC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /hpcfs/juno/junogpu/blyth/junotop/data/Simulation/DetSim
    junotoptask:PMTSimParamSvc.helper_pmt_mpt ERROR: empty material property: PMTProperty.NNVTMCP_HiQE.PHC_RINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /hpcfs/juno/junogpu/blyth/junotop/data/Simulation/DetSim
    junotoptask:PMTSimParamSvc.helper_pmt_mpt ERROR: empty material property: PMTProperty.NNVTMCP_HiQE.PHC_KINDEX
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /hpcfs/juno/junogpu/blyth/junotop/data/Simulation/DetSim

FIXED::

    90/201 Test  #90: SysRapTest.SEvtTest ......................................Subprocess aborted***Exception:   0.05 sec 
        terminate called after throwing an instance of 'std::logic_error'
         what():  basic_string::_M_construct null not valid


try deleting sample_detsim_user.root before running::

     64  solids 139
     65  enable_osur YES
     66  enable_isur YES
     67 
     68 Traceback (most recent call last):
     69   File "/hpcfs/juno/junogpu/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 21, in <module>
     70     juno_application.run()
     71   File "/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 184, in run
     72     self.toptask.run()
     73 RuntimeError: unidentifiable C++ exception
     74 Warning in <TFile::Write>: file sample_detsim_user.root not opened in write mode
     75 ls: cannot access /tmp/.mount_pythono6Fv4b: Permission denied
     76 ls: cannot access /tmp/.mount_pythonYjEt8x: Permission denied
     77 ls: cannot access /tmp/.mount_pythonBG2S0T: Permission denied

same again::

    Traceback (most recent call last):
      File "/hpcfs/juno/junogpu/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 21, in <module>
        juno_application.run()
      File "/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 184, in run 
        self.toptask.run()
    RuntimeError: unidentifiable C++ exception
    Warning in <TFile::Write>: file sample_detsim_user.root not opened in write mode
    ls: cannot access /tmp/.mount_pythonmwWOp0: Permission denied



Running on N, does not have the exception::

      45608 sid    32396
      45609 sid    32397
      45610 sid    32398
      45611 sid    32399
    ]]stree::postcreate
    2023-11-16 09:37:57.555 INFO  [323477] [G4CXOpticks::setGeometry@254] CSGOptiX::Desc Version 7 PTXNAME CSGOptiX7 GEO_PTXNAME - WITH_CUSTOM4 
    2023-11-16 09:37:57.555 INFO  [323477] [G4CXOpticks::SaveGeometry@581]  save to dir /home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0 configured via envvar G4CXOpticks__SaveGeometry_DIR
    2023-11-16 09:37:57.555 INFO  [323477] [G4CXOpticks::saveGeometry@538] [ /home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    2023-11-16 09:37:57.563 INFO  [323477] [U4GDML::write@188]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    G4GDML: Writing '/home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml' done !
    2023-11-16 09:38:00.834 INFO  [323477] [U4GDML::write@199]  Apply GDXML::Fix  rawpath /home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml dstpath /home/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin.gdml
    2023-11-16 09:38:01.466 INFO  [323477] [LSExpDetectorConstruction_Opticks::Setup@54] ] WITH_G4CXOPTICKS 
    /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5
    @@@ G4ParticleHPInelastic instantiated for particle neutron data directory variable is G4NEUTRONHPDATA pointing to /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5/Inelastic
    @@@ G4ParticleHPInelasticData instantiated for particle neutron data directory variable is G4NEUTRONHPDATA pointing to /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Geant4/10.04.p02.juno/share/Geant4-10.4.2/data/G4NDL4.5
    NeutronHP: /Capture file for Z = 6, A = 12 is not found and NeutronHP will use /cvmfs/juno.ihep.ac.cn/cen



L::

    2023-11-16 09:22:32.455 INFO  [91890] [G4CXOpticks::SaveGeometry@581]  save to dir /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0 configured via envvar G4CXOpticks__SaveGeometry_DIR
    2023-11-16 09:22:32.455 INFO  [91890] [G4CXOpticks::saveGeometry@538] [ /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    G4CXOpticks::saveGeometry [ /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    2023-11-16 09:22:32.460 INFO  [91890] [U4GDML::write@187]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    Namespace(help_more=False, loglevel='Info', evtmax=1,


::

    533 void G4CXOpticks::saveGeometry(const char* dir_) const
    534 {
    535     LOG(LEVEL) << " dir_ " << dir_ ;
    536     const char* dir = spath::Resolve(dir_);
    537     LOG(LEVEL) << "[ " << ( dir ? dir : "-" ) ;
    538     LOG(info)  << "[ " << ( dir ? dir : "-" ) ;
    539     std::cout << "G4CXOpticks::saveGeometry [ " << ( dir ? dir : "-" ) << std::endl ;
    540 
    541     if(wd) U4GDML::Write(wd, dir, "origin.gdml" );  // world 
    542     if(fd) fd->save(dir) ;
    543     //if(cx) cx->save(dir);  // debug serialization of OptixInstance that was never used 
    544 
    545     LOG(LEVEL) << "] " << ( dir ? dir : "-" ) ;
    546 }

Issue on L looks to be with U4GDML::Write.


Could be simply creation of the GEOM directory::

    L7[blyth@lxslc708 okjob]$ l /hpcfs/juno/junogpu/blyth/.opticks/GEOM/
    total 24
    4 drwxr-xr-x 5 blyth dyw 4096 Nov 15 21:44 .
    4 drwxr-xr-x 8 blyth dyw 4096 Nov  8 22:06 ..
    4 drwxr-xr-x 3 blyth dyw 4096 Nov  8 22:06 RaindropRockAirWater
    4 drwxr-xr-x 4 blyth dyw 4096 Nov  8 22:06 V1J011
    4 drwxr-xr-x 4 blyth dyw 4096 Nov  8 22:06 FewPMT
    4 -rw-r--r-- 1 blyth dyw  726 Nov  8 16:15 GEOM.sh
    L7[blyth@lxslc708 okjob]$ 


HUH : a clean build and it works::

    ]]stree::postcreate
    2023-11-16 10:48:45.878 INFO  [46210] [G4CXOpticks::setGeometry@254] CSGOptiX::Desc Version 7 PTXNAME CSGOptiX7 GEO_PTXNAME - WITH_CUSTOM4 
    2023-11-16 10:48:45.880 INFO  [46210] [G4CXOpticks::SaveGeometry@581]  save to dir /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0 configured via envvar G4CXOpticks__SaveGeometry_DIR
    2023-11-16 10:48:45.880 INFO  [46210] [G4CXOpticks::saveGeometry@538] [ /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    G4CXOpticks::saveGeometry [ /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0
    2023-11-16 10:48:45.885 INFO  [46210] [U4GDML::write@188]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    2023-11-16 10:48:45.885 INFO  [46210] [U4GDML::write_@211] [
    [U4GDML::write_
    .U4GDML::write_ path /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml exists NO 
    2023-11-16 10:48:45.885 INFO  [46210] [U4GDML::write_@227]  path /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml exists NO  rc 0
    .U4GDML::write_ path /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml exists NO  rc 0
    G4GDML: Writing '/hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    G4GDML: Writing '/hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml' done !
    2023-11-16 10:48:47.933 INFO  [46210] [U4GDML::write_@244] ]
    ]U4GDML::write_
    2023-11-16 10:48:47.933 INFO  [46210] [U4GDML::write@198] [ Apply GDXML::Fix  rawpath /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml dstpath /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin.gdml
    2023-11-16 10:48:49.489 INFO  [46210] [U4GDML::write@200] ] Apply GDXML::Fix  rawpath /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin_raw.gdml dstpath /hpcfs/juno/junogpu/blyth/.opticks/GEOM/J23_1_0_rc3_ok0/origin.gdml
    2023-11-16 10:48:50.925 INFO  [46210] [LSExpDetectorConstruction_Opticks::Setup@54] ] WITH_G4CXOPTICKS 



setInputPhoton crash at eventID 1 (eventID 0 ok)
---------------------------------------------------

L::

    067 
     68 GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists(0) Y SEvt::Exists(1) Y
     69  SEvt::Get(0)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     70  SEvt::Get(1)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     71  m_input_photon (10000, 4, 4, )
     72 GtOpticksTool::mutate event_number 0 numPhotons 10000
     73 junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
     74 junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES
     75 GtOpticksTool::mutate event_number 1 numPhotons -616276272
     76 junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 1 LEVEL 5:DEBUG
     77 junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 1 opticksMode 3 with m_jpmt_dbg YES
     78  *** Break *** segmentation violation
     79 

    204 ===========================================================
    205 #7  0x00002b793f930b11 in NP::has_shape (this=0x225594f0, ni=-1, nj=4, nk=4, nl=-1, nm=-1, no=-1) at /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/optic    ks/head/include/SysRap/NP.hh:1083
    206 #8  0x00002b793f950351 in QEvent::setInputPhoton (this=0x1d53fdb0) at /hpcfs/juno/junogpu/blyth/junotop/opticks/qudarap/QEvent.cc:284
    207 #9  0x00002b793f94ff21 in QEvent::setGenstep (this=0x1d53fdb0, gs_=0x196adbd0) at /hpcfs/juno/junogpu/blyth/junotop/opticks/qudarap/QEvent.cc:231
    208 #10 0x00002b793f94f971 in QEvent::setGenstep (this=0x1d53fdb0) at /hpcfs/juno/junogpu/blyth/junotop/opticks/qudarap/QEvent.cc:165
    209 #11 0x00002b793f92354a in QSim::simulate (this=0x1d565e20, eventID=1) at /hpcfs/juno/junogpu/blyth/junotop/opticks/qudarap/QSim.cc:356
    210 #12 0x00002b793f2cd898 in G4CXOpticks::simulate (this=0xb4bbf70, eventID=1) at /hpcfs/juno/junogpu/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:459
    211 #13 0x00002b79408d5428 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x9b2db70, eventID=1) at /hpcfs/juno/junogpu/blyth/junotop/junosw/Simulation/D    etSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:239
    212 #14 0x00002b79408d4fba in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x9b2db70, eventID=1) at /hpcfs/juno/junogpu/blyth/junotop/junosw/Simulation/DetSimV2/P    MTSim/src/junoSD_PMT_v2_Opticks.cc:166
    213 #15 0x00002b79408c8917 in junoSD_PMT_v2::EndOfEvent (this=0x9b2faa0, HCE=0xd55055f0) at /hpcfs/juno/junogpu/blyth/junotop/junosw/Simulation/DetSimV2/PMTS    im/src/junoSD_PMT_v2.cc:1142


Debug is easier on N, so try to reproduce there.::

   N[blyth@localhost ~]$ GDB=1 ./j/okjob.sh  

Looks like input photon garbled at 2nd event, was it cleared::

    gdb) p input_photon->shape[0]
    $5 = (__gnu_cxx::__alloc_traits<std::allocator<int>, int>::value_type &) @0x7fffffff0054: 0
    (gdb) p input_photon->shape[1]
    $6 = (__gnu_cxx::__alloc_traits<std::allocator<int>, int>::value_type &) @0x7fffffff0058: 0
    (gdb) p input_photon->shape[2]
    $7 = (__gnu_cxx::__alloc_traits<std::allocator<int>, int>::value_type &) @0x7fffffff005c: 0
    (gdb) p input_photon->shape.size()
    $8 = 18446708889461540615
    (gdb) 




TODO : put download cache on /cvmfs so only have one to look after
-----------------------------------------------------------------------


