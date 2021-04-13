tds-mu-not-enough-rng
========================


::

    Begin of Event --> 0
    2021-04-12 03:55:30.019 INFO  [325852] [PMTEfficiencyCheck::addHitRecord@72]  m_eventID 0 m_record_count 1000000 m_record_limit 1000000 (change limit with envvar : PMTEfficiencyCheck_record_limit)  record_count reached record_limit  invoke SaveRecords 
    ../src/PMTEfficiencyCheck.cc +256 SaveRecords  eventID 0 m_eventID 0 m_record_limit 1000000 m_record_count 1000000 m_record_saved 0  PROCEED 
    ../src/PMTEfficiencyCheck.cc +270 SaveRecords  eventID 0 m_uvolname.size 4 all volnames hit : 
    NNVTMCPPMT_PMT_20inch_body_phys
    HamamatsuR12860_PMT_20inch_body_phys
    PMT_3inch_body_phys
    HamamatsuR12860_PMT_20inch_inner1_phys
    ../src/PMTEfficiencyCheck.cc +288 SaveRecords  eventID 0 m_eventID 0 m_hitrecords.size 16000000 record_count 1000000 items 1000000 parcat_mismatch_count 189904 simcat_mismatch_count 189904
    ../src/PMTEfficiencyCheck.cc +304 record_count 1000000 save to $TMP/PMTEfficiencyCheck/ASIS/0.npy shape 1000000,4,4
    ../src/PMTEfficiencyCheck.cc +312 record_count 1000000 save to $TMP/PMTEfficiencyCheck/ASIS/0.txt names 16
    2021-04-12 03:55:30.326 INFO  [325852] [SStr::Save@54] SPath::Resolve $TMP/PMTEfficiencyCheck/ASIS/0.txt to /tmp/blyth/opticks/PMTEfficiencyCheck/ASIS/0.txt
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [7608599]@[pLPMT_NNVT_MCPPMT] (-8104.66, 17659.2, 431.641, 197.54)  step number >= 1000
     decay 2 gammas 0.510999
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [9857018]@[HamamatsuR12860pMask] (-11632.7, 3017.22, 15548.2, 201.457)  step number >= 1000
    2021-04-12 04:00:10.589 INFO  [325852] [PMTEfficiencyCheck::addHitRecord@72]  m_eventID 0 m_record_count 1000000 m_record_limit 1000000 (change limit with envvar : PMTEfficiencyCheck_record_limit)  record_count reached record_limit  invoke SaveRecords 
    ../src/PMTEfficiencyCheck.cc +256 SaveRecords  eventID 0 m_eventID 0 m_record_limit 1000000 m_record_count 1000000 m_record_saved 1  SKIP AS RECORD SAVED ALREADY 
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [17309963]@[HamamatsuR12860pMask] (10247.9, -4298.49, -15911.9, 257.655)  step number >= 1000
     decay 2 gammas 0.510999
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [30382362]@[NNVTMCPPMTpMask] (3998.49, -4923.74, -18667.6, 141.809)  step number >= 1000
     decay 2 gammas 0.510999
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [52587204]@[pLPMT_Hamamatsu_R12860] (6803.67, -11485.5, 14272.3, 245.348)  step number >= 1000
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [55588702]@[HamamatsuR12860_PMT_20inch_body_phys] (15546.5, 5077.33, -10925.1, 130.509)  step number >= 1000
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [57781380]@[NNVTMCPPMTpMask] (4044.96, -5025.1, -18758.2, 136.472)  step number >= 1000
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [69209227]@[pLPMT_NNVT_MCPPMT] (-36.2257, 3266.11, -19429.9, 151.963)  step number >= 1000
    junotoptask:NormalAnaMgr.UserSteppingAction  WARN: opticalphoton [72606283]@[pLPMT_NNVT_MCPPMT] (3025.55, -19217.2, -1387.83, 224.669)  step number >= 1000
    [[ junoSD_PMT_v2_Opticks::EndOfEvent  eventID 0 m_opticksMode 1 numGensteps 109988 numPhotons 51369695
    2021-04-12 05:00:51.813 INFO  [325852] [OpticksRun::createEvent@115]  tagoffset 0 skipaheadstep 0 skipahead 0
    2021-04-12 05:00:51.874 FATAL [325852] [OpticksEvent::resize@1258] NOT ENOUGH RNG : USE OPTION --rngmax 3/10/100  num_photons 51369695 rng_max 3000000
    python: /home/blyth/opticks/optickscore/OpticksEvent.cc:1263: void OpticksEvent::resize(): Assertion `enoughRng && " need to prepare and persist more RNG states up to maximual per propagation number"' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) Connection to 127.0.0.1 closed by remote host.
    Connection to 127.0.0.1 closed.
    "ssh P" gives connection refused if ssh tunnel "tun" is not running
    epsilon:~ blyth$ 
    epsilon:~ blyth$ 

