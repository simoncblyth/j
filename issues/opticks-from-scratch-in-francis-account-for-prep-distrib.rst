opticks-from-scratch-in-francis-account-for-prep-distrib
==========================================================

Overview
----------

Test opticks fresh build and okdist-- creation of binary distribution 
in a clean user environment in the "francis" account on laptop
and "simon" account on workstation. 

As that worked proceeded to also do the same for laptop "blyth" account.

Workstation "blyth" is a bit more complicated as thats integrated
with junosw. 



Documenting this in j initially to prevent changes to opticks repo
while doing distribution testing. 


Doing the same on workstation/simon (R)
-----------------------------------------

::

    epsilon:issues blyth$ ssh R 
    Last login: Thu Nov  2 20:25:36 2023 from lxslc708.ihep.ac.cn
    (base) [simon@localhost ~]$ pwd
    /home/simon
    (base) [simon@localhost ~]$ l
    total 4
    drwxrwxr-x. 2 simon simon 4096 Sep 29  2019 CerenkovMinimal
    drwxrwxr-x. 9 simon simon  249 Feb 17  2021 G4OpticksTest_fork
    drwxrwxr-x. 8 simon simon  201 Jul  5  2020 junotop
    drwxrwxr-x. 3 simon simon   31 Oct 31 15:29 local
    lrwxrwxrwx. 1 simon simon   19 Dec 18  2020 opticks -> /home/blyth/opticks
    (base) [simon@localhost ~]$     


get opticks
--------------

Instead of cloning, plant a symbolic link into other "blyth" account::

   cd
   #git clone https://bitbucket.org/simoncblyth/opticks.git
   ln -s /Users/blyth/opticks


fresh_build.sh testing
------------------------

* opticks-full in "francis" account on laptop : for a fresh install to test okdist with
* populate OPTICKS_DOWNLOAD_CACHE /data/opticks_download_cache on laptop first 
  to speedup interations of fresh_build.sh 

::

    epsilon:issues blyth$ ssh F
    Last login: Mon Nov  6 09:41:31 2023 from 127.0.0.1
    epsilon:~ francis$ pwd
    /Users/francis

    epsilon:~ francis$ cat fresh_build.sh 
    #!/bin/bash -l 

    rm -rf local/opticks
    opticks-full


Outcome : fresh_build taking 7min on laptop/francis 4 min on workstation/simon 
------------------------------------------------------------------------------

FIXED : okdist-prefix issue
-----------------------------

::

    (base) [simon@localhost ~]$ okdist-
    (base) [simon@localhost ~]$ okdist-prefix
    Opticks-0.0.0_alpha/x86_64-centos7-gcc83-geant4_10_04_p02-dbg


    epsilon:opticks francis$ okdist-prefix
    Configured with: --prefix=/Applications/Xcode/Xcode_9_2.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
    Opticks-0.0.0_alpha/i386-UNKNOWN-gcc9077-geant4_10_04_p02-dbg
    epsilon:opticks francis$ 


    epsilon:opticks blyth$ t okdist-prefix
    okdist-prefix () 
    { 
        echo $(okdist-title)-$(okdist-version)/$(opticks-okdist-dirlabel)
    }
    epsilon:opticks blyth$ okdist-title
    Opticks
    epsilon:opticks blyth$ okdist-version
    0.0.0_alpha
    epsilon:opticks blyth$ opticks-okdist-dirlabel
    Configured with: --prefix=/Applications/Xcode/Xcode_9_2.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
    i386-UNKNOWN-gcc9077-geant4_10_04_p02-dbg
    epsilon:opticks blyth$ 

::

    epsilon:opticks blyth$ opticks-okdist-dirlabel
    i386-10.13.6-gcc4.2.1-geant4_10_04_p02-dbg
    epsilon:opticks blyth$ 



Issue 2 : laptop/francis 42/205 installed ctests fails for lack of GEOM
--------------------------------------------------------------------------

::

    opticks-cd tests
    ctest 

Add symbolic link::

    lrwxr-xr-x  1 francis  staff  26 Nov  6 11:23 GEOM -> /Users/blyth/.opticks/GEOM


Issue 3 : 17/205 fails in laptop/francis
-------------------------------------------

::

    92% tests passed, 17 tests failed out of 205

    Total Test time (real) = 155.79 sec

    The following tests FAILED:
         80 - SysRapTest.stranTest (INTERRUPT)
        112 - CSGTest.CSGPrimImpTest (Failed)
        131 - CSGTest.CUTest (Failed)
        152 - QUDARapTest.QRngTest (Failed)
        153 - QUDARapTest.QScintTest (Failed)
        156 - QUDARapTest.QSimTest (Failed)
        157 - QUDARapTest.QOpticalTest (Failed)
        158 - QUDARapTest.QPropTest (Failed)
        159 - QUDARapTest.QEventTest (Failed)
        160 - QUDARapTest.QSimWithEventTest (Failed)
        161 - QUDARapTest.QSimCreateTest (Failed)
        162 - QUDARapTest.QUTest (Failed)
        163 - QUDARapTest.QTexMakerTest (Failed)
        164 - QUDARapTest.QTexLookupTest (Failed)
        165 - QUDARapTest.QBufTest (Failed)
        179 - U4Test.U4RandomTest (Failed)
        203 - CSGOptiXTest.CSGOptiXRenderTest (Failed)
    Errors while running CTest
    epsilon:tests francis$ 




::

    epsilon:tests francis$ ctest -R stranTest --output-on-failure
    Test project /Users/francis/local/opticks/tests
        Start 80: SysRapTest.stranTest
    1/1 Test #80: SysRapTest.stranTest .............***Exception: Interrupt  0.02 sec
    NP::load Failed to load from path /Users/francis/.opticks/InputPhotons/RandomDisc100_f8.npy


    0% tests passed, 1 tests failed out of 1

    Total Test time (real) =   0.04 sec

    The following tests FAILED:
         80 - SysRapTest.stranTest (INTERRUPT)
    Errors while running CTest
    epsilon:tests francis$ 




::

    epsilon:tests francis$ ctest -R CUTest --output-on-failure
    Test project /Users/francis/local/opticks/tests
        Start 131: CSGTest.CUTest
    1/1 Test #131: CSGTest.CUTest ...................***Failed    0.28 sec
                    HOME : /Users/francis
                     PWD : /Users/francis/local/opticks/tests/CSG/tests
                    GEOM : V1J011
             BASH_SOURCE : /Users/francis/opticks/CSG/tests/CSGTestRunner.sh
              EXECUTABLE : CUTest
                    ARGS : 
    libc++abi.dylib: terminating with uncaught exception of type sutil::CUDA_Exception: CUDA call (cudaMalloc(reinterpret_cast<void**>( &d_array ), num_bytes ) ) failed with error: 'no CUDA-capable device is detected' (/Users/francis/opticks/CSG/CU.cc:101)

    /Users/francis/opticks/CSG/tests/CSGTestRunner.sh: line 25: 76945 Abort trap: 6           $EXECUTABLE $@
    /Users/francis/opticks/CSG/tests/CSGTestRunner.sh : FAIL from CUTest


    0% tests passed, 1 tests failed out of 1

    Total Test time (real) =   0.30 sec

    The following tests FAILED:
        131 - CSGTest.CUTest (Failed)
    Errors while running CTest
    epsilon:tests francis$ 


