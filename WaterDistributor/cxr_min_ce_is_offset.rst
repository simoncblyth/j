cxr_min_ce_is_offset
========================


Overview
----------

Unexpected cxr_min.sh viewpoint with MOI=Waterdistributor_2:0:-2 which is at expected Z, 
but very offset in Y (~17m) and perhaps X (few-m?) too.  The CE is coming from a bbox calc
that is clearly wrong. BUT sframe seems to get it right but sfr gets it wrong ?

Waterdistributor_2 is one tree node that is a listnode of leaves that are mostly unsupported.

* HMM: how to grab the bbox from the triangles ? 


* ~/j/WaterDistributor/dbg_frame_offset.sh

::

    MOI=0.000,0.000,18935.000,1435.000 ssst.sh

    MOI=0,0,-21000,3000 cxr_min.sh
    MOI=0,0,-21000,3000 ssst.sh



Get bbox from tri ? 
----------------------

SOLID=Waterdistributor_1 ~/o/u4/tests/U4Mesh_test_py.sh::

    In [1]: f.vtx
    Out[1]: 
    array([[-1130.   ,     0.   ,   468.061],
           [-1132.385,    18.117,   469.049],
           [-1139.378,    35.   ,   471.946],
           [-1150.503,    49.497,   476.554],
           [-1165.   ,    60.622,   482.559],
           ...,
           [ -875.587,  -234.949,  -875.152],
           [ -875.177,  -234.949,  -875.562],
           [ -875.613,  -234.992,  -875.117],
           [ -875.143,  -234.992,  -875.588],
           [ -875.378,  -234.992,  -875.353]], shape=(3537, 3))

    In [2]: np.min(f.vtx)
    Out[2]: np.float64(-1270.0248600989098)

    In [3]: np.min(f.vtx,axis=0)
    Out[3]: array([-1270.025,  -272.981, -1270.018])

    In [4]: np.max(f.vtx,axis=0)
    Out[4]: array([1270.018,  272.975, 1270.014])

    In [5]: np.max(f.vtx,axis=0) - np.min(f.vtx,axis=0)
    Out[5]: array([2540.043,  545.956, 2540.032])

    In [6]: os.environ["SOLID"]
    Out[6]: 'Waterdistributor_1'


SOLID=Waterdistributor_2 ~/o/u4/tests/U4Mesh_test_py.sh::

    In [1]: np.min(f.vtx,axis=0)
    Out[1]: array([-1265.025,  -267.982, -1265.018])

    In [2]: np.max(f.vtx,axis=0)
    Out[2]: array([1265.018,  267.975, 1265.014])

    In [3]: np.max(f.vtx,axis=0) - np.min(f.vtx,axis=0)
    Out[3]: array([2530.043,  535.957, 2530.032])

    In [4]: os.environ["SOLID"]
    Out[4]: 'Waterdistributor_2'


Notice its flatter in Y dimension, and roughly the same in X and Z ???


HMM : HOW TO ACCESS THE SNODE TRANSFORM FOR LVID 124 ?
----------------------------------------------------------

::

    ok) A[blyth@localhost tests]$ TEST=desc_solid LVID=124 ~/o/sysrap/tests/stree_load_test.sh  run
    stree::desc_solid lvid 124 lvn Waterdistributor_2 root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv 124 xf Y pa Y bb Y pt N nc 11 dp  0 tg co bb.desc [-100000.000,-100000.000,-100000.000,100000.000,100000.000,100000.000]
      1 : sn::brief tc  125 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 124 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
    (ok) A[blyth@localhost tests]$ 


::

    CSG_NODE=11,
    CSG_LIST=11,
        CSG_CONTIGUOUS=11,
        CSG_DISCONTIGUOUS=12,
        CSG_OVERLAP=13,

    CSG_LEAF=101,
        CSG_SPHERE=101,
        CSG_BOX=102,
        CSG_ZSPHERE=103,
        CSG_TUBS=104,
        CSG_CYLINDER=105,
        CSG_SLAB=106,
        CSG_PLANE=107,
        CSG_CONE=108,
        CSG_EXBB=109,
        CSG_BOX3=110,
        CSG_TRAPEZOID=111,
        CSG_CONVEXPOLYHEDRON=112,
        CSG_DISC=113,
        CSG_SEGMENT=114,
        CSG_ELLIPSOID=115,
        CSG_TORUS=116,
        CSG_HYPERBOLOID=117,
        CSG_CUBIC=118,
        CSG_INFCYLINDER=119,
        CSG_OLDCYLINDER=120,
        CSG_PHICUT=121,
        CSG_THETACUT=122,
        CSG_OLDCONE=123,
        CSG_CUTCYLINDER=124,
        CSG_NOTSUPPORTED=125,
        CSG_UNDEFINED=126,








