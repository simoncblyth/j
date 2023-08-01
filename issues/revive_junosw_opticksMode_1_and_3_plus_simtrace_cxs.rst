revive_junosw_opticksMode_1_and_3_plus_simtrace_cxs
=======================================================

The goal is junosw opticksMode 1 and 3 initially with input photons.  
But getting there will be faster with more standalone tests 
like simtrace or things like the below initially.:

High Level Progress
---------------------

1. DONE : summarized the PMTSimParamData NPFold into a few arrays in SPMT.h 
2. DONE : checked  SPMT.h by comparison with JPMT get_stackspec scans
3. DONE : revived j/Layr/LayrTest 
4. DONE : NumPy compare scans from LayrTest.sh and SPMT_test.sh, small SPMT dev at critical angle 
5. DONE : generalize qpmt/QPMT/QPMTTest for lpmtid lookups based off the full SPMT info
6. DONE : qpmt/QPMT Stack AOI scanning based off SPMT.h full data, like SPMT_test but on GPU  
7. DONE : getting mat/sur/bnd/optical into new workflow as qpmt needs to change optical 
8. DONE : Bringing C4CustomART::doIt to GPU, by integrating qpmt with new CSGFoundry special surface enum 
9. WIP : review SEvt usage with opticksMode:1 and opticksMode:2 consider how to do both at once in opticksMode:3




TODO : commit junosw changes (mostly SPMT prep) into another branch and MR
------------------------------------------------------------------------------

::

    epsilon:issues blyth$ jo
    /Users/blyth/junotop/junosw
    On branch blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping
    Your branch is up-to-date with 'origin/blyth-add-options-to-skip-expensive-stick-geom-and-toptask-json-dumping'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
        modified:   Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.cc
        Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ 







DONE : getting mat/sur/bnd/optical into new workflow as qpmt needs to change optical 
-------------------------------------------------------------------------------------

* ~/opticks/notes/issues/mat_sur_bnd_optical_direct_without_GGeo_X4.rst

* Water RAYLEIGH : old Geant4 special case strikes again 
* note that vetoWater has no RAYLEIGH and as not called "Water" is not special cased : possible junosw bug 
* GROUPVEL looks like the Geant4 calc has changed : need to use new one 


DONE : regenerate the geom with ntds2_noxj to get X4/GGeo oldmat oldsur for comparison
----------------------------------------------------------------------------------------

It was necessary to C4 bump to 0.1.5 in order for Opticks to compile. 
Motivation is to get the oldmat oldsur for checking with new workflow
versions of these::

    N[blyth@localhost SSim]$ l
    total 13360
        4 drwxr-xr-x. 6 blyth blyth     4096 Jul  2 23:45 stree
        0 drwxr-xr-x. 4 blyth blyth      273 Jul  2 23:45 .
        4 -rw-rw-r--. 1 blyth blyth      109 Jul  2 23:45 icdf_meta.txt
        4 -rw-rw-r--. 1 blyth blyth        3 Jul  2 23:45 icdf_names.txt
      100 -rw-rw-r--. 1 blyth blyth    98432 Jul  2 23:45 icdf.npy
        4 -rw-rw-r--. 1 blyth blyth       56 Jul  2 23:45 NPFold_index.txt
        4 -rw-rw-r--. 1 blyth blyth     1490 Jul  2 23:45 oldsur_names.txt
        4 -rw-rw-r--. 1 blyth blyth      179 Jul  2 23:45 oldmat_names.txt
     2188 -rw-rw-r--. 1 blyth blyth  2240512 Jul  2 23:45 oldsur.npy
      952 -rw-rw-r--. 1 blyth blyth   974208 Jul  2 23:45 oldmat.npy
        4 -rw-rw-r--. 1 blyth blyth     3520 Jul  2 23:45 optical.npy
        4 -rw-rw-r--. 1 blyth blyth       69 Jul  2 23:45 bnd_meta.txt
        4 -rw-rw-r--. 1 blyth blyth     2734 Jul  2 23:45 bnd_names.txt
    10084 -rw-rw-r--. 1 blyth blyth 10325392 Jul  2 23:45 bnd.npy
        0 drwxr-xr-x. 5 blyth blyth       91 Jun 16 02:34 jpmt
        0 drwxr-xr-x. 3 blyth blyth      190 Jun  7 21:17 ..
    N[blyth@localhost SSim]$ pwd
    /home/blyth/.opticks/GEOM/V1J009/CSGFoundry/SSim
    N[blyth@localhost SSim]$ 

::

    epsilon:~ blyth$ t ntds2_noxj
    ntds2_noxj () 
    { 
        OPTICKS_INTEGRATION_MODE=2 ntds_noxj
    }
    epsilon:~ blyth$ t ntds_noxj
    ntds_noxj () 
    { 
        local gpfx=V;
        GPFX=${GPFX:-$gpfx};
        export EVTMAX=1;
        NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds
    }
    epsilon:~ blyth$ 

    epsilon:~ blyth$ ntds2_noxj_getgeom
    == /Users/blyth/opticks/bin/rsync.sh odir .opticks/GEOM/V1J009 exists
    BASH_SOURCE                    : /Users/blyth/opticks/bin/rsync.sh 
    xdir                           : .opticks/GEOM/V1J009/ 
    from                           : P:.opticks/GEOM/V1J009/ 
    to                             : /Users/blyth/.opticks/GEOM/V1J009/ 





DONE : Bringing C4CustomART::doIt to GPU, by integrating qpmt with new CSGFoundry special surface enum
--------------------------------------------------------------------------------------------------------


DONE : LayrTest standardize layout etc.. to match SPMT and QPMT
----------------------------------------------------------------

Hmm QPMT/qscan not following the standard spec + stack:(art,comp,ll) layout::

    epsilon:Layr blyth$ l /tmp/QPMTTest/qscan/
    total 776
     56 -rw-r--r--   1 blyth  wheel   26192 Jun 27 10:28 lpmtid_ARTE.npy
    256 -rw-r--r--   1 blyth  wheel  104384 Jun 27 10:28 lpmtid_ART.npy
     40 -rw-r--r--   1 blyth  wheel   16880 Jun 27 10:28 lpmtcat_qeshape.npy
    384 -rw-r--r--   1 blyth  wheel  134144 Jun 27 10:28 lpmtcat_rindex.npy
      8 -rw-r--r--   1 blyth  wheel     164 Jun 27 10:28 lpmtid.npy
      8 -rw-r--r--   1 blyth  wheel     852 Jun 27 10:28 mct_domain.npy
     16 -rw-r--r--   1 blyth  wheel    5712 Jun 27 10:28 energy_eV_domain.npy
      8 -rw-r--r--   1 blyth  wheel     117 Jun 27 10:28 NPFold_index.txt

This is standard::

    epsilon:Layr blyth$ l /tmp/blyth/opticks/LayrTest/4/scan__R12860__cpu_thr_double/
    total 2704
       8 -rw-r--r--  1 blyth  wheel     256 Jun 27 12:09 spec.npy
     256 -rw-r--r--  1 blyth  wheel  115328 Jun 27 12:09 art.npy
       8 -rw-r--r--  1 blyth  wheel     227 Jun 27 12:09 art_meta.txt
    1920 -rw-r--r--  1 blyth  wheel  921744 Jun 27 12:09 ll.npy
     512 -rw-r--r--  1 blyth  wheel  230528 Jun 27 12:09 comp.npy
       0 drwxr-xr-x  7 blyth  wheel     224 Jun 27 12:09 ..
       0 drwxr-xr-x  7 blyth  wheel     224 Jun 27 11:37 .

    epsilon:Layr blyth$ l /tmp/SPMT_test/sscan/
    total 2912
     120 -rw-r--r--   1 blyth  wheel   57744 Jun 27 10:13 art.npy
       8 -rw-r--r--   1 blyth  wheel      66 Jun 27 10:13 art_meta.txt
     256 -rw-r--r--   1 blyth  wheel  115344 Jun 27 10:13 comp.npy
    1024 -rw-r--r--   1 blyth  wheel  460944 Jun 27 10:13 ll.npy
    1280 -rw-r--r--   1 blyth  wheel  633744 Jun 27 10:13 stack.npy
     120 -rw-r--r--   1 blyth  wheel   57744 Jun 27 10:13 spec.npy
      32 -rw-r--r--   1 blyth  wheel   14544 Jun 27 10:13 extra.npy
      32 -rw-r--r--   1 blyth  wheel   14544 Jun 27 10:13 ARTE.npy
      32 -rw-r--r--   1 blyth  wheel   14544 Jun 27 10:13 args.npy
       8 -rw-r--r--   1 blyth  wheel      71 Jun 27 10:13 NPFold_index.txt
       0 drwxr-xr-x   6 blyth  wheel     192 Jun 27 10:13 ..



DONE : Fixed bug : uninitialized ART values
---------------------------------------------

::

    In [21]: ts
    Out[21]: 
    CFLayrTest
     a :          R12860 : scan__R12860__cpu_thr_double 
     b :          R12860 : scan__R12860__cpu_thr_float 
     c :          R12860 : scan__R12860__gpu_thr_double 
     d :          R12860 : scan__R12860__gpu_thr_float 
     e :          R12860 : sscan 

    In [22]: a.f.art[0]
    Out[22]: 
    array([[  0.627,   0.627,   0.627,   0.   ],
           [  0.045,   0.045,   0.045,   0.   ],
           [  0.328,   0.328,   0.328, 440.   ],
           [  0.   , 440.   ,   1.   ,  -1.   ]])

    In [23]: b.f.art[0]
    Out[23]: 
    array([[ 6.272e-01,  6.272e-01,  6.272e-01,  4.591e-41],
           [ 4.470e-02,  4.470e-02,  4.470e-02,  1.401e-45],
           [ 3.281e-01,  3.281e-01,  3.281e-01,  4.591e-41],
           [-1.764e+22,  4.400e+02,  1.000e+00, -1.000e+00]], dtype=float32)

    In [24]: c.f.art[0]
    Out[24]: 
    array([[  0.627,   0.627,   0.627,     nan],
           [  0.045,   0.045,   0.045,     nan],
           [  0.328,   0.328,   0.328,     nan],
           [    nan, 440.   ,   1.   ,  -1.   ]])

    In [25]: d.f.art[0]
    Out[25]: 
    array([[ 6.272e-01,  6.272e-01,  6.272e-01,  1.845e-31],
           [ 4.470e-02,  4.470e-02,  4.470e-02,  5.266e+10],
           [ 3.281e-01,  3.281e-01,  3.281e-01,  1.617e-36],
           [ 1.934e+00,  4.400e+02,  1.000e+00, -1.000e+00]], dtype=float32)

    In [26]: e.f.art.squeeze()[0]
    Out[26]: 
    array([[  0.627,   0.627,   0.627,   0.627],
           [  0.045,   0.045,   0.045,   0.045],
           [  0.328,   0.328,   0.328,   0.328],
           [  0.   , 440.   ,   1.   ,  -1.   ]], dtype=float32)

    In [27]:                      



DONE : Debug cudaMemCopy crash
---------------------------------

"Binary" search investigating the kernel, shows
smoking gun : the pmtcat lookup is going wrong 
for anything other than lpmtid 0::


    //qpmt::get_lpmtid_stackspec lpmtid 0 lpmtcat 1 
    //qpmt::get_lpmtid_stackspec lpmtid 0 lpmtcat 1 
    //qpmt::get_lpmtid_stackspec lpmtid 0 lpmtcat 1 
    //qpmt::get_lpmtid_stackspec lpmtid 0 lpmtcat 1 
    //qpmt::get_lpmtid_stackspec lpmtid 0 lpmtcat 1 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 


    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 10 lpmtcat -268500993 
    //qpmt::get_lpmtid_stackspec lpmtid 55 lpmtcat -1 
    //qpmt::get_lpmtid_stackspec lpmtid 55 lpmtcat -1 
    //qpmt::get_lpmtid_stackspec lpmtid 55 lpmtcat -1 


    In [5]: t.src_lcqs
    Out[5]: array([[         1, 1065565820]], dtype=int32)

    In [6]: t.src_lcqs.shape
    Out[6]: (1, 2)


DONE : qpmt/QPMT TMM Stack calc AOI scanning based off SPMT.h full data, like SPMT_test but on GPU
------------------------------------------------------------------------------------------------------

* see qudarap/QPMTTest.sh 

DONE : compare QPMTTest GPU AOI scans with others using LayrTest.sh comparison machinery 
-------------------------------------------------------------------------------------------


DONE : Bring C4CustomART::doIt to GPU, by integrating qpmt with new CSGFoundry special surface enum
------------------------------------------------------------------------------------------------------


DONE : remove stackNormal instance
------------------------------------

After rationalizing the serialization layout:

+---+--------+--------+--------+--------+
|   |  x     |  y     |  z     |  w     |
+===+========+========+========+========+
| 0 |  A_s   |  A_p   |  A_av  |  A     |
+---+--------+--------+--------+--------+
| 1 |  R_s   |  R_p   |  R_av  |  R     |
+---+--------+--------+--------+--------+
| 2 |  T_s   |  T_p   |  T_av  |  T     |
+---+--------+--------+--------+--------+
| 3 |  SF    |  wl    | ART_av |  mct   |
+---+--------+--------+--------+--------+


    st ; ./SPMT_scan.sh ana::

    In [1]: nart[0]
    Out[1]: 
    array([[  0.627,   0.627,   0.627,   0.627],
           [  0.045,   0.045,   0.045,   0.045],
           [  0.328,   0.328,   0.328,   0.328],
           [  0.   , 440.   ,   1.   ,  -1.   ]], dtype=float32)

    In [2]: art[0]
    Out[2]: 
    array([[  0.627,   0.627,   0.627,   0.627],
           [  0.045,   0.045,   0.045,   0.045],
           [  0.328,   0.328,   0.328,   0.328],
           [  0.   , 440.   ,   1.   ,  -1.   ]], dtype=float32)

    In [3]: np.all( nart[0] == art[0] )
    Out[3]: True






DONE : qpmt/QPMT/QPMTTest generalization for lpmtid info lookups based off the full SPMT info
-----------------------------------------------------------------------------------------------

::

    103 template<typename T>
    104 inline QPMT_METHOD void qpmt<T>::get_lpmtid_stackspec( quad4& spec, int lpmtid, T energy_eV ) const
    105 {           
    106             
    107     const int& lpmtcat = i_lcqs[lpmtid*2+0] ;
    108         
    109     // printf("//qpmt::get_lpmtid_stackspec lpmtid %d lpmtcat %d \n", lpmtid, lpmtcat );  
    110 
    111     const T& qe_scale = lcqs[lpmtid*2+1] ;
    112     const T qe = qeshape_prop->interpolate( lpmtcat, energy_eV ) ;
    113     const T _qe = qe_scale*qe ;
    114 
    115     spec.q0.i.w = lpmtcat ; 
    116     spec.q1.f.w = qe_scale ;
    117     spec.q2.f.w = qe ;
    118     spec.q3.f.w = _qe ; 
    119     
    120     get_lpmtcat_stackspec( spec, lpmtcat, energy_eV );
    121 }   

::

    In [15]: t.lpmtid_stackspec[:,:,0,3].view(np.int32)
    Out[15]: 
    array([[1, 1, 1, 1, 1, ..., 1, 1, 1, 1, 1],
           [1, 1, 1, 1, 1, ..., 1, 1, 1, 1, 1],
           [2, 2, 2, 2, 2, ..., 2, 2, 2, 2, 2],
           [1, 1, 1, 1, 1, ..., 1, 1, 1, 1, 1],
           [2, 2, 2, 2, 2, ..., 2, 2, 2, 2, 2]], dtype=int32)

    In [16]: t.lpmtid_stackspec[:,:,1,3]
    Out[16]: 
    array([[1.025, 1.025, 1.025, 1.025, 1.025, ..., 1.025, 1.025, 1.025, 1.025, 1.025],
           [1.027, 1.027, 1.027, 1.027, 1.027, ..., 1.027, 1.027, 1.027, 1.027, 1.027],
           [1.287, 1.287, 1.287, 1.287, 1.287, ..., 1.287, 1.287, 1.287, 1.287, 1.287],
           [1.041, 1.041, 1.041, 1.041, 1.041, ..., 1.041, 1.041, 1.041, 1.041, 1.041],
           [1.338, 1.338, 1.338, 1.338, 1.338, ..., 1.338, 1.338, 1.338, 1.338, 1.338]], dtype=float32)

    In [17]: t.lpmtid_stackspec[:,:,2,3]
    Out[17]: 
    array([[0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.014, 0.014, 0.014, 0.014, 0.014, ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.014, 0.014, 0.014, 0.014, 0.014, ..., 0.   , 0.   , 0.   , 0.   , 0.   ]], dtype=float32)

    In [18]: t.lpmtid_stackspec[:,:,3,3]
    Out[18]: 
    array([[0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.018, 0.018, 0.018, 0.018, 0.018, ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.   , 0.   , 0.   , 0.   , 0.   , ..., 0.   , 0.   , 0.   , 0.   , 0.   ],
           [0.019, 0.019, 0.019, 0.019, 0.019, ..., 0.   , 0.   , 0.   , 0.   , 0.   ]], dtype=float32)



    In [19]: np.max(t.lpmtid_stackspec[:,:,0,3].view(np.int32), axis=1)
    Out[19]: array([1, 1, 2, 1, 2], dtype=int32)

    In [20]: np.max(t.lpmtid_stackspec[:,:,1,3], axis=1)
    Out[20]: array([1.025, 1.027, 1.287, 1.041, 1.338], dtype=float32)

    In [21]: np.max(t.lpmtid_stackspec[:,:,2,3], axis=1)
    Out[21]: array([0.356, 0.356, 0.288, 0.356, 0.288], dtype=float32)

    In [22]: np.max(t.lpmtid_stackspec[:,:,3,3], axis=1)
    Out[22]: array([0.365, 0.366, 0.371, 0.37 , 0.385], dtype=float32)



    In [23]: np.argmax(t.lpmtid_stackspec[:,:,0,3].view(np.int32), axis=1)
    Out[23]: array([0, 0, 0, 0, 0])

    In [24]: np.argmax(t.lpmtid_stackspec[:,:,1,3], axis=1)
    Out[24]: array([0, 0, 0, 0, 0])

    In [25]: np.argmax(t.lpmtid_stackspec[:,:,2,3], axis=1)
    Out[25]: array([163, 163, 163, 163, 163])

    In [26]: np.argmax(t.lpmtid_stackspec[:,:,3,3], axis=1)
    Out[26]: array([163, 163, 163, 163, 163])


