G4OpticksRecorder_EndOfRunAction_SEGV
=======================================



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

