geometry-render-speed-check-shakedown
=======================================



NEXT:

* quiet mode when scanning
* "nvidia-smi -l 1" monitor during scan 
* investigate the overview fails for some ELV gas_idx and not uploading 
* reldir
* do view scan 
* look at the metadata, make the scan time table 
* full ELV scans
* EMM scans





cx::

    epsilon:CSGOptiX blyth$ grep ELV *.sh 
    cxr_overview.sh:export ELV=${ELV:-$elv}
    cxr_overview.sh:export NAMEPREFIX=cxr_overview_emm_${EMM}_elv_${ELV}_moi_      # MOI gets appended by the executable
    cxr_scan.sh:        ELV=$e ./$script.sh $*
    epsilon:CSGOptiX blyth$ 


cxr_scan.sh repeatedly runs cxr_overview.sh with different ELV 

HMM: what geocache is cxr_overview.sh using ?

* cxr.sh : basis for higher level render scripts using CSGOptiXRenderTest




* all those arguments, no longer parsed ? 


::

    CAMERATYPE : 0 
    OPTICKS_GEOM : cxr_overview 
    OPTICKS_RELDIR : cam_0_tmin_0.4 
          SIZE : 1280,720,1 
     SIZESCALE : 1.5 
        CFBASE :  
    OPTICKS_OUT_FOLD : /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000 
    OPTICKS_OUT_NAME : -1 
    /data/blyth/junotop/ExternalLibs/opticks/head/lib/CSGOptiXRenderTest
    /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest
    CSGOptiXRenderTest --nameprefix "cxr_overview_emm_t0_elv_t_moi_" --cvd 1 -e "t0" --size "1280,720,1" --sizescale "1.5" --solid_label ""
    main@217:  getenv.CAM perspective
    main@218:  getenv.CAMERATYPE 0
    SOpticks::WriteOutputDirScript@138:  outdir /tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1writing sh_path CSGOptiXRenderTest_OUTPUT_DIR.sh
    sh [
    # Opticks::writeOutputDirScript 
    # 20230601_031835

    export CSGOptiXRenderTest_OUTPUT_DIR=/tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1
    ]
    CSGFoundry::ResolveCFBase@2644:  cfbase/CSGFoundy directory (null)/CSGFoundry IS NOT READABLE 
    CSGFoundry::CSGFoundry@97: must SSim::Create before CSGFoundry::CSGFoundry 
    CSGOptiXRenderTest: /data/blyth/junotop/opticks/CSG/CSGFoundry.cc:98: CSGFoundry::CSGFoundry(): Assertion `sim' failed.
    ./cxr.sh: line 146: 356676 Aborted                 (core dumped) CSGOptiXRenderTest --nameprefix "cxr_overview_emm_t0_elv_t_moi_" --cvd 1 -e "t0" --size "1280,720,1" --sizescale "1.5" --solid_label ""
    === render : rc 134
    === ./cxr.sh : non-zero RC from render
    N[blyth@localhost CSGOptiX]$ 



Revert and compare logs
---------------------------


::

    N[blyth@localhost opticks]$ git log -n3
    commit 7c63ce5fd1f97817109ca5d4d41cd433716cf7c8 (HEAD -> master, origin/master, origin/HEAD)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Jun 1 14:31:46 2023 +0100

        write logs into render dir

    commit c44720f20ec94dfa26d3cb8c7b4064049d1db38a
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Jun 1 13:35:53 2023 +0100

        move some render mechanics down in SGLM::set_frame and store sframe in sglm

    commit 4b543c996e2e38e934dbd566d50042cc02839f61
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Jun 1 12:07:07 2023 +0100

        reviving CSGOptiXRenderTest to enable geometry performance scan comparisons of unnatural and natural PMT geometry
    N[blyth@localhost opticks]$ git checkout 


Capture the prior working outputs and log::

    N[blyth@localhost opticks]$ git checkout 4b543c996e2e38e934dbd566d50042cc02839f61
    Note: switching to '4b543c996e2e38e934dbd566d50042cc02839f61'.

    You are in 'detached HEAD' state. You can look around, make experimental
    changes and commit them, and you can discard any commits you make in this
    state without impacting any branches by switching back to a branch.

    If you want to create a new branch to retain commits you create, you may
    do so (now or later) by using -c with the switch command. Example:

      git switch -c <new-branch-name>

    Or undo this operation with:

      git switch -

    Turn off this advice by setting config variable advice.detachedHead to false

    HEAD is now at 4b543c996 reviving CSGOptiXRenderTest to enable geometry performance scan comparisons of unnatural and natural PMT geometry
    N[blyth@localhost opticks]$ 



    epsilon:CSGOptiXRenderTest blyth$ cp CSGOptiXRenderTest.log 4b543c996_working/
    epsilon:CSGOptiXRenderTest blyth$ cp SGLM_sWorld:0:0.json 4b543c996_working/
    epsilon:CSGOptiXRenderTest blyth$ cp SGLM_sWorld:0:0.jpg 4b543c996_working/
    epsilon:CSGOptiXRenderTest blyth$ 



Clean up the detached HEAD and return to the real HEAD::

    N[blyth@localhost CSGOptiX]$ o
    HEAD detached at 4b543c996
    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   CSGOptiX/cxr_min.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost opticks]$ git restore CSGOptiX/cxr_min.sh
    N[blyth@localhost opticks]$ o
    HEAD detached at 4b543c996
    nothing to commit, working tree clean
    N[blyth@localhost opticks]$ 

    N[blyth@localhost opticks]$ git checkout 7c63ce5fd1f97817109ca5d4d41cd433716cf7c8
    Previous HEAD position was 4b543c996 reviving CSGOptiXRenderTest to enable geometry performance scan comparisons of unnatural and natural PMT geometry
    HEAD is now at 7c63ce5fd write logs into render dir
    N[blyth@localhost opticks]$ 


    N[blyth@localhost opticks]$ git branch 
    * (HEAD detached at 7c63ce5fd)
      master
    N[blyth@localhost opticks]$ git checkout master 
    Switched to branch 'master'
    Your branch is up to date with 'origin/master'.
    N[blyth@localhost opticks]$ 
    N[blyth@localhost opticks]$ git branch 
    * master
    N[blyth@localhost opticks]$ 


Notice that need to checkout master not the hash to return to normal. 


/tmp/blyth/opticks/GEOM/V0J008/CSGOptiXRenderTest





cxr_overview.sh Getting some -ve midx 
-----------------------------------------

::

    export CSGOptiXRenderTest_OUTPUT_DIR=/tmp/blyth/opticks/CSGOptiX/CSGOptiXRenderTest/SCVD1/70000/-1
    ]
    CSGFoundry::CopySelect@2599:    -         t 148 : 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111
    CSGFoundry::descELV elv.num_bits 148 num_include 148 num_exclude 0
    INCLUDE:148

    p:  0:midx:  0:mn:sTopRock_domeAir
    p:  1:midx: -1:mn:sTopRock_dome
    p:  2:midx:  2:mn:sDomeRockBox
    p:  3:midx:  3:mn:PoolCoversub
    p:  4:midx:  4:mn:Upper_LS_tube
    p:  5:midx:  5:mn:Upper_Steel_tube
    p:  6:midx:  6:mn:Upper_Tyvek_tube
    p:  7:midx:  7:mn:Upper_Chimney
    p:  8:midx: -1:mn:sBar
    p:  9:midx: -1:mn:sBar
    p: 10:midx: 10:mn:sPanelTape
    p: 11:midx: -1:mn:sPanel
    p: 12:midx: 12:mn:sPlane
    p: 13:midx: 13:mn:sWall
    p: 14:midx: 14:mn:sAirTT
    p: 15:midx: 15:mn:sExpHall
    p: 16:midx: 16:mn:sExpRockBox
    p: 17:midx: -1:mn:sTopRock
    p: 18:midx: 18:mn:GLw1.up10_up11_FlangeI_Web_FlangeII
    p: 19:midx: 19:mn:GLw1.up09_up10_FlangeI_Web_FlangeII
    p: 20:midx: 20:mn:GLw1.up08_up09_FlangeI_Web_FlangeII



Review CSGOptiXRenderTest : where does ELV selection happen
--------------------------------------------------------------

::

    In [1]: emm = np.uint64("18446744073709551615") ; emm 
    Out[1]: 18446744073709551615

    In [2]: hex(emm)
    Out[2]: '0xffffffffffffffff'


    epsilon:opticks blyth$ opticks-f \"ELV\"  
    ./CSG/tests/CSGCopyTest.cc:    const SBitSet* elv = SBitSet::Create( src->getNumMeshName(), "ELV", "t" ); 
    ./CSG/CSGFoundry.cc:        elv = SSys::getenvvar("ELV", nullptr ); 
    epsilon:opticks blyth$ 

::

    2516 const char* CSGFoundry::ELVString(const SName* id)
    2517 {
    2518     const char* elv_selection_ = SGeoConfig::ELVSelection() ;
    2519     const char* elv = nullptr ;
    2520     if( elv_selection_ )
    2521     {
    2522         bool has_names = id->hasNames(elv_selection_);
    2523         if(has_names)
    2524         {
    2525             elv = id->getIDXListFromNames(elv_selection_, ',', "t" );
    2526         }
    2527         else
    2528         {
    2529             LOG(fatal) << "geometry does not have all the elv_selection_ names [" << elv_selection_ << "] NO SELECTION WILL BE APPLIED      " ;
    2530         }
    2531     }
    2532     else
    2533     {
    2534         elv = SSys::getenvvar("ELV", nullptr );
    2535     }
    2536 
    2537     LOG(LEVEL)
    2538         << " elv_selection_ " << elv_selection_
    2539         << " elv " << elv
    2540         ;
    2541 
    2542     return elv ;
    2543 }

    2585 CSGFoundry* CSGFoundry::Load() // static
    2586 {
    2587     LOG(LEVEL) << "[ argumentless " ;
    2588     CSGFoundry* src = CSGFoundry::Load_() ;
    2589     if(src == nullptr) return nullptr ;
    2590 
    2591     SGeoConfig::GeometrySpecificSetup(src->id);
    2592 
    2593     const SBitSet* elv = ELV(src->id);
    2594     CSGFoundry* dst = elv ? CSGFoundry::CopySelect(src, elv) : src  ;
    2595 
    2596     if( elv != nullptr && Load_saveAlt)
    2597     {
    2598         LOG(error) << " non-standard dynamic selection CSGFoundry_Load_saveAlt " ;
    2599         dst->saveAlt() ;
    2600     }
    2601 
    2602     LOG(LEVEL) << "] argumentless " ;
    2603     return dst ;
    2604 }


Trying to exclude uni1 "99" throws::

    N[blyth@localhost CSGOptiX]$ ELV=t15,16,17,94,96,97,99  ./cxr_view.sh 


    p: 97:midx: -1:mn:sStrut
    p: 99:midx: -1:mn:uni1

    SBT::getGAS@288:  no such gas_idx 9
    terminate called after throwing an instance of 'std::out_of_range'
      what():  map::at
    ./cxr.sh: line 153: 213452 Aborted                 (core dumped) CSGOptiXRenderTest
    === render : rc 134
    N[blyth@localhost CSGOptiX]$ 


EMM::

    epsilon:opticks blyth$ opticks-f \"EMM\"
    ./sysrap/tests/SBitFromStringTest.cc:    unsigned long long emm = SBit::FromEString("EMM"); 
    ./sysrap/SGeoConfig.hh:    static constexpr const char* kEMM            = "EMM" ; 
    epsilon:opticks blyth$ 


    019 unsigned long long SGeoConfig::_EMM = SBit::FromEString(kEMM, "~0");
    020 const char* SGeoConfig::_ELVSelection   = SSys::getenvvar(kELVSelection, nullptr );




