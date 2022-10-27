Layr.rst : TMM Transfer Matrix Method Modelling Stacks of Thin Layers
========================================================================

Objective
-----------

Explore thin layer stack optics math using TMM "Transfer Matrix Method" 
by simplifying into a single header and coding in a style amenable 
to being ported to GPU 

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
         

TODO: Need low dependency access to properties from::

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


