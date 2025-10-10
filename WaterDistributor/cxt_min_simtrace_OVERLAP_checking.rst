cxt_min_simtrace_OVERLAP_checking
====================================


Overview
----------

* simtrace CPU overlap checking operational (but takes about 15s for nearest neighbor between pairs of point clouds)

  * impl is adhoc and tightly coupled to cxt_min.py

* explored using rapidsai/cuml to do point cloud penetration testing

  * with test geometries (spheres) it works, see ~/env/tools/cuml_check/cuml_check.sh
  
  * BUT, found getting a working conda environment is rather hit and miss, 
    presumably due to too many packages/dependencies
    



Commandlines for CPU overlap checking
--------------------------------------


running simtrace with ELV dynamic geometry
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    USE_ELV=1 cxt_min.sh run
 

    2025-10-10 21:16:47.061 INFO  [1022498] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv YES extra.size 43 tree_digest f94d93c709d76d3f6c8cc0ad6c25e61a dynamic b2df1b57775dc026996ecf05df4e6dd0
    //CSGOptiX7.cu : simtrace idx 0 photon_idx 0  genstep_idx 0 evt->num_simtrace 5956500 
    //CSGOptiX7.cu : simtrace idx 0 pos.xyz -2296.000,-1291.500,17643.500 mom.xyz  -0.523,  0.384,  0.761  
    (ok) A[blyth@localhost sysrap]$ 
    (ok) A[blyth@localhost sysrap]$ 




analysis of simtrace with ELV dynamic geometry
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    USE_ELV=1 PRIMTAB=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 cxt_min.sh pdb

    USE_ELV=1 PRIMTAB=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 OVERLAP=1 KEY=deeppink,honeydew cxt_min.sh pdb


* USE_ELV is needed to define CFBASE_ALT such that the python script cxt_min.py 
  loads the geometry that corresponds to same geometry used by the C++ executable
  that wrote the simtrace event file 

* TODO : add metadata concerning the geometry together with the simtrace event arrays
  such that can check are using the appropriate geometry. Currently there is no such
  check so using the above commandline without USE_ELV will run but the labelling
  of geometries and key selection will be wrong because the indices of volumes and
  correspondence to names with be wrong


DONE : EVT SIDE WITH DYNAMIC METADATA WITH THE SFRAME
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    In [1]: e.f.sframe_meta
    Out[1]: 
    creator:sframe::getFrameArray
    frs:Waterdistributor_2:0:-2
    tree:f94d93c709d76d3f6c8cc0ad6c25e61a
    dynamic:b2df1b57775dc026996ecf05df4e6dd0
    ek:MOI
    ev:Waterdistributor_2:0:-2
    ekvid:sframe_MOI_Waterdistributor_2_0_-2


TODO : GEOM SIDE NEEDS THE DYNAMIC METADATA TOO
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





where is the nexus between event and geometry where the geometry digest should be passed to the event ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    stree_load_test::make_tree_digest
     tree_digest f94d93c709d76d3f6c8cc0ad6c25e61a
     dynamic_0   f94d93c709d76d3f6c8cc0ad6c25e61a
     dynamic_1   f3fa6611ab61f44e6d0ceb093dac5992
    (ok) A[blyth@localhost sysrap]$ 




* need place that works for running from persisted geometry and live translated geometry

::

     787 void SEvt::setFrame(const sframe& fr )
     788 {
     789     const char* name = fr.get_name() ;
     790     LOG_IF(info, FRAME)
     791         << " [" << SEvt__FRAME << "]"
     792         << " fr.get_name " << ( name ? name : "-" ) << "\n"
     793         << " fr.desc\n"
     794         << fr.desc()
     795         ;
     796     frame = fr ;
     797     transformInputPhoton();
     798 }


::

    (ok) A[blyth@localhost CSGOptiX]$ BP=SEvt::setFrame cxt_min.sh

    (gdb) bt
    #0  SEvt::setFrame (this=0x1608dd10, fr=...) at /home/blyth/opticks/sysrap/SEvt.cc:789
    #1  0x00007ffff594e7a2 in SEvt::SetFrame (fr=...) at /home/blyth/opticks/sysrap/SEvt.cc:1396
    #2  0x00007ffff7652787 in CSGFoundry::AfterLoadOrCreate () at /home/blyth/opticks/CSG/CSGFoundry.cc:3717
    #3  0x00007ffff764fb1a in CSGFoundry::Load () at /home/blyth/opticks/CSG/CSGFoundry.cc:3072
    #4  0x00007ffff7e324a8 in CSGOptiX::SimtraceMain () at /home/blyth/opticks/CSGOptiX/CSGOptiX.cc:155
    #5  0x0000000000404a95 in main (argc=1, argv=0x7fffffffb2d8) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXTMTest.cc:13
    (gdb) 



