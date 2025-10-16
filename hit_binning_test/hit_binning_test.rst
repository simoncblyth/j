hit_binning_test
=================

lposcost
---------

::

    (ok) A[blyth@localhost opticks]$ opticks-f lposcost 
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
    ./qudarap/tests/QSim_MockTest.cc:    prd.q1.f.x = 0.5f ;  // lposcost : local position cosTheta of intersect 
    ./qudarap/qsim.h:    const float lposcost = ctx.prd->lposcost() ;  // local frame intersect position cosine theta
    ./qudarap/qsim.h:    printf("//qsim::propagate_at_surface_CustomART pidx %7d : lposcost = %10.8f (expect 0->1)\n", ctx.pidx, lposcost );
    ./qudarap/qsim.h:    if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ctx.pidx, ctx.pidx_debug );
    ./qudarap/qsim.h:    if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    ./qudarap/qsim.h:           ctx.pidx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ATQC[0], ATQC[1], ATQC[2], ATQC[3] );
    ./qudarap/qsim.h:surface handling for z-minus, when lposcost < 0.f at lower z-hemi.
    ./qudarap/qsim.h:For z-plus with lposcost > 0.f upper z-hemi simply ignore
    ./qudarap/qsim.h:    const float lposcost = ctx.prd->lposcost() ;  // local frame intersect position cosine theta
    ./qudarap/qsim.h:    ctx.p.set_prd(boundary, identity, cosTheta, iindex );  // HMM: lposcost not passed along
    ./qudarap/qsim.h:            printf("//qsim.propagate.body.WITH_CUSTOM4 pidx %7d  BOUNDARY ems %d lposcost %7.3f \n", ctx.pidx, ems, lposcost );
    ./qudarap/qsim.h:            printf("//qsim.propagate.body.NOT:WITH_CUSTOM4 pidx %7d BOUNDARY ems %d lposcost %7.3f \n", ctx.pidx, ems, lposcost);
    ./qudarap/qsim.h:        else if( lposcost < 0.f )  // could combine with prior, but handy for debug to keep separate
    ./qudarap/qsim.h:                printf("//qsim.propagate.body (lposcost < 0.f) pidx %7d bounce %d command %d flag %d ems %d \n",
    ./qudarap/qsim.h:   of fallback to ordinary surface handling for "lposcost < 0.f" and also
    ./qudarap/qsim.h:   ordinary NoSurface must be possible no matter the lposcost value.
    ./qudarap/QPMT.cu:    F lposcost = 0.5f ;  // np.acos(0.5) 1.047197
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_SPEC_ce(payload, pmtid, wavelength_nm, lposcost, pidx, pidx_debug );
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_SPEC_ce(payload, pmtid, wavelength_nm, lposcost );
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_ATQC(payload, pmtid, wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, pidx, pidx_debug );
    ./qudarap/QPMT.cu:            pmt->get_lpmtid_ATQC(payload, pmtid, wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_stackspec_ce_acosf( F* spec16, int lpmtid, F energy_eV, F lposcost, unsigned pidx, bool pidx_debug ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_stackspec_ce_acosf( F* spec16, int lpmtid, F energy_eV, F lposcost ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_stackspec_ce(       F* spec15, int lpmtid, F energy_eV, F lposcost ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_SPEC_ce(F* spec16 , int lpmtid, F wavelength_nm, F lposcost, unsigned pidx, bool pidx_debug ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_SPEC_ce(F* spec16 , int lpmtid, F wavelength_nm, F lposcost ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_ATQC(  F* ATQC, int lpmtid, F wavelength_nm, F minus_cos_theta, F dot_pol_cross_mom_nrm, F lposcost, unsigned pidx, bool pidx_debug ) const ;
    ./qudarap/qpmt.h:    QPMT_METHOD void get_lpmtid_ATQC(  F* ATQC  , int lpmtid, F wavelength_nm, F minus_cos_theta, F dot_pol_cross_mom_nrm, F lposcost ) const ;
    ./qudarap/qpmt.h:lposcost
    ./qudarap/qpmt.h:    , F lposcost
    ./qudarap/qpmt.h:    const F theta_radians = acosf(lposcost);
    ./qudarap/qpmt.h:    if(pidx_debug) printf("//qpmt::get_lpmtid_stackspec_ce_acosf pidx %7d lpmtid %6d lpmtidx %6d lpmtcat %2d qe_scale %8.4f energy_eV %8.4f qe_shape %8.4f qe(qe_scale*qe_shape) %8.4f spec[15] %8.4f lposcost %8.4f theta_radians %8.4f ce %8.4f \n",
    ./qudarap/qpmt.h:                                                                      pidx, lpmtid, lpmtidx, lpmtcat,  qe_scale, energy_eV, qe_shape, qe, spec[15], lposcost, theta_radians, ce );
    ./qudarap/qpmt.h:lposcost
    ./qudarap/qpmt.h:inline QPMT_METHOD void qpmt<F>::get_lpmtid_stackspec_ce( F* spec, int lpmtid, F energy_eV, F lposcost ) const
    ./qudarap/qpmt.h:    const F ce = cecosth_prop->interpolate( lpmtcat, lposcost );
    ./qudarap/qpmt.h:    //printf("//qpmt::get_lpmtid_stackspec_ce lpmtid %d lpmtidx %d lpmtcat %d lposcost %7.3f  ce %7.3f spec[7] %7.3f \n", lpmtid, lpmtidx, lpmtcat, lposcost, ce, spec[7] );
    ./qudarap/qpmt.h:   , F lposcost
    ./qudarap/qpmt.h:    get_lpmtid_stackspec_ce_acosf( spec_16, lpmtid, energy_eV, lposcost, pidx, pidx_debug );
    ./qudarap/qpmt.h:    get_lpmtid_stackspec_ce_acosf( spec_16, lpmtid, energy_eV, lposcost );
    ./qudarap/qpmt.h:    , F lposcost
    ./qudarap/qpmt.h:    get_lpmtid_stackspec_ce_acosf( spec, lpmtid, energy_eV, lposcost, pidx, pidx_debug );
    ./qudarap/qpmt.h:    get_lpmtid_stackspec_ce_acosf( spec, lpmtid, energy_eV, lposcost );
    ./qudarap/qpmt.h:    //if(pidx_debug) printf("//qpmt.get_lpmtid_ATQC pidx %7d lpmtid %d energy_eV %8.4f _qe(spec[15]) %8.4f lposcost %8.4f ce %8.4f  \n", pidx, lpmtid, energy_eV, _qe, lposcost, ce );
    ./qudarap/qpmt.h:        if(pidx_debug) printf("//qpmt.get_lpmtid_ATQC pidx %7d lpmtid %d energy_eV %8.4f _qe(spec[15]) %8.4f lposcost %8.4f ce %8.4f stack.art.A %8.4f _qe/stack.art.A=ATQC[2] %8.4f  ce=ATQC[3] %8.4f  \n",
    ./qudarap/qpmt.h:                                                      pidx, lpmtid, energy_eV, _qe, lposcost, ce, stack.art.A, ATQC[2], ATQC[3] );
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




add lposphi sibling to lposcost ?
----------------------------------

::

    808 extern "C" __global__ void __intersection__is()
    809 {
    810 
    811 #if defined(DEBUG_PIDXYZ)
    812     const uint3 idx = optixGetLaunchIndex();
    813     const uint3 dim = optixGetLaunchDimensions();
    814     bool dumpxyz = idx.x == params.pidxyz.x && idx.y == params.pidxyz.y && idx.z == params.pidxyz.z ;
    815     //if(dumpxyz) printf("//__intersection__is  idx(%u,%u,%u) dim(%u,%u,%u) dumpxyz:%d \n", idx.x, idx.y, idx.z, dim.x, dim.y, dim.z, dumpxyz);
    816 #else
    817     bool dumpxyz = false ;
    818 #endif
    819 
    820 
    821     HitGroupData* hg  = (HitGroupData*)optixGetSbtDataPointer();
    822     int nodeOffset = hg->prim.nodeOffset ;
    823     int globalPrimIdx = hg->prim.globalPrimIdx ;
    824 
    825     const CSGNode* node = params.node + nodeOffset ;  // root of tree
    826     const float4* plan = params.plan ;
    827     const qat4*   itra = params.itra ;
    828 
    829     const float  t_min = optixGetRayTmin() ;
    830     const float3 ray_origin = optixGetObjectRayOrigin();
    831     const float3 ray_direction = optixGetObjectRayDirection();
    832 
    833     float4 isect ; // .xyz normal .w distance
    834     isect.x = 0.f ;
    835     isect.y = 0.f ;
    836     isect.z = 0.f ;
    837     isect.w = 0.f ;
    838 
    839     bool valid_isect = intersect_prim(isect, node, plan, itra, t_min , ray_origin, ray_direction, dumpxyz );
    840     if(valid_isect)
    841     {
    842         const float lposcost = normalize_z(ray_origin + isect.w*ray_direction ) ;  // scuda.h cosTheta z/len of local(aka Object) frame position
    843         const unsigned hitKind = 0u ;     // only up to 127:0x7f : could use to customize how attributes interpreted
    844         const unsigned boundary = node->boundary() ;  // all CSGNode in the tree for one CSGPrim tree have same boundary
    845         const unsigned globalPrimIdx_boundary = (( globalPrimIdx & 0xffffu ) << 16 ) | ( boundary & 0xffffu ) ;
    846 
    847 #ifdef WITH_PRD
    848         if(optixReportIntersection( isect.w, hitKind))
    849         {
    850             quad2* prd = SOPTIX_getPRD<quad2>(); // access prd addr from RG program
    851             prd->q0.f = isect ;  // .w:distance and .xyz:normal which starts as the local frame one
    852             prd->set_globalPrimIdx_boundary_(globalPrimIdx_boundary) ;
    853             prd->set_lposcost(lposcost);
    854         }
    855 #else
    856         unsigned a0, a1, a2, a3, a4, a5  ; // MUST CORRESPOND TO num_attribute_values in PIP::PIP


