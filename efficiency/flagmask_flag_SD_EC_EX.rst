flagmask_flag_SD_EC_EX
========================

overview
----------

* next :doc:`../SPMT/SPMT`


qsim.h sneak into flagmask first
---------------------------------

::

    1822 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1823     if( ctx.pidx == base->pidx )
    1824         printf("//qsim.propagate_at_surface_CustomART pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) u_theAbsorption  %7.3f action %d \n",
    1825         ctx.pidx, lpmtid, ATQC[0], ATQC[1], ATQC[2], ATQC[3], u_theAbsorption, action  );
    1826 #endif
    1827 
    1828     if( action == BREAK )
    1829     {
    1830         float u_theEfficiency = curand_uniform(&rng) ;
    1831         float u_collectionEfficiency = curand_uniform(&rng);
    1832 
    1833         flag = u_theEfficiency < theEfficiency ? SURFACE_DETECT : SURFACE_ABSORB ;
    1834 
    1835         unsigned ce_flag = flag == SURFACE_DETECT
    1836                                  ?
    1837                                      (  u_collectionEfficiency < collectionEfficiency ? EFFICIENCY_COLLECT : EFFICIENCY_CULL )
    1838                                  :
    1839                                      0u
    1840                                  ;
    1841 
    1842         p.flagmask |= ce_flag ;  // sneak into flagmask without changing flag
    1843 
    1844 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1845         if( ctx.pidx == base->pidx )
    1846             printf("//qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) u_theEfficiency  %7.3f theEfficiency %7.3f flag %d ce_flag %d\n",
    1847                                                                     ctx.pidx, lpmtid, ATQC[0],ATQC[1], ATQC[2],ATQC[3],  u_theEfficiency,  theEfficiency, flag, ce_flag  );
    1848 #endif
    1849 
    1850     }
    1851     else


qsim.h now go into flag, flagmask will be set within sphoton.h
--------------------------------------------------------------------

::

    1828     if( action == BREAK )
    1829     {
    1830         float u_theEfficiency = curand_uniform(&rng) ;
    1831         float u_collectionEfficiency = curand_uniform(&rng);
    1832 
    1833         flag = u_theEfficiency < theEfficiency ? 
    1834                                                     (  u_collectionEfficiency < collectionEfficiency ? EFFICIENCY_COLLECT : EFFICIENCY_CULL )
    1835                                                :    
    1836                                                     SURFACE_ABSORB
    1837                                                ;    
    1838         
    1839         // former SD:SURFACE_DETECT, now becomes EC:EFFICIENCY_COLLECT or EX:EFFICIENCY_CULL depending on collectionEfficiency and random throw
    1840 
    1841 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1842         if( ctx.pidx == base->pidx )
    1843             printf("//qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) u_theEfficiency  %7.3f theEfficiency %7.3f flag %d \n",
    1844                                                                     ctx.pidx, lpmtid, ATQC[0],ATQC[1], ATQC[2],ATQC[3],  u_theEfficiency,  theEfficiency, flag );
    1845 #endif
    1846     
    1847     }



Where is B side equivalent ?  SEvt::finalPhoton called by U4Recorder::PostUserTrackingAction_Optical_
------------------------------------------------------------------------------------------------------

