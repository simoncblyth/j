junoPMTOpticalModel
======================

Question 1 : why backwards qe is zero ?
-------------------------------------------

In junoPMTOpticalModel::DoIt why is _qe set to zero for vacuum to glass photons ?
this means that will get no hits from photons that enter the PMT and get reflected 
back to the photocathode ?  

Yaoguang Wang::

    In the new PMT optical model, we regard the measured PDE at one point to be
    contributed by several points on the photocathode due to inner reflections.
    There is no doubt that the backward photons may also generate hit.

    However, the PMT's PDE in simulation is provided by the Pan-Asia mass testing
    system, the contribution from inner reflections may have been involved in the
    PDE data. To avoid double-counting, we adopt a compromise method: the PDE data
    from mass testing system is regarded as the real PDE of the incident point, and
    the backward photons don't yield hits. In this case, the PDE in simulation is
    consistent with data, and we can also take the PMT reflection into
    consideration.

    This is not the final solution, we are still working on decoupling the
    contributions from the incident point and other points due to reflection, then
    the contribution of inner reflections to QE can be properly handled.


Question 2 : why different geometry
-----------------------------------------


I have another question regarding the reasons behind the artificial 
Pyrex/Pyrex boundary and the -4.999 mm smaller size of PMT body solid 
with the multifilm optical model active ?


m_enable_optical_model == false 

                             pyrex
                             .
          |                 | |       |           |
     vac  |     pyrex       | | water |  acrylic  | water 
          |                 | |       |           | 
        inner            body pmt         mask 

        -5 mm             0mm +1e-3mm  


m_enable_optical_model == true
 
           pyrex 
           . 
          | |                 |       |          |
     vac  | |    pyrex        | water | acrylic  |  water 
          | |                 |       |          | 
      inner body             pmt         mask
        -5 -5+1e-3            +1e-3  


(relevant code from the PMT managers is below)


The body_log is where ordinary Geant4 sim hands
over to fastsim/junoPMTOpticalModel so this means that 
the TMM calc starts from the artificial pyrex/pyrex 
boundary which in new optical model is shifted to 1e-3 mm 
from the vacuum. 

Why the complication of the artificial Pyrex/Pyrex boundary ?

Why not start the TMM from the water/pyrex boundary 
and remove the artificial pyrex/pyrex boundary ? 

GPU intersection calcs in float precision against 
boundaries only 1e-3 mm from each other cause complications.
Life would be easier with the GPU simulation to avoid such near coincidence 
boundaries if possible. 

If using the artificial Pyrex/Pyrex boundary is unavoidable 
is there any reason why the nominal offset 1e-3 needs to be so small ?

While 1e-3 mm is small in this context it is 16x - 30x 
larger than the actual total thickness of the thin layers of ~30-60 nm. 
(calculation and relevant code below)

So, could this nominal thickness be 1 mm for example ? 
That would be large enough to avoid float precision intersection issues 
on GPU. 

Simon





::

    epsilon:PMTProperty blyth$ cat R12860/THICKNESS
    ARC_THICKNESS   36.49e-9*m
    PHC_THICKNESS   21.13e-9*m
    epsilon:PMTProperty blyth$ cat NNVTMCP/THICKNESS
    ARC_THICKNESS   40.00e-9*m
    PHC_THICKNESS   20.58e-9*m
    epsilon:PMTProperty blyth$ cat NNVTMCP_HiQE/THICKNESS
    ARC_THICKNESS   10.24e-9*m
    PHC_THICKNESS   18.73e-9*m
    epsilon:PMTProperty blyth$ 


    In [1]: t.thickness    # ( 3 pmtcat, 4 layers, thickness nm )                                                                                                                                     
    Out[1]: 
    array([[[ 0.  ],
            [36.49],
            [21.13],
            [ 0.  ]],

           [[ 0.  ],
            [40.  ],
            [20.58],
            [ 0.  ]],

           [[ 0.  ],
            [10.24],
            [18.73],
            [ 0.  ]]])


    In [6]: 1e-3/(60*1e-9*1e3)
    Out[6]: 16.666666666666664

    In [7]: 1e-3/(30*1e-9*1e3)
    Out[7]: 33.33333333333333



