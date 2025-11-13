branch-blyth-OJ-pmt-hit-type-2-for-muon-hits.rst
===================================================


Overview
---------

* DONE : added photonlite, photonlocal, hitlite, hitlocal
* DONE : validated hitlite by comparison with hitlocal, "cxs_min.sh lite"
* TODO : validate photonlocal, need to look at what happens with non-hit photons
* TODO : integrate hitlite with OJ
* TODO : merging 





CPU hit merge optimization
-----------------------------

* https://github.com/greg7mdp/parallel-hashmap



What is the time window ? How to pass it to Opticks ?
------------------------------------------------------

::

    BP=PMTHitMerger::doMerge TEST=hit2 ojet 



FIRST hcMuon population from Opticks
---------------------------------------

::

    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2319]  index 2147483647 instance 0
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2404]  tot_photon 9188 evt.num_photon 9169 num_photon_changed 1 gs.size 88 genstep.size 88 numgenstep_collected 88 numphoton_collected 9188 tot_photon 9188 s.index 87 s.photons 19 s.offset 9169 s.gentype 5 s.desc sgs: idx  87 pho    19 off   9169 typ DsG4Scintillation_r4695
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::setNumPhoton@2486]  evt->num_photon 9188 evt->num_tag 0 evt->num_flat 0
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2319]  index 2147483647 instance 0
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2404]  tot_photon 9193 evt.num_photon 9188 num_photon_changed 1 gs.size 89 genstep.size 89 numgenstep_collected 89 numphoton_collected 9193 tot_photon 9193 s.index 88 s.photons 5 s.offset 9188 s.gentype 5 s.desc sgs: idx  88 pho     5 off   9188 typ DsG4Scintillation_r4695
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::setNumPhoton@2486]  evt->num_photon 9193 evt->num_tag 0 evt->num_flat 0
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2319]  index 2147483647 instance 0
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::addGenstep@2404]  tot_photon 9195 evt.num_photon 9193 num_photon_changed 1 gs.size 90 genstep.size 90 numgenstep_collected 90 numphoton_collected 9195 tot_photon 9195 s.index 89 s.photons 2 s.offset 9193 s.gentype 5 s.desc sgs: idx  89 pho     2 off   9193 typ DsG4Scintillation_r4695
    2025-11-13 15:34:02.455 INFO  [995736] [SEvt::setNumPhoton@2486]  evt->num_photon 9195 evt->num_tag 0 evt->num_flat 0
    2025-11-13 15:34:02.455 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent@204] [  eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    2025-11-13 15:34:02.455 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent@206] 
    [junoSD_PMT_v2::descHitCollection alt NO  entries 0
    ]junoSD_PMT_v2::descHitCollection
    2025-11-13 15:34:02.456 INFO  [995736] [SEvt::beginOfEvent@1790]  eventID 0
    2025-11-13 15:34:02.456 INFO  [995736] [SEvt::clear_output@2080] ]
    2025-11-13 15:34:02.456 INFO  [995736] [SEvt::addInputGenstep@1011] 
    2025-11-13 15:34:02.456 ERROR [995736] [SEvt::addGenstep@2273]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this  
    2025-11-13 15:34:02.482 INFO  [995736] [SEvt::setNumPhoton@2486]  evt->num_photon 9195 evt->num_tag 0 evt->num_flat 0
    2025-11-13 15:34:02.535 INFO  [995736] [SEvt::gather_components@3922]  num_comp 1 from provider QEvt fkey f000
    2025-11-13 15:34:02.536 INFO  [995736] [SEvt::gather_components@3932]  k         hitlite a  <u4(1614, 4, ) null_component NO 
    2025-11-13 15:34:02.536 INFO  [995736] [SEvt::gather_components@3960]  num_comp 1 num_genstep -1 num_photon -1 num_hit -1 gather_total 1 genstep_total 0 photon_total 0 hit_total 0
    2025-11-13 15:34:02.537 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent_Simulate@235] [ eventID 0 [G4CXOpticks::descSimulate
    SEvt::descSimulate instance 0 index 0 num_genstep 90 num_photon 9195 num_hit 1614 num_hit.is_undef NO  sev.brief SEvt::brief  getIndex 0 hasInputPhoton N hasInputPhotonTransformed N]G4CXOpticks::descSimulate

    2025-11-13 15:34:02.537 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits@336] [ eventID 0 num_hit 1614 m_hit_type 2
    2025-11-13 15:34:02.539 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent@214] ]  eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 1544 GPU YES
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
                             EndOfEvent_Simulate_count              1              0.000001    /M 

                          EndOfEvent_Simulate_EGPU_hit           1614              0.001614    /M 
                     EndOfEvent_hitCollection_entries0              0              0.000000    /M 
                     EndOfEvent_hitCollection_entries1              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries1              0              0.000000    /M 

                      EndOfEvent_Simulate_merged_count             70              0.000070    /M 
                     EndOfEvent_Simulate_savehit_count           1544              0.001544    /M 
                        SUM_merged_count_savehit_count           1614              0.001614    /M 

                      EndOfEvent_Simulate_merged_total             70              0.000070    /M 
                     EndOfEvent_Simulate_savehit_total           1544              0.001544    /M 
                        SUM_merged_total_savehit_total           1614              0.001614    /M 

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

    2025-11-13 15:34:02.539 INFO  [995736] [junoSD_PMT_v2_Opticks::EndOfEvent_recordStats@443]  eventID 0 recorder NO  eph_meta -
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
                             EndOfEvent_Simulate_count              1              0.000001    /M 

                          EndOfEvent_Simulate_EGPU_hit           1614              0.001614    /M 
                     EndOfEvent_hitCollection_entries0              0              0.000000    /M 
                     EndOfEvent_hitCollection_entries1              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries0              0              0.000000    /M 
                  EndOfEvent_hitCollectionAlt_entries1              0              0.000000    /M 

                      EndOfEvent_Simulate_merged_count             70              0.000070    /M 
                     EndOfEvent_Simulate_savehit_count           1544              0.001544    /M 
                        SUM_merged_count_savehit_count           1614              0.001614    /M 

                      EndOfEvent_Simulate_merged_total             70              0.000070    /M 
                     EndOfEvent_Simulate_savehit_total           1544              0.001544    /M 
                        SUM_merged_total_savehit_total           1614              0.001614    /M 

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

    2025-11-13 15:34:02.539 INFO  [995736] [SEvt::gather_metadata@4005]  provmeta [NumPhotonCollected:9195
    NumGenstepCollected:90
    MaxBounce:31
    site:SEvt::endMeta
    hitmask:8192
    index:0
    instance:0
    SEvt__beginOfEvent_0:1763019242456263,11111016,4453456
    SEvt__beginOfEvent_1:1763019242456505,11111016,4453456
    SEvt__endOfEvent_0:1763019242539680,33592540,4461520
    t_BeginOfEvent:1763019242456354
    t_setGenstep_0:0
    t_setGenstep_1:0
    t_setGenstep_2:0
    t_setGenstep_3:1763019242456636
    t_setGenstep_4:1763019242457749
    t_setGenstep_5:1763019242478682
    t_setGenstep_6:1763019242478760
    t_setGenstep_7:1763019242482166
    t_setGenstep_8:1763019242527108
    t_PreLaunch:1763019242527145
    t_PostLaunch:1763019242535720
    t_EndOfEvent:1763019242539689
    t_Event:83335
    t_Launch:0.00853907
    ]
    2025-11-13 15:34:02.539 INFO  [995736] [SEvt::save@4406] SEvt::DescComponent
     SEventConfig::DescGatherComp hitlite

     SEventConfig::DescSaveComp 
                     hit                    - 
                    seed                    - 
                 genstep                    -       SEventConfig::MaxGenstep            10000000
                  photon                    -        SEventConfig::MaxPhoton       1000000000000
                  record                    -        SEventConfig::MaxRecord                   0
                     aux                    -           SEventConfig::MaxAux                   0
                     sup                    -           SEventConfig::MaxSup                   0
                     rec                    -           SEventConfig::MaxRec                   0
                     seq                    -           SEventConfig::MaxSeq                   0
                  domain                    - 
                simtrace                    - 
                 g4state                    - 
                     pho                    - 
                      gs                    - 

    2025-11-13 15:34:02.539 INFO  [995736] [SEvt::save@4407] [NPFold::desc
    NPFold::desc_subfold
     tot_items 1
     folds 1
     paths 1
      0 [/]  stamp:13
    NPFold::desc(0) 
    [NPFold::desc_(0)
     subfold 0 ff 0 kk 1 aa 1
    [NP::DescMetaKVS only_with_stamp : NO 
    [NP::DescMetaKVS_kvs  keys.size 25 vals.size 25 tt.size 25 num_keys 25
                    t_setGenstep_1 :                                   0                                                                  
                          t_Launch :                          0.00853907                                                                  
                           t_Event :                               83335                                                                  
                    t_setGenstep_2 :                                   0                                                                  
                NumPhotonCollected :                                9195                                                                  
                    t_setGenstep_0 :                                   0                                                                  
                          instance :                                   0                                                                  
               NumGenstepCollected :                                  90                                                                  
                         MaxBounce :                                  31                                                                  
                              site :                       SEvt::endMeta                                                                  
                             index :                                   0                                                                  
                           hitmask :                                8192                                                                  

                                 k :                                   v                 t:microsecond  dt0:(t-t0)  dt1:(t-t1)  dt:(t-tpr)
              SEvt__beginOfEvent_0 :   1763019242456263,11111016,4453456      2025-11-13T15:34:02..456           0                        
                    t_BeginOfEvent :                    1763019242456354      2025-11-13T15:34:02..456          91           0          91
              SEvt__beginOfEvent_1 :   1763019242456505,11111016,4453456      2025-11-13T15:34:02..456         242         151         151
                    t_setGenstep_3 :                    1763019242456636      2025-11-13T15:34:02..456         373         282         131
                    t_setGenstep_4 :                    1763019242457749      2025-11-13T15:34:02..457       1,486       1,395       1,113
                    t_setGenstep_5 :                    1763019242478682      2025-11-13T15:34:02..478      22,419      22,328      20,933
                    t_setGenstep_6 :                    1763019242478760      2025-11-13T15:34:02..478      22,497      22,406          78
                    t_setGenstep_7 :                    1763019242482166      2025-11-13T15:34:02..482      25,903      25,812       3,406
                    t_setGenstep_8 :                    1763019242527108      2025-11-13T15:34:02..527      70,845      70,754      44,942
                       t_PreLaunch :                    1763019242527145      2025-11-13T15:34:02..527      70,882      70,791          37
                      t_PostLaunch :                    1763019242535720      2025-11-13T15:34:02..535      79,457      79,366       8,575
                SEvt__endOfEvent_0 :   1763019242539680,33592540,4461520      2025-11-13T15:34:02..539      83,417      83,326       3,960
                      t_EndOfEvent :                    1763019242539689      2025-11-13T15:34:02..539      83,426      83,335           9
    ]NP::DescMetaKVS_kvs
    ]NP::DescMetaKVS

       0 :             hitlite.npy : (1614, 4, )
    ]NPFold::desc_(0)
    [NPFold::descf_( 0)
    ]NPFold::descf_( 0)

    ]NPFold::desc

    2025-11-13 15:34:02.541 INFO  [995736] [SEvt::save@4486] SKIP SAVE AS NPFold::_save_local_item_count zero 
    2025-11-13 15:34:02.541 INFO  [995736] [SEvt::clear_output@2080] ]
    2025-11-13 15:34:02.541 INFO  [995736] [SEvt::setNumPhoton@2486]  evt->num_photon 0 evt->num_tag 0 evt->num_flat 0
    2025-11-13 15:34:02.541 INFO  [995736] [SEvt::endOfEvent@1862]  is_last_eventID YES is_last_evt_instance YES
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 1544 GPU YES
    hitCollectionTT.size: 0	userhitCollectionTT.size: 0
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2025-11-13 07:34:02.542377000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2025-11-13 07:34:02.604272000Z
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 152.20 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 152.20 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.29200        1.29200      0.00023      
    DetSimAlg                1           154.06000      154.06000    0.00000      
    Sum of junotoptask       1           155.35500      155.35500    0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 1 WITH_G4CXOPTICKS 
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2025-11-13 15:34:02,711] p995736 {/home/blyth/junosw/InstallArea/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [Thread 0x7fffcd5ff640 (LWP 995752) exited]
    Delete G4SvcRunManager
    2025-11-13 15:34:02.866 INFO  [995736] [junoSD_PMT_v2_Opticks::~junoSD_PMT_v2_Opticks@118] junoSD_PMT_v2_Opticks::desc WITH_G4CXOPTICKS  WITH_G4CXOPTICKS_EPH  m_opticksMode 1 m_hit_type 2 m_merged_total 70 m_savehit_total 1544 m_gpu_simulation YES

    **************************************************
    Terminating @ localhost.localdomain on Thu Nov 13 15:34:03 2025
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Thread 0x7fffb57ff640 (LWP 997013) exited]
    [Thread 0x7fffbd3ff640 (LWP 996988) exited]
    [Thread 0x7ffff7ecc4c0 (LWP 995736) exited]
    [Thread 0x7fffb4ffe640 (LWP 997014) exited]
    [New process 995736]
    [Inferior 1 (process 995736) exited normally]
    Missing separate debuginfos, use: dnf debuginfo-install libnvidia-gpucomp-580.82.07-1.el9.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64
    (gdb) 



