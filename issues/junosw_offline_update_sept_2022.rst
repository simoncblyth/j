junosw_offline_update_sept_2022
==================================





Try collections/22.1.sh::





Clean up branch following accepted merge request::

    N[blyth@localhost junoenv]$ git s
    # On branch blyth-add-junoenv-libs-vlist
    nothing to commit, working directory clean
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ git help branch 
    N[blyth@localhost junoenv]$ git branch -d 
    fatal: branch name required
    N[blyth@localhost junoenv]$ git branch -d blyth-add-junoenv-libs-vlist
    error: Cannot delete the branch 'blyth-add-junoenv-libs-vlist' which you are currently on.
    N[blyth@localhost junoenv]$ git checkout main
    Switched to branch 'main'
    Your branch is behind 'origin/main' by 14 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)
    N[blyth@localhost junoenv]$ git branch -d blyth-add-junoenv-libs-vlist
    warning: deleting branch 'blyth-add-junoenv-libs-vlist' that has been merged to
             'refs/remotes/origin/blyth-add-junoenv-libs-vlist', but not yet merged to HEAD.
    Deleted branch blyth-add-junoenv-libs-vlist (was 592668b).
    N[blyth@localhost junoenv]$ git pull 
    Updating 0e0aad5..877fc01
    Fast-forward
     collections/22.1.sh      |  35 ++++++++++++++++++++
     collections/22.2.sh      |  35 ++++++++++++++++++++
     git-junoenv/git-junoenv  | 308 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     junoenv                  |  12 +++++++
     junoenv-external-libs.sh |  23 ++++++++++---
     5 files changed, 409 insertions(+), 4 deletions(-)
     create mode 100644 collections/22.1.sh
     create mode 100644 collections/22.2.sh
     create mode 100755 git-junoenv/git-junoenv
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ 




::

    N[blyth@localhost junoenv]$ git add . 
    N[blyth@localhost junoenv]$ git commit -m "add junoenv libs vlist to facilitate version overriding"
    [blyth-add-junoenv-libs-vlist 592668b] add junoenv libs vlist to facilitate version overriding
     1 file changed, 19 insertions(+), 4 deletions(-)
    N[blyth@localhost junoenv]$ git push 
    fatal: The current branch blyth-add-junoenv-libs-vlist has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-add-junoenv-libs-vlist

    N[blyth@localhost junoenv]$ git push --set-upstream origin blyth-add-junoenv-libs-vlist
    Counting objects: 255, done.
    Delta compression using up to 48 threads.
    Compressing objects: 100% (62/62), done.
    Writing objects: 100% (224/224), 23.26 KiB | 0 bytes/s, done.
    Total 224 (delta 138), reused 217 (delta 132)
    remote: Resolving deltas: 100% (138/138), completed with 31 local objects.
    remote: 
    remote: To create a merge request for blyth-add-junoenv-libs-vlist, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junoenv/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-add-junoenv-libs-vlist
    remote: 
    To git@code.ihep.ac.cn:JUNO/offline/junoenv.git
     * [new branch]      blyth-add-junoenv-libs-vlist -> blyth-add-junoenv-libs-vlist
    Branch blyth-add-junoenv-libs-vlist set up to track remote branch blyth-add-junoenv-libs-vlist from origin.
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ 






::

     282 function juno-ext-libs-PKG-version {
     283     local curpkg=$1
     284     # check override
     285     type -t juno-ext-libs-${curpkg}-version- >& /dev/null
     286     if [ "$?" = "0" ]; then
     287         # user defined 
     288         echo $(juno-ext-libs-${curpkg}-version-)
     289     else
     290         echo $(juno-ext-libs-${curpkg}-version-default)
     291     fi
     292 }





