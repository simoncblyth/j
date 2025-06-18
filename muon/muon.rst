muon
======


Capture igs of crashing muon in QSim::simulate::

    junoSD_PMT_v2::EndOfEvent eventID 5 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-06-12 08:01:25.300322000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  WARN: No Hit produced
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-06-12 08:01:25.300523000Z
    end of event action 
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (6) 
    junoSD_PMT_v2::Initialize eventID 6
    Begin of Event --> 6
    2025-06-12 16:01:29.084 INFO  [3957937] [QSim::MaybeSaveIGS@540]  eventID 6 igs (149247, 6, 4, ) [QSim__SAVE_IGS_EVENTID] 6 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/tmp/blyth/opticks/.opticks/igs.npy] save_igs YES
    2025-06-12 16:01:29.091 INFO  [3957937] [QSim::simulate@438]  igs (149247, 6, 4, ) MaxSlot 262000000 sslice::Desc(igs_slice)
    sslice::Desc num_slice 1 TotalPhoton 34205002
      0 : sslice {    0,149247,      0,34205002}
                  start stop  offset   count 
     num_slice 1
    2025-06-12 16:01:29.091 INFO  [3957937] [QSim::simulate@454] sslice {    0,149247,      0,34205002}
    2025-06-12 16:01:29.100 INFO  [3957937] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 16:01:29.101 INFO  [3957937] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 34205002 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 16:01:29,202] p3957937 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 3957959) exited]

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00000000c53eca80 in ?? ()
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 nvidia-driver-libs-570.124.06-1.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 


Examine the igs::

    In [1]: import numpy as np

    In [2]: gs = np.load("/tmp/blyth/opticks/.opticks/igs.npy")

    In [3]: gs.shape
    Out[3]: (149247, 6, 4)

    In [4]: gs[0]
    Out[4]: 
    array([[ 2.5223372e-44,  2.8025969e-45,  2.1019477e-44,  4.2038954e-45],
           [-1.0052462e+04, -1.6695398e+04,  4.3403184e+04,  3.6035343e+01],
           [-2.0085740e+00,  8.3504877e+00, -2.6040117e+01,  2.7419933e+01],
           [           nan,  1.0000000e+00,  1.0000000e+00,  2.9979245e+02],
           [ 1.0000000e+00,  1.9997452e+02,  7.9989807e+02,  9.9972707e-01],
           [ 5.4577651e-04,  9.3852624e-02,  9.3852624e-02,  2.9979245e+02]],
          dtype=float32)


    In [6]: gs[:,0].view(np.int32)
    Out[6]: 
    array([[   18,     2,    15,     3],
           [   18,     2,    15,     1],
           [   18,     2,    15,     4],
           ...,
           [   18, 25223,    95,   124],
           [   18, 25223,    95,    60],
           [   18, 25223,    95,    25]], shape=(149247, 4), dtype=int32)

    In [7]: gs[:20,0].view(np.int32)
    Out[7]: 
    array([[18,  2, 15,  3],
           [18,  2, 15,  1],
           [18,  2, 15,  4],
           [18,  2, 15,  2],
           [18,  2, 15,  5],
           [18,  2, 15,  5],
           [18,  2, 15,  2],
           [18,  2, 15,  2],
           [18,  2, 15,  2],
           [18,  2, 15,  4],
           [18,  2, 15,  2],
           [18,  2, 15,  2],
           [18,  2, 15,  1],
           [18,  2, 15,  4],
           [18,  2, 15,  3],
           [18,  2, 15,  5],
           [18,  2, 15,  1],
           [18,  2, 15,  3],
           [18,  2, 15,  2],
           [18,  2, 15,  3]], dtype=int32)


::

    In [9]: np.c_[np.unique(gs[:,0,0].view(np.int32), return_counts=True)]
    Out[9]: array([[    18, 149247]])

    In [10]: gs.shape
    Out[10]: (149247, 6, 4)



All G4Cerenkov_modified::

     19 enum
     20 {
     21     OpticksGenstep_INVALID                  = 0,
     22     OpticksGenstep_G4Cerenkov_1042          = 1,
     23     OpticksGenstep_G4Scintillation_1042     = 2,
     24     OpticksGenstep_DsG4Cerenkov_r3971       = 3,
     25     OpticksGenstep_DsG4Scintillation_r3971  = 4,
     26     OpticksGenstep_DsG4Scintillation_r4695  = 5,
     27     OpticksGenstep_TORCH                    = 6,
     28     OpticksGenstep_FABRICATED               = 7,
     29     OpticksGenstep_EMITSOURCE               = 8,
     30     OpticksGenstep_NATURAL                  = 9,
     31     OpticksGenstep_MACHINERY                = 10,
     32     OpticksGenstep_G4GUN                    = 11,
     33     OpticksGenstep_PRIMARYSOURCE            = 12,
     34     OpticksGenstep_GENSTEPSOURCE            = 13,
     35     OpticksGenstep_CARRIER                  = 14,
     36     OpticksGenstep_CERENKOV                 = 15,
     37     OpticksGenstep_SCINTILLATION            = 16,
     38     OpticksGenstep_FRAME                    = 17,
     39     OpticksGenstep_G4Cerenkov_modified      = 18,
     40     OpticksGenstep_INPUT_PHOTON             = 19,
     41     OpticksGenstep_NumType                  = 20
     42 };





cxs_min.sh run using the igs : got OOM because another debugger process was occupying lots of VRAM
---------------------------------------------------------------------------------------------------


