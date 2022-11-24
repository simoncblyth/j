junoPMTOpticalModel
=====================

Doubtful of S/P handling : why E_s2 set to zero for _sin_theta1 <= 0 ? Thats just handling normal incidence
-------------------------------------------------------------------------------------------------------------

junoPMTOpticalModel::DoIt::

    443     norm = _inner1_solid->SurfaceNormal(pos);
    444 #ifdef PMTFASTSIM_STANDALONE
    445     minus_cos_theta = dir*norm ; 
    446 #endif
    447 
    448     if(whereAmI == kInGlass){
    449         norm *= -1.0;
    450     }
    451     _cos_theta1 = dir*norm;
    452 
    453     if(_cos_theta1 < 0.){
    454         _cos_theta1 = -_cos_theta1;
    455         norm = -norm;
    456     }
    457     // SCB : nasty multiple flips to normal vector, 
    458     //       simpler to have separate oriented_normal 
    459     //       and keep the original geometrical normal as fixed 
    460     //       and pointing outwards
    461     
    462     
    463     _aoi = acos(_cos_theta1)*360./twopi;
    464     
    465     CalculateCoefficients();
    466     
    467     G4double T  = 0.;
    468     G4double R  = 0.;
    469     G4double A  = 0.;
    470     G4double An = 0.;
    471     G4double escape_fac = 0.;
    472     G4double E_s2 = 0.;
    473     
    474     if(_sin_theta1 > 0.){
    475         E_s2 = (pol*dir.cross(norm))/_sin_theta1;
    476         E_s2 *= E_s2;
    477     }else{
    478         E_s2 = 0.;   
    479     }
    480 
    481     // SCB
    482     //    _sin_theta1 is zero at normal incidence where -cos(theta) is -1 and +1 
    483     //    and where dir.cross(norm) will be very small 
    484     //
    485     //    this is just because that S and P loose meaning at normal incidence
    486     //    so setting E_s2 to 0 artifically picks P for normal incidence
    487     //
    488     //    BUT that doesnt matter as s/p coeffs are equal at normal incidence anyhow::
    489     //
    490     //        fA_s = fA_p 
    491     //        fR_s = fR_p 
    492     //        fT_s = fT_p 
    493     //           



Hmm why the division by _sin_theta1 ? thats equivalent to my division by trans length
----------------------------------------------------------------------------------------


::

                    norm
                     |   dir 
                     |  /
                     | /
                     |/
         ------------+--------------


dir.cross(norm) 
    transverse to the the dir and norm
    so its out of the page, with length proportional to 
    the sin of the angle between the norm and the dir

dir.cross(norm)/_sin_theta1
    unit vector transverse to the normal and direction, 
    so its a vector within the plane of the surface 
    or tangential to it (pointing out the page in below)

pol*(dir.cross(norm)/_sin_theta1)
    transverse (S) component of the polarization 


Reflect and Refract polarization does not match G4OpBoundaryProcess
---------------------------------------------------------------------

TODO: compare jPOM polarization from a 2-layer stack with G4OpBoundaryProcess/Opticks

* I think they are going to be very different 

::

     747 /**
     748 junoPMTOpticalModel::Reflect junoPMTOpticalModel::Refract
     749 -----------------------------------------------------------
     750 
     751 Comparing to qsim::propagate_at_boundary (port of G4OpBoundaryProcess) 
     752 this is not the same polarization in both Reflect and Refract. 
     753 
     754 TODO: numerical comparison, see how big the difference 
     755 
     756 **/
     757 
     758 void junoPMTOpticalModel::Reflect()
     759 {
     760     dir -= 2.*(dir*norm)*norm;
     761     pol -= 2.*(pol*norm)*norm;
     762 }
     763 void junoPMTOpticalModel::Refract()
     764 {
     765     dir = (real(_cos_theta4) - _cos_theta1*_n1/_n4)*norm + (_n1/_n4)*dir;
     766     pol = (pol-(pol*dir)*dir).unit();
     767 }


Does the E_s2 calc assume once side of border incorrectly ?
--------------------------------------------------------------


Photon History Checking
-----------------------------

::

    u4t
    ./U4PMTFastSimTest.sh run
    ./U4PMTFastSimTest.sh ana
    ./U4PMTFastSimTest.sh nana


There are many ModelTrigger:YES across the fake Vacuum/Vacuum border equator 
-----------------------------------------------------------------------------

They do get propagated forward by dist1 : but thats dodgy on a coincident face. 

::

    In [8]: ds1_trg_yes = ds1[trg_yes]

    In [9]: np.histogram(ds1_trg_yes)
    Out[9]: 
    (array([  236,   304, 12674, 30597,  1738,  2058,   152,   188,  2706,    91]),
     array([  0.001,  49.784,  99.567, 149.35 , 199.133, 248.916, 298.699, 348.482, 398.265, 448.048, 497.831]))



TODO: select trg_yes with small dist1 and see where they are 


