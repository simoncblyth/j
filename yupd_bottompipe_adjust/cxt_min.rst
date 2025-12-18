cxt_min.sh
==============



* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1062

After fixing a couple of Opticks transform related bugs that your geometry
additions revealed I have been taking a look at your cut tube subtractions.  

The solution is to overlap the two angled tubes that are subtracted to avoid 
the coincidence.

After fixing a couple of Opticks transform related bugs that your geometry
additions revealed I have been taking a look at the geometry at the bottom. 
The attached 2D opticks/simtrace cross section shows several spurious boundaries
caused by coincident faces.  I expect these issues will not cause much of a
problem however due to them being within Steel and being in the region between
the Tyvek reflectors where there are no PMTs.



An example of the problem is with sOuterReflectorInCD_TSubWaterDistributor_cutTube2
where the outer round bottom flask has two angled tubes subtracted. The problem
is that the two subtracted tubes have a coincident face which results in a phantom 
boundary between them. But because it is Steel it does not matter for optical photons.
This kind of issue can be easily fixed by slightly (eg 1mm z shift of one the 2nd tube) 
overlapping the two angled tubes that are subtracted to avoid the coincidence.

I investigated avoiding this councidence with the UNCOINCIDE_MM offset shown in:

https://github.com/simoncblyth/opticks/blob/master/u4/U4SolidMaker.cc#L2615











Seg legs
----------


::

    (ok) A[blyth@localhost tests]$ SID=0 ./CSGFoundryLoadTest.sh | grep Seg
    2330 : SMesh::descRange   mn [  -133.972    543.122 -19623.000 ] mx [    25.028    702.122 -18914.000 ] ce [   -54.472    622.622 -19268.500    354.500 ]  name[-]  lvid 129 so[LowerWaterDistributorSeg3_0] extent_diff      0.000
    2331 : SMesh::descRange   mn [  -666.808   -293.263 -19623.000 ] mx [  -507.808   -134.263 -18914.000 ] ce [  -587.308   -213.763 -19268.500    354.500 ]  name[-]  lvid 130 so[LowerWaterDistributorSeg3_1] extent_diff      0.000
    2332 : SMesh::descRange   mn [   184.636   -645.942 -19623.000 ] mx [   343.636   -486.942 -18914.000 ] ce [   264.136   -566.442 -19268.500    354.500 ]  name[-]  lvid 131 so[LowerWaterDistributorSeg3_2] extent_diff      0.000
    1014 : SMesh::descRange   mn [  -133.972    543.122 -20468.000 ] mx [    25.028    702.122 -19639.000 ] ce [   -54.472    622.622 -20053.500    414.500 ]  name[-]  lvid  76 so[LowerWaterDistributorSeg2_0] extent_diff      0.000
    1015 : SMesh::descRange   mn [  -666.808   -293.263 -20468.000 ] mx [  -507.808   -134.263 -19639.000 ] ce [  -587.308   -213.763 -20053.500    414.500 ]  name[-]  lvid  77 so[LowerWaterDistributorSeg2_1] extent_diff      0.000
    1016 : SMesh::descRange   mn [   184.636   -645.942 -20468.000 ] mx [   343.636   -486.942 -19639.000 ] ce [   264.136   -566.442 -20053.500    414.500 ]  name[-]  lvid  78 so[LowerWaterDistributorSeg2_2] extent_diff      0.000
     217 : SMesh::descRange   mn [  -204.472    472.622 -21750.000 ] mx [    95.528    772.622 -20484.000 ] ce [   -54.472    622.622 -21117.000    633.000 ]  name[-]  lvid  35 so[LowerWaterDistributorSeg1_0] extent_diff      0.000
     218 : SMesh::descRange   mn [  -737.308   -363.763 -21750.000 ] mx [  -437.308    -63.763 -20484.000 ] ce [  -587.308   -213.763 -21117.000    633.000 ]  name[-]  lvid  36 so[LowerWaterDistributorSeg1_1] extent_diff      0.000
     219 : SMesh::descRange   mn [   114.136   -716.442 -21750.000 ] mx [   414.136   -416.442 -20484.000 ] ce [   264.136   -566.442 -21117.000    633.000 ]  name[-]  lvid  37 so[LowerWaterDistributorSeg1_2] extent_diff      0.000