::

    3694 /**
    3695 CSGFoundry::AfterLoadOrCreate
    3696 -------------------------------
    3697 
    3698 Called from some high level methods eg: CSGFoundry::Load
    3699 
    3700 The idea behind this is to auto connect SEvt with the frame
    3701 from the geometry.
    3702 
    3703 HMM: not called after Create, see CSGOptiX::initFrame
    3704 
    3705 **/
    3706 
    3707 void CSGFoundry::AfterLoadOrCreate() // static
    3708 {
    3709     CSGFoundry* fd = CSGFoundry::Get();
    3710 
    3711     SEvt::CreateOrReuse() ;   // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE
    3712 
    3713     if(!fd) return ;
    3714 
    3715     sframe fr = fd->getFrameE() ;
    3716     LOG(LEVEL) << fr ;
    3717     SEvt::SetFrame(fr); // now only needs to be done once to transform input photons
    3718 
    3719 }



    0604 /**
     605 CSGOptiX::initFrame (formerly G4CXOpticks::setupFrame)
     606 ---------------------------------------------------------
     607 
     608 The frame used depends on envvars INST, MOI, OPTICKS_INPUT_PHOTON_FRAME
     609 it comprises : fr.ce fr.m2w fr.w2m set by CSGTarget::getFrame
     610 
     611 Q: why is the frame needed ?
     612 A: cx rendering viewpoint, input photon frame and the simtrace genstep grid
     613    are all based on the frame center, extent and transforms
     614 
     615 Q: Given the sframe and SEvt are from sysrap it feels too high level to do this here,
     616    should be at CSG or sysrap level perhaps ?
     617    And then CSGOptix could grab the SEvt frame at its initialization.
     618 
     619 TODO: see CSGFoundry::AfterLoadOrCreate for maybe auto frame hookup
     620 
     621 **/
     622 
     623 void CSGOptiX::initFrame()
     624 {
     625     sframe _fr = foundry->getFrameE() ;   // TODO: migrate to lighweight sfr from stree level
     626     LOG(LEVEL) << _fr ;
     627     SEvt::SetFrame(_fr) ;
     628 
     629     sfr _lfr = _fr.spawn_lite();
     630     setFrame(_lfr);
     631 }
     632 
     633 





WIP : geometry digest ?
~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    2025-10-10 17:04:49.234 INFO  [966560] [SSim::annotate_frame@177]  tree YES tree_digest f94d93c709d76d3f6c8cc0ad6c25e61a


HMM the digest needs to feel ELV ... seems how doing it currently does not::

    f94d93c709d76d3f6c8cc0ad6c25e61a


::

    In [3]: e.f.sframe_meta
    Out[3]: 
    creator:sframe::getFrameArray
    frs:Waterdistributor_2:0:-2
    tree:f94d93c709d76d3f6c8cc0ad6c25e61a
    ek:MOI
    ev:Waterdistributor_2:0:-2
    ekvid:sframe_MOI_Waterdistributor_2_0_-2




::

    3332 /**
    3333 stree::get_tree_digest
    3334 ------------------------
    3335 
    3336 Returns subtree digest of *nidx* zero, the root node. 
    3337 The string returned can be accessed at bash level from a
    3338 persisted geometry with eg::
    3339 
    3340     (ok) A[blyth@localhost InstallArea]$ head -1 .opticks/GEOM/$GEOM/CSGFoundry/SSim/stree/subs_names.txt
    3341     f94d93c709d76d3f6c8cc0ad6c25e61a
    3342 
    3343 **/
    3344 
    3345 inline const char* stree::get_tree_digest() const
    3346 {
    3347     int num_sub = subs.size() ;
    3348     return num_sub > 0 ? subs[0].c_str() : nullptr ;
    3349 }








Maybe because ELV acts at CSGFoundry level, not stree::get_tree_digest level ?

* could kludge it by forming dynamic digest that includes ELV




::

    (ok) A[blyth@localhost stree]$ wc -l *.txt
      384627 digs_names.txt
         110 implicit_names.txt
          23 mtname_names.txt
          13 mtname_no_rindex_names.txt
          35 NPFold_index.txt
           2 NPFold_meta.txt
           0 NPFold_names.txt
        3064 prname_names.txt
           5 sensor_name_names.txt
         340 soname_names.txt
      384627 subs_names.txt
         234 suname_names.txt
      773080 total
    (ok) A[blyth@localhost stree]$ 


    (ok) A[blyth@localhost stree]$ head -5 digs_names.txt
    58f66b49ee9654a16fa958556f872f8b
    85c731694f398bb1b3da6894bcf98ead
    d6f4ce66cff77d7d287ad5674ee06f0c
    d051b337905df60e81f8dabfc2f71bdd
    dcee34e236ba05f2bd53f7ac6683955e

    (ok) A[blyth@localhost stree]$ head -5 subs_names.txt 
    f94d93c709d76d3f6c8cc0ad6c25e61a
    a5eb593f652cf1770d76dc28fab5b2cf
    d62852063838cd57e3ff3b319213f769
    17b94274d71d339e3600d1309c7dd930
    f1d3ff8443297732862df21dc4e57262
    (ok) A[blyth@localhost stree]$ 

