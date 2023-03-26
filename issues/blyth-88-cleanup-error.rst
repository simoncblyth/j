blyth-88-cleanup-error
==========================

Context
--------

* from :doc:`blyth-88-Custom4-shakedown`



dtor problem ?
----------------

::

    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    *** Error in `/data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python': free(): invalid next size (normal): 0x0000000000b280f0 ***
    ======= Backtrace: =========
    /lib64/libc.so.6(+0x81299)[0x7ffff69b9299]
    /data/blyth/junotop/junosw/InstallArea/lib64/libMCParamsSvc.so(_ZN14SniperPropertyIbED0Ev+0x29)[0x7fffe3c8e3cf]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN11PropertyMgrD1Ev+0x2e)[0x7fffed6bb2fe]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN9DLElementD1Ev+0x22)[0x7fffed6ab3c2]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so(_ZN21WaterPoolConstructionD2Ev+0x41)[0x7fffcee8abeb]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimOptions.so(_ZN21WaterPoolConstructionD0Ev+0x18)[0x7fffcee8ac18]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN7AlgBaseD1Ev+0xf5)[0x7fffed6a8b85]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimAlg.so(_ZN9DetSimAlgD1Ev+0x84)[0x7fffccee2816]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimAlg.so(_ZN9DetSimAlgD0Ev+0x18)[0x7fffccee2832]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN13DleSupervisor5clearEv+0x192)[0x7fffed6b3d02]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN8ExecUnit5resetEv+0x2d)[0x7fffed6b46cd]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN12TaskWatchDog9terminateEv+0x9a)[0x7fffed6


    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69b0ed7 in __libc_message () from /lib64/libc.so.6
    #3  0x00007ffff69b9299 in _int_free () from /lib64/libc.so.6
    #4  0x00007fffe3c8e3cf in SniperProperty<bool>::~SniperProperty (this=0xb280f0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h:51
    #5  0x00007fffed6bb2fe in PropertyMgr::~PropertyMgr() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffed6ab3c2 in DLElement::~DLElement() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffcee8abeb in WaterPoolConstruction::~WaterPoolConstruction (this=0xb27ed0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:36
    #8  0x00007fffcee8ac18 in WaterPoolConstruction::~WaterPoolConstruction (this=0xb27ed0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:38
    #9  0x00007fffed6a8b85 in AlgBase::~AlgBase() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffccee2816 in DetSimAlg::~DetSimAlg (this=0xb26f30, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:28
    #11 0x00007fffccee2832 in DetSimAlg::~DetSimAlg (this=0xb26f30, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:30
    #12 0x00007fffed6b3d02 in DleSupervisor::clear() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffed6b46cd in ExecUnit::reset() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffed6ce0da in TaskWatchDog::terminate() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffed6ca0a4 in Task::~Task() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so


     28 DetSimAlg::~DetSimAlg()
     29 {       
     30 }       

    (gdb) f 9
    #9  0x00007fffed6a8b85 in AlgBase::~AlgBase() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    (gdb) f 8
    #8  0x00007fffcee8ac18 in WaterPoolConstruction::~WaterPoolConstruction (this=0xb27ed0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:38
    38	}
    (gdb) 

     36 WaterPoolConstruction::~WaterPoolConstruction() {
     37     
     38 }   

    (gdb) f 6
    #6  0x00007fffed6ab3c2 in DLElement::~DLElement() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    (gdb) 

    (gdb) f 5
    #5  0x00007fffed6bb2fe in PropertyMgr::~PropertyMgr() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    (gdb) 

    (gdb) f 4
    #4  0x00007fffe3c8e3cf in SniperProperty<bool>::~SniperProperty (this=0xb280f0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h:51
    51	class SniperProperty : public Property
    (gdb) 


HUH all the dtor seem empty

/data/blyth/junotop/sniper/SniperKernel/src/Property.cc
/data/blyth/junotop/sniper/InstallArea/include/SniperKernel/Property.h

::

     26 Property::~Property()
     27 {
     28 }



::

     24 class Property
     25 {
     26 public:
     27     Property(const std::string &key);
     28 
     29     virtual ~Property();
     30 
     31     //return the property key name
     32     const std::string &key() { return m_key; }
     33 
     34     //set property value as var
     35     virtual bool set(const std::string &var) = 0;
     36 
     37     //append var to vector/map property
     38     virtual bool append(const std::string &var);
     39 
     40     //the json value of the associated variable
     41     virtual SniperJSON json() = 0;
     42 
     43     //show the value of the property
     44     virtual void show();
     45 
     46 protected:
     47     const std::string m_key;
     48 };



issue is flakey
-----------------

::

    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 28 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@151:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2055:  dir /tmp/blyth/opticks/GEOM/ntds2/ALL/000
    SEvt::gatherHit@1784:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@669: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    U4Recorder::EndOfRunAction@136: 
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           7.26600        7.26600      0.00101      
    DetSimAlg                1           199997.67188   199997.67188 38.11273     
    Sum of junotoptask       1           200005.09375   200005.09375 0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    *** Error in `/data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python': double free or corruption (!prev): 0x0000000000b2be10 ***
    ======= Backtrace: =========
    /lib64/libc.so.6(+0x81299)[0x7ffff69b9299]
    /data/blyth/junotop/junosw/InstallArea/lib64/libCentralDetector.so(_ZN17HBeamConstructionD1Ev+0x65)[0x7fffce83218f]
    /data/blyth/junotop/junosw/InstallArea/lib64/libCentralDetector.so(_ZN17HBeamConstructionD0Ev+0x18)[0x7fffce8321bc]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN7AlgBaseD1Ev+0xf5)[0x7fffed6a8b85]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimAlg.so(_ZN9DetSimAlgD1Ev+0x84)[0x7fffccee2816]
    /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimAlg.so(_ZN9DetSimAlgD0Ev+0x18)[0x7fffccee2832]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN13DleSupervisor5clearEv+0x192)[0x7fffed6b3d02]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN8ExecUnit5resetEv+0x2d)[0x7fffed6b46cd]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN12TaskWatchDog9terminateEv+0x9a)[0x7fffed6ce0da]
    /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so(_ZN4TaskD1Ev+0x24)[0x7fffed6ca0a4]
    /data/blyth/junotop/sniper/InstallArea/python/Sniper/libSniperPython.so(_ZN5boost6python7objects12value_holderI7TopTaskED2Ev+0x1c)[0x7fffedb86c7c]
    /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so.1.78.0(+0x1b31c)[0x7fffed46c31c]


    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-25.el7_9.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69b0ed7 in __libc_message () from /lib64/libc.so.6
    #3  0x00007ffff69b9299 in _int_free () from /lib64/libc.so.6
    #4  0x00007fffce83218f in HBeamConstruction::~HBeamConstruction (this=0xb2be40, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc:153
    #5  0x00007fffce8321bc in HBeamConstruction::~HBeamConstruction (this=0xb2be40, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/CentralDetector/src/HBeamConstruction.cc:155
    #6  0x00007fffed6a8b85 in AlgBase::~AlgBase() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffccee2816 in DetSimAlg::~DetSimAlg (this=0xb26cd0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:28
    #8  0x00007fffccee2832 in DetSimAlg::~DetSimAlg (this=0xb26cd0, __in_chrg=<optimized out>)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:30
    #9  0x00007fffed6b3d02 in DleSupervisor::clear() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffed6b46cd in ExecUnit::reset() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffed6ce0da in TaskWatchDog::terminate() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffed6ca0a4 in Task::~Task() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffedb86c7c in boost::python::objects::value_holder<TopTask>::~value_holder() ()


