One double muon event
========================


Summary table
----------------


Timings for one double muon event, ~150M photons, 28M hit, 6.4M mergedHit [28/6.4=4.3]


+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
| [seconds]       |   Method                   | Collect+(CPUMerge) |   Kernel Time   | Download+(GPUMerge)  | Total (no-init)    |
|                 |                            |                    |   PREL:POST     |   POST:DOWN          |                    |
+=================+============================+====================+=================+======================+====================+
|  hit            |  CollectFullHits_cpumerged | 190.445588         |  22.996241      |   1.949322           |  215.560469        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitmerged      |  CollectFullHits_premerged |  6.712759   (x28)  |  22.988498      |   0.543559   (x3.5)  |   30.400825        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitlite        |  CollectMuonHits_cpumerge  | 146.471113         |  23.108319      |   0.484299           |  170.226838        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+
|  hitlitemerged  |  CollectMuonHits_premerged |   0.403599 (x366)  |  23.097717      |   0.181023   (x2.6)  |   23.835564        |
+-----------------+----------------------------+--------------------+-----------------+----------------------+--------------------+


* no significant kernel time differences
* huge reduction in hit collection time (x28,x366) by merging hits on GPU [2.5min -> 0.4 seconds]
* significant reductions in download overheads by merging hits on GPU

GPU hit merging doubly beneficial:

1. reduced overhead, as less to download from GPU
2. almost eliminates CPU post processing for "hitlitemerged"




detsim2.sh : opticksMode:0 "J" measurements
---------------------------------------------

TEST=hit ./detsim.sh
~~~~~~~~~~~~~~~~~~~~~

::

    2025-12-04 22:57:14.857 ]junoSD_PMT_v2::Initialize eventID 0
    2025-12-05 00:55:46.451 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 6474451 hitCollectionAlt -1 hcMuon 0 GPU NO

    A[blyth@localhost zhenning_double_muon]$ seconds_between "2025-12-04 22:57:14.857" "2025-12-05 00:55:46.451"
    7112

    A[blyth@localhost zhenning_double_muon]$ echo $(( 7112/60 ))
    118


    A[blyth@localhost OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run]$ l
    total 153696
         4 drwxr-xr-x. 27 blyth blyth      4096 Dec  5 09:52 ..
       404 -rw-r--r--.  1 blyth blyth    409641 Dec  5 00:55 OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run.log
       640 -rw-r--r--.  1 blyth blyth    654064 Dec  5 00:55 user_output.root
    152644 -rw-r--r--.  1 blyth blyth 156306497 Dec  5 00:55 output.root
         4 drwxr-xr-x.  2 blyth blyth      4096 Dec  5 00:55 .
    A[blyth@localhost OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run]$ pwd
    /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run
    A[blyth@localhost OJ_LOCAL_Dec04_ok0_hit_seed42_evtmax1_run]




TEST=hitlite ./detsim.sh
~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::



    2025-12-05 09:54:44.657 [junoSD_PMT_v2::Initialize eventID 0
    2025-12-05 11:49:48.015 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 6474451 GPU NO

    junotoptask.finalize            INFO: events processed 1
    [2025-12-05 11:49:56,260] p502133 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2025-12-05 11:49:56,260] p502133 {/home/blyth/junosw/InstallArea/bin/tut_detsim.py:55} INFO - ]juno_application.run

    seconds_between "2025-12-05 09:54:44.657" "2025-12-05 11:49:48.015"

    A[blyth@localhost zhenning_double_muon]$ seconds_between "2025-12-05 09:54:44.657" "2025-12-05 11:49:48.015"
    6904

    A[blyth@localhost zhenning_double_muon]$ echo $(( 6904/60 ))
    115








