ab-shakedown
=============

Related
---------

* ~/opticks/notes/issues/analysis_shakedown.rst


tds3gun.sh get : fails to grab as non-existing P:/tmp/blyth/opticks/tds3gun/evt/g4live/natural
-------------------------------------------------------------------------------------------------

::

    epsilon:opticks blyth$ tds3gun.sh get 
    PFX=tds3gun evtsync.sh
    evtsync from P:/tmp/blyth/opticks/tds3gun/evt/g4live/natural to /tmp/blyth/opticks/tds3gun/evt/g4live/natural
    receiving incremental file list
    rsync: change_dir "/tmp/blyth/opticks/tds3gun/evt/g4live/natural" failed: No such file or directory (2)

    sent 68 bytes  received 117 bytes  24.67 bytes/sec
    total size is 0  speedup is 0.00
    rsync error: some files/attrs were not transferred (see previous errors) (code 23) at main.c(1679) [Receiver=3.1.3]
    rsync: [Receiver] write error: Broken pipe (32)
    === evtsync : non-zero rc from rsync : start ssh tunnel with "tun" and ensure remote directory being grabbed exists
    epsilon:opticks blyth$ 


Only recent event dir from tds3 running is /tmp/blyth/opticks/evt/g4live/natural/1/ containing gensteps only
-------------------------------------------------------------------------------------------------------------

::

    N[blyth@localhost ~]$ l /tmp/blyth/opticks/evt/g4live/natural/1/
    total 16
     4 -rw-rw-r--. 1 blyth blyth    50 Dec 27 03:34 gs.json
    12 -rw-rw-r--. 1 blyth blyth 11600 Dec 27 03:34 gs.npy
     0 drwxrwxr-x. 4 blyth blyth    24 Dec 10 23:08 ..
     0 drwxrwxr-x. 2 blyth blyth    35 Dec 10 23:08 .
    N[blyth@localhost ~]$ date
    Mon Dec 27 18:19:39 CST 2021
    N[blyth@localhost ~]$ 


what does tds3gun do that tds3 does not ? what controls event writing and locations ?
--------------------------------------------------------------------------------------

Very little, just defines OPTICKS_EVENT_PFX and G4OpticksAnaMgr_outdir::

    2391 tds3gun(){
    2392    : unsets ctrl evars that may be defined from other funcs
    2393    export OPTICKS_EVENT_PFX=tds3gun
    2394    unset INPUT_PHOTON_PATH
    2395 
    2396    local outdir="/tmp/G4OpticksAnaMgr"
    2397    mkdir -p $outdir
    2398    export G4OpticksAnaMgr_outdir=$outdir
    2399 
    2400    tds3
    2401 }


OPTICKS_EVENT_PFX
---------------------

