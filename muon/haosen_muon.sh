#!/bin/bash

######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=Mode1

######## Part 2 #########

usage(){ cat << EOU

Started from Haosen::

    generation_opticks_mode1_muon.sh

EOU
}

path=$(realpath $BASH_SOURCE)
name=$(basename $path)
stem=${name/.sh}
fold=$(basename $(dirname $path))

tmp=/tmp/$USER/opticks
export TMP=${TMP:-$tmp}
DIR=$TMP/j/$fold/$stem
mkdir -p $DIR


defarg="ctx_env_info_run"
arg=${1:-$defarg}

vv=""
vv="$vv BASH_SOURCE path name stem fold DIR"
vv="$vv TUTORIALROOT"

if [ "${arg/ctx}" != "$arg" ]; then
    lscpu
    nvidia-smi
fi

if [ "${arg/env}" != "$arg" ]; then

    #source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/2025_06_01/envset.sh
    source /home/blyth/junosw/InstallArea/envset.sh

    export QSim=INFO
    export CSGOptiX=INFO 
    #export QSim__SAVE_IGS_EVENTID=6
    export QSim__CONCAT=1


    #export OPTICKS_MAX_SLOT=M10    
    #export OPTICKS_MAX_SLOT=M1
    #export OPTICKS_MAX_SLOT=H1  ## 0.1 million  K100
    export OPTICKS_MAX_SLOT=K1   ## 


    export CUDA_VISIBLE_DEVICES=0
    export OPTICKS_MAX_BOUNCE=63
    export OPTICKS_EVENT_MODE=Minimal

    #export HOME=/hpcfs/juno/junogpu/zhanghaosen
    #export TMP=/hpcfs/juno/junogpu/zhanghaosen/Test1/GPU/mode1_muon/tmp

    #export BP="DsG4Scintillation::PostStepDoIt DsG4Scintillation::DsG4Scintillation"


    export CSGOptiX__optixpath=$OPTICKS_PREFIX/ptx/objects-Debug/CSGOptiXOPTIX/CSGOptiX7.ptx


fi


if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi 

if [ "${arg/run}" != "$arg" ]; then

    cd $DIR
    source dbg__.sh

    dbg__ \
        $(which python) \
        $(which tut_detsim.py) \
        --no-gdml \
        --pmtsd-merge-twindow 1.0 \
        --event-split \
        --output oj_edm.root \
        --user-output oj_user.root \
        --evtmax 100 \
        --seed 42 \
        hepevt \
        --exe Muon;

    touch done_flag
fi

