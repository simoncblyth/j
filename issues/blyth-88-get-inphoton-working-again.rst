blyth-88-get-inphoton-working-again
====================================


Overview : check again input photon running, chi2 check 
-----------------------------------------------------

Reusing ntds2_cf after uncommenting IPHO 10k. 


FIXED : SEGV on trying to save inphoton within second event
---------------------------------------------------------------

Maybe the inphoton is being cleared ?::

    Begin of Event --> 0
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 2 with m_jpmt_dbg YES
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 2 hitCollection 3083 hcMuon 0 hcOpticks 0 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2347:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::gatherHit@2020:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@812: 
    GtOpticksTool::mutate event_number 1 numPhotons 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize eventID 1
    junoSD_PMT_v2_Opticks::Initialize opticksMode 2 eventID 1 LEVEL 5:DEBUG


    Begin of Event --> 1
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 1 opticksMode 2 with m_jpmt_dbg YES
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 2 hitCollection 0 hcMuon 0 hcOpticks 0 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2347:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001
    SEvt::gatherHit@2020:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 

    Program received signal SIGSEGV, Segmentation fault.
    NPS::size (shape=...) at /data/blyth/junotop/opticks/sysrap/NPU.hh:286
    286	        for(unsigned i=0; i<shape.size(); ++i) sz *= shape[i] ;



DONE : Checking persisted first event, looks fine
------------------------------------------------------

::

    N[blyth@localhost 000]$ pwd
    /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000


    In [1]: a = np.load("inphoton.npy")

    In [2]: a.shape
    Out[2]: (10000, 4, 4)

    In [4]: np.set_printoptions(suppress=True)

    In [5]: a[0]
    Out[5]: 
    array([[-12052.89648438,   9510.56152344,  11538.32910156,      0.1       ],
           [    -0.62137848,      0.49031082,      0.6111334 ,      1.        ],
           [    -0.61944878,     -0.78503704,      0.        ,    440.        ],
           [     0.        ,      0.        ,      0.        ,      0.        ]], dtype=float32)

    In [6]: a[-1]
    Out[6]: 
    array([[-11813.015625  ,   9321.27832031,  11934.09277344,      0.1       ],
           [    -0.62137848,      0.49031082,      0.6111334 ,      1.        ],
           [    -0.61944878,     -0.78503704,      0.        ,    440.        ],
           [     0.        ,      0.        ,      0.        ,      0.        ]], dtype=float32)




FIXED : 2nd event SEGV from inphoton
--------------------------------------

Are pushing the envelope with multi-event input photon running. 
Previously just did single event input photon and simtrace running
with multi-event only exercised for ordinary S+C genstep running. 

Left field issue::

    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2347:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001

    Program received signal SIGSEGV, Segmentation fault.
    NPS::size (shape=...) at /data/blyth/junotop/opticks/sysrap/NPU.hh:286
    286	        for(unsigned i=0; i<shape.size(); ++i) sz *= shape[i] ;
    (gdb) bt
    #0  NPS::size (shape=...) at /data/blyth/junotop/opticks/sysrap/NPU.hh:286
    #1  0x00007fffcf1e09d2 in NP::arr_bytes (this=0x18dea2b30) at /data/blyth/junotop/opticks/sysrap/NP.hh:738
    #2  0x00007fffcf1e38d7 in NP::save (this=0x18dea2b30, path_=0x24960cbe0 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001/inphoton.npy")
        at /data/blyth/junotop/opticks/sysrap/NP.hh:4248
    #3  0x00007fffcf1fc944 in NP::save (this=0x18dea2b30, dir=0x24960e8c0 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001", 
        name=0x24b976370 "inphoton.npy") at /data/blyth/junotop/opticks/sysrap/NP.hh:4264
    #4  0x00007fffcf25e8d9 in NPFold::_save_arrays (this=0xb52ec0, base=0x24960e8c0 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001")
        at /data/blyth/junotop/opticks/sysrap/NPFold.h:801
    #5  0x00007fffcf25e763 in NPFold::save (this=0xb52ec0, base_=0x245309b40 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001")
        at /data/blyth/junotop/opticks/sysrap/NPFold.h:781
    #6  0x00007fffcf252f96 in SEvt::save (this=0xb52790, dir_=0x7fffcf3365ba "$DefaultOutputDir")
        at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2358
    #7  0x00007fffcf25245e in SEvt::save (this=0xb52790) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2250
    #8  0x00007fffcf24af4d in SEvt::Save () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:752
    #9  0x00007fffd29a90e1 in U4Recorder::EndOfEventAction (this=0xb29880, event=0x2453463d0)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:220
    #10 0x00007fffcddf49a8 in U4RecorderAnaMgr::EndOfEventAction (this=0xb52600, evt=0x2453463d0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:32


