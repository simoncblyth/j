offline-opticks-test-fails
-----------------------------



Remaining FAIL is from lack of PYTHONPATH setup
--------------------------------------------------

Looks like the below is not automated::

    105 
    106 sysrap-csg-generate()
    107 {
    108     local msg="$FUNCNAME : "
    109     local iwd=$PWD
    110     sysrap-cd
    111     c_enums_to_python.py OpticksCSG.h
    112 
    113     echo $msg To write above generated python to OpticksCSG.py ..
    114 
    115     local ans
    116     read -p "Enter YES ... " ans
    117 
    118     if [  "$ans" == "YES" ]; then
    119        c_enums_to_python.py OpticksCSG.h > OpticksCSG.py
    120 
    121        echo $msg checking the generated python is valid 
    122        python  OpticksCSG.py
    123 
    124     else
    125        echo $msg SKIP
    126     fi
    127 
    128     cd $iwd
    129 }
    130 



Is everything installed under py::

    epsilon:opticks blyth$ find $OPTICKS_PREFIX/py
    /usr/local/opticks/py
    /usr/local/opticks/py/opticks
    /usr/local/opticks/py/opticks/ana
    /usr/local/opticks/py/opticks/ana/histype.py
    /usr/local/opticks/py/opticks/ana/evt.py
    /usr/local/opticks/py/opticks/ana/abstat.py
    /usr/local/opticks/py/opticks/ana/ab.py
    /usr/local/opticks/py/opticks/ana/dat.py
    /usr/local/opticks/py/opticks/ana/metadata.py
    /usr/local/opticks/py/opticks/ana/env.py
    /usr/local/opticks/py/opticks/ana/nibble.py
    /usr/local/opticks/py/opticks/ana/mattype.py

Because its too tedious to keep installing the python after changes, its much 
better to grab from source dirs. 



Tue : down to 1 FAIL
----------------------

::

    SLOW: tests taking longer that 15 seconds
      4  /16  Test #4  : QUDARapTest.QCerenkovIntegralTest             Passed                         33.65  


    FAILS:  1   / 541   :  Wed Dec 15 04:40:19 2021   
      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      7.90   
    N[blyth@localhost opticks]$ 


    Missing PYTHONPATH
    N[blyth@localhost opticks]$ echo $PYTHONPATH | tr ":" "\n"
    /data/blyth/junotop/offline/InstallArea/python
    /data/blyth/junotop/offline/InstallArea/lib64
    /data/blyth/junotop/sniper/InstallArea/lib64
    /data/blyth/junotop/sniper/InstallArea/python
    /data/blyth/junotop/ExternalLibs/ROOT/6.24.06/lib
    N[blyth@localhost opticks]$ 





::

    SLOW: tests taking longer that 15 seconds


    FAILS:  13  / 542   :  Wed Dec 15 02:07:26 2021   
      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      8.16   

      3  /12  Test #3  : CSGTest.CSGPrimSpecTest                       Subprocess aborted***Exception:   0.10   
      4  /12  Test #4  : CSGTest.CSGPrimTest                           Subprocess aborted***Exception:   0.09   
      7  /12  Test #7  : CSGTest.CSGFoundryLoadTest                    Subprocess aborted***Exception:   0.10   
      8  /12  Test #8  : CSGTest.CSGNameTest                           Subprocess aborted***Exception:   0.09   
      9  /12  Test #9  : CSGTest.CSGTargetTest                         Subprocess aborted***Exception:   0.10   
      All these are fail to load errors. Need to update for new CFBASE approach.  NOW FIXED 

      1  /1   Test #1  : CSG_GGeoTest.CSG_GGeoTest                     Subprocess aborted***Exception:   2.57   
      Failing with assert from lack of --gparts_transform_offset option 
      
      * have moved that into argforced, but anyhow its not such a good idea to run this 
        every time tests are run ... more appropriate to run it as part of geocache-create-

      3  /16  Test #3  : QUDARapTest.QScintTest                        ***Exception: SegFault         0.09   
      4  /16  Test #4  : QUDARapTest.QCerenkovIntegralTest             ***Exception: SegFault         0.07   
      7  /16  Test #7  : QUDARapTest.QSimTest                          ***Failed                      0.04   
      8  /16  Test #8  : QUDARapTest.QBndTest                          ***Exception: SegFault         0.07   
      9  /16  Test #9  : QUDARapTest.QPropTest                         ***Exception: SegFault         0.10   
      12 /16  Test #12 : QUDARapTest.QSimWithEventTest                 ***Failed                      0.04   

      FIXED
      


    N[blyth@localhost opticks]$ 



