G4OpticksRecorder_EndOfRunAction_SEGV 
=======================================


Actually issue is bug with passing soname/lvname down the X4PhysicalVolume::ConvertSolid sequence of funcs
--------------------------------------------------------------------------------------------------------------

* at least tidying up soname/lvname handling allows geocache-12dec2021 to succeed on laptop

* corrupt entries for soname/lvname passed into NCSG metadata led to json.exception.type_error.316 
  within GMeshLib::saveMeshes/NCSGData::savesrc/BMeta::write

* somehow this C++ exception is passed into python which results in the stack trace being lost 

* used caveman debugging to isolate the cause

* subseqently found that got same issue with geocache-12dec2021 which does not suffer from 
  the boost::python exception **hiding** (not handling) 


* https://www.boost.org/doc/libs/1_78_0/libs/python/doc/html/tutorial/tutorial/exception.html

::

    struct PodBayDoorException;
    void translator(PodBayDoorException const& x) {
        PyErr_SetString(PyExc_UserWarning, "I'm sorry Dave...");
    }
    BOOST_PYTHON_MODULE(kubrick) {
         register_exception_translator<
              PodBayDoorException>(translator);
         ...




Issue
------------

::

   tds3 

     i 133 aidx  88 midx  88 name                                     solidXJfixture mesh  nv    176 nf    344
    2021-12-12 23:07:33.616 ERROR [201500] [GMeshLib::getMeshSimple@330]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx  94 midx  94 name                                               uni1 mesh  nv    496 nf    960
    2021-12-12 23:07:33.616 ERROR [201500] [GMeshLib::getMeshSimple@330]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx  96 midx  96 name                                       uni_acrylic3 mesh  nv    630 nf   1272
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 1: 0x91
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully



     65     def run(self):
     66         parser = self.get_parser()
     67         if '--help-more' in sys.argv:
     68             parser.print_help()
     69             sys.exit()
     70 
     71         self.args = parser.parse_args()
     72         print(self.args)
     73 
     74         # collect output information
     75         self.args.output_vec = []
     76         self.args.user_output_vec = []
     77 
     78         for module in self.modules:
     79             module.add_output_vec(self.args.output_vec, self.args)
     80             module.add_user_output_vec(self.args.user_output_vec, self.args)
     81 
     82         self.toptask = Sniper.TopTask("junotoptask")
     83         self.toptask.setEvtMax(self.args.evtmax)
     84         self.toptask.setLogLevel(self.DATA_LOG_MAP[self.args.loglevel])
     85 
     86         for module in self.modules:
     87             module.init(self.toptask, self.args)
     88 
     89         self.toptask.show()
     90         self.toptask.run()
    "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py" 90L, 3260C




whats wrong with offline error handling ?
---------------------------------------------

By observation the way the exception gets passed from C++ into python
is done in a way that looses the C++ stack. So cannot see where the 
error is.  It would be better for an abort to happen within C++ to 
avoid loosing the stack. 

* basically passing the exception into python is not helpful in the slightest 


geocache-create on laptop has same error
-----------------------------------------

* with advantage that the stack is intact 
* also this points to not being an overwrite : as wouldnt get error in same place
* suspect the recent rejig of X4PhysicalVolume::ConvertSolid is the culprit 

::

    .i 124 aidx 124 midx 124 name              PMT_20inch_veto_inner1_solid0x5f344e0 mesh  nv    266 nf    528
     i 125 aidx 125 midx 125 name              PMT_20inch_veto_inner2_solid0x5f346d0 mesh  nv    146 nf    288
     i 126 aidx 126 midx 126 name            PMT_20inch_veto_body_solid_1_20x5f33890 mesh  nv    314 nf    624
     i 127 aidx 127 midx 127 name             PMT_20inch_veto_pmt_solid_1_20x5f32f80 mesh  nv    314 nf    624
     i 128 aidx 128 midx 128 name         mask_PMT_20inch_vetosMask_virtual0x5f30030 mesh  nv     50 nf     96
     i 129 aidx 129 midx 129 name                           sOuterWaterPool0x575efd0 mesh  nv     50 nf     96
     i 130 aidx 130 midx 130 name                               sPoolLining0x575e8c0 mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name                               sBottomRock0x575a4e0 mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name                                    sWorld0x574c190 mesh  nv      8 nf     12
    2021-12-12 18:19:36.437 ERROR [3089947] [*GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 133 mesh.index 88
     i 133 aidx  88 midx  88 name                            solidXJfixture0x592ba10 mesh  nv    176 nf    344
    2021-12-12 18:19:36.437 ERROR [3089947] [*GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx  94 midx  94 name                                      uni10x57c5dd0 mesh  nv    496 nf    960
    2021-12-12 18:19:36.437 ERROR [3089947] [*GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx  96 midx  96 name                              uni_acrylic30x59496d0 mesh  nv    630 nf   1272
    2021-12-12 18:19:36.437 INFO  [3089947] [BFile::preparePath@836] created directory /usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1/GItemList
    libc++abi.dylib: terminating with uncaught exception of type nlohmann::detail::type_error: [json.exception.type_error.316] invalid UTF-8 byte at index 1: 0x35
    Process 19851 stopped
    Target 0: (OKX4Test) stopped.

    Process 19851 launched: '/usr/local/opticks/lib/OKX4Test' (x86_64)
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff7264ab66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff72815080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff725a61ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff704a0f8f libc++abi.dylib`abort_message + 245
        frame #4: 0x00007fff704a1113 libc++abi.dylib`default_terminate_handler() + 241
        frame #5: 0x00007fff718e2eab libobjc.A.dylib`_objc_terminate() + 105
        frame #6: 0x00007fff704bc7c9 libc++abi.dylib`std::__terminate(void (*)()) + 8
        frame #7: 0x00007fff704bc26f libc++abi.dylib`__cxa_throw + 121
        frame #8: 0x000000010ac43dc0 libBoostRap.dylib`nlohmann::detail::serializer<nlohmann::basic_json<std::__1::map, std::__1::vector, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, long long, unsigned long long, double, std::__1::allocator, nlohmann::adl_serializer, std::__1::vector<unsigned char, std::__1::allocator<unsigned char> > > >::dump_escaped(this=0x00007ffeefbf7ec8, s="?5P\x17\x01", ensure_ascii=false) at json.hpp:15939
        frame #9: 0x000000010ac4160c libBoostRap.dylib`nlohmann::detail::serializer<nlohmann::basic_json<std::__1::map, std::__1::vector, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, long long, unsigned long long, double, std::__1::allocator, nlohmann::adl_serializer, std::__1::vector<unsigned char, std::__1::allocator<unsigned char> > > >::dump(this=0x00007ffeefbf7ec8, val=0x000000011742c4e8, pretty_print=false, ensure_ascii=false, indent_step=0, current_indent=0) at json.hpp:15676
        frame #10: 0x000000010ac4108b libBoostRap.dylib`nlohmann::detail::serializer<nlohmann::basic_json<std::__1::map, std::__1::vector, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, long long, unsigned long long, double, std::__1::allocator, nlohmann::adl_serializer, std::__1::vector<unsigned char, std::__1::allocator<unsigned char> > > >::dump(this=0x00007ffeefbf7ec8, val=0x000000011742c0e0, pretty_print=false, ensure_ascii=false, indent_step=0, current_indent=0) at json.hpp:15606
        frame #11: 0x000000010ac3099d libBoostRap.dylib`nlohmann::operator<<(std::__1::basic_ostream<char, std::__1::char_traits<char> >&, nlohmann::basic_json<std::__1::map, std::__1::vector, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, long long, unsigned long long, double, std::__1::allocator, nlohmann::adl_serializer, std::__1::vector<unsigned char, std::__1::allocator<unsigned char> > > const&)(o=0x00007ffeefbf8be0, j=0x000000011742c0e0) at json.hpp:23055
        frame #12: 0x000000010ac2fd5b libBoostRap.dylib`BMeta::write(this=0x000000011742c0e0, path0="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1/GMeshLibNCSG/15/meta.json", path1=0x0000000000000000) const at BMeta.cc:530
        frame #13: 0x000000010ac2f616 libBoostRap.dylib`BMeta::save(this=0x000000011742c0e0, path="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1/GMeshLibNCSG/15/meta.json") const at BMeta.cc:115
        frame #14: 0x000000010a5460a3 libNPY.dylib`NPYMeta::save(this=0x0000000117429510, dir="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1/GMeshLibNCSG/15") const at NPYMeta.cpp:107
        frame #15: 0x000000010a64309a libNPY.dylib`NCSG::savesrc(this=0x0000000117429380, treedir_="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1/GMeshLibNCSG/15") const at NCSG.cpp:375
        frame #16: 0x000000010a642b50 libNPY.dylib`NCSG::savesrc(this=0x0000000117429380, idpath="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1", rela="GMeshLibNCSG", relb="15") const at NCSG.cpp:358
        frame #17: 0x0000000109b349df libGGeo.dylib`GMeshLib::saveMeshes(this=0x0000000115945f70, idpath="/usr/local/opticks/geocache/OKX4Test_lWorld0x574e7f0_PV_g4live/g4ok_gltf/f65f5cd1a197e3a0c9fe55975ff2c7a7/1") const at GMeshLib.cc:601
        frame #18: 0x0000000109b337c0 libGGeo.dylib`GMeshLib::save(this=0x0000000115945f70) at GMeshLib.cc:101
        frame #19: 0x0000000109b18a9c libGGeo.dylib`GGeo::save(this=0x0000000115943950) at GGeo.cc:718
        frame #20: 0x0000000109b17945 libGGeo.dylib`GGeo::postDirectTranslation(this=0x0000000115943950) at GGeo.cc:600
        frame #21: 0x000000010001575a OKX4Test`main(argc=8, argv=0x00007ffeefbfe660) at OKX4Test.cc:113
        frame #22: 0x00007fff724fa015 libdyld.dylib`start + 1
    (lldb) 





Attempting to switch off execptions not working
--------------------------------------------------

* https://json.nlohmann.me/home/exceptions/

::
  
    export JSON_NOEXCEPTION=1





red herring SEGV
--------------------

::

    Program received signal SIGSEGV, Segmentation fault.
    G4OpticksRecorder::EndOfRunAction (this=0xb30880, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    83	    m_manager->EndOfRunAction(run); 
    (gdb) bt
    #0  G4OpticksRecorder::EndOfRunAction (this=0xb30880, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    #1  0x00007fffcaa5b0a8 in G4OpticksAnaMgr::EndOfRunAction (this=0xb580c0, run=0x0) at /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:30
    #2  0x00007fffcb20c945 in MgrOfAnaElem::EndOfRunAction (this=0x7fffcb41bb00 <MgrOfAnaElem::instance()::s_mgr>, run=0x0)
        at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:39
    #3  0x00007fffcad7eabf in LSExpRunAction::EndOfRunAction (this=0x56d6660, aRun=0x0) at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimOptions/src/LSExpRunAction.cc:73
    #4  0x00007fffdf76071d in G4RunManager::RunTermination() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #5  0x00007fffcafd253b in G4SvcRunManager::finalizeRM (this=0x854d50) at /data/blyth/junotop/offline/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #6  0x00007fffcb20003a in DetSimAlg::finalize (this=0xb30b80) at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #7  0x00007fffef610a0d in DleSupervisor::finalize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffef62250b in Task::finalize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffef6266b0 in TaskWatchDog::finalize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffef6273c8 in TaskWatchDog::terminate() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffef623304 in Task::~Task() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffefaca96c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /data/blyth/junotop/sniper/InstallArea/python/Sniper/libSniperPython.so
    #13 0x00007fffef3d031c in instance_dealloc () from /data/blyth/junotop/ExternalLibs/Boost/1.77.0/lib/libboost_python38.so.1.77.0
    #14 0x00007ffff7955ec2 in subtype_dealloc (self=0x7ffff0034720) at Objects/typeobject.c:1292
    #15 0x00007ffff79328c4 in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #16 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #17 dict_dealloc (mp=0x7fffeff053c0) at Objects/dictobject.c:1990
    #18 0x00007ffff7955fe1 in _Py_DECREF (filename=0x7ffff7ab3990 "Objects/typeobject.c", lineno=1277, op=<optimized out>) at ./Include/object.h:478
    #19 subtype_dealloc (self=0x7ffff01112e0) at Objects/typeobject.c:1277
    #20 0x00007ffff793105d in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #21 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #22 free_keys_object (keys=0x6ab210) at Objects/dictobject.c:584
    #23 0x00007ffff7932968 in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #24 dict_dealloc (mp=0x7ffff7f1bfc0) at Objects/dictobject.c:1998
    #25 0x00007ffff7942285 in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #26 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #27 module_dealloc (m=0x7ffff7ed1360) at Objects/moduleobject.c:690
    #28 0x00007ffff7931ad5 in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #29 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #30 insertdict (mp=0x7ffff7f51d00, key=0x7ffff01720f0, hash=-113109597308247622, value=0x7ffff7d97200 <_Py_NoneStruct>) at Objects/dictobject.c:1102
    #31 0x00007ffff7a04779 in PyImport_Cleanup () at Python/import.c:492
    #32 0x00007ffff7a1b990 in Py_FinalizeEx () at Python/pylifecycle.c:1229
    #33 Py_FinalizeEx () at Python/pylifecycle.c:1150
    #34 0x00007ffff7a3e255 in Py_RunMain () at Modules/main.c:691
    #35 0x00007ffff7a3e953 in pymain_main (args=0x7fffffff7290) at Modules/main.c:719
    #36 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:743
    #37 0x00007ffff695a555 in __libc_start_main () from /lib64/libc.so.6
    #38 0x000000000040065e in _start ()
    (gdb) 


::

    (gdb) f 2
    #2  0x00007fffcb20c945 in MgrOfAnaElem::EndOfRunAction (this=0x7fffcb41bb00 <MgrOfAnaElem::instance()::s_mgr>, run=0x0)
        at /data/blyth/junotop/offline/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:39
    39	          val->EndOfRunAction(run);
    (gdb) f 1
    #1  0x00007fffcaa5b0a8 in G4OpticksAnaMgr::EndOfRunAction (this=0xb580c0, run=0x0) at /data/blyth/junotop/offline/Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc:30
    30	void G4OpticksAnaMgr::EndOfRunAction(const G4Run* run) {           m_recorder->EndOfRunAction(run);         }
    (gdb) f 0
    #0  G4OpticksRecorder::EndOfRunAction (this=0xb30880, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    83	    m_manager->EndOfRunAction(run); 
    (gdb) list
    78	    m_manager->BeginOfRunAction(run); 
    79	}
    80	void G4OpticksRecorder::EndOfRunAction(const G4Run* run)
    81	{
    82	    LOG(LEVEL); 
    83	    m_manager->EndOfRunAction(run); 
    84	
    85	}
    86	
    87	
    (gdb) p m_manager
    $1 = (CManager *) 0x0
    (gdb) 



Huh : G4OpticksRecorder::setGeometry not called ?::


     52 /**
     53 G4OpticksRecorder::setGeometry
     54 ---------------------------------
     55 
     56 Invoked by G4Opticks::setGeometry
     57 **/
     58 
     59 void G4OpticksRecorder::setGeometry(const GGeo* ggeo_)
     60 {
     61     m_ggeo = ggeo_ ;
     62     m_ok = m_ggeo->getOpticks();
     63 
     64 
     65 
     66     m_material_bridge = new CMaterialBridge(m_ggeo->getMaterialLib()) ;
     67     m_manager = new CManager(m_ok);
     68     m_manager->setMaterialBridge(m_material_bridge);
     69 
     70     m_ok->setSave(true);  // override embedded commandline default 
     71     LOG(LEVEL);
     72 }
     73 
     74 
     75 void G4OpticksRecorder::BeginOfRunAction(const G4Run* run)
     76 {
     77     LOG(LEVEL);
     78     m_manager->BeginOfRunAction(run);
     79 }
     80 void G4OpticksRecorder::EndOfRunAction(const G4Run* run)
     81 {
     82     LOG(LEVEL);
     83     m_manager->EndOfRunAction(run);
     84 
     85 }
     86 


This could be red herring arising from an early termination as a result of another error. 



Back to 15
--------------


Looks like soname metadata being overwritten::

    N[blyth@localhost GMeshLibNCSG]$ cat 0/meta.json
    {"balanced":0,"lvname":"lUpperChimneyLS","soname":"Upper_LS_tube"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 1/meta.json
    {"balanced":0,"lvname":"lUpperChimneySteel","soname":"a"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 2/meta.json
    {"balanced":0,"lvname":"lUpperChimneyTyvek","soname":"a"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 3/meta.json
    {"balanced":0,"lvname":"lUpperChimney","soname":"Upper_Chimney"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 4/meta.json
    {"balanced":0,"lvname":"lBar","soname":"sBar"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 5/meta.json
    {"balanced":0,"lvname":"lCoating","soname":"sBar"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 6/meta.json
    {"balanced":0,"lvname":"lPanelTape","soname":"sPanelTape"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 7/meta.json
    {"balanced":0,"lvname":"lPanel","soname":"sPanel"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 8/meta.json
    {"balanced":0,"lvname":"lPlanef_","soname":"sPlane"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 9/meta.json
    {"balanced":0,"lvname":"lWallff_","soname":"sWall"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 10/meta.json
    {"balanced":0,"lvname":"lAirTT","soname":"sAirTT"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 11/meta.json
    {"balanced":0,"lvname":"lExpHall","soname":"sExpHall"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 12/meta.json
    {"balanced":0,"lvname":"lTopRock","soname":"sTopRock"}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 13/meta.json
    {"balanced":0,"lvname":"GLw1.up10_up11_HBeam","soname":""}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 14/meta.json
    {"balanced":0,"lvname":"GLw1.up09_up10_HBeam","soname":""}N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 15/meta.json
    {"balanced":0,"lvname":"GLw1.up08_up09_HBeam","soname":"N[blyth@localhost GMeshLibNCSG]$ 
    N[blyth@localhost GMeshLibNCSG]$ cat 16/meta.json
    cat: 16/meta.json: No such file or directory
    N[blyth@localhost GMeshLibNCSG]$ 




::

    2021-12-13 01:16:01.439 INFO  [257648] [NCSG::savesrc@374] [ m_meta
    2021-12-13 01:16:01.440 INFO  [257648] [NPYMeta::save@96] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14
    2021-12-13 01:16:01.440 INFO  [257648] [NPYMeta::save@106] [ path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [BMeta::save@114] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [BMeta::write@519] write to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [BMeta::write@529] [ stream m_js to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [BMeta::write@534] ] stream m_js to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [BMeta::save@116] ] /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [NPYMeta::save@108] ] path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14/meta.json
    2021-12-13 01:16:01.440 INFO  [257648] [NPYMeta::save@110] ] /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14
    2021-12-13 01:16:01.440 INFO  [257648] [NCSG::savesrc@376] ] m_meta
    2021-12-13 01:16:01.440 INFO  [257648] [NCSG::savesrc@378] ] treedir_ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/14
    2021-12-13 01:16:01.440 INFO  [257648] [GMeshLib::saveMeshes@602] ] saving NCSG sidx 14
    2021-12-13 01:16:01.440 INFO  [257648] [GMeshLib::saveMeshes@586]  idx 15
    2021-12-13 01:16:01.440 INFO  [257648] [GMeshLib::saveMeshes@591] [ saving GMesh sidx 15
    2021-12-13 01:16:01.440 INFO  [257648] [GMeshLib::saveMeshes@593] ] saving GMesh sidx 15
    2021-12-13 01:16:01.440 INFO  [257648] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 15
    2021-12-13 01:16:01.440 INFO  [257648] [NCSG::savesrc@369] [ treedir_ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15
    2021-12-13 01:16:01.440 INFO  [257648] [NCSG::savesrc@371] m_csgdata
    2021-12-13 01:16:01.440 INFO  [257648] [NCSGData::savesrc@170] [
    2021-12-13 01:16:01.441 INFO  [257648] [NCSGData::savesrc@180] ]
    2021-12-13 01:16:01.441 INFO  [257648] [NCSG::savesrc@374] [ m_meta
    2021-12-13 01:16:01.441 INFO  [257648] [NPYMeta::save@96] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15
    2021-12-13 01:16:01.441 INFO  [257648] [NPYMeta::save@106] [ path /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15/meta.json
    2021-12-13 01:16:01.441 INFO  [257648] [BMeta::save@114] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15/meta.json
    2021-12-13 01:16:01.441 INFO  [257648] [BMeta::write@519] write to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15/meta.json
    2021-12-13 01:16:01.441 INFO  [257648] [BMeta::write@529] [ stream m_js to /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/15/meta.json
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 2: 0xB1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-13 01:16:01.455 FATAL [257648] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-13 01:16:01.456 INFO  [257648] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -
    2021-12-13 01:16:01.456 FATAL [257648] [G4Opticks::dumpSkipGencode@392] OPTICKS_SKIP_GENCODE m_skip_gencode_count 0
    2021-12-13 01:16:01.456 FATAL [257648] [G4Opticks::finalizeProfile@427]  not enough profile stamps0
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    Delete G4SvcRunManager
    2021-12-13 01:16:01.470 INFO  [257648] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@52]  m_opticksMode 3 m_opticksCtrl - m_event_total 0 m_genstep_total 0 m_photon_total 0 m_hit_total 0 m_merged_total 0 m_savegensteps 0 m_savehits 0

    **************************************************
    Terminating @ localhost.localdomain on Mon Dec 13 01:16:01 2021
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Inferior 1 (process 257648) exited with code 01]
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-24.el7_9.x86_64 openssl-libs-1.0.2k-22.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) 




Some variability in which save fails...
------------------------------------------

::

    2021-12-13 01:00:45.073 INFO  [244249] [GMeshLib::saveMeshes@602] ] saving NCSG sidx 19
    2021-12-13 01:00:45.073 INFO  [244249] [GMeshLib::saveMeshes@586]  idx 20
    2021-12-13 01:00:45.073 INFO  [244249] [GMeshLib::saveMeshes@591] [ saving GMesh sidx 20
    2021-12-13 01:00:45.074 INFO  [244249] [GMeshLib::saveMeshes@593] ] saving GMesh sidx 20
    2021-12-13 01:00:45.074 INFO  [244249] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 20
    2021-12-13 01:00:45.074 INFO  [244249] [NCSG::savesrc@369] [ treedir_ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/20
    2021-12-13 01:00:45.074 INFO  [244249] [NCSG::savesrc@371] m_csgdata
    2021-12-13 01:00:45.074 INFO  [244249] [NCSG::savesrc@374] m_meta
    2021-12-13 01:00:45.074 INFO  [244249] [NCSG::savesrc@377] ] treedir_ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/20
    2021-12-13 01:00:45.074 INFO  [244249] [GMeshLib::saveMeshes@602] ] saving NCSG sidx 20
    2021-12-13 01:00:45.074 INFO  [244249] [GMeshLib::saveMeshes@586]  idx 21
    2021-12-13 01:00:45.074 INFO  [244249] [GMeshLib::saveMeshes@591] [ saving GMesh sidx 21
    2021-12-13 01:00:45.075 INFO  [244249] [GMeshLib::saveMeshes@593] ] saving GMesh sidx 21
    2021-12-13 01:00:45.075 INFO  [244249] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 21
    2021-12-13 01:00:45.075 INFO  [244249] [NCSG::savesrc@369] [ treedir_ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GMeshLibNCSG/21
    2021-12-13 01:00:45.075 INFO  [244249] [NCSG::savesrc@371] m_csgdata
    2021-12-13 01:00:45.075 INFO  [244249] [NCSG::savesrc@374] m_meta
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 1: 0x8E
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-13 01:00:45.088 FATAL [244249] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-13 01:00:45.089 INFO  [244249] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -
    2021-12-13 01:00:45.089 FATAL [244249] [G4Opticks::dumpSkipGencode@392] OPTICKS_SKIP_GENCODE m_skip_gencode_count 0
    2021-12-13 01:00:45.089 FATAL [244249] [G4Opticks::finalizeProfile@427]  not enough profile stamps0
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    Delete G4SvcRunManager
    2021-12-13 01:00:45.102 INFO  [244249] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@52]  m_opticksMode 3 m_opticksCtrl - m_event_total 0 m_genstep_total 0 m_photon_total 0 m_hit_total 0 m_merged_total 0 m_savegensteps 0 m_savehits 0

    **************************************************
    Terminating @ localhost.localdomain on Mon Dec 13 01:00:45 2021
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Inferior 1 (process 244249) exited with code 01]
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-24.el7_9.x86_64 openssl-libs-1.0.2k-22.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) 


Yet more pointing to NCSG of "16 GLw1.up08_up09_FlangeI_Web_FlangeII"
--------------------------------------------------------------------------

::

    N[blyth@localhost offline]$ export BMeta=INFO
    N[blyth@localhost offline]$ export NPYMeta=INFO
    N[blyth@localhost offline]$ export NCSGData=INFO
    N[blyth@localhost offline]$ export NCSG=INFO
    N[blyth@localhost offline]$ export GMeshLib=INFO
    N[blyth@localhost offline]$ export GGeo=INFO



/home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1/GItemList/GMeshLib.txt::

     01 Upper_LS_tube
      2 Upper_Steel_tube
      3 Upper_Tyvek_tube
      4 Upper_Chimney
      5 sBar
      6 sBar
      7 sPanelTape
      8 sPanel
      9 sPlane
     10 sWall
     11 sAirTT
     12 sExpHall
     13 sTopRock
     14 GLw1.up10_up11_FlangeI_Web_FlangeII
     15 GLw1.up09_up10_FlangeI_Web_FlangeII
     16 GLw1.up08_up09_FlangeI_Web_FlangeII
     17 GLw1.up07_up08_FlangeI_Web_FlangeII
     18 GLw1.up06_up07_FlangeI_Web_FlangeII
     19 GLw1.up05_up06_FlangeI_Web_FlangeII
     20 GLw1.up04_up05_FlangeI_Web_FlangeII
     21 GLw1.up03_up04_FlangeI_Web_FlangeII
     22 GLw1.up02_up03_FlangeI_Web_FlangeII
     23 GLw1.up01_up02_FlangeI_Web_FlangeII
     24 GLw2.equ_up01_FlangeI_Web_FlangeII
     25 GLw2.equ_bt01_FlangeI_Web_FlangeII
     26 GLw3.bt01_bt02_FlangeI_Web_FlangeII
     27 GLw3.bt02_bt03_FlangeI_Web_FlangeII
     28 GLw2.bt03_bt04_FlangeI_Web_FlangeII
     29 GLw2.bt04_bt05_FlangeI_Web_FlangeII




::

    2021-12-13 00:47:45.044 INFO  [231381] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 14
    2021-12-13 00:47:45.044 INFO  [231381] [GMeshLib::saveMeshes@602] ] saving NCSG sidx 14
    2021-12-13 00:47:45.044 INFO  [231381] [GMeshLib::saveMeshes@586]  idx 15
    2021-12-13 00:47:45.044 INFO  [231381] [GMeshLib::saveMeshes@591] [ saving GMesh sidx 15
    2021-12-13 00:47:45.045 INFO  [231381] [GMeshLib::saveMeshes@593] ] saving GMesh sidx 15
    2021-12-13 00:47:45.045 INFO  [231381] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 15
    2021-12-13 00:47:45.045 INFO  [231381] [GMeshLib::saveMeshes@602] ] saving NCSG sidx 15
    2021-12-13 00:47:45.045 INFO  [231381] [GMeshLib::saveMeshes@586]  idx 16
    2021-12-13 00:47:45.045 INFO  [231381] [GMeshLib::saveMeshes@591] [ saving GMesh sidx 16
    2021-12-13 00:47:45.046 INFO  [231381] [GMeshLib::saveMeshes@593] ] saving GMesh sidx 16
    2021-12-13 00:47:45.046 INFO  [231381] [GMeshLib::saveMeshes@600] [ saving NCSG sidx 16
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 2: 0xB2
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-13 00:47:45.059 FATAL [231381] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-13 00:47:45.059 INFO  [231381] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -
    2021-12-13 00:47:45.060 FATAL [231381] [G4Opticks::dumpSkipGencode@392] OPTICKS_SKIP_GENCODE m_skip_gencode_count 0
    2021-12-13 00:47:45.060 FATAL [231381] [G4Opticks::finalizeProfile@427]  not enough profile stamps0
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    Delete G4SvcRunManager
    2021-12-13 00:47:45.077 INFO  [231381] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@52]  m_opticksMode 3 m_opticksCtrl - m_event_total 0 m_genstep_total 0 m_photon_total 0 m_hit_total 0 m_merged_total 0 m_savegensteps 0 m_savehits 0

    **************************************************





More logging makes it look like an error during the save of a mesh !
------------------------------------------------------------------------

::

    i 130 aidx 130 midx 130 name                                        sPoolLining mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name                                        sBottomRock mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name                                             sWorld mesh  nv      8 nf     12
    2021-12-13 00:34:42.145 ERROR [229474] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 133 mesh.index 88
     i 133 aidx  88 midx  88 name                                     solidXJfixture mesh  nv    176 nf    344
    2021-12-13 00:34:42.145 ERROR [229474] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx  94 midx  94 name                                               uni1 mesh  nv    496 nf    960
    2021-12-13 00:34:42.145 ERROR [229474] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx  96 midx  96 name                                       uni_acrylic3 mesh  nv    630 nf   1272
    2021-12-13 00:34:42.145 INFO  [229474] [GMeshLib::addAltMeshes@148] ]
    2021-12-13 00:34:42.145 INFO  [229474] [GMeshLib::save@93] m_meshnames.save idpath /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-13 00:34:42.145 INFO  [229474] [GMeshLib::save@97] saveAltReferences 
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::save@100] saveMeshes
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::saveMeshes@578] [
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@436] [
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@437]   MAX_MESH 300 idpath /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1 m_reldir GMeshLib m_reldir_solids GMeshLibNCSG
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 0 exists_0 1 exists_1 1
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 1 exists_0 1 exists_1 1
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.146 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 2 exists_0 1 exists_1 1
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 3 exists_0 1 exists_1 1
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 4 exists_0 1 exists_1 1
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.147 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 5 exists_0 1 exists_1 1
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 6 exists_0 1 exists_1 1
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 7 exists_0 1 exists_1 1
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.148 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 8 exists_0 1 exists_1 1
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 9 exists_0 1 exists_1 1
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 10 exists_0 1 exists_1 1
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.149 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 11 exists_0 1 exists_1 1
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 12 exists_0 1 exists_1 1
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 13 exists_0 1 exists_1 1
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.150 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 14 exists_0 1 exists_1 1
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 15 exists_0 1 exists_1 1
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 16 exists_0 1 exists_1 1
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.151 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 17 exists_0 1 exists_1 1
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 18 exists_0 1 exists_1 1
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 19 exists_0 1 exists_1 1
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.152 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 20 exists_0 1 exists_1 1
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 21 exists_0 1 exists_1 1
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@455]  exists_0 RemoveDir 
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@461]  exists_1 RemoveDir 
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 22 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 23 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 24 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 25 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 26 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 27 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 28 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 29 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 30 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 31 exists_0 0 exists_1 0
    2021-12-13 00:34:42.153 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 32 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 33 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 34 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 35 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 36 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 37 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 38 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 39 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 40 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 41 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 42 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 43 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 44 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 45 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 46 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 47 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 48 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 49 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 50 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 51 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 52 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 53 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 54 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 55 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 56 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 57 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 58 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 59 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 60 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 61 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 62 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 63 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 64 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 65 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 66 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 67 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 68 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 69 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 70 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 71 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 72 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 73 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 74 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 75 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 76 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 77 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 78 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 79 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 80 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 81 exists_0 0 exists_1 0
    2021-12-13 00:34:42.154 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 82 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 83 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 84 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 85 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 86 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 87 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 88 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 89 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 90 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 91 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 92 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 93 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 94 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 95 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 96 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 97 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 98 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 99 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 100 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 101 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 102 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 103 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 104 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 105 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 106 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 107 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 108 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 109 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 110 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 111 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 112 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 113 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 114 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 115 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 116 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 117 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 118 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 119 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 120 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 121 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 122 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 123 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 124 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 125 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 126 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 127 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 128 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 129 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 130 exists_0 0 exists_1 0
    2021-12-13 00:34:42.155 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 131 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 132 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 133 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 134 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 135 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 136 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 137 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 138 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 139 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 140 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 141 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 142 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 143 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 144 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 145 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 146 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 147 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 148 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 149 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 150 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 151 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 152 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 153 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 154 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 155 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 156 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 157 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 158 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 159 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 160 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 161 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 162 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 163 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 164 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 165 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 166 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 167 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 168 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 169 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 170 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 171 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 172 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 173 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 174 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 175 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 176 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 177 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 178 exists_0 0 exists_1 0
    2021-12-13 00:34:42.156 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 179 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 180 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 181 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 182 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 183 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 184 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 185 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 186 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 187 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 188 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 189 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 190 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 191 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 192 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 193 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 194 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 195 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 196 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 197 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 198 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 199 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 200 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 201 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 202 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 203 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 204 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 205 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 206 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 207 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 208 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 209 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 210 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 211 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 212 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 213 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 214 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 215 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 216 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 217 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 218 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 219 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 220 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 221 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 222 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 223 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 224 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 225 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 226 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 227 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 228 exists_0 0 exists_1 0
    2021-12-13 00:34:42.157 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 229 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 230 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 231 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 232 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 233 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 234 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 235 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 236 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 237 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 238 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 239 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 240 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 241 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 242 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 243 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 244 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 245 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 246 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 247 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 248 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 249 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 250 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 251 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 252 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 253 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 254 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 255 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 256 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 257 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 258 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 259 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 260 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 261 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 262 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 263 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 264 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 265 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 266 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 267 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 268 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 269 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 270 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 271 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 272 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 273 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 274 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 275 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 276 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 277 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 278 exists_0 0 exists_1 0
    2021-12-13 00:34:42.158 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 279 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 280 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 281 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 282 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 283 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 284 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 285 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 286 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 287 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 288 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 289 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 290 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 291 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 292 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 293 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 294 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 295 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 296 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 297 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 298 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@451]  sidx 299 exists_0 0 exists_1 0
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::removeDirs@465] ]
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::saveMeshes@582]  num_meshes 136
    2021-12-13 00:34:42.159 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 0
    2021-12-13 00:34:42.160 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 1
    2021-12-13 00:34:42.161 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 2
    2021-12-13 00:34:42.161 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 3
    2021-12-13 00:34:42.162 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 4
    2021-12-13 00:34:42.163 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 5
    2021-12-13 00:34:42.164 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 6
    2021-12-13 00:34:42.165 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 7
    2021-12-13 00:34:42.166 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 8
    2021-12-13 00:34:42.167 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 9
    2021-12-13 00:34:42.168 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 10
    2021-12-13 00:34:42.168 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 11
    2021-12-13 00:34:42.169 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 12
    2021-12-13 00:34:42.170 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 13
    2021-12-13 00:34:42.171 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 14
    2021-12-13 00:34:42.172 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 15
    2021-12-13 00:34:42.172 INFO  [229474] [GMeshLib::saveMeshes@586]  idx 16
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 2: 0xB2
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-13 00:34:42.191 FATAL [229474] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-13 00:34:42.191 INFO  [229474] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -
    2021-12-13 00:34:42.191 FATAL [229474] [G4Opticks::dumpSkipGencode@392] OPTICKS_SKIP_GENCODE m_skip_gencode_count 0
    2021-12-13 00:34:42.191 FATAL [229474] [G4Opticks::finalizeProfile@427]  not enough profile stamps0
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    Delete G4SvcRunManager
    2021-12-13 00:34:42.210 INFO  [229474] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@52]  m_opticksMode 3 m_opticksCtrl - m_event_total 0 m_genstep_total 0 m_photon_total 0 m_hit_total 0 m_merged_total 0 m_savegensteps 0 m_savehits 0

    **************************************************




