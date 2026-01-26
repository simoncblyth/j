#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1

usage(){ cat << EOH

$BASH_SOURCE usage
$BASH_SOURCE info
$BASH_SOURCE info_chk_env_run

EOH
}


path=$(realpath $BASH_SOURCE)
name=$(basename $path)
name=${name/.sh}

fold=$(dirname $path)
relfold=${fold:$(( 1+${#HOME} ))}  # assume repo is within original HOME
relpath=$relfold/$name

home=/hpcfs/juno/junogpu/$USER
tmp=$home/tmp/$relpath

export HOME=$home
export TMP=$tmp


envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.5.8/el9_amd64_gcc11/2026_01_18/envset.sh
ENVSET=${ENVSET:-$envset}

vv="envset ENVSET path name fold relfold relpath HOME TMP"

defarg=info
arg=${1:-$defarg}

if [ "${arg/usage}" != "$arg" ]; then
   usage
fi 

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do  printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/env}" != "$arg" ]; then

    source $ENVSET

    #export CUDA_VISIBLE_DEVICES=0
    #export OPTICKS_MAX_BOUNCE=31
    #export OPTICKS_EVENT_MODE=Minimal


    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from env && exit 1
fi

if [ "${arg/chk}" != "$arg" ]; then
    lscpu
    nvidia-smi
fi 

if [ "${arg/run}" != "$arg" ]; then

    pushd $TMP

    time \
        $(which python) \
        $(which tut_detsim.py) \
        --output oj_edm.root \
        --user-output oj_user.root \
        --evtmax 1 \
        --seed 42 \
        gun \
        --momentums 1.0;

   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from run && exit 2

   popd

fi

if [ "${arg/sub}" != "$arg" ]; then

   sbatch --job-name=$name $BASH_SOURCE info_chk_env_run
   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from sub && exit 3

fi 

exit 0


