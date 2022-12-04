junoPMTOpticalModelSimple_in_customized_G4OpBoundaryProcess
=============================================================

Motivation
-------------

Not certain yet, but I suspect that FastSim might not be usable with a very simple 
single surface geometry : because cannot stop ordinary G4OpBoundaryProcess
stepping in. 

The objective is just to change the A-R-T of a surface : so using FastSim 
to do that is actually not such a good fit. Making it fit is 
maybe the reason for the same material fake boundaries. 

So customizing u4/InstrumentedG4OpBoundaryProcess would seem like 
a natural place to do this.  


What about implementing the model in customized G4OpBoundaryProcess, instead of using FastSim ?
----------------------------------------------------------------------------------------------------

* advantage is that can use standard machinery for reflection and refraction (esp polarization)

  * just need to conditionally override calculation of ARTD coefficients to use the stack calc

* how to switch it on for local_z > 0 ? 

  * via having a G4OpticalSurface associated with the boundary that has some string in the name like "__junoPMTOpticalModel__" 
  * OR could be via existence of a set of properties in the MPT RINDEX_L1,KINDEX_L1

* complexity is that need pmtid (to give _qe) and pmtcat to give thicknesses and refractive indices

  * HMM: G4OpticalSurface has G4MaterialPropertiesTable so could provide RINDEX+KINDEX and thickness of ARC and PHC 
  * HMM: could stuff the _qe into a property vector : mis-using the energy domain as pmtid  
  
* then need to extend InstrumentedG4OpBoundaryProcess::DielectricDielectric 
  which normally does 2-material R/T to instead do R/T/A/D 

u4/InstrumentedG4OpBoundaryProcess.cc::


     403         G4LogicalSurface* Surface = NULL;
     404 
     405         Surface = G4LogicalBorderSurface::GetSurface(thePrePV, thePostPV);
     406 
     407 //#ifdef DEBUG_PIDX
     408         //std::cout << "InstrumentedG4OpBoundaryProcess::PostStepDoIt Surface " << ( Surface ? "Y" : "N" ) << std::endl ; 
     409         //if(Surface) std::raise(SIGINT) ; 
     410 //#endif
     411 
     412 
     413         if (Surface == NULL){
     414           G4bool enteredDaughter= (thePostPV->GetMotherLogical() ==
     415                                    thePrePV ->GetLogicalVolume());
     416       if(enteredDaughter){
     417         Surface =
     418               G4LogicalSkinSurface::GetSurface(thePostPV->GetLogicalVolume());
     419         if(Surface == NULL)
     420           Surface =
     421                 G4LogicalSkinSurface::GetSurface(thePrePV->GetLogicalVolume());
     422       }
     423       else {
     424         Surface =
     425               G4LogicalSkinSurface::GetSurface(thePrePV->GetLogicalVolume());
     426         if(Surface == NULL)
     427           Surface =
     428                 G4LogicalSkinSurface::GetSurface(thePostPV->GetLogicalVolume());
     429       }
     430     }
     431
     432         if (Surface) OpticalSurface =
     433            dynamic_cast <G4OpticalSurface*> (Surface->GetSurfaceProperty());
     434 
     435         if (OpticalSurface) {
     436 
     437            type      = OpticalSurface->GetType();
     438            theModel  = OpticalSurface->GetModel();
     439            theFinish = OpticalSurface->GetFinish();
     440 
     441            aMaterialPropertiesTable = OpticalSurface->
     442                                         GetMaterialPropertiesTable();
     443 



Getting acquainted
-------------------

::

    In [1]: uu = t.U4Recorder_G4StateRerun_726

    In [2]: uu[:10]
    Out[2]: array([0.872, 0.625, 0.792, 0.943, 0.194, 0.101, 0.347, 0.398, 0.986, 0.942])

::

    U4PMTFastSimTest::BeamOn@42: U4UniformRand::Desc
         0    0.13049
         1    0.61775
         2    0.99595
         3    0.49590
         4    0.11292
         5    0.28987
         6    0.47304
         7    0.83762
         8    0.35936
         9    0.92694



    U4Engine::DescStateArray

    state = np.array([ 
    2888826676, 353482723, 130506889, 1116636468, 243326789, 913214171, 264080965, 1143869688, 52046569, 4072241841, 
    3581138, 2255342921, 74600254, 62127458, 23647093, 4114481141, 236367991, 397407612, 157777808, 420466572, 
    155182832, 756200498, 293007582, 3123446104, 74820627, 2127040698, 262440231, 4231485520, 446450517, 2275155686, 
    314373770, 1344302897, 333054943, 3124239389, 28366213, 5, 1766370320, 409277658 ], dtype=np.uint64 )

     rerun_rand 
    {   0.87237    0.62535    0.79217    0.94347    0.19391 ...    0.45323    0.49189    0.09694    0.00667 }
    U4Recorder::PreUserTrackingAction_Optical@227: ]


After rerun::

    U4Recorder::EndOfEventAction@95: 
    U4Recorder::EndOfRunAction@93: 
    U4PMTFastSimTest::BeamOn@42: U4UniformRand::Desc
         0    0.23041
         1    0.92902
         2    0.12271
         3    0.95757
         4    0.57763
         5    0.10686
         6    0.66933
         7    0.87154
         8    0.33823
         9    0.34132

    In [6]: np.where( np.abs( uu - 0.23041 ) < 1e-5 )
    Out[6]: (array([78]),)

    In [7]: uu[77:87]
    Out[7]: array([0.163, 0.23 , 0.929, 0.123, 0.958, 0.578, 0.107, 0.669, 0.872, 0.338])

    In [8]: np.set_printoptions(precision=6)

    In [9]: uu[77:87]
    Out[9]: array([0.163458, 0.230408, 0.929016, 0.122712, 0.95757 , 0.577633, 0.106861, 0.669328, 0.871536, 0.338231])


So the ~20 step points of the rerun consumed ~78 u (avg ~4 per point)


Before rerun, not starting at expectation. Thats because the g4state reset not yet done::

    epsilon:tests blyth$ BeamOn=-1 ./U4PMTFastSimTest.sh 

    U4PMTFastSimTest::BeamOn@42: U4UniformRand::Desc
         0    0.13049
         1    0.61775
         2    0.99595
         3    0.49590
         4    0.11292
         5    0.28987
         6    0.47304
         7    0.83762
         8    0.35936
         9    0.92694



::

    epsilon:tests blyth$ grep ResetNumberOfInteractionLengthLeft *.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.872371
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.101369
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.351664
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.877615
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.038024
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.497643
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.490044
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.437493
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.018568
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.456924
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.328085
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.751191
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.859019
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.645412
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.501576
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.854555
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.663337
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.502386
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.448201
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@127:  u   0.672622

    In [14]: uu[:40].reshape(-1,5)  ## first 2 points consumed 5u
    Out[14]: 
    array([[0.872371, 0.625351, 0.792168, 0.943474, 0.19391 ],
           [0.101369, 0.347062, 0.397885, 0.98594 , 0.941896],
           [0.351664, 0.201621, 0.433664, 0.877615, 0.457637],
           [0.776891, 0.774611, 0.038024, 0.537972, 0.505659],
           [0.497643, 0.548503, 0.205443, 0.005939, 0.490044],
           [0.914878, 0.766359, 0.437493, 0.028126, 0.493141],
           [0.339021, 0.619328, 0.743584, 0.011179, 0.018568],
           [0.073415, 0.994039, 0.456924, 0.684105, 0.966989]])



Keep track of position in random stream when rerunning using U4UniformRand::Desc.

Checking with the big bouncer (export hama_UseNaturalGeometry=0)::

    epsilon:tests blyth$ grep Reset *.log 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.87237      0]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.10137      5]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.35166     10]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.87761     13]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.03802     17]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.49764     20]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.49004     24]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.43749     27]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.01857     34]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.45692     37]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.32809     41]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.75119     44]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.85902     48]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.64541     51]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.50158     55]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.85455     58]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.66334     63]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.50239     66]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.44820     70]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: [0.67262     73]
    epsilon:tests blyth$ 


When (export hama_UseNaturalGeometry=1) get very different::

    epsilon:tests blyth$ grep UU *.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: UU[0.87237      0]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@656: didi.rand UU[0.94347      3]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: UU[0.10137      5]
    epsilon:tests blyth$ 