::

    N[blyth@localhost junotop]$ jx-extlib
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    == setup-juno-external-libs
    === junoenv-external-libs: allpkgs will be loaded
    === junoenv-external-libs: git cmake python python-setuptools python-pip python-cython python-numpy libyaml python-yaml boost xercesc gsl fftw3 sqlite3 mysql-connector-c mysql-connector-cpp pacparser frontier log4cpp libxml2 LHAPDF pythia6 tbb clhep xrootd ROOT hepmc geant4 genie nuwro talys gibuu libmore libonnxruntime
    === junoenv-external-libs: command: reuse
    === junoenv-external-libs: packages: git cmake python python-setuptools python-pip python-cython python-numpy libyaml python-yaml boost xercesc gsl fftw3 sqlite3 mysql-connector-c mysql-connector-cpp pacparser frontier log4cpp libxml2 LHAPDF pythia6 tbb clhep xrootd ROOT hepmc geant4 genie nuwro talys gibuu libmore libonnxruntime
    === junoenv-external-libs: create function juno-ext-libs-git-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init git
    ==== juno-ext-libs-check-init: setup dependencies for git
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: create log directory /data/blyth/junotop/junoenv/logs/git
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: create function juno-ext-libs-git-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: source /data/blyth/junotop/junoenv/packages/git.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: After source: git
    === junoenv-external-libs: juno-ext-libs-check-is-reused git
    === junoenv-external-libs: juno-ext-libs-reuse git
    ==== juno-ext-libs-reuse: git oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3
    ==== juno-ext-libs-reuse: git newpath: /data/blyth/junotop/ExternalLibs/Git/2.37.3
    ==== juno-ext-libs-reuse: git oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-cmake-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init cmake
    ==== juno-ext-libs-check-init: setup dependencies for cmake
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: create log directory /data/blyth/junotop/junoenv/logs/cmake
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: create function juno-ext-libs-cmake-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: source /data/blyth/junotop/junoenv/packages/cmake.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: After source: cmake
    === junoenv-external-libs: juno-ext-libs-check-is-reused cmake
    === junoenv-external-libs: juno-ext-libs-reuse cmake
    ==== juno-ext-libs-reuse: cmake oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Cmake/3.24.1
    ==== juno-ext-libs-reuse: cmake newpath: /data/blyth/junotop/ExternalLibs/Cmake/3.24.1
    ==== juno-ext-libs-reuse: cmake oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Cmake/3.24.1" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-python-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init python
    ==== juno-ext-libs-check-init: setup dependencies for python
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: create log directory /data/blyth/junotop/junoenv/logs/python
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: After source: python
    === junoenv-external-libs: juno-ext-libs-check-is-reused python
    === junoenv-external-libs: juno-ext-libs-reuse python
    ==== juno-ext-libs-reuse: python oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Python/3.9.14
    ==== juno-ext-libs-reuse: python newpath: /data/blyth/junotop/ExternalLibs/Python/3.9.14
    ==== juno-ext-libs-reuse: python oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Python/3.9.14" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-python-setuptools-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init python-setuptools
    ==== juno-ext-libs-check-init: setup dependencies for python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: create log directory /data/blyth/junotop/junoenv/logs/python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: create function juno-ext-libs-python-setuptools-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: source /data/blyth/junotop/junoenv/packages/python-setuptools.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: After source: python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: After source: python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: status: 0 python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: can not find /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: Please install python first.
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3
    ls: cannot access /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3: No such file or directory
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/
    total 26
    5 drwxr-xr-x.  9 cvmfs cvmfs 4096 Sep  8 23:04 ..






