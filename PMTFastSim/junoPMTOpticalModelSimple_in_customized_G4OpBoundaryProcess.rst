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