For the test situation of loadsa photons going in +Z direction 
from below the equator get loadsa ModelTrigger:YES at z=0::

    In [21]: np.c_[pos[trg_yes][50:80], mom[trg_yes][50:80], ds1[trg_yes][50:80], tim[trg_yes][50:80] ]
    Out[21]: 
    array([[  46.925,    8.693,    0.   ,    0.   ,    0.   ,    1.   ,  181.57 ,    0.3  ],
           [ -32.446,  131.811,    0.   ,    0.   ,    0.   ,    1.   ,  155.091,    0.3  ],
           [  91.07 ,   34.099,    0.   ,    0.   ,    0.   ,    1.   ,  170.308,    0.3  ],
           [ 131.236, -118.212,    0.   ,    0.   ,    0.   ,    1.   ,  130.4  ,    0.3  ],
           [  57.876, -119.806,    0.   ,    0.   ,    0.   ,    1.   ,  156.374,    0.3  ],
           [  72.393,  -99.086,    0.   ,    0.   ,    0.   ,    1.   ,  160.974,    0.3  ],
           [   5.484,  -31.37 ,    0.   ,    0.   ,    0.   ,    1.   ,  183.481,    0.3  ],
           [ -59.494,   49.156,    0.   ,    0.   ,    0.   ,    1.   ,  175.89 ,    0.3  ],
           [   0.017,   -0.065,    0.   ,    0.   ,    0.   ,    1.   ,  185.   ,    0.3  ],
           [ -83.808, -156.722,    0.   ,    0.   ,    0.   ,    1.   ,  129.575,    0.3  ],
           [ -12.37 ,    7.716,    0.   ,    0.   ,    0.   ,    1.   ,  184.683,    0.3  ],
           [  67.138, -110.352,    0.   ,    0.   ,    0.   ,    1.   ,  158.16 ,    0.3  ],
           [ -32.627,   26.526,    0.   ,    0.   ,    0.   ,    1.   ,  182.343,    0.3  ],
           [ 111.027,  140.15 ,    0.   ,    0.   ,    0.   ,    1.   ,  128.755,    0.3  ],
           [ 108.86 ,  137.414,  131.379,   -0.541,   -0.684,   -0.489,    0.001,    0.766],
           [ 108.859,  137.413,  131.379,   -0.597,   -0.753,   -0.278,  441.421,    0.766],
           [ -76.758,   18.73 ,    0.   ,    0.   ,    0.   ,    1.   ,  175.44 ,    0.3  ],
           [ -74.172,  -72.527,    0.   ,    0.   ,    0.   ,    1.   ,  168.18 ,    0.3  ],
           [  -4.509,  -25.862,    0.   ,    0.   ,    0.   ,    1.   ,  183.969,    0.3  ],
           [ -79.272, -171.727,    0.   ,    0.   ,    0.   ,    1.   ,  120.322,    0.3  ],
           [ -79.272, -171.727,  120.322,    0.415,    0.899,   -0.141,  429.028,    0.702],
           [   3.421,  -25.533,    0.   ,    0.   ,    0.   ,    1.   ,  184.007,    0.3  ],
           [   0.88 ,  -17.677,    0.   ,    0.   ,    0.   ,    1.   ,  184.532,    0.3  ],
           [ -30.582,  186.238,    0.   ,    0.   ,    0.   ,    1.   ,  120.675,    0.3  ],
           [  94.902, -173.289,    0.   ,    0.   ,    0.   ,    1.   ,  112.593,    0.3  ],
           [  94.902, -173.289,  112.593,   -0.48 ,    0.877,   -0.032,  407.604,    0.676],
           [-100.135,  182.845,    0.   ,   -0.017,    0.031,    0.999,   97.215,    3.839],
           [-101.784,  185.854,   97.154,    0.475,   -0.867,    0.149,  360.277,    4.163],
           [-112.426, -145.043,    0.   ,    0.   ,    0.   ,    1.   ,  125.04 ,    0.3  ],
           [-112.426, -145.043,  125.04 ,    0.599,    0.773,   -0.207,  437.744,    0.717]])


Control photon initial positions to make plotting and interpretation simpler
-----------------------------------------------------------------------------------


sysrap/storch.h::

    119 inline void storch::FillGenstep( storch& gs, unsigned genstep_id, unsigned numphoton_per_genstep )
    120 {   
    121     gs.gentype = OpticksGenstep_TORCH ;   
    122     gs.numphoton = numphoton_per_genstep  ;
    123     
    124     qvals( gs.pos , storch_FillGenstep_pos , "0,0,-90" );
    125     gs.time = 0.f ; 
    126     printf("//storch::FillGenstep storch_FillGenstep_pos gs.pos (%10.4f %10.4f %10.4f) \n", gs.pos.x, gs.pos.y, gs.pos.z );
    127     
    128     qvals( gs.mom , storch_FillGenstep_mom , "0,0,1" );
    129     gs.mom = normalize(gs.mom); 
    130     printf("//storch::FillGenstep storch_FillGenstep_mom gs.mom (%10.4f %10.4f %10.4f) \n", gs.mom.x, gs.mom.y, gs.mom.z );
    131     
    132     gs.wavelength = 501.f ;  
    133     gs.zenith = make_float2( 0.f, 1.f ); 
    134     gs.azimuth = make_float2( 0.f, 1.f );
    135     
    136     qvals( gs.radius, storch_FillGenstep_radius, "50" ); 
    137     printf("//storch::FillGenstep storch_FillGenstep_radius gs.radius (%10.4f) \n", gs.radius );
    138     
    139     gs.type = storchtype::Type("disc");  
    140     gs.mode = 255 ;    //torchmode::Type("...");  
    141 }