ok) A[blyth@localhost CSG]$ SID=0 tests/CSGFoundryLoadTest.sh | grep Seg
2330 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-19268.500,   354.500])  ; bb = np.array([  -133.972,   543.122,-19623.000,    25.028,   702.122,-18914.000])  # CSGPrim::descRangeNumPy  lvid 129 ridx    0 pidx  2330 so[LowerWaterDistributorSeg3_0]
2330 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-19268.500,   354.500])  ; bb = np.array([  -133.972,   543.122,-19623.000,    25.028,   702.122,-18914.000])  # SMesh::descRangeNumPy  name[-]  lvid 129 so[LowerWaterDistributorSeg3_0] extent_diff      0.000
2331 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-19268.500,   354.500])  ; bb = np.array([  -666.808,  -293.263,-19623.000,  -507.808,  -134.263,-18914.000])  # CSGPrim::descRangeNumPy  lvid 130 ridx    0 pidx  2331 so[LowerWaterDistributorSeg3_1]
2331 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-19268.500,   354.500])  ; bb = np.array([  -666.808,  -293.263,-19623.000,  -507.808,  -134.263,-18914.000])  # SMesh::descRangeNumPy  name[-]  lvid 130 so[LowerWaterDistributorSeg3_1] extent_diff      0.000
2332 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-19268.500,   354.500])  ; bb = np.array([   184.636,  -645.942,-19623.000,   343.636,  -486.942,-18914.000])  # CSGPrim::descRangeNumPy  lvid 131 ridx    0 pidx  2332 so[LowerWaterDistributorSeg3_2]
2332 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-19268.500,   354.500])  ; bb = np.array([   184.636,  -645.942,-19623.000,   343.636,  -486.942,-18914.000])  # SMesh::descRangeNumPy  name[-]  lvid 131 so[LowerWaterDistributorSeg3_2] extent_diff      0.000
1014 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-20053.500,   414.500])  ; bb = np.array([  -133.972,   543.122,-20468.000,    25.028,   702.122,-19639.000])  # CSGPrim::descRangeNumPy  lvid  76 ridx    0 pidx  1014 so[LowerWaterDistributorSeg2_0]
1014 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-20053.500,   414.500])  ; bb = np.array([  -133.972,   543.122,-20468.000,    25.028,   702.122,-19639.000])  # SMesh::descRangeNumPy  name[-]  lvid  76 so[LowerWaterDistributorSeg2_0] extent_diff      0.000
1015 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-20053.500,   414.500])  ; bb = np.array([  -666.808,  -293.263,-20468.000,  -507.808,  -134.263,-19639.000])  # CSGPrim::descRangeNumPy  lvid  77 ridx    0 pidx  1015 so[LowerWaterDistributorSeg2_1]
1015 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-20053.500,   414.500])  ; bb = np.array([  -666.808,  -293.263,-20468.000,  -507.808,  -134.263,-19639.000])  # SMesh::descRangeNumPy  name[-]  lvid  77 so[LowerWaterDistributorSeg2_1] extent_diff      0.000
1016 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-20053.500,   414.500])  ; bb = np.array([   184.636,  -645.942,-20468.000,   343.636,  -486.942,-19639.000])  # CSGPrim::descRangeNumPy  lvid  78 ridx    0 pidx  1016 so[LowerWaterDistributorSeg2_2]
1016 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-20053.500,   414.500])  ; bb = np.array([   184.636,  -645.942,-20468.000,   343.636,  -486.942,-19639.000])  # SMesh::descRangeNumPy  name[-]  lvid  78 so[LowerWaterDistributorSeg2_2] extent_diff      0.000
 217 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-21117.000,   633.000])  ; bb = np.array([  -204.472,   472.622,-21750.000,    95.528,   772.622,-20484.000])  # CSGPrim::descRangeNumPy  lvid  35 ridx    0 pidx   217 so[LowerWaterDistributorSeg1_0]
 217 : import numpy as np  ; ce = np.array([   -54.472,   622.622,-21117.000,   633.000])  ; bb = np.array([  -204.472,   472.622,-21750.000,    95.528,   772.622,-20484.000])  # SMesh::descRangeNumPy  name[-]  lvid  35 so[LowerWaterDistributorSeg1_0] extent_diff      0.000
 218 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-21117.000,   633.000])  ; bb = np.array([  -737.308,  -363.763,-21750.000,  -437.308,   -63.763,-20484.000])  # CSGPrim::descRangeNumPy  lvid  36 ridx    0 pidx   218 so[LowerWaterDistributorSeg1_1]
 218 : import numpy as np  ; ce = np.array([  -587.308,  -213.763,-21117.000,   633.000])  ; bb = np.array([  -737.308,  -363.763,-21750.000,  -437.308,   -63.763,-20484.000])  # SMesh::descRangeNumPy  name[-]  lvid  36 so[LowerWaterDistributorSeg1_1] extent_diff      0.000
 219 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-21117.000,   633.000])  ; bb = np.array([   114.136,  -716.442,-21750.000,   414.136,  -416.442,-20484.000])  # CSGPrim::descRangeNumPy  lvid  37 ridx    0 pidx   219 so[LowerWaterDistributorSeg1_2]
 219 : import numpy as np  ; ce = np.array([   264.136,  -566.442,-21117.000,   633.000])  ; bb = np.array([   114.136,  -716.442,-21750.000,   414.136,  -416.442,-20484.000])  # SMesh::descRangeNumPy  name[-]  lvid  37 so[LowerWaterDistributorSeg1_2] extent_diff      0.000