With CUDA 10.1 and gcc 11.2 (CUDA 10.1 max supported GCC is 8, to work with gcc 11 would need CUDA 11.5)::

    [  1%] Generating OpticksGenstep_Enum.ini
    In file included from /usr/local/cuda/include/cuda_runtime.h:83,
                     from <command-line>:
    /usr/local/cuda/include/crt/host_config.h:129:2: error: #error -- unsupported GNU version! gcc versions later than 8 are not supported!
      129 | #error -- unsupported GNU version! gcc versions later than 8 are not supported!
          |  ^~~~~
    [2022-09-26 21:30:19,444] p349597 {/data/bl


* https://rotadev.com/cuda-incompatible-with-my-gcc-version-dev/








Dwarf Error::


    N[blyth@localhost junosw]$ which gdb
    /usr/bin/gdb


    gdb -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --evtmax 2 gun
    Mon Sep 26 20:59:43 CST 2022
    GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-114.el7
    Copyright (C) 2013 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "x86_64-redhat-linux-gnu".
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>...
    Reading symbols from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Python/3.9.14/bin/python3.9...Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Python/3.9.14/bin/python3.9]
    (no debugging symbols found)...done.
    Starting program: /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --evtmax 2 gun
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/libpython3.9.so.1.0]
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_heapq.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/zlib.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_bz2.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_lzma.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/grp.cpython-39-x86_64-linux-gnu.so]
    Namespace(help_more=False, loglevel='Info', evtmax=2, input=None, input_list=None, output='sample_detsim.root', user_output='sample_detsim_user.root', profiling=True, seed=42, start_evtid=0, restore_seed_status=None, dbtype='File', mac='run.mac', vis=False, vis_mac='vis.mac', detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, K40_ACU_source_weight_QC=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=False, dfball_tube=False, simplify_calib_anchor=True, cd_enabled=True, real_surface_in_cd_enabled=True, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', additionacrylic_simplify_csg=False, pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=0.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', cerenkov_yield_factor=1.0, pmt_optical_model=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, opticks_mode=0, opticks_anamgr=False, replace_param=None, usepmtsimsvc=True, quenching=True, pmt_hit_type=1, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, split_maxhits=None, anamgr_simtrack=True, anamgr_edm_gen=True, anamgr_tt=False, anamgr_normal=True, anamgr_normal_hit=False, anamgr_muon=False, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_interesting_process=True, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='gun', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, particles='gamma', momentums=1.0, momentums_mode='Fix', momentums_extra_params=None, momentums_interp='Momentum', positions=[(0, 0, 0)], times=None, directions=None)
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6]
    warning: File "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6.0.29-gdb.py" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load:/usr/bin/mono-gdb.py".
    To enable execution of this file add
        add-auto-load-safe-path /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6.0.29-gdb.py
    line to your configuration file "/home/blyth/.gdbinit".
    To completely disable this security protection add
        set auto-load safe-path /
    line to your configuration file "/home/blyth/.gdbinit".




    ine to your configuration file "/home/blyth/.gdbinit".
    For more information about this security protection see the
    "Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
        info "(gdb)Auto-loading safe path"
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libgcc_s.so.1]
    **************************************************
    Welcome to SNiPER v2.1.0
    Running @ localhost.localdomain on Mon Sep 26 20:59:44 2022
    **************************************************
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_json.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/tbb/2020.3/lib/libtbb.so.2]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/sqlite3/3.38.5/lib/libsqlite3.so.0]
    == ROOT IO Svc ==
    == Buffer Memory Management ==
    == Random Svc ==
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/lib/libCLHEP-2.4.1.0.so]
    == Root Writer ==
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/mysql-connector-c/6.1.9/lib/libmysqlclient.so.18]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libatomic.so.1]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Xercesc/3.2.3/lib/libxerces-c-3.2.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/frontier/2.9.1/lib/libfrontier_client.so.2]
     == PMTSimParamSvc == 
    GENTOOL MODE:  gun
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/HepMC/2.06.11/lib/libHepMC.so.4]
    [(0, 0, 0)] None

    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)



::

    N[blyth@localhost ~]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/
    total 137
     5 drwxr-xr-x. 27 cvmfs cvmfs  4096 Sep 16 10:40 junosw
     1 drwxr-xr-x.  8 cvmfs cvmfs    28 Sep 16 10:39 .
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 bashrc.sh
     1 -rw-r--r--.  1 cvmfs cvmfs   908 Sep 12 21:42 setup.csh
     1 -rw-r--r--.  1 cvmfs cvmfs   911 Sep 12 21:42 setup.sh
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 tcshrc.csh
     1 drwxr-xr-x.  7 cvmfs cvmfs   207 Sep 12 21:22 mt.sniper
     5 drwxr-xr-x. 12 cvmfs cvmfs  4096 Sep 12 21:22 sniper
     1 drwxr-xr-x.  8 cvmfs cvmfs   138 Sep 12 20:38 data
    32 -rw-r--r--.  1 cvmfs cvmfs 32036 Sep 12 20:26 sniper-v0.9.1.tar.gz
    79 -rw-r--r--.  1 cvmfs cvmfs 80884 Sep 12 20:26 sniper-v2.2.2.tar.gz
     1 drwxrwxr-x.  3 cvmfs cvmfs    29 Sep 12 18:30 ..
     1 -rw-r--r--.  1 cvmfs cvmfs     0 Sep 12 18:30 .cvmfscatalog
     5 drwxr-xr-x.  9 cvmfs cvmfs  4096 Sep 12 18:20 junoenv
     1 drwxr-xr-x. 36 cvmfs cvmfs    27 Sep 12 18:19 ExternalLibs
    N[blyth@localhost ~]$ 


