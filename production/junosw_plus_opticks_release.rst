junosw_plus_opticks_release
=============================

Overview
----------

Redo the below builds and get familiar with the environment setup, 
while considering how best to make a junosw+opticks release

The offline and opticks are from source. Here need to consider
how to turn those into a binary release. 

After offline + opticks from source is working can try building 
offline against the opticks binary release. The difference 
is there is no need for "bash junoenv opticks" anymore (which git clones
and builds and hooksup) 
all that will be needed will be to source the installed opticks bashrc.   

And that will appear as a line of the JUNOTOP/bashrc.sh in the 
release directory on /cvmfs 

Need to define a name for the junosw+opticks release, perhaps::

    J23.1.0-rc3-Opticks-v0.2.1 

Potential issues. Need to ensure the opticks binary build uses the same
versions of Geant4, Custom4, Boost, Xercesc that the offline does.


Start by reviewing the setup on N (workstation) and then bring that over to L(cluster)
----------------------------------------------------------------------------------------

* actually ended up doing L first and then N : as simpler to start from scratch 

1. pure junosw build
2. junosw+opticks build with opticks using updated versions NVIDIA OptiX 7.5 + CUDA 11.7 


pure junosw build on N 
~~~~~~~~~~~~~~~~~~~~~~~~~

::

    N
    jre

    jt
    vi bashrc.sh   # comment the opticks hookup line 

    jo
    rm -rf build
    ./build_Debug.sh 


* HMM: tis building against Custom4 0.1.9 (unreleased) when should be 0.1.8 
  because I omitted to switch the Custom4 line down to 0.1.8 
  (actually there is no significant different between those anyhow)

* this worked but its mixing envs somewhat 


pure junosw build on L
~~~~~~~~~~~~~~~~~~~~~~~~

* review : https://juno.ihep.ac.cn/mediawiki/index.php/Offline:Installation

Starting from scratch::

    L7[blyth@lxslc714 ~]$ g
    L7[blyth@lxslc714 ~]$ pwd
    /hpcfs/juno/junogpu/blyth

    L7[blyth@lxslc714 ~]$ rm -rf junotop  ## wow the cluster is slow 


Hmm cannot do preq that needs root, so just assume. 

HMM :GG  dont want to build all the externals, so get them from a release.

* https://code.ihep.ac.cn/JUNO/offline/junosw/-/releases/J23.1.0-rc3

::

   /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/

::

   cd $JUNOTOP
   ln -s /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3
   ln -s J23.1.0-rc3/bashrc.sh basis_bashrc.sh 
   cp basis_bashrc.sh bashrc.sh 

    L7[blyth@lxslc705 junotop]$ head -10 bashrc.sh 
    #export JUNOTOP=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3
    # cannot just use the original as need to customize JUNOTOP and 
    # add the opticks line down below
    export JUNOTOP=$(dirname $BASH_SOURCE)

    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/binutils/2.36/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/go/1.20.6/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/junoenv/etc/bashrc
    source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/ExternalLibs/Git/2.37.3/bashrc
    L7[blyth@lxslc705 junotop]$ 

::

    L7[blyth@lxslc705 junotop]$ source $JUNOTOP/bashrc.sh 
    -bash: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/ROOT/6.26.06/bin/thisroot.sh: No such file or directory
    -bash: /hpcfs/juno/junogpu/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno/bin/geant4.sh: No such file or directory


Avoid this by unset JUNOTOP at head and set it at tail::

     05 unset JUNOTOP
      6 
      7 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/binutils/2.36/bashrc
      8 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/gcc/11.2.0/bashrc
      9 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/contrib/go/1.20.6/bashrc
      ..
     44 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/ExternalLibs/libmore/0.8.3/bashrc
     45 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/ExternalLibs/libonnxruntime/1.11.1/bashrc
     46 
     47 export JUNOTOP=$(cd $(dirname $BASH_SOURCE) && pwd)
     48 

 
Get junoenv (its from git not svn)::

    L7[blyth@lxslc714 junotop]$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git

::

    cd $JUNOTOP/junoenv


