Layr.rst : TMM Transfer Matrix Method Modelling Stacks of Thin Layers
========================================================================

Objective
-----------

Explore thin layer stack optics math using TMM "Transfer Matrix Method" 
by simplifying into a single header and coding in a style amenable 
to being ported to GPU 


Q: How to connect polarizarion vectors before and after with the TMM ?
---------------------------------------------------------------------------


TODO: Do a single interface calc using TMM formalism and compare with ordinary approach
-----------------------------------------------------------------------------------------


References for Thin Film Optics Using "Transfer Matrix Method" (aka TMM)
----------------------------------------------------------------------------

* https://indico.cern.ch/event/981823/contributions/4304807/attachments/2250565/3817610/poster_725.pdf
* ~/opticks_refs/yaoguang_ttm_poster_725.pdf


* https://en.wikipedia.org/wiki/Thin-film_optics
* https://en.wikipedia.org/wiki/Transfer-matrix_method_(optics)
* https://www.patarnott.com/atms749/pdf/FresnelEquations.pdf

* https://arxiv.org/abs/1603.02720
* ~/opticks_refs/Byrnes_Multilayer_optical_calculations_1603.02720.pdf


* https://pypi.org/project/tmm/
* https://github.com/sbyrnes321/tmm
* http://sjbyrnes.com/science-programming.html
* http://sjbyrnes.com/multilayer_film_optics_programs.html

* :google:`bo sernelius lecture notes pdf`

* http://www.phys.ubbcluj.ro/~emil.vinteler/nanofotonica/TTM/TTM_Sernelius.pdf
* ~/opticks_refs/TTM_Sernelius.pdf


TMM in a nutshell
---------------------

The vector 2-tuples are for left-going and right-going waves:: 
       
   | E_inc |     | M00    M01 | | E_tra |
   |       |  =  |            | |       |
   | E_ref |     | M10    M11 | |  0    |

   E_inc  = M00 E_tra 

   E_ref  = M10 E_tra 

         E_ref        M10
   r  =  -----   =   -----
         E_inc        M00

         E_tra         1
   t =  -------  =   ------
         E_inc        M00 


TMM Explanations
-------------------

Best explanation of TMM found is on YouTube from Jordan Edmunds

* https://www.youtube.com/watch?v=XuSxmb9-viY

Explains the transfer matrix formalism 

* think of matrix for the medium separate from matrix for interfaces
* 2-vectors are for (E_right E_left) 

Start of the stack:: 

   | E_incident   |
   | E_reflected  |

End of the stack::

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




From amplitude to power relations : for relectance R and tranmittance T
--------------------------------------------------------------------------

R : simpler because same medium and angle 

* https://en.wikipedia.org/wiki/Fresnel_equations  has _T_s 
* https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture13_0.pdf




CUDA standin for std::complex and arithmetic functions : currently thrust::complex 
------------------------------------------------------------------------------------

Need complex handling equivalent to::

    std::conj  # these two are trivial
    std::norm
    std::sin   # these need to be "official" :google:`CUDA complex arithmetics`
    std::cos
    std::sqrt
    std::exp

Contenders:

* cuComplex.h : looks real awkward and limited

  * https://stackoverflow.com/questions/9860711/cucomplex-h-and-exp

* https://thrust.github.io/doc/group__complex__numbers.html

  * looks like thrust::complex can do everything needed, and its included with old CUDA
  * /usr/local/cuda/include/thrust/complex.h 
  * examples/UseThrust/basic_complex.sh 
  * THIS IS THE NOW 

* https://github.com/NVIDIA/libcudacxx
* https://nvidia.github.io/libcudacxx/releases.html

  * suggests inclusion of cuda/std/complex starts from CUDA 11.3 
  * THIS IS PROBABLY THE FUTURE 



TODO : more realistic CPU testing by loading actual refractive indices and thicknesses
-----------------------------------------------------------------------------------------

* not in ~/.opticks/GEOM/J004
* need to add some property harvesting from m_PMTSimParSvc

jcv junoPMTOpticalModel::

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


    036         void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
     37         IPMTSimParamSvc* getPMTSimParamSvc() const { return m_PMTSimParSvc; }
     38 
     39         void setPMTParamSvc(IPMTParamSvc* svc) { m_PMTParamSvc = svc; }
     40         IPMTParamSvc* getPMTParamSvc() const { return m_PMTParamSvc; }

    093         IPMTParamSvc* m_PMTParamSvc;
     94         IPMTSimParamSvc* m_PMTSimParSvc;
     95         MultiFilmModel* m_multi_film_model;


    epsilon:junosw blyth$ jgr setPMTSimParamSvc
    ./Simulation/DetSimV2/PMTSim/include/junoPMTOpticalModel.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* svc) { m_PMTSimParSvc = svc; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setPMTSimParamSvc(IPMTSimParamSvc* para){ m_PMTSimParsvc=para; }
    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);
    epsilon:junosw blyth$ 

