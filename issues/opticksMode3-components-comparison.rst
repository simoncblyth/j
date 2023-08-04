opticksMode3-components-comparison
===================================

Concluded that the two SEvt components are close
enough to proceed with looking at content. 

* :doc:`opticksMode3-contents-comparison`

A::

    epsilon:ALL1 blyth$ ls -1 p001/         
    ## NPFold_meta.txt    ##  DONE?  : where does the fold meta come from ?                       
    ## hit.npy            ##  DONE : implemented SEvt::gatherHit so this should now be present in B 

    NPFold_index.txt                        
    domain.npy                              
    domain_meta.txt                         
    flat.npy                                
    genstep.npy                             
    inphoton.npy
    junoSD_PMT_v2_Opticks.npy
    junoSD_PMT_v2_Opticks_meta.txt
    junoSD_PMT_v2_Opticks_names.txt
    photon.npy
    prd.npy
    record.npy
    record_meta.txt
    seq.npy
    sframe.npy
    sframe_meta.txt
    tag.npy


B::

    epsilon:ALL1 blyth$ ls -1 n001/

    ## aux.npy            ## aux,sup not in SComp::ALL_
    ## sup.npy

    ## gs.npy             ## from SEvt::saveLabels ... makes sense these are CPU side only 
    ## pho.npy
    ## pho0.npy

    ## photon_meta.txt     ## DONE? change QEvent to use SEvt::getPhoton so should not miss the metadata

    NPFold_index.txt
    domain.npy
    domain_meta.txt
    flat.npy
    genstep.npy
    inphoton.npy
    junoSD_PMT_v2_Opticks.npy
    junoSD_PMT_v2_Opticks_meta.txt
    junoSD_PMT_v2_Opticks_names.txt
    photon.npy
    prd.npy
    record.npy
    record_meta.txt
    seq.npy
    sframe.npy
    sframe_meta.txt
    tag.npy


::

    2459 NP* SEvt::gatherPho0() const { return NPX::Make<int>( (int*)pho0.data(), int(pho0.size()), 4 ); }
    2460 NP* SEvt::gatherPho() const {  return NPX::Make<int>( (int*)pho.data(), int(pho.size()), 4 ); }
    2461 NP* SEvt::gatherGS() const {   return NPX::Make<int>( (int*)gs.data(),  int(gs.size()), 4 );  }


    epsilon:u4 blyth$ opticks-f pho0
    ./ana/catdir.py:        numpho0 = mds[0].numPhotons
    ./ana/catdir.py:            if md.numPhotons == numpho0:
    ./sysrap/SEvt.hh:    std::vector<spho>    pho0 ;  // unordered push_back as they come 
    ./sysrap/SEvt.cc:    pho0.clear(); 
    ./sysrap/SEvt.cc:    pho0.push_back(label);    // push_back asis for debugging
    ./sysrap/SEvt.cc:NP* SEvt::gatherPho0() const { return NPX::Make<int>( (int*)pho0.data(), int(pho0.size()), 4 ); }
    ./sysrap/SEvt.cc:    if(a0) a0->save(dir, "pho0.npy"); 
    ./sysrap/SEvt.cc:       << " pho0 " << pho0.size()  
    ./u4/tests/U4RecorderTest.py:    When reemission is enabled this would fail for pho0 (push_back labels)


    3183 void SEvt::saveLabels(const char* dir) const
    3184 {
    3185     LOG(LEVEL) << "[ dir " << dir ;
    3186 
    3187     NP* a0 = gatherPho0();
    3188     if(a0) a0->save(dir, "pho0.npy");
    3189 
    3190     NP* a = gatherPho();
    3191     if(a) a->save(dir, "pho.npy");
    3192 
    3193     NP* g = gatherGS();
    3194     if(g) g->save(dir, "gs.npy");
    3195 
    3196     LOG(LEVEL) << "] dir " << dir ;
    3197 }




