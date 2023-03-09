blyth-88-quadrant-matching.rst
=================================

* from :doc:`blyth-88-incorporation-notes`

* next :doc:`blyth-88-ModelTrigger_Debug`


Speeddial
----------

::
 
    jcv HamamatsuR12860PMTManager
    jcv NNVTMCPPMTManager



POM : Open Questions
------------------------

Thoughts while reading ~/opticks_refs/Optical_Properties_of_Bialkali_Photocathodes_Motta_and_Schonert_MPI_0408075.pdf 
and looking at the junoPOM code

* Paper talks about photocathode A,R,T surely it should talk about the A,R,T of the stack of layers ? Is that what is means ? 

  * seems not, Fig 2 R does not go to 1. at glancing incidence 
    (huh comment about that saying "first order Fresnel reflection from glass not included")
  * this makes this diffult to compare with my plots  

* JUNO POM MultiLayer stack is 4 layers (Pyrex/ARC/PHC/Vacuum) not 5 (Water/Pyrex/ARC/PHC/Vacuum). 
  Does that cause an "interpretation model matching" problem, 
  eg when trying to use the QE from another measurement to get escape fraction ? 

* The stacks are Pyrex/ARC/PHC/Vacuum NOT Water/Pyrex/ARC/PHC/Vacuum which 
  makes me suspect apples-vs-oranges issue with "escape_fac  = _qe/An" 
  because surely _qe is coming from an in Water measurement ? 
  Unless it was somehow corrected ? 

  *  ~/opticks_refs/JUNO_MultiFilm_PMT_Optical_Model_2204.02703.pdf section 4. 
     characterization measuremnents are done in LAB (linear alkylbenzene) 
     which has refractive index close to Pyrex so that provides some justification 
   
     * google: LAB 1.481-1.485 Pyrex 1.474    




WIP : Comparing U4SimulateTest.sh between corresponding N=0,1 quadrants for both hama and nnvt PMTs
------------------------------------------------------------------------------------------------------


+----------------+------------------------+--------------------------+
|                | PMT:0  (unnatural)     | PMT:1  (natural)         |  
+================+========================+==========================+
| POM:0          |                        |  #CustomG4OpBoundary     |
| (traditional)  |                        |                          | 
|                |                        |                          |   
+----------------+------------------------+--------------------------+
| POM:1          |     FastSim            |  @CustomG4OpBoundary     | 
| (ph in PMT)    |                        |                          | 
|                |          A             |           B              |   
+----------------+------------------------+--------------------------+


A vs B : manual low stats (1000) comparison (still with pmtid -1, pmtcat 0)
------------------------------------------------------------------------------

* A has many fake extras, which are expected and which complicate the comparison  

* Most prolific "A:TO BT BT SA" "B:TO BT SA"  

