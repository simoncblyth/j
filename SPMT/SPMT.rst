SPMT
=====

Overview
-----------

* prior :doc:`../efficiency/flagmask_flag_SD_EC_EX`


ipc with new InputPhotons _X25 narrowed for SPMT
--------------------------------------------------

ipcv::

    157     elif [ "$TEST" == "SPMT" ]; then
    158 
    159        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    160        #opticks_input_photon=RainXZ_Z230_100k_f8.npy    # too long for tiny SPMT
    161        opticks_input_photon=RainXZ_Z230_X25_100k_f8.npy
    162        opticks_input_photon_frame=PMT_3inch:0:0


WOW, that make the issue stand out::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 21919 hitCollectionAlt 74 hcMuon 0 GPU YES


    AB
    [sseq_index_ab::desc u_size 288 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum     2.5750 ndf  4.0000 sum/ndf     0.6437 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT SD                                                                                      :   99106     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
        TO BT BT EX                                                                                      :      -1  77187 :     0.0000 : N :      -1      0 : AZERO C2EXC  
        TO BT BT EC                                                                                      :      -1  21843 :     0.0000 : N :      -1      2 : AZERO C2EXC  
        TO AB                                                                                            :     456    486 :     0.9554 : Y :      25     76 :   
        TO BT BT AB                                                                                      :     119    110 :     0.3537 : Y :    2121    261 :   
        TO BT AB                                                                                         :      36     41 :     0.3247 : Y :    3833    420 :   
        TO BT BR BT BT BT AB                                                                             :      30     38 :     0.9412 : Y :    2867   6191 :   
        TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                        :      16     14 :     0.0000 : N :    5229   7937 : C2EXC  
        TO SC BT BT BT BT EC                                                                             :      13     14 :     0.0000 : N :    8966  28955 : C2EXC  
        TO SC BT BT BT BT SA                                                                             :       8     12 :     0.0000 : N :    6692   9608 : C2EXC  


:: 

    In [1]: 77187+21843
    Out[1]: 99030

    In [2]: 21843/(77187+21843)
    Out[2]: 0.22056952438654953






B has no SD, but A has many : review 3inch treatment
------------------------------------------------------

jcv junoSD_PMT_v2::

     459     double qe = 1;
     460     double ce = 1;
     462     int pmtID = get_pmtid(track);
     467     if(m_use_pmtsimsvc){
     468         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     469         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     470      }
     ...
     476     double f_angle_response = 1.0;
     477     double de = qe*ce*f_angle_response ;
     478     if (de>1.0){
     479         std::cout<<"junoSD_PMT_v2:: de is larger than 1.0"<<std::endl;
     480     }
     481     bool de_cull = G4UniformRand() > de ;
     482 
     483 
     484 
     485 
     486 
     487     if (de_cull)
     488     {
     489 #ifdef WITH_G4CXOPTICKS_EPH
     490        m_eph = EPH::NDECULL ;
     491 #endif
     492        return false;
     493     }



where to do A side COLLECT/CULL ?
-------------------------------------

::

    n [1]: a.q
    Out[1]: 
    array([[b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           ...,
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SD                                                                                     ']], shape=(100000, 1), dtype='|S96')

    In [2]: b.q
    Out[2]: 
    array([[b'TO BT BT EX                                                                                     '],
           [b'TO BT BT EX                                                                                     '],
           [b'TO BT BT EC                                                                                     '],
           [b'TO BT BT EC                                                                                     '],
           [b'TO BT BT EX                                                                                     '],
           ...,
           [b'TO BT BT EX                                                                                     '],
           [b'TO BT BT EC                                                                                     '],
           [b'TO BT BT EX                                                                                     '],
           [b'TO BT BT EX                                                                                     '],
           [b'TO BT BT EX                                                                                     ']], shape=(100000, 1), dtype='|S96')




::

    PIDX=0 ipc

    //qsim.propagate_to_boundary.tail.SAIL pidx       0 : post = np.array([-5459.87158,18216.12695,3668.73730,   1.08475]) ;  sail_time_delta =    0.01079   
    //qsim.propagate.body pidx       0 bounce 2 command 3 flag 0 s.optical.x 20 s.optical.y 2 
    //qsim.propagate.body.WITH_CUSTOM4 pidx       0  BOUNDARY ems 2 lposcost   0.555 
    //qsim.propagate_at_surface.SA/SD.BREAK pidx       0 : flag 64 
    //qsim.propagate.tail pidx       0 bounce 2 command 1 flag 64 ctx.s.optical.y(ems) 2 
    2025-06-20 21:26:36.507 INFO  [2371855] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc


ipc dev cycle too long so setup cxs_min.sh
--------------------------------------------

::

    1695     int action = u_surface < absorb + detect ? BREAK : CONTINUE  ;
    1696 
    1697     if( action == BREAK )
    1698     {
    1699 
    1700 #if defined(WITH_CUSTOM4)
    1701         int pmtid = ctx.prd->identity() - 1 ;     // identity comes from optixInstance.instanceId where 0 means not-a-sensor
    1702         // here need a new qpmt call to get the needed efficiency   

    ///  need selection opmtid in spmt range

    1703 
    1704 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1705         if(ctx.pidx == base->pidx)
    1706         printf("//qsim.propagate_at_surface.BREAK pidx %7d : pmtid %d \n" , ctx.pidx, pmtid );
    1707 #endif
    1708 #endif
    1709 
    1710         flag = u_surface < absorb ? SURFACE_ABSORB : SURFACE_DETECT  ;
    1711 
    1712 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1713         if(ctx.pidx == base->pidx)
    1714         printf("//qsim.propagate_at_surface.SA/SD.BREAK pidx %7d : flag %d \n" , ctx.pidx, flag );
    1715 #endif
    1716     }





::

    PIDX=0 cxs_min.sh

    //qsim.propagate_to_boundary.head pidx       0 : u_scattering     0.6939 u_absorption     0.0371 
    //qsim.propagate_to_boundary.tail.SAIL pidx       0 : post = np.array([-5459.87158,18216.12695,3668.73730,   1.08475]) ;  sail_time_delta =    0.01079   
    //qsim.propagate.body pidx       0 bounce 2 command 3 flag 0 s.optical.x 20 s.optical.y 2 
    //qsim.propagate.body.WITH_CUSTOM4 pidx       0  BOUNDARY ems 2 lposcost   0.555 
    //qsim.propagate_at_surface.BREAK pidx       0 : pmtid 20000 
    //qsim.propagate_at_surface.SA/SD.BREAK pidx       0 : flag 64 
    //qsim.propagate.tail pidx       0 bounce 2 command 1 flag 64 ctx.s.optical.y(ems) 2 
    2025-06-20 21:56:11.276 INFO  [185666] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7f9600000000
    2025-06-20 21:56:11.454 INFO  [185666] [QSim::simulate@492]  eventID 0 tot_dt    0.005453 tot_ph     100000 tot_ph/M   0.100000 tot_ht         74 tot_ht/M   0.000074 tot_ht/tot_ph   0.000740 reset_ YES
    2025-06-20 21:56:11.457 INFO  [185666] [SEvt::save@4158] /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Phil


setup cxs_min.sh  input_photon_s_pmt
---------------------------------------

::

    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_s_pmt/A000 
    qtab
    [[b'99106' b'0' b'TO BT BT SD                                                                                     ']
     [b'456' b'25' b'TO AB                                                                                           ']
     [b'119' b'2121' b'TO BT BT AB                                                                                     ']
     [b'36' b'3833' b'TO BT AB                                                                                        ']
     [b'30' b'2867' b'TO BT BR BT BT BT AB                                                                            ']
     [b'16' b'5229' b'TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                       ']
     [b'13' b'8966' b'TO SC BT BT BT BT EC                                                                            ']
     [b'10' b'33607' b'TO BT BR BT BT BT BT BT BT BT BT BT EC                                                          ']
     [b'10' b'8104' b'TO BT BR BT BT BT BT BT BT BT BT BT SA                                                          ']
     [b'9' b'5616' b'TO BT BR BT BT BT SC AB                                                                         ']]
    not plotting as MODE 0 in environ





PMTSimParamSvc::get_pmtid_qe
------------------------------

jcv PMTSimParamSvc::

    1069 double PMTSimParamSvc::get_pmtid_qe(int pmtid, double energy) const
    1070 {
    1071
    1072   int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid) ;
    1073   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1074   double qe = get_pmtcat_qe(pmtcat, energy);
    1075   double qe_scale = get_pmt_qe_scale(pmtid);
    1076   qe = qe*qe_scale;
    1077   assert(qe > 0 && qe < 1);
    1078   return qe;
    1079 }


get_pmtcat_qe needs handling of different length qe-vs-energy prop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    1060 double PMTSimParamSvc::get_pmtcat_qe(int pmtcat, double energy) const
    1061 {
    1062     double qe = -1 ;
    1063     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(pmtcat);
    1064     assert(vec);
    1065     qe = vec->Value(energy);
    1066     return qe;
    1067 }

    1124 G4MaterialPropertyVector*  PMTSimParamSvc::get_pmtcat_qe_vs_energy(int pmtcat) const
    1125 {
    1126     assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1127     G4MaterialPropertyVector * vec = 0 ;
    1128     switch(pmtcat)
    1129     {   //FIXME:KPMT_Unknown represent WP pmt,which use normal NNVTMCP ?
    1130         case kPMT_Unknown:     vec = m_QEshape_WP_PMT    ; break ;
    1131         case kPMT_NNVT:        vec = m_QEshape_NNVT      ; break ;
    1132         case kPMT_Hamamatsu:   vec = m_QEshape_R12860    ; break ;
    1133         case kPMT_HZC:         vec = m_QEshape_HZC       ; break ;
    1134         case kPMT_NNVT_HighQE: vec = m_QEshape_NNVT_HiQE ; break ;



get_pmt_qe_scale(pmtid) : avoided complication by collecting m_all_pmtID_qe_scale
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I collected m_all_pmtID_qe_scale to avoid delving into the at420nm details::

     234     for(int i=0 ; i < m_PmtTotal_ALL ; i++)
     235     {
     236         int pmtid = m_all_pmtID[i] ; 
     237         double qe_scale = get_pmt_qe_scale(pmtid) ; 
     238         m_all_pmtID_qe_scale.push_back(qe_scale); 
     239     }


get_pmtid_ce : only cat 2 for small pmt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    1140 double PMTSimParamSvc::get_pmtid_ce(int pmtid , double theta) const
    1141 {
    1142      int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    1143      double ce = get_pmtcat_ce(pmtcat,theta);
    1144      assert( ce > 0 );
    1145      return  ce ;
    1146 
    1147 }


get_pmtcat_ce :  ce 1. anyhow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    1149 double PMTSimParamSvc::get_pmtcat_ce(int pmtcat, double theta) const
    1150 {
    1151 
    1152   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1153   double ce = -1;
    1154   G4MaterialPropertyVector * vec = 0 ;
    1155   switch(pmtcat)
    1156     {   //FIXME:KPMT_Unknown represent WP pmt,which are use normal NNVTMCP ?
    1157         case kPMT_Unknown:     { vec = m_CE_WP_PMT ; } ; break ;
    1158         case kPMT_NNVT:        { vec = m_CE_NNVTMCP ; } ; break ;
    1159         case kPMT_Hamamatsu:   { vec = m_CE_R12860 ; } ; break ;
    1160         case kPMT_HZC:         { ce = 1.0 ; } ; return ce ;
    1161         case kPMT_NNVT_HighQE: { vec = m_CE_NNVTMCP_HiQE ; } ; break ;
    1162     }
    1163 
    1164   if(vec){
    1165         //vec -> SetSpline(false);  that is default 
    1166         ce = vec->Value(theta);
    1167   }
    1168 
    1169   //double CE = ce >= 1 ? 1 : ce ;  
    1170   assert(ce > 0 && ce <= 1 );
    1171   return ce;
    1172 }








Have QEshape_HZC.npy
------------------------

::

    [blyth@localhost PMTSimParamData]$ cd QEshape
    A[blyth@localhost QEshape]$ l
    total 28
    4 -rw-r--r--. 1 blyth blyth   93 Jun 10 16:18 NPFold_index.txt
    0 -rw-r--r--. 1 blyth blyth    0 Jun 10 16:18 NPFold_names.txt
    4 -rw-r--r--. 1 blyth blyth 1088 Jun 10 16:18 QEshape_HZC.npy
    4 -rw-r--r--. 1 blyth blyth  816 Jun 10 16:18 QEshape_NNVT_HiQE.npy
    4 -rw-r--r--. 1 blyth blyth  816 Jun 10 16:18 QEshape_NNVT.npy
    4 -rw-r--r--. 1 blyth blyth  816 Jun 10 16:18 QEshape_R12860.npy
    4 -rw-r--r--. 1 blyth blyth  816 Jun 10 16:18 QEshape_WP_PMT.npy
    4 drwxr-xr-x. 7 blyth blyth 4096 Jun  9 20:59 ..
    0 drwxr-xr-x. 2 blyth blyth  182 Jun  7 18:21 .
    A[blyth@localhost QEshape]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: `?` alone on a line will brings up IPython's help
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.QEshape_HZC                                      :              (60, 2) : 10 days, 1:15:17.600064 
      : f.QEshape_NNVT                                     :              (43, 2) : 10 days, 1:15:17.600064 
      : f.QEshape_NNVT_HiQE                                :              (43, 2) : 10 days, 1:15:17.600064 
      : f.QEshape_R12860                                   :              (43, 2) : 10 days, 1:15:17.600064 
      : f.QEshape_WP_PMT                                   :              (43, 2) : 10 days, 1:15:17.600064 
      : f.NPFold_index                                     :                 (5,) : 10 days, 1:15:17.600064 
      : f.NPFold_names                                     :                 (0,) : 10 days, 1:15:17.600064 

     min_stamp : 2025-06-10 16:18:59.675449 
     max_stamp : 2025-06-10 16:18:59.675449 
     dif_stamp : 0:00:00 
        1135     }
        1136     assert(vec);
        1137     return vec;
        1138 }








pmtcat is 2 for all SPMT
--------------------------

::

    A[blyth@localhost PMTParamData]$ f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.pmtCat                                           :           (45612, 2) : 10 days, 1:07:36.250709 
      : f.NPFold_index                                     :                 (1,) : 10 days, 1:07:36.250709 
      : f.NPFold_names                                     :                 (0,) : 10 days, 1:07:36.250709 

     min_stamp : 2025-06-10 16:18:59.671449 
     max_stamp : 2025-06-10 16:18:59.671449 
     dif_stamp : 0:00:00 
     age_stamp : 10 days, 1:07:36.250709 

    In [1]: f.pmtCat[:17612]
    Out[1]: 
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

    In [2]: f.pmtCat[17612:17612+25600]
    Out[2]: 
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

    In [3]: np.unique(f.pmtCat[17612:17612+25600,1], return_counts=True)
    Out[3]: (array([2], dtype=int32), array([25600]))






