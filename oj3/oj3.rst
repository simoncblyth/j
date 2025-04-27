oj3
====


TODO : arrange for InputPhotons from release
-----------------------------------------------

Hmm too big for adding to dist tarball::

    A[blyth@localhost tests]$ du -h ~/.opticks/InputPhotons/
    274M	/home/blyth/.opticks/InputPhotons/


SEvt defaulting to  HOME paths for inputs
--------------------------------------------

::

     320 const char* SEvt::INPUT_GENSTEP_DIR = spath::Resolve("${SEvt__INPUT_GENSTEP_DIR:-$HOME/.opticks/InputGensteps}") ;
     321 const char* SEvt::INPUT_PHOTON_DIR = spath::Resolve("${SEvt__INPUT_PHOTON_DIR:-$HOME/.opticks/InputPhotons}") ;


Trying OJ release opticksMode 3 on A
---------------------------------------

Pilot error, prior to switching off the other anamgr get wierd error::

    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbe93dbfc in SEvt::rjoinPhoton (this=0x6995d80, label=...) at /home/blyth/opticks/sysrap/SEvt.cc:2569
    #6  0x00007fffc0dd9f4e in U4Recorder::PreUserTrackingAction_Optical (this=0x6995d50, track=0xc345fb00) at /home/blyth/opticks/u4/U4Recorder.cc:482
    #7  0x00007fffc0dd95a8 in U4Recorder::PreUserTrackingAction (this=0x6995d50, track=0xc345fb00) at /home/blyth/opticks/u4/U4Recorder.cc:379
    #8  0x00007fffbdba5780 in U4RecorderAnaMgr::PreUserTrackingAction (this=0x67b7ee0, trk=0xc345fb00) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:37
    #9  0x00007fffcf354d92 in MgrOfAnaElem::PreUserTrackingAction (this=0x8f1de40, trk=0xc345fb00) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #10 0x00007fffbdfc9def in LSExpTrackingAction::PreUserTrackingAction (this=0x9239a60, aTrack=0xc345fb00) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpTrackingAction.cc:37
    #11 0x00007fffc663a880 in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #12 0x00007fffc6bc6565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x00007fffe038568e in G4SvcRunManager::SimulateEvent (this=0x6751470, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #14 0x00007fffcf349d3e in DetSimAlg::execute (this=0x670eaf0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #15 0x00007fffd422b4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so
    #16 0x00007fffd422fbbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/sniper/InstallArea/lib64/libSniperKernel.so
    ...
    (gdb) f 5
    #5  0x00007fffbe93dbfc in SEvt::rjoinPhoton (this=0x6995d80, label=...) at /home/blyth/opticks/sysrap/SEvt.cc:2569
    warning: Source file is more recent than executable.
    2569	    bool in_range = idx < pho.size() ;
    (gdb) p idx
    $1 = 0
    (gdb) p pho.size()
    $2 = 0
    (gdb) 

    (gdb) p SEventConfig::EventMode
    $4 = {const char *(void)} 0x7fffbe9239b4 <SEventConfig::EventMode()>
    (gdb) p SEventConfig::EventMode()
    $5 = 0x7fffffff805b "DebugLite"
    (gdb) p SEventConfig::IntegrationMode()
    $6 = 3

    (gdb) p record.size()
    $7 = 0
    (gdb) p seq.size()
    $8 = 0
    (gdb) 

    (gdb) p genstep.size()
    $10 = 1

    (gdb) p gs.size()
    $11 = 1





oj3 shakedown
----------------


