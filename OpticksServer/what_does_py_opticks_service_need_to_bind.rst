what_does_py_opticks_service_need_to_bind
============================================

Overview
-----------

* client collects gensteps and at end of event makes libcurl NP_CURL POST 
  request with response being the hits array 

* need to nanobind to very small subset of the CSGOptiX/CSGOptiX API

* adding highlevel C++ CSGOptiXService with very high level API
  suitable for easy nanobind::

      NP* CSGOptiXService::simulate(const NP* gensteps);


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








