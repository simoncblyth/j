lack-of-B-side-hit
====================

::

     306 void U4Recorder::EndOfEventAction_(int eventID_)
     307 {
     308     assert( eventID == eventID_ ); 
     309     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     310 
     311     #if defined(WITH_PMTSIM) && defined(POM_DEBUG)
     312         NP* mtda = PMTSim::ModelTrigger_Debug_Array();
     313         std::string name = mtda->get_meta<std::string>("NAME", "MTDA.npy") ;
     314         sev->add_array( name.c_str(), mtda );   
     315     #else
     316         LOG(LEVEL) << "not-(WITH_PMTSIM and POM_DEBUG)"  ;
     317     #endif
     318 
     319     sev->add_array("TRS.npy", U4VolumeMaker::GetTransforms() );
     320     sev->add_array("U4R.npy", MakeMetaArray() );
     321     sev->addEventConfigArray(); 
     322 
     323     // SEvt::endOfEvent THIS TAKES IMPORTANT ACTIONS
     324     // BUT USING THE RECORDER IS OPTIONAL ? 
     325     sev->endOfEvent(eventID_);  // does save and clear
     326 
     327     const char* savedir = sev->getSaveDir() ; 
     328     LOG(info) << " savedir " << ( savedir ? savedir : "-" );
     329     SaveMeta(savedir);  
     330 
     331 }


::

    epsilon:ALL0 blyth$ cd n001
    epsilon:n001 blyth$ l
    total 62544
        0 drwxrwxr-x  10 blyth  staff       320 Nov 28 20:15 ..
        0 drwxr-xr-x  10 blyth  staff       320 Nov 28 20:11 .
        8 -rw-rw-r--   1 blyth  staff       144 Nov 28 20:11 gs.npy
        8 -rw-rw-r--   1 blyth  staff       384 Nov 28 20:11 sframe.npy
        8 -rw-rw-r--   1 blyth  staff       113 Nov 28 20:11 sframe_meta.txt
    31256 -rw-rw-r--   1 blyth  staff  16000128 Nov 28 20:11 pho.npy
    31256 -rw-rw-r--   1 blyth  staff  16000128 Nov 28 20:11 pho0.npy
        8 -rw-rw-r--   1 blyth  staff       921 Nov 28 20:11 NPFold_meta.txt
        0 -rw-rw-r--   1 blyth  staff         0 Nov 28 20:11 NPFold_names.txt
        0 -rw-rw-r--   1 blyth  staff         0 Nov 28 20:11 NPFold_index.txt
    epsilon:n001 blyth$ 
    epsilon:n001 blyth$ 
    epsilon:n001 blyth$ opticks-
    epsilon:n001 blyth$ opticks-f pho0
    ./ana/catdir.py:        numpho0 = mds[0].numPhotons
    ./ana/catdir.py:            if md.numPhotons == numpho0:
    ./ana/fold.py:    Observe some pho0.npy with header only and no content ? 
    ./sysrap/SEvt.hh:    std::vector<spho>    pho0 ;  // unordered push_back as they come 
    ./sysrap/SEvt.cc:    pho0.clear(); 
    ./sysrap/SEvt.cc:    pho0.push_back(label);    // push_back asis for debugging
    ./sysrap/SEvt.cc:NP* SEvt::gatherPho0() const { return NPX::Make<int>( (int*)pho0.data(), int(pho0.size()), 4 ); }
    ./sysrap/SEvt.cc:    if(a0) a0->save(dir, "pho0.npy"); 
    ./sysrap/SEvt.cc:       << " pho0 " << pho0.size()  
    ./u4/tests/U4RecorderTest.py:    When reemission is enabled this would fail for pho0 (push_back labels)
    epsilon:opticks blyth$ 


A side::

    809 NP* QEvent::gatherComponent_(unsigned cmp) const
    810 {
    811     NP* a = nullptr ;
    812     switch(cmp)
    813     {
    814         case SCOMP_GENSTEP:   a = getGenstep()     ; break ;
    815         case SCOMP_INPHOTON:  a = getInputPhoton() ; break ;
    816 
    817         case SCOMP_PHOTON:    a = gatherPhoton()   ; break ;
    818         case SCOMP_HIT:       a = gatherHit()      ; break ;
    819 #ifndef PRODUCTION
    820         case SCOMP_DOMAIN:    a = gatherDomain()      ; break ;
    821         case SCOMP_RECORD:    a = gatherRecord()   ; break ;
    822         case SCOMP_REC:       a = gatherRec()      ; break ;
    823         case SCOMP_SEQ:       a = gatherSeq()      ; break ;
    824         case SCOMP_PRD:       a = gatherPrd()      ; break ;
    825         case SCOMP_SEED:      a = gatherSeed()     ; break ;
    826         case SCOMP_SIMTRACE:  a = gatherSimtrace() ; break ;
    827         case SCOMP_TAG:       a = gatherTag()      ; break ;
    828         case SCOMP_FLAT:      a = gatherFlat()     ; break ;
    829 #endif
    830     }
    831     return a ;
    832 }