::

    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::addGenstep@2040] SEvt::id EGPU (0)  GSV YES SEvt__OTHER
    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::addGenstep@2040] SEvt::id EGPU (0)  GSV YES SEvt__OTHER
    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::addGenstep@2040] SEvt::id EGPU (0)  GSV YES SEvt__OTHER
    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::addGenstep@2040] SEvt::id EGPU (0)  GSV YES SEvt__OTHER
    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::addGenstep@2040] SEvt::id EGPU (0)  GSV YES SEvt__OTHER
    2025-06-12 16:28:26.516 INFO  [3959607] [SEvt::beginOfEvent@1578]  NumPhotonCollected 34205002 NumGenstepCollected 149247 MaxBounce 31
    2025-06-12 16:28:26.535 INFO  [3959607] [QSim::MaybeSaveIGS@540]  eventID 0 igs (149247, 6, 4, ) [QSim__SAVE_IGS_EVENTID] -1 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/data1/blyth/tmp/.opticks/igs.npy] save_igs NO 
    2025-06-12 16:28:26.538 INFO  [3959607] [QSim::simulate@438]  igs (149247, 6, 4, ) MaxSlot 262000000 sslice::Desc(igs_slice)
    sslice::Desc num_slice 1 TotalPhoton 34205002
      0 : sslice {    0,149247,      0,34205002}
                  start stop  offset   count 
     num_slice 1
    2025-06-12 16:28:26.538 INFO  [3959607] [QSim::simulate@454] sslice {    0,149247,      0,34205002}
    2025-06-12 16:28:26.538 INFO  [3959607] [QEvent::setGenstepUpload_NP@195]  gs (149247, 6, 4, )SGenstep::DescGensteps num_genstep 149247 (3 1 4 2 5 5 2 2 2 4 ... 289 271 311 256 198 169 124 60 25 ) total 34205002
    2025-06-12 16:28:26.538 INFO  [3959607] [QEvent::setGenstepUpload@311] [
    2025-06-12 16:28:26.538 INFO  [3959607] [QEvent::setGenstepUpload@324]  gs_start 0 gs_stop 149247 evt.num_genstep 149247 not_allocated YES zero_genstep NO 
    2025-06-12 16:28:26.538 INFO  [3959607] [QEvent::setGenstepUpload@334] [ device_alloc_genstep_and_seed 
    2025-06-12 16:28:26.538 INFO  [3959607] [QEvent::device_alloc_genstep_and_seed@429]  device_alloc genstep and seed 
    2025-06-12 16:28:26.539 INFO  [3959607] [QEvent::setGenstepUpload@336] ] device_alloc_genstep_and_seed 
    2025-06-12 16:28:26.539 INFO  [3959607] [QEvent::setGenstepUpload@350] [ QU::copy_host_to_device 
    2025-06-12 16:28:26.539 INFO  [3959607] [QEvent::setGenstepUpload@352] ] QU::copy_host_to_device 
    2025-06-12 16:28:26.539 INFO  [3959607] [QEvent::setGenstepUpload@359] [ QU::device_memset 
    2025-06-12 16:28:26.540 INFO  [3959607] [QEvent::setGenstepUpload@361] ] QU::device_memset 
    2025-06-12 16:28:26.540 INFO  [3959607] [QEvent::setGenstepUpload@371] [ count_genstep_photons_and_fill_seed_buffer 
    2025-06-12 16:28:26.549 INFO  [3959607] [QEvent::setGenstepUpload@373] ] count_genstep_photons_and_fill_seed_buffer 
    2025-06-12 16:28:26.549 INFO  [3959607] [QEvent::setNumPhoton@975] 
    2025-06-12 16:28:26.549 INFO  [3959607] [QEvent::device_alloc_photon@1009]  evt.max_slot   262000000 evt.max_photon 1000000000 evt.num_photon 34205002 evt.num_record 0 evt.num_rec    0 evt.num_seq    0 evt.num_prd    0 evt.num_tag    0 evt.num_flat   0
    2025-06-12 16:28:26.549 ERROR [3959607] [QU::_cudaMalloc@272] save salloc record to /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest
    terminate called after throwing an instance of 'QUDA_Exception'
      what():  CUDA call (QEvent::device_alloc_photon/max_slot*sizeof(sphoton) ) failed with error: 'out of memory' (/home/blyth/opticks/qudarap/QU.cc:265)
    [salloc::desc alloc.size 25 label.size 25
    [salloc.meta
    evt.max_curand:1000000000
    evt.max_slot:262000000
    evt.max_photon:1000000000
    evt.num_photon:34205002
    evt.max_curand/M:1000
    evt.max_slot/M:262
    evt.max_photon/M:1000
    evt.num_photon/M:34
    evt.max_record:0
    evt.max_rec:0
    evt.max_seq:0
    evt.max_prd:0
    evt.max_tag:0
    evt.max_flat:0
    evt.num_record:0
    evt.num_rec:0
    evt.num_seq:0
    evt.num_prd:0
    evt.num_tag:0
    evt.num_flat:0
    ]salloc.meta

         [           size   num_items sizeof_item       spare]    size_GB    percent label
         [        (bytes)                                    ]   size/1e9            

         [              8           1           8           0]       0.00       0.00 QBase::init/d_base
         [             24           1          24           0]       0.00       0.00 QRng::initMeta/d_qr
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             32           1          32           0]       0.00       0.00 QBnd::QBnd/d_qb
         [            432           1         432           0]       0.00       0.00 QDebug::QDebug/d_dbg
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             24           1          24           0]       0.00       0.00 QScint::QScint/d_scint
         [             24           1          24           0]       0.00       0.00 QCerenkov::QCerenkov/d_cerenkov.0
         [           2880         720           4           0]       0.00       0.00 QProp::upload/pp
         [             16           1          16           0]       0.00       0.00 QProp::upload/d_prop
         [           1056         264           4           0]       0.00       0.00 QProp::upload/pp
         [             16           1          16           0]       0.00       0.00 QProp::upload/d_prop
         [            240          60           4           0]       0.00       0.00 QProp::upload/pp
         [             16           1          16           0]       0.00       0.00 QProp::upload/d_prop
         [            240          60           4           0]       0.00       0.00 QProp::upload/pp
         [             16           1          16           0]       0.00       0.00 QProp::upload/d_prop
         [             48          12           4           0]       0.00       0.00 QPMT::init_thickness/d_thickness
         [         140896       35224           4           0]       0.00       0.00 QPMT::init_lcqs/d_lcqs
         [             56           1          56           0]       0.00       0.00 QPMT::init/d_pmt
         [            256           1         256           0]       0.00       0.00 QEvent::QEvent/sevent
         [             64           1          64           0]       0.00       0.00 QSim::init.sim
         [        8294400     2073600           4           0]       0.01       0.04 Frame::DeviceAllo:num_pixels
         [      960000000    10000000          96           0]       0.96       4.42 QEvent::setGenstep/device_alloc_genstep_and_seed:quad6
         [     4000000000  1000000000           4           0]       4.00      18.40 QEvent::setGenstep/device_alloc_genstep_and_seed:int seed
         [    16768000000   262000000          64           0]      16.77      77.14 QEvent::device_alloc_photon/max_slot*sizeof(sphoton)

     tot      21736440872                                           21.74
    ]salloc::desc
     ;
    QU::_cudaMalloc_OOM_NOTES
    ==========================

    When running with debug arrays, such as the record array, enabled
    it is necessary to set max_slot to something reasonable, otherwise with the 
    default max_slot of zero, it gets set to a high value (eg M197 with 24GB) 
    appropriate for production running with the available VRAM. 

    One million is typically reasonable for debugging:: 

       export OPTICKS_MAX_SLOT=M1



    Thread 1 "CSGOptiXSMTest" received signal SIGABRT, Aborted.
    0x00007ffff4a8b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install glibc-2.34-125.el9_5.3.alma.1.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libnvidia-ml-570.124.06-1.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 nvidia-driver-cuda-libs-570.124.06-1.el9.x86_64 nvidia-driver-libs-570.124.06-1.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64
    (gdb) 
    quit
    A debugging session is active.

        Inferior 1 [process 3959607] will be killed.






