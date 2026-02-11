

::

    PRIMTAB=1 POINT=-5600,0,21000 LINE=-5600,0,19000,-5600,0,20000 ./cxt_min.sh pdb

    PRIMTAB=1 POINT=-5600,0,21000 LINE=-6169,0,19000,-6169,0,19500 ./cxt_min.sh pdb



    (ok) A[blyth@localhost CSG]$ CSGPrim__DescRange_CE_ZMIN_ZMAX=19000,20000 CSGPrim__DescRange_CE_YMIN_YMAX=-100,100 ~/o/CSG/tests/CSGFoundryLoadTest.sh
                       BASH_SOURCE : /home/blyth/o/CSG/tests/CSGFoundryLoadTest.sh
                              name : CSGFoundryLoadTest
                               bin : CSGFoundryLoadTest
                            script : CSGFoundryLoadTest.py
                               PWD : /home/blyth/opticks/CSG/tests
                              GEOM : J25_7_2_opticks_Debug
                       GEOM_METHOD : local sourcing of ~/.opticks/GEOM/GEOM.sh
                              TEST : descPrimRange
                              LVID : 
    [CSGFoundryLoadTest::descPrimRange 
    [CSGFoundry.descBase 
     CFBase       /home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug
     OriginCFBase /home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug
    ]CSGFoundry.descBase 
    [CSGFoundry::descPrimRange num_solid 13
    [CSGFoundry::descPrimRange solidIdx  0 so.primOffset     0 so.numPrim  3070
    [CSGPrim::Desc numPrim 3070 mg_subs 0
     EXTENT_MINI :      0.000 [CSGPrim__DescRange_EXTENT_MINI]
     EXTENT_DIFF :    200.000 [CSGPrim__DescRange_EXTENT_DIFF]
     [CSGPrim__DescRange_CE_ZMIN_ZMAX] CE_ZMIN :  19000.000 CE_ZMAX :  20000.000
     [CSGPrim__DescRange_CE_YMIN_YMAX] CE_YMIN :   -100.000 CE_YMAX :    100.000
     [CSGPrim__DescRange_CE_XMIN_XMAX] CE_XMIN :      0.000 CE_XMAX :      0.000
     226 :  ; ce = np.array([     0.000,     0.000, 19632.410,  8700.219])  ; bb = np.array([ -8700.219, -8700.219, 19594.910,  8700.219,  8700.219, 19669.910])  # CSGPrim::descRangeNumPy  lvid  46 ridx    0 pidx   226 so[s_EMFsupport_ring4]
    2206 :  ; ce = np.array([  6168.931,     0.000, 19213.971,   544.813])  ; bb = np.array([  5949.688,  -544.813, 18930.084,  6388.174,   544.813, 19497.857])  # CSGPrim::descRangeNumPy  lvid 228 ridx    0 pidx  2206 so[GLb3.up09_FlangeI_Web_FlangeII]
    2221 :  ; ce = np.array([ -6168.931,     0.000, 19213.971,   544.813])  ; bb = np.array([ -6388.174,  -544.813, 18930.084, -5949.688,   544.813, 19497.857])  # CSGPrim::descRangeNumPy  lvid 228 ridx    0 pidx  2221 so[GLb3.up09_FlangeI_Web_FlangeII]
     271 :  ; ce = np.array([  8423.973,     0.000, 19174.340,   429.192])  ; bb = np.array([  8220.637,   -37.500, 18745.148,  8627.309,    37.500, 19603.533])  # CSGPrim::descRangeNumPy  lvid  67 ridx    0 pidx   271 so[s_EMF_bar_box_920mm]
    2176 :  ; ce = np.array([  4057.752,     0.000, 19767.828,   358.363])  ; bb = np.array([  3860.547,  -358.363, 19492.773,  4254.958,   358.363, 20042.885])  # CSGPrim::descRangeNumPy  lvid 227 ridx    0 pidx  2176 so[GLb4.up10_FlangeI_Web_FlangeII]
    2191 :  ; ce = np.array([ -4057.752,     0.000, 19767.828,   358.363])  ; bb = np.array([ -4254.958,  -358.363, 19492.773, -3860.547,   358.363, 20042.885])  # CSGPrim::descRangeNumPy  lvid 227 ridx    0 pidx  2191 so[GLb4.up10_FlangeI_Web_FlangeII]
     numPrim 3070 mg_subs 0
     EXTENT_MINI :      0.000 [CSGPrim__DescRange_EXTENT_MINI]
     EXTENT_DIFF :    200.000 [CSGPrim__DescRange_EXTENT_DIFF]
     [CSGPrim__DescRange_CE_ZMIN_ZMAX] CE_ZMIN :  19000.000 CE_ZMAX :  20000.000
     [CSGPrim__DescRange_CE_YMIN_YMAX] CE_YMIN :   -100.000 CE_YMAX :    100.000
     [CSGPrim__DescRange_CE_XMIN_XMAX] CE_XMIN :      0.000 CE_XMAX :      0.000
    ]CSGPrim::Desc

    ]CSGFoundry::descPrimRange solidIdx  0
    [CSGFoundry::descPrimRange num_solid 13
    [CSGFoundry.descBase 
     CFBase       /home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug
     OriginCFBase /home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug
    ]CSGFoundry.descBase 
    ]CSGFoundryLoadTest::descPrimRange
    (ok) A[blyth@localhost CSG]$ CSGPrim__DescRange_CE_ZMIN_ZMAX=19000,20000 CSGPrim__DescRange_CE_YMIN_YMAX=-100,100 ~/o/CSG/tests/CSGFoundryLoadTest.sh




::

     PRIMTAB=1 POINT=-6000,0,20000 LINE=-6000,0,19700,-6000,0,20500 ./cxt_min.sh pdb




    n [13]: p[np.logical_and(p[:,2] > 19000, p[:,1] == 0.)]
    Out[13]: 
    array([[ 2457.261,     0.   , 19278.02 ,     0.   ],
           [-2457.26 ,     0.   , 19278.02 ,     0.   ]])



    Mon Feb  2 08:33:39 PM CST 2026] FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:27:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    [Mon Feb  2 08:35:21 PM CST 2026] FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:26:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    [Mon Feb  2 08:35:51 PM CST 2026] FULLSCREEN=0 MOI=GZ1.A03_04_FlangeI_Web_FlangeII:25:-2 EYE=1,1,1 LOOK=0,0,1 cxr_min.sh 
    [Mon Feb  9 09:55:15 PM CST 2026] FULLSCREEN=0 MOI=-6000,0,19700,500 cxr_min.sh 
    [Mon Feb  9 09:55:48 PM CST 2026] FULLSCREEN=0 MOI=-6000,0,19700,500 ssst.sh 
    [Mon Feb  9 09:57:32 PM CST 2026] FULLSCREEN=0 MOI=-6000,0,19700,500 cxr_min.sh 
    (ok) A[blyth@localhost stree]$ 


::

     ELV=mask_PMT_20inch_vetosMask_virtual MOI=EXTENT:20000 cxr_min.sh
     ELV=mask_PMT_20inch_vetosMask_virtual MOI=-6000,0,19700,500 cxr_min.sh



Use MOI pointing at CE arround coordinate::

    moi=-6000,0,19700,500 ; moi_note="$LINENO close to where the stake goes thru mask_PMT_20inch_vetosMask_virtual"

Then simtrace with cxt_min.py and dump idtab::

    In [1]: idtab
    Out[1]: 
    [idtab
    array([[     0, 461340,      0],
           [ 50056,  74539,   9021],
           [ 50086,  12487,   9001],
           [ 50087,   1890,  15209],
           [ 50146,    559,  17249],
           [ 50001,    134, 311415],
           [ 50147,     51,  25163]])
    ]idtab


Then use MOI=SID:50055 why off-by-one ? That plucks the staked PMT::

     FULLSCREEN=0 MOI=SID:50055 cxr_min.sh


::

    301     ust = st[presel]   ## example ust shape (13812151, 4, 4)
    302     ## for simtrace layout see sysrap/sevent.h
    303 
    304     _ii = ust[:,3,3].view(np.int32)   ## instanceIndex
    305     _gp_bn = ust[:,2,3].view(np.int32)    ## simtrace intersect boundary indices
    306     _gp = _gp_bn >> 16      ## globalPrimIdx
    307     _bn = _gp_bn & 0xffff   ## boundary
    308 
    309     gnrm = ust[:,0].copy()



Change to including both ii and id in the simtrace::


    In [2]: iitab
    Out[2]: 
    [iitab
    array([[     0, 456008,      0],
           [ 43252,  74539,   9021],
           [ 43282,  12487,   9001],
           [ 49185,   5332,   9066],
           [ 43283,   1890,  15209],
           [ 43342,    559,  17249],
           [ 43197,    134, 311415],
           [ 43343,     51,  25163]])
    ]iitab

    In [3]: idtab
    Out[3]: 
    [idtab
    array([[     0, 461340,      0],
           [ 50056,  74539,   9021],
           [ 50086,  12487,   9001],
           [ 50087,   1890,  15209],
           [ 50146,    559,  17249],
           [ 50001,    134, 311415],
           [ 50147,     51,  25163]])
    ]idtab


Using MOI=INST:43252 finds the distinctive WP PMT with stake thru its heart::

    orun.sh FULLSCREEN=0 MOI=INST:43252 EYE=3,3,3 cxr_min.sh

    orun.sh FULLSCREEN=0 MOI=SID:50056 EYE=3,3,3 cxr_min.sh   ## finds adjacent PMT
    orun.sh FULLSCREEN=0 MOI=SID:50055 EYE=3,3,3 cxr_min.sh   

    MOI=SIDX:43256 EYE=3,3,3 cxr_min.sh    ## sidx has no off by one

::

    In [8]: f.prim_nidx[266]
    Out[8]: array([64754], dtype=int32)

    In [9]: nidx = f.prim_nidx[266][0]

    In [10]: nidx
    Out[10]: np.int32(64754)


    MOI=PRIM:266 cxr_min.sh  ## YEP FINDS IT


    In [11]: f.nds[nidx]
    Out[11]: array([64754,     4,    60, 64688,     0,    -1, 64755,    66,  3305,    -1,    -1,     0,    -1,    69,    -1], dtype=int32)



So its::

    MOI=LVID_COPYNO:66/3305 cxr_min.sh





::

    In [2]: f.inst.shape
    Out[2]: (49186, 4, 4)

    In [3]: pwd
    Out[3]: '/home/blyth/junosw/InstallArea/Chenjing-EMFcoilsgeometry/.opticks/GEOM/J25_7_2_opticks_Debug/CSGFoundry/SSim/stree'


    In [4]: f.inst[43252]
    Out[4]: 
    array([[   -0.961,     0.005,    -0.278,     0.   ],
           [   -0.005,    -1.   ,     0.   ,     0.   ],
           [   -0.278,     0.001,     0.961,     0.   ],
           [-5700.183,    29.893, 19693.629,     0.   ]])

    In [9]: f.inst[43252,:,3].view(np.uint64)
    Out[9]: array([43252,     4, 50055, 43256], dtype=uint64)




Would be good to relate to the code
--------------------------------------

::

    798 
    799         bool placedInThisRing = false;
    800         for (int k = 0; k < Nbars; ++k) {
    801             const double phi = (2.0 * M_PI / Nbars) * k;
    802             const double cosPhi = std::cos(phi);
    803             const double sinPhi = std::sin(phi);
    804 
    805             const double er_xy_coeff = R_ring_inner_m / r_dir;
    806             const double er_z        = z_center_m    / r_dir;
    807 
    808             const G4ThreeVector u_hat(
    809                 cosPhi * er_xy_coeff,
    810                 sinPhi * er_xy_coeff,
    811                 er_z
    812             );
    813 
    814             const G4ThreeVector pos = u_hat * r_c;
    815             const G4RotationMatrix rot = AlignLocalYToAxisPreferZdown(u_hat);
    816 
    817             const int length_mm = static_cast<int>(std::round(Lmm));
    818             G4LogicalVolume* lv_bar = CreateUSupportBarLV(length_mm);
    819             if (!lv_bar) continue;
    820 
    821             const std::string pname =
    822                 "s_EMFsupportBar_r" + std::to_string(i+1) + "_k" + std::to_string(k);
    823 
    824             new G4PVPlacement(
    825                 G4Transform3D(rot, pos * m),
    826                 lv_bar,
    827                 pname.c_str(),
    828                 m_logicWaterPool,
    829                 false,
    830                 (3000 + (i+1)*100 + k),
    831                 false
    832             );
    833             ++supportBarPlaced;
    834             placedInThisRing = true;
    835         }
    836         if (placedInThisRing) ++supportBarRingCount;
    837     }
    838     LogInfo << "[EMF][Status] Support bars equipped: "
    839             << ((supportBarPlaced > 0) ? "YES" : "NO")
    840             << " (bars=" << supportBarPlaced
    841             << ", ringsWithBars=" << supportBarRingCount << ")"
    842             << std::endl;
    843 }



