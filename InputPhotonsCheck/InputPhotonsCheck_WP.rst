InputPhotonsCheck_WP
=======================

::

    153     elif [ "$TEST" == "WP_PMT" ]; then
    154 
    155        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    156        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    157        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    158        observation="B side sees no hits, like diff geom, TODO:try B side simtrace"




FIXED : Issue : no intersects on B side for WP_PMT 
-------------------------------------------------------

* Problem was with WaterPoolConstruction::inject in CONFIG:3 theLV was not appropriate
  fix branch blyth-WaterPoolConstruction-fix-theLV-injection-bug-for-HIERARCHY-CONFIG

* Following fix observe 10% more SA for A for WP PMTs :doc:`InputPhotonsCheck/InputPhotonsCheck_WP_10percent_more_SA_for_A`

* lack of identity info on B side makes this difficult to debug from record and photon arrays :
  actually with severely broken geometry identity info not much help



Big gun : U4Recorder__EndOfRunAction_Simtrace
------------------------------------------------

::

     091 const bool U4Recorder::EndOfRunAction_Simtrace = ssys::getenvbool("U4Recorder__EndOfRunAction_Simtrace") ;


     310 void U4Recorder::setU4Tree(const U4Tree* _tree)
     311 {
     312     tree = _tree ;
     313 }
     314 
     315 
     316 
     317 void U4Recorder::BeginOfRunAction(const G4Run*)
     318 {
     319     LOG(LEVEL);
     320 }
     321 
     322 /**
     323 U4Recorder::EndOfRunAction
     324 ---------------------------
     325 
     326 **/
     327 void U4Recorder::EndOfRunAction(const G4Run*)
     328 {
     329     SEvt::SetRunMeta<int>("FAKES_SKIP", int(FAKES_SKIP) );
     330 
     331 
     332     LOG(LEVEL)
     333         << "[ U4Recorder__EndOfRunAction_Simtrace : " << ( EndOfRunAction_Simtrace ? "YES" : "NO " )
     334         ;
     335 
     336     if(EndOfRunAction_Simtrace)
     337     {
     338         U4Simtrace::EndOfRunAction(tree) ;
     339     }
     340 
     341     LOG(LEVEL)
     342         << "] U4Recorder__EndOfRunAction_Simtrace : " << ( EndOfRunAction_Simtrace ? "YES" : "NO " )
     343         ;
     344 }



     40 inline void U4Simtrace::Scan(const U4Tree* tree)
     41 {
     42     int level = ssys::getenvint(U4Simtrace__level, 0);
     43 
     44     int eventID = 998 ;
     45 
     46     SEvt* evt = SEvt::CreateSimtraceEvent();
     47     evt->beginOfEvent(eventID);
     48 
     49     int num_simtrace = int(evt->simtrace.size()) ;
     50     if(level > 0) std::cout << "[U4Simtrace::Scan num_simtrace " << num_simtrace <<  "\n" ;
     51 
     52     U4Navigator nav(tree);
     53 
     54     for(int i=0 ; i < num_simtrace ; i++)
     55     {
     56         quad4& p = evt->simtrace[i] ;
     57         nav.simtrace(p);
     58         if( level > 1 && i % 1000 == 0 ) std::cout << "-U4Simtrace::Scan " << nav.isect.desc() << "\n" ;
     59     }
     60     if(level > 0) std::cout << "-U4Simtrace::Scan nav.stats.desc\n" << nav.stats.desc() << "\n" ;
     61 
     62 
     63     evt->gather();        // follow QSim::simulate
     64     evt->topfold->concat();
     65     evt->topfold->clear_subfold();
     66 
     67     evt->endOfEvent(eventID);
     68 
     69     if(level > 0) std::cout << "]U4Simtrace::Scan num_simtrace " << num_simtrace <<  "\n" ;
     70 }





HMM doing simtrace after an input photon run asserts... FIXED: make simtrace running ignore input photons
---------------------------------------------------------------------------------------------------------------

::
    
    TEST=WP_PMT ipc

::

    153     elif [ "$TEST" == "WP_PMT" ]; then
    154 
    155        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    156        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    157        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    158        observation="B side sees no hits, like diff geom, WIP:B side simtrace"
    159 
    160        export U4Recorder__EndOfRunAction_Simtrace=1   ## CONFIG B SIDE SIMTRACE RUNNING 
    161        export U4Simtrace__level=2



U4Simtrace.h
----------------

