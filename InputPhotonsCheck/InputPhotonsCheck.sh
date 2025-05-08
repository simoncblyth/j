#!/bin/bash
usage(){ cat << EOU
InputPhotonsCheck.sh
=====================

NB while it is convenient for debug to inhabit some env
setup in .bashrc etc.. for scripts its better to use an
almost empty env and do all setup in the script.

AN::

    ~/j/InputPhotonsCheck/InputPhotonsCheck.sh


    cd /tmp/blyth/opticks/GEOM/J25_3_0_Opticks_v0_4_1/InputPhotonsCheck/ALL0_DebugPhilox
    ~/j/InputPhotonsCheck/InputPhotonsCheck.sh chi2
    

EOU
}

#cd $(dirname $(realpath $BASH_SOURCE))

anascript=oj3ana.py

defarg="env_info_run_ls_chi2"
arg=${1:-$defarg}

if [ "${arg/env}" != "$arg" ]; then

    source /home/blyth/junosw/InstallArea/envset.sh

    export CUDA_VISIBLE_DEVICES=0
    export OPTICKS_MAX_SLOT=M5
    export OPTICKS_MAX_BOUNCE=31
    export OPTICKS_EVENT_MODE=DebugLite

    ## config input photon running
    export SEvt__INPUT_PHOTON_DIR=/cvmfs/opticks.ihep.ac.cn/.opticks/InputPhotons
    #opticks_input_photon=RainXZ_Z230_10k_f8.npy
    opticks_input_photon=RainXZ_Z230_1M_f8.npy
    export OPTICKS_INPUT_PHOTON=${opticks_input_photon}
    export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000


    ## optional env adapting output directory for .npy arrays
    ## OPTICKS_EVENT_NAME is required to contain strings such as "Debug" and "Philox" 
    ## when those correspond to the build config as checked by sbuild::Matches
    export OPTICKS_SCRIPT=InputPhotonsCheck
    export OPTICKS_EVENT_NAME=DebugPhilox
    export VERSION=0

    ## convenience vars for analysis
    export LOGDIR=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}
    export EVT=000
    export AFOLD=$LOGDIR/A$EVT
    export BFOLD=$LOGDIR/B$EVT

    mkdir -p $LOGDIR
    cd $LOGDIR && pwd

    ## HMM: getting into env takes a few seconds, can avoid that by caching the env needed for analysis into LOGDIR
    ## actually could just use relative dirs from the LOGDIR avoiding the need to get into env
fi


if [ "${arg/info}" != "$arg" ]; then
   vv="BASH_SOURCE defarg arg TMP GEOM LOGDIR AFOLD BFOLD IPYTHON PYTHON"
   for v in $vv ; do printf "%20s :  %s\n" "$v" "${!v}" ; done
fi


if [ "${arg/run}" != "$arg" ]; then

    gdb -ex r --args \
        $(which python) \
        $(which tut_detsim.py) \
        --opticks-mode 3 \
        --opticks-anamgr \
        --no-anamgr-normal \
        --no-anamgr-genevt \
        --no-anamgr-edm-v2 \
        --no-anamgr-grdm \
        --no-anamgr-deposit \
        --no-anamgr-deposit-tt \
        --no-anamgr-interesting-process \
        --no-anamgr-optical-parameter \
        --no-anamgr-timer \
        --evtmax 1 \
        --seed 42 \
        opticks

    rc=$?
    echo DONE $rc
    pwd
fi


if [ "${arg/ls}" != "$arg" ]; then
    ff="LOGDIR AFOLD BFOLD"
    for f in $ff ; do echo $f ${!f} && ls -alst ${!f} ; done
fi

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $anascript
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error
fi

if [ "${arg/chi2}" != "$arg" ] ; then
   sseq_index_test.sh info_run_ana
fi



