3inch_PMT_geometry_after_virtual_delta
=========================================

Context 
----------

* from :doc:`3inch_PMT_geometry`


After Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM = 1  AND enabling osur implicits : NO DISCREPANTS
-------------------------------------------------------------------------------------------------

::

    a.CHECK : circle_inwards_100 
    b.CHECK : circle_inwards_100 
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :     4.9681 c2n :     4.0000 c2per:     1.2420  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)   4.97/4:1.242 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT SD   ' ' 0' '  4351   4354' ' 0.0010' '   310    310']
     [' 1' 'TO BT SA      ' ' 1' '  3449   3449' ' 0.0000' '  5775   5775']
     [' 2' 'TO BT BT SA   ' ' 2' '  2145   2162' ' 0.0671' '     0      0']
     [' 3' 'TO BT BR BT SA' ' 3' '    27     13' ' 4.9000' '   107   1143']
     [' 4' 'TO BT BT AB   ' ' 4' '    12      9' ' 0.0000' '   431   1226']
     [' 5' 'TO AB         ' ' 5' '    10      7' ' 0.0000' '   336    615']
     [' 6' 'TO SC SA      ' ' 6' '     2      3' ' 0.0000' '  1338   4018']
     [' 7' 'TO BT AB      ' ' 7' '     3      2' ' 0.0000' '  2413   1246']
     [' 8' 'TO SC BT BT SD' ' 8' '     1      0' ' 0.0000' '  1859     -1']
     [' 9' 'TO SC AB      ' ' 9' '     0      1' ' 0.0000' '    -1   5925']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    []

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    []


After Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM = 1  : still discrepants
--------------------------------------------------------------------------

::

    a.CHECK : circle_inwards_100 
    b.CHECK : circle_inwards_100 
    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :  6837.5391 c2n :     6.0000 c2per:  1139.5898  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  6837.54/6:1139.590 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT SD      ' ' 0' '  4351   4354' ' 0.0010' '   310    310']
     [' 1' 'TO BT SA         ' ' 1' '     0   3449' '3449.0000' '    -1   5775']
     [' 2' 'TO BT BT SA      ' ' 2' '  2147   2162' ' 0.0522' '     0      0']
     [' 3' 'TO BT BT BT SD   ' ' 3' '  1710      0' '1710.0000' '  5934     -1']
     [' 4' 'TO BT BR BT SA   ' ' 4' '  1379     13' '1340.4856' '   107   1143']
     [' 5' 'TO BT BT BT SA   ' ' 5' '   338      0' '338.0000' '  5776     -1']
     [' 6' 'TO BT BT BT AB   ' ' 6' '    28      0' ' 0.0000' '  5780     -1']
     [' 7' 'TO BT BT AB      ' ' 7' '    15      9' ' 0.0000' '   431   1226']
     [' 8' 'TO BT BR BT AB   ' ' 8' '    11      0' ' 0.0000' '  6137     -1']
     [' 9' 'TO AB            ' ' 9' '    10      7' ' 0.0000' '   336    615']
     ['10' 'TO BT BT BR AB   ' '10' '     4      0' ' 0.0000' '  5851     -1']
     ['11' 'TO SC SA         ' '11' '     2      3' ' 0.0000' '  1338   4018']
     ['12' 'TO BT AB         ' '12' '     3      2' ' 0.0000' '  2413   1246']
     ['13' 'TO SC BT BT SD   ' '13' '     1      0' ' 0.0000' '  1859     -1']
     ['14' 'TO SC AB         ' '14' '     0      1' ' 0.0000' '    -1   5925']
     ['15' 'TO BT BR BT SC SA' '15' '     1      0' ' 0.0000' '  8255     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][bzero]  ## bzero: A histories not in B 
    [[' 3' 'TO BT BT BT SD   ' ' 3' '  1710      0' '1710.0000' '  5934     -1']
     [' 5' 'TO BT BT BT SA   ' ' 5' '   338      0' '338.0000' '  5776     -1']
     [' 6' 'TO BT BT BT AB   ' ' 6' '    28      0' ' 0.0000' '  5780     -1']
     [' 8' 'TO BT BR BT AB   ' ' 8' '    11      0' ' 0.0000' '  6137     -1']]

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][azero]  ## azero: B histories not in A 
    [[' 1' 'TO BT SA         ' ' 1' '     0   3449' '3449.0000' '    -1   5775']]
    PICK=AB MODE=0 SEL=0 ./G4CXAppTest.sh ana 
    not plotting as MODE 0 in environ
    not plotting as MODE 0 in environ



