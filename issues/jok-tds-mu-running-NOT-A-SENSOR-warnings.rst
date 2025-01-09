jok-tds-mu-running-NOT-A-SENSOR-warnings
===========================================

* prior  :doc:`jok-tds-mu-running`

::

    330    local gun0="opticks"   ## input photons
    331    local gun1="gun"
    332    local gun2="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
    333    local gun3="gun --particles gamma --momentums 22.23 --momentums-interp KineticEnergy --positions 0 0 0"
    334    local gun4="gun --particles mu- --momentums 214000 --positions 0 0 0"   ## 214 GeV
    335    local gun5="gun --particles mu- --momentums  50000 --positions 0 0 0"   ##  50 GeV
    336    ## --momentums in MeV 
    337 
    338    jok-tds-inputphoton-unset 
    339 
    340    local trgs=""     ## "trgs" are arguments after the opts : eg "gun" or "opticks" 
    341    case $TEST in
    342      GUN0) trgs="$trgs $gun0" ;  jok-tds-inputphoton ;;
    343      GUN1) trgs="$trgs $gun1"  ;;
    344      GUN2) trgs="$trgs $gun2"  ;;
    345      GUN3) trgs="$trgs $gun3"  ;;
    346      GUN4) trgs="$trgs $gun4"  ;;
    347      GUN5) trgs="$trgs $gun5"  ;;
    348    esac


::

    jok-;TEST=GUN4 OIM=1 jok-tds-gdb


    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2025-01-09 16:17:27.787 INFO  [82696] [QSim::simulate@395] sslice {    0,147081,      0,37942661}
    //qcerenkov::wavelength_sampled_bndtex idx 582127 sampledRI   1.618 cosTheta   0.958 sin2Theta   0.083 wavelength 199.922 count 53 matline 35 
    //qsim::propagate_at_surface_CustomART idx 4494025 lpmtid 50838 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 5857823 lpmtid 51513 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qcerenkov::wavelength_sampled_bndtex idx 10361342 sampledRI   1.756 cosTheta   0.917 sin2Theta   0.159 wavelength 161.453 count 53 matline 35 
    //qsim::propagate_at_surface_CustomART idx 13684825 lpmtid 51397 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qcerenkov::wavelength_sampled_bndtex idx 26140230 sampledRI   1.790 cosTheta   0.913 sin2Theta   0.166 wavelength 156.726 count 55 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 26665366 sampledRI   1.792 cosTheta   0.906 sin2Theta   0.178 wavelength 159.618 count 75 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 29056747 sampledRI   1.739 cosTheta   0.951 sin2Theta   0.096 wavelength 146.145 count 65 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 29518148 sampledRI   1.768 cosTheta   0.900 sin2Theta   0.190 wavelength 148.667 count 59 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 29566423 sampledRI   1.785 cosTheta   0.947 sin2Theta   0.103 wavelength 152.396 count 56 matline 35 
    //qcerenkov::wavelength_sampled_bndtex idx 31198617 sampledRI   1.792 cosTheta   0.957 sin2Theta   0.085 wavelength 158.458 count 67 matline 35 
    //qsim::propagate_at_surface_CustomART idx 36640872 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36640874 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36640803 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36641515 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36644996 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36644854 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36645763 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36646000 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36650183 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36649222 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36647505 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36652603 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36652914 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36652859 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36646439 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36645924 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36646094 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36640503 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36658022 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 36658111 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    ...
    //qsim::propagate_at_surface_CustomART idx 37856939 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37852242 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37858990 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37856460 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37847818 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37858848 lpmtid 52266 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37858788 lpmtid 52264 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37852306 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37856622 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37858064 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART idx 37847901 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 7188954 hcMuon 0 GPU YES
    hitCollectionTT.size: 0 userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           3.12800        3.12800      0.00000      
    DetSimAlg                1           51064.06250    51064.06250  0.00000      
    Sum of junotoptask       1           51067.41797    51067.41797  6.16482      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-01-09 16:18:17,028] p82696 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:201} INFO - ]JUNOApplication.run
    [Thread 0x7fffd03dd700 (LWP 82845) exited]
    Delete G4SvcRunManager

    **************************************************
    Terminating @ localhost.localdomain on Thu Jan  9 16:18:18 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Thread 0x7fffb1396700 (LWP 84199) exited]
    [Thread 0x7fffb1b97700 (LWP 84198) exited]
    [Thread 0x7ffff7fcc740 (LWP 82696) exited]
    [Thread 0x7fffb6399700 (LWP 83292) exited]
    [New process 82696]
    [Inferior 1 (process 82696) exited normally]
    (gdb) 