::

    A[blyth@localhost ~]$ oj3dbg  env_info_chi2
    [ source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/envset.sh
    Setup Official junosw (CMake version)
    === opticks-setup-        add     append                 PATH /usr/local/cuda-12.4/bin
    === opticks-setup-        add     append                 PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin
    === opticks-setup-        add     append                 PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/lib
    === opticks-setup-        add     append           PYTHONPATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/py
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/externals
    === opticks-setup-        add     append    CMAKE_PREFIX_PATH /cvmfs/opticks.ihep.ac.cn/external/OptiX_800
    === opticks-setup-      nodir     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/lib64/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/externals/lib/pkgconfig
    === opticks-setup-        add     append      PKG_CONFIG_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/externals/lib64/pkgconfig
    === opticks-setup-        add     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/lib64
    === opticks-setup-        add     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/externals/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/externals/lib64
    === opticks-setup-      nodir     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib
    === opticks-setup-        add     append      LD_LIBRARY_PATH /usr/local/cuda-12.4/lib64
    === opticks-setup-geant4- : sourcing /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4.sh
    oj_geomsetup is a function
    oj_geomsetup () 
    { 
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
        export stree__force_triangulate_solid="filepath:${OJ_GEOMDIR}/CSGFoundry/tessname.txt";
        export SScene__initFromTree_addFrames=${OJ_GEOMDIR}/CSGFoundry/framespec.txt;
        local vv="FUNCNAME OJ_SLUG GEOM BASH_SOURCE OJ_PREFIX OJ_GEOMDIR ${GEOM}_CFBaseFromGEOM stree__force_triangulate_solid SScene__initFromTree_addFrames";
        for v in $vv;
        do
            printf "%30s : %s\n" "$v" "${!v}";
        done;
        export WaterPoolConstruction__CONFIG=3;
        export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10;
        export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10;
        export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10;
        unset U4Mesh__NumberOfRotationSteps_DUMP;
        export U4Mesh__NumberOfRotationSteps_DUMP=1;
        export U4Mesh__NumberOfRotationSteps_entityType_G4Torus=480;
        : NumberOfRotationSteps operates at the level of the full torus;
        : rather than the small segment of the torus, so quite a large number of rotation;
        : steps is needed to prevent the tesselated guidetube from impinging into the acrylic;
        return 0
    }
                          FUNCNAME : oj_geomsetup
                           OJ_SLUG : J25_3_0_Opticks_v0_4_0
                              GEOM : J25_3_0_Opticks_v0_4_0
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/bin/opticks_juno.sh
                         OJ_PREFIX : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat
                        OJ_GEOMDIR : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/.opticks/GEOM/J25_3_0_Opticks_v0_4_0
    J25_3_0_Opticks_v0_4_0_CFBaseFromGEOM : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/.opticks/GEOM/J25_3_0_Opticks_v0_4_0
    stree__force_triangulate_solid : filepath:/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/.opticks/GEOM/J25_3_0_Opticks_v0_4_0/CSGFoundry/tessname.txt
    SScene__initFromTree_addFrames : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/.opticks/GEOM/J25_3_0_Opticks_v0_4_0/CSGFoundry/framespec.txt
    ] source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/envset.sh
    logging is a function
    logging () 
    { 
        type $FUNCNAME;
        export QU=INFO;
        export SEvt__LIFECYCLE=1;
        export SEvt=INFO;
        export U4Recorder=INFO
    }
             BASH_SOURCE : /home/blyth/oj/oj3.sh
                       0 : /home/blyth/oj/oj3.sh
                  defarg : env_info_run_chi2
                     arg : env_info_chi2
                  envset : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/envset.sh
                 _envset : /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/envset.sh
          OPTICKS_SCRIPT : oj3_sh
               OJ_LOGDIR : /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh
                     LOG : 1
                     DBG : 1
                     CMD : gdb -ex r --args /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.3.0/ExternalLibs/Python/3.11.10/bin/python  /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/bin/tut_detsim.py --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer --opticks-anamgr --evtmax 1 --no-toptask-show --opticks-mode 3 gun
                    GEOM : J25_3_0_Opticks_v0_4_0
      OPTICKS_MAX_BOUNCE : 31
                   AFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/A000
                   BFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/B000
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_Opticks_v0_4_0
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin 
                              FOLD : /data1/blyth/tmp/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin/sseq_index_test.sh 
                              SDIR : /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/A000 
                             BFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/B000 
    SLOG::EnvLevel adjusting loglevel by envvar   key SEvt level INFO fallback DEBUG upper_level INFO
    a_path $AFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/A000/seq.npy a_seq (9063, 2, 2, )
    b_path $BFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_no_opticks_event_name/B000/seq.npy b_seq (9063, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u.size 4914 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   487.9809 ndf 29.0000 sum/ndf    16.8269 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        SI AB                                                                                            :    1401   1431 :     0.3178 : Y :     100    123 :   
        SI BT BT BT BT BT BT SD                                                                          :      -1    494 :     0.0000 : N :      -1    118 : AZERO C2EXC  
        SI RE AB                                                                                         :     434    410 :     0.6825 : Y :     117    115 :   
        SI BT BT BT BT BT BT SA                                                                          :      -1    420 :     0.0000 : N :      -1    153 : AZERO C2EXC  
        SI SC AB                                                                                         :     287    272 :     0.4025 : Y :     116    210 :   
        SI BT BT BT BT BT BT    SA                                                                       :     265     -1 :     0.0000 : N :      96     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT SD                                                                       :      -1    213 :     0.0000 : N :      -1    147 : AZERO C2EXC  
        SI BT BT BT BT BT BT    SR SA                                                                    :     206     -1 :     0.0000 : N :     201     -1 : BZERO C2EXC  
    :r:`SI SC BT BT BT BT BT BT SA                                                                       :       4    172 :   160.3636 : Y :    1019    112 : DEVIANT  `
        SI RE BT BT BT BT BT BT SD                                                                       :      -1    155 :     0.0000 : N :      -1    121 : AZERO C2EXC  
        SI RE RE AB                                                                                      :     132    130 :     0.0153 : Y :     251    120 :   
    :r:`SI RE BT BT BT BT BT BT SA                                                                       :       2    129 :   123.1221 : Y :    8250    195 : DEVIANT  `
        SI BT BT SA                                                                                      :     107    119 :     0.6372 : Y :     256    137 :   
        CK AB                                                                                            :     117    115 :     0.0172 : Y :       2      1 :   
        SI BT BT BT BT BT BT BT SA                                                                       :      -1     94 :     0.0000 : N :      -1    225 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT    SA                                                                    :      93     -1 :     0.0000 : N :     109     -1 : BZERO C2EXC  
        SI RE SC AB                                                                                      :      93     90 :     0.0492 : Y :     126    370 :   
        SI RE BT BT BT BT BT BT    SA                                                                    :      90     -1 :     0.0000 : N :     113     -1 : BZERO C2EXC  
    :r:`SI SC SC BT BT BT BT BT BT SD                                                                    :       4     90 :    78.6809 : Y :     628    322 : DEVIANT  `
        SI SC BT BT BT BT BT BT    SR SA                                                                 :      89     -1 :     0.0000 : N :     141     -1 : BZERO C2EXC  
        SI BT BT AB                                                                                      :      89     83 :     0.2093 : Y :     255    142 :   
        SI SC SC AB                                                                                      :      79     88 :     0.4850 : Y :     413    138 :   
        SI BT BT BT BT BT BT BT SR SA                                                                    :      -1     77 :     0.0000 : N :      -1    219 : AZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR SA                                                                 :      74     -1 :     0.0000 : N :     399     -1 : BZERO C2EXC  
    :r:`SI SC SC BT BT BT BT BT BT SA                                                                    :       4     74 :    62.8205 : Y :    2298    192 : DEVIANT  `
        SI RE SC BT BT BT BT BT BT SD                                                                    :      -1     67 :     0.0000 : N :      -1    295 : AZERO C2EXC  
        SI BT BT BT SA                                                                                   :      65     63 :     0.0312 : Y :     149    182 :   
        SI RE SC BT BT BT BT BT BT SA                                                                    :      -1     63 :     0.0000 : N :      -1    599 : AZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SA                                                                 :      62     -1 :     0.0000 : N :     114     -1 : BZERO C2EXC  
    :r:`SI RE RE BT BT BT BT BT BT SA                                                                    :       1     51 :    48.0769 : Y :    1244     95 : DEVIANT  `
        SI BT BT BT BT SD                                                                                :      51     48 :     0.0909 : Y :     185    129 :   
        SI SC SC SC BT BT BT BT BT BT SD                                                                 :      -1     48 :     0.0000 : N :      -1    145 : AZERO C2EXC  
        SI BT BT DR BT SA                                                                                :      31     46 :     2.9221 : Y :     523    212 :   
        SI BT AB                                                                                         :      40     46 :     0.4186 : Y :     333    190 :   
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                               :      44     -1 :     0.0000 : N :     995     -1 : BZERO C2EXC  
        SI RE SC BT BT BT BT BT BT    SA                                                                 :      42     -1 :     0.0000 : N :     240     -1 : BZERO C2EXC  
        SI RE RE RE AB                                                                                   :      41     28 :     2.4493 : Y :     135    972 :   
        SI SC SC SC AB                                                                                   :      40     39 :     0.0127 : Y :     427    107 :   
        SI SC BT BT AB                                                                                   :      40     39 :     0.0127 : Y :     325    716 :   
        SI SC BT BT BT BT BT BT BT SR SA                                                                 :      -1     38 :     0.0000 : N :      -1    109 : AZERO C2EXC  
        SI RE RE BT BT BT BT BT BT SD                                                                    :      -1     37 :     0.0000 : N :      -1    560 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SR SR SA                                                                 :      -1     37 :     0.0000 : N :      -1    161 : AZERO C2EXC  
        SI SC RE AB                                                                                      :      31     36 :     0.3731 : Y :     602    180 :   
        SI SC SC BT BT BT BT BT BT    SA                                                                 :      33     -1 :     0.0000 : N :     893     -1 : BZERO C2EXC  
        SI RE BT BT AB                                                                                   :      32     32 :     0.0000 : Y :     191    314 :   
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT AB                                         :      32     -1 :     0.0000 : N :     284     -1 : BZERO C2EXC  
        SI SC BT BT SA                                                                                   :      32     27 :     0.4237 : Y :     143    248 :   
        SI RE RE SC AB                                                                                   :      27     31 :     0.2759 : Y :     202    183 :   
        SI SC BT BT BT BT BT BT BT SA                                                                    :      -1     31 :     0.0000 : N :      -1    767 : AZERO C2EXC  
        SI RE BT BT SA                                                                                   :      27     30 :     0.1579 : Y :     123    260 :   
        SI RE RE BT BT BT BT BT BT    SA                                                                 :      29     -1 :     0.0000 : N :     107     -1 : BZERO C2EXC  
        SI RE SC SC AB                                                                                   :      28     22 :     0.7200 : Y :     340    392 :   
        SI SC BT AB                                                                                      :      14     27 :     4.1220 : Y :    1312    105 :   
        SI RE RE BT BT BT BT BT BT    SR SA                                                              :      27     -1 :     0.0000 : N :     981     -1 : BZERO C2EXC  
        SI RE SC BT BT BT BT BT BT    SR SA                                                              :      27     -1 :     0.0000 : N :     230     -1 : BZERO C2EXC  
        SI SC SC BT BT BT BT BT BT    SR SA                                                              :      26     -1 :     0.0000 : N :    1090     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                            :      26     -1 :     0.0000 : N :     169     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR SR SA                                                              :      25     -1 :     0.0000 : N :     215     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SR SR SA                                                              :      25     -1 :     0.0000 : N :     308     -1 : BZERO C2EXC  
        SI SC BT BT BT SA                                                                                :      16     24 :     0.0000 : N :     293    250 : C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u.size 4914 opt AZERO mode 1
        SI BT BT BT BT BT BT SD                                                                          :      -1    494 :     0.0000 : N :      -1    118 : AZERO C2EXC  
        SI BT BT BT BT BT BT SA                                                                          :      -1    420 :     0.0000 : N :      -1    153 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT SD                                                                       :      -1    213 :     0.0000 : N :      -1    147 : AZERO C2EXC  
        SI RE BT BT BT BT BT BT SD                                                                       :      -1    155 :     0.0000 : N :      -1    121 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SA                                                                       :      -1     94 :     0.0000 : N :      -1    225 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SR SA                                                                    :      -1     77 :     0.0000 : N :      -1    219 : AZERO C2EXC  
        SI RE SC BT BT BT BT BT BT SD                                                                    :      -1     67 :     0.0000 : N :      -1    295 : AZERO C2EXC  
        SI RE SC BT BT BT BT BT BT SA                                                                    :      -1     63 :     0.0000 : N :      -1    599 : AZERO C2EXC  
        SI SC SC SC BT BT BT BT BT BT SD                                                                 :      -1     48 :     0.0000 : N :      -1    145 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT BT SR SA                                                                 :      -1     38 :     0.0000 : N :      -1    109 : AZERO C2EXC  
        SI RE RE BT BT BT BT BT BT SD                                                                    :      -1     37 :     0.0000 : N :      -1    560 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SR SR SA                                                                 :      -1     37 :     0.0000 : N :      -1    161 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT BT SA                                                                    :      -1     31 :     0.0000 : N :      -1    767 : AZERO C2EXC  
        SI RE BT BT BT BT BT BT BT SR SA                                                                 :      -1     24 :     0.0000 : N :      -1    712 : AZERO C2EXC  
        SI RE BT BT BT BT BT BT BT SA                                                                    :      -1     24 :     0.0000 : N :      -1    264 : AZERO C2EXC  
        SI SC SC SC BT BT BT BT BT BT SA                                                                 :      -1     24 :     0.0000 : N :      -1    110 : AZERO C2EXC  
        SI BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                               :      -1     24 :     0.0000 : N :      -1    125 : AZERO C2EXC  
        SI RE SC SC BT BT BT BT BT BT SD                                                                 :      -1     23 :     0.0000 : N :      -1    262 : AZERO C2EXC  
        SI RE RE SC BT BT BT BT BT BT SD                                                                 :      -1     22 :     0.0000 : N :      -1     98 : AZERO C2EXC  
        SI BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SD                                               :      -1     20 :     0.0000 : N :      -1    457 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SR SR SR SA                                                              :      -1     19 :     0.0000 : N :      -1    303 : AZERO C2EXC  
        SI BT BT BT BT BT BT BT SD                                                                       :      -1     19 :     0.0000 : N :      -1    224 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT BT SD                                                                    :      -1     19 :     0.0000 : N :      -1    166 : AZERO C2EXC  
        SI RE SC SC BT BT BT BT BT BT SA                                                                 :      -1     19 :     0.0000 : N :      -1    339 : AZERO C2EXC  
        SI RE RE SC BT BT BT BT BT BT SA                                                                 :      -1     16 :     0.0000 : N :      -1    321 : AZERO C2EXC  
        SI RE RE RE SC BT BT BT BT BT BT SD                                                              :      -1     15 :     0.0000 : N :      -1    405 : AZERO C2EXC  
        SI SC RE BT BT BT BT BT BT SD                                                                    :      -1     15 :     0.0000 : N :      -1    809 : AZERO C2EXC  
        SI SC BT BT BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                            :      -1     14 :     0.0000 : N :      -1   1069 : AZERO C2EXC  
        SI RE RE RE BT BT BT BT BT BT SD                                                                 :      -1     12 :     0.0000 : N :      -1    647 : AZERO C2EXC  
        SI RE BT BT BT BT BT BT BT SR SR SA                                                              :      -1     12 :     0.0000 : N :      -1   1035 : AZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u.size 4914 opt BZERO mode 2
        SI BT BT BT BT BT BT    SA                                                                       :     265     -1 :     0.0000 : N :      96     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SA                                                                    :     206     -1 :     0.0000 : N :     201     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SA                                                                    :      93     -1 :     0.0000 : N :     109     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SA                                                                    :      90     -1 :     0.0000 : N :     113     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SR SA                                                                 :      89     -1 :     0.0000 : N :     141     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR SA                                                                 :      74     -1 :     0.0000 : N :     399     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SA                                                                 :      62     -1 :     0.0000 : N :     114     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                               :      44     -1 :     0.0000 : N :     995     -1 : BZERO C2EXC  
        SI RE SC BT BT BT BT BT BT    SA                                                                 :      42     -1 :     0.0000 : N :     240     -1 : BZERO C2EXC  
        SI SC SC BT BT BT BT BT BT    SA                                                                 :      33     -1 :     0.0000 : N :     893     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT AB                                         :      32     -1 :     0.0000 : N :     284     -1 : BZERO C2EXC  
        SI RE RE BT BT BT BT BT BT    SA                                                                 :      29     -1 :     0.0000 : N :     107     -1 : BZERO C2EXC  
        SI RE RE BT BT BT BT BT BT    SR SA                                                              :      27     -1 :     0.0000 : N :     981     -1 : BZERO C2EXC  
        SI RE SC BT BT BT BT BT BT    SR SA                                                              :      27     -1 :     0.0000 : N :     230     -1 : BZERO C2EXC  
        SI SC SC BT BT BT BT BT BT    SR SA                                                              :      26     -1 :     0.0000 : N :    1090     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                            :      26     -1 :     0.0000 : N :     169     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR SR SA                                                              :      25     -1 :     0.0000 : N :     215     -1 : BZERO C2EXC  
        SI SC BT BT BT BT BT BT    SR SR SA                                                              :      25     -1 :     0.0000 : N :     308     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT AB                                                     :      19     -1 :     0.0000 : N :     351     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT BT BT BT BT BT BT    SR    BT BT BT BT BT BT BT  :      17     -1 :     0.0000 : N :     432     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT AB                                      :      16     -1 :     0.0000 : N :     474     -1 : BZERO C2EXC  
        SI RE BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                            :      16     -1 :     0.0000 : N :    1558     -1 : BZERO C2EXC  
        SI RE RE SC BT BT BT BT BT BT    SA                                                              :      15     -1 :     0.0000 : N :     121     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT AB                                               :      14     -1 :     0.0000 : N :     297     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR    BT BT BT BT  :      14     -1 :     0.0000 : N :     553     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR    BT BT BT BT BT BT  :      13     -1 :     0.0000 : N :     476     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT BT BT       BT BT BT BT BT BT BT BT       BT BT  :      13     -1 :     0.0000 : N :     275     -1 : BZERO C2EXC  
        SI SC RE BT BT BT BT BT BT    SA                                                                 :      12     -1 :     0.0000 : N :     494     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT SC SC BT BT BT BT BT BT    SR    BT BT BT BT BT  :      12     -1 :     0.0000 : N :     238     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT SC AB                                            :      12     -1 :     0.0000 : N :     408     -1 : BZERO C2EXC  
        SI RE RE RE BT BT BT BT BT BT    SA                                                              :      11     -1 :     0.0000 : N :    2649     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR    BT BT BT BT BT BT BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT  :      11     -1 :     0.0000 : N :     165     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT SC AB                                      :      11     -1 :     0.0000 : N :    2535     -1 : BZERO C2EXC  
        SI BT BT BT BT BT BT    SR SR SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR SR    BT BT BT  :      11     -1 :     0.0000 : N :    1338     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u.size 4914 opt DEVIANT mode 5
    :r:`SI SC BT BT BT BT BT BT SA                                                                       :       4    172 :   160.3636 : Y :    1019    112 : DEVIANT  `
    :r:`SI RE BT BT BT BT BT BT SA                                                                       :       2    129 :   123.1221 : Y :    8250    195 : DEVIANT  `
    :r:`SI SC SC BT BT BT BT BT BT SD                                                                    :       4     90 :    78.6809 : Y :     628    322 : DEVIANT  `
    :r:`SI SC SC BT BT BT BT BT BT SA                                                                    :       4     74 :    62.8205 : Y :    2298    192 : DEVIANT  `
    :r:`SI RE RE BT BT BT BT BT BT SA                                                                    :       1     51 :    48.0769 : Y :    1244     95 : DEVIANT  `
    ]sseq_index_ab::desc

    f

    CMDLINE:/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-v0.4.0/bin/sseq_index_test.py
    f.base:/data1/blyth/tmp/sseq_index_test

      : f.sseq_index_ab_chi2                               :                 (4,) : 0:00:03.777024 

     min_stamp : 2025-04-27 13:50:54.496542 
     max_stamp : 2025-04-27 13:50:54.496542 
     dif_stamp : 0:00:00 
     age_stamp : 0:00:03.777024 
    [487.981  29.     40.      0.   ]
    c2sum/c2n:c2per(C2CUT)  487.98/29:16.827 (40) pv[1.000,> 0.05 : null-hyp ] 
    c2sum :   487.9809 c2n :    29.0000 c2per:    16.8269  C2CUT:   40 
    A[blyth@localhost ~]$ 