::

     367     std::vector<std::string> digs ;        // per-node digest for all nodes
     368     std::vector<std::string> subs ;        // subtree digest for all nodes



  
TODO : geometry metadata with SEvt event arrays (folder level makes sense)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    In [1]: os.environ["MFOLD"]
    Out[1]: '/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXTMTest/ALL0_no_opticks_event_name/A000'

    In [7]: e.f.base
    Out[7]: '/data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXTMTest/ALL0_no_opticks_event_name/A000'

    In [8]: e.f.NPFold_meta
    Out[8]: 
    NumPhotonCollected:6575600
    NumGenstepCollected:18104
    MaxBounce:31
    site:SEvt::endMeta
    hitmask:64
    index:0
    instance:0
    SEvt__beginOfEvent_0:1759992544016291,7707624,1382752
    SEvt__beginOfEvent_1:1759992544053916,7720944,1395296
    SEvt__endOfEvent_0:1759992544512594,26516708,1813396
    t_BeginOfEvent:1759992544016299
    t_setGenstep_0:0
    t_setGenstep_1:0
    t_setGenstep_2:0
    t_setGenstep_3:1759992544056037
    t_setGenstep_4:1759992544056244
    t_setGenstep_5:1759992544056367
    t_setGenstep_6:1759992544056384
    t_setGenstep_7:1759992544058780
    t_setGenstep_8:1759992544059150
    t_PreLaunch:1759992544059151
    t_PostLaunch:1759992544109354
    t_EndOfEvent:1759992544512637
    t_Event:496338
    t_Launch:0.0501851



sframe is natural connection between geometry and event that is already persisted with SEvt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* need geometry digest and directory to be stored together : but do not 

::


    In [10]: e.f.sframe
    Out[10]: 
    sframe       : 
    path         : /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXTMTest/ALL0_no_opticks_event_name/A000/sframe.npy
    meta         : creator:sframe::getFrameArray
    frs:Waterdistributor_2:0:-2
    ek:MOI
    ev:Waterdistributor_2:0:-2
    ekvid:sframe_MOI_Waterdistributor_2_0_-2
    ce           : array([    0.,     0., 18935.,  1435.], dtype=float32)
    grid         : ix0  -16 ix1   16 iy0   -9 iy1    9 iz0   -9 iz1    9 num_photon  500 gridscale     0.1000
    bbox         : array([[-2296. , -1291.5, -1291.5],
           [ 2296. ,  1291.5,  1291.5]], dtype=float32)
    target       : midx    122 mord      0 gord     -2       inst       0   
    qat4id       : ins_idx     -1 gas_idx   -1   -1 
    m2w          : 
    array([[    1.,     0.,     0.,     0.],
           [    0.,     1.,     0.,     0.],
           [    0.,     0.,     1.,     0.],
           [    0.,     0., 18935.,     1.]], dtype=float32)

    w2m          : 
    array([[     1.,      0.,      0.,      0.],
           [     0.,      1.,      0.,      0.],
           [     0.,      0.,      1.,      0.],
           [     0.,      0., -18935.,      1.]], dtype=float32)

    id           : 
    array([[1., 0., 0., 0.],
           [0., 1., 0., 0.],
           [0., 0., 1., 0.],
           [0., 0., 0., 1.]], dtype=float32)
    ins_gas_ias  :  ins      0 gas    0 ias    0 

    In [11]: e.f.sframe_meta
    Out[11]: 
    creator:sframe::getFrameArray
    frs:Waterdistributor_2:0:-2
    ek:MOI
    ev:Waterdistributor_2:0:-2
    ekvid:sframe_MOI_Waterdistributor_2_0_-2






Old exploration
-------------------


::

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew cxt_min.sh pdb


Adhoc python level offset (shifting the point cloud) is not the same a real offset in the geometry,
but it should give the ballpark of how much offset is needed to avoid overlap::

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-10 cxt_min.sh pdb      ## overlap_pt 187
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-20 cxt_min.sh pdb      ## overlap_pt 61
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-25 cxt_min.sh pdb      ## overlap_pt 5

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-27 cxt_min.sh pdb      ##  overlap_pt 1
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-28 cxt_min.sh pdb      ## NO OVERLAP

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-30 cxt_min.sh pdb      ## NO OVERLAP
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-1000 cxt_min.sh pdb    ## NO OVERLAP
    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew KEYOFF=honeydew:0,0,-1000 cxt_min.sh pdb    ## NO OVERLAP

