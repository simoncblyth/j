hmsk_solidMaskTail_and_solidMask_need_coincidence_avoidance_to_prevent_intersects_inside_PMT
================================================================================================

preparations
---------------

Grabbed HamamatsuMaskManager and NNVTMaskManager over to j/PMTSim and adapted for standalone testing, 
such that PMTSim::GetSolid can provide its geometry. 


Testing the fix
-------------------

::

    ## examine the CSG tree
    GEOM=hmsk_solidMaskTail GetSolidTest 
    GEOM=hmsk_solidMask     GetSolidTest 
    GEOM=nmsk_solidMaskTail GetSolidTest 
    GEOM=nmsk_solidMask     GetSolidTest 


    ## view the Geant4 polygonization to get familiar with geometry 
    x4                                      ## cd ~/opticks/extg4

    GEOM=hmsk_solidMaskTail EYE=1,1,0.8 ZOOM=2   ${IPYTHON:-ipython} -i tests/X4MeshTest.py 
    GEOM=nmsk_solidMaskTail EYE=1,1,0.8 ZOOM=2   ${IPYTHON:-ipython} -i tests/X4MeshTest.py 
    GEOM=hmsk_solidMask     EYE=1,1,-0.8 ZOOM=2  ${IPYTHON:-ipython} -i tests/X4MeshTest.py 
    GEOM=nmsk_solidMask     EYE=1,1,-0.8 ZOOM=2  ${IPYTHON:-ipython} -i tests/X4MeshTest.py 


    ## convert G4VSolid obtained from from j/PMTSim into GGeo and then CSGFoundry  

    gc   # cd ~/opticks/GeoChain 
    GEOM=hmsk_solidMaskTail ./run.sh    
    GEOM=nmsk_solidMaskTail ./run.sh    
    GEOM=hmsk_solidMask     ./run.sh        ## writes to /tmp/blyth/opticks/GeoChain_Darwin/hmsk_solidMask/CSGFoundry/
    GEOM=nmsk_solidMask     ./run.sh        

    ## create ray trace renders of the CSGFoundry geometry 

    cx   # cd ~/opticks/CSGOptiX                               

    GEOM=hmsk_solidMaskTail EYE=0.7,0.7,0.5 TMIN=0.0 ./cxr_geochain.sh     ## look down into the bowl 
    GEOM=nmsk_solidMaskTail EYE=0.7,0.7,0.5 TMIN=0.0 ./cxr_geochain.sh     ## look down into the bowl 
    GEOM=hmsk_solidMask     EYE=0.7,0.7,-0.5 TMIN=0.0 ./cxr_geochain.sh    ## look up under the cap 
    GEOM=nmsk_solidMask     EYE=0.7,0.7,-0.5 TMIN=0.0 ./cxr_geochain.sh    ## look up under the cap 



hmsk_solidMask
----------------

Offsetting the G4Tubs makes a peaked cap, with the lower edge at same z : ie the ellipsoid and tubs low edge is at same z   


coincidence nudge for hmsk_solidMaskTail
-------------------------------------------

Lower part of the mask looks very much like a bowl with a thin lip edge::

    GEOM=hmsk_solidMaskTail EYE=0.5,0.5,0.3 ZOOM=2 ./X4MeshTest.sh