::

    egin of Event --> 6
    2025-06-12 20:34:54.409 INFO  [1222061] [QSim::MaybeSaveIGS@577]  eventID 6 igs (149247, 6, 4, ) [QSim__SAVE_IGS_EVENTID] -1 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/tmp/blyth/opticks/.opticks/igs.npy] save_igs NO 
    2025-06-12 20:34:54.412 INFO  [1222061] [QSim::simulate@446]  igs (149247, 6, 4, ) MaxSlot 10000000 MaxSlot/M 10 sslice::Desc(igs_slice)
    sslice::Desc num_slice 4 TotalPhoton 34205002
      0 : sslice {    0,36176,      0,9999742}
      1 : sslice {36176,86770,9999742,9999892}
      2 : sslice {86770,124182,19999634,9999793}
      3 : sslice {124182,149247,29999427,4205575}
                  start stop  offset   count 
     num_slice 4
    2025-06-12 20:34:54.413 INFO  [1222061] [QSim::simulate@463] sslice {    0,36176,      0,9999742}
    2025-06-12 20:34:54.421 INFO  [1222061] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 20:34:54.421 INFO  [1222061] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 9999742 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 20:34:54,523] p1222061 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1222074) exited]

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00000000c53eb400 in ?? ()




FIXED : Slicing small runs into NPFold::can_concat issue 
---------------------------------------------------------

* FIX by reimplementing NPFold::concat to be less strict regarding existance
  within every subfold because many slices would have no hits when slice fine enough

::

    025-06-12 22:40:56.467 INFO  [110452] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0001
    2025-06-12 22:40:56.467 INFO  [110452] [QSim::simulate@447]   31 : sslice {  3246,  3538,   28755,     996}
    2025-06-12 22:40:56.476 INFO  [110452] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 22:40:56.476 INFO  [110452] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 996 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 22:40:56.476 INFO  [110452] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0001
    2025-06-12 22:40:56.476 INFO  [110452] [QSim::simulate@447]   32 : sslice {  3538,  3557,   29751,      72}
    2025-06-12 22:40:56.484 INFO  [110452] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 22:40:56.484 INFO  [110452] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 72 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 22:40:56.484 INFO  [110452] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0001
    python: /data1/blyth/local/opticks_Debug/include/SysRap/NPFold.h:1247: void NPFold::concat(std::ostream*): Assertion `can' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 nvidia-driver-libs-570.124.06-1.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 
    quit
    A debugging session is active.

        Inferior 1 [process 110452] will be killed.

    Quit anyway? (y or n) y
    Thu Jun 12 10:57:33 PM CST 2025
    A[blyth@localhost muon]$ 



    2025-06-12 23:02:03.727 INFO  [115621] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 23:02:03.727 INFO  [115621] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 996 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 23:02:03.727 INFO  [115621] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0001
    2025-06-12 23:02:03.727 INFO  [115621] [QSim::simulate@447]   32 : sslice {  3538,  3557,   29751,      72}
    2025-06-12 23:02:03.735 INFO  [115621] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 23:02:03.735 INFO  [115621] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 72 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 23:02:03.736 INFO  [115621] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0001
    NPFold::concat can_concat FAIL : problem with subfold ? return 1 
    2025-06-12 23:02:03.736 INFO  [115621] [QSim::simulate@480] NPFold::concat zero_sub NO 
    NPFold::can_concat maxdepth 1
    NPFold::can_concat num_sub 33
    NPFold::can_concat all_intkey YES
    NPFold::can_concat num_top_kk0 0
    NPFold::can_concat sub_with_all_kk0 1
    NPFold::can_concat can NO 

    2025-06-12 23:02:03.736 FATAL [115621] [QSim::simulate@481]  sev->topfold->concat FAILED 
    python: /home/blyth/opticks/qudarap/QSim.cc:482: double QSim::simulate(int, bool): Assertion `concat_rc == 0' failed.





OPTICKS_MAX_SLOT=M1 shows issue within the 3rd launch, so slice finer with M1 into 35 launch
------------------------------------------------------------------------------------------------

::

    Begin of Event --> 6
    2025-06-12 21:45:23.141 INFO  [1794857] [QSim::MaybeSaveIGS@567]  eventID 6 igs (149247, 6, 4, ) igs_null NO  [QSim__SAVE_IGS_EVENTID] -1 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/tmp/blyth/opticks/.opticks/igs.npy] save_igs NO 
    2025-06-12 21:45:23.144 INFO  [1794857] [QSim::simulate@429]  igs (149247, 6, 4, ) MaxSlot 1000000 MaxSlot/M 1 sslice::Desc(igs_slice)
    sslice::Desc num_slice 35 TotalPhoton 34205002
      0 : sslice {    0, 4164,      0, 999778}
      1 : sslice { 4164, 7738, 999778, 999915}
      2 : sslice { 7738,11282,1999693, 999700}
      3 : sslice {11282,14856,2999393, 999809}
      4 : sslice {14856,18413,3999202, 999869}
      5 : sslice {18413,21955,4999071, 999920}
      6 : sslice {21955,25507,5998991, 999872}
      7 : sslice {25507,29058,6998863, 999746}
      8 : sslice {29058,32608,7998609, 999812}
      9 : sslice {32608,36171,8998421, 999882}
     10 : sslice {36171,40784,9998303, 999820}
     11 : sslice {40784,46753,10998123, 999920}
     12 : sslice {46753,52723,11998043, 999984}
     13 : sslice {52723,58762,12998027, 999766}
     14 : sslice {58762,63838,13997793, 999959}
     15 : sslice {63838,68654,14997752, 999748}
     16 : sslice {68654,73582,15997500, 999873}
     17 : sslice {73582,78075,16997373, 999721}
     18 : sslice {78075,83210,17997094, 999886}
     19 : sslice {83210,86760,18996980, 999772}
     20 : sslice {86760,90328,19996752, 999926}
     21 : sslice {90328,93897,20996678, 999872}
     22 : sslice {93897,97459,21996550, 999771}
     23 : sslice {97459,101012,22996321, 999942}
     24 : sslice {101012,104569,23996263, 999753}
     25 : sslice {104569,108129,24996016, 999850}
     26 : sslice {108129,111686,25995866, 999893}
     27 : sslice {111686,115245,26995759, 999990}
     28 : sslice {115245,118800,27995749, 999718}
     29 : sslice {118800,124168,28995467, 999798}
     30 : sslice {124168,128755,29995265, 999840}
     31 : sslice {128755,134278,30995105, 999879}
     32 : sslice {134278,141802,31994984, 999960}
     33 : sslice {141802,147522,32994944, 999851}
     34 : sslice {147522,149247,33994795, 210207}
                  start stop  offset   count 
     num_slice 35
    2025-06-12 21:45:23.144 INFO  [1794857] [QSim::simulate@446] sslice {    0, 4164,      0, 999778}
    2025-06-12 21:45:23.152 INFO  [1794857] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:45:23.152 INFO  [1794857] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 999778 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:45:23.177 INFO  [1794857] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0247
    2025-06-12 21:45:23.177 INFO  [1794857] [QSim::simulate@446] sslice { 4164, 7738, 999778, 999915}
    2025-06-12 21:45:23.185 INFO  [1794857] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:45:23.185 INFO  [1794857] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 999915 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:45:23.210 INFO  [1794857] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0251
    2025-06-12 21:45:23.210 INFO  [1794857] [QSim::simulate@446] sslice { 7738,11282,1999693, 999700}
    2025-06-12 21:45:23.218 INFO  [1794857] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:45:23.218 INFO  [1794857] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 999700 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 21:45:23,273] p1794857 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1794873) exited]

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    (gdb) 


