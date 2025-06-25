#!/bin/bash

usage(){ cat << EOU

~/j/zhanghaosen/Muon_Test2/run/run1_5.sh

EOU
}


######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=run1_5
#SBATCH --output=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/log/run1_5.txt

######## Part 2 #########


path=$(realpath $BASH_SOURCE)
fold=$(dirname $path)
relfold=${fold:$(( 1+${#HOME} ))}

tm=/tmp/$USER
export TM=${TM:-$tm}
DIR=$TM/$relfold
mkdir -p $DIR
cd $DIR

vv=""
vv="$vv BASH_SOURCE BASH_VERSION path fold relfold tm TM DIR PWD"
pvv(){ for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done ; } 

defarg=run
arg=${1:-$defarg}

vv="$vv defarg arg"
pvv


# should now not need the below in opticksMode:1
#export junoSD_PMT_v2__ProcessHits_EPH_NOLABEL=1


#lscpu
#nvidia-smi

#pushd /hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/root
#source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/envset.sh
source $HOME/junosw/InstallArea/envset.sh

export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=63
#export OPTICKS_EVENT_MODE=Minimal    ## this is default
export OPTICKS_HIT_MASK=EC            ## cannot be default, could be included in OJ environment

#export HOME=/hpcfs/juno/junogpu/zhanghaosen
#export TMP=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/Tmp/tmp5

if [ "${arg/run}" != "$arg" ]; then

    source dbg__.sh 

    dbg__ \
        $(which python) \
        $(which tut_detsim.py) \
        --no-gdml \
        --pmtsd-merge-twindow 1.0 \
        --event-split \
        --output oj_edm_5.root \
        --user-output oj_user_5.root \
        --evtmax 5 \
        --seed 5 \
        hepevt \
        --file $fold/file5;

    touch done_flag_5

fi 

pvv