::

    epsilon:PMTSim blyth$ GEOM=hmsk_solidMaskTail GetSolidTest 

    PMTSim::GetSolid name hmsk_solidMaskTail zcut   999.0000
    ZSolid::Draw [-1] nameprefix hmskTail  NODE:11 PRIM:6 UNDEFINED:11 EXCLUDE:0 INCLUDE:0 MIXED:0 Order:IN

                                            Sub                                                     
                                            U                                                       
                                            5                                                       
                                                                                                    
                                                                                                    
                            Uni                                             Uni                     
                            U                                               U                       
                            3                                               9                       
                                                                                                    
                                                                                                    
            Uni                     Tub                     Uni                     Tub             
            U                       U                       U                       U               
            1                       4                       7                       10              
                                                                                                    
                                                                                                    
    Ell             Tub                             Ell             Tub                             
    U               U                               U               U                               
    0               2                               6               8                               
                                                                                                    
                                                                                                    
    0               -40             -116            0               -40             -112    zdelta  
                                                                                                    
    -40             -40             -40             -40             -40             -40     az1     
    -193            -40             -193            -185            -40             -185    az0     
    _outer  _outer  _outer  _outer  _outer          _inner  _inner  _inner  _inner  _inner          
    ZSolid::Draw
      0 :      hmskTail_outer_PartI_Ellipsoid :              _outer_PartI_Ellipsoid : [    _outer]
      1 :                hmskTail_outer_PartI :                        _outer_PartI : [    _outer]
      2 :           hmskTail_outer_PartI_Tube :                   _outer_PartI_Tube : [    _outer]
      3 :                      hmskTail_outer :                              _outer : [    _outer]
      4 :               hmskTail_outer_PartII :                       _outer_PartII : [    _outer]
      5 :                            hmskTail :                                     : [          ]
      6 :      hmskTail_inner_PartI_Ellipsoid :              _inner_PartI_Ellipsoid : [    _inner]
      7 :                hmskTail_inner_PartI :                        _inner_PartI : [    _inner]
      8 :           hmskTail_inner_PartI_Tube :                   _inner_PartI_Tube : [    _inner]
      9 :                      hmskTail_inner :                              _inner : [    _inner]
     10 :               hmskTail_inner_PartII :                       _inner_PartII : [    _inner]
    ZSolid::Draw
     ix  0 iy  3 idx  0 tag        Ell zcn          U zdelta      0.000 az0   -193.225 az1    -40.000 name hmskTail_outer_PartI_Ellipsoid
     ix  2 iy  3 idx  2 tag        Tub zcn          U zdelta    -40.150 az0    -40.300 az1    -40.000 name hmskTail_outer_PartI_Tube
     ix  4 iy  2 idx  4 tag        Tub zcn          U zdelta   -116.612 az0   -193.225 az1    -40.000 name hmskTail_outer_PartII
     ix  6 iy  3 idx  6 tag        Ell zcn          U zdelta      0.000 az0   -185.225 az1    -40.000 name hmskTail_inner_PartI_Ellipsoid
     ix  8 iy  3 idx  8 tag        Tub zcn          U zdelta    -40.150 az0    -40.300 az1   *-40.000 name hmskTail_inner_PartI_Tube*
     ix 10 iy  2 idx 10 tag        Tub zcn          U zdelta   -112.612 az0   -185.225 az1    -40.000 name hmskTail_inner_PartII
    epsilon:PMTSim blyth$ 



The part needing coincidence nudge is *hmskTail_inner_PartI_Tube* 

* need to increse its z1 from -40.0  -> -40.0 + uncoincide_z (eg  uncoincide_z = 1.*mm)
* but G4Tubs is symmetrically defined, so need to increase the size and and shift it upwards  

::

    460     // inner
    461 
    462     Tail_inner_I_Ellipsoid = new G4Ellipsoid(
    463             objName()+"Tail_inner_PartI_Ellipsoid",
    464             mask_radiu_in, // pxSemiAxis
    465             mask_radiu_in, // pySemiAxis
    466             htop_in,  // pzSemiAxis
    467             -(height_out+paramRealMaskTail.height-htop_thickness), // pzBottomCut (TODO)
    468             -height_out // pzTopCut
    469             );
    470 
    471     Tail_inner_I_Tube = new G4Tubs(
    472             objName()+"Tail_inner_PartI_Tube",
    473             0*mm,
    474             mask_radiu_in,
    475             paramRealMaskTail.edge_height/2,
    476             0*deg,
    477             360*deg);
    478 
    479     Tail_inner_I = new G4UnionSolid
    480         (objName()+"Tail_inner_PartI",
    481          Tail_inner_I_Ellipsoid ,
    482          Tail_inner_I_Tube ,
    483          0,
    484          G4ThreeVector(0,0,-(height_out+paramRealMaskTail.edge_height/2))) ;
    485 