HMM : photons still getting in from the back in A : (THATS BEFORE ENABLING OSUR IMPLICITS)

* is this missing implicit in the geometry conversion ?
* how come B is doing "TO BT SA" and A is not ? 

What A does when B does "TO BT SA"::

    In [1]: np.c_[np.unique(a.q[b.q_startswith("TO BT SA")], return_counts=True)]
    Out[1]: 
    array([[b'TO BT AB                                                                                        ', b'1'],
           [b'TO BT BR BT AB                                                                                  ', b'11'],
           [b'TO BT BR BT SA                                                                                  ', b'1351'],
           [b'TO BT BR BT SC SA                                                                               ', b'1'],
           [b'TO BT BT AB                                                                                     ', b'3'],
           [b'TO BT BT BR AB                                                                                  ', b'4'],
           [b'TO BT BT BT AB                                                                                  ', b'28'],
           [b'TO BT BT BT SA                                                                                  ', b'337'],
           [b'TO BT BT BT SD                                                                                  ', b'1710'],
           [b'TO BT BT SA                                                                                     ', b'2'],
           [b'TO SC SA                                                                                        ', b'1']], dtype='|S96')

    In [2]: uq,nq=np.unique(a.q[b.q_startswith("TO BT SA")], return_counts=True)    

    In [5]: np.c_[uq,nq][np.argsort(nq)[::-1]]
    Out[5]: 
    array([[b'TO BT BT BT SD                                                                                  ', b'1710'],
           [b'TO BT BR BT SA                                                                                  ', b'1351'],
           [b'TO BT BT BT SA                                                                                  ', b'337'],
           [b'TO BT BT BT AB                                                                                  ', b'28'],
           [b'TO BT BR BT AB                                                                                  ', b'11'],
           [b'TO BT BT BR AB                                                                                  ', b'4'],
           [b'TO BT BT AB                                                                                     ', b'3'],
           [b'TO BT BT SA                                                                                     ', b'2'],
           [b'TO SC SA                                                                                        ', b'1'],
           [b'TO BT BR BT SC SA                                                                               ', b'1'],
           [b'TO BT AB                                                                                        ', b'1']], dtype='|S96')




::

    PICK=AB MODE=2 PIDX=5775 HSEL="TO BT SA" ./G4CXTest.sh ana
    PICK=AB MODE=2 PIDX=5934 HSEL="TO BT BT BT SD" FOCUS=0,-20,60 ./G4CXTest.sh ana

It is Water//Steel that is not doing the expected absortion::

    In [35]: boundary___(a.f.record[wb])
    Out[35]: 
    array([[0, 2, 6, 5, 0, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 2, 1, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           ...,
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 3, 5, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0],
           [0, 2, 6, 5, 0, 0, 0, 0, ..., 0, 0, 0, 0, 0, 0, 0, 0]], dtype=uint32)

    In [36]: cf.sim.bndnamedict
    Out[36]: 
    {0: 'Rock///Rock',
     1: 'Rock//water_rock_bs/Water',
     2: 'Water///Water',
     3: 'Water///Pyrex',
     4: 'Pyrex/tub3_photocathode_logsurf2/tub3_photocathode_logsurf1/Vacuum',
     5: 'Pyrex/tub3_absorb_logsurf2/tub3_absorb_logsurf1/Vacuum',
     6: 'Water///Steel'}