QUDARap FAILs
-----------------

::

    Total Test time (real) =  49.12 sec

    The following tests FAILED:
          5 - QUDARapTest.QCerenkovTest (SEGFAULT)

         ** seems to be due to NP::MakeNarrow not passing along the meta , NOW FIXED

         11 - QUDARapTest.QEventTest (Child aborted)

         ** avoided fail from non existing cegs.npy 

    Errors while running CTest
    Sun Dec 12 20:16:47 GMT 2021
    epsilon:qudarap blyth$ 


After fixing the GDML duplicatedMatrix issue down to 15/542
-------------------------------------------------------------

::

    SLOW: tests taking longer that 15 seconds
      6  /17  Test #6  : QUDARapTest.QCKTest                           Passed                         249.51 

    skip this one, until have revisited to see if a quicker test can be used


    FAILS:  15  / 542   :  Mon Dec 13 03:30:06 2021   
      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      7.80        

    known python/numpy env : maybe now fixable with PYTHONPATH setup ?

    N[blyth@localhost opticks]$ which python
    /data/blyth/junotop/ExternalLibs/Python/3.8.12/bin/python
    N[blyth@localhost opticks]$ python -c "import numpy"
    N[blyth@localhost opticks]$ 

      3  /12  Test #3  : CSGTest.CSGPrimSpecTest                       Subprocess aborted***Exception:   0.12   
      4  /12  Test #4  : CSGTest.CSGPrimTest                           Subprocess aborted***Exception:   0.10   
      7  /12  Test #7  : CSGTest.CSGFoundryLoadTest                    Subprocess aborted***Exception:   0.08   
      8  /12  Test #8  : CSGTest.CSGNameTest                           Subprocess aborted***Exception:   0.08   
      9  /12  Test #9  : CSGTest.CSGTargetTest                         Subprocess aborted***Exception:   0.10   

      organizational issue : need to integrate CSGFoundry creation with geocache-create (at some level) 

      2  /3   Test #2  : GeoChainTest.GeoChainVolumeTest               Subprocess aborted***Exception:   0.29   

      FIXED : default PV name with prefix hama_ + avoid fail when no PMTSim 

      1  /17  Test #1  : QUDARapTest.QTexRotateTest                    Subprocess aborted***Exception:   0.09   

      avoid failing when no path to PNG provided

      3  /17  Test #3  : QUDARapTest.QScintTest                        ***Exception: SegFault         0.07   

      Fail due to CSGFoundry not existing, same as the above set of 5 CSG fails   

      4  /17  Test #4  : QUDARapTest.QCerenkovIntegralTest             ***Exception: SegFault         0.09   
      5  /17  Test #5  : QUDARapTest.QCerenkovTest                     Subprocess aborted***Exception:   0.34   
      8  /17  Test #8  : QUDARapTest.QSimTest                          ***Failed                      0.03   
      9  /17  Test #9  : QUDARapTest.QBndTest                          ***Exception: SegFault         0.47   
      10 /17  Test #10 : QUDARapTest.QPropTest                         ***Exception: SegFault         0.09   
      13 /17  Test #13 : QUDARapTest.QSimWithEventTest                 ***Failed                      0.04   


Five CSG Fails : all due to lack of CSGFoundry
--------------------------------------------------

* TODO: automate creation of foundry when create geocache ?  
* TODO: relocate default CSGFoundry dir within the geocache dir  
* could do this at bash level with underlying geocache-create functions

::

    epsilon:CSG blyth$ CSGPrimSpecTest
    2021-12-12 19:33:26.119 INFO  [3187540] [CSGFoundry::load@1148] /tmp/blyth/opticks/CSG_GGeo/CSGFoundry
    NP::load Failed to load from path /tmp/blyth/opticks/CSG_GGeo/CSGFoundry/solid.npy
    2021-12-12 19:33:26.121 FATAL [3187540] [CSGFoundry::loadArray@1199] FAIL to load non-optional array  /tmp/blyth/opticks/CSG_GGeo/CSGFoundry/solid.npy
    2021-12-12 19:33:26.121 FATAL [3187540] [CSGFoundry::loadArray@1200] convert geocache into CSGFoundry model using CSG_GGeo/run.sh 
    Assertion failed: (0), function loadArray, file /Users/blyth/opticks/CSG/CSGFoundry.cc, line 1202.
    Abort trap: 6

