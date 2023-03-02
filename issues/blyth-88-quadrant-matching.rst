blyth-88-quadrant-matching.rst
=================================

* from :doc:`blyth-88-incorporation-notes`


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





Where did I do skipping before ? microstep ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


~~~~~~~

::

    epsilon:opticks blyth$ opticks-fl StepTooSmall
    ./ana/g4lldb.py
    ./cfg4/CBoundaryProcess.hh
    ./cfg4/CRecorderLive.cc
    ./cfg4/DsG4OpBoundaryProcessStatus.h
    ./cfg4/CBoundaryProcess.cc
    ./cfg4/OpStatus.cc
    ./cfg4/CRandomEngine.cc
    ./cfg4/CCtx.cc
    ./cfg4/CRecorder.cc
    ./cfg4/CRecorder.hh
    ./cfg4/DsG4OpBoundaryProcess.cc
    ./cfg4/CRec.cc
    ./integration/tests/tboolean.bash
    ./extg4/X4OpBoundaryProcessStatus.hh
    ./u4/U4OpBoundaryProcessStatus.h
    ./u4/U4StepPoint.cc
    ./u4/U4Recorder.cc
    ./u4/InstrumentedG4OpBoundaryProcess.hh
    ./u4/InstrumentedG4OpBoundaryProcess.cc
    ./examples/Geant4/BoundaryStandalone/G4OpBoundaryProcess_MOCK.cc
    ./examples/Geant4/BoundaryStandalone/G4OpBoundaryProcess_MOCK.hh
    epsilon:opticks blyth$ 


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