Simplify by switching to input photons
----------------------------------------

::

    (gdb) f 5
    #5  0x00007fffbe927cb3 in SEventConfig::Initialize_EventName () at /home/blyth/opticks/sysrap/SEventConfig.cc:1000
    1000	    assert(build_matches_EventName);
    (gdb) p kEventName
    $1 = 0x7fffbea732fb "OPTICKS_EVENT_NAME"
    (gdb) p SEventConfig::EventName()
    $2 = 0x7fffffff17b6 "shakedownIPH"
    (gdb) p sbuild::Matches("DebugPhiloxShakedownIPH")
    $3 = true
    (gdb) p sbuild::Matches("DebugPhiloyShakedownIPH")
    $4 = false
    (gdb) 


::


    A[blyth@localhost ~]$ oj3dbg
    ...
    SLOG::EnvLevel adjusting loglevel by envvar   key SEvt level INFO fallback DEBUG upper_level INFO
    a_path $AFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_DebugPhiloxShakedownIPH/A000/seq.npy a_seq (10000, 2, 2, )
    b_path $BFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_DebugPhiloxShakedownIPH/B000/seq.npy b_seq (10000, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u.size 3170 opt BRIEF mode 6sseq_index_ab_chi2::desc sum     1.7097 ndf  2.0000 sum/ndf     0.8548 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SD                                                                                :      -1   3539 :     0.0000 : N :      -1      5 : AZERO C2EXC  
        TO BT BT BT BT SA                                                                                :      -1   2566 :     0.0000 : N :      -1      1 : AZERO C2EXC  
        TO BT BT BT BT    SA                                                                             :    1876     -1 :     0.0000 : N :       2     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR SA                                                                          :     790     -1 :     0.0000 : N :      11     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SA                                                                          :      -1    629 :     0.0000 : N :      -1   1038 : AZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT BT AB                                                     :     573     -1 :     0.0000 : N :    1479     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SA                                                                             :      -1    477 :     0.0000 : N :      -1    880 : AZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT AB                                                           :     198     -1 :     0.0000 : N :    1586     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT BT SC AB                                                  :     184     -1 :     0.0000 : N :    1661     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR SR SA                                                                       :     163     -1 :     0.0000 : N :       1     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT BT BT BT BT BT BT BT    SR SA                             :     110     -1 :     0.0000 : N :    1712     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR SR SR    BT BT BT BT BT BT AB                                               :     109     -1 :     0.0000 : N :     253     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :      -1    103 :     0.0000 : N :      -1   1755 : AZERO C2EXC  
        TO BT BT AB                                                                                      :     101     85 :     1.3763 : Y :      47    127 :   
        TO BT BT BT BT    SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SA                             :     100     -1 :     0.0000 : N :    1716     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR BR SA                                                                       :      -1     99 :     0.0000 : N :      -1   2120 : AZERO C2EXC  
        TO BT BT BT BT BT SR BR SR SA                                                                    :      -1     96 :     0.0000 : N :      -1   2101 : AZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT BT BT BT BT BT BT BT    SA                                :      95     -1 :     0.0000 : N :    1659     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT SA                                                        :      93     -1 :     0.0000 : N :    8682     -1 : BZERO C2EXC  
        TO BT BT BT BT    SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SR    BT BT BT BT BT BT BT BT  :      82     -1 :     0.0000 : N :    1747     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SA                                                                       :      -1     81 :     0.0000 : N :      -1   1063 : AZERO C2EXC  





pdb : Newer python more fussy on right_shift types
-----------------------------------------------------

::

    TypeError: ufunc 'right_shift' not supported for the input types, and the inputs could not be safely coerced to any supported types according to the casting rule ''safe''
    > /home/blyth/opticks/ana/histype.py(105)Convert()
        103         """
        104         qq = np.zeros( (len(q), 32), dtype=np.int8 )  # 32 bytes for each item, ie 64 nibbles
    --> 105         for i in np.arange(16): qq[:,i]    = ( q[:,0] >> (4*i) ) & 0xf
        106         for i in np.arange(16): qq[:,16+i] = ( q[:,1] >> (4*i) ) & 0xf
        107         return qq



pdb : A side history dropouts
------------------------------


::

    (ok) A[blyth@localhost oj]$ source oj3.sh  info_pdb

    ...

    ab.qcf[:40]
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum : 13741.7686 c2n :    60.0000 c2per:   229.0295  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  13741.77/60:229.029 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '     0   3539' '3539.0000' '    -1      5']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '     0   2566' '2566.0000' '    -1      1']
     [' 2' 'TO BT BT BT BT    SA                                                                           ' ' 2' '  1876      0' '1876.0000' '     2     -1']
     [' 3' 'TO BT BT BT BT    SR SA                                                                        ' ' 3' '   790      0' '790.0000' '    11     -1']
     [' 4' 'TO BT BT BT BT BT SR SA                                                                        ' ' 4' '     0    629' '629.0000' '    -1   1038']
     [' 5' 'TO BT BT BT BT    SR    BT BT BT BT BT BT AB                                                   ' ' 5' '   573      0' '573.0000' '  1479     -1']
     [' 6' 'TO BT BT BT BT BT SA                                                                           ' ' 6' '     0    477' '477.0000' '    -1    880']
     [' 7' 'TO BT BT BT BT    SR    BT BT BT BT AB                                                         ' ' 7' '   198      0' '198.0000' '  1586     -1']
     [' 8' 'TO BT BT BT BT    SR    BT BT BT BT BT BT SC AB                                                ' ' 8' '   184      0' '184.0000' '  1661     -1']
     [' 9' 'TO BT BT BT BT    SR SR SA                                                                     ' ' 9' '   163      0' '163.0000' '     1     -1']
     ['10' 'TO BT BT BT BT    SR    BT BT BT BT BT BT BT BT BT BT BT BT    SR SA                           ' '10' '   110      0' '110.0000' '  1712     -1']
     ['11' 'TO BT BT BT BT    SR SR SR    BT BT BT BT BT BT AB                                             ' '11' '   109      0' '109.0000' '   253     -1']
     ['12' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' '12' '     0    103' '103.0000' '    -1   1755']
     ['13' 'TO BT BT AB                                                                                    ' '13' '   101     85' ' 1.3763' '    47    127']
     ['14' 'TO BT BT BT BT    SR    BT BT BT BT BT BT SC BT BT BT BT BT BT    SA                           ' '14' '   100      0' '100.0000' '  1716     -1']


::

    (ok) A[blyth@localhost oj]$ source oj3.sh  info_pdb
    ...

    In [2]: a
    Out[2]: SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_DebugPhiloxShakedownIPH/A000 

    In [3]: b
    Out[3]: SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_4_0/oj3_sh/ALL0_DebugPhiloxShakedownIPH/B000 

    In [4]: a.q
    Out[4]: 
    array([[b'TO BT BT BT BT    SR SR SR SR SR    BT BT BT BT BT BT BT BT BT BT BT BT    SA                   '],
           [b'TO BT BT BT BT    SR SR SA                                                                      '],
           [b'TO BT BT BT BT    SA                                                                            '],
           [b'TO BT BT BT BT    SR SR SA                                                                      '],
           [b'TO BT BT BT BR BT BT BT BT SA                                                                   '],
           ...,
           [b'TO BT BT BT BT    SR SR SR SR SR    BT BT BR BT BR BT BT BT BT BT SC BT BT BT BT BT BT    SR SR '],
           [b'TO BT BT BT BT    SR SR SR SA                                                                   '],
           [b'TO BT BT BT BT    SA                                                                            '],
           [b'TO BT BT BT BT    SR SR SA                                                                      '],
           [b'TO BT BT BT BT    SR SA                                                                         ']], shape=(10000, 1), dtype='|S96')

    In [5]: b.q
    Out[5]: 
    array([[b'TO BT BT BT BT BR BT BT BT BT SA                                                                '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT BR BT BT BT BT DR BT SA                                                          '],
           [b'TO BT BT BT BT BR BT BT BT BT DR BT SA                                                          '],
           [b'TO BT BT BT BT SA                                                                               '],
           ...,
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BR BT BT BT BT BT BT SR BT DR BT SR BT DR BT SR BT DR BT SR BT SA                      ']], shape=(10000, 1), dtype='|S96')



    In [6]: a.q_startswith("TO BT BT BT BT    SA")
    Out[6]: array([   2,    5,   20,   60,   62, ..., 9945, 9953, 9962, 9994, 9997], shape=(1876,))

    In


The next thing to do is PIDX dumping to understand the cause of dropouts,
but need frequent rebuilding for that to be useful. Back to source tree.
My guess is that changes in PMT identifiers have not been accounted for
in serialization of PMT info which is messing up the in GPU PMT Optical Model.


OJ cycle time far too long for debugging : need to get OK G4CXTest.sh 
going for doing this debug

HMM : the issue is likely with the serialization of PMT info
will that cause a problem for G4CXTest.sh


Updated from SOpticksResource to spath
-----------------------------------------


::

    163 G4VPhysicalVolume* G4CXApp::Construct()
    164 {
    165     LOG(info) << "[" ;
    166     const G4VPhysicalVolume* pv_ = U4VolumeMaker::PV() ;
    167     LOG_IF(fatal, pv_ == nullptr)
    168         << " FAILED TO CREATE PV : CHECK GEOM envvar "
    169         << std::endl
    170         << U4VolumeMaker::Desc()
    171         ;
    172 
    173     if(pv_ == nullptr) std::raise(SIGINT) ;
    174 
    175     G4VPhysicalVolume* pv = const_cast<G4VPhysicalVolume*>(pv_);


    0136 const G4VPhysicalVolume* U4VolumeMaker::PVG_(const char* name)
     137 {
     138     METH = "PVG_" ;
     139     const char* gdmlpath = SOpticksResource::GDMLPathFromGEOM(name) ;
     140     const char* sub = SOpticksResource::GEOMSub(name);
     141     bool exists = gdmlpath && spath::Exists(gdmlpath) ;
     142 
     143     std::cerr
     144         << "U4VolumeMaker::PVG_"
     145         << " name " << name
     146         << " gdmlpath " << ( gdmlpath ? gdmlpath : "-" )




G4CXTest_GEOM.sh
------------------


FIXED SEGV from non-standard geometry access::

    Local_DsG4Scintillation::Local_DsG4Scintillation level 0 verboseLevel 0
    2025-04-27 17:04:27.253 FATAL [393818] [U4Physics::CreateBoundaryProcess@412]  FAILED TO SPMTAccessor::Load from [$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/extra/jpmt] GEOM J25_3_0_Opticks_v0_3_5
    2025-04-27 17:04:27.253 INFO  [393818] [U4Physics::ConstructOp@310]  fBoundary 0x12a9e830
    2025-04-27 17:04:27.256 INFO  [393818] [G4CXApp::G4CXApp@160] 
    ...
    2025-04-27 17:05:07.795 INFO  [393818] [U4Recorder::BeginOfEventAction_@333]  eventID 0

    Thread 1 "G4CXTest" received signal SIGSEGV, Segmentation fault.
    (gdb) bt
    #0  0x00007ffff4f23e7a in C4CustomART::doIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #1  0x00007ffff4f1d76a in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #2  0x00007ffff7031519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007ffff703191b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007ffff702f154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007ffff703a70f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007ffff771e565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #7  0x00007ffff77be93f in G4RunManager::DoEventLoop(int, char const*, int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007ffff77bc37e in G4RunManager::BeamOn(int, char const*, int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x000000000040aa15 in G4CXApp::BeamOn (this=0x6cd200) at /home/blyth/opticks/g4cx/tests/G4CXApp.h:348
    #10 0x000000000040ab21 in G4CXApp::Main () at /home/blyth/opticks/g4cx/tests/G4CXApp.h:355
    #11 0x000000000040acaf in main (argc=1, argv=0x7fffffffb668) at /home/blyth/opticks/g4cx/tests/G4CXTest.cc:13
    (gdb) 


No debug symbols, probably null accessor::

    338 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    339 {
    340     G4double zero = 0. ;
    341     G4double minus_one = -1. ;
    342     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    343     G4double dot_pol_cross_mom_nrm = OldPolarization*OldMomentum.cross(theRecoveredNormal) ;
    344 
    345     G4double energy = thePhotonMomentum ;
    346     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    347     G4double energy_eV = energy/CLHEP::eV ;
    348     G4double wavelength_nm = wavelength/CLHEP::nm ;
    349 
    350     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    351     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    352 
    353     std::array<double,16> a_spec ;
    354     const double* ss = a_spec.data() ;
    355 
    356     Stack<double,4> stack ;
    357     theEfficiency = zero ;
    358     double _qe = zero ;
    359 
    360     if(implementation_version == ORIGINAL)
    361     {
    362         accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    363 
    364         _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;
    365         // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    366         if( minus_cos_theta < zero )
    367         {
    368             // normal incidence calc only needed for ingoing photons as _qe is fixed to zero for outgoing  
    369             stack.calc( wavelength_nm, minus_one, zero, ss, 16u );  // normal incidence calc 
    370             theEfficiency = _qe/stack.art.A ;                       // aka escape_fac
    371         }
    372     }
    373     else if( implementation_version == TRANSIENT )
    374     {
    375         _qe = accessor->get_pmtid_qe_angular( pmtid, energy, lposcost, minus_cos_theta ) ;
    376         // allowing non-zero "backwards" _qe means must do norml incidence calc every time as need theEfficiency
    377         stack.calc( wavelength_nm, minus_one, zero, ss, 16u );  // normal incidence calc 
    378         theEfficiency = _qe/stack.art.A ;                       // aka escape_fac
    379     }
    380     else if( implementation_version == YUHAN )
    381     {
    382         double theta_deg = localPoint.theta()*360./CLHEP::twopi;
    383         accessor->get_stackspec_pmtid_theta_deg(a_spec, pmtcat, pmtid, energy_eV, theta_deg );
    384         theEfficiency = 1. ;
    385     }


::

    113 
    114     C4CustomART(
    115         const C4IPMTAccessor* accessor,
    116         G4double& theAbsorption,
    117         G4double& theReflectivity,
    118         G4double& theTransmittance,
    119         G4double& theEfficiency,
    120         const G4ThreeVector& theGlobalPoint,
    121         const G4ThreeVector& OldMomentum,
    122         const G4ThreeVector& OldPolarization,
    123         const G4ThreeVector& theRecoveredNormal,
    124         const G4double& thePhotonMomentum
    125     );




FIXED : Another non-standard path for jpmt
----------------------------------------------

::

    391 G4VProcess* U4Physics::CreateBoundaryProcess()  // static 
    ...
    407 #elif defined(WITH_CUSTOM4)
    408     //const U4PMTAccessor* pmt = new U4PMTAccessor ; // DUMMY PLACEHOLDER
    409     const char* jpmt = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/extra/jpmt" ;
    410     const SPMTAccessor* pmt = SPMTAccessor::Load(jpmt) ;
    411     const char* geom = ssys::getenvvar("GEOM", "no-GEOM") ;
    412     LOG_IF(fatal, pmt == nullptr )
    413          << " FAILED TO SPMTAccessor::Load from [" << jpmt << "]"
    414          << " GEOM " << ( geom ? geom : "-" )
    415          ;


DONE : Reproduced the issue with G4CXTest_GEOM.sh on A
----------------------------------------------------------


::

    A[blyth@localhost tests]$ G4CXTest_GEOM.sh chi2
    knobs is a function
    knobs () 
    { 
        type $FUNCNAME;
        local exceptionFlags;
        local debugLevel;
        local optLevel;
        exceptionFlags=NONE;
        debugLevel=NONE;
        optLevel=LEVEL_3;
        export PIP__CreatePipelineOptions_exceptionFlags=$exceptionFlags;
        export PIP__CreateModule_debugLevel=$debugLevel;
        export PIP__linkPipeline_debugLevel=$debugLevel;
        export PIP__CreateModule_optLevel=$optLevel
    }
    /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh - using externally configured GEOM J25_3_0_Opticks_v0_3_5
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              FOLD : /data1/blyth/tmp/sseq_index_test 
                              name : sseq_index_test 
                               bin : sseq_index_test 
                               DEV :  
                          bin_note : using installed binary - built by om/CMake - use DEV=1 to use dev binary 
                       BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/sseq_index_test.sh 
                              SDIR : /data1/blyth/local/opticks_Debug/bin 
                              name : sseq_index_test 
                             C2CUT : 40 
                               MSG : Using EXTERNALLY configured AFOLD BFOLD 
                             AFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_3_5/G4CXTest/ALL98_Debug_Philox_ref5/A000 
                             BFOLD : /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_3_5/G4CXTest/ALL98_Debug_Philox_ref5/B000 
    a_path $AFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_3_5/G4CXTest/ALL98_Debug_Philox_ref5/A000/seq.npy a_seq (5000000, 2, 2, )
    b_path $BFOLD/seq.npy /data1/blyth/tmp/GEOM/J25_3_0_Opticks_v0_3_5/G4CXTest/ALL98_Debug_Philox_ref5/B000/seq.npy b_seq (5000000, 2, 2, )
    sseq_index_test__DEBUG:0
    AB
    [sseq_index_ab::desc u_size 777318 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum 1729756.9363 ndf 3519.0000 sum/ndf   491.5479 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO AB                                                                                            :  636289 634102 :     3.7650 : Y :       6      9 :   
    :r:`TO BT BT BT BT BT BT SD                                                                          :       9 372151 : 372124.0009 : Y :  272811     37 : DEVIANT  `
    :r:`TO BT BT BT BT BT BT SA                                                                          :      29 260435 : 260348.0129 : Y :  269128     15 : DEVIANT  `
        TO SC AB                                                                                         :  257290 257267 :     0.0010 : Y :      28      0 :   
    :r:`TO SC BT BT BT BT BT BT SD                                                                       :    1015 190199 : 187175.5512 : Y :    1089      4 : DEVIANT  `
    :r:`TO SC BT BT BT BT BT BT SA                                                                       :    3417 136757 : 126839.1827 : Y :     142     54 : DEVIANT  `
        TO BT BT BT BT BT BT    SA                                                                       :  117248     -1 :     0.0000 : N :       1     -1 : BZERO C2EXC  
        TO SC SC AB                                                                                      :   99382  99281 :     0.0513 : Y :      89     50 :   
        TO RE AB                                                                                         :   91132  91112 :     0.0022 : Y :     269     27 :   
    :r:`TO SC SC BT BT BT BT BT BT SD                                                                    :     655  81956 : 80011.7733 : Y :   44281     30 : DEVIANT  `
        TO BT BT SA                                                                                      :   77880  78485 :     2.3408 : Y :      32    245 :   
        TO BT BT BT BT BT BT    SR SA                                                                    :   58703     -1 :     0.0000 : N :     124     -1 : BZERO C2EXC  
    :r:`TO SC SC BT BT BT BT BT BT SA                                                                    :    1749  58610 : 53565.7205 : Y :    1360     16 : DEVIANT  `
        TO SC BT BT BT BT BT BT    SA                                                                    :   56418     -1 :     0.0000 : N :      24     -1 : BZERO C2EXC  
        TO BT BT AB                                                                                      :   54130  54818 :     4.3447 : Y :     147    116 :   
    :r:`TO BT AB                                                                                         :   45553  46786 :    16.4642 : Y :      13    268 : DEVIANT  `
        TO BT BT BT SA                                                                                   :   44895  44480 :     1.9270 : Y :      10    214 :   
        TO BT BT BT BT BT BT    SR    BT BT BT BT BT BT AB                                               :   42119     -1 :     0.0000 : N :      54     -1 : BZERO C2EXC  
        TO BT BT BT BT BT BT BT SR SA                                                                    :      -1  39989 :     0.0000 : N :      -1     47 : AZERO C2EXC  
    :r:`TO BT BT BT BT BT BT BT SA                                                                       :       4  39577 : 39565.0016 : Y :  423541    19



::

    In [8]: a.q_startswith("TO BT BT BT BT BT BT    SA")
    Out[8]: array([      1,       4,      72,     112,     145, ..., 4999887, 4999893, 4999916, 4999990, 4999995], shape=(117248,))


::

    In [20]: a.f.record[1,:10,0]
    Out[20]: 
    array([[   92.847,   -36.992,    -3.336,     0.   ],
           [16433.855, -6547.5  ,  -590.443,    90.504],
           [16548.986, -6593.37 ,  -594.579,    91.15 ],
           [17921.81 , -7140.324,  -643.902,    97.932],
           [17941.281, -7148.082,  -644.602,    98.028],
           [17950.725, -7152.991,  -645.12 ,    98.083],
           [17953.576, -7154.1  ,  -645.218,    98.097],
           [17959.83 , -7157.269,  -645.549,    98.133],
           [18137.703, -7247.415,  -654.944,    98.799],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)


    In [24]: a.f.record[1,:9,1,3].view(np.uint32)   ## iindex
    Out[24]: array([    0,     0,     0, 32051, 32051, 32051, 32051, 32051, 32051], dtype=uint32)

    In [25]: a.f.record[4,:9,1,3].view(np.uint32)
    Out[25]: array([    0,     0,     0, 43029, 43029, 43029, 43029, 43029, 43029], dtype=uint32)


    +----+----------------+----------------+----------------+----------------+--------------------------+
    | q  |      x         |      y         |     z          |      w         |  notes                   |
    +====+================+================+================+================+==========================+
    |    |  pos.x         |  pos.y         |  pos.z         |  time          |                          |
    | q0 |                |                |                |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  mom.x         |  mom.y         | mom.z          |  iindex        |                          |
    | q1 |                |                |                | (unsigned)     |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    |  pol.x         |  pol.y         |  pol.z         |  wavelength    |                          |
    | q2 |                |                |                |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    | boundary_flag  |  identity      |  orient_idx    |  flagmask      |  (unsigned)              |
    | q3 | (3,0)          |                |  orient:1bit   |                |                          |
    |    |                |                |  (3,2)         |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+


    In [26]: a.f.record[1,:9,3,1].view(np.uint32)
    Out[26]: array([   0,    0,    0, 9095, 9095, 9095, 9095, 9095, 9095], dtype=uint32)



    In [32]: 0x1 << 12 # TORCH
    Out[32]: 4096

    In [33]: 0x1 << 11 # BT
    Out[33]: 2048

    In [34]: 0x1 <<  7 # SA
    Out[34]: 128


    In [37]: a.f.record[1,:9,3,0].view(np.uint32) & 0xffff
    Out[37]: array([4096, 2048, 2048, 2048, 2048, 2048, 2048,    0,  128], dtype=uint32)


Drop outs from flag zero


HMM G4CXTest not suited to OIM 1 : need to use cxs_min.sh for A side only
--------------------------------------------------------------------------

::

    PIDX=1 OPTICKS_INTEGRATION_MODE=1 source G4CXTest_GEOM.sh dbg

    A[blyth@localhost ~]$ vm
    VIP_MODE : ok_local : Sun Apr 27 07:48:24 PM CST 2025
    A[blyth@localhost ~]$ PIDX=1 OPTICKS_INTEGRATION_MODE=1 source G4CXTest_GEOM.sh dbg



    //qsim.propagate.head idx 1 : bnc 6 cosTheta -0.69404179 
    //qsim.propagate.head idx 1 : mom = np.array([0.89099997,-0.45155698,-0.04706402]) ; lmom = 0.99999982  
    //qsim.propagate.head idx 1 : pos = np.array([17953.57617,-7154.09961,-645.21826]) ; lpos = 19337.22656250 
    //qsim.propagate.head idx 1 : nrm = np.array([(-0.29206914,0.94612086,0.13982496]) ; lnrm = 1.00000000  
    //qsim.propagate_to_boundary.head idx 1 : u_absorption 0.31586072 logf(u_absorption) -1.15245378 absorption_length  1562.9586 absorption_distance 1801.237549 
    //qsim.propagate_to_boundary.head idx 1 : post = np.array([17953.57617,-7154.09961,-645.21826,  98.09746]) 
    //qsim.propagate_to_boundary.head idx 1 : distance_to_boundary     7.0188 absorption_distance  1801.2375 scattering_distance 170218520576.0000 
    //qsim.propagate_to_boundary.head idx 1 : u_scattering     0.8435 u_absorption     0.3159 
    //qsim.propagate_to_boundary.tail.SAIL idx 1 : post = np.array([17959.83008,-7157.26904,-645.54858,  98.13323]) ;  sail_time_delta =    0.03577   
    //qsim.propagate.body idx 1 bounce 6 command 3 flag 0 s.optical.x 16 s.optical.y 4 
    //qsim.propagate.body.NOT:WITH_CUSTOM4 idx 1 BOUNDARY ems 4 lposcost   0.391 
    //qsim.propagate.tail idx 1 bounce 6 command 3 flag 0 ctx.s.optical.y(ems) 4 

    //qsim.propagate.head idx 1 : bnc 7 cosTheta 0.66791463 
    //qsim.propagate.head idx 1 : mom = np.array([0.89099997,-0.45155698,-0.04706402]) ; lmom = 0.99999982  
    //qsim.propagate.head idx 1 : pos = np.array([17959.83008,-7157.26904,-645.54858]) ; lpos = 19344.21679688 
    //qsim.propagate.head idx 1 : nrm = np.array([(0.93245018,0.35247871,0.07934351]) ; lnrm = 0.99999994  
    //qsim.propagate_to_boundary.head idx 1 : u_absorption 0.95651788 logf(u_absorption) -0.04445577 absorption_length 1000000000.0000 absorption_distance 44455776.000000 
    //qsim.propagate_to_boundary.head idx 1 : post = np.array([17959.83008,-7157.26904,-645.54858,  98.13323]) 
    //qsim.propagate_to_boundary.head idx 1 : distance_to_boundary   199.6332 absorption_distance 44455776.0000 scattering_distance 1845980561408.0000 
    //qsim.propagate_to_boundary.head idx 1 : u_scattering     0.1579 u_absorption     0.9565 
    //qsim.propagate_to_boundary.tail.SAIL idx 1 : post = np.array([18137.70312,-7247.41504,-654.94415,  98.79914]) ;  sail_time_delta =    0.66591   
    //qsim.propagate.body idx 1 bounce 7 command 3 flag 0 s.optical.x 16 s.optical.y 4 
    //qsim.propagate.body.NOT:WITH_CUSTOM4 idx 1 BOUNDARY ems 4 lposcost  -0.478 
    //qsim.propagate.body (lposcost < 0.f) idx 1 bounce 7 command 3 flag 0 ems 4 

    THIS flag:0 APPEARS DUE TO NOT:WITH_CUSTOM4

    //qsim.propagate_at_surface.SA/SD.BREAK idx 1 : flag 128 
    //qsim.propagate.tail idx 1 bounce 7 command 1 flag 128 ctx.s.optical.y(ems) 4 
    2025-04-27 19:53:13.337 INFO  [461864] [QEvent::gatherPhoton@613] [ evt.num_photon 5000000 p.sstr (5000000, 4, 4, ) evt.photon 0x7ffb86000000


::

    2207     if( command == BOUNDARY )
    2208     {
    2209         const int& ems = ctx.s.optical.y ;
    2210 
    2211 #if !defined(PRODUCTION) && defined(DEBUG_PIDX) 
    2212         if( ctx.idx == base->pidx )
    2213         {
    2214 #if defined(WITH_CUSTOM4)
    2215             printf("//qsim.propagate.body.WITH_CUSTOM4 idx %d  BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost );
    2216 #else
    2217             printf("//qsim.propagate.body.NOT:WITH_CUSTOM4 idx %d BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost);
    2218 #endif
    2219         }
    2220 #endif
    2221 
    2222         if( ems == smatsur_NoSurface )
    2223         {
    2224             command = propagate_at_boundary( flag, rng, ctx ) ;
    2225         }
    2226         else if( ems == smatsur_Surface )
    2227         {
    2228             command = propagate_at_surface( flag, rng, ctx ) ;
    2229         }
    2230         else if( lposcost < 0.f )  // could combine with prior, but handy for debug to keep separate
    2231         {
    2232 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    2233             if( ctx.idx == base->pidx )
    2234             printf("//qsim.propagate.body (lposcost < 0.f) idx %d bounce %d command %d flag %d ems %d \n",
    2235                      ctx.idx, bounce, command, flag, ems  );
    2236 #endif
    2237             command = propagate_at_surface( flag, rng, ctx ) ;
    2238         }
    2239         else if( ems == smatsur_Surface_zplus_sensor_A )
    2240         {
    2241             command = propagate_at_surface_Detect( flag, rng, ctx ) ;
    2242         }
    2243         else if( ems == smatsur_Surface_zplus_sensor_CustomART )
    2244         {
    2245 #if defined(WITH_CUSTOM4)
    2246             command = propagate_at_surface_CustomART( flag, rng, ctx ) ;
    2247             //command = base->custom_lut == 0u ? propagate_at_surface_CustomART( flag, rng, ctx ) : propagate_at_surface_MultiFilm(flag, rng, ctx );
    2248 
    2249 #endif
    2250         }
    2251     }


::

     08 enum {
      9     smatsur_Material                       = 0, 
     10     smatsur_NoSurface                      = 1,
     11     smatsur_Surface                        = 2,
     12     smatsur_Surface_zplus_sensor_A         = 3,
     13     smatsur_Surface_zplus_sensor_CustomART = 4,
     14     smatsur_Surface_zminus                 = 5
     15  
     16 };


HUH: seems inconsistency of WITH_CUSTOM4 between device and host::

    2025-04-27 19:49:21.026 INFO  [461864] [G4CXApp::G4CXApp@160] 
    U4Recorder__PreUserTrackingAction_Optical_UseGivenVelocity_KLUDGE:0
    $Name: geant4-10-04-patch-02 [MT]$ (25-May-2018)U4Recorder::Switches
    WITH_CUSTOM4
    NOT:WITH_PMTSIM
    NOT:PMTSIM_STANDALONE
    NOT:PRODUCTION
    NOT:WITH_INSTRUMENTED_DEBUG



After fix that::

    //qsim.propagate_at_boundary.body idx 1 : nrm = np.array([-0.92846638,0.36991528,0.03335834]) ; lnrm = 0.99999994 
    //qsim.propagate_at_boundary.body idx 1 : n1 = 1.50430501 ; n2 = 1.35398555 ; eta = 1.11101997  
    //qsim.propagate_at_boundary.body idx 1 : c1 = 0.99999982 ; eta_c1 = 1.11101973 ; c2 = 0.99999976 ; eta_c1__c2 = 0.11101997 
    //qsim.propagate_at_boundary.tail idx 1 : reflect 0 tir 0 TransCoeff     0.9972 u_reflect     0.4273 
    //qsim.propagate_at_boundary.tail idx 1 : mom1 = np.array([0.92846626,-0.36991525,-0.03335834]) ; lmom1 = 0.99999982  
    //qsim.propagate_at_boundary.tail idx 1 : pol1 = np.array([-0.03098941,0.01234645,-0.99944335]) ; lpol1 = 0.99999988 
    //qsim.propagate.tail idx 1 bounce 1 command 2 flag 2048 ctx.s.optical.y(ems) 1 

    //qsim.propagate.head idx 1 : bnc 2 cosTheta -0.79896814 
    terminate called after throwing an instance of 'CUDA_Exception'
      what():  CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1068)


    Thread 1 "G4CXTest" received signal SIGABRT, Aborted.
    0x00007ffff168b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff168b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff163e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff1628833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff1aa1b21 in __gnu_cxx::__verbose_terminate_handler() [clone .cold] () from /lib64/libstdc++.so.6
    #4  0x00007ffff1aad52c in __cxxabiv1::__terminate(void (*)()) () from /lib64/libstdc++.so.6
    #5  0x00007ffff1aad597 in std::terminate() () from /lib64/libstdc++.so.6
    #6  0x00007ffff1aad7f9 in __cxa_throw () from /lib64/libstdc++.so.6
    #7  0x00007ffff488a3a9 in CSGOptiX::launch (this=0xa38b320) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1068
    #8  0x00007ffff488a840 in CSGOptiX::simulate_launch (this=0xa38b320) at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1128
    #9  0x00007ffff2a6da2b in QSim::simulate (this=0x12762e30, eventID=0, reset_=true) at /home/blyth/opticks/qudarap/QSim.cc:406
    #10 0x00007ffff7eeb5a6 in G4CXOpticks::simulate (this=0x7aaab0, eventID=0, reset_=true) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:450
    #11 0x000000000040a507 in G4CXApp::EndOfEventAction (this=0x6cd200, event=0x16ef96c0) at /home/blyth/opticks/g4cx/tests/G4CXApp.h:307
    #12 0x00007ffff771ea92 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #13 0x00007ffff77be93f in G4RunManager::DoEventLoop(int, char const*, int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #14 0x00007ffff77bc37e in G4RunManager::BeamOn(int, char const*, int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #15 0x000000000040aa15 in G4CXApp::BeamOn (this=0x6cd200) at /home/blyth/opticks/g4cx/tests/G4CXApp.h:348
    #16 0x000000000040ab21 in G4CXApp::Main () at /home/blyth/opticks/g4cx/tests/G4CXApp.h:355
    #17 0x000000000040acaf in main (argc=1, argv=0x7fffffffb058) at /home/blyth/opticks/g4cx/tests/G4CXTest.cc:13
    (gdb) 


cxs_min.sh : seems not to suffer from this
--------------------------------------------

::

    A[blyth@localhost CSGOptiX]$ PIDX=1 cxs_min.sh dbg




