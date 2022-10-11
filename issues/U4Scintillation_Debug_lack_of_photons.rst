U4Scintillation_Debug_lack_of_photons
========================================

FIXED : Was typo in BirksConstant1

::

    epsilon:tests blyth$ ./U4Scintillation_Debug.sh 
    s30 ntds3/000 (47, 4, 4) /tmp/u4debug/ntds3/000/U4Scintillation_Debug.npy
    s31 ntds3/001 (51, 4, 4) /tmp/u4debug/ntds3/001/U4Scintillation_Debug.npy
    ['posx', 'posy', 'posz', 'time', 'ResolutionScale', 'dx', 'dE_dx', 'birk1', 'TotalEnergyDeposit', 'QuenchedTotalEnergyDeposit', 'delta', 'birk2', 'ScintillationYield', 'MeanNumberOfTracks', 'NumTracks', 'MeanNumberOfPhotons']

    In [1]: s30[0]                                                                                                                                                                 
    Out[1]: 
    {'posx': 0.0,
     'posy': 0.0,
     'posz': 0.0,
     'time': 0.0,
     'ResolutionScale': 1.0,
     'dx': 222.63492523043573,
     'dE_dx': 9.293368125518313,
     'birk1': 7.521019124780102e+23,
     'TotalEnergyDeposit': 1.756e-05,
     'QuenchedTotalEnergyDeposit': 1.346967616860581e-11,
     'delta': 1.7333662276764504e-18,
     'birk2': 0.0,
     'ScintillationYield': 9846.0,
     'MeanNumberOfTracks': 1.326224315560928e-07,
     'NumTracks': 0.0,
     'MeanNumberOfPhotons': 1.326224315560928e-07}

    In [2]:                                                  


Scint setup
--------------

::


    149     G4VProcess* scint_ = 0;
    150 
    151     if (m_useScintillation && 1) { // DsG4 (with re-emission)
    152         DsG4Scintillation* scint = new DsG4Scintillation(m_opticksMode);
    153 
    154         scint->SetDoQuenching(m_enableQuenching);
    155         scint->SetBirksConstant1(m_birksConstant1);
    156         scint->SetBirksConstant2(m_birksConstant2);
    157         scint->SetDoReemission(m_doReemission);
    158         scint->SetDoReemissionOnly(m_doReemissionOnly);
    159         scint->SetDoBothProcess(m_doScintAndCeren);
    160         scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
    161         scint->SetPreQE(1./m_scintPhotonScaleWeight);
    162         scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
    163         scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
    164         scint->SetTrackSecondariesFirst(true);
    165         scint->SetFlagDecayTimeFast(flagDecayTimeFast);
    166         scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
    167         scint->SetVerboseLevel(EGet::Get<int>("DsG4Scintillation_verboseLevel",0));
    168 
    169 
    170         scint_ = scint;


    074 
     75     //m_cerenPhotonScaleWeight = 3.125;
     76     //m_scintPhotonScaleWeight = 3.125;
     77     m_cerenPhotonScaleWeight = 1;
     78     m_scintPhotonScaleWeight = 1;
     79    
     80 }





Check Where Birks constants are coming from
------------------------------------------------

::

    090 void DsPhysConsOptical::SetParameters(){
     91 
     92       SniperPtr<IMCParamsSvc> mcgt(*getParent(), "MCParamsSvc");
     93       if (mcgt.invalid()) {
     94           G4cout << "Can't find MCParamsSvc." << G4endl;
     95           assert(0);
     96        }
     97       IMCParamsSvc::map_s2d LS_constant_map;
     98       bool st = mcgt->Get("Material.LS.ConstantProperty", LS_constant_map);
     99         if (st && LS_constant_map.count("BirksConstant1") && LS_constant_map.count("BirksConstant2")) {
    100            m_birksConstant1 = LS_constant_map["BirksConstant1"];
    101            m_birksConstant2 = LS_constant_map["BirksConstant2"];
    102           }
    103         else{
    104          LogError<<" BirksConstant doesn't exist.Please check."<<std::endl;
    105         }
    106       LogInfo<<"m_birksConstant1 == " << m_birksConstant1 <<std::endl;
    107       LogInfo<<"m_birksConstant2 == " << m_birksConstant2 <<std::endl;
    108 }

    N[blyth@localhost LS]$ cat $JUNOTOP/data/Simulation/DetSim/Material/LS/ConstantProperty 
    #some constant property of LS

    #SCINTILLATIONYIELD
    ScintillationYield   9846/MeV
    ResolutionScale      1.0

    #birks law
    BirksConstant1  12.05e3*g/cm2/MeV
    BirksConstant2  0
    N[blyth@localhost LS]$ 



HMM::

     358         //////////////////////////////////// Birks' law ////////////////////////
     359         // J.B.Birks. The theory and practice of Scintillation Counting. 
     360         // Pergamon Press, 1964.      
     361         // For particles with energy much smaller than minimum ionization 
     362         // energy, the scintillation response is non-linear because of quenching  
     363         // effect. The light output is reduced by a parametric factor: 
     364         // 1/(1 + birk1*delta + birk2* delta^2). 
     365         // Delta is the energy loss per unit mass thickness. birk1 and birk2 
     366         // were measured for several organic scintillators.         
     367         // Here we use birk1 = 0.0125*g/cm2/MeV and ignore birk2.               
     368         // R.L.Craun and D.L.Smith. Nucl. Inst. and Meth., 80:239-244, 1970.   
     369         // Liang Zhan  01/27/2006 
     370         // /////////////////////////////////////////////////////////////////////
     371 

HMM I wonder is there a 10^6 typo in BirksConstant1 ?::

    In [2]: 12.05e-3
    Out[2]: 0.01205

    In [3]: 12.05e3
    Out[3]: 12050.0


 