Lookup lvid for s_EMF_bar_box_810mm
-------------------------------------

::

    (ok) A[blyth@localhost CSGFoundry]$ cat.py meshname.txt  | grep s_EMF_bar_box_810mm
    66   s_EMF_bar_box_810mm

Then lookup volumes with lvid 66::

    In [5]: f.nds[f.nds[:,7] == 66]
    Out[5]: 
    array([[64734,     4,    40, 64688,     0,    -1, 64735,    66,  3100,    -1,    -1,     0,    -1,    69,    -1],
           [64735,     4,    41, 64688,     0,    -1, 64736,    66,  3101,    -1,    -1,     0,    -1,    69,    -1],
           [64736,     4,    42, 64688,     0,    -1, 64737,    66,  3102,    -1,    -1,     0,    -1,    69,    -1],
           [64737,     4,    43, 64688,     0,    -1, 64738,    66,  3103,    -1,    -1,     0,    -1,    69,    -1],
           [64738,     4,    44, 64688,     0,    -1, 64739,    66,  3104,    -1,    -1,     0,    -1,    69,    -1],
           [64739,     4,    45, 64688,     0,    -1, 64740,    66,  3200,    -1,    -1,     0,    -1,    69,    -1],
           [64740,     4,    46, 64688,     0,    -1, 64741,    66,  3201,    -1,    -1,     0,    -1,    69,    -1],
           [64741,     4,    47, 64688,     0,    -1, 64742,    66,  3202,    -1,    -1,     0,    -1,    69,    -1],
           [64742,     4,    48, 64688,     0,    -1, 64743,    66,  3203,    -1,    -1,     0,    -1,    69,    -1],
           [64743,     4,    49, 64688,     0,    -1, 64744,    66,  3204,    -1,    -1,     0,    -1,    69,    -1],
           [64744,     4,    50, 64688,     0,    -1, 64745,    66,  3205,    -1,    -1,     0,    -1,    69,    -1],
           [64745,     4,    51, 64688,     0,    -1, 64746,    66,  3206,    -1,    -1,     0,    -1,    69,    -1],
           [64746,     4,    52, 64688,     0,    -1, 64747,    66,  3207,    -1,    -1,     0,    -1,    69,    -1],
           [64747,     4,    53, 64688,     0,    -1, 64748,    66,  3208,    -1,    -1,     0,    -1,    69,    -1],
           [64748,     4,    54, 64688,     0,    -1, 64749,    66,  3209,    -1,    -1,     0,    -1,    69,    -1],
           [64749,     4,    55, 64688,     0,    -1, 64750,    66,  3300,    -1,    -1,     0,    -1,    69,    -1],
           [64750,     4,    56, 64688,     0,    -1, 64751,    66,  3301,    -1,    -1,     0,    -1,    69,    -1],
           [64751,     4,    57, 64688,     0,    -1, 64752,    66,  3302,    -1,    -1,     0,    -1,    69,    -1],
           [64752,     4,    58, 64688,     0,    -1, 64753,    66,  3303,    -1,    -1,     0,    -1,    69,    -1],
           [64753,     4,    59, 64688,     0,    -1, 64754,    66,  3304,    -1,    -1,     0,    -1,    69,    -1],
           [64754,     4,    60, 64688,     0,    -1, 64755,    66,  3305,    -1,    -1,     0,    -1,    69,    -1],
           [64755,     4,    61, 64688,     0,    -1, 64756,    66,  3306,    -1,    -1,     0,    -1,    69,    -1],
           [64756,     4,    62, 64688,     0,    -1, 64757,    66,  3307,    -1,    -1,     0,    -1,    69,    -1],
           [64757,     4,    63, 64688,     0,    -1, 64758,    66,  3308,    -1,    -1,     0,    -1,    69,    -1],
           [64758,     4,    64, 64688,     0,    -1, 64759,    66,  3309,    -1,    -1,     0,    -1,    69,    -1]], dtype=int32)

    In [6]: f.nds[f.nds[:,7] == 66].shape
    Out[6]: (25, 15)