After enabling osur implicits are getting expected absorb onto Steel::

    In [1]: cf.sim.bndnamedict
    Out[1]: 
    {0: 'Rock///Rock',
     1: 'Rock//water_rock_bs/Water',
     2: 'Water///Water',
     3: 'Water///Pyrex',
     4: 'Pyrex/tub3_photocathode_logsurf2/tub3_photocathode_logsurf1/Vacuum',
     5: 'Pyrex/tub3_absorb_logsurf2/tub3_absorb_logsurf1/Vacuum',
     6: 'Water/Implicit_RINDEX_NoRINDEX_tub3_log_pv_tub3_cntr_phys//Steel'}





Implicits::

     580 inline int U4Tree::initNodes_r(
     581     const G4VPhysicalVolume* const pv,
     582     const G4VPhysicalVolume* const pv_p,
     583     int depth,
     584     int sibdex,
     585     int parent )
     586 {
     587     // preorder visit before recursive call 
     588 
     589     U4TreeBorder border(st, num_surfaces, pv, pv_p) ;
     590 
     591     int omat = stree::GetPointerIndex<G4Material>(      materials, border.omat_);
     592     int osur = stree::GetPointerIndex<G4LogicalSurface>(surfaces,  border.osur_);
     593     int isur = stree::GetPointerIndex<G4LogicalSurface>(surfaces,  border.isur_);
     594     int imat = stree::GetPointerIndex<G4Material>(      materials, border.imat_);
     595 
     596     int4 bd = {omat, osur, isur, imat } ;
     597 
     598 #ifdef U4_OPTICAL_DEBUG
     599     if(border.is_flagged()) std::cout
     600         << "U4Tree::initNodes_r border.is_flagged " << std::endl
     601         << " (omat,osur,isur,imat) " << bd << std::endl
     602         << border.desc()
     603         << std::endl
     604         ;
     605 #endif
     606 
     607     bool do_osur = false ; // **THIS NEEDS TO BE ENABLED FOR GEANT4 MATCHING** 
     608     bool do_isur = true ;
     609     // overrides add implicit surfaces when no prior surface and RINDEX->NoRINDEX 
     610     if(do_osur && border.has_osur_override(bd)) border.do_osur_override(bd);
     611     if(do_isur && border.has_isur_override(bd)) border.do_isur_override(bd);
     612 
     613     int boundary = st->add_boundary(bd) ;
     614     assert( boundary > -1 );
     615   
     616 






::

    In [6]: wb = b.q_startswith("TO BT SA")

    In [7]: wb
    Out[7]: array([5775, 5776, 5777, 5778, 5779, ..., 9221, 9222, 9223, 9224, 9225])

    In [8]: a.q[wb[0]]
    Out[8]: array([b'TO BT BT SA                                                                                     '], dtype='|S96')

    In [9]: a.f.record[wb[0],:3]
    Out[9]:
    array([[[-88.377,   0.   , -46.793,   0.   ],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-36.234,   0.   , -19.185,   0.271],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,  -0.   ,   0.   ]],

           [[-29.999,   0.   , -15.884,   0.303],
            [  0.774,   0.   ,   0.634,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,  -0.   ,   0.   ]]], dtype=float32)

    In [10]: a.f.record[wb[0],:4]
    Out[10]:
    array([[[-88.377,   0.   , -46.793,   0.   ],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-36.234,   0.   , -19.185,   0.271],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,  -0.   ,   0.   ]],

           [[-29.999,   0.   , -15.884,   0.303],
            [  0.774,   0.   ,   0.634,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,  -0.   ,   0.   ]],

           [[-28.429,   0.   , -14.598,   0.313],
            [  0.774,   0.   ,   0.634,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,  -0.   ,   0.   ]]], dtype=float32)

    In [11]: b.f.record[wb[0],:4]
    Out[11]:
    array([[[-88.377,   0.   , -46.793,   0.   ],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-36.234,   0.   , -19.185,   0.271],
            [  0.884,   0.   ,   0.468,     nan],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[-29.999,   0.   , -15.884,   0.303],
            [  0.884,   0.   ,   0.468,   0.   ],
            [  0.   ,  -1.   ,   0.   , 420.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]],

           [[  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ],
            [  0.   ,   0.   ,   0.   ,   0.   ]]], dtype=float32)

    In [12]: wb[0]
    Out[12]: 5775

    In [13]: b.f.record[wb[0],:4,0]
    Out[13]:
    array([[-88.377,   0.   , -46.793,   0.   ],
           [-36.234,   0.   , -19.185,   0.271],
           [-29.999,   0.   , -15.884,   0.303],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)

    In [14]: a.f.record[wb[0],:4,0]
    Out[14]:
    array([[-88.377,   0.   , -46.793,   0.   ],
           [-36.234,   0.   , -19.185,   0.271],
           [-29.999,   0.   , -15.884,   0.303],
           [-28.429,   0.   , -14.598,   0.313]], dtype=float32)

    In [15]: b.f.record[wb[0],:4,0]
    Out[15]:
    array([[-88.377,   0.   , -46.793,   0.   ],
           [-36.234,   0.   , -19.185,   0.271],
           [-29.999,   0.   , -15.884,   0.303],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)

    In [16]: b.f.record[wb[0],:4,0] - a.f.record[wb[0],:4,0]
    Out[16]:
    array([[ 0.   ,  0.   , -0.   ,  0.   ],
           [-0.   ,  0.   , -0.   ,  0.   ],
           [ 0.   ,  0.   , -0.   ,  0.   ],
           [28.429,  0.   , 14.598, -0.313]], dtype=float32)

    In [17]: np.set_printoptions(precision=8)

    In [18]: b.f.record[wb[0],:4,0] - a.f.record[wb[0],:4,0]
    Out[18]:
    array([[ 0.        ,  0.        , -0.00002289,  0.        ],
           [-0.00000381,  0.        , -0.00000954,  0.        ],
           [ 0.        ,  0.        , -0.00000763,  0.00000003],
           [28.42909   ,  0.        , 14.598051  , -0.31329522]], dtype=float32)

    In [19]:




Problem maybe non-parent-child border surface
-----------------------------------------------


Heirarchy::

    m_logical_pmt
       body_phys
          inner1
          inner2
       cntr_phys


Note that most of the below borders are not translated
into Opticks because the pv pairs are not parent-child. 
However it dont matter as no photons inside there anyhow. 

::

    In [1]: cf.sim.bndnamedict
    Out[1]: 
    {0: 'Rock///Rock',
     1: 'Rock//water_rock_bs/Water',
     2: 'Water///Water',
     3: 'Water///Pyrex',
     4: 'Pyrex/tub3_photocathode_logsurf2/tub3_photocathode_logsurf1/Vacuum',       ## inner1 / body
     5: 'Pyrex/tub3_absorb_logsurf2/tub3_absorb_logsurf1/Vacuum',                   ## inner2 / body
     6: 'Water/Implicit_RINDEX_NoRINDEX_tub3_log_pv_tub3_cntr_phys//Steel'}


::

    369 void
    370 Tub3inchPMTV3Manager::helper_make_optical_surface()
    371 {   
    372     // inner1 / body
    373     new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf1",
    374             inner1_phys, body_phys,
    375             Photocathode_opsurf);
    376     new G4LogicalBorderSurface(GetName()+"_photocathode_logsurf2",
    377             body_phys, inner1_phys,
    378             Photocathode_opsurf);
    379     
    380     // inner2 / body
    381     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf1",
    382             inner2_phys, body_phys,
    383             m_absorb_opsurf);
    384     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf2",
    385             body_phys, inner2_phys,
    386             m_absorb_opsurf);
    387     
    388     // container / body
    389     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf3",
    390             cntr_phys, body_phys,
    391             m_absorb_opsurf);
    392     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf4",
    393             body_phys, cntr_phys,
    394             m_absorb_opsurf);
    395     
    396     // inner1 / inner2
    397     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf5",
    398             inner1_phys, inner2_phys,
    399             m_absorb_opsurf);
    400     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf6",
    401             inner2_phys, inner1_phys,
    402             m_absorb_opsurf);
    403     
    404     // inner2 / container
    405     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf7",
    406             cntr_phys, inner2_phys,
    407             m_absorb_opsurf);
    408     new G4LogicalBorderSurface(GetName()+"_absorb_logsurf8",
    409             inner2_phys, cntr_phys,
    410             m_absorb_opsurf);
    411 
    412 }
    413 



