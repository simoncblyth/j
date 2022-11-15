PMTFastSim
=============

Trying to create a standalone single PMT test of junoPMTOpticalModel


Done
----------

1. angle scanning with the hacked junoPMTOpticalModel agrees reasonably with LayrTest scanning


FastSim Hookup
----------------

* https://indico.cern.ch/event/789510/contributions/3297180/attachments/1817759/2973421/G4Tutorial_fastSim_vFin.pdf

G4Region attached to root G4LogicalVolume is shared with daughters (and further ancestors).

In Geant4 parametrisation is defined as an additional process that (selected) particle
may undergo – G4FastSimulationManagerProcess.



How is fast sim hooked up in junosw ?
----------------------------------------

::

     37 class junoPMTOpticalModel : public G4VFastSimulationModel
     38 {

     32 junoPMTOpticalModel::junoPMTOpticalModel(G4String modelName, G4VPhysicalVolume* envelope_phys, G4Region* envelope)
     33     : G4VFastSimulationModel(modelName, envelope)
     34 {


::

    epsilon:junosw blyth$ jgr G4FastSimulation
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:#include "G4FastSimulationManagerProcess.hh"
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    G4FastSimulationManagerProcess* fast_sim_man = 0;
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:        fast_sim_man = new G4FastSimulationManagerProcess("fast_sim_man");

::

    229     G4FastSimulationManagerProcess* fast_sim_man = 0;
    230     if (m_doFastSim) { 
    231         fast_sim_man = new G4FastSimulationManagerProcess("fast_sim_man");
    232     }
    233 
    ...
    271           if(particle==G4OpticalPhoton:: Definition()){
    272               if (absreemit_PPO)
    273                   pmanager->AddDiscreteProcess(absreemit_PPO);
    274               if (absreemit_bisMSB)
    275                   pmanager->AddDiscreteProcess(absreemit_bisMSB);
    276               if (absorb)
    277                   pmanager->AddDiscreteProcess(absorb);
    278               if (rayleigh)
    279                   pmanager->AddDiscreteProcess(rayleigh);
    280               pmanager->AddDiscreteProcess(boundproc);
    281              //pmanager->AddDiscretePrcess(pee);
    282               if (m_doFastSim)
    283                   pmanager->AddDiscreteProcess(fast_sim_man);
    284            }




Find Standalone Geant4 setup to bring in 
----------------------------------------------

Need to setup simple standalone Geant4 environment (G4RunManager, physics etc..)
so can get some optical photons onto the single PMT 
and try to get the FastSim model to kick in 

::

    epsilon:opticks blyth$ find . -name '*.cc' -exec grep -l G4RunManager {} \;
    ./cfg4/CSensitiveDetector.cc
    ./cfg4/CPhysics.cc
    ./cfg4/OpNovicePhysicsList.cc
    ./cfg4/Format.cc
    ./cfg4/CStepRec.cc
    ./cfg4/CInputPhotonSource.cc
    ./cfg4/CG4.cc
    ./cfg4/DsG4OpBoundaryProcess.cc
    ## these are ancient 

    ./sysrap/tests/SStackFrameTest.cc
    ./sysrap/tests/SStackFrame_test.cc
    ## stackframe dumping 

    ./u4/tests/U4RecorderTest.cc
    ## THIS ONE LOOKS THE MOST APPROPRIATE 

    ./examples/Geant4/CerenkovMinimal/src/CKM.cc
    ./examples/Geant4/CerenkovMinimal/src/SensitiveDetector.cc
    ## old world G4Opticks, so not directly use, but might have things woth grabbing 


    ./examples/Geant4/G4Minimal/G4Minimal.cc
    ./examples/Geant4/G4Minimal/PhysicsList.cc
    ./examples/Geant4/OpNovice/OpNovice.cc
    ./examples/Geant4/OpNovice/src/OpNoviceSteppingAction.cc
    ## ANCIENT : NO CHANGES SINCE May 16  2020 : BIG RED FLAG : DONT TOUCH WITH BARGE POLE






