blyth-OJ-pmt-hit-type-2-for-muon-hits/index
=============================================

Overview
-----------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1171

* previously suspected this needed new Custom4 causing delay to merge,
  but from reading the code see no sign of that


Steps to get it merged
------------------------

1. DONE : study this branch checking especially what it requires from Custom4 and Opticks

   * just needs to role-back some of the NormalTrackInfo changes, retaining the FromTrack


Steps deferred to a future OPTICKS-MODE 3 REVIVAL branch
----------------------------------------------------------

1. study Custom4 current version and next one, especially wrt trackinfo
2. create some Custom4 tests, probably into a separate branch for that
3. discuss with Tao how to proceed with Custom4 update and do that



Review MR 1171, Draft: integrating Opticks GPU hit merging and photon-lite with JUNOSW + NormalTrackInfo rejig avoiding dangerous C-style casts
--------------------------------------------------------------------------------------------------------------------------------------------------


March 18 2026 : NormalTrackInfo roleback
------------------------------------------

::

    git show main:Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh > Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh_
    git show main:Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc > Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc_

Before reverting NormalTrackInfo retain changes in ~/j/NormalTrackInfo::

    (ok) A[blyth@localhost junosw]$ cp Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh ~/j/NormalTrackInfo/
    (ok) A[blyth@localhost junosw]$ cp Simulation/DetSimV2/SimUtil/src/NormalTrackInfo.cc ~/j/NormalTrackInfo/
    (ok) A[blyth@localhost junosw]$ cp Simulation/DetSimV2/SimUtil/include/NormalTrackInfoDebug.h ~/j/NormalTrackInfo/
    (ok) A[blyth@localhost junosw]$ cp Simulation/DetSimV2/SimUtil/tests/NormalTrackInfo_test.cc ~/j/NormalTrackInfo/
    (ok) A[blyth@localhost junosw]$ cp Simulation/DetSimV2/SimUtil/tests/NormalTrackInfo_test.sh ~/j/NormalTrackInfo/


Just need to keep::


    static       NormalTrackInfo* FromTrack(const G4Track* track);
    static const NormalTrackInfo* FromTrack(const G4Track& track);


    inline NormalTrackInfo* NormalTrackInfo::FromTrack(const G4Track* track) // static
    {
        return track ? dynamic_cast<NormalTrackInfo*>(track->GetUserInformation()) : nullptr;
    }

    inline const NormalTrackInfo* NormalTrackInfo::FromTrack(const G4Track& track) // static
    {
        return FromTrack(&track);
    }


How to test this ? With ~/j/local.sh oj_test ojt and ojtt
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* /data2/blyth/local/oj_test/20260318/hitlitemerged/


FIXED : Issue 1 : ojt giving lots of qcerenkov warnings, with cosTheta > 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* THIS MEANS cerenkov wavelengths are flat random,
* FIXED THIS ~/o/notes/issues/qcerenkov_dumping_following_WITH_OLD_FRAME_due_to_matline_0.rst

::

    2026-03-18 15:37:20.524 INFO  [3897404] [SEvt::setNumPhoton@2614]  evt->num_photon 9195 evt->num_tag 0 evt->num_flat 0
    //qcerenkov::wavelength_sampled_bndtex idx   1280 sampledRI   1.000 cosTheta   1.136 sin2Theta   0.000 wavelength 154.707 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2784 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 192.791 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2785 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 125.202 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2786 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 102.389 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2787 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 162.512 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2788 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 471.085 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2789 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 101.372 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2790 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength  97.554 count 100 matline 0
    //qcerenkov::wavelength_sampled_bndtex idx   2791 sampledRI   1.000 cosTheta   1.206 sin2Theta   0.000 wavelength 590.119 count 100 matline 0



WIP : Issue 2 : missing(?) analysis script for a quick check of ojtt outputs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* ACTUALLY ojtt ANALYSIS WAS NOT BROUGHT OVER FROM ~/j/blyth-OJ-pmt-hit-type-2-for-muon-hits/detsim.sh

  * started by relocating profile and log analysis into ~/o/bin/SProf.sh for reuse



* from Wuhan presentation timings, looks like using SProf timestamps

