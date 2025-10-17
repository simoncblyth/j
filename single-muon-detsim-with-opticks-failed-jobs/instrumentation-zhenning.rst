Hi Zhenning,

Thank you for your report that Ziyan presented at 
this mornings simulation meeting. 

Regarding failed jobs in the recent production, you mentioned 3 issues:

1. events with more than max photon of 2000M

2. unexpected PMTid 

   * possibly WP wall PMTs, but that is not confirmed : 
     it could be some other bug causing incorrect pmtid

3. GPU hardware, ECC fail

   * as this is a hardware problem the only option is to avoid GPUs 
     with this problem, and report the issue to administrators... 
     could be poor connection

It would be good to know the proportions of those issues you got. 
Also were there any other issues ?   


For the first issue, I have made changes (not yet released)
to get simulations of 4.29 billion photons 
(OPTICKS_MAX_PHOTON=X32, max uint32_t) per event 
running successfully on my workstation already with no 
impact on performance. 
Do you think there will be significant numbers of events 
exceeding "X32" 4.29 billion photons ?  

In any case I will add the capability to optionally just give warnings 
when exceeding the MAX_PHOTON limit instead of exiting. 
Simulating more than 4.29 billion photons per event without 
impacting performace per million photons needs more development.

If the 2nd issue is really due to photons hitting wall WP PMTs,
then I would have expected it would happen much more than the first issue
in your production. Also handling of wall WP PMTs should be fixed
in the next OJ release.

To understand bottlenecks and plan how/what to optimize it would
be good to perform single jobs with the same 5/10 events (single and double muons) 
in J and OJ runs in order to make an apple-to-apple comparison. 

Opticks has profiling enabled by default that collects 
timestamps and memory usage into a "run_meta.txt" file that
gets written throughout running in order to still be available even
when a job crashes. Extract from run_meta.txt::

    SEvt__BeginOfRun:1760593677804485,7316440,1220224
    SEvt__beginOfEvent_FIRST_EGPU:1760593677804634,7316440,1220224
    SEvt__setIndex_A000:1760593677804659,7316440,1220224
    SEvt__endIndex_A000:1760593678062575,8372996,1332824
    SEvt__EndOfRun:1760593678127979,8266712,1227112
    CSGOptiX__SimulateMain_HEAD:1760593674165428,46456,11200
    CSGFoundry__Load_HEAD:1760593674165461,46456,11200
    CSGFoundry__Load_TAIL:1760593677267321,5419960,883336
    CSGOptiX__Create_HEAD:1760593677267361,5419960,883336
    CSGOptiX__Create_TAIL:1760593677804424,7316440,1220224
    A000_QSim__simulate_HEAD:1760593677804471,7316440,1220224
    A000_QSim__simulate_LBEG:1760593677804798,7316440,1220672
    A000_QSim__simulate_PRUP:1760593677804804,7316440,1220672
    A000_QSim__simulate_PREL:1760593677805962,8266712,1221120
    A000_QSim__simulate_POST:1760593677959345,8266712,1225600
    A000_QSim__simulate_DOWN:1760593678062442,8372996,1332824
    A000_QSim__simulate_LEND:1760593678062471,8372996,1332824
    A000_QSim__simulate_PCAT:1760593678062500,8372996,1332824
    A000_QSim__simulate_BRES:1760593678062548,8372996,1332824
    A000_QSim__reset_HEAD:1760593678062555,8372996,1332824
    A000_QSim__reset_TAIL:1760593678129505,8266712,1227112


The entries beginning A000 A001 etc are event level entries with the 
three numbers being : microseconds since epoch and virtual(VM) 
and resident(RS) memory of the process in KB. The suffixes like "QSim__simulate_HEAD" 
correspond to labels of places throughout the code where calls like the 
below are made::

    SProf::Add("QSim__simulate_HEAD")

Opticks has machinery that reads and analyses this metadata
(eg ~/opticks/sysrap/tests/sreport.sh)
So it would be good to gather the run_meta.txt files together
with other logs into a tarball that I can examine.

The directory where the "run_meta.txt" is written is determined from::

    $TMP/GEOM/$GEOM/$ExecutableName/$Reldir

* TMP defaults to /tmp/$USER/opticks unless you define it with "export TMP=..."
* GEOM is set by envset.sh eg to "J25_4_0_opticks_Debug"
* ExecutableName for tut_detsim.py running is probably "python3.11", unless
  you "export OPTICKS_SCRIPT=..." which will override that
