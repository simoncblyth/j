3inch_PMT_geometry
====================

Context
----------

Most A/B comparison issues invoke photons ending at 3inch PMTs 

* :doc:`opticksMode3-2nd-wave-contents-comparison`


WIP : Standalone 3inch into ~/j/PMTSim/CMakeLists.txt
--------------------------------------------------------

* PMTSim is "virtual" package that incorporates parts of junosw for standalone investigation 

::

    102 list(APPEND SOURCES
    103 
    104      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMaskManager.cc
    105      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    106      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/NNVT_MCPPMT_PMTSolid.cc
    107 
    108      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuMaskManager.cc
    109      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    110      $ENV{JUNOTOP}/junosw/Simulation/DetSimV2/PMTSim/src/Hamamatsu_R12860_PMTSolid.cc
    111 

Contrast::

   jcv Tub3inchPMTV3Manager
   jcv HamamatsuR12860PMTManager
   jcv Tub3inchPMTV3Solid

::

    242 void
    243 Tub3inchPMTV3Manager::helper_make_solid()
    244 {   
    245     pmt_solid = m_pmtsolid_maker->GetUnionSolid(GetName() + "_pmt_solid", 1.e-3*mm);
    246     body_solid = m_pmtsolid_maker->GetEllipsoidSolid(GetName() + "_body_solid", 0.);
    247     inner1_solid = m_pmtsolid_maker->GetEllipsoidSolid(GetName()+"_inner1_solid", m_pmt_H, m_photocathode_Z, -1.*m_glass_thickness);
    248     inner2_solid = m_pmtsolid_maker->GetEllipsoidSolid(GetName()+"_inner2_solid", m_photocathode_Z, m_cntr_Z1, -1.*m_glass_thickness);
    249     cntr_solid = m_pmtsolid_maker->GetContainerSolid(GetName()+"_cntr_solid", -1.e-3*mm);
    250 }





HamamatsuR12860PMTManager has PMTSIM_STANDALONE::

     14 #ifdef PMTSIM_STANDALONE
     15 #include "IGeomManager.h"
     16 #else
     17 #include "SniperKernel/ToolBase.h"
     18 #include "DetSimAlg/IPMTElement.h"
     19 #include "Geometry/IPMTParamSvc.h"
     20 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
     21 #endif








standalone 3 inch
-----------------

::

    epsilon:include blyth$ l *3inch*
    8 -rw-r--r--  1 blyth  staff   778 Sep 22  2022 Tub3inchPMTV3Solid.hh
    8 -rw-r--r--  1 blyth  staff  2630 Sep 22  2022 Tub3inchPMTV3Manager.hh
    8 -rw-r--r--  1 blyth  staff   468 Sep 22  2022 Tub3inchPMTV2Solid.hh
    8 -rw-r--r--  1 blyth  staff  2372 Sep 22  2022 Tub3inchPMTV2Manager.hh
    8 -rw-r--r--  1 blyth  staff   332 Sep 22  2022 Tub3inchPMTSolid.hh
    8 -rw-r--r--  1 blyth  staff  2356 Sep 22  2022 Tub3inchPMTManager.hh
    8 -rw-r--r--  1 blyth  staff  2370 Sep 22  2022 Hello3inchPMTManager.hh
    8 -rw-r--r--  1 blyth  staff  2525 Sep 22  2022 HZC3inchPMTManager.hh
    epsilon:include blyth$ pwd

::

    epsilon:V1J009 blyth$ jgr PMT_3inch
    ./Simulation/GenTools/share/gtposgeomap.py:                  "PMT_3inch_body_phys": "Pyrex",
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    // * PMT_3inch_body_phys
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc:    m_volnames.push_back("PMT_3inch_body_phys");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTManager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTV2Manager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTV3Manager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      //         "PMT_3inch",
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det = dynamic_cast<IPMTElement*>(det_elem("Hello3inchPMTManager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_3inch = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTManager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_3inch = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTV2Manager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_3inch = dynamic_cast<IPMTElement*>(det_elem("Tub3inchPMTV3Manager/PMT_3inch"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      //         "PMT_3inch",
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_3inch = dynamic_cast<IPMTElement*>(det_elem("Hello3inchPMTManager/PMT_3inch"));
    ./Detector/Geometry/src/CdGeom.cc:        else if ( volPmtName.Contains("PMT_3inch") ) {
    ./Detector/Geometry/src/CdGeom.cc:    if ( TString(node->GetVolume()->GetName()).Contains("inch_inner2") ) {  // PMT_20inch_inner2 or PMT_3inch_inner2
    ./Examples/Tutorial/share/mac/GtPosGeoMapping.yaml:PMT_3inch_body_phys: Pyrex
    ./Doc/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + PMT_3inch_log_phys : 36572
    ./Doc/detsim/PMTconstruct.md:    +      IDetElement* t = det_elem("R12199PMTManager/PMT_3inch");
    ./Doc/oum/source/detsim/anaelement.md:    PMTPosAnaMgr.BeginOfRunAction   INFO:  + PMT_3inch_log_phys : 36572
    ./Doc/oum/source/detsim/PMTconstruct.md:    +      IDetElement* t = det_elem("R12199PMTManager/PMT_3inch");
    epsilon:junosw blyth$ 





