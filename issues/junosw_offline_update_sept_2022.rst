junosw_offline_update_sept_2022
==================================


Developing the U4Debug machinery
------------------------------------

u4/tests::

    epsilon:tests blyth$ ./U4Debug.sh 
    Fold : symbol f30 base /tmp/u4debug/ntds3/000 
    Fold : symbol f31 base /tmp/u4debug/ntds3/001 
    f30c     (8, 8) f30s    (47, 8) f30h    (14, 4) 
    f31c     (7, 8) f31s    (51, 8) f31h     (8, 4) 
        
Not the expected labels, probably due to omitted U4::GenPhotonAncestor(&aTrack) in G4Cerenkov_modified::

    In [1]: f30h
    Out[1]: 
    array([[ 0,  0,  0,  1],
           [ 0,  0,  0,  4],
           [ 0,  0,  0,  3],
           [ 0,  0,  0,  3],
           [ 0,  0,  0,  2],
           [ 0,  0,  0,  3],
           [ 0,  0,  0,  7],
           [ 0,  0,  0,  8],
           [ 0,  0,  0,  9],
           [ 0,  0,  0,  8],
           [ 0,  0,  0,  8],
           [ 0,  0,  0, 15],
           [ 0,  0,  0, 13],
           [ 0,  0,  0, 14]], dtype=int32)

    In [2]: f31h
    Out[2]: 
    array([[ 0,  0,  0, 15],
           [ 0,  0,  0, 15],
           [ 0,  0,  0, 19],
           [ 0,  0,  0, 16],
           [ 0,  0,  0, 16],
           [ 0,  0,  0, 19],
           [ 0,  0,  0, 21],
           [ 0,  0,  0, 20]], dtype=int32)


After adding U4::GenPhotonAncestor(&aTrack) to Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc
get more reasonable labels. As the ancestor is getting reset for each genstep::

    epsilon:tests blyth$ ./U4Debug.sh 
    Fold : symbol f30 base /tmp/u4debug/ntds3/000 
    Fold : symbol f31 base /tmp/u4debug/ntds3/001 
    f30c     (8, 8) f30s    (47, 8) f30h    (14, 4) 
    f31c     (7, 8) f31s    (51, 8) f31h     (8, 4) 

    In [1]: f30h
    Out[1]: 
    array([[ 0, 15, 15,  0],
           [ 0, 22, 22,  2],
           [ 0, 10, 10,  1],
           [ 0,  8,  8,  1],
           [ 0,  3,  3,  0],
           [ 0,  2,  2,  1],
           [ 0,  3,  3,  2],
           [ 0, 41, 41,  1],
           [ 0, 36, 36,  2],
           [ 0, 29, 29,  1],
           [ 0, 19, 19,  1],
           [ 0, 26, 26,  4],
           [ 0,  7,  7,  1],
           [ 0,  2,  2,  1]], dtype=int32)

    In [2]: f31h
    Out[2]: 
    array([[ 0, 67, 67,  1],
           [ 0, 28, 28,  1],
           [ 0, 18, 18,  5],
           [ 0, 28, 28,  1],
           [ 0, 10, 10,  1],
           [ 0,  5,  5,  1],
           [ 0,  6,  6,  2],
           [ 0,  0,  0,  1]], dtype=int32)


Note that having reemission generations larger than zero 
does not mean the photon originally came from scint. 
In this case I think there are no photons coming from scint, 
but reemission of initially Cerenkov photons is happening. 

NB this are the labels of just the hits, so should not 
expect to see the same lineage repeated across reemission generations. 

Need to SetOpticksMode to get genstep indices to raise above zero. 
Doing that gives more normal labels::

    epsilon:tests blyth$ ./U4Debug.sh 
    Fold : symbol f30 base /tmp/u4debug/ntds3/000 
    Fold : symbol f31 base /tmp/u4debug/ntds3/001 
    f30c     (8, 8) f30s    (47, 8) f30h    (14, 4) 
    f31c     (7, 8) f31s    (51, 8) f31h     (8, 4) 

    In [1]: f30h
    Out[1]: 
    array([[  0,  15,  15,   0],
           [  1,  22,  56,   2],
           [  1,  10,  44,   1],
           [  1,   8,  42,   1],
           [  1,   3,  37,   0],
           [  1,   2,  36,   1],
           [  2,   3,  60,   2],
           [  3,  41, 102,   1],
           [  3,  36,  97,   2],
           [  3,  29,  90,   1],
           [  3,  19,  80,   1],
           [  4,  26, 157,   4],
           [  5,   7, 174,   1],
           [  6,   2, 195,   1]], dtype=int32)

    ## hits coming from 7 distinct gensteps : I think origins are all Cerenkov

    In [2]: f31h
    Out[2]: 
    array([[  0,  67,  67,   1],
           [  0,  28,  28,   1],
           [  0,  18,  18,   5],
           [  1,  28, 103,   1],
           [  1,  10,  85,   1],
           [  2,   5, 123,   1],
           [  3,   6, 155,   2],
           [  3,   0, 149,   1]], dtype=int32)

    ## hits coming from 4 distinct gensteps : I think origins are all Cerenkov

The debug info identifies exactly which photon from which genstep 
is the originating photon and how many reemission generations are undergone. 
HMM need genstep labels to identify original C or S of the hits.
Added SEvt::SaveGenstepLabels to U4Debug::Save::

    epsilon:tests blyth$ ./U4Debug.sh 
    Fold : symbol f30 base /tmp/u4debug/ntds3/000 
    f30c     (8, 8) f30s    (47, 8) f30h    (14, 4) f30g     (8, 4) 
    Fold : symbol f31 base /tmp/u4debug/ntds3/001 
    f31c     (7, 8) f31s    (51, 8) f31h     (8, 4) f31g     (7, 4) 

    In [1]: f30g
    Out[1]: 
    array([[  0,  34,   0,  18],
           [  1,  23,  34,  18],
           [  2,   4,  57,  18],
           [  3,  70,  61,  18],
           [  4,  36, 131,  18],
           [  5,  26, 167,  18],
           [  6,   4, 193,  18],
           [  7,   1, 197,  18]], dtype=int32)

    In [2]: f31g
    Out[2]: 
    array([[  0,  75,   0,  18],
           [  1,  43,  75,  18],
           [  2,  31, 118,  18],
           [  3,  14, 149,  18],
           [  4,   8, 163,  18],
           [  5,   1, 171,  18],
           [  6,   2, 172,  18]], dtype=int32)


As expected origins of all hits are OpticksGenstep_G4Cerenkov_modified = 18::

     19 enum
     20 {
     21     OpticksGenstep_INVALID                  = 0,
     22     OpticksGenstep_G4Cerenkov_1042          = 1,
     23     OpticksGenstep_G4Scintillation_1042     = 2,
     24     OpticksGenstep_DsG4Cerenkov_r3971       = 3,
     25     OpticksGenstep_DsG4Scintillation_r3971  = 4,
     26     OpticksGenstep_DsG4Scintillation_r4695  = 5,
     27     OpticksGenstep_TORCH                    = 6,
     28     OpticksGenstep_FABRICATED               = 7,
     29     OpticksGenstep_EMITSOURCE               = 8,
     30     OpticksGenstep_NATURAL                  = 9,
     31     OpticksGenstep_MACHINERY                = 10,
     32     OpticksGenstep_G4GUN                    = 11,
     33     OpticksGenstep_PRIMARYSOURCE            = 12,
     34     OpticksGenstep_GENSTEPSOURCE            = 13,
     35     OpticksGenstep_CARRIER                  = 14,
     36     OpticksGenstep_CERENKOV                 = 15,
     37     OpticksGenstep_SCINTILLATION            = 16,
     38     OpticksGenstep_FRAME                    = 17,
     39     OpticksGenstep_G4Cerenkov_modified      = 18,
     40     OpticksGenstep_INPUT_PHOTON             = 19,
     41     OpticksGenstep_NumType                  = 20
     42 };








Need to get changes tucked into branches::

    N[blyth@localhost junosw]$ git s
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
        modified:   Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h
        modified:   Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
        modified:   Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ 


* Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc              Call U4Cerenkov_Debug::EndOfEvent U4Scintillation_Debug::EndOfEvent
* Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc        Using U4Scintillation_Debug
* Simulation/DetSimV2/PhysiSim/src/G4Cerenkov_modified.cc      Using U4Cerenkov_Debug

* Simulation/DetSimV2/PhysiSim/include/DsPhysConsOptical.h     EInt
* Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc        TMP Cerenkov pinning, EInt implementation


Almost all is debug, so tuck under WITH_G4CXOPTICKS_DEBUG 


    

How to control the debug ? Perhaps WITH_G4CXOPTICKS_DEBUG which comes from Opticks:cmake/Modules/FindOpticks.cmake::

     49 find_package(G4CX CONFIG QUIET)
     50 
     51 if(G4CX_FOUND)
     52     #add_compile_definitions(WITH_G4OPTICKS)
     53     add_compile_definitions(WITH_G4CXOPTICKS)
     54     add_compile_definitions(WITH_G4CXOPTICKS_DEBUG)
     55     


U4Cerenkov_Debug
U4Scintillation_Debug
   records cerenkov and scintillation steps, 
   for investigating a lack of gensteps for example 

U4Hit_Debug
   records labels of hits with gs indices


To make the connection between the debug steps and labels ? 
Not so simple because the purposes are different.  
Want to record steps that yield no gensteps in order to 
understand lack of gensteps. 



 










DONE : Fix whacky num_hit SEvt::getNumHit::

    junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    2022-09-29 00:51:15.867 DEBUG [62180] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 1 m_opticksMode 3
    2022-09-29 00:51:15.867 FATAL [62180] [QEvent::setGenstep@151] Must SEvt::AddGenstep before calling QEvent::setGenstep 
    2022-09-29 00:51:15.867 ERROR [62180] [QSim::simulate@296]  QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate 
    2022-09-29 00:51:15.867 ERROR [62180] [SEvt::gather@1413] gather_done already skip gather 
    2022-09-29 00:51:15.867 INFO  [62180] [junoSD_PMT_v2_Opticks::EndOfEvent@190]  eventID 1 num_hit 4294967295 way_enabled 0
    2022-09-29 00:51:15.867 INFO  [62180] [junoSD_PMT_v2_Opticks::EndOfEvent@258] ] num_hit 4294967295 merged_count  0 savehit_count  0 m_merged_total 0 m_savehit_total 0 m_opticksMode 3 LEVEL 5:DEBUG
    2022-09-29 00:51:15.867 INFO  [62180] [junoSD_PMT_v2_Opticks::TerminateEvent@307]  invoking SEvt::Clear as no U4Recorder detected 
    ] junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 8 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully


Cleanup after accepted MR::

    N[blyth@localhost junoenv]$ git diff 
    diff --git a/junoenv-opticks.sh b/junoenv-opticks.sh
    index e50602d..ad07798 100644
    --- a/junoenv-opticks.sh
    +++ b/junoenv-opticks.sh
    @@ -259,10 +259,9 @@ function junoenv-opticks-url {
         if [ "${version:0:1}" == "v" ]; then
             echo https://github.com/simoncblyth/opticks/archive/refs/tags/$version.tar.gz 
         else
    -        case $USER in
    -             blyth) echo git@bitbucket.org:simoncblyth/opticks.git  ;; 
    -                 *) echo https://bitbucket.org/simoncblyth/opticks  ;;
    -        esac
    +        echo https://bitbucket.org/simoncblyth/opticks 
    +        #echo git@bitbucket.org:simoncblyth/opticks.git 
    +        # access from IHEP to bitbucket.org over ssh has become unreliable since Aug 2022
         fi 
         return 0 
     }
    N[blyth@localhost junoenv]$ git s
    On branch blyth-update-junoenv-opticks-for-CMake
    Your branch is up to date with 'origin/blyth-update-junoenv-opticks-for-CMake'.

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   junoenv-opticks.sh

    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ git checkout . 
    Updated 1 path from the index
    N[blyth@localhost junoenv]$ git s
    On branch blyth-update-junoenv-opticks-for-CMake
    Your branch is up to date with 'origin/blyth-update-junoenv-opticks-for-CMake'.

    nothing to commit, working tree clean
    N[blyth@localhost junoenv]$ git checkout main
    Switched to branch 'main'
    Your branch is up to date with 'origin/main'.
    N[blyth@localhost junoenv]$ git branch 
      blyth-update-junoenv-opticks-for-CMake
    * main
    N[blyth@localhost junoenv]$ git branch -d blyth-update-junoenv-opticks-for-CMake
    warning: deleting branch 'blyth-update-junoenv-opticks-for-CMake' that has been merged to
             'refs/remotes/origin/blyth-update-junoenv-opticks-for-CMake', but not yet merged to HEAD.
    Deleted branch blyth-update-junoenv-opticks-for-CMake (was 3fbca14).
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ 





::


+        echo https://bitbucket.org/simoncblyth/opticks 
+        #echo git@bitbucket.org:simoncblyth/opticks.git 
+        # access from IHEP to bitbucket.org over ssh has become unreliable since Aug 2022


    N[blyth@localhost opticks]$ git remote -v
    origin	git@bitbucket.org:simoncblyth/opticks.git (fetch)
    origin	git@bitbucket.org:simoncblyth/opticks.git (push)
    N[blyth@localhost opticks]$ git remote set-url origin https://bitbucket.org/simoncblyth/opticks 
    N[blyth@localhost opticks]$ git remote -v
    origin	https://bitbucket.org/simoncblyth/opticks (fetch)
    origin	https://bitbucket.org/simoncblyth/opticks (push)
    N[blyth@localhost opticks]$ 



::

    N[blyth@localhost PhysiSim]$ mkdir /tmp/ntds3
    N[blyth@localhost PhysiSim]$ mkdir /tmp/ntds0
    N[blyth@localhost PhysiSim]$ export DsG4Scintillation_Debug_SaveDir=/tmp/ntds3



Try using *DsG4Scintillation_Debug* to compare ntds3 and ntds0::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize
    2022-09-28 01:04:45.016 DEBUG [17812] [junoSD_PMT_v2_Opticks::Initialize@119]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    [ junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    2022-09-28 01:04:45.020 DEBUG [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 0 m_opticksMode 3
    2022-09-28 01:04:45.021 FATAL [17812] [QEvent::setGenstep@151] Must SEvt::AddGenstep before calling QEvent::setGenstep 
    2022-09-28 01:04:45.021 ERROR [17812] [QSim::simulate@296]  QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate 
    2022-09-28 01:04:45.021 INFO  [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@190]  eventID 0 num_hit 4294967295 way_enabled 0
    2022-09-28 01:04:45.021 INFO  [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@258] ] num_hit 4294967295 merged_count  0 savehit_count  0 m_merged_total 0 m_savehit_total 0 m_opticksMode 3 LEVEL 5:DEBUG
    2022-09-28 01:04:45.021 INFO  [17812] [junoSD_PMT_v2_Opticks::TerminateEvent@307]  invoking SEvt::Clear as no U4Recorder detected 
    ] junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 0 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize
    2022-09-28 01:04:45.026 DEBUG [17812] [junoSD_PMT_v2_Opticks::Initialize@119]  eventID 1 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 LEVEL 5:DEBUG
    Begin of Event --> 1
    [ junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    2022-09-28 01:04:45.026 DEBUG [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 1 m_opticksMode 3
    2022-09-28 01:04:45.026 FATAL [17812] [QEvent::setGenstep@151] Must SEvt::AddGenstep before calling QEvent::setGenstep 
    2022-09-28 01:04:45.026 ERROR [17812] [QSim::simulate@296]  QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate 
    2022-09-28 01:04:45.026 ERROR [17812] [SEvt::gather@1413] gather_done already skip gather 
    2022-09-28 01:04:45.026 INFO  [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@190]  eventID 1 num_hit 4294967295 way_enabled 0
    2022-09-28 01:04:45.026 INFO  [17812] [junoSD_PMT_v2_Opticks::EndOfEvent@258] ] num_hit 4294967295 merged_count  0 savehit_count  0 m_merged_total 0 m_savehit_total 0 m_opticksMode 3 LEVEL 5:DEBUG
    2022-09-28 01:04:45.026 INFO  [17812] [junoSD_PMT_v2_Opticks::TerminateEvent@307]  invoking SEvt::Clear as no U4Recorder detected 
    ] junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    junoSD_PMT_v2::EndOfEvent m_opticksMode 3 hitCollection 0 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 2           7.07200        3.53600      3.12600      
    DetSimAlg                2           16.71300       8.35650      4.29350      
    Sum of junotoptask       2           23.92400       11.96200     7.48100      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::finalizeOpticks m_opticksMode 3 WITH_G4CXOPTICKS 







Supect G4OpticksAnaMgr no longer needed::

    N[blyth@localhost junoenv]$ cd /data/blyth/junotop/junosw/Simulation/DetSimV2/AnalysisCode/src/
    N[blyth@localhost src]$ vi G4OpticksAnaMgr.cc 
     


