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








