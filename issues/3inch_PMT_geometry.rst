3inch_PMT_geometry
====================

Context
----------

Most A/B comparison issues invoke photons ending at 3inch PMTs 

* :doc:`opticksMode3-2nd-wave-contents-comparison`



DONE : Simtrace plotting with tub3
-------------------------------------

* u4/tests/U4SimtraceTest.sh FewPMT now works with tub3 Manager 

u4/tests/FewPMT.sh::

    export FewPMT_GEOMList=tub3LogicalPMT

::

    MODE=2 FOCUS=0,0,80 ~/opticks/u4/tests/U4SimtraceTest.sh ana



DONE : added T_CIRCLE storch.h type for shooting tub3 from every 2D direction
---------------------------------------------------------------------------------


DONE : U4SimtraceTest.sh : very clear degeneracy of the tube cyclinder 
--------------------------------------------------------------------------

::

    MODE=2 FOCUS=0,-20,65 ~/opticks/u4/tests/U4SimtraceTest.sh ana 



WIP : G4CXTest.sh comparison : very discrepant
-----------------------------------------------

::

    PICK=AB MODE=2 FOCUS=0,0,100 APID=0 BPID=0 ~/opticks/g4cx/tests/G4CXTest.sh ana


    a.CHECK : circle_inwards_100 
    b.CHECK : circle_inwards_100 
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :  4186.4951 c2n :     7.0000 c2per:   598.0707  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  4186.50/7:598.071 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT SD   ' ' 0' '  7003   4354' '617.8745' '   310    310']
     [' 1' 'TO BT SA      ' ' 1' '   237   3449' '2798.9539' '     0   5775']  ## left-right-sides 
     [' 2' 'TO BT BT SA   ' ' 2' '  1909   2162' '15.7232' '    60      0']
     [' 3' 'TO BT BT BT SD' ' 3' '   370      0' '370.0000' '  5934     -1']   ## 
     [' 4' 'TO BT BT BT SA' ' 4' '   295      0' '295.0000' '  5776     -1']   ##
     [' 5' 'TO BT BR BT SA' ' 5' '    95     13' '62.2593' '   107   1143']
     [' 6' 'TO BT BT AB   ' ' 6' '    48      9' '26.6842' '   431   1226']
     [' 7' 'TO AB         ' ' 7' '    11      7' ' 0.0000' '   336    615']
     [' 8' 'TO BT BR AB   ' ' 8' '     9      0' ' 0.0000' '  6190     -1']
     [' 9' 'TO BT BT BT AB' ' 9' '     8      0' ' 0.0000' '  5780     -1']
     ['10' 'TO BT AB      ' '10' '     7      2' ' 0.0000' '  2413   1246']
     ['11' 'TO BT BT BR AB' '11' '     3      0' ' 0.0000' '  5851     -1']
     ['12' 'TO SC SA      ' '12' '     2      3' ' 0.0000' '  1338   4018']
     ['13' 'TO SC BT BT SD' '13' '     1      0' ' 0.0000' '  1859     -1']
     ['14' 'TO BT SC AB   ' '14' '     1      0' ' 0.0000' '  6977     -1']
     ['15' 'TO SC AB      ' '15' '     0      1' ' 0.0000' '    -1   5925']
     ['16' 'TO BT BR BT AB' '16' '     1      0' ' 0.0000' '  6137     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [[' 3' 'TO BT BT BT SD' ' 3' '   370      0' '370.0000' '  5934     -1']
     [' 4' 'TO BT BT BT SA' ' 4' '   295      0' '295.0000' '  5776     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    []



Lots of B:"TO BT SA" few in A : corresponding photons mostly "TO BT BT SD"
----------------------------------------------------------------------------

* in B almost all photons from the rear are "TO BT SA" with the BT and SA positions degenerate
* zooming in can see the small shifts

::

    PICK=AB MODE=2 FOCUS=0,0,100 APID=0 BPID=0 HSEL="TO BT SA" ~/opticks/g4cx/tests/G4CXTest.sh ana

Looking at the A histories for photons that are "TO BT SA" in B::

    In [3]: np.c_[np.unique(a.q[b.q_startswith("TO BT SA")], return_counts=True)]
    Out[3]: 
    array([[b'TO BT AB                                                                                        ', b'4'],
           [b'TO BT BR AB                                                                                     ', b'9'],
           [b'TO BT BR BT AB                                                                                  ', b'1'],
           [b'TO BT BR BT SA                                                                                  ', b'68'],
           [b'TO BT BT AB                                                                                     ', b'36'],
           [b'TO BT BT BR AB                                                                                  ', b'3'],
           [b'TO BT BT BT AB                                                                                  ', b'8'],
           [b'TO BT BT BT SA                                                                                  ', b'294'],
           [b'TO BT BT BT SD                                                                                  ', b'370'],
           [b'TO BT BT SA                                                                                     ', b'2'],
           [b'TO BT BT SD                                                                                     ', b'2652'],
           [b'TO BT SC AB                                                                                     ', b'1'],
           [b'TO SC SA                                                                                        ', b'1']], dtype='|S96')


jcv Tub3inchPMTV3Manager
-------------------------

jcv Tub3inchPMTV3Solid
-------------------------

::

     08 class Tub3inchPMTV3Solid {
      9 
     10 public:
     11     // R -- bulb radius
     12     // H -- bulb equator to top size
     13     // Rc -- container radius
     14     // Zc1 -- container top z-position
     15     // Zc2 -- container bottom z-position
     16     Tub3inchPMTV3Solid(double R, double H, double Rc, double Zc1, double Zc2);
     17 
     18     G4VSolid* GetContainerSolid(G4String solidname, double dr);
     19     G4VSolid* GetEllipsoidSolid(G4String solidname, double dr);
     20     G4VSolid* GetEllipsoidSolid(G4String solidname, double Z_cut1, double Z_cut2, double dr);
     21     G4VSolid* GetUnionSolid(G4String solidname, double dr);
     22 
     23 private:
     24     double m_R;
     25     double m_H;
     26     double m_Rc;
     27     double m_Zc1;
     28     double m_Zc2;
     29 





TO BT BT SD : in B only from the front, in A lots from the back too
------------------------------------------------------------------------

::

    PICK=AB MODE=2 FOCUS=0,0,100 APID=0 BPID=0 HSEL="TO BT BT SD" ~/opticks/g4cx/tests/G4CXTest.sh ana



Almost all the A only : A:"TO BT BT BT SD" A:"TO BT BT BT SA" are B:"TO BT SA"   
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* All the 370 A:"TO BT BT BT SD" are B:"TO BT SA" 
* All but one of the 295 A:"TO BT BT BT SA" are B:"TO BT SA"

::

    In [6]: np.c_[np.unique( b.q[a.q_startswith("TO BT BT BT SD")], return_counts=True)]
    Out[6]: array([[b'TO BT SA                                                                                        ', b'370']], dtype='|S96')

    In [9]: np.c_[np.unique( b.q[a.q_startswith("TO BT BT BT SA")], return_counts=True)]
    Out[9]: 
    array([[b'TO BT SA                                                                                        ', b'294'],
           [b'TO SC AB                                                                                        ', b'1']], dtype='|S96')


Color the selected photon indices red::  

    aw = a.q_startswith_or("TO BT BT BT SD","TO BT BT BT SA")

    PICK=AB MODE=2 FOCUS=0,0,100 APID=0 BPID=0 ~/opticks/g4cx/tests/G4CXTest.sh ana






::


    PICK=A MODE=2 APID=5934 FOCUS=0,0,50 ~/opticks/g4cx/tests/G4CXTest.sh ana   ## in the back 
    PICK=A MODE=2 APID=5935 FOCUS=0,0,50 ~/opticks/g4cx/tests/G4CXTest.sh ana 

    PICK=B MODE=2 BPID=5934 FOCUS=0,0,50 ~/opticks/g4cx/tests/G4CXTest.sh ana   ## in the back 

    PICK=AB MODE=2 PIDX=5934 FOCUS=0,0,50 ~/opticks/g4cx/tests/G4CXTest.sh ana 
       A:
       B: 


    In [2]: a.q[5934]
    Out[2]: array([b'TO BT BT BT SD                                                                                  '], dtype='|S96')

    In [3]: b.q[5934]
    Out[3]: array([b'TO BT SA                                                                                        '], dtype='|S96')




    In [1]: a.q_startswith("TO BT BT BT SD")
    Out[1]: 
    array([5934, 5935, 5936, 5937, 5938, 5939, 5940, 5941, 5942, 5943, 5944, 5945, 5946, 5948, 5949, 5950, 5951, 5952, 5953, 5954, 5955, 5956, 5958, 5959, 5960, 5961, 5962, 5963, 5964, 5965, 5966, 5967,
           5969, 5970, 5971, 5972, 5973, 5974, 5975, 5976, 5977, 5978, 5979, 5980, 5981, 5982, 5983, 5984, 5985, 5986, 5987, 5988, 5989, 5990, 5991, 5992, 5993, 5994, 5995, 5996, 5997, 6000, 6001, 6002,
           6003, 6004, 6005, 6006, 6007, 6008, 6009, 6010, 6011, 6012, 6013, 6015, 6016, 6017, 6019, 6020, 6021, 6022, 6023, 6024, 6025, 6027, 6028, 6029, 6030, 6031, 6032, 6033, 6034, 6035, 6036, 6037,
           6038, 6040, 6041, 6042, 6043, 6044, 6045, 6046, 6047, 6048, 6049, 6050, 6051, 6052, 6054, 6055, 6056, 6057, 6058, 6059, 6060, 6061, 6062, 6063, 6064, 6065, 6066, 6067, 6068, 6069, 6071, 6072,
           6073, 6074, 6075, 6076, 6077, 6078, 6079, 6081, 6084, 6085, 6086, 6087, 6088, 6089, 6091, 6092, 6093, 6094, 6095, 6097, 6098, 6099, 6100, 6101, 6102, 6103, 6104, 6105, 6107, 6108, 6109, 6111,
           6112, 6113, 6114, 6117, 6118, 6119, 6120, 6121, 6122, 6123, 6124, 6126, 6127, 6129, 6130, 6131, 6132, 6133, 6134, 6135, 6138, 6139, 6141, 6142, 6143, 6146, 6147, 8852, 8853, 8854, 8855, 8857,
           8858, 8859, 8860, 8861, 8862, 8864, 8865, 8866, 8867, 8868, 8870, 8873, 8874, 8875, 8876, 8877, 8878, 8879, 8880, 8883, 8884, 8886, 8887, 8888, 8889, 8891, 8892, 8893, 8894, 8895, 8896, 8897,
           8899, 8900, 8901, 8902, 8903, 8906, 8907, 8908, 8909, 8910, 8911, 8912, 8914, 8916, 8918, 8920, 8921, 8922, 8924, 8925, 8926, 8927, 8928, 8930, 8931, 8933, 8935, 8936, 8937, 8938, 8940, 8941,
           8942, 8943, 8944, 8945, 8946, 8947, 8948, 8949, 8950, 8951, 8952, 8953, 8954, 8955, 8956, 8957, 8958, 8959, 8960, 8961, 8962, 8963, 8964, 8965, 8967, 8968, 8969, 8970, 8971, 8973, 8974, 8975,
           8976, 8977, 8978, 8979, 8980, 8983, 8985, 8986, 8987, 8988, 8989, 8990, 8991, 8992, 8993, 8994, 8995, 8996, 8997, 8998, 8999, 9000, 9002, 9003, 9004, 9005, 9006, 9007, 9008, 9009, 9010, 9011,
           9012, 9013, 9014, 9015, 9016, 9018, 9019, 9020, 9021, 9022, 9024, 9025, 9026, 9027, 9028, 9029, 9030, 9031, 9032, 9033, 9034, 9035, 9037, 9038, 9039, 9040, 9041, 9042, 9043, 9044, 9045, 9046,
           9047, 9048, 9049, 9050, 9051, 9052, 9053, 9054, 9055, 9056, 9057, 9058, 9059, 9060, 9061, 9062, 9063, 9065])








DONE : Standalone 3inch into  ~/j/PMTSim/CMakeLists.txt
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