Problem with inphoton::

    (gdb) f 8
    #8  0x00007fffcf24af4d in SEvt::Save () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:752
    752	void SEvt::Save(){  Check() ; INSTANCE->save(); }
    (gdb) f 7
    #7  0x00007fffcf25245e in SEvt::save (this=0xb52790) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2250
    2250	    save(dir); 
    (gdb) p dir
    $1 = 0x7fffcf3365ba "$DefaultOutputDir"
    (gdb) f 6
    #6  0x00007fffcf252f96 in SEvt::save (this=0xb52790, dir_=0x7fffcf3365ba "$DefaultOutputDir")
        at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2358
    2358	    fold->save(dir); 
    (gdb) p dir
    $2 = 0x245309b40 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001"
    (gdb) f 5
    #5  0x00007fffcf25e763 in NPFold::save (this=0xb52ec0, base_=0x245309b40 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001")
        at /data/blyth/junotop/opticks/sysrap/NPFold.h:781
    781	    _save_arrays(base); 
    (gdb) f 4
    #4  0x00007fffcf25e8d9 in NPFold::_save_arrays (this=0xb52ec0, base=0x24960e8c0 "/tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/001")
        at /data/blyth/junotop/opticks/sysrap/NPFold.h:801
    801	            a->save(base, k );  
    (gdb) p k
    $3 = 0x24b976370 "inphoton.npy"
    (gdb) p a
    $4 = (const NP *) 0x18dea2b30
    (gdb) p this
    $5 = (NPFold * const) 0xb52ec0
    (gdb) 


::

     789 inline void NPFold::_save_arrays(const char* base) // using the keys with .npy ext as filenames
     790 {
     791     for(unsigned i=0 ; i < kk.size() ; i++)
     792     {
     793         const char* k = kk[i].c_str() ;
     794         const NP* a = aa[i] ;
     795         if( a == nullptr )
     796         {
     797             std::cout << " base " << base << " k " << k << " ERROR MISSING ARRAY FOR KEY " << std::endl ;
     798         }
     799         else
     800         {
     801             a->save(base, k );
     802         }
     803     }
     804     // this motivated adding directory creation to NP::save 
     805 }


That pointer is very different to the others::

    (gdb) p a
    $4 = (const NP *) 0x18dea2b30
    (gdb) p this
    $5 = (NPFold * const) 0xb52ec0
    (gdb) p i
    $6 = 6
    (gdb) p aa[6]
    $7 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15830: 0x18dea2b30
    (gdb) p aa[5]
    $8 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15828: 0x245308e10
    (gdb) p aa[4]
    $9 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15820: 0x237d47f30
    (gdb) p aa[3]
    $10 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15818: 0x2453098b0
    (gdb) p aa[2]
    $11 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15810: 0x24960cad0
    (gdb) p aa[1]
    $12 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15808: 0x24960c170
    (gdb) p aa[0]
    $13 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15800: 0x24960eaa0
    (gdb) p aa[7]
    $14 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15838: 0x245309030
    (gdb) p aa[8]
    $15 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15840: 0x237d46dc0
    (gdb) p aa[9]
    $16 = (__gnu_cxx::__alloc_traits<std::allocator<NP const*>, NP const*>::value_type &) @0x24af15848: 0x24960e740
    (gdb) p kk.size()
    $17 = 10
    (gdb) 

    (gdb) p shape
    $18 = (const std::vector<int, std::allocator<int> > &) @0x18dea2b48: {<std::_Vector_base<int, std::allocator<int> >> = {
        _M_impl = {<std::allocator<int>> = {<__gnu_cxx::new_allocator<int>> = {<No data fields>}, <No data fields>}, _M_start = 0x24b9764a0, 
          _M_finish = 0x18dd69e0c, _M_end_of_storage = 0x18dd69e10}}, <No data fields>}
    (gdb) p shape.size()
    $19 = 18446744072913669723
    (gdb) 


