InputPhotonsCheck_WP
=======================

::

    153     elif [ "$TEST" == "WP_PMT" ]; then
    154 
    155        sevt__input_photon_dir=$HOME/.opticks/InputPhotons
    156        opticks_input_photon=RainXZ_Z230_100k_f8.npy
    157        opticks_input_photon_frame=PMT_20inch_veto:0:1000
    158        observation="B side sees no hits, like diff geom, TODO:try B side simtrace"



Overview
-----------

* lack of identity info on B side makes this difficult to debug from record and photon arrays


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


BP=C4OpBoundaryProcess::PostStepDoIt ipc run
---------------------------------------------

::

   ipc env_info
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








