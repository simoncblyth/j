oj_opticksMode_0_cleanup_SIGABRT
==================================


The G4SvcRunManager looks to be deleted twice by python ?::


    [Thread 0x7fffcd5ff640 (LWP 186014) exited]

    Thread 1 "python" hit Breakpoint 1.2, G4SvcRunManager::~G4SvcRunManager (this=0x65d7750, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    11    }
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  G4SvcRunManager::~G4SvcRunManager (this=0x65d7750, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #1  0x00007fffc6b9d6db in G4Svc::~G4Svc (this=0x663e080, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #2  0x00007fffc6b9d72e in G4Svc::~G4Svc (this=0x663e080, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #3  0x00007fffd24c6513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd24c6e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd24deb4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd24dbf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #8  0x00007fffd4856d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #9  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc1478f90) at Objects/typeobject.c:1463
    #10 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #11 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #12 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #13 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff7710110) at Objects/typeobject.c:1433
    #14 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #15 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #16 free_keys_object (keys=0x7ffff7e7bd20) at Objects/dictobject.c:664
    #17 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #18 dict_dealloc (mp=0x7ffff76e6000) at Objects/dictobject.c:2378
    #19 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #20 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #21 module_dealloc (m=0x7ffff76be9d0) at Objects/moduleobject.c:699
    #22 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #23 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #24 insertdict (mp=0x7ffff7e45340, key=0x7ffff76e6030, hash=731918893601119491, value=<optimized out>) at Objects/dictobject.c:1304
    #25 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e45340) at Python/pylifecycle.c:1415
    #26 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #27 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #28 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #29 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #30 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeab0) at Modules/main.c:714
    #31 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #32 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #33 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #34 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.

    Thread 1 "python" hit Breakpoint 1.1, G4SvcRunManager::~G4SvcRunManager (this=0x65d7750, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:9
    9    G4SvcRunManager::~G4SvcRunManager() {
    (gdb) bt
    #0  G4SvcRunManager::~G4SvcRunManager (this=0x65d7750, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:9
    #1  0x00007fffe05845ba in G4SvcRunManager::~G4SvcRunManager (this=0x65d7750, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #2  0x00007fffc6b9d6db in G4Svc::~G4Svc (this=0x663e080, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #3  0x00007fffc6b9d72e in G4Svc::~G4Svc (this=0x663e080, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #4  0x00007fffd24c6513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd24c6e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd24deb4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd24dbf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #9  0x00007fffd4856d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc1478f90) at Objects/typeobject.c:1463
    #11 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #12 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #13 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #14 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff7710110) at Objects/typeobject.c:1433
    #15 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #16 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #17 free_keys_object (keys=0x7ffff7e7bd20) at Objects/dictobject.c:664
    #18 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #19 dict_dealloc (mp=0x7ffff76e6000) at Objects/dictobject.c:2378
    #20 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #21 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #22 module_dealloc (m=0x7ffff76be9d0) at Objects/moduleobject.c:699
    #23 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #24 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #25 insertdict (mp=0x7ffff7e45340, key=0x7ffff76e6030, hash=731918893601119491, value=<optimized out>) at Objects/dictobject.c:1304
    #26 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e45340) at Python/pylifecycle.c:1415
    #27 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #28 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #29 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #30 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #31 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeab0) at Modules/main.c:714
    #32 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #33 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #34 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #35 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.
    Delete G4SvcRunManager
    double free or corruption (out)

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    (gdb) 




Gemini


This is exactly what I suspected! Your backtraces provide a perfect "autopsy"
of a Double Free via Static Conflict, though it's a bit more subtle than Python
simply calling it twice.

Look closely at the this pointer in both hits: this=0x65d7750. It is indeed the same object.
The "Smoking Gun" in your Backtrace

Here is why it’s crashing:

    Hit #1 (The "First" Delete): This happens at #8
boost::python::objects::value_holder<TopTask>::~value_holder(). Python is
shutting down (Py_FinalizeEx), and it's cleaning up the TopTask (your JUNO
application). Sniper’s Task destructor triggers a chain reaction: Task ->
TaskWatchDog -> ExecUnit -> DleSupervisor -> G4Svc. The G4Svc destructor then
deletes the G4SvcRunManager.

    Hit #2 (The "Illegal" Second Delete): You hit the destructor again
immediately after. Notice the library addresses change slightly
(0x7fffe05845ba).

    The Crash: After Hit #2, you see the message Delete G4SvcRunManager
followed by the double free or corruption.

What is actually happening?

You aren't just seeing two calls; you are seeing a Symbol Conflict or a
Double-Linked Library issue.

Notice that in Hit #1, the address of the destructor is resolved within the
main execution flow. In Hit #2, the debugger shows the address again. This
often happens in JUNO when:

    A shared library is loaded twice under different names.

    Most Likely: The G4SvcRunManager is being managed by a std::unique_ptr or a
raw pointer in G4Svc, but another part of the code—possibly the new
"Opticks-Convert" code you added—is also attempting to manage that same pointer
or is registered as a "Secondary" owner in the Sniper DleSupervisor.

Why this=0x65d7750 appears twice

When Hit #1 finishes, the memory at 0x65d7750 is marked as "free" by the
system. However, the pointer variable itself isn't wiped out in the other
owner's memory. When Hit #2 occurs, the code attempts to run the destructor on
that same address. The cout works because the code for the destructor is still
in the CPU instruction cache, but as soon as the destructor finishes and the
Base Class (G4RunManager) tries to release internal Geant4 memory, the
allocator detects that 0x65d7750 is already gone.

How to Fix It

1. The "Nullify" Defense
Check G4Svc.cc around line 20. It likely looks like this:
C++

delete m_runmgr;

Change it to a safer pattern and add a debug print:
C++

if (m_runmgr) {
    std::cout << "DEBUG: G4Svc deleting m_runmgr at " << m_runmgr << std::endl;
    delete m_runmgr;
    m_runmgr = nullptr; 
} else {
    std::cout << "DEBUG: G4Svc m_runmgr already null, skipping." << std::endl;
}

If you still get Hit #2, it means Hit #2 is coming from a different pointer variable that was pointing to the same address (aliasing).

2. Check your "Opticks-Convert" Initialization
Did you manually create a G4SvcRunManager in your new code?
In JUNO, the G4Svc should be the sole owner of the RunManager. If your
conversion script does new G4SvcRunManager(), you are creating a second manager
that Sniper doesn't know about, or you are overwriting the pointer that Sniper
thought it owned.

3. The "Leaky" Fix (Diagnostic)
In G4Svc::~G4Svc(), simply comment out the delete m_runmgr;.

    If the program exits perfectly without a crash, then Hit #2 was actually
the "correct" cleanup (perhaps from a global static) and Hit #1 was an
aggressive cleanup by the Sniper Task.

    Given that JUNO is a long-running framework, a small leak at the very last
second of termination is often preferable to a SIGABRT.

Quick Question: Does your opticks-convert code use G4Opticks::Get() or similar singletons? Those singletons often register their own atexit handlers which conflict with Sniper’s teardown.








A[blyth@localhost junosw]$ jgr getRunMgr
./Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:    run_manager = g4svc->getRunMgr();
./Simulation/DetSimV2/DetSimMT/DetSimMT/SlaveRunMgrSvc.hh:        tbbWorkerRunManager* getRunMgr();
./Simulation/DetSimV2/DetSimMT/src/SimAlg.cc:    m_runmgr = drSvc->getRunMgr();
./Simulation/DetSimV2/DetSimMT/src/SlaveRunMgrSvc.cc:SlaveRunMgrSvc::getRunMgr()
./Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h:        G4SvcRunManager* getRunMgr();
./Simulation/DetSimV2/G4Svc/G4Svc/IG4Svc.h:        virtual G4SvcRunManager* getRunMgr()=0;
./Simulation/DetSimV2/G4Svc/src/G4Svc.cc:G4SvcRunManager* G4Svc::getRunMgr()
A[blyth@localhost junosw]$ 







Look at your bt again. You have Hit #1 and Hit #2 at the same address.

    Hit #1 is triggered by Task::~Task() (Sniper's graceful exit).

    Hit #2 is triggered by Py_FinalizeEx (Python's hard teardown).

If your G4Svc is being deleted twice, it means the G4Svc instance itself is likely being managed by two different owners.

    Owner A: The Sniper ServiceManager.

    Owner B: A Python variable in your gun.sh script that holds a reference to the service or the task.





(ok) A[blyth@localhost junosw]$ find InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/ -name JUNODetSimModule.py
InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNODetSimModule.py
(ok) A[blyth@localhost junosw]$ vi InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNODetSimModule.py
(ok) A[blyth@localhost junosw]$ 











junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr OpticalParameterAnaMgr
junotoptask:DetSim0Svc.initialize  INFO: Register AnaMgr TimerAnaMgr
junotoptask:SniperProfiling.initialize  INFO: 
junotoptask:GenTools.gun.configure  INFO: Positions Mode: FixOne
junotoptask:GenTools.gun.configure  INFO:  + Position : (0.00000, 0.00000, 0.00000) 
junotoptask:GenTools.gun.configure  INFO: Particle/Mass/Momentum: gamma(22)/0.00000MeV/1.00000MeV
junotoptask:DetSimAlg.initialize  INFO: DetSimAlg initialized successfully
junotoptask:DetSimAlg.initialize  INFO: DetSimAlg : Load Factory Name: DetSim0Svc

Thread 1 "python" hit Breakpoint 1, G4Svc::getRunMgr (this=0x6549f30) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:36
warning: Source file is more recent than executable.
36	
Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
(gdb) bt
#0  G4Svc::getRunMgr (this=0x6549f30) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:36
#1  0x00007fffce088a6e in DetSimAlg::initialize (this=0x65a8150) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:61
#2  0x00007fffd24c5b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#3  0x00007fffd24db09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#4  0x00007fffd24e3447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#5  0x00007fffd24db048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#6  0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
#7  0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#8  0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
   from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#9  0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#10 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#11 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fbf490, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
#12 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
#13 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
#14 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e6140, func=0x7ffff76e9f80, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
#15 PyEval_EvalCode (co=co@entry=0x4ed140, globals=globals@entry=0x7ffff76e6140, locals=locals@entry=0x7ffff76e6140) at Python/ceval.c:1148
#16 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e6140, globals=0x7ffff76e6140, co=0x4ed140, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
#17 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cac90, globals=globals@entry=0x7ffff76e6140, locals=locals@entry=0x7ffff76e6140, flags=flags@entry=0x7ffffffee998, arena=arena@entry=0x7ffff7de2b70)
    at Python/pythonrun.c:1762
#18 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee998, closeit=<optimized out>, locals=0x7ffff76e6140, globals=0x7ffff76e6140, start=257, filename=0x7ffff76cac90, fp=0x42f4a0) at Python/pythonrun.c:1657
#19 _PyRun_SimpleFileObject (fp=fp@entry=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee998) at Python/pythonrun.c:440
#20 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee998) at Python/pythonrun.c:79
#21 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cac90, program_name=0x7ffff7e26b80) at Modules/main.c:360
#22 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
#23 pymain_run_python (exitcode=0x7ffffffee994) at Modules/main.c:605
#24 Py_RunMain () at Modules/main.c:684
#25 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeaa0) at Modules/main.c:714
#26 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
#27 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
#28 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
#29 0x0000000000401075 in _start ()
(gdb) 





With HARD_EXIT no logging from G4SvcRunManager:: 

    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 577.55499 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 577.55499 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.27400        1.27400      0.00000      
    DetSimAlg                1           580.25000      580.25000    0.00000      
    Sum of junotoptask       1           581.52698      581.52698    0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2026-04-01 14:48:29,482] p269121 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2026-04-01 14:48:29,483] p269121 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:55} INFO - ]juno_application.run
    [2026-04-01 14:48:29,483] p269121 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:58} INFO - End of script - doing HARD_EXIT os._exit(0)
    [Thread 0x7fffcd5ff640 (LWP 269137) exited]
    [Thread 0x7ffff7ec8740 (LWP 269121) exited]
    [Thread 0x7fffbcfff640 (LWP 269148) exited]
    [New process 269121]
    [Inferior 1 (process 269121) exited normally]
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 




