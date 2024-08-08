shakedown_remote
==================

Overview
----------

Old environment "jre" no longer working, now need "jsw"


Issue : trying to use jre/oo fails
--------------------------------------

Uncommented::

     77 source ~/j/.junosw_build_config   # jre function 
     78 #jre

But fails::

    N[blyth@localhost opticks]$ oo
    === om-env : normal running
    -bash: /home/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh: No such file or directory
    === om-check : top level bdir /home/blyth/junotop/ExternalLibs/opticks/head/build/ does not exist : creating it
    mkdir: cannot create directory ‘/home/blyth/junotop/ExternalLibs/opticks’: Read-only file system
    === om-check : top level bdir /home/blyth/junotop/ExternalLibs/opticks/head/build/ does not exist : create failed
    === om-one-or-all make : ERROR om-check failed
    bash: om-name: command not found...
    bash: om-local: command not found...
    bash: om-fold: command not found...

       om-home-default    : /home/blyth/junotop/opticks
       om-home            : /home/blyth/junotop/opticks  from OPTICKS_HOME envvar if defined 
       om-name            : 
       om-local           :   from LOCAL_BASE envvar if defined
       om-fold            : 
       om-prefix          : /home/blyth/junotop/ExternalLibs/opticks/head
       om-cmake-generator : Unix Makefiles
       om-bdir            : /home/blyth/junotop/ExternalLibs/opticks/head/build/
       om-sdir            : /home/blyth/junotop/opticks/




::

    N[blyth@localhost opticks]$ t oo
    oo () 
    { 
        opticks-;
        cd $(opticks-home);
        om-;
        om--;
        : opticks.bash
    }
    N[blyth@localhost opticks]$ om-
    === om-env : normal running
    -bash: /home/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh: No such file or directory
    N[blyth@localhost opticks]$ 



No opticks dir::

    N[blyth@localhost opticks]$ l /home/blyth/junotop/ExternalLibs/
    total 24
    1 drwxr-xr-x.  8 cvmfs cvmfs   44 May  5 02:46 ..
    1 drwxr-xr-x.  2 cvmfs cvmfs   27 May  5 02:36 custom4
    1 drwxr-xr-x.  2 cvmfs cvmfs   36 May  5 02:35 Geant4
    5 drwxr-xr-x. 39 cvmfs cvmfs 4096 May  5 02:35 .

::

     42 _jre_opticks_build_env()
     43 {
     44     : ~/j/.junosw_build_config
     45     : this setup enables opticks-full source build ... so its bootstrapping
     46     : mostly NOT needed for release running
     47 
     48     export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.7
     49     export OPTICKS_DOWNLOAD_CACHE=/cvmfs/opticks.ihep.ac.cn/opticks_download_cache
     50     export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_750
     51     export OPTICKS_COMPUTE_CAPABILITY=70
     52 
     53     opticks-(){ source $JUNOTOP/opticks/opticks.bash && opticks-env $* ; }
     54     opticks-
     55 
     56     oo(){ opticks- ; cd $(opticks-home) ; om- ; om-- ;  }
     57     : running oo needs OPTICKS_PREFIX to find bin/opticks-setup.sh
     58 
     59     export OPTICKS_PREFIX=$JUNOTOP/ExternalLibs/opticks/head
     60     export OPTICKS_HOME=$JUNOTOP/opticks
     61 
     62     : env setup used by om- oe- needs the opticks-setup.sh
     63     : generated as part of opticks-full : so "oo" only works
     64     : for rebuilding after small changes, not initial building
     65     : initial building requires opticks-full
     66 }


::

    N[blyth@localhost opticks]$ t om-
    om- () 
    { 
        . $(opticks-home)/om.bash && om-env $*
    }
    N[blyth@localhost opticks]$ . $(opticks-home)/om.bash
    N[blyth@localhost opticks]$ om-env
    === om-env : normal running
    -bash: /home/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh: No such file or directory
    N[blyth@localhost opticks]$ 


    N[blyth@localhost opticks]$ t om-env
    om-env () 
    { 
        olocal-;
        opticks-;
        local msg="=== $FUNCNAME :";
        if [ "$1" == "quiet" -o "$1" == "q" -o -n "$OPTICKS_QUIET" ]; then
            oe- 2> /dev/null;
        else
            echo $msg normal running;
            oe-;
        fi
    }


    N[blyth@localhost opticks]$ oe-
    -bash: /home/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh: No such file or directory
    N[blyth@localhost opticks]$ 

    N[blyth@localhost opticks]$ t oe-
    oe- () 
    { 
        . $(opticks-home)/oe.bash && oe-env $*
    }

    N[blyth@localhost opticks]$ oe-env
    -bash: /home/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh: No such file or directory
    N[blyth@localhost opticks]$ t oe-env
    oe-env () 
    { 
        olocal-;
        opticks-;
        source $OPTICKS_PREFIX/bin/opticks-setup.sh 1>&2
    }
    N[blyth@localhost opticks]$ 



Hmm opticks-full fails because ExternalLibs is symbolic link to readonly cvmfs

That means must have stomped on OPTICKS_PREFIX with jre::

     63     #export OPTICKS_BUILDTYPE=Debug
     64     export OPTICKS_BUILDTYPE=Release
     65     export OPTICKS_PREFIX=/data/$USER/opticks_${OPTICKS_BUILDTYPE}
     66     mkdir -p $OPTICKS_PREFIX
     67 
     68     export TMP=/data/$USER/opticks
     69     mkdir -p $TMP
     70 
     71     opticks-(){ . $HOME/opticks/opticks.bash && opticks-env $* ; : .bashrc/.local.bash ; }
     72     opticks-

Yep, look to now use jsw::

    085 jsw(){
     86     source $JUNOTOP/setup.sh
     87     opticks-(){ . $HOME/opticks/opticks.bash && opticks-env $* ; : .bashrc/.local.bash ; }
     88     opticks-
     89 
     90     source ~/j/jok.bash
     91 
     92     export OPTICKS_DOWNLOAD_CACHE=/data/opticks_download_cache
     93     export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.7
     94     export OPTICKS_OPTIX_PREFIX=/home/blyth/local/opticks/externals/OptiX_750
     95     export OPTICKS_COMPUTE_CAPABILITY=70
     96     export OPTICKS_BUILDTYPE=Debug
     97     export OPTICKS_PREFIX=/data/$USER/opticks_${OPTICKS_BUILDTYPE}
     98     mkdir -p $OPTICKS_PREFIX
     99 
    100     export TMP=/data/$USER/opticks
    101     mkdir -p $TMP
    102 
    103 }



