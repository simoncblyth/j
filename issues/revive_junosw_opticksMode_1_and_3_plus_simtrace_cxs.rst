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
6. TODO : qpmt/QPMT Stack AOI scanning based off SPMT.h full data, like SPMT_test but on GPU  
7. TODO : Bringing C4CustomART::doIt to GPU, by integrating qpmt with new CSGFoundry special surface enum 

TODO : qpmt/QPMT TMM Stack calc AOI scanning based off SPMT.h full data, like SPMT_test but on GPU
------------------------------------------------------------------------------------------------------


TODO : Bring C4CustomART::doIt to GPU, by integrating qpmt with new CSGFoundry special surface enum
------------------------------------------------------------------------------------------------------


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



TODO : generalise qsim::propagate for special surfaces
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


TODO : commit persisted jpmt changes into another branch and MR
-----------------------------------------------------------------------

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


HMM : Skip WPMTs SPMTs from the arrays needed for QPMT ?
----------------------------------------------------------

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



