blyth-88-merge-totalTime
==========================


Hi Simon,

I re-checked the result after fixing the issue, the totalPE distributions are
almost the same as expected.

But it's strange that the natural geometry is more time-consuming compared with
the unnatural one. The figure below shows the time distributions of them,
corresponding to 100 jobs for each simulation configuration. How to understand
this phenomenon?

My simulation scripts and data are stored in the IHEP server:
/junofs/users/wangyg/Software/juno-dev/Official/sim_data

Best Regards,

Yaoguang


::

    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)     
    GenTools                 500         15.52200       0.03104      0.14086     
    DetSimAlg                500         653788.52722   1307.57705   31.37479     
    Sum of junotoptask       500         653806.11560   1307.61223   31.39943     
    #############################################################################





Hi Yaoguang, 

> I re-checked the result after fixing the issue, the totalPE distributions are
> almost the same as expected.
> 
> But it's strange that the natural geometry is more time-consuming compared with
> the unnatural one. The figure below shows the time distributions of them,
> corresponding to 100 jobs for each simulation configuration. How to understand
> this phenomenon?

Just a reminder. Some of the bugs in the old FastSim based implementation:

* many fake intersects onto Pyrex/Pyrex and Vacuum/Vacuum boundaries
* wrong polarization on reflect+refract within PMT 
* pyrex (not vacuum) propagation time within PMT
* unphysical mid-vacuumn ARTD, tunneling [actually my branch fixed this to allow validations]

Comparing the speed of an implementation with a large number of known bugs 
and one which fixes all those bugs is a bit of an apples-vs-oranges comparison.
Thats a idiom meaning not a valid comparison.  

Nevertheless, I agree that it is good to investigate where the time is going as 
that might allow speedups to be achieved while also not compromising correctness.
For example it is not impossible that some significant debugging instrumentation 
might be left in place which can now be disabled.  

My understanding is that you are comparing timings of two implementations 
from the branch against each other.

FastSim: --pmt-unnatural-geometry
Custom: --pmt-natural-geometry

However the FastSim implementation from the branch is not the same as the 
one from main. It is using a simpler junoPMTOpticalModel::ModelTrigger
with less geometry queries so I would expect it to be faster. 

You can infact switch the ModelTrigger implementation using an environment 
variable to switch to the old buggy version. That should slow things down
for the unnatural PMT geometry::

    export junoPMTOpticalModel__ModelTrigger_IMPL=1 

That envvar picks between the Simple and Buggy impl (line 167 below).  

    124 const int junoPMTOpticalModel::ModelTrigger_IMPL = EGet::Get<int>("junoPMTOpticalModel__ModelTrigger_IMPL", 0 ) ;
    ...
    144 G4bool junoPMTOpticalModel::ModelTrigger(const G4FastTrack &fastTrack)
    145 {
    146     _track = fastTrack.GetPrimaryTrack();
    147 
    148 #if defined(WITH_G4CXOPTICKS) || defined(PMTSIM_STANDALONE)
    149     m_track_id = C4Track::GetLabelID(_track) ;
    150     m_track_dump = ( m_track_id == PIDX && PIDX_ENABLED ) || PIDX == -2  ;
    151     LOG_IF(info, m_track_dump ) << " PIDX " << PIDX << " m_track_id " << m_track_id ;  
    152 #endif
    153         
    154     _pv = _track->GetVolume() ;
    155     _mlv = _pv->GetMotherLogical();
    156 
    157     envelope_solid = fastTrack.GetEnvelopeSolid();
    158 
    159     pos     = fastTrack.GetPrimaryTrackLocalPosition();
    160     dir     = fastTrack.GetPrimaryTrackLocalDirection();
    161     pol     = fastTrack.GetPrimaryTrackLocalPolarization();
    162     time    = fastTrack.GetPrimaryTrack()->GetGlobalTime();
    163     energy  = fastTrack.GetPrimaryTrack()->GetKineticEnergy();
    164 
    165     dist2 = kInfinity ;
    166 
    167     G4bool trig = ModelTrigger_IMPL == 0 ? ModelTriggerSimple_(fastTrack) : ModelTriggerBuggy_(fastTrack)  ;
    168     CollectDebugInfo(trig);
    169     return trig ;
    170 }


It would be interesting to see your timings when using the ModelTriggerBuggy. 
I expect the timings with that setting should be close to the timings that would be 
obtained with the main that the branch split from.
To find the main that the branch started from::

    git --no-pager log 636e^^.. --pretty=oneline 
    ...
    e843201a22ba1f29500cf46cca5fa17430466063 change classname to CustomG4OpBoundaryProcess for clarity
    636e78a25b8ce07ee8e16cbafc97bcb41954d996 bring in original Geant4 1042 G4OpBoundaryProcess under different name, ready for customization
    b4e0089a9305c9a055239390f2cbba9414012867 Merge branch 'yangyixiang_junosw_OnlineBuilding' into 'main'
    75ec43abfe38c7c46291ec7accdf5dd08062d14b Add building test to CI/CD for online OEC
        
The b4e0089 is the last commit that is in common between the main and the branch. 
I expect that timings for that main should be very close to those from the branch 
when using --pmt-unnatural-geometry and switching the bugs back on by using ModelTriggerBuggy.  
It would be good to confirm that and to contrast that baseline time
with the two timings you made already.   

Those comparisons will give a clearer picture of whether there is in fact a slowdown, 
when comparing the old main with the branch. 

As for speculations on what could cause timing differences. 
The Custom implementation is almost entirely using standard Geant4 
whereas the FastSim implementation switches Geant4 off for ModelTrigger:true. 
Custom has the advantage of a simpler geometry but the disadvantage of Geant4 being 
on all the time for all the photons.  As there are competing effects the only way to 
get a clearer picture is with fine grained timing measurements. 


Simon





::

    -bash-4.2$ pwd
    /junofs/users/wangyg/Software/juno-dev/Official/sim_data

    -bash-4.2$ diff old/job.sh new/job.sh 
    4c4
    < export JobPath=${TopPath}/sim_data/old
    ---
    > export JobPath=${TopPath}/sim_data/new
    20c20
    < (time python ${RunPath}/tut_detsim.py --evtmax 500 --seed $1 --output ${OutPath}/evt-nH-${1}.root --user-output ${OutPath}/user-evt-nH-${1}.root --pmt-unnatural-geometry gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0)
    ---
    > (time python ${RunPath}/tut_detsim.py --evtmax 500 --seed $1 --output ${OutPath}/evt-nH-${1}.root --user-output ${OutPath}/user-evt-nH-${1}.root --pmt-natural-geometry gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0)
    -bash-4.2$ 




HMM : how to fine-grained-instrument ? Start standalone for dev speed
-----------------------------------------------------------------------

* Q: How clearly does CPU time scale with number of step points ? 
* A: Very clear linear relationship with number of step points in averages shown.

* Q: Would truncation (photon time OR num bounces) have much benefit ? 

* Q: Given that backwards QE is set to zero, expect aggressive truncation would have little effect on hits ? 

* Q: How much of event time is spent simulating big bouncers ? 



Step Point Timestamps
--------------------------

* Start with full detail... record timestamps for each step .. 
* Added stamp.h to do this more simply than stimer.h 


trace where the SEvt start time metadata comes from
------------------------------------------------------

sysrap/sevt.py::

    137         metakey = os.environ.get("METAKEY", "junoSD_PMT_v2_Opticks_meta" )
    138         meta = getattr(f, metakey, None)