::

    PREL->POST
    POST->DOWN
    HEAD->RESET


::

    A[blyth@localhost opticks]$ ojt log
    → /data2/blyth/local/oj_test/20260318/hitlitemerged/oj_test.log
    → /data2/blyth/local/oj_test/hit/oj_test.log
    → /data2/blyth/local/oj_test/hitmerged/oj_test.log
    → /data2/blyth/local/oj_test/hitlitemerged/oj_test.log
    → /data2/blyth/local/oj_test/hitlite/oj_test.log
    → /data2/blyth/local/oj_test/20260319/hit/oj_test.log
    → /data2/blyth/local/oj_test/20260319/hitmerged/oj_test.log
    → /data2/blyth/local/oj_test/20260319/hitlitemerged/oj_test.log
    → /data2/blyth/local/oj_test/20260319/hitlite/oj_test.log


Issue 3 : EPH output mostly irrelevant to opticksMode 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0)
    2026-03-19 10:29:25.953 [junoSD_PMT_v2::Initialize eventID 0
    2026-03-19 10:29:25.955 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2026-03-19 10:29:25.956 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    2026-03-19 10:29:25.957 ERROR [4130755] [SEvt::addGenstep@2397]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this
    2026-03-19 10:29:25.989 INFO  [4130755] [QEvt::gatherPhotonLite@697] [ evt.num_photon 9195 l.sstr (9195, 4, ) evt.photon 0
    [SPM::merge_partial_select num_in 9195 select_flagmask 8192 time_window   1.000
    ]SPM::merge_partial_select select_flagmask 8192 time_window   1.000 in 9195 selected 1767 merged 1764 selected/in   0.192 merged/selected   0.998
    junoSD_PMT_v2_Opticks::EndOfEvent_recordStats eventID 0 recorder NO  eph_meta -
    [SProcessHits_EPH::desc
                                     ProcessHits_count              0              0.000000    /M
                                      ProcessHits_true              0              0.000000    /M
                                     ProcessHits_false              0              0.000000    /M
                                     SaveNormHit_count              0              0.000000    /M
                                     SaveMuonHit_count              0              0.000000    /M
                                             EPH_UNSET              0              0.000000    /M
                                              EPH_NDIS              0              0.000000    /M
                                              EPH_NOPT              0              0.000000    /M
                                             EPH_NEDEP              0              0.000000    /M
                                            EPH_NBOUND              0              0.000000    /M
                                             EPH_NPROC              0              0.000000    /M
                                           EPH_NDETECT              0              0.000000    /M
                                           EPH_NDECULL              0              0.000000    /M
                                            EPH_YMERGE              0              0.000000    /M
                                             EPH_YSAVE              0              0.000000    /M
                                          EPH_SAVENORM              0              0.000000    /M
                                          EPH_SAVEMUON              0              0.000000    /M

                Initialize_G4HCofThisEvent_opticksMode              1              0.000001    /M
                      Initialize_G4HCofThisEvent_count              1              0.000001    /M
                           EndOfEvent_Simulate_eventID              0              0.000000    /M
                             EndOfEvent_Simulate_count              0              0.000000    /M

                          EndOfEvent_Simulate_EGPU_hit              0              0.000000    /M
                     EndOfEvent_hitCollection_entries0              0              0.000000    /M
                     EndOfEvent_hitCollection_entries1              0              0.000000    /M
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M
                  EndOfEvent_hitCollectionAlt_entries1              0              0.000000    /M

                      EndOfEvent_Simulate_merged_count              0              0.000000    /M
                     EndOfEvent_Simulate_savehit_count              0              0.000000    /M
                        SUM_merged_count_savehit_count              0              0.000000    /M

                      EndOfEvent_Simulate_merged_total              0              0.000000    /M
                     EndOfEvent_Simulate_savehit_total              0              0.000000    /M
                        SUM_merged_total_savehit_total              0              0.000000    /M

    SProcessHits_EPH::NOTES
    ------------------------

    ProcessHits_count
    ProcessHits_true
    ProcessHits_false
        number of calls to *SProcessHits_EPH::add* and sub-counts where is_hit is true/false,
        done from junoSD_PMT_v2::ProcessHits

    SaveNormHit_count
    SaveMuonHit_count
        counts collected from junoSD_PMT_v2::SaveNormHit junoSD_PMT_v2::SaveMuonHit

    All 7 EndOfEvent_Simulate values are collected from junoSD_PMT_v2_Opticks::EndOfEvent_Simulate

    EndOfEvent_Simulate_EGPU_hit
        Opticks GPU num_hit returned from SEvt::GetNumHit_EGPU() immediately following G4CXOpticks::simulate call

    EndOfEvent_Simulate_merged_count
    EndOfEvent_Simulate_savehit_count
        The sum of merged_count and savehit_count should sum to EGPU_hit in opticksMode:1

    EndOfEvent_Simulate_merged_total
    EndOfEvent_Simulate_savehit_total
        The totals sum over all events

    EndOfEvent_hitCollection_entries0
    EndOfEvent_hitCollection_entries1
    EndOfEvent_hitCollectionAlt_entries0
    EndOfEvent_hitCollectionAlt_entries1
        entries into hitCollection and hitCollectionAlt before and after the
        call to junoSD_PMT_v2_Opticks::EndOfEvent.
        This is recorded from junoSD_PMT_v2::EndOfEvent.

        In all cases entries0 are expected to be zero with entries1
        for the active collection matching the savehit_count

        For opticksMode:1 only hitCollection should be active,
        it contains the GPU originated hits.

        For opticksMode:3 both hitCollection and hitCollectionAlt should
        be active with hitCollection containing CPU hits and
        hitCollectionAlt containing GPU hits.

    ]SProcessHits_EPH::desc

    2026-03-19 10:29:25.998 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 1764 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-03-19 02:29:25.998867000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-03-19 02:29:26.020935000Z
    end of event action
    junotoptask:detsimiotask.finalize  INFO: events processed 1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names:
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries:
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 65.79 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 65.79 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)
    GenTools                 1           1.21100        1.21100      0.00000
    DetSimAlg                1           67.99500       67.99500     0.00000
    Sum of junotoptask       1           69.21000       69.21000     0.00000
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 WITH_G4CXOPTICKS
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1








March 18 2026 : Review commits in the branch
-----------------------------------------------


working out whats needed to get muon hits from sphotonlite hitlite array
    initially just added dumb "muon" hit conversion to junoSD_PMT_v2_Opticks
    without benefitting from the less info needed

use new opticks photonlite/hitlite to implement junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits not yet assuming GPU hit merging
    junoSD_PMT_v2_Opticks::EndOfEvent_CollectNormHits
    junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits PRIOR TO GPU HIT MERGING

improve python logging of the init methods, add init_opticks_environ that passes pmt hit type and merge window config to Opticks
    making sure the environment passed to Opticks is done early enough for consistent control

add EndOfEvent_CollectMuonHits_premerged that handles hitlite arrays that have been merged already, old traditional PMTHitMerger approach is moved to EndOfEvent_CollectMuonHits_cpumerge
     EndOfEvent_CollectMuonHits_premerged  : really simple direct from sphotonlite into the muonhit collection
     EndOfEvent_CollectMuonHits_cpumerge

     assert on ModeLite hit-type consistency in junoSD_PMT_v2_Opticks::Initialize
     --pmt-hit-type 2 # Only 1 or 2 allowed

     gpu_merge_operational still false


enable Opticks hitlitemerged for pmt_hit_type:2 hitmerged not yet impl
     OPTICKS_MODE_MERGE only for hitlitemerged


add JLog.h which provides J::Log for millisecond formatted time stamps
     just that

replace all? python print with log.info for time stamping and consistency


overhaul NormalTrackInfo and its usage, replacing all dangerous C-style casts with dynamic cast from static helper NormalTrackInfo::FromTrack, add standalone test and optional degug registry functionality
     SUBSTANTIAL ROLE-BACK NEEDED FOR TAO APPROVAL

     * https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1171/diffs?commit_id=97ec33fb93883a112872ec7c645c64788e78b5e8


explicitly restrict use of Geant4 track info to opticksMode 3
    motive is to avoid problems from trackinfo to only when actually need it


make it explicit that SEventConfig::ModeMerge dictates if the hits are premerged or not
    start using the GPU premerging, controlled via the envvar OPTICKS_MODE_MERGE SEventConfig::ModeMerge


start revival of opticksMode:0 for standard CPU simulation with some Opticks instrumentation
    expect more effort needed here


switch to new FullHit impl removing pointless intermediary U4Hit
     Old impl hidden behind WITH_U4HIT destined for deletion

     junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits

     junoSD_PMT_v2_Opticks::EndOfEvent_CollectFullHits_premerged
            uses SEvt::localize_photon_inplace  [POTENTIAL FOR OPTIMIZATION HERE, BUT NO HOLDUP ON THE MR]


temporarily skip setting OPTICKS_MODE_MERGE as want to compare performance with and without
avoid needing a temporary change to OPTICKS_MODE_MERGE envvar setting for debugging by addition of OPTICKS_MODE_MERGE_OVERRIDE
   OPTICKS_MODE_MERGE_OVERRIDE







log : shows commits from nov+dec 2025
--------------------------------------

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/commits/blyth-OJ-pmt-hit-type-2-for-muon-hits/



::

    (ok) A[blyth@localhost junosw]$ git lg blyth-OJ-pmt-hit-type-2-for-muon-hits
    * 2025-12-08 a65ea362 - (origin/blyth-OJ-pmt-hit-type-2-for-muon-hits, blyth-OJ-pmt-hit-type-2-for-muon-hits) temporarily skip setting OPTICKS_MODE_MERGE as want to compare performance with and without (7 weeks ago) <Simon C Blyth>

        log.info("[init_opticks_environ")
        os.environ["OPTICKS_MODE_LITE"] = "1" if args.pmt_hit_type == 2 else "0"
        os.environ["OPTICKS_MODE_MERGE"] = "1" if args.pmt_hit_type == 2 else "0" # hitlitemerged only, hitmerged not yet impl
        #os.environ["OPTICKS_MODE_MERGE"] = "1" if args.pmtsd_merge_twindow > 0 else "0"  ## INSTEAD BE SENSITIVE TO ENV TO CHECK IMPACT
        os.environ["OPTICKS_MERGE_WINDOW"] = f"{args.pmtsd_merge_twindow:.6f}"  # ns unit, typically 1.0, 0.0 to disable merge
        log.info("]init_opticks_environ")



    * 2025-12-08 b2a6795d - switch to new FullHit impl removing pointless intermediary U4Hit (7 weeks ago) <Simon C Blyth>
    * 2025-12-01 cbe401b9 - start revival of opticksMode:0 for standard CPU simulation with some Opticks instrumentation (8 weeks ago) <Simon C Blyth>




    * 2025-12-01 03087ce2 - make it explicit that SEventConfig::ModeMerge dictates if the hits are premerged or not (8 weeks ago) <Simon C Blyth>

            * plus added more SProf labelling


    * 2025-12-01 6dd97627 - explicitly restrict use of Geant4 track info to opticksMode 3 (8 weeks ago) <Simon C Blyth>


    * 2025-12-01 4b526503 - overhaul NormalTrackInfo and its usage, replacing all dangerous C-style casts with dynamic cast from static helper NormalTrackInfo::FromTrack, add standalone test and optional degug registry functionality (8 weeks ago) <Simon C Blyth>

           AHAH : HERE IS THE TRICKY BIT

           * replace all dangerous casts from allover the place with NormalTrackInfo::FromTrack(track)
           * also rejigged  Simulation/DetSimV2/SimUtil/include/NormalTrackInfo.hh  with hidden debug functionality




    * 2025-12-01 e7ba84bd - replace all? python print with log.info for time stamping and consistency (8 weeks ago) <Simon C Blyth>



    * 2025-11-25 2319df6f - add JLog.h which provides J::Log for millisecond formatted time stamps (9 weeks ago) <Simon C Blyth>

          JLog.h added to CMakeLists.txt of multiple packages


    * 2025-11-25 f01f65a4 - enable Opticks hitlitemerged for pmt_hit_type:2 hitmerged not yet impl (9 weeks ago) <Simon C Blyth>

           Justs sets environment switches in init_opticks_environ based on python args


    * 2025-11-14 a5231d99 - add EndOfEvent_CollectMuonHits_premerged that handles hitlite arrays that have been merged already, old traditional PMTHitMerger approach is moved to EndOfEvent_CollectMuonHits_cpumerge (2 months ago) <Simon C Blyth>

           Profit from premerging with : junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits_premerged
           old cpumerge : junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits_cpumerge



    * 2025-11-14 e703d28a - improve python logging of the init methods, add init_opticks_environ that passes pmt hit type and merge window config to Opticks (2 months ago) <Simon C Blyth>


        the python logging was inproved to track down the cause of environment inconsistency, as described

        def init_opticks_environ(self, args):
            """
            TL;DR: init_opticks_environ must be invoked prior to init_mc_parameters

            When JUNOSW is compiled WITH_G4CXOPTICKS the first load of Opticks libs
            happens as a side effect of the Sniper.loadDll("libMultiFilmLUTMakerSvc.so")
            as that lib has dependency on Opticks libSysRap.so.
            That loadDll is done by init_mc_parameters.

            Hence in order to set Opticks envvars that are interpreted to give the sysrap/SEventConfig
            statics prior to libSysrap.so loading when the statics get initialized by the compiler
            generated function _GLOBAL__sub_I_SEventConfig.cc it is required that the environment
            is set prior to loading the first library that depends on Opticks libs.
            If this is not so, then the environment is still changed, but after SEventConfig
            statics are set : which causes inconsistency.
            """
            if args.opticks_mode == 0: return
            log.info("[init_opticks_environ")
            os.environ["OPTICKS_MODE_LITE"] = "1" if args.pmt_hit_type == 2 else "0"
            os.environ["OPTICKS_MERGE_WINDOW"] = f"{args.pmtsd_merge_twindow:.6f}"  # > 0 [ns] enables GPU hit merging
            log.info("]init_opticks_environ")





    * 2025-11-12 1fe32f2e - use new opticks photonlite/hitlite to implement junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits not yet assuming GPU hit merging (3 months ago) <Simon C Blyth>

         next improved on that with where EndOfEvent_CollectNormHits was same as before (U4Hit based)
         and EndOfEvent_CollectMuonHits did a direct conversion from sphotonlite into the summary hits

                 void EndOfEvent_CollectNormHits( int eventID );
                 void EndOfEvent_CollectMuonHits( int eventID );

         this also added some SProf.hh profiling::

                void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
                {
                    SProf::Add("junoSD_PMT_v2_Opticks__EndOfEvent_Simulate_HEAD");



    * 2025-11-04 deeae12d - working out whats needed to get muon hits from sphotonlite hitlite array (3 months ago) <Simon C Blyth>

         initially took minimal approach of just adding junoSD_PMT_v2_Opticks::convertHit_muon
         which trivially does everything and just summarizes at the last stage
         THIS TRIVIAL APPROACH DOES NOT BENEFIT FROM THE SUMMARIZED NATURE OF THE MUON HITS


    *   2025-10-29 429466da - Merge branch 'blyth-fix-opticks-PMT-serialization-issue-from-partial-addition-of-600-MPMT' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\
    | * 2025-10-29 4976b4ff - Avoids Opticks PMT serialization inconsistency between PMTParamData and PMTSimParamData by collecting added pmtNum info from PMTParamData (3 months ago) <blyth@ihep.ac.cn>
    * |   2025-10-29 8abae80c - Merge branch 'lintao/reprod25c/enable-trigger-edm-in-esd' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\ \
    | |/
    |/|
    | * 2025-10-29 0bacd2b5 - WIP: enable cd and wp trigger in ESD. (3 months ago) <Tao Lin>
    |/
    *   2025-10-24 b0890f6f - Merge branch 'lintao/rootio-dump/skimming' into 'main' (3 months ago) <lintao@ihep.ac.cn>
    |\
    | * 2025-10-24 17da8cef - WIP: support skimming in rootio-dump (3 months ago) <lintao@ihep.ac.cn>
    |/

