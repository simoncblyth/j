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

path=$(realpath $BASH_SOURCE)
name=$(basename $path)
stem=${name/.sh}
fold=$(basename $(dirname $path))

tmp=/tmp/$USER/opticks
export TMP=${TMP:-$tmp}
DIR=$TMP/j/$fold/$stem
mkdir -p $DIR
cd $DIR

vv=""
vv="$vv BASH_SOURCE path name stem fold tmp TMP DIR PWD"
pvv(){ for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; }
pvv


defarg="run"
arg=${1:-$defarg}

#source  /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/envset.sh
source /home/blyth/junosw/InstallArea/envset.sh

#export SEvt__SAVE_NOTHING=1
export OPTICKS_EVENT_MODE=DebugLite

export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=63
#export OPTICKS_EVENT_MODE=Minimal   ## Minimal is the default SEventConfig::EventMode
export OPTICKS_HIT_MASK=EC  ## EC:EFFICIENCY_COLLECT changed from default SD:SURFACE_DETECT

source dbg__.sh


if [ "${arg/run}" != "$arg" ]; then

    lscpu
    nvidia-smi

    dbg__ \
            $(which python) \
            $(which tut_detsim.py) \
            --no-gdml \
            --pmtsd-merge-twindow 1.0 \
            --event-split \
            --output oj_edm.root \
            --user-output oj_user.root \
            --evtmax 10 \
            --seed 42 \
            hepevt \
            --exe Muon;

    touch done_flag
    pvv

fi


if [ "${arg/ls}" != "$arg" ]; then
   outfold=/tmp/$USER/opticks/GEOM/$GEOM/python3.11/ALL${VERSION:-0}_no_opticks_event_name
   cmd="ls -alst $outfold"
   echo $cmd
   eval $cmd
fi 