::

     MOI=LVID_COPYNO:66/3100 cxr_min.sh

     MOI=LVID_COPYNO:66/3100 EYE=2,0,0 UP=0,1,0  cxr_min.sh



Finding the staked PMT::


     MOI=LVID_COPYNO:s_EMF_bar_box_810mm/3305 EYE=2,0,0 UP=0,1,0  cxr_min.sh

     MOI=PRIM:266 EYE=2,0,0 UP=0,1,0  cxr_min.sh



::

     pr   264 nx   64752 nd [snode ix:  64752 dh: 4 sx:   58 pt:  64688 nc:    0 fc:     -1 ns:  64753 lv: 66 cp:   3303 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]
     pr   265 nx   64753 nd [snode ix:  64753 dh: 4 sx:   59 pt:  64688 nc:    0 fc:     -1 ns:  64754 lv: 66 cp:   3304 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]

     pr   266 nx   64754 nd [snode ix:  64754 dh: 4 sx:   60 pt:  64688 nc:    0 fc:     -1 ns:  64755 lv: 66 cp:   3305 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]

     pr   267 nx   64755 nd [snode ix:  64755 dh: 4 sx:   61 pt:  64688 nc:    0 fc:     -1 ns:  64756 lv: 66 cp:   3306 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]
     pr   268 nx   64756 nd [snode ix:  64756 dh: 4 sx:   62 pt:  64688 nc:    0 fc:     -1 ns:  64757 lv: 66 cp:   3307 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]
     pr   269 nx   64757 nd [snode ix:  64757 dh: 4 sx:   63 pt:  64688 nc:    0 fc:     -1 ns:  64758 lv: 66 cp:   3308 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]
     pr   270 nx   64758 nd [snode ix:  64758 dh: 4 sx:   64 pt:  64688 nc:    0 fc:     -1 ns:  64759 lv: 66 cp:   3309 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 69 sn:-1]
     pr   271 nx   64759 nd [snode ix:  64759 dh: 4 sx:   65 pt:  64688 nc:    0 fc:     -1 ns:  64760 lv: 67 cp:   3400 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   272 nx   64760 nd [snode ix:  64760 dh: 4 sx:   66 pt:  64688 nc:    0 fc:     -1 ns:  64761 lv: 67 cp:   3401 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   273 nx   64761 nd [snode ix:  64761 dh: 4 sx:   67 pt:  64688 nc:    0 fc:     -1 ns:  64762 lv: 67 cp:   3402 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   274 nx   64762 nd [snode ix:  64762 dh: 4 sx:   68 pt:  64688 nc:    0 fc:     -1 ns:  64763 lv: 67 cp:   3403 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   275 nx   64763 nd [snode ix:  64763 dh: 4 sx:   69 pt:  64688 nc:    0 fc:     -1 ns:  64764 lv: 67 cp:   3404 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   276 nx   64764 nd [snode ix:  64764 dh: 4 sx:   70 pt:  64688 nc:    0 fc:     -1 ns:  64765 lv: 67 cp:   3405 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   277 nx   64765 nd [snode ix:  64765 dh: 4 sx:   71 pt:  64688 nc:    0 fc:     -1 ns:  64766 lv: 67 cp:   3406 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   278 nx   64766 nd [snode ix:  64766 dh: 4 sx:   72 pt:  64688 nc:    0 fc:     -1 ns:  64767 lv: 67 cp:   3407 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]
     pr   279 nx   64767 nd [snode ix:  64767 dh: 4 sx:   73 pt:  64688 nc:    0 fc:     -1 ns:  64768 lv: 67 cp:   3408 se:     -1 se:     -1 ri: 0 ro:   -1 bd: 70 sn:-1]









::

    082 struct snode
     83 {
     84     static constexpr const int NV = 15 ;
     85 
     86     int index ;        // 0
     87     int depth ;        // 1
     88     int sibdex ;       // 2    0-based sibling index
     89     int parent ;       // 3
     90 
     91     int num_child ;    // 4
     92     int first_child ;  // 5
     93     int next_sibling ; // 6
     94     int lvid ;         // 7
     95 
     96     int copyno ;       // 8
     97     int sensor_id ;    // 9  : -1 signifies "not-a-sensor"
     98     int sensor_index ; // 10
     99     int repeat_index ; // 11
    100 
    101     int repeat_ordinal ; // 12
    102     int boundary ;       // 13
    103     int sensor_name ;    // 14
    104 
    105     std::string desc() const ;
    106     int*        data();
    107     const int*  cdata() const ;
    108     int    get_attrib(int idx) const ;
    109     static std::string Brief_(const std::vector<snode>& nodes );
    110 };