::


    1742 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, RNG& rng, sctx& ctx) const
    1743 {
    1744 
    1745     const sphoton& p = ctx.p ;
    1746     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal 
    1747     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor  
    1748     //int lpmtid = p.identity ; 
    ...
    1770     if(lpmtid < 0 || lpmtid >= 17612 )
    1771     {
    1772         flag = NAN_ABORT ;
    1773 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1774         //if( ctx.idx == base->pidx ) 
    1775         printf("//qsim::propagate_at_surface_CustomART idx %7d lpmtid %d : ERROR NOT-A-SENSOR : NAN_ABORT \n", ctx.idx, lpmtid );
    1776 #endif
    1777         return BREAK ;
    1778     }


The NOT-A-SENSOR lpmtid is only a handful of values::

    52146
    52351
    52203
    52264
    52265
    52266


Add some debug::

    601 extern "C" __global__ void __closesthit__ch()
    602 {
    603     unsigned iindex = optixGetInstanceIndex() ;
    604     unsigned identity = optixGetInstanceId() ;
    605     OptixPrimitiveType type = optixGetPrimitiveType(); // HUH: getting type 0, when expect OPTIX_PRIMITIVE_TYPE_TRIANGLE 
    606 
    607 #if defined(DEBUG_PIDX)
    608     //const uint3 idx = optixGetLaunchIndex();
    609     //if(idx.x == 10 && idx.y == 10) printf("//__closesthit__ch idx(%u,%u,%u) type %d \n", idx.x, idx.y, idx.z, type); 
    610     if(identity == 52264 || identity == 52265 || identity == 52266)
    611     printf("//__closesthit__ch iindex %u type %d identity %d \n", iindex, type, identity );                    
    612 #endif




::

    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45476 type 9472 identity 52264 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //qsim::propagate_at_surface_CustomART idx 37847901 lpmtid 52265 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45476 type 9472 identity 52264 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 



::

::

    In [1]: i = np.load("inst.npy")

    In [2]: i.shape
    Out[2]: (47888, 4, 4)


    In [14]: i[45478].view(np.uint32)
    Out[14]: 
    array([[3203142446, 1061981168, 3200622543,      45478],
           [1063107267, 1056958471,          0,          4],
           [1044745549, 3198888738, 3211536716,      52266],
           [1165475471, 3319179355, 3331593432,      45477]], dtype=uint32)

    In [15]: i[45478,:,3].view(np.uint32)
    Out[15]: array([45478,     4, 52266, 45477], dtype=uint32)



Seems that its coming from WP PMTs, based on gas_idx 4::

    In [19]: np.c_[np.unique(i[:,1,3].view(np.uint32), return_counts=True)]
    Out[19]: 
    array([[    0,     1],
           [    1, 25600],
           [    2, 12615],
           [    3,  4997],
           [    4,  2400],   ## WP PMTs
           [    5,   590],
           [    6,   590],
           [    7,   590],
           [    8,   504],
           [    9,     1]])


::

    366     QAT4_METHOD int get_IAS_OptixInstance_instanceId() const
    367     {
    368         const int& sensor_identifier_1 = q2.i.w ;
    369         assert( sensor_identifier_1 >= 0 );  // 0 means not a sensor GPU side, so subtract 1 to get actual sensorId
    370         return sensor_identifier_1 ; 
    371     }
    372 
    373     /**
    374     sqat4::setIdentity
    375     -------------------
    376 
    377     Canonical usage from CSGFoundry::addInstance  where sensor_identifier gets +1 
    378     with 0 meaning not a sensor. 
    379     **/ 
    380 
    381     QAT4_METHOD void setIdentity(int ins_idx, int gas_idx, int sensor_identifier_1, int sensor_index )
    382     {
    383         assert( sensor_identifier_1 >= 0 );
    384         
    385         q0.i.w = ins_idx ;             // formerly unsigned and "+ 1"
    386         q1.i.w = gas_idx ;
    387         q2.i.w = sensor_identifier_1 ;   // now +1 with 0 meaning not-a-sensor 
    388         q3.i.w = sensor_index ; 
    389     }





::

    In [1]: 0x2500    ## OPTIX_PRIMITIVE_TYPE_CUSTOM
    Out[1]: 9472

    In [2]: 0x2531    ## OPTIX_PRIMITIVE_TYPE_TRIANGLE
    Out[2]: 9521


Look to all be CUSTOM. Note the iindex and identity seem 1-to-1::

    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45477 type 9472 identity 52265 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45477 type 9472 identity 52265 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 
    //__closesthit__ch iindex 45478 type 9472 identity 52266 


Deciding to run surface_CustomART depends on the ems enum ctx.s.optical.y:: 

    2188     bnd->fill_state(ctx.s, boundary, ctx.p.wavelength, cosTheta, ctx.idx );
    2189 
    2190     unsigned flag = 0 ; 
    2191 
    2192     int command = propagate_to_boundary( flag, rng, ctx );
    2193     /**
    2194     command possibilities:
    2195 
    2196     1. CONTINUE (eg scatter)
    2197     2. BREAK (eg absorb) 
    2198     3. BOUNDARY 
    2199 
    2200     **/
    2201 
    2202 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    2203     if( ctx.idx == base->pidx )
    2204     printf("//qsim.propagate.body idx %d bounce %d command %d flag %d s.optical.x %d s.optical.y %d \n",
    2205           ctx.idx, bounce, command, flag, ctx.s.optical.x, ctx.s.optical.y );
    2206 #endif
    2207 
    2208     if( command == BOUNDARY )
    2209     {
    2210         const int& ems = ctx.s.optical.y ;
    2211 
    2212 #if !defined(PRODUCTION) && defined(DEBUG_PIDX) 
    2213         if( ctx.idx == base->pidx )
    2214         {
    2215 #if defined(WITH_CUSTOM4)
    2216             printf("//qsim.propagate.body.WITH_CUSTOM4 idx %d  BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost );
    2217 #else
    2218             printf("//qsim.propagate.body.NOT:WITH_CUSTOM4 idx %d BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost);
    2219 #endif
    2220         }
    2221 #endif
    2222 
    2223         if( ems == smatsur_NoSurface )
    2224         {
    2225             command = propagate_at_boundary( flag, rng, ctx ) ;
    2226         }
    2227         else if( ems == smatsur_Surface )
    2228         {
    2229             command = propagate_at_surface( flag, rng, ctx ) ;
    2230         }
    2231         else if( lposcost < 0.f )  // could combine with prior, but handy for debug to keep separate
    2232         {
    2233 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    2234             if( ctx.idx == base->pidx )
    2235             printf("//qsim.propagate.body (lposcost < 0.f) idx %d bounce %d command %d flag %d ems %d \n",
    2236                      ctx.idx, bounce, command, flag, ems  );
    2237 #endif
    2238             command = propagate_at_surface( flag, rng, ctx ) ;
    2239         }
    2240         else if( ems == smatsur_Surface_zplus_sensor_A )
    2241         {
    2242             command = propagate_at_surface_Detect( flag, rng, ctx ) ;
    2243         }
    2244         else if( ems == smatsur_Surface_zplus_sensor_CustomART )
    2245         {
    2246 #if defined(WITH_CUSTOM4)
    2247             command = propagate_at_surface_CustomART( flag, rng, ctx ) ;
    2248             //command = base->custom_lut == 0u ? propagate_at_surface_CustomART( flag, rng, ctx ) : propagate_at_surface_MultiFilm(flag, rng, ctx );
    2249 
    2250 #endif



::

    P[blyth@localhost CSGFoundry]$ cat mmlabel.txt 
    2896:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual
    4:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:base_steel
    3:uni_acrylic1
    130:sPanel
    322:solidSJCLSanchor
    P[blyth@localhost CSGFoundry]$ 

::

    P[blyth@localhost CSGFoundry]$ ~/opticks/bin/cat.py meshname.txt 
    0    sTopRock_domeAir
    1    sTopRock_dome
    2    sDomeRockBox
    3    PoolCoversub
    4    Upper_LS_tube
    5    Upper_Steel_tube
    6    Upper_Tyvek_tube
    7    Upper_Chimney
    8    sBar_0
    9    sBar_1
    10   sPanelTape
    11   sPanel
    12   sPlane
    13   sWall
    14   sAirTT
    15   sExpHall
    16   sExpRockBox
    17   sTopRock
    18   GLw1.up10_up11_FlangeI_Web_FlangeII
    19   GLw1.up09_up10_FlangeI_Web_FlangeII
    ...
    293  sInnerWater
    294  sReflectorInCD

    295  mask_PMT_20inch_vetosMask
    296  PMT_20inch_veto_inner_solid_1_2
    297  PMT_20inch_veto_pmt_solid_1_2
    298  mask_PMT_20inch_vetosMask_virtual

    299  sAirGap
    300  sPoolLining
    301  sBottomRock
    302  sWorld
    P[blyth@localhost CSGFoundry]$ 



::

    P[blyth@localhost junosw]$ jgr PMT_20inch_veto
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:      IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    P[blyth@localhost junosw]$ 


jcv JUNODetSimModule::

    1902         # == enable or disable PMTs in WP ==
    1903         if not args.pmt_optical_model:
    1904             pmt_det_veto = sim_conf.tool("R12860OnlyFrontPMTManager/PMT_20inch_veto")
    1905             pmt_det_veto.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1906         if not args.wp_pmt_enabled:
    1907             wp = sim_conf.wp()
    1908             wp.property("IsVetoPMT20inchEnabled").set(args.wp_pmt_enabled)
    1909         if args.pmtsd_v2:
    1910             sim_conf.enable_PMTSD_v2()
    1911             pmtsdmgr = sim_conf.pmtsd_mgr()
    1912             pmtsdmgr.property("CollEffiMode").set(args.ce_mode)
    1913             pmtsdmgr.property("CEFlatValue").set(args.ce_flat_value)
    1914             pmtsdmgr.property("OpticksMode").set(args.opticks_mode)
    1915             pmtsdmgr.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    1916             pmtsdmgr.property("UsePmtSimSvc").set(args.usepmtsimsvc)



jcv LSExpDetectorConstruction::

    1248   // Veto PMT
    1249   if (m_veto_pmt_name == "R12860OnlyFront") {
    1250       pmt_det_veto = dynamic_cast<IPMTElement*>(det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto"));
    1251       assert (pmt_det_veto);
    1252       auto lv = pmt_det_veto->getLV();
    1253       assert (lv);
    1254   } else if (m_veto_pmt_name == "R12860OnlyFrontMask") {
    1255       IDetElement* t = det_elem("R12860OnlyFrontPMTManager/PMT_20inch_veto");
    1256       IDetElement* mask = det_elem("R12860OnlyFrontMaskManager/mask_PMT_20inch_veto");
    1257       if (t && mask) {
    1258           // build
    1259           mask->getLV();
    1260           t->getLV();
    1261           pmt_det_veto = dynamic_cast<IPMTElement*>(mask);
    1262           pmt_det_veto->inject("lMaskVirtual", t, 0);
    1263       }
    1264 
    1265       assert(pmt_det_veto);



jcv R12860OnlyFrontPMTManager::

    167 void
    168 R12860OnlyFrontPMTManager::init_mirror_surface() {
    169     if ( m_mirror_opsurf == NULL ) {
    170         // construct a static mirror surface with idealized properties
    171         G4String name;
    172         name += CommonPMTManager::GetMirrorOpticalSurfacePrefix(m_UsePMTOpticalModel, m_UsePMTOpticalModel);
    173         name += GetName();
    174         name += "_Mirror_opsurf";
    175 
    176         m_mirror_opsurf =  new G4OpticalSurface(name);
    177         m_mirror_opsurf->SetFinish(polishedfrontpainted); // needed for mirror
    178         m_mirror_opsurf->SetModel(glisur);
    179         m_mirror_opsurf->SetType(dielectric_metal);
    180         m_mirror_opsurf->SetPolish(0.999);              // a guess -- FIXME
    181         G4MaterialPropertiesTable* propMirror= NULL;
    182 
    183         G4Material *matMirror = G4Material::GetMaterial("PMT_Mirror");
    184         if (matMirror) {
    185             propMirror= matMirror->GetMaterialPropertiesTable();
    186         }
    187 
    188         if (propMirror == NULL) {
    189             G4cout << "Warning: setting PMT mirror reflectivity to 0.92 "
    190                    << "because no PMT_Mirror material properties defined" << G4endl;
    191             propMirror= new G4MaterialPropertiesTable();
    192             // propMirror->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
    193             // propMirror->AddEntry("REFLECTIVITY", 1.55*eV, 0.92);
    194             // propMirror->AddEntry("REFLECTIVITY", 15.5*eV, 0.92);
    195             auto vec = new G4MaterialPropertyVector();
    196             vec->InsertValues(1.55*eV, 0.92);
    197             vec->InsertValues(15.5*eV, 0.92);
    198             propMirror->AddProperty("REFLECTIVITY", vec);
    199         }
    200         m_mirror_opsurf->SetMaterialPropertiesTable( propMirror );
    201     }
    202 
    203 }



::

     21 void LSExpDetectorConstruction_Opticks::Setup(
     22           int opticksMode,
     23           const G4VPhysicalVolume* world,
     24           const G4VSensitiveDetector* sd,
     25           PMTParamData* ppd, 
     26           PMTSimParamData* psd,
     27           NPFold* pmtscan
     28           )
     29 {   
     30     int integrationMode = SEventConfig::IntegrationMode();
     31     bool opticksMode_valid = 
     32          ( opticksMode == 0 || opticksMode == 1 || opticksMode == 2 || opticksMode == 3 )  && opticksMode == integrationMode ;
     33     LOG_IF(fatal, !opticksMode_valid ) 
     34         << " UNEXPECTED "
     35         << " opticksMode " << opticksMode
     36         << " integrationMode " << integrationMode
     37         ;
     38     assert( opticksMode_valid );
     39 
     40     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     41     const NP* jlut = SerializeMultiFilmLUT();
     42     assert(jlut);
     43 
     44     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ; 
     45 
     46     G4CXOpticks::SetGeometry_JUNO(world, sd, jpmt, jlut ); 
     47 
     48     LOG(info) << "] WITH_G4CXOPTICKS " ; 
     49     DebugMultiFilmTable();
     50 }


     52 NPFold* LSExpDetectorConstruction_Opticks::SerializePMT( 
     53           PMTParamData* ppd, 
     54           PMTSimParamData* psd,
     55           NPFold* pmtscan 
     56      )
     57 {
     58     _PMTParamData    _ppd(*ppd) ; 
     59     _PMTSimParamData _psd(*psd) ; 
     60 
     61     NPFold* pmt_rindex = S4Material::MakePropertyFold("Pyrex,Vacuum","RINDEX") ; 
     62 
     63     NPFold* j = new NPFold ; 
     64     j->add_subfold( "PMTParamData",    _ppd.serialize() );
     65     j->add_subfold( "PMTSimParamData", _psd.serialize() );
     66     j->add_subfold( "PMT_RINDEX" ,     pmt_rindex ) ;
     67 
     68     if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     69     return j ;
     70 }


::

    P[blyth@localhost junosw]$ jcv junoSD_PMT_v2
    2 files to edit
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc

    P[blyth@localhost junosw]$ jgr setHitType
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setHitType(int i) { m_hit_type = i; }
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setHitType(m_hit_type);



    018 PMTSDMgr::PMTSDMgr(const std::string& name)
     19     : ToolBase(name)
     20 {
     21     m_merge_flag = false;
     22     m_time_window = 1000*ns;
     23 
     24     declProp("EnableMergeHit", m_merge_flag);
     25     declProp("MergeTimeWindow", m_time_window);
     26     // XXX need to switch.
     27     declProp("PMTSD", m_pmt_sd="junoSD_PMT_v2");
     28     // declProp("PMTSD", m_pmt_sd="junoSD_PMT");
     29     declProp("CollEffiMode", m_ce_mode="None");
     30 
     31     declProp("HitType", m_hit_type=1);
     32 

     91     } else if (m_pmt_sd == "junoSD_PMT_v2") {
     92         junoSD_PMT_v2* sd = new junoSD_PMT_v2(objName(), m_opticksMode);
     93         // As a merger is attached to a specific SD, so also create new merger for the new SD.
     94         PMTHitMerger* pmthitmerger = new PMTHitMerger();
     95 
     96         if (m_pmthitmerger) {
     97             G4cout << "WARNING: PMTSDMgr::m_pmthitmerger already exists." << G4endl;
     98         }
     99 
    100         m_pmthitmerger = pmthitmerger;
    101 
    102         sd->setCEMode(m_ce_mode);
    103         // if flat mode
    104         sd->setCEFlatValue(m_ce_flat_value);
    105         // func mode
    106         sd->setCEFunc(m_ce_func, m_ce_func_params);
    107         sd->setMergeFlag(m_merge_flag);
    108         sd->setMergeWindows(m_time_window);
    109         sd->setMerger(pmthitmerger);
    110         sd->setPMTParamSvc(m_pmt_param_svc);
    111         sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    112         sd->setHitType(m_hit_type);
    113         //use pmt sim svc
    114         sd->setUsePmtSimSvc(m_use_pmtsimsvc);
    115         // configure the merger
    116         pmthitmerger->setMergeFlag(m_merge_flag);
    117         pmthitmerger->setTimeWindow(m_time_window);
    118 


    1923         # pmt hit type
    1924         pmtsdmgr = sim_conf.pmtsd_mgr()
    1925         pmtsdmgr.property("HitType").set(args.pmt_hit_type)


::

    P[blyth@localhost junosw]$ jgr HitType
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        pmtsdmgr.property("HitType").set(args.pmt_hit_type)
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    if (m_pmthitmerger->hasNormalHitType()) {
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    } else if (m_pmthitmerger->hasMuonHitType()) {
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    pmtsdmgr.property("HitType").set(2)
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasNormalHitType() { return hitCollection != 0; }
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasMuonHitType() { return hitCollection_muon != 0; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setHitType(int i) { m_hit_type = i; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        int getHitType() { return m_hit_type; }
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasNormalHitType()) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasMuonHitType()) {
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("HitType", m_hit_type=1);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setHitType(m_hit_type);
    P[blyth@localhost junosw]$ 

    0433         grp_pmt_op.add_argument("--pmt-hit-type", type=int, default=1, choices=[1,2],
     434                             help=mh("1 for normal hit, 2 for muon"))