The old big bouncer::

    In [4]: t.record[726].reshape(-1,16)                                                                                                                                             
    Out[4]: 
    0 ###([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.  #0 
    1 ###  [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.  #1 
    2      [-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.  #2 
    3      [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.  #3 
    4 ###  [-135.824,    0.   ,    0.   ,    1.012,   -0.138,    0.   ,   -0.99 ,    0.   
    5      [-156.577,    0.   , -148.846,    1.778,    0.81 ,    0.   ,    0.587,    0.   
    6      [ -95.   ,    0.   , -104.211,    2.166,   -0.81 ,    0.   ,    0.587,    0.   
    7      [-238.764,    0.   ,   -0.   ,    3.071,   -0.81 ,    0.   ,    0.587,    0.   
    8      [-248.807,    0.   ,    7.28 ,    3.112,    0.867,    0.   ,    0.498,    0.   
    9      [  53.205,    0.   ,  180.727,    4.274,    0.665,    0.   ,   -0.747,    0.   
    10 ### [ 214.06 ,    0.   ,    0.   ,    5.507,    0.665,    0.   ,   -0.747,    0.   
    11     [ 245.605,    0.   ,  -35.443,    5.749,   -0.92 ,    0.   ,   -0.391,    0.   
    12     [  95.   ,    0.   ,  -99.428,    6.583,    0.92 ,    0.   ,   -0.391,    0.   
    13     [ 177.724,    0.   , -134.574,    7.041,   -0.127,    0.   ,    0.992,    0.   
    14 ??? [ 160.533,    0.   ,    0.   ,    7.732,   -0.127,    0.   ,    0.992,    0.   
    15     [ 141.059,    0.   ,  152.451,    8.245,   -0.878,    0.   ,   -0.479,    0.   
    16 ### [-138.46 ,    0.   ,    0.   ,    9.867,   -0.878,    0.   ,   -0.479,    0.   
    17     [-239.66 ,    0.   ,  -55.195,   10.455,    0.975,    0.   ,    0.224,    0.   
    18     [   0.427,    0.   ,    0.   ,   11.71 ,    0.975,    0.   ,    0.224,    0.   
    19 ### [ 237.91 ,    0.   ,   54.596,   12.523,    0.975,    0.   ,    0.224,    0.   
    20     [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.


    rerun_rand (about to be consumed, did RestoreState after collecting them)  
    {   0.87237    0.62535    0.79217    0.94347    0.19391 ...    0.45323    0.49189    0.09694    0.00667 }

    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: UU[0.87237      0]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@656: didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    U4Recorder::UserSteppingAction_Optical@475: U4StepPoint::DescPositionTime (   -113.000      0.000    170.163      0.137)
    U4Recorder::Check_TrackStatus_Flag@513:  step.tstat fAlive BOUNDARY_TRANSMIT from UserSteppingAction_Optical

    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@130: UU[0.10137      5]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@474: U4OpticalSurface::Desc _Photocathode_opsurf type:dielectric_metal model:glisur finish:polished polish:1
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@487: U4MaterialPropertiesTable::Desc
    DescPropertyMap  miv.size 6 v0 [ 0x7f8afc3021c0 0x7f8afc302550 0x7f8afc3028c0 0x7f8afc301d30 0x7f8afc302400 0x7f8afc302630 ] i [0 1 4 9 23 24] n [RINDEX REFLECTIVITY EFFICIENCY GROUPVEL KINDEX THICKNESS] v [0x7f8afc3021c0 0x7f8afc302550 0x7f8afc3028c0 0x7f8afc301d30 0x7f8afc302400 0x7f8afc302630 vl [4 4 2 4 4 2]
    DescConstPropertyMap  mif.size 0

    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@514:  PropertyPointer.kREFLECTIVITY 0x7f8afc302550 PropertyPointer1.kREALRINDEX 0x0 PropertyPointer2.kIMAGINARYRINDEX 0x0
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@549:  theReflectivity 0 theEfficiency 1 theTransmittance 0
    U4Recorder::UserSteppingAction_Optical@417: [ pv _log_pv
    U4Recorder::UserSteppingAction_Optical@475: U4StepPoint::DescPositionTime (   -112.830      0.000    164.917      0.164)

    ## YEP : ITS THE EXPECTED POSITION : NEED TO CHANGE OUTCOME : POINT #3 IN ABOVE BIG BOUNCER ARRAY

    U4Recorder::Check_TrackStatus_Flag@513:  step.tstat fStopAndKill SURFACE_DETECT from UserSteppingAction_Optical
    U4Recorder::UserSteppingAction_Optical@499: ]
    U4Recorder::PostUserTrackingAction@97: 
    U4Recorder::PostUserTrackingAction_Optical@326: [
    U4Recorder::PostUserTrackingAction_Optical@329: fStopAndKill
    U4Recorder::PostUserTrackingAction_Optical@352:  label.id   726 seq.desc_seqhis                 0              7cd nib  3 TO BT SD
    U4Recorder::PostUserTrackingAction_Optical@366: ]
    U4Recorder::EndOfEventAction@95: 
    U4Recorder::EndOfRunAction@93: 



Comparing FastSim bigbouncer with CustomART shoe horned into InstrumentedG4OpBoundaryProcess
-----------------------------------------------------------------------------------------------


U4PMTFastSimTest.sh::

     26 ## u4/tests/U4PMTFastSimTest.cc
     27 export BeamOn=${BeamOn:-1}
     28 
     29 ## PMTFastSim/HamamatsuR12860PMTManager declProp config 
     30 export hama_FastCoverMaterial=Cheese
     31 export hama_UsePMTOpticalModel=1
     32 export hama_UseNaturalGeometry=0  ## 0:FastSim/jPOM 1:InstrumentedG4OpBoundaryProcess/CustomART
     33 
     34 case $hama_UseNaturalGeometry in
     35   0) echo FastSim/jPOM ;;
     36   1) echo InstrumentedG4OpBoundaryProcess/CustomART ;;
     37 esac
     38 
     39 #running_mode=SRM_G4STATE_SAVE  
     40 running_mode=SRM_G4STATE_RERUN
     41 
     42 case $running_mode in
     43    SRM_G4STATE_SAVE)  reldir=ALL ;;
     44    SRM_G4STATE_RERUN) reldir=SEL$hama_UseNaturalGeometry ;;
     45 esac
     46 




Refract formula needed flip of oriented normal
-------------------------------------------------

::

   u4t
   ./U4PMTFastSimTest.sh    
   ./U4PMTFastSimTest.sh cf   # compare SEL0 and SEL1   

Transmission direction, clear discrepancy::

    In [14]: a.record[PID,:4,:3].reshape(-1,12)
    Out[14]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ]], dtype=float32)

    In [15]: b.record[PID,:4,:3].reshape(-1,12)
    Out[15]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,    0.118,    0.   ,   -0.993,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [ -82.608,    0.   ,  -90.   ,    1.02 ,    0.118,    0.   ,   -0.993,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ]], dtype=float32)


    In [16]: aa = a.record[PID]
    In [17]: bb = b.record[PID]

    In [22]: np.all( aa[0] == bb[0] )   ## generation point is same
    Out[22]: True

    In [23]: np.all( aa[1] == bb[1] )   ## Water/Pyrex point is same 
    Out[23]: True

    ## aa[2] is the Fake border point, not present in bb 

    In [33]: (aa[3,0] - bb[2,0])*1e9    ## Pyrex/Vacuum point same position, slightly different time 
    Out[33]: array([   0.   ,    0.   ,    0.   , -149.012], dtype=float32)


     92 junoPMTOpticalModel::UpdateTrackInfo@556:
     93 junoPMTOpticalModel::Refract@720:  time 0.163593 pos (-112.83,0,164.917) norm (0.353306,-0,-0.935508)
     ## HUH: thats an inwards pointing normal 

     94 junoPMTOpticalModel::Refract@725:  _n1 1.48426 _n4 1 _cos_theta1 0.94647 _cos_theta4 (0.877756,0)
     95 junoPMTOpticalModel::Refract@732:  bef  dir (0.0324194,0,-0.999474) pol (0,-1,0)
     96 junoPMTOpticalModel::Refract@743:  aft  dir (-0.138093,0,-0.990419) pol (0,-1,0)
     97 junoPMTOpticalModel::UpdateTrackInfo@556:

    ## flipped norm ? 
    ## refraction bends towards the normal when entering higher index material 
    ## refraction bends away from  normal  when entering lower index material 


    InstrumentedG4OpBoundaryProcess::CustomART@996:  time 0.163593 pos (-112.83,0,164.917) norm (-0.353306,0,0.935508)
    ## outwards normal 
    InstrumentedG4OpBoundaryProcess::CustomART@1001:  _n0 1.48426 _n3 1 _cos_theta0 0.94647 _cos_theta3 0.877757
    InstrumentedG4OpBoundaryProcess::CustomART@1008:  bef  dir (0.0324194,0,-0.999474) pol (0,-1,0)
    InstrumentedG4OpBoundaryProcess::CustomART@1018:  aft  dir (0.23433,0,-1.97654) pol (0,-1,0)
    InstrumentedG4OpBoundaryProcess::CustomART@1026:  status T


    In [34]: aa[3,1]   ## A: goes left 
    Out[34]: array([-0.138,  0.   , -0.99 ,  0.   ], dtype=float32)

    In [35]: bb[2,1]   ## B: goes right       thats not a consumption difference : MUST BE BUG 
    Out[35]: array([ 0.118,  0.   , -0.993,  0.   ], dtype=float32)



Trying to keep the consumption aligned
-----------------------------------------

::

    u4t
    N=0 ./U4PMTFastSimTest.sh 
    N=1 ./U4PMTFastSimTest.sh 

    grep UU U4PMTFastSimTest_0.log
    grep UU U4PMTFastSimTest_1.log


    epsilon:tests blyth$ grep UU U4PMTFastSimTest_0.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.87237      0]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@739:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.10137      5]
    junoPMTOpticalModel::DoIt@493:  time 0.163593 dbg.Count 0 dbg.Name A_SPhoton_Debug.npy u0 UU[0.98594      8] u1 UU[0.94190      9] u0_idx 8
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.35166     10]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.87761     13]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1231:  PostStepDoIt_count 3 do-while n 1 rand UU[0.77461     16] theReflectivity 0.92 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.03802     17]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.49764     20]




    epsilon:tests blyth$ grep UU U4PMTFastSimTest_1.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.87237      0]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@739:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.10137      5]
    InstrumentedG4OpBoundaryProcess::CustomART@1081:  time 0.163593 dbg.Count 0 dbg.Name B_SPhoton_Debug.npy u0 UU[0.98594      8] u1 UU[0.94190      9] u0_idx 8
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@134: UU[0.35166     10]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1231:  PostStepDoIt_count 2 do-while n 1 rand UU[0.87761     13] theReflectivity 0 theTransmittance 0
    epsilon:tests blyth$ 




    epsilon:tests blyth$ grep UU *_1.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.87237      0] u_idx 0
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@755:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.10137      5] u_idx 5
    InstrumentedG4OpBoundaryProcess::CustomART@1099:  time 0.163593 dbg.Count 0 dbg.Name B_SPhoton_Debug.npy u0 UU[0.98594      8] u1 UU[0.94190      9] u0_idx 8
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.35166     10] u_idx 10
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@143: UU[0.87761     13] after uu_burn 3 for u_idx 10
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1250:  PostStepDoIt_count 2 do-while n 1 rand UU[0.77461     16] theReflectivity 0 theTransmittance 0



