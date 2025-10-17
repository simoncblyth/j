instrumentation
=================

instrumentation controls
---------------------------

export SEvt__RUNMETA=1
    enable RUNMETA logging, including the path to "run_meta.txt" 
    with labelled int64_t timestamps, eg::

    SEvt__BeginOfRun:1760593677804485,7316440,1220224
    SEvt__beginOfEvent_FIRST_EGPU:1760593677804634,7316440,1220224
    SEvt__setIndex_A000:1760593677804659,7316440,1220224
    SEvt__endIndex_A000:1760593678062575,8372996,1332824
    SEvt__EndOfRun:1760593678127979,8266712,1227112
    CSGOptiX__SimulateMain_HEAD:1760593674165428,46456,11200
    CSGFoundry__Load_HEAD:1760593674165461,46456,11200
    CSGFoundry__Load_TAIL:1760593677267321,5419960,883336
    CSGOptiX__Create_HEAD:1760593677267361,5419960,883336
    CSGOptiX__Create_TAIL:1760593677804424,7316440,1220224
    A000_QSim__simulate_HEAD:1760593677804471,7316440,1220224
    A000_QSim__simulate_LBEG:1760593677804798,7316440,1220672
    A000_QSim__simulate_PRUP:1760593677804804,7316440,1220672
    A000_QSim__simulate_PREL:1760593677805962,8266712,1221120
    A000_QSim__simulate_POST:1760593677959345,8266712,1225600
    A000_QSim__simulate_DOWN:1760593678062442,8372996,1332824
    A000_QSim__simulate_LEND:1760593678062471,8372996,1332824
    A000_QSim__simulate_PCAT:1760593678062500,8372996,1332824
    A000_QSim__simulate_BRES:1760593678062548,8372996,1332824
    A000_QSim__reset_HEAD:1760593678062555,8372996,1332824
    A000_QSim__reset_TAIL:1760593678129505,8266712,1227112

    The "A000" "A001" prefixes corresponds to the first and second events etc.., 
    suffixes like "QSim__simulate_HEAD" correspond to places throughout the code, eg::

          SProf::Add("QSim__simulate_HEAD")

    The first of the three numbers is microseconds since the epoch. Divide by one million 
    to give seconds. The other two numbers are VM and RS memory usage in KB.
    I have code sysrap/tests/sreport.sh that reads and analyses this metadata
    and makes plots. 



export SEvt__SAVE_NOTHING=1
    with Minimal OR Nothing OPTICKS_EVENT_MODE this setting prevents
    metadata writing





SProf::Add collects int64_t absolute timestamps
------------------------------------------------

::

    zeta:opticks blyth$ find . -type f -exec grep -H SProf::Add {} \;
    ./CSGOptiX/CSGOptiX.cc:    SProf::Add("CSGOptiX__SimulateMain_HEAD");
    ./CSGOptiX/CSGOptiX.cc:    SProf::Add("CSGOptiX__SimulateMain_TAIL");
    ./CSGOptiX/CSGOptiX.cc:    SProf::Add("CSGOptiX__Create_HEAD");
    ./CSGOptiX/CSGOptiX.cc:    SProf::Add("CSGOptiX__Create_TAIL");
    ./CSG/CSGFoundry.cc:    SProf::Add("CSGFoundry__Load_HEAD");
    ./CSG/CSGFoundry.cc:    SProf::Add("CSGFoundry__Load_TAIL");
    ./sysrap/SProf.hh:inline int64_t SProf::Add(const char* name)
    ./sysrap/SProf.hh:inline void SProf::Add( const char* _name, const sprof& prof)
    ./sysrap/tests/SProfTest.cc:    SProf::Add("start"); 
    ./sysrap/tests/SProfTest.cc:    SProf::Add("red"); 
    ./sysrap/tests/SProfTest.cc:    SProf::Add("green"); 
    ./sysrap/tests/SProfTest.cc:    SProf::Add("blue"); 
    ./sysrap/tests/SProfTest.cc:    SProf::Add("stop"); 
    ./qudarap/QSim.cc:    int64_t t_HEAD = SProf::Add("QSim__simulate_HEAD");
    ./qudarap/QSim.cc:    int64_t t_LBEG = SProf::Add("QSim__simulate_LBEG");
    ./qudarap/QSim.cc:        SProf::Add("QSim__simulate_PRUP");
    ./qudarap/QSim.cc:        SProf::Add("QSim__simulate_PREL");
    ./qudarap/QSim.cc:        int64_t t_POST = SProf::Add("QSim__simulate_POST");
    ./qudarap/QSim.cc:        int64_t t_DOWN = SProf::Add("QSim__simulate_DOWN");
    ./qudarap/QSim.cc:    int64_t t_LEND = SProf::Add("QSim__simulate_LEND");
    ./qudarap/QSim.cc:    int64_t t_PCAT = SProf::Add("QSim__simulate_PCAT");
    ./qudarap/QSim.cc:    int64_t t_BRES  = SProf::Add("QSim__simulate_BRES");
    ./qudarap/QSim.cc:    int64_t t_TAIL  = SProf::Add("QSim__simulate_TAIL");
    ./qudarap/QSim.cc:    SProf::Add("QSim__reset_HEAD");
    ./qudarap/QSim.cc:    SProf::Add("QSim__reset_TAIL");
    ./u4/tests/U4HitTest.cc:    SProf::Add("Head"); 
    ./u4/tests/U4HitTest.cc:    SProf::Add("Tail"); 
    ./u4/tests/U4HitTest.cc:    SProf::Add("Head"); 
    ./u4/tests/U4HitTest.cc:    SProf::Add("Tail"); 
    ./u4/tests/U4HitTest.cc:    SProf::Add("Head"); 
    ./u4/tests/U4HitTest.cc:    SProf::Add("Tail"); 






