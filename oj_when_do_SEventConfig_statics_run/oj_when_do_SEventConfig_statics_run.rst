oj_when_do_SEventConfig_statics_run.rst
========================================



Set breakpoint on the compiler generated function that sets all the SEventConfig statics::

    _GLOBAL__sub_I_SEventConfig.cc 


::

    A[blyth@localhost junosw]$ BP="SEventConfig::Initialize,_GLOBAL__sub_I_SEventConfig.cc"  TEST=hit2 ojet
    Setup Official junosw (CMake version)
    === opticks-setup-        add     append                 PATH /usr/local/cuda-12.4/bin
    === opticks-setup-        add     append                 PATH /data1/blyth/local/opticks_Debug/bin
    === opticks-setup-        add     append                 PATH /data1/blyth/local/opticks_Debug/lib
    === opticks-setup-        add     append           PYTHONPATH /data1/blyth/local/opticks_Debug/py
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /data1/blyth/local/opticks_Debug
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /data1/blyth/local/opticks_Debug/externals
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    === opticks-setup-      nodir     append      PKG_CONFIG_PATH /data1/blyth/local/opticks_Debug/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /data1/blyth/local/opticks_Debug/lib64/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /data1/blyth/local/opticks_Debug/externals/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /data1/blyth/local/opticks_Debug/externals/lib64/pkgconfig
    === opticks-setup-        add     append      LD_LIBRARY_PATH /data1/blyth/local/opticks_Debug/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /data1/blyth/local/opticks_Debug/lib64
    === opticks-setup-        add     append      LD_LIBRARY_PATH /data1/blyth/local/opticks_Debug/externals/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /data1/blyth/local/opticks_Debug/externals/lib64
    === opticks-setup-      nodir     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib64
    /data1/blyth/local/opticks_Debug/bashrc - USE DETECTED GEANT4 ENVIRONMENT
    oj_geomsetup is a function
    oj_geomsetup () 
    { 
        : opticks_juno.sh;
        : extra env settings needed by Opticks-JUNOSW geometry conversion;
        : NB this is sourced from envset.sh so needs to be appropriate to every usage;
        : not just the .gitlab-ci.yml one off first runs;
        if [ -n "$OJ_VERBOSE" ]; then
            type $FUNCNAME;
        fi;
        export GEOM=$OJ_SLUG;
        export OJ_PREFIX=$(dirname $(dirname $(realpath $BASH_SOURCE)));
        export OJ_GEOMDIR=$OJ_PREFIX/.opticks/GEOM/${GEOM};
        export ${GEOM}_CFBaseFromGEOM=${OJ_GEOMDIR};
        export CSGOptiXRenderInteractiveTest__FRAME_HOP=1;
        export stree__FREQ_CUT=300;
        export stree__force_triangulate_solid="filepath:${OJ_GEOMDIR}/CSGFoundry/tessname.txt";
        export SScene__initFromTree_addFrames=${OJ_GEOMDIR}/CSGFoundry/framespec.txt;
        local vv="FUNCNAME OJ_SLUG GEOM BASH_SOURCE OJ_PREFIX OJ_GEOMDIR ${GEOM}_CFBaseFromGEOM stree__force_triangulate_solid SScene__initFromTree_addFrames";
        for v in $vv;
        do
            printf "%30s : %s\n" "$v" "${!v}";
        done;
        unset WaterPoolConstruction__CONFIG;
        export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10;
        export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10;
        export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10;
        export R12860OnlyFrontMaskManager__MAGIC_virtual_thickness_MM=0.10;
        export U4Mesh__NumberOfRotationSteps_DUMP=1;
        export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480;
        : four large solids are triangulated due to subtraction of Waterdistributor - so they need more rotation steps;
        local pfxs="sInnerWater sInnerReflectorInCD sOuterWaterInCD sOuterReflectorInCD";
        for pfx in $pfxs;
        do
            export U4Mesh__NumberOfRotationSteps_solidName_${pfx}_TSubWaterDistributor_cutTube2=480;
        done;
        : NumberOfRotationSteps operates at the level of the full torus;
        : rather than the small segment of the torus, so quite a large number of rotation;
        : steps is needed to prevent the tesselated guidetube from impinging into the acrylic;
        export OPTICKS_HIT_MASK=EC;
        return 0
    }
                          FUNCNAME : oj_geomsetup
                           OJ_SLUG : J25_4_0_opticks_Debug
                              GEOM : J25_4_0_opticks_Debug
                       BASH_SOURCE : /home/blyth/junosw/InstallArea/bin/opticks_juno.sh
                         OJ_PREFIX : /home/blyth/junosw/InstallArea
                        OJ_GEOMDIR : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug
    J25_4_0_opticks_Debug_CFBaseFromGEOM : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug
    stree__force_triangulate_solid : filepath:/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/tessname.txt
    SScene__initFromTree_addFrames : /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/framespec.txt
    /tmp/blyth/opticks/oj_envset_test/hit2 ~/junosw
                       BASH_SOURCE : /home/blyth/j/local.sh
                          FUNCNAME : vvp
                              test : default
                              TEST : hit2
                            LOGDIR : /tmp/blyth/opticks/oj_envset_test/hit2
                               PWD : /tmp/blyth/opticks/oj_envset_test/hit2
                      SProf__WRITE : 1
    gdb -ex "set breakpoint pending on" -ex "break SEventConfig::Initialize" -ex "break _GLOBAL__sub_I_SEventConfig.cc " -ex "info break" -ex r --args /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Python/3.11.10/bin/python /home/blyth/junosw/InstallArea/bin/tut_detsim.py --evtmax 1 --pmt-hit-type 2 gun
    Thu Nov 13 03:17:19 PM CST 2025
    GNU gdb (AlmaLinux) 14.2-4.1.el9_6
    Copyright (C) 2023 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.
    Type "show copying" and "show warranty" for details.
    This GDB was configured as "x86_64-redhat-linux-gnu".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <https://www.gnu.org/software/gdb/bugs/>.
    Find the GDB manual and other documentation resources online at:
        <http://www.gnu.org/software/gdb/documentation/>.

    For help, type "help".
    Type "apropos word" to search for commands related to "word"...
    Reading symbols from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Python/3.11.10/bin/python...
    Function "SEventConfig::Initialize" not defined.
    Breakpoint 1 (SEventConfig::Initialize) pending.
    Function "_GLOBAL__sub_I_SEventConfig.cc" not defined.
    Breakpoint 2 (_GLOBAL__sub_I_SEventConfig.cc) pending.
    Num     Type           Disp Enb Address    What
    1       breakpoint     keep y   <PENDING>  SEventConfig::Initialize
    2       breakpoint     keep y   <PENDING>  _GLOBAL__sub_I_SEventConfig.cc
    Starting program: /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Python/3.11.10/bin/python /home/blyth/junosw/InstallArea/bin/tut_detsim.py --evtmax 1 --pmt-hit-type 2 gun
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    [Detaching after vfork from child process 995742]
    [Detaching after vfork from child process 995745]
    [Detaching after vfork from child process 995749]
    [New Thread 0x7fffcd5ff640 (LWP 995752)]
    [Detaching after vfork from child process 995753]
    **************************************************
    Welcome to SNiPER v2.1.0
    Running @ localhost.localdomain on Thu Nov 13 15:17:24 2025
    **************************************************
    [2025-11-13 15:17:26,361] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:52} INFO - [__init__
    [2025-11-13 15:17:26,551] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:107} INFO - end of init_yaml_conf
    [2025-11-13 15:17:26,551] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:60} INFO - ]__init__
    [2025-11-13 15:17:26,551] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:76} INFO - end of register
    [2025-11-13 15:17:26,551] p995736 {/home/blyth/junosw/InstallArea/bin/tut_detsim.py:49} INFO - after juno_application.register(detsim_module) 
    [2025-11-13 15:17:26,551] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:159} INFO - [JUNOApplication.run
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='sample_detsim.root', user_output='sample_detsim_user.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=False, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=0.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=1, opticks_anamgr=False, replace_param=None, usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=False, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=False, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='gun', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, particles='gamma', momentums=1.0, momentums_mode='Fix', momentums_extra_params=None, momentums_interp='Momentum', positions=[(0, 0, 0)], times=None, directions=None)
    [2025-11-13 15:17:26,645] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:152} INFO - [init
    [2025-11-13 15:17:26,645] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:915} INFO - [init_rootio_buffer
    == Buffer Memory Management ==
    [2025-11-13 15:17:26,722] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:978} INFO - ]init_rootio_buffer
    [2025-11-13 15:17:26,722] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:982} INFO - init_dbsvc
    [2025-11-13 15:17:26,722] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1029} INFO - init_random_service
    [2025-11-13 15:17:26,764] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1054} INFO - init_rootwriter
    [2025-11-13 15:17:26,765] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1064} INFO - init_global_time
    [2025-11-13 15:17:26,765] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1074} INFO - init_juno_timer
    [2025-11-13 15:17:26,806] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1812} INFO - [init_opticks_environ
    [2025-11-13 15:17:26,806] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1814} INFO - ]init_opticks_environ
    [2025-11-13 15:17:26,806] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1823} INFO - [init_mc_parameters
    [2025-11-13 15:17:26,806] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNODetSimModule.py:1825} INFO - -init_mc_parameters.loadDll.libMultiFilmLUTMakerSvc[

    Thread 1 "python" hit Breakpoint 2, _GLOBAL__sub_I_SEventConfig.cc(void) () at /home/blyth/opticks/sysrap/SEventConfig.cc:1823
    1823	}
    (gdb) 


    (gdb) bt
    #0  _GLOBAL__sub_I_SEventConfig.cc(void) () at /home/blyth/opticks/sysrap/SEventConfig.cc:1823
    #1  0x00007ffff7fcc51e in call_init (env=0x4bdfc0, argv=0x7fffffff0198, argc=7, l=<optimized out>) at dl-init.c:70
    #2  call_init (l=<optimized out>, argc=7, argv=0x7fffffff0198, env=0x4bdfc0) at dl-init.c:26
    #3  0x00007ffff7fcc60c in _dl_init (main_map=0x66ab040, argc=7, argv=0x7fffffff0198, env=0x4bdfc0) at dl-init.c:117
    #4  0x00007ffff7fc94d6 in __GI__dl_catch_exception (exception=exception@entry=0x0, operate=operate@entry=0x7ffff7fd3060 <call_dl_init>, args=args@entry=0x7ffffffef590) at dl-catch.c:211
    #5  0x00007ffff7fd2ffe in dl_open_worker (a=a@entry=0x7ffffffef730) at dl-open.c:797
    #6  0x00007ffff7fc9445 in __GI__dl_catch_exception (exception=exception@entry=0x7ffffffef710, operate=operate@entry=0x7ffff7fd2f60 <dl_open_worker>, args=args@entry=0x7ffffffef730) at dl-catch.c:237
    #7  0x00007ffff7fd33ff in _dl_open (file=<optimized out>, mode=-2147483391, caller_dlopen=0x7fffd0ae8955 <Sniper::loadDll(char const*)+277>, nsid=-2, argc=7, argv=0x7fffffff0198, env=0x4bdfc0) at dl-open.c:873
    #8  0x00007ffff748674c in dlopen_doit () from /lib64/libc.so.6
    #9  0x00007ffff7fc9445 in __GI__dl_catch_exception (exception=exception@entry=0x7ffffffef900, operate=0x7ffff74866f0 <dlopen_doit>, args=0x7ffffffef9a0) at dl-catch.c:237
    #10 0x00007ffff7fc9593 in _dl_catch_error (objname=0x7ffffffef958, errstring=0x7ffffffef960, mallocedp=0x7ffffffef957, operate=<optimized out>, args=<optimized out>) at dl-catch.c:256
    #11 0x00007ffff748621e in _dlerror_run () from /lib64/libc.so.6
    #12 0x00007ffff7486801 in dlopen@GLIBC_2.2.5 () from /lib64/libc.so.6
    #13 0x00007fffd0ae8955 in Sniper::loadDll(char const*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffccbc9c38 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<void (*)(char const*), boost::python::default_call_policies, boost::mpl::vector2<void, char const*> > >::operator()(_object*, _object*) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007fffdf0bd515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007fffdf0bd728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffdf0c2443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffdf0bb182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fafb40, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e4fc0, func=0x7ffff7e649a0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co@entry=0x4ebd90, globals=globals@entry=0x7ffff76e4fc0, locals=locals@entry=0x7ffff76e4fc0) at Python/ceval.c:1148
    #24 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e4fc0, globals=0x7ffff76e4fc0, co=0x4ebd90, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7dfb130, globals=globals@entry=0x7ffff76e4fc0, locals=locals@entry=0x7ffff76e4fc0, flags=flags@entry=0x7ffffffeff18, arena=arena@entry=0x7ffff7de6b70) at Python/pythonrun.c:1762
    #26 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffeff18, closeit=<optimized out>, locals=0x7ffff76e4fc0, globals=0x7ffff76e4fc0, start=257, filename=0x7ffff7dfb130, fp=0x407e90) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp@entry=0x407e90, filename=filename@entry=0x7ffff7dfb130, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeff18) at Python/pythonrun.c:440
    #28 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x407e90, filename=filename@entry=0x7ffff7dfb130, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeff18) at Python/pythonrun.c:79
    #29 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7dfb130, program_name=0x7ffff7e2a550) at Modules/main.c:360
    #30 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffffffeff14) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007ffff7ab95b7 in pymain_main (args=0x7fffffff0020) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6