Who is holding the run_manager ? DetSimAlg from :  BP=G4Svc::getRunMgr ojt dbg
--------------------------------------------------------------------------------


::


    junotoptask:SniperProfiling.initialize  INFO: 
    junotoptask:GenTools.gun.configure  INFO: Positions Mode: FixOne
    junotoptask:GenTools.gun.configure  INFO:  + Position : (0.00000, 0.00000, 0.00000) 
    junotoptask:GenTools.gun.configure  INFO: Particle/Mass/Momentum: gamma(22)/0.00000MeV/1.00000MeV
    junotoptask:DetSimAlg.initialize  INFO: DetSimAlg initialized successfully
    junotoptask:DetSimAlg.initialize  INFO: DetSimAlg : Load Factory Name: DetSim0Svc

    Thread 1 "python" hit Breakpoint 1, G4Svc::getRunMgr (this=0x6549f30) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:36
    warning: Source file is more recent than executable.
    36	
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  G4Svc::getRunMgr (this=0x6549f30) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:36
    #1  0x00007fffce088a6e in DetSimAlg::initialize (this=0x65a8150) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.c
    #2  0x00007fffd24c5b56 in DleSupervisor::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #3  0x00007fffd24db09b in Task::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd24e3447 in TopTask::initialize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd24db048 in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #7  0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #8  0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #9  0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #11 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x5fbf490, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #12 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #13 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #14 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e6140, func=0x7ffff76e9f80, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #15 PyEval_EvalCode (co=co@entry=0x4ed140, globals=globals@entry=0x7ffff76e6140, locals=locals@entry=0x7ffff76e6140) at Python/ceval.c:1148
    #16 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e6140, globals=0x7ffff76e6140, co=0x4ed140, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #17 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cac90, globals=globals@entry=0x7ffff76e6140, locals=locals@entry=0x7ffff76e6140, flags=flags@entry=0x7ffffffee998, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #18 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee998, closeit=<optimized out>, locals=0x7ffff76e6140, globals=0x7ffff76e6140, start=257, filename=0x7ffff76cac90, fp=0x42f4a0) at Python/pythonrun.c:1657
    #19 _PyRun_SimpleFileObject (fp=fp@entry=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee998) at Python/pythonrun.c:440
    #20 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee998) at Python/pythonrun.c:79
    #21 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cac90, program_name=0x7ffff7e26b80) at Modules/main.c:360
    #22 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #23 pymain_run_python (exitcode=0x7ffffffee994) at Modules/main.c:605
    #24 Py_RunMain () at Modules/main.c:684
    #25 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeaa0) at Modules/main.c:714
    #26 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #27 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #28 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #29 0x0000000000401075 in _start ()
    (gdb) 








DetSimAlg holds run_manager::

    class DetSimAlg: public AlgBase
    {
        public:
            DetSimAlg(const std::string& name);
            ~DetSimAlg();

            bool initialize();
            bool execute();
            bool finalize();

        private:
            bool SetG4Init();
            bool SetG4RunMac();
            bool SetG4RunCmds();
            bool StartG4Vis();


        private:
            std::string m_factory_name;
            std::string m_run_mac;
            std::vector<std::string> m_run_cmds;
            std::string m_vis_mac;
            std::string m_g4svc_name;

            IDetSimFactory* det_factory;
            G4SvcRunManager* run_manager;

            int i_event;
            bool is_mt; // single thread or multi-threading

    };





    bool
    DetSimAlg::finalize()
    {
        if (is_mt) {
            return true;
        }

        LogInfo << objName()
                << " finalized successfully"
                << std::endl;
        if (m_vis_mac.length()) {
            // If user set the vis mac file,
            // start to run the GUI
            return true;
        }
        if (run_manager) {
            run_manager->finalizeRM();
        }
        return true;
    }







G4Svc double delete protection
--------------------------------

::

     jcv G4Svc   ## add below protection
     ljbb0       ## OJ update build