::

    epsilon:opticks blyth$ opticks-f OPTICKS_EVENT_PFX
    ./optickscore/OpticksCfg.cc:The envvars OPTICKS_EVENT_PFX and TESTNAME are checked in order, the first that
    ./optickscore/OpticksCfg.cc:    const char* pfx_envvar_default = SSys::getenvvar("OPTICKS_EVENT_PFX,TESTNAME" , NULL ); 
    epsilon:opticks blyth$ 


    1687 /**
    1688 OpticksCfg::getEventPfx
    1689 -------------------------
    1690 
    1691 Canonically used from Opticks::defineEventSpec to create Opticks::m_spec and m_nspec
    1692 that are the blueprints for all OpticksEvent.
    1693 
    1694 The envvars OPTICKS_EVENT_PFX and TESTNAME are checked in order, the first that
    1695 is found to be set defines the default pfx.  
    1696 This default is overridden by the commandline --pfx argument.
    1697 
    1698 **/
    1699 
    1700 template <class Listener>
    1701 const char* OpticksCfg<Listener>::getEventPfx() const
    1702 {
    1703     const char* pfx_envvar_default = SSys::getenvvar("OPTICKS_EVENT_PFX,TESTNAME" , NULL );
    1704     return m_event_pfx.empty() ? pfx_envvar_default : m_event_pfx.c_str() ;
    1705 }



    epsilon:opticks blyth$ opticks-f getEventPfx
    ./optickscore/OpticksAna.cc:         << "--pfx " << m_ok->getEventPfx() << " "
    ./optickscore/Opticks.hh:       const char*          getEventPfx() const ;
    ./optickscore/OpticksCfg.cc:OpticksCfg::getEventPfx
    ./optickscore/OpticksCfg.cc:const char* OpticksCfg<Listener>::getEventPfx() const 
    ./optickscore/OpticksCfg.hh:     const char* getEventPfx() const ;
    ./optickscore/Opticks.cc:    const char* resource_pfx = m_rsc->getEventPfx() ; 
    ./optickscore/Opticks.cc:    const char* config_pfx = m_cfg->getEventPfx() ; 
    ./optickscore/Opticks.cc:const char* Opticks::getEventPfx() const
    ./optickscore/Opticks.cc:    const char* pfx = getEventPfx();
    ./optickscore/Opticks.cc:    const char* pfx = getEventPfx();
    ./optickscore/Opticks.cc:    const char* pfx = getEventPfx();
    ./boostrap/BOpticksResource.hh:        const char* getEventPfx() const ; 
    ./boostrap/BOpticksResource.cc:const char* BOpticksResource::getEventPfx() const {  return m_evtpfx ; } 
    epsilon:opticks blyth$ 



    3046 void Opticks::defineEventSpec()
    3047 {
    3048     const char* cat = m_cfg->getEventCat(); // expected to be defined for tests and equal to the TESTNAME from bash functions like tboolean-
    3049     const char* udet = getInputUDet();
    3050     const char* tag = m_cfg->getEventTag();
    3051     const char* ntag = BStr::negate(tag) ;
    3052     const char* typ = getSourceType();
    3053 
    3054     const char* resource_pfx = m_rsc->getEventPfx() ;
    3055     const char* config_pfx = m_cfg->getEventPfx() ;
    3056     const char* pfx = config_pfx ? config_pfx : resource_pfx ;
    3057     if( !pfx )
    3058     {
    3059         pfx = DEFAULT_PFX ;
    3060         LOG(fatal)
    3061             << " resource_pfx " << resource_pfx
    3062             << " config_pfx " << config_pfx
    3063             << " pfx " << pfx
    3064             << " cat " << cat
    3065             << " udet " << udet
    3066             << " typ " << typ
    3067             << " tag " << tag
    3068             ;
    3069     }
    3070     //assert( pfx ); 
    3071 
    3072 
    3073     m_spec  = new OpticksEventSpec(pfx, typ,  tag, udet, cat );
    3074     m_nspec = new OpticksEventSpec(pfx, typ, ntag, udet, cat );
    3075 
    3076     LOG(LEVEL)
    3077          << " pfx " << pfx
    3078          << " typ " << typ
    3079          << " tag " << tag
    3080          << " ntag " << ntag
    3081          << " udet " << udet
    3082          << " cat " << cat
    3083          ;
    3084 
    3085 }


Logging from tds3gun.sh::

    0
        19 gp.x    3550.77 gp.y   -3828.58 gp.z   18657.51 gp.R   19374.43 pmt  314239          SI|SD|BT|EX otk     10 oti    3.61 bti    94.42 bp.x    3253.14 bp.y   -3530.91 bp.z   17161.07 bp.R   17820.00
    2021-12-27 18:33:56.404 INFO  [13051] [junoSD_PMT_v2_Opticks::EndOfEvent@180] ] num_hit 4887 merged_count  0 m_merged_total 0 m_opticksMode 3
    2021-12-27 18:33:56.404 INFO  [13051] [junoSD_PMT_v2_Opticks::TerminateEvent@227]  NOT invoking G4Opticks::reset as G4OpticksRecorder detected, should do reset in G4OpticksRecorder::TerminateEvent
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 6385 hitCollection_muon 0 hitCollection_opticks 0
    2021-12-27 18:33:56.404 INFO  [13051] [OpticksEvent::save@1972] /tmp/blyth/opticks/tds3gun/evt/g4live/natural/-2
    2021-12-27 18:33:56.427 FATAL [13051] [G4Opticks::reset@544]  m_way_enabled reset m_hiys 
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-12-27 18:33:56.428 INFO  [13051] [G4Opticks::Finalize@290] G4Opticks.desc ok 0x82ea240 opmgr 0x2c5989c0 


