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



after qe_scale contiguous/oldcontiguous bugfix : have perfect match for input photons onto one S_PMT
--------------------------------------------------------------------------------------------------------

::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 21919 hitCollectionAlt 21893 hcMuon 0 GPU YES

    SABHit  a_nhit : (   21893 +-  147 )  b_nhit:(    21919 +-  148 )  a/b: (  0.999 +-  0.013 )  b/a: (  1.001 +-  0.014)  [assume uncorr.]


    AB
    [sseq_index_ab::desc u_size 286 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum     2.6529 ndf  6.0000 sum/ndf     0.4422 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT EX                                                                                      :   77287  77187 :     0.0647 : Y :       0      0 :   
        TO BT BT EC                                                                                      :   21819  21843 :     0.0132 : Y :       3      2 :   
        TO AB                                                                                            :     456    486 :     0.9554 : Y :      25     76 :   
        TO BT BT AB                                                                                      :     119    110 :     0.3537 : Y :    2121    261 :   
        TO BT AB                                                                                         :      36     41 :     0.3247 : Y :    3833    420 :   
        TO BT BR BT BT BT AB                                                                             :      30     38 :     0.9412 : Y :    2867   6191 :   
        TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                        :      16     14 :     0.0000 : N :    5229   7937 : C2EXC  
        TO SC BT BT BT BT EC                                                                             :      13     14 :     0.0000 : N :    8966  28955 : C2EXC  
        TO SC BT BT BT BT SA                                                                             :       8     12 :     0.0000 : N :    6692   9608 : C2EXC  
        TO BT BR BT BT BT SC BT BT BT BT BT BT SA                                                        :       9     11 :     0.0000 : N :   10946  34936 : C2EXC  
        TO BT BR BT BT BT BT BT BT BT BT BT EC                                                           :      10     11 :     0.0000 : N :   33607   7618 : C2EXC  



after getting SPMT info to GPU and using in qsim::propagate_at_surface
--------------------------------------------------------------------------

::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 21919 hitCollectionAlt 27296 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0

    ABHit  a_nhit : (   27296 +-  165 )  b_nhit:(    21919 +-  148 )  a/b: (  1.245 +-  0.016 )  b/a: (  0.803 +-  0.010)  [assume uncorr.]


    AB
    [sseq_index_ab::desc u_size 286 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   780.9223 ndf  6.0000 sum/ndf   130.1537 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT BT EX                                                                                      :   71884  77187 :   188.6471 : Y :       0      0 : DEVIANT  `
    :r:`TO BT BT EC                                                                                      :   27222  21843 :   589.7002 : Y :       3      2 : DEVIANT  `
        TO AB                                                                                            :     456    486 :     0.9554 : Y :      25     76 :   
        TO BT BT AB                                                                                      :     119    110 :     0.3537 : Y :    2121    261 :   
        TO BT AB                                                                                         :      36     41 :     0.3247 : Y :    3833    420 :   
        TO BT BR BT BT BT AB                                                                             :      30     38 :     0.9412 : Y :    2867   6191 :   
        TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                        :      16     14 :     0.0000 : N :    5229   7937 : C2EXC  
        TO SC BT BT BT BT EC                                                                             :      13     14 :     0.0000 : N :    8966  28955 : C2EXC  
        TO SC BT BT BT BT SA                                                                             :       8     12 :     0.0000 : N :    6692   9608 : C2EXC  


EX+EC sum is matching but A side collecing 25% more ?::

    In [1]: 71884 + 27222  // A : EX+EC   A side collecting 25% too much
    Out[1]: 99106

    In [2]: 77187 + 21843  // B : EX+EC
    Out[2]: 99030



PIDX=0 cxs_min.sh::

    //qsim.propagate.body pidx       0 bounce 2 command 3 flag 0 s.optical.x 20 s.optical.y 2 
    //qsim.propagate.body.WITH_CUSTOM4 pidx       0  BOUNDARY ems 2 lposcost   0.555 
    //qsim.propagate_at_surface.BREAK.is_spmtid pidx       0 : pmtid 20000 energy_eV   2.818 qe_shape   0.249 qe_scale   1.099 qe   0.274 detect   1.000 absorb   0.000 reflect_specular   0.000 reflect_diffuse   0.000 
    //qsim.propagate_at_surface.SA/SD.BREAK pidx       0 : flag 16384 
    //qsim.propagate.tail pidx       0 bounce 2 command 1 flag 16384 ctx.s.optical.y(ems) 2 
    2025-06-23 21:45:24.823 INFO  [3219434] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7f4500000000
    2025-06-23 21:45:25.014 INFO  [3219434] [QSim::simulate@492]  eventID 0 tot_dt    0.004757 tot_ph     100000 tot_ph/M   0.100000 tot_ht      27296 tot_ht/M   0.027296 tot_ht/tot_ph   0.272960 reset_ YES


qe_shape matches but qe_scale does not::

    In [6]: np.interp( 2.818, p.s_qeshape[0, :-1,0], p.s_qeshape[0,:-1,1] )
    Out[6]: np.float64(0.24930848206507444)



BP=junoSD_PMT_v2::ProcessHits_ ipc
------------------------------------

::

    Thread 1 "python" hit Breakpoint 3, junoSD_PMT_v2::ProcessHits_ (this=0xa243ec0, step=0x68703f0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:401
    401	    if (edep<=0.0) {
    (gdb) p edep
    $2 = 2.8178227113797455e-06

    (gdb) p 1239.84198433200208455673/2.8178227113797455
    $3 = 439.9999969213514


    gdb) list
    462	    int pmtID = get_pmtid(track);
    463	    // = final DE = QE * CE,
    464	    // but QE is already applied (this is old implementation,
    465	    // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
    466	    // = DE: Detection Efficiency
    467	    if(m_use_pmtsimsvc){
    468	        qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
    469	        ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
    470	     }
    471	     else{
    (gdb) p pmtID
    $4 = 20000
    (gdb) p m_use_pmtsimsvc
    $5 = true
    (gdb) p m_enable_optical_model
    $6 = true
    (gdb) p PMT::Is20inch(pmtID)
    $7 = false

    (gdb) p m_PMTSimParsvc
    $8 = (IPMTSimParamSvc *) 0x65853c0

    (gdb) p m_PMTSimParsvc->get_pmtid_qe(pmtID,edep)
    $9 = 0.22096722445789505   ## A SIDE qe_shape 0.274  ??? PRECISELY THE ISSUE ???

    (gdb) p m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta())
    $10 = 1



    (gdb) b PMTSimParamSvc::get_pmtid_qe


    (gdb) list
    1067	}
    1068	
    1069	double PMTSimParamSvc::get_pmtid_qe(int pmtid, double energy) const
    1070	{
    1071	 
    1072	  int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid) ;
    1073	  assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 ); 
    1074	  double qe = get_pmtcat_qe(pmtcat, energy);
    1075	  double qe_scale = get_pmt_qe_scale(pmtid);
    1076	  qe = qe*qe_scale;
    (gdb) b 1076
    Breakpoint 7 at 0x7fffbebd6c49: file /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc, line 1076.
    (gdb) p pmtid
    $11 = 20000
    (gdb) p m_PMTParamSvc->getPMTCategory(pmtid)
    $12 = 2
    (gdb) p kPMT_Unknown
    $13 = kPMT_Unknown
    (gdb) p (int)kPMT_Unknown
    $14 = -1
    (gdb) p (int)kPMT_NNVT_HighQE
    $15 = 3
    (gdb) b PMTSimParamSvc::get_pmtcat_qe
    Breakpoint 8 at 0x7fffbebd6af0: file /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc, line 1062.
    (gdb) b PMTSimParamSvc::get_pmt_qe_scale
    Breakpoint 9 at 0x7fffbebd6cb6: file /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc, line 1083.
    (gdb) 





    (gdb) b 1076
    Breakpoint 3 at 0x7fffbebd6c49: file /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc, line 1076.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 3, PMTSimParamSvc::get_pmtid_qe (this=0x65bdf20, pmtid=20000, energy=2.8178227113797455e-06) at /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:1076
    1076	  qe = qe*qe_scale;
    (gdb) p qe
    $1 = 0.24930611765217103


QEShape interpolation matches::

    In [8]: np.interp( 2.8178227113797455, p.s_qeshape[0, :-1,0], p.s_qeshape[0,:-1,1] )
    Out[8]: np.float64(0.2493061113567255)


QEScale different::

    (gdb) p qe_scale
    $2 = 0.88632892982668765

B side qe_scale from debugger matches the qeScale array::

    In [8]: pwd
    Out[8]: '/home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt/PMTSimParamData'

    In [9]: f.qeScale[17612+2400,0]
    Out[9]: np.float64(0.8863289298266877)


    In [6]: f.pmtID[17612+2400:17612+2400+25600,0]
    Out[6]: array([20000, 20001, 20002, 20003, 20004, ..., 45595, 45596, 45597, 45598, 45599], shape=(25600,), dtype=int32)

    In [7]: f.qeScale[17612+2400:17612+2400+25600,0]
    Out[7]: array([0.886, 0.962, 1.029, 1.025, 0.978, ..., 0.981, 0.979, 1.009, 0.965, 0.979], shape=(25600,))



But that does not match SPMT_test.sh pdb::

    In [1]: s.s_qescale
    Out[1]: 
    array([[1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           ...,
           [0.991],
           [0.989],
           [1.003],
           [1.029],
           [0.939],
           [0.996],
           [1.005],
           [0.981],
           [1.118],
           [1.003],
           [0.951],
           [1.002],
           [0.987],
           [1.048],
           [1.032],
           [1.045]], shape=(25600, 1), dtype=float32)

    In [3]: t.get_s_qescale_from_spmtid
    Out[3]: 
    array([[1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           [1.099],
           ...,
           [0.991],
           [0.989],
           [1.003],
           [1.029],
           [0.939],
           [0.996],
           [1.005],
           [0.981],
           [1.118],
           [1.003],
           [0.951],
           [1.002],
           [0.987],
           [1.048],
           [1.032],
           [1.045]], shape=(25600, 1), dtype=float32)


Must be bug at SPMT.h level because the Data level looks OK::

    In [6]: f.pmtID[17612+2400:17612+2400+25600,0]
    Out[6]: array([20000, 20001, 20002, 20003, 20004, ..., 45595, 45596, 45597, 45598, 45599], shape=(25600,), dtype=int32)

    In [7]: f.qeScale[17612+2400:17612+2400+25600,0]
    Out[7]: array([0.886, 0.962, 1.029, 1.025, 0.978, ..., 0.981, 0.979, 1.009, 0.965, 0.979], shape=(25600,))


BINGO : ITS THE s_pmt::contiguousidx choice of CD_LPMT, SPMT, WP should be CD_PMT, WP, SPMT 


After fix the bug by distinguishing "oldcontigious" and "contiguous" in s_pmt.h::

    In [2]: t.get_s_qescale_from_spmtid
    Out[2]: 
    array([[0.886],
           [0.962],
           [1.029],
           [1.025],
           [0.978],
           [0.991],
           [0.989],
           [0.986],
           [0.983],
           [0.994],
           [0.971],
           [1.013],
           [0.986],
           [1.005],
           [0.96 ],
           [0.979],
           ...,
           [0.944],
           [1.027],
           [0.972],
           [0.958],
           [0.982],
           [0.985],
           [1.004],
           [0.996],
           [0.974],
           [0.985],
           [0.954],
           [0.981],
           [0.979],
           [1.009],
           [0.965],
           [0.979]], shape=(25600, 1), dtype=float32)











::

     032 PMTSimParamSvc::PMTSimParamSvc(const std::string& name)
      33     :
      34     SvcBase(name),
      35     m_all_pmtID(m_data.m_all_pmtID),
      36     m_all_pmtID_qe_scale(m_data.m_all_pmtID_qe_scale),
      37     m_db_path_SPMT(),


     47 struct PMTSimParamData
     48 {
     49     const char*                    loaddir ;
     50     std::vector<int>               m_all_pmtID;
     51     std::vector<double>            m_all_pmtID_qe_scale ;
     52     std::unordered_map<int, int>   m_map_pmt_category ; // NB not all, only LPMT
     53     std::unordered_map<int, int>   m_all_pmt_category ;
     54     std::vector<int>               m_all_pmt_catvec ;
     55 
     56     int                            m_PmtTotal_SPMT ;
     57     std::unordered_map<int, PmtSimData_SPMT> pd_map_SPMT;
     58 
     59     int                            m_PmtTotal ;  // _LPMT
     60     std::vector<PmtSimData_LPMT>   pd_vector;
     61 
     62     int                            m_PmtTotal_ALL ;
     63     int                            m_PmtTotal_WP ;
     64 




::

    In [1]: 0.249/1.099
    Out[1]: 0.22656960873521384


    In [8]: np.interp( 2.8178227113797455, p.s_qeshape[0, :-1,0], p.s_qeshape[0,:-1,1] )
    Out[8]: np.float64(0.2493061113567255)

    In [9]: np.interp( 2.8178227113797455, p.s_qeshape[0, :-1,0], p.s_qeshape[0,:-1,1] )/p.s_qescale[0,0]
    Out[9]: np.float64(0.22686855024623634)

    In [10]: np.interp( 2.8178227113797455, p.s_qeshape[0, :-1,0], p.s_qeshape[0,:-1,1] )*p.s_qescale[0,0]
    Out[10]: np.float64(0.2739627731228168)






    (ok) A[blyth@localhost qudarap]$ PIDX=0 cxs_min.sh run


    //qsim.propagate.body pidx       0 bounce 2 command 3 flag 0 s.optical.x 20 s.optical.y 2 
    //qsim.propagate.body.WITH_CUSTOM4 pidx       0  BOUNDARY ems 2 lposcost   0.555 
    //qsim.propagate_at_surface.BREAK.is_spmtid pidx       0 : pmtid 20000 energy_eV   2.818 qe_shape   0.249 qe_scale   1.099 qe   0.274 detect   1.000 absorb   0.000 reflect_specular   0.000 reflect_diffuse   0.000 
    //qsim.propagate_at_surface.SA/SD.BREAK pidx       0 : flag 16384 
    //qsim.propagate.tail pidx       0 bounce 2 command 1 flag 16384 ctx.s.optical.y(ems) 2 
    2025-06-24 14:56:12.962 INFO  [3250386] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7f6d2a000000
    2025-06-24 14:56:13.141 INFO  [3250386] [QSim::simulate@492]  eventID 0 tot_dt    0.005440 tot_ph     100000 tot_ph/M   0.100000 tot_ht      27296 tot_ht/M   0.027296 tot_ht/tot_ph   0.272960 reset_ YES
    2025-06-24 14:56:13.144 INFO  [3250386] [SEvt::save@4158] /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_s_pmt/A000 [genstep,photon,record,seq,hit,domain,inphoton]
    2025-06-24 14:56:14.240 INFO  [3250386] [QSim::simulate@507] 
    SEvt__MINTIME
     (TAIL - HEAD)/M   1.310225 (head to tail of QSim::simulate method) 
     (LEND - LBEG)/M   0.210318 (multilaunch loop begin to end) 
     (PCAT - LEND)/M   0.000030 (topfold concat and clear subfold) 
     (TAIL - BRES)/M   1.099342 (QSim::reset which saves hits) 
     tot_idt/M         0.005470 (sum of kernel execution int64_t stamp differences in microseconds)
     tot_dt            0.005440 int(tot_dt*M)         5439 (sum of kernel execution double chrono stamp differences in seconds, and scaled to ms) 
     tot_gdt/M         0.184147 (sum of SEvt::gather int64_t stamp differences in microseconds)

    2025-06-24 14:56:14.349  349822130 : ]/data1/blyth/local/opticks_Debug/bin/cxs_min.sh 
    (ok) A[blyth@localhost qudarap]$ 
    (ok) A[blyth@localhost qudarap]$ 
    (ok) A[blyth@localhost qudarap]$ 


After qe_scale oldcontiguous/contiguous bugfix  : get the expected qe_scale and qe
-----------------------------------------------------------------------------------------

::

    PIDX=0 cxs_min.sh run


    /qsim.propagate.body pidx       0 bounce 2 command 3 flag 0 s.optical.x 20 s.optical.y 2 
    //qsim.propagate.body.WITH_CUSTOM4 pidx       0  BOUNDARY ems 2 lposcost   0.555 
    //qsim.propagate_at_surface.BREAK.is_spmtid pidx       0 : pmtid 20000 energy_eV   2.818 qe_shape   0.249 qe_scale   0.886 qe   0.221 detect   1.000 absorb   0.000 reflect_specular   0.000 reflect_diffuse   0.000 
    //qsim.propagate_at_surface.SA/SD.BREAK pidx       0 : flag 16384 
    //qsim.propagate.tail pidx       0 bounce 2 command 1 flag 16384 ctx.s.optical.y(ems) 2 
    2025-06-24 17:35:58.982 INFO  [3282148] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7fb258000000







ipc EPH numbers
----------------

::

    jcv junoSD_PMT_v2


    BP=junoSD_PMT_v2::ProcessHits ipc
    BP=junoSD_PMT_v2::ProcessHits_ ipc


::

    2025-06-24 10:58:14.982 INFO  [3241588] [QSim::simulate@448]    0 : sslice {     0,     1,       0,  100000}
    2025-06-24 10:58:15.044 INFO  [3241588] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc
                                     ProcessHits_count   99845
                                      ProcessHits_true   21919
                                     ProcessHits_false   77926         # 21919 + 77926 = 99845
                                     SaveNormHit_count   21919
                                     SaveMuonHit_count       0

                                             EPH_UNSET       0
                                              EPH_NDIS       0
                                              EPH_NOPT       0
                                             EPH_NEDEP     610
                                            EPH_NBOUND     114
                                             EPH_NPROC       0
                                           EPH_NDETECT       0
                                           EPH_NDECULL   77202        # 77202 + 114 + 610 = 77926

                                            EPH_YMERGE       0
                                             EPH_YSAVE       0
                                          EPH_SAVENORM   21919
                                          EPH_SAVEMUON       0
                Initialize_G4HCofThisEvent_opticksMode       3
                      Initialize_G4HCofThisEvent_count       1
                           EndOfEvent_Simulate_eventID       0
                             EndOfEvent_Simulate_count       1
                          EndOfEvent_Simulate_EGPU_hit   27296
                     EndOfEvent_hitCollection_entries0   21919
                     EndOfEvent_hitCollection_entries1   21919
                  EndOfEvent_hitCollectionAlt_entries0       0
                  EndOfEvent_hitCollectionAlt_entries1   27296
                      EndOfEvent_Simulate_merged_count       0
                     EndOfEvent_Simulate_savehit_count   27296
                      EndOfEvent_Simulate_merged_total       0
                     EndOfEvent_Simulate_savehit_total   27296
    ]SProcessHits_EPH::desc

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 21919 hitCollectionAlt 27296 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0




    SABHit  a_nhit : (   27296 +-  165 )  b_nhit:(    21919 +-  148 )  a/b: (  1.245 +-  0.016 )  b/a: (  0.803 +-  0.010)  [assume uncorr.]


    In [3]: a.q_find("EC")
    Out[3]: array([    3,     7,    10,    14,    19, ..., 99974, 99975, 99978, 99981, 99999], shape=(27296,))

    In [4]: a.q_find("EX")
    Out[4]: array([    0,     1,     2,     4,     5, ..., 99994, 99995, 99996, 99997, 99998], shape=(71889,))

    In [9]: a.q_find_or_("EC,EX")
    Out[9]: array([    0,     1,     2,     3,     4, ..., 99995, 99996, 99997, 99998, 99999], shape=(99185,))




    In [5]: b.q_find("EC")
    Out[5]: array([    2,     3,     9,    12,    14, ..., 99976, 99981, 99987, 99994, 99996], shape=(21916,))
    ## slight difference of 3 compared to 21919 could be from truncation as hit decision made on flagmask not seq

    In [6]: b.q_find("EX")
    Out[6]: array([    0,     1,     4,     5,     6, ..., 99992, 99995, 99997, 99998, 99999], shape=(77202,))

    In [7]: b.q_find_or_("EC,EX")
    Out[7]: array([    0,     1,     2,     3,     4, ..., 99995, 99996, 99997, 99998, 99999], shape=(99118,))

    In [8]: 77202 + 21916
    Out[8]: 99118


Can view the difference as more culling (less collection) on the B side::

    In [10]: 77202/99118
    Out[10]: 0.7788898081075082   # B side cull fraction 

    In [12]: 1 - 0.7788898081075082
    Out[12]: 0.22111019189249181



    In [11]: 71889/99185
    Out[11]: 0.7247970963351313   # A side cull fraction

    In [13]: 1 - 0.7247970963351313
    Out[13]: 0.27520290366486866








    In [2]: a.qtab
    Out[2]:                # 27222 + 16 + 13 + 10 = 27261   .... the qtab selects the 10 most frequent so does not add up to total
    array([[b'71884', b'0', b'TO BT BT EX                                                                                     '],
           [b'27222', b'3', b'TO BT BT EC                                                                                     '],
           [b'456', b'25', b'TO AB                                                                                           '],
           [b'119', b'2121', b'TO BT BT AB                                                                                     '],
           [b'36', b'3833', b'TO BT AB                                                                                        '],
           [b'30', b'2867', b'TO BT BR BT BT BT AB                                                                            '],
           [b'16', b'5229', b'TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                       '],
           [b'13', b'8966', b'TO SC BT BT BT BT EC                                                                            '],
           [b'10', b'33607', b'TO BT BR BT BT BT BT BT BT BT BT BT EC                                                          '],
           [b'10', b'8104', b'TO BT BR BT BT BT BT BT BT BT BT BT SA                                                          ']], dtype='|S96')

    In [3]: b.qtab
    Out[3]: 
    array([[b'77187', b'0', b'TO BT BT EX                                                                                     '],
           [b'21843', b'2', b'TO BT BT EC                                                                                     '],
           [b'486', b'76', b'TO AB                                                                                           '],
           [b'110', b'261', b'TO BT BT AB                                                                                     '],
           [b'41', b'420', b'TO BT AB                                                                                        '],
           [b'38', b'6191', b'TO BT BR BT BT BT AB                                                                            '],
           [b'14', b'28955', b'TO SC BT BT BT BT EC                                                                            '],
           [b'14', b'7937', b'TO BT BR BT BT BT SC BT BT BT BT BT BT EC                                                       '],
           [b'12', b'9608', b'TO SC BT BT BT BT SA                                                                            '],
           [b'11', b'34936', b'TO BT BR BT BT BT SC BT BT BT BT BT BT SA                                                       ']], dtype='|S96')


    






OJ build
-----------

::

    [ 83%] Built target MuonWaveRec
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc: In member function 'std::string junoSD_PMT_v2_Opticks::descHit(unsigned int, const U4Hit*, const U4HitExtra*) const':
    /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:366:51: error: 'FlagMask' is not a member of 'OpticksPhoton'
      366 |         << " " << std::setw(20) << OpticksPhoton::FlagMask(hit->flag_mask, true)
          |                                                   ^~~~~~~~




Tub3inchPMTV3Manager photocathode_3inch
-----------------------------------------

::

    [blyth@localhost qudarap]$ jcv Tub3inchPMTV3Manager
    2 files to edit
    ./Simulation/DetSimV2/PMTSim/include/Tub3inchPMTV3Manager.hh
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc
    A[blyth@localhost junosw]$ jgr photocathode_3inch
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:    //photocathode_3inch
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:    G4Material* mat_photocathode_3inch = G4Material::GetMaterial("photocathode_3inch");
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:        G4MaterialPropertiesTable* tbl_PC3in = mat_photocathode_3inch->GetMaterialPropertiesTable();
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:    G4Material* Photocathode_mat_3inch = G4Material::GetMaterial("photocathode_3inch", any_warnings); 
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "photocathode_3inch is constructed from the GDML file" << G4endl;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "photocathode_3inch is constructed from the code" << G4endl;   
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        Photocathode_mat_3inch = new G4Material("photocathode_3inch",density,1);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        G4cout << "Setup photocathode_3inch Material Tables from MCParamsSvc" << G4endl;
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(PhotocathodeMPT_3inch, "RINDEX", mcgt.data(), "Material.photocathode_3inch.RINDEX");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(PhotocathodeMPT_3inch, "KINDEX", mcgt.data(), "Material.photocathode_3inch.KINDEX");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(PhotocathodeMPT_3inch, "REFLECTIVITY", mcgt.data(), "Material.photocathode_3inch.REFLECTIVITY");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(PhotocathodeMPT_3inch, "THICKNESS", mcgt.data(), "Material.photocathode_3inch.THICKNESS");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        bool st = mcgt->Get("Material.photocathode_3inch.scale", s_map);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:          helper_mpt(PhotocathodeMPT_3inch, "EFFICIENCY", mcgt.data(), "Material.photocathode_3inch.EFFICIENCY_v2");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        Photocathode_opsurf_3inch->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_3inch")->GetMaterialPropertiesTable() );
    ./Simulation/DetSimV2/PMTSim/src/Hello3inchPMTManager.cc:     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_3inch")->GetMaterialPropertiesTable() );
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTManager.cc:     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_3inch")->GetMaterialPropertiesTable() );
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV2Manager.cc:     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_3inch")->GetMaterialPropertiesTable() );
    ./Simulation/DetSimV2/PMTSim/src/Tub3inchPMTV3Manager.cc:     Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_3inch")->GetMaterialPropertiesTable() );
    A[blyth@localhost junosw]$ 








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


Need qpmt.h versions of the below for S_PMT "spmtid"->"spmtidx"::

     qe = m_PMTSimParsvc->get_pmtid_qe(pmtID,edep)
     ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());



where to do A side COLLECT/CULL ?
-------------------------------------

* within WITH_CUSTOM4 block of qsim.h

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






