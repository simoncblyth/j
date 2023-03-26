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



C4 bump to 0.0.7 for duplicate target avoidance and extra basics like C4Pho.h C4Sys.h
---------------------------------------------------------------------------------------

::

    je ; vi packages/custom4.sh 
    je ; bash junoenv libs all custom4


ntsd0 check : shows junoSD_PMT_v2 issue from changed OpBoundaryProcess type 
-----------------------------------------------------------------------------

::

    Begin of Event --> 0
    Can't locate OpBoundaryProcess.
    Can't locate OpBoundaryProcess.
    Can't locate OpBoundaryProcess.
    Can't locate OpBoundaryProcess.
    Can't locate OpBoundaryProcess.
    Can't locate OpBoundaryProcess.

::

    epsilon:junosw blyth$ jgr "OpBoundaryProcess" | grep locate
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        G4cout << "Can't locate OpBoundaryProcess." << G4endl;

    jcv junoSD_PMT_v2


    epsilon:junosw blyth$ jgr enableOpticalModel
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void enableOpticalModel() { m_enable_optical_model = true; }
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:            sd->enableOpticalModel();

    jcv PMTSDMgr


Opticks build on workstation
-------------------------------

::

    - cmake/Modules/OpticksCUDAFlags.cmake : using default OPTICKS_CUDA_NVCC_DIALECT variable c++11
    -- /data/blyth/junotop/opticks/u4/tests/CMakeLists.txt : PMTFastSim_FOUND NO
    -- Configuring done
    CMake Error at /data/blyth/junotop/ExternalLibs/opticks/head/externals/share/bcm/cmake/BCMFuture.cmake:83 (_add_library):
      Target "U4" links to target "Custom4::Custom4" but the target was not
      found.  Perhaps a find_package() call is missing for an IMPORTED target, or
      an ALIAS target is missing?
    Call Stack (most recent call first):
      CMakeLists.txt:119 (add_library)


    CMake Error at tests/CMakeLists.txt:15 (add_executable):
      Target "U4VPrimaryGeneratorTest" links to target "Custom4::Custom4" but the
      target was not found.  Perhaps a find_package() call is missing for an
      IMPORTED target, or an ALIAS target is missing?


Need to install C4 into OPTICKS_PREFIX
-----------------------------------------

::

    N[blyth@localhost customgeant4]$ git pull 
    ssh_exchange_identification: Connection closed by remote host
    fatal: Could not read from remote repository.

    Please make sure you have the correct access rights
    and the repository exists.
    N[blyth@localhost customgeant4]$ git remote -v
    origin	git@github.com:simoncblyth/customgeant4.git (fetch)
    origin	git@github.com:simoncblyth/customgeant4.git (push)
    N[blyth@localhost customgeant4]$ 



Actually its better to use the same C4 that junosw is using via CMAKE_PREFIX_PATH
-------------------------------------------------------------------------------------

* exactly like must use same G4 must also use same C4 off the CMAKE_PREFIX_PATH 
* have to make sure $JUNOTOP/bashrc.sh custom4 line is the latest 

::

    [ 21%] Building CXX object CMakeFiles/U4.dir/Local_G4Cerenkov_modified.cc.o
    /data/blyth/junotop/opticks/u4/U4Physics.cc:9:10: fatal error: PMTSimParamSvc/PMTAccessor.h: No such file or directory
     #include "PMTSimParamSvc/PMTAccessor.h"
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    compilation terminated.
    make[2]: *** [CMakeFiles/U4.dir/U4Physics.cc.o] Error 1
    make[2]: *** Waiting for unfinished jobs....
    make[1]: *** [CMakeFiles/U4.dir/all] Error 2
    make: *** [all] Error 2
    === om-one-or-all make : non-zero rc 2
    === om-all om-make : ERROR bdir /data/blyth/junotop/ExternalLibs/opticks/head/build/u4 : non-zero rc 2
    === om-one-or-all make : non-zero rc 2
    N[blyth@localhost opticks]$ 


::

     06 #ifdef WITH_CUSTOM4
      7 #include "G4OpBoundaryProcess.hh"
      8 #include "C4OpBoundaryProcess.hh"
      9 #include "PMTSimParamSvc/PMTAccessor.h"
     10 #elif WITH_PMTSIM
     11 #include "PMTSimParamSvc/PMTAccessor.h"
     12 #include "PMTSimParamSvc/IPMTAccessor.h"
     13 #elif WITH_PMTFASTSIM
     14 #include "JPMT.h"
     15 #endif


N jps : missing symbol : fixed with G4USE_STD11
--------------------------------------------------


::

    [ 88%] Linking CXX executable MaterialSvcTest
    ../libPMTSim.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    collect2: error: ld returned 1 exit status
    make[2]: *** [tests/DetectorConstructionTest] Error 1
    make[1]: *** [tests/CMakeFiles/DetectorConstructionTest.dir/all] Error 2
    make[1]: *** Waiting for unfinished jobs....


::

    epsilon:issues blyth$ grep G4MTHepRandom::getTheEngine *.*
    CerenkovMinimal_clhep_link_issue.rst:    /home/blyth/opticks/examples/Geant4/CerenkovMinimal/L4Cerenkov.cc:365: undefined reference to `G4MTHepRandom::getTheEngine()'
    CerenkovMinimal_clhep_link_issue.rst:    /home/blyth/opticks/examples/Geant4/CerenkovMinimal/L4Cerenkov.cc:371: undefined reference to `G4MTHepRandom::getTheEngine()'
    CerenkovMinimal_clhep_link_issue.rst:    /home/blyth/opticks/examples/Geant4/CerenkovMinimal/L4Cerenkov.cc:379: undefined reference to `G4MTHepRandom::getTheEngine()'
    CerenkovMinimal_clhep_link_issue.rst:    /home/blyth/opticks/examples/Geant4/CerenkovMinimal/L4Cerenkov.cc:435: undefined reference to `G4MTHepRandom::getTheEngine()'
    CerenkovMinimal_clhep_link_issue.rst:    /home/blyth/opticks/examples/Geant4/CerenkovMinimal/L4Cerenkov.cc:438: undefined reference to `G4MTHepRandom::getTheEngine()'
    CerenkovMinimal_clhep_link_issue.rst:    CMakeFiles/CerenkovMinimal.dir/L4Cerenkov.cc.o:/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/include/Geant4/G4Poisson.hh:59: more undefined references to `G4MTHepRandom::getTheEngine()' follow
    CerenkovMinimal_clhep_link_issue.rst:     66 #define G4UniformRand() G4MTHepRandom::getTheEngine()->flat()
    somehow_spontaneous_missing_symbol_G4MTHepRandom_getTheEngine.rst:    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    somehow_spontaneous_missing_symbol_G4MTHepRandom_getTheEngine.rst:    ../libExtG4.so: undefined reference to `G4MTHepRandom::getTheEngine()'
    epsilon:issues blyth$ 
    epsilon:issues blyth$ 





DONE: Check U4RecorderAnaMgr insitu running of U4Recorder
-------------------------------------------------------------

jcv U4RecorderAnaMgr::

    ./Simulation/DetSimV2/AnalysisCode/include/U4RecorderAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc


     10 U4RecorderAnaMgr::U4RecorderAnaMgr(const std::string& name)
     11     : 
     12     ToolBase(name),
     13 #ifdef WITH_G4CXOPTICKS
     14     m_recorder(new U4Recorder)
     15 #else
     16     m_recorder(nullptr)
     17 #endif
     18 {
     19 }

Need to include opticks line in $JUNOTOP/bashrc.sh reconnect and rebuild.::

    jo ; ./build_Debug.sh    ## NOTICE C4 VERSION IS LATEST : 0.0.7 

Need to use ntds2 as need Opticks code such as U4 without using Opticks simulation::

    BP=U4RecorderAnaMgr::BeginOfRunAction ntds2

No need. Lots of U4Recorder logging::

    ntds2

    U4Recorder::PreUserTrackingAction_Optical@298: ]
    U4Recorder::UserSteppingAction_Optical@548: [ pv pTarget
    U4Recorder::UserSteppingAction_Optical@577:  first_flag, track 0x9bf1e420
    U4Recorder::UserSteppingAction_Optical@596:  flag 32 BULK_SCATTER is_boundary_flag 0
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (   3496.187  -4264.902    461.549     74.733)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BULK_SCATTER from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]
    U4Recorder::UserSteppingAction_Optical@548: [ pv pTarget
    U4Recorder::CollectBoundaryAux@730:  bop Y cart Y cdbg Y current_aux Y bop.m_custom_status U CustomStatus::Name Undefined
    U4Recorder::UserSteppingAction_Optical@596:  flag 2048 BOUNDARY_TRANSMIT is_boundary_flag 1
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (  -1985.951  16628.515   5730.487    189.025)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]
    U4Recorder::UserSteppingAction_Optical@548: [ pv pAcrylic
    U4Recorder::CollectBoundaryAux@730:  bop Y cart Y cdbg Y current_aux Y bop.m_custom_status U CustomStatus::Name Undefined
    U4Recorder::UserSteppingAction_Optical@596:  flag 2048 BOUNDARY_TRANSMIT is_boundary_flag 1
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (  -2016.836  16746.530   5760.301    189.678)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]


    U4Recorder::UserSteppingAction_Optical@548: [ pv NNVTMCPPMT_PMT_20inch_log_phys
    U4Recorder::CollectBoundaryAux@730:  bop Y cart Y cdbg Y current_aux Y bop.m_custom_status Y CustomStatus::Name CustomARTCalc
    U4Recorder::UserSteppingAction_Optical@596:  flag 2048 BOUNDARY_TRANSMIT is_boundary_flag 1
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (   6786.390   5913.521 -17152.485    114.912)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]
    U4Recorder::UserSteppingAction_Optical@548: [ pv NNVTMCPPMT_PMT_20inch_inner_phys
    U4Recorder::CollectBoundaryAux@730:  bop Y cart Y cdbg Y current_aux Y bop.m_custom_status Y CustomStatus::Name CustomARTCalc
    U4Recorder::UserSteppingAction_Optical@596:  flag 2048 BOUNDARY_TRANSMIT is_boundary_flag 1
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (   6908.012   6158.809 -16953.922    116.040)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]
    U4Recorder::UserSteppingAction_Optical@548: [ pv NNVTMCPPMT_PMT_20inch_log_phys
    U4Recorder::CollectBoundaryAux@730:  bop Y cart Y cdbg Y current_aux Y bop.m_custom_status U CustomStatus::Name Undefined
    U4Recorder::UserSteppingAction_Optical@596:  flag 2048 BOUNDARY_TRANSMIT is_boundary_flag 1
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime (   6908.312   6162.587 -16949.434    116.070)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]


    U4Recorder::UserSteppingAction_Optical@685: ]
    junoSD_PMT_v2::ProcessHits dumpcount 0
    U4Touchable::Desc HistoryDepth  7 TouchDepth  0 ReplicaDepth  1 ReplicaNumber 320860
     i  0 cp      0 nd      2 so PMT_3inch_body_solid_ell_ell_helper pv  PMT_3inch_body_phys
     i  1 cp 320860 nd      2 so  PMT_3inch_pmt_solid pv   PMT_3inch_log_phys
     i  2 cp      0 nd  46276 so          sInnerWater pv          pInnerWater
     i  3 cp      0 nd      1 so       sReflectorInCD pv     pCentralDetector
     i  4 cp      0 nd   4521 so      sOuterWaterPool pv      pOuterWaterPool
     i  5 cp      0 nd      1 so          sPoolLining pv          pPoolLining
     i  6 cp      0 nd      1 so          sBottomRock pv             pBtmRock


    U4Recorder::UserSteppingAction_Optical@548: [ pv pTarget
    U4Recorder::UserSteppingAction_Optical@596:  flag 8 BULK_ABSORB is_boundary_flag 0
    U4Recorder::UserSteppingAction_Optical@638: U4StepPoint::DescPositionTime ( -11886.888   -240.837   6382.626    197.803)
    U4Recorder::Check_TrackStatus_Flag@926:  step.tstat fStopAndKill BULK_ABSORB from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@685: ]
    U4Recorder::PostUserTrackingAction@136: 
    U4Recorder::PostUserTrackingAction_Optical@412: [
    U4Recorder::PostUserTrackingAction_Optical@415: fStopAndKill
    U4Recorder::PostUserTrackingAction_Optical@453: ]
    U4Debug::Save eventID 0 dir /tmp/u4debug/ntds2/000 EKEY U4Debug_SaveDir
    U4Debug::Save@32:  eventID 0 dir /tmp/u4debug/ntds2/000 EKEY U4Debug_SaveDir
    U4Cerenkov_Debug::Save@11:  dir /tmp/u4debug/ntds2/000 num_record 6
    U4Cerenkov_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 6
    U4Scintillation_Debug::Save@11:  dir /tmp/u4debug/ntds2/000 num_record 77
    U4Scintillation_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 77
    U4Hit_Debug::Save@11:  dir /tmp/u4debug/ntds2/000 num_record 28
    U4Hit_Debug::Save dir /tmp/u4debug/ntds2/000 num_record 28
    junoSD_PMT_v2::EndOfEvent@1163: [ m_opticksMode  2
    junoSD_PMT_v2_Opticks::EndOfEvent@169: [ eventID 0 m_opticksMode 2

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffd2eaded4 in G4CXOpticks::simulate (this=0x0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:338
    338	    assert(cx); 
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-25.el7_9.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) 


    (gdb) bt
    #0  0x00007fffd2eaded4 in G4CXOpticks::simulate (this=0x0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:338
    #1  0x00007fffcde8cec3 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd0af0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:185
    #2  0x00007fffcde8aaa7 in junoSD_PMT_v2::EndOfEvent (this=0x5bd02f0, HCE=0x2bc0700) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1167
    #3  0x00007fffd9bbac95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #4  0x00007fffdbcc58cd in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #5  0x00007fffcf0ef45d in G4SvcRunManager::SimulateEvent (this=0x94b1f0, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #6  0x00007fffccee3e9b in DetSimAlg::execute (this=0xb26ca0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #7  0x00007fffed6c984a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



FIXED : U4SimulateTest SEvt saving currently done in main assuming single event
-------------------------------------------------------------------------------------------

* instead move SEvt mechanics into U4Recorder BeginOfEventAction/EndOfEventAction 
* so U4Recorder holds onto SEvt pointer
* test this with U4SimulateTest running with more than one event 

::

     19 int main(int argc, char** argv)
     20 {
     21     OPTICKS_LOG(argc, argv);
     22 #ifdef WITH_PMTSIM
     23     J_PMTSIM_LOG_(0);
     24 #endif
     25     int VERSION = ssys::getenvint("VERSION", 0 );
     26     LOG(info) << "[ " << argv[0] << " " << STime::Now() << " VERSION " << VERSION ;
     27 
     28     LOG(info) << U4Recorder::Switches() ;
     29 
     30     SEvt* evt = SEvt::HighLevelCreate();
     31     U4App* app = U4App::Create() ;
     32     app->BeamOn();
     33 
     34     evt->save();   // HMM: this is assuming single event running 
     35     const char* savedir = evt->getSaveDir();
     36     U4App::SaveMeta(savedir);
     37 
     38 #if defined(WITH_PMTSIM) && defined(POM_DEBUG)
     39     PMTSim::ModelTrigger_Debug_Save(savedir) ;
     40 #else
     41     LOG(info) << "not-POM_DEBUG  "  ;
     42 #endif
     43     delete app ;
     44 
     45     LOG(info) << "] " << argv[0] << " " << STime::Now() << " VERSION " << VERSION << " savedir " << savedir ;
     46     return 0 ;
     47 }


* Moved SEvt lifecycle mechanics from U4SimulateTest main into U4App and U4Recorder


FIXED : U4Engine::SaveState assert at first track of second event : FIXED BY SKIPPING FOR OTHER THAN FIRST EVENT
-------------------------------------------------------------------------------------------------------------------

::

    U4VPrimaryGenerator::GeneratePrimaries ph (50000, 4, 4, )
    U4App::GeneratePrimaries@190: ]
    U4Recorder::BeginOfEventAction@139:  eventID 1
    Assertion failed: (states && states->shape.size() > 0), function SaveState, file /Users/blyth/opticks/u4/U4Engine.h, line 152.
    Process 45900 stopped
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff5582f080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff555c01ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x00000001002530ad libU4.dylib`U4Engine::SaveState(states=0x0000000107102d70, idx=49999) at U4Engine.h:152
        frame #5: 0x000000010025231e libU4.dylib`U4Recorder::saveOrLoadStates(this=0x00000001071b3e00, id=49999) at U4Recorder.cc:352
        frame #6: 0x000000010024edbc libU4.dylib`U4Recorder::PreUserTrackingAction_Optical(this=0x00000001071b3e00, track=0x000000010ea386b0) at U4Recorder.cc:257
        frame #7: 0x000000010024e632 libU4.dylib`U4Recorder::PreUserTrackingAction(this=0x00000001071b3e00, track=0x000000010ea386b0) at U4Recorder.cc:154
        frame #8: 0x000000010003df71 U4SimulateTest`U4App::PreUserTrackingAction(this=0x00000001071b5440, trk=0x000000010ea386b0) at U4App.h:220
        frame #9: 0x000000010003dfac U4SimulateTest`non-virtual thunk to U4App::PreUserTrackingAction(this=0x00000001071b5440, trk=0x000000010ea386b0) at U4App.h:0
        frame #10: 0x0000000102b7057d libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x0000000107189df0, apValueG4Track=0x000000010ea386b0) at G4TrackingManager.cc:94
        frame #11: 0x0000000102a3671a libG4event.dylib`G4EventManager::DoProcessing(this=0x0000000107189d60, anEvent=0x000000010aa7aaa0) at G4EventManager.cc:185
        frame #12: 0x0000000102a37c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x0000000107189d60, anEvent=0x000000010aa7aaa0) at G4EventManager.cc:338
        frame #13: 0x00000001029439e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x0000000107189b80, i_event=1) at G4RunManager.cc:399
        frame #14: 0x0000000102943815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x0000000107189b80, n_event=2, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #15: 0x0000000102941cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x0000000107189b80, n_event=2, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #16: 0x000000010003e4dd U4SimulateTest`U4App::BeamOn(this=0x00000001071b5440) at U4App.h:263
        frame #17: 0x000000010003eb34 U4SimulateTest`main(argc=1, argv=0x00007ffeefbfe460) at U4SimulateTest.cc:31
        frame #18: 0x00007fff55514015 libdyld.dylib`start + 1
    (lldb) 


    (lldb) f 6
    frame #6: 0x000000010024edbc libU4.dylib`U4Recorder::PreUserTrackingAction_Optical(this=0x00000001071b3e00, track=0x000000010ea386b0) at U4Recorder.cc:257
       254 	            << " label.desc " << label->desc() 
       255 	            ; 
       256 	
    -> 257 	        saveOrLoadStates(label->id);  // moved here as labelling happens once per torch/input photon
       258 	    }
       259 	
       260 	
    (lldb) p label
    (spho *) $0 = 0x000000010d820ce0
    (lldb) p *label
    (spho) $1 = {
      gs = 0
      ix = 49999
      id = 49999
      uc4 = (x = '\0', y = '\0', z = '\0', w = '\0')
    }
    (lldb) 





