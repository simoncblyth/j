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



OPTICKS_MAX_SLOT=M1 shows issue within the 3rd launch
-------------------------------------------------------

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
    0x00000000c6329be0 in ?? ()
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 nvidia-driver-libs-570.124.06-1.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 




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
      7 : sslice { 3086, 3447, 699180,  99743}
      8 : sslice { 3447, 3804, 798923,  99971}
      9 : sslice { 3804, 4161, 898894,  99983}
     10 : sslice { 4161, 4518, 998877,  99764}
     11 : sslice { 4518, 4883,1098641,  99789}
     12 : sslice { 4883, 5242,1198430,  99890}
     13 : sslice { 5242, 5597,1298320,  99839}
     14 : sslice { 5597, 5952,1398159,  99763}
     15 : sslice { 5952, 6304,1497922,  99897}
     16 : sslice { 6304, 6656,1597819,  99893}
     17 : sslice { 6656, 7011,1697712,  99781}
     18 : sslice { 7011, 7370,1797493,  99985}
     19 : sslice { 7370, 7730,1897478,  99758}
     20 : sslice { 7730, 8083,1997236,  99863}
     21 : sslice { 8083, 8440,2097099,  99912}
     22 : sslice { 8440, 8794,2197011,  99841}
     23 : sslice { 8794, 9148,2296852,  99998}
     24 : sslice { 9148, 9499,2396850,  99738}
     25 : sslice { 9499, 9855,2496588,  99994}
     26 : sslice { 9855,10205,2596582,  99889}
     27 : sslice {10205,10558,2696471,  99851}
     28 : sslice {10558,10914,2796322,  99745}
     29 : sslice {10914,11268,2896067,  99752}
     30 : sslice {11268,11630,2995819,  99950}
     31 : sslice {11630,11984,3095769,  99774}
     32 : sslice {11984,12337,3195543,  99702}
     33 : sslice {12337,12688,3295245,  99780}
     34 : sslice {12688,13041,3395025,  99845}
     35 : sslice {13041,13400,3494870,  99855}
     36 : sslice {13400,13756,3594725,  99830}
     37 : sslice {13756,14118,3694555,  99937}
     38 : sslice {14118,14483,3794492,  99948}
     39 : sslice {14483,14839,3894440,  99783}
     40 : sslice {14839,15193,3994223,  99808}
     41 : sslice {15193,15546,4094031,  99998}
     42 : sslice {15546,15900,4194029,  99766}
     43 : sslice {15900,16252,4293795,  99726}
     44 : sslice {16252,16612,4393521,  99798}
     45 : sslice {16612,16967,4493319,  99911}
     46 : sslice {16967,17322,4593230,  99839}
     47 : sslice {17322,17681,4693069,  99788}
     48 : sslice {17681,18034,4792857,  99977}
     49 : sslice {18034,18390,4892834,  99952}
     50 : sslice {18390,18736,4992786,  99776}
     51 : sslice {18736,19082,5092562,  99952}
     52 : sslice {19082,19441,5192514,  99840}
     53 : sslice {19441,19796,5292354,  99810}
     54 : sslice {19796,20153,5392164,  99968}
     55 : sslice {20153,20509,5492132,  99718}
     56 : sslice {20509,20864,5591850,  99891}
     57 : sslice {20864,21216,5691741,  99898}
     58 : sslice {21216,21574,5791639,  99929}
     59 : sslice {21574,21928,5891568,  99957}
     60 : sslice {21928,22283,5991525,  99725}
     61 : sslice {22283,22639,6091250,  99706}
     62 : sslice {22639,22994,6190956,  99950}
     63 : sslice {22994,23351,6290906,  99755}
     64 : sslice {23351,23705,6390661,  99905}
     65 : sslice {23705,24060,6490566,  99839}
     66 : sslice {24060,24410,6590405,  99751}
     67 : sslice {24410,24767,6690156,  99850}
     68 : sslice {24767,25122,6790006,  99763}
     69 : sslice {25122,25476,6889769,  99987}
     70 : sslice {25476,25832,6989756,  99808}
     71 : sslice {25832,26181,7089564,  99779}
     72 : sslice {26181,26535,7189343,  99764}
     73 : sslice {26535,26896,7289107,  99951}
     74 : sslice {26896,27255,7389058,  99837}
     75 : sslice {27255,27606,7488895,  99754}
     76 : sslice {27606,27960,7588649, 100000}
     77 : sslice {27960,28314,7688649,  99882}
     78 : sslice {28314,28668,7788531,  99852}
     79 : sslice {28668,29020,7888383,  99841}
     80 : sslice {29020,29373,7988224,  99871}
     81 : sslice {29373,29728,8088095,  99869}
     82 : sslice {29728,30082,8187964,  99970}
     83 : sslice {30082,30434,8287934,  99715}
     84 : sslice {30434,30788,8387649,  99743}
     85 : sslice {30788,31138,8487392,  99759}
     86 : sslice {31138,31497,8587151,  99844}
     87 : sslice {31497,31856,8686995,  99931}
     88 : sslice {31856,32211,8786926,  99918}
     89 : sslice {32211,32565,8886844,  99811}
     90 : sslice {32565,32928,8986655,  99925}
     91 : sslice {32928,33276,9086580,  99993}
     92 : sslice {33276,33635,9186573,  99876}
     93 : sslice {33635,33984,9286449,  99989}
     94 : sslice {33984,34337,9386438,  99766}
     95 : sslice {34337,34700,9486204,  99898}
     96 : sslice {34700,35052,9586102,  99732}
     97 : sslice {35052,35405,9685834,  99832}
     98 : sslice {35405,35767,9785666,  99835}
     99 : sslice {35767,36126,9885501,  99842}
    100 : sslice {36126,36485,9985343,  99755}
    101 : sslice {36485,36837,10085098,  99725}
    102 : sslice {36837,37194,10184823,  99752}
    103 : sslice {37194,37546,10284575,  99813}
    104 : sslice {37546,37901,10384388,  99950}
    105 : sslice {37901,38262,10484338,  99910}
    106 : sslice {38262,38807,10584248,  99931}
    107 : sslice {38807,39552,10684179,  99952}
    108 : sslice {39552,40199,10784131,  99968}
    109 : sslice {40199,40698,10884099,  99814}
    110 : sslice {40698,41441,10983913,  99936}
    111 : sslice {41441,42277,11083849,  99849}
    112 : sslice {42277,42773,11183698,  99848}
    113 : sslice {42773,43251,11283546,  99879}
    114 : sslice {43251,44150,11383425,  99965}
    115 : sslice {44150,44662,11483390,  99977}
    116 : sslice {44662,45486,11583367,  99872}
    117 : sslice {45486,45973,11683239,  99902}
    118 : sslice {45973,46337,11783141,  99777}
    119 : sslice {46337,46694,11882918,  99850}
    120 : sslice {46694,47310,11982768,  99858}
    121 : sslice {47310,47920,12082626,  99974}
    122 : sslice {47920,48467,12182600,  99798}
    123 : sslice {48467,48929,12282398,  99869}
    124 : sslice {48929,49396,12382267,  99711}
    125 : sslice {49396,49902,12481978,  99909}
    126 : sslice {49902,50795,12581887,  99931}
    127 : sslice {50795,51413,12681818,  99937}
    128 : sslice {51413,52049,12781755,  99868}
    129 : sslice {52049,52665,12881623,  99810}
    130 : sslice {52665,53149,12981433,  99742}
    131 : sslice {53149,53512,13081175,  99743}
    132 : sslice {53512,53902,13180918,  99930}
    133 : sslice {53902,54482,13280848,  99876}
    134 : sslice {54482,55249,13380724,  99777}
    135 : sslice {55249,55988,13480501,  99933}
    136 : sslice {55988,56536,13580434,  99994}
    137 : sslice {56536,57023,13680428,  99995}
    138 : sslice {57023,57875,13780423,  99766}
    139 : sslice {57875,58698,13880189,  99932}
    140 : sslice {58698,59059,13980121,  99986}
    141 : sslice {59059,59711,14080107,  99923}
    142 : sslice {59711,60537,14180030,  99830}
    143 : sslice {60537,60907,14279860,  99964}
    144 : sslice {60907,61278,14379824,  99689}
    145 : sslice {61278,61642,14479513,  99713}
    146 : sslice {61642,62257,14579226,  99947}
    147 : sslice {62257,62689,14679173,  99812}
    148 : sslice {62689,63295,14778985,  99894}
    149 : sslice {63295,63770,14878879,  99865}
    150 : sslice {63770,64243,14978744,  99877}
    151 : sslice {64243,64724,15078621,  99717}
    152 : sslice {64724,65237,15178338,  99994}
    153 : sslice {65237,65620,15278332,  99940}
    154 : sslice {65620,66162,15378272,  99855}
    155 : sslice {66162,66663,15478127,  99978}
    156 : sslice {66663,67231,15578105,  99843}
    157 : sslice {67231,67659,15677948,  99924}
    158 : sslice {67659,68167,15777872,  99991}
    159 : sslice {68167,68583,15877863,  99812}
    160 : sslice {68583,68940,15977675,  99877}
    161 : sslice {68940,69530,16077552,  99929}
    162 : sslice {69530,70045,16177481,  99898}
    163 : sslice {70045,70662,16277379,  99858}
    164 : sslice {70662,71101,16377237,  99793}
    165 : sslice {71101,71470,16477030,  99676}
    166 : sslice {71470,72033,16576706,  99947}
    167 : sslice {72033,72448,16676653,  99923}
    168 : sslice {72448,72931,16776576,  99733}
    169 : sslice {72931,73451,16876309,  99827}
    170 : sslice {73451,73868,16976136,  99853}
    171 : sslice {73868,74236,17075989,  99938}
    172 : sslice {74236,74754,17175927,  99973}
    173 : sslice {74754,75204,17275900,  99932}
    174 : sslice {75204,75629,17375832,  99933}
    175 : sslice {75629,76111,17475765,  99927}
    176 : sslice {76111,76567,17575692,  99752}
    177 : sslice {76567,77084,17675444,  99733}
    178 : sslice {77084,77507,17775177,  99861}
    179 : sslice {77507,77970,17875038,  99997}
    180 : sslice {77970,78373,17975035,  99791}
    181 : sslice {78373,78909,18074826,  99896}
    182 : sslice {78909,79587,18174722,  99881}
    183 : sslice {79587,80131,18274603,  99893}
    184 : sslice {80131,81350,18374496,  99933}
    185 : sslice {81350,81712,18474429,  99984}
    186 : sslice {81712,82068,18574413,  99737}
    187 : sslice {82068,82419,18674150,  99933}
    188 : sslice {82419,82770,18774083,  99810}
    189 : sslice {82770,83129,18873893,  99865}
    190 : sslice {83129,83484,18973758,  99697}
    191 : sslice {83484,83840,19073455,  99724}
    192 : sslice {83840,84197,19173179,  99980}
    193 : sslice {84197,84556,19273159,  99909}
    194 : sslice {84556,84903,19373068,  99753}
    195 : sslice {84903,85251,19472821,  99691}
    196 : sslice {85251,85603,19572512,  99723}
    197 : sslice {85603,85956,19672235,  99924}
    198 : sslice {85956,86310,19772159,  99723}
    199 : sslice {86310,86670,19871882,  99746}
    200 : sslice {86670,87022,19971628,  99966}
    201 : sslice {87022,87379,20071594,  99942}
    202 : sslice {87379,87742,20171536,  99777}
    203 : sslice {87742,88097,20271313,  99811}
    204 : sslice {88097,88449,20371124,  99912}
    205 : sslice {88449,88809,20471036,  99940}
    206 : sslice {88809,89162,20570976,  99876}
    207 : sslice {89162,89512,20670852, 100000}
    208 : sslice {89512,89874,20770852,  99731}
    209 : sslice {89874,90236,20870583,  99965}
    210 : sslice {90236,90591,20970548,  99758}
    211 : sslice {90591,90949,21070306,  99954}
    212 : sslice {90949,91304,21170260,  99801}
    213 : sslice {91304,91657,21270061,  99864}
    214 : sslice {91657,92014,21369925,  99847}
    215 : sslice {92014,92371,21469772,  99947}
    216 : sslice {92371,92729,21569719,  99993}
    217 : sslice {92729,93085,21669712,  99963}
    218 : sslice {93085,93438,21769675,  99875}
    219 : sslice {93438,93803,21869550,  99850}
    220 : sslice {93803,94159,21969400,  99830}
    221 : sslice {94159,94513,22069230,  99861}
    222 : sslice {94513,94873,22169091,  99941}
    223 : sslice {94873,95229,22269032,  99801}
    224 : sslice {95229,95582,22368833,  99861}
    225 : sslice {95582,95936,22468694,  99935}
    226 : sslice {95936,96290,22568629, 100000}
    227 : sslice {96290,96653,22668629,  99695}
    228 : sslice {96653,97010,22768324,  99940}
    229 : sslice {97010,97361,22868264,  99995}
    230 : sslice {97361,97711,22968259,  99927}
    231 : sslice {97711,98073,23068186,  99922}
    232 : sslice {98073,98427,23168108,  99821}
    233 : sslice {98427,98780,23267929,  99705}
    234 : sslice {98780,99133,23367634,  99816}
    235 : sslice {99133,99488,23467450,  99735}
    236 : sslice {99488,99850,23567185,  99761}
    237 : sslice {99850,100203,23666946,  99705}
    238 : sslice {100203,100557,23766651,  99869}
    239 : sslice {100557,100906,23866520,  99701}
    240 : sslice {100906,101255,23966221,  99755}
    241 : sslice {101255,101615,24065976,  99921}
    242 : sslice {101615,101970,24165897,  99987}
    243 : sslice {101970,102318,24265884,  99748}
    244 : sslice {102318,102670,24365632,  99920}
    245 : sslice {102670,103035,24465552,  99846}
    246 : sslice {103035,103392,24565398,  99802}
    247 : sslice {103392,103744,24665200,  99750}
    248 : sslice {103744,104099,24764950,  99827}
    249 : sslice {104099,104459,24864777,  99929}
    250 : sslice {104459,104814,24964706,  99762}
    251 : sslice {104814,105169,25064468,  99754}
    252 : sslice {105169,105537,25164222,  99776}
    253 : sslice {105537,105888,25263998,  99987}
    254 : sslice {105888,106244,25363985,  99983}
    255 : sslice {106244,106594,25463968,  99875}
    256 : sslice {106594,106948,25563843,  99957}
    257 : sslice {106948,107298,25663800,  99971}
    258 : sslice {107298,107656,25763771,  99840}
    259 : sslice {107656,108006,25863611,  99750}
    260 : sslice {108006,108365,25963361,  99855}
    261 : sslice {108365,108722,26063216,  99720}
    262 : sslice {108722,109077,26162936,  99890}
    263 : sslice {109077,109435,26262826,  99874}
    264 : sslice {109435,109788,26362700,  99877}
    265 : sslice {109788,110141,26462577,  99864}
    266 : sslice {110141,110498,26562441,  99842}
    267 : sslice {110498,110855,26662283,  99890}
    268 : sslice {110855,111206,26762173,  99976}
    269 : sslice {111206,111563,26862149,  99858}
    270 : sslice {111563,111918,26962007,  99845}
    271 : sslice {111918,112269,27061852,  99790}
    272 : sslice {112269,112627,27161642,  99961}
    273 : sslice {112627,112987,27261603,  99869}
    274 : sslice {112987,113339,27361472,  99811}
    275 : sslice {113339,113688,27461283,  99790}
    276 : sslice {113688,114046,27561073,  99874}
    277 : sslice {114046,114401,27660947,  99889}
    278 : sslice {114401,114757,27760836,  99779}
    279 : sslice {114757,115119,27860615,  99732}
    280 : sslice {115119,115472,27960347,  99780}
    281 : sslice {115472,115824,28060127,  99883}
    282 : sslice {115824,116178,28160010,  99998}
    283 : sslice {116178,116539,28260008,  99795}
    284 : sslice {116539,116898,28359803,  99760}
    285 : sslice {116898,117251,28459563,  99959}
    286 : sslice {117251,117607,28559522,  99783}
    287 : sslice {117607,117955,28659305,  99979}
    288 : sslice {117955,118314,28759284,  99734}
    289 : sslice {118314,118671,28859018,  99786}
    290 : sslice {118671,119023,28958804,  99807}
    291 : sslice {119023,119394,29058611,  99911}
    292 : sslice {119394,120003,29158522,  99711}
    293 : sslice {120003,120791,29258233, 100000}
    294 : sslice {120791,121478,29358233,  99786}
    295 : sslice {121478,122143,29458019,  99695}
    296 : sslice {122143,122535,29557714,  99944}
    297 : sslice {122535,123213,29657658,  99910}
    298 : sslice {123213,123646,29757568,  99970}
    299 : sslice {123646,124002,29857538,  99855}
    300 : sslice {124002,124504,29957393,  99947}
    301 : sslice {124504,124947,30057340,  99805}
    302 : sslice {124947,125476,30157145,  99924}
    303 : sslice {125476,125928,30257069,  99870}
    304 : sslice {125928,126445,30356939,  99940}
    305 : sslice {126445,126841,30456879,  99976}
    306 : sslice {126841,127390,30556855,  99970}
    307 : sslice {127390,127774,30656825,  99801}
    308 : sslice {127774,128158,30756626,  99673}
    309 : sslice {128158,128518,30856299,  99765}
    310 : sslice {128518,129139,30956064,  99933}
    311 : sslice {129139,129621,31055997,  99899}
    312 : sslice {129621,130236,31155896,  99913}
    313 : sslice {130236,130714,31255809,  99815}
    314 : sslice {130714,131280,31355624,  99871}
    315 : sslice {131280,131772,31455495,  99895}
    316 : sslice {131772,132242,31555390,  99972}
    317 : sslice {132242,132735,31655362,  99904}
    318 : sslice {132735,133282,31755266,  99967}
    319 : sslice {133282,133865,31855233,  99883}
    320 : sslice {133865,134798,31955116,  99857}
    321 : sslice {134798,135659,32054973,  99915}
    322 : sslice {135659,136517,32154888,  99718}
    323 : sslice {136517,137276,32254606,  99743}
    324 : sslice {137276,137964,32354349,  99766}
    325 : sslice {137964,138458,32454115,  99965}
    326 : sslice {138458,139160,32554080,  99996}
    327 : sslice {139160,139871,32654076,  99835}
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
    2025-06-12 21:55:51.963 INFO  [1795697] [QSim::simulate@446] sslice {    0,  950,      0,  99816}
    2025-06-12 21:55:51.971 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:51.971 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99816 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:51.975 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0037
    2025-06-12 21:55:51.975 INFO  [1795697] [QSim::simulate@446] sslice {  950, 1304,  99816,  99867}
    2025-06-12 21:55:51.983 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:51.983 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99867 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:51.988 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0045
    2025-06-12 21:55:51.988 INFO  [1795697] [QSim::simulate@446] sslice { 1304, 1666, 199683,  99807}
    2025-06-12 21:55:51.996 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:51.996 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99807 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.002 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0062
    2025-06-12 21:55:52.002 INFO  [1795697] [QSim::simulate@446] sslice { 1666, 2019, 299490,  99880}
    2025-06-12 21:55:52.010 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.010 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99880 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.015 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0049
    2025-06-12 21:55:52.015 INFO  [1795697] [QSim::simulate@446] sslice { 2019, 2377, 399370,  99859}
    2025-06-12 21:55:52.023 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.023 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99859 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.029 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0058
    2025-06-12 21:55:52.029 INFO  [1795697] [QSim::simulate@446] sslice { 2377, 2730, 499229,  99954}
    2025-06-12 21:55:52.037 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.037 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99954 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.042 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0055
    2025-06-12 21:55:52.042 INFO  [1795697] [QSim::simulate@446] sslice { 2730, 3086, 599183,  99997}
    2025-06-12 21:55:52.050 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.050 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99997 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.055 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0053
    2025-06-12 21:55:52.055 INFO  [1795697] [QSim::simulate@446] sslice { 3086, 3447, 699180,  99743}
    2025-06-12 21:55:52.064 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.064 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99743 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.069 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0047
    2025-06-12 21:55:52.069 INFO  [1795697] [QSim::simulate@446] sslice { 3447, 3804, 798923,  99971}
    2025-06-12 21:55:52.076 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.076 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99971 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.081 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0045
    2025-06-12 21:55:52.081 INFO  [1795697] [QSim::simulate@446] sslice { 3804, 4161, 898894,  99983}
    2025-06-12 21:55:52.089 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.089 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99983 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.095 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0057
    2025-06-12 21:55:52.095 INFO  [1795697] [QSim::simulate@446] sslice { 4161, 4518, 998877,  99764}
    2025-06-12 21:55:52.103 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.103 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99764 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.108 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0052
    2025-06-12 21:55:52.108 INFO  [1795697] [QSim::simulate@446] sslice { 4518, 4883,1098641,  99789}
    2025-06-12 21:55:52.116 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.116 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99789 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.121 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0051
    2025-06-12 21:55:52.121 INFO  [1795697] [QSim::simulate@446] sslice { 4883, 5242,1198430,  99890}
    2025-06-12 21:55:52.129 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.129 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99890 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.134 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0047
    2025-06-12 21:55:52.134 INFO  [1795697] [QSim::simulate@446] sslice { 5242, 5597,1298320,  99839}
    2025-06-12 21:55:52.142 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.142 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99839 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.147 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0051
    2025-06-12 21:55:52.147 INFO  [1795697] [QSim::simulate@446] sslice { 5597, 5952,1398159,  99763}
    2025-06-12 21:55:52.155 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.155 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99763 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.161 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0059
    2025-06-12 21:55:52.161 INFO  [1795697] [QSim::simulate@446] sslice { 5952, 6304,1497922,  99897}
    2025-06-12 21:55:52.169 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.169 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99897 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.173 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0045
    2025-06-12 21:55:52.173 INFO  [1795697] [QSim::simulate@446] sslice { 6304, 6656,1597819,  99893}
    2025-06-12 21:55:52.181 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.181 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99893 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.186 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0047
    2025-06-12 21:55:52.186 INFO  [1795697] [QSim::simulate@446] sslice { 6656, 7011,1697712,  99781}
    2025-06-12 21:55:52.195 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.195 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99781 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.197 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0022
    2025-06-12 21:55:52.197 INFO  [1795697] [QSim::simulate@446] sslice { 7011, 7370,1797493,  99985}
    2025-06-12 21:55:52.205 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.205 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99985 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.206 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0019
    2025-06-12 21:55:52.207 INFO  [1795697] [QSim::simulate@446] sslice { 7370, 7730,1897478,  99758}
    2025-06-12 21:55:52.214 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.214 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99758 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.216 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0019
    2025-06-12 21:55:52.216 INFO  [1795697] [QSim::simulate@446] sslice { 7730, 8083,1997236,  99863}
    2025-06-12 21:55:52.225 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.225 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99863 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    2025-06-12 21:55:52.236 INFO  [1795697] [CSGOptiX::launch@1053]  (params.width, params.height, params.depth) ( 1920,1080,1) 0.0114
    2025-06-12 21:55:52.237 INFO  [1795697] [QSim::simulate@446] sslice { 8083, 8440,2097099,  99912}
    2025-06-12 21:55:52.244 INFO  [1795697] [CSGOptiX::prepareParamSimulate@927] 
    2025-06-12 21:55:52.244 INFO  [1795697] [CSGOptiX::launch@1013]  raygenmode 2 SRG::Name(raygenmode) simulate width 99912 height 1 depth 1 DEBUG_SKIP_LAUNCH NO 
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/home/blyth/opticks/CSGOptiX/CSGOptiX.cc:1034)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-12 21:55:52,287] p1795697 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 1795710) exited]

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00000000066fc4e0 in ?? ()
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 nvidia-driver-libs-570.124.06-1.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 




Slicing small runs into NPFold::can_concat issue
---------------------------------------------------

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




