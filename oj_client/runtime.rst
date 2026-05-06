oj_client/runtime.sh
====================

overview
---------

Initially did the below testing using custom libcurl and custom openssl
BUT : it seems custom openssl is problematic and its better to stick
with the system openssl.  


clean OpticksClient build
-------------------------------

::

    lo_client
    o
    om-cleaninstall


clean OJ build againt OpticksClient : "ljclient ljbb0c"
---------------------------------------------------------

::

    ljclient ljbb0c


single event test of JUNOSW+OpticksClient
-------------------------------------------

After set ENVSET to source the JUNOSW+OpticksClient envset.sh::

    ljrt



runtime env setup
------------------------

Sourcing of JUNOTOP/setup.sh leads to sourcing of the bashrc.sh that invokes loadsa bashrc::

    A[blyth@localhost tests]$ cat /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/bashrc.sh
    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/binutils/2.35.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/go/1.20.6/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junoenv/etc/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Git/2.46.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/git-lfs/3.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Cmake/3.30.5/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-setuptools/69.5.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-pip/23.3.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-cython/3.0.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-numpy/1.26.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libyaml/0.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Xercesc/3.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/fftw3-proxy/3.3.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/eigen/3.4.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/sqlite3/3.38.5/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-c/6.1.9/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/mysql-connector-cpp/1.1.12/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pacparser/1.4.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/frontier/2.10.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HDF5/1.14.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/log4cpp/1.1.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libxml2/2.9.12/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/LHAPDF/6.3.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/pythia6/6.4.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/tbb/2020.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/CLHEP/2.4.7.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/xrootd/5.7.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/ROOT/6.30.08/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/HepMC/2.06.11/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/custom4/0.1.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/genie/3.04.02/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/nuwro/21.09.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/talys/1.95/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gibuu/r2023_02_juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gemini/juno_master_20260408/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libmore/0.8.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libonnxruntime/1.17.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/healpix/3.83/bashrc


buildtime addition of openssl and libcurl externals
-------------------------------------------------------


Added the openssl and libcurl externals via change to local_oj_build::

    local_oj_build()
    {
       : ~/j/local.sh
       export VIP_MODE=oj_build
       export VIP_DESC="local OJ build adapting .gitlab-ci.yml Opticks+JUNOSW build, see oj_build func"


       : JUNOTOP defines the versions of externals used by both JUNOSW
       : Opticks grabs the same versions of those externals it needs
       :
       : 2025/06/04
       :    JLatest symbolic link no longer latest - currently J25.3.0
       :    so follow .gitlab-ci.yml and change the below JUNOTOP to J25.4.0

       export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
       #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0
       source $JUNOTOP/setup.sh

       : sourcing of JUNOTOP/setup.sh leads to sourcing of JUNOTOP/bashrc.sh
       : which results in the sourcing of around 40 bashrc like ExternalLibs/name/name-version/bashrc

       if [ "$JUNO_OPTICKS_CONFIG" == "Client" ]; then
           ## DOES NOT REALY NEED TO BE CONDITIONAL ONCE WORKING
           local_JUNOTOP_client
       fi

       local_JUNOTOP_override  ## potentially changing paths to build against different custom4

       local BASE=/data1/blyth/local

       local juno_opticks_config=Debug
       export JUNO_OPTICKS_CONFIG=${JUNO_OPTICKS_CONFIG:-$juno_opticks_config}

       : JUNO_OPTICKS_CONFIG is input which controls which JUNO_OPTICKS_PREFIX to build against
       unset JUNO_OPTICKS_PREFIX
       case $JUNO_OPTICKS_CONFIG in
         vLatest) export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest ;;
           Debug) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
          Client) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
         Release) export JUNO_OPTICKS_PREFIX=$BASE/opticks_${JUNO_OPTICKS_CONFIG}  ;;
       esac




ljrt shakedown : issue 1 : (SSim)SEvt::sim undefined
---------------------------------------------------------

