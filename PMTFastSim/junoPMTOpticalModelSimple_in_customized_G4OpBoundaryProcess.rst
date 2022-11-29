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