Need to expand the tubs upwards without changing position of lower half, 
so grow outwards from *hz* to *new_hz* and shift upwards by *zoff*::


       +hz + uncoincide - - - - - - - +~~~~~~~~~+ - -    zoff + new_hz  - - -
                                      |         |
                                      |         |
       +hz  +---------+ - - - - - - - | - - - - | - - - - - - - - - - - - - -
            |         |               |         |  
            |         |               |         |
            |         |               |         |
            |         |               |_________|        zoff 
            |         |               |         |
        0 --|---------| - - - - - - - - - - - - - - - - - - - - - - - - - - -
            |         |               |         |
            |         |               |         |
            |         |               |         |                                
            |         |               |         |
            |         |               |         |
       -hz  +---------+ - - - - - - - +---------+ - - -  zoff - new_hz  - - -


Add the line equations::

      hz + uncoincide = zoff + new_hz

      -hz             = zoff - new_hz 

           => uncoincide = 2*zoff       =>   zoff = uncoincide/2


Subtract the line equations::
     
        2 hz + uncoincide = 2*new_hz    ==>  new_hz = hz + uncoincide/2 




Smoking gun found
--------------------

I think I found the cause of the unexpected mask intersects inside the PMT.    
From the below render you can see what looks like a subtraction coincidence.  
Probably the issue is that the shape being subtracted (inside of the bowl) 
has a coincident surface with the outside of the bowl. 


Opticks has automated coincidence prevention, but maybe that needs some
generalization to work with CSG trees of the form used by the mask.


GetSolidTest
...
ZSolid::Draw [-1] nameprefix hmskTail  NODE:11 PRIM:6 UNDEFINED:11 EXCLUDE:0 INCLUDE:0 MIXED:0 Order:IN

                                        Sub                                                     
                                        U                                                       
                                        5                                                       
                                                                                                
                                                                                                
                        Uni                                             Uni                     
                        U                                               U                       
                        3                                               9                       
                                                                                                
                                                                                                
        Uni                     Tub                     Uni                     Tub             
        U                       U                       U                       U               
        1                       4                       7                       10              
                                                                                                
                                                                                                
Ell             Tub                             Ell             Tub                             
U               U                               U               U                               
0               2                               6               8                               
                                                                                                
                                                                                                
0               -40             -116            0               -40             -112    zdelta  
                                                                                                
-40             -40             -40             -40             -40             -40     az1     
-193            -40             -193            -185            -40             -185    az0     
_outer  _outer  _outer  _outer  _outer          _inner  _inner  _inner  _inner  _inner          
ZSolid::Draw
  0 :      hmskTail_outer_PartI_Ellipsoid :              _outer_PartI_Ellipsoid : [    _outer]
  1 :                hmskTail_outer_PartI :                        _outer_PartI : [    _outer]
  2 :           hmskTail_outer_PartI_Tube :                   _outer_PartI_Tube : [    _outer]
  3 :                      hmskTail_outer :                              _outer : [    _outer]
  4 :               hmskTail_outer_PartII :                       _outer_PartII : [    _outer]
  5 :                            hmskTail :                                     : [          ]
  6 :      hmskTail_inner_PartI_Ellipsoid :              _inner_PartI_Ellipsoid : [    _inner]
  7 :                hmskTail_inner_PartI :                        _inner_PartI : [    _inner]
  8 :           hmskTail_inner_PartI_Tube :                   _inner_PartI_Tube : [    _inner]
  9 :                      hmskTail_inner :                              _inner : [    _inner]
 10 :               hmskTail_inner_PartII :                       _inner_PartII : [    _inner]