HMM: -1:-2:-3 using local CE ? 
---------------------------------

::

    229 int CSGTarget::getFrameComponents(float4& ce, int midx, int mord, int gord, qat4* m2w, qat4* w2m ) const
    230 {
    231     LOG(LEVEL) << " (midx mord gord) " << "(" << midx << " " << mord << " " << gord << ") " ;
    232     if( gord == -1 || gord == -2 || gord == -3 )
    233     {
    234         int lrc = getLocalCenterExtent(ce, midx, mord);
    235         if(lrc != 0) return 1 ;
    236 
    237         if( gord == -1 )
    238         {
    239             LOG(info) << "(gord == -1) qptr transform will not be set, typically defaulting to identity " ;
    240             assert(0) ; // WHAT IS USING -1 WITH CE SET AND IDENTITY TRANSFORMS ?  COMMONLY 0:0:-1 default MOI
    241         }
    242         else if( gord == -2 )
    243         {
    244             bool rtp_tangential = false ;
    245             bool extent_scale = false ;  // NB recent change switching off extent scaling
    246             SCenterExtentFrame<double> cef_xyzw( ce.x, ce.y, ce.z, ce.w, rtp_tangential, extent_scale );
    247             m2w->read_narrow(cef_xyzw.model2world_data);
    248             w2m->read_narrow(cef_xyzw.world2model_data);
    249         }
    250         else if( gord == -3 )
    251         {
    252             bool rtp_tangential = true ;
    253             bool extent_scale = false ;   // NB recent change witching off extent scaling
    254             SCenterExtentFrame<double> cef_rtpw( ce.x, ce.y, ce.z, ce.w, rtp_tangential, extent_scale );
    255             m2w->read_narrow(cef_rtpw.model2world_data);
    256             w2m->read_narrow(cef_rtpw.world2model_data);
    257         }
    258     }
    259     else
    260     {
    261         int grc = getGlobalCenterExtent(ce, midx, mord, gord, m2w, w2m );
    262         //  HMM: the m2w here populated is from the (midx, mord, gord) instance transform, with identity info
    263         if(grc != 0) return 2 ;
    264     }
    265     return 0 ;
    266 }






Investigations
----------------


::

    SGLFW__renderloop_tail_LEVEL=1 FULLSCREEN=0 cxr_min.sh

MOI::
 
    moi=Waterdistributor_2:0:-2   # lower of the upper pair with PMT overlap risk

VUE::

     29 vue=Y
     30 export VUE=${VUE:-$vue}
     31 
     32 if [ "$VUE" == "X" -o "$VUE" == "+X" ]; then
     33 
     34    eye=1,0,0
     35    up=0,0,1
     36 
     37 elif [ "$VUE" == "-X" ]; then
     38 
     39    eye=-1,0,0
     40    up=0,0,1
     41 
     42 elif [ "$VUE" == "Y" -o "$VUE" == "+Y" ]; then
     43 
     44    eye=0,1,0
     45    up=0,0,1



::

    SGLFW::renderloop_tail Waterdistributor_2:0:-2 sfr::desc_ce  -3883.1474 -25358.5972 18935.0000  8617.2703 sglm.e(c2w*ori) [ -3883.147 -16741.328  18935.000 ] SGLM::updateTitle
    SGLFW::renderloop_tail Waterdistributor_2:0:-2 sfr::desc_ce  -3883.1474 -25358.5972 18935.0000  8617.2703 sglm.e(c2w*ori) [ -3883.147 -16741.328  18935.000 ] SGLM::updateTitle
    SGLFW::renderloop_tail Waterdistributor_2:0:-2 sfr::desc_ce  -3883.1474 -25358.5972 18935.0000  8617.2703 sglm.e(c2w*ori) [ -3883.147 -16741.328  18935.000 ] SGLM::updateTitle


Reproduce that eye position by::

    m2w @ np.array([0,extent,0,1]) 

    In [23]: m2w @ np.array([0,8617.2703,0,1])
    Out[23]: array([ -3883.147 , -16741.3277,  18935.    ,      1.    ])


