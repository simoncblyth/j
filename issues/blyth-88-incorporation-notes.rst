blyth-88-incorporation-notes.rst
=====================================

Next
-----

* :doc:`blyth-88-quadrant-matching`


Speeddial
----------

::
 
    jcv HamamatsuR12860PMTManager
    jcv NNVTMCPPMTManager


WIP : Standalone U4SimulateTest.sh : checking all four quadrants are operational for both hama and nnvt PMTs
----------------------------------------------------------------------------------------------------------------


+----------------+------------------------+--------------------------+
|                | PMT:0  (unnatural)     | PMT:1  (natural)         |  
+================+========================+==========================+
| POM:0          |                        |  #CustomG4OpBoundary     |
| (traditional)  |                        |                          | 
+----------------+------------------------+--------------------------+
| POM:1          |     FastSim            |  @CustomG4OpBoundary     | 
| (ph in PMT)    |                        |                          | 
+----------------+------------------------+--------------------------+

HMM: this means must switch from the InstrumentedG4OpBoundaryProcess to CustomG4OpBoundary ?



Where to hookup the Accessor ? : DOING THIS IN junoPMTOpticalModel
-----------------------------------------------------------------------

::

    (lldb) f 4
    frame #4: 0x0000000100872641 libPMTSim.dylib`junoPMTOpticalModel::DoIt(this=0x000000010724a5a0, fastTrack=0x000000010724ae80, fastStep=0x000000010724afd8) at junoPMTOpticalModel.cc:141
       138 	    int pmtid  = get_pmtid(track);
       139 	
       140 	#ifdef PMTSIM_STANDALONE
    -> 141 	    assert( m_PMTAccessor ); 
       142 	    int pmtcat = m_PMTAccessor->get_pmtcat(pmtid) ; 
       143 	    _qe  = m_PMTAccessor->get_pmtid_qe(pmtid, energy);
       144 	
    (lldb) ^D
    epsilon:tests blyth$ 



BoundaryProcess compile-time or run-time switch ?
----------------------------------------------------

G4OpBoundaryProcess
   standard

CustomG4OpBoundaryProcess
   customizations only take effect for special '@' '#' OpticalSurfaceName[0]

InstrumentedG4OpBoundaryProcess
   TODO: review the changes, what does history recording depend on ? 



U4Recorder.{h,cc}:: 

    068     // HMM: anyway to hide the type here ? 
     69     template<typename T> void UserSteppingAction(const G4Step*);
     70     template<typename T> void UserSteppingAction_Optical(const G4Step*);

    613 #include "InstrumentedG4OpBoundaryProcess.hh"
    615 template void U4Recorder::UserSteppingAction<InstrumentedG4OpBoundaryProcess>(const G4Step*) ;
    616 template void U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(const G4Step*) ;

    # just plants the symbols it doesnt mean they will be used
    # could those be moved to the Test.cc ?

tests/U4RecorderTest.h::

    180 #include "InstrumentedG4OpBoundaryProcess.hh"
    181 void U4RecorderTest::UserSteppingAction(const G4Step* step){     fRecorder->UserSteppingAction<InstrumentedG4OpBoundaryProcess>(step); }
    182 // HMM: can this be templated ?


tests/U4SimulateTest.cc::

    011 #include "U4RecorderTest.h"



Decided to use simple compile time switch between Custom and Instrumented::


    613 #ifdef WITH_PMTSIM
    614 
    615 #include "CustomG4OpBoundaryProcess.hh"
    616 template void U4Recorder::UserSteppingAction<CustomG4OpBoundaryProcess>(const G4Step*) ;
    617 template void U4Recorder::UserSteppingAction_Optical<CustomG4OpBoundaryProcess>(const G4Step*) ;
    618 
    619 #else
    620 
    621 #include "InstrumentedG4OpBoundaryProcess.hh"
    622 template void U4Recorder::UserSteppingAction<InstrumentedG4OpBoundaryProcess>(const G4Step*) ;
    623 template void U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(const G4Step*) ;
    624 
    625 #endif




Get Oriented 
---------------