::

    N[blyth@localhost PhysiSim]$ DsG4Scintillation_verboseLevel=1 ntds3

    junoSD_PMT_v2::Initialize
    2022-09-27 23:02:04.010 DEBUG [458322] [junoSD_PMT_v2_Opticks::Initialize@119]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 LEVEL 5:DEBUG
    Begin of Event --> 0
     TotalEnergyDeposit 1.756e-05 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 1.32622e-07
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 8.99e-06 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 9.48931e-08
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 1.756e-05 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 1.32622e-07
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 1.361e-05 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 1.16757e-07
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 8.99e-06 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 9.48931e-08
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 0.00029101 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 7.01747e-07
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 1.756e-05 material LS
     MaterialPropertyVectors: Fast_Intensity 0x56f1690 Slow_Intensity 0x56f0c20 Reemission_Prob 0x56fb510
     Generated 0 scint photons. mean(scint photons) = 1.32622e-07
     set scint photon weight to 1 after multiplying original weight by fPhotonWeight 1 NumTracks = 0
     TotalEnergyDeposit 1.756e-05 material LS
    TotalEnergyDeposit 0 material LS
    [ junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    2022-09-27 23:02:04.015 DEBUG [458322] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 0 m_opticksMode 3
    2022-09-27 23:02:04.016 FATAL [458322] [QEvent::setGenstep@151] Must SEvt::AddGenstep before calling QEvent::setGenstep 
    2022-09-27 23:02:04.016 ERROR [458322] [QSim::simulate@296]  QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate 
    python: /data/blyth/junotop/opticks/qudarap/QEvent.cc:356: void QEvent::gatherPhoton(NP*) const: Assertion `p->has_shape(evt->num_photon, 4, 4)' failed.

    Program received signal SIGABRT, Aborted.
    0x00007ffff696e387 in raise () from /lib64/libc.so.6

    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd14c8bbb in QEvent::gatherPhoton (this=0x165f30de0, p=0x1fb972e00) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:356
    #5  0x00007fffd14c8d68 in QEvent::gatherPhoton (this=0x165f30de0) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:364
    #6  0x00007fffd14caf75 in QEvent::gatherComponent_ (this=0x165f30de0, comp=4) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:579
    #7  0x00007fffd14cacfa in QEvent::gatherComponent (this=0x165f30de0, comp=4) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:566
    #8  0x00007fffd10f44e2 in SEvt::gather (this=0x1653dc3b0) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1423
    #9  0x00007fffd454e59f in G4CXOpticks::simulate (this=0x718fa80) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:335
    #10 0x00007fffcedc031a in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5949020) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:185
    #11 0x00007fffcedbe612 in junoSD_PMT_v2::EndOfEvent (this=0x5948820, HCE=0x2b93950) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1094
    #12 0x00007fffdd61bc95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #13 0x00007fffdf7268cd in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #14 0x00007fffd020345d in G4SvcRunManager::SimulateEvent (this=0x90ef70, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29


    #50 0x000000000040065e in _start ()
    (gdb) f 4
    #4  0x00007fffd14c8bbb in QEvent::gatherPhoton (this=0x165f30de0, p=0x1fb972e00) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:356
    356	    assert( p->has_shape(evt->num_photon, 4, 4) ); 
    (gdb) p evt->num_photon
    $1 = 0
    (gdb) p p->sstr()
    $2 = {static npos = 18446744073709551615, _M_dataplus = {<std::allocator<char>> = {<__gnu_cxx::new_allocator<char>> = {<No data fields>}, <No data fields>}, _M_p = 0x7fffffff0360 "(4, 4, )"}, 
      _M_string_length = 8, {_M_local_buf = "(4, 4, )\000:\233\366\377\177\000", _M_allocated_capacity = 2963417157199475752}}
    (gdb) 

::

    562 NP* QEvent::gatherComponent(unsigned comp) const
    563 {
    564     LOG(LEVEL) << "[ comp " << comp ;
    565     unsigned mask = SEventConfig::CompMask();
    566     bool proceed = (mask & comp) != 0 ;
    567     NP* a = proceed ? gatherComponent_(comp) : nullptr ;
    568     LOG(LEVEL) << "[ comp " << comp << " proceed " << proceed << " a " <<  a ;
    569     return a ;
    570 }
    571 NP* QEvent::gatherComponent_(unsigned comp) const
    572 {
    573     NP* a = nullptr ;
    574     switch(comp)
    575     {
    576         case SCOMP_GENSTEP:   a = getGenstep()     ; break ;
    577         case SCOMP_DOMAIN:    a = gatherDomain()      ; break ;
    578         case SCOMP_INPHOTON:  a = getInputPhoton() ; break ;
    579 
    580         case SCOMP_PHOTON:    a = gatherPhoton()   ; break ;
    581         case SCOMP_RECORD:    a = gatherRecord()   ; break ;
    582         case SCOMP_REC:       a = gatherRec()      ; break ;
    583         case SCOMP_SEQ:       a = gatherSeq()      ; break ;
    584         case SCOMP_PRD:       a = gatherPrd()      ; break ;
    585         case SCOMP_SEED:      a = gatherSeed()     ; break ;

    362 NP* QEvent::gatherPhoton() const
    363 {
    364     NP* p = NP::Make<float>( evt->num_photon, 4, 4);
    365     gatherPhoton(p);
    366     return p ;
    367 }
    368 







g4-cls G4VProcess::

    361  public: // with description
    362    void  SetVerboseLevel(G4int value);
    363    G4int GetVerboseLevel() const;
    364    // set/get controle flag for output message
    365    //  0: Silent
    366    //  1: Warning message
    367    //  2: More
    368 
    369 
    370  protected:
    371    G4int verboseLevel;
    372    // controle flag for output message
    373 



BP=DsG4Scintillation::PostStepDoIt ntds3 looks like NumTracks is coming up zero at lot::

    (gdb) c
    Continuing.

    Breakpoint 11, DsG4Scintillation::PostStepDoIt (this=0x1697a7950, aTrack=..., aStep=...) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:437
    437	        G4double MeanNumberOfTracks= MeanNumberOfPhotons/fPhotonWeight; 
    (gdb) p MeanNumberOfPhotons
    $7 = 7.0174652758266295e-07
    (gdb) 

     459     // G4cerr<<"Scint weight is "<<weight<<G4endl;
     460     if (NumTracks <= 0) {
     461         // return unchanged particle and no secondaries 
     462         aParticleChange.SetNumberOfSecondaries(0);
     463         return G4VRestDiscreteProcess::PostStepDoIt(aTrack, aStep);
     464     }
     465 

    (gdb) b 462
    Breakpoint 13 at 0x7fffd0949922: file /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc, line 462.
    (gdb) c
    Continuing.

    Breakpoint 13, DsG4Scintillation::PostStepDoIt (this=0x1697a7950, aTrack=..., aStep=...) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:462
    462	        aParticleChange.SetNumberOfSecondaries(0);
    (gdb) 





Not getting any gensteps::

    ntds3
    ...

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize
    2022-09-27 21:51:06.243 DEBUG [456601] [junoSD_PMT_v2_Opticks::Initialize@119]  eventID 0 wavelength (null) tool 0 input_photons 0 input_photon_repeat 0 LEVEL 5:DEBUG
    Begin of Event --> 0
    [ junoSD_PMT_v2::EndOfEvent m_opticksMode  3
    2022-09-27 21:51:06.247 DEBUG [456601] [junoSD_PMT_v2_Opticks::EndOfEvent@169] [ eventID 0 m_opticksMode 3
    2022-09-27 21:51:06.247 FATAL [456601] [QEvent::setGenstep@151] Must SEvt::AddGenstep before calling QEvent::setGenstep 
    2022-09-27 21:51:06.247 ERROR [456601] [QSim::simulate@296]  QEvent::setGenstep ERROR : have event but no gensteps collected : will skip cx.simulate 
    python: /data/blyth/junotop/opticks/qudarap/QEvent.cc:356: void QEvent::gatherPhoton(NP*) const: Assertion `p->has_shape(evt->num_photon, 4, 4)' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff696e387 in raise () from /lib64/libc.so.6
    #1  0x00007ffff696fa78 in abort () from /lib64/libc.so.6
    #2  0x00007ffff69671a6 in __assert_fail_base () from /lib64/libc.so.6
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd14c8bbb in QEvent::gatherPhoton (this=0x165f41f20, p=0x1fb970ad0) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:356
    #5  0x00007fffd14c8d68 in QEvent::gatherPhoton (this=0x165f41f20) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:364
    #6  0x00007fffd14caf75 in QEvent::gatherComponent_ (this=0x165f41f20, comp=4) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:579
    #7  0x00007fffd14cacfa in QEvent::gatherComponent (this=0x165f41f20, comp=4) at /data/blyth/junotop/opticks/qudarap/QEvent.cc:566
    #8  0x00007fffd10f44e2 in SEvt::gather (this=0x1653db940) at /data/blyth/junotop/opticks/sysrap/SEvt.cc:1423
    #9  0x00007fffd454e59f in G4CXOpticks::simulate (this=0x718f9c0) at /data/blyth/junotop/opticks/g4cx/G4CXOpticks.cc:335
    #10 0x00007fffcedd731a in junoSD_PMT_v2_Opticks::EndOfEvent (this=0x5948df0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc:185
    #11 0x00007fffcedd5612 in junoSD_PMT_v2::EndOfEvent (this=0x59485f0, HCE=0x2b93720) at /data/blyth/junotop/junosw/Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc:1094
    #12 0x00007fffdd61bc95 in G4SDStructure::Terminate(G4HCofThisEvent*) [clone .localalias.78] () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #13 0x00007fffdf7268cd in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #14 0x00007fffd021a45d in G4SvcRunManager::SimulateEvent (this=0x90ee50, i_event=0) at /data/blyth/junotop/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #15 0x00007fffd0447e9b in DetSimAlg::execute (this=0xaf5800) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #16 0x00007fffee52384a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007fffee528855 in TaskWatchDog::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007fffee523574 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #19 0x00007fffee9da7a3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, b






junoenv opticks update for CMake::

    N[blyth@localhost junoenv]$ git s
    # On branch main
    # Changes not staged for commit:
    #   (use "git add <file>..." to update what will be committed)
    #   (use "git checkout -- <file>..." to discard changes in working directory)
    #
    #	modified:   junoenv-opticks.sh
    #
    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junoenv]$ git checkout -b blyth-update-junoenv-opticks-for-CMake
    M	junoenv-opticks.sh
    Switched to a new branch 'blyth-update-junoenv-opticks-for-CMake'
    N[blyth@localhost junoenv]$ git add . 
    N[blyth@localhost junoenv]$ git commit -m "WIP: #3 update junoenv opticks for CMake based junosw"
    [blyth-update-junoenv-opticks-for-CMake 3fbca14] WIP: #3 update junoenv opticks for CMake based junosw
     1 file changed, 76 insertions(+), 25 deletions(-)
    N[blyth@localhost junoenv]$ git push 
    fatal: The current branch blyth-update-junoenv-opticks-for-CMake has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-update-junoenv-opticks-for-CMake

    N[blyth@localhost junoenv]$ git push --set-upstream origin blyth-update-junoenv-opticks-for-CMake
    Counting objects: 5, done.
    Delta compression using up to 48 threads.
    Compressing objects: 100% (3/3), done.
    Writing objects: 100% (3/3), 1.37 KiB | 0 bytes/s, done.
    Total 3 (delta 2), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-update-junoenv-opticks-for-CMake, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junoenv/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-update-junoenv-opticks-for-CMake
    remote: 
    To git@code.ihep.ac.cn:JUNO/offline/junoenv.git
     * [new branch]      blyth-update-junoenv-opticks-for-CMake -> blyth-update-junoenv-opticks-for-CMake
    Branch blyth-update-junoenv-opticks-for-CMake set up to track remote branch blyth-update-junoenv-opticks-for-CMake from origin.
    N[blyth@localhost junoenv]$ 





::

    epsilon:junosw blyth$ find . -name CMakeLists.txt -exec grep -H Opticks {} \;
    ./Simulation/GenTools/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}> 
    ./Simulation/DetSimV2/PhysiSim/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>
    ./Simulation/DetSimV2/PMTSim/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>  
    ./Simulation/DetSimV2/DetSimOptions/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>
    ./Simulation/DetSimV2/AnalysisCode/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}>
    ./Generator/GenGenie/CMakeLists.txt:        $<$<BOOL:${Opticks_FOUND}>:${Opticks_TARGET}> 


cmake/Modules/FindOpticks.cmake::

     48 #find_package(G4OK CONFIG QUIET)
     49 find_package(G4CX CONFIG QUIET)
     50 
     51 if(G4CX_FOUND)
     52     #add_compile_definitions(WITH_G4OPTICKS)
     53     add_compile_definitions(WITH_G4CXOPTICKS)
     54 
     55     if(Opticks_VERBOSE)
     56         message(STATUS "${Opticks_MODULE} : PLog_INCLUDE_DIR :${PLog_INCLUDE_DIR} ")
     57     endif()
     58     include_directories(${PLog_INCLUDE_DIR})  ## WHY NOT AUTOMATIC ? Maybe because plog is header only ?
     59 
     60     set(Opticks_TARGET "Opticks::G4CX")
     61     set(Opticks_FOUND "YES")
     62 
     63 else()
     64     set(Opticks_FOUND "NO")
     65 endif()
     66 



Same again after jx-offline-build so the mechanism to switch on WITH_G4CXOPTICKS cannot be working ?

