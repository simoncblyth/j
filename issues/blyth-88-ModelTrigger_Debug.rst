blyth-88-ModelTrigger_Debug
=============================

* :doc:`blyth-88-quadrant-matching`


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



