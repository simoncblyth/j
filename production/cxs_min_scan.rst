cxs_min_scan
===============


StandardFullDebug writing GB
--------------------------------

::

    N[blyth@localhost ALL]$ du -hs *
    8.0K	CSGOptiXSMTest.log
    338M	p001
    669M	p002
    999M	p003
    1.3G	p004
    1.7G	p005
    2.0G	p006
    2.3G	p007
    2.6G	p008
    3.0G	p009
    3.3G	p010
    4.0K	run_meta.txt
    4.0K	run.npy
    N[blyth@localhost ALL]$ 


::

    2023-11-29 17:30:00.050 INFO  [343034] [SEvt::SaveRunMeta@1408]  base - dir /home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL
    sstampfold_report
    NPFold::LoadNoData("/home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/ALL")
    [sstampfold_report.run (1, )
     sstampfold_report.run.descMetaKVS 
    NP::descMetaKVS
               SEvt__Init_RUN_META :         1701250008635076,60496,4156    2023-11-29T17:26:48.635076           0                        
                  SEvt__BeginOfRun :    1701250011035527,7587228,1281204    2023-11-29T17:26:51.035527   2,400,451           0   2,400,451
     SEvt__beginOfEvent_FIRST_EGPU :    1701250011035620,7587228,1281244    2023-11-29T17:26:51.035620   2,400,544          93          93
        SEvt__endOfEvent_LAST_EGPU :   1701250200049742,12436892,1286572    2023-11-29T17:30:00.049742 191,414,666 189,014,215 189,014,122
                    SEvt__EndOfRun :   1701250200049946,12436892,1286572    2023-11-29T17:30:00.049946 191,414,870 189,014,419         204
    ]sstampfold_report.run 
    NPFold::subfold_summary k [b] v [//n] sub NO 
    NPX::BOA ABORT A or B null 
     A (10, 16, )
     B -
    NPX::BOA
     A (10, 16, )
     B -
    [NPFold::compare_subarray key delta_substamp asym a bsym b af YES bf NO  a YES b NO  a_subcount YES b_subcount NO  boa NO 
    -NPFold::compare_subarray.a_subcount
    NP::descTable_ (10, 9, )
                       domain     flat  genstep      hit   photon      prd   record      seq      tag
              //p001        2   100000        1    22216   100000   100000   100000   100000   100000
              //p002        2   200000        1    44419   200000   200000   200000   200000   200000
              //p003        2   300000        1    66591   300000   300000   300000   300000   300000
              //p004        2   400000        1    89001   400000   400000   400000   400000   400000
              //p005        2   500000        1   111435   500000   500000   500000   500000   500000
              //p006        2   600000        1   133792   600000   600000   600000   600000   600000
              //p007        2   700000        1   156315   700000   700000   700000   700000   700000
              //p008        2   800000        1   178615   800000   800000   800000   800000   800000
              //p009        2   900000        1   200850   900000   900000   900000   900000   900000
              //p010        2  1000000        1   223036  1000000  1000000  1000000  1000000  1000000

    -NPFold::compare_subarray.b_subcount
    -
    -NPFold::compare_subarray.a
    NP::descTable_ (10, 16, )
                        SbOE0    SbOE1    SeOE0     tBOE     tsG0     tsG1     tsG2     tsG3     tsG4     tsG5     tsG6     tsG7     tsG8     tPrL     tPoL     tEOE
              //p001        0      148    70429       42      191      207      212      213      510      522      541      723    11599    11600    70361    70488
              //p002        0      217   110813       88      264      277      281      282      283      337      360      549      557      557   110743   110869
              //p003        0      243   157696      106      291      303      306      307      308      360      421      981      990      990   157623   157766
              //p004        0      238   214091       91      283      297      301      301      302      352      378      606      614      614   213935   214279
              //p005        0      243   256382       90      289      307      310      310      312      397      424      654      662      662   256214   256552
              //p006        0      233   292007       92      280      294      297      298      299      407      456      789      798      799   291947   292066
              //p007        0      230   350015       92      275      287      291      291      293     4468     4507     4810     4819     4820   349959   350077
              //p008        0      225   355640       88      272      284      288      288      289      338      364      588      595      595   355579   355699
              //p009        0      591   421782       91      643      656      660      660      662     4750     4804     5121     5130     5131   421681   421846
              //p010        0      234   469452       96      283      296      300      300      302    13898    13931    14169    14178    14178   469361   469515

       SbOE0 : SEvt__beginOfEvent_0
       SbOE1 : SEvt__beginOfEvent_1
       SeOE0 : SEvt__endOfEvent_0
        tBOE : t_BeginOfEvent
        tsG0 : t_setGenstep_0
        tsG1 : t_setGenstep_1
        tsG2 : t_setGenstep_2
        tsG3 : t_setGenstep_3
        tsG4 : t_setGenstep_4
        tsG5 : t_setGenstep_5
        tsG6 : t_setGenstep_6
        tsG7 : t_setGenstep_7
        tsG8 : t_setGenstep_8
        tPrL : t_PreLaunch
        tPoL : t_PostLaunch
        tEOE : t_EndOfEvent

    -NPFold::compare_subarray.b
    -
    -NPFold::compare_subarray.boa 
    -
    ]NPFold::compare_subarray
    NPFold::save("$FOLD")
     resolved to  [/home/blyth/tmp/GEOM/J23_1_0_rc3_ok0/CSGOptiXSMTest/sstampfold_report]



Changing cxs_min.sh VERSION not writing to ALL${VERSION} dir
----------------------------------------------------------------


Try changing DEFAULT_RELDIR::

    1625 // SetReldir can be used with the default SEvt::save() changing the last directory element before the index if present
    1626 
    1627 const char* SEvt::DEFAULT_RELDIR = "ALL${VERSION:-0}" ;
    1628 const char* SEvt::RELDIR = nullptr ;
    1629 void        SEvt::SetReldir(const char* reldir_){ RELDIR = reldir_ ? strdup(reldir_) : nullptr ; }
    1630 const char* SEvt::GetReldir(){ return RELDIR ? RELDIR : DEFAULT_RELDIR ; }
    1631 


::

    BP=SEvt::SEvt ~/opticks/CSGOptiX/cxs_min.sh

    Thread 1 "CSGOptiXSMTest" hit Breakpoint 1, 0x00007ffff718df60 in SEvt::SEvt()@plt () from /data/blyth/junotop/ExternalLibs/opticks/head/lib/../lib64/libSysRap.so
    (gdb) bt
    #0  0x00007ffff718df60 in SEvt::SEvt()@plt () from /data/blyth/junotop/ExternalLibs/opticks/head/lib/../lib64/libSysRap.so
    #1  0x00007ffff7249c0e in SEvt::Create (idx=0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:997
    #2  0x00007ffff7249f79 in SEvt::CreateOrReuse (idx=0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1055
    #3  0x00007ffff724a379 in SEvt::CreateOrReuse () at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1101
    #4  0x00007ffff7c22c2e in CSGFoundry::AfterLoadOrCreate () at /home/blyth/junotop/opticks/CSG/CSGFoundry.cc:3432
    #5  0x00007ffff7c2053d in CSGFoundry::Load () at /home/blyth/junotop/opticks/CSG/CSGFoundry.cc:2868
    #6  0x00007ffff7e998a2 in CSGOptiX::SimulateMain () at /home/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:172
    #7  0x0000000000405b15 in main (argc=1, argv=0x7fffffff2148) at /home/blyth/junotop/opticks/CSGOptiX/tests/CSGOptiXSMTest.cc:13
    (gdb) 

    (gdb) f 7
    #7  0x0000000000405b15 in main (argc=1, argv=0x7fffffff2148) at /home/blyth/junotop/opticks/CSGOptiX/tests/CSGOptiXSMTest.cc:13
    13	    CSGOptiX::SimulateMain(); 
    (gdb) f 6
    #6  0x00007ffff7e998a2 in CSGOptiX::SimulateMain () at /home/blyth/junotop/opticks/CSGOptiX/CSGOptiX.cc:172
    172	    CSGFoundry* fd = CSGFoundry::Load(); 
    (gdb) f 5
    #5  0x00007ffff7c2053d in CSGFoundry::Load () at /home/blyth/junotop/opticks/CSG/CSGFoundry.cc:2868
    2868	    AfterLoadOrCreate(); 
    (gdb) f 4
    #4  0x00007ffff7c22c2e in CSGFoundry::AfterLoadOrCreate () at /home/blyth/junotop/opticks/CSG/CSGFoundry.cc:3432
    3432	    SEvt::CreateOrReuse() ;   // creates 1/2 SEvt depending on OPTICKS_INTEGRATION_MODE
    (gdb) f 3
    #3  0x00007ffff724a379 in SEvt::CreateOrReuse () at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1101
    1101	        CreateOrReuse(EGPU); 
    (gdb) f 2
    #2  0x00007ffff7249f79 in SEvt::CreateOrReuse (idx=0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:1055
    1055	    SEvt* evt = Exists(idx) ? Get(idx) : Create(idx) ; 
    (gdb) f 1
    #1  0x00007ffff7249c0e in SEvt::Create (idx=0) at /home/blyth/junotop/opticks/sysrap/SEvt.cc:997
    997	    SEvt* evt = new SEvt ; 
    (gdb) 