But ntds3 still fails::

    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:PMTSimParamSvc.init_file  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    Detaching after fork from child process 450370.
    junotoptask:PMTSimParamSvc.init_file_SPMT  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
     m_all_pmtID.size = 45612
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 3 **NOT** WITH_G4CXOPTICKS or WITH_G4OPTICKS 
    junotoptask:DetSim0Svc.initializeOpticks ERROR:  FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS or WITH_G4OPTICKS  
    python: /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:315: bool DetSim0Svc::initializeOpticks(): Assertion `0' failed.




Seems to work::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/junosw/InstallArea/lib64/
    total 274664
       16 drwxrwxr-x. 3 blyth blyth    12288 Sep 27 20:42 .
     5108 -rwxr-xr-x. 1 blyth blyth  5226832 Sep 27 20:42 libDetSimOptions.so
    12868 -rwxr-xr-x. 1 blyth blyth 13174744 Sep 27 20:42 libAnalysisCode.so
    12420 -rwxr-xr-x. 1 blyth blyth 12715296 Sep 27 20:42 libPMTSim.so
     9640 -rwxr-xr-x. 1 blyth blyth  9868208 Sep 27 20:42 libGenTools.so
     7628 -rwxr-xr-x. 1 blyth blyth  7809344 Sep 27 20:42 libPhysiSim.so
        0 drwxrwxr-x. 6 blyth blyth       92 Sep 27 19:39 ..
     2948 -rwxr-xr-x. 1 blyth blyth  3014712 Sep 27 19:39 libDetSimMTUtil.so
     1024 -rwxr-xr-x. 1 blyth blyth  1046176 Sep 27 19:39 libSPMTCalibAlg.so
      992 -rwxr-xr-x. 1 blyth blyth  1012888 Sep 27 19:39 libWpPMTCalibAlg.so
     1348 -rwxr-xr-x. 1 blyth blyth  1378376 Sep 27 19:38 libOPSimulator.so
    11956 -rwxr-xr-x. 1 blyth blyth 12239168 Sep 27 19:38 libElecSimAlg.so



Need to update the touchbuild::

    N[blyth@localhost junosw]$ find . -type f -exec grep -l OPTICKS {} \;
    ./Doc/oum/source/releasenotes/J22.1.0.md
    ./Examples/Tutorial/python/Tutorial/JUNODetSimModule.py
    ./Simulation/DetSimV2/AnalysisCode/include/G4OpticksAnaMgr.hh
    ./Simulation/DetSimV2/AnalysisCode/src/G4OpticksAnaMgr.cc
    ./Simulation/DetSimV2/DetSimMTUtil/src/DetFactorySvc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc
    ./Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc
    ./Simulation/DetSimV2/PMTSim/include/PMTEfficiencyCheck.hh
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2.hh
    ./Simulation/DetSimV2/PMTSim/include/junoSD_PMT_v2_Opticks.hh
    ./Simulation/DetSimV2/PMTSim/src/PMTEfficiencyCheck.cc
    ./Simulation/DetSimV2/PMTSim/src/PMTSDMgr.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2.cc
    ./Simulation/DetSimV2/PMTSim/src/junoSD_PMT_v2_Opticks.cc
    ./Simulation/DetSimV2/PhysiSim/include/DsG4Scintillation.h
    ./Simulation/DetSimV2/PhysiSim/include/LocalG4Cerenkov1042.hh
    ./Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc
    ./Simulation/DetSimV2/PhysiSim/src/DsPhysConsOptical.cc
    ./Simulation/DetSimV2/PhysiSim/src/LocalG4Cerenkov1042.cc
    ./Simulation/GenTools/GenTools/GtOpticksTool.h
    ./Simulation/GenTools/src/GtOpticksTool.cc
    ./cmake/JUNODependencies.cmake
    ./build/python/Tutorial/JUNODetSimModule.py
    ./build/Simulation/GenTools/CMakeFiles/GenTools.dir/src/GtOpticksTool.cc.o
    ./build/Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/src/junoSD_PMT_v2.cc.o
    ./build/Simulation/DetSimV2/PhysiSim/CMakeFiles/PhysiSim.dir/src/DsPhysConsOptical.cc.o
    ./build/Simulation/DetSimV2/DetSimOptions/CMakeFiles/DetSimOptions.dir/src/DetSim0Svc.cc.o
    ./build/Simulation/DetSimV2/DetSimMTUtil/CMakeFiles/DetSimMTUtil.dir/src/DetFactorySvc.cc.o
    ./build/lib/libPhysiSim.so
    ./build/lib/libGenTools.so
    ./build/lib/libPMTSim.so
    ./build/lib/libDetSimOptions.so
    ./build/lib/libDetSimMTUtil.so
    ./InstallArea/include/GenTools/GtOpticksTool.h
    ./InstallArea/lib64/libGenTools.so
    ./InstallArea/lib64/libPMTSim.so
    ./InstallArea/lib64/libPhysiSim.so
    ./InstallArea/lib64/libDetSimOptions.so
    ./InstallArea/lib64/libDetSimMTUtil.so
    ./InstallArea/lib64/cmake/junosw/JUNODependencies.cmake
    ./InstallArea/python/Tutorial/JUNODetSimModule.py
    ./InstallArea/python/Tutorial/__pycache__/JUNODetSimModule.cpython-38.pyc
    N[blyth@localhost junosw]$ 





ntds3 again, now with debug build::

    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:MCParamsSvc.GetPath  INFO: Optical parameters will be used from: /data/blyth/junotop/data/Simulation/DetSim
    junotoptask:PMTSimParamSvc.init_file  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_LPMT.root
    Detaching after fork from child process 432245.
    junotoptask:PMTSimParamSvc.init_file_SPMT  INFO: Loading parameters from file: /data/blyth/junotop/data/Simulation/SimSvc/PMTSimParamSvc/PMTParam_CD_SPMT.root
     m_all_pmtID.size = 45612
    junotoptask:DetSim0Svc.dumpOpticks  INFO: DetSim0Svc::initializeOpticks m_opticksMode 3 **NOT** WITH_G4CXOPTICKS or WITH_G4OPTICKS 
    junotoptask:DetSim0Svc.initializeOpticks ERROR:  FATAL : non-zero opticksMode **NOT** WITH_G4CXOPTICKS or WITH_G4OPTICKS  
    python: /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:315: bool DetSim0Svc::initializeOpticks(): Assertion `0' failed.

    Program received signal SIGABRT, Aborted.
    (gdb) bt
    #3  0x00007ffff6967252 in __assert_fail () from /lib64/libc.so.6
    #4  0x00007fffd32be0cc in DetSim0Svc::initializeOpticks (this=0xadc530) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:315
    #5  0x00007fffd32bce63 in DetSim0Svc::initialize (this=0xadc530) at /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimOptions/src/DetSim0Svc.cc:104
    #6  0x00007fffee50d266 in DleSupervisor::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffee5235a9 in Task::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffee52c187 in TopTask::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffee527a2b in TaskWatchDog::initialize() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffee523568 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so



Check ntds0, it works without incident::

    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize
    Begin of Event --> 0
    junoSD_PMT_v2::EndOfEvent NOT WITH OPTICKS
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 14 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (1) 
    junoSD_PMT_v2::Initialize
    Begin of Event --> 1
    junoSD_PMT_v2::EndOfEvent NOT WITH OPTICKS
    junoSD_PMT_v2::EndOfEvent m_opticksMode 0 hitCollection 8 hitCollection_muon 0 hitCollection_opticks 0
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 2           7.47800        3.73900      3.26200      
    DetSimAlg                2           59.47800       29.73900     15.52500     
    Sum of junotoptask       2           67.11800       33.55900     18.85800     
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 2
    Delete G4SvcRunManager

    **************************************************
    Terminating @ localhost.localdomain on Tue Sep 27 19:42:53 2022
    SNiPER::Context Running Mode = { BASIC }
    SNiPER::Context Terminated Successfully
    [Inferior 1 (process 432072) exited normally]
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-25.el7_9.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) 



Build debug::

     jo
     ./build_Debug.sh 


