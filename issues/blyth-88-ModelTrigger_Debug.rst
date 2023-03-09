blyth-88-ModelTrigger_Debug
=============================

* :doc:`blyth-88-quadrant-matching`



WIP : Directing beam at NNVT PMT gives worse chi2  : Due to a zero dropout 
-------------------------------------------------------------------------

::

    In [2]: np.c_[siq,quo,siq,sabo2,sc2,sabo1][:50]                                                                                                                             
    Out[2]: 
    array([[' 0', 'TO BT SD                                                    ', ' 0', ' 35832  36034', ' 0.5678', '     2      0'],
           [' 1', 'TO BT SA                                                    ', ' 1', ' 30792  30754', ' 0.0235', '     0      1'],
           [' 2', 'TO BT BT SR BT BT SA                                        ', ' 2', '  8735   8684', ' 0.1493', '     6     34'],
           [' 3', 'TO BT BT SR SA                                              ', ' 3', '  7970   8032', ' 0.2402', '     3     10'],
           [' 4', 'TO BT BT SR BR SA                                           ', ' 4', '  3657   3561', ' 1.2768', '    19     55'],
           [' 5', 'TO BT BR BT SA                                              ', ' 5', '  2973   2853', ' 2.4717', '    27     48'],
           [' 6', 'TO BT BT SA                                                 ', ' 6', '  2288   2371', ' 1.4786', '    28     50'],
           [' 7', 'TO BT BT SR BR SR SR BT BT SA                               ', ' 7', '  1895   1963', ' 1.1985', '    25    110'],
           [' 8', 'TO BT BT SR BR SR SR SA                                     ', ' 8', '  1881   1807', ' 1.4848', '    17     33'],
           [' 9', 'TO BT BT SR BR SR SR BR SR SA                               ', ' 9', '   612    635', ' 0.4242', '   304    292'],
           ['10', 'TO BT BT SR BR SR SA                                        ', '10', '   530    545', ' 0.2093', '   130     92'],
           ['11', 'TO BT AB                                                    ', '11', '   340    322', ' 0.4894', '   165     78'],
           ['12', 'TO BR SA                                                    ', '12', '   291    274', ' 0.5115', '  1074    908'],
           ['13', 'TO AB                                                       ', '13', '   228    241', ' 0.3603', '   261    398'],
           ['14', 'TO BT BT SR BR SR SR BR SR BR SR SA                         ', '14', '   236    234', ' 0.0085', '   282    326'],
           ['15', 'TO BT BT SR BR SR SR BR SR BT BT BT SD                      ', '15', '   218    203', ' 0.5344', '   115    125'],
           ['16', 'TO BT BT SR BR SR SR BR SA                                  ', '16', '   211    201', ' 0.2427', '   253    470'],
           ['17', 'TO BT BT SR BR SR SR BR SR BT BT BT SA                      ', '17', '   199    198', ' 0.0025', '  2626     65'],
           ['18', 'TO BT BT SR BR SR SR BR SR BT BT BT BT SA                   ', '18', '   198    195', ' 0.0229', '   251    341'],
           ['19', 'TO BT BT SR BR SR SR BR SR BR SR BT BT BT SD                ', '19', '   117    106', ' 0.5426', '   127     23'],
           ['20', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BT BT SA             ', '20', '    98    105', ' 0.2414', '  3337   1715'],
           ['21', 'TO BT BT SR BR SR SR BR SR BR SR BT BT BT SA                ', '21', '   105    103', ' 0.0192', '   516    308'],
           ['22', 'TO BT BT SR BR SR SR BR SR BR SR BR SR SA                   ', '22', '   103    100', ' 0.0443', '   520   2403'],
           ['23', 'TO BT BT SR BR SR SR BR SR BR SA                            ', '23', '    81     81', ' 0.0000', '   246    131'],
           ['24', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BR SR SA             ', '24', '    42     48', ' 0.4000', '  2562   4391'],

           ['25', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BR SR SR SD          ', '25', '    36      0', '36.0000', '  4772     -1'],
           ['32', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BR SR SR BT BT SA    ', '32', '     0     24', ' 0.0000', '    -1   6043'],
           ['34', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BR SR SR BR SA       ', '34', '     0     15', ' 0.0000', '    -1   3566'],
           ['40', 'TO BT BT SR BR SR SR BR SR BR SR BR SR BR SR SR BR BT BT SA ', '40', '     0     10', ' 0.0000', '    -1   4730'],


::

    N=0 APID=4772 ./U4SimtraceTest.sh ana
    ## lots of bouncing around inside NNVT ending with an SD on the fake border, which makes no sense at all

    N=1 BPID=6043 ./U4SimtraceTest.sh ana

    N=0 APID=4772 BPID=6043 BOFF=400,0,0 ./U4SimtraceTest.sh ana
    
    w = np.where( q[:,0] == q[4772] )[0]    

    In [19]: w[:10]
    Out[19]: array([ 4772,  8809,  8909, 10099, 12715, 13162, 14008, 19524, 20787, 21350])

    In [17]: t.photon[w,0]   ## ALL ENDING WITH SD AT THE SAME PLACE : LOOKS LIKE A BUG 
    Out[17]: 
    array([[-250.   ,    0.   ,  183.618,   20.122],
           [-250.   ,    0.   ,  183.618,   20.122],
           [-250.   ,    0.   ,  183.618,   20.122],


Curious N=0 FastSim midline SA/SD only happens with NNVT (not with HAMA)
----------------------------------------------------------------------------

What should happen is fall-thru SameMaterial transmission, but 
are getting SA/SD there ? 


Pick photons that end on the NNVT mid-line::

    124     x_pick = np.logical_and( pos[:,0] > -251, pos[:,0] < -249 )
    125     z_pick = np.logical_and( pos[:,2] > -250, pos[:,2] <  250 )
    126     xz_pick = np.logical_and( x_pick, z_pick )

    In [14]: np.c_[w_xz_pick,pos[w_xz_pick],q[w_xz_pick]]
    Out[14]: 
    array([[b'12216', b'-250.0', b'0.0', b'199.61691', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12229', b'-250.0', b'0.0', b'201.23035', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12239', b'-250.0', b'0.0', b'202.47464', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12242', b'-250.0', b'0.0', b'202.84843', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12245', b'-250.0', b'0.0', b'203.22209', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12255', b'-250.0', b'0.0', b'204.47124', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12261', b'-250.0', b'0.0', b'205.22177', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12267', b'-250.0', b'0.0', b'205.97293', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12268', b'-250.0', b'0.0', b'206.0988', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12292', b'-250.0', b'0.0', b'209.116', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12294', b'-250.0', b'0.0', b'209.36806', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12295', b'-250.0', b'0.0', b'209.49432', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12314', b'-250.0', b'0.0', b'211.89659', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12374', b'-250.0', b'0.0', b'219.55368', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12378', b'-250.0', b'0.0', b'220.0678', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12380', b'-250.0', b'0.0', b'220.32542', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12417', b'-250.0', b'0.0', b'225.10968', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12420', b'-250.0', b'0.0', b'225.4991', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12442', b'-250.0', b'0.0', b'228.3668', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12446', b'-250.0', b'0.0', b'228.89001', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12454', b'-250.0', b'0.0', b'229.93802', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12455', b'-250.0', b'0.0', b'230.06886', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12460', b'-250.0', b'0.0', b'230.72522', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12469', b'-250.0', b'0.0', b'231.90826', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12472', b'-250.0', b'0.0', b'232.30322', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12477', b'-250.0', b'0.0', b'232.962', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12487', b'-250.0', b'0.0', b'234.28253', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12492', b'-250.0', b'0.0', b'234.94427', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12499', b'-250.0', b'0.0', b'235.8715', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12501', b'-250.0', b'0.0', b'236.13708', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12514', b'-250.0', b'0.0', b'237.86508', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12521', b'-250.0', b'0.0', b'238.79764', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12525', b'-250.0', b'0.0', b'239.33118', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12532', b'-250.0', b'0.0', b'240.26724', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12547', b'-250.0', b'0.0', b'242.27736', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12548', b'-250.0', b'0.0', b'242.41223', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12555', b'-250.0', b'0.0', b'243.3532', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12559', b'-250.0', b'0.0', b'243.89198', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12564', b'-250.0', b'0.0', b'244.56636', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12573', b'-250.0', b'0.0', b'245.78165', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12583', b'-250.0', b'0.0', b'247.136', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12586', b'-250.0', b'0.0', b'247.5434', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12588', b'-250.0', b'0.0', b'247.81477', b'TO BT BT SR SR SR SA                                                                            '],
           [b'12643', b'-250.0', b'0.0', b'-171.18556', b'TO BT BT SR SR SR SR BR BR SR SR SD                                                             '],
           [b'13535', b'-250.10449', b'0.0', b'248.99995', b'TO BT BT SR SR SR SR SA                                                                         '],
           [b'17573', b'-250.0', b'0.0', b'168.81075', b'TO BT BT SR SR BR BR SR SR SD                                                                   '],
           [b'17603', b'-250.0', b'0.0', b'179.68512', b'TO BT BT SR SR BR BR SR SR SD                                                                   '],
           [b'17608', b'-250.0', b'0.0', b'181.52397', b'TO BT BT SR SR BR BR SR SR SA                                                                   '],
           [b'18285', b'-250.0', b'0.0', b'-156.15952', b'TO BT BT SR SR BR SR SR SA                                                                      '],
           [b'18408', b'-250.0', b'0.0', b'220.31389', b'TO BT BT SR SR BR SR SR SR SA                                                                   '],
           ...,


::

    epsilon:tests blyth$ APID=12231 N=0 ./U4SimtraceTest.sh ana
    epsilon:tests blyth$ APID=12588 N=0 ./U4SimtraceTest.sh ana

    ## hmm: L corner bounce 



    epsilon:tests blyth$ APID=12643 N=0 ./U4SimtraceTest.sh ana    #


    In [6]: rg = np.arange(12216,12239)

    In [7]: np.c_[rg, q[rg]]
    Out[7]: 
    array([[b'12216', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12217', b'TO BT SA                                                                                        '],
           [b'12218', b'TO BT SA                                                                                        '],
           [b'12219', b'TO BT SD                                                                                        '],
           [b'12220', b'TO BT SA                                                                                        '],
           [b'12221', b'TO BT SD                                                                                        '],
           [b'12222', b'TO BT SD                                                                                        '],
           [b'12223', b'TO BT SA                                                                                        '],
           [b'12224', b'TO BT SA                                                                                        '],
           [b'12225', b'TO BT SA                                                                                        '],
           [b'12226', b'TO BT SD                                                                                        '],
           [b'12227', b'TO BT SD                                                                                        '],
           [b'12228', b'TO BT SA                                                                                        '],
           [b'12229', b'TO BT BT SR SR SR SD                                                                            '],
           [b'12230', b'TO BT SD                                                                                        '],
           [b'12231', b'TO BT BT SR SR SA                                                                               '],
           [b'12232', b'TO BT SD                                                                                        '],
           [b'12233', b'TO BT SA                                                                                        '],
           [b'12234', b'TO BT BT SA                                                                                     '],
           [b'12235', b'TO BT SD                                                                                        '],
           [b'12236', b'TO BT SD                                                                                        '],
           [b'12237', b'TO BT SD                                                                                        '],
           [b'12238', b'TO BT BT SR SR SA                                                                               ']], dtype='|S96')






    In [16]: u_mtd, n_mtd = np.unique( mtd[:,2,3].view("|S8"), return_counts=True )

    In [17]: np.c_[u_mtd, n_mtd]
    Out[17]: 
    array([[b'N_I1>I2', b'233'],
           [b'N_MIS_I2', b'186'],
           [b'N_MLV_I2', b'75'],
           [b'N_PV_I2', b'736'],
           [b'N_TAIL', b'351'],
           [b'Y_GLASS', b'1034'],
           [b'Y_VACUUM', b'281']], dtype='|S21')


Getting Rerunning to work
-----------------------------


u4t/U4SimulateTest.sh::

    118 if [ -n "$RERUN" ]; then 
    119    export OPTICKS_G4STATE_RERUN=$RERUN
    120    running_mode=SRM_G4STATE_RERUN
    121 else
    122    running_mode=SRM_G4STATE_SAVE
    123 fi
    124 
    125 case $running_mode in 
    126    SRM_G4STATE_SAVE)  reldir=ALL$VERSION ;;
    127    SRM_G4STATE_RERUN) reldir=SEL$VERSION ;;
    128 esac
    129 
    130 ## sysrap/SEventConfig 
    131 export OPTICKS_RUNNING_MODE=$running_mode   # see SEventConfig::RunningMode
    132 export OPTICKS_MAX_BOUNCE=31                # can go upto 31 now that extended sseq.h 
    133 export OPTICKS_EVENT_MODE=StandardFullDebug
    134 

SEventConfig.cc::

    061 int SEventConfig::_RunningMode = SRM::Type(SSys::getenvvar(kRunningMode, _RunningModeDefault));
     62 const char* SEventConfig::_G4StateSpec  = SSys::getenvvar(kG4StateSpec,  _G4StateSpecDefault );
     63 int         SEventConfig::_G4StateRerun = SSys::getenvint(kG4StateRerun, _G4StateRerunDefault) ;
     64 

     92 int         SEventConfig::RunningMode(){ return _RunningMode ; }
     93 const char* SEventConfig::RunningModeLabel(){ return SRM::Name(_RunningMode) ; }
     94 bool SEventConfig::IsRunningModeDefault(){      return RunningMode() == SRM_DEFAULT ; }
     95 bool SEventConfig::IsRunningModeG4StateSave(){  return RunningMode() == SRM_G4STATE_SAVE ; }
     96 bool SEventConfig::IsRunningModeG4StateRerun(){ return RunningMode() == SRM_G4STATE_RERUN ; }
     97 
     98 const char* SEventConfig::G4StateSpec(){  return _G4StateSpec ; }
     99 
    100 /**
    101 SEventConfig::G4StateRerun
    102 ----------------------------
    103 
    104 When rerun mode is not enabled returns -1 even when rerun id is set. 
    105 
    106 **/
    107 int SEventConfig::G4StateRerun()
    108 {
    109     bool rerun_enabled = IsRunningModeG4StateRerun() ;
    110     return rerun_enabled && _G4StateRerun > -1 ? _G4StateRerun : -1  ;
    111 }
    112 


After config to save all g4state (not just 1000) by changing OPTICKS_G4STATE_SPEC to "$num_ph:38"
can rerun the single photon::

    RERUN=4772 N=0 POM=1 ./U4SimulateTest.sh 

    RERUN=4772 BP=junoPMTOpticalModel::DoIt N=0 POM=1 ./U4SimulateTest.sh 




HMM : LOOKS LIKE FASTSIM N=0 HAS ANOTHER BUG : SOMETIMES GETTING SURFACE_DETECT  AT THE VAC/VAC BOUNDARY
-------------------------------------------------------------------------------------------------------------


Rerun shows that are getting SD on the Fake boundary in middle of PMT::

    RERUN=4772 N=0 POM=1 ./U4SimulateTest.sh 
    RERUN=4772 BP=junoPMTOpticalModel::DoIt N=0 POM=1 ./U4SimulateTest.sh 

::

    (lldb) 
    Process 52577 resuming
    junoPMTOpticalModel::DoIt@183:  pmtid 0 pmtcat 1 _qe 0.347509 _photon_energy/eV 2.952 n_glass 1.48426 n_coating 1.94133 k_coating 0 d_coating 36.49 n_photocathode 2.27348 k_photocathode 1.40706 d_photocathode 21.13 n_vacuum 1
    junoPMTOpticalModel::DoIt@261:  _cos_theta1 0.636195 _aoi 50.4914 m_label spho (gs:ix:id:gn   04772 4772[  0,  0,  0, 95])
    junoPMTOpticalModel::DoIt@293:  E_s2 1 fT_s 1.44814e-17 fT_p 5.87806e-17 T 1.44814e-17 fR_s 0.0318883 fR_p 0.223724 R 0.0318883 A 0.968112 fT_n 0.327437 fR_n 0.0255893 An 0.646974 escape_fac 0.53713
    Process 52577 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 2.1
        frame #0: 0x00000001008d54e6 libPMTSim.dylib`junoPMTOpticalModel::DoIt(this=0x000000010770e780, fastTrack=0x000000010770e980, fastStep=0x000000010770ead8) at junoPMTOpticalModel.cc:322
       319 	        fastStep.ProposeTrackStatus(fStopAndKill);
       320 	        if(rand_escape<escape_fac){
       321 	        // detected
    -> 322 	            fastStep.ProposeTotalEnergyDeposited(_photon_energy);
       323 	        }
       324 	    }else if(rand_absorb < A+R){
       325 	        // fastStep.ProposeTrackStatus(fStopAndKill);
    Target 0: (U4SimulateTest) stopped.
    (lldb) p A
    (G4double) $0 = 0.9681117487651012
    (lldb) p rand_absorb
    (G4double) $1 = 0.63633601726184885
    (lldb) p rand_escape
    (G4double) $2 = 0.40912593597398816
    (lldb) p escape_fac
    (G4double) $3 = 0.53713009155559488
    (lldb) 

    (lldb) p pos
    (G4ThreeVector) $4 = {
      data = ([0] = -183.61805248417411, [1] = 0, [2] = 0)     ## local frame along -X axis
    }
    (lldb) p dist1
    (G4double) $5 = 175.90799836311567

    (lldb) p pmtid                      ## SUSPECT THIS IS DISCREPANT AS N=1 GETTING SPECIAL HANDLING TO SET THIS TO CopyNo EVEN THOUGH ONE OF EACH 
    (int) $6 = 0
    (lldb) p pmtcat
    (int) $7 = 1
    (lldb) p _qe
    (G4double) $8 = 0.3475091505761605
    (lldb) 

    (lldb) p dir
    (G4ThreeVector) $11 = {
      data = ([0] = -0.77152860442434201, [1] = 0, [2] = 0.63619463417654443)
    }
    (lldb) p norm
    (G4ThreeVector) $12 = {
      data = ([0] = -0, [1] = -0, [2] = 1)
    }
    (lldb) 

    (lldb) p A+R
    (double) $13 = 1
    (lldb) p whereAmI
    (EWhereAmI) $14 = kInGlass         ## HUH: WRONG 
    (lldb) 

    (lldb) p dist1
    (G4double) $15 = 175.90799836311567
    (lldb) p dist2
    (G4double) $16 = 8.9999999999999999E+99
    (lldb) 

    (lldb) p track->GetVolume()
    (G4PVPlacement *) $18 = 0x000000010770c120
    (lldb) p track->GetVolume()->GetName()
    (const G4String) $19 = (std::__1::string = "nnvt_edge_phy")    ## HUH: NOT EXPECTED
    (lldb) p track->GetNextVolume()->GetName()
    (const G4String) $20 = (std::__1::string = "nnvt_edge_phy")
    (lldb) 


The "nnvt_edge_phy" is going to mess with the ModelTrigger giving kInGlass when actually in vacuum::

    124 
    125     if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner1_phys){
    126         whereAmI = kInVacuum;
    127     }else{
    128         whereAmI = kInGlass;
    129     }
    130 


RERUN=4772 BP="junoPMTOpticalModel::DoIt junoPMTOpticalModel::ModelTrigger" N=0 POM=1 ./U4SimulateTest.sh 




Developed "jcv ModelTrigger_Debug" to look into this, populated from "jcv junoPMTOpticalModel"
---------------------------------------------------------------------------------------------------

::

     27 struct ModelTrigger_Debug
     28 {   
     29     static std::vector<ModelTrigger_Debug> RECORD ;
     30     static UName PV ; 
     31     static UName MLV ;
     32     
     33     void add(){ RECORD.push_back(*this); }
     34     static NP* Array();
     35     
     36     double pos_x ;       // 00
     37     double pos_y ;       // 01
     38     double pos_z ;       // 02
     39     double time ;        // 03
     40     
     41     double dir_x ;       // 10
     42     double dir_y ;       // 11
     43     double dir_z ;       // 12
     44     double energy ;      // 13
     45     
     46     double   dist1 ;     // 20
     47     double   dist2 ;     // 21
     48     uint64_t mlv   ;     // 22
     49     uc8      etrig ;     // 23
     50     
     51     uint64_t index ;     // 30 
     52     uint64_t pv ;        // 31
     53     uint64_t whereAmI ;  // 32
     54     uint64_t trig ;      // 33
     55 };

::

    In [12]: t.photon.shape                                                                                                                                                     
    Out[12]: (1000, 4, 4)

    In [13]: imtd.shape    ## AVG of 2.5 ModelTrigger calls for each photon
    Out[13]: (2496,)

    In [4]: imtd = mtd[:,3,0].view(np.uint64)
    In [7]: imtd                                                                                                                                                                
    Out[7]: 
    array([998, 996, 994, 993, 992, 991, 990, 989, 988, 987, 986, 985, 984, 983, 982, 981, 980, 979, 978, 977, 977, 976, 975, 974, 973, 972, 971, 970, 969, 968, 966, 966, 965, 964, 963, 962, 961, 960,
           959, 958, 957, 956, 955, 954, 953, 952, 951, 950, 949, 948, ...,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  40,  39,  38,  37,  36,  35,  34,  33,  32,  31,  30,  29,  28,  27,
            26,  25,  24,  23,  22,  22,  22,  20,  19,  18,  17,  16,  15,  13,  12,  11,  10,   9,   7,   7,   6,   5,   4,   3,   2], dtype=uint64)

    In [8]: w_midline    ## indices of photons that end on the midline  
    Out[8]: array([123, 269, 321, 332, 400, 401, 402, 457, 543, 544, 546, 555, 561, 565, 569, 588, 598, 669, 724, 816])

    In [10]: w123 = np.where( imtd == 123 )[0] ; w123    ## ModelTrigger indices  
    Out[10]: array([2302, 2303, 2304, 2305, 2306, 2307, 2308, 2309]),


    In [20]: mtd[w123,3].view(np.uint64)
    Out[20]: 
    array([[123,   0,   1,   1],
           [123,   1,   2,   0],
           [123,   2,   2,   0],
           [123,   0,   1,   0],
           [123,   2,   1,   0],
           [123,   0,   1,   0],
           [123,   2,   1,   0],
           [123,   3,   1,   1]], dtype=uint64)


    In [30]: PV = np.array(t.ModelTrigger_Debug_meta.PV)                                                                                                                                             

    In [31]: np.c_[pv, PV[pv] ]                                                                                                                                                 
    Out[31]: 
    array([['0', 'nnvt_body_phys'],
           ['1', 'nnvt_inner1_phys'],
           ['2', 'nnvt_inner2_phys'],
           ['0', 'nnvt_body_phys'],
           ['2', 'nnvt_inner2_phys'],
           ['0', 'nnvt_body_phys'],
           ['2', 'nnvt_inner2_phys'],
           ['3', 'nnvt_tube_phy']], dtype='<U20')

    In [34]: MLV = np.array(t.ModelTrigger_Debug_meta.MLV)                                                                                                                      

    In [35]: MLV                                                                                                                                                                
    Out[35]: array(['nnvt_log', 'nnvt_body_log', 'nnvt_inner2_log', 'hama_log', 'hama_body_log', 'hama_inner2_log'], dtype='<U15')



    In [41]: np.c_[pv, PV[pv], mlv, MLV[mlv] ]
    Out[41]: 
    array([['0', 'nnvt_body_phys',   '0', 'nnvt_log'],
           ['1', 'nnvt_inner1_phys', '1', 'nnvt_body_log'],
           ['2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['0', 'nnvt_body_phys',   '0', 'nnvt_log'],
           ['2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['0', 'nnvt_body_phys',   '0', 'nnvt_log'],
           ['2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['3', 'nnvt_tube_phy',    '2', 'nnvt_inner2_log']], dtype='<U20')


    In [65]: mtd[:,0][w123]
    Out[65]: 
    array([[-188.086,    0.   ,  117.301,    0.612],
           [-188.086,    0.   ,  117.299,    0.612],
           [-188.086,    0.   ,  117.299,    0.612],
           [-244.43 ,    0.   ,  -34.138,    1.435],
           [-244.43 ,    0.   ,  -34.138,    1.435],
           [ -80.873,    0.   , -168.225,    2.513],
           [ -80.873,    0.   , -168.225,    2.513],
           [ -42.9  ,    0.   , -137.094,    2.763]])

    In [66]: np.c_[etrig, whereAmI, pv, PV[pv], mlv, MLV[mlv]][w123]                                                                                                            
    Out[66]: 
    array([['Y_GLASS', '1', '0', 'nnvt_body_phys', '0', 'nnvt_log'],
           ['N_TAIL', '2', '1', 'nnvt_inner1_phys', '1', 'nnvt_body_log'],
           ['N_PV_I2', '2', '2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['N_MIS_I2', '1', '0', 'nnvt_body_phys', '0', 'nnvt_log'],
           ['N_PV_I2', '1', '2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['N_I1>I2', '1', '0', 'nnvt_body_phys', '0', 'nnvt_log'],
           ['N_PV_I2', '1', '2', 'nnvt_inner2_phys', '1', 'nnvt_body_log'],
           ['Y_GLASS', '1', '3', 'nnvt_tube_phy', '2', 'nnvt_inner2_log']], dtype='<U20')




::

    epsilon:tests blyth$ APID=123 N=0 ./U4SimtraceTest.sh ana