SProf::Add
-------------

SProf.hh::

     73 inline int64_t SProf::Add(const char* name)
     74 {
     75     sprof prof ;
     76     sprof::Stamp(prof);
     77     Add(name, prof);
     78     return prof.st ;
     79 }


     81 inline void SProf::Add( const char* _name, const sprof& prof)
     82 {      
     83     std::stringstream ss ; 
     84     ss << ( HasTag() ? TAG : "" ) << _name ;
     85     std::string name = ss.str();
     86     NAME.push_back(name);
     87     PROF.push_back(prof);
     88 }


* when a tag is defined it is used to prefix the argument name, this
  is used to distinguish profile collections across multiple events



sprof.h::

     25 struct sprof
     26 {
     27     int64_t st ;  // us microsecond (10^-6) timestamp
     28     int32_t vm ;  // KB
     29     int32_t rs ;  // KB 
     ..
     46 };


     53 inline void sprof::Stamp(sprof& p)
     54 {
     55     p.st = sstamp::Now(); 
     56     sproc::Query(p.vm, p.rs) ;  // sprof::Stamp
     57 }   





SProf.cc
----------

::

      1 #include "SProf.hh"
      2 
      3 char SProf::TAG[N] = {} ; 
      4 
      5 std::vector<sprof>       SProf::PROF = {} ;
      6 std::vector<std::string> SProf::NAME = {} ;


SProf::Write
--------------

::

    zeta:opticks blyth$ find . -type f -exec grep -H SProf::Write {} \;
    ./CSGOptiX/CSGOptiX.cc:    SProf::Write("run_meta.txt", true ); // append:true
    ./sysrap/SProf.hh:inline void SProf::Write(const char* path, bool append)
    ./sysrap/tests/SProfTest.cc:    SProf::Write(path, append ); 
    ./sysrap/SEvt.cc:        SProf::Write("SEvt__EndOfRun_SProf.txt", append ) ;
    ./u4/tests/U4HitTest.cc:    SProf::Write(path, append); 
    ./notes/issues/okjob_GPU_memory_leak.rst:     183     SProf::Write("run_meta.txt", true ); // append:true 
    ./notes/issues/CSGOptiXService_impl_notes.rst:     170     SProf::Write("run_meta.txt", true ); // append:true
    zeta:opticks blyth$ 


this write is only for cxs_min.sh
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
::

     161 int CSGOptiX::SimulateMain() // static
     162 {
     163     SProf::Add("CSGOptiX__SimulateMain_HEAD");
     164     SEventConfig::SetRGModeSimulate();
     165     CSGFoundry* fd = CSGFoundry::Load();
     166     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     167     for(int i=0 ; i < SEventConfig::NumEvent() ; i++) cx->simulate(i);
     168     SProf::UnsetTag();
     169     SProf::Add("CSGOptiX__SimulateMain_TAIL");
     170     SProf::Write("run_meta.txt", true ); // append:true
     171     cx->write_Ctx_log();
     172     delete cx ;
     173     return 0 ;
     174 }