ZSolid::Draw
 ix  0 iy  3 idx  0 tag        Ell zcn          U zdelta      0.000 az0   -193.225 az1    -40.000 name hmskTail_outer_PartI_Ellipsoid
 ix  2 iy  3 idx  2 tag        Tub zcn          U zdelta    -40.150 az0    -40.300 az1    -40.000 name hmskTail_outer_PartI_Tube
 ix  4 iy  2 idx  4 tag        Tub zcn          U zdelta   -116.612 az0   -193.225 az1    -40.000 name hmskTail_outer_PartII
 ix  6 iy  3 idx  6 tag        Ell zcn          U zdelta      0.000 az0   -185.225 az1    -40.000 name hmskTail_inner_PartI_Ellipsoid
 ix  8 iy  3 idx  8 tag        Tub zcn          U zdelta    -40.150 az0    -40.300 az1    -40.000 name hmskTail_inner_PartI_Tube
 ix 10 iy  2 idx 10 tag        Tub zcn          U zdelta   -112.612 az0   -185.225 az1    -40.000 name hmskTail_inner_PartII
epsilon:PMTSim blyth$ 


I will try some manual coincidence avoidance tricks to see if I can 
get the bad intersects to go away.

Geant4 CSG is less sensitive to coincidence issues because it 
does everything in doubles. 




Explaining the issue prior to cause being known
-----------------------------------------------------------

https://simoncblyth.bitbucket.io/env/presentation/opticks_20211223_pre_xmas.html

All the 2D geometry cross section images on the pages 19-28 of my slides
are created using my cxs.sh script which is using the below executable and script

https://bitbucket.org/simoncblyth/opticks/src/master/CSGOptiX/tests/CSGOptiXSimulateTest.cc
https://bitbucket.org/simoncblyth/opticks/src/master/CSGOptiX/tests/CSGOptiXSimulateTest.py

The executable creates gensteps in a 2d planar grid which cause rays constrained
to the plane to be generated. The 6x4 of each genstep includes a 4x4 transforms 
which allows the rays to be generated into the local frame of any volume of the geometry. 
The first intersects of these planar rays are saved into the “photons” array and
persisted to .npy files. Together with intersect position identity information 
of which piece of geometry is hit is included. 
The python script then reads these .npy and makes scatter plots of the 
intersect positions using the identity info to makes the different colors
as shown in the key. 

This cross section visualization approach means that you are seeing actual 
intersects onto the geometry.  

https://simoncblyth.bitbucket.io/env/presentation/3dbec4dc3bdef47884fe48af781a179d/CSGOptiXSimulateTest/cvd0/70000/Hama_1/figs/positions_mpplt_pid.png

The p22 image linked above shows that there are intersects onto the Hama*Mask and Hama*Tail 
inside the volume of the PMT : the red dots within the cyan “line” shows
that there are actually two surfaces here. 

Of course you might also point out the blue line above between inner1 and inner2, 
but that one does not matter as it is a same material Vacuum-Vacuum boundary.   


The standard Geant4 visualization is using OpenGL to render triangles from a polygonization of the solids.  
The Hama*Mask and Hama*Tail have a coincident face which could explain why they are difficult 
to see with the OpenGL visualization. 


Visualization by looking at actual intersects positions is a much 
better way to test geometry.  So I also have scripts and executables to visualize 
using Geant4 intersects onto solids and volumes.  
   
    ~/opticks/extg4/xxs.sh 
    ~/opticks/extg4/tests/X4IntersectSolidTest.cc

    ~/opticks/extg4/xxv.sh 
    ~/opticks/extg4/tests/X4IntersectVolumeTest.cc  


Those are both based on X4Intersect

161 G4double X4Intersect::Distance(const G4VSolid* solid, const G4ThreeVector& pos, const G4ThreeVector& dir, bool dump ) // static
162 {
163     EInside in =  solid->Inside(pos) ;
164     G4double t = kInfinity ;
165     switch( in )
166     {
167         case kInside:  t = solid->DistanceToOut( pos, dir ) ; break ;
168         case kSurface: t = solid->DistanceToOut( pos, dir ) ; break ;
169         case kOutside: t = solid->DistanceToIn(  pos, dir ) ; break ;
170         default:  assert(0) ;
171     }

It is not impossible that the intersects onto the Mask and Tail 
within the PMT are due to a problem with the Opticks geometry translation. 
To try to work out what is happening I would start by using my xxs.sh and xxv.sh scripts 
to visualize the Geant4 geometry using its intersects.



