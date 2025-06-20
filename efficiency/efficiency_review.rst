efficiency_review
===================

Summary
-----------

* FIXED : Missing CE scaledown of hits on GPU
* next :doc:`hitCollection`



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

          /// NB with m_enable_optical_model:true WHICH IS STANDARD   de = ce 
          /// SO THIS IS JUST DECIDING ON COLLECT OR CULL 
          /// IT IS NOT DOING ANYTHING WITH QE 
          ///  

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





DONE : CE collection and use from qsim.h, heavy lifting in qpmt.h QPMT.cc
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




CECOS landed
------------

::

    A[blyth@localhost CECOStheta]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt/PMTSimParamData/CECOStheta

    A[blyth@localhost CECOStheta]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: `?` alone on a line will brings up IPython's help
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.CECOS_R12860                                     :               (9, 2) : 0:05:17.959316 
      : f.CECOS_NNVTMCP                                    :               (9, 2) : 0:05:17.959316 
      : f.CECOS_NNVTMCP_HiQE                               :               (9, 2) : 0:05:17.959316 
      : f.CECOS_WP_PMT                                     :               (9, 2) : 0:05:17.959316 
      : f.NPFold_index                                     :                 (4,) : 0:05:17.959316 
      : f.NPFold_names                                     :                 (0,) : 0:05:17.959316 

     min_stamp : 2025-06-09 20:59:32.569722 
     max_stamp : 2025-06-09 20:59:32.569722 
     dif_stamp : 0:00:00 
     age_stamp : 0:05:17.959316 

    In [1]: f.CECOS_R12860
    Out[1]: 
    array([[0.   , 0.273],
           [0.087, 0.626],
           [0.191, 0.909],
           [0.407, 0.93 ],
           [0.574, 0.923],
           [0.755, 0.929],
           [0.883, 0.922],
           [0.974, 0.911],
           [1.   , 0.911]])

    In [2]: f.CECOS_NNVTMCP
    Out[2]: 
    array([[0.   , 0.734],
           [0.087, 0.884],
           [0.216, 0.927],
           [0.391, 0.925],
           [0.574, 0.893],
           [0.737, 0.91 ],
           [0.866, 0.945],
           [0.97 , 1.   ],
           [1.   , 1.   ]])

    In [3]: f.CECOS_NNVTMCP_HiQE
    Out[3]: 
    array([[0.   , 0.734],
           [0.087, 0.91 ],
           [0.216, 0.945],
           [0.391, 0.97 ],
           [0.574, 0.97 ],
           [0.737, 0.972],
           [0.866, 0.977],
           [0.97 , 1.   ],
           [1.   , 1.   ]])

    In [4]: f.CECOS_WP_PMT
    Out[4]: 
    array([[0.   , 0.734],
           [0.087, 0.884],
           [0.216, 0.927],
           [0.391, 0.925],
           [0.574, 0.893],
           [0.737, 0.91 ],
           [0.866, 0.945],
           [0.97 , 1.   ],
           [1.   , 1.   ]])


    A[blyth@localhost CECOStheta]$ cd ../CEtheta/
    A[blyth@localhost CEtheta]$ f
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: You can use `%hist` to view history, see the options with `%history?`
    f

    CMDLINE:/home/blyth/np/fold.py
    f.base:.

      : f.CE_R12860                                        :               (9, 2) : 0:08:36.018767 
      : f.CE_NNVTMCP                                       :               (9, 2) : 0:08:36.018767 
      : f.CE_NNVTMCP_HiQE                                  :               (9, 2) : 0:08:36.018767 
      : f.CE_WP_PMT                                        :               (9, 2) : 0:08:36.018767 
      : f.NPFold_index                                     :                 (4,) : 0:08:36.018767 
      : f.NPFold_names                                     :                 (0,) : 0:08:36.018767 

     min_stamp : 2025-06-09 20:59:32.569722 
     max_stamp : 2025-06-09 20:59:32.569722 
     dif_stamp : 0:00:00 
     age_stamp : 0:08:36.018767 

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





qsim.h propagate : single bit flag ? 
-------------------------------------

TAIL of propagate::

    2249             command = propagate_at_surface( flag, rng, ctx ) ;
    2250         }
    2251         else if( ems == smatsur_Surface_zplus_sensor_A )
    2252         {
    2253             command = propagate_at_surface_Detect( flag, rng, ctx ) ;
    2254         }
    2255         else if( ems == smatsur_Surface_zplus_sensor_CustomART )
    2256         {
    2257 #if defined(WITH_CUSTOM4)
    2258             command = propagate_at_surface_CustomART( flag, rng, ctx ) ;
    2259             //command = base->custom_lut == 0u ? propagate_at_surface_CustomART( flag, rng, ctx ) : propagate_at_surface_MultiFilm(flag, rng, ctx );
    2260 
    2261 #endif
    2262         }
    2263     }
    2264     ctx.p.set_flag(flag);
    2265     // Q: Does flag need to be single bit at this point OR can multiple "flags" be OR-ed together here ? 
    2266     // A: 
    2267 
    2268 
    2269 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    2270     if( ctx.idx == base->pidx )
    2271     printf("//qsim.propagate.tail idx %d bounce %d command %d flag %d ctx.s.optical.y(ems) %d \n",
    2272              ctx.idx, bounce, command, flag, ctx.s.optical.y  );
    2273 #endif
    2274 
    2275     return command ;
    2276 }   



flagmask
----------