SEvt::EndOfRun writes SEvt__EndOfRun_SProf.txt when "export SEvt__EndOfRun_SProf=1"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    1568 void SEvt::EndOfRun()
    1569 {
    1570     SetRunProf("SEvt__EndOfRun");
    1571     SaveRunMeta();
    1572 
    1573     if(EndOfRun_SProf == 1 )
    1574     {
    1575         bool append = false ;
    1576         SProf::Write("SEvt__EndOfRun_SProf.txt", append ) ;
    1577     }
    1578 }
    1579 
    1580 
    1581 const int SEvt::EndOfRun_SProf = ssys::getenvint("SEvt__EndOfRun_SProf",-1) ;





SEvt::endOfEvent
~~~~~~~~~~~~~~~~~~~~

::

    1811 void SEvt::endOfEvent(int eventID)
    1812 {
    1813 
    1814     setStage(SEvt__endOfEvent);
    1815     LOG_IF(info, LIFECYCLE) << id() ;
    1816     sprof::Stamp(p_SEvt__endOfEvent_0);
    1817 
    1818     endIndex(eventID);   // eventID is 0-based
    1819     endMeta();
    1820     gather_metadata();
    1821 
    1822     save();              // gather and save SEventConfig configured arrays
    1823     clear_output();
    1824     clear_genstep();
    1825     clear_extra();
    1826     reset_counter();
    1827 
    1828     SaveRunMeta(); // saving run_meta.txt at end of every event incase of crashes
    1829 
    1830 
    1831     bool is_last_eventID = SEventConfig::IsLastEvent(eventID) ;
    1832     if(is_last_eventID)
    1833     {
    1834         //SetRunProf( isEGPU() ? "SEvt__endOfEvent_LAST_EGPU" : "SEvt__endOfEvent_LAST_ECPU" ) ;
    1835         bool is_last_evt_instance = isLastEvtInstance() ;
    1836 
    1837         LOG(LEVEL)
    1838             << " is_last_eventID " << ( is_last_eventID ? "YES" : "NO " )
    1839             << " is_last_evt_instance " << ( is_last_evt_instance ? "YES" : "NO " )
    1840             ;
    1841 
    1842         if(is_last_evt_instance) SEvt::EndOfRun();   // invokes SaveRunMeta
    1843     }
    1844 
    1845 
    1846 }



SEvt::SaveRunMeta
~~~~~~~~~~~~~~~~~~

::

    1645 /**
    1646 SEvt::SaveRunMeta
    1647 -------------------
    1648 
    1649 Saving only at the end of run is problematic
    1650 when jobs are prone to memory failure. So
    1651 better to save at the end of every event, not
    1652 just the last.
    1653 
    1654 **/
    1655 
    1656 void SEvt::SaveRunMeta(const char* base)
    1657 {
    1658     const char* dir = RunDir(base);
    1659 
    1660     bool is_save_nothing = IsSaveNothing();
    1661 
    1662     LOG_IF(info, RUNMETA)
    1663         << " [" << SEvt__RUNMETA << "]"
    1664         << " is_save_nothing " << ( is_save_nothing ? "YES" : "NO " )
    1665         << " base " << ( base ? base : "-" )
    1666         << " dir " << ( dir ? dir : "-" )
    1667         ;
    1668 
    1669     if(!is_save_nothing) RUN_META->save(dir, "run.npy") ;
    1670 }


    1626 /**
    1627 SEvt::IsSaveNothing
    1628 --------------------
    1629 
    1630 When using OPTICKS_EVENT_MODE of Minimal or Nothing
    1631 the saving of run metadata and directory creation
    1632 can be disabled with::
    1633 
    1634     export SEvt__SAVE_NOTHING=1
    1635 
    1636 **/
    1637 
    1638 bool SEvt::IsSaveNothing() // static
    1639 {
    1640     return SEventConfig::IsMinimalOrNothing() && SAVE_NOTHING ;
    1641 }






IN the run folder above the A000 is run_meta.txt and run.npy (placeholder array)
----------------------------------------------------------------------------------

