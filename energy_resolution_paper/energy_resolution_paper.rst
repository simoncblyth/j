energy_resolution_paper
=========================

From Liang Zhan, overleaf link::

    Hi Simon,

    https://latex.ihep.ac.cn/9177974132qzxcsxgvhhby
    You can also download the tex from this link. Note the latest version is main_v3.tex

    Best Regards,
    Liang

::

    https://latex.ihep.ac.cn/project/6285f2dd94cce10091d336e6


Commented
----------

"The roughness of the SS surface is set to 0.2 in simulation. "

I removed the above sentence, as without discussion of 
the "roughness" model this sentence has no information.
Also, in any case I recently (during my covid isolation) 
looked into the Geant4 SigmaAlpha of surfaces in the simulation, 
to check if I needed to port it to Opticks. I concluded that 
the SigmaAlpha is actually doing nothing in the current simulation. 

This can be seen from the G4OpBoundaryProcess DielectricMetal code. 
(actually should look at Custom4 C4OpBoundaryProcess as that is being 
used, but they are very similar).

With unified model surfaces the ChooseReflection method always 
sets theStatus LambertianReflection when prob_ss prob_sl prob_bs 
are all at their defaults of zero. 

So the default LambertianReflection gets used for unified/ground 
surfaces. To change that it would be necessary to setup 
SpikeReflection/BackScattering/LobeReflection via their properties::
  
   kSPECULARLOBECONSTANT
   kSPECULARSPIKECONSTANT
   kBACKSCATTERCONSTANT

I confirmed this by a test run with break point set to C4OpBoundaryProcess::GetFacetNormal
(C4 for Custom4) which never gets run. 

There is another const property, that changes DielectricDielectric::

    kSURFACEROUGHNESS

    


https://geant4-forum.web.cern.ch/t/roughness-of-surfaces/4095

* ~/opticks_refs/UNIFIED_model_diagram.png
* ~/opticks_refs/UNIFIED_model_diagram.txt





Scattering in Acrylic or Water
--------------------------------

I changed a factual error regarding scattering in Water and Acrylic

OLD::

    However, the scattering process within these materials 
    is not currently considered in the model.

NEW::

    Scattering within Water uses Rayleigh scattering lengths calculated from the refractive index by GEANT4. 
    Scattering within Acrylic is currently neglected.


Materials named "Water" that have RINDEX property are special cased by 
Geant4 in G4OpRayleigh::CalculateRayleighMeanFreePaths. 
It automatically calculates a Rayleigh scattering length directly into 
the physics table of the G4OpRayleigh process.
Note that this special casing does not apply to "vetoWater"
as the name is not "Water" so despite "vetoWater" having the same RINDEX 
as "Water" no Rayleigh scattering will happen for it.
A simple way to avoid this would be to change the vetoWater name into Water. 




Background reading
-------------------

* https://ocw.mit.edu/courses/8-701-introduction-to-nuclear-and-particle-physics-fall-2020/e0c43345709c1e799efd2238d7d41a77_9QPqYAr-Zsc.pdf

* https://ocw.mit.edu/courses/8-701-introduction-to-nuclear-and-particle-physics-fall-2020/



Technical Issues
-------------------

From Table 1.2 of Conceptual Design Report
the GW total of 6 Yangjian and 4 Taishang cores
sum to 6*2.9+4*4.6 = 35.8 GW 


::

    (298) 4.1 The roughness of the SS surface is set to 0.2 in simulation


This is meaningless without a discussion of the model in use. Suggest to skip.
The way the JUNO optical surfaces are setup means that the sigma_alpha settings
are doing nothing. 





