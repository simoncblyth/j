ok-tds-release-running-shakedown
==================================

::

    N
    jre
    ok-tds   



Issue 1 : improve spath.h handling of DefaultOutputDir, switch to OPTICKS_SCRIPT 
----------------------------------------------------------------------------------

::

    N[blyth@localhost junosw]$ l /tmp/blyth/opticks/GEOM/python3.9/ALLVERSION/p001/
    total 125096
        4 -rw-rw-r--. 1 blyth blyth      143 Nov 13 15:55 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Nov 13 15:55 sframe.npy
        4 -rw-rw-r--. 1 blyth blyth      856 Nov 13 15:55 NPFold_meta.txt
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 13 15:55 inphoton.npy
        4 -rw-rw-r--. 1 blyth blyth       57 Nov 13 15:55 domain_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      256 Nov 13 15:55 domain.npy
       60 -rw-rw-r--. 1 blyth blyth    59328 Nov 13 15:55 hit.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 13 15:55 photon.npy
        4 -rw-rw-r--. 1 blyth blyth      224 Nov 13 15:55 genstep.npy
        4 -rw-rw-r--. 1 blyth blyth       55 Nov 13 15:55 NPFold_index.txt
        0 drwxr-xr-x. 4 blyth blyth       65 Nov 13 10:32 ..


HMM: should GEOM be automated from junosw prespective ? 

* thats not possible until after no longer need envvar kludges 
  although can manually use the release name within the GEOM

::

    N[blyth@localhost opticks]$ l /data/blyth/opticks/GEOM/UNRESOLVED_TOKEN_GEOM/ok-tds/ALLVERSION/n001/
    total 180092
        0 drwxr-xr-x. 2 blyth blyth      252 Nov 14 15:23 .
        4 -rw-rw-r--. 1 blyth blyth      144 Nov 14 15:23 gs.npy
        4 -rw-rw-r--. 1 blyth blyth      143 Nov 14 15:23 sframe_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      384 Nov 14 15:23 sframe.npy
    15628 -rw-rw-r--. 1 blyth blyth 16000128 Nov 14 15:23 pho.npy
    15628 -rw-rw-r--. 1 blyth blyth 16000128 Nov 14 15:23 pho0.npy
        4 -rw-rw-r--. 1 blyth blyth      639 Nov 14 15:23 NPFold_meta.txt
        4 -rw-rw-r--. 1 blyth blyth       57 Nov 14 15:23 domain_meta.txt
        4 -rw-rw-r--. 1 blyth blyth      256 Nov 14 15:23 domain.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 14 15:23 inphoton.npy
    23796 -rw-rw-r--. 1 blyth blyth 24366464 Nov 14 15:23 hit.npy
    62504 -rw-rw-r--. 1 blyth blyth 64000128 Nov 14 15:23 photon.npy
        0 drwxr-xr-x. 4 blyth blyth       30 Nov 14 15:23 ..
        4 -rw-rw-r--. 1 blyth blyth      224 Nov 14 15:23 genstep.npy
        4 -rw-rw-r--. 1 blyth blyth       55 Nov 14 15:23 NPFold_index.txt
    N[blyth@localhost opticks]$ 


With spath.h need to explicitly create the output dirs
---------------------------------------------------------