::

    bash junoenv libs reuse allpkgs


::

    N[blyth@localhost blyth]$ mv junotop junotop_old
    N[blyth@localhost blyth]$ mkdir junotop




WIP : get setup into git and new working approach
---------------------------------------------------

::

    epsilon:junotop blyth$ mv junoenv junoenv_svn 
    epsilon:junotop blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
    Cloning into 'junoenv'...
    remote: Enumerating objects: 313, done.
    remote: Total 313 (delta 0), reused 0 (delta 0), pack-reused 313
    Receiving objects: 100% (313/313), 153.61 KiB | 131.00 KiB/s, done.
    Resolving deltas: 100% (170/170), done.
    epsilon:junotop blyth$ 

::

    045 function junoenv-offline-checkout {
     46     # checkout all code
     47     local msg="==== $FUNCNAME: "
     48     local repourl=$1; shift
     49     local dstname=$1; shift
     50     local revision=$1; shift
     51 
     52     echo $msg checkout the code $repourl 
     53     # check
     54     git clone $repourl $dstname || exit -1
     55     cd $dstname && git checkout $revision || exit -1
     56 }


    106 function junoenv-offline {
    107     local msg="=== $FUNCNAME: "
    108     # the main handler in this script
    109     local branchname=${1:-$(junoenv-offline-default-branch)}
    110     local revision=${2:-}
    111     # check version
    112     junoenv-offline-version $branchname
    113     if [ "$?" != "0" ]; then
    114         echo $msg branchesname ret: $?
    115         return 1
    116     fi
    117 
    118 
    119     local url=$(junoenv-offline-url $branchname)
    120     echo $msg $?
    121     echo $msg URL: $url
    122     # change directory to $JUNOTOP
    123     pushd $JUNOTOP >& /dev/null
    124     junoenv-offline-checkout $url $(junoenv-offline-name) $revision
    125     junoenv-offline-preq
    126     junoenv-offline-compile
    127     popd
    128 
    129 }




