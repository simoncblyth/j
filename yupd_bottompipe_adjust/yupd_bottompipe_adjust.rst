yupd_bottompipe_adjust
=======================





WaterdistributorpipeMaker
-----------------------------


solid:WaterDistributorPipeInner
    WaterdistributorpipeMaker::MakeStraightPipePartI  

solid:WaterDistributorPipeOuter
    WaterdistributorpipeMaker::MakeStraightPipePartII

solid:WaterDistributorPipePartIII
    WaterdistributorpipeMaker::MakeStraightPipePartIII

solid:ConnectingCutTube
    WaterdistributorpipeMaker::MakeConnectingCutTubes

solid:AirGapWaterDistributorPipe
    WaterdistributorpipeMaker::MakeAirGapWaterDistributorPipe

solid:solidWaterDistributorIIInner,solidWaterDistributorII
    WaterdistributorpipeMaker::MakeWaterDistributorPolycone

solid:sBotChimneySSEnclosure_Flange,CutTube1,CutTube2,torus1,torus2,WaterDistributorPartIIIUnion
   WaterdistributorpipeMaker::MakeWaterDistributorPartIIIUnion







CompareRanges : show that WaterDistributorPartIIIUnion is exceptional
-----------------------------------------------------------------------

::

    CSGFoundryLoadTest::CompareRanges 
     num_solid 12 solidIdx 11 tr YES sc YES mg YES
    [CSGFoundry::comparePrimRange solidIdx 11 so.primOffset  2731 so.numPrim   338 mg YES
    [CSGPrim::Desc numPrim 338 mg_subs 338
       0 : CSGPrim::descRange mn [  -727.052   -538.335  21683.797 ] mx [  -406.658   -255.495  22066.203 ] ce [  -566.855   -396.915  21875.000    191.203 ] lvid  29 ridx    0 pidx     0 so[ConnectingCutTube_0]
       0 : SMesh::descRange   mn [  -698.234   -508.169  21750.000 ] mx [  -435.476   -285.661  22000.000 ] ce [  -566.855   -396.915  21875.000    131.379 ]  name[-]  lvid  29 so[ConnectingCutTube_0] extent_diff    -59.824
       1 : CSGPrim::descRange mn [   320.786   -661.030  21683.797 ] mx [   623.104   -351.170  22066.203 ] ce [   471.945   -506.100  21875.000    191.203 ] lvid  30 ridx    0 pidx     1 so[ConnectingCutTube_1]
       1 : SMesh::descRange   mn [   351.675   -630.004  21750.000 ] mx [   592.215   -382.196  22000.000 ] ce [   471.945   -506.100  21875.000    125.000 ]  name[-]  lvid  30 so[ConnectingCutTube_1] extent_diff    -66.203
       2 : CSGPrim::descRange mn [  -256.899    515.754  21683.795 ] mx [   -54.431    832.776  22066.205 ] ce [  -155.665    674.265  21875.000    191.205 ] lvid  31 ridx    0 pidx     2 so[ConnectingCutTube_2]
       2 : SMesh::descRange   mn [  -241.315    530.078  21750.000 ] mx [   -70.015    818.452  22000.000 ] ce [  -155.665    674.265  21875.000    144.187 ]  name[-]  lvid  31 so[ConnectingCutTube_2] extent_diff    -47.018

       3 : CSGPrim::descRange mn [ -9103.062 -20790.500 -19998.969 ] mx [  5702.666  21247.500    418.500 ] ce [ -1700.198    228.500  -9790.234  21019.000 ] lvid  32 ridx    0 pidx     3 so[WaterDistributorPartIIIUnion]
       3 : SMesh::descRange   mn [  -661.993   -125.000 -21073.482 ] mx [   136.645    125.000 -19120.000 ] ce [  -262.674      0.000 -20096.742    976.741 ]  name[-]  lvid  32 so[WaterDistributorPartIIIUnion] extent_diff -20042.258

MOI=0,0,-20000,1000


       4 : CSGPrim::descRange mn [ -1225.791   -252.399  19974.000 ] mx [  1225.791    252.399  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  34 ridx    0 pidx     4 so[Waterdistributor_1]
       4 : SMesh::descRange   mn [ -1342.054  -1342.032  21136.018 ] mx [  1342.070   1342.071  21681.975 ] ce [     0.008      0.020  21408.996   1342.062 ]  name[-]  lvid  34 so[Waterdistributor_1] extent_diff    -92.938
       5 : CSGPrim::descRange mn [ -1219.998   -246.607  19974.000 ] mx [  1219.998    246.607  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  33 ridx    0 pidx     5 so[Waterdistributor_0]
       5 : SMesh::descRange   mn [ -1336.770  -1336.749  21141.018 ] mx [  1336.786   1336.788  21676.975 ] ce [     0.008      0.019  21408.996   1336.778 ]  name[-]  lvid  33 so[Waterdistributor_0] extent_diff    -98.222
       6 : CSGPrim::descRange mn [ -1225.791   -252.399 -22747.000 ] mx [  1225.791    252.399 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  34 ridx    0 pidx     6 so[Waterdistributor_1]
       6 : SMesh::descRange   mn [ -1342.054  -1342.032 -21584.982 ] mx [  1342.070   1342.071 -21039.025 ] ce [     0.008      0.020 -21312.004   1342.062 ]  name[-]  lvid  34 so[Waterdistributor_1] extent_diff    -92.938
       7 : CSGPrim::descRange mn [ -1219.998   -246.607 -22747.000 ] mx [  1219.998    246.607 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  33 ridx    0 pidx     7 so[Waterdistributor_0]
       7 : SMesh::descRange   mn [ -1336.770  -1336.749 -21579.982 ] mx [  1336.786   1336.788 -21044.025 ] ce [     0.008      0.019 -21312.004   1336.778 ]  name[-]  lvid  33 so[Waterdistributor_0] extent_diff    -98.222
       8 : CSGPrim::descRange mn [-20476.000 -20476.000 -20476.000 ] mx [ 20476.000  20476.000  22000.000 ] ce [     0.000      0.000    762.000  21238.000 ] lvid 336 ridx    0 pidx     8 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2]
       8 : SMesh::descRange   mn [-20476.000 -20476.000 -20475.582 ] mx [ 20476.000  20476.000  22000.025 ] ce [     0.000      0.000    762.222  21237.805 ]  name[-]  lvid 336 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2] extent_diff     -0.195
       9 : CSGPrim::descRange mn [-20474.000 -20474.000 -20474.000 ] mx [ 20474.000  20474.000  22000.000 ] ce [     0.000      0.000    763.000  21237.000 ] lvid 335 ridx    0 pidx     9 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2]
       9 : SMesh::descRange   mn [-20474.000 -20474.000 -20473.582 ] mx [ 20474.000  20474.000  22000.025 ] ce [     0.000      0.000    763.222  21236.805 ]  name[-]  lvid 335 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2] extent_diff     -0.195
      10 : CSGPrim::descRange mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.000 ] ce [     0.000      0.000   1184.500  20815.500 ] lvid 334 ridx    0 pidx    10 so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2]
      10 : SMesh::descRange   mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.041 ] ce [     0.000      0.000   1184.521  20815.520 ]  name[-]  lvid 334 so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2] extent_diff      0.020
      11 : CSGPrim::descRange mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.000 ] ce [     0.000      0.000   1185.500  20814.500 ] lvid 333 ridx    0 pidx    11 so[sInnerWater_TSubWaterDistributor_cutTube2]
      11 : SMesh::descRange   mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.041 ] ce [     0.000      0.000   1185.521  20814.520 ]  name[-]  lvid 333 so[sInnerWater_TSubWaterDistributor_cutTube2] extent_diff      0.020
      12 : CSGPrim::descRange mn [ -1225.791   -252.399  17500.000 ] mx [  1225.791    252.399  20370.000 ] ce [     0.000      0.000  18935.000   1435.000 ] lvid 125 ridx    0 pidx    12 so[Waterdistributor_3]
      12 : SMesh::descRange   mn [ -1342.054  -1342.032  18662.018 ] mx [  1342.070   1342.071  19207.975 ] ce [     0.008      0.020  18934.996   1342.062 ]  name[-]  lvid 125 so[Waterdistributor_3] extent_diff    -92.938
      13 : CSGPrim::descRange mn [ -1219.998   -246.607  17500.000 ] mx [  1219.998    246.607  20370.000 ] ce [     0.000      0.000  18935.000   1435.000 ] lvid 124 ridx    0 pidx    13 so[Waterdistributor_2]
      13 : SMesh::descRange   mn [ -1336.770  -1336.749  18667.018 ] mx [  1336.786   1336.788  19202.975 ] ce [     0.008      0.019  18934.996   1336.778 ]  name[-]  lvid 124 so[Waterdistributor_2] extent_diff    -98.222
      14 : CSGPrim::descRange mn [ -1225.791   -252.399 -20273.000 ] mx [  1225.791    252.399 -17403.000 ] ce [     0.000      0.000 -18838.000   1435.000 ] lvid 125 ridx    0 pidx    14 so[Waterdistributor_3]
      14 : SMesh::descRange   mn [ -1342.054  -1342.032 -19110.982 ] mx [  1342.070   1342.071 -18565.025 ] ce [     0.008      0.020 -18838.004   1342.062 ]  name[-]  lvid 125 so[Waterdistributor_3] extent_diff    -92.938
      15 : CSGPrim::descRange mn [ -1219.998   -246.607 -20273.000 ] mx [  1219.998    246.607 -17403.000 ] ce [     0.000      0.000 -18838.000   1435.000 ] lvid 124 ridx    0 pidx    15 so[Waterdistributor_2]
      15 : SMesh::descRange   mn [ -1336.770  -1336.749 -19105.982 ] mx [  1336.786   1336.788 -18570.025 ] ce [     0.008      0.019 -18838.004   1336.778 ]  name[-]  lvid 124 so[Waterdistributor_2] extent_diff    -98.222
      16 : CSGPrim::descRange mn [   -60.000 -12773.921  12245.275 ] mx [    60.000 -12683.368  12338.543 ] ce [     0.000 -12728.645  12291.909     60.000 ] lvid 132 ridx    0 pidx    16 so[solidSJCLSanchor]
      16 : SMesh::descRange   mn [   -60.000 -12773.921  12252.222 ] mx [    60.000 -12690.562  12338.543 ] ce [     0.000 -12732.241  12295.383     60.000 ]  name[-]  lvid 132 so[solidSJCLSanchor] extent_diff      0.000
      17 : CSGPrim::descRange mn [   -60.000  17145.771   4221.356 ] mx [    60.000  17188.650   4340.210 ] ce [     0.000  17167.211   4280.783     60.000 ] lvid 132 ridx    0 pidx    17 so[solidSJCLSanchor]
      17 : SMesh::descRange   mn [   -60.000  17145.770   4223.775 ] mx [    60.000  17188.650   4340.210 ] ce [     0.000  17167.211   4281.993     60.000 ]  name[-]  lvid 132 so[solidSJCLSanchor] extent_diff      0.000