(ok) A[blyth@localhost CSG]$ 



    In [2]: bb = np.array([   184.636,  -645.942,-19623.000,   343.636,  -486.942,-18914.000])

    In [3]: bb[:3]
    Out[3]: array([   184.636,   -645.942, -19623.   ])

    In [4]: bb[3:]
    Out[4]: array([   343.636,   -486.942, -18914.   ])

    In [5]: (bb[:3] + bb[3:])/2
    Out[5]: array([   264.136,   -566.442, -19268.5  ])


    ce = np.array([   264.136,  -566.442,-19268.500,   354.500])




OPTICKS_EVENT_NAME=2dxy POINT=264.136,-566.442,0 cxt_min.sh pdb   ## succeeds to land a point in the middle of the xy view of the pipe

moi=264.136,-566.442,-20475,1500        # xy-middle-of-pipe z-outer-tyvek
    



    SimtracePlot.__call__ picked_point [ 218.654 -501.238    0.   ] pointId 15827 idx 42 k mediumblue label      mediumblue    31610                        Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_PhysLowerWaterDistSeg2//Steel$ ##  
    SimtracePlot.__call__ picked_point [ 218.654 -501.238    0.   ] pointId 15827 idx 42 k mediumblue label      mediumblue    31610                        Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_PhysLowerWaterDistSeg2//Steel$ ##  