ntds3 SEGV::

    Correlated gamma emission flag                      0
    Max 2J for sampling of angular correlations         10
    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    junoSD_PMT_v2::Initialize

    Program received signal SIGSEGV, Segmentation fault.
    0x00007fffd2b2faa1 in PMTHitMerger::init(G4THitsCollection<junoHit_PMT>*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    Missing separate debuginfos, use: debuginfo-install bzip2-libs-1.0.6-13.el7.x86_64 cyrus-sasl-lib-2.1.26-23.el7.x86_64 expat-2.1.0-10.el7_3.x86_64 freetype-2.8-12.el7_6.1.x86_64 glibc-2.17-307.el7.1.x86_64 keyutils-libs-1.5.8-3.el7.x86_64 krb5-libs-1.15.1-37.el7_6.x86_64 libICE-1.0.9-9.el7.x86_64 libSM-1.2.2-2.el7.x86_64 libX11-1.6.7-4.el7_9.x86_64 libXau-1.0.8-2.1.el7.x86_64 libXext-1.3.3-3.el7.x86_64 libXmu-1.1.2-2.el7.x86_64 libXt-1.1.5-3.el7.x86_64 libcom_err-1.42.9-13.el7.x86_64 libcurl-7.29.0-59.el7_9.1.x86_64 libglvnd-1.0.1-0.8.git5baa1e5.el7.x86_64 libglvnd-glx-1.0.1-0.8.git5baa1e5.el7.x86_64 libicu-50.2-4.el7_7.x86_64 libidn-1.28-4.el7.x86_64 libpng-1.5.13-7.el7_2.x86_64 libselinux-2.5-14.1.el7.x86_64 libssh2-1.8.0-3.el7.x86_64 libuuid-2.23.2-59.el7_6.1.x86_64 libxcb-1.13-1.el7.x86_64 mesa-libGLU-9.0.0-4.el7.x86_64 ncurses-libs-5.9-14.20130511.el7_4.x86_64 nspr-4.19.0-1.el7_5.x86_64 nss-3.36.0-7.1.el7_6.x86_64 nss-softokn-freebl-3.36.0-5.el7_5.x86_64 nss-util-3.36.0-1.1.el7_6.x86_64 openldap-2.4.44-25.el7_9.x86_64 openssl-libs-1.0.2k-25.el7_9.x86_64 pcre-8.32-17.el7.x86_64 readline-6.2-11.el7.x86_64 xz-libs-5.2.2-1.el7.x86_64 zlib-1.2.7-18.el7.x86_64
    (gdb) bt
    #0  0x00007fffd2b2faa1 in PMTHitMerger::init(G4THitsCollection<junoHit_PMT>*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    #1  0x00007fffd2b8a123 in junoSD_PMT_v2::Initialize(G4HCofThisEvent*) () from /data/blyth/junotop/junosw/InstallArea/lib64/libPMTSim.so
    #2  0x00007fffdd919c25 in G4SDStructure::Initialize(G4HCofThisEvent*) [clone .localalias.79] () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #3  0x00007fffdd917b5d in G4SDManager::PrepareNewEvent() () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so
    #4  0x00007fffdfa240a6 in G4EventManager::DoProcessing(G4Event*) () from /data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #5  0x00007fffd3dbed20 in G4SvcRunManager::SimulateEvent(int) () from /data/blyth/junotop/junosw/InstallArea/lib64/libG4Svc.so
    #6  0x00007fffd3fca339 in DetSimAlg::execute() () from /data/blyth/junotop/junosw/InstallArea/lib64/libDetSimAlg.so
    #7  0x00007fffee52384a in Task::execute() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffee528855 in TaskWatchDog::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffee523574 in Task::run() () from /data/blyth/junotop/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffee9da7a3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /data/blyth/junotop/sniper/InstallArea/python/Sniper/libSniperPython.so
    #11 0x00007fffee2c9c5d in boost::python::objects::function::call(_object*, _object*) const () from /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so.1.78.0
    #12 0x00007fffee2c9ee8 in boost::detail::function::void_function_ref_invoker0<boost::python::objects::(anonymous namespace)::bind_ret



Tidy up after accepted MR is merged and close issue in web interface::

    N[blyth@localhost junosw]$ git s
    # On branch blyth-handle-genie-API-change-in-backwards-compatible-manner
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ git checkout main
    Switched to branch 'main'
    N[blyth@localhost junosw]$ git s
    # On branch main
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ git branch
      blyth-handle-genie-API-change-in-backwards-compatible-manner
    * main
    N[blyth@localhost junosw]$ git pull 
    remote: Enumerating objects: 1, done.
    remote: Counting objects: 100% (1/1), done.
    remote: Total 1 (delta 0), reused 0 (delta 0), pack-reused 0
    Unpacking objects: 100% (1/1), done.
    From code.ihep.ac.cn:JUNO/offline/junosw
       216c922..4efaaf7  main       -> origin/main
    Updating 216c922..4efaaf7
    Fast-forward
     Generator/GenGenie/src/ghep2hepmc.cc | 8 ++++++++
     1 file changed, 8 insertions(+)
    N[blyth@localhost junosw]$ git branch
      blyth-handle-genie-API-change-in-backwards-compatible-manner
    * main
    N[blyth@localhost junosw]$ git branch -d blyth-handle-genie-API-change-in-backwards-compatible-manner
    Deleted branch blyth-handle-genie-API-change-in-backwards-compatible-manner (was f305ec5).
    N[blyth@localhost junosw]$ 








Make MR for GenGenie change::

    N[blyth@localhost junosw]$ git s
    # On branch main
    # Changes not staged for commit:
    #   (use "git add <file>..." to update what will be committed)
    #   (use "git checkout -- <file>..." to discard changes in working directory)
    #
    #	modified:   Generator/GenGenie/src/ghep2hepmc.cc
    #
    no changes added to commit (use "git add" and/or "git commit -a")
    N[blyth@localhost junosw]$ git checkout -b blyth-handle-genie-API-change-in-backwards-compatible-manner
    M	Generator/GenGenie/src/ghep2hepmc.cc
    Switched to a new branch 'blyth-handle-genie-API-change-in-backwards-compatible-manner'
    N[blyth@localhost junosw]$ 


    N[blyth@localhost junosw]$ git add . 
    N[blyth@localhost junosw]$ git commit -m "WIP: #16 handle genie API transition using GVersion.h GRELCODE "
    [blyth-handle-genie-API-change-in-backwards-compatible-manner f305ec5] WIP: #16 handle genie API transition using GVersion.h GRELCODE
     1 file changed, 8 insertions(+)
    N[blyth@localhost junosw]$ git push 
    fatal: The current branch blyth-handle-genie-API-change-in-backwards-compatible-manner has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-handle-genie-API-change-in-backwards-compatible-manner

    N[blyth@localhost junosw]$ git push --set-upstream origin blyth-handle-genie-API-change-in-backwards-compatible-manner
    Counting objects: 11, done.
    Delta compression using up to 48 threads.
    Compressing objects: 100% (6/6), done.
    Writing objects: 100% (6/6), 617 bytes | 0 bytes/s, done.
    Total 6 (delta 5), reused 0 (delta 0)
    remote: 
    remote: To create a merge request for blyth-handle-genie-API-change-in-backwards-compatible-manner, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junosw/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-handle-genie-API-change-in-backwards-compatible-manner
    remote: 
    To git@code.ihep.ac.cn:JUNO/offline/junosw
     * [new branch]      blyth-handle-genie-API-change-in-backwards-compatible-manner -> blyth-handle-genie-API-change-in-backwards-compatible-manner
    Branch blyth-handle-genie-API-change-in-backwards-compatible-manner set up to track remote branch blyth-handle-genie-API-change-in-backwards-compatible-manner from origin.
    N[blyth@localhost junosw]$ 

    N[blyth@localhost junosw]$ git s
    # On branch blyth-handle-genie-API-change-in-backwards-compatible-manner
    nothing to commit, working directory clean
    N[blyth@localhost junosw]$ 





Missed some env setup for sniper due to genie interrupted build::

    N[blyth@localhost build]$ cmake --build . -j48
    ...


    [100%] Building CXX object Simulation/DetSimV2/DetSimMTUtil/CMakeFiles/DetSimMTUtil.dir/src/GlobalDetSimOutAlg.cc.o
    [100%] Building CXX object Simulation/DetSimV2/DetSimMTUtil/CMakeFiles/DetSimMTUtil.dir/src/LSExpMTEventAction.cc.o
    [100%] Building CXX object Simulation/DetSimV2/DetSimMTUtil/CMakeFiles/DetSimMTUtil.dir/src/DetFactorySvc.cc.o
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimMTUtil/src/JUNOEventUserInfo.hh:7,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimMTUtil/src/LSExpMTEventAction.cc:43:
    /data/blyth/junotop/junosw/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
     #include "SniperMuster/GlobalStream.h"
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    compilation terminated.
    gmake[2]: *** [Simulation/DetSimV2/DetSimMTUtil/CMakeFiles/DetSimMTUtil.dir/src/LSExpMTEventAction.cc.o] Error 1
    gmake[2]: *** Waiting for unfinished jobs....
    In file included from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimMTUtil/src/GlobalDetSimOutAlg.h:8,
                     from /data/blyth/junotop/junosw/Simulation/DetSimV2/DetSimMTUtil/src/GlobalDetSimOutAlg.cc:2:
    /data/blyth/junotop/junosw/Utilities/MtUtilities/MtUtilities/EventContext.h:5:10: fatal error: SniperMuster/GlobalStream.h: No such file or directory
     #include "SniperMuster/GlobalStream.h"
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As that header is there::

    N[blyth@localhost SniperMuster]$ l
    total 28
    0 drwxrwxr-x. 2 blyth blyth  145 Jun  6 15:28 .
    0 drwxrwxr-x. 6 blyth blyth   86 Jun  6 15:28 ..
    8 -rw-rw-r--. 1 blyth blyth 5250 Jun  6 15:28 GlobalBuffer.h
    4 -rw-rw-r--. 1 blyth blyth 1524 Jun  6 15:28 GlobalStream4Any.h
    4 -rw-rw-r--. 1 blyth blyth 1676 Jun  6 15:28 GlobalStreamBase.h
    4 -rw-rw-r--. 1 blyth blyth 3926 Jun  6 15:28 GlobalStream.h
    4 -rw-rw-r--. 1 blyth blyth 1952 Jun  6 15:28 MtDagTask.h
    4 -rw-rw-r--. 1 blyth blyth 1182 Jun  6 15:28 ThreadAssistor.h
    N[blyth@localhost SniperMuster]$ vi GlobalStream.h
    N[blyth@localhost SniperMuster]$ pwd
    /data/blyth/junotop/mt.sniper/SniperMuster/SniperMuster
    N[blyth@localhost SniperMuster]$ 








/data/blyth/junotop/ExternalLibs/genie/3.00.06/include/GENIE/Framework/Conventions/GVersion.h::

     01 #ifndef _GVERSION_H_ 
      2 #define _GVERSION_H_ 
      3 /* 
      4  * Version information automatically generated by the GENIE installer 
      5  * 
      6  * These macros can be used in the following way (as the ones at ROOT's RVersion.h): 
      7  * #if __GENIE_RELEASE_CODE__ >= GRELCODE(2,4,11) 
      8  * #include <newheader.h>
      9  * #else
     10  * #include <oldheader.h>
     11  * #endif
     12 */
     13 
     14 #define GRELCODE(a,b,c) (((a) << 16) + ((b) << 8) + (c)) 
     15 
     16 #define __GENIE_RELEASE__      "3.0.6"
     17 #define __GENIE_RELEASE_CODE__ GRELCODE(3,0,6) 
     18 
     19 #define __GENIE_GIT_REVISION__ "-1" 
     20 
     21 #endif
     22 


* https://code.ihep.ac.cn/JUNO/offline/junosw/-/commit/4a768f6cba50dbc8d1479783926ba647f4f34ebd




::

    [ 91%] Linking CXX shared library ../../../lib/libPMTSimParamSvc.so
    [ 91%] Building CXX object Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/src/R12860PMTManager.cc.o
    [ 91%] Building CXX object Simulation/DetSimV2/PMTSim/CMakeFiles/PMTSim.dir/src/R12860TorusPMTManager.cc.o
    /data/blyth/junotop/junosw/Generator/GenGenie/src/ghep2hepmc.cc: In function 'bool ghep2hepmc(genie::EventRecord&, HepMC::GenEvent&)':
    /data/blyth/junotop/junosw/Generator/GenGenie/src/ghep2hepmc.cc:83:32: error: 'const class genie::ProcessInfo' has no member named 'IsCoherentProduction'; did you mean 'IsCoherent'?
         bool is_coh    = proc_info.IsCoherentProduction();
                                    ^~~~~~~~~~~~~~~~~~~~
                                    IsCoherent




collections/22.2.sh::

    function juno-ext-libs-python-version- { echo 3.9.14 ; }
    function juno-ext-libs-boost-version- { echo 1.78.0 ; }

collections/22.1.sh::

    function juno-ext-libs-python-version- { echo 3.8.12 ; }
    function juno-ext-libs-boost-version- { echo 1.78.0 ; }
    
::

    epsilon:collections blyth$ diff -y  22.1.sh 22.2.sh 
    function juno-ext-libs-git-version- { echo 2.34.1 ; }	      |	function juno-ext-libs-git-version- { echo 2.37.3 ; }
    function juno-ext-libs-cmake-version- { echo 3.22.1 ; }	      |	function juno-ext-libs-cmake-version- { echo 3.24.1 ; }
    function juno-ext-libs-python-version- { echo 3.8.12 ; }      |	function juno-ext-libs-python-version- { echo 3.9.14 ; }
    function juno-ext-libs-python-setuptools-version- { echo 58.0 |	function juno-ext-libs-python-setuptools-version- { echo 58.1
    function juno-ext-libs-python-pip-version- { echo 21.2.4 ; }  |	function juno-ext-libs-python-pip-version- { echo 22.2.2 ; }
    function juno-ext-libs-python-cython-version- { echo 0.29.24  |	function juno-ext-libs-python-cython-version- { echo 0.29.28 
    function juno-ext-libs-python-numpy-version- { echo 1.21.4 ;  |	function juno-ext-libs-python-numpy-version- { echo 1.22.3 ; 
    function juno-ext-libs-libyaml-version- { echo 0.2.4 ; }	    function juno-ext-libs-libyaml-version- { echo 0.2.4 ; }
    function juno-ext-libs-python-yaml-version- { echo 5.4.1.1 ; 	function juno-ext-libs-python-yaml-version- { echo 5.4.1.1 ; 
    function juno-ext-libs-boost-version- { echo 1.78.0 ; }		    function juno-ext-libs-boost-version- { echo 1.78.0 ; }
    function juno-ext-libs-xercesc-version- { echo 3.2.2 ; }      |	function juno-ext-libs-xercesc-version- { echo 3.2.3 ; }
    function juno-ext-libs-gsl-version- { echo 2.5 ; }	          |	function juno-ext-libs-gsl-version- { echo 2.7 ; }
    function juno-ext-libs-fftw3-version- { echo 3.3.8 ; }	      |	function juno-ext-libs-fftw3-version- { echo 3.3.10 ; }
    function juno-ext-libs-sqlite3-version- { echo 3.35.5 ; }     |	function juno-ext-libs-sqlite3-version- { echo 3.38.5 ; }
    function juno-ext-libs-mysql-connector-c-version- { echo 6.1.	function juno-ext-libs-mysql-connector-c-version- { echo 6.1.
    function juno-ext-libs-mysql-connector-cpp-version- { echo 1.	function juno-ext-libs-mysql-connector-cpp-version- { echo 1.
    function juno-ext-libs-pacparser-version- { echo 1.3.7 ; }	    function juno-ext-libs-pacparser-version- { echo 1.3.7 ; }
    function juno-ext-libs-frontier-version- { echo 2.9.1 ; }	    function juno-ext-libs-frontier-version- { echo 2.9.1 ; }
    function juno-ext-libs-log4cpp-version- { echo 1.1.3 ; }	    function juno-ext-libs-log4cpp-version- { echo 1.1.3 ; }
    function juno-ext-libs-libxml2-version- { echo 2.9.12 ; }	    function juno-ext-libs-libxml2-version- { echo 2.9.12 ; }
    function juno-ext-libs-LHAPDF-version- { echo 6.3.0 ; }		    function juno-ext-libs-LHAPDF-version- { echo 6.3.0 ; }
    function juno-ext-libs-pythia6-version- { echo 6.4.28 ; }	    function juno-ext-libs-pythia6-version- { echo 6.4.28 ; }
    function juno-ext-libs-tbb-version- { echo 2020.3 ; }		    function juno-ext-libs-tbb-version- { echo 2020.3 ; }
    function juno-ext-libs-clhep-version- { echo 2.4.1.0 ; }	    function juno-ext-libs-clhep-version- { echo 2.4.1.0 ; }
    function juno-ext-libs-xrootd-version- { echo 5.3.4 ; }	      |	function juno-ext-libs-xrootd-version- { echo 5.4.3 ; }
    function juno-ext-libs-ROOT-version- { echo 6.24.06 ; }	      |	function juno-ext-libs-ROOT-version- { echo 6.26.06 ; }
    function juno-ext-libs-hepmc-version- { echo 2.06.09 ; }      |	function juno-ext-libs-hepmc-version- { echo 2.06.11 ; }
    function juno-ext-libs-geant4-version- { echo 10.04.p02.juno 	function juno-ext-libs-geant4-version- { echo 10.04.p02.juno 

    function juno-ext-libs-genie-version- { echo 3.00.06 ; }      |	function juno-ext-libs-genie-version- { echo 3.02.00 ; }

    function juno-ext-libs-nuwro-version- { echo 19.02.2 ; }	    function juno-ext-libs-nuwro-version- { echo 19.02.2 ; }
    function juno-ext-libs-talys-version- { echo 1.95 ; }		    function juno-ext-libs-talys-version- { echo 1.95 ; }
    function juno-ext-libs-gibuu-version- { echo r2021_01 ; }	    function juno-ext-libs-gibuu-version- { echo r2021_01 ; }
    function juno-ext-libs-libmore-version- { echo 0.8.3 ; }	    function juno-ext-libs-libmore-version- { echo 0.8.3 ; }
    function juno-ext-libs-libmore-data-version- { echo 20140630 	function juno-ext-libs-libmore-data-version- { echo 20140630 
    function juno-ext-libs-libonnxruntime-version- { echo 1.11.1 	function juno-ext-libs-libonnxruntime-version- { echo 1.11.1 
    epsilon:collections blyth$ 


Now which sniper version to use with junoenv/collections/22.1.sh ?::

   cd /tmp
   curl -L -O https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
   curl -L -O https://github.com/SNiPER-Framework/sniper/archive/v2.2.1.tar.gz
   tar zxvf v2.2.2.tar.gz 
   tar zxvf v2.2.1.tar.gz 


* Sniper 2.2.2, Boost 1.67 : so it should work with both collections







Clean up branch following accepted merge request::

    N[blyth@localhost junoenv]$ git s
    # On branch blyth-add-junoenv-libs-vlist
    nothing to commit, working directory clean
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ git help branch 
    N[blyth@localhost junoenv]$ git branch -d 
    fatal: branch name required
    N[blyth@localhost junoenv]$ git branch -d blyth-add-junoenv-libs-vlist
    error: Cannot delete the branch 'blyth-add-junoenv-libs-vlist' which you are currently on.
    N[blyth@localhost junoenv]$ git checkout main
    Switched to branch 'main'
    Your branch is behind 'origin/main' by 14 commits, and can be fast-forwarded.
      (use "git pull" to update your local branch)
    N[blyth@localhost junoenv]$ git branch -d blyth-add-junoenv-libs-vlist
    warning: deleting branch 'blyth-add-junoenv-libs-vlist' that has been merged to
             'refs/remotes/origin/blyth-add-junoenv-libs-vlist', but not yet merged to HEAD.
    Deleted branch blyth-add-junoenv-libs-vlist (was 592668b).
    N[blyth@localhost junoenv]$ git pull 
    Updating 0e0aad5..877fc01
    Fast-forward
     collections/22.1.sh      |  35 ++++++++++++++++++++
     collections/22.2.sh      |  35 ++++++++++++++++++++
     git-junoenv/git-junoenv  | 308 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     junoenv                  |  12 +++++++
     junoenv-external-libs.sh |  23 ++++++++++---
     5 files changed, 409 insertions(+), 4 deletions(-)
     create mode 100644 collections/22.1.sh
     create mode 100644 collections/22.2.sh
     create mode 100755 git-junoenv/git-junoenv
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ 




::

    N[blyth@localhost junoenv]$ git add . 
    N[blyth@localhost junoenv]$ git commit -m "add junoenv libs vlist to facilitate version overriding"
    [blyth-add-junoenv-libs-vlist 592668b] add junoenv libs vlist to facilitate version overriding
     1 file changed, 19 insertions(+), 4 deletions(-)
    N[blyth@localhost junoenv]$ git push 
    fatal: The current branch blyth-add-junoenv-libs-vlist has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin blyth-add-junoenv-libs-vlist

    N[blyth@localhost junoenv]$ git push --set-upstream origin blyth-add-junoenv-libs-vlist
    Counting objects: 255, done.
    Delta compression using up to 48 threads.
    Compressing objects: 100% (62/62), done.
    Writing objects: 100% (224/224), 23.26 KiB | 0 bytes/s, done.
    Total 224 (delta 138), reused 217 (delta 132)
    remote: Resolving deltas: 100% (138/138), completed with 31 local objects.
    remote: 
    remote: To create a merge request for blyth-add-junoenv-libs-vlist, visit:
    remote:   https://code.ihep.ac.cn/JUNO/offline/junoenv/-/merge_requests/new?merge_request%5Bsource_branch%5D=blyth-add-junoenv-libs-vlist
    remote: 
    To git@code.ihep.ac.cn:JUNO/offline/junoenv.git
     * [new branch]      blyth-add-junoenv-libs-vlist -> blyth-add-junoenv-libs-vlist
    Branch blyth-add-junoenv-libs-vlist set up to track remote branch blyth-add-junoenv-libs-vlist from origin.
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ 






::

     282 function juno-ext-libs-PKG-version {
     283     local curpkg=$1
     284     # check override
     285     type -t juno-ext-libs-${curpkg}-version- >& /dev/null
     286     if [ "$?" = "0" ]; then
     287         # user defined 
     288         echo $(juno-ext-libs-${curpkg}-version-)
     289     else
     290         echo $(juno-ext-libs-${curpkg}-version-default)
     291     fi
     292 }





::

    N[blyth@localhost junotop]$ jx-extlib
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: ""
    == setup-juno-basic-preq: ================================================================
    == setup-juno-external-libs
    === junoenv-external-libs: allpkgs will be loaded
    === junoenv-external-libs: git cmake python python-setuptools python-pip python-cython python-numpy libyaml python-yaml boost xercesc gsl fftw3 sqlite3 mysql-connector-c mysql-connector-cpp pacparser frontier log4cpp libxml2 LHAPDF pythia6 tbb clhep xrootd ROOT hepmc geant4 genie nuwro talys gibuu libmore libonnxruntime
    === junoenv-external-libs: command: reuse
    === junoenv-external-libs: packages: git cmake python python-setuptools python-pip python-cython python-numpy libyaml python-yaml boost xercesc gsl fftw3 sqlite3 mysql-connector-c mysql-connector-cpp pacparser frontier log4cpp libxml2 LHAPDF pythia6 tbb clhep xrootd ROOT hepmc geant4 genie nuwro talys gibuu libmore libonnxruntime
    === junoenv-external-libs: create function juno-ext-libs-git-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init git
    ==== juno-ext-libs-check-init: setup dependencies for git
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: create log directory /data/blyth/junotop/junoenv/logs/git
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: create function juno-ext-libs-git-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: source /data/blyth/junotop/junoenv/packages/git.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup git: After source: git
    === junoenv-external-libs: juno-ext-libs-check-is-reused git
    === junoenv-external-libs: juno-ext-libs-reuse git
    ==== juno-ext-libs-reuse: git oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3
    ==== juno-ext-libs-reuse: git newpath: /data/blyth/junotop/ExternalLibs/Git/2.37.3
    ==== juno-ext-libs-reuse: git oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-cmake-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init cmake
    ==== juno-ext-libs-check-init: setup dependencies for cmake
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: create log directory /data/blyth/junotop/junoenv/logs/cmake
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: create function juno-ext-libs-cmake-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: source /data/blyth/junotop/junoenv/packages/cmake.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup cmake: After source: cmake
    === junoenv-external-libs: juno-ext-libs-check-is-reused cmake
    === junoenv-external-libs: juno-ext-libs-reuse cmake
    ==== juno-ext-libs-reuse: cmake oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Cmake/3.24.1
    ==== juno-ext-libs-reuse: cmake newpath: /data/blyth/junotop/ExternalLibs/Cmake/3.24.1
    ==== juno-ext-libs-reuse: cmake oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Cmake/3.24.1" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-python-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init python
    ==== juno-ext-libs-check-init: setup dependencies for python
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: create log directory /data/blyth/junotop/junoenv/logs/python
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python: After source: python
    === junoenv-external-libs: juno-ext-libs-check-is-reused python
    === junoenv-external-libs: juno-ext-libs-reuse python
    ==== juno-ext-libs-reuse: python oldpath: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Python/3.9.14
    ==== juno-ext-libs-reuse: python newpath: /data/blyth/junotop/ExternalLibs/Python/3.9.14
    ==== juno-ext-libs-reuse: python oldpath "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Python/3.9.14" does not exist.
    === junoenv-external-libs: create function juno-ext-libs-python-setuptools-version- to override default
    === junoenv-external-libs: juno-ext-libs-check-init python-setuptools
    ==== juno-ext-libs-check-init: setup dependencies for python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: create log directory /data/blyth/junotop/junoenv/logs/python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: create function juno-ext-libs-python-setuptools-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: source /data/blyth/junotop/junoenv/packages/python-setuptools.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: # setup python-setuptools: After source: python-setuptools
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: create function juno-ext-libs-python-version- to override default
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: source /data/blyth/junotop/junoenv/packages/python.sh
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: After source: python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: status: 0 python
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: can not find /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup python: Please install python first.
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3
    ls: cannot access /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/Git/2.37.3: No such file or directory
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs/
    total 26
    5 drwxr-xr-x.  9 cvmfs cvmfs 4096 Sep  8 23:04 ..






With CUDA 10.1 and gcc 11.2 (CUDA 10.1 max supported GCC is 8, to work with gcc 11 would need CUDA 11.5)::

    [  1%] Generating OpticksGenstep_Enum.ini
    In file included from /usr/local/cuda/include/cuda_runtime.h:83,
                     from <command-line>:
    /usr/local/cuda/include/crt/host_config.h:129:2: error: #error -- unsupported GNU version! gcc versions later than 8 are not supported!
      129 | #error -- unsupported GNU version! gcc versions later than 8 are not supported!
          |  ^~~~~
    [2022-09-26 21:30:19,444] p349597 {/data/bl


* https://rotadev.com/cuda-incompatible-with-my-gcc-version-dev/








Dwarf Error::


    N[blyth@localhost junosw]$ which gdb
    /usr/bin/gdb


    gdb -ex r --args python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --evtmax 2 gun
    Mon Sep 26 20:59:43 CST 2022
    GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-114.el7
    Copyright (C) 2013 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "x86_64-redhat-linux-gnu".
    For bug reporting instructions, please see:
    <http://www.gnu.org/software/gdb/bugs/>...
    Reading symbols from /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Python/3.9.14/bin/python3.9...Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/Python/3.9.14/bin/python3.9]
    (no debugging symbols found)...done.
    Starting program: /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python /data/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py --opticks-mode 0 --no-guide_tube --evtmax 2 gun
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/libpython3.9.so.1.0]
    [Thread debugging using libthread_db enabled]
    Using host libthread_db library "/lib64/libthread_db.so.1".
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_heapq.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/zlib.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_bz2.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_lzma.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/grp.cpython-39-x86_64-linux-gnu.so]
    Namespace(help_more=False, loglevel='Info', evtmax=2, input=None, input_list=None, output='sample_detsim.root', user_output='sample_detsim_user.root', profiling=True, seed=42, start_evtid=0, restore_seed_status=None, dbtype='File', mac='run.mac', vis=False, vis_mac='vis.mac', detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, K40_ACU_source_weight_QC=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=False, dfball_tube=False, simplify_calib_anchor=True, cd_enabled=True, real_surface_in_cd_enabled=True, strut_surface_enabled=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, tt_enabled=True, shutter=False, commissioning_enabled=False, below_z_is_water=0.0, pmt20inch=True, pmt20inch_name='PMTMask', additionacrylic_simplify_csg=False, pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=0.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', cerenkov_yield_factor=1.0, pmt_optical_model=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, opticks_mode=0, opticks_anamgr=False, replace_param=None, usepmtsimsvc=True, quenching=True, pmt_hit_type=1, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, split_maxhits=None, anamgr_simtrack=True, anamgr_edm_gen=True, anamgr_tt=False, anamgr_normal=True, anamgr_normal_hit=False, anamgr_muon=False, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_interesting_process=True, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='gun', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, particles='gamma', momentums=1.0, momentums_mode='Fix', momentums_extra_params=None, momentums_interp='Momentum', positions=[(0, 0, 0)], times=None, directions=None)
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6]
    warning: File "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6.0.29-gdb.py" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load:/usr/bin/mono-gdb.py".
    To enable execution of this file add
        add-auto-load-safe-path /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libstdc++.so.6.0.29-gdb.py
    line to your configuration file "/home/blyth/.gdbinit".
    To completely disable this security protection add
        set auto-load safe-path /
    line to your configuration file "/home/blyth/.gdbinit".




    ine to your configuration file "/home/blyth/.gdbinit".
    For more information about this security protection see the
    "Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
        info "(gdb)Auto-loading safe path"
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libgcc_s.so.1]
    **************************************************
    Welcome to SNiPER v2.1.0
    Running @ localhost.localdomain on Mon Sep 26 20:59:44 2022
    **************************************************
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Python/3.9.14/lib/python3.9/lib-dynload/_json.cpython-39-x86_64-linux-gnu.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/tbb/2020.3/lib/libtbb.so.2]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs/sqlite3/3.38.5/lib/libsqlite3.so.0]
    == ROOT IO Svc ==
    == Buffer Memory Management ==
    == Random Svc ==
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/CLHEP/2.4.1.0/lib/libCLHEP-2.4.1.0.so]
    == Root Writer ==
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/mysql-connector-c/6.1.9/lib/libmysqlclient.so.18]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/lib64/libatomic.so.1]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/Xercesc/3.2.3/lib/libxerces-c-3.2.so]
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/frontier/2.9.1/lib/libfrontier_client.so.2]
     == PMTSimParamSvc == 
    GENTOOL MODE:  gun
    Dwarf Error: wrong version in compilation unit header (is 5, should be 2, 3, or 4) [in module /data/blyth/junotop/ExternalLibs/HepMC/2.06.11/lib/libHepMC.so.4]
    [(0, 0, 0)] None

    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)



::

    N[blyth@localhost ~]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/
    total 137
     5 drwxr-xr-x. 27 cvmfs cvmfs  4096 Sep 16 10:40 junosw
     1 drwxr-xr-x.  8 cvmfs cvmfs    28 Sep 16 10:39 .
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 bashrc.sh
     1 -rw-r--r--.  1 cvmfs cvmfs   908 Sep 12 21:42 setup.csh
     1 -rw-r--r--.  1 cvmfs cvmfs   911 Sep 12 21:42 setup.sh
     4 -rw-r--r--.  1 cvmfs cvmfs  3903 Sep 12 21:42 tcshrc.csh
     1 drwxr-xr-x.  7 cvmfs cvmfs   207 Sep 12 21:22 mt.sniper
     5 drwxr-xr-x. 12 cvmfs cvmfs  4096 Sep 12 21:22 sniper
     1 drwxr-xr-x.  8 cvmfs cvmfs   138 Sep 12 20:38 data
    32 -rw-r--r--.  1 cvmfs cvmfs 32036 Sep 12 20:26 sniper-v0.9.1.tar.gz
    79 -rw-r--r--.  1 cvmfs cvmfs 80884 Sep 12 20:26 sniper-v2.2.2.tar.gz
     1 drwxrwxr-x.  3 cvmfs cvmfs    29 Sep 12 18:30 ..
     1 -rw-r--r--.  1 cvmfs cvmfs     0 Sep 12 18:30 .cvmfscatalog
     5 drwxr-xr-x.  9 cvmfs cvmfs  4096 Sep 12 18:20 junoenv
     1 drwxr-xr-x. 36 cvmfs cvmfs    27 Sep 12 18:19 ExternalLibs
    N[blyth@localhost ~]$ 


::

    bash junoenv libs reuse allpkgs


::

    N[blyth@localhost blyth]$ mv junotop junotop_old
    N[blyth@localhost blyth]$ mkdir junotop




WIP : get setup into git and new working approach
---------------------------------------------------

::

    epsilon:junotop blyth$ mv junoenv junoenv_svn 
    epsilon:junotop blyth$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
    Cloning into 'junoenv'...
    remote: Enumerating objects: 313, done.
    remote: Total 313 (delta 0), reused 0 (delta 0), pack-reused 313
    Receiving objects: 100% (313/313), 153.61 KiB | 131.00 KiB/s, done.
    Resolving deltas: 100% (170/170), done.
    epsilon:junotop blyth$ 

::

    045 function junoenv-offline-checkout {
     46     # checkout all code
     47     local msg="==== $FUNCNAME: "
     48     local repourl=$1; shift
     49     local dstname=$1; shift
     50     local revision=$1; shift
     51 
     52     echo $msg checkout the code $repourl 
     53     # check
     54     git clone $repourl $dstname || exit -1
     55     cd $dstname && git checkout $revision || exit -1
     56 }


    106 function junoenv-offline {
    107     local msg="=== $FUNCNAME: "
    108     # the main handler in this script
    109     local branchname=${1:-$(junoenv-offline-default-branch)}
    110     local revision=${2:-}
    111     # check version
    112     junoenv-offline-version $branchname
    113     if [ "$?" != "0" ]; then
    114         echo $msg branchesname ret: $?
    115         return 1
    116     fi
    117 
    118 
    119     local url=$(junoenv-offline-url $branchname)
    120     echo $msg $?
    121     echo $msg URL: $url
    122     # change directory to $JUNOTOP
    123     pushd $JUNOTOP >& /dev/null
    124     junoenv-offline-checkout $url $(junoenv-offline-name) $revision
    125     junoenv-offline-preq
    126     junoenv-offline-compile
    127     popd
    128 
    129 }




libmore-data fail : judged harmless as coming from cvmfs link anyhow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

HUH: libmore-data-install trying to rsync to cvmfs? ::

    === juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: After source: libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: status: 0 libmore
    ==== juno-ext-libs-dependencies-setup-rec-impl: ## setup libmore: source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
    === junoenv-external-libs: juno-ext-libs-check-is-reused libmore-data
    === junoenv-external-libs: juno-ext-libs-all libmore-data
    ==== juno-ext-libs-get:
    [libmore-data-conf] ===== juno-ext-libs-PKG-get: SKIP DOWNLOADING: ensdf-files-20140630.tar already exists
    ==== juno-ext-libs-conf:
    ==== juno-ext-libs-make:
    ==== juno-ext-libs-install:
    [libmore-data-install] ===== juno-ext-libs-PKG-install: call juno-ext-libs-libmore-data-install-
    [libmore-data-install] sending incremental file list
    [libmore-data-install] rsync: chgrp "/data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/." failed: Read-only file system (30)
    [libmore-data-install] ./
    [libmore-data-install] ar001.ens.bz2
    [libmore-data-install] ar001h.ens.bz2
    [libmore-data-install] ar001nn.ens.bz2
    [libmore-data-install] ar002.ens.bz2


    Last login: Fri Sep 23 19:08:47 2022 from lxslc714.ihep.ac.cn
    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/0.8.3/com/more/ensdf/
    total 24458
    113 drwxr-xr-x. 2 cvmfs cvmfs 114688 Mar  4  2022 .
      4 -rw-r--r--. 1 cvmfs cvmfs   3529 Mar  4  2022 ar28614.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1110 Mar  4  2022 ar286cn.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2941 Mar  4  2022 ar28714.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1875 Mar  4  2022 ar28715.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2809 Mar  4  2022 ar28814.ens.bz2
      2 -rw-r--r--. 1 cvmfs cvmfs   1942 Mar  4  2022 ar28815.ens.bz2
      5 -rw-r--r--. 1 cvmfs cvmfs   4791 Mar  4  2022 ar28914.ens.bz2
      3 -rw-r--r--. 1 cvmfs cvmfs   2396 Mar  4  2022 ar28915.ens.bz2

The 0.8.3 is link to cvmfs::

    N[blyth@localhost ~]$ l /data/blyth/junotop/ExternalLibs/libmore/
    total 4
    4 drwxrwxr-x. 38 blyth blyth 4096 Jul 25 18:30 ..
    0 drwxrwxr-x.  2 blyth blyth   19 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 0.8.3 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/libmore/0.8.3
    N[blyth@localhost ~]$ 

Note that libonnxruntime has large number of github submodules::

    == junoenv-external-libs: juno-ext-libs-check-is-reused libonnxruntime
    === junoenv-external-libs: juno-ext-libs-all libonnxruntime
    ==== juno-ext-libs-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get:
    [libonnxruntime-conf] ===== juno-ext-libs-libonnxruntime-get: clone https://github.com/microsoft/onnxruntime
    [libonnxruntime-conf] Cloning into 'libonnxruntime-1.11.1'...
    [libonnxruntime-conf] Submodule 'cmake/external/FP16' (https://github.com/Maratyszcza/FP16.git) registered for path 'cmake/external/FP16'
    [libonnxruntime-conf] Submodule 'cmake/external/SafeInt/safeint' (https://github.com/dcleblanc/SafeInt.git) registered for path 'cmake/external/SafeInt/safeint'
    [libonnxruntime-conf] Submodule 'cmake/external/XNNPACK' (https://github.com/google/XNNPACK.git) registered for path 'cmake/external/XNNPACK'
    [libonnxruntime-conf] Submodule 'cmake/external/cub' (https://github.com/NVlabs/cub.git) registered for path 'cmake/external/cub'
    [libonnxruntime-conf] Submodule 'cmake/external/cxxopts' (https://github.com/jarro2783/cxxopts.git) registered for path 'cmake/external/cxxopts'
    [libonnxruntime-conf] Submodule 'cmake/external/date' (https://github.com/HowardHinnant/date.git) registered for path 'cmake/external/date'
    [libonnxruntime-conf] Submodule 'cmake/external/dlpack' (https://github.com/dmlc/dlpack.git) registered for path 'cmake/external/dlpack'
    [libonnxruntime-conf] Submodule 'cmake/external/eigen' (https://gitlab.com/libeigen/eigen.git) registered for path 'cmake/external/eigen'
    [libonnxruntime-conf] Submodule 'cmake/external/emsdk' (https://github.com/emscripten-core/emsdk.git) registered for path 'cmake/external/emsdk'
    [libonnxruntime-conf] Submodule 'cmake/external/flatbuffers' (https://github.com/google/flatbuffers.git) registered for path 'cmake/external/flatbuffers'

Even though it looks to have hung checking ps shows that some progress is being made, with movement between submodules::

    N[blyth@localhost ~]$ ps aux | grep blyth




fail : bash junoenv sniper
----------------------------

::

    N[blyth@localhost junoenv]$ source $JUNOTOP/bashrc.sh
    N[blyth@localhost junoenv]$ 
    N[blyth@localhost junoenv]$ bash junoenv sniper
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /data/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    == setup-juno-basic-preq: ================================================================
    == setup-juno-basic-preq: GLOBAL Environment Variables:
    == setup-juno-basic-preq: $JUNOTOP is "/data/blyth/junotop"
    == setup-juno-basic-preq: $JUNO_EXTLIB_OLDTOP: "/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs"
    == setup-juno-basic-preq: $JUNOARCHIVEGET: ""
    == setup-juno-basic-preq: $JUNOARCHIVEURL: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON2: ""
    == setup-juno-basic-preq: $JUNO_USE_PYTHON3: ""
    == setup-juno-basic-preq: $CMTEXTRATAGS: "opticks"
    == setup-juno-basic-preq: ================================================================
    == setup-juno-sniper
    === junoenv-sniper: 0
    === junoenv-sniper: SNiPER URL: https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
    === junoenv-sniper: MT SNiPER URL: https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/sniper/archive/v2.2.2.tar.gz
      % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                     Dload  Upload   Total   Spent    Left  Speed
      0     0    0     0    0     0      0      0 --:--:--  0:00:01 --:--:--     0
      0     0    0 80884    0     0  31319      0 --:--:--  0:00:02 --:--:-- 85410
    ==== junoenv-sniper-get: download the source code https://github.com/SNiPER-Framework/mt.sniper/archive/v0.9.1.tar.gz
    ==== junoenv-sniper-check-preq: Pre Requirement Check
    ==== junoenv-sniper-check-preq: source /data/blyth/junotop/bashrc.sh
    /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    /data/blyth/junotop/sniper/build /data/blyth/junotop/sniper /data/blyth/junotop /data/blyth/junotop /data/blyth/junotop/junoenv /data/blyth/junotop/junoenv
    -- cmake version 3.24.1
    -- The CXX compiler identification is GNU 8.3.0
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Check for working CXX compiler: /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bin/g++ - skipped
    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    CMake Error at /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
      Could NOT find Python3 (missing: Interpreter) (found version "3.8.12")

          Reason given by package: 
              Interpreter: Cannot run the interpreter "/data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8"

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPackageHandleStandardArgs.cmake:594 (_FPHSA_FAILURE_MESSAGE)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake:3203 (find_package_handle_standard_args)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake:490 (include)
      CMakeLists.txt:65 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost junoenv]$ 


::

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python3.8: error while loading shared libraries: libpython3.8.so.1.0: cannot open shared object file: No such file or directory
    N[blyth@localhost junoenv]$ 



/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython3.cmake::

    486 set (_PYTHON_PREFIX Python3)
    487 
    488 set (_Python3_REQUIRED_VERSION_MAJOR 3)
    489 
    490 include (${CMAKE_CURRENT_LIST_DIR}/FindPython/Support.cmake)
    491 
    492 if (COMMAND __Python3_add_library)
    493   macro (Python3_add_library)
    494     __Python3_add_library (Python3 ${ARGV})
    495   endmacro()
    496 endif()

/data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindPython/Support.cmake::



Huh sniper/CMake trying to use python 3.8.12 when 3.9.14 is available::

    N[blyth@localhost junoenv]$ cat $JUNOTOP/bashrc.sh 
    export JUNOTOP=/data/blyth/junotop
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/binutils/2.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/contrib/gcc/8.3.0/bashrc
    source /data/blyth/junotop/ExternalLibs/Git/2.37.3/bashrc
    source /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/bashrc
    source /data/blyth/junotop/ExternalLibs/Python/3.9.14/bashrc
    source /data/blyth/junotop/ExternalLibs/python-setuptools/58.1.0/bashrc
    source /data/blyth/junotop/ExternalLibs/python-pip/22.2.2/bashrc
    source /data/blyth/junotop/ExternalLibs/python-cython/0.29.28/bashrc

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Python/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  6 blyth blyth   84 Sep 23 18:51 3.9.14
    0 drwxrwxr-x.  3 blyth blyth   34 Sep 23 18:49 .
    0 lrwxrwxrwx.  1 blyth blyth   90 Mar  2  2022 3.8.12 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Python/3.8.12
    N[blyth@localhost junoenv]$ 

    N[blyth@localhost junoenv]$ /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3
    Python 3.9.14 (main, Sep 23 2022, 18:50:47) 
    [GCC 8.3.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> 


Probably update building not operational::

    N[blyth@localhost junotop]$ mv sniper sniper_old
    N[blyth@localhost junotop]$ mv mt.sniper mt.sniper_old


That gets further, failing at boost python::

    -- Detecting CXX compile features
    -- Detecting CXX compile features - done
    -- Found Python3: /data/blyth/junotop/ExternalLibs/Python/3.9.14/bin/python3.9 (found version "3.9.14") found components: Interpreter Development Development.Module Development.Embed 
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!


Hmm it would be easier to reuse sniper and all the external libs. 


::

    N[blyth@localhost sniper]$ cd build
    N[blyth@localhost build]$ cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
    -- cmake version 3.24.1
    -- python version 3.9.14
    CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
      Found package configuration file:

        /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

      but it set boost_python_FOUND to FALSE so package "boost_python" is
      considered to be NOT FOUND.  Reason given by package:

      No suitable build variant has been found.

      The following variants have been tried and rejected:

      * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

      * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

    Call Stack (most recent call first):
      /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
      /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
      CMakeLists.txt:73 (find_package)


    -- Configuring incomplete, errors occurred!
    See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
    N[blyth@localhost build]$ 



sniper/CMakeLists.txt is looking for Boost 1.67::

     57 # Config for Option USE_PYTHON
     58 if(USE_PYTHON)
     59     #python
     60     set(PyPkgName Python3)  #Use Python3 by default
     61     option(USE_PYTHON2 "Use Python2 instead of Python3" OFF)
     62     if(USE_PYTHON2)
     63         set(PyPkgName Python2)
     64     endif()
     65     find_package(${PyPkgName} COMPONENTS Interpreter Development REQUIRED)
     66     message(STATUS "python version ${${PyPkgName}_VERSION}")
     67     set(PYTHON_VERSION "${${PyPkgName}_VERSION}")
     68     set(PYTHON_INCLUDE_DIRS "${${PyPkgName}_INCLUDE_DIRS}")
     69     set(PYTHON_LIBRARY "${${PyPkgName}_LIBRARIES}")
     70     #boost.python
     71     set(Boost_USE_MULTITHREADED OFF)
     72     set(BoostPyVer "${${PyPkgName}_VERSION_MAJOR}${${PyPkgName}_VERSION_MINOR}")
     73     find_package(Boost 1.67 COMPONENTS python${BoostPyVer} REQUIRED)
     74     set(BOOST_PYTHON_LIBRARY "${Boost_PYTHON${BoostPyVer}_LIBRARY}")
     75     unset(BoostPyVer)
     76     #python install dir
     77     if(NOT CMAKE_INSTALL_PYTHONDIR)
     78         set(CMAKE_INSTALL_PYTHONDIR "python")
     79     endif()
     80     #...
     81     add_definitions(-DHAVE_PYTHON)
     82     unset(PyPkgName)
     83 endif()


::

    N[blyth@localhost junoenv]$ l /data/blyth/junotop/ExternalLibs/Boost/
    total 4
    4 drwxrwxr-x. 39 blyth blyth 4096 Sep 23 19:47 ..
    0 drwxrwxr-x.  2 blyth blyth   20 Mar  2  2022 .
    0 lrwxrwxrwx.  1 blyth blyth   89 Mar  2  2022 1.78.0 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0
    N[blyth@localhost junoenv]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/
    total 2
    1 drwxr-xr-x. 37 cvmfs cvmfs 36 May 26 16:39 ..
    1 drwxr-xr-x.  4 cvmfs cvmfs 80 Mar  4  2022 1.78.0
    1 drwxr-xr-x.  3 cvmfs cvmfs 28 Jan  5  2022 .
    N[blyth@localhost junoenv]$ 






N[blyth@localhost build]$  cmake .. -DCMAKE_INSTALL_PREFIX=../InstallArea -DCMAKE_CXX_STANDARD=17 
-- cmake version 3.24.1
-- python version 3.9.14
CMake Error at /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:141 (find_package):
  Found package configuration file:

    /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/boost_python-1.78.0/boost_python-config.cmake

  but it set boost_python_FOUND to FALSE so package "boost_python" is
  considered to be NOT FOUND.  Reason given by package:

  No suitable build variant has been found.

  The following variants have been tried and rejected:

  * libboost_python38.so.1.78.0 (3.8, Boost_PYTHON_VERSION=3.9)

  * libboost_python38.a (3.8, Boost_PYTHON_VERSION=3.9)

Call Stack (most recent call first):
  /data/blyth/junotop/ExternalLibs/Boost/1.78.0/lib/cmake/Boost-1.78.0/BoostConfig.cmake:262 (boost_find_component)
  /data/blyth/junotop/ExternalLibs/Cmake/3.24.1/share/cmake-3.24/Modules/FindBoost.cmake:594 (find_package)
  CMakeLists.txt:73 (find_package)


-- Configuring incomplete, errors occurred!
See also "/data/blyth/junotop/sniper/build/CMakeFiles/CMakeOutput.log".
N[blyth@localhost build]$ 



::

    N[blyth@localhost Boost]$ l /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/*python*.*
    644 -rw-r--r--. 1 cvmfs cvmfs 659132 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.a
    334 -rwxr-xr-x. 1 cvmfs cvmfs 341264 Mar  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so.1.78.0
      1 lrwxrwxrwx. 1 cvmfs cvmfs     27 Jan  4  2022 /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs/Boost/1.78.0/lib/libboost_python38.so -> libboost_python38.so.1.78.0
    N[blyth@localhost Boost]$ 





