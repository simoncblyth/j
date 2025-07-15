InputPhotonsCheck_WP_long_ray_intersect_precision
==================================================



::

    1367 void
    1368 LSExpDetectorConstruction::setupWP_PMTs() {
    1369 
    1370   //put veto pmts into water pool
    1371   IDetElement* glob_info = det_elem("GlobalGeomInfo");
    1372   G4double waterpool_r = glob_info->geom_info("WaterPool.R");
    1373   G4double waterpool_h = glob_info->geom_info("WaterPool.H");
    1374   G4double vetopmt_interval = 2*m;
    1375   IDetElementPos* veto_pmt_detelem_pos = 0;
    1376   if (m_veto_pmt_pos_mode == "CalMode") {
    1377       veto_pmt_detelem_pos = new JUNO::Cylinder::CalPositionCylinder(
    1378               waterpool_r,
    1379               waterpool_h,
    1380               pmt_det_veto->GetPMTRadius(),
    1381               pmt_det_veto->GetPMTHeight(),
    1382               vetopmt_interval);
    1383   } else if (m_veto_pmt_pos_mode == "FileMode") {
    1384    veto_pmt_detelem_pos = new JUNO::Ball::VetoPmtPosBall(m_scope);
    1385   }
    1386   assert (veto_pmt_detelem_pos);
    1387  std::cout << "WP PMT Position Mode: " << m_veto_pmt_pos_mode << std::endl;
    1388   // If the string m_veto_pmt_pos_mode is empty, don't place any PMTs.
    1389   if (m_veto_pmt_pos_mode.size()!=0) {
    1390       assert (veto_pmt_detelem_pos);
    1391       m_pmt_mother = "OuterWaterVeto";
    1392       bool veto_status = de_wp_det->inject(m_pmt_mother, pmt_det_veto, veto_pmt_detelem_pos);
    1393       assert (veto_status);
    1394   }
    1395 }


::

    BP=LSExpDetectorConstruction::setupWP_PMTs ipc



::

     43 void
     44 VetoPmtPosBall::initialize() {
     45     SniperPtr<IPMTParamSvc> pmtParamSvc(*m_scope, "PMTParamSvc");
     46     if (pmtParamSvc.invalid())
     47     {
     48         LogError << "Can't Locate  PMTParamSvc." << std::endl;
     49         assert(0);
     50     }
     51 
     52     for (int i = kOFFSET_WP_PMT; i<kOFFSET_WP_PMT+pmtParamSvc->get_NTotal_WP_LPMT(); i++) // kOFFSET_WP_PMT=30000
     53     {
     54         G4int copyno{0}; 
     55         G4double theta{0}; // degree
     56         G4double phi{0}; // degree
     57         G4double psi{0}; // degree
     58         G4double x{0};   // x
     59         G4double y{0};   // y
     60         G4double z{0};   // z
     61         
     62 
     63         copyno = i;
     64         x = pmtParamSvc->getPMTX(i);
     65         y = pmtParamSvc->getPMTY(i);
     66         z = pmtParamSvc->getPMTZ(i);
     67         theta = pmtParamSvc->getPMTTheta(i);
     68         phi = pmtParamSvc->getPMTPhi(i);
     69         
     70         //std::cout <<"veto pmt number " <<copyno << " " << x << " " << y << " " << z <<" "<< theta<<" "<< phi << std::endl;
     71        
     72         theta = theta * deg;
     73         phi = phi * deg;
     74         psi = psi * deg;
     75         // Positions and rotations for regular PMT
     76         // construct G4Transform3D
     77         G4ThreeVector pos(x, y, z);
     78         G4RotationMatrix rot;
     79         rot.rotateY(theta);
     80         rot.rotateZ(phi);
     81         G4Transform3D trans(rot, pos);
     82         m_position.push_back(trans);
     83     }
     84 }



BP=VetoPmtPosBall::initialize ipc



Not getting SA ? 
-------------------

