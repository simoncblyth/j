j/Misc
=======

Dont recall the story behind thi, probably temp kludge for testing.

::

    epsilon:junosw blyth$ git s
    On branch albert_waterpoolcxn_debug
    Your branch is up-to-date with 'origin/albert_waterpoolcxn_debug'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git checkout -- <file>..." to discard changes in working directory)

        modified:   Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc

    no changes added to commit (use "git add" and/or "git commit -a")
    epsilon:junosw blyth$ git diff 
    diff --git a/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc b/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    index b41b35be..97dfcc2c 100644
    --- a/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    +++ b/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc
    @@ -128,11 +128,17 @@
             Galactic = new G4Material("Galactic", 1., 1.01*g/mole, universe_mean_density, kStateGas, 2.73*kelvin, 3.e-18*pascal);
         }
     
    +
    +#ifdef PMTSIM_STANDALONE
    +    MaterialSvc msv ;
    +    RefBase<MaterialSvc> mcgt(&msv);
    +#else
         SniperPtr<IMCParamsSvc> mcgt(*m_scope, "MCParamsSvc");
         if (mcgt.invalid()) {
               G4cout << "Can't find MCParamsSvc." << G4endl;
               assert(0);
            }
    +#endif
     
     
         LS = G4Material::GetMaterial("LS", any_warnings);
    epsilon:junosw blyth$ cp Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc ~/j/Misc/