All 1000 photons are starting from same position along Z axis and travelling in +X direction::

    In [10]: t.record[:,0,0]
    Out[10]: 
    array([[   0.,    0., -120.,    0.],
           [   0.,    0., -120.,    0.],
           [   0.,    0., -120.,    0.],
           [   0.,    0., -120.,    0.],
           [   0.,    0., -120.,    0.],
           [   0.,    0., -120.,    0.],

    In [11]: t.record[:,0,1]
    Out[11]: 
    array([[ 1.,  0.,  0., nan],
           [ 1.,  0.,  0., nan],
           [ 1.,  0.,  0., nan],
           [ 1.,  0.,  0., nan],
           [ 1.,  0.,  0., nan],



Refraction angle difference 
-----------------------------

::

    APID=17 BPID=7  N=1 ./U4SimtraceTest.sh ana



::

    junoPMTOpticalModel::DoIt@344:  pmtid 0 pmtcat 0 status R A 0.376787 R 0.292582 A+R 0.669369 D 0 label spho (gs:ix:id:gn   0 451  451[  0,  0,  0, 82])
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   451 seq TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BR BT SR SA
    junoPMTOpticalModel::DoIt@173:  pmtid 0 pmtcat 0 _qe 0 _photon_energy/eV 2.952 n_glass 1.48426 n_coating 1.53735 k_coating 0 d_coating 40 n_photocathode 2.33045 k_photocathode 1.22533 d_photocathode 20.58 n_vacuum 1


    In [1]: q[451]
    Out[1]: array([b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BR BT SR SA                         '], dtype='|S96')




Global vs Local normal mixup ?
-----------------------------------


Compare A:17 with B:7 because of similar history:: 


    epsilon:tests blyth$ N=0 POM=1 PIDX=17 ./U4SimulateTest.sh

    junoPMTOpticalModel::Refract@441:  PIDX 17 m_label->ix 17 norm (0.377629,-0,-0.925957) dir (-0.149856,0,-0.988708) _n1 1.48426 _n4 1 _cos_theta1 0.938589



    epsilon:tests blyth$ N=1 POM=1 PIDX=7 ./U4SimulateTest.sh 

    *CustomG4OpBoundaryProcess::PostStepDoIt@209:  PIDX 7 m_label spho (gs:ix:id:gn   0   7    7[  0,  0,  0,  0])
    *CustomG4OpBoundaryProcess::PostStepDoIt@306:  PIDX 7 haveEnteredDaughter 1 theGlobalNormal (0.928166,0,0.372166) theRecoveredNormal (-0.928166,-0,-0.372166)
    *CustomG4OpBoundaryProcess::PostStepDoIt@209:  PIDX 7 m_label spho (gs:ix:id:gn   0   7    7[  0,  0,  0,  0])
    *CustomG4OpBoundaryProcess::PostStepDoIt@306:  PIDX 7 haveEnteredDaughter 1 theGlobalNormal (0.925957,0,0.377629) theRecoveredNormal (-0.925957,-0,-0.377629)
    *CustomG4OpBoundaryProcess::PostStepDoIt@209:  PIDX 7 m_label spho (gs:ix:id:gn   0   7    7[  0,  0,  0,  0])
    *CustomG4OpBoundaryProcess::PostStepDoIt@306:  PIDX 7 haveEnteredDaughter 1 theGlobalNormal (1,-0,-0) theRecoveredNormal (-1,0,0)
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id     7 seq TO BT BT SA



HMM the transition from local dir, pol directions back to global must happen here::

    401 void junoPMTOpticalModel::UpdateTrackInfo(G4FastStep &fastStep)
    402 {
    403     fastStep.SetPrimaryTrackFinalTime(time);
    404     fastStep.SetPrimaryTrackFinalPosition(pos);
    405     fastStep.SetPrimaryTrackFinalMomentum(dir);
    406     fastStep.SetPrimaryTrackFinalPolarization(pol);
    407     fastStep.ForceSteppingHitInvocation();
    408 }

    123 void
    124 G4FastStep::
    125 ProposePrimaryTrackFinalMomentumDirection(const G4ThreeVector &momentum,
    126                                           G4bool localCoordinates)
    127 {
    128   // Compute the momentum in global reference
    129   // system if needed ...
    130   G4ThreeVector globalMomentum = momentum;
    131   if (localCoordinates)
    132     globalMomentum = fFastTrack->GetInverseAffineTransformation()->
    133       TransformAxis(momentum);
    134   // ...and feed the globalMomentum (ensuring unitarity)
    135   SetMomentumChange(globalMomentum.unit());
    136 }
    137 
    138 void
    139 G4FastStep::
    140 SetPrimaryTrackFinalMomentum(const G4ThreeVector &momentum,
    141                              G4bool localCoordinates)
    142 {
    143   ProposePrimaryTrackFinalMomentumDirection(momentum, localCoordinates);
    144 }

Is that immediately set back into the track ?

::

    CustomG4OpBoundaryProcess::PostStepDoIt@306:  PIDX 17 haveEnteredDaughter 1 theGlobalNormal (0.925958,0,0.377628) theRecoveredNormal (-0.925958,-0,-0.377628)
    junoPMTOpticalModel::Refract@447:  PIDX 17 m_label->ix 17 norm (0.377629,-0,-0.925957) dir (-0.149856,0,-0.988708) _n1 1.48426 _n4 1 _cos_theta1 0.938589
    junoPMTOpticalModel::DoIt@343:  PIDX 17 track.GetMomentumDirection (0.999389,0,0.0349492)


    In [6]: t.record[17,:6,:2]
    Out[6]: 
    array([[[   0.   ,    0.   , -120.   ,    0.   ],
            [   1.   ,    0.   ,    0.   ,      nan]],

           [[  82.54 ,    0.   , -120.   ,    0.379],
            [   0.999,    0.   ,    0.035,      nan]],

           [[  87.824,    0.   , -119.815,    0.406],
            [   0.999,    0.   ,    0.035,      nan]],

           [[  87.826,    0.   , -119.815,    0.406],
            [   0.989,    0.   ,   -0.15 ,      nan]],

           [[ 250.   ,    0.   , -144.396,    1.241],
            [   0.989,    0.   ,   -0.15 ,      nan]],

           [[ 392.859,    0.   , -166.048,    1.978],
            [   0.989,    0.   ,   -0.15 ,      nan]]], dtype=float32)

    In [2]: t.record[7,:4,:2]
    Out[2]: 
    array([[[   0.   ,    0.   , -120.   ,    0.   ],
            [   1.   ,    0.   ,    0.   ,      nan]],

           [[  82.54 ,    0.   , -120.   ,    0.379],
            [   0.999,    0.   ,    0.035,      nan]],

           [[  87.826,    0.   , -119.815,    0.406],
            [   0.999,    0.   ,    0.035,      nan]],    ### HMM: SAW THIS BEFORE : TRANSMITTED WITHOUT CHANGE IN DIRECTION 

           [[ 402.44 ,    0.   , -108.813,    1.456],
            [   0.999,    0.   ,    0.035,      nan]]], dtype=float32)







Second most prolific history : "TO BT BT SA" getting absorbed at back of PMT
------------------------------------------------------------------------------

::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'583' b'0' b'TO BT SA                                                                                        ']
     [b'313' b'7' b'TO BT BT SA                                                                                     ']
     [b'78' b'13' b'TO BT BR BT SA                                                                                  ']
     [b'10' b'8' b'TO BT BT SR SA                                                                                  ']
     [b'3' b'23' b'TO BT BT SR SR SR SA                                                                            ']


Look into lots of "TO BT BT SA" for 4th quadrant::

    N=1 POM=1 ./U4SimulateTest.sh  

::

    In [18]: ws_ = 1   ## 2nd most prolific history 
    In [19]: ws = np.where( q[:,0] == qu[quo][ws_] )


    In [24]: t.record[ws, :4,0]
    Out[24]: 
    array([[[[   0.   ,    0.   , -120.   ,    0.   ],
             [  82.54 ,    0.   , -120.   ,    0.379],
             [  87.826,    0.   , -119.815,    0.406],
             [ 402.44 ,    0.   , -108.813,    1.456]],

            [[   0.   ,    0.   , -120.   ,    0.   ],
             [  82.54 ,    0.   , -120.   ,    0.379],
             [  87.826,    0.   , -119.815,    0.406],
             [ 402.44 ,    0.   , -108.813,    1.456]],

            [[   0.   ,    0.   , -120.   ,    0.   ],
             [  82.54 ,    0.   , -120.   ,    0.379],
             [  87.826,    0.   , -119.815,    0.406],
             [ 402.44 ,    0.   , -108.813,    1.456]],

::

     N=1 BPID=7 ./U4SimtraceTest.sh ana

HMM: N=0 POM=1 ending up somewhere else::

            [[   0.   ,    0.   , -120.   ,    0.   ],
             [  82.54 ,    0.   , -120.   ,    0.379],
             [  87.824,    0.   , -119.815,    0.406],
             [  87.826,    0.   , -119.815,    0.406],
             [ 250.   ,    0.   , -144.396,    1.241],
             [ 392.859,    0.   , -166.048,    1.978]]]], dtype=float32)


Use two U4SimulateTest.sh sessions::

     N=0 POM=1 ./U4SimulateTest.sh ph  
     N=1 POM=1 ./U4SimulateTest.sh ph



Look for adjacent quadrant equivalent::

    N=0 POM=1 ./U4SimulateTest.sh  

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'571' b'0' b'TO BT BT SA                                                                                     ']
     [b'104' b'2' b'TO BT BT BT BT SR BT SA                                                                         ']
     [b'104' b'6' b'TO BT BT BR BT BT SA                                                                            ']
     [b'92' b'5' b'TO BT BT BT BT SR BT BT BT BT SA                                                                ']
     [b'37' b'30' b'TO BT BT BT BT SR BT BR BT SA                                                                   ']
     5: [b'31' b'65' b'TO BT BT BT BT SA                                                                               ']
     [b'20' b'32' b'TO BT BT BT BT SR BT BR BT SR SR BT SA                                                          ']
     [b'13' b'55' b'TO BT BT BT BT SR BT BR BT SR SR BT BT BT BT SA                                                 ']
     [b'5' b'278' b'TO BT AB                                                                                        ']
     [b'4' b'190' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT SA                                              ']
     [b'3' b'306' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT SA                                  ']



Sixth most prolific::

    In [1]: ws_ = 5
    In [2]: ws = np.where( q[:,0] == qu[quo][ws_] )

    In [3]: q[ws]
    Out[3]: 
    array([[b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],

    In [5]: t.record[ws,:6,0]   
    Out[5]: 
    array([[[[   0.   ,    0.   , -120.   ,    0.   ],
             [ -87.828,    0.   , -120.   ,    0.403],
             [ -93.087,    0.   , -119.822,    0.43 ],
             [ -93.088,    0.   , -119.822,    0.43 ],
             [-250.   ,    0.   , -142.762,    1.238],
             [-385.576,    0.   , -162.583,    1.936]],


    ## AHHA : photon going the other way, so will hit the other PMT type giving very different history  


    In [8]: t.record[:,0,1]     ## recall flipping the direction, where did I do that ?
    Out[8]: 
    array([[-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],
           [-1.,  0.,  0., nan],

Direction was flipped at bash level in U4SimulateTest.sh get rid of that flip::

    126 ## when comparing quadrants between N=0/1 VERSION 
    127 ## it is confusing to flip direction : so keep them the same +X for now
    128 mom=1,0,0
    129 case $VERSION in
    130    0) mom=1,0,0 ;;
    131    1) mom=1,0,0  ;;
    132 esac


After avoid the mom direction flip::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'595' b'0' b'TO BT BT SA                                                                                     ']
     [b'105' b'3' b'TO BT BT BR BT BT SA                                                                            ']
     [b'105' b'5' b'TO BT BT BT BT SR SA                                                                            ']
     [b'46' b'13' b'TO BT BT BT BT SR SR SR BT SA                                                                   ']
     [b'38' b'41' b'TO BT BT BT BT SR SR SR BT BT BT BT SA                                                          ']
     [b'27' b'48' b'TO BT BT BT BT SR SR SR BT BR BT SR SA                                                          ']
     6: [b'22' b'17' b'TO BT BT BT BT SA                                                                               ']
     [b'13' b'201' b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT SA                                                 ']
     [b'9' b'336' b'TO BT BT BT BT SR SR SA                                                                         ']
     [b'8' b'203' b'TO BT BT BT BT SR SR SR BT BR BT SR SR SR BT BR BT SR SR BT BT BT BT SA                         ']








Fourth Quadrant
-----------------

::

    epsilon:tests blyth$ N=1 POM=1 ./U4SimulateTest.sh 


    CustomART::doIt count 0 pmtid -1 _si    0.34504 _si2    0.34504 theRecoveredNormal (-0.92596,-0.00000,-0.37763) OldPolarization*OldMomentum.cross(theRecoveredNormal) -0.34504 E_s2    1.00000
    CustomART::doIt count 0 S    1.00000 P    0.00000 T    0.30529 R    0.10361 A    0.59110
    CustomART::desc theGlobalPoint (87.8255,0,-119.815) theRecoveredNormal (-0.925957,-0,-0.377629) theTransmittance    0.30529 theReflectivity    0.10361 theEfficiency    0.00000
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id     3 seq TO BT SA
    CustomART::doIt pmtid -1 pmtcat 0 minus_cos_theta -0.93859 _qe 0.00000 wavelength_nm 420.00000 energy_eV 2.95200 spec 


* because only one PMT of each type (one HAMA, one NNVT) get pmtid -1, pmtcat 0
* WHY is that causing lots of "TO BT SA" ? 

::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'583' b'0' b'TO BT SA                                                                                        ']
     [b'313' b'7' b'TO BT BT SA                                                                                     ']
     [b'78' b'13' b'TO BT BR BT SA                                                                                  ']
     [b'10' b'8' b'TO BT BT SR SA                                                                                  ']
     [b'3' b'23' b'TO BT BT SR SR SR SA                                                                            ']
     [b'3' b'287' b'TO BT BT SR SR SR BT BT SA                                                                      ']
     [b'3' b'452' b'TO AB                                                                                           ']
     [b'2' b'117' b'TO BT AB                                                                                        ']
     [b'1' b'239' b'TO SC SA                                                                                        ']
     [b'1' b'295' b'TO BT BT SR SR SR BR SR SR SR SA                                                                ']
     [b'1' b'18' b'TO BT BT SR SR SR BR SR SR SR BT BT BT BT SR SA                                                 ']
     [b'1' b'136' b'TO BT BT SR SR SR BR SR SR SR BR SA                                                             ']
     [b'1' b'373' b'TO BT BT SR SR SR BR SA                                                                         ']]


After fixing FastSim nan issue, the histories are more similar (modulo the fakes)::

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'571' b'0' b'TO BT BT SA                                                                                     ']
     [b'104' b'2' b'TO BT BT BT BT SR BT SA                                                                         ']
     [b'104' b'6' b'TO BT BT BR BT BT SA                                                                            ']
     [b'92' b'5' b'TO BT BT BT BT SR BT BT BT BT SA                                                                ']
     [b'37' b'30' b'TO BT BT BT BT SR BT BR BT SA                                                                   ']
     [b'31' b'65' b'TO BT BT BT BT SA                                                                               ']
     [b'20' b'32' b'TO BT BT BT BT SR BT BR BT SR SR BT SA                                                          ']
     [b'13' b'55' b'TO BT BT BT BT SR BT BR BT SR SR BT BT BT BT SA                                                 ']
     [b'5' b'278' b'TO BT AB                                                                                        ']
     [b'4' b'190' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT SA                                              ']
     [b'3' b'306' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT SA                                  ']
     [b'3' b'137' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SA                                                    ']
     [b'2' b'82' b'TO BR SA                                                                                        ']
     [b'2' b'221' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT BT BT BT BT BT SA                   ']
     [b'1' b'36' b'TO BT BT BR BT BT AB                                                                            ']
     [b'1' b'626' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT BT BT BT BT BT BR BT BT SA          ']
     [b'1' b'59' b'TO BT BT BT BT SR BT BR BT SR SA                                                                ']
     [b'1' b'283' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT BR BT SR BT BR BT SA                ']
     [b'1' b'350' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BR BT SR BT BR BT SR BT BT BT BT SA             ']
     [b'1' b'866' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BT BT BT BT BT BR BT BT SA                      ']
     [b'1' b'273' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BT BT BT BT BT BT BT SA                         ']
     [b'1' b'114' b'TO BT BT BT BT SR BT BR BT SR SR BT BR BT SR BT BT BT BT BT BT SA                               ']
     [b'1' b'972' b'TO AB                                                                                           ']]




With lots of nan causing FastSim to only transmit::

    epsilon:tests blyth$ N=0 POM=1 ./U4SimulateTest.sh 

    np.c_[qn,qi,qu][quo]  ## unique histories qu in descending count qn order, qi first index 
    [[b'900' b'0' b'TO BT BT BT BT SR BT BT BT BT SA                                                                ']
     [b'88' b'19' b'TO BT BT BT BT SA                                                                               ']
     [b'2' b'146' b'TO BT BT BT BT SR BT BT BT BT SC SA                                                             ']
     [b'2' b'283' b'TO BT BT BT BT SR BT BT BT BT AB                                                                ']
     [b'2' b'137' b'TO BT BT BT BT SR BT BT BT BR BT BT BT SR SR BT BT BT BT SA                                     ']
     [b'2' b'594' b'TO BT AB                                                                                        ']
     [b'2' b'351' b'TO BR SA                                                                                        ']
     [b'1' b'206' b'TO BT BT BT BT SR BT BT BT AB                                                                   ']
     [b'1' b'218' b'TO AB                                                                                           ']]

Adding junoPMTOpticalModel debug see that FastSim quadrant has lots of nan::

    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status X
    junoPMTOpticalModel::DoIt@157:  pmtid 0 pmtcat 0 _qe 0 _photon_energy/eV 2.952
    junoPMTOpticalModel::DoIt@263:  E_s2 1 fT_s nan fT_p nan T nan fR_s nan fR_p nan R nan A nan fT_n 0 fR_n nan An nan escape_fac nan
    junoPMTOpticalModel::DoIt@326:  pmtid 0 pmtcat 0 status T A nan R nan A+R nan D nan
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id    25 seq TO BT BT BT BT SR BT BT BT BT SA
    junoPMTOpticalModel::DoIt@157:  pmtid 0 pmtcat 0 _qe 0 _photon_energy/eV 2.952


nan were caused by mixing m and nm for wavelength units::

    junoPMTOpticalModel::DoIt@344:  pmtid 0 pmtcat 0 status A A 0.589441 R 0.103227 A+R 0.692668 D 0
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id    20 seq TO BT BT SA
    junoPMTOpticalModel::DoIt@173:  pmtid 0 pmtcat 0 _qe 0 _photon_energy/eV 2.952 n_glass 1.48426 n_coating 1.53735 k_coating 0 d_coating 40 n_photocathode 2.33045 k_photocathode 1.22533 d_photocathode 20.58 n_vacuum 1
    junoPMTOpticalModel::DoIt@250:  _cos_theta1 0.942086 _aoi 19.5951
    junoPMTOpticalModel::DoIt@281:  E_s2 1 fT_s 0.307332 fT_p 0.36157 T 0.307332 fR_s 0.103227 fR_p 0.086352 R 0.103227 A 0.589441 fT_n 0.338183 fR_n 0.0969988 An 0.564818 escape_fac 0
    junoPMTOpticalModel::DoIt@344:  pmtid 0 pmtcat 0 status A A 0.589441 R 0.103227 A+R 0.692668 D 0
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id    19 seq TO BT BT SA
    junoPMTOpticalModel::DoIt@173:  pmtid 0 pmtcat 0 _qe 0 _photon_energy/eV 2.952 n_glass 1.48426 n_coating 1.53735 k_coating 0 d_coating 40 n_photocathode 2.33045 k_photocathode 1.22533 d_photocathode 20.58 n_vacuum 1
    junoPMTOpticalModel::DoIt@250:  _cos_theta1 0.942086 _aoi 19.5951
    junoPMTOpticalModel::DoIt@281:  E_s2 1 fT_s 0.307332 fT_p 0.36157 T 0.307332 fR_s 0.1032



@Custom quadrant very different histories to FastSim quadrant
----------------------------------------------------------------

* getting loadsa "TO BT SA"


::

    epsilon:tests blyth$ N=1 POM=1 ./U4SimulateTest.sh 


    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   129 seq TO BT BR BT SA
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   128 seq TO BT SA
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   127 seq TO BT SA
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   126 seq TO BT SA
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   125 seq TO BT SA
    CustomG4OpBoundaryProcess::PostStepDoIt m_custom_status Y
    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   124 seq TO BT SA





FastSim quadrant with Custom missing something needed by the recorder
--------------------------------------------------------------------------

::

    u4t
    ./U4SimulateTest.sh 

    ..

    U4Recorder::PostUserTrackingAction_Optical@353:  l.id   921 seq TO BT BT    BT SR BT    BT BT SA
    U4Recorder::UserSteppingAction_Optical@519:  DEFER_FSTRACKINFO  FAILED TO GET THE FastSim status from trackinfo  fstrackinfo_stat 
    U4Recorder::UserSteppingAction_Optical@532:  ERR flag zero : post U4StepPoint::Desc
     proc 5 procName fast_sim_man procNameRaw fast_sim_man
     status 1 statusName fGeomBoundary
     bstat 12 bstatName SameMaterial
     flag 2097152 flagName DEFER_FSTRACKINFO



j/PMTFastSim/junoPMTOpticalModel has instrumentation to plant FastSim status info into track label::

     310 void junoPMTOpticalModel::DoIt(const G4FastTrack& fastTrack, G4FastStep &fastStep)
     311 {
     ...
     563     spho* label = STrackInfo<spho>::GetRef(track);
     564     LOG_IF(fatal, !label)
     565         << " all photon tracks must be labelled "
     566         << " track " << track
     567         << std::endl
     568         << STrackInfo<spho>::Desc(track)
     569         ;
     570 
     571     assert( label );
     572     label->uc4.w = status ;


Fixed FastSim quadrant by doing something similar in monolith "jcv junoPMTOpticalModel"::

    280 #ifdef PMTSIM_STANDALONE
    281     G4double& u0 = rand_absorb ;
    282     G4double& u1 = rand_escape ;
    283     G4double& D  = escape_fac ;
    284  
    285     char status = '?' ;
    286     if(      u0 < A)    status = u1 < D ? 'D' : 'A' ;
    287     else if( u0 < A+R)  status = 'R' ; 
    288     else                status = 'T' ;
    289 
    290     spho* label = STrackInfo<spho>::GetRef(track);
    291     assert( label && "all photon tracks must be labelled" );
    292     label->uc4.w = status ;
    293 
    294     if(status != 'T') std::cout << "junoPMTOpticalModel::DoIt " << status << std::endl ;
    295 #endif  
    296 
    297     return;
    298 }       




HMM : some Instrumented still left 
-------------------------------------



::

    u4t
    ./U4SimulateTest.sh dbg


    (lldb) bt
    * thread #1, queue = 'com.apple.main-thread', stop reason = signal SIGABRT
      * frame #0: 0x00007fff55664b66 libsystem_kernel.dylib`__pthread_kill + 10
        frame #1: 0x00007fff5582f080 libsystem_pthread.dylib`pthread_kill + 333
        frame #2: 0x00007fff555c01ae libsystem_c.dylib`abort + 127
        frame #3: 0x00007fff555881ac libsystem_c.dylib`__assert_rtn + 320
        frame #4: 0x00000001002487fb libU4.dylib`U4Recorder::Check_TrackStatus_Flag(this=0x00000001070e5ea0, tstat=fStopAndKill, flag=0, from="UserSteppingAction_Optical") at U4Recorder.cc:600
        frame #5: 0x0000000100249eeb libU4.dylib`void U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(this=0x00000001070e5ea0, step=0x00000001070bc060) at U4Recorder.cc:546
        frame #6: 0x0000000100248d76 libU4.dylib`void U4Recorder::UserSteppingAction<InstrumentedG4OpBoundaryProcess>(this=0x00000001070e5ea0, step=0x00000001070bc060) at U4Recorder.cc:101
        frame #7: 0x0000000100033c21 U4SimulateTest`U4RecorderTest::UserSteppingAction(this=0x00000001070e74e0, step=0x00000001070bc060) at U4RecorderTest.h:179
        frame #8: 0x0000000100033c5c U4SimulateTest`non-virtual thunk to U4RecorderTest::UserSteppingAction(this=0x00000001070e74e0, step=0x00000001070bc060) at U4RecorderTest.h:0



::

    (lldb) f 1
    frame #1: 0x0000000100247dd6 libU4.dylib`void U4Recorder::UserSteppingAction<InstrumentedG4OpBoundaryProcess>(this=0x00000001076ab9b0, step=0x0000000107681b50) at U4Recorder.cc:101
       98  	void U4Recorder::PostUserTrackingAction(const G4Track* track){ LOG(LEVEL) ; if(U4Track::IsOptical(track)) PostUserTrackingAction_Optical(track); }
       99  	
       100 	template<typename T>
    -> 101 	void U4Recorder::UserSteppingAction(const G4Step* step){ if(U4Track::IsOptical(step->GetTrack())) UserSteppingAction_Optical<T>(step); }
       102 	
       103 	/**
       104 	U4Recorder::PreUserTrackingAction_Optical
    (lldb) f 0
    frame #0: 0x00000001002480c9 libU4.dylib`void U4Recorder::UserSteppingAction_Optical<InstrumentedG4OpBoundaryProcess>(this=0x00000001076ab9b0, step=0x0000000107681b50) at U4Recorder.cc:434
       431 	    quad4& current_aux = sev->current_ctx.aux ; 
       432 	
       433 	    SOpBoundaryProcess* bop = SOpBoundaryProcess::Get(); 
    -> 434 	    current_aux.q0.f.x = bop->getU0() ; 
       435 	    current_aux.q0.i.w = bop->getU0_idx() ; 
       436 	
       437 	    /*
    (lldb) p bop
    (SOpBoundaryProcess *) $0 = 0x0000000000000000
    (lldb) 




DONE : Standalone U4SimtraceTest.sh with PMTSim standalone geometry, including hama and nnvt PMTs
---------------------------------------------------------------------------------------------------------

HMM: currently U4SimtraceTest.sh/U4SimulateTest.sh is limited to 
a single type of PMT picked via GEOM envvar. 

* extended U4VolumeMaker to remove that limitation using "${GEOM}_GEOMList" envvar etc..   


GEOMWrap::

    export ${GEOM}_GEOMWrap=AroundCircle 
    export U4VolumeMaker_MakeTransforms_AroundCircle_radius=250
    export U4VolumeMaker_MakeTransforms_AroundCircle_numInRing=2
    export U4VolumeMaker_MakeTransforms_AroundCircle_fracPhase=0

Allows multiple PMTs but they are currently restricted to all 
being from the same manager (eg same PMT type). 

Need to generalize to constructing geometries with more than one type of PMT. 



Review UsePMTOpticalModel switch effect, consider how to switch between impl
-------------------------------------------------------------------------------

Must maintain clear distinction in mind between the high level PMT Optical Model (POM) approach
and the PMT geometry Unnatural/natural implementation. 

Four POM*PMT cases to consider::
   
               +-------------------------+--------------------------+-------------------------------+   
               |  4 POM*PMT cases        | Unnatural PMT Impl       |  Natural PMT Impl             |
               +=========================+==========================+===============================+   
               |  Traditional POM        |                          |                               |
               |  (all Detection         |  ProcessHits QE          |  CustomG4OpBoundaryProcess    |
               |   at photocathode)      |                          |                               |
               |                         |                          |                               |
               |                         | OpticalSurfaceName       |  OpticalSurfaceName           |
               |                         | without special prefix   |  starting '#'                 |
               |                         |                          |                               |
               |  (ph stop at cathode)   |                          |                               |
               +-------------------------+--------------------------+-------------------------------+
               |  MultiFilm POM          |                          |                               |
               |  (photons refract       | junoPMTOpticalModel.hh   | MultiLayrStack.h              |
               |   into PMT, complex     | FastSim in control       | CustomART.h                   |
               |   rindex layers)        | (boundary not run)       | CustomG4OpBoundaryProcess     |
               |                         |                          |                               |
               |                         |                          |                               |
               |                         |                          |                               |
               |                         | OpticalSurfaceName       |  OpticalSurfaceName           |
               |                         | without special prefix   |  starting '@'                 |
               |                         |                          |                               |
               |                         |                          |                               |
               |                         |                          |                               |
               |                         |                          |                               |
               +-------------------------+--------------------------+-------------------------------+

TODO
------

* add high level and low level NaturalPMT switches 
* NNVT + HAMA : obey switches : considering all 4 POM*PMT cases::

    jcv HamamatsuR12860PMTManager
    jcv NNVTMCPPMTManager    
    # what more than OpticalSurfaceName controlling customization + simpler geometry ?
  
* review code in the light of all 4 POM*PMT cases 
* devise some tests within monolith
* update standalone tests to use the added monolith code



Incorporation Commits
-------------------------


::

    epsilon:junosw blyth$ git --no-pager l -n 5
    commit 318ad8a3bd5b4b0e8593e51943a9fd13ffe88664 (HEAD -> blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess, origin/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess)
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Feb 23 20:09:32 2023 +0000

        incorporate CustomART.h MultiLayrStack.h customization into CustomG4OpBoundaryProcess

    M	Simulation/DetSimV2/PhysiSim/CMakeLists.txt
    A	Simulation/DetSimV2/PhysiSim/include/CustomART.h
    M	Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
    A	Simulation/DetSimV2/PhysiSim/include/MultiLayrStack.h
    M	Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc
    A	Simulation/DetSimV2/SimUtil/SimUtil/S4Touchable.h

    commit 2ab30fac7786f0a56b73af2c599a121b8161c4e5
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Thu Feb 23 10:14:51 2023 +0000

        fix without Opticks build fail with preprocessor macros in PMTAccessor::LoadPMTSimParamData, quell some compilation warnings

    M	Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_LPMT.h
    M	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PmtSimData_SPMT.h

    commit fce28c08bdb857e20f3735cae0eecc3a754db684
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Wed Feb 22 20:39:13 2023 +0000

        start integration of CustomG4OpBoundaryProcess using IPMTAccessor/PMTAccessor connector created from PMTSimParamData struct obtained from the PMTSimParamSvc

    M	Simulation/DetSimV2/PhysiSim/CMakeLists.txt
    M	Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
    M	Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
    M	Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc
    M	Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    A	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/IPMTAccessor.h
    A	Simulation/SimSvc/PMTSimParamSvc/PMTSimParamSvc/PMTAccessor.h

    commit e843201a22ba1f29500cf46cca5fa17430466063
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Wed Feb 22 17:01:43 2023 +0000

        change classname to CustomG4OpBoundaryProcess for clarity

    M	Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
    M	Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc

    commit 636e78a25b8ce07ee8e16cbafc97bcb41954d996
    Author: Simon C Blyth <simoncblyth@gmail.com>
    Date:   Wed Feb 22 16:58:04 2023 +0000

        bring in original Geant4 1042 G4OpBoundaryProcess under different name, ready for customization

    A	Simulation/DetSimV2/PhysiSim/include/CustomG4OpBoundaryProcess.hh
    A	Simulation/DetSimV2/PhysiSim/src/CustomG4OpBoundaryProcess.cc
    epsilon:junosw blyth$ 




Where should the incorporated code live within the monolith ?
----------------------------------------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/commits/blyth-88-pivot-PMT-optical-model-from-FastSim-to-CustomG4OpBoundaryProcess


As the stack calc is only needed from CustomG4OpBoundaryProcess
the calculation can live  ?

::

   junotop/junosw/Simulation/DetSimV2/PhysiSim/include/CustomART.h
   junotop/junosw/Simulation/DetSimV2/PhysiSim/include/Layr.h

   junotop/junosw/Simulation/DetSimV2/SimUtil/SimUtil/S4Touchable.h



MultiFilm POM
----------------

Q: In MultiFilm POM, what allows photons to refract into PMT ?

A0(Unnatural PMT): body-Pyrex is the FastSim region so the boundary process does not get to run, 
   so the opsurf has no chance to do anything. Instead FastSim ModelTrigger/DoIT runs 
   implementing refraction into the PMT.  

A1(Natural PMT): CustomG4OpticalBoundaryProcess/CustomART kicks in for OpticalSurfaceName[0] == '@' at local_z > 0 
   which calculates theTransmittance,theReflectivity,theEfficiency using the MultiFilm Layr calc with pmtid param 



How to switch between the Traditional POM and MultiFilm POM impl : Try control via OpticalSurfaceName prefix
---------------------------------------------------------------------------------------------------------------

* putting this switch into geometry is convenient 

::

     333 void HamamatsuR12860PMTManager::init_mirror_surface()
     334 {
     335     if(m_mirror_opsurf) return ;
     336 
     337     G4String name ;
     338     if(m_natural_geometry) name += ( m_enable_optical_model ? '@' : '#' ) ; // prefix controls CustomG4OpBoundaryProcess 
     339     name += GetName() ;
     340     name += "_Mirror_opsurf" ;


HMM : CustomG4OpBoundaryProcess/CustomART with traditional POM ?
------------------------------------------------------------------

Try generalization to handle both Traditional POM and MultiFilm POM::

            //[OpticalSurface.mpt.CustomBoundary
            char osn = OpticalSurfaceName[0] ; 
            if(  osn == '@' || osn == '#' )  // only customize specially named OpticalSurfaces 
            {
                if( m_custom_art->local_z(aTrack) < 0. ) // lower hemi : No customization, standard boundary  
                {
                    theCustomStatus = 'Z' ;
                }
                else if( osn == '@') //  upper hemi with name starting @ : MultiFilm ART transmit thru into PMT
                {
                    theCustomStatus = 'Y' ;
                    m_custom_art->doIt(aTrack, aStep) ;  // calculate theReflectivity theTransmittance theEfficiency 

                    type = dielectric_dielectric ;
                    theModel = glisur ;
                    theFinish = polished ;
                    // guide thru the below jungle : only when custom handling is triggered 
                }
                else if( osn == '#' ) // upper hemi with name starting # : Traditional Detection at photocathode
                {
                    theCustomStatus = '-' ;

                    type == dielectric_metal ;
                    theModel = glisur ;
                    theReflectivity = 0. ;
                    theTransmittance = 0. ;
                    theEfficiency = 1. ;
                }
            }
            else
            {
                theCustomStatus = 'X' ; 
            }



::

     717             //[OpticalSurface.mpt.CustomBoundary
     718 #ifdef WITH_PMTFASTSIM
     719             //theCustomStatus = m_custom_boundary->maybe_doIt( OpticalSurfaceName, aTrack, aStep );  
     720             theCustomStatus = m_custom_art->maybe_doIt( OpticalSurfaceName, aTrack, aStep );
     721             if(theCustomStatus == 'Y')
     722             {
     723                 type = dielectric_dielectric ;
     724                 theModel = glisur ;
     725                 theFinish = polished ;
     726                 // guide thru the below jungle : only when custom handling is triggered 
     727             }
     728 #else
     729             theCustomStatus = 'X' ;
     730 #endif
     731             //]OpticalSurface.mpt.CustomBoundary
     ...
     812     //[type_switch 
     813 #ifdef WITH_PMTFASTSIM
     814     if( theCustomStatus == 'Y' )
     815     {
     816         G4double rand = G4UniformRand();
     817 
     818         G4double A = 1. - (theReflectivity + theTransmittance) ;
     819 
     820         if ( rand < A )  // HMM: more normally rand > theReflectivity + theTransmittance 
     821         {
     822             DoAbsorption();   // theStatus is set to Detection/Absorption depending on a random and theEfficiency  
     823         }
     824         else
     825         {
     826             DielectricDielectric();
     827         }
     828     }
     829     else
     830 #endif
     831     if (type == dielectric_metal)
     832     {
     833         //[type_switch.dime
     834         DielectricMetal();
     835         //]type_switch.dime
     836     }





Traditional POM
------------------

Q: In traditional POM, what stops photons that are not detected at Photocathode from entering PMT ?

A0(Unnatural PMT): HamamatsuR12860PMTManager::Photocathode_opsurf NNVTMCPPMTManager::Photocathode_opsurf
   between body-Pyrex and inner1-Vacuum is dielectric_metal opsurface with  EFFICIENCY 1. REFLECTIVITY 0. 

   * that always DoAbsorption/theStatus=Detection 
   * so there is no reflection or refraction between body-Pyrex and inner1-Vacuum 
   * every photon gets "Detection" so ProcessHits will get called 

A1(Natural PMT):

   * HMM: COULD ENCODE THE TRADITIONAL SWITCH WITH : OpticalSurfaceName[0] == '#' 
   * HMM: CustomG4OpticalBoundaryProcess/CustomART needs a "traditional" switch that sets:
     dielectric_metal,theTransmittance:0.,theReflectivity:0.,theEfficiency:1.



Old Surface POM::

      +---------------pmt-Pyrex----------------+
      | +-------------body-Pyrex-------------+ |
      | |                                    | |
      | |                                    | |
      | |     +------------------------+     | |
      | |     |                        |     | |
      | |     |                        |     | |
      | |     |        inner1-Vacuum   |     |-|
      | |     |                        |     |1e-3
      | |     |                        |     | |
      | |     +~~coincident~face~~~~~~~+     | |
      | |     |                        |     | |
      | |     |                        |     | |
      | |     |        inner2-Vacuum   |     | |
      | |     |                        |     | |
      | |     |                        |     | |
      | |     +------------------------+     | |
      | |                                    | |
      | |                                    | |
      | +------------------------------------+ |
      +----------------------------------------+



G4OpBoundaryProcess::DielectricMetal with REFLECTIVITY 0. TRANSMITTANCE 0. (default) ALWAYS DoAbsorption
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* DielectricMetal with REFLECTIVITY 0. always Detection/Absorption 
* Further with EFFICIENCY 1. always Detection

::

    1061 void InstrumentedG4OpBoundaryProcess::DielectricMetal()
    1062 {
    1067     G4int n = 0;
    1068     G4double rand, PdotN, EdotN;
    1069     G4ThreeVector A_trans, A_paral;
    1070 
    1071     do
    1072     {
    1073         n++;
    1074 
    1075         rand = G4UniformRand();
    1076 
    1090         if ( rand > theReflectivity && n == 1 )   // ALWAYS rand > theReflectivity:0.
    1091         {
    1092             if (rand > theReflectivity + theTransmittance)  // ALWAYS rand > theReflectivity:0. + theTransmittance:0. (default)  
    1093             {
    1094                 DoAbsorption();
    1095             }
    1096             else
    1097             {
    1098                 theStatus = Transmission;
    1099                 NewMomentum = OldMomentum;
    1100                 NewPolarization = OldPolarization;
    1101             }
    1102             LOG(LEVEL) << " rand > theReflectivity && n == 1  break " ;
    1103             break;
    1104         }


    1953 void InstrumentedG4OpBoundaryProcess::DoAbsorption()
    1954 {
    1955     LOG(LEVEL)
    1956         << " PostStepDoIt_count " << PostStepDoIt_count
    1957         << " theEfficiency " << theEfficiency
    1958         ;
    1959 
    1960     bool detect = G4BooleanRand_theEfficiency(theEfficiency) ;
    1961     theStatus = detect ? Detection : Absorption ;
    1962 
    1963     NewMomentum = OldMomentum;
    1964     NewPolarization = OldPolarization;
    1965 
    1966     aParticleChange.ProposeLocalEnergyDeposit(detect ? thePhotonMomentum : 0.0);
    1967     aParticleChange.ProposeTrackStatus(fStopAndKill);
    1968 }




Photocathode_Opsurf
~~~~~~~~~~~~~~~~~~~~~~

::

     197 void
     198 HamamatsuR12860PMTManager::init_material() {
     199 
     200      GlassMat = G4Material::GetMaterial("Pyrex");
     201      PMT_Vacuum = G4Material::GetMaterial("Vacuum");
     202      DynodeMat = G4Material::GetMaterial("Steel");
     203 
     204      Photocathode_opsurf =  new G4OpticalSurface(GetName()+"_Photocathode_opsurf");
     205      Photocathode_opsurf->SetType(dielectric_metal); // ignored if RINDEX defined
     206      //Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode")->GetMaterialPropertiesTable() );
     207 
     208 #ifdef PMTSIM_STANDALONE
     209      G4Material* mat = G4Material::GetMaterial("photocathode_Ham20inch");
     210      Photocathode_opsurf->SetMaterialPropertiesTable(mat ? mat->GetMaterialPropertiesTable() : nullptr ) ;
     211 #else
     212      Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_Ham20inch")->GetMaterialPropertiesTable() );
     213 #endif
     214      if (m_fast_cover) {
     215          m_cover_mat = G4Material::GetMaterial(m_cover_mat_str);
     216          assert(m_cover_mat);
     217      }
     218 }

::

    190 void NNVTMCPPMTManager::init_material()
    191 {
    192      GlassMat = G4Material::GetMaterial("Pyrex");
    193      PMT_Vacuum = G4Material::GetMaterial("Vacuum");
    194      DynodeMat = G4Material::GetMaterial("Steel");
    195 
    196      Photocathode_opsurf =  new G4OpticalSurface(GetName()+"_Photocathode_opsurf");
    197      Photocathode_opsurf->SetType(dielectric_metal); // ignored if RINDEX defined
    198      //Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode")->GetMaterialPropertiesTable() );
    199      Photocathode_opsurf->SetMaterialPropertiesTable(G4Material::GetMaterial("photocathode_MCP20inch")->GetMaterialPropertiesTable() );
    200 
    201      if (m_fast_cover) {
    202          m_cover_mat = G4Material::GetMaterial(m_cover_mat_str);
    203          assert(m_cover_mat);
    204      }
    205 }


::

    epsilon:DetSim blyth$ cd $JUNOTOP/data
    epsilon:data blyth$ find . -name photocathode_*
    ./Simulation/DetSim/Material/photocathode_Ham20inch
    ./Simulation/DetSim/Material/photocathode_HZC9inch
    ./Simulation/DetSim/Material/photocathode_MCP8inch
    ./Simulation/DetSim/Material/photocathode_3inch
    ./Simulation/DetSim/Material/photocathode_Ham8inch
    ./Simulation/DetSim/Material/photocathode_MCP20inch
    epsilon:data blyth$ 




EFFICIENCY 1. REFLECTIVITY 0::

    epsilon:photocathode_MCP20inch blyth$ l
    total 48
    0 drwxr-xr-x   8 blyth  staff   256 Oct 27 17:55 .
    0 drwxr-xr-x  35 blyth  staff  1120 Oct 27 17:55 ..
    8 -rw-r--r--   1 blyth  staff    90 Oct 27 17:55 EFFICIENCY_v2
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 KINDEX
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 REFLECTIVITY
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 RINDEX
    8 -rw-r--r--   1 blyth  staff   106 Oct 27 17:55 THICKNESS
    8 -rw-r--r--   1 blyth  staff   214 Oct 27 17:55 scale
    epsilon:photocathode_MCP20inch blyth$ 
    epsilon:photocathode_MCP20inch blyth$ 
    epsilon:photocathode_MCP20inch blyth$ cat EFFICIENCY_v2 
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    epsilon:photocathode_MCP20inch blyth$ cat KINDEX 
    3.26274             *eV   1.69                
    4.13                *eV   2                   
    4.96                *eV   1.79                
    15.5                *eV   1.79                
    epsilon:photocathode_MCP20inch blyth$ cat RINDEX 
    3.26274             *eV   1.92                
    4.13                *eV   1.49                
    4.96                *eV   0.564               
    15.5                *eV   0.88                
    epsilon:photocathode_MCP20inch blyth$ cat scale
    # This file is used for scale some variables quickly
    #   XXXBefore 1
    #   XXXAfter  1.5
    # so we could calculate the ratio is 1.5/1

    qe_before              0.273
    qe_after               0.8
    pmt_qe_scale_for_elec  1.0
    epsilon:photocathode_MCP20inch blyth$ cat THICKNESS
    0                   *m    2.6e-08             *m    
    0.375               *m    2.6e-08             *m    
    epsilon:photocathode_MCP20inch blyth$ 
    epsilon:photocathode_MCP20inch blyth$ 
    epsilon:photocathode_MCP20inch blyth$ cat REFLECTIVITY 
    1.55                *eV   0                   
    6.2                 *eV   0                   
    10.33               *eV   0                   
    15.5                *eV   0                   
    epsilon:photocathode_MCP20inch blyth$ 



    epsilon:photocathode_Ham20inch blyth$ l
    total 48
    0 drwxr-xr-x   8 blyth  staff   256 Oct 27 17:55 .
    0 drwxr-xr-x  35 blyth  staff  1120 Oct 27 17:55 ..
    8 -rw-r--r--   1 blyth  staff    90 Oct 27 17:55 EFFICIENCY_v2
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 KINDEX
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 REFLECTIVITY
    8 -rw-r--r--   1 blyth  staff   188 Oct 27 17:55 RINDEX
    8 -rw-r--r--   1 blyth  staff   106 Oct 27 17:55 THICKNESS
    8 -rw-r--r--   1 blyth  staff   236 Oct 27 17:55 scale
    epsilon:photocathode_Ham20inch blyth$ cat EFFICIENCY_v2 
    1.55                *eV   1.0               
    15.5                *eV   1.0               
    epsilon:photocathode_Ham20inch blyth$ cat REFLECTIVITY 
    1.55                *eV   0                   
    6.2                 *eV   0                   
    10.33               *eV   0                   
    15.5                *eV   0                   
    epsilon:photocathode_Ham20inch blyth$ 




Without Opticks Fails : FIXED
---------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/jobs/19094/raw


CustomG4OpBoundaryProcess
----------------------------

* what about old non-MultiFilm PMT optical model ? How to organize the switch ?

  * must use same natural geometry 
  * review the PMT code to help with this  

* incorporate selection of changes from u4/InstrumentedCustomG4OpBoundaryProcess
* theRecoveredNormal 
* CustomART instanciation    
* decide where to keep CustomART.h Layr.h ? 
* consider rename Layr.h ? MultiFilmLayr.h


review existing POM switch
-----------------------------

::

    epsilon:junosw blyth$ jcv JUNODetSimModule
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py


The below should be changed to ls_optical_model::

    0408         # add new optical model
     409 
     410         grp_pmt_op.add_argument("--new-optical-model", dest="new_optical_model", action="store_true",
     411                       help=mh("Use the new optical model."))
     412         grp_pmt_op.add_argument("--old-optical-model", dest="new_optical_model", action="store_false",
     413                       help=mh("Use the old optical model"))
     414         grp_pmt_op.set_defaults(new_optical_model=False)
     415 


To avoid confusion with pmt-optical-model::

     474         # == use new pmt optical model or not ==
     475         grp_pmt_op.add_argument("--pmt-optical-model", dest="pmt_optical_model", action="store_true", help=mh("Enable New PMT optical model (default is enabled)"))
     476         grp_pmt_op.add_argument("--no-pmt-optical-model", dest="pmt_optical_model", action="store_false", help=mh("Disable New PMT optical model"))
     477         grp_pmt_op.set_defaults(pmt_optical_model=True)
     478 


::

    1681         if args.pmt_optical_model:
    1682             detsimfactory.property("UsePMTOpticalModel").set("new")
    1683         else:
    1684             detsimfactory.property("UsePMTOpticalModel").set("old")


Impl of existing POM switch
------------------------------


::                   
                     
    epsilon:junosw b-lyth$ jgr UsePMTOpticalModel
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=false); // just the fast simulation

    ## m_doFastSim 

    239     G4VProcess* boundproc_ = nullptr ;
    240     G4FastSimulationManagerProcess* fast_sim_man = 0;
    241 
    242     if(m_doFastSim)  // using m_doFastSim to configure use of the old impl 
    243     {
    244         G4OpBoundaryProcess* boundproc = new G4OpBoundaryProcess();
    245         boundproc->SetInvokeSD(false);
    246         boundproc_ = boundproc ;
    247 
    248         fast_sim_man = new G4FastSimulationManagerProcess("fast_sim_man");
    249     }
    250     else
    251     {
    252         CustomG4OpBoundaryProcess* boundproc = CreateCustomG4OpBoundaryProcess();
    253         boundproc->SetInvokeSD(false);
    254         boundproc_ = boundproc ;
    255     }
    256 



    ./Simulation/DetSimV2/G4DAEChroma/src/phys/DAEDsPhysConsOptical.cc:    declProp("UsePMTOpticalModel", m_doFastSim=true); // just the fast simulation
    ## junk code to be removed

    ./Simulation/DetSimV2/PMTSim/src/HamamatsuR12860PMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);
    ./Simulation/DetSimV2/PMTSim/src/NNVTMCPPMTManager.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);

    BOTH PMT IMPLEMENTED SIMILARLY 

    0308 void HamamatsuR12860PMTManager::init_pmt()
     309 {
     310   helper_make_solid();
     311   helper_make_logical_volume();
     312   helper_make_physical_volume();
     313 
     314   if(m_enable_optical_model || m_plus_dynode)
     315   {
     316       helper_make_dynode_volume();
     317   }
     318 
     319   helper_make_optical_surface();
     320 
     321   if(m_enable_optical_model)
     322   {
     323       helper_fast_sim();
     324   }
     325  
     326   helper_vis_attr();
     327 }

    SOME GEOMETRY DEPENDENCE

    312 void NNVTMCPPMTManager::helper_make_solid()
    313 {
    314     double pmt_delta = 1E-3*mm ;
    315     double inner_delta = -5*mm ;
    316 
    317     double body_delta = m_enable_optical_model == false ? 0. : inner_delta+1E-3*mm ;
    318     // TODO: find out why body_delta depends on m_enable_optical_model and add comment about that 
    319 

helper_fast_sim instanciates junoPMTOpticalModel and hooks up fast sim and svc to it.
All that needs to be switched off in new impl::

    0975 void
     976 HamamatsuR12860PMTManager::helper_fast_sim()
     977 {
     978 #ifdef PMTSIM_STANDALONE
     979 #else
     980     G4Region* body_region = new G4Region(this->GetName()+"_body_region");
     981     body_log->SetRegion(body_region);
     982     body_region->AddRootLogicalVolume(body_log);
     983     
     984     junoPMTOpticalModel *pmtOpticalModel = new junoPMTOpticalModel(GetName()+"_optical_model",
     985                                                                    body_phys, body_region);
     986     
     987     m_pmt_param_svc = 0;
     988     LogInfo << "Retrieving PMTParamSvc." << std::endl;
     989     SniperPtr<IPMTParamSvc> parsvc(*getParent(), "PMTParamSvc");
     990     if(parsvc.invalid()){
     991         LogError << "Can't get PMTParamSvc. We can't initialize PMT." << std::endl;
     992         assert(0);
     993         exit(EXIT_FAILURE);
     994     }else{
     995         LogInfo << "Retrieve PMTParamSvc successfully." << std::endl;
     996         m_pmt_param_svc = parsvc.data();
     997     }
     998     pmtOpticalModel->setPMTParamSvc(m_pmt_param_svc);
     999     
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
    1012     
    1013     // We don't support the original PMT optical model in this new class.
    1014     // new dywPMTOpticalModel( GetName()+"_optical_model", 
    1015     //        body_phys, body_region);
    1016 
    1017 #endif
    1018 
    1019 }




    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("UsePMTOpticalModel", m_enable_optical_model=false);

    147         if(m_enable_optical_model){
    148             LogInfo << "junoSD_PMT_v2::The new PMT optical model is enabled now." << std::endl;
    149             sd->enableOpticalModel();
    150         }

    jcv junoSD_PMT_v2
    85         void enableOpticalModel() { m_enable_optical_model = true; }


    0335 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     336 {

     389     if (!m_enable_optical_model) {
     390        G4OpBoundaryProcessStatus theStatus = Undefined;
     391        theStatus = boundary_proc->GetStatus();
     392 
     393        if (theStatus != Detection) {
     394            return false;
     395        }
     396     }

     In old model non-Detection photons get st

     In old model getting past the above means theStatus is Detection otherwise not treated as a hit. 
     HMM: MAYBE in new impl suspect will need to remove that  ?


     


    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:    declProp("UsePMTOpticalModel", m_pmt_optical_model = "old");

    087  //   declProp("GdLSAbsLengthMode", m_GdLSAbsLengthMode="old");
     88     declProp("UsePMTOpticalModel", m_pmt_optical_model = "old");
     89     declProp("UseLSOpticalModel", m_LS_optical_model = "old");
     90 
     91     declProp("CDInnerReflectorEnabled", m_isCDInnerReflectorEnabled = true);
     92 
     93     declProp("UsePmtSimSvc",m_use_pmtsimsvc=true);


    175 G4VUserDetectorConstruction*
    176 DetSim0Svc::createDetectorConstruction()
    177 {
    178     LSExpDetectorConstruction* dc = new LSExpDetectorConstruction;
    ...
    231     //dc->setGdLSAbsLengthMode(m_GdLSAbsLengthMode);
    232     dc->setPMTOpticalModel(m_pmt_optical_model);
    233     dc->setLSOpticalModel(m_LS_optical_model);
    234 
    235     dc->setCDInnerReflector(m_isCDInnerReflectorEnabled);
    236 

jcv LSExpDetectorConstruction::

    396   private:
    397   //  std::string m_GdLSAbsLengthMode;
    398     std::string m_pmt_optical_model;
    399     std::string m_LS_optical_model;
    400   public:
    401     // void setGdLSAbsLengthMode(std::string GdLSAbsLengthMode) {m_GdLSAbsLengthMode = GdLSAbsLengthMode ;}
    402      void setPMTOpticalModel(std::string mode ){ m_pmt_optical_model = mode;}
    403      void setLSOpticalModel(std::string mode ){m_LS_optical_model = mode ;}
    404 
         
    0170 //  m_GdLSAbsLengthMode = "old";
     171   m_pmt_optical_model = "old";
     172   m_LS_optical_model = "old";
     173   m_use_pmtsimsvc = true;

    HUH ALL THAT AND IT SEEMS ITS NOT USED ?







    ./Simulation/DetSimV2/DetSimOptions/python/DetSimOptions/ConfAcrylic.py:        #op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_any.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype.py:    op.property("UsePMTOpticalModel").set(False)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:            pmtmgr.property("UsePMTOpticalModel").set(True)
    ./Simulation/DetSimV2/DetSimOptions/share/examples/prototype/pyjob_prototype_onepmt.py:    op.property("UsePMTOpticalModel").set(False)


    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("UsePMTOpticalModel").set("new")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            detsimfactory.property("UsePMTOpticalModel").set("old")
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            nnvt_mcp_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            hamamatsu_pmt.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            pmtsdmgr.property("UsePMTOpticalModel").set(args.pmt_optical_model)
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            op_process.property("UsePMTOpticalModel").set(True)
    epsilon:junosw blyth$ 




