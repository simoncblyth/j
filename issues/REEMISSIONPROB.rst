REEMISSIONPROB
=================

::

    epsilon:ana blyth$ jgr REEMISSIONPROB
    ./Simulation/DetSimV2/PhysiSim/src/DsG4ScintSimple.cc:        aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/PhysiSim/src/DsG4ScintSimple.cc:                aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/PhysiSim/src/DsG4ScintSimple.cc:                G4cout << " Building the material properties table for REEMISSIONPROB" << G4endl;
    ./Simulation/DetSimV2/PhysiSim/src/DsG4OpAbsReemit.cc:  m_label_reemiprob = label+"REEMISSIONPROB";
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:        aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:                aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:                G4cout << " Building the material properties table for REEMISSIONPROB" << G4endl;
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Scintillation.cc:        aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Scintillation.cc:                aMaterialPropertiesTable->GetProperty("REEMISSIONPROB");
    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsG4Scintillation.cc:                G4cout << " Building the material properties table for REEMISSIONPROB" << G4endl;
    ./Simulation/DetSimV2/MCParamsSvc/share/filldb.C:        " FASTCOMPONENT, REEMISSIONPROB, RAYLEIGH, "
    ./Simulation/DetSimV2/MCParamsSvc/share/filldb.C:        " '%s', '%s', '%s', " // FASTCOMPONENT, REEMISSIONPROB, RAYLEIGH,
    ./Simulation/DetSimV2/MCParamsSvc/share/filldb.C:    TString reem     = load("Material.LS.REEMISSIONPROB");
    ./Simulation/DetSimV2/MCParamsSvc/share/filldb.C:           fastc.Data(), reem.Data(), rayleigh.Data(), // FASTCOMPONENT, REEMISSIONPROB, RAYLEIGH,
    ./Simulation/DetSimV2/MCParamsSvc/share/gen_all.py:    ("Material.LS.REEMISSIONPROB", "vec_d2d"),
    ./Simulation/DetSimV2/MCParamsSvc/share/mc.json:    "objectType": "Material.LS.REEMISSIONPROB",
    ./Simulation/DetSimV2/MCParamsSvc/share/create.sql:  `REEMISSIONPROB` longblob COMMENT '',
    ./Simulation/DetSimV2/MCParamsSvc/src/MCParamsDBSvc.cc:    {"Material.LS.REEMISSIONPROB", "vec_d2d"},
    ./Simulation/DetSimV2/MCParamsSvc/src/test/TestAlg.cc:    st = m_params_svc->Get("Material.LS.REEMISSIONPROB", LS_reemprob);
    ./Simulation/DetSimV2/MCParamsSvc/src/test/TestAlg.cc:    if (st) { LogInfo << "LS.REEMISSIONPROB: " << LS_reemprob.size() << std::endl; }
    ./Simulation/DetSimV2/MCParamsSvc/src/test/TestAlg.cc:    save_it("LS_REEMISSIONPROB", LS_reemprob);
    ./Simulation/DetSimV2/CalibUnit/share/LS.gdml:    <matrix coldim="2" name="REEMISSIONPROB0x252b070" values="1.55e-06 0 
    ./Simulation/DetSimV2/CalibUnit/share/LS.gdml:      <property name="REEMISSIONPROB" ref="REEMISSIONPROB0x252b070"/>
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        LSMPT->AddProperty("REEMISSIONPROB", GdLSReemEnergy, GdLSReem, 28);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        //     + XXXREEMISSIONPROB
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        LSMPT->AddProperty("PPOREEMISSIONPROB", PPO_ReemMomentum, PPO_Reemission, 15);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        LSMPT->AddProperty("bisMSBREEMISSIONPROB", bisMSB_ReemMomentum, bisMSB_Reemission, 23);
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:         helper_mpt(LSMPT, "REEMISSIONPROB",             mcgt.data(), "Material.LS.REEMISSIONPROB");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(LSMPT, "PPOREEMISSIONPROB",          mcgt.data(), "Material.LS.PPOREEMISSIONPROB");
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstructionMaterial.icc:        helper_mpt(LSMPT, "bisMSBREEMISSIONPROB",       mcgt.data(), "Material.LS.bisMSBREEMISSIONPROB");
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:        // REEMISSIONPROB
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:        get_matprop(tbl_LS, "REEMISSIONPROB", LS_ReEmission_n, LS_ReEmission_energy, LS_ReEmission_prob);
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:        get_matprop(tbl_LS, "PPOREEMISSIONPROB", LS_PPOReEmission_n, LS_PPOReEmission_energy, LS_PPOReEmission_prob);
    ./Simulation/DetSimV2/AnalysisCode/src/OpticalParameterAnaMgr.cc:        get_matprop(tbl_LS, "bisMSBREEMISSIONPROB", LS_bisReEmission_n, LS_bisReEmission_energy, LS_bisReEmission_prob);
    epsilon:offline blyth$ 



    epsilon:offline blyth$ jgr LSExpDetectorConstructionMaterial.icc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:#include "LSExpDetectorConstructionMaterial.icc"
    ./Doc/detsim/material.md:    * `LSExpDetectorConstructionMaterial.icc`
    ./Doc/oum/source/detsim/material.md:    * `LSExpDetectorConstructionMaterial.icc`
    epsilon:offline blyth$ 