::

    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-04-28 18:01:27.542 [junoSD_PMT_v2::Initialize eventID 0
    2026-04-28 18:01:27.543 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc0b5f655 in SSim::lookup_mtline (this=0x65646c6f685f6c69, mtindex=1) at /home/blyth/opticks/sysrap/SSim.cc:246
    246	    return tree->lookup_mtline(mtindex);
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 pcre-8.44-4.el9.x86_64 pcre2-10.40-6.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffc0b5f655 in SSim::lookup_mtline (this=0x65646c6f685f6c69, mtindex=1) at /home/blyth/opticks/sysrap/SSim.cc:246
    #1  0x00007fffc0b17b5f in SEvt::addGenstep (this=0xc941470, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2496
    #2  0x00007fffc0b1444a in SEvt::AddGenstep (q=...) at /home/blyth/opticks/sysrap/SEvt.cc:1587
    #3  0x00007fffc0ee147c in U4::CollectGenstep_DsG4Scintillation_r4695 (aTrack=0xbf5b2e80, aStep=0x68c87b0, numPhotons=1, scnt=0, ScintillationTime=4.5999999999999996) at /home/blyth/opticks/u4/U4.cc:183
    #4  0x00007fffbf88aa6e in DsG4Scintillation::PostStepDoIt (this=0x29c8e610, aTrack=..., aStep=...) at /home/blyth/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:601
    #5  0x00007fffc66ea519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffc66ea91b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffc66e8154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffc66f370f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc672e565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x6653e60, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffce08dd2e in DetSimAlg::execute (this=0x6674b80) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #12 0x00007fffd24db4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd24dfbbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd24db054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #16 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5b0d0e0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #21 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #22 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #23 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e5c40, func=0x7ffff76ea200, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #24 PyEval_EvalCode (co=co@entry=0x4f9fa0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40) at Python/ceval.c:1148
    #25 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, co=0x4f9fa0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #26 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76c2dd0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40, flags=flags@entry=0x7ffffffee388, arena=arena@entry=0x7ffff7de2b90)
        at Python/pythonrun.c:1762
    #27 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee388, closeit=<optimized out>, locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, start=257, filename=0x7ffff76c2dd0, fp=0x42c7c0) at Python/pythonrun.c:1657
    #28 _PyRun_SimpleFileObject (fp=fp@entry=0x42c7c0, filename=filename@entry=0x7ffff76c2dd0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee388) at Python/pythonrun.c:440
    #29 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42c7c0, filename=filename@entry=0x7ffff76c2dd0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee388) at Python/pythonrun.c:79
    #30 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76c2dd0, program_name=0x7ffff7e26790) at Modules/main.c:360
    #31 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #32 pymain_run_python (exitcode=0x7ffffffee384) at Modules/main.c:605
    #33 Py_RunMain () at Modules/main.c:684
    #34 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffee490) at Modules/main.c:714
    #35 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #36 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #37 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #38 0x0000000000401075 in _start ()
    (gdb) 




Run again with breakpoint::

    BP=SSim::SSim ljrt


Shows it is being instanciated::

    U::Resolve token [MultiFilmLUTMakerSvc_DIR] does not resolve 
    NP::save failed to U::Resolve path_ $MultiFilmLUTMakerSvc_DIR/multifilm.npy
    2026-04-28 18:09:48.197 INFO  [2308670] [LSExpDetectorConstruction_Opticks::Setup@52] [ WITH_G4CXOPTICKS opticksMode 1 sd 0x65c2d70

    Thread 1 "python" hit Breakpoint 1, SSim::SSim (this=0xc951d60) at /home/blyth/opticks/sysrap/SSim.cc:161
    161	    relp(ssys::getenvvar("SSim__RELP", RELP_DEFAULT )),
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 pcre-8.44-4.el9.x86_64 pcre2-10.40-6.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  SSim::SSim (this=0xc951d60) at /home/blyth/opticks/sysrap/SSim.cc:161
    #1  0x00007fffc0b5ea46 in SSim::Create () at /home/blyth/opticks/sysrap/SSim.cc:97
    #2  0x00007fffc0b5e238 in SSim::CreateOrReuse () at /home/blyth/opticks/sysrap/SSim.cc:43
    #3  0x00007fffc1243064 in G4CXOpticks::SetGeometry_JUNO (world=0xabe4fa0, sd=0x65c2d70, jpmt=0xc8c4640, jlut=0xc951170) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:104
    #4  0x00007fffbfd4520d in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xabe4fa0, sd=0x65c2d70, ppd=0x66d2500, psd=0x66d2f90, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:54
    #5  0x00007fffbfd08eb6 in LSExpDetectorConstruction::setupOpticks (this=0xa7d6e10, world=0xabe4fa0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #6  0x00007fffbfd08756 in LSExpDetectorConstruction::Construct (this=0xa7d6e10) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #7  0x00007fffc67ca92e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007fffc67caafc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x00007fffce08db0b in DetSimAlg::initialize (this=0x65ec010) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #10 0x00007fffd24c5b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd24db09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffd24e3447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd24db048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fc6990, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e5c40, func=0x7ffff7e609a0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co@entry=0x4ddbc0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40) at Python/ceval.c:1148
    #24 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, co=0x4ddbc0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7e611b0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40, flags=flags@entry=0x7ffffffe8ee8, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #26 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffe8ee8, closeit=<optimized out>, locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, start=257, filename=0x7ffff7e611b0, fp=0x408e60) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp@entry=0x408e60, filename=filename@entry=0x7ffff7e611b0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe8ee8) at Python/pythonrun.c:440
    #28 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x408e60, filename=filename@entry=0x7ffff7e611b0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe8ee8) at Python/pythonrun.c:79
    #29 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7e611b0, program_name=0x7ffff7e24b70) at Modules/main.c:360
    #30 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffffffe8ee4) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffe8ff0) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.
    2026-04-28 18:10:17.623 INFO  [2308670] [G4CXOpticks::SetGeometry_JUNO@114]  opticksMode 1 sd 0x65c2d70
    2026-04-28 18:10:17.623 INFO  [2308670] [U4Tree::Create@225] [new U4Tree
    2026-04-28 18:10:17.623 INFO  [2308670] [U4Tree::init@283] -initSid
    2026-04-28 18:10:17.623 INFO  [2308670] [U4Tree::init@285] -initRayleigh


    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc0b5f655 in SSim::lookup_mtline (this=0x65646c6f685f6c69, mtindex=1) at /home/blyth/opticks/sysrap/SSim.cc:246
    246	    return tree->lookup_mtline(mtindex);
    (gdb) p tree
    Cannot access memory at address 0x65646c6f685f6c81
    (gdb) bt
    #0  0x00007fffc0b5f655 in SSim::lookup_mtline (this=0x65646c6f685f6c69, mtindex=1) at /home/blyth/opticks/sysrap/SSim.cc:246
    #1  0x00007fffc0b17b5f in SEvt::addGenstep (this=0xc9551e0, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2496
    #2  0x00007fffc0b1444a in SEvt::AddGenstep (q=...) at /home/blyth/opticks/sysrap/SEvt.cc:1587
    #3  0x00007fffc0ee147c in U4::CollectGenstep_DsG4Scintillation_r4695 (aTrack=0xbf58e790, aStep=0x6789180, numPhotons=1, scnt=0, ScintillationTime=4.5999999999999996) at /home/blyth/opticks/u4/U4.cc:183
    #4  0x00007fffbf88aa6e in DsG4Scintillation::PostStepDoIt (this=0x29012950, aTrack=..., aStep=...) at /home/blyth/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:601
    #5  0x00007fffc66ea519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #6  0x00007fffc66ea91b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #7  0x00007fffc66e8154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #8  0x00007fffc66f370f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #9  0x00007fffc672e565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #10 0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x65d30a0, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #11 0x00007fffce08dd2e in DetSimAlg::execute (this=0x65ec010) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #12 0x00007fffd24db4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd24dfbbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffd24db054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #15 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #16 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #20 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fc6990, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #21 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #22 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #23 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e5c40, func=0x7ffff7e609a0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #24 PyEval_EvalCode (co=co@entry=0x4ddbc0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40) at Python/ceval.c:1148
    #25 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, co=0x4ddbc0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #26 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7e611b0, globals=globals@entry=0x7ffff76e5c40, locals=locals@entry=0x7ffff76e5c40, flags=flags@entry=0x7ffffffe8ee8, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #27 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffe8ee8, closeit=<optimized out>, locals=0x7ffff76e5c40, globals=0x7ffff76e5c40, start=257, filename=0x7ffff7e611b0, fp=0x408e60) at Python/pythonrun.c:1657
    #28 _PyRun_SimpleFileObject (fp=fp@entry=0x408e60, filename=filename@entry=0x7ffff7e611b0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe8ee8) at Python/pythonrun.c:440
    #29 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x408e60, filename=filename@entry=0x7ffff7e611b0, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe8ee8) at Python/pythonrun.c:79
    #30 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7e611b0, program_name=0x7ffff7e24b70) at Modules/main.c:360
    #31 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #32 pymain_run_python (exitcode=0x7ffffffe8ee4) at Modules/main.c:605
    #33 Py_RunMain () at Modules/main.c:684
    #34 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffe8ff0) at Modules/main.c:714
    #35 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #36 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #37 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #38 0x0000000000401075 in _start ()
    (gdb) f 1
    #1  0x00007fffc0b17b5f in SEvt::addGenstep (this=0xc9551e0, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2496
    2496	        matline = sim ? sim->lookup_mtline(mtindex) : 0 ;
    (gdb) p sim
    $1 = (const SSim *) 0x65646c6f685f6c69
    (gdb) 


    (gdb) p (char)0x65
    $3 = 101 'e'
    (gdb) p (char)0x64
    $4 = 100 'd'
    (gdb) p (char)0x6c
    $5 = 108 'l'
    (gdb) p (char)0x6f
    $6 = 111 'o'
    (gdb) p (char)0x68
    $7 = 104 'h'
    (gdb) p (char)0x5f
    $8 = 95 '_'
    (gdb) p (char)0x6c
    $9 = 108 'l'
    (gdb) p (char)0x69
    $10 = 105 'i'
    (gdb) 

::

    edloh_li
    il_holde

::


    A[blyth@localhost opticks]$ find . -type f -exec grep -H il_holde {} \;
    ./CSGOptiX/cxt_min.sh:           ['3275', '3729', '24032', 's_EMFcoil_holder_ring13_seg1'],
    ./notes/issues/stree_MOI_SID_frame_addressing_is_off_by_one_as_revealed_by_the_staked_PMT.rst:           ['3265', '3451', '9066', 's_EMFcoil_holder_ring11_seg1'],
    ./notes/issues/stree_MOI_SID_frame_addressing_is_off_by_one_as_revealed_by_the_staked_PMT.rst:           ['3270', '882', '11085', 's_EMFcoil_holder_ring12_seg1'],
    ./notes/issues/stree_MOI_SID_frame_addressing_is_off_by_one_as_revealed_by_the_staked_PMT.rst:           ['3262', '615', '260030', 's_EMFcoil_holder_ring10_seg1'],
    ./notes/issues/stree_MOI_SID_frame_addressing_is_off_by_one_as_revealed_by_the_staked_PMT.rst:           ['3275', '384', '13283', 's_EMFcoil_holder_ring13_seg1'],
    ./notes/issues/U4Polycone_improve_phicut_error_message.rst:    U4Polycone::init FATAL geometry with unsupported phicut :  enable experimental support with envvar  [U4Polycone__ENABLE_PHICUT] G4Polycone.GetName [s_EMFcoil_holder_ring8_seg1]
    ./notes/issues/U4Polycone_improve_phicut_error_message.rst:    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_pfx_0=s_EMFcoil_holder_ring
    ./notes/issues/U4Polycone_improve_phicut_error_message.rst:    U4Solid::Convert solid.GetName[s_EMFcoil_holder_ring8_seg1] lvid 87 U4Solid__IsFlaggedLVID : YES depth 0 level -1
    ./notes/issues/U4Polycone_improve_phicut_error_message.rst:    [U4Solid::init  87/0/Pol/ -1/1 lvid/depth/tag/root/level s_EMFcoil_holder_ring8_seg1
    ./notes/issues/U4Polycone_improve_phicut_error_message.rst:    U4Polycone::init FATAL geometry with unsupported phicut :  enable experimental support with envvar  [U4Polycone__ENABLE_PHICUT] G4Polycone.GetName [s_EMFcoil_holder_ring8_seg1]
    ./sysrap/tests/sregex_test.sh:export REGEX='s_EMFcoil_holder_ring(_mod)?[0-9]+_seg[0-9]+'  # NB single quote protection from bash
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring25_seg20",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring2_seg0",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg10",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg11",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg12",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg13",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg14",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring26_seg15",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring_mod26_seg1",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring_mod26_seg2",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring27_seg1",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring27_seg2",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring27_seg3",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring27_seg4",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring_mod27_seg1",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring_mod27_seg2",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg1",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg2",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg3",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg4",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg5",
    ./sysrap/tests/sregex_test.cc:        "s_EMFcoil_holder_ring28_seg6"
    ./u4/U4Mesh.h:("G4Torus", "s_EMFcoil_holder_ring26_seg8"). Based on the existence
    ./u4/U4Mesh.h:    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_pfx_0=s_EMFcoil_holder_ring
    ./u4/U4Mesh.h:    export U4Mesh__NumberOfRotationSteps_solidName_STARTING_pfx_1=s_EMFcoil_holder_ring
    ./u4/tests/U4Mesh_test.sh:solid=Torus_s_EMFcoil_holder_ring_mod26_seg1
    ./u4/tests/U4Mesh_test.sh:    export $pfx=Torus_s_EMFcoil_holder_ring
    A[blyth@localhost opticks]$ 
    A[blyth@localhost opticks]$ 





watch SSim
-------------

::

    (gdb) bt
    #0  SSim::SSim (this=0xc95eb00) at /home/blyth/opticks/sysrap/SSim.cc:161
    #1  0x00007fffc0b5ea46 in SSim::Create () at /home/blyth/opticks/sysrap/SSim.cc:97
    #2  0x00007fffc0b5e238 in SSim::CreateOrReuse () at /home/blyth/opticks/sysrap/SSim.cc:43
    #3  0x00007fffc1243064 in G4CXOpticks::SetGeometry_JUNO (world=0xabf2230, sd=0x67616d0, jpmt=0xc8d13e0, jlut=0xc95df10) at /home/blyth/opticks/g4cx/G4CXOpticks.cc:104
    #4  0x00007fffbfd4520d in LSExpDetectorConstruction_Opticks::Setup (opticksMode=1, world=0xabf2230, sd=0x67616d0, ppd=0x65f2600, psd=0x65f3090, pmtscan=0x0)
        at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction_Opticks.cc:54
    #5  0x00007fffbfd08eb6 in LSExpDetectorConstruction::setupOpticks (this=0xa7e3ce0, world=0xabf2230) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:472
    #6  0x00007fffbfd08756 in LSExpDetectorConstruction::Construct (this=0xa7e3ce0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpDetectorConstruction.cc:393
    #7  0x00007fffc67ca92e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #8  0x00007fffc67caafc in G4RunManager::Initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #9  0x00007fffce08db0b in DetSimAlg::initialize (this=0x661bc20) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:80
    #10 0x00007fffd24c5b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007fffd24db09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007fffd24e3447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007fffd24db048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fdf2e0, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb0020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e5cc0, func=0x7ffff7e60ae0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co@entry=0x509980, globals=globals@entry=0x7ffff76e5cc0, locals=locals@entry=0x7ffff76e5cc0) at Python/ceval.c:1148
    #24 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e5cc0, globals=0x7ffff76e5cc0, co=0x509980, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff7e61430, globals=globals@entry=0x7ffff76e5cc0, locals=locals@entry=0x7ffff76e5cc0, flags=flags@entry=0x7ffffffe3b68, arena=arena@entry=0x7ffff7de2b50)
        at Python/pythonrun.c:1762
    #26 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffe3b68, closeit=<optimized out>, locals=0x7ffff76e5cc0, globals=0x7ffff76e5cc0, start=257, filename=0x7ffff7e61430, fp=0x409710) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp@entry=0x409710, filename=filename@entry=0x7ffff7e61430, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe3b68) at Python/pythonrun.c:440
    #28 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x409710, filename=filename@entry=0x7ffff7e61430, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffe3b68) at Python/pythonrun.c:79
    #29 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff7e61430, program_name=0x7ffff7e24b70) at Modules/main.c:360
    #30 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffffffe3b64) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffe3c70) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    (gdb) f 1
    #1  0x00007fffc0b5ea46 in SSim::Create () at /home/blyth/opticks/sysrap/SSim.cc:97
    97	    new SSim ;
    (gdb) watch *(long*)0xc95eb00 
    Hardware watchpoint 2: *(long*)0xc95eb00
    (gdb) c



FIX : SEvt::sim nullptr-ing
--------------------------------


HMM: were to do this in Client case ? Is the somewhere that can be in common ?

::

    1194 /**
    1195 SEvt::setSim
    1196 -------------
    1197 
    1198 Invoked from::
    1199 
    1200     CSGOptiX::Create
    1201     CSGOptiX::InitEvt
    1202 
    1203 **/
    1204 
    1205 void SEvt::setSim(const SSim* sim_)
    1206 {
    1207     assert(sim_);
    1208     sim = sim_ ;
    1209     tree = sim->get_tree();
    1210 }
    1211 




BETTER ljrt ERROR : now that SEvt::sim is nullptr 
---------------------------------------------------

::

    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-04-28 20:46:37.053 [junoSD_PMT_v2::Initialize eventID 0
    2026-04-28 20:46:37.054 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    python: /home/blyth/opticks/sysrap/SEvt.cc:2497: sgs SEvt::addGenstep(const quad6&): Assertion `sim' failed.

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff742875b in __assert_fail_base.cold () from /lib64/libc.so.6
    #4  0x00007ffff7437886 in __assert_fail () from /lib64/libc.so.6
    #5  0x00007fffc0917b4c in SEvt::addGenstep (this=0xc9914d0, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2497
    #6  0x00007fffc0914468 in SEvt::AddGenstep (q=...) at /home/blyth/opticks/sysrap/SEvt.cc:1589
    #7  0x00007fffc0b2247c in U4::CollectGenstep_DsG4Scintillation_r4695 (aTrack=0xbf5cea00, aStep=0x6862a00, numPhotons=1, scnt=0, ScintillationTime=4.5999999999999996) at /home/blyth/opticks/u4/U4.cc:183
    #8  0x00007fffbf4efa6e in DsG4Scintillation::PostStepDoIt (this=0x2903bbc0, aTrack=..., aStep=...) at /home/blyth/junosw/Simulation/DetSimV2/PhysiSim/src/DsG4Scintillation.cc:601
    #9  0x00007fffc6bd4519 in G4SteppingManager::InvokePSDIP(unsigned long) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #10 0x00007fffc6bd491b in G4SteppingManager::InvokePostStepDoItProcs() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #11 0x00007fffc6bd2154 in G4SteppingManager::Stepping() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #12 0x00007fffc6bdd70f in G4TrackingManager::ProcessOneTrack(G4Track*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so
    #13 0x00007fffc6c18565 in G4EventManager::DoProcessing(G4Event*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so
    #14 0x00007fffe058468e in G4SvcRunManager::SimulateEvent (this=0x6722260, i_event=0) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:29
    #15 0x00007fffce088d2e in DetSimAlg::execute (this=0x6866a10) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:112
    #16 0x00007fffd24db4b1 in Task::execute() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #17 0x00007fffd24dfbbd in TaskWatchDog::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #18 0x00007fffd24db054 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/lib64/libSniperKernel.so
    #19 0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/sniper/InstallArea/python/Sniper/libSniperPython.so
    #20 0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    ...
    (gdb) 


    (gdb) f 5
    #5  0x00007fffc0917b4c in SEvt::addGenstep (this=0xc9914d0, q_=...) at /home/blyth/opticks/sysrap/SEvt.cc:2497
    2497	        assert(sim);
    (gdb) list
    2492	#ifdef WITH_OLD_FRAME
    2493	        assert(cf);
    2494	        matline = cf ? cf->lookup_mtline(mtindex) : 0 ;
    2495	#else
    2496	        // omitting this caused ~/o/notes/issues/qcerenkov_dumping_following_WITH_OLD_FRAME_due_to_matline_0.rst
    2497	        assert(sim);
    2498	        matline = sim ? sim->lookup_mtline(mtindex) : 0 ;
    2499	#endif
    2500	
    2501	        bool bad_ck = is_cerenkov_gs && matline == -1 ;
    (gdb) 






how to fix : need to relocate CSGOptiX::InitEvt somewhere common to Client and Server/full Opticks
---------------------------------------------------------------------------------------------------

::



    1194 /**
    1195 SEvt::setSim
    1196 -------------
    1197 
    1198 Invoked from::
    1199 
    1200     CSGOptiX::InitEvt
    1201     CSGOptiX::Create
    1202     G4CXOpticks::CreateSimulator
    1203     G4CXOpticks::setGeometry_
    1204 
    1205 **/
    1206 
    1207 void SEvt::setSim(const SSim* sim_)
    1208 {   
    1209     assert(sim_);
    1210     sim = sim_ ;
    1211     tree = sim->get_tree();
    1212 }
    1213 



     235 /**
     236 CSGOptiX::InitEvt  TODO : THIS DOES NOT USE GPU : SO SHOULD BE ELSEWHERE
     237 --------------------------------------------------------------------------
     238 
     239 Invoked from CSGOptiX::Create
     240 
     241 
     242 Q: Why the SEvt geometry connection ?
     243 A: Needed for global to local transform conversion
     244 
     245 Q: What uses SEVt::setGeo (SGeo) ?
     246 A: Essential set_matline of Cerenkov Genstep
     247 
     248 **/
     249 
     250 void CSGOptiX::InitEvt( CSGFoundry* fd  )
     251 {
     252     SEvt* sev = SEvt::CreateOrReuse(SEvt::EGPU) ;
     253 
     254 #ifdef WITH_OLD_FRAME
     255     sev->setGeo((SGeo*)fd);
     256 #else
     257     const SSim* ssim = fd->getSim();
     258     sev->setSim(ssim);
     259 #endif
     260 
     261     std::string* rms = SEvt::RunMetaString() ;
     262     assert(rms);
     263 
     264     bool stamp = false ;
     265     smeta::Collect(*rms, "CSGOptiX__InitEvt", stamp );
     266 }




::

    400 SSimulator* G4CXOpticks::CreateSimulator(CSGFoundry* fd)  // static
    401 {
    402     SSimulator* cx = nullptr ;
    403 
    404 #if defined(WITH_CUDA)
    405     cx = CSGOptiX::Create(fd);
    406 #elif defined(WITH_CURL)
    407     stree* tr = fd->getTree();
    408     cx = SClientSimulator::Create(tr);
    409 #endif
    410 
    411     assert(cx);
    412     return cx ;
    413 }



    355 void G4CXOpticks::setGeometry_(CSGFoundry* fd_)
    356 {
    357     fd = fd_ ;
    358     LOG(LEVEL) << "[ fd " << fd ;
    359 
    360     if(!NoSim)
    361     {
    362         LOG(LEVEL) << "[ CreateSimulator " ;
    363         cx = CreateSimulator(fd);
    364         LOG(LEVEL) << "] CreateSimulator " ;
    365     }










ljrt : seems gensteps were uploaded as server did some sim
--------------------------------------------------------------


Server log::

    //qcerenkov::wavelength_sampled_bndtex idx   4338 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 154.765 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4339 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength  93.177 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4340 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 283.727 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4341 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 112.856 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4342 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 110.075 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4343 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 256.950 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    //qcerenkov::wavelength_sampled_bndtex idx   4344 sampledRI   1.263 cosTheta   1.022 sin2Theta   0.000 wavelength 104.159 count 100 gs.matline 39 gs.pos (426.618, 43.461,128.104)
    SProf::Write DISABLED, enable[export SProf__WRITE=1] disable[unset SProf__WRITE]
    2026-04-29 10:08:01.236 INFO  [1925978] [QSim::simulate@736]  eventID      0 gs (90, 6, 4, ) ht (6, 4, 4, ) tot_dt   0.003641 server_settings HitCompOneName:hit,PhotonCompOneName:photon tree_digest 79f17049c1f5806abe058cf4449eb712
    SProf::Write DISABLED, enable[export SProf__WRITE=1] disable[unset SProf__WRITE]
          INFO   127.0.0.1:56950 - "POST /simulate HTTP/1.1" 200



But client lacks symbol : curl_easy_nextheader::


    =======================================================================
    ### Run : 0
    junotoptask.initialize          INFO: initialized
    junotoptask:detsimiotask.find   WARN: Cann't find Object InputSvc
    junotoptask:detsimiotask:OutputSvc.initialize  INFO: ... isReproducible: 0
    junotoptask:detsimiotask.initialize  INFO: initialized
    junotoptask:DetSimAlg.execute   INFO: DetSimAlg Simulate An Event (0) 
    2026-04-29 10:08:01.176 [junoSD_PMT_v2::Initialize eventID 0
    2026-04-29 10:08:01.176 ]junoSD_PMT_v2::Initialize eventID 0
    Begin of Event --> 0
    2026-04-29 10:08:01.178 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 1 hitCollection 0 hitCollectionAlt -1 hcMuon 0 GPU YES
    SProf::Write DISABLED, enable[export SProf__WRITE=1] disable[unset SProf__WRITE]
    2026-04-29 10:08:01.179 ERROR [33140] [SEvt::addGenstep@2430]  a null : low level simtrace tests like CSGSimtraceTest.sh can do this  
    /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Python/3.11.10/bin/python: symbol lookup error: /data1/blyth/local/opticks_Client/lib64/libG4CX.so: undefined symbol: curl_easy_nextheader
    [Thread 0x7fffcd5ff640 (LWP 33164) exited]
    [Inferior 1 (process 33140) exited with code 0177]
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    No stack.
    (gdb) 




::

    A[blyth@localhost junosw]$ t ljrt
    ljrt () 
    { 
        : ~/j/local.sh;
        : setup environment to check a release;
        local_oj_release;
        oj_release;
        oj_release_test
    }
    A[blyth@localhost junosw]$ t local_oj_release
    local_oj_release () 
    { 
        : ~/j/local.sh;
        local desc="TODO: cvmfs release";
        local mode=oj_release;
        export VIP_MODE="${VIP_MODE},$mode";
        export VIP_DESC="${VIP_DESC},$desc";
        export VIP_FUNC="${VIP_FUNC},$FUNCNAME";
        function oj_release () 
        { 
            : ~/j/local.sh;
            source ~/.opticks/GEOM/ENVSET.sh;
            if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
                source $ENVSET;
            else
                echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET;
            fi
        };
        function oj_release_test () 
        { 
            : ~/local.sh;
            source dbg__.sh;
            dbg__ $(which python) $(which tut_detsim.py) --evtmax 1 gun
        }
    }
    A[blyth@localhost junosw]$ echo $ENVSET
    /home/blyth/junosw/InstallArea/Client_blyth-revive-opticksMode-zero-fixing-cleanup-SIGSEGV/envset.sh
    A[blyth@localhost junosw]$ 



check the OK bashrc env : shows using system libcurl
------------------------------------------------------------

::

    A[blyth@localhost opticks]$ source /data1/blyth/local/opticks_Client/bashrc
    === opticks-setup-geant4- : WARNING no OPTICKS_GEANT4_PREFIX : Geant4 will need be setup by other means

    A[blyth@localhost opticks]$ ldd /data1/blyth/local/opticks_Client/lib64/libG4CX.so
        linux-vdso.so.1 (0x00007ffd22b85000)
        libCSG.so => /data1/blyth/local/opticks_Client/lib64/../lib64/libCSG.so (0x00007ff351315000)
        libU4.so => /data1/blyth/local/opticks_Client/lib64/../lib64/libU4.so (0x00007ff35114a000)
        libcurl.so.4 => /lib64/libcurl.so.4 (0x00007ff351094000)
        libG4Tree.so => not found
        libG4FR.so => not found

Actually that is expected as ljrt kludges the runtime env via bash function::

    527 local_setup_client()
    528 {
    529     : see ~/opticks/externals/openssl.bash
    530     : see ~/opticks/externals/libcurl.bash
    531     : used from local_oj_release and local_ok_externals
    532 
    533     #source /usr/local/ExternalLibs/openssl/openssl-3.2.0/bashrc
    534     source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc
    535 }

After manual kludge get the expected libcurl::

    A[blyth@localhost opticks]$ source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc
    A[blyth@localhost opticks]$ ldd /data1/blyth/local/opticks_Client/lib64/libG4CX.so
        linux-vdso.so.1 (0x00007ffc383f1000)
        libCSG.so => /data1/blyth/local/opticks_Client/lib64/../lib64/libCSG.so (0x00007fc536727000)
        libU4.so => /data1/blyth/local/opticks_Client/lib64/../lib64/libU4.so (0x00007fc53655c000)
        libcurl.so.4 => /usr/local/ExternalLibs/libcurl/curl-8.12.1/lib64/libcurl.so.4 (0x00007fc53649b000)
        libG4Tree.so => not found
        libG4FR.so => not found


Need to solidify the custom libcurl setup into the envset.sh::

    847 local_oj_release()
    848 {
    849    : ~/j/local.sh
    850    local desc="TODO: cvmfs release"
    851    local mode=oj_release
    852 
    853    export VIP_MODE="${VIP_MODE},$mode"
    854    export VIP_DESC="${VIP_DESC},$desc"
    855    export VIP_FUNC="${VIP_FUNC},$FUNCNAME"
    856 
    857    oj_release()
    858    {
    859        : ~/j/local.sh
    860 
    861        source ~/.opticks/GEOM/ENVSET.sh
    862        if [ -n "$ENVSET" -a -f "$ENVSET" ]; then
    863            source $ENVSET
    864 
    865            if [ "$OPTICKS_CONFIG" == "Client" ]; then  ## DOES NOT NEED TO BE CONDITIONAL ONCE WORKING
    866                echo $BASH_SOURCE - OPTICKS_CONFIG $OPTICKS_CONFIG - doing local_setup_client
    867                local_setup_client
    868            else
    869                echo $BASH_SOURCE - OPTICKS_CONFIG $OPTICKS_CONFIG - NOT DOING local_setup_client
    870            fi
    871        else
    872            echo $BASH_SOURCE - ERROR - MISSING ENVSET $ENVSET
    873        fi
    874    }
    875 
    876    oj_release_test()
    877    {
    878        : ~/local.sh
    879        source dbg__.sh
    880        dbg__ \
    881           $(which python) \
    882           $(which tut_detsim.py) \
    883           --evtmax 1 \
    884           gun
    885    }
    886 }


TODO: check NOT:WITH_CUDA WITH_CURL build on non-GPU non-CUDA machine
-----------------------------------------------------------------------


what is generating the envset.sh and when ? ".gitlab-ci/oj_helper.sh"
------------------------------------------------------------------------

Yes, that is correct for the gitlib-ci build. But what about my local one ? 
The ~/j/local.sh script uses bits of the junosw machinery to do (close to) the same thing
locally::


    673    oj_build_pre(){
    674        : ~/j/local.sh
    675        cd $(local_srcdir)
    676        source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
    677        mkdir -p InstallConfig
    678        source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
    679        source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
    680        ## HMM: should InstallConfig use reldir too ?
    681    }
    682 
    683    oj_build_(){
    684        : ~/j/local.sh
    685        cd $(local_srcdir)
    686 
    687        ##rm -f $FUNCNAME.log  ## retaining log to follow progression of build time is useful
    688        oj_log $FUNCNAME START $CMD
    689 
    690        ./build_Debug.sh ;
    691 
    692        [ $? -ne 0 ] && echo $FUNCNAME ERROR DURING BUILD && return 1
    693 
    694        oj_log $FUNCNAME FINISH $CMD
    695        return 0
    696    }

    686    oj_build_post(){
    687        : ~/j/local.sh
    688        cd $(local_srcdir)
    689        local reldir=$(local_reldir)
    690 
    691       if [ -n "$JUNO_OFFLINE_BUILD_BRANCH" ]; then
    692            cp InstallConfig/ENV.bash  InstallArea/$reldir/ENV.bash
    693            cp InstallConfig/envset.sh InstallArea/$reldir/envset.sh
    694       else
    695            cp InstallConfig/ENV.bash  InstallArea/ENV.bash
    696            cp InstallConfig/envset.sh InstallArea/envset.sh
    697       fi
    698    }


::

    source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallArea/envset.sh


Need OpticksClient variant in the gitlab-ci to build and install "CJ" OpticksClient+JUNOSW 

Whats different ? 

JUNO_OPTICKS_PREFIX
    /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/OpticksClient-vLatest

JUNO_OPTICKS_CONFIG
    Client



TODO: test OpticksClient built against my libcurl and system openssl
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Current way of doing this does env control via bash function : local_client_setup
That is fine for initial local testing - but need to solidify this by getting 
the source line into the envset.sh with a cvmfs path. Actually JUNOTOP/bashrc.sh is the 
eventual place for the libcurl sourcing from cvmfs. But prior to that can put the
source line directly into the generated envset.sh::

    local_client_setup()
    {
        : see ~/opticks/externals/openssl.bash 
        : see ~/opticks/externals/libcurl.bash
        : used from local_oj_release and local_ok_externals

        #source /usr/local/ExternalLibs/openssl/openssl-3.2.0/bashrc
        source /usr/local/ExternalLibs/libcurl/curl-8.12.1/bashrc
    }


    A[blyth@localhost Jlatest]$ cat /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest/bashrc.sh
    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/binutils/2.35.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/go/1.20.6/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junoenv/etc/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Git/2.46.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/git-lfs/3.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Cmake/3.30.5/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Python/3.11.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-setuptools/69.5.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-pip/23.3.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-cython/3.0.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/python-numpy/1.26.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/libyaml/0.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Boost/1.85.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/Xercesc/3.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/gsl/2.7/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/fftw3-proxy/3.3.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J26.1.1/ExternalLibs/eigen/3.4.0/bashrc



Check libcurl openssl versions in the docker image
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    A[blyth@localhost ~]$ docker images simoncblyth/cuda
    REPOSITORY         TAG                              IMAGE ID       CREATED         SIZE
    simoncblyth/cuda   12.4.1-runtimeplus-rockylinux9   8c10f253f281   13 months ago   7.89GB
    A[blyth@localhost ~]$ docker run -it simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9 /bin/bash

* ~/j/rockylinux_docker_image_gcc_version/check_openssl_libcurl_in_docker_container.rst



TODO: make and test OpticksClient distribution, extending okdist
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


generalized OJ - adding Client build
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Gemini snippet: ~/j/oj_client/.gitlab-ci.yml


standard OJ
~~~~~~~~~~~~

::

     51 ##############################################################################
     52 # Opticks Build Job Template
     53 ##############################################################################
     54 .opticks_build_job_template:
     55   extends: .job_template
     56   stage: build
     57   image: simoncblyth/cuda:12.4.1-runtimeplus-rockylinux9
     58   variables:
     59     JUNO_CLANG_PREFIX:
     60     JUNO_OPTICKS_PREFIX: /cvmfs/opticks.ihep.ac.cn/ok/releases/el9_amd64_gcc11/Opticks-vLatest
     61     EXTRA_BUILD_FLAGS: JUNO_CMAKE_BUILD_TYPE=Debug
     62   script:
     63     - printf "[ ================ BUILD PHASE OF BUILD JOB =========================\n"
     64     - for repo in juno.ihep.ac.cn opticks.ihep.ac.cn; do if [ ! -d /cvmfs/$repo ]; then sudo mkdir /cvmfs/$repo; fi; sudo mount -t cvmfs $repo /cvmfs/$repo; done
     65     - source .gitlab-ci/oj_helper.sh EMIT_ENV_CHECK
     66     - mkdir InstallConfig
     67     - source .gitlab-ci/oj_helper.sh EMIT_ENV    > InstallConfig/ENV.bash
     68     - cat InstallConfig/ENV.bash
     69     - source .gitlab-ci/oj_helper.sh EMIT_ENVSET > InstallConfig/envset.sh
     70     - cat InstallConfig/envset.sh
     71     - export JUNO_OFFLINE_OFF=1        # Disable JUNOSW setup prior to having built JUNOSW
     72     - export OPTICKS_SETUP_VERBOSE=1   # ~/j/gitlab-ci/mockbuild.sh shows this protects against "set -eo pipefail"
     73     - source $JUNOTOP/setup.sh
     74     - if [ -n "$JUNO_CLANG_PREFIX" ]; then source $JUNO_CLANG_PREFIX/bashrc; fi
     75     - if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi
     76     - env $EXTRA_BUILD_FLAGS ./build.sh
     77     - cp InstallConfig/ENV.bash  InstallArea/ENV.bash
     78     - cp InstallConfig/envset.sh InstallArea/envset.sh
     79     - unset JUNO_OFFLINE_OFF # now that it has been built the below needs the JUNOSW environment for tut_detsim.py running
     80     - printf "] ================ BUILD PHASE OF BUILD JOB =========================\n"
     81     - printf "[ ================ TEST PHASE OF BUILD JOB =========================\n"
     82     - env $EXTRA_BUILD_FLAGS ./oj_initialize.sh
     83     - printf "] ================ TEST PHASE OF BUILD JOB =========================\n"
     84 