Appluying UU_BURN to keep aligned further
--------------------------------------------

Fixing UU_BURN machinery, still only with only one shunt::

   a = np.array( [[10,3]], dtype=np.int32 ) 

Plus changing to m_mirror_opsurf gets further matched
(in old numbering gets to point 8 with matched positions, 
but see time difference starting from point 5[old]::

    u4t
    ./U4PMTFastSimTest.sh ncf


    In [9]: a.record[726,:10,:3].reshape(-1,12)
    Out[9]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
        #1 [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #2 [-112.83 ,    0.   ,  164.918,    0.164,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #3 [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #4 [-135.824,    0.   ,    0.   ,    1.012,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #5 [-156.577,    0.   , -148.846,   *1.778*,   0.81 ,    0.   ,    0.587,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
        #6 [ -95.   ,    0.   , -104.211,    2.166,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #7 [-238.764,    0.   ,   -0.   ,    3.071,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
        #8 [-248.807,    0.   ,    7.28 ,    3.112,    0.867,    0.   ,    0.498,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [  53.205,    0.   ,  180.727,    4.274,    0.665,    0.   ,   -0.747,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ]], dtype=float32)

    In [10]: b.record[726,:10,:3].reshape(-1,12)
    Out[10]: 
    array([[-113.   ,    0.   ,  200.   ,    0.   ,    0.   ,    0.   ,   -1.   ,    0.   ,   -0.   ,   -1.   ,   -0.   ,  420.   ],
           [-113.   ,    0.   ,  170.163,    0.137,    0.032,    0.   ,   -0.999,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-112.83 ,    0.   ,  164.917,    0.164,   -0.138,    0.   ,   -0.99 ,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-156.577,    0.   , -148.846,   *1.22*,    0.81 ,    0.   ,    0.587,    0.   ,    0.   ,    1.   ,    0.   ,  420.   ],
           [ -95.   ,    0.   , -104.211,    1.474,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [-248.807,    0.   ,    7.28 ,    2.108,   -0.81 ,    0.   ,    0.587,    0.   ,    0.   ,   -1.   ,    0.   ,  420.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ],
           [   0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ,    0.   ]], dtype=float32)

    In [11]:                                            



::

    epsilon:tests blyth$ grep UU *_0.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.87237      0] u_idx 0
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@755:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.10137      5] u_idx 5
    junoPMTOpticalModel::DoIt@462:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T
    junoPMTOpticalModel::DoIt@471:  u1 UU[0.94190      9] u1_idx 9 D     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.35166     10] u_idx 10
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.87761     13] u_idx 13
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1262:  PostStepDoIt_count 3 do-while n 1 rand UU[0.77461     16] theReflectivity 0.92 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.03802     17] u_idx 17
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.49764     20] u_idx 20
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1262:  PostStepDoIt_count 5 do-while n 1 rand UU[0.00594     23] theReflectivity 0.65 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.49004     24] u_idx 24
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.43749     27] u_idx 27

    junoPMTOpticalModel::DoIt@462:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R
    junoPMTOpticalModel::DoIt@471:  u1 UU[0.61933     31] u1_idx 31 D     0.0000

    junoPMTOpticalModel::DoIt@462:  u0 UU[0.74358     32] u0_idx 32 A     0.2341 A+R     0.7652 T     0.2348 status R
    junoPMTOpticalModel::DoIt@471:  u1 UU[0.01118     33] u1_idx 33 D     0.0000

    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.01857     34] u_idx 34
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.45692     37] u_idx 37
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1262:  PostStepDoIt_count 9 do-while n 1 rand UU[0.76067     40] th



    epsilon:tests blyth$ grep UU *_1.log
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.87237      0] u_idx 0
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@755:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.10137      5] u_idx 5
    InstrumentedG4OpBoundaryProcess::CustomART@1026:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T
    InstrumentedG4OpBoundaryProcess::CustomART@1035:  u1 UU[0.94190      9] u1_idx 9 D     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.35166     10] u_idx 10
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@143: UU[0.87761     13] after uu_burn 3 for u_idx 10
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1262:  PostStepDoIt_count 2 do-while n 1 rand UU[0.77461     16] theReflectivity 0.92 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.03802     17] u_idx 17
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.49764     20] u_idx 20
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1262:  PostStepDoIt_count 4 do-while n 1 rand UU[0.00594     23] theReflectivity 0.65 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.49004     24] u_idx 24
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@137: UU[0.43749     27] u_idx 27
    InstrumentedG4OpBoundaryProcess::CustomART@1026:  u0 UU[0.33902     30] u0_idx 30 A     0.7357 A+R     0.7766 T     0.2234 status A
    InstrumentedG4OpBoundaryProcess::CustomART@1035:  u1 UU[0.61933     31] u1_idx 31 D     0.0000
    epsilon:tests blyth$ 


* A higher in 1 than 0 