::

    In [8]: t.base,np.c_[qn,qi,qu][quo][:10]
    Out[8]: 
    ('/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0',
     array([[b'595', b'0', b'TO BT BT SA                                                                                     '],
            [b'105', b'3', b'TO BT BT BR BT BT SA      reflect from cathode and gets absorbed on the wall (B:TO BT BR BT SA) 
            [b'105', b'5', b'TO BT BT BT BT SR SA      enter PMT reflect off inside of back hemi and get absorbed on red collar (B:TO BT BT SR SA)
            [b'46', b'13', b'TO BT BT BT BT SR SR SR BT SA                                                                   '],
            [b'38', b'41', b'TO BT BT BT BT SR SR SR BT BT BT BT SA                                                          '],
            [b'27', b'48', b'TO BT BT BT BT SR SR SR BT BR BT SR SA                                                          '],
            [b'22', b'17', b'TO BT BT BT BT SA                                                                               '],
            [b'13', b'201', b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT SA                                                 '],
            [b'9', b'336', b'TO BT BT BT BT SR SR SA                                                                         '],
            [b'8', b'203', b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BT BT BT SA                         ']], dtype='|S96'))

Visualize A:"TO BT BT BR BT BT SA" by using the "qi" first index column of the above::
     
    APID=3 N=1 ./U4SimtraceTest.sh ana

Find photon with corresponding history in B:"TO BT BR BT SA" with fakes skipped, using "qi" first index from B below::

    BPID=2 N=1 ./U4SimtraceTest.sh ana

    APID=3 BPID=2 N=1 ./U4SimtraceTest.sh ana       ## both together shows they are on top of each other, as expected 

    APID=3 BPID=2 AOFF=0,0,10 N=1 ./U4SimtraceTest.sh ana   ## use AOFF to offset A so can distinguish A and B  


Visualize A:"TO BT BT BT BT SR SA" (enter PMT reflect off inside of back hemi and get absorbed on red collar)::

    APID=5 N=1 ./U4SimtraceTest.sh ana
    APID=5 N=0 ./U4SimtraceTest.sh ana    # because of the vacuum fakes use the N=0 geometry 

    ## that should correspond to B:"TO BT BT SR SA"  

    APID=5 AOFF=0,0,10 BPID=13 N=0 ./U4SimtraceTest.sh ana    

    ## yep but  


    In [1]:  t.base,np.c_[qn,qi,qu][quo][:10]
    Out[1]: 
    ('/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1',
     array([[b'584', b'0', b'TO BT SA                                                                                        '],
            [b'295', b'2', b'TO BT BR BT SA                                                                                  '],
            [b'28', b'13', b'TO BT BT SR SA                                                                                  '],
            (only 28 vs 105 above, TODO: pump up the stats to 1M see if significant)

            [b'16', b'49', b'TO BT BT SR SR SR SA                                                                            '],
            [b'12', b'78', b'TO BT BT SR SR SR BT BT SA                                                                      '],
            [b'11', b'84', b'TO BT BT SR SR SR BR SR SR SR SA                                                                '],
            [b'9', b'125', b'TO BT AB                                                                                        '],
            [b'9', b'20', b'TO BT BT SR SR SR BR SR SA                                                                      '],
            [b'8', b'38', b'TO BT BT SA                                                                                     '],
            [b'5', b'75', b'TO BT BT SR SR SA                                                                               ']], dtype='|S96'))




Pump up the stats : to 100k for now
--------------------------------------

* see sysrap/tests/SEvtTest_saveDir.sh for controlling saveDir


As starting to take a while to do the simulation, load prior runs with ph arg::

    N=0 POM=1 ./U4SimulateTest.sh ph  # A

    N=1 POM=1 ./U4SimulateTest.sh ph  # B



A with 100000::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'58664' b'0'  b'TO BT BT*SA*                Absorbed on cathode 
     [b'9979' b'9'   b'TO BT BT*BR*BT BT SA        Bounce off the cathode                                              ']

     [b'9697' b'2'   b'TO BT BT*BT*BT SR SA        All this lot transmit into the PMT                                  ']
     [b'5358' b'4'   b'TO BT BT BT BT SR SR SR BT SA                                                                   ']
     [b'4150' b'28'  b'TO BT BT BT BT SR SR SR BT BT BT BT SA                                                          ']
     [b'2416' b'1'   b'TO BT BT BT BT SA                                                                               ']
     [b'2359' b'39'  b'TO BT BT BT BT SR SR SR BT BR BT SR SA                                                          ']
     [b'1400' b'91'  b'TO BT BT BT BT SR SR SA                                                                         ']
     [b'1394' b'55'  b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT SA                                                 ']
     [b'642' b'136'  b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BT BT BT BT BT SA                                  ']
     [b'600' b'153'  b'TO BT BT BT BT SR SR SR BT BR BT SA                                                             ']
     [b'452' b'283'  b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT SA                                  ']
     [b'416' b'251'  b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BT BT BT SA                         ']
     [b'323' b'58'   b'TO BT BT BT BT SR SR SR BT BR BT SR SR SA                                                       ']

     9697+5358+4150+2416+2359+1400+1394+642+600+452+416+323 = 29207   AN APPROX CUTTING THE LONG TAIL 

     A  : 58664     
     R  :  9979
     T  : 29207

     TOT: 97850

     In [7]: np.set_printoptions(precision=4)
     In [8]: a = np.array([58664,9979,29207]) ; a/a.sum()
     Out[8]: array([0.5995, 0.102 , 0.2985])       ## CLOSE TO A,R,T EXPECTED 


     [b'314' b'303'  b'TO BT AB                                                                                        ']
     [b'272' b'642'  b'TO BR SA                                                                                        ']
     [b'219' b'110'  b'TO AB                                                                                           ']

     * A HAS LOTS MORE TRANSMISSION (AND LESS REFLECTION) THAN B 

::

    junoPMTOpticalModel::DoIt@359:  pmtid 0 pmtcat 0 u0 0.426916 A 0.591099 R 0.103609 A+R 0.694708 T 0.305292 D 0 status A
    junoPMTOpticalModel::DoIt@359:  pmtid 0 pmtcat 0 u0 0.568736 A 0.591099 R 0.103609 A+R 0.694708 T 0.305292 D 0 status A
    junoPMTOpticalModel::DoIt@359:  pmtid 0 pmtcat 0 u0 0.814937 A 0.591099 R 0.103609 A+R 0.694708 T 0.305292 D 0 status T
    junoPMTOpticalModel::DoIt@359:  pmtid 0 pmtcat 0 u0 0.384291 A 0.591099 R 0.103609 A+R 0.694708 T 0.305292 D 0 status A
    junoPMTOpticalModel::DoIt@359:  pmtid 0 pmtcat 0 u0 0.957711 A 0.591099 R 0.103609 A+R 0.694708 T 0.305292 D 0 status T

     
B::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 

    [[b'58653' b'0'     b'TO BT*SA*            ABSORBED ON CATHODE LOOKS CONSISTENT                                       ']
     [b'27795' b'3'     b'TO BT*BR*BT SA       HMM: 3 TIMES MORE LIKELY TO BOUNCE OFF THE CATHODE ?                       ']

     [b'3918' b'9'      b'TO BT BT SR SA                                                                                  ']
     [b'2188' b'25'     b'TO BT BT SR SR SR SA                                                                            ']
     [b'1198' b'116'    b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'1114' b'11'     b'TO BT BT SR SR SR BR SR SA                                                                      ']
     [b'1000' b'46'     b'TO BT BT SA                                                                                     ']
     [b'620' b'70'      b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'573' b'71'      b'TO BT BT SR SR SA                                                                               ']
     [b'265' b'467'     b'TO BT BT SR SR SR BR SA                                                                         ']
     [b'265' b'324'     b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ']

     [b'327' b'114'     b'TO BT AB                                                                                        ']
     [b'287' b'304'     b'TO BR SA                                                                                        ']
     [b'228' b'402'     b'TO AB                                                                                           ']


    In [1]: a = np.array([58653,27795,3918+2188+1198+1114+1000+620+573+265+265]); a/a.sum()
    Out[1]: array([0.601, 0.285, 0.114])    

    ## HMM : LOOKS LIKE A IS OK BUT R AND T ARE SWAPPED ?

    theTransmittance    0.30529 theReflectivity    0.10361 theEfficiency    0.00000


    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'51829' b'1' b'TO SA                                                                                           ']
     [b'28330' b'0' b'TO BT SA                                                                                        ']
     [b'4620' b'40' b'TO BT BT SR SA                                                                                  ']
     [b'2948' b'34' b'TO BT BR SA                                                                                     ']
     [b'2525' b'14' b'TO BT BT SR SR SR SA                                                                            ']
     [b'1923' b'65' b'TO BT BR BT SA                                                                                  ']
     [b'1352' b'143' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'1133' b'56' b'TO BT BT SA                                                                                     ']
     [b'1091' b'136' b'TO BT BT SR SR SR BR SR SA                                                                      ']
     [b'695' b'31' b'TO BT BT SR SR SA                                                                               ']
     [b'654' b'356' b'TO BT BT SR SR SR BT SA                                                                         ']
     [b'633' b'41' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'242' b'1269' b'TO BT BT SR SR SR BR SA                                                                         ']
     [b'216' b'429' b'TO AB                                                                                           ']









::

     606     // SCB treat m_custom_status:Y as a kinda boundary type 
     607     // in order to provide  : Absorption-or-Detection/FresnelReflect/FresnelRefract
     608     if( m_custom_status == 'Y' )
     609     {
     610         G4double rand = G4UniformRand();
     611        
     612         G4double A = 1. - (theReflectivity + theTransmittance) ;
     613        
     614         if ( rand < A )  // HMM: more normally rand > theReflectivity + theTransmittance 
     615         {    
     616             DoAbsorption();   // theStatus is set to Detection/Absorption depending on a random and theEfficiency  
     617         }    
     618         else         
     619         {
     620             DielectricDielectric();
     621         }
     622     }


HMM: probably need to rescale the 3-way ART theTransmittance 
into a 2-way RT to work correctly with DielectricDielectric which is 
not expecting any absorption in the interface.

HMM maybe clearer to add theAbsorption to make it explicit 


CustomG4OpBoundaryProcess::DielectricDielectric::

    1321               if (theTransmittance > 0) TransCoeff = theTransmittance;
    1322               else if (cost1 != 0.0) TransCoeff = s2/s1;
    1323               else TransCoeff = 0.0;
    1324 
    1325               if ( !G4BooleanRand(TransCoeff) ) {
    1326 
    1327                  // Simulate reflection
    1328 

    274 inline
    275 G4bool CustomG4OpBoundaryProcess::G4BooleanRand(const G4double prob) const
    276 {
    277   /* Returns a random boolean variable with the specified probability */
    278 
    279   return (G4UniformRand() < prob);
    280 }





B: After the 3-way to 2-way fix getting loadsa "TO SA"::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'51829' b'1' b'TO SA                                                                                           ']
     [b'28330' b'0' b'TO BT SA                                                                                        ']
     [b'4620' b'40' b'TO BT BT SR SA                                                                                  ']
     [b'2948' b'34' b'TO BT BR SA                                                                                     ']
     [b'2525' b'14' b'TO BT BT SR SR SR SA                                                                            ']
     [b'1923' b'65' b'TO BT BR BT SA                                                                                  ']
     [b'1352' b'143' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'1133' b'56' b'TO BT BT SA                                                                                     ']

    * have somehow disturbed non-custom boundary ?
    * fixed it, twas due to m_custom_status not being reset at start of PostStepDoIt 

B, after fix::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'58337'  b'0' b'TO BT SA                                                                                        ']
     [b'10133'  b'2' b'TO BT BR BT SA                                                                                  ']
     [b'9857'   b'3' b'TO BT BT SR SA                                                                                  ']
     [b'5478'   b'7' b'TO BT BT SR SR SR SA                                                                            ']
     [b'4112'  b'20' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'2470' b'167' b'TO BT BT SA                                                                                     ']
     [b'2289'  b'78' b'TO BT BT SR SR SR BR SR SA                                                                      ']
     [b'1418'  b'45' b'TO BT BT SR SR SA                                                                               ']
     [b'1348'  b'15' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'654'  b'254' b'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ']
     [b'570'   b'62' b'TO BT BT SR SR SR BR SA                                                                         ']
     [b'451'  b'514' b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ']
     [b'376'  b'303' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ']
     [b'359'  b'357' b'TO BT BT SR SR SR BR SR SR SA                                                                   ']
     [b'358'  b'116' b'TO BT AB                                                                                        ']
     [b'259'   b'54' b'TO BR SA                                                                                        ']
     [b'226' b'1167' b'TO AB                                                                                           ']
     [b'166'  b'131' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ']


Thats getting much closer to A::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'58664' b'0'   b'TO BT BT SA                                                                                     ']
     [b'9979' b'9'    b'TO BT BT BR BT BT SA                                                                            ']
     [b'9697' b'2'    b'TO BT BT BT BT SR SA                                                                            ']
     [b'5358' b'4'    b'TO BT BT BT BT SR SR SR BT SA                                                                   ']
     [b'4150' b'28'   b'TO BT BT BT BT SR SR SR BT BT BT BT SA                                                          ']
     [b'2416' b'1'    b'TO BT BT BT BT SA                                                                               ']
     [b'2359' b'39'   b'TO BT BT BT BT SR SR SR BT BR BT SR SA                                                          ']
     [b'1400' b'91'   b'TO BT BT BT BT SR SR SA                                                                         ']
     [b'1394' b'55'   b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT SA                                                 ']
     [b'642' b'136'   b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BT BT BT BT BT SA                                  ']
     [b'600' b'153'   b'TO BT BT BT BT SR SR SR BT BR BT SA                                                             ']
     [b'452' b'283'   b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT SA                                  ']
     [b'416' b'251'   b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BT BT BT SA                         ']
     [b'323' b'58'    b'TO BT BT BT BT SR SR SR BT BR BT SR SR SA                                                       ']
     [b'314' b'303'   b'TO BT AB                                                                                        ']
     [b'272' b'642'   b'TO BR SA                                                                                        ']
     [b'219' b'110'   b'TO AB                                                                                           ']



Quantified Statistical A-B comparison
-----------------------------------------

* HMM: Need automated statistical and quantified A-B comparison. 
* Previously did that in a highly designed and not very flexible way "ana/ab.py" 
* need a more flexibly approach : like a general tool 

BUT: this means need to remove the fakes in the A histories so they can be 
compared in an automated way 

* could do that manually for specific photon paths, but that is not practical generally
* SO: need to skip the fakes (maybe "U4Recorder_SkipSameMaterialBoundary" ?) 


How to skip fakes with U4Recorder ?
---------------------------------------

::

    N=0 POM=1 ./U4SimulateTest.sh   # unnatural geom , multifilm POM 

    U4Recorder::UserSteppingAction_Optical@474:  l.id   2 same_material_step NO  step_mm    82.5401 pre/post : Water/Pyrex pv Water_lv_pv
    U4Recorder::UserSteppingAction_Optical@474:  l.id   2 same_material_step YES step_mm     5.2876 pre/post : Pyrex/Pyrex pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id   2 same_material_step YES step_mm     0.0011 pre/post : Pyrex/Pyrex pv hama_body_phys
    U4Recorder::PostUserTrackingAction_Optical@355:  l.id     2 seq TO BT BT SA

    ## HMM: when pre->post is a small step need to skip the pre which was already collected (when it was post of the prior step)
    ##
    ## SO IT LOOKS LIKE CANNOT DO FAKE SKIPPING WITH LIVE WRITING 
    ## UNLESS OVERWRITE THE PRIOR BY NOT INCREMENTING THE SLOT WHEN DISCOVER THE FAKE 
    ##
    ## SO EVERYTHING STAYS THE SAME : JUST NEED TO DECREMENT THE SLOT WHEN DISCOVER THAT LAST WRITE WAS THE FAKE
    ##

    N=1 POM=1 ./U4SimulateTest.sh   # natural geom , multifilm POM 

    U4Recorder::UserSteppingAction_Optical@474:  l.id   2 same_material_step NO  step_mm    82.5401 pre/post : Water/Pyrex pv Water_lv_pv
    U4Recorder::UserSteppingAction_Optical@474:  l.id   2 same_material_step NO  step_mm     5.2887 pre/post : Pyrex/Vacuum pv AroundCircle0
    U4Recorder::PostUserTrackingAction_Optical@355:  l.id     2 seq TO BT SA


The N=0 FastSim-region-kludge results in always getting two same material steps::

    N=0              
            
                    Py/Py 
             |     ! |
             |     ! |
      Wa/Py  |Py/Py! |
             |     ! |
    0--------1-----2-3        To allow comparison need to suppress steppoint 2. 
             |     ! |
             |     ! |
    TO      BT    BT SA  


    N=1

       Wa/Py  | Py/Va|
              |      |
     0--------1------2
              |      |
              |      |
     TO       BT     SA



* notice few-per-1000 same_material_step for N=1 (TODO: investigate those) 


Need to find an approach that also handles the  Vacuum/Vacuum fake::

    N=0 POM=1 ./U4SimulateTest.sh 

    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm    82.5401 pre/post : Water/Pyrex pv Water_lv_pv
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step YES step_mm     5.2876 pre/post : Pyrex/Pyrex pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step YES step_mm     0.0011 pre/post : Pyrex/Pyrex pv hama_body_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step YES step_mm   164.0267 pre/post : Vacuum/Vacuum pv hama_inner1_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   144.4904 pre/post : Vacuum/Pyrex pv hama_inner2_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Pyrex/Vacuum pv hama_body_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm    83.2208 pre/post : Vacuum/Steel pv hama_inner2_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Steel/Vacuum pv hama_dynode_tube_phy
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   180.3831 pre/post : Vacuum/Pyrex pv hama_inner2_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Pyrex/Vacuum pv hama_body_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step YES step_mm    10.5976 pre/post : Vacuum/Vacuum pv hama_inner2_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step YES step_mm   342.8424 pre/post : Vacuum/Vacuum pv hama_inner1_phys
    U4Recorder::PostUserTrackingAction_Optical@355:  l.id    31 seq TO BT BT BT BT SR SR SR BT SA

    In [1]: 164.0267 + 144.4904
    Out[1]: 308.5171

    N=1 POM=1 ./U4SimulateTest.sh 

    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm    82.5401 pre/post : Water/Pyrex pv Water_lv_pv
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     5.2887 pre/post : Pyrex/Vacuum pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   308.5171 pre/post : Vacuum/Pyrex pv hama_inner_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Pyrex/Vacuum pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm    83.2208 pre/post : Vacuum/Steel pv hama_inner_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Steel/Vacuum pv hama_dynode_tube_phy
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   180.3831 pre/post : Vacuum/Pyrex pv hama_inner_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     0.0000 pre/post : Pyrex/Vacuum pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   353.4399 pre/post : Vacuum/Pyrex pv hama_inner_phys
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm     5.7919 pre/post : Pyrex/Water pv AroundCircle0
    U4Recorder::UserSteppingAction_Optical@474:  l.id  31 same_material_step NO  step_mm   360.7316 pre/post : Water/Rock pv Water_lv_pv
    U4Recorder::PostUserTrackingAction_Optical@355:  l.id    31 seq TO BT BT SR SR SR BT BT SA

Visualize that photon::

    APID=31 N=0 ./U4SimtraceTest.sh ana


Dont Think General (Its too difficult) : Think specific
-----------------------------------------------------------

Thinking about all possible photon paths that yield fakes 
there is a plethora of arrangements making it very difficult 
for reliable detection and skipping in general.  

* BUT : DO NOT NEED A GENERAL SOLUTION 
* JUST NEED SOLUTION THAT WORKS FOR A SPECIFIC FASTSIM-COMPOMISED-KLUDGED-MONSTROSITY OF A GEOMETRY

  * THAT MAKES IT MUCH EASIER : CAN IDENTIFY USING PRE-KNOWLEDGE OF WHERE THEY ARE 
    BASED ON VOL-NAMES AND LOCAL POSITIONS 

  * HOPEFULLY THAT CAN AVOID THE NEED TO PASS INFO BETWEEN STEPS,
    SO CAN SKIP LIVE WITHOUT HAVING TO DECREMENT THE SLOT AND OVERWRITE ?


10k WITH FIRST TRY AT FAKES_SKIP 
-------------------------------------

::

     82 
     83 if [ "$VERSION" == "0" ]; then
     84     f0=Pyrex/Pyrex:AroundCircle0/hama_body_phys
     85     f1=Pyrex/Pyrex:hama_body_phys/AroundCircle0
     86     f2=Vacuum/Vacuum:hama_inner1_phys/hama_inner2_phys
     87     f3=Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys
     88     export U4Recorder__FAKES="$f0,$f1,$f2,$f3"
     89     export U4Recorder__FAKES_SKIP=1
     90     echo $BASH_SOURCE : U4Recorder__FAKES_SKIP ENABLED 
     91 fi
     92 
     93 


The simple U4Step::Spec based fake skipping looks to be working ok::

    epsilon:tests blyth$ N=0 POM=1 ./U4SimulateTest.sh # unnatural geom , multifilm POM     epsilon:tests blyth$ N=1 POM=1 ./U4SimulateTest.sh # natural geom , multifilm POM 


    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first     np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi firindex 
    [[b'5867' b'0' b'TO BT SA                                                               [[b'5799' b'0' b'TO BT SA                                                        
     [b'1006' b'2' b'TO BT BR BT SA                                                          [b'1039' b'24' b'TO BT BR BT SA                                                 
     [b'963' b'4' b'TO BT BT SR SA                                                           [b'987' b'1' b'TO BT BT SR SA                                                   
     [b'527' b'56' b'TO BT BT SR SR SR SA                                                    [b'544' b'2' b'TO BT BT SR SR SR SA                                             
     [b'411' b'26' b'TO BT BT SR SR SR BT BT SA                                              [b'413' b'4' b'TO BT BT SR SR SR BT BT SA                                       

     [b'260' b'39' b'TO BT BT SR SR SR BR SR SA                                              [b'245' b'77' b'TO BT BT SA                                                     
     [b'218' b'11' b'TO BT BT SA                                                             [b'243' b'64' b'TO BT BT SR SR SR BR SR SA                                      

     [b'152' b'5' b'TO BT BT SR SR SR BR SR SR SR SA                                         [b'150' b'190' b'TO BT BT SR SR SA                                              
     [b'133' b'20' b'TO BT BT SR SR SA                                                       [b'132' b'89' b'TO BT BT SR SR SR BR SR SR SR SA                                

     [b'66' b'13' b'TO BT BT SR SR SR BR SA                                                  [b'64' b'75' b'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                        
     [b'63' b'35' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                             [b'55' b'72' b'TO BT BT SR SR SR BR SA                                          
     [b'51' b'15' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                          [b'53' b'62' b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                        
     [b'45' b'297' b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                               [b'41' b'483' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                 
     [b'30' b'772' b'TO BT AB                                                                [b'30' b'777' b'TO BT BT SR SR SR BR SR SR SA                                   
     [b'23' b'788' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                         [b'26' b'621' b'TO BT AB                                                        
     [b'22' b'899' b'TO BR SA                                                                [b'26' b'342' b'TO BR SA                                                        
     [b'20' b'1069' b'TO BT BT SR SR SR BR SR SR SA                                          [b'21' b'2443' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                   
     [b'19' b'2445' b'TO AB                                                                  [b'16' b'349' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                 
     [b'16' b'966' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SR BT SA                [b'15' b'34' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                  
     [b'14' b'1190' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                           [b'14' b'485' b'TO AB                                                           
     [b'13' b'619' b'TO BT BT SR SR SR BR SR SR SR BR SA                                     [b'13' b'69' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA            
     [b'12' b'222' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SR BT BT BT BT SA       [b'13' b'129' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                 
     [b'11' b'866' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BR BT BT SA                   [b'13' b'2114' b'TO BT BT SR SR SR BR SR SR SR BR SA                            
     [b'8' b'717' b'TO BT BR BT AB                                                           [b'7' b'400' b'TO BT BT SR SR SR BR SR SR SR BR SR SA                           
     [b'8' b'793' b'TO BT BT SR SR SR BR SR SR SR BR SR SA                                   [b'6' b'23' b'TO BT BR BT AB                                                    
     [b'4' b'2664' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SA                      [b'5' b'584' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR SA            
     [b'4' b'741' b'TO BT BT SR SR SR BT AB                                                  [b'4' b'4412' b'TO BT BT SR SR SR BT BT AB                                      
                                                                                             [b'4' b'1409' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR BT BT BT SA  
                                                                                             [b'3' b'2019' b'TO BT BR BT SC SA                                               



Where did I do skipping before ? microstep ?
---------------------------------------------

* HMM: MAYBE THERE IS SOMETHING MORE RECENT THAN CRecorder ? 

::

    094 CRecorder::CRecorder(CCtx& ctx)
     95     :
     96     m_ctx(ctx),
     97     m_ok(m_ctx.getOpticks()),
     98     m_microStep_mm(0.004),              //  see notes/issues/ok_lacks_SI-4BT-SD.rst
     99     m_suppress_same_material_microStep(true),
    100     m_suppress_all_microStep(true),
    101     m_mode(m_ok->getManagerMode()),   // --managermode

    550         unsigned premat = m_material_bridge->getPreMaterial(step) ;
    552         unsigned postmat = m_material_bridge->getPostMaterial(step) ;
    553 
    554         bool suppress_microStep = false ;
    555         if(m_suppress_same_material_microStep ) suppress_microStep = premat == postmat && microStep ;
    556         if(m_suppress_all_microStep )           suppress_microStep = microStep ;
    557         // suppress_all_microStep trumps suppress_same_material_microStep
    558 

    590 #ifdef USE_CUSTOM_BOUNDARY
    591         bool postSkip = ( boundary_status == Ds::StepTooSmall || suppress_microStep ) && !lastPost  ;
    592         bool matSwap = next_boundary_status == Ds::StepTooSmall ;
    593 #else
    594         bool postSkip = ( boundary_status == StepTooSmall || suppress_microStep ) && !lastPost  ;
    595         bool matSwap = next_boundary_status == StepTooSmall ;
    596 #endif
    597 




Need to revive statistical A-B comparison and make it work with extended histories
------------------------------------------------------------------------------------

Old machinery is based on assumption can fit the history into 64 bits 
that is no longer the case (now 128 bits). 


::

    epsilon:ana blyth$ grep SeqTable *.py 
    dv.py:        :param seqtab: ab.ahis SeqTable
    evt.py:            c_tab = a_tab.compare(b_tab, ordering=ordering, shortname=shortname)   # see seq.py SeqTable.compare 

    hismask.py:from opticks.ana.seq import MaskType, SeqTable, SeqAna
    hismask.py:def test_HisMask_SeqTable(aa, af):
    hismask.py:     st = SeqTable(cu, af)
    hismask.py:         #test_HisMask_SeqTable(ht, af)
    hismask.py:         #test_HisMask_SeqTable(ox, af)
    histype.py:from opticks.ana.seq import SeqType, SeqTable, SeqAna
    histype.py:def test_load_SeqTable(ok, af):
    histype.py:     ht = SeqTable(cu, af, smry=True)
    histype.py:     test_load_SeqTable(ok, af)
    qdv.py:        self.seqtab = ab.ahis   # SeqTable
    seq.py:class SeqTable(object):
    seq.py:        log.debug("SeqTable.__init__ dbgseq %x" % dbgseq)
    seq.py:        :param other: SeqTable instance
    seq.py:        log.debug("SeqTable.compare START")
    seq.py:        cftab = SeqTable(cf, self.af, cnames=cnames, dbgseq=self.dbgseq, dbgmsk=self.dbgmsk, dbgzero=self.dbgzero, cmx=self.cmx, shortname=shortname)    
    seq.py:        log.debug("SeqTable.compare DONE")
    seq.py:    In addition to holding the SeqTable instance SeqAna provides
    seq.py:    SeqAna and its contained SeqTable exist within a particular selection, 
    seq.py:    ie changing selection entails recreation of SeqAna and its contained SeqTable
    seq.py:        self.table = SeqTable(cu, af, cnames=cnames, dbgseq=self.dbgseq, dbgmsk=self.dbgmsk, dbgzero=self.dbgzero, cmx=self.cmx, shortname=table_shortname)
    seq.py:    table = SeqTable(cu, af) 
    seq.py:    table = SeqTable(cu, af) 
    seq.py:    table = SeqTable.FromTxt(txt, af) 
    epsilon:ana blyth$ 




A few notable dropout zeros to chase
----------------------------------------


::

    epsilon:tests blyth$ ./U4SimulateTest.sh cf
    ...    
    Fold : symbol a base /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0 
    Fold : symbol b base /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1 

    np.c_[aqn,aqi,aqu][aquo][lim]  ## aexpr : unique histories aqu in descending count aqn order, aqi first index 
    [[b'58664' b'0' b'TO BT SA                                                                                        ']
     [b'9979' b'9' b'TO BT BR BT SA                                                                                  ']
     [b'9697' b'2' b'TO BT BT SR SA                                                                                  ']
     [b'5358' b'4' b'TO BT BT SR SR SR SA                                                                            ']
     [b'4150' b'28' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'2416' b'1' b'TO BT BT SA                                                                                     ']
     [b'2359' b'39' b'TO BT BT SR SR SR BR SR SA                                                                      ']
     [b'1400' b'91' b'TO BT BT SR SR SA                                                                               ']
     [b'1394' b'55' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'642' b'136' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ']]

    np.c_[bqn,bqi,bqu][bquo][lim]  ## bexpr : unique histories bqu in descending count bqn order, bqi first index 
    [[b'58337' b'0' b'TO BT SA                                                                                        ']
     [b'10133' b'2' b'TO BT BR BT SA                                                                                  ']
     [b'9857' b'3' b'TO BT BT SR SA                                                                                  ']
     [b'5478' b'7' b'TO BT BT SR SR SR SA                                                                            ']
     [b'4112' b'20' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'2470' b'167' b'TO BT BT SA                                                                                     ']
     [b'2289' b'78' b'TO BT BT SR SR SR BR SR SA                                                                      ']
     [b'1418' b'45' b'TO BT BT SR SR SA                                                                               ']
     [b'1348' b'15' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'654' b'254' b'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ']]

    np.c_[quo,abo[:,2,:],abo[:,1,:]][:30]  ## abexpr : A-B comparison of unique history counts 
    [[b'TO BT SA                                                                                        ' b'58664' b'58337' b'0' b'0']
     [b'TO BT BR BT SA                                                                                  ' b'9979' b'10133' b'9' b'2']
     [b'TO BT BT SR SA                                                                                  ' b'9697' b'9857' b'2' b'3']
     [b'TO BT BT SR SR SR SA                                                                            ' b'5358' b'5478' b'4' b'7']
     [b'TO BT BT SR SR SR BT BT SA                                                                      ' b'4150' b'4112' b'28' b'20']
     [b'TO BT BT SA                                                                                     ' b'2416' b'2470' b'1' b'167']
     [b'TO BT BT SR SR SR BR SR SA                                                                      ' b'2359' b'2289' b'39' b'78']
     [b'TO BT BT SR SR SA                                                                               ' b'1400' b'1418' b'91' b'45']
     [b'TO BT BT SR SR SR BR SR SR SR SA                                                                ' b'1394' b'1348' b'55' b'15']

     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ' b'0' b'654' b'-1' b'254']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ' b'642' b'29' b'136' b'8642']

           ## MAYBE FAKE NOT BEING DETECTED ? 

           BPID=8642 ./U4SimtraceTest.sh ana    
           APID=136  ./U4SimtraceTest.sh ana    
           APID=136 BPID=8642 BOFF=0,0,10 ./U4SimtraceTest.sh ana 

           ## YES: the photon bounces around inside HAMA and then crosses over inside NNVT
           ## DID NOT YET SETUP FAKE DETECTION FOR NNVT VOL NAMES 
           ## HMM BUT B IS N=1 NO FAKE DETECTION 


     [b'TO BT BT SR SR SR BR SA                                                                         ' b'600' b'570' b'153' b'62']
     [b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ' b'452' b'451' b'283' b'514']
     [b'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ' b'416' b'376' b'251' b'303']
     [b'TO BT BT SR SR SR BR SR SR SA                                                                   ' b'323' b'359' b'58' b'357']
     [b'TO BT AB                                                                                        ' b'314' b'358' b'303' b'116']
     [b'TO BR SA                                                                                        ' b'272' b'259' b'642' b'54']
     [b'TO AB                                                                                           ' b'219' b'226' b'110' b'1167']
     [b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ' b'186' b'166' b'383' b'131']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SR BT SA                                        ' b'133' b'0' b'1398' b'-1']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ' b'0' b'127' b'-1' b'875']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                                                 ' b'0' b'124' b'-1' b'693']
     [b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                                                    ' b'124' b'122' b'1252' b'699']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BR BT BT SA                                           ' b'113' b'0' b'131' b'-1']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SR BT BT BT BT SA                               ' b'110' b'0' b'836' b'-1']
     [b'TO BT BT SR SR SR BR SR SR SR BR SR SA                                                          ' b'109' b'106' b'835' b'4067']
     [b'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ' b'94' b'105' b'1270' b'923']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA                                           ' b'0' b'103' b'-1' b'1360']
     [b'TO BT BR BT AB                                                                                  ' b'70' b'76' b'2234' b'798']
     [b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT BT BT SR BT BR BT SR BT SA                            ' b'35' b'0' b'551' b'-1']]

    In [1]: aq[110]                                                                                                                                                             
    Out[1]: array([b'TO AB                                                                                           '], dtype='|S96')

    In [2]: bq[1167]                                                                                                                                                            
    Out[2]: array([b'TO AB                                                                                           '], dtype='|S96')



After add NNVT fake skipping : No obvious zero dropouts in A-B comparison
----------------------------------------------------------------------------

After extending Fake skipping to NNVT::

     83 if [ "$VERSION" == "0" ]; then
     84     f0=Pyrex/Pyrex:AroundCircle0/hama_body_phys
     85     f1=Pyrex/Pyrex:hama_body_phys/AroundCircle0
     86     f2=Vacuum/Vacuum:hama_inner1_phys/hama_inner2_phys
     87     f3=Vacuum/Vacuum:hama_inner2_phys/hama_inner1_phys
     88 
     89     f4=Pyrex/Pyrex:AroundCircle1/nnvt_body_phys
     90     f5=Pyrex/Pyrex:nnvt_body_phys/AroundCircle1
     91     f6=Vacuum/Vacuum:nnvt_inner1_phys/nnvt_inner2_phys
     92     f7=Vacuum/Vacuum:nnvt_inner2_phys/nnvt_inner1_phys
     93 
     94     export U4Recorder__FAKES="$f0,$f1,$f2,$f3,$f4,$f5,$f6,$f7"
     95     export U4Recorder__FAKES_SKIP=1
     96     echo $BASH_SOURCE : U4Recorder__FAKES_SKIP ENABLED 
     97 fi


There are no obvious zero dropouts in the A-B comparison::

    epsilon:tests blyth$ ./U4SimulateTest.sh cf
    ...

    np.c_[np.arange(len(quo)),quo,np.arange(len(quo)),abo[:,2,:],abo[:,1,:]][:30]  ## abexpr : A-B comparison of unique history counts 
    [[b'0' b'TO BT SA                                                                                        ' b'0' b'58664' b'58337' b'0' b'0']
     [b'1' b'TO BT BR BT SA                                                                                  ' b'1' b'9979' b'10133' b'9' b'2']
     [b'2' b'TO BT BT SR SA                                                                                  ' b'2' b'9697' b'9857' b'2' b'3']
     [b'3' b'TO BT BT SR SR SR SA                                                                            ' b'3' b'5358' b'5478' b'4' b'7']
     [b'4' b'TO BT BT SR SR SR BT BT SA                                                                      ' b'4' b'4150' b'4112' b'28' b'20']
     [b'5' b'TO BT BT SA                                                                                     ' b'5' b'2416' b'2470' b'1' b'167']
     [b'6' b'TO BT BT SR SR SR BR SR SA                                                                      ' b'6' b'2359' b'2289' b'39' b'78']
     [b'7' b'TO BT BT SR SR SA                                                                               ' b'7' b'1400' b'1418' b'91' b'45']
     [b'8' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ' b'8' b'1394' b'1348' b'55' b'15']
     [b'9' b'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ' b'9' b'642' b'654' b'136' b'254']
     [b'10' b'TO BT BT SR SR SR BR SA                                                                         ' b'10' b'600' b'570' b'153' b'62']
     [b'11' b'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ' b'11' b'452' b'451' b'283' b'514']
     [b'12' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ' b'12' b'416' b'376' b'251' b'303']
     [b'13' b'TO BT BT SR SR SR BR SR SR SA                                                                   ' b'13' b'323' b'359' b'58' b'357']
     [b'14' b'TO BT AB                                                                                        ' b'14' b'314' b'358' b'303' b'116']
     [b'15' b'TO BR SA                                                                                        ' b'15' b'272' b'259' b'642' b'54']
     [b'16' b'TO AB                                                                                           ' b'16' b'219' b'226' b'110' b'1167']
     [b'17' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ' b'17' b'186' b'166' b'383' b'131']
     [b'18' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ' b'18' b'133' b'127' b'1398' b'875']
     [b'19' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                                                 ' b'19' b'113' b'124' b'131' b'693']
     [b'20' b'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                                                    ' b'20' b'124' b'122' b'1252' b'699']
     [b'21' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA                                           ' b'21' b'110' b'103' b'836' b'1360']
     [b'22' b'TO BT BT SR SR SR BR SR SR SR BR SR SA                                                          ' b'22' b'109' b'106' b'835' b'4067']
     [b'23' b'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ' b'23' b'94' b'105' b'1270' b'923']
     [b'24' b'TO BT BR BT AB                                                                                  ' b'24' b'70' b'76' b'2234' b'798']
     [b'25' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR SA                                           ' b'25' b'35' b'31' b'551' b'5431']
     [b'26' b'TO BT BT SR SR SR BT BT AB                                                                      ' b'26' b'34' b'34' b'517' b'638']
     [b'27' b'TO BT BR AB                                                                                     ' b'27' b'34' b'27' b'51' b'447']
     [b'28' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ' b'28' b'33' b'29' b'18155' b'8642']
     [b'29' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR BT BT BT SA                                  ' b'29' b'12' b'29' b'7276' b'1992']]



1M Statistical Comparison of history counts : whats the chi2 ? Any significant deviants ? NO 
-----------------------------------------------------------------------------------------------

::

    epsilon:tests blyth$ ./U4SimulateTest.sh cf 
    layout two_pmt
    FewPMT.sh N=0 unnatural geometry : FastSim/jPOM
    POM 0 : traditional stop at photocathode : PMT with no innards
    ./U4SimulateTest.sh : U4Recorder__FAKES_SKIP ENABLED
    PID : -1 
    Fold : symbol a base /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0 
    Fold : symbol b base /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1 
    ...

    c2sum :    66.3813 c2n :    61.0000 c2per:     1.0882 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SA                                                                                        ' ' 0' '585683 585608' ' 0.0048' '     0      1']
     [' 1' 'TO BT BR BT SA                                                                                  ' ' 1' '101296 101008' ' 0.4100' '     5      0']
     [' 2' 'TO BT BT SR SA                                                                                  ' ' 2' ' 97899  97419' ' 1.1796' '     1      9']
     [' 3' 'TO BT BT SR SR SR SA                                                                            ' ' 3' ' 53988  54285' ' 0.8147' '    20     17']
     [' 4' 'TO BT BT SR SR SR BT BT SA                                                                      ' ' 4' ' 41036  41260' ' 0.6097' '    47     32']

     [' 5' 'TO BT BT SA                                                                                     ' ' 5' ' 23986  24442' ' 4.2937' '    44      5']

     [' 6' 'TO BT BT SR SR SR BR SR SA                                                                      ' ' 6' ' 22975  22604' ' 3.0198' '    27     13']
     [' 7' 'TO BT BT SR SR SA                                                                               ' ' 7' ' 14247  14493' ' 2.1056' '     9     84']
     [' 8' 'TO BT BT SR SR SR BR SR SR SR SA                                                                ' ' 8' ' 13766  13649' ' 0.4993' '   537     82']
     [' 9' 'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ' ' 9' '  6299   6397' ' 0.7565' '   158    159']
     ['10' 'TO BT BT SR SR SR BR SA                                                                         ' '10' '  5756   5580' ' 2.7325' '    40    196']
     ['11' 'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ' '11' '  4503   4416' ' 0.8486' '   358    436']
     ['12' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ' '12' '  3816   3818' ' 0.0005' '   100    290']
     ['13' 'TO BT BT SR SR SR BR SR SR SA                                                                   ' '13' '  3359   3452' ' 1.2699' '   399    675']
     ['14' 'TO BT AB                                                                                        ' '14' '  3282   3414' ' 2.6022' '    73     22']
     ['15' 'TO BR SA                                                                                        ' '15' '  2760   2655' ' 2.0360' '   149      6']
     ['16' 'TO AB                                                                                           ' '16' '  2190   2230' ' 0.3620' '   243    157']
     ['17' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ' '17' '  1829   1805' ' 0.1585' '    38    351']
     ['18' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ' '18' '  1282   1321' ' 0.5843' '   250     20']
     ['19' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                                                    ' '19' '  1178   1225' ' 0.9193' '  1000     91']
     ['20' 'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ' '20' '  1145   1084' ' 1.6694' '  2193    921']
     ['21' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                                                 ' '21' '  1064   1065' ' 0.0005' '   111   2270']
     ['22' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA                                           ' '22' '  1046   1061' ' 0.1068' '    99   1873']
     ['23' 'TO BT BT SR SR SR BR SR SR SR BR SR SA                                                          ' '23' '  1008   1002' ' 0.0179' '  2889    117']
     ['24' 'TO BT BR BT AB                                                                                  ' '24' '   674    736' ' 2.7262' '   120   1309']
     ['25' 'TO BT BT SR SR SR BT BT AB                                                                      ' '25' '   380    376' ' 0.0212' '  5043   5602']
     ['26' 'TO BT BR AB                                                                                     ' '26' '   362    318' ' 2.8471' '  6974    900']
     ['27' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR SA                                           ' '27' '   356    331' ' 0.9098' '  5397   1299']
     ['28' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ' '28' '   266    289' ' 0.9532' '   682   1221']
     ['29' 'TO SC SA                                                                                        ' '29' '   210    215' ' 0.0588' '   132    408']]


HMM: IS THERE SOME ISSUE WITH FAKE SKIPPING ?

     [' 5' 'TO BT BT SA                                                                                     ' ' 5' ' 23986  24442' ' 4.2937' '    44      5']


Visualizing the first two photons with that history::

    POM=1 N=0 APID=44 ./U4SimtraceTest.sh ana  
    POM=1 N=1 APID=-44 BPID=5 ./U4SimtraceTest.sh ana

"TO BT BT SA" enters PMT and gets absorbed on back hemi


Look at end position of all photons in A and B with history "TO BT BT SA"::

    In [8]: aw = np.where( aq[:,0] == aq[44] )[0]

    In [9]: bw = np.where( bq[:,0] == aq[44] )[0]

    In [15]: aw,bw,aw.shape,bw.shape
    Out[15]: 
    (array([    44,    117,    125,    190,    203, ..., 999775, 999815, 999878, 999927, 999981]),
     array([     5,     11,     24,     42,     51, ..., 999972, 999979, 999985, 999989, 999993]),
     (23986,),
     (24442,))

Nothing unexpected all end at same place::

    In [20]: a.photon[aw,0,:]
    Out[20]: 
    array([[ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           ...,
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978],
           [ 392.859,    0.   , -166.048,    1.978]], dtype=float32)

    In [25]: np.where( a.photon[aw[0],0,0] != a.photon[aw,0,0] )
    Out[25]: (array([], dtype=int64),)

    In [26]: np.where( a.photon[aw[0],0,1] != a.photon[aw,0,1] )
    Out[26]: (array([], dtype=int64),)

    In [27]: np.where( a.photon[aw[0],0,2] != a.photon[aw,0,2] )
    Out[27]: (array([], dtype=int64),)


    In [28]: b.photon[bw,0,:]   ## NOTE THE EARLIER TIME : KNOWN PYREX SPEED IN VACCUUM ABOVE
    Out[28]: 
    array([[ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           ...,
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435],
           [ 392.859,    0.   , -166.048,    1.435]], dtype=float32)

    In [29]: np.where( b.photon[bw[0],0,0] != b.photon[bw,0,0] )
    Out[29]: (array([], dtype=int64),)

    In [30]: np.where( b.photon[bw[0],0,1] != b.photon[bw,0,1] )
    Out[30]: (array([], dtype=int64),)

    In [31]: np.where( b.photon[bw[0],0,2] != b.photon[bw,0,2] )
    Out[31]: (array([], dtype=int64),)


Look at the fraction absorbed/reflected at the inside back hemi
-----------------------------------------------------------------

HMM: What fraction is absorbed/reflected at the back there ? Does that correspond to input ?  YES

* select indices where t.record position of point 3 matches the first

::

    In [37]: a.record[aw[0],:4,0]
    Out[37]: 
    array([[   0.   ,    0.   , -120.   ,    0.   ],
           [  82.54 ,    0.   , -120.   ,    0.379],
           [  87.826,    0.   , -119.815,    0.406],
           [ 392.859,    0.   , -166.048,    1.978]], dtype=float32)

    In [38]: b.record[bw[0],:4,0]
    Out[38]: 
    array([[   0.   ,    0.   , -120.   ,    0.   ],
           [  82.54 ,    0.   , -120.   ,    0.379],
           [  87.826,    0.   , -119.815,    0.406],
           [ 392.859,    0.   , -166.048,    1.435]], dtype=float32)

::

    zw = np.where( np.logical_and( a.record[aw[0],3,0,0] == a.record[:,3,0,0], a.record[aw[0],3,0,2] == a.record[:,3,0,2] ) ) 

    In [45]: zw[0].shape
    Out[45]: (302814,)     ## how many have point 3 at the back there 

    In [46]: 23986/302814
    Out[46]: 0.07921034034093535     ## fraction absorbed

    In [48]: 1.- (23986/302814)
    Out[48]: 0.9207896596590647      ## fraction reflected



    In [49]: bzw = np.where( np.logical_and( b.record[bw[0],3,0,0] == b.record[:,3,0,0], b.record[bw[0],3,0,2] == b.record[:,3,0,2] ) )

    In [50]: bzw[0].shape
    Out[50]: (303092,)

    In [51]: 24442/303092, 1-24442/303092
    Out[51]: (0.08064218125189711, 0.9193578187481029)


Reflectivity of 0.92 is the default when no PMT_Mirror


    0328 void
     329  HamamatsuR12860PMTManager::init_mirror_surface()
     330 {
     331     if( m_mirror_opsurf != nullptr ) return ;
     332 
     333         // construct a static mirror surface with idealized properties
     334         G4String name ;
     335         name += CommonPMTManager::GetMirrorOpticalSurfacePrefix(m_natural_geometry, m_enable_optical_model ) ;  // control customization, see above 
     336         name += GetName() ;
     337         name += "_Mirror_opsurf" ;
     338 
     339         m_mirror_opsurf = new G4OpticalSurface(name);
     340         m_mirror_opsurf->SetFinish(polishedfrontpainted); // needed for mirror
     341         m_mirror_opsurf->SetModel(glisur);
     342         m_mirror_opsurf->SetType(dielectric_metal);
     343         m_mirror_opsurf->SetPolish(0.999);             // Causes very slight smearing of GetFacetNormal result, is that always used? 
    
     ///   MY READING OF G4OpBoundaryProcess SUGGESTS THE "polishedfrontpainted" DOES NOTHING FOR type:dielectric_metal 
     ///
     ///        finish:polishedfrontpainted 
     ///
     ///   HOWEVER model:glisur IS ACTUALLY NEEDED 
     ///   

     344 
     345         G4Material* matMirror = G4Material::GetMaterial("PMT_Mirror");
     346         G4MaterialPropertiesTable* propMirror = matMirror ? matMirror->GetMaterialPropertiesTable() : nullptr ;
     347 
     348         if(propMirror == nullptr)
     349         {
     350             propMirror= new G4MaterialPropertiesTable();
     351             propMirror->AddProperty("REFLECTIVITY", new G4MaterialPropertyVector());
     352             propMirror->AddEntry("REFLECTIVITY", 1.55*eV, 0.92);
     353             propMirror->AddEntry("REFLECTIVITY", 15.5*eV, 0.92);
     354         }
     355         m_mirror_opsurf->SetMaterialPropertiesTable( propMirror );
     356 }

::

    epsilon:tests blyth$ cd $NP_PROP_BASE
    epsilon:DetSim blyth$ find . -name PMT_Mirror
    epsilon:DetSim blyth$ 

::

    epsilon:tests blyth$ export BP="CustomG4OpBoundaryProcess::DielectricMetal CustomG4OpBoundaryProcess::ChooseReflection CustomG4OpBoundaryProcess::DoAbsorption" 
         POM=1 N=1 ./U4SimulateTest.sh dbg 


SetPolish(0.999) DOES IT DO ANYTHING ? YES : Small smear to GetFacetNormal 
---------------------------------------------------------------------------------

g4-cls G4OpticalSurface::

    186     G4double GetPolish() const { return polish; }
    187         // Returns the optical surface polish type.
    188     inline void SetPolish(const G4double plsh) { polish=plsh; }
    189         // Sets the optical surface polish type.


::

    epsilon:junosw blyth$ g4-cc GetPolish 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/processes/optical/src/G4OpBoundaryProcess.cc:           if (OpticalSurface) polish = OpticalSurface->GetPolish();
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/persistency/gdml/src/G4GDMLWriteSolids.cc:   G4double sval = (smodel==glisur) ? surf->GetPolish() : surf->GetSigmaAlpha();
    epsilon:junosw blyth$ 
    epsilon:junosw blyth$ g4-hh GetPolish 
    /usr/local/opticks_externals/g4_1042.build/geant4.10.04.p02/source/materials/include/G4OpticalSurface.hh:	G4double GetPolish() const { return polish; }
    epsilon:junosw blyth$ 


See u4/tests/G4OpBoundaryProcess_GetFacetNormal_Test.sh


DONE : POM:0 COMPARISON BETWEEN N=0/1 A-B comparison  : no significant deviation
-------------------------------------------------------------------------------------

Expect very simple histories in this case

::

    POM=0 N=0 ./U4SimulateTest.sh 
    POM=0 N=1 ./U4SimulateTest.sh 
    POM=0 ./U4SimulateTest.sh cf

::

    c2sum :     6.7669 c2n :     6.0000 c2per:     1.1278 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                                                                                        ' ' 0' ' 99119  99129' ' 0.0005' '     0      0']
     [' 1' 'TO BT AB                                                                                        ' ' 1' '   352    334' ' 0.4723' '   156     28']
     [' 2' 'TO BR SA                                                                                        ' ' 2' '   280    259' ' 0.8182' '   175    163']
     [' 3' 'TO AB                                                                                           ' ' 3' '   214    221' ' 0.1126' '  1421    187']
     [' 4' 'TO SC SA                                                                                        ' ' 4' '    17     33' ' 5.1200' '   560   1415']
     [' 5' 'TO SC BT SD                                                                                     ' ' 5' '    17     20' ' 0.2432' ' 10268    255']
     [' 6' 'TO SC AB                                                                                        ' ' 6' '     0      3' ' 0.0000' '    -1   5474']
     [' 7' 'TO BR AB                                                                                        ' ' 7' '     1      1' ' 0.0000' '  9335  86580']]


Efficiency is set to 1. for::

     560                 else if( OpticalSurfaceName0 == '#' ) // upper hemi with name starting # : Traditional Detection at photocathode
     561                 {
     562                     m_custom_status = '-' ;
     563 
     564                     type = dielectric_metal ;
     565                     theModel = glisur ;
     566                     theReflectivity = 0. ;
     567                     theTransmittance = 0. ;
     568                     theEfficiency = 1. ;
     569                 }




POM:1 SINGLE POINT IS CONSISTENT : BUT WHY NO SD ? BECAUSE WAS USING JPMT NOT PMTSimParamData 
------------------------------------------------------------------------------------------------------------

::

    POM=0 N=0 ./U4SimulateTest.sh 
    POM=0 N=1 ./U4SimulateTest.sh 
    POM=0 ./U4SimulateTest.sh cf


    c2sum :    29.0921 c2n :    32.0000 c2per:     0.9091 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SA                                                                                        ' ' 0' ' 58664  58337' ' 0.9139' '     0      0']
     [' 1' 'TO BT BR BT SA                                                                                  ' ' 1' '  9979  10133' ' 1.1792' '     9      2']
     [' 2' 'TO BT BT SR SA                                                                                  ' ' 2' '  9697   9857' ' 1.3092' '     2      3']
     [' 3' 'TO BT BT SR SR SR SA                                                                            ' ' 3' '  5358   5478' ' 1.3289' '     4      7']
     [' 4' 'TO BT BT SR SR SR BT BT SA                                                                      ' ' 4' '  4150   4112' ' 0.1748' '    28     20']
     [' 5' 'TO BT BT SA                                                                                     ' ' 5' '  2416   2470' ' 0.5968' '     1    167']
     [' 6' 'TO BT BT SR SR SR BR SR SA                                                                      ' ' 6' '  2359   2289' ' 1.0542' '    39     78']
     [' 7' 'TO BT BT SR SR SA                                                                               ' ' 7' '  1400   1418' ' 0.1150' '    91     45']
     [' 8' 'TO BT BT SR SR SR BR SR SR SR SA                                                                ' ' 8' '  1394   1348' ' 0.7717' '    55     15']
     [' 9' 'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ' ' 9' '   642    654' ' 0.1111' '   136    254']
     ['10' 'TO BT BT SR SR SR BR SA                                                                         ' '10' '   600    570' ' 0.7692' '   153     62']
     ['11' 'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ' '11' '   452    451' ' 0.0011' '   283    514']
     ['12' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ' '12' '   416    376' ' 2.0202' '   251    303']
     ['13' 'TO BT BT SR SR SR BR SR SR SA                                                                   ' '13' '   323    359' ' 1.9003' '    58    357']
     ['14' 'TO BT AB                                                                                        ' '14' '   314    358' ' 2.8810' '   303    116']
     ['15' 'TO BR SA                                                                                        ' '15' '   272    259' ' 0.3183' '   642     54']
     ['16' 'TO AB                                                                                           ' '16' '   219    226' ' 0.1101' '   110   1167']
     ['17' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ' '17' '   186    166' ' 1.1364' '   383    131']
     ['18' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ' '18' '   133    127' ' 0.1385' '  1398    875']
     ['19' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                                                 ' '19' '   113    124' ' 0.5105' '   131    693']
     ['20' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                                                    ' '20' '   124    122' ' 0.0163' '  1252    699']
     ['21' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA                                           ' '21' '   110    103' ' 0.2300' '   836   1360']
     ['22' 'TO BT BT SR SR SR BR SR SR SR BR SR SA                                                          ' '22' '   109    106' ' 0.0419' '   835   4067']
     ['23' 'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ' '23' '    94    105' ' 0.6080' '  1270    923']
     ['24' 'TO BT BR BT AB                                                                                  ' '24' '    70     76' ' 0.2466' '  2234    798']
     ['25' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR SA                                           ' '25' '    35     31' ' 0.2424' '   551   5431']
     ['26' 'TO BT BT SR SR SR BT BT AB                                                                      ' '26' '    34     34' ' 0.0000' '   517    638']
     ['27' 'TO BT BR AB                                                                                     ' '27' '    34     27' ' 0.8033' '    51    447']
     ['28' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ' '28' '    33     29' ' 0.2581' ' 18155   8642']
     ['29' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR BT BT BT SA                                  ' '29' '    12     29' ' 7.0488' '  7276   1992']]


    

Presumably POM:1 HAS NO SD because theEfficiency is zero ? Why is theEfficiency 0 ? FIXED that 
-----------------------------------------------------------------------------------------------

::

    540 inline double JPMT::get_pmtid_qe( int pmtid, double energy ) const  // placeholder returing zero 
    541 {
    542     // HMM: energy or energy_eV ? standalone uses energy_eV for GPU simularity where use float 
    543     return 0. ;
    544 }

The N=0,1 standalone tests are still using JPMT for their IPMTAccessor. 
Need to use the persisted PMTSimParamData approach for the full PMT data 
to be available. 

N=0 standalone test sets the PMTAccessor, jcv HamamatsuR12860PMTManager::

    1221 void
    1222 HamamatsuR12860PMTManager::helper_fast_sim()
    1223 {
    1224     assert( m_enable_optical_model == true && m_natural_geometry == false);
    1225 
    1226     G4String name = GetName()+"_optical_model" ;
    1227 
    1228     G4Region* body_region = new G4Region(name);
    1229     body_log->SetRegion(body_region);
    1230     body_region->AddRootLogicalVolume(body_log);
    1231 
    1232     pmtOpticalModel = new junoPMTOpticalModel(name, body_phys, body_region);
    1233 
    1234 #ifdef PMTSIM_STANDALONE
    1235     const IPMTAccessor* accessor = JPMT::Get() ;   // feels silly to have more than one of these ? 
    1236     pmtOpticalModel->setPMTAccessor(accessor);
    1237 #else


N=1 standalone test also sets the PMTAccessor, u4/U4Physics::

    161 void U4Physics::ConstructOp()
    ...
    210     if(G4OpBoundaryProcess_DISABLE == 0)
    211     {
    212 #ifdef WITH_PMTSIM
    213         IPMTAccessor* ipmt = dynamic_cast<IPMTAccessor*>(new JPMT) ;
    214         fBoundary = new CustomG4OpBoundaryProcess(ipmt);
    215 #elif WITH_PMTFASTSIM
    216         IPMTAccessor* ipmt = dynamic_cast<IPMTAccessor*>(new JPMT) ;
    217         fBoundary = new InstrumentedG4OpBoundaryProcess(ipmt);
    218 #else
    219         fBoundary = new InstrumentedG4OpBoundaryProcess();
    220 #endif
    221         LOG(info) << " fBoundary " << fBoundary ;
    222     }

Now loading from persisted PMTSimParamData::

    213         const IPMTAccessor* ipmt = PMTAccessor::Load("$PMTSimParamData_BASE/PMTSimParamData") ;
    214         fBoundary = new CustomG4OpBoundaryProcess(ipmt);



NB in monolithic running the hookup happens at physics setup, jcv DsPhysConsOptical::

    336 CustomG4OpBoundaryProcess* DsPhysConsOptical::CreateCustomG4OpBoundaryProcess()
    337 {
    338     SniperPtr<IPMTSimParamSvc> psps_ptr(*getParent(), "PMTSimParamSvc");
    339 
    340     if(psps_ptr.invalid())
    341     {
    342         std::cout << "invalid" << std::endl ;
    343         return nullptr ;
    344     }
    345 
    346     IPMTSimParamSvc* ipsps = psps_ptr.data();
    347     PMTSimParamData* pspd = ipsps->getPMTSimParamData() ;
    348     IPMTAccessor* accessor = new PMTAccessor(pspd) ;
    349 
    350     CustomG4OpBoundaryProcess* boundproc = new CustomG4OpBoundaryProcess(accessor) ;
    351     return boundproc ;
    352 }



j/PMTSimParamData test loaded PMT data 
--------------------------------------------

The test demonstrates loading the PMT data from NPFold folders. Now how to 
use that capability in the tests to replace JPMT ? 

Doing this within a PMTAccessor::Load seems natural. 



DONE : Handle not enough PMTs for standalone testing giving pmtid -1 using copyNo in PMTSIM_STANDALONE
-----------------------------------------------------------------------------------------------------------

HMM : THE VERY SIMPLE N=1 PMT GEOMETRY MEANS THAT PERHAPS CAN AVOID THE COMPLICATED S4Touchable/U4Touchable ?



U4VolumeMaker::WrapAround::

    0992 void U4VolumeMaker::WrapAround( const char* prefix, const NP* trs, std::vector<G4LogicalVolume*>& lvs, G4LogicalVolume* mother_lv )
     993 {
     994     unsigned num_place = trs->shape[0] ;
     995     unsigned place_tr = trs->shape[1] ;
     996     unsigned place_values = place_tr*4*4 ;
     997     unsigned num_lv = lvs.size();
     998 
     999 
    1000     assert( trs->has_shape(num_place,place_tr,4,4) );
    1001     assert( place_tr == 6 );  // expected number of different options from "TR,tr,R,T,r,t"
    1002     enum { _TR, _tr, _R, _T, _r, _t } ;  // order must match opts "TR,tr,R,T,r,t"
    1003 
    1004     const double* tt = trs->cvalues<double>();
    1005 
    1006     for(unsigned i=0 ; i < num_place ; i++)
    1007     {
    1008         const double* T = tt + place_values*i + _T*16 ;
    1009         const double* R = tt + place_values*i + _R*16 ;
    1010 
    1011         // TODO: get these from a single matrix, not 6 
    1012 
    1013         G4ThreeVector tla( T[12], T[13], T[14] );
    1014 
    1015         LOG(LEVEL) << " i " << std::setw(7) << " tla " << U4ThreeVector::Desc(tla) ;
    1016 
    1017         bool transpose = true ;
    1018         U4RotationMatrix* rot = new U4RotationMatrix( R, transpose );  // ISA G4RotationMatrix
    1019 
    1020         LOG(LEVEL) << " i " << std::setw(7) << " rot " << U4RotationMatrix::Desc(rot) ;
    1021 
    1022         const char* iname = PlaceName(prefix, i, nullptr);
    1023 
    1024         G4bool pMany_unused = false ;
    1025         G4int  pCopyNo = (i+1)*10 ;
    1026         G4LogicalVolume* lv = lvs[i%num_lv] ;
    1027 
    1028         const G4VPhysicalVolume* pv_n = new G4PVPlacement(rot, tla, lv, iname, mother_lv, pMany_unused, pCopyNo ); // 1st ctor
    1029         assert( pv_n );
    1030     }
    1031 }




WITH SD COMPARISONS IN POM 0,1  : c2 OK : SURPRISED BY SO MUCH SD ? efficiency not that much ?
----------------------------------------------------------------------------------------------------




::

    c2sum :    34.4124 c2n :    34.0000 c2per:     1.0121 

    np.c_[siq,quo,siq,sabo2,sc2,sabo1][:30]  ## abexpr : A-B comparison of unique history counts 
    [[' 0' 'TO BT SD                                                                                        ' ' 0' ' 36013  36183' ' 0.4003' '     6      0']
     [' 1' 'TO BT SA                                                                                        ' ' 1' ' 30863  31002' ' 0.3123' '     2     13']
     [' 2' 'TO BT BT SR SA                                                                                  ' ' 2' '  9431   9442' ' 0.0064' '     3      8']
     [' 3' 'TO BT BT SR SR SR SA                                                                            ' ' 3' '  3905   3801' ' 1.4036' '     0     37']
     [' 4' 'TO BT BT SR SR SR BT BT SA                                                                      ' ' 4' '  3872   3710' ' 3.4614' '    24    147']
     [' 5' 'TO BT BR BT SA                                                                                  ' ' 5' '  2871   2814' ' 0.5715' '    15     40']
     [' 6' 'TO BT BT SR SR SR BR SR SA                                                                      ' ' 6' '  2746   2601' ' 3.9321' '    26     34']
     [' 7' 'TO BT BT SA                                                                                     ' ' 7' '  2333   2351' ' 0.0692' '    70     54']
     [' 8' 'TO BT BT SR SR SA                                                                               ' ' 8' '  1346   1447' ' 3.6523' '    60      4']
     [' 9' 'TO BT BT SR SR SR BR SR SR SR SA                                                                ' ' 9' '  1183   1183' ' 0.0000' '   159     18']
     ['10' 'TO BT BT SR SR SR BR SA                                                                         ' '10' '   634    700' ' 3.2654' '    98      1']
     ['11' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BT BT SA                                                 ' '11' '   587    556' ' 0.8408' '   606    111']
     ['12' 'TO BT BT SR SR SR BR SR SR SR BR SR SR SA                                                       ' '12' '   569    573' ' 0.0140' '   377    160']
     ['13' 'TO BT BT SR SR SR BR SR SR SR BT BT BT SD                                                       ' '13' '   419    432' ' 0.1986' '     1    209']
     ['14' 'TO BT BT SR SR SR BR SR SR SA                                                                   ' '14' '   419    407' ' 0.1743' '    56    180']
     ['15' 'TO BT BT SR SR SR BR SR SR SR BT BT BT SA                                                       ' '15' '   367    371' ' 0.0217' '   509     51']
     ['16' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SA                                                 ' '16' '   333    345' ' 0.2124' '  1040    371']
     ['17' 'TO BT AB                                                                                        ' '17' '   304    341' ' 2.1225' '   157    497']
     ['18' 'TO BR SA                                                                                        ' '18' '   312    265' ' 3.8284' '   365   1717']
     ['19' 'TO AB                                                                                           ' '19' '   224    243' ' 0.7730' '   262     10']
     ['20' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SA                                                    ' '20' '   227    224' ' 0.0200' '    47   1813']
     ['21' 'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ' '21' '   161    157' ' 0.0503' '   222     88']
     ['22' 'TO BT BT SR SR SR BR SR SR SR BR SR SA                                                          ' '22' '   152    144' ' 0.2162' '   345    196']
     ['23' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BT BT SA                                           ' '23' '   139    130' ' 0.3011' '   361   1026']
     ['24' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ' '24' '   126    101' ' 2.7533' '  1274    443']
     ['25' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR BR SR SA                                           ' '25' '    39     53' ' 2.1304' '  4042    701']
     ['26' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SA                                                    ' '26' '    40     35' ' 0.3333' '  4710    665']
     ['27' 'TO BT BT SR SR SR BT BT AB                                                                      ' '27' '    37     29' ' 0.9697' '  2303     99']
     ['28' 'TO BT BT SR SR SR BR SR SR SR BR SR SR BR SR SR SA                                              ' '28' '    27     33' ' 0.6000' '  1668   3548']
     ['29' 'TO BT BT SR SR SR BR SR SR SR BT BT BT BR BT SA                                                 ' '29' '    30     33' ' 0.1429' '  2521    269']]




DONE : Checked _qe upscaling by An : COMES DOWN TO HOW _qe defined and measured
-------------------------------------------------------------------------------------

The below from CustomART.h is just duplicating what junoPMTOpticalModel does. 
Now I need to check validity of that::

    312     // stackNormal is not flipped (as minus_cos_theta is fixed at -1.) presumably this is due to _qe definition
    313     Stack<double,4> stackNormal(wavelength_nm, -1. , spec ); 
    314     
    315     // at normal incidence S/P become meaningless, and the values converge anyhow : so no polarization worries here
    316     double An = one - (stackNormal.art.T + stackNormal.art.R) ; 
    317     double D = _qe/An;   // LOOKS STRANGE TO DIVIDE BY An : BUT IT COMES DOWN TO THE _qe DEFINITION : TODO: Check with experts. 
    318     
    319     theEfficiency = D ;
    320     


junoPMTOpticalModel::

    271     G4double R  = 0.;
    272     G4double A  = 0.;
    273     G4double An = 0.;
    274     G4double escape_fac = 0.;
    275     G4double E_s2 = 0.;
    276 
    277     if(_sin_theta1 > 0.){
    278         E_s2 = (pol*dir.cross(norm))/_sin_theta1;
    279         E_s2 *= E_s2;
    280     }else{
    281         E_s2 = 0.;
    282     }
    283 
    284     T = fT_s*E_s2 + fT_p*(1.0-E_s2);
    285     R = fR_s*E_s2 + fR_p*(1.0-E_s2);
    286     A = 1.0 - (T+R);
    287 
    288     An = 1.0 - (fT_n+fR_n);
    289     escape_fac  = _qe/An;

   
    /**




    At normal incidence factorize the QE (signal_electrons/incident_photons) into two terms::
    
    
             qe = An * escape_fac    <= fraction of photoelectrons that get from cathode to dynode and form a signal  
                                        (depends on fields inside the PMT vacuum, shape of dynodes etc.., ) 
                  ^^
                  Normal incidence absorption (from An = 1-Rn-Tn) 
                  depending on wl, properties of ARC, PHC (complex refractive indices). 
                  Material properties and EM (Maxwells) boundary conditions. 
                  (NOTHING TO DO WITH THE PMT, OTHER THAN ITS MATERIALS)

    **/
 

    ...
    309 
    310     if(escape_fac > 1.){
    311         G4cout<<"junoPMTOpticalModel: QE is larger than absorption coeff."<<G4endl;
    312     }
    313 
    314     G4double rand_absorb = G4UniformRand();
    315     G4double rand_escape = G4UniformRand();
    316 
    317     if(rand_absorb < A){
    318         // absorbed
    319         fastStep.ProposeTrackStatus(fStopAndKill);
    320         if(rand_escape<escape_fac){
    321         // detected
    322             fastStep.ProposeTotalEnergyDeposited(_photon_energy);
    323         }
    324     }else if(rand_absorb < A+R){
    325         // fastStep.ProposeTrackStatus(fStopAndKill);
    326         // reflected


Quantum Efficiency
---------------------

* https://en.wikipedia.org/wiki/Quantum_efficiency





google : absorption at boundary complex refractive index
------------------------------------------------------------

* https://geant4-forum.web.cern.ch/t/complex-refractive-index-reflectivity-absorption-at-the-surface-optical-surfaces/6290
* https://geant4-forum.web.cern.ch/t/complex-refractive-index-for-a-dielectric-dielectric-interface-photon-absorption-at-the-interface/1617




* https://www.sciencedirect.com/science/article/abs/pii/S0168900204022132




Optical Properties of Bialkali Photocathodes, D. Motta and S. Shonert
-------------------------------------------------------------------------

* https://arxiv.org/pdf/physics/0408075.pdf
* ~/opticks_refs/Optical_Properties_of_Bialkali_Photocathodes_Motta_and_Schonert_MPI_0408075.pdf



Spicer Three-step model for photoemission
-------------------------------------------

* https://www.slac.stanford.edu/pubs/slacpubs/6250/slac-pub-6306.pdf

  Modern Theory and Applications of Photocathodes, W.E.Spicer


Bulk treatment to calculate QE 
  
* Optical absorption 
* Electron transport
* Escape across surface, work functions



A new optical model for photomultiplier tubes, Published: 16 April 2022
--------------------------------------------------------------------------


* ~/opticks_refs/JUNO_MultiFilm_PMT_Optical_Model_2204.02703.pdf

* https://link.springer.com/article/10.1140/epjc/s10052-022-10288-y

Yaoguang Wang, Guofu Cao, Liangjian Wen & Yifang Wang 

The European Physical Journal C volume 82, Article number: 329 (2022) Cite this article



Interestingly, the proposed model predicts a similar level (20–30%) of light
yield excess observed in the experimental data of many liquid
scintillator-based neutrino detectors, compared with that predicted at the
stage of detector design. However, this excess has never been explained, and
the proposed PMT model provides a good explanation for it, which highlights the
imperfections of PMT models used in their detector simulations.


PDE : Photon Detection Efficiency
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The PDE is defined as the ratio of the number of detected photons to the number
of incident photons on the PMT. In general, PDE can be further decomposed into
QE and collection efficiency (CE). Based on Spicer’s three-step model [21], QE
can be considered a product of two terms: one is the absorption probability of
converting an incident photon to a photoelectron in the photocathode via the
photoelectric effect, and the other is the escape probability of the generated
photoelectrons that overcome the photocathode’s potential and become free
photoelectrons. CE is the probability of successfully collecting free
photoelectrons via built-in electrodes of the PMT. It depends on the electrical
field distributed inside the PMT. The electrical field accelerates the
photoelectrons to hit the first dynode or micro-channel plate (MCP) and knock
out secondary electrons. Then, the secondary electrons are multiplied in
multistage dynodes (MCPs) and eventually collected by the anode to form an
electrical signal. The following factors must be managed correctly to obtain an
accurate PMT optical model aimed at describing the angular and spectral
dependence of the PDE and its uniformity on PMTs. 



line test gives ReplicaDepth assert
---------------------------------------

::

    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff5582f080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff555c01ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x0000000100250371 libU4.dylib`U4Touchable::ReplicaDepth(touch=0x0000000112c26770) at U4Touchable.h:66
        frame #5: 0x000000010024bdc5 libU4.dylib`U4Touchable::ReplicaNumber(touch=0x0000000112c26770) at U4Touchable.h:36
        frame #6: 0x00000001002495a1 libU4.dylib`void U4Recorder::UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(this=0x000000010711a820, step=0x000000010743d330) at U4Recorder.cc:489
        frame #7: 0x0000000100249076 libU4.dylib`void U4Recorder::UserSteppingAction<CustomG4OpBoundaryProcess>(this=0x000000010711a820, step=0x000000010743d330) at U4Recorder.cc:111
        frame #8: 0x0000000100033c01 U4SimulateTest`U4RecorderTest::UserSteppingAction(this=0x000000010711be60, step=0x000000010743d330) at U4RecorderTest.h:190
        frame #9: 0x0000000100033c3c U4SimulateTest`non-virtual thunk to U4RecorderTest::UserSteppingAction(this=0x000000010711be60, step=0x000000010743d330) at U4RecorderTest.h:0
        frame #10: 0x0000000102afef06 libG4tracking.dylib`G4SteppingManager::Stepping(this=0x000000010743d1a0) at G4SteppingManager.cc:243
        frame #11: 0x0000000102b1586f libG4tracking.dylib`G4TrackingManager::ProcessOneTrack(this=0x000000010743d160, apValueG4Track=0x0000000112c26330) at G4TrackingManager.cc:126


    (lldb) f 6
    frame #6: 0x00000001002495a1 libU4.dylib`void U4Recorder::UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(this=0x000000010711a820, step=0x000000010743d330) at U4Recorder.cc:489
       486 	
       487 	    const G4VTouchable* touch = track->GetTouchable();  
       488 	    LOG(LEVEL) << U4Touchable::Brief(touch) ;
    -> 489 	    current_photon.iindex = U4Touchable::ReplicaNumber(touch); 
       490 	
       491 	    // first_point identified by the flagmask having a single bit (all genflag are single bits, set in beginPhoton)
       492 	    bool first_point = current_photon.flagmask_count() == 1 ;  
    (lldb) 


    (lldb) f 5
    frame #5: 0x000000010024bdc5 libU4.dylib`U4Touchable::ReplicaNumber(touch=0x0000000112c26770) at U4Touchable.h:36
       33  	
       34  	inline int U4Touchable::ReplicaNumber(const G4VTouchable* touch)  // static 
       35  	{
    -> 36  	    int d = ReplicaDepth(touch);
       37  	    return d > -1 ? touch->GetReplicaNumber(d) : d  ;
       38  	}
       39  	
    (lldb) f 4
    frame #4: 0x0000000100250371 libU4.dylib`U4Touchable::ReplicaDepth(touch=0x0000000112c26770) at U4Touchable.h:66
       63  	        << std::endl
       64  	        ; 
       65  	
    -> 66  	    assert(expected); 
       67  	
       68  	    if(!expected) return -2 ; 
       69  	
    (lldb) 


Check where this happens, probably when miss the PMT::

    In [17]: iindex = t.photon[:,1,3].view(np.int32)

    In [18]: w2 = np.where( iindex == -2 )[0]

    In [19]: w2 
    Out[19]: 
    array([86000, 86001, 86002, 86003, 86004, 86005, 86006, 86007, 86008, 86009, 86010, 86011, 86012, 86013, 86014, 86015, 86016, 86017, 86018, 86019, 86020, 86021, 86022, 86023, 86024, 86025, 86026,
           86027, 86028, 86029, 86030, 86031, 86032, 86033, 86034, 86035, 86036, 86037, 86038, 86039, 86040, 86041, 86042, 86043, 86044, 86045, 86046, 86047, 86048, 86049, ..., 99950, 99951, 99952,
           99953, 99954, 99955, 99956, 99957, 99958, 99959, 99960, 99961, 99962, 99963, 99964, 99965, 99966, 99967, 99968, 99969, 99970, 99971, 99972, 99973, 99974, 99975, 99976, 99977, 99978, 99979,
           99980, 99981, 99982, 99983, 99984, 99985, 99986, 99987, 99988, 99989, 99990, 99991, 99992, 99993, 99994, 99995, 99996, 99997, 99998, 99999])


Yep, they are all BULK_ABSORB::

    In [22]: np.unique(q[w2])
    Out[22]: array([b'TO AB                                                                                           '], dtype='|S96')

    In [26]: t.record[w2,0,0]
    Out[26]: 
    array([[   0.   ,    0.   , -300.   ,    0.   ],
           [   0.   ,    0.   , -300.005,    0.   ],
           [   0.   ,    0.   , -300.01 ,    0.   ],
           [   0.   ,    0.   , -300.015,    0.   ],
           [   0.   ,    0.   , -300.02 ,    0.   ],
           [   0.   ,    0.   , -300.025,    0.   ],
           [   0.   ,    0.   , -300.03 ,    0.   ],
           [   0.   ,    0.   , -300.035,    0.   ],
           [   0.   ,    0.   , -300.04 ,    0.   ],
           [   0.   ,    0.   , -300.045,    0.   ],
           [   0.   ,    0.   , -300.05 ,    0.   ],
           [   0.   ,    0.   , -300.055,    0.   ],


Looking at simtrace shows these are all starting in the Rock::

   ./U4SimtraceTest.sh ana 



Look into a point in unexpected position : probably scattered out of plane, YEP : all are scattered
----------------------------------------------------------------------------------------------------------------------------

::

    POM=1 N=1 ./U4SimulateTest.sh ph 


    x_pick = np.logical_and( pos[:,0] > -90, pos[:,0] < -80 )     
    z_pick = np.logical_and( pos[:,2] >  25, pos[:,2] <  35 )    
    xz_pick = np.logical_and( x_pick, z_pick )
    w_xz_pick = np.where(xz_pick)[0]  

    In [4]: w_xz_pick
    Out[4]: array([58825])

    In [5]: q[w_xz_pick]
    Out[5]: array([[b'TO SC BT SD                                                                                     ']], dtype='|S96')

    In [6]: t.record[w_xz_pick, :4, 0]
    Out[6]: 
    array([[[  0.   ,   0.   , -44.125,   0.   ],
            [-20.458,   0.   , -44.125,   0.094],
            [-77.808,  85.647,  26.076,   0.666],
            [-85.206,  91.938,  31.596,   0.723]]], dtype=float32)

    In [34]: w_y_out = np.where( np.sum( t.record[:,:,0,1], axis=1 ) != 0. )[0]

    In [35]: w_y_out
    Out[35]: 
    array([  338,   378,  2649,  3492,  6580,  6728,  7650, 11062, 12433, 12458, 13046, 13397, 14534, 15749, 16232, 19363, 20549, 21046, 21364, 21376, 22532, 22550, 24197, 24813, 26886, 29429, 30662,
           30964, 32023, 32113, 32426, 33414, 34622, 35774, 40195, 43872, 44087, 45979, 49716, 50816, 52351, 53137, 53171, 53463, 54587, 57026, 58825, 61622, 61847, 63109, 67114, 67946, 68046, 68443,
           69296, 73834, 73952, 74495, 75530, 77971, 78283, 79067, 79909, 81176, 84122, 84829, 87152, 89328, 89602, 90785, 91198, 91831, 93217, 94576, 95876, 96096, 96120, 98079, 99277, 99521])

    In [36]: q[w_y_out]
    Out[36]: 
    array([[b'TO BT BR BT SC SA                                                                               '],
           [b'TO SC BT BR BT SA                                                                               '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC BT SA                                                                                     '],
           [b'TO SC BT SD                                                                                     '],
           [b'TO SC BT SA                                                                                     '],
           [b'TO SC BT SA                                                                                     '],


Its better to use np.abs and np.max rather than np.sum which could be tricked by symmetry::

    In [3]: yy = t.record[:,:,0,1]

    In [12]: myy = np.max( np.abs(yy), axis=1 )     ## max absolute y of all step points for each photon

    In [17]: wyy = np.where( myy > 0 )[0]

    In [18]: q[wyy]
    Out[18]: 
    array([[b'TO BT BR BT SC SA                                                                               '],
           [b'TO SC BT BR BT SA                                                                               '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC SA                                                                                        '],
           [b'TO SC BT SA                                                                                     '],




TODO : Suspect N=0/1 POM=1 discrepant efficiency from different pmtid : IT IS PUSHING UP CHI2
-----------------------------------------------------------------------------------------------


TODO : 4 PMTs (2 HAMA, 2 NNVT) to check PMTAccessor access to specific PMT qe, also check get SD
----------------------------------------------------------------------------------------------------


TODO : MORE THAN 4 PMTs : JUST MACHINERY CHECK
--------------------------------------------------


TODO : WIDE BEAM, RANDOM DIRECTIONS FOR 3D CHECK
--------------------------------------------------------


TODO : POM:0,1 CHECK MIRROR PORTION : IE SHOOT THE SIDE/BACK OF PMT
------------------------------------------------------------------------------




