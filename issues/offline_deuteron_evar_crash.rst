offline_deuteron_evar_crash
==============================



* https://juno.ihep.ac.cn/trac/changeset/4550/offline/trunk/installation/junoenv/packages/geant4.sh




::

    NeutronHP: /Inelastic file for Z = 8, A = 18 is not found and NeutronHP will use /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4NDL4.5/Inelastic/CrossSection/8_17_Oxygen
    In /home/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/source/processes/hadronic/models/particle_hp/src/G4ParticleHPInelastic.cc, line 87: 
    ===> Please set the environement variable G4DEUTERONHPDATA to point to the deuteron cross-section files.
    Traceback (most recent call last):
      File "/home/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/home/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: std::exception
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully


    eutronHP: /Inelastic file for Z = 8, A = 18 is not found and NeutronHP will use /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4NDL4.5/Inelastic/CrossSection/8_17_Oxygen
    In /home/blyth/junotop/ExternalLibs/Build/geant4.10.04.p02/source/processes/hadronic/models/particle_hp/src/G4ParticleHPInelastic.cc, line 87: 
    ===> Please set the environement variable G4DEUTERONHPDATA to point to the deuteron cross-section files.
    Traceback (most recent call last):
      File "/home/blyth/junotop/offline/Examples/Tutorial/share/tut_detsim.py", line 20, in <module>
        juno_application.run()
      File "/home/blyth/junotop/offline/InstallArea/python/Tutorial/JUNOApplication.py", line 90, in run
        self.toptask.run()
    RuntimeError: std::exception
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4OPTICKS 
    2021-06-26 02:36:43.721 INFO  [388098] [G4Opticks::Finalize@288] G4Opticks.desc ok 0x5a13ff0 opmgr 0x12e688e80 


::

    P[blyth@localhost junoenv]$ env | grep G4
    G4LEVELGAMMADATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/PhotonEvaporation5.2
    G4SVCROOT=/home/blyth/junotop/offline/Simulation/DetSimV2/G4Svc
    G4NEUTRONXSDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4NEUTRONXS1.4
    G4LEDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4EMLOW7.3
    G4NEUTRONHPDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4NDL4.5
    G4ENSDFSTATEDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4ENSDFSTATE2.2
    G4RADIOACTIVEDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/RadioactiveDecay5.2
    G4ABLADATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4ABLA3.1
    G4PIIDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4PII1.3
    G4SAIDXSDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/G4SAIDDATA1.1
    G4REALSURFACEDATA=/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/share/Geant4-10.4.2/data/RealSurface2.1.1
    P[blyth@localhost junoenv]$ 



g4-cls G4ParticleHPInelastic::

     57   //const char* dataDirVariable;
     58   G4String particleName;
     59   if( theProjectile == G4Neutron::Neutron() ) {
     60     dataDirVariable = "G4NEUTRONHPDATA";
     61   }else if( theProjectile == G4Proton::Proton() ) {
     62     dataDirVariable = "G4PROTONHPDATA";
     63      particleName = "Proton";
     64   }else if( theProjectile == G4Deuteron::Deuteron() ) {
     65     dataDirVariable = "G4DEUTERONHPDATA";
     66      particleName = "Deuteron";
     67   }else if( theProjectile == G4Triton::Triton() ) {
     68     dataDirVariable = "G4TRITONHPDATA";
     69      particleName = "Triton";
     70   }else if( theProjectile == G4He3::He3() ) {
     71     dataDirVariable = "G4HE3HPDATA";
     72      particleName = "He3";
     73   }else if( theProjectile == G4Alpha::Alpha() ) {
     74     dataDirVariable = "G4ALPHAHPDATA";
     75      particleName = "Alpha";
     76   } else {
     77     G4String message("G4ParticleHPInelastic may only be called for neutron, proton, deuteron, triton, He3 or alpha, while it is called for " + theProjectile->GetParticleName());
     78     throw G4HadronicException(__FILE__, __LINE__,message.c_str());
     79   }
     80 
     81     SetMinEnergy( 0.0 );
     82     SetMaxEnergy( 20.*MeV );
     83 
     84 //    G4cout << " entering G4ParticleHPInelastic constructor"<<G4endl;
     85   if ( !getenv("G4PARTICLEHPDATA") && !getenv(dataDirVariable) ) {
     86      G4String message( "Please set the environement variable " + G4String(dataDirVariable) + " to point to the " + theProjectile->GetParticleName() + " cross-section files." );
     87      throw G4HadronicException(__FILE__, __LINE__,message.c_str());
     88   }
     89   if ( getenv(dataDirVariable) ) {
     90      dirName = getenv(dataDirVariable);
     91   } else {
     92      dirName = baseName + "/" + particleName;
     93   }
     94 G4cout << dirName << G4endl;


Looking at G4IonPhysicsPHP its clear that Deuterons are involved, but they are not in G4IonPhysics.::

    epsilon:offline blyth$ g4-cls G4IonPhysicsPHP
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02
    vi -R source/physics_lists/constructors/ions/include/G4IonPhysicsPHP.hh source/physics_lists/constructors/ions/src/G4IonPhysicsPHP.cc
    2 files to edit
    epsilon:offline blyth$ g4-cls G4IonPhysics
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02
    vi -R source/physics_lists/constructors/ions/include/G4IonPhysics.hh source/physics_lists/constructors/ions/src/G4IonPhysics.cc
    2 files to edit
    epsilon:offline blyth$ 