* Reldir is probably something like "ALL1_Debug_Philox_no_event_name"
  unless you override the eventname with "export OPTICKS_EVENT_NAME=..." 

Using opticks with a C++ executable CSGOptiXSMTest gives rundir::

    /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvvlarge_evt/

The easiest way to find the "RunDir" is to run with the below
setting which will log the directory where the run_meta.txt is written::

    export SEvt__RUNMETA=1


::

    (ok) A[blyth@localhost ALL1_Debug_Philox_vvvvlarge_evt]$ ls -l 
    total 32
    drwxr-xr-x. 20 blyth blyth 4096 Oct 16 16:34 A000           ## event directory with ~50G of hits
    -rw-r--r--.  1 blyth blyth 4862 Oct 16 16:34 CSGOptiX__Ctx.log
    -rw-r--r--.  1 blyth blyth 7556 Oct 16 16:34 CSGOptiXSMTest.log
    -rw-r--r--.  1 blyth blyth  132 Oct 16 16:34 run.npy        ## placeholder NumPy array
    -rw-r--r--.  1 blyth blyth 7331 Oct 16 16:34 run_meta.txt   ## metadata associated with the run array


Currently the genstep/photon/hit counts are not included in the 
run_meta.txt as I usually save arrays with that info for my testing.  
But those arrays are too large to be practical for production
so I will add simple counts to the run_meta.txt. 
These counts are also visible in logging though. 

