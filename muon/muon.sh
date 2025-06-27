#!/bin/bash
usage(){ cat << EOU

  ~/j/muon/muon.sh

EOU
}


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
sfold=$(dirname $path)
script=$sfold/muon.py

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

allarg="info_run_ls"
defarg="info_run_ls"
arg=${1:-$defarg}

vv="$vv allarg defarg arg"


#source  /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/envset.sh
#source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.8/el9_amd64_gcc11/2025_06_25/envset.sh
source /home/blyth/junosw/InstallArea/envset.sh

#export SEvt__SAVE_NOTHING=1
#export OPTICKS_EVENT_MODE=Minimal   ## Minimal is the default SEventConfig::EventMode
export OPTICKS_EVENT_MODE=DebugLite

export OPTICKS_MAX_SLOT=M10

export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=63
export OPTICKS_HIT_MASK=EC  ## EC:EFFICIENCY_COLLECT changed from default SD:SURFACE_DETECT

export QEvent=INFO
export QSim__ALLOC=1   # SEventConfig::ALLOC dumping before launch

export BASE=/tmp/$USER/opticks/GEOM/$GEOM/python3.11/ALL${VERSION:-0}_no_opticks_event_name
export AFOLD=$BASE/A001
vv="$vv BASE AFOLD"


if [ "${arg/info}" != "$arg" ]; then
    pvv
fi

if [ "${arg/run}" != "$arg" ]; then

    #lscpu
    #nvidia-smi

    source dbg__.sh
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
   cmd="ls -alst $BASE"
   echo $cmd
   eval $cmd
fi 


if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 1 
fi 

exit 0 