jcv HamamatsuR12860PMTManager::

    1000     m_pmt_sim_param_svc = 0;
    1001     LogInfo << "Retrieving PMTSimParamSvc." << std::endl;
    1002     SniperPtr<IPMTSimParamSvc> simsvc(*getParent(), "PMTSimParamSvc");
    1003     if(simsvc.invalid()){
    1004         LogError << "Can't get PMTSimParamSvc. We can't initialize PMT." << std::endl;
    1005         assert(0);
    1006         exit(EXIT_FAILURE);
    1007     }else{
    1008         LogInfo <<"Retrieve PMTSimParamSvc successfully." << std::endl;
    1009         m_pmt_sim_param_svc = simsvc.data();
    1010     }
    1011     pmtOpticalModel->setPMTSimParamSvc(m_pmt_sim_param_svc);

jcv PMTSimParamSvc::

    1278 double PMTSimParamSvc::get_pmtcat_prop(int pmtcat, const std::string& prop_name, double val){
    1279     assert( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1280 
    1281     auto iter1 = m_PMT_MPT.find(pmtcat);
    1282     assert(iter1 != m_PMT_MPT.end());
    1283     auto iter2 = iter1->second.find(prop_name);
    1284     assert(iter2 != iter1->second.end());
    1285 
    1286     return iter2->second->Value(val);
    1287 }
    1288 
    1289 double PMTSimParamSvc::get_pmtcat_const_prop(int pmtcat, const std::string& prop_name){
    1290     bool check = ( pmtcat >= (int)kPMT_Unknown && pmtcat <= (int)kPMT_NNVT_HighQE && pmtcat + 1 >= 0 );
    1291     if (!check) {
    1292         LogError << "Failed to find the PMTCAT Const Prop with "
    1293                  << " pmtcat: " << pmtcat
    1294                  << " prop_name: " << prop_name
    1295                  << std::endl;
    1296         return 0.0;
    1297     }
    1298 
    1299     auto iter1 = m_PMT_CONST.find(pmtcat);
    1300     if (iter1 != m_PMT_CONST.end()) {
    1301         auto iter2 = iter1->second.find(prop_name);
    1302         if (iter2 != iter1->second.end()) {
    1303             return iter2->second;
    1304         }
    1305     }
    1306 
    1307     LogError << "Failed to find the PMTCAT Const Prop with "
    1308              << " pmtcat: " << pmtcat
    1309              << " prop_name: " << prop_name
    1310              << std::endl;
    1311 
    1312     return 0.0;
    1313 }


::

    343   std::map<int, std::map<std::string, G4MaterialPropertyVector*>> m_PMT_MPT;
    344   std::map<int, std::map<std::string, G4double>> m_PMT_CONST;


    288 bool PMTSimParamSvc::init_default() {
    289 

    0290     SniperPtr<IPMTParamSvc> svc(*getParent(), "PMTParamSvc");
     291        if (svc.invalid()) {
     292            LogError << "Can't get PMTParamSvc. We can't initialize PMT." << std::endl;
     293            assert(0);
     294         } else {
     295            LogInfo << "Retrieve PMTParamSvc successfully." << std::endl;
     296            m_PMTParamSvc = svc.data();
     297         }
     298 
     299    SniperPtr<IMCParamsSvc> mcgt(getParent(), "MCParamsSvc");
     300    if (mcgt.invalid()) {
     301       std::cout << "Can't find MCParamsSvc." << std::endl;
     302       assert(0);
     303    }

    0322   helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_RINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_RINDEX");
     323   helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["ARC_KINDEX"], mcgt.data(), "PMTProperty.R12860.ARC_KINDEX");
     324   helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_RINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_RINDEX");
     325   helper_pmt_mpt(m_PMT_MPT[kPMT_Hamamatsu]["PHC_KINDEX"], mcgt.data(), "PMTProperty.R12860.PHC_KINDEX");

    0251 bool PMTSimParamSvc::helper_pmt_mpt(G4MaterialPropertyVector*& vec, IMCParamsSvc* params, const std::string& name){
     252     IMCParamsSvc::vec_d2d props;
     253     bool st = params->Get(name, props);
     254     if (!st) {
     255         LogError << "can't find material property: " << name << std::endl;
     256         return false;
     257     }
     258     vec = new G4MaterialPropertyVector(0,0,0);
     259 
     260     int N = props.size();
     261     if (!N) {
     262         LogError << "empty material property: " << name << std::endl;
     263         return false;
     264     }
     265     for (int i = 0; i < N; ++i) {
     266         vec->InsertValues(props[i].get<0>(), props[i].get<1>());
     267     }
     268 
     269 
     270     LogDebug<<"******** name = "<< name<<" ***********" <<std::endl;
     271     for (int i = 0; i < N; i++){
     272           LogDebug<<"energy = " << vec->Energy(i) <<" value = " << (*vec)[i] <<std::endl;
     273     }
     274    
     275  
     276    return true;
     277 }

Added NP methods to duplicate this::

    NP* a = NP::ArrayFromTxt<double>("PMTProperty.R12860.PHC_KINDEX") ; 
    double v = NP::ReadKV_Value<double>("PMTProperty.R12860.THICKNESS", "THICKNESS_PHC") ;  





jcv MCParamsFileSvc::

     42 bool
     43 MCParamsFileSvc::Get(const std::string& param, vec_d2d& props)
     44 {
     45      const std::string path = GetPath( param );
     46     return get_implv1(path, props);
     47 }
         

DONE : Added low dependency access to properties by additions to NP.hh NPFold.h 
------------------------------------------------------------------------------------

Especially::

   NP::LoadFromString 
   NP::LoadFromTxtFile
   NPFold::load_dir

::

    N[blyth@localhost ~]$ l $JUNOTOP/data/Simulation/DetSim/PMTProperty/
    total 0
    0 drwxrwxr-x. 6 blyth blyth  76 Sep 27 18:32 ..
    0 drwxrwxr-x. 2 blyth blyth  45 Sep 27 18:32 WP_PMT
    0 drwxrwxr-x. 9 blyth blyth 111 Sep 27 18:32 .
    0 drwxrwxr-x. 2 blyth blyth 134 Sep 27 18:32 NNVTMCP
    0 drwxrwxr-x. 2 blyth blyth 134 Sep 27 18:32 R12860
    0 drwxrwxr-x. 2 blyth blyth  16 Sep 27 18:32 Dynode
    0 drwxrwxr-x. 2 blyth blyth  16 Sep 27 18:32 MCP
    0 drwxrwxr-x. 2 blyth blyth 134 Sep 27 18:32 NNVTMCP_HiQE
    0 drwxrwxr-x. 2 blyth blyth  35 Sep 27 18:32 HZC_3inch
    N[blyth@localhost ~]$ 




Using persisted Layr from NumPy
--------------------------------------

Each Layr has 32 elements from 16 complex numbers persisted into shape (4,4,2).  

Thickness of all layers::

    a.lls[0,:,0,0,0]  

List layer thickness and complex refractive indices::

    In [20]: np.c_[a.lls[0,:,0,0,0],a.lls[0,:,0,1]]
    Out[20]: 
    array([[  0.  ,   1.  ,   0.  ],
           [500.  ,   1.  ,   0.01],
           [500.  ,   1.  ,   0.01],
           [  0.  ,   1.5 ,   0.  ]])




TODO : devise CPU/GPU counterpart paired structs for this calculation
-------------------------------------------------------------------------

How to organize the refractive indices as function of energy for use on GPU ? 

* DONE: JPMT.h collects arrays or rindex and thickness
* DONE: qudarap/QPMT.hh/qpmt.h propel those arrays onto GPU 


Considerations:

1. enum pmt category (3,)
2. reverse stack for backwards photons 

   * same info used in reverse order 

3. rindex common energy domain or not ? 

   * close enough to glue them together in common domain 
     and remove energy from the array like with texture ?

   * hmm given that there are potentially 3*4 = 12 different energy domains
     would only be able to go for common domain by doing pre-interpolation
     (like with textures)
 
   * OR use NP::Combine NP::combine_interp to carry multiple domains 


Array layout:

0. thickness (3 pmtcat, 4 layers, 1 )    
1. rindex    (3 pmtcat, 4 layers, 2 prop ,  ~15  ,  2 )   
                                  |                 |
                                  RINDEX  1+mx_itm  dom
                                  KINDEX            val  

Could also combine the RINDEX, KINDEX within the 
item but keeping them separate is more generic for 
expansion to other situations and 
will allow an easy extension to NP::Combine to 
create these arrays. 

Also this layout could be turned into a float2 texture. 

DONE : high dimension interpolation on CPU NP::combined_interp_5 
DONE : high dimension interpolation on GPU qudarap/qpmt.h 

First 3 dimensions of rindex are equivalent to the iprop in the 
below ? How to split the API to avoid lots of duplication ?

::

    2672 
    2673 template<typename T> inline T NP::combined_interp(unsigned iprop, T x) const
    2674 {
    2675     unsigned ndim = shape.size() ;
    2677     assert( ndim == 3 && shape[ndim-1] >= 2 && iprop < shape[0] && shape[1] > 1 );
    2678     unsigned nj = shape[ndim-1] ;  // normally 2 with (dom, val)
    2679 
 

Relevant:

LayrTest.cc 
    PrepStackSpec 

NP::Combine NP::combined_interp
    CPU preparation of the arrays 

QProp.hh
qprop.h 
    will need to extend these to work with 4D arrays  


Contrast Layr.h with junosw implementation 
----------------------------------------------

::

    epsilon:~ blyth$ cd $JUNOTOP/junosw/Simulation/SimSvc/MultiFilmSimSvc
    epsilon:MultiFilmSimSvc blyth$ find . 
    .
    ./CMakeLists.txt
    ./python
    ./python/MultiFilmSimSvc
    ./python/MultiFilmSimSvc/__init__.py
    ./MultiFilmSimSvc
    ./MultiFilmSimSvc/MultiFilmModel.h
    ./src
    ./src/OpticalSystem.h
    ./src/Layer.h
    ./src/Material.h
    ./src/Layer.cc
    ./src/Matrix.h
    ./src/OpticalSystem.cc
    ./src/MultiFilmModel.cc
    ./src/Material.cc
    ./src/Matrix.cc
    epsilon:MultiFilmSimSvc blyth$ 


MultiFilmSimSvc/MultiFilmModel.h
    struct ART
    class MultiFilmModel::

        OpticalSystem* optical_system;
        double wavelength;
        double theta;
        ART art;
        Matrix* Ms; 
        Matrix* Mp; 

    REPLACED WITH : template<typename T, int N> struct Stack<T,N>   
    effectively combines MultiFilmModel, OpticalSystem

src/OpticalSystem.{h,cc}

    class OpticalSystem:: 

        ThickLayer* top_layer;
        ThickLayer* bot_layer;
        std::vector<Layer*> layers;

     REPLACED BY : struct Stack<T,N>  array of Layr:  Layr<T> ll[N]   

src/Layer.{h,cc}

    class Layer::

        LayerParameter parameter;
        Material* material;
        LayerType type;
        Matrix* Ms; 
        Matrix* Mp; 

    class ThickLayer : public Layer
    class ThinLayer : public Layer::
 
         double thickness; 

    REPLACED WITH SINGLE STRUCT : Layr and convention thick => zero thickness 

src/Material.{h,cc}

    class Material::

        std::string fName;
        TComplex n;
        static std::map<std::string, Material*> materials;
    
     REPLACED : Layr has refractive index member



What happens to the calc at glancing incidence, mct=0 ?
----------------------------------------------------------

As the angle gets more and more glancing 
the S and P matx for one of the layers blows up its values. 
Because of::

    618     // populate transfer matrices for both thick and thin layers  
    619     ll[0].reset();
    620     for(int idx=1 ; idx < N ; idx++)
    621     {
    622         const Layr<T>& i = ll[idx-1] ;
    623         Layr<T>& j = ll[idx] ;
    624 
    625         complex<T> tmp_s = one/i.ts ;
    626         complex<T> tmp_p = one/i.tp ;
    627         // at glancing incidence ts, tp approach zero : blowing up tmp_s tmp_p
    628         // which causes the S and P matrices to blow up yielding infinities at mct zero

::

    epsilon:Layr blyth$ MCT=-0.000001 ./LayrMinimal.sh 

    idx 1
    Layr
      n:(    1.9200     0.0000)s  d:   36.4900
     st:(    0.7719     0.0000)s ct:(    0.6358     0.0000)s
     rs:(   -0.4004    -0.2878)s rp:(   -0.0105     0.1893)s
     ts:(    0.5996    -0.2878)s tp:(    0.6582    -0.2205)s
    S
    | (331297.4688 -244647.9375)s (-331296.6875 -244647.3594)s |
    | (-331296.6875 244647.3594)s (331297.4688 244647.9375)s |

    P
    | (255720.4531 -188837.7812)s (-255719.4219 -188837.0156)s |
    | (-255719.4219 188837.0156)s (255720.4531 188837.7812)s |

    ...

    comp
    Layr
      n:(    0.0000     0.0000)s  d:    0.0000
     st:(    0.0000     0.0000)s ct:(    0.0000     0.0000)s
     rs:(   -1.0000    -0.0000)s rp:(   -1.0000     0.0000)s
     ts:(    0.0000     0.0000)s tp:(    0.0000    -0.0000)s
    S
    | (519205.6250 -230821.5156)s (360978.0938 -610134.4375)s |
    | (-519204.5625 230820.1875)s (-360978.4062 610133.5000)s |

    P
    | (314248.9375 56780.9961)s (-335603.5000 -440843.2188)s |
    | (-314246.8125 -56780.5156)s (335601.6875 440842.3750)s |


    ART
     R_s     1.0000 R_p     1.0000
     T_s     0.0000 T_p     0.0000
     A_s     0.0000 A_p     0.0000
     R       1.0000 T       0.0000 A       0.0000 A_R_T     1.0000
     wl    440.0000
     mct    -0.0000



Very close to zero, does not give nan::

    S
    | (455426375680.0000 -1436173467648.0000)s (381454450688.0000 -315594735616.0000)s |
    | (-455426375680.0000 1436173467648.0000)s (-381454450688.0000 315594735616.0000)s |

    P
    | (-33171656704.0000 -415557681152.0000)s (-106015178752.0000 -270847377408.0000)s |
    | (33171656704.0000 415557681152.0000)s (106015178752.0000 270847377408.0000)s |


    ART
     R_s     1.0000 R_p     1.0000
     T_s     0.0000 T_p     0.0000
     A_s    -0.0000 A_p    -0.0000
     R       1.0000 T       0.0000 A      -0.0000 A_R_T     1.0000
     wl    440.0000
     mct     0.0000


    epsilon:Layr blyth$ MCT=0.000000000001 ./LayrMinimal.sh 


At zero, get nan for ART::

    ART
     R_s        nan R_p        nan
     T_s        nan T_p        nan
     A_s        nan A_p        nan
     R          nan T          nan A          nan A_R_T        nan
     wl    440.0000
     mct     0.0000


    epsilon:Layr blyth$ MCT=0 ./LayrMinimal.sh 



This blowup at glancing explains the float/double and gpu/cpu differences. 




TMM Fast 
------------

* https://opg.optica.org/josaa/fulltext.cfm?uri=josaa-39-6-1007&id=472723

* https://arxiv.org/abs/2111.13667

* https://github.com/MLResearchAtOSRAM/tmm_fast

* https://github.com/MLResearchAtOSRAM/tmm_fast/blob/main/tmm_fast/vectorized_tmm_dispersive_multistack.py

The key contribution to the core functionality of the TMM package is the
parallelized handling of the characteristic matrix that reduces computational
time. The matrix M consists of three separate matrices: matrix A, which
encompasses the accumulated phase, and the two matrices holding the
coefficients of reflection and transmission, respectively. They are of shape
[num_wavelength,num_incident_angles,num_layers,2,2]

To get the characteristic matrix M, np.einsum
method allows us to specify multiplication and contractions of different
dimensions easily:

::

    1  M_l = np.zeros((num_lambda, num_angles, num_layers, 2, 2),dtype = complex) 
    2  F = r_list[:, 1:]

    3  M_l[:,:,1:-1,0,0] = np.einsum(’hji,ji-> jhi’, 1/A, 1/t_list[:, 1:]) 
    4  M_l[:,:,1:-1,0,1] = np.einsum(’hji,ji-> jhi’, 1/A, F/t_list[:, 1:])
    5  M_l[:,:,1:-1,1,0] = np.einsum(’hji,ji-> jhi’, A, F/t_list[:, 1:])
    6  M_l[:,:,1:-1,1,1] = np.einsum(’hji,ji-> jhi’, A, 1/t_list[:, 1:])

    7	Mtilde = np.empty((num_angles, num_lambda, 2, 2), dtype = complex)
    8	Mtilde[:, :] = make_2x2_array(1, 0, 0, 1, dtype = complex)
    9	for i in range(1, num_layers-1):
    10	   Mtilde = np.einsum(’ijkl,ijlm-> ijkm’, Mtilde, M_l[:,:,i])








