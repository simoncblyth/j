offline-opticks-test-fails
-----------------------------


Attempting to run without jre fails many tests for lack of Geant4 environment::


    SLOW: tests taking longer that 15 seconds
      6  /17  Test #6  : QUDARapTest.QCKTest                           Passed                         249.42 


    FAILS:  24  / 541   :  Sun Dec 12 00:56:45 2021   
      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      7.59   
      1  /39  Test #1  : ExtG4Test.X4GeometryMakerTest                 Child aborted***Exception:     0.35   
      12 /39  Test #12 : ExtG4Test.X4MaterialWaterTest                 Child aborted***Exception:     0.29   
      14 /39  Test #14 : ExtG4Test.X4PhysicalVolumeTest                Child aborted***Exception:     0.32   
      38 /39  Test #38 : ExtG4Test.X4IntersectSolidTest                Child aborted***Exception:     0.29   
      3  /45  Test #3  : CFG4Test.CTestDetectorTest                    ***Exception: SegFault         2.92   
      5  /45  Test #5  : CFG4Test.CGDMLDetectorTest                    Child aborted***Exception:     4.86   
      7  /45  Test #7  : CFG4Test.CGeometryTest                        Child aborted***Exception:     4.95   
      27 /45  Test #27 : CFG4Test.CInterpolationTest                   ***Exception: SegFault         2.88   
      44 /45  Test #44 : CFG4Test.WaterTest                            Child aborted***Exception:     0.39   
      3  /12  Test #3  : CSGTest.CSGPrimSpecTest                       Child aborted***Exception:     0.11   
      4  /12  Test #4  : CSGTest.CSGPrimTest                           Child aborted***Exception:     0.08   
      7  /12  Test #7  : CSGTest.CSGFoundryLoadTest                    Child aborted***Exception:     0.08   
      8  /12  Test #8  : CSGTest.CSGNameTest                           Child aborted***Exception:     0.08   
      9  /12  Test #9  : CSGTest.CSGTargetTest                         Child aborted***Exception:     0.07   
      2  /2   Test #2  : GeoChainTest.GeoChainVolumeTest               Child aborted***Exception:     0.28   
      1  /17  Test #1  : QUDARapTest.QTexRotateTest                    Child aborted***Exception:     0.08   
      3  /17  Test #3  : QUDARapTest.QScintTest                        ***Exception: SegFault         0.07   
      4  /17  Test #4  : QUDARapTest.QCerenkovIntegralTest             ***Exception: SegFault         0.08   
      5  /17  Test #5  : QUDARapTest.QCerenkovTest                     Child aborted***Exception:     0.33   
      8  /17  Test #8  : QUDARapTest.QSimTest                          ***Failed                      0.03   
      9  /17  Test #9  : QUDARapTest.QBndTest                          ***Exception: SegFault         0.08   
      10 /17  Test #10 : QUDARapTest.QPropTest                         ***Exception: SegFault         0.08   
      13 /17  Test #13 : QUDARapTest.QSimWithEventTest                 ***Failed                      0.04   
    N[blyth@localhost ~]$ 



With proper Geant4 environment
--------------------------------

::

    SLOW: tests taking longer that 15 seconds
      6  /17  Test #6  : QUDARapTest.QCKTest                           Passed                         250.11 


    FAILS:  20  / 542   :  Sun Dec 12 03:08:55 2021   
      25 /35  Test #25 : OptiXRapTest.interpolationTest                ***Failed                      8.05   

      * known python/numpy issue 

      38 /39  Test #38 : ExtG4Test.X4IntersectSolidTest                Subprocess aborted***Exception:   0.32   
      * FIXED : was bad default that depends on j/PMTSim
   

      3  /45  Test #3  : CFG4Test.CTestDetectorTest                    Subprocess aborted***Exception:   4.90   
      5  /45  Test #5  : CFG4Test.CGDMLDetectorTest                    Subprocess aborted***Exception:   4.91   
      7  /45  Test #7  : CFG4Test.CGeometryTest                        Subprocess aborted***Exception:   5.01   
      27 /45  Test #27 : CFG4Test.CInterpolationTest                   Subprocess aborted***Exception:   4.98   

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