Arghh GFW blocks access to github, so use symbolic links across to the release::

    bash junoenv sniper

    L7[blyth@lxslc705 junotop]$ l
    total 24
    4 drwxr-xr-x  3 blyth dyw     4096 Nov 11 17:18 .
    0 -rw-r--r--  1 blyth dyw        0 Nov 11 17:18 sniper-v2.2.3.tar.gz
    4 drwxr-xr-x 21 blyth junogpu 4096 Nov 11 17:17 ..

    L7[blyth@lxslc705 junotop]$ pwd
    /hpcfs/juno/junogpu/blyth/junotop
    L7[blyth@lxslc705 junotop]$ l
    total 24
    4 drwxr-xr-x  3 blyth dyw     4096 Nov 11 17:24 .
    0 lrwxrwxrwx  1 blyth dyw       21 Nov 11 17:24 basis_bashrc.sh -> J23.1.0-rc3/bashrc.sh
    0 lrwxrwxrwx  1 blyth dyw       32 Nov 11 17:23 sniper-v0.9.1.tar.gz -> J23.1.0-rc3/sniper-v0.9.1.tar.gz
    0 lrwxrwxrwx  1 blyth dyw       32 Nov 11 17:23 sniper-v2.2.3.tar.gz -> J23.1.0-rc3/sniper-v2.2.3.tar.gz
    4 lrwxrwxrwx  1 blyth dyw       68 Nov 11 17:22 J23.1.0-rc3 -> /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3
    4 drwxr-xr-x 21 blyth junogpu 4096 Nov 11 17:17 ..
    8 -rw-r--r--  1 blyth dyw     4489 Nov 11 17:11 bashrc.sh
    4 drwxr-xr-x 11 blyth dyw     4096 Nov 11 16:35 junoenv
    L7[blyth@lxslc705 junotop]$ 

::

    === junoenv-offline: Please using junoenv env to setup the environment first


Forgot to setup sniper environment. So create a bash function for env hookup::

    jre(){ 
        : ~/.junosw_build_config
        : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont;
        local msg="=== $FUNCNAME: ";
        echo $msg;

        export JUNOTOP=$HOME/junotop
        source $JUNOTOP/bashrc.sh;
        source $JUNOTOP/sniper/InstallArea/bashrc;
        source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh;
        source $JUNOTOP/mt.sniper/InstallArea/bashrc;

        local setup=$JUNOTOP/junosw/InstallArea/setup.sh;
        [ -s "$setup" ] && source $setup

        jt(){ cd $JUNOTOP ; } 
        je(){ cd $JUNOTOP/junoenv ; } 

        echo $msg
    }



::

    bash junoenv offline
    bash junoenv offline-data 

    ==== junoenv-offline-data-checkout: downloading LFS object data under offline-data/
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa': 
    Enter passphrase for key '/afs/ihep.ac.cn/users/b/blyth/.ssh/id_rsa':                                                                                        
    Skipping object checkout, Git LFS is not installed for this repository.                                                                                      
    Consider installing it with 'git lfs install'.
    ~/junotop/junoenv ~/junotop/junoenv
    L7[blyth@lxslc701 junoenv]$ 



doing similar on N(workstation) with fresh junotop
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    N[blyth@localhost junotop]$ ln -s /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3
    N[blyth@localhost junotop]$ ln -s J23.1.0-rc3/sniper-v0.9.1.tar.gz
    N[blyth@localhost junotop]$ ln -s J23.1.0-rc3/sniper-v2.2.3.tar.gz
    N[blyth@localhost junotop]$ ln -s J23.1.0-rc3/bashrc.sh basis_bashrc.sh 
    N[blyth@localhost junotop]$ cp basis_bashrc.sh bashrc.sh 
    N[blyth@localhost junotop]$ vi bashrc.sh    ## unset JUNOTOP at head, set it at tail 
    N[blyth@localhost junotop]$ git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git

Hookup similar jre from ~/.bashrc::

    jre(){ 
        : ~/.junosw_build_config

        : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont;
        local msg="=== $FUNCNAME: ";
        echo $msg;

        export JUNOTOP=$HOME/junotop

        _source(){ [ -s "$1" ] && source "$1" ; } 
        _source $JUNOTOP/bashrc.sh;
        _source $JUNOTOP/sniper/InstallArea/bashrc;
        _source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh;
        _source $JUNOTOP/mt.sniper/InstallArea/bashrc;
        _source $JUNOTOP/junosw/InstallArea/setup.sh

        jt(){ cd $JUNOTOP && pwd ; } 
        je(){ cd $JUNOTOP/junoenv && pwd && git status ; } 
        jo(){ cd $JUNOTOP/junosw  && pwd && git status ; } 

        echo $msg
    }



    export JUNOTOP=$HOME/junotop    # thats symbolic linked to /data/$USER/junotop  
    source ~/.junosw_build_config   # jre function 

    N[blyth@localhost junoenv]$ bash junoenv sniper
    N[blyth@localhost junoenv]$ bash junoenv offline-data 

"bash junoenv offline" gets offline but then keeps asking to setup env,
even when have done so. So build with::

     jo
     ./build_Debug.sh 