/Users/blyth/opticks/CSG_GGeo/run.sh::

    092 
     93 export CFBASE=/tmp/$USER/opticks/CSG_GGeo
     94 outdir=${CFBASE}/CSGFoundry
     95 logdir=${CFBASE}/logs
     96 
     97 mkdir -p $outdir
     98 mkdir -p $logdir
     99 
    100 


Steps to make foundry ...

1. copy over the tds3 CGDMLKludge geometry from GPU workstation
2. run geocache-create on this GDML file
3. convert the geocache into CSGFoundry model::

   cd ~/opticks/CSG_GGeo ; ./run.sh 

4. cd ~/opticks/CSG ; om- ; om-test # now the tests should pass


* NEED TO AUTOMATE THE LAST STEP AND RELOCATE THE CSGFoundry INSIDE geocache dir


::

    epsilon:issues blyth$ 
    epsilon:issues blyth$ cg
    /Users/blyth/opticks/CSG_GGeo
    epsilon:CSG_GGeo blyth$ ./run.sh 
    /usr/local/opticks/lib/CSG_GGeo
    2021-12-12 19:48:24.739 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  1
    2021-12-12 19:48:24.740 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  2
    2021-12-12 19:48:24.740 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  3
    2021-12-12 19:48:24.740 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  4
    2021-12-12 19:48:24.740 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  5
    2021-12-12 19:48:24.740 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  6
    2021-12-12 19:48:24.741 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  7
    2021-12-12 19:48:24.741 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  8
    2021-12-12 19:48:24.741 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  9
    2021-12-12 19:48:24.926 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  1000
    2021-12-12 19:48:25.136 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  2000
    2021-12-12 19:48:25.291 INFO  [3199206] [GParts::add@1314]  --gparts_transform_offset IS ENABLED, COUNT  3000
    2021-12-12 19:48:25.668 INFO  [3199206] [CSG_GGeo_Convert::CSG_GGeo_Convert@46]  reverse 0 dump_ridx (DUMP_RIDX) 8
    2021-12-12 19:48:25.669 INFO  [3199206] [CSG_GGeo_Convert::init@58] 
     foundry.meshname.size 136
    2021-12-12 19:48:25.669 INFO  [3199206] [CSG_GGeo_Convert::convertGeometry@110] convert all solids (default)
    2021-12-12 19:48:25.669 ERROR [3199206] [CSG_GGeo_Convert::convertAllSolid@122] proceeding with convert for repeatIdx 0
    2021-12-12 19:48:25.669 INFO  [3199206] [*CSG_GGeo_Convert::convertSolid@220]  repeatIdx 0 nmm 10 numPrim(GParts.getNumPrim) 3084 rlabel r0 num_inst 1 dump_ridx 8 dump 0
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   0 AABB  -60000.00  -60000.00  -60000.00   60000.00   60000.00   60000.00 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   1 AABB  -27000.00  -27000.00   21750.00   27000.00   27000.00   43350.00 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   2 AABB  -24000.00  -24000.00   21750.00   24000.00   24000.00   40350.00 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   3 AABB    -412.00    -412.00   20000.00     412.00     412.00   23500.00 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   4 AABB    -400.00    -400.00   20000.00     400.00     400.00   23500.00 
      2 CSGNode     7 !cy aabb:  -402.0  -402.0 19982.5   402.0   402.0 23517.5  trIdx:     7 atm     4 IsOnlyIntersectionMask 1 is_complemented_leaf 1 bbskip 1
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   5 AABB    -407.00    -407.00   20000.00     407.00     407.00   23500.00 
      2 CSGNode    10 !cy aabb:  -400.0  -400.0 19982.5   400.0   400.0 23517.5  trIdx:     9 atm     4 IsOnlyIntersectionMask 1 is_complemented_leaf 1 bbskip 1
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   6 AABB    -402.00    -402.00   20000.00     402.00     402.00   23500.00 
      2 CSGNode    13 !cy aabb:  -500.0  -500.0 21752.0   500.0   500.0 25752.0  trIdx:    11 atm     4 IsOnlyIntersectionMask 1 is_complemented_leaf 1 bbskip 1
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   7 AABB  -24000.00  -24000.00   21752.00   24000.00   24000.00   30152.00 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   8 AABB   16703.00  -10141.80   23483.20   23564.20   -3280.60   23510.80 
    CSG_GGeo_Convert::convertPrim  ridx  0 primIdx   9 AABB   16703.00  -10096.35   23483.20   23564.20   -3326.05   23496.50 

    ...