0::


    junoPMTOpticalModel::CalculateCoefficients@645:  DoIt_count 1 stack crossheck Stack<double,4>
    idx 0
    Layr
      n:(    1.0000     0.0000)s  d:    0.0000
     st:(    0.5432     0.0000)s ct:(    0.8396    -0.0000)s
     rs:(   -0.5509    -0.2104)s rp:(    0.4119     0.2305)s
     ts:(    0.4491    -0.2104)s tp:(    0.4944    -0.2046)s
    S
    | (    1.0000     0.0000)s (    0.0000     0.0000)s |
    | (    0.0000     0.0000)s (    1.0000     0.0000)s |

    P
    | (    1.0000     0.0000)s (    0.0000     0.0000)s |
    | (    0.0000     0.0000)s (    1.0000     0.0000)s |

    idx 1
    Layr
      n:(    2.2735     1.4071)s  d:   21.1300
     st:(    0.1728    -0.1069)s ct:(    0.9909     0.0186)s
     rs:(    0.1888     0.2849)s rp:(   -0.1537    -0.2682)s
     ts:(    1.1888     0.2849)s tp:(    1.1856     0.2993)s
    S
    | (    3.0642    -0.8338)s (   -0.0483    -0.7536)s |
    | (   -1.8637    -0.1854)s (    0.5324     1.1646)s |

    P
    | (    2.8016    -0.9019)s (   -0.0199     0.5598)s |
    | (    1.3619     0.2742)s (    0.5423     1.0556)s |

    idx 2
    Layr
      n:(    1.9413     0.0000)s  d:   36.4900
     st:(    0.2798     0.0000)s ct:(    0.9601     0.0000)s
     rs:(    0.1487     0.0000)s rp:(   -0.1181     0.0000)s
     ts:(    1.1487     0.0000)s tp:(    1.1535     0.0000)s
    S
    | (    0.2559    -0.7770)s (   -0.0547     0.2742)s |
    | (    0.2697    -0.0738)s (    0.5803     0.5766)s |

    P
    | (    0.2465    -0.7798)s (    0.0625    -0.2450)s |
    | (   -0.2471     0.0537)s (    0.5870     0.5694)s |

    idx 3
    Layr
      n:(    1.4843     0.0000)s  d:    0.0000
     st:(    0.3660     0.0000)s ct:(    0.9306     0.0000)s
     rs:(    0.0000     0.0000)s rp:(    0.0000     0.0000)s
     ts:(    0.0000     0.0000)s tp:(    0.0000     0.0000)s
    S
    | (    0.8706     0.0000)s (    0.1294     0.0000)s |
    | (    0.1294     0.0000)s (    0.8706     0.0000)s |

    P
    | (    0.8670     0.0000)s (   -0.1024     0.0000)s |
    | (   -0.1024     0.0000)s (    0.8670     0.0000)s |

    comp
    Layr
      n:(    0.0000     0.0000)s  d:    0.0000
     st:(    0.0000     0.0000)s ct:(    0.0000     0.0000)s
     rs:(   -0.6458    -0.1223)s rp:(    0.5206     0.1486)s
     ts:(    0.0211     0.4195)s tp:(    0.0012     0.4621)s
    S
    | (    0.1194    -2.3778)s (    0.4157     0.0046)s |
    | (   -0.3679     1.5209)s (   -0.2332     0.6364)s |

    P
    | (    0.0055    -2.1640)s (   -0.3223    -0.1081)s |
    | (    0.3244    -1.1256)s (   -0.1498     0.6561)s |


    ART_
     R_s     0.4320 R_p     0.2931
     T_s     0.2903 T_p     0.3513
     A_s     0.2778 A_p     0.3556
     R       0.3625 T       0.3208 A       0.3167 A_R_T     1.0000
     wl    420.0000
     mct    -0.8396   ## SHOULD BE +VE ? 


    junoPMTOpticalModel::DoIt@397:  DoIt_count 1 _sin_theta1    0.54322 norm (-0.99860,0.00000,0.05293) pol*dir.cross(norm)    0.54322 E_s2    1.00000


    junoPMTOpticalModel::DoIt@397:  DoIt_count 1 _sin_theta1    0.54322 norm (-0.99860,0.00000,0.05293) pol*dir.cross(norm)    0.54322 E_s2    1.00000
    junoPMTOpticalModel::DoIt@431:  DoIt_count 1 E_s2    1.00000 fT_s    0.29025 1-E_s2   -0.00000 fT_p    0.35132 T    0.29025
    junoPMTOpticalModel::DoIt@440:  DoIt_count 1 E_s2    1.00000 fR_s    0.43197 1-E_s2   -0.00000 fR_p    0.29305 R    0.43197 A    0.27778
    junoPMTOpticalModel::DoIt@495:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R
    junoPMTOpticalModel::DoIt@504:  u1 UU[0.61933     31] u1_idx 31 D     0.0000
    junoPMTOpticalModel::UpdateTrackInfo@636: 





1::


    InstrumentedG4OpBoundaryProcess::CustomART@987:  CustomART_count 1 stack Stack<double,4>
    idx 0
    Layr
      n:(    1.4843     0.0000)s  d:    0.0000            ## THATS WRONG : AS ARE IN VACUUM HERE 
     st:(    0.5432     0.0000)s ct:(    0.8396    -0.0000)s
     rs:(   -0.1726     0.0000)s rp:(    0.0939     0.0000)s
     ts:(    0.8274     0.0000)s tp:(    0.8363     0.0000)s
    S
    | (    1.0000     0.0000)s (    0.0000     0.0000)s |
    | (    0.0000     0.0000)s (    1.0000     0.0000)s |

    P
    | (    1.0000     0.0000)s (    0.0000     0.0000)s |
    | (    0.0000     0.0000)s (    1.0000     0.0000)s |

    idx 1
    Layr
      n:(    1.9413     0.0000)s  d:   36.4900
     st:(    0.4153     0.0000)s ct:(    0.9097     0.0000)s
     rs:(   -0.2131    -0.2946)s rp:(    0.1298     0.2576)s
     ts:(    0.7869    -0.2946)s tp:(    0.7959    -0.2727)s
    S
    | (    0.6891    -0.9928)s (   -0.1189    -0.1713)s |
    | (   -0.1189     0.1713)s (    0.6891     0.9928)s |

    P
    | (    0.6818    -0.9823)s (    0.0640     0.0922)s |
    | (    0.0640    -0.0922)s (    0.6818     0.9823)s |

    idx 2
    Layr
      n:(    2.2735     1.4071)s  d:   21.1300
     st:(    0.2564    -0.1587)s ct:(    0.9804     0.0415)s
     rs:(    0.6666     0.1779)s rp:(   -0.2493    -0.2464)s
     ts:(    1.6666     0.1779)s tp:(    2.0533     0.4960)s
    S
    | (    1.7953    -0.6106)s (    0.1103    -0.2482)s |
    | (   -0.5624    -0.3989)s (    0.3753     0.6457)s |

    P
    | (    1.7751    -0.6601)s (   -0.1123     0.1835)s |
    | (    0.4003     0.3715)s (    0.3928     0.6341)s |

    idx 3
    Layr
      n:(    1.0000     0.0000)s  d:    0.0000
     st:(    0.8063     0.0000)s ct:(    0.5915     0.0000)s
     rs:(    0.0000     0.0000)s rp:(    0.0000     0.0000)s
     ts:(    0.0000     0.0000)s tp:(    0.0000     0.0000)s
    S
    | (    0.5933    -0.0633)s (    0.4067     0.0633)s |
    | (    0.4067     0.0633)s (    0.5933    -0.0633)s |

    P
    | (    0.4602    -0.1112)s (   -0.1421    -0.0857)s |
    | (   -0.1421    -0.0857)s (    0.4602    -0.1112)s |

    comp
    Layr
      n:(    0.0000     0.0000)s  d:    0.0000
     st:(    0.0000     0.0000)s ct:(    0.0000     0.0000)s
     rs:(   -0.0764    -0.1871)s rp:(   -0.1028     0.1422)s
     ts:(    0.1070     0.6777)s tp:(    0.0286     0.9137)s
    S
    | (    0.2273    -1.4397)s (    0.2979    -1.0413)s |
    | (   -0.2868     0.0675)s (   -0.1668     0.3455)s |

    P
    | (    0.0342    -1.0934)s (   -0.1943     0.3916)s |
    | (    0.1520     0.1173)s (   -0.0221     0.3658)s |


    ART_
     R_s     0.0408 R_p     0.0308
     T_s     0.2234 T_p     0.3966
     A_s     0.7357 A_p     0.5726
     R       0.0358 T       0.3100 A       0.6541 A_R_T     1.0000
     wl    420.0000
     mct    -0.8396


    InstrumentedG4OpBoundaryProcess::CustomART@999:  CustomART_count 1 _sin_theta0    0.54322 oriented_normal (0.99860,0.00000,-0.05293) polarization*direction.cross(oriented_normal) -0.54322 E_s2    1.00000
    InstrumentedG4OpBoundaryProcess::CustomART@1018:  CustomART_count 1 E_s2    1.00000 fT_s    0.22343 1-E_s2    0.00000 fT_p    0.39663 T    0.22343
    InstrumentedG4OpBoundaryProcess::CustomART@1027:  CustomART_count 1 E_s2    1.00000 fR_s    0.04085 1-E_s2    0.00000 fR_p    0.03080 R    0.04085 A    0.73572




    InstrumentedG4OpBoundaryProcess::CustomART@991:  CustomART_count 1 _sin_theta0    0.54322 oriented_normal (0.99860,0.00000,-0.05293) polarization*direction.cross(oriented_normal) -0.54322 E_s2    1.00000
    InstrumentedG4OpBoundaryProcess::CustomART@1010:  CustomART_count 1 E_s2    1.00000 fT_s    0.22343 1-E_s2    0.00000 fT_p    0.39663 T    0.22343
    InstrumentedG4OpBoundaryProcess::CustomART@1019:  CustomART_count 1 E_s2    1.00000 fR_s    0.04085 1-E_s2    0.00000 fR_p    0.03080 R    0.04085 A    0.73572
    InstrumentedG4OpBoundaryProcess::CustomART@1057:  u0 UU[0.33902     30] u0_idx 30 A     0.7357 A+R     0.7766 T     0.2234 status A
    InstrumentedG4OpBoundaryProcess::CustomART@1066:  u1 UU[0.61933     31] u1_idx 31 D     0.0000