The question is why is the center offset compared to the geometry ?::

    2559 inline int stree::_get_frame_global(sfr& f, int lvid, int lvid_ordinal, int repeat_ordinal, char ridx_type ) const
    2560 {
    2561     assert( repeat_ordinal == -1 || repeat_ordinal == -2 || repeat_ordinal == -3 );
    2562     const snode* _node = pick_lvid_ordinal_node( lvid, lvid_ordinal, ridx_type );
    2563     if(_node == nullptr) return 1 ;
    2564 
    2565     const snode& node = *_node ;
    2566 
    2567     std::array<double,4> ce = {} ;
    2568     std::array<double,6> bb = {} ;
    2569     int rc = get_node_ce_bb( ce, bb, node );
    2570     f.set_ce(ce.data() );
    2571 
    2572     if( repeat_ordinal == -2 || repeat_ordinal == -3 )
    2573     {
    2574         bool rtp_tangential = repeat_ordinal == -3 ? true : false ;
    2575         bool extent_scale = false ;
    2576         SCenterExtentFrame<double> cef(ce[0], ce[1], ce[2], ce[3], rtp_tangential, extent_scale ) ;
    2577         f.m2w = cef.model2world ;
    2578         f.w2m = cef.world2model ;
    2579     }
    2580 





Dumping the transform::

    SGLFW::renderloop_tail  gm.title [Waterdistributor_2:0:-2 sfr::desc_ce  -3883.1474 -25358.5972 18935.0000  8617.2703 sglm.e(c2w*ori) [ -3883.147 -16741.328  18935.000 ] SGLM::updateTitle] SGLM::descModelMatrix
     sglm.model2world 
         1.000     0.000     0.000 -3883.147
         0.000     1.000     0.000-25358.598
         0.000     0.000     1.000 18935.000
         0.000     0.000     0.000     1.000

     sglm.world2model 
         1.000     0.000     0.000  3883.147
         0.000     1.000     0.000 25358.598
         0.000     0.000     1.000-18935.000
         0.000     0.000     0.000     1.000

     sglm.initModelMatrix_branch 1

Try to reproduce the eye position::

    In [6]: m2w = np.eye(4)

    In [7]: m2w[:,3] = (-3883.147,-25358.598,18935.000,1.000)

    In [8]: m2w
    Out[8]: 
    array([[ 1.0000000e+00,  0.0000000e+00,  0.0000000e+00, -3.8831470e+03],
           [ 0.0000000e+00,  1.0000000e+00,  0.0000000e+00, -2.5358598e+04],
           [ 0.0000000e+00,  0.0000000e+00,  1.0000000e+00,  1.8935000e+04],
           [ 0.0000000e+00,  0.0000000e+00,  0.0000000e+00,  1.0000000e+00]])

    In [9]: np.set_printoptions(edgeitems=100, suppress=True)

    In [10]: m2w
    Out[10]: 
    array([[     1.   ,      0.   ,      0.   ,  -3883.147],
           [     0.   ,      1.   ,      0.   , -25358.598],
           [     0.   ,      0.   ,      1.   ,  18935.   ],
           [     0.   ,      0.   ,      0.   ,      1.   ]])

    In [11]: 


This dont work, as it misses the extent scaling::

    In [18]: ori
    Out[18]: array([0, 1, 0, 1])

    In [15]: m2w @ ori
    Out[15]: array([ -3883.147, -25357.598,  18935.   ,      1.   ])

    In [16]: np.dot(m2w, ori)
    Out[16]: array([ -3883.147, -25357.598,  18935.   ,      1.   ])

    In [17]: m2w
    Out[17]: 
    array([[     1.   ,      0.   ,      0.   ,  -3883.147],
           [     0.   ,      1.   ,      0.   , -25358.598],
           [     0.   ,      0.   ,      1.   ,  18935.   ],
           [     0.   ,      0.   ,      0.   ,      1.   ]])


With extent scaling, reproduce the eye position::

    In [23]: m2w @ np.array([0,8617.2703,0,1])
    Out[23]: array([ -3883.147 , -16741.3277,  18935.    ,      1.    ])





stree::get_node_bb whats special with WaterDistributor bbox ?
----------------------------------------------------------------


BP=stree::get_node_bb FULLSCREEN=0 cxr_min.sh::

    (gdb) bt
    #0  stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2595
    #1  0x000000000047c86a in stree::get_node_ce_bb (this=0x53d5b0, ce=..., bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2588
    #2  0x000000000047c36a in stree::_get_frame_global (this=0x53d5b0, f=..., lvid=124, lvid_ordinal=0, repeat_ordinal=-2, ridx_type=63 '?') at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2554
    #3  0x000000000047c234 in stree::get_frame_global (this=0x53d5b0, f=..., lvid=124, lvid_ordinal=0, repeat_ordinal=-2) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2498
    #4  0x000000000047b558 in stree::get_frame_from_triplet (this=0x53d5b0, f=..., q_spec=0x7fffffffbcde "Waterdistributor_2:0:-2") at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2247
    #5  0x000000000047b374 in stree::get_frame (this=0x53d5b0, q_spec=0x7fffffffbcde "Waterdistributor_2:0:-2") at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2210
    #6  0x000000000047b29b in stree::get_frame_moi (this=0x53d5b0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2178
    #7  0x0000000000488372 in SGLM::setTreeScene (this=0x1d08f6f0, _tree=0x53d5b0, _scene=0x28dec80) at /data1/blyth/local/opticks_Debug/include/SysRap/SGLM.h:846
    #8  0x00000000004931d5 in CSGOptiXRenderInteractiveTest::init (this=0x7fffffffb080) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:124
    #9  0x00000000004930c4 in CSGOptiXRenderInteractiveTest::CSGOptiXRenderInteractiveTest (this=0x7fffffffb080) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:113
    #10 0x0000000000445eb2 in main (argc=1, argv=0x7fffffffb228) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:206
    (gdb) 



Debug the calc of bbox for LVID 124
-------------------------------------

::

    (gdb) list
    2646	    for(int i=0 ; i < bn ; i++)
    2647	    {
    2648	        const sn* n = bds[i];
    2649	        int  typecode = n ? n->typecode : CSG_ZERO ;
    2650	
    2651	        if(n && n->is_listnode())
    2652	        {
    2653	            // hmm subtracted holes will not contribute to bbox
    2654	            int num_sub = n->child.size() ;
    2655	            for(int j=0 ; j < num_sub ; j++)
    (gdb) list
    2656	            {
    2657	                const sn* c = n->child[j];
    2658	                subs.push_back(c);
    2659	            }
    2660	        }
    2661	        else
    2662	        {
    2663	            bool leaf = CSG::IsLeaf(typecode) ;
    2664	
    2665	            if(0) std::cout
    (gdb) b 2655
    Breakpoint 3 at 0x47c9ec: file /data1/blyth/local/opticks_Debug/include/SysRap/stree.h, line 2655.
    (gdb) c
    Continuing.

    Breakpoint 3, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2655
    2655	            for(int j=0 ; j < num_sub ; j++)
    (gdb) p num_sub
    $6 = 11
    (gdb) b 2684
    Breakpoint 4 at 0x47cb21: file /data1/blyth/local/opticks_Debug/include/SysRap/stree.h, line 2684.
    (gdb) c
    Continuing.

    Breakpoint 4, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2684
    2684	    for( int i=0 ; i < num_sub_total ; i++ )
    (gdb) p num_sub_total
    $7 = 11
    (gdb) b 2694
    Breakpoint 5 at 0x47cbd0: file /data1/blyth/local/opticks_Debug/include/SysRap/stree.h, line 2694.
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p n
    $8 = (const sn *) 0x112bfdf0
    (gdb) p n->typecode
    $9 = 125
    (gdb) p leaf
    $10 = true
    (gdb) p tv
    $11 = (const Tran<double> *) 0x1d090050
    (gdb) p n_bb
    $12 = {_M_elems = {-5990.8621295090961, -33975.86747892118, 18935.000000000004, -5990.8621295090961, -33975.86747892118, 18935.000000000004}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p n_bb
    $13 = {_M_elems = {-5990.8621295090961, -33975.86747892118, 18935.000000000004, -5990.8621295090961, -33975.86747892118, 18935.000000000004}}

    UNSUPPORTED TYPECODE 125 GIVES ZERO EXTENT BB ? 


    (gdb) p i
    $14 = 1
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p n_bb
    $15 = {_M_elems = {-5990.8621295090961, -33975.86747892118, 18935.000000000004, -5990.8621295090961, -33975.86747892118, 18935.000000000004}}
    (gdb) p n->typecode()
    'at 0x0x7d' has unknown return type; cast the call to its declared return type
    (gdb) p n->typecode
    $16 = 125
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p n->typecode
    $17 = 105
    (gdb) p n_bb
    $18 = {_M_elems = {-4215.4294140816091, -16817.784971972684, 18700, -4138.9713226567856, -16741.326880547862, 19170}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $19 = 4
    (gdb) p n->typecode
    $20 = 105
    (gdb) p n_bb
    $21 = {_M_elems = {-3869.2971988509826, -16878.817420410232, 17851.471862576145, -3792.839107426159, -16802.359328985411, 18321.471862576145}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $22 = 5
    (gdb) o n->typecode
    Ambiguous command "o n->typecode": obscure, output, ov, overlay, ovly.
    (gdb) p n->typecode
    $23 = 105
    (gdb) p n_bb
    $24 = {_M_elems = {-3033.6601104669598, -17026.162785173001, 17500, -2957.2020190421363, -16949.704693748179, 17970}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $25 = 6
    (gdb) p n->typecode
    $26 = 105
    (gdb) p n_bb
    $27 = {_M_elems = {-2198.0230220829371, -17173.508149935769, 17851.471862576145, -2121.5649306581136, -17097.050058510948, 18321.471862576145}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $28 = 7
    (gdb) p n->typecode
    $29 = 105
    (gdb) p n_bb
    $30 = {_M_elems = {-1851.8908068523101, -17234.540598373318, 18700, -1775.432715427487, -17158.082506948496, 19170}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $31 = 8
    (gdb) p n->typecode
    $32 = 105
    (gdb) p n_bb
    $33 = {_M_elems = {-2198.0230220829371, -17173.508149935769, 19548.528137423858, -2121.5649306581136, -17097.050058510948, 20018.528137423858}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $34 = 9
    (gdb) o n->typecode
    Ambiguous command "o n->typecode": obscure, output, ov, overlay, ovly.
    (gdb) p n->typecode
    $35 = 105
    (gdb) p n_bb
    $36 = {_M_elems = {-3033.6601104669594, -17026.162785173001, 19900, -2957.2020190421358, -16949.704693748179, 20370}}
    (gdb) c
    Continuing.

    Breakpoint 5, stree::get_node_bb (this=0x53d5b0, bb=..., node=...) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2694
    2694	        if(tv && leaf && n_aabb && !n->is_complement_primitive()) s_bb::IncludeAABB( bb.data(), n_aabb, out );
    (gdb) p i
    $37 = 10
    (gdb) p node.lvid
    $38 = 124
    (gdb) 

    quit
    A debugging session is active.

        Inferior 1 [process 333422] will be killed.

    Quit anyway? (y or n) y

    Tue Dec  9 03:37:15 PM CST 2025
    (ok) A[blyth@localhost CSGOptiX]$ BP=stree::get_node_bb FULLSCREEN=0  stree__get_frame_global_LVID=124 cxr_min.sh






::

    (ok) A[blyth@localhost CSGOptiX]$ cd /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXRenderInteractiveTest
    (ok) A[blyth@localhost CSGOptiXRenderInteractiveTest]$ l
    total 3756
       8 -rw-r--r--.  1 blyth blyth    4647 Dec  9 16:17 CSGOptiXRenderInteractiveTest.log
       4 -rw-r--r--.  1 blyth blyth     656 Dec  9 16:17 stree__get_frame_global_LVID_124.npy
       4 drwxr-xr-x.  2 blyth blyth    4096 Dec  9 16:12 .
       4 drwxr-xr-x. 19 blyth blyth    4096 Nov 12 11:48 ..
      64 -rw-r--r--.  1 blyth blyth   64385 Jul  1 20:47 20250701_204730_00000_depth.jpg
    3604 -rw-r--r--.  1 blyth blyth 3686528 Jul  1 20:47 20250701_204730_00000_depth.npy
      68 -rw-r--r--.  1 blyth blyth   65709 Jul  1 20:47 20250701_204730_00000.jpg
    (ok) A[blyth@localhost CSGOptiXRenderInteractiveTest]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: IPython 0.0.2 was announced 24 years ago: https://mail.python.org/pipermail/python-list/2001-December/093408.html
    pvplt MODE:2 
    f

    CMDLINE:/data1/blyth/local/opticks_Debug/bin/f.py
    f.base:.

      : f.stree__get_frame_global_LVID_124                 :              (11, 6) : 0:02:08.428237 
      : f.20250701_204730_00000_depth                      :      (1440, 2560, 1) : 160 days, 19:32:31.908867 

     min_stamp : 2025-07-01 20:47:30.544423 
     max_stamp : 2025-12-09 16:17:54.025053 
     dif_stamp : 160 days, 19:30:23.480630 
     age_stamp : 0:02:08.428237 

    In [1]: f.stree__get_frame_global_LVID_124
    Out[1]: 
    array([[ -5990.862, -33975.867,  18935.   ,  -5990.862, -33975.867,  18935.   ],
           [ -5990.862, -33975.867,  18935.   ,  -5990.862, -33975.867,  18935.   ],
           [ -5990.862, -33975.867,  18935.   ,  -5990.862, -33975.867,  18935.   ],
           [ -4215.429, -16817.785,  18700.   ,  -4138.971, -16741.327,  19170.   ],
           [ -3869.297, -16878.817,  17851.472,  -3792.839, -16802.359,  18321.472],
           [ -3033.66 , -17026.163,  17500.   ,  -2957.202, -16949.705,  17970.   ],
           [ -2198.023, -17173.508,  17851.472,  -2121.565, -17097.05 ,  18321.472],
           [ -1851.891, -17234.541,  18700.   ,  -1775.433, -17158.083,  19170.   ],
           [ -2198.023, -17173.508,  19548.528,  -2121.565, -17097.05 ,  20018.528],
           [ -3033.66 , -17026.163,  19900.   ,  -2957.202, -16949.705,  20370.   ],
           [ -3869.297, -16878.817,  19548.528,  -3792.839, -16802.359,  20018.528]])

    In [2]: 




    In [1]: f.stree__get_frame_global_LVID_124
    Out[1]: 
    array([[ -4215.429, -16817.785,  18700.   ,  -4138.971, -16741.327,  19170.   ],
           [ -3869.297, -16878.817,  17851.472,  -3792.839, -16802.359,  18321.472],
           [ -3033.66 , -17026.163,  17500.   ,  -2957.202, -16949.705,  17970.   ],
           [ -2198.023, -17173.508,  17851.472,  -2121.565, -17097.05 ,  18321.472],
           [ -1851.891, -17234.541,  18700.   ,  -1775.433, -17158.083,  19170.   ],
           [ -2198.023, -17173.508,  19548.528,  -2121.565, -17097.05 ,  20018.528],
           [ -3033.66 , -17026.163,  19900.   ,  -2957.202, -16949.705,  20370.   ],
           [ -3869.297, -16878.817,  19548.528,  -3792.839, -16802.359,  20018.528]])



HMM: THESE BBOX LOOK LIKE THEY HAVE A WHOPPER UNEXPECTED OFFSET IN Y ?::

    In [3]: bb = f.stree__get_frame_global_LVID_124

    In [4]: bb[:,1]
    Out[4]: array([-16817.785, -16878.817, -17026.163, -17173.508, -17234.541, -17173.508, -17026.163, -16878.817])

    In [5]: bb[:,1].min()
    Out[5]: np.float64(-17234.540598373318)

    In [6]: bb[:,1].max()
    Out[6]: np.float64(-16817.784971972684)

    In [7]: bb[:,1].max() - bb[:,1].min()
    Out[7]: np.float64(416.75562640063436)

    In [8]: bb[:,4].max() - bb[:,4].min()
    Out[8]: np.float64(416.75562640063436)



About 17m offset in Y::


    In [14]: bb + np.array([0,17000,0,0,17000,0])
    Out[14]: 
    array([[-4215.429,   182.215, 18700.   , -4138.971,   258.673, 19170.   ],
           [-3869.297,   121.183, 17851.472, -3792.839,   197.641, 18321.472],
           [-3033.66 ,   -26.163, 17500.   , -2957.202,    50.295, 17970.   ],
           [-2198.023,  -173.508, 17851.472, -2121.565,   -97.05 , 18321.472],
           [-1851.891,  -234.541, 18700.   , -1775.433,  -158.083, 19170.   ],
           [-2198.023,  -173.508, 19548.528, -2121.565,   -97.05 , 20018.528],
           [-3033.66 ,   -26.163, 19900.   , -2957.202,    50.295, 20370.   ],
           [-3869.297,   121.183, 19548.528, -3792.839,   197.641, 20018.528]])



    In [15]: bb2 = bb + np.array([0,17000,0,0,17000,0])
        ...: 

    In [16]: bb2[3:]
    Out[16]: 
    array([[-2198.023,  -173.508, 17851.472, -2121.565,   -97.05 , 18321.472],
           [-1851.891,  -234.541, 18700.   , -1775.433,  -158.083, 19170.   ],
           [-2198.023,  -173.508, 19548.528, -2121.565,   -97.05 , 20018.528],
           [-3033.66 ,   -26.163, 19900.   , -2957.202,    50.295, 20370.   ],
           [-3869.297,   121.183, 19548.528, -3792.839,   197.641, 20018.528]])

    In [17]: bb2[:,3:]
    Out[17]: 
    array([[-4138.971,   258.673, 19170.   ],
           [-3792.839,   197.641, 18321.472],
           [-2957.202,    50.295, 17970.   ],
           [-2121.565,   -97.05 , 18321.472],
           [-1775.433,  -158.083, 19170.   ],
           [-2121.565,   -97.05 , 20018.528],
           [-2957.202,    50.295, 20370.   ],
           [-3792.839,   197.641, 20018.528]])

    In [18]: bb2[:,:3]
    Out[18]: 
    array([[-4215.429,   182.215, 18700.   ],
           [-3869.297,   121.183, 17851.472],
           [-3033.66 ,   -26.163, 17500.   ],
           [-2198.023,  -173.508, 17851.472],
           [-1851.891,  -234.541, 18700.   ],
           [-2198.023,  -173.508, 19548.528],
           [-3033.66 ,   -26.163, 19900.   ],
           [-3869.297,   121.183, 19548.528]])

    In [19]: bb2[:,3:] - bb2[:,:3]
    Out[19]: 
    array([[ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ],
           [ 76.458,  76.458, 470.   ]])









::

    CSGTarget=INFO FULLSCREEN=0 MOI=0.000,0.000,18935.000,1435.000 CSGFoundry__getFrame_VERBOSE=1 SGLFW__renderloop_tail_LEVEL=1 cxr_min.sh
    CSGTarget=INFO FULLSCREEN=0                                    CSGFoundry__getFrame_VERBOSE=1 SGLFW__renderloop_tail_LEVEL=1 cxr_min.sh






CSGTarget=INFO FULLSCREEN=0 CSGFoundry__getFrame_VERBOSE=1 SGLFW__renderloop_tail_LEVEL=1 cxr_min.sh


025-12-10 17:39:31.312 INFO  [69813] [CSGTarget::getFrame@154]  midx 124 mord 0 gord -2 rc 0
2025-12-10 17:39:31.312 INFO  [69813] [CSGFoundry::getFrame@3588] [CSGFoundry__getFrame_VERBOSE] YES frs Waterdistributor_2:0:-2 looks_like_moi YES midx 124 mord 0 gord -2 rc 0
2025-12-10 17:39:31.312 INFO  [69813] [CSGFoundry::getFrame@3617] [CSGFoundry__getFrame_VERBOSE] YES[fr.desc
sframe::desc inst 0 frs Waterdistributor_2:0:-2
 tree -
 dynamic -
 ekvid - ek - ev -
 ce  ( 0.000, 0.000,18935.000,1435.000)  is_zero 0
 m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000,18935.000, 1.000) 
 w2m ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000,-18935.000, 1.000) 
 midx  124 mord    0 gord   -2
 inst    0
 ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
 ins     0 gas     0 sensor_identifier        0 sensor_index      0
 propagate_epsilon    0.05000 is_hostside_simtrace NO
]fr.desc

2025-12-10 17:39:31.444 INFO  [69813] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv YES extra.size 44 tree_digest 301158ef96cbf4d61f96ed76aee59990 dynamic 1004b598fa0efb93c91e4f066293e602
2025-12-10 17:39:31.446 INFO  [69813] [CSGFoundry::getFrame@3569] [CSGFoundry__getFrame_VERBOSE] YES frs Waterdistributor_2:0:-2 looks_like_moi YES looks_like_raw NO 
2025-12-10 17:39:31.446 INFO  [69813] [CSGTarget::getFrameComponents@231]  (midx mord gord) (124 0 -2) 
2025-12-10 17:39:31.446 INFO  [69813] [CSGTarget::getLocalCenterExtent@286]  midx 124 mord 0 prim.size 2 mord_in_range 1
2025-12-10 17:39:31.446 INFO  [69813] [CSGTarget::getLocalCenterExtent@304]  lce ( 0.000, 0.000,18935.000,1435.000) 
2025-12-10 17:39:31.446 INFO  [69813] [CSGTarget::getFrame@154]  midx 124 mord 0 gord -2 rc 0
2025-12-10 17:39:31.446 INFO  [69813] [CSGFoundry::getFrame@3588] [CSGFoundry__getFrame_VERBOSE] YES frs Waterdistributor_2:0:-2 looks_like_moi YES midx 124 mord 0 gord -2 rc 0
2025-12-10 17:39:31.446 INFO  [69813] [CSGFoundry::getFrame@3617] [CSGFoundry__getFrame_VERBOSE] YES[fr.desc
sframe::desc inst 0 frs Waterdistributor_2:0:-2
 tree -
 dynamic -
 ekvid - ek - ev -
 ce  ( 0.000, 0.000,18935.000,1435.000)  is_zero 0
 m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000,18935.000, 1.000) 
 w2m ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) ( 0.000, 0.000,-18935.000, 1.000) 
 midx  124 mord    0 gord   -2
 inst    0
 ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
 ins     0 gas     0 sensor_identifier        0 sensor_index      0
 propagate_epsilon    0.05000 is_hostside_simtrace NO
]fr.desc

SGLFW::renderloop_tail  count 1 gm.title [Waterdistributor_2:0:-2 sfr::desc_ce  -2995.4311 -16987.9337 18935.0000  1435.0000 sglm.e(c2w*ori) [ -2995.431 -15552.934  18935.000 ] SGLM::updateTitle] SGLM::descModelMatrix
 sglm.model2world 
     1.000     0.000     0.000 -2995.431
     0.000     1.000     0.000-16987.934
     0.000     0.000     1.000 18935.000
     0.000     0.000     0.000     1.000

 sglm.world2model 
     1.000     0.000     0.000  2995.431
     0.000     1.000     0.000 16987.934
     0.000     0.000     1.000-18935.000
     0.000     0.000     0.000     1.000

 sglm.initModelMatrix_branch 1


(ok) A[blyth@localhost opticks]$ 







 841 inline void SGLM::setTreeScene( stree* _tree, SScene* _scene )
 842 {
 843     tree = _tree ;
 844     scene = _scene ;
 845 
 846     moi_fr = tree->get_frame_moi();
 847 
 848     bool DUMP = ssys::getenvbool(__setTreeScene_DUMP) ;
 849     if(DUMP) std::cout
 850         << "SGLM::setTreeScene "
 851         << __setTreeScene_DUMP
 852         << " DUMP " << ( DUMP ? "YES" : "NO " )
 853         << " moi_fr \n"
 854         << moi_fr.desc()
 855         << "\n"
 856         ;
 857 
 858 }


2179 inline sfr stree::get_frame_moi() const
2180 {
2181     float _extent = sstr::StartsWith(MOI, _EXTENT_PFX) ? sstr::To<float>( MOI + strlen(_EXTENT_PFX) ) : 0.f ;
2182     sfr mf =  _extent > 0.f ? sfr::MakeFromExtent<float>(_extent) : get_frame(MOI) ;
2183     return mf ;
2184 }




::

    In [17]: f.stree__get_frame_global_LVID_124_contrib_bb
    Out[17]: 
    array([[   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -4215.429, -16817.785,  18700.   ,  -4138.971, -16741.327,  19170.   ],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -3869.297, -16878.817,  17851.472,  -3792.839, -16802.359,  18321.472],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -3033.66 , -17026.163,  17500.   ,  -2957.202, -16949.705,  17970.   ],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -2198.023, -17173.508,  17851.472,  -2121.565, -17097.05 ,  18321.472],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -1851.891, -17234.541,  18700.   ,  -1775.433, -17158.083,  19170.   ],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -2198.023, -17173.508,  19548.528,  -2121.565, -17097.05 ,  20018.528],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -3033.66 , -17026.163,  19900.   ,  -2957.202, -16949.705,  20370.   ],
           [   -33.   ,    -33.   ,   -235.   ,     33.   ,     33.   ,    235.   ],
           [ -3869.297, -16878.817,  19548.528,  -3792.839, -16802.359,  20018.528]])

    In [18]: pos
    Out[18]: array([ -33.,  -33., -235.,    1.])