With proper Geant4+other environment from jre : at 20/542
--------------------------------------------------------------

NB : Attempting to run without jre fails many tests for lack of Geant4 environment

::

    SLOW: tests taking longer that 15 seconds
      6  /17  Test #6  : QUDARapTest.QCKTest                           Passed                         250.11 


    FAILS:  20  / 542   :  Sun Dec 12 03:08:55 2021   

      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      8.05   

      * known python/numpy issue 

      38 /39  Test #38 : ExtG4Test.X4IntersectSolidTest                Subprocess aborted***Exception:   0.32   

      * FIXED : was bad default that depends on j/PMTSim

    . 3  /45  Test #3  : CFG4Test.CTestDetectorTest                    Subprocess aborted***Exception:   4.90   
      5  /45  Test #5  : CFG4Test.CGDMLDetectorTest                    Subprocess aborted***Exception:   4.91   
      7  /45  Test #7  : CFG4Test.CGeometryTest                        Subprocess aborted***Exception:   5.01   
      27 /45  Test #27 : CFG4Test.CInterpolationTest                   Subprocess aborted***Exception:   4.98   

      * G4 REPEATED matrix BUG ? MAYBE FIXED BY CGDMLKludge::pruneRepeatedMatrix 

      3  /12  Test #3  : CSGTest.CSGPrimSpecTest                       Subprocess aborted***Exception:   0.08   
      4  /12  Test #4  : CSGTest.CSGPrimTest                           Subprocess aborted***Exception:   0.09   
      7  /12  Test #7  : CSGTest.CSGFoundryLoadTest                    Subprocess aborted***Exception:   0.09   
      8  /12  Test #8  : CSGTest.CSGNameTest                           Subprocess aborted***Exception:   0.08   
      9  /12  Test #9  : CSGTest.CSGTargetTest                         Subprocess aborted***Exception:   0.09   



      2  /3   Test #2  : GeoChainTest.GeoChainVolumeTest               Subprocess aborted***Exception:   0.29   



      1  /17  Test #1  : QUDARapTest.QTexRotateTest                    Subprocess aborted***Exception:   0.09   
      3  /17  Test #3  : QUDARapTest.QScintTest                        ***Exception: SegFault         0.07   
      4  /17  Test #4  : QUDARapTest.QCerenkovIntegralTest             ***Exception: SegFault         0.08   
      5  /17  Test #5  : QUDARapTest.QCerenkovTest                     Subprocess aborted***Exception:   0.33   
      8  /17  Test #8  : QUDARapTest.QSimTest                          ***Failed                      0.03   
      9  /17  Test #9  : QUDARapTest.QBndTest                          ***Exception: SegFault         0.15   
      10 /17  Test #10 : QUDARapTest.QPropTest                         ***Exception: SegFault         0.09   
      13 /17  Test #13 : QUDARapTest.QSimWithEventTest                 ***Failed                      0.04   

    N[blyth@localhost opticks]$ 



Seems all GDML reading tests are failing : Hopeful of fix via CGDMLKludgeRead::pruneDuplicatedMatrix
--------------------------------------------------------------------------------------------------------

* :doc:`geant4-gdml-repeated-reflectivity-define-matrix-error-dec2021`



OptiXRapTest.interpolationTest familiar fail from lack of python setup
------------------------------------------------------------------------

* now that offline python has numpy can maybe fix this for offline+opticks 

