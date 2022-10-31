junoPMTOpticalModel
======================

Questions
-----------

1. in junoPMTOpticalModel::DoIt why is _qe set to zero for vacuum to glass photons ?
   this means that will get no hits from photons that enter the PMT and get reflected 
   back to the photocathode ?  



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
 