Find the crucial Z positions of the tyvek::

    [CSGFoundry::comparePrimRange solidIdx 11 so.primOffset  2731 so.numPrim   338 mg YES
    [CSGPrim::Desc numPrim 338 mg_subs 338 EXTENT_DIFF :    200.000 [CSGPrim__DescRange_EXTENT_DIFF]
      11 : CSGPrim::descRange mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.000 ] ce [     0.000      0.000   1185.500  20814.500 ] lvid 333 ridx    0 pidx    11 so[sInnerWater_TSubWaterDistributor_cutTube2]
      10 : CSGPrim::descRange mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.000 ] ce [     0.000      0.000   1184.500  20815.500 ] lvid 334 ridx    0 pidx    10 so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2]
       9 : CSGPrim::descRange mn [-20474.000 -20474.000 -20474.000 ] mx [ 20474.000  20474.000  22000.000 ] ce [     0.000      0.000    763.000  21237.000 ] lvid 335 ridx    0 pidx     9 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2]
       8 : CSGPrim::descRange mn [-20476.000 -20476.000 -20476.000 ] mx [ 20476.000  20476.000  22000.000 ] ce [     0.000      0.000    762.000  21238.000 ] lvid 336 ridx    0 pidx     8 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2]
       0 : CSGPrim::descRange mn [  -727.052   -538.335  21683.797 ] mx [  -406.658   -255.495  22066.203 ] ce [  -566.855   -396.915  21875.000    191.203 ] lvid  29 ridx    0 pidx     0 so[ConnectingCutTube_0]
       1 : CSGPrim::descRange mn [   320.786   -661.030  21683.797 ] mx [   623.104   -351.170  22066.203 ] ce [   471.945   -506.100  21875.000    191.203 ] lvid  30 ridx    0 pidx     1 so[ConnectingCutTube_1]
       2 : CSGPrim::descRange mn [  -256.899    515.754  21683.795 ] mx [   -54.431    832.776  22066.205 ] ce [  -155.665    674.265


               -19630  
               -20475







Give colors to geometry at bottom of detector::

    [key_prim_regexp]
    white = sExpHall$
    blue = sOuterWaterPool$
    green = sTarget_T$
    yellow = sAcrylic_T$
    red = sOuterWaterInCD_TSubWaterDistributor$
    magenta = sOuterReflectorInCD_TSubWaterDistributor$
    pink = sDeadWater_shell$
    orange = sTyvek_shell$
    cyan = sInnerReflectorInCD_TSubWaterDistributor$
    crimson  = sInnerWater_TSubWaterDistributor$
    teal = sAirGap$
    plum = sAirTT$
    dodgerblue = sChimneyAcrylic$
    lightblue = sChimneyLS$
    turquoise = sChimneySteel$
    lightseagreen = sPlane$
    steelblue = sWall$
    darkmagenta = sWaterTube$
    azure = uni_acrylic1$
    powderblue = GLb.*$
    deeppink = Hama.*$
    orchid = NNVT.*$
    thistle = mask_PMT_20inch_vetosMask$
    indigo = mask_PMT_20inch_vetosMask_virtual$
    fuchsia = PMT_20inch_veto.*$
    tomato = PMT_3.*$
    cadetblue = PoolCoversub$
    lawngreen = Upper_Chimney$
    cornflowerblue = Upper_LS_tube$
    aquamarine = Upper_Steel_tube$
    hotpink = Waterdistributor_2$
    honeydew = Waterdistributor_3$
    darkcyan = Waterdistributor_0$
    darkorange = Waterdistributor_1$
    darkgoldenrod = sOuterWaterInCD_TSubWaterDistributor_cutTube2$
    darkgreen = sInnerReflectorInCD_TSubWaterDistributor_cutTube2$
    darkkhaki = sOuterReflectorInCD_TSubWaterDistributor_cutTube2$
    darkolivegreen = sInnerWater_TSubWaterDistributor_cutTube2$
    darkorchid = sBotChimneySSEnclosure_PartI_II_III$
    darkred = sBotChimneySSEnclosureLS_PartI_II_III$
    darksalmon = WaterDistributorPartIIIUnion$
    darkseagreen = LowerWaterDistributorSeg1_0$
    darkslateblue = LowerWaterDistributorSeg1_1$
    darkturquoise = LowerWaterDistributorSeg1_2$
    lavender = LowerWaterDistributorSeg2_0$
    lavenderblush = LowerWaterDistributorSeg2_1$
    lightskyblue = LowerWaterDistributorSeg2_2$
    lemonchiffon = LowerWaterDistributorSeg3_0$
    lightcoral = LowerWaterDistributorSeg3_1$
    lightcyan = LowerWaterDistributorSeg3_2$
    grey = 
    #
    #



PRIMTAB=1 KEY=darkgoldenrod,darkgreen,darkkhaki,darkolivegreen cxt_min.sh



PRIMTAB=1 KEY=darkgoldenrod cxt_min.sh


PRIMTAB=1 KEY=darkgreen cxt_min.sh
    sInnerReflectorInCD_TSubWaterDistributor_cutTube2
    big sphere with holes and angled tube sticking up



PRIMTAB=1 KEY=dark cxt_min.sh






Boundary Check 2D 
-------------------

    [key_boundary_regexp]
    red = (?P<Water_Virtuals>Water/.*/Water$)
    blue = Water///Acrylic$
    yellow = DeadWater/Implicit_RINDEX_NoRINDEX_pDeadWater_pTyvekFilm//Tyvek$
    orange = Water/Steel_surface//Steel$
    pink = Air/CDTyvekSurface//Tyvek$
    azure = Air///Water$
    salmon = Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD.*//LatticedShellSteel$
    tomato = Tyvek//CDInnerTyvekSurface/Water$

    cyan = Tyvek//Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pCentralDetector/Water$
    magenta = Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pInnerReflector//Tyvek$
    lawngreen = Tyvek//Implicit_RINDEX_NoRINDEX_pWaterPool_pTyvekFilm/vetoWater$
    lightcyan = Tyvek//Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pCentralDetector/Water$

    teal = Vacuum/NNVT.*//Steel$
    plum = Vacuum/Hama.*//Steel$
    deeppink = Pyrex/Hama.*/Vacuum$
    crimson = Pyrex/NNVT.*/Vacuum$
    dodgerblue = Pyrex/PMT_20.*/Vacuum$
    lightblue = Acrylic///LS$
    steelblue = Water/NNVTMaskOpticalSurface//CDReflectorSteel$
    skyblue = Water/HamamatsuMaskOpticalSurface//CDReflectorSteel$
    aquamarine = Water///AcrylicMask$
    powderblue = Water///Pyrex$
    cadetblue = Water/.*3inch.*/Steel$
    turquoise = Rock//Implicit_RINDEX_NoRINDEX_pExpHall_pExpRockBox/Air$
    lightseagreen = Air///Air$
    darkmagenta = Air/Implicit_RINDEX_NoRINDEX_pExpHall_pPoolCover//Steel$
    thistle = Steel//UpperChimneySteelSurface/LS$
    white = Black_HDPE//Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pPoolLining/Air
    orchid = Air/Implicit_RINDEX_NoRINDEX_lUpperChimney_phys_pUpperChimneySteel//Steel$
    cornflowerblue= Water///LS$
    darkorange = vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pWaterDistributorPartIIIUnion//Steel$
    lightcoral = vetoWater/VETOTyvekSurface//Tyvek$
    honeydew = vetoWater/CDTyvekSurface//Tyvek$
    darkred = Steel//Implicit_RINDEX_NoRINDEX_pBotChimneySSEnclosureLogicalLS_pBotChimneySSEnclosure/LS$
    darksalmon = Water/Implicit_RINDEX_NoRINDEX_pInnerWater_pBotChimneySSEnclosure//Steel$
    darkseagreen = vetoWater///Water$
    darkslateblue = vetoWater/PVDFSkinSurface_0/PVDFSkinSurface_0/PVDF$
    darkturquoise = Water/PVDFSkinSurface_1/PVDFSkinSurface_1/PVDF$
    lavender = Black_HDPE//Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pPoolLining/vetoWater$
    lavenderblush = vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.B05_B05_HBeam_phys//LatticedShellSteel$
    lightskyblue = Acrylic/LowerChimneySteelSkinSurface//Steel$
    darkolivegreen = vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_ZC2.A05_A05_HBeam_phys//LatticedShellSteel$
    grey =   
    #


::

    KEY=cyan,magenta,lawngreen,lightcyan cxt_min.sh pdb





::

    KEY=lavender,lightcoral,darkslateblue cxt_min.sh pdb


::

    [cf.btab KEY:lavender,lightcoral,darkslateblue
                     .akk :   .u       .c       .x : .n 
               lightcoral :   34    85991        0 : vetoWater/VETOTyvekSurface//Tyvek                                                ## THE BIG CYLINDER
            darkslateblue :   38    16111     1001 : vetoWater/PVDFSkinSurface_0/PVDFSkinSurface_0/PVDF                               ## WATER DISTRIB CIRCLES
                 lavender :   31     9437        1 : Black_HDPE//Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pPoolLining/vetoWater       ## OUTSIDE BIG CYLINDER 
                     .akk :   .u       .c       .x : .n 
                          :        111539          : .ctot 
    ]cf.btab


::

    KEY=lavender,lightcoral,darkslateblue,darkorange cxt_min.sh pdb   ## curly snake appears

          darkorange :   37   104790     1004 : vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pWaterDistributorPartIIIUnion//Steel     ## THE CURLY SNAKE
           lightcoral :   34    85991        0 : vetoWater/VETOTyvekSurface//Tyvek 
        darkslateblue :   38    16111     1001 : vetoWater/PVDFSkinSurface_0/PVDFSkinSurface_0/PVDF 
             lavender :   31     9437        1 : Black_HDPE//Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pPoolLining/vetoWater 
                 .akk :   .u       .c       .x : .n 



     KEY=lightcyan,darkorange cxt_min.sh pdb

     KEY=magenta,lightcyan,darkorange cxt_min.sh pdb
            the curly traversing the two            

     KEY=cyan cxt_min.sh pdb

     KEY=cyan,magenta,lightcyan,darkorange cxt_min.sh pdb



This captures the gross boundaries::

    KEY=cyan,magenta,lightcyan,darkorange,tomato,honeydew cxt_min.sh pdb

    [cf.btab KEY:cyan,magenta,lightcyan,darkorange,tomato,honeydew
                     .akk :   .u       .c       .x : .n 
               darkorange :   37   104790     1004 : vetoWater/Implicit_RINDEX_NoRINDEX_pOuterWaterPool_pWaterDistributorPartIIIUnion//Steel 
                  magenta :  125    47745    13002 : Water/Implicit_RINDEX_NoRINDEX_pOuterWaterInCD_pInnerReflector//Tyvek 
                 honeydew :   76    47720     1014 : vetoWater/CDTyvekSurface//Tyvek 
                   tomato :  126    46442    22004 : Tyvek//CDInnerTyvekSurface/Water 
                     .akk :   .u       .c       .x : .n 
                          :        246697          : .ctot 
    ]cf.btab

Make the normals visible::

    KEY=cyan,magenta,lightcyan,darkorange,tomato,honeydew NORMAL=1 NORMAL_FILTER=500 cxt_min.sh pdb


    XKEY=cyan,magenta,lightcyan,darkorange,tomato,honeydew KEY=darkorange,honeydew,lightcyan NORMAL=1 NORMAL_FILTER=100 cxt_min.sh pdb



PRIMTAB darkgreen,darksalmon coincident potential::

    PRIMTAB=1 NORMAL=1 NORMAL_FILTER=100 X=darkgoldenrod,darksalmon X=darkgreen,darkkhaki,darkolivegreen,darksalmon KEY=darkgreen,darksalmon GSGRID=1 cxt_min.sh pdb

     darkgreen   538032 sInnerReflectorInCD_TSubWaterDistributor_cutTube2$
     darksalmon    74228 WaterDistributorPartIIIUnion$




::

    A[blyth@localhost CSG]$ jgr sInnerReflectorInCD_TSubWaterDistributor_cutTube2
    A[blyth@localhost junosw]$ jgr sInnerReflectorInCD
    ./Examples/Tutorial/share/opticks_juno.sh:   local pfxs="sInnerWater sInnerReflectorInCD sOuterWaterInCD sOuterReflectorInCD"
    ./Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc:    RoundBottomFlaskSolidMaker rbfs("sInnerReflectorInCD",
    A[blyth@localhost junosw]$ 



* solid flask of Tyvek



::

     654 void
     655 DetSim1Construction::makeInnerReflectorLogical() {
     656     RoundBottomFlaskSolidMaker rbfs("sInnerReflectorInCD",
     657                                     m_radInnerReflector,             // 
     658                                     m_radReflectorChimney,      // 
     659                                     m_heightWP/2 + m_waterPoolHeightplus,
     660                                     m_radReflectorBotChimney,   //
     661                                     m_ChimneyBotToCenter, // todo
     662                                     TOPTOEQUATORH,
     663                                     BOTTOEQUATORH);
     664     solidInnerReflector = rbfs.getSolid();
     665     solidInnerReflector = helper_subtract_water_distributor(solidInnerReflector);
     666 
     667     logicInnerReflector = new G4LogicalVolume(solidInnerReflector,
     668                                          Tyvek,
     669                                          "lInnerReflectorInCD",
     670                                          0,
     671                                          0,
     672                                          0);
     673     G4VisAttributes* visatt = new G4VisAttributes(G4Colour(0.5, 0., 0.5));
     674     visatt -> SetForceWireframe(true);
     675     visatt -> SetForceAuxEdgeVisible(true);
     676     //visatt -> SetForceSolid(true);
     677     //visatt -> SetForceLineSegmentsPerCircle(4);
     678     logicInnerReflector -> SetVisAttributes(visatt);
     679 
     680 }


     531 G4VSolid*
     532 DetSim1Construction::helper_subtract_water_distributor(G4VSolid* solid_input) {
     533     G4VSolid* solid_output = solid_input;
     534     G4String name = solid_input->GetName() + "SubWaterDistributor";
     535 
     536     // need to subtract the lower water distributor (only if not using segmented method)
     537     if (!m_use_segmented_water_distributor) {
     538         LogInfo << "Subtracting the lower water distributor from the solid: " << solid_input->GetName() << std::endl;
     539         double r_bottom = 150*mm;
     540         double h_bottom = 20*mm;
     541         double r_outer = 159./2*mm;
     542         double h = 2836*mm;
     543         auto solidWaterDistributorII = new G4Polycone("solidWaterDistributorIISub",
     544                                     0,
     545                                     360*deg,
     546                                     4, //G4int         numZPlanes,
     547                                     new G4double[4]{-h, -(h-h_bottom), -(h-h_bottom), 0}, //const G4double  zPlane[],
     548                                     new G4double[4]{0., 0., 0., 0.}, //const G4double  rInner[],
     549                                     new G4double[4]{r_bottom, r_bottom, r_outer, r_outer} //const G4double  rOuter[]
     550                                 );
     551         double r = 1250*mm/2;
     552         double thetas[] = {95.*deg, 200.*deg, 295*deg};
     553         double z = m_heightWP/2 - h;
     554 
     555         for (int i = 0; i < 3; ++i) {
     556             double theta = thetas[i];
     557             double x = r * cos(theta);
     558             double y = r * sin(theta);
     559             solid_output = new G4SubtractionSolid(name,
     560                                                     solid_input,
     561                                                     solidWaterDistributorII,
     562                                                     0,
     563                                                     G4ThreeVector(x, y, -z));
     564         }
     565     }
     566 
     567     // ==== New: Subtract two inclined cutTubes of lower water distributor ====
     568     auto cutTubes = WaterdistributorpipeMaker::MakeLowerWaterDistributorCurvedCutTubes(m_lowerchimney_rotangle);
     569 
     570     for (size_t i = 0; i < cutTubes.size(); ++i) {
     571         const auto& tube = cutTubes[i];
     572         G4Transform3D transform(tube.rot, tube.pos);
     573 
     574         solid_output = new G4SubtractionSolid(
     575             name + "_cutTube" + std::to_string(i+1),
     576             solid_output,
     577             tube.solid,
     578             transform
     579         );
     580     }
     581 
     582     return solid_output;
     583 }


::

    (ok) A[blyth@localhost CSGFoundry]$ grep SubWaterDistributor meshname.txt 
    sInnerWater_TSubWaterDistributor_cutTube2
    sInnerReflectorInCD_TSubWaterDistributor_cutTube2
    sOuterWaterInCD_TSubWaterDistributor_cutTube2
    sOuterReflectorInCD_TSubWaterDistributor_cutTube2
    (ok) A[blyth@localhost CSGFoundry]$ 


            sInnerWater_TSubWaterDistributor_cutTube2
    sInnerReflectorInCD_TSubWaterDistributor_cutTube2
        sOuterWaterInCD_TSubWaterDistributor_cutTube2
    sOuterReflectorInCD_TSubWaterDistributor_cutTube2
 



::

    CSGFoundry::comparePrimRange solidIdx 11 so.primOffset  2731 so.numPrim   338 mg YES
    [CSGPrim::Desc numPrim 338 mg_subs 338 EXTENT_DIFF :    200.000 [CSGPrim__DescRange_EXTENT_DIFF]
      10 : CSGPrim::descRange mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.000 ] ce [     0.000      0.000   1184.500  20815.500 ] lvid 334 ridx    0 pidx    10 so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2]
      10 : SMesh::descRange   mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.041 ] ce [     0.000      0.000   1184.521  20815.520 ] lvid 334                      so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2] extent_diff      0.020
      11 : CSGPrim::descRange mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.000 ] ce [     0.000      0.000   1185.500  20814.500 ] lvid 333 ridx    0 pidx    11 so[sInnerWater_TSubWaterDistributor_cutTube2]
      11 : SMesh::descRange   mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.041 ] ce [     0.000      0.000   1185.521  20814.520 ] lvid 333                      so[sInnerWater_TSubWaterDistributor_cutTube2] extent_diff      0.020
       8 : CSGPrim::descRange mn [-20476.000 -20476.000 -20476.000 ] mx [ 20476.000  20476.000  22000.000 ] ce [     0.000      0.000    762.000  21238.000 ] lvid 336 ridx    0 pidx     8 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2]
       8 : SMesh::descRange   mn [-20476.000 -20476.000 -20475.582 ] mx [ 20476.000  20476.000  22000.025 ] ce [     0.000      0.000    762.222  21237.805 ]  name[-]  lvid 336 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2] extent_diff     -0.195
       9 : CSGPrim::descRange mn [-20474.000 -20474.000 -20474.000 ] mx [ 20474.000  20474.000  22000.000 ] ce [     0.000      0.000    763.000  21237.000 ] lvid 335 ridx    0 pidx     9 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2]
       9 : SMesh::descRange   mn [-20474.000 -20474.000 -20473.582 ] mx [ 20474.000  20474.000  22000.025 ] ce [     0.000      0.000    763.222  21236.805 ]  name[-]  lvid 335 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2] extent_diff     -0.195
       0 : CSGPrim::descRange mn [  -727.052   -538.335  21683.797 ] mx [  -406.658   -255.495  22066.203 ] ce [  -566.855   -396.915  21875.000    191.203 ] lvid  29 ridx    0 pidx     0 so[ConnectingCutTube_0]
       0 : SMesh::descRange   mn [  -698.234   -508.169  21750.000 ] mx [  -435.476   -285.661  22000.000 ] ce [  -566.855   -396.915  21875.000    131.379 ]  name[-]  lvid  29 so[ConnectingCutTube_0] extent_diff    -59.824
       1 : CSGPrim::descRange mn [   320.786   -661.030  21683.797 ] mx [   623.104   -351.170  22066.203 ] ce [   471.945   -506.100  21875.000    191.203 ] lvid  30 ridx    0 pidx     1 so[ConnectingCutTube_1]
       1 : SMesh::descRange   mn [   351.675   -630.004  21750.000 ] mx [   592.215   -382.196  22000.000 ] ce [   471.945   -506.100  21875.000    125.000 ]  name[-]  lvid  30 so[ConnectingCutTube_1] extent_diff    -66.203
       2 : CSGPrim::descRange mn [  -256.899    515.754  21683.795 ] mx [   -54.431    832.776  22066.205 ] ce [  -155.665    674.265  21875.000    191.205 ] lvid  31 ridx    0 pidx     2 so[ConnectingCutTube_2]
       2 : SMesh::descRange   mn [  -241.315    530.078  21750.000 ] mx [   -70.015    818.452  22000.000 ] ce [  -155.665    674.265  21875.000    144.187 ]  name[-]  lvid  31 so[ConnectingCutTube_2] extent_diff    -47.018
       4 : CSGPrim::descRange mn [ -1225.791  -1225.791  21174.000 ] mx [  1225.791   1225.791  21644.000 ] ce [     0.000      0.000  21409.000   1225.791 ] lvid  34 ridx    0 pidx     4 so[Waterdistributor_1]
       4 : SMesh::descRange   mn [ -1342.054  -1342.032  21136.018 ] mx [  1342.070   1342.071  21681.975 ] ce [     0.008      0.020  21408.996   1342.062 ]  name[-]  lvid  34 so[Waterdistributor_1] extent_diff    116.271
       5 : CSGPrim::descRange mn [ -1219.998  -1219.998  21174.000 ] mx [  1219.998   1219.998  21644.000 ] ce [     0.000      0.000  21409.000   1219.998 ] lvid  33 ridx    0 pidx     5 so[Waterdistributor_0]
       5 : SMesh::descRange   mn [ -1336.770  -1336.749  21141.018 ] mx [  1336.786   1336.788  21676.975 ] ce [     0.008      0.019  21408.996   1336.778 ]  name[-]  lvid  33 so[Waterdistributor_0] extent_diff    116.780
      12 : CSGPrim::descRange mn [ -1225.791  -1225.791  18700.000 ] mx [  1225.791   1225.791  19170.000 ] ce [     0.000      0.000  18935.000   1225.791 ] lvid 125 ridx    0 pidx    12 so[Waterdistributor_3]
      12 : SMesh::descRange   mn [ -1342.054  -1342.032  18662.018 ] mx [  1342.070   1342.071  19207.975 ] ce [     0.008      0.020  18934.996   1342.062 ]  name[-]  lvid 125 so[Waterdistributor_3] extent_diff    116.271
      13 : CSGPrim::descRange mn [ -1219.998  -1219.998  18700.000 ] mx [  1219.998   1219.998  19170.000 ] ce [     0.000      0.000  18935.000   1219.998 ] lvid 124 ridx    0 pidx    13 so[Waterdistributor_2]
      13 : SMesh::descRange   mn [ -1336.770  -1336.749  18667.018 ] mx [  1336.786   1336.788  19202.975 ] ce [     0.008      0.019  18934.996   1336.778 ]  name[-]  lvid 124 so[Waterdistributor_2] extent_diff    116.780
     182 : CSGPrim::descRange mn [ -2470.439    514.747  17278.676 ] mx [  -334.919   3739.801  17855.316 ] ce [ -1402.679   2127.274  17566.996   1612.527 ] lvid 178 ridx    0 pidx   182 so[sSurftube_0V1_0]
     182 : SMesh::descRange   mn [ -2469.234    515.017  17278.676 ] mx [  -335.100   3738.175  17855.316 ] ce [ -1402.167   2126.596  17566.996   1611.579 ]  name[-]  lvid 178 so[sSurftube_0V1_0] extent_diff     -0.948
     260 : CSGPrim::descRange mn [  -212.439  -4469.167  17278.676 ] mx [   -18.739   -621.783  17855.316 ] ce [  -115.589  -2545.475  17566.996   1923.692 ] lvid 256 ridx    0 pidx   260 so[sSurftube_0V1_1]







