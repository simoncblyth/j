InputPhotonsCheck/InputPhotonsCheck_WP_10percent_more_SA_for_A.rst
=====================================================================

Overview
----------

* Prior :doc:`InputPhotonsCheck/InputPhotonsCheck_WP`
* Next :doc:`InputPhotonsCheck/InputPhotonsCheck_WP_poolcover_deviant`


After another SPMT.h qeScale_v fix 
-------------------------------------


::
         
    SABHit  a_nhit : (   29562 +-  171 )  b_nhit:(    29680 +-  172 )  a/b: (  0.996 +-  0.012 )  b/a: (  1.004 +-  0.012)  [assume uncorr.]

    AB
    [sseq_index_ab::desc u_size 868 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   117.7114 ndf 60.0000 sum/ndf     1.9619 sseq_index_ab_chi2_ABSUM_MIN:40.0000
        TO BT BT BT BT SA                                                                                :   30563  30517 :     0.0346 : Y :       2      0 :   
        TO BT BT BT BT EC                                                                                :   29246  29368 :     0.2539 : Y :       1      4 :   
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9621   9789 :     1.4541 : Y :       6      2 :   
        TO BT BT BT BT BT SR SA                                                                          :    7688   7791 :     0.6854 : Y :   10622  10360 :   
        TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    6782   6908 :     1.1597 : Y :   10830  10807 :   
        TO BT BT BT BT BT SA                                                                             :    2060   1949 :     3.0733 : Y :    8707   8505 :   
        TO BT BT BT BT EX                                                                                :    1982   1838 :     5.4283 : Y :       0     26 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :    1739   1734 :     0.0072 : Y :   20717  20592 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    1552   1515 :     0.4464 : Y :   20911  20924 :   
        TO BT BT BT BT BT SR BR SA                                                                       :     911    891 :     0.2220 : Y :   10942  10885 :   
        TO BT BT BR BT BT SA                                                                             :     674    678 :     0.0118 : Y :      16      9 :   
        TO BT BT BT BR BT BT BT SA                                                                       :     590    579 :     0.1035 : Y :       4      1 :   
 


NOW FIXED : After fixing WaterPoolConstruction HIERARCHY CONFIG observe 10% hit deficit on A side
----------------------------------------------------------------------------------------------------

BUT hit discrepancy::

    INFO:opticks.ana.pvplt:SEvt.__init__  symbol b pid -1 opt  off [0. 0. 0.] 
    SEvt symbol a pid -1 opt  off [0. 0. 0.] a.f.base /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/A000 
    SEvt symbol b pid -1 opt  off [0. 0. 0.] b.f.base /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/B000 
     NOT doing ab = SAB(a,b) # do that with : export SAB=1
    [--- abh = SABHit(a,b) ----
    ]--- abh = SABHit(a,b) ----
    [----- repr(abh) 


    SABHit  a_nhit : (   26756 +-  163 )  b_nhit:(    29680 +-  172 )  a/b: (  0.901 +-  0.011 )  b/a: (  1.109 +-  0.013)  [assume uncorr.]


    ]----- repr(abh) 


Looks like efficiency difference for WP_PMT ? (Had S_PMT issue like that recently from oldcontiguousidx/contiguousidx mixup)::

    AB
    [sseq_index_ab::desc u_size 868 NUM_MAX 40 num 40 opt BRIEF mode 6sseq_index_ab_chi2::desc sum   408.8915 ndf 60.0000 sum/ndf     6.8149 sseq_index_ab_chi2_ABSUM_MIN:40.0000
    :r:`TO BT BT BT BT SA                                                                                :   33552  30517 :   143.7704 : Y :       2      0 : DEVIANT  `
    :r:`TO BT BT BT BT EC                                                                                :   26462  29368 :   151.2598 : Y :       1      4 : DEVIANT  `
        TO BT BT BT BT BR BT BT BT BT SA                                                                 :    9621   9789 :     1.4541 : Y :       6      2 :   
        TO BT BT BT BT BT SR SA                                                                          :    7688   7791 :     0.6854 : Y :   10622  10360 :   
        TO BT BT BT BT BT SR BT BT BT BT BT SA                                                           :    6782   6908 :     1.1597 : Y :   10830  10807 :   
        TO BT BT BT BT BT SA                                                                             :    2060   1949 :     3.0733 : Y :    8707   8505 :   
        TO BT BT BT BT EX                                                                                :    1777   1838 :     1.0293 : Y :       0     26 :   
        TO BT BT BT BT BT SR BR SR SA                                                                    :    1739   1734 :     0.0072 : Y :   20717  20592 :   
        TO BT BT BT BT BT SR BR SR BT BT BT BT BT SA                                                     :    1552   1515 :     0.4464 : Y :   20911  20924 :   
        TO BT BT BT BT BT SR BR SA                                                                       :     911    891 :     0.2220 : Y :   10942  10885 :   
        TO BT BT BR BT BT SA                                                                             :     674    678 :     0.0118 : Y :      16      9 :   
        TO BT BT BT BR BT BT BT SA                                                                       :     590    579 :     0.1035 : Y :       4      1 :   
        TO BT BR BT SA                                                                                   :     505    507 :     0.0040 : Y :      23     17 :   
        TO BT BT BT BT BT SR BR SR BR SR SA                                                              :     507    484 :     0.5338 : Y :   21826  21759 :   

::

    In [8]: 33552 - 30517, 26462 - 29368
    Out[8]: (3035, -2906)

    In [6]: 33552 + 26462
    Out[6]: 60014

    In [7]: 30517 + 29368
    Out[7]: 59885


Actually issue looks like A side theEfficiency too low, not collectionEfficiency (which messes with the EC/EX split)
as A side is getting more SURFACE_ABSORB::

    1841     const float& theAbsorption        = ATQC[0];
    1842     const float& theTransmittance     = ATQC[1];
    1843     const float& theEfficiency        = ATQC[2];
    1844     const float& collectionEfficiency = ATQC[3];
    1845 
    1846     float u_theAbsorption = curand_uniform(&rng);
    1847     int action = u_theAbsorption < theAbsorption  ? BREAK : CONTINUE ;
    1848 
    1849 
    1850 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1851     if( ctx.pidx == base->pidx )
    1852         printf("//qsim.propagate_at_surface_CustomART pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) u_theAbsorption  %7.3f action %d \n",
    1853         ctx.pidx, lpmtid, ATQC[0], ATQC[1], ATQC[2], ATQC[3], u_theAbsorption, action  );
    1854 #endif
    1855 
    1856     if( action == BREAK )
    1857     {
    1858         float u_theEfficiency = curand_uniform(&rng) ;
    1859         float u_collectionEfficiency = curand_uniform(&rng);
    1860 
    1861         flag = u_theEfficiency < theEfficiency ?
    1862                                                     (  u_collectionEfficiency < collectionEfficiency ? EFFICIENCY_COLLECT : EFFICIENCY_CULL )
    1863                                                :
    1864                                                     SURFACE_ABSORB
    1865                                                ;




::

    261 template<typename F>
    262 inline QPMT_METHOD void qpmt<F>::get_lpmtid_stackspec_ce_acosf( F* spec, int lpmtid, F energy_eV, F lposcost ) const
    263 {
    264     int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);  // lpmtidx:-1 FOR SPMT, BUT THAT SHOULD NEVER HAPPEN
    265     const int& lpmtcat = i_lcqs[lpmtidx*2+0] ;
    266 
    267     const F& qe_scale = lcqs[lpmtidx*2+1] ;
    268     const F qe_shape = qeshape_prop->interpolate( lpmtcat, energy_eV ) ;
    269     const F qe = qe_scale*qe_shape ;
    270 
    271     const F theta_radians = acosf(lposcost);
    272     const F ce = cetheta_prop->interpolate( lpmtcat, theta_radians );
    273 
    274     spec[0*4+3] = lpmtcat ;       //  3
    275     spec[1*4+3] = ce ;            //  7
    276     spec[2*4+3] = qe_shape ;      // 11
    277     spec[3*4+3] = qe ;            // 15
    278 
    279     get_lpmtcat_stackspec( spec, lpmtcat, energy_eV );
    280 
    281     //printf("//qpmt::get_lpmtidx_stackspec lpmtid %d lpmtidx %d lpmtcat %d lposcost %7.3f acosf_lposcost %7.3f ce %7.3f spec[7] %7.3f \n", lpmtid, lpmtidx, lpmtcat, lposcost, acosf_lposcost, ce, spec[7] );
    282 }








    293 inline void C4CustomART::doIt(const G4Track& aTrack, const G4Step& )
    294 {
    295     G4double zero = 0. ;
    296     G4double minus_one = -1. ;
    297     G4double minus_cos_theta = OldMomentum*theRecoveredNormal ;
    298     G4double dot_pol_cross_mom_nrm = OldPolarization*OldMomentum.cross(theRecoveredNormal) ;
    299 
    300     G4double energy = thePhotonMomentum ;
    301     G4double wavelength = CLHEP::twopi*CLHEP::hbarc/energy ;
    302     G4double energy_eV = energy/CLHEP::eV ;
    303     G4double wavelength_nm = wavelength/CLHEP::nm ;
    304 
    305     int pmtid = C4Touchable::VolumeIdentifier(&aTrack, true );
    306     int pmtcat = accessor->get_pmtcat( pmtid ) ;
    307     double _qe = minus_cos_theta > 0. ? 0.0 : accessor->get_pmtid_qe( pmtid, energy ) ;  // energy_eV ?
    308     // following the old junoPMTOpticalModel with "backwards" _qe always zero 
    309 
    310     std::array<double,16> a_spec ;
    311     accessor->get_stackspec(a_spec, pmtcat, energy_eV );
    312 
    313     const double* ss = a_spec.data() ;
    314 
    315     Stack<double,4> stack ;
    316 
    317     theEfficiency = zero ;
    318     if( minus_cos_theta < zero ) // only ingoing photons 
    319     {
    320         stack.calc( wavelength_nm, minus_one, zero, ss, 16u );
    321         theEfficiency = _qe/stack.art.A ;    // aka escape_fac
    322 
    323         bool expect = theEfficiency <= 1. ;
    324         if(!expect) std::cerr
    325             << "C4CustomART::doIt"
    326             << " FATAL "
    327             << " ERR: theEfficiency > 1. : " << theEfficiency
    328             << " _qe " << _qe
    329             << " stack.art.A (aka An) " << stack.art.A
    330             << std::endl
    331             ;
    332         assert( expect );
    333     }
    334     stack.calc( wavelength_nm, minus_cos_theta, dot_pol_cross_mom_nrm, ss, 16u );
    335 
    336     const double& A = stack.art.A ;
    337     const double& R = stack.art.R ;
    338     const double& T = stack.art.T ;
    339 
    340     theAbsorption = A ;
    341     theReflectivity  = R/(1.-A) ;
    342     theTransmittance = T/(1.-A)  ;
    343 


BP=C4CustomART::doIt ipc
---------------------------


::

    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 2, C4CustomART::doIt (this=0x335a7fd0, aTrack=...) at /home/blyth/customgeant4/C4CustomART.h:311
    311	    accessor->get_stackspec(a_spec, pmtcat, energy_eV ); 
    (gdb) p pmtcat
    $1 = 0
    (gdb)  pmtid
    Undefined command: "pmtid".  Try "help".
    (gdb) p pmtid
    $2 = 51000
    (gdb) p pmtcat
    $3 = 0
    (gdb) p minus_cos_theta
    $4 = -0.39604325269297802
    (gdb) p _qe
    $5 = 0.27683696724597923
    (gdb) b 324
    Breakpoint 3 at 0x7fffc10d2fb3: file /home/blyth/customgeant4/C4CustomART.h, line 324.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 3, C4CustomART::doIt (this=0x335a7fd0, aTrack=...) at /home/blyth/customgeant4/C4CustomART.h:324
    324	        if(!expect) std::cerr
    (gdb) p stack.art.A
    $6 = 0.54856416888149884
    (gdb) p _qe
    $7 = 0.27683696724597923
    (gdb) p theEfficiency
    $8 = (G4double &) @0x2c8332f0: 0.50465740008218019
    (gdb) p _qe/stack.art.A
    $9 = 0.50465740008218019
    (gdb) 




theEfficiency determines theStatus = Absorption OR Detection::

    323 inline
    324 void C4OpBoundaryProcess::DoAbsorption()
    325 {
    326               theStatus = Absorption;
    327 
    328               if ( G4BooleanRand(theEfficiency) ) {
    329 
    330                  // EnergyDeposited =/= 0 means: photon has been detected
    331                  theStatus = Detection;
    332                  aParticleChange.ProposeLocalEnergyDeposit(thePhotonMomentum);
    333               }
    334               else {
    335                  aParticleChange.ProposeLocalEnergyDeposit(0.0);
    336               }
    337 
    338               NewMomentum = OldMomentum;
    339               NewPolarization = OldPolarization;
    340 
    341 //              aParticleChange.ProposeEnergy(0.0);
    342               aParticleChange.ProposeTrackStatus(fStopAndKill);
    343 }



    0199 G4VParticleChange*
     200 C4OpBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     201 {
     202         m_track_label = C4TrackInfo<C4Pho>::GetRef(&aTrack);
     203 #ifdef C4_DEBUG_PIDX
     204         m_track_dump = ( m_track_label != nullptr && m_track_label->id == PIDX && PIDX_ENABLED ) || PIDX == -2  ;
     205 #endif
     206 


PIDX_ENABLED
---------------

::

     export C4OpBoundaryProcess__PIDX_ENABLED=1
     export PIDX=99999




Efficiency debug
-----------------

::

    In [8]: a_ec = a.q_startswith("TO BT BT BT BT EC") ; a_ec
    Out[8]: array([    1,     5,    12,    13,    14, ..., 99986, 99990, 99992, 99993, 99999], shape=(26462,))

    In [9]: b_ec = b.q_startswith("TO BT BT BT BT EC") ; b_ec
    Out[9]: array([    4,     6,     8,    15,    20, ..., 99986, 99987, 99990, 99991, 99995], shape=(29368,))

    In [11]: ab_ec = np.intersect1d( a_ec, b_ec ) ; ab_ec        ## accidental alignment, useful for debug 
    Out[11]: array([   15,    22,    70,    74,    77, ..., 99945, 99947, 99949, 99986, 99990], shape=(8035,))

    In [12]: a.q[15]
    Out[12]: array([b'TO BT BT BT BT EC                                                                               '], dtype='|S96')

    In [13]: b.q[15]
    Out[13]: array([b'TO BT BT BT BT EC                                                                               '], dtype='|S96')

Yes but unclear how to gdb debug a photon other than the first::

    In [15]: a.q[0]
    Out[15]: array([b'TO BT BT BT BT EX                                                                               '], dtype='|S96')

    In [16]: b.q[0]
    Out[16]: array([b'TO BT BT BT BT SA                                                                               '], dtype='|S96')




BP=junoSD_PMT_v2::ProcessHits PIDX=0 ipc
------------------------------------------

::

    BP=junoSD_PMT_v2::ProcessHits PIDX=0 ipc 

::

     465     double qe = 1;
     466     double ce = 1;
     467     // == get the copy number -> pmt id
     468     int pmtID = get_pmtid(track);
     469     // = final DE = QE * CE,
     470     // but QE is already applied (this is old implementation,
     471     // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
     472     // = DE: Detection Efficiency
     473     if(m_use_pmtsimsvc){
     474         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     475         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     476      }
     477      else{
     478         std::string volname = track->GetVolume()->GetName();
     479     GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     480      }
     481 
     482     double f_angle_response = 1.0;
     483     double de = qe*ce*f_angle_response ;
     484     if (de>1.0){
     485         std::cout<<"junoSD_PMT_v2:: de is larger than 1.0"<<std::endl;
     486     }
     487     bool de_cull = G4UniformRand() > de ;
     488 



    1140 double PMTSimParamSvc::get_pmtid_ce(int pmtid , double theta) const
    1141 {
    1142      int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    1143      double ce = get_pmtcat_ce(pmtcat,theta);
    1144      assert( ce > 0 );
    1145      return  ce ;
    1146 
    1147 }


    1140	double PMTSimParamSvc::get_pmtid_ce(int pmtid , double theta) const
    1141	{   
    1142	     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    1143	     double ce = get_pmtcat_ce(pmtcat,theta);
    1144	     assert( ce > 0 );
    1145	     return  ce ;
    1146	
    (gdb) b 1145
    Breakpoint 8 at 0x7fffbebd7211: file /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc, line 1145.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 8, PMTSimParamSvc::get_pmtid_ce (this=0x6678d80, pmtid=51000, theta=1.4523447961095182) at /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:1145
    1145	     return  ce ;
    (gdb) p ce
    $16 = 0.89441563487952169
    (gdb) p pmtcat
    $17 = -1
    (gdb) p pmtid
    $18 = 51000

    (gdb) p kPMT_Unknown
    $19 = kPMT_Unknown
    (gdb) p kPMT_Unknown == -1
    $20 = true
    (gdb) 


    1149 double PMTSimParamSvc::get_pmtcat_ce(int pmtcat, double theta) const
    1150 {
    1151 
    1152   assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1153   double ce = -1;
    1154   G4MaterialPropertyVector * vec = 0 ;
    1155   switch(pmtcat)
    1156     {   //FIXME:KPMT_Unknown represent WP pmt,which are use normal NNVTMCP ?
    1157         case kPMT_Unknown:     { vec = m_CE_WP_PMT ; } ; break ;
    1158         case kPMT_NNVT:        { vec = m_CE_NNVTMCP ; } ; break ;
    1159         case kPMT_Hamamatsu:   { vec = m_CE_R12860 ; } ; break ;
    1160         case kPMT_HZC:         { ce = 1.0 ; } ; return ce ;
    1161         case kPMT_NNVT_HighQE: { vec = m_CE_NNVTMCP_HiQE ; } ; break ;
    1162     }
    1163 
    1164   if(vec){
    1165         //vec -> SetSpline(false);  that is default 
    1166         ce = vec->Value(theta);
    1167   }
    1168 
    1169   //double CE = ce >= 1 ? 1 : ce ;  
    1170   assert(ce > 0 && ce <= 1 );
    1171   return ce;
    1172 }






::

    Thread 1 "python" hit Breakpoint 5, junoSD_PMT_v2::ProcessHits_ (this=0xa275640, step=0x6954dc0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:483
    483	    double de = qe*ce*f_angle_response ;
    (gdb) p qe
    $7 = 1
    (gdb) p ce
    $8 = 0.89439200547660513
    (gdb) p m_use_pmtsimsvc
    $9 = true
    (gdb) p m_enable_optical_model
    $10 = true
    (gdb) p pmtID
    $11 = 51000
    (gdb) p PMT::Is20inch(pmtID)
    $12 = true
    (gdb) p local_pos
    $13 = {static ToleranceTicks = 100, data = {245.66047933835733, -4.255158273736015e-05, 29.217924215128733}}
    (gdb) p local_pos.theta()
    $14 = 1.4524162298649179



QPMTTest.sh
---------------

::

    In [6]: t.qpmt.cetheta
    Out[6]: 
    array([[[0.   , 1.   ],
            [0.244, 1.   ],
            [0.524, 0.945],
            [0.742, 0.91 ],
            [0.96 , 0.893],
            [1.169, 0.925],
            [1.353, 0.927],
            [1.484, 0.884],
            [1.571, 0.734],
            [0.   , 0.   ]],

           [[0.   , 0.911],
            [0.227, 0.911],
            [0.489, 0.922],
            [0.716, 0.929],
            [0.96 , 0.924],
            [1.152, 0.93 ],
            [1.379, 0.91 ],
            [1.484, 0.626],
            [1.571, 0.273],
            [0.   , 0.   ]],

           [[0.   , 1.   ],
            [0.244, 1.   ],
            [0.524, 0.977],
            [0.742, 0.972],
            [0.96 , 0.97 ],
            [1.169, 0.97 ],
            [1.353, 0.945],
            [1.484, 0.91 ],
            [1.571, 0.734],
            [0.   , 0.   ]]], dtype=float32)

    In [7]: t.qpmt.cetheta_names
    Out[7]: array(['CE_NNVTMCP.npy', 'CE_R12860.npy', 'CE_NNVTMCP_HiQE.npy'], dtype='<U19')


::

    (ok) A[blyth@localhost PMTSimParamData]$ cd CEtheta
    (ok) A[blyth@localhost CEtheta]$ l
    total 24
    4 -rw-r--r--. 1 blyth blyth  272 Jun 30 11:41 CE_NNVTMCP_HiQE.npy
    4 -rw-r--r--. 1 blyth blyth  272 Jun 30 11:41 CE_NNVTMCP.npy
    4 -rw-r--r--. 1 blyth blyth  272 Jun 30 11:41 CE_R12860.npy
    4 -rw-r--r--. 1 blyth blyth  272 Jun 30 11:41 CE_WP_PMT.npy
    4 -rw-r--r--. 1 blyth blyth   63 Jun 30 11:41 NPFold_index.txt
    0 -rw-r--r--. 1 blyth blyth    0 Jun 30 11:41 NPFold_names.txt
    0 drwxr-xr-x. 2 blyth blyth  145 Jun 26 21:12 .
    4 drwxr-xr-x. 7 blyth blyth 4096 Jun 26 21:12 ..
    (ok) A[blyth@localhost CEtheta]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/extra/jpmt/PMTSimParamData/CEtheta
    (ok) A[blyth@localhost CEtheta]$ 




    In [1]: f.CE_WP_PMT
    Out[1]: 
    array([[0.   , 1.   ],
           [0.244, 1.   ],
           [0.524, 0.945],
           [0.742, 0.91 ],
           [0.96 , 0.893],
           [1.169, 0.925],
           [1.353, 0.927],
           [1.484, 0.884],
           [1.571, 0.734]])

    In [2]: f.CE_NNVTMCP
    Out[2]: 
    array([[0.   , 1.   ],
           [0.244, 1.   ],
           [0.524, 0.945],
           [0.742, 0.91 ],
           [0.96 , 0.893],
           [1.169, 0.925],
           [1.353, 0.927],
           [1.484, 0.884],
           [1.571, 0.734]])

    In [3]: np.all( f.CE_WP_PMT == f.CE_NNVTMCP )
    Out[3]: np.True_


::

    1829     float ATQC[4] = {} ;
    1830 
    1831     if(lpmtid > -1 && pmt != nullptr) pmt->get_lpmtid_ATQC(ATQC, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost );
    1832 
    1833 
    1834 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1835     if( ctx.pidx == base->pidx )
    1836     printf("//qsim::propagate_at_surface_CustomART pidx %7d lpmtid %d wl %7.3f mct %7.3f dpcmn %7.3f lpc %7.3f ATQC ( %7.3f %7.3f %7.3f %7.3f  ) \n",
    1837            ctx.pidx, lpmtid, p.wavelength, minus_cos_theta, dot_pol_cross_mom_nrm, lposcost, ATQC[0], ATQC[1], ATQC[2], ATQC[3] );
    1838 #endif
    1839 
    1840 
    1841     const float& theAbsorption        = ATQC[0];
    1842     const float& theTransmittance     = ATQC[1];
    1843     const float& theEfficiency        = ATQC[2];
    1844     const float& collectionEfficiency = ATQC[3];
    1845 
    1846     float u_theAbsorption = curand_uniform(&rng);
    1847     int action = u_theAbsorption < theAbsorption  ? BREAK : CONTINUE ;
    1848 
    1849 
    1850 #if !defined(PRODUCTION) && defined(DEBUG_PIDX)
    1851     if( ctx.pidx == base->pidx )
    1852         printf("//qsim.propagate_at_surface_CustomART pidx %7d lpmtid %d ATQC ( %7.3f %7.3f %7.3f %7.3f ) u_theAbsorption  %7.3f action %d \n",
    1853         ctx.pidx, lpmtid, ATQC[0], ATQC[1], ATQC[2], ATQC[3], u_theAbsorption, action  );
    1854 #endif
    1855 
    1856     if( action == BREAK )
    1857     {
    1858         float u_theEfficiency = curand_uniform(&rng) ;
    1859         float u_collectionEfficiency = curand_uniform(&rng);
    1860 
    1861         flag = u_theEfficiency < theEfficiency ?
    1862                                                     (  u_collectionEfficiency < collectionEfficiency ? EFFICIENCY_COLLECT : EFFICIENCY_CULL )
    1863                                                :
    1864                                                     SURFACE_ABSORB
    1865                                                ;



    261 template<typename F>
    262 inline QPMT_METHOD void qpmt<F>::get_lpmtid_stackspec_ce_acosf( F* spec, int lpmtid, F energy_eV, F lposcost ) const
    263 {
    264     int lpmtidx = s_pmt::lpmtidx_from_pmtid(lpmtid);  // lpmtidx:-1 FOR SPMT, BUT THAT SHOULD NEVER HAPPEN
    265     const int& lpmtcat = i_lcqs[lpmtidx*2+0] ;
    266 
    267     const F& qe_scale = lcqs[lpmtidx*2+1] ;
    268     const F qe_shape = qeshape_prop->interpolate( lpmtcat, energy_eV ) ;
    269     const F qe = qe_scale*qe_shape ;
    270 
    271     const F theta_radians = acosf(lposcost);
    272     const F ce = cetheta_prop->interpolate( lpmtcat, theta_radians );
    273 
    274     spec[0*4+3] = lpmtcat ;       //  3
    275     spec[1*4+3] = ce ;            //  7
    276     spec[2*4+3] = qe_shape ;      // 11
    277     spec[3*4+3] = qe ;            // 15
    278 
    279     get_lpmtcat_stackspec( spec, lpmtcat, energy_eV );
    280 
    281     //printf("//qpmt::get_lpmtidx_stackspec lpmtid %d lpmtidx %d lpmtcat %d lposcost %7.3f acosf_lposcost %7.3f ce %7.3f spec[7] %7.3f \n", lpmtid, lpmtidx, lpmtcat, lposcost, acosf_lposcost, ce, spec[7] );
    282 }
    283 


::

    In [11]: t.qpmt.lcqs[:,0]
    Out[11]: array([1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, ..., 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0], shape=(20012,), dtype=int32)

    In [12]: np.unique(t.qpmt.lcqs[:,0])
    Out[12]: array([0, 1, 2], dtype=int32)

    In [13]: 17612 + 2400
    Out[13]: 20012

    In [14]: np.unique(t.qpmt.lcqs[:,0], return_counts=True)
    Out[14]: (array([0, 1, 2], dtype=int32), array([ 4574,  4955, 10483]))

    In [15]: np.unique(t.qpmt.lcqs[17612:,0], return_counts=True)
    Out[15]: (array([0, 2], dtype=int32), array([1836,  564]))




The order could have changed::

     819     v_lcqs.resize(s_pmt::NUM_CD_LPMT_AND_WP);
     820 
     821     for(int i=0 ; i < s_pmt::NUM_CD_LPMT_AND_WP ; i++ )
     822     {
     823         int lpmtidx = i ;
     824 
     825         int pmtid = s_pmt::pmtid_from_lpmtidx( lpmtidx );
     826         int lpmtidx2 = s_pmt::lpmtidx_from_pmtid( pmtid );
     827         assert( lpmtidx == lpmtidx2 );
     828 
     829         // pmtCat from _PMTParamData uses oldcontiguous order : CD_LPMT, SPMT, WP
     830         int oldcontiguousidx = s_pmt::oldcontiguousidx_from_pmtid( pmtid );
     831         assert( oldcontiguousidx < s_pmt::NUM_ALL );
     832 
     833         int copyno = pmtCat_v[2*oldcontiguousidx+0] ;
     834         int cat    = pmtCat_v[2*oldcontiguousidx+1] ;
     835         assert( copyno == pmtid );
     836 
     837         float qesc = qeScale_v[oldcontiguousidx] ;
     838 
     839         v_lcqs[lpmtidx] = { TranslateCat(cat), qesc } ;
     840     }
     841     lcqs = NPX::ArrayFromVec<int,LCQS>( v_lcqs ) ;



::

      58 /**
      59 PMTParamSvc::getPMTCategory
      60 ----------------------------
      61 
      62 WP PMTs (pmtID 30,000+) are not listed, so return category kPMT_Unknown -1 
      63 
      64 **/
      65 int PMTParamSvc::getPMTCategory(int pmtID) const
      66 {
      67     //return m_pmt_categories.count(pmtID) == 1 ? m_pmt_categories.at(pmtID) : kPMT_Unknown  ; 
      68     return isWP(pmtID) ? kPMT_Unknown : m_pmt_categories.at(pmtID) ;
      69 }



Suspect B side always using kPMT_Unknown but A side not always using that ?  

::

    //qsim::propagate_at_surface_CustomART pidx       0 : minus_cos_theta = -0.39603478 
    //qsim::propagate_at_surface_CustomART pidx       0 : lposcost = 0.11760086 (expect 0->1)
    //qsim::propagate_at_surface_CustomART pidx       0 lpmtid 51000 wl 440.000 mct  -0.396 dpcmn   0.918 pmt 0x7fff82c48200 pre-ATQC 
    //qsim::propagate_at_surface_CustomART pidx       0 lpmtid 51000 wl 440.000 mct  -0.396 dpcmn   0.918 lpc   0.118 ATQC (   0.818   0.000   0.456   0.894  ) 
    //qsim.propagate_at_surface_CustomART pidx       0 lpmtid 51000 ATQC (   0.818   0.000   0.456   0.894 ) u_theAbsorption    0.605 action 1 
    //qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx       0 lpmtid 51000 ATQC (   0.818   0.000   0.456   0.894 ) u_theEfficiency    0.427 theEfficiency   0.456 flag 16384 
    //qsim.propagate.tail pidx       0 bounce 4 command 1 flag 16384 ctx.s.optical.y(ems) 4 
    2025-06-30 15:43:11.188 INFO  [1505239] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )
    [SProcessHits_EPH::desc





Enhanced PIDX debug
---------------------

ipcv::

    172     elif [ "$TEST" == "WP_PMT" ]; then
    173 
    174        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    175        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    176        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    177        observation="looks like 10% QE difference between A and B"
    178 
    179        #export U4Recorder__EndOfRunAction_Simtrace=1
    180        #export U4Simtrace__level=2
    181 
    182        export C4OpBoundaryProcess__PIDX_ENABLED=1
    183        export PIDX=99999
    184 
    185     elif [ "$TEST" == "SPMT" ]; then

cxs_min.sh::

    436    elif [ "${TEST:12}" == "_wp_pmt" ]; then
    437 
    438       sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    439       opticks_input_photon=RainXZ_Z230_100k_f8.npy
    440       opticks_input_photon_frame=PMT_20inch_veto:0:1000
    441 
    442       export PIDX=99999
    443 



ipc::

    [C4CustomART::doIt

     energy                   :     0.0000
     wavelength               :     0.0004
     energy_eV                :     2.8178
     wavelength_nm            :   440.0000
     pmtid                    : 51000
     pmtcat                   : 0
     _qe                      :     0.2768
     minus_cos_theta          :    -0.3960
     dot_pol_cross_mom_nrm    :    -0.9182

    ...
    ART_
      A_s      0.8179  A_p      0.9065  A_av     0.8622  A        0.8179
      R_s      0.1821  R_p      0.0935  R_av     0.1378  R        0.1821
      T_s      0.0000  T_p      0.0000  T_av     0.0000  T        0.0000
     SUM_s     1.0000 SUM_p     1.0000 SUM_a     1.0000 SUM_      1.0000
     SF        1.0000 wl      440.0000 dpcmn    -0.9182 mct      -0.3960

     ]stack
      stack.art.A              :     0.8179
     stack.art.R              :     0.1821
     stack.art.T              :     0.0000
     theAbsorption            :     0.8179
     theReflectivity          :     1.0000
     theTransmittance         :     0.0000
     theEfficiency (_qe/s..A) :     0.5047
    ]C4CustomART::doIt
    C4OpBoundaryProcess::PostStepDoIt PIDX 99999 m_custom_status Y
    2025-07-01 14:57:25.903 INFO  [2029267] [U4Recorder::PreUserTrackingAction_Optical_@500]  modulo 100000 : ulabel.id 0









    //qsim.propagate.body.WITH_CUSTOM4 pidx   99999  BOUNDARY ems 4 lposcost   0.118 
    //qsim::propagate_at_surface_CustomART pidx   99999 : mom = np.array([-0.15841781,-0.97655874,0.14572878]) ; lmom = 1.00000000 
    //qsim::propagate_at_surface_CustomART pidx   99999 : pol = np.array([-0.98709625,0.16012782,0.00000408]) ; lpol = 0.99999994 
    //qsim::propagate_at_surface_CustomART pidx   99999 : nrm = np.array([0.04131211,0.25467181,-0.96614468]) ; lnrm = 0.99999994 
    //qsim::propagate_at_surface_CustomART pidx   99999 : cross_mom_nrm = np.array([0.90638405,-0.14703415,-0.00000085]) ; lcross_mom_nrm = 0.91823262  
    //qsim::propagate_at_surface_CustomART pidx   99999 : dot_pol_cross_mom_nrm = -0.91823256 
    //qsim::propagate_at_surface_CustomART pidx   99999 : minus_cos_theta = -0.39604163 
    //qsim::propagate_at_surface_CustomART pidx   99999 : lposcost = 0.11760516 (expect 0->1)
    //qsim::propagate_at_surface_CustomART pidx   99999 lpmtid 51000 wl 440.0000 mct  -0.3960 dpcmn  -0.9182 pmt 0x7fff82c48200 pre-ATQC 
    //qpmt::get_lpmtid_stackspec_ce_acosf pidx   99999 lpmtid  51000 lpmtidx  18612 lpmtcat  0 qe_scale   0.9933 qe_shape   0.2519 qe   0.2502 lposcost   0.1176 theta_radians   1.4529 ce   0.8942 
    //qpmt::get_lpmtid_ATQC pidx   99999 lpmtid 51000 energy_eV   2.818 _qe   0.250 lposcost   0.118 ce   0.894  
    //qpmt::get_lpmtid_ATQC pidx   99999 stack.art.A   0.549 _qe/stack.art.A=ATQC[2]   0.456  ce=ATQC[3]   0.894  
    //qsim::propagate_at_surface_CustomART pidx   99999 lpmtid 51000 wl 440.0000 mct  -0.3960 dpcmn  -0.9182 lpc   0.1176 ATQC (   0.8179   0.0000   0.4561   0.8942  ) 
    //qsim.propagate_at_surface_CustomART pidx   99999 lpmtid 51000 ATQC (   0.8179   0.0000   0.4561   0.8942 ) u_theAbsorption    0.161 action 1 
    //qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx   99999 lpmtid 51000 ATQC (   0.8179   0.0000   0.4561   0.8942 ) u_theEfficiency    0.1222 theEfficiency   0.4561 flag 8192 
    //qsim.propagate.tail pidx   99999 bounce 4 command 1 flag 8192 ctx.s.optical.y(ems) 4 
    2025-07-01 13:48:20.729 INFO  [1570163] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7ffecc000000
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder YES eph_meta (1, )


cxs_min.sh::

    //qsim.propagate.body.WITH_CUSTOM4 pidx   99999  BOUNDARY ems 4 lposcost   0.118 
    //qsim::propagate_at_surface_CustomART pidx   99999 : mom = np.array([-0.15841781,-0.97655874,0.14572878]) ; lmom = 1.00000000 
    //qsim::propagate_at_surface_CustomART pidx   99999 : pol = np.array([-0.98709625,0.16012782,0.00000408]) ; lpol = 0.99999994 
    //qsim::propagate_at_surface_CustomART pidx   99999 : nrm = np.array([0.04131211,0.25467181,-0.96614468]) ; lnrm = 0.99999994 
    //qsim::propagate_at_surface_CustomART pidx   99999 : cross_mom_nrm = np.array([0.90638405,-0.14703415,-0.00000085]) ; lcross_mom_nrm = 0.91823262  
    //qsim::propagate_at_surface_CustomART pidx   99999 : dot_pol_cross_mom_nrm = -0.91823256 
    //qsim::propagate_at_surface_CustomART pidx   99999 : minus_cos_theta = -0.39604163 
    //qsim::propagate_at_surface_CustomART pidx   99999 : lposcost = 0.11760516 (expect 0->1)
    //qsim::propagate_at_surface_CustomART pidx   99999 lpmtid 51000 wl 440.0000 mct  -0.3960 dpcmn  -0.9182 pmt 0x7fc9c4c48200 pre-ATQC 
    //qpmt::get_lpmtid_stackspec_ce_acosf pidx   99999 lpmtid  51000 lpmtidx  18612 lpmtcat  0 qe_scale   0.9933 energy_eV   2.8178 qe_shape   0.2519 qe(qe_scale*qe_shape)   0.2502 spec[15]   0.2502 lposcost   0.1176 theta_radians   1.4529 ce   0.8942 
    //qpmt.get_lpmtid_ATQC pidx   99999 lpmtid 51000 energy_eV   2.8178 _qe(spec[15])   0.2502 lposcost   0.1176 ce   0.8942 stack.art.A   0.5486 _qe/stack.art.A=ATQC[2]   0.4561  ce=ATQC[3]   0.8942  
    //qsim::propagate_at_surface_CustomART pidx   99999 lpmtid 51000 wl 440.0000 mct  -0.3960 dpcmn  -0.9182 lpc   0.1176 ATQC (   0.8179   0.0000   0.4561   0.8942  ) 
    //qsim.propagate_at_surface_CustomART pidx   99999 lpmtid 51000 ATQC (   0.8179   0.0000   0.4561   0.8942 ) u_theAbsorption    0.161 action 1 
    //qsim.propagate_at_surface_CustomART.BREAK.SD/SA EC/EX pidx   99999 lpmtid 51000 ATQC (   0.8179   0.0000   0.4561   0.8942 ) u_theEfficiency    0.1222 theEfficiency   0.4561 flag 8192 
    //qsim.propagate.tail pidx   99999 bounce 4 command 1 flag 8192 ctx.s.optical.y(ems) 4 
    2025-07-01 14:19:32.593 INFO  [1573618] [QEvent::gatherPhoton@628] [ evt.num_photon 100000 p.sstr (100000, 4, 4, ) evt.photon 0x7fc990000000
    2025-07-01 14:19:32.762 INFO  [1573618] [QSim::simulate@501]  eventID 0 tot_dt    0.010411 tot_ph     100000 tot_ph/M   0.100000 tot_ht      26756 tot_ht/M   0.026756 tot_ht/tot_ph   0.267560 reset_ YES
    2025-07-01 14:19:32.763 INFO  [1573618] [SEvt::save@4163] /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL98_Debug_Philox_input_photon_wp_pmt/A000 [genstep,photon,record,seq,hit,domain,inphoton]
    2025-07-01 14:19:33.822 INFO  [1573618] [QSim::simulate@516] 


QPMTTest.sh pdb::

    In [6]: t.qpmt.lcqs[:,1].view(np.float32)[17612+1000]
    Out[6]: np.float32(0.9932614)

After SPMT.h qeScale_v oldcontiguousidx vs contiguousidx bug::

    In [1]: t.qpmt.lcqs[:,1].view(np.float32)[17612+1000]
    Out[1]: np.float32(1.0989012)



::

    [C4CustomART::doIt.nrm
     wavelength_nm            :   440.0000
     minus_cos_theta          :    -0.3960
     _qe                      :     0.2768
     stack.art.A(nrm)         :     0.5486     ## MATCHES A side 
     theEfficiency(_qe/An)    :     0.5047
     expect                   : YES
    ]C4CustomART::doIt.nrm
    [C4CustomART::doIt.mct
     energy                   :     0.0000
     wavelength               :     0.0004
     energy_eV                :     2.8178
     wavelength_nm            :   440.0000
     pmtid                    : 51000
     pmtcat                   : 0
     _qe                      :     0.2768
     minus_cos_theta          :    -0.3960
     dot_pol_cross_mom_nrm    :    -0.9182


Continue finds correct one::

    228	inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const 
    229	{
    230	    int idx = get_pmtContiguousIndex(pmtid) ; 
    231	    int cat = m_all_pmt_catvec[idx] ; 
    232	    double qe = get_pmtcat_qe(cat, energy);
    233	    double qe_scale = m_all_pmtID_qe_scale[idx] ; 
    234	    qe *= qe_scale ;
    235	    assert(qe > 0 && qe < 1);
    236	    return qe ; 
    237	}
    238	
    239	inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const 
    240	{
    241	    G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    242	    double qe = vec->Value(energy);
    --Type <RET> for more, q to quit, c to continue without paging--
    243	    return qe;
    244	}
    (gdb) p pmtid
    $5 = 51000
    (gdb) p idx
    $6 = 18612
    (gdb) p cat
    $7 = 0
    (gdb) p energy
    $8 = 2.817822667394958e-06
    (gdb) p qe
    $9 = 0.27683696724597923

    (gdb) p qe_scale                          
    $10 = 1.0989010989010988                  ## DOES NOT MATCH 

    (gdb) p this->get_pmtcat_qe(cat,energy)   ## matches qe_shape on A side
    $11 = 0.25192164019384111

    (gdb) p 0.25192164019384111*qe_scale
    $12 = 0.27683696724597923
 


SMOKING GUN : qe_scale MISMATCH
----------------------------------








Rebuild with more C4 debug. ~/j/local.sh
-----------------------------------------

~/j/local.sh::

     49 BUILD ORDER WHEN CHANGING CUSTOM4 VERSION : C4, OK, OJ
     50 -------------------------------------------------------
     51 
     52 Do each of the below in clean tabs:
     53 
     54 cd ~/customgeant4
     55 git status  # check are on the 0.1.8_transient branch
     56 ## NB do not want to make major changes in the transient branch, changing debug is acceptable 
     57 
     58 
     59 1. local_c4_build ; c4_build
     60 2. local_ok_build ; ok_build
     61 3. local_oj_build ; oj_build
     62 
     63 



::

    223 inline void PMTAccessor::get_stackspec( std::array<double, 16>& ss, int pmtcat, double energy_eV ) const
    224 {
    225     double energy = energy_eV*CLHEP::eV ;
    226 
    227     ss.fill(0.);
    228 
    229     ss[4*0+0] = PyrexRINDEX ? PyrexRINDEX->Value(energy) : 0. ;
    230 
    231     ss[4*1+0] = data->get_pmtcat_prop(       pmtcat, "ARC_RINDEX" , energy );
    232     ss[4*1+1] = data->get_pmtcat_prop(       pmtcat, "ARC_KINDEX" , energy );
    233     ss[4*1+2] = data->get_pmtcat_const_prop( pmtcat, "ARC_THICKNESS" )/CLHEP::nm ;
    234 
    235     ss[4*2+0] = data->get_pmtcat_prop(       pmtcat, "PHC_RINDEX" , energy );
    236     ss[4*2+1] = data->get_pmtcat_prop(       pmtcat, "PHC_KINDEX" , energy );
    237     ss[4*2+2] = data->get_pmtcat_const_prop( pmtcat, "PHC_THICKNESS" )/CLHEP::nm ;
    238 
    239     ss[4*3+0] = VacuumRINDEX ? VacuumRINDEX->Value(energy) : 1. ;
    240 }



jcv PMTAccessor::

    210 inline double PMTAccessor::get_pmtid_qe( int pmtid, double energy ) const
    211 {
    212     return data->get_pmtid_qe(pmtid, energy) ;
    213 }

jcv PMTSimParamData::

    228 inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const
    229 {
    230     int idx = get_pmtContiguousIndex(pmtid) ;
    231     int cat = m_all_pmt_catvec[idx] ;
    232     double qe = get_pmtcat_qe(cat, energy);
    233     double qe_scale = m_all_pmtID_qe_scale[idx] ;
    234     qe *= qe_scale ;
    235     assert(qe > 0 && qe < 1);
    236     return qe ;
    237 }



    281 inline int PMTSimParamData::get_pmtContiguousIndex(int pmtid) const
    282 {
    283     int idx = -1 ;
    284     if(PMT::IsCD(pmtid) and PMT::Is20inch(pmtid)) {
    285         idx = pmtid ;    // LPMT 
    286     } else if(PMT::IsWP(pmtid)) {
    287         idx = pmtid - kOFFSET_WP_PMT  + m_PmtTotal ;  // WPMT 
    288     } else if (PMT::IsCD(pmtid) and PMT::Is3inch(pmtid)){
    289         idx = pmtid - kOFFSET_CD_SPMT + m_PmtTotal + m_PmtTotal_WP ;  // SPMT  
    290     }
    291 
    292     return idx ;
    293 }

    239 inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const
    240 {
    241     G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    242     double qe = vec->Value(energy);
    243     return qe;
    244 }



BP=PMTSimParamData::get_pmtid_qe ipc
---------------------------------------

::

    (gdb) bt
    #0  0x00007fffc113ef90 in PMTSimParamData::get_pmtid_qe(int, double) const@plt () from /home/blyth/junosw/InstallArea/lib64/libMultiFilmLUTMakerSvc.so
    #1  0x00007fffc1164312 in PMTAccessor::get_pmtid_qe (this=0x349f6bb0, pmtid=51000, energy=2.817822667394958e-06) at /home/blyth/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h:212
    #2  0x00007fffc10d1eb4 in C4CustomART::doIt (this=0x34574390, aTrack=...) at /home/blyth/customgeant4/C4CustomART.h:307
    #3  0x00007fffc10c67ea in C4OpBoundaryProcess::PostStepDoIt (this=0x9e2bad0, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:518
    #4  0x00007fffc6727519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc672791b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffc6725154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so



HUH thats the wrong lib::

    (gdb) f 0
    #0  0x00007fffc113ef90 in PMTSimParamData::get_pmtid_qe(int, double) const@plt () from /home/blyth/junosw/InstallArea/lib64/libMultiFilmLUTMakerSvc.so
    (gdb) list
    217	}

Continue finds correct one::

    228	inline double PMTSimParamData::get_pmtid_qe(int pmtid, double energy) const 
    229	{
    230	    int idx = get_pmtContiguousIndex(pmtid) ; 
    231	    int cat = m_all_pmt_catvec[idx] ; 
    232	    double qe = get_pmtcat_qe(cat, energy);
    233	    double qe_scale = m_all_pmtID_qe_scale[idx] ; 
    234	    qe *= qe_scale ;
    235	    assert(qe > 0 && qe < 1);
    236	    return qe ; 
    237	}
    238	
    239	inline double PMTSimParamData::get_pmtcat_qe(int cat, double energy) const 
    240	{
    241	    G4MaterialPropertyVector* vec = get_pmtcat_qe_vs_energy(cat);
    242	    double qe = vec->Value(energy);
    --Type <RET> for more, q to quit, c to continue without paging--
    243	    return qe;
    244	}
    (gdb) p pmtid
    $5 = 51000
    (gdb) p idx
    $6 = 18612
    (gdb) p cat
    $7 = 0
    (gdb) p energy
    $8 = 2.817822667394958e-06
    (gdb) p qe
    $9 = 0.27683696724597923
    (gdb) p qe_scale
    $10 = 1.0989010989010988
    (gdb) p this->get_pmtcat_qe(cat,energy)
    $11 = 0.25192164019384111
    (gdb) p 0.25192164019384111*qe_scale
    $12 = 0.27683696724597923
    (gdb) p m_all_pmtID_qe_scale
    $13 = std::vector of length 45612, capacity 65536 = {1.0253443749830857, 1.2010977528218907, 1.238126167086141, 1.1719315167591029, 1.1368772157722389, 1.177060487405315, 1.0979066872344456, 1.0302495196341099, 1.2451533141188313, 1.0256826608210874, 
      1.1623242657725414, 1.1053489756704824, 1.04638575410679, 1.041954209628968, 1.1861701516873933, 1.0592067873670536, 1.1640849571884055, 1.0332602635923249, 1.1808498015394566, 1.0299112337961083, 1.0368799220589429, 1.2760802415974828, 
      1.2509712509712509, 1.3545458373044581, 1.3109878627120006, 1.2940699147595698, 1.3117916566192427, 1.411002790313135, 1.2809795568416256, 1.3000409552133689, 1.3052464776602706, 1.2995433685088855, 1.346469622331691, 1.2436988299057263, 
      1.2964047446806068, 1.2499760775622843, 1.2763481728998969, 1.2543395302015992, 1.2634491944836772, 1.3559620456172181, 1.0442207247435793, 1.0408040377797623, 1.316040281557523, 1.31829855967787, 1.3293220189771913, 1.2986630228009539, 
      1.3243997632643918, 1.2624540210747106, 1.2502440088646987, 1.2616885030678135, 1.2871419767971493, 1.3575313575313575, 1.2748936886867921, 1.3160785574578677, 1.2558322903150489, 1.2756209307933444, 1.3120213120213118, 1.4319779837021216, 
      1.2854195612816302, 1.2616885030678135, 1.3357906461354738, 1.2596598803495351, 1.2839650770685254, 1.2510095268715957, 1.1738807044483899, 1.3137054516364861, 1.3137054516364861, 1.2734392044736873, 1.3189875258840775, 1.2203880544491896, 
      1.279525072628521, 1.289208875415772, 1.2869888731957699, 1.2886730128109438, 1.4030796789417477, 1.2467991778336605, 1.2818599025495578, 1.2723674792640307, 1.2403688265757231, 1.2952564676702607, 1.3572634262289434, 1.3091506194954472, 
      1.2932661208523275, 1.2598512598512597, 1.2895150826185307, 1.3296665020802951, 1.3678658506244714, 1.2671619568171293, 1.3565744600227359, 1.2881754261064606, 1.3706599913496464, 1.3371303026475438, 1.3571485985279088, 1.3160020056571777, 
      1.2993902649075062, 1.3124806228254504, 1.300883025020956, 1.4093569265983057, 1.1433290145080537, 1.3415703070875482, 1.2874864599002529, 1.1572852184205893, 1.2761185174978278, 1.0302833482179101, 1.0343089496901299, 1.2955243989726748, 
      1.3028350959385442, 1.2623391933736758, 1.3076961352823422, 1.2642529883909195, 1.3272168444582235, 1.2986247469006087, 1.2632578149819529, 1.2542247025005646, 1.2931130172509482, 1.2536888398957364, 1.2613822958650545, 1.2855726648830099, 
      1.2702240288447184, 1.3521727314830763, 1.3135906239354516, 1.3107964832102765, 1.2653247136005754, 1.2525405628853905, 1.2787212787212787, 1.3748703403875819, 1.3434841021047919, 1.3468906572354848, 1.2544926338029785, 1.3301640887847785, 
      1.3702389564458528, 1.2861850792885277, 1.3130547613306236, 1.2485215933491793, 1.256100221617463, 1.3129782095299334, 1.250932975070906, 1.1304404407852684, 1.265477817201955, 1.3572251503285986, 1.3263364987502919, 1.3339151270185754, 
      1.293189569051638, 1.0371843793131443, 1.0440854104083788, 1.26834850972782, 1.2804054183364528, 1.2485981451498693, 1.3087678604919981, 1.3333027126130577, 1.3086913086913088, 1.2422443456926215, 1.3248437386368419, 1.3389292699637527, 
      1.3388527181630629, 1.2611526404629851, 1.2475646958405577, 1.2556026349129796, 1.371655164758613, 1.3040599247495799, 1.3410344444827205, 1.2651333340988513, 1.3429865154003084, 1.3999793310138138, 1.2567509119233258, 1.2564064288202221, 
      1.3194851125885607, 1.2670471291160945, 1.2949502604675018, 1.3203654582964928, 1.4133376202341719, 1.3806117254393118, 1.2715636853567884, 1.4169355548665892, 1.3237720134271858, 1.2490957318543525, 1.3726120622672346, 1.2865295623916313, 
      1.2519281484798723, 1.2655543690026447, 1.2785681751198994, 1.2467609019333157, 1.4155193465538294, 1.3502972123661778, 1.3336854716165063, 1.3261068433482226, 1.2751616199892062, 1.3404603059775475, 1.3027202682375094, 1.2453829695209004, 
      1.2883668056081847, 1.0902275987118075, 1.3375130616509927, 1.325992015647188, 1.3378192688537516, 1.4158255537565883, 1.3352165076303006, 1.3174947657706277, 1.0363048361343401, 1.3093037230968265...}
    (gdb) p m_all_pmt_catvec
    $14 = std::vector of length 45612, capacity 65536 = {1, 3, 1, 3, 1, 3, 1, 1, 3, 1, 3, 1, 1, 1, 3, 1, 3, 1, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 
      3, 3, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 
      3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3...}
    (gdb) 






jcv PMTSimParamSvc::

      32 PMTSimParamSvc::PMTSimParamSvc(const std::string& name)
      33     :
      34     SvcBase(name),
      35     m_all_pmtID(m_data.m_all_pmtID),
      36     m_all_pmtID_qe_scale(m_data.m_all_pmtID_qe_scale),
      37     m_db_path_SPMT(),
      38     m_PmtTotal_SPMT(m_data.m_PmtTotal_SPMT),
      39     pd_map_SPMT(m_data.pd_map_SPMT),
      40     m_map_pmt_category(m_data.m_map_pmt_category),
      41     m_all_pmt_category(m_data.m_all_pmt_category),
      42     m_all_pmt_catvec(m_data.m_all_pmt_catvec),
      43     m_db_type("File"),
      44     m_db_path_CD_LPMT(),


Both m_all_pmtID_qe_scale and m_all_pmt_catvec depend on ordering in m_all_pmtID::

     229     m_PmtTotal_ALL = int(m_all_pmtID.size()) ;
     230 
     231     assert( m_PmtTotal_ALL == m_PmtTotal + m_PmtTotal_WP + m_PmtTotal_SPMT ) ;
     232 
     233 
     234     for(int i=0 ; i < m_PmtTotal_ALL ; i++)
     235     {
     236         int pmtid = m_all_pmtID[i] ;
     237         double qe_scale = get_pmt_qe_scale(pmtid) ;
     238         m_all_pmtID_qe_scale.push_back(qe_scale);
     239     }
     240 
     241 
     242 
     243     const auto& ii = m_all_pmt_category ;
     244     for (int i=0 ; i < m_PmtTotal_ALL ; i++) {
     245         int pmtid = m_all_pmtID[i];
     246 
     247         m_all_pmt_catvec.push_back(ii.at(pmtid));
     248     }



Ordering is CD_LPMT, WP, SPMT::

     176 void PMTSimParamSvc::init_all_pmtID_qe_scale()
     177 {
     178     m_all_pmtID.clear();
     179 
     180     // pd_vector will contain both CD-LPMT and WP-LPMT
     181     assert( m_PmtTotal+m_PmtTotal_WP == int(pd_vector.size()) );
     182 
     183     if (m_PmtTotal+m_PmtTotal_WP != int(pd_vector.size())) {
     184         LogError << "Mismatch m_PmtTotal+m_PmtTotal_WP != int(pd_vector.size())." << std::endl;
     185         LogError << " m_PmtTotal: " << m_PmtTotal << std::endl;
     186         LogError << " m_PmtTotal_WP: " << m_PmtTotal_WP << std::endl;
     187         LogError << " int(pd_vector.size()): " << int(pd_vector.size()) << std::endl;
     188     }
     189 
     190     for(int idx = 0 ; idx < m_PmtTotal ; idx++ )
     191     {
     192         int id = pd_vector[idx].pmtId() ;
     193         assert( id == idx );
     194         m_all_pmtID.push_back(id);
     195     }
     196 
     197 
     198 
     199     m_all_pmt_category = m_PMTParamSvc->getPMTCategoryMap() ;  // this excludes WP 
     200     for(int idx = 0 ; idx < m_PmtTotal_WP ; idx++ )
     201     {
     202         int idx_pd_vector = m_PmtTotal + idx; // index in pd_vector
     203         int id = pd_vector[idx_pd_vector].pmtId(); // PMT ID from pd_vector
     204         int pmtid = kOFFSET_WP_PMT + idx ;
     205 
     206         if (id != pmtid) {
     207             LogError << "Mismatch WP PMTID: "
     208                      << " idx_pd_vector (m_PmtTotal + idx): " << idx_pd_vector
     209                      << " id: " << id
     210                      << " pmtid (kOFFSET_WP_PMT + idx): " << pmtid
     211                      << std::endl;
     212         }
     213 
     214         m_all_pmtID.push_back(pmtid);
     215         m_all_pmt_category[pmtid] = kPMT_NNVT ;  // that means WP 
     216     }
     217 
     218 
     219 
     220 
     221     assert( m_PmtTotal_SPMT == int(pd_map_SPMT.size()) );
     222 
     223     // FIXME: this is also unordered now
     224     for (int idx = 0; idx < m_PmtTotal_SPMT; ++idx) {
     225         int pmtid = kOFFSET_CD_SPMT + idx;
     226         m_all_pmtID.push_back(pmtid);
     227     }








::

    A[blyth@localhost junosw]$ jgl PMTSimParamData
    ./Simulation/DetSimV2/DetSimOptions/include/LSExpDetectorConstruction_Opticks.hh
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h
    ./Simulation/SimSvc/MultiFilmLUTMakerSvc/MultiFilmLUTMakerSvc/MultiFilmLUTMakerSvc.hh
    ./Simulation/SimSvc/MultiFilmLUTMakerSvc/src/MultiFilmLUTMakerSvc.cc
    ./Simulation/SimSvc/PMTSimParamSvc/CMakeLists.txt
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTQty.h
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.py
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData.sh
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.cc
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/_PMTSimParamData.h
    ./Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTSimParamData.h
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamData.cc
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h
    A[blyth@localhost junosw]$ 