::

    In [7]: a.qtab
    Out[7]: 
    array([[b'99594', b'0', b'TO BT BT                                                                                        '],
           [b'251', b'71432', b'TO BT BT BT BT                                                                                  '],
           [b'155', b'71433', b'TO BT BT BT BT BT                                                                               ']], dtype='|S96')

    In [8]: w = a.q_startswith("TO BT BT BT BT")

    In [9]: a.f.record[w,:5,0]
    Out[9]: 
    array([[[  3234.436,  20623.73 ,  20512.508,      0.1  ],
            [ -1255.312,  20623.73 ,    818.01 ,     67.479],
            [ -1265.47 ,  20623.73 ,    773.453,     67.632],
            [ -6377.33 ,  20623.73 , -21650.   ,    144.347],
            [ -6377.786,  20623.73 , -21652.   ,    144.354]],

           [[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
            [ -1251.225,  20623.73 ,    830.09 ,     67.437],
            [ -1251.335,  20623.73 ,    829.608,     67.439],
            [ -1266.823,  20623.73 ,    761.648,     67.671],
            [ -6374.514,  20623.73 , -21650.   ,    144.345]],

           [[  3234.497,  20623.73 ,  20512.492,      0.1  ],
            [ -1248.073,  20623.73 ,    838.069,     67.409],
            [ -1248.144,  20623.73 ,    837.756,     67.41 ],
            [ -1267.481,  20623.73 ,    752.885,     67.7  ],
            [ -6371.695,  20623.73 , -21650.   ,    144.343]],



    In [10]: w5 = a.q_startswith("TO BT BT BT BT BT")

    In [11]: a.f.record[w5,:6,0]
    Out[11]: 
    array([[[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
            [ -1251.225,  20623.73 ,    830.09 ,     67.437],
            [ -1251.335,  20623.73 ,    829.608,     67.439],
            [ -1266.823,  20623.73 ,    761.648,     67.671],
            [ -6374.514,  20623.73 , -21650.   ,    144.345],
            [ -6374.97 ,  20623.73 , -21652.   ,    144.352]],

           [[  3234.497,  20623.73 ,  20512.492,      0.1  ],
            [ -1248.073,  20623.73 ,    838.069,     67.409],
            [ -1248.144,  20623.73 ,    837.756,     67.41 ],
            [ -1267.481,  20623.73 ,    752.885,     67.7  ],
            [ -6371.695,  20623.73 , -21650.   ,    144.343],
            [ -6372.151,  20623.73 , -21652.   ,    144.35 ]],



Setting MPT and rindex gets SA
----------------------------------

::

    INFO:opticks.ana.pvplt:SEvt.__init__  symbol a pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data1/blyth/tmp/GEOM/BigWaterPool/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_poolcover/A000 
    qtab
    [[b'99594' b'0' b'TO SA                                                                                           ']
     [b'251' b'71432' b'TO BT BT SA                                                                                     ']
     [b'155' b'71433' b'TO BT BT BT SA                                                                                  ']]
    qt.qpa.plugin: Could not find the Qt platform plugin "wayland" in ""



MODE=3 cxs_min.sh pdb::

    In [2]: w2 = a.q__("TO BT BT SA") ; w2.shape
    Out[2]: (251,)

    In [3]: w3 = a.q__("TO BT BT BT SA") ; w3.shape
    Out[3]: (155,)

    In [7]: a.qtab[:,0].astype(int).sum()
    Out[7]: np.int64(100000)


    In [8]: a.f.record[w2,:4,0]
    Out[8]: 
    array([[[  3234.436,  20623.73 ,  20512.508,      0.1  ],
            [ -1255.312,  20623.73 ,    818.01 ,     89.916],
            [ -1265.47 ,  20623.73 ,    773.453,     90.12 ],
            [ -6377.33 ,  20623.73 , -21650.   ,    192.382]],

           [[  3234.681,  20623.73 ,  20512.451,      0.1  ],
            [ -1233.192,  20623.73 ,    868.348,     89.676],
            [ -1267.254,  20623.73 ,    718.588,     90.359],
            [ -6354.785,  20623.73 , -21650.   ,    192.359]],

           [[  3234.742,  20623.73 ,  20512.438,      0.1  ],
            [ -1228.869,  20623.73 ,    875.662,     89.64 ],
            [ -1266.506,  20623.73 ,    710.086,     90.395],
            [ -6349.15 ,  20623.73 , -21650.   ,    192.354]],



    In [9]: a.f.record[w3,:5,0]
    Out[9]: 
    array([[[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
            [ -1251.225,  20623.73 ,    830.09 ,     89.86 ],
            [ -1251.335,  20623.73 ,    829.608,     89.862],
            [ -1266.823,  20623.73 ,    761.648,     90.172],
            [ -6374.514,  20623.73 , -21650.   ,    192.379]],

           [[  3234.497,  20623.73 ,  20512.492,      0.1  ],
            [ -1248.073,  20623.73 ,    838.069,     89.822],
            [ -1248.144,  20623.73 ,    837.756,     89.824],
            [ -1267.481,  20623.73 ,    752.885,     90.211],
            [ -6371.695,  20623.73 , -21650.   ,    192.376]],

           [[  3234.527,  20623.73 ,  20512.486,      0.1  ],
            [ -1245.165,  20623.73 ,    844.988,     89.789],
            [ -1245.289,  20623.73 ,    844.443,     89.792],
            [ -1267.806,  20623.73 ,    745.585,     90.243],
            [ -6368.879,  20623.73 , -21650.   ,    192.373]],

           [[  3234.558,  20623.73 ,  20512.479,      0.1  ],
            [ -1242.59 ,  20623.73 ,    850.446,     89.763],
            [ -1242.639,  20623.73 ,    850.232,     89.764],
            [ -1267.925,  20623.73 ,    739.184,     90.271],
            [ -6366.059,  20623.73 , -21650.   ,    192.37 ]],

           [[  3234.589,  20623.73 ,  20512.473,      0.1  ],
            [ -1240.084,  20623.73 ,    855.607,     89.738],
            [ -1240.134,  20623.73 ,    855.386,     89.739],
            [ -1267.899,  20623.73 ,    733.416,     90.296],
            [ -6363.24 ,  20623.73 , -21650.   ,    192.368]],



EVT::

    180 elif [ "$GEOM" == "BigWaterPool" ]; then
    181 
    182     evt_check=poolcover_cxs
    183     export EVT_CHECK=${EVT_CHECK:-$evt_check}
    184     if [ "$EVT_CHECK" == "poolcover_cxs" ]; then
    185 
    186         export AFOLD=/data1/blyth/tmp/GEOM/BigWaterPool/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_poolcover/A000
    187         #export AFOLD_RECORD_SLICE="TO BT BT SA" 
    188         export AFOLD_RECORD_SLICE="TO BT BT BT SA" 
    189     fi


The 2 and 3 BT look the same::

     T0=85 T1=95 TN=1000 ssst.sh



cxs_min.sh::

    460    elif [ "${TEST:12}" == "_poolcover" -o "${TEST:12}" == "_poolcover_refine" ]; then
    461 
    462       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    463       #opticks_input_photon=UpXZ1000_f8.npy
    464       opticks_input_photon=CircleXZ_R500_100k_f8.npy
    465       #opticks_input_photon=CircleXZ_R10_361_f8.npy
    466       #opticks_input_photon_frame=3345.569,20623.73,21500
    467       opticks_input_photon_frame=3345.569,20623.73,21000
    468       #export PIDX=99999
    469 
    470       export SEvt__transformInputPhoton_VERBOSE=1
    471       export CSGFoundry__getFrame_VERBOSE=1
    472       export CSGFoundry__getFrameE_VERBOSE=1
    473 
    474       if [ "${TEST/refine}" != "$TEST" ]; then
    475          export OPTICKS_PROPAGATE_REFINE=1
    476       fi 



Without refine::

    qtab
    [[b'99594' b'0' b'TO SA                                                                                           ']
     [b'251' b'71432' b'TO BT BT SA                                                                                     ']
     [b'155' b'71433' b'TO BT BT BT SA                                                                                  ']]
    qt.qpa.plugin: Could not find the Qt platform plugin "wayland" in ""


With refine::

    Evt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data1/blyth/tmp/GEOM/BigWaterPool/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_poolcover_refine/A000 
    qtab
    [[b'99594' b'0' b'TO SA                                                                                           ']
     [b'406' b'71432' b'TO BT BT SA                                                                                     ']]
    /data1/blyth/tmp/GEOM/BigWaterPool/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_poolcover_refine/A000 : found record

    In [1]: 251+155
    Out[1]: 406

    In [2]: w2 = a.q__("TO BT BT SA") ; w2.shape
    Out[2]: (406,)


    In [3]: a.f.record[w2,:4,0]
    Out[3]: 
    array([[[  3234.436,  20623.73 ,  20512.508,      0.1  ],
            [ -1255.219,  20623.73 ,    818.418,     89.915],
            [ -1265.47 ,  20623.73 ,    773.453,     90.12 ],
            [ -6377.335,  20623.73 , -21650.   ,    192.382]],

           [[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
            [ -1251.334,  20623.73 ,    829.608,     89.862],
            [ -1266.823,  20623.73 ,    761.648,     90.172],
            [ -6374.518,  20623.73 , -21650.   ,    192.379]],

           [[  3234.497,  20623.73 ,  20512.492,      0.1  ],
            [ -1248.144,  20623.73 ,    837.757,     89.824],
            [ -1267.481,  20623.73 ,    752.885,     90.211],
            [ -6371.696,  20623.73 , -21650.   ,    192.376]],

           [[  3234.527,  20623.73 ,  20512.486,      0.1  ],
            [ -1245.289,  20623.73 ,    844.443,     89.792],
            [ -1267.806,  20623.73 ,    745.585,     90.243],
            [ -6368.88 ,  20623.73 , -21650.   ,    192.373]],



Without refine::

    In [11]: w3
    Out[11]: 
    array([71433, 71434, 71435, 71436, 71437, 71438, 71439, 71441, 71445, 71449, 71453, 71454, 71455, 71460, 71461, 71462, 71463, 71464, 71466, 71468, 71470, 71476, 71484, 71485, 71486, 71492, 71494,
           71495, 71496, 71497, 71500, 71504, 71505, 71511, 71514, 71516, 71527, 71532, 71540, 71541, 71542, 71545, 71546, 71549, 71551, 71555, 71556, 71559, 71562, 71566, 71567, 71568, 71574, 71575,
           71576, 71577, 71578, 71583, 71584, 71586, 71591, 71600, 71603, 71607, 71612, 71615, 71616, 71627, 71632, 71638, 71639, 71644, 71647, 71648, 71653, 71654, 71661, 71662, 71665, 71666, 71676,
           71678, 71685, 71688, 71690, 71695, 71697, 71700, 71704, 71707, 71710, 71711, 71713, 71714, 71717, 71718, 71719, 71720, 71721, 71726, 71727, 71730, 71731, 71732, 71733, 71734, 71740, 71741,
           71743, 71745, 71746, 71748, 71755, 71756, 71757, 71759, 71766, 71767, 71768, 71769, 71772, 71773, 71774, 71775, 71778, 71780, 71782, 71784, 71785, 71788, 71792, 71793, 71798, 71799, 71801,
           71802, 71803, 71804, 71811, 71812, 71813, 71814, 71815, 71817, 71818, 71819, 71820, 71822, 71825, 71826, 71827, 71828, 71831, 71833, 71836])

    In [12]: a.f.record[w3[0],:5,0]
    Out[12]: 
    array([[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
           [ -1251.225,  20623.73 ,    830.09 ,     89.86 ],
           [ -1251.335,  20623.73 ,    829.608,     89.862],
           [ -1266.823,  20623.73 ,    761.648,     90.172],
           [ -6374.514,  20623.73 , -21650.   ,    192.379]], dtype=float32)


With refine, and pasting w3 across::

    In [6]: a.f.record[w3[0],:5,0]
    Out[6]: 
    array([[  3234.466,  20623.73 ,  20512.5  ,      0.1  ],
           [ -1251.334,  20623.73 ,    829.608,     89.862],
           [ -1266.823,  20623.73 ,    761.648,     90.172],
           [ -6374.518,  20623.73 , -21650.   ,    192.379],
           [     0.   ,      0.   ,      0.   ,      0.   ]], dtype=float32)




Repeat ipc with new OPTICKS_EVENT_NAME still without refine

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum    65.7112 ndf  9.0000 sum/ndf     7.3012 </span> ]
    TO SA                                                                                            :   85301  85453 :     0.1353 : Y :       0      0 :   
    TO AB                                                                                            :   13861  13716 :     0.7624 : Y :       1      3 :   
    TO BT BT BT BT SA                                                                                :     143    224 :    17.8774 : Y :   71432  71433 : <span class="r">DEVIANT</span>   
    TO BT BT SA                                                                                      :      72    132 :    17.6471 : Y :   71342  71341 : <span class="r">DEVIANT</span>   
    TO BT BT BT BT EC                                                                                :      90    117 :     3.5217 : Y :   71553  71555 :   
    TO BT BT AB                                                                                      :      58    108 :    15.0602 : Y :   71358  71344 : <span class="r">DEVIANT</span>   
    TO BT BT BT BT BT SA                                                                             :      71     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
    TO BT BT BT SA                                                                                   :      68     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
    TO BT BT BT BT AB                                                                                :      40     59 :     3.6465 : Y :   71440  71432 :   
    TO BT BT BT BT BT EC                                                                             :      45     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
    TO BT BT BR BT BT SA                                                                             :      26     40 :     2.9697 : Y :   71537  71534 :   
    TO BT BT BT AB                                                                                   :      38      1 :     0.0000 : N :   71392  73345 : C2EXC  
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :      20     35 :     4.0909 : Y :   71583  71580 :   
    TO BT BT BT BT BT AB                                                                             :      27     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
    TO BT BR BT SA                                                                                   :      11     17 :     0.0000 : N :   71532  71537 : C2EXC  
    TO BT BT BT BR BT BT BT SA                                                                       :      10     13 :     0.0000 : N :   71561  71549 : C2EXC  
    TO BT BT BT BT BR BT BT SA                                                                       :       5     12 :     0.0000 : N :   71835  71825 : C2EXC  
    TO BT BT BT BT BT BR BT BT BT BT SA                                                              :      11     -1 :     0.0000 : N :   71575     -1 : BZERO C2EXC  
    TO BT BT BT BT EX                                                                                :       5     10 :     0.0000 : N :   71609  71586 : C2EXC  
    TO BT BT BT BR BT BT SA                                                                          :      10     -1 :     0.0000 : N :   71566     -1 : C2EXC  
    TO BT BT BT BT BT BT SA                                                                          :       3      9 :     0.0000 : N :   73056  72037 : C2EXC  
    TO BT BT BT BT BT BR BT BT SA                                                                    :       8     -1 :     0.0000 : N :   71826     -1 : C2EXC  
    TO BT BT BR BT SA                                                                                :       8     -1 :     0.0000 : N :   71538     -1 : C2EXC  
    TO BT BT BT BR BT SA                                                                             :       7      6 :     0.0000 : N :   71823  71822 : C2EXC  
    TO BT BT BR BR BR BT BT SA                                                                       :      -1      6 :     0.0000 : N :      -1  71539 : C2EXC  
    TO BT BT BT BT BR BT BT BT SA                                                                    :       5     -1 :     0.0000 : N :   71546     -1 : C2EXC  
    TO BT BT BT BT BT BT EC                                                                          :       3      5 :     0.0000 : N :   73281  73281 : C2EXC  
    TO BT BT BT BT BT EX                                                                             :       3     -1 :     0.0000 : N :   71600     -1 : C2EXC  
    TO BT BT BT BT BR BT BR BT SA                                                                    :       3     -1 :     0.0000 : N :   71638     -1 : C2EXC  
    TO BT BT BT BT BT BR BT BT BT SA                                                                 :       1      3 :     0.0000 : N :   73303  71837 : C2EXC  
    TO BT AB                                                                                         :       3      2 :     0.0000 : N :   71659  73136 : C2EXC  
    TO BT BT BT BR BR BR BT BT AB                                                                    :       2     -1 :     0.0000 : N :   72044     -1 : C2EXC  
    TO BT BT BT BT BR BT BT BT BT AB                                                                 :      -1      2 :     0.0000 : N :      -1  71696 : C2EXC  
    TO BT BT BT BT BR BT BT BR BT BT SA                                                              :       1      2 :     0.0000 : N :   73095  71614 : C2EXC  
    TO BT BT BT BT BT BT BT SA                                                                       :       2     -1 :     0.0000 : N :   73278     -1 : C2EXC  
    TO BT BT BT BT BT BT BR BT BT BT BT SA                                                           :      -1      2 :     0.0000 : N :      -1  73279 : C2EXC  
    TO BT BT BT BT BT BT BT EC                                                                       :       2     -1 :     0.0000 : N :   73282     -1 : C2EXC  
    TO BT BT BT BR BT BT BT AB                                                                       :      -1      2 :     0.0000 : N :      -1  73062 : C2EXC  
    TO BT BT BR BT BT AB                                                                             :       2      2 :     0.0000 : N :   71753  72046 : C2EXC  
    TO BT SC BT SA                                                                                   :      -1      2 :     0.0000 : N :      -1  71976 : C2EXC  
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    TO BT BT BT BT BT SA                                                                             :      71     -1 :     0.0000 : N :   71455     -1 : BZERO C2EXC  
    TO BT BT BT SA                                                                                   :      68     -1 :     0.0000 : N :   71352     -1 : BZERO C2EXC  
    TO BT BT BT BT BT EC                                                                             :      45     -1 :     0.0000 : N :   71554     -1 : BZERO C2EXC  
    TO BT BT BT BT BT AB                                                                             :      27     -1 :     0.0000 : N :   71434     -1 : BZERO C2EXC  
    TO BT BT BT BT BT BR BT BT BT BT SA                                                              :      11     -1 :     0.0000 : N :   71575     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc DEVIANT 
    TO BT BT BT BT SA                                                                                :     143    224 :    17.8774 : Y :   71432  71433 : <span class="r">DEVIANT</span>   
    TO BT BT SA                                                                                      :      72    132 :    17.6471 : Y :   71342  71341 : <span class="r">DEVIANT</span>   
    TO BT BT AB                                                                                      :      58    108 :    15.0602 : Y :   71358  71344 : <span class="r">DEVIANT</span>   
    ]sseq_index_ab::desc
    </pre>



With refine the chi2 comes into line, with no AZERO,BZERO or DEVIANT
----------------------------------------------------------------------- 

.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc  [CHI2 <span class="r">  sum     2.3424 ndf  9.0000 sum/ndf     0.2603 </span> ]
    TO SA                                                                                            :   85301  85453 :     0.1353 : Y :       0      0 :   
    TO AB                                                                                            :   13861  13716 :     0.7624 : Y :       1      3 :   
    TO BT BT BT BT SA                                                                                :     218    224 :     0.0814 : Y :   71432  71433 :   
    TO BT BT SA                                                                                      :     128    132 :     0.0615 : Y :   71342  71341 :   
    TO BT BT BT BT EC                                                                                :     131    117 :     0.7903 : Y :   71553  71555 :   
    TO BT BT AB                                                                                      :     101    108 :     0.2344 : Y :   71358  71344 :   
    TO BT BT BT BT AB                                                                                :      57     59 :     0.0345 : Y :   71440  71432 :   
    TO BT BT BR BT BT SA                                                                             :      40     40 :     0.0000 : Y :   71537  71534 :   
    TO BT BT BT BT BR BT BT BT BT SA                                                                 :      31     35 :     0.2424 : Y :   71583  71580 :   
    TO BT BR BT SA                                                                                   :      19     17 :     0.0000 : N :   71532  71537 : C2EXC  
    TO BT BT BT BR BT BT BT SA                                                                       :      14     13 :     0.0000 : N :   71554  71549 : C2EXC  
    TO BT BT BT BT BR BT BT SA                                                                       :       9     12 :     0.0000 : N :   71824  71825 : C2EXC  
    TO BT BT BT BR BT SA                                                                             :      11      6 :     0.0000 : N :   71822  71822 : C2EXC  
    TO BT BT BT BT EX                                                                                :      10     10 :     0.0000 : N :   71590  71586 : C2EXC  
    TO BT BT BT BT BT BT SA                                                                          :       5      9 :     0.0000 : N :   73056  72037 : C2EXC  
    TO BT BT BT AB                                                                                   :       6      1 :     0.0000 : N :   71585  73345 : C2EXC  
    TO BT BT BR BR BR BT BT SA                                                                       :       2      6 :     0.0000 : N :   71538  71539 : C2EXC  
    TO BT AB                                                                                         :       5      2 :     0.0000 : N :   71405  73136 : C2EXC  
    TO BT BT BT BT BT BT EC                                                                          :       5      5 :     0.0000 : N :   73281  73281 : C2EXC  
    TO BT BT BT BT BR BT BR BT SA                                                                    :       4     -1 :     0.0000 : N :   71638     -1 : C2EXC  
    TO BT BT BR BT BT AB                                                                             :       3      2 :     0.0000 : N :   71753  72046 : C2EXC  
    TO BT BT BT BT BT BR BT BT BT SA                                                                 :       3      3 :     0.0000 : N :   73277  71837 : C2EXC  


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc AZERO 
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc BZERO 
    ]sseq_index_ab::desc
    </pre>


.. raw:: html

    <pre class="mypretiny">
    [sseq_index_ab::desc DEVIANT 
    ]sseq_index_ab::desc
    </pre>