::

    [U4Simtrace::Scan num_simtrace 627000
    -U4Simtrace::Scan  t    243.847 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t    191.493 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t   1137.920 valid YES nidx    67472 prim   1952 prn GLb2.equ_FlangeI_Web_FlangeII pv0 pOuterWaterInCD pv1 GLb2.equ_HBeam_phys so1 GLb2.equ_FlangeI_Web_FlangeII
    -U4Simtrace::Scan  t    196.329 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t   1391.094 valid YES nidx    67825 prim   2305 prn sInnerReflectorInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pInnerReflector so1 sInnerReflectorInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t    129.171 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t    149.218 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t   1051.329 valid YES nidx    67472 prim   1952 prn GLb2.equ_FlangeI_Web_FlangeII pv0 pOuterWaterInCD pv1 GLb2.equ_HBeam_phys so1 GLb2.equ_FlangeI_Web_FlangeII
    -U4Simtrace::Scan  t  20728.076 valid YES nidx    65724 prim    204 prn sDeadWater_shell pv0 pWaterPool pv1 pDeadWater so1 sDeadWater_shell
    -U4Simtrace::Scan  t  44341.332 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t   1160.103 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t   1124.530 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t   3722.088 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t  23460.886 valid YES nidx    65724 prim    204 prn sDeadWater_shell pv0 pWaterPool pv1 pDeadWater so1 sDeadWater_shell
    -U4Simtrace::Scan  t  42259.146 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t   1277.814 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t  28531.898 valid YES nidx    65724 prim    204 prn sDeadWater_shell pv0 pWaterPool pv1 pDeadWater so1 sDeadWater_shell
    -U4Simtrace::Scan  t   1493.678 valid YES nidx    65726 prim    206 prn sOuterWaterPool pv0 pWaterPool pv1 pWaterPool so1 sOuterWaterPool
    -U4Simtrace::Scan  t  22565.644 valid YES nidx    65724 prim    204 prn sDeadWater_shell pv0 pWaterPool pv1 pDeadWater so1 sDeadWater_shell
    -U4Simtrace::Scan  t    225.499 valid YES nidx    66514 prim    994 prn sOuterWaterInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pOuterWaterInCD so1 sOuterWaterInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t    727.271 valid YES nidx    67825 prim   2305 prn sInnerReflectorInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pInnerReflector so1 sInnerReflectorInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t  24802.953 valid YES nidx    67742 prim   2222 prn GLb3.bt09_FlangeI_Web_FlangeII pv0 pOuterWaterInCD pv1 GLb3.bt09_HBeam_phys so1 GLb3.bt09_FlangeI_Web_FlangeII
    -U4Simtrace::Scan  t   1771.699 valid YES nidx    66513 prim    993 prn sOuterReflectorInCD_TSubWaterDistributor pv0 pOuterWaterInCD pv1 pCentralDetector so1 sOuterReflectorInCD_TSubWaterDistributor
    -U4Simtrace::Scan  t  22852.487 valid YES nidx    67202 prim   1682 prn GLb3.up09_FlangeI_Web_FlangeII pv0 pOuterWaterInCD pv1 GLb3.up09_HBeam_phys so1 GLb3.up09_FlangeI_Web_FlangeII


::

    A[blyth@localhost opticks]$ l /tmp/blyth/opticks/GEOM/J25_4_0_opticks_Debug/InputPhotonsCheck/ALL1_DebugPhilox_3_PMT_20inch_veto:0:1000_RainXZ_Z230_100k_f8/M998/
    total 39264
        0 drwxr-xr-x. 2 blyth blyth      157 Jun 25 20:38 .
        4 -rw-r--r--. 1 blyth blyth       25 Jun 25 20:38 NPFold_index.txt
        4 -rw-r--r--. 1 blyth blyth      562 Jun 25 20:38 NPFold_meta.txt
        0 -rw-r--r--. 1 blyth blyth        0 Jun 25 20:38 NPFold_names.txt
        4 -rw-r--r--. 1 blyth blyth      176 Jun 25 20:38 sframe_meta.txt
        4 -rw-r--r--. 1 blyth blyth      384 Jun 25 20:38 sframe.npy
        0 drwxr-xr-x. 5 blyth blyth      137 Jun 25 20:38 ..
       60 -rw-r--r--. 1 blyth blyth    60320 Jun 25 20:38 genstep.npy
    39188 -rw-r--r--. 1 blyth blyth 40128128 Jun 25 20:38 simtrace.npy
    A[blyth@localhost opticks]$ 



Can I simtrace plot without creating yet another simtrace script ?
----------------------------------------------------------------------

YES, use most recent installed simtrace script cxt_min.py from ipcv::

    093     cxtscript=$(which cxt_min.py)

    294 if [ "${arg/cxt}" != "$arg" ]; then
    295    ${IPYTHON:-ipython} --pdb -i $cxtscript
    296    [ $? -ne 0 ] && echo $BASH_SOURCE cxt error
    297 fi


::

   (ok) A[blyth@localhost opticks]$ ls -alst `!!`
    ls -alst `find . -name '*.py' -exec grep -l simtrace {} \;`
    12 -rw-r--r--. 1 blyth blyth  9248 May 29 16:55 ./CSGOptiX/cxt_min.py
     4 -rw-r--r--. 1 blyth blyth  3073 May 29 16:38 ./g4cx/tests/G4CXTest_raindrop_simtrace.py
    36 -rw-r--r--. 1 blyth blyth 36650 May 27 21:19 ./CSG/CSGFoundry.py
    36 -rw-r--r--. 1 blyth blyth 34313 May 27 21:07 ./ana/pvplt.py
     8 -rw-r--r--. 1 blyth blyth  7541 May 21 17:12 ./CSGOptiX/tests/CSGOptiXSimtraceTest.py
    16 -rw-r--r--. 1 blyth blyth 13824 Apr  3 21:16 ./u4/tests/U4SimtraceSimpleTest.py
     8 -rw-r--r--. 1 blyth blyth  7446 Dec 15  2024 ./ana/simtrace_positions.py
     4 -rw-r--r--. 1 blyth blyth  1177 Aug 29  2024 ./u4/tests/U4SimtracePlot.py
    16 -rw-r--r--. 1 blyth blyth 13765 Aug 29  2024 ./u4/tests/U4SimtraceTest.py
     4 -rw-r--r--. 1 blyth blyth   302 Aug 29  2024 ./sysrap/tests/SSimtrace_check.py
     8 -rw-r--r--. 1 blyth blyth  4536 Aug 29  2024 ./g4cx/tests/cf_G4CXSimtraceTest.py
     4 -rw-r--r--. 1 blyth blyth  3019 Aug 29  2024 ./g4cx/tests/G4CXSimtraceMinTest.py
     8 -rw-r--r--. 1 blyth blyth  7862 Aug 29  2024 ./g4cx/tests/G4CXSimtraceTest.py
     4 -rw-r--r--. 1 blyth blyth  1994 Aug 29  2024 ./extg4/tests/X4SimtraceTest.py
    12 -rw-r--r--. 1 blyth blyth  9405 Aug 29  2024 ./extg4/tests/X4IntersectVolumeTest.py
    12 -rw-r--r--. 1 blyth blyth 11339 Aug 29  2024 ./ana/simtrace_plot.py
    16 -rw-r--r--. 1 blyth blyth 13324 Aug 29  2024 ./ana/feature.py
     8 -rw-r--r--. 1 blyth blyth  6138 Aug 29  2024 ./ana/framegensteps.py
     8 -rw-r--r--. 1 blyth blyth  5657 Aug 29  2024 ./CSG/tests/CSGSimtraceTest.py
     4 -rw-r--r--. 1 blyth blyth  1106 Aug 29  2024 ./CSG/tests/CSGIntersectComparisonTest.py
     4 -rw-r--r--. 1 blyth blyth   810 Aug 29  2024 ./CSG/tests/CSGNodeScanTest.py
    (ok) A[blyth@localhost opticks]$ 


The B side simtrace plot needs some work to have some identity color but looks like 
the expected slice through the geometry with GSGRID on the WP_PMT. 

* So the B side simulation mystery remains. 


jcv GtOpticksTool 
-------------------

::

    126     else if( ebyte == sizeof(double) )
    127     {
    128         sphotond p ;   
    129         sphotond::Get(p, m_input_photon, idx );  
    130         post.set(p.pos.x,p.pos.y,p.pos.z,p.time); 
    131         dir.set(p.mom.x, p.mom.y, p.mom.z);  
    132         pol.set(p.pol.x, p.pol.y, p.pol.z);  
    133         wavelength_nm = p.wavelength  ; 
    134     }
    135     else
    136     {
    137         std::cerr
    138             << "GtOpticksTool::add_optical_photon" 
    139             << " FATAL "
    140             << " no input_photon OR invalid type "
    141             << " ebyte " << ebyte 
    142             << std::endl 
    143             ;
    144         assert(0);  
    145     }
    146 
    147     G4double wavelength = wavelength_nm * CLHEP::nm ; 
    148     G4double energy = h_Planck*c_light/wavelength ;
    149 
    150     HepMC::GenVertex* vertex = new HepMC::GenVertex(post) ; 
    151     HepMC::FourVector momentum(dir.x()*energy, dir.y()*energy, dir.z()*energy, energy );  
    152     HepMC::Polarization polarization(pol); 
    153 
    154     int pdg_id = 20022 ; // optical photon 
    155     int status = 1 ;  // ?
    156     HepMC::GenParticle* particle = new HepMC::GenParticle(momentum, pdg_id, status);
    157 
    158     particle->set_polarization(polarization);
    159     vertex->add_particle_out(particle);
    160     event.add_vertex(vertex); 
    161 




HMM nothing special for WP_PMT on B side : perplexing 

* its the same GtOpticksTool code converting input photons into Geant4 ? 
* only geometry that the B side input photons "see" is sOuterWaterPool,
  that could be no-RINDEX SA


BP=C4OpBoundaryProcess::PostStepDoIt ipc env_info_run
---------------------------------------------------------

::

   BP=C4OpBoundaryProcess::PostStepDoIt ipc env_info_run
   BP=C4OpBoundaryProcess::PostStepDoIt ipc run


    (gdb) bt
    #0  0x00007fffc10d1610 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #1  0x00007fffc6727519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #2  0x00007fffc672791b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffc6725154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007fffc673070f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x661ab70, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x65a8e00) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #8  0x00007fffd0af44b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #9  0x00007fffd0af8bbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007fffd0af4054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/sniper/InstallArea/lib64/libSniperKernel.so


Argh after rebuild still not using the Debug Custom4::

egin of Event --> 0

    (gdb) bt
    #0  0x00007fffc10d1610 in C4OpBoundaryProcess::PostStepDoIt(G4Track const&, G4Step const&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so
    #1  0x00007fffc6727519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #2  0x00007fffc672791b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #3  0x00007fffc6725154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #4  0x00007fffc673070f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #5  0x00007fffc676b565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #6  0x00007fffe1a6c68e in G4SvcRunManager::SimulateEvent (this=0x674fde0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #7  0x00007fffd485ed3e in DetSimAlg::execute (this=0x65b31f0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112


Need to change runtime env as well as build env::

    [blyth@localhost InputPhotonsCheck]$ cat /home/blyth/junosw/InstallArea/envset.sh
    #!/bin/bash
    # generated from .gitlab-ci.yml of 
    # .gitlab-ci/oj_helper.sh EMIT_ENVSET

    HERE=$(dirname $(realpath $BASH_SOURCE))
    DEFAULT_PREFIX=$HERE
    PREFIX=${OJ_PREFIX:-$DEFAULT_PREFIX}

    source $PREFIX/ENV.bash             ## define JUNOTOP and JUNO_OPTICKS_PREFIX 
    source $JUNOTOP/setup.sh            ## hookup many JUNOSW externals excluding Opticks
    source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals

    source $PREFIX/bin/opticks_juno.sh  ## oj bash functions 
    oj_geomsetup


Added envset_Debug_custom4.sh with::

    #!/bin/bash
    # generated from .gitlab-ci.yml of 
    # .gitlab-ci/oj_helper.sh EMIT_ENVSET

    HERE=$(dirname $(realpath $BASH_SOURCE))
    DEFAULT_PREFIX=$HERE
    PREFIX=${OJ_PREFIX:-$DEFAULT_PREFIX}

    source $PREFIX/ENV.bash             ## define JUNOTOP and JUNO_OPTICKS_PREFIX 
    source $JUNOTOP/setup.sh            ## hookup many JUNOSW externals excluding Opticks


    #[ non-standard change to use Debug Custom4
        source ~/j/JUNOTOP/JUNOTOP_change_paths.sh
        JUNOTOP_change_paths custom4 /data1/blyth/local/custom4_Debug/0.1.8
    #] non-standard change to use Debug Custom4


    source $JUNO_OPTICKS_PREFIX/bashrc  ## hookup for Opticks and its externals

    source $PREFIX/bin/opticks_juno.sh  ## oj bash functions 
    oj_geomsetup

    export CMAKE_PREFIX_PATH=$PREFIX:${CMAKE_PREFIX_PATH}
    export PATH=$PREFIX/bin:${PATH}
    export LD_LIBRARY_PATH=$PREFIX/lib64:${LD_LIBRARY_PATH}
    export PYTHONPATH=$PREFIX/lib64:${PYTHONPATH}
    export PYTHONPATH=$PREFIX/python:${PYTHONPATH}




::

    (gdb) b 207
    Breakpoint 2 at 0x7fffc10c76fc: file /home/blyth/customgeant4/C4OpBoundaryProcess.cc, line 207.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 2, C4OpBoundaryProcess::PostStepDoIt (this=0x2c801490, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:207
    207	        theStatus = Undefined;
    (gdb) p m_track_label
    $1 = (C4Pho *) 0x2c7caef0
    (gdb) p m_track_label->id
    $2 = 99999
    (gdb) p aTrack
    $3 = (const G4Track &) @0xcebf14a0: {fCurrentStepNumber = 1, fPosition = {static ToleranceTicks = 100, data = {-3466.772558980093, -21370.63377685142, -1022.9566710082902}}, fGlobalTime = 195.59464864719899, fLocalTime = 195.49464864570888, 
      fTrackLength = 0, fParentID = 0, fTrackID = 100000, fVelocity = 216.9098374062423, fpTouchable = {fObj = 0x6735780}, fpNextTouchable = {fObj = 0x6735790}, fpOriginTouchable = {fObj = 0x6735780}, fpDynamicParticle = 0xcebf0e28, fTrackStatus = fAlive, 
      fBelowThreshold = false, fGoodForTracking = false, fStepLength = 42404.712451531181, fWeight = 1, fpStep = 0x6726630, fVtxPosition = {static ToleranceTicks = 100, data = {3319.070068359375, 20460.26171875, 489.7098388671875}}, 
      fVtxMomentumDirection = {static ToleranceTicks = 100, data = {-0.16002567250268995, -0.98646808520195395, -0.035672132233049894}}, fVtxKineticEnergy = 2.817822667394958e-06, fpLVAtVertex = 0xa4ddda0, fpCreatorProcess = 0x0, fCreatorModelIndex = -1, 
      fpUserInformation = 0x2c7caee0, prev_mat = 0xa4b3ef0, groupvel = 0xa4b3ca0, prev_velocity = 216.9098374062423, prev_momentum = 2.817822667394958e-06, is_OpticalPhoton = true, useGivenVelocity = true, fpAuxiliaryTrackInformationMap = 0x0}
    (gdb) 


    Thread 1 "python" hit Breakpoint 7, C4OpBoundaryProcess::PostStepDoIt (this=0x2c801490, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:272
    272	        G4int hNavId = G4ParallelWorldProcess::GetHypNavigatorID();
    (gdb) p theGlobalPoint
    $12 = {static ToleranceTicks = 100, data = {-3466.772558980093, -21370.63377685142, -1022.9566710082902}}
    (gdb) 







Need JUNOSW debug build using debug version of Custom4 external
-------------------------------------------------------------------

Where is the version of Custom4 configured for the local junosw build ?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    163 local_oj_build()
    164 {
    165    : ~/local.sh
    166    export VIP_MODE=oj_build
    167    export VIP_DESC="local OJ build adapting .gitlab-ci.yml Opticks+JUNOSW build, see oj_build func"
    168
    169
    170    : JUNOTOP defines the versions of externals used by both JUNOSW and Opticks
    171    : 2025/06/04
    172    :    JLatest symbolic link no longer latest - currently J25.3.0
    173    :    so follow .gitlab-ci.yml and change the below JUNOTOP to J25.4.0
    174
    175    #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
    176    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
    ...
    184    export JUNO_OFFLINE_OFF=1
    185    export OPTICKS_SETUP_VERBOSE=1
    186
    187    source $JUNOTOP/setup.sh


JUNOTOP/bashrc::

     29 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/CLHEP/2.4.7.1/bashrc
     30 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/xrootd/5.7.3/bashrc
     31 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/ROOT/6.30.08/bashrc
     32 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/HepMC/2.06.11/bashrc
     33 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/bashrc
     34 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8/bashrc
     35 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/genie/3.04.02/bashrc
     36 source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/nuwro/21.09.2/bashrc



What they do::

    if [ -z "${JUNOTOP}" ]; then
    export JUNO_EXTLIB_custom4_HOME=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8
    else
    export JUNO_EXTLIB_custom4_HOME=${JUNOTOP}/ExternalLibs/custom4/0.1.8
    fi

    export PATH=${JUNO_EXTLIB_custom4_HOME}/bin:${PATH}
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_custom4_HOME}/lib:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_custom4_HOME}/lib/pkgconfig:${PKG_CONFIG_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib64 ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_custom4_HOME}/lib64:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib64/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_custom4_HOME}/lib64/pkgconfig:${PKG_CONFIG_PATH}
    fi
    export CPATH=${JUNO_EXTLIB_custom4_HOME}/include:${CPATH}
    export MANPATH=${JUNO_EXTLIB_custom4_HOME}/share/man:${MANPATH}

    # For CMake search path
    export CMAKE_PREFIX_PATH=${JUNO_EXTLIB_custom4_HOME}:${CMAKE_PREFIX_PATH}






BP=C4OpBoundaryProcess::PostStepDoIt ipc env_info_run
---------------------------------------------------------


First point in PostStepDoIt is on the other side::


    gdb) p m_track_label->id
    $2 = 99999
    (gdb) p aTrack
    $3 = (const G4Track &) @0xcebf14a0: {fCurrentStepNumber = 1, fPosition = {static ToleranceTicks = 100, data = {-3466.772558980093, -21370.63377685142, -1022.9566710082902}}, fGlobalTime = 195.59464864719899, fLocalTime = 195.49464864570888, 
      fTrackLength = 0, fParentID = 0, fTrackID = 100000, fVelocity = 216.9098374062423, fpTouchable = {fObj = 0x6735780}, fpNextTouchable = {fObj = 0x6735790}, fpOriginTouchable = {fObj = 0x6735780}, fpDynamicParticle = 0xcebf0e28, fTrackStatus = fAlive, 
      fBelowThreshold = false, fGoodForTracking = false, fStepLength = 42404.712451531181, fWeight = 1, fpStep = 0x6726630, fVtxPosition = {static ToleranceTicks = 100, data = {3319.070068359375, 20460.26171875, 489.7098388671875}}, 
      fVtxMomentumDirection = {static ToleranceTicks = 100, data = {-0.16002567250268995, -0.98646808520195395, -0.035672132233049894}}, fVtxKineticEnergy = 2.817822667394958e-06, fpLVAtVertex = 0xa4ddda0, fpCreatorProcess = 0x0, fCreatorModelIndex = -1, 
      fpUserInformation = 0x2c7caee0, prev_mat = 0xa4b3ef0, groupvel = 0xa4b3ca0, prev_velocity = 216.9098374062423, prev_momentum = 2.817822667394958e-06, is_OpticalPhoton = true, useGivenVelocity = true, fpAuxiliaryTrackInformationMap = 0x0}
    (gdb) p aTrack.prev_mat
    $4 = (G4Material *) 0xa4b3ef0



    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 7, C4OpBoundaryProcess::PostStepDoIt (this=0x2c801490, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:272
    272	        G4int hNavId = G4ParallelWorldProcess::GetHypNavigatorID();
    (gdb) p theGlobalPoint
    $12 = {static ToleranceTicks = 100, data = {-3466.772558980093, -21370.63377685142, -1022.9566710082902}}
    (gdb) b 300



    Thread 1 "python" hit Breakpoint 8, C4OpBoundaryProcess::PostStepDoIt (this=0x2c801490, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:300
    300	        if (valid) {
    (gdb) p haveEnteredDaughter
    $13 = false
    (gdb) p theRecoveredNormal
    $14 = {static ToleranceTicks = 100, data = {-0.16012806277044306, -0.98709624835341414, -0}}
    (gdb) 


    (gdb) p Rindex1
    $18 = 1.3529723513319996
    (gdb) 


    (gdb) p Rindex
    $29 = (G4MaterialPropertyVector *) 0x0
    (gdb) b 596
    Breakpoint 20 at 0x7fffc10c8b4c: file /home/blyth/customgeant4/C4OpBoundaryProcess.cc, line 596.
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 20, C4OpBoundaryProcess::PostStepDoIt (this=0x2c801490, aTrack=..., aStep=...) at /home/blyth/customgeant4/C4OpBoundaryProcess.cc:596
    596	                 return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
    (gdb) p theStatus
    $30 = NoRINDEX
    (gdb) 



::

    (gdb) p m_track_label
    $31 = (C4Pho *) 0x2c7caef0
    (gdb) p m_track_label->id
    $32 = 99998
    (gdb) p aTrack
    $33 = (const G4Track &) @0xcebf12a0: {fCurrentStepNumber = 1, fPosition = {static ToleranceTicks = 100, data = {-3466.772558980093, -21370.63377685142, -1022.9516661254777}}, fGlobalTime = 195.59464864719899, 
      fLocalTime = 195.49464864570888, fTrackLength = 0, fParentID = 0, fTrackID = 99999, fVelocity = 216.9098374062423, fpTouchable = {fObj = 0x67357a0}, fpNextTouchable = {fObj = 0x6735780}, fpOriginTouchable = {fObj = 0x67357a0}, 
      fpDynamicParticle = 0xcebf0d90, fTrackStatus = fAlive, fBelowThreshold = false, fGoodForTracking = false, fStepLength = 42404.712451531181, fWeight = 1, fpStep = 0x6726630, fVtxPosition = {static ToleranceTicks = 100, data = {
          3319.070068359375, 20460.26171875, 489.71484375}}, fVtxMomentumDirection = {static ToleranceTicks = 100, data = {-0.16002567250268995, -0.98646808520195395, -0.035672132233049894}}, fVtxKineticEnergy = 2.817822667394958e-06, 
      fpLVAtVertex = 0xa4ddda0, fpCreatorProcess = 0x0, fCreatorModelIndex = -1, fpUserInformation = 0x2c7caee0, prev_mat = 0xa4b3ef0, groupvel = 0xa4b3ca0, prev_velocity = 216.9098374062423, prev_momentum = 2.817822667394958e-06, 
      is_OpticalPhoton = true, useGivenVelocity = true, fpAuxiliaryTrackInformationMap = 0x0}
    (gdb) 







Getting ZERO B side hits : looks like different (empty) geometry on B side ? 
------------------------------------------------------------------------------

::

    
    In [4]: a.f.inphoton[0]
    Out[4]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

    In [5]: b.f.inphoton[0]
    Out[5]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [   -0.16 ,    -0.986,    -0.036,     0.   ],
           [   -0.987,     0.16 ,     0.   ,   440.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)

    In [6]: np.all( a.f.inphoton == b.f.inphoton )
    Out[6]: np.True_


    vn [14]: a.f.record[0,:5,0]
    Out[14]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [ 3310.461, 20407.191,   988.109,     0.22 ],
           [ 3289.384, 20277.26 ,   983.411,     0.827],
           [ 3287.088, 20263.111,   980.263,     0.903],
           [ 3285.897, 20255.768,   980.413,     0.937]], dtype=float32)

    In [17]: b.f.record[0,:5,0]
    Out[17]: 
    array([[ 3316.214, 20442.654,   989.392,     0.1  ],
           [ -523.403, -3226.422,   133.483,   110.716],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ],
           [    0.   ,     0.   ,     0.   ,     0.   ]], dtype=float32)




    In [15]: a.f.record[0,:5,1]
    Out[15]: 
    array([[-0.16 , -0.986, -0.036,  0.   ],
           [-0.16 , -0.986, -0.036,  0.   ],
           [-0.156, -0.964, -0.214,  0.   ],
           [-0.16 , -0.987,  0.02 ,  0.   ],
           [-0.156, -0.964, -0.216,  0.   ]], dtype=float32)

    In [20]: b.f.record[0,:5,1]
    Out[20]: 
    array([[-0.16 , -0.986, -0.036,  0.   ],
           [-0.16 , -0.986, -0.036,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ],
           [ 0.   ,  0.   ,  0.   ,  0.   ]], dtype=float32)