::

    Changes not staged for commit:
      (use "git add <file>..." to update what will be committed)
      (use "git restore <file>..." to discard changes in working directory)
        modified:   Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h
        modified:   Simulation/DetSimV2/G4Svc/src/G4Svc.cc

    no changes added to commit (use "git add" and/or "git commit -a")
    (ok) A[blyth@localhost junosw]$ git diff 
    diff --git a/Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h b/Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h
    index 30628f40..bc6f9dda 100644
    --- a/Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h
    +++ b/Simulation/DetSimV2/G4Svc/G4Svc/G4Svc.h
    @@ -14,9 +14,22 @@ class G4Svc: public IG4Svc, public SvcBase {
     
             G4SvcRunManager* getRunMgr();
     
    +        static bool& is_deleted() {
    +             static bool deleted = false;
    +             return deleted;
    +        }
    +
         private:
             G4SvcRunManager* m_runmgr;
     
    +
    +
    +
     };
     
    +
    +
    +
    +
    +
     #endif
    diff --git a/Simulation/DetSimV2/G4Svc/src/G4Svc.cc b/Simulation/DetSimV2/G4Svc/src/G4Svc.cc
    index 1984f8a8..e9ffd8d1 100644
    --- a/Simulation/DetSimV2/G4Svc/src/G4Svc.cc
    +++ b/Simulation/DetSimV2/G4Svc/src/G4Svc.cc
    @@ -13,13 +13,25 @@ G4Svc::G4Svc(const std::string& name)
         m_runmgr = new G4SvcRunManager;
     }
     
    +
    +
    +
    +
    +
     G4Svc::~G4Svc()
     {
    +    if (is_deleted()) {
    +        std::cout << "WARNING: G4Svc destructor called TWICE! Blocking second delete." << std::endl;
    +        return; 
    +    }
    + 
    +
         LogDebug << "Delete G4SvcRunManager in G4Svc" << std::endl;
         if (m_runmgr) {
             delete m_runmgr;
         }
         m_runmgr = NULL;
    :




HUH with the G4Svc double delete protection, the SIGABRT still happening::

    [Thread 0x7fffcd5ff640 (LWP 1358286) exited]
    Delete G4SvcRunManager
    double free or corruption (out)

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
    #4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
    #5  0x00007ffff7497c70 in _int_free () from /lib64/libc.so.6
    #6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
    #7  0x00007ffff74412dd in __run_exit_handlers () from /lib64/libc.so.6
    #8  0x00007ffff7441430 in exit () from /lib64/libc.so.6
    #9  0x00007ffff74295d7 in __libc_start_call_main () from /lib64/libc.so.6
    #10 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #11 0x0000000000401075 in _start ()
    (gdb) 



::

     BP=G4Svc::~G4Svc ojt dbg



This is a major breakthrough. If you implemented the "Double Delete Protection"
in G4Svc and the crash still happens, it means the G4Svc instance itself is
being destroyed twice, but each destruction is happening to a different
instance of G4Svc that manages the same G4SvcRunManager address.

This effectively confirms a Symbol Conflict caused by your static linking of
Opticks.
The Breakdown: Two Services, One Pointer

Here is the likely architecture of the failure:

    The "Official" Service: Sniper loads libG4Svc.so dynamically. It creates an
instance of G4Svc (let's call it Svc_A). Svc_A creates G4SvcRunManager at
address 0x65d7750.

    The "Ghost" Service: Because your Opticks-convert code is statically linked
and likely includes G4Svc.h or triggers a registration macro, a second instance
or a duplicate set of static symbols for G4Svc exists in memory (let's call it
Svc_B).

    The Collision: Due to how symbols are resolved in Linux, Svc_B ends up
pointing to the exact same m_runmgr address as Svc_A.

    The Teardown:

        Destruction 1: Sniper cleans up. Svc_A's destructor runs. It sees
m_runmgr is not null, deletes it, and sets its local m_runmgr = NULL.

        Destruction 2: Python/Static cleanup runs. Svc_B's destructor runs.
Because Svc_B is a different object in memory, its m_runmgr variable is still
pointing to 0x65d7750. It doesn't know Svc_A already deleted it. It calls
delete again.

        BOOM: SIGABRT.





Thread 1 "python" hit Breakpoint 1.2, G4Svc::~G4Svc (this=0x663a7a0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:35
35	}
Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
(gdb) bt
#0  G4Svc::~G4Svc (this=0x663a7a0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:35
#1  0x00007fffd24c6513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#2  0x00007fffd24c6e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#3  0x00007fffd24deb4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#4  0x00007fffd24dbf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#5  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
#6  0x00007fffd4856d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#7  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffcd629990) at Objects/typeobject.c:1463
#8  0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#9  Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#10 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
#11 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff77100d0) at Objects/typeobject.c:1433
#12 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#13 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#14 free_keys_object (keys=0x7ffff7e7bd20) at Objects/dictobject.c:664
#15 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
#16 dict_dealloc (mp=0x7ffff76e6000) at Objects/dictobject.c:2378
#17 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#18 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#19 module_dealloc (m=0x7ffff76be9d0) at Objects/moduleobject.c:699
#20 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#21 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#22 insertdict (mp=0x7ffff7e45340, key=0x7ffff76e6030, hash=7472098547170181186, value=<optimized out>) at Objects/dictobject.c:1304
#23 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e45340) at Python/pylifecycle.c:1415
#24 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
#25 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
#26 Py_FinalizeEx () at Python/pylifecycle.c:1751
#27 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
#28 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeab0) at Modules/main.c:714
#29 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
#30 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
#31 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
#32 0x0000000000401075 in _start ()
(gdb) c
Continuing.

Thread 1 "python" hit Breakpoint 1.1, G4Svc::~G4Svc (this=0x663a7a0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:21
21	G4Svc::~G4Svc()
(gdb) bt
#0  G4Svc::~G4Svc (this=0x663a7a0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:21
#1  0x00007fffc6b9d7b4 in G4Svc::~G4Svc (this=0x663a7a0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:35
#2  0x00007fffd24c6513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#3  0x00007fffd24c6e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#4  0x00007fffd24deb4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#5  0x00007fffd24dbf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
#6  0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
#7  0x00007fffd4856d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
#8  0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffcd629990) at Objects/typeobject.c:1463
#9  0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#10 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#11 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
#12 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff77100d0) at Objects/typeobject.c:1433
#13 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#14 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#15 free_keys_object (keys=0x7ffff7e7bd20) at Objects/dictobject.c:664
#16 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
#17 dict_dealloc (mp=0x7ffff76e6000) at Objects/dictobject.c:2378
#18 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#19 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#20 module_dealloc (m=0x7ffff76be9d0) at Objects/moduleobject.c:699
#21 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
#22 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
#23 insertdict (mp=0x7ffff7e45340, key=0x7ffff76e6030, hash=7472098547170181186, value=<optimized out>) at Objects/dictobject.c:1304
#24 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e45340) at Python/pylifecycle.c:1415
#25 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
#26 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
#27 Py_FinalizeEx () at Python/pylifecycle.c:1751
#28 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
#29 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeab0) at Modules/main.c:714
#30 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
#31 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
#32 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
#33 0x0000000000401075 in _start ()
(gdb) c
Continuing.
Delete G4SvcRunManager
double free or corruption (out)

Thread 1 "python" received signal SIGABRT, Aborted.
0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
(gdb) 




ctor only once::

    2026-04-01 15:27:44,569] p1361682 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNODetSimModule.py:1935} INFO - [init_op_simulator
    [2026-04-01 15:27:44,569] p1361682 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNODetSimModule.py:1955} INFO - [init_detector_simulation

    Thread 1 "python" hit Breakpoint 1, G4Svc::G4Svc (this=0x663a7a0, name=...) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:10
    10	    : SvcBase(name)
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  G4Svc::G4Svc (this=0x663a7a0, name=...) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:10
    #1  0x00007fffc6b9dd9f in SniperCreateDLE_T<G4Svc> (name=...) at /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/include/SniperKernel/DeclareDLE.h:38
    #2  0x00007fffd24bd411 in DLEFactory::create(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #3  0x00007fffd24c7242 in ExecUnit::createSvc(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffccbc12f6 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<SvcBase* (ExecUnit::*)(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&), boost::python::return_value_policy<boost::python::reference_existing_object, boost::python::default_call_policies>, boost::mpl::vector3<SvcBase*, ExecUnit&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #5  0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #6  0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #7  0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #8  0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #9  0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x60087e0, args=<optimized out>, nargs=2, keywords=0x0) at Objects/call.c:214
    #10 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e6000, func=0x7ffff76e9f80, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #13 PyEval_EvalCode (co=co@entry=0x4d03d0, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000) at Python/ceval.c:1148
    #14 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e6000, globals=0x7ffff76e6000, co=0x4d03d0, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #15 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cac90, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000, flags=flags@entry=0x7ffffffee9a8, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #16 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffee9a8, closeit=<optimized out>, locals=0x7ffff76e6000, globals=0x7ffff76e6000, start=257, filename=0x7ffff76cac90, fp=0x42f4a0) at Python/pythonrun.c:1657
    #17 _PyRun_SimpleFileObject (fp=fp@entry=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee9a8) at Python/pythonrun.c:440
    #18 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffee9a8) at Python/pythonrun.c:79
    #19 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cac90, program_name=0x7ffff7e26b80) at Modules/main.c:360
    #20 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #21 pymain_run_python (exitcode=0x7ffffffee9a4) at Modules/main.c:605
    #22 Py_RunMain () at Modules/main.c:684
    #23 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeab0) at Modules/main.c:714
    #24 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #25 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #26 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #27 0x0000000000401075 in _start ()
    (gdb) c
    Continuing.

    **************************************************************
     Geant4 version Name: geant4-10-04-patch-02 [MT]   (25-May-2018)
                           Copyright : Geant4 Collaboration
                          References : NIM A 506 (2003), 250-303
                                     : IEEE-TNS 53 (2006), 270-278
                                     : NIM A 835 (2016), 186-225
                                 WWW : http://geant4.org/
    **************************************************************

    Create G4SvcRunManager
    [2026-04-01 15:28:08,808] p1361682 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNODetSimModule.py:2322} INFO - [init_detsim_detcomp
    GLb3.up11.try_init_model        INFO: Initialize model GLb3
    GLb3.up11.try_init_model_shell  INFO: HBeam (row):  R: 17050 L: 347.826
    GLb4.up10.try_init_model        INFO: Initialize model GLb4
    GLb4.up10.try_init_model_shell  INFO: HBeam (row):  R: 17050 L: 716.726




G4Svc ctor once, dtor twice with same address
-----------------------------------------------


If you hit the Constructor once but the Destructor twice with the exact same
this address, you have found a classic "Double-Free via Object Aliasing" in a
hybrid Python/C++ environment.

This specific symptom—same this pointer, multiple destructor calls—is almost
always caused by Python and C++ both claiming ownership of the same memory
address.






The "Double free or corruption" occurs because:

    The VTable is pointing to the wrong place: If your Opticks-convert library
was compiled with a slightly different version of Geant4 or a different
compiler flag than the rest of JUNO, the VTable offsets for G4RunManager will
be wrong.

    When G4Svc calls delete m_runmgr, it looks at the VTable to find the
destructor. If that VTable has been "interposed" by your statically linked
Opticks library, it jumps to the wrong destructor code or tries to free a
pointer that was never a heap-allocated object.










A[blyth@localhost oj]$ echo $LD_LIBRARY_PATH | tr ":" "\n"
/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/junosw/InstallArea/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/mt.sniper/InstallArea/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libonnxruntime/1.17.3/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libmore/0.8.3/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/nuwro/21.09.2/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/genie/3.04.02/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/lib64

         OOPS THAT SHOULD BE 0.1.9  ??????????
         OPTICKS AND JUNOSW NEED TO BE USING CONSISTENT custom4 LIBS

/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/HepMC/2.06.11/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/xrootd/5.7.3/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/xrootd/5.7.3/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/CLHEP/2.4.7.1/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/tbb/2020.3/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/pythia6/6.4.28/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/LHAPDF/6.3.0/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libxml2/2.9.12/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/log4cpp/1.1.3/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/HDF5/1.14.3/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/frontier/2.10.2/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/pacparser/1.4.2/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/mysql-connector-cpp/1.1.12/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/mysql-connector-c/6.1.9/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/sqlite3/3.38.5/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/fftw3/3.3.10/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/gsl/2.7/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Xercesc/3.2.4/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libyaml/0.2.4/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Python/3.11.10/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/binutils/2.35.2/lib64
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/binutils/2.35.2/lib

/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/CLHEP/2.4.7.1/lib
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/Xercesc/3.2.4/lib
/data1/blyth/local/opticks_Debug/lib
/data1/blyth/local/opticks_Debug/lib64
/data1/blyth/local/opticks_Debug/externals/lib
/data1/blyth/local/opticks_Debug/externals/lib64
/usr/local/cuda-12.4/lib64
A[blyth@localhost oj]$ l /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/lib64/
total 108
  1 drwxr-xr-x. 3 cvmfs cvmfs     60 Oct 21  2024 .
  1 drwxr-xr-x. 4 cvmfs cvmfs     82 Oct 21  2024 ..
  1 drwxr-xr-x. 2 cvmfs cvmfs     79 Oct 21  2024 Custom4-0.1.8
107 -rwxr-xr-x. 1 cvmfs cvmfs 108728 Oct 21  2024 libCustom4.so
A[blyth@localhost oj]$ nm 




nm -A /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so | c++filt 

nm -A /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so  | c++filt | grep G4




A[blyth@localhost oj]$ ldd /data1/blyth/local/opticks_Debug/lib64/libG4CX.so
	linux-vdso.so.1 (0x00007ffc30d40000)
	libU4.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libU4.so (0x00007f5672b86000)
	libCSGOptiX.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libCSGOptiX.so (0x00007f56729bf000)
	libG4Tree.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4Tree.so (0x00007f56729aa000)
	libG4FR.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4FR.so (0x00007f5672993000)
	libG4GMocren.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4GMocren.so (0x00007f5672943000)
	libG4visHepRep.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4visHepRep.so (0x00007f56728a6000)
	libG4RayTracer.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4RayTracer.so (0x00007f5672876000)
	libG4VRML.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4VRML.so (0x00007f567285b000)
	libG4vis_management.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4vis_management.so (0x00007f567274f000)
	libG4modeling.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4modeling.so (0x00007f567267a000)
	libG4interfaces.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4interfaces.so (0x00007f5672628000)
	libG4persistency.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4persistency.so (0x00007f56724c7000)
	libG4analysis.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4analysis.so (0x00007f5671e00000)
	libG4error_propagation.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4error_propagation.so (0x00007f567248a000)
	libG4readout.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4readout.so (0x00007f567247d000)
	libG4physicslists.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4physicslists.so (0x00007f5671c51000)
	libG4run.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so (0x00007f56723f2000)
	libG4event.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4event.so (0x00007f5672371000)
	libG4tracking.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4tracking.so (0x00007f567231f000)
	libG4parmodels.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4parmodels.so (0x00007f5672305000)
	libG4processes.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so (0x00007f5670400000)
	libG4digits_hits.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4digits_hits.so (0x00007f5670337000)
	libG4track.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4track.so (0x00007f5671c2e000)
	libG4particles.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4particles.so (0x00007f56701fa000)
	libG4geometry.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4geometry.so (0x00007f566fe00000)
	libG4materials.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4materials.so (0x00007f5670120000)
	libG4graphics_reps.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4graphics_reps.so (0x00007f56700d9000)
	libG4intercoms.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4intercoms.so (0x00007f566fd8e000)
	libG4global.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4global.so (0x00007f566fd2f000)
	libG4zlib.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4zlib.so (0x00007f56700be000)
	libCLHEP-2.4.7.1.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/CLHEP/2.4.7.1/lib/libCLHEP-2.4.7.1.so (0x00007f566fbc8000)
	libGDXML.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libGDXML.so (0x00007f566fbac000)
	libxerces-c-3.2.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Xercesc/3.2.4/lib/libxerces-c-3.2.so (0x00007f566f800000)
	libCustom4.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/lib64/libCustom4.so (0x00007f566f7e7000)
	libCSG.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libCSG.so (0x00007f566f400000)
	libcudart.so.12 => /usr/local/cuda-12.4/lib64/libcudart.so.12 (0x00007f566f000000)
	libQUDARap.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libQUDARap.so (0x00007f566da00000)
	libSysRap.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libSysRap.so (0x00007f566d000000)
	libOKConf.so => /data1/blyth/local/opticks_Debug/lib64/../lib64/libOKConf.so (0x00007f56722f7000)
	libcrypto.so.3 => /lib64/libcrypto.so.3 (0x00007f566ca00000)
	libssl.so.3 => /lib64/libssl.so.3 (0x00007f566f307000)
	libstdc++.so.6 => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/lib64/libstdc++.so.6 (0x00007f566c600000)
	libm.so.6 => /lib64/libm.so.6 (0x00007f566ef25000)
	libgcc_s.so.1 => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/lib64/libgcc_s.so.1 (0x00007f566f7b7000)





[blyth@localhost oj]$ local_c4_prefix
/data1/blyth/local/custom4_Debug/0.1.9
A[blyth@localhost oj]$ 


HMM GENERATED bashrc IS OK::

    A[blyth@localhost customgeant4]$ cat /data1/blyth/local/custom4_Debug/0.1.9/bashrc 
    ## generated Tue Mar 31 03:06:27 PM CST 2026 by /home/blyth/customgeant4/generate_bashrc.sh generate_bashrc

    if [ -z "${JUNOTOP}" ]; then
    export JUNO_EXTLIB_custom4_HOME=/data1/blyth/local/custom4_Debug/0.1.9
    else
    export JUNO_EXTLIB_custom4_HOME=/data1/blyth/local/custom4_Debug/0.1.9
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

    A[blyth@localhost customgeant4]$ 



IT CANNOT BE BEING SOURCED...


    A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ cat /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/bashrc.sh
    export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/binutils/2.35.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/gcc/11.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/contrib/go/1.20.6/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/junoenv/etc/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Git/2.46.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/git-lfs/3.4.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Cmake/3.30.5/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Python/3.11.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/python-setuptools/69.5.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/python-pip/23.3.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/python-cython/3.0.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/python-numpy/1.26.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libyaml/0.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Xercesc/3.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/gsl/2.7/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/fftw3/3.3.10/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/eigen/3.4.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/sqlite3/3.38.5/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/mysql-connector-c/6.1.9/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/mysql-connector-cpp/1.1.12/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/pacparser/1.4.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/frontier/2.10.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/HDF5/1.14.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/log4cpp/1.1.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libxml2/2.9.12/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/LHAPDF/6.3.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/pythia6/6.4.28/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/tbb/2020.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/CLHEP/2.4.7.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/xrootd/5.7.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/HepMC/2.06.11/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/genie/3.04.02/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/nuwro/21.09.2/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/talys/1.95/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/gibuu/r2023_02_juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libmore/0.8.3/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/libonnxruntime/1.17.3/bashrc
    A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ 


 A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ local_c4_prefix_default
/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/custom4/0.1.8
A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ 
A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ 
A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ local_c4_prefix
/data1/blyth/local/custom4_Debug/0.1.9





[blyth@localhost junosw]$ ldd /home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/lib64/libPhysiSim.so
	linux-vdso.so.1 (0x00007ffd13334000)
	libDetSimAlg.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/junosw/InstallArea/lib64/libDetSimAlg.so (0x00007f3ac7d95000)
	libMCParamsSvcLib.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/junosw/InstallArea/lib64/libMCParamsSvcLib.so (0x00007f3ac7d90000)
	libPMTSimParamSvcLib.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/junosw/InstallArea/lib64/libPMTSimParamSvcLib.so (0x00007f3ac7d89000)
	libCustom4.so => /data1/blyth/local/custom4_Debug/0.1.9/lib64/libCustom4.so (0x00007f3ac7d68000)
	libG4CX.so => /data1/blyth/local/opticks_Debug/lib64/libG4CX.so (0x00007f3ac7c60000)
	libG4SvcLib.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/junosw/InstallArea/lib64/libG4SvcLib.so (0x00007f3ac7c5a000)
	libG4Tree.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4Tree.so (0x00007f3ac7c45000)
	libG4GMocren.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4GMocren.so (0x00007f3ac7bf3000)
	libG4FR.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4FR.so (0x00007f3ac7bdc000)
	libG4visHepRep.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4visHepRep.so (0x00007f3ac7b3f000)
	libG4RayTracer.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4RayTracer.so (0x00007f3ac7b11000)
	libG4VRML.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4VRML.so (0x00007f3ac7af6000)
	libG4OpenGL.so => /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4OpenGL.so (0x00007f3ac7aaf000)
	libSM.so.6 => /lib64/libSM.so.6 (0x00007f3ac7a8d000)
	libICE.so.6 => /lib64/libICE.so.6 (0x00007f3ac7a6f000)
	libX11.so.6 => /lib64/libX11.so.6 (0x00007f3ac7927000)
	libXext.so.6 => /lib64/libXext.so.6 (0x00007f3ac7912000)
	libXmu.so.6 => /lib64/libXmu.so.6 (0x00007f3ac78f5000)

   





    A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ cat /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/custom4/0.1.8/bashrc
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
    A[blyth@localhost blyth-geometry-config-needed-for-EMF-opticks-convert]$ 



HMM : SOME PATH SURGERY IS NEEDED TO USE 0.1.9 : DID THIS BEFORE ?
-----------------------------------------------------------------------

::

    298 local_JUNOTOP_override()
    299 {
    300 
    301    : change PATH LD_LIBRARY_PATH PKG_CONFIG_PATH CPATH MANPATH CMAKE_PREFIX_PATH
    302    : in order to use different prefix of an external
    303 
    304    source ~/j/JUNOTOP/JUNOTOP_change_paths.sh
    305    JUNOTOP_change_paths custom4 $(local_c4_prefix)
    306 
    307    : HMM when building JUNOSW against different Custom4 will need to
    308    : also build Opticks against that same Custom4 FIRST
    309 }
    310 






HMM : PROBLEM MAY BE THAT THE RUNTIME ENV IS NOT FIXED UP, ONLY THE BUILD TIME ENV...
----------------------------------------------------------------------------------------

* after the TEST.sh sources the ENVSET.sh NEED TO RUN THE FIXUP : FOR THE RUNTIME ENV
  TO CORRESPOND TO BUILD TIME ?

* to fit in with the OJ testing pattern need to make a special envset.sh with the override





AFTER FIXING (?) THE RUNTIME VS BUILD TIME ENV DIFFERENCE : GET DIFFERENT ERROR
--------------------------------------------------------------------------------



This successful termination with HARD_EXIT dumps SniperProfiling::

    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 709.11401 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 709.11298 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.13600        1.13600      0.00016      
    DetSimAlg                1           711.30298      711.30298    0.10127      
    Sum of junotoptask       1           712.44098      712.44098    0.08767      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
 



::

    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 686.74298 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 686.74103 ms

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc6cc5df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffc6cc5df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #1  0x00007fffe0584727 in G4SvcRunManager::finalizeRM (this=0x65b3940) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #2  0x00007fffce088e8f in DetSimAlg::finalize (this=0x67120d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #3  0x00007fffd24c5d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd24dad6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd24e3588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd24de611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd24db05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #9  0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #11 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #12 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #13 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x600aa10, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #14 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #15 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e6000, func=0x7ffff76e9f80, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #17 PyEval_EvalCode (co=co@entry=0x4d0360, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000) at Python/ceval.c:1148
    #18 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e6000, globals=0x7ffff76e6000, co=0x4d0360, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #19 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cac90, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000, flags=flags@entry=0x7ffffffeea98, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #20 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffeea98, closeit=<optimized out>, locals=0x7ffff76e6000, globals=0x7ffff76e6000, start=257, filename=0x7ffff76cac90, fp=0x42f4a0) at Python/pythonrun.c:1657
    #21 _PyRun_SimpleFileObject (fp=fp@entry=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeea98) at Python/pythonrun.c:440
    #22 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeea98) at Python/pythonrun.c:79
    #23 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cac90, program_name=0x7ffff7e26b80) at Modules/main.c:360
    #24 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #25 pymain_run_python (exitcode=0x7ffffffeea94) at Modules/main.c:605
    #26 Py_RunMain () at Modules/main.c:684
    #27 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeba0) at Modules/main.c:714
    #28 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #29 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #30 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #31 0x0000000000401075 in _start ()
    (gdb) 



::

    00348 void G4RunManagerKernel::RunTermination()
    00349 { G4StateManager::GetStateManager()->SetNewState(G4State_Idle); }
    00350 


SEGV from there must mean the state manager was deleted already ?






Check if HARD_EXIT still avoids the crash::

    A[blyth@localhost junosw]$ vi InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py


    log.info("[juno_application.run")
    juno_application.run()
    log.info("]juno_application.run")

    if "HARD_EXIT" in os.environ:
        log.info("doing HARD_EXIT")
        os._exit(0)
    else:
        log.info("not doing HARD_EXIT")
    pass



In fresh tab::
     
     [blyth@localhost oj]$ oj
     [blyth@localhost oj]$ HARD_EXIT=1 ojt db


HARD_EXIT still avoids the cleanup issue::

    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 709.11401 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 709.11298 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.13600        1.13600      0.00016      
    DetSimAlg                1           711.30298      711.30298    0.10127      
    Sum of junotoptask       1           712.44098      712.44098    0.08767      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2026-04-01 17:40:56,416] p2489334 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2026-04-01 17:40:56,416] p2489334 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:55} INFO - ]juno_application.run
    [2026-04-01 17:40:56,416] p2489334 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:58} INFO - doing HARD_EXIT
    [Thread 0x7fffbcfff640 (LWP 2489359) exited]
    [Thread 0x7fffcd5ff640 (LWP 2489348) exited]
    [Inferior 1 (process 2489334) exited normally]
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) 