Testing in sysrap/tests/SPM_test.sh
------------------------------------



CAUTION : JUNOSW PMT HIT MERGING NOT DONE BY DEFAULT, NEEDS --pmtsd-merge-twindow 1.0
---------------------------------------------------------------------------------------- 


::

    0394         grp_pmt_op.add_argument("--pmtsd-merge-twindow", type=float, default=0.0,
     395                             help=mh("Merge the hits in a PMT within the time window (ns)"))



    2085         if args.pmtsd_merge_twindow>0:
    2086             pmtsdmgr = sim_conf.pmtsd_mgr()
    2087             pmtsdmgr.property("EnableMergeHit").set(True)
    2088             pmtsdmgr.property("MergeTimeWindow").set(args.pmtsd_merge_twindow)
    2089         # pmt hit type
    2090         pmtsdmgr = sim_conf.pmtsd_mgr()
    2091         pmtsdmgr.property("HitType").set(args.pmt_hit_type)
    2092         pmtsdmgr.property("DisableSD").set(args.pmt_disable_process)
    2093 


OJ : how is the m_merge_flag:true without --pmtsd-merge-twindow 1.0 ?
----------------------------------------------------------------------

::

   NORUN=1 TEST=hit2 ojet


::

    gdb) bt
    #0  PMTHitMerger::PMTHitMerger (this=0xa6078a0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:4
    #1  0x00007fffbd4f9745 in PMTSDMgr::getSD (this=0x6596610) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:95
    #2  0x00007fffbdd606a4 in LSExpDetectorConstruction::getPMTSD (this=0xa263c70, sd_name="PMTSDMgr") at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:1148
    #3  0x00007fffbdd5a186 in LSExpDetectorConstruction::Construct (this=0xa263c70) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:259
    #4  0x00007fffc67ca92e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #5  0x00007fffc67caafc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #6  0x00007fffd485eb1b in DetSimAlg::initialize (this=0x661afe0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80





