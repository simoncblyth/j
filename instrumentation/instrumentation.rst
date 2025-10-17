instrumentation
=================


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
    Binary file ./sysrap/.SProf.hh.swp matches
    ./sysrap/SEvt.cc:        SProf::Write("SEvt__EndOfRun_SProf.txt", append ) ;
    ./u4/tests/U4HitTest.cc:    SProf::Write(path, append); 
    ./notes/issues/okjob_GPU_memory_leak.rst:     183     SProf::Write("run_meta.txt", true ); // append:true 
    ./notes/issues/CSGOptiXService_impl_notes.rst:     170     SProf::Write("run_meta.txt", true ); // append:true
    zeta:opticks blyth$ 


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





