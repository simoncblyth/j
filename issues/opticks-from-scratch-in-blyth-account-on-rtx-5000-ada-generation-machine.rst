opticks-from-scratch-in-blyth-account-on-rtx-5000-ada-generation-machine
==========================================================================


machine config
---------------

* useradd blyth
* add blyth to /etc/sudoers
* ~/.vimrc
* ~/.gitconfig
* network setup for IP

ssh hookup
-----------

* ssh-keygen -t rsa -C ada.blyth.rsa
* scp id_rsa.pub to laptop and upload to github and bitbucket from there 
* ~/.ssh/config setup passwordless access to bastion BB 
* add ssh "alias" A for Ada to other machines 


configure soks proxy 
---------------------

::

    soks-do(){ ssh -C -ND localhost:8080 BB ; } 
    soks()
    {
       type $FUNCNAME
       type ${FUNCNAME}-do

       local count=0
       while [ $count -lt 1000 ]; do 
           echo $FUNCNAME $count $(date)
           count=$(( count + 1 ))
           ${FUNCNAME}-do
       done
    }


* arrange for bitbucket + github ssh to use the proxy by extracts from ~/.ssh/config 


ssh clone repos from github and bitbucket
-------------------------------------------

Previous step is needed to avoid cloning being horribly slow or blocked. 

* j 
* env
* opticks 


cvmfs
------

* follow cvmfs readthedocs installation guidelines using yum to install


copy fresh build config from user simon on Gold
------------------------------------------------------

::

    ~/.opticks_externals_config  ## update for arch el9_amd64_gcc11
    ~/.opticks_build_config      ## try /usr/local/cuda-12.4 

    ~/fresh_build.sh  


~/.opticks_externals_config 
-------------------------------


::

    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Boost/1.82.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Xercesc/3.2.4/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/CLHEP/2.4.7.1/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Geant4/10.04.p02.juno/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/custom4/0.1.8/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/Python/3.9.19/bashrc
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Pre-Release/J24.1.x/ExternalLibs/python-numpy/1.23.5/bashrc




shakedown build
--------------------

* build worked first time


shakedown install 
----------------------

FIXED : Issue 1 : QRng::Save error opening file : due to missing RNG directory
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Issue::

    2024-08-29 16:27:14.875 INFO  [34355] [QCurandState::download@64] after copy_device_to_host  
    2024-08-29 16:27:14.875 FATAL [34355] [QRng::Save@124]  error opening file /home/blyth/.opticks/rngcache/RNG/QCurandState_1000000_0_0.bin
    QCurandStateTest: /home/blyth/opticks/qudarap/QRng.cc:125: static void QRng::Save(curandState*, unsigned int, const char*): Assertion `fp' failed.
    /home/blyth/opticks/qudarap/qudarap.bash: line 34: 34355 Aborted                 (core dumped) QCurandState_SPEC=$size:0:0 ${OPTICKS_PREFIX}/lib/QCurandStateTest

Reproduce with::

    [blyth@localhost InputPhotons]$ t qudarap-prepare-installation
    qudarap-prepare-installation () 
    { 
        local sizes=$(qudarap-prepare-sizes);
        local size;
        for size in $sizes;
        do
            QCurandState_SPEC=$size:0:0 ${OPTICKS_PREFIX}/lib/QCurandStateTest;
            rc=$?;
            [ $rc -ne 0 ] && return $rc;
        done;
        return 0
    }
    [blyth@localhost InputPhotons]$ 


Fixed with Opticks change using sdirectory.h in QRng.cc


FIXED Issue 2 : missing numpy : handle more cleanly
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* added numpy check to script
* TODO: document the environment 



::

    blyth@localhost ~]$ opticks-prepare-InputPhotons
    === opticks-prepare-InputPhotons : used by some tests
                               DIR : /home/blyth/opticks/ana 
                            script : /home/blyth/opticks/ana/input_photons.py 
                            defarg : info_run_ls 
                               arg : info_run_ls 
                            dtypes : np.float32 np.float64 
    Traceback (most recent call last):
      File "/home/blyth/opticks/ana/input_photons.py", line 11, in <module>
        import numpy as np
    ModuleNotFoundError: No module named 'numpy'
    /home/blyth/opticks/ana/input_photons.sh run error
    [blyth@localhost ~]$ 



Issue 3 : using /cvmfs geometry kinda works but analytic optix render for some shapes looks broken
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* using exact same geometry in earlier CUDA works OK 

* TODO: solid by solid geometry testing 


Issue 4 : test fails
~~~~~~~~~~~~~~~~~~~~~~

Avoid changing the runners to look in /cvmfs by using a symbolic link::

    cd ~/.opticks/GEOM
    ln -s /cvmfs/opticks.ihep.ac.cn/.opticks/GEOM/J_2024aug27 


::

    FAILS:  5   / 213   :  Thu Aug 29 22:11:33 2024   
      94 /107 Test #94 : SysRapTest.ssys_test                          Subprocess aborted***Exception:   0.05   
      10 /20  Test #10 : QUDARapTest.QEventTest                        ***Failed                      0.17   
      11 /20  Test #11 : QUDARapTest.QEvent_Lifecycle_Test             ***Failed                      0.13   
      13 /20  Test #13 : QUDARapTest.QSimWithEventTest                 ***Failed                      2.12   
      11 /30  Test #11 : U4Test.U4RandomTest                           ***Failed                      0.03   



FIXED ssys_test impl error when no envvar defined::

    94/107 Test  #94: SysRapTest.ssys_test .....................................Subprocess aborted***Exception:   0.05 sec
    terminate called after throwing an instance of 'std::logic_error'
      what():  basic_string::_M_construct null not valid


QUDARap 3 thrust related fails::

    0/20 Test #10: QUDARapTest.QEventTest ..............***Failed    0.17 sec
                    HOME : /home/blyth
                     PWD : /data1/blyth/local/opticks_Debug/build/qudarap/tests
                    GEOM : J_2024aug27
             BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/QTestRunner.sh
              EXECUTABLE : QEventTest
                    ARGS : 
    QEventTest::setGenstep_one
    terminate called after throwing an instance of 'thrust::THRUST_200302_700_NS::system::system_error'
      what():  after reduction step 1: cudaErrorNoKernelImageForDevice: no kernel image is available for execution on the device
    /data1/blyth/local/opticks_Debug/bin/QTestRunner.sh: line 23: 59189 Aborted                 (core dumped) $EXECUTABLE $@
    /data1/blyth/local/opticks_Debug/bin/QTestRunner.sh : FAIL from QEventTest


* TODO : try different COMPUTE_CAPABILITY


U4RandomTest failing from missing precooked::

          Start 11: U4Test.U4RandomTest
    11/30 Test #11: U4Test.U4RandomTest ...........................***Failed    0.03 sec
                    HOME : /home/blyth
                     PWD : /data1/blyth/local/opticks_Debug/build/u4/tests
                    GEOM : J_2024aug27
             BASH_SOURCE : /data1/blyth/local/opticks_Debug/bin/U4TestRunner.sh
              EXECUTABLE : U4RandomTest
                    ARGS : 
    NP::load Failed to load from path /home/blyth/.opticks/precooked/QSimTest/rng_sequence/rng_sequence_f_ni1000000_nj16_nk16_tranche100000/rng_sequence_f_ni100000_nj16_nk16_ioffset000000.npy
    /data1/blyth/local/opticks_Debug/bin/U4TestRunner.sh : FAIL from U4RandomTest