H1=K100 slicing into 343 launches
-----------------------------------

::


    Begin of Event --> 6
    2025-06-12 21:55:51.960 INFO  [1795697] [QSim::MaybeSaveIGS@567]  eventID 6 igs (149247, 6, 4, ) igs_null NO  [QSim__SAVE_IGS_EVENTID] -1 [QSim__SAVE_IGS_PATH] $TMP/.opticks/igs.npy igs_path [/tmp/blyth/opticks/.opticks/igs.npy] save_igs NO 
    2025-06-12 21:55:51.963 INFO  [1795697] [QSim::simulate@429]  igs (149247, 6, 4, ) MaxSlot 100000 MaxSlot/M 0 sslice::Desc(igs_slice)
    sslice::Desc num_slice 343 TotalPhoton 34205002

                   start stop   offset  count
      0 : sslice {    0,  950,      0,  99816}
      1 : sslice {  950, 1304,  99816,  99867}
      2 : sslice { 1304, 1666, 199683,  99807}
      3 : sslice { 1666, 2019, 299490,  99880}
      4 : sslice { 2019, 2377, 399370,  99859}
      5 : sslice { 2377, 2730, 499229,  99954}
      6 : sslice { 2730, 3086, 599183,  99997}
    ...
    328 : sslice {139871,140806,32753911,  99904}
    329 : sslice {140806,141574,32853815,  99892}
    330 : sslice {141574,142107,32953707,  99902}
    331 : sslice {142107,142604,33053609,  99953}
    332 : sslice {142604,143206,33153562,  99845}
    333 : sslice {143206,143824,33253407,  99781}
    334 : sslice {143824,144552,33353188,  99985}
    335 : sslice {144552,145179,33453173,  99980}
    336 : sslice {145179,145695,33553153,  99940}
    337 : sslice {145695,146170,33653093,  99909}
    338 : sslice {146170,146766,33753002,  99954}
    339 : sslice {146766,147366,33852956,  99847}
    340 : sslice {147366,147941,33952803,  99898}
    341 : sslice {147941,148902,34052701,  99902}
    342 : sslice {148902,149247,34152603,  52399}
                  start stop  offset   count 
     num_slice 343
    ...
    2025-06-12 21:55:52.161 INFO  [1795697] [QSim::simulate@446] sslice { 5952, 6304,1497922,  99897}
    2025-06-12 21:55:52.173 INFO  [1795697] [QSim::simulate@446] sslice { 6304, 6656,1597819,  99893}
    2025-06-12 21:55:52.186 INFO  [1795697] [QSim::simulate@446] sslice { 6656, 7011,1697712,  99781}
    2025-06-12 21:55:52.197 INFO  [1795697] [QSim::simulate@446] sslice { 7011, 7370,1797493,  99985}
    2025-06-12 21:55:52.207 INFO  [1795697] [QSim::simulate@446] sslice { 7370, 7730,1897478,  99758}
    2025-06-12 21:55:52.216 INFO  [1795697] [QSim::simulate@446] sslice { 7730, 8083,1997236,  99863}
    2025-06-12 21:55:52.237 INFO  [1795697] [QSim::simulate@446] sslice { 8083, 8440,2097099,  99912}
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 21:55:52,287] p1795697 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1795710) exited]


    echo $(( 2097099 + 99912 ))     2197011




Slicing finer MAX_SLOT K1 : pins down to within 3 gensteps: 8259,8260,8261 corresponding to 875 photons
--------------------------------------------------------------------------------------------------------

::

    2025-06-12 23:35:17.310 INFO  [120940] [QSim::simulate@447] 2414 : sslice {  8246,  8250, 2142695,     890}
    2025-06-12 23:35:17.324 INFO  [120940] [QSim::simulate@447] 2415 : sslice {  8250,  8253, 2143585,     966}
    2025-06-12 23:35:17.340 INFO  [120940] [QSim::simulate@447] 2416 : sslice {  8253,  8256, 2144551,     951}
    2025-06-12 23:35:17.353 INFO  [120940] [QSim::simulate@447] 2417 : sslice {  8256,  8259, 2145502,     712}
    2025-06-12 23:35:17.368 INFO  [120940] [QSim::simulate@447] 2418 : sslice {  8259,  8262, 2146214,     875}
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 23:35:17,416] p120940 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 120953) exited]

    (gdb) 

    echo $(( 2146214 + 875 ))      2147089



igs.sh : anything special about those three gensteps ?
---------------------------------------------------------

::

    (ok) A[blyth@localhost muon]$ ./igs.sh 
             BASH_SOURCE : ./igs.sh
                     PWD : /home/blyth/j/muon
                    name : igs
                  script : igs.py
                  defarg : info_pdb
                     arg : info_pdb
                IGS_PATH : /home/blyth/.opticks/crash_muon_igs.npy
    Python 3.13.2 | packaged by Anaconda, Inc. | (main, Feb  6 2025, 18:56:02) [GCC 11.2.0]
    Type 'copyright', 'credits' or 'license' for more information
    IPython 9.1.0 -- An enhanced Interactive Python. Type '?' for help.
    Tip: Use `F2` or %edit with no arguments to open an empty editor with a temporary file.
    igs.shape (149247, 6, 4)
    igs
     [[[     0.              0.              0.              0.        ]
      [-10052.462      -16695.398       43403.184          36.035343  ]
      [    -2.008574        8.350488      -26.040117       27.419933  ]
      [            nan      1.              1.            299.79245   ]
      [     1.            199.97452       799.8981          0.9997271 ]
      [     0.00054578      0.09385262      0.09385262    299.79245   ]]



    In [4]: igs[8259:8262].view(np.int32)[:,0]
    Out[4]: 
    array([[ 18,   2, 103, 319],
           [ 18,   2, 103, 260],
           [ 18,   2, 103, 296]], dtype=int32)

    In [6]: igs[8259:8262].view(np.int32)[:,0,3].sum()
    Out[6]: np.int64(875)


    n [7]: igs[8259:8262]
    Out[7]: 
    array([[[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12398.721,  -6936.81 ,  12980.386,    142.895],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]],

           [[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12398.815,  -6936.416,  12979.159,    142.899],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]],

           [[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12398.91 ,  -6936.022,  12977.934,    142.903],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]]], dtype=float32)


