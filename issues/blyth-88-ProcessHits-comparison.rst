blyth-88-ProcessHits-comparison
===================================

* from :doc:`blyth-88-revive-input-photons`


WIP : investigate hitCollection counts difference
------------------------------------------------------

::

    N=0 junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 29208 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent m_opticksMode 2 gpu_simulation  NO  hitCollection 189 hitCollection_muon 0 hitCollection_opticks 0


* Many input photons will be arriving at very close to the same time ? But thats true for both N=0 and N=1 ?
* HMM: is there hit merging happening here ? 
* Does hit merging work with opticksMode:2 ? 

* DONE : incorporate those hit counts into opticks logging 
* DONE : incorporate ProcessHits info into opticks SEvt

::

    optepsilon:ntds blyth$ jgr getMergerOpticks
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        PMTHitMerger*    getMergerOpticks() const ;  
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:1. sets m_pmthitmerger_opticks using  junoSD_PMT_v2::getMergerOpticks with result depending on m_opticksMode 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        m_pmthitmerger_opticks = m_jpmt->getMergerOpticks(); 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:junoSD_PMT_v2::getMergerOpticks
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:PMTHitMerger* junoSD_PMT_v2::getMergerOpticks() const 
    epsilon:junosw blyth$ 


DONE : basic instrumentation of junoSD_PMT_v2
------------------------------------------------

N=0::

    junoSD_PMT_v2::EndOfEvent@1131:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1139: junoSD_PMT_v2_Debug::desc
     ProcessHits_count     1486
     ProcessHits_true       296    //  296/1486  ~0.2
     ProcessHits_false     1190
     SaveNormHit_count      296
     SaveMuonHit_count        0

N=1::

    junoSD_PMT_v2::EndOfEvent@1131:  m_opticksMode 2 gpu_simulation  NO  hitCollection 2 hitCollection_muon 0 hitCollection_opticks 0
    junoSD_PMT_v2::EndOfEvent@1139: junoSD_PMT_v2_Debug::desc
     ProcessHits_count      523
     ProcessHits_true         2     // 2/523  ~0.004 
     ProcessHits_false      521
     SaveNormHit_count        2
     SaveMuonHit_count        0


DONE : more detailed instrumentation and make pmt_log sensitive
------------------------------------------------------------------

Q: Why is ProcessHits_count 1486 for N=0 but only 523 for N=1 ? 
A: Mostly it seems due to pmt_log not being sensitive. 
   
Q: Why is ProcessHits_true/ProcessHits_count fraction much lower for N=1 ? 
A: After pmt_log made sensitive they are much closer. 

N=0,1 edited together, first without HAMA pmt_log being sensitive in N=1::

    N=0 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 2 hitCollection_muon 0 hitCollection_opticks 0
    
    N=0                                 N=1 
     ProcessHits_count      1486         ProcessHits_count       523
     ProcessHits_true        296         ProcessHits_true          2
     ProcessHits_false      1190         ProcessHits_false       521
     SaveNormHit_count       296         SaveNormHit_count         2
     SaveMuonHit_count         0         SaveMuonHit_count         0
               EPH_UNSET       0                   EPH_UNSET       0
                EPH_NDIS       0                    EPH_NDIS       0
                EPH_NOPT       0                    EPH_NOPT       0
               EPH_NEDEP    1153                   EPH_NEDEP     514
              EPH_NBOUND       0                  EPH_NBOUND       0
               EPH_NPROC       0                   EPH_NPROC       0
             EPH_NDETECT       0                 EPH_NDETECT       0
             EPH_NDECULL      37                 EPH_NDECULL       7
              EPH_YMERGE       0                  EPH_YMERGE       0
               EPH_YSAVE     296                   EPH_YSAVE       2

