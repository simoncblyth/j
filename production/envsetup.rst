
envsetup on N : Tracing environment setup and junosw + opticks integration mechanics
-------------------------------------------------------------------------------------------

Q: Where is runtime OPTICKS_PREFIX exported from ?
A: Sourcing sequence:: 

    (externals runtime env)JUNOTOP/bashrc.sh 
              (hookup line)OPTICKS_PREFIX/bashrc
          (generated scipt)OPTICKS_PREFIX/bin/opticks-setup.sh


local .bashrc sets build env 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The below 5 OPTICKS envvars are defined in .bashrc::

    epsilon:~ blyth$ N
    N[blyth@localhost ~]$ env | grep OPTICKS
    OPTICKS_COMPUTE_CAPABILITY=70
    OPTICKS_OPTIX_PREFIX=/home/blyth/local/opticks/externals/OptiX_700
    OPTICKS_CUDA_PREFIX=/usr/local/cuda
    OPTICKS_HOME=/data/blyth/junotop/opticks 
    OPTICKS_DOWNLOAD_CACHE=/data/opticks_download_cache
    N[blyth@localhost ~]$ 

This config from .bashrc is regarded as buildtime env, it gets copies 
into the opticks-setup.sh script by the opticks-setup-generate.
Whence it is later sourced to form part of the runtime environment.  


* first 3 are mandatory, last 2 just useful

After jre, get additional 5 envvars::

    N[blyth@localhost ~]$ jre
    /data/blyth/junotop/junosw
    N[blyth@localhost junosw]$ env | grep OPTICKS
    OPTICKS_TMP=/tmp/blyth/opticks
    OPTICKS_PREFIX=/data/blyth/junotop/ExternalLibs/opticks/head
    OPTICKS_EVENT_BASE=/tmp/blyth/opticks
    OPTICKS_STTF_PATH=/data/blyth/junotop/ExternalLibs/opticks/head/externals/imgui/imgui/extra_fonts/Cousine-Regular.ttf
    OPTICKS_GEANT4_PREFIX=/data/blyth/junotop/ExternalLibs/Geant4/10.04.p02.juno
    #OPTICKS_COMPUTE_CAPABILITY=70
    #OPTICKS_OPTIX_PREFIX=/home/blyth/local/opticks/externals/OptiX_700
    #OPTICKS_CUDA_PREFIX=/usr/local/cuda
    #OPTICKS_HOME=/data/blyth/junotop/opticks
    #OPTICKS_DOWNLOAD_CACHE=/data/opticks_download_cache
    N[blyth@localhost junosw]$ 

::

    N[blyth@localhost junosw]$ t jre
    jre () 
    { 
        jx-runtime-env;
        jo;
        if [ -n "$OPTICKS_PREFIX" ]; then
            : TODO add these settings to standard environment;
            opticks-;
            export PYTHONPATH=$PYTHONPATH:$JUNOTOP;
        fi
    }
    ### THIS IS TO ENABLE "import opticks" FROM PYTHON 
    ### JUNOTOP playing the role of HOME


    N[blyth@localhost junosw]$ t jx-runtime-env-
    jx-runtime-env- () 
    { 
        : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont;
        local msg="=== $FUNCNAME: ";
        echo $msg;
        source $JUNOTOP/bashrc.sh;
        source $JUNOTOP/sniper/InstallArea/bashrc;
        source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh;
        source $JUNOTOP/mt.sniper/InstallArea/bashrc;
        source $JUNOTOP/junosw/InstallArea/setup.sh;
        echo $msg
    }


JUNOTOP/bashrc.sh::

     ..
     36 source /data/blyth/junotop/ExternalLibs/gibuu/r2021_01/bashrc
     37 source /data/blyth/junotop/ExternalLibs/libmore/0.8.3/bashrc
     38 source /data/blyth/junotop/ExternalLibs/libonnxruntime/1.11.1/bashrc
     39 source /data/blyth/junotop/ExternalLibs/opticks/head/bashrc # Tue Sep 27 19:24:34 CST 2022

* hmm : i recall hookup functions to add that line ... where are those ? 


/data/blyth/junotop/ExternalLibs/opticks/head/bashrc


::

    N[blyth@localhost junotop]$ cat /data/blyth/junotop/ExternalLibs/opticks/head/bashrc

    if [ -s "/data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh" ]; then 

        # get CMTEXTRATAGS to contain the string opticks switching on WITH_G4OPTICKS macro in offline compilation
        if [ -z "$CMTEXTRATAGS" ]; then   # not yet defined
            CMTEXTRATAGS="opticks"
        elif [ "${CMTEXTRATAGS/opticks}" == "${CMTEXTRATAGS}" ]; then  # defined but without opticks
            CMTEXTRATAGS=:opticks
        fi 
        export CMTEXTRATAGS

        if [ -n "$VERBOSE" ]; then 
           source /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh 
        else
           source /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh > /dev/null
        fi  

        opticks-(){ . /data/blyth/junotop/opticks/opticks.bash && opticks-env  ; }

    else
        if [ -n "$VERBOSE" ]; then 
            echo script /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh does not exist 
        fi
    fi 


WHEN IS THE ABOVE INTERMEDIARY SCRIPT GENERATED ?


* TODO: get rid of the CMTEXTRATAGS guff 
* HUH: why not define the opticks- within the setup ? probably because 
  that function is used to build opticks when not embedded within another package 

Setup is done via::

   source /data/blyth/junotop/ExternalLibs/opticks/head/bin/opticks-setup.sh 

The opticks-setup.sh is too long... needs trimming : notice the 
distinction between buildenv and userenv::

    # mandatory envvars from buildenv propagated into userenv via this setup
    export OPTICKS_PREFIX=/data/blyth/junotop/ExternalLibs/opticks/head
    export OPTICKS_CUDA_PREFIX=/usr/local/cuda
    export OPTICKS_OPTIX_PREFIX=/home/blyth/local/opticks/externals/OptiX_700

* crucially the OPTICKS_PREFIX envvar is set by sourcing the opticks-setup.sh : that 
  triggers the offline CMake build to add opticks dependencies to some packages 

* sourcing the opticks-setup.sh is happens via OPTICKS_PREFIX/bashrc with gets 
  sourced via the hookup line in JUNOTOP/bashrc.sh 

So in sequence, when opticks is enabled

1. JUNOTOP/bashrc.sh contains hookup line that sources OPTICKS_PREFIX/bashrc
2. OPTICKS_PREFIX/bashrc sources OPTICKS_PREFIX/bin/opticks-setup.sh setting 
   OPTICKS_PREFIX and appending to PATH variables 
3. 

 



* TODO: review opticks-setup-generate removing stuff no longer used 


How does junosw+opticks build the opticks optional external ? 
-----------------------------------------------------------------

::

    bash junoenv opticks
    bash junoenv opticks help    # brief
    bash junoenv opticks notes   # detailed