Is Opticks holding on to run manager ?
----------------------------------------

::

    (ok) A[blyth@localhost opticks]$ opticks-f G4RunManager

    ./g4cx/tests/G4CXApp.h:#include "G4RunManager.hh"
    ./g4cx/tests/G4CXApp.h:    G4RunManager*         fRunMgr ;
    ./g4cx/tests/G4CXApp.h:    G4CXApp(G4RunManager* runMgr);
    ./g4cx/tests/G4CXApp.h:    static G4RunManager* InitRunManager();
    ./g4cx/tests/G4CXApp.h:G4CXApp::G4CXApp(G4RunManager* runMgr)
    ./g4cx/tests/G4CXApp.h:G4RunManager* G4CXApp::InitRunManager()  // static
    ./g4cx/tests/G4CXApp.h:    G4RunManager* run = new G4RunManager ;
    ./g4cx/tests/G4CXApp.h:Geant4 requires G4RunManager to be instanciated prior to the Actions
    ./g4cx/tests/G4CXApp.h:    G4RunManager* run = InitRunManager();
    ./g4cx/tests/G4CXTest_GEOM.sh:  G4RunManager::BeamOn
    ./g4cx/tests/G4CXTest_GEOM.sh:  G4RunManager::GenerateEvent

    ./sysrap/SEventConfig.cc:    #9  0x00007fffc67ca92e in G4RunManager::InitializeGeometry() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.4.0/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    ./sysrap/tests/SStackFrameTest.cc:11  libG4run.dylib                      0x00000001086e79f5 _ZN12G4RunManager15ProcessOneEventEi + 69
    ./sysrap/tests/SStackFrameTest.cc:12  libG4run.dylib                      0x00000001086e7825 _ZN12G4RunManager11DoEventLoopEiPKci + 101
    ./sysrap/tests/SStackFrameTest.cc:13  libG4run.dylib                      0x00000001086e5ce1 _ZN12G4RunManager6BeamOnEiPKci + 193
    ./sysrap/tests/SStackFrameTest.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager15ProcessOneEventEi+0x57) [0x7ffff3c82665] 
    ./sysrap/tests/SStackFrameTest.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager11DoEventLoopEiPKci+0x59) [0x7ffff3c824d7] 
    ./sysrap/tests/SStackFrameTest.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager6BeamOnEiPKci+0xc1) [0x7ffff3c81d2d] 
    ./sysrap/tests/SStackFrame_test.cc:11  libG4run.dylib                      0x00000001086e79f5 _ZN12G4RunManager15ProcessOneEventEi + 69
    ./sysrap/tests/SStackFrame_test.cc:12  libG4run.dylib                      0x00000001086e7825 _ZN12G4RunManager11DoEventLoopEiPKci + 101
    ./sysrap/tests/SStackFrame_test.cc:13  libG4run.dylib                      0x00000001086e5ce1 _ZN12G4RunManager6BeamOnEiPKci + 193
    ./sysrap/tests/SStackFrame_test.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager15ProcessOneEventEi+0x57) [0x7ffff3c82665] 
    ./sysrap/tests/SStackFrame_test.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager11DoEventLoopEiPKci+0x59) [0x7ffff3c824d7] 
    ./sysrap/tests/SStackFrame_test.cc:/home/blyth/local/opticks/externals/lib64/libG4run.so(_ZN12G4RunManager6BeamOnEiPKci+0xc1) [0x7ffff3c81d2d] 

    ./u4/U4App.h:#include "G4RunManager.hh"
    ./u4/U4App.h:    G4RunManager*         fRunMgr ;  
    ./u4/U4App.h:    U4App(G4RunManager* runMgr); 
    ./u4/U4App.h:    static G4RunManager* InitRunManager(); 
    ./u4/U4App.h:U4App::U4App(G4RunManager* runMgr)
    ./u4/U4App.h:G4RunManager* U4App::InitRunManager()  // static
    ./u4/U4App.h:    G4RunManager* run = new G4RunManager ; 
    ./u4/U4App.h:Geant4 requires G4RunManager to be instanciated prior to the Actions 
    ./u4/U4App.h:    G4RunManager* run = InitRunManager(); 
    ./u4/tests/U4AppTest.cc:    G4RunManager* runMgr = new G4RunManager ;