i
Similar, but not close enough::

    In [26]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[0]
    Out[26]: array([ -4203.969, -16741.327,  19170.   ,      1.   ])

    In [19]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[1]
    Out[19]: array([ -3857.836, -16802.359,  18321.472,      1.   ])

    In [20]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[2]
    Out[20]: array([ -3022.199, -16949.705,  17970.   ,      1.   ])

    In [21]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[3]
    Out[21]: array([ -2186.562, -17097.05 ,  18321.472,      1.   ])

    In [22]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[4]
    Out[22]: array([ -1840.43 , -17158.083,  19170.   ,      1.   ])

    In [23]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[5]
    Out[23]: array([ -2186.562, -17097.05 ,  20018.528,      1.   ])

    In [24]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[6]
    Out[24]: array([ -3022.199, -16949.705,  20370.   ,      1.   ])

    In [25]: pos @ f.stree__get_frame_global_LVID_124_contrib_tr[7]
    Out[25]: array([ -3857.836, -16802.359,  20018.528,      1.   ])

    In [26]: 




    In [27]: ppos = np.ones(4)

    In [28]: ppos[:3] = f.stree__get_frame_global_LVID_124_contrib_bb[0][3:]

    In [29]: ppos
    Out[29]: array([ 33.,  33., 235.,   1.])

    In [30]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[0]
    Out[30]: array([ -4150.432, -16817.785,  18700.   ,      1.   ])

    In [31]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[1]
    Out[31]: array([ -3804.3  , -16878.817,  17851.472,      1.   ])

    In [32]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[2]
    Out[32]: array([ -2968.663, -17026.163,  17500.   ,      1.   ])

    In [33]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[3]
    Out[33]: array([ -2133.026, -17173.508,  17851.472,      1.   ])

    In [34]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[4]
    Out[34]: array([ -1786.893, -17234.541,  18700.   ,      1.   ])

    In [35]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[5]
    Out[35]: array([ -2133.026, -17173.508,  19548.528,      1.   ])

    In [36]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[6]
    Out[36]: array([ -2968.663, -17026.163,  19900.   ,      1.   ])

    In [37]: ppos @ f.stree__get_frame_global_LVID_124_contrib_tr[7]
    Out[37]: array([ -3804.3  , -16878.817,  19548.528,      1.   ])