Next step is "bash junoenv opticks"  
currentlyt the version is "head" which 
causes getting the 

::

    235 function junoenv-opticks-name { echo opticks ; }
    236 
    237 #function junoenv-opticks-version { echo v0.1.0-rc2 ; }
    238 function junoenv-opticks-version { echo head ; }
    239 
    240 function junoenv-opticks-url {
    241     local version=$(junoenv-opticks-version)
    242     if [ "${version:0:1}" == "v" ]; then
    243         echo https://github.com/simoncblyth/opticks/archive/refs/tags/$version.tar.gz 
    244     else
    245         case $USER in
    246              blyth) echo git@bitbucket.org:simoncblyth/opticks.git  ;;
    247                  *) echo https://bitbucket.org/simoncblyth/opticks  ;;
    248         esac



Old bashrc : hooks up the opticks- functions from source tree ? 
--------------------------------------------------------------------


/data/blyth/old_junotop/ExternalLibs/opticks/head/bashrc::

    opticks-(){ . /data/blyth/junotop/opticks/opticks.bash && opticks-env  ; }



HOW TO PROCEED : "bash junoenv opticks tar" ? NO : just use /cvmfs release
------------------------------------------------------------------------------

::

    N[blyth@localhost junoenv]$ bash junoenv opticks
    = The junoenv is in /data/blyth/junotop/junoenv
    = main
    = THE JUNOTOP is /home/blyth/junotop
    = THE JUNOENVDIR is /data/blyth/junotop/junoenv
    ...

    ==== junoenv-opticks-get: url git@bitbucket.org:simoncblyth/opticks.git base opticks.git name opticks PWD /home/blyth/junotop
    git clone git@bitbucket.org:simoncblyth/opticks.git opticks
    Cloning into 'opticks'...
    remote: Enumerating objects: 106335, done.
    remote: Counting objects: 100% (2128/2128), done.
    remote: Compressing objects: 100% (2046/2046), done.
    remote: Total 106335 (delta 1480), reused 102 (delta 80), pack-reused 104207
    Receiving objects: 100% (106335/106335), 100.14 MiB | 5.96 MiB/s, done.
    Resolving deltas: 100% (82966/82966), done.
    === junoenv-opticks: junoenv-opticks-get rc 0
    ==== junoenv-opticks-bashrc: Pre Requirement Check
    ==== junoenv-opticks-bashrc: source /home/blyth/junotop/bashrc.sh
    ==== junoenv-opticks-env: missing OPTICKS_CUDA_PREFIX envvar or invalid directory
    ==== junoenv-opticks-command: FAIL from junoenv-opticks-env
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: junoenv-opticks-full rc 2
    === junoenv-opticks: rc 2
    N[blyth@localhost junoenv]$ env | grep OPTICKS




"bash junoenv opticks" currently does an opticks source build. 
Instead want to base on a binary release on cvmfs. 


So start by getting a test release onto cvmfs
-------------------------------------------------

Extracting from tarball into /cvmfs/opticks.ihep.ac.cn/ok/releases/::

    L     # (ssh into lxslc7) ssh keys are setup there, so go that way 

    L> g 
    L> cd local/opticks
    L> scp Opticks-v0.2.1.tar O:   # copy tarball to stratum0 optickspub account 
    L> ssh O                       # into stratum0

    O> cvmfs_server transaction opticks.ihep.ac.cn   ## start transation to make it writable
    O> mv Opticks-v0.2.1.tar /cvmfs/opticks.ihep.ac.cn/ok/releases/
    O> cd /cvmfs/opticks.ihep.ac.cn/ok/releases/
    O> tar tvf Opticks-v0.2.1.tar  # check the paths in the tarball 
    O> tar xvf Opticks-v0.2.1.tar  # explode the tarball 
    O> rm Opticks-v0.2.1.tar       # remove tarball 
    O> cd /cvmfs                   # step away from modified folders
    O> cvmfs_server publish -m "Add Opticks-v0.2.1 test release " opticks.ihep.ac.cn
    O> exit 


* NB IT CAN TAKE 5 MIN OR SO BEFORE THE ADDITION APPEARS ON CLUSTER MACHINES AND WORKSTATION
   

Next step : try to get "jo ; ./build_Debug.sh " to build against that binary opticks release on /cvmfs
-------------------------------------------------------------------------------------------------------

::

    source /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/bashrc


1. add opticks line to junotop/bashrc.sh : source it and check OPTICKS env 
2. do the build and see if opticks is found and built against : it should when OPTICKS_PREFIX 
   is defined correctly 


