G4CXTest_find_the_leak
==========================

* cxs_min.sh profile is flat as a pancake : the issue is with B(U4Recorder collected SEvt), not the A(QSim/QEvent collected SEvt)

10M HitAndPhoton VERSION=3  : WANT TO SEE THE LEAK IN SINGLE EVENT

::

   ~/opticks/g4cx/tests/G4CXTest_GEOM.sh

   JOB=N5 ~/opticks/sysrap/tests/sreport.sh grab 
   JOB=N5 subprofile=1 ~/opticks/sysrap/tests/sreport.sh ana

::

    In [3]: fold.subprofile.a.subprofile_labels
    Out[3]: array(['SEvt__beginOfEvent_0', 'SEvt__beginOfEvent_1', 'SEvt__endOfEvent_0'], dtype='<U20')

    In [4]: fold.subprofile.b.subprofile_labels
    Out[4]: array(['SEvt__beginOfEvent_0', 'SEvt__beginOfEvent_1', 'SEvt__endOfEvent_0'], dtype='<U20')

    In [5]: fold.subprofile.a.subprofile
    Out[5]:
    array([[[1701401289858109,         22088588,         10917884],
            [1701401289858240,         22088588,         10917884],
            [1701401293565758,         29035404,         10920200]]])

    In [6]: fold.subprofile.b.subprofile
    Out[6]:
    array([[[1701400621605083,         15213364,          4200540],
            [1701400621605263,         15213364,          4200540],
            [1701401285431216,         21776084,         10605356]]])



Use a smallish 10 evt run :  OPTICKS_NUM_PHOTON=H1:10  large enough to see leak, but not taking too long
----------------------------------------------------------------------------------------------------------

::

    ~/opticks/g4cx/tests/G4CXTest_GEOM.sh    

    JOB=N5 runprof=1 ~/opticks/sysrap/tests/sreport.sh ana
    runprof=1 VM=1 ~/opticks/sysrap/tests/sreport.sh ana

    ## runprof range : 400s VM 8.3G RS 1.3G    

Before:

1. seed deletion in SGenerate::GeneratePhotons
2. photon deletion in G4CXApp::GeneratePrimaries

::

    In [2]: fold.runprof[-1] - fold.runprof[0]
    Out[2]: array([399599564,   8300040,   1353644])

    In [3]: ( fold.runprof[-1] - fold.runprof[0] )/1e6
    Out[3]: array([399.6  ,   8.3  ,   1.354])

After::

    In [1]: ( fold.runprof[-1] - fold.runprof[0] )/1e6
    Out[1]: array([369.851,   7.935,   0.988])

More::

    In [1]: ( fold.runprof[-1] - fold.runprof[0] )/1e6
    Out[1]: array([397.11 ,   7.76 ,   0.814])

    In [1]: ( fold.runprof[-1] - fold.runprof[0] )/1e6
    Out[1]: array([385.735,   7.76 ,   0.814])



* RSS going in right direction

* Between the end of ECPU and begin of EGPU are recovering only smth like 
  a third of the memory increase across ECPU 

* HMM: need monitoring of the vec sizes ? 



Check profile jump with 10M and 100M photons in SEvtTest::hostside_running_resize_
-------------------------------------------------------------------------------------

Resize the vectors for 10M photons (default components) takes 0.542 s and 840MB in both VM and RSS::

    2023-12-01 13:44:02.941 INFO  [18179626] [SEvt::hostside_running_resize_@2190]  photon.size 0 photon.size/M 0 =>  evt.num_photon 10000000 evt.num_photon/M 10
    1701409442941953,4377075,2220
    1701409443484140,5217087,842399
    542187,840012,840179

For 100M photons takes 6.2 s and 8.4/5.5 GB  VM/RSS::

    2023-12-01 13:47:21.845 INFO  [18184651] [SEvt::hostside_running_resize_@2190]  photon.size 0 photon.size/M 0 =>  evt.num_photon 100000000 evt.num_photon/M 100
    1701409641845097,4386512,2236
    1701409648092925,12795961,5580337
    6247828,8409449,5578101


Investigate in sysrap/tests/SEvtTest.sh 
------------------------------------------

* adding shrink_to_fit in SEvt::clear_vectors seems effective in the simple SEvtTest.sh 
  but not so far in G4CXTest 

* HMM: check clear/clear_vectors being called where expected 