::

    (ok) A[blyth@localhost u4]$ opticks-f EFFICIENCY_COLLECT
    ./cfg4/CCtx.cc:Adds EFFICIENCY_COLLECT or EFFICIENCY_CULL to the _hitflags, 
    ./cfg4/CCtx.cc:        _hitflags |= EFFICIENCY_COLLECT ; 
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    EFFICIENCY_COLLECT = 0x1 << 15, 
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:    static constexpr const char* _EFFICIENCY_COLLECT = "EC" ;
    ./examples/Geant4/OpticalApp/OpticalRecorder.h:        case EFFICIENCY_COLLECT: str=_EFFICIENCY_COLLECT ;break;
    ./g4ok/G4Opticks.cc:    EFFICIENCY_COLLECT (EC) or EFFICIENCY_CULL (EX) flag for photons that already 
    ./optickscore/tests/OpticksFlagsTest.cc:    OpticksFlagsTest --dbghitmask SD,EC           # EC: EFFICIENCY_COLLECT 
    ./optixrap/cu/generate.cu:        p.flags.u.w |= ( u_angular < efficiency ?  EFFICIENCY_COLLECT : EFFICIENCY_CULL ) ;   
    ./qudarap/qsim.h:                                                    (  u_collectionEfficiency < collectionEfficiency ? EFFICIENCY_COLLECT : EFFICIENCY_CULL )
    ./qudarap/qsim.h:        // former SD:SURFACE_DETECT, now becomes EC:EFFICIENCY_COLLECT or EX:EFFICIENCY_CULL depending on collectionEfficiency and random throw
    ./sysrap/OpticksPhoton.cc:        "EFFICIENCY_COLLECT":"pink",
    ./sysrap/OpticksPhoton.h:    EFFICIENCY_COLLECT = 0x1 << 15,
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* EFFICIENCY_COLLECT_ = "EFFICIENCY_COLLECT" ;
    ./sysrap/OpticksPhoton.hh:    static constexpr const char* _EFFICIENCY_COLLECT = "EC" ;
    ./sysrap/OpticksPhoton.hh:        case EFFICIENCY_COLLECT: s=EFFICIENCY_COLLECT_ ;break;
    ./sysrap/OpticksPhoton.hh:        case EFFICIENCY_COLLECT: s=_EFFICIENCY_COLLECT ;break;
    ./sysrap/OpticksPhoton.hh:    pairs.push_back(KV(EFFICIENCY_COLLECT_ , _EFFICIENCY_COLLECT));
    ./sysrap/SEventConfig.hh:        EC : EFFICIENCY_COLLECT
    ./sysrap/SEvt.cc:   of SURFACE_DETECT(SD) to EFFICIENCY_COLLECT(EC) or EFFICIENCY_CULL(EX)
    ./sysrap/SEvt.cc:                                         EFFICIENCY_COLLECT
    ./sysrap/tests/sphoton_test.cc:    p.set_flag( EFFICIENCY_COLLECT );
    ./sysrap/tests/sphoton_test.cc:    p.add_flagmask( EFFICIENCY_COLLECT );
    ./sysrap/tests/sphoton_test.cc:    std::cout << "add_flagmask.2 EFFICIENCY_COLLECT : " << p.descFlag() << "\n" ;
    ./sysrap/tests/sphoton_test.cc:    |= EFFICIENCY_COLLECT 00000000000000001111111111111111 16
    ./sysrap/tests/sphoton_test.cc:    flagmask |= EFFICIENCY_COLLECT ; dump("|= EFFICIENCY_COLLECT", flagmask) ;
    (ok) A[blyth@localhost opticks]$ 
    (ok) A[blyth@localhost opticks]$ 



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




     827 void U4Recorder::PostUserTrackingAction_Optical_(const G4Track* track, int* label)
     828 {
     829     spho& ulabel = reinterpret_cast<spho&>(*label);
     830     if(!Enabled(ulabel)) return ; // EIDX, GIDX skipping
     831 
     832     G4TrackStatus tstat = track->GetTrackStatus();
     833     LOG(LEVEL) << U4TrackStatus::Name(tstat) ;
     834 
     835     bool is_fStopAndKill = tstat == fStopAndKill ;
     836     bool is_fSuspend     = tstat == fSuspend ;
     837     bool is_fStopAndKill_or_fSuspend = is_fStopAndKill || is_fSuspend  ;
     838     LOG_IF(info, !is_fStopAndKill_or_fSuspend ) << " not is_fStopAndKill_or_fSuspend  post.tstat " << U4TrackStatus::Name(tstat) ;
     839     assert( is_fStopAndKill_or_fSuspend );
     840 
     841 
     842     if(is_fStopAndKill)
     843     {
     844         SEvt* sev = SEvt::Get_ECPU();
     845         U4Random::SetSequenceIndex(-1);
     846         sev->finalPhoton(ulabel);
     847         transient_fSuspend_track = nullptr ;
     848 #ifndef PRODUCTION
     849         bool PIDX_DUMP = ulabel.id == PIDX && PIDX_ENABLED ;
     850         sseq& seq = sev->current_ctx.seq ;
     851 
     852         LOG_IF(info, PIDX_DUMP )    // CURIOUS : THIS IS NOT SHOWING UP
     853             << " l.id " << std::setw(5) << ulabel.id
     854             << " seq " << seq.brief()
     855             ;
     856 
     857         if(PIDX_DUMP) std::cerr
     858             << "U4Recorder::PostUserTrackingAction_Optical.fStopAndKill "
     859             << " ulabel.id " << std::setw(6) << ulabel.id
     860             << " seq.brief " << seq.brief()
     861             << std::endl
     862             ;
     863 #endif
     864     }
     865     else if(is_fSuspend)
     866     {
     867         transient_fSuspend_track = track ;
     868     }
     869     LOG(LEVEL) << "]" ;
     870 }


    3007 void SEvt::finalPhoton(const spho& label)
    3008 {
    3009     dbg->finalPhoton++ ;
    3010     LOG(LEVEL) << label.desc() ;
    3011     assert( label.isSameLineage(current_pho) );
    3012 
    3013     unsigned idx = label.id ;
    3014     sctx& ctx = current_ctx ;
    3015     assert( ctx.idx == idx );
    3016 
    3017 
    3018     int eph_flag = finalPhoton_eph_flag(label);  // eph_flag will often be zero
    3019 
    3020     LOG_IF(info, EPH_)
    3021         << " before:ctx.p.abbrev_() [" << ctx.p.abbrev_() << "]"
    3022         << " eph_flag [" << OpticksPhoton::Abbrev(eph_flag) << "]"
    3023         ;
    3024 
    3025     if( eph_flag > 0 )
    3026     {
    3027 #ifdef AFTER_FLAGMASK_HAS_BEEN_VERIFIED
    3028         ctx.p.set_flag(eph_flag);      // sets both flag and flagmask
    3029 #else
    3030         ctx.p.flagmask |= eph_flag ;
    3031 #endif
    3032     }
    3033 
    3034    
    3035 #ifndef PRODUCTION
    3036 #ifdef WITH_SUP
    3037     quadx6& xsup = (quadx6&)ctx.sup ;
    3038     xsup.q0.w.y = sstamp::Now();
    3039     xsup.q1.w.x = t_PenultimatePoint ;
    3040     xsup.q1.w.y = t_LastPoint ;
    3041 #endif
    3042     ctx.end();   // copies {seq,sup} into evt->{seq,sup}[idx] (and tag, flat when DEBUG_TAG)
    3043 #endif
    3044 
    3045     evt->photon[idx] = ctx.p ;   // HUH: why not do this in ctx.end ?
    3046 }  