doMerge
----------

::

    (gdb) bt
    #0  PMTHitMerger::doMerge (this=0xa658ab0, pmtid=5584, hittime=136.99800109863281) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    #1  0x00007fffbd574d39 in junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits (this=0xa671710, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:372
    #2  0x00007fffbd573f0c in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xa671710, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:245
    #3  0x00007fffbd573bc2 in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xa671710, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:211
    #4  0x00007fffbd56430f in junoSD_PMT_v2::EndOfEvent (this=0x66b0080, HCE=0xc22e34f0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1129




    (gdb) p m_merge_flag
    $1 = true
    (gdb) list
    29	
    30	    if (pmt != m_PMThit.end()) {
    31	
    32	      int time1 = static_cast<int>(hittime/m_time_window);
    33	
    34	      std::vector<junoHit_PMT*>::iterator it = pmt->second.begin();
    35	
    36	      for ( ; it != pmt->second.end(); ++it) {
    37	
    38	 	// compare the time 
    (gdb) p m_time_window
    $2 = 1000
    (gdb) 



    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=3790, hittime=177.49359130859375) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=1411, hittime=292.21481323242188) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=15511, hittime=108.43733215332031) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=12307, hittime=159.00102233886719) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=14399, hittime=107.41964721679688) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=2048, hittime=133.56716918945312) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=5522, hittime=106.8721923828125) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1, PMTHitMerger::doMerge (this=0xa658ab0, pmtid=17378, hittime=104.22635650634766) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:24
    24	  if (not m_merge_flag) return false;
    (gdb) 