::

    In [32]: t.lpmtid
    Out[32]: array([    0,    10,   100,  1000, 10000], dtype=int32)


Those 5 lpmtid are all lpmt 1,2 no 0, so find some::

    In [30]: np.where( t.src_lcqs[:,0] == 0 )[0]
    Out[30]: array([   55,    98,   137,   267,   368, ..., 17255, 17327, 17504, 17526, 17537])

    In [31]: np.where( t.src_lcqs[:,0] == 0 )[0].shape
    Out[31]: (2720,)



DONE : LayrTest.sh vs SPMT_test.sh comparison
-----------------------------------------------

The last ART row (xx,yy,zz,ww) is not used in LayrTest::  

    a_art = a.f.art.squeeze()
    e_art = e.f.art.squeeze()

    In [13]: np.abs(a_art[:,:3] - e_art[:,:3]).max()
    Out[13]: 6.361931981246904e-05


    In [15]: a_art[0]
    Out[15]: 
    array([[  0.045,   0.045,   0.328,   0.328],
           [  0.627,   0.627,   0.045,   0.328],
           [  0.627,   1.   , 440.   ,  -1.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ]])

    In [16]: e_art[0]
    Out[16]: 
    array([[  0.045,   0.045,   0.328,   0.328],
           [  0.627,   0.627,   0.045,   0.328],
           [  0.627,   1.   , 440.   ,  -1.   ],
           [  0.627,   0.045,   0.328,   0.   ]], dtype=float32)


SPMT.h::

     847     const float S = E_s2 ;
     848     const float P = one - S ;
     849 
     850     const float T = S*stack.art.T_s + P*stack.art.T_p ;  // matched with TransCoeff see sysrap/tests/stmm_vs_sboundary_test.cc
     851     const float R = S*stack.art.R_s + P*stack.art.R_p ;
     852     const float A = S*stack.art.A_s + P*stack.art.A_p ;
     853     //const float A1 = one - (T+R);  // note that A1 matches A 
     854 
     855     stack.art.xx = A ;
     856     stack.art.yy = R ;
     857     stack.art.zz = T ;
     858     stack.art.ww = S ;


DONE : investigate comp deviation close to critical angle 
----------------------------------------------------------

::

    epsilon:Layr blyth$ ./LayrTest.sh ana
    ./LayrTest.sh : WITH_THRUST config
    ./LayrTest.sh : WITH_STACKSPEC config
    ## ts = LayrTestSet(symbol="ts") 
     ts.xbase     : /tmp/SPMT_test/get_ARTE 
     ts.xnames    : ['xscan'] 
     ts.ALL_NAMES : ['scan__R12860__cpu_thr_double', 'scan__R12860__cpu_thr_float', 'scan__R12860__gpu_thr_double', 'scan__R12860__gpu_thr_float', 'xscan'] 
    LayrTest.py:88: RuntimeWarning: invalid value encountered in arcsin
      critical = np.array( [np.arcsin(nr_frac[0]), np.pi - np.arcsin(nr_frac[1]) ] )  # one of these will be np.nan
    kludge the label of is_extra 
    ## repr(ts) 
    CFLayrTest
     a :          R12860 : scan__R12860__cpu_thr_double 
     b :          R12860 : scan__R12860__cpu_thr_float 
     c :          R12860 : scan__R12860__gpu_thr_double 
     d :          R12860 : scan__R12860__gpu_thr_float 
     e :          R12860 : xscan 
    ## cf_ab  = CF(a,b,excl)   # excl: 0.05 
    ## repr(cf_ab) 
    CF(a,b,0.05) : scan__R12860__cpu_thr_double vs scan__R12860__cpu_thr_float 
    LayrTest<double,4> WITH_THRUST  name scan__R12860__cpu_thr_double ni 900 wl 440 mct[0] -1 mct[ni-1] 1
    LayrTest<float,4> WITH_THRUST  name scan__R12860__cpu_thr_float ni 900 wl 440 mct[0] -1 mct[ni-1] 1
            ll :   7.33e-05 :   7.11e-05 :  -7.33e-05
          comp :   4.83e-05 :   4.83e-05 :  -4.65e-05
           art :    6.1e-06 :    6.1e-06 :   -6.1e-06
    ## ts.select(pmtcat)  # pmtcat: R12860  
    ## pmtcat:R12860 tt:5 t:e : SPMT.title 
    ## ARTPlot 
    ## rst = ts.cf_table(tt, pmtcat, excl=excl) # excl 0.05 
    ## rst 
    +------------------------------+----------+----------+----------+----------+----------+
    |          R12860 art\comp 0.05|     a:ctd|     b:ctf|     c:gtd|     d:gtf|        e:|
    +==============================+==========+==========+==========+==========+==========+
    |                         a:ctd|         0| 4.829e-05| 7.445e-14| 4.829e-05| 0.0003496|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         b:ctf| 6.101e-06|         0| 4.829e-05| 3.977e-05|  0.000318|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         c:gtd| 1.321e-14| 6.101e-06|         0| 4.829e-05| 0.0003496|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         d:gtf| 1.523e-06| 7.451e-06| 1.523e-06|         0| 0.0003578|
    +------------------------------+----------+----------+----------+----------+----------+
    |                            e:| 6.362e-05| 5.752e-05| 6.362e-05| 6.497e-05|         0|
    +------------------------------+----------+----------+----------+----------+----------+


    In [1]: be = CF(b,e,0.05)

    In [2]: be 
    Out[2]: 
    CF(b,e,0.05) : scan__R12860__cpu_thr_float vs xscan 
    LayrTest<float,4> WITH_THRUST  name scan__R12860__cpu_thr_float ni 900 wl 440 mct[0] -1 mct[ni-1] 1
    SPMT.brief
            ll :   0.000412 :   0.000385 :  -0.000412
          comp :   0.000318 :    4.3e-05 :  -0.000318
           art :   5.75e-05 :   5.75e-05 :  -5.75e-05

    In [10]: np.where( be.comp < -3e-4 )
    Out[10]: (array([212]), array([1]), array([3]), array([0]))

    In [11]: np.where( be.comp < -2e-4 )
    Out[11]: (array([212]), array([1]), array([3]), array([0]))

    In [12]: np.where( be.comp < -1e-4 )
    Out[12]: (array([212, 212, 213]), array([1, 1, 1]), array([1, 3, 3]), array([1, 0, 0]))

    In [8]: be.comp.shape
    Out[8]: (872, 4, 4, 2)

    In [6]: be.comp[:,:,:,0].min()
    Out[6]: -0.00031801313          

    In [7]: be.comp[:,:,:,1].min()
    Out[7]: -0.00010895729

    In [12]: be.mct[np.where( be.comp < -1e-4 )[0]]   
    Out[12]: array([-0.738, -0.738, -0.736], dtype=float32)   ## minus_cos_theta where deviation is largest 

    In [15]: np.arccos( -be.mct[np.where( be.comp < -1e-4 )[0]]  )  ## convert minus_cos_theta into theta 
    Out[15]: array([0.741, 0.741, 0.744], dtype=float32)

    In [14]: b.critical            ## discontinuities close to critical angle implicated in deviation
    Out[14]: array([0.74,  nan])   ## problem is the kinks, no resolution is enough at critical angle   


    In [17]: e.critical[0]
    Out[17]: 0.7404550313949585

    In [18]: b.critical[0]
    Out[18]: 0.7404559254646301

    In [1]: a.critical_mct 
    Out[1]: -0.7381610892515559

    In [2]: e.critical_mct
    Out[2]: -0.7381616601198697

    In [3]: b.critical_mct
    Out[3]: -0.7381610569588344

    In [1]: a.critical_theta_degrees
    Out[1]: 42.42499670195976

    In [2]: e.critical_theta_degrees
    Out[2]: 42.42494821815799


DONE : After excluding critical, brings SPMT_test into line with LayrTest
------------------------------------------------------------------------------

BUT: this doesnt answer why SPMT_test has small deviation from LayrTest 
at critical angle. Possibly there is small property difference 
between old NP_PROP_BASE and the new SPMT data ? 

But useful nevertherless to know where the small deviation is concentrated. 

::

    epsilon:Layr blyth$ ./LayrTest.sh ana
    ..

    ## repr(ts) 
    CFLayrTest
     a :          R12860 : scan__R12860__cpu_thr_double 
     b :          R12860 : scan__R12860__cpu_thr_float 
     c :          R12860 : scan__R12860__gpu_thr_double 
     d :          R12860 : scan__R12860__gpu_thr_float 
     e :          R12860 : xscan 
    ## cf_ab  = CF(a,b,excl)   # excl: 0.05 
    ## repr(cf_ab) 
    CF(a,b,0.05,exclude_pole=True,exclude_critical=True) : scan__R12860__cpu_thr_double vs scan__R12860__cpu_thr_float 
    LayrTest<double,4> WITH_THRUST  name scan__R12860__cpu_thr_double ni 900 wl 440 mct[0] -1 mct[ni-1] 1
    LayrTest<float,4> WITH_THRUST  name scan__R12860__cpu_thr_float ni 900 wl 440 mct[0] -1 mct[ni-1] 1
            ll :   7.33e-05 :   7.11e-05 :  -7.33e-05
          comp :   4.83e-05 :   4.83e-05 :  -4.65e-05
           art :   9.32e-07 :   9.02e-07 :  -9.32e-07
    mct pole/critical/sel 28/43/829 
    ## ts.select(pmtcat)  # pmtcat: R12860  
    ## pmtcat:R12860 tt:5 t:e : SPMT.title 
    ## ARTPlot 
    ## tab, rst = ts.cf_table(tt, pmtcat, excl=excl) # excl 0.05 
    ## rst 
    +------------------------------+----------+----------+----------+----------+----------+
    |          R12860 art\comp 0.05|     a:ctd|     b:ctf|     c:gtd|     d:gtf|        e:|
    +==============================+==========+==========+==========+==========+==========+
    |                         a:ctd|         0| 4.829e-05| 1.066e-14| 4.829e-05| 8.644e-05|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         b:ctf| 9.317e-07|         0| 4.829e-05| 5.722e-06| 4.578e-05|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         c:gtd| 1.582e-15| 9.317e-07|         0| 4.829e-05| 8.644e-05|
    +------------------------------+----------+----------+----------+----------+----------+
    |                         d:gtf| 7.958e-07| 8.792e-07| 7.958e-07|         0| 4.196e-05|
    +------------------------------+----------+----------+----------+----------+----------+
    |                            e:| 2.956e-06| 3.159e-06| 2.956e-06|  3.07e-06|         0|
    +------------------------------+----------+----------+----------+----------+----------+


DONE : work out how to scan the polarization fraction with SPMT::get_ARTE using E_s2 : S-pol fraction
------------------------------------------------------------------------------------------------------------

