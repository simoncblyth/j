G4CXTest_GEOM_disrepant_Chimney
=================================


::

   ~/o/G4CXTest_GEOM.sh ana 


    In [1]: w = a.q_startswith("TO BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT") ; w                                                                         
    Out[1]: 
    array([ 11040,  15219, 118322, 152607, 165838, 215978, 299136, 374379, 395244, 422394, 427598, 434101, 443666, 445392, 479186, 531698, 549984, 592656, 604821, 637582, 656052, 736283, 777988, 789501,
           821402, 837105, 853410, 898084, 903045, 923645, 927731, 974750, 989689])

    In [2]: a.f.record[w[0],:,0]
    Out[2]: 
    array([[   -1.594,     0.835,    99.984,     0.   ],
           [ -284.142,   148.854, 17823.998,    81.302],
           [ -315.513,   165.289, 20000.   ,    88.563],
           [ -332.369,   174.119, 21750.   ,    94.401],
           [ -332.383,   174.127, 21752.   ,    94.407],
           [ -344.817,   180.641, 23500.   ,   103.396],
           [ -368.795,   193.202, 25752.   ,   110.911],
           [ -409.746,   214.655, 29598.2  ,   123.745],
           [ -409.753,   214.658, 29598.799,   123.747],
           [ -409.762,   214.663, 29599.7  ,   123.75 ],
           [ -409.764,   214.664, 29599.85 ,   123.75 ],

    In [6]: b.f.record[w[0],:,0]
    Out[6]: 
    array([[  -96.287,     1.155,    26.974,     0.   ],
           [-1209.685,    14.51 ,   338.88 ,     5.946],
           [ -526.46 ,   669.372,  -106.271,    11.324],
           [ -378.484,  5043.437,  2154.593,    36.655],
           [-4193.48 , 10921.861,  4487.588,    74.636],
           [-4890.896, 14143.509,  9451.471,   106.177],
           [-4906.948, 14217.333,  9564.741,   106.875],
           [-5060.682, 15014.834, 10921.09 ,   114.114],
           [-5062.732, 15025.474, 10939.185,   114.21 ],
           [-5063.558, 15029.474, 10946.02 ,   114.251],
           [-5063.751, 15030.477, 10947.727,   114.26 ],
           [-5064.264, 15032.978, 10951.997,   114.286],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],



* A and B photons are not the same : despite same genstep
  (mock curand not providing same randoms as curand here)

  * HMM: could make it do so with U4Random : that would be convenient for debug this and other issues
  * or could use input photons ?  


Looks like not moving much, stuck in something ?::

    In [10]: a.f.record[w[0],:,1,3].view(np.int32)
    Out[10]: 
    array([    0,     0,     0,     0,     0,     0,         0,     0, 
               47465, 47465, 47465, 47465, 47465, 47465,     0,     0, 
               47469, 47469, 47469, 47469, 47469, 47469,     0,     0, 
               47633, 47633, 47633, 47633, 47633, 47633,     0,     0], dtype=int32)


iindex : repeated pattern of 6+2 ? 

::

    In [3]: cf.inst.shape
    Out[3]: (47887, 4, 4)


::

    In [4]: cf.inst[47465]
    Out[4]:
    array([[    1.  ,     0.  ,     0.  ,     0.  ],
           [    0.  ,     1.  ,     0.  ,     0.  ],
           [    0.  ,     0.  ,     1.  ,     0.  ],
           [    0.  ,   846.3 , 29604.85,      nan]], dtype=float32)

    In [5]: cf.inst[47469]
    Out[5]:
    array([[    0.  ,     1.  ,     0.  ,     0.  ],
           [   -1.  ,     0.  ,     0.  ,     0.  ],
           [    0.  ,     0.  ,     1.  ,     0.  ],
           [ -846.3 ,     0.  , 29619.15,      nan]], dtype=float32)

    In [6]: cf.inst[47633]
    Out[6]:
    array([[    1.  ,     0.  ,     0.  ,     0.  ],
           [    0.  ,     1.  ,     0.  ,     0.  ],
           [    0.  ,     0.  ,     1.  ,     0.  ],
           [    0.  ,   846.3 , 29854.85,      nan]], dtype=float32)


::

    In [12]: aa = np.array([47465,47469,47633])

    In [13]: cf.inst[aa,:,3].view(np.int32)
    Out[13]: 
    array([[47465,     8,     0,    -1],
           [47469,     8,     0,    -1],
           [47633,     8,     0,    -1]], dtype=int32)

    #sqat4.h ins_idx gas_idx s_id  s_idx      

    In [15]: cf.mmlabel
    Out[15]: 
    array(['2923:sWorld', '5:PMT_3inch_pmt_solid', '9:NNVTMCPPMTsMask_virtual', '12:HamamatsuR12860sMask_virtual', '6:mask_PMT_20inch_vetosMask_virtual', '1:sStrutBallhead', '1:base_steel',
           '1:uni_acrylic1', '130:sPanel'], dtype=object)

    In [16]: np.c_[cf.mmlabel]
    Out[16]: 
    array([['2923:sWorld'],
           ['5:PMT_3inch_pmt_solid'],
           ['9:NNVTMCPPMTsMask_virtual'],
           ['12:HamamatsuR12860sMask_virtual'],
           ['6:mask_PMT_20inch_vetosMask_virtual'],
           ['1:sStrutBallhead'],
           ['1:base_steel'],
           ['1:uni_acrylic1'],
           ['130:sPanel']], dtype=object)


* up in top tracker panels 


::

    In [22]: a.f.record[w[0],:,3].view(np.uint32)
    Out[22]:
    array([[      4096,          0,      11040,       4096],
           [   7735296,          0, 2147494688,       6144],
           [    526336,          0, 2147494688,       6144],
           [   6293504,          0,      11040,       6144],
           [    460800,          0, 2147494688,       6144],
           [    526336,          0,      11040,       6144],
           [    460800,          0, 2147494688,       6144],
           [    460800,          0, 2147494688,       6144],
           [    788480,          0, 2147494688,       6144],
           [    854016,          0, 2147494688,       6144],
           [    919552,          0, 2147494688,       6144],
           [    919552,          0,      11040,       6144],
           [    854016,          0,      11040,       6144],
           [    788480,          0,      11040,       6144],
           [    460800,          0,      11040,       6144],
           [    460800,          0, 2147494688,       6144],
           [    788480,          0, 2147494688,       6144],
           [    854016,          0, 2147494688,       6144],
           [    919552,          0, 2147494688,       6144],
           [    919552,          0,      11040,       6144],
           [    854016,          0,      11040,       6144],
           [    788480,          0,      11040,       6144],
           [    460800,          0,      11040,       6144],
           [    460800,          0, 2147494688,       6144],
           [    788480,          0, 2147494688,       6144],
           [    854016,          0, 2147494688,       6144],
           [    919552,          0, 2147494688,       6144],
           [    919552,          0,      11040,       6144],
           [    854016,          0,      11040,       6144],
           [    788480,          0,      11040,       6144],
           [    460800,          0,      11040,       6144],
           [    460800,          0, 2147494688,       6144]], dtype=uint32)

::

    +----+----------------+----------------+----------------+----------------+--------------------------+
    |    | boundary_flag  |  identity      |  orient_idx    |  flagmask      |  (unsigned)              |
    | q3 | (3,0)          |                |  orient:1bit   |                |                          |
    |    |                |                |                |                |                          |
    +----+----------------+----------------+----------------+----------------+--------------------------+


::

    In [28]: np.c_[a.f.record[w[0],:,3,0].view(np.uint32) >> 16]
    Out[28]:
    array([[  0],
           [118],
           [  8],
           [ 96],
           [  7],
           [  8],
           [  7],
           [  7],
           [ 12],
           [ 13],
           [ 14],
           [ 14],
           [ 13],
           [ 12],
           [  7],
           [  7],
           [ 12],
           [ 13],
           [ 14],
           [ 14],
           [ 13],
           [ 12],
           [  7],
           [  7],
           [ 12],
           [ 13],
           [ 14],
           [ 14],
           [ 13],
           [ 12],
           [  7],
           [  7]], dtype=uint32)


    In [40]: np.c_[cf.sim.stree.standard.bnd_names[bnd]]
    Out[40]:
    array([['Galactic///Galactic'],
           ['Vacuum/NNVTMCPPMT_PMT_20inch_mcp_edge_opsurface//Steel'],
           ['Air///LS'],
           ['vetoWater/CDTyvekSurface//Tyvek'],
           ['Air///Air'],
           ['Air///LS'],
           ['Air///Air'],
           ['Air///Air'],
           ['Aluminium///Adhesive'],
           ['Adhesive///TiO2Coating'],
           ['TiO2Coating///Scintillator'],
           ['TiO2Coating///Scintillator'],
           ['Adhesive///TiO2Coating'],
           ['Aluminium///Adhesive'],
           ['Air///Air'],
           ['Air///Air'],
           ['Aluminium///Adhesive'],
           ['Adhesive///TiO2Coating'],
           ['TiO2Coating///Scintillator'],
           ['TiO2Coating///Scintillator'],
           ['Adhesive///TiO2Coating'],
           ['Aluminium///Adhesive'],
           ['Air///Air'],
           ['Air///Air'],
           ['Aluminium///Adhesive'],
           ['Adhesive///TiO2Coating'],
           ['TiO2Coating///Scintillator'],
           ['TiO2Coating///Scintillator'],
           ['Adhesive///TiO2Coating'],
           ['Aluminium///Adhesive'],
           ['Air///Air'],
           ['Air///Air']], dtype='<U122')


G4CXApp.h::

    233     else if(SEventConfig::IsRunningModeTorch())
    234     {
    235         int idx_arg = eventID ;
    236         NP* gs = SEvent::MakeTorchGenstep(idx_arg) ;
    237         NP* ph = SGenerate::GeneratePhotons(gs);
    238         U4VPrimaryGenerator::GeneratePrimaries_From_Photons(event, ph);
    239         delete ph ;
    240 
    241         SEvent::SetGENSTEP(gs);  // picked up by 
    242     }



Start positions of first 10 photons::

    In [2]: a.f.record[:10,0,0]
    Out[2]: 
    array([[-81.226,  33.078, -48.044,   0.   ],
           [-52.285,  13.297, -84.199,   0.   ],
           [ -0.052,  38.729,  92.196,   0.   ],
           [-34.665,   1.145, -93.793,   0.   ],
           [ 49.74 ,  17.209, -85.028,   0.   ],
           [-52.054,  84.707,  10.73 ,   0.   ],
           [-75.095,  56.929, -33.464,   0.   ],
           [ 44.075, -44.398,  78.014,   0.   ],
           [-99.196,  11.162,   5.956,   0.   ],
           [ 96.366,  26.584,  -2.639,   0.   ]], dtype=float32)

    In [3]: b.f.record[:10,0,0]
    Out[3]: 
    array([[ 44.585,  51.482,  73.225,   0.   ],
           [ 98.656,  13.109,   9.757,   0.   ],
           [ 81.025, -50.455,  29.82 ,   0.   ],
           [ 89.111,  45.   ,   5.85 ,   0.   ],
           [-65.375, -74.371, -13.969,   0.   ],
           [-53.56 , -19.732,  82.109,   0.   ],
           [ 14.451,  80.22 , -57.93 ,   0.   ],
           [  0.138,  98.668,  16.266,   0.   ],
           [ 29.85 , -85.885,  41.627,   0.   ],
           [-12.479,  99.088,   5.081,   0.   ]], dtype=float32)




SGenerate__test.sh first 10::

    In [5]: f.ph[:10,0,:3]    
    Out[5]: 
    array([[ 44.585,  51.482,  73.225],
           [ 98.656,  13.109,   9.757],
           [ 81.025, -50.455,  29.82 ],
           [ 89.111,  45.   ,   5.85 ],
           [-65.375, -74.371, -13.969],
           [-53.56 , -19.732,  82.109],
           [ 14.451,  80.22 , -57.93 ],
           [  0.138,  98.668,  16.266],
           [ 29.85 , -85.885,  41.627],
           [-12.479,  99.088,   5.081]], dtype=float32)


    In [2]: f.ph[:10,0]   ## WITHOUT MOCK_CURAND GET SAME PHOTONS
    Out[2]: 
    array([[ 44.585,  51.482,  73.225,   0.   ],
           [ 98.656,  13.109,   9.757,   0.   ],
           [ 81.025, -50.455,  29.82 ,   0.   ],
           [ 89.111,  45.   ,   5.85 ,   0.   ],
           [-65.375, -74.371, -13.969,   0.   ],
           [-53.56 , -19.732,  82.109,   0.   ],
           [ 14.451,  80.22 , -57.93 ,   0.   ],
           [  0.138,  98.668,  16.266,   0.   ],
           [ 29.85 , -85.885,  41.627,   0.   ],
           [-12.479,  99.088,   5.081,   0.   ]], dtype=float32)




Using SGenerate__GeneratePhotons_RNG_PRECOOKED=1 are using the
precooked randoms from curand to provide Geant4 with the same 
start photons as Opticks::

    In [1]: f.ph[:10,0]
    Out[1]: 
    array([[-81.226,  33.078, -48.044,   0.   ],
           [-52.285,  13.297, -84.199,   0.   ],
           [ -0.052,  38.729,  92.196,   0.   ],
           [-34.665,   1.145, -93.793,   0.   ],
           [ 49.74 ,  17.209, -85.028,   0.   ],
           [-52.054,  84.707,  10.73 ,   0.   ],
           [-75.095,  56.929, -33.464,   0.   ],
           [ 44.075, -44.398,  78.014,   0.   ],
           [-99.196,  11.162,   5.956,   0.   ],
           [ 96.366,  26.584,  -2.639,   0.   ]], dtype=float32)

::

    epsilon:opticks blyth$ git log -n1
    commit eaf615a4e9e75707ccdc799abe64d69f1cfcf650 (HEAD -> master, origin/master, origin/HEAD)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Tue Dec 12 17:00:35 2023 +0800

        try to arrange G4CXTest_GEOM.sh TORCH running to use the same initial photons for B as for A by using precooked randoms in SGenerate when an environment key is set : this to help with issue debugging
    epsilon:opticks blyth$ 


::

    2023-12-12 18:57:36.953 INFO  [410170] [G4CXApp::BeamOn@342] [ OPTICKS_NUM_EVENT=1
    2023-12-12 18:59:10.215 INFO  [410170] [G4CXApp::GeneratePrimaries@223] [ SEventConfig::RunningModeLabel SRM_TORCH eventID 0
    SGenerate::GeneratePhotons SGenerate__GeneratePhotons_RNG_PRECOOKED : YES
    s_seq::setSequenceIndexFATAL : OUT OF RANGE :  m_seq_ni 100000 index_ 100000 idx 100000 (must be < m_seq_ni )  desc s_seq::desc
     m_seqpath /home/blyth/.opticks/precooked/QSimTest/rng_sequence/rng_sequence_f_ni1000000_nj16_nk16_tranche100000/rng_sequence_f_ni100000_nj16_nk16_ioffset000000.npy
     m_seq (100000, 16, 16, )
    G4CXTest: /home/blyth/junotop/ExternalLibs/opticks/head/include/SysRap/s_seq.h:156: void s_seq::setSequenceIndex(int): Assertion `idx_in_range' failed.
    ./G4CXTest_GEOM.sh: line 273: 410170 Aborted                 (core dumped) $bin
    ./G4CXTest_GEOM.sh run error
    N[blyth@localhost opticks]$ 



Scaling back to 100k and it works with same initial photons::

    In [3]: a.f.record[:,0,0]
    Out[3]:
    array([[-81.226,  33.078, -48.044,   0.   ],
           [-52.285,  13.297, -84.199,   0.   ],
           [ -0.052,  38.729,  92.196,   0.   ],
           [-34.665,   1.145, -93.793,   0.   ],
           [ 49.74 ,  17.209, -85.028,   0.   ],
           ...,
           [ -1.951, -74.26 , -66.945,   0.   ],
           [ 44.346,  71.254, -54.372,   0.   ],
           [ 23.053,  73.62 , -63.629,   0.   ],
           [ 91.344,  31.719, -25.498,   0.   ],
           [-52.174,  20.534, -82.802,   0.   ]], dtype=float32)

    In [4]: b.f.record[:,0,0]
    Out[4]:
    array([[-81.226,  33.078, -48.044,   0.   ],
           [-52.285,  13.297, -84.199,   0.   ],
           [ -0.052,  38.729,  92.196,   0.   ],
           [-34.665,   1.145, -93.793,   0.   ],
           [ 49.74 ,  17.209, -85.028,   0.   ],
           ...,
           [ -1.951, -74.26 , -66.945,   0.   ],
           [ 44.346,  71.254, -54.372,   0.   ],
           [ 23.053,  73.62 , -63.629,   0.   ],
           [ 91.344,  31.719, -25.498,   0.   ],
           [-52.174,  20.534, -82.802,   0.   ]], dtype=float32)


BUT not enough stats to see issue::

    c2sum/c2n:c2per(C2CUT)  341.80/366:0.934 (30) pv[1.000,> 0.05 : null-hyp ] 
    c2sum :   341.7979 c2n :   366.0000 c2per:     0.9339  C2CUT:   30 
    N[blyth@localhost opticks]$ 



Difference in hi Z::


    In [28]: np.where( a.f.record[:,:,0,2] > 29000 )[0].shape
    Out[28]: (1394,)

    In [29]: np.where( b.f.record[:,:,0,2] > 29000 )[0].shape
    Out[29]: (27,)


    In [30]: aw = np.where( a.f.record[:,:,0,2] > 29000 )[0]

    In [31]: bw = np.where( b.f.record[:,:,0,2] > 29000 )[0]


    In [34]: np.c_[np.unique(a.q[aw], return_counts=True)]
    Out[34]:
    array([[b'TO BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'72'],
           [b'TO BT BR BT BT BT SC BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT SA ', b'2'],
           [b'TO BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'48'],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'72'],
           [b'TO BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'825'],
           [b'TO BT BT BT BT BT BT SA                                                                         ', b'1'],
           [b'TO BT BT BT BT BT SA                                                                            ', b'3'],
           [b'TO RE BT BT BR BT BT SC BT BT BT SA                                                             ', b'2'],
           [b'TO RE BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'46'],
           [b'TO RE BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'96'],
           [b'TO RE BT DR BT BR BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'21'],
           [b'TO RE SC SC SC SC BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'19'],
           [b'TO SC BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'23'],
           [b'TO SC BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'72'],
           [b'TO SC BT BT BT BT DR DR DR BT BR BR BT BT BR BT BT BT SA                                        ', b'2'],
           [b'TO SC RE BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'22'],
           [b'TO SC RE BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'46'],
           [b'TO SC SC BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT ', b'22']], dtype='|S96')


HUH: G4 not managing to get out the chimney ?::

    In [35]: np.c_[np.unique(b.q[bw], return_counts=True)]
    Out[35]: 
    array([[b'TO BT BT BT BT BT BT SA                                                                         ', b'4'],
           [b'TO BT BT BT BT BT SA                                                                            ', b'3'],
           [b'TO BT BT BT BT SA                                                                               ', b'20']], dtype='|S96')


::

    In [1]: b.q[sel]
    Out[1]: 
    array([[b'TO BT BT BT BT SA                                                                               '],
           [b'TO SC BT SA                                                                                     '],
           [b'TO BT BT BT BT BT SA                                                                            '],
           [b'TO BT BT SC SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT BT BT BT BT SA                                                                         '],
           [b'TO BT AB                                                                                        '],
           [b'TO RE BT BT BT SA                                                                               '],
           [b'TO RE SC BT BT BT BT SA                                                                         '],
           [b'TO SC SC SC BT BT BT BT DR DR DR DR SC SA                                                       '],
           [b'TO SC BT SA                                                                                     '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BR BT BT BT SA                                                                         '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO RE RE BT BT BR BT BT SA                                                                      '],
           [b'TO BT SC DR SA                                                                                  '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO SC SC RE BT BT BT SA                                                                         '],
           [b'TO BT DR SA                                                                                     '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT BT BT SA                                                                         '],
           [b'TO BT BT BT BT SA                                                                               '],



HMM : Looks like diff geom in Chimney.

Try to so a simtrace up there.


Workstation::

    ~/o/cxt_min.sh

Laptop::

    ~/o/cxt_min.sh grab 
    NOGRID=1 ~/o/cxt_min.sh ana


HMM: seems simtrace frame targetting not working 