DONE : Review : Recent tidy of junoSD_PMT_v2_Opticks removed input photon related stuff
------------------------------------------------------------------------------------------

Recently removed the SEvt::SetInputPhoton in junoSD_PMT_v2_Opticks::Initialize

* dont think this is the cause
* probably its because dont usually do multievent with inphoton, so are pushing envelope 

::

    epsilon:junosw blyth$ git diff main Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc

     void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
     {
    -    const GtOpticksTool* tool = GtOpticksTool::Get(); 
    +    SEvt::TimerStart() ; 
     
    -#ifdef WITH_G4CXOPTICKS
    -    NP* input_photons = tool ? tool->getInputPhotons() : nullptr ; 
    -#elif WITH_G4OPTICKS
    -    NPY<float>* input_photons = tool ? tool->getInputPhotons() : nullptr ;
    -    G4Opticks* g4ok = G4Opticks::Get() ;
    -#elif WITH_G4OPTICKS
    -    NPY<float>* input_photons = tool ? tool->getInputPhotons() : nullptr ;
    -    G4Opticks* g4ok = G4Opticks::Get() ;
    -#endif
    -
    -    int input_photon_repeat = tool ? tool->getInputPhotonRepeat() : 0 ; 
    -    const char* wavelength = tool ? tool->getInputPhotonWavelength() : nullptr ; 
    -
    -    LOG(debug) 
    +    std::cerr
    +        << "junoSD_PMT_v2_Opticks::Initialize"
    +        << " opticksMode " << m_opticksMode
             << " eventID " << eventID
    -        << " wavelength " << wavelength  
    -        << " tool " << tool 
    -        << " input_photons " << input_photons 
    -        << " input_photon_repeat " << input_photon_repeat 
             << " LEVEL " << LEVEL << ":" << plog::severityToString(LEVEL) 
    +        << std::endl 
             ; 
    -
    -
    -    if(input_photons)
    -    {
    -#ifdef WITH_G4CXOPTICKS 
    -        SEvt::SetInputPhoton(input_photons); 
    -#elif WITH_G4OPTICKS
    -        g4ok->setInputPhotons(input_photons, input_photon_repeat, wavelength, eventID ); 
    -#endif
    -    }
     }
    -#endif




    148 
    149 #ifdef WITH_G4CXOPTICKS
    150 bool GtOpticksTool::mutate(HepMC::GenEvent& event)
    151 {   
    152     int event_number = event.event_number() ; // is this 0-based ? 
    153     if(m_input_photon == nullptr)
    154     {   
    155         m_input_photon = SEvt::GetInputPhoton() ;
    156         std::cerr 
    157             << "GtOpticksTool::mutate"
    158             << " event_number " << event_number
    159             << " deferred SEvt::GetInputPhoton "
    160             << " " << SEvt::Brief()
    161             << " m_input_photon " << ( m_input_photon ? m_input_photon->sstr() : "-" )
    162             << std::endl
    163             ;



DONE : Try to fix this with a gatherInputPhoton that copies 
-----------------------------------------------------------------

::

    1985 NP* SEvt::gatherComponent_(unsigned comp) const
    1986 {   
    1987     NP* a = nullptr ;
    1988     switch(comp)
    1989     {   
    1990         case SCOMP_INPHOTON:  a = getInputPhoton() ; break ;
    1991         case SCOMP_G4STATE:   a = gatherG4State()  ; break ;
    1992         
    1993         case SCOMP_GENSTEP:   a = gatherGenstep()  ; break ;
    1994         case SCOMP_DOMAIN:    a = gatherDomain()   ; break ;



::

     825 void SEvt::clear()
     826 {
     827     LOG(LEVEL) << "[" ;
     828     clear_();
     829     if(fold) fold->clear();
     830     LOG(LEVEL) << "]" ;
     831 }




FIXED : Another beginPhoton not in range issue on 2nd event : needed SEvt::addFrameGenstep for every cycle
--------------------------------------------------------------------------------------------------------------

::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists Y INSTANCE SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )
    GtOpticksTool::mutate event_number 0 numPhotons 10000
     idx 0 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 1 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 2 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 3 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 4 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 5 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 6 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 7 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 2 eventID 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 2 with m_jpmt_dbg YES
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 2 hitCollection 3083 hcMuon 0 hcOpticks 0 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    SEvt::save@2368:  dir /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/000
    SEvt::gatherHit@2041:  not yet implemented for hostside running : avoid this error by changing CompMask with SEventConfig 
    SEvt::clear_@833: 
    GtOpticksTool::mutate event_number 1 numPhotons 10000
     idx 0 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 1 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 2 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 3 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 4 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 5 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 6 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 7 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 1 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 

    junoSD_PMT_v2::Initialize eventID 1
    junoSD_PMT_v2_Opticks::Initialize opticksMode 2 eventID 1 LEVEL 5:DEBUG
    Begin of Event --> 1
    SEvt::beginPhoton@1302:  not in_range  idx 9999 pho.size  0 label spho (gs:ix:id:gn   09999 9999[  0,  0,  0,  0])
    SEvt::beginPhoton FATAL not in_range idx 9999 pho.size  0 label spho (gs:ix:id:gn   09999 9999[  0,  0,  0,  0])
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1317: void SEvt::beginPhoton(const spho&): Assertion `in_range' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6


    (gdb) f 7
    #7  0x00007fffcddf49d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0xb52600, trk=0x245ae4260)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    33	void U4RecorderAnaMgr::PreUserTrackingAction(const G4Track* trk) {  m_recorder->PreUserTrackingAction(trk);  } 
    (gdb) f 6
    #6  0x00007fffd29a9304 in U4Recorder::PreUserTrackingAction (this=0xb29880, track=0x245ae4260)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:227
    227	void U4Recorder::PreUserTrackingAction(const G4Track* track){  LOG(LEVEL) ; if(U4Track::IsOptical(track)) PreUserTrackingAction_Optical(track); }
    (gdb) f 5
    #5  0x00007fffd29a9aa0 in U4Recorder::PreUserTrackingAction_Optical (this=0xb29880, track=0x245ae4260)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:297
    297	            sev->beginPhoton(ulabel);  // THIS ZEROS THE SLOT 
    (gdb) p ulabel
    $1 = {static N = 4, gs = 0, ix = 9999, id = 9999, uc4 = {x = 0 '\000', y = 0 '\000', z = 0 '\000', w = 0 '\000'}}
    (gdb) f 4
    #4  0x00007fffcf24ddea in SEvt::beginPhoton (this=0xb52790, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1317
    1317	    assert(in_range);  
    (gdb) p hostside_running_resize_done
    $2 = true
    (gdb) 

::

    1062 void SEvt::setNumPhoton(unsigned num_photon)
    1063 {
    1064     bool num_photon_allowed = int(num_photon) <= evt->max_photon ;
    1065     LOG_IF(fatal, !num_photon_allowed) << " num_photon " << num_photon << " evt.max_photon " << evt->max_photon ;
    1066     assert( num_photon_allowed );
    1067 
    1068     evt->num_photon = num_photon ;
    1069     evt->num_seq    = evt->max_seq   > 0 ? evt->num_photon : 0 ;
    1070     evt->num_tag    = evt->max_tag  == 1 ? evt->num_photon : 0 ;
    1071     evt->num_flat   = evt->max_flat == 1 ? evt->num_photon : 0 ;
    1072 
    1073     evt->num_record = evt->max_record * evt->num_photon ;
    1074     evt->num_rec    = evt->max_rec    * evt->num_photon ;
    1075     evt->num_aux    = evt->max_aux    * evt->num_photon ;
    1076     evt->num_prd    = evt->max_prd    * evt->num_photon ;
    1077 
    1078     LOG(info)
    1079         << " evt->num_photon " << evt->num_photon
    1080         << " evt->num_tag " << evt->num_tag
    1081         << " evt->num_flat " << evt->num_flat
    1082         ;
    1083 
    1084     hostside_running_resize_done = false ;
    1085 }


DONE : SEvt_Lifecycle_Test.cc suggests need to SEvt::setFrame every cycle to allocate
---------------------------------------------------------------------------------------------

Q: Where is the frame being set with input photon running ?
A: Currently with G4CXOpticks::setupFrame which looks to be misplaced
   as it needs to be done every event cycle

DONE: split off the every cycle actions into SEvt::addFrameGenstep from SEvt::setFrame 
and moved to invoking from SEvt::BeginOfEvent

::

    272 void G4CXOpticks::setGeometry(CSGFoundry* fd_)
    273 {
    274     setGeometry_(fd_);
    275     setupFrame();    // EXPT: MOVED HERE TO INITIALIZATION
    276 }


    330 /**
    331 G4CXOpticks::setupFrame
    332 -------------------------
    333 
    334 The frame used depends on envvars INST, MOI, OPTICKS_INPUT_PHOTON_FRAME 
    335 it comprises : fr.ce fr.m2w fr.w2m set by CSGTarget::getFrame 
    336 
    337 This setupFrame was formerly called from G4CXOpticks::simulate and G4CXOpticks::simtrace
    338 it is now moved to G4CXOpticks::setGeometry. 
    339 
    340 Q: why is the frame needed ?
    341 A: cx rendering viewpoint, input photon frame and the simtrace genstep grid 
    342    are all based on the frame center, extent and transforms 
    343 
    344 Q: This feels like too high level to do this, should be at CSG level perhaps ? 
    345    And then CSGOptix could grab the SEvt frame at its initialization. 
    346 
    347 **/
    348 
    349 void G4CXOpticks::setupFrame()
    350 {
    351     SEvt* sev = SEvt::Get();
    352     assert(sev); 
    353     
    354     sframe fr = fd->getFrameE() ;
    355     LOG(LEVEL) << fr ; 
    356     
    357     sev->setFrame(fr);
    358     if(cx) cx->setFrame(fr);
    359 }   
    360 


::

     418 void SEvt::setFrame(const sframe& fr )
     419 {
     420     frame = fr ;
     421     // addFrameGenstep(); // relocated to SEvt::BeginOfEvent
     422 }



DONE : check again ntds2_cf with IPHO RainXZ_Z230_10k_f8.npy
--------------------------------------------------------------

::

    N[blyth@localhost junosw]$ t ntds2_cf
    ntds2_cf () 
    { 
        : ntds2 is Geant4 running with Opticks U4Recorder instrumentation;
        : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories;
        : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds;
        export EVTMAX=10;
        N=0 GEOM=V0J008 ntds2;
        [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1;
        N=1 GEOM=V1J008 ntds2;
        [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2;
        return 0
    }
    N[blyth@localhost junosw]$ 

    N[blyth@localhost junosw]$ t ntds
    ntds () 
    { 
        env | grep --color=auto =INFO;
        local args=$*;
        local msg="=== $FUNCNAME :";
        local trgs="";
        ...

        IPHO=RainXZ_Z230_10k_f8.npy;
        layout="";
        if [ -n "$IPHO" ]; then
            export OPTICKS_INPUT_PHOTON=$IPHO;
            moi=Hama:0:1000;
            export MOI=${MOI:-$moi};
            layout="ip_MOI_$MOI";
            echo $msg IPHO defined : configuring OPTICKS_INPUT_PHOTON $OPTICKS_INPUT_PHOTON;
            trgs="$trgs opticks";
        else
            unset OPTICKS_INPUT_PHOTON;
            unset MOI;
            echo $msg IPHO not defined : not configuring OPTICKS_INPUT_PHOTON;
            trgs="$trgs gun";
        fi;




DONE : Rerun succeeds
------------------------

::

    N[blyth@localhost junosw]$ ntds2_cf   ## workstation

    epsilon:ntds blyth$ ./ntds.sh grab_evt    ## laptop

    epsilon:ntds blyth$ ./ntds.sh cfmeta
             BASH_SOURCE : ./ntds.sh 
                   CHECK : all_point 
                     arg : cfmeta 
                  defarg : ana 
                     DIR : . 
            OPTICKS_MODE : 2 
                  SCRIPT : ntds2 
                    BASE :  
                     EVT : %0.3d 
                   AGEOM : V0J008 
                   ABASE : /tmp/blyth/opticks/GEOM/V0J008/ntds2 
                   AFOLD : /tmp/blyth/opticks/GEOM/V0J008/ntds2/ALL0/%0.3d 
                   BGEOM : V1J008 
                   BBASE : /tmp/blyth/opticks/GEOM/V1J008/ntds2 
                   BFOLD : /tmp/blyth/opticks/GEOM/V1J008/ntds2/ALL1/%0.3d 
                       N :  
                 VERSION : -1 
                   UBASE :  
    ./ntds.sh VERSION:-1 load both AFOLD and BFOLD
    ./ntds.sh : anascript :
    CSGFoundry.CFBase returning None, note:via NO envvars 
    ERROR CSGFoundry.CFBase returned None OR non-existing CSGFoundry dir so cannot CSGFoundry.Load

    msab.c_itab

    array([[[ 8136,  8309,  8096,  8228,  8424,  8073,  8296,  8365,  8205,  8277],       ProcessHits_count 
            [ 9995, 10339, 10280, 10297, 10391, 10323,  9911,  9955, 10347, 10711]],        
            
           [[ 1344,  1405,  1427,  1404,  1336,  1373,  1457,  1421,  1385,  1375],       ProcessHits_true 
            [ 1456,  1412,  1361,  1444,  1424,  1466,  1359,  1332,  1373,  1437]],        
            
           [[ 6792,  6904,  6669,  6824,  7088,  6700,  6839,  6944,  6820,  6902],       ProcessHits_false 
            [ 8539,  8927,  8919,  8853,  8967,  8857,  8552,  8623,  8974,  9274]],        
            
           [[ 1344,  1405,  1427,  1404,  1336,  1373,  1457,  1421,  1385,  1375],       SaveNormHit_count 
            [ 1456,  1412,  1361,  1444,  1424,  1466,  1359,  1332,  1373,  1437]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       SaveMuonHit_count 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       UNSET 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       NDIS 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       NOPT 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[ 6584,  6706,  6492,  6644,  6881,  6494,  6662,  6745,  6636,  6691],       NEDEP 
            [ 8330,  8743,  8703,  8646,  8756,  8656,  8363,  8412,  8768,  9045]],        
            
           [[    0,     1,     0,     1,     0,     0,     0,     0,     0,     0],       NBOUND 
            [   17,    25,    13,    23,    29,    31,    21,    21,    22,    21]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       NPROC 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       NDETECT 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[  208,   197,   177,   179,   207,   206,   177,   199,   184,   211],       NDECULL 
            [  192,   159,   203,   184,   182,   170,   168,   190,   184,   208]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       YMERGE 
            [    0,     0,     0,     0,     0,     0,     0,     0,     0,     0]],        
            
           [[ 1344,  1405,  1427,  1404,  1336,  1373,  1457,  1421,  1385,  1375],       YSAVE 
            [ 1456,  1412,  1361,  1444,  1424,  1466,  1359,  1332,  1373,  1437]],        
            
           [[    2,     2,     2,     2,     2,     2,     2,     2,     2,     2],       opticksMode 
            [    2,     2,     2,     2,     2,     2,     2,     2,     2,     2]],        
            
           [[    0,     1,     2,     3,     4,     5,     6,     7,     8,     9],       eventID 
            [    0,     1,     2,     3,     4,     5,     6,     7,     8,     9]],        
            
           [[    0,     0,     0,     0,     0,     0,     0,     0,     0,     0],       VERSION 
            [    1,     1,     1,     1,     1,     1,     1,     1,     1,     1]]], dtype=uint64)        

    msab.c_ftab

    array([[[2.033, 2.473, 1.962, 1.961, 1.974, 1.96 , 1.966, 1.981, 1.946, 2.058],       SEvt__TimerDone 
            [1.911, 1.833, 1.867, 1.88 , 1.869, 2.269, 1.927, 2.172, 1.878, 1.892]]])        

    msab.c_ftab[0,1].sum()/msab.c_ftab[0,0].sum()  # ratio of duration totals N=1/N=0 FMT:%10.4f

        0.9599

    np.diff(msab.c_ttab)/1e6   # seconds between event starts

    array([[[2.319, 2.803, 2.282, 2.212, 2.296, 2.273, 2.282, 2.748, 2.249],
            [2.193, 2.51 , 2.113, 2.134, 2.191, 3.442, 2.172, 2.42 , 2.26 ]]])

    np.c_[msab.c_ttab[0].T].view('datetime64[us]') # SEvt start times (UTC)

    array([['2023-04-15T14:21:16.478345', '2023-04-15T14:26:21.851744'],
           ['2023-04-15T14:21:18.796948', '2023-04-15T14:26:24.044676'],
           ['2023-04-15T14:21:21.600241', '2023-04-15T14:26:26.554724'],
           ['2023-04-15T14:21:23.882363', '2023-04-15T14:26:28.667469'],
           ['2023-04-15T14:21:26.094289', '2023-04-15T14:26:30.801561'],
           ['2023-04-15T14:21:28.390379', '2023-04-15T14:26:32.992083'],
           ['2023-04-15T14:21:30.663470', '2023-04-15T14:26:36.434110'],
           ['2023-04-15T14:21:32.945789', '2023-04-15T14:26:38.606420'],
           ['2023-04-15T14:21:35.693866', '2023-04-15T14:26:41.026458'],
           ['2023-04-15T14:21:37.943079', '2023-04-15T14:26:43.286450']], dtype='datetime64[us]')

    msab.c2tab  # c2sum, c2n, c2per for each event

    array([[57.087, 64.866, 41.019, 54.365, 38.898, 48.919, 65.558, 59.794, 54.986, 56.472],
           [57.   , 55.   , 58.   , 55.   , 56.   , 59.   , 59.   , 58.   , 60.   , 58.   ],
           [ 1.002,  1.179,  0.707,  0.988,  0.695,  0.829,  1.111,  1.031,  0.916,  0.974]])

    msab.c2tab[0,:].sum()/msab.c2tab[1,:].sum() # c2per_tot FMT:%10.4f

        0.9425

    In [1]:                



FIXED : ntds.sh ana shows the input photon frame targetting is not working : photons starting mid-CD
----------------------------------------------------------------------------------------------------


Hmm, the inphoton is transformed. Just not in time. ::

    epsilon:opticks blyth$ git commit -m "split SEvt::transformInputPhoton from SEvt::addFrameGenstep and do that from SEvt::setFrame as the transformed input photons are needed earlier than SEvt::BeginOfEvent "
    [master 5fb3671c8] split SEvt::transformInputPhoton from SEvt::addFrameGenstep and do that from SEvt::setFrame as the transformed input photons are needed earlier than SEvt::BeginOfEvent
     9 files changed, 127 insertions(+), 58 deletions(-)








