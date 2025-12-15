WaterDistributorPartIIIUnion
==============================





PROBABLY FIXED::

    119 /**
    120 U4Transform::GetMultiUnionItemTransform
    121 -----------------------------------------
    122 
    123 Gave very incorrect bbox for WaterDistributorPartIIIUnion (a multiunion with
    124 rotations and translations on the items) whilst using Convert_TranslateThenRotate.
    125 After switched to Convert_RotateThenTranslate the bbox looks consistent with
    126 expectations from SMesh.
    127 
    128 **/
    129 
    130 
    131 inline void U4Transform::GetMultiUnionItemTransform(  glm::tmat4x4<double>& xf, const G4MultiUnion* const muni, unsigned item )
    132 {
    133     [[maybe_unused]] unsigned num_item = muni->GetNumberOfSolids() ;
    134     assert( item < num_item );
    135     const G4Transform3D& tr = muni->GetTransformation(item) ;
    136 
    137     Convert_RotateThenTranslate(xf,  tr );
    138 }
    139 






::

    2025-12-15 22:27:49.635 INFO  [2753514] [SSim::AnnotateFrame@197]  caller CSGFoundry::getFrameE tree YES elv NO  extra.size 0 tree_digest 301158ef96cbf4d61f96ed76aee59990 dynamic 301158ef96cbf4d61f96ed76aee59990
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


















 bb [-9103.062,-20790.500,-19998.969,5702.666,21247.500,418.500]



::

    TEST=CompareRanges ~/o/CSG/tests/CSGFoundryLoadTest.sh


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





    [U4SolidMakerTest::get_node_bb lvid 0
     bn 1
     ln 1
     ns 5
     0 [    -0.000,    -0.000,    -0.000,     0.000,     0.000,     0.000] ALL_ZERO DEGENERATE [     0.000,     0.000,     0.000,     0.000,     0.000,     0.000] ALL_ZERO DEGENERATE [     0.000,     0.000,     0.000,     0.000,     0.000,     0.000] ALL_ZERO DEGENERATE 
     1 [   -59.252,   -59.252,  -294.190,    59.252,    59.252,   294.190] [  -306.353,   -59.252,-19694.251,    66.353,    59.252,-19116.200] [  -306.353,   -59.252,-19694.251,    66.353,    59.252,-19116.200] 
     2 [   -63.924,   -63.924,  -580.955,    63.924,    63.924,   580.955] [  -306.500,   -63.924,-20757.351,   136.661,    63.924,-19605.212] [  -306.500,   -63.924,-20757.351,   136.661,    63.924,-19116.200] 
     3 [  -349.500,  -349.500,   -66.500,   247.134,     0.000,    66.500] [  -460.134,   -66.500,-21073.500,   136.500,    66.500,-20724.000] [  -460.134,   -66.500,-21073.500,   136.661,    66.500,-19116.200] 
     4 [     0.000,   201.879,   -66.500,   295.924,   418.500,    66.500] [  -662.000,   -66.500,-20979.121,  -366.076,    66.500,-20762.500] [  -662.000,   -66.500,-21073.500,   136.661,    66.500,-19116.200] 
     bb [  -662.000,   -66.500,-21073.500,   136.661,    66.500,-19116.200]
     ce [  -262.670,     0.000,-20094.850,   978.650]
    ]U4SolidMakerTest::get_node_bb lvid 0