::

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
    2025-12-04 22:57:14.857 [junoSD_PMT_v2::Initialize eventID 0
    2025-12-04 22:57:14.857 ]junoSD_PMT_v2::Initialize eventID 0
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
    2025-12-05 00:55:46.451 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 6474451 hitCollectionAlt -1 hcMuon 0 GPU NO
    2025-12-05 00:55:46.451 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 6474451 hitCollectionAlt -1 hcMuon 0 GPU NO
    hitCollectionTT.size: 102	userhitCollectionTT.size: 51
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-12-04 16:55:47.289272000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-12-04 16:55:54.776777000Z
    end of event action 
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 30150.00 / 30150.00
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 648
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] neutronInelastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hadElastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] nCapture
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] photonNuclear
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 7120829.50 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 7120829.50 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.26300        1.26300      0.00020      
    DetSimAlg                1           7121184.50000  7121184.500001256.06359   
    Sum of junotoptask       1           7121186.00000  7121186.000001088.88016   
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-12-05 00:55:56,332] p468024 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2025-12-05 00:55:56,332] p468024 {/home/blyth/junosw/InstallArea/bin/tut_detsim.py:55} INFO - ]juno_application.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=1, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='hepevt', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, exe='Muon', file='/home/blyth/j/zhenning_double_muon/j__zhenning_double_muon_seed_42_evtmax_1.txt', use_event_time_from_generator=False)
    HepEvt2HepMC Dtor called begin
    HepEvt2HepMC Dtor called end
    Delete G4SvcRunManager
    corrupted size vs. prev_size
     *** Break *** abort





detsim4.sh : OJ measuments
------------------------------------




→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hit_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.466   215.560469        22.996241 (PREL→POST)         1.949322 (POST→DOWN) 32168.83  7971.96  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlite_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.462   170.226838        23.108319 (PREL→POST)         0.484299 (POST→DOWN) 32499.61  5361.86  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlitemerged_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  107.263    23.835564        23.097717 (PREL→POST)         0.181023 (POST→DOWN) 87284.29  4988.84  # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitmerged_seed42_evtmax1_run/SProf.txt
Method                                               Start(s)  Duration(s)     Sub PREL→POST(s)     Sub POST→DOWN(s)   VM(MB)  RSS(MB) Comment
------------------------------------------------------------------------------------------------------------------------------------------------------
A000_QSim__simulate_HEAD->reset_HEAD                  106.770    30.400825        22.988498 (PREL→POST)         0.543559 (POST→DOWN) 88292.85  6634.07  # slice=1,max_slot_M=150
A[blyth@localhost zhenning_double_muon]$ 













A[blyth@localhost j]$ T0="2025-12-04 16:00" zhenning_double_muon/detsim.sh prof
                            t0 : 120 minutes ago
                            T0 : 2025-12-04 16:00
                            mt : 2025-12-04 16:00:00
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hit_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:07:25.334   1024.60    493.44  SEvt__Init_RUN_META
 30.755473  30.755473  2025-12-04 16:07:56.090   6394.04   1368.74  CSGOptiX__Create_HEAD
 32.047164   1.291691  2025-12-04 16:07:57.382   8509.56   1955.52  CSGOptiX__Create_TAIL
106.465519  74.418355  2025-12-04 16:09:11.800  11099.55   4542.50  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.465588   0.000069  2025-12-04 16:09:11.800  11099.55   4542.50  A000_QSim__simulate_HEAD
106.465623   0.000035  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__BeginOfRun
106.465743   0.000120  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__beginOfEvent_FIRST_EGPU
106.465769   0.000026  2025-12-04 16:09:11.800  11099.55   4542.50  A000_SEvt__setIndex
106.571435   0.105666  2025-12-04 16:09:11.906  11153.01   4595.72  A000_QSim__simulate_LBEG
106.571472   0.000037  2025-12-04 16:09:11.906  11153.01   4595.72  A000_QSim__simulate_PRUP
106.634089   0.062617  2025-12-04 16:09:11.969  28785.01   4596.59  A000_QSim__simulate_PREL
129.630330  22.996241  2025-12-04 16:09:34.965  28785.01   4601.41  A000_QSim__simulate_POST
131.579652   1.949322  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_DOWN
131.579698   0.000046  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_LEND
131.579721   0.000023  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_PCAT
131.579765   0.000044  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
131.579770   0.000005  2025-12-04 16:09:36.914  30461.76   6279.35  A000_QSim__simulate_TAIL
131.579950   0.000180  2025-12-04 16:09:36.914  30461.76   6279.35  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
131.580014   0.000064  2025-12-04 16:09:36.914  30461.76   6279.35  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_HEAD
322.025602 190.445588  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_cpumerged_TAIL # hit=27471928,merged=21062899,save=6409029
322.025669   0.000067  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
322.025677   0.000008  2025-12-04 16:12:47.360  32168.83   7971.96  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
322.026057   0.000380  2025-12-04 16:12:47.360  32168.83   7971.96  A000_QSim__reset_HEAD
322.026391   0.000334  2025-12-04 16:12:47.361  32115.37   7918.59  A000_SEvt__endIndex
322.030447   0.004056  2025-12-04 16:12:47.365  30438.62   6241.84  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlite_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:15:54.245   1023.13    496.45  SEvt__Init_RUN_META
 29.961488  29.961488  2025-12-04 16:16:24.206   6393.96   1375.03  CSGOptiX__Create_HEAD
 31.212086   1.250598  2025-12-04 16:16:25.457   8509.47   1960.28  CSGOptiX__Create_TAIL