u4/tests/U4RecorderTest.h::

     35 struct U4RecorderTest
     36     : 
     37     public G4UserRunAction,
     38     public G4UserEventAction,
     39     public G4UserTrackingAction,
     40     public G4UserSteppingAction,
     41     public G4VUserPrimaryGeneratorAction,
     42     public G4VUserDetectorConstruction
     43 {

Generation from SGenerate::GeneratePhotons::

    105 /**
    106 U4VPrimaryGenerator::GeneratePrimaries
    107 ---------------------------------------
    108 
    109 1. generates NP array of Opticks sphoton or sphotond with SGenerate::GeneratePhotons 
    110 2. populates the G4Event argument with these as G4PrimaryVertex
    111 
    112 Notice that there are no G4Track in sight here, so there is no 
    113 way to annotate the tracks with *spho* labels.  
    114 
    115 **/
    116 
    117 inline void U4VPrimaryGenerator::GeneratePrimaries(G4Event* event)
    118 {   
    119     NP* ph = SGenerate::GeneratePhotons(); 



Ten photons down : at apex : reordered to put same histories together
-----------------------------------------------------------------------

Logging only in ModelTrigger with FastSim envelope the body_log (so dont see pmt_phys here)::

    epsilon:tests blyth$ grep photon_id U4PMTFastSimTest.log
     Hdr  photon_id      9 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      8 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      7 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      4 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      3 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      1 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      0 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)

     Hdr  photon_id      6 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      6 volumeName         _inner1_phys lpos                    (0,0,185)     ldir                    (0,0,-1)
     Hdr  photon_id      6 volumeName         _inner2_phys lpos                    (0,0,0)       ldir                    (0,0,-1)

     Hdr  photon_id      5 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      5 volumeName         _inner1_phys lpos                    (0,0,185)     ldir                    (0,0,-1)
     Hdr  photon_id      5 volumeName         _inner2_phys lpos                    (0,0,0)       ldir                    (0,0,-1)

     Hdr  photon_id      2 volumeName           _body_phys lpos                    (0,0,185.001) ldir                    (0,0,-1)
     Hdr  photon_id      2 volumeName         _inner1_phys lpos                    (0,0,185)     ldir                    (0,0,-1)
     Hdr  photon_id      2 volumeName         _inner2_phys lpos                    (0,0,0)       ldir                    (0,0,-1)



More Photons to look for intersecting histories, as far as can see from ModelTrigger
-----------------------------------------------------------------------------------------

::

     Hdr  photon_id     96 volumeName           _body_phys lpos                    (201.463,0,108.723) ldir                    (-0.0827612,0,-0.996569)
     Hdr  photon_id     96 volumeName         _inner1_phys lpos                    (201.463,0,108.722) ldir                    (0.510805,0,-0.859697)
     Hdr  photon_id     96 volumeName         _inner1_phys lpos                    (243.875,0,37.3422) ldir                    (0.00504964,0,-0.999987)
     Hdr  photon_id     96 volumeName         _inner2_phys lpos                    (244.063,0,0) ldir                          (0.00504964,0,-0.999987)
     Hdr  photon_id     96 volumeName           _body_phys lpos                    (244.27,0,-40.8886) ldir                    (-0.501479,0,-0.86517)
     Hdr  photon_id     96 volumeName         _inner2_phys lpos                    (244.27,0,-40.8886) ldir                    (-0.501479,0,-0.86517)
     Hdr  photon_id     96 volumeName           _body_phys lpos                    (202.936,0,-112.199) ldir                    (-0.84228,0,-0.539041)
     Hdr  photon_id     96 volumeName         _inner2_phys lpos                    (202.936,0,-112.199) ldir                    (-0.84228,0,-0.539041)


Pick some big history photons::

    In [4]: u_pid, u_pid_count = np.unique( pid, return_counts=True )     

    In [12]: u_pid[u_pid_count > 12]
    Out[12]: array([726])

    In [13]: pos.shape
    Out[13]: (1671, 3)

    In [14]: pid.shape
    Out[14]: (1671,)

    In [15]: np.where( pid == 726 )
    Out[15]: (array([460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473]),)



    In [17]: np.c_[pos[pid == 726],mom[pid == 726]]
    Out[17]: 
    array([[-112.83 ,    0.   ,  164.918,    0.032,    0.   ,   -0.999],
           [-112.83 ,    0.   ,  164.917,   -0.138,    0.   ,   -0.99 ],
           [-156.577,    0.   , -148.846,    0.81 ,    0.   ,    0.587],
           [ -95.   ,    0.   , -104.211,   -0.81 ,    0.   ,    0.587],
           [-238.764,    0.   ,   -0.   ,   -0.81 ,    0.   ,    0.587],
           [-248.807,    0.   ,    7.28 ,    0.867,    0.   ,    0.498],
           [  53.205,    0.   ,  180.727,    0.665,    0.   ,   -0.747],
           [ 245.605,    0.   ,  -35.443,   -0.92 ,    0.   ,   -0.391],
           [  95.   ,    0.   ,  -99.428,    0.92 ,    0.   ,   -0.391],
           [ 177.724,    0.   , -134.574,   -0.127,    0.   ,    0.992],
           [ 160.533,    0.   ,    0.   ,   -0.127,    0.   ,    0.992],
           [ 141.059,    0.   ,  152.451,   -0.878,    0.   ,   -0.479],
           [-239.66 ,    0.   ,  -55.195,    0.975,    0.   ,    0.224],
           [   0.427,    0.   ,    0.   ,    0.975,    0.   ,    0.224]])




Understanding the positions
------------------------------


::

     373 /**
     374 HamamatsuR12860PMTManager::helper_make_solid
     375 ----------------------------------------------
     376 
     377 * body_delta depends on m_enable_optical_model 
     378 * TODO: find out why body solid is needed at all 
     379 
     380 m_enable_optical_model:false
     381 
     382    1e-3  0                           -5
     383     | Py |             Py            |   Vac
     384     |    |                           |
     385    pmt  body                        inner
     386 
     387 
     388 m_enable_optical_model:true
     389 
     390    1e-3                    -5+1e-3  -5
     391     |         Py                 Py  |    Vac 
     392     |                         |      |
     393    pmt                       body   inner
     394 
     395 **/



9e99 kInfinity is obnoxious : replace with -1
-------------------------------------------------

::

    In [15]: extra[:,1]
    Out[15]: 
    array([[ 3.242e-02,  0.000e+00, -9.995e-01,  1.050e-03],
           [-1.381e-01,  0.000e+00, -9.904e-01,  1.665e+02],
           [ 8.097e-01,  0.000e+00,  5.869e-01,  2.536e+02],
           [-8.097e-01,  0.000e+00,  5.869e-01,  1.776e+02],
           [-8.097e-01,  0.000e+00,  5.869e-01,  1.240e+01],
           [ 8.672e-01,  0.000e+00,  4.980e-01,  3.483e+02],


    In [16]: np.where( extra == 9e99 )
    Out[16]: 
    (array([ 4,  5,  7,  8,  8, 10, 13]),
     array([2, 2, 1, 1, 2, 2, 2]),
     array([3, 3, 3, 3, 3, 3, 3]))

    In [17]: extra[np.where( extra == 9e99 )] = -1

    In [18]: extra
    Out[18]: 
    array([[[-112.83 ,    0.   ,  164.918,    0.164],
            [   0.032,    0.   ,   -0.999,    0.001],
            [   0.   ,   -1.   ,    0.   ,  165.005],
            [   1.   ,    1.   ,    0.   ,  726.   ]],

           [[-112.83 ,    0.   ,  164.917,    0.164],
        

Looking at big bouncer note two bounces off inside at top 
not giving trigger when would have expected them to. 

* this is because DoIt shifts forwards by dist1 : so ModelTrigger is effectively 
  triggering *dist1* ahead 



HMM : want to repeat a single torch photon selected from a large sample : how to do that ?
---------------------------------------------------------------------------------------------

* generation is quick, might as well just apply a mask to the ph array 

::

    117 inline void U4VPrimaryGenerator::GeneratePrimaries(G4Event* event)
    118 {
    119     NP* ph = SGenerate::GeneratePhotons();

Best place to do that is `NP* SGenerate::GeneratePhotons()` so can 
apply to all genstep types. 

HMM: can NP already do item masking ?

* seems not,  bring over from NPY::make_masked
* YES: that will be needed, added this into NP::MakeSelectCopy 

  * just need "export SGenerate_GeneratePhotons_MASK=726" to mask the generated

* BUT also need to record positions and reset Geant4 random stream 

  * investigating in U4EngineTest.cc


Adding evt.save() causes error:: 

    2022-11-23 11:26:24.746 INFO  [62626867] [SEvt::save@1541] SGeo::DefaultDir $DefaultOutputDir
    2022-11-23 11:26:24.746 INFO  [62626867] [SEvt::save@1613]  dir /tmp/blyth/opticks/GEOM/hamaLogicalPMT/U4PMTFastSimTest/ALL
    2022-11-23 11:26:24.746 INFO  [62626867] [SEvt::save@1615] [ gather 
    2022-11-23 11:26:24.747 INFO  [62626867] [SEvt::gather@1493]  k         genstep a  <f4(1, 6, 4, )
    2022-11-23 11:26:24.747 INFO  [62626867] [SEvt::gather@1493]  k          photon a  <f4(1000, 4, 4, )
    2022-11-23 11:26:24.748 FATAL [62626867] [*SEvt::gatherHit@1378]  not yet implemented for hostside running : getting this error indicates CompMask mixup
    Assertion failed: (0), function gatherHit, file /Users/blyth/opticks/sysrap/SEvt.cc, line 1379.
    ./U4PMTFastSimTest.sh: line 66: 12386 Abort trap: 6           $bin
    ./U4PMTFastSimTest.sh run error
    epsilon:tests blyth$ 



Added RunningMode to SEventConfig for g4state save/rerun control::

    In [1]: a = np.load("/tmp/blyth/opticks/GEOM/hamaLogicalPMT/U4PMTFastSimTest/ALL/g4states.npy")

    In [2]: a.shape
    Out[2]: (1000, 38)

    In [13]: a[0]
    Out[13]: 
    array([2888826676, 3514589213,  215100124, 2552366885,  419715749, 1994477360,  459065707, 2217638329,  348294683, 1646814406,  415070695,  474756176,  528547226, 2937583061,  376307002, 1319456156,
            234690512,  312598043,  512101989, 1866186205,  241132494, 1788253485,  402684727, 3712579448,    4998380,  409334120,  339164266,  159141042,   77681803, 1507596083,   28576003,  425264305,
            106735813, 2657964106,  257569119,          6, 3726794656,  135598090], dtype=uint64)


    In [10]: a.max()
    Out[10]: 4294894629

    In [11]: a.max() < 0xffffffff    ## its twice the size as using uint64 when would fit into uint32 
    Out[11]: True                    ## its because "unsigned long" is 64bit and not 32bit (as it apparently is on some ancient OS)






Debug g4state rerun
-----------------------


::

    5112 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PostUserTrackingAction_Optical@245]
     5113 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PreUserTrackingAction@88]
     5114 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PreUserTrackingAction_Optical@130]
     5115 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PreUserTrackingAction_Optical@154]  labelling photon spho (gs:ix:id:gn   0 726  726  0)
     5116 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::saveOrLoadStates@206]  id == SEventConfig::_G4StateRerun 726
     5117 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::saveOrLoadStates@207] U4Engine::DescStateArray
     5118 state = np.array([ 2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 535678722, 1842038071, 30747806, 1828      092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021,       468350706, 1222870066, 335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64)
     5119 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::saveOrLoadStates@224]  max_state 1000
     5120 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::UserSteppingAction_Optical@304]
     5121 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::Check_TrackStatus_Flag@367]  step.tstat fAlive BOUNDARY_TRANSMIT
     5122 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::UserSteppingAction_Optical@304]
     5123 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::Check_TrackStatus_Flag@367]  step.tstat fAlive BOUNDARY_TRANSMIT
     5124 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::UserSteppingAction_Optical@304]
     5125 2022-11-23 20:41:22.198 ERROR [63354588] [U4Recorder::UserSteppingAction_Optical@328]  ERR flag zero : post U4StepPoint::Desc proc 0 procName Undefined status 1 statu      sName fGeomBoundary bstat 12 bstatName SameMaterial flag 0 flagName .
     5126 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::Check_TrackStatus_Flag@367]  step.tstat fSuspend .
     5127 2022-11-23 20:41:22.198 FATAL [63354588] [U4Recorder::Check_TrackStatus_Flag@394]  unexpected trackstatus  trackStatus fSuspend flag .
     5128 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PostUserTrackingAction@89]
     5129 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PostUserTrackingAction_Optical@245]
     5130 2022-11-23 20:41:22.198 INFO  [63354588] [U4Recorder::PostUserTrackingAction_Optical@256]  not is_fStopAndKill  post.tstat fSuspend
     5131 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::PreUserTrackingAction@88]
     5132 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::PreUserTrackingAction_Optical@130]
     5133 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::saveOrLoadStates@206]  id == SEventConfig::_G4StateRerun 726
     5134 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::saveOrLoadStates@207] U4Engine::DescStateArray
     5135 state = np.array([ 2888826676, 3162134576, 204179185, 1635965861, 104104595, 210017765, 54421913, 3212691643, 186327343, 90518726, 213612834, 2952750858, 529322658, 2      988860439, 505676476, 2805755598, 188798436, 1526251316, 108244360, 4127086702, 232821609, 2312679732, 471165782, 1599121603, 245691924, 3156443174, 417089942, 228523      5186, 415866305, 2456245545, 20413889, 454387351, 288821452, 848617616, 271473783, 7, 1465025331, 163065198 ], dtype=np.uint64)
     5136 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::saveOrLoadStates@224]  max_state 1000
     5137 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::UserSteppingAction_Optical@304]
     5138 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::Check_TrackStatus_Flag@367]  step.tstat fAlive BOUNDARY_TRANSMIT
     5139 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::UserSteppingAction_Optical@304]
     5140 2022-11-23 20:41:22.199 INFO  [63354588] [U4Recorder::Check_TrackStatus_Flag@367]  step.tstat fAlive SURFACE_SREFLECT