Bizarre : running again gives different error
-----------------------------------------------

::

    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 820.13397 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 820.13397 ms
    ############################## SniperProfiling ##############################
    Name                     Count       Total(ms)      Mean(ms)     RMS(ms)      
    GenTools                 1           1.35900        1.35900      0.00003      
    DetSimAlg                1           823.00403      823.00403    0.00000      
    Sum of junotoptask       1           824.36700      824.36700    0.00000      
    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2026-04-01 18:00:22,936] p2494151 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2026-04-01 18:00:22,937] p2494151 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:55} INFO - ]juno_application.run
    [2026-04-01 18:00:22,937] p2494151 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:61} INFO - not doing HARD_EXIT
    Namespace(help_more=False, loglevel='Info', dryrun=False, showTime=False, evtmax=1, seed=42, restore_seed_status=None, input=None, input_list=None, input_correlation=None, input_correlation_list=None, output='output.root', user_output='user_output.root', EnableUserOutput=False, output_stream=None, output_reproducible=False, profiling=True, profiling_with_details=False, toptask_show=True, restore_evtid_list='', start_evtid=0, dbtype='File', PDEValue=0.0, paradb=False, para_gtag='J22.1.0', dbconf=None, config_gen_materials=None, config_gen_exec=None, mac='run.mac', vis=False, vis_mac='vis.mac', detsim=True, detoption='Acrylic', qescale=1.0, light_yield=None, gdml=False, dae=False, splitevent=True, event_split_maxhits=None, splittrack=False, track_split_mode='PrimaryTrack', track_split_time=3000.0, pelletron=False, source=False, source_weights=False, source_weight_QC=False, ACU_source_weight_QC=False, CLS_source_weight_QC=False, ACU_source_weight_QC_Ti=False, CLS_source_weight_QC_Ti=False, K40_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC=False, AmC_ACU_source_weight_QC_thicker=False, AmC_ACU_source_weight_QC_thickest=False, submarine=False, OffsetInZ=0, OffsetInX=0, OffsetInY=0, GT_source_theta=0, guide_tube=True, dfball_tube=False, teflonhook=False, dflightcos=True, simplify_calib_anchor=True, cd_enabled=True, reflectivity=0.4, isgroundsurface=True, real_surface_in_cd_enabled=True, strut_complex_geometry=False, strut_surface_enabled=True, acrylic_repairs=False, segmented_water_distributor=True, real_mask_tail=True, mask_tail_surface_enabled=True, optical_surface_in_cd_enabled=True, check_overlap_in_cd_enabled=False, wp_enabled=True, wp_pmt_enabled=True, wp_latticed_enabled=True, water_distributor_enabled=True, emf_coils_system_enabled=True, emf_support_bars_enabled=True, emf_steel_reflectivity=0.535, tt_enabled=True, shutter=False, lchimneywater=False, uchimneywater=False, botchimneywater=False, commissioning_enabled=False, below_z_is_water=0.0, use_elecroom=True, rock_thickness=10000.0, pmt20inch=True, pmt20inch_name='PMTMask', pmt20inch_obsolete_torus_neck=False, pmt20inch_profligate_tail_cut=False, debug_disable_sticks=False, debug_disable_st=False, debug_disable_xj=False, debug_disable_sj=False, debug_disable_fa=False, pmt20inch_plus_dynode=False, pmt20inch_extra='TWO-mask', pmtmask_top_thick=10.0, pmt3inch=True, pmt3inch_name='Tub3inchV3', pmt3inch_offset=-50.0, ranges_pmt_enabled=None, ranges_pmt_constructed=None, construct_center_pmtid=-1, distance_to_center_pmt=-1, pmt_dbtype='IDService', new_optical_model=False, MaterialDataDir=None, pmtsd_v2=True, ce_mode='20inch', ce_flat_value=0.9, ce_func=None, ce_func_par=None, pmtsd_merge_twindow=1.0, useoptical=True, cerenkov_only=False, cerenkov=True, cerenkov_type='modified', opabs=True, opsct=True, pmt_optical_model=True, pmt_natural_geometry=True, track_op_first=True, deferred_op=False, deferred_op_testing_ratio=1.0, preselect=None, usingLS=False, cutEdep_in_ls=0, opticks_mode=0, opticks_anamgr=False, replace_param='Material.LS.scale.AbsorptionLenAfter:86.5,Material.Water.scale.abs_after:133.6*m', usepmtsimsvc=True, quenching=True, pmt_hit_type=2, pmt_disable_process=False, photon_conversion=False, nphotonsperparticle=10, fixed_energy=None, physics_list='JUNO', positronium=True, use_stepfunc_in_macro=False, enableIonPHP=True, flag_struts_fasteners='none', anamgr_grdm=True, stopAtPa234m=True, anamgr_edm=False, anamgr_edm_v2=True, anamgr_simtrack=True, anamgr_hitcollection='hitCollection', anamgr_edm_gen=True, anamgr_tt=True, anamgr_normal=True, anamgr_normal_hit=False, use_given_velocity=True, anamgr_muon=True, anamgr_atmo=False, anamgr_genevt=True, anamgr_deposit=True, anamgr_deposit_tt=True, anamgr_deposit_voxel=False, anamgr_deposit_voxelsize=100, anamgr_interesting_process=True, anamgr_extra_procnames=None, anamgr_legacy_michel_electron=False, anamgr_legacy_ncapture=False, anamgr_legacy_decay=False, anamgr_neutron_inelastic=False, anamgr_optical_parameter=True, anamgr_timer=True, enable_zero_step_check=False, zero_step_threshold=100, anamgr_photon_tracking=False, anamgr_g4tracking_verbose=None, anamgr_g4tracking_evtlist=None, anamgr_list=[], anamgr_config_file=None, voxel_fast_sim=False, voxel_merge_flag=False, voxel_merge_twin=1, voxel_fill_ntuple=False, voxel_fast_dir=None, voxel_geom_file='geom-geom-20pmt.root', voxel_npe_file='npehist3d_single.root', voxel_time_file='dist_tres_single.root', voxel_gen_npe=True, voxel_gen_time=True, voxel_save_hits=True, voxel_pmts_structs=True, voxel_quenching_scale=0.93, global_time_begin='1970-01-01 00:00:01', global_time_end='2038-01-19 03:14:07', global_event_rate=0.0, gentool_mode='gun', material='None', volume='None', volume_radius_min=0.0, volume_radius_max=0.0, volume_z_min=None, volume_z_max=None, volume_x_min=None, volume_x_max=None, volume_y_min=None, volume_y_max=None, volume_rock_depth=None, global_position=None, particles='gamma', momentums=1.0, momentums_mode='Fix', momentums_extra_params=None, momentums_interp='Momentum', positions=[(0, 0, 0)], times=None, directions=None)
    [Thread 0x7fffcd5ff640 (LWP 2494164) exited]
    G4Svc: First-time destruction of 0x65489b0
    Delete G4SvcRunManager

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc529d6a4 in G4ProductionCutsTable::~G4ProductionCutsTable() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffc529d6a4 in G4ProductionCutsTable::~G4ProductionCutsTable() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #1  0x00007ffff74412dd in __run_exit_handlers () from /lib64/libc.so.6
    #2  0x00007ffff7441430 in exit () from /lib64/libc.so.6
    #3  0x00007ffff74295d7 in __libc_start_call_main () from /lib64/libc.so.6
    #4  0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #5  0x0000000000401075 in _start ()
    (gdb) 



Try clean build:  ljbb0c
-------------------------

Then test:

     oj
     ojt dbg


