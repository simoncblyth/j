# .bash_profile > .bashrc > .opticks_config   (workstation/simon)
usage(){ cat << EOU
~/.opticks_config
========================

Caution this is now sourced first - with almost no environment - it constitutes
the inputs that control the opticks build

Build and usage config, build config should provide the environment to complete opticks-full.
Note how sourcing the bashrc rather than using opticks-prepend-prefix
allows more intuitive ordering.

EOU
}



### TOP CONFIG RELEVANT TO BOTH BUILD AND USAGE ###

export OPTICKS_HOME=$HOME/opticks

config=Debug
export OPTICKS_CONFIG=${OPTICKS_CONFIG:-$config}

buildtype=Debug
case $OPTICKS_CONFIG in
   Debug)    buildtype=Debug ;;
   Release)  buildtype=Release ;;
   Client)   buildtype=Debug  ;;
esac

[   -z "$VIP_LOCAL_BASE" ] && echo $BASH_SOURCE - FATAL MISSING VIP_LOCAL_BASE $VIP_LOCAL_BASE && return 1
[ ! -d "$VIP_LOCAL_BASE" ] && echo $BASH_SOURCE - FATAL NON-EXISTING VIP_LOCAL_BASE $VIP_LOCAL_BASE && return 1

export OPTICKS_BUILDTYPE=$buildtype
#export OPTICKS_PREFIX=$VIP_LOCAL_BASE/local/opticks_${OPTICKS_BUILDTYPE}
export OPTICKS_PREFIX=$VIP_LOCAL_BASE/local/opticks_${OPTICKS_CONFIG}    # Apr23 2026 : Generalize to OPTICKS_CONFIG



export TMP=$VIP_LOCAL_BASE/tmp   # override default TMP of /tmp/$USER/opticks
mkdir -p $TMP                 # whether override or not, need to create

export CUDA_VISIBLE_DEVICES=0

## PUTTING HOME INTO PYTHONPATH MIXES SOURCE AND INSTALL TREES
## BREAKING ISOLATION BETWEEN THE TWO TREES - DO NOT DO THIS
## export PYTHONPATH=$(dirname $OPTICKS_HOME)


#export IPYTHON=/home/blyth/local/env/tools/conda/miniconda3/bin/ipython

opticks-(){  [ -r $OPTICKS_HOME/opticks.bash ] && . $OPTICKS_HOME/opticks.bash && opticks-env $* ; }
opticks-


#ctrl="build_usage"
ctrl="build"


if [ "${ctrl/build}" != "$ctrl" ]; then


    # config system level pre-requisites
    #export OPTICKS_CUDA_PREFIX=/usr/local/cuda-11.7
    #export OPTICKS_CUDA_PREFIX=/usr/local/cuda-12.4    ## USED UNTIL JUN 2026
    export OPTICKS_CUDA_PREFIX=/usr/local/cuda-13.1     ## TEST FROM JUN 2026

    #export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_750
    #export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_760
    #export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_770
    #export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_800    ## USED UNTIL JUN 2026
    export OPTICKS_OPTIX_PREFIX=/cvmfs/opticks.ihep.ac.cn/external/OptiX_910     ## TEST FROM JUN 2026

    ## should set to lowest CC that wish to support, not the highest
    ##export OPTICKS_COMPUTE_CAPABILITY=70   ## CUDA 13.1 DROPS SUPPORT FOR VOLTA
    export OPTICKS_COMPUTE_CAPABILITY=89

    ## comma delimited list of the CC of GPUs that wish to build for
    #export OPTICKS_COMPUTE_ARCHITECTURES=70,89
    export OPTICKS_COMPUTE_ARCHITECTURES=89,120   ## 120 FOR RTX PRO 6000 BLACKWELL

    # config opticks build : wheres the source, where to install etc..
    export OPTICKS_DOWNLOAD_CACHE=/cvmfs/opticks.ihep.ac.cn/opticks_download_cache
    export EXTERNALS_DOWNLOAD_CACHE=/cvmfs/opticks.ihep.ac.cn/opticks_download_cache
fi

if [ "${ctrl/usage}" != "$ctrl" ]; then
    source $OPTICKS_PREFIX/bashrc
fi