The below shows logging for a 4.29 billion photon event. 
The 256 gensteps are sliced into 18 pieces in order to fit within 
available VRAM (my workstation GPU has 32GB VRAM when can fit ~260M photons per launch)::

   2025-10-16 16:16:28.281 INFO  [1868052] [QSim::simulate@441]  eventID      0 igs (256, 6, 4, ) tot_ph_0 4294967040 tot_ph_0/M 4294 xxl YES MaxSlot 262000000 MaxSlot/M 262 sslice::Desc(igs_slice)
    sslice::Desc num_slice 18 TotalPhoton 4294967040 TotalPhoton/M 4294.967040
                      start    stop     offset      count    count/M 
       0 : sslice {       0,      15,         0, 251658225}251.658225
       1 : sslice {      15,      30, 251658225, 251658225}251.658225
       2 : sslice {      30,      45, 503316450, 251658225}251.658225
       3 : sslice {      45,      60, 754974675, 251658225}251.658225
       4 : sslice {      60,      75,1006632900, 251658225}251.658225
       5 : sslice {      75,      90,1258291125, 251658225}251.658225
       6 : sslice {      90,     105,1509949350, 251658225}251.658225
       7 : sslice {     105,     120,1761607575, 251658225}251.658225
       8 : sslice {     120,     135,2013265800, 251658225}251.658225
       9 : sslice {     135,     150,2264924025, 251658225}251.658225
      10 : sslice {     150,     165,2516582250, 251658225}251.658225
      11 : sslice {     165,     180,2768240475, 251658225}251.658225
      12 : sslice {     180,     195,3019898700, 251658225}251.658225
      13 : sslice {     195,     210,3271556925, 251658225}251.658225
      14 : sslice {     210,     225,3523215150, 251658225}251.658225
      15 : sslice {     225,     240,3774873375, 251658225}251.658225
      16 : sslice {     240,     255,4026531600, 251658225}251.658225
      17 : sslice {     255,     256,4278189825,  16777215} 16.777215
                      start    stop     offset      count    count/M 
     num_slice 18
    2025-10-16 16:17:03.597 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    0 dt   35.274382 slice    0 : sslice {       0,      15,         0, 251658225}251.658225
    2025-10-16 16:17:42.800 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    1 dt   36.166941 slice    1 : sslice {      15,      30, 251658225, 251658225}251.658225
    2025-10-16 16:18:22.211 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    2 dt   36.361664 slice    2 : sslice {      30,      45, 503316450, 251658225}251.658225
    2025-10-16 16:19:01.820 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    3 dt   36.607363 slice    3 : sslice {      45,      60, 754974675, 251658225}251.658225
    2025-10-16 16:19:41.570 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    4 dt   36.736681 slice    4 : sslice {      60,      75,1006632900, 251658225}251.658225
    2025-10-16 16:20:21.385 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    5 dt   36.776848 slice    5 : sslice {      75,      90,1258291125, 251658225}251.658225
    2025-10-16 16:21:01.049 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    6 dt   36.615532 slice    6 : sslice {      90,     105,1509949350, 251658225}251.658225
    2025-10-16 16:21:40.706 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    7 dt   36.700994 slice    7 : sslice {     105,     120,1761607575, 251658225}251.658225
    2025-10-16 16:22:20.554 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    8 dt   36.830185 slice    8 : sslice {     120,     135,2013265800, 251658225}251.658225
    2025-10-16 16:23:00.609 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i    9 dt   36.781247 slice    9 : sslice {     135,     150,2264924025, 251658225}251.658225
    2025-10-16 16:23:40.233 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   10 dt   36.640915 slice   10 : sslice {     150,     165,2516582250, 251658225}251.658225
    2025-10-16 16:24:19.883 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   11 dt   36.625538 slice   11 : sslice {     165,     180,2768240475, 251658225}251.658225
    2025-10-16 16:24:59.492 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   12 dt   36.683829 slice   12 : sslice {     180,     195,3019898700, 251658225}251.658225
    2025-10-16 16:25:39.402 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   13 dt   36.730781 slice   13 : sslice {     195,     210,3271556925, 251658225}251.658225
    2025-10-16 16:26:19.201 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   14 dt   36.676339 slice   14 : sslice {     210,     225,3523215150, 251658225}251.658225
    2025-10-16 16:26:59.007 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   15 dt   36.718967 slice   15 : sslice {     225,     240,3774873375, 251658225}251.658225
    2025-10-16 16:27:38.815 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   16 dt   36.712459 slice   16 : sslice {     240,     255,4026531600, 251658225}251.658225
    2025-10-16 16:27:44.380 INFO  [1868052] [QSim::simulate@489]  eventID 0 xxl YES i   17 dt    2.448857 slice   17 : sslice {     255,     256,4278189825,  16777215} 16.777215
    2025-10-16 16:28:37.037 INFO  [1868052] [QSim::simulate@523]  eventID 0 tot_dt  624.089522 tot_ph 4294967040 tot_ph/M 4294.966797 tot_ht  857047734 tot_ht/M 857.047729 tot_ht/tot_ph   0.199547 reset_ YES
    2025-10-16 16:28:37.037 INFO  [1868052] [SEvt::save@4370] /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvvlarge_evt/A000 [genstep,hit]
    2025-10-16 16:34:53.649 INFO  [1868052] [QSim::simulate@541] 
    SEvt__MINTIME
     (TAIL - HEAD)/M 1105.368774 (head to tail of QSim::simulate method) 
     (LEND - LBEG)/M 676.305054 (multilaunch loop begin to end) 
     (PCAT - LEND)/M  52.450851 (topfold concat and clear subfold) 
     (TAIL - BRES)/M 376.611786 (QSim::reset which saves hits) 
     tot_idt/M       624.089905 (sum of kernel execution int64_t stamp differences in microseconds)
     tot_dt          624.089522 int(tot_dt*M)    624089521 (sum of kernel execution double chrono stamp differences in seconds, and scaled to ms) 
     tot_gdt/M        52.034294 (sum of SEvt::gather int64_t stamp differences in microseconds)

    2025-10-16 16:34:53.841  841167325 : ]/data1/blyth/local/opticks_Debug/bin/cxs_min.sh 
    [sreport.main  argv0 sreport dirp /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXSMTest/ALL1_Debug_Philox_vvvvlarge_evt is_executable_sibling_path NO 
    [sreport.main : CREATING REPORT 

The dt show ~37s kernel execution for each slice of 251M photons.
Some of that logging will be done by default for large events, but the below setting switches 
on some extra logging::

    export SEvt__MINTIME=1


When comparing J and OJ performance it is 
good to consider the various stages of processing
and the overheads that Opticks needs like
genstep upload, kernel execution, hits download.

+-----------------------+-----------------------------------+
|  stage                |  OJ extra                         |
+=======================+===================================+
|  initialization       | Opticks geometry conversion       |   
+-----------------------+-----------------------------------+
|  non-optical sim      | genstep collection                |
+-----------------------+-----------------------------------+
|  end of event         | 1. upload gensteps                | 
|                       | 2. kernel execution               |
|                       | 3. download hits                  |
|                       | 4. convert hits into G4 coll.     | 
+-----------------------+-----------------------------------+


Simon