Using cxr_min.sh viz shows the position is at top and edge of waterpool.

Other gensteps nearby very similar (stuck track?)::

    In [8]: igs[8250:8253]
    Out[8]: 
    array([[[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12397.932,  -6940.1  ,  12990.633,    142.859],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]],

           [[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12398.026,  -6939.706,  12989.406,    142.863],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]],

           [[     0.   ,      0.   ,      0.   ,      0.   ],
            [-12398.121,  -6939.312,  12988.181,    142.867],
            [    -0.094,      0.394,     -1.226,      1.291],
            [       nan,      1.   ,      1.   ,    299.792],
            [     1.   ,     79.99 ,    799.898,      0.719],
            [     0.482,    232.344,    232.344,    299.792]]], dtype=float32)




::

    In [23]: dv = igs[:,5,1] - igs[:,5,2]

    In [24]: dv
    Out[24]: 
    array([ 0.   ,  0.   ,  0.   , ..., 21.942, 54.774, 60.942],
          shape=(149247,), dtype=float32)

    In [25]: dv.min(0
        ...: )
    Out[25]: np.float32(0.0)

    In [26]: dv.min()
    Out[26]: np.float32(0.0)

    In [27]: dv.max()
    Out[27]: np.float32(150.42343)

    In [28]: np.where( dv == 0. )
    Out[28]: 
    (array([     0,      1,      2, ..., 132484, 132488, 132635],
           shape=(80622,)),)

    In [29]: dv.shape
    Out[29]: (149247,)


qcerenkov::fraction_sampled lots of 

::

    136 inline QCERENKOV_METHOD void qcerenkov::fraction_sampled(float& fraction, float& delta, RNG& rng, const scerenkov& gs, int idx, int gsid ) const
    137 {
    138     float NumberOfPhotons ;
    139     float N ;
    140     float u ;
    141 
    142     float MeanNumberOfPhotonsMax = fmaxf( gs.MeanNumberOfPhotons1, gs.MeanNumberOfPhotons2 );
    143     float DeltaN = (gs.MeanNumberOfPhotons1-gs.MeanNumberOfPhotons2) ;
    144     do
    145     {
    146         fraction = curand_uniform(&rng) ;
    147 
    148         delta = fraction * gs.step_length ;
    149 
    150         NumberOfPhotons = gs.MeanNumberOfPhotons1 - fraction * DeltaN  ;
    151 
    152         u = curand_uniform(&rng) ;
    153 
    154         N = u * MeanNumberOfPhotonsMax ;
    155 
    156     } while (N > NumberOfPhotons);
    157 
    158     //printf("//qcerenkov::fraction_sampled fraction %10.4f delta %10.4f \n", fraction, delta ); 
    159 
    160 }





U4 + scerenkov
-----------------

::

    214     scerenkov* gs = (scerenkov*)(&_gs) ;
    215 
    216     gs->gentype = OpticksGenstep_G4Cerenkov_modified ;
    217     gs->trackid = aTrack->GetTrackID() ;
    218     gs->matline = aMaterial->GetIndex() + SEvt::G4_INDEX_OFFSET ;  // offset signals that a mapping must be done in SEvt::setGenstep
    219     gs->numphoton = numPhotons ;
    220 
    221     gs->pos.x = x0.x() ;
    222     gs->pos.y = x0.y() ;
    223     gs->pos.z = x0.z() ;
    224     gs->time = t0 ;
    225 
    226     gs->DeltaPosition.x = deltaPosition.x() ;
    227     gs->DeltaPosition.y = deltaPosition.y() ;
    228     gs->DeltaPosition.z = deltaPosition.z() ;
    229     gs->step_length = aStep->GetStepLength() ;
    230 
    231     gs->code = aParticle->GetDefinition()->GetPDGEncoding() ;
    232     gs->charge = aParticle->GetDefinition()->GetPDGCharge() ;
    233     gs->weight = aTrack->GetWeight() ;
    234     gs->preVelocity = pPreStepPoint->GetVelocity() ;
    235 
    236     gs->BetaInverse = betaInverse ;
    237     gs->Wmin = Wmin_nm ;
    238     gs->Wmax = Wmax_nm   ;
    239     gs->maxCos = maxCos ;
    240 
    241     gs->maxSin2 = maxSin2 ;
    242     gs->MeanNumberOfPhotons1 = meanNumberOfPhotons1 ;
    243     gs->MeanNumberOfPhotons2 = meanNumberOfPhotons2 ;
    244     gs->postVelocity = pPostStepPoint->GetVelocity() ;





need to get cxs_min.sh to reproduce the issue to change 5 min dev cycle to 5 seconds
----------------------------------------------------------------------------------------

