G4CXAppTest_comparison
========================

Context
--------

* previous :doc:`G4CXAppTest_shakedown`


Standalone bi-simulation workflow
------------------------------------

::

    o ; ./bin/rsync_put.sh                # laptop
    o ; oo                                # workstation  
    gxt ; ./G4CXAppTest.sh                # workstation
    gxt ; ./G4CXAppTest.sh grab           # laptop
    PICK=AB MODE=2 ./G4CXAppTest.sh ana   # laptop

    GEOM get # laptop


* When updating qsim.h need to build both qu and cx 


Initial issues
---------------

1. Looks like B (on workstation) is POM:0 with photons not entering PMT with Custom4 "0.1.5"
2. Bizarrely B on laptop looks more normal POM:1 with current Custom4 "0.1.6" 

3. A has no SD, so no hits, missing GBndLib__SENSOR_BOUNDARY_LIST ?

   * after rejig of U4SensorIdentifierDefault::getGlobalIdentity now get SD and hits, but discrepant 


Overview
----------

* DONE : U4SensorIdentifierDefault::getGlobalIdentity rejig giving SD and hits to A and avoiding lpmtid -1  
* DONE : GPU side PIDX dumping single photons down to ARTE level  
* TODO : CPU side PIDX dumping single photons down to ARTE level  
* TODO : tag Custom4 0.1.6 and get that going on workstation (with E_s2 bug fix)


After rejig of U4SensorIdentifierDefault::getGlobalIdentity
--------------------------------------------------------------

::

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][:25]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT SD                                                                                       ' ' 0' '  4391   5108' '54.1203' '   136    127']
     [' 1' 'TO BT SA                                                                                       ' ' 1' '  3760   4474' '61.9135' '   134    129']
     [' 2' 'TO BT BR BT SA                                                                                 ' ' 2' '   257     25' '190.8652' '  1678    150']
     [' 3' 'TO BT BT SR SA                                                                                 ' ' 3' '   230      0' '230.0000' '  1641     -1']
     [' 4' 'TO SA                                                                                          ' ' 4' '   228    224' ' 0.0354' '     0      0']
     [' 5' 'TO BT BT SA                                                                                    ' ' 5' '   180      3' '171.1967' '  1882   4853']
     [' 6' 'TO BT BT SR BT BT SA                                                                           ' ' 6' '   179      0' '179.0000' '  2684     -1']
     [' 7' 'TO BR SA                                                                                       ' ' 7' '   150    104' ' 8.3307' '   116    116']
     [' 8' 'TO BT BT SR BR SR SA                                                                           ' ' 8' '    54      0' '54.0000' '  3322     -1']
     [' 9' 'TO BT AB                                                                                       ' ' 9' '    49     26' ' 7.0533' '   201    438']
     ['10' 'TO BT BR BR BR BR BR SA                                                                        ' '10' '    48      0' '48.0000' '   326     -1']
     ['11' 'TO BT BR BR BR BR SA                                                                           ' '11' '    42      0' '42.0000' '   135     -1']
     ['12' 'TO BT BT SR BR SA                                                                              ' '12' '    36      0' '36.0000' '  3383     -1']
     ['13' 'TO BT BR BR BR BR BR BR SA                                                                     ' '13' '    36      0' '36.0000' '   805     -1']
     ['14' 'TO BT BT SR BR SR SR SA                                                                        ' '14' '    26      0' ' 0.0000' '  3418     -1']
     ['15' 'TO BT BR BR SD                                                                                 ' '15' '    22      0' ' 0.0000' '  1352     -1']
     ['16' 'TO BT BT SR BR SR BT BT SA                                                                     ' '16' '    20      0' ' 0.0000' '  3734     -1']
     ['17' 'TO AB                                                                                          ' '17' '    15     19' ' 0.4706' '    39     14']
     ['18' 'TO BT BT SR SR SR SR SR SR BR BR BR BR SA                                                      ' '18' '    18      0' ' 0.0000' '  2270     -1']


This is still with Custom4 0.1.5