::

    In [16]: np.all( a[726] == state )
    Out[16]: True


Need to restore state at the same place where labelling happens, as that happens once per photon::

    epsilon:tests blyth$ grep labelling U4PMTFastSimTest.log > /tmp/labelling
    epsilon:tests blyth$ vi /tmp/labelling
    epsilon:tests blyth$ wc /tmp/labelling
        1000   13000  142000 /tmp/labelling
    epsilon:tests blyth$ 

::

     5037 2022-11-23 22:01:49.249 INFO  [63431498] [U4Recorder::PreUserTrackingAction_Optical@130]
     5038 2022-11-23 22:01:49.249 INFO  [63431498] [U4Recorder::PreUserTrackingAction_Optical@154]  labelling photon spho (gs:ix:id:gn   0 726  726  0)
     5039 2022-11-23 22:01:49.250 INFO  [63431498] [U4Recorder::saveOrLoadStates@207]  id == SEventConfig::_G4StateRerun 726
     5040 2022-11-23 22:01:49.250 INFO  [63431498] [U4Recorder::saveOrLoadStates@208] U4Engine::DescStateArray
     5041 
     5042 state = np.array([
     5043 2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646,
     5044 535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860,
     5045 287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066,
     5046 335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64)
     5047 
     5048 2022-11-23 22:01:49.250 INFO  [63431498] [U4Recorder::saveOrLoadStates@225]  max_state 1000
     5049 2022-11-23 22:01:49.250 INFO  [63431498] [U4Recorder::UserSteppingActi


SEvtLoadTest.sh::

    2022-11-23 22:39:26.922 INFO  [63476608] [main@24]  SEvt::getG4State (1000, 38, )
    SEventConfig::_G4StateRerun 726
    np.array([ 
    2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 
    535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 
    287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066, 
    335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64 )
    epsilon:tests blyth$ 



    2022-11-23 22:59:25.382 INFO  [63517682] [U4Recorder::PreUserTrackingAction_Optical@154]  labelling photon spho (gs:ix:id:gn   0 726  726  0)
    2022-11-23 22:59:25.382 INFO  [63517682] [U4Recorder::saveOrLoadStates@241] U4Engine::RestoreState for id (SEventConfig::_G4StateRerun)  726
    U4Engine::DescStateArray

    state = np.array([ 
    2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 
    535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 
    287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066, 
    335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64 )

    2022-11-23 22:59:25.382 INFO  [63517682] [U4Recorder::UserSteppingAction_Optical@316] 



/tmp/blyth/opticks/GEOM/hamaLogicalPMT/U4PMTFastSimTest/ALL



Making sense of the big bouncer
----------------------------------

::

    ./U4PMTFastSimTest.sh

HMM: to succeed to rerun with SRM_G4STATE_RERUN 
have to keep almost everything in the .sh the same as when save the states 
with SRM_G4STATE_SAVE::

     13 export Local_G4Cerenkov_modified_DISABLE=1
     14 export Local_DsG4Scintillation_DISABLE=1
     15 export G4FastSimulationManagerProcess_ENABLE=1
     16 
     17 #running_mode=SRM_G4STATE_SAVE  
     18 running_mode=SRM_G4STATE_RERUN
     19 export OPTICKS_RUNNING_MODE=$running_mode   # see SEventConfig::RunningMode
     20 export OPTICKS_G4STATE_RERUN=726
     21 
     22 export GEOM=hamaLogicalPMT
     23 export U4RecorderTest__PRIMARY_MODE=torch
     24 # hmm seems iphoton and torch do same thing internally 
     25 export BeamOn=${BeamOn:-1}
     26 
     27 export hama_FastCoverMaterial=Cheese
     28 export hama_UsePMTOpticalModel=1
     29 
     30 #num_ph=2
     31 #num_ph=10
     32 num_ph=1000
     33 #num_ph=50000
     34 
     35 radius=250
     36 #radius=0
     37 [ $num_ph -lt 11  ] && radius=0
     38 
     39 export SEvent_MakeGensteps_num_ph=$num_ph
     40 export storch_FillGenstep_type=line     # disc
     41 export storch_FillGenstep_radius=$radius
     42 
     43 # up from line below equator
     44 #export storch_FillGenstep_pos=0,0,-20
     45 #export storch_FillGenstep_mom=0,0,1
     46 
     47 # down from line outside Pyrex
     48 export storch_FillGenstep_pos=0,0,200
     49 export storch_FillGenstep_mom=0,0,-1
     50 
     51 
     52 bin=U4PMTFastSimTest
     53 log=$bin.log
     54 
     55 loglevel(){
     56    export U4Recorder=INFO
     57    #export junoPMTOpticalModel=INFO
     58    #export SEvt=INFO
     59    export SEventConfig=INFO
     60 }
     61 loglevel
     62 
     63 
     64 defarg="run"
     65 arg=${1:-$defarg}
     66 
     67 if [ "$arg" == "run" ]; then
     68     [ -f "$log" ] && rm $log
     69     $bin
     70     [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 1
     71 fi
     72 




::

    2022-11-24 11:05:22.892 INFO  [63694727] [U4Recorder::BeginOfRunAction@84] 
    2022-11-24 11:05:22.892 INFO  [63694727] [U4RecorderTest::GeneratePrimaries@152] [ fPrimaryMode T
    SGenerate::GeneratePhotons rerun_id 726 ph  <f4(1000, 4, 4, ) phs  <f4(1, 4, 4, ) (OPTICKS_G4STATE_RERUN) 
    U4VPrimaryGenerator::GeneratePrimaries ph (1, 4, 4, )
    2022-11-24 11:05:22.895 INFO  [63694727] [U4RecorderTest::GeneratePrimaries@160] ]
    2022-11-24 11:05:22.896 INFO  [63694727] [U4Recorder::BeginOfEventAction@86] 
    2022-11-24 11:05:22.897 INFO  [63694727] [U4Recorder::PreUserTrackingAction@88] 
    2022-11-24 11:05:22.897 INFO  [63694727] [U4Recorder::PreUserTrackingAction_Optical@130] 
    2022-11-24 11:05:22.897 INFO  [63694727] [U4Recorder::PreUserTrackingAction_Optical@148]  setting rerun_id 726
    2022-11-24 11:05:22.897 INFO  [63694727] [U4Recorder::PreUserTrackingAction_Optical@154]  labelling photon spho (gs:ix:id:gn   0 726  726  0)
    2022-11-24 11:05:22.898 INFO  [63694727] [U4Recorder::saveOrLoadStates@241] U4Engine::RestoreState for id (SEventConfig::_G4StateRerun)  726
    U4Engine::DescStateArray

    state = np.array([ 
    2888826676, 853948299, 81707227, 2768798580, 436796321, 24866296, 309900311, 3416087829, 320598279, 83213646, 
    535678722, 1842038071, 30747806, 1828092817, 252805928, 1781365106, 522054134, 800148090, 188640588, 1209180860, 
    287663768, 1713468264, 94225986, 1924824469, 37977166, 1704769691, 201322355, 1866980021, 468350706, 1222870066, 
    335732855, 2097966227, 425291744, 3793320011, 506523491, 13, 3162134576, 204179185 ], dtype=np.uint64 )



From::

    ./U4PMTFastSim.sh nana

    In [3]: extra.reshape(-1,16)
    Out[3]: 
    array([[-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.001,    0.   ,   -1.   ,    0.   ,  165.005,    1.   ,    1.   ,    0.   ,  726.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,  166.512,    0.   ,   -1.   ,    0.   ,  166.512,    0.   ,    2.   ,    0.   ,  726.   ],
           [-156.577,    0.   , -148.846,    1.778,    0.81 ,    0.   ,    0.587,  253.614,    0.   ,    1.   ,    0.   ,    0.   ,    0.   ,    1.   ,    0.   ,  726.   ],
           [ -95.   ,    0.   , -104.211,    2.166,   -0.81 ,    0.   ,    0.587,  177.561,    0.   ,   -1.   ,    0.   ,  169.042,    0.   ,    1.   ,    0.   ,  726.   ],
           [-238.764,    0.   ,   -0.   ,    3.071,   -0.81 ,    0.   ,    0.587,   12.404,    0.   ,   -1.   ,    0.   ,   -1.   ,    1.   ,    2.   ,    0.   ,  726.   ],
           [-248.807,    0.   ,    7.28 ,    3.112,    0.867,    0.   ,    0.498,  348.275,    0.   ,   -1.   ,    0.   ,   -1.   ,    1.   ,    2.   ,    0.   ,  726.   ],
           [  53.205,    0.   ,  180.727,    4.274,    0.665,    0.   ,   -0.747,  241.943,    0.   ,   -1.   ,    0.   ,  241.943,    0.   ,    2.   ,    0.   ,  726.   ],
           [ 245.605,    0.   ,  -35.443,    5.749,   -0.92 ,    0.   ,   -0.391,   -1.   ,    0.   ,    1.   ,    0.   ,    0.   ,    0.   ,    1.   ,    0.   ,  726.   ],
           [  95.   ,    0.   ,  -99.428,    6.583,    0.92 ,    0.   ,   -0.391,   -1.   ,    0.   ,   -1.   ,    0.   ,   -1.   ,    0.   ,    1.   ,    0.   ,  726.   ],
           [ 177.724,    0.   , -134.574,    7.041,   -0.127,    0.   ,    0.992,  135.667,    0.   ,    1.   ,    0.   ,    0.   ,    0.   ,    1.   ,    0.   ,  726.   ],
           [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,  153.69 ,    0.   ,    1.   ,    0.   ,   -1.   ,    1.   ,    2.   ,    0.   ,  726.   ],
           [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,  318.39 ,    0.   ,    1.   ,    0.   ,  318.39 ,    0.   ,    2.   ,    0.   ,  726.   ],
           [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,  246.349,    0.   ,   -1.   ,    0.   ,    0.   ,    0.   ,    1.   ,    0.   ,  726.   ],
           [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,  243.678,    0.   ,   -1.   ,    0.   ,   -1.   ,    1.   ,    2.   ,    0.   ,  726.   ]])

    In [4]:            


FastSim record saving is mangled with overwrites
--------------------------------------------------

Record/photon somehow mangled. 
Checking the times makes it clear that overwrites are happening. 

* The record slot needs adapting for FastSim somehow. 

Its kinda like reemission rejoining with the photon history 
split up into multiple tracks that need joining. But need to 
correctly determine the record slot at which to write the entry.  

Some of the positions/times/mom match ModelTrigger but many do not. The first is repeated::

    In [6]: t.record.shape
    Out[6]: (1000, 10, 4, 4)

    In [11]: t.record[726].reshape(-1,16)
    Out[11]: 
    array([[ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-138.46 ,    0.   ,    0.   ,    9.867,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 237.91 ,    0.   ,   54.596,   12.523,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)


    In [12]: t.photon[726]                                                                                                                                                       
    Out[12]: 
    array([[237.91 ,   0.   ,  54.596,  12.523],
           [  0.975,   0.   ,   0.224,   0.   ],
           [  0.   ,  -1.   ,   0.   , 420.   ],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)

    In [13]:                                                                        


Get multiple first_point::

    U4Recorder::BeginOfEventAction@86: 
    U4Recorder::UserSteppingAction_Optical@341:  first_point 
    U4Recorder::UserSteppingAction_Optical@341:  first_point 
    U4Recorder::UserSteppingAction_Optical@341:  first_point 
    U4Recorder::UserSteppingAction_Optical@341:  first_point 
    U4Recorder::UserSteppingAction_Optical@341:  first_point 
    U4Recorder::EndOfEventAction@87: 






    epsilon:tests blyth$ grep U4StepPoint::DescPositionTime U4PMTFastSimTest.log
    U4StepPoint::DescPositionTime (   -113.000      0.000    170.163      0.137)  ?

    U4StepPoint::DescPositionTime (   -112.830      0.000    164.918      0.164)  0
    U4StepPoint::DescPositionTime (   -112.830      0.000    164.917      0.164)  1

    U4StepPoint::DescPositionTime (   -135.824      0.000      0.000      1.012)  ??? 

    U4StepPoint::DescPositionTime (   -156.577      0.000   -148.846      1.778)  2
    U4StepPoint::DescPositionTime (    -95.000      0.000   -104.211      2.166)  3
    U4StepPoint::DescPositionTime (   -238.764      0.000     -0.000      3.071)  4
    U4StepPoint::DescPositionTime (   -248.807      0.000      7.280      3.112)  5
    U4StepPoint::DescPositionTime (     53.205      0.000    180.727      4.274)  6

    U4StepPoint::DescPositionTime (    214.060      0.000      0.000      5.507)  ???

    U4StepPoint::DescPositionTime (    245.605      0.000    -35.443      5.749)  7
    U4StepPoint::DescPositionTime (     95.000      0.000    -99.428      6.583)  8
    U4StepPoint::DescPositionTime (    177.724      0.000   -134.574      7.041)  9
    U4StepPoint::DescPositionTime (    160.533      0.000      0.000      7.732) 10 
    U4StepPoint::DescPositionTime (    141.059      0.000    152.451      8.245) 11

    U4StepPoint::DescPositionTime (   -138.460      0.000      0.000      9.867)  ???

    U4StepPoint::DescPositionTime (   -239.660      0.000    -55.195     10.455) 12 
    U4StepPoint::DescPositionTime (      0.427      0.000      0.000     11.710) 13

    U4StepPoint::DescPositionTime (    237.910      0.000     54.596     12.523)  ?
    epsilon:tests blyth$ 



53 2022-11-24 12:24:30.078 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@323]
 54 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::Check_TrackStatus_Flag@383]  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
 55 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@357] U4StepPoint::DescPositionTime (   -113.000      0.000    170.163      0.137)
 56 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@323]
 57 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::Check_TrackStatus_Flag@383]  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical
 58 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@357] U4StepPoint::DescPositionTime (   -112.830      0.000    164.918      0.164)
 59 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@323]
 60 2022-11-24 12:24:30.079 ERROR [63973055] [U4Recorder::UserSteppingAction_Optical@345]  ERR flag zero : post U4StepPoint::Desc proc 0 procName Undefined status 1 statusNa    me fGeomBoundary bstat 12 bstatName SameMaterial flag 0 flagName .
 61 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::Check_TrackStatus_Flag@383]  step.tstat fSuspend . from UserSteppingAction_Optical
 62 2022-11-24 12:24:30.079 FATAL [63973055] [U4Recorder::Check_TrackStatus_Flag@410]  unexpected trackstatus  trackStatus fSuspend flag .
 63 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::UserSteppingAction_Optical@357] U4StepPoint::DescPositionTime (   -112.830      0.000    164.917      0.164)
 64 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::PostUserTrackingAction@89]
 65 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::PostUserTrackingAction_Optical@262]
 66 2022-11-24 12:24:30.079 INFO  [63973055] [U4Recorder::PostUserTrackingAction_Optical@273]  not is_fStopAndKill  post.tstat fSuspend
 67 2022-11-24 12:24:30.079 INFO  [639730




Seems get new track at every FastSim DoIt::

    epsilon:tests blyth$ grep "U4Recorder::PreUserTrackingAction_Optical@185: ]" U4PMTFastSimTest.log
    U4Recorder::PreUserTrackingAction_Optical@185: ]
    U4Recorder::PreUserTrackingAction_Optical@185: ]
    U4Recorder::PreUserTrackingAction_Optical@185: ]
    U4Recorder::PreUserTrackingAction_Optical@185: ]
    U4Recorder::PreUserTrackingAction_Optical@185: ]
    epsilon:tests blyth$ 