::

     340 void HamamatsuR12860PMTManager::helper_make_solid()
     341 {
     342     double pmt_delta = 1E-3*mm ;
     343     double inner_delta =  -5*mm ;
     344     double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ;
     345 
     346     double zcut = m_pmt_equator_to_bottom ;
     347 
     348     Hamamatsu_R12860_PMTSolid* maker = m_pmtsolid_maker ;
     349     pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
     350     body_solid   = maker->GetSolid(GetName() + "_body_solid",   body_delta , ' ');
     351     inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' ');  // no longer used
     352     inner1_solid = maker->GetSolid(GetName() + "_inner1_solid", inner_delta, 'H');
     353     inner2_solid = maker->GetSolid(GetName() + "_inner2_solid", inner_delta, 'T');
     354 



    312 void NNVTMCPPMTManager::helper_make_solid()
    313 {
    314     double pmt_delta = 1E-3*mm ;
    315     double inner_delta = -5*mm ;
    316 
    317     double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ;
    318     // TODO: find out why body_delta depends on m_enable_optical_model and add comment about that 
    319 
    320     double zcut = m_pmt_equator_to_bottom ;
    321 
    322     NNVT_MCPPMT_PMTSolid* maker = m_pmtsolid_maker ;
    323     pmt_solid    = maker->GetSolid(GetName() + "_pmt_solid",    pmt_delta  , ' ');
    324     body_solid   = maker->GetSolid(GetName() + "_body_solid",   body_delta , ' ');
    325     inner_solid  = maker->GetSolid(GetName() + "_inner_solid",  inner_delta, ' ');
    326     inner1_solid = maker->GetSolid(GetName() + "_inner1_solid", inner_delta, 'H'); // head
    327     inner2_solid = maker->GetSolid(GetName() + "_inner2_solid", inner_delta, 'T'); // tail
    328 


Yaoguang answer
~~~~~~~~~~~~~~~~~~~

The reason that I only enable the PMT optical model at a region 4.999 mm
smaller the PMT body solid is to make the pyrex in this region "thin" enough
that the photon absorption can be neglected. Otherwise, I have to deal with the
photon abosprtion in pyrex in junoPMTOpticalModel.cc

In fact, the mean thickness of PMT bulb is about 3~4mm in our experience,
smaller than the default value (5mm) in simulation. So, I think 1mm thickness
is also acceptable.

Best Regards,

Yaoguang






How is junoPMTOpticalModel hooked up with the normal Geant4 simulation
------------------------------------------------------------------------

* https://geant4.web.cern.ch/sites/default/files/geant4/collaboration/workshops/users2002/talks/lectures/FastSimulation.pdf

::

    807 void
    808 NNVTMCPPMTManager::helper_fast_sim()
    809 {
    810 
    811 #ifdef PMTSIM_STANDALONE
    812 #else
    813 
    814     G4Region* body_region = new G4Region(this->GetName()+"_body_region");
    815     body_log->SetRegion(body_region);
    816     body_region->AddRootLogicalVolume(body_log);
    817 
    818     junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
    819                                                                    body_phys, body_region);
    820 

::

     26 class junoPMTOpticalModel : public G4VFastSimulationModel
     27 {
     28     public:
     29         junoPMTOpticalModel(G4String, G4VPhysicalVolume*, G4Region*);
     30         ~junoPMTOpticalModel();
     31 
     32         virtual G4bool IsApplicable(const G4ParticleDefinition&);
     33         virtual G4bool ModelTrigger(const G4FastTrack&);
     34         virtual void DoIt(const G4FastTrack&, G4FastStep&);
     35 

     75 G4bool junoPMTOpticalModel::IsApplicable(const G4ParticleDefinition & particleType)
     76 {
     77     return (&particleType == G4OpticalPhoton::OpticalPhotonDefinition());
     78 }

     80 G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
     81 {

     // HMM: its quite involved : need to debug this in operation to be confident in it 
     //      curious about how/when/were handover between normal sim and fast sim happens 


    epsilon:src blyth$ g4-cc ModelTrigger
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc://      2) for these, loops on the ModelTrigger() methods to find out 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:  // Loops on the ModelTrigger() methods
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    // Asks the ModelTrigger method if it must be trigged now.
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    if(fApplicableModelList[iModel]->ModelTrigger(fFastTrack)) {
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:    if(fApplicableModelList[iModel]->AtRestModelTrigger(fFastTrack))
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:    case OneModelTrigger:
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:      G4cout << "OneModelTrigger" << G4endl;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:    case NoModelTrigger:
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:      G4cout << "NoModelTrigger" << G4endl;
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/parameterisations/gflash/src/GFlashShowerModel.cc:G4bool GFlashShowerModel::ModelTrigger(const G4FastTrack & fastTrack )
    epsilon:src blyth$ 


g4-cls G4FastSimulationManager::

    160 //------------------------------------------------------------------
    161 // Interface trigger method for the G4ParameterisationManagerProcess
    162 //------------------------------------------------------------------
    163 //   G4bool GetFastSimulationManagerTrigger(const G4Track &);
    164 //
    165 //    This method is used to interface the G4FastSimulationManagerProcess
    166 //    with the user Fast Simulation Models. It's called when the particle 
    167 //    is inside the envelope.
    168 //
    169 //    It :
    170 //
    171 //      1) initialises the private members (fFastTrack and so
    172 //         on);
    173 //      2) loops on the IsApplicable() methods to find out the
    174 //         ones should be applied.
    175 //      2) for these, loops on the ModelTrigger() methods to find out 
    176 //         perhaps one that must be applied just now.
    177 //
    178 //    If the a Fast Simulation Model is triggered then it returns 
    179 //    true, false otherwise.
    180 //
    181 //-----------------------------------------------------------
    182 G4bool
    183 G4FastSimulationManager::
    184 PostStepGetFastSimulationManagerTrigger(const G4Track& track,
    185                     const G4Navigator* theNavigator)
    186 {
    ...
    217     if(fApplicableModelList[iModel]->ModelTrigger(fFastTrack)) {
    218       //--------------------------------------------------
    219       // The model will be applied. Initializes the G4FastStep 
    220       // with the current state of the G4Track and 
    221       // same usefull parameters.
    222       // In particular it does SetLocalEnergyDeposit(0.0).
    223       //--------------------------------------------------  
    224       fFastStep.Initialize(fFastTrack);
    225      
    226       // Keeps the FastSimulationModel pointer to call the
    227       // DoIt() method.
    228       fTriggedFastSimulationModel=fApplicableModelList[iModel];
    229       return true;
    230     }
    231 
    232   //--------------------------------------------
    233   // Nobody asks to gain control, returns false
    234   //--------------------------------------------
    235   return false;
    236 }


    epsilon:src blyth$ g4-cc PostStepGetFastSimulationManagerTrigger
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:PostStepGetFastSimulationManagerTrigger(const G4Track& track,
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManager.cc:  // -- (note: compared to the PostStepGetFastSimulationManagerTrigger,
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/parameterisation/src/G4FastSimulationManagerProcess.cc:	  fFastSimulationTrigger = fFastSimulationManager->PostStepGetFastSimulationManagerTrigger(track, fGhostNavigator);
    epsilon:src blyth$ 


    239 G4double
    240 G4FastSimulationManagerProcess::
    241 PostStepGetPhysicalInteractionLength(const G4Track&               track,
    242                      G4double,
    243                      G4ForceCondition*        condition)
    244 { 
    245   // -- Get current volume, and check for presence of fast simulation manager.
    246   // -- For the case of the navigator for tracking (fGhostNavigatorIndex == 0)
    247   // -- we use the track volume. This allows the code to be valid for both
    248   // -- cases where the PathFinder is used (G4CoupledTranportation) or not
    249   // -- (G4Transportation).
    250   const G4VPhysicalVolume* currentVolume(0);
    251   if ( fIsGhostGeometry )  currentVolume = fPathFinder->GetLocatedVolume(fGhostNavigatorIndex);
    252   else                     currentVolume = track.GetVolume();
    253   
    254   if ( currentVolume )
    255     { 
    256       fFastSimulationManager = currentVolume->GetLogicalVolume()->GetFastSimulationManager();
    257       if( fFastSimulationManager )
    258     { 
    259       // Ask for trigger:
    260       fFastSimulationTrigger = fFastSimulationManager->PostStepGetFastSimulationManagerTrigger(track, fGhostNavigator);
    261       if( fFastSimulationTrigger )
    262         { 
    263           // Take control over stepping:
    264           *condition = ExclusivelyForced;
    265           return 0.0;
    266         }
    267     }
    268     }
    269   
    270   // -- no fast simulation occuring there:
    271   *condition = NotForced;
    272   return DBL_MAX;
    273 }


Looks to me like the fastsim model must take reponsibility for 
everything inside the body_log that fulfils ModelTrigger.
But it doest look like its handling reflections or absorption 
off the innards ? 

HMM: suspect that the junoPMTOpticalModel::ModelTrigger is too 
tightly defined such that it will not handle rays that bounce off PMT innards 
in lower hemi and approach the photocathode from inside. 

TODO: standalone debugging, following photon histories in usual Opticks recorder way

So ModelTrigger is critical::

    080 G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
     81 {
     82 
     83     if(fastTrack.GetPrimaryTrack()->GetVolume() == _inner2_phys){
     84         return false;
     85     }

     //   exclude lower hemi, 
     //   all the PMT innards are in lower hemi so does that 
     //   mean that ordinary G4OpBoundaryProcess kicks in for 
     //   reflections off the innards ? 

     86 
    ...
    100 
    101 #ifndef PMTSIM_STANDALONE
    102     if(whereAmI == kInGlass){
    103         dist1 = _inner1_solid->DistanceToIn(pos, dir);
    104         dist2 = _inner2_solid->DistanceToIn(pos, dir);
    105 
    106         if(dist1 == kInfinity){
    107             return false;
    108         }else if(dist1>dist2){
    109             return false;
    110         }else{
    111             return true;
    112         }

    ///   when in the pyrex only true (and triggered) for when the ray intersects _inner1_solid more closely than _inner2_solid
    ///   which means the ray is pointed at the upper hemi  

    113     }else{
    114         dist1 = _inner1_solid->DistanceToOut(pos, dir);
    115         dist2 = _inner2_solid->DistanceToIn(pos, dir);
    116 
    117         if(dist2 == kInfinity){
    118             return true;
    119         }

    ///    when in vacuum only true when ray misses the lower hemi _inner2_solid
    ///    which means that the ray origin is not inside lower hemi and ray direction
    ///    is not pointed towards lower hemi
    ///
    ///    THAT SEEMS TOO TIGHT A REQUIREMENT 
    ///

    120     }
    121     return false;
    122 
    123 #else
    124     dist1 = whereAmI == kInGlass ? _inner1_solid->DistanceToIn(pos, dir) : _inner1_solid->DistanceToOut(pos, dir);
    125     dist2 = whereAmI == kInGlass ? _inner2_solid->DistanceToIn(pos, dir) : _inner2_solid->DistanceToIn(pos, dir) ;
    126 
    127     bool ret =  whereAmI == kInGlass ?
    128                        (( dist1 == kInfinity || dist1 > dist2 ) ? false : true )
    129                 :
    130                        (( dist2 == kInfinity ) ? true : false )
    131                 ;
    132 





Tree of dependencies
------------------------

from gather.sh::


   Matrix.h  : TComplex.h              # MATRIX, Matrix
   Matrix.cc : Matrix.h                # four TComplex in one MATRIX

   Material.h  : TComplex.h 
   Material.cc : Material.h            #  static material map, std::string name and one TComplex n (refractive index) 

   # trivial to replace Material with small static array of TComplex 
   # as there are only a few materials. Can also replace the std::string name 
   # with implicit array index.  
   #
   # Actually : the Material class seems pointless, just use rindex member for each layer 
   #

   Layer.h   : Matrix.h Material.h      # Layer, ThickLayer, ThinLayer 
   Layer.cc  : Layer.h                  

   # two Matrix pointers Ms, Mp 
   # one Material pointer
   # layer type : enum LayerType { fThin, fThick };  
   # parameter struct with 6 TComplex

       struct LayerParameter
        {   
            TComplex sin_theta;
            TComplex cos_theta;
            TComplex rs_ij;
            TComplex rp_ij;
            TComplex ts_ij;
            TComplex tp_ij;     // 6*2 = 12 elem (plus 2*2 -> 12+4 = 16)
        };  

   # ThinLayer has thickness double, ThickLayer does not
   # trivial to use single Layer type with 0./-1. thickness for ThickLayer 

   # ctor takes std::string argument used for material lookup, 
   # trivial to replace with material index 

   # so Layer comprises : 6 + 4 + 4 TComplex, material_index, thickness (with convention to indicate Thick )    

   # for persistency purposes should pad the 6 to 8 and use those for material_iidex, thickness
   # so array shape for layer becomes the below where each element is (real, imag) 2-tuple  

        sin_theta  cos_theta  material_idx thickness     8 
        rs_ij      rp_ij      ts_ij        tp_ij         8
        Ms_00      Ms_01      Ms_10        Ms_11         8
        Mp_00      Mp_01      Mp_10        Mp_11         8

   # overall array shape (4,4) complex or (4,4,2) when spelling out (real, imag)


    In [1]: a = np.eye(4, dtype=np.complex)

    In [2]: a
    Out[2]: 
    array([[1.+0.j, 0.+0.j, 0.+0.j, 0.+0.j],
           [0.+0.j, 1.+0.j, 0.+0.j, 0.+0.j],
           [0.+0.j, 0.+0.j, 1.+0.j, 0.+0.j],
           [0.+0.j, 0.+0.j, 0.+0.j, 1.+0.j]])

    In [3]: a.shape
    Out[3]: (4, 4)

    In [4]: a.view(np.float64)
    Out[4]: 
    array([[1., 0., 0., 0., 0., 0., 0., 0.],
           [0., 0., 1., 0., 0., 0., 0., 0.],
           [0., 0., 0., 0., 1., 0., 0., 0.],
           [0., 0., 0., 0., 0., 0., 1., 0.]])

    In [5]: a.view(np.float64).shape
    Out[5]: (4, 8)

    In [6]:  




   OpticalSystem.h  :   Layer.h         # vector of layers with ThickLayer top_layer bot_layer    
   OpticalSystem.cc :   TString.h       # TMath::Sin TMath::Cos TMath::Sqrt TComplex::Sqrt TString?Form 

   Note pointlessly involved layer setup with AddLayer inserting thin layers before the end. 
   Could simply model as array and populate in layer order.  

   void OpticalSystem::Initialize(double wl, double theta)   
   # meat of layer setup setting parameters and matrix


   MultiFilmModel.h  :  TComplex.h           #   ART
   MultiFilmModel.cc :  MultiFilmModel.h Matrix.h OpticalSystem.h    # contains optical_system and Matrix Ms Mp  TComplex::Conjugate

   MultiFilmModel::MultiFilmModel(int n_layer)
       instanciate OpticalSystem(n_layer) and Ms Mp matrix  

   MultiFilmModel::Calculate()
       optical_system->Initialize(wavelength, theta);

       product of matrix from all the layers    

       form the ART double param from the matrix product and layer param   

       0040         OpticalSystem* optical_system;
         41 
         42         double wavelength;
         43         double theta;
         44 
         45         ART art;
         46 
         47         Matrix* Ms;
         48         Matrix* Mp;



   junoPMTOpticalModel.h  : many G4 headers, Sniper, Svcs and MultiFilmSimSvc/MultiFilmModel.h   m_multi_film_model
   junoPMTOpticalModel.cc : m_multi_film_model = new MultiFilmModel(4);

   0285 void junoPMTOpticalModel::CalculateCoefficients()
    286 {
    287     G4complex one(1., 0.);
    288     _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1);
    289     _sin_theta4 = _n1 * _sin_theta1/_n4;
    290     _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);
    291 
    292     m_multi_film_model->SetWL(_wavelength/m);
    293     m_multi_film_model->SetAOI(_aoi);
    294 
    295     m_multi_film_model->SetLayerPar(0, _n1);
    296     m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    297     m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    298     m_multi_film_model->SetLayerPar(3, _n4);
    299     ART art1 = m_multi_film_model->GetART();
    300     fR_s = art1.R_s;
    301     fT_s = art1.T_s;
    302     fR_p = art1.R_p;
    303     fT_p = art1.T_p;
    304 
    305     m_multi_film_model->SetLayerPar(0, n_glass);
    306     m_multi_film_model->SetLayerPar(1, n_coating, k_coating, d_coating);
    307     m_multi_film_model->SetLayerPar(2, n_photocathode, k_photocathode, d_photocathode);
    308     m_multi_film_model->SetLayerPar(3, n_vacuum);
    309     ART art2 = m_multi_film_model->GetNormalART();
    310     fR_n = art2.R;
    311     fT_n = art2.T;
    312 }



Background
------------

* :google:`optics stokes jones mueller`

* https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture17_0.pdf

* https://en.wikipedia.org/wiki/Jones_calculus

In optics, polarized light can be described using the Jones calculus,[1]
discovered by R. C. Jones in 1941. Polarized light is represented by a Jones
vector, and linear optical elements are represented by Jones matrices. When
light crosses an optical element the resulting polarization of the emerging
light is found by taking the product of the Jones matrix of the optical element
and the Jones vector of the incident light. Note that Jones calculus is only
applicable to light that is already fully polarized. Light which is randomly
polarized, partially polarized, or incoherent must be treated using Mueller
calculus. 

Thus, the Jones vector represents the amplitude and phase of the electric field
in the x and y directions. 

The sum of the squares of the absolute values of the two components of Jones
vectors is proportional to the intensity of light. It is common to normalize it
to 1 at the starting point of calculation for simplification. It is also common
to constrain the first component of the Jones vectors to be a real number. This
discards the overall phase information that would be needed for calculation of
interference with other beams. 


* :google:`jones calculus thin films`

* https://home.strw.leidenuniv.nl/~keller/Teaching/China_2011/China2011_L04_ThinFilms.pdf
* ~/opticks_refs/China2011_L04_ThinFilms.pdf

sufficient to look at complex scalar quantities instead of full 3-D
vector since electric field is perpendicular to wave vector and in
plane of incidence

phase factor for forward propagating wave:
 
           2 pi     ~
  delta =  ----   * n1 d1 cos(theta1) 
           lambda



Jones Waveplate Matrix

* https://www.youtube.com/watch?v=y1KoLLk9C4U


Andrew Berger : Large number of Optics Videos

* https://www.youtube.com/channel/UCmex3hKJjm3UN3l2Ie9rJrQ
* https://www.youtube.com/channel/UCmex3hKJjm3UN3l2Ie9rJrQ/videos


3 layer system:

* https://www.youtube.com/watch?v=eYQjjx-MEZc



* https://physlab.org/wp-content/uploads/2016/07/Ch6-BYUOpticsBook_2013.pdf
* ~/opticks_refs/Ch6-BYUOpticsBook_2013.pdf

Reflection from an interface:

   |  -r_p   0   |
   |   0     r_s |

Transmission thru an interface

   |   t_p   0   |
   |   0     t_s |

   

* https://arxiv.org/pdf/2204.02703.pdf
* ~/opticks_refs/JUNO_MultiFilm_PMT_Optical_Model_2204.02703.pdf


tmm : transfer matrix method
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* https://arxiv.org/abs/1603.02720
* ~/opticks_refs/Byrnes_Multilayer_optical_calculations_1603.02720.pdf

* https://pypi.org/project/tmm/
* https://github.com/sbyrnes321/tmm
* http://sjbyrnes.com/science-programming.html
* http://sjbyrnes.com/multilayer_film_optics_programs.html

* :google:`bo sernelius lecture notes pdf`

* http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/TTM/TTM_Sernelius.pdf
* ~/opticks_refs/TTM_Sernelius.pdf


::

    In [1]: np.arcsin(2)
    /Users/blyth/miniconda3/bin/ipython:1: RuntimeWarning: invalid value encountered in arcsin
      #!/Users/blyth/miniconda3/bin/python
    Out[1]: nan

    In [2]: from numpy.lib.scimath import arcsin

    In [3]: arcsin(2)
    Out[3]: (1.5707963267948966+1.3169578969248166j)

    In [4]: np.sin(arcsin(2))
    Out[4]: (1.9999999999999998+1.0605752387249067e-16j)

    In [5]: EPSILON = sys.float_info.epsilon

    In [6]: EPSILON
    Out[6]: 2.220446049250313e-16



* http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/TTM/Fresnel_Sernelius.pdf

* https://en.wikipedia.org/wiki/Transfer-matrix_method_(optics)

* :google:`Abeles matrix formalism`

* https://www.fzu.cz/~kuzelp/Optics/Lecture6.pdf



* https://www.youtube.com/c/JordanEdmundsEECS/videos

  Lots of well explained optics videos 

* https://www.youtube.com/watch?v=XuSxmb9-viY

  Jordan Edmunds 

  Explains the transfer matrix formalism : can think of matrix for the medium separate from matrix for interfaces
  Decalares the vectors are for (Er El)  fields travelling to right and left 

  So at start of the stack:: 

      | E_incident   |
      | E_reflected  |

  At end of the stack::

      | E_transmitted |      # no left going expected   
      |      0        |


  System::  

      | E_incident   |  =    |  M00    M01  |  |   E_trans  |  
      | E_reflected  |       |  M10    M11  |  |    0       |



      E_incident = M00 E_trans          E_trans/E_incident = 1/M00

      E_reflected = M10 E_trans         E_refl/E_incident = M10/M00 


* https://www.youtube.com/watch?v=dE7Yi3u9cvI

  Transmission Matrix::
            
              
         |  E0_r |         1    |   1     r01  |   |  E1_r |
         |       |   =   ------ |              |   |       |
         |  E0_l |        t01   |  r01     1   |   |  E1_l |  

 
  Using    t01t10 - r01r10 = 1 

  Works for S or P by using the corresponding r and t 


* https://www.youtube.com/watch?v=BX_-1ei12sU

  Propagation Matrix::

  .         
  EA(x) = E0 exp(i(wt-kx))

  EA(x+L) = E0 exp(i(wt-k(x+L))) = E0 exp(i(wt-kx)) exp(-ikL) = EA(x) exp(-ikL)

   EA(x+L)
   ------- = exp(-ikL)
    EA(x)

    EB  = EA exp(-ikL)

    EA = EB exp(ikL)

  | EA_r |     |   exp(i k1 L1)      0          | |  EB_r |
  |      |  =  |                                | |       |
  | EA_l |     |      0         exp(-i k1 L1)   | |  EB_l |






Q:Any way to factor off a constant part of the calculation ?
----------------------------------------------------------------


junoPMTOpticalModel.cc
------------------------


* UGLY : for every G4FastStep lots of lookups and model rejig because indices depend in wavelength
* it would be more efficient and cleaner for the model to hold arrays of properties for all wavelengths

  * the reason is that are having to do the lookups for every steps of every photon
  * of course would need to do lookups from the arrays, but at least that would
    prevent rebuilding the model from scratch 

::


    165 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
    166 {
    167     const G4Track* track = fastTrack.GetPrimaryTrack();
    168 
    169     int pmtid  = get_pmtid(track);
    170     int pmtcat = m_PMTParamSvc->getPMTCategory(pmtid);
    171    
    172     _photon_energy  = energy;
    173     _wavelength     = twopi*hbarc/energy;
    174     n_glass         = _rindex_glass->Value(_photon_energy);
    175    
    176     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    177 
    178     n_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_RINDEX", _photon_energy);
    179     k_coating       = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "ARC_KINDEX", _photon_energy);
    180     d_coating       = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "ARC_THICKNESS")/m;
    181 
    182     n_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_RINDEX", _photon_energy);
    183     k_photocathode  = m_PMTSimParSvc->get_pmtcat_prop(pmtcat, "PHC_KINDEX", _photon_energy);
    184     d_photocathode  = m_PMTSimParSvc->get_pmtcat_const_prop(pmtcat, "PHC_THICKNESS")/m;
    185 
    186     if(whereAmI == kInGlass){
    187         _n1 = n_glass;
    188         _n2 = n_coating;
    189         _k2 = k_coating;
    190         _d2 = d_coating;
    191         _n3 = n_photocathode;
    192         _k3 = k_photocathode;
    193         _d3 = d_photocathode;
    194         _n4 = n_vacuum;
    195     }else{
    196         _n1 = n_vacuum;
    197         _n2 = n_photocathode;
    198         _k2 = k_photocathode;
    199         _d2 = d_photocathode;
    200         _n3 = n_coating;
    201         _k3 = k_coating;
    202         _d3 = d_coating;
    203         _n4 = n_glass;
    204 
    205         _qe = 0.;
    206     }
    207     pos  += dist1*dir;
    208     time += dist1*_n1/c_light;
    209 
    210     UpdateTrackInfo(fastStep);
    211 
    212     fastTrack.GetPrimaryTrack()->GetStep()
    213         ->GetPostStepPoint()->SetStepStatus(fGeomBoundary);
    214 
    215     norm = _inner1_solid->SurfaceNormal(pos);
    216     if(whereAmI == kInGlass){
    217         norm *= -1.0;
    218     }
    219 
    220     _cos_theta1 = dir*norm;
    221 
    222     if(_cos_theta1 < 0.){
    223         _cos_theta1 = -_cos_theta1;
    224         norm = -norm;
    225     }
    226     _aoi = acos(_cos_theta1)*360./twopi;
    227 
    228     CalculateCoefficients();
    229 
    230     G4double T  = 0.;
    231     G4double R  = 0.;
    232     G4double A  = 0.;
    233     G4double An = 0.;
    234     G4double escape_fac = 0.;
    235     G4double E_s2 = 0.;
    236 
    237     if(_sin_theta1 > 0.){
    238         E_s2 = (pol*dir.cross(norm))/_sin_theta1;
    239         E_s2 *= E_s2;
    240     }else{
    241         E_s2 = 0.;
    242     }
    243 
    244     T = fT_s*E_s2 + fT_p*(1.0-E_s2);
    245     R = fR_s*E_s2 + fR_p*(1.0-E_s2);
    246     A = 1.0 - (T+R);
    247 
    248     An = 1.0 - (fT_n+fR_n);
    249     escape_fac  = _qe/An;
    250 
    251     if(escape_fac > 1.){
    252         G4cout<<"junoPMTOpticalModel: QE is larger than absorption coeff."<<G4endl;
    253     }
    254 
    255     G4double rand_absorb = G4UniformRand();
    256     G4double rand_escape = G4UniformRand();
    257 
    258     if(rand_absorb < A){
    259         // absorbed
    260         fastStep.ProposeTrackStatus(fStopAndKill);
    261         if(rand_escape<escape_fac){
    262         // detected
    263             fastStep.ProposeTotalEnergyDeposited(_photon_energy);
    264         }


Because the indices depend on wavelength are rejiging the model at every step:: 

    285 void junoPMTOpticalModel::CalculateCoefficients()
    286 {
    287     G4complex one(1., 0.);
    288     _sin_theta1 = sqrt(1.-_cos_theta1*_cos_theta1);
    289     _sin_theta4 = _n1 * _sin_theta1/_n4;
    290     _cos_theta4 = sqrt(one-_sin_theta4*_sin_theta4);
    291 
    292     m_multi_film_model->SetWL(_wavelength/m);
    293     m_multi_film_model->SetAOI(_aoi);
    294 
    295     m_multi_film_model->SetLayerPar(0, _n1);
    296     m_multi_film_model->SetLayerPar(1, _n2, _k2, _d2);
    297     m_multi_film_model->SetLayerPar(2, _n3, _k3, _d3);
    298     m_multi_film_model->SetLayerPar(3, _n4);
    299     ART art1 = m_multi_film_model->GetART();
    300     fR_s = art1.R_s;
    301     fT_s = art1.T_s;
    302     fR_p = art1.R_p;
    303     fT_p = art1.T_p;
    304 
    305     m_multi_film_model->SetLayerPar(0, n_glass);
    306     m_multi_film_model->SetLayerPar(1, n_coating, k_coating, d_coating);
    307     m_multi_film_model->SetLayerPar(2, n_photocathode, k_photocathode, d_photocathode);
    308     m_multi_film_model->SetLayerPar(3, n_vacuum);
    309     ART art2 = m_multi_film_model->GetNormalART();
    310     fR_n = art2.R;
    311     fT_n = art2.T;
    312 }



_qe and "jcv PMTSimParamSvc"
------------------------------

::

    176     _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);


    epsilon:issues blyth$ jgr get_pmtid_qe
    ./Simulation/DetSimV2/PMTSim/src/junoPMTOpticalModel.cc:    _qe             = m_PMTSimParSvc->get_pmtid_qe(pmtid, energy);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        qe = (m_enable_optical_model && pmtID<300000) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
    ./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h:     virtual double get_pmtid_qe(int pmtid, double energy) = 0;
    ./Simulation/SimSvc/IPMTSimParamSvc/IPMTSimParamSvc/IPMTSimParamSvc.h:    // virtual std::shared_ptr<G4MaterialPropertyVector>  get_pmtid_qe_vs_energy(int pmtid) = 0;
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h:  double get_pmtid_qe(int pmtid, double energy);
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.h:  //std::shared_ptr<G4MaterialPropertyVector> get_pmtid_qe_vs_energy(int pmtid);
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:           double qe = get_pmtid_qe(pmtID,edep);
    ./Simulation/SimSvc/PMTSimParamSvc/src/PMTSimParamSvc.cc:double PMTSimParamSvc::get_pmtid_qe(int pmtid, double energy){
    epsilon:junosw blyth$ 


Looks too complicated to reproduce starting from property files, so need to harvest with::

    void PMTSimParamSvc::getQEData(std::vector<double>& qe_data, double en0, double en1, unsigned num_edep  )


* TODO: add SSim/NPFold/NP functionality to collect such data arrays into the SSim NPFold 
 








