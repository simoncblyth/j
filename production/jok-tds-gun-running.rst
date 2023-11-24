jok-tds-gun-running
======================

::

    N> GUN=1 ~/j/okjob.sh  


    //qcerenkov::wavelength_sampled_bndtex idx   3163 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 159.878 count 100 
    //qcerenkov::wavelength_sampled_bndtex idx   3164 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 532.943 count 100 
    //qcerenkov::wavelength_sampled_bndtex idx   3165 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 214.234 count 100 
    //qcerenkov::wavelength_sampled_bndtex idx   3166 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 285.599 count 100 
    //qcerenkov::wavelength_sampled_bndtex idx   3167 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 281.132 count 100 
    2023-11-24 11:01:17.064 INFO  [327459] [SEvt::save@3501]  dir /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/jok-tds/ALL0/p002 index 2 instance 0 OPTICKS_SAVE_COMP  genstep,photon,record,seq,prd,hit,domain,inphoton,tag,flat,aux,sup
    junoSD_PMT_v2::EndOfEvent eventID 1 opticksMode 3 hitCollection 1595 hcMuon 0 hcOpticks 1726 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    2023-11-24 11:01:17.111 INFO  [327459] [U4Recorder::MakeMetaArray@676] U4Recorder::DescFakes  
    U4Recorder::FAKES_SKIP NO 
    U4Recorder::FAKES      YES
    FAKES.size             0

    NPFold::add_ FATAL : have_key_already [hit.npy]
    NPFold::descKeys kk.size 8 [hit.npy]  [U4R.npy]  [SEventConfig.npy]  [genstep.npy]  [photon.npy]  [record.npy]  [seq.npy]  [prd.npy] python: /home/blyth/junotop/opticks/sysrap/NPFold.h:858: void NPFold::add_(const char*, const NP*): Assertion `!have_key_already' failed.
     *** Break *** abort



    #7  0x00007f92d23d7387 in raise () from /lib64/libc.so.6
    #8  0x00007f92d23d8a78 in abort () from /lib64/libc.so.6
    #9  0x00007f92d23d01a6 in __assert_fail_base () from /lib64/libc.so.6
    #10 0x00007f92d23d0252 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f92a36dcf2e in NPFold::add_ (this=0x7299c40, k=0x7fff9691b8c0 "hit.npy", a=0xd5253b20) at /home/blyth/junotop/opticks/sysrap/NPFold.h:858
    #12 0x00007f92a36dcd6a in NPFold::add (this=0x7299c40, k=0x7f92a3821029 "hit", a=0xd5253b20) at /home/blyth/junotop/opticks/sysrap/NPFold.h:838
    #13 0x00007f92a371f114 in SEvt::gather_components (this=0x72993a0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3081
    #14 0x00007f92a371f854 in SEvt::gather (this=0x72993a0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3134
    #15 0x00007f92a3720de6 in SEvt::save (this=0x72993a0, dir_=0x7f92a381cefa "$DefaultOutputDir") at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3488
    #16 0x00007f92a371f952 in SEvt::save (this=0x72993a0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:3215
    #17 0x00007f92a3716878 in SEvt::endOfEvent (this=0x72993a0, eventID=1) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1351
    #18 0x00007f92a44e0aa4 in U4Recorder::EndOfEventAction (this=0x7270620, event=0xc8d5d530) at /home/blyth/junotop/opticks/u4/U4Recorder.cc:311
    #19 0x00007f92a3481e94 in U4RecorderAnaMgr::EndOfEventAction (this=0x72990b0, evt=0xc8d5d530) at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:32



SEvt__LIFECYLE debug
----------------------

::

    U4::Collect uses SEvt::AddGenstep collecting into both ECPU and EGPU 


