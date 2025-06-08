efficiency_review
===================

Summary
-----------

Missing CE scaledown of hits. 


LSExpDetectorConstruction_Opticks::Setup gets PMT data from PMTParamData and PMTSimParamData that are serialized into jpmt
------------------------------------------------------------------------------------------------------------------------------

::

     21 void LSExpDetectorConstruction_Opticks::Setup(
     22           int opticksMode,
     23           const G4VPhysicalVolume* world,
     24           const G4VSensitiveDetector* sd,
     25           PMTParamData* ppd,
     26           PMTSimParamData* psd,
     27           NPFold* pmtscan
     28           )
     29 {
     30     SEventConfig::SetIntegrationMode(opticksMode);
     31     int integrationMode = SEventConfig::IntegrationMode();
     32     bool opticksMode_valid =
     33          ( opticksMode == 0 || opticksMode == 1 || opticksMode == 2 || opticksMode == 3 )  && opticksMode == integrationMode ;
     34     LOG_IF(fatal, !opticksMode_valid )
     35         << " UNEXPECTED "
     36         << " opticksMode " << opticksMode
     37         << " integrationMode " << integrationMode
     38         ;
     39     assert( opticksMode_valid );
     40 
     41     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     42     const NP* jlut = SerializeMultiFilmLUT();
     43     assert(jlut);
     44 
     45     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     46 
     47     G4CXOpticks::SetGeometry_JUNO(world, sd, jpmt, jlut );
     48 
     49     LOG(info) << "] WITH_G4CXOPTICKS " ;
     50     DebugMultiFilmTable();
     51 }



A side
---------

