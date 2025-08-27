WP_ATM_LPMT_348_extension_to_SPMT_QPMT
=======================================

Following blyth-AtmPmtPosCylinder-point-WP_ATM_LPMT-inwards-not-outwards
----------------------------------------------------------------------------





lcqs array only has CD_LPMT:17612 + WP:2400 = 20012
-----------------------------------------------------

~/o/sysrap/tests/SPMT_test.sh::

    In [5]: s
    Out[5]: 
    s

    CMDLINE:/home/blyth/opticks/sysrap/tests/SPMT_test.py
    s.base:/data1/blyth/tmp/SPMT_test/spmt

      : s.NPFold_index                                     :                 (9,) : 0:17:22.288924 
      : s.cetheta_names                                    :                 (3,) : 0:17:22.289924 
      : s.rindex                                           :     (3, 4, 2, 15, 2) : 0:17:22.289924 
      : s.s_qeshape                                        :           (1, 61, 2) : 0:17:22.289924 
      : s.cetheta                                          :           (3, 10, 2) : 0:17:22.289924 
      : s.jpmt                                             : SUBFOLD 
      : s.qeshape_names                                    :                 (3,) : 0:17:22.289924 
      : s.s_qescale                                        :           (25600, 1) : 0:17:22.289924 
      : s.NPFold_names                                     :                 (0,) : 0:17:22.220924 

      : s.lcqs                                             :           (20012, 2) : 0:17:22.289924 

      : s.thickness                                        :            (3, 4, 1) : 0:17:22.289924 
      : s.cecosth_names                                    :                 (3,) : 0:17:22.289924 
      : s.cecosth                                          :           (3, 10, 2) : 0:17:22.289924 
      : s.qeshape                                          :           (3, 44, 2) : 0:17:22.289924 
      : s.s_qeshape_names                                  :                 (1,) : 0:17:22.289924 

     min_stamp : 2025-08-26 09:41:32.703458 
     max_stamp : 2025-08-26 09:41:32.772458 
     dif_stamp : 0:00:00.069000 
     age_stamp : 0:17:22.220924 




::

    In [8]: s.jpmt.PMTParamData.pmtCat
    Out[8]: 
    array([[    0,     1],
           [    1,     3],
           [    2,     1],
           [    3,     3],
           [    4,     1],
           [    5,     3],
           [    6,     1],
           [    7,     1],
           [    8,     3],
           [    9,     1],
           [   10,     3],
           [   11,     1],
           [   12,     1],
           [   13,     1],
           [   14,     3],
           [   15,     1],
           ...,
           [52737,     0],
           [52738,     0],
           [52739,     3],
           [52740,     3],
           [52741,     0],
           [52742,     0],
           [52743,     3],
           [52744,     0],
           [52745,     3],
           [52746,     0],
           [52747,     0],

           [54000,     3],
           [54001,     0],
           [54002,     0],
           [54003,     0],
           [54004,     0]], shape=(45965, 2), dtype=int32)

::

    In [8]: 17612 + 25600 + 2400 + 348 + 5
    Out[8]: 45965

     



::

     13 jcv CopyNumber::
     14 
     15         014 enum PMTID_OFFSET_DETSIM {
     16          15   kOFFSET_CD_LPMT=0,     kOFFSET_CD_LPMT_END=17612, // CD-LPMT
     17          16   kOFFSET_CD_SPMT=20000, kOFFSET_CD_SPMT_END=45600,  // CD-SPMT
     18          17   kOFFSET_WP_PMT=50000,  kOFFSET_WP_PMT_END=52400,  // WP-LPMT
     19          18   kOFFSET_WP_ATM_LPMT=52400,  kOFFSET_WP_ATM_LPMT_END=52748, //WP-Atmosphere-LPMT
     20          19   kOFFSET_WP_ATM_MPMT=53000,  kOFFSET_WP_ATM_MPMT_END=53600,  //WP-Atmosphere-MPMT (Medium, 8 inch)
     21          20   kOFFSET_WP_WAL_PMT=54000,  kOFFSET_WP_WAL_PMT_END=54005 //WP-Water-attenuation-length
     22          21
     23          22 };



    In [13]: s.jpmt.PMTParamData.pmtCat[17612+25600:17612+25600+2400]   ## WP
    Out[13]: 
    array([[50000,     3],
           [50001,     0],
           [50002,     0],
           [50003,     3],
           [50004,     0],
           [50005,     3],
           ...,
           [52394,     0],
           [52395,     0],
           [52396,     3],
           [52397,     3],
           [52398,     3],
           [52399,     0]], shape=(2400, 2), dtype=int32)

    In [16]: s.jpmt.PMTParamData.pmtCat[17612+25600+2400:17612+25600+2400+348]   ## WP_ATM_LPMT
    Out[16]: 
    array([[52400,     3],
           [52401,     0],
           [52402,     0],
           [52403,     3],
           [52404,     3],
           ...
           [52744,     0],
           [52745,     3],
           [52746,     0],
           [52747,     0]], dtype=int32)


    In [18]: s.jpmt.PMTParamData.pmtCat[17612+25600+2400+348:17612+25600+2400+348+5]   ## WP_WAL_PMT
    Out[18]: 
    array([[54000,     3],
           [54001,     0],
           [54002,     0],
           [54003,     0],
           [54004,     0]], dtype=int32)




After s_pmt.h overhaul : adding WP_ATM_LPMT WP_ATM_MPMT WP_WAL_PMT
---------------------------------------------------------------------

Review s_pmt.h usage
---------------------

::

    (ok) A[blyth@localhost opticks]$ opticks-f s_pmt.h
    ./qudarap/QPMT.hh:#include "s_pmt.h"
    ./qudarap/qpmt.h:#include "s_pmt.h"
    ./sysrap/CMakeLists.txt:    s_pmt.h
    ./sysrap/SPMT.h:#include "s_pmt.h"
    ./sysrap/SPMT.h:    // TODO: get these from s_pmt.h also
    ./sysrap/SPMT.h:qeScale from  _PMTSimParamData::serialize uses s_pmt.h contiguousidx order : CD_LPMT, WP, SPMT
    ./sysrap/SPMT.h:        // outcome depends crucially on the implicit order of lpmtidx from s_pmt.h
    ./sysrap/SPMT.h:        // pmtCat from _PMTParamData uses s_pmt.h "oldcontiguous" order : CD_LPMT, SPMT, WP
    ./sysrap/s_pmt.h:s_pmt.h
    ./sysrap/tests/s_pmt_test.cc:#include "s_pmt.h"
    (ok) A[blyth@localhost opticks]$ 



