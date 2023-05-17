ntds2_cf_incorrectly_using_opticksMode_3_and_asserting
========================================================

Overview
---------

OpticksMode 3 means that QEvent gets instanciated that calls 
SEvt::setCompProvider resulting in the is_self_provider assert
within SEvt::beginPhoton

Cause : seems ntds2_cf was untested using "ntds" when should use "ntds2" 
---------------------------------------------------------------------------

::

    ntds2_cf()
    {
       : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories
       : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds

       export EVTMAX=3
       #export NODBG=1 

       N=0 GEOM=V0J008 ntds2
       [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1

       N=1 GEOM=V1J008 ntds2
       [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2

       return 0
    }


Issue : OOPS USING ntds (defaulting to 3 it seems) WHEN NEED ntds2
---------------------------------------------------------------------

::

    N[blyth@localhost junosw]$ t ntds2_cf    
    ntds2_cf () 
    { 
        : this function runs simulation with N:0 and N:1 geometries allowing comparison of histories;
        : the logs are copied into event dir from TDS_LOG_COPYDIR setting by ntds;
        export EVTMAX=3;
        N=0 GEOM=V0J008 ntds;
        [ $? -ne 0 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 0 && return 1;
        N=1 GEOM=V1J008 ntds;
        [ $? -ne 1 ] && echo $BASH_SOURCE $FUNCNAME ERROR N 1 && return 2;
        return 0
    }
    N[blyth@localhost junosw]$ ntds2_cf
    === ntds : OPTICKS_MODE is active and OPTICKS_PREFIX /data/blyth/junotop/ExternalLibs/opticks/head is detected
                FUNCNAME : ntds 
                  SCRIPT : ntds3 
                 TDS_DIR : /tmp/u4debug/ntds3 
                 TDS_LOG : /tmp/u4debug/ntds3/ntds3.log 
                  SCRIPT : ntds3 
         U4Debug_SaveDir : /tmp/u4debug/ntds3 
    === ntds : DEBUG NOT-enabled
    === ntds : DISABLE-NOT-enabled

    /home/blyth/j/jx.bash : ENABLED U4Recorder__FAKES_SKIP : 1
    === ntds : opts : --opticks-mode 3 --no-guide_tube --additionacrylic-simplify-csg --pmt-optical-model --pmt-unnatural-geometry --evtmax 3 --opticks-anamgr --no-anamgr-normal --no-anamgr-genevt --no-anamgr-edm-v2 --no-anamgr-grdm --no-anamgr-deposit --no-anamgr-deposit-tt --no-anamgr-interesting-process --no-anamgr-optical-parameter --no-anamgr-timer
    === ntds : trgs : opticks
    === ntds : args :


     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    SEvt::MakeInputPhotonGenstep@655:  input_photon (10000, 4, 4, )
    Begin of Event --> 0
    SEvt::hostside_running_resize@1232:  NOT-is_self_provider SEvt::descProvider provider: 0x18ee6ccd0 that address is: another object
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1239: void SEvt::hostside_running_resize(): Assertion `is_self_provider' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf24a76d in SEvt::hostside_running_resize (this=0xb53000) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1239
    #5  0x00007fffcf24aff4 in SEvt::beginPhoton (this=0xb53000, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1418
    #6  0x00007fffd29a8b16 in U4Recorder::PreUserTrackingAction_Optical (this=0xb29cb0, track=0x7fff0ba6a880)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:298
    #7  0x00007fffd29a82d0 in U4Recorder::PreUserTrackingAction (this=0xb29cb0, track=0x7fff0ba6a880)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:224
    #8  0x00007fffcddef9d6 in U4RecorderAnaMgr::PreUserTrackingAction (this=0x93bd50, trk=0x7fff0ba6a880)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    #9  0x00007fffce805d39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffcea14b00 <MgrOfAnaElem::instance()::s_mg


    (gdb) f 6
    #6  0x00007fffd29a8b16 in U4Recorder::PreUserTrackingAction_Optical (this=0xb29cb0, track=0x7fff0ba6a880)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:298
    298	            sev->beginPhoton(ulabel);  // THIS ZEROS THE SLOT 
    (gdb) f 5
    #5  0x00007fffcf24aff4 in SEvt::beginPhoton (this=0xb53000, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1418
    1418	    if(!hostside_running_resize_done) hostside_running_resize(); 
    (gdb) f 4
    #4  0x00007fffcf24a76d in SEvt::hostside_running_resize (this=0xb53000) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1239
    1239	    assert( is_self_provider ); 
    (gdb) p is_self_provider
    $1 = false
    (gdb) 


::

    1229 void SEvt::hostside_running_resize()
    1230 {
    1231     bool is_self_provider = isSelfProvider() ;
    1232     LOG_IF(fatal, is_self_provider == false ) << " NOT-is_self_provider " << descProvider() ;
    1233     LOG(LEVEL)
    1234         << " is_self_provider " << is_self_provider
    1235         << " hostside_running_resize_done " << hostside_running_resize_done
    1236         ;
    1237 
    1238     assert( hostside_running_resize_done == false );
    1239     assert( is_self_provider );
    1240 
    1241     hostside_running_resize_done = true ;
    1242     hostside_running_resize_();
    1243 

    0666 /**
     667 SEvt::setCompProvider
     668 ----------------------
     669 
     670 This is called for device side running only from QEvent::init
     671 
     672 **/
     673 
     674 void SEvt::setCompProvider(const SCompProvider* provider_)
     675 {
     676     provider = provider_ ;
     677     LOG(fatal) << descProvider() ;
     678 }
     679 
     680 bool SEvt::isSelfProvider() const {   return provider == this ; }
     681 