Now the events are being saved, what did tds3gun do that tds3 did not to switch that on ?::

    N[blyth@localhost ~]$ cd /tmp/blyth/opticks/tds3gun/evt/g4live/natural/-2
    N[blyth@localhost -2]$ l
    total 10012
       4 drwxrwxr-x. 3 blyth blyth    4096 Dec 27 18:33 .
       4 drwxrwxr-x. 2 blyth blyth    4096 Dec 27 18:33 20211227_183355
       4 -rw-rw-r--. 1 blyth blyth     144 Dec 27 18:33 OpticksProfileAccLabels.npy
       4 -rw-rw-r--. 1 blyth blyth      96 Dec 27 18:33 OpticksProfileAcc.npy
       4 -rw-rw-r--. 1 blyth blyth     144 Dec 27 18:33 OpticksProfileLisLabels.npy
       4 -rw-rw-r--. 1 blyth blyth      88 Dec 27 18:33 OpticksProfileLis.npy
       4 -rw-rw-r--. 1 blyth blyth    2068 Dec 27 18:33 report.txt
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 DeltaTime.ini
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 DeltaVM.ini
       4 -rw-rw-r--. 1 blyth blyth      96 Dec 27 18:33 idom.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 OpticksProfileLabels.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 OpticksProfile.npy
       4 -rw-rw-r--. 1 blyth blyth    1772 Dec 27 18:33 parameters.json
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 Time.ini
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 VM.ini
       4 -rw-rw-r--. 1 blyth blyth     128 Dec 27 18:33 fdom.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 bn.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 dg.npy
     184 -rw-rw-r--. 1 blyth blyth  184928 Dec 27 18:33 ph.npy
    7224 -rw-rw-r--. 1 blyth blyth 7394016 Dec 27 18:33 dx.npy
    1808 -rw-rw-r--. 1 blyth blyth 1848576 Dec 27 18:33 rx.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 ht.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 hy.npy
     724 -rw-rw-r--. 1 blyth blyth  739472 Dec 27 18:33 ox.npy
       0 drwxrwxr-x. 7 blyth blyth      53 Dec 27 18:33 ..
       4 -rw-rw-r--. 1 blyth blyth      28 Dec 27 18:33 so.json
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 so.npy
    N[blyth@localhost -2]$ cd /tmp/blyth/opticks/tds3gun/evt/g4live/natural/2
    N[blyth@localhost 2]$ l
    total 4320
       0 drwxrwxr-x. 7 blyth blyth      53 Dec 27 18:33 ..
       4 drwxrwxr-x. 2 blyth blyth    4096 Dec 27 18:33 20211227_183355
       4 drwxrwxr-x. 3 blyth blyth    4096 Dec 27 18:33 .
       4 -rw-rw-r--. 1 blyth blyth     144 Dec 27 18:33 OpticksProfileAccLabels.npy
       4 -rw-rw-r--. 1 blyth blyth      96 Dec 27 18:33 OpticksProfileAcc.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 OpticksProfileLabels.npy
       4 -rw-rw-r--. 1 blyth blyth     144 Dec 27 18:33 OpticksProfileLisLabels.npy
       4 -rw-rw-r--. 1 blyth blyth      88 Dec 27 18:33 OpticksProfileLis.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 OpticksProfile.npy
       4 -rw-rw-r--. 1 blyth blyth    2022 Dec 27 18:33 report.txt
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 DeltaTime.ini
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 DeltaVM.ini
       4 -rw-rw-r--. 1 blyth blyth      96 Dec 27 18:33 idom.npy
       4 -rw-rw-r--. 1 blyth blyth    1748 Dec 27 18:33 parameters.json
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 Time.ini
       0 -rw-rw-r--. 1 blyth blyth       0 Dec 27 18:33 VM.ini
       4 -rw-rw-r--. 1 blyth blyth     128 Dec 27 18:33 fdom.npy
       4 -rw-rw-r--. 1 blyth blyth     692 Dec 27 18:33 Boundary_IndexLocal.json
       4 -rw-rw-r--. 1 blyth blyth     696 Dec 27 18:33 Boundary_IndexSource.json
       4 -rw-rw-r--. 1 blyth blyth     636 Dec 27 18:33 History_SequenceLocal.json
       4 -rw-rw-r--. 1 blyth blyth     649 Dec 27 18:33 Material_SequenceLocal.json
       4 -rw-rw-r--. 1 blyth blyth     674 Dec 27 18:33 Material_SequenceSource.json
       4 -rw-rw-r--. 1 blyth blyth     663 Dec 27 18:33 History_SequenceSource.json
      48 -rw-rw-r--. 1 blyth blyth   46292 Dec 27 18:33 ps.npy
     452 -rw-rw-r--. 1 blyth blyth  462216 Dec 27 18:33 rs.npy
     184 -rw-rw-r--. 1 blyth blyth  184928 Dec 27 18:33 bn.npy
       4 -rw-rw-r--. 1 blyth blyth      80 Dec 27 18:33 dg.npy
       4 -rw-rw-r--. 1 blyth blyth      96 Dec 27 18:33 dx.npy
     184 -rw-rw-r--. 1 blyth blyth  184928 Dec 27 18:33 ph.npy
     364 -rw-rw-r--. 1 blyth blyth  369776 Dec 27 18:33 wy.npy
    1808 -rw-rw-r--. 1 blyth blyth 1848576 Dec 27 18:33 rx.npy
      12 -rw-rw-r--. 1 blyth blyth   11024 Dec 27 18:33 gs.npy
     308 -rw-rw-r--. 1 blyth blyth  312848 Dec 27 18:33 ht.npy
     156 -rw-rw-r--. 1 blyth blyth  156464 Dec 27 18:33 hy.npy
     724 -rw-rw-r--. 1 blyth blyth  739472 Dec 27 18:33 ox.npy
    N[blyth@localhost 2]$ 