* transmission different, reflection much less 


Problem is that theGlobalNormal is not pointing outwards, as I assumed. It seems to not be rigidly defined 
according to the geometry : which Opticks needs.   


After established reliable orientation 
-----------------------------------------

After establishing the orientation based on "outwards = localNormal.z() > 0." 
manage to reproduce the bounces of the big bounder, but it goes beyond.


::

     902 char InstrumentedG4OpBoundaryProcess::CustomART(const G4Track& aTrack, const G4Step& aStep )
     903 {
     904     const G4AffineTransform& transform = aTrack.GetTouchable()->GetHistory()->GetTopTransform();
     905     
     906     G4ThreeVector localPoint  = transform.TransformPoint(theGlobalPoint);
     907     G4ThreeVector localNormal = transform.TransformAxis(theGlobalNormal);
     908     G4ThreeVector localMomentum = transform.TransformAxis(OldMomentum);
     909     G4ThreeVector localPolarization = transform.TransformAxis(OldPolarization);
     910     
     911     G4double z_local = localPoint.z() ;
     912     if( z_local < 0. ) return 'Z' ;
     913     
     914     bool outwards = localNormal.z() > 0. ; // as always upper hemi of PMT in local frame  
     915     G4ThreeVector surface_normal = (outwards ? 1. : -1.)*localNormal ;
     916     const G4ThreeVector& direction      = localMomentum ; 
     917     const G4ThreeVector& polarization   = localPolarization ;
     918     
     919     G4double minus_cos_theta = direction*surface_normal  ; 
     920     G4ThreeVector oriented_normal = ( minus_cos_theta < 0. ? 1. : -1. )*surface_normal ;
     921 


This match must be "by accident" because the UU_BURN still has only one shunt. 



Record the u0 and u0_idx in SPhoton_Debug
---------------------------------------------

::

    In [7]: aa[:,4,3].view(np.uint64)
    Out[7]: array([ 5, 27, 27, 58, 73], dtype=uint64)

    In [9]: aa[:,4,0]
    Out[9]: array([0.101, 0.437, 0.437, 0.855, 0.673])
    #1 and #2 both FastSim bounces directly connected  
    so it kinda makes sense there is no consumption between them 


    In [8]: bb[:,4,3].view(np.uint64)
    Out[8]: array([ 5, 27, 35, 64, 79], dtype=uint64)

    In [10]: bb[:,4,0]
    Out[10]: array([0.101, 0.437, 0.073, 0.799, 0.929])

    ## HMM : LOOKS LIKE WILL NEED TO REWIND THE SEQUENCE : IMPLEMENT AN "UN-BURN" 



Add aux to SEvt : following SOpBoundaryProp::get_u0 at each point
---------------------------------------------------------------------

::

    In [14]: a.aux[726,:21,0,3].view(np.uint32)
    Out[14]: array([ 0,  0,  5,  5, 10, 13, 20, 27, 27, 27, 34, 37, 44, 51, 58, 58, 63, 66, 73, 73,  0], dtype=uint32)

    In [29]: np.diff(a.aux[726,:21,0,3].view(np.uint32))[:-1]
    Out[29]: array([0, 5, 0, 5, 3, 7, 7, 0, 0, 7, 3, 7, 7, 7, 0, 5, 3, 7, 0], dtype=uint32)


    In [13]: b.aux[726,:21,0,3].view(np.uint32)
    Out[13]: array([ 0,  0,  5, 10, 20, 27, 35, 43, 50, 57, 64, 72, 79, 87, 94,  0,  0,  0,  0,  0,  0], dtype=uint32)

    In [33]: np.diff(b.aux[726,:21,0,3].view(np.uint32))[:-6]
    Out[33]: array([ 0,  5,  5, 10,  7,  8,  8,  7,  7,  7,  8,  7,  8,  7], dtype=uint32)



    In [15]: a.aux[726,:21,0,0]
    Out[15]: array([0.872, 0.872, 0.101, 0.101, 0.352, 0.878, 0.498, 0.437, 0.437, 0.437, 0.019, 0.457, 0.751, 0.645, 0.855, 0.855, 0.663, 0.502, 0.673, 0.673, 0.   ], dtype=float32)

    In [16]: b.aux[726,:21,0,0]
    Out[16]: array([0.872, 0.872, 0.101, 0.878, 0.498, 0.437, 0.073, 0.106, 0.841, 0.812, 0.799, 0.246, 0.929, 0.341, 0.556, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   ], dtype=float32)




random consumption comparison between N=0 and N=1
-----------------------------------------------------

u4t/U4PMTFastSimTest.sh add BP::

    119 if [ "$arg" == "dbg" ]; then
    120     export BP=MixMaxRng::flat
    121     [ -f "$log" ] && rm $log 
    122     case $(uname) in 
    123         Darwin) lldb__ $bin ;;
    124         Linux)   gdb__ $bin ;;
    125     esac
    126     [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 2
    127 fi  


::

    Process 85498 stopped
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
        frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107800190) at MixMaxRng.h:67 [opt]
       64  	  MixMaxRng& operator=(const MixMaxRng& rng);
       65  	  // Copy constructor and assignment operator.
       66  	
    -> 67  	  double flat() { return (S.counter<=(N-1)) ? generate(S.counter):iterate(); }
       68  	  // Returns a pseudo random number between 0 and 1
       69  	  // (excluding the zero: in (0,1] )
       70  	  // smallest number which it will give is approximately 10^-19
    Target 0: (U4PMTFastSimTest) stopped.
    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107800190) at MixMaxRng.h:67 [opt]
        frame #1: 0x000000010026b622 libU4.dylib`U4UniformRand::Get() at U4UniformRand.h:63
        frame #2: 0x000000010026b460 libU4.dylib`U4UniformRand::Get(uu=size=1000) at U4UniformRand.h:73
        frame #3: 0x0000000100264d38 libU4.dylib`U4UniformRand::Get(n=1000) at U4UniformRand.h:94
        frame #4: 0x0000000100263c19 libU4.dylib`U4Recorder::saveOrLoadStates(this=0x0000000107a44090, id=726) at U4Recorder.cc:290
        frame #5: 0x000000010026252c libU4.dylib`U4Recorder::PreUserTrackingAction_Optical(this=0x0000000107a44090, track=0x00000001078c79a0) at U4Recorder.cc:184
        frame #6: 0x0000000100261da2 libU4.dylib`U4Recorder::PreUserTrackingAction(this=0x0000000107a44090, track=0x00000001078c79a0) at U4Recorder.cc:96
        frame #7: 0x0000000100035ba1 U4PMTFastSimTest`U4RecorderTest::PreUserTrackingAction(this=0x0000000