qsim.h propagate::

    2242         }
    2243         else if( ems == smatsur_Surface_zplus_sensor_CustomART )
    2244         {
    2245 #if defined(WITH_CUSTOM4)
    2246             command = propagate_at_surface_CustomART( flag, rng, ctx ) ;
    2247             //command = base->custom_lut == 0u ? propagate_at_surface_CustomART( flag, rng, ctx ) : propagate_at_surface_MultiFilm(flag, rng, ctx );
    2248 
    2249 #endif
    2250         }
    2251     }
    2252     ctx.p.set_flag(flag);


    1742 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, RNG& rng, sctx& ctx) const
    1743 {
    1744 
    1745     const sphoton& p = ctx.p ;
    1746     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal
    1747     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor
    1748     //int lpmtid = p.identity ;
    1749 

    1785     float ARTE[4] = {} ;
    1786     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ARTE(ARTE, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm );


    1795     const float& theAbsorption = ARTE[0];
    1796     //const float& theReflectivity = ARTE[1];
    1797     const float& theTransmittance = ARTE[2];
    1798     const float& theEfficiency = ARTE[3];
    1799 
    1800     float u_theAbsorption = curand_uniform(&rng);
    1801     int action = u_theAbsorption < theAbsorption  ? BREAK : CONTINUE ;
    ....
    1810     if( action == BREAK )
    1811     {
    1812         float u_theEfficiency = curand_uniform(&rng) ;
    1813         flag = u_theEfficiency < theEfficiency ? SURFACE_DETECT : SURFACE_ABSORB ;
    1814 


qpmt.h::

    304 template<typename F>
    305 inline QPMT_METHOD void qpmt<F>::get_lpmtid_ARTE(
    306     F* arte4,
    307     int lpmtid,
    308     F wavelength_nm,
    309     F minus_cos_theta,
    310     F dot_pol_cross_mom_nrm ) const
    311 {
    312     const F energy_eV = hc_eVnm/wavelength_nm ;
    313 
    314     F spec[16] ;
    315     get_lpmtid_stackspec( spec, lpmtid, energy_eV );
    316 
    317     const F* ss = spec ;
    318     const F& _qe = spec[15] ;
    319 
    320 #ifdef MOCK_CURAND_DEBUG
    321     printf("//qpmt::get_lpmtid_ARTE lpmtid %d energy_eV %7.3f _qe %7.3f \n", lpmtid, energy_eV, _qe );
    322 #endif
    323 
    324 
    325     Stack<F,4> stack ;
    326 
    327     if( minus_cos_theta < zero )
    328     {
    329         stack.calc(wavelength_nm, -one, zero, ss, 16u );
    330         arte4[3] = _qe/stack.art.A ;
    331 
    332 #ifdef MOCK_CURAND_DEBUG
    333         printf("//qpmt::get_lpmtid_ARTE stack.art.A %7.3f _qe/stack.art.A %7.3f \n", stack.art.A, arte4[3] );
    334 #endif
    335     }
    336     else
    337     {
    338         arte4[3] = zero ;
    339     }
    340 
    341     stack.calc(wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, ss, 16u );
    342 
    343     const F& A = stack.art.A ;
    344     const F& R = stack.art.R ;
    345     const F& T = stack.art.T ;



    156 template<typename F>
    157 inline QPMT_METHOD void qpmt<F>::get_lpmtid_stackspec( F* spec, int lpmtid, F energy_eV ) const
    158 {
    159     const int& lpmtcat = i_lcqs[lpmtid*2+0] ;
    160     // printf("//qpmt::get_lpmtid_stackspec lpmtid %d lpmtcat %d \n", lpmtid, lpmtcat );
    161 
    162     const F& qe_scale = lcqs[lpmtid*2+1] ;
    163     const F qe_shape = qeshape_prop->interpolate( lpmtcat, energy_eV ) ;
    164     const F qe = qe_scale*qe_shape ;
    165 
    166     spec[0*4+3] = lpmtcat ;
    167     spec[1*4+3] = qe_scale ;
    168     spec[2*4+3] = qe_shape ;
    169     spec[3*4+3] = qe ;
    170 
    171     get_lpmtcat_stackspec( spec, lpmtcat, energy_eV );
    172 }

QPMT.cc::

    130 template<typename T>
    131 inline void QPMT<T>::init_lcqs()
    132 {
    133     LOG(LEVEL)
    134        << " src_lcqs " << ( src_lcqs ? src_lcqs->sstr() : "-" )
    135        << " lcqs " << ( lcqs ? lcqs->sstr() : "-" )
    136        ;
    137 
    138     const char* label = "QPMT::init_lcqs/d_lcqs" ;
    139 
    140 #if defined(MOCK_CURAND) || defined(MOCK_CUDA)
    141     T* d_lcqs = lcqs ? const_cast<T*>(lcqs->cvalues<T>()) : nullptr ;
    142 #else
    143     T* d_lcqs = lcqs ? QU::UploadArray<T>(lcqs->cvalues<T>(), lcqs->num_values(), label) : nullptr ;
    144 #endif
    145 
    146     pmt->lcqs = d_lcqs ;
    147     pmt->i_lcqs = (int*)d_lcqs ;   // HMM: would cause issues with T=double  
    148 }
    149 


    102 template<typename T>
    103 inline QPMT<T>::QPMT(const NPFold* jpmt )
    104     :
    105     ExecutableName(sproc::ExecutableName()),
    106     src_rindex(   jpmt->get("rindex")),
    107     src_thickness(jpmt->get("thickness")),
    108     src_qeshape(  jpmt->get("qeshape")),
    109     src_lcqs(     jpmt->get_optional("lcqs")),
    110     rindex3(  NP::MakeCopy3D(src_rindex)),   // make copy and change shape to 3D
    111     rindex(   NP::MakeWithType<T>(rindex3)), // adopt template type, potentially narrowing
    112     rindex_prop(new QProp<T>(rindex)),
    113     qeshape(   NP::MakeWithType<T>(src_qeshape)), // adopt template type, potentially narrowing
    114     qeshape_prop(new QProp<T>(qeshape)),
    115     thickness(NP::MakeWithType<T>(src_thickness)),
    116     lcqs(src_lcqs ? NP::MakeWithType<T>(src_lcqs) : nullptr),
    117     i_lcqs( lcqs ? (int*)lcqs->cvalues<T>() : nullptr ),    // CPU side lookup lpmtid->lpmtcat 0/1/2
    118     pmt(new qpmt<T>()),                    // host-side qpmt.h instance 
    119     d_pmt(nullptr)                         // device-side pointer set at upload in init
    120 {
    121     init();
    122 }


QSim.cc::

     187     const NPFold* spmt_f = ssim->get_spmt_f() ;
     188     QPMT<float>* qpmt = spmt_f ? new QPMT<float>(spmt_f) : nullptr ;



     321 const NPFold* SSim::get_jpmt_nocopy() const
     322 {
     323 
     324     NPFold* f = top ? top->find_subfold_(JPMT_RELP) : nullptr ;     // extra/jpmt
     325     //if(f) f->set_verbose_r();
     326     LOG(LEVEL)
     327         << " (NPFold)top " << ( top ? "YES" : "NO " )
     328         << " (NPFold)f " << ( f ? "YES" : "NO " )
     329         ;
     330     return f ;
     331 }
     332 
     333 const NPFold* SSim::get_jpmt() const
     334 {
     335     const NPFold* f = get_jpmt_nocopy();
     336     const NPFold* fc  = f ? f->deepcopy() : nullptr ;
     337 
     338     LOG(LEVEL)
     339         << " (NPFold)f " << ( f ? "YES" : "NO " )
     340         << " (NPFold)fc " << ( fc ? "YES" : "NO " )
     341         ;
     342 
     343     return fc ;
     344 }
     345 const SPMT* SSim::get_spmt() const
     346 {
     347     const NPFold* jpmt = get_jpmt();
     348     const SPMT* spmt = jpmt ? new SPMT(jpmt) : nullptr ;
     349 
     350     LOG(LEVEL)
     351         << " (NPFold)jpmt " << ( jpmt ? "YES" : "NO " )
     352         << " (SPMT)spmt " << ( spmt ? "YES" : "NO " )
     353         ;
     354 
     355     return spmt ;
     356 }

     358 /**
     359 SSim::get_spmt_f
     360 ------------------
     361 
     362 This is invoked from QSim::UploadComponents and
     363 used to instanciate QPMT for GPU uploading.
     364 
     365 **/
     366 
     367 
     368 const NPFold* SSim::get_spmt_f() const
     369 {
     370     const SPMT* spmt = get_spmt() ;
     371     const NPFold* spmt_f = spmt ? spmt->serialize() : nullptr ;
     372 
     373     LOG(LEVEL)
     374         << " (SPMT)spmt " << ( spmt ? "YES" : "NO " )
     375         << " (NPFold)spmt_f " << ( spmt_f ? "YES" : "NO " )
     376         ;
     377 
     378     return spmt_f ;
     379 }
     380 



     002 /**
       3 SPMT.h : summarize PMTSimParamData NPFold into the few arrays needed on GPU
       4 ============================================================================
       5 
       6 Usage sketch
       7 -------------
       8 
       9 ::
      10 
      11     SSim::get_spmt
      12     QSim::UploadComponents
      13     QPMT
      14     qpmt
      15 





     478 inline void SPMT::init_lcqs()
     479 {
     480     if( PMTSimParamData == nullptr )
     481     {
     482         std::cout << "SPMT::init_lcqs exit as PMTSimParamData is NULL\n" ;
     483         return ;
     484     }
     485     assert( PMTSimParamData );
     486     const NP* lpmtCat = PMTSimParamData->get("lpmtCat") ;
     487     assert( lpmtCat && lpmtCat->uifc == 'i' && lpmtCat->ebyte == 4 );
     488     assert( lpmtCat->shape[0] == NUM_LPMT );
     489     const int* lpmtCat_v = lpmtCat->cvalues<int>();
     490 
     491     const NP* qeScale = PMTSimParamData->get("qeScale") ;
     492     assert( qeScale && qeScale->uifc == 'f' && qeScale->ebyte == 8 );
     493     assert( qeScale->shape[0] >= NUM_LPMT );  // SPMT, WPMT info after LPMT
     494     const double* qeScale_v = qeScale->cvalues<double>();
     495 
     496     for(int i=0 ; i < NUM_LPMT ; i++ )
     497     {
     498         v_lcqs[i] = { TranslateCat(lpmtCat_v[i]), float(qeScale_v[i]) } ;
     499     }
     500     lcqs = NPX::ArrayFromVec<int,LCQS>( v_lcqs ) ;
     501 
     502     if(VERBOSE) std::cout
     503        << "SPMT::init_lcqs" << std::endl
     504        << " NUM_LPMT " << NUM_LPMT << std::endl
     505        << " lpmtCat " << ( lpmtCat ? lpmtCat->sstr() : "-" ) << std::endl
     506        << " qeScale " << ( qeScale ? qeScale->sstr() : "-" ) << std::endl
     507        << " lcqs " << ( lcqs ? lcqs->sstr() : "-" ) << std::endl
     508        ;
     509 
     510     assert( lcqs->shape[0] == NUM_LPMT );
     511     assert( NUM_LPMT == 17612 );
     512 }
     513 


::

    (ok) A[blyth@localhost PMTSimParamData]$ pwd
    /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/Sun/.opticks/GEOM/J25_3_0_Opticks_v0_4_3/CSGFoundry/SSim/extra/jpmt/PMTSimParamData


    In [3]: qs = np.load("qeScale.npy")

    In [4]: qs
    Out[4]: 
    array([[1.02534437],
           [1.25485868],
           [1.23812617],
           ...,
           [1.00907365],
           [0.96539813],
           [0.97932776]], shape=(45612, 1))

    In [5]: qs.shape
    Out[5]: (45612, 1)

    In [6]: lc = np.load("lpmtCat.npy")

    In [7]: lc
    Out[7]: 
    array([[1],
           [0],
           [1],
           ...,
           [0],
           [0],
           [0]], shape=(17612, 1), dtype=int32)

    In [8]: lc[:,0]
    Out[8]: array([1, 0, 1, ..., 0, 0, 0], shape=(17612,), dtype=int32)

    In [9]: np.unique(lc[:,0], return_counts=True)
    Out[9]: (array([0, 1], dtype=int32), array([12673,  4939]))

    In [10]: np.c_[np.unique(lc[:,0], return_counts=True)]
    Out[10]: 
    array([[    0, 12673],
           [    1,  4939]])

    In [11]: tab = np.c_[np.unique(lc[:,0], return_counts=True)]

    In [12]: tab[:,1]
    Out[12]: array([12673,  4939])

    In [13]: tab[:,1].sum()
    Out[13]: np.int64(17612)




Big difference : NNVT and NNVT-hi-qe are being lumped together ?
------------------------------------------------------------------

::

     514 /**
     515 SPMT::TranslateCat : 0,1,3 => 0,1,2
     516 --------------------------------------
     517 
     518 ::
     519 
     520     In [10]: np.c_[np.unique( t.lpmtCat[:,0], return_counts=True )]
     521     Out[10]:
     522     array([[   0, 2720],
     523            [   1, 4997],
     524            [   3, 9895]])
     525 
     526 
     527     In [4]: t.lcqs[:,0]
     528     Out[4]: array([1, 1, 2, 1, 2, ..., 1, 1, 1, 1, 1], dtype=int32)
     529 
     530     In [5]: np.unique(t.lcqs[:,0], return_counts=True)
     531     Out[5]: (array([0, 1, 2], dtype=int32), array([2720, 4997, 9895]))
     532 







Potential for enum value changes from JUNOSW to cause problem here::

     514 /**
     515 SPMT::TranslateCat : 0,1,3 => 0,1,2
     516 --------------------------------------
     517 
     518 ::
     519 
     520     In [10]: np.c_[np.unique( t.lpmtCat[:,0], return_counts=True )]
     521     Out[10]:
     522     array([[   0, 2720],
     523            [   1, 4997],
     524            [   3, 9895]])
     525 
     526 
     527     In [4]: t.lcqs[:,0]
     528     Out[4]: array([1, 1, 2, 1, 2, ..., 1, 1, 1, 1, 1], dtype=int32)
     529 
     530     In [5]: np.unique(t.lcqs[:,0], return_counts=True)
     531     Out[5]: (array([0, 1, 2], dtype=int32), array([2720, 4997, 9895]))
     532 
     533 
     534 **/
     535 
     536 inline int SPMT::TranslateCat(int lpmtcat) // static
     537 {
     538     int lcat = -1 ;
     539     switch( lpmtcat )
     540     {
     541         case -1: lcat = -99  ; break ;   // kPMT_Unknown     see "jcv PMTCategory"
     542         case  0: lcat =  0   ; break ;   // kPMT_NNVT
     543         case  1: lcat =  1   ; break ;   // kPMT_Hamamatsu
     544         case  2: lcat =  -99 ; break ;   // kPMT_HZC
     545         case  3: lcat =  2   ; break ;   // kPMT_NNVT_HighQE
     546         default: lcat = -99  ; break ;
     547     }
     548     assert( lcat >= 0 );
     549     return lcat ;
     550 }













::

    A[blyth@localhost extra]$ cd jpmt/
    A[blyth@localhost jpmt]$ l
    total 8
    0 -rw-r--r--. 1 blyth blyth    0 Apr  1 11:40 NPFold_names.txt
    4 -rw-r--r--. 1 blyth blyth   40 Apr  1 11:40 NPFold_index.txt
    0 drwxr-xr-x. 5 blyth blyth  115 Mar 24 16:39 .
    0 drwxr-xr-x. 3 blyth blyth  140 Mar 24 16:39 ..
    0 drwxr-xr-x. 2 blyth blyth  101 Mar 24 16:39 PMT_RINDEX
    4 drwxr-xr-x. 5 blyth blyth 4096 Mar 24 16:39 PMTSimParamData
    0 drwxr-xr-x. 2 blyth blyth   72 Mar 24 16:39 PMTParamData
    A[blyth@localhost jpmt]$ l PMTParamData/
    total 364
      4 -rw-r--r--. 1 blyth blyth     11 Apr  1 11:40 NPFold_index.txt
      0 -rw-r--r--. 1 blyth blyth      0 Apr  1 11:40 NPFold_names.txt
    360 -rw-r--r--. 1 blyth blyth 365024 Apr  1 11:40 pmtCat.npy
      0 drwxr-xr-x. 5 blyth blyth    115 Mar 24 16:39 ..
      0 drwxr-xr-x. 2 blyth blyth     72 Mar 24 16:39 .
    A[blyth@localhost jpmt]$ l PMTSimParamData/
    total 4596
       0 -rw-r--r--. 1 blyth blyth       0 Apr  1 11:40 NPFold_names.txt
    1408 -rw-r--r--. 1 blyth blyth 1440992 Apr  1 11:40 lpmtData.npy
       4 -rw-r--r--. 1 blyth blyth     131 Apr  1 11:40 NPFold_index.txt
       4 -rw-r--r--. 1 blyth blyth      48 Apr  1 11:40 pmtTotal_names.txt
       4 -rw-r--r--. 1 blyth blyth     144 Apr  1 11:40 pmtTotal.npy
       4 -rw-r--r--. 1 blyth blyth      73 Apr  1 11:40 spmtData_meta.txt
    2004 -rw-r--r--. 1 blyth blyth 2048128 Apr  1 11:40 spmtData.npy
       4 -rw-r--r--. 1 blyth blyth      69 Apr  1 11:40 lpmtCat_meta.txt
      72 -rw-r--r--. 1 blyth blyth   70576 Apr  1 11:40 lpmtCat.npy
       4 -rw-r--r--. 1 blyth blyth      64 Apr  1 11:40 pmtCatName_names.txt
       4 -rw-r--r--. 1 blyth blyth     148 Apr  1 11:40 pmtCatName.npy
     360 -rw-r--r--. 1 blyth blyth  365024 Apr  1 11:40 pmtCat.npy
     180 -rw-r--r--. 1 blyth blyth  182576 Apr  1 11:40 pmtCatVec.npy
     180 -rw-r--r--. 1 blyth blyth  182576 Apr  1 11:40 pmtID.npy
     360 -rw-r--r--. 1 blyth blyth  365024 Apr  1 11:40 qeScale.npy
       4 drwxr-xr-x. 5 blyth blyth    4096 Mar 24 16:39 .
       0 drwxr-xr-x. 5 blyth blyth     115 Mar 24 16:39 ..
       0 drwxr-xr-x. 2 blyth blyth     162 Mar 24 16:39 CONST
       0 drwxr-xr-x. 5 blyth blyth      87 Mar 24 16:39 MPT
       0 drwxr-xr-x. 2 blyth blyth     182 Mar 24 16:39 QEshape
    A[blyth@localhost jpmt]$ pwd
    /home/blyth/.opticks/GEOM/J_2025_mar24/CSGFoundry/SSim/extra/jpmt
    A[blyth@localhost jpmt]$ 


::

    215 inline NPFold* _PMTSimParamData::serialize() const
    216 {
    217     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    218     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;
    219     NP* lpmtCat = NPX::ArrayFromMapUnordered<int, int>(data.m_map_pmt_category) ;
    220     NP* pmtCat = NPX::ArrayFromDiscoMapUnordered<int>(data.m_all_pmt_category) ;
    221     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;
    222 
    223     NP* spmtData = NPX::ArrayFromMapUnordered<double, PmtSimData_SPMT>(data.pd_map_SPMT) ;
    224     NP* lpmtData = NPX::ArrayFromVec<double, PmtSimData_LPMT>(data.pd_vector) ;
    225     NP* pmtTotal = serialize_pmtTotal();
    226 
    227     NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT);
    228     NPFold* CONST = NPFold::Serialize_MIMSD(data.m_PMT_CONST);
    229     NPFold* QEshape = serialize_QEshape() ;


::

     619 bool PMTSimParamSvc::init_PMTParamSvc()
     620 {
     621     int num_lpmt = m_PMTParamSvc->get_NTotal_CD_LPMT() ;
     622     for(int i = 0 ; i < num_lpmt ; i++)
     623     {
     624         int pmtid = kOFFSET_CD_LPMT + i ;
     625         int cat = m_PMTParamSvc->getPMTCategory(pmtid) ;
     626         m_map_pmt_category[i] = cat ;
     627     }
     628 
     629     m_PmtTotal_WP = m_PMTParamSvc->get_NTotal_WP_LPMT() ;
     630 
     631 
     632    return true;
     633 
     634 }


Add branch : blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc
------------------------------------------------------------------

::


    jcv _PMTSimParamData
    jcv PMTSimParamData
    jcv PMTSimParamSvc


    (ok) A[blyth@localhost junosw]$ git s
    On branch blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc
    Your branch is up to date with 'origin/blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h


    (ok) A[blyth@localhost junosw]$ git commit -m "collect CE theta mpv into PMTSimParamData.h and add to serialization _PMTSimParamData.h "
    [blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc 82be1b48] collect CE theta mpv into PMTSimParamData.h and add to serialization _PMTSimParamData.h
     4 files changed, 144 insertions(+), 23 deletions(-)
    (ok) A[blyth@localhost junosw]$ git push 
    Enumerating objects: 19, done.
    Counting objects: 100% (19/19), done.
    Delta compression using up to 56 threads
    Compressing objects: 100% (11/11), done.
    Writing objects: 100% (11/11), 4.75 KiB | 4.75 MiB/s, done.
    Total 11 (delta 6), reused 0 (delta 0), pack-reused 0
    remote: 
    remote: To create a merge request for blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc
    remote: 
    To code.ihep.ac.cn:JUNO/offline/junosw.git
       ada95832..82be1b48  blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc -> blyth-add-CE-theta-to-PMTSimParamData-PMTSimParamSvc
    (ok) A[blyth@localhost junosw]$ 





Check persisted CSGFoundry/SSim/extra/jpmt/PMTSimParamData/CEtheta
-------------------------------------------------------------------

::

    A[blyth@localhost CEtheta]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt/PMTSimParamData/CEtheta

    A[blyth@localhost CEtheta]$ t f
    f () 
    { 
        PYTHONPATH=$HOME ~/np/f.sh
    }
    A[blyth@localhost CEtheta]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: Use the IPython.lib.demo.Demo class to load any Python script as an interactive demo.
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.CE_R12860                                        :               (9, 2) : 0:10:05.341821 
      : f.CE_NNVTMCP                                       :               (9, 2) : 0:10:05.341821 
      : f.CE_NNVTMCP_HiQE                                  :               (9, 2) : 0:10:05.341821 
      : f.CE_WP_PMT                                        :               (9, 2) : 0:10:05.341821 
      : f.NPFold_index                                     :                 (4,) : 0:10:05.341821 
      : f.NPFold_names                                     :                 (0,) : 0:10:05.341821 

     min_stamp : 2025-06-07 18:21:46.340147 
     max_stamp : 2025-06-07 18:21:46.340147 
     dif_stamp : 0:00:00 
     age_stamp : 0:10:05.341821 

    In [1]: f.CE_R12860
    Out[1]: 
    array([[0.   , 0.911],
           [0.227, 0.911],
           [0.489, 0.922],
           [0.716, 0.929],
           [0.96 , 0.923],
           [1.152, 0.93 ],
           [1.379, 0.909],
           [1.484, 0.626],
           [1.571, 0.273]])

    In [2]: f.CE_NNVTMCP
    Out[2]: 
    array([[0.   , 1.   ],
           [0.244, 1.   ],
           [0.524, 0.945],
           [0.742, 0.91 ],
           [0.96 , 0.893],
           [1.169, 0.925],
           [1.353, 0.927],
           [1.484, 0.884],
           [1.571, 0.734]])

    In [3]: f.CE_NNVTMCP_HiQE
    Out[3]: 
    array([[0.   , 1.   ],
           [0.244, 1.   ],
           [0.524, 0.977],
           [0.742, 0.972],
           [0.96 , 0.97 ],
           [1.169, 0.97 ],
           [1.353, 0.945],
           [1.484, 0.91 ],
           [1.571, 0.734]])

    In [4]: f.CE_WP_PMT
    Out[4]: 
    array([[0.   , 1.   ],
           [0.244, 1.   ],
           [0.524, 0.945],
           [0.742, 0.91 ],
           [0.96 , 0.893],
           [1.169, 0.925],
           [1.353, 0.927],
           [1.484, 0.884],
           [1.571, 0.734]])

    In [5]: 





B side hit culling
--------------------

::

     jcv junoSD_PMT_v2


     335 #ifdef WITH_G4CXOPTICKS_DEBUG
     336 G4bool junoSD_PMT_v2::ProcessHits_(G4Step * step,G4TouchableHistory*)
     337 #else
     338 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     339 #endif
     340 {
     341     if (m_disable) {
     342 #ifdef WITH_G4CXOPTICKS_DEBUG
     343         m_eph = EPH::NDIS ;
     344 #endif
     345         return false;
     346     }
     347 
     348     // TODO: now it only support the single PE.
     349     // = only accept the optical photon
     350     G4Track* track = step->GetTrack();
     351     if (track->GetDefinition() != G4OpticalPhoton::Definition()) {
     352 #ifdef WITH_G4CXOPTICKS_DEBUG
     353         m_eph = EPH::NOPT ;
     354 #endif
     355         return false;
     356     }
     357 
     ...
     422     double qe = 1;
     423     double ce = 1;
     424     // == get the copy number -> pmt id
     425     int pmtID = get_pmtid(track);
     426     // = final DE = QE * CE, 
     427     // but QE is already applied (this is old implementation,
     428     // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
     429     // = DE: Detection Efficiency

     430     if(m_use_pmtsimsvc){

     431         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);

     432         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());

     433      }
     434      else{
     435         std::string volname = track->GetVolume()->GetName();
     436     GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     437      }
     438 
     439     double f_angle_response = 1.0;
     440     double de = qe*ce*f_angle_response ;
     441     if (de>1.0){
     442         std::cout<<"junoSD_PMT_v2:: de is larger than 1.0"<<std::endl;
     443     }
     444     bool de_cull = G4UniformRand() > de ;
     ... 
     470     if (de_cull) {
     471 #ifdef WITH_G4CXOPTICKS_DEBUG
     472         m_eph = EPH::NDECULL ;
     473 #endif
     474         return false;
     475     }
     480     double hittime = postStepPoint->GetGlobalTime();
     491     if (m_pmthitmerger and m_pmthitmerger->getMergeFlag()) {
     495         bool ok = m_pmthitmerger->doMerge(pmtID, hittime);
     496         if (ok) {
     497             m_merge_count += 1 ;
     498 
     499 #ifdef WITH_G4CXOPTICKS_DEBUG
     500             m_eph = EPH::YMERGE ;
     501 #endif
     502             return true;
     503         }
     504     }
     507     if (m_hit_type == 1) {
     508         SaveNormHit(pmtID, local_pos, global_pos, hittime, track, edep);
     509     } else if (m_hit_type == 2) {
     510         SaveMuonHit(pmtID, local_pos, hittime);
     511     }
     512     return true;
     513 }



BP=PMTSimParamSvc::get_pmtid_ce

::

    1134 double PMTSimParamSvc::get_pmtid_ce(int pmtid , double theta) const
    1135 {
    1136      int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    1137      double ce = get_pmtcat_ce(pmtcat,theta);
    1138      assert( ce > 0 );
    1139      return  ce ;
    1140 
    1141 }

    1143 double PMTSimParamSvc::get_pmtcat_ce(int pmtcat, double theta) const
    1144 {
    1145 
    1146   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1147   double ce = -1;
    1148   G4MaterialPropertyVector * vec = 0 ;
    1149   switch(pmtcat)
    1150     {   //FIXME:KPMT_Unknown represent WP pmt,which are use normal NNVTMCP ?
    1151         case kPMT_Unknown:     { vec = m_CE_WP_PMT ; } ; break ;
    1152         case kPMT_NNVT:        { vec = m_CE_NNVTMCP ; } ; break ;
    1153         case kPMT_Hamamatsu:   { vec = m_CE_R12860 ; } ; break ;
    1154         case kPMT_HZC:         { ce = 1.0 ; } ; return ce ;
    1155         case kPMT_NNVT_HighQE: { vec = m_CE_NNVTMCP_HiQE ; } ; break ;
    1156     }
    1157 
    1158   if(vec){
    1159         //vec -> SetSpline(false);  that is default 
    1160         ce = vec->Value(theta);
    1161   }
    1162 
    1163   //double CE = ce >= 1 ? 1 : ce ;  
    1164   assert(ce > 0 && ce <= 1 );
    1165   return ce;
    1166 }



SMOKING GUN, CE NOT COLLECTED INTO PMTSimParamData
----------------------------------------------------

::

    218  // G4MaterialPropertyVector* m_Amp_MCP;
    219   G4MaterialPropertyVector* m_CE_Dynode;
    220   G4MaterialPropertyVector* m_CE_MCP;
    221   G4MaterialPropertyVector* m_CE_R12860;
    222   G4MaterialPropertyVector* m_CE_NNVTMCP;//means normal nnvt
    223   G4MaterialPropertyVector* m_CE_NNVTMCP_HiQE;
    224   G4MaterialPropertyVector* m_CE_WP_PMT;
    225 
    226 //the shape of qe curve of PMT
    227 private:  
    228   G4MaterialPropertyVector*& m_QEshape_HZC;
    229   G4MaterialPropertyVector*& m_QEshape_NNVT;//means normal
    230   G4MaterialPropertyVector*& m_QEshape_NNVT_HiQE;
    231   G4MaterialPropertyVector*& m_QEshape_R12860;
    232   G4MaterialPropertyVector*& m_QEshape_WP_PMT;
    233 



PMTSimParamSvc
---------------

::

     78         void setPMTParamSvc(IPMTParamSvc* para){ m_PMTParamsvc=para; }
     79         void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }
     80 
     81         IPMTParamSvc*     getPMTParamSvc() const { return m_PMTParamsvc ; }
     82         IPMTSimParamSvc* getPMTSimParamSvc() const { return m_PMTSimParsvc ; }


    ok) A[blyth@localhost junosw]$ jgr setPMTSimParamSvc
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }
    grep: ./Simulation/DetSimV2/PMTSim/include/.junoSD_PMT_v2.hh.swp: binary file matches
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    (ok) A[blyth@localhost junosw]$ 



