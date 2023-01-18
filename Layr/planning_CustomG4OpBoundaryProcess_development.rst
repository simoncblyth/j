
planning_CustomG4OpBoundaryProcess_development.rst
===================================================

Intermediary struct to hold PMTSimParamData pointer and Pyrex + Vacuum props and provide StackSpec API
---------------------------------------------------------------------------------------------------------

* Interim name : JPMTData.h/JPMTSimData.h 
* aims to replace the role of JPMT.h for full running 
* based on low dependency PMTSimParamData 
* aim for use from an ~/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc 

Although this must become part of the monolith are aiming 
for the initial development to be done within Opticks territory within some macro block, 
profiting from the persisting of PMTSimParamData as used by::

   ~/junotop/junosw/Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/tests/PMTSimParamData_test.sh

Considerations
----------------

1. current expts are in Opticks environment, BUT code needs to operate within monolith, so:

   * no SLOG.hh : easily dropped 
   * no U4Touchable.h : U4Touchable::ReplicaNumber need to bring this header into monolith

2. u4 depends on PMTFastSim package from whence it gets JPMT.h 
   via ../Layr/JPMT.h in ~/j/PMTFastSim/CMakeLists.txt 


CustomG4OpBoundaryProcess
--------------------------

Q: CustomG4OpBoundaryProcess will be instanciated within DsPhysConsOptical, is that too soon 
   for the PMT data to be accessed ?

A: Unknown, BUT DsPhysConsOptical already accesses IMCParamsSvc so presumably it
   can also access IPMTSimParamSvc in order to get the PMTSimParamData pointer 
   and hence instanciate the intermediary 

jcv DsPhysConsOptical::

     89 void DsPhysConsOptical::SetParameters(){
     90 
     91       SniperPtr<IMCParamsSvc> mcgt(*getParent(), "MCParamsSvc");
     96       IMCParamsSvc::map_s2d LS_constant_map;
     97       bool st = mcgt->Get("Material.LS.ConstantProperty", LS_constant_map);



How to effect the customization with some impl flexibility ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* CustomART is templated on the accessor 

* too tedious to turn CustomG4OpBoundaryProcess into a templated class

* could add a templated method to slide in a flexible impl : but 
  CustomART really needs instanciation in the ctor, so thats not 
  very convenient  

* customizing a Geant4 class is inherently fiddly, so dont 
  worry too much about impl flexibility : just keep things 
  clear by keeping changes in separate headers to minimize 
  changes to CustomG4OpBoundaryProcess code



u4/CustomBoundary.h : abandoned expt?
-----------------------------------------

* actually doing the Reflect/Refract, better 
  to reuse this functionality from the CustomG4OpBoundaryProcess host  
  

u4/CustomART.h : CustomART<JPMT> doing less than CustomBoundary.h 
------------------------------------------------------------

* need to converge standalone and full PMT data accessor APIs
  such that CustomART can work with both of them 

* currently instantiates J* parameter_accessor in ctor, 
  it makes more sense to pass ptr into ctor : clearer + more general 

* CustomART::doIt prepares StackSpec<double,4> with multiple calls to 
  the J* parameter_accessor with pmtcat and energy_eV arguments, the 
  pmtcat needs to be obtained from pmtid 

  * makes sense to hive this off into J so can::

      void J::get_stackspec_qe(StackSpec<double>& spec, double& qe, int pmtid, double energy_eV ) const ;  

      parameter_accessor->get_stackspec_qe(spec, _qe, pmtid, energy_eV) ; 

  * hiving off moves all the parameter access into one call, so easier to test  

  * but that means must split StackSpec and LayrSpec from current home in j/Layr.h  
  * (OR could just use std::array<double, 16>& to keep things decoupled? the spec is 
     simple enough that this makes sense)
    


j/Layr/JPMT.h
-----------------

gives standalone access to PMT data

Used within PMTFASTSIM_STANDALONE blocks of:

* ~/j/PMTFastSim/junoPMTOpticalModel.cc
* ~/opticks/u4/InstrumentedG4OpBoundaryProcess.cc 

* JPMT.h gets PMT data by direct loading with NPFold::LoadProp from 
  NP_PROP_BASE=$JUNOTOP/data/Simulation/DetSim

* avoids any use of PMTSimParamSvc OR PMTParamSvc 



TODO : Review Priors 
----------------------

p17

* https://simoncblyth.bitbucket.io/env/presentation/opticks_20221220_junoPMTOpticalModel_FastSim_issues_and_CustomG4OpBoundaryProcess_fix.html



HMM : rather than start from JPMTData.h better to start by 
copying the standard 1042 G4OpBoundaryProcess into u4/CustomG4OpBoundaryProcess 
and see how I am going to do the customization.

::

    epsilon:u4 blyth$ cp /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/include/G4OpBoundaryProcess.hh CustomG4OpBoundaryProcess.hh
    epsilon:u4 blyth$ cp /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/src/G4OpBoundaryProcess.cc CustomG4OpBoundaryProcess.cc
    epsilon:u4 blyth$ 


HMM : actually before that can start by studying u4/InstrumentedG4OpBoundaryProcess
and exploring ways of getting the PMT data into it. 

* JPMT.h just 



::

     222 InstrumentedG4OpBoundaryProcess::InstrumentedG4OpBoundaryProcess(const G4String& processName, G4ProcessType type)
     223     :
     224     G4VDiscreteProcess(processName, type)
     225 #ifdef WITH_PMTFASTSIM
     226     ,SOpBoundaryProcess(processName.c_str())
     227 #endif
     228     ,theCustomStatus('U')
     229 #ifdef WITH_PMTFASTSIM
     230     ,m_custom_boundary(new CustomBoundary<JPMT>(
     231                   NewMomentum,
     232                   NewPolarization,
     233                   aParticleChange,
     234                   theStatus,
     235                   theGlobalPoint,
     236                   OldMomentum,
     237                   OldPolarization,
     238                   theRecoveredNormal,
     239                   thePhotonMomentum))
     240 
     241     ,m_custom_art(new CustomART<JPMT>(
     242                   theTransmittance,
     243                   theReflectivity,
     244                   theEfficiency,
     245                   theGlobalPoint,
     246                   OldMomentum,
     247                   OldPolarization,
     248                   theRecoveredNormal,
     249                   thePhotonMomentum))
     250     ,m_u0(-1.)
     251     ,m_u0_idx(-1)
     252 #endif