::

    2025-12-15 20:00:58.157 INFO  [2717854] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest 301158ef96cbf4d61f96ed76aee59990 dynamic 301158ef96cbf4d61f96ed76aee59990
    [CSGFoundryLoadTest::CompareRanges 
     num_solid 12 solidIdx 11 tr YES sc YES mg YES
    [CSGFoundry::comparePrimRange solidIdx 11 so.primOffset  2731 so.numPrim   338 mg YES
    [CSGPrim::Desc numPrim 338 mg_subs 338
       0 : CSGPrim::descRange mn [  -727.052   -538.335  21683.797 ] mx [  -406.658   -255.495  22066.203 ] ce [  -566.855   -396.915  21875.000    191.203 ] lvid  29 ridx    0 pidx     0 so[ConnectingCutTube_0]
       0 : SMesh::descRange   mn [  -698.234   -508.169  21750.000 ] mx [  -435.476   -285.661  22000.000 ] ce [  -566.855   -396.915  21875.000    131.379 ]  name[-]  lvid  29 so[ConnectingCutTube_0] extent_diff    -59.824
       1 : CSGPrim::descRange mn [   320.786   -661.030  21683.797 ] mx [   623.104   -351.170  22066.203 ] ce [   471.945   -506.100  21875.000    191.203 ] lvid  30 ridx    0 pidx     1 so[ConnectingCutTube_1]
       1 : SMesh::descRange   mn [   351.675   -630.004  21750.000 ] mx [   592.215   -382.196  22000.000 ] ce [   471.945   -506.100  21875.000    125.000 ]  name[-]  lvid  30 so[ConnectingCutTube_1] extent_diff    -66.203
       2 : CSGPrim::descRange mn [  -256.899    515.754  21683.795 ] mx [   -54.431    832.776  22066.205 ] ce [  -155.665    674.265  21875.000    191.205 ] lvid  31 ridx    0 pidx     2 so[ConnectingCutTube_2]
       2 : SMesh::descRange   mn [  -241.315    530.078  21750.000 ] mx [   -70.015    818.452  22000.000 ] ce [  -155.665    674.265  21875.000    144.187 ]  name[-]  lvid  31 so[ConnectingCutTube_2] extent_diff    -47.018
       3 : CSGPrim::descRange mn [ -9103.062 -20790.500 -19998.969 ] mx [  5702.666  21247.500    418.500 ] ce [ -1700.198    228.500  -9790.234  21019.000 ] lvid  32 ridx    0 pidx     3 so[WaterDistributorPartIIIUnion]
       3 : SMesh::descRange   mn [  -661.993   -125.000 -21073.482 ] mx [   136.645    125.000 -19120.000 ] ce [  -262.674      0.000 -20096.742    976.741 ]  name[-]  lvid  32 so[WaterDistributorPartIIIUnion] extent_diff -20042.258
     LARGE extent_diff -20042.258
     sub_tr0
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000     0.0000     1.0000.

     sub_loaddir [/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/scene/meshgroup/11/3]
       4 : CSGPrim::descRange mn [ -1225.791   -252.399  19974.000 ] mx [  1225.791    252.399  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  34 ridx    0 pidx     4 so[Waterdistributor_1]
       4 : SMesh::descRange   mn [ -1342.054  -1342.032  21136.018 ] mx [  1342.070   1342.071  21681.975 ] ce [     0.008      0.020  21408.996   1342.062 ]  name[-]  lvid  34 so[Waterdistributor_1] extent_diff    -92.938
       5 : CSGPrim::descRange mn [ -1219.998   -246.607  19974.000 ] mx [  1219.998    246.607  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  33 ridx    0 pidx     5 so[Waterdistributor_0]
       5 : SMesh::descRange   mn [ -1336.770  -1336.749  21141.018 ] mx [  1336.786   1336.788  21676.975 ] ce [     0.008      0.019  21408.996   1336.778 ]  name[-]  lvid  33 so[Waterdistributor_0] extent_diff    -98.222
       6 : CSGPrim::descRange mn [ -1225.791   -252.399 -22747.000 ] mx [  1225.791    252.399 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  34 ridx    0 pidx     6 so[Waterdistributor_1]
       6 : SMesh::descRange   mn [ -1342.054  -1342.032 -21584.982 ] mx [  1342.070   1342.071 -21039.025 ] ce [     0.008      0.020 -21312.004   1342.062 ]  name[-]  lvid  34 so[Waterdistributor_1] extent_diff    -92.938
       7 : CSGPrim::descRange mn [ -1219.998   -246.607 -22747.000 ] mx [  1219.998    246.607 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  33 ridx    0 pidx     7 so[Waterdistributor_0]
       7 : SMesh::descRange   mn [ -1336.770  -1336.749 -21579.982 ] mx [  1336.786   1336.788 -21044.025 ] ce [     0.008      0.019 -21312.004   1336.778 ]  name[-]  lvid  33 so[Waterdistributor_0] extent_diff    -98.222




HMM the vertices are enormously offset to -ve Z::

    In [1]: f.vtx
    Out[1]:
    array([[   125.   ,      0.   , -19120.   ],
           [   120.741,     32.352, -19120.   ],
           [   108.253,     62.5  , -19120.   ],
           [    88.388,     88.388, -19120.   ],
           [    62.5  ,    108.253, -19120.   ],
           ...,
           [  -384.395,     47.018, -20895.363],
           [  -391.006,     54.191, -20901.973],
           [  -394.134,     57.586, -20905.102],
           [  -401.409,     61.847, -20912.377],
           [  -405.475,     64.229, -20916.443]], shape=(592, 3), dtype=float32)

    In [2]: f.vtx.min()
    Out[2]: np.float32(-21073.482)

    In [3]: f.vtx.min(axis=0)
    Out[3]: array([  -661.993,   -125.   , -21073.482], dtype=float32)

    In [4]: f.vtx.max(axis=0)
    Out[4]: array([   136.645,    125.   , -19120.   ], dtype=float32)

    In [5]: pwd
    Out[5]: '/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/scene/meshgroup/11/3'







Improved SScene::descRanges
------------------------------

::


    mm[10]
    SMesh::descRange name[10]  lvid  -1 mn [  -253.746   -253.746   -173.226 ] mx [   253.746    253.746    184.001 ] ce [     0.000      0.000      5.388    253.746 ]
    mg[11]
    [SMeshGroup::descRange num_subs 338
       0 : SMesh::descRange name[-]  lvid  29 mn [  -698.234   -508.169  21750.000 ] mx [  -435.476   -285.661  22000.000 ] ce [  -566.855   -396.915  21875.000    131.379 ] so[ConnectingCutTube_0]
       1 : SMesh::descRange name[-]  lvid  30 mn [   351.675   -630.004  21750.000 ] mx [   592.215   -382.196  22000.000 ] ce [   471.945   -506.100  21875.000    125.000 ] so[ConnectingCutTube_1]
       2 : SMesh::descRange name[-]  lvid  31 mn [  -241.315    530.078  21750.000 ] mx [   -70.015    818.452  22000.000 ] ce [  -155.665    674.265  21875.000    144.187 ] so[ConnectingCutTube_2]
       3 : SMesh::descRange name[-]  lvid  32 mn [  -661.993   -125.000 -21073.482 ] mx [   136.645    125.000 -19120.000 ] ce [  -262.674      0.000 -20096.742    976.741 ] so[WaterDistributorPartIIIUnion]
       4 : SMesh::descRange name[-]  lvid  34 mn [ -1342.054  -1342.032  21136.018 ] mx [  1342.070   1342.071  21681.975 ] ce [     0.008      0.020  21408.996   1342.062 ] so[Waterdistributor_1]
       5 : SMesh::descRange name[-]  lvid  33 mn [ -1336.770  -1336.749  21141.018 ] mx [  1336.786   1336.788  21676.975 ] ce [     0.008      0.019  21408.996   1336.778 ] so[Waterdistributor_0]
       6 : SMesh::descRange name[-]  lvid  34 mn [ -1342.054  -1342.032 -21584.982 ] mx [  1342.070   1342.071 -21039.025 ] ce [     0.008      0.020 -21312.004   1342.062 ] so[Waterdistributor_1]
       7 : SMesh::descRange name[-]  lvid  33 mn [ -1336.770  -1336.749 -21579.982 ] mx [  1336.786   1336.788 -21044.025 ] ce [     0.008      0.019 -21312.004   1336.778 ] so[Waterdistributor_0]
       8 : SMesh::descRange name[-]  lvid 336 mn [-20476.000 -20476.000 -20475.582 ] mx [ 20476.000  20476.000  22000.025 ] ce [     0.000      0.000    762.222  21237.805 ] so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2]
       9 : SMesh::descRange name[-]  lvid 335 mn [-20474.000 -20474.000 -20473.582 ] mx [ 20474.000  20474.000  22000.025 ] ce [     0.000      0.000    763.222  21236.805 ] so[sOuterWaterInCD_TSubWaterDistributor_cutTube2]
      10 : SMesh::descRange name[-]  lvid 334 mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.041 ] ce [     0.000      0.000   1184.521  20815.520 ] so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2]
      11 : SMesh::descRange name[-]  lvid 333 mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.041 ] ce [     0.000      0.000   1185.521  20814.520 ] so[sInnerWater_TSubWaterDistributor_cutTube2]
      12 : SMesh::descRange name[-]  lvid 125 mn [ -1342.054  -1342.032  18662.018 ] mx [  1342.070   1342.071  19207.975 ] ce [     0.008      0.020  18934.996   1342.062 ] so[Waterdistributor_3]
      13 : SMesh::descRange name[-]  lvid 124 mn [ -1336.770  -1336.749  18667.018 ] mx [  1336.786   1336.788  19202.975 ] ce [     0.008      0.019  18934.996   1336.778 ] so[Waterdistributor_2]
      14 : SMesh::descRange name[-]  lvid 125 mn [ -1342.054  -1342.032 -19110.982 ] mx [  1342.070   1342.071 -18565.025 ] ce [     0.008      0.020 -18838.004   1342.062 ] so[Waterdistributor_3]
      15 : SMesh::descRange name[-]  lvid 124 mn [ -1336.770  -1336.749 -19105.982 ] mx [  1336.786   1336.788 -18570.025 ] ce [     0.008      0.019 -18838.004   1336.778 ] so[Waterdistributor_2]
      16 : SMesh::descRange name[-]  lvid 132 mn [   -60.000 -12773.921  12252.222 ] mx [    60.000 -12690.562  12338.543 ] ce [     0.000 -12732.241  12295.383     60.000 ] so[solidSJCLSanchor]
      17 : SMesh::descRange name[-]  lvid 132 mn [   -60.000  17145.770   4223.775 ] mx [    60.000  17188.650   4340.210 ] ce [     0.000  17167.211   4281.993     60.000 ] so[solidSJCLSanchor]
      18 : SMesh::descRange name[-]  lvid 133 mn [-15177.086  -8776.702   2560.935 ] mx [-15138.457  -8732.784   2610.399 ] ce [-15157.771  -8754.743   2585.667     24.732 ] so[solidSJFixture]
      19 : SMesh::descRange name[-]  lvid 133 mn [-14688.354  -8494.117   5090.064 ] mx [-14646.824  -8450.004   5139.791 ] ce [-14667.590  -8472.061   5114.928     24.863 ] so[solidSJFixture]
      20 : SMesh::descRange name[-]  lvid 133 mn [-13885.197  -8030.001   7508.397 ] mx [-13840.863  -7985.355   7558.906 ] ce [-13863.030  -8007.678   7533.651     25.255 ] so[solidSJFixture]
      21 : SMesh::descRange name[-]  lvid 133 mn [-12784.855  -7394.049   9765.635 ] mx [-12737.868  -7348.642   9815.844 ] ce [-12761.361  -7371.346   9790.739     25.104 ] so[solidSJFixture]
      22 : SMesh::descRange name[-]  lvid 133 mn [-11446.172  -6620.525  11767.373 ] mx [-11397.233  -6574.387  11816.250 ] ce [-11421.703  -6597.456  11791.812     24.469 ] so[solidSJFixture]
      23 : SMesh::descRange name[-]  lvid 133 mn [ -9914.556  -5735.818  13488.700 ] mx [ -9864.397  -5688.771  13535.312 ] ce [ -9889.477  -5712.295  13512.006     25.079 ] so[solidSJFixture]



Also added CSGFoundry::descPrimRange::

    [CSGFoundry::descPrimRange solidIdx 11 so.primOffset  2731 so.numPrim   338
    [CSGPrim::Desc numPrim 338
       0 : CSGPrim::descRange mn [  -727.052   -538.335  21683.797 ] mx [  -406.658   -255.495  22066.203 ] ce [  -566.855   -396.915  21875.000    191.203 ] lvid  29 ridx    0 pidx     0 so[ConnectingCutTube_0]
       1 : CSGPrim::descRange mn [   320.786   -661.030  21683.797 ] mx [   623.104   -351.170  22066.203 ] ce [   471.945   -506.100  21875.000    191.203 ] lvid  30 ridx    0 pidx     1 so[ConnectingCutTube_1]
       2 : CSGPrim::descRange mn [  -256.899    515.754  21683.795 ] mx [   -54.431    832.776  22066.205 ] ce [  -155.665    674.265  21875.000    191.205 ] lvid  31 ridx    0 pidx     2 so[ConnectingCutTube_2]
       3 : CSGPrim::descRange mn [ -9103.062 -20790.500 -19998.969 ] mx [  5702.666  21247.500    418.500 ] ce [ -1700.198    228.500  -9790.234  21019.000 ] lvid  32 ridx    0 pidx     3 so[WaterDistributorPartIIIUnion]
       4 : CSGPrim::descRange mn [ -1225.791   -252.399  19974.000 ] mx [  1225.791    252.399  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  34 ridx    0 pidx     4 so[Waterdistributor_1]
       5 : CSGPrim::descRange mn [ -1219.998   -246.607  19974.000 ] mx [  1219.998    246.607  22844.000 ] ce [     0.000      0.000  21409.000   1435.000 ] lvid  33 ridx    0 pidx     5 so[Waterdistributor_0]
       6 : CSGPrim::descRange mn [ -1225.791   -252.399 -22747.000 ] mx [  1225.791    252.399 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  34 ridx    0 pidx     6 so[Waterdistributor_1]
       7 : CSGPrim::descRange mn [ -1219.998   -246.607 -22747.000 ] mx [  1219.998    246.607 -19877.000 ] ce [     0.000      0.000 -21312.000   1435.000 ] lvid  33 ridx    0 pidx     7 so[Waterdistributor_0]
       8 : CSGPrim::descRange mn [-20476.000 -20476.000 -20476.000 ] mx [ 20476.000  20476.000  22000.000 ] ce [     0.000      0.000    762.000  21238.000 ] lvid 336 ridx    0 pidx     8 so[sOuterReflectorInCD_TSubWaterDistributor_cutTube2]
       9 : CSGPrim::descRange mn [-20474.000 -20474.000 -20474.000 ] mx [ 20474.000  20474.000  22000.000 ] ce [     0.000      0.000    763.000  21237.000 ] lvid 335 ridx    0 pidx     9 so[sOuterWaterInCD_TSubWaterDistributor_cutTube2]
      10 : CSGPrim::descRange mn [-19631.000 -19631.000 -19631.000 ] mx [ 19631.000  19631.000  22000.000 ] ce [     0.000      0.000   1184.500  20815.500 ] lvid 334 ridx    0 pidx    10 so[sInnerReflectorInCD_TSubWaterDistributor_cutTube2]
      11 : CSGPrim::descRange mn [-19629.000 -19629.000 -19629.000 ] mx [ 19629.000  19629.000  22000.000 ] ce [     0.000      0.000   1185.500  20814.500 ] lvid 333 ridx    0 pidx    11 so[sInnerWater_TSubWaterDistributor_cutTube2]
      12 : CSGPrim::descRange mn [ -1225.791   -252.399  17500.000 ] mx [  1225.791    252.399  20370.000 ] ce [     0.000      0.000  18935.000   1435.000 ] lvid 125 ridx    0 pidx    12 so[Waterdistributor_3]
      13 : CSGPrim::descRange mn [ -1219.998   -246.607  17500.000 ] mx [  1219.998    246.607  20370.000 ] ce [     0.000      0.000  18935.000   1435.000 ] lvid 124 ridx    0 pidx    13 so[Waterdistributor_2]
      14 : CSGPrim::descRange mn [ -1225.791   -252.399 -20273.000 ] mx [  1225.791    252.399 -17403.000 ] ce [     0.000      0.000 -18838.000   1435.000 ] lvid 125 ridx    0 pidx    14 so[Waterdistributor_3]
      15 : CSGPrim::descRange mn [ -1219.998   -246.607 -20273.000 ] mx [  1219.998    246.607 -17403.000 ] ce [     0.000      0.000 -18838.000   1435.000 ] lvid 124 ridx    0 pidx    15 so[Waterdistributor_2]
      16 : CSGPrim::descRange mn [   -60.000 -12773.921  12245.275 ] mx [    60.000 -12683.368  12338.543 ] ce [     0.000 -12728.645  12291.909     60.000 ] lvid 132 ridx    0 pidx    16 so[solidSJCLSanchor]
      17 : CSGPrim::descRange mn [   -60.000  17145.771   4221.356 ] mx [    60.000  17188.650   4340.210 ] ce [     0.000  17167.211   4280.783     60.000 ] lvid 132 ridx    0 pidx    17 so[solidSJCLSanchor]
      18 : CSGPrim::descRange mn [-15179.856  -8778.528   2559.474 ] mx [-15138.458  -8726.628   2610.399 ] ce [-15159.157  -8752.578   2584.937     25.950 ] lvid 133 ridx    0 pidx    18 so[solidSJFixture]
      19 : CSGPrim::descRange mn [-14693.158  -8497.532   5089.034 ] mx [-14646.825  -8442.219   5139.791 ] ce [-14669.992  -8469.875   5114.412     27.657 ] lvid 133 ridx    0 pidx    19 so[solidSJFixture]
      20 : CSGPrim::descRange mn [-13891.481  -8034.684   7508.396 ] mx [-13840.208  -7976.214   7558.906 ] ce [-13865.845  -8005.449   7533.651     29.235 ] lvid 133 ridx    0 pidx    20 so[solidSJFixture]
      21 : CSGPrim::descRange mn [-12792.026  -7399.914   9765.634 ] mx [-12735.851  -7338.613   9815.844 ] ce [-12763.938  -7369.263   9790.738     30.650 ] lvid 133 ridx    0 pidx    21 so[solidSJFixture]
      22 : CSGPrim::descRange mn [-11454.060  -6627.438  11767.373 ] mx [-11393.742  -6563.746  11816.250 ] ce [-11423.900  -6595.592  11791.812     31.846 ] lvid 133 ridx    0 pidx    22 so[solidSJFixture]
      23 : CSGPrim::descRange mn [ -9923.021  -5743.493  13488.699 ] mx [ -9859.358  -5677.869  13535.312 ] ce [ -9891.189  -5710.681  13512.006     32.812 ] lvid 133 ridx    0 pidx    23 so[solidSJFixture]
      24 : CSGPrim::descRange mn [ -6461.781  -3745.145  16038.377 ] mx [ -6393.841  -3677.052  16078.131 ] ce [ -6427.811  -3711.099  16058.254     34.047 ] lvid 133 ridx    0 pidx    24 so[solidSJFixture]
      25 : CSGPrim::descRange mn [ -4719.006  -2738.953  16824.660 ] mx [ -4650.130  -2670.320  16860.316 ] ce [ -4684.568  -2704.636  16842.488     34.438 ] lvid 133 ridx    0 pidx    25 so[solidSJFixture]
      26 : CSGPrim::descRange mn [ -3115.958  -1813.433  17311.912 ] mx [ -3046.800  -1744.637  17343.492 ] ce [ -3081.379  -1779.035  17327.703     34.579 ] lvid 133 ridx    0 pidx    26 so[solidSJFixture]
      27 : CSGPrim::descRange mn [ -1529.860   -897.699  17590.666 ] mx [ -1460.920   -829.029  17617.947 ] ce [ -1495.390   -863.364  17604.307     34.470 ] lvid 133 ridx    0 pidx    27 so[solidSJFixture]
      28 : CSGPrim::descRange mn [   -25.000  -7446.989  16038.377 ] mx [    25.000  -7396.491  16078.131 ] ce [     0.000  -7421.740  16058.254     25.249 ] lvid 133 ridx    0 pidx    28 so[solidSJFixture]
      29 : CSGPrim::descRange mn [   -25.000  -5434.604  16824.660 ] mx [    25.000  -5383.941  16860.316 ] ce [     0.000  -5409.273  16842.488     25.332 ] lvid 133 ridx    0 pidx    29 so[solidSJFixture]
      30 : CSGPrim::descRange mn [   -25.000  -3583.565  17311.912 ] mx [    25.000  -3532.575  17343.492 ] ce [     0.000  -3558.070  17327.703     25.495 ] lvid 133 ridx    0 pidx    30 so[solidSJFixture]
      31 : CSGPrim::descRange mn [   -25.000  -1752.096  17590.666 ] mx [    25.000  -1701.359  17617.947 ] ce [     0.000  -1726.728  17604.307     25.369 ] lvid 133 ridx    0 pidx    31 so[solidSJFixture]
      32 : CSGPrim::descRange mn [  6393.841  -3745.145  16038.377 ] mx [  6461.781  -3677.052  16078.131 ] ce [  6427.811  -3711.099  16058.254     34.047 ] lvid 133 ridx    0 pidx    32 so[solidSJFixture]
      33 : CSGPrim::descRange mn [  4650.130  -2738.953  16824.660 ] mx [  4719.006  -2670.320  16860.316 ] ce [  4684.568  -2704.636  16842.488     34.438 ] lvid 133 ridx    0 pidx    33 so[solidSJFixture]
      34 : CSGPrim::descRange mn [  3046.800  -1813.433  17311.912 ] mx [  3115.958  -1744.637  17343.492 ] ce [  3081.379  -1779.035  17327.703     34.579 ] lvid 133 ridx    0 pidx    34 so[solidSJFixture]
      35 : CSGPrim::descRange mn [  1460.920   -897.699  17590.666 ] mx [  1529.860   -829.029  17617.947 ] ce [  1495.390   -863.364  17604.307     34.470 ] lvid 133 ridx    0 pidx    35 so[solidSJFixture]
      36 : CSGPrim::descRange mn [-15179.856   8726.628   2559.474 ] mx [-15138.458   8778.528   2610.399 ] ce [-15159.157   8752.578   2584.937     25.950 ] lvid 133 ridx    0 pidx    36 so[solidSJFixture]
      37 : CSGPrim::descRange mn [-14693.158   8442.219   5089.034 ] mx [-14646.825   8497.532   5139.791 ] ce [-14669.992   8469.875   5114.412     27.657 ] lvid 133 ridx    0 pidx    37 so[solidSJFixture]
      38 : CSGPrim::descRange mn [-13891.481   7976.214   7508.396 ] mx [-13840.208   8034.684   7558.906 ] ce [-13865.845   8005.449   7533.651     29.235 ] lvid 133 ridx    0 pidx    38 so[solidSJFixture]
      39 : CSGPrim::descRange mn [-12792.026   7338.613   9765.634 ] mx [-12735.851   7399.914   9815.844 ] ce [-12763.938   7369.263   9790.738     30.650 ] lvid 133 ridx    0 pidx    39 so[solidSJFixture]
      40 : CSGPrim::descRange mn [-11454.060   6563.746  11767.373 ] mx [-11393.742   6627.438  11816.250 ] ce [-11423.900   6595.592  11791.812     31.846 ] lvid 133 ridx    0 pidx    40 so[solidSJFixture]
      41 : CSGPrim::descRange mn [ -9923.021   5677.869  13488.699 ] mx [ -9859.358   5743.493  13535.312 ] ce [ -9891.189   5710.681  13512.006     32.812 ] lvid 133 ridx    0 pidx    41 so[solidSJFixture]
      42 : CSGPrim::descRange mn [ -6461.781   3677.052  16038.377 ] mx [ -6393.841   3745.145  16078.131 ] ce [ -6427.811   3711.099  16058.254     34.047 ] lvid 133 ridx    0 pidx    42 so[solidSJFixture]
      43 : CSGPrim::descRange mn [ -4719.006   2670.320  16824.660 ] mx [ -4650.130   2738.953  16860.316 ] ce [ -4684.568   2704.636  16842.488     34.438 ] lvid 133 ridx    0 pidx    43 so[solidSJFixture]
      44 : CSGPrim::descRange mn [ -3115.958   1744.637  17311.912 ] mx [ -3046.800   1813.433  17343.492 ] ce [ -3081.379   1779.035  17327.703     34.579 ] lvid 133 ridx    0 pidx    44 so[solidSJFixture]
      45 : CSGPrim::descRange mn [ -1529.860    829.029  17590.666 ] mx [ -1460.920    897.699  17617.947 ] ce [ -1495.390    863.364  17604.307     34.470 ] lvid 133 ridx    0 pidx    45 so[solidSJFixture]
      46 : CSGPrim::descRange mn [  6393.841   3677.052  16038.377 ] mx [  6461.781   3745.145  16078.131 ] ce [  6427.811   3711.099  16058.254     34.047 ] lvid 133 ridx    0 pidx    46 so[solidSJFixture]
      47 : CSGPrim::descRange mn [  4650.130   2670.320  16824.660 ] mx [  4719.006   2738.953  16860.316 ] ce [  4684.568   2704.636  16842.488     34.438 ] lvid 133 ridx    0 pidx    47 so[solidSJFixture]
      48 : CSGPrim::descRange mn [  3046.800   1744.637  17311.912 ] mx [  3115.958   1813.433  17343.492 ] ce [  3081.379   1779.035  17327.703     34.579 ] lvid 133 ridx    0 pidx    48 so[solidSJFixture]
      49 : CSGPrim::descRange mn [  1460.920    829.029  17590.666 ] mx [  1529.860    897.699  17617.947 ] ce [  1495.390    863.364  17604.307     34.470 ] lvid 133 ridx    0 pidx    49 so[solidSJFixture]
      50 : CSGPrim::descRange mn [   -25.000   7396.491  16038.377 ] mx [    25.000   7446.989  16078.131 ] ce [     0.000   7421.740  16058.254     25.249 ] lvid 133 ridx    0 pidx    50 so[solidSJFixture]
      51 : CSGPrim::descRange mn [   -25.000   5383.941  16824.660 ] mx [    25.000   5434.604  16860.316 ] ce [     0.000   5409.273  16842.488     25.332 ] lvid 133 ridx    0 pidx    51 so[solidSJFixture]
      52 : CSGPrim::descRange mn [   -25.000   3532.575  17311.912 ] mx [    25.000   3583.565  17343.492 ] ce [     0.000   3558.070  17327.703     25.495 ] lvid 133 ridx    0 pidx    52 so[solidSJFixture]
      53 : CSGPrim::descRange mn [   -25.000   1701.359  17590.666 ] mx [    25.000   1752.096  17617.947 ] ce [     0.000   1726.728  17604.307     25.369 ] lvid 133 ridx    0 pidx    53 so[solidSJFixture]
      54 : CSGPrim::descRange mn [-15358.562   8792.987    -60.000 ] mx [-15289.901   8901.910     60.000 ] ce [-15324.231   8847.449      0.000     60.000 ] lvid 134 ridx    0 pidx    54 so[solidSJReceiver]
      55 : CSGPrim::descRange mn [-15358.562  -8901.910    -60.000 ] mx [-15289.901  -8792.987     60.000 ] ce [-15324.231  -8847.449      0.000     60.000 ] lvid 134 ridx    0 pidx    55 so[solidSJReceiver]
      56 : CSGPrim::descRange mn [  8044.245   4609.706  14970.089 ] mx [  8196.966   4767.162  15042.160 ] ce [  8120.605   4688.434  15006.125     78.728 ] lvid 134 ridx    0 pidx    56 so[solidSJReceiver]
      57 : CSGPrim::descRange mn [   -60.000   9323.335  14970.089 ] mx [    60.000   9430.399  15042.160 ] ce [     0.000   9376.867  15006.125     60.000 ] lvid 134 ridx    0 pidx    57 so[solidSJReceiver]
      58 : CSGPrim::descRange mn [ -8196.966   4609.706  14970.089 ] mx [ -8044.245   4767.162  15042.160 ] ce [ -8120.605   4688.434  15006.125     78.728 ] lvid 134 ridx    0 pidx    58 so[solidSJReceiver]
      59 : CSGPrim::descRange mn [ -8196.966  -4767.162  14970.089 ] mx [ -8044.245  -4609.706  15042.160 ] ce [ -8120.605  -4688.434  15006.125     78.728 ] lvid 134 ridx    0 pidx    59 so[solidSJReceiver]
      60 : CSGPrim::descRange mn [   -60.000  -9430.399  14970.089 ] mx [    60.000  -9323.335  15042.160 ] ce [     0.000  -9376.867  15006.125     60.000 ] lvid 134 ridx    0 pidx    60 so[solidSJReceiver]
      61 : CSGPrim::descRange mn [  8044.245  -4767.162  14970.089 ] mx [  8196.966  -4609.706  15042.160 ] ce [  8120.605  -4688.434  15006.125     78.728 ] lvid 134 ridx    0 pidx    61 so[solidSJReceiver]
      62 : CSGPrim::descRange mn [-15352.401   8777.157    -62.000 ] mx [-15265.260   8901.240     62.000 ] ce [-15308.830   8839.199      0.000     62.042 ] lvid 135 ridx    0 pidx    62 so[solidSJReceiverFastern]
      63 : CSGPrim::descRange mn [-15352.401  -8901.240    -62.000 ] mx [-15265.260  -8777.157     62.000 ] ce [-15308.830  -8839.199      0.000     62.042 ] lvid 135 ridx    0 pidx    63 so[solidSJReceiverFastern]
      64 : CSGPrim::descRange mn [  8056.795   4618.363  14958.005 ] mx [  8173.860   4749.761  15034.739 ] ce [  8115.328   4684.062  14996.372     65.699 ] lvid 135 ridx    0 pidx    64 so[solidSJReceiverFastern]
      65 : CSGPrim::descRange mn [   -65.000   9314.750  14958.005 ] mx [    65.000   9426.797  15034.739 ] ce [     0.000   9370.773  14996.372     65.000 ] lvid 135 ridx    0 pidx    65 so[solidSJReceiverFastern]
      66 : CSGPrim::descRange mn [ -8173.860   4618.363  14958.005 ] mx [ -8056.795   4749.761  15034.739 ] ce [ -8115.328   4684.062  14996.372     65.699 ] lvid 135 ridx    0 pidx    66 so[solidSJReceiverFastern]
      67 : CSGPrim::descRange mn [ -8173.860  -4749.761  14958.005 ] mx [ -8056.795  -4618.363  15034.739 ] ce [ -8115.328  -4684.062  14996.372     65.699 ] lvid 135 ridx    0 pidx    67 so[solidSJReceiverFastern]
      68 : CSGPrim::descRange mn [   -65.000  -9426.797  14958.005 ] mx [    65.000  -9314.750  15034.739 ] ce [     0.000  -9370.773  14996.372     65.000 ] lvid 135 ridx    0 pidx    68 so[solidSJReceiverFastern]
      69 : CSGPrim::descRange mn [  8056.795  -4749.761  14958.005 ] mx [  8173.860  -4618.363  15034.739 ] ce [  8115.328  -4684.062  14996.372     65.699 ] lvid 135 ridx    0 pidx    69 so[solidSJReceiverFastern]
      70 : CSGPrim::descRange mn [  -141.592  -1800.876  17733.078 ] mx [   -16.254  -1675.153  17764.264 ] ce [   -78.923  -1738.015  17748.672     62.861 ] lvid 149 ridx    0 pidx    70 so[solidXJanchor]
      71 : CSGPrim::descRange mn [  -166.833  -2356.737  17667.818 ] mx [   -41.500  -2231.129  17701.574 ] ce [  -104.167  -2293.933  17684.695     62.804 ] lvid 149 ridx    0 pidx    71 so[solidXJanchor]
      72 : CSGPrim::descRange mn [  -251.443  -4219.983  17317.516 ] mx [  -126.167  -4095.643  17359.723 ] ce [  -188.805  -4157.813  17338.619     62.638 ] lvid 149 ridx    0 pidx    72 so[solidXJanchor]
      73 : CSGPrim::descRange mn [  -339.191  -6152.354  16728.561 ] mx [  -214.044  -6030.846  16779.244 ] ce [  -276.618  -6091.600  16753.902     62.573 ] lvid 149 ridx    0 pidx    73 so[solidXJanchor]
      74 : CSGPrim::descRange mn [  -435.909  -8282.235  15782.376 ] mx [  -310.994  -8165.847  15846.656 ] ce [  -373.452  -8224.041  15814.516     62.457 ] lvid 149 ridx    0 pidx    74 so[solidXJanchor]
      75 : CSGPrim::descRange mn [  -520.406 -10143.009  14655.241 ] mx [  -395.786 -10033.113  14731.451 ] ce [  -458.096 -10088.061  14693.346     62.310 ] lvid 149 ridx    0 pidx    75 so[solidXJanchor]
      76 : CSGPrim::descRange mn [  -608.500 -12082.985  13100.696 ] mx [  -484.303 -11982.411  13189.140 ] ce [  -546.402 -12032.698  13144.918     62.098 ] lvid 149 ridx    0 pidx    76 so[solidXJanchor]
      77 : CSGPrim::descRange mn [  -685.917 -13787.834  11291.161 ] mx [  -562.227 -13698.432  11390.116 ] ce [  -624.072 -13743.133  11340.639     61.845 ] lvid 149 ridx    0 pidx    77 so[solidXJanchor]
      78 : CSGPrim::descRange mn [  -754.791 -15304.577   9128.608 ] mx [  -631.722 -15228.830   9236.619 ] ce [  -693.257 -15266.703   9182.613     61.534 ] lvid 149 ridx    0 pidx    78 so[solidXJanchor]
      79 : CSGPrim::descRange mn [  -808.402 -16485.166   6765.517 ] mx [  -686.023 -16424.617   6880.209 ] ce [  -747.212 -16454.891   6822.863     61.189 ] lvid 149 ridx    0 pidx    79 so[solidXJanchor]
      80 : CSGPrim::descRange mn [  -843.855 -17268.131   4404.685 ] mx [  -722.176 -17220.770   4523.366 ] ce [  -783.015 -17244.449   4464.025     60.839 ] lvid 149 ridx    0 pidx    80 so[solidXJanchor]
      81 : CSGPrim::descRange mn [  -864.794 -17734.705   1803.444 ] mx [  -743.898 -17699.123   1923.832 ] ce [  -804.346 -17716.914   1863.638     60.448 ] lvid 149 ridx    0 pidx    81 so[solidXJanchor]
      82 : CSGPrim::descRange mn [  -868.942 -17829.762    -60.000 ] mx [  -748.612 -17802.930     60.000 ] ce [  -808.777 -17816.346      0.000     60.165 ] lvid 149 ridx    0 pidx    82 so[solidXJanchor]
      83 : CSGPrim::descRange mn [  -864.794 -17734.705  -1923.832 ] mx [  -743.898 -17699.123  -1803.444 ] ce [  -804.346 -17716.914  -1863.638     60.448 ] lvid 149 ridx    0 pidx    83 so[solidXJanchor]
      84 : CSGPrim::descRange mn [  -843.855 -17268.131  -4523.366 ] mx [  -722.176 -17220.770  -4404.685 ] ce [  -783.015 -17244.449  -4464.025     60.839 ] lvid 149 ridx    0 pidx    84 so[solidXJanchor]
      85 : CSGPrim::descRange mn [  -808.402 -16485.166  -6880.209 ] mx [  -686.023 -16424.617  -6765.517 ] ce [  -747.212 -16454.891  -6822.863     61.189 ] lvid 149 ridx    0 pidx    85 so[solidXJanchor]
      86 : CSGPrim::descRange mn [  -754.791 -15304.577  -9236.619 ] mx [  -631.722 -15228.830  -9128.608 ] ce [  -693.257 -15266.703  -9182.613     61.534 ] lvid 149 ridx    0 pidx    86 so[solidXJanchor]
      87 : CSGPrim::descRange mn [  -685.917 -13787.834 -11390.116 ] mx [  -562.227 -13698.432 -11291.161 ] ce [  -624.072 -13743.133 -11340.639     61.845 ] lvid 149 ridx    0 pidx    87 so[solidXJanchor]
      88 : CSGPrim::descRange mn [  -608.500 -12082.985 -13189.140 ] mx [  -484.303 -11982.411 -13100.696 ] ce [  -546.402 -12032.698 -13144.918     62.098 ] lvid 149 ridx    0 pidx    88 so[solidXJanchor]
      89 : CSGPrim::descRange mn [  -520.406 -10143.009 -14731.451 ] mx [  -395.786 -10033.113 -14655.241 ] ce [  -458.096 -10088.061 -14693.346     62.310 ] lvid 149 ridx    0 pidx    89 so[solidXJanchor]
      90 : CSGPrim::descRange mn [  -435.909  -8282.235 -15846.656 ] mx [  -310.994  -8165.847 -15782.376 ] ce [  -373.452  -8224.041 -15814.516     62.457 ] lvid 149 ridx    0 pidx    90 so[solidXJanchor]
      91 : CSGPrim::descRange mn [  -339.191  -6152.354 -16779.244 ] mx [  -214.044  -6030.846 -16728.561 ] ce [  -276.618  -6091.600 -16753.902     62.573 ] lvid 149 ridx    0 pidx    91 so[solidXJanchor]
      92 : CSGPrim::descRange mn [  -251.443  -4219.983 -17359.723 ] mx [  -126.167  -4095.643 -17317.516 ] ce [  -188.805  -4157.813 -17338.619     62.638 ] lvid 149 ridx    0 pidx    92 so[solidXJanchor]
      93 : CSGPrim::descRange mn [  -200.320  -3094.177 -17590.830 ] mx [   -75.003  -2968.906 -17553.697 ] ce [  -137.661  -3031.541 -17572.264     62.659 ] lvid 149 ridx    0 pidx    93 so[solidXJanchor]
      94 : CSGPrim::descRange mn [  -213.654  -2447.904 -17689.428 ] mx [   -86.339  -2320.348 -17655.246 ] ce [  -149.996  -2384.126 -17672.336     63.778 ] lvid 149 ridx    0 pidx    94 so[solidXJanchor]
      95 : CSGPrim::descRange mn [  -253.485  -1982.088 -17745.312 ] mx [  -122.311  -1850.574 -17713.268 ] ce [  -187.898  -1916.331 -17729.289     65.757 ] lvid 149 ridx    0 pidx    95 so[solidXJanchor]
      96 : CSGPrim::descRange mn [  -338.783  -1506.170 -17789.035 ] mx [  -198.680  -1365.735 -17759.148 ] ce [  -268.731  -1435.952 -17774.092     70.218 ] lvid 149 ridx    0 pidx    96 so[solidXJanchor]
      97 : CSGPrim::descRange mn [  -431.412  -1072.937 -17817.068 ] mx [  -277.983   -919.276 -17789.068 ] ce [  -354.698   -996.106 -17803.068     76.830 ] lvid 149 ridx    0 pidx    97 so[solidXJanchor]
      98 : CSGPrim::descRange mn [  -899.344    589.397 -17817.068 ] mx [  -730.097    758.593 -17789.068 ] ce [  -814.720    673.995 -17803.068     84.623 ] lvid 149 ridx    0 pidx    98 so[solidXJanchor]
      99 : CSGPrim::descRange mn [ -1050.921   1010.982 -17789.035 ] mx [  -881.276   1180.665 -17759.148 ] ce [  -966.098   1095.823 -17774.092     84.841 ] lvid 149 ridx    0 pidx    99 so[solidXJanchor]
     100 : CSGPrim::descRange mn [ -1226.651   1465.789 -17745.312 ] mx [ -1058.629   1633.891 -17713.268 ] ce [ -1142.640   1549.840 -17729.289     84.051 ] lvid 149 ridx    0 pidx   100 so[solidXJanchor]
     101 : CSGPrim::descRange mn [ -1433.093   1887.553 -17689.428 ] mx [ -1266.138   2054.575 -17655.246 ] ce [ -1349.616   1971.064 -17672.336     83.511 ] lvid 149 ridx    0 pidx   101 so[solidXJanchor]
     102 : CSGPrim::descRange mn [ -1753.631   2450.385 -17590.830 ] mx [ -1587.418   2616.583 -17553.697 ] ce [ -1670.525   2533.484 -17572.264     83.106 ] lvid 149 ridx    0 pidx   102 so[solidXJanchor]
     103 : CSGPrim::descRange mn [ -2374.004   3392.008 -17359.723 ] mx [ -2208.305   3557.428 -17317.516 ] ce [ -2291.154   3474.718 -17338.619     82.850 ] lvid 149 ridx    0 pidx   103 so[solidXJanchor]
     104 : CSGPrim::descRange mn [ -3438.833   5009.273 -16779.244 ] mx [ -3274.695   5172.326 -16728.561 ] ce [ -3356.764   5090.800 -16753.902     82.069 ] lvid 149 ridx    0 pidx   104 so[solidXJanchor]
     105 : CSGPrim::descRange mn [ -4612.500   6793.511 -15846.656 ] mx [ -4451.183   6952.286 -15782.376 ] ce [ -4531.842   6872.898 -15814.516     80.659 ] lvid 149 ridx    0 pidx   105 so[solidXJanchor]
     106 : CSGPrim::descRange mn [ -5637.876   8354.001 -14731.451 ] mx [ -5480.136   8507.350 -14655.241 ] ce [ -5559.006   8430.676 -14693.346     78.870 ] lvid 149 ridx    0 pidx   106 so[solidXJanchor]
     107 : CSGPrim::descRange mn [ -6706.896   9983.044 -13189.140 ] mx [ -6554.292  10128.604 -13100.696 ] ce [ -6630.594  10055.824 -13144.918     76.302 ] lvid 149 ridx    0 pidx   107 so[solidXJanchor]
     108 : CSGPrim::descRange mn [ -7646.350  11417.137 -11390.116 ] mx [ -7499.902  11553.359 -11291.161 ] ce [ -7573.126  11485.248 -11340.639     73.224 ] lvid 149 ridx    0 pidx   108 so[solidXJanchor]
     109 : CSGPrim::descRange mn [ -8482.147  12696.104  -9236.619 ] mx [ -8343.226  12820.914  -9128.608 ] ce [ -8412.687  12758.509  -9182.613     69.461 ] lvid 149 ridx    0 pidx   109 so[solidXJanchor]
     110 : CSGPrim::descRange mn [ -9132.709  13695.433  -6880.209 ] mx [ -9002.162  13807.542  -6765.517 ] ce [ -9067.436  13751.487  -6822.863     65.273 ] lvid 149 ridx    0 pidx   110 so[solidXJanchor]
     111 : CSGPrim::descRange mn [ -9562.931  14360.784  -4523.366 ] mx [ -9440.880  14460.008  -4404.685 ] ce [ -9501.905  14410.396  -4464.025     61.025 ] lvid 149 ridx    0 pidx   111 so[solidXJanchor]
     112 : CSGPrim::descRange mn [ -9817.037  14760.548  -1923.832 ] mx [ -9704.476  14845.380  -1803.444 ] ce [ -9760.756  14802.964  -1863.638     60.194 ] lvid 149 ridx    0 pidx   112 so[solidXJanchor]
     113 : CSGPrim::descRange mn [ -9867.364  14847.300    -60.000 ] mx [ -9761.678  14921.706     60.000 ] ce [ -9814.521  14884.503      0.000     60.000 ] lvid 149 ridx    0 pidx   113 so[solidXJanchor]
     114 : CSGPrim::descRange mn [ -9817.037  14760.548   1803.444 ] mx [ -9704.476  14845.380   1923.832 ] ce [ -9760.756  14802.964   1863.638     60.194 ] lvid 149 ridx    0 pidx   114 so[solidXJanchor]
     115 : CSGPrim::descRange mn [ -9562.931  14360.784   4404.685 ] mx [ -9440.880  14460.008   4523.366 ] ce [ -9501.905  14410.396   4464.025     61.025 ] lvid 149 ridx    0 pidx   115 so[solidXJanchor]
     116 : CSGPrim::descRange mn [ -9132.709  13695.433   6765.517 ] mx [ -9002.162  13807.542   6880.209 ] ce [ -9067.436  13751.487   6822.863     65.273 ] lvid 149 ridx    0 pidx   116 so[solidXJanchor]
     117 : CSGPrim::descRange mn [ -8482.147  12696.104   9128.608 ] mx [ -8343.226  12820.914   9236.619 ] ce [ -8412.687  12758.509   9182.613     69.461 ] lvid 149 ridx    0 pidx   117 so[solidXJanchor]
     118 : CSGPrim::descRange mn [ -7646.350  11417.137  11291.161 ] mx [ -7499.902  11553.359  11390.116 ] ce [ -7573.126  11485.248  11340.639     73.224 ] lvid 149 ridx    0 pidx   118 so[solidXJanchor]
     119 : CSGPrim::descRange mn [ -6706.896   9983.044  13100.696 ] mx [ -6554.292  10128.604  13189.140 ] ce [ -6630.594  10055.824  13144.918     76.302 ] lvid 149 ridx    0 pidx   119 so[solidXJanchor]
     120 : CSGPrim::descRange mn [ -5637.876   8354.001  14655.241 ] mx [ -5480.136   8507.350  14731.451 ] ce [ -5559.006   8430.676  14693.346     78.870 ] lvid 149 ridx    0 pidx   120 so[solidXJanchor]
     121 : CSGPrim::descRange mn [ -4612.500   6793.511  15782.376 ] mx [ -4451.183   6952.286  15846.656 ] ce [ -4531.842   6872.898  15814.516     80.659 ] lvid 149 ridx    0 pidx   121 so[solidXJanchor]
     122 : CSGPrim::descRange mn [ -3438.833   5009.273  16728.561 ] mx [ -3274.695   5172.326  16779.244 ] ce [ -3356.764   5090.800  16753.902     82.069 ] lvid 149 ridx    0 pidx   122 so[solidXJanchor]
     123 : CSGPrim::descRange mn [ -2374.004   3392.008  17317.516 ] mx [ -2208.305   3557.428  17359.723 ] ce [ -2291.154   3474.718  17338.619     82.850 ] lvid 149 ridx    0 pidx   123 so[solidXJanchor]
     124 : CSGPrim::descRange mn [ -1347.266   1833.818  17667.818 ] mx [ -1180.868   2000.299  17701.574 ] ce [ -1264.067   1917.058  17684.695     83.240 ] lvid 149 ridx    0 pidx   124 so[solidXJanchor]
     125 : CSGPrim::descRange mn [ -1040.960   1369.185  17733.078 ] mx [  -874.499   1535.761  17764.264 ] ce [  -957.729   1452.473  17748.672     83.288 ] lvid 149 ridx    0 pidx   125 so[solidXJanchor]
     126 : CSGPrim::descRange mn [  -144.657  -1801.931  17742.836 ] mx [   -13.335  -1676.340  17790.158 ] ce [   -78.996  -1739.135  17766.496     65.661 ] lvid 150 ridx    0 pidx   126 so[solidXJfixture]
     127 : CSGPrim::descRange mn [  -169.938  -2358.191  17677.479 ] mx [   -38.588  -2232.634  17727.062 ] ce [  -104.263  -2295.412  17702.270     65.675 ] lvid 150 ridx    0 pidx   127 so[solidXJfixture]
     128 : CSGPrim::descRange mn [  -254.696  -4222.757  17326.771 ] mx [  -123.263  -4098.232  17383.643 ] ce [  -188.980  -4160.495  17355.207     65.717 ] lvid 150 ridx    0 pidx   128 so[solidXJfixture]
     129 : CSGPrim::descRange mn [  -342.625  -6156.473  16737.273 ] mx [  -211.123  -6034.585  16801.195 ] ce [  -276.874  -6095.529  16769.234     65.751 ] lvid 150 ridx    0 pidx   129 so[solidXJfixture]
     130 : CSGPrim::descRange mn [  -439.575  -8287.804  15790.323 ] mx [  -308.020  -8170.888  15861.357 ] ce [  -373.797  -8229.346  15825.840     65.778 ] lvid 150 ridx    0 pidx   130 so[solidXJfixture]
     131 : CSGPrim::descRange mn [  -524.309 -10149.811  14662.350 ] mx [  -392.731 -10039.325  14743.297 ] ce [  -458.520 -10094.568  14702.823     65.789 ] lvid 150 ridx    0 pidx   131 so[solidXJfixture]
     132 : CSGPrim::descRange mn [  -612.695 -12091.032  13106.718 ] mx [  -481.120 -11989.887  13200.075 ] ce [  -546.907 -12040.459  13153.396     65.787 ] lvid 150 ridx    0 pidx   132 so[solidXJfixture]
     133 : CSGPrim::descRange mn [  -690.418 -13796.926  11295.979 ] mx [  -558.881 -13707.068  11399.929 ] ce [  -624.650 -13751.997  11347.953     65.768 ] lvid 150 ridx    0 pidx   133 so[solidXJfixture]
     134 : CSGPrim::descRange mn [  -759.629 -15314.769   9132.045 ] mx [  -628.168 -15238.563   9245.029 ] ce [  -693.899 -15276.666   9188.537     65.731 ] lvid 150 ridx    0 pidx   134 so[solidXJfixture]
     135 : CSGPrim::descRange mn [  -813.579 -16503.973   6767.496 ] mx [  -682.228 -16435.283   6887.032 ] ce [  -747.904 -16469.629   6827.264     65.675 ] lvid 150 ridx    0 pidx   135 so[solidXJfixture]
     136 : CSGPrim::descRange mn [  -849.348 -17292.424   4405.252 ] mx [  -718.131 -17232.143   4528.557 ] ce [  -783.740 -17262.283   4466.904     65.609 ] lvid 150 ridx    0 pidx   136 so[solidXJfixture]
     137 : CSGPrim::descRange mn [  -870.614 -17761.166   1802.500 ] mx [  -739.568 -17711.049   1927.180 ] ce [  -805.091 -17736.107   1864.840     65.523 ] lvid 150 ridx    0 pidx   137 so[solidXJfixture]
     138 : CSGPrim::descRange mn [  -874.980 -17857.414    -62.000 ] mx [  -744.070 -17812.693     62.000 ] ce [  -809.525 -17835.055      0.000     65.455 ] lvid 150 ridx    0 pidx   138 so[solidXJfixture]
     139 : CSGPrim::descRange mn [  -870.614 -17761.166  -1927.180 ] mx [  -739.568 -17711.049  -1802.500 ] ce [  -805.091 -17736.107  -1864.840     65.523 ] lvid 150 ridx    0 pidx   139 so[solidXJfixture]
     140 : CSGPrim::descRange mn [  -849.348 -17292.424  -4528.557 ] mx [  -718.131 -17232.143  -4405.252 ] ce [  -783.740 -17262.283  -4466.904     65.609 ] lvid 150 ridx    0 pidx   140 so[solidXJfixture]
     141 : CSGPrim::descRange mn [  -813.579 -16503.973  -6887.032 ] mx [  -682.228 -16435.283  -6767.496 ] ce [  -747.904 -16469.629  -6827.264     65.675 ] lvid 150 ridx    0 pidx   141 so[solidXJfixture]
     142 : CSGPrim::descRange mn [  -759.629 -15314.769  -9245.029 ] mx [  -628.168 -15238.563  -9132.045 ] ce [  -693.899 -15276.666  -9188.537     65.731 ] lvid 150 ridx    0 pidx   142 so[solidXJfixture]
     143 : CSGPrim::descRange mn [  -690.418 -13796.926 -11399.929 ] mx [  -558.881 -13707.068 -11295.979 ] ce [  -624.650 -13751.997 -11347.953     65.768 ] lvid 150 ridx    0 pidx   143 so[solidXJfixture]
     144 : CSGPrim::descRange mn [  -612.695 -12091.032 -13200.075 ] mx [  -481.120 -11989.887 -13106.718 ] ce [  -546.907 -12040.459 -13153.396     65.787 ] lvid 150 ridx    0 pidx   144 so[solidXJfixture]
     145 : CSGPrim::descRange mn [  -524.309 -10149.811 -14743.297 ] mx [  -392.731 -10039.325 -14662.350 ] ce [  -458.520 -10094.568 -14702.823     65.789 ] lvid 150 ridx    0 pidx   145 so[solidXJfixture]
     146 : CSGPrim::descRange mn [  -439.575  -8287.804 -15861.357 ] mx [  -308.020  -8170.888 -15790.323 ] ce [  -373.797  -8229.346 -15825.840     65.778 ] lvid 150 ridx    0 pidx   146 so[solidXJfixture]
     147 : CSGPrim::descRange mn [  -342.625  -6156.473 -16801.195 ] mx [  -211.123  -6034.585 -16737.273 ] ce [  -276.874  -6095.529 -16769.234     65.751 ] lvid 150 ridx    0 pidx   147 so[solidXJfixture]
     148 : CSGPrim::descRange mn [  -254.696  -4222.757 -17383.643 ] mx [  -123.263  -4098.232 -17326.771 ] ce [  -188.980  -4160.495 -17355.207     65.717 ] lvid 150 ridx    0 pidx   148 so[solidXJfixture]
     149 : CSGPrim::descRange mn [  -203.481  -3096.156 -17615.734 ] mx [   -72.096  -2970.837 -17563.211 ] ce [  -137.789  -3033.497 -17589.473     65.692 ] lvid 150 ridx    0 pidx   149 so[solidXJfixture]
     150 : CSGPrim::descRange mn [  -216.037  -2448.575 -17714.844 ] mx [   -84.233  -2322.753 -17664.887 ] ce [  -150.135  -2385.664 -17689.865     65.902 ] lvid 150 ridx    0 pidx   150 so[solidXJfixture]
     151 : CSGPrim::descRange mn [  -254.338  -1980.731 -17771.074 ] mx [  -121.806  -1854.403 -17722.992 ] ce [  -188.072  -1917.567 -17747.033     66.266 ] lvid 150 ridx    0 pidx   151 so[solidXJfixture]
     152 : CSGPrim::descRange mn [  -335.794  -1500.255 -17815.125 ] mx [  -202.166  -1373.502 -17768.951 ] ce [  -268.980  -1436.878 -17792.039     66.814 ] lvid 150 ridx    0 pidx   152 so[solidXJfixture]
     153 : CSGPrim::descRange mn [  -421.511  -1059.275 -17843.428 ] mx [  -288.540   -934.223 -17798.932 ] ce [  -355.026   -996.749 -17821.180     66.485 ] lvid 150 ridx    0 pidx   153 so[solidXJfixture]
     154 : CSGPrim::descRange mn [  -878.839    610.877 -17843.428 ] mx [  -751.652    737.982 -17798.932 ] ce [  -815.246    674.430 -17821.180     63.593 ] lvid 150 ridx    0 pidx   154 so[solidXJfixture]
     155 : CSGPrim::descRange mn [ -1030.488   1032.730 -17815.125 ] mx [  -902.955   1160.330 -17768.951 ] ce [  -966.722   1096.530 -17792.039     63.800 ] lvid 150 ridx    0 pidx   155 so[solidXJfixture]
     156 : CSGPrim::descRange mn [ -1206.562   1487.562 -17771.074 ] mx [ -1080.193   1614.116 -17722.992 ] ce [ -1143.377   1550.839 -17747.033     63.277 ] lvid 150 ridx    0 pidx   156 so[solidXJfixture]
     157 : CSGPrim::descRange mn [ -1413.766   1909.398 -17714.844 ] mx [ -1287.670   2035.273 -17664.887 ] ce [ -1350.718   1972.335 -17689.865     63.048 ] lvid 150 ridx    0 pidx   157 so[solidXJfixture]
     158 : CSGPrim::descRange mn [ -1735.550   2472.403 -17615.734 ] mx [ -1608.591   2597.833 -17563.211 ] ce [ -1672.071   2535.118 -17589.473     63.479 ] lvid 150 ridx    0 pidx   158 so[solidXJfixture]
     159 : CSGPrim::descRange mn [ -2357.047   3414.391 -17383.643 ] mx [ -2229.503   3539.528 -17326.771 ] ce [ -2293.275   3476.959 -17355.207     63.772 ] lvid 150 ridx    0 pidx   159 so[solidXJfixture]
     160 : CSGPrim::descRange mn [ -3424.060   5032.153 -16801.195 ] mx [ -3295.681   5156.014 -16737.273 ] ce [ -3359.871   5094.083 -16769.234     64.190 ] lvid 150 ridx    0 pidx   160 so[solidXJfixture]
     161 : CSGPrim::descRange mn [ -4600.548   6816.731 -15861.357 ] mx [ -4471.523   6937.932 -15790.323 ] ce [ -4536.035   6877.332 -15825.840     64.512 ] lvid 150 ridx    0 pidx   161 so[solidXJfixture]
     162 : CSGPrim::descRange mn [ -5628.806   8377.307 -14743.297 ] mx [ -5499.495   8494.919 -14662.350 ] ce [ -5564.150   8436.113 -14702.823     64.656 ] lvid 150 ridx    0 pidx   162 so[solidXJfixture]
     163 : CSGPrim::descRange mn [ -6701.360  10006.175 -13200.075 ] mx [ -6572.101  10118.446 -13106.718 ] ce [ -6636.730  10062.311 -13153.396     64.630 ] lvid 150 ridx    0 pidx   163 so[solidXJfixture]
     164 : CSGPrim::descRange mn [ -7644.537  11439.801 -11399.929 ] mx [ -7515.732  11547.032 -11295.979 ] ce [ -7580.135  11493.416 -11347.953     64.402 ] lvid 150 ridx    0 pidx   164 so[solidXJfixture]
     165 : CSGPrim::descRange mn [ -8484.416  12717.966  -9245.029 ] mx [ -8356.528  12820.776  -9132.045 ] ce [ -8420.473  12769.371  -9188.537     63.944 ] lvid 150 ridx    0 pidx   165 so[solidXJfixture]
     166 : CSGPrim::descRange mn [ -9139.101  13714.771  -6887.032 ] mx [ -9012.553  13813.657  -6767.496 ] ce [ -9075.826  13764.214  -6827.264     63.274 ] lvid 150 ridx    0 pidx   166 so[solidXJfixture]
     167 : CSGPrim::descRange mn [ -9573.160  14375.521  -4528.557 ] mx [ -9448.237  14471.944  -4405.252 ] ce [ -9510.699  14423.732  -4466.904     62.461 ] lvid 150 ridx    0 pidx   167 so[solidXJfixture]
     168 : CSGPrim::descRange mn [ -9831.214  14770.024  -1927.180 ] mx [ -9708.365  14863.654  -1802.500 ] ce [ -9769.789  14816.840  -1864.840     62.340 ] lvid 150 ridx    0 pidx   168 so[solidXJfixture]
     169 : CSGPrim::descRange mn [ -9884.199  14852.896    -62.000 ] mx [ -9763.009  14944.090     62.000 ] ce [ -9823.604  14898.492      0.000     62.000 ] lvid 150 ridx    0 pidx   169 so[solidXJfixture]
     170 : CSGPrim::descRange mn [ -9831.214  14770.024   1802.500 ] mx [ -9708.365  14863.654   1927.180 ] ce [ -9769.789  14816.840   1864.840     62.340 ] lvid 150 ridx    0 pidx   170 so[solidXJfixture]
     171 : CSGPrim::descRange mn [ -9573.160  14375.521   4405.252 ] mx [ -9448.237  14471.944   4528.557 ] ce [ -9510.699  14423.732   4466.904     62.461 ] lvid 150 ridx    0 pidx   171 so[solidXJfixture]
     172 : CSGPrim::descRange mn [ -9139.101  13714.771   6767.496 ] mx [ -9012.553  13813.657   6887.032 ] ce [ -9075.826  13764.214   6827.264     63.274 ] lvid 150 ridx    0 pidx   172 so[solidXJfixture]
     173 : CSGPrim::descRange mn [ -8484.416  12717.966   9132.045 ] mx [ -8356.528  12820.776   9245.029 ] ce [ -8420.473  12769.371   9188.537     63.944 ] lvid 150 ridx    0 pidx   173 so[solidXJfixture]
     174 : CSGPrim::descRange mn [ -7644.537  11439.801  11295.979 ] mx [ -7515.732  11547.032  11399.929 ] ce [ -7580.135  11493.416  11347.953     64.402 ] lvid 150 ridx    0 pidx   174 so[solidXJfixture]
     175 : CSGPrim::descRange mn [ -6701.360  10006.175  13106.718 ] mx [ -6572.101  10118.446  13200.075 ] ce [ -6636.730  10062.311  13153.396     64.630 ] lvid 150 ridx    0 pidx   175 so[solidXJfixture]
     176 : CSGPrim::descRange mn [ -5628.806   8377.307  14662.350 ] mx [ -5499.495   8494.919  14743.297 ] ce [ -5564.150   8436.113  14702.823     64.656 ] lvid 150 ridx    0 pidx   176 so[solidXJfixture]
     177 : CSGPrim::descRange mn [ -4600.548   6816.731  15790.323 ] mx [ -4471.523   6937.932  15861.357 ] ce [ -4536.035   6877.332  15825.840     64.512 ] lvid 150 ridx    0 pidx   177 so[solidXJfixture]
     178 : CSGPrim::descRange mn [ -3424.060   5032.153  16737.273 ] mx [ -3295.681   5156.014  16801.195 ] ce [ -3359.871   5094.083  16769.234     64.190 ] lvid 150 ridx    0 pidx   178 so[solidXJfixture]
     179 : CSGPrim::descRange mn [ -2357.047   3414.391  17326.771 ] mx [ -2229.503   3539.528  17383.643 ] ce [ -2293.275   3476.959  17355.207     63.772 ] lvid 150 ridx    0 pidx   179 so[solidXJfixture]
     180 : CSGPrim::descRange mn [ -1328.506   1855.569  17677.479 ] mx [ -1201.968   1981.021  17727.062 ] ce [ -1265.237   1918.295  17702.270     63.269 ] lvid 150 ridx    0 pidx   180 so[solidXJfixture]
     181 : CSGPrim::descRange mn [ -1021.716   1390.720  17742.836 ] mx [  -895.515   1516.100  17790.158 ] ce [  -958.616   1453.410  17766.496     63.101 ] lvid 150 ridx    0 pidx   181 so[solidXJfixture]
     182 : CSGPrim::descRange mn [ -2470.439    514.747  17278.676 ] mx [  -334.919   3739.801  17855.316 ] ce [ -1402.679   2127.274  17566.996   1612.527 ] lvid 178 ridx    0 pidx   182 so[sSurftube_0V1_0]
     183 : CSGPrim::descRange mn [ -2468.897    515.666  17280.211 ] mx [  -336.272   3738.597  17853.732 ] ce [ -1402.585   2127.132  17566.973   1611.466 ] lvid 177 ridx    0 pidx   183 so[svacSurftube_0V1_0]
     184 : CSGPrim::descRange mn [ -3300.387   3736.076  16871.916 ] mx [ -2458.994   4998.483  17346.883 ] ce [ -2879.690   4367.280  17109.398    631.203 ] lvid 180 ridx    0 pidx   184 so[sSurftube_1V1_0]
     185 : CSGPrim::descRange mn [ -3298.772   3737.280  16873.410 ] mx [ -2460.536   4997.169  17345.348 ] ce [ -2879.654   4367.225  17109.379    629.944 ] lvid 179 ridx    0 pidx   185 so[svacSurftube_1V1_0]
     186 : CSGPrim::descRange mn [ -3612.491   4968.364  16605.303 ] mx [ -3271.538   5471.814  16841.422 ] ce [ -3442.014   5220.089  16723.363    251.725 ] lvid 182 ridx    0 pidx   186 so[sSurftube_2V1_0]
     187 : CSGPrim::descRange mn [ -3610.848   4969.678  16606.777 ] mx [ -3273.152   5470.457  16839.928 ] ce [ -3442.000   5220.067  16723.352    250.389 ] lvid 181 ridx    0 pidx   187 so[svacSurftube_2V1_0]
     188 : CSGPrim::descRange mn [ -4406.820   5468.594  16010.331 ] mx [ -3601.379   6676.477  16662.848 ] ce [ -4004.099   6072.535  16336.590    603.941 ] lvid 184 ridx    0 pidx   188 so[sSurftube_3V1_0]
     189 : CSGPrim::descRange mn [ -4405.107   5469.952  16011.749 ] mx [ -3603.022   6675.014  16661.373 ] ce [ -4004.064   6072.482  16336.561    602.531 ] lvid 183 ridx    0 pidx   189 so[svacSurftube_3V1_0]
     190 : CSGPrim::descRange mn [ -4850.937   6642.950  15533.369 ] mx [ -4375.724   7350.016  15989.076 ] ce [ -4613.331   6996.483  15761.223    353.533 ] lvid 186 ridx    0 pidx   190 so[sSurftube_4V1_0]
     191 : CSGPrim::descRange mn [ -4849.184   6644.413  15534.748 ] mx [ -4377.437   7348.492  15987.658 ] ce [ -4613.311   6996.452  15761.203    352.039 ] lvid 185 ridx    0 pidx   191 so[svacSurftube_4V1_0]
     192 : CSGPrim::descRange mn [ -5140.066   7322.181  15197.458 ] mx [ -4823.594   7788.503  15529.800 ] ce [ -4981.830   7555.342  15363.629    233.161 ] lvid 188 ridx    0 pidx   192 so[sSurftube_5V1_0]
     193 : CSGPrim::descRange mn [ -5138.287   7323.705  15198.810 ] mx [ -4825.347   7786.939  15528.421 ] ce [ -4981.817   7555.322  15363.615    231.617 ] lvid 187 ridx    0 pidx   193 so[svacSurftube_5V1_0]
     194 : CSGPrim::descRange mn [ -5434.003   7776.577  14876.314 ] mx [ -5123.213   8234.282  15227.130 ] ce [ -5278.608   8005.430  15051.723    228.853 ] lvid 190 ridx    0 pidx   194 so[sSurftube_6V1_0]
     195 : CSGPrim::descRange mn [ -5432.198   7778.141  14877.637 ] mx [ -5124.992   8232.680  15225.778 ] ce [ -5278.595   8005.410  15051.707    227.269 ] lvid 189 ridx    0 pidx   195 so[svacSurftube_6V1_0]
     196 : CSGPrim::descRange mn [ -5719.165   8218.428  14529.642 ] mx [ -5414.560   8666.753  14898.371 ] ce [ -5566.862   8442.590  14714.006    224.163 ] lvid 192 ridx    0 pidx   196 so[sSurftube_7V1_0]
     197 : CSGPrim::descRange mn [ -5717.335   8220.030  14530.933 ] mx [ -5416.365   8665.111  14897.049 ] ce [ -5566.850   8442.570  14713.990    222.541 ] lvid 191 ridx    0 pidx   197 so[svacSurftube_7V1_0]
     198 : CSGPrim::descRange mn [ -6516.375   8635.808  13349.387 ] mx [ -5689.771   9875.785  14526.304 ] ce [ -6103.073   9255.797  13937.846    619.989 ] lvid 194 ridx    0 pidx   198 so[sSurftube_8V1_0]
     199 : CSGPrim::descRange mn [ -6514.474   8637.448  13350.574 ] mx [ -5691.601   9874.036  14525.014 ] ce [ -6103.037   9255.742  13937.794    618.294 ] lvid 193 ridx    0 pidx   199 so[svacSurftube_8V1_0]
     200 : CSGPrim::descRange mn [ -6777.918   9867.566  12945.865 ] mx [ -6501.967  10272.437  13380.993 ] ce [ -6639.942  10070.002  13163.430    217.564 ] lvid 196 ridx    0 pidx   200 so[sSurftube_9V1_0]
     201 : CSGPrim::descRange mn [ -6775.995   9869.316  12947.015 ] mx [ -6503.868  10270.653  13379.806 ] ce [ -6639.932  10069.984  13163.410    216.396 ] lvid 195 ridx    0 pidx   201 so[svacSurftube_9V1_0]
     202 : CSGPrim::descRange mn [ -7476.854  10237.699  11575.762 ] mx [ -6746.024  11332.427  12942.892 ] ce [ -7111.438  10785.062  12259.326    683.565 ] lvid 198 ridx    0 pidx   202 so[sSurftube_10V1_0]
     203 : CSGPrim::descRange mn [ -7474.867  10239.482  11576.791 ] mx [ -6747.948  11330.549  12941.741 ] ce [ -7111.407  10785.016  12259.266    682.475 ] lvid 197 ridx    0 pidx   203 so[svacSurftube_10V1_0]
     204 : CSGPrim::descRange mn [ -7704.902  11324.543  11110.112 ] mx [ -7462.666  11678.281  11603.169 ] ce [ -7583.784  11501.412  11356.641    246.528 ] lvid 200 ridx    0 pidx   204 so[sSurftube_11V1_0]
     205 : CSGPrim::descRange mn [ -7702.896  11326.422  11111.099 ] mx [ -7464.652  11676.373  11602.140 ] ce [ -7583.774  11501.397  11356.619    245.521 ] lvid 199 ridx    0 pidx   205 so[svacSurftube_11V1_0]
     206 : CSGPrim::descRange mn [ -8291.958  11640.223   9576.828 ] mx [ -7670.818  12568.598  11107.560 ] ce [ -7981.388  12104.410  10342.193    765.366 ] lvid 202 ridx    0 pidx   206 so[sSurftube_12V1_0]
     207 : CSGPrim::descRange mn [ -8289.899  11642.131   9577.680 ] mx [ -7672.824  12566.609  11106.573 ] ce [ -7981.362  12104.370  10342.127    764.447 ] lvid 201 ridx    0 pidx   207 so[svacSurftube_12V1_0]
     208 : CSGPrim::descRange mn [ -8567.899  12560.998   8788.357 ] mx [ -8277.958  12987.085   9599.502 ] ce [ -8422.929  12774.041   9193.930    405.572 ] lvid 204 ridx    0 pidx   208 so[sSurftube_13V1_0]
     209 : CSGPrim::descRange mn [ -8565.816  12562.986   8789.138 ] mx [ -8280.017  12985.061   9598.650 ] ce [ -8422.916  12774.023   9193.895    404.756 ] lvid 203 ridx    0 pidx   209 so[svacSurftube_13V1_0]
     210 : CSGPrim::descRange mn [ -9015.550  12945.936   7107.303 ] mx [ -8531.777  13665.983   8786.338 ] ce [ -8773.664  13305.959   7946.820    839.517 ] lvid 206 ridx    0 pidx   210 so[sSurftube_14V1_0]
     211 : CSGPrim::descRange mn [ -9013.427  12947.959   7107.936 ] mx [ -8533.859  13663.897   8785.558 ] ce [ -8773.643  13305.928   7946.747    838.811 ] lvid 205 ridx    0 pidx   211 so[svacSurftube_14V1_0]
     212 : CSGPrim::descRange mn [ -9158.607  13658.636   6541.002 ] mx [ -9001.716  13882.941   7124.130 ] ce [ -9080.162  13770.789   6832.566    291.564 ] lvid 208 ridx    0 pidx   212 so[sSurftube_15V1_0]
     213 : CSGPrim::descRange mn [ -9156.473  13660.722   6541.583 ] mx [ -9003.840  13880.838   7123.499 ] ce [ -9080.156  13770.779   6832.541    290.958 ] lvid 207 ridx    0 pidx   213 so[svacSurftube_15V1_0]
     214 : CSGPrim::descRange mn [ -9472.977  13839.676   4763.257 ] mx [ -9121.090  14359.706   6539.500 ] ce [ -9297.033  14099.691   5651.378    888.121 ] lvid 210 ridx    0 pidx   214 so[sSurftube_16V1_0]
     215 : CSGPrim::descRange mn [ -9470.812  13841.779   4763.680 ] mx [ -9123.225  14357.559   6538.919 ] ce [ -9297.019  14099.669   5651.300    887.619 ] lvid 209 ridx    0 pidx   215 so[svacSurftube_16V1_0]
     216 : CSGPrim::descRange mn [ -9571.209  14352.518   4166.334 ] mx [ -9459.247  14508.685   4774.534 ] ce [ -9515.229  14430.602   4470.435    304.100 ] lvid 212 ridx    0 pidx   216 so[sSurftube_17V1_0]
     217 : CSGPrim::descRange mn [ -9569.037  14354.666   4166.705 ] mx [ -9461.411  14506.525   4774.111 ] ce [ -9515.225  14430.596   4470.408    303.703 ] lvid 211 ridx    0 pidx   217 so[svacSurftube_17V1_0]
     218 : CSGPrim::descRange mn [ -9746.177  14463.940   2326.499 ] mx [ -9532.717  14774.036   4165.377 ] ce [ -9639.447  14618.988   3245.938    919.439 ] lvid 214 ridx    0 pidx   218 so[sSurftube_18V1_0]
     219 : CSGPrim::descRange mn [ -9743.988  14466.100   2326.706 ] mx [ -9534.889  14771.852   4165.007 ] ce [ -9639.438  14618.976   3245.856    919.151 ] lvid 213 ridx    0 pidx   219 so[svacSurftube_18V1_0]
     220 : CSGPrim::descRange mn [ -9842.951  14766.943  -2332.007 ] mx [ -9732.511  14920.802   2332.007 ] ce [ -9787.730  14843.873      0.000   2332.007 ] lvid 216 ridx    0 pidx   220 so[sSurftube_19V1_0]
     221 : CSGPrim::descRange mn [ -9840.755  14769.128  -2331.800 ] mx [ -9734.698  14918.606   2331.800 ] ce [ -9787.727  14843.867      0.000   2331.800 ] lvid 215 ridx    0 pidx   221 so[svacSurftube_19V1_0]
     222 : CSGPrim::descRange mn [ -9746.177  14463.940  -4165.377 ] mx [ -9532.717  14774.036  -2326.499 ] ce [ -9639.447  14618.988  -3245.938    919.439 ] lvid 218 ridx    0 pidx   222 so[sSurftube_20V1_0]
     223 : CSGPrim::descRange mn [ -9743.988  14466.100  -4165.007 ] mx [ -9534.889  14771.852  -2326.706 ] ce [ -9639.438  14618.976  -3245.856    919.151 ] lvid 217 ridx    0 pidx   223 so[svacSurftube_20V1_0]
     224 : CSGPrim::descRange mn [ -9571.209  14352.518  -4774.534 ] mx [ -9459.247  14508.685  -4166.334 ] ce [ -9515.229  14430.602  -4470.435    304.100 ] lvid 220 ridx    0 pidx   224 so[sSurftube_21V1_0]
     225 : CSGPrim::descRange mn [ -9569.037  14354.666  -4774.111 ] mx [ -9461.411  14506.525  -4166.705 ] ce [ -9515.225  14430.596  -4470.408    303.703 ] lvid 219 ridx    0 pidx   225 so[svacSurftube_21V1_0]
     226 : CSGPrim::descRange mn [ -9472.977  13839.676  -6539.500 ] mx [ -9121.090  14359.706  -4763.257 ] ce [ -9297.033  14099.691  -5651.378    888.121 ] lvid 222 ridx    0 pidx   226 so[sSurftube_22V1_0]
     227 : CSGPrim::descRange mn [ -9470.812  13841.779  -6538.919 ] mx [ -9123.225  14357.559  -4763.680 ] ce [ -9297.019  14099.669  -5651.300    887.619 ] lvid 221 ridx    0 pidx   227 so[svacSurftube_22V1_0]
     228 : CSGPrim::descRange mn [ -9158.607  13658.636  -7124.130 ] mx [ -9001.716  13882.941  -6541.002 ] ce [ -9080.162  13770.789  -6832.566    291.564 ] lvid 224 ridx    0 pidx   228 so[sSurftube_23V1_0]
     229 : CSGPrim::descRange mn [ -9156.473  13660.722  -7123.499 ] mx [ -9003.840  13880.838  -6541.583 ] ce [ -9080.156  13770.779  -6832.541    290.958 ] lvid 223 ridx    0 pidx   229 so[svacSurftube_23V1_0]
     230 : CSGPrim::descRange mn [ -9015.550  12945.936  -8786.338 ] mx [ -8531.777  13665.983  -7107.303 ] ce [ -8773.664  13305.959  -7946.820    839.517 ] lvid 226 ridx    0 pidx   230 so[sSurftube_24V1_0]
     231 : CSGPrim::descRange mn [ -9013.427  12947.959  -8785.558 ] mx [ -8533.859  13663.897  -7107.936 ] ce [ -8773.643  13305.928  -7946.747    838.811 ] lvid 225 ridx    0 pidx   231 so[svacSurftube_24V1_0]
     232 : CSGPrim::descRange mn [ -8567.899  12560.998  -9599.502 ] mx [ -8277.958  12987.085  -8788.357 ] ce [ -8422.929  12774.041  -9193.930    405.572 ] lvid 228 ridx    0 pidx   232 so[sSurftube_25V1_0]
     233 : CSGPrim::descRange mn [ -8565.816  12562.986  -9598.650 ] mx [ -8280.017  12985.061  -8789.138 ] ce [ -8422.916  12774.023  -9193.895    404.756 ] lvid 227 ridx    0 pidx   233 so[svacSurftube_25V1_0]
     234 : CSGPrim::descRange mn [ -8291.958  11640.223 -11107.560 ] mx [ -7670.818  12568.598  -9576.828 ] ce [ -7981.388  12104.410 -10342.193    765.366 ] lvid 230 ridx    0 pidx   234 so[sSurftube_26V1_0]
     235 : CSGPrim::descRange mn [ -8289.899  11642.131 -11106.573 ] mx [ -7672.824  12566.609  -9577.680 ] ce [ -7981.362  12104.370 -10342.127    764.447 ] lvid 229 ridx    0 pidx   235 so[svacSurftube_26V1_0]
     236 : CSGPrim::descRange mn [ -7704.902  11324.543 -11603.169 ] mx [ -7462.666  11678.281 -11110.112 ] ce [ -7583.784  11501.412 -11356.641    246.528 ] lvid 232 ridx    0 pidx   236 so[sSurftube_27V1_0]
     237 : CSGPrim::descRange mn [ -7702.896  11326.422 -11602.140 ] mx [ -7464.652  11676.373 -11111.099 ] ce [ -7583.774  11501.397 -11356.619    245.521 ] lvid 231 ridx    0 pidx   237 so[svacSurftube_27V1_0]
     238 : CSGPrim::descRange mn [ -7476.854  10237.699 -12942.892 ] mx [ -6746.024  11332.427 -11575.762 ] ce [ -7111.438  10785.062 -12259.326    683.565 ] lvid 234 ridx    0 pidx   238 so[sSurftube_28V1_0]
     239 : CSGPrim::descRange mn [ -7474.867  10239.482 -12941.741 ] mx [ -6747.948  11330.549 -11576.791 ] ce [ -7111.407  10785.016 -12259.266    682.475 ] lvid 233 ridx    0 pidx   239 so[svacSurftube_28V1_0]
     240 : CSGPrim::descRange mn [ -6777.918   9867.566 -13380.993 ] mx [ -6501.967  10272.437 -12945.865 ] ce [ -6639.942  10070.002 -13163.430    217.564 ] lvid 236 ridx    0 pidx   240 so[sSurftube_29V1_0]
     241 : CSGPrim::descRange mn [ -6775.995   9869.316 -13379.806 ] mx [ -6503.868  10270.653 -12947.015 ] ce [ -6639.932  10069.984 -13163.410    216.396 ] lvid 235 ridx    0 pidx   241 so[svacSurftube_29V1_0]
     242 : CSGPrim::descRange mn [ -6516.375   8635.808 -14526.304 ] mx [ -5689.771   9875.785 -13349.387 ] ce [ -6103.073   9255.797 -13937.846    619.989 ] lvid 238 ridx    0 pidx   242 so[sSurftube_30V1_0]
     243 : CSGPrim::descRange mn [ -6514.474   8637.448 -14525.014 ] mx [ -5691.601   9874.036 -13350.574 ] ce [ -6103.037   9255.742 -13937.794    618.294 ] lvid 237 ridx    0 pidx   243 so[svacSurftube_30V1_0]
     244 : CSGPrim::descRange mn [ -5719.165   8218.428 -14898.371 ] mx [ -5414.560   8666.753 -14529.642 ] ce [ -5566.862   8442.590 -14714.006    224.163 ] lvid 240 ridx    0 pidx   244 so[sSurftube_31V1_0]
     245 : CSGPrim::descRange mn [ -5717.335   8220.030 -14897.049 ] mx [ -5416.365   8665.111 -14530.933 ] ce [ -5566.850   8442.570 -14713.990    222.541 ] lvid 239 ridx    0 pidx   245 so[svacSurftube_31V1_0]
     246 : CSGPrim::descRange mn [ -5434.003   7776.577 -15227.130 ] mx [ -5123.213   8234.282 -14876.314 ] ce [ -5278.608   8005.430 -15051.723    228.853 ] lvid 242 ridx    0 pidx   246 so[sSurftube_32V1_0]
     247 : CSGPrim::descRange mn [ -5432.198   7778.141 -15225.778 ] mx [ -5124.992   8232.680 -14877.637 ] ce [ -5278.595   8005.410 -15051.707    227.269 ] lvid 241 ridx    0 pidx   247 so[svacSurftube_32V1_0]
     248 : CSGPrim::descRange mn [ -5140.066   7322.181 -15529.800 ] mx [ -4823.594   7788.503 -15197.458 ] ce [ -4981.830   7555.342 -15363.629    233.161 ] lvid 244 ridx    0 pidx   248 so[sSurftube_33V1_0]
     249 : CSGPrim::descRange mn [ -5138.287   7323.705 -15528.421 ] mx [ -4825.347   7786.939 -15198.810 ] ce [ -4981.817   7555.322 -15363.615    231.617 ] lvid 243 ridx    0 pidx   249 so[svacSurftube_33V1_0]
     250 : CSGPrim::descRange mn [ -4850.937   6642.950 -15989.076 ] mx [ -4375.724   7350.016 -15533.369 ] ce [ -4613.331   6996.483 -15761.223    353.533 ] lvid 246 ridx    0 pidx   250 so[sSurftube_34V1_0]
     251 : CSGPrim::descRange mn [ -4849.184   6644.413 -15987.658 ] mx [ -4377.437   7348.492 -15534.748 ] ce [ -4613.311   6996.452 -15761.203    352.039 ] lvid 245 ridx    0 pidx   251 so[svacSurftube_34V1_0]
     252 : CSGPrim::descRange mn [ -4406.820   5468.594 -16662.848 ] mx [ -3601.379   6676.477 -16010.331 ] ce [ -4004.099   6072.535 -16336.590    603.941 ] lvid 248 ridx    0 pidx   252 so[sSurftube_35V1_0]
     253 : CSGPrim::descRange mn [ -4405.107   5469.952 -16661.373 ] mx [ -3603.022   6675.014 -16011.749 ] ce [ -4004.064   6072.482 -16336.561    602.531 ] lvid 247 ridx    0 pidx   253 so[svacSurftube_35V1_0]
     254 : CSGPrim::descRange mn [ -3612.491   4968.364 -16841.422 ] mx [ -3271.538   5471.814 -16605.303 ] ce [ -3442.014   5220.089 -16723.363    251.725 ] lvid 250 ridx    0 pidx   254 so[sSurftube_36V1_0]
     255 : CSGPrim::descRange mn [ -3610.848   4969.678 -16839.928 ] mx [ -3273.152   5470.457 -16606.777 ] ce [ -3442.000   5220.067 -16723.352    250.389 ] lvid 249 ridx    0 pidx   255 so[svacSurftube_36V1_0]
     256 : CSGPrim::descRange mn [ -3300.387   3736.076 -17346.883 ] mx [ -2458.994   4998.483 -16871.916 ] ce [ -2879.690   4367.280 -17109.398    631.203 ] lvid 252 ridx    0 pidx   256 so[sSurftube_37V1_0]
     257 : CSGPrim::descRange mn [ -3298.772   3737.280 -17345.348 ] mx [ -2460.536   4997.169 -16873.410 ] ce [ -2879.654   4367.225 -17109.379    629.944 ] lvid 251 ridx    0 pidx   257 so[svacSurftube_37V1_0]
     258 : CSGPrim::descRange mn [ -2470.439   2197.066 -17669.955 ] mx [ -1444.203   3739.801 -17278.676 ] ce [ -1957.321   2968.434 -17474.316    771.368 ] lvid 254 ridx    0 pidx   258 so[sSurftube_38V1_0]
     259 : CSGPrim::descRange mn [ -2468.897   2198.134 -17668.387 ] mx [ -1445.656   3738.597 -17280.211 ] ce [ -1957.276   2968.366 -17474.299    770.232 ] lvid 253 ridx    0 pidx   259 so[svacSurftube_38V1_0]
     260 : CSGPrim::descRange mn [  -212.439  -4469.167  17278.676 ] mx [   -18.739   -621.783  17855.316 ] ce [  -115.589  -2545.475  17566.996   1923.692 ] lvid 256 ridx    0 pidx   260 so[sSurftube_0V1_1]
     261 : CSGPrim::descRange mn [  -210.838  -4468.698  17280.211 ] mx [   -20.325   -621.910  17853.732 ] ce [  -115.582  -2545.304  17566.973   1923.394 ] lvid 255 ridx    0 pidx   261 so[svacSurftube_0V1_1]
     262 : CSGPrim::descRange mn [  -280.832  -5975.293  16871.916 ] mx [  -193.776  -4476.394  17346.883 ] ce [  -237.304  -5225.843  17109.398    749.450 ] lvid 258 ridx    0 pidx   262 so[sSurftube_1V1_1]
     263 : CSGPrim::descRange mn [  -279.225  -5974.692  16873.410 ] mx [  -195.378  -4476.862  17345.348 ] ce [  -237.301  -5225.777  17109.379    748.915 ] lvid 257 ridx    0 pidx   263 so[svacSurftube_1V1_1]
     264 : CSGPrim::descRange mn [  -306.551  -6541.676  16605.303 ] mx [  -260.735  -5950.936  16841.422 ] ce [  -283.643  -6246.306  16723.363    295.370 ] lvid 260 ridx    0 pidx   264 so[sSurftube_2V1_1]
     265 : CSGPrim::descRange mn [  -304.942  -6541.023  16606.777 ] mx [  -262.342  -5951.537  16839.928 ] ce [  -283.642  -6246.280  16723.352    294.743 ] lvid 259 ridx    0 pidx   265 so[svacSurftube_2V1_1]
     266 : CSGPrim::descRange mn [  -372.009  -7983.163  16010.331 ] mx [  -287.916  -6549.507  16662.848 ] ce [  -329.962  -7266.335  16336.590    716.828 ] lvid 262 ridx    0 pidx   266 so[sSurftube_3V1_1]
     267 : CSGPrim::descRange mn [  -370.393  -7982.384  16011.749 ] mx [  -289.526  -6550.159  16661.373 ] ce [  -329.959  -7266.271  16336.561    716.113 ] lvid 261 ridx    0 pidx   267 so[svacSurftube_3V1_1]
     268 : CSGPrim::descRange mn [  -408.607  -8789.113  15533.369 ] mx [  -351.727  -7954.729  15989.076 ] ce [  -380.167  -8371.922  15761.223    417.192 ] lvid 264 ridx    0 pidx   268 so[sSurftube_4V1_1]
     269 : CSGPrim::descRange mn [  -406.988  -8788.262  15534.748 ] mx [  -353.342  -7955.508  15987.658 ] ce [  -380.165  -8371.885  15761.203    416.377 ] lvid 263 ridx    0 pidx   269 so[svacSurftube_4V1_1]
     270 : CSGPrim::descRange mn [  -432.433  -9313.803  15197.458 ] mx [  -388.634  -8767.490  15529.800 ] ce [  -410.533  -9040.646  15363.629    273.156 ] lvid 266 ridx    0 pidx   270 so[sSurftube_5V1_1]
     271 : CSGPrim::descRange mn [  -430.812  -9312.903  15198.810 ] mx [  -390.253  -8768.342  15528.421 ] ce [  -410.532  -9040.623  15363.615    272.281 ] lvid 265 ridx    0 pidx   271 so[svacSurftube_5V1_1]
     272 : CSGPrim::descRange mn [  -456.655  -9847.218  14876.314 ] mx [  -413.324  -9311.216  15227.130 ] ce [  -434.990  -9579.217  15051.723    268.001 ] lvid 268 ridx    0 pidx   272 so[sSurftube_6V1_1]
     273 : CSGPrim::descRange mn [  -455.032  -9846.271  14877.637 ] mx [  -414.945  -9312.115  15225.778 ] ce [  -434.989  -9579.193  15051.707    267.078 ] lvid 267 ridx    0 pidx   273 so[svacSurftube_6V1_1]
     274 : CSGPrim::descRange mn [  -480.154 -10364.707  14529.642 ] mx [  -437.333  -9839.930  14898.371 ] ce [  -458.744 -10102.318  14714.006    262.389 ] lvid 270 ridx    0 pidx   274 so[sSurftube_7V1_1]
     275 : CSGPrim::descRange mn [  -478.529 -10363.716  14530.933 ] mx [  -438.956  -9840.876  14897.049 ] ce [  -458.743 -10102.296  14713.990    261.420 ] lvid 269 ridx    0 pidx   275 so[svacSurftube_7V1_1]
     276 : CSGPrim::descRange mn [  -545.849 -11811.424  13349.387 ] mx [  -460.012 -10339.362  14526.304 ] ce [  -502.931 -11075.393  13937.846    736.031 ] lvid 272 ridx    0 pidx   276 so[sSurftube_8V1_1]
     277 : CSGPrim::descRange mn [  -544.218 -11810.303  13350.574 ] mx [  -461.637 -10340.354  14525.014 ] ce [  -502.928 -11075.328  13937.794    734.975 ] lvid 271 ridx    0 pidx   277 so[svacSurftube_8V1_1]
     278 : CSGPrim::descRange mn [  -567.402 -12286.053  12945.865 ] mx [  -526.942 -11813.273  13380.993 ] ce [  -547.172 -12049.663  13163.430    236.390 ] lvid 274 ridx    0 pidx   278 so[sSurftube_9V1_1]
     279 : CSGPrim::descRange mn [  -565.769 -12284.891  12947.015 ] mx [  -528.573 -11814.395  13379.806 ] ce [  -547.171 -12049.643  13163.410    235.248 ] lvid 273 ridx    0 pidx   279 so[svacSurftube_9V1_1]
     280 : CSGPrim::descRange mn [  -624.998 -13554.427  11575.762 ] mx [  -547.054 -12256.170  12942.892 ] ce [  -586.026 -12905.299  12259.326    683.565 ] lvid 276 ridx    0 pidx   280 so[sSurftube_10V1_1]
     281 : CSGPrim::descRange mn [  -623.360 -13553.150  11576.791 ] mx [  -548.687 -12257.331  12941.741 ] ce [  -586.024 -12905.240  12259.266    682.475 ] lvid 275 ridx    0 pidx   281 so[svacSurftube_10V1_1]
     282 : CSGPrim::descRange mn [  -643.791 -13968.272  11110.112 ] mx [  -606.109 -13556.677  11603.169 ] ce [  -624.950 -13762.475  11356.641    246.528 ] lvid 278 ridx    0 pidx   282 so[sSurftube_11V1_1]
     283 : CSGPrim::descRange mn [  -642.151 -13966.961  11111.099 ] mx [  -607.748 -13557.953  11602.140 ] ce [  -624.950 -13762.457  11356.619    245.521 ] lvid 277 ridx    0 pidx   283 so[svacSurftube_11V1_1]
     284 : CSGPrim::descRange mn [  -692.168 -15033.616   9576.828 ] mx [  -623.263 -13934.416  11107.560 ] ce [  -657.715 -14484.016  10342.193    765.366 ] lvid 280 ridx    0 pidx   284 so[sSurftube_12V1_1]
     285 : CSGPrim::descRange mn [  -690.524 -15032.209   9577.680 ] mx [  -624.902 -13935.727  11106.573 ] ce [  -657.713 -14483.968  10342.127    764.447 ] lvid 279 ridx    0 pidx   285 so[svacSurftube_12V1_1]
     286 : CSGPrim::descRange mn [  -714.907 -15534.373   8788.357 ] mx [  -673.295 -15036.206   9599.502 ] ce [  -694.101 -15285.289   9193.930    405.572 ] lvid 282 ridx    0 pidx   286 so[sSurftube_13V1_1]
     287 : CSGPrim::descRange mn [  -713.261 -15532.924   8789.138 ] mx [  -674.939 -15037.613   9598.650 ] ce [  -694.100 -15285.269   9193.895    404.756 ] lvid 281 ridx    0 pidx   287 so[svacSurftube_13V1_1]
     288 : CSGPrim::descRange mn [  -751.797 -16346.736   7107.303 ] mx [  -694.211 -15496.818   8786.338 ] ce [  -723.004 -15921.777   7946.820    839.517 ] lvid 284 ridx    0 pidx   288 so[sSurftube_14V1_1]
     289 : CSGPrim::descRange mn [  -750.147 -16345.212   7107.936 ] mx [  -695.857 -15498.268   8785.558 ] ce [  -723.002 -15921.740   7946.747    838.811 ] lvid 283 ridx    0 pidx   289 so[svacSurftube_14V1_1]
     290 : CSGPrim::descRange mn [  -763.585 -16606.346   6541.002 ] mx [  -732.937 -16349.628   7124.130 ] ce [  -748.261 -16477.986   6832.566    291.564 ] lvid 286 ridx    0 pidx   290 so[sSurftube_15V1_1]
     291 : CSGPrim::descRange mn [  -761.935 -16604.801   6541.583 ] mx [  -734.586 -16351.152   7123.499 ] ce [  -748.260 -16477.977   6832.541    290.958 ] lvid 285 ridx    0 pidx   291 so[svacSurftube_15V1_1]
     292 : CSGPrim::descRange mn [  -789.491 -17176.838   4763.257 ] mx [  -742.774 -16566.260   6539.500 ] ce [  -766.133 -16871.549   5651.378    888.121 ] lvid 288 ridx    0 pidx   292 so[sSurftube_16V1_1]
     293 : CSGPrim::descRange mn [  -787.839 -17175.240   4763.680 ] mx [  -744.424 -16567.805   6538.919 ] ce [  -766.131 -16871.523   5651.300    887.619 ] lvid 287 ridx    0 pidx   293 so[svacSurftube_16V1_1]
     294 : CSGPrim::descRange mn [  -797.586 -17355.104   4166.334 ] mx [  -770.640 -17179.922   4774.534 ] ce [  -784.113 -17267.512   4470.435    304.100 ] lvid 290 ridx    0 pidx   294 so[sSurftube_17V1_1]
     295 : CSGPrim::descRange mn [  -795.933 -17353.492   4166.705 ] mx [  -772.293 -17181.520   4774.111 ] ce [  -784.113 -17267.506   4470.408    303.703 ] lvid 289 ridx    0 pidx   295 so[svacSurftube_17V1_1]
     296 : CSGPrim::descRange mn [  -812.005 -17672.621   2326.499 ] mx [  -776.694 -17313.248   4165.377 ] ce [  -794.349 -17492.934   3245.938    919.439 ] lvid 292 ridx    0 pidx   296 so[sSurftube_18V1_1]
     297 : CSGPrim::descRange mn [  -810.350 -17670.980   2326.706 ] mx [  -778.348 -17314.859   4165.007 ] ce [  -794.349 -17492.920   3245.856    919.151 ] lvid 291 ridx    0 pidx   297 so[svacSurftube_18V1_1]
     298 : CSGPrim::descRange mn [  -819.979 -17848.240  -2332.007 ] mx [  -793.159 -17675.818   2332.007 ] ce [  -806.569 -17762.029      0.000   2332.007 ] lvid 294 ridx    0 pidx   298 so[sSurftube_19V1_1]
     299 : CSGPrim::descRange mn [  -818.324 -17846.584  -2331.800 ] mx [  -794.813 -17677.459   2331.800 ] ce [  -806.569 -17762.021      0.000   2331.800 ] lvid 293 ridx    0 pidx   299 so[svacSurftube_19V1_1]
     300 : CSGPrim::descRange mn [  -812.005 -17672.621  -4165.377 ] mx [  -776.694 -17313.248  -2326.499 ] ce [  -794.349 -17492.934  -3245.938    919.439 ] lvid 296 ridx    0 pidx   300 so[sSurftube_20V1_1]
     301 : CSGPrim::descRange mn [  -810.350 -17670.980  -4165.007 ] mx [  -778.348 -17314.859  -2326.706 ] ce [  -794.349 -17492.920  -3245.856    919.151 ] lvid 295 ridx    0 pidx   301 so[svacSurftube_20V1_1]
     302 : CSGPrim::descRange mn [  -797.586 -17355.104  -4774.534 ] mx [  -770.640 -17179.922  -4166.334 ] ce [  -784.113 -17267.512  -4470.435    304.100 ] lvid 298 ridx    0 pidx   302 so[sSurftube_21V1_1]
     303 : CSGPrim::descRange mn [  -795.933 -17353.492  -4774.111 ] mx [  -772.293 -17181.520  -4166.705 ] ce [  -784.113 -17267.506  -4470.408    303.703 ] lvid 297 ridx    0 pidx   303 so[svacSurftube_21V1_1]
     304 : CSGPrim::descRange mn [  -789.491 -17176.838  -6539.500 ] mx [  -742.774 -16566.260  -4763.257 ] ce [  -766.133 -16871.549  -5651.378    888.121 ] lvid 300 ridx    0 pidx   304 so[sSurftube_22V1_1]
     305 : CSGPrim::descRange mn [  -787.839 -17175.240  -6538.919 ] mx [  -744.424 -16567.805  -4763.680 ] ce [  -766.131 -16871.523  -5651.300    887.619 ] lvid 299 ridx    0 pidx   305 so[svacSurftube_22V1_1]
     306 : CSGPrim::descRange mn [  -763.585 -16606.346  -7124.130 ] mx [  -732.937 -16349.628  -6541.002 ] ce [  -748.261 -16477.986  -6832.566    291.564 ] lvid 302 ridx    0 pidx   306 so[sSurftube_23V1_1]
     307 : CSGPrim::descRange mn [  -761.935 -16604.801  -7123.499 ] mx [  -734.586 -16351.152  -6541.583 ] ce [  -748.260 -16477.977  -6832.541    290.958 ] lvid 301 ridx    0 pidx   307 so[svacSurftube_23V1_1]
     308 : CSGPrim::descRange mn [  -751.797 -16346.736  -8786.338 ] mx [  -694.211 -15496.818  -7107.303 ] ce [  -723.004 -15921.777  -7946.820    839.517 ] lvid 304 ridx    0 pidx   308 so[sSurftube_24V1_1]
     309 : CSGPrim::descRange mn [  -750.147 -16345.212  -8785.558 ] mx [  -695.857 -15498.268  -7107.936 ] ce [  -723.002 -15921.740  -7946.747    838.811 ] lvid 303 ridx    0 pidx   309 so[svacSurftube_24V1_1]
     310 : CSGPrim::descRange mn [  -714.907 -15534.373  -9599.502 ] mx [  -673.295 -15036.206  -8788.357 ] ce [  -694.101 -15285.289  -9193.930    405.572 ] lvid 306 ridx    0 pidx   310 so[sSurftube_25V1_1]
     311 : CSGPrim::descRange mn [  -713.261 -15532.924  -9598.650 ] mx [  -674.939 -15037.613  -8789.138 ] ce [  -694.100 -15285.269  -9193.895    404.756 ] lvid 305 ridx    0 pidx   311 so[svacSurftube_25V1_1]
     312 : CSGPrim::descRange mn [  -692.168 -15033.616 -11107.560 ] mx [  -623.263 -13934.416  -9576.828 ] ce [  -657.715 -14484.016 -10342.193    765.366 ] lvid 308 ridx    0 pidx   312 so[sSurftube_26V1_1]
     313 : CSGPrim::descRange mn [  -690.524 -15032.209 -11106.573 ] mx [  -624.902 -13935.727  -9577.680 ] ce [  -657.713 -14483.968 -10342.127    764.447 ] lvid 307 ridx    0 pidx   313 so[svacSurftube_26V1_1]
     314 : CSGPrim::descRange mn [  -643.791 -13968.272 -11603.169 ] mx [  -606.109 -13556.677 -11110.112 ] ce [  -624.950 -13762.475 -11356.641    246.528 ] lvid 310 ridx    0 pidx   314 so[sSurftube_27V1_1]
     315 : CSGPrim::descRange mn [  -642.151 -13966.961 -11602.140 ] mx [  -607.748 -13557.953 -11111.099 ] ce [  -624.950 -13762.457 -11356.619    245.521 ] lvid 309 ridx    0 pidx   315 so[svacSurftube_27V1_1]
     316 : CSGPrim::descRange mn [  -624.998 -13554.427 -12942.892 ] mx [  -547.054 -12256.170 -11575.762 ] ce [  -586.026 -12905.299 -12259.326    683.565 ] lvid 312 ridx    0 pidx   316 so[sSurftube_28V1_1]
     317 : CSGPrim::descRange mn [  -623.360 -13553.150 -12941.741 ] mx [  -548.687 -12257.331 -11576.791 ] ce [  -586.024 -12905.240 -12259.266    682.475 ] lvid 311 ridx    0 pidx   317 so[svacSurftube_28V1_1]
     318 : CSGPrim::descRange mn [  -567.402 -12286.053 -13380.993 ] mx [  -526.942 -11813.273 -12945.865 ] ce [  -547.172 -12049.663 -13163.430    236.390 ] lvid 314 ridx    0 pidx   318 so[sSurftube_29V1_1]
     319 : CSGPrim::descRange mn [  -565.769 -12284.891 -13379.806 ] mx [  -528.573 -11814.395 -12947.015 ] ce [  -547.171 -12049.643 -13163.410    235.248 ] lvid 313 ridx    0 pidx   319 so[svacSurftube_29V1_1]
     320 : CSGPrim::descRange mn [  -545.849 -11811.424 -14526.304 ] mx [  -460.012 -10339.362 -13349.387 ] ce [  -502.931 -11075.393 -13937.846    736.031 ] lvid 316 ridx    0 pidx   320 so[sSurftube_30V1_1]
     321 : CSGPrim::descRange mn [  -544.218 -11810.303 -14525.014 ] mx [  -461.637 -10340.354 -13350.574 ] ce [  -502.928 -11075.328 -13937.794    734.975 ] lvid 315 ridx    0 pidx   321 so[svacSurftube_30V1_1]
     322 : CSGPrim::descRange mn [  -480.154 -10364.707 -14898.371 ] mx [  -437.333  -9839.930 -14529.642 ] ce [  -458.744 -10102.318 -14714.006    262.389 ] lvid 318 ridx    0 pidx   322 so[sSurftube_31V1_1]
     323 : CSGPrim::descRange mn [  -478.529 -10363.716 -14897.049 ] mx [  -438.956  -9840.876 -14530.933 ] ce [  -458.743 -10102.296 -14713.990    261.420 ] lvid 317 ridx    0 pidx   323 so[svacSurftube_31V1_1]
     324 : CSGPrim::descRange mn [  -456.655  -9847.218 -15227.130 ] mx [  -413.324  -9311.216 -14876.314 ] ce [  -434.990  -9579.217 -15051.723    268.001 ] lvid 320 ridx    0 pidx   324 so[sSurftube_32V1_1]
     325 : CSGPrim::descRange mn [  -455.032  -9846.271 -15225.778 ] mx [  -414.945  -9312.115 -14877.637 ] ce [  -434.989  -9579.193 -15051.707    267.078 ] lvid 319 ridx    0 pidx   325 so[svacSurftube_32V1_1]
     326 : CSGPrim::descRange mn [  -432.433  -9313.803 -15529.800 ] mx [  -388.634  -8767.490 -15197.458 ] ce [  -410.533  -9040.646 -15363.629    273.156 ] lvid 322 ridx    0 pidx   326 so[sSurftube_33V1_1]
     327 : CSGPrim::descRange mn [  -430.812  -9312.903 -15528.421 ] mx [  -390.253  -8768.342 -15198.810 ] ce [  -410.532  -9040.623 -15363.615    272.281 ] lvid 321 ridx    0 pidx   327 so[svacSurftube_33V1_1]
     328 : CSGPrim::descRange mn [  -408.607  -8789.113 -15989.076 ] mx [  -351.727  -7954.729 -15533.369 ] ce [  -380.167  -8371.922 -15761.223    417.192 ] lvid 324 ridx    0 pidx   328 so[sSurftube_34V1_1]
     329 : CSGPrim::descRange mn [  -406.988  -8788.262 -15987.658 ] mx [  -353.342  -7955.508 -15534.748 ] ce [  -380.165  -8371.885 -15761.203    416.377 ] lvid 323 ridx    0 pidx   329 so[svacSurftube_34V1_1]
     330 : CSGPrim::descRange mn [  -372.009  -7983.163 -16662.848 ] mx [  -287.916  -6549.507 -16010.331 ] ce [  -329.962  -7266.335 -16336.590    716.828 ] lvid 326 ridx    0 pidx   330 so[sSurftube_35V1_1]
     331 : CSGPrim::descRange mn [  -370.393  -7982.384 -16661.373 ] mx [  -289.526  -6550.159 -16011.749 ] ce [  -329.959  -7266.271 -16336.561    716.113 ] lvid 325 ridx    0 pidx   331 so[svacSurftube_35V1_1]
     332 : CSGPrim::descRange mn [  -306.551  -6541.676 -16841.422 ] mx [  -260.735  -5950.936 -16605.303 ] ce [  -283.643  -6246.306 -16723.363    295.370 ] lvid 328 ridx    0 pidx   332 so[sSurftube_36V1_1]
     333 : CSGPrim::descRange mn [  -304.942  -6541.023 -16839.928 ] mx [  -262.342  -5951.537 -16606.777 ] ce [  -283.642  -6246.280 -16723.352    294.743 ] lvid 327 ridx    0 pidx   333 so[svacSurftube_36V1_1]
     334 : CSGPrim::descRange mn [  -280.832  -5975.293 -17346.883 ] mx [  -193.776  -4476.394 -16871.916 ] ce [  -237.304  -5225.843 -17109.398    749.450 ] lvid 330 ridx    0 pidx   334 so[sSurftube_37V1_1]
     335 : CSGPrim::descRange mn [  -279.225  -5974.692 -17345.348 ] mx [  -195.378  -4476.862 -16873.410 ] ce [  -237.301  -5225.777 -17109.379    748.915 ] lvid 329 ridx    0 pidx   335 so[svacSurftube_37V1_1]
     336 : CSGPrim::descRange mn [  -212.439  -4469.167 -17669.955 ] mx [  -110.151  -2634.829 -17278.676 ] ce [  -161.295  -3551.998 -17474.316    917.169 ] lvid 332 ridx    0 pidx   336 so[sSurftube_38V1_1]
     337 : CSGPrim::descRange mn [  -210.838  -4468.698 -17668.387 ] mx [  -111.745  -2635.135 -17280.211 ] ce [  -161.292  -3551.917 -17474.299    916.781 ] lvid 331 ridx    0 pidx   337 so[svacSurftube_38V1_1]
    ]CSGPrim::Desc numPrim 338
    ]CSGFoundry::descPrimRange solidIdx 11
    [CSGFoundry::descPrimRange num_solid 12
    ]CSGFoundryLoadTest::descPrimRange
























LVID=124 TEST=findSubMesh ~/o/sysrap/tests/SSceneLoadTest.sh::

    SSceneLoadTest::findSubMesh LVID 124
    SScene::findSubMesh lvid 124 num_mg 12
    ]SSceneLoadTest::findSubMesh LVID 124 subs.size 2
    [SScene::descSubMesh
    [SMeshGroup::DescSubMesh num_subs 2
       0 : SMesh::descRange name[-]  lvid 124 mn [ -1336.770  -1336.749  18667.018 ] mx [  1336.786   1336.788  19202.975 ] ce [     0.008      0.019  18934.996   1336.778 ] so[Waterdistributor_2]
       1 : SMesh::descRange name[-]  lvid 124 mn [ -1336.770  -1336.749 -19105.982 ] mx [  1336.786   1336.788 -18570.025 ] ce [     0.008      0.019 -18838.004   1336.778 ] so[Waterdistributor_2]
    ]SMeshGroup::DescSubMesh
    ]SScene::descSubMesh


LVID=124 TEST=getMeshPrim ~/o/CSG/tests/CSGFoundryLoadTest.sh::

    [CSGFoundryLoadTest::getMeshPrim LVID 124
    2025-12-15 14:40:00.949 INFO  [2660084] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest 301158ef96cbf4d61f96ed76aee59990 dynamic 301158ef96cbf4d61f96ed76aee59990
    ]CSGFoundryLoadTest::getMeshPrim LVID 124
    [CSGPrim::Desc num_prim 2
       0 : CSGPrim numNode/node/tran/plan  12 18814 7771    0 sbtOffset/meshIdx/repeatIdx/primIdx   13  124    0   13 mn (-1219.998,-246.607,17500.000)  mx (1219.998,246.607,20370.000) 
       1 : CSGPrim numNode/node/tran/plan  12 18838 7793    0 sbtOffset/meshIdx/repeatIdx/primIdx   15  124    0   15 mn (-1219.998,-246.607,-20273.000)  mx (1219.998,246.607,-17403.000) 
    ]CSGPrim::Desc num_prim 2


LVID=32 TEST=findSubMesh ~/o/sysrap/tests/SSceneLoadTest.sh::

    [SSceneLoadTest::findSubMesh LVID 32
    SScene::findSubMesh lvid 32 num_mg 12
    ]SSceneLoadTest::findSubMesh LVID 32 subs.size 1
    [SScene::descSubMesh
    [SMeshGroup::DescSubMesh num_subs 1
       0 : SMesh::descRange name[-]  lvid  32 mn [  -661.993   -125.000 -21073.482 ] mx [   136.645    125.000 -19120.000 ] ce [  -262.674      0.000 -20096.742    976.741 ] so[WaterDistributorPartIIIUnion]
    ]SMeshGroup::DescSubMesh
    ]SScene::descSubMesh


LVID=32 TEST=getMeshPrim ~/o/CSG/tests/CSGFoundryLoadTest.sh::

    (ok) A[blyth@localhost CSG]$ LVID=32 TEST=getMeshPrim ~/o/CSG/tests/CSGFoundryLoadTest.sh
    [CSGFoundryLoadTest::getMeshPrim LVID 32
    2025-12-15 14:44:59.814 INFO  [2660357] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest 301158ef96cbf4d61f96ed76aee59990 dynamic 301158ef96cbf4d61f96ed76aee59990
    ]CSGFoundryLoadTest::getMeshPrim LVID 32
    [CSGPrim::Desc num_prim 1
       0 : CSGPrim numNode/node/tran/plan   6 18688 7695    0 sbtOffset/meshIdx/repeatIdx/primIdx    3   32    0    3 mn (-9103.062,-20790.500,-19998.969)  mx (5702.666,21247.500,418.500) 
    ]CSGPrim::Desc num_prim 1
    (ok) A[blyth@localhost CSG]$ 




::

    2025-12-15 13:51:17.529 INFO  [2652859] [CSGFoundry::getFrame@3617] [CSGFoundry__getFrame_VERBOSE] YES[fr.desc
    sframe::desc inst 0 frs WaterDistributorPartIIIUnion:0:-2
     tree -
     dynamic -
     ekvid - ek - ev -
     ce  (-1717.812,228.500,-9502.200,21019.000)  is_zero 0
     m2w ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) (-1717.812,228.500,-9502.200, 1.000) 
     w2m ( 1.000, 0.000, 0.000, 0.000) ( 0.000, 1.000, 0.000, 0.000) ( 0.000, 0.000, 1.000, 0.000) (1717.812,-228.500,9502.200, 1.000) 
     midx   32 mord    0 gord   -2
     inst    0
     ix0     0 ix1     0 iy0     0 iy1     0 iz0     0 iz1     0 num_photon    0
     ins     0 gas     0 sensor_identifier        0 sensor_index      0
     propagate_epsilon    0.05000 is_hostside_simtrace NO
    ]fr.desc







WaterDistributorPartIIIUnion transforms all over the place
---------------------------------------------------------------

::

    sn::desc_xform_full pid   58 idx   58 lvid  32 tag no xform Y 
     t                                                      v                                                      tv                                                    
     1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000                1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000                0.0000     0.0000     1.0000     0.0000    
     0.0000     0.0000     0.0000     1.0000                0.0000     0.0000     0.0000     1.0000                0.0000     0.0000     0.0000     1.0000    
     mn    -100.0000    -100.0000    -100.0000    1.0000      
     mx    100.0000     100.0000     100.0000     1.0000      
     t_mn  -100.0000    -100.0000    -100.0000    1.0000      
     t_mx  100.0000     100.0000     100.0000     1.0000      

    sn::desc_xform_full pid   59 idx   59 lvid  32 tag cu xform Y 
     t                                                      v                                                      tv                                                    
     0.8910     0.0000     -0.4540    0.0000                0.8910     -0.0000    0.4540     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                -0.0000    1.0000     -0.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.4540     0.0000     0.8910     0.0000                -0.4540    -0.0000    0.8910     -0.0000               0.0000     0.0000     1.0000     0.0000    
     -8916.7089 0.0000     -17235.7039 1.0000                120.0000   -0.0000    19405.2257 1.0000                0.0000     0.0000     0.0000     1.0000    
     mn    -100.0000    -100.0000    -100.0000    1.0000      
     mx    100.0000     100.0000     100.0000     1.0000      
     t_mn  -9051.2086   -100.0000    -17279.4055  1.0000      
     t_mx  -8782.2092   100.0000     -17192.0023  1.0000      

    sn::desc_xform_full pid   60 idx   60 lvid  32 tag cu xform Y 
     t                                                      v                                                      tv                                                    
     0.9613     0.0000     0.2756     0.0000                0.9613     -0.0000    -0.2756    -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     1.0000     0.0000     0.0000                -0.0000    1.0000     -0.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     -0.2756    0.0000     0.9613     0.0000                0.2756     -0.0000    0.9613     -0.0000               0.0000     0.0000     1.0000     0.0000    
     5481.0851  0.0000     -19422.8997 1.0000                84.9195    -0.0000    20181.2813 1.0000                0.0000     0.0000     -0.0000    1.0000    
     mn    -100.0000    -100.0000    -100.0000    1.0000      
     mx    100.0000     100.0000     100.0000     1.0000      
     t_mn  5412.5227    -100.0000    -19546.5896  1.0000      
     t_mx  5549.6476    100.0000     -19299.2098  1.0000      

    sn::desc_xform_full pid   61 idx   61 lvid  32 tag to xform Y 
     t                                                      v                                                      tv                                                    
     -1.0000    0.0000     -0.0000    0.0000                -1.0000    -0.0000    0.0000     -0.0000               1.0000     0.0000     -0.0000    0.0000    
     -0.0000    0.0000     1.0000     0.0000                -0.0000    0.0000     1.0000     0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     1.0000     -0.0000    0.0000                -0.0000    1.0000     -0.0000    -0.0000               -0.0000    0.0000     1.0000     0.0000    
     213.0000   -20724.0000 0.0000     1.0000                213.0000   -0.0000    20724.0000 1.0000                0.0000     0.0000     0.0000     1.0000    
     mn    -100.0000    -100.0000    -100.0000    1.0000      
     mx    100.0000     100.0000     100.0000     1.0000      
     t_mn  313.0000     -20824.0000  -100.0000    1.0000      
     t_mx  113.0000     -20624.0000  100.0000     1.0000      

    sn::desc_xform_full pid   62 idx   62 lvid  32 tag to xform Y 
     t                                                      v                                                      tv                                                    
     1.0000     0.0000     0.0000     0.0000                1.0000     -0.0000    0.0000     -0.0000               1.0000     0.0000     0.0000     0.0000    
     0.0000     0.0000     1.0000     0.0000                -0.0000    0.0000     -1.0000    0.0000                0.0000     1.0000     0.0000     0.0000    
     0.0000     -1.0000    0.0000     0.0000                -0.0000    1.0000     0.0000     -0.0000               0.0000     0.0000     1.0000     0.0000    
     -662.0000  21181.0000 -0.0000    1.0000                662.0000   0.0000     21181.0000 1.0000                0.0000     0.0000     0.0000     1.0000    
     mn    -100.0000    -100.0000    -100.0000    1.0000      
     mx    100.0000     100.0000     100.0000     1.0000      
     t_mn  -762.0000    21281.0000   -100.0000    1.0000      
     t_mx  -562.0000    21081.0000   100.0000     1.0000      





::


    (ok) A[blyth@localhost desc]$ TEST=desc_solid LVID=32 ~/o/sysrap/tests/stree_load_test.sh 
    stree::desc_solid lvid 32 lvn WaterDistributorPartIIIUnion root Y sn::rbrief
      0 : sn::brief tc   11 cm  0 lv  32 xf Y pa N bb N pt N nc  5 dp  0 tg co bb.desc -
      1 : sn::brief tc  125 cm  0 lv  32 xf Y pa N bb Y pt Y nc  0 dp  0 tg no bb.desc [ -0.000, -0.000, -0.000,  0.000,  0.000,  0.000] ALL_ZERO DEGENERATE
      1 : sn::brief tc  124 cm  0 lv  32 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cu bb.desc [-59.252,-59.252,-294.190, 59.252, 59.252,294.190]
      1 : sn::brief tc  124 cm  0 lv  32 xf Y pa Y bb Y pt Y nc  0 dp  0 tg cu bb.desc [-63.924,-63.924,-580.955, 63.924, 63.924,580.955]
      1 : sn::brief tc  116 cm  0 lv  32 xf Y pa Y bb Y pt Y nc  0 dp  0 tg to bb.desc [-349.500,-349.500,-66.500,247.134,  0.000, 66.500]
      1 : sn::brief tc  116 cm  0 lv  32 xf Y pa Y bb Y pt Y nc  0 dp  0 tg to bb.desc [  0.000,201.879,-66.500,295.924,418.500, 66.500]
    st.find_lvid_nodes (structural nodes)  lvid 32 src N nodes.size 1
     nidx 65740
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

     sn::Desc(nds) (csg nodes) lvid 32 num_nds 8
    sn::Desc num_nd 8-
    sn::desc pid   55 idx   55 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag cy
    sn::desc pid   56 idx   56 typecode 105 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag cy
    sn::desc pid   57 idx   57 typecode  11 num_node   6 num_leaf   5 maxdepth  1 is_positive_form Y lvid  32 xform Y tag co
    sn::desc pid   58 idx   58 typecode 125 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag no
    sn::desc pid   59 idx   59 typecode 124 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag cu
    sn::desc pid   60 idx   60 typecode 124 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag cu
    sn::desc pid   61 idx   61 typecode 116 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag to
    sn::desc pid   62 idx   62 typecode 116 num_node   1 num_leaf   1 maxdepth  0 is_positive_form Y lvid  32 xform Y tag to

     sn::DescXform(nds) (csg nodes) lvid 32 num_nds 8sn::DescXform num_nd 8-
    sn::desc_xform pid   55 idx   55 lvid  32 xform Y  t      0.0000     0.0000     0.0000     1.0000 v      0.0000     0.0000     0.0000     1.0000 tag cy
    sn::desc_xform pid   56 idx   56 lvid  32 xform Y  t      0.0000     0.0000     0.0000     1.0000 v      0.0000     0.0000     0.0000     1.0000 tag cy
    sn::desc_xform pid   57 idx   57 lvid  32 xform Y  t      0.0000     0.0000     0.0000     1.0000 v      0.0000     0.0000     0.0000     1.0000 tag co
    sn::desc_xform pid   58 idx   58 lvid  32 xform Y  t      0.0000     0.0000     0.0000     1.0000 v      0.0000     0.0000     0.0000     1.0000 tag no
    sn::desc_xform pid   59 idx   59 lvid  32 xform Y  t  -8916.7089     0.0000 -17235.7039     1.0000 v    120.0000    -0.0000 19405.2257     1.0000 tag cu
    sn::desc_xform pid   60 idx   60 lvid  32 xform Y  t   5481.0851     0.0000 -19422.8997     1.0000 v     84.9195    -0.0000 20181.2813     1.0000 tag cu
    sn::desc_xform pid   61 idx   61 lvid  32 xform Y  t    213.0000 -20724.0000     0.0000     1.0000 v    213.0000    -0.0000 20724.0000     1.0000 tag to
    sn::desc_xform pid   62 idx   62 lvid  32 xform Y  t   -662.0000 21181.0000    -0.0000     1.0000 v    662.0000     0.0000 21181.0000     1.0000 tag to

    (ok) A[blyth@localhost desc]$ 



curly


::


    In [1]: f.stree__get_frame_global_LVID_32_contrib_tr
    Out[1]: 
    array([[[     0.891,      0.   ,     -0.454,      0.   ],
            [     0.   ,      1.   ,      0.   ,      0.   ],
            [     0.454,      0.   ,      0.891,      0.   ],
            [ -8916.709,      0.   , -17235.704,      1.   ]],

           [[     0.961,      0.   ,      0.276,      0.   ],
            [     0.   ,      1.   ,      0.   ,      0.   ],
            [    -0.276,      0.   ,      0.961,      0.   ],
            [  5481.085,      0.   , -19422.9  ,      1.   ]],

           [[    -1.   ,      0.   ,     -0.   ,      0.   ],
            [    -0.   ,      0.   ,      1.   ,      0.   ],
            [     0.   ,      1.   ,     -0.   ,      0.   ],
            [   213.   , -20724.   ,      0.   ,      1.   ]],

           [[     1.   ,      0.   ,      0.   ,      0.   ],
            [     0.   ,      0.   ,      1.   ,      0.   ],
            [     0.   ,     -1.   ,      0.   ,      0.   ],
            [  -662.   ,  21181.   ,     -0.   ,      1.   ]]])

    In [2]: 


    223     double offset2 = dz2 * cos(-16*deg);
    224 
    225     // Position vectors
    226     G4ThreeVector positions[] = {
    227         G4ThreeVector(0, 0, -19120),                                                          // Flange
    228         G4ThreeVector(-120, 0, -19120 - 50*mm - offset1),                                    // CutTube1
    229         G4ThreeVector(-240 + dz2 * sin(16*deg), 0, -19120 - 50*mm - offset1 * 2 - offset2), // CutTube2
    230         G4ThreeVector(70 - r_main1, 0, -20724),                                             // Torus1
    231         G4ThreeVector(70 - 449 - 283, 0, -21181)                                            // Torus2
    232     };



    In [2]: 70 - 449 - 283
    Out[2]: -662




    233 
    234     // Component names for debugging
    235     const char* component_names[] = {"Flange", "CutTube1", "CutTube2", "Torus1", "Torus2"};
    236 
    237     // Create MultiUnion and add all components in a loop
    238     G4MultiUnion* unionSolid = new G4MultiUnion("WaterDistributorPartIIIUnion");
    239 
    240     for (int i = 0; i < 5; ++i) {
    241         // Create rotation matrix for this component
    242         G4RotationMatrix rotation;
    243         if (rotX_angles[i] != 0) {
    244             rotation.rotateX(rotX_angles[i]);
    245         }
    246         if (rotY_angles[i] != 0) {
    247             rotation.rotateY(rotY_angles[i]);
    248         }
    249 
    250         // Create transform and add node
    251         G4Transform3D transform(rotation, positions[i]);
    252         unionSolid->AddNode(*solids[i], transform);
    253     }













::

    zeta:junosw blyth$ git l -n2
    commit 9ee1bf72090b8ba81934f7175a7a5c1806e5e00f (HEAD -> yupd_bottompipe_adjust, origin/yupd_bottompipe_adjust)
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Nov 4 16:49:23 2025 +0800

        Adjust the logical position of the water distribution pipe section

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc

    commit 5a4bf902b0df2dafcdb2330d87f3ee2b08103f82
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Wed Oct 15 20:38:20 2025 +0800

        Add segmented water distributor implementation, support switching between old and new implementations.

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc
    zeta:junosw blyth$ git l -n5
    commit 9ee1bf72090b8ba81934f7175a7a5c1806e5e00f (HEAD -> yupd_bottompipe_adjust, origin/yupd_bottompipe_adjust)
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Tue Nov 4 16:49:23 2025 +0800

        Adjust the logical position of the water distribution pipe section

    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc

    commit 5a4bf902b0df2dafcdb2330d87f3ee2b08103f82
    Author: yupeidong <yupd@ihep.ac.cn>
    Date:   Wed Oct 15 20:38:20 2025 +0800

        Add segmented water distributor implementation, support switching between old and new implementations.

    M       Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    M       Simulation/DetSimV2/CentralDetector/include/DetSim1Construction.hh
    M       Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh
    M       Simulation/DetSimV2/CentralDetector/src/DetSim1Construction.cc
    M       Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc
    M       Simulation/DetSimV2/DetSimOptions/include/WaterPoolConstruction.hh
    M       Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc




