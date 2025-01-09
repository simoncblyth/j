FIXED jok-tds-B-side-missing-NPFold-concat
================================================

Where is the U4Recorder equivalent of the QSim::simulate tail::

     419         tot_gdt += ( t_DOWN - t_POST ) ;
     420     }
     421 
     422     int64_t t_LEND = SProf::Add("QSim__simulate_LEND");
     423 
     424     sev->topfold->concat();
     425     if(!KEEP_SUBFOLD) sev->topfold->clear_subfold();
     426 
     427     int64_t t_PCAT = SProf::Add("QSim__simulate_PCAT");
     428 
     429     int tot_ht = sev->getNumHit() ;  // NB from fold, so requires hits array gathering to be configured to get non-zero 
     430 


Here::

     347 void U4Recorder::EndOfEventAction_(int eventID_)
     348 {
     349     assert( eventID == eventID_ );
     350     LOG_IF(info, SEvt::LIFECYCLE ) << " eventID " << eventID ;
     351 
     352     #if defined(WITH_PMTSIM) && defined(POM_DEBUG)
     353         NP* mtda = PMTSim::ModelTrigger_Debug_Array();
     354         std::string name = mtda->get_meta<std::string>("NAME", "MTDA.npy") ;
     355         sev->add_array( name.c_str(), mtda );
     356     #else
     357         LOG(LEVEL) << "not-(WITH_PMTSIM and POM_DEBUG)"  ;
     358     #endif
     359 
     360 
     361     // adding to topfold 
     362     sev->add_array("TRS.npy", U4VolumeMaker::GetTransforms() );
     363     sev->add_array("U4R.npy", MakeMetaArray() );
     364     sev->addEventConfigArray();
     365 
     366     sev->gather() ;             // now gathers into fold, separate from topfold 
     367 
     368     // ~/j/issues/jok-tds-B-side-missing-NPFold-concat.rst 
     369     sev->topfold->concat();         // in this trivial one fold case just copies pointers and arranges skipdelete on fold arrays
     370     sev->topfold->clear_subfold();
     371 
     372     sev->endOfEvent(eventID_);  // does save and clear
     373 
     374     const char* savedir = sev->getSaveDir() ;
     375     LOG(LEVEL) << " savedir " << ( savedir ? savedir : "-" );
     376     SaveMeta(savedir);
     377 
     378 }











FIXED : Bash level using old ALL0, C++ level using ALL0_none::

    P[blyth@localhost J_2025jan08]$ cd jok-tds/
    P[blyth@localhost jok-tds]$ l
    total 0
    0 drwxrwxr-x. 2 blyth blyth 245 Jan  8 17:21 ALL0
    0 drwxr-xr-x. 4 blyth blyth  65 Jan  8 16:49 ALL0_none
    0 drwxrwxr-x. 4 blyth blyth  58 Jan  8 16:27 ..
    0 drwxrwxr-x. 5 blyth blyth  49 Jan  8 16:15 .
    0 drwxr-xr-x. 2 blyth blyth  71 Jan  8 16:15 salloc
    P[blyth@localhost jok-tds]$ l ALL0/
    total 46784
       4 -rw-r--r--. 1 blyth blyth     455 Jan  8 17:21 sample_detsim_user.root
    2824 -rw-r--r--. 1 blyth blyth 2889670 Jan  8 17:21 jok-tds.log
       0 drwxrwxr-x. 2 blyth blyth     245 Jan  8 17:21 .
    4884 -rw-r--r--. 1 blyth blyth 5000147 Jan  8 17:21 jok-tds.1.log
    4884 -rw-r--r--. 1 blyth blyth 5000150 Jan  8 17:21 jok-tds.2.log
    4884 -rw-r--r--. 1 blyth blyth 5000107 Jan  8 17:21 jok-tds.3.log
    4884 -rw-r--r--. 1 blyth blyth 5000046 Jan  8 17:21 jok-tds.4.log
    4884 -rw-r--r--. 1 blyth blyth 5000161 Jan  8 17:21 jok-tds.5.log
    4884 -rw-r--r--. 1 blyth blyth 5000270 Jan  8 17:21 jok-tds.6.log
    4884 -rw-r--r--. 1 blyth blyth 5000163 Jan  8 17:21 jok-tds.7.log
    4884 -rw-r--r--. 1 blyth blyth 5000294 Jan  8 17:21 jok-tds.8.log
    4884 -rw-r--r--. 1 blyth blyth 5000052 Jan  8 17:21 jok-tds.9.log
       0 drwxrwxr-x. 5 blyth blyth      49 Jan  8 16:15 ..
    P[blyth@localhost jok-tds]$ 



