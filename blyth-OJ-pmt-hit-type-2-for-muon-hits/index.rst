blyth-OJ-pmt-hit-type-2-for-muon-hits/index
=============================================

Overview
-----------

* suspect this needs new Custom4 causing delay to merge
* https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/1171


Steps to get it merged
------------------------

1. study this branch checking especially what it requires from Custom4 and Opticks
2. study Custom4 current version and next one, especially wrt trackinfo
3. create some Custom4 tests, probably into a separate branch for that
4. discuss with Tao how to proceed with Custom4 update and do that
5. create MR for this branch


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

