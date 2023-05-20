junoSD_PMT_v2_UsePMTNatural
==============================


Does junoSD_PMT_v2 needs to know UsePMTNatural ? Would need another declProp to do this
-----------------------------------------------------------------------------------------

jgl junoSD_PMT_v2::

    epsilon:junosw blyth$ jgl junoSD_PMT_v2
    ./Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Debug.h
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiency.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py
    ./Simulation/DetSimV2/AnalysisCode/include/MuonFastSimVoxel.hh
    ./Doc/oum/source/quickstart/quickstart.md
    epsilon:junosw blyth$ 


jcv PMTSDMgr::

     19 PMTSDMgr::PMTSDMgr(const std::string& name)
     20     : ToolBase(name)
     21 {
     ..
     51     declProp("UsePMTOpticalModel", m_enable_optical_model=false);
     52     declProp("UsePmtSimSvc",m_use_pmtsimsvc = true);
     53 }
     ..
     59 G4VSensitiveDetector*
     60 PMTSDMgr::getSD()
     61 {
     ..
     92     } else if (m_pmt_sd == "junoSD_PMT_v2") {
     93         junoSD_PMT_v2* sd = new junoSD_PMT_v2(objName(), m_opticksMode);
     94         // As a merger is attached to a specific SD, so also create new merger for the new SD.
     95         PMTHitMerger* pmthitmerger = new PMTHitMerger();


jcv JUNODetSimModule::

    1854         if args.pmtsd_v2:
    1855             sim_conf.enable_PMTSD_v2()
    1856             pmtsdmgr = sim_conf.pmtsd_mgr()
    1857             pmtsdmgr.property("CollEffiMode").set(args.ce_mode)
    1858             pmtsdmgr.property("CEFlatValue").set(args.ce_flat_value)
    1859             pmtsdmgr.property("OpticksMode").set(args.opticks_mode)
    1860             pmtsdmgr.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1861             pmtsdmgr.property("UsePmtSimSvc").set(args.usepmtsimsvc)



