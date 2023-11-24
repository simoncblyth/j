jok-tds-gun-running
======================

::

    N> GUN=1 ~/j/okjob.sh  


    /qcerenkov::wavelength_sampled_bndtex idx   3162 sampledRI   0.000 cosTheta     inf sin2Theta   0.000 wavelength 214.188 count 100 
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



