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







find_lvid_nodes
-----------------

::

    (ok) A[blyth@localhost sysrap]$ LVID=125 ~/o/sysrap/tests/stree_load_test.sh run
    stree::desc_solid lvid 125 lvn Waterdistributor_3 root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv 125 xf Y pa Y bb Y pt N nc 11 dp  0 tg co bb.desc [-100000.000,-100000.000,-100000.000,100000.000,100000.000,100000.000]
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
    st.find_lvid_nodes  lvid 125 src N nodes.size 2
     nidx 67889
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 18935.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 18935.0000     1.0000.

     nidx 67891
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -18838.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -18838.0000     1.0000.



    sn::Desc(nds) (csg nodes) lvid 125 num_nds 12
    sn::Desc num_nd 12-
    sn::desc pid  600 idx  600 typecode  11 num_node  12 num_leaf  11 maxdepth  1 is_positive_form Y lvid 125 xform Y tag co
    sn::desc pid  601 idx  601 typecode 125 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag no
    sn::desc pid  602 idx  602 typecode 125 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag no
    sn::desc pid  603 idx  603 typecode 125 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag no
    sn::desc pid  604 idx  604 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  605 idx  605 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  606 idx  606 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  607 idx  607 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  608 idx  608 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  609 idx  609 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  610 idx  610 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy
    sn::desc pid  611 idx  611 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid 125 xform Y tag cy

     sn::DescXform(nds) (csg nodes) lvid 125 num_nds 12sn::DescXform num_nd 12-
    sn::desc_xform pid  600 idx  600 lvid 125 xform Y  t      0.0000     0.0000 17250.0000     1.0000 v     -0.0000     0.0000 -17250.0000     1.0000 tag co
    sn::desc_xform pid  601 idx  601 lvid 125 xform Y  t      0.0000     0.0000 17250.0000     1.0000 v     -0.0000     0.0000 -17250.0000     1.0000 tag no
    sn::desc_xform pid  602 idx  602 lvid 125 xform Y  t      0.0000     0.0000 17250.0000     1.0000 v     -0.0000     0.0000 -17250.0000     1.0000 tag no
    sn::desc_xform pid  603 idx  603 lvid 125 xform Y  t      0.0000     0.0000 17250.0000     1.0000 v     -0.0000     0.0000 -17250.0000     1.0000 tag no
    sn::desc_xform pid  604 idx  604 lvid 125 xform Y  t  -1200.0000     0.0000     0.0000     1.0000 v   1200.0000    -0.0000    -0.0000     1.0000 tag cy
    sn::desc_xform pid  605 idx  605 lvid 125 xform Y  t   -848.5281  -848.5281     0.0000     1.0000 v    848.5281     0.0000  -848.5281     1.0000 tag cy
    sn::desc_xform pid  606 idx  606 lvid 125 xform Y  t     -0.0000 -1200.0000     0.0000     1.0000 v      0.0000     0.0000 -1200.0000     1.0000 tag cy
    sn::desc_xform pid  607 idx  607 lvid 125 xform Y  t    848.5281  -848.5281     0.0000     1.0000 v   -848.5281     0.0000  -848.5281     1.0000 tag cy
    sn::desc_xform pid  608 idx  608 lvid 125 xform Y  t   1200.0000    -0.0000     0.0000     1.0000 v  -1200.0000     0.0000    -0.0000     1.0000 tag cy
    sn::desc_xform pid  609 idx  609 lvid 125 xform Y  t    848.5281   848.5281    -0.0000     1.0000 v   -848.5281     0.0000   848.5281     1.0000 tag cy
    sn::desc_xform pid  610 idx  610 lvid 125 xform Y  t      0.0000  1200.0000    -0.0000     1.0000 v     -0.0000     0.0000  1200.0000     1.0000 tag cy
    sn::desc_xform pid  611 idx  611 lvid 125 xform Y  t   -848.5281   848.5281    -0.0000     1.0000 v    848.5281     0.0000   848.5281     1.0000 tag cy




HMM: where is the +Z 17250 transform on the compound coming from ?
-------------------------------------------------------------------