C4OpBoundaryProcess
-----------------------

::

    (ok) A[blyth@localhost junosw]$ jgr C4OpBoundaryProcess
    ./Doc/oum/source/releasenotes/J23.1.md:  * Fix issue #88 , PMT Geometry pivot, Transition from FastSim to Custom Boundary Process C4OpBoundaryProcess. See MR !180, done by Simon Blyth.
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:               |   at photocathode)            |                                   |  now C4OpBoundaryProcess      |
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:               |   rindex layers)              | (boundary not run)                | C4OpBoundaryProcess           |
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:the customization of the C4OpBoundaryProcess only for 
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:See C4OpBoundaryProcess::PostStepDoIt  
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:    without any special prefix char, C4OpBoundaryProcess behaves standardly 
    ./Simulation/DetSimV2/PMTSim/include/CommonPMTManager.h:behavior is overridden by the C4OpBoundaryProcess handling. 
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#include "C4OpBoundaryProcess.hh"
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    static G4ThreadLocal C4OpBoundaryProcess* boundary_proc = GetOpBoundaryProcess<C4OpBoundaryProcess>() ; 
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h:class C4OpBoundaryProcess ;
    ./Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h:    C4OpBoundaryProcess* CreateCustomG4OpBoundaryProcess(); 
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#include "C4OpBoundaryProcess.hh"
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    C4OpBoundaryProcess* boundproc = CreateCustomG4OpBoundaryProcess();
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ; 
    (ok) A[blyth@localhost junosw]$ 



    383 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    384 {
    385     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    386 
    387     if(psps_ptr.invalid())
    388     {
    389         std::cout << "invalid" << std::endl ;
    390         return nullptr ;
    391     }
    392 
    393     IPMTSimParamSvc* ipsps = psps_ptr.data();
    394     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    395 
    396     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    397     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    398     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    399 
    400     return boundproc ;
    401 }




    205 
    206 inline int PMTAccessor::get_num_lpmt() const
    207 {
    208     return data->get_num_lpmt() ;
    209 }
    210 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    211 {
    212     return data->get_pmtid_qe(pmtid, energy) ;
    213 }
    214 inline double PMTAccessor::get_qescale( int pmtid ) const
    215 {
    216     return data->get_qescale(pmtid) ;
    217 }
    218 
    219 inline int PMTAccessor::get_pmtcat( int pmtid  ) const
    220 {
    221     return data->get_pmtcat(pmtid) ;
    222 }
    223 inline void PMTAccessor::get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const
    224 {
    225     double energy = energy_eV*CLHEP::eV ;
    226 
    227     ss.fill(0.);
    228 
    229     ss[4*0+0] = PyrexRINDEX ? PyrexRINDEX->Value(energy) : 0. ;
    230 
    231     ss[4*1+0] = data->get_pmtcat_prop(       pmtcat, "ARC_RINDEX" , energy );
    232     ss[4*1+1] = data->get_pmtcat_prop(       pmtcat, "ARC_KINDEX" , energy );
    233     ss[4*1+2] = data->get_pmtcat_const_prop( pmtcat, "ARC_THICKNESS" )/CLHEP::nm ;
    234 
    235     ss[4*2+0] = data->get_pmtcat_prop(       pmtcat, "PHC_RINDEX" , energy );
    236     ss[4*2+1] = data->get_pmtcat_prop(       pmtcat, "PHC_KINDEX" , energy );
    237     ss[4*2+2] = data->get_pmtcat_const_prop( pmtcat, "PHC_THICKNESS" )/CLHEP::nm ;
    238 
    239     ss[4*3+0] = VacuumRINDEX ? VacuumRINDEX->Value(energy) : 1. ;
    240 }
    241 
    242 inline const char* PMTAccessor::get_typename() const
    243 {
    244     return TypeName ;
    245 }
    246 

