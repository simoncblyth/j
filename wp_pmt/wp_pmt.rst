wp_pmt
==========


ipc env_pdb : looks like seeing differnt geometry 
----------------------------------------------------



::


    In [1]: a
    Out[1]: SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/A000 

    In [2]: a.qtab
    Out[2]: 
    array([[b'95065', b'0', b'TO BT BT BT BT NA                                                                               '],
           [b'2253', b'16', b'TO BR SA                                                                                        '],
           [b'313', b'199', b'TO BT BT BT BT AB                                                                               '],
           [b'246', b'368', b'TO BT BT BR BT BT SA                                                                            '],
           [b'240', b'228', b'TO BT BR BT SA                                                                                  '],
           [b'216', b'265', b'TO BT BT BR BT BT DR SA                                                                         '],
           [b'208', b'933', b'TO BT BT BT BR BT BT BT SA                                                                      '],
           [b'153', b'23', b'TO BT BR BT DR SA                                                                               '],
           [b'152', b'690', b'TO BT BT BT BR BT BT BT DR SA                                                                   '],
           [b'135', b'4', b'TO BT BT BT BR BT BT BR BT BT BT NA                                                             ']], dtype='|S96')

    In [3]: b.qtab
    Out[3]: 
    array([[b'64035', b'0', b'TO AB                                                                                           '],
           [b'35965', b'5', b'TO SA                                                                                           ']], dtype='|S96')

    In [67]: 64035 + 35965
    Out[67]: 100000



A side NA : NAN_ABORT
-----------------------

::

    1755 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1756     if( ctx.pidx == base->pidx )
    1757     {
    1758     float3 cross_mom_nrm = cross(p.mom, *normal) ;
    1759     printf("//qsim::propagate_at_surface_CustomART pidx %7d : mom = np.array([%10.8f,%10.8f,%10.8f]) ; lmom = %10.8f \n",
    1760        ctx.pidx, p.mom.x, p.mom.y, p.mom.z, length(p.mom) );
    1761     printf("//qsim::propagate_at_surface_CustomART pidx %7d : pol = np.array([%10.8f,%10.8f,%10.8f]) ; lpol = %10.8f \n",
    1762        ctx.pidx, p.pol.x, p.pol.y, p.pol.z, length(p.pol) );
    1763     printf("//qsim::propagate_at_surface_CustomART pidx %7d : nrm = np.array([%10.8f,%10.8f,%10.8f]) ; lnrm = %10.8f \n",
    1764        ctx.pidx, normal->x, normal->y, normal->z, length(*normal) );
    1765     printf("//qsim::propagate_at_surface_CustomART pidx %7d : cross_mom_nrm = np.array([%10.8f,%10.8f,%10.8f]) ; lcross_mom_nrm = %10.8f  \n",
    1766            ctx.pidx, cross_mom_nrm.x, cross_mom_nrm.y, cross_mom_nrm.z, length(cross_mom_nrm)  );
    1767     printf("//qsim::propagate_at_surface_CustomART pidx %7d : dot_pol_cross_mom_nrm = %10.8f \n", ctx.pidx, dot_pol_cross_mom_nrm );
    1768     printf("//qsim::propagate_at_surface_CustomART pidx %7d : minus_cos_theta = %10.8f \n", ctx.pidx, minus_cos_theta );
    1769     printf("//qsim::propagate_at_surface_CustomART pidx %7d : lposcost = %10.8f (expect 0->1)\n", ctx.pidx, lposcost );
    1770     }
    1771 #endif
    1772 
    1773     if(lpmtid < 0 || lpmtid >= 17612 )  // find Custom4 hits onto WP PMTs are causing this warning, so comment it, see ~/j/issues/jok-tds-mu-running-NOT-A-SENSOR-warnings.rst
    1774     {
    1775         flag = NAN_ABORT ;
    1776 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1777         printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d : ERROR NOT-A-SENSOR : NAN_ABORT \n", ctx.pidx, lpmtid );
    1778 #endif
    1779         return BREAK ;
    1780     }
    1781 
    1782 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1783     if( ctx.pidx == base->pidx )
    1784     printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d wl %7.3f mct %7.3f dpcmn %7.3f pmt %p pre-ATQC \n",
    1785            ctx.pidx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, pmt );
    1786 #endif
    1787 
    1788     float ATQC[4] = {} ;
    1789 
    1790     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    1791 
    1792 




qpmt::get_lpmtid_ATQC : What is needed to add WP_PMT to this ?
------------------------------------------------------------------

