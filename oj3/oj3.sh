#!/bin/bash
usage(){ cat << EOU
oj3.sh : example opticksMode:3 script using cvmfs auto-built JUNOSW+Opticks
=============================================================================

Usage:


0. clone OJ repo:

   git clone https://code.ihep.ac.cn/blyth/oj.git

1. use "env" to check if some of the JUNOSW runtime envvars
   are already present. If so then change .bash_profile .bashrc etc..
   to remove that setup then exit your session and start new one.

2. repeat 1. until you get a clean env

3. add some bash functions to work with this script::


    ## when you want to have persistent env use source
    source oj3.sh env_info_chi2
    source oj3.sh info_pdb

    ## after script has stopped changing all the time 
    ## use "./oj3.sh" for definiteness



    oj3(){ ~/oj/oj3.sh $* ; }
    oj3dbg(){ DBG=1 ~/oj/oj3.sh $* ; }
    oj3v(){ vi ~/oj/oj3.sh ; }

    t(){ typeset -f $* ; }

4. check some commands::

    oj3


    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.3.6/el9_amd64_gcc11/Latest/envset.sh
    tut_detsim.py --opticks-mode 1 --evtmax 10 gun
    tut_detsim.py --evtmax 10 gun                    ## opticks-mode 1 is default within OJ environment


ipython and conda
------------------

The pdb uses ipython which is not part of release, use your own conda install::

    hookup_conda
    conda activate ok   ## ok is a conda virtual env with : ipython + matplotlib + pyvista


EOU
}

defarg="env_info_run_chi2_pdb"
arg=${1:-$defarg}
vars="BASH_SOURCE 0 defarg arg envset _envset OPTICKS_SCRIPT OJ_LOGDIR LOG DBG CMD GEOM OPTICKS_MAX_BOUNCE AFOLD BFOLD anascript"
anascript=oj3ana.py

release_env()
{
    envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.0/el9_amd64_gcc11/Sat/envset.sh
    _envset=$(realpath $envset)

    echo [ source ${_envset}
    source ${_envset}
    echo ] source ${_envset}
}


local_env()
{
   echo TODO
}


no-anamgr(){ cat << EOU
--no-anamgr-normal \
--no-anamgr-genevt \
--no-anamgr-edm-v2 \
--no-anamgr-grdm \
--no-anamgr-deposit \
--no-anamgr-deposit-tt \
--no-anamgr-interesting-process \
--no-anamgr-optical-parameter \
--no-anamgr-timer
EOU
   : opticksMode 2 or 3 requires no-anamgr that use Geant4 trackinfo
}


inputphoton-set()
{
    : this is invoked from jok-tds when GUN is zero
    type $FUNCNAME
    export OPTICKS_RUNNING_MODE=SRM_INPUT_PHOTON
    export OPTICKS_INPUT_PHOTON=RainXZ_Z230_10k_f8.npy
    export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000
}

inputphoton-unset()
{
    : this is invoked from jok-tds when GUN is non-zero
    type $FUNCNAME
    unset OPTICKS_RUNNING_MODE
    unset OPTICKS_INPUT_PHOTON
    unset OPTICKS_INPUT_PHOTON_FRAME
}


oj3_env()
{
    release_env

    export OPTICKS_SCRIPT=oj3_sh  ## HMM: should this be included in envset, no its too user domain and not needed
    export OJ_LOGDIR=/tmp/$USER/opticks/GEOM/$GEOM/$OPTICKS_SCRIPT
    oj_find(){ find $OJ_LOGDIR -name '*.npy' ; }

    ## optionally enable saving of Debug photon history arrays
    export OPTICKS_EVENT_MODE=DebugLite
    if [ "$OPTICKS_EVENT_MODE" == "DebugLite" ]; then
        export OPTICKS_MAX_SLOT=M2
        ## with debug arrays enabled must limit max slot to avoid VRAM OOM
    fi


    ctx=DebugPhilox   ## when setting EVENT_NAME it must contain context string matching the build
    #name=ShakedownGUN
    name=ShakedownIPH

    export OPTICKS_EVENT_NAME=$ctx$name
    export OPTICKS_MAX_BOUNCE=31
    export OPTICKS_INTEGRATION_MODE=3

    CMD=""
    [ -n "$DBG" ] && CMD="gdb -ex r --args $(which python) "
    CMD="$CMD $(which tut_detsim.py)"

    [ "$OPTICKS_INTEGRATION_MODE" == "3" -o "$OPTICKS_INTEGRATION_MODE" == "2"  ] && CMD="$CMD $(no-anamgr)"


    inputphoton-unset

    if [ "${name/GUN}" != "$name" ]; then
        GUN=gun
    elif [ "${name/IPH}" != "$name" ]; then
        GUN=opticks
        inputphoton-set
    fi

    CMD="$CMD --opticks-anamgr"   ## use U4Recorder to record Geant4 propagaion
    CMD="$CMD --evtmax 1 --no-toptask-show --opticks-mode $OPTICKS_INTEGRATION_MODE"
    CMD="$CMD $GUN"


    ## settings for analysis only : ie have no effect on running
    export VERSION=0
    export AFOLD=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}/A000
    export BFOLD=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}/B000
}




if [ "${arg/env}" != "$arg" ]; then
   oj3_env
fi


logging(){
    type $FUNCNAME
    #export QEvent=INFO
    export QU=INFO
    export SEvt__LIFECYCLE=1
    export SEvt=INFO
    export U4Recorder=INFO
}
[ -n "$LOG" ] && logging
#logging




if [ "${arg/info}" != "$arg" ] ; then
   for var in $vars ; do printf "%20s : %s\n" "$var" "${!var}" ; done
fi


if [ "${arg/run}" != "$arg" ] ; then

    echo [ run
    iwd=$PWD

    if [ -n "$OJ_LOGDIR" ]; then
       echo $0 OJ_LOGDIR $OJ_LOGDIR
       mkdir -p $OJ_LOGDIR && cd $OJ_LOGDIR && pwd
    fi

    echo $CMD
    [ ! -n "$DEBUG" ] && eval $CMD


    if [ -n "$OJ_LOGDIR" ]; then
       pwd
       echo $0 OJ_LOGDIR $OJ_LOGDIR
       ls -alst $OJ_LOGDIR
    fi

    cd $iwd && pwd
    echo ] run
fi

if [ "${arg/chi2}" != "$arg" ] ; then
   export AFOLD=A000
   export BFOLD=B000
   sseq_index_test.sh info_run_ana
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error
fi