FIXED : MISSING SIZING FOR 2ND EVENT
-----------------------------------------

* fixed by moving the below from SEvt::setNumPhoton to SEvt::clear

::

     890     // moved to SEvt::clear
     891     // hostside_running_resize_done = false ;    
     892     // gather_done = false ;    // hmm perhaps should be in ::clear 


::

    U4VPrimaryGenerator::GeneratePrimaries ph (50000, 4, 4, )
    U4App::GeneratePrimaries@190: ]
    U4Recorder::BeginOfEventAction@140:  eventID 1
    SEvt::beginPhoton@1048:  not in_range  idx 49999 pho.size  0 label spho (gs:ix:id:gn   04999949999[  0,  0,  0,  0])
    Assertion failed: (in_range), function beginPhoton, file /Users/blyth/opticks/sysrap/SEvt.cc, line 1054.
    (lldb) bt
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x0000000100bc5c8b libSysRap.dylib`SEvt::beginPhoton(this=0x0000000108001000, label=0x00000001074e3770) at SEvt.cc:1054
        frame #5: 0x000000010024f0cf libU4.dylib`U4Recorder::PreUserTrackingAction_Optical(this=0x000000010745ab90, track=0x000000010e9f1da0) at U4Recorder.cc:298
        frame #6: 0x000000010024e442 libU4.dylib`U4Recorder::PreUserTrackingAction(this=0x000000010745ab90, track=0x000000010e9f1da0) at U4Recorder.cc:162
        frame #7: 0x000000010003df71 U4SimulateTest`U4App::PreUserTrackingAction(this=0x000000010745ab00, trk=0x000000010e9f1da0) at U4App.h:220
        frame #8: 0x000000010003dfac U4SimulateTest`non-virtual thunk to U4App::PreUserTrackingAction(this=0x000000010745ab00, trk=0x000000010e9f1da0) at U4App.h:0
        frame #9: 0x0000000102b7057d libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x000000010742f510, apValueG4Track=0x000000010e9f1da0) at G4TrackingManager.cc:94
        frame #10: 0x0000000102a3671a libG4event.dylib`G4EventManager::DoProcessing(this=0x000000010742f480, anEvent=0x00000001072545b0) at G4EventManager.cc:185
        frame #11: 0x0000000102a37c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x000000010742f480, anEvent=0x00000001072545b0) at G4EventManager.cc:338
        frame #12: 0x00000001029439e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x000000010742f2a0, i_event=1) at G4RunManager.cc:399
        frame #13: 0x0000000102943815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x000000010742f2a0, n_event=2, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #14: 0x0000000102941cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x000000010742f2a0, n_event=2, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #15: 0x000000010003e4dd U4SimulateTest`U4App::BeamOn(this=0x000000010745ab00) at U4App.h:263
        frame #16: 0x000000010003eb34 U4SimulateTest`main(argc=1, argv=0x00007ffeefbfe460) at U4SimulateTest.cc:31
        frame #17: 0x00007fff55514015 libdyld.dylib`start + 1
    (lldb) 


