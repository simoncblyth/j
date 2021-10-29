EndOfRunAction_getting_null_G4Run
===================================

Actually thats not the real problem. Just the silly way that JUNO offline/sniper tries
hard to hide the real error. Which is a missing input file.::

    Setup CDReflectorSteel Material Tables from MCParamsSvc
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:MCParamsSvc.GetPath ERROR: Path /data/blyth/junotop/data/Simulation/DetSim/Material/CDInnerReflector/REFLECTIVITY does not exist.
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: basic_string::_S_construct null not valid
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffce4525c8 in G4OpticksRecorder::EndOfRunAction (this=0x41538f0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    83	    m_manager->EndOfRunAction(run); 


::

    Setup CDReflectorSteel Material Tables from MCParamsSvc
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:MCParamsSvc.GetPath ERROR: Path /data/blyth/junotop/data/Simulation/DetSim/Material/CDInnerReflector/REFLECTIVITY does not exist.
    Traceback (most recent call last):
      File "/data/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/data/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: basic_string::_S_construct null not valid
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffce4525c8 in G4OpticksRecorder::EndOfRunAction (this=0x41538f0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    83	    m_manager->EndOfRunAction(run); 
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-3.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libgcc-4.8.5-44.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-44.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-23.el7_9.x86_64 openssl-libs-1.0.2k-21.el7_9.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007fffce4525c8 in G4OpticksRecorder::EndOfRunAction (this=0x41538f0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    #1  0x00007fffc208da04 in MgrOfAnaElem::EndOfRunAction (this=<optimized out>, run=0x0) at ../src/MgrOfAnaElem.cc:39
    #2  0x00007fffce6a5c8d in G4RunManager::RunTermination() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #3  0x00007fffc2a20bea in G4SvcRunManager::finalizeRM() () from /data/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #4  0x00007fffc2088bdc in DetSimAlg::finalize (this=0x3c48b60) at ../src/DetSimAlg.cc:136
    #5  0x00007fffef7c182d in DleSupervisor::finalize() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #6  0x00007fffef7ceeeb in Task::finalize() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #7  0x00007fffef7d2637 in TaskWatchDog::finalize() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #8  0x00007fffef7d5410 in TaskWatchDog::terminate() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #9  0x00007fffef7d09bf in Task::~Task() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #10 0x00007fffefc7541c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /data/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #11 0x00007fffef9f9e87 in instance_dealloc () from /data/blyth/junotop/ExternalLibs/Boost/1.75.0/lib/libboost_python38.so.1.75.0
    #12 0x00007ffff79374d3 in subtype_dealloc (self=0x7fffedcb9040) at Objects/typeobject.c:1292
    #13 0x00007ffff7911e4d in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #14 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #15 dict_dealloc (mp=0x7fffefe98200) at Objects/dictobject.c:1990
    #16 0x00007ffff79375d2 in _Py_DECREF (filename=0x7ffff7ab3bc5 "Objects/typeobject.c", lineno=1277, op=<optimized out>) at ./Include/object.h:478
    #17 subtype_dealloc (self=0x7ffff7e46430) at Objects/typeobject.c:1277
    #18 0x00007ffff7911d4a in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #19 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #20 free_keys_object (keys=0x6d1200) at Objects/dictobject.c:584
    #21 0x00007ffff7911ee8 in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #22 dict_dealloc (mp=0x7ffff7f456c0) at Objects/dictobject.c:1998
    #23 0x00007ffff7922c1b in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #24 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #25 module_dealloc (m=0x7ffff7f4f720) at Objects/moduleobject.c:690
    #26 0x00007ffff7914da5 in _Py_DECREF (filename=<synthetic pointer>, lineno=541, op=<optimized out>) at ./Include/object.h:478
    #27 _Py_XDECREF (op=<optimized out>) at ./Include/object.h:541
    #28 insertdict (value=0x7ffff7d96300 <_Py_NoneStruct>, hash=2086043064995400815, key=0x7ffff7f0c170, mp=0x7ffff7f52d00) at Objects/dictobject.c:1102
    #29 PyDict_SetItem (op=0x7ffff7f52d00, key=0x7ffff7f0c170, value=0x7ffff7d96300 <_Py_NoneStruct>) at Objects/dictobject.c:1545
    #30 0x00007ffff79f3dcd in PyImport_Cleanup () at Python/import.c:492
    #31 0x00007ffff7a11767 in Py_FinalizeEx () at Python/pylifecycle.c:1229
    #32 0x00007ffff7a3696b in Py_RunMain () at Modules/main.c:691
    #33 0x00007ffff7a3735f in pymain_main (args=0x7fffffff6320) at Modules/main.c:719
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:743
    #35 0x00007ffff6937555 in __libc_start_main () from /lib64/libc.so.6
    #36 0x000000000040069e in _start ()
    (gdb) f 1
    #1  0x00007fffc208da04 in MgrOfAnaElem::EndOfRunAction (this=<optimized out>, run=0x0) at ../src/MgrOfAnaElem.cc:39
    39	          val->EndOfRunAction(run);
    (gdb) f 0
    #0  0x00007fffce4525c8 in G4OpticksRecorder::EndOfRunAction (this=0x41538f0, run=0x0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:83
    83	    m_manager->EndOfRunAction(run); 
    (gdb) 



O[blyth@localhost junoenv]$ bash junoenv offline-data 
= The junoenv is in /data/blyth/junotop/junoenv
= main
= THE JUNOTOP is /data/blyth/junotop
= THE JUNOENVDIR is /data/blyth/junotop/junoenv
== setup-juno-basic-preq: ================================================================
== setup-juno-basic-preq: GLOBAL Environment Variables:
== setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
== setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: ""
== setup-juno-basic-preq: $JUNOARCHIVEGET: ""
== setup-juno-basic-preq: $JUNOARCHIVEURL: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
== setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
== setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
== setup-juno-basic-preq: ================================================================
== setup-juno-offline-data
trunk
=== junoenv-offline-data: 0
=== junoenv-offline-data: URL: https://juno.ihep.ac.cn/svn/offline-data/trunk
==== junoenv-offline-data-checkout: checkout the code https://juno.ihep.ac.cn/svn/offline-data/trunk
==== junoenv-offline-data-checkout: svn co https://juno.ihep.ac.cn/svn/offline-data/trunk data
U    data/Detector/Geometry/PMTPos_CD_LPMT.csv
A    data/Simulation/DetSim/Material/CDInnerReflector
A    data/Simulation/DetSim/Material/CDInnerReflector/ABSLENGTH
A    data/Simulation/DetSim/Material/CDInnerReflector/REFLECTIVITY
U    data/Simulation/DetSim/Material/AcrylicMask/ABSLENGTH
A    data/Simulation/DetSim/Material/StrutSteel
A    data/Simulation/DetSim/Material/StrutSteel/ABSLENGTH
A    data/Simulation/DetSim/Material/StrutSteel/REFLECTIVITY
Checked out revision 107.
/data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
O[blyth@localhost junoenv]$ 