EC not appearing on A or B side ?
------------------------------------

::

    AB
    [sseq_index_ab::desc u_size 32503 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  4754.3746 ndf 404.0000 sum/ndf    11.7683 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SD                                                                                :      -1 345451 :     0.0000 : N :      -1      2 : AZERO C2EXC  
        TO BT BT BT BT SA                                                                                :  336783 336864 :     0.0097 : Y :       2      1 :   
        TO BT BT BT BT                                                                                   :  317582     -1 :     0.0000 : N :       5     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SA                                                                             :  124915 125034 :     0.0567 : Y :   88947  88032 :   
        TO BT BT BT BT BT SR SA                                                                          :   38523  38441 :     0.0874 : Y :  108919 108963 :   
        TO BT BT BT BT EX                                                                                :   27933     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SA                                                                       :   20226  20245 :     0.0089 : Y :  108778 108786 :   
        TO BT BT BT BT BR BT BT BT BT BT SA                                                              :   10668  10871 :     1.9132 : Y :   49243  49230 :   
        TO BT BT AB                                                                                      :    8758   8719 :     0.0870 : Y :      47     43 :   
        TO BT BT BT BT BT SR SR SR SA                                                                    :    6015   5935 :     0.5356 : Y :  147290 147241 :   
        TO BT BT BT BT AB                                                                                :    3410   3319 :     1.2306 : Y :     199     41 :   
        TO BT BT BT BT BT SR BR SA                                                                       :    3136   3088 :     0.3702 : Y :  335672 335683 :   
    :r:`TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :    2958   2469 :    44.0614 : Y :   64577  64662 : DEVIANT  `
        TO BT BT BT BT BT SR SR SR BR SA                                                                 :    2391   2325 :     0.9237 : Y :  147741 147420 :   



After reorder the OpticksPhoton.h enum get EC+EX on A side, BUT still getting SD on B side ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    t3 1750343346432883 (t3 - t2)    25599 0.025599
    AB
    [sseq_index_ab::desc u_size 32503 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  4754.3746 ndf 404.0000 sum/ndf    11.7683 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SD                                                                                :      -1 345451 :     0.0000 : N :      -1      2 : AZERO C2EXC  
        TO BT BT BT BT SA                                                                                :  336783 336864 :     0.0097 : Y :       2      1 :   
        TO BT BT BT BT EC                                                                                :  317582     -1 :     0.0000 : N :       5     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SA                                                                             :  124915 125034 :     0.0567 : Y :   88947  88032 :   
        TO BT BT BT BT BT SR SA                                                                          :   38523  38441 :     0.0874 : Y :  108919 108963 :   
        TO BT BT BT BT EX                                                                                :   27933     -1 :     0.0000 : N :       0     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SA                                                                       :   20226  20245 :     0.0089 : Y :  108778 108786 :   
        TO BT BT BT BT BR BT BT BT BT BT SA                                                              :   10668  10871 :     1.9132 : Y :   49243  49230 :   
        TO BT BT AB                                                                                      :    8758   8719 :     0.0870 : Y :      47     43 :   
        TO BT BT BT BT BT SR SR SR SA                                                                    :    6015   5935 :     0.5356 : Y :  147290 147241 :   
        TO BT BT BT BT AB                                                                                :    3410   3319 :     1.2306 : Y :     199     41 :   
        TO BT BT BT BT BT SR BR SA                                                                       :    3136   3088 :     0.3702 : Y :  335672 335683 :   
    :r:`TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :    2958   2469 :    44.0614 : Y :   64577  64662 : DEVIANT  `



Changing flag from SD to EC/EX in finalPhoton must be missing the seq boat on the B side ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

YES::

    130 SCTX_METHOD void sctx::point(int bounce)
    131 {
    132     if(evt->record && bounce < evt->max_record) evt->record[evt->max_record*idx+bounce] = p ;
    133     if(evt->rec    && bounce < evt->max_rec)    evt->add_rec( rec, idx, bounce, p );    // this copies into evt->rec array
    134     if(evt->seq)                                seq.add_nibble( bounce, p.flag(), p.boundary() );
    135     if(evt->aux    && bounce < evt->max_aux)    evt->aux[evt->max_aux*idx+bounce] = aux ;
    136 }


Try moving the flag change earlier, to U4Recorder::UserSteppingAction_Optical
------------------------------------------------------------------------------

YEP that helps now getting EC and EX on both sides.
But A side has long histories ending in SD than B side lacks. Maybe 3inch landings::

    [sseq_index_ab::desc u_size 32005 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum  1115.8250 ndf 465.0000 sum/ndf     2.3996 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SA                                                                                :  336783 336864 :     0.0097 : Y :       2      1 :   
        TO BT BT BT BT EC                                                                                :  317582 317390 :     0.0581 : Y :       5      2 :   
        TO BT BT BT BT BT SA                                                                             :  124915 125034 :     0.0567 : Y :   88947  88032 :   
        TO BT BT BT BT BT SR SA                                                                          :   38523  38441 :     0.0874 : Y :  108919 108963 :   
        TO BT BT BT BT EX                                                                                :   27933  28061 :     0.2926 : Y :       0     10 :   
        TO BT BT BT BT BT SR SR SA                                                                       :   20226  20245 :     0.0089 : Y :  108778 108786 :   
        TO BT BT BT BT BR BT BT BT BT BT SA                                                              :   10668  10871 :     1.9132 : Y :   49243  49230 :   
        TO BT BT AB                                                                                      :    8758   8719 :     0.0870 : Y :      47     43 :   
        TO BT BT BT BT BT SR SR SR SA                                                                    :    6015   5935 :     0.5356 : Y :  147290 147241 :   
        TO BT BT BT BT AB                                                                                :    3410   3319 :     1.2306 : Y :     199     41 :   
        TO BT BT BT BT BT SR BR SA                                                                       :    3136   3088 :     0.3702 : Y :  335672 335683 :   
    :r:`TO BT BT BT BT BR BT BT BT BT BT BT AB                                                           :    2958   2469 :    44.0614 : Y :   64577  64662 : DEVIANT  `
        TO BT BT BT BT BT SR SR SR BR SA                                                                 :    2391   2325 :     0.9237 : Y :  147741 147420 :   
        TO BT BT BR BT BT BT SA                                                                          :    1961   2021 :     0.9041 : Y :   27950  38276 :   
        TO BT BT BT BT BR BT BT BT BT AB                                                                 :    1844   1829 :     0.0613 : Y :    2209   4770 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    1778   1815 :     0.3810 : Y :      31     44 :   
        TO BT BT BT BR BT BT BT BT SA                                                                    :    1690   1635 :     0.9098 : Y :   42010  42229 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT EC                                                     :    1663   1535 :     5.1232 : Y :   67671  67669 :   
        TO BT BT BT BT BT BR SR SA                                                                       :    1577   1653 :     1.7882 : Y :   92600  92124 :   
        TO BT BR BT BT SA                                                                                :    1566   1597 :     0.3038 : Y :   27119  27153 :   
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT SA                                                     :    1571   1486 :     2.3634 : Y :   61181  60825 :   
        TO BT BT BT BT BT SR SR SR BR BR SR SA                                                           :    1453   1461 :     0.0220 : Y :  153888 153753 :   
        TO BT BT BT BT BT SR SR SR BR SR SA                                                              :    1446   1428 :     0.1127 : Y :  147316 147569 :   
        TO AB                                                                                            :    1183   1209 :     0.2826 : Y :      25    126 :   
        TO BT BT BT BT BT SR SR BR SA                                                                    :    1185   1153 :     0.4380 : Y :  265598 265603 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :    1097   1115 :     0.1465 : Y :  335753 335956 :   
        TO BT BT BT BT BT SR SR SR BR BR SA                                                              :    1050   1090 :     0.7477 : Y :  153736 153784 :   
        TO BT BT BT BT BR BT BT BT BT BT DR BT SA                                                        :     890    876 :     0.1110 : Y :   49229  49448 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SA                                      :     765    874 :     7.2489 : Y :  167000 167778 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT EC                                      :     840    849 :     0.0480 : Y :  105815 166665 :   
        TO BT BT BT BT BR BT BT BT BT BT BT SC AB                                                        :     769    823 :     1.8317 : Y :  169397 166947 :   
    :r:`TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT AB                                               :     742    605 :    13.9339 : Y :  147868 147285 : DEVIANT  `
        TO BT BT BT BT BR BT BT BT BT BT BT BT AB                                                        :     653    738 :     5.1941 : Y :  165022  91233 :   
        TO BT BT BT BT BT SR SR SR BR BT BT BT BT BT BT SA                                               :     718    701 :     0.2037 : Y :  153711 153788 :   
        TO BT BT BT BT BT BR SR SR SA                                                                    :     613    702 :     6.0236 : Y :   92866  92649 :   
        TO BT BT BR BT BT SA                                                                             :     698    677 :     0.3207 : Y :      13     37 :   
        TO BT BT BT BR BT BT BT SA                                                                       :     684    663 :     0.3274 : Y :      34      5 :   
        TO BT BT BT BT BR BT BT BT BT BT DR BT BT BT BT BT SA                                            :     662    667 :     0.0188 : Y :   54300  49953 :   
        TO BT BT BT BT BT SR SR BT BT BT BT BT BT SA                                                     :     609    622 :     0.1373 : Y :  713725 713763 :   
        TO BT BT BT BT BR BT BT BT BT BT DR BT BT BT BT BT EC                                            :     619    597 :     0.3980 : Y :   57954  51734 :   
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 32005 NUM_MAX 40 num 32005 opt AZERO mode 1
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT EX                                            :      -1     55 :     0.0000 : N :      -1 106361 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC BT BT BT BT EX                                :      -1     21 :     0.0000 : N :      -1 154598 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT EX                                         :      -1     17 :     0.0000 : N :      -1 180165 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT EC                    :      -1     16 :     0.0000 : N :      -1 250486 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT SC AB                                      :      -1     14 :     0.0000 : N :      -1 251565 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                 :      -1     14 :     0.0000 : N :      -1 245640 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR BR BR SR SR SR BT BT BT BT BT BT BT BT SA                                :      -1     14 :     0.0000 : N :      -1 715357 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT SC BT BT BT BT EX                                         :      -1     13 :     0.0000 : N :      -1 214256 : AZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                    :      -1     13 :     0.0000 : N :      -1 252086 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT EC                                            :      -1     12 :     0.0000 : N :      -1 249919 : AZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT EC                                         :      -1     11 :     0.0000 : N :      -1 268103 : AZERO C2EXC  
    ]sseq_index_ab::desc

    AB
    [sseq_index_ab::desc u_size 32005 NUM_MAX 40 num 32005 opt BZERO mode 2
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT SD                                            :      69     -1 :     0.0000 : N :  169684     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR BT BT BT BT BT BT BT SC BT BT BT BT SD                                      :      27     -1 :     0.0000 : N :  337065     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT EC                          :      25     -1 :     0.0000 : N :  680340     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SC SC BT BT BT BT SD                                         :      24     -1 :     0.0000 : N :  264394     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA              :      21     -1 :     0.0000 : N :  245972     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT SA                          :      20     -1 :     0.0000 : N :  681020     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT SC BT BT BT BT BT BT EC              :      19     -1 :     0.0000 : N :  245700     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT EC              :      18     -1 :     0.0000 : N :  246358     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT SC BT BT BT BT SD                                :      15     -1 :     0.0000 : N :  162000     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SC AB                                            :      15     -1 :     0.0000 : N :  680508     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT SC AB                                :      14     -1 :     0.0000 : N :  245799     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT BT BT SD                                      :      14     -1 :     0.0000 : N :  178791     -1 : BZERO C2EXC  
        TO BT BT BT BT BT SR SR SR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT EC                 :      14     -1 :     0.0000 : N :  249073     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT DR BT BT BR SA                                                  :      13     -1 :     0.0000 : N :  729811     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SD                                               :      13     -1 :     0.0000 : N :  460432     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT SC SC AB                                         :      11     -1 :     0.0000 : N :  693277     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT BT SA                          :      11     -1 :     0.0000 : N :  171940     -1 : BZERO C2EXC  
        TO BT BT BT BT BR BT BT BT BT BT BT BT SC BT BT BT BT SD                                         :      11     -1 :     0.0000 : N :  200242     -1 : BZERO C2EXC  
    ]sseq_index_ab::desc









Adding history selection to cxr_min.sh SRecord
---------------------------------------------------

::

        TO BT BT BT BT BR BT BT BT BT BT BT SC BT BT BT BT SD                                            :      69     -1 :     0.0000 : N :  169684     -1 : BZERO C2EXC  



    hanges not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   CSGOptiX/tests/CSGOptiXRenderInteractiveTest.cc
        modified:   sysrap/NP.hh
        modified:   sysrap/SRecord.h
        modified:   sysrap/spath.h
        modified:   sysrap/sseq_array.h
        modified:   sysrap/sseq_record.h
        modified:   sysrap/tests/SGLFW_Event_test.cc
        modified:   sysrap/tests/SGLFW_SOPTIX_Scene_test.cc
        modified:   sysrap/tests/SRecord_test.cc
        modified:   sysrap/tests/SRecord_test.sh
        modified:   sysrap/tests/spath_test.cc
        modified:   sysrap/tests/spath_test.sh
        modified:   sysrap/tests/sseq_record_test.cc







Am I wrong about "0x1 << 15" surviving ? YES FFS(0x1 << 15) = 16 which does not fit in the 0xf MASK
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

     22 enum
     23 {
     24     CERENKOV          = 0x1 <<  0,    
     25     SCINTILLATION     = 0x1 <<  1,    
     26     MISS              = 0x1 <<  2,
     27     BULK_ABSORB       = 0x1 <<  3,
     28     BULK_REEMIT       = 0x1 <<  4,
     29     BULK_SCATTER      = 0x1 <<  5,
     30     SURFACE_DETECT    = 0x1 <<  6,
     31     SURFACE_ABSORB    = 0x1 <<  7,
     32     SURFACE_DREFLECT  = 0x1 <<  8,
     33     SURFACE_SREFLECT  = 0x1 <<  9,
     34     BOUNDARY_REFLECT  = 0x1 << 10,
     35     BOUNDARY_TRANSMIT = 0x1 << 11,
     36     TORCH             = 0x1 << 12,
     37     NAN_ABORT         = 0x1 << 13,
     38     EFFICIENCY_CULL    = 0x1 << 14,
     39     EFFICIENCY_COLLECT = 0x1 << 15,
     40     __NATURAL         = 0x1 << 16,
     41     __MACHINERY       = 0x1 << 17,
     42     __EMITSOURCE      = 0x1 << 18,
     43     PRIMARYSOURCE     = 0x1 << 19,
     44     GENSTEPSOURCE     = 0x1 << 20,
     45     DEFER_FSTRACKINFO = 0x1 << 21
     46 }; 
     47 
     48 //  only ffs 0-15 make it into the record so debug flags only beyond 15 



IsTerminalFlag
~~~~~~~~~~~~~~~~~

::

    (ok) A[blyth@localhost opticks]$ opticks-f IsTerminalFlag
    ./cfg4/CRec.cc:    bool lastPre = OpStatus::IsTerminalFlag(preFlag);  assert(!lastPre);
    ./cfg4/CRec.cc:    bool lastPost = OpStatus::IsTerminalFlag(postFlag);
    ./cfg4/OpStatus.cc:bool OpStatus::IsTerminalFlag(unsigned flag)
    ./cfg4/OpStatus.hh:       static  bool IsTerminalFlag(unsigned flag); 
    ./sysrap/OpticksPhoton.hh:    static bool IsTerminalFlag(const unsigned flag);
    ./sysrap/OpticksPhoton.hh:inline bool OpticksPhoton::IsTerminalFlag(const unsigned flag) // static : AB SA SD MI

    ./u4/U4Recorder.cc:        bool is_terminal_flag = OpticksPhoton::IsTerminalFlag(flag);
    (ok) A[blyth@localhost opticks]$ 