::


    (ok) A[blyth@localhost ALL1_Debug_Philox_ref1]$ cat run_meta.txt 
    SEvt__Init_RUN_META:1760593674164589,46456,8512
    source:CSGOptiX__InitEvt
    creator:CSGOptiXSMTest
    uname:Linux localhost.localdomain 5.14.0-570.37.1.el9_6.x86_64 #1 SMP PREEMPT_DYNAMIC Tue Aug 26 10:33:12 EDT 2025 x86_64 x86_64 x86_64 GNU/Linux
    CUDA_VISIBLE_DEVICES:0
    HOME:/home/blyth
    USER:blyth
    SCRIPT:cxs_min.sh
    PWD:/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_ref1
    TEST:ref1
    VERSION:1
    GEOM:J25_4_0_opticks_Debug
    ${GEOM}_GEOMList:J25_4_0_opticks_Debug_GEOMList
    OPTICKS_INTEGRATION_MODE:1
    OPTICKS_NUM_GENSTEP:10
    OPTICKS_EVENT_RELDIR:ALL${VERSION:-0}_${OPTICKS_EVENT_NAME:-none}
    OPTICKS_CUDA_PREFIX:/usr/local/cuda-12.4
    OPTICKS_NUM_EVENT:1
    OPTICKS_BUILDTYPE:Debug
    OPTICKS_EVENT_NAME:Debug_Philox_ref1
    OPTICKS_HIT_MASK:EC
    OPTICKS_MAX_PHOTON:
    OPTICKS_OPTIX_PREFIX:/cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    OPTICKS_MAX_BOUNCE:63
    OPTICKS_RUNNING_MODE:SRM_TORCH
    OPTICKS_HOME:/home/blyth/opticks
    OPTICKS_COMPUTE_ARCHITECTURES:70,89
    OPTICKS_GEANT4_PREFIX:/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Geant4/10.04.p02.juno
    OPTICKS_EVENT_MODE:HitPhotonSeq
    OPTICKS_NUM_PHOTON:M1
    OPTICKS_PREFIX:/data1/blyth/local/opticks_Debug
    OPTICKS_MAX_SLOT:M1
    OPTICKS_MAX_CURAND:
    OPTICKS_COMPUTE_CAPABILITY:70
    OPTICKS_START_INDEX:0
    OPTICKS_DOWNLOAD_CACHE:/cvmfs/opticks.ihep.ac.cn/opticks_download_cache
    OPTICKS_STTF_PATH:/data1/blyth/local/opticks_Debug/externals/imgui/imgui/extra_fonts/Cousine-Regular.ttf
    GPUMeta:-1:NVIDIA_RTX_5000_Ada_Generation
    QSim__Switches:CONFIG_Debug,NOT-CONFIG_RelWithDebInfo,NOT-CONFIG_Release,NOT-CONFIG_MinSizeRel,NOT-PRODUCTION,WITH_CHILD,WITH_CUSTOM4,PLOG_LOCAL,DEBUG_PIDX,NOT-DEBUG_TAG,NOT-RNG_XORWOW,RNG_PHILOX,NOT-RNG_PHILITEOX,
    C4Version:TBD
    optixpath:/data1/blyth/local/opticks_Debug/optix/objects-Debug/CSGOptiX_OPTIX/CSGOptiX7.ptx
    optixpath_mtime_str:2025-10-16T11:35:38..000
    optixpath_mtime:1760585738000000
    optixpath_age_secs:7939
    optixpath_age_days:0
    SEvt__BeginOfRun:1760593677804485,7316440,1220224
    SEvt__beginOfEvent_FIRST_EGPU:1760593677804634,7316440,1220224
    SEvt__setIndex_A000:1760593677804659,7316440,1220224
    SEvt__endIndex_A000:1760593678062575,8372996,1332824
    SEvt__EndOfRun:1760593678127979,8266712,1227112
    CSGOptiX__SimulateMain_HEAD:1760593674165428,46456,11200
    CSGFoundry__Load_HEAD:1760593674165461,46456,11200
    CSGFoundry__Load_TAIL:1760593677267321,5419960,883336
    CSGOptiX__Create_HEAD:1760593677267361,5419960,883336
    CSGOptiX__Create_TAIL:1760593677804424,7316440,1220224
    A000_QSim__simulate_HEAD:1760593677804471,7316440,1220224
    A000_QSim__simulate_LBEG:1760593677804798,7316440,1220672
    A000_QSim__simulate_PRUP:1760593677804804,7316440,1220672
    A000_QSim__simulate_PREL:1760593677805962,8266712,1221120
    A000_QSim__simulate_POST:1760593677959345,8266712,1225600
    A000_QSim__simulate_DOWN:1760593678062442,8372996,1332824
    A000_QSim__simulate_LEND:1760593678062471,8372996,1332824
    A000_QSim__simulate_PCAT:1760593678062500,8372996,1332824
    A000_QSim__simulate_BRES:1760593678062548,8372996,1332824
    A000_QSim__reset_HEAD:1760593678062555,8372996,1332824
    A000_QSim__reset_TAIL:1760593678129505,8266712,1227112
    A000_QSim__simulate_TAIL:1760593678129514,8266712,1227112
    CSGOptiX__SimulateMain_TAIL:1760593678129555,8266712,1227112
    (ok) A[blyth@localhost ALL1_Debug_Philox_ref1]$ 