try clean build
-----------------

::

    N[blyth@localhost junosw]$ cd build
    N[blyth@localhost build]$ make clean

    jo
    ./build_Debug.sh 


Fixed by clean build
-----------------------

::

    ntds2
    ...
    SEvt::hostside_running_resize_@1005: resizing photon 9508 to evt.num_photon 9810
    U4Debug::Save eventID 0 dir /tmp/u4debug/ntds2/000 EKEY U4Debug_SaveDir
    U4Cerenkov_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 6
    U4Scintillation_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 77
    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 28
    junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 28 hitCollection_muon 0 hitCollection_opticks 0
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4Recorder::EndOfEventAction@151:  eventID 0 eventID_ 0 eidx 0 consistent_eventID  YES
    SEvt::save@2055:  dir /tmp/blyth/opticks/GEOM/ntds2/ALL/000
    SEvt::gatherHit@1784:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@669: 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    U4Recorder::EndOfRunAction@136: 
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           7.12200        7.12200      0.00136      
    DetSimAlg                1           211876.03125   211876.03125 0.00000      
    Sum of junotoptask       1           211883.31250   211883.31250 40.74343     
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 2 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    Delete G4SvcRunManager

    **************************************************
    Terminating @ localhost.localdomain on Sun Mar 26 21:24:24 2023
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    (gdb) bt
    No stack.
    (gdb) 

