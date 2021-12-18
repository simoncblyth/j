tds-logfile-preservation
===========================

* note that logging gets appended into the python3.8.log 

Hmm the executable name in the current directory could stay as the default LOGPATH,
but also add sensitivity to OPTICKS_LOGPATH ennvar

Hmm but what is really needed is for the logs to end up in geocache. 

::

    164 /**
    165 PLOG::_logpath()
    166 ------------------
    167 
    168 This uses just the executable name with .log appended 
    169 
    170 **/
    171 
    172 const char* PLOG::_logpath()
    173 {
    174     const char* exename = SProc::ExecutableName() ;
    175     std::string lp(exename) ;
    176     lp += ".log" ;
    177     return strdup(lp.c_str());
    178 }



::

    N[blyth@localhost j]$ tds-dir
    /tmp/blyth/opticks/tds
    N[blyth@localhost j]$ tds-cd
    N[blyth@localhost tds]$ pwd
    /tmp/blyth/opticks/tds
    N[blyth@localhost tds]$ l
    total 3372
    3244 -rw-r--r--.  1 blyth blyth 3321245 Dec 18 03:25 python3.8.log
       4 -rw-r--r--.  1 blyth blyth     455 Dec 18 03:25 sample_detsim_user.root
       0 drwxrwxr-x.  2 blyth blyth      84 Dec 18 03:21 .
       4 drwxrwxr-x. 44 blyth blyth    4096 Dec 18 03:04 ..
     120 -rw-r--r--.  1 blyth blyth  119213 Dec 10 22:41 sample_detsim.root
    N[blyth@localhost tds]$ vi python3.8.log
    N[blyth@localhost tds]$ 
    N[blyth@localhost tds]$ python --version
    Python 3.8.12
    N[blyth@localhost tds]$ python -c "import sys ; print(sys.argv[0])"
    -c
    N[blyth@localhost tds]$ 
    N[blyth@localhost tds]$ pwd
    /tmp/blyth/opticks/tds
    N[blyth@localhost tds]$ l
    total 3372
       0 drwxrwxr-x.  2 blyth blyth      84 Dec 18 03:58 .
    3244 -rw-r--r--.  1 blyth blyth 3321245 Dec 18 03:25 python3.8.log
       4 -rw-r--r--.  1 blyth blyth     455 Dec 18 03:25 sample_detsim_user.root
       4 drwxrwxr-x. 44 blyth blyth    4096 Dec 18 03:04 ..
     120 -rw-r--r--.  1 blyth blyth  119213 Dec 10 22:41 sample_detsim.root
    N[blyth@localhost tds]$ 
    N[blyth@localhost tds]$ head -10 python3.8.log
    2021-12-07 03:18:52.441 INFO  [289530] [LSExpDetectorConstruction_Opticks::Setup@87] [ WITH_G4OPTICKS opticksMode 3
    2021-12-07 03:18:52.442 FATAL [289530] [G4Opticks::initSkipGencode@358] OPTICKS_SKIP_GENCODE - m_skip_gencode_count 0
    2021-12-07 03:18:52.442 INFO  [289530] [G4Opticks::G4Opticks@351] ctor : DISABLE FPE detection : as it breaks OptiX launches
    2021-12-07 03:18:52.442 INFO  [289530] [LSExpDetectorConstruction_Opticks::Setup@100]  embedded_commandline_extra --way --pvname pAcrylic --boundary Water///Acrylic --waymask 3 --gdmlkludge
    2021-12-07 03:18:53.378 INFO  [289530] [G4Opticks::InitOpticks@216] 
    # BOpticksKey::export_ 
    export OPTICKS_KEY=DetSim0Svc.X4PhysicalVolume.pWorld.e8da8a0bd500b2e1ec6415cf80aaa266

    2021-12-07 03:18:53.378 INFO  [289530] [G4Opticks::EmbeddedCommandLine@135] Using ecl :[ --compute --embedded --xanalytic --save --natural --printenabled --pindex 0] OPTICKS_EMBEDDED_COMMANDLINE
    2021-12-07 03:18:53.378 INFO  [289530] [G4Opticks::EmbeddedCommandLine@136]  mode(Pro/Dev/Asis) D using "dev" (development) commandline with full event saving 
    N[blyth@localhost tds]$ 