DONE : SEvt__LoadTest.sh for testing SEvt::gatherHit 
-------------------------------------------------------

Implemented by adding NP::copy_if 



DONE? : fold meta : missing from B :   NPFold_meta.txt
--------------------------------------------------------

::

    epsilon:p001 blyth$ cat /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001/NPFold_meta.txt
    creator:python3.8
    mtime:1690807632
    HOME:/home/blyth
    USER:blyth
    SCRIPT:ntds3
    PWD:/tmp/u4debug/ntds3
    cxskiplv:
    cxskiplv_idxlist:
    epsilon:p001 blyth$ 

Thats coming from (SCompProvider)provider SEvt::getMeta QEvent::getMeta.
Factored off meta collection into smeta::Collect
and add use of that from U4Recorder::init

::

    2862 void SEvt::gather_components()   // *GATHER*
    2863 {
    2864     int num_genstep = -1 ;
    2865     int num_photon  = -1 ;
    2866     int num_hit     = -1 ;
    2867 
    2868     int num_comp = gather_comp.size() ;
    2869 
    2870     for(int i=0 ; i < num_comp ; i++)
    2871     {
    2872         unsigned cmp = gather_comp[i] ;
    2873         const char* k = SComp::Name(cmp);
    2874         NP* a = provider->gatherComponent(cmp);
    2875         LOG(LEVEL) << " k " << std::setw(15) << k << " a " << ( a ? a->brief() : "-" ) ;
    2876         if(a == nullptr) continue ;
    2877         fold->add(k, a);
    2878 
    2879         int num = a->shape[0] ;
    2880         if(     SComp::IsGenstep(cmp)) num_genstep = num ;
    2881         else if(SComp::IsPhoton(cmp))  num_photon = num ;
    2882         else if(SComp::IsHit(cmp))     num_hit = num ;
    2883     }
    2884     fold->meta = provider->getMeta();
    2885 
    2886 



DONE? : photon meta
---------------------


::

    epsilon:n001 blyth$ cat photon_meta.txt
    SCRIPT:ntds3
    LAYOUT:OIPF_Hama:0:1000
    VERSION:1
    GEOM:V1J009
    COMMANDLINE:gdb -ex "set breakpoint pending on"  -ex "break SEvt::clear"  -ex "info break" -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 3 --no-guide_tube --additionacrylic-simplify-csg --no-toptask-show --pmt-optical-model --debug-disable-xj --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks 2>&1 | tee ntds3.tlog 
    DIRECTORY:/tmp/u4debug/ntds3
    ${GEOM}_GEOMList:V1J009_GEOMList

    // ALL THE ABOVE FROM ENV SO BELONG BETTER ON FOLD NOT ON PHOTON

    t_BeginOfEvent:1690911836717713
    t_EndOfEvent:1690911986245160
    T_BeginOfRun:1690911836660119
    epsilon:n001 blyth$ 




::

    2462 NP* SEvt::gatherPhoton() const
    2463 {
    2464     if( evt->photon == nullptr ) return nullptr ;
    2465     NP* p = makePhoton();
    2466     p->read2( (float*)evt->photon );
    2467 
    2468     p->set_meta<uint64_t>("t_BeginOfEvent", t_BeginOfEvent );
    2469     p->set_meta<uint64_t>("t_EndOfEvent",   t_EndOfEvent );
    2470     p->set_meta<uint64_t>("T_BeginOfRun",   T_BeginOfRun );
    2471     // T_EndOfRun cannot be saved here, it might be saved if SEvt::SaveRunMeta is called
    2472     return p ;
    2473 }

    2625 NP* SEvt::makePhoton() const
    2626 {
    2627     NP* p = NP::Make<float>( evt->num_photon, 4, 4 );
    2628     AddEnvMeta(p, false) ;
    2629     return p ;
    2630 }

    418 NP* QEvent::gatherPhoton() const
    419 {
    420     NP* p = NP::Make<float>( evt->num_photon, 4, 4);
    421     gatherPhoton(p);
    422     return p ;
    423 }
    424 


So QEvent is not using SEvt::makePhoton, but it should. 



CHECK SECOND TIME AFTER UPDATES
---------------------------------

* still no NPFold meta

::

    GEOM tmp
    mv ntds3 ntds3_0
    GEOM tmpget


    epsilon:ALL1 blyth$ diff -r --brief p001 n001 

    Only in n001: sup.npy
    Only in n001: aux.npy

    Only in n001: gs.npy
    Only in n001: pho.npy
    Only in n001: pho0.npy

    Files p001/NPFold_index.txt and n001/NPFold_index.txt differ
    Files p001/domain.npy and n001/domain.npy differ
    Files p001/domain_meta.txt and n001/domain_meta.txt differ
    Files p001/flat.npy and n001/flat.npy differ
    Files p001/hit.npy and n001/hit.npy differ
    Files p001/photon.npy and n001/photon.npy differ
    Files p001/photon_meta.txt and n001/photon_meta.txt differ
    Files p001/prd.npy and n001/prd.npy differ
    Files p001/record.npy and n001/record.npy differ
    Files p001/seq.npy and n001/seq.npy differ
    Files p001/tag.npy and n001/tag.npy differ



FIXED : lack of fold metadata 
---------------------------------

::

    export U4Recorder=INFO SEvt=INFO ; ntds3_noxj 


Suspect some stomping is happening as the metadata is lacking.
Actually not stomped, it was from the switch to SaveComps 
meaning that the NPFold is copied before being saved. 

     
::

    GEOM tmpget
    GEOM tmp
    find . -name NPFold_meta.txt 



::

    2871 void SEvt::gather_metadata()
    2872 {
    2873     std::string provmeta = provider->getMeta();
    2874     LOG(LEVEL) << " provmeta ["<< provmeta << "]" ;
    2875     fold->meta = provmeta ;
    2876 }



At SEvt::gather_metadata the metadata is present::

    2023-08-03 04:02:29.905 INFO  [451689] [SEvt::gather_metadata@2874]  provmeta [source:CSGFoundry::init
    creator:python3.8
    mtime:1691006408229248
    HOME:/home/blyth
    USER:blyth
    SCRIPT:ntds3
    PWD:/tmp/u4debug/ntds3
    LAYOUT:OIPF_Hama:0:1000
    VERSION:1
    GEOM:V1J009
    COMMANDLINE:gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 3 --no-guide_tube --additionacrylic-simplify-csg --no-toptask-show --pmt-optical-model --debug-disable-xj --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks 2>&1 | tee ntds3.tlog 
    DIRECTORY:/tmp/u4debug/ntds3
    ${GEOM}_GEOMList:V1J009_GEOMList
    cxskiplv:
    cxskiplv_idxlist:
    ]


    2023-08-03 04:02:29.911 INFO  [451689] [SEvt::gather_metadata@2874]  provmeta [source:U4Recorder::init
    creator:python3.8
    mtime:1691006328176141
    HOME:/home/blyth
    USER:blyth
    SCRIPT:ntds3
    PWD:/tmp/u4debug/ntds3
    LAYOUT:OIPF_Hama:0:1000
    VERSION:1
    GEOM:V1J009
    COMMANDLINE:gdb   -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 3 --no-guide_tube --additionacrylic-simplify-csg --no-toptask-show --pmt-optical-model --debug-disable-xj --evtmax 1 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer opticks 2>&1 | tee ntds3.tlog 
    DIRECTORY:/tmp/u4debug/ntds3
    ${GEOM}_GEOMList:V1J009_GEOMList
    ]


AHHA the fold gets copied to apply the SEventConfig::SaveComp selection before its saved
which drops the metadata::

    3150 void SEvt::save(const char* dir_)
    3151 {
    3152     gather();
    3153 
    3154     LOG(LEVEL) << descComponent() ;
    3155     LOG(LEVEL) << descFold() ;
    3156 
    3157     bool shallow = true ;
    3158     std::string save_comp = SEventConfig::SaveCompLabel() ;
    3159     NPFold* save_fold = fold->copy(save_comp.c_str(), shallow) ;
    3160 
    3161     LOG_IF(LEVEL, save_fold == nullptr) << " NOTHING TO SAVE SEventConfig::SaveCompLabel/OPTICKS_SAVE_COMP  " << save_comp ;
    3162     if(save_fold == nullptr) return ;
    3163 
    3164     const char* dir = getOutputDir(dir_);
    3165     LOG(info) << " dir " << dir <<  " index " << index << " instance " << instance  << " OPTICKS_SAVE_COMP  " << save_comp ;
    3166     LOG(LEVEL) << descSaveDir(dir_) ;
    3167 
    3168 
    3169     LOG(LEVEL) << "[ save_fold.save " << dir ;
    3170     save_fold->save(dir);
    3171     LOG(LEVEL) << "] save_fold.save " << dir ;
    3172 
    3173     saveLabels(dir);
    3174     saveFrame(dir);
    3175     // could add these to the fold ?  
    3176 }


CHECK THIRD TIME : After NPFold::CopyMeta and with stampFmt
-------------------------------------------------------------

::

    epsilon:ALL1 blyth$ diff -r --brief p001 n001

    Only in n001: sup.npy
    Only in n001: aux.npy   ## sup/aux should be possible with GPU running too ? Why no show ? 

    Only in n001: gs.npy    ## gs/pho/pho0 labels are expected CPU only 
    Only in n001: pho.npy
    Only in n001: pho0.npy

    Files p001/NPFold_index.txt and n001/NPFold_index.txt differ
    Files p001/NPFold_meta.txt and n001/NPFold_meta.txt differ
    Files p001/domain.npy and n001/domain.npy differ
    Files p001/domain_meta.txt and n001/domain_meta.txt differ
    Files p001/flat.npy and n001/flat.npy differ
    Files p001/hit.npy and n001/hit.npy differ
    Files p001/photon.npy and n001/photon.npy differ
    Files p001/photon_meta.txt and n001/photon_meta.txt differ
    Files p001/prd.npy and n001/prd.npy differ
    Files p001/record.npy and n001/record.npy differ
    Files p001/seq.npy and n001/seq.npy differ
    Files p001/tag.npy and n001/tag.npy differ
    epsilon:ALL1 blyth$ 





aux,sup are configured by only present in B CPU side
------------------------------------------------------

aux,sup not in the standard SComp::ALL::

     48 struct SYSRAP_API SComp
     49 {
     50     static constexpr const char* ALL_ = "genstep,photon,record,rec,seq,prd,seed,hit,simtrace,domain,inphoton,tag,flat" ;


::

    2494 NP* SEvt::gatherAux() const
    2495 {
    2496     if( evt->aux == nullptr ) return nullptr ;
    2497     NP* r = makeAux();
    2498     r->read2( (float*)evt->aux );
    2499     return r ;
    2500 }
    2501 NP* SEvt::gatherSup() const
    2502 {
    2503     if( evt->sup == nullptr ) return nullptr ;
    2504     NP* p = makeSup();
    2505     p->read2( (float*)evt->sup );
    2506     return p ;
    2507 }



    241 void SEventConfig::CompAuto(unsigned& gather_mask, unsigned& save_mask )
    242 {   
    243     if(IsRGModeSimulate())
    244     {   
    245         gather_mask |= SCOMP_DOMAIN ;  save_mask |= SCOMP_DOMAIN ;
    246         
    247         if(MaxGenstep()>0){  gather_mask |= SCOMP_GENSTEP ; save_mask |= SCOMP_GENSTEP ; }
    248         if(MaxPhoton()>0)
    249         {   
    250             gather_mask |= SCOMP_INPHOTON ;  save_mask |= SCOMP_INPHOTON ;
    251             gather_mask |= SCOMP_PHOTON   ;  save_mask |= SCOMP_PHOTON   ;
    252             gather_mask |= SCOMP_HIT      ;  save_mask |= SCOMP_HIT ; 
    253             //gather_mask |= SCOMP_SEED ;   save_mask |= SCOMP_SEED ;  // only needed for deep debugging 
    254         }
    255         if(MaxRecord()>0){    gather_mask |= SCOMP_RECORD ;  save_mask |= SCOMP_RECORD ; }
    256         if(MaxAux()>0){       gather_mask |= SCOMP_AUX    ;  save_mask |= SCOMP_AUX    ; }
    257         if(MaxSup()>0){       gather_mask |= SCOMP_SUP    ;  save_mask |= SCOMP_SUP    ; }
    258         if(MaxSeq()>0){       gather_mask |= SCOMP_SEQ    ;  save_mask |= SCOMP_SEQ    ; }
    259         if(MaxPrd()>0){       gather_mask |= SCOMP_PRD    ;  save_mask |= SCOMP_PRD    ; }
    260         if(MaxTag()>0){       gather_mask |= SCOMP_TAG    ;  save_mask |= SCOMP_TAG    ; }
    261         if(MaxFlat()>0){      gather_mask |= SCOMP_FLAT   ;  save_mask |= SCOMP_FLAT   ; }
    262     }


Aux, Sup are configured by SEventConfig::Initialize for StandardFullDebug mode::

    533 int SEventConfig::Initialize() // static
    534 {
    535     LOG_IF(LEVEL, Initialize_COUNT > 0 )
    536         << "SEventConfig::Initialize() called more than once " << std::endl
    537         << " this is now done automatically at SEvt::SEvt usually from main "
    538         << " (IN SOME CASES ITS CONVENIENT TO HAVE MORE THAN ONE SEvt, THOUGH "
    539         << "  SO MAYBE SHOULD MOVE THIS TO OPTICKS_LOG/SLOG ? "
    540         ;
    541     // assert( Initialize_COUNT == 0); 
    542     Initialize_COUNT += 1 ;
    543 
    544     const char* mode = EventMode();
    545     LOG(LEVEL) <<  " EventMode() " << mode ;
    546     LOG(LEVEL)
    547         <<  " RunningMode() " << RunningMode()
    548         <<  " RunningModeLabel() " << RunningModeLabel()
    549         ;
    550 
    551     //std::raise(SIGINT); 
    552 
    553     int maxbounce = MaxBounce();
    554 
    555     if(strcmp(mode, Default) == 0 )
    556     {
    557         SetCompAuto() ;   // comp set based on Max values   
    558     }
    559     else if(strcmp(mode, StandardFullDebug) == 0 )
    560     {
    561         SEventConfig::SetMaxRecord(maxbounce+1);
    562         SEventConfig::SetMaxRec(maxbounce+1);
    563         SEventConfig::SetMaxSeq(maxbounce+1);
    564         SEventConfig::SetMaxPrd(maxbounce+1);
    565         SEventConfig::SetMaxAux(maxbounce+1);
    567         // since moved to compound sflat/stag so MaxFlat/MaxTag should now either be 0 or 1, nothing else  
    568         SEventConfig::SetMaxTag(1);
    569         SEventConfig::SetMaxFlat(1);
    570         SEventConfig::SetMaxSup(1);
    571 
    572         SetCompAuto() ;   // comp set based on Max values    



aux,sup GPU side shakedown
-----------------------------

* note that aux, sup are just not gathered from GPU side
* TODO: review aux,sup CPU side and GPU side to see if makes sense to gather from GPU 

::

    652 NP* QEvent::gatherComponent_(unsigned cmp) const
    653 {   
    654     NP* a = nullptr ;
    655     switch(cmp)
    656     {   
    657         case SCOMP_GENSTEP:   a = getGenstep()     ; break ;   
    658         case SCOMP_DOMAIN:    a = gatherDomain()      ; break ;
    659         case SCOMP_INPHOTON:  a = getInputPhoton() ; break ;
    660         
    661         case SCOMP_PHOTON:    a = gatherPhoton()   ; break ;
    662         case SCOMP_RECORD:    a = gatherRecord()   ; break ;
    663         case SCOMP_REC:       a = gatherRec()      ; break ;
    664         case SCOMP_SEQ:       a = gatherSeq()      ; break ;
    665         case SCOMP_PRD:       a = gatherPrd()      ; break ;
    666         case SCOMP_SEED:      a = gatherSeed()     ; break ;
    667         case SCOMP_HIT:       a = gatherHit()      ; break ;
    668         case SCOMP_SIMTRACE:  a = gatherSimtrace() ; break ;
    669         case SCOMP_TAG:       a = gatherTag()      ; break ;
    670         case SCOMP_FLAT:      a = gatherFlat()     ; break ;  
    671         // gather downloads from device, get access from host 
    672     }   
    673     return a ;
    674 }


aux, sup
~~~~~~~~~~

::

     65 struct sctx
     66 {
     67     sevent* evt ;
     68     const quad2* prd ;
     69     unsigned idx ;
     70 
     71     sphoton p ;
     72     sstate  s ;
     73 
     74 #ifndef PRODUCTION
     75     srec rec ;
     76     sseq seq ;
     77     stagr tagr ;
     78     quad4 aux ;
     79     quad6 sup ;
     80     // NB these are heavy : important to test with and without PRODUCTION 
     81     // as these are expected to be rather expensive  
     82 #endif



CPU side sup carries time stamp ranges and counts see SEvt::addProcessHitsStamp : unclear how to do that GPU side
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


CPU side aux collects details of the boundary calc, could so the same GPU side
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    1006 #if defined(WITH_CUSTOM4)
    1007 template<>
    1008 void U4Recorder::CollectBoundaryAux<C4OpBoundaryProcess>(quad4* current_aux)
    1009 {
    1010     C4OpBoundaryProcess* bop = U4OpBoundaryProcess::Get<C4OpBoundaryProcess>() ;
    1011     assert(bop) ;
    1012     assert(current_aux);
    1013 
    1014     char customStatus = bop ? bop->m_custom_status : 'B' ;
    1015     C4CustomART* cart   = bop ? bop->m_custom_art : nullptr ;
    1016     const double* recoveredNormal =  bop ? (const double*)&(bop->theRecoveredNormal) : nullptr ;
    1017 
    1018 #ifdef C4_DEBUG
    1019     C4CustomART_Debug* cdbg = cart ? &(cart->dbg) : nullptr ;
    1020 #else
    1021     C4CustomART_Debug* cdbg = nullptr ;
    1022 #endif
    1023 
    1024     LOG(LEVEL)
    1025         << " bop " << ( bop ? "Y" : "N" )
    1026         << " cart " << ( cart ? "Y" : "N" )
    1027         << " cdbg " << ( cdbg ? "Y" : "N" )
    1028         << " current_aux " << ( current_aux ? "Y" : "N" )
    1029         << " bop.m_custom_status " << customStatus
    1030         << " CustomStatus::Name " << CustomStatus::Name(customStatus)
    1031         ;
    1032 
    1033     if(cdbg && customStatus == 'Y') current_aux->load( cdbg->data(), C4CustomART_Debug::N ) ;
    1034     current_aux->set_v(3, recoveredNormal, 3);   // nullptr are just ignored
    1035     current_aux->q3.i.w = int(customStatus) ;    // moved from q1 to q3
    1036 }