Before doing sev->topfold->concat() on the B side are left with the f000 subfold::

    P[blyth@localhost J_2025jan08]$ l jok-tds/
    total 0
    0 drwxrwxr-x. 2 blyth blyth 245 Jan  8 17:21 ALL0
    0 drwxr-xr-x. 4 blyth blyth  65 Jan  8 16:49 ALL0_none
    0 drwxrwxr-x. 4 blyth blyth  58 Jan  8 16:27 ..
    0 drwxrwxr-x. 5 blyth blyth  49 Jan  8 16:15 .
    0 drwxr-xr-x. 2 blyth blyth  71 Jan  8 16:15 salloc


    P[blyth@localhost J_2025jan08]$ l jok-tds/ALL0_none/
    total 12
    4 -rw-rw-r--. 1 blyth blyth 1791 Jan  8 17:21 run_meta.txt
    4 -rw-rw-r--. 1 blyth blyth  132 Jan  8 17:21 run.npy
    4 drwxr-xr-x. 2 blyth blyth 4096 Jan  8 16:49 A000
    0 drwxr-xr-x. 4 blyth blyth   65 Jan  8 16:49 .
    0 drwxrwxr-x. 5 blyth blyth   49 Jan  8 16:15 ..
    0 drwxr-xr-x. 3 blyth blyth  130 Jan  8 16:15 B000


    P[blyth@localhost J_2025jan08]$ l jok-tds/ALL0_none/A000/
    total 21884
        4 -rw-rw-r--. 1 blyth blyth      671 Jan  8 17:21 NPFold_meta.txt
        0 -rw-rw-r--. 1 blyth blyth        0 Jan  8 17:21 NPFold_names.txt
        4 -rw-rw-r--. 1 blyth blyth      143 Jan  8 17:21 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Jan  8 17:21 sframe.npy
        4 -rw-rw-r--. 1 blyth blyth      256 Jan  8 17:21 domain.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  8 17:21 inphoton.npy
        4 -rw-rw-r--. 1 blyth blyth      102 Jan  8 17:21 NPFold_index.txt
       40 -rw-rw-r--. 1 blyth blyth    40128 Jan  8 17:21 seqnib.npy
        4 -rw-rw-r--. 1 blyth blyth      260 Jan  8 17:21 seqnib_table.npy
      232 -rw-rw-r--. 1 blyth blyth   237056 Jan  8 17:21 hit.npy
      316 -rw-rw-r--. 1 blyth blyth   320128 Jan  8 17:21 seq.npy
        4 -rw-rw-r--. 1 blyth blyth       36 Jan  8 17:21 record_meta.txt
    20004 -rw-rw-r--. 1 blyth blyth 20480144 Jan  8 17:21 record.npy
        4 -rw-rw-r--. 1 blyth blyth      224 Jan  8 17:21 genstep.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  8 17:21 photon.npy
        4 drwxr-xr-x. 2 blyth blyth     4096 Jan  8 16:49 .
        0 drwxr-xr-x. 4 blyth blyth       65 Jan  8 16:49 ..
    P[blyth@localhost J_2025jan08]$ l jok-tds/ALL0_none/B000/
    total 16
    4 -rw-rw-r--. 1 blyth blyth 1696 Jan  8 17:21 NPFold_meta.txt
    0 -rw-rw-r--. 1 blyth blyth    0 Jan  8 17:21 NPFold_names.txt
    4 -rw-rw-r--. 1 blyth blyth  143 Jan  8 17:21 sframe_meta.txt
    4 -rw-rw-r--. 1 blyth blyth  384 Jan  8 17:21 sframe.npy
    4 -rw-rw-r--. 1 blyth blyth    5 Jan  8 17:21 NPFold_index.txt
    0 drwxr-xr-x. 4 blyth blyth   65 Jan  8 16:49 ..
    0 drwxr-xr-x. 3 blyth blyth  130 Jan  8 16:15 .
    0 drwxr-xr-x. 2 blyth blyth  185 Jan  8 16:15 f000
    P[blyth@localhost J_2025jan08]$ l jok-tds/ALL0_none/B000/f000/
    total 21592
        4 -rw-rw-r--. 1 blyth blyth       66 Jan  8 17:21 NPFold_index.txt
        0 -rw-rw-r--. 1 blyth blyth        0 Jan  8 17:21 NPFold_names.txt
        4 -rw-rw-r--. 1 blyth blyth      256 Jan  8 17:21 domain.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  8 17:21 inphoton.npy
      316 -rw-rw-r--. 1 blyth blyth   320128 Jan  8 17:21 seq.npy
        4 -rw-rw-r--. 1 blyth blyth       36 Jan  8 17:21 record_meta.txt
    20004 -rw-rw-r--. 1 blyth blyth 20480144 Jan  8 17:21 record.npy
      628 -rw-rw-r--. 1 blyth blyth   640128 Jan  8 17:21 photon.npy
        4 -rw-rw-r--. 1 blyth blyth      224 Jan  8 17:21 genstep.npy
        0 drwxr-xr-x. 2 blyth blyth      185 Jan  8 16:15 .
        0 drwxr-xr-x. 3 blyth blyth      130 Jan  8 16:15 ..
    P[blyth@localhost J_2025jan08]$ 




::

    2025-01-08 17:21:36.463 INFO  [116647] [SEvt::save@3995] SEvt::descSaveDir dir_ $TMP/GEOM/$GEOM/$ExecutableName dir  /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_none/A000 reldir ALL${VERSION:-0}_${OPTICKS_EVENT_NAME:-none} SEventConfig::_EventReldirDefault ALL${VERSION:-0}_${OPTICKS_EVENT_NAME:-none} with_index Y index 0 this 0xb139060

    2025-01-08 17:21:36.463 INFO  [116647] [SEvt::save@3997] [ save_fold.save /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_none/A000
    2025-01-08 17:21:36.480 INFO  [116647] [SEvt::save@3999] ] save_fold.save /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_none/A000
    2025-01-08 17:21:36.480 INFO  [116647] [SEvt::saveFrame@4025] [ dir /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_none/A000
    2025-01-08 17:21:36.481 INFO  [116647] [SEvt::saveFrame@4027] ] dir /data/blyth/opticks/GEOM/J_2025jan08/jok-tds/ALL0_none/A000



