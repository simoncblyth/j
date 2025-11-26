boost python error at finalization
====================================


::

    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] photonNuclear
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 7048008.50 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 7048008.50 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.28800        1.28800      0.00021      
    DetSimAlg                1           7048118.50000  7048118.500000.00000      
    Sum of junotoptask       1           7048120.00000  7048120.000000.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-25 23:14:20,924] p1726377 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1.txt', use_event_time_from_generator=False)
    == Buffer Memory Management ==
     == PMTSimParamSvc == 
    GENTOOL MODE:  hepevt
    3inch PMT type:  Tub3inchV3
    WARNING: mac file run.mac does not exist.
    HepEvt2HepMC Dtor called begin
    HepEvt2HepMC Dtor called end
    Delete G4SvcRunManager
    corrupted size vs. prev_size
     *** Break *** abort
    ^Czhenning_double_muon/detsim.sh - ERROR FOM tut_detsim.py
    A[blyth@localhost j]$ 


::

      1 #include "G4Svc/G4SvcRunManager.h"
      2 #include <iostream>
      3 
      4 G4SvcRunManager::G4SvcRunManager()
      5     : G4RunManager(){
      6     std::cout << "Create G4SvcRunManager" << std::endl;
      7 }   
      8 
      9 G4SvcRunManager::~G4SvcRunManager() {
     10     std::cout << "Delete G4SvcRunManager" << std::endl;
     11 }
     12 


::

    A[blyth@localhost junosw]$ jgr PMTSimParamSvc | grep ==
    ./Examples/Tutorial/python/Tutorial/JUNOEventRecModule.py:        # print(" == PMTSimParamSvc == ")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        print(" == PMTSimParamSvc == ")
    ./Reconstruction/OMILREC/share/tut_calib2rec.py:        print(" == PMTSimParamSvc == ")
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    print(" == PMTSimParamSvc == ")
    A[blyth@localhost junosw]$ 









::


    2025-11-25 18:55:04.016 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    -------- WWWW ------- G4Exception-START -------- WWWW -------
    *** G4Exception : Warning
          issued by : G4Step::GetDeltaEnergy()
    This method is obsolete and will be removed soon
    *** This is just a warning message. ***
    -------- WWWW -------- G4Exception-END --------- WWWW -------

     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [61710629]@[PMT_3inch_inner2_phys] (-9293.64, 4609.02, -16390.59, 297.92)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [64010277]@[PMT_3inch_inner1_phys] (-9422.46, 4721.79, -16260.01, 286.39)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [80534704]@[pAcrylic] (-15507.47, 8096.74, -3414.09, 291.94)  step number >= 1000
     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [155573108]@[PMT_3inch_inner2_phys] (13792.75, 11884.84, 6636.63, 1001.48)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [160066560]@[PMT_3inch_inner1_phys] (-9235.43, 4624.44, -16394.77, 314.80)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [196134319]@[PMT_3inch_cntr_phys] (-9263.56, 4616.93, -16408.10, 257.26)  step number >= 1000
    2025-11-25 21:02:07.311 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 6474451 GPU NO
    2025-11-25 21:02:07.311 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 6474451 GPU NO
    hitCollectionTT.size: 102	userhitCollectionTT.size: 51
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-11-25 13:02:08.030725000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-11-25 13:02:13.841446000Z
    end of event action 
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 30150.00 / 30150.00
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 648
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] photonNuclear
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hadElastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] neutronInelastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] nCapture
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 7629856.00 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 7629856.00 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.42300        1.42300      0.00033      
    DetSimAlg                1           7629951.00000  7629951.000000.00000      
    Sum of junotoptask       1           7629952.00000  7629952.00000495.74187    
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-25 21:02:14,041] p748691 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1.txt', use_event_time_from_generator=False)
    == Buffer Memory Management ==
     == PMTSimParamSvc == 
    GENTOOL MODE:  hepevt
    3inch PMT type:  Tub3inchV3
    WARNING: mac file run.mac does not exist.
    [Thread 0x7fffcd5ff640 (LWP 748706) exited]
    HepEvt2HepMC Dtor called begin
    HepEvt2HepMC Dtor called end
    Delete G4SvcRunManager
    double free or corruption (!prev)

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
    #4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
    #5  0x00007ffff7497c7c in _int_free () from /lib64/libc.so.6
    #6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
    #7  0x00007ffff79b0b2a in _PyObject_Free (ctx=<optimized out>, p=<optimized out>) at Objects/obmalloc.c:2285
    #8  _PyObject_Free (ctx=<optimized out>, p=<optimized out>) at Objects/obmalloc.c:2276
    #9  0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #10 dict_dealloc (mp=0x7ffff7770d80) at Objects/dictobject.c:2378
    #11 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #12 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #13 insertdict (mp=mp@entry=0x7ffff7793440, key=0x7ffff76b56b0, hash=2349690666635389043, value=value@entry=0x7ffff7c5dca0 <_Py_NoneStruct>) at Objects/dictobject.c:1304
    #14 0x00007ffff799b2f2 in _PyDict_SetItem_Take2 (value=0x7ffff7c5dca0 <_Py_NoneStruct>, key=<optimized out>, mp=0x7ffff7793440) at Objects/dictobject.c:1886
    #15 0x00007ffff79aa917 in _PyModule_ClearDict (d=0x7ffff7793440) at Objects/moduleobject.c:613
    #16 0x00007ffff79aabfe in _PyModule_Clear (m=m@entry=0x7ffff76efc40) at Objects/moduleobject.c:582
    #17 0x00007ffff7a8fcea in finalize_modules_clear_weaklist (verbose=0, weaklist=0x7ffff7e6b280, interp=0x7ffff7d5f3b8 <_PyRuntime+58936>) at Python/pylifecycle.c:1499
    #18 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1581
    #19 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #20 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #21 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #22 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefde0) at Modules/main.c:714
    #23 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #24 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #25 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #26 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.
     *** Break *** abort
    [Detaching after vfork from child process 1724141]






Contrast with successful termination, ojt::

    unotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 137.33 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 137.33 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.17600        1.17600      0.00024      
    DetSimAlg                1           139.53200      139.53200    0.00000      
    Sum of junotoptask       1           140.71100      140.71100    0.02879      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-26 16:34:11,852] p1806637 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1806660) exited]
    Delete G4SvcRunManager
    2025-11-26 16:34:12.017 INFO  [1806637] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@118] junoSD_PMT_v2_Opticks::desc WITH_G4CXOPTICKS  WITH_G4CXOPTICKS_EPH  m_opticksMode 1 m_hit_type 2 m_merged_total 0 m_savehit_total 0 m_gpu_simulation YES

    **************************************************
    Terminating @ localhost.localdomain on Wed Nov 26 16:34:12 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Thread 0x7fffb4bfe640 (LWP 1806718) exited]
    [Thread 0x7fffbcfff640 (LWP 1806675) exited]
    [Thread 0x7ffff7ecc4c0 (LWP 1806637) exited]
    [Thread 0x7fffb53ff640 (LWP 1806717) exited]
    [New process 1806637]
    [Inferior 1 (process 1806637) exited normally]
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libnvidia-gpucomp-580.82.07-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 