::

    (ok) A[blyth@localhost qudarap]$ opticks-f flagmask
    ./ana/p.py:     64     unsigned flagmask ;       // p.view(np.uint32)[3,3]
    ./ana/p.py:flagmask_ = lambda p:p.view(np.uint32)[3,3]
    ./ana/p.py:flagdesc_ = lambda p:" idx(%6d) prd(b%3d p%4d i%5d o%1d ii:%5d) %3s  %15s " % ( idx_(p),  boundary_(p),primIdx_(p),instanceId_(p), orient_(p), iindex_(p), hm.label(flag_(p)),hm.label( flagmask_(p) ))
    ./ana/p.py:flagmask__ = lambda p:p.view(np.uint32)[:,3,3]
    ./ana/p.py:hit__      = lambda p,msk:p[np.where( ( flagmask__(p) & msk ) == msk)]    
    ./optickscore/tests/OpticksFlagsTest.cc:        << " flagmask(abbrev) " << OpticksPhoton::FlagMask(msk, true) 
    ./optickscore/tests/OpticksFlagsTest.cc:        << " flagmask " << OpticksPhoton::FlagMask(msk, false)
    ./sysrap/OpticksPhoton.hh:    static bool HasCerenkovFlag(const unsigned flagmask); 
    ./sysrap/OpticksPhoton.hh:    static bool HasScintillationFlag(const unsigned flagmask); 
    ./sysrap/OpticksPhoton.hh:    static bool HasTorchFlag(const unsigned flagmask); 
    ./sysrap/OpticksPhoton.hh:inline bool OpticksPhoton::HasCerenkovFlag(const unsigned flagmask)
    ./sysrap/OpticksPhoton.hh:    return ( flagmask & CERENKOV ) != 0 ;  
    ./sysrap/OpticksPhoton.hh:inline bool OpticksPhoton::HasScintillationFlag(const unsigned flagmask)
    ./sysrap/OpticksPhoton.hh:    return ( flagmask & SCINTILLATION ) != 0 ;  
    ./sysrap/OpticksPhoton.hh:inline bool OpticksPhoton::HasTorchFlag(const unsigned flagmask)
    ./sysrap/OpticksPhoton.hh:    return ( flagmask & TORCH ) != 0 ;  
    ./sysrap/SEvt.cc:    bool flagmask_one_bit = ctx.p.flagmask_count() == 1  ;
    ./sysrap/SEvt.cc:    LOG_IF(error, !flagmask_one_bit )
    ./sysrap/SEvt.cc:        << " not flagmask_one_bit "
    ./sysrap/SEvt.cc:        << " : should only be a single bit in the flagmask at this juncture "
    ./sysrap/SEvt.cc:    assert( flagmask_one_bit );
    ./sysrap/SEvt.cc:        current_photon.flagmask &= ~BULK_ABSORB  ; // scrub BULK_ABSORB from flagmask
    ./sysrap/SEvt.cc:        current_photon.set_flag(BULK_REEMIT) ;     // gets OR-ed into flagmask
    ./sysrap/SEvt.cc:        rjoin_record.flagmask &= ~BULK_ABSORB ; // scrub BULK_ABSORB from flagmask
    ./sysrap/SEvt.cc:    unsigned flagmask = ph.flagmask ;
    ./sysrap/SEvt.cc:    bool flagmask_AB = flagmask & BULK_ABSORB  ;
    ./sysrap/SEvt.cc:    bool flagmask_MI = flagmask & MISS ;
    ./sysrap/SEvt.cc:    bool flagmask_or = flagmask_AB | flagmask_MI ;
    ./sysrap/SEvt.cc:    if(flagmask_AB) dbg->rjoinPhotonCheck_flagmask_AB++ ;
    ./sysrap/SEvt.cc:    if(flagmask_MI) dbg->rjoinPhotonCheck_flagmask_MI++ ;
    ./sysrap/SEvt.cc:    if(flagmask_or) dbg->rjoinPhotonCheck_flagmask_or++ ;
    ./sysrap/SEvt.cc:    bool expect = flag_xor && flagmask_or ;
    ./sysrap/SEvt.cc:        << "rjoinPhotonCheck : unexpected flag/flagmask"
    ./sysrap/SEvt.cc:        << " flagmask_AB " << flagmask_AB
    ./sysrap/SEvt.cc:        << " flagmask_MI " << flagmask_MI
    ./sysrap/SEvt.cc:        << " flagmask_or " << flagmask_or
    ./sysrap/SEvt.cc:    bool first_flag = ctx.p.flagmask_count() == 1 ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_AB ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_MI ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_or ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_AB ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_MI ;
    ./sysrap/sdebug.h:    int rjoinPhotonCheck_flagmask_or ;
    ./sysrap/squad.h:    SQUAD_METHOD unsigned flagmask() const ;
    ./sysrap/squad.h:    q3.u.w |= flag ;    // bitwise-OR into flagmask
    ./sysrap/squad.h:SQUAD_METHOD unsigned quad4::flagmask() const
    ./sysrap/squad.h:    SQUAD_METHOD bool operator() (const quad4& p) const { return ( p.flagmask() & hitmask ) == hitmask  ; }   // require all bits of the mask to be set
    ./sysrap/squad.h:    SQUAD_METHOD bool operator() (const T& p) const { return ( p.flagmask() & hitmask ) == hitmask  ; }   // require all bits of the mask to be set
    ./sysrap/squad.h:    flagmask_ = lambda p:p.view(np.uint32)[3,3]
    ./sysrap/squad.h:    flagdesc_ = lambda p:" %4d %10s id:%6d ori:%d idx:%6d %10s " % ( boundary_(p), hm.label(flag_(p)), identity_(p), orient_(p), idx_(p), hm.label( flagmask_(p) ))
    ./sysrap/sphoton.h:|    | boundary_flag  |  identity      |  orient_idx    |  flagmask      |  (unsigned)              |
    ./sysrap/sphoton.h:flagmask (32 bit)
    ./sysrap/sphoton.h:    flagmask_ = lambda p:p.view(np.uint32)[3,3]
    ./sysrap/sphoton.h:    unsigned flagmask ; 
    ./sysrap/sphoton.h:    unsigned flagmask ; 
    ./sysrap/sphoton.h:    SPHOTON_METHOD void     set_flag(unsigned flag) {         boundary_flag = ( boundary_flag & 0xffff0000u ) | ( flag & 0xffffu ) ; flagmask |= flag ;  } // clear flag bits then set them  
    ./sysrap/sphoton.h:    SPHOTON_METHOD void zero_flags() { boundary_flag = 0u ; identity = 0u ; orient_idx = 0u ; flagmask = 0u ; } 
    ./sysrap/sphoton.h:       boundary_flag = 0u ; identity = 0u ; orient_idx = 0u ; flagmask = 0u ;  
    ./sysrap/sphoton.h:    SPHOTON_METHOD bool is_cerenkov()  const { return (flagmask & CERENKOV) != 0 ; }
    ./sysrap/sphoton.h:    SPHOTON_METHOD bool is_reemit() const {    return (flagmask & BULK_REEMIT) != 0 ; }
    ./sysrap/sphoton.h:    SPHOTON_METHOD unsigned flagmask_count() const ; 
    ./sysrap/sphoton.h:SPHOTON_METHOD unsigned sphoton::flagmask_count() const 
    ./sysrap/sphoton.h:    return std::bitset<32>(flagmask).count() ;   // NB counting bits, not nibbles with bits
    ./sysrap/sphoton.h:        << " fm " << std::hex << flagmask  << std::dec 
    ./sysrap/sphoton.h:       << " flagmask " << OpticksPhoton::FlagMask(flagmask)
    ./sysrap/sphoton.h:           a.flagmask == b.flagmask 
    ./sysrap/sphoton.h:    SPHOTON_METHOD bool operator() (const sphoton& p) const { return ( p.flagmask  & hitmask ) == hitmask  ; }   // require all bits of the mask to be set 
    ./sysrap/sphoton.h:    SPHOTON_METHOD bool operator() (const sphoton* p) const { return ( p->flagmask & hitmask ) == hitmask  ; }   // require all bits of the mask to be set 
    ./sysrap/sphoton.h:    unsigned long long flagmask ; 
    ./sysrap/sphoton.h:    d.flagmask      = ull(s.flagmask) ;  
    ./sysrap/tests/OpticksPhotonTest.cc:            << " flagmask(abbrev) " << std::setw(20) << OpticksPhoton::FlagMask(msk, true) 
    ./sysrap/tests/OpticksPhotonTest.cc:            << " flagmask " << OpticksPhoton::FlagMask(msk, false)
    ./sysrap/tests/SUTest.cc:Zeros pp photon array and for a third of the entries sets the flagmask entry 
    ./sysrap/tests/sphoton_test.cc:    static void change_flagmask();
    ./sysrap/tests/sphoton_test.cc:void sphoton_test::change_flagmask()
    ./sysrap/tests/sphoton_test.cc:    unsigned flagmask = 0u ;         dump("zero", flagmask );  
    ./sysrap/tests/sphoton_test.cc:    flagmask |= CERENKOV ;           dump("|= CERENKOV", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SCINTILLATION ;      dump("|= SCINTILLATION", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= MISS ;               dump("|= MISS", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= BULK_ABSORB ;        dump("|= BULK_ABSORB", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= BULK_REEMIT ;        dump("|= BULK_REEMIT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= BULK_SCATTER ;       dump("|= BULK_SCATTER", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SURFACE_DETECT ;     dump("|= SURFACE_DETECT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SURFACE_ABSORB ;     dump("|= SURFACE_ABSORB", flagmask );   
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SURFACE_DREFLECT ;   dump("|= SURFACE_DREFLECT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SURFACE_SREFLECT ;   dump("|= SURFACE_SREFLECT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= BOUNDARY_REFLECT ;   dump("|= BOUNDARY_REFLECT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= BOUNDARY_TRANSMIT ;  dump("|= BOUNDARY_TRANSMIT", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= TORCH ;              dump("|= TORCH", flagmask); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= NAN_ABORT ;          dump("|= NAN_ABORT", flagmask );  
    ./sysrap/tests/sphoton_test.cc:    flagmask |= EFFICIENCY_CULL ;    dump("|= EFFICIENCY_CULL", flagmask ); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |= EFFICIENCY_COLLECT ; dump("|= EFFICIENCY_COLLECT", flagmask) ;  
    ./sysrap/tests/sphoton_test.cc:    flagmask &= ~BULK_ABSORB ;       dump("&= ~BULK_ABSORB", flagmask); 
    ./sysrap/tests/sphoton_test.cc:    flagmask &= ~BULK_REEMIT ;       dump("&= ~BULK_REEMIT", flagmask); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |=  BULK_REEMIT ;       dump("|=  BULK_REEMIT", flagmask); 
    ./sysrap/tests/sphoton_test.cc:    flagmask |=  BULK_ABSORB ;       dump("|=  BULK_ABSORB", flagmask); 
    ./sysrap/tests/sphoton_test.cc:    else if(strcmp(TEST, "change_flagmask")==0)    change_flagmask(); 
    ./u4/U4HitGet.h:    hit.flag_mask = global.flagmask ; 
    ./u4/U4Recorder.cc:Can get that by counting bits in the flagmask, as only the first step will have only
    ./u4/U4Recorder.cc:    // first_flag identified by the flagmask having a single bit (all genflag are single bits, set in beginPhoton)
    ./u4/U4Recorder.cc:    bool first_flag = current_photon.flagmask_count() == 1 ;
    ./u4/tests/U4RecorderTest.py:    flagmask_u, flagmask_c = np.unique(p.view(np.uint32)[:,3,3], return_counts=True)    
    ./u4/tests/U4RecorderTest.py:    print("flagmask_u:%s " % str(flagmask_u))
    ./u4/tests/U4RecorderTest.py:    print("flagmask_c:%s " % str(flagmask_c))
    ./u4/tests/U4SimulateTest_mt.py:    flagmask = t.photon[:,3,3].view(np.int32) 
    ./u4/tests/U4SimulateTest_mt.py:    sd = flagmask & SURFACE_DETECT != 0 
    ./u4/tests/U4SimulateTest_mt.py:    sa = flagmask & SURFACE_ABSORB != 0 
    ./u4/tests/U4SimulateTest_ph.py:    flagmask = t.photon[:,3,3].view(np.int32) 
    ./u4/tests/U4SimulateTest_ph.py:    sd = flagmask & SURFACE_DETECT
    (ok) A[blyth@localhost opticks]$ 




hitmask
-----------

::

    175     static constexpr const char* kHitMask      = "OPTICKS_HIT_MASK" ;


    unsigned SEventConfig::_HitMask  = OpticksPhoton::GetHitMask(ssys::getenvvar(kHitMask, _HitMaskDefault )) ;



Mode 3 A:B hits matched before impl of CE cull GPU side  : confirmed due to pre-CE comparison
----------------------------------------------------------------------------------------------

A side
    qsim.h assigns SURFACE_DETECT flag following QE culling only   

B side
    U4StepPoint::BoundaryFlag translates "Detection" from the boundary process 
    (which is with QE culling only) to SURFACE_DETECT. 




::

    234 unsigned U4StepPoint::BoundaryFlag(unsigned status) // BT BR NA SA SD SR DR 
    235 {
    236     unsigned flag = 0 ;
    237     switch(status)
    238     {
    239         case FresnelRefraction:
    240         case SameMaterial:
    241         case Transmission:
    242                                flag=BOUNDARY_TRANSMIT;
    243                                break;
    244         case TotalInternalReflection:
    245         case       FresnelReflection:
    246                                flag=BOUNDARY_REFLECT;
    247                                break;
    248         case StepTooSmall:
    249                                flag=NAN_ABORT;
    250                                break;
    251         case Absorption:
    252                                flag=SURFACE_ABSORB ;
    253                                break;
    254         case Detection:
    255                                flag=SURFACE_DETECT ;
    256                                break;
    257         case SpikeReflection:
    258                                flag=SURFACE_SREFLECT ;
    259                                break;
    260         case LobeReflection:
    261         case LambertianReflection:
    262                                flag=SURFACE_DREFLECT ;
    263                                break;
    264         case NoRINDEX:
    265                                flag=SURFACE_ABSORB ;
    266                                //flag=NAN_ABORT;
    267                                break;
    268         case Undefined:
    269         case BackScattering:
    270         case NotAtBoundary:
    271         case PolishedLumirrorAirReflection:
    272         case PolishedLumirrorGlueReflection:




SURFACE_DETECT
-----------------

::


    ok) A[blyth@localhost tests]$ opticks-f SURFACE_DETECT
    ./ana/debug/types.py:        SURFACE_DETECT = 0x1 << 2
    ./ana/debug/types.py:        detected = np.where( flags & SURFACE_DETECT  )
    ./ana/ht.py:    ht = np.load("ht.npy") # ht are a selection of the ox:photons with SD:SURFACE_DETECT flag set  
    ./ana/ht.py:    # and knowledge that hit selection requires SD:SURFACE_DETECT 
    ./boostrap/BRegex.cc:    SURFACE_DETECT         = 0x1 << 2,
    ./boostrap/brap.bash:                    SURFACE_DETECT : 7 :         64 :         40
    ./boostrap/brap.bash:    SURFACE_DETECT         = 0x1 << 2,
    ./cfg4/CPhoton.cc:    bool flag_done = ( _flag & (BULK_ABSORB | SURFACE_ABSORB | SURFACE_DETECT | MISS)) != 0 ;
    ./cfg4/CRec.cc:    bool surfaceAbsorb = (postFlag & (SURFACE_ABSORB | SURFACE_DETECT)) != 0 ;
    ./cfg4/CRecorder.cc:        bool lastPost = (postFlag & (BULK_ABSORB | SURFACE_ABSORB | SURFACE_DETECT | MISS )) != 0 ;
    ./cfg4/CRecorder.cc:        bool surfaceAbsorb = (postFlag & (SURFACE_ABSORB | SURFACE_DETECT)) != 0 ;
    ./cfg4/CRecorder.cc:        SD = (postFlag & SURFACE_DETECT) != 0 ;
    ./cfg4/CRecorderLive.cc:    bool lastPost = (postFlag & (BULK_ABSORB | SURFACE_ABSORB | SURFACE_DETECT | MISS)) != 0 ;
    ./cfg4/CRecorderLive.cc:    bool surfaceAbsorb = (postFlag & (SURFACE_ABSORB | SURFACE_DETECT)) != 0 ;
    ./cfg4/OpStatus.cc:    return (flag & (BULK_ABSORB | SURFACE_ABSORB | SURFACE_DETECT | MISS )) != 0 ;
    ./cfg4/OpStatus.cc:                               flag=SURFACE_DETECT ; 
    ./cfg4/OpStatus.cc:                               flag=SURFACE_DETECT ; 
    ./cfg4/OpStatus.cc:        flag = OpStatus::OpBoundaryFlag(bst) ; // BOUNDARY_TRANSMIT/BOUNDARY_REFLECT/NAN_ABORT/SURFACE_ABSORB/SURFACE_DETECT/SURFACE_DREFLECT/SURFACE_SREFLECT
    ./examples/Geant4/BoundaryStandalone/G4OpBoundaryProcessTest.cc:        case Detection:               st = SURFACE_DETECT    ; break ; 
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    SURFACE_DETECT    = 0x1 <<  6,  
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    static constexpr const char* _SURFACE_DETECT    = "SD" ;
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:        case SURFACE_DETECT:   str=_SURFACE_DETECT ;break;
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:                               flag=SURFACE_DETECT ; 
    ./g4ok/G4Opticks.cc:    have SURFACE_DETECT flag 
    ./ggeo/GPho.cc:    return ( pflg & SURFACE_DETECT) != 0 ; 
    ./npy/Types.cpp:    s["SURFACE_DETECT"]    = "SD" ;
    ./ok/tests/flagsTest.cc:    DUMP(SURFACE_DETECT);
    ./okop/tests/compactionTest.cc:    unsigned hitmask = SURFACE_DETECT ; 
    ./optickscore/OpticksEvent.cc:    unsigned hitmask = SURFACE_DETECT ;   // TODO: this is an input, not a constant 
    ./optickscore/SensorLib.cc:    that already have SURFACE_DETECT 
    ./optickscore/okc.bash:* add extra SkinSurface and OpticalSurface objects to DAE level geometry in order to be transformed into sensitive surfaces needed for chroma SURFACE_DETECT
    ./optixrap/OEvent.cc:    2021-01-25 23:16:19.422 INFO  [4926544] [OEvent::downloadHits@443]  nhit 87 --dbghit N hitmask 0x40 SD SURFACE_DETECT
    ./optixrap/cu/generate.cu:    unsigned trivial_flags = photon_id % 1000 == 0 ? SURFACE_DETECT : 0u ; 
    ./optixrap/cu/generate.cu:            if(command == BREAK)    break ;       // SURFACE_DETECT/SURFACE_ABSORB
    ./optixrap/cu/generate.cu:    //if( bounce == bounce_max && ( s.flag == SURFACE_DETECT || s.flag == SURFACE_ABSORB ))
    ./optixrap/cu/generate.cu:    if( s.flag == SURFACE_DETECT ) 
    ./optixrap/cu/generate.cu:    //  kludged this with s.index.y -> s.index.x in propagate for SURFACE_ABSORB and SURFACE_DETECT
    ./optixrap/cu/generate.cu:   //if(p.flags.i.w & SURFACE_DETECT )
    ./optixrap/cu/propagate.h:* BREAK(SURFACE_DETECT) 
    ./optixrap/cu/propagate.h:        s.flag = SURFACE_DETECT ;
  


    ./qudarap/qsim.h:        flag = u_theEfficiency < theEfficiency ? SURFACE_DETECT : SURFACE_ABSORB ;
    ./qudarap/qsim.h:|   SURFACE_DETECT    |    BREAK         |                                                         |              |
    ./qudarap/qsim.h:   0--SURFACE_ABSORB---|--SURFACE_DETECT---|--SURFACE_DREFLECT---|--SURFACE_SREFLECT------1
    ./qudarap/qsim.h:        flag = u_surface < absorb ? SURFACE_ABSORB : SURFACE_DETECT  ;
    ./qudarap/qsim.h:    flag = SURFACE_DETECT ;
    ./qudarap/qsim.h:        flag = u_theEfficiency < theEfficiency ? SURFACE_DETECT : SURFACE_ABSORB ;
    ./qudarap/qsim.h:        unsigned ce_flag = flag == SURFACE_DETECT

    ./sysrap/OpticksPhoton.cc:        "SURFACE_DETECT":"purple",
    ./sysrap/OpticksPhoton.h:    SURFACE_DETECT    = 0x1 <<  6,
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* SURFACE_DETECT_ = "SURFACE_DETECT" ;
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* _SURFACE_DETECT    = "SD" ;
    ./sysrap/OpticksPhoton.hh:    return (flag & (BULK_ABSORB | SURFACE_ABSORB | SURFACE_DETECT | MISS )) != 0 ;
    ./sysrap/OpticksPhoton.hh:    return (flag & (SURFACE_DETECT | SURFACE_ABSORB | SURFACE_DREFLECT | SURFACE_SREFLECT | BOUNDARY_REFLECT | BOUNDARY_TRANSMIT )) != 0 ; 
    ./sysrap/OpticksPhoton.hh:    return (flag & (SURFACE_DETECT | SURFACE_ABSORB)) != 0  ; 
    ./sysrap/OpticksPhoton.hh:    return flag == SURFACE_DETECT ; 
    ./sysrap/OpticksPhoton.hh:        case SURFACE_DETECT:   s=SURFACE_DETECT_ ;break; 
    ./sysrap/OpticksPhoton.hh:        case SURFACE_DETECT:   s=_SURFACE_DETECT ;break; 
    ./sysrap/OpticksPhoton.hh:    pairs.push_back(KV(SURFACE_DETECT_ , _SURFACE_DETECT)); 

    ./sysrap/tests/OpticksPhotonTest.cc:    unsigned x_mask = TORCH | SURFACE_DETECT | BOUNDARY_TRANSMIT ;
    ./sysrap/tests/sphoton_test.cc:    p.set_flag( SURFACE_DETECT );
    ./sysrap/tests/sphoton_test.cc:    p.add_flagmask( SURFACE_DETECT );
    ./sysrap/tests/sphoton_test.cc:    std::cout << "add_flagmask.1 SURFACE_DETECT : " << p.descFlag() << "\n" ;
    ./sysrap/tests/sphoton_test.cc:        |= SURFACE_DETECT 00000000000000000000000001111111  7
    ./sysrap/tests/sphoton_test.cc:    flagmask |= SURFACE_DETECT ;     dump("|= SURFACE_DETECT", flagmask );
    ./sysrap/tests/sseq_test.cc:       SURFACE_DETECT,
    ./sysrap/tests/sseq_test.cc:       SURFACE_DETECT,
    ./sysrap/tests/sseq_test.cc:       SURFACE_DETECT,
    ./sysrap/tests/SEvtTest.cc:       SURFACE_DETECT

    ./thrustrap/TBuf_.cu:     69    //m_hitmask(SURFACE_DETECT),
    ./thrustrap/TIsHit.hh:Canonically only a single bit is set in the mask with SURFACE_DETECT.  
    ./thrustrap/TIsHit.hh:* photon flags such as SURFACE_DETECT are assigned to s.flag by oxrap-/cu/propagate.h
    ./thrustrap/TIsHit.hh:In [43]: TORCH | SURFACE_DETECT | BOUNDARY_TRANSMIT
    ./thrustrap/TIsHit.hh:n [47]: ( TORCH | SURFACE_DETECT | BOUNDARY_TRANSMIT | BULK_SCATTER  )
    ./thrustrap/tests/TBuf2x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 
    ./thrustrap/tests/TBuf4x4Test.cu:    NPY<float>* ph = DummyPhotonsNPY::Make(num_photons, SURFACE_DETECT );
    ./thrustrap/tests/TBuf4x4Test.cu:    NPY<float>* ph = DummyPhotonsNPY::Make(num_photons, SURFACE_DETECT );
    ./thrustrap/tests/TBuf4x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 
    ./thrustrap/tests/TBuf4x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 
    ./thrustrap/tests/TBuf4x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 
    ./thrustrap/tests/TBuf4x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 
    ./thrustrap/tests/TBuf4x4Test.cu:    unsigned hitmask = SURFACE_DETECT ; 

    ./u4/U4StepPoint.cc:                               flag=SURFACE_DETECT ; 
    ./u4/U4Recorder.cc:           case 'D': flag = SURFACE_DETECT    ; break ;

    ./u4/U4Touchable.h:for step points classified as SURFACE_DETECT "SD". 

    ./u4/tests/U4SimulateTest_mt.py:SURFACE_DETECT = 0x1 << 6 
    ./u4/tests/U4SimulateTest_mt.py:SD = SURFACE_DETECT.bit_length()
    ./u4/tests/U4SimulateTest_mt.py:    sd = flagmask & SURFACE_DETECT != 0 
    ./u4/tests/U4SimulateTest_ph.py:    SURFACE_DETECT = 0x1 << 6 
    ./u4/tests/U4SimulateTest_ph.py:    sd = flagmask & SURFACE_DETECT
    (ok) A[blyth@localhost opticks]$ 





How to plant EC/EX into sphoton flag/flagmask on B side with U4Recorder ?
-----------------------------------------------------------------------------


jcv junoSD_PMT_v2 ProcessHits::

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
     445 
     446 

Need to communicate de_cull from ProcessHits to the U4Recorder ?

U4Recorder::

     937 **How to incorporate info from ProcessHits into the SEvt ?**
     938 
     939 g4-cls G4SteppingManager::
     940 
     941     230 // Send G4Step information to Hit/Dig if the volume is sensitive
     942     231    fCurrentVolume = fStep->GetPreStepPoint()->GetPhysicalVolume();
     943     232    StepControlFlag =  fStep->GetControlFlag();
     944     233    if( fCurrentVolume != 0 && StepControlFlag != AvoidHitInvocation) {
     945     234       fSensitive = fStep->GetPreStepPoint()->
     946     235                                    GetSensitiveDetector();
     947     236       if( fSensitive != 0 ) {
     948     237         fSensitive->Hit(fStep);
     949     238       }
     950     239    }
     951     240
     952     241 // User intervention process.
     953     242    if( fUserSteppingAction != 0 ) {
     954     243       fUserSteppingAction->UserSteppingAction(fStep);
     955     244    }
     956 
     957 * G4VSensitive::Hit/G4VSensitive::ProcessHits happens before UserSteppingAction
     958   so if plant the ProcessHits enum into the track label
     959   can then copy that into the current_aux
     960 

* could use the track info label 


eph enumeration precisely whats needed ?
--------------------------------------------

::

     35 struct spho
     36 {
     37     static constexpr const int N = 4 ;
     38 
     39     int gs ; // 0-based genstep index within the event
     40     int ix ; // 0-based photon index within the genstep
     41     int id ; // 0-based photon identity index within the event
     42 
     43     spho_uchar4 uc4 ;
     44     // uc4.x : gen : 0-based reemission index incremented at each reemission
     45     // uc4.y : eph : eg junoSD_PMT_v2::ProcessHits eph enumeration
     46     // uc4.z : ext : unused
     47     // uc4.w : photon point flag TO/BT/BR/SC/AB/SD/SR/... etc
     48 
     49     unsigned uc4packed() const ;
     50 
     51     int gen() const ;
     52     int eph() const ;
     53     int ext() const ;
     54     int flg() const ;
     55 
     56     void set_gen(int gn) ;
     57     void set_eph(int ep) ;
     58     void set_ext(int ex) ;
     59     void set_flg(int fg) ;


Not quite thats only within G4CXOPTICKS_DEBUG but the machinery can be adapted
to do something similar within:: 

     310 #ifdef WITH_G4CXOPTICKS_DEBUG
     311 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     312 {
     313     G4bool is_hit = ProcessHits_(step, nullptr) ;
     314     m_jpmt_dbg->add( m_eph, is_hit );
     315 
     316     G4Track* track = step->GetTrack() ;
     317     int label_id = C4Track::GetLabelID(track);
     318 
     319     C4Track::SetLabelEph(track, m_eph);
     320     C4Track::IncrementLabelExt(track) ;
     321 
     322     LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     323 
     324     return is_hit ;
     325 }
     326 
     327 junoSD_PMT_v2_Debug* junoSD_PMT_v2::getProcessHitsDebug() const
     328 {
     329     return m_jpmt_dbg ;
     330 }
     331 
     332 
     333 #endif




The flag wont fit in the char slots of the label, so will need::

    unsigned flg = OpticksPhoton::BitPos(flag);   // where flg is < 32 


HMM : might as well use the EPH machinery always within WITH_G4CXOPTICKS::

    jcv junoSD_PMT_v2_Debug


    int eph = C4Track::GetLabelEph(track) ; // BUT with spho ? 



WITH_G4CXOPTICKS_DEBUG
-------------------------

::

    ok) A[blyth@localhost junosw]$ jgr G4CXOPTICKS_DEBUG
    ./Doc/oum/source/releasenotes/J22.2.md:    * collect more debug fields into U4Scintillation_Debug hidden behind WITH_G4CXOPTICKS_DEBUG, plus avoid compilation warnings (see MR !24 and !27)
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_DEBUG

          Adds shim ProcessHits_

    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_DEBUG


Does stuff beyond m_eph::

     919 #ifdef WITH_G4CXOPTICKS_DEBUG
     920     LOG(LEVEL) << " pmtID "  << std::setw(7) << pmtID ;
     921     U4Hit_Debug hit_dbg ;
     922     hit_dbg.label = U4PhotonInfo::Get(track);
     923     hit_dbg.add();
     924 #endif



    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
 
         ## collects using U4Scintillation_Debug
         ## thats too extreme to move to WITH_G4CXOPTICKS

    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG
    ./Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc:#ifdef WITH_G4CXOPTICKS_DEBUG

         ## collects using U4Cerenkov_Debug.hh
         ## again too extreme to move to WITH_G4CXOPTICKS

    (ok) A[blyth@localhost junosw]$ 



ADDED WITH_G4CXOPTICKS_EPH to house just the m_eph collection
---------------------------------------------------------------

::

    (ok) A[blyth@localhost u4]$ jgr WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#define WITH_G4CXOPTICKS_EPH 1
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:#ifdef WITH_G4CXOPTICKS_EPH
    (ok) A[blyth@localhost junosw]$ 



::

     310 #ifdef WITH_G4CXOPTICKS_EPH
     311 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     312 {
     313     G4bool is_hit = ProcessHits_(step, nullptr) ;
     314     m_jpmt_dbg->add( m_eph, is_hit );
     315 
     316     G4Track* track = step->GetTrack() ;
     317     int label_id = C4Track::GetLabelID(track);
     318 
     319     C4Track::SetLabelEph(track, m_eph);
     320     C4Track::IncrementLabelExt(track) ;
     321 
     322     LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     323 
     324     return is_hit ;
     325 }



WHERE TO GET EPH ? U4Recorder::PostUserTrackingAction_Optical_ -> SEvt::finalPhoton  
------------------------------------------------------------------------------------

The label gets passed to SEvt::finalPhoton::

    0809 void U4Recorder::PostUserTrackingAction_Optical_(const G4Track* track, int* label)
     810 {
     811     spho& ulabel = reinterpret_cast<spho&>(*label);
     812     if(!Enabled(ulabel)) return ; // EIDX, GIDX skipping
     813 
     814     G4TrackStatus tstat = track->GetTrackStatus();
     815     LOG(LEVEL) << U4TrackStatus::Name(tstat) ;
     816 
     817     bool is_fStopAndKill = tstat == fStopAndKill ;
     818     bool is_fSuspend     = tstat == fSuspend ;
     819     bool is_fStopAndKill_or_fSuspend = is_fStopAndKill || is_fSuspend  ;
     820     LOG_IF(info, !is_fStopAndKill_or_fSuspend ) << " not is_fStopAndKill_or_fSuspend  post.tstat " << U4TrackStatus::Name(tstat) ;
     821     assert( is_fStopAndKill_or_fSuspend );
     822 
     823 
     824     if(is_fStopAndKill)
     825     {
     826         SEvt* sev = SEvt::Get_ECPU();
     827         U4Random::SetSequenceIndex(-1);
     828         sev->finalPhoton(ulabel);
     829         transient_fSuspend_track = nullptr ;
     830 #ifndef PRODUCTION
     831         bool PIDX_DUMP = ulabel.id == PIDX && PIDX_ENABLED ;
     832         sseq& seq = sev->current_ctx.seq ;



    2940 void SEvt::finalPhoton(const spho& label)
    2941 {
    2942     dbg->finalPhoton++ ;
    2943     LOG(LEVEL) << label.desc() ;
    2944     assert( label.isSameLineage(current_pho) );
    2945 
    2946     int eph = label.eph();
    2947     const char* eph_name = EPH::Name(eph);
    2948     LOG(info) << " eph " << std::setw(2) << eph << " eph_name " << ( eph_name ? eph_name : "-" ) ;
    2949 
    2950     unsigned idx = label.id ;
    2951     sctx& ctx = current_ctx ;
    2952     assert( ctx.idx == idx );

::

    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph 11 eph_name EPH_SAVENORM
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  3 eph_name EPH_NEDEP
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  3 eph_name EPH_NEDEP
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph 11 eph_name EPH_SAVENORM
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  3 eph_name EPH_NEDEP
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  0 eph_name EPH_UNSET
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph 11 eph_name EPH_SAVENORM
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph 11 eph_name EPH_SAVENORM
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  3 eph_name EPH_NEDEP
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph 11 eph_name EPH_SAVENORM
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  0 eph_name EPH_UNSET
    2025-06-10 16:47:13.371 INFO  [3140501] [SEvt::finalPhoton@2948]  eph  3 eph_name EPH_NEDEP


::

    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  4 ext  1 flg  0 eph_ EPH_NBOUND is_eph_collect NO  is_eph_cull NO  eph_flag 0 eph_flag_ .
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() AB eph_flag_   
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  3 ext  1 flg  0 eph_ EPH_NEDEP is_eph_collect NO  is_eph_cull NO  eph_flag 0 eph_flag_ .
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SA eph_flag_   
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph 10 ext  1 flg  0 eph_ EPH_SAVENORM is_eph_collect YES is_eph_cull NO  eph_flag 32768 eph_flag_ EFFICIENCY_COLLECT
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SD eph_flag_ EC
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  7 ext  1 flg  0 eph_ EPH_NDECULL is_eph_collect NO  is_eph_cull YES eph_flag 16384 eph_flag_ EFFICIENCY_CULL
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SD eph_flag_ EX
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph 10 ext  1 flg  0 eph_ EPH_SAVENORM is_eph_collect YES is_eph_cull NO  eph_flag 32768 eph_flag_ EFFICIENCY_COLLECT
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SD eph_flag_ EC
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph 10 ext  1 flg  0 eph_ EPH_SAVENORM is_eph_collect YES is_eph_cull NO  eph_flag 32768 eph_flag_ EFFICIENCY_COLLECT
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SD eph_flag_ EC
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  3 ext  1 flg  0 eph_ EPH_NEDEP is_eph_collect NO  is_eph_cull NO  eph_flag 0 eph_flag_ .
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SA eph_flag_   
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph 10 ext  1 flg  0 eph_ EPH_SAVENORM is_eph_collect YES is_eph_cull NO  eph_flag 32768 eph_flag_ EFFICIENCY_COLLECT
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SD eph_flag_ EC
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  3 ext  1 flg  0 eph_ EPH_NEDEP is_eph_collect NO  is_eph_cull NO  eph_flag 0 eph_flag_ .
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SA eph_flag_   
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton_eph_flag@3007]  gen  0 eph  3 ext  1 flg  0 eph_ EPH_NEDEP is_eph_collect NO  is_eph_cull NO  eph_flag 0 eph_flag_ .
    2025-06-10 21:49:17.300 INFO  [4016991] [SEvt::finalPhoton@2954]  before:ctx.p.abbrev_() SA eph_flag_   



DONE : pass eph_stats via U4RecorderAnaMgr to U4Recorder
-----------------------------------------------------------------------------

::
 
    327 SProcessHits_EPH* junoSD_PMT_v2::getProcessHitsDebug() const
    328 {
    329     return m_eph_stats ;
    330 }

    (ok) A[blyth@localhost junosw]$ jgr getProcessHitsDebug
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        SProcessHits_EPH* getProcessHitsDebug() const ;  
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:SProcessHits_EPH* junoSD_PMT_v2::getProcessHitsDebug() const 
    (ok) A[blyth@localhost junosw]$ 



::

     96 inline int spho::gen() const { return int(uc4.x); }
     97 inline int spho::eph() const { return int(uc4.y); }
     98 inline int spho::ext() const { return int(uc4.z); }
     99 inline int spho::flg() const { return int(uc4.w); }




DONE : ipc A:B iterate to get the EC/EX flagmask to correspond  
----------------------------------------------------------------

Currently are putting the EC EX into photon.flagmask on A side only. 

* DONE: use the EPH info to do the same on the B side

  * start by getting eph_stats metadata into the SEvt 

* after flagmask is agreeing can move to flag 


::

    In [7]: a.fmtab[:20]
    Out[7]: 
    array([['TO|BT|SA', '326185'],

           ['EC|TO|BT|SD', '312177'],

           ['TO|BT|SR|SA', '56805'],
           ['TO|BT|BR|SR|SA', '53334'],
           ['TO|BT|BR|SA', '42888'],
           ['TO|BT|BR|AB', '37716'],
           ['EC|TO|BT|BR|SD', '21709'],
           ['TO|BT|BR|SA|SC', '20683'],
           ['TO|BT|BR|SC|AB', '15776'],
           ['EC|TO|BT|BR|SD|SC', '13679'],
           ['TO|BT|AB', '12490'],
           ['TO|BT|BR|SR|SA|SC', '8668'],

           ['EX|TO|BT|SD', '7448'],                 ## 312177 + 7448 = 319625

           ['TO|BT|BR|SD', '6431'],
           ['TO|BT|SR|AB', '5622'],
           ['TO|BT|BR|DR|SA', '4305'],
           ['TO|BT|SR|SA|SC', '3756'],
           ['TO|BT|BR|SR|AB', '3594'],
           ['TO|BT|BR|SR|DR|SA', '3313'],
           ['TO|BT|BR|DR|SA|SC', '3167']], dtype='<U26')


Before implementing the EC/EX from ProcessHits info::

    In [8]: b.fmtab[:20]
    Out[8]: 
    array([['TO|BT|SA', '327349'],

           ['TO|BT|SD', '319936'],             ####################### ^^^^^^

           ['TO|BT|SR|SA', '56405'],
           ['TO|BT|BR|SR|SA', '52585'],
           ['TO|BT|BR|SA', '42904'],
           ['TO|BT|BR|AB', '36283'],
           ['TO|BT|BR|SD', '29433'],
           ['TO|BT|BR|SA|SC', '21160'],
           ['TO|BT|BR|SC|AB', '15927'],
           ['TO|BT|BR|SD|SC', '15915'],
           ['TO|BT|AB', '12574'],
           ['TO|BT|BR|SR|SA|SC', '8949'],
           ['TO|BT|SR|AB', '5599'],
           ['TO|BT|BR|DR|SA', '4343'],
           ['TO|BT|BR|SR|AB', '3628'],
           ['TO|BT|SR|SA|SC', '3544'],
           ['TO|BT|BR|SR|DR|SA', '3489'],
           ['TO|BT|BR|DR|SA|SC', '3259'],
           ['TO|BT|BR|SR|SD', '2971'],
           ['TO|BT|BR|SR|SC|AB', '2883']], dtype='<U23')




DONE : ipc onto PMT shows flagmask agreement using the ProcessHits_EPH setting of EC/EX
-----------------------------------------------------------------------------------------

::

    In [1]: a.fmtab[:20]
    Out[1]: 
    array([['TO|BT|SA', '326185'],
           ['EC|TO|BT|SD', '312177'],
           ['TO|BT|SR|SA', '56805'],
           ['TO|BT|BR|SR|SA', '53334'],
           ['TO|BT|BR|SA', '42888'],
           ['TO|BT|BR|AB', '37716'],
           ['EC|TO|BT|BR|SD', '21709'],
           ['TO|BT|BR|SA|SC', '20683'],
           ['TO|BT|BR|SC|AB', '15776'],
           ['EC|TO|BT|BR|SD|SC', '13679'],
           ['TO|BT|AB', '12490'],
           ['TO|BT|BR|SR|SA|SC', '8668'],
           ['EX|TO|BT|SD', '7448'],
           ['TO|BT|BR|SD', '6431'],
           ['TO|BT|SR|AB', '5622'],
           ['TO|BT|BR|DR|SA', '4305'],
           ['TO|BT|SR|SA|SC', '3756'],
           ['TO|BT|BR|SR|AB', '3594'],
           ['TO|BT|BR|SR|DR|SA', '3313'],
           ['TO|BT|BR|DR|SA|SC', '3167']], dtype='<U26')

    In [2]: b.fmtab[:20]
    Out[2]: 
    array([['TO|BT|SA', '327349'],
           ['EC|TO|BT|SD', '312604'],
           ['TO|BT|SR|SA', '56405'],
           ['TO|BT|BR|SR|SA', '52585'],
           ['TO|BT|BR|SA', '42904'],
           ['TO|BT|BR|AB', '36283'],
           ['EC|TO|BT|BR|SD', '23149'],
           ['TO|BT|BR|SA|SC', '21160'],
           ['TO|BT|BR|SC|AB', '15927'],
           ['EC|TO|BT|BR|SD|SC', '13965'],
           ['TO|BT|AB', '12574'],
           ['TO|BT|BR|SR|SA|SC', '8949'],
           ['EX|TO|BT|SD', '7332'],
           ['EX|TO|BT|BR|SD', '6284'],
           ['TO|BT|SR|AB', '5599'],
           ['TO|BT|BR|DR|SA', '4343'],
           ['TO|BT|BR|SR|AB', '3628'],
           ['TO|BT|SR|SA|SC', '3544'],
           ['TO|BT|BR|SR|DR|SA', '3489'],
           ['TO|BT|BR|DR|SA|SC', '3259']], dtype='<U26')



MAYBE : SD scrubbing in the flagmask ?
---------------------------------------




WIP : Getting the EPH stats saved with the SEvt
--------------------------------------------------

::

    jcv PMTSDMgr

    BP=junoSD_PMT_v2::junoSD_PMT_v2 ipc run

    (gdb) bt
    #0  junoSD_PMT_v2::junoSD_PMT_v2 (this=0xa2722e0, name="PMTSDMgr", opticksMode=3) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:80
    #1  0x00007fffbd68bdec in PMTSDMgr::getSD (this=0x6684130) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:92
    #2  0x00007fffbdd66514 in LSExpDetectorConstruction::getPMTSD (this=0xa231030, sd_name="PMTSDMgr") at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1133
    #3  0x00007fffbdd60230 in LSExpDetectorConstruction::Construct (this=0xa231030) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:283
    #4  0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #5  0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #6  0x00007fffd485eb1b in DetSimAlg::initialize (this=0x65d2e70) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #7  0x00007fffd0adeb56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.a

    gdb) f 0
    #0  junoSD_PMT_v2::junoSD_PMT_v2 (this=0xa2722e0, name="PMTSDMgr", opticksMode=3) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:80
    80	    ,m_jpmt_opticks(new junoSD_PMT_v2_Opticks(this))
    (gdb) f 1
    #1  0x00007fffbd68bdec in PMTSDMgr::getSD (this=0x6684130) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:92
    92	        junoSD_PMT_v2* sd = new junoSD_PMT_v2(objName(), m_opticksMode);
    (gdb) f 2
    #2  0x00007fffbdd66514 in LSExpDetectorConstruction::getPMTSD (this=0xa231030, sd_name="PMTSDMgr") at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1133
    1133	            sd = sde->getSD();
    (gdb) f 3
    #3  0x00007fffbdd60230 in LSExpDetectorConstruction::Construct (this=0xa231030) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:283
    283	      G4VSensitiveDetector* not_a_leak = getPMTSD("PMTSDMgr");
    (gdb) f 4
    #4  0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    (gdb) 



Doing this from::

    jcv U4RecorderAnaMgr

    049 void U4RecorderAnaMgr::EndOfEventAction(const G4Event* evt)
     50 {
     51     junoSD_PMT_v2_Opticks* jpmt_ok = junoSD_PMT_v2_Opticks::Get();
     52     SProcessHits_EPH* eph_stats = jpmt_ok ? jpmt_ok->getProcessHits_EPH() : nullptr ;
     53     NP* eph_meta = eph_stats ? eph_stats->get_meta_array() : nullptr ;
     54     std::cout
     55         << "U4RecorderAnaMgr::EndOfEventAction"
     56         << " eph_meta "  << ( eph_meta  ? eph_meta->sstr() : "-"   ) << "\n"
     57         << " eph_stats " << ( eph_stats ? "YES"            : "NO " ) << "\n"
     58         << ( eph_stats ? eph_stats->desc() : "" )
     59         << "\n"
     60         ;
     61     
     62     if(eph_meta) m_recorder->addProcessHits_EPH(eph_meta);
     63 }


Problem is thats called after the SEvt::save.



junoSD_PMT_v2::EndOfEvent
----------------------------

That "hitCollection 742977" looks too much::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 742977 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4RecorderAnaMgr::EndOfEventAction eph_meta (1, )
     eph_stats YES
    SProcessHits_EPH::desc
     ProcessHits_count   2542310
     ProcessHits_true     363159
     ProcessHits_false   2179151
     SaveNormHit_count    363159
     SaveMuonHit_count         0
               EPH_UNSET       0
                EPH_NDIS       0
                EPH_NOPT       0
               EPH_NEDEP 2156552
              EPH_NBOUND    5153
               EPH_NPROC       0
             EPH_NDETECT       0
             EPH_NDECULL   17446
              EPH_YMERGE       0
               EPH_YSAVE       0
            EPH_SAVENORM  363159
            EPH_SAVEMUON       0


::

    363159 + 363159*1.2 = 798949.8

    In [1]: 363159 + 363159*1.2
    Out[1]: 798949.8

    In [2]: 742977/363159
    Out[2]: 2.0458724690837897



Added some stats collection : shows that are adding both CPU and GPU hits into the collection in mode 3
----------------------------------------------------------------------------------------------------------


export OPTICKS_HIT_MASK=SD  ## current default
--------------------------------------------------

::

    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 742977 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4RecorderAnaMgr::EndOfEventAction eph_meta (1, )
     eph_stats YES
    SProcessHits_EPH::desc
                 ProcessHits_count 2542310
                  ProcessHits_true  363159
                 ProcessHits_false 2179151
                 SaveNormHit_count  363159
                 SaveMuonHit_count       0
                         EPH_UNSET       0
                          EPH_NDIS       0
                          EPH_NOPT       0
                         EPH_NEDEP 2156552
                        EPH_NBOUND    5153
                         EPH_NPROC       0
                       EPH_NDETECT       0
                       EPH_NDECULL   17446
                        EPH_YMERGE       0
                         EPH_YSAVE       0
                      EPH_SAVENORM  363159
                      EPH_SAVEMUON       0
         EndOfEvent_Simulate_count       1
      EndOfEvent_Simulate_EGPU_hit  379818
    EndOfEvent_hitCollection_entries0  363159
    EndOfEvent_hitCollection_entries1  742977


    In [2]: 363159 + 379818
    Out[2]: 742977

    In [3]: 379818/363159
    Out[3]: 1.0458724690837897



export OPTICKS_HIT_MASK=EC
----------------------------


    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 723521 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    U4RecorderAnaMgr::EndOfEventAction eph_meta (1, )
     eph_stats YES
    SProcessHits_EPH::desc
                 ProcessHits_count 2542310
                  ProcessHits_true  363159
                 ProcessHits_false 2179151
                 SaveNormHit_count  363159
                 SaveMuonHit_count       0
                         EPH_UNSET       0
                          EPH_NDIS       0
                          EPH_NOPT       0
                         EPH_NEDEP 2156552
                        EPH_NBOUND    5153
                         EPH_NPROC       0
                       EPH_NDETECT       0
                       EPH_NDECULL   17446
                        EPH_YMERGE       0
                         EPH_YSAVE       0
                      EPH_SAVENORM  363159
                      EPH_SAVEMUON       0
         EndOfEvent_Simulate_count       1
      EndOfEvent_Simulate_EGPU_hit  360362
    EndOfEvent_hitCollection_entries0  363159
    EndOfEvent_hitCollection_entries1  723521


::

    ----- repr(abh) 


    SABHit  a_nhit : (  360362 +-  600 )  b_nhit:(   363159 +-  602 )  a/b: (  0.992 +-  0.003 )  b/a: (  1.008 +-  0.003)  [assume uncorr.]


    ]----- repr(abh) 



HUH : MOVING FROM U4RecorderAnaMgr TO  junoSD_PMT_v2_Opticks MAKES EndOfEvent_hitCollection_entries1 GO TO ZERO ? 
--------------------------------------------------------------------------------------------------------------------

* PILOT error the save happened before the count 

::

    junoSD_PMT_v2_Opticks::EndOfEvent_Simulate_recordStats eventID 0 recorder YES eph_meta (1, )
    SProcessHits_EPH::desc
                 ProcessHits_count 2542310
                  ProcessHits_true  363159
                 ProcessHits_false 2179151
                 SaveNormHit_count  363159
                 SaveMuonHit_count       0
                         EPH_UNSET       0
                          EPH_NDIS       0
                          EPH_NOPT       0
                         EPH_NEDEP 2156552
                        EPH_NBOUND    5153
                         EPH_NPROC       0
                       EPH_NDETECT       0
                       EPH_NDECULL   17446
                        EPH_YMERGE       0
                         EPH_YSAVE       0
                      EPH_SAVENORM  363159
                      EPH_SAVEMUON       0
        Initialize_G4HCofThisEvent       1
       EndOfEvent_Simulate_eventID       0
         EndOfEvent_Simulate_count       1
      EndOfEvent_Simulate_EGPU_hit  360362
    EndOfEvent_hitCollection_entries0  363159
    EndOfEvent_hitCollection_entries1       0    ## HUH : WHY THIS GONE TO ZERO ? 
    EndOfEvent_Simulate_merged_count       0
    EndOfEvent_Simulate_savehit_count  360362
    EndOfEvent_Simulate_merged_total       0
    EndOfEvent_Simulate_savehit_total  360362





How does collection clearing happen between events ? 
-----------------------------------------------------

::

    81         void setMerger(PMTHitMerger* phm) { m_pmthitmerger=phm; }

    (ok) A[blyth@localhost g4cx]$ jgr setMerger
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setMerger(PMTHitMerger* phm) { m_pmthitmerger=phm; }
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setMerger(pmthitmerger);
    (ok) A[blyth@localhost junosw]$ 


::

    011 class PMTSDMgr: public ISensitiveDetectorElement,
     12                 public ToolBase {
     13 public:
     14     PMTSDMgr(const std::string& name);
     15     ~PMTSDMgr();
     16 
     17     // can only call once
     18     virtual G4VSensitiveDetector* getSD();
     19     // return the Hit Merger;
     20     PMTHitMerger* getPMTMerger() { return m_pmthitmerger; }
     21     IPMTParamSvc* gerPMTParSvc(){ return m_pmt_param_svc;}
     22     IPMTSimParamSvc* getPMTSimParamSvc() {return m_pmt_sim_param_svc; }
     23 private:



     91     } else if (m_pmt_sd == "junoSD_PMT_v2") {
     92         junoSD_PMT_v2* sd = new junoSD_PMT_v2(objName(), m_opticksMode);
     93         // As a merger is attached to a specific SD, so also create new merger for the new SD.
     94         PMTHitMerger* pmthitmerger = new PMTHitMerger();
     95 
     96         if (m_pmthitmerger) {
     97             G4cout << "WARNING: PMTSDMgr::m_pmthitmerger already exists." << G4endl;
     98         }
     99 
    100         m_pmthitmerger = pmthitmerger;
    101 
    102         sd->setCEMode(m_ce_mode);
    103         // if flat mode
    104         sd->setCEFlatValue(m_ce_flat_value);
    105         // func mode
    106         sd->setCEFunc(m_ce_func, m_ce_func_params);
    107         sd->setMergeFlag(m_merge_flag);
    108         sd->setMergeWindows(m_time_window);
    109         sd->setMerger(pmthitmerger);
    110         sd->setPMTParamSvc(m_pmt_param_svc);
    111         sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    112         sd->setHitType(m_hit_type);
    113         //use pmt sim svc
    114         sd->setUsePmtSimSvc(m_use_pmtsimsvc);
    115         // configure the merger
    116         pmthitmerger->setMergeFlag(m_merge_flag);
    117         pmthitmerger->setTimeWindow(m_time_window);
    118 


jcv JCV
---------

::

    jcv PMTHitMerger
    jcv U4RecorderAnaMgr
    jcv PMTSDMgr          ## where SD and merger created
    jcv junoHit_PMT       ## collection typedef   junoHit_PMT_Collection : G4THitsCollection<junoHit_PMT>

    jcv junoSD_PMT_v2
    jcv junoSD_PMT_v2_Opticks
  
    jcv U4RecorderAnaMgr junoSD_PMT_v2 junoSD_PMT_v2_Opticks


How to handle GPU and CPU hits in mode 3/2/1/0 ?  
--------------------------------------------------

* https://geant4.kek.jp/lxr/search?string=collectionName
* https://geant4.kek.jp/lxr/source/digits_hits/detector/include/G4CollectionNameVector.hh

::

     37 class G4CollectionNameVector : public std::vector<G4String>
     38 {
     39  public:
     40   G4CollectionNameVector() {}
     41   virtual ~G4CollectionNameVector() {}
     42 
     43   void insert(const G4String& str) { push_back(str); }
     44 };
     45 



How is merger connected to collection ? It saves to one associated collection
--------------------------------------------------------------------------------

* junoSD_PMT_v2::Initialize associates merger to collection controlled by m_hit_type 

* HMM: in mode 1 or mode 2 there is no problem with current approach of GPU, CPU
  hits going to "hitCollection"

* in mode 3 currently both GPU and CPU hits go to "hitCollection" doubling up
 
  * in mode 3 need to collect into "hitCollection" and "hitCollection_alt"
    


::

    BP=PMTHitMerger::init ipc 

::

    (gdb) bt
    #0  PMTHitMerger::init (this=0xa67fac0, hitcol=0xf33c08c0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:128
    #1  0x00007fffbd6f28b6 in junoSD_PMT_v2::Initialize (this=0xa272600, HCE=0xf33c0420) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:194
    #2  0x00007fffc4d71cfa in G4SDStructure::Initialize(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #3  0x00007fffc4d6f6bc in G4SDManager::PrepareNewEvent() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #4  0x00007fffc676b289 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #5  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x65dea00, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29



     168 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     169 {
     170     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     171     m_eventID = event->GetEventID() ;
     172 
     173     m_merge_count = 0 ;
     174     if (m_debug) {
     175         G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
     176     }
     177     hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
     178     hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);
     179 
     180     // changed from a static variable to a normal variable by Jillings, August 2, 2006
     181     int HCID = -1;
     182     if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection);
     183     HCE->AddHitsCollection( HCID, hitCollection );
     184 
     185     HCID = -1;
     186     if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection_muon);
     187     HCE->AddHitsCollection( HCID, hitCollection_muon );
     188 
     189     m_pmtid2idincol.clear();
     190     assert( m_pmtid2idincol.size() == 0 );
     191 
     192     if (m_pmthitmerger) {
     193         if (m_hit_type == 1) {
     194             m_pmthitmerger->init(hitCollection);
     195         } else if (m_hit_type == 2) {
     196             // TODO
     197             m_pmthitmerger->init(hitCollection_muon);
     198         } else {
     199             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     200         }
     201     }
     202     // make sure the PMT merger exists.
     203     assert(m_pmthitmerger);
     204 
     205 
     206 #ifdef WITH_G4CXOPTICKS
     207     m_jpmt_opticks->Initialize(HCE, m_eventID);
     208 #endif
     209 #ifdef WITH_G4CXOPTICKS_EPH
     210     m_eph_stats->Initialize_G4HCofThisEvent += 1 ;
     211 #endif
     212 
     213 
     214 }






    125 bool
    126 PMTHitMerger::init(junoHit_PMT_Collection* hitcol) {
    127 
    128   assert(m_time_window > 0);
    129 
    130   // during event begin, retrieve the hit collection
    131   hitCollection = hitcol;
    132 
    133   // clear all vectors but saving pmts number
    134 
    135   std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.begin();
    136   for ( ; pmt != m_PMThit.end(); ++pmt) pmt->second.clear();
    137 
    138   return true;
    139 }


     79 bool
     80 PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
     81   if (not hasNormalHitType()) {
     82     std::cerr << "WARN: PMTHitMerger don't use normal hit type, however a normal hit is inserted."
     83           << std::endl;
     84     return false;
     85   }
     86 
     87   if (m_merge_flag) {
     88     int pmtid = hit_photon->GetPMTID();
     89     std::map<int, std::vector<junoHit_PMT*> >::iterator pmt = m_PMThit.find(pmtid);
     90     if (pmt == m_PMThit.end()) {
     91       m_PMThit[pmtid].clear();
     92       m_PMThit[pmtid].push_back(hit_photon);
     93     }
     94     else pmt->second.push_back(hit_photon);
     95   }
     96   hitCollection->insert(hit_photon);
     97 
     98   return true;
     99 }



* Where is the bulk hit collection::

    248 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    249 {
    250     bool merged = m_merger->getMergeFlag() ? m_merger->doMerge(hit->sensor_identifier, hit->time) : false ;
    251     if(merged)
    252     {
    253         merged_count += 1 ;
    254     }
    255     else
    256     {
    257         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    258         savehit_count += 1 ;
    259         m_merger->saveHit(hit_photon);
    260     }
    261 }



 

HMM : DONT RELY ON --opticks-anamgr U4RecorderAnaMgr
------------------------------------------------------



Where do hits get deleted ?  By deletion of G4HCofThisEvent by G4Event 
-----------------------------------------------------------------------

::

    BP="junoHit_PMT::operator delete" ipc

    gdb) bt
    #0  junoHit_PMT::operator delete (aHit=0x675bbb0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:163
    #1  0x00007fffbd6dcb62 in junoHit_PMT::~junoHit_PMT (this=0x675bbb0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoHit_PMT.cc:32
    #2  0x00007fffbd6f10aa in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xf33bda50, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:165
    #3  0x00007fffbd6f111c in G4THitsCollection<junoHit_PMT>::~G4THitsCollection (this=0xf33bda50, __in_chrg=<optimized out>)
        at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/include/Geant4/G4THitsCollection.hh:168
    #4  0x00007fffc4d7b0fb in G4HCofThisEvent::~G4HCofThisEvent() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #5  0x00007fffc676a0d3 in G4Event::~G4Event() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffc68096b8 in G4RunManager::StackPreviousEvent(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007fffe1a6c6db in G4SvcRunManager::SimulateEvent (this=0x65ab4a0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:32
    #8  0x00007fffd485ed3e in DetSimAlg::execute (this=0x6610b40) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #9  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


    gdb) f 7
    #7  0x00007fffe1a6c6db in G4SvcRunManager::SimulateEvent (this=0x65ab4a0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:32
    32	    StackPreviousEvent(currentEvent);
    (gdb) list
    27	bool G4SvcRunManager::SimulateEvent(int i_event) {
    28	    currentEvent = GenerateEvent(i_event);
    29	    eventManager->ProcessOneEvent(currentEvent);
    30	    AnalyzeEvent(currentEvent);
    31	    UpdateScoring();
    32	    StackPreviousEvent(currentEvent);
    33	    currentEvent = 0;
    34	
    35	    if(runAborted) return false;
    36	    return true;
    (gdb) 




junoHit_PMT_Collection : G4THitsCollection<junoHit_PMT> wants to be deleted
----------------------------------------------------------------------------------


::

    A[blyth@localhost junosw]$ jgr junoHit_PMT_Collection
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriter.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/DataModelWriterWithSplit.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/MuonToySim.cc:    junoHit_PMT_Collection* col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:    junoHit_PMT_Collection* col = 0;
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        col = (junoHit_PMT_Collection*)(HCE->GetHC(CollID));
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool init(junoHit_PMT_Collection* hitcol);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:  junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:// junoHit_PMT_Collection is a vector of hits
    ./Simulation/DetSimV2/PMTSim/include/junoHit_PMT.hh:typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT.hh:    junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection*      getHitCollection(){      return hitCollection ; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        junoHit_PMT_Collection* hitCollection;
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::init(junoHit_PMT_Collection* hitcol) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT.cc:  hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
    A[blyth@localhost junosw]$ 


::

    146 // junoHit_PMT_Collection is a vector of hits
    147 typedef G4THitsCollection<junoHit_PMT> junoHit_PMT_Collection;



* https://apc.u-paris.fr/~franco/g4doxy/html/classG4THitsCollection.html




NEED control for opticksMode:3 to pick between GPU and CPU hits  
----------------------------------------------------------------

HMM : I thought that was there previously. 



HCE : Initialize CALL ORDER 
-----------------------------

::

    0175 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     176 {
     177     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     178     m_eventID = event->GetEventID() ;
     179 
     180     m_merge_count = 0 ;
     181     if (m_debug) {
     182         G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
     183     }
     184     hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
     185     hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);
     186 
     187     // changed from a static variable to a normal variable by Jillings, August 2, 2006
     188     int HCID = -1;
     189     if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection);
     190     HCE->AddHitsCollection( HCID, hitCollection );
     191 
     192     HCID = -1;
     193     if(HCID<0) HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitCollection_muon);
     194     HCE->AddHitsCollection( HCID, hitCollection_muon );
     195 
     196     m_pmtid2idincol.clear();
     197     assert( m_pmtid2idincol.size() == 0 );
     198 
     199     if (m_pmthitmerger) {
     200         if (m_hit_type == 1) {
     201             m_pmthitmerger->init(hitCollection);
     202         } else if (m_hit_type == 2) {
     203             // TODO
     204             m_pmthitmerger->init(hitCollection_muon);
     205         } else {
     206             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     207         }
     208     }
     209     // make sure the PMT merger exists.
     210     assert(m_pmthitmerger);
     211 
     212 
     213 #ifdef WITH_G4CXOPTICKS
     214     m_jpmt_opticks->Initialize(HCE, m_eventID);
     215 #endif
     216 
     217 }


    115 void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
    116 {
    117     G4CXOpticks* gx = G4CXOpticks::Get() ;
    118     gx->SensitiveDetector_Initialize(eventID) ;
    119 
    120     //if( (m_opticksMode == 0) or (m_opticksMode == 1) ) SEvt::Get_ECPU()->beginOfEvent(eventID);
    121 
    122     LOG(LEVEL)
    123         << " opticksMode " << m_opticksMode
    124         << " eventID " << eventID
    125         << " LEVEL " << LEVEL << ":" << plog::severityToString(LEVEL)
    126         ;
    127 }

    609 void G4CXOpticks::SensitiveDetector_Initialize(int eventID)
    610 {
    611     LOG(LEVEL) << " eventID " << eventID ;
    612     U4Recorder* recorder = U4Recorder::Get();
    613     if(recorder)
    614     {
    615         recorder->BeginOfEventAction_(eventID);
    616     }
    617 }


     345 void U4Recorder::BeginOfEventAction(const G4Event*)
     346 {
     347     LOG(fatal) << "CHANGE TO U4Recorder::BeginOfEventAction_ : see G4CXOpticks::SensitiveDetector_EndOfEvent " ;
     348     assert(0);
     349 }

     357 void U4Recorder::BeginOfEventAction_(int eventID_)
     358 {
     359     eventID = eventID_ ;
     360     LOG(info) << " eventID " << eventID ;
     361     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     362     sev->beginOfEvent(eventID);
     363 }


    1556 void SEvt::beginOfEvent(int eventID)
    1557 {
    1558     if(isFirstEvtInstance() && eventID == 0) BeginOfRun() ;
    1559     if(eventID == 0) SetRunProf( isEGPU() ? "SEvt__beginOfEvent_FIRST_EGPU" : "SEvt__beginOfEvent_FIRST_ECPU" ) ;
    1560 
    1561     setStage(SEvt__beginOfEvent);
    1562     sprof::Stamp(p_SEvt__beginOfEvent_0);
    1563 
    1564     LOG(LEVEL) << " eventID " << eventID ;   // 0-based
    1565     setIndex(eventID);
    1566 
    1567 
    1568     LOG_IF(info, LIFECYCLE) << id() ;
    1569 
    1570     clear_output();   // output vectors and fold : excluding gensteps as thats input
    1571 
    1572     addInputGenstep();  // does genstep setup for simtrace, input photon and torch running
    1573 
    1574     setMeta<int>("NumPhotonCollected", numphoton_collected );
    1575     setMeta<int>("NumGenstepCollected", numgenstep_collected );
    1576     setMeta<int>("MaxBounce", evt->max_bounce );
    1577 
    1578     LOG_IF(info, LIFECYCLE)
    1579         << " NumPhotonCollected " << numphoton_collected
    1580         << " NumGenstepCollected " << numgenstep_collected
    1581         << " MaxBounce " << evt->max_bounce
    1582         ;
    1583 
    1584     sprof::Stamp(p_SEvt__beginOfEvent_1);
    1585 }




HCE : EndOfEvent CALL ORDER 
-----------------------------


::

    1080 void junoSD_PMT_v2::EndOfEvent(G4HCofThisEvent* HCE)
    1081 {
    1082 #ifdef WITH_G4CXOPTICKS
    1083     m_jpmt_opticks->EndOfEvent(HCE, m_eventID );
    1084 #endif
    1085     G4cout << "junoSD_PMT_v2::EndOfEvent" << desc() << G4endl ;
    1086 }


    147 void junoSD_PMT_v2_Opticks::EndOfEvent(G4HCofThisEvent*, int eventID )
    148 {
    149     G4CXOpticks* gx = G4CXOpticks::Get() ;
    150     gx->SensitiveDetector_EndOfEvent(eventID) ;
    151     
    152     if(m_merger == nullptr) m_merger = m_jpmt->getMerger();
    153 
    154     LOG(LEVEL) << "[ " << m_jpmt->desc() ;
    155 
    156     LOG(LEVEL) << std::endl << m_jpmt->descHitCollection() ;
    157 
    158     
    159     if(m_gpu_simulation)
    160     {
    161         EndOfEvent_Simulate(eventID) ;
    162     }
    163 
    164     LOG(LEVEL) << "] " << m_jpmt->desc() ;
    165 }


    669 void G4CXOpticks::SensitiveDetector_EndOfEvent(int eventID)
    670 {
    671     LOG(LEVEL) << " eventID " << eventID ;
    672     U4Recorder* recorder = U4Recorder::Get();
    673     if(recorder)
    674     {
    675         recorder->EndOfEventAction_(eventID);
    676     }
    677 }


    0374 void U4Recorder::EndOfEventAction_(int eventID_)
     375 {
     376     assert( eventID == eventID_ );
     377     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     378 
     379     #if defined(WITH_PMTSIM) && defined(POM_DEBUG)
     380         NP* mtda = PMTSim::ModelTrigger_Debug_Array();
     381         std::string name = mtda->get_meta<std::string>("NAME", "MTDA.npy") ;
     382         sev->add_array( name.c_str(), mtda );
     383     #else
     384         LOG(LEVEL) << "not-(WITH_PMTSIM and POM_DEBUG)"  ;
     385     #endif
     386 
     387 
     388     // adding to extrafold
     389     sev->add_array("TRS.npy", U4VolumeMaker::GetTransforms() );
     390     sev->add_array("U4R.npy", MakeMetaArray() );
     391     sev->addEventConfigArray();
     392 
     393     sev->gather() ;             // now gathers into fold, separate from topfold
     394 
     395     // ~/j/issues/jok-tds-B-side-missing-NPFold-concat.rst
     396     sev->topfold->concat();         // in this trivial one fold case just copies pointers and arranges skipdelete on fold arrays
     397     sev->topfold->clear_subfold();
     398 
     399     sev->endOfEvent(eventID_);  // does save and clear
     400 
     401     const char* savedir = sev->getSaveDir() ;
     402     LOG(LEVEL) << " savedir " << ( savedir ? savedir : "-" );
     403     SaveMeta(savedir);
     404 }


    177 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    178 {
    179     G4CXOpticks* gx = G4CXOpticks::Get() ;
    180 
    181     bool reset_ = false ;
    182     gx->simulate(eventID, reset_ ) ;
    183 
    184     assert( m_merger );
    185 
    186     std::stringstream ss ;
    187     unsigned num_hit = SEvt::GetNumHit_EGPU() ;
    188     LOG(LEVEL)
    189         << "[ eventID " << eventID
    190         << " " << gx->descSimulate()
    191         << " num_hit " << num_hit
    192         ;
    193 
    194     int merged_count(0);
    195     int savehit_count(0);
    196     bool way_enabled = false ;
    197 
    198     U4Hit hit ;
    199     U4HitExtra hit_extra ;
    200     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    201     for(int idx=0 ; idx < int(num_hit) ; idx++)
    202     {
    203         U4HitGet::FromEvt_EGPU(hit, idx);
    204         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    205         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    206     }
    207     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;
    208     LOG(LEVEL)
    209         << "]"
    210         << " num_hit " << num_hit
    211         << ( merged_count > 0 ? " MERGED " : "" )
    212         << " merged_count  " << merged_count 
    213         << " savehit_count  " << savehit_count
    214         << " m_merged_total " << m_merged_total
    215         << " m_savehit_total " << m_savehit_total
    216         << " m_opticksMode " << m_opticksMode
    217         ;
    218 
    219     m_merged_total += merged_count ;
    220     m_savehit_total += savehit_count ;
    221     
    222     gx->reset(eventID) ;
    223 }





FIXED : directory of extra is messed up
-----------------------------------------

::

    A[blyth@localhost ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8]$ cd B000/
    A[blyth@localhost B000]$ l
    total 12
    0 drwxr-xr-x. 2 blyth blyth 125 Jun 11 10:12 .
    4 -rw-r--r--. 1 blyth blyth 245 Jun 11 10:12 SProcessHits_EPH_meta.txt
    4 -rw-r--r--. 1 blyth blyth 130 Jun 11 10:12 SProcessHits_EPH_names.txt
    4 -rw-r--r--. 1 blyth blyth 132 Jun 11 10:12 SProcessHits_EPH.npy
    0 drwxr-xr-x. 3 blyth blyth  18 Jun 11 09:59 ..
    0 -rw-r--r--. 1 blyth blyth   0 Jun 11 09:59 SProcessHits_EPH
    A[blyth@localhost B000]$ cat SProcessHits_EPH_names.txt
    EPH_UNSET
    EPH_NDIS
    EPH_NOPT
    EPH_NEDEP
    EPH_NBOUND
    EPH_NPROC
    EPH_NDETECT
    EPH_NDECULL
    EPH_YMERGE
    EPH_YSAVE
    EPH_SAVENORM
    EPH_SAVEMUON
    A[blyth@localhost B000]$ cat SProcessHits_EPH_meta.txt
    ProcessHits_count:2542310
    ProcessHits_true:363159
    ProcessHits_false:2179151
    SaveNormHit_count:363159
    SaveMuonHit_count:0
    UNSET:0
    NDIS:0
    NOPT:0
    NEDEP:2156552
    NBOUND:5153
    NPROC:0
    NDETECT:0
    NDECULL:17446
    YMERGE:0
    YSAVE:0
    SAVENORM:363159
    SAVEMUON:0
    A[blyth@localhost B000]$ pwd
    /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8/B000/ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8/B000
    A[blyth@localhost B000]$ pwd
    /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8/B000/ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8/B000
    A[blyth@localhost B000]$ 





call order complications may have been stepped on by changes to U4RecorderAnaMgr
----------------------------------------------------------------------------------

::

    620 /**
    621 G4CXOpticks::SensitiveDetector_EndOfEvent
    622 -------------------------------------------
    623 
    624 Optional lifecycle method intended to be called from Geant4 integration
    625 G4VSensitiveDetector::EndOfEvent
    626 
    627 The Geant4 call order gleaned from g4-cls G4EventManager
    628 with the related calls to G4CXOpticks and U4Recorder
    629 that were used previously::
    630 
    631     G4VSensitiveDetector::Initialize
    632 
    633     G4UserEventAction::BeginOfEventAction  ==> U4Recorder::BeginOfEventAction
    634 
    635 
    636     G4VSensitiveDetector::EndOfEvent       ==> G4CXOpticks::simulate : AS HITS NEEDED HERE
    637 
    638     G4UserEventAction::EndOfEventAction    ==> U4Recorder::EndOfEventAction
    639 
    640 
    641 The old call order presented complications as the simulate call needs the gensteps
    642 from the SEvt::ECPU that is only wrapped up at U4Recorder::EndOfEventAction.
    643 This SensitiveDetector pair of methods enables rearranging the order::
    644 
    645     G4VSensitiveDetector::Initialize       ==> U4Recorder::BeginOfEventAction
    646 
    647     G4UserEventAction::BeginOfEventAction
    648 
    649 
    650     G4VSensitiveDetector::EndOfEvent       ==> U4Recorder::EndOfEventAction,
    651                                            ==> G4CXOpticks::simulate : AS HITS NEEDED HERE
    652 
    653     G4UserEventAction::EndOfEventAction
    654 
    655 Note that the Stepping and Tracking actions handled by
    656 the U4Recorder can proceed unchanged by this.
    657 
    658 **/
    659 
    660 void G4CXOpticks::SensitiveDetector_EndOfEvent(int eventID)
    661 {
    662     LOG(LEVEL) << " eventID " << eventID ;
    663     U4Recorder* recorder = U4Recorder::Get();
    664     if(recorder)
    665     {
    666         recorder->EndOfEventAction_(eventID);
    667     }
    668 }


EVTMAX 10
----------

::

    A[blyth@localhost ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8]$ grep hit B00?/SProcessHits_EPH_meta.txt
    B000/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360362
    B000/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363159
    B000/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723521
    B000/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360362
    B000/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:360362
    B001/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360426
    B001/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363147
    B001/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723573
    B001/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360426
    B001/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:720788
    B002/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360078
    B002/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363974
    B002/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:724052
    B002/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360078
    B002/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:1080866
    B003/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360223
    B003/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:362195
    B003/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:722418
    B003/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360223
    B003/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:1441089
    B004/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360275
    B004/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363036
    B004/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723311
    B004/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360275
    B004/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:1801364
    B005/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360103
    B005/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363158
    B005/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723261
    B005/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360103
    B005/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:2161467
    B006/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:361349
    B006/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363474
    B006/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:724823
    B006/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:361349
    B006/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:2522816
    B007/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360493
    B007/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:362955
    B007/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723448
    B007/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360493
    B007/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:2883309
    B008/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360465
    B008/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:363225
    B008/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723690
    B008/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360465
    B008/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:3243774
    B009/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_EGPU_hit:360684
    B009/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries0:362660
    B009/SProcessHits_EPH_meta.txt:EndOfEvent_hitCollection_entries1:723344
    B009/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_count:360684
    B009/SProcessHits_EPH_meta.txt:EndOfEvent_Simulate_savehit_total:3604458
    A[blyth@localhost ALL1_DebugPhilox_3_NNVT:0:1000_RainXZ_Z230_1M_f8]$ 


Overview
-----------

* next :doc:`hitCollection`


