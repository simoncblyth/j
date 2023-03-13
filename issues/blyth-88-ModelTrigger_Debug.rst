blyth-88-ModelTrigger_Debug
=============================

* :doc:`blyth-88-quadrant-matching`


Speeddial
-----------

::

   jcv junoPMTOpticalModel
   jcv NNVTMCPPMTManager
   jcv HamamatsuR12860PMTManager
   jcv CustomG4OpBoundaryProcess
   jcv DsPhysConsOptical



WIP : Directing beam at NNVT PMT gives worse chi2  : Due to a zero dropout 
-----------------------------------------------------------------------------

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

* suspect that means ModelTrigger is firing when it should not for NNVT 


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


Many photons with history "TO BT BT SR SR SR SD" have an "L corner" double bounce 
with NNVT that means loads of photons heading back towards the midline coming 
off something other than inner2. 


::


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



HMM : LOOKS LIKE FASTSIM N=0 HAS ANOTHER BUG : SOMETIMES GETTING SURFACE_DETECT  AT THE VAC/VAC BOUNDARY
-------------------------------------------------------------------------------------------------------------

* see :doc:`blyth-88-revive-rerunning-single-photon`

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




HMM : ModelTrigger_Debug is storing in local frame, need that in global
--------------------------------------------------------------------------

Come up with the transform::

    epsilon:tests blyth$ ./stra_test.sh 
    .
         0.0000     0.0000    -1.0000     0.0000.
         0.0000     1.0000     0.0000     0.0000.
         1.0000     0.0000     0.0000     0.0000.
      -250.0000     0.0000     0.0000     1.0000.

    np.array([[  0.000,  0.000, -1.000,  0.000],[  0.000,  1.000,  0.000,  0.000],[  1.000,  0.000,  0.000,  0.000],[-250.000,  0.000,  0.000,  1.000]],dtype=np.float64)

                  O      0.0000     0.0000     0.0000     1.0000       (tr * O)   -250.0000     0.0000     0.0000     1.0000
                +sx    254.0000     0.0000     0.0000     1.0000     (tr * +sx)   -250.0000     0.0000  -254.0000     1.0000
                +sy      0.0000   254.0000     0.0000     1.0000     (tr * +sy)   -250.0000   254.0000     0.0000     1.0000
                +sz      0.0000     0.0000   186.0000     1.0000     (tr * +sz)    -64.0000     0.0000     0.0000     1.0000
                -sx   -254.0000     0.0000     0.0000     1.0000     (tr * -sx)   -250.0000     0.0000   254.0000     1.0000
                -sy      0.0000  -254.0000     0.0000     1.0000     (tr * -sy)   -250.0000  -254.0000     0.0000     1.0000
                -sz      0.0000     0.0000  -186.0000     1.0000     (tr * -sz)   -436.0000     0.0000     0.0000     1.0000



Split off into U4SimulateTest_mt.py for clarity
---------------------------------------------------

::

    In [1]: w_midline
    Out[1]: array([123, 269, 321, 332, 400, 401, 402, 457, 543, 544, 546, 555, 561, 565, 569, 588, 598, 669, 724, 816])

    In [5]: mt = np.where( imtd == 123 )[0] ; mt  ## model trigger indices for first midline photon
    Out[5]: array([2302, 2303, 2304, 2305, 2306, 2307, 2308, 2309])