N=0,1 edited together, now with HAMA pmt_log sensitive::

    N=0 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 296 hitCollection_muon 0 hitCollection_opticks 0
    N=1 junoSD_PMT_v2::EndOfEvent@1186:  m_opticksMode 2 gpu_simulation  NO  hitCollection 266 hitCollection_muon 0 hitCollection_opticks 0

    N=0                                 N=1
     ProcessHits_count      1486         ProcessHits_count      1815
     ProcessHits_true        296         ProcessHits_true        266
     ProcessHits_false      1190         ProcessHits_false      1549
     SaveNormHit_count       296         SaveNormHit_count       266
     SaveMuonHit_count         0         SaveMuonHit_count         0
               EPH_UNSET       0    #0             EPH_UNSET       0
                EPH_NDIS       0    #1              EPH_NDIS       0
                EPH_NOPT       0    #2              EPH_NOPT       0
               EPH_NEDEP    1153    #3             EPH_NEDEP    1520   
              EPH_NBOUND       0    #4            EPH_NBOUND       4
               EPH_NPROC       0    #5             EPH_NPROC       0
             EPH_NDETECT       0    #6           EPH_NDETECT       0
             EPH_NDECULL      37    #7           EPH_NDECULL      25
              EPH_YMERGE       0    #8            EPH_YMERGE       0
               EPH_YSAVE     296    #9             EPH_YSAVE     266


DONE : include eph enum into current_aux, getting ProcessHits info into SEvt
------------------------------------------------------------------------------

Q: How to associate ProcessHits info like eph back into the opticks SEvt ? 
A: Write eph into C4Pho G4Track info label, and from U4Recorder::UserSteppingAction  
   copy that into current_aux for each step point ?    

So can viz the photons with the different EPH enum values::

    In [41]: a_uc4 = a.f.aux[:,:,2,2].copy().view(np.uint8).reshape(-1,32,4)
    In [42]: b_uc4 = b.f.aux[:,:,2,2].copy().view(np.uint8).reshape(-1,32,4)

    In [43]: np.c_[np.unique( a_uc4[:,:,1], return_counts=True )]
    Out[43]: 
    array([[    0, 29826],
           [    3,  1841],  # EPH_NEDEP
           [    7,    37],  # EPH_NDECULL
           [    9,   296]]) # EPH_YSAVE

    In [44]: np.c_[np.unique( b_uc4[:,:,1], return_counts=True )]
    Out[44]: 
    array([[    0, 29651],
           [    3,  2054],  # EPH_NEDEP
           [    4,     4],  # EPH_NBOUND 
           [    7,    25],  # EPH_NDECULL
           [    9,   266]]) # EPH_YSAVE

Include uc4, eph into sysrap/sevt.py:SEvt::

    In [8]: a.f.record.shape
    Out[8]: (1000, 32, 4, 4)

    In [9]: a.eph.shape
    Out[9]: (1000, 32)

    In [10]: a.uc4.shape
    Out[10]: (1000, 32, 4)

    In [4]: np.c_[np.unique( a.eph, return_counts=True )]
    Out[4]: 
    array([[    0, 29826],
           [    3,  1841],
           [    7,    37],
           [    9,   296]])

    In [5]: np.c_[np.unique( b.eph, return_counts=True )]
    Out[5]: 
    array([[    0, 29651],
           [    3,  2054],
           [    4,     4],
           [    7,    25],
           [    9,   266]])



WIP : make connection between EPH ProcessHits enum and opticks flags especially SD, SA 
--------------------------------------------------------------------------------------------

