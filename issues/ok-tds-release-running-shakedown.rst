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



FIXED : setInputPhoton crash at eventID 1 (eventID 0 ok)
----------------------------------------------------------

* fixed by developing qudarap/tests/QEvent_Lifecycle_Test.cc and rationalizing 
  input photon handling 

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




WIP : change stderr to stdout for slurm : junosw remains
-----------------------------------------------------------

Changed the optickd std::cerr writing, what remains is from junosw including tut_detsim.py 
logging.::

    [2023-11-17 13:51:16,911] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:106} INFO - end of init_yaml_conf
    [2023-11-17 13:51:16,913] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:59} INFO - end of __init__
    [2023-11-17 13:51:16,913] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:70} INFO - end of register
    [2023-11-17 13:51:16,913] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py:20} INFO - after juno_application.register(detsim_module) 
    [2023-11-17 13:51:16,913] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:130} INFO - [JUNOApplication.run
    [2023-11-17 13:51:18,734] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1627} INFO - setup_generator_opticks : objName:[ok]
    [2023-11-17 13:51:19,200] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1748} INFO - PMTName PMTMask --pmt20inch-name 
    [2023-11-17 13:51:19,200] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1749} INFO - LPMTExtra TWO-mask --pmt20inch-extra 
    [2023-11-17 13:51:19,200] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1992} INFO - init_SWITCH_envvars : parsing 36 SWITCH lines
    [2023-11-17 13:51:19,200] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:2004} INFO - init_SWITCH_envvars : setting key JUNO_ADDITIONACRYLIC_SIMPLIFY_CSG from args.additionacrylic_simplify_csg  
    [2023-11-17 13:51:19,200] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:2004} INFO - init_SWITCH_envvars : setting key JUNO_DEBUG_DISABLE_XJ from args.debug_disable_xj  
    [2023-11-17 13:51:19,201] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:2004} INFO - init_SWITCH_envvars : setting key JUNO_DEBUG_DISABLE_SJ from args.debug_disable_sj  
    [2023-11-17 13:51:19,201] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:2004} INFO - init_SWITCH_envvars : setting key JUNO_DEBUG_DISABLE_FA from args.debug_disable_fa  
    [2023-11-17 13:51:19,201] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1825} INFO - TWO-mask . args.pmt20inch_extra TWO-mask 
    [2023-11-17 13:51:19,201] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1901} INFO - end of init_detsim_optical
    [2023-11-17 13:51:19,202] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1701} INFO - end of init_detector_simulation
    [2023-11-17 13:51:19,202] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:162} INFO - end of init
    [2023-11-17 13:51:19,210] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:181} INFO - JUNOApplication.run --no-toptask-show skipping toptask.show
    [2023-11-17 13:51:19,211] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:183} INFO - JUNOApplication.run toptask.run
    Tub3inchPMTV3Manager::helper_make_solid Tub3inchPMTV3Manager::desc 
    Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM : 1.000000e-01
     VIRTUAL_DELTA_MM_DEFAULT*mm : 1.000000e-03
     VIRTUAL_DELTA_MM*mm : 1.000000e-01
     mm : 1.000000e+00

    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists(0) Y SEvt::Exists(1) Y
     SEvt::Get(0)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     SEvt::Get(1)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )
    GtOpticksTool::mutate event_number 0 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 1 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 1 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 1 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 2 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 2 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 2 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 3 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 3 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 3 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 4 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 4 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 4 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 5 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 5 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 5 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 6 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 6 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 6 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 7 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 7 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 7 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 8 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 8 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 8 opticksMode 3 with m_jpmt_dbg YES 
    GtOpticksTool::mutate event_number 9 numPhotons 10000
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 9 LEVEL 5:DEBUG
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 9 opticksMode 3 with m_jpmt_dbg YES 
    [2023-11-17 13:54:27,686] p177454 {/hpcfs/juno/junogpu/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:185} INFO - ]JUNOApplication.run




Why the size difference ? A is 20MB less than B : aux.npy mostly 
-------------------------------------------------------------------

::

    epsilon:ALL0 blyth$ du -hs * 

     34M	p001
     34M	p002
     34M	p003
     34M	p004
     34M	p005
     34M	p006
     34M	p007
     34M	p008
     34M	p009
     34M	p010

     55M	n001
     55M	n002
     55M	n003
     55M	n004
     55M	n005
     55M	n006
     55M	n007
     55M	n008
     55M	n009
     55M	n010

    4.0K	run.npy
    4.0K	run_meta.txt
    epsilon:ALL0 blyth$ 