identity for PMT_20inch_veto:0:1000  that is 1+pmtid : 1+50000+1000
-----------------------------------------------------------------------

::

    In [35]:  a.f.record[:,:12,3,1].view(np.int32)
    Out[35]: 
    array([[    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ..., 51001, 51001, 51001, 51001, 51001],
           ...,
           [    0, 51001, 51001, 51001, 51001, ..., 51001, 51001, 51001, 51001, 51001],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0],
           [    0, 51001,     0,     0,     0, ...,     0,     0,     0,     0,     0],
           [    0, 51001, 51001, 51001, 51001, ...,     0,     0,     0,     0,     0]], shape=(100000, 12), dtype=int32)


    In [38]: np.all( b.f.record[:,:12,3,1].view(np.int32) == 0 )
    Out[38]: np.True_


iindex
---------

::

    In [30]: a.f.record[:,:12,1,3].view(np.int32)
    Out[30]: 
    array([[    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ..., 44213, 44213, 44213, 44213, 44213],
           ...,
           [    0, 44213, 44213, 44213, 44213, ..., 44213, 44213, 44213, 44213, 44213],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0],
           [    0, 44213,     0,     0,     0, ...,     0,     0,     0,     0,     0],
           [    0, 44213, 44213, 44213, 44213, ...,     0,     0,     0,     0,     0]], shape=(100000, 12), dtype=int32)

    In [31]: a.q
    Out[31]: 
    array([[b'TO BT BT BT BT EX                                                                               '],
           [b'TO BT BT BT BT EC                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BR BT BT BR BT BT BT EX                                                             '],
           ...,
           [b'TO BT BT BT BR BT BT BR BT BT BT SA                                                             '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BT BT BT BT SA                                                                               '],
           [b'TO BR SA                                                                                        '],
           [b'TO BT BT BT BT EC                                                                               ']], shape=(100000, 1), dtype='|S96')


    ## HMM iindex not set on B side anyhow ? 

    In [33]: b.f.record[:,:,1,3].view(np.int32).max()
    Out[33]: np.int32(0)

    In [34]: b.f.record[:,:,1,3].view(np.int32).min()
    Out[34]: np.int32(0)

    In [10]: b.q
    Out[10]: 
    array([[b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           ...,
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO AB                                                                                           '],
           [b'TO SA                                                                                           '],
           [b'TO SA                                                                                           ']], shape=(100000, 1), dtype='|S96')







try changing WaterPoolConstruction_CONFIG
--------------------------------------------


::

    084 if [ "${arg/env}" != "$arg" ]; then
     85 
     86     ## see A:~/.bashrc oj_build + oj_local
     87 
     88     ##source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/2025_06_01/envset.sh
     89     ##source /home/blyth/junosw/InstallArea/envset.sh
     90     source /home/blyth/junosw/InstallArea/envset_Debug_custom4.sh
     91 
     92 
     93     ASIS=0
     94     ZERO_HOLES=1
     95     MULTIUNION_HOLES=2
     96     HIERARCHY=3
     97 
     98     #export WaterPoolConstruction__CONFIG=$HIERARCHY  # HIERARCHY is set by oj_geomsetup
     99     export WaterPoolConstruction__CONFIG=$ASIS        # override 
    100 


::

     ipc env_info_run_cxt



ASIS : crashes in geometry conversion of lvid:18 with enormous backtrace
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::


    [U4Tree::initSolids
    sn::increase_zmax_ lvid 18 _zmax -21652.00 dz    1.00 new_zmax -21651.00
    sn::increase_zmax_ lvid 18 _zmax 21652.00 dz    1.00 new_zmax 21653.00
    sn::setBB BAD BOUNDING BOX 
     x0 -0 x1 0
     y0 -0 y1 0
     z0 -21750 z1 -21652
    python: /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2674: void sn::setBB(double, double, double, double, double, double): Assertion `!bad_bbox' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc10106dc in sn::setBB (this=0xc6f6a50, x0=-0, y0=-0, z0=-21750, x1=0, y1=0, z1=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2674
    #6  0x00007fffc1011080 in sn::Cylinder (radius=0, z1=-21750, z2=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2802
    #7  0x00007fffc0fd8172 in U4Polycone::collectPrims (this=0x7ffffffe17b0, prims=std::vector of length 0, capacity 0, outside=false) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:455
    #8  0x00007fffc102be2c in U4Polycone::init_inner (this=0x7ffffffe17b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:401
    #9  0x00007fffc102b756 in U4Polycone::init (this=0x7ffffffe17b0) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:270
    #10 0x00007fffc102b4c1 in U4Polycone::U4Polycone (this=0x7ffffffe17b0, polycone_=0xa4db790, lvid_=18, depth_=64, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:236
    #11 0x00007fffc102aa0a in U4Polycone::Convert (polycone=0xa4db790, lvid=18, depth=64, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:151
    #12 0x00007fffc102e405 in U4Solid::init_Polycone (this=0x7ffffffe1aa0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:797
    #13 0x00007fffc102cc8e in U4Solid::init_Constituents (this=0x7ffffffe1aa0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:400
    #14 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe1aa0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #15 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe1aa0, solid_=0xa4db790, lvid_=18, depth_=64, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #16 0x00007fffc102c91c in U4Solid::Convert (solid=0xa4db790, lvid=18, depth=64, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #17 0x00007fffc102eafd in U4Solid::init_BooleanSolid (this=0x7ffffffe1cc0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:965
    #18 0x00007fffc102e82c in U4Solid::init_SubtractionSolid (this=0x7ffffffe1cc0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:864
    #19 0x00007fffc102ccf0 in U4Solid::init_Constituents (this=0x7ffffffe1cc0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:407
    #20 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe1cc0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #21 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe1cc0, solid_=0xa4dc4a0, lvid_=18, depth_=63, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #22 0x00007fffc102c91c in U4Solid::Convert (solid=0xa4dc4a0, lvid=18, depth=63, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #23 0x00007fffc102eafd in U4Solid::init_BooleanSolid (this=0x7ffffffe1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:965
    #24 0x00007fffc102e82c in U4Solid::init_SubtractionSolid (this=0x7ffffffe1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:864
    #25 0x00007fffc102ccf0 in U4Solid::init_Constituents (this=0x7ffffffe1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:407
    #26 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe1ee0) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #27 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe1ee0, solid_=0xa4dc640, lvid_=18, depth_=62, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #28 0x00007fffc102c91c in U4Solid::Convert (solid=0xa4dc640, lvid=18, depth=62, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #29 0x00007fffc102eafd in U4Solid::init_BooleanSolid (this=0x7ffffffe2100) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:965
    #30 0x00007fffc102e82c in U4Solid::init_SubtractionSolid (this=0x7ffffffe2100) at /data1/blyth/local/opticks_
    ...
    #406 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc28cd40, pv=0xa4daa60) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #407 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc28cd40, pv=0xa4c7230) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #408 0x00007fffc10324cc in U4Tree::initSolids (this=0xc28cd40) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #409 0x00007fffc1030cc0 in U4Tree::init (this=0xc28cd40) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #410 0x00007fffc10306f7 in U4Tree::U4Tree (this=0xc28cd40, st_=0x68cf810, top_=0xa4c7230, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #411 0x00007fffc102fc3e in U4Tree::Create (st=0x68cf810, top=0xa4c7230, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #412 0x00007fffc0fd9fee in G4CXOpticks::setGeometry (this=0xc28cbd0, world=0xa4c7230) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #413 0x00007fffc0fd8919 in G4CXOpticks::SetGeometry (world=0xa4c7230) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #414 0x00007fffc0fd8bc8 in G4CXOpticks::SetGeometry_JUNO (world=0xa4c7230, sd=0xa223960, jpmt=0xc1a85e0, jlut=0xc288fe0) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #415 0x00007fffbdd99ee8 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0xa4c7230, sd=0xa223960, ppd=0x658a010, psd=0x66ecbb0, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #416 0x00007fffbdd5ff76 in LSExpDetectorConstruction::setupOpticks (this=0xa23a3d0, world=0xa4c7230) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:457
    #417 0x00007fffbdd5f816 in LSExpDetectorConstruction::Construct (this=0xa23a3d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:378
    #418 0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #419 0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so


ZERO_HOLES : lvid 18 crash with shorter bt from zero radius cylinder
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc10106dc in sn::setBB (this=0xc6e72e0, x0=-0, y0=-0, z0=-21750, x1=0, y1=0, z1=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2674
    #6  0x00007fffc1011080 in sn::Cylinder (radius=0, z1=-21750, z2=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2802

    zero radius cylinder::

        2797	inline sn* sn::Cylinder(double radius, double z1, double z2) // static
        2798	{   
        2799	    assert( z2 > z1 );  
        2800	    sn* nd = Create(CSG_CYLINDER); 
        2801	    nd->setPA( 0.f, 0.f, 0.f, radius, z1, z2)  ;   
        2802	    nd->setBB( -radius, -radius, z1, +radius, +radius, z2 );
        2803	    return nd ;
        2804	}
        2805	inline sn* sn::Cone(double r1, double z1, double r2, double z2)  // static
        2806	{   
        (gdb) p radius
        $1 = 0
        (gdb) p z1
        $2 = -21750
        (gdb) p z2
        $3 = -21652

        2657	inline void sn::setBB( double x0, double y0, double z0, double x1, double y1, double z1 )
        2658	{
        2659	    bool bad_bbox =  x0 >= x1 || y0 >= y1 || z0 >= z1  ;
        2660	    if(bad_bbox) std::cerr 
        2661	          << "sn::setBB BAD BOUNDING BOX "
        2662	          << "\n"
        2663	          << " x0 " << x0
        2664	          << " x1 " << x1
        (gdb) p x0
        $4 = -0
        (gdb) p x1
        $5 = 0
        (gdb) p x0 > x1
        $6 = false
        (gdb) p y0
        $7 = -0
        (gdb) p y1
        $8 = 0
        (gdb) p y0 > y1
        $9 = false
        (gdb) p z0
        $10 = -21750
        (gdb) p z1
        $11 = -21652
        (gdb) p z0 >= z1
        $12 = false
        (gdb) p x0 >= x1
        $13 = true
        (gdb) p y0 >= y1
        $14 = true
        (gdb) p z0 >= z1
        $15 = false
        (gdb) p x0 == x1
        $16 = true
        (gdb) p y0 == y1
        $17 = true
        (gdb) p z0 == z1
        $18 = false
        (gdb) 







    #7  0x00007fffc0fd8172 in U4Polycone::collectPrims (this=0x7ffffffe9730, prims=std::vector of length 0, capacity 0, outside=false) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:455
    #8  0x00007fffc102be2c in U4Polycone::init_inner (this=0x7ffffffe9730) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:401
    #9  0x00007fffc102b756 in U4Polycone::init (this=0x7ffffffe9730) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:270
    #10 0x00007fffc102b4c1 in U4Polycone::U4Polycone (this=0x7ffffffe9730, polycone_=0xa4db790, lvid_=18, depth_=4, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:236
    #11 0x00007fffc102aa0a in U4Polycone::Convert (polycone=0xa4db790, lvid=18, depth=4, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:151
    #12 0x00007fffc102e405 in U4Solid::init_Polycone (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:797
    #13 0x00007fffc102cc8e in U4Solid::init_Constituents (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:400
    #14 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #15 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe9a20, solid_=0xa4db790, lvid_=18, depth_=4, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #16 0x00007fffc102c91c in U4Solid::Convert (solid=0xa4db790, lvid=18, depth=4, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #17 0x00007fffc102eafd in U4Solid::init_BooleanSolid (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:965
    #18 0x00007fffc102e82c in U4Solid::init_SubtractionSolid (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:864
    #19 0x00007fffc102ccf0 in U4Solid::init_Constituents (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:407
    #20 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #21 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe9c40, solid_=0xa4dc4a0, lvid_=18, depth_=3, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    ...
    #42 0x00007fffc103271e in U4Tree::initSolid (this=0xc27e4d0, lv=0xa4dd5a0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:671
    #43 0x00007fffc10326b4 in U4Tree::initSolids_r (this=0xc27e4d0, pv=0xa4dd650) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:664
    #44 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc27e4d0, pv=0xa52d0d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #45 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc27e4d0, pv=0xa4daa00) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #46 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc27e4d0, pv=0xa4daa60) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #47 0x00007fffc103264f in U4Tree::initSolids_r (this=0xc27e4d0, pv=0xa4c7230) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:661
    #48 0x00007fffc10324cc in U4Tree::initSolids (this=0xc27e4d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:611
    #49 0x00007fffc1030cc0 in U4Tree::init (this=0xc27e4d0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:296
    #50 0x00007fffc10306f7 in U4Tree::U4Tree (this=0xc27e4d0, st_=0x68cf810, top_=0xa4c7230, sid_=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:267
    #51 0x00007fffc102fc3e in U4Tree::Create (st=0x68cf810, top=0xa4c7230, sid=0x0) at /data1/blyth/local/opticks_Debug/include/U4/U4Tree.h:224
    #52 0x00007fffc0fd9fee in G4CXOpticks::setGeometry (this=0xc27e360, world=0xa4c7230) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:302
    #53 0x00007fffc0fd8919 in G4CXOpticks::SetGeometry (world=0xa4c7230) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:70
    #54 0x00007fffc0fd8bc8 in G4CXOpticks::SetGeometry_JUNO (world=0xa4c7230, sd=0xa223960, jpmt=0xc199d70, jlut=0xc27a770) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:108
    #55 0x00007fffbdd99ee8 in LSExpDetectorConstruction_Opticks::Setup (opticksMode=3, world=0xa4c7230, sd=0xa223960, ppd=0x658a010, psd=0x66ecbb0, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:47
    #56 0x00007fffbdd5ff76 in LSExpDetectorConstruction::setupOpticks (this=0xa23a3d0, world=0xa4c7230) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:457
    #57 0x00007fffbdd5f816 in LSExpDetectorConstruction::Construct (this=0xa23a3d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:378
    #58 0x00007fffc680792e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #59 0x00007fffc6807afc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so



MULTUNION_HOLES
~~~~~~~~~~~~~~~~~~

::

    [U4Tree::initSolids
    sn::increase_zmax_ lvid 18 _zmax -21652.00 dz    1.00 new_zmax -21651.00
    sn::increase_zmax_ lvid 18 _zmax 21652.00 dz    1.00 new_zmax 21653.00
    sn::setBB BAD BOUNDING BOX 
     x0 -0 x1 0
     y0 -0 y1 0
     z0 -21750 z1 -21652
    python: /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2674: void sn::setBB(double, double, double, double, double, double): Assertion `!bad_bbox' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-3.el9_5.1.x86_64 freetype-2.10.4-9.el9.alma.2.x86_64 glib2-2.68.4-14.el9_4.1.x86_64 glibc-2.34-125.el9_5.3.alma.1.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-4.el9_5.x86_64 libICE-1.0.10-8.el9.x86_64 libSM-1.2.3-10.el9.x86_64 libX11-1.7.0-9.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-5.el9.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libgcc-11.5.0-5.el9_5.alma.1.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libpsl-0.21.1-5.el9.x86_64 libselinux-3.6-1.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libstdc++-11.5.0-5.el9_5.alma.1.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-20.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.1-2.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9.x86_64 openssl-libs-3.2.2-6.el9_5.1.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748b52c in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743e686 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff74373c6 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc10106dc in sn::setBB (this=0xc6ea890, x0=-0, y0=-0, z0=-21750, x1=0, y1=0, z1=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2674
    #6  0x00007fffc1011080 in sn::Cylinder (radius=0, z1=-21750, z2=-21652) at /data1/blyth/local/opticks_Debug/include/SysRap/sn.h:2802
    #7  0x00007fffc0fd8172 in U4Polycone::collectPrims (this=0x7ffffffe9730, prims=std::vector of length 0, capacity 0, outside=false) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:455
    #8  0x00007fffc102be2c in U4Polycone::init_inner (this=0x7ffffffe9730) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:401
    #9  0x00007fffc102b756 in U4Polycone::init (this=0x7ffffffe9730) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:270
    #10 0x00007fffc102b4c1 in U4Polycone::U4Polycone (this=0x7ffffffe9730, polycone_=0xa4db790, lvid_=18, depth_=4, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:236
    #11 0x00007fffc102aa0a in U4Polycone::Convert (polycone=0xa4db790, lvid=18, depth=4, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Polycone.h:151
    #12 0x00007fffc102e405 in U4Solid::init_Polycone (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:797
    #13 0x00007fffc102cc8e in U4Solid::init_Constituents (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:400
    #14 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe9a20) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #15 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe9a20, solid_=0xa4db790, lvid_=18, depth_=4, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362
    #16 0x00007fffc102c91c in U4Solid::Convert (solid=0xa4db790, lvid=18, depth=4, level=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:343
    #17 0x00007fffc102eafd in U4Solid::init_BooleanSolid (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:965
    #18 0x00007fffc102e82c in U4Solid::init_SubtractionSolid (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:864
    #19 0x00007fffc102ccf0 in U4Solid::init_Constituents (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:407
    #20 0x00007fffc102cb3e in U4Solid::init (this=0x7ffffffe9c40) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:375
    #21 0x00007fffc102ca10 in U4Solid::U4Solid (this=0x7ffffffe9c40, solid_=0xa4dc640, lvid_=18, depth_=3, level_=-1) at /data1/blyth/local/opticks_Debug/include/U4/U4Solid.h:362