::

    jcv LSExpDetectorConstruction LSExpDetectorConstructionMaterial


    185   private:
    186      bool helper_mpt(G4MaterialPropertiesTable*, const std::string&, IMCParamsSvc*, const std::string&, double scale=1.0);


    1806 bool
    1807 LSExpDetectorConstruction::helper_mpt(G4MaterialPropertiesTable* MPT, const std::string& mname, IMCParamsSvc* params, const std::string& name, double scale) {
    1808     IMCParamsSvc::vec_d2d props;
    1809     bool st = params->Get(name, props);
    1810     if (!st) {
    1811         LogError << "can't find material property: " << name << std::endl;
    1812         return false;
    1813     }
    1814     G4MaterialPropertyVector* vec = new G4MaterialPropertyVector(0,0,0);
    1815 
    1816     int N = props.size();
    1817     if (!N) {
    1818         LogError << "empty material property: " << name << std::endl;
    1819         return false;
    1820     }
    1821     for (int i = 0; i < N; ++i) {
    1822         vec->InsertValues(props[i].get<0>(), props[i].get<1>()*scale);
    1823     }
    1824     MPT->AddProperty(mname.c_str(), vec);
    1825     return true;
    1826 }


::

     131     SniperPtr<IMCParamsSvc> mcgt(*m_scope, "MCParamsSvc");
     132     if (mcgt.invalid()) {
     133           G4cout << "Can't find MCParamsSvc." << G4endl;
     134           assert(0);
     135        }
     136 
     ...
     288        
     289          helper_mpt(LSMPT, "RINDEX",                     mcgt.data(), "Material.LS.RINDEX");
     290          helper_mpt(LSMPT, "FASTCOMPONENT",              mcgt.data(), "Material.LS.FASTCOMPONENT");
     291          helper_mpt(LSMPT, "SLOWCOMPONENT",              mcgt.data(), "Material.LS.FASTCOMPONENT");
     292          helper_mpt(LSMPT, "REEMISSIONPROB",             mcgt.data(), "Material.LS.REEMISSIONPROB");
     293          helper_mpt(LSMPT, "RAYLEIGH",                   mcgt.data(), "Material.LS.RAYLEIGH", scale_rayleigh);
     294         