::

     mom       nrm
         +--s--+
          \    |
           \   | 
     pol.   \  |  
             \ | 
              \|
     ----------0-------

     OldMomentum.cross(theRecoveredNormal) 
         transverse direction, eg out the page 
         (OldMomentum, theRecoveredNoraml are normalized, 
         so magnitude will be sine of angle between mom and nrm) 

     (OldPolarization*OldMomentum.cross(theRecoveredNormal)) 
         dot product between the OldPolarization and transverse direction
         is expressing the S polarization fraction
         (OldPolarization is normalized so the magnitude will be 
          cos(angle-between-pol-and-transverse)*sin(angle-between-mom-and-nrm)

         * hmm pulling out "pol_dot_mom_cross_nrm" argument 
           would provide some splitting 

     mct is OldMomentum*theRecoveredNormal (both those are normalized)

* dot product with a cross product is the determinant of the three vectors 


::

    271     const double _si = stack.ll[0].st.real() ;

    /// mct = do
    ///     this : sqrt(1.f - mct*mct )

    272     double E_s2 = _si > 0. ? (OldPolarization*OldMomentum.cross(theRecoveredNormal))/_si : 0. ;
    273     E_s2 *= E_s2;
    274 
    275     // E_s2 : S-vs-P power fraction : signs make no difference as squared
    276     // E_s2 matches E1_perp*E1_perp see sysrap/tests/stmm_vs_sboundary_test.cc 



DONE : Encapsulate the Stack ART API further with SPMT::get_ARTE 
-------------------------------------------------------------------

HMM looks rather S/P polarizartion entangled, difficult to pull off API

* yes but using whacky arg "dot_pol_cross_mom_nrm" enables the encapsulation
* testing with SPMT_test.sh 

::

    788 inline void SPMT::get_ARTE(
             SPMTData& pd, 
             int pmtid, 
             float wavelength_nm, 
             float minus_cos_theta, 
             float dot_pol_cross_mom_nrm ) const


::


    259     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    263 
    264     std::array<double,16> a_spec ;
    265     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    266     StackSpec<double,4> spec ;
    267     spec.import( a_spec );
    268 
    269     Stack<double,4> stack(wavelength_nm, minus_cos_theta, spec );
    270 
    271     const double _si = stack.ll[0].st.real() ;
    272     double E_s2 = _si > 0. ? (OldPolarization*OldMomentum.cross(theRecoveredNormal))/_si : 0. ;
    273     E_s2 *= E_s2;
    274 
    275     // E_s2 : S-vs-P power fraction : signs make no difference as squared
    276     // E_s2 matches E1_perp*E1_perp see sysrap/tests/stmm_vs_sboundary_test.cc 
    277 
    278     double one = 1.0 ;
    279     double S = E_s2 ;
    280     double P = one - S ;
    281 
    282     double T = S*stack.art.T_s + P*stack.art.T_p ;  // matched with TransCoeff see sysrap/tests/stmm_vs_sboundary_test.cc
    283     double R = S*stack.art.R_s + P*stack.art.R_p ;
    284     double A = S*stack.art.A_s + P*stack.art.A_p ;
    285     //double A1 = one - (T+R);  // note that A1 matches A 
    286 
    287     theAbsorption = A ;
    288     theReflectivity  = R/(1.-A) ;
    289     theTransmittance = T/(1.-A)  ;
    290 


Because the stackNormal has no S/P worries, getting theEfficiency could be split off more easily::

    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;

    291     // stackNormal is not flipped (as minus_cos_theta is fixed at -1.) presumably this is due to _qe definition
    292     Stack<double,4> stackNormal(wavelength_nm, -1. , spec );
    293 
    294     // at normal incidence S/P distinction is meaningless, and the values converge anyhow : so no polarization worries here
    295     //double An = stackNormal.art.A ; 
    296     double An = one - (stackNormal.art.T + stackNormal.art.R) ;
    297     double escape_fac = _qe/An;
    298     theEfficiency = escape_fac ;
    299 



Issue 1 : Getting all SR off the PMT : as expected : need to "Custom4" special case the surface name
------------------------------------------------------------------------------------------------------

::

    epsilon:CSGOptiX blyth$ ./cxs_min.sh ana
    CSGFoundry.CFBase returning [/Users/blyth/.opticks/GEOM/V1J009], note:[via GEOM] 
    GLOBAL:0 MODE:3
    INFO:opticks.ana.pvplt:SEvt.Load NEVT:0 
    INFO:opticks.ana.fold:Fold.Load args ['/Users/blyth/.opticks/GEOM/V1J009/CSGOptiXSMTest/ALL/000'] quiet:1
    INFO:opticks.ana.pvplt:init_ee with_photon_meta:0 with_ff:0
    INFO:opticks.ana.pvplt:SEvt.__init__  symbol e pid -1 opt  off [0. 0. 0.] 
    SEvt symbol e pid -1 opt  off [0. 0. 0.] e.f.base /Users/blyth/.opticks/GEOM/V1J009/CSGOptiXSMTest/ALL/000 
    INFO:opticks.ana.pvplt:minimal_qtab : np.c_[nq,iq,uq][oq][:10] 
    [[b'746' b'185' b'TO BT BT BT BT SA                                                                               ']
     [b'734' b'1736' b'TO BT BT BT BT SR BT BT BT BT BT BT AB                                                          ']
     [b'372' b'1666' b'TO BT BT BT BT SR BT BT BT BT AB                                                                ']
     [b'227' b'2189' b'TO BT BT BT BT SR BT BT BT BT BT BT SC AB                                                       ']
     [b'91' b'319' b'TO BT BT BT BT SR BR BR BR BR BR BR BR BT DR AB                                                 ']
     [b'90' b'1641' b'TO BT BT BT BT SR BT BT BT BT BT AB                                                             ']
     [b'86' b'2198' b'TO BT BT BT BT SR BT BT BT BT BT BT SC SC AB                                                    ']
     [b'84' b'0' b'TO BT BT BR BR BR BR BT SA                                                                      ']
     [b'80' b'26' b'TO BT BT AB                                                                                     ']
     [b'69' b'349' b'TO BT BT BT BT SR BR BR BR BR BR BR BR BT SA                                                    ']]





DONE : sort out CSGOptiX API for minimal render/simtrace/simulate
--------------------------------------------------------------------

While the code is minimal all these are using full CSGFoundry geometry::

    epsilon:CSGOptiX blyth$ l tests/CSGOptiX*MTest.cc
    8 -rw-r--r--  1 blyth  staff  205 Jun 13 16:29 tests/CSGOptiXTMTest.cc
    8 -rw-r--r--  1 blyth  staff  255 Jun 13 13:56 tests/CSGOptiXSMTest.cc
    8 -rw-r--r--  1 blyth  staff  343 Jun 13 13:55 tests/CSGOptiXRMTest.cc
    epsilon:CSGOptiX blyth$ 

    epsilon:CSGOptiX blyth$ l *_min.sh 
    8 -rwxr-xr-x  1 blyth  staff  2336 Jun 13 17:23 cxt_min.sh
    8 -rwxr-xr-x  1 blyth  staff  2701 Jun 13 16:33 cxs_min.sh
    8 -rwxr-xr-x  1 blyth  staff  3659 Jun 13 13:56 cxr_min.sh
    epsilon:CSGOptiX blyth$ 



DONE : rerun geom creation with additional SSim/jpmt RINDEX data
-------------------------------------------------------------------

::

    ntds_noxj()
    {
       #local gpfx=R           # R:Release builds of junosw+custom4   
       local gpfx=V          # V:Debug builds of junosw+custom4  
       GPFX=${GPFX:-$gpfx}    # need to match with j/ntds/ntds.sh  AGEOM, BGEOM

       export EVTMAX=1

       NOXJ=1 GEOM=${GPFX}1J009 OPTICKS_INTEGRATION_MODE=${OPTICKS_INTEGRATION_MODE:-0} ntds 

       ## HMM: INPUT PHOTONS WILL NOT WORK IN OPTICKS MODE 0 HOW AND WHERE TO RAISE AN ERROR FOR THAT ?
    }

    ntds0_noxj(){ OPTICKS_INTEGRATION_MODE=0 ntds_noxj ; }
    ntds2_noxj(){ OPTICKS_INTEGRATION_MODE=2 ntds_noxj ; }


DONE : grab geom with additional SSim/jpmt RINDEX data
--------------------------------------------------------

::

    epsilon:junosw blyth$ t ntds2_noxj_getgeom
    ntds2_noxj_getgeom () 
    { 
        source $OPTICKS_HOME/bin/rsync.sh .opticks/GEOM/${GEOM:-V1J009};
        : j/jx.bash
    }

DONE : Check standalone PMT data access
-----------------------------------------

::

    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh
    Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh


DONE : Convert FewPMT geometry from PMTSim into CSGFoundry 
-------------------------------------------------------------

For shakedown of Custom4 equivalent GPU side prefer using simpler FewPMT geometry. 
So start by saving a FewPMT geometry into CSGFoundry and running the three minimals on it 
FewPMT running was done in u4 using PMTSim. 

But u4 does not depend on CSG so cannot convert there. 
So get a G4CX test to do the PV to CSGFoundry conversion. 


* :doc:`G4CXOpticks_setGeometry_Test_unexpected_GGeo_writing`


DONE : Fix undersized FewPMT box
------------------------------------

Suspect the Rock_solid, Water_solid box too small in Y::

    ELV=t6,7 ./cxr_min.sh 

::

    339     <box lunit="mm" name="Water_solid0x7eee30" x="711.11111111108" y="400" z="400"/>
    345     <box lunit="mm" name="Rock_solid0x7eeca0" x="746.666666666634" y="420" z="420"/>
    346   </solids>


Eyeballing size of outer Rock in XZ directions "MODE=2 ./cxt_min.sh ana"::

    In [2]: 214*2 
    Out[2]: 428

    In [3]: 373*2
    Out[3]: 746


HMM doing a XY simtrace at Z=0 would confirm. Probably the Y needs the aspect 1.7777 too. 

* YEP: confirmed, needs more room in Y avoid clipping


Cycle on the conversion whilst dumping from U4VolumeMaker::

    gxt
    ./G4CXOpticks_setGeometry_Test.sh

FewPMT.sh boxscale use the aspect for both x and y::

    epsilon:opticks blyth$ git diff
    diff --git a/u4/tests/FewPMT.sh b/u4/tests/FewPMT.sh
    index 43ca769f3..cb0f79605 100644
    --- a/u4/tests/FewPMT.sh
    +++ b/u4/tests/FewPMT.sh
    @@ -111,7 +111,7 @@ if [ "$LAYOUT" == "one_pmt" ]; then
     
        export U4VolumeMaker_WrapRockWater_Rock_HALFSIDE=210
        export U4VolumeMaker_WrapRockWater_Water_HALFSIDE=200
    -   export U4VolumeMaker_WrapRockWater_BOXSCALE=$aspect,1,1
    +   export U4VolumeMaker_WrapRockWater_BOXSCALE=$aspect,$aspect,1
     
     elif [ "$LAYOUT" == "two_pmt" ]; then 


    N[blyth@localhost tests]$ grep box ~/.opticks/GEOM/FewPMT/origin.gdml
        <box lunit="mm" name="Water_solid0x7eee30" x="711.11111111108" y="711.11111111108" z="400"/>
        <box lunit="mm" name="Rock_solid0x7eeca0" x="746.666666666634" y="746.666666666634" z="420"/>




DONE : cxr_min/cxt_min/cxs_min all working with the FewPMT geometry 
---------------------------------------------------------------------

DONE : Review CPU C4CustomART and work out how to do it standalone and then on GPU
--------------------------------------------------------------------------------------------


DONE : provisioned the C4CustomART calculation using SPMT.h, see SPMT_test.sh 
---------------------------------------------------------------------------------

* see PMTSimParamData_test.sh 
* see PMTAccessor_test.sh : it does standalone calc from persisted jpmt 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh 

  * python load the persisted PMTSimParamData 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh 

  * _PMTSimParamData::Load from "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt/PMTSimParamData"
  * test a few simple queries against the loaded PMTSimParamData 

* Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTAccessor_test.sh

  * PMTAccessor::Load from "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt" 
  * standalone CPU use of PMTAccessor to do the stack calc  

* qudarap/tests/QPMTTest.sh 

  * JPMT NP_PROP_BASE loading rindex and thickness
  * on GPU interpolation check using QPMT
  * TODO: extend this to do the full calculation based off the PMTAccessor NPFold data, not JPMT

    * form a (17612,4) array (pmtcat,qescale,spare,pmtidx) 
    * 1st reproduce the JPMT.rindex JPMT.thickness arrays frm PMTAccessor NPFold
    * HMM: dont want to use junosw within opticks so start from NPFold ?



DONE : generalise qsim::propagate for special surfaces
---------------------------------------------------------

* devise optical enumeration to handle boundary/ordinarySurface/specialSurface/...
* use the enumeration in the translation to CSGFoundry

qsim.h::

    1461     if( command == BOUNDARY )
    1462     {
    1463         command = ctx.s.optical.x == 0 ?
    1464                                       propagate_at_boundary( flag, rng, ctx )
    1465                                   :
    1466                                       propagate_at_surface( flag, rng, ctx )
    1467                                   ; 
    1468 
    1469 
    1470     }



**CPU kickoff**

c4/C4OpBoundaryProcess.cc::

     502             //[OpticalSurface.mpt.CustomPrefix
     503             if( OpticalSurfaceName0 == '@' || OpticalSurfaceName0 == '#' )  // only customize specially named OpticalSurfaces 
     504             {
     505                 if( m_custom_art->local_z(aTrack) < 0. ) // lower hemi : No customization, standard boundary  
     506                 {
     507                     m_custom_status = 'Z' ;
     508                 }
     509                 else if( OpticalSurfaceName0 == '@') //  upper hemi with name starting @ : MultiFilm ART transmit thru into PMT
     510                 {
     511                     m_custom_status = 'Y' ;
     512 
     513                     m_custom_art->doIt(aTrack, aStep) ;
     514 


c4/C4CustomART.h 

* connector between c4/C4OpBoundaryProcess and the Stack calculation 

::

    251 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    252 {
    253     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    254     G4double energy = thePhotonMomentum ;
    255     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    256     G4double energy_eV = energy/CLHEP::eV ;
    257     G4double wavelength_nm = wavelength/CLHEP::nm ;
    258 
    259     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );

    ///  THIS STILL THE OLD SLOW WAY : CAN DO IT MUCH FASTER   

    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;
    262     // following the old junoPMTOpticalModel with "backwards" _qe always zero 

    ///  HMM: WOULD BE MORE GENERAL TO MAKE CHOICE OF BACKWARDS QE ZERO OR NOT INSIDE ACCESSOR ?

    263 
    264     std::array<double,16> a_spec ;
    265     accessor->get_stackspec(a_spec, pmtcat, energy_eV );

    /// providing layer thicknesses, complex refractive indices for that energy 

    266     StackSpec<double,4> spec ;
    267     spec.import( a_spec );

    /// import just copying into different type, could be avoided 

    268 
    269     Stack<double,4> stack(wavelength_nm, minus_cos_theta, spec );
    270 


jcv DsPhysConsOptical::

    367 #include "IPMTSimParamSvc/IPMTSimParamSvc.h"
    368 #include "PMTSimParamSvc/PMTSimParamData.h"
    369 #include "PMTSimParamSvc/PMTAccessor.h"
    370 
    371 C4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    372 {
    373     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    374 
    375     if(psps_ptr.invalid()) 
    376     {
    377         std::cout << "invalid" << std::endl ;
    378         return nullptr ; 
    379     }   
    380 
    381     IPMTSimParamSvc* ipsps = psps_ptr.data();
    382     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    383 
    384     C4IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    385     C4OpBoundaryProcess* boundproc = new C4OpBoundaryProcess(accessor) ;
    386     std::cout << "DsPhysConsOptical::CreateCustomG4OpBoundaryProcess" << std::endl ;
    387 
    388     return boundproc ;
    389 }   


PMTAccessor
-------------

::

    epsilon:PMTSimParamData blyth$ jcv PMTAccessor
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h




DONE : Check PMTSimParamData is complete and can provide standalone StackSpec creation
------------------------------------------------------------------------------------------

DONE : cleaned up the test::

   /Users/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh


Accessor is built on top of PMTSimParamData which should be persisted. Is it complete::

    epsilon:jpmt blyth$ pwd
    /Users/blyth/.opticks/GEOM/V1J009/CSGFoundry/SSim/jpmt
    epsilon:jpmt blyth$ cd PMTSimParamData/
    epsilon:PMTSimParamData blyth$ l
    total 10992
       0 drwxr-xr-x  17 blyth  staff      544 Jun  7 14:17 .
       0 drwxr-xr-x   9 blyth  staff      288 Jun  7 14:17 CONST
       0 drwxr-xr-x   8 blyth  staff      256 Jun  7 14:17 QEshape
       0 drwxr-xr-x   6 blyth  staff      192 Jun  7 14:17 MPT
       8 -rw-rw-r--   1 blyth  staff      116 Jun  7 14:17 NPFold_index.txt
       8 -rw-rw-r--   1 blyth  staff      144 Jun  7 14:17 pmtTotal.npy
       8 -rw-rw-r--   1 blyth  staff       48 Jun  7 14:17 pmtTotal_names.txt
    3736 -rw-rw-r--   1 blyth  staff  1440992 Jun  7 14:17 lpmtData.npy
       8 -rw-rw-r--   1 blyth  staff       26 Jun  7 14:17 spmtData_meta.txt
     144 -rw-rw-r--   1 blyth  staff    70576 Jun  7 14:17 lpmtCat.npy
       8 -rw-rw-r--   1 blyth  staff       21 Jun  7 14:17 lpmtCat_meta.txt
     720 -rw-rw-r--   1 blyth  staff   365024 Jun  7 14:17 pmtCat.npy
     360 -rw-rw-r--   1 blyth  staff   182576 Jun  7 14:17 pmtCatVec.npy
    4912 -rw-rw-r--   1 blyth  staff  2048128 Jun  7 14:17 spmtData.npy
       0 drwxr-xr-x   5 blyth  staff      160 Jun  7 14:17 ..
     360 -rw-rw-r--   1 blyth  staff   182576 Jun  7 14:17 pmtID.npy
     720 -rw-rw-r--   1 blyth  staff   365024 Jun  7 14:17 qeScale.npy

    epsilon:PMTSimParamData blyth$ l ../PMTParamData/
    total 688
      0 drwxr-xr-x  4 blyth  staff     128 Jun  7 14:17 .
      0 drwxr-xr-x  5 blyth  staff     160 Jun  7 14:17 ..
      8 -rw-rw-r--  1 blyth  staff      11 Jun  7 14:17 NPFold_index.txt
    680 -rw-rw-r--  1 blyth  staff  345824 Jun  7 14:17 pmtCat.npy
    epsilon:PMTSimParamData blyth$ 

    epsilon:SSim blyth$ cd jpmt/PMTSimParamData/MPT
    epsilon:MPT blyth$ l
    total 8
    0 drwxr-xr-x  17 blyth  staff  544 Jun  7 14:17 ..
    0 drwxr-xr-x   6 blyth  staff  192 Jun  7 14:17 .
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 001
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 003
    0 drwxr-xr-x   7 blyth  staff  224 Jun  7 14:17 000
    8 -rw-rw-r--   1 blyth  staff   12 Jun  7 14:17 NPFold_index.txt
    epsilon:MPT blyth$ l 000/
    total 40
    0 drwxr-xr-x  6 blyth  staff  192 Jun  7 14:17 ..
    0 drwxr-xr-x  7 blyth  staff  224 Jun  7 14:17 .
    8 -rw-rw-r--  1 blyth  staff  160 Jun  7 14:17 ARC_KINDEX.npy
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 ARC_RINDEX.npy
    8 -rw-rw-r--  1 blyth  staff   60 Jun  7 14:17 NPFold_index.txt
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 PHC_KINDEX.npy
    8 -rw-rw-r--  1 blyth  staff  352 Jun  7 14:17 PHC_RINDEX.npy


jcv _PMTSimParamData::

    198 inline NPFold* _PMTSimParamData::serialize() const
    199 {
    200     NP* pmtID = NPX::ArrayFromVec<int, int>(data.m_all_pmtID) ;
    201     NP* qeScale = NPX::ArrayFromVec<double,double>(data.m_all_pmtID_qe_scale) ;
    202     NP* lpmtCat = NPX::ArrayFromMap<int, int>(data.m_map_pmt_category) ;
    203     NP* pmtCat = NPX::ArrayFromDiscoMap<int>(data.m_all_pmt_category) ;
    204     NP* pmtCatVec = NPX::ArrayFromVec<int, int>(data.m_all_pmt_catvec) ;
    205 
    206     NP* spmtData = NPX::ArrayFromMap<double, PmtSimData_SPMT>(data.pd_map_SPMT) ;
    207     NP* lpmtData = NPX::ArrayFromVec<double, PmtSimData_LPMT>(data.pd_vector) ;
    208     NP* pmtTotal = serialize_pmtTotal();
    209 
    210     NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT);
    211     NPFold* CONST = NPFold::Serialize_MIMSD(data.m_PMT_CONST);
    212     NPFold* QEshape = serialize_QEshape() ;
    213 


Q: where do the 0,1,3 keys come from and why no 2?
A: Those are PMTCategory enums with no entry for 2 kPMT_HZC


jcv PMTCategory::

     06 enum PMT_CATEGORY {
      7   kPMT_Unknown=-1,
      8   kPMT_NNVT,
      9   kPMT_Hamamatsu,
     10   kPMT_HZC,
     11   kPMT_NNVT_HighQE
     12 };
     13 
     14 
     15 struct PMTCategory
     16 {
     17    static constexpr const char* Unknown     = "kPMT_Unknown" ;
     18    static constexpr const char* NNVT        = "kPMT_NNVT" ;
     19    static constexpr const char* Hamamatsu   = "kPMT_Hamamatsu" ;
     20    static constexpr const char* HZC         = "kPMT_HZC" ;
     21    static constexpr const char* NNVT_HighQE = "kPMT_NNVT_HighQE" ;


        

::

    :set nowrap

    epsilon:issues blyth$ jgr m_PMT_MPT
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    std::map<int, std::map<std::string, G4MaterialPropertyVector*>>& MPT = data.m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    NPFold* MPT = S4MaterialPropertyVector::Serialize_MIMSV(data.m_PMT_MPT); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    S4MaterialPropertyVector::Import_MIMSV( data.m_PMT_MPT, MPT ); 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h:    ss << S4MaterialPropertyVector::Desc_MIMSV(data.m_PMT_MPT)   << std::endl ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:    std::map<int, std::map<std::string, G4MaterialPropertyVector*>> m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h:    return m_PMT_MPT.at(pmtcat).at(prop_name) ;
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            if(data.m_PMT_MPT.count(cat) == 0)           continue ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            if(data.m_PMT_MPT.at(cat).count(qname) == 0) continue ; 
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h:            mpva[cat] = data.m_PMT_MPT.at(cat).at(qname) ;  
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h:  std::map<int, std::map<std::string, G4MaterialPropertyVector*>>& m_PMT_MPT;
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    m_PMT_MPT(m_data.m_PMT_MPT),
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_RINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_KINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_RINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_KINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["ARC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["ARC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["PHC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT]["PHC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["ARC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.ARC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["ARC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.ARC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["PHC_RINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.PHC_RINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    helper_pmt_mpt(m_PMT_MPT[kPMT_NNVT_HighQE]["PHC_KINDEX"], mcgt.data(), "PMTProperty.NNVTMCP_HiQE.PHC_KINDEX");
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    auto iter1 = m_PMT_MPT.find(pmtcat);
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:    assert(iter1 != m_PMT_MPT.end());
    epsilon:junosw blyth$ 





SSim/jpmt vs SSim/juno ? jpmt is the standard now 
------------------------------------------------------

:: 

    epsilon:junosw blyth$ jgr SSim
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:#include "SSim.hh"
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::Create();                    // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::AddSubfold("jpmt", jpmt );
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:        SSim::AddSubfold("jpmt", jpmt );  // needs to be before SaveGeometry 
    Binary file ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/.PMTSimParamData_test.sh.swp matches
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh:    base=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData
    ./Detector/Geometry/Geometry/tests/PMTParamData_test.sh:    base=$HOME/.opticks/GEOM/J005/CSGFoundry/SSim/juno/PMTParamData
    epsilon:junosw blyth$ 


::

     16 void LSExpDetectorConstruction_Opticks::Setup(
     17           int opticksMode,
     18           const G4VPhysicalVolume* world,
     19           const G4VSensitiveDetector* sd,
     20           PMTParamData* ppd,
     21           PMTSimParamData* psd,
     22           NPFold* pmtscan
     23           )
     24 {   
     25     bool opticksMode_valid = opticksMode > -1 && opticksMode <= 3 ;  
     26     LOG_IF(fatal, !opticksMode_valid ) << " unexpected opticksMode " << opticksMode ;
     27     assert( opticksMode_valid );
     28     
     29     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     30     
     31     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     32     if( opticksMode == 0 )
     33     {   
     34         SEvt::HighLevelCreateOrReuse();    // U4RecorderAnaMgr not active in opticksMode:0 
     35         SSim::Create();                    // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
     36         SSim::AddSubfold("jpmt", jpmt );
     37     }
     38     else if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
     39     {   
     40         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ;
     41         G4CXOpticks::SetGeometry(world) ; 
     42         SSim::AddSubfold("jpmt", jpmt );  // needs to be before SaveGeometry 
     43         G4CXOpticks::SaveGeometry();
     44     }
     45     LOG(info) << "] WITH_G4CXOPTICKS " ;
     46 }



DONE : incorporate PyrexRINDEX VacuumRINDEX into SerializePMT
--------------------------------------------------------------- 


::

     48 NPFold* LSExpDetectorConstruction_Opticks::SerializePMT(
     49           PMTParamData* ppd,
     50           PMTSimParamData* psd,
     51           NPFold* pmtscan
     52      )
     53 {
     54     _PMTParamData    _ppd(*ppd) ;
     55     _PMTSimParamData _psd(*psd) ;
     56 
     57     NPFold* j = new NPFold ;
     58     j->add_subfold( "PMTParamData",    _ppd.serialize() );
     59     j->add_subfold( "PMTSimParamData", _psd.serialize() );
     60     if(pmtscan) j->add_subfold( "PMTScan",  pmtscan );
     61 
     62     return j ;
     63 }

::

    118 inline const PMTAccessor* PMTAccessor::Load(const char* base )
    119 {   
    120     const PMTSimParamData* data = LoadData(base) ;
    121     assert( data ); 
    122     return Create(data);
    123 }
    124 

::

      4 int main(int argc, char** argv)
      5 {
      6     const char* pathspec = "$HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt/PMTSimParamData" ;
      7     const PMTAccessor* pmt = PMTAccessor::Load(pathspec) ;
      8     if( pmt == nullptr )


Can PMTAccessor::Load from one directory up::

    $HOME/.opticks/GEOM/$GEOM/CSGFoundry/SSim/jpmt

Thence can include the RINDEX in another subfold. 



What is missing with JPMT approach ?
---------------------------------------

See c4/C4CustomART::doIt getting pmtcat from pmtid and getting qe for (pmtid,energy)::

    260     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    261     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;

::

    210 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    211 {   
    212     return data->get_pmtid_qe(pmtid, energy) ;
    213 }

    134 inline int PMTSimParamData::get_pmtcat(int pmtid) const
    135 {
    136     int idx = get_pmtContiguousIndex(pmtid);
    137     return m_all_pmt_catvec[idx];
    138 }

    177 inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const
    178 {
    179     int idx = get_pmtContiguousIndex(pmtid) ;
    180     int cat = m_all_pmt_catvec[idx] ;
    181     double qe = get_pmtcat_qe(cat, energy);   // interpolation on m_QEshape_.. MPV
    182     double qe_scale = m_all_pmtID_qe_scale[idx] ;
    183     qe *= qe_scale ;


    184     assert(qe > 0 && qe < 1);
    185     return qe ;
    186 }


    188 inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const
    189 {
    190     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    191     double qe = vec->Value(energy);
    192     return qe;
    193 }

    245 inline G4MaterialPropertyVector* PMTSimParamData::get_pmtcat_qe_vs_energy(int pmtcat) const
    246 {
    247     G4MaterialPropertyVector * vec = 0 ;
    248     switch(pmtcat)
    249     {
    250         case kPMT_Unknown:     vec = m_QEshape_WP_PMT    ; break ;
    251         case kPMT_NNVT:        vec = m_QEshape_NNVT      ; break ;
    252         case kPMT_Hamamatsu:   vec = m_QEshape_R12860    ; break ;
    253         case kPMT_HZC:         vec = m_QEshape_HZC       ; break ;
    254         case kPMT_NNVT_HighQE: vec = m_QEshape_NNVT_HiQE ; break ;
    255     }

   
Whats missing is contiguous pmt index array with category and qe_scale.


DONE : Skip WPMTs SPMTs from the SPMT.h arrays needed for QPMT ? YES
----------------------------------------------------------------------

Only pmtid from NNVT,NNVTHiQE,HAMA PMTs will be arriving into 
QPMT because only those have the special "@/#" surface names prefix.  
So can skip WPMTs and SPMTs. 

HMM: that restriction means the pmtid is already contiguous so 
can directly use it to lookup pmtCat and qeScale. 


::

    /Users/blyth/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py


                                          t.pmtID.shape  : (45612, 1) 
                                         t.pmtCat.shape  : (45612, 2) 
                                      t.pmtCatVec.shape  : (45612, 1) 
                                        t.qeScale.shape  : (45612, 1) 
                                         t.lpmtCat.shape : (17612, 1) 
                                        t.lpmtData.shape : (20012, 9) 

                     np.all(t.pmtID[:,0]==t.pmtCat[:,0]) : True 
                 np.all(t.pmtCatVec[:,0]==t.pmtCat[:,1]) : True 
      np.all(t.pmtCat[:len(t.lpmtCat),1]==t.lpmtCat[:,0]) : True 

      np.all(t.lpmtData[:len(t.lpmtCat),0].view(np.int64)==t.pmtID[:len(t.lpmtCat),0]) : True 






TODO : revive SEvt in opticksMode:1 + 3
---------------------------------------------


Reviving CPU+GPU (opticksMode:3) running after a long hiatus. 

* HMM: maybe need separate SEvt instances ? 
* TODO: review SEvt usage in opticksMode:1 (GPU only) 
* TODO: review SEvt usage in opticksMode:2 (CPU only) 


ntds3_noxj::

    .idx 7 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    2023-07-28 21:49:38.013 FATAL [424508] [SEvt::hostside_running_resize@1315]  NOT-is_self_provider SEvt::descProvider provider: 0x16e9a6590 that address is: another object
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1322: void SEvt::hostside_running_resize(): Assertion `is_self_provider' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #4  0x00007fffcf32b801 in SEvt::hostside_running_resize (this=0xb56690) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1322
    #5  0x00007fffcf32c088 in SEvt::beginPhoton (this=0xb56690, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1501
    #6  0x00007fffd296e036 in U4Recorder::PreUserTrackingAction_Optical (this=0xb2d300, track=0x7fff17989710)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:314
    #7  0x00007fffd296d7f0 in U4Recorder::PreUserTrackingAction (this=0xb2d300, track=0x7fff17989710) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:230
    #8  0x00007fffcdc8d8a8 in U4RecorderAnaMgr::PreUserTrackingAction (this=0x93f2e0, trk=0x7fff17989710)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:33
    #9  0x00007fffce6cbd39 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffce8dab00 <MgrOfAnaElem::instance()::s_mgr>, trk=0x7fff17989710)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:60
    #10 0x00007fffcdfbb779 in LSExpTrackingAction::PreUserTrackingAction (this=0x597a030, aTrack=0x7fff17989710)




Same assert in opticksMode:1::

    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 1 eventID 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    2023-07-28 22:50:29.534 FATAL [434171] [SEvt::hostside_running_resize@1315]  NOT-is_self_provider SEvt::descProvider provider: 0x16eac4060 that address is: another object
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1322: void SEvt::hostside_running_resize(): Assertion `is_self_provider' failed.

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf32b801 in SEvt::hostside_running_resize (this=0xb560e0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1322
    #5  0x00007fffcf32c088 in SEvt::beginPhoton (this=0xb560e0, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1501
    #6  0x00007fffd296e036 in U4Recorder::PreUserTrackingAction_Optical (this=0xb2d1b0, track=0x7fff17988170)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:314
    #7  0x00007fffd296d7f0 in U4Recorder::PreUserTrackingAction (this=0xb2d1b0, track=0x7fff17988170) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:230
    #8  0x00007fffcdc8d8a8 in U4RecorderAnaMgr::PreUserTrackingAction (this=0xb55f10, trk=0x7fff17988170)




::

    (gdb) f 4
    #4  0x00007fffcf32b801 in SEvt::hostside_running_resize (this=0xb56690) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1322
    1322        assert( is_self_provider ); 
    (gdb) f 3
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    (gdb) f 5
    #5  0x00007fffcf32c088 in SEvt::beginPhoton (this=0xb56690, label=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1501
    1501        if(!hostside_running_resize_done) hostside_running_resize(); 
    (gdb) f 6
    #6  0x00007fffd296e036 in U4Recorder::PreUserTrackingAction_Optical (this=0xb2d300, track=0x7fff17989710)
        at /data/blyth/junotop/opticks/u4/U4Recorder.cc:314
    314             sev->beginPhoton(ulabel);  // THIS ZEROS THE SLOT 
    (gdb) 


::

    1304 /**
    1305 SEvt::hostside_running_resize
    1306 -------------------------------
    1307 
    1308 Canonically called from SEvt::beginPhoton  (also SEvt::setFrame_HostsideSimtrace)
    1309 
    1310 **/
    1311 
    1312 void SEvt::hostside_running_resize()
    1313 {
    1314     bool is_self_provider = isSelfProvider() ;
    1315     LOG_IF(fatal, is_self_provider == false ) << " NOT-is_self_provider " << descProvider() ;
    1316     LOG(LEVEL)
    1317         << " is_self_provider " << is_self_provider
    1318         << " hostside_running_resize_done " << hostside_running_resize_done
    1319         ;
    1320 
    1321     assert( hostside_running_resize_done == false );
    1322     assert( is_self_provider );
    1323 
    1324     hostside_running_resize_done = true ;
    1325     hostside_running_resize_();
    1326 
    1327     LOG(LEVEL)
    1328         << " is_self_provider " << is_self_provider
    1329         << std::endl
    1330         << evt->desc()
    1331         ;
    1332 
    1333 }


SEvt::hostside_running_resize is assuming sole SEvt but QSim needs its own ? 




TODO : review SEvt usage for GPU and CPU running 
------------------------------------------------

Beware that Opticks itself is deliberately kinda ignorant of opticksMode as its 
kinda more to do with the integration.  This may need to change to handle 
management of two SEvt simulataneously. 

::

    333 void G4CXOpticks::setGeometry_(CSGFoundry* fd_)
    334 {
    335     fd = fd_ ;
    336     
    337     sim->serialize() ;
    338     
    339     // formerly did G4CXOpticks__setGeometry_saveGeometry here 
    340     
    341     
    342     LOG(LEVEL) << "[ fd " << fd ;
    343     SEvt* sev = SEvt::Get() ; 
    344     if( sev == nullptr )
    345     {
    346         LOG(LEVEL) << " Calling SEvt::Create " ;
    347         sev = SEvt::Create() ; 
    348         // formerly setReldir to "ALL" but thats now default, and SEvt::RELDIR now static 
    349     }   
    350     else
    351     {
    352         LOG(LEVEL) << " Using pre-existing SEvt (happens when U4Recorder instanciated it first) " ;
    353     }   



::

    epsilon:g4cx blyth$ opticks-f SEvt::Get
    ./sysrap/SGenerate.h:        ph = SEvt::GetInputPhoton(); 
    ./sysrap/tests/SEvt_Lifecycle_Test.cc:        assert( SEvt::Get() == evt ); 
    ./sysrap/tests/SEvt_Lifecycle_Test.cc:        int npc = SEvt::GetNumPhotonCollected() ; 
    ./sysrap/tests/SEvt_Lifecycle_Test.cc:        assert( SEvt::Get() == evt ); 
    ./sysrap/tests/SEvt_test.cc:   std::cout << SEvt::Get()->desc() << std::endl ; 
    ./sysrap/tests/SEvt_test.cc:    unsigned num_hit = SEvt::GetNumHit(); 
    ./sysrap/tests/SEvtTest.cc:   std::cout << SEvt::Get()->desc() << std::endl ; 
    ./sysrap/tests/SGenerate_test.cc:    NP* gs = SEvt::GetGenstep();     
    ./sysrap/SEvt.cc:const char* SEvt::GetSaveDir(){ return INSTANCE ? INSTANCE->getSaveDir() : nullptr ; }
    ./sysrap/SEvt.cc:const char* SEvt::GetFrameId(){    return INSTANCE ? INSTANCE->getFrameId() : nullptr ; }
    ./sysrap/SEvt.cc:const NP*   SEvt::GetFrameArray(){ return INSTANCE ? INSTANCE->getFrameArray() : nullptr ; } 
    ./sysrap/SEvt.cc:    SEvt* prior = SEvt::Get();  
    ./sysrap/SEvt.cc:SEvt* SEvt::Get(){     return INSTANCE ; }
    ./sysrap/SEvt.cc:int  SEvt::GetTagSlot(){ return INSTANCE->getTagSlot() ; }
    ./sysrap/SEvt.cc:        assert( index == SEvt::GetIndex() );  
    ./sysrap/SEvt.cc:int SEvt::GetIndex(){           return INSTANCE ? INSTANCE->getIndex()  :  0 ; }
    ./sysrap/SEvt.cc:S4RandomArray* SEvt::GetRandomArray(){ return INSTANCE ? INSTANCE->random_array : nullptr ; }
    ./sysrap/SEvt.cc:const char* SEvt::GetReldir(){ return RELDIR ? RELDIR : DEFAULT_RELDIR ; }
    ./sysrap/SEvt.cc:const char* SEvt::GetReldir(){  return INSTANCE ? INSTANCE->getReldir() : nullptr ; }
    ./sysrap/SEvt.cc:int SEvt::GetNumPhotonCollected(){    return INSTANCE ? INSTANCE->getNumPhotonCollected() : UNDEF ; }
    ./sysrap/SEvt.cc:int SEvt::GetNumPhotonGenstepMax(){   return INSTANCE ? INSTANCE->getNumPhotonGenstepMax() : UNDEF ; }
    ./sysrap/SEvt.cc:int SEvt::GetNumPhotonFromGenstep(){  return INSTANCE ? INSTANCE->getNumPhotonFromGenstep() : UNDEF ; }
    ./sysrap/SEvt.cc:int SEvt::GetNumGenstepFromGenstep(){ return INSTANCE ? INSTANCE->getNumGenstepFromGenstep() : UNDEF ; }
    ./sysrap/SEvt.cc:int SEvt::GetNumHit(){  return INSTANCE ? INSTANCE->getNumHit() : UNDEF ; }
    ./sysrap/SEvt.cc:NP* SEvt::GetInputPhoton() {  return INSTANCE ? INSTANCE->getInputPhoton() : nullptr ; }
    ./qudarap/tests/QSimTest.cc:    SEvt* evt = SEvt::Get(); 
    ./qudarap/tests/QSimTest.cc:    SEvt* sev = SEvt::Get();
    ./qudarap/QEvent.cc:    sev(SEvt::Get()),
    ./qudarap/QEvent.cc:    input_photon = SEvt::GetInputPhoton(); 
    ./qudarap/QSim.cc:    const NP* p = SEvt::GetInputPhoton(); 
    ./qudarap/QSim.cc:    const NP* ip = SEvt::GetInputPhoton(); 
    ./u4/tests/U4SimulateTest.cc:    LOG(info) << SLOG::Banner() << " " << " savedir " << SEvt::GetSaveDir() ; 
    ./u4/tests/U4App.h:    const char* savedir = SEvt::GetSaveDir(); 
    ./u4/U4Random.cc:    int slot = SEvt::GetTagSlot(); 
    ./u4/U4Recorder.cc:    const char* savedir = SEvt::GetSaveDir() ; 
    ./u4/U4Recorder.cc:    SEvt* sev = SEvt::Get(); 
    ./u4/U4Recorder.cc:    LOG_IF(fatal, sev == nullptr) << " SEvt::Get returned nullptr " ; 
    ./u4/U4Recorder.cc:    SEvt* sev = SEvt::Get(); 
    ./u4/U4Recorder.cc:        SEvt* sev = SEvt::Get(); 
    ./u4/U4Recorder.cc:    SEvt* sev = SEvt::Get(); 
    ./u4/InstrumentedG4OpBoundaryProcess.cc:        quad2& prd = SEvt::Get()->current_prd ; 
    ./u4/U4HitGet.h:    SEvt* sev = SEvt::Get(); 
    ./g4cx/tests/G4CXOpticks_SetGeometry_GetInputPhoton_Test.cc:    NP* ip = SEvt::GetInputPhoton() ; 
    ./g4cx/tests/G4CXOpticks_SetGeometry_GetInputPhoton_Test.cc:    LOG_IF(error, ip == nullptr) << "SEvt::GetInputPhoton GIVES nullptr : SET OPTICKS_INPUT_PHOTON TO CONFIGURE " ; 
    ./g4cx/tests/G4CXOpticks_SetGeometry_GetInputPhoton_Test.cc:    const char* id = SEvt::GetFrameId() ; 
    ./g4cx/tests/G4CXOpticks_SetGeometry_GetInputPhoton_Test.cc:    const NP*   fr = SEvt::GetFrameArray() ; 
    ./g4cx/G4CXOpticks.cc:    SEvt* sev = SEvt::Get() ; 
    ./g4cx/G4CXOpticks.cc:    SEvt* sev = SEvt::Get();  
    ./g4cx/G4CXOpticks.cc:    SEvt* sev = SEvt::Get();  assert(sev); 
    ./g4cx/G4CXOpticks.cc:    int sev_index = SEvt::GetIndex() ;
    ./g4cx/G4CXOpticks.cc:    SEvt* sev = SEvt::Get(); 
    epsilon:opticks blyth$ 






DONE : maybe SEvt::Create SEvt::Get statics could manage multiple SEvt instances depending on opticksMode
-----------------------------------------------------------------------------------------------------------

so have 0,1 OR 2 SEvt INSTANCE not just 1 ?


::

    SEvt::CreateOrReuse
    ---------------------

    Creates 0, 1 OR 2 SEvt depending on SEventConfig::IntegrationMode()::

        OPTICKS_INTEGRATION_MODE (aka opticksMode)

    +-----------------+----------+----------+--------------------------------------------+
    |  opticksMode    | num SEvt | SEvt idx | notes                                      |
    +=================+==========+==========+============================================+
    |             0   |    0     |    -     |                                            |
    +-----------------+----------+----------+--------------------------------------------+
    |             1   |    1     |    0     |  GPU optical simulation only               |
    +-----------------+----------+----------+--------------------------------------------+
    |             2   |    1     |    1     |  CPU optical simulation only               |
    +-----------------+----------+----------+--------------------------------------------+
    |             3   |    2     |   0,1    |  both GPU and CPU optical simulations      |
    +-----------------+----------+----------+--------------------------------------------+






integrated running shakedown
-------------------------------

::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    GtOpticksTool::mutate event_number 0 deferred SEvt::GetInputPhoton  SEvt::Brief  SEvt::Exists(0) Y SEvt::Exists(1) Y
     SEvt::Get(0)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     SEvt::Get(1)->brief() SEvt::brief  getIndex 2147483647 hasInputPhoton Y hasInputPhotonTransformed Y
     m_input_photon (10000, 4, 4, )
    GtOpticksTool::mutate event_number 0 numPhotons 10000
     idx 0 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 1 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 2 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 3 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 4 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 5 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 6 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 7 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 2 eventID 0 LEVEL 5:DEBUG
    2023-07-30 00:16:30.262 FATAL [77715] [SEvt::SetIndex@1174]  index 0 count 2
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1175: static void SEvt::SetIndex(int): Assertion `index_permitted' failed.
    [New Thread 0x7fff9ffff700 (LWP 77783)]

    (gdb) 

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf32967c in SEvt::SetIndex (index=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1175
    #5  0x00007fffcf3293ab in SEvt::BeginOfEvent (index=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1129
    #6  0x00007fffd296d553 in U4Recorder::BeginOfEventAction (this=0xb2cfe0, event=0x7fff4e205d30) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:212
    #7  0x00007fffcdc8584c in U4RecorderAnaMgr::BeginOfEventAction (this=0xb55d60, evt=0x7fff4e205d30)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:31
    #8  0x00007fffce6cba69 in MgrOfAnaElem::BeginOfEventAction (this=0x7fffce8dab00 <MgrOfAnaElem::instance()::s_mgr>, evt=0x7fff4e205d30)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:46
    #9  0x00007fffcdfb4068 in LSExpEventAction::BeginOfEventAction (this=0x5979620, evt=0x7fff4e205d30)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpEventAction.cc:66
    #10 0x00007fffdbcc50bc in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so



    (gdb) f 7
    #7  0x00007fffcdc8584c in U4RecorderAnaMgr::BeginOfEventAction (this=0xb55d60, evt=0x7fff4e205d30)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:31
    31	void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* evt) {     m_recorder->BeginOfEventAction(evt);     }
    (gdb) f 6
    #6  0x00007fffd296d553 in U4Recorder::BeginOfEventAction (this=0xb2cfe0, event=0x7fff4e205d30) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:212
    212	    SEvt::BeginOfEvent(eventID); 
    (gdb) p eventID
    $1 = 0
    (gdb) f 5
    #5  0x00007fffcf3293ab in SEvt::BeginOfEvent (index=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1129
    1129	        SEvt::SetIndex(index); 
    (gdb) p index
    $2 = 0

    (gdb) f 4
    #4  0x00007fffcf32967c in SEvt::SetIndex (index=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1175
    1175	    assert( index_permitted ); 
    (gdb) 





Note that are getting 2 SEvt in opticksMode:2 due to G4CXOpticks::setGeometry called : although only CPU one will be filled
---------------------------------------------------------------------------------------------------------------------------------



HMM where is SEvt getting instanciated::

    BP=SEvt::SEvt ntds2_noxj 


    Breakpoint 1, SEvt::SEvt (this=0xb56130) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:132
    132	    clear_count(0)
    (gdb) bt
    #0  SEvt::SEvt (this=0xb56130) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:132
    #1  0x00007fffcf327465 in SEvt::Create (idx=1) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:801
    #2  0x00007fffcf328008 in SEvt::HighLevelCreate (idx=1) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:937
    #3  0x00007fffd296d1f4 in U4Recorder::U4Recorder (this=0xb2d1f0) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:157
    #4  0x00007fffcdc846c7 in U4RecorderAnaMgr::U4RecorderAnaMgr (this=0xb55f60, name=...)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:14



1st SEvt::

     152 U4Recorder::U4Recorder()
     153     :
     154     eventID(-1),
     155     transient_fSuspend_track(nullptr),
     156     rerun_rand(nullptr),
     157     evt(SEvt::HighLevelCreate(SEvt::ECPU))
     158 {
     159     INSTANCE = this ;
     160 }
     161 


2nd SEvt::

    (gdb) bt
    #0  SEvt::SEvt (this=0x16ba5d8b0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:132
    #1  0x00007fffcf327465 in SEvt::Create (idx=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:801
    #2  0x00007fffcf32768f in SEvt::CreateOrReuse (idx=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:815
    #3  0x00007fffd2e7b717 in G4CXOpticks::setGeometry_ (this=0x7513d90, fd_=0x164775110) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:343
    #4  0x00007fffd2e7b5eb in G4CXOpticks::setGeometry (this=0x7513d90, fd_=0x164775110) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:309
    #5  0x00007fffd2e7b5a3 in G4CXOpticks::setGeometry (this=0x7513d90, gg_=0xb32e530) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:272
    #6  0x00007fffd2e7b47c in G4CXOpticks::setGeometry (this=0x7513d90, world=0x59f2eb0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:264
    #7  0x00007fffd2e79ccf in G4CXOpticks::SetGeometry (world=0x59f2eb0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:66
    #8  0x00007fffcdf97754 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=2, world=0x59f2eb0, sd=0x5bd48d0, ppd=0x926c10, psd=0x929610, pmtscan=0x0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:50
    #9  0x00007fffcdf7a0c8 in LSExpDetectorConstruction::setupOpticks (this=0x580c660, world=0x59f2eb0)


Presumably could skip the second one in opticksMode 2 ... but opticksMode 2 and 3 are debug focussed 
so might as well just have both SEvt for them both. 




FIXED : Another index assert
------------------------------

::

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf328d38 in SEvt::SetIndex (index=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1196
    #5  0x00007fffd20889d8 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd4810, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:165
    #6  0x00007fffd207bc9b in junoSD_PMT_v2::EndOfEvent (this=0x5bd4870, HCE=0x7fff4de79fb0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    #7  0x00007fffd9bbac95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so



Looks like the two SEvt saved into same dir, switch on SPath::Resolve prefix:true
------------------------------------------------------------------------------------

::

    idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 2 eventID 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    2023-07-30 02:30:46.942 INFO  [124069] [SEvt::hostside_running_resize_@1762] resizing photon 0 to evt.num_photon 10000
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 2 with m_jpmt_dbg YES
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 2 hitCollection 3922 hcMuon 0 hcOpticks 0 GPU NO
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    2023-07-30 02:30:47.731 INFO  [124069] [SEvt::AddArray@2886]  k U4R.npy a (1, )
    2023-07-30 02:30:47.732 INFO  [124069] [SEvt::AddArray@2886]  k SEventConfig.npy a (1, )
    2023-07-30 02:30:47.732 INFO  [124069] [SEvt::save@3132]  dir /tmp/blyth/opticks/GEOM/V1J009/ntds2/ALL1/001
    2023-07-30 02:30:47.732 ERROR [124069] [SEvt::gatherHit@2541]  not yet implemented for hostside running : change CompMask with SEventConfig to avoid 
    2023-07-30 02:30:47.736 INFO  [124069] [SEvt::save@3132]  dir /tmp/blyth/opticks/GEOM/V1J009/ntds2/ALL1/001
    2023-07-30 02:30:47.842 ERROR [124069] [SEvt::gatherHit@2541]  not yet implemented for hostside running : change CompMask with SEventConfig to avoid 
    2023-07-30 02:30:47.950 INFO  [124069] [SEvt::clear@1405] SEvt::clear
    2023-07-30 02:30:47.950 INFO  [124069] [SEvt::clear@1405] SEvt::clear
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully




opticksMode:3 
----------------

::

    Begin of Event --> 0
    2023-07-30 03:16:40.122 INFO  [153097] [SEvt::hostside_running_resize_@1762] resizing photon 0 to evt.num_photon 10000
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES
    2023-07-30 03:16:40.900 INFO  [153097] [G4CXOpticks::simulate@440] [
    2023-07-30 03:16:40.900 INFO  [153097] [G4CXOpticks::simulate@441] G4CXOpticks::desc sim 0x7515680 tr 0x794e4f0 wd 0x59f2a60 gg 0xb32e040 fd 0x1647747e0 cx Y qs Y
    2023-07-30 03:16:40.900 INFO  [153097] [G4CXOpticks::simulate@455] [ num_genstep 1 num_photon 10000 SEvt::brief  getIndex 1 hasInputPhoton Y hasInputPhotonTransformed Y
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:545: void SEvt::addFrameGenstep(): Assertion `genstep.size() == 0' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf326146 in SEvt::addFrameGenstep (this=0x16ba5cf70) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:545
    #5  0x00007fffcf325dd6 in SEvt::AddFrameGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:522
    #6  0x00007fffcf328a8f in SEvt::BeginOfEvent (eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1151
    #7  0x00007fffcf7675a4 in QSim::simulate (this=0x16ec45a20, eventID=0) at /data/blyth/junotop/opticks/qudarap/QSim.cc:315
    #8  0x00007fffd2e7c4bf in G4CXOpticks::simulate (this=0x75138c0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:463
    #9  0x00007fffd2088e57 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd4420, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:237
    #10 0x00007fffd2088a15 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd4420, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:172
    #11 0x00007fffd207bc9b in junoSD_PMT_v2::EndOfEvent (this=0x5bd4480, HCE=0x7fff17a62c10) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    #12 0x00007fffd9bbac95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] ()


    (gdb) f 8 
    #8  0x00007fffd2e7c4bf in G4CXOpticks::simulate (this=0x75138c0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:463
    463	    qs->simulate(eventID);   // GPU launch doing generation and simulation here 
    (gdb) f 7
    #7  0x00007fffcf7675a4 in QSim::simulate (this=0x16ec45a20, eventID=0) at /data/blyth/junotop/opticks/qudarap/QSim.cc:315
    315	    SEvt::BeginOfEvent(eventID);  // set SEvt index and tees up frame gensteps for simtrace and input photon simulate running
    (gdb) f 6
    #6  0x00007fffcf328a8f in SEvt::BeginOfEvent (eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1151
    1151	    SEvt::AddFrameGenstep();  // needed for simtrace and input photon running
    (gdb) list
    1146	void SEvt::BeginOfEvent(int eventID)  // static
    1147	{
    1148	    int index = 1+eventID ;  
    1149	    LOG(LEVEL) << " index " << index ; 
    1150	    SEvt::SetIndex(index); 
    1151	    SEvt::AddFrameGenstep();  // needed for simtrace and input photon running
    1152	}
    1153	
    1154	/**
    1155	SEvt::EndOfEvent
    (gdb) f 5
    #5  0x00007fffcf325dd6 in SEvt::AddFrameGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:522
    522	    if(Exists(0)) Get(0)->addFrameGenstep() ; 
    (gdb) f 4
    #4  0x00007fffcf326146 in SEvt::addFrameGenstep (this=0x16ba5cf70) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:545
    545	        assert( genstep.size() == 0 ) ; // cannot mix input photon running with other genstep running  
    (gdb) 



Where are the extra genstep coming from ?
----------------------------------------------

::

    BP=SEvt::addGenstep ntds3_noxj


::

    (gdb) bt
    #0  SEvt::addGenstep (this=0x16ba5d8b0, q_=...) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1541
    #1  0x00007fffcf32630a in SEvt::addFrameGenstep (this=0x16ba5d8b0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:557
    #2  0x00007fffcf325dd6 in SEvt::AddFrameGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:522
    #3  0x00007fffcf328c35 in SEvt::BeginOfEvent (eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1160
    #4  0x00007fffd296d553 in U4Recorder::BeginOfEventAction (this=0xb2d310, event=0x7fff17dede50) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:212
    #5  0x00007fffcdc8484c in U4RecorderAnaMgr::BeginOfEventAction (this=0x93f2b0, evt=0x7fff17dede50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:31
    #6  0x00007fffce6caa69 in MgrOfAnaElem::BeginOfEventAction (this=0x7fffce8d9b00 <MgrOfAnaElem::instance()::s_mgr>, evt=0x7fff17dede50)

    (gdb) f 5
    #5  0x00007fffcdc8484c in U4RecorderAnaMgr::BeginOfEventAction (this=0x93f2b0, evt=0x7fff17dede50)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:31
    31	void U4RecorderAnaMgr::BeginOfEventAction(const G4Event* evt) {     m_recorder->BeginOfEventAction(evt);     }
    (gdb) f 4
    #4  0x00007fffd296d553 in U4Recorder::BeginOfEventAction (this=0xb2d310, event=0x7fff17dede50) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:212
    212	    SEvt::BeginOfEvent(eventID); 
    (gdb) f 3
    #3  0x00007fffcf328c35 in SEvt::BeginOfEvent (eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1160
    1160	    SEvt::AddFrameGenstep();  // needed for simtrace and input photon running
    (gdb) f 2
    #2  0x00007fffcf325dd6 in SEvt::AddFrameGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:522
    522	    if(Exists(0)) Get(0)->addFrameGenstep() ; 
    (gdb) f 1
    #1  0x00007fffcf32630a in SEvt::addFrameGenstep (this=0x16ba5d8b0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:557
    557	        addGenstep(MakeInputPhotonGenstep(input_photon, frame)); 
    (gdb) p instance
    $1 = 0
    (gdb) p index
    $2 = 1
    (gdb) 


Looks like SEvt::AddFrameGenstep needs to be more careful about which SEvt to target for opticksMode:3 
Currently both going to instance slot zero, the first one encountered. 


In general need to revisit the SEvt statics in the light of now sometimes having two INSTANCES
--------------------------------------------------------------------------------------------------

DONE : SEvt:: static weeding, lots of the statics are being used lazily, have removed many of them 
---------------------------------------------------------------------------------------------------

* expect opticksMode:3 validations will reveal more SEvt statics that need changing 


::

    .idx 7 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 8 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
     idx 9 event.event_number 0 wavelength_nm 440.000 wavelength      0.000 energy      0.000 energy/eV      2.818
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    2023-07-30 23:35:38.074 INFO  [199089] [SEvt::addGenstep@1523]  index 1 instance 1
    Begin of Event --> 0
    2023-07-30 23:35:38.080 INFO  [199089] [SEvt::hostside_running_resize_@1752] resizing photon 0 to evt.num_photon 10000
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1244: static int SEvt::GetNumGenstepFromGenstep(): Assertion `n0 == n1' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf327e92 in SEvt::GetNumGenstepFromGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1244
    #5  0x00007fffd2088e2e in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd4910, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:234
    #6  0x00007fffd2088a15 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd4910, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:172
    #7  0x00007fffd207bc9b in junoSD_PMT_v2::EndOfEvent (this=0x5bd4970, HCE=0x7fff17a62410) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    #8  0x00007fffd9bbac95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] ()



    (gdb) f 7
    #7  0x00007fffd207bc9b in junoSD_PMT_v2::EndOfEvent (this=0x5bd4970, HCE=0x7fff17a62410) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    1142	    m_jpmt_opticks->EndOfEvent(HCE, m_eventID );    
    (gdb) f 6
    #6  0x00007fffd2088a15 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd4910, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:172
    172	        EndOfEvent_Simulate(eventID) ; 
    (gdb) f 5
    #5  0x00007fffd2088e2e in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd4910, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:234
    234	    unsigned num_genstep = SEvt::GetNumGenstepFromGenstep(); 
    (gdb) list
    229	}
    230	
    231	
    232	void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    233	{
    234	    unsigned num_genstep = SEvt::GetNumGenstepFromGenstep(); 
    235	    unsigned num_photon  = SEvt::GetNumPhotonFromGenstep(); 
    236	
    237	    G4CXOpticks::Get()->simulate(eventID) ; 
    238	
    (gdb) f 4
    #4  0x00007fffcf327e92 in SEvt::GetNumGenstepFromGenstep () at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1244
    1244	        assert( n0 == n1 );
    (gdb) p n0
    $1 = 0
    (gdb) p n1
    $2 = 1
    (gdb) 



OOM
-----

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    2023-07-31 01:03:40.275 INFO  [225267] [SEvt::addGenstep@1480]  index 1 instance 1
    Begin of Event --> 0
    2023-07-31 01:03:40.280 INFO  [225267] [SEvt::hostside_running_resize_@1709] resizing photon 0 to evt.num_photon 10000
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES
    2023-07-31 01:03:41.039 INFO  [225267] [G4CXOpticks::simulate@480] [
    2023-07-31 01:03:41.039 INFO  [225267] [G4CXOpticks::simulate@481] G4CXOpticks::desc sim 0x7515a90 tr 0x794e980 wd 0x59f2df0 gg 0xb32e300 fd 0x1647747e0 cx Y qs Y
    2023-07-31 01:03:41.039 INFO  [225267] [SEvt::addGenstep@1480]  index 1 instance 0
    2023-07-31 01:03:41.039 INFO  [225267] [SEvt::clear@1348] SEvt::clear
    2023-07-31 01:03:41.059 ERROR [225267] [QU::_cudaMalloc@219] save salloc record to /tmp/blyth/opticks/GEOM/V1J009/ntds3
    junotoptask.execute            ERROR: CUDA call (max_photon*max_prd*sizeof(quad2) ) failed with error: 'out of memory' (/data/blyth/junotop/opticks/qudarap/QU.cc:213)
    salloc::desc alloc.size 9 label.size 9

         [           size   num_items sizeof_item       spare]    size_GB    percent label
         [        (bytes)                                    ]   size/1e9            

         [            240           1         240           0]       0.00       0.00 QEvent::QEvent/sevent
         [        8294400     2073600           4           0]       0.01       0.06 Frame::DeviceAllo:num_pixels
         [       96000000     1000000          96           0]       0.10       0.68 device_alloc_genstep:quad6
         [       12000000     3000000           4           0]       0.01       0.08 device_alloc_genstep:int seed
         [      192000000     3000000          64           0]       0.19       1.36 max_photon*sizeof(sphoton)
         [     6144000000    96000000          64           0]       6.14      43.47 max_photon*max_record*sizeof(sphoton)
         [     1536000000    96000000          16           0]       1.54      10.87 max_photon*max_rec*sizeof(srec)
         [     3072000000    96000000          32           0]       3.07      21.74 max_photon*max_seq*sizeof(sseq)
         [     3072000000    96000000          32           0]       3.07      21.74 max_photon*max_prd*sizeof(quad2)

     tot      14132294640                                           14.13

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2023-07-31 01:03:41,664] p225267 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:176} INFO - ]JUNOApplication.run
    Namespace(ACU_source_weight_QC=False, CLS_source_weight_QC=False, GT_source_theta=0, K40_ACU_source_weight_QC=False, MaterialDataDir=None, OffsetInX=0, OffsetInY=0, OffsetInZ=0, additionacrylic_simplify_csg=True, anamgr_atmo=False, anamgr_config_file=None, anamgr_deposit=False, anamgr_deposit_tt=False, anamgr_edm=False, 




::

     68 QEvent::QEvent()
     69     :
     70     sev(SEvt::Get_EGPU()),
     71     selector(sev ? sev->selector : nullptr),
     72     evt(sev ? sev->evt : nullptr),
     73     d_evt(QU::device_alloc<sevent>(1,"QEvent::QEvent/sevent")),
     74     gs(nullptr),
     75     input_photon(nullptr),
     76     upload_count(0),



Improve salloc collection
---------------------------

::

    2023-07-31 03:03:17.853 INFO  [251673] [G4CXOpticks::simulate@480] [
    2023-07-31 03:03:17.853 INFO  [251673] [G4CXOpticks::simulate@481] G4CXOpticks::desc sim 0x75157a0 tr 0x794e690 wd 0x59f2af0 gg 0xb32e000 fd 0x1647747e0 cx Y qs Y
    2023-07-31 03:03:17.853 INFO  [251673] [SEvt::addGenstep@1480]  index 1 instance 0
    2023-07-31 03:03:17.854 INFO  [251673] [SEvt::clear@1348] SEvt::clear
    2023-07-31 03:03:17.854 INFO  [251673] [QU::device_alloc@238]  num_items    1000000 size   96000000 label QEvent::setGenstep/device_alloc_genstep:quad6
    2023-07-31 03:03:17.855 INFO  [251673] [QU::device_alloc@238]  num_items    3000000 size   12000000 label QEvent::setGenstep/device_alloc_genstep:int seed
    2023-07-31 03:03:17.861 INFO  [251673] [QU::device_alloc_zero@276]  num_items    3000000 size  192000000 label QEvent::device_alloc_photon/max_photon*sizeof(sphoton)
    2023-07-31 03:03:17.862 INFO  [251673] [QU::device_alloc_zero@276]  num_items   96000000 size 6144000000 label max_photon*max_record*sizeof(sphoton)
    2023-07-31 03:03:17.868 INFO  [251673] [QU::device_alloc_zero@276]  num_items   96000000 size 1536000000 label max_photon*max_rec*sizeof(srec)
    2023-07-31 03:03:17.870 INFO  [251673] [QU::device_alloc_zero@276]  num_items   96000000 size 3072000000 label max_photon*max_seq*sizeof(sseq)
    2023-07-31 03:03:17.874 INFO  [251673] [QU::device_alloc_zero@276]  num_items   96000000 size 3072000000 label max_photon*max_prd*sizeof(quad2)
    2023-07-31 03:03:17.875 ERROR [251673] [QU::_cudaMalloc@224] save salloc record to /tmp/blyth/opticks/GEOM/V1J009/ntds3
    junotoptask.execute            ERROR: CUDA call (max_photon*max_prd*sizeof(quad2) ) failed with error: 'out of memory' (/data/blyth/junotop/opticks/qudarap/QU.cc:218)
    salloc::desc alloc.size 19 label.size 19
    salloc.meta
    evt.max_photon:3000000
    evt.max_record:32
    evt.max_rec:32
    evt.max_seq:32
    evt.max_prd:32
    evt.max_tag:1
    evt.max_flat:1
    evt.num_photon:10000
    evt.num_record:320000
    evt.num_rec:320000
    evt.num_seq:10000
    evt.num_prd:320000
    evt.num_tag:10000
    evt.num_flat:10000


         [           size   num_items sizeof_item       spare]    size_GB    percent label
         [        (bytes)                                    ]   size/1e9            

         [              4           1           4           0]       0.00       0.00 QBase::init/d_base
         [      144000000     3000000          48           0]       0.14       1.01 QRng::upload/rng_states
         [             16           1          16           0]       0.00       0.00 QRng::upload/d_qr
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             32           1          32           0]       0.00       0.00 QBnd::QBnd/d_qb
         [            416           1         416           0]       0.00       0.00 QDebug::QDebug/d_dbg
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             24           1          24           0]       0.00       0.00 QScint::QScint/d_scint
         [             24           1          24           0]       0.00       0.00 QCerenkov::QCerenkov/d_cerenkov.0
         [            240           1         240           0]       0.00       0.00 QEvent::QEvent/sevent
         [             64           1          64           0]       0.00       0.00 QSim::init.sim
         [        8294400     2073600           4           0]       0.01       0.06 Frame::DeviceAllo:num_pixels
         [       96000000     1000000          96           0]       0.10       0.67 QEvent::setGenstep/device_alloc_genstep:quad6
         [       12000000     3000000           4           0]       0.01       0.08 QEvent::setGenstep/device_alloc_genstep:int seed
         [      192000000     3000000          64           0]       0.19       1.34 QEvent::device_alloc_photon/max_photon*sizeof(sphoton)
         [     6144000000    96000000          64           0]       6.14      43.04 max_photon*max_record*sizeof(sphoton)
         [     1536000000    96000000          16           0]       1.54      10.76 max_photon*max_rec*sizeof(srec)
         [     3072000000    96000000          32           0]       3.07      21.52 max_photon*max_seq*sizeof(sseq)
         [     3072000000    96000000          32           0]       3.07      21.52 max_photon*max_prd*sizeof(quad2)

     tot      14276295348                                           14.28






    epsilon:tests blyth$ ./salloc_test.sh
             BASH_SOURCE : ./salloc_test.sh 
                    name : salloc_test 
                    FOLD : /tmp/salloc_test 
                    BASE : /tmp/blyth/opticks/GEOM/V1J009/ntds3 
          OPTICKS_PREFIX : /usr/local/opticks 
                    GEOM : V1J009 
    a.desc
    salloc::desc alloc.size 19 label.size 19
    salloc.meta
    evt.max_photon:3000000
    evt.max_record:32
    evt.max_rec:32
    evt.max_seq:32
    evt.max_prd:32
    evt.max_tag:1
    evt.max_flat:1
    evt.num_photon:10000
    evt.num_record:320000
    evt.num_rec:320000
    evt.num_seq:10000
    evt.num_prd:320000
    evt.num_tag:10000
    evt.num_flat:10000


         [           size   num_items sizeof_item       spare]    size_GB    percent label
         [        (bytes)                                    ]   size/1e9            

         [              4           1           4           0]       0.00       0.00 QBase::init/d_base
         [      144000000     3000000          48           0]       0.14       1.01 QRng::upload/rng_states
         [             16           1          16           0]       0.00       0.00 QRng::upload/d_qr
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             32           1          32           0]       0.00       0.00 QBnd::QBnd/d_qb
         [            416           1         416           0]       0.00       0.00 QDebug::QDebug/d_dbg
         [             64           1          64           0]       0.00       0.00 QTex::uploadMeta
         [             24           1          24           0]       0.00       0.00 QScint::QScint/d_scint
         [             24           1          24           0]       0.00       0.00 QCerenkov::QCerenkov/d_cerenkov.0
         [            240           1         240           0]       0.00       0.00 QEvent::QEvent/sevent
         [             64           1          64           0]       0.00       0.00 QSim::init.sim
         [        8294400     2073600           4           0]       0.01       0.06 Frame::DeviceAllo:num_pixels
         [       96000000     1000000          96           0]       0.10       0.67 QEvent::setGenstep/device_alloc_genstep:quad6
         [       12000000     3000000           4           0]       0.01       0.08 QEvent::setGenstep/device_alloc_genstep:int seed
         [      192000000     3000000          64           0]       0.19       1.34 QEvent::device_alloc_photon/max_photon*sizeof(sphoton)
         [     6144000000    96000000          64           0]       6.14      43.04 max_photon*max_record*sizeof(sphoton)
         [     1536000000    96000000          16           0]       1.54      10.76 max_photon*max_rec*sizeof(srec)
         [     3072000000    96000000          32           0]       3.07      21.52 max_photon*max_seq*sizeof(sseq)
         [     3072000000    96000000          32           0]       3.07      21.52 max_photon*max_prd*sizeof(quad2)

     tot      14276295348                                           14.28
    epsilon:tests blyth$ 




HMM : ARE USING "TITAN V" WITH 12G BASED ON nvidia-smi process list::

    N[blyth@localhost opticks]$ nvidia-smi
    Mon Jul 31 03:15:17 2023       
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 435.21       Driver Version: 435.21       CUDA Version: 10.1     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  TITAN RTX           Off  | 00000000:73:00.0 Off |                  N/A |
    | 41%   38C    P8    23W / 280W |     10MiB / 24219MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
    |   1  TITAN V             Off  | 00000000:A6:00.0 Off |                  N/A |
    | 34%   49C    P8    28W / 250W |    536MiB / 12066MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+
                                                                                   
    +-----------------------------------------------------------------------------+
    | Processes:                                                       GPU Memory |
    |  GPU       PID   Type   Process name                             Usage      |
    |=============================================================================|
    |    1    252057      C   ...p/ExternalLibs/Python/3.8.12/bin/python   525MiB |
    +-----------------------------------------------------------------------------+
    N[blyth@localhost opticks]$ 



Check with::

    export OPTICKS_MAX_PHOTON=10000 
    ntds3_noxj




::

    2023-07-31 03:15:29.983 INFO  [252057] [QU::device_alloc_zero@276]  num_items     320000 size   10240000 label max_photon*max_seq*sizeof(sseq)
    2023-07-31 03:15:29.984 INFO  [252057] [QU::device_alloc_zero@276]  num_items     320000 size   10240000 label max_photon*max_prd*sizeof(quad2)
    2023-07-31 03:15:29.984 INFO  [252057] [QU::device_alloc_zero@276]  num_items      10000 size     320000 label max_photon*sizeof(stag)
    2023-07-31 03:15:29.984 INFO  [252057] [QU::device_alloc_zero@276]  num_items      10000 size    2560000 label max_photon*sizeof(sflat)
    junotoptask.execute            ERROR: CUDA error on synchronize with error 'an illegal memory access was encountered' (/data/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:920)

    junotoptask.finalize            WARN: invalid state tranform ((Running)) => ((Finalized))
    [2023-07-31 03:15:30,049] p252057 {/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py:176} INFO - ]JUNOApplication.run
    Namespace(ACU_source_weight_QC=False, CLS_source_weight_QC=False, GT_source_theta=0, K40_ACU_source_weight_QC=False, MaterialDataDir=None, OffsetInX=0, OffsetInY=0, OffsetInZ=0, additionacrylic_simplify_csg=True, anamgr_atmo=False, anamgr_config_file=None, anamgr_deposit=False, anamgr_deposit_tt=False, anamgr_edm=False, anamgr_edm_ge




FIXED : ntds3 CUDA fail : "an illegal memory access was encountered"
---------------------------------------------------------------------

* fixed by arranging QPMT upload by moving SSim::AddExtraSubfold earlier 

Fail seen when using ntds3_noxj and input photons::

    RainXZ_Z230_100_f8.npy
    RainXZ_Z230_10k_f8.npy

Initially thought the ntds3 fail could be from a rare photon, eg big bouncer not truncated properly,
but the success of below cxs_min.sh with 100k input photons makes that unlikely although still possible. 

So could be a general problem at G4CXOpticks gx level ? Need to test up at that level ?
Actually there is not much done at that level : so looks unlikely to be cause of issues. 

Could be a difference between running from a live geometry vs one that has been loaded. 
Maybe something missing in the live geometry that gets serialized by the save ? 
Could move the save before the launch to check if that is the issue. 

* problem with this is the slow development cycle 





DONE : Check the cx min scripts : all working as expected
-----------------------------------------------------------

* cxr_min.sh works with expected render 
* cxt_min.sh works with expected simtrace plot 
* cxs_min.sh works with expected simulate positions

  * OK: RainXZ_Z195_1000_f8.npy 
  * OK: RainXZ_Z230_1000_f8.npy
  * OK: RainXZ_Z230_10k_f8.npy 
  * OK: RainXZ_Z230_100k_f8.npy 





DONE : QSim=INFO logging comparison between ntds3_noxj and cxs_min.sh  : reveals lack of QPMT
-----------------------------------------------------------------------------------------------

ntds3_noxj::

    2023-07-31 19:22:17.838 INFO  [270896] [QSim::UploadComponents@138] QDebug::desc  dbg 0x16eb2e430 d_dbg 0x7fff5fe01600
     QState::Desc QState::Desc
    material1 ( 1.000,1000.000,1000.000, 0.000) 
    material2 ( 1.500,1000.000,1000.000, 0.000) 
    m1group2  (300.000, 0.000, 0.000, 0.000) 
    surface   ( 0.000, 0.000, 0.000, 0.000) 
    optical   (     0,     0,     0,     0) 

     dbg.p.desc  pos ( 0.000, 0.000, 0.000)  t     0.000  mom ( 1.000, 0.000, 0.000)  iindex 1065353216  pol ( 0.000, 1.000, 0.000)  wl  500.000   bn 0 fl 0 id 0 or 1 ix 0 fm 0 ab    ii 1065353216
    2023-07-31 19:22:17.838 INFO  [270896] [QSim::UploadComponents@151]   propcom null, snam::PROPCOM propcom.npy
    2023-07-31 19:22:17.839 INFO  [270896] [QSim::UploadComponents@164] QScint dsrc NP  dtype <f8(3, 4096, 1, ) size 12288 uifc f ebyte 8 shape.size 3 data.size 98304 meta.size 97 names.size 1 src NP  dtype <f4(3, 4096, 1, ) size 12288 uifc f ebyte 4 shape.size 3 data.size 49152 meta.size 97 names.size 1 tex QTex width 4096 height 3 texObj 2 meta 0x16ea40fd0 d_meta 0x7fff5fe01800 tex 0x16eb2e140
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::UploadComponents@173] QCerenkov fold - icdf_ - icdf - tex 0
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::UploadComponents@184]  NO QPMT instance 
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::UploadComponents@185] QPMT<float> WITH_CUSTOM4  INSTANCE:NO  
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::QSim@242] QSim.hh this 0x16eb27e40 INSTANCE 0x0 QEvent.hh:event 0x16eb27ef0 qsim.h:sim 0x0
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::init@282] QSim.hh this 0x16eb27e40 INSTANCE 0x16eb27e40 QEvent.hh:event 0x16eb27ef0 qsim.h:sim 0x16eb27b00
    2023-07-31 19:22:17.840 INFO  [270896] [QSim::init@283] 
     base       Y
     event      Y
     rng        Y
     scint      Y
     cerenkov   Y
     bnd        Y
     prop       N
     multifilm  N
     sim        Y
     d_sim      Y
     dbg        Y
     d_dbg      Y



cxs_min.sh::

    2023-07-31 19:29:38.006 INFO  [271364] [QSim::UploadComponents@104] [ ssim 0x1dec6b0
    2023-07-31 19:29:38.006 INFO  [271364] [QSim::UploadComponents@107] [ new QBase
    2023-07-31 19:29:38.137 INFO  [271364] [QSim::UploadComponents@109] ] new QBase : latency here of about 0.3s from first device access, if latency of >1s need to start nvidia-persistenced 
    2023-07-31 19:29:38.137 INFO  [271364] [QSim::UploadComponents@110] QBase::desc base 0x5fd81d0 d_base 0x7fa988400000 base.desc qbase::desc pidx 4294967295
    2023-07-31 19:29:38.137 INFO  [271364] [QSim::UploadComponents@114] [ new QRng 
    2023-07-31 19:29:38.708 INFO  [271364] [QSim::UploadComponents@116] ] new QRng 
    2023-07-31 19:29:38.708 INFO  [271364] [QSim::UploadComponents@118] QRng path /home/blyth/.opticks/rngcache/RNG/QCurandState_3000000_0_0.bin rngmax 3000000 qr 0xa63b0d0 d_qr 0x7fa988400200
    2023-07-31 19:29:38.708 INFO  [271364] [QSim::UploadComponents@131] QOptical optical NP  dtype <i4(52, 4, 4, ) size 832 uifc i ebyte 4 shape.size 3 data.size 3328 meta.size 0 names.size 0
    2023-07-31 19:29:38.728 INFO  [271364] [QSim::UploadComponents@134] QBnd src NP  dtype <f4(52, 4, 2, 761, 4, ) size 1266304 uifc f ebyte 4 shape.size 5 data.size 5065216 meta.size 61 names.size 52 tex QTex width 761 height 416 texObj 1 meta 0xa6dc120 d_meta 0x7fa988401200 tex 0xa6dc230
    2023-07-31 19:29:38.728 INFO  [271364] [QSim::UploadComponents@138] QDebug::desc  dbg 0xa727ea0 d_dbg 0x7fa988401600
     QState::Desc QState::Desc
    material1 ( 1.000,1000.000,1000.000, 0.000) 
    material2 ( 1.500,1000.000,1000.000, 0.000) 
    m1group2  (300.000, 0.000, 0.000, 0.000) 
    surface   ( 0.000, 0.000, 0.000, 0.000) 
    optical   (     0,     0,     0,     0) 

     dbg.p.desc  pos ( 0.000, 0.000, 0.000)  t     0.000  mom ( 1.000, 0.000, 0.000)  iindex 1065353216  pol ( 0.000, 1.000, 0.000)  wl  500.000   bn 0 fl 0 id 0 or 1 ix 0 fm 0 ab    ii 1065353216
    2023-07-31 19:29:38.729 INFO  [271364] [QSim::UploadComponents@151]   propcom null, snam::PROPCOM propcom.npy
    2023-07-31 19:29:38.729 INFO  [271364] [QSim::UploadComponents@164] QScint dsrc NP  dtype <f8(3, 4096, 1, ) size 12288 uifc f ebyte 8 shape.size 3 data.size 98304 meta.size 97 names.size 1 src NP  dtype <f4(3, 4096, 1, ) size 12288 uifc f ebyte 4 shape.size 3 data.size 49152 meta.size 97 names.size 1 tex QTex width 4096 height 3 texObj 2 meta 0xa6d9750 d_meta 0x7fa988401800 tex 0xa65a660
    2023-07-31 19:29:38.729 INFO  [271364] [QSim::UploadComponents@173] QCerenkov fold - icdf_ - icdf - tex 0
    2023-07-31 19:29:38.732 INFO  [271364] [QSim::UploadComponents@185] QPMT<float> WITH_CUSTOM4  INSTANCE:YES QPMT::desc
                           rindex (24, 15, 2, )
                          qeshape (3, 44, 2, )
                        thickness (3, 4, 1, )
                             lcqs (17612, 2, )
                  pmt.rindex_prop 0x7fa988402a00
                 pmt.qeshape_prop 0x7fa988403200
                    pmt.thickness 0x7fa988403400
                         pmt.lcqs 0x7fa988403600
                            d_pmt 0x7fa988425e00

    2023-07-31 19:29:38.732 INFO  [271364] [QSim::QSim@242] QSim.hh this 0xa7594e0 INSTANCE 0x0 QEvent.hh:event 0xa65a890 qsim.h:sim 0x0
    2023-07-31 19:29:38.732 INFO  [271364] [QSim::init@282] QSim.hh this 0xa7594e0 INSTANCE 0xa7594e0 QEvent.hh:event 0xa65a890 qsim.h:sim 0xa74f510
    2023-07-31 19:29:38.733 INFO  [271364] [QSim::init@283] 
     base       Y
     event      Y
     rng        Y
     scint      Y
     cerenkov   Y
     bnd        Y
     prop       Y
     multifilm  N
     sim        Y
     d_sim      Y
     dbg        Y
     d_dbg      Y

    2023-07-31 19:29:39.820 INFO  [271364] [QSim::simulate@310] 
    2023-07-31 19:29:39.820 INFO  [271364] [SEvt::addGenstep@1480]  index 1 instance 0
    2023-07-31 19:29:39.820 INFO  [271364] [QSim::simulate@318] QSim.hh this 0xa7594e0 INSTANCE 0xa7594e0 QEvent.hh:event 0xa65a890 qsim.h:sim 0xa74f510



Add some QSim debug::

     174     const NPFold* spmt_f = ssim->get_spmt_f() ;
     175     QPMT<float>* qpmt = spmt_f ? new QPMT<float>(spmt_f) : nullptr ;
     176     LOG_IF(LEVEL, qpmt == nullptr ) 
     177         << " NO QPMT instance "
     178         << " spmt_f " << ( spmt_f ? "YES" : "NO " )
     179         << " qpmt " << ( qpmt ? "YES" : "NO " )
     180         ;
     181     


HMM ordering issue ? The adding of jpmt needs to happen before G4CXOpticks::SetGeometry ?
Thats because SetGeometry instanciates QSim and upload components to GPU::

    SSim::AddExtraSubfold("jpmt", jpmt )

jcv LSExpDetectorConstruction_Opticks::

     38     NPFold* jpmt = SerializePMT(ppd, psd, pmtscan) ;
     39 
     40     LOG(info) << "[ WITH_G4CXOPTICKS opticksMode " << opticksMode << " sd " << sd  ;
     41     if( opticksMode == 0 )
     42     {
     43         SEvt::HighLevelCreateOrReuse(SEvt::ECPU);    // U4RecorderAnaMgr not active in opticksMode:0 
     44         SSim::Create();                              // done by G4CXOpticks::G4CXOpticks in opticksMode > 0
     45         SSim::AddExtraSubfold("jpmt", jpmt );
     46     }
     47     else if( opticksMode == 1 || opticksMode == 3 || opticksMode == 2 )
     48     {
     49         if(opticksMode == 2) G4CXOpticks::SetNoGPU() ;
     50         G4CXOpticks::SetGeometry(world) ;
     51         SSim::AddExtraSubfold("jpmt", jpmt );  // needs to be before SaveGeometry 
     52         G4CXOpticks::SaveGeometry();
     53     }
     54     LOG(info) << "] WITH_G4CXOPTICKS " ;
     55 }



DONE : gatherHit assert, this was due to repeated gather ?
-----------------------------------------------------------------

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    junoSD_PMT_v2_Opticks::Initialize opticksMode 3 eventID 0 LEVEL 5:DEBUG
    2023-07-31 20:49:33.425 INFO  [276821] [SEvt::addGenstep@1480]  index 1 instance 1
    Begin of Event --> 0
    2023-07-31 20:49:33.427 INFO  [276821] [SEvt::hostside_running_resize_@1709] resizing photon 0 to evt.num_photon 100
    junoSD_PMT_v2_Opticks::EndOfEvent_Debug eventID 0 opticksMode 3 with m_jpmt_dbg YES
    2023-07-31 20:49:33.444 INFO  [276821] [G4CXOpticks::simulate@480] [
    2023-07-31 20:49:33.444 INFO  [276821] [G4CXOpticks::simulate@481] G4CXOpticks::desc sim 0x7518cb0 tr 0x7951d00 wd 0x59f5ff0 gg 0xb331760 fd 0x164778110 cx Y qs Y
    2023-07-31 20:49:33.444 INFO  [276821] [QSim::simulate@312] 
    2023-07-31 20:49:33.445 INFO  [276821] [SEvt::addGenstep@1480]  index 1 instance 0
    2023-07-31 20:49:33.445 INFO  [276821] [QSim::simulate@320] QSim::desc
     this 0x16f074aa0 INSTANCE 0x16f074aa0 QEvent.hh:event 0x16eaf0270 qsim.h:sim 0x16f0515d0
    2023-07-31 20:49:33.445 INFO  [276821] [SEvt::clear@1348] SEvt::clear
    2023-07-31 20:49:33.463 INFO  [276821] [SEvt::save@3093]  dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001 index 1 instance 0
    2023-07-31 20:49:33.468 INFO  [276821] [SEvt::clear@1348] SEvt::clear
    python: /data/blyth/junotop/opticks/qudarap/QEvent.cc:588: NP* QEvent::gatherHit() const: Assertion `evt->num_photon' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf795e5a in QEvent::gatherHit (this=0x16eaf0270) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:588
    #5  0x00007fffcf79678f in QEvent::gatherComponent_ (this=0x16eaf0270, comp=256) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:653
    #6  0x00007fffcf796491 in QEvent::gatherComponent (this=0x16eaf0270, comp=256) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:634
    #7  0x00007fffcf33085d in SEvt::gather (this=0x16ba60800) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2813
    #8  0x00007fffd2e7c6b3 in G4CXOpticks::simulate (this=0x7951ca0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:495
    #9  0x00007fffd2089d22 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd79b0, eventID=0)


    (gdb) f 8
    #8  0x00007fffd2e7c6b3 in G4CXOpticks::simulate (this=0x7951ca0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:495
    495	    sev->gather();           // downloads components configured by SEventConfig::CompMask 
    (gdb) list
    490	    unsigned num_genstep = sev->getNumGenstepFromGenstep(); 
    491	    unsigned num_photon  = sev->getNumPhotonCollected(); 
    492	
    493	    qs->simulate(eventID);   // GPU launch doing generation and simulation here 
    494	
    495	    sev->gather();           // downloads components configured by SEventConfig::CompMask 
    496	    // save would gather, but need to do that anyhow even when not saving 
    497	
    498	    unsigned num_hit = sev->getNumHit() ; 
    499	
    (gdb) f 7
    #7  0x00007fffcf33085d in SEvt::gather (this=0x16ba60800) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2813
    2813	        NP* a = provider->gatherComponent(cmp); 
    (gdb) p cmp
    $1 = 256
    (gdb) f 6
    #6  0x00007fffcf796491 in QEvent::gatherComponent (this=0x16eaf0270, comp=256) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:634
    634	    NP* a = proceed ? gatherComponent_(comp) : nullptr ;
    (gdb) p comp
    $2 = 256
    (gdb) f 5
    #5  0x00007fffcf79678f in QEvent::gatherComponent_ (this=0x16eaf0270, comp=256) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:653
    653	        case SCOMP_HIT:       a = gatherHit()      ; break ;   
    (gdb) f 4
    #4  0x00007fffcf795e5a in QEvent::gatherHit (this=0x16eaf0270) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:588
    588	    assert( evt->num_photon ); 
    (gdb) p *evt
    $3 = {static genstep_itemsize = 24, static genstep_numphoton_offset = 3, static w_lo = 60, static w_hi = 820, static w_center = 440, static w_extent = 380, 
      center_extent = {x = 0, y = 0, z = 0, w = 1000}, time_domain = {x = 0, y = 10}, wavelength_domain = {x = 440, y = 380}, max_genstep = 1000000, max_photon = 10000, 
      max_simtrace = 3000000, max_bounce = 31, max_record = 32, max_rec = 32, max_seq = 32, max_prd = 32, max_tag = 1, max_flat = 1, max_aux = 32, max_sup = 1, 
      num_genstep = 1, num_seed = 100, num_hit = 32, num_photon = 0, num_record = 0, num_rec = 0, num_seq = 0, num_prd = 0, num_tag = 0, num_flat = 0, num_simtrace = 0, 
      num_aux = 0, num_sup = 0, genstep = 0x7fff12000000, seed = 0x7fff6a258800, hit = 0x0, photon = 0x7fff6a262600, record = 0x7fff6b600000, rec = 0x7fff6ca00000, 
      seq = 0x7fff6d000000, prd = 0x7fff6da00000, tag = 0x7fff6a2fea00, flat = 0x7fff17c00000, simtrace = 0x0, aux = 0x0, sup = 0x0}
    (gdb) 



::

    0310 double QSim::simulate(int eventID)
     311 {
     312     LOG(LEVEL);
     313 
     314     LOG_IF(error, event == nullptr) << " QEvent:event null " << desc()  ;
     315     if( event == nullptr ) std::raise(SIGINT) ;
     316     if( event == nullptr ) return -1. ;
     317 
     318     sev->beginOfEvent(eventID);  // set SEvt index and tees up frame gensteps for simtrace and input photon simulate running
     319 
     320     LOG(LEVEL) << desc() ;
     321     int rc = event->setGenstep() ;
     322     LOG_IF(error, rc != 0) << " QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate " ;
     323 
     324     double dt = rc == 0 && cx != nullptr ? cx->simulate_launch() : -1. ;
     325 
     326     sev->endOfEvent(eventID);
     327 
     328     return dt ;
     329 }


::

    1166 void SEvt::endOfEvent(int eventID)
    1167 {
    1168     int index_ = 1+eventID ;
    1169     endIndex(index_);
    1170     save();
    1171     clear();
    1172 }



Looks like the SEvt::clear done frm SEvt::endOfEvent sets num_photon to zero causing 
an assert when trying to gather again::

    577 NP* QEvent::gatherHit() const
    578 {
    579     // hasHit at this juncture is misleadingly always false, 
    580     // because the hits array is derived by *gatherHit_* which  selects from the photons 
    581 
    582     bool has_photon = hasPhoton();
    583 
    584     LOG_IF(LEVEL, !has_photon) << " gatherHit called when there is no photon array " ;
    585     if(!has_photon) return nullptr ;
    586 
    587     assert( evt->photon );
    588     assert( evt->num_photon );
    589     evt->num_hit = SU::count_if_sphoton( evt->photon, evt->num_photon, *selector );
    590 
    591     LOG(LEVEL)
    592          << " evt.photon " << evt->photon
    593          << " evt.num_photon " << evt->num_photon
    594          << " evt.num_hit " << evt->num_hit
    595          << " selector.hitmask " << selector->hitmask
    596          << " SEventConfig::HitMask " << SEventConfig::HitMask()
    597          << " SEventConfig::HitMaskLabel " << SEventConfig::HitMaskLabel()
    598          ;
    599 
    600     NP* hit = evt->num_hit > 0 ? gatherHit_() : nullptr ;
    601 
    602     return hit ;
    603 }




jcv junoSD_PMT_v2_Opticks::

    224 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    225 {
    226     G4CXOpticks* gx = G4CXOpticks::Get() ;
    227     gx->simulate(eventID) ;
    228 
    229     unsigned num_hit = SEvt::GetNumHit_EGPU() ;
    230 
    231     LOG(LEVEL)
    232         << " eventID " << eventID
    233         << " " << gx->descSimulate()
    234         << " num_hit " << num_hit
    235         ;
    236 
    237     int merged_count(0);
    238     int savehit_count(0);
    239     std::stringstream ss ;
    240 
    241     bool way_enabled = false ;
    242     U4Hit hit ;
    243     U4HitExtra hit_extra ;
    244     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    245     for(int idx=0 ; idx < int(num_hit) ; idx++)
    246     {
    247         U4HitGet::FromEvt_EGPU(hit, idx);
    248         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    249         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    250     }
    251 
    252     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;



HMM hits are special they need to survive the SEvt::clear ?::

     57 inline void U4HitGet::FromEvt(U4Hit& hit, unsigned idx, int eidx )
     58 {
     59     sphoton global, local  ;
     60     SEvt* sev = SEvt::Get(eidx);
     61     sev->getHit( global, idx);
     62 
     63     sphit ht ;
     64     sev->getLocalHit( ht, local,  idx);
     65 
     66     ConvertFromPhoton(hit, global, local, ht );
     67 }


::

    3271 const NP* SEvt::getHit() const {    return fold->get(SComp::HIT_) ; }

    3287 void SEvt::getHit(sphoton& p, unsigned idx) const
    3288 {
    3289     const NP* hit = getHit();
    3290     sphoton::Get(p, hit, idx );
    3291 }


gatherHit needs to copy the hit array somewhere else to avoid getting cleared at endOfEvent

* add NPFold::clear_except SEvt::clear_except to preseve "hit" beyond the save 


NOPE : git pull from bitbucket taking ages : try switch to github : but the clone gets time out 
--------------------------------------------------------------------------------------------------

Change url in je/junoenv-opticks.sh and do::

    N[blyth@localhost junoenv]$ bash junoenv opticks get
    = The junoenv is in /data/blyth/junotop/junoenv
    ...
    == setup-juno-basic-preq: Loading EXTLIB versions from /data/blyth/junotop/junoenv/collections/22.1.sh

    == setup-juno-opticks
    === junoenv-opticks: get
    ==== junoenv-opticks-get: url https://github.com/simoncblyth/opticks base opticks name opticks PWD /data/blyth/junotop
    git clone https://github.com/simoncblyth/opticks opticks
    Cloning into 'opticks'...
    fatal: unable to access 'https://github.com/simoncblyth/opticks/': Failed connect to github.com:443; Connection timed out
    ==== junoenv-opticks-get: FAILED
         


DONE : switch to rsync push
----------------------------

::

    bin/rsync_put_repo.sh



FIXED : endOfEvent genstep assert
-------------------------------------

::

    2023-08-01 23:23:35.491 INFO  [332711] [G4CXOpticks::simulate@450] [
    2023-08-01 23:23:35.491 INFO  [332711] [G4CXOpticks::simulate@451] G4CXOpticks::desc sim 0x7518f00 tr 0x7951ef0 wd 0x59f6250 gg 0xc210290 fd 0x1647777e0 cx Y qs Y
    2023-08-01 23:23:35.491 INFO  [332711] [SEvt::clear@1354] SEvt::clear
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:2837: void SEvt::gather_components(): Assertion `num == num_genstep' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf330366 in SEvt::gather_components (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2837
    #5  0x00007fffcf3305ed in SEvt::gather (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2875
    #6  0x00007fffcf331291 in SEvt::save (this=0x16ba5fec0, dir_=0x7fffcf41dcaa "$DefaultOutputDir") at /data/blyth/junotop/opticks/sysrap/SEvt.cc:3148
    #7  0x00007fffcf3306aa in SEvt::save (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2978
    #8  0x00007fffcf3282cf in SEvt::endOfEvent (this=0x16ba5fec0, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1179
    #9  0x00007fffcf76796e in QSim::simulate (this=0x16eb703f0, eventID=0) at /data/blyth/junotop/opticks/qudarap/QSim.cc:346
    #10 0x00007fffd2e7d3e3 in G4CXOpticks::simulate (this=0x74d5ee0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:457
    #11 0x00007fffd2089d22 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd7c10, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:227
    #12 0x00007fffd20898f1 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd7c10, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:164
    #13 0x00007fffd207cc3b in junoSD_PMT_v2::EndOfEvent (this=0x5bd7c70, HCE=0x7fff17d999c0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    #14 0x00007fffd9bbac95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] ()
       from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so


    (gdb) f 13
    #13 0x00007fffd207cc3b in junoSD_PMT_v2::EndOfEvent (this=0x5bd7c70, HCE=0x7fff17d999c0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1142
    1142	    m_jpmt_opticks->EndOfEvent(HCE, m_eventID );    
    (gdb) f 12
    #12 0x00007fffd20898f1 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5bd7c10, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:164
    164	        EndOfEvent_Simulate(eventID) ; 
    (gdb) f 11
    #11 0x00007fffd2089d22 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0x5bd7c10, eventID=0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:227
    227	    gx->simulate(eventID) ; 
    (gdb) f 10
    #10 0x00007fffd2e7d3e3 in G4CXOpticks::simulate (this=0x74d5ee0, eventID=0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:457
    457	    qs->simulate(eventID);   // GPU launch doing generation and simulation here 
    (gdb) f 9
    #9  0x00007fffcf76796e in QSim::simulate (this=0x16eb703f0, eventID=0) at /data/blyth/junotop/opticks/qudarap/QSim.cc:346
    346	    sev->endOfEvent(eventID);
    (gdb) list
    341	    LOG_IF(error, rc != 0) << " QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate " ; 
    342	
    343	    double dt = rc == 0 && cx != nullptr ? cx->simulate_launch() : -1. ;
    344	    //post_launch(); 
    345	
    346	    sev->endOfEvent(eventID);
    347	 
    348	    return dt ; 
    349	}
    350	
    (gdb) f 8
    #8  0x00007fffcf3282cf in SEvt::endOfEvent (this=0x16ba5fec0, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1179
    1179	    save();             
    (gdb) list
    1174	
    1175	void SEvt::endOfEvent(int eventID)
    1176	{
    1177	    int index_ = 1+eventID ;    
    1178	    endIndex(index_); 
    1179	    save();             
    1180	    clear_except("hit"); 
    1181	}
    1182	
    1183	
    (gdb) f 7
    #7  0x00007fffcf3306aa in SEvt::save (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2978
    2978	    save(dir); 
    (gdb) list
    2973	**/
    2974	
    2975	void SEvt::save() 
    2976	{
    2977	    const char* dir = DefaultDir(); 
    2978	    save(dir); 
    2979	}
    2980	void SEvt::saveExtra( const char* name, const NP* a  ) const 
    2981	{
    2982	    const char* dir = DefaultDir(); 
    (gdb) f 6
    #6  0x00007fffcf331291 in SEvt::save (this=0x16ba5fec0, dir_=0x7fffcf41dcaa "$DefaultOutputDir") at /data/blyth/junotop/opticks/sysrap/SEvt.cc:3148
    3148	    gather(); 
    (gdb) list
    3143	
    3146	void SEvt::save(const char* dir_) 
    3147	{
    3148	    gather(); 
    3149	
    3150	    LOG(LEVEL) << descComponent() ; 
    3151	    LOG(LEVEL) << descFold() ; 
    3152	

    (gdb) f 5
    #5  0x00007fffcf3305ed in SEvt::gather (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2875
    2875	    gather_components(); 
    (gdb) list
    2870	{
    2871	    LOG_IF(fatal, gather_done) << " gather_done ALREADY : SKIPPING " ; 
    2872	    if(gather_done) return ; 
    2873	    gather_done = true ;   // SEvt::setNumPhoton which gets called by adding gensteps resets this to false
    2874	
    2875	    gather_components(); 
    2876	}
    2877	

    (gdb) f 4
    #4  0x00007fffcf330366 in SEvt::gather_components (this=0x16ba5fec0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2837
    2837	            assert( num == num_genstep );   
    (gdb) list
    2832	
    2833	        int num = a->shape[0] ;  
    2834	        
    2835	        if(SComp::IsGenstep(cmp))
    2836	        {
    2837	            assert( num == num_genstep );   
    2838	        }
    2839	        else if(SComp::IsPhoton(cmp))
    2840	        {
    2841	            assert( num == num_photon );   

    (gdb) p num
    $1 = 1
    (gdb) p num_genstep
    $2 = 0
    (gdb) 



HUH, some extra SEvt::clear before the gather ?::

    export SEvt=INFO ; BP=SEvt::clear ntds3_noxj


Probably one of those statics to weed. Interference between the two SEvt.  

Nope its not that... the clear is called by QEvent::setGenstep

::

    (gdb) f 1
    #1  0x00007fffcf792e95 in QEvent::setGenstep (this=0x16efeedf0) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:165
    165	    sev->clear();  // clear the quad6 vector, ready to collect more genstep
    (gdb) list
    160	int QEvent::setGenstep()  // onto device
    161	{
    162	    LOG(LEVEL); 
    163	
    164	    NP* gs = sev->gatherGenstep();
    165	    sev->clear();  // clear the quad6 vector, ready to collect more genstep
    166	
    167	    LOG_IF(fatal, gs == nullptr ) << "Must SEvt/addGenstep before calling QEvent::setGenstep " ;
    168	    //if(gs == nullptr) std::raise(SIGINT); 
    169	
    (gdb) f 2
    #2  0x00007fffcf767846 in QSim::simulate (this=0x16f0749b0, eventID=0) at /data/blyth/junotop/opticks/qudarap/QSim.cc:340
    340	    int rc = event->setGenstep() ; 
    (gdb) list
    335	    if( event == nullptr ) return -1. ; 
    336	
    337	    sev->beginOfEvent(eventID);  // set SEvt index and tees up frame gensteps for simtrace and input photon simulate running
    338	
    339	    LOG(LEVEL) << desc() ;  
    340	    int rc = event->setGenstep() ; 
    341	    LOG_IF(error, rc != 0) << " QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate " ; 
    342	
    343	    double dt = rc == 0 && cx != nullptr ? cx->simulate_launch() : -1. ;
    344	    //post_launch(); 
    (gdb) 



Rejig SEvt::gather_components to get its stats from the fold, not from the vectors
that are already cleared. 


FIXED : endIndex assert coming from the CPU event with its negative index
----------------------------------------------------------------------------

::

    2023-08-02 00:09:01.295 INFO  [347049] [SEvt::save@3165] [ save_fold.save /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::save@3167] ] save_fold.save /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::saveLabels@3188] [ dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::saveLabels@3199] ] dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::saveFrame@3204] [ dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::saveFrame@3206] ] dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::clear_except@1378] SEvt::clear_except
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::clear_except@1380] [
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::setNumPhoton@1646]  evt->num_photon 0 evt->num_tag 0 evt->num_flat 0
    2023-08-02 00:09:01.297 INFO  [347049] [SEvt::clear_except@1387] ]
    2023-08-02 00:09:01.297 INFO  [347049] [G4CXOpticks::simulate@458] ]
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 44 hcMuon 0 hcOpticks 32 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:1402: void SEvt::endIndex(int): Assertion `index == index_' failed.

    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf329514 in SEvt::endIndex (this=0xb56720, index_=1) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1402
    #5  0x00007fffcf328311 in SEvt::endOfEvent (this=0xb56720, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1179
    #6  0x00007fffd296e62c in U4Recorder::EndOfEventAction (this=0xb2d370, event=0x7fff17d91680) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:223
    #7  0x00007fffcdc8387a in U4RecorderAnaMgr::EndOfEventAction (this=0x93f2f0, evt=0x7fff17d91680)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:32
    #8  0x00007fffce6c9bd1 in MgrOfAnaElem::EndOfEventAction (this=0x7fffce8d8b00 <MgrOfAnaElem::instance()::s_mgr>, evt=0x7fff17d91680)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53
    #9  0x00007fffcdfb20dd in LSExpEventAction::EndOfEventAction (this=0x597ccd0, evt=0x7fff17d91680)



    (gdb) f 6
    #6  0x00007fffd296e62c in U4Recorder::EndOfEventAction (this=0xb2d370, event=0x7fff17d91680) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:223
    223	    sev->endOfEvent(eventID_);  // does save and clear
    (gdb) list
    218	    assert( eventID == eventID_ ); 
    219	
    220	    sev->add_array("U4R.npy", MakeMetaArray() ); 
    221	    sev->addEventConfigArray(); 
    222	
    223	    sev->endOfEvent(eventID_);  // does save and clear
    224	
    225	    const char* savedir = sev->getSaveDir() ; 
    226	    LOG(info) << " savedir " << ( savedir ? savedir : "-" );
    227	    SaveMeta(savedir);  
    (gdb) p eventID_
    $1 = 0
    (gdb) p eventID
    $2 = 0
    (gdb) f 5
    #5  0x00007fffcf328311 in SEvt::endOfEvent (this=0xb56720, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1179
    1179	    endIndex(index_); 
    (gdb) p index_
    $3 = 1
    (gdb) list
    1174	**/
    1175	
    1176	void SEvt::endOfEvent(int eventID)
    1177	{
    1178	    int index_ = 1+eventID ;    
    1179	    endIndex(index_); 
    1180	    save();             
    1181	    clear_except("hit"); 
    1182	}
    1183	
    (gdb) f 4
    #4  0x00007fffcf329514 in SEvt::endIndex (this=0xb56720, index_=1) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1402
    1402	    assert( index == index_ );  
    (gdb) p index
    $4 = -1
    (gdb) p index_
    $5 = 1
    (gdb) list 
    1397	    index = index_ ; 
    1398	    t_BeginOfEvent = stamp::Now();  // moved here from the static 
    1399	}
    1400	void SEvt::endIndex(int index_)
    1401	{ 
    1402	    assert( index == index_ );  
    1403	    t_EndOfEvent = stamp::Now();  
    1404	}
    1405	
    1406	int SEvt::getIndex() const 
    (gdb) 




CPU event assert from lack of hits
-------------------------------------


::

    2023-08-02 00:22:12.934 INFO  [360361] [SEvt::saveFrame@3212] ] dir /tmp/blyth/opticks/GEOM/V1J009/ntds3/ALL1/p001
    2023-08-02 00:22:12.934 INFO  [360361] [SEvt::clear_except@1378] SEvt::clear_except
    2023-08-02 00:22:12.934 INFO  [360361] [SEvt::clear_except@1380] [
    2023-08-02 00:22:12.934 INFO  [360361] [SEvt::setNumPhoton@1646]  evt->num_photon 0 evt->num_tag 0 evt->num_flat 0
    2023-08-02 00:22:12.934 INFO  [360361] [SEvt::clear_except@1387] ]
    2023-08-02 00:22:12.934 INFO  [360361] [G4CXOpticks::simulate@458] ]
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 44 hcMuon 0 hcOpticks 32 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    2023-08-02 00:22:12.938 INFO  [360361] [SEvt::gather_components@2852]  k         genstep a  <f4(1, 6, 4, )
    2023-08-02 00:22:12.946 INFO  [360361] [SEvt::gather_components@2852]  k          photon a  <f4(100, 4, 4, )
    2023-08-02 00:22:12.947 INFO  [360361] [SEvt::gather_components@2852]  k          record a  <f4(100, 32, 4, 4, )
    2023-08-02 00:22:12.947 INFO  [360361] [SEvt::gather_components@2852]  k             seq a  <u8(100, 2, 2, )
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k             prd a  <f4(100, 32, 2, 4, )
    2023-08-02 00:22:12.948 ERROR [360361] [SEvt::gatherHit@2529]  not yet implemented for hostside running : change CompMask with SEventConfig to avoid 
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k             hit a -
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k          domain a  <f4(2, 4, 4, )
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k        inphoton a  <f4(100, 4, 4, )
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k             tag a  <u8(100, 4, )
    2023-08-02 00:22:12.948 INFO  [360361] [SEvt::gather_components@2852]  k            flat a  <f4(100, 64, )
    2023-08-02 00:22:12.949 INFO  [360361] [SEvt::gather_components@2852]  k             aux a  <f4(100, 32, 4, 4, )
    2023-08-02 00:22:12.949 INFO  [360361] [SEvt::gather_components@2852]  k             sup a  <f4(100, 6, 4, )
    2023-08-02 00:22:12.949 INFO  [360361] [SEvt::gather_components@2869]  num_comp 12 num_genstep 1 num_photon 100 num_hit -1 gather_total 1 genstep_total 1 photon_total 100 hit_total 4294967295
    python: /data/blyth/junotop/opticks/sysrap/SEvt.cc:2882: void SEvt::gather_components(): Assertion `num_hit > -1' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffcf3307aa in SEvt::gather_components (this=0xb568d0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2882
    #5  0x00007fffcf330923 in SEvt::gather (this=0xb568d0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2904
    #6  0x00007fffcf3315c7 in SEvt::save (this=0xb568d0, dir_=0x7fffcf41dfea "$DefaultOutputDir") at /data/blyth/junotop/opticks/sysrap/SEvt.cc:3154
    #7  0x00007fffcf3309e0 in SEvt::save (this=0xb568d0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:2984
    #8  0x00007fffcf32831d in SEvt::endOfEvent (this=0xb568d0, eventID=0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1180
    #9  0x00007fffd296e62c in U4Recorder::EndOfEventAction (this=0xb2d520, event=0x7fff18949bc0) at /data/blyth/junotop/opticks/u4/U4Recorder.cc:223
    #10 0x00007fffcdc8387a in U4RecorderAnaMgr::EndOfEventAction (this=0x93f4a0, evt=0x7fff18949bc0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/U4RecorderAnaMgr.cc:32
    #11 0x00007fffce6c9bd1 in MgrOfAnaElem::EndOfEventAction (this=0x7fffce8d8b00 <MgrOfAnaElem::instance()::s_mgr>, evt=0x7fff18949bc0)
        at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/MgrOfAnaElem.cc:53