At solid convert level there are no transforms there::

    [U4SolidMakerTest nd->detail_r()
    sn::detail_r
      0: 0x16f9b20 sn::descXF (s_tv)xform -
      1: 0x1670dc0 sn::descXF (s_tv)xform -
      1: 0x166d440 sn::descXF (s_tv)xform -
      1: 0x16f88a0 sn::descXF (s_tv)xform -
      1: 0x16f8920 sn::descXF (s_tv)xform  t  -1200.0000     0.0000     0.0000     1.0000 v   1200.0000    -0.0000    -0.0000     1.0000
      1: 0x16f8b30 sn::descXF (s_tv)xform  t   -848.5281  -848.5281     0.0000     1.0000 v    848.5281     0.0000  -848.5281     1.0000
      1: 0x16f8d80 sn::descXF (s_tv)xform  t     -0.0000 -1200.0000     0.0000     1.0000 v      0.0000     0.0000 -1200.0000     1.0000
      1: 0x16f8fd0 sn::descXF (s_tv)xform  t    848.5281  -848.5281     0.0000     1.0000 v   -848.5281     0.0000  -848.5281     1.0000
      1: 0x16f9220 sn::descXF (s_tv)xform  t   1200.0000    -0.0000     0.0000     1.0000 v  -1200.0000     0.0000    -0.0000     1.0000
      1: 0x16f9470 sn::descXF (s_tv)xform  t    848.5281   848.5281    -0.0000     1.0000 v   -848.5281     0.0000   848.5281     1.0000
      1: 0x16f96c0 sn::descXF (s_tv)xform  t      0.0000  1200.0000    -0.0000     1.0000 v     -0.0000     0.0000  1200.0000     1.0000
      1: 0x16f9910 sn::descXF (s_tv)xform  t   -848.5281   848.5281    -0.0000     1.0000 v    848.5281     0.0000   848.5281     1.0000


::

    (ok) A[blyth@localhost tests]$ opticks-f setXF
    ./sysrap/sn.h:    void setXF(     const glm::tmat4x4<double>& t );
    ./sysrap/sn.h:    void setXF(     const glm::tmat4x4<double>& t, const glm::tmat4x4<double>& v ) ;
    ./sysrap/sn.h:inline void sn::setXF( const glm::tmat4x4<double>& t )
    ./sysrap/sn.h:    setXF(t, v);
    ./sysrap/sn.h:inline void sn::setXF( const glm::tmat4x4<double>& t, const glm::tmat4x4<double>& v )
    ./sysrap/snd.cc:snd::setXF
    ./sysrap/snd.cc:Calling setXF again will just adds another transform 
    ./sysrap/snd.cc:the setXF actually needs to combine the transforms as was done in nnode::set_transform
    ./sysrap/snd.cc:void snd::setXF(const glm::tmat4x4<double>& t )
    ./sysrap/snd.cc:    setXF(t, v); 
    ./sysrap/snd.cc:void snd::setXF(const glm::tmat4x4<double>& t, const glm::tmat4x4<double>& v )
    ./sysrap/snd.cc:            << "snd::setXF STOMPING"
    ./sysrap/snd.cc:    CheckPOOL("snd::setXForm") ; 
    ./sysrap/snd.cc:        setXF(t,v); 
    ./sysrap/snd.hh:    void setXF( const glm::tmat4x4<double>& t ); 
    ./sysrap/snd.hh:    void setXF( const glm::tmat4x4<double>& t, const glm::tmat4x4<double>& v ) ; 
    ./sysrap/tests/stree_create_test.cc:        r->setXF(tv->t, tv->v );  
    ./sysrap/tests/sn_test.cc:    r->setXF(t); 
    ./u4/U4Solid.h:    root->setXF(scale);
    (ok) A[blyth@localhost opticks]$ u4
    /home/blyth/opticks/u4



HMM : could it be a meaningfull -1 issue for an unset xform ? 
---------------------------------------------------------------

::

      68 struct _sn
      69 {
      70     int  typecode ;     // 0
      71     int  complement ;   // 1
      72     int  lvid ;         // 2
      73     int  xform ;        // 3
      74     int  param ;        // 4
      75     int  aabb ;         // 5
      76     int  parent ;       // 6
      77 
      78 #ifdef WITH_CHILD
      79     int  sibdex ;       // 7     0-based sibling index
      80     int  num_child ;    // 8
      81     int  first_child ;  // 9
      82     int  next_sibling ; // 10
      83     int  index ;        // 11
      84     int  depth ;        // 12
      85     int  note  ;        // 13
      86     int  coincide ;     // 14
      87     char label[16] ;    // 15,16,17,18
      88     static constexpr const char* ITEM = "19" ;



::

    In [13]: f.sn[f.sn[:,2]==125]
    Out[13]: 
    array([[125,   0, 125,  -1,  -1, 428, 611,   0,   0,  -1, 592, 582,   1,   0,   0,   0,   0,   0,   0],
           [125,   0, 125,  -1,  -1, 429, 611,   1,   0,  -1, 602, 592,   1,   0,   0,   0,   0,   0,   0],
           [125,   0, 125,  -1,  -1, 430, 611,   2,   0,  -1, 603, 602,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 290, 410, 420, 611,   3,   0,  -1, 604, 603,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 291, 411, 421, 611,   4,   0,  -1, 605, 604,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 292, 412, 422, 611,   5,   0,  -1, 606, 605,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 293, 413, 423, 611,   6,   0,  -1, 607, 606,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 294, 414, 424, 611,   7,   0,  -1, 608, 607,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 295, 415, 425, 611,   8,   0,  -1, 609, 608,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 296, 416, 426, 611,   9,   0,  -1, 610, 609,   1,   0,   0,   0,   0,   0,   0],
           [105,   0, 125, 297, 417, 427, 611,  10,   0,  -1,  -1, 610,   1,   0,   0,   0,   0,   0,   0],
           [ 11,   0, 125,  -1,  -1,  -1,  -1,   0,  11, 582,  -1, 611,   0,   0,   0,   0,   0,   0,   0]], dtype=int32)


    In [6]: np.where( f.s_tv == 17250 )
    Out[6]: (array([399]), array([0]), array([3]), array([2]))

    In [7]: f.s_tv[399]
    Out[7]: 
    array([[[     1.,      0.,      0.,      0.],
            [     0.,      1.,      0.,      0.],
            [     0.,      0.,      1.,      0.],
            [     0.,      0.,  17250.,      1.]],

           [[     1.,     -0.,      0.,     -0.],
            [    -0.,      1.,     -0.,      0.],
            [     0.,     -0.,      1.,     -0.],
            [    -0.,      0., -17250.,      1.]]])

    In [8]: f.s_tv[-1]
    Out[8]: 
    array([[[     1.,      0.,      0.,      0.],
            [     0.,      1.,      0.,      0.],
            [     0.,      0.,      1.,      0.],
            [     0.,      0.,  17250.,      1.]],

           [[     1.,     -0.,      0.,     -0.],
            [    -0.,      1.,     -0.,      0.],
            [     0.,     -0.,      1.,     -0.],
            [    -0.,      0., -17250.,      1.]]])



Who really uses that last transform, lvid 343 (sBottomRock_withLowerRect, one before sWorld::

    In [14]: f.sn[f.sn[:,3]==399]
    Out[14]: array([[ 110,    0,  343,  399,  753,  766, 1053,    1,    0,   -1,   -1, 1052,    1,    0,    0,    0,    0,    0,    0]], dtype=int32)

::


    In [10]: 22.25-5
    Out[10]: 17.25


I suspect that sn csg nodes without transforms are magically acquiring the "-1" transform after being de-serialized
---------------------------------------------------------------------------------------------------------------------- 





bbox debug
------------


The first other_aabb has unexpected whopper Y shift::

    s_bb::IncludeAABB 
     inital_aabb  [  0.000,  0.000,  0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
     other_aabb   [-4221.222,-16823.577,18700.000,-4133.179,-16735.535,19170.000] ADOPT OTHER AS STARTING
     updated_aabb [-4221.222,-16823.577,18700.000,-4133.179,-16735.535,19170.000]
    stree::get_node_bb.sub_loop.TAIL i[3/11]
    stree::get_node_bb.sub_loop.HEAD i[4/11]
    stree::get_node_bb.sub_loop.GET_COMBINED_TRAN_AND_AABB i[4]


structural snode transform looks OK, sn one does not
--------------------------------------------------------

::

    stree::get_node_bb.sub_loop.TAIL i[2/11]
    stree::get_node_bb.sub_loop.HEAD i[3/11]
    stree::get_node_bb.sub_loop.GET_COMBINED_TRAN_AND_AABB i[3]
    stree::get_node_product.HEAD nidx 67889 local 0 reverse 0
    stree::get_ancestors nidx 67889 local 0 nd0.repeat_index 0 nd.repeat_index -10 num_ancestors 8 [0 65726 65727 65728 66569 66570 67887 67888 ]
    +              snode ix:      0 dh: 0 sx:   -1 pt:     -1 nc:    2 fc:      1 ns:     -1 lv:344 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd:  0 sn:-1 ou Y    98 : 301158ef96cbf4d61f96ed76aee59990 :     1 sWorld
     +             snode ix:  65726 dh: 1 sx:    1 pt:      0 nc:    1 fc:  65727 ns:     -1 lv:343 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd:  1 sn:-1 ou N   112 : 7be309d42747e431541776b09ae8eff4 :     1 sBottomRock_withLowerRect
      +            snode ix:  65727 dh: 2 sx:    0 pt:  65726 nc:    1 fc:  65728 ns:     -1 lv:342 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 30 sn:-1 ou N   113 : b4671d162461927d31dff4ba8397f405 :     1 sPoolLining
       +           snode ix:  65728 dh: 3 sx:    0 pt:  65727 nc: 3548 fc:  65729 ns:     -1 lv:341 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 31 sn:-1 ou N   114 : 58e5be105f11f4bb80baa8af737ee720 :     1 sOuterWaterPool
        +          snode ix:  66569 dh: 4 sx:  800 pt:  65728 nc:    1 fc:  66570 ns: 372948 lv:336 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 76 sn:-1 ou N   131 : 56675a5bf92b389cc8b35ed6e0b670a4 :     1 sOuterReflectorInCD_TSubWaterDistributor_cutTube2
         +         snode ix:  66570 dh: 5 sx:    0 pt:  66569 nc: 1317 fc:  66571 ns:     -1 lv:335 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 77 sn:-1 ou N   132 : f4eb1e79f14bd046068830ceb85b4549 :     1 sOuterWaterInCD_TSubWaterDistributor_cutTube2
          +        snode ix:  67887 dh: 6 sx: 1316 pt:  66570 nc:    1 fc:  67888 ns:     -1 lv:334 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd:125 sn:-1 ou N   139 : 5b62ff8f84e2a9ab081a37032ae47e40 :     1 sInnerReflectorInCD_TSubWaterDistributor_cutTube2
           +       snode ix:  67888 dh: 7 sx:    0 pt:  67887 nc:45756 fc:  67889 ns:     -1 lv:333 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd:126 sn:-1 ou N   140 : f0dda094a986487a979dc25257c627e9 :     1 sInnerWater_TSubWaterDistributor_cutTube2
            +      snode ix:  67889 dh: 8 sx:    0 pt:  67888 nc:    1 fc:  67890 ns:  67891 lv:125 cp:      0 se:     -1 se:     -1 ri: 0 ro:   -1 bd:127 sn:-1 ou N    95 : 224af5cd0a32e9a7d52f4c4e165c411f :     2 Waterdistributor_3 
    stree::get_node_product nidx 67889 local 0 reverse 0 is_local_outer 0 num_nodes 9 [ 0 65726 65727 65728 66569 66570 67887 67888 67889]

     i 0 j 8 ii 0 jj 67889 s_ii sWorld s_jj Waterdistributor_3

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     0.9848     -0.1736    0.0000     0.0000                0.9848     0.0000     -0.1736    0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.1736    0.0000     -0.9848    0.0000                0.0000     1.0000     0.0000     0.0000    
     -0.1736    -0.9848    0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     18935.0000 1.0000                0.0000     -18935.0000 -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 1 j 7 ii 65726 jj 67888 s_ii sBottomRock_withLowerRect s_jj sInnerWater_TSubWaterDistributor_cutTube2

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 2 j 6 ii 65727 jj 67887 s_ii sPoolLining s_jj sInnerReflectorInCD_TSubWaterDistributor_cutTube2

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 3 j 5 ii 65728 jj 66570 s_ii sOuterWaterPool s_jj sOuterWaterInCD_TSubWaterDistributor_cutTube2

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 4 j 4 ii 66569 jj 66569 s_ii sOuterReflectorInCD_TSubWaterDistributor_cutTube2 s_jj sOuterReflectorInCD_TSubWaterDistributor_cutTube2

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 5 j 3 ii 66570 jj 65728 s_ii sOuterWaterInCD_TSubWaterDistributor_cutTube2 s_jj sOuterWaterPool

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 6 j 2 ii 67887 jj 65727 s_ii sInnerReflectorInCD_TSubWaterDistributor_cutTube2 s_jj sPoolLining

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 7 j 1 ii 67888 jj 65726 s_ii sInnerWater_TSubWaterDistributor_cutTube2 s_jj sBottomRock_withLowerRect

     it                                                     iv                                                     it*iv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 8 j 0 ii 67889 jj 0 s_ii Waterdistributor_3 s_jj sWorld

     it                                                     iv                                                     it*iv                                                 
     0.9848     -0.1736    0.0000     0.0000                0.9848     0.0000     -0.1736    0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.1736    0.0000     -0.9848    0.0000                0.0000     1.0000     0.0000     0.0000    
     -0.1736    -0.9848    0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     18935.0000 1.0000                0.0000     -18935.0000 -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     jt                                                     jv                                                     jt*jv                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                -0.0000    -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    
    stree::get_node_product tp:product.it, vp:product.jv in opposite order

     tp                                                     vp                                                     tp*vp                                                 
     0.9848     -0.1736    0.0000     0.0000                0.9848     0.0000     -0.1736    0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.1736    0.0000     -0.9848    0.0000                0.0000     1.0000     0.0000     0.0000    
     -0.1736    -0.9848    0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     18935.0000 1.0000                0.0000     -18935.0000 -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    
    stree::get_node_product.TAIL nidx 67889 local 0 reverse 0

    sn::getNodeTransformProduct idx 604 reverse 0 num_nds 2
     i 0 j 1 ii.idx 600 jj.idx 604 ixf Y jxf Y

     (ixf.t)                                                (ixf.v)                                                (ixf.t)*(ixf.v)                                       
     1.0000     0.0000     0.0000     0.0000                1.0000     -0.0000    0.0000     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                -0.0000    1.0000     -0.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     -0.0000    1.0000     -0.0000               0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     17250.0000 1.0000                -0.0000    0.0000     -17250.0000 1.0000                0.0000     0.0000     0.0000     1.0000    


     (jxf.t)                                                (jxf.v)                                                (jxf.t)*(jxf.v)                                       
     1.0000     0.0000     0.0000     0.0000                1.0000     -0.0000    0.0000     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.0000    0.0000     -1.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     -1.0000    0.0000     0.0000                -0.0000    1.0000     0.0000     -0.0000               0.0000     0.0000     1.0000     0.0000    
     -1200.0000 0.0000     0.0000     1.0000                1200.0000  -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    

     i 1 j 0 ii.idx 604 jj.idx 600 ixf Y jxf Y

     (ixf.t)                                                (ixf.v)                                                (ixf.t)*(ixf.v)                                       
     1.0000     0.0000     0.0000     0.0000                1.0000     -0.0000    0.0000     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.0000    0.0000     -1.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     -1.0000    0.0000     0.0000                -0.0000    1.0000     0.0000     -0.0000               0.0000     0.0000     1.0000     0.0000    
     -1200.0000 0.0000     0.0000     1.0000                1200.0000  -0.0000    -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    


     (jxf.t)                                                (jxf.v)                                                (jxf.t)*(jxf.v)                                       
     1.0000     0.0000     0.0000     0.0000                1.0000     -0.0000    0.0000     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                -0.0000    1.0000     -0.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     -0.0000    1.0000     -0.0000               0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     17250.0000 1.0000                -0.0000    0.0000     -17250.0000 1.0000                0.0000     0.0000     0.0000     1.0000    


     tp                                                     vp                                                     tp*vp                                                 
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     -1.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     -1.0000    0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     -1200.0000 0.0000     17250.0000 1.0000                1200.0000  -17250.0000 -0.0000    1.0000                0.0000     0.0000     0.0000     1.0000    


     (tt*tc)                                                (vc*vv)                                                (tt*tc)*(vc*vv)                                       
     0.9848     -0.1736    0.0000     0.0000                0.9848     -0.1736    -0.0000    0.0000                1.0000     0.0000     0.0000     0.0000    
     -0.1736    -0.9848    0.0000     0.0000                -0.1736    -0.9848    -0.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     -0.0000    -0.0000    -1.0000    0.0000                0.0000     0.0000     -1.0000    0.0000                0.0000     0.0000     1.0000     0.0000    
     -4177.2004 -16779.5559 18935.0000 1.0000                1200.0000  -17250.0000 18935.0000 1.0000                0.0000     0.0000     -0.0000    1.0000    


    stree::get_node_bb.sub_loop.i[3].n_bb0 [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
    stree::get_node_bb.sub_loop.i[3].n_bb  [-4221.222,-16823.577,18700.000,-4133.179,-16735.535,19170.000]
    s_bb::IncludeAABB 
     inital_aabb  [  0.000,  0.000,  0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
     other_aabb   [-4221.222,-16823.577,18700.000,-4133.179,-16735.535,19170.000] ADOPT OTHER AS STARTING
     updated_aabb [-4221.222,-16823.577,18700.000,-4133.179,-16735.535,19170.000]
    stree::get_node_bb.sub_loop.TAIL i[3/11]
    stree::get_node_bb.sub_loop.HEAD i[4/11]
    stree::get_node_bb.sub_loop.GET_COMBINED_TRAN_AND_AABB i[4]





sn::NodeTransformProduct
--------------------------


::

    (gdb) bt
    #0  sn::getNodeTransformProduct (this=0x112c4c20, t=..., v=..., reverse=false, out=0x1d09c940) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5070
    #1  0x00000000004768ff in sn::NodeTransformProduct (idx=601, t=..., v=..., reverse=false, out=0x1d09c940) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:5040
    #2  0x000000000047f922 in stree::get_combined_transform (this=0x5405b0, t=..., v=..., node=..., nd=0x112c4c20, out=0x1d09c940) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:3342
    #3  0x000000000047fd85 in stree::get_combined_tran_and_aabb (this=0x5405b0, aabb=0x7fffffffa2b0, node=..., nd=0x112c4c20, out=0x1d09c940) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:3397
    #4  0x000000000047dd26 in stree::get_node_bb (this=0x5405b0, bb=..., node=..., contrib_bb=0x1d09bf70, contrib_tr=0x1d09bed0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2803
    #5  0x000000000047d546 in stree::get_node_ce_bb (this=0x5405b0, ce=..., bb=..., node=..., contrib_bb=0x1d09bf70, contrib_tr=0x1d09bed0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2668
    #6  0x000000000047cc1c in stree::_get_frame_global (this=0x5405b0, f=..., lvid=125, lvid_ordinal=0, repeat_ordinal=-2, ridx_type=63 '?') at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2588
    #7  0x000000000047ca3a in stree::get_frame_global (this=0x5405b0, f=..., lvid=125, lvid_ordinal=0, repeat_ordinal=-2) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2520
    #8  0x000000000047bd5e in stree::get_frame_from_triplet (this=0x5405b0, f=..., q_spec=0x7fffffffbb19 "Waterdistributor_3:0:-2") at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2269
    #9  0x000000000047bb7a in stree::get_frame (this=0x5405b0, q_spec=0x7fffffffbb19 "Waterdistributor_3:0:-2") at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2216
    #10 0x000000000047baa1 in stree::get_frame_moi (this=0x5405b0) at /data1/blyth/local/opticks_Debug/include/SysRap/stree.h:2185
    #11 0x0000000000489a04 in SGLM::setTreeScene (this=0x1d09c030, _tree=0x5405b0, _scene=0x28e1c80) at /data1/blyth/local/opticks_Debug/include/SysRap/SGLM.h:846
    #12 0x0000000000494897 in CSGOptiXRenderInteractiveTest::init (this=0x7fffffffae90) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:124
    #13 0x0000000000494786 in CSGOptiXRenderInteractiveTest::CSGOptiXRenderInteractiveTest (this=0x7fffffffae90) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:113
    #14 0x000000000044658d in main (argc=1, argv=0x7fffffffb038) at /home/blyth/opticks/CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc:206
    (gdb) 
        stree::get_node_product.HEAD nidx 67889 local 0 reverse 0
         



jgr Waterdistributor
--------------------

::

    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:std::vector<PlacedSolid> WaterdistributorpipeMaker::MakeLoopDistributer() {
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:    WaterdistributorlooppipeMaker* pipeMaker = new WaterdistributorlooppipeMaker("Waterdistributor", TubeR_type_I, TubeR_type_II, TubeR_type_I);
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:    result.push_back({solid_outer, G4ThreeVector(0, 0, 21409), rot, 0, "LogicWaterdistributor", "PhysWaterdistributor"});


::

    264 std::vector<PlacedSolid> WaterdistributorpipeMaker::MakeLoopDistributer() {
    265     std::vector<PlacedSolid> result;
    266 
    267     G4double TubeR_type_I = 38 * mm;
    268     G4double TubeR_type_II = 70 * mm;
    269     G4RotationMatrix rot;
    270     rot.rotateX(90 * deg);
    271     rot.rotateZ(-10 * deg);
    272 
    273     WaterdistributorlooppipeMaker* pipeMaker = new WaterdistributorlooppipeMaker("Waterdistributor", TubeR_type_I, TubeR_type_II, TubeR_type_I);
    274     G4VSolid* solid_outer = pipeMaker->getSolid();
    275 
    276     result.push_back({solid_outer, G4ThreeVector(0, 0, 21409), rot, 0, "LogicWaterdistributor", "PhysWaterdistributor"});
    277 
    278     WaterdistributorlooppipeMaker* pipeMaker_inner = new WaterdistributorlooppipeMaker(
    279         "Waterdistributor", TubeR_type_I - 5 * mm, TubeR_type_II - 5 * mm, TubeR_type_I - 5 * mm
    280     );
    281     G4VSolid* solid_inner = pipeMaker_inner->getSolid();
    282     result.push_back({solid_inner, G4ThreeVector(0, 0, 0), G4RotationMatrix(), 0, "LogicWaterdistributor_partII", "PhysWaterdistributor_partII"});
    283 
    284     return result;
    285 }


    A[blyth@localhost junosw]$ jgr MakeLoopDistributer
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh:    std::vector<PlacedSolid> MakeLoopDistributer();
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:std::vector<PlacedSolid> WaterdistributorpipeMaker::MakeLoopDistributer() {
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    A[blyth@localhost junosw]$ 




    1040 void
    1041 DetSim1Construction::makeWaterdistributorLooppipe()
    1042 {
    1043     G4LogicalVolume* logicLoopOuter = nullptr;
    1044     G4LogicalVolume* logicLoopInner = nullptr;
    1045     double m_waterDistributorLoopTopZ = 18935*mm;     // Top position of water distributor looppipe
    1046     double m_waterDistributorLoopBottomZ = -18838*mm; // Bottom position of water distributor looppipe
    1047     G4RotationMatrix rot;
    1048 
    1049     auto loop_vec = WaterdistributorpipeMaker::MakeLoopDistributer();
    1050     for (size_t i = 0; i < loop_vec.size(); ++i) {
    1051         const auto& p = loop_vec[i];
    1052         if(i==0) {
    1053             logicLoopOuter = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
    1054 
    1055             G4VisAttributes* visAttr1 = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    1056             visAttr1->SetForceAuxEdgeVisible(true);
    1057             logicLoopOuter->SetVisAttributes(visAttr1);
    1058 
    1059             new G4PVPlacement(G4Transform3D(p.rot, G4ThreeVector(0, 0, m_waterDistributorLoopTopZ)), logicLoopOuter, "pWaterDistributorLoopOuterCD_I", logicInnerWaterPool, false, p.copy_no);
    1060 
    1061             rot = p.rot;
    1062         } else {
    1063             logicLoopInner = new G4LogicalVolume(p.solid, (i==0 ? PVDF : Water), p.log_name);
    1064 
    1065             G4VisAttributes* visAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
    1066             visAttr->SetForceSolid(true);
    1067             logicLoopInner->SetVisAttributes(visAttr);
    1068             new G4PVPlacement(G4Transform3D(p.rot, p.pos), logicLoopInner, p.phy_name,logicLoopOuter, false, p.copy_no);
    1069         }
    1070     }
    1071 
    1072     new G4PVPlacement(G4Transform3D(rot, G4ThreeVector(0, 0, m_waterDistributorLoopBottomZ)), logicLoopOuter, "pWaterDistributorLoopOuterCD_II", logicInnerWaterPool, false, 1);
    1073 
    1074     G4OpticalSurface* pvdf_surface = new G4OpticalSurface("PVDFOpticalSurface");
    1075     pvdf_surface->SetModel(unified);
    1076     pvdf_surface->SetType(dielectric_dielectric);
    1077     pvdf_surface->SetFinish(ground);
    1078     pvdf_surface->SetSigmaAlpha(0.1);
    1079 




















::

     06 WaterdistributorlooppipeMaker::WaterdistributorlooppipeMaker(const std::string& name,
      7     double TubeR_type_I, 
      8     double TubeR_type_II,
      9     double holeR)
     10 {
     11     G4MultiUnion* multiUnion = new G4MultiUnion(name);
     12 
     13     G4double distance = 120 *cm;
     14     G4double TubeR_I = TubeR_type_I;
     15     
     16     G4double TubeR_II = TubeR_type_II;
     17 
     18     G4double TubeR_III = TubeR_type_I;
     19 
     20     G4double holeRadius = holeR;
     21 
     22     auto solid_I = helper_Waterdistributorlooppipe("Waterdistributor_I",distance, TubeR_I);
     23     auto solid_II = helper_Waterdistributorlooppipe("Waterdistributor_II",distance, TubeR_II);
     24     auto solid_III = helper_Waterdistributorlooppipe("Waterdistributor_III",distance, TubeR_III);
     25 
     26     G4RotationMatrix* rotation = new G4RotationMatrix();
     27     G4ThreeVector positionI(0, 23.5*cm, 0);
     28     G4Transform3D trI = G4Transform3D(*rotation, positionI);
     29     
     30     G4ThreeVector positionII(0, 0, 0);
     31     G4Transform3D trII = G4Transform3D(*rotation, positionII);
     32 
     33     G4ThreeVector positionIII(0, - 23.5*cm, 0);
     34     G4Transform3D trIII = G4Transform3D(*rotation, positionIII); 
     35 
     36     multiUnion->AddNode(*solid_II, trII);
     37     multiUnion->AddNode(*solid_I, trI);
     38     multiUnion->AddNode(*solid_III, trIII);
     39 
     40     for (int i = 0; i < 8; i++) {
     41         // Create circular hole geometry
     42         G4Tubs* hole = new G4Tubs("Hole_" + std::to_string(i), 0, holeRadius, (23.5) * cm, 0, 360 * deg);
     43 
     44         G4double theta = i * 45 * deg;
     45         G4RotationMatrix* rotation = new G4RotationMatrix();
     46         rotation->rotateX(90 * deg);
     47 
     48         G4ThreeVector position(-distance * cos(theta), 0, distance * sin(theta));
     49         G4Transform3D tr = G4Transform3D(*rotation, position);
     50     
     51         multiUnion->AddNode(*hole, tr);
     52     }
     53 
     54     multiUnion->Voxelize();
     55 
     56     m_solid = multiUnion;
     57 }



Those 8 are the vertical cylinders around the octagon, and the last transforms
of each t_stack places them::

    In [50]: f.stree__get_node_bb_LVID_125_10_isub_t_stack[-1]
    Out[50]: 
    array([[   1.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    1.   ,    0.   ],
           [   0.   ,   -1.   ,    0.   ,    0.   ],
           [-848.528,  848.528,   -0.   ,    1.   ]])

    In [51]: f.stree__get_node_bb_LVID_125_9_isub_t_stack[-1]
    Out[51]: 
    array([[   1.,    0.,    0.,    0.],
           [   0.,    0.,    1.,    0.],
           [   0.,   -1.,    0.,    0.],
           [   0., 1200.,   -0.,    1.]])

    In [52]: f.stree__get_node_bb_LVID_125_8_isub_t_stack[-1]
    Out[52]: 
    array([[  1.   ,   0.   ,   0.   ,   0.   ],
           [  0.   ,   0.   ,   1.   ,   0.   ],
           [  0.   ,  -1.   ,   0.   ,   0.   ],
           [848.528, 848.528,  -0.   ,   1.   ]])

    In [53]: f.stree__get_node_bb_LVID_125_7_isub_t_stack[-1]
    Out[53]: 
    array([[   1.,    0.,    0.,    0.],
           [   0.,    0.,    1.,    0.],
           [   0.,   -1.,    0.,    0.],
           [1200.,   -0.,    0.,    1.]])

    In [54]: f.stree__get_node_bb_LVID_125_6_isub_t_stack[-1]
    Out[54]: 
    array([[   1.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    1.   ,    0.   ],
           [   0.   ,   -1.   ,    0.   ,    0.   ],
           [ 848.528, -848.528,    0.   ,    1.   ]])

    In [55]: f.stree__get_node_bb_LVID_125_5_isub_t_stack[-1]
    Out[55]: 
    array([[    1.,     0.,     0.,     0.],
           [    0.,     0.,     1.,     0.],
           [    0.,    -1.,     0.,     0.],
           [   -0., -1200.,     0.,     1.]])

    In [56]: f.stree__get_node_bb_LVID_125_4_isub_t_stack[-1]
    Out[56]: 
    array([[   1.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    1.   ,    0.   ],
           [   0.   ,   -1.   ,    0.   ,    0.   ],
           [-848.528, -848.528,    0.   ,    1.   ]])

    In [57]: f.stree__get_node_bb_LVID_125_3_isub_t_stack[-1]
    Out[57]: 
    array([[    1.,     0.,     0.,     0.],
           [    0.,     0.,     1.,     0.],
           [    0.,    -1.,     0.,     0.],
           [-1200.,     0.,     0.,     1.]])

    In [58]: 







isub_t_stack debug
---------------------



* First three constituent repeat the Z offset (looks wrong, but those degenerate bbox are skipped anyhow)
* Other eight have the unexpected big Y offset




::

    In [24]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_0_isub_t_stack)
    Out[24]: 
    array([[    0.985,    -0.174,     0.   ,     0.   ],
           [    0.   ,     0.   ,     1.   ,     0.   ],
           [   -0.174,    -0.985,     0.   ,     0.   ],
           [    0.   ,     0.   , 53435.   ,     1.   ]])

    In [25]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_1_isub_t_stack)
    Out[25]: 
    array([[    0.985,    -0.174,     0.   ,     0.   ],
           [    0.   ,     0.   ,     1.   ,     0.   ],
           [   -0.174,    -0.985,     0.   ,     0.   ],
           [    0.   ,     0.   , 53435.   ,     1.   ]])

    In [26]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_2_isub_t_stack)
    Out[26]: 
    array([[    0.985,    -0.174,     0.   ,     0.   ],
           [    0.   ,     0.   ,     1.   ,     0.   ],
           [   -0.174,    -0.985,     0.   ,     0.   ],
           [    0.   ,     0.   , 53435.   ,     1.   ]])

    In [27]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_3_isub_t_stack)
    Out[27]: 
    array([[     0.985,     -0.   ,     -0.174,      0.   ],
           [     0.   ,     -1.   ,      0.   ,      0.   ],
           [    -0.174,     -0.   ,     -0.985,      0.   ],
           [ -1200.   , -36185.   ,      0.   ,      1.   ]])

    In [28]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_4_isub_t_stack)
    Out[28]: 
    array([[     0.985,     -0.   ,     -0.174,      0.   ],
           [     0.   ,     -1.   ,      0.   ,      0.   ],
           [    -0.174,     -0.   ,     -0.985,      0.   ],
           [  -848.528, -37033.528,      0.   ,      1.   ]])

    In [29]: reduce(np.matmul, f.stree__get_node_bb_LVID_125_5_isub_t_stack)
    Out[29]: 
    array([[     0.985,     -0.   ,     -0.174,      0.   ],
           [     0.   ,     -1.   ,      0.   ,      0.   ],
           [    -0.174,     -0.   ,     -0.985,      0.   ],
           [    -0.   , -37385.   ,      0.   ,      1.   ]])

    In [30]: 




Flipping to -17250, avoids big Y shift but looses expected Z shift::

     [[     1.   ,      0.   ,      0.   ,      0.   ],
        [     0.   ,      1.   ,      0.   ,      0.   ],
        [     0.   ,      0.   ,      1.   ,      0.   ],
        [     0.   ,      0.   ,      0.   ,      1.   ]],

       [[     0.985,     -0.174,      0.   ,      0.   ],
        [     0.   ,      0.   ,      1.   ,      0.   ],
        [    -0.174,     -0.985,      0.   ,      0.   ],
        [     0.   ,      0.   ,  18935.   ,      1.   ]],

       [[     1.   ,      0.   ,      0.   ,      0.   ],
        [     0.   ,      1.   ,      0.   ,      0.   ],
        [     0.   ,      0.   ,      1.   ,      0.   ],
        [     0.   ,      0.   , -17250.   ,      1.   ]],

       [[     1.   ,      0.   ,      0.   ,      0.   ],
        [     0.   ,      0.   ,      1.   ,      0.   ],
        [     0.   ,     -1.   ,      0.   ,      0.   ],
        [    -0.   ,  -1200.   ,      0.   ,      1.   ]]])

    In [42]: ts[-3] @ ts[-2] @ ts[-1]
    Out[42]: 
    array([[    0.985,    -0.   ,    -0.174,     0.   ],
           [    0.   ,    -1.   ,     0.   ,     0.   ],
           [   -0.174,    -0.   ,    -0.985,     0.   ],
           [   -0.   , -2885.   ,     0.   ,     1.   ]])









HMM : CSGTarget::getFrame vs stree ?  Instanced is easy, global isnt
---------------------------------------------------------------------


TODO : review U4Tree workflow, where do the transforms go to in global case ?
--------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost desc]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/stree/desc
    (ok) A[blyth@localhost desc]$ grep Waterdistrib nds.txt
     uv    124 :  cn      2  ix  67890  un Waterdistributor_2
     uv    125 :  cn      2  ix  67889  un Waterdistributor_3
     uv     33 :  cn      2  ix  65742  un Waterdistributor_0
     uv     34 :  cn      2  ix  65741  un Waterdistributor_1
    (ok) A[blyth@localhost desc]$ 



125:Waterdistributor_3 is parent of 124:Waterdistributor_2
-------------------------------------------------------------

::

    (ok) A[blyth@localhost sysrap]$ LVID=125 TEST=desc_solid ~/o/sysrap/tests/stree_load_test.sh
    stree::desc_solid lvid 125 lvn Waterdistributor_3 root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv 125 xf Y pa Y bb Y pt N nc 11 dp  0 tg co bb.desc [-100000.000,-100000.000,-100000.000,100000.000,100000.000,100000.000]
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv 125 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
    st.find_lvid_nodes  lvid 125 src N nodes.size 2
     nidx 67889
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 18935.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 18935.0000     1.0000.

     nidx 67891
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -18838.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -18838.0000     1.0000.

    (ok) A[blyth@localhost sysrap]$ 




34:Waterdistributor_1 is parent of 33:Waterdistributor_0 so need that transform tree ?
---------------------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost sysrap]$ LVID=34 TEST=desc_solid ~/o/sysrap/tests/stree_load_test.sh
    stree::desc_solid lvid 34 lvn Waterdistributor_1 root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv  34 xf Y pa Y bb Y pt N nc 11 dp  0 tg co bb.desc [-100000.000,-100000.000,-100000.000,100000.000,100000.000,100000.000]
      1 : sn::brief tc  125 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  34 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-38.000,-38.000,-235.000, 38.000, 38.000,235.000]
    st.find_lvid_nodes  lvid 34 src N nodes.size 2
     nidx 65741
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 21409.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 21409.0000     1.0000.

     nidx 65743
    m2w
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -21312.0000     1.0000.

    gtd
    .
         0.9848    -0.1736     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
        -0.1736    -0.9848     0.0000     0.0000.
         0.0000     0.0000 -21312.0000     1.0000.

    (ok) A[blyth@localhost sysrap]$ 



    (ok) A[blyth@localhost sysrap]$ LVID=33 TEST=desc_solid ~/o/sysrap/tests/stree_load_test.sh
    stree::desc_solid lvid 33 lvn Waterdistributor_0 root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv  33 xf Y pa Y bb Y pt N nc 11 dp  0 tg co bb.desc [-100000.000,-100000.000,-100000.000,100000.000,100000.000,100000.000]
      1 : sn::brief tc  125 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  125 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
      1 : sn::brief tc  105 cm  0 lv  33 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cy bb.desc [-33.000,-33.000,-235.000, 33.000, 33.000,235.000]
    st.find_lvid_nodes  lvid 33 src N nodes.size 2
     nidx 65742
    m2w
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

    gtd
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

     nidx 65744
    m2w
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

    gtd
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.







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







