FIXED : jok-tds-B-side-missing-hits-array-despite-having-hits
==================================================================

Fixed this, was due to the multi-launch impl on A side changing SEvt NPFold handling 
to use topfold and fold. 


Chi2 match is ok so photons with hitmask flags are there : but missing the selection to create the array
----------------------------------------------------------------------------------------------------------

::

    QCF qcf :  
    a.q 10000 b.q 10000 lim slice(None, None, None) 
    c2sum :    38.2620 c2n :    32.0000 c2per:     1.1957  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  38.26/32:1.196 (30) pv[1.000,> 0.05 : null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '  3227   3341' ' 1.9787' '     0      2']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '  2882   2770' ' 2.2194' '     2      0']
     [' 2' 'TO BT BT BT BT BT SR SA                                                                        ' ' 2' '   659    618' ' 1.3164' '  1063   1135']
     [' 3' 'TO BT BT BT BT BT SA                                                                           ' ' 3' '   451    484' ' 1.1647' '   898    912']
     [' 4' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' ' 4' '   131    135' ' 0.0602' '  2182   2184']
     [' 5' 'TO BT BT BT BT BR BT BT BT BT BT BT AB                                                         ' ' 5' '    86    120' ' 5.6117' '  1624   1616']


::

    P[blyth@localhost ALL0_Debug_Philox_GUN0]$ l A000/
    total 21884
        4 drwxr-xr-x. 2 blyth blyth     4096 Jan  9 11:02 .
        4 -rw-rw-r--. 1 blyth blyth      256 Jan  9 11:02 domain.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  9 11:02 inphoton.npy
        4 -rw-rw-r--. 1 blyth blyth      102 Jan  9 11:02 NPFold_index.txt
        4 -rw-rw-r--. 1 blyth blyth      670 Jan  9 11:02 NPFold_meta.txt
        0 -rw-rw-r--. 1 blyth blyth        0 Jan  9 11:02 NPFold_names.txt
       40 -rw-rw-r--. 1 blyth blyth    40128 Jan  9 11:02 seqnib.npy
        4 -rw-rw-r--. 1 blyth blyth      260 Jan  9 11:02 seqnib_table.npy
        4 -rw-rw-r--. 1 blyth blyth      143 Jan  9 11:02 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Jan  9 11:02 sframe.npy
      232 -rw-rw-r--. 1 blyth blyth   236544 Jan  9 11:02 hit.npy
        4 -rw-rw-r--. 1 blyth blyth       36 Jan  9 11:02 record_meta.txt
      316 -rw-rw-r--. 1 blyth blyth   320128 Jan  9 11:02 seq.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  9 11:02 photon.npy
    20004 -rw-rw-r--. 1 blyth blyth 20480144 Jan  9 11:02 record.npy
        0 drwxrwxr-x. 4 blyth blyth      115 Jan  9 11:02 ..
        4 -rw-rw-r--. 1 blyth blyth      224 Jan  9 11:02 genstep.npy

    P[blyth@localhost ALL0_Debug_Philox_GUN0]$ l B000/
    total 21652
        0 drwxrwxr-x. 4 blyth blyth      115 Jan  9 11:02 ..
        4 drwxr-xr-x. 2 blyth blyth     4096 Jan  9 11:02 .
        4 -rw-rw-r--. 1 blyth blyth      256 Jan  9 11:02 domain.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  9 11:02 inphoton.npy
        4 -rw-rw-r--. 1 blyth blyth       94 Jan  9 11:02 NPFold_index.txt
        4 -rw-rw-r--. 1 blyth blyth     1826 Jan  9 11:02 NPFold_meta.txt
        0 -rw-rw-r--. 1 blyth blyth        0 Jan  9 11:02 NPFold_names.txt
       40 -rw-rw-r--. 1 blyth blyth    40128 Jan  9 11:02 seqnib.npy
        4 -rw-rw-r--. 1 blyth blyth      260 Jan  9 11:02 seqnib_table.npy
        4 -rw-rw-r--. 1 blyth blyth      143 Jan  9 11:02 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Jan  9 11:02 sframe.npy
        4 -rw-rw-r--. 1 blyth blyth       36 Jan  9 11:02 record_meta.txt
      316 -rw-rw-r--. 1 blyth blyth   320128 Jan  9 11:02 seq.npy
        4 -rw-rw-r--. 1 blyth blyth      224 Jan  9 11:02 genstep.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  9 11:02 photon.npy
    20004 -rw-rw-r--. 1 blyth blyth 20480144 Jan  9 11:02 record.npy
    P[blyth@localhost ALL0_Debug_Philox_GUN0]$ 
    P[blyth@localhost ALL0_Debug_Philox_GUN0]$ 


On the A side QEvent::gatherHit does this
---------------------------------------------

::

     836 NP* QEvent::gatherHit_() const
     837 {
     838     LOG_IF(info, LIFECYCLE) ;
     839     evt->hit = QU::device_alloc<sphoton>( evt->num_hit, "QEvent::gatherHit_:sphoton" );
     840 
     841     SU::copy_if_device_to_device_presized_sphoton( evt->hit, evt->photon, evt->num_photon,  *selector );
     842 
     843     NP* hit = NP::Make<float>( evt->num_hit, 4, 4 );   
     844 
     845     QU::copy_device_to_host<sphoton>( (sphoton*)hit->bytes(), evt->hit, evt->num_hit );
     846 
     847     QU::device_free<sphoton>( evt->hit );
     848 
     849     evt->hit = nullptr ;
     850     LOG(LEVEL) << " hit.sstr " << hit->sstr() ;
     851 
     852     return hit ;
     853 }


B side
----------

::

    3172 /**
    3173 SEvt::gatherHit
    3174 -------------------------------------------
    3175 
    3176 Does CPU side equivalent of QEvent::gatherHit_ 
    3177 using the photon array and the sphoton_selector 
    3178 
    3179 HMM: notice that this relies on having gathered 
    3180 the photon array, and there being an entry in the fold.
    3181 So cannot have HitOnly on B side ? 
    3182 
    3183 This means that hit must come after photon in the component order 
    3184 
    3185 **/
    3186 
    3187 NP* SEvt::gatherHit() const
    3188 {
    3189     const NP* p = getPhoton();
    3190     NP* h = p ? p->copy_if<float, sphoton>(*selector) : nullptr ;
    3191     return h ;
    3192 }


::

    const NP* SEvt::getPhoton() const {  return topfold->get(SComp::PHOTON_) ; }


Try simply getting the photons from the fold::

    3187 NP* SEvt::gatherHit() const
    3188 {
    3189     const NP* p = fold->get(SComp::PHOTON_) ;  
    3190     // cannot use getPhoton here as that is coming from topfold which is only populated after gather 
    3191     NP* h = p ? p->copy_if<float, sphoton>(*selector) : nullptr ;
    3192     return h ;  
    3193 }   



