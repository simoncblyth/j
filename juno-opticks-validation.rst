juno-opticks-validation
=========================


build tips
--------------


::

    export CMTEXTRATAGS=opticks      ## bash junoenv sets this, but its not a standard pkg 



    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/G4Opticks/cmt       ## G4OpticksAnaMgr that passes G4 objects to CManager

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PhysiSim/cmt        ## added trackInfo to S + C 

    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/DetSimV2/PMTSim/cmt          ## logging 


    CMTEXTRATAGS=opticks jok-touchbuild- Simulation/GenTools/cmt



    jok-touchbuild- Simulation/DetSimV2/AnalysisCode/cmt           ## this was for dynamic_cast of TrackInfo in the InteresingAnaMgr before switched that off 

    jok-touchbuild- Examples/Tutorial/cmt    ## to install the python machinery 




::

    O
    jre
    jok-g4o


    O[blyth@localhost cmt]$ ls -l /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks*
    lrwxrwxrwx. 1 blyth blyth 67 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so -> ../../../Simulation/DetSimV2/G4Opticks/Linux-x86_64/libG4Opticks.so
    -rw-rw-r--. 1 blyth blyth 87 May 21 21:20 /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Opticks.so.cmtref
    O[blyth@localhost cmt]$ date
    Fri May 21 21:23:38 CST 2021




logging makes be unconvinced that SetTrackSecondariesFirst(true) 
--------------------------------------------------------------------

* code look shows that is is set by is specifically excluded at doing 
  anything with reemission : precisely when I need it 