::

    296 static __forceinline__ __device__ void simulate( const uint3& launch_idx, const uint3& dim, quad2* prd )
    297 {
    298     sevent* evt = params.evt ;
    299     if (launch_idx.x >= evt->num_photon) return;   // ? evt->num_slot ?
    300 
    301     unsigned idx = launch_idx.x ;
    302     unsigned genstep_idx = evt->seed[idx] ;
    303     const quad6& gs = evt->genstep[genstep_idx] ;
    304     // genstep needs the raw index, from zero for each genstep slice sub-launch
    305 
    306     unsigned photon_idx = params.photon_slot_offset + idx ;
    307     // rng_state access and array recording needs the absolute photon_idx
    308     // for multi-launch and single-launch simulation to match.
    309     // The offset hides the technicality of the multi-launch from output.
    310 
    311     qsim* sim = params.sim ;
    312 
    313 //#define OLD_WITHOUT_SKIPAHEAD 1
    314 #ifdef OLD_WITHOUT_SKIPAHEAD
    315     RNG rng = sim->rngstate[photon_idx] ;
    316 #else
    317     RNG rng ;
    318     sim->rng->init( rng, sim->evt->index, photon_idx );
    319 #endif
    320 
    321 
    322     sctx ctx = {} ;
    323     ctx.evt = evt ;
    324     ctx.prd = prd ;
    325     ctx.idx = idx ;
    326 
    327     sim->generate_photon(ctx.p, rng, gs, photon_idx, genstep_idx );
    328 
    329     int command = START ;
    330     int bounce = 0 ;
    331 #ifndef PRODUCTION
    332     ctx.point(bounce);
    333 #endif
    334     while( bounce < evt->max_bounce )
    335     {
    336         trace( params.handle, ctx.p.pos, ctx.p.mom, params.tmin, params.tmax, prd, params.vizmask );  // geo query filling prd
    337         if( prd->boundary() == 0xffffu ) break ; // SHOULD ONLY HAPPEN FOR PHOTONS STARTING OUTSIDE WORLD
    338         // propagate can do nothing meaningful without a boundary
    339 
    340         // HMM: normalize here or within CSG ? Actually only needed for
    341         // geometry with active scaling, such as ellipsoid.
    342         // TODO: move this so its only done when needed
    343         //     ~/o/notes/issues/CSGOptiX_simulate_avoid_normalizing_every_normal.rst
    344         //
    345 
    346         float3* normal = prd->normal();
    347         *normal = normalize(*normal);
    348 


    103 /**
    104 qrng<Philox>
    105 -------------
    106 
    107 With Philox the curand_init does skipahead and skipahead_sequence advancing ctr.xyzw:
    108 
    109 skipahead(offset,&rng)
    110    ctr.xyzw
    111 
    112 skipahead_sequence(subsequence,&rng)  
    113    ctr.zw
    114 
    115 **/
    116 
    117 template<>
    118 struct qrng<Philox>
    119 {
    120     ULL  seed ;
    121     ULL  offset ;
    122     ULL  skipahead_event_offset ;
    123 
    124 #if defined(__CUDACC__) || defined(__CUDABE__)
    125     QRNG_METHOD void init(Philox& rng, unsigned event_idx, unsigned photon_idx )
    126     {
    127         ULL subsequence_ = photon_idx ;
    128         curand_init( seed, subsequence_, offset, &rng ) ;
    129         ULL skipahead_ = skipahead_event_offset*event_idx ;
    130         skipahead( skipahead_, &rng );
    131     }
    132 #else
    133     qrng(ULL seed_, ULL offset_, ULL skipahead_event_offset_ )
    134         :
    135         seed(seed_),
    136         offset(offset_),
    137         skipahead_event_offset(skipahead_event_offset_)
    138     {
    139     }
    140     void set_uploaded_states( void* ){}
    141 #endif
    142 };





sim->evt->index
-----------------

Need to offset the event_idx in the igs running to the 
event_idx where the igs came from::


      72 struct qsim
      73 {
      74     qbase*              base ;
      75     sevent*             evt ;
      76     qrng<RNG>*          rng ; 
      77     qbnd*               bnd ;
      78     qmultifilm*         multifilm;
      79     qcerenkov*          cerenkov ;
      80     qscint*             scint ;
      81     qpmt<float>*        pmt ;



    099 struct sevent
    100 {
    101     static constexpr unsigned M = 1000000 ;
    102     static constexpr unsigned genstep_itemsize = 6*4 ;
    103     static constexpr unsigned genstep_numphoton_offset = 3 ;
    104     static constexpr float w_lo = 60.f ;
    105     static constexpr float w_hi = 820.f ;  // these need to match sdomain.h
    106     static constexpr float w_center = (w_lo+w_hi)/2.f ; // convert wavelength range into center-extent form
    107     static constexpr float w_extent = (w_hi-w_lo)/2.f ;
    108 
    109     float4 center_extent ;
    110     float2 time_domain ;
    111     float2 wavelength_domain ;
    112 
    113     // TODO: make all these below unsigned
    114     // sevent::init sets these max using values from SEventConfig
    115     int      max_curand ;
    116     int      max_slot   ;
    117     int      max_genstep ;  // eg:      100,000
    118     int      max_photon  ;  // eg:  100,000,000
    119     int      max_simtrace ; // eg: 100,000,000
    120 
    121     int      max_bounce  ; // eg: 0:32  (not including 32)
    122     int      max_record  ; // eg: 10  full step record
    123     int      max_rec     ; // eg: 10  compressed step record
    124     int      max_seq     ; // now restricted to 0 or 1 only
    125     int      max_prd     ; // eg: 16
    126     int      max_tag     ; // 0 or 1 only
    127     int      max_flat    ; // 0 or 1 only
    128     int      max_aux     ; // eg 0, 16, 32 : when greater than zero typically follows max_record
    129     int      max_sup     ;
    130 
    131     int      index ;
    132 
    133     //[ counts and pointers, zeroed by sevent::zero
    134     //  only first 4 are always in use, the last 7 are only relevant whilst debugging
    135     //
    136     int      num_curand ;
    137     int      num_genstep ;
    138     int      num_seed ;
    139     int      num_hit ;    // set by QEvent::gatherHit using SU::count_if_sphoton
    140     int      num_photon ;
    141 
    142     int      num_record ;
    143     int      num_rec ;
    144     int      num_seq ;
    145     int      num_prd ;
    146     int      num_tag ;


Controlling the event index
-----------------------------

::

    0223 int SEventConfig::EventIndex(int idx){ return _StartIndex + idx ; }
     224 int SEventConfig::EventIndexArg(int index){ return index == MISSING_INDEX ? -1 : index - _StartIndex ; }
    151     static constexpr const char* kStartIndex   = "OPTICKS_START_INDEX" ;
    01 int         SEventConfig::_StartIndex = ssys::getenvint(kStartIndex, _StartIndexDefault );

    (ok) A[blyth@localhost qudarap]$ opticks-f SEventConfig::EventIndex
    ./sysrap/SEventConfig.cc:int SEventConfig::EventIndex(int idx){ return _StartIndex + idx ; }
    ./sysrap/SEventConfig.cc:int SEventConfig::EventIndexArg(int index){ return index == MISSING_INDEX ? -1 : index - _StartIndex ; }
    ./sysrap/SEvt.cc:    event index obtained from SEventConfig::EventIndex(index_arg)
    ./sysrap/SEvt.cc:    index = SEventConfig::EventIndex(index_arg) ;
    ./sysrap/SEvt.cc:    int index_expected = SEventConfig::EventIndex(index_arg) ;
    ./sysrap/SEvt.cc:    return SEventConfig::EventIndexArg(index);
    (ok) A[blyth@localhost opticks]$ 



::

     162 int CSGOptiX::SimulateMain() // static
     163 {
     164     SProf::Add("CSGOptiX__SimulateMain_HEAD");
     165     SEventConfig::SetRGModeSimulate();
     166     CSGFoundry* fd = CSGFoundry::Load();
     167     CSGOptiX* cx = CSGOptiX::Create(fd) ;
     168     for(int i=0 ; i < SEventConfig::NumEvent() ; i++) cx->simulate(i);
     169     SProf::UnsetTag();
     170     SProf::Add("CSGOptiX__SimulateMain_TAIL");
     171     SProf::Write("run_meta.txt", true ); // append:true
     172     cx->write_Ctx_log();
     173     delete cx ;
     174     return 0 ;
     175 }

     690 double CSGOptiX::simulate(int eventID)
     691 {
     692     SProf::SetTag(eventID, "A%0.3d_" ) ;
     693     assert(sim);
     694     bool reset = true ;   // reset:true calls SEvt::endOfEvent for cleanup after simulate
     695     double dt = sim->simulate(eventID, reset) ; // (QSim)
     696     return dt ;
     697 }


    1557 void SEvt::beginOfEvent(int eventID)
    1558 {
    1559     if(isFirstEvtInstance() && eventID == 0) BeginOfRun() ;
    1560     if(eventID == 0) SetRunProf( isEGPU() ? "SEvt__beginOfEvent_FIRST_EGPU" : "SEvt__beginOfEvent_FIRST_ECPU" ) ;
    1561 
    1562     setStage(SEvt__beginOfEvent);
    1563     sprof::Stamp(p_SEvt__beginOfEvent_0);
    1564 
    1565     LOG(LEVEL) << " eventID " << eventID ;   // 0-based
    1566     setIndex(eventID);
    1567 
    1568 
    1569     LOG_IF(info, LIFECYCLE) << id() ;
    1570 
    1571     clear_output();   // output vectors and fold : excluding gensteps as thats input
    1572 
    1573     addInputGenstep();  // does genstep setup for simtrace, input photon and torch running
    1574 
    1575     setMeta<int>("NumPhotonCollected", numphoton_collected );
    1576     setMeta<int>("NumGenstepCollected", numgenstep_collected );
    1577     setMeta<int>("MaxBounce", evt->max_bounce );
    1578 
    1579     LOG_IF(info, LIFECYCLE)
    1580         << " NumPhotonCollected " << numphoton_collected
    1581         << " NumGenstepCollected " << numgenstep_collected
    1582         << " MaxBounce " << evt->max_bounce
    1583         ;
    1584 
    1585     sprof::Stamp(p_SEvt__beginOfEvent_1);
    1586 }


    1890 void SEvt::setIndex(int index_arg)
    1891 {
    1892     assert( index_arg >= 0 );
    1893     index = SEventConfig::EventIndex(index_arg) ;
    1894     t_BeginOfEvent = sstamp::Now();                // moved here from the static
    1895 
    1896     setRunProf_Annotated("SEvt__setIndex_" );
    1897 }


SEvt::index copied to sevent::index by SEvt::setNumPhoton
-----------------------------------------------------------

::

    2183 void SEvt::setNumPhoton(unsigned num_photon)
    2184 {
    2185     //LOG_IF(info, LIFECYCLE) << id() << " num_photon " << num_photon ;
    2186     bool num_photon_allowed = num_photon <= (unsigned)(evt->max_photon) ;   // evt->max_slot ?
    2187     const int M = 1000000 ;
    2188 
    2189     LOG_IF(fatal, !num_photon_allowed)
    2190         << " num_photon/M " << num_photon/M
    2191         << " evt.max_photon/M " << evt->max_photon/M
    2192         << " num_photon " << num_photon
    2193         << " evt.max_photon " << evt->max_photon
    2194         ;
    2195     assert( num_photon_allowed );
    2196 
    2197     evt->index = index ;
    2198     evt->num_photon = num_photon ;
    2199     evt->num_seq    = evt->max_seq  == 1 ? evt->num_photon : 0 ;
    2200     evt->num_tag    = evt->max_tag  == 1 ? evt->num_photon : 0 ;
    2201     evt->num_flat   = evt->max_flat == 1 ? evt->num_photon : 0 ;
    2202     evt->num_sup    = evt->max_sup   > 0 ? evt->num_photon : 0 ;
    2203 
    2204     evt->num_record = evt->max_record * evt->num_photon ;
    2205     evt->num_rec    = evt->max_rec    * evt->num_photon ;
    2206     evt->num_aux    = evt->max_aux    * evt->num_photon ;
    2207     evt->num_prd    = evt->max_prd    * evt->num_photon ;
    2208 
    2209     LOG(LEVEL)






eventID 6 PIDX=1000000
------------------------

::

    2025-06-13 15:39:23.992 INFO  [177112] [QSim::simulate@448]    0 : sslice {     0, 36176,       0, 9999742}
    2025-06-13 15:39:24.000 INFO  [177112] [CSGOptiX::prepareParamSimulate@944] 
    2025-06-13 15:39:24.000 INFO  [177112] [CSGOptiX::launch@1030]  raygenmode 2 SRG::Name(raygenmode) simulate width 9999742 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 

    //qsim.propagate.head idx 1000000 : ctx.evt.index 6 evt.index 6 

    //qsim.propagate.head idx 1000000 : bnc 0 boundary 25 cosTheta 0.62765312 
    //qsim.propagate.head idx 1000000 : mom = np.array([-0.61301464,0.57454115,-0.54232401]) ; lmom = 0.99999988  
    //qsim.propagate.head idx 1000000 : pos = np.array([-12037.18555,-8443.40918,17671.42578]) ; lpos = 22988.35156250 
    //qsim.propagate.head idx 1000000 : nrm = np.array([(-0.99966615,0.02583475,0.00000000]) ; lnrm = 0.99999994  
    //qbnd.fill_state idx 1000000 boundary 25 line 100 wavelength   303.6495 m1_line 103 m2_line 100 su_line 102 s.optical.x 131  
    //qbnd.fill_state idx 1000000 boundary 25 [s.index.x-1](m1_index) 11 [s.index.y-1](m2_index) 10 [s.index.z-1](su_index) 130 
    //qsim.propagate_to_boundary.head idx 1000000 : u_absorption 0.99995255 logf(u_absorption) -0.00004740 absorption_length  9320.5557 absorption_distance   0.441792 
    //qsim.propagate_to_boundary.head idx 1000000 : post = np.array([-12037.18555,-8443.40918,17671.42578, 126.41569]) 
    //qsim.propagate_to_boundary.head idx 1000000 : distance_to_boundary 15669.4287 absorption_distance     0.4418 scattering_distance 105995182080.0000 
    //qsim.propagate_to_boundary.head idx 1000000 : u_scattering     0.8994 u_absorption     1.0000 
    //qsim.propagate_to_boundary.body.BULK_ABSORB idx 1000000 : post = np.array([-12037.45605,-8443.15527,17671.18555, 126.41773]) ; absorb_time_delta = 0.00204170   
    //qsim.propagate.body idx 1000000 bounce 0 command 1 flag 8 s.optical.x 131 s.optical.y 2 
    //qsim.propagate.tail idx 1000000 bounce 0 command 1 flag 8 ctx.s.optical.y(ems) 2 
    2025-06-13 15:39:24.837 INFO  [177112] [CSGOptiX::launch@1070]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.8366
    2025-06-13 15:39:24.877 INFO  [177112] [QSim::simulate@448]    1 : sslice { 36176, 86770, 9999742, 9999892}
    2025-06-13 15:39:24.886 INFO  [177112] [CSGOptiX::prepareParamSimulate@944] 
    2025-06-13 15:39:24.886 INFO  [177112] [CSGOptiX::launch@1030]  raygenmode 2 SRG::Name(raygenmode) simulate width 9999892 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-13 15:39:25.370 INFO  [177112] [CSGOptiX::launch@1070]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.4842
    2025-06-13 15:39:25.392 INFO  [177112] [QSim::simulate@448]    2 : sslice { 86770,124182,19999634, 9999793}
    2025-06-13 15:39:25.401 INFO  [177112] [CSGOptiX::prepareParamSimulate@944] 
    2025-06-13 15:39:25.401 INFO  [177112] [CSGOptiX::launch@1030]  raygenmode 2 SRG::Name(raygenmode) simulate width 9999793 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-13 15:39:26.150 INFO  [177112] [CSGOptiX::launch@1070]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.7492
    2025-06-13 15:39:26.183 INFO  [177112] [QSim::simulate@448]    3 : sslice {124182,149247,29999427, 4205575}
    2025-06-13 15:39:26.192 INFO  [177112] [CSGOptiX::prepareParamSimulate@944] 
    2025-06-13 15:39:26.192 INFO  [177112] [CSGOptiX::launch@1030]  raygenmode 2 SRG::Name(raygenmode) simulate width 4205575 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-13 15:39:26.391 INFO  [177112] [CSGOptiX::launch@1070]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.1990
    2025-06-13 15:39:26.494 INFO  [177112] [QSim::simulate@481] NPFold::concat zero_sub NO 
    NPFold::concat subfold.size 4 num_uk 1
    NPFold::concat_ non-trivial concat 
    NPFold::concat k hit.npy a (1508171, 4, 4, )




    (ok) A[blyth@localhost CSGOptiX]$ PIDX=1000000 cxs_min.sh
    2025-06-13 15:47:56.257 INFO  [178540] [SEventConfig::SetDevice@1374]  Configured_MaxSlot/M 10 Final_MaxSlot/M 10 HeuristicMaxSlot_Rounded/M 262 changed NO  DeviceName NVIDIA RTX 5000 Ada Generation HasDevice YES
    (export OPTICKS_MAX_SLOT=0 # to use VRAM based HeuristicMaxPhoton) 
    2025-06-13 15:47:56.357 INFO  [178540] [QRng::initStates@72] initStates<Philox> DO NOTHING : No LoadAndUpload needed  rngmax 1000000000 SEventConfig::MaxCurand 1000000000
    2025-06-13 15:47:56.357 INFO  [178540] [QRng::init@104] [QRng__init_VERBOSE] YES
    QRng::desc
                             IMPL CHUNKED_CURANDSTATE
                          RNGNAME Philox
                UPLOAD_RNG_STATES NO 
                             seed 0
                           offset 0
                           rngmax 1000000000
                         rngmax/M 1000
                               qr 0x15128fc0
        qr.skipahead_event_offset 100000
                             d_qr 0x7f0ba4c00200

    2025-06-13 15:47:56.593 INFO  [178540] [QSim::simulate@430]  eventID      0 igs (149247, 6, 4, ) MaxSlot 10000000 MaxSlot/M 10 sslice::Desc(igs_slice)
    sslice::Desc num_slice 4 TotalPhoton 34205002
                    start  stop   offset    count 
       0 : sslice {     0, 36176,       0, 9999742}
       1 : sslice { 36176, 86770, 9999742, 9999892}
       2 : sslice { 86770,124182,19999634, 9999793}
       3 : sslice {124182,149247,29999427, 4205575}
                    start  stop   offset    count 
     num_slice 4
    2025-06-13 15:47:56.593 INFO  [178540] [QSim::simulate@448]    0 : sslice {     0, 36176,       0, 9999742}

    //qsim.propagate.head idx 1000000 : ctx.evt.index 6 evt.index 6 

    //qsim.propagate.head idx 1000000 : bnc 0 boundary 25 cosTheta 0.62765312 
    //qsim.propagate.head idx 1000000 : mom = np.array([-0.61301464,0.57454115,-0.54232401]) ; lmom = 0.99999988  
    //qsim.propagate.head idx 1000000 : pos = np.array([-12037.18555,-8443.40918,17671.42578]) ; lpos = 22988.35156250 
    //qsim.propagate.head idx 1000000 : nrm = np.array([(-0.99966615,0.02583475,0.00000000]) ; lnrm = 0.99999994  
    //qbnd.fill_state idx 1000000 boundary 25 line 100 wavelength   303.6495 m1_line 103 m2_line 100 su_line 102 s.optical.x 131  
    //qbnd.fill_state idx 1000000 boundary 25 [s.index.x-1](m1_index) 11 [s.index.y-1](m2_index) 10 [s.index.z-1](su_index) 130 
    //qsim.propagate_to_boundary.head idx 1000000 : u_absorption 0.99995255 logf(u_absorption) -0.00004740 absorption_length  9320.5557 absorption_distance   0.441792 
    //qsim.propagate_to_boundary.head idx 1000000 : post = np.array([-12037.18555,-8443.40918,17671.42578, 126.41569]) 
    //qsim.propagate_to_boundary.head idx 1000000 : distance_to_boundary 15669.4287 absorption_distance     0.4418 scattering_distance 105995182080.0000 
    //qsim.propagate_to_boundary.head idx 1000000 : u_scattering     0.8994 u_absorption     1.0000 
    //qsim.propagate_to_boundary.body.BULK_ABSORB idx 1000000 : post = np.array([-12037.45605,-8443.15527,17671.18555, 126.41773]) ; absorb_time_delta = 0.00204170   
    //qsim.propagate.body idx 1000000 bounce 0 command 1 flag 8 s.optical.x 131 s.optical.y 2 
    //qsim.propagate.tail idx 1000000 bounce 0 command 1 flag 8 ctx.s.optical.y(ems) 2 
    2025-06-13 15:47:57.468 INFO  [178540] [QSim::simulate@448]    1 : sslice { 36176, 86770, 9999742, 9999892}
    2025-06-13 15:47:57.984 INFO  [178540] [QSim::simulate@448]    2 : sslice { 86770,124182,19999634, 9999793}
    2025-06-13 15:47:58.772 INFO  [178540] [QSim::simulate@448]    3 : sslice {124182,149247,29999427, 4205575}
    2025-06-13 15:47:59.111 INFO  [178540] [QSim::simulate@492]  eventID 0 tot_dt    2.257604 tot_ph   34205002 tot_ph/M  34.205002 tot_ht    1508171 tot_ht/M   1.508171 tot_ht/tot_ph   0.044092 reset_ YES
    2025-06-13 15:47:59.111 INFO  [178540] [SEvt::save@4189] /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSM


