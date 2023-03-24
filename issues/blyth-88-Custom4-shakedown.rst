blyth-88-Custom4-shakedown
=============================

* prior :doc:`blyth-88-setup-customgeant4-mini-external-package-to-avoid-circular-dependency-issue`


DONE : getting C4 to work with j/PMTSim and  U4SimulateTest
---------------------------------------------------------------

Assert caused by C4 compile not having the PMTID_STANDALONE single pmt pmtid fixup, 
so was getting pmtid -1::

    epsilon:tests blyth$ N=1 ./ph.sh dbg

    U4Recorder::BeginOfRunAction@131: 
    U4App::GeneratePrimaries@172: [ fPrimaryMode T
    U4VPrimaryGenerator::GeneratePrimaries ph (50000, 4, 4, )
    U4App::GeneratePrimaries@180: ]
    U4Recorder::BeginOfEventAction@133: 
    Assertion failed: (qe > 0 && qe < 1), function get_pmtid_qe, file /usr/local/opticks/include/PMTSim/PMTSimParamSvc/PMTSimParamData.h, line 196.
    Process 13026 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
        frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
    libsystem_kernel.dylib`__pthread_kill:
    ->  0x7fff55664b66 <+10>: jae    0x7fff55664b70            ; <+20>
        0x7fff55664b68 <+12>: movq   %rax, %rdi
        0x7fff55664b6b <+15>: jmp    0x7fff5565bae9            ; cerror_nocancel
        0x7fff55664b70 <+20>: retq   
    Target 0: (U4SimulateTest) stopped.
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff5582f080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff555c01ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x00000001002ba3c7 libU4.dylib`PMTSimParamData::get_pmtid_qe(this=0x000000010974e620, pmtid=-1, energy=0.0000029520047246000052) const at PMTSimParamData.h:196
        frame #5: 0x000000010029d0e9 libU4.dylib`PMTAccessor::get_pmtid_qe(this=0x000000010d4bff50, pmtid=-1, energy=0.0000029520047246000052) const at PMTAccessor.h:159
        frame #6: 0x000000010083e76d libCustom4.dylib`C4CustomART::doIt(this=0x000000010d4c2440, aTrack=0x00000001101017a0, (null)=0x000000010717e450) at C4CustomART.h:280
        frame #7: 0x000000010083c515 libCustom4.dylib`C4OpBoundaryProcess::PostStepDoIt(this=0x000000010d4c2100, aTrack=0x00000001101017a0, aStep=0x000000010717e450) at C4OpBoundaryProcess.cc:541
        frame #8: 0x0000000102b907db libG4tracking.dylib`G4SteppingManager::InvokePSDIP(this=0x000000010717e2c0, np=3) at G4SteppingManager2.cc:538
        frame #9: 0x0000000102b9064d libG4tracking.dylib`G4SteppingManager::InvokePostStepDoItProcs(this=0x000000010717e2c0) at G4SteppingManager2.cc:510
        frame #10: 0x0000000102b8bdaa libG4tracking.dylib`G4SteppingManager::Stepping(this=0x000000010717e2c0) at G4SteppingManager.cc:209
        frame #11: 0x0000000102ba286f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x000000010717e280, apValueG4Track=0x00000001101017a0) at G4TrackingManager.cc:126
        frame #12: 0x0000000102a6871a libG4event.dylib`G4EventManager::DoProcessing(this=0x000000010717e1f0, anEvent=0x000000010ce5ebb0) at G4EventManager.cc:185
        frame #13: 0x0000000102a69c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x000000010717e1f0, anEvent=0x000000010ce5ebb0) at G4EventManager.cc:338
        frame #14: 0x00000001029759e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x000000010717e010, i_event=0) at G4RunManager.cc:399
        frame #15: 0x0000000102975815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x000000010717e010, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #16: 0x0000000102973cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x000000010717e010, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #17: 0x000000010003e55d U4SimulateTest`U4App::BeamOn(this=0x00000001071a98d0) at U4App.h:226
        frame #18: 0x000000010003eb80 U4SimulateTest`main(argc=1, argv=0x00007ffeefbfe4b0) at U4SimulateTest.cc:32
        frame #19: 0x00007fff55514015 libdyld.dylib`start + 1
    (lldb) 


    (lldb) f 7
    frame #7: 0x000000010083c515 libCustom4.dylib`C4OpBoundaryProcess::PostStepDoIt(this=0x000000010bbf58f0, aTrack=0x000000010e8e8080, aStep=0x0000000107571020) at C4OpBoundaryProcess.cc:541
       538 	                {
       539 	                    m_custom_status = 'Y' ;
       540 	
    -> 541 	                    m_custom_art->doIt(aTrack, aStep) ;  
       542 	         
       543 	                    /**
       544 	                    m_custom_art calculates 3-way probabilities (A,R,T) that sum to 1. 
    (lldb) p m_custom_art
    (C4CustomART *) $0 = 0x000000010bbf5c30
    (lldb) f 6
    frame #6: 0x000000010083e76d libCustom4.dylib`C4CustomART::doIt(this=0x000000010bbf5c30, aTrack=0x000000010e8e8080, (null)=0x0000000107571020) at C4CustomART.h:280
       277 	#endif
       278 	
       279 	    int pmtcat = accessor->get_pmtcat( pmtid ) ; 
    -> 280 	    double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  
       281 	    // following the old junoPMTOpticalModel with "backwards" _qe always zero 
       282 	
       283 	    std::array<double,16> a_spec ; 
    (lldb) p accessor
    (PMTAccessor *) $1 = 0x000000010bbf3740
    (lldb) p pmtid
    (int) $2 = -1
    (lldb) p pmtcat
    (int) $3 = 0
    (lldb) p minus_cos_theta
    (G4double) $4 = -0.33161169492377301
    (lldb) 


    (lldb) f 4
    frame #4: 0x00000001002ba3c7 libU4.dylib`PMTSimParamData::get_pmtid_qe(this=0x00000001071c0670, pmtid=-1, energy=0.0000029520047246000052) const at PMTSimParamData.h:196
       193 	    double qe = get_pmtcat_qe(cat, energy);
       194 	    double qe_scale = m_all_pmtID_qe_scale[idx] ; 
       195 	    qe *= qe_scale ;
    -> 196 	    assert(qe > 0 && qe < 1);
       197 	    return qe ; 
       198 	}
       199 	
    (lldb) p qe
    (double) $6 = 0
    (lldb) p qe_scale
    (double) $7 = 0
    (lldb) p qe
    (double) $8 = 0
    (lldb) p idx
    (int) $9 = -1
    (lldb) 




Checking C4 debug info is present
------------------------------------

::

    In [15]: np.c_[np.where(n>5)[0], q[n>5]]
    Out[15]: 
    array([[b'579', b'TO BT SR BR SR BR SR BR SA                                                                      '],
           [b'584', b'TO BT SR BR SR BR SR BR SR BR SA                                                                '],
           [b'595', b'TO BT SR BR SR BT SA                                                                            '],
           [b'598', b'TO BT SR BR SR BR SR BR SR BR SA                                                                '],
           [b'599', b'TO BT SR BR SR BT SA                                                                            '],
           ...,
           [b'49390', b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BT SA                      '],
           [b'49391', b'TO BT SR BR SR BR SR BT SA                                                                      '],
           [b'49398', b'TO BT SR BR SR BT SA                                                                            '],
           [b'49413', b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BT SA                      '],
           [b'49416', b'TO BT SR BR SR BR SR BR SR BR AB                                                                ']], dtype='|S96')





Find a bouncer that enters PMT window::

    In [6]: q[11585]
    Out[6]: array([b'TO BT BT SR BR SR BR SR BR SR SR SR SR BR SR BR SR SA                                           '], dtype='|S96')


    In [5]: t.aux[11585,:10]
    Out[5]: 
    array([[[  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.43 ,   0.   ,   0.903,   0.   ]],

           [[  0.686,   0.032,   0.282,   0.348],
            [  0.647,   0.026,   0.327,   0.537],
            [ -0.917, 420.   ,   0.   ,   0.   ],
            [  0.437,   0.   ,   0.9  ,   0.   ]],

           [[  0.686,   0.032,   0.282,   0.348],
            [  0.647,   0.026,   0.327,   0.537],
            [ -0.917, 420.   ,   0.   ,   0.   ],
            [  0.638,   0.   ,  -0.77 ,   0.   ]],

           [[  0.304,   0.369,   0.327,   0.   ],
            [  0.647,   0.026,   0.327,   0.   ],
            [  1.   , 420.   ,   0.   ,   0.   ],
            [ -0.933,   0.   ,   0.36 ,   0.   ]],




WIP : Get C4 to work with junosw
-----------------------------------



Remove the old headers
~~~~~~~~~~~~~~~~~~~~~~~~

* replacing CustomG4OpBoundaryProcess and associated headers with C4 equivalents 

Safety copy before removal::

    epsilon:PhysiSim blyth$ cp include/Custom* ~/j/attic/PhysiSim/
    epsilon:PhysiSim blyth$ cp src/Custom* ~/j/attic/PhysiSim/
    epsilon:PhysiSim blyth$ cp include/MultiLayrStack.h ~/j/attic/PhysiSim/

    epsilon:PhysiSim blyth$ git rm src/CustomG4OpBoundaryProcess.cc include/Custom* include/MultiLayrStack.h 
    rm 'Simulation/DetSimV2/PhysiSim/include/CustomART.h'
    rm 'Simulation/DetSimV2/PhysiSim/include/CustomART_Debug.h'
    rm 'Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh'
    rm 'Simulation/DetSimV2/PhysiSim/include/MultiLayrStack.h'
    rm 'Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc'
    epsilon:PhysiSim blyth$ 


Adapt to new C4 impl
~~~~~~~~~~~~~~~~~~~~~~~

::

    epsilon:junosw blyth$ jgl CustomG4
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    epsilon:junosw blyth$ 



WIP : Front Door Config of Natural Geometry
--------------------------------------------

* TODO:DsPhysConsOptical needs to know the quadrant for FastSim switch on in only one quadrant  
* See "jcv CommonPMTManager" for explanation of POM/PMT quadrants.
* NEED A WAY TO CONFIG NaturalGeometry : THRU FRONT DOOR (declprop envvars are a PMTSIM_STANDALONE thing)
* jcv JUNODetSimModule

::

     jcv JUNODetSimModule

    0474         # == use new pmt optical model or not ==
     475         grp_pmt_op.add_argument("--pmt-optical-model", dest="pmt_optical_model", action="store_true", help=mh("Enable New PMT optical model (default is enabled)"))
     476         grp_pmt_op.add_argument("--no-pmt-optical-model", dest="pmt_optical_model", action="store_false", help=mh("Disable New PMT optical model"))
     477         grp_pmt_op.set_defaults(pmt_optical_model=True)
     478 
     479         grp_pmt_op.add_argument("--pmt-natural-geometry", dest="pmt_natural_geometry", action="store_true", help=mh("Natural 2-volume PMT geometry (default)"))
     480         grp_pmt_op.add_argument("--pmt-unnatural-geometry", dest="pmt_natural_geometry", action="store_false", help=mh("Unnatural 4-volume FastSim kludged PMT geometry"))
     481         grp_pmt_op.set_defaults(pmt_natural_geometry=True)


PMTManagers need to know the quadrant::

    1739         if args.pmt20inch_extra == "TWO":
    1740             log.info("TWO . args.pmt20inch_extra %s " % args.pmt20inch_extra)
    1741             nnvt_mcp_pmt = sim_conf.tool("NNVTMCPPMTManager/NNVTMCPPMT")
    1742             nnvt_mcp_pmt.property("FastCover").set(True)
    1743             nnvt_mcp_pmt.property("FastCoverMaterial").set("Water")
    1744             nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1745             nnvt_mcp_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    1746 
    1747             hamamatsu_pmt = sim_conf.tool("HamamatsuR12860PMTManager/HamamatsuR12860")
    1748             hamamatsu_pmt.property("FastCover").set(True)
    1749             hamamatsu_pmt.property("FastCoverMaterial").set("Water")
    1750             hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1751             hamamatsu_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    1752 
    1753         elif args.pmt20inch_extra == "TWO-mask":
    1754             log.info("TWO-mask . args.pmt20inch_extra %s " % args.pmt20inch_extra)
    1755             nnvt_mcp_pmt = sim_conf.tool("NNVTMCPPMTManager/NNVTMCPPMT_PMT_20inch")
    1756             nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1757             nnvt_mcp_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    1758             nnvt_mcp_pmt.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1759             
    1760             nnvt_mcp_mask = sim_conf.tool("NNVTMaskManager/NNVTMCPPMT")
    1761             nnvt_mcp_mask.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1762             nnvt_mcp_mask.property("UseRealMaskTail").set(args.real_mask_tail)
    1763             nnvt_mcp_mask.property("UseMaskTailOpSurface").set(args.mask_tail_surface_enabled)
    1764             
    1765             hamamatsu_pmt = sim_conf.tool("HamamatsuR12860PMTManager/HamamatsuR12860_PMT_20inch")
    1766             hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1767             hamamatsu_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    1768             hamamatsu_pmt.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1769             
    1770             hamamatsu_mask = sim_conf.tool("HamamatsuMaskManager/HamamatsuR12860")
    1771             hamamatsu_mask.property("UseRealSurface").set(args.real_surface_in_cd_enabled)
    1772             hamamatsu_mask.property("UseRealMaskTail").set(args.real_mask_tail)
    1773             hamamatsu_mask.property("UseMaskTailOpSurface").set(args.mask_tail_surface_enabled)
    1774         
        




TODO:DsPhysConsOptical needs to known quadrant also for FastSim control
--------------------------------------------------------------------------

::

     61     declProp("UsePMTOpticalModel", m_doFastSim=false); // just the fast simulation
     62     // conflating PMTOpticalModel with m_doFastSim 
     63 


::

    epsilon:issues blyth$ jgr UsePMTOpticalModel
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=false); // just the fast simulation
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=true); // just the fast simulation
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=true); 
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        #op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_any.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:            pmtmgr.property("UsePMTOpticalModel").set(True)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("UsePMTOpticalModel", m_pmt_optical_model = "old");
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("UsePMTOpticalModel").set("new")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("UsePMTOpticalModel").set("old")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmtsdmgr.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("UsePMTOpticalModel").set(True)
    epsilon:junosw blyth$ 


jcv JUNODetSimModule::

    1597     def init_detector_simulation(self, task, args):
    1598         ###################################################################################
    1599         # If user only want to run generation, then don't need to load detector simulation.
    1600         ###################################################################################
    1601         if not args.detsim:
    1602             return
    1603 
    1604         import DetSimOptions
    1605         sim_conf = None
    1606         if args.detoption == "Acrylic":
    1607             from DetSimOptions.ConfAcrylic import ConfAcrylic
    1608             acrylic_conf = ConfAcrylic(task)
    1609             acrylic_conf.configure()
    1610             sim_conf = acrylic_conf
    1611 
    1612         if sim_conf is None:
    1613             log.fatal("The sim_conf is None.")
    1614             log.fatal("Maybe the detector option %s is not supported."%args.detoption)
    1615             sys.exit(-1)
    1616 
    1617         # = detector components =
    1618         self.init_detsim_detcomp(task, args, sim_conf)
    1619         # = analysis manager control =
    1620         self.init_detsim_anamgr(task, args, sim_conf)
    1621         self.init_detsim_anamgr_fastsim(task, args, sim_conf)
    1622 
    1623         # physics list
    1624         self.init_detsim_phys(task, args, sim_conf)
    1625         # optical related
    1626         self.init_detsim_optical(task, args, sim_conf)
    1627 
    1628         # simulation framework
    1629         self.init_detsim_sim_framework(task, args, sim_conf)



    2284     def init_detsim_phys(self, task, args, sim_conf):
    2285         # = em =
    2286         em_process = sim_conf.em_process()
    2287         em_process.property("UsePositronium").set(args.positronium)
    2288         # = ion =
    2289         ion_process = sim_conf.ion_process()
    2290         ion_process.property("EnableIonPHP").set(args.enableIonPHP)
    2291         # disable the optical progress
    2292         op_process = sim_conf.optical_process()
    2293         op_process.property("OpticksMode").set(args.opticks_mode)  # see DsPhysConsOptical
    2294         op_process.property("UseCerenkov").set(args.cerenkov)
    2295         op_process.property("UseCerenkovType").set(args.cerenkov_type)
    2296         if not args.useoptical or args.voxel_fast_sim:


jcv ConfAcrylic::

    335     def optical_process(self):
    336         if self._optical_process is None:
    337             self._optical_process = self.tool("DsPhysConsOptical")
    338         return self._optical_process



Rationalize PMT/POM quadrant control::

    epsilon:junosw blyth$ jgr UseNaturalGeometry
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    declProp("UseNaturalGeometry", m_natural_geometry=false); 
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    declProp("UseNaturalGeometry", m_natural_geometry=false);
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UseNaturalGeometry").set(args.pmt_natural_geometry)
    epsilon:junosw blyth$ 




* TODO: Check U4RecorderAnaManager insitu recording 