Need to skip the pre-collection. So plant a breakpoint after and diable the flat BP::

    (lldb) f 4
    frame #4: 0x0000000100263c19 libU4.dylib`U4Recorder::saveOrLoadStates(this=0x0000000107c73ca0, id=726) at U4Recorder.cc:290
       287 	
       288 	        if( id == SEventConfig::_G4StateRerun )
       289 	        {
    -> 290 	            rerun_rand = U4UniformRand::Get(1000);
       291 	            U4UniformRand::UU = rerun_rand ; 
       292 	            SEvt::UU = rerun_rand ;  // better hitching it somewhere thats always accessible 
       293 	
    (lldb) b 291
    Breakpoint 2: where = libU4.dylib`U4Recorder::saveOrLoadStates(int) + 1490 at U4Recorder.cc:291, address = 0x0000000100263c32
    (lldb) br list
    Current breakpoints:
    1: name = 'MixMaxRng::flat', locations = 1, resolved = 1, hit count = 1
      1.1: where = libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat() + 4 at MixMaxRng.h:67, address = 0x0000000105eef4a4, resolved, hit count = 1 

    2: file = '/Users/blyth/opticks/u4/U4Recorder.cc', line = 291, exact_match = 0, locations = 1, resolved = 1, hit count = 0
      2.1: where = libU4.dylib`U4Recorder::saveOrLoadStates(int) + 1490 at U4Recorder.cc:291, address = 0x0000000100263c32, resolved, hit count = 0 

    (lldb) 

    (lldb) br dis 1
    1 breakpoints disabled.
    (lldb) 

    ## continue past the pre-collection 

    (lldb) br en 1
    1 breakpoints enabled.


N=0 Manual Enumeration of Random Consumption
----------------------------------------------

::

   00: BOP.Reset
    1: Rayleigh.Reset
    2: Absorption.Reset

    3: BOP.PSDI
    4: BOP.PSDI.DiDi.TransCoeff

    5: BOP.Reset
    6: Rayleigh.Reset
    7: Absorption.Reset

    8: jPOM.DoIt.u0   176 junoPMTOpticalModel::DoIt@497:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T 
    9: jPOM.DoIt.u1   177 junoPMTOpticalModel::DoIt@506:  u1 UU[0.94190      9] u1_idx 9 D     0.0000                                       

   10: BOP.Reset
   11: Rayleigh.Reset
   12: Absorption.Reset        ## thats fake z=0 crossing  

   13: BOP.Reset
   14: Rayleigh.Reset
   15: Absorption.Reset


HMM, thats confusing this is N=0 but still encounter the "@" OpticalSurface? 
Add the "if(m_natural_geometry) name += '@' ;"::

     333 void HamamatsuR12860PMTManager::init_mirror_surface()
     334 {
     335     if(m_mirror_opsurf) return ;
     336 
     337     G4String name ;
     338     if(m_natural_geometry) name += '@' ;  
     339     name += GetName() ;
     340     name += "_Mirror_opsurf" ;
     341 
     342     m_mirror_opsurf = new G4OpticalSurface(name);
     343     m_mirror_opsurf->SetFinish(polishedfrontpainted); // needed for mirror
     344     m_mirror_opsurf->SetModel(glisur);
     345     m_mirror_opsurf->SetType(dielectric_metal);
     346     m_mirror_opsurf->SetPolish(0.999);


This kinda invalidates the comparison. 
So start again with Rayleigh and Absorption switched off 
to simplify consumption. 


N=0 Fall Stacks at random consumption, summarized above
-----------------------------------------------------------

::

    (lldb) c
    Process 85715 resuming
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt@250: [  PostStepDoIt_count 3 label.desc spho (gs:ix:id:gn   0 726  726[  0,  0,  0, 95])
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@388:  PostStepDoIt_count 3 thePrePV hama_inner2_phys thePostPV hama_body_phys kCarTolerance/2 5e-10
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@551:  PostStepDoIt_count 3 Surface hama_mirror_logsurf1 OpticalSurface @hama_Mirror_opsurf
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@561:  PostStepDoIt_count 3  OpticalSurfaceName @hama_Mirror_opsurfU4OpticalSurface::Desc  @hama_Mirror_opsurf type:dielectric_metal model:glisur finish:polishedfrontpainted polish:0.999
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@648:  PostStepDoIt_count 3 theReflectivity 0.92 theEfficiency 0 theTransmittance 0 CustomART_status Z
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@685:  PostStepDoIt_count 3 after OpticalSurface if 
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@730:  PostStepDoIt_count 3 type switch dielectric_metal CustomART_status Z CustomART_active 0 CustomART_::Desc ZLocalDoesNotTrigger








First is as expected, BOP.Reset::

    (lldb) f 1
    frame #1: 0x000000010027dcd6 libU4.dylib`InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft(this=0x0000000106f6f9c0) at InstrumentedG4OpBoundaryProcess.cc:131
       128 	//void InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft(){ G4VProcess::ResetNumberOfInteractionLengthLeft(); }
       129 	void InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft()
       130 	{
    -> 131 	    G4double u0 = G4UniformRand() ; 
       132 	
       133 	    bool burn_enabled = true ; 
       134 	    if(burn_enabled)
    (lldb) 


2nd unexpected, I thought I had disabled Rayleigh.Reset::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107a01db0) at MixMaxRng.h:67 [opt]
        frame #1: 0x000000010006619a U4PMTFastSimTest`ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft(this=0x0000000106f6f830) at ShimG4OpRayleigh.cc:39
        frame #2: 0x0000000100066302 U4PMTFastSimTest`ShimG4OpRayleigh::PostStepGetPhysicalInteractionLength(this=0x0000000106f6f830, track=0x0000000107a5b950, previousStepSize=0, condition=0x00000001078a98b8) at ShimG4OpRayleigh.cc:66
        frame #3: 0x000000010227fff0 libG4tracking.dylib`G4VProcess::PostStepGPIL(this=0x0000000106f6f830, track=0x0000000107a5b950, previousStepSize=0, condition=0x00000001078a98b8) at G4VProcess.hh:506
        frame #4: 0x000000010227fa1a libG4tracking.dylib`G4SteppingManager::DefinePhysicalStepLength(this=0x00000001078a9730) at G4SteppingManager2.cc:173
        frame #5: 0x000000010227cc3a libG4tracking.dylib`G4SteppingManager::Stepping(this=0x00000001078a9730) at G4SteppingManager.cc:180
        frame #6: 0x000000010229386f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x00000001078a96f0, apValueG4Track=0x0000000107a5b950) at G4TrackingManager.cc:126
        frame #7: 0x000000010215971a libG4event.dylib`G4EventManager::DoProcessing(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:185
        frame #8: 0x000000010215ac2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:338
        frame #9: 0x00000001020669e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x00000001078a9480, i_event=0) at G4RunManager.cc:399
        frame #10: 0x0000000102066815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #11: 0x0000000102064cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #12: 0x0000000100039b5d U4PMTFastSimTest`U4PMTFastSimTest::BeamOn(this=0x00007ffeefbfe010) at U4PMTFastSimTest.cc:43
        frame #13: 0x000000010003a482 U4PMTFastSimTest`main(argc=1, argv=0x00007ffeefbfe5f0) at U4PMTFastSimTest.cc:75
        frame #14: 0x00007fff702c2015 libdyld.dylib`start + 1
    (lldb) 

3rd also unexpected from Absorption.Reset::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107a01db0) at MixMaxRng.h:67 [opt]
        frame #1: 0x000000010006480a U4PMTFastSimTest`ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft(this=0x0000000106f6f6b0) at ShimG4OpAbsorption.cc:35
        frame #2: 0x0000000100064b12 U4PMTFastSimTest`ShimG4OpAbsorption::PostStepGetPhysicalInteractionLength(this=0x0000000106f6f6b0, track=0x0000000107a5b950, previousStepSize=0, condition=0x00000001078a98b8) at ShimG4OpAbsorption.cc:66
        frame #3: 0x000000010227fff0 libG4tracking.dylib`G4VProcess::PostStepGPIL(this=0x0000000106f6f6b0, track=0x0000000107a5b950, previousStepSize=0, condition=0x00000001078a98b8) at G4VProcess.hh:506
        frame #4: 0x000000010227fa1a libG4tracking.dylib`G4SteppingManager::DefinePhysicalStepLength(this=0x00000001078a9730) at G4SteppingManager2.cc:173
        frame #5: 0x000000010227cc3a libG4tracking.dylib`G4SteppingManager::Stepping(this=0x00000001078a9730) at G4SteppingManager.cc:180
        frame #6: 0x000000010229386f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x00000001078a96f0, apValueG4Track=0x0000000107a5b950) at G4TrackingManager.cc:126
        frame #7: 0x000000010215971a libG4event.dylib`G4EventManager::DoProcessing(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:185
        frame #8: 0x000000010215ac2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:338
        frame #9: 0x00000001020669e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x00000001078a9480, i_event=0) at G4RunManager.cc:399
        frame #10: 0x0000000102066815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #11: 0x0000000102064cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #12: 0x0000000100039b5d U4PMTFastSimTest`U4PMTFastSimTest::BeamOn(this=0x00007ffeefbfe010) at U4PMTFastSimTest.cc:43
        frame #13: 0x000000010003a482 U4PMTFastSimTest`main(argc=1, argv=0x00007ffeefbfe5f0) at U4PMTFastSimTest.cc:75
        frame #14: 0x00007fff702c2015 libdyld.dylib`start + 1
    (lldb) 



4th expected, BOP.PSDI::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107a01db0) at MixMaxRng.h:67 [opt]
        frame #1: 0x000000010028299e libU4.dylib`InstrumentedG4OpBoundaryProcess::PostStepDoIt_(this=0x0000000106f6f9c0, aTrack=0x0000000107a5b950, aStep=0x00000001078a98c0) at InstrumentedG4OpBoundaryProcess.cc:774
        frame #2: 0x0000000100280025 libU4.dylib`InstrumentedG4OpBoundaryProcess::PostStepDoIt(this=0x0000000106f6f9c0, aTrack=0x0000000107a5b950, aStep=0x00000001078a98c0) at InstrumentedG4OpBoundaryProcess.cc:256
        frame #3: 0x00000001022817db libG4tracking.dylib`G4SteppingManager::InvokePSDIP(this=0x00000001078a9730, np=3) at G4SteppingManager2.cc:538
        frame #4: 0x000000010228164d libG4tracking.dylib`G4SteppingManager::InvokePostStepDoItProcs(this=0x00000001078a9730) at G4SteppingManager2.cc:510
        frame #5: 0x000000010227cdaa libG4tracking.dylib`G4SteppingManager::Stepping(this=0x00000001078a9730) at G4SteppingManager.cc:209
        frame #6: 0x000000010229386f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x00000001078a96f0, apValueG4Track=0x0000000107a5b950) at G4TrackingManager.cc:126
        frame #7: 0x000000010215971a libG4event.dylib`G4EventManager::DoProcessing(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:185
        frame #8: 0x000000010215ac2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:338
        frame #9: 0x00000001020669e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x00000001078a9480, i_event=0) at G4RunManager.cc:399
        frame #10: 0x0000000102066815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #11: 0x0000000102064cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #12: 0x0000000100039b5d U4PMTFastSimTest`U4PMTFastSimTest::BeamOn(this=0x00007ffeefbfe010) at U4PMTFastSimTest.cc:43
        frame #13: 0x000000010003a482 U4PMTFastSimTest`main(argc=1, argv=0x00007ffeefbfe5f0) at U4PMTFastSimTest.cc:75
        frame #14: 0x00007fff702c2015 libdyld.dylib`start + 1
    (lldb) 

    (lldb) f 1
    frame #1: 0x000000010028299e libU4.dylib`InstrumentedG4OpBoundaryProcess::PostStepDoIt_(this=0x0000000106f6f9c0, aTrack=0x0000000107a5b950, aStep=0x00000001078a98c0) at InstrumentedG4OpBoundaryProcess.cc:774
       771 	        else
       772 	        {   
       773 	            //[type_switch.didi.not_backpainted
    -> 774 	            G4double rand = G4UniformRand();
       775 	            LOG(LEVEL) 
       776 	                << " PostStepDoIt_count " << PostStepDoIt_count
       777 	                << " didi.rand " << U4UniformRand::Desc(rand) 
    (lldb) 


BOP.PSDI.DiDi.TransCoeff::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
      * frame #0: 0x0000000105eef4a4 libCLHEP-2.4.1.0.dylib`CLHEP::MixMaxRng::flat(this=0x0000000107a01db0) at MixMaxRng.h:67 [opt]
        frame #1: 0x0000000100290577 libU4.dylib`InstrumentedG4OpBoundaryProcess::G4BooleanRand_TransCoeff(this=0x0000000106f6f9c0, prob=0.99733593988630786) const at InstrumentedG4OpBoundaryProcess.cc:2373
        frame #2: 0x000000010028cc62 libU4.dylib`InstrumentedG4OpBoundaryProcess::DielectricDielectric(this=0x0000000106f6f9c0) at InstrumentedG4OpBoundaryProcess.cc:1881
        frame #3: 0x0000000100283003 libU4.dylib`InstrumentedG4OpBoundaryProcess::PostStepDoIt_(this=0x0000000106f6f9c0, aTrack=0x0000000107a5b950, aStep=0x00000001078a98c0) at InstrumentedG4OpBoundaryProcess.cc:830
        frame #4: 0x0000000100280025 libU4.dylib`InstrumentedG4OpBoundaryProcess::PostStepDoIt(this=0x0000000106f6f9c0, aTrack=0x0000000107a5b950, aStep=0x00000001078a98c0) at InstrumentedG4OpBoundaryProcess.cc:256
        frame #5: 0x00000001022817db libG4tracking.dylib`G4SteppingManager::InvokePSDIP(this=0x00000001078a9730, np=3) at G4SteppingManager2.cc:538
        frame #6: 0x000000010228164d libG4tracking.dylib`G4SteppingManager::InvokePostStepDoItProcs(this=0x00000001078a9730) at G4SteppingManager2.cc:510
        frame #7: 0x000000010227cdaa libG4tracking.dylib`G4SteppingManager::Stepping(this=0x00000001078a9730) at G4SteppingManager.cc:209
        frame #8: 0x000000010229386f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x00000001078a96f0, apValueG4Track=0x0000000107a5b950) at G4TrackingManager.cc:126
        frame #9: 0x000000010215971a libG4event.dylib`G4EventManager::DoProcessing(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:185
        frame #10: 0x000000010215ac2f libG4event.dylib`G4EventManager::ProcessOneEvent(this=0x00000001078a9660, anEvent=0x0000000107a59f00) at G4EventManager.cc:338
        frame #11: 0x00000001020669e5 libG4run.dylib`G4RunManager::ProcessOneEvent(this=0x00000001078a9480, i_event=0) at G4RunManager.cc:399
        frame #12: 0x0000000102066815 libG4run.dylib`G4RunManager::DoEventLoop(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:367
        frame #13: 0x0000000102064cd1 libG4run.dylib`G4RunManager::BeamOn(this=0x00000001078a9480, n_event=1, macroFile=0x0000000000000000, n_select=-1) at G4RunManager.cc:273
        frame #14: 0x0000000100039b5d U4PMTFastSimTest`U4PMTFastSimTest::BeamOn(this=0x00007ffeefbfe010) at U4PMTFastSimTest.cc:43
        frame #15: 0x000000010003a482 U4PMTFastSimTest`main(argc=1, argv=0x00007ffeefbfe5f0) at U4PMTFastSimTest.cc:75
        frame #16: 0x00007fff702c2015 libdyld.dylib`start + 1
    (lldb) 



Disable Rayleigh and Absorption
-------------------------------------

Add more disabling::

    148 void U4Physics::ConstructOp()
    ...
    
    171     int G4OpAbsorption_DISABLE = EInt("G4OpAbsorption_DISABLE", "0") ;
    172     int G4OpRayleigh_DISABLE = EInt("G4OpRayleigh_DISABLE", "0") ;
    173     int G4OpBoundaryProcess_DISABLE = EInt("G4OpBoundaryProcess_DISABLE", "0") ;
    174 
    175     LOG(LEVEL) << "G4OpAbsorption_DISABLE      : " << G4OpAbsorption_DISABLE ;
    176     LOG(LEVEL) << "G4OpRayleigh_DISABLE        : " << G4OpRayleigh_DISABLE ;
    177     LOG(LEVEL) << "G4OpBoundaryProcess_DISABLE : " << G4OpBoundaryProcess_DISABLE ;
    178 
    179     if(G4OpAbsorption_DISABLE == 0)
    180     {
    181 #ifdef DEBUG_TAG
    182         fAbsorption = new ShimG4OpAbsorption();
    183 #else
    184         fAbsorption = new G4OpAbsorption();
    185 #endif
    186     }


ARGHH: cannot disable, as it turns big-bouncer into a boring ordinary photon.



Annoyance that x4/xxv.sh x4/tests/X4IntersectVolumeTest.cc accesses geometry differently from u4/tests/U4PMTFastSimTest.cc
-----------------------------------------------------------------------------------------------------------------------------

Would be better to bring xxv.sh functionality over to U4, so can then use more of the same U4VolumeMaker 
geometry access code. 

The thing is the N=0/1 changes geometry. The cleanest way to handle that is to 
have different GEOM names ?  But thats a bit awkward, so take the easy way out and just 
change FOLD with extra "0" or "1" in xxv.sh and tests/X4IntersectVolumeTest.{cc,py}

::

   N=0 ./xxv.sh ana
   N=1 ./xxv.sh ana




Full check of flat backtraces above is informative, but try a simpler approach of just monitoring the decision randoms in N=0 and 1
---------------------------------------------------------------------------------------------------------------------------------------

HMM It would be easier to do the burn shunts at the decision points, rather than the Reset ? 
So can directly control the decisions. But will need to rewind the stream::

    epsilon:tests blyth$ grep DECISION U4PMTFastSimTest_0.log 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R DECISION 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.74358     32] u0_idx 32 A     0.2341 A+R     0.7652 T     0.2348 status R DECISION 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.42483     61] u0_idx 61 A     0.2753 A+R     0.7132 T     0.2868 status R DECISION 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.07245     76] u0_idx 76 A     0.3017 A+R     0.6757 T     0.3243 status A DECISION 

    epsilon:tests blyth$ grep DECISION U4PMTFastSimTest_1.log 
    InstrumentedG4OpBoundaryProcess::CustomART@1096:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    InstrumentedG4OpBoundaryProcess::CustomART@1096:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R DECISION 
    InstrumentedG4OpBoundaryProcess::CustomART@1096:  u0 UU[0.68411     38] u0_idx 38 A     0.2341 A+R     0.7652 T     0.2348 status R DECISION 
    InstrumentedG4OpBoundaryProcess::CustomART@1096:  u0 UU[0.39100     67] u0_idx 67 A     0.2753 A+R     0.7132 T     0.2868 status R DECISION 
    InstrumentedG4OpBoundaryProcess::CustomART@1096:  u0 UU[0.57763     82] u0_idx 82 A     0.3017 A+R     0.6757 T     0.3243 status R DECISION 