With a few mm safety margin, would suggest z-shift downwards of 30mm is needed to avoid overlap between Waterdistributor and the
virtual wrapper of Hama PMTs.


To check without the virtual wrappers : had to save the dynamic geometry and load that into ipython
-------------------------------------------------------------------------------------------------------

::

     USE_ELV=1 cxt_min.sh run


    USE_ELV=1 PRIMTAB=1 OVERLAP=1 KEY=honeydew,deeppink cxt_min.sh pdb

    USE_ELV=1 PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew  KEYOFF=honeydew:0,0,-1000 cxt_min.sh pdb
    USE_ELV=1 PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew  KEYOFF=honeydew:0,0,-25 cxt_min.sh pdb     ## overlap_pt 1





ELV::

    106 elif [ "$GEOM" == "J25_4_0_opticks_Debug" -a "$elv_name" == "all" ]; then
    107 
    108     elv="t:sWorld"
    109     elv="$elv,HamamatsuR12860sMask_virtual"
    110     elv="$elv,NNVTMCPPMTsMask_virtual"
    111     elv="$elv,mask_PMT_20inch_vetosMask_virtual"
    112 
    113    elv_branch=4



HMM using ELV is problematic because it means are using a dynamic geometry
that makes the naming all wrong... the GEOM folder is effectively using
a different geometry


::

    USE_ELV=1 cxt_min.sh run

    PRIMTAB=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 cxt_min.sh pdb

    PRIMTAB=1 OVERLAP=1 BOXSEL=-2000,2000,-2000,2000,-1000,1000 KEY=deeppink,honeydew  cxt_min.sh pdb





::

    3031 CSGFoundry* CSGFoundry::Load() // static
    3032 {
    3033     SProf::Add("CSGFoundry__Load_HEAD");
    3034 
    3035 
    3036 
    3037     LOG(LEVEL) << "[ argumentless " ;
    3038     CSGFoundry* src = CSGFoundry::Load_() ;
    3039     if(src == nullptr) return nullptr ;
    3040 
    3041     SGeoConfig::GeometrySpecificSetup(src->id);
    3042 
    3043     const SBitSet* elv = SGeoConfig::ELV(src->id);
    3044     CSGFoundry* dst = elv ? CSGFoundry::CopySelect(src, elv) : src  ;
    3045 
    3046 
    3047     if(elv)
    3048     {
    3049         LOG(LEVEL) << " apply ELV selection to triangulated SScene " ;
    3050         SScene* src_sc = dst->sim->scene ;
    3051         SScene* dst_sc = src_sc->copy(elv);
    3052         const_cast<SSim*>(dst->sim)->set_override_scene(dst_sc);
    3053     }
    3054 
    3055 
    3056     if( elv != nullptr && Load_saveAlt)
    3057     {
    3058         LOG(error) << " non-standard dynamic selection CSGFoundry_Load_saveAlt " ;
    3059         dst->saveAlt() ;
    3060     }
    3061 
    3062 
    3063     AfterLoadOrCreate();
    3064 
    3065     LOG(LEVEL) << "] argumentless " ;
    3066     SProf::Add("CSGFoundry__Load_TAIL");
    3067     return dst ;
    3068 }



    3029 bool CSGFoundry::Load_saveAlt = ssys::getenvbool("CSGFoundry_Load_saveAlt") ;


::

    cfbase_alt=/tmp/$USER/.opticks/ELV_Dynamic/GEOM/$GEOM
    mkdir -p $cfbase_alt
    export CFBASE_ALT=$cfbase_alt
    export CSGFoundry_Load_saveAlt=1



::

    2629 /**
    2630 CSGFoundry::saveAlt
    2631 -----------------------
    2632 
    2633 Write geometry to $CFBaseAlt/CSGFoundry currently used as workaround so
    2634 that the python view of dynamic prim selection geometry can match
    2635 the actual uploaded geometry.
    2636 
    2637 See notes/issues/primIdx-and-skips.rst
    2638 **/
    2639 
    2640 void CSGFoundry::saveAlt() const
    2641 {
    2642     const char* cfbase_alt = spath::Resolve("CFBASE_ALT");
    2643     if( cfbase && cfbase_alt && strcmp(cfbase, cfbase_alt) == 0 )
    2644     {
    2645         LOG(fatal)
    2646             << "cannot saveAlt as cfbase_alt directory matched the loaded directory "
    2647             << " cfbase " << cfbase
    2648             << " cfbase_alt " << cfbase_alt
    2649             ;
    2650     }
    2651     else
    2652     {
    2653         LOG(info) << " cfbase " << cfbase << " cfbase_alt " << cfbase_alt ;
    2654         save(cfbase_alt, RELDIR);
    2655     }
    2656 }