epsilon:tests blyth$ POM=1 N=0 PIDX=123 ./U4SimulateTest.sh mt::

    PIDX : 321 

    np.c_[mt_index, mt_whereAmI, mt_trig, mt_etrig, mt_pv, mt_mlv][mt_index == PIDX] ## ModelTrigger_Debug mlv and pv for PIDX 
    [['321' 'kInGlass   ' '1' 'Y_GLASS ' 'nnvt_body_phys' 'nnvt_log']
     ['321' 'kInVacuum  ' '0' 'N_TAIL  ' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['321' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['321' 'kInGlass   ' '0' 'N_I1>I2 ' 'nnvt_body_phys' 'nnvt_log']
     ['321' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['321' 'kInVacuum  ' '1' 'Y_VACUUM' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['321' 'kInVacuum  ' '0' 'N_TAIL  ' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['321' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['321' 'kInGlass   ' '0' 'N_I1>I2 ' 'nnvt_body_phys' 'nnvt_log']
     ['321' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['321' 'kInGlass   ' '1' 'Y_GLASS ' 'nnvt_edge_phy' 'nnvt_inner2_log']]
    ## kInVacuum : ACTUALLY pv is inner1_phys 
    ## kInGlass  : ACTUALLY pv NOT inner1_phys 
    ## kUnset    : ACTUALLY pv is inner2_phys causing early exit 

     np.c_[mt_index, mt_time, mt_gpos[:,:3], mt_gdir[:,:3], mt_dist1, mt_dist2][mt_index == PIDX]  ## ModelTrigger_Debug for PIDX 
    [[ 321.       0.383  -82.928    0.      89.378   -1.       0.      -0.024    0.001  167.12 ]
     [ 321.       0.383  -82.929    0.      89.378   -0.995    0.       0.1    167.908  167.908]
     [ 321.       0.383  -82.929    0.      89.378   -0.995    0.       0.1    167.908  167.908]
     [ 321.       2.038 -406.135    0.     121.77     0.786    0.      -0.618  198.626    0.   ]
     [ 321.       2.038 -406.135    0.     121.77     0.786    0.      -0.618  198.626    0.   ]
     [ 321.       3.051 -250.       0.      -1.006    0.786    0.      -0.618  197.837      inf]
     [ 321.       3.711  -94.484    0.    -123.295   -0.994    0.       0.111  156.485  156.485]
     [ 321.       3.711  -94.484    0.    -123.295   -0.994    0.       0.111  156.485  156.485]
     [ 321.       5.368 -417.675    0.     -87.161    0.804    0.       0.594  208.461    0.   ]
     [ 321.       5.368 -417.675    0.     -87.161    0.804    0.       0.594  208.461    0.   ]
     [ 321.       5.705 -364.525    0.     -47.9      0.804    0.      -0.594  142.382      inf]]

    q[PIDX] ## 
    [b'TO BT BT SR BR SR SR SA                                                                         ']



Viz::

    epsilon:tests blyth$ POM=1 N=0 APID=123 ./U4SimtraceTest.sh ana



::

    In [3]: np.c_[w_midline,q[w_midline]]
    Out[3]: 
    array([[b'123', b'TO BT BT SR SR SR SD                                                                            '],
           [b'269', b'TO BT BT SR BR SR SR BT BR SR SD                                                                '],
           [b'321', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'332', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'400', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'401', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'402', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'457', b'TO BT BT SR SA                                                                                  '],
           [b'543', b'TO BT BT SR SD                                                                                  '],
           [b'544', b'TO BT BT SR SD                                                                                  '],
           [b'546', b'TO BT BT SR SA                                                                                  '],
           [b'555', b'TO BT BT SR BT BR SR SD                                                                         '],
           [b'561', b'TO BT BT SR SA                                                                                  '],
           [b'565', b'TO BT BT SR SD                                                                                  '],
           [b'569', b'TO BT BT SR SA                                                                                  '],
           [b'588', b'TO BT BT SR BR SR SD                                                                            '],
           [b'598', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'669', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'724', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'816', b'TO BT BT SR SR BR SR SR SR SA                                                                   ']], dtype='|S96')



YET another class of FastSim bug : kink at the midline
----------------------------------------------------------

::

    epsilon:tests blyth$ POM=1 N=0 APID=269 ./U4SimtraceTest.sh ana

    MODE : 2 
    PIDX : 269 

    np.c_[mt_index, mt_whereAmI, mt_trig, mt_etrig, mt_pv, mt_mlv][mt_index == PIDX] ## ModelTrigger_Debug mlv and pv for PIDX 
    [['269' 'kInGlass   ' '1' 'Y_GLASS ' 'nnvt_body_phys' 'nnvt_log']
     ['269' 'kInVacuum  ' '0' 'N_TAIL  ' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['269' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['269' 'kInGlass   ' '0' 'N_I1>I2 ' 'nnvt_body_phys' 'nnvt_log']
     ['269' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['269' 'kInVacuum  ' '1' 'Y_VACUUM' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['269' 'kInVacuum  ' '0' 'N_TAIL  ' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['269' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['269' 'kInGlass   ' '0' 'N_I1>I2 ' 'nnvt_body_phys' 'nnvt_log']
     ['269' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['269' 'kInGlass   ' '1' 'Y_GLASS ' 'nnvt_tube_phy' 'nnvt_inner2_log']
     ['269' 'kInVacuum  ' '1' 'Y_VACUUM' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['269' 'kInVacuum  ' '0' 'N_TAIL  ' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['269' 'kUnset     ' '0' 'N_PV_I2 ' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['269' 'kInGlass   ' '1' 'Y_GLASS ' 'nnvt_plate_phy' 'nnvt_inner2_log']]

    ## kInVacuum : ACTUALLY pv is inner1_phys 
    ## kInGlass  : ACTUALLY pv NOT inner1_phys 
    ## kUnset    : ACTUALLY pv is inner2_phys causing early exit 

     np.c_[mt_index, mt_time, mt_gpos[:,:3], mt_gdir[:,:3], mt_dist1, mt_dist2][mt_index == PIDX]  ## ModelTrigger_Debug for PIDX 
    [[ 269.       0.422  -91.357    0.     115.331   -0.999    0.      -0.032    0.001  158.725]
     [ 269.       0.422  -91.358    0.     115.331   -0.991    0.       0.137  160.159  160.159]
     [ 269.       0.422  -91.358    0.     115.331   -0.991    0.       0.137  160.159  160.159]
     [ 269.       1.954 -389.161    0.     156.612    0.609    0.      -0.793  228.449    0.   ]
     [ 269.       1.954 -389.161    0.     156.612    0.609    0.      -0.793  228.449    0.   ]
     [ 269.       3.118 -250.       0.     -24.559    0.609    0.      -0.793  199.529      inf]
     [ 269.       3.784 -128.456    0.    -182.796   -0.919    0.       0.395  132.275  132.275]
     [ 269.       3.784 -128.456    0.    -182.796   -0.919    0.       0.395  132.275  132.275]
     [ 269.       5.391 -418.225    0.     -58.373    0.919    0.       0.395  183.077    0.   ]
     [ 269.       5.391 -418.225    0.     -58.373    0.919    0.       0.395  183.077    0.   ]
     [ 269.       5.591 -382.189    0.     -42.9      0.919    0.      -0.395  143.86       inf]
     [ 269.       6.303 -250.       0.     -99.66     0.811    0.      -0.586  147.042      inf]
     [ 269.       6.794 -130.809    0.    -185.771   -0.745    0.       0.667  160.018  160.018]
     [ 269.       6.794 -130.809    0.    -185.771   -0.745    0.       0.667  160.018  160.018]
     [ 269.       8.403 -366.       0.      24.908    0.745    0.       0.667  155.735      inf]]

    q[PIDX] ## 
    [b'TO BT BT SR BR SR SR BT BR SR SD                                                                ']




Try ModelTriggerSimple_ impl
-----------------------------------------

::

    283 G4bool junoPMTOpticalModel::ModelTriggerSimple_(const G4FastTrack &fastTrack)
    284 {
    285     track = fastTrack.GetPrimaryTrack();
    286     pv = track->GetVolume() ;
    287     mlv = pv->GetMotherLogical();
    288 
    289     whereAmI = kUnset ;
    290 
    291 #ifdef PMTSIM_STANDALONE
    292     m_label = STrackInfo<spho>::GetRef(track);
    293     assert( m_label && "all photon tracks must be labelled" );
    294 #endif
    295 
    296     pos     = fastTrack.GetPrimaryTrackLocalPosition();
    297     dir     = fastTrack.GetPrimaryTrackLocalDirection();
    298     pol     = fastTrack.GetPrimaryTrackLocalPolarization();
    299     time    = fastTrack.GetPrimaryTrack()->GetGlobalTime();
    300     energy  = fastTrack.GetPrimaryTrack()->GetKineticEnergy();
    301 
    302     bool trig = false ;
    303     dist1 = Distance( _inner1_solid, pos, dir, in1 );
    304     dist2 = Distance( _inner2_solid, pos, dir, in2 );
    305     
    306     if( dist1 != kInfinity && dist1 < dist2  )
    307     {
    308         next_pos = pos + dir*dist1 ;
    309         next_norm = _inner1_solid->SurfaceNormal(next_pos);
    310     }   
    311     else if( dist2 != kInfinity )
    312     {
    313         next_pos = pos + dir*dist2 ;
    314         next_norm = _inner2_solid->SurfaceNormal(next_pos);
    315     }   
    316     else
    317     {
    318         assert(0); 
    319     }
    320     
    321     next_mct  = next_norm * dir ; 
    322     whereAmI  = next_mct < 0. ? kInGlass : kInVacuum ; // against normal is outside
    323     trig = next_pos.z() > 0. ;
    324     return trig ;
    325 }





::

    In [1]: w_midline
    Out[1]: array([ 25, 357, 742, 765, 791, 792, 851])

    In [2]: q[w_midline]
    Out[2]: 
    array([[b'TO BT BR BT BT BR SD                                                                            '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SR BT BT BR SR SR BR SD                                                                '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SR BR BR SD                                                                            '],
           [b'TO BT BT SD                                                                                     ']], dtype='|S96')


One impl having issue when dist1 and dist2 equal (7/1000)::

    In [2]: w_midline
    Out[2]: array([ 25, 357, 742, 765, 791, 792, 851])

    In [3]:  np.c_[mt_index, mt_pos[:,2],mt_time, mt_gpos[:,:3], mt_gdir[:,:3], mt_dist1, mt_dist2][mt_index == 25]
    Out[3]: 
    array([[  25.   ,   56.614,    0.892, -193.386,    0.   ,  236.219,   -0.989,    0.   ,   -0.147,    0.002,   57.236],
           [  25.   ,   56.612,    0.892, -193.388,    0.   ,  236.219,   -0.527,    0.   ,    0.85 ,    0.   ,      inf],
           [  25.   ,   56.612,    0.892, -193.388,    0.   ,  236.219,   -0.163,    0.   ,    0.987,    0.   ,      inf],
           [  25.   ,   56.612,    0.892, -193.388,    0.   ,  236.219,    0.045,    0.   ,    0.999,    0.   ,      inf],
           [  25.   ,   56.612,    0.892, -193.388,    0.   ,  236.219,   -0.733,    0.   ,   -0.68 ,   77.197,   77.197]])


Changed impl, now looks like distance zero getting stuck issue perhaps (9/1000)::

    In [11]: w_midline
    Out[11]: array([151, 209, 218, 233, 235, 239, 666, 746, 776])

    In [12]: t.photon.shape
    Out[12]: (1000, 4, 4)


    In [15]: np.c_[w_midline, q[w_midline]]
    Out[15]: 
    array([[b'151', b'TO BT BT SA                                                                                     '],
           [b'209', b'TO BT BT SR SA                                                                                  '],
           [b'218', b'TO BT BT SR SA                                                                                  '],
           [b'233', b'TO BT BT SR SD                                                                                  '],
           [b'235', b'TO BT BT SR SD                                                                                  '],
           [b'239', b'TO BT BT SR SA                                                                                  '],
           [b'666', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'746', b'TO BT BT SA                                                                                     '],
           [b'776', b'TO BT BT SA                                                                                     ']], dtype='|S96')

::

    In [19]: np.c_[mt_index,mt_trig, mt_dist1, mt_dist2, mt_next_mct, mt_gpos[:,:3],mt_gnext_pos[:,:3]][mt_index == 151],np.c_[mt_index,mt_whereAmI][mt_index == 151]
    Out[19]: 
    (array([[ 151.   ,    1.   ,    0.001,  128.155,   -0.85 , -122.068,    0.   ,  174.159, -122.069,    0.   ,  174.159],
            [ 151.   ,    1.   ,  133.239,  133.239,    0.96 , -122.069,    0.   ,  174.159, -250.   ,    0.   ,  211.392]]),
     array([['151', 'kInGlass   '],
            ['151', 'kInVacuum  ']], dtype='<U20'))


    In [10]: np.c_[mt_index,mt_trig, mt_dist1, mt_dist2, mt_next_mct, mt_gpos[:,:3],mt_gnext_pos[:,:3]][mt_index == PIDX]
    Out[10]: 
    array([[ 209.   ,    1.   ,    0.001,  145.526,   -0.908, -104.615,    0.   ,  145.261, -104.616,    0.   ,  145.261],
           [ 209.   ,    0.   ,  148.196,  148.196,    0.981, -104.616,    0.   ,  145.261, -250.   ,    0.   ,  173.992],
           [ 209.   ,    0.   ,    0.   ,  112.686,    0.981, -250.   ,    0.   ,  173.992, -250.   ,    0.   ,  173.992],
           [ 209.   ,    1.   ,  395.503,  395.503,   -0.28 , -360.548,    0.   ,  195.839, -250.   ,    0.   , -183.9  ]])





Changed impl appears to fix the midliners but huge chi2 diff related to SA/SD
-----------------------------------------------------------------------------------

* somehow N=0 is giving "TO BT BT SR SD" ( which is not expected as backwards _qe should be zero )
* N=1 give the expected "TO BT BT SR SA" 

::

    epsilon:tests blyth$ POM=1 N=0 APID=3 ./U4SimtraceTest.sh ana 



    epsilon:tests blyth$ POM=1 N=0 PIDX=3 ./U4SimulateTest.sh mt 

    PIDX : 3 

    np.c_[mt_index, mt_whereAmI, mt_trig, mt_etrig, mt_pv, mt_mlv][mt_index == PIDX] ## ModelTrigger_Debug mlv and pv for PIDX 
    [['3' 'kInGlass   ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['3' 'kInVacuum  ' '0' '' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['3' 'kInVacuum  ' '0' '' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['3' 'kInGlass   ' '0' '' 'nnvt_body_phys' 'nnvt_log']
     ['3' 'kInGlass   ' '0' '' 'nnvt_inner2_phys' 'nnvt_body_log']
     ['3' 'kInVacuum  ' '0' '' 'nnvt_inner1_phys' 'nnvt_body_log']]

     np.c_[
     mt_index, mt_pos[:,2],mt_time,     mt_gpos[:,:3],              mt_gdir[:,:3],        mt_dist1, mt_dist2][mt_index == PIDX]  
                                      
    [[   3.     156.913    0.43         -93.087  0.  -119.822      -0.999 0.  0.034         0.001  157.003]
     [   3.     156.912    0.43         -93.088  0.  -119.822      -0.989 0. -0.145       158.58   158.58 ]
                                      
     [   3.       0.       1.238       -250.     0.  -142.762      -0.989 0. -0.145        -0.     137.017]
                                      
     [   3.    -135.576    1.936       -385.576  0.  -162.583       0.57  0.  0.822       237.899  237.899]
     [   3.    -135.576    1.936       -385.576  0.  -162.583       0.57  0.  0.822       237.899  237.899]
                                      
     [   3.       0.       3.149       -250.     0.    32.904       0.57  0.  0.822       196.419    0.   ]]

    q[PIDX] ## 
    [b'TO BT BT SR SD                         

    In [5]: t.record[3,:5,0]
    Out[5]: 
    array([[   0.   ,    0.   , -120.   ,    0.   ],
           [ -87.828,    0.   , -120.   ,    0.403],
           [ -93.088,    0.   , -119.822,    0.43 ],
           [-385.576,    0.   , -162.583,    1.936],
           [-138.063,    0.   ,  194.307,    4.15 ]], dtype=float32)


    In [4]: np.c_[mt_index, mt_gnext_pos[:,:3], mt_gnext_norm, mt_next_mct ][mt_index == 3]
    Out[4]: 
    array([[   3.   ,  -93.088,    0.   , -119.822,    0.93 ,    0.   ,   -0.367,    0.   ,   -0.942],
           [   3.   , -250.   ,    0.   , -142.762,   -1.   ,    0.   ,    0.   ,    0.   ,    0.989],
           [   3.   , -250.   ,    0.   , -142.762,   -1.   ,    0.   ,    0.   ,    0.   ,    0.989],
           [   3.   , -250.   ,    0.   ,   32.904,   -1.   ,    0.   ,    0.   ,    0.   ,   -0.57 ],
           [   3.   , -250.   ,    0.   ,   32.904,   -1.   ,    0.   ,    0.   ,    0.   ,   -0.57 ],
           [   3.   , -250.   ,    0.   ,   32.904,    1.   ,    0.   ,    0.   ,    0.   ,    0.57 ]])

    In [5]: np.c_[mt_index, mt_gpos[:,:3], mt_gnext_pos[:,:3], mt_gnext_norm, mt_next_mct ][mt_index == 3]
    Out[5]: 
    array([[   3.   ,  -93.087,    0.   , -119.822,  -93.088,    0.   , -119.822,    0.93 ,    0.   ,   -0.367,    0.   ,   -0.942],
           [   3.   ,  -93.088,    0.   , -119.822, -250.   ,    0.   , -142.762,   -1.   ,    0.   ,    0.   ,    0.   ,    0.989],
           [   3.   , -250.   ,    0.   , -142.762, -250.   ,    0.   , -142.762,   -1.   ,    0.   ,    0.   ,    0.   ,    0.989],
           [   3.   , -385.576,    0.   , -162.583, -250.   ,    0.   ,   32.904,   -1.   ,    0.   ,    0.   ,    0.   ,   -0.57 ],
           [   3.   , -385.576,    0.   , -162.583, -250.   ,    0.   ,   32.904,   -1.   ,    0.   ,    0.   ,    0.   ,   -0.57 ],
           [   3.   , -250.   ,    0.   ,   32.904, -250.   ,    0.   ,   32.904,    1.   ,    0.   ,    0.   ,    0.   ,    0.57 ]])

          FAILURE TO LAUNCH ON THE LAST LINE 



     np.c_[
    mt_index, mt_pos[:,2],mt_time,    mt_gpos[:,:3],               mt_gdir[:,:3],                  mt_dist1, mt_dist2][mt_index == PIDX]  

    [[   3.     156.913    0.43        -93.087    0.    -119.822   -0.999    0.       0.034         0.001  157.003]
     [   3.     156.912    0.43        -93.088    0.    -119.822   -0.989    0.      -0.145       158.58   158.58 ]
     [   3.       0.       1.238      -250.       0.    -142.762   -0.989    0.      -0.145        -0.     137.017]
     [   3.    -135.576    1.936      -385.576    0.    -162.583    0.57     0.       0.822       237.899  237.899]
     [   3.    -135.576    1.936      -385.576    0.    -162.583    0.57     0.       0.822       237.899  237.899]
     [   3.       0.       3.149      -250.       0.      32.904    0.57     0.       0.822       196.419    0.   ]]

    q[PIDX] ## 
    [b'TO BT BT SR SD                                                                                  ']





    In [6]: np.c_[mt_whereAmI, mt_trig][mt_index == 3]
    Out[6]: 
    array([['kInGlass   ', '1'],
           ['kInVacuum  ', '0'],
           ['kInVacuum  ', '0'],
           ['kInGlass   ', '0'],
           ['kInGlass   ', '0'],
           ['kInVacuum  ', '0']], dtype='<U20')    ## WHY FAIL TO TRIGGER FASTSIM HERE ? 


    epsilon:tests blyth$ POM=1 N=0 RERUN=3 ./U4SimulateTest.sh 

    epsilon:tests blyth$ POM=1 N=0 RERUN=3 BP=junoPMTOpticalModel::DoIt ./U4SimulateTest.sh 

    epsilon:tests blyth$ POM=1 N=0 RERUN=3 BP="junoPMTOpticalModel::DoIt CustomG4OpBoundaryProcess::DoAbsorption" ./U4SimulateTest.sh 


HUH theEfficiency is 1., Question is why this failed to trigger::

    Process 56484 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 2.1
        frame #0: 0x00000001008fa200 libPMTSim.dylib`CustomG4OpBoundaryProcess::DoAbsorption(this=0x000000010d962550) at CustomG4OpBoundaryProcess.hh:337
       334 	inline
       335 	void CustomG4OpBoundaryProcess::DoAbsorption()
       336 	{
    -> 337 	              theStatus = Absorption;
       338 	
       339 	              if ( G4BooleanRand(theEfficiency) ) {
       340 	
    Target 0: (U4SimulateTest) stopped.
    (lldb) p theEfficiency
    (G4double) $0 = 1
    (lldb) 


HUH why DielectricMetal ?::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 2.1
      * frame #0: 0x00000001008fa200 libPMTSim.dylib`CustomG4OpBoundaryProcess::DoAbsorption(this=0x000000010d962550) at CustomG4OpBoundaryProcess.hh:337
        frame #1: 0x00000001008fbf8c libPMTSim.dylib`CustomG4OpBoundaryProcess::DielectricMetal(this=0x000000010d962550) at CustomG4OpBoundaryProcess.cc:924
        frame #2: 0x00000001008f61d3 libPMTSim.dylib`CustomG4OpBoundaryProcess::PostStepDoIt(this=0x000000010d962550, aTrack=0x000000010b84b2d0, aStep=0x000000010778f4a0) at CustomG4OpBoundaryProcess.cc:641
        frame #3: 0x0000000102b0d7db libG4tracking.dylib`G4SteppingManager::InvokePSDIP(this=0x000000010778f310, np=3) at G4SteppingManager2.cc:538
        frame #4: 0x0000000102b0d64d libG4tracking.dylib`G4SteppingManager::InvokePostStepDoItProcs(this=0x000000010778f310) at G4SteppingManager2.cc:510
        frame #5: 0x0000000102b08daa libG4tracking.dylib`G4SteppingManager::Stepping(this=0x000000010778f310) at G4SteppingManager.cc:209
        frame #6: 0x0000000102b1f86f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x000000010778f2d0, apValueG4Track=0x000000010b84b2d0) at G4TrackingManager.cc:126
        frame #7: 0x00000001029e571a libG4event.dylib`G4EventManager::DoProcessing(this=0x000000010778f240, anEvent=0x000000010b849880) at G4EventManager.cc:185
        frame #8: 0x00000001029e6c2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x000000010778f240, anEvent=0x000000010b849880) at G4EventManager.cc:338
        frame #9: 0x00000001028f29e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x000000010778f060, i_event=0) at G4RunManager.cc:399
        frame #10: 0x00000001028f2815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x000000010778f060, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #11: 0x00000001028f0cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x000000010778f060, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #12: 0x0000000100037c5d U4SimulateTest`U4SimulateTest::BeamOn(this=0x00007ffeefbfdac8) at U4SimulateTest.cc:66
        frame #13: 0x000000010003850e U4SimulateTest`main(argc=1, argv=0x00007ffeefbfe028) at U4SimulateTest.cc:119
        frame #14: 0x00007fff55514015 libdyld.dylib`start + 1
        frame #15: 0x00007fff55514015 libdyld.dylib`start + 1
    (lldb) f 1
    frame #1: 0x00000001008fbf8c libPMTSim.dylib`CustomG4OpBoundaryProcess::DielectricMetal(this=0x000000010d962550) at CustomG4OpBoundaryProcess.cc:924
       921 	           rand = G4UniformRand();
       922 	           if ( rand > theReflectivity && n == 1 ) {
       923 	              if (rand > theReflectivity + theTransmittance) {
    -> 924 	                DoAbsorption();
       925 	              } else {
       926 	                theStatus = Transmission;
       927 	                NewMomentum = OldMomentum;
    (lldb) p theReflectivity
    (G4double) $1 = 0
    (lldb) p theTransmittance
    (G4double) $2 = 0
    (lldb) p rand
    (G4double) $3 = 0.64903362508319518
    (lldb) 


    (lldb) p m_custom_status
    (char) $4 = 'X'
    (lldb) p OpticalSurface
    (G4OpticalSurface *) $5 = 0x000000010bfb4f30
    (lldb) p OpticalSurface->GetName()
    (const G4String) $6 = (std::__1::string = "nnvt_Photocathode_opsurf")
    (lldb) p OpticalSurface->GetType()
    (const G4SurfaceType) $7 = dielectric_metal
    (lldb) 




Failed the trigger because the impl was requring dist1 < dist2, changed to::

    302     // note split inner is an annoyance here, would be cleaner without the split
    303         
    304     dist1 = Distance( _inner1_solid, pos, dir, in1 );
    305     dist2 = Distance( _inner2_solid, pos, dir, in2 );
    306 
    307     if( dist1 != kInfinity )
    308     {   
    309         next_pos = pos + dir*dist1 ;
    310         next_norm = _inner1_solid->SurfaceNormal(next_pos);
    311     }   
    312     else if( dist2 != kInfinity )
    313     {   
    314         next_pos = pos + dir*dist2 ;
    315         next_norm = _inner2_solid->SurfaceNormal(next_pos);
    316     }
    317     else
    318     {
    319         assert(0);
    320     }
    321         
    322     next_mct  = next_norm * dir ;
    323     whereAmI  = next_mct < 0. ? kInGlass : kInVacuum ; // against normal is outside
    324     return next_pos.z() > 1e-4 ;    
    325         




After that still big discrep
-------------------------------

* issue may be lacking some fake skipping 


::

    c2sum :   120.4095 c2n :     8.0000 c2per:    15.0512 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                       ' ' 0' '   368    372' ' 0.0216' '     4      0']
     [' 1' 'TO BT SA                       ' ' 1' '   303    288' ' 0.3807' '     0      3']

     [' 2' 'TO BT BT SR BT BT SA           ' ' 2' '     8    104' '82.2857' '    61     56']

     [' 3' 'TO BT BT SR SA                 ' ' 3' '    96     76' ' 2.3256' '     8     40']
     [' 4' 'TO BT BR BT SA                 ' ' 4' '     4     44' '33.3333' '   446     18']
     [' 5' 'TO BT BT SR BR SA              ' ' 5' '    36     29' ' 0.7538' '    20    112']
     [' 6' 'TO BT BT SA                    ' ' 6' '    23     26' ' 0.1837' '   112      4']

     [' 7' 'TO BT BT SR BT SA              ' ' 7' '    25      0' ' 0.0000' '   162     -1']

     [' 8' 'TO BT BT SR BR SR SR SA        ' ' 8' '    19     13' ' 1.1250' '    18     51']
     [' 9' 'TO BT BT SR BR SR SR BT BT SA  ' ' 9' '     1     19' ' 0.0000' '   659     33']
     ['10' 'TO BT BT SR BT BR SA           ' '10' '    10      0' ' 0.0000' '    79     -1']
     ['11' 'TO BT BT SR BT BR SR SR SA     ' '11' '     8      0' ' 0.0000' '    23     -1']
     ['12' 'TO BT BR SA                    ' '12' '     6      0' ' 0.0000' '    11     -1']


::

    epsilon:tests blyth$ POM=1 N=0 APID=61 AOPT=idx ./U4SimtraceTest.sh ana

    POM=1 N=0 APID=61 ./U4SimtraceTest.sh ana


    In [6]: q[61], t.record[61,:7,0]
    Out[6]: 
    (array([b'TO BT BT SR BT BT SA                                                                            '], dtype='|S96'),
     array([[   0.   ,    0.   , -120.   ,    0.   ],
            [ -87.828,    0.   , -120.   ,    0.403],
            [ -93.088,    0.   , -119.822,    0.43 ],
            [-385.576,    0.   , -162.583,    1.936],
            [-138.063,    0.   ,  194.307,    3.804],
            [-138.063,    0.   ,  194.307,    3.804],
            [-138.063,    0.   ,  194.307,    3.804]], dtype=float32))      

    ## repeated record positions suggests are missing some U4Step fake suppression


Use UName URecorder::SPECS to collect unique U4Step::Spec indices for each step:: 

    In [6]: SPECS = np.array(t.TRS_names.lines)

    In [11]: q[61]
    Out[11]: array([b'TO BT BT SR BT BT SA                                                                            '], dtype='|S96')

    In [12]: np.c_[SPECS[t.aux[61,:7,2,3].view(np.int32)]]
    Out[12]: 
    array([['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Pyrex/Pyrex:AroundCircle1/nnvt_body_phys'],
           ['Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys']], dtype='<U47')

    In [2]: np.c_[st[61]]
    Out[2]: 
    array([['UNSET'],
           ['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Pyrex/Pyrex:AroundCircle1/nnvt_body_phys'],
           ['Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['UNSET'],
           ['UNSET'],
           ['UNSET'],


    UserSteppingAction_Optical@612:  l.id  61 step_mm    87.8283 abbrev BT spec              Water/Pyrex:Water_lv_pv/AroundCircle1 is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm     5.2615 abbrev BT spec           Pyrex/Pyrex:AroundCircle1/nnvt_body_phys is_fake YES FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm     0.0011 abbrev BT spec          Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm   158.5802 abbrev BT spec    Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys is_fake YES FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm   137.0169 abbrev SR spec       Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm     0.0000 abbrev NA spec       Pyrex/Vacuum:nnvt_body_phys/nnvt_inner2_phys is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm   237.8992 abbrev BT spec    Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys is_fake YES FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm   196.4194 abbrev BT spec    Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm     0.0000 abbrev BT spec          Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys is_fake NO  FAKES_SKIP YES
    UserSteppingAction_Optical@612:  l.id  61 step_mm     0.0000 abbrev SA spec          Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys is_fake NO  FAKES_SKIP YES

    PostUserTrackingAction_Optical@364:  l.id    61 seq TO BT BT SR BT BT SA





    In [13]: t.record[61,:7,0]
    Out[13]: 
    array([[   0.   ,    0.   , -120.   ,    0.   ],
           [ -87.828,    0.   , -120.   ,    0.403],
           [ -93.088,    0.   , -119.822,    0.43 ],
           [-385.576,    0.   , -162.583,    1.936],
           [-138.063,    0.   ,  194.307,    3.804],
           [-138.063,    0.   ,  194.307,    3.804],
           [-138.063,    0.   ,  194.307,    3.804]], dtype=float32)


HUH : Its as if fakes are not being skipped ? 

::

    epsilon:tests blyth$ POM=1 N=0 PIDX=61 ./U4SimulateTest.sh run_mt





Current fakes::

    086 if [ "$VERSION" == "0" ]; then
     87     f0=Pyrex/Pyrex:AroundCircle0/hama_body_phys
     88     f1=Pyrex/Pyrex:hama_body_phys/AroundCircle0
     89     f2=Vacuum/Vacuum:hama_inner1_phys/hama_inner2_phys
     90     f3=Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys
     91 
     92     f4=Pyrex/Pyrex:AroundCircle1/nnvt_body_phys
     93     f5=Pyrex/Pyrex:nnvt_body_phys/AroundCircle1
     94     f6=Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys
     95     f7=Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys
     96 
     97     export U4Recorder__FAKES="$f0,$f1,$f2,$f3,$f4,$f5,$f6,$f7"
     98     export U4Recorder__FAKES_SKIP=1
     99     echo $BASH_SOURCE : U4Recorder__FAKES_SKIP ENABLED 
    100 fi




::

    epsilon:tests blyth$ POM=1 N=1 BPID=56 BOPT=idx  ./U4SimtraceTest.sh ana     ## this gets out to Rock

    POM=1 N=1 PIDX=56 ./U4SimulateTest.sh mt

    In [3]: t.record[56,:7,0]
    Out[3]: 
    array([[   0.   ,    0.   , -120.   ,    0.   ],
           [ -87.828,    0.   , -120.   ,    0.403],
           [ -93.088,    0.   , -119.822,    0.43 ],
           [-385.576,    0.   , -162.583,    1.416],
           [-138.063,    0.   ,  194.307,    2.864],
           [-134.91 ,    0.   ,  198.18 ,    2.89 ],
           [ -54.504,    0.   ,  300.   ,    3.485]], dtype=float32)

    In [1]: SPECS = np.array(t.TRS_names.lines) 

    In [2]: np.c_[SPECS[t.aux[56,:7,2,3].view(np.int32)]]
    Out[2]: 
    array([['Water/Pyrex:Water_lv_pv/AroundCircle1'],   ## THIS SHOULD PROBABLY BE BLANK ? CORRES TO THE "TO" first step 
           ['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Pyrex/Vacuum:AroundCircle1/nnvt_inner_phys'],
           ['Vacuum/Pyrex:nnvt_inner_phys/AroundCircle1'],
           ['Vacuum/Pyrex:nnvt_inner_phys/AroundCircle1'],
           ['Pyrex/Water:AroundCircle1/Water_lv_pv'],
           ['Water/Rock:Water_lv_pv/Rock_lv_pv']], dtype='<U44')


Huh those are N=1 specs, no need for fakes there. 

Change UName to place UNSET in 0th place. 



Debug Lack of escapes to Rock in N=0 
-----------------------------------------


Suspect getting very few escapes to Rock in N=0::

    N:0
    np.c_[n_st,u_st][np.argsort(n_st)[::-1]]
    [['28616' 'UNSET']
     ['1038' 'Pyrex/Pyrex:AroundCircle1/nnvt_body_phys']
     ['1000' 'Water/Pyrex:Water_lv_pv/AroundCircle1']
     ['674' 'Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys']
     ['491' 'Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys']
     ['105' 'Vacuum/Steel:nnvt_inner2_phys/nnvt_tube_phy']
     ['49' 'Vacuum/Steel:nnvt_inner2_phys/nnvt_edge_phy']
     ['19' 'Vacuum/Steel:nnvt_inner2_phys/nnvt_plate_phy']
     ['7' 'Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy']
     ['1' 'Water/Rock:Water_lv_pv/Rock_lv_pv']]

    In [2]: np.c_[SPECS]
    Out[2]: 
    array([['UNSET'],
           ['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Pyrex/Pyrex:AroundCircle1/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys'],
           ['Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_tube_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_edge_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_plate_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy'],
           ['Water/Rock:Water_lv_pv/Rock_lv_pv']], dtype='<U47')

Only one gets to Rock and thats an external bounce::

    In [3]: np.where( st_ == 10 )
    Out[3]: (array([5]), array([2])

    In [4]: q[5]                  
    Out[4]: array([b'TO BR SA                                                                                        '], dtype='|S96')


Supect issue with FAKES skipping to disable that.



N:1 168/1000 manage to escape to Rock
-----------------------------------------

::

    N:1
    np.c_[n_st,u_st][np.argsort(n_st)[::-1]]
    [['28801' 'UNSET']
     ['998' 'Water/Pyrex:Water_lv_pv/AroundCircle1']
     ['996' 'Pyrex/Vacuum:AroundCircle1/nnvt_inner_phys']
     ['750' 'Vacuum/Pyrex:nnvt_inner_phys/AroundCircle1']
     ['178' 'Pyrex/Water:AroundCircle1/Water_lv_pv']
     ['168' 'Water/Rock:Water_lv_pv/Rock_lv_pv']
     ['84' 'Vacuum/Steel:nnvt_inner_phys/nnvt_tube_phy']
     ['10' 'Water/Pyrex:Water_lv_pv/AroundCircle0']
     ['10' 'Pyrex/Vacuum:AroundCircle0/hama_inner_phys']
     ['3' 'Vacuum/Steel:nnvt_inner_phys/nnvt_edge_phy']
     ['2' 'Vacuum/Steel:hama_inner_phys/hama_shield_phy']]

    In [17]: t.photon[np.where( st_ == 5 )[0]][:,0].shape
    Out[17]: (168, 4)

    In [16]: t.photon[np.where( st_ == 5 )[0]][:,0]
    Out[16]: 
    array([[  99.953,    0.   , -300.   ,    1.643],
           [  99.953,    0.   , -300.   ,    1.643],
           [  26.548,    0.   ,  300.   ,    5.889],
           [  99.953,    0.   , -300.   ,    1.643],
           [  99.953,    0.   , -300.   ,    1.643],
           [  99.953,    0.   , -300.   ,    1.643],

    In [18]: q[np.where( st_ == 5 )[0]]
    Out[18]: 
    array([[b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SR BR SR SR BT BT SA                                                                   '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BR BT SA                                                                                  '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BR SR SR BT BT SA                                                                   '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT BT SR BT BT SA                                                                            '],





Return to one_pmt shooting verically upwards from vacumm to debug in simpler situation
-----------------------------------------------------------------------------------------

N=1::

    POM=1 N=1 ./U4SimulateTest.sh ph 

    In [6]: N,t.record[1,:4,0]
    Out[6]: 
    (1,
     array([[  0.   ,   0.   , 100.   ,   0.   ],
            [  0.   ,   0.   , 179.   ,   0.264],
            [  0.   ,   0.   , 184.001,   0.289],
            [  0.   ,   0.   , 200.   ,   0.362]], dtype=float32))

    In [7]: np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index
    Out[7]: 
    array([[b'350', b'17', b'TO BR SA        bounce then absorbed on mcp                                                     '],
           [b'331', b'1', b'TO BT BT SA      escape to rock                                                                 '],
           [b'317', b'0', b'TO SA                                                                                           '],
           [b'1', b'504', b'TO BT BT AB      absorbed in water before reaching rock                                         '],
           [b'1', b'429', b'TO BT BR SD      curious one : bounces back from Pyrex/Water vacuum                             ']], dtype='|S96')

::

    epsilon:tests blyth$ POM=1 N=1 BPID=429 ./U4SimtraceTest.sh ana



Initially without any U4Recorder__FAKE skipping.

N=0::

    POM=1 N=0 ./U4SimulateTest.sh ph 

    In [1]: np.c_[qn,qi,qu][quo]
    Out[1]: 
    array([[b'357', b'6', b'TO BR BT SA      bounce then absorbed on mcp : extra BT is the fake                             '],
           [b'306', b'2', b'TO SA                                                                                           '],
           [b'126', b'1', b'TO BT BR BT SA                                                                                  '],
           [b'100', b'0', b'TO BT SA                                                                                        '],
           [b'39', b'4', b'TO BT BT BR BT SA                                                                               '],
           [b'37', b'52', b'TO BT BT SA                                                                                     '],
           [b'13', b'66', b'TO BT BT BT BR BT SA                                                                            '],
           [b'7', b'36', b'TO BT BT BT SA                                                                                  '],
           [b'4', b'253', b'TO BT BT BT BT SA                                                                               '],
           [b'4', b'564', b'TO BT BT BT BT BT SA                                                                            '],
           [b'3', b'605', b'TO BT BT BT BT BR BT SA                                                                         '],
           [b'2', b'207', b'TO BT BT BT BT BT BT SA                                                                         '],
           [b'2', b'61', b'TO BT BT BT BT BT BR BT SA                                                                      ']], dtype='|S96')


    ## ABOVE HAS STEP STUCK ISSUES, BELOW REQUIRES dist1 > 0 TO GET A ModelTrigger SEEMS TO AVOID THE STEP STUCK ISSUE

    In [1]:  np.c_[qn,qi,qu][quo]
    Out[1]: 
    array([[b'368', b'3', b'TO BR BT SA                                                                                     '],
           [b'321', b'1', b'TO BT BT BT SA                                                                                  '],
           [b'310', b'0', b'TO SA                                                                                           '],
           [b'1', b'965', b'TO BT BT AB                                                                                     ']], dtype='|S96')





    POM=1 N=0 APID=6 ./U4SimtraceTest.sh ana

    POM=1 N=0 APID=61 ./U4SimtraceTest.sh ana


    In [2]: t.record[61,:9,0]    ## WOW : STEPS REALLY GETTING HUNG UP 
    Out[2]: 
    array([[   0.   ,    0.   ,  100.   ,    0.   ],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,  179.   ,    0.264],
           [   0.   ,    0.   ,    0.   ,    0.861],
           [   0.   ,    0.   , -126.   ,    1.281]], dtype=float32)

    In [5]: t.record[207,:8,0]
    Out[5]: 
    array([[  0.   ,   0.   , 100.   ,   0.   ],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.   ,   0.264]], dtype=float32)

    PIDX:61
    N:0
    np.c_[n_st,u_st][np.argsort(n_st)[::-1]]
    [['30920' 'UNSET']
     ['540' 'Water/Pyrex:Water_lv_pv/AroundCircle1']
     ['540' 'Pyrex/Pyrex:AroundCircle1/nnvt_body_phys']]

    np.c_[mt_index, mt_whereAmI, mt_trig, mt_etrig, mt_pv, mt_mlv][mt_index == PIDX] ## ModelTrigger_Debug mlv and pv for PIDX 
    [['61' 'kInVacuum  ' '1' '' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['61' 'kInVacuum  ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['61' 'kInVacuum  ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['61' 'kInVacuum  ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['61' 'kInVacuum  ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['61' 'kInVacuum  ' '1' '' 'nnvt_body_phys' 'nnvt_log']
     ['61' 'kInVacuum  ' '0' '' 'nnvt_inner1_phys' 'nnvt_body_log']
     ['61' 'kInVacuum  ' '0' '' 'nnvt_inner2_phys' 'nnvt_body_log']]
    ## kInVacuum : ACTUALLY pv is inner1_phys 
    ## kInGlass  : ACTUALLY pv NOT inner1_phys 
    ## kUnset    : ACTUALLY pv is inner2_phys causing early exit 

    np.c_[mt_index, mt_pos[:,2],mt_time, mt_gpos[:,:3], mt_gdir[:,:3], mt_dist1, mt_dist2][mt_index == PIDX]  ## ModelTrigger_Debug for PIDX 
    [[ 61.    100.      0.      0.      0.    100.      0.      0.      1.     79.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.      1.      0.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.      1.      0.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.      1.      0.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.      1.      0.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.      1.      0.        inf]
     [ 61.    179.      0.264   0.      0.    179.      0.      0.     -1.    179.    179.   ]
     [ 61.      0.      0.861   0.      0.      0.      0.      0.     -1.     -0.    168.225]]

    q[PIDX] ## 
    [b'TO BT BT BT BT BT BR BT SA                                                                      ']

::

    In [5]: mt_dist1[mt_index == PIDX]
    Out[5]: array([ 79.,   0.,   0.,   0.,   0.,   0., 179.,  -0.])

    In [9]: np.where( mt_dist1[mt_index == PIDX]  == 0. )
    Out[9]: (array([1, 2, 3, 4, 5, 7]),)

    ## HMM FastSim is triggering but dist1 is precisely zero so nothing happens 




Step specs look wrong::

    In [6]: np.c_[t.record[1,:5,0], st[1,:5]]
    Out[6]: 
    array([['0.0', '0.0', '100.0', '0.0', 'UNSET'],
           ['0.0', '0.0', '179.0', '0.2635159', 'UNSET'],
           ['0.0', '0.0', '179.001', '0.26351923', 'Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['0.0', '0.0', '184.001', '0.28019744', 'Pyrex/Pyrex:AroundCircle1/nnvt_body_phys'],
           ['0.0', '0.0', '200.0', '0.35357454', 'Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys']], dtype='<U47')

    In [8]: q[1]
    Out[8]: array([b'TO BT BT BT SA                                                                                  '], dtype='|S96')


* THIS WAS CAUSED BY USING STALE SPECS, AVOID THE ISSUE BY SEPARATING USING A DUMMY ARRAY TO HOLD THE SPECS 


one_pmt is lacking fake skips causing huge chi2
---------------------------------------------------

::

    np.c_[aqn,aqi,aqu][aquo][lim]  ## aexpr : unique histories aqu in descending count aqn order, aqi first index 
    [[b'3707' b'0' b'TO BR BT SA                                                                                     ']
     [b'3260' b'4' b'TO BT BT BT SA                                                                                  ']
     [b'3020' b'1' b'TO SA                                                                                           ']
     [b'8' b'1933' b'TO BT BT AB                                                                                     ']
     [b'3' b'5253' b'TO BT BT BR BT BT BT SA                                                                         ']
     [b'1' b'5599' b'TO BT BT BR BT SD                                                                               ']
     [b'1' b'4511' b'TO BT BT BR BT SA                                                                               ']]

    np.c_[bqn,bqi,bqu][bquo][lim]  ## bexpr : unique histories bqu in descending count bqn order, bqi first index 
    [[b'3675' b'0' b'TO BR SA                                                                                        ']
     [b'3259' b'3' b'TO BT BT SA                                                                                     ']
     [b'3048' b'2' b'TO SA                                                                                           ']
     [b'10' b'165' b'TO BT AB                                                                                        ']
     [b'4' b'1085' b'TO BT BR SD                                                                                     ']
     [b'2' b'5535' b'TO BT BR SA                                                                                     ']
     [b'1' b'9504' b'TO BT BT AB                                                                                     ']
     [b'1' b'1802' b'TO BT BR BR BT SA                                                                               ']]
    c2sum : 13901.1289 c2n :     5.0000 c2per:  2780.2258 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BR BT SA                                                                                     ' ' 0' '  3707      0' '3707.0000' '     0     -1']
     [' 1' 'TO BR SA                                                                                        ' ' 1' '     0   3675' '3675.0000' '    -1      0']
     [' 2' 'TO BT BT BT SA                                                                                  ' ' 2' '  3260      0' '3260.0000' '     4     -1']
     [' 3' 'TO BT BT SA                                                                                     ' ' 3' '     0   3259' '3259.0000' '    -1      3']
     [' 4' 'TO SA                                                                                           ' ' 4' '  3020   3048' ' 0.1292' '     1      2']
     [' 5' 'TO BT AB                                                                                        ' ' 5' '     0     10' ' 0.0000' '    -1    165']
     [' 6' 'TO BT BT AB                                                                                     ' ' 6' '     8      1' ' 0.0000' '  1933   9504']
     [' 7' 'TO BT BR SD                                                                                     ' ' 7' '     0      4' ' 0.0000' '    -1   1085']
     [' 8' 'TO BT BT BR BT BT BT SA                                                                         ' ' 8' '     3      0' ' 0.0000' '  5253     -1']




N=0 Maybe step specs shifted::

    In [2]: np.c_[st[0,:5]] 
    Out[2]: 
    array([['UNSET'],
           ['UNSET'],
           ['Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['UNSET']], dtype='<U47')



    UName::add idx    1 name Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys count 27229 size    11
    UName::add idx    2 name Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv count 27230 size    11
    UName::add idx    3 name Pyrex/Water:nnvt_log_pv/Water_lv_pv count 27231 size    11
    UName::add idx    4 name Water/Rock:Water_lv_pv/Rock_lv_pv count 27232 size    11

    U4Recorder::UserSteppingAction_Optical@613:  l.id   4 step_mm    79.0000 abbrev BT spec    Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys st   1 is_fake NO  FAKES_SKIP YES
    U4Recorder::UserSteppingAction_Optical@613:  l.id   4 step_mm     0.0010 abbrev BT spec             Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv st   2 is_fake NO  FAKES_SKIP YES
    U4Recorder::UserSteppingAction_Optical@613:  l.id   4 step_mm     5.0000 abbrev BT spec                Pyrex/Water:nnvt_log_pv/Water_lv_pv st   3 is_fake NO  FAKES_SKIP YES
    U4Recorder::UserSteppingAction_Optical@613:  l.id   4 step_mm    15.9990 abbrev SA spec                  Water/Rock:Water_lv_pv/Rock_lv_pv st   4 is_fake NO  FAKES_SKIP YES

    U4Recorder::PostUserTrackingAction_Optical@364:  l.id     4 seq TO BT BT BT SA

    In [2]: np.c_[SPECS]                                                                                                                                                           
    Out[2]: 
    array([['UNSET'],
           ['Water/Pyrex:Water_lv_pv/AroundCircle1'],
           ['Pyrex/Pyrex:AroundCircle1/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys'],
           ['Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys'],
           ['Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_tube_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_edge_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_plate_phy'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy'],
           ['Water/Rock:Water_lv_pv/Rock_lv_pv']], dtype='<U47')



    UName::desc count 27232 size    11
        0 : UNSET
        1 : Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys
        2 : Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv
        3 : Pyrex/Water:nnvt_log_pv/Water_lv_pv
        4 : Water/Rock:Water_lv_pv/Rock_lv_pv
        5 : Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys
        6 : Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy
        7 : Pyrex/Pyrex:nnvt_log_pv/nnvt_log_pv
        8 : Water/Pyrex:Water_lv_pv/nnvt_log_pv
        9 : Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys
       10 : Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys


    In [1]: np.c_[SPECS]                                                                                                                                                           
    Out[1]: 
    array([['UNSET'],
           ['Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys'],
           ['Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv'],
           ['Pyrex/Water:nnvt_log_pv/Water_lv_pv'],
           ['Water/Rock:Water_lv_pv/Rock_lv_pv'],
           ['Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys'],
           ['Vacuum/Steel:nnvt_inner2_phys/nnvt_mcp_phy'],
           ['Pyrex/Pyrex:nnvt_log_pv/nnvt_log_pv'],
           ['Water/Pyrex:Water_lv_pv/nnvt_log_pv'],
           ['Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys'],
           ['Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys']], dtype='<U47')

    In [3]: np.c_[st[4,:5]]                                                                                                                                                        
    Out[3]: 
    array([['UNSET'],
           ['Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys'],
           ['Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv'],
           ['Pyrex/Water:nnvt_log_pv/Water_lv_pv'],
           ['Water/Rock:Water_lv_pv/Rock_lv_pv']], dtype='<U47')

    In [2]: t.record[4,:5,0]                                                                                                                                                       
    Out[2]: 
    array([[  0.   ,   0.   , 100.   ,   0.   ],
           [  0.   ,   0.   , 179.   ,   0.264],
           [  0.   ,   0.   , 179.001,   0.264],
           [  0.   ,   0.   , 184.001,   0.28 ],
           [  0.   ,   0.   , 200.   ,   0.354]], dtype=float32)



After add needed fake detection : chi2 sinks to almost zero : this is with very simple one_pmt setup single point shooting
----------------------------------------------------------------------------------------------------------------------------

::

    np.c_[aqn,aqi,aqu][aquo][lim]  ## aexpr : unique histories aqu in descending count aqn order, aqi first index 
    [[b'3707' b'0' b'TO BR SA                                                                                        ']
     [b'3260' b'4' b'TO BT BT SA                                                                                     ']
     [b'3020' b'1' b'TO SA                                                                                           ']
     [b'8' b'1933' b'TO BT AB                                                                                        ']
     [b'3' b'5253' b'TO BT BR BT BT SA                                                                               ']
     [b'1' b'5599' b'TO BT BR BT SD                                                                                  ']
     [b'1' b'4511' b'TO BT BR BT SA                                                                                  ']]

    np.c_[bqn,bqi,bqu][bquo][lim]  ## bexpr : unique histories bqu in descending count bqn order, bqi first index 
    [[b'3675' b'0' b'TO BR SA                                                                                        ']
     [b'3259' b'3' b'TO BT BT SA                                                                                     ']
     [b'3048' b'2' b'TO SA                                                                                           ']
     [b'10' b'165' b'TO BT AB                                                                                        ']
     [b'4' b'1085' b'TO BT BR SD                                                                                     ']
     [b'2' b'5535' b'TO BT BR SA                                                                                     ']
     [b'1' b'9504' b'TO BT BT AB                                                                                     ']
     [b'1' b'1802' b'TO BT BR BR BT SA                                                                               ']]
    c2sum :     0.2681 c2n :     3.0000 c2per:     0.0894 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BR SA                                                                                        ' ' 0' '  3707   3675' ' 0.1387' '     0      0']
     [' 1' 'TO BT BT SA                                                                                     ' ' 1' '  3260   3259' ' 0.0002' '     4      3']
     [' 2' 'TO SA                                                                                           ' ' 2' '  3020   3048' ' 0.1292' '     1      2']
     [' 3' 'TO BT AB                                                                                        ' ' 3' '     8     10' ' 0.0000' '  1933    165']
     [' 4' 'TO BT BR SD                                                                                     ' ' 4' '     0      4' ' 0.0000' '    -1   1085']
     [' 5' 'TO BT BR BT BT SA                                                                               ' ' 5' '     3      0' ' 0.0000' '  5253     -1']
     [' 6' 'TO BT BR SA                                                                                     ' ' 6' '     0      2' ' 0.0000' '    -1   5535']
     [' 7' 'TO BT BT AB                                                                                     ' ' 7' '     0      1' ' 0.0000' '    -1   9504']
     [' 8' 'TO BT BR BT SD                                                                                  ' ' 8' '     1      0' ' 0.0000' '  5599     -1']
     [' 9' 'TO BT BR BT SA                                                                                  ' ' 9' '     1      0' ' 0.0000' '  4511     -1']
     ['10' 'TO BT BR BR BT SA                                                                               ' '10' '     0      1' ' 0.0000' '    -1   1802']]





Now generalize to a line of photons raining down onto one_pmt
-----------------------------------------------------------------

Huge chi2 as lacking fake skips::

    c2sum : 15468.5195 c2n :    28.0000 c2per:   552.4471 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                                                                                        ' ' 0' '     0   3543' '3543.0000' '    -1    476']
     [' 1' 'TO BT BT SD                                                                                     ' ' 1' '  3473      0' '3473.0000' '   475     -1']
     [' 2' 'TO BT BT SA                                                                                     ' ' 2' '  3036    402' '2018.0210' '   477   1411']
     [' 3' 'TO BT SA                                                                                        ' ' 3' '     0   2953' '2953.0000' '    -1    479']
     [' 4' 'TO SA                                                                                           ' ' 4' '   915    921' ' 0.0196' '     0      0']
     [' 5' 'TO BT BT BT SR SA                                                                               ' ' 5' '   471      0' '471.0000' '  1534     -1']
     [' 6' 'TO BT BT SR SA                                                                                  ' ' 6' '     0    431' '431.0000' '    -1   1494']
     [' 7' 'TO BT BT SR BT BT SA                                                                            ' ' 7' '     0    410' '410.0000' '    -1   2347']
     [' 8' 'TO BT BT BT SA                                                                                  ' ' 8' '   370      0' '370.0000' '  1358     -1']
     [' 9' 'TO BT BR BT SA                                                                                  ' ' 9' '     0    336' '336.0000' '    -1    478']
     ['10' 'TO BT BT BT SR BT BT SA                                                                         ' '10' '   318      0' '318.0000' '  2347     -1']
     ['11' 'TO BT BT BR BT SA                                                                               ' '11' '   243      0' '243.0000' '   503     -1']
     ['12' 'TO BT BT SR BR SR SA                                                                            ' '12' '     0    131' '131.0000' '    -1   2420']
     ['13' 'TO BT BT BT SR BR SA                                                                            ' '13' '   125      0' '125.0000' '  2371     -1']
     ['14' 'TO BT BT BT SR BR SR SA                                                                         ' '14' '   107      0' '107.0000' '  2498     -1']
     ['15' 'TO BR SA                                                                                        ' '15' '   102    101' ' 0.0049' '   465    467']


Try to find what needs to be skipped::

    In [10]: aq[475],a_st[475,:4],a.record[475,:4,0] 
    Out[10]: 
    (array([b'TO BT BT SD                                                                                     '], dtype='|S96'),
     array(['UNSET', 'Water/Pyrex:Water_lv_pv/nnvt_log_pv', 'Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys', 'Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys'], dtype='<U47'),
     array([[253.4  ,   0.   , 190.   ,   0.   ],
            [253.4  ,   0.   ,  12.65 ,   0.813],
            [249.001,   0.   ,   0.101,   0.881],   ## OBVIOUSLY Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys
            [249.   ,   0.   ,   0.098,   0.881]], dtype=float32))

    POM=1 N=0 APID=475 AOPT=idx LOC=skip ./U4SimtraceTest.sh ana   # labelling the points helps to find the fake to skip

    ## HMM: FEAR THAT WAHT NEED TO SKIP IN ONE CASE MIGHT NOT BE THE CORRECT THING TO SKIP IN ANOTHER CASE


    In [9]: bq[476],b_st[476,:3],b.record[476,:3,0]
    Out[9]: 
    (array([b'TO BT SD                                                                                        '], dtype='|S96'),
     array(['UNSET', 'Water/Pyrex:Water_lv_pv/nnvt_log_pv', 'Pyrex/Vacuum:nnvt_log_pv/nnvt_inner_phys'], dtype='<U43'),
     array([[253.344,   0.   , 190.   ,   0.   ],
            [253.344,   0.   ,  13.226,   0.811],
            [248.998,   0.   ,   0.692,   0.878]], dtype=float32))

    POM=1 N=1 BPID=476 LOC=skip ./U4SimtraceTest.sh ana

    
Automate above dumping::

    epsilon:tests blyth$ POM=1 N=0 APID=475 BPID=476 ./U4SimulateTest.sh cf

    APID:475
    aq[APID]
    array([b'TO BT SD                                                                                        '], dtype='|S96')
    .
    a_st[APID,:an[APID]]
    array(['UNSET', 'Water/Pyrex:Water_lv_pv/nnvt_log_pv', 'Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys'], dtype='<U47')
    .
    a.record[APID,:an[APID],0]
    array([[253.4  ,   0.   , 190.   ,   0.   ],
           [253.4  ,   0.   ,  12.65 ,   0.813],
           [249.   ,   0.   ,   0.098,   0.881]], dtype=float32)
    .
    BPID:476
    bq[BPID]
    array([b'TO BT SD                                                                                        '], dtype='|S96')
    .
    b_st[APID,:bn[BPID]]
    array(['UNSET', 'Water/Pyrex:Water_lv_pv/nnvt_log_pv', 'Water/Rock:Water_lv_pv/Rock_lv_pv'], dtype='<U43')
    .
    b.record[BPID,:bn[BPID],0]
    array([[253.344,   0.   , 190.   ,   0.   ],
           [253.344,   0.   ,  13.226,   0.811],
           [248.998,   0.   ,   0.692,   0.878]], dtype=float32)
    .



::


    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                                                                                        ' ' 0' '  3473   3543' ' 0.6984' '   475    476']
     [' 1' 'TO BT SA                                                                                        ' ' 1' '  3036   2953' ' 1.1503' '   477    479']
     [' 2' 'TO SA                                                                                           ' ' 2' '   915    921' ' 0.0196' '     0      0']
     [' 3' 'TO BT BT SR SA                                                                                  ' ' 3' '   471    431' ' 1.7738' '  1534   1494']

     [' 4' 'TO BT BT SR BT BT SA                                                                            ' ' 4' '   318    410' '11.6264' '  2347   2347']

     POM=1 N=0 APID=2347 AOPT=idx LOC=skip ./U4SimtraceTest.sh ana
     POM=1 N=1 BPID=2347 BOPT=idx LOC=skip ./U4SimtraceTest.sh ana

     HMM: LOOKING THE SAME : EASIER TO DEBUG ZEROS RATHER THAN LEVEL DIFFS LIKE THIS


     [' 5' 'TO BT BT SA                                                                                     ' ' 5' '   370    402' ' 1.3264' '  1358   1411']

     [' 6' 'TO BT BR BT SA                                                                                  ' ' 6' '   243    336' '14.9378' '   503    478']

     [' 7' 'TO BT BT SR BR SR SA                                                                            ' ' 7' '   107    131' ' 2.4202' '  2498   2420']
     [' 8' 'TO BT BT SR BR SA                                                                               ' ' 8' '   125    100' ' 2.7778' '  2371   2350']
     [' 9' 'TO BR SA                                                                                        ' ' 9' '   102    101' ' 0.0049' '   465    467']
     ['10' 'TO BT BT SR SR SA                                                                               ' '10' '    73     63' ' 0.7353' '  1522   1468']
     ['11' 'TO BT BT SR BR SR BT BT SA                                                                      ' '11' '    43     58' ' 2.2277' '  2462   2447']
     ['12' 'TO BT AB                                                                                        ' '12' '    41     35' ' 0.4737' '   506    482']

     ['13' 'TO BT BT SR BT BT BT SA                                                                         ' '13' '    36      0' '36.0000' '  2374     -1']
     ['15' 'TO BT BT SR BT SA                                                                               ' '15' '    35      0' '35.0000' '  2958     -1']
     ['21' 'TO BT BR SA                                                                                     ' '21' '    24      0' ' 0.0000' '   495     -1']


     POM=1 N=0 APID=2374 AOPT=idx LOC=skip ./U4SimtraceTest.sh ana
     POINTS 5,6 ON TOP OF EACH OTHER



     ['14' 'TO BT BT SR BR SR SR SA                                                                         ' '14' '    35     31' ' 0.2424' '  2761   2574']
     ['16' 'TO BT BT SR BR SR BR SR BT BT SA                                                                ' '16' '    14     33' ' 7.6809' '  3079   3075']
     ['17' 'TO BT BT SR SR BT BT SA                                                                         ' '17' '    22     32' ' 1.8519' '  2068   2075']
     ['18' 'TO BT BT SR BR SR SR BT BT SA                                                                   ' '18' '    25     28' ' 0.1698' '  2713   2576']
     ['19' 'TO BT BT SR SR SR BT BT SA                                                                      ' '19' '     7     25' '10.1250' '  1779   1635']
     ['20' 'TO BT BT SR SR SR SA                                                                            ' '20' '    22     24' ' 0.0870' '  1465   1566']






Hmm : need to better way to identify fakes : for very close volumes cannot rely on the volume that G4 says
--------------------------------------------------------------------------------------------------------------

1. traverse up or down geometry tree from step point volume 
   to find the known fake "body_phys" volume

2. calculate the distance to that when its below some cutoff declare the point to be fake
   * note that cannot rely on the G4 volume 


* WIP : U4Recorder::CheckFake


::

    N=0 PIDX=2374 ./U4SimulateTest.sh 

    N=0 APID=2374 AOPT=idx ./U4SimtraceTest.sh ana

    In [2]: aq[2374:2384]
    Out[2]: 
    array([[b'TO BT BT SR BT BT BT SA              Extra BT                                                   '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT BT SR BR BT BT SA                                                                         '],
           [b'TO BT BT SR BR BR SR SR SA                                                                      '],
           [b'TO BT BT SR SA                                                                                  '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SD                                                                                        ']], dtype='|S96')

    In [3]: bq[2374:2384]
    Out[3]: 
    array([[b'TO BT SD                            2374                                                        '],
           [b'TO BT BT SR BR BR SA                2375                                                        '],
           [b'TO BT SA                            2376                                                        '],
           [b'TO BT SA                            2377                                                        '],
           [b'TO BT BT SR BT BT SA                2378                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT BT SR BT BT SA                                                                            '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        ']], dtype='|S96')

    N=1 BPID=2378 BOPT=idx ./U4SimtraceTest.sh ana



    epsilon:tests blyth$ N=0 PIDX=2374 ./U4SimulateTest.sh 


     pos (   147.056      0.000    150.027) dir (    -0.045      0.000     -0.999) in kOutside t      5.454 ipos (   146.813      0.000    144.577)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm    39.9735 abbrev BT spec                Water/Pyrex:Water_lv_pv/nnvt_log_pv st   3 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (   146.813      0.000    144.577) dir (    -0.045      0.000     -0.999) in kSurface t    295.925 ipos (   133.604      0.000   -151.052)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     5.4545 abbrev BT spec             Pyrex/Pyrex:nnvt_log_pv/nnvt_body_phys st  -4 is_fake YES check_fake NO  FAKES_SKIP YES

     pos (   146.812      0.000    144.576) dir (     0.197      0.000     -0.980) in kInside t    258.371 ipos (   197.823      0.000   -108.709)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     0.0011 abbrev BT spec          Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys st   9 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (   175.929      0.000      0.000) dir (     0.197      0.000     -0.980) in kInside t    110.892 ipos (   197.823      0.000   -108.709)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm   147.4792 abbrev BT spec    Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys st -11 is_fake YES check_fake NO  FAKES_SKIP YES

     pos (   197.822      0.000   -108.708) dir (    -0.966      0.000      0.257) in kInside t    461.968 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm   110.8905 abbrev SR spec       Vacuum/Pyrex:nnvt_inner2_phys/nnvt_body_phys st   6 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (   197.822      0.000   -108.708) dir (    -0.966      0.000      0.257) in kInside t    461.968 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     0.0000 abbrev NA spec       Pyrex/Vacuum:nnvt_body_phys/nnvt_inner2_phys st   5 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (  -210.614      0.000      0.000) dir (    -0.966      0.000      0.257) in kInside t     39.312 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm   422.6555 abbrev BT spec    Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys st -14 is_fake YES check_fake NO  FAKES_SKIP YES

     pos (  -248.602      0.000     10.111) dir (    -0.980      0.000      0.199) in kInside t      0.001 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm    39.3110 abbrev BT spec    Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner1_phys st  15 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (  -248.602      0.000     10.111) dir (    -0.987      0.000      0.160) in kInside t      0.001 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     0.0000 abbrev BT spec          Pyrex/Pyrex:nnvt_body_phys/nnvt_body_phys st   9 is_fake NO  check_fake NO  FAKES_SKIP YES

     pos (  -248.603      0.000     10.111) dir (    -0.987      0.000      0.160) in kSurface t      0.000 ipos (  -248.603      0.000     10.111)
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     0.0010 abbrev BT spec             Pyrex/Pyrex:nnvt_body_phys/nnvt_log_pv st  -7 is_fake YES check_fake YES FAKES_SKIP YES

    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm     5.0150 abbrev BT spec                Pyrex/Water:nnvt_log_pv/Water_lv_pv st   8 is_fake NO  check_fake NO  FAKES_SKIP YES
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2374 step_mm   103.4618 abbrev SA spec                  Water/Rock:Water_lv_pv/Rock_lv_pv st   2 is_fake NO  check_fake NO  FAKES_SKIP YES

    U4Recorder::PostUserTrackingAction_Optical@366:  l.id  2374 seq TO BT BT SR BT BT BT SA


    In [3]: a.record[2374,:8,0]                                                                                                                                                    
    Out[3]: 
    array([[ 147.056,    0.   ,  190.   ,    0.   ],
           [ 147.056,    0.   ,  150.027,    0.183],
           [ 146.812,    0.   ,  144.576,    0.211],
           [ 197.822,    0.   , -108.708,    1.528],
           [-248.602,    0.   ,   10.111,    3.813],
           [-248.602,    0.   ,   10.111,    3.813],
           [-253.554,    0.   ,   10.913,    3.839],
           [-355.556,    0.   ,   28.233,    4.313]], dtype=float32)


    epsilon:tests blyth$ N=1 PIDX=2378 ./U4SimulateTest.sh 

    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm    39.8584 abbrev BT spec                Water/Pyrex:Water_lv_pv/nnvt_log_pv st   3 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm     5.4536 abbrev BT spec           Pyrex/Vacuum:nnvt_log_pv/nnvt_inner_phys st   4 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm   258.7347 abbrev SR spec           Vacuum/Pyrex:nnvt_inner_phys/nnvt_log_pv st   5 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm     0.0000 abbrev NA spec           Pyrex/Vacuum:nnvt_log_pv/nnvt_inner_phys st   4 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm   461.9809 abbrev BT spec           Vacuum/Pyrex:nnvt_inner_phys/nnvt_log_pv st   5 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm     5.0329 abbrev BT spec                Pyrex/Water:nnvt_log_pv/Water_lv_pv st   6 is_fake NO  check_fake NO  FAKES_SKIP NO 
    U4Recorder::UserSteppingAction_Optical@611:  l.id 2378 step_mm   104.5801 abbrev SA spec                  Water/Rock:Water_lv_pv/Rock_lv_pv st   2 is_fake NO  check_fake NO  FAKES_SKIP NO 

    U4Recorder::PostUserTrackingAction_Optical@366:  l.id  2378 seq TO BT BT SR BT BT SA

    In [7]: b.record[2378,:7,0]                                                                                                                                                    
    Out[7]: 
    array([[ 146.832,    0.   ,  190.   ,    0.   ],
           [ 146.832,    0.   ,  150.142,    0.183],
           [ 146.589,    0.   ,  144.693,    0.211],
           [ 197.537,    0.   , -108.975,    1.074],
           [-248.499,    0.   ,   11.349,    2.615],
           [-253.426,    0.   ,   12.378,    2.64 ],
           [-355.556,    0.   ,   34.883,    3.12 ]], dtype=float32)






Are not skipping some "pile up" fakes
------------------------------------------------

::

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30][bzero]  ## A-B comparison of unique history counts 
    [['14' 'TO BT BT SR BT SA                                                                               ' '14' '    35      0' '35.0000' '  2958     -1']
     ['20' 'TO BT BR SA                                                                                     ' '20' '    24      0' ' 0.0000' '   495     -1']
     ['25' 'TO BT BT SR BT BR SA                                                                            ' '25' '    13      0' ' 0.0000' '  2590     -1']
     ['26' 'TO BT BT SR BT BR SR SA                                                                         ' '26' '    12      0' ' 0.0000' '  2556     -1']]
 
    b'TO BT BT SR BT SA          ## BT and SA on top of each other                                                                              '
    u4t ; N=0 APID=2958 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3003 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3239 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3250 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3332 AOPT=idx ./U4SimtraceTest.sh ana
 
    b'TO BT BR SA                  ## BR and SA on top of each other                                                                                   '
    u4t ; N=0 APID=495 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=859 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=1153 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=1343 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=1627 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=2567 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=2740 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3441 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3442 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4518 AOPT=idx ./U4SimtraceTest.sh ana

    b'TO BT BT SR BT BR SA         ## BT and BR on top of each other                                                                         '
    u4t ; N=0 APID=2590 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3029 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4202 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4435 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4597 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4724 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5423 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5465 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=6120 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=6183 AOPT=idx ./U4SimtraceTest.sh ana

    b'TO BT BT SR BT BR SR SA      ## BT and BR on top of each other                                                                   '
    u4t ; N=0 APID=2556 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=3528 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=4381 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5823 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5853 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5860 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=5973 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=6039 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=6232 AOPT=idx ./U4SimtraceTest.sh ana
    u4t ; N=0 APID=6267 AOPT=idx ./U4SimtraceTest.sh ana



::

    ./mt.sh 

    In [1]: q[495]
    Out[1]: array([b'TO BT BR SA                                                                                     '], dtype='|S96')

    In [3]: t.record[495,:4,0]
    Out[3]: 
    array([[252.28 ,   0.   , 190.   ,   0.   ],
           [252.28 ,   0.   ,  21.383,   0.773],
           [248.667,   0.   ,   9.258,   0.838],
           [248.667,   0.   ,   9.258,   0.838]], dtype=float32)




Improve ModelTriggerSimple to avoid double trigger very close to each other
----------------------------------------------------------------------------

Below improved impl requiring dist1 > EPSILON gets chi2 N=0/1 histories to match in one_pmt line tests.::

    c2sum :    20.6285 c2n :    21.0000 c2per:     0.9823  C2CUT:   30 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30][:30]  ## A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                                                                                        ' ' 0' '  3493   3543' ' 0.3553' '   489    476']
     [' 1' 'TO BT SA                                                                                        ' ' 1' '  3023   2953' ' 0.8199' '   476    479']
     [' 2' 'TO SA                                                                                           ' ' 2' '   917    921' ' 0.0087' '     0      0']
     [' 3' 'TO BT BT SR SA                                                                                  ' ' 3' '   440    431' ' 0.0930' '  1482   1494']
     [' 4' 'TO BT BT SR BT BT SA                                                                            ' ' 4' '   433    410' ' 0.6275' '  2355   2347']
     [' 5' 'TO BT BT SA                                                                                     ' ' 5' '   405    402' ' 0.0112' '  1300   1411']
     [' 6' 'TO BT BR BT SA                                                                                  ' ' 6' '   309    336' ' 1.1302' '   483    478']
     [' 7' 'TO BT BT SR BR SR SA                                                                            ' ' 7' '    96    131' ' 5.3965' '  2515   2420']
     [' 8' 'TO BR SA                                                                                        ' ' 8' '   107    101' ' 0.1731' '   466    467']
     [' 9' 'TO BT BT SR BR SA                                                                               ' ' 9' '    94    100' ' 0.1856' '  2376   2350']
     ['10' 'TO BT BT SR SR SA                                                                               ' '10' '    89     63' ' 4.4474' '  1468   1468']
     ['11' 'TO BT BT SR BR SR BT BT SA                                                                      ' '11' '    50     58' ' 0.5926' '  2461   2447']
     ['12' 'TO BT AB                                                                                        ' '12' '    28     35' ' 0.7778' '   821    482']
     ['13' 'TO BT BT SR BR SR SR SA                                                                         ' '13' '    34     31' ' 0.1385' '  2564   2574']
     ['14' 'TO BT BT SR BR SR BR SR BT BT SA                                                                ' '14' '    19     33' ' 3.7692' '  2548   3075']
     ['15' 'TO BT BT SR SR BT BT SA                                                                         ' '15' '    32     32' ' 0.0000' '  2077   2075']
     ['16' 'TO BT BT SR BR SR SR BT BT SA                                                                   ' '16' '    22     28' ' 0.7200' '  2700   2576']


::

    267 /**
    268 junoPMTOpticalModel::ModelTriggerSimple_
    269 ------------------------------------------
    270 
    271 This is a "pre-trigger" returning true when approaching 
    272 the upper hemisphere of inner1 from inside or outside.
    273 
    274 The implementation is based on the distance *dist1*
    275 in the current momentum direction of the photon to the inner1 solid. 
    276 
    277 *dist1* is required to be greater than EPSILON
    278 where EPSILON is 2e-4 which is one fifth of the 
    279 distance between body and inner1 1e-3.
    280 
    281 Also the local z of next_pos which is *dist1* ahead
    282 is required to exceed EPSILON in order to exclude
    283 situations where next position is on the Vacuum/Vacuum midline. 
    284 
    285 This the positions where this returns true 
    286 are expected to be very close to the fake "body" volume 
    287 when coming from outside or close to fake Vacumm/Vacuum 
    288 border when approaching from inside. 
    289 
    290 Note that the implemetation avoids relying on the volume that 
    291 Geant4 thinks are currently at because that is unreliable.
    292 Also as the PMT has various volumes for dynodes and MCT 
    293 within inner2 a current volume based implementation would 
    294 be complicated.   
    295 
    296 ::
    297 
    298      +---Pyrex--pmt-------------------+
    299      |                                |
    300      |   +--Pyrex-body - - - - - +    |
    301      |   : +~~Vacuum~~inner1~~~+ :    |
    302      |   : !                   ! :    |
    303      |   : !                   !1e-3  |
    304      |   : !                   ! :    |
    305      |   + +- - - - - - - - ---+ +    |
    306      |   : |                   | :    |
    307      |   : |                   | :    |
    308      |   : |                   | :    |
    309      |   : +--Vacuum--inner2---+ :    |
    310      |   +- - - - - - - - - - - -+    |
    311      |                                |
    312      +--------------------------------+
    313 
    314 **/
    315 
    316 G4bool junoPMTOpticalModel::ModelTriggerSimple_(const G4FastTrack& )
    317 {
    318     bool trig = false ;
    319     dist1 = Distance( _inner1_solid, pos, dir, in1 );
    320     if( dist1 != kInfinity && dist1 > EPSILON )
    321     {
    322         next_pos = pos + dir*dist1 ;
    323         trig = next_pos.z() > EPSILON ;  // disqualify flat face intersects 
    324 
    325         next_norm = _inner1_solid->SurfaceNormal(next_pos);
    326         next_mct  = next_norm * dir ;
    327         whereAmI  = next_mct < 0. ? kInGlass : kInVacuum ; // against normal is outside
    328     }
    329 
    330 #ifdef PMTSIM_STANDALONE
    331     bool PIDX_DUMP = m_label->id == PIDX && PIDX_ENABLED ;
    332     LOG_IF(info, PIDX_DUMP) << " PIDX " << PIDX << " label.id " << m_label->id << " dist1 " << dist1 << " trig " << trig << " whereAmI " << whereAmI ;
    333 #endif
    334     return trig ;
    335 }
    336 
    337 const G4double junoPMTOpticalModel::EPSILON = 2e-4 ;



Check ModelTrigger positions : is there a whereAmI bug ? SEEMS NOT
----------------------------------------------------------------------

Better to check by comparing EInside vs sign of normal*dir 

::

    079     mtd_py = np.logical_and(mtd.trig == 1, mtd.whereAmI_ == 1 )
     80     mtd_va = np.logical_and(mtd.trig == 1, mtd.whereAmI_ == 2 )
    ...
     97     ppos0 = mtd.pos[mtd_py]
     98     ppos1 = mtd.pos[mtd_va]
     99     label = "b:mtd.pos[mtd_py] r:mtd.pos[mtd_va]"
    100     


mtd.pos[mtd_pyrex] 
   all around the upper hemi as expected.

mtd.pos[mtd_vacuum] 
   most along the Vac/Vac midline but there is significant number around the upper hemi. 

   * is that a whereAmI bug ?
   * NO, cannot easily check like this because you can be inside the vacuum and also close to the hemi. 
     eg consider very "oblique" photon paths just inside the hemi


::

    58 enum EInside {kOutside,kSurface,kInside};

::

    In [5]: np.unique( mtd.EInside1, return_counts=True  )
    Out[5]: (array([0, 1], dtype=uint64), array([15387,  8808]))

    In [6]: np.unique( mtd.whereAmI_, return_counts=True  )
    Out[6]: (array([0, 1, 2], dtype=uint64), array([   17, 14486,  9692]))



Config to ModelTriggerBuggy and look for problems to show
-------------------------------------------------------------

::

     epsilon:tests blyth$ APID=2181 AOPT=idx N=0 ./U4SimtraceTest.sh ana


     80     mtd_trig = mtd.trig == 1
     81     mtd_trig_pyrex  = np.logical_and(mtd.trig == 1, mtd.whereAmI_ == 1 )
     82     mtd_trig_vacuum = np.logical_and(mtd.trig == 1, mtd.whereAmI_ == 2 )
     83     mtd_outside = np.logical_and(mtd.trig == 1, mtd.EInside1 == 0 )
     84 
     85     mtd_upper = mtd.pos[:,2] > 1e-4
     86     mtd_lower = mtd.pos[:,2] < -1e-4
     87     mtd_trig_vacuum_upper = np.logical_and(mtd_trig_vacuum, mtd_upper )
     88     mtd_trig_pyrex_lower = np.logical_and(mtd_trig_pyrex, mtd_lower )
     89 
     90     idxs = np.unique(mtd.index[mtd_trig_pyrex_lower])   # photon indices 
     91 

Select photon indices of ModelTriggerDummy triggers with whereAmI classified as "Pyrex" 
that are in lower hemi due to reflections of dynode or MCP. That provides a rich vein of bugs::

    In [4]: np.c_[idxs,q[idxs]]
    Out[4]: 
    array([[b'1628', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1635', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1639', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1646', b'TO BT BT SR SR SR SD                                                                            '],
           [b'2181', b'TO BT BT SR SR BR SR SR SR BR SR SR BT BT SA              BR off the midline                    '],
           [b'2563', b'TO BT BT SR BR SR SR SD                                   SD on the midline                     '],
           [b'2572', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'2575', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'2682', b'TO BT BT SR BR SR SD                                                                            '],
           [b'2696', b'TO BT BT SR BR SR SA                                                                            '],
           [b'2864', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'2912', b'TO BT BT SR BR SR SR BT BR SR SR SD                                                             '],
           [b'2923', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'2926', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'2942', b'TO BT BT SR BR SR SR BR SR BR SR BT BT SA        reflect off midline, cross geometry            '],
           [b'2982', b'TO BT BT SR BR SR SR BT BT BT SA                 refract across midline                         '],
           [b'2992', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'3017', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'3021', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'3027', b'TO BT BT SR BR SR SR BT SA                                                                      '],
           [b'3187', b'TO BT BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR SR SA                                     '],
           [b'3270', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'3323', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'3330', b'TO BT BT SR BR SR SR SD                                                                         '],


::


    APID=2181 AOPT=idx N=0 SUBTITLE="9:reflect at vac/vac (but obscured)" ./U4SimtraceTest.sh ana

    APID=2563 AOPT=idx N=0 SUBTITLE="7:SD at vac/vac" ./U4SimtraceTest.sh ana

    APID=2912 AOPT=idx N=0 SUBTITLE="7:vac/vac refract 11:SD detect in vac" ./U4SimtraceTest.sh ana

    APID=2942 AOPT=idx N=0 SUBTITLE="6->7:cross-geometry 7:vac/vac-reflect" ./U4SimtraceTest.sh ana

    APID=2982 AOPT=idx N=0 SUBTITLE="7:unphysical refract" ./U4SimtraceTest.sh ana

    APID=5866 AOPT=idx N=0 SUBTITLE="7:reflect at vac/vac" ./U4SimtraceTest.sh ana

    APID=7625 AOPT=idx N=0 SUBTITLE="13:detect mid vacuum" ./U4SimtraceTest.sh ana

    APID=8499 AOPT=idx N=0 SUBTITLE="13:detect mid vacuum" ./U4SimtraceTest.sh ana 



Select photons ending on the midline::

    In [3]: np.c_[w_midline,q[w_midline]]
    Out[3]: 
    array([[b'1628', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1635', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1639', b'TO BT BT SR SR SR SA                                                                            '],
           [b'1646', b'TO BT BT SR SR SR SD                                                                            '],
           [b'2563', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'2572', b'TO BT BT SR BR SR SR SD                                                                         '],
           [b'2575', b'TO BT BT SR BR SR SR SA                                                                         '],
           [b'2682', b'TO BT BT SR BR SR SD                                                                            '],
           ...
           [b'7625', b'TO BT BT SR BR BR SR SR BR BR BR SR SR SD                                                       '],
           [b'7637', b'TO BT BT SR BR BR SR SR SA                                                                      '],
           [b'8348', b'TO BT BT SR SR SR SA                                                                            '],
           [b'8351', b'TO BT BT SR SR SR SD                                                                            '],
           [b'8366', b'TO BT BT SR SR SR SA                                                                            '],
           [b'8371', b'TO BT BT SR SR SR SD                                                                            '],
           [b'8372', b'TO BT BT SR SR SR SD                                                                            '],
           [b'8499', b'TO BT BT SR SR SR SR SR BR BR SR SR SR SD                                                       ']], dtype='|S96')

Penultimate flag all "SR" for specular reflection off the dynode/MCP.

::

    In [25]: end2 = t.record[w_midline, tuple(nn-1), 0, :3]  

    In [31]: penultimate =  t.record[w_midline, tuple(nn-2), 0, :3]

    In [32]: penultimate                                          
    Out[32]: 
    array([[  42.9  ,    0.   , -133.607],
           [  42.9  ,    0.   , -137.71 ],
           [  42.9  ,    0.   , -139.974],
           [  42.9  ,    0.   , -143.803],
           [  20.588,    0.   , -116.   ],
           [  32.33 ,    0.   , -116.   ],
           [  35.979,    0.   , -116.   ],
           [ -21.828,    0.   , -116.   ],
           [ -27.978,    0.   , -116.   ],