::

    epsilon:offline blyth$ jgr get_implv1
    ./Simulation/DetSimV2/MCParamsSvc/src/MCParamsFileSvc.cc:    return get_implv1(param, props);
    ./Simulation/DetSimV2/MCParamsSvc/src/MCParamsFileSvc.cc:    return get_implv1(param, props);
    ./Simulation/DetSimV2/MCParamsSvc/src/MCParamsFileSvc.cc:    st = get_implv1(param, vec_props);
    ./Simulation/DetSimV2/MCParamsSvc/src/utils.hh:bool get_implv1(const std::string& param, 
    epsilon:offline blyth$ vi Simulation/DetSimV2/MCParamsSvc/src/utils.hh
    epsilon:offline blyth$ 


::

    P[blyth@localhost LS]$ cat $JUNOTOP/data/Simulation/DetSim/Material/LS/REEMISSIONPROB
              1.55000*eV     0
              1.73987*eV     0
              2.15315*eV     0.0587
              2.42867*eV     0.1141
              2.45963*eV     0.1259
              2.49129*eV     0.1215
              2.52368*eV     0.116
              2.55682*eV     0.1372
              2.59075*eV     0.1344
              2.62547*eV     0.1409
              2.66104*eV     0.1417
              2.69747*eV     0.1712
              2.73481*eV     0.1936
              2.77308*eV     0.1969
              2.81231*eV     0.2203
              2.85255*eV     0.2354
              2.89384*eV     0.3004
              2.93621*eV     0.4165
              2.97972*eV     0.6353
              3.02439*eV     0.8022
              3.07030*eV     0.8004
              3.21588*eV     0.8006
              3.80628*eV     0.8    
              5.87347*eV     0.45   
              6.20000*eV     0.42   
              7.75000*eV     0.40   
              10.33  *eV     0.40   
              15.5   *eV     0.40   
    P[blyth@localhost LS]$ 


    epsilon:ana blyth$ ./ls.py 
        wavelen      rindex      abslen     scatlen    reemprob    groupvel 
         60.000       1.454       0.003     546.429       0.400     206.241 
         80.000       1.454       0.003     546.429       0.400     206.241 
        100.000       1.454       0.003     546.429       0.400     206.241 
        120.000       1.454       0.003     546.429       0.400     192.299 
        140.000       1.664       0.003     546.429       0.400     173.446 
        160.000       1.793       0.003     546.429       0.400     118.988 
        180.000       1.527       0.003     546.429       0.410     139.949 
        200.000       1.618       0.003     547.535       0.420     177.249 
        220.000       1.600       0.198    1415.292       0.477     166.321 
        240.000       1.582       0.392    2283.049       0.538     166.320 
        260.000       1.563       0.586    3150.806       0.599     166.319 
        280.000       1.545       0.781    4018.563       0.660     166.319 
        300.000       1.526       0.975    4887.551       0.721     177.207 
        320.000       1.521       1.169    7505.381       0.782     186.734 
        340.000       1.516       1.364   10123.211       0.800     186.733 
        360.000       1.511       5.664   12741.041       0.800     186.733 
        380.000       1.505      12.239   15358.871       0.801     186.733 
        400.000       1.500     195.518   17976.701       0.800     189.766 
        420.000       1.497   40892.633   23161.414       0.497     193.682 
        440.000       1.495   84240.547   29164.996       0.222     195.357 
        460.000       1.494   78284.352   33453.633       0.169     195.915 
        480.000       1.492   92540.648   37742.270       0.135     195.684 
        500.000       1.490  114196.219   43987.516       0.123     195.369 
        520.000       1.488   88688.727   52136.293       0.106     195.275 
        540.000       1.487   91878.211   60285.070       0.089     196.430 
        560.000       1.485   93913.664   75733.656       0.072     198.024 
        580.000       1.485   67581.016   98222.445       0.057     198.572 
        600.000       1.484   46056.891  116999.734       0.048     198.683 
        620.000       1.483   44640.812  132183.031       0.040     198.732 
        640.000       1.482   15488.402  147366.312       0.031     198.733 
        660.000       1.481   20362.018  162549.594       0.023     198.733 
        680.000       1.480   20500.150  177732.875       0.014     199.247 
        700.000       1.480   13182.578  192957.234       0.005     200.349 
        720.000       1.479    7429.221  218677.828       0.000     200.931 
        740.000       1.479    5515.074  244398.406       0.000     200.931 
        760.000       1.479    2898.857  270119.000       0.000     200.931 
        780.000       1.478   10900.813  295839.562       0.000     200.936 
        800.000       1.478    9584.489  321429.000       0.000     201.905 
        820.000       1.478    5822.304  321429.000       0.000     202.823 
    epsilon:ana blyth$ 
    epsilon:ana blyth$ 