::

     119 C4OpBoundaryProcess::C4OpBoundaryProcess(
     120                                                const C4IPMTAccessor* accessor,
     121                                                const G4String& processName,
     122                                                G4ProcessType type)
     123              :
     124              G4VDiscreteProcess(processName, type),
     125              m_custom_status('U'),
     126              m_custom_art(new C4CustomART(
     127                                         accessor,
     128                                         theAbsorption,
     129                                         theReflectivity,
     130                                         theTransmittance,
     131                                         theEfficiency,
     132                                         theGlobalPoint,
     133                                         OldMomentum,
     134                                         OldPolarization,
     135                                         theRecoveredNormal,
     136                                         thePhotonMomentum
     137                                        ))
     138 {


     504             //[OpticalSurface.mpt.CustomPrefix
     505             if( OpticalSurfaceName0 == '@' || OpticalSurfaceName0 == '#' )  // only customize specially named OpticalSurfaces 
     506             {
     507                 m_custom_art->update_local_position(aTrack);
     508                 if( m_custom_art->local_z() < 0. ) // lower hemi : No customization, standard boundary  
     509                 {
     510                     m_custom_status = 'Z' ;
     511                 }
     512                 else if( OpticalSurfaceName0 == '@') //  upper hemi with name starting @ : MultiFilm ART transmit thru into PMT
     513                 {
     514                     m_custom_status = 'Y' ;
     515 
     516 #ifdef C4_DEBUG_PIDX
     517                     m_custom_art->dump = m_track_dump ;
     518 #endif
     519                     m_custom_art->doIt(aTrack, aStep) ;
     520 
     521                     /**
     522                     m_custom_art calculates 3-way probabilities (A,R,T) that sum to 1. 
     523                     and looks up theEfficiency appropriate for the PMT 
     524                     
     525                     BUT: as DielectricDielectric is expecting a 2-way *theTransmittance* probability 
     526                     m_custom_art leaves theAbsorption as A and rescales the others to create 2-way probs::
     527 
     528                          ( theAbsorption, theReflectivity, theTransmittance ) =  ( A, R/(1-A), T/(1-A) )
     529 
     530                     **/
     531 
     532 

::

    437	
    438	    double f_angle_response = 1.0;
    439	    double de = qe*ce*f_angle_response ;
    440	    if (de>1.0){
    441	        std::cout<<"junoSD_PMT_v2:: de is larger than 1.0"<<std::endl;
    442	    }
    443	    bool de_cull = G4UniformRand() > de ; 
    444	
    (gdb) p qe
    $9 = 1
    (gdb) p ce
    $10 = 0.9184643973589105
    (gdb) p qe
    $11 = 1
    (gdb) p qe*ce*f_angle_response
    $12 = 0.9184643973589105
    (gdb) 



The actual qe comes via the PMTOpticalModel that 
is impl in C4OpBoundaryProcess by C4CustomART::


    https://github.com/simoncblyth/customgeant4/blob/v0.1.8/C4CustomART.h

    inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    {
        G4double zero = 0. ; 
        G4double minus_one = -1. ; 
        G4double minus_cos_theta = OldMomentum*theRecoveredNormal ; 
        G4double dot_pol_cross_mom_nrm = OldPolarization*OldMomentum.cross(theRecoveredNormal) ; 

        G4double energy = thePhotonMomentum ; 
        G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
        G4double energy_eV = energy/CLHEP::eV ;
        G4double wavelength_nm = wavelength/CLHEP::nm ; 

        int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true ); 
        int pmtcat = accessor->get_pmtcat( pmtid ) ; 
        double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
        // following the old junoPMTOpticalModel with "backwards" _qe always zero 

        std::array<double,16> a_spec ; 
        accessor->get_stackspec(a_spec, pmtcat, energy_eV ); 

        const double* ss = a_spec.data() ; 

        Stack<double,4> stack ; 

        theEfficiency = zero ;
        if( minus_cos_theta < zero ) // only ingoing photons 
        {
            stack.calc( wavelength_nm, minus_one, zero, ss, 16u );  
            theEfficiency = _qe/stack.art.A ;    // aka escape_fac

            bool expect = theEfficiency <= 1. ; 
            if(!expect) std::cerr
                << "C4CustomART::doIt"
                << " FATAL "
                << " ERR: theEfficiency > 1. : " << theEfficiency
                << " _qe " << _qe
                << " stack.art.A (aka An) " << stack.art.A 
                << std::endl 
                ;
            assert( expect ); 
        }
        stack.calc( wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, ss, 16u );  

        const double& A = stack.art.A ; 
        const double& R = stack.art.R ; 
        const double& T = stack.art.T ; 

        theAbsorption = A ; 
        theReflectivity  = R/(1.-A) ; 
        theTransmittance = T/(1.-A)  ;   






::

    BP=C4CustomART::doIt

    (gdb) bt
    #0  0x00007fffc10f5c40 in C4CustomART::doIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #1  0x00007fffc10ef76a in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #2  0x00007fffc6727519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffc672791b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007fffc6725154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc673070f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #7  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x66b8440, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #8  0x00007fffd485ed3e in DetSimAlg::execute (this=0x65d2e70) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112


::

    BP=junoSD_PMT_v2::ProcessHits ipc run 




CULL::

    (ok) A[blyth@localhost optixrap]$ opticks-f CULL
    ./cfg4/CCtx.cc:Adds EFFICIENCY_COLLECT or EFFICIENCY_CULL to the _hitflags, 
    ./cfg4/CCtx.cc:        _hitflags |= EFFICIENCY_CULL ; 
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    EFFICIENCY_CULL    = 0x1 << 14, 
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    static constexpr const char* _EFFICIENCY_CULL    = "EX" ;
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:        case EFFICIENCY_CULL:    str=_EFFICIENCY_CULL ;break;

    ./examples/UseShaderSGLFW_Mesh/face_culling.txt:    glEnable(GL_CULL_FACE); 
    ./externals/optix.bash:RT_RAY_FLAG_CULL_BACK_FACING_TRIANGLES Do not intersect triangle back faces.
    ./externals/optix.bash:RT_RAY_FLAG_CULL_FRONT_FACING_TRIANGLES Do not intersect triangle front faces.
    ./externals/optix.bash:RT_RAY_FLAG_CULL_DISABLED_ANYHIT Do not intersect geometry which disables any-hit
    ./externals/optix.bash:RT_RAY_FLAG_CULL_ENFORCED_ANYHIT Do not intersect geometry which enforces
    ./externals/optix.bash:    /home/blyth/local/opticks/externals/OptiX/include/internal/optix_declarations.h:  RT_RAY_FLAG_CULL_DISABLED_ANYHIT          = 1u << 6, /*!< Do not intersect geometry which disables any-hit programs. */
    ./externals/optix.bash:    /home/blyth/local/opticks/externals/OptiX/include/internal/optix_declarations.h:  RT_RAY_FLAG_CULL_ENFORCED_ANYHIT          = 1u << 7  /*!< Do not intersect geometry which enforces any-hit programs. */

    ./g4ok/G4Opticks.cc:    EFFICIENCY_COLLECT (EC) or EFFICIENCY_CULL (EX) flag for photons that already 

    ./oglrap/GUI.cc:    //glEnable(GL_CULL_FACE);  going-one-sided causes issues
    ./optixrap/cu/generate.cu:        p.flags.u.w |= ( u_angular < efficiency ?  EFFICIENCY_COLLECT : EFFICIENCY_CULL ) ;   
    ./sysrap/OpticksPhoton.cc:        "EFFICIENCY_CULL":"red"
    ./sysrap/OpticksPhoton.h:    EFFICIENCY_CULL    = 0x1 << 14,
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* EFFICIENCY_CULL_ = "EFFICIENCY_CULL" ;
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* _EFFICIENCY_CULL    = "EX" ;
    ./sysrap/OpticksPhoton.hh:        case EFFICIENCY_CULL:    s=EFFICIENCY_CULL_ ;break; 
    ./sysrap/OpticksPhoton.hh:        case EFFICIENCY_CULL:    s=_EFFICIENCY_CULL ;break; 
    ./sysrap/OpticksPhoton.hh:    pairs.push_back(KV(EFFICIENCY_CULL_ , _EFFICIENCY_CULL)); 
    ./sysrap/SOPTIX_BuildInput_Mesh.h:    flag( OPTIX_GEOMETRY_FLAG_DISABLE_ANYHIT | OPTIX_GEOMETRY_FLAG_DISABLE_TRIANGLE_FACE_CULLING ),
    ./sysrap/SOPTIX_Scene.h:    flags |= OPTIX_INSTANCE_FLAG_DISABLE_TRIANGLE_FACE_CULLING ;
    ./sysrap/tests/sphoton_test.cc:       |= EFFICIENCY_CULL 00000000000000000111111111111111 15
    ./sysrap/tests/sphoton_test.cc:    flagmask |= EFFICIENCY_CULL ;    dump("|= EFFICIENCY_CULL", flagmask ); 
    (ok) A[blyth@localhost opticks]$ 


OLD OPTICKS optixrap/cu/generate.cu::


    864 #ifdef WITH_SENSORLIB
    865     if( s.flag == SURFACE_DETECT )
    866     {
    867         const unsigned& sensorIndex = s.identity.w ;   // should always be > 0 as flag is SD
    868 #ifdef ANGULAR_ENABLED
    869         const float& f_theta = prd.f_theta ;
    870         const float& f_phi = prd.f_phi ;
    871         const float efficiency = OSensorLib_combined_efficiency(sensorIndex, f_phi, f_theta);
    872         //rtPrintf("//SD sensorIndex %d f_theta %f f_phi %f efficiency %f \n", sensorIndex, f_theta, f_phi, efficiency );
    873 #else
    874         const float efficiency = OSensorLib_simple_efficiency(sensorIndex);
    875         //rtPrintf("//SD sensorIndex %d efficiency %f \n", sensorIndex, efficiency );
    876 #endif
    877         float u_angular = curand_uniform(&rng) ;
    878         p.flags.u.w |= ( u_angular < efficiency ?  EFFICIENCY_COLLECT : EFFICIENCY_CULL ) ;
    879     }
    880 #endif
    881 


    058 static __device__ __inline__ float OSensorLib_combined_efficiency(unsigned sensorIndex, float phi_fraction, float theta_fraction  )
     59 {
     60     // not expecting sensorIndex 0 which means that the volume is not a sensor
     61 
     62     unsigned sensor_data_size = OSensorLib_sensor_data.size();
     63     if( sensor_data_size == 0 ) return 1.f ;
     64 
     65     const float4& sensor_data = OSensorLib_sensor_data[sensorIndex-1] ;  // 1-based sensorIndex
     66 
     67     float efficiency_1 = sensor_data.x ;
     68     float efficiency_2 = sensor_data.y ;
     69     int category = __float_as_int(sensor_data.z);
     70     //int identifier = __float_as_int(sensor_data.w); 
     71 
     72     int tex_id = category > -1 ? OSensorLib_texid[category].x : -1 ;
     73     float angular_efficiency = tex_id > -1 ? rtTex2D<float>( tex_id, phi_fraction, theta_fraction ) : 1.f ;
     74 
     75     float combined_efficiency = efficiency_1*efficiency_2*angular_efficiency ;
     76     return combined_efficiency ;
     77 }



Setting the flag is good idea, OpticksPhoton.h::

     36     TORCH             = 0x1 << 12,
     37     NAN_ABORT         = 0x1 << 13,
     38     EFFICIENCY_CULL    = 0x1 << 14,
     39     EFFICIENCY_COLLECT = 0x1 << 15,
     40     __NATURAL         = 0x1 << 16,
     41     __MACHINERY       = 0x1 << 17,





TODO : CE collection and use from qsim.h, heavy lifting in qpmt.h QPMT.cc
---------------------------------------------------------------------------



qsim.h::

    1775 #endif
    1776         return BREAK ;
    1777     }
    1778 
    1779 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1780     if( ctx.idx == base->pidx )
    1781     printf("//qsim::propagate_at_surface_CustomART idx %d lpmtid %d wl %7.3f mct %7.3f dpcmn %7.3f pmt %p pre-ARTE \n",
    1782            ctx.idx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, pmt );
    1783 #endif
    1784 
    1785     float ARTE[4] = {} ;
    1786     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ARTE(ARTE, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm );
    1787 
    1788 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1789     if( ctx.idx == base->pidx )
    1790     printf("//qsim::propagate_at_surface_CustomART idx %d lpmtid %d wl %7.3f mct %7.3f dpcmn %7.3f ARTE ( %7.3f %7.3f %7.3f %7.3f ) \n",
    1791            ctx.idx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, ARTE[0], ARTE[1], ARTE[2], ARTE[3] );
    1792 #endif
    1793 
    1794 
    1795     const float& theAbsorption = ARTE[0];
    1796     //const float& theReflectivity = ARTE[1];
    1797     const float& theTransmittance = ARTE[2];
    1798     const float& theEfficiency = ARTE[3];
    1799 
    1800     float u_theAbsorption = curand_uniform(&rng);
    1801     int action = u_theAbsorption < theAbsorption  ? BREAK : CONTINUE ;
    1802 
    1803 
    1804 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1805     if( ctx.idx == base->pidx )
    1806     printf("//qsim.propagate_at_surface_CustomART idx %d lpmtid %d ARTE ( %7.3f %7.3f %7.3f %7.3f ) u_theAbsorption  %7.3f action %d \n",
    1807         ctx.idx, lpmtid, ARTE[0], ARTE[1], ARTE[2], ARTE[3], u_theAbsorption, action  );
    1808 #endif
    1809 
    1810     if( action == BREAK )
    1811     {
    1812         float u_theEfficiency = curand_uniform(&rng) ;
    1813         flag = u_theEfficiency < theEfficiency ? SURFACE_DETECT : SURFACE_ABSORB ;
    1814 
    1815 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1816     if( ctx.idx == base->pidx )
    1817     printf("//qsim.propagate_at_surface_CustomART.BREAK.SD/SA idx %d lpmtid %d ARTE ( %7.3f %7.3f %7.3f %7.3f ) u_theEfficiency  %7.3f theEfficiency %7.3f flag %d \n",
    1818         ctx.idx, lpmtid, ARTE[0], ARTE[1], ARTE[2], ARTE[3], u_theEfficiency, theEfficiency, flag  );
    1819 #endif
    1820 




lposcost
------------

::

        
    (ok) A[blyth@localhost sysrap]$ opticks-f lposcost
    ./CSGOptiX/CSGOptiX7.cu:    prd->set_lposcost(__uint_as_float(p6)) ;
    ./CSGOptiX/CSGOptiX7.cu:    //if(idx.x == 10 && idx.y == 10) printf("//CSGOptiX7.cu:render prd.distance(%7.3f)  prd.lposcost(%7.3f)  \n", prd->distance(), prd->lposcost()  );
    ./CSGOptiX/CSGOptiX7.cu:static __forceinline__ __device__ void setPayload( float normal_x, float normal_y, float normal_z, float distance, unsigned identity, unsigned globalPrimIdx_boundary, float lposcost, unsigned iindex )
    ./CSGOptiX/CSGOptiX7.cu:    optixSetPayload_6( lposcost );
    ./CSGOptiX/CSGOptiX7.cu:    const float lposcost = 0.f ;
    ./CSGOptiX/CSGOptiX7.cu:    prd->set_lposcost(lposcost);
    ./CSGOptiX/CSGOptiX7.cu:    setPayload( ms->r, ms->g, ms->b, 0.f, identity, globalPrimIdx_boundary, lposcost, 0u );  // communicate from ms->rg
    ./CSGOptiX/CSGOptiX7.cu:        float lposcost = normalize_z(P); // scuda.h  "cosTheta" z/len of local frame position 
    ./CSGOptiX/CSGOptiX7.cu:        prd->set_lposcost(lposcost);
    ./CSGOptiX/CSGOptiX7.cu:        setPayload( N.x, N.y, N.z, t, identity, globalPrimIdx_boundary, lposcost, iindex );  // communicate from ch->rg
    ./CSGOptiX/CSGOptiX7.cu:        const float lposcost = __uint_as_float( optixGetAttribute_5() ) ;
    ./CSGOptiX/CSGOptiX7.cu:        setPayload( normal.x, normal.y, normal.z, distance, identity, globalPrimIdx_boundary, lposcost, iindex );  // communicate from ch->rg
    ./CSGOptiX/CSGOptiX7.cu:        const float lposcost = normalize_z(ray_origin + isect.w*ray_direction ) ;  // scuda.h cosTheta z/len of local(aka Object) frame position
    ./CSGOptiX/CSGOptiX7.cu:            prd->set_lposcost(lposcost);
    ./CSGOptiX/CSGOptiX7.cu:        a5 = __float_as_uint( lposcost );

    ./qudarap/qsim.h:surface handling for z-minus, when lposcost < 0.f at lower z-hemi.
    ./qudarap/qsim.h:For z-plus with lposcost > 0.f upper z-hemi simply ignore
    ./qudarap/qsim.h:    const float lposcost = ctx.prd->lposcost() ;  // local frame intersect position cosine theta
    ./qudarap/qsim.h:    ctx.p.set_prd(boundary, identity, cosTheta, iindex );  // HMM: lposcost not passed along
    ./qudarap/qsim.h:            printf("//qsim.propagate.body.WITH_CUSTOM4 idx %d  BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost );
    ./qudarap/qsim.h:            printf("//qsim.propagate.body.NOT:WITH_CUSTOM4 idx %d BOUNDARY ems %d lposcost %7.3f \n", ctx.idx, ems, lposcost);
    ./qudarap/qsim.h:        else if( lposcost < 0.f )  // could combine with prior, but handy for debug to keep separate
    ./qudarap/qsim.h:            printf("//qsim.propagate.body (lposcost < 0.f) idx %d bounce %d command %d flag %d ems %d \n",
    ./qudarap/qsim.h:   of fallback to ordinary surface handling for "lposcost < 0.f" and also
    ./qudarap/qsim.h:   ordinary NoSurface must be possible no matter the lposcost value.

    ./qudarap/tests/QSim_MockTest.cc:    prd.q1.f.x = 0.5f ;  // lposcost : local position cosTheta of intersect 
    ./sysrap/SOPTIX.cu:    const float lposcost = 0.f ;
    ./sysrap/SOPTIX.cu:    prd->set_lposcost(lposcost);
    ./sysrap/SOPTIX.cu:    float lposcost = normalize_z(P); // scuda.h
    ./sysrap/SOPTIX.cu:    prd->set_lposcost(lposcost);
    ./sysrap/SPrd.h:    std::vector<float>  lposcost;
    ./sysrap/SPrd.h:    ssys::fill_evec<float>(lposcost, "SPRD_LPOSCOST", SPRD_LPOSCOST_DEFAULT, ',' );
    ./sysrap/SPrd.h:    int num_lposcost = lposcost.size() ;
    ./sysrap/SPrd.h:                      num_bnd_idx == num_lposcost
    ./sysrap/SPrd.h:        pr.set_lposcost( lposcost[i] );
    ./sysrap/SPrd.h:        << " num_lposcost " << lposcost.size()
    ./sysrap/squad.h:    | f:lposcost | u:iindex   | u:identity | u:boundary    |
    ./sysrap/squad.h:f:lposcost
    ./sysrap/squad.h:    SQUAD_METHOD float lposcost() const ;
    ./sysrap/squad.h:    SQUAD_METHOD void set_lposcost(float lpc);
    ./sysrap/squad.h:SQUAD_METHOD float          quad2::lposcost() const {   return q1.f.x ; }
    ./sysrap/squad.h:SQUAD_METHOD void           quad2::set_lposcost(float lpc)   { q1.f.x = lpc ; }
    ./u4/CustomBoundary.h:    double lposcost ; 
    ./u4/CustomBoundary.h:    lposcost(-2.),
    ./u4/CustomBoundary.h:    lposcost = localPoint.cosTheta() ;
    ./u4/LocalCustomART.h:    double lposcost ; 
    ./u4/LocalCustomART.h:    lposcost(-2.),
    ./u4/LocalCustomART.h:Q:What is lposcost for ?  
    ./u4/LocalCustomART.h:A:Preparing for doing this on GPU, as lposcost is available there already but zlocal is not, 
    ./u4/LocalCustomART.h:  so want to check the sign of lposcost is following that of zlocal. It looks 
    ./u4/LocalCustomART.h:    lposcost = localPoint.cosTheta() ;  
    (ok) A[blyth@localhost opticks]$ 