::

    191 void junoSD_PMT_v2_Opticks::EndOfEvent_Debug(int eventID )
    192 {
    193     std::cerr
    194         << "junoSD_PMT_v2_Opticks::EndOfEvent_Debug"
    195         << " eventID " << eventID
    196         << " opticksMode " << m_opticksMode
    197         << " with m_jpmt_dbg " << ( m_jpmt_dbg ? "YES" : "NO " )
    198         << std::endl
    199         ;
    200 
    201     if( m_jpmt_dbg != nullptr )
    202     {
    203         NP* jsdpmt = m_jpmt_dbg->get_meta_array(m_opticksMode, eventID ) ;  // junoSD_PMT_v2_Debug
    204         jsdpmt->set_meta<int>("VERSION", ssys::getenvint("VERSION", -1) );
    205         jsdpmt->set_meta<double>("SEvt__TimerDone", SEvt::TimerDone() );
    206         jsdpmt->set_meta<uint64_t>("SEvt__TimerStartCount", SEvt::TimerStartCount() );
    207         SEvt::SaveExtra("junoSD_PMT_v2_Opticks.npy", jsdpmt );
    208 
    209         LOG(LEVEL) << m_jpmt_dbg->desc() ;
    210         m_jpmt_dbg->zero();
    211     }


    epsilon:sysrap blyth$ opticks-f TimerStartCount
    ./sysrap/SEvt.hh:    static uint64_t TimerStartCount(); 
    ./sysrap/SEvt.cc:uint64_t SEvt::TimerStartCount(){ return TIMER->start_count() ; }
    epsilon:opticks blyth$ 


Added sysrap/stamp.h "uint64_t stamp::Now()" for simple epoch stamping
------------------------------------------------------------------------

See sysrap/tests/stamp_test.sh 


How to add event and photon level time stamping ?
----------------------------------------------------

Time stamping every step point probably overkill 
could also restrict to just stamping at event and photon levels

Actually it would be useful to know the extent of timing differences
for different types of step (especially C4CustomART steps, as 
that is a potential source of slowdown from the PMTAccessor)::

    U4Recorder::BeginOfEventAction
    U4Recorder::EndOfEventAction

    U4Recorder::PreUserTrackingAction_Optical
    U4Recorder::PostUserTrackingAction_Optical
    

How to store step level uint64_t stamps into aux ?
-----------------------------------------------------

Initial thought is to use aux and stamp every step point,  
but the stamps need uint64_t.  

Added squadx.h to facilitate shoe horning the uint64_t into 
the 32 bit element quad4 of the aux::

    epsilon:opticks blyth$ o
    On branch master
    Your branch is up-to-date with 'origin/master'.

    Untracked files:
      (use "git add <file>..." to include in what will be committed)

        sysrap/squadx.h
        sysrap/tests/squadx_test.cc
        sysrap/tests/squadx_test.py
        sysrap/tests/squadx_test.sh


Where to do the stamping ?
------------------------------

Two options:

SEvt::pointPhoton 
   if possible and makes sense this is the best place, as most general.
   Of course it will be triggered by calls from U4Recorder::UserSteppingAction_Optical 

U4Recorder::UserSteppingAction_Optical 
   also possible, but less general 


Hmm this is all absolute stamps, could also just store durations. 
Yes, but the simplicity of the absolute stamps for getting timings 
from anywhere to anywhere is convenient. 


U4SimulateTest.sh standalone running
---------------------------------------

::

    In [7]: t.aux[0,:3,3,:2].copy().view("datetime64[us]")
    Out[7]: 
    array([['2023-05-12T15:09:57.636101'],
           ['2023-05-12T15:09:57.636104'],
           ['1970-01-01T00:00:00.000000']], dtype='datetime64[us]')

    In [8]: t.aux[1,:3,3,:2].copy().view("datetime64[us]")
    Out[8]: 
    array([['2023-05-12T15:09:57.636062'],
           ['2023-05-12T15:09:57.636065'],
           ['1970-01-01T00:00:00.000000']], dtype='datetime64[us]')

    In [9]: t.aux[-1,:3,3,:2].copy().view("datetime64[us]")
    Out[9]: 
    array([['2023-05-12T15:09:56.163085'],
           ['2023-05-12T15:09:56.163170'],
           ['1970-01-01T00:00:00.000000']], dtype='datetime64[us]')



    In [16]: w = np.where( n > 20)[0] ; w 
    Out[16]: array([1046, 1494, 6604, 6787, 8369, 8803])


    In [19]: tt = t.aux[w[0],:n[w[0]],3,:2].copy().view(np.uint64)[:,0]

    In [28]: np.c_[tt.view("datetime64[us]")]
    Out[28]: 
    array([['2023-05-12T15:09:57.541452'],
           ['2023-05-12T15:09:57.541466'],
           ['2023-05-12T15:09:57.541486'],
           ['2023-05-12T15:09:57.541520'],
           ['2023-05-12T15:09:57.541581'],
           ['2023-05-12T15:09:57.541639'],
           ['2023-05-12T15:09:57.541684'],
           ['2023-05-12T15:09:57.541739'],
           ['2023-05-12T15:09:57.541783'],
           ['2023-05-12T15:09:57.541827'],
           ['2023-05-12T15:09:57.541874'],
           ['2023-05-12T15:09:57.541917'],
           ['2023-05-12T15:09:57.541966'],
           ['2023-05-12T15:09:57.542041'],
           ['2023-05-12T15:09:57.542080'],
           ['2023-05-12T15:09:57.542115'],
           ['2023-05-12T15:09:57.542150'],
           ['2023-05-12T15:09:57.542193'],
           ['2023-05-12T15:09:57.542251'],
           ['2023-05-12T15:09:57.542298'],
           ['2023-05-12T15:09:57.542343'],
           ['2023-05-12T15:09:57.542390'],
           ['2023-05-12T15:09:57.542435'],
           ['2023-05-12T15:09:57.542481'],
           ['2023-05-12T15:09:57.542555']], dtype='datetime64[us]')

    In [29]: np.diff(tt)
    Out[29]: array([14, 20, 34, 61, 58, 45, 55, 44, 44, 47, 43, 49, 75, 39, 35, 35, 43, 58, 47, 45, 47, 45, 46, 74], dtype=uint64)

    ## no big poppies outstanding  

    In [31]: q[w[0]]
    Out[31]: array([b'TO BT BT BT BR SR SR SR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR SA                      '], dtype='|S96')

    In [31]: q[w[0]]
    Out[31]: array([b'TO BT BT BT BR SR SR SR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR SA                      '], dtype='|S96')

    In [32]: n[w[0]]
    Out[32]: 25

    In [33]: np.diff(tt).shape    ## times between the points 
    Out[33]: (24,)
    I


    epsilon:tests blyth$ ./U4SimulateTest.sh tt


    w
    8803
    q[w]
    [b'TO BT BT BT SR SR SR SR SR SR BR BR BR BR SR SR SR SR SR SR SR BR BR BR BT BT SA                ']
    n[w]
    27
    np.diff(tt)
    [ 3 18 34 62 45 45 41 46 44 86 43 40 39 58 46 46 42 43 45 53 78 42 40 39 54 19]

    np.c_[tt.view("datetime64[us]")] 
    [['2023-05-12T15:32:34.791890']
     ['2023-05-12T15:32:34.791893']
     ['2023-05-12T15:32:34.791911']
     ['2023-05-12T15:32:34.791945']
     ['2023-05-12T15:32:34.792007']
     ['2023-05-12T15:32:34.792052']
     ['2023-05-12T15:32:34.792097']
     ['2023-05-12T15:32:34.792138']
     ['2023-05-12T15:32:34.792184']
     ['2023-05-12T15:32:34.792228']
     ['2023-05-12T15:32:34.792314']
     ['2023-05-12T15:32:34.792357']
     ['2023-05-12T15:32:34.792397']
     ['2023-05-12T15:32:34.792436']
     ['2023-05-12T15:32:34.792494']
     ['2023-05-12T15:32:34.792540']
     ['2023-05-12T15:32:34.792586']
     ['2023-05-12T15:32:34.792628']
     ['2023-05-12T15:32:34.792671']
     ['2023-05-12T15:32:34.792716']
     ['2023-05-12T15:32:34.792769']
     ['2023-05-12T15:32:34.792847']
     ['2023-05-12T15:32:34.792889']
     ['2023-05-12T15:32:34.792929']
     ['2023-05-12T15:32:34.792968']
     ['2023-05-12T15:32:34.793022']
     ['2023-05-12T15:32:34.793041']]





N=0,1 Standalone one_pmt rain_line check
--------------------------------------------------


::

    epsilon:tests blyth$ N=-1 ./U4SimulateTest.sh tt
    BASH_SOURCE                    : ./FewPMT.sh 
    VERSION                        : -1 
    version_desc                   :  
    POM                            :  
    pom_desc                       :  
    GEOM                           : FewPMT 
    FewPMT_GEOMList                : nnvtLogicalPMT 
    LAYOUT                         : one_pmt 
    GEOM                           : FewPMT 
    _GEOMList                      : FewPMT_GEOMList 
    GEOMList                       : nnvtLogicalPMT 
    ./U4SimulateTest.sh : switch on some logging anyhow : THIS WILL BE VERBOSE
    CSGFoundry.CFBase returning [/Users/blyth/.opticks/GEOM/FewPMT], note:[via GEOM] 
    ERROR CSGFoundry.CFBase returned None OR non-existing CSGFoundry dir so cannot CSGFoundry.Load
    AFOLD:/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0/000
    BFOLD:/tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL1/000
    N:-1 
    SEvt symbol a pid -1 opt  off [0. 0. 0.]
    SEvt symbol b pid -1 opt  off [0. 0. 0.]
    #######  t.symbol : a 

    w
    1046
    q[w]
    [b'TO BT BT BT BR SR SR SR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR SA                      ']
    n[w]
    25
    np.diff(tt)
    [ 3 21 36 45 62 48 63 45 43 44 51 48 76 40 37 46 42 58 45 44 44 43 44 72]
    #np.c_[tt.view("datetime64[us]")] 


    w
    8803
    q[w]
    [b'TO BT BT BT SR SR SR SR SR SR BR BR BR BR SR SR SR SR SR SR SR BR BR BR BT BT SA                ']
    n[w]
    27
    np.diff(tt)
    [ 3 19 32 58 45 45 41 45 45 82 39 37 35 55 46 45 40 42 45 51 74 40 36 36 50 18]
    #np.c_[tt.view("datetime64[us]")] 

    #######  t.symbol : b 

    w
    117
    q[w]
    [b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR BR SR BR SR BR BR ']
    n[w]
    32
    np.diff(tt)
    [ 2 18 28 30 26 29 26 29 25 31 28 29 27 29 26 29 26 28 26 29 26 31 27 30 27 27 29 26 30 27 26]
    #np.c_[tt.view("datetime64[us]")] 


    w
    8854
    q[w]
    [b'TO BT BT BR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR BR BR BR BR SA                      ']
    n[w]
    25
    np.diff(tt)
    [11 36 35 33 33 31 42 41 80 89 77 46 45 31 30 30 52 42 50 77 57 56 67 88]
    #np.c_[tt.view("datetime64[us]")] 


    In [1]:             


What to look at ?
-------------------

* average CPU time per bounce in N=0 N=1 ? 
* what fraction of total time is covered by the stepping time : ie what are the gaps between the end of one photon and the start of the next 



Subtract off the earliest time, but avoid touching the zeros::

    ss0 = ss[:,0].min()

    In [4]: ss[np.where( ss != 0 )] -= ss0

    In [5]: ss
    Out[5]: 
    array([[1019385, 1019387,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019356, 1019358,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019328, 1019330,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019299, 1019301,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019271, 1019272,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           ...,
           [    273,     275,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    242,     244,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    210,     212,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    167,     174,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [      0,      39,       0,       0,       0, ...,       0,       0,       0,       0,       0]], dtype=uint64)

    
Comparing step times::

    In [27]: np.diff(ss[n==6,:6], axis=1)
    Out[27]: 
    array([[ 2, 35, 35, 19, 16],
           [ 2, 35, 35, 19, 16],
           [ 2, 36, 34, 33, 30],
           [ 2, 36, 35, 18, 16],
           [ 2, 36, 35, 19, 16],
           [ 2, 36, 35, 34, 32],
           [ 2, 35, 21, 31, 35],
           [ 3, 38, 22, 34, 35],
           [ 2, 36, 20, 32, 33],
           [ 2, 36, 21, 31, 32],
           [ 2, 36, 20, 32, 33],
           [ 2, 36, 20, 31, 33],
           [ 2, 36, 20, 32, 53],
           [ 2, 82, 20, 34, 33],



    In [33]: ss[:,:10]
    Out[33]: 
    array([[1019385, 1019387,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019356, 1019358,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019328, 1019330,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019299, 1019301,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019271, 1019272,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019242, 1019244,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019214, 1019216,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019185, 1019187,       0,       0,       0,       0,       0,       0,       0,       0],
           [1019157, 1019158,       0,       0,       0,       0,       0,       0,       0,       0],

           [    392,     394,       0,       0,       0,       0,       0,       0,       0,       0],
           [    362,     364,       0,       0,       0,       0,       0,       0,       0,       0],
           [    333,     335,       0,       0,       0,       0,       0,       0,       0,       0],
           [    303,     305,       0,       0,       0,       0,       0,       0,       0,       0],
           [    273,     275,       0,       0,       0,       0,       0,       0,       0,       0],
           [    242,     244,       0,       0,       0,       0,       0,       0,       0,       0],
           [    210,     212,       0,       0,       0,       0,       0,       0,       0,       0],
           [    167,     174,       0,       0,       0,       0,       0,       0,       0,       0],
           [      0,      39,       0,       0,       0,       0,       0,       0,       0,       0]], dtype=uint64)

    In [34]:                                        

Usually about 30us between the last step point of one photon and the first step point of the next. 

    
Move that into sevt.py::

    In [1]: a.tt   # old N=0
    Out[1]: 
    array([[1433352, 1433355,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1433319, 1433322,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1433286, 1433289,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1433253, 1433256,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1433219, 1433223,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           ...,
           [    304,     307,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    269,     272,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    232,     236,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    185,     192,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [      0,      50,       0,       0,       0, ...,       0,       0,       0,       0,       0]], dtype=uint64)

    In [2]: b.tt   # new N=1
    Out[2]: 
    array([[1019385, 1019387,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019356, 1019358,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019328, 1019330,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019299, 1019301,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [1019271, 1019272,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           ...,
           [    273,     275,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    242,     244,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    210,     212,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [    167,     174,       0,       0,       0, ...,       0,       0,       0,       0,       0],
           [      0,      39,       0,       0,       0, ...,       0,       0,       0,       0,       0]], dtype=uint64)


Note the overall timings new is substantially quicker. But this is with a very simple single PMT geometry.


DONE : Machinery for  photon level timings
---------------------------------------------

As its not so easy to handle times with a variable number of steps. 
Added *sup* to SEvt for a quad4 of photon level supplemental info.

::

    In [8]: t0 = a.f.sup[:,0,:2].copy().view(np.uint64).squeeze()

    In [9]: t1 = a.f.sup[:,0,2:].copy().view(np.uint64).squeeze()

    In [10]: t0
    Out[10]: 
    array([1683916845167515, 1683916845167482, 1683916845167449, 1683916845167416, 1683916845167383, ..., 1683916843726291, 1683916843726254, 1683916843726215, 1683916843726110, 1683916843725747],
          dtype=uint64)

    In [11]: t1
    Out[11]: 
    array([1683916845167539, 1683916845167506, 1683916845167473, 1683916845167440, 1683916845167406, ..., 1683916843726373, 1683916843726280, 1683916843726244, 1683916843726201, 1683916843726056],
          dtype=uint64)

    In [12]: t0.view("datetime64[us]")
    Out[12]: 
    array(['2023-05-12T18:40:45.167515', '2023-05-12T18:40:45.167482', '2023-05-12T18:40:45.167449', '2023-05-12T18:40:45.167416', '2023-05-12T18:40:45.167383', ..., '2023-05-12T18:40:43.726291',
           '2023-05-12T18:40:43.726254', '2023-05-12T18:40:43.726215', '2023-05-12T18:40:43.726110', '2023-05-12T18:40:43.725747'], dtype='datetime64[us]')

    In [13]: np.c_[t0.view("datetime64[us]"),t1.view("datetime64[us]")]
    Out[13]: 
    array([['2023-05-12T18:40:45.167515', '2023-05-12T18:40:45.167539'],
           ['2023-05-12T18:40:45.167482', '2023-05-12T18:40:45.167506'],
           ['2023-05-12T18:40:45.167449', '2023-05-12T18:40:45.167473'],
           ['2023-05-12T18:40:45.167416', '2023-05-12T18:40:45.167440'],
           ['2023-05-12T18:40:45.167383', '2023-05-12T18:40:45.167406'],
           ...,
           ['2023-05-12T18:40:43.726291', '2023-05-12T18:40:43.726373'],
           ['2023-05-12T18:40:43.726254', '2023-05-12T18:40:43.726280'],
           ['2023-05-12T18:40:43.726215', '2023-05-12T18:40:43.726244'],
           ['2023-05-12T18:40:43.726110', '2023-05-12T18:40:43.726201'],
           ['2023-05-12T18:40:43.725747', '2023-05-12T18:40:43.726056']], dtype='datetime64[us]')

Solidify that into sevt.py::

    In [5]: np.c_[b.s0,b.s1].view("datetime64[us]")
    Out[5]: 
    array([['2023-05-12T18:40:27.221154', '2023-05-12T18:40:27.221173'],
           ['2023-05-12T18:40:27.221127', '2023-05-12T18:40:27.221146'],
           ['2023-05-12T18:40:27.221099', '2023-05-12T18:40:27.221118'],
           ['2023-05-12T18:40:27.221072', '2023-05-12T18:40:27.221091'],
           ['2023-05-12T18:40:27.221044', '2023-05-12T18:40:27.221063'],
           ...,
           ['2023-05-12T18:40:26.258471', '2023-05-12T18:40:26.258496'],
           ['2023-05-12T18:40:26.258434', '2023-05-12T18:40:26.258460'],
           ['2023-05-12T18:40:26.258388', '2023-05-12T18:40:26.258421'],
           ['2023-05-12T18:40:26.258272', '2023-05-12T18:40:26.258367'],
           ['2023-05-12T18:40:26.257455', '2023-05-12T18:40:26.258211']], dtype='datetime64[us]')

::

    In [8]: bt = b.s1 - b.s0

    In [9]: at = a.s1 - a.s0

    In [10]: at
    Out[10]: array([ 24,  24,  24,  24,  23, ...,  82,  26,  29,  91, 309], dtype=uint64)

    In [11]: bt
    Out[11]: array([ 19,  19,  19,  19,  19, ...,  25,  26,  33,  95, 756], dtype=uint64)

    ## that last one which takes longer is probably the first photon handled 



    In [12]: at.max()
    Out[12]: 2838

    In [13]: bt.max()
    Out[13]: 1875


    In [14]: at.sum()
    Out[14]: 1326188

    In [15]: bt.sum()
    Out[15]: 854781

    In [16]: bt.sum()/at.sum()
    Out[16]: 0.6445398389971859




    In [19]: a.q[ at > 1000]
    Out[19]: 
    array([[b'TO BT BT BT BR SR SR SR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR SA                      '],
           [b'TO BT BT BT SR SR SR SR SR BR BR BR BR SR SR SR SR SR SR BR BR BT BT SA                         '],
           [b'TO BT BT BT SR SR BR SR SR BR SR SR BR SR SR SA                                                 '],
           [b'TO BT BT BT SR BR SR BR SR BR SR BR SR BR SR BT BT SA                                           '],
           [b'TO BT BT BT SR BR SR SR BR SR BR SR BR SR BR SR BT BT SA                                        '],
           [b'TO BT BT BT SR BR SR BR SR SA                                                                   '],
           [b'TO BT BT BT SR BR SR BR SR BR SR BR SR BR SR BR SR SA                                           '],
           [b'TO BT BT BT SR BR SR SR BR SR BR SR BR SR BR SR BR SR SR BR SR BR SR SA                         '],
           [b'TO BT BT BT SR BR SR SR BR SR BR SR BR SR BR SR BT BT SA                                        '],
           [b'TO BT BT BT SR BR SR SR BR SR BR SR BR SR BT BT SA                                              '],
           [b'TO BT BT BT SR BR SR SR BR SR BR SR BR SR BR SR SR BR SR BT BT SA                               '],
           [b'TO BT BT BT SR BT BR BT BT SR BR SR BR SR BR SR SA                                              '],
           [b'TO BT BT BT SR SR BR SR SR BR SR SR BT BT SA                                                    '],
           [b'TO BT BT BT SR SR SR SR SR SR BR BR BR BR SR SR SR SR SR SR SR BR BR BR BT BT SA                ']], dtype='|S96')

    In [20]: b.q[ bt > 1000]
    Out[20]: array([[b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR BR SR BR SR BR BR ']], dtype='|S96')

    In [21]: b.q[ bt > 800]
    Out[21]: 
    array([[b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR BR SR BR SR BR BR '],
           [b'TO BT BT BR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR BR BR BR BR SA                      ']], dtype='|S96')

    In [22]: b.q[ bt > 500]
    Out[22]: 
    array([[b'TO BT SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR SR BR BR SR BR SR BR BR '],
           [b'TO BT BT BR BR BR BR BR BR BR BR BR BT BT SA                                                    '],
           [b'TO BT BT BR SR SR SR SR BR BR BR SR SR SR BT BT SA                                              '],
           [b'TO BT BT SR SR SR SR SR BR BR BR SR SR SR SR BT BT SA                                           '],
           [b'TO BT BT SR SR BR SR SR BR SR SR SR SR BR SR SR BT BT SA                                        '],
           [b'TO BT BT SR SR BR SR SR BR SR SR BR SR SR BR SR SR SA                                           '],
           [b'TO BT BT SR BR SR SR BR SR BR SR BR SR SR BR SA                                                 '],
           [b'TO BT BT SR SR BR BR SR SR BR SR BR SR BR SR BR SR SR BR BT BT SA                               '],
           [b'TO BT BT SR SR SR BR BR SR SR BR BR SR SR BT BT SA                                              '],
           [b'TO BT BT SR SR SR SR BR BR BR SR SR SR SR SR BT BT SA                                           '],
           [b'TO BT BT SR SR SR SR BR BR SR SR SR BR BR SR SA                                                 '],
           [b'TO BT BT SR SR SR SR SR BR BR BR BR SR SR SR SR SA                                              '],
           [b'TO BT BT SR SR SR SR SR BR BR BR SR SR SR SR BR SA                                              '],
           [b'TO BT BT SR SR SR SR SR SR SR SR BR BR BR BR BR BR BR BR BT BT SA                               '],
           [b'TO BT BT BR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR BR BR BR BR SA                      '],
           [b'TO BT BT BR SR SR SR SR SR BR BR BR BR SR SR SR SA                                              '],
           [b'TO AB                                                                                           ']], dtype='|S96')

    In [23]: np.where( bt > 500)
    Out[23]: (array([ 117,  998, 1174, 1305, 2026, 2085, 7604, 8131, 8447, 8533, 8577, 8647, 8698, 8781, 8854, 8866, 9999]),)


::

    In [6]: b.q[200:210]
    Out[6]: 
    array([[b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BR SA                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SD                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        '],
           [b'TO BT SA                                                                                        ']], dtype='|S96')

    In [7]: a.q[200:210]
    Out[7]: 
    array([[b'TO BT BT SD                                                                                     '],
           [b'TO BR SA                                                                                        '],
           [b'TO BR SA                                                                                        '],
           [b'TO BR SA                                                                                        '],
           [b'TO BT BT BR BT SA                                                                               '],
           [b'TO BR SA                                                                                        '],
           [b'TO BT BT SD                                                                                     '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SA                                                                                     '],
           [b'TO BT BT SD                                                                                     ']], dtype='|S96')


HUH: looks like fake skipping in A(N=0) is not operating ? 
-------------------------------------------------------------

::

    In [1]: a.q[128:138]          
    Out[1]: 
    array([[b'TO BT BT SD             '],
           [b'TO BT BT SA             '],
           [b'TO BR SA                '],
           [b'TO BT BT SA             '],
           [b'TO BT BT SD             '],
           [b'TO BT BT SA             '],
           [b'TO BR SA                '],
           [b'TO BT BT SD             '],
           [b'TO BR SA                '],
           [b'TO BT BT SA             ']], dtype='|S96')

    In [2]: b.q[128:138]                                                                               
    Out[2]: 
    array([[b'TO BT SD                '],
           [b'TO BT SD                '],
           [b'TO BR SA                '],
           [b'TO BR SA                '],
           [b'TO BT BR BT SA          '],
           [b'TO BT SD                '],
           [b'TO BT SA                '],
           [b'TO BT SA                '],
           [b'TO BT SD                '],
           [b'TO BT BR BR SR BT SA    ']], dtype='|S96')

    In [5]: a.f.record[128,:4,0]
    Out[5]: 
    array([[253.344,   0.   , 195.   ,   0.   ],
           [253.344,   0.   ,  13.226,   0.834],
           [248.999,   0.   ,   0.695,   0.901],
           [248.998,   0.   ,   0.692,   0.901]], dtype=float32)

    In [6]: b.f.record[128,:4,0]
    Out[6]: 
    array([[253.344,   0.   , 195.   ,   0.   ],
           [253.344,   0.   ,  13.226,   0.834],
           [248.998,   0.   ,   0.692,   0.901],
           [  0.   ,   0.   ,   0.   ,   0.   ]], dtype=float32)



Shows the extra fake in A::

    N=0 APID=128 AOPT=idx ~/opticks/u4/tests/U4SimtraceTest.sh ana
    N=1 BPID=128 BOPT=idx ~/opticks/u4/tests/U4SimtraceTest.sh ana


Using ~/opticks/u4/tests/PIDX.sh to dump PIDX 128::

    ~/opticks/u4/tests/PIDX.sh 
    ...
    U4VPrimaryGenerator::GeneratePrimaries ph (10000, 4, 4, )
    U4App::GeneratePrimaries@203: ]
    SEvt::hostside_running_resize_@1256: resizing photon 0 to evt.num_photon 10000
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    253.344      0.000     13.226      0.834) is_fastsim_flag 0 FAKES_SKIP 1 is_fake 0
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    248.999      0.000      0.695      0.901) is_fastsim_flag 0 FAKES_SKIP 1 is_fake 0
    junoPMTOpticalModel::ModelTrigger@151:  PIDX 128 m_track_id 128
    junoPMTOpticalModel::ModelTriggerSimple_@376:  PIDX 128 label.id 128 dist1 0.00300585 trig 1 whereAmI 1
    junoPMTOpticalModel::DoIt@595:  PIDX 128 track.GetMomentumDirection (-0.327598,0,-0.944817)
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    248.998      0.000      0.692      0.901) is_fastsim_flag 1 FAKES_SKIP 1 is_fake 0
    SEvt::save@2478:  dir /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0/000


The recording needs to skip the FAKE where ModeTrigger:true happens.  


Add dumping of theLocalIntersect::

    SEvt::hostside_running_resize_@1256: resizing photon 0 to evt.num_photon 10000
    U4Recorder::ClassifyFake fdist -1.000 fin kOutside fso - theLocalPoint (253.344,0.000,13.226) theLocalDirection (-0.328,0.000,-0.945) theLocalIntersect (0.000,0.000,0.000) fakemask 0 desc  duration 1.000e-06
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    253.344      0.000     13.226      0.834) is_fastsim_flag 0 FAKES_SKIP 1 is_fake 0 fakemask 0
    U4Recorder::ClassifyFake fdist -1.000e+00 fin kOutside fso - theLocalPoint (2.490e+02,0.000e+00,6.948e-01) theLocalDirection (-3.276e-01,0.000e+00,-9.448e-01) theLocalIntersect (0.000e+00,0.000e+00,0.000e+00) fakemask 0 desc  duration 1.000e-06
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    248.999      0.000      0.695      0.901) is_fastsim_flag 0 FAKES_SKIP 1 is_fake 0 fakemask 0
    junoPMTOpticalModel::ModelTrigger@151:  PIDX 128 m_track_id 128
    junoPMTOpticalModel::ModelTriggerSimple_@376:  PIDX 128 label.id 128 dist1 0.00300585 trig 1 whereAmI 1
    junoPMTOpticalModel::DoIt@595:  PIDX 128 track.GetMomentumDirection (-0.327598,0,-0.944817)
    U4Recorder::ClassifyFake fdist 9.030e+01 fin kInside fso nnvt_body_solid_head theLocalPoint (2.490e+02,0.000e+00,6.920e-01) theLocalDirection (-3.276e-01,0.000e+00,-9.448e-01) theLocalIntersect (2.194e+02,0.000e+00,-8.463e+01) fakemask 0 desc  duration 2.000e-06
    U4Recorder::UserSteppingAction_Optical PIDX 128 post U4StepPoint::DescPositionTime (    248.998      0.000      0.692      0.901) is_fastsim_flag 1 FAKES_SKIP 1 is_fake 0 fakemask 0
    SEvt::save@2478:  dir /tmp/blyth/opticks/GEOM/FewPMT/U4SimulateTest/ALL0/000


Add extra line from theLocalPoint to theLocalIntersect to the plot, shows fdist intersect is on the lower hemi::

    N=0 APID=128 AOPT=idx LINE=249,0,0.692,219.4,0,-84.63  ~/opticks/u4/tests/U4SimtraceTest.sh ana

Hmm but thats not the one that needs to be skipped its the one before, which is showing no intersect. 

Find that need to reenable the slow ClassifyFake approach for Fakes to be found in the standalone test::

   export U4Recorder__ClassifyFake_FindPV_r=1 




Time stamping 
----------------

::

    epsilon:sysrap blyth$ opticks-f stamp::Now
    ./sysrap/tests/stamp_test.cc:    for(int i=0 ; i < N ; i++) tt[i] = stamp::Now(); 
    ./sysrap/tests/squadx_test.cc:    q[1].w.x = stamp::Now(); 
    ./sysrap/tests/squadx_test.cc:    q[1].w.y = stamp::Now(); 
    ./sysrap/tests/squadx_test.cc:    qx.q3.w.x = stamp::Now(); 
    ./sysrap/tests/squadx_test.cc:    qx.q3.w.y = stamp::Now(); 
    ./sysrap/stamp.h:inline uint64_t stamp::Now()
    ./sysrap/SEvt.cc:    xsup.q0.w.x = stamp::Now(); 
    ./sysrap/SEvt.cc:    auxx.q3.w.x = stamp::Now() ;  // shoe-horn uint64_t time stamp into aux 
    ./sysrap/SEvt.cc:    xsup.q0.w.y = stamp::Now(); 
    epsilon:opticks blyth$ 




Time Checks : After Fake skipping is working again
-----------------------------------------------------

::

    ~/opticks/u4/tests/U4SimulateTest.sh tt 


comparing first step point stamps for each photon with begin of event stamps::

    In [12]: da = a.t[:,0] - a.s0 ; da
    Out[12]: array([ 20,  19,  20,  19,  20, ...,  21,  32,  24,  70, 195], dtype=uint64)

    In [13]: db = b.t[:,0] - b.s0 ; db 
    Out[13]: array([ 16,  16,  17,  16,  17, ...,  22,  22,  28,  86, 705], dtype=uint64)

Exclude first photon step point from the max::

    In [17]: da[:-1].max()
    Out[17]: 85

    In [19]: db[:-1].max()
    Out[19]: 86

Solidify those into sevt.py::

    In [1]: a.dt
    Out[1]: array([ 20,  19,  20,  19,  20, ...,  21,  32,  24,  70, 195], dtype=uint64)

    In [2]: b.dt
    Out[2]: array([ 16,  16,  17,  16,  17, ...,  22,  22,  28,  86, 705], dtype=uint64)



HUH, diff of time stamps from first point to end of photon doesnt make sense, too small::

    In [19]: a.s1 - a.t[:,0]
    Out[19]: array([ 4,  5,  4,  5,  4, ...,  5,  5,  4, 19, 50], dtype=uint64)

    In [20]: aqt = a.s1 - a.t[:,0]

    In [21]: aqt.max()
    Out[21]: 2885

    In [23]: a.s1-a.s0
    Out[23]: array([ 24,  24,  24,  24,  24, ...,  26,  37,  28,  89, 245], dtype=uint64)

    In [24]: a.ss
    Out[24]: array([ 24,  24,  24,  24,  24, ...,  26,  37,  28,  89, 245], dtype=uint64)


Could be confused by fastsim resumption ? No its just use of inconsistent time baseline. 

Change to using the smallest s0 (beginPhoton) as a common baseline. 


Find some big bouncers and look at timings::


    In [14]: np.where( a.n > 20 )
    Out[14]: (array([1046, 1494, 6604, 6787, 8803]),)

    In [15]: np.where( b.n > 20 )
    Out[15]: (array([ 117, 8131, 8781, 8854]),)

    In [16]: a.t[1046]
    Out[16]: 
    array([1683990895888577, 1683990895888580, 1683990895888633, 1683990895888675, 1683990895888734, 1683990895888781, 1683990895888836, 1683990895888883, 1683990895888928, 1683990895888976,
           1683990895889019, 1683990895889068, 1683990895889145, 1683990895889185, 1683990895889222, 1683990895889258, 1683990895889301, 1683990895889362, 1683990895889410, 1683990895889457,
           1683990895889504, 1683990895889551, 1683990895889598, 1683990895889675,                0,                0,                0,                0,                0,                0,
                          0,                0], dtype=uint64)

    In [17]: a.q[1046]
    Out[17]: array([b'TO BT BT BR SR SR SR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR SA                         '], dtype='|S96')

    In [18]: a.tt[1046]
    Out[18]: 
    array([1388005, 1388008, 1388061, 1388103, 1388162, 1388209, 1388264, 1388311, 1388356, 1388404, 1388447, 1388496, 1388573, 1388613, 1388650, 1388686, 1388729, 1388790, 1388838, 1388885, 1388932,
           1388979, 1389026, 1389103,       0,       0,       0,       0,       0,       0,       0,       0], dtype=uint64)

    In [19]: a.s0[1046]
    Out[19]: 1683990895888553

    In [20]: a.s1[1046]
    Out[20]: 1683990895889676

    In [21]: a.s1[1046] - a.s0[1046]
    Out[21]: 1123

    In [22]: a.ss[1046]
    Out[22]: 1123

    In [23]: a.t[1046]
    Out[23]: 
    array([1683990895888577, 1683990895888580, 1683990895888633, 1683990895888675, 1683990895888734, 1683990895888781, 1683990895888836, 1683990895888883, 1683990895888928, 1683990895888976,
           1683990895889019, 1683990895889068, 1683990895889145, 1683990895889185, 1683990895889222, 1683990895889258, 1683990895889301, 1683990895889362, 1683990895889410, 1683990895889457,
           1683990895889504, 1683990895889551, 1683990895889598, 1683990895889675,                0,                0,                0,                0,                0,                0,
                          0,                0], dtype=uint64)

    In [24]: a.t[1046] - a.s0[1046]
    Out[24]: 
    array([                  24,                   27,                   80,                  122,                  181,                  228,                  283,                  330,
                            375,                  423,                  466,                  515,                  592,                  632,                  669,                  705,
                            748,                  809,                  857,                  904,                  951,                  998,                 1045,                 1122,
           18445060082813663063, 18445060082813663063, 18445060082813663063, 18445060082813663063, 18445060082813663063, 18445060082813663063, 18445060082813663063, 18445060082813663063], dtype=uint64)

    In [25]:                                                                              

    In [25]: a.s1[1046] - a.t[1046]
    Out[25]: 
    array([            1099,             1096,             1043,             1001,              942,              895,              840,              793,              748,              700,
                        657,              608,              531,              491,              454,              418,              375,              314,              266,              219,
                        172,              125,               78,                1, 1683990895889676, 1683990895889676, 1683990895889676, 1683990895889676, 1683990895889676, 1683990895889676,
           1683990895889676, 1683990895889676], dtype=uint64)








::


    In [26]: b.q[8854]
    Out[26]: array([b'TO BT BT BR SR SR SR SR SR BR BR BR BR BR SR SR SR SR SR SR BR BR BR BR SA                      '], dtype='|S96')

    In [27]: b.t[8854]
    Out[27]: 
    array([1683916826339374, 1683916826339376, 1683916826339411, 1683916826339444, 1683916826339476, 1683916826339507, 1683916826339537, 1683916826339567, 1683916826339595, 1683916826339640,
           1683916826339685, 1683916826339730, 1683916826339774, 1683916826339819, 1683916826339848, 1683916826339877, 1683916826339906, 1683916826339936, 1683916826339966, 1683916826339994,
           1683916826340036, 1683916826340081, 1683916826340125, 1683916826340169, 1683916826340213,                0,                0,                0,                0,                0,
                          0,                0], dtype=uint64)

    In [28]: b.t[8854] - b.s0[8854]
    Out[28]: 
    array([                  20,                   22,                   57,                   90,                  122,                  153,                  183,                  213,
                            241,                  286,                  331,                  376,                  420,                  465,                  494,                  523,
                            552,                  582,                  612,                  640,                  682,                  727,                  771,                  815,
                            859, 18445060156883212262, 18445060156883212262, 18445060156883212262, 18445060156883212262, 18445060156883212262, 18445060156883212262, 18445060156883212262], dtype=uint64)

    In [29]: b.s1[8854] - b.t[8854]
    Out[29]: 
    array([             840,              838,              803,              770,              738,              707,              677,              647,              619,              574,
                        529,              484,              440,              395,              366,              337,              308,              278,              248,              220,
                        178,              133,               89,               45,                1, 1683916826340214, 1683916826340214, 1683916826340214, 1683916826340214, 1683916826340214,
           1683916826340214, 1683916826340214], dtype=uint64)

    In [30]:                                                                            



DONE : Sanity Check Timings, beginEvent + endEvent stamps into metadata
------------------------------------------------------------------------

* the above examples suggest that step point stamps are correctly bracketed 
  by the beginPhoton endPhoton stamps 

* need to make the connection between event timings and the photon and step timings 
* what fraction of time is "covered" ? 


::

    In [3]: a.ee
    Out[3]: array([1683996203207999, 1683996204668958], dtype=uint64)   ## millionths of second [us] from epoch

    In [5]: a.ee[1] - a.ee[0]
    Out[5]: 1460959               # 1.46s duration     ## FAKE SKIPPING TIME MIGHT BE SIGNIFICANT 

    In [1]: a.ee.view("datetime64[us]")
    Out[1]: array(['2023-05-13T16:43:23.207999', '2023-05-13T16:43:24.668958'], dtype='datetime64[us]')

    In [12]: np.array( [a.s0.min(), a.s1.max() ] ).view("datetime64[us]")
    Out[12]: array(['2023-05-13T16:43:23.255086', '2023-05-13T16:43:24.668427'], dtype='datetime64[us]')

    In [13]: a.s1.max() - a.s0.min()    # s0,s1 and beginPhoton,endPhoton time stamps
    Out[13]: 1413341

    In [6]: np.sum(a.s1 - a.s0)
    Out[6]: 1297673         

    In [8]: 1297673/1413341         ## ~8% gap 
    Out[8]: 0.9181598779063227



    In [14]: 1413341/1460959
    Out[14]: 0.9674063406296823    ## photon time range covers ~97% of event time range 

    In [18]: a.s0.min() - a.ee[0]  ## time from BeginOfEvent to first photon start 
    Out[18]: 47087


    In [20]: 47087/1460959             
    Out[20]: 0.032230199478561684


::

    In [4]: b.ee
    Out[4]: array([1683996495777071, 1683996496795210], dtype=uint64)

    In [6]: b.ee[1] - b.ee[0]
    Out[6]: 1018139              # 1.02s 

    In [15]: b.s1.max() - b.s0.min()    # s0,s1 and beginPhoton,endPhoton time stamps
    Out[15]: 968137

    In [7]: np.sum(b.s1 - b.s0)
    Out[7]: 856967

    In [10]: 856967/968137          ## 12% gap
    Out[10]: 0.8851712102729262




    In [16]: 968137/1018139        ## photon time range covers ~95% of event time range   
    Out[16]: 0.9508888275569446

    In [17]: b.s0.min() - b.ee[0]   ## time from BeginOfEvent to first photon start 
    Out[17]: 49529

    In [19]: 49529/1018139          ## uncovered is mostly at start 
    Out[19]: 0.04864659933466845

    In [2]: b.ee.view("datetime64[us]")
    Out[2]: array(['2023-05-13T16:48:15.777071', '2023-05-13T16:48:16.795210'], dtype='datetime64[us]')



Connect the step point stamps with the begin/endPhoton stamps
----------------------------------------------------------------

::
 
    nn = np.arange( a.n.min(), a.n.max()+1, dtype=np.uint64 ) 
    n = 10    # selecting all photons with 10 points, makes easier to handle 
    w = np.where( a.n == n )[0]

    ## subtract off the first photon step point timestamp

    In [31]: a.t[w,:n] - a.t[w,0,np.newaxis]   
    Out[31]: 
    array([[[  0,   3,  54, 111, 154, 197, 241, 284, 357, 402],
            [  0,   4,  54, 112, 159, 199, 254, 328, 367, 402],
            [  0,   3,  97, 161, 213, 261, 346, 389, 446, 466],
            [  0,   3,  54, 111, 158, 203, 289, 328, 384, 430],
            [  0,   3,  56, 124, 182, 232, 328, 372, 429, 449],
            [  0,   3,  54, 111, 157, 202, 278, 323, 377, 396],

    ## point-to-point timings 

    In [47]: np.diff( a.t[w,:n], axis=1 )
    Out[47]: 
    array([[  3,  51,  57,  43,  43,  44,  43,  73,  45],
           [  4,  50,  58,  47,  40,  55,  74,  39,  35],
           [  3,  94,  64,  52,  48,  85,  43,  57,  20],
           [  3,  51,  57,  47,  45,  86,  39,  56,  46],
           [  3,  53,  68,  58,  50,  96,  44,  57,  20],
           [  3,  51,  57,  46,  45,  76,  45,  54,  19],
           [  3,  51,  58,  44,  44,  75,  38,  56,  57],

Selecting all photons with fixed number of step points makes it possible 
to compare first and last point with the begin/endPhoton timings::

    In [59]: np.c_[a.t[w,n-1] - a.t[w,0], a.ss[w]]
    Out[59]: 
    array([[402, 426],
           [402, 426],
           [466, 491],
           [430, 455],
           [449, 484],
           [396, 421],
           [426, 450],






DONE : presentation of some timing metrics 
----------------------------------------------

* HMM: use matplotlib to illustrate the timeline of the stamps 

::

    ~/opticks/u4/tests/tt.sh 

    average beginPhoton->endPhoton CPU time [us] vs (step point count - 2) 

    np.c_[mc]
    [[60.297 20.787]
     [35.821 14.994]]

    ranno
    np.diff(a.ee)[0]/1e6 :    1.480 
    np.diff(b.ee)[0]/1e6 :    1.040 

    np.diff(a.rr)[0]/1e6 :    2.176 
    np.diff(b.rr)[0]/1e6 :    1.718 



DONE : repeat A without the slow fakes skipping
-------------------------------------------------

::

    epsilon:tests blyth$ grep FAKES *.sh 
    FewPMT.sh:    export U4Recorder__FAKES_SKIP=1
    FewPMT.sh:    # export U4Recorder__FAKES="$fakes"  formerly used manual config of fakes skipping
    U4SimulateTest.sh:## moved LAYOUT and FAKES control inside geomscript so its in common 
    epsilon:tests blyth$ 

::

    average beginPhoton->endPhoton CPU time [us] vs (step point count - 2) 
    np.c_[mc]
    [[31.011 16.721]    # A: without Fake skipping  (with ModelTriggerSimple)
     [35.821 14.994]]

    PLOT1 : average beginPhoton->endPhoton CPU time [us] vs (step point count - 2) 
    np.c_[mc]
    [[35.006 10.051]
     [35.821 14.994]]
    ranno
    np.diff(a.ee)[0]/1e6 :    1.439 
    np.diff(b.ee)[0]/1e6 :    1.040 
    np.diff(a.rr)[0]/1e6 :    2.114 
    np.diff(b.rr)[0]/1e6 :    1.718 




    average beginPhoton->endPhoton CPU time [us] vs (step point count - 2) 
    np.c_[mc]
    [[31.837 15.296]     # A: without Fake skipping (with ModelTriggerBuggy)
     [35.821 14.994]]




WIP : repeat with insitu running : trying ntds2_cf with input photon
-----------------------------------------------------------------------

N=0::

    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 3           48.78200       16.26067     3.17436      
    DetSimAlg                3           9026.12207     3008.70736   55.61212     
    Sum of junotoptask       3           9075.07910     3025.02637   58.51619     

N=1::

    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 3           49.38200       16.46067     4.65143      
    DetSimAlg                3           8464.59204     2821.53068   47.24532     
    Sum of junotoptask       3           8514.19897     2838.06632   51.71269     


::

    In [4]: np.diff(a.rr)
    Out[4]: array([9075824], dtype=uint64)

    In [5]: np.diff(b.rr)
    Out[5]: array([8515728], dtype=uint64)

    In [6]: np.diff(b.rr)/1e6
    Out[6]: array([8.516])

    In [7]: np.diff(a.rr)/1e6
    Out[7]: array([9.076])

    In [8]: a.ee
    Out[8]: array([1684237724196005, 1684237727007215], dtype=uint64)

    In [9]: np.diff(a.ee)/1e6
    Out[9]: array([2.811])

    In [10]: np.diff(b.ee)/1e6
    Out[10]: array([2.661])



DONE : tt encapsulation into sevt_tt.py : avoiding duplication for use from ~/j/ntds
---------------------------------------------------------------------------------------

* From u4/tests/U4SimulateTest_tt.py  

Observe in both A and B pointPhoton stamp gaps mainly at last step, ending SD or SA::

   PLOT=STAMP STAMP_TT=90000,5000 STAMP_ANNO=1 ~/j/ntds/ntds.sh tt 


DONE : last pointPhoton stamp at photon(not point level) for easy usage in analysis
------------------------------------------------------------------------------------

Did this in SEvt::pointPhoton SEvt::finalPhoton 

::

    In [11]: b.q[8131]
    Out[11]: array([b'TO BT BT SR SR BR BR SR SR BR SR BR SR BR SR BR SR SR BR BT BT SA                               '], dtype='|S96')

    In [12]: b.sp[8131]
    Out[12]: 1684253013084985

    In [13]: b.t[8131]
    Out[13]: 
    array([1684253013084270, 1684253013084272, 1684253013084306, 1684253013084326, 1684253013084358, 1684253013084404, 1684253013084449, 1684253013084482, 1684253013084515, 1684253013084562,
           1684253013084595, 1684253013084641, 1684253013084673, 1684253013084719, 1684253013084751, 1684253013084796, 1684253013084829, 1684253013084861, 1684253013084907, 1684253013084952,
           1684253013084969, 1684253013084985,                0,                0,                0,                0,                0,                0,                0,                0,
                          0,                0], dtype=uint64)

    In [18]: b.t[8131,22]
    Out[18]: 0

    In [19]: b.t[8131,21]
    Out[19]: 1684253013084985

    In [20]: b.sp[8131]
    Out[20]: 1684253013084985

Already have direct access to first pointPhoton at b.t[8131,0]
Now have easy access to last pointPhoton at b.sp[8131] without having to find it. 


DONE : actually also need t_PenultimatePoint into sup(photon level)
-------------------------------------------------------------------

Lower last step CPU times mostly AB::

    In [25]: a.q[a.ff < 10]
    Out[25]: 
    array([[b'TO BT BT AB                                                                                     '],
           [b'TO BT BT BT BT BR BT BT AB                                                                      '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO AB                                                                                           '],

    In [24]: b.q[b.ff < 10]
    Out[24]: 
    array([[b'TO BT BT AB                                                                                     '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO BT BT BT BT BR BT BT BT BT DR BT DR BT BT BT BT DR BT SA                                     '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO BT BT BT BT AB                                                                               '],
           [b'TO BT AB                                                                                        '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO AB                                                                                           '],
           [b'TO BT BT AB                                                                                     '],
           [b'TO BT BT AB                                                                                     '],


DONE : add stamps from ProcessHits to probe the tail gaps ?
--------------------------------------------------------------

* hmm, the photon label is too lightweight to carry uint64_t 
  timestamps around. 

* an argumentless SEvt stamp call to record ProcessHits timestamp 
  into SEvt is possible. BUT : ProcessHits can be called 
  multiple times for each photon. 

  * see SEvt::AddProcessHitsStamp  

  Point is to probe the gap to see what is taking the time within in : 
  eg by collecting first, last and count of ProcessHits calls 
  for the photon and held in sup is possible.  

* Thought about doing things at ProcessHits debug  
  BUT : junoSD_PMT_v2_Debug is just keeping metadata 
  counts so not suitable for timestamp duties  


DONE : Probing the gap, shows ProcessHits calls generally in middle of gap
----------------------------------------------------------------------------

::

   PLOT=STAMP STAMP_TT=90000,5000 STAMP_ANNO=1 ~/j/ntds/ntds.sh tt
   PLOT=STAMP STAMP_TT=100000,2000 STAMP_ANNO=1 ~/j/ntds/ntds.sh tt

Look into B.9706 with large tail gap and b.hc == 3 (ProcessHits calls)::

   N=1 MODE=2 ~/j/ntds/ntds.sh ana

   N=1 MODE=2 CHECK=PID PID=9706  ~/j/ntds/ntds.sh ana

   N=1 MODE=3 CHECK=all_point W=ALL,PID PID=9706 ~/j/ntds/ntds.sh ana

Check for slow photons::

   N=1 MODE=2 CHECK=all_point W=ALL,US_MIN US=1500 ~/j/ntds/ntds.sh ana

Sanity check STAMP time range of one photon::

    In [8]: i = 9756 ; b.s0[i] - b.ee[0], b.s1[i] - b.ee[0]
    Out[8]: (90499, 90710)


DONE : examine some photons with stamp gaps
-----------------------------------------------

Did this by adding multiple selection plotting to j/ntds/ntds.{sh,py} 


DONE : More instrumentation in the gap 
-----------------------------------------

Added an integer argument to SEvt::AddProcessHitsStamp to 
allow collecting stamps from multiple positions within the ProcessHits 
territory and extend sup from quad4 to quad6 to make space for the stamp ranges. 

Bracket the ProcessHits call::

     360 #ifdef WITH_G4CXOPTICKS
     361 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     362 {
     363     SEvt::AddProcessHitsStamp(0);
     364 
     365     G4bool is_hit = ProcessHits_(step, nullptr) ;
     366     m_jpmt_dbg->add( m_eph, is_hit );
     367 
     368     G4Track* track = step->GetTrack() ;
     369     int label_id = C4Track::GetLabelID(track);
     370 
     371     C4Track::SetLabelEph(track, m_eph);
     372     C4Track::IncrementLabelExt(track) ;
     373 
     374     LOG_IF(LEVEL, (label_id % 1000) == 0) << " label " << C4Track::Desc(track)  << " m_eph " << EPH::Name(m_eph) ;
     375 
     376     SEvt::AddProcessHitsStamp(1);
     377     return is_hit ;
     378 }


DONE : Analyse the extra probe in the gap stamps
-------------------------------------------------

* How much of the gap is due to ProcessHits ? 
* compare timings with SD to other terminators 


::

    jcn
    STAMP_TT=


    In [9]: np.c_[np.unique( b.q[b.hi0 > 20], return_counts=True )]
    Out[9]: 
    array([[b'TO BT BR BT BT BT BT BT BT BT SD                                                                ', b'2'],
           [b'TO BT BR BT BT BT BT BT SD                                                                      ', b'3'],
           [b'TO BT BR BT BT BT SC BT BT BT BT BR BT BT BT BT BT BT SD                                        ', b'1'],
           [b'TO BT BR BT BT BT SC BT BT BT SD                                                                ', b'1'],
           [b'TO BT BR BT BT SD                                                                               ', b'5'],
           [b'TO BT BT BR BT BT BT BT BT BT BT BR BR BT BT BT BT BT BT BT SD                                  ', b'1'],
           [b'TO BT BT BR BT BT BT BT BT BT BT BT BT BT SD                                                    ', b'1'],
           [b'TO BT BT BR BT BT BT BT BT BT BT BT SD                                                          ', b'2'],
           [b'TO BT BT BR BT BT BT BT BT BT SD                                                                ', b'5'],
           [b'TO BT BT BR BT BT BT BT DR BT BT BT BT BR BT BT BT BT BT BT BT BT BT BT BT SD                   ', b'1'],
           [b'TO BT BT BR BT BT BT BT SC BT BT BT BT BT BT SD                                                 ', b'2'],
           [b'TO BT BT BR BT BT BT BT SC BT BT BT SD                                                          ', b'1'],
           [b'TO BT BT BR BT BT BT SD                                                                         ', b'9'],
           [b'TO BT BT BT BT SD                                                                               ', b'3366']], dtype='|S96')

    In [10]:                                            


WIP : Fast SD : is that SPMT ?
---------------------------------

Probably, but the SD point is miles away, so cannot easily see what its hitting::

    In [1]: b.hi0[9801]
    Out[1]: 1

    In [2]: b.q[9801]
    Out[2]: array([b'TO BT BT BT BR BT BT BT BT BT BT DR BT BT BT BT BT SC BT BT BT BT BT BT BT BT SD                '], dtype='|S96')


::

   N=1 MODE=3 CHECK=all_point W=ALL,PID PID=9801 ~/j/ntds/ntds.sh ana


DONE : ProcessHits Profiling : Initial Coarse SProfile<5> Check
------------------------------------------------------------------

::

    STAMP_TT=100k,2k ~/j/ntds/stamp.sh 


    In [4]: p = a.f.junoSD_PMT_v2_SProfile
    In [5]: i = 9879  ## pick an SD photon index with large ProcessHits (most of them) 

    In [3]: p.shape        ## CAUTION: ProcessHits often called more than once for a photon 
    Out[3]: (22063, 6)     ## BUT the last call is probably the one that is interesting (and that takes the time)

    ## HMM: maintaining a max stamp slot in SProfile would be convenient for analysis
    ## ACTUALLY CAN DO THAT EASILY WITH np.max(p[:,1:], axis=1 )

    In [6]: p[i]
    Out[6]: array([5673, 1684419268677283,  0, 0,  0, 0], dtype=uint64) ## NOPE: NEED TO DO A LOOKUP

    In [7]: np.where( p[:,0] == i )[0]
    Out[7]: array([120])

    In [9]: ii = np.where( p[:,0] == i )[0][0]  

    In [10]: p[ii]
    Out[10]: array([9879, 1684419267540089, 1684419267540090, 1684419267540143, 1684419267540143, 1684419267540146], dtype=uint64)

    In [11]: p[ii,1:]
    Out[11]: array([1684419267540089, 1684419267540090, 1684419267540143, 1684419267540143, 1684419267540146], dtype=uint64)

    In [12]: np.diff(p[ii,1:])   ## (0,1,2,3,4)   ## ALL TIME BETWEEN 1->2 (THAT WAS NOT EXPECTED)
    Out[12]: array([ 1, 53,  0,  3], dtype=uint64)


    In [11]: pmi = p[:,1]
    In [12]: pmx = np.max(p[:,1:], axis=1 )
    In [13]: pp = pmx - pmi 

    In [14]: pp
    Out[14]: array([2010,    0,    0,   55,    0, ...,    0,    0,    0,    0,    0], dtype=uint64)

    In [15]: pp[pp>10]
    Out[15]: array([2010,   55,   96,   60,   57, ...,   57,   58,   57,   58,   57], dtype=uint64)

    In [16]: pp[pp>20]
    Out[16]: array([2010,   55,   96,   60,   57, ...,   57,   58,   57,   58,   57], dtype=uint64)


    In [28]: p[pp>20,0]
    Out[28]: array([9999, 9998, 9995, 9994, 9993, ...,   24,   16,   11,    8,    6], dtype=uint64)

    In [29]: w = p[pp>20,0]

    In [30]: a.q[w]
    Out[30]: 
    array([[b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT BR BR SD                                                                         '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           ...,
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               '],
           [b'TO BT BT BT BT SD                                                                               ']], dtype='|S96')


    In [34]: np.diff(p[pp>20,1:],axis=1)
    Out[34]: 
    array([[                 191,                  720,                   30,                 1069],
           [                   1,                   54, 18445059654442035404,                    0],
           [                   0,                   56,                    0,                   40],
           [                   0,                   54,                    1,                    5],
           [                   0,                   53,                    0,                    4],
           ...,
           [                   0,                   53,                    0,                    4],
           [                   0,                   54,                    0,                    4],
           [                   1,                   52,                    1,                    3],
           [                   1,                   52,                    1,                    4],
           [                   0,                   53,                    1,                    3]], dtype=uint64)


All time between 1 and 2 looks common.


DONE : ProcessHits Profiling : Drill Down SProfile<11> Check
------------------------------------------------------------------

::

    pp = a.pf[a.pfr>20,1:][10:]  

    In [23]: pp.shape
    Out[23]: (3783, 11)

    In [24]: pp[:,0].shape
    Out[24]: (3783,)

    In [25]: pp[:,0,np.newaxis].shape   ## adding an axis allows element-by-element subtraction
    Out[25]: (3783, 1)

    In [26]: pp[:,0,None].shape
    Out[26]: (3783, 1)

    In [22]: pp - pp[:,0,None]
    Out[22]:#0   1   2   3   4-->5
    array([[ 0,  1,  1,  1,  1, 51, 52, 53, 53, 53, 57],
           [ 0,  1,  1,  1,  1, 51, 51, 53, 53, 53, 56],
           [ 0,  0,  1,  1,  1, 51, 52, 53, 53, 53, 56],
           [ 0,  1,  1,  1,  1, 52, 52, 53, 53, 54, 57],
           [ 0,  0,  0,  0,  0, 50, 50, 52, 52, 52, 54],
           [ 0,  0,  0,  0,  0, 50, 50, 51, 51, 52, 54],
           [ 0,  0,  1,  1,  1, 51, 52, 53, 53, 53, 57],
           [ 0,  0,  1,  1,  1, 53, 53, 55, 55, 55, 61],

Collect loadsa stamps across the slow zone::

     481 #ifdef WITH_G4CXOPTICKS
     482     m_profile->stamp(1);
     483 #endif
     484     // TODO: get CE and angle response from data.
     485     // = decide the CE (collection efficiency)
     486     // = the CE can be different at different position
     487     // == position
     488     const G4AffineTransform& trans = track->GetTouchable()->GetHistory()->GetTopTransform();
     489 #ifdef WITH_G4CXOPTICKS
     490     m_profile->stamp(2);
     491 #endif
     492     const G4ThreeVector& global_pos = postStepPoint->GetPosition();
     493 #ifdef WITH_G4CXOPTICKS
     494     m_profile->stamp(3);
     495 #endif
     496     G4ThreeVector local_pos = trans.TransformPoint(global_pos);
     497 #ifdef WITH_G4CXOPTICKS
     498     m_profile->stamp(4);
     499 #endif
     500     double qe = 1;
     501     double ce = 1;
     502     // == get the copy number -> pmt id
     503     int pmtID = get_pmtid(track);
     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ LOOKS LIKE get_pmtid IS TAKING ~50us FOR EVERY CANDIDATE HIT 
     504 #ifdef WITH_G4CXOPTICKS
     505     m_profile->stamp(5);
     506 #endif
     507     // = final DE = QE * CE, 
     508     // but QE is already applied (this is old implementation,
     509     // Now we use PMTSimParamSvc to get real QE and CE ), so only CE is important.
     510     // = DE: Detection Efficiency
     511     if(m_use_pmtsimsvc){
     512         qe = (m_enable_optical_model && PMT::Is20inch(pmtID)) ? 1.0 : m_PMTSimParsvc->get_pmtid_qe(pmtID,edep);
     513 #ifdef WITH_G4CXOPTICKS
     514         m_profile->stamp(6);
     515 #endif
     516         ce = m_PMTSimParsvc->get_pmtid_ce(pmtID,local_pos.theta());
     517 
     518 #ifdef WITH_G4CXOPTICKS
     519         m_profile->stamp(7);
     520 #endif
     521      }
     522      else{
     523         std::string volname = track->GetVolume()->GetName();
     524     GetQEandCEByOldWay(qe , ce , pmtID,  volname, local_pos);
     525      }
     526 #ifdef WITH_G4CXOPTICKS
     527     m_profile->stamp(8);
     528 #endif
     529 
     530 

::

    In [7]: np.diff(a.pf[a.pfr>20,1:],axis=1)[10:]   ## 5->6 is the consuming the time
    Out[7]: 
    array([[ 1,  0,  0,  0, 50,  1,  1,  0,  0,  4],
           [ 1,  0,  0,  0, 50,  0,  2,  0,  0,  3],
           [ 0,  1,  0,  0, 50,  1,  1,  0,  0,  3],
           [ 1,  0,  0,  0, 51,  0,  1,  0,  1,  3],
           [ 0,  0,  0,  0, 50,  0,  2,  0,  0,  2],
           ...,
           [ 0,  1,  0,  0, 49,  1,  1,  0,  0,  4],
           [ 0,  0,  0,  0, 52,  0,  2,  0,  0,  4],
           [ 0,  1,  0,  0, 50,  0,  2,  0,  0,  3],
           [ 0,  0,  0,  0, 51,  0,  2,  0,  0,  4],
           [ 0,  1,  0,  0, 51,  0,  1,  0,  1,  3]], dtype=uint64)



::

    STAMP_TT=100k,2k ~/j/ntds/stamp.sh 

    In [1]: a.pf.shape
    Out[1]: (22063, 12)

    In [2]: b.pf.shape
    Out[2]: (25986, 12)

sevt.py::

    239         if hasattr(f, 'junoSD_PMT_v2_SProfile') and not f.junoSD_PMT_v2_SProfile is None:
    240             pf = f.junoSD_PMT_v2_SProfile
    241             pfmx = np.max(pf[:,1:], axis=1 )
    242             pfmi = pf[:,1]
    243             pfr = pfmx - pfmi
    244         else:
    245             pf = None
    246             pfmx = None
    247             pfmi = None
    248             pfr = None
    249         pass
    250         self.pf = pf  ## CAUTION: multiple ProcessHits calls per photon, so not in photon index order 
    251         self.pfmx = pfmx
    252         self.pfmi = pfmi
    253         self.pfr  = pfr 


::

    In [4]: a.pfr
    Out[4]: array([2126,    0,    0,   55,    0, ...,    0,    0,    0,    0,    0], dtype=uint64)

    In [5]: a.pfr[a.pfr>20]
    Out[5]: array([2126,   55,  102,   58,   61, ...,   56,   58,   56,   57,   57], dtype=uint64)



DONE : Confirm Culprit "get_pmtid(track)" taking ~50us for every ProcessHits call that gets that far
--------------------------------------------------------------------------------------------------------

Follow up regarding get_pmtid in :doc:`blyth-88-get_pmtid_from_track_50us`


HMM : some gdb ctrl-c random sampling to see what inside ProcessHits takes the time
---------------------------------------------------------------------------------------

This is not feasible without gdb automation, because it takes ~4 minutes to get to the point of interest 
of a few seconds only. That could be extended by doing more events, but still impractical. 

::

    ntds2_dbg()
    {
       export BP=junoSD_PMT_v2::ProcessHits
       export EVTMAX=3
       N=0 GEOM=V0J008 ntds2
       return 0
    }


* checkout https://github.com/jasonrohrer/wallClockProfiler/blob/master/wallClockProfiler.cpp

wallClockProfiler looks interesting but looks like needs considerable improvement
to add flexibility. For example restricting sampling to after a breakpoint. 


NOPE : standalone ProcessHits 
--------------------------------

Arranging to run ProcessHits in standalone running 
would be the best way to find whats taking the time
as it gives fast dev cycle.  Actually thats not practical, 
for decision timings need to be insitu. 

Insitu testing above already reveals that the primary culprit is "get_pmtid(track)".  


WIP : Q:What is time fraction for handling the big bouncers ? 
-----------------------------------------------------------------

* calculate event times from sum of photon times and then vary a truncation cut 
  to back-of-envelope calculate the benefit would get from truncation. 

* my guess is that truncation not very helpful, as big bouncers are rare


TODO : gun running stamp analysis
------------------------------------

