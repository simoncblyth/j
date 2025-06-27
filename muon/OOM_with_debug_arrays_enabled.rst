muon/OOM_with_debug_arrays_enabled
=====================================


Issue
------

* auto-max-slot does not account for debug arrays
* have doubts on the salloc calc


DONE
-----

* added QSim__ALLOC envvar control to see salloc::desc for successful running, not just when have OOM crashes 

TODO
-----

* get the estimate to get close to actual memory usage
* use the calc to give appropriate auto-max-slot 


OOM Crash
----------

::

    ~/j/muon/muon.sh   ## with default OPTICKS_MAX_SLOT still giving OOM 



::

    2025-06-27 11:17:23.469 INFO  [23575] [QSim::simulate@448]    0 : sslice {       0,    3557,         0,     29823}  0.029823
    2025-06-27 11:17:23.487 ERROR [23575] [QU::_cudaMalloc@272] save salloc record to /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/python3.11
    junotoptask.execute            ERROR: CUDA call (max_slot*max_record*sizeof(sphoton) ) failed with error: 'out of memory' (/home/blyth/opticks/qudarap/QU.cc:265)
    [salloc::desc alloc.size 36 label.size 36
    [salloc.meta
    evt.max_curand:1000000000
    evt.max_slot:262000000
    evt.max_photon:1000000000
    evt.num_photon:29823
    evt.max_curand/M:1000
    evt.max_slot/M:262
    evt.max_photon/M:1000
    evt.num_photon/M:0
    evt.max_record:32
    evt.max_rec:0
    evt.max_seq:1
    evt.max_prd:0
    evt.max_tag:0
    evt.max_flat:0
    evt.num_record:954336
    evt.num_rec:0
    evt.num_seq:29823
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
         [            488         122           4           0]       0.00       0.00 QProp::upload/pp
         [             16           1          16           0]       0.00       0.00 QProp::upload/d_prop
         [             48          12           4           0]       0.00       0.00 QPMT::init_thickness/d_thickness
         [         160096       40024           4           0]       0.00       0.00 QPMT::init_lcqs/d_lcqs
         [         102400       25600           4           0]       0.00       0.00 QPMT::init_s_qescale/d_s_qescale
         [             72           1          72           0]       0.00       0.00 QPMT::init/d_pmt
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             96           1          96           0]       0.00       0.00 QMultiFilm::uploadMultifilmlut
         [            256           1         256           0]       0.00       0.00 QEvent::QEvent/sevent
         [             64           1          64           0]       0.00       0.00 QSim::init.sim
         [        8294400     2073600           4           0]       0.01       0.00 Frame::DeviceAllo:num_pixels
         [      960000000    10000000          96           0]       0.96       0.34 QEvent::setGenstep/device_alloc_genstep_and_seed:quad6/max_genstep
         [     1048000000   262000000           4           0]       1.05       0.37 QEvent::setGenstep/device_alloc_genstep_and_seed:int/max_slot
         [    16768000000   262000000          64           0]      16.77       5.98 QEvent::device_alloc_photon/max_slot*sizeof(sphoton)
         [   261698093056  4089032704          64           0]     261.70      93.30 max_slot*max_record*sizeof(sphoton)

     tot     280482656528                                          280.48
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



    [SEventConfig::AllocEstimate
    [salloc::desc alloc.size 4 label.size 4
    [salloc.meta
    -]salloc.meta

         [           size   num_items sizeof_item       spare]    size_GB    percent label
         [        (bytes)                                    ]   size/1e9            

         [      960000000    10000000          96           0]       0.96       0.17 QEvent::setGenstep/device_alloc_genstep_and_seed:quad6/max_genstep
         [     1048000000   262000000           4           0]       1.05       0.19 QEvent::setGenstep/device_alloc_genstep_and_seed:int/max_slot
         [    16768000000   262000000          64           0]      16.77       3.02 QEvent::device_alloc_photon/max_slot*sizeof(sphoton)
         [   536576000000  8384000000          64           0]     536.58      96.62 QEvent::device_alloc_photon/max_slot*max_record*sizeof(sphoton)

     tot     555352000000                                          555.35
    ]salloc::desc
    ]SEventConfig::AllocEstimate

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2025-06-27 11:17:23,488] p23575 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 23590) exited]

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x0000000000000230 in ?? ()
    (gdb) 




::

    1022 void QEvent::device_alloc_photon()
    1023 {
    1024     LOG_IF(info, LIFECYCLE) ;
    1025     SetAllocMeta( QU::alloc, evt );   // do this first as memory errors likely to happen in following lines
    1026 
    1027     LOG(LEVEL)
    1028         << " evt.max_slot   " << evt->max_slot
    1029         << " evt.max_photon " << evt->max_photon
    1030         << " evt.num_photon " << evt->num_photon
    1031 #ifndef PRODUCTION
    1032         << " evt.num_record " << evt->num_record
    1033         << " evt.num_rec    " << evt->num_rec
    1034         << " evt.num_seq    " << evt->num_seq
    1035         << " evt.num_prd    " << evt->num_prd
    1036         << " evt.num_tag    " << evt->num_tag
    1037         << " evt.num_flat   " << evt->num_flat
    1038 #endif
    1039         ;
    1040 
    1041     evt->photon  = evt->max_slot > 0 ? QU::device_alloc_zero<sphoton>( evt->max_slot, "QEvent::device_alloc_photon/max_slot*sizeof(sphoton)" ) : nullptr ;
    1042 
    1043 #ifndef PRODUCTION
    1044     evt->record  = evt->max_record > 0 ? QU::device_alloc_zero<sphoton>( evt->max_slot * evt->max_record, "max_slot*max_record*sizeof(sphoton)" ) : nullptr ;
    1045     evt->rec     = evt->max_rec    > 0 ? QU::device_alloc_zero<srec>(    evt->max_slot * evt->max_rec   , "max_slot*max_rec*sizeof(srec)"    ) : nullptr ;
    1046     evt->prd     = evt->max_prd    > 0 ? QU::device_alloc_zero<quad2>(   evt->max_slot * evt->max_prd   , "max_slot*max_prd*sizeof(quad2)"    ) : nullptr ;
    1047     evt->seq     = evt->max_seq   == 1 ? QU::device_alloc_zero<sseq>(    evt->max_slot                  , "max_slot*sizeof(sseq)"    ) : nullptr ;
    1048     evt->tag     = evt->max_tag   == 1 ? QU::device_alloc_zero<stag>(    evt->max_slot                  , "max_slot*sizeof(stag)"    ) : nullptr ;
    1049     evt->flat    = evt->max_flat  == 1 ? QU::device_alloc_zero<sflat>(   evt->max_slot                  , "max_slot*sizeof(sflat)"   ) : nullptr ;
    1050 #endif
    1051 
    1052     LOG(LEVEL) << desc() ;
    1053     LOG(LEVEL) << desc_alloc() ;
    1054 }