SEvt::addGenstep::

     830     bool num_photon_changed = tot_photon != evt->num_photon ;
     831 
     832     LOG(info)
     833         << " tot_photon " << tot_photon
     834         << " evt.num_photon " << evt->num_photon
     835         << " num_photon_changed " << num_photon_changed
     836         ;
     837 
     838     if(num_photon_changed)
     839     {
     840         setNumPhoton(tot_photon);
     841     }
     842 
     843     return s ;
     844 }


::

    //storch::FillGenstep storch_FillGenstep_type line  gs.type 2 
    SEvt::addGenstep@832:  tot_photon 50000 evt.num_photon 0 num_photon_changed 1
    U4VPrimaryGenerator::GeneratePrimaries ph (50000, 4, 4, )
    U4App::GeneratePrimaries@190: ]
    U4Recorder::BeginOfEventAction@140:  eventID 0
    U4Recorder::PreUserTrackingAction_Optical@282:  modulo : label->id 49000
    U4Recorder::PreUserTrackingAction_Optical@282:  modulo : label->id 48000
    ...

    //storch::FillGenstep storch_FillGenstep_radius gs.radius (  260.0000) 
    //storch::FillGenstep storch_FillGenstep_type line  gs.type 2 
    SEvt::addGenstep@832:  tot_photon 50000 evt.num_photon 50000 num_photon_changed 0
    U4VPrimaryGenerator::GeneratePrimaries ph (50000, 4, 4, )
    U4App::GeneratePrimaries@190: ]
    U4Recorder::BeginOfEventAction@140:  eventID 1





FIXED : Save error on 2nd or 3rd event : from g4state.npy 
-----------------------------------------------------------

g4state is special because its only used for first event. 
So needed to set SEvt::g4state to nullptr in SEvt::clear


::

    SEvt::save@1991:  dir /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003
    *SEvt::gatherHit@1720:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x0)
      * frame #0: 0x00007fff55564232 libsystem_c.dylib`strlen + 18
        frame #1: 0x0000000100a0e825 libSysRap.dylib`std::__1::char_traits<char>::length(__s=0x0000000000000000) at __string:215
        frame #2: 0x0000000100a0fc2c libSysRap.dylib`std::__1::basic_ostream<char, std::__1::char_traits<char> >& std::__1::operator<<<std::__1::char_traits<char> >(__os=0x00007ffeefbfbab8, __str=0x0000000000000000) at ostream:866
        frame #3: 0x0000000100aae0c9 libSysRap.dylib`NPU::_make_dict(shape=size=0, descr=0x0000000000000000) at NPU.hh:1505
        frame #4: 0x0000000100aadad3 libSysRap.dylib`NPU::_make_header(shape=size=0, descr=0x0000000000000000) at NPU.hh:1488
        frame #5: 0x0000000100aacd25 libSysRap.dylib`NP::make_header(this=0x000000010721b980) const at NP.hh:774
        frame #6: 0x0000000100ab3888 libSysRap.dylib`NP::save(this=0x000000010721b980, path_="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003/g4state.npy") const at NP.hh:4244
        frame #7: 0x0000000100b08ef6 libSysRap.dylib`NP::save(this=0x000000010721b980, dir="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003", name="g4state.npy") const at NP.hh:4263
        frame #8: 0x0000000100bf2321 libSysRap.dylib`NPFold::_save_arrays(this=0x000000010721b8f0, base="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003") at NPFold.h:801
        frame #9: 0x0000000100bd8236 libSysRap.dylib`NPFold::save(this=0x000000010721b8f0, base_="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003") at NPFold.h:781
        frame #10: 0x0000000100bbe20b libSysRap.dylib`SEvt::save(this=0x0000000108067600, dir_="$DefaultOutputDir") at SEvt.cc:2001
        frame #11: 0x0000000100bbdaac libSysRap.dylib`SEvt::save(this=0x0000000108067600) at SEvt.cc:1921
        frame #12: 0x0000000100bbd955 libSysRap.dylib`SEvt::Save() at SEvt.cc:612
        frame #13: 0x000000010024e304 libU4.dylib`U4Recorder::EndOfEventAction(this=0x00000001073e0650, event=0x00000001071e54d0) at U4Recorder.cc:158
        frame #14: 0x000000010003dd91 U4SimulateTest`U4App::EndOfEventAction(this=0x00000001073e05c0, event=0x00000001071e54d0) at U4App.h:204
        frame #15: 0x000000010003df3c U4SimulateTest`non-virtual thunk to U4App::EndOfEventAction(this=0x00000001073e05c0, event=0x00000001071e54d0) at U4App.h:0
        frame #16: 0x0000000102a36fd7 libG4event.dylib`G4EventManager::DoProcessing(this=0x00000001073b4ee0, anEvent=0x00000001071e54d0) at G4EventManager.cc:265
        frame #17: 0x0000000102a37c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x00000001073b4ee0, anEvent=0x00000001071e54d0) at G4EventManager.cc:338
        frame #18: 0x00000001029439e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x00000001073b4d00, i_event=3) at G4RunManager.cc:399
        frame #19: 0x0000000102943815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x00000001073b4d00, n_event=10, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #20: 0x0000000102941cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x00000001073b4d00, n_event=10, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #21: 0x000000010003e4dd U4SimulateTest`U4App::BeamOn(this=0x00000001073e05c0) at U4App.h:263
        frame #22: 0x000000010003eb34 U4SimulateTest`main(argc=1, argv=0x00007ffeefbfe468) at U4SimulateTest.cc:31
        frame #23: 0x00007fff55514015 libdyld.dylib`start + 1
        frame #24: 0x00007fff55514015 libdyld.dylib`start + 1
    (lldb) 



::

    (lldb) p dir
    (const char *) $0 = 0x000000010a139760 "/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003"
    (lldb) f 9
    frame #9: 0x0000000100bd8236 libSysRap.dylib`NPFold::save(this=0x000000010721b8f0, base_="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003") at NPFold.h:781
       778 	
       779 	    NP::WriteNames(base, INDEX, kk );  
       780 	
    -> 781 	    _save_arrays(base); 
       782 	
       783 	    NP::WriteNames(base, INDEX, ff, 0, true  ); // append:true : write subfold keys (without .npy ext) to INDEX  
       784 	    _save_subfold_r(base); 
    (lldb) p base
    (const char *) $1 = 0x000000010a13a870 "/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003"
    (lldb) f 8
    frame #8: 0x0000000100bf2321 libSysRap.dylib`NPFold::_save_arrays(this=0x000000010721b8f0, base="/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003") at NPFold.h:801
       798 	        }
       799 	        else
       800 	        { 
    -> 801 	            a->save(base, k );  
       802 	        }
       803 	    }
       804 	    // this motivated adding directory creation to NP::save 
    (lldb) p k
    (const char *) $2 = 0x000000010a385461 "g4state.npy"
    (lldb) p a
    (const NP *) $3 = 0x000000010721b980
    (lldb) 


::

    epsilon:tests blyth$ l /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/003/
    total 848
     56 -rw-r--r--   1 blyth  wheel   25728 Mar 25 19:14 flat.npy
      0 drwxr-xr-x  14 blyth  wheel     448 Mar 25 19:14 .
      8 -rw-r--r--   1 blyth  wheel    3328 Mar 25 19:14 tag.npy
    208 -rw-r--r--   1 blyth  wheel  102528 Mar 25 19:14 prd.npy
      8 -rw-r--r--   1 blyth  wheel    3328 Mar 25 19:14 seq.npy
    104 -rw-r--r--   1 blyth  wheel   51328 Mar 25 19:14 rec.npy
      8 -rw-r--r--   1 blyth  wheel      35 Mar 25 19:14 rec_meta.txt
    408 -rw-r--r--   1 blyth  wheel  204928 Mar 25 19:14 record.npy
      8 -rw-r--r--   1 blyth  wheel      36 Mar 25 19:14 record_meta.txt
     16 -rw-r--r--   1 blyth  wheel    6528 Mar 25 19:14 photon.npy
      8 -rw-r--r--   1 blyth  wheel      85 Mar 25 19:14 photon_meta.txt
      8 -rw-r--r--   1 blyth  wheel     224 Mar 25 19:14 genstep.npy
      8 -rw-r--r--   1 blyth  wheel      95 Mar 25 19:14 NPFold_index.txt
      0 drwxr-xr-x  33 blyth  wheel    1056 Mar 25 19:14 ..
    epsilon:tests blyth$ 



WIP : check U4RecorderAnaMgr/U4Recorder can save SEvt insitu with ntds2
---------------------------------------------------------------------------

* hmm is some SEventConfig envvars needed ? 

::

    112 ## sysrap/SEventConfig 
    113 export OPTICKS_RUNNING_MODE=$running_mode   # see SEventConfig::RunningMode
    114 export OPTICKS_MAX_BOUNCE=31                # can go upto 31 now that extended sseq.h 
    115 export OPTICKS_EVENT_MODE=StandardFullDebug
    116 export OPTICKS_G4STATE_SPEC=$num_ph:38       # default is only 1000:38 to keep state files small 
    117 


::

    Begin of Event --> 0
    U4Recorder::PreUserTrackingAction@162: 
    U4Scintillation_Debug::add@24: num_record 0
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.172896 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 1
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.0885155 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 2
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.172896 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 3
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.134004 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 4
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.0885155 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 5
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 2.86528 NumTracks 5
    SEvt::addGenstep@843:  tot_photon 1 evt.num_photon 0 num_photon_changed 1
    SEvt::addGenstep@843:  tot_photon 4 evt.num_photon 1 num_photon_changed 1
    SEvt::addGenstep@843:  tot_photon 5 evt.num_photon 4 num_photon_changed 1
    U4Recorder::PostUserTrackingAction@163: 




    U4Recorder::PreUserTrackingAction@162: 
    U4Scintillation_Debug::add@24: num_record 6
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 56.791 NumTracks 63
    SEvt::addGenstep@843:  tot_photon 55 evt.num_photon 5 num_photon_changed 1
    SEvt::addGenstep@843:  tot_photon 67 evt.num_photon 55 num_photon_changed 1
    SEvt::addGenstep@843:  tot_photon 68 evt.num_photon 67 num_photon_changed 1
    U4Recorder::PostUserTrackingAction@163: 
    U4Recorder::PreUserTrackingAction@162: 
    U4Recorder::PreUserTrackingAction_Optical@228:  track 0x9bf56780 status:fAlive resume_fSuspend NO
    U4Recorder::PreUserTrackingAction_Optical@235: [
    SEvt::beginPhoton@1071:  not in_range  idx 67 pho.size  5 label spho (gs:ix:id:gn   5   0   67[  0,  0,  0,  0])
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1077: void SEvt::beginPhoton(const spho&): Assertion `in_range' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf678853 in SEvt::beginPhoton (this=0x7413160, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1077
    #5  0x00007fffd29bfa90 in U4Recorder::PreUserTrackingAction_Optical (this=0xb27fc0, track=0x9bf56780) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:298
    #6  0x00007fffd29bf012 in U4Recorder::PreUserTrackingAction (this=0xb27fc0, track=0x9bf56780) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:162
    #7  0x00007fffceb649d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0xb4f8a0, trk=0x9bf56780)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    #8  0x00007fffcceefd39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffcd0feb00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x9bf56780)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #9  0x00007fffcee86283 in LSExpTrackingAction::PreUserTrackingAction (this=0x596b080, aTrack=0x9bf56780)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #10 0x00007fffdba8e5f0 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #11 0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #12 0x00007fffcf0ee45d in G4SvcRunManager::SimulateEvent (this=0x94b350, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #13 0x00007fffccee2e9b in DetSimAlg::execute (this=0xb26e20) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112


::

    BP=SEvt::addGenstep ntds2


    Begin of Event --> 0
    U4Recorder::PreUserTrackingAction@162: 
    U4Scintillation_Debug::add@24: num_record 0
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.172896 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 1
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.0885155 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 2
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.172896 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 3
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.134004 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 4
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 0.0885155 NumTracks 0
    U4Scintillation_Debug::add@24: num_record 5
    DsG4Scintillation::PostStepDoIt@502:  MeanNumberOfTracks 2.86528 NumTracks 5

    Breakpoint 1, SEvt::addGenstep (this=0x74132d0, q_=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:780
    (gdb) bt
    #0  SEvt::addGenstep (this=0x74132d0, q_=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:780
    #1  0x00007fffcf675e58 in SEvt::AddGenstep (q=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:596
    #2  0x00007fffd2957170 in U4::CollectGenstep_DsG4Scintillation_r4695 (aTrack=0x2bc0770, aStep=0xade280, numPhotons=1, scnt=0, ScintillationTime=4.5999999999999996)
        at /data/blyth/junotop/opticks/u4/U4.cc:154
    #3  0x00007fffcd65c788 in DsG4Scintillation::PostStepDoIt (this=0x9fd1c50, aTrack=..., aStep=...)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:635
    #4  0x00007fffdba850f9 in G4SteppingManager::InvokePSDIP(unsigned long) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffdba8556b in G4SteppingManager::InvokePostStepDoItProcs() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffdba82d3d in G4SteppingManager::Stepping() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffdba8e472 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffdbcc5389 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #9  0x00007fffcf0ee45d in G4SvcRunManager::SimulateEvent (this=0x94b3d0, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #10 0x00007fffccee2e9b in DetSimAlg::execute (this=0xb27030) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112



::

     623 
     624         G4int NumPhoton =  NumVec[scnt] ;
     625 
     626 #if (defined WITH_G4CXOPTICKS) || (defined WITH_G4OPTICKS)
     627         //NumPhoton = std::min( NumPhoton, 3 );  // for debugging purposes it sometimes helps to have less photons
     628         if(flagReemission) assert( NumPhoton == 0 || NumPhoton == 1);   // expecting only 0 or 1 remission photons
     629         bool is_opticks_genstep = NumPhoton > 0 && !flagReemission ;
     630 #endif
     631 
     632 #ifdef WITH_G4CXOPTICKS
     633         if(is_opticks_genstep && (m_opticksMode > 0))
     634         {
     635             U4::CollectGenstep_DsG4Scintillation_r4695( &aTrack, &aStep, NumPhoton, scnt, ScintillationTime);
     636         }
     637 #elif WITH_G4OPTICKS
     638         CGenstep gs ;
     639         if(is_opticks_genstep && (m_opticksMode > 0))
     640         {
     641             gs = G4Opticks::Get()->collectGenstep_DsG4Scintillation_r4695( &aTrack, &aStep, NumPhoton, scnt, ScintillationTime);
     642         }
     643 #endif
     644 
     645          if( m_opticksMode != 1 )
     646          {
     647 
     648          for(G4int i = 0 ; i < NumPhoton ; i++) {
     649 #ifdef WITH_G4CXOPTICKS
     650            U4::GenPhotonBegin(i);
     651 #elif WITH_G4OPTICKS
     652            G4Opticks::Get()->setAlignIndex( ancestor_id > -1 ? ancestor_id : gs.offset + i );  // aka photon_id
     653 #endif
     654            G4double sampledEnergy;


::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    U4Recorder::BeginOfEventAction@141:  eventID 0
    Begin of Event --> 0
    SEvt::addGenstep@845:  tot_photon 1 evt.num_photon 0 num_photon_changed 1 gs.size 1 genstep.size 1 numphoton_collected 1 tot_photon 1 s.index 0 s.photons 1 s.offset 0 s.gentype 5 s.desc sgs: idx   0 pho     1 off      0 typ DsG4Scintillation_r4695
    SEvt::addGenstep@845:  tot_photon 4 evt.num_photon 1 num_photon_changed 1 gs.size 2 genstep.size 2 numphoton_collected 4 tot_photon 4 s.index 1 s.photons 3 s.offset 1 s.gentype 5 s.desc sgs: idx   1 pho     3 off      1 typ DsG4Scintillation_r4695
    SEvt::addGenstep@845:  tot_photon 5 evt.num_photon 4 num_photon_changed 1 gs.size 3 genstep.size 3 numphoton_collected 5 tot_photon 5 s.index 2 s.photons 1 s.offset 4 s.gentype 5 s.desc sgs: idx   2 pho     1 off      4 typ DsG4Scintillation_r4695
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     4 seq  
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     3 seq  
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     3 seq  
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     2 seq  
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     2 seq  
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     1 seq  
    U4Recorder::PreUserTrackingAction_Optical@282:  modulo : label->id 0
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     0 seq  
    U4Recorder::PreUserTrackingAction_Optical@282:  modulo : label->id 0
    U4Recorder::PostUserTrackingAction_Optical@455:  l.id     0 seq  
    SEvt::addGenstep@845:  tot_photon 55 evt.num_photon 5 num_photon_changed 1 gs.size 4 genstep.size 4 numphoton_collected 55 tot_photon 55 s.index 3 s.photons 50 s.offset 5 s.gentype 5 s.desc sgs: idx   3 pho    50 off      5 typ DsG4Scintillation_r4695
    SEvt::addGenstep@845:  tot_photon 67 evt.num_photon 55 num_photon_changed 1 gs.size 5 genstep.size 5 numphoton_collected 67 tot_photon 67 s.index 4 s.photons 12 s.offset 55 s.gentype 5 s.desc sgs: idx   4 pho    12 off     55 typ DsG4Scintillation_r4695
    SEvt::addGenstep@845:  tot_photon 68 evt.num_photon 67 num_photon_changed 1 gs.size 6 genstep.size 6 numphoton_collected 68 tot_photon 68 s.index 5 s.photons 1 s.offset 67 s.gentype 5 s.desc sgs: idx   5 pho     1 off     67 typ DsG4Scintillation_r4695
    SEvt::beginPhoton@1082:  not in_range  idx 67 pho.size  5 label spho (gs:ix:id:gn   5   0   67[  0,  0,  0,  0])
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1088: void SEvt::beginPhoton(const spho&): Assertion `in_range' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) 


In attempt to fix this:

1. reorganized SEvt::hostside_running_resize_done signalling to work with real gensteps, 
   not just fake torch ones where have only one big genstep in each event  


Seems to work::

    SEvt::addGenstep@843:  tot_photon 9714 evt.num_photon 9508 num_photon_changed 1 gs.size 158 genstep.size 158 numphoton_collected 9714 tot_photon 9714 s.index 157 s.photons 206 s.offset 9508 s.gentype 5 s.desc sgs: idx 157 pho   206 off   9508 typ DsG4Scintillation_r4695
    SEvt::addGenstep@843:  tot_photon 9790 evt.num_photon 9714 num_photon_changed 1 gs.size 159 genstep.size 159 numphoton_collected 9790 tot_photon 9790 s.index 158 s.photons 76 s.offset 9714 s.gentype 5 s.desc sgs: idx 158 pho    76 off   9714 typ DsG4Scintillation_r4695
    SEvt::addGenstep@843:  tot_photon 9807 evt.num_photon 9790 num_photon_changed 1 gs.size 160 genstep.size 160 numphoton_collected 9807 tot_photon 9807 s.index 159 s.photons 17 s.offset 9790 s.gentype 5 s.desc sgs: idx 159 pho    17 off   9790 typ DsG4Scintillation_r4695
    SEvt::addGenstep@843:  tot_photon 9810 evt.num_photon 9807 num_photon_changed 1 gs.size 161 genstep.size 161 numphoton_collected 9810 tot_photon 9810 s.index 160 s.photons 3 s.offset 9807 s.gentype 5 s.desc sgs: idx 160 pho     3 off   9807 typ DsG4Scintillation_r4695
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


But now have cleanup error
-----------------------------

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