Does the timewindow config need to be passed across ?
-------------------------------------------------------

jcv PMTHitMerger::

  3 using namespace CLHEP;
  4 PMTHitMerger::PMTHitMerger() {
  5   hitCollection = 0;
  6   hitCollection_muon = 0;
  7   m_merge_flag = false;
  8   m_time_window = 1.0; // 1ns



::

    019 PMTSDMgr::PMTSDMgr(const std::string& name)
     20     : ToolBase(name)
     21 {
     22     m_merge_flag = false;
     23     m_time_window = 1000*ns;


     24 
     25     declProp("EnableMergeHit", m_merge_flag);
     26     declProp("MergeTimeWindow", m_time_window);
     27     // XXX need to switch.
     28     declProp("PMTSD", m_pmt_sd="junoSD_PMT_v2");
     29     // declProp("PMTSD", m_pmt_sd="junoSD_PMT");
     30     declProp("CollEffiMode", m_ce_mode="None");
     31 
     32     declProp("HitType", m_hit_type=1);
     33 
    ...
    109         sd->setCEFunc(m_ce_func, m_ce_func_params);
    110         sd->setMergeFlag(m_merge_flag);
    111         sd->setMergeWindows(m_time_window);
    112 
    113         sd->setMerger(pmthitmerger);
    114         sd->setMergerAlt(pmthitmergerAlt);
    115 
    116         sd->setPMTParamSvc(m_pmt_param_svc);
    117         sd->setPMTSimParamSvc(m_pmt_sim_param_svc);
    118         sd->setHitType(m_hit_type);
    119         //use pmt sim svc
    120         sd->setUsePmtSimSvc(m_use_pmtsimsvc);
    121         // configure the merger
    122         pmthitmerger->setMergeFlag(m_merge_flag);
    123         pmthitmerger->setTimeWindow(m_time_window);
    124 
    125         pmthitmergerAlt->setMergeFlag(m_merge_flag);
    126         pmthitmergerAlt->setTimeWindow(m_time_window);





Where to kick off GPU hit merging from ?
-------------------------------------------

* could add "hitlitemerged" [HMM within OJ could do CPU merging only for NormHit pmt-hit-type 1] 


"TEST=hit2 ojet" after oo, ljbb : something didnt get the hitlite memo ?
---------------------------------------------------------------------------

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2025-11-12 21:20:05.740 ERROR [3963838] [SEvt::addGenstep@2273]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this  

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    (gdb) bt
    #0  0x00007fffc1129e62 in std::vector<long, std::allocator<long> >::size (this=0x18) at /usr/include/c++/11/bits/stl_vector.h:919
    #1  0x00007fffbdb7fc26 in NP::has_shape (this=0x0, ni=0, nj=4, nk=-1, nl=-1, nm=-1, no=-1) at /data1/blyth/local/opticks_Debug/include/SysRap/NP.hh:2124
    #2  0x00007fffbd58d7ed in junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits (this=0xa6215f0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:329
    #3  0x00007fffbd58cd08 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xa6215f0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:229
    #4  0x00007fffbd58c9be in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xa6215f0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:195
    #5  0x00007fffbd57d31f in junoSD_PMT_v2::EndOfEvent (this=0xa220b60, HCE=0xd15de770) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1129
    #6  0x00007fffc4d720fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #7  0x00007fffc672ea80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #8  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x66a9890, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #9  0x00007fffd485ed3e in DetSimAlg::execute (this=0x660ed80) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #10 0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so

    (gdb) f 2
    #2  0x00007fffbd58d7ed in junoSD_PMT_v2_Opticks::EndOfEvent_CollectMuonHits (this=0xa6215f0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:329
    329	    bool expected_shape = hitlite->has_shape(num_hit, 4) ;
    (gdb) p hitlite
    $1 = (const NP *) 0x0
    (gdb) p SEvt::Get_EGPU()
    $2 = (SEvt *) 0xc5b6bc0
    (gdb) p SEvt::Get_EGPU()->desc()
    $3 = "sevent::descMax    \n evt.max_curand    1", '0' <repeats 12 times>, "\n evt.max_slot      262000000\n evt.max_genstep   10000000\n evt.max_photon    1", '0' <repeats 12 times>, "\n evt.max_simtrace  1", '0' <repeats 12 times>, "\n evt.max_bounce       31"...
    (gdb) p SEvt::Get_EGPU()->getPhoton()
    $4 = (const NP *) 0x0
    (gdb) p SEventConfig::ModeLite()
    $5 = 1
    (gdb) p SEventConfig::PhotonComp()
    $6 = 4194304
    (gdb) p SEvt::Count()
    $7 = 1
    (gdb) p SEventConfig::IntegrationMode()
    $8 = 1
    (gdb) p SEvt::Get_EGPU()->topfold
    $9 = (NPFold *) 0xc6d84b0
    (gdb) p SEventConfig::HitCompNameOne()
    $10 = 0x7fffbe8c168f "hitlite"
    (gdb) p SEventConfig::PhotonCompNameOne()
    $11 = 0x7fffbe8c1684 "photonlite"
    (gdb) p SEvt::Get_EGPU()->topfold->desc()
    $12 = "[NPFold::desc\nNPFold::desc_subfold\n tot_items 1\n folds 1\n paths 1\n  0 [/]  stamp:0\nNPFold::desc(0) \n[NPFold::desc_(0)\n subfold 0 ff 0 kk 1 aa 1\n[NP::DescMetaKVS only_with_stamp : NO \n]NP::DescMetaKVS\n"...
    (gdb) p SEvt::Get_EGPU()->topfold->kk
    $13 = std::vector of length 1, capacity 1 = {"hit.npy"}

    (gdb) p SEvt::Get_EGPU()->topfold->get("hit")
    $14 = (const NP *) 0xd18d6310
    (gdb) p SEvt::Get_EGPU()->topfold->get("hit")->sstr()
    $15 = "(1614, 4, 4, )"
    (gdb) 

    (gdb) p m_hit_type
    $16 = 2

    (gdb) p SCOMP_HIT
    $17 = SCOMP_HIT
    (gdb) p (int)SCOMP_HIT
    $18 = 256
    (gdb) p (int)SCOMP_HITLITE
    $19 = 8388608
    (gdb) p (int)SCOMP_PHOTONLITE
    $20 = 4194304
    (gdb) p SEventConfig::HitComp()
    $21 = 8388608
    (gdb) 

    (gdb) p SEvt::Get_EGPU()->descComponent()
    $22 = "SEvt::DescComponent\n SEventConfig::DescGatherComp hit\n\n SEventConfig::DescSaveComp \n", ' ' <repeats 17 times>, "hit       (1614, 4, 4, ) \n", ' ' <repeats 16 times>, "seed", ' ' <repeats 20 times>, "- \n", ' ' <repeats 13 times>, "genstep          "...
    (gdb) p SEvt::GetNumHit_EGPU() 
    $23 = 0


Consistency check not so easy : because ordering is unclear
---------------------------------------------------------------

::

    2025-11-13 10:36:13.767 FATAL [2517110] [junoSD_PMT_v2_Opticks::Initialize@147]  opticksMode 1 eventID 0 m_hit_type 2 SEventConfig::ModeLite 0 consistent NO 
    python: /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:155: void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent*, G4int): Assertion `consistent' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff7437886 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffbd573728 in junoSD_PMT_v2_Opticks::Initialize (this=0xa6216e0, eventID=0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:155
    #6  0x00007fffbd56193a in junoSD_PMT_v2::Initialize (this=0xa125920, HCE=0xc22927e0) at /home/blyth/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:248
    #7  0x00007fffc4d71cfa in G4SDStructure::Initialize(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #8  0x00007fffc4d6f6bc in G4SDManager::PrepareNewEvent() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #9  0x00007fffc672e289 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65e5580, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffd485ed3e in DetSimAlg::execute (this=0x56e47f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112



::

    (gdb) p mode_lite
    $1 = 0
    (gdb) p m_hit_type
    $2 = 2
    (gdb) p getenv("OPTICKS_MODE_LITE")
    'getenv' has unknown return type; cast the call to its declared return type
    (gdb) p (char*)getenv("OPTICKS_MODE_LITE")
    $3 = 0x68f5752 "1"
    (gdb) p SEventConfig::ModeLite()
    $4 = 0
    (gdb) 



Easy to be early enough from bash::


    BP=SEventConfig::Initialize OPTICKS_MODE_LITE=1 TEST=hit2 ojet

    (gdb) p SEventConfig::IsCompConfigured()
    $1 = false
    (gdb) p SEventConfig::ModeLite()
    $2 = 1
    (gdb) p (char*)getenv("OPTICKS_MODE_LITE")
    $3 = 0x6915d12 "1"
    (gdb) 


Not so easy to be early enough from python::

     BP=SEventConfig::Initialize TEST=hit2 ojet


    (gdb) p SEventConfig::IsCompConfigured()
    $1 = false
    (gdb) p SEventConfig::ModeLite()
    $2 = 0
    (gdb) p (char*)getenv("OPTICKS_MODE_LITE")
    $3 = 0x6906fe2 "1"
    (gdb) 



Try to break on where the statics get initialized::

    BP="SEventConfig::Initialize,_GLOBAL__sub_I_SEventConfig.cc"  OPTICKS_MODE_LITE=1 TEST=hit2 ojet





Likely due to config being too late, after SEvt instanciation
----------------------------------------------------------------

::

    130 #ifdef WITH_G4CXOPTICKS
    131 void junoSD_PMT_v2_Opticks::Initialize(G4HCofThisEvent* /*HCE*/, G4int eventID)
    132 {
    133 
    134     // HMM THIS IS ALMOST CERTAINLY TOO LATE TO BE SETTING CONFIG : IT HAS TO BE BEFORE SEvt INSTANCIATION
    135     m_hit_type = m_jpmt->getHitType();
    136     assert( m_hit_type == 1 || m_hit_type == 2);
    137 
    138     switch(m_hit_type)
    139     {
    140         case 1: SEventConfig::SetModeLite(0) ; break ;
    141         case 2: SEventConfig::SetModeLite(1) ; break ;
    142     }
    143 


How to get m_hit_type earlier ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Could set envvar within the python ?

::

    A[blyth@localhost junosw]$ jgr m_hit_type
    ./Simulation/DetSimV2/PMTSim/PMTSim/junoSD_PMT_v2_Opticks.hh:        int                   m_hit_type ; 
    ./Simulation/DetSimV2/PMTSim/include/PMTSDMgr.hh:    G4int m_hit_type;
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setHitType(int i) { m_hit_type = i; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        int getHitType() { return m_hit_type; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        G4int m_hit_type;
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("HitType", m_hit_type=1);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setHitType(m_hit_type);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    m_hit_type = 1; // 1 for normal, 2 for muon
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        if (m_hit_type == 1) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        } else if (m_hit_type == 2) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:            G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        if (m_hit_type == 1)
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:            G4cout << "FATAL : hitCollectionAlt cannot handle hit type [" << m_hit_type << "]" << G4endl;
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    if (m_hit_type == 1) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:    } else if (m_hit_type == 2) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    m_hit_type(-1),
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        << " m_hit_type " << m_hit_type
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    m_hit_type = m_jpmt->getHitType();
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    assert( m_hit_type == 1 || m_hit_type == 2);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    switch(m_hit_type)
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        << " m_hit_type " << m_hit_type
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    switch(m_hit_type)
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    assert( m_hit_type == 1 );
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        << " m_hit_type " << m_hit_type
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        << " m_hit_type " << m_hit_type
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    assert( m_hit_type == 2 );
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        << " m_hit_type " << m_hit_type
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:    assert( m_hit_type == 1 );
    A[blyth@localhost junosw]$ 





What is needed to add pmt-hit-type 2 
-----------------------------------------

jcv junoHit_PMT_muon junoHit_PMT
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The "junoHit_PMT_muon" is a subset of "junoHit_PMT" so in principal not difficult to support::

     44   private:
     45     G4int pmtID;         // the ID of the PMT the photon hits
     46     G4double time;       // the time when photon hitting PMT
     47     G4int iHitCount;     // the Number of p.e. from a Hit
     48     G4float localtheta;  // the photon local theth
     49     G4float localphi;    // the photon local phi


Its easy to support, but not so easy to fully benefit from the very large
potential for more performance using newly added *hitlite*.




ThreeVector.icc
~~~~~~~~~~~~~~~~~~~~

* https://apc.u-paris.fr/~franco/g4doxy/html/ThreeVector_8icc-source.html

::

    00120 inline double Hep3Vector::theta()       const {
    00121   return dx == 0.0 && dy == 0.0 && dz == 0.0 ? 0.0 : std::atan2(perp(),dz);
    00122 }
    00123 inline double Hep3Vector::phi() const {
    00124   return dx == 0.0 && dy == 0.0 ? 0.0 : std::atan2(dy,dx);
    00125 }


    00160 inline double Hep3Vector::perp2()  const { return dx*dx + dy*dy; }
    00161 inline double Hep3Vector::perp()   const { return std::sqrt(perp2()); }





SEvt::GetNumHit
~~~~~~~~~~~~~~~~

::

    1930 int64_t SEvt::GetNumHit(int idx){                return Exists(idx) ? Get(idx)->getNumHit() : UNDEF ; }
    1931 int64_t SEvt::GetNumHit_EGPU(){  return GetNumHit(EGPU) ; }
    1932 int64_t SEvt::GetNumHit_ECPU(){  return GetNumHit(ECPU) ; }




OJ Integration of hitlite ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~


::

    196 void junoSD_PMT_v2_Opticks::EndOfEvent_Simulate(int eventID )
    197 {
    198     G4CXOpticks* gx = G4CXOpticks::Get() ;
    199 
    200     bool reset_ = false ;
    201     gx->simulate(eventID, reset_ ) ;
    202 
    203     assert( m_merger );
    204 
    205     std::stringstream ss ;
    206     unsigned num_hit = SEvt::GetNumHit_EGPU() ;
    207 
    208     LOG(LEVEL)
    209         << "[ eventID " << eventID
    210         << " " << gx->descSimulate()
    211         << " num_hit " << num_hit
    212         << " m_hit_type " << m_hit_type
    213         ;
    214 
    215     int merged_count(0);
    216     int savehit_count(0);
    217     bool way_enabled = false ;
    218 
    219     U4Hit hit ;
    220     U4HitExtra hit_extra ;
    221     U4HitExtra* hit_extra_ptr = way_enabled ? &hit_extra : nullptr ;
    222     for(int idx=0 ; idx < int(num_hit) ; idx++)
    223     {
    224         U4HitGet::FromEvt_EGPU(hit, idx);
    225         collectHit(&hit, hit_extra_ptr, merged_count, savehit_count );
    226         if(idx < 20 && LEVEL == info) ss << descHit(idx, &hit, hit_extra_ptr ) << std::endl ;
    227     }
    228     LOG_IF(LEVEL, LEVEL == info) << std::endl << ss.str() ;
    229     LOG(LEVEL)
    230         << "]"
    231         << " num_hit " << num_hit
    232         << ( merged_count > 0 ? " MERGED " : "" )
    233         << " merged_count  " << merged_count
    234         << " savehit_count  " << savehit_count
    235         << " m_merged_total " << m_merged_total
    236         << " m_savehit_total " << m_savehit_total
    237         << " m_opticksMode " << m_opticksMode
    238         << " m_hit_type " << m_hit_type
    239         ;
    240 
    241     m_merged_total += merged_count ;




How to support muon hits in Opticks ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* SEventConfig::SetModeLite(1) 



1. junoSD_PMT_v2_Opticks::collectHit needs to branch on hit_type::

    int hit_type = m_jpmt->getHitType();


    289 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    290 {
    291     bool merged = m_merger->getMergeFlag() ? m_merger->doMerge(hit->sensor_identifier, hit->time) : false ;
    292     if(merged)
    293     {
    294         merged_count += 1 ;
    295     }
    296     else
    297     {
    298         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    299         savehit_count += 1 ;
    300         m_merger->saveHit(hit_photon);
    301     }
    302 }

2. need junoSD_PMT_v2_Opticks::convertHit_Lite that returns junoHit_PMT_muon




Where is non-Opticks saveHit ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost junosw]$ jgr saveHit
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh: *                  2. saveHit, if not merge, create new hit and put it into collection
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT* hit);
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool saveHit(junoHit_PMT_muon* hit);
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT* hit_photon) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:PMTHitMerger::saveHit(junoHit_PMT_muon* hit_photon) {
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:        m_pmthitmerger->saveHit(hit_photon);
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:        m_merger->saveHit(hit_photon);



non-Opticks junoSD_PMT_v2::ProcessHits handles hits one by one ? Is there just one merger ? YES
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The single merger is init with normal or muon hit collection, and subsequently
expects to be given only that corresponding type of hit::

    186 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
    187 {
    ...
     218     if (m_pmthitmerger) {
     219         if (m_hit_type == 1) {
     220             m_pmthitmerger->init(hitCollection);
     221         } else if (m_hit_type == 2) {
     222             // TODO
     223             m_pmthitmerger->init(hitCollection_muon);
     224         } else {
     225             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     226         }
     227     }
     228     // make sure the PMT merger exists.
     229     assert(m_pmthitmerger);
     230  


     378 #ifdef WITH_G4CXOPTICKS_EPH
     379 G4bool junoSD_PMT_v2::ProcessHits_(G4Step * step,G4TouchableHistory*)
     380 #else
     381 G4bool junoSD_PMT_v2::ProcessHits(G4Step * step,G4TouchableHistory*)
     382 #endif
     383 {




     515     if (m_pmthitmerger and m_pmthitmerger->getMergeFlag()) {
     516         // == if merged, just return true. That means just update the hit
     517         // NOTE: only the time and count will be update here, the others
     518         //       will not filled.
     519         bool ok = m_pmthitmerger->doMerge(pmtID, hittime);
     520         if (ok) {
     521             m_merge_count += 1 ;
     522 
     523 #ifdef WITH_G4CXOPTICKS_EPH
     524             m_eph = EPH::YMERGE ;
     525 #endif
     526             return true;
     527         }
     528     }
     529    // = save the hit in the collection
     ...
     531     if (m_hit_type == 1) {
     532 
     533        SaveNormHit(pmtID, local_pos, global_pos, hittime, track, edep);
     534 #ifdef WITH_G4CXOPTICKS_EPH
     535        m_eph = EPH::SAVENORM ;
     536 #endif
     537 
     538     } else if (m_hit_type == 2) {
     539         SaveMuonHit(pmtID, local_pos, hittime);
     540 #ifdef WITH_G4CXOPTICKS_EPH
     541         m_eph = EPH::SAVEMUON ;
     542 #endif
     543     }
     544 
     545     return true;
     546 }
     547 



GPU PMTHitMerger idea
~~~~~~~~~~~~~~~~~~~~~~

~/j/CUDA_Thrust_PMTHitMerge/CUDA_Thrust_PMTHitMerge_two_phase_less_memory_cleaner.cu




Where does hit conversion happen
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    Thread 1 "python" hit Breakpoint 2.1, PMTHitMerger::saveHit (this=0xaa6fcc0, hit_photon=0xd1ef2120) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    81	in /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc
    (gdb) bt
    #0  PMTHitMerger::saveHit (this=0xaa6fcc0, hit_photon=0xd1ef2120) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:81
    #1  0x00007fffbd60c3fb in junoSD_PMT_v2_Opticks::collectHit (this=0xaa87530, hit=0x7ffffffedf60, hit_extra=0x0, merged_count=@0x7ffffffee038: 0, savehit_count=@0x7ffffffee034: 1)
        at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:300
    #2  0x00007fffbd60b8d8 in junoSD_PMT_v2_Opticks::EndOfEvent_Simulate (this=0xaa87530, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:219
    #3  0x00007fffbd60b4ca in junoSD_PMT_v2_Opticks::EndOfEvent (this=0xaa87530, eventID=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:175
    #4  0x00007fffbd5fbf1f in junoSD_PMT_v2::EndOfEvent (this=0x9dd8340, HCE=0xd1a084c0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1129
    #5  0x00007fffc4d720fa in G4SDStructure::Terminate(G4HCofThisEvent*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #6  0x00007fffc672ea80 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #7  0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65c6a00, i_event=0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #8  0x00007fffd485ed3e in DetSimAlg::execute (this=0x66be8d0) at /builds/JUNO/offline/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #9  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so

::

    289 void junoSD_PMT_v2_Opticks::collectHit(const U4Hit* hit, const U4HitExtra* hit_extra, int& merged_count, int& savehit_count )
    290 {
    291     bool merged = m_merger->getMergeFlag() ? m_merger->doMerge(hit->sensor_identifier, hit->time) : false ;
    292     if(merged)
    293     {
    294         merged_count += 1 ;
    295     }
    296     else
    297     {
    298         junoHit_PMT* hit_photon = convertHit(hit, hit_extra );
    299         savehit_count += 1 ;
    300         m_merger->saveHit(hit_photon);
    301     }
    302 }






    318 junoHit_PMT* junoSD_PMT_v2_Opticks::convertHit(const U4Hit* hit, const U4HitExtra* hit_extra ) const
    319 {
    320     junoHit_PMT* hit_photon = new junoHit_PMT();
    321 
    322     bool originalOP = !hit->is_reemission ;
    323     double edep = twopi*hbarc / hit->wavelength ;  // TODO:check units match with CPU hits
    324 
    325     hit_photon->SetKineticEnergy(edep);
    326     hit_photon->SetOriginalOP(originalOP);
    327     hit_photon->SetCount(1);
    328 
    329     hit_photon->SetWavelength(hit->wavelength);
    330     hit_photon->SetPMTID(hit->sensor_identifier);
    331     hit_photon->SetWeight(hit->weight);
    332     hit_photon->SetTime(hit->time);
    333 
    334     hit_photon->SetPosition(hit->local_position);
    335     hit_photon->SetTheta(   hit->local_position.theta());
    336     hit_photon->SetPhi(     hit->local_position.phi());
    337     hit_photon->SetMomentum(hit->local_direction);
    338     hit_photon->SetPolarization(hit->local_polarization);
    339 
    340     hit_photon->SetGlobalPosition(hit->global_position);
    341     hit_photon->SetGlobalMomentum(hit->global_direction);
    342     hit_photon->SetGlobalPolarization(hit->global_polarization);
    343 
    344     hit_photon->SetFromCerenkov(hit->is_cerenkov);
    345     hit_photon->SetReemission(hit->is_reemission);
    346 
    347     if(hit_extra)
    348     {
    349         hit_photon->SetProducerID(hit_extra->origin_trackID);
    350         hit_photon->SetOriginalOPStartT(hit_extra->origin_time);
    351         hit_photon->SetBoundaryPosition(hit_extra->boundary_pos);
    352     }
    353     return hit_photon ;
    354 }



pmt hit type branching
~~~~~~~~~~~~~~~~~~~~~~~~~~


::

     450         grp_pmt_op.add_argument("--pmt-hit-type", type=int, default=1, choices=[1,2],
     451                             help=mh("1 for normal hit, 2 for muon"))

    A[blyth@localhost jiabin-simulation-PMTHitMerger-missing-hitcol]$ jgr pmt_hit_type
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        pmtsdmgr.property("HitType").set(args.pmt_hit_type)

    A[blyth@localhost junosw]$ jgr HitType

    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py:        pmtsdmgr.property("HitType").set(args.pmt_hit_type)
    ./Simulation/DetSimV2/DetSimMT/share/run_mt.py:    pmtsdmgr.property("HitType").set(2)

    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    if (m_pmthitmerger->hasNormalHitType()) {
    ./Simulation/DetSimV2/AnalysisCode/src/MuonFastSimVoxel.cc:    } else if (m_pmthitmerger->hasMuonHitType()) {

    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasNormalHitType() { return hitCollection != 0; }
    ./Simulation/DetSimV2/PMTSim/include/PMTHitMerger.hh:    bool hasMuonHitType() { return hitCollection_muon != 0; }
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasNormalHitType()) {
    ./Simulation/DetSimV2/PMTSim/src/PMTHitMerger.cc:  if (not hasMuonHitType()) {

    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        void setHitType(int i) { m_hit_type = i; }
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh:        int getHitType() { return m_hit_type; }

    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:    declProp("HitType", m_hit_type=1);
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc:        sd->setHitType(m_hit_type);
           ## just passes m_hit_type along to junoSD_PMT_v2



jcv junoSD_PMT_v2
~~~~~~~~~~~~~~~~~~~~

m_hit_type:1
    m_pmthitmerger init with (junoHit_PMT_Collection)hitCollection     

m_hit_type:2
    m_pmthitmerger init with (junoHit_PMT_muon_Collection)hitCollection_muon     


::

     186 void junoSD_PMT_v2::Initialize(G4HCofThisEvent *HCE)
     187 {
     188     const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent() ;
     189     m_eventID = event->GetEventID() ;
     190 
     191     m_merge_count = 0 ;
     192     if (m_debug) {
     193         G4cout << "junoSD_PMT_v2::Initialize eventID " << m_eventID << G4endl;
     194     }
     195     hitCollection = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[0]);
     196     hitCollection_muon = new junoHit_PMT_muon_Collection(SensitiveDetectorName,collectionName[1]);
     197     if(m_opticksMode == 3) hitCollectionAlt = new junoHit_PMT_Collection(SensitiveDetectorName,collectionName[2]);
     198 
     ...

     218     if (m_pmthitmerger) {
     219         if (m_hit_type == 1) {
     220             m_pmthitmerger->init(hitCollection);
     221         } else if (m_hit_type == 2) {
     222             // TODO
     223             m_pmthitmerger->init(hitCollection_muon); 
     224         } else {
     225             G4cout << "unknown hit type [" << m_hit_type << "]" << G4endl;
     226         }
     227     }
     228     // make sure the PMT merger exists.
     229     assert(m_pmthitmerger);
     230 
     231     if (m_pmthitmergerAlt && hitCollectionAlt )
     232     {
     233         if (m_hit_type == 1)
     234         {
     235             m_pmthitmergerAlt->init(hitCollectionAlt);
     236         }
     237         else
     238         {
     239             G4cout << "FATAL : hitCollectionAlt cannot handle hit type [" << m_hit_type << "]" << G4endl;
     240             assert(0);
     241         }
     242     }