::

    512 template<typename F>
    513 inline QPMT_METHOD void qpmt<F>::get_lpmtid_ATQC(
    514     F* ATQC,
    515     int lpmtid,
    516     F wavelength_nm,
    517     F minus_cos_theta,
    518     F dot_pol_cross_mom_nrm,
    519     F lposcost ) const
    520 {
    521     const F energy_eV = hc_eVnm/wavelength_nm ;
    522 
    523     F spec[16] ;
    524 
    525     get_lpmtid_stackspec_ce_acosf( spec, lpmtid, energy_eV, lposcost );
    526   //get_lpmtid_stackspec_ce(       spec, lpmtid, energy_eV, lposcost );
    527 
    528 


    215 template<typename F>
    216 inline QPMT_METHOD void qpmt<F>::get_lpmtid_stackspec_ce_acosf( F* spec, int lpmtid, F energy_eV, F lposcost ) const
    217 {
    218     const int& lpmtcat = i_lcqs[lpmtid*2+0] ;
    219 
    220     const F& qe_scale = lcqs[lpmtid*2+1] ;
    221     const F qe_shape = qeshape_prop->interpolate( lpmtcat, energy_eV ) ;
    222     const F qe = qe_scale*qe_shape ;
    223 
    224     const F theta_radians = acosf(lposcost);
    225     const F ce = cetheta_prop->interpolate( lpmtcat, theta_radians );
    226 
    227     spec[0*4+3] = lpmtcat ;       //  3
    228     spec[1*4+3] = ce ;            //  7
    229     spec[2*4+3] = qe_shape ;      // 11
    230     spec[3*4+3] = qe ;            // 15
    231 
    232     get_lpmtcat_stackspec( spec, lpmtcat, energy_eV );
    233 


lcqs
~~~~

::

    120 template<typename T>
    121 inline QPMT<T>::QPMT(const NPFold* jpmt )
    122     :
    123     ExecutableName(sproc::ExecutableName()),
    124     src_rindex(   jpmt->get("rindex")),
    125     src_thickness(jpmt->get("thickness")),
    126     src_qeshape(  jpmt->get("qeshape")),
    127     src_cetheta(  jpmt->get("cetheta")),
    128     src_cecosth(  jpmt->get("cecosth")),
    129     src_lcqs(     jpmt->get_optional("lcqs")),
    130     rindex3(  NP::MakeCopy3D(src_rindex)),   // make copy and change shape to 3D
    131     rindex(   NP::MakeWithType<T>(rindex3)), // adopt template type, potentially narrowing
    132     rindex_prop(new QProp<T>(rindex)),
    133     qeshape(   NP::MakeWithType<T>(src_qeshape)), // adopt template type, potentially narrowing
    134     qeshape_prop(new QProp<T>(qeshape)),
    135     cetheta(   NP::MakeWithType<T>(src_cetheta)), // adopt template type, potentially narrowing
    136     cetheta_prop(new QProp<T>(cetheta)),
    137     cecosth(   NP::MakeWithType<T>(src_cecosth)), // adopt template type, potentially narrowing
    138     cecosth_prop(new QProp<T>(cecosth)),
    139     thickness(NP::MakeWithType<T>(src_thickness)),
    140     lcqs(src_lcqs ? NP::MakeWithType<T>(src_lcqs) : nullptr),
    141     i_lcqs( lcqs ? (int*)lcqs->cvalues<T>() : nullptr ),    // CPU side lookup lpmtid->lpmtcat 0/1/2
    142     pmt(new qpmt<T>()),                    // host-side qpmt.h instance
    143     d_pmt(nullptr)                         // device-side pointer set at upload in init
    144 {
    145     init();
    146 }




/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt/PMTSimParamData
---------------------------------------------------------------------------------------------------------------

::

    A[blyth@localhost PMTSimParamData]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: Use `object?` to see the help on `object`, `object??` to view its source
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.pmtID                                            :           (45612, 1) : 7 days, 23:13:52.230958 
      : f.qeScale                                          :           (45612, 1) : 7 days, 23:13:52.230958 
      : f.lpmtCat                                          :           (17612, 1) : 7 days, 23:13:52.229958 
      : f.lpmtCat_meta                                     :                    4 : 7 days, 23:13:52.229958 
      : f.pmtCat                                           :           (45612, 2) : 7 days, 23:13:52.229958 
      : f.pmtCatName                                       :                 (5,) : 7 days, 23:13:52.229958 
      : f.pmtCatName_names                                 :                 (5,) : 7 days, 23:13:52.229958 
      : f.pmtCatVec                                        :           (45612, 1) : 7 days, 23:13:52.229958 
      : f.spmtData                                         :          (25600, 10) : 7 days, 23:13:52.229958 
      : f.spmtData_meta                                    :                    4 : 7 days, 23:13:52.228958 
      : f.lpmtData                                         :           (20012, 9) : 7 days, 23:13:52.228958 
      : f.pmtTotal                                         :                 (4,) : 7 days, 23:13:52.227958 
      : f.pmtTotal_names                                   :                 (4,) : 7 days, 23:13:52.227958 
      : f.NPFold_index                                     :                (14,) : 7 days, 23:13:52.227958 
      : f.MPT                                              :                 None : 10 days, 21:11:05.562260 
      : f.CONST                                            :                 None : 10 days, 21:11:05.562260 
      : f.QEshape                                          :                 None : 10 days, 21:11:05.562260 
      : f.CEtheta                                          :                 None : 10 days, 21:11:05.562260 
      : f.NPFold_names                                     :                 (0,) : 7 days, 23:13:52.226958 
      : f.CECOStheta                                       :                 None : 8 days, 18:33:19.332685 

     min_stamp : 2025-06-07 18:21:46.340147 
     max_stamp : 2025-06-10 16:18:59.675449 
     dif_stamp : 2 days, 21:57:13.335302 
     age_stamp : 7 days, 23:13:52.226958 


::

    In [3]: pc = f.PMTParamData.pmtCat


    In [31]: pc[:,1]
    Out[31]: array([1, 3, 1, 3, 1, ..., 0, 3, 3, 3, 0], shape=(45612,), dtype=int32)

    In [26]: pc0 = f.PMTSimParamData.lpmtCat[:,0]

    In [32]: pc0
    Out[32]: array([1, 3, 1, 3, 1, ..., 1, 3, 1, 1, 1], shape=(17612,), dtype=int32)

    In [33]: np.all( pc0 == pc[:17612,1] )
    Out[33]: np.True_




    In [8]: pc[:17612]
    Out[8]: 
    array([[    0,     1],
           [    1,     3],
           [    2,     1],
           [    3,     3],
           [    4,     1],
           ...,
           [17607,     1],
           [17608,     3],
           [17609,     1],
           [17610,     1],
           [17611,     1]], shape=(17612, 2), dtype=int32)

    In [9]: np.unique( pc[:17612,1], return_counts=True )
    Out[9]: (array([0, 1, 3], dtype=int32), array([2738, 4955, 9919]))

    In [10]: np.c_[np.unique( pc[:17612,1], return_counts=True )]
    Out[10]: 
    array([[   0, 2738],
           [   1, 4955],
           [   3, 9919]])

    In [11]: np.c_[np.unique( pc[:17612,1], return_counts=True )][:,1].sum()
    Out[11]: np.int64(17612)


    In [13]: np.c_[np.unique( pc[17612:,1], return_counts=True )]
    Out[13]: 
    array([[    0,  1836],
           [    2, 25600],
           [    3,   564]])

    In [14]: 1836+564
    Out[14]: 2400


    In [16]: pc[17612:17612+25600]
    Out[16]: 
    array([[20000,     2],
           [20001,     2],
           [20002,     2],
           [20003,     2],
           [20004,     2],
           ...,
           [45595,     2],
           [45596,     2],
           [45597,     2],
           [45598,     2],
           [45599,     2]], shape=(25600, 2), dtype=int32)

    In [17]: np.c_[np.unique( pc[17612:17612+25600,1], return_counts=True )]
    Out[17]: array([[    2, 25600]])


    In [19]: np.c_[np.unique( pc[17612+25600:,1], return_counts=True )]
    Out[19]: 
    array([[   0, 1836],
           [   3,  564]])


    In [20]: pc[17612+25600:]
    Out[20]: 
    array([[50000,     3],
           [50001,     0],
           [50002,     0],
           [50003,     3],
           [50004,     0],
           ...,
           [52395,     0],
           [52396,     3],
           [52397,     3],
           [52398,     3],
           [52399,     0]], shape=(2400, 2), dtype=int32)



lpmtid to contiguous index ordered such that have LPMT, WP
--------------------------------------------------------------

::

     [0:17612]                      LPMT
     [17612:17612+25600]            SPMT
     [17612+25600:17612+25600+2400] WP      17612+25600+2400 = 45612

Unfortunately SPMT in the middle::

     start with premise that lpmtid >=0 && lpmtid < 45612 



     int lpmtidx = lpmtid < 17612 ? 
                                        lpmtid 
                                  : 
                                       ( lpmtid > 17612+25600 ? lpmtid - 25600 : -1 ) 
                                  ;  






Added SPMT_Total to SPMT.h and revived SPMT_test.sh 
--------------------------------------------------------








cxs_min.sh # wp_pmt with qsim.h NAN_ABORT uncommented
--------------------------------------------------------

cxs_min.sh:

    435    elif [ "${TEST:12}" == "_wp_pmt" ]; then
    436 
    437       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    438       opticks_input_photon=RainXZ_Z230_100k_f8.npy
    439       opticks_input_photon_frame=PMT_20inch_veto:0:1000
    440 


Looks like PMT_20inch_veto:0:1000 is lpmtid 51000::

    //qsim::propagate_at_surface_CustomART pidx   99723 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99726 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99731 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99739 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99774 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96886 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   98628 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   98639 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   98650 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   97954 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   97937 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   91366 lpmtid 51225 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99025 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99217 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99323 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99133 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99064 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   91390 lpmtid 51225 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96958 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99087 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99260 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   92792 lpmtid 51225 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99174 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99230 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99304 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99322 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99281 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99285 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   93946 lpmtid 50999 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   96796 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   99089 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 
    //qsim::propagate_at_surface_CustomART pidx   98774 lpmtid 51000 : ERROR NOT-A-SENSOR : NAN_ABORT 



Should I convert to contiguous index in preprocessing ?
-----------------------------------------------------------

HMM: these copyno are tighter packed than the old ones.
So less reason to use contiguous index. 

::


    A[blyth@localhost junosw]$ jcv CopyNumber
    ./Detector/Identifier/Identifier/CopyNumber.hh

    014 enum PMTID_OFFSET_DETSIM {
     15   kOFFSET_CD_LPMT=0,     kOFFSET_CD_LPMT_END=17612, // CD-LPMT
     16   kOFFSET_CD_SPMT=20000, kOFFSET_CD_SPMT_END=45600,  // CD-SPMT
     17   kOFFSET_WP_PMT=50000,  kOFFSET_WP_PMT_END=52400,  // WP-LPMT
     18   kOFFSET_WP_ATM_LPMT=52400,  kOFFSET_WP_ATM_LPMT_END=52748, //WP-Atmosphere-LPMT
     19   kOFFSET_WP_ATM_MPMT=53000,  kOFFSET_WP_ATM_MPMT_END=53600,  //WP-Atmosphere-MPMT (Medium, 8 inch)
     20   kOFFSET_WP_WAL_PMT=54000,  kOFFSET_WP_WAL_PMT_END=54005 //WP-Water-attenuation-length
     21 
     22 };

::

    In [1]: 17612 + (52400 - 50000)
    Out[1]: 20012

    In [3]: (45600 - 20000) + (17612 - 0) + (52400-50000)
    Out[3]: 45612


::

    [stree::postcreate
    stree::desc_sensor
     sensor_id.size 45612
     sensor_count 45612
     sensor_name.size 4
    sensor_name[
    PMT_3inch_log_phys
    pLPMT_NNVT_MCPPMT
    pLPMT_Hamamatsu_R12860
    mask_PMT_20inch_vetolMaskVirtual_phys
    ]
    [stree::desc_sensor_nd
     edge            0
     num_nd          382670
     num_nd_sensor   45612
     num_sid         45612
    ...
     nidx  71549 i      1 sensor_id      1 sensor_index      1 sensor_name      1
     nidx  71558 i      2 sensor_id      2 sensor_index      2 sensor_name      2
     nidx  71570 i      3 sensor_id      3 sensor_index      3 sensor_name      1
     nidx  71579 i      4 sensor_id      4 sensor_index      4 sensor_name      2
     nidx 244898 i  17611 sensor_id  17611 sensor_index  17611 sensor_name      2
     nidx 244910 i  17612 sensor_id  20000 sensor_index  17612 sensor_name      0
     nidx 244915 i  17613 sensor_id  20001 sensor_index  17613 sensor_name      0
     nidx 244920 i  17614 sensor_id  20002 sensor_index  17614 sensor_name      0
     nidx 372905 i  43211 sensor_id  45599 sensor_index  43211 sensor_name      0
     nidx 373070 i  43212 sensor_id  50000 sensor_index  43212 sensor_name      3
     nidx 373074 i  43213 sensor_id  50001 sensor_index  43213 sensor_name      3
     nidx 373078 i  43214 sensor_id  50002 sensor_index  43214 sensor_name      3
    ]stree::desc_sensor_nd
    stree::desc_sensor_id sensor_id.size 45612
    [
          0 sid        0
          1 sid        1
          2 sid        2
          3 sid        3
          4 sid        4
          5 sid        5
          6 sid        6
          7 sid        7
          8 sid        8
          9 sid        9
    ...
      17611 sid    17611
      17612 sid    20000
      17613 sid    20001
      17614 sid    20002
      43211 sid    45599
      43212 sid    50000
      43213 sid    50001
      43214 sid    50002
      45603 sid    52391
      45604 sid    52392
      45605 sid    52393
      45606 sid    52394
      45607 sid    52395
      45608 sid    52396
      45609 sid    52397
      45610 sid    52398
      45611 sid    52399
    ]]stree::postcreate




sensor_id from stree
-----------------------

::


    In [9]: pwd
    Out[9]: '/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/stree'


    n [6]: f.sensor_id
    Out[6]: 
    array([[    0],
           [    1],
           [    2],
           [    3],
           [    4],
           ...,
           [52395],
           [52396],
           [52397],
           [52398],
           [52399]], shape=(45612, 1), dtype=int32)

    In [7]: f.base
    Out[7]: '.'




        In [2]: f.sensor_id[:17612]
        Out[2]: 
        array([[    0],
               [    1],
               [    2],
               [    3],
               [    4],
               ...,
               [17607],
               [17608],
               [17609],
               [17610],
               [17611]], shape=(17612, 1), dtype=int32)

        In [3]: f.sensor_id[17612:17612+25600]
        Out[3]: 
        array([[20000],
               [20001],
               [20002],
               [20003],
               [20004],
               ...,
               [45595],
               [45596],
               [45597],
               [45598],
               [45599]], shape=(25600, 1), dtype=int32)

        In [4]: 45599 + 1 - 20000
        Out[4]: 25600

        In [5]: f.sensor_id[17612+25600:]
        Out[5]: 
        array([[50000],
               [50001],
               [50002],
               [50003],
               [50004],
               ...,
               [52395],
               [52396],
               [52397],
               [52398],
               [52399]], shape=(2400, 1), dtype=int32)

        In [6]: 








BP=U4SensorIdentifierDefault::getInstanceIdentity ipc
--------------------------------------------------------

::

    (gdb) bt
    #0  U4SensorIdentifierDefault::getInstanceIdentity (this=0xc277ed0, instance_outer_pv=0xb3f8290) at /data1/blyth/local/opticks_Debug/include/U4/U4SensorIdentifierDefault.h:93
    #1  0x00007fffc103d3d5 in U4Tree::identifySensitiveInstances (this=0xc277f60) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:1096
    #2  0x00007fffc103d1df in U4Tree::identifySensitive (this=0xc277f60) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:1034
    #3  0x00007fffc1039a15 in U4Tree::Create (st=0x6abde60, top=0xa4c7d50, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:231
    #4  0x00007fffc0fe3fde in G4CXOpticks::setGeometry (this=0xc277a80, world=0xa4c7d50) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #5  0x00007fffc0fe2909 in G4CXOpticks::SetGeometry (world=0xa4c7d50) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #6  0x00007fffc0fe2bb8 in G4CXOpticks::SetGeometry_JUNO (world=0xa4c7d50, sd=0x67b6ae0, jpmt=0xc195730, jlut=0xc275e70) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #7  0x00007fffbdd9aa68 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0xa4c7d50, sd=0x67b6ae0, ppd=0x668acf0, psd=0x67010b0, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #8  0x00007fffbdd60f56 in LSExpDetectorConstruction::setupOpticks (this=0xa274eb0, world=0xa4c7d50) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:457
    #9  0x00007fffbdd607f6 in LSExpDetectorConstruction::Construct (this=0xa274eb0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:378
    #10 0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #11 0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so



::

    U4SensorIdentifierDefault::getIdentity level 1 copyno 17532 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17532
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17536 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17536
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17539 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17539
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17555 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17555
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17567 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17567
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17570 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17570
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17591 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17591
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17593 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17593
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17595 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17595
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17596 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17596
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17599 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17599
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17601 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17601
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17603 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17603
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17605 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17605
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17607 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17607
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17609 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17609
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17610 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17610
    U4SensorIdentifierDefault::getIdentity level 1 copyno 17611 num_sd 2 is_sensor 1 pvn pLPMT_Hamamatsu_R12860 has_PMT_pvn YES identifier 17611
    U4Tree::identifySensitiveInstances factor 2 fac.sensors 4955
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50000 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50000
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50001 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50001
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50002 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50002
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50003 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50003
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50004 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50004
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50005 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50005
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50006 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50006
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50007 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50007
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50008 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50008
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50009 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50009
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50010 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50010
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50011 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50011
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50012 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50012
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50013 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50013
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50014 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50014
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50015 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50015
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50016 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50016
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50017 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50017
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50018 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50018
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50019 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50019
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50020 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50020
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50021 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50021
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50022 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50022
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50023 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50023
    U4SensorIdentifierDefault::getIdentity level 1 copyno 50024 num_sd 2 is_sensor 1 pvn mask_PMT_20inch_vetolMaskVirtual_phys has_PMT_pvn YES identifier 50024





Where did this lpmtid come from ? 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

qsim.h::

    1747     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor


squad.h::

    113 u:identity
    114     see cx:CSGOptiX7.cu:__closesthit__ch
    115 
    116     FROM July 2023
    117         instance_id which is *sensor_identifier+1* (as need lpmtid for QPMT),
    118         zero means not-a-sensor GPU side
    119 
    120     FORMERLY
    121         (( prim_idx & 0xffff ) << 16 ) | ( instance_id & 0xffff )
    122 

CSGOptiX7.cu::

    613 extern "C" __global__ void __closesthit__ch()
    614 {
    615     unsigned iindex = optixGetInstanceIndex() ;
    616     unsigned identity = optixGetInstanceId() ;
    ...
    668         prd->set_identity( identity ) ;
    669         prd->set_iindex(   iindex ) ;
    670         prd->set_globalPrimIdx_boundary_(  globalPrimIdx_boundary ) ;
    671         prd->set_lposcost(lposcost);


sqat4.h::

    345     QAT4_METHOD void getIdentity(int& ins_idx, int& gas_idx, int& sensor_identifier, int& sensor_index ) const
    346     {
    347         ins_idx           = q0.i.w ;   // formerly used unsigned and "- 1" 
    348         gas_idx           = q1.i.w ;
    349         sensor_identifier = q2.i.w ;
    350         sensor_index      = q3.i.w  ;
    351     }
    352 
    353     /**
    354     sqat4::get_IAS_OptixInstance_instanceId
    355     ----------------------------------------
    356 
    357     Canonical use by IAS_Builder::CollectInstances
    358 
    359     * July 2023 : QPMT needs lpmtid GPU side so changing from ins_idx to sensor_identifier
    360     * HMM: there are -1 in there, which as unsigned becomes  ~0u 
    361 
    362     YEP: that ~0u may be cause of notes/issues/unspecified_launch_failure_with_simpleLArTPC.rst
    363 
    364     **/
    365 
    366     QAT4_METHOD int get_IAS_OptixInstance_instanceId() const
    367     {
    368         //const unsigned& ins_idx = q0.u.w ;  
    369         //return ins_idx ; 
    370         const int& sensor_identifier = q2.i.w ;
    371         assert( sensor_identifier >= 0 );  // 0 means not a sensor GPU side, so subtract 1 to get actual sensorId
    372         return sensor_identifier ;
    373     }

U4Tree.h::

    0095 struct U4Tree
      96 {
      97     static constexpr const plog::Severity LEVEL = plog::info ;
      98     friend struct U4SimtraceTest ;       // for U4Tree ctor
      99     friend struct U4SimtraceSimpleTest ; // for U4Tree ctor
     100 
     101     stree*                                      st ;
     102     const G4VPhysicalVolume* const              top ;
     103     U4SensorIdentifier*                         sid ;
     104     int                                         level ;
     105     // export SSim__stree_level=1 controls this


    0248 inline U4Tree::U4Tree(
     249     stree* st_,
     250     const G4VPhysicalVolume* const top_,
     251     U4SensorIdentifier* sid_
     252     )
     253     :
     254     st(st_),
     255     top(top_),
     256     sid(sid_ ? sid_ : new U4SensorIdentifierDefault),
     257     level(st->level),
     258     num_surface_standard(-1),
     259     rayleigh_table(CreateRayleighTable()),




    1064 inline void U4Tree::identifySensitiveInstances()
    1065 {
    1066     unsigned num_factor = st->get_num_factor();
    1067     if(level > 0) std::cerr
    1068         << "[ U4Tree::identifySensitiveInstances"
    1069         << " num_factor " << num_factor
    1070         << " st.sensor_count " << st->sensor_count
    1071         << std::endl
    1072         ;
    1073 
    1074     for(unsigned i=0 ; i < num_factor ; i++)
    1075     {
    1076         std::vector<int> outer ;
    1077         st->get_factor_nodes(outer, i);
    1078         // nidx of outer volumes of the instances for each factor
    1079 
    1080         sfactor& fac = st->get_factor_(i);
    1081         fac.sensors = 0  ;
    1082 
    1083         for(unsigned j=0 ; j < outer.size() ; j++)
    1084         {
    1085             int nidx = outer[j] ;
    1086             const G4VPhysicalVolume* pv = get_pv_(nidx) ;
    1087             const char* pvn = pv->GetName().c_str() ;
    1088 
    1089             int sensor_id = sid->getInstanceIdentity(pv) ;
    1090             assert( sensor_id >= -1 );  // sensor_id:-1 signifies "not-a-sensor"
    1091 
    1092             int sensor_index = sensor_id > -1 ? st->sensor_count : -1 ;
    1093             int sensor_name = -1 ;
    1094 
    1095             if(sensor_id > -1 )
    1096             {
    1097                 st->sensor_count += 1 ;  // count over all factors
    1098                 fac.sensors += 1 ;       // count sensors for each factor
    1099                 sensor_name = suniquename::Add(pvn, st->sensor_name ) ;
    1100             }
    1101 
    1102             snode& nd = st->nds[nidx] ;
    1103             nd.sensor_id = sensor_id ;  // -1:not-a-sensor-at-this-juncture
    1104             nd.sensor_index = sensor_index ;
    1105             nd.sensor_name = sensor_name ;
    1106 
    1107             if(level > 1) std::cerr
    1108                 << "U4Tree::identifySensitiveInstances"
    1109                 << " i " << std::setw(7) << i
    1110                 << " sensor_id " << std::setw(7) << sensor_id
    1111                 << " sensor_index " << std::setw(7) << sensor_index
    1112                 << std::endl
    1113                 ;
    1114         }



    085 inline int U4SensorIdentifierDefault::getInstanceIdentity( const G4VPhysicalVolume* instance_outer_pv ) const
     86 {
     87     const char* pvn = instance_outer_pv ? instance_outer_pv->GetName().c_str() : "-" ;
     88     bool has_PMT_pvn = strstr(pvn, "PMT") != nullptr  ;
     89 
     90     const G4PVPlacement* pvp = dynamic_cast<const G4PVPlacement*>(instance_outer_pv) ;
     91     int copyno = pvp ? pvp->GetCopyNo() : -1 ;
     92 
     93     std::vector<const G4VPhysicalVolume*> sdpv ;
     94     FindSD_r(sdpv, instance_outer_pv, 0 );
     95 
     96     unsigned num_sd = sdpv.size() ;
     97     bool is_sensor = num_sd > 0 && has_PMT_pvn  ;
     98 
     99     //bool is_interesting_copyno = IsInterestingCopyNo(copyno) ; 
    100     //bool dump = is_sensor && is_interesting_copyno ; 
    101     bool dump = false ;
    102     //bool dump = true ;
    103     //bool dump = num_sd > 0 ; 
    104 
    105     if(dump) std::cout
    106         << "U4SensorIdentifierDefault::getIdentity"
    107         << " copyno " << copyno
    108         << " num_sd " << num_sd
    109         << " is_sensor " << is_sensor
    110         << " pvn " << ( pvn ? pvn : "-" )
    111         << " has_PMT_pvn " << ( has_PMT_pvn ? "YES" : "NO " )
    112         << std::endl
    113         ;
    114 
    115 
    116     return is_sensor ? copyno : -1  ;
    117 }


HMM : requiring "PMT" in the name of the outer volume potentially problematic 
------------------------------------------------------------------------------- 


::

    A[blyth@localhost CSGFoundry]$ cat mmlabel.txt 
    2905:sWorld
    5:PMT_3inch_pmt_solid
    9:NNVTMCPPMTsMask_virtual
    12:HamamatsuR12860sMask_virtual            #### NO PMT IN THE NAME 
    4:mask_PMT_20inch_vetosMask_virtual
    1:sStrutBallhead
    1:base_steel
    3:uni_acrylic1
    130:sPanel
    322:solidSJCLSanchor
    A[blyth@localhost CSGFoundry]$ 


True there is potential for trouble from that.
But it is not realized as the PV names do all have "PMT"
in them::

    [stree::postcreate
    stree::desc_sensor
     sensor_id.size 45612
     sensor_count 45612
     sensor_name.size 4
    sensor_name[
    PMT_3inch_log_phys
    pLPMT_NNVT_MCPPMT
    pLPMT_Hamamatsu_R12860
    mask_PMT_20inch_vetolMaskVirtual_phys
    ]
    [stree::desc_sensor_nd
     edge            0
     num_nd          382670
     num_nd_sensor   45612
     num_sid         45612
    ...
     nidx  71549 i      1 sensor_id      1 sensor_index      1 sensor_name      1
     nidx  71558 i      2 sensor_id      2 sensor_index      2 sensor_name      2
     nidx  71570 i      3 sensor_id      3 sensor_index      3 sensor_name      1
     nidx  71579 i      4 sensor_id      4 sensor_index      4 sensor_name      2
     nidx 244898 i  17611 sensor_id  17611 sensor_index  17611 sensor_name      2
     nidx 244910 i  17612 sensor_id  20000 sensor_index  17612 sensor_name      0
     nidx 244915 i  17613 sensor_id  20001 sensor_index  17613 sensor_name      0
     nidx 244920 i  17614 sensor_id  20002 sensor_index  17614 sensor_name      0
     nidx 372905 i  43211 sensor_id  45599 sensor_index  43211 sensor_name      0
     nidx 373070 i  43212 sensor_id  50000 sensor_index  43212 sensor_name      3
     nidx 373074 i  43213 sensor_id  50001 sensor_index  43213 sensor_name      3
     nidx 373078 i  43214 sensor_id  50002 sensor_index  43214 sensor_name      3
    ]stree::desc_sensor_nd
    stree::desc_sensor_id sensor_id.size 45612
    [
          0 sid        0
          1 sid        1
          2 sid        2
          3 sid        3
          4 sid        4
          5 sid        5
          6 sid        6
          7 sid        7
          8 sid        8
          9 sid        9
    ...
      17611 sid    17611
      17612 sid    20000
      17613 sid    20001
      17614 sid    20002
      43211 sid    45599
      43212 sid    50000
      43213 sid    50001
      43214 sid    50002
      45603 sid    52391
      45604 sid    52392
      45605 sid    52393
      45606 sid    52394
      45607 sid    52395
      45608 sid    52396
      45609 sid    52397
      45610 sid    52398
      45611 sid    52399
    ]]stree::postcreate







Contiguous
~~~~~~~~~~~

::

    A[blyth@localhost junosw]$ jgl Contiguous
    ./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h
    A[blyth@localhost junosw]$ 


    252 inline int PMTSimParamData::get_pmtContiguousIndex_slowly(int pmtid) const
    253 {
    254     const std::vector<int>& a = m_all_pmtID ;
    255     size_t idx = std::distance( a.begin(), std::find( a.begin(), a.end(), pmtid )) ;
    256     return idx < a.size() ? int(idx) : -1 ;
    257 }
    258 
    259 /**
    260 PMTSimParamData::get_pmtContiguousIndex
    261 ---------------------------------------
    262 
    263 ::
    264 
    265     pmtid
    266     |
    267     |                          SPMT 
    268     |
    269     + kOFFSET_CD_SPMT=300000
    270     |
    271     |                          WPMT    
    272     |
    273     + kOFFSET_WP_PMT=30000
    274     |  
    275     |                          LPMT 
    276     |
    277     + kOFFSET_CD_LPMT=0 
    278 
    279 
    280 **/
    281 inline int PMTSimParamData::get_pmtContiguousIndex(int pmtid) const
    282 {
    283     int idx = -1 ;
    284     if(PMT::IsCD(pmtid) and PMT::Is20inch(pmtid)) {
    285         idx = pmtid ;    // LPMT 
    286     } else if(PMT::IsWP(pmtid)) {
    287         idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    288     } else if (PMT::IsCD(pmtid) and PMT::Is3inch(pmtid)){
    289         idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    290     }
    291 
    292     return idx ;
    293 }






B side bizarre
----------------

::

    In [7]: a.f.record[0,0]
    Out[7]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

    In [8]: b.f.record[0,0]
    Out[8]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)



::


    In [10]: b.f.record[0,0:1]
    Out[10]: 
    array([[[ 3316.214, 20442.654,   989.392,     0.1  ],
            [   -0.16 ,    -0.986,    -0.036,     0.   ],
            [   -0.987,     0.16 ,     0.   ,   440.   ],
            [    0.   ,     0.   ,     0.   ,     0.   ]]], dtype=float32)

    In [11]: b.f.record[0,0:2]
    Out[11]: 
    array([[[ 3316.214, 20442.654,   989.392,     0.1  ],
            [   -0.16 ,    -0.986,    -0.036,     0.   ],
            [   -0.987,     0.16 ,     0.   ,   440.   ],
            [    0.   ,     0.   ,     0.   ,     0.   ]],

           [[ -523.403, -3226.422,   133.483,   110.716],
            [   -0.16 ,    -0.986,    -0.036,     0.   ],
            [   -0.987,     0.16 ,     0.   ,   440.   ],
            [    0.   ,     0.   ,     0.   ,     0.   ]]], dtype=float32)

    In [12]: b.f.record[0,0:2,0]
    Out[12]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [ -523.403, -3226.422,   133.483,   110.716]], dtype=float32)

    In [13]: b.f.record[1,0:2,0]
    Out[13]: 
    array([[ 3316.214, 20442.654,   989.387,     0.1  ],
           [ -222.037, -1368.672,   200.657,   102.034]], dtype=float32)

    In [14]: b.f.record[2,0:2,0]
    Out[14]: 
    array([[ 3316.214, 20442.656,   989.382,     0.1  ],
           [  191.016,  1177.57 ,   292.728,    90.134]], dtype=float32)

    In [15]: b.f.record[3,0:2,0]
    Out[15]: 
    array([[ 3316.214, 20442.656,   989.377,     0.1  ],
           [ 2109.171, 13001.918,   720.309,    34.874]], dtype=float32)

    In [16]: b.f.record[4,0:2,0]
    Out[16]: 
    array([[ 3316.214, 20442.656,   989.372,     0.1  ],
           [  719.63 ,  4436.178,   410.554,    74.905]], dtype=float32)



B side looks to be crossing sphere and getting absorbed
--------------------------------------------------------


::

    In [19]: w = b.q_startswith("TO SA")

    In [30]: b.f.record[w,0,0]
    Out[30]: 
    array([[ 3316.214, 20442.656,   989.367,     0.1  ],
           [ 3316.214, 20442.656,   989.362,     0.1  ],
           [ 3316.214, 20442.656,   989.352,     0.1  ],
           [ 3316.214, 20442.656,   989.347,     0.1  ],
           [ 3316.214, 20442.656,   989.337,     0.1  ],
           ...,
           [ 3319.07 , 20460.26 ,   489.77 ,     0.1  ],
           [ 3319.07 , 20460.26 ,   489.745,     0.1  ],
           [ 3319.07 , 20460.26 ,   489.735,     0.1  ],
           [ 3319.07 , 20460.262,   489.715,     0.1  ],
           [ 3319.07 , 20460.262,   489.71 ,     0.1  ]], shape=(35965, 4), dtype=float32)

    In [39]: np.sqrt(np.sum(b.f.record[w,0,0,:3]*b.f.record[w,0,0,:3],axis=1)).min()
    Out[39]: np.float32(20731.998)

    In [40]: np.sqrt(np.sum(b.f.record[w,0,0,:3]*b.f.record[w,0,0,:3],axis=1)).max()
    Out[40]: np.float32(20733.508)




    In [29]: b.f.record[w,1,0]
    Out[29]: 
    array([[ -3466.772, -21370.633,   -522.663,    195.512],
           [ -3466.772, -21370.635,   -522.668,    195.512],
           [ -3466.772, -21370.635,   -522.678,    195.512],
           [ -3466.772, -21370.635,   -522.683,    195.512],
           [ -3466.772, -21370.635,   -522.693,    195.512],
           ...,
           [ -3466.772, -21370.633,  -1022.897,    195.595],
           [ -3466.772, -21370.633,  -1022.922,    195.595],
           [ -3466.772, -21370.635,  -1022.932,    195.595],
           [ -3466.772, -21370.633,  -1022.952,    195.595],
           [ -3466.772, -21370.633,  -1022.957,    195.595]], shape=(35965, 4), dtype=float32)

    In [43]: np.sqrt(np.sum(b.f.record[w,1,0,:3]*b.f.record[w,1,0,:3],axis=1)).min()
    Out[43]: np.float32(21656.307)

    In [44]: np.sqrt(np.sum(b.f.record[w,1,0,:3]*b.f.record[w,1,0,:3],axis=1)).max()
    Out[44]: np.float32(21674.154)


    In [49]: np.sqrt(np.sum((b.f.record[w,1,0,:3] - b.f.record[w,0,0,:3])* (b.f.record[w,1,0,:3] - b.f.record[w,0,0,:3]), axis=1)).min()
    Out[49]: np.float32(42386.863)

    In [50]: np.sqrt(np.sum((b.f.record[w,1,0,:3] - b.f.record[w,0,0,:3])* (b.f.record[w,1,0,:3] - b.f.record[w,0,0,:3]), axis=1)).max()
    Out[50]: np.float32(42404.71)

    In [52]: (b.f.record[w,1,0,3] - b.f.record[w,0,0,3]).min()
    Out[52]: np.float32(195.41237)

    In [53]: (b.f.record[w,1,0,3] - b.f.record[w,0,0,3]).max()
    Out[53]: np.float32(195.49464)

    In [54]: 42404.71/195.49464   ## 216.9 mm/ns
    Out[54]: 216.90983445888847

    In [63]: 299/216.9
    Out[63]: 1.3785154449054864

    In [66]: cf.sim.stree.material.vetoWater.GROUPVEL
    Out[66]: 
    array([[  0.   , 218.693],
           [  0.   , 217.883],
           [  0.   , 218.204],
           [  0.   , 218.183],
           [  0.   , 218.157],
           [  0.   , 218.246],
           [  0.   , 218.204],
           [  0.   , 218.158],
           [  0.   , 218.212],
           [  0.   , 218.155],
           [  0.   , 218.188],
           [  0.   , 218.208],
           [  0.   , 216.507],
           [  0.   , 215.846],
           [  0.   , 218.128],
           [  0.   , 218.11 ],
           [  0.   , 215.856],
           [  0.   , 218.798],
           [  0.   , 215.988],
           [  0.   , 218.001],
           [  0.   , 218.046],
           [  0.   , 218.029],
           [  0.   , 218.046],
           [  0.   , 218.01 ],
           [  0.   , 218.041],
           [  0.   , 216.226],
           [  0.   , 218.568],
           [  0.   , 216.325],
           [  0.   , 217.945],
           [  0.   , 217.962],
           [  0.   , 217.941],
           [  0.   , 217.951],
           [  0.   , 216.505],
           [  0.   , 207.106],
           [  0.   , 220.436],
           [  0.   , 225.408]])