20 MB extra on B side, mostly from aux.npy::

    epsilon:jtds blyth$ cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p001 
    epsilon:p001 blyth$ du -hs *
    4.0K	NPFold_index.txt
    4.0K	NPFold_meta.txt
    4.0K	domain.npy
    4.0K	domain_meta.txt
    2.4M	flat.npy
    4.0K	genstep.npy
    240K	hit.npy
    628K	inphoton.npy
    628K	photon.npy
    9.8M	prd.npy
     20M	record.npy
    4.0K	record_meta.txt
    316K	seq.npy
    4.0K	sframe.npy
    4.0K	sframe_meta.txt
    316K	tag.npy

    epsilon:p001 blyth$ cd /hpcfs/juno/junogpu/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/n001
    epsilon:n001 blyth$ du -hs *
    4.0K	NPFold_index.txt
    4.0K	NPFold_meta.txt
    4.0K	domain.npy
    4.0K	domain_meta.txt
    2.4M	flat.npy
    4.0K	genstep.npy
    248K	hit.npy
    628K	inphoton.npy
    628K	photon.npy
    9.8M	prd.npy
     20M	record.npy
    4.0K	record_meta.txt
    316K	seq.npy
    4.0K	sframe.npy
    4.0K	sframe_meta.txt
    316K	tag.npy

    ## 20M	aux.npy
    ## 4.0K	gs.npy
    ## 160K	pho.npy
    ## 160K	pho0.npy
    ## 940K	sup.npy



FIXED : U4Recorder/SEvt/NPFold managing to yield duplicate hit.npy keys, revealed which implementing nodata mode for fast metadata access
------------------------------------------------------------------------------------------------------------------------------------------