106.462371  75.250285  2025-12-04 16:17:40.707  11099.45   4545.73  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.462438   0.000067  2025-12-04 16:17:40.707  11099.45   4545.73  A000_QSim__simulate_HEAD
106.462471   0.000033  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__BeginOfRun
106.462645   0.000174  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__beginOfEvent_FIRST_EGPU
106.462671   0.000026  2025-12-04 16:17:40.707  11099.45   4545.73  A000_SEvt__setIndex
106.561261   0.098590  2025-12-04 16:17:40.806  11152.91   4598.96  A000_QSim__simulate_LBEG
106.561297   0.000036  2025-12-04 16:17:40.806  11152.91   4598.96  A000_QSim__simulate_PRUP
106.624614   0.063317  2025-12-04 16:17:40.869  31728.91   4599.39  A000_QSim__simulate_PREL
129.732933  23.108319  2025-12-04 16:18:03.977  31728.91   4604.21  A000_QSim__simulate_POST
130.217232   0.484299  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_DOWN
130.217271   0.000039  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_LEND
130.217293   0.000022  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_PCAT
130.217334   0.000041  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=27471928
130.217340   0.000006  2025-12-04 16:18:04.462  32148.10   5024.47  A000_QSim__simulate_TAIL
130.217641   0.000301  2025-12-04 16:18:04.462  32148.10   5024.47  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
130.217711   0.000070  2025-12-04 16:18:04.462  32148.10   5024.47  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_HEAD
276.688824 146.471113  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_cpumerge_TAIL # hit=27471928,merged=21062899,save=6409029
276.688881   0.000057  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
276.688888   0.000007  2025-12-04 16:20:30.933  32499.61   5361.86  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
276.689276   0.000388  2025-12-04 16:20:30.934  32499.61   5361.86  A000_QSim__reset_HEAD
276.689602   0.000326  2025-12-04 16:20:30.934  32446.15   5308.67  A000_SEvt__endIndex
276.691025   0.001423  2025-12-04 16:20:30.936  32026.96   4889.48  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitlitemerged_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 16:20:53.651   1023.25    495.63  SEvt__Init_RUN_META
 30.937038  30.937038  2025-12-04 16:21:24.588   6394.08   1377.59  CSGOptiX__Create_HEAD
 32.213934   1.276896  2025-12-04 16:21:25.865   8509.61   1965.09  CSGOptiX__Create_TAIL