::

    In [14]: np.unique( a.qq[np.where(a.eph == 9)], return_counts=True )
    Out[14]: (array([7], dtype=int8), array([296]))

    In [15]: fla[7]
    Out[15]: 'SD'

    ## all EPH_YSAVE:9 correspond to SD

    In [26]: a.q[np.where(a.eph == 9)[0]]
    Out[26]: 
    array([[b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
                                                                         '],

    In [23]: np.c_[np.unique( a.qq[np.where(a.eph == 7)], return_counts=True )]
    Out[23]: array([[ 7, 37]])

    ## all EPH_NDECULL:7 correspond to SD



    In [25]: a.q[np.where(a.eph == 7)[0]]
    Out[25]: 
    array([[b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SD                                                             '],
           [b'TO BT BR BT BT SD                                                                               '],
           [b'TO BT BT BT BT BR BT BT BT BT BT SD                                                             '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD                      '],
           [b'TO BT BT BT BR BT BT BT BT BT BT BT BT SD                                                       '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD          



But SD have a variety of EPH::

    In [18]: np.c_[np.unique(a.eph[np.where( a.qq == 7 )],return_counts=True)]
    Out[18]: 
    array([[  7,  37],   # EPH_DECULL
           [  9, 296]])  # EPH_YSAVE

    In [19]: np.c_[np.unique(b.eph[np.where( b.qq == 7 )],return_counts=True)]
    Out[19]: 
    array([[  0,   1],   # UNSET
           [  3,   9],   # EPH_NEDEP           
           [  7,  25],   # EPH_NDECULL 
           [  9, 266]])  # EPH_YSAVE


    In [82]: w =  np.where(np.logical_and( b.eph == 0, b.qq == 7 )) ; w
    Out[82]: (array([963]), array([20]))

    In [83]: b.q[w[0]]
    Out[83]: array([[b'TO SC BT BT SC SC SC BT BT BT BT BT BR BT BT BT BT BT BT BT SD                                  ']], dtype='|S96')


Those 9 which are SD but EPH_NEDEP all have complex histories, probably some distant PMT::

    In [34]: w =  np.where(np.logical_and( b.eph == 3, b.qq == 7 )) ; w
    Out[34]: 
    (array([102, 119, 188, 190, 253, 714, 763, 797, 840]),
     array([28, 16, 25, 22, 28, 19, 21, 19, 23]))

    In [35]: b.q[w[0]]
    Out[35]: 
    array([[b'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD          '],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SD                                              '],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC SC BT BT BT BT BT BT BT SD                   '],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT BT BT SD                            '],
           [b'TO BT BT BT BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT BT SC SC BT BT BT BT BT BT SD          '],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                     '],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT DR SC BT BT BT BT SD                               '],
           [b'TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                     '],
           [b'TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC BT BT BT BT BT BT SD                         ']], dtype='|S96')


HMM: those 9 are all over the place. So maybe due to NNVT lack of sensitive::

    In [81]: b.f.record[w][:,0,:3]
    Out[81]: 
    array([[ -7339.035,   9483.076,  15067.431],
           [-13954.789,  11011.507,   7489.889],
           [  9970.17 , -14538.838,   7789.211],
           [ 12772.203, -10079.686, -10506.772],
           [ -4750.779,  -4312.689,  18158.158],
           [ -4379.288,  -2136.1  ,  18677.955],
           [  9436.662,  -5176.761,  16008.536],
           [ -4366.585,    -20.829,  18876.564],
           [ 16944.299,   1640.556,   9312.878]], dtype=float32)


Mostly nowhere near the targetted PMT::

    In [70]: b.f.record[0,:b.n[0],0]
    Out[70]: 
    array([[-11574.436,   9133.022,  11067.756,      0.1  ],
           [-12127.061,   9569.082,  11611.27 ,      4.2  ],
           [-12155.882,   9591.824,  11639.615,      4.414],
           [-12163.636,   9597.942,  11650.679,      4.49 ],
           [-12175.027,   9606.931,  11647.537,      4.567],
           [-12181.73 ,   9612.22 ,  11647.288,      4.606],
           [-12225.451,   9646.719,  11645.658,      4.863],
           [-12225.454,   9646.721,  11645.658,      4.863]], dtype=float32)


Suspicious, all over the place in X. Close to origin in YZ::

    In [3]: w_gpos  ## MUST BE NUMPY BUG MIXING POS/DIR/POL ? 
    Out[3]: 
    array([[ -7339.035,     -0.286,     -0.839,      1.   ],
           [-13954.789,     -0.453,     -0.719,      1.   ],
           [  9970.17 ,      0.317,     -0.444,      1.   ],
           [ 12772.203,      0.558,     -0.182,      1.   ],
           [ -4750.779,     -0.144,      0.225,      1.   ],
           [ -4379.288,      0.14 ,     -0.909,      1.   ],
           [  9436.662,      0.895,     -0.177,      1.   ],
           [ -4366.585,     -0.744,     -0.035,      1.   ],
           [ 16944.299,      0.218,     -0.188,      1.   ]])


::

    In [5]: np.c_[a.f.junoSD_PMT_v2_meta.lines, b.f.junoSD_PMT_v2_meta.lines]
    Out[5]: 
    array([['ProcessHits_count:15311', 'ProcessHits_count:18131'],
           ['ProcessHits_true:2938', 'ProcessHits_true:2929'],
           ['ProcessHits_false:12373', 'ProcessHits_false:15202'],
           ['SaveNormHit_count:2938', 'SaveNormHit_count:2929'],
           ['SaveMuonHit_count:0', 'SaveMuonHit_count:0'],
           ['UNSET:0', 'UNSET:0'],
           ['NDIS:0', 'NDIS:0'],
           ['NOPT:0', 'NOPT:0'],
           ['NEDEP:12080', 'NEDEP:14858'],     ## lots of edep 0. as have to make multiple vols sensitive
           ['NBOUND:0', 'NBOUND:42'],          ## explained : bulk absorb in Pyrex 
           ['NPROC:0', 'NPROC:0'],
           ['NDETECT:0', 'NDETECT:0'],
           ['NDECULL:293', 'NDECULL:302'],     ## similar values : but why so small ?
           ['YMERGE:0', 'YMERGE:0'],           ## why no merging ?
           ['YSAVE:2938', 'YSAVE:2929'],
           ['opticksMode:2', 'opticksMode:2']], dtype='<U23')



::

    In [10]: np.c_[np.unique(a.eph,return_counts=True)]
    Out[10]: 
    array([[     0, 297456],
           [     3,  19327],   # EPH_NEDEP
           [     7,    288],   # EPH_NDECULL
           [     9,   2929]])  # EPH_YSAVE  : why not 2938 ?

    In [11]: np.c_[np.unique(b.eph,return_counts=True)]
    Out[11]: 
    array([[     0, 296824],
           [     3,  19909],   # WHY SO MANY ProcessHits calls with zero edep ? Because have to make multiple vol sensitive
           [     4,     41],   # explained by AB:BULK_ABSORB in Pyrex happening for N=1 but not N=0
           [     7,    302],   # slightly more EPH_NDECULL : not significant ? TODO: stats*10
           [     9,   2924]])  # EPH_YSAVE : why not 2929 ? 
 

    In [4]: np.c_[np.unique(b.qq[np.where(b.eph == 9)], return_counts=True)]
    Out[4]: array([[   7, 2924]])   ## EPH_YSAVE all SD

    In [5]: np.c_[np.unique(b.qq[np.where(b.eph == 7)], return_counts=True)]
    Out[5]: array([[  7, 302]])     ## EPH_NDECULL all SD 

    In [6]: np.c_[np.unique(b.qq[np.where(b.eph == 4)], return_counts=True)]
    Out[6]: array([[ 4, 41]])       


EPH_NBOUND all AB : makes sense, but why ProcessHits called ? And why none with N=0 ?
that is from bulk absorption in the Pyrex, as shown by::

::

   CHECK=EPH_NBOUND_PYREX_AB ./ntds.sh ana
    
Doesnt happen with N=0 because simpler N=1 geometry means pmt_log needs to be sensitive. 

::

    In [7]: fln[7]
    Out[7]: 'SURFACE_DETECT'

    In [8]: fln[4]
    Out[8]: 'BULK_ABSORB'



DONE : Expect total SD should be NDECULL+YSAVE : but it is not quite so ? It is when use np.max(eph, axis=1)
--------------------------------------------------------------------------------------------------------------

Probably because ProcessHits will run more than once for some photons 
but there is always only 0 or 1 SD for a photon. 

Check this with totaling in label->uc4.z::

    #ifdef WITH_G4CXOPTICKS
    G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
    {
        G4bool processHits = ProcessHits_(step, nullptr) ; 
        dbg.add( eph, processHits ); 

        C4Pho* label = C4TrackInfo<C4Pho>::GetRef(step->GetTrack());
        assert(label); 

        label->uc4.y = eph ; 
        label->uc4.z += 1  ; 
        //label->set_eph(eph) ;  // switch to this when bump Custom4 to 0.0.9

        // ProcessHits may run 0,1,>1 times per photon, 
        // so its non-trivial to match eph counts with per photon SD flag counts.
        //
        // When ProcessHits runs more than once for a photon it looks like the 
        // above will stomp, but that is not the full story as the label values 
        // will get copied into the aux for the step by U4Recorder before stomping happens. 
        //

        //LOG_IF(info, (label->id % 100) == 0) << " label " << ( label ? label->desc() : "-" ) << " eph " << EPH::Name(eph) ; 
        return processHits ; 
    }
    #endif


::

    In [3]: np.count_nonzero(a.eph)    ## average 2.24 ProcessHits calls per photon
    Out[3]: 22544

    In [4]: np.count_nonzero(b.eph)    ## average 2.31 ProcessHists calls per photon
    Out[4]: 23176

    In [6]: a.f.record.shape
    Out[6]: (10000, 32, 4, 4)

    In [7]: a.eph.shape
    Out[7]: (10000, 32)

    In [10]: np.max(a.eph, axis=1).shape
    Out[10]: (10000,)

    In [12]: a_ep = np.max(a.eph, axis=1)

    In [13]: np.count_nonzero(a_ep)   ## ProcessHits being called for almost all 
    Out[13]: 9590


    In [21]: a.q[a_ep==0]  ## photons without ProcessHits calls cannot enter PMT ? TODO: plot these
    Out[21]: 
    array([[b'TO BT BT BT BR BT BT BT DR BT DR BT SA     '],
           [b'TO BT BT BT BR BT BT BT DR BT DR BT BT SA  '],
           [b'TO BT BT BT BR BT BT BT SA                 '],
           [b'TO BT BT BT BR BT BT BT SA                 '],
           [b'TO BT BR BT BT SA                          '],
           [b'TO BT BT BT BR BT BT BT BT SA              '],
           [b'TO BT BT BR BT BT BT SA                    '],
           [b'TO BT BT BT BR BT BT BT BT SA              '],
           [b'TO BT BR BT BT SA                          '],
           [b'TO BT BT BT BR BT BT BT BT SA              '],
           [b'TO AB                                      '],
           [b'TO BT BT BR BT BT BT SA                    '],
           [b'TO BT BT BT BR BT BT BT BT SA              '],
           [b'TO BT BR BT BT SA                          '],




    In [14]: b_ep = np.max(b.eph, axis=1)

    In [15]: np.count_nonzero(b_ep)
    Out[15]: 9686


    In [16]: np.c_[np.unique(a_ep, return_counts=True)]
    Out[16]: 
    array([[   0,  410],
           [   3, 6373],
           [   7,  288],
           [   9, 2929]])

    In [19]: 2929+288
    Out[19]: 3217

    In [17]: np.c_[np.unique(b_ep, return_counts=True)]
    Out[17]: 
    array([[   0,  314],
           [   3, 6419],
           [   4,   41],
           [   7,  302],
           [   9, 2924]])  

    In [18]: 2924 + 302
    Out[18]: 3226


::

    In [10]: np.where(a.qq == 7)[0].shape
    Out[10]: (3217,)

    In [11]: 2938 + 293
    Out[11]: 3231       ## 14 fewer SD when look at straight eph 

    ## matches when look at np.max(a.eph, axis=1)


    In [3]: np.where(b.qq == 7)[0].shape 
    Out[3]: (3226,)

    ## matches when look at np.max(b.eph, axis=1)


    In [9]: 2929+302
    Out[9]: 3231        ## 5 fewer SD   (3231 matches above by chance ?)




DONE : Photon level a.ep counts match SD counts
-------------------------------------------------

::

   jxn
   ./ntds.sh ana

    np.c_[np.unique(a.ep,return_counts=True)]    # photon level ProcessHits EPH enum 

    array(
      [[    0,  4150],
       [    3, 63634],
       [    4,     1],
       [    7,  3104],
       [    9, 29111]])

    np.c_[np.unique(b.ep,return_counts=True)]    # photon level ProcessHits EPH enum 

    array(
      [[    0,  3456],
       [    3, 63585],
       [    4,   414],
       [    7,  3122],
       [    9, 29423]])

    100000 : np.unique(a.ep,return_counts=True)[1].sum()  # a.ep count total  
    100000 : np.unique(b.ep,return_counts=True)[1].sum()  # b.ep count total  

     32215 : len(a.ep[a.ep >= 7])                         # 7:EPH_NDECULL, 8:EPH_YMERGE, 9:EPH_YSAVE 
     32215 : len(np.where(a.qq == pcf.SD)[0])             # photons with SD in history  

     32545 : len(b.ep[b.ep >= 7])                         # 7:EPH_NDECULL, 8:EPH_YMERGE, 9:EPH_YSAVE 
     32545 : len(np.where(b.qq == pcf.SD)[0])             # photons with SD in history  




DONE : High stats (100k) chi2 onto Hama:0:1000 : MATCHING 
------------------------------------------------------------

::

    QCF qcf 
    c2sum :   108.5824 c2n :   110.0000 c2per:     0.9871  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  108.58/110:0.987 (30)

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SA                                        ' ' 0' ' 37047  36670' ' 1.9280' '     0      4']
     [' 1' 'TO BT BT BT BT SD                                        ' ' 1' ' 29898  30192' ' 1.4384' '     6      1']
     [' 2' 'TO BT BT BT BT BT SA                                     ' ' 2' ' 12157  12109' ' 0.0949' '  8819   9048']
     [' 3' 'TO BT BT BT BT BT SR SA                                  ' ' 3' '  3641   3730' ' 1.0746' ' 10883  10964']
     [' 4' 'TO BT BT BT BT BT SR SR SA                               ' ' 4' '  2002   1952' ' 0.6323' ' 10886  10892']
     [' 5' 'TO AB                                                    ' ' 5' '  1970   1947' ' 0.1351' '    46    145']
     [' 6' 'TO BT BT AB                                              ' ' 6' '   836    860' ' 0.3396' '   120    150']
     [' 7' 'TO BT BT BT BT BT SR SR SR SA                            ' ' 7' '   573    581' ' 0.0555' ' 14738  14772']
     [' 8' 'TO BT BT BT BT BR BT BT BT BT BT SA                      ' ' 8' '   454    415' ' 1.7503' '  1055   1033']
     [' 9' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                   ' ' 9' '   380    402' ' 0.6189' ' 12054  10783']
     ['10' 'TO BT BT BT BT AB                                        ' '10' '   312    352' ' 2.4096' '   133     28']
     ['11' 'TO BT BT BT BT BR BT BT BT BT BT SD                      ' '11' '   350    327' ' 0.7814' '  5250   5259']
     ['12' 'TO BT BT BT BT BT SR BR SA                               ' '12' '   320    302' ' 0.5209' ' 33580  33624']
     ['13' 'TO BT BT BR BT BT BT SA                                  ' '13' '   307    267' ' 2.7875' '    10      7']
     ['14' 'TO BT BT BT BT BR BT BT BT BT AB                         ' '14' '   306    293' ' 0.2821' '   510   8996']
     ['15' 'TO BT BT BT BR BT BT BT BT SA                            ' '15' '   280    281' ' 0.0018' '   209    207']
     ['16' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SD             ' '16' '   256    251' ' 0.0493' '  9345   9353']
     ['17' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA             ' '17' '   233    250' ' 0.5983' '  9360   9380']
     ['18' 'TO BT BT BT BT BT SR SR SR BR SA                         ' '18' '   249    233' ' 0.5311' ' 14948  14975']
     ['19' 'TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA             ' '19' '   225    226' ' 0.0022' ' 26574  26559']
     ['20' 'TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA       ' '20' '   206    204' ' 0.0098' ' 15409  15448']
     ['21' 'TO BT BT BT BT BT BR SR SA                               ' '21' '   166    183' ' 0.8281' '  9262   9760']
     ['22' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SD ' '22' '   174    174' ' 0.0000' ' 17444  11855']
     ['23' 'TO BT BT BT BT BT SR SR SR BR BR SR SA                   ' '23' '   159    146' ' 0.5541' ' 15472  15493']
     ['24' 'TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT SA ' '24' '   159    145' ' 0.6447' '  7330   7320']]



TODO : High stats (100k) chi2 onto NNVT:0:1000 : ?
------------------------------------------------------------






DONE : Maybe need pmt_log volume as sensitive with N=1, not just inner_log as now ?
--------------------------------------------------------------------------------------

jcv HamamatsuR12860PMTManager::

     713 void
     714 HamamatsuR12860PMTManager::helper_make_logical_volume()
     715 {
     716     if( m_UsePMTNaturalGeometry == false )
     717     {
     ...
     743     }
     744     else
     745     {
     746         pmt_log = new G4LogicalVolume
     747             ( pmt_solid,
     748               GlassMat,
     749               GetName()+"_log" );
     750 
     751         inner_log= new G4LogicalVolume
     752             ( inner_solid,
     753               PMT_Vacuum,
     754               GetName()+"_inner_log" );
     755 
     756         inner_log->SetSensitiveDetector(m_detector);
     757         m_logical_pmt = pmt_log ;
     758     }
     759 
     760 }


Changed that to::

     744     else
     745     {
     746         pmt_log = new G4LogicalVolume
     747             ( pmt_solid,
     748               GlassMat,
     749               GetName()+"_log" );
     750         pmt_log->SetSensitiveDetector(m_detector);
     751         // G4SteppingManager::Stepping only calls Hit/ProcessHits 
     752         // when the prestep point volume is sensitive so for 
     753         // sensitive boundary need to set two volumes as sensitive 
     754    
     755         inner_log= new G4LogicalVolume
     756             ( inner_solid,
     757               PMT_Vacuum,
     758               GetName()+"_inner_log" );
     759    
     760         inner_log->SetSensitiveDetector(m_detector);
     761         m_logical_pmt = pmt_log ;
     762     }


DONE : Same fix for NNVT 
---------------------------


HMM: Does this mean all PMT innards must be Sensitive to avoid missed ProcessHits ?
---------------------------------------------------------------------------------------- 



DONE : Review ProcessHits : prestep point volume needs to be sensitive for Hit/ProcessHits to run
----------------------------------------------------------------------------------------------------

::

   79 class junoSD_PMT_v2 : public G4VSensitiveDetector, public IToolForSD_PMT


g4-cls G4VSensitiveDetector::

    113   public: // with description
    114       inline G4bool Hit(G4Step*aStep)
    115       { 
    116         G4TouchableHistory* ROhis = 0;
    117         if(!isActive()) return false;
    118         if(filter)
    119         { if(!(filter->Accept(aStep))) return false; }
    120         if(ROgeometry)
    121         { if(!(ROgeometry->CheckROVolume(aStep,ROhis))) return false; }
    122         return ProcessHits(aStep,ROhis);
    123       }

g4-cls G4SteppingManager::

    116 G4StepStatus G4SteppingManager::Stepping()
    ...
    221 // Update 'TrackLength' and remeber the Step length of the current Step
    222    fTrack->AddTrackLength(fStep->GetStepLength());
    223    fPreviousStepSize = fStep->GetStepLength();
    224    fStep->SetTrack(fTrack);
    225 #ifdef G4VERBOSE
    226                          // !!!!! Verbose
    227 
    228            if(verboseLevel>0) fVerbose->StepInfo();
    229 #endif
    230 // Send G4Step information to Hit/Dig if the volume is sensitive
    231    fCurrentVolume = fStep->GetPreStepPoint()->GetPhysicalVolume();
    232    StepControlFlag =  fStep->GetControlFlag();
    233    if( fCurrentVolume != 0 && StepControlFlag != AvoidHitInvocation) {
    234       fSensitive = fStep->GetPreStepPoint()->
    235                                    GetSensitiveDetector();
    236       if( fSensitive != 0 ) {
    237         fSensitive->Hit(fStep);
    238       }
    239    }
    240 
    241 // User intervention process.
    242    if( fUserSteppingAction != 0 ) {
    243       fUserSteppingAction->UserSteppingAction(fStep);
    244    }
    245    G4UserSteppingAction* regionalAction
    246     = fStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetRegion()
    247       ->GetRegionalSteppingAction();
    248    if( regionalAction ) regionalAction->UserSteppingAction(fStep);
    249 
    250 // Stepping process finish. Return the value of the StepStatus.
    251    return fStepStatus;
    252 
    253 }



TODO : add presentation plots and chi2 tables for these comparisons
----------------------------------------------------------------------

TODO : target NNVT and do comparisons 
----------------------------------------

* heavy 600M SEvt for 100k input photons, so complete Hama presentation plots before doing NNVT


TODO : simtrace running insitu : how to do that ?
-----------------------------------------------------

* moved simtrace_scan to U4Tree