Check the number of randoms consumed between each BOP.RESET.
The u0_idx_delta shows the number consumed by the prior step::

    epsilon:tests blyth$ grep "RESET\|DECISION" *_0.log 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87237      0] u0_idx 0 u0_idx_delta 1 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.10137      5] u0_idx 5 u0_idx_delta 5 BOP.RESET 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.35166     10] u0_idx 10 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87761     13] u0_idx 13 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.03802     17] u0_idx 17 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49764     20] u0_idx 20 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49004     24] u0_idx 24 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.43749     27] u0_idx 27 u0_idx_delta 3 BOP.RESET 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R DECISION 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.74358     32] u0_idx 32 A     0.2341 A+R     0.7652 T     0.2348 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.01857     34] u0_idx 34 u0_idx_delta 7 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.45692     37] u0_idx 37 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.32809     41] u0_idx 41 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.75119     44] u0_idx 44 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.85902     48] u0_idx 48 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.64541     51] u0_idx 51 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.50158     55] u0_idx 55 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.85455     58] u0_idx 58 u0_idx_delta 3 BOP.RESET 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.42483     61] u0_idx 61 A     0.2753 A+R     0.7132 T     0.2868 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.66334     63] u0_idx 63 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.50239     66] u0_idx 66 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.44820     70] u0_idx 70 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.67262     73] u0_idx 73 u0_idx_delta 3 BOP.RESET 
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.07245     76] u0_idx 76 A     0.3017 A+R     0.6757 T     0.3243 status A DECISION 