107.262853  75.048919  2025-12-04 16:22:40.913  11099.59   4552.83  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
107.262921   0.000068  2025-12-04 16:22:40.913  11099.59   4552.83  A000_QSim__simulate_HEAD
107.262955   0.000034  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__BeginOfRun
107.263078   0.000123  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__beginOfEvent_FIRST_EGPU
107.263104   0.000026  2025-12-04 16:22:40.914  11099.59   4552.83  A000_SEvt__setIndex
107.367226   0.104122  2025-12-04 16:22:41.018  11153.05   4606.05  A000_QSim__simulate_LBEG
107.367261   0.000035  2025-12-04 16:22:41.018  11153.05   4606.05  A000_QSim__simulate_PRUP
107.415403   0.048142  2025-12-04 16:22:41.066  22481.05   4606.93  A000_QSim__simulate_PREL
130.513120  23.097717  2025-12-04 16:23:04.164  22481.05   4611.74  A000_QSim__simulate_POST
130.694143   0.181023  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_DOWN
130.694182   0.000039  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_LEND
130.694203   0.000021  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_PCAT
130.694244   0.000041  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
130.694250   0.000006  2025-12-04 16:23:04.345  86994.84   4713.71  A000_QSim__simulate_TAIL
130.694408   0.000158  2025-12-04 16:23:04.345  86994.84   4713.71  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_HEAD
130.694467   0.000059  2025-12-04 16:23:04.345  86994.84   4713.71  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_HEAD
131.098066   0.403599  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_premerged_TAIL # hit=6409029
131.098102   0.000036  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectMuonHits_TAIL
131.098108   0.000006  2025-12-04 16:23:04.749  87284.16   4988.84  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
131.098485   0.000377  2025-12-04 16:23:04.749  87284.29   4988.84  A000_QSim__reset_HEAD
131.098769   0.000284  2025-12-04 16:23:04.749  87230.82   4935.50  A000_SEvt__endIndex
131.099464   0.000695  2025-12-04 16:23:04.750  87133.03   4837.70  A000_SEvt__EndOfRun
→ /data1/blyth/tmp/j/zhenning_double_muon/detsim/OJ_LOCAL_Dec04_ok1_hitmerged_seed42_evtmax1_run/SProf.txt
  Delta(s)   Δprev(s)  DateTime (UTC)         VM(MB)   RSS(MB)  Label / Comment
--------------------------------------------------------------------------------------------
  0.000000   0.000000  2025-12-04 17:11:37.343   1023.01    492.82  SEvt__Init_RUN_META
 29.918053  29.918053  2025-12-04 17:12:07.262   6393.87   1376.53  CSGOptiX__Create_HEAD
 31.164170   1.246117  2025-12-04 17:12:08.508   8509.39   1964.82  CSGOptiX__Create_TAIL
106.770381  75.606211  2025-12-04 17:13:24.114  11099.38   4550.71  junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD
106.770446   0.000065  2025-12-04 17:13:24.114  11099.38   4550.71  A000_QSim__simulate_HEAD
106.770477   0.000031  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__BeginOfRun
106.770616   0.000139  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__beginOfEvent_FIRST_EGPU
106.770643   0.000027  2025-12-04 17:13:24.114  11099.38   4550.71  A000_SEvt__setIndex
106.877424   0.106781  2025-12-04 17:13:24.221  11152.84   4603.94  A000_QSim__simulate_LBEG
106.877463   0.000039  2025-12-04 17:13:24.221  11152.84   4603.94  A000_QSim__simulate_PRUP
106.925702   0.048239  2025-12-04 17:13:24.269  21840.84   4604.38  A000_QSim__simulate_PREL
129.914200  22.988498  2025-12-04 17:13:47.258  21840.84   4608.75  A000_QSim__simulate_POST
130.457759   0.543559  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_DOWN
130.457808   0.000049  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_LEND # slice=1,max_slot_M=150
130.457829   0.000021  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_PCAT
130.457865   0.000036  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_BRES # numGenstepCollected=583922,numPhotonCollected=148793197,numHit=6409029
130.457870   0.000005  2025-12-04 17:13:47.801  86648.02   5004.11  A000_QSim__simulate_TAIL
130.458047   0.000177  2025-12-04 17:13:47.802  86648.02   5004.11  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_HEAD
130.458106   0.000059  2025-12-04 17:13:47.802  86648.02   5004.11  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_HEAD
137.170865   6.712759  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_premerged_TAIL # hit=6409029
137.170900   0.000035  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_CollectFullHits_TAIL
137.170909   0.000009  2025-12-04 17:13:54.514  88292.85   6634.07  A000_junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_TAIL
137.171271   0.000362  2025-12-04 17:13:54.515  88292.85   6634.07  A000_QSim__reset_HEAD
137.171567   0.000296  2025-12-04 17:13:54.515  88239.39   6580.73  A000_SEvt__endIndex
137.172888   0.001321  2025-12-04 17:13:54.516  87848.21   6189.55  A000_SEvt__EndOfRun
A[blyth@localhost j]$ 
A[blyth@localhost j]$ 



