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

TODO: compare a 2-layer stack with G4OpBoundaryProcess

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

    In [19]: np.c_[pos[trg_yes][50:80], mom[trg_yes][50:80], ds1[trg_yes][50:80] ]
    Out[19]: 
    array([[  46.925,    8.693,    0.   ,    0.   ,    0.   ,    1.   ,  181.57 ],
           [ -32.446,  131.811,    0.   ,    0.   ,    0.   ,    1.   ,  155.091],
           [  91.07 ,   34.099,    0.   ,    0.   ,    0.   ,    1.   ,  170.308],
           [ 131.236, -118.212,    0.   ,    0.   ,    0.   ,    1.   ,  130.4  ],
           [  57.876, -119.806,    0.   ,    0.   ,    0.   ,    1.   ,  156.374],
           [  72.393,  -99.086,    0.   ,    0.   ,    0.   ,    1.   ,  160.974],
           [   5.484,  -31.37 ,    0.   ,    0.   ,    0.   ,    1.   ,  183.481],
           [ -59.494,   49.156,    0.   ,    0.   ,    0.   ,    1.   ,  175.89 ],
           [   0.017,   -0.065,    0.   ,    0.   ,    0.   ,    1.   ,  185.   ],
           [ -83.808, -156.722,    0.   ,    0.   ,    0.   ,    1.   ,  129.575],
           [ -12.37 ,    7.716,    0.   ,    0.   ,    0.   ,    1.   ,  184.683],
           [  67.138, -110.352,    0.   ,    0.   ,    0.   ,    1.   ,  158.16 ],
           [ -32.627,   26.526,    0.   ,    0.   ,    0.   ,    1.   ,  182.343],
           [ 111.027,  140.15 ,    0.   ,    0.   ,    0.   ,    1.   ,  128.755],
           [ 108.86 ,  137.414,  131.379,   -0.541,   -0.684,   -0.489,    0.001],
           [ 108.859,  137.413,  131.379,   -0.597,   -0.753,   -0.278,  441.421],
           [ -76.758,   18.73 ,    0.   ,    0.   ,    0.   ,    1.   ,  175.44 ],
           [ -74.172,  -72.527,    0.   ,    0.   ,    0.   ,    1.   ,  168.18 ],
           [  -4.509,  -25.862,    0.   ,    0.   ,    0.   ,    1.   ,  183.969],
           [ -79.272, -171.727,    0.   ,    0.   ,    0.   ,    1.   ,  120.322],
           [ -79.272, -171.727,  120.322,    0.415,    0.899,   -0.141,  429.028],
           [   3.421,  -25.533,    0.   ,    0.   ,    0.   ,    1.   ,  184.007],
           [   0.88 ,  -17.677,    0.   ,    0.   ,    0.   ,    1.   ,  184.532],
           [ -30.582,  186.238,    0.   ,    0.   ,    0.   ,    1.   ,  120.675],
           [  94.902, -173.289,    0.   ,    0.   ,    0.   ,    1.   ,  112.593],
           [  94.902, -173.289,  112.593,   -0.48 ,    0.877,   -0.032,  407.604],
           [-100.135,  182.845,    0.   ,   -0.017,    0.031,    0.999,   97.215],
           [-101.784,  185.854,   97.154,    0.475,   -0.867,    0.149,  360.277],
           [-112.426, -145.043,    0.   ,    0.   ,    0.   ,    1.   ,  125.04 ],
           [-112.426, -145.043,  125.04 ,    0.599,    0.773,   -0.207,  437.744]])


