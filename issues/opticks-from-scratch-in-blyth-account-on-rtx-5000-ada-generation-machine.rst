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


Issue 2 : missing numpy : handle more cleanly
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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