::

    Start 25: OptiXRapTest.interpolationTest
    25/35 Test #25: OptiXRapTest.interpolationTest ..............................***Failed    7.59 sec
    2021-12-12 00:49:29.638 INFO  [96403] [OpticksHub::loadGeometry@283] [ /home/blyth/.opticks/geocache/DetSim0Svc_pWorld_g4live/g4ok_gltf/3dbec4dc3bdef47884fe48af781a179d/1
    2021-12-12 00:49:30.452 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 
    2021-12-12 00:49:30.453 INFO  [96403] [GParts::add@1314]  NOT ENABLED --gparts_transform_offset 

    // GETTING MANY THOUSANDS OF THIS "NOT ENABLED" 

    ...
    ...

    2021-12-12 00:49:35.109 INFO  [96403] [interpolationTest::init@115]  name interpolationTest_interpol.npy base $TMP/optixrap/interpolationTest script interpolationTest_interpol.py nb    42 nx   761 ny   336 progname              interpolationTest
    2021-12-12 00:49:35.109 INFO  [96403] [OLaunchTest::init@69] OLaunchTest entry   0 width       1 height       1 ptx                               interpolationTest.cu prog                                  interpolationTest
    2021-12-12 00:49:35.109 INFO  [96403] [OLaunchTest::launch@80] OLaunchTest entry   0 width     761 height      42 ptx                               interpolationTest.cu prog                                  interpolationTest
    2021-12-12 00:49:36.157 INFO  [96403] [interpolationTest::launch@158] OLaunchTest entry   0 width     761 height      42 ptx                               interpolationTest.cu prog                                  interpolationTest
    2021-12-12 00:49:36.161 INFO  [96403] [interpolationTest::launch@165]  save  base $TMP/optixrap/interpolationTest name interpolationTest_interpol.npy
    2021-12-12 00:49:36.277 INFO  [96403] [SSys::RunPythonScript@648]  script interpolationTest_interpol.py script_path /data/blyth/junotop/ExternalLibs/opticks/head/bin/interpolationTest_interpol.py python_executable /usr/bin/python
    Traceback (most recent call last):
      File "/data/blyth/junotop/ExternalLibs/opticks/head/bin/interpolationTest_interpol.py", line 23, in <module>
        from opticks.ana.proplib import PropLib
    ImportError: No module named opticks.ana.proplib
    2021-12-12 00:49:36.682 INFO  [96403] [SSys::run@100] /usr/bin/python /data/blyth/junotop/ExternalLibs/opticks/head/bin/interpolationTest_interpol.py  rc_raw : 256 rc : 1
    2021-12-12 00:49:36.683 ERROR [96403] [SSys::run@107] FAILED with  cmd /usr/bin/python /data/blyth/junotop/ExternalLibs/opticks/head/bin/interpolationTest_interpol.py  RC 1
    2021-12-12 00:49:36.683 INFO  [96403] [SSys::RunPythonScript@655]  RC 1
    2021-12-12 00:49:36.683 ERROR [96403] [SSys::RunPythonScript@656] 

    SSys::RunPythonScript_NOTES 
    ------------------------------

    Common causes of error when running python scripts via SSys::RunPythonScript are:

    1. using a python which does not have the *numpy* module
    2. not configuring PYTHONPATH such that the *opticks* modules can be found 
    3. not configuring PATH to allow SSys::Which to find the python scripts 

    Example settings of envvars to configure within .bash_profile or .bashrc which 
    control the python that opticks C++ will use with SSys::RunPythonScript are::

       export OPTICKS_PYTHON=/Users/blyth/miniconda3/bin/python
       export PYTHONPATH=$PYTHONPATH:$(opticks-fold)
       export PATH=$PATH:$(opticks-home)/bin

    Note that opticks-fold is the directory above opticks-home "/home/blyth/opticks" 
    so that will often be the HOME directory, eg /home/blyth



X4GeometryMakerTest ... hmm that was renamed X4SolidMakerTest 
---------------------------------------------------------------

::

    Test project /data/blyth/junotop/ExternalLibs/opticks/head/build/extg4
          Start  1: ExtG4Test.X4GeometryMakerTest
     1/39 Test  #1: ExtG4Test.X4GeometryMakerTest ...........................Child aborted***Exception:   0.35 sec
    X4GeometryMakerTest: /home/blyth/opticks/extg4/tests/X4GeometryMakerTest.cc:7: void test_CanMake(): Assertion `default_ == true' failed.

          Start  2: ExtG4Test.X4Test
     2/39 Test  #2: ExtG4Test.X4Test ........................................   Passed    0.22 sec
          Start  3: ExtG4Test.X4EntityTest