Look for termination stack::

    BP=junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks ojt


::

    2025-11-26 16:49:28,660] p1808117 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1808135) exited]
    Delete G4SvcRunManager

    Thread 1 "python" hit Breakpoint 1.2, junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks (this=0xa631eb0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:122
    122	}
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libnvidia-gpucomp-580.82.07-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks (this=0xa631eb0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:122
    #1  0x00007fffbd16333e in junoSD_PMT_v2::~junoSD_PMT_v2 (this=0x69ad820, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:145
    #2  0x00007fffbd1633d0 in junoSD_PMT_v2::~junoSD_PMT_v2 (this=0x69ad820, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:147
    #3  0x00007fffc4d703f6 in G4SDStructure::~G4SDStructure() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #4  0x00007fffc4d6e826 in G4SDManager::~G4SDManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #5  0x00007fffc67da6f0 in G4RunManagerKernel::~G4RunManagerKernel() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #6  0x00007fffc67db069 in G4RunManagerKernel::~G4RunManagerKernel() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007fffc67cc216 in G4RunManager::~G4RunManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007fffe058459f in G4SvcRunManager::~G4SvcRunManager (this=0x667ee60, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #9  0x00007fffe05845ba in G4SvcRunManager::~G4SvcRunManager (this=0x667ee60, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #10 0x00007fffcf9766db in G4Svc::~G4Svc (this=0x6722450, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #11 0x00007fffcf97672e in G4Svc::~G4Svc (this=0x6722450, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #12 0x00007fffd0adf513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd0adfe0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd0af7b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffd0af4f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #17 0x00007fffdf0b9d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffe9d63290) at Objects/typeobject.c:1463
    #19 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #20 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #21 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #22 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff770f050) at Objects/typeobject.c:1433
    #23 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #24 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #25 free_keys_object (keys=0x7ffff7e7fd20) at Objects/dictobject.c:664
    #26 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #27 dict_dealloc (mp=0x7ffff76e50c0) at Objects/dictobject.c:2378
    #28 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #29 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #30 module_dealloc (m=0x7ffff76e1b20) at Objects/moduleobject.c:699
    #31 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #32 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #33 insertdict (mp=0x7ffff7e49340, key=0x7ffff76e5130, hash=-961337612909165183, value=<optimized out>) at Objects/dictobject.c:1304
    #34 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e49340) at Python/pylifecycle.c:1415
    #35 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #36 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #37 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #38 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #39 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeb580) at Modules/main.c:714
    #40 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #41 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #42 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #43 0x0000000000401075 in _start ()











Q: where does "double free or corruption (!prev)" come from
A: libc probably



Your crash is a classic **double free / memory corruption** that happens during
Python interpreter shutdown (`Py_FinalizeEx()`), right after your Geant4-based
C++ code has cleaned up its own objects (you see "Delete G4SvcRunManager" just
before the abort).

This specific pattern — everything works fine until the very end of the Python
process, and then it explodes with a double free inside Python’s object
allocator while clearing modules — almost always means:

**A Boost.Python-wrapped C++ object that holds a raw pointer to a
heap-allocated object is being destroyed after the object it points to has
already been deleted by the C++ side (usually Geant4 or your own singleton run
manager).**

### Most common real-world causes in Geant4 + Boost.Python setups

1. **G4RunManager (or your G4SvcRunManager) is deleted on the C++ side**, but
some Boost.Python-exposed object still holds a raw pointer (or a
`std::unique_ptr` that was moved out) to it or to some object owned by it
(G4VPhysicalVolume, G4LogicalVolume, G4Material, G4UserAction classes, etc.).

2. You have static/global Boost.Python objects (very common with
`BOOST_PYTHON_MODULE`) whose lifetime extends to the end of the program. When
Python shuts down, it destroys the module dictionary → destroys those wrapper
objects → they try to delete or access already-deleted C++ objects →
use-after-free → Python’s obmalloc gets corrupted → double free during
finalization.

3. You are using `boost::python::object` or `boost::python::dict` static
variables, or you keep references to Python objects inside long-lived C++
objects that survive Geant4 cleanup.

4. You expose user actions (G4UserRunAction, G4UserEventAction, etc.) with
`class_<G4UserRunAction, boost::noncopyable>("G4UserRunAction", no_init)` and
the Python side creates instances that outlive the G4RunManager (which deletes
the actions in its destructor).

### Proven fixes that solve this 99% of the time

#### 1. Destroy all Python-side Geant4 objects BEFORE deleting the run manager
```python
# Critical: delete in this order
del my_event_action
del my_run_action
del my_stepping_action
del my_detector
# ... any other Python objects that wrap C++ Geant4 objects

# Force garbage collection so Boost.Python destructors run immediately
import gc
gc.collect()

# NOW delete the run manager on C++ side
g4svc.deleteRunManager()   # or however you trigger the C++ cleanup
```

#### 2. Make sure your BOOST_PYTHON_MODULE does NOT hold static boost::python objects
Bad:
```cpp
BOOST_PYTHON_MODULE(mymodule) {
    static SomeWrapper wrapper;   // lives forever → destroyed after Geant4 cleanup
    ...
}
```

Good: only register classes, never keep static wrapper instances.

#### 3. Use call policies or holder types that prevent ownership issues
For user actions:
```cpp
class_<MyRunAction, MyRunAction*, boost::noncopyable>
    ("MyRunAction", init<>())
    .def("GenerateRun", &MyRunAction::GenerateRun)
    ;
// Do NOT give Boost.Python ownership of the pointer
// Geant4 owns it, not Python
```

Or explicitly tell Boost.Python the Python object does not own the C++ object:
```cpp
class_<G4RunManager, boost::noncopyable>("G4RunManager", no_init)
    .add_property("instance", make_function(
        &G4RunManager::GetRunManager,
        return_internal_reference<>()))
    ;
```

#### 4. Force Python reference count to drop to zero before C++ cleanup
If you have a global/module-level variable in Python that holds the run manager or actions, do:
```python
# At the very end of your script
MyModule.runManager = None
MyModule.detector   = None
import gc; gc.collect()
```

#### 5. If you use a singleton G4SvcRunManager, delete it as early as possible
```cpp
// In your shutdown function that is called from Python
void G4Svc::shutdown() {
    delete G4RunManager::GetRunManager();  // or your own
    G4RunManager::DeleteInstance();       // if you use that pattern
    // Do this BEFORE Python starts clearing modules
}
```

Then call that function explicitly from Python before exit.

### Quick checklist for your case

- [ ] You have Python variables holding Geant4 actions/detector → set them to None + gc.collect()
- [ ] You delete G4SvcRunManager while Python wrapper objects are still alive → reverse the order
- [ ] Your Boost.Python module has static or global wrapper objects → remove them
- [ ] You use `return_internal_reference<>()` or `with_custodian_and_ward` where needed

Do the explicit Python-side deletion + gc.collect() first — in 90% of Geant4 + Boost.Python crashes I’ve seen exactly like yours, that alone fixes it.

If it still crashes after that, let me know exactly how you expose G4SvcRunManager and the user actions, and I’ll point out the exact line that needs the ownership policy fix.








::

    A[blyth@localhost junosw]$ jgr G4Svc
    ./Doc/detsim/structures.md:    * `G4Svc`
    ./Doc/oum/source/detsim/structures.md:    * `G4Svc`
    ./Simulation/DetSimV2/CMakeLists.txt:add_subdirectory(G4Svc)
    ./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    # == G4Svc ==
    ./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    # == G4Svc ==
    ./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimAlg/CMakeLists.txt:        G4SvcLib
    ./Simulation/DetSimV2/DetSimAlg/DetSimAlg/DetSimAlg.h:#include "G4Svc/G4SvcRunManager.h"
    ./Simulation/DetSimV2/DetSimAlg/DetSimAlg/DetSimAlg.h:        G4SvcRunManager* run_manager;
    ./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:#include "G4Svc/IG4Svc.h"
    ./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:    declProp("G4Svc", m_g4svc_name="G4Svc");
    ./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:    SniperPtr<IG4Svc> g4svc(*getParent(), m_g4svc_name);
    ./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:        LogError << "Failed to Load the G4Svc " << m_g4svc_name
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        self._g4svc = self._task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py:# == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py:Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:            # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:            self._g4svc = self._task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_any.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/pyjob.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/share/pyjob.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    # == G4Svc ==
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    Sniper.loadDll("libG4Svc.so")
    ./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    g4svc = task.createSvc("G4Svc")
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:PKG (G4Svc
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:    SHARED # G4SvcLib
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:        src/IG4Svc.cc
    ./Simulation/DetSimV2/G4Svc/CMakeLists.txt:        src/G4SvcRunManager.cc
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#ifndef G4Svc_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#define G4Svc_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#include "G4Svc/IG4Svc.h"
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:class G4Svc: public IG4Svc, public SvcBase {
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4Svc(const std::string& name);
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        ~G4Svc();
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4SvcRunManager* getRunMgr();
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4SvcRunManager* m_runmgr;
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:#ifndef G4SvcRunManager_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:#define G4SvcRunManager_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:class G4SvcRunManager: public G4RunManager {
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:        G4SvcRunManager();
    ./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:        ~G4SvcRunManager();
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#ifndef IG4Svc_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#define IG4Svc_h
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#include "G4Svc/G4SvcRunManager.h"
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:class IG4Svc {
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:        virtual ~IG4Svc() = 0;
    ./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:        virtual G4SvcRunManager* getRunMgr()=0;
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:#include "G4Svc/G4Svc.h"
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:#include "G4Svc/G4SvcRunManager.h"
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:DECLARE_SERVICE(G4Svc);
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4Svc::G4Svc(const std::string& name)
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    LogDebug << "Create G4SvcRunManager in G4Svc" << std::endl;
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    m_runmgr = new G4SvcRunManager;
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4Svc::~G4Svc()
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    LogDebug << "Delete G4SvcRunManager in G4Svc" << std::endl;
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:bool G4Svc::initialize() {
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:bool G4Svc::finalize() {
    ./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4SvcRunManager* G4Svc::getRunMgr()
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:#include "G4Svc/G4SvcRunManager.h"
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:G4SvcRunManager::G4SvcRunManager() 
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:    std::cout << "Create G4SvcRunManager" << std::endl;
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:G4SvcRunManager::~G4SvcRunManager() {
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:    std::cout << "Delete G4SvcRunManager" << std::endl;
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::initializeRM() {
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::SimulateEvent(int i_event) {
    ./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::finalizeRM() {
    ./Simulation/DetSimV2/G4Svc/src/IG4Svc.cc:#include "G4Svc/IG4Svc.h"
    ./Simulation/DetSimV2/G4Svc/src/IG4Svc.cc:IG4Svc::~IG4Svc()










::

      1 #ifndef G4SvcRunManager_h
      2 #define G4SvcRunManager_h
      3 
      4 #include "G4RunManager.hh"
      5 
      6 class G4SvcRunManager: public G4RunManager {
      7     public:
      8         G4SvcRunManager();
      9         ~G4SvcRunManager();
     10 
     11         bool initializeRM();
     12         bool SimulateEvent(int i_event);
     13         bool finalizeRM();
     14 
     15 };
     16 
     17 #endif



      1 #include "G4Svc/G4SvcRunManager.h"
      2 #include <iostream>
      3 
      4 G4SvcRunManager::G4SvcRunManager() 
      5     : G4RunManager(){
      6     std::cout << "Create G4SvcRunManager" << std::endl;
      7 }   
      8 
      9 G4SvcRunManager::~G4SvcRunManager() {
     10     std::cout << "Delete G4SvcRunManager" << std::endl;
     11 }
     12 
     13 // * initializeRM and finalizeRM is based G4RunManager::BeamOn
     14 // * SimulateEvent is based on G4RunManager::DoEventLoop
     15 
     16 bool G4SvcRunManager::initializeRM() {
     17   G4bool cond = ConfirmBeamOnCondition();
     18   if(cond)
     19   {
     20     ConstructScoringWorlds();
     21     RunInitialization();
     22     return true;
     23   }
     24   return false;
     25 }
     26 
     27 bool G4SvcRunManager::SimulateEvent(int i_event) {
     28     currentEvent = GenerateEvent(i_event);
     29     eventManager->ProcessOneEvent(currentEvent);
     30     AnalyzeEvent(currentEvent);
     31     UpdateScoring();
     32     StackPreviousEvent(currentEvent);
     33     currentEvent = 0;
     34 
     35     if(runAborted) return false;
     36     return true;
     37 
     38 }
     39 
     40 bool G4SvcRunManager::finalizeRM() {
     41     RunTermination();
     42     return true;
     43 }





[blyth@localhost junosw]$ jgr G4Svc
./Doc/detsim/structures.md:    * `G4Svc`
./Doc/oum/source/detsim/structures.md:    * `G4Svc`
./Simulation/DetSimV2/CMakeLists.txt:add_subdirectory(G4Svc)
./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    # == G4Svc ==
./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/CalibUnit/share/pyjob.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    # == G4Svc ==
./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/CalibUnit/share/pyvis.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimAlg/CMakeLists.txt:        G4SvcLib
./Simulation/DetSimV2/DetSimAlg/DetSimAlg/DetSimAlg.h:#include "G4Svc/G4SvcRunManager.h"
./Simulation/DetSimV2/DetSimAlg/DetSimAlg/DetSimAlg.h:        G4SvcRunManager* run_manager;
./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimAlg/share/run_job.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:#include "G4Svc/IG4Svc.h"
./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:    declProp("G4Svc", m_g4svc_name="G4Svc");
./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:    SniperPtr<IG4Svc> g4svc(*getParent(), m_g4svc_name);
./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:        LogError << "Failed to Load the G4Svc " << m_g4svc_name
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfTT.py:        self._g4svc = self._task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py:# == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py:Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:            # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:            self._g4svc = self._task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_any.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/pyjob.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/share/pyjob.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimOptions/share/pyjob_atmospheric.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimOptions/share/pyvis.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimOptions/share/pyvis_dev_sticks.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    # == G4Svc ==
./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    Sniper.loadDll("libG4Svc.so")
./Simulation/DetSimV2/DetSimOptions/share/pyvis_guidetube.py:    g4svc = task.createSvc("G4Svc")
./Simulation/DetSimV2/G4Svc/CMakeLists.txt:PKG (G4Svc
./Simulation/DetSimV2/G4Svc/CMakeLists.txt:    SHARED # G4SvcLib
./Simulation/DetSimV2/G4Svc/CMakeLists.txt:        src/IG4Svc.cc
./Simulation/DetSimV2/G4Svc/CMakeLists.txt:        src/G4SvcRunManager.cc
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#ifndef G4Svc_h
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#define G4Svc_h
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:#include "G4Svc/IG4Svc.h"
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:class G4Svc: public IG4Svc, public SvcBase {
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4Svc(const std::string& name);
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        ~G4Svc();
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4SvcRunManager* getRunMgr();
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4SvcRunManager* m_runmgr;
./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:#ifndef G4SvcRunManager_h
./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:#define G4SvcRunManager_h
./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:class G4SvcRunManager: public G4RunManager {
./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:        G4SvcRunManager();
./Simulation/DetSimV2/G4Svc/G4Svc/G4SvcRunManager.h:        ~G4SvcRunManager();
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#ifndef IG4Svc_h
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#define IG4Svc_h
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:#include "G4Svc/G4SvcRunManager.h"
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:class IG4Svc {
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:        virtual ~IG4Svc() = 0;
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:        virtual G4SvcRunManager* getRunMgr()=0;
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:#include "G4Svc/G4Svc.h"
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:#include "G4Svc/G4SvcRunManager.h"
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:DECLARE_SERVICE(G4Svc);
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4Svc::G4Svc(const std::string& name)
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    LogDebug << "Create G4SvcRunManager in G4Svc" << std::endl;
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    m_runmgr = new G4SvcRunManager;
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4Svc::~G4Svc()
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:    LogDebug << "Delete G4SvcRunManager in G4Svc" << std::endl;
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:bool G4Svc::initialize() {
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:bool G4Svc::finalize() {
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4SvcRunManager* G4Svc::getRunMgr()
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:#include "G4Svc/G4SvcRunManager.h"
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:G4SvcRunManager::G4SvcRunManager() 
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:    std::cout << "Create G4SvcRunManager" << std::endl;
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:G4SvcRunManager::~G4SvcRunManager() {
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:    std::cout << "Delete G4SvcRunManager" << std::endl;
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::initializeRM() {
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::SimulateEvent(int i_event) {
./Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:bool G4SvcRunManager::finalizeRM() {
./Simulation/DetSimV2/G4Svc/src/IG4Svc.cc:#include "G4Svc/IG4Svc.h"
./Simulation/DetSimV2/G4Svc/src/IG4Svc.cc:IG4Svc::~IG4Svc()
A[blyth@localhost junosw]$ 




python "del "

    [blyth@localhost junosw]$ find . -name '*.py' -exec grep -H 'del ' {} \; | grep -iv model
    ./Calibration/OMILRECCalibSvc/python/OMILRECCalibSvc/__init__.py:del Sniper
    ./Calibration/PMTCalibSvc/python/PMTCalibSvc/__init__.py:del Sniper
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.refractive_energy[:]
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.refractive_index[:]
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.pmtid[:]
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.ishama[:]
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.gain[:]
    ./Database/CondDB/share/run-pyobj.py:                    del self.self_.fwhm[:]
    ./Examples/OECEventAnalysis/python/OECEventAnalysis/__init__.py:del Sniper
    ./Examples/RawAnalysis/python/RawAnalysis/__init__.py:del Sniper
    ./Examples/TimeShiftAnalysis/python/TimeShiftAnalysis/__init__.py:del Sniper
    ./Examples/Tutorial/python/Tutorial/JUNOMtApplication.py:        del muster
    ./Examples/Tutorial/python/Tutorial/JUNOMtApplication.py:        del gs
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimApplication.py:        del muster
    ./Examples/Tutorial/python/Tutorial/JUNOMtDetSimApplication.py:        del gs
    ./OEC/EvtProcessor/EvtConfig/python/EvtConfig/__init__.py:del Sniper
    ./OEC/FBRalg/python/FBRalg/__init__.py:del Sniper
    ./OEC/HECAlg/python/HECAlg/__init__.py:del Sniper
    ./OEC/HECAtmAlg/python/HECAtmAlg/__init__.py:del Sniper
    ./OEC/HECMuonAlg/python/HECMuonAlg/__init__.py:del Sniper
    ./OEC/HECWaveformScaleAlg/python/HECWaveformScaleAlg/__init__.py:del Sniper
    ./OEC/OECProcessor/python/OECProcessor/__init__.py:del Sniper
    ./OEC/SNMonitorAlg/MonitorMethod/python/MonitorMethod/__init__.py:del Sniper
    ./OEC/SNMonitorAlg/SNOnlineMonitor/python/SNOnlineMonitor/__init__.py:del Sniper
    ./OEC/readFromRecAlg/python/readFromRecAlg/__init__.py:del Sniper
    ./Reconstruction/PSDTools/python/PSDTools/__init__.py:#del Sniper
    ./Reconstruction/RecTools/python/RecTools/__init__.py:del Sniper
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    del muster
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    del gs
    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/__init__.py:del Sniper
    ./Simulation/SNMonitorSim/PromptMonitor/python/PromptMonitor/__init__.py:del Sniper
    ./Simulation/SimSvc/PMTSimParamSvc/python/PMTSimParamSvc/__init__.py:del Sniper
    ./Utilities/MtUtilities/python/MtUtilities/__init__.py:del Sniper
    ./Utilities/MtUtilities/share/mtSeparatedOuputInThreads.py:    del muster
    ./Utilities/MtUtilities/share/mtSeparatedOuputInThreads.py:    del gs
    ./Validation/JunoTest/python/JunoTest/Job/Analysis.py:        del os.environ["JUNOTEST_%s_INPUT"%self.cfg.getAttr('step').upper()]
    ./Validation/JunoTest/python/JunoTest/Process/Parser.py:          del s[ps]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/catalog.py:        del self.__catalog_stack[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/dtdparser.py:        del self.own_ent_stack[-1]
    grep: ./XmlObjDesc/scripts/xml/parsers/xmlproc/errors.py: binary file matches
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/errors.py:    2000: "El valor real del atributo '%s' no se corresponde al valor fijado",
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/errors.py:    2024: "No se puede resolver la URI relativa '%s' si se desconoce la URI del documento",
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/errors.py:    2025: "No se encuentra el elemento '%s' antes del '%s'",
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/namespace.py:                del self.ns_map[prefix]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/namespace.py:                del attrs[a]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/namespace.py:            del attrs[a]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/namespace.py:        del self.ns_stack[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/namespace.py:            del self.ns_map[prefix]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xcatalog.py:        del self.parser
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmldtd.py:            del self.attlists[elem_name]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmldtd.py:        del self.__mem[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlproc.py:                del self.open_ents[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlproc.py:                del self.open_ents[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlproc.py:                    del self.stack[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlproc.py:                del self.stack[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlproc.py:        del self.open_ents[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlutils.py:        del self.ent_stack[-1]
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlutils.py:    del characters
    ./XmlObjDesc/scripts/xml/parsers/xmlproc/xmlval.py:            del self.stack[-1]
    ./XmlObjDesc/scripts/xml/utils/iso8601.py:del re
    ./XmlObjDesc/scripts/xml/utils/qp_xml.py:    del self.cur_elem.ns_scope
    ./XmlObjDesc/scripts/xml/utils/qp_xml.py:    del self.cur_elem.parent
    ./XmlObjDesc/scripts/xml/utils/qp_xml.py:  del elem.parent
    ./XmlObjDesc/scripts/xml/utils/qp_xml.py:  del d['']	# make sure we don't pick up no-namespace entries
    ./build/python/PMTCalibSvc/__init__.py:del Sniper
    ./build/python/OMILRECCalibSvc/__init__.py:del Sniper
    ./build/python/DetSimOptions/__init__.py:del Sniper
    ./build/python/PMTSimParamSvc/__init__.py:del Sniper
    ./build/python/PromptMonitor/__init__.py:del Sniper
    ./build/python/RecTools/__init__.py:del Sniper
    ./build/python/PSDTools/__init__.py:#del Sniper
    ./build/python/MtUtilities/__init__.py:del Sniper
    ./build/python/JunoTest/Job/Analysis.py:        del os.environ["JUNOTEST_%s_INPUT"%self.cfg.getAttr('step').upper()]
    ./build/python/JunoTest/Process/Parser.py:          del s[ps]
    ./build/python/Tutorial/JUNOMtApplication.py:        del muster
    ./build/python/Tutorial/JUNOMtApplication.py:        del gs
    ./build/python/Tutorial/JUNOMtDetSimApplication.py:        del muster
    ./build/python/Tutorial/JUNOMtDetSimApplication.py:        del gs
    ./build/python/RawAnalysis/__init__.py:del Sniper
    ./build/python/OECEventAnalysis/__init__.py:del Sniper
    ./build/python/OECProcessor/__init__.py:del Sniper
    ./build/python/HECAlg/__init__.py:del Sniper
    ./build/python/MonitorMethod/__init__.py:del Sniper
    ./build/python/SNOnlineMonitor/__init__.py:del Sniper
    ./build/python/FBRalg/__init__.py:del Sniper
    ./build/python/HECAtmAlg/__init__.py:del Sniper
    ./build/python/readFromRecAlg/__init__.py:del Sniper
    ./build/python/HECWaveformScaleAlg/__init__.py:del Sniper
    ./InstallArea/python/PMTCalibSvc/__init__.py:del Sniper
    ./InstallArea/python/OMILRECCalibSvc/__init__.py:del Sniper
    ./InstallArea/python/DetSimOptions/__init__.py:del Sniper
    ./InstallArea/python/PMTSimParamSvc/__init__.py:del Sniper
    ./InstallArea/python/PromptMonitor/__init__.py:del Sniper
    ./InstallArea/python/RecTools/__init__.py:del Sniper
    ./InstallArea/python/PSDTools/__init__.py:#del Sniper
    ./InstallArea/python/MtUtilities/__init__.py:del Sniper
    ./InstallArea/python/JunoTest/Job/Analysis.py:        del os.environ["JUNOTEST_%s_INPUT"%self.cfg.getAttr('step').upper()]
    ./InstallArea/python/JunoTest/Process/Parser.py:          del s[ps]
    ./InstallArea/python/Tutorial/JUNOMtApplication.py:        del muster
    ./InstallArea/python/Tutorial/JUNOMtApplication.py:        del gs
    ./InstallArea/python/Tutorial/JUNOMtDetSimApplication.py:        del muster
    ./InstallArea/python/Tutorial/JUNOMtDetSimApplication.py:        del gs
    ./InstallArea/python/RawAnalysis/__init__.py:del Sniper
    ./InstallArea/python/OECEventAnalysis/__init__.py:del Sniper
    ./InstallArea/python/OECProcessor/__init__.py:del Sniper
    ./InstallArea/python/HECAlg/__init__.py:del Sniper
    ./InstallArea/python/MonitorMethod/__init__.py:del Sniper
    ./InstallArea/python/SNOnlineMonitor/__init__.py:del Sniper
    ./InstallArea/python/FBRalg/__init__.py:del Sniper
    ./InstallArea/python/HECAtmAlg/__init__.py:del Sniper
    ./InstallArea/python/readFromRecAlg/__init__.py:del Sniper
    ./InstallArea/python/HECWaveformScaleAlg/__init__.py:del Sniper
    A[blyth@localhost junosw]$ 



::

     01 #!/usr/bin/env python
      2 # -*- coding:utf-8 -*-
      3 # author: lintao
      4 
      5 import Sniper
      6 # = geant4 related =
      7 # == G4Svc ==
      8 Sniper.loadDll("libG4Svc.so")
      9 # == DetSimOptions ==
     10 Sniper.loadDll("libDetSimOptions.so")
     11 Sniper.loadDll("libAnalysisCode.so")
     12 Sniper.loadDll("libPhysiSim.so")
     13 Sniper.loadDll("libCentralDetector.so")
     14 Sniper.loadDll("libTopTracker.so")
     15 Sniper.loadDll("libChimney.so")
     16 Sniper.loadDll("libCalibUnit.so")
     17 # == DetSimAlg ==
     18 Sniper.loadDll("libDetSimAlg.so")
     19 
     20 # = helper =
     21 # == load data from default directory ==
     22 import os
     23 def data_load(filename):
     24     # Load the data located in $DETSIMOPTIONSROOT/data
     25     detroot = os.environ["DETSIMOPTIONSROOT"]
     26     if not detroot:
     27         raise Exception("Can't get $DETSIMOPTIONSROOT")
     28     f = os.path.join(detroot, "data",  filename)
     29     if not os.path.exists(f):
     30         raise Exception("Can't get $DETSIMOPTIONSROOT/data/%s"%filename)
     31 
     32     return f
     33 
     34 del Sniper



BP=G4Svc::~G4Svc
--------------------

junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] photonNuclear
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 3566722.25 ms
junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 3566722.25 ms
############################## SniperProfiling ##############################
Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
GenTools                 1           1.32900        1.32900      0.00000      
DetSimAlg                1           3566803.75000  3566803.75000708.14260    
Sum of junotoptask       1           3566805.25000  3566805.25000535.54873    
#############################################################################
junotoptask:SniperProfiling.finalize  INFO: finalized successfully
junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
junotoptask.finalize            INFO: events processed 1
[2025-11-26 18:38:37,137] p1816188 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1_db1.txt', use_event_time_from_generator=False)
== Buffer Memory Management ==
 == PMTSimParamSvc == 
GENTOOL MODE:  hepevt
3inch PMT type:  Tub3inchV3
WARNING: mac file run.mac does not exist.
[Thread 0x7fffcd5ff640 (LWP 1816209) exited]
HepEvt2HepMC Dtor called begin
HepEvt2HepMC Dtor called end

Thread 1 "python" hit Breakpoint 1.2, G4Svc::~G4Svc (this=0x6633370, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
warning: Source file is more recent than executable.
23	}
Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
(gdb) bt
#0  G4Svc::~G4Svc (this=0x6633370, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
#1  0x00007fffd0adf513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#2  0x00007fffd0adfe0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#3  0x00007fffd0af7b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#4  0x00007fffd0af4f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
#5  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
#6  0x00007fffdf0b9d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#7  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc1519530) at Objects/typeobject.c:1463
#8  0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#9  Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#10 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
#11 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff770f650) at Objects/typeobject.c:1433
#12 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#13 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#14 free_keys_object (keys=0x7ffff7e7fd20) at Objects/dictobject.c:664
#15 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
#16 dict_dealloc (mp=0x7ffff76e5640) at Objects/dictobject.c:2378
#17 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#18 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#19 module_dealloc (m=0x7ffff76e1b20) at Objects/moduleobject.c:699
#20 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#21 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#22 insertdict (mp=0x7ffff7e49340, key=0x7ffff76e56f0, hash=-944555062593403840, value=<optimized out>) at Objects/dictobject.c:1304
#23 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e49340) at Python/pylifecycle.c:1415
#24 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
#25 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
#26 Py_FinalizeEx () at Python/pylifecycle.c:1751
#27 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
#28 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefdc0) at Modules/main.c:714
#29 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
#30 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
#31 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
#32 0x0000000000401075 in _start ()
(gdb) 







Double delete G4Svc ?
-------------------------

::

    Level density (1/MeV)                               0.1
    Time limit for long lived isomeres (ns)             1442.7
    Internal e- conversion flag                         1
    Store e- internal conversion data                   1
    Electron internal conversion ID                     0
    Correlated gamma emission flag                      0
    Max 2J for sampling of angular correlations         10
    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2025-11-26 17:39:10.180 [junoSD_PMT_v2::Initialize eventID 0
    2025-11-26 17:39:10.181 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    -------- WWWW ------- G4Exception-START -------- WWWW -------
    *** G4Exception : Warning
          issued by : G4Step::GetDeltaEnergy()
    This method is obsolete and will be removed soon
    *** This is just a warning message. ***
    -------- WWWW -------- G4Exception-END --------- WWWW -------

     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [61710628]@[PMT_3inch_inner2_phys] (-9293.64, 4609.02, -16390.59, 297.48)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [64010276]@[PMT_3inch_inner1_phys] (-9422.46, 4721.79, -16260.01, 285.94)  step number >= 1000
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [80534703]@[pAcrylic] (-15507.47, 8096.74, -3414.09, 291.49)  step number >= 1000
     decay 2 gammas 0.510999
    2025-11-26 18:38:32.348 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 4417735 GPU NO
    2025-11-26 18:38:32.348 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 4417735 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-11-26 10:38:32.870361000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-11-26 10:38:36.902719000Z
    end of event action 
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 442
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] neutronInelastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] nCapture
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hadElastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] photonNuclear
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 3566722.25 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 3566722.25 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.32900        1.32900      0.00000      
    DetSimAlg                1           3566803.75000  3566803.75000708.14260    
    Sum of junotoptask       1           3566805.25000  3566805.25000535.54873    
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-26 18:38:37,137] p1816188 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1_db1.txt', use_event_time_from_generator=False)
    == Buffer Memory Management ==
     == PMTSimParamSvc == 
    GENTOOL MODE:  hepevt
    3inch PMT type:  Tub3inchV3
    WARNING: mac file run.mac does not exist.
    [Thread 0x7fffcd5ff640 (LWP 1816209) exited]
    HepEvt2HepMC Dtor called begin
    HepEvt2HepMC Dtor called end

    Thread 1 "python" hit Breakpoint 1.2, G4Svc::~G4Svc (this=0x6633370, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    warning: Source file is more recent than executable.
    23	}
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  G4Svc::~G4Svc (this=0x6633370, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #1  0x00007fffd0adf513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #2  0x00007fffd0adfe0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #3  0x00007fffd0af7b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd0af4f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #6  0x00007fffdf0b9d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #7  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc1519530) at Objects/typeobject.c:1463
    #8  0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #9  Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #10 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #11 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff770f650) at Objects/typeobject.c:1433
    #12 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #13 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #14 free_keys_object (keys=0x7ffff7e7fd20) at Objects/dictobject.c:664
    #15 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #16 dict_dealloc (mp=0x7ffff76e5640) at Objects/dictobject.c:2378
    #17 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #18 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #19 module_dealloc (m=0x7ffff76e1b20) at Objects/moduleobject.c:699
    #20 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #21 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #22 insertdict (mp=0x7ffff7e49340, key=0x7ffff76e56f0, hash=-944555062593403840, value=<optimized out>) at Objects/dictobject.c:1304
    #23 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e49340) at Python/pylifecycle.c:1415
    #24 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #25 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #26 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #27 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #28 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefdc0) at Modules/main.c:714
    #29 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #30 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #31 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #32 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1.1, G4Svc::~G4Svc (this=0x6633370, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:16
    16	G4Svc::~G4Svc()
    (gdb) c
    Continuing.
    Delete G4SvcRunManager
    double free or corruption (out)

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
    #4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
    #5  0x00007ffff7497c70 in _int_free () from /lib64/libc.so.6
    #6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
    #7  0x00007fffe77aa77b in llvm::Module::~Module() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #8  0x00007fffe41bc1cc in std::_Rb_tree<llvm::Module const*, std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule>, std::_Select1st<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >, std::less<llvm::Module const*>, std::allocator<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> > >::_M_erase(std::_Rb_tree_node<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >*) [clone .isra.0] ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #9  0x00007fffe41bc16d in std::_Rb_tree<llvm::Module const*, std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule>, std::_Select1st<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >, std::less<llvm::Module const*>, std::allocator<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> > >::_M_erase(std::_Rb_tree_node<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >*) [clone .isra.0] ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #10 0x00007fffe41bc16d in std::_Rb_tree<llvm::Module const*, std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule>, std::_Select1st<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >, std::less<llvm::Module const*>, std::allocator<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> > >::_M_erase(std::_Rb_tree_node<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >*) [clone .isra.0] ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #11 0x00007fffe41bc16d in std::_Rb_tree<llvm::Module const*, std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule>, std::_Select1st<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >, std::less<llvm::Module const*>, std::allocator<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> > >::_M_erase(std::_Rb_tree_node<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >*) [clone .isra.0] ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #12 0x00007fffe41bc16d in std::_Rb_tree<llvm::Module const*, std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule>, std::_Select1st<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >, std::less<llvm::Module const*>, std::allocator<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> > >::_M_erase(std::_Rb_tree_node<std::pair<llvm::Module const* const, llvm::orc::ThreadSafeModule> >*) [clone .isra.0] ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #13 0x00007fffe41bc55e in cling::IncrementalExecutor::~IncrementalExecutor() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #14 0x00007fffe414ea5a in cling::Interpreter::~Interpreter() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #15 0x00007fffe414ecd9 in cling::Interpreter::~Interpreter() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #16 0x00007fffe406b3f8 in TCling::~TCling() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #17 0x00007fffe406b6c9 in TCling::~TCling() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCling.so
    #18 0x00007fffe97eefcc in TROOT::~TROOT() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #19 0x00007ffff74412dd in __run_exit_handlers () from /lib64/libc.so.6
    #20 0x00007ffff7441430 in exit () from /lib64/libc.so.6
    #21 0x00007ffff74295d7 in __libc_start_call_main () from /lib64/libc.so.6
    #22 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #23 0x0000000000401075 in _start ()
    (gdb) 



















Need faster cycle
--------------------


::

    1545     def setup_generator_hepevt(self, args, gt):
    1546         # == HepEvt to HepMC ==
    1547         gun = gt.createTool("GtHepEvtGenTool/gun")
    1548         #gun.property("Source").set("K40.exe -seed 42 -n 100|")
    1549         source = self.GENERATOR_EXEC[args.exe].format(SEED=args.seed,
    1550                                                       EVENT=args.evtmax)
    1551         if args.file:
    1552             source = args.file
    1553         gun.property("Source").set(source)
    1554         gt.property("GenToolNames").set([gun.objName()])
    1555 
    1556         if not args.use_event_time_from_generator:
    1557             # == GtTimeOffsetTool ==
    1558             toffset = gt.createTool("GtTimeOffsetTool")
    1559             gt.property("GenToolNames").append([toffset.objName()])
    1560         gt.property("EnableSNTime").set(args.use_event_time_from_generator



     20 GtHepEvtGenTool::~GtHepEvtGenTool()
     21 {
     22     if (m_parser) {
     23         delete m_parser;
     24     }   
     25     m_parser = 0;
     26 }
     27 
     28 bool
     29 GtHepEvtGenTool::configure()
     30 {
     31     if (!m_parser) {
     32         if ("" == m_source) {
     33             LogError << "No HEPEvt source string given." << std::endl;
     34             return false;
     35         }
     36         m_parser = new HepEvt2HepMC(m_source);
     37         // if (not m_parser->fill(m_source.c_str())) {
     38         //     LogError << "Failed to fill primary vertices using \""
     39         //              << m_source << "\"" << std::endl;
     40         //     return false;
     41         // }
     42         // LogInfo  << "Filled HEPEvt cache with " << m_parser->cacheSize()
     43         //         << " events" << std::endl;
     44     }
     45     return true;
     46 }
     47 
     48 bool
     49 GtHepEvtGenTool::mutate(HepMC::GenEvent& event)
     50 {
     51     if (!m_parser)  {
     52         return false;
     53     }
     54 
     55     // HepMC::GenEvent* new_event=0;
     56     if (not m_parser->generate(event)) {
     57         LogError << "Failed to generate new event" << std::endl;
     58         return false;
     59     }
     60 
     61     return true;
     62 }


     14 HepEvt2HepMC::HepEvt2HepMC(const std::string& filename)
     15     : m_eventCount(0), m_filename(filename), m_fp(0)
     16 {
     17     // open the file or execute the generator when HepEvt2HepMC is created. 
     18     if (!m_fp) {
     19         // reset errno first
     20         errno = 0;
     21         m_fp = open_file(m_filename);
     22         if ((!m_fp) or errno) {
     23             std::string msg = "Failed to open HEPEvt data source: \"";
     24             msg += m_filename;
     25             msg += "\"";
     26             std::cerr << msg << std::endl;
     27             m_fp = 0;
     28         }
     29     }
     30 
     31 }
     32 
     33 HepEvt2HepMC::~HepEvt2HepMC()
     34 {
     35     std::cerr << "HepEvt2HepMC Dtor called begin" << std::endl;
     36     close_file(m_fp, m_filename);
     37     std::cerr << "HepEvt2HepMC Dtor called end" << std::endl;
     38 }



::

    BP=G4SvcRunManager::~G4SvcRunManager,G4Svc::~G4Svc

    BP=G4SvcRunManager::~G4SvcRunManager,G4Svc::~G4Svc zhenning_double_muon/detsim.sh db1


::

     Process: protonInelastic
            Model:                      QGSP: 12 GeV ---> 100 TeV
            Model:                      FTFP: 9.5 GeV ---> 25 GeV
            Model:            BertiniCascade: 0 eV  ---> 9.9 GeV
         Cr_sctns:       Barashenkov-Glauber: 0 eV  ---> 100 TeV
         Cr_sctns:       Barashenkov-Glauber: 0 eV  ---> 100 TeV
         Cr_sctns:          GheishaInelastic: 0 eV  ---> 100 TeV

    ---------------------------------------------------
                               Hadronic Processes for triton

      Process: hadElastic
            Model:              hElasticLHEP: 0 eV /n ---> 100 TeV/n
         Cr_sctns:            GheishaElastic: 0 eV  ---> 100 TeV

      Process: tInelastic
            Model:       ParticleHPInelastic: 0 eV /n ---> 200 MeV/n
            Model:  Binary Light Ion Cascade: 190 MeV/n ---> 4 GeV/n
            Model:                      FTFP: 2 GeV/n ---> 100 TeV/n
         Cr_sctns:       TritonHPInelasticXS: 0 eV  ---> 200 MeV
         Cr_sctns: Glauber-Gribov nucleus nucleus: 0 eV  ---> 2.88022e+295 J  
         Cr_sctns:          GheishaInelastic: 0 eV  ---> 100 TeV

    ================================================================
    junotoptask.find                WARN: Cann't find Object SimTrackSvc
    junotoptask:DetSimAlg.DataModelWriterWithSplit.BeginOfRunAction  INFO: Retrieving PMTParamSvc.
    junotoptask:DetSimAlg.DataModelWriterWithSplit.BeginOfRunAction  INFO: Retrieve PMTParamSvc successfully.
    junotoptask:DetSimAlg.NormalAnaMgr.BeginOfRunAction  INFO: Retrieving PMTParamSvc.
    junotoptask:DetSimAlg.NormalAnaMgr.BeginOfRunAction  INFO: Retrieve PMTParamSvc successfully.
    Warning in <TTree::Bronch>: Using split mode on a class: TString with a custom Streamer
    Warning in <TTree::Bronch>: Using split mode on a class: TString with a custom Streamer
    Warning in <TTree::Bronch>: Using split mode on a class: TString with a custom Streamer
    Warning in <TTree::Bronch>: Using split mode on a class: TString with a custom Streamer
    junotoptask:MCParamsSvc.GetPath  INFO: - MC Param: Material.LS.ConstantProperty will be loaded from: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/dbdata/offline-data/Simulation/DetSim/Material/LS/ConstantProperty
    =======================================================================
    ======       Pre-compound/De-excitation Physics Parameters     ========
    =======================================================================
    Type of pre-compound inverse x-section              3
    Pre-compound model active                           1
    Pre-compound low energy (MeV)                       0.1
    Type of de-excitation inverse x-section             3
    Type of de-excitation factory                       Evaporation
    Number of de-excitation channels                    8
    Min excitation energy (keV)                         0.01
    Min energy per nucleon for multifragmentation (MeV) 1e+05
    Level density (1/MeV)                               0.1
    Time limit for long lived isomeres (ns)             1442.7
    Internal e- conversion flag                         1
    Store e- internal conversion data                   1
    Electron internal conversion ID                     0
    Correlated gamma emission flag                      0
    Max 2J for sampling of angular correlations         10
    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2025-11-26 20:28:59.063 [junoSD_PMT_v2::Initialize eventID 0
    2025-11-26 20:28:59.064 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    -------- WWWW ------- G4Exception-START -------- WWWW -------
    *** G4Exception : Warning
          issued by : G4Step::GetDeltaEnergy()
    This method is obsolete and will be removed soon
    *** This is just a warning message. ***
    -------- WWWW -------- G4Exception-END --------- WWWW -------

     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
     decay 2 gammas 0.510999
    junotoptask:DetSimAlg.NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [86647204]@[pLPMT_Hamamatsu_R12860] (-1019.44, -3045.34, -19146.90, 256.27)  step number >= 1000
     decay 2 gammas 0.510999
    2025-11-26 21:30:00.661 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 4417723 GPU NO
    2025-11-26 21:30:00.662 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 4417723 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-11-26 13:30:01.149507000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-11-26 13:30:05.124198000Z
    end of event action 
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 30150.00 / 30150.00
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 442
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] Decay
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 3666079.00 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 3666079.00 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.27200        1.27200      0.00023      
    DetSimAlg                1           3666160.75000  3666160.750000.00000      
    Sum of junotoptask       1           3666162.00000  3666162.000000.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-26 21:30:05,395] p694813 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2025-11-26 21:30:05,395] p694813 {/home/blyth/junosw/InstallArea/bin/tut_detsim.py:55} INFO - ]juno_application.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1_db1.txt', use_event_time_from_generator=False)
    3inch PMT type:  Tub3inchV3
    [Thread 0x7fffcd5ff640 (LWP 694828) exited]
    HepEvt2HepMC Dtor called begin
    HepEvt2HepMC Dtor called end

    Thread 1 "python" hit Breakpoint 1.2, G4SvcRunManager::~G4SvcRunManager (this=0x65f3b40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    11	}
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  G4SvcRunManager::~G4SvcRunManager (this=0x65f3b40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #1  0x00007fffcf9766db in G4Svc::~G4Svc (this=0x65c4040, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #2  0x00007fffcf97672e in G4Svc::~G4Svc (this=0x65c4040, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #3  0x00007fffd0adf513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd0adfe0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd0af7b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd0af4f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #8  0x00007fffdf0b9d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #9  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc15d4a90) at Objects/typeobject.c:1463
    #10 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #11 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #12 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #13 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff770f6d0) at Objects/typeobject.c:1433
    #14 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #15 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #16 free_keys_object (keys=0x7ffff7e7fd20) at Objects/dictobject.c:664
    #17 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #18 dict_dealloc (mp=0x7ffff76e5640) at Objects/dictobject.c:2378
    #19 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #20 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #21 module_dealloc (m=0x7ffff76e1b70) at Objects/moduleobject.c:699
    #22 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #23 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #24 insertdict (mp=0x7ffff7e49340, key=0x7ffff76e56f0, hash=2031409552524386301, value=<optimized out>) at Objects/dictobject.c:1304
    #25 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e49340) at Python/pylifecycle.c:1415
    #26 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #27 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #28 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #29 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #30 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefd90) at Modules/main.c:714
    #31 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #32 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #33 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #34 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1.1, G4SvcRunManager::~G4SvcRunManager (this=0x65f3b40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:9
    9	G4SvcRunManager::~G4SvcRunManager() {
    (gdb) bt
    #0  G4SvcRunManager::~G4SvcRunManager (this=0x65f3b40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:9
    #1  0x00007fffe05845ba in G4SvcRunManager::~G4SvcRunManager (this=0x65f3b40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #2  0x00007fffcf9766db in G4Svc::~G4Svc (this=0x65c4040, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #3  0x00007fffcf97672e in G4Svc::~G4Svc (this=0x65c4040, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #4  0x00007fffd0adf513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd0adfe0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd0af7b4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd0af4f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #9  0x00007fffdf0b9d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc15d4a90) at Objects/typeobject.c:1463
    #11 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #12 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #13 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #14 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff770f6d0) at Objects/typeobject.c:1433
    #15 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #16 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #17 free_keys_object (keys=0x7ffff7e7fd20) at Objects/dictobject.c:664
    #18 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #19 dict_dealloc (mp=0x7ffff76e5640) at Objects/dictobject.c:2378
    #20 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #21 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #22 module_dealloc (m=0x7ffff76e1b70) at Objects/moduleobject.c:699
    #23 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #24 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #25 insertdict (mp=0x7ffff7e49340, key=0x7ffff76e56f0, hash=2031409552524386301, value=<optimized out>) at Objects/dictobject.c:1304
    #26 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e49340) at Python/pylifecycle.c:1415
    #27 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #28 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #29 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #30 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #31 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffefd90) at Modules/main.c:714
    #32 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #33 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #34 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #35 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.
    Delete G4SvcRunManager
    double free or corruption (out)

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) 