After clean build, stays same::

    #############################################################################
    junotoptask:SniperProfiling.finalize  INFO: finalized successfully
    junotoptask:PMTSimParamSvc.finalize  INFO: PMTSimParamSvc is finalizing!
    junotoptask.finalize            INFO: events processed 1
    [2026-04-01 20:09:30,741] p3777348 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/python/Tutorial/JUNOApplication.py:225} INFO - ]JUNOApplication.run
    [2026-04-01 20:09:30,741] p3777348 {/home/blyth/junosw/InstallArea/blyth-geometry-config-needed-for-EMF-opticks-convert/bin/tut_detsim.py:55} INFO - ]juno_application.run
    [Thread 0x7fffcd5ff640 (LWP 3777366) exited]
    G4Svc: First-time destruction of 0x65df1d0
    Delete G4SvcRunManager

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc529d6a4 in G4ProductionCutsTable::~G4ProductionCutsTable() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    (gdb) bt
    #0  0x00007fffc529d6a4 in G4ProductionCutsTable::~G4ProductionCutsTable() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #1  0x00007ffff74412dd in __run_exit_handlers () from /lib64/libc.so.6
    #2  0x00007ffff7441430 in exit () from /lib64/libc.so.6
    #3  0x00007ffff74295d7 in __libc_start_call_main () from /lib64/libc.so.6
    #4  0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #5  0x0000000000401075 in _start ()
    (gdb) 



Another run and the SEGV happens earlier::


    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 1
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 687.77899 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 687.77502 ms

    Thread 1 "python" received signal SIGSEGV, Segmentation fault.
    0x00007fffc6cc5df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 nvidia-driver-cuda-libs-580.82.07-1.el9.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007fffc6cc5df5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #1  0x00007fffe0584727 in G4SvcRunManager::finalizeRM (this=0x65b3940) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #2  0x00007fffce088e8f in DetSimAlg::finalize (this=0x67120d0) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #3  0x00007fffd24c5d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #4  0x00007fffd24dad6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #5  0x00007fffd24e3588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #6  0x00007fffd24de611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #7  0x00007fffd24db05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #8  0x00007fffccbd38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*)
        () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #9  0x00007fffd485a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #10 0x00007fffd485a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) ()
       from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #11 0x00007fffd485f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #12 0x00007fffd4858182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #13 0x00007ffff7959cc3 in _PyObject_MakeTpCall (tstate=0x7ffff7d79738 <_PyRuntime+166328>, callable=0x600aa10, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #14 0x00007ffff78fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #15 0x00007ffff7a4f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7ffff7fb2020, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7ffff76e6000, func=0x7ffff76e9f80, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #17 PyEval_EvalCode (co=co@entry=0x4d0360, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000) at Python/ceval.c:1148
    #18 0x00007ffff7a980ed in run_eval_code_obj (locals=0x7ffff76e6000, globals=0x7ffff76e6000, co=0x4d0360, tstate=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #19 run_mod (mod=<optimized out>, filename=filename@entry=0x7ffff76cac90, globals=globals@entry=0x7ffff76e6000, locals=locals@entry=0x7ffff76e6000, flags=flags@entry=0x7ffffffeea98, arena=arena@entry=0x7ffff7de2b70)
        at Python/pythonrun.c:1762
    #20 0x00007ffff7a998ab in pyrun_file (flags=0x7ffffffeea98, closeit=<optimized out>, locals=0x7ffff76e6000, globals=0x7ffff76e6000, start=257, filename=0x7ffff76cac90, fp=0x42f4a0) at Python/pythonrun.c:1657
    #21 _PyRun_SimpleFileObject (fp=fp@entry=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeea98) at Python/pythonrun.c:440
    #22 0x00007ffff7a99e5b in _PyRun_AnyFileObject (fp=0x42f4a0, filename=filename@entry=0x7ffff76cac90, closeit=closeit@entry=1, flags=flags@entry=0x7ffffffeea98) at Python/pythonrun.c:79
    #23 0x00007ffff7ab9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7ffff76cac90, program_name=0x7ffff7e26b80) at Modules/main.c:360
    #24 pymain_run_file (config=0x7ffff7d5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #25 pymain_run_python (exitcode=0x7ffffffeea94) at Modules/main.c:605
    #26 Py_RunMain () at Modules/main.c:684
    #27 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeba0) at Modules/main.c:714
    #28 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #29 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #30 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #31 0x0000000000401075 in _start ()
    (gdb) 


Skip the opticks conversion and the cleanup crash happens elsewhere::

    Thread 0x7fffcd5ff640 (LWP 291741) exited]
    Delete G4SvcRunManager
    free(): invalid pointer

    Thread 1 "python" received signal SIGABRT, Aborted.
    0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    Missing separate debuginfos, use: dnf debuginfo-install bzip2-libs-1.0.8-10.el9_5.x86_64 cyrus-sasl-lib-2.1.27-21.el9.x86_64 expat-2.5.0-5.el9_6.x86_64 freetype-2.10.4-10.el9_5.x86_64 glib2-2.68.4-16.el9_6.2.x86_64 glibc-2.34-168.el9_6.23.x86_64 graphite2-1.3.14-9.el9.x86_64 harfbuzz-2.7.4-10.el9.x86_64 keyutils-libs-1.6.3-1.el9.x86_64 krb5-libs-1.21.1-8.el9_6.x86_64 libICE-1.0.10-8.el9.x86_64 libXau-1.0.9-8.el9.x86_64 libXext-1.3.4-8.el9.x86_64 libXmu-1.1.3-8.el9.x86_64 libXt-1.2.0-6.el9.x86_64 libbrotli-1.0.9-7.el9_5.x86_64 libcom_err-1.46.5-7.el9.x86_64 libcurl-7.76.1-31.el9_6.1.x86_64 libevent-2.1.12-8.el9_4.x86_64 libffi-3.4.2-8.el9.x86_64 libglvnd-1.3.4-1.el9.x86_64 libglvnd-glx-1.3.4-1.el9.x86_64 libicu-67.1-10.el9_6.x86_64 libidn2-2.3.0-7.el9.x86_64 libnghttp2-1.43.0-6.el9.x86_64 libnsl2-2.0.0-1.el9.x86_64 libpng-1.6.37-12.el9.x86_64 libselinux-3.6-3.el9.x86_64 libssh-0.10.4-13.el9.x86_64 libtirpc-1.3.3-9.el9.x86_64 libunistring-0.9.10-15.el9.x86_64 libuuid-2.37.4-21.el9.x86_64 libxcb-1.13.1-9.el9.x86_64 libxcrypt-4.4.18-3.el9.x86_64 libzstd-1.5.5-1.el9.x86_64 mesa-libGLU-9.0.1-6.el9.x86_64 ncurses-libs-6.2-10.20210508.el9_6.2.x86_64 openldap-2.6.8-4.el9.x86_64 openssl-libs-3.5.1-7.el9_7.x86_64 pcre-8.44-4.el9.x86_64 readline-8.1-4.el9.x86_64 xz-libs-5.2.5-8.el9_0.x86_64
    (gdb) bt
    #0  0x00007ffff748bedc in __pthread_kill_implementation () from /lib64/libc.so.6
    #1  0x00007ffff743eb46 in raise () from /lib64/libc.so.6
    #2  0x00007ffff7428833 in abort () from /lib64/libc.so.6
    #3  0x00007ffff7429172 in __libc_message.cold () from /lib64/libc.so.6
    #4  0x00007ffff7495f87 in malloc_printerr () from /lib64/libc.so.6
    #5  0x00007ffff749783c in _int_free () from /lib64/libc.so.6
    #6  0x00007ffff749a2c5 in free () from /lib64/libc.so.6
    #7  0x00007fffc5da0c67 in G4ProcessVector::~G4ProcessVector() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #8  0x00007fffc5da0c89 in G4ProcessVector::~G4ProcessVector() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #9  0x00007fffc5d90147 in G4ProcessManager::~G4ProcessManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4processes.so
    #10 0x00007fffc6cdc923 in G4VUserPhysicsList::RemoveProcessManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #11 0x00007fffc6cdcb6e in G4VUserPhysicsList::~G4VUserPhysicsList() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #12 0x00007fffbd56c880 in LSExpPhysicsList::~LSExpPhysicsList (this=0xac8e650, __in_chrg=<optimized out>, __vtt_parm=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpPhysicsList.cc:152
    #13 0x00007fffbd56c8a8 in LSExpPhysicsList::~LSExpPhysicsList (this=0xac8e650, __in_chrg=<optimized out>, __vtt_parm=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/DetSimOptions/src/LSExpPhysicsList.cc:152
    #14 0x00007fffc6cb4c7f in G4RunManager::DeleteUserInitializations() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #15 0x00007fffc6cb605b in G4RunManager::~G4RunManager() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #16 0x00007fffe058459f in G4SvcRunManager::~G4SvcRunManager (this=0x669ff40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #17 0x00007fffe05845ba in G4SvcRunManager::~G4SvcRunManager (this=0x669ff40, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:11
    #18 0x00007fffc6b9d6db in G4Svc::~G4Svc (this=0x65489b0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:20
    #19 0x00007fffc6b9d72e in G4Svc::~G4Svc (this=0x65489b0, __in_chrg=<optimized out>) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4Svc.cc:23
    #20 0x00007fffd24c6513 in DleSupervisor::clear() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #21 0x00007fffd24c6e0d in ExecUnit::reset() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #22 0x00007fffd24deb4b in TaskWatchDog::terminate() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #23 0x00007fffd24dbf64 in Task::~Task() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #24 0x00007fffccbd983c in boost::python::objects::value_holder<TopTask>::~value_holder() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #25 0x00007fffd4856d4f in instance_dealloc () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #26 0x00007ffff79c0ae2 in subtype_dealloc (self=0x7fffc1504db0) at Objects/typeobject.c:1463
    #27 0x00007ffff799eeae in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #28 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #29 _PyObject_FreeInstanceAttributes (self=<optimized out>) at Objects/dictobject.c:5583
    #30 0x00007ffff79c0bf3 in subtype_dealloc (self=0x7ffff77101d0) at Objects/typeobject.c:1433
    #31 0x00007ffff79963ad in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #32 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #33 free_keys_object (keys=0x7ffff7e7bd20) at Objects/dictobject.c:664
    #34 0x00007ffff799730c in dictkeys_decref (dk=<optimized out>) at Objects/dictobject.c:324
    #35 dict_dealloc (mp=0x7ffff76e6000) at Objects/dictobject.c:2378
    #36 0x00007ffff79a9ae5 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #37 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #38 module_dealloc (m=0x7ffff76be9d0) at Objects/moduleobject.c:699
    #39 0x00007ffff799a3d0 in Py_DECREF (op=<optimized out>) at ./Include/object.h:538
    #40 Py_XDECREF (op=<optimized out>) at ./Include/object.h:602
    #41 insertdict (mp=0x7ffff7e45340, key=0x7ffff76e6030, hash=-2961300368424893728, value=<optimized out>) at Objects/dictobject.c:1304
    #42 0x00007ffff7a8faa8 in finalize_remove_modules (verbose=0, modules=0x7ffff7e45340) at Python/pylifecycle.c:1415
    #43 finalize_modules (tstate=tstate@entry=0x7ffff7d79738 <_PyRuntime+166328>) at Python/pylifecycle.c:1550
    #44 0x00007ffff7a92e20 in Py_FinalizeEx () at Python/pylifecycle.c:1833
    #45 Py_FinalizeEx () at Python/pylifecycle.c:1751
    #46 0x00007ffff7ab8bc4 in Py_RunMain () at Modules/main.c:686
    #47 0x00007ffff7ab95b7 in pymain_main (args=0x7ffffffeeba0) at Modules/main.c:714
    #48 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #49 0x00007ffff74295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #50 0x00007ffff7429680 in __libc_start_main_impl () from /lib64/libc.so.6
    #51 0x0000000000401075 in _start ()
    (gdb) 