::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 1 LEVEL 5:DEBUG
    2023-11-17 18:57:20.402 INFO  [299890] [U4Recorder::BeginOfEventAction@284]  eventID 1
    Begin of Event --> 1
    2023-11-17 18:57:20.404 INFO  [299890] [SEvt::hostside_running_resize_@1820] resizing photon 0 to evt.num_photon 10000
    2023-11-17 18:57:21.311 INFO  [299890] [U4Recorder::PreUserTrackingAction_Optical@374]  modulo 100000 : ulabel.id 0
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 1 opticksMode 3 with m_jpmt_dbg YES
    2023-11-17 18:57:21.423 INFO  [299890] [SEvt::save@3349]  dir /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p002 index 2 instance 0 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 3 hitCollection 3518 hcMuon 0 hcOpticks 3812 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    2023-11-17 18:57:21.502 INFO  [299890] [U4Recorder::MakeMetaArray@672] U4Recorder::DescFakes  
    U4Recorder::FAKES_SKIP NO 
    U4Recorder::FAKES      YES
    FAKES.size             0

    NPFold::add_ FATAL : have_key_already hit.npy
    python: /data/blyth/junotop/opticks/sysrap/NPFold.h:754: void NPFold::add_(const char*, const NP*): Assertion `!have_key_already' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff6b34387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6b35a78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6b2d1a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6b2d252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffc7e8efbf in NPFold::add_ (this=0x5e19ef0, k=0x7ffffffeb4b0 "hit.npy", a=0xd838eee0) at /data/blyth/junotop/opticks/sysrap/NPFold.h:754
    #5  0x00007fffc7e8eeac in NPFold::add (this=0x5e19ef0, k=0x7fffc7fbf0b9 "hit", a=0xd838eee0) at /data/blyth/junotop/opticks/sysrap/NPFold.h:740
    #6  0x00007fffc7ebf58c in SEvt::gather_components (this=0x5e19680) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2922
    #7  0x00007fffc7ebfc47 in SEvt::gather (this=0x5e19680) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2983
    #8  0x00007fffc7ec10b7 in SEvt::save (this=0x5e19680, dir_=0x7fffc7fbb65a "$DefaultOutputDir") at /data/blyth/junotop/opticks/sysrap/SEvt.cc:3336
    #9  0x00007fffc7ebfd14 in SEvt::save (this=0x5e19680) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:3064
    #10 0x00007fffc7eb767e in SEvt::endOfEvent (this=0x5e19680, eventID=1) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1271
    #11 0x00007fffc8c5ad88 in U4Recorder::EndOfEventAction (this=0x5df08f0, event=0xd3f5b370) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:307
    #12 0x00007fffc7c29e94 in U4RecorderAnaMgr::EndOfEventAction (this=0x5e193b0, evt=0xd3f5b370)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:32
    #13 0x00007fffc7540c38 in MgrOfAnaElem::EndOfEventAction (this=0x7fffc754f8c0 <MgrOfAnaElem::instance()::s_mgr>, evt=0xd3f5b370)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53
    #14 0x00007fffc7d5aefd in LSExpEventAction::EndOfEventAction (this=0x8b400c0, evt=0xd3f5b370)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpEventAction.cc:76
    #15 0x00007fffcf355242 in G4EventManager::DoProcessing(G4Event*) ()



Big difference between U4Recorder and QEvent is the QEvent::setGenstep which calls SEvt::clear 
just before the launch. 


TODO : get PRODUCTION macro to work 
-------------------------------------

Before doing that switch off debug


Profile shake
---------------

::

    PICK:CF
    A:ProfileWithinEvent stampFmt:2023-11-20T16:53:25.315104  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:0:NVIDIA_TITAN_V prefix://p creator:jok-tds
    A.t
    array([[    0,   115, 35662],
           [    0,   104, 14592],
           [    0,   105, 14456],
           [    0,    95, 14453],
           [    0,   122, 15026],
           [    0,    89, 14522],
           [    0,   101, 14493],
           [    0,    99, 14453],
           [    0,    98, 14682],
           [    0,   112, 14473]])
    B:ProfileWithinEvent stampFmt:2023-11-20T16:53:07.719859  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    B.t
    array([[      0,    1651, 1153925],
           [      0,     109, 1102947],
           [      0,     204, 1182319],
           [      0,     199, 1101756],
           [      0,     123, 1316343],
           [      0,      94, 1122567],
           [      0,      98, 1095478],
           [      0,      99, 1337383],
           [      0,     124, 1333284],
           [      0,     149, 1072843]])
    Profile.ABPlot
    A:ProfileWithinEvent stampFmt:2023-11-20T16:53:25.315104  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:0:NVIDIA_TITAN_V prefix://p creator:jok-tds
    B:ProfileWithinEvent stampFmt:2023-11-20T16:53:07.719859  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    BOA : 32.4 75.6 81.8 76.2 87.6 77.3 75.6 92.5 90.8 74.1   avg(BOA[1:]) 81.3  




TITAN V
---------

::

    PYTHONPATH=$HOME MODE=0 ~/np/tests/NPFold_profile_test.sh run_ana


    PICK:CF
    A:ProfileWithinEvent stampFmt:2023-11-20T16:53:25.315104  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:0:NVIDIA_TITAN_V prefix://p creator:jok-tds
    A.t
    array([[    0,   115, 35662],
           [    0,   104, 14592],
           [    0,   105, 14456],
           [    0,    95, 14453],
           [    0,   122, 15026],
           [    0,    89, 14522],
           [    0,   101, 14493],
           [    0,    99, 14453],
           [    0,    98, 14682],
           [    0,   112, 14473]])
    B:ProfileWithinEvent stampFmt:2023-11-20T16:53:07.719859  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    B.t
    array([[      0,    1651, 1153925],
           [      0,     109, 1102947],
           [      0,     204, 1182319],
           [      0,     199, 1101756],
           [      0,     123, 1316343],
           [      0,      94, 1122567],
           [      0,      98, 1095478],
           [      0,      99, 1337383],
           [      0,     124, 1333284],
           [      0,     149, 1072843]])
    Profile.ABPlot
    A:ProfileWithinEvent stampFmt:2023-11-20T16:53:25.315104  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:0:NVIDIA_TITAN_V prefix://p creator:jok-tds
    B:ProfileWithinEvent stampFmt:2023-11-20T16:53:07.719859  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    BOA : 32.4 75.6 81.8 76.2 87.6 77.3 75.6 92.5 90.8 74.1   avg(BOA[1:]) 81.3  



PYTHONPATH=$HOME MODE=0 ~/np/tests/NPFold_stamps_test.sh run_ana::

    MODE:2
    A:Stamps stampFmt:2023-11-19T20:24:20.917690  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:0:NVIDIA_TITAN_V 1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
              tBOE   tsG0   tsG1   tsG2   tsG3   tsG4   tsG5   tsG6   tsG7   tsG8   tPrL   tPoL   tEOE 
    array([[    0,    60,    74,    84,    85,    86,   166,   193,   376,  2364,  2364, 14550, 14614],
           [    0,    58,    73,    84,    85,    86,   123,   148,   314,  2225,  2225, 14412, 14470],
           [    0,    60,    81,    91,    91,   108,   146,   168,   334,  2314,  2315, 14505, 14569],
           [    0,    64,    79,    90,    91,    92,   169,   207,   503,  2616,  2617, 14843, 14910],
           [    0,    59,    73,    83,    84,    85,   122,   144,   310,  2265,  2265, 14438, 14498],
           [    0,    60,    75,    86,    86,    87,   125,   146,   310,  2274,  2275, 14452, 14512],
           [    0,    58,    72,    82,    82,    83,   122,   144,   308,  2231,  2231, 14643, 14703],
           [    0,    59,    73,    84,    84,    85,   123,   144,   311,  2248,  2248, 14410, 14470],
           [    0,    60,    75,    87,    87,    89,   124,   146,   311,  2259,  2259, 14423, 14483]])

    B:Stamps stampFmt:2023-11-19T20:24:03.859933  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
              tBOE   tEOE 
    array([[      0, 1101852],
           [      0, 1064596],
           [      0, 1049256],
           [      0, 1073432],
           [      0, 1053079],
           [      0, 1045362],
           [      0, 1062443],
           [      0, 1059465],
           [      0, 1051069]])




Switch to TITAN RTX
---------------------

::

    N[blyth@localhost j]$ PYTHONPATH=$HOME MODE=0 ~/np/tests/NPFold_profile_test.sh run_ana
    /home/blyth/tmp/NPFold_profile_test.build/NPFold_profile_test
    NPFold::Load("@/data/blyth/opticks/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0")
    NPFold::subprofile_ab created and saved subprofile symmary NPFold to $FOLD 
    Python 3.7.7 (default, May  7 2020, 21:25:33) 
    Type 'copyright', 'credits' or 'license' for more information
    IPython 7.18.1 -- An enhanced Interactive Python. Type '?' for help.
    ab

    CMDLINE:/home/blyth/np/tests/NPFold_profile_test.py
    ab.base:/home/blyth/tmp/NPFold_profile_test

      : ab.NPFold_index                                    :                 (2,) : 0:00:00.524550 
      : ab.a                                               :                 None : 1:13:43.927552 
      : ab.b                                               :                 None : 1:13:43.926552 

     min_stamp : 2023-11-20 16:02:26.964313 
     max_stamp : 2023-11-20 17:16:10.367315 
     dif_stamp : 1:13:43.403002 
     age_stamp : 0:00:00.524550 
    PICK:CF
    A:ProfileWithinEvent stampFmt:2023-11-20T17:10:36.521941  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
    A.t
    array([[    0,   110, 42045],
           [    0,   103,  9778],
           [    0,   106,  9371],
           [    0,   111,  9308],
           [    0,   100,  9304],
           [    0,    99,  9367],
           [    0,   114,  9410],
           [    0,    99,  9417],
           [    0,   103,  9619],
           [    0,    96,  9356]])
    B:ProfileWithinEvent stampFmt:2023-11-20T17:10:18.913541  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    B.t
    array([[      0,     132, 1161460],
           [      0,     959, 1062014],
           [      0,     157, 1108391],
           [      0,     163, 1044401],
           [      0,     830, 1070616],
           [      0,     104, 1094539],
           [      0,      95, 1064913],
           [      0,      96, 1115427],
           [      0,     807, 1263878],
           [      0,     102, 1095688]])
    Profile.ABPlot
    A:ProfileWithinEvent stampFmt:2023-11-20T17:10:36.521941  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
    B:ProfileWithinEvent stampFmt:2023-11-20T17:10:18.913541  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    BOA : 27.6 108.6 118.3 112.2 115.1 116.9 113.2 118.4 131.4 117.1   avg(BOA[1:]) 116.8  



::


    PICK:CF
    A:ProfileWithinEvent stampFmt:2023-11-20T20:10:17.034371  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
    A.t
    array([[    0,   107, 26143],
           [    0,   119,  8865],
           [    0,   109,  8667],
           [    0,   104,  8665],
           [    0,   104,  8668],
           [    0,   113,  8675],
           [    0,   113,  8635],
           [    0,   108,  8603],
           [    0,   136,  8895],
           [    0,   111,  9078]])
    B:ProfileWithinEvent stampFmt:2023-11-20T20:09:59.710368  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    B.t
    array([[     0,    140, 953060],
           [     0,     74, 929931],
           [     0,    169, 896197],
           [     0,     72, 883669],
           [     0,     73, 905663],
           [     0,     74, 891380],
           [     0,     75, 877029],
           [     0,     72, 891590],
           [     0,     72, 885622],
           [     0,     77, 885482]])
    Profile.ABPlot
    A:ProfileWithinEvent stampFmt:2023-11-20T20:10:17.034371  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
    B:ProfileWithinEvent stampFmt:2023-11-20T20:09:59.710368  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
    BOA : 36.5 104.9 103.4 102.0 104.5 102.8 101.6 103.6 99.6 97.5   avg(BOA[1:]) 102.2  




~/np/tests/NPFold_stamps_test.sh run_ana::

    MODE:2
    A:Stamps stampFmt:2023-11-20T20:10:17.034371  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
             tBOE  tsG0  tsG1  tsG2  tsG3  tsG4  tsG5  tsG6  tsG7  tsG8  tPrL  tPoL  tEOE 
    A.dss
    array([[   0,   85,  102,  114,  114,  115,  162,  183,  343, 2264, 2265, 8789, 8850],
           [   0,   62,   79,   91,   91,   93,  125,  142,  332, 2097, 2097, 8580, 8639],
           [   0,   62,   78,   91,   91,   92,  126,  143,  287, 2099, 2099, 8583, 8640],
           [   0,   62,   79,   92,   92,   94,  126,  144,  288, 2073, 2074, 8586, 8642],
           [   0,   66,   83,   95,   96,   97,  151,  169,  314, 2085, 2085, 8588, 8647],
           [   0,   74,   91,  103,  103,  105,  139,  156,  301, 2090, 2091, 8545, 8603],
           [   0,   63,   79,   92,   92,   94,  127,  144,  288, 2048, 2048, 8518, 8574],
           [   0,   90,  107,  120,  120,  121,  155,  173,  318, 2110, 2110, 8809, 8870],
           [   0,   65,   82,   95,   96,   97,  171,  203,  482, 2481, 2482, 8991, 9049]])

    B:Stamps stampFmt:2023-11-20T20:09:59.710368  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
             tBOE  tEOE 
    B.dss
    array([[     0, 929934],
           [     0, 896187],
           [     0, 883665],
           [     0, 905660],
           [     0, 891376],
           [     0, 877026],
           [     0, 891586],
           [     0, 885619],
           [     0, 885476]])


PRODUCTION macro : HUH: not much diff
---------------------------------------

::

    ~/np/tests/NPFold_stamps_test.sh run_ana
    PYTHONPATH=$HOME MODE=0 ~/np/tests/NPFold_stamps_test.sh run_ana
    PYTHONPATH=$HOME MODE=0 ~/np/tests/NPFold_profile_test.sh run_ana
    ~/j/jtds/jtds.sh grab 


    MODE:0
    A:Stamps stampFmt:2023-11-20T21:52:45.325569  J23_1_0_rc3_ok0/jok-tds/ALL0 GPUMeta:1:NVIDIA_TITAN_RTX prefix://p creator:jok-tds
              tBOE   tPrL   tPoL  tEOET 
    array([[   0, 2095, 8412, 8412],
           [   0, 2631, 8921, 8922],
           [   0, 2077, 8362, 8362],
           [   0, 2117, 8410, 8410],
           [   0, 2065, 8334, 8335],
           [   0, 2074, 8314, 8314],
           [   0, 2091, 8343, 8344],
           [   0, 2159, 8683, 8685],
           [   0, 2078, 8414, 8415]])
    B:Stamps stampFmt:2023-11-20T21:52:27.692022  J23_1_0_rc3_ok0/jok-tds/ALL0 prefix://n creator:jok-tds
              tBOE   tEOE 
    array([[     0, 883719],
           [     0, 922105],
           [     0, 855139],
           [     0, 878761],
           [     0, 862350],
           [     0, 846799],
           [     0, 858702],
           [     0, 858369],
           [     0, 853864]])



TODO : opticksMode 1 vs 2 vs 3 
--------------------------------