::

    (ok) A[blyth@localhost opticks]$ jgr WaterDistributorPartIIIUnion
    ./Simulation/DetSimV2/CentralDetector/include/WaterdistributorpipeMaker.hh:    PlacedSolid MakeWaterDistributorPartIIIUnion(double m_lowerchimney_rotangle);
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:PlacedSolid WaterdistributorpipeMaker::MakeWaterDistributorPartIIIUnion(double m_lowerchimney_rotangle) {
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:    G4MultiUnion* unionSolid = new G4MultiUnion("WaterDistributorPartIIIUnion");
    ./Simulation/DetSimV2/CentralDetector/src/WaterdistributorpipeMaker.cc:    return {unionSolid, G4ThreeVector(0, 0, 0), finalRotation, 0, "lWaterDistributorPartIIIUnion", "pWaterDistributorPartIIIUnion"};
    ./Simulation/DetSimV2/DetSimOptions/src/WaterPoolConstruction.cc:    auto unionSolid = WaterdistributorpipeMaker::MakeWaterDistributorPartIIIUnion(m_lowerchimney_rotangle);
    (ok) A[blyth@localost junosw]$ 





::


    (ok) A[blyth@localhost tests]$ ./U4SolidMakerTest.sh 
                       BASH_SOURCE : ./U4SolidMakerTest.sh
                              name : U4SolidMakerTest
                               PWD : /home/blyth/opticks/u4/tests
                               bin : U4SolidMakerTest
                            script : U4SolidMakerTest.py
                              FOLD : /tmp/blyth/opticks/U4SolidMakerTest
                             SOLID : WaterDistributorPartIIIUnion
                               arg : info_run_pdb
                            defarg : info_run_pdb

    [U4Solid::init   0/0/Mul/ -1/4 lvid/depth/tag/root/level WaterDistributorPartIIIUnion
    [U4Solid::init_MultiUnion {  0/0/Mul/ -1/4}  level 4 name WaterDistributorPartIIIUnion hint 0 CSG::Name(hint) zero type 11 CSG::Name(type) contiguous sub_num 5
    [U4MultiUnion::Desc
     name WaterDistributorPartIIIUnion
     sub_num 5
       0 : sBotChimneySSEnclosure_Flange
       1 : CutTube1
       2 : CutTube2
       3 : torus1
       4 : torus2
    ]U4MultiUnion::Desc

    [U4Solid::init   0/1/Pol/ -1/4  
    U4Polycone::collectPrims outside YES idx -1 is_cylinder YES
    U4Polycone::collectPrims skipping prim as z2 == z1  
    U4Polycone::collectPrims outside YES idx -1 is_cylinder YES
    U4Polycone::init_outer. num_outer_prim 2
    sn::increase_zmax_ lvid 0 _zmax  -25.00 dz    1.00 new_zmax  -24.00
    U4Polycone::U4Polycone NOT-WITH-SND
    U4Polycone::desc lvid 0 depth 1 level 4 enable_nudge YES num 4 rz 4
     num_R_inner   1 R_inner_min          0 R_inner_max          0
     num_R_outer   2 R_outer_min       66.5 R_outer_max        125
     num_Z         3 Z_min              -50 Z_max                0
     has_inner NO root  -1 label NOT-WITH-SND
      0 RRZ      0.000     66.500    -50.000
      1 RRZ      0.000     66.500    -25.000
      2 RRZ      0.000    125.000    -25.000
      3 RRZ      0.000    125.000      0.000

    U4Polycone::Convert

    sn::desc pid   -1 idx   -1 typecode   1 num_node   3 num_leaf   2 maxdepth  1 is_positive_form Y lvid  -1 xform N tag un
    sn::render mode 5 PID
       -1       
                
    -1    -1    
                
                
                

    preorder  sn::desc_order [-1 -1 -1 ]
    inorder   sn::desc_order [-1 -1 -1 ]
    postorder sn::desc_order [-1 -1 -1 ]
     ops = operators(0) 2
     CSG::MaskDesc(ops) : union 
     is_positive_form() : YES
    U4Solid::init_Polycone level 4
      0/1/Pol/ -1/4 level 4 entityType       G4Polycone name sBotChimneySSEnclosure_Flange
    ]U4Solid::init   0/1/Pol/ -1/4
    -U4Solid::init_MultiUnion i     0 sub_name sBotChimneySSEnclosure_Flange p_expect NO 
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000     0.0000 -19120.0000     1.0000.

    [U4Solid::init   0/1/TuC/ -1/4  
    ]U4Solid::init   0/1/TuC/ -1/4
    -U4Solid::init_MultiUnion i     1 sub_name CutTube1 p_expect YES
    .
         0.8910     0.0000    -0.4540     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         0.4540     0.0000     0.8910     0.0000.
     -8916.7089     0.0000 -17235.7039     1.0000.

    [U4Solid::init   0/1/TuC/ -1/4  
    ]U4Solid::init   0/1/TuC/ -1/4
    -U4Solid::init_MultiUnion i     2 sub_name CutTube2 p_expect YES
    .
         0.9613     0.0000     0.2756     0.0000.
         0.0000     1.0000     0.0000     0.0000.
        -0.2756     0.0000     0.9613     0.0000.
      5481.0851     0.0000 -19422.8997     1.0000.

    [U4Solid::init   0/1/Tor/ -1/4  
     U4Solid::init_Torus  rmin_mm 0.00 rmax_mm 66.50 rtor_mm 283.00 startPhi_deg 180.00 deltaPhi_deg 135.00
    ]U4Solid::init   0/1/Tor/ -1/4
    -U4Solid::init_MultiUnion i     3 sub_name torus1 p_expect YES
    .
        -1.0000     0.0000    -0.0000     0.0000.
        -0.0000     0.0000     1.0000     0.0000.
         0.0000     1.0000    -0.0000     0.0000.
       213.0000 -20724.0000     0.0000     1.0000.

    [U4Solid::init   0/1/Tor/ -1/4  
     U4Solid::init_Torus  rmin_mm 0.00 rmax_mm 66.50 rtor_mm 352.00 startPhi_deg 45.00 deltaPhi_deg 45.00
    ]U4Solid::init   0/1/Tor/ -1/4
    -U4Solid::init_MultiUnion i     4 sub_name torus2 p_expect YES
    .
         1.0000     0.0000     0.0000     0.0000.
         0.0000     0.0000     1.0000     0.0000.
         0.0000    -1.0000     0.0000     0.0000.
      -662.0000 21181.0000    -0.0000     1.0000.

    ]U4Solid::init_MultiUnion level 4
    ]U4Solid::init   0/0/Mul/ -1/4
    [U4SolidMakerTest nd.desc
    sn::desc pid   -1 idx   -1 typecode  11 num_node   6 num_leaf   5 maxdepth  1 is_positive_form Y lvid   0 xform N tag co]U4SolidMakeTest nd.desc

    [U4SolidMakerTest nd->render() 

    sn::desc pid   -1 idx   -1 typecode  11 num_node   6 num_leaf   5 maxdepth  1 is_positive_form Y lvid   0 xform N tag co
    sn::render mode 0 MINIMAL
                o        
                         


