libmore-data fail : judged harmless as coming from cvmfs link anyhow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HUH: libmore-data-install trying to rsync to cvmfs? ::

    === juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: After source: libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: status: 0 libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused libmore-data
    === junoenv-external-libs: juno-ext-libs-all libmore-data
    ==== juno-ext-libs-get:
    [libmore-data-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: ensdf-files-20140630.tar already exists
    ==== juno-ext-libs-conf:
    ==== juno-ext-libs-make:
    ==== juno-ext-libs-install:
    [libmore-data-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-libmore-data-install-
    [libmore-data-install] sending incremental file list
    [libmore-data-install] rsync: chgrp "/data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/." failed: Read-only file system (30)
    [libmore-data-install] ./
    [libmore-data-install] ar001.ens.bz2
    [libmore-data-install] ar001h.ens.bz2
    [libmore-data-install] ar001nn.ens.bz2
    [libmore-data-install] ar002.ens.bz2


    Last login: Fri Sep 23 19:08:47 2022 from lxslc714.ihep.ac.cn
    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/
    total 24458
    113 drwxr-xr-x. 2 cvmfs cvmfs 114688 Mar  4  2022 .
      4 -rw-r--r--. 1 cvmfs cvmfs   3529 Mar  4  2022 ar28614.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1110 Mar  4  2022 ar286cn.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2941 Mar  4  2022 ar28714.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1875 Mar  4  2022 ar28715.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2809 Mar  4  2022 ar28814.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1942 Mar  4  2022 ar28815.ens.bz2
      5 -rw-r--r--. 1 cvmfs cvmfs   4791 Mar  4  2022 ar28914.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2396 Mar  4  2022 ar28915.ens.bz2

The 0.8.3 is link to cvmfs::

    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/
    total 4
    4 drwxrwxr-x. 38 blyth blyth 4096 Jul 25 18:30 ..
    0 drwxrwxr-x.  2 blyth blyth   19 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 0.8.3 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/libmore/0.8.3
    N[blyth@localhost ~]$ 

Note that libonnxruntime has large number of github submodules::

    == junoenv-external-libs: juno-ext-libs-check-is-reused libonnxruntime
    === junoenv-external-libs: juno-ext-libs-all libonnxruntime
    ==== juno-ext-libs-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get: clone https://github.com/microsoft/onnxruntime
    [libonnxruntime-conf] Cloning into 'libonnxruntime-1.11.1'...
    [libonnxruntime-conf] Submodule 'cmake/external/FP16' (https://github.com/Maratyszcza/FP16.git) registered for path 'cmake/external/FP16'
    [libonnxruntime-conf] Submodule 'cmake/external/SafeInt/safeint' (https://github.com/dcleblanc/SafeInt.git) registered for path 'cmake/external/SafeInt/safeint'
    [libonnxruntime-conf] Submodule 'cmake/external/XNNPACK' (https://github.com/google/XNNPACK.git) registered for path 'cmake/external/XNNPACK'
    [libonnxruntime-conf] Submodule 'cmake/external/cub' (https://github.com/NVlabs/cub.git) registered for path 'cmake/external/cub'
    [libonnxruntime-conf] Submodule 'cmake/external/cxxopts' (https://github.com/jarro2783/cxxopts.git) registered for path 'cmake/external/cxxopts'
    [libonnxruntime-conf] Submodule 'cmake/external/date' (https://github.com/HowardHinnant/date.git) registered for path 'cmake/external/date'
    [libonnxruntime-conf] Submodule 'cmake/external/dlpack' (https://github.com/dmlc/dlpack.git) registered for path 'cmake/external/dlpack'
    [libonnxruntime-conf] Submodule 'cmake/external/eigen' (https://gitlab.com/libeigen/eigen.git) registered for path 'cmake/external/eigen'
    [libonnxruntime-conf] Submodule 'cmake/external/emsdk' (https://github.com/emscripten-core/emsdk.git) registered for path 'cmake/external/emsdk'
    [libonnxruntime-conf] Submodule 'cmake/external/flatbuffers' (https://github.com/google/flatbuffers.git) registered for path 'cmake/external/flatbuffers'

Even though it looks to have hung checking ps shows that some progress is being made, with movement between submodules::

    N[blyth@localhost ~]$ ps aux | grep blyth




fail : bash junoenv sniper
----------------------------

::

    N[blyth@localhost junoenv]$ source $JUNOTOP/bashrc.sh
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ bash junoenv sniper
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
    == setup-juno-basic-preq: ================================================================
    == setup-juno-sniper
    === junoenv-sniper: 0
    === junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
    === junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:00:01 --:--:--     0
      0     0    0 80884    0     0  31319      0 --:--:--  0:00:02 --:--:-- 85410
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-check-preq: Pre Requirement Check
    ==== junoenv-sniper-check-preq: source /data/blyth/junotop/bashrc.sh
    /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    /data/blyth/junotop/sniper/build /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    -- cmake version 3.24.1
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    CMake Error at /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
      Could NOT find Python3 (missing: Interpreter) (found version "3.8.12")

          Reason given by package: 
              Interpreter: Cannot run the interpreter "/data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8"

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:594 (_FPHSA_FAILURE_MESSAGE)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake:3203 (find_package_handle_standard_args)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake:490 (include)
      CMakeLists.txt:65 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost junoenv]$ 


::

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8: error while loading shared libraries: libpython3.8.so.1.0: cannot open shared object file: No such file or directory
    N[blyth@localhost junoenv]$ 



/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake::

    486 set (_PYTHON_PREFIX Python3)
    487 
    488 set (_Python3_REQUIRED_VERSION_MAJOR 3)
    489 
    490 include (${CMAKE_CURRENT_LIST_DIR}/FindPython/Support.cmake)
    491 
    492 if (COMMAND __Python3_add_library)
    493   macro (Python3_add_library)
    494     __Python3_add_library (Python3 ${ARGV})
    495   endmacro()
    496 endif()

/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake::



Huh sniper/CMake trying to use python 3.8.12 when 3.9.14 is available::

    N[blyth@localhost junoenv]$ cat $JUNOTOP/bashrc.sh 
    export JUNOTOP=/data/blyth/junotop
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Git/2.37.3/bashrc
    source /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.1.0/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/22.2.2/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.28/bashrc

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Python/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  6 blyth blyth   84 Sep 23 18:51 3.9.14
    0 drwxrwxr-x.  3 blyth blyth   34 Sep 23 18:49 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 3.8.12 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Python/3.8.12
    N[blyth@localhost junoenv]$ 

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3
    Python 3.9.14 (main, Sep 23 2022, 18:50:47) 
    [GCC 8.3.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> 


Probably update building not operational::

    N[blyth@localhost junotop]$ mv sniper sniper_old
    N[blyth@localhost junotop]$ mv mt.sniper mt.sniper_old


That gets further, failing at boost python::

    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found Python3: /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3.9 (found version "3.9.14") found components: Interpreter Development Development.Module Development.Embed 
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!


Hmm it would be easier to reuse sniper and all the external libs. 


::

    N[blyth@localhost sniper]$ cd build
    N[blyth@localhost build]$ cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
    -- cmake version 3.24.1
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost build]$ 



sniper/CMakeLists.txt is looking for Boost 1.67::

     57 # Config for Option USE_PYTHON
     58 if(USE_PYTHON)
     59     #python
     60     set(PyPkgName Python3)  #Use Python3 by default
     61     option(USE_PYTHON2 "Use Python2 instead of Python3" OFF)
     62     if(USE_PYTHON2)
     63         set(PyPkgName Python2)
     64     endif()
     65     find_package(${PyPkgName} COMPONENTS Interpreter Development REQUIRED)
     66     message(STATUS "python version ${${PyPkgName}_VERSION}")
     67     set(PYTHON_VERSION "${${PyPkgName}_VERSION}")
     68     set(PYTHON_INCLUDE_DIRS "${${PyPkgName}_INCLUDE_DIRS}")
     69     set(PYTHON_LIBRARY "${${PyPkgName}_LIBRARIES}")
     70     #boost.python
     71     set(Boost_USE_MULTITHREADED OFF)
     72     set(BoostPyVer "${${PyPkgName}_VERSION_MAJOR}${${PyPkgName}_VERSION_MINOR}")
     73     find_package(Boost 1.67 COMPONENTS python${BoostPyVer} REQUIRED)
     74     set(BOOST_PYTHON_LIBRARY "${Boost_PYTHON${BoostPyVer}_LIBRARY}")
     75     unset(BoostPyVer)
     76     #python install dir
     77     if(NOT CMAKE_INSTALL_PYTHONDIR)
     78         set(CMAKE_INSTALL_PYTHONDIR "python")
     79     endif()
     80     #...
     81     add_definitions(-DHAVE_PYTHON)
     82     unset(PyPkgName)
     83 endif()


::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Boost/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  2 blyth blyth   20 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   89 Mar  2  2022 1.78.0 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/
    total 2
    1 drwxr-xr-x. 37 cvmfs cvmfs 36 May 26 16:39 ..
    1 drwxr-xr-x.  4 cvmfs cvmfs 80 Mar  4  2022 1.78.0
    1 drwxr-xr-x.  3 cvmfs cvmfs 28 Jan  5  2022 .
    N[blyth@localhost junoenv]$ 






N[blyth@localhost build]$  cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
-- cmake version 3.24.1
-- python version 3.9.14
CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
  Found package configuration file:

    /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

  but it set boost_python_FOUND to FALSE so package "boost_python" is
  considered to be NOT FOUND.  Reason given by package:

  No suitable build variant has been found.

  The following variants have been tried and rejected:

  * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

  * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

Call Stack (most recent call first):
  /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
  /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
  CMakeLists.txt:73 (find_package)


-- Configuring incomplete, errors occurred!
See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
N[blyth@localhost build]$ 



::

    N[blyth@localhost Boost]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/*python*.*
    644 -rw-r--r--. 1 cvmfs cvmfs 659132 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.a
    334 -rwxr-xr-x. 1 cvmfs cvmfs 341264 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so.1.78.0
      1 lrwxrwxrwx. 1 cvmfs cvmfs     27 Jan  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so -> libboost_python38.so.1.78.0
    N[blyth@localhost Boost]$ 