doublemuon termination issue, hmm maybe HARD_EXIT not always preventing the issue::

    A[blyth@localhost oj]$ ojt run




    2026-04-02 00:24:44.588 [junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 6452269 GPU NO
    2026-04-02 00:24:44.588 ]junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 0 hitCollection 0 hitCollectionAlt -1 hcMuon 6452269 GPU NO
    hitCollectionTT.size: 136	userhitCollectionTT.size: 68
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split begin. 2026-04-01 16:24:45.308762000Z
    junotoptask:DetSimAlg.DataModelWriterWithSplit.EndOfEventAction  INFO: writing events with split end. 2026-04-01 16:24:51.271025000Z
    end of event action 
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 30150.00000 / 30150.00000
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.check_init_same  WARN: Init Z are not consistent: 30150.00000 / 30150.00000
    junotoptask:DetSimAlg.GenEvtInfoAnaMgr.EndOfEventAction  WARN: Check Init Info Consitent failed.
    end of event action 
    junotoptask:detsimiotask.finalize  INFO: events processed 646
    junotoptask:DetSimAlg.finalize  INFO: DetSimAlg finalized successfully
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO: All the collected process names: 
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] nCapture
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hadElastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] neutronInelastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] Decay
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] protonInelastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hadElastic
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] muPairProd
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hBertiniCaptureAtRest
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] phot
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] compt
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] PsFormation
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muonNuclear
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] conv
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] hIoni
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] eBrem
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [ ] muBrems
    junotoptask:DetSimAlg.InteresingProcessAnaMgr.EndOfRunAction  INFO:  -  [x] RadioactiveDecay
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: summaries: 
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: number of measurements: 1
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: mean time: 10447380.00000 ms
    junotoptask:DetSimAlg.TimerAnaMgr.EndOfRunAction  INFO: total time elapsed: 10447380.00000 ms
     *** Break *** segmentation violation



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 2 (Thread 0x7f5f882ff640 (LWP 634088) "python"):
    #0  0x00007f5fb228722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f5fb228996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f5fb284df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f5fb2b50f38 <_PyRuntime+440>, cond=0x7f5fb2b50f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x7285530) at Python/ceval_gil.h:231
    #4  0x00007f5fb284e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x7285530) at Python/ceval.c:521
    #5  0x00007f5fb2915894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f5fb27a88f2 in cfunction_vectorcall_O (func=0x7f5fb25a7970, args=0x7f5f9e0f31e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f5fb275a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f5fb25a7970, tstate=0x7285530) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f5fb25a7970, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f5fb284f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f5f9e0f3188, tstate=0x7285530) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x7285530, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f5fb2701e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f5fa49e7f00, callargs=0x7f5fa49936a0, func=0x7f5fa497fa60, tstate=0x7285530) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f5fb284f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f5f9e0f3020, tstate=0x7285530) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x7285530, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f5fb275cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f5f882feda8, callable=0x7f5fa4922ca0, tstate=0x7285530) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f5fb2b5f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f5fb2913fe2 in thread_run (boot_raw=0x67d2c80) at ./Modules/_threadmodule.c:1124
    #20 0x00007f5fb28a87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f5fb228a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f5fb230f240 in clone3 () from /lib64/libc.so.6

    Thread 1 (Thread 0x7f5fb2c68740 (LWP 634059) "python"):
    #0  0x00007f5fb22d8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f5fb224b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f5fa44f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f5fb2be70f3 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f5fa44f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f5f85a6fdf5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007f5f9b184727 in G4SvcRunManager::finalizeRM (this=0x7e3b770) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #8  0x00007f5f8bbb5e8f in DetSimAlg::finalize (this=0x7fda280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #9  0x00007f5f8fb36d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007f5f8fb4bd6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007f5f8fb54588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007f5f8fb4f611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007f5f8fb4c05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f5f878d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007f5f9a02a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007f5f9a02a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007f5f9a02f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007f5f9a028182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007f5fb2759cc3 in _PyObject_MakeTpCall (tstate=0x7f5fb2b79738 <_PyRuntime+166328>, callable=0x77b8110, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007f5fb284f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f5fb2d52020, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f5fa4b46280, func=0x7f5fa4b49f80, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co
    entry=0x1cddb40, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280) at Python/ceval.c:1148
    #24 0x00007f5fb28980ed in run_eval_code_obj (locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, co=0x1cddb40, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename
    entry=0x7f5fa4b2ac90, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280, flags=flags
    entry=0x7ffd8470e9b8, arena=arena
    entry=0x7f5fb251ab70) at Python/pythonrun.c:1762
    #26 0x00007f5fb28998ab in pyrun_file (flags=0x7ffd8470e9b8, closeit=<optimized out>, locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, start=257, filename=0x7f5fa4b2ac90, fp=0x1bf84c0) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp
    entry=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:440
    #28 0x00007f5fb2899e5b in _PyRun_AnyFileObject (fp=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:79
    #29 0x00007f5fb28b9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7f5fa4b2ac90, program_name=0x7f5fb255eb80) at Modules/main.c:360
    #30 pymain_run_file (config=0x7f5fb2b5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffd8470e9b4) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007f5fb28b95b7 in pymain_main (args=0x7ffd8470eac0) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007f5fb22295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007f5fb2229680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    ===========================================================


    The lines below might hint at the cause of the crash. If you see question
    marks as part of the stack trace, try to recompile with debugging information
    enabled and export CLING_DEBUG=1 environment variable before running.
    You may get help by asking at the ROOT forum https://root.cern/forum
    preferably using the command (.forum bug) in the ROOT prompt.
    Only if you are really convinced it is a bug in ROOT then please submit a
    report at https://root.cern/bugs or (preferably) using the command (.gh bug) in
    the ROOT prompt. Please post the ENTIRE stack trace
    from above as an attachment in addition to anything else
    that might help us fixing this issue.
    ===========================================================
    #6  0x00007f5f85a6fdf5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007f5f9b184727 in G4SvcRunManager::finalizeRM (this=0x7e3b770) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #8  0x00007f5f8bbb5e8f in DetSimAlg::finalize (this=0x7fda280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #9  0x00007f5f8fb36d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007f5f8fb4bd6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007f5f8fb54588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007f5f8fb4f611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007f5f8fb4c05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f5f878d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007f5f9a02a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007f5f9a02a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007f5f9a02f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007f5f9a028182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007f5fb2759cc3 in _PyObject_MakeTpCall (tstate=0x7f5fb2b79738 <_PyRuntime+166328>, callable=0x77b8110, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007f5fb284f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f5fb2d52020, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f5fa4b46280, func=0x7f5fa4b49f80, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co
    entry=0x1cddb40, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280) at Python/ceval.c:1148
    #24 0x00007f5fb28980ed in run_eval_code_obj (locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, co=0x1cddb40, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename
    entry=0x7f5fa4b2ac90, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280, flags=flags
    entry=0x7ffd8470e9b8, arena=arena
    entry=0x7f5fb251ab70) at Python/pythonrun.c:1762
    #26 0x00007f5fb28998ab in pyrun_file (flags=0x7ffd8470e9b8, closeit=<optimized out>, locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, start=257, filename=0x7f5fa4b2ac90, fp=0x1bf84c0) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp
    entry=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:440
    #28 0x00007f5fb2899e5b in _PyRun_AnyFileObject (fp=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:79
    #29 0x00007f5fb28b9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7f5fa4b2ac90, program_name=0x7f5fb255eb80) at Modules/main.c:360
    #30 pymain_run_file (config=0x7f5fb2b5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffd8470e9b4) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007f5fb28b95b7 in pymain_main (args=0x7ffd8470eac0) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007f5fb22295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007f5fb2229680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    ===========================================================


     *** Break *** segmentation violation



    ===========================================================
    There was a crash.
    This is the entire stack trace of all threads:
    ===========================================================

    Thread 2 (Thread 0x7f5f882ff640 (LWP 634088) "python"):
    #0  0x00007f5fb228722a in __futex_abstimed_wait_common () from /lib64/libc.so.6
    #1  0x00007f5fb228996f in pthread_cond_timedwait

    GLIBC_2.3.2 () from /lib64/libc.so.6
    #2  0x00007f5fb284df4f in PyCOND_TIMEDWAIT (us=<optimized out>, mut=0x7f5fb2b50f38 <_PyRuntime+440>, cond=0x7f5fb2b50f08 <_PyRuntime+392>) at Python/condvar.h:73
    #3  take_gil (tstate=tstate
    entry=0x7285530) at Python/ceval_gil.h:231
    #4  0x00007f5fb284e43e in PyEval_RestoreThread (tstate=tstate
    entry=0x7285530) at Python/ceval.c:521
    #5  0x00007f5fb2915894 in pysleep (timeout=<optimized out>) at ./Modules/timemodule.c:2168
    #6  time_sleep (self=<optimized out>, timeout_obj=<optimized out>) at ./Modules/timemodule.c:383
    #7  0x00007f5fb27a88f2 in cfunction_vectorcall_O (func=0x7f5fb25a7970, args=0x7f5f9e0f31e8, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/methodobject.c:514
    #8  0x00007f5fb275a2d4 in _PyObject_VectorcallTstate (kwnames=<optimized out>, nargsf=<optimized out>, args=<optimized out>, callable=0x7f5fb25a7970, tstate=0x7285530) at ./Include/internal/pycore_call.h:92
    #9  PyObject_Vectorcall (callable=0x7f5fb25a7970, args=<optimized out>, nargsf=<optimized out>, kwnames=<optimized out>) at Objects/call.c:299
    #10 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #11 0x00007f5fb284f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f5f9e0f3188, tstate=0x7285530) at ./Include/internal/pycore_ceval.h:73
    #12 _PyEval_Vector (tstate=0x7285530, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #13 0x00007f5fb2701e42 in do_call_core (use_tracing=<optimized out>, kwdict=0x7f5fa49e7f00, callargs=0x7f5fa49936a0, func=0x7f5fa497fa60, tstate=0x7285530) at Python/ceval.c:7349
    #14 _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:5376
    #15 0x00007f5fb284f1d1 in _PyEval_EvalFrame (throwflag=0, frame=0x7f5f9e0f3020, tstate=0x7285530) at ./Include/internal/pycore_ceval.h:73
    #16 _PyEval_Vector (tstate=0x7285530, func=<optimized out>, locals=<optimized out>, args=<optimized out>, argcount=<optimized out>, kwnames=<optimized out>) at Python/ceval.c:6434
    #17 0x00007f5fb275cc6c in _PyObject_VectorcallTstate (kwnames=0x0, nargsf=1, args=0x7f5f882feda8, callable=0x7f5fa4922ca0, tstate=0x7285530) at ./Include/internal/pycore_call.h:92
    #18 method_vectorcall (method=<optimized out>, args=0x7f5fb2b5f3b0 <_PyRuntime+58928>, nargsf=<optimized out>, kwnames=0x0) at Objects/classobject.c:67
    #19 0x00007f5fb2913fe2 in thread_run (boot_raw=0x67d2c80) at ./Modules/_threadmodule.c:1124
    #20 0x00007f5fb28a87b7 in pythread_wrapper (arg=<optimized out>) at Python/thread_pthread.h:241
    #21 0x00007f5fb228a19a in start_thread () from /lib64/libc.so.6
    #22 0x00007f5fb230f240 in clone3 () from /lib64/libc.so.6

    Thread 1 (Thread 0x7f5fb2c68740 (LWP 634059) "python"):
    #0  0x00007f5fb22d8fff in wait4 () from /lib64/libc.so.6
    #1  0x00007f5fb224b7e3 in do_system () from /lib64/libc.so.6
    #2  0x00007f5fa44f6bcc in TUnixSystem::StackTrace() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #3  0x00007f5fb2be6f73 in (anonymous namespace)::TExceptionHandlerImp::HandleException(int) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libcppyy_backend3_11.so
    #4  0x00007f5fa44f4161 in TUnixSystem::DispatchSignals(ESignals) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/ROOT/6.30.08/lib/libCore.so
    #5  <signal handler called>
    #6  0x00007f5f85a6fdf5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007f5f9b184727 in G4SvcRunManager::finalizeRM (this=0x7e3b770) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #8  0x00007f5f8bbb5e8f in DetSimAlg::finalize (this=0x7fda280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #9  0x00007f5f8fb36d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007f5f8fb4bd6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007f5f8fb54588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007f5f8fb4f611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007f5f8fb4c05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f5f878d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007f5f9a02a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007f5f9a02a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007f5f9a02f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007f5f9a028182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007f5fb2759cc3 in _PyObject_MakeTpCall (tstate=0x7f5fb2b79738 <_PyRuntime+166328>, callable=0x77b8110, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007f5fb284f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f5fb2d52020, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f5fa4b46280, func=0x7f5fa4b49f80, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co
    entry=0x1cddb40, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280) at Python/ceval.c:1148
    #24 0x00007f5fb28980ed in run_eval_code_obj (locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, co=0x1cddb40, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename
    entry=0x7f5fa4b2ac90, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280, flags=flags
    entry=0x7ffd8470e9b8, arena=arena
    entry=0x7f5fb251ab70) at Python/pythonrun.c:1762
    #26 0x00007f5fb28998ab in pyrun_file (flags=0x7ffd8470e9b8, closeit=<optimized out>, locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, start=257, filename=0x7f5fa4b2ac90, fp=0x1bf84c0) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp
    entry=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:440
    #28 0x00007f5fb2899e5b in _PyRun_AnyFileObject (fp=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:79
    #29 0x00007f5fb28b9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7f5fa4b2ac90, program_name=0x7f5fb255eb80) at Modules/main.c:360
    #30 pymain_run_file (config=0x7f5fb2b5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffd8470e9b4) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007f5fb28b95b7 in pymain_main (args=0x7ffd8470eac0) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007f5fb22295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007f5fb2229680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    ===========================================================


    The lines below might hint at the cause of the crash. If you see question
    marks as part of the stack trace, try to recompile with debugging information
    enabled and export CLING_DEBUG=1 environment variable before running.
    You may get help by asking at the ROOT forum https://root.cern/forum
    preferably using the command (.forum bug) in the ROOT prompt.
    Only if you are really convinced it is a bug in ROOT then please submit a
    report at https://root.cern/bugs or (preferably) using the command (.gh bug) in
    the ROOT prompt. Please post the ENTIRE stack trace
    from above as an attachment in addition to anything else
    that might help us fixing this issue.
    ===========================================================
    #6  0x00007f5f85a6fdf5 in G4RunManagerKernel::RunTermination() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Geant4/10.04.p02.juno/lib64/libG4run.so
    #7  0x00007f5f9b184727 in G4SvcRunManager::finalizeRM (this=0x7e3b770) at /home/blyth/junosw/Simulation/DetSimV2/G4Svc/src/G4SvcRunManager.cc:41
    #8  0x00007f5f8bbb5e8f in DetSimAlg::finalize (this=0x7fda280) at /home/blyth/junosw/Simulation/DetSimV2/DetSimAlg/src/DetSimAlg.cc:136
    #9  0x00007f5f8fb36d3a in DleSupervisor::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #10 0x00007f5f8fb4bd6b in Task::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #11 0x00007f5f8fb54588 in TopTask::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #12 0x00007f5f8fb4f611 in TaskWatchDog::finalize() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #13 0x00007f5f8fb4c05c in Task::run() () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/lib64/libSniperKernel.so
    #14 0x00007f5f878d38d3 in boost::python::objects::caller_py_function_impl<boost::python::detail::caller<bool (Task::*)(), boost::python::default_call_policies, boost::mpl::vector2<bool, Task&> > >::operator()(_object*, _object*) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/sniper/InstallArea/python/Sniper/libSniperPython.so
    #15 0x00007f5f9a02a515 in boost::python::objects::function::call(_object*, _object*) const () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #16 0x00007f5f9a02a728 in boost::detail::function::void_function_ref_invoker<boost::python::objects::(anonymous namespace)::bind_return, void>::invoke(boost::detail::function::function_buffer&) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #17 0x00007f5f9a02f443 in boost::python::handle_exception_impl(boost::function_n<void>) () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #18 0x00007f5f9a028182 in function_call () from /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.7.2/ExternalLibs/Boost/1.85.0/lib/libboost_python311.so.1.85.0
    #19 0x00007f5fb2759cc3 in _PyObject_MakeTpCall (tstate=0x7f5fb2b79738 <_PyRuntime+166328>, callable=0x77b8110, args=<optimized out>, nargs=1, keywords=0x0) at Objects/call.c:214
    #20 0x00007f5fb26fe606 in _PyEval_EvalFrameDefault (tstate=<optimized out>, frame=<optimized out>, throwflag=<optimized out>) at Python/ceval.c:4769
    #21 0x00007f5fb284f06f in _PyEval_EvalFrame (throwflag=0, frame=0x7f5fb2d52020, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at ./Include/internal/pycore_ceval.h:73
    #22 _PyEval_Vector (args=0x0, argcount=0, kwnames=0x0, locals=0x7f5fa4b46280, func=0x7f5fa4b49f80, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/ceval.c:6434
    #23 PyEval_EvalCode (co=co
    entry=0x1cddb40, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280) at Python/ceval.c:1148
    #24 0x00007f5fb28980ed in run_eval_code_obj (locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, co=0x1cddb40, tstate=0x7f5fb2b79738 <_PyRuntime+166328>) at Python/pythonrun.c:1741
    #25 run_mod (mod=<optimized out>, filename=filename
    entry=0x7f5fa4b2ac90, globals=globals
    entry=0x7f5fa4b46280, locals=locals
    entry=0x7f5fa4b46280, flags=flags
    entry=0x7ffd8470e9b8, arena=arena
    entry=0x7f5fb251ab70) at Python/pythonrun.c:1762
    #26 0x00007f5fb28998ab in pyrun_file (flags=0x7ffd8470e9b8, closeit=<optimized out>, locals=0x7f5fa4b46280, globals=0x7f5fa4b46280, start=257, filename=0x7f5fa4b2ac90, fp=0x1bf84c0) at Python/pythonrun.c:1657
    #27 _PyRun_SimpleFileObject (fp=fp
    entry=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:440
    #28 0x00007f5fb2899e5b in _PyRun_AnyFileObject (fp=0x1bf84c0, filename=filename
    entry=0x7f5fa4b2ac90, closeit=closeit
    entry=1, flags=flags
    entry=0x7ffd8470e9b8) at Python/pythonrun.c:79
    #29 0x00007f5fb28b9060 in pymain_run_file_obj (skip_source_first_line=0, filename=0x7f5fa4b2ac90, program_name=0x7f5fb255eb80) at Modules/main.c:360
    #30 pymain_run_file (config=0x7f5fb2b5f780 <_PyRuntime+59904>) at Modules/main.c:379
    #31 pymain_run_python (exitcode=0x7ffd8470e9b4) at Modules/main.c:605
    #32 Py_RunMain () at Modules/main.c:684
    #33 0x00007f5fb28b95b7 in pymain_main (args=0x7ffd8470eac0) at Modules/main.c:714
    #34 Py_BytesMain (argc=<optimized out>, argv=<optimized out>) at Modules/main.c:738
    #35 0x00007f5fb22295d0 in __libc_start_call_main () from /lib64/libc.so.6
    #36 0x00007f5fb2229680 in __libc_start_main_impl () from /lib64/libc.so.6
    #37 0x0000000000401075 in _start ()
    ===========================================================


    WARNING - Attempt to delete the physical volume store while geometry closed !
    WARNING - Attempt to delete the logical volume store while geometry closed !
    WARNING - Attempt to delete the solid store while geometry closed !
    Command terminated by signal 11
    10482.90user 9.99system 2:55:30elapsed 99%CPU (0avgtext+0avgdata 3596824maxresident)k
    16inputs+292584outputs (27major+1183808minor)pagefaults 0swaps
                       BASH_SOURCE : /home/blyth/oj/doublemuon/doublemuon.sh
                      BASH_VERSION : 5.1.8(1)-release
                          FUNCNAME : vvp
                                 1 : 
                                 2 : 
                             xname : 
                            _xhome : 
                             xhome : 
                             yhome : 
                            change : 
                               MSG : OPTICKS RUNNING
                           LOGNAME : OJ_LOCAL_blyth-geometry-config-needed-for-EMF-opticks-convert_2026Apr01_ok0_zerohitlite_seed42_evtmax1_run.log
                           ENVNAME : OJ_LOCAL_blyth-geometry-config-needed-for-EMF-opticks-convert_2026Apr01_ok0_zerohitlite_seed42_evtmax1_run.env
                                d0 : Wed Apr  1 09:29:34 PM CST 2026
                                d1 : Thu Apr  2 12:25:05 AM CST 2026
                                dt : 10531
    ~/oj/doublemuon
    A[blyth@localhost oj]$ 