Issue 1 : FindOpticks.cmake FAIL : fixed by changing cmake/legacy/JUNODependencies.cmake to use OPTICKS_PREFIX
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

::

    -- Found SNiPER: /hpcfs/juno/junogpu/blyth/junotop/sniper/InstallArea/lib64/cmake/SNiPER/SNiPERConfig.cmake  
    CMake Warning at cmake/legacy/JUNODependencies.cmake:171 (find_package):
      No "FindOpticks.cmake" found in CMAKE_MODULE_PATH.
    Call Stack (most recent call first):
      cmake/legacy.cmake:28 (include)
      CMakeLists.txt:53 (include)

    CMake Warning (dev) at cmake/legacy/JUNODependencies.cmake:171 (find_package):
      FindOpticks.cmake must either be part of this project itself, in this case
      adjust CMAKE_MODULE_PATH so that it points to the correct location inside
      its source tree.

cmake/legacy/JUNODependencies.cmake was assuming source tree, fixed that::

    ## Opticks
    if(DEFINED ENV{OPTICKS_PREFIX})
       set(Opticks_VERBOSE YES)
       #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{JUNOTOP}/opticks/cmake/Modules")
       set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{OPTICKS_PREFIX}/cmake/Modules")
       find_package(Opticks MODULE)
       message(STATUS "${CMAKE_CURRENT_LIST_FILE} : Opticks_FOUND:${Opticks_FOUND}" )
    endif()


TODO : switch to config finding for opticks not module finding ? 
-------------------------------------------------------------------
  

WIP : create minimal script to run with opticks
-------------------------------------------------

* j/ok.bash:ok-tds 



N : hookup old style source opticks build for faster cycle than making releases
---------------------------------------------------------------------------------

Comment the opticks release hookup in bashrc.sh::

     42 source /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/ExternalLibs/libonnxruntime/1.11.1/bashrc
     43 
     44 # hookup opticks release 
     45 # source /cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-v0.2.1/x86_64-CentOS7-gcc1120-geant4_10_04_p02-dbg/bashrc
     46 
     47 # hookup opticks source build prefix dir
     48 # source /home/blyth/junotop/ExternalLibs/opticks/head/bashrc
     49 
     50 export JUNOTOP=$(cd $(dirname $BASH_SOURCE) && pwd)
     51 


To ~/j/.junosw_build_config jre add func::

    _jre_opticks_workstation_source_build_env()
    {
        : ~/j/.junosw_build_config
        : this setup enables opticks-full source build ... so its bootstrapping 
        : mostly NOT needed for release running

        export OPTICKS_DOWNLOAD_CACHE=/data/opticks_download_cache
        export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.7
        export OPTICKS_OPTIX_PREFIX=/home/blyth/local/opticks/externals/OptiX_750
        export OPTICKS_COMPUTE_CAPABILITY=70

        export OPTICKS_PREFIX=/data/blyth/junotop/ExternalLibs/opticks/head
        export OPTICKS_HOME=/data/blyth/junotop/opticks
        export TMP=/data/blyth/opticks

        o(){  cd $JUNOTOP/opticks && pwd && git status ; } 
        opticks-(){ source $JUNOTOP/opticks/opticks.bash && opticks-env $* ; } 
        opticks-

        oo(){ opticks- ; cd $(opticks-home) ; om- ; om-- ;  }   

        : env setup used by om- oe- needs the opticks-setup.sh 
        : generated as part of opticks-full : so "oo" only works
        : for rebuilding after small changes, not initial building
    }


This enables first time build using junosw base externals::

    N
    opticks-full 



Hmm the spath.h changes are insufficient need to handle DefaultOutputDir resolution::

    2023-11-14 14:04:32.864 INFO  [353885] [SEvt::getOutputDir@3162] 
     base_  $DefaultOutputDir
     reldir   ALLVERSION
     sidx   p001
     path   UNRESOLVED_TOKEN_DefaultOutputDir/ALLVERSION/p001

    2023-11-14 14:04:32.864 INFO  [353885] [SEvt::save@3331]  dir UNRESOLVED_TOKEN_DefaultOutputDir/ALLVERSION/p001 index 1 instance 0 OPTICKS_SAVE_COMP  genstep,photon,hit,domain,inphoton
    [ sframe::save  dir : UNRESOLVED_TOKEN_DefaultOutputDir/ALLVERSION/p001 name: sframe
    ] sframe::save 
    2023-11-14 14:04:32.920 INFO  [353885] [SEvt::clear_except@1445] SEvt::clear_except
    junoSD_PMT_v2::EndOfEvent eventID 0 opticksMode 3 hitCollection 352923 hcMuon 0 hcOpticks 925 GP



