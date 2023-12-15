missing_SLOG_logging
=======================


::

    N[blyth@localhost junosw]$ find . -name '*_LOG.hh'
    ./Simulation/DetSimV2/PMTSim/PMTSim/OK_PMTSIM_LOG.hh
    ./InstallArea/include/PMTSim/OK_PMTSIM_LOG.hh

    ./Simulation/DetSimV2/PhysiSim/PhysiSim/OK_PHYSISIM_LOG.hh
    ./InstallArea/include/PhysiSim/OK_PHYSISIM_LOG.hh
    N[blyth@localhost junosw]$ vi 



::

    N[blyth@localhost junosw]$ find . -name '*.cc' -exec grep -H OK_PMTSIM_LOG.hh {} \;
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#include "PMTSim/OK_PMTSIM_LOG.hh"
    ./Simulation/DetSimV2/PMTSim/src/OK_PMTSIM_LOG.cc:#include "PMTSim/OK_PMTSIM_LOG.hh"
    N[blyth@localhost junosw]$ 

    N[blyth@localhost junosw]$ find . -name '*.cc' -exec grep -H OK_PHYSISIM_LOG.hh {} \;
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:#include "PhysiSim/OK_PHYSISIM_LOG.hh"
    ./Simulation/DetSimV2/PhysiSim/src/OK_PHYSISIM_LOG.cc:#include "PhysiSim/OK_PHYSISIM_LOG.hh"
    N[blyth@localhost junosw]$ 



::

    303 bool DetSim0Svc::initializeOpticks()
    304 {
    305     dumpOpticks("DetSim0Svc::initializeOpticks");
    306     assert( m_opticksMode > 0);
    307 
    308 #ifdef WITH_G4CXOPTICKS
    309     // TODO: arrange logging setup earlier than this 
    310     OPTICKS_ELOG("DetSim0Svc_CXOK");
    311     OK_PMTSIM_LOG_(0) ;
    312     OK_PHYSISIM_LOG_(0) ;
    313 #else
    314     LogError << " FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS " << std::endl ;
    315     assert(0);
    316 #endif
    317     return true ;
    318 }



