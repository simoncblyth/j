blyth-88-runner-fails
=======================


* https://code.ihep.ac.cn/JUNO/offline/junosw/-/jobs/21773/raw


::

    /builds/JUNO/offline/junosw/Detector/Geometry/Geometry/PMT.h:19:36: warning: overlapping comparisons always evaluate to false [-Wtautological-overlap-compare]
        return (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_WP_PMT)  or (kOFFSET_CD_SPMT<=pmtid);
                ~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~~~~~



::

     17 inline bool PMT::IsCD(int pmtid)
     18 {
     19     return (kOFFSET_CD_SPMT<=pmtid and pmtid<kOFFSET_WP_PMT)  or (kOFFSET_CD_SPMT<=pmtid);
     20 }


That is fixed in main already.



Private field not used warnings::

    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4EmLivermorePhysics.cc:140:34: warning: field 'verbose' will be initialized after base 'ToolBase' [-Wreorder-ctor]
      : G4VPhysicsConstructor(name), verbose(1)
                                     ^
    In file included from /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:7:
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:49:31: warning: private field 'm_jpmt' is not used [-Wunused-private-field]
            junoSD_PMT_v2*        m_jpmt ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:50:31: warning: private field 'm_jpmt_dbg' is not used [-Wunused-private-field]
            junoSD_PMT_v2_Debug*  m_jpmt_dbg ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:52:31: warning: private field 'm_pmthitmerger_opticks' is not used [-Wunused-private-field]
            PMTHitMerger*         m_pmthitmerger_opticks ;
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:54:31: warning: private field 'm_event_total' is not used [-Wunused-private-field]
            unsigned              m_event_total ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:55:31: warning: private field 'm_genstep_total' is not used [-Wunused-private-field]
            unsigned              m_genstep_total ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:56:31: warning: private field 'm_photon_total' is not used [-Wunused-private-field]
            unsigned              m_photon_total ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:57:31: warning: private field 'm_hit_total' is not used [-Wunused-private-field]
            unsigned              m_hit_total ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:58:31: warning: private field 'm_merged_total' is not used [-Wunused-private-field]
            unsigned              m_merged_total ; 
                                  ^
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh:59:31: warning: private field 'm_savehit_total' is not used [-Wunused-private-field]
            unsigned              m_savehit_total ; 
                                  ^






Seems Custom4 not installed, causing the error::

    1 error generated.
    gmake[2]: *** [Simulation/DetSimV2/PhysiSim/CMakeFiles/PhysiSim.dir/src/DsPhysConsOptical.cc.o] Error 1
    gmake[2]: *** Waiting for unfinished jobs....
    15 warnings generated.
    [ 91%] Linking CXX shared library ../../../lib/libElecSimAlg.so
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:28:10: fatal error: 'C4OpBoundaryProcess.hh' file not found
    #include "C4OpBoundaryProcess.hh"
             ^~~~~~~~~~~~~~~~~~~~~~~~
    2 warnings generated.
    8 warnings generated.
    1 warning and 1 error generated.
    gmake[2]: *** [Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/src/junoSD_PMT_v2.cc.o] Error 1
    gmake[2]: *** Waiting for unfinished jobs....
    In file included from /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:2:
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:134:18: warning: private field 'in2' is not used [-Wunused-private-field]
            EInside  in2 ;