::

    epsilon:tests blyth$ grep "RESET\|DECISION" *_1.log 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87237      0] u0_idx 0 u0_idx_delta 1 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.10137      5] u0_idx 5 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.35166     10] u0_idx 10 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@154: UU[0.87761     13] u0_idx 13 u0_idx_delta 8 after uu_burn 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.03802     17] u0_idx 17 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49764     20] u0_idx 20 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49004     24] u0_idx 24 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.43749     27] u0_idx 27 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.33902     30] u0_idx 30 A     0.2778 A+R     0.7097 T     0.2903 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.74358     32] u0_idx 32 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.07341     35] u0_idx 35 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.68411     38] u0_idx 38 A     0.2341 A+R     0.7652 T     0.2348 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.76067     40] u0_idx 40 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.10561     43] u0_idx 43 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.15855     47] u0_idx 47 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.84133     50] u0_idx 50 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.12365     54] u0_idx 54 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.81213     57] u0_idx 57 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.42483     61] u0_idx 61 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.79864     64] u0_idx 64 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.39100     67] u0_idx 67 A     0.2753 A+R     0.7132 T     0.2868 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87442     69] u0_idx 69 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.24637     72] u0_idx 72 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.07245     76] u0_idx 76 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.92902     79] u0_idx 79 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.57763     82] u0_idx 82 A     0.3017 A+R     0.6757 T     0.3243 status R DECISION 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.66933     84] u0_idx 84 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.34132     87] u0_idx 87 u0_idx_delta 3 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.96883     91] u0_idx 91 u0_idx_delta 4 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.55617     94] u0_idx 94 u0_idx_delta 3 BOP.RESET 
    epsilon:tests blyth$ 


Follow every consumption
--------------------------

::

    epsilon:tests blyth$ grep UU *_0.log > /tmp/UU_0.log  
    epsilon:tests blyth$ grep UU *_1.log > /tmp/UU_1.log  
    vimdiff  /tmp/UU_0.log /tmp/UU_1.log 



::

    epsilon:tests blyth$ grep UU *_0.log 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87237      0] u0_idx 0 u0_idx_delta 1 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.62535      1]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.79217      2]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@793:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::G4BooleanRand_TransCoeff@2394: UU[0.19391      4] TransCoeff 0.997336 DECISION T
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.10137      5] u0_idx 5 u0_idx_delta 5 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.34706      6]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.39788      7]
    junoPMTOpticalModel::DoIt@497:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    junoPMTOpticalModel::DoIt@507:  u1 UU[0.94190      9] u1_idx 9 D     0.0000

    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.35166     10] u0_idx 10 u0_idx_delta 5 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.20162     11]         
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.43366     12]       ## 10,11,12 FROM THE FAKE 

    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87761     13] u0_idx 13 u0_idx_delta 3 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.45764     14]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.77689     15]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1355:  PostStepDoIt_count 3 do-while n 1 rand UU[0.77461     16] theReflectivity 0.92 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.03802     17] u0_idx 17 u0_idx_delta 4 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.53797     18]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.50566     19]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49764     20] u0_idx 20 u0_idx_delta 3 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.54850     21]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.20544     22]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1355:  PostStepDoIt_count 5 do-while n 1 rand UU[0.00594     23] theReflectivity 0.65 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49004     24] u0_idx 24 u0_idx_delta 4 BOP.RESET 



    epsilon:tests blyth$ grep UU *_1.log 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.87237      0] u0_idx 0 u0_idx_delta 1 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.62535      1]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.79217      2]
    *InstrumentedG4OpBoundaryProcess::PostStepDoIt_@793:  PostStepDoIt_count 0 didi.rand UU[0.94347      3] theReflectivity     1.0000 theTransmittance     0.0000
    InstrumentedG4OpBoundaryProcess::G4BooleanRand_TransCoeff@2394: UU[0.19391      4] TransCoeff 0.997336 DECISION T
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.10137      5] u0_idx 5 u0_idx_delta 5 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.34706      6]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.39788      7]
    InstrumentedG4OpBoundaryProcess::CustomART@1114:  u0 UU[0.98594      8] u0_idx 8 A     0.6713 A+R     0.7005 T     0.2995 status T DECISION 
    InstrumentedG4OpBoundaryProcess::CustomART@1124:  u1 UU[0.94190      9] u1_idx 9 D     0.0000
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.35166     10] u0_idx 10 u0_idx_delta 5 BOP.RESET 
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@154: UU[0.87761     13] u0_idx 13 u0_idx_delta 8 after uu_burn 3 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.45764     14]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.77689     15]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1355:  PostStepDoIt_count 2 do-while n 1 rand UU[0.77461     16] theReflectivity 0.92 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.03802     17] u0_idx 17 u0_idx_delta 4 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.53797     18]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.50566     19]
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49764     20] u0_idx 20 u0_idx_delta 3 BOP.RESET 
    ShimG4OpRayleigh::ResetNumberOfInteractionLengthLeft@44: UU[0.54850     21]
    ShimG4OpAbsorption::ResetNumberOfInteractionLengthLeft@43: UU[0.20544     22]
    InstrumentedG4OpBoundaryProcess::DielectricMetal@1355:  PostStepDoIt_count 4 do-while n 1 rand UU[0.00594     23] theReflectivity 0.65 theTransmittance 0
    InstrumentedG4OpBoundaryProcess::ResetNumberOfInteractionLengthLeft@139: UU[0.49004     24] u0_idx 24 u0_idx_delta 4 BOP.RESET 



N=0/1 diverges between point 8 and 9

* FastSim->FastSim has none of the ordinary process Reset consumption, this causes N=1 to consume more of the stream 





How to rewind the stream ?
-----------------------------

saveOrLoadStates currently done at the start of each optical track to allow single photon rerun::

    143 void U4Recorder::PreUserTrackingAction_Optical(const G4Track* track)
    144 {
    ...
    184         saveOrLoadStates(label->id);  // moved here as labelling happens once per torch/input photon


Need to do something similar at step (or even decision) level followed by burn. 




