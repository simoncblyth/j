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