Added logging to caveman debug issue as offline catches errors and in so doing hides the location of causes
-------------------------------------------------------------------------------------------------------------

::

    .i 130 aidx 130 midx 130 name                                        sPoolLining mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name                                        sBottomRock mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name                                             sWorld mesh  nv      8 nf     12
    2021-12-13 00:13:51.294 ERROR [227355] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 133 mesh.index 88
     i 133 aidx  88 midx  88 name                                     solidXJfixture mesh  nv    176 nf    344
    2021-12-13 00:13:51.294 ERROR [227355] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx  94 midx  94 name                                               uni1 mesh  nv    496 nf    960
    2021-12-13 00:13:51.294 ERROR [227355] [GMeshLib::getMeshSimple@342]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx  96 midx  96 name                                       uni_acrylic3 mesh  nv    630 nf   1272
    2021-12-13 00:13:51.294 INFO  [227355] [GMeshLib::addAltMeshes@148] ]
    2021-12-13 00:13:51.294 INFO  [227355] [GMeshLib::save@93] m_meshnames.save idpath /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-13 00:13:51.294 INFO  [227355] [GMeshLib::save@97] saveAltReferences 
    2021-12-13 00:13:51.295 INFO  [227355] [GMeshLib::save@100] saveMeshes

    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 0: 0xA0

    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-13 00:13:51.336 FATAL [227355] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-13 00:13:51.336 INFO  [227355] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -







Can avoid SEGV but still same initial fail
--------------------------------------------

::


    .i 129 aidx 129 midx 129 name                                    sOuterWaterPool mesh  nv     50 nf     96
     i 130 aidx 130 midx 130 name                                        sPoolLining mesh  nv     50 nf     96
     i 131 aidx 131 midx 131 name                                        sBottomRock mesh  nv     50 nf     96
     i 132 aidx 132 midx 132 name                                             sWorld mesh  nv      8 nf     12
    2021-12-12 23:24:54.906 ERROR [210602] [GMeshLib::getMeshSimple@330]  mesh indices do not match  m_meshes index 133 mesh.index 88
     i 133 aidx  88 midx  88 name                                     solidXJfixture mesh  nv    176 nf    344
    2021-12-12 23:24:54.906 ERROR [210602] [GMeshLib::getMeshSimple@330]  mesh indices do not match  m_meshes index 134 mesh.index 94
     i 134 aidx  94 midx  94 name                                               uni1 mesh  nv    496 nf    960
    2021-12-12 23:24:54.906 ERROR [210602] [GMeshLib::getMeshSimple@330]  mesh indices do not match  m_meshes index 135 mesh.index 96
     i 135 aidx  96 midx  96 name                                       uni_acrylic3 mesh  nv    630 nf   1272
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: [json.exception.type_error.316] invalid UTF-8 byte at index 0: 0x80
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    2021-12-12 23:24:54.948 FATAL [210602] [G4OpticksRecorder::EndOfRunAction@95]  m_manager null indicates that G4OpticksRecorder::setGeometry has not been called 
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-12 23:24:54.948 INFO  [210602] [G4Opticks::Finalize@290] G4Opticks.desc ok 0
    -
    -
    2021-12-12 23:24:54.948 FATAL [210602] [G4Opticks::dumpSkipGencode@392] OPTICKS_SKIP_GENCODE m_skip_gencode_count 0
    2021-12-12 23:24:54.948 FATAL [210602] [G4Opticks::finalizeProfile@427]  not enough profile stamps0
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    Delete G4SvcRunManager
    2021-12-12 23:24:54.969 INFO  [210602] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@52]  m_opticksMode 3 m_opticksCtrl - m_event_total 0 m_genstep_total 0 m_photon_total 0 m_hit_total 0 m_merged_total 0 m_savegensteps 0 m_savehits 0