Hmm need way to get info from fast_sim_man to the recorder analogous to boundary process::

    171 void U4RecorderTest::UserSteppingAction(const G4Step* step){     fRecorder->UserSteppingAction<InstrumentedG4OpBoundaryProcess>(step); }

::

    146     else if( status == fGeomBoundary && proc == U4StepPoint_Transportation )
    147     {
    148         unsigned bstat = U4OpBoundaryProcess::GetStatus<T>(); 
    149 
    150         flag = BoundaryFlag(bstat) ;
    151         LOG_IF(LEVEL, flag == NAN_ABORT )
    152             << " fGeomBoundary "
    153             << " U4OpBoundaryProcessStatus::Name " << U4OpBoundaryProcessStatus::Name(bstat)
    154             << " flag " << OpticksPhoton::Flag(flag)
    155             ;



How to get access to the appropriate G4VFastSimulationModel for a PMT so can ask for a status flag ?
---------------------------------------------------------------------------------------------------------

::

    junoPMTOpticalModel : public G4VFastSimulationModel

    148 void U4Physics::ConstructOp()
    149 {
    ...
    165     if(EInt("G4FastSimulationManagerProcess_ENABLE", "0") == 1 )
    166     {
    167         fFastSim  = new G4FastSimulationManagerProcess("fast_sim_man");
    168     }
    ...
    205         if (particleName == "opticalphoton")
    206         {
    207             pmanager->AddDiscreteProcess(fAbsorption);
    208             pmanager->AddDiscreteProcess(fRayleigh);
    209             //pmanager->AddDiscreteProcess(fMieHGScatteringProcess);
    210             pmanager->AddDiscreteProcess(fBoundary);
    211             if(fFastSim) pmanager->AddDiscreteProcess(fFastSim);
    212         }


Can access the fast_sim_man process, but how to get to the appropriate model from that ?
The one that just triggered and did its DoIt ?

Does not look like any API to do this in G4FastSimulationManagerProcess

* difficulty is the opticks U4Recorder code cannot directly use junoPMTOpticalModel, 
  so need an intermediary that can be used to post the status at the last DoIt 

* can require that the fast sim model implements a protocol base S4FastSimOpticalModel 
  that returns the status of the last DoIt 

::

      1 #pragma once
      2 struct S4FastSimOpticalModel
      3 {
      4     virtual char getStatus() const = 0 ;  // 'A' 'R' 'T' 'D' '?'
      5 };



    In [6]: t.record.shape
    Out[6]: (1000, 10, 4, 4)

    In [11]: t.record[726].reshape(-1,16)
    Out[11]: 
    array([[ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-138.46 ,    0.   ,    0.   ,    9.867,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 237.91 ,    0.   ,   54.596,   12.523,    0.975,    0.   ,    0.224,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)




