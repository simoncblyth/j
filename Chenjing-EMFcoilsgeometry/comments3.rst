comments3
===========


Hi Jing,

Apologies for the long delay from travel + grant applications
that took all my time these past few weeks.

The flight path functionality I added to Opticks has allowed me to fly 
around all the EMF rings (horizontal and slanted) doing a visual inspection.
Good news : I no longer see any overlaps. 
How did you succeed to avoid all the overlaps ? 
There were many previously. 
Describing your techniques briefly into this MR would be useful.

I repeated the visual check of bars crossing the Tyvek::

    FULLSCREEN=0 MOI=0,0,10000,1000 EYE=0,0,-5 UP=0,1,0 ELV=sOuterReflectorInCD_T,^s_EMF cxr_min.sh

Now none of the bars are doing that.



Solid and volume counts are acceptable::

    (ok) A[blyth@localhost CSGFoundry]$ grep s_EMF meshname.txt | wc -l
    116

    (ok) A[blyth@localhost CSGFoundry]$ ~/o/CSG/tests/CSGFoundryLoadTest.sh | grep s_EMF | wc -l
    572


Via WeChat You mentioned simulation times increasing from 46 minutes to 52 minutes.
Given how much geometry is added that ~10% level of increase seems acceptable.








Look at controls
---------------------

::


     155         if (m_emf_coils_system) {
     156             WaterPoolConstructionEMF emf(logicWaterPool,
     157                                          m_emfSteelReflectivity,
     158                                          m_emf_cd_outer_tyvek_radius,
     159                                          m_emf_bar_tyvek_clearance);
     160             emf.makeEMFSupport_Polycone(m_emf_support_bars);
     161             emf.makeEMFCoilHolders_Polycone();
     162         }






