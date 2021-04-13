PMTEfficiencyCheck_addHitRecord_assert
==========================================


Actions
----------

1. add envvar controls::

    PMTEfficiencyCheck_dump
    PMTEfficiencyCheck_assert_match

2. add string list name saving for more easily maintained analysis
3. add mismatch summary bitfield
4. relocate PMTEfficiencyCheck.py into j 
5. arrange to save the first million hit records when reached rarther than waiting for the end of event


jcv HamamatsuR12860PMTManager::


    239 void
    240 HamamatsuR12860PMTManager::helper_make_solid()
    241 {   
    242     pmt_solid = m_pmtsolid_maker->GetSolid(GetName() + "_pmt_solid", 1E-3*mm);
    243     double inner_delta =  -5*mm ;
    244     if(!m_enable_optical_model)
    245     {   
    246         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid");
    247     }
    248     else
    249     {   
    250         // For the new PMT optical model. In fact, no impact on PMT geometry, just for safety
    251         body_solid = m_pmtsolid_maker->GetSolid(GetName() + "_body_solid", inner_delta+1E-3*mm);
    252     }
    253     
    254     inner_solid= m_pmtsolid_maker->GetSolid(GetName()+"_inner_solid", inner_delta );
    255     
    256     G4double helper_sep_tube_r = m_pmt_r;
    257     G4double helper_sep_tube_h = m_z_equator;
    258     G4double helper_sep_tube_hh = helper_sep_tube_h/2;
    259     
    260     // TODO: check the UNIT?
    261     
    262     if(m_simplify_csg == false)
    263     {   
    264         G4VSolid * pInnerSep = new G4Tubs("Inner_Separator",
    265                 0.,
    266                 helper_sep_tube_r+1E-9*mm,
    267                 helper_sep_tube_hh+1E-9*mm,
    268                 0.,360.*degree);
    269         G4ThreeVector innerSepDispl(0.,0.,helper_sep_tube_hh-1E-9*mm);
    270         inner1_solid = new G4IntersectionSolid( GetName()
    271                 + "_inner1_solid", inner_solid, pInnerSep, NULL, innerSepDispl);
    272         inner2_solid = new G4SubtractionSolid( GetName()
    273                 + "_inner2_solid", inner_solid, pInnerSep, NULL, innerSepDispl);
    274     }
    275     else
    276     {   
    277         inner1_solid = m_pmtsolid_maker->GetSolid(GetName()+"_inner1_solid", inner_delta, 'H');
    278         inner2_solid = m_pmtsolid_maker->GetSolid(GetName()+"_inner2_solid", inner_delta, 'T');
    279     }



Ellipsoid hit landing debug 
------------------------------

* see ~/opticks/examples/UseGLMStandalone/sdEllipse.{sh,cc,py}



Analysis
----------

* ce and de efficiency mismatch issue is at a one in a million level, as shown by below "bitwise nonzero_smry"

::

    epsilon:j blyth$ ./PMTEfficiencyCheck.sh 
    ipython -i PMTEfficiencyCheck.py
     (1000000, 4, 4) : /tmp/blyth/opticks/PMTEfficiencyCheck/ASIS/0.npy 
     (1000000, 4, 4) : a.shape concatenated 
    Mismatch
    total:1000000
    bitfield unique_smry
    i  0   mismatch (dec)     0 (hex)     0 (bin)          0  mismatch_count 810095 
    i  1   mismatch (dec)     6 (hex)     6 (bin)        110  mismatch_count      1 
    i  2   mismatch (dec)    24 (hex)    18 (bin)      11000  mismatch_count 189904 
    bitwise nonzero_smry
     qe      0    0.000
     ce      1    0.000      ### 1 in a million with mismatched ce
     de      1    0.000      ### 1 in a million with mismatched de
     pc 189904    0.190
     sc 189904    0.190
    w_qe: [] 
    w_de: [997966] 
    w_ce: [997966] 


* the same hit has discrepant ce and de

::

    In [2]: idx = 997966

    In [5]: pmtId[idx]
    Out[5]: 5697

    In [6]: local_pos[idx]
    Out[6]: array([-87.96 , 110.195, 152.483])

    In [7]: local_theta[idx]
    Out[7]: 0.7462784984722678

    In [8]: local_theta
    Out[8]: array([0.636, 1.228, 0.939, ..., 0.849, 1.061, 0.701])

    In [9]: global_pos[idx]
    Out[9]: array([  5012.565, -17474.166,   6428.413])

    In [10]: volIdx[idx]
    Out[10]: 3

    In [11]: np.unique(volIdx, return_counts=True)
    Out[11]: (array([0, 1, 2, 3], dtype=uint32), array([271898, 695327,  32774,      1]))

These three volumes are hit by 999999 out of a million. The discrepant hits a fourth volume.::

     37 void PMTEfficiencyCheck::init()  
     38 {       
     39     m_volnames.push_back("HamamatsuR12860_PMT_20inch_body_phys");
     40     m_volnames.push_back("NNVTMCPPMT_PMT_20inch_body_phys");
     41     m_volnames.push_back("PMT_3inch_body_phys");
     42 }       

::

    ../src/PMTEfficiencyCheck.cc +270 SaveRecords  eventID 0 m_uvolname.size 4 all volnames hit : 
    NNVTMCPPMT_PMT_20inch_body_phys
    HamamatsuR12860_PMT_20inch_body_phys
    PMT_3inch_body_phys
    HamamatsuR12860_PMT_20inch_inner1_phys

* The 4th volume is : HamamatsuR12860_PMT_20inch_inner1_phys

::

    In [12]: global_radius
    Out[12]: array([19276.264, 19355.622, 19307.136, ..., 19293.278, 19325.048, 19281.373])

    In [13]: global_radius[idx]
    Out[13]: 19282.032460661314



    In [16]: qeff[idx],qeff2[idx],ceff[idx],ceff2[idx],deff[idx],deff2[idx]
    Out[16]:
    (0.4446674311926605,
     0.4446674311926605,
     1.0,                        ## looks like the unexpected volume leads to ceff defaulting to 1.0 ?
     0.9295678299010578,
     0.4446674311926605,
     0.41334853904143937)



    In [17]: ceCat[idx]
    Out[17]: 0

    In [18]: ceCat
    Out[18]: array([6, 5, 6, ..., 4, 6, 6], dtype=uint32)

    In [19]: np.unique(ceCat, return_counts=True)
    Out[19]: (array([0, 4, 5, 6], dtype=uint32), array([ 32775, 271898, 112177, 583150]))




WOW : surprised by the number of ceCat zeros. 3 percent of hits slip thru junoSD_PMT_v2::get_ce and end up with ce of 1.0::

    In [20]: ceff
    Out[20]: array([0.974, 0.924, 0.969, ..., 0.928, 0.976, 0.973])

    In [21]: ceff[ceCat == 0]
    Out[21]: array([1., 1., 1., ..., 1., 1., 1.])

    In [22]: np.all( ceff[ceCat == 0] == 1)
    Out[22]: True

Explained : They are all volIdx 2 PMT_3inch_body_phys, aprt from the 1-in-a-million::

    In [7]: np.where(volIdx == 2)
    Out[7]: (array([    45,    101,    146, ..., 999954, 999962, 999968]),)

    In [8]: volIdx[ceCat == 0]
    Out[8]: array([2, 2, 2, ..., 2, 2, 2], dtype=uint32)

    In [9]: np.unique(volIdx[ceCat == 0])
    Out[9]: array([2, 3], dtype=uint32)

    In [10]: np.unique(volIdx[ceCat == 0], return_counts=True)
    Out[10]: (array([2, 3], dtype=uint32), array([32774,     1]))




Anything special about 1-in-a-million photon ?
--------------------------------------------------

* nothing obvious, does not look to be at extremes : could have sneeked thru CSG constituent edge
* TODO: SDF of the surfaces, is there some volume overlap ?


::

    In [5]: lp0 = local_pos[volIdx==0]

    In [6]: lp1 = local_pos[volIdx==1]

    In [7]: lp2 = local_pos[volIdx==2]

    In [8]: plot3d(lp0)
    Out[8]:
    [(-387.5656604909922, -1270.176106207008, -371.1626120284283),
     (-0.0008747117256007186, -0.013089484067336343, 92.50043777067367),
     (0.8649689272960127, -0.08328071249086905, -0.4948667272502754)]

    In [9]: plot3d(lp1)
    Out[9]:
    [(-1113.737093503127, 845.8388952807445, -31.616225645797545),
     (-0.0037490452195925172, -0.0018631747295785317, 89.50236786419191),
     (0.29167582510180307, 0.5007524392759299, 0.8149676113873412)]

    In [10]: plot3d(lp2)
    Out[10]:
    [(154.06733168890418, 123.84050330126335, -4.536131466270664),
     (0.014702022773462886, -0.028748498119512078, 14.521880684656935),
     (-0.3741735425490822, 0.5770419692355915, 0.7259591763983569)]

    In [11]: lp3 = local_pos[volIdx==3]

    In [12]: lp3
    Out[12]: array([[-87.96 , 110.195, 152.483]])

    In [13]: lp1
    Out[13]:
    array([[  23.956, -114.304,  158.09 ],
           [  -1.15 ,  222.979,   79.662],
           [-147.45 ,   93.419,  127.653],
           ...,
           [ 183.576,    9.234,  120.753],
           [-194.838,   25.415,  109.951],
           [  29.807, -125.618,  153.059]])

    In [14]: local_theta[volIdx==1]
    Out[14]: array([0.636, 1.228, 0.939, ..., 0.99 , 1.061, 0.701])

    In [15]: local_theta[volIdx==3]
    Out[15]: array([0.746])





Investigate ceCat zeros : how can that happen at all : its 3inch
---------------------------------------------------------------------------

junoSD_PMT_v2::get_ce

::

    In [1]: ceCat
    Out[1]: array([6, 5, 6, ..., 4, 6, 6], dtype=uint32)

    In [2]: np.unique(ceCat)
    Out[2]: array([0, 4, 5, 6], dtype=uint32)

    In [3]: np.unique(ceCat, return_counts=True)
    Out[3]: (array([0, 4, 5, 6], dtype=uint32), array([ 32775, 271898, 112177, 583150]))

    In [4]: np.where(ceCat == 0 )
    Out[4]: (array([    45,    101,    146, ..., 999954, 999962, 999968]),)

    In [5]: 32775./1000000.
    Out[5]: 0.032775


After changing cats, all the zeros become 8::

    In [1]: np.unique(ceCat, return_counts=True)
    Out[1]: (array([4, 5, 6, 8], dtype=uint32), array([271898, 112177, 583150,  32775]))

::

     690         else if (volname == "NNVTMCPPMT_PMT_20inch_body_phys") {
     691             // calculate the angle theta
     692             double theta = localpos.theta();
     693             // do interpolate
     694             static double s_theta_NNVT[] = {
     695                 0.*deg, 14.*deg, 30.*deg, 42.5*deg, 55.*deg, 67.*deg,
     696                 77.5*deg, 85.*deg, 90.*deg,
     697             };
     698             static double s_ce_NNVT[] =    {
     699                 1.0,    1.0,    0.9453,     0.9105,     0.8931,     0.9255,
     700                 0.9274,     0.8841,     0.734,
     701             };
     702             static double s_ce_NNVT_highQE[] = {
     703                1.0,     1.0,    0.9772,     0.9723,     0.9699,     0.9697,
     704                0.9452,  0.9103,     0.734,
     705             };
     706
     707             if(!pmt_type && !qe_type){
     708                 static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT, 9, 0., 0.);
     709
     710                 ce_cat = 5 ;
     711                 return s_di.CubicSplineInterpolation(theta);
     712             }
     713             else if(!pmt_type && qe_type) {
     714                 static G4DataInterpolation s_di(s_theta_NNVT, s_ce_NNVT_highQE, 9, 0., 0.);
     715                 ce_cat = 6 ;
     716                 return s_di.CubicSplineInterpolation(theta);
     717             }
     718             ce_cat = 7 ;
     719         }
     720         ce_cat = 8 ;   // hit onto some other volname
     721
     722     } else if (m_ce_mode == "20inchflat"){




Response
-----------

When you meet a problem the first thing you should do is
take a look at the code where the error occurs.::


    epsilon:offline blyth$ find . -name PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    epsilon:offline blyth$ vi Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    epsilon:offline blyth$

::

     53 #ifdef WITH_G4OPTICKS
     54 void PMTEfficiencyCheck::addHitRecord(int pmtID, const G4ThreeVector& global_pos, const G4ThreeVector& local_pos, double qe, double ce, double de, const std::string& volname, int ce_cat )
     55 {
     56     unsigned volIdx = getVolnameIndex(volname);
     57     // NB volIdx uses the standard list of volname, not the one being collected below which is in an uncontrolled order
     58
     59     std::vector<std::string>& u = m_uvolname ;
     60     if(std::find(u.begin(), u.end(), volname ) == u.end()) u.push_back(volname); // collect unique volnames
     61
     62     double theta = local_pos.theta() ;
     63     double qe2 = m_jpmt->getQuantumEfficiency(pmtID);
     64     double ce2 = m_jpmt->getCollectionEfficiency(theta, pmtID);
     65     double de2 = m_jpmt->getDetectionEfficiency(theta, pmtID);
     66
     67     double epsilon = 1e-10 ;
     68     bool qe_match = std::abs(qe - qe2) < epsilon ;
     69     bool ce_match = std::abs(ce - ce2) < epsilon ;
     70     bool de_match = std::abs(de - de2) < epsilon ;
     71
     72     assert( qe_match );
     73     assert( ce_match );
     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Hu Yuxiang report
---------------------

::

    Hi simon,

          I did use the below commad line to install Opticks.

              bash junoenv opticks

         I updated the opticks  on your advice and it can simulate gamma event with low energy.
         When I want to simulate high energy event such as muon with 215GeV energy, it breaks down!


    1.  the command is :

    python tut_detsim.py --seed 10 --evtmax 1 --opticks-mode 1 --pmt20inch-polycone-neck    --no-guide_tube  gun  --particles mu- --momentums 215000


    the error is :


    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0)
    junoSD_PMT_v2::Initialize
    Begin of Event --> 0
    python: ../src/PMTEfficiencyCheck.cc:73: void PMTEfficiencyCheck::addHitRecord(int, const G4ThreeVector&, const G4ThreeVector&, double, double, double, const string&, int): Assertion `ce_match' failed.
     *** Break *** abort
    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 1 (Thread 0x7f03b92c5740 (LWP 39823)):

    #0  0x00007f03b7cca4b9 in waitpid () from /lib64/libc.so.6
    #1  0x00007f03b7c47f62 in do_system () from /lib64/libc.so.6
    #2  0x00007f03b7c48311 in system () from /lib64/libc.so.6
    #3  0x00007f03ae944364 in TUnixSystem::StackTrace() () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libCore.so
    #4  0x00007f03a9c00f2f in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libcppyy_backend3_8.so
    #5  0x00007f03ae946a8b in TUnixSystem::DispatchSignals(ESignals) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/ROOT/6.22.08/lib/libCore.so
    #6  <signal handler called>
    #7  0x00007f03b7c3b387 in raise () from /lib64/libc.so.6
    #8  0x00007f03b7c3ca78 in abort () from /lib64/libc.so.6
    #9  0x00007f03b7c341a6 in __assert_fail_base () from /lib64/libc.so.6
    #10 0x00007f03b7c34252 in __assert_fail () from /lib64/libc.so.6
    #11 0x00007f038045a803 in PMTEfficiencyCheck::addHitRecord (this=0x6595600, pmtID=pmtID
    entry=13411, global_pos=..., local_pos=..., qe=qe
    entry=0.36854931192660545, ce=ce
    entry=1, de=de
    entry=0.36854931192660545, volname="HamamatsuR12860_PMT_20inch_inner1_phys", ce_cat=0) at ../src/PMTEfficiencyCheck.cc:73
    #12 0x00007f038044477d in junoSD_PMT_v2::ProcessHits (this=0x6594c10, step=<optimized out>) at ../src/junoSD_PMT_v2.cc:373
    #13 0x00007f0390f9999c in G4SteppingManager::Stepping() () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so

    #14 0x00007f0390fa510d in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #15 0x00007f03911dcb53 in G4EventManager::DoProcessing(G4Event*) () from /home/ihep/juno/JUNO-SOFT/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #16 0x00007f0380927ba0 in G4SvcRunManager::SimulateEvent(int) () from /home/ihep/juno/JUNO-SOFT/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #17 0x00007f037ffa3d9b in DetSimAlg::execute (this=0x539bbd0) at ../src/DetSimAlg.cc:112
    #18 0x00007f03b0e05381 in Task::execute() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #19 0x00007f03b0e0bbe5 in TaskWatchDog::run() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #20 0x00007f03b0e04d68 in Task::run() () from /home/ihep/juno/JUNO-SOFT/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so


    2.  From your last reply, you mentioned the argument "--cerenkov-type  original". I use this argument in order to avoid the current hang problem. Did  you mean that if I use Opticks then I don't need to care about the current hang problem with G4Cerenkov_modified because Opticks will use its own G4Cerenkov ?