::

    2023-11-14 15:41:23.394 INFO  [61679] [G4CXOpticks::saveGeometry@536] [ /home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0
    G4CXOpticks::saveGeometry [ /home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0
    2023-11-14 15:41:23.403 INFO  [61679] [U4GDML::write@187]  ekey U4GDML_GDXML_FIX_DISABLE U4GDML_GDXML_FIX_DISABLE 0 U4GDML_GDXML_FIX 1
    G4GDML: Writing '/home/blyth/.opticks/GEOM/J23.1.0-rc3-ok0/origin_raw.gdml'...
    G4GDML: Writing definitions...
    G4GDML: Writing materials...
    G4GDML: Writing solids...
    G4GDML: Writing structure...
    G4GDML: Writing setup...
    G4GDML: Writing surfaces...
    Traceback (most recent call last):
      File "/home/blyth/junotop/junosw/Examples/Tutorial/share/tut_detsim.py", line 21, in <module>
        juno_application.run()
      File "/data/blyth/junotop/junosw/InstallArea/python/Tutorial/JUNOApplication.py", line 184, in run
        self.toptask.run()
    RuntimeError: unidentifiable C++ exception



Shared QCurandStates : generalized spath.h in spath::_ResolvePathGeneralized 
-------------------------------------------------------------------------------

Making it sensitive to envvar allows config of a shared location, eg on /cvmfs/opticks.ihep.ac.cn::

    ${OPTICKS_RNGDir:-$HOME/.opticks/rngcache/RNG}


Shared InputPhotons ?
------------------------


::

    epsilon:opticks blyth$ opticks-f /InputPhotons
    ./ana/input_photons.sh:into the directory ~/.opticks/InputPhotons::
    ./ana/input_photons.sh:ls -alst ~/.opticks/InputPhotons
    ./ana/input_photons.py:    DEFAULT_BASE = os.path.expanduser("~/.opticks/InputPhotons")
    ./bin/OPTICKS_INPUT_PHOTON_.sh:        abspath=$HOME/.opticks/InputPhotons/$path
    ./sysrap/tests/storch_test.sh:odir=$HOME/.opticks/InputPhotons/storch
    ./sysrap/tests/stranTest.cc:     const char* path = SPath::Resolve("$HOME/.opticks/InputPhotons" , name, NOOP ); 
    ./sysrap/SEvt.cc:const char* SEvt::INPUT_PHOTON_DIR = ssys::getenvvar("SEvt__INPUT_PHOTON_DIR", "$HOME/.opticks/InputPhotons") ; 
    ./sysrap/SEvt.cc:   of $HOME/.opticks/InputPhotons. 


    ./g4ok/tests/G4OKTest.sh:path=$HOME/.opticks/InputPhotons/$name.npy
    ./npy/tests/NPY7Test.cc:   NPY<float>* ip = NPY<float>::load("$HOME/.opticks/InputPhotons/InwardsCubeCorners1.npy"); 
    epsilon:opticks blyth$ 


WIP : ok-tds config debug SEvt and compare them 
--------------------------------------------------

HMM: cannot use /tmp on N as far too tight::

    epsilon:GEOM blyth$ du -hs J23_1_0_rc3_ok0
    5.1G	J23_1_0_rc3_ok0


Spaced out history issue::

    QCF qcf :  
    a.q 1000000 b.q 1000000 lim slice(None, None, None) 
    c2sum : 1772472.8750 c2n :  2113.0000 c2per:   838.8419  C2CUT:   30 
    c2sum/c2n:c2per(C2CUT)  1772472.88/2113:838.842 (30) pv[0.00,< 0.05 : NOT:null-hyp ] 

    np.c_[siq,_quo,siq,sabo2,sc2,sabo1][0:40]  ## A-B history frequency chi2 comparison 
    [[' 0' 'TO BT BT BT BT SD                                                                              ' ' 0' '     0 331327' '331327.0000' '    -1      1']
     [' 1' 'TO BT BT BT BT SA                                                                              ' ' 1' '     0 281937' '281937.0000' '    -1      2']
     [' 2' 'TO BT BT BT BT    SA                                                                           ' ' 2' '187448      0' '187448.0000' '     4     -1']
     [' 3' 'TO BT BT BT BT    SR SA                                                                        ' ' 3' ' 75719      0' '75719.0000' '    20     -1']
     [' 4' 'TO BT BT BT BT BT SR SA                                                                        ' ' 4' '     0  62886' '62886.0000' '    -1 103703']
     [' 5' 'TO BT BT BT BT    SR    BT BT BT BT BT BT AB                                                   ' ' 5' ' 62442      0' '62442.0000' '120824     -1']
     [' 6' 'TO BT BT BT BT BT SA                                                                           ' ' 6' '     0  46679' '46679.0039' '    -1  84186']
     [' 7' 'TO BT BT BT BT    SR    BT BT BT BT AB                                                         ' ' 7' ' 22410      0' '22410.0000' '121428     -1']
     [' 8' 'TO BT BT BT BT    SR    BT BT BT BT BT BT SC AB                                                ' ' 8' ' 19747      0' '19747.0000' '139242     -1']
     [' 9' 'TO BT BT BT BT    SR SR SA                                                                     ' ' 9' ' 15680      0' '15680.0000' '     6     -1']
     ['10' 'TO BT BT BT BT BT SR BR SR SA                                                                  ' '10' '     0  11901' '11901.0010' '    -1 209894']



TODO : setup source build environment on L : check ok-tds on GPU cluster
----------------------------------------------------------------------------