::

    In [2]: a.f.NPFold_meta
    Out[2]: 
    source:G4CXOpticks::init_SEvt
    creator:G4CXAppTest
    stamp:1691263497354932
    stampFmt:2023-08-06T03:24:57.354932
    uname:Linux localhost.localdomain 3.10.0-957.10.1.el7.x86_64 #1 SMP Mon Mar 18 15:06:45 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
    HOME:/home/blyth
    USER:blyth
    PWD:/data/blyth/junotop/opticks/g4cx/tests
    CHECK:rain_line
    LAYOUT:one_pmt
    VERSION:0
    GEOM:FewPMT
    ${GEOM}_GEOMList:nnvtLogicalPMT
    C4Version:0.1.5

    In [3]: b.f.NPFold_meta
    Out[3]: 
    source:U4Recorder::init_SEvt
    creator:G4CXAppTest
    stamp:1691263495165218
    stampFmt:2023-08-06T03:24:55.165218
    uname:Linux localhost.localdomain 3.10.0-957.10.1.el7.x86_64 #1 SMP Mon Mar 18 15:06:45 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
    HOME:/home/blyth
    USER:blyth
    PWD:/data/blyth/junotop/opticks/g4cx/tests
    CHECK:rain_line
    LAYOUT:one_pmt
    VERSION:0
    GEOM:FewPMT
    ${GEOM}_GEOMList:nnvtLogicalPMT
    C4Version:0.1.5


NEXT : tag Custom4 0.1.6 and get that operational on workstation 
-------------------------------------------------------------------

Differences between 0.1.5 and currently untagged "0.1.6" 

* polarization E_s2 bug fix could have cause large changes
* BUT why the A/B difference : would have expected the bug to 
  have equal effect on A and B ? 


::

    epsilon:~ blyth$ cd /usr/local/opticks_externals/custom4/
    epsilon:custom4 blyth$ diff -r --brief 0.1.5 0.1.6 
    Files 0.1.5/include/Custom4/C4MultiLayrStack.h and 0.1.6/include/Custom4/C4MultiLayrStack.h differ
    Files 0.1.5/include/Custom4/C4Version.h and 0.1.6/include/Custom4/C4Version.h differ
    Only in 0.1.5/lib: Custom4-0.1.5
    Only in 0.1.6/lib: Custom4-0.1.6
    Files 0.1.5/lib/libCustom4.dylib and 0.1.6/lib/libCustom4.dylib differ
    epsilon:custom4 blyth$ 

    epsilon:custom4 blyth$ diff 0.1.5/include/Custom4/C4MultiLayrStack.h 0.1.6/include/Custom4/C4MultiLayrStack.h 
    602a603,614
    >       
    >     /*
    >     BUG FIX July 2023: 
    >         using norm(stst) to give sin_theta*sin_theta is incorrect
    >         because stst is already squared and the norm squares it again 
    >         Found that bug, because it leads to SF of 2. which is nonsensical (SF must be from 0. to 1. ) 
    >         which gave a polarization specific A of greater than 1. 
    >           
    >     BUG: const F E_s2 = norm(stst)   > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/norm(stst) : zero ;
    >     OK : const F E_s2 = l0.st.real() > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/(l0.st.real()*l0.st.real()) : zero ;
    >     */
    >     const F E_s2 = stst.real() > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/stst.real() : zero ;
    604d615
    <     const F E_s2 = norm(stst) > zero ? (dot_pol_cross_mom_nrm*dot_pol_cross_mom_nrm)/norm(stst) : zero ;
    607a619,624
    > #ifdef MOCK_CURAND_DEBUG
    >     printf("//stack.calc dot_pol_cross_mom_nrm %7.3f norm(stst) %7.3f l0.st (%7.3f,%7.3f) E_s2 %7.3f \n", 
    >             dot_pol_cross_mom_nrm, norm(stst), l0.st.real(), l0.st.imag(), E_s2 ); 
    > #endif
    > 
    > 





Single photon PIDX debug 
--------------------------