Now "tds3gun.sh get" succeeds to grab
----------------------------------------

::

    epsilon:optickscore blyth$ tds3gun.sh get
    PFX=tds3gun evtsync.sh
    evtsync from P:/tmp/blyth/opticks/tds3gun/evt/g4live/natural to /tmp/blyth/opticks/tds3gun/evt/g4live/natural
    receiving incremental file list
    ./
    -1/
    -1/DeltaTime.ini
                  0 100%    0.00kB/s    0:00:00 (xfr#1, to-chk=164/171)
    -1/DeltaVM.ini
                  0 100%    0.00kB/s    0:00:00 (xfr#2, to-chk=163/171)



And "tds3gun.sh 1" succeeds to compare
------------------------------------------
 

::

    #ab.ahis
    ab.ahis
    .    all_seqhis_ana  cfo:sum  1:g4live:tds3gun   -1:g4live:tds3gun 
    .             TOTALS:    11300    11300                  8372.99     8372.99/68 = 123.13   pvalue:P[C2>]:1.000  1-pvalue:P[C2<]:0.000 
       n             iseq        a        b      a-b     (a-b)^2/(a+b)        a/b                  b/a          [ns]   label
    0000               42     1727     1683       44            0.57        1.026 +- 0.025       0.975 +- 0.024 [2 ]   SI AB
    0001         7cccccc2       73     1795     -1722         1587.41        0.041 +- 0.005      24.589 +- 0.580 [8 ]   SI BT BT BT BT BT BT SD
    0002          7ccccc2     1836        1     1835         1833.00     1836.000 +- 42.849       0.001 +- 0.001 [7 ]   SI BT BT BT BT BT SD
    0003              452      515      505       10            0.10        1.020 +- 0.045       0.981 +- 0.044 [3 ]   SI RE AB
    0004         7ccccc62      809        1      808          806.00      809.000 +- 28.443       0.001 +- 0.001 [8 ]   SI SC BT BT BT BT BT SD
    0005        7cccccc62       48      713     -665          581.11        0.067 +- 0.010      14.854 +- 0.556 [9 ]   SI SC BT BT BT BT BT BT SD
    0006              462      379      377        2            0.01        1.005 +- 0.052       0.995 +- 0.051 [3 ]   SI SC AB
    0007        7cccccc52       23      518     -495          452.91        0.044 +- 0.009      22.522 +- 0.990 [9 ]   SI RE BT BT BT BT BT BT SD
    0008         7ccccc52      531        0      531          531.00        0.000 +- 0.000       0.000 +- 0.000 [8 ]   SI RE BT BT BT BT BT SD
    0009               41      256      262       -6            0.07        0.977 +- 0.061       1.023 +- 0.063 [2 ]   CK AB
    0010             4552      173      162       11            0.36        1.068 +- 0.081       0.936 +- 0.074 [4 ]   SI RE RE AB
    0011             8cc2      134      173      -39            4.95        0.775 +- 0.067       1.291 +- 0.098 [4 ]   SI BT BT SA
    0012        7ccccc662      267        0      267          267.00        0.000 +- 0.000       0.000 +- 0.000 [9 ]   SI SC SC BT BT BT BT BT SD
    0013       7cccccc662       15      249     -234          207.41        0.060 +- 0.016      16.600 +- 1.052 [10]   SI SC SC BT BT BT BT BT BT SD
    0014       7cccccc652       14      230     -216          191.21        0.061 +- 0.016      16.429 +- 1.083 [10]   SI RE SC BT BT BT BT BT BT SD
    0015             4652      119      120       -1            0.00        0.992 +- 0.091       1.008 +- 0.092 [4 ]   SI RE SC AB
    0016        7ccccc652      235        0      235          235.00        0.000 +- 0.000       0.000 +- 0.000 [9 ]   SI RE SC BT BT BT BT BT SD
    0017             4662      100      110      -10            0.48        0.909 +- 0.091       1.100 +- 0.105 [4 ]   SI SC SC AB
    0018             4cc2      109       87       22            2.47        1.253 +- 0.120       0.798 +- 0.086 [4 ]   SI BT BT AB
    .             TOTALS:    11300    11300                  8372.99     8372.99/68 = 123.13   pvalue:P[C2>]:1.000  1-pvalue:P[C2<]:0.000 




Clear difference in the number of BT before SD::

    G4 b : SI 6*BT SD 
    OK a : SI 5*BT SD
    .                            a        b
    0001         7cccccc2       73     1795     -1722         1587.41        0.041 +- 0.005      24.589 +- 0.580 [8 ]   SI BT BT BT BT BT BT SD
    0002          7ccccc2     1836        1     1835         1833.00     1836.000 +- 42.849       0.001 +- 0.001 [7 ]   SI BT BT BT BT BT SD


* I have fixed something like this before  : on that occasion it was the degenerate PMT surface causing microsteps that have to be skipped
  from G4 to align the bookkeeping  


Comparing with the histories from Jul, see that there are matched "SI 3*BT SD" so the issue is arising 
with the additional surfaces from the mask

* OR could be intersects onto the virtual hatboxes that are skipped from the GPU geometry 
  (that skipping is for pretty visuals cosmetics 

* TODO: set up some planar input photons so can visualize the photons 
  together with the geometry in my 2D cxs cross section scatter plots  



hatbox skipping of virtuals is for the cosmetics of the renders so when ab comparing need to not skip them
------------------------------------------------------------------------------------------------------------------

::

    2445 tds-skipsolidname(){ echo $(tds-skipsolidname-) | tr " " "," ; }
    2446 tds-skipsolidname-(){ cat << EON | grep -v ^#
    2447 
    2448 NNVTMCPPMTsMask_virtual
    2449 HamamatsuR12860sMask_virtual
    2450 mask_PMT_20inch_vetosMask_virtual
    2451 
    2452 NNVTMCPPMT_PMT_20inch_body_solid_1_2
    2453 HamamatsuR12860_PMT_20inch_body_solid_1_4
    2454 PMT_20inch_veto_body_solid_1_2
    2455 
    2456 EON
    2457 }
    2458 



Matched histories from Jul 2021 (without mask)
-------------------------------------------------

* http://localhost/env/presentation/juno_opticks_20210712.html


::

    .. raw:: html 

        <pre class="mypretiny">
        epsilon:ana blyth$ tds3gun.sh 1    ## <b>seqhis: 64bit uint : 16x4bit step flags for each photon</b>
        In [1]: ab.his[:20]   ##  OK:1    G4:-1     OK-G4   "c2" deviation     

        .  n           seqhis        a        b      a-b     (a-b)^2/(a+b)   label                ## optickscore/OpticksPhoton.h enum 
                  ## hexstring
        0000               42     1822     1721      101            2.88     SI AB                ## <b>AB : BULK_ABSORB </b> 
        0001            7ccc2     1446     1406       40            0.56     SI BT BT BT SD       ## <b>SD : SURFACE_DETECT </b> 
        0002           7ccc62      672      666        6            0.03     SI SC BT BT BT SD    ## <b>SC : BULK_SCATTER </b> 
        0003            8ccc2      649      597       52            2.17     SI BT BT BT SA       ## <b>BT : BOUNDARY_TRANSMIT </b> 
        0004             8cc2      606      615       -9            0.07     SI BT BT SA          ## <b>SI : SCINTILLATION </b> 
        0005              452      538      536        2            0.00     SI RE AB             ## <b>RE : BULK_REEMIT </b> 
        0006           7ccc52      433      438       -5            0.03     SI RE BT BT BT SD    
        0007              462      397      405       -8            0.08     SI SC AB
        0008           8ccc62      269      262        7            0.09     SI SC BT BT BT SA
        0009          7ccc662      242      222       20            0.86     SI SC SC BT BT BT SD
        0010            8cc62      217      212        5            0.06     SI SC BT BT SA
        0011          7ccc652      211      205        6            0.09     SI RE SC BT BT BT SD
        0012           8ccc52      200      201       -1            0.00     SI RE BT BT BT SA
        0013            8cc52      158      192      -34            3.30     SI RE BT BT SA
        0014             4552      181      165       16            0.74     SI RE RE AB
        0015               41      164      145       19            1.17     CK AB                ## <b>CK : CERENKOV</b> 
        0016          7ccc552      135      160      -25            2.12     SI RE RE BT BT BT SD
        0017             4cc2      130      115       15            0.92     SI BT BT AB
        0018             4652      120      117        3            0.04     SI RE SC AB

        .             TOTALS:    11684    11684                    52.92     52.92/63 =  0.84   pvalue:P[C2>]:0.814  1-pvalue:P[C2<]:0.186 





