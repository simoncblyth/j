cuda13_1_gitlab_ci_fail.rst
=============================


Overview
---------

gitlab-ci build nodes have no GPU, but as evtmax is zero this did not cause problem.




gitlab-ci fail
---------------



::

    2026-06-16 08:37:09.492 INFO  [185418] [U4Tree::Create@247] ]stree::postcreate
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=0, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='sample_detsim.root', user_output='sample_detsim_user.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=False, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, acrylic_repairs=False, segmented_water_distributor=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, water_distributor_enabled=True, emf_coils_system_enabled=True, emf_support_bars_enabled=True, emf_steel_reflectivity=0.535, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, use_elecroom=True, rock_thickness=10000.0, pmt20inch=True, pmt20inch_name='PMTMask', lab2ppo_prob=0.68392399, lab2bis_prob=0.31607601, lab2ppo_tau=1.24779657, lab2bis_tau=29.59617096, pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=0.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=1, anamgr_opticks=False, replace_param=None, usepmtsimsvc=True, quenching=True, pmt_hit_type=1, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=False, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=False, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, enable_zero_step_check=False, zero_step_threshold=100, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='gun', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, particles='gamma', momentums=1.0, momentums_mode='Fix', momentums_extra_params=None, momentums_interp='Momentum', positions=[(0, 0, 0)], times=None, directions=None)
    Traceback (most recent call last):
      File "/builds/JUNO/offline/junosw/InstallArea/bin/tut_detsim.py", line 54, in <module>
        juno_application.run()
      File "/builds/JUNO/offline/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 224, in run
        self.toptask.run()
    RuntimeError: CUDA call (cudaMalloc(reinterpret_cast<void**>( &d_array ), size ) ) failed with error: 'CUDA driver version is insufficient for CUDA runtime version' (/home/blyth/opticks/qudarap/QU.cc:144)
    junotoptask:detsimiotask.terminate  WARN: invalid state tranform ((StartUp)) => ((EndUp))
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements:  *** Break *** segmentation violation
    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================
    #0  0x00007f5ac8672fba in wait4 () from /lib64/libc.so.6
    #1  0x00007f5ac85e57e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f5ac7cc0bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f5ac7ea20f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f5ac7cbe161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f5aa41304e8 in JunoTimer::number_of_measurements (this=0x0) at /builds/JUNO/offline/junosw/Utilities/JunoTimer/JunoTimer/JunoTimer.h:32
    #7  0x00007f5aa0a401c4 in TimerAnaMgr::EndOfRunAction (this=0x7b3c0b0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/TimerAnaMgr.cc:64
    #8  0x00007f5aaa2b894a in MgrOfAnaElem::EndOfRunAction (this=0xba942b0, run=0x0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:39
    #9  0x00007f5aa0c06283 in LSExpRunAction::EndOfRunAction (this=0xbe25850, aRun=0x0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpRunAction.cc:73
    #10 0x00007f5aa94d75ed in G4RunManager::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #11 0x00007f5aa6dfc727 in G4SvcRunManager::finalizeRM (this=0x7896710) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #12 0x00007f5aaa2ade8f in DetSimAlg::finalize (this=0x78b8980) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #13 0x00007f5aabcc1d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f5aabcd6d6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007f5aabcda611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007f5aabcdabb8 in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007f5aabcd7f64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007f5aabd9383c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #19 0x00007f5ab18c1d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007f5ac8a49ae2 in subtype_dealloc (self=0x7f5aa45a22f0) at Objects/typeobject.c:1463
    #21 0x00007f5ac8a27eae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #22 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #23 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #24 0x00007f5ac8a49bf3 in subtype_dealloc (self=0x7f5ac835d9d0) at Objects/typeobject.c:1433
    #25 0x00007f5ac8a1f3ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #26 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #27 free_keys_object (keys=0x7f5ac84f7d20) at Objects/dictobject.c:664
    #28 0x00007f5ac8a2030c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #29 dict_dealloc (mp=0x7f5ac832b880) at Objects/dictobject.c:2378
    #30 0x00007f5ac8a32ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #31 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #32 module_dealloc (m=0x7f5ac83036a0) at Objects/moduleobject.c:699
    #33 0x00007f5ac8a233d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #34 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #35 insertdict (mp=0x7f5ac84c1340, key=0x7f5ac832b8b0, hash=2949966383109291102, value=<optimized out>) at Objects/dictobject.c:1304
    #36 0x00007f5ac8b18aa8 in finalize_remove_modules (verbose=0, modules=0x7f5ac84c1340) at Python/pylifecycle.c:1415
    #37 finalize_modules (tstate=tstate
    entry=0x7f5ac8e02738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #38 0x00007f5ac8b1be20 in Py_FinalizeEx () at Python/pylifecycle.c:1833



::

    123 template <typename T>
    124 T* QU::UploadArray(const T* array, unsigned num_items, const char* label ) // static
    125 {
    126     size_t size = num_items*sizeof(T) ;
    127 
    128     LOG(LEVEL)
    129        << " num_items " << num_items
    130        << " size " << size
    131        << " label " << ( label ? label : "-" )
    132        ;
    133 
    134     LOG_IF(info, MEMCHECK)
    135        << " num_items " << num_items
    136        << " size " << size
    137        << " label " << ( label ? label : "-" )
    138        ;
    139 
    140 
    141     alloc_add( label, num_items, sizeof(T) ) ;
    142 
    143     T* d_array = nullptr ;
    144     QUDA_CHECK( cudaMalloc(reinterpret_cast<void**>( &d_array ), size ));
    145     QUDA_CHECK( cudaMemcpy(reinterpret_cast<void*>( d_array ), array, size, cudaMemcpyHostToDevice ));
    146     return d_array ;
    147 }









::


    A[blyth@localhost junosw]$ vi oj_initialize.sh
    A[blyth@localhost junosw]$ vi Examples/Tutorial/share/opticks_juno.sh
    A[blyth@localhost junosw]$ source Examples/Tutorial/share/opticks_juno.sh
    A[blyth@localhost junosw]$ vi Examples/Tutorial/share/opticks_juno.sh
    A[blyth@localhost junosw]$ t oj_initialize_tut_detsim_dbg
    oj_initialize_tut_detsim_dbg () 
    { 
        source dbg__.sh || return $?;
        dbg__ $(which python) $(which tut_detsim.py) ${OJ_INITIALIZE_TUT_DETSIM_OPTION} --opticks-mode 1 --evtmax 0 gun;
        return $?
    }
    A[blyth@localhost junosw]$ BP=QU::UploadArray oj_initialize_tut_detsim_dbg





    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 **NOT** WITH_G4CXOPTICKS 
    junotoptask:DetSim0Svc.finalizeOpticks ERROR:  FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS  
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 0
    [2026-06-16 16:58:07,518] p3301854 {/cvmfs/juno.ihe





Not the same situation.


::

      source ~/j/mock_gitlab_ci/mock_gitlab_ci.sh




::

    #!/bin/sh 

    usage(){ cat << EOU

       source ~/j/mock_gitlab_ci/mock_gitlab_ci.sh

    EOU
    }


    export JUNO_OFFLINE_BUILD_BRANCH=1  ## FOR LOCAL TESTING USE BRANCHED build and InstallArea


    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
    export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
    export EXTRA_BUILD_FLAGS="JUNO_CMAKE_BUILD_TYPE=Debug"
    export JUNO_OFFLINE_OFF=1        # Disable JUNOSW setup prior to having built JUNOSW
    export OPTICKS_SETUP_VERBOSE=1   # ~/j/gitlab-ci/mockbuild.sh shows this protects against "set -eo pipefail"
    unset JUNO_OFFLINE_OFF

    printf " -----------[source \$JUNOTOP/setup.sh \n" 
    source $JUNOTOP/setup.sh
    printf " -----------]source \$JUNOTOP/setup.sh \n" 


    printf " -----------[source \$JUNO_OPTICKS_PREFIX/bashrc.sh \n" 
    source $JUNO_OPTICKS_PREFIX/bashrc
    printf " -----------]source \$JUNO_OPTICKS_PREFIX/bashrc.sh \n" 

    cd ~/junosw



    export CUDA_VISIBLE_DEVICES=""

    printf " -----------[./oj_initialize.sh \n" 
    env $EXTRA_BUILD_FLAGS OJ_DEBUG=1 BP=cudaMalloc ./oj_initialize.sh
    printf " -----------]./oj_initialize.sh \n" 






Unintended GPU upload from QBase::


    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 21305.000,     0.000,     0.000, 21305.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  0 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  1 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    stree::get_node_bb.subs i  2 SKIP DEGENERATE bb  typecode 126 [     0.000,     0.000, 18831.000,     0.000,     0.000, 18831.000] DEGENERATE
    [Detaching after vfork from child process 3308472]

    Thread 1 "python" hit Breakpoint 1.8, 0x00007fffbefc32d4 in cudaMalloc () from /data1/blyth/local/opticks_Debug/lib64/libQUDARap.so
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-610.43.02-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffbefc32d4 in cudaMalloc () from /data1/blyth/local/opticks_Debug/lib64/libQUDARap.so
    #1  0x00007fffbef25ac4 in QU::UploadArray<qbase> (array=0x2bed0db0, num_items=1, label=0x7fffbf01fe2d "QBase::init/d_base") at /home/blyth/opticks/qudarap/QU.cc:144
    #2  0x00007fffbef4e368 in QBase::init (this=0x2e8e0730) at /home/blyth/opticks/qudarap/QBase.cc:75
    #3  0x00007fffbef4e216 in QBase::QBase (this=0x2e8e0730) at /home/blyth/opticks/qudarap/QBase.cc:37
    #4  0x00007fffbee80976 in QSim::UploadComponents (ssim=0xc9724b0) at /home/blyth/opticks/qudarap/QSim.cc:124
    #5  0x00007fffc0b3e7ea in CSGOptiX::InitSim (ssim=0xc9724b0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:271
    #6  0x00007fffc0b3ee33 in CSGOptiX::Create (fd=0x21e8d5b0) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:350
    #7  0x00007fffc0ea443a in G4CXOpticks::CreateSimulator (fd=0x21e8d5b0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:424
    #8  0x00007fffc0ea3f29 in G4CXOpticks::setGeometry_ (this=0xcbe5c50, fd_=0x21e8d5b0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:370
    #9  0x00007fffc0ea3d37 in G4CXOpticks::setGeometry (this=0xcbe5c50, fd_=0x21e8d5b0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:339
    #10 0x00007fffc0ea3941 in G4CXOpticks::setGeometry (this=0xcbe5c50, world=0xac05b00) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:312
    #11 0x00007fffc0ea1af1 in G4CXOpticks::SetGeometry (world=0xac05b00) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:78
    #12 0x00007fffc0ea1da0 in G4CXOpticks::SetGeometry_JUNO (world=0xac05b00, sd=0x68554b0, jpmt=0xc8e4d50, jlut=0xc971930) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:118
    #13 0x00007fffbd745287 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xac05b00, sd=0x68554b0, ppd=0x67ef140, psd=0x66158c0, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:54
    #14 0x00007fffbd708f30 in LSExpDetectorConstruction::setupOpticks (this=0xa7f7bf0, world=0xac05b00) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #15 0x00007fffbd7087d0 in LSExpDetectorConstruction::Construct (this=0xa7f7bf0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #16 0x00007fffc6cb492e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #17 0x00007fffc6cb4afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #18 0x00007fffce088b0b in DetSimAlg::initialize (this=0x66403b0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #19 0x00007fffd24c5b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #20 0x00007fffd24db09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007fffd24e3447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #22 0x00007fffd24db048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #23 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #24 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #25 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #26 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #27 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #28 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fc3cb0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #29 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #30 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb0020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #31 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76ea0c0, func=0x7ffff76edda0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #32 PyEval_EvalCode (co=co@entry=0x4dd130, globals=globals@entry=0x7ffff76ea0c0, locals=locals@entry=0x7ffff76ea0c0) at Python/ceval.c:1148
    #33 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76ea0c0, globals=0x7ffff76ea0c0, co=0x4dd130, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #34 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cee70, globals=globals@entry=0x7ffff76ea0c0, locals=locals@entry=0x7ffff76ea0c0, flags=flags@entry=0x7ffffffe91f8, arena=arena@entry=0x7ffff7de2bb0)
        at Python/pythonrun.c:1762
    #35 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffe91f8, closeit=<optimized out>, locals=0x7ffff76ea0c0, globals=0x7ffff76ea0c0, start=257, filename=0x7ffff76cee70, fp=0x42cee0) at Python/pythonrun.c:1657
    #36 _PyRun_SimpleFileObject (fp=fp@entry=0x42cee0, filename=filename@entry=0x7ffff76cee70, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe91f8) at Python/pythonrun.c:440
    #37 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42cee0, filename=filename@entry=0x7ffff76cee70, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe91f8) at Python/pythonrun.c:79
    #38 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cee70, program_name=0x7ffff7e24c90) at Modules/main.c:360
    #39 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379




AHAH : the 