::

    In [3]: a.f.record[:,0,0]
    Out[3]: 
    array([[ 260.   ,    0.   ,  195.   ,    0.   ],
           [ 259.948,    0.   ,  195.   ,    0.   ],
           [ 259.896,    0.   ,  195.   ,    0.   ],
           [ 259.844,    0.   ,  195.   ,    0.   ],
           [ 259.792,    0.   ,  195.   ,    0.   ],
           ...,
           [-259.74 ,    0.   ,  195.   ,    0.   ],
           [-259.792,    0.   ,  195.   ,    0.   ],
           [-259.844,    0.   ,  195.   ,    0.   ],
           [-259.896,    0.   ,  195.   ,    0.   ],
           [-259.948,    0.   ,  195.   ,    0.   ]], dtype=float32)

    In [5]: a.f.record[5000,0]
    Out[5]: 
    array([[  0.,   0., 195.,   0.],
           [  0.,   0.,  -1.,   0.],
           [ -0.,  -1.,  -0., 420.],
           [  0.,   0.,   0.,   0.]], dtype=float32)

    In [6]: a.f.record[5001,0]
    Out[6]: 
    array([[ -0.052,   0.   , 195.   ,   0.   ],
           [  0.   ,   0.   ,  -1.   ,   0.   ],
           [ -0.   ,  -1.   ,  -0.   , 420.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)


    In [7]: a.q[5000]
    Out[7]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [8]: a.q[5001]
    Out[8]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [9]: a.q[5000-10:5000+10]
    Out[9]: 
    array([[b'TO BT BT SA                                                                                     '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SA                                                                                     ']], dtype='|S96')


    In [9]: a.q[5000-10:5000+10]
    Out[9]: 
    array([[b'TO BT BT SA                                                                                     '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SA                                                                                     ']], dtype='|S96')

    In [10]: b.f.record[5000,0]
    Out[10]: 
    array([[  0.,   0., 195.,   0.],
           [  0.,   0.,  -1.,   0.],
           [ -0.,  -1.,  -0., 420.],
           [  0.,   0.,   0.,   0.]], dtype=float32)

    In [11]: b.q[5000-10:5000+10]
    Out[11]: 
    array([[b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        ']], dtype='|S96')



    In [14]: a.q[5001]
    Out[14]: array([b'TO BT SA                                                                                        '], dtype='|S96')

    In [13]: b.q[5001]
    Out[13]: array([b'TO BT SD                                                                                        '], dtype='|S96')



Pick PIDX 5001 : Aim to dump ART values to see whats up
----------------------------------------------------------

::

    //qsim.propagate idx 5001 bnc 0 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.92535669 logf(u_absorption) -0.07757594 absorption_length 37213.9219 absorption_distance 2886.905029 
    //qsim.propagate idx 5001 bounce 0 command 3 flag 0 s.optical.x 0 s.optical.y 1 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 1 
    //qsim.propagate_at_boundary idx 5001 nrm   (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_at_boundary idx 5001 mom_0 (    0.0000     0.0000    -1.0000) 
    //qsim.propagate_at_boundary idx 5001 pol_0 (   -0.0000    -1.0000    -0.0000) 
    //qsim.propagate_at_boundary idx 5001 c1     1.0000 normal_incidence 0 
    //qsim.propagate_at_boundary idx 5001 normal_incidence 0 p.pol (   -0.0000,   -1.0000,   -0.0000) p.mom (    0.0000,    0.0000,   -1.0000) o_normal (   -0.0001,    0.0000,    1.0000)
    //qsim.propagate_at_boundary idx 5001 TransCoeff     0.9979 n1c1     1.3540 n2c2     1.4843 E2_t (   -0.9541,    0.0000) A_trans (    0.0000,    1.0000,    0.0000) 
    //qsim.propagate_at_boundary idx 5001 u_reflect     0.5400 TransCoeff     0.9979 reflect 0 
    //qsim.propagate_at_boundary idx 5001 reflect 0 tir 0 TransCoeff     0.9979 u_reflect     0.5400 
    //qsim.propagate_at_boundary idx 5001 mom_1 (    0.0000     0.0000    -1.0000) 
    //qsim.propagate_at_boundary idx 5001 pol_1 (    0.0000    -1.0000     0.0000) 
    //qsim.propagate idx 5001 bnc 1 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.81189805 logf(u_absorption) -0.20838045 absorption_length  1562.9586 absorption_distance 325.690002 
    //qsim.propagate idx 5001 bounce 1 command 3 flag 0 s.optical.x 7 s.optical.y 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 lposcost   1.000 
    //qsim.propagate_at_surface_CustomART idx 5001 ARTE (   0.565   0.223   0.777   0.000 ) u_theAbsorption    0.369 action 1 

* SMOKING GUN : ARE GETTING theEfficiency zero 

::

    //qsim.propagate_at_boundary idx 5001 pol_1 (    0.0000    -1.0000     0.0000) 
    //qsim.propagate idx 5001 bnc 1 cosTheta    -1.0000 dir (    0.0000     0.0000    -1.0000) nrm (   -0.0001     0.0000     1.0000) 
    //qsim.propagate_to_boundary[ idx 5001 u_absorption 0.81189805 logf(u_absorption) -0.20838045 absorption_length  1562.9586 absorption_distance 325.690002 
    //qsim.propagate idx 5001 bounce 1 command 3 flag 0 s.optical.x 7 s.optical.y 4 
    //qsim.propagate.WITH_CUSTOM4 idx 5001  BOUNDARY ems 4 lposcost   1.000 
    //qsim::propagate_at_surface_CustomART p.mom                 (  0.000   0.000  -1.000) 
    //qsim::propagate_at_surface_CustomART p.pol                 (  0.000  -1.000   0.000) 
    //qsim::propagate_at_surface_CustomART normal                ( -0.000   0.000   1.000) 
    //qsim::propagate_at_surface_CustomART cross_mom_nrm         (  0.000   0.000   0.000) 
    //qsim::propagate_at_surface_CustomART dot_pol_cross_mom_nrm:  -0.000 
    //qsim::propagate_at_surface_CustomART minus_cos_theta         -1.000 
    //qsim::propagate_at_surface_CustomART idx 5001 lpmtid -1 wl 420.000 mct  -1.000 dpcmn  -0.000 ARTE (   0.565   0.223   0.777   0.000 ) 
    //qsim.propagate_at_surface_CustomART idx 5001 lpmtid -1 ARTE (   0.565   0.223   0.777   0.000 ) u_theAbsorption    0.369 action 1 
    2023-08-05 20:53:31.051 INFO  [207652] [QEvent::gatherComponent@643] [ cmp 2


* HMM : lpmtid -1 

::

    1469 inline QSIM_METHOD int qsim::propagate_at_surface_CustomART(unsigned& flag, curandStateXORWOW& rng, sctx& ctx) const
    1470 {
    1471     const sphoton& p = ctx.p ;
    1472     const float3* normal = (float3*)&ctx.prd->q0.f.x ;  // geometrical outwards normal 
    1473     int lpmtid = ctx.prd->identity() - 1 ;  // identity comes from optixInstance.instanceId where 0 means not-a-sensor  
    1474     float minus_cos_theta = dot(p.mom, *normal); 
    1475     float dot_pol_cross_mom_nrm = dot(p.pol,cross(p.mom,*normal)) ;
    1476     

    447 extern "C" __global__ void __closesthit__ch()
    448 {
    449     unsigned iindex = optixGetInstanceIndex() ;    // 0-based index within IAS
    450     unsigned instance_id = optixGetInstanceId() ;  // user supplied instanceId, see IAS_Builder::Build 
    451     unsigned prim_idx = optixGetPrimitiveIndex() ; // GAS_Builder::MakeCustomPrimitivesBI_11N  (1+index-of-CSGPrim within CSGSolid/GAS)
    452 
    453     //unsigned identity = (( prim_idx & 0xffff ) << 16 ) | ( instance_id & 0xffff ) ; 
    454     unsigned identity = instance_id ;  // CHANGED July 2023, as now carrying sensor_identifier, see sysrap/sqat4.h 
    455 

    366     QAT4_METHOD int get_IAS_OptixInstance_instanceId() const
    367     {
    368         //const unsigned& ins_idx = q0.u.w ;  
    369         //return ins_idx ; 
    370         const int& sensor_identifier = q2.i.w ;
    371         assert( sensor_identifier >= 0 );  // 0 means not a sensor GPU side, so subtract 1 to get actual sensorId
    372         return sensor_identifier ;
    373     }


* DONE: added protection against not-a-sensor (from identity 0) which yields lpmtid -1 
* TODO: find why getting not-a-sensor


ems
-----


::

     08 enum {
      9     smatsur_Material                       = 0,
     10     smatsur_NoSurface                      = 1,
     11     smatsur_Surface                        = 2,
     12     smatsur_Surface_zplus_sensor_A         = 3,
     13     smatsur_Surface_zplus_sensor_CustomART = 4,
     14     smatsur_Surface_zminus                 = 5
     15 
     16 };


DONE : Added qsim.h handling for lpmtid < 0 
-------------------------------------------------

* ~/opticks/notes/issues/qsim_propagate_at_surface_CustomART_NOT-A-SENSOR_error.rst


DONE : rejig U4SensorIdentifierDefault::getGlobalIdentity 
-----------------------------------------------------------

* now depends on (pv,ppv) to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST
* this was needed because the small FewPMT geometry with 1 PMT is purely global with no instances 

::

    epsilon:opticks blyth$ git commit -m "rejig U4SensorIdentifierDefault::getGlobalIdentity to depend on pv ppv to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST "
    [master 151de19ce] rejig U4SensorIdentifierDefault::getGlobalIdentity to depend on pv ppv to allow forming a boundary name to compare with envvar configured list U4SensorIdentifierDefault__GLOBAL_SENSOR_BOUNDARY_LIST
     13 files changed, 274 insertions(+), 32 deletions(-)
     create mode 100644 u4/U4Boundary.h
    epsilon:opticks blyth$ git push 


This avoids the lpmtid -1 