::

    139 
    140     if (m_useScintillation && 1) { // DsG4 (with re-emission)
    141         DsG4Scintillation* scint = new DsG4Scintillation(m_opticksMode);
    142 
    143         scint->SetDoQuenching(m_enableQuenching);
    144         scint->SetBirksConstant1(m_birksConstant1);
    145         scint->SetBirksConstant2(m_birksConstant2);
    146         scint->SetGammaSlowerTimeConstant(m_gammaSlowerTime);
    147         scint->SetGammaSlowerRatio(m_gammaSlowerRatio);
    148         scint->SetNeutronSlowerTimeConstant(m_neutronSlowerTime);
    149         scint->SetNeutronSlowerRatio(m_neutronSlowerRatio);
    150         scint->SetAlphaSlowerTimeConstant(m_alphaSlowerTime);
    151         scint->SetAlphaSlowerRatio(m_alphaSlowerRatio);
    152         scint->SetDoReemission(m_doReemission);
    153         scint->SetDoReemissionOnly(m_doReemissionOnly);
    154         scint->SetDoBothProcess(m_doScintAndCeren);
    155         scint->SetApplyPreQE(m_scintPhotonScaleWeight>1.);
    156         scint->SetPreQE(1./m_scintPhotonScaleWeight);
    157         scint->SetScintillationYieldFactor(m_ScintillationYieldFactor); //1.);
    158         scint->SetUseFastMu300nsTrick(m_useFastMu300nsTrick);
    159         scint->SetTrackSecondariesFirst(true);
               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    160         scint->SetFlagDecayTimeFast(flagDecayTimeFast);
    161         scint->SetFlagDecayTimeSlow(flagDecayTimeSlow);
    162         scint->SetVerboseLevel(0);
    163 


::

    g4-cls G4Scintillation

    156         void SetTrackSecondariesFirst(const G4bool state);
    157         // If set, the primary particle tracking is interrupted and any
    158         // produced scintillation photons are tracked next. When all 
    159         // have been tracked, the tracking of the primary resumes.
    160 
    161         G4bool GetTrackSecondariesFirst() const;
    162         // Returns the boolean flag for tracking secondaries first.
    163 

    296         ////////////////////////////////////////////////////////////////
    297 
    298         aParticleChange.SetNumberOfSecondaries(fNumPhotons);
    299 
    300         if (fTrackSecondariesFirst) {
    301            if (aTrack.GetTrackStatus() == fAlive )
    302                   aParticleChange.ProposeTrackStatus(fSuspend);
    303         }
    304 
    305         ////////////////////////////////////////////////////////////////





    jcv DsG4Scintillation

    360 inline
    361 void DsG4Scintillation::SetTrackSecondariesFirst(const G4bool state)
    362 {
    363     fTrackSecondariesFirst = state;
    364 }
    365 
    366 inline
    367 G4bool DsG4Scintillation::GetTrackSecondariesFirst() const
    368 {
    369         return fTrackSecondariesFirst;
    370 }



     197 G4VParticleChange*
     198 DsG4Scintillation::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
     199 
     ...
     470 
     471     aParticleChange.SetNumberOfSecondaries(NumTracks);
     472 
     473     if (fTrackSecondariesFirst) {
     474         if (!flagReemission)
     475             if (aTrack.GetTrackStatus() == fAlive )
     476                 aParticleChange.ProposeTrackStatus(fSuspend);
     477     }
     478 





running tips
--------------

::

     export CG4Ctx=INFO
     export DsG4Scintillation=INFO
     export LocalG4Cerenkov1042=INFO

     tds3




::

    opticks --input-photon-path 



thu may 27 2021 : JUNO-Opticks "gun" tracing with eye to adding "opticks_input_photon_source" standin for "gun"
------------------------------------------------------------------------------------------------------------------

* get path to input photon file by envvar for simplicity 

::

    jcv tut_detsim JUNOApplication JUNODetSimModule
    

* https://docs.python.org/3/library/argparse.html

::

    >>> # create the top-level parser
    >>> parser = argparse.ArgumentParser(prog='PROG')
    >>> parser.add_argument('--foo', action='store_true', help='foo help')
    >>> subparsers = parser.add_subparsers(help='sub-command help')
    >>>
    >>> # create the parser for the "a" command
    >>> parser_a = subparsers.add_parser('a', help='a help')
    >>> parser_a.add_argument('bar', type=int, help='bar help')
    >>>
    >>> # create the parser for the "b" command
    >>> parser_b = subparsers.add_parser('b', help='b help')
    >>> parser_b.add_argument('--baz', choices='XYZ', help='baz help')
    >>>
    >>> # parse some argument lists
    >>> parser.parse_args(['a', '12'])
    Namespace(bar=12, foo=False)
    >>> parser.parse_args(['--foo', 'b', '--baz', 'Z'])
    Namespace(baz='Z', foo=True)

 
::

     096         subparsers = parser.add_subparsers(help='Please select the generator mode',
      97                                            dest='gentool_mode')
      98         subparsers.required = True
      99         self.register_subparser_gun(subparsers, base_parser_positioner)
     100         self.register_subparser_photon(subparsers, base_parser_positioner)
     101         self.register_subparser_gendecay(subparsers, base_parser_positioner)


::

     619     def register_subparser_gun(self, subparsers, base_parser_positioner):
     620         parser_gun = subparsers.add_parser("gun", help="gun mode", parents=[base_parser_positioner])
     621         parser_gun.add_argument("--particles",default="gamma", nargs='+',
     622                                 help="Particles to do the simulation.")
     623         parser_gun.add_argument("--momentums",default=1.0, nargs='+',
     624                                 type=float, 
     625                                 help="Momentums(MeV) p1 p2 ....")
     626         parser_gun.add_argument("--momentums-mode", default="Fix",
     627                                     choices=["Fix", "Uniform", "Range", "Gaus"],
     628                                     help="different momentum modes")
     629         parser_gun.add_argument("--momentums-extra-params", nargs='+',
     630                                 type=float,
     631                                 help="Extra Momentums Parameters(MeV) p1 p2 .... when mode is different, meaning is different."
     632                                      " Uniform: [mom-param, mom+param];"
     633                                      " Range: [mom, param];"
     634                                      " Gaus: Gaus(mom, param);"
     635                                 )
     636         parser_gun.add_argument("--momentums-interp", default="Momentum",
     637                                     choices=["Momentum", "KineticEnergy", "TotalEnergy"],
     638                                     help="Interpret momentum.")
     639         parser_gun.add_argument("--positions",default=[(0,0,0)], nargs='+',
     640                                 type=float, action=MakeTVAction,
     641                                 help="Positions (mm) x1 y1 z1 x2 y2 z2 ....")
     642         parser_gun.add_argument("--times",default=None, nargs='+',
     643                                 type=float,
     644                                 help="Time (mm) t1 t2 ....")
     645         parser_gun.add_argument("--directions",default=None, nargs='+',
     646                                 type=float, action=MakeTVAction,
     647                                 help="If you don't set, the directions are randoms. "
     648                                      "Directions dx1 dy1 dz1 dx2 dy2 dz2 ....")

     649         parser_gun.add_argument("--opticks-input-photon-source-path", default=None,  
     650                                 help="overrides other gun options with input photons from .npy files" 
     651                                      " for Opticks debugging, requires compilation WITH_G4OPTICKS" )
     652     


::

     jgr momentums_extra_params

    epsilon:offline blyth$ jgr momentums_extra_params
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        if args.momentums_extra_params:
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:            gun.property("particleMomentumParams").set(args.momentums_extra_params)
    epsilon:offline blyth$ 



Maybe create an opticks gentool, rather than overriding the existing gun.

Cannot use existing generators as for alignment purposes 
needs to operate without consuming any randoms. 


::

    epsilon:offline blyth$ jgr GtGunGenTool
    ./Simulation/GenTools/doc/README.rst:GtGunGenTool
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/share/run_gentool.py:    gun = gt.createTool("GtGunGenTool/gun")
    ./Simulation/GenTools/src/GtGunGenTool.cc:#include "GtGunGenTool.h"
    ./Simulation/GenTools/src/GtGunGenTool.cc:DECLARE_TOOL(GtGunGenTool);
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::GtGunGenTool(const std::string& name)
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::~GtGunGenTool()
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::configure()
    ./Simulation/GenTools/src/GtGunGenTool.cc:GtGunGenTool::mutate(HepMC::GenEvent& event)
    ...
 

thu may 27 2021 : how to do JUNO-Opticks aligned running
-----------------------------------------------------------------


Previous aligned running was done in CFG4 in a fully controlled Geant4 
environment.  Doing it within JUNO Offline will require:

1. input photons : needs new development as need to work with JUNO-Offline 
   approach to generation  

   * how much of existing machinery cfg4/CInputPhotonSource is usable 
     in JUNO context ?  CInputPhotonSource < CSource < G4VPrimaryGenerator

   * investigate existing JUNO generators and see how to add
     a WITH_G4OPTICKS only generator based on CInputPhotonSoutce 

2. input random numbers : existing machinery CAlignEngine should 
   be directly usable as this is done at Geant4 level beneath the level 
   of the experiment  


thu may 27 2021 : the case for JUNO-Opticks aligned running 
-----------------------------------------------------------------


Initially I was planning to do statistical non-random-aligned comparisons first 
before reviving the random aligned but given the large differences 
I see in the histories I think the fastest way to resolve problems and debug the 
machinery maybe to start with the sledgehammer of random-aligned running.  

Random aligned running uses input photons so there is no consumption 
of random numbers to generate the photons and input random numbers. 
With random aligned running you need a “quiet" Geant4 environment in terms 
of the random numbers that Geant4 consumes.
You can configure Geant4 to use the sequence of random numbers that you give it.

Random aligned running is difficult to get working across many photons
because it means you need to understand every random number consumed by Geant4 
and have Opticks do the same.  While it is difficult to keep the simulations together 
for large numbers of photons due to edge case details of Geant4 doing complicated things it 
is not so difficult to do for a small number of photons : and those small numbers of photons 
can be exceedingly informative at finding discrepancies because you 
can make direct comparisons of every photon step unclouded by statistics.





thu may 27 2021 : brief description of current investigations 
----------------------------------------------------------------

Currently there are big differences, although as this stage the problems 
could be bugs in the bookkeeping machinery rather than the simulation. 

I use the convention of using +ve tags Opticks events and negated ones for Geant4 events 
In the below a (OK:1) and b (G4:-1) are two events being compared

Get into ipython and load two events (+1 and -1) using::

    ab.sh 1 —-nocompare   

        ## —nocompare currently as there are metadata bugs that need to be fixed
        ## before the comparison table will work 


For every step of the photon I record four bits (aka nibble) of history flag into 
a 64 bit unsigned long long called “seqhis” (there is also “seqmat” for materials)
So I record the history of up to 16 steps of the photon.   
Sorting these integers and counting how many there are of each gives 
a history table showing how many photons with each history.

The below table shows the hex of the seqhis and the fraction of that and the 
count with the label showing the step history in readable form

   SI : scintillation generation
   CK : cherenkov generation
   AB : bulk absorb 
   BT : boundary transmit 
   SD : surface detect  
   SA : surface absorb 
   SC : bulk scatter 
   RE : reemission    


In [1]: a.seqhis_ana.table[:20]
Out[1]: 
all_seqhis_ana
.                     cfo:-  1:g4live:source 
.                              11278         1.00 
0000               42        0.147        1653        [2 ] SI AB
0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
0004              452        0.037         422        [3 ] SI RE AB
0005              462        0.035         392        [3 ] SI SC AB
0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
0011               41        0.013         142        [2 ] CK AB
0012             4662        0.012         137        [4 ] SI SC SC AB
0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
0014             4cc2        0.012         130        [4 ] SI BT BT AB
0015             4552        0.011         124        [4 ] SI RE RE AB
0016             4652        0.011         121        [4 ] SI RE SC AB
0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
.                              11278         1.00 


### G4 in the below has much more AB that OK above : MAYBE RE-JOIN not working properly 
### G4 has one extra “BT” on the way to SD : that is the virtual PMT container that is 
### skipped from GPU geometry (perhaps will put that back to match this)

In [2]: b.seqhis_ana.table[:20]
Out[2]: 
all_seqhis_ana
.                     cfo:-  -1:g4live:source    
.                              11278         1.00 
0000               42        0.315        3555        [2 ] SI AB
0001              452        0.099        1122        [3 ] SI RE AB
0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
0003              462        0.043         480        [3 ] SI SC AB
0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
0006             4552        0.028         314        [4 ] SI RE RE AB
0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
0008               41        0.022         246        [2 ] CK AB
0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
0011             4662        0.013         150        [4 ] SI SC SC AB
0012             4652        0.013         146        [4 ] SI RE SC AB
0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
0015             4562        0.010         111        [4 ] SI SC RE AB
0016             4cc2        0.008          95        [4 ] SI BT BT AB
0017            45552        0.008          93        [5 ] SI RE RE RE AB
0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
.                              11278         1.00 

In [3]: 



As the G4 machinery (event B) has only been up and running for a day or so, 
I don’t believe what I am seeing yet. It needs debugging.

In particular reemission is quite complicated because there is a fundamental 
difference regarding how the simulation is done on GPU and CPU that has to be 
handled in order to do the bookkeeping in the same way.

In JUNO Offline Geant4 reemission is handled as a secondary track 
but in Opticks a fraction of the AB (bulk absorbed) gets RE (reemitted).
This means that for Geant4 events to be matched in the above way 
you have to join together the secondary reemission  photons with their parents
across multiple generations of reemission.
I call that REJOIN-ing. The machinery to do that is fragile,  
I am currently debugging this.

If the REJOIN-ing is done wrong then you join the wrong photons together and 
mess up the histories. That could well be happening. 

Note that the above is just the start of the table the full table 
has many more lines with all the possible histories of the photons.





metadata numPhotons double counting ?
-----------------------------------------

::



::

    epsilon:offline blyth$ opticks-f setNumPhotons
    ...
    ./cfg4/CManager.cc:            g4evt->setNumPhotons( numPhotons, resize ); 
    ...


    142 void CManager::EndOfEventAction(const G4Event*)
    143 {
    144     LOG(LEVEL);
    145 
    146     char ctrl = '-' ;
    147     plog::Severity level = info ;
    148     if(m_ok->isSave())
    149     {
    150         unsigned numPhotons = m_ctx->getNumTrackOptical() ;
    151         //   this doesnt account for reemission REJOIN, so it will be too high 
    152         
    153         OpticksEvent* g4evt = m_ok->getEvent(ctrl) ;
    154         
    155         if(g4evt)
    156         {   
    157             LOG(level) << " --save g4evt numPhotons " << numPhotons ;
    158             bool resize = false ; 
    159             g4evt->setNumPhotons( numPhotons, resize );
    160             
    161             m_ok->saveEvent(ctrl);
    162             m_ok->resetEvent(ctrl);
    163         }
    164     }
    165     else
    166     {   
    167         LOG(level) << " NOT saving as no --save " ;
    168     }
    169 }


wed may 26 2021 : with first try at REJOIN : but suspect non-sequential RE messing up REJOIN
-----------------------------------------------------------------------------------------------


* "SI AB" : G4 - OK : 3555 - 1653 = 1902
* "CK AB" : G4 - OK : 246 - 142 = 104

Because Opticks does RE as a fraction of AB... 
does that mean should adjust the absorption_distance. 
Surely not, as this has matched before. 

First check simpler things like dumping absorption distance etc..

* Also "CK AB" also lots less with OK.  
* Note that "CK AB" still has reemission prob 

::

    132     if (absorption_distance <= scattering_distance)
    133     {   
    134         if (absorption_distance <= s.distance_to_boundary)
    135         {   
    136             p.time += absorption_distance/speed ;   
    137             p.position += absorption_distance*p.direction;
    138             
    139             const float& reemission_prob = s.material1.w ;  
    140             float u_reemit = reemission_prob == 0.f ? 2.f : curand_uniform(&rng);  // avoid consumption at absorption when not scintillator
    141             
    142             if (u_reemit < reemission_prob)
    143             {   
    144                 // no materialIndex input to reemission_lookup as both scintillators share same CDF 
    145                 // non-scintillators have zero reemission_prob
    146                 p.wavelength = reemission_lookup(curand_uniform(&rng));
    147                 p.direction = uniform_sphere(&rng);
    148                 p.polarization = normalize(cross(uniform_sphere(&rng), p.direction));
    149                 p.flags.i.x = 0 ;   // no-boundary-yet for new direction
    150                 
    151                 s.flag = BULK_REEMIT ;
    152                 return CONTINUE;
    153             }   
    154             else
    155             {   
    156                 s.flag = BULK_ABSORB ;
    157                 return BREAK;
    158             }
    159         }
    160         //  otherwise sail to boundary  
    161     }
    162     else







Counts with RE in any slot fairly close::

    In [38]: np.where(are)[0].shape
    Out[38]: (3724,)

    In [39]: np.where(bre)[0].shape
    Out[39]: (3956,)




::

    epsilon:j blyth$ ab.sh 1 --nocompare

    In [4]: a.seqhis_ana.table[:20]   ##  
    Out[4]: 
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [5]: b.seqhis_ana.table[:20]    ## G4 lots more "SI AB" and "CK AB" 
    Out[5]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.315        3555        [2 ] SI AB
    0001              452        0.099        1122        [3 ] SI RE AB
    0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
    0003              462        0.043         480        [3 ] SI SC AB
    0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
    0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
    0006             4552        0.028         314        [4 ] SI RE RE AB
    0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
    0008               41        0.022         246        [2 ] CK AB
    0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
    0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
    0011             4662        0.013         150        [4 ] SI SC SC AB
    0012             4652        0.013         146        [4 ] SI RE SC AB
    0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
    0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
    0015             4562        0.010         111        [4 ] SI SC RE AB
    0016             4cc2        0.008          95        [4 ] SI BT BT AB
    0017            45552        0.008          93        [5 ] SI RE RE RE AB
    0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
    0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
    .                              11278         1.00 





wed may 26 2021 : review reemission and REJOIN-ing
------------------------------------------------------

::


    246 /**
    247 CRecorder::Record
    248 --------------------
    ...
    259 * see notes/issues/reemission_review.rst
    260 
    261 Rejoining happens on output side not in the crec CStp list.
    262 
    263 The rejoins of AB(actually RE) tracks with reborn secondaries 
    264 are done by writing two (or more) sequences of track steps  
    265 into the same record_id in the record buffer at the 
    266 appropriate non-zeroed slot.
    267 
    268 WAS a bit confused by this ...
    269  
    270 This assumes that the REJOINing track will
    271 be the one immediately after the original AB. 
    272 By virtue of the Cerenkov/Scintillation process setting:
    273 
    274      SetTrackSecondariesFirst(true)
    275   
    276 If not so, this will "join" unrelated tracks ?
    277 (Really? remember it has random access into record buffer
    278 using record_id)
    279 
    280 TODO: find how to check this is the case and assert on it
    281 
    289 **/





tue numPhotons metadata out of whack with evt ?
------------------------------------------------

::

    epsilon:ana blyth$ js.py /tmp/blyth/opticks/source/evt/g4live/natural/*/parameters.json --keys Tag,NumPhotons
    /tmp/blyth/opticks/source/evt/g4live/natural/-1/parameters.json
    Tag                  : -1
    NumPhotons           : 17384
    /tmp/blyth/opticks/source/evt/g4live/natural/-2/parameters.json
    Tag                  : -2
    NumPhotons           : 17815
    /tmp/blyth/opticks/source/evt/g4live/natural/0/parameters.json
    Tag                  : -
    NumPhotons           : -
    /tmp/blyth/opticks/source/evt/g4live/natural/1/parameters.json
    Tag                  : 1
    NumPhotons           : 11278
    /tmp/blyth/opticks/source/evt/g4live/natural/2/parameters.json
    Tag                  : 2
    NumPhotons           : 11632
    epsilon:ana blyth$ 


This might be explained by the REJOIN-ing not working yet, leading to the reemission
photons being added to the total for G4.  


::

    In [11]: 17384 - 11278
    Out[11]: 6106


Every RE in OK:1 may be leading a separate "photon" in G4:-1 

* need to count RE nibbles, not photons
* number of RE nibbles 5406 is in the ballpark 

* also the truncation will be different as when the photons are split 
  at each RE they will not be truncated as much in G4:-1 


::

    In [1]: a.seqhis_ana.seq_any_count_nibble("RE")
    Out[1]: 5406

    In [2]: a.seqhis_ana.seq_any_count_nibble("SI")
    Out[2]: 11015

    In [3]: a.seqhis_ana.seq_any_count_nibble("CK")
    Out[3]: 263

    In [4]: b.seqhis_ana.seq_any_count_nibble("RE")
    Out[4]: 0



The truth is *11278*::

    epsilon:ana blyth$ gs.sh 1 
    [2021-05-25 18:54:48,089] p84123 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/1/gs.npy shape (66, 6, 4) 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:102} INFO - check_pdgcode
          11 :         e- : 62 
          22 :      gamma : 4 
    [2021-05-25 18:54:48,090] p84123 {/Users/blyth/opticks/ana/gs.py:116} INFO - check_ranges
     tr     0.7426     3.5089 
     xr   -15.7261    77.3296 
     yr   -90.1411   401.1544 
     zr  -537.4855  -206.4406 

::

    ab.sh 1 --nocompare


    In [3]: a.seqhis_ana.table[:20]
    Out[3]: 
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [4]: b.seqhis_ana.table[:20]
    Out[4]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.494        5570        [2 ] SI AB                ##
    0001           7cccc2        0.131        1474        [6 ] SI BT BT BT BT SD
    0002              462        0.066         745        [3 ] SI SC AB             ##
    0003           8cccc2        0.056         635        [6 ] SI BT BT BT BT SA
    0004          7cccc62        0.056         635        [7 ] SI SC BT BT BT BT SD
    0005          8cccc62        0.026         288        [7 ] SI SC BT BT BT BT SA
    0006         7cccc662        0.022         247        [8 ] SI SC SC BT BT BT BT SD
    0007               41        0.022         246        [2 ] CK AB                ##  
    0008             4662        0.021         234        [4 ] SI SC SC AB          ##
    0009             4cc2        0.013         144        [4 ] SI BT BT AB           
    0010         8cccc662        0.009          97        [8 ] SI SC SC BT BT BT BT SA
    0011        7cccc6662        0.007          75        [9 ] SI SC SC SC BT BT BT BT SD
    0012            4cc62        0.006          71        [5 ] SI SC BT BT AB
    0013            46662        0.006          70        [5 ] SI SC SC SC AB
    0014          7ccccc2        0.006          68        [7 ] SI BT BT BT BT BT SD
    0015              4c2        0.005          62        [3 ] SI BT AB
    0016         7ccccc62        0.004          42        [8 ] SI SC BT BT BT BT BT SD
    0017          8ccccc2        0.004          42        [7 ] SI BT BT BT BT BT SA
    0018        8cccc6662        0.004          40        [9 ] SI SC SC SC BT BT BT BT SA
    0019             4c62        0.003          35        [4 ] SI SC BT AB
    .                              11278         1.00 




Observations:

1. lots less BULK_ABSORB in OK:1 cf G4:-1 

   * consistent with many of the extra G4 "AB" going on to be RE-emitted
     and appearing as extra photons with G4 

   * counts for G4 histories ending with AB are elevated compared to OK, again reemission   

2. no RE:reemission in G4:-1

3. extra BT in G4 vs OK (virtual hatbox?)
4. G4 small CK/SI mismatches genstep : MUST BE A BUG  



After first try at REJOIN::

  

    In [5]: b.seqhis_ana.table[:20]
    Out[5]: 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               42        0.315        3555        [2 ] SI AB
    0001              452        0.099        1122        [3 ] SI RE AB
    0002           7cccc2        0.085         953        [6 ] SI BT BT BT BT SD
    0003              462        0.043         480        [3 ] SI SC AB
    0004           8cccc2        0.037         422        [6 ] SI BT BT BT BT SA
    0005          7cccc62        0.037         416        [7 ] SI SC BT BT BT BT SD
    0006             4552        0.028         314        [4 ] SI RE RE AB
    0007          7cccc52        0.026         291        [7 ] SI RE BT BT BT BT SD
    0008               41        0.022         246        [2 ] CK AB
    0009          8cccc62        0.016         180        [7 ] SI SC BT BT BT BT SA
    0010         7cccc662        0.014         159        [8 ] SI SC SC BT BT BT BT SD
    0011             4662        0.013         150        [4 ] SI SC SC AB
    0012             4652        0.013         146        [4 ] SI RE SC AB
    0013         7cccc652        0.011         124        [8 ] SI RE SC BT BT BT BT SD
    0014          8cccc52        0.010         113        [7 ] SI RE BT BT BT BT SA
    0015             4562        0.010         111        [4 ] SI SC RE AB
    0016             4cc2        0.008          95        [4 ] SI BT BT AB
    0017            45552        0.008          93        [5 ] SI RE RE RE AB
    0018         7cccc552        0.008          90        [8 ] SI RE RE BT BT BT BT SD
    0019         8cccc662        0.006          67        [8 ] SI SC SC BT BT BT BT SA
    .                              11278         1.00 


* now get RE
* but still more AB 
* TODO: check the REJOIN points, suspicion of non-sequential 


How to check are REJOIN-in the correct tracks  ?
----------------------------------------------------

::

    In [26]: als[:2]
    Out[26]: 
    SI BT BT BT SD
    SI RE AB

    In [27]: bls[:2]
    Out[27]: 
    SI AB
    SI SC SC BT BT BT BR BT BT SC

    In [28]: a.rpost_(slice(0,10))[0]
    Out[28]: 
    A([[    60.4266,    113.5289,   -419.3243,      5.6764],
       [-16342.6618,   6793.4202,    184.9422,     96.939 ],
       [-16454.3596,   6839.198 ,    188.6044,     97.5616],
       [-17860.6525,   7410.5045,    243.5377,    104.5198],
       [-17866.1458,   7414.1667,    243.5377,    104.5564],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ]])

    In [29]: b.rpost_(slice(0,10))[0]
    Out[29]: 
    A([[    60.4266,    113.5289,   -419.3243,      4.9074],
       [-11856.4409,   1254.3107,   -413.831 ,     66.213 ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ],
       [     0.    ,      0.    ,      0.    ,      0.    ]])




Find psel with RE in any slot::


    In [31]: a.seqhis_ana.seq_any("RE")
    Out[31]: array([False,  True, False, ..., False, False, False])

    In [32]: b.seqhis_ana.seq_any("RE")
    Out[32]: array([False, False, False, ...,  True, False, False])

    In [33]: are = a.seqhis_ana.seq_any("RE")

    In [34]: bre = b.seqhis_ana.seq_any("RE")

    In [35]: np.where(are)
    Out[35]: (array([    1,     4,     5, ..., 11262, 11263, 11266]),)

    In [36]: np.where(are)[0]
    Out[36]: array([    1,     4,     5, ..., 11262, 11263, 11266])

    In [37]: np.where(bre)[0]
    Out[37]: array([    3,     4,     6, ..., 11262, 11264, 11275])


Counts with RE in any slot fairly close::

    In [38]: np.where(are)[0].shape
    Out[38]: (3724,)

    In [39]: np.where(bre)[0].shape
    Out[39]: (3956,)

Find the histories of single photons::

    In [47]: afl = a.seqhis_ana.af.label

    In [48]: a.seqhis
    Out[48]: A([      511170,         1106,           66, ...,           66,           66, 871019341410], dtype=uint64)

    In [50]: afl(511170)
    Out[50]: 'SI BT BT BT SD'

    In [51]: a.seqhis[are]
    Out[51]: A([     1106,     19538,    288082, ...,      1106, 130860626,     17746], dtype=uint64)

    In [52]: afl(1106)
    Out[52]: 'SI RE AB'

    In [53]: afl(19538)
    Out[53]: 'SI RE BT AB'

    In [54]: afl(288082)
    Out[54]: 'SI RE RE SC AB'






RE
----

::

    In [11]: bre = b.seqhis_ana.seq_any("RE")

    In [12]: np.count_nonzero(bre)
    Out[12]: 0

    In [13]: are = a.seqhis_ana.seq_any("RE")

    In [14]: np.count_nonzero(are)
    Out[14]: 3724



small CK/SI mismatch : BUT should not happen, must be a bug  : G4:-1  -9:CK +9:SI 
-----------------------------------------------------------------------------------------------

* gensteps are in common so the counts of CK and SI much match 

::

    In [15]: ack = a.seqhis_ana.seq_any("CK")

    In [16]: np.count_nonzero(ack)
    Out[16]: 263

    In [1]: a.seqhis_ana.seq_any_count("CK")
    Out[1]: 263                                 ## CORRECT : MATCHES GS

    In [7]: a.seqhis_ana.seq_startswith_count("SI")
    Out[7]: 11015                               ## CORRECT : MATCHES GS



    epsilon:ana blyth$ gs.sh 1 
    [2021-05-25 20:31:30,264] p86263 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 20:31:30,265] p86263 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/1/gs.npy shape (66, 6, 4) 
    [2021-05-25 20:31:30,265] p86263 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 



    In [17]: bck = b.seqhis_ana.seq_any("CK")

    In [18]: np.count_nonzero(bck)
    Out[18]: 254                    ## <<<< G4:-1 : MISSING 9 CK PHOTONS 

    In [2]: b.seqhis_ana.seq_any_count("CK")
    Out[2]: 254


    In [8]: b.seqhis_ana.seq_startswith_count("SI")
    Out[8]: 11024                  ###   HUH :  +9 RELATIVE TO GS

    In [9]: b.seqhis_ana.seq_startswith_count("CK")
    Out[9]: 254                    ###    HUH : -9 RELATIVE TO GS   




    epsilon:ana blyth$ gs.sh -1 
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:137} INFO - Namespace(level='info', paths=['-1'], pathtmpl='$TMP/source/evt/g4live/natural/%d/gs.npy')
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:58} INFO -  path $TMP/source/evt/g4live/natural/-1/gs.npy shape (66, 6, 4) 
    [2021-05-25 20:32:08,824] p86437 {/Users/blyth/opticks/ana/gs.py:78} INFO - check_counts
    num_gensteps : 66 
    num_photons  : 11278 
     (4)DsG4Scintillation_r3971   : ngs:   58  npho:11015 
     (1)G4Cerenkov_1042           : ngs:    8  npho:  263 
     (0)TOTALS                    : ngs:   66  npho:11278 








    In [1]: a.seqhis_ana.seq_startswith_count("CK")
    Out[1]: 263

    In [2]: b.seqhis_ana.seq_startswith_count("CK")
    Out[2]: 254

    In [5]: a.seqhis_ana.seq_any_count("SI")
    Out[5]: 11015

    In [6]: 11015+263
    Out[6]: 11278

    In [7]: b.seqhis_ana.seq_startswith_count("SI")
    Out[7]: 11024



    In [8]: a.seqhis_ana.seq_startswith_count("SI")
    Out[8]: 11015

    In [9]: b.seqhis_ana.seq_startswith_count("CK")
    Out[9]: 254

    In [10]: 11024+254
    Out[10]: 11278





UserInfo clash : fixed with dynamic_cast
------------------------------------------

::

    epsilon:offline blyth$ jgr SetUserInformation
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:            aSecondaryTrack->SetUserInformation(new CTrackInfo( opticks_record_id, 'S' ) );
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc:      aSecondaryTrack->SetUserInformation(new CTrackInfo( opticks_record_id, 'C' ) );

    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/MuIsoProcessAnaMgr.cc:                (*secondaries)[i]->SetUserInformation(infoNew);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:        trk_michael->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/InteresingProcessAnaMgr.cc:            sectrk->SetUserInformation(info);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:        theTrack->SetUserInformation(anInfo);
    ./Simulation/DetSimV2/AnalysisCode/src/NormalAnaMgr.cc:                (*secondaries)[i]->SetUserInformation(infoNew);


::

    (gdb) bt
    #0  0x00007fffedd850ff in void __gnu_cxx::new_allocator<int>::construct<int, int const&>(int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #1  0x00007fffedd83ee8 in std::enable_if<std::allocator_traits<std::allocator<int> >::__construct_helper<int, int const&>::value, void>::type std::allocator_traits<std::allocator<int> >::_S_construct<int, int const&>(std::allocator<int>&, int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #2  0x00007fffedd82021 in decltype (_S_construct({parm#1}, {parm#2}, (forward<int const&>)({parm#3}))) std::allocator_traits<std::allocator<int> >::construct<int, int const&>(std::allocator<int>&, int*, int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #3  0x00007fffedd80c10 in std::vector<int, std::allocator<int> >::push_back(int const&) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libEDMUtil.so
    #4  0x00007fffc04ae1b8 in NormalTrackInfo::markTracedAncestors (this=0x17911ba30, trkid=10) at /home/blyth/junotop/offline/Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh:33
    #5  0x00007fffc04ad8f6 in InteresingProcessAnaMgr::saveSecondaryInit (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:537
    #6  0x00007fffc04ad4d8 in InteresingProcessAnaMgr::saveNeutronCapture (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:450
    #7  0x00007fffc04ab299 in InteresingProcessAnaMgr::PreUserTrackingAction (this=0x2ead490, aTrack=0x17911c770) at ../src/InteresingProcessAnaMgr.cc:162
    #8  0x00007fffc1c29598 in MgrOfAnaElem::PreUserTrackingAction (this=0x7fffc1e34440 <MgrOfAnaElem::instance()::s_mgr>, trk=0x17911c770) at ../src/MgrOfAnaElem.cc:60
    #9  0x00007fffc247222c in LSExpTrackingAction::PreUserTrackingAction (this=0x3386ed0, aTrack=0x17911c770) at ../src/LSExpTrackingAction.cc:37
    #10 0x00007fffd17a008e in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so
    #11 0x00007fffd19d7b53 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #12 0x00007fffc26be760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #13 0x00007fffc1c21a3c in DetSimAlg::execute (this=0x250de70) at ../src/DetSimAlg.cc:112


No dynamic_cast::

    521 void
    522 InteresingProcessAnaMgr::saveSecondaryInit(const G4Track* aTrack) {
    523     NormalTrackInfo* info = (NormalTrackInfo*)(aTrack->GetUserInformation());
    524     if ((not info)) {
    525         return;
    526     }




recollections
---------------

1. need to make G4 do secondaries first for re-emission REJOIN-ing to work
2. G4Track stopAndKill must be used to truncate the G4 simulation in the same way as Opticks bouncemax
3. reem "gensteps" are excluded:: 

     586         if((m_opticksMode & 1) && Num > 0 && !flagReemission)
     587         {
     588 #ifdef WITH_G4OPTICKS
     589             G4Opticks::Get()->collectGenstep_DsG4Scintillation_r3971(
     590                  &aTrack,



Avoided some Geant4 bug with::

    153 void Ctx::setTrackOptical(const G4Track* track)
    154 {
    155     const_cast<G4Track*>(track)->UseGivenVelocity(true);
    156 



G4 OpticksEvent missing gs.npy
----------------------------------

An organizational issue, as gensteps are by definition common to both simulations

::

    epsilon:ana blyth$ find /tmp/blyth/opticks/source/evt/g4live/natural -name gs.npy 
    /tmp/blyth/opticks/source/evt/g4live/natural/1/gs.npy
    /tmp/blyth/opticks/source/evt/g4live/natural/3/gs.npy
    /tmp/blyth/opticks/source/evt/g4live/natural/2/gs.npy
    epsilon:ana blyth$ 




bookending photon generation
---------------------------------

Bookending the photon generation corresponding to each genstep, will 
allow the CRecorder collected photons to be labelled with a genstep 
index so can then see the correspondence between the same single gensteps 
in each simulation without having to restrict running to a single genstep.
This also identifies the gentype. 

Hmm not directly. The geant4 photon generation loop creates secondary tracks 
and collects them into the G4VParticleChange that is returned by eg L4Cerenkov::PostStepDoIt
so in order to match need to plant info into these secondaries.


numPhotons mismatch : a total no-no : clearly a bug 
--------------------------------------------------------

* after adding CTrackInfo instrumentation gentype is now to be trusted
* maybe event mingling problem, are now not getting 1,2 written 


::

    epsilon:offline blyth$ evtbase.sh    ## rsync the events from P 
    from P:/home/blyth/local/opticks/evtbase/source/evt/g4live/natural to /tmp/blyth/opticks/source/evt/g4live/natural    


    epsilon:offline blyth$ evt.sh -1 2>/dev/null        ## seeing around 50% more in G4 
    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              15833         1.00 
    0000               42        0.497        7875        [2 ] SI AB
    0001           7cccc2        0.133        2099        [6 ] SI BT BT BT BT SD
    0002              462        0.066        1042        [3 ] SI SC AB
    0003          7cccc62        0.058         912        [7 ] SI SC BT BT BT BT SD
    0004           8cccc2        0.056         888        [6 ] SI BT BT BT BT SA
    0005          8cccc62        0.025         398        [7 ] SI SC BT BT BT BT SA
    0006         7cccc662        0.022         346        [8 ] SI SC SC BT BT BT BT SD
    0007             4662        0.020         320        [4 ] SI SC SC AB
    0008               41        0.016         248        [2 ] CK AB
    0009             4cc2        0.013         200        [4 ] SI BT BT AB
    0010         8cccc662        0.008         133        [8 ] SI SC SC BT BT BT BT SA
    0011        7cccc6662        0.008         120        [9 ] SI SC SC SC BT BT BT BT SD
    0012            46662        0.007         104        [5 ] SI SC SC SC AB
    0013          7ccccc2        0.006         100        [7 ] SI BT BT BT BT BT SD
    0014            4cc62        0.006          99        [5 ] SI SC BT BT AB
    0015              4c2        0.005          84        [3 ] SI BT AB
    0016         7ccccc62        0.004          60        [8 ] SI SC BT BT BT BT BT SD
    0017          8ccccc2        0.003          54        [7 ] SI BT BT BT BT BT SA
    0018        8cccc6662        0.003          52        [9 ] SI SC SC SC BT BT BT BT SA
    0019             4c62        0.003          48        [4 ] SI SC BT AB
    .                              15833         1.00 

    In [1]: epsilon:offline blyth$ evt.sh 1 2>/dev/null
    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 

    In [1]: 





running shakedown
--------------------


tds2 with "--opticks-anamgr" to feed G4OpticksRecorder with G4Run G4Event G4Track G4Step::

    O[blyth@localhost cmt]$ t tds2
    tds2 () 
    { 
        : run with opticks disabled, but with Opticks provided intrumentation used to save info from Geant4 in OpticksEvent format files;
        local opts="--opticks-mode 2 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 --opticks-anamgr";
        tds- $opts gun $*
    }


::

    epsilon:offline blyth$ svn commit -m "pass G4 objects from detsim/G4OpticksAnaMgr to opticks/g4ok/G4OpticksRecorder, so can develop in Opticks repo"
    Sending        Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.cc
    Sending        Simulation/DetSimV2/G4Opticks/src/G4OpticksAnaMgr.hh
    Transmitting file data ...done
    Committing transaction...
    Committed revision 4596.




Do not see output from G4OpticksAnaMgr although it is in the AnaMgrList, I recall getting this before

jnu/opticks-junoenv-runtime.rst


::

    BP=LSExpRunAction::BeginOfRunAction tds2


::

     30 void MgrOfAnaElem::BeginOfRunAction(const G4Run* run) {
     31     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     32     {
     33           val->BeginOfRunAction(run);
     34     }
     35 }
     36 void MgrOfAnaElem::EndOfRunAction(const G4Run* run){
     37     BOOST_FOREACH(EXEORD::value_type const& val, m_order)
     38     {
     39           val->EndOfRunAction(run);
     40     }
     41 


::

    (gdb) p m_order
    $2 = std::vector of length 10, capacity 16 = {0x250c090, 0x250d9f0, 0x2533030, 0x2aa76c0, 0x2ebc060, 0x300a890, 0x7fffbf507010, 0x2eabe00, 0x29bd680, 0x25337e0}
    (gdb) p m_anamgrs
    $3 = std::map with 10 elements = {["DataModelWriterWithSplit"] = 0x2533030, ["DepositEnergyAnaMgr"] = 0x300a890, ["DepositEnergyTTAnaMgr"] = 0x7fffbf507010, ["G4OpticksAnaMgr"] = 0x250c090, 
      ["GenEvtInfoAnaMgr"] = 0x2ebc060, ["InteresingProcessAnaMgr"] = 0x2eabe00, ["NormalAnaMgr"] = 0x2aa76c0, ["OpticalParameterAnaMgr"] = 0x29bd680, ["RadioAnaMgr"] = 0x250d9f0, 
      ["TimerAnaMgr"] = 0x25337e0}
    (gdb) 


Getting the output now, but not WITH_G4OPTICKS::

    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::UserSteppingAction 
    G4OpticksAnaMgr::PostUserTrackingAction 
    G4OpticksAnaMgr::PreUserTrackingAction 


::

    epsilon:~ blyth$ cat $JUNOTOP/ExternalInterface/Externals/OpticksG4OK/cmt/requirements
    package OpticksG4OK

    macro OpticksG4OK_home "" \
              opticks " \`opticks-config --prefix\` "

    macro OpticksG4OK_cppflags "" \
              opticks  " \`opticks-config --cflags G4OK\` -DWITH_G4OPTICKS "

    macro OpticksG4OK_linkopts "" \
              opticks " \`opticks-config --libs G4OK\` " 



Package dependency tree must include OpticksG4OK::

    epsilon:offline blyth$ jgr OpticksG4OK
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:use OpticksG4OK    v* Externals


    epsilon:offline blyth$ jgr DetSimPolicy
    ./Simulation/DetSimV2/SimUtil/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PhysiSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/G4DAEChroma/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CMakeLists.txt:#add_subdirectory(DetSimPolicy)
    ./Simulation/DetSimV2/G4Opticks/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/PMTSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimAlg/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/MCParamsSvc/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/GenSim/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/TopTracker/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CalibUnit/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/Chimney/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimOptions/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/CentralDetector/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    ./Simulation/DetSimV2/DetSimPolicy/cmt/requirements:package DetSimPolicy
    ./Simulation/DetSimV2/OPSimulator/cmt/requirements:use DetSimPolicy  v* Simulation/DetSimV2
    ./Simulation/DetSimV2/DAE/cmt/requirements:use DetSimPolicy v* Simulation/DetSimV2
    ./Simulation/DetSimV2/G4Svc/cmt/requirements:use DetSimPolicy    v*   Simulation/DetSimV2
    ./Simulation/DetSimV2/AnalysisCode/cmt/requirements:use DetSimPolicy    v*  Simulation/DetSimV2
    epsilon:offline blyth$ 


    O[blyth@localhost cmt]$ pwd
    /home/blyth/junotop/offline/Simulation/DetSimV2/G4Opticks/cmt
    O[blyth@localhost cmt]$ 

    O[blyth@localhost cmt]$ cmt show macro_value OpticksG4OK_cppflags
    O[blyth@localhost cmt]$ CMTEXTRATAGS=opticks cmt show macro_value OpticksG4OK_cppflags
     -DG4INTY_USE_XT -DG4VIS_USE_OPENGL -DG4UI_USE_TCSH -DG4VIS_USE_RAYTRACERX -DG4VIS_USE_OPENGLX -W -Wall -pedantic -Wno-non-virtual-dtor -Wno-long-long -Wwrite-strings -Wpointer-arith -Woverloaded-virtual -Wno-variadic-macros -Wshadow -pipe -DG4USE_STD11 -pthread -ftls-model=global-dynamic -std=c++11 -DG4MULTITHREADED -DOPTICKS_G4OK -DOPTICKS_CFG4 -DOPTICKS_X4 -DOPTICKS_OKOP -DOPTICKS_OKGEO -DOPTICKS_THRAP -DOPTICKS_GGEO -DOPTICKS_OKCORE -DOPTICKS_NPY -DOPTICKS_OKCONF -DOPTICKS_SYSRAP -DWITH_STTF -DWITH_PLOG -DOPTICKS_BRAP -DWITH_BOOST_ASIO -DOPTICKS_CUDARAP -DOPTICKS_OXRAP -I/home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/bin/../include/Geant4 -I/home/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/include -I/home/blyth/local/opticks/include/G4OK -I/home/blyth/local/opticks/include/CFG4 -I/home/blyth/local/opticks/include/ExtG4 -I/home/blyth/local/opticks/include/OKOP -I/home/blyth/local/opticks/include/OpticksGeo -I/home/blyth/local/opticks/include/ThrustRap -I/home/blyth/local/opticks/include/GGeo -I/home/blyth/local/opticks/include/OpticksCore -I/home/blyth/local/opticks/externals/include -I/home/blyth/local/opticks/include/NPY -I/home/blyth/local/opticks/include/OKConf -I/home/blyth/local/opticks/externals/glm/glm -I/home/blyth/local/opticks/include/SysRap -I/home/blyth/local/opticks/include/BoostRap -I/home/blyth/local/opticks/include/CUDARap -I/home/blyth/local/opticks/include/OptiXRap -I/home/blyth/junotop/ExternalLibs/Xercesc/3.2.2/include -I/home/blyth/local/opticks/externals/plog/include -I/home/blyth/local/opticks/externals/include/nljson -I/usr/local/cuda/include -I/home/blyth/local/opticks/externals/OptiX_650/include -std=c++11 -DWITH_G4OPTICKS 
    O[blyth@localhost cmt]$ 






tds3 : duplicate material
----------------------------

CMaterialBridge was assuming that all geant4 materials are in GMaterialLib.  That is no longer
the case, since have moved to carrying only materials that are used by geometry. This 
change from a few months ago was for consistency with GDML exports, and for running from 
GDML exports.


::

    tds3
    ...

    2021-05-24 20:00:38.481 INFO  [339226] [OGeo::convert@302] [ nmm 10
    2021-05-24 20:00:39.749 INFO  [339226] [OGeo::convert@321] ] nmm 10
    2021-05-24 20:00:39.813 ERROR [339226] [cuRANDWrapper::setItems@154] CAUTION : are resizing the launch sequence 
    python: /home/blyth/opticks/cfg4/CMaterialBridge.cc:88: void CMaterialBridge::initMap(): Assertion `m_ixtoname.size() == nmat && "there is probably a duplicated material name"' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6cfaa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6cf21a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffce68fd12 in CMaterialBridge::initMap (this=0x14bf072a0) at /home/blyth/opticks/cfg4/CMaterialBridge.cc:88
    #5  0x00007fffce68f650 in CMaterialBridge::CMaterialBridge (this=0x14bf072a0, mlib=0x155cb820) at /home/blyth/opticks/cfg4/CMaterialBridge.cc:41
    #6  0x00007fffcf2b710e in G4OpticksRecorder::setGeometry (this=0x2537030, ggeo_=0x155cb2b0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:61
    #7  0x00007fffcf2abe76 in G4Opticks::setGeometry (this=0x4e9e6f0, ggeo=0x155cb2b0) at /home/blyth/opticks/g4ok/G4Opticks.cc:674
    #8  0x00007fffcf2ab7f6 in G4Opticks::setGeometry (this=0x4e9e6f0, world=0x33fe7e0) at /home/blyth/opticks/g4ok/G4Opticks.cc:598
    #9  0x00007fffc23c3a5d in LSExpDetectorConstruction_Opticks::Setup (world=0x33fe7e0, sd_=0x35f73d0, opticksMode=3) at ../src/LSExpDetectorConstruction_Opticks.cc:105
    #10 0x00007fffc23b443e in LSExpDetectorConstruction::Construct (this=0x31f7e40) at ../src/LSExpDetectorConstruction.cc:387
    #11 0x00007fffcf505253 in G4RunManager::InitializeGeometry() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #12 0x00007fffcf504fda in G4RunManager::Initialize() () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4run.so
    #13 0x00007fffc1b79826 in DetSimAlg::initialize (this=0x25150b0) at ../src/DetSimAlg.cc:80
    #14 0x00007fffef12d5e0 in DleSupervisor::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #15 0x00007fffef13801e in Task::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #16 0x00007fffef141832 in TopTask::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #17 0x00007fffef13d26a in TaskWatchDog::initialize() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #18 0x00007fffef137f35 in Task::run() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so
    #19 0x00007fffef6c013e in _object* boost::python::detail::invoke<boost::python::to_python_value<bool const&>, bool (Task::*)(), boost::python::arg_from_python<Task&> >(boost::python::detail::invoke_tag_<false, true>, boost::python::to_python_value<bool const&> const&, bool (Task::*&)(), boost::python::arg_from_python<Task&>&) ()
       from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #20 0x00007fffef6beb32 in boost::python::detail::caller_arity<1u>::impl<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> >::operator()(_object*, _object*) ()
       from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #21 0x00007fffef6bde93 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperPython.so
    #22 0x00007fffef3773d1 in boost::python::objects::function::call(_object*, _object*) const () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #23 0x00007fffef377738 in boost::detail::function::void_function_ref_invoker0<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #24 0x00007fffef381023 in boost::python::handle_exception_impl(boost::function0<void>) () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #25 0x00007fffef376013 in function_call () from /home/blyth/junotop/ExternalLibs/Boost/1.72.0/lib/libboost_python27.so.1.72.0
    #26 0x00007ffff7a09c53 in PyObject_Call (func=func@entry=0x702260, arg=arg@entry=0x7fffee1942d0, kw=kw@entry=0x0) at Objects/abstract.c:2544
    #27 0x00007ffff7abfce6 in do_call (nk=<optimized out>, na=<optimized out>, pp_stack=0x7fffffff7180, func=<optimized out>) at Python/ceval.c:4593






bad flag : boundary_status not handled : NRI 
--------------------------------------------------------------------------

* how to avoid the annoying USE_CUSTOM_BOUNDARY compile time switch ???

OpStatus.cc::

     80 std::string OpStatus::OpBoundaryAbbrevString(const G4OpBoundaryProcessStatus status)
     81 {   
     ..
     99         case NoRINDEX:s="NRI";break;



::

    2021-05-24 21:20:32.756 INFO  [11533] [CRecorder::postTrackWriteSteps@422] [
    2021-05-24 21:20:32.756 INFO  [11533] [CRecorder::postTrackWriteSteps@430]  NOT USE_CUSTOM_BOUNDARY 
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 FATAL [11533] [OpStatus::OpPointFlag@365]  boundary flag zero  bst 14
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 0 processName Transportation
    2021-05-24 21:20:32.756 FATAL [11533] [CRecorder::postTrackWriteSteps@497]  num 4 i 3 postFlag zero  prior_boundary_status 2 boundary_status 14 next_boundary_status 0 postStage 2 premat 15 postmat 3
    2021-05-24 21:20:32.756 INFO  [11533] [OpStatus::OpPointFlag@386]  flag 2048 processName Transportation
    2021-05-24 21:20:32.756 WARN  [11533] [CRecorder::WriteStepPoint@670]  boundary_status not handled : NRI
    2021-05-24 21:20:32.756 FATAL [11533] [CPhoton::add@100]  _badflag 0
    python: /home/blyth/opticks/cfg4/CPhoton.cc:103: void CPhoton::add(unsigned int, unsigned int): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-2.el7.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-57.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-21.el7_6.x86_64 openssl-libs-1.0.2k-19.el7.x86_64 pcre-8.32-17.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007ffff6cf9387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff6cfaa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff6cf21a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6cf2252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffce761ad1 in CPhoton::add (this=0x14bf00668, flag=0, material=3) at /home/blyth/opticks/cfg4/CPhoton.cc:103
    #5  0x00007fffce7632d9 in CWriter::writeStepPoint (this=0x14bf007a0, point=0x179122d30, flag=0, material=3, last=false) at /home/blyth/opticks/cfg4/CWriter.cc:167
    #6  0x00007fffce75aa0a in CRecorder::WriteStepPoint (this=0x14bf00630, point=0x179122d30, flag=0, material=3, boundary_status=NoRINDEX, last=false) at /home/blyth/opticks/cfg4/CRecorder.cc:673
    #7  0x00007fffce75a346 in CRecorder::postTrackWriteSteps (this=0x14bf00630) at /home/blyth/opticks/cfg4/CRecorder.cc:594
    #8  0x00007fffce758900 in CRecorder::postTrack (this=0x14bf00630) at /home/blyth/opticks/cfg4/CRecorder.cc:193
    #9  0x00007fffce78154c in CManager::postTrack (this=0x14bf00830) at /home/blyth/opticks/cfg4/CManager.cc:207
    #10 0x00007fffce7814c0 in CManager::PostUserTrackingAction (this=0x14bf00830, track=0x179157620) at /home/blyth/opticks/cfg4/CManager.cc:189
    #11 0x00007fffcf3647c2 in G4OpticksRecorder::PostUserTrackingAction (this=0x250d6d0, track=0x179157620) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:104
    #12 0x00007fffc28c88de in G4OpticksAnaMgr::PostUserTrackingAction (this=0x250d780, trk=0x179157620) at ../src/G4OpticksAnaMgr.cc:34
    #13 0x00007fffc1c2d700 in MgrOfAnaElem::PostUserTrackingAction (this=0x7fffc1e38440 <MgrOfAnaElem::instance()::s_mgr>, trk=0x179157620) at ../src/MgrOfAnaElem.cc:67
    #14 0x00007fffc2476252 in LSExpTrackingAction::PostUserTrackingAction (this=0x3387090, aTrack=0x179157620) at ../src/LSExpTrackingAction.cc:48
    #15 0x00007fffd17a314d in G4TrackingManager::ProcessOneTrack(G4Track*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4tracking.so




Quite a few "not done"
-------------------------

::

    2021-05-24 22:19:55.120 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1549 photon CPhoton slot_constrained 4 seqhis                ecc61 seqmat                3fb11 is_flag_done N is_done N action POST_SAVE  i 4 num 4
    2021-05-24 22:19:55.120 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1550 photon CPhoton slot_constrained 3 seqhis                 ecc1 seqmat                 3fb1 is_flag_done N is_done N action POST_SAVE  i 3 num 3
    2021-05-24 22:19:55.121 FATAL [107794] [CRecorder::postTrackWriteSteps@625] postTrackWriteSteps  not-done 1551 photon CPhoton slot_constrained 3 seqhis                 ecc1 seqmat                 3fb1 is_flag_done N is_done N action POST_SAVE  i 3 num 3
    [[ junoSD_PMT_v2_Opticks::EndOfEvent  eventID 0 m_opticksMode 3 numGensteps 66 numPhotons 11278




CManager::EndOfEventAction assert OpticksEvent NULL
-------------------------------------------------------

Looks like the GPU event creation stomps on the g4evt that was created previously.

Rearranged OpticksRun to be more g4/ok symmetric and not do such stomping.




::

    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 5073 hitCollection_muon 0 hitCollection_opticks 0
    2021-05-24 21:49:12.372 INFO  [49312] [G4OpticksRecorder::EndOfEventAction@91] 
    2021-05-24 21:49:12.372 INFO  [49312] [CManager::EndOfEventAction@145] 
    2021-05-24 21:49:12.372 INFO  [49312] [CManager::EndOfEventAction@149]  --save 

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffca94e72e in OpticksEvent::setNumPhotons (this=0x0, num_photons=17384, resize_=false) at /home/blyth/opticks/optickscore/OpticksEvent.cc:295
    295	    m_num_photons = num_photons ; 
    (gdb) bt
    #0  0x00007fffca94e72e in OpticksEvent::setNumPhotons (this=0x0, num_photons=17384, resize_=false) at /home/blyth/opticks/optickscore/OpticksEvent.cc:295
    #1  0x00007fffce78114f in CManager::EndOfEventAction (this=0x14bf00830) at /home/blyth/opticks/cfg4/CManager.cc:154
    #2  0x00007fffcf3645e6 in G4OpticksRecorder::EndOfEventAction (this=0x250d6d0, event=0x17910ddd0) at /home/blyth/opticks/g4ok/G4OpticksRecorder.cc:92
    #3  0x00007fffc28c886e in G4OpticksAnaMgr::EndOfEventAction (this=0x250d780, evt=0x17910ddd0) at ../src/G4OpticksAnaMgr.cc:32
    #4  0x00007fffc1c2d430 in MgrOfAnaElem::EndOfEventAction (this=0x7fffc1e38440 <MgrOfAnaElem::instance()::s_mgr>, evt=0x17910ddd0) at ../src/MgrOfAnaElem.cc:53
    #5  0x00007fffc2470e00 in LSExpEventAction::EndOfEventAction (this=0x3385780, evt=0x17910ddd0) at ../src/LSExpEventAction.cc:76
    #6  0x00007fffd19db045 in G4EventManager::DoProcessing(G4Event*) () from /home/blyth/junotop/ExternalLibs/Geant4/10.04.p02/lib64/libG4event.so
    #7  0x00007fffc26c2760 in G4SvcRunManager::SimulateEvent(int) () from /home/blyth/junotop/offline/InstallArea/Linux-x86_64/lib/libG4Svc.so
    #8  0x00007fffc1c25a3c in DetSimAlg::execute (this=0x250dd20) at ../src/DetSimAlg.cc:112
    #9  0x00007fffef13836d in Task::execute() () from /home/blyth/junotop/sniper/InstallArea/Linux-x86_64/lib/libSniperKernel.so


evt.sh shape mismatch for "so" with g4evt -1
------------------------------------------------




::

    cd ~/opticks/ana
    ./evtbase.sh    # rsync from remote 

    ./ab.sh 
    ./evt.sh 
    ..

    [{tagdir_             :nload.py  :118} INFO     - tagdir_ det g4live typ natural tag -1 layout 2 DEFAULT_DIR_TEMPLATE $OPTICKS_EVENT_BASE/$0/evt/$1/$2/$3 
    [{load_               :nload.py  :276} INFO     -  path /tmp/blyth/opticks/source/evt/g4live/natural/-1/so.npy size 80 
    [{check_shapes        :evt.py    :408} INFO     - stems : ['ox', 'rx', 'ph', 'so', 'ps', 'rs'] 
    [{check_shapes        :evt.py    :414} INFO     - stem ox a.shape (11278, 4, 4) a.oshape (11278, 4, 4)  
    [{check_shapes        :evt.py    :414} INFO     - stem rx a.shape (11278, 10, 2, 4) a.oshape (11278, 10, 2, 4)  
    [{check_shapes        :evt.py    :414} INFO     - stem ph a.shape (11278, 1, 2) a.oshape (11278, 1, 2)  
    [{check_shapes        :evt.py    :414} INFO     - stem so a.shape (0, 4, 4) a.oshape (0, 4, 4)  
    [{check_shapes        :evt.py    :443} CRITICAL - oshape_mismatch : ['so']  file_photons 11278 
    ---------------------------------------------------------------------------
    AssertionError                            Traceback (most recent call last)



CK/SI seem off
-----------------


evt.sh 1::

    all_seqhis_ana
    .                     cfo:-  1:g4live:source 
    .                              11278         1.00 
    0000               42        0.147        1653        [2 ] SI AB
    0001            7ccc2        0.116        1307        [5 ] SI BT BT BT SD
    0002            8ccc2        0.052         592        [5 ] SI BT BT BT SA
    0003           7ccc62        0.052         591        [6 ] SI SC BT BT BT SD
    0004              452        0.037         422        [3 ] SI RE AB
    0005              462        0.035         392        [3 ] SI SC AB
    0006           7ccc52        0.034         385        [6 ] SI RE BT BT BT SD
    0007           8ccc62        0.022         249        [6 ] SI SC BT BT BT SA
    0008          7ccc662        0.019         219        [7 ] SI SC SC BT BT BT SD
    0009           8ccc52        0.015         169        [6 ] SI RE BT BT BT SA
    0010          7ccc652        0.013         147        [7 ] SI RE SC BT BT BT SD
    0011               41        0.013         142        [2 ] CK AB
    0012             4662        0.012         137        [4 ] SI SC SC AB
    0013            4cc62        0.012         130        [5 ] SI SC BT BT AB
    0014             4cc2        0.012         130        [4 ] SI BT BT AB
    0015             4552        0.011         124        [4 ] SI RE RE AB
    0016             4652        0.011         121        [4 ] SI RE SC AB
    0017           7cccc2        0.010         114        [6 ] SI BT BT BT BT SD
    0018           4cccc2        0.009         105        [6 ] SI BT BT BT BT AB
    0019          7ccc552        0.009          98        [7 ] SI RE RE BT BT BT SD
    .                              11278         1.00 


evt.sh -1::

    all_seqhis_ana
    .                     cfo:-  -1:g4live:source 
    .                              11278         1.00 
    0000               41        0.516        5816        [2 ] CK AB
    0001           7cccc1        0.131        1476        [6 ] CK BT BT BT BT SD
    0002              461        0.066         745        [3 ] CK SC AB
    0003           8cccc1        0.056         637        [6 ] CK BT BT BT BT SA
    0004          7cccc61        0.056         635        [7 ] CK SC BT BT BT BT SD
    0005          8cccc61        0.026         288        [7 ] CK SC BT BT BT BT SA
    0006         7cccc661        0.022         247        [8 ] CK SC SC BT BT BT BT SD
    0007             4661        0.021         235        [4 ] CK SC SC AB
    0008             4cc1        0.013         146        [4 ] CK BT BT AB
    0009         8cccc661        0.009          97        [8 ] CK SC SC BT BT BT BT SA
    0010        7cccc6661        0.007          75        [9 ] CK SC SC SC BT BT BT BT SD
    0011            4cc61        0.006          71        [5 ] CK SC BT BT AB
    0012            46661        0.006          70        [5 ] CK SC SC SC AB
    0013          7ccccc1        0.006          68        [7 ] CK BT BT BT BT BT SD
    0014              4c1        0.006          63        [3 ] CK BT AB
    0015          8ccccc1        0.004          42        [7 ] CK BT BT BT BT BT SA
    0016         7ccccc61        0.004          42        [8 ] CK SC BT BT BT BT BT SD
    0017        8cccc6661        0.004          40        [9 ] CK SC SC SC BT BT BT BT SA
    0018             4c61        0.003          35        [4 ] CK SC BT AB
    0019       7cccc66661        0.003          29        [10] CK SC SC SC SC BT BT BT BT SD
    .                              11278         1.00





