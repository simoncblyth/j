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


