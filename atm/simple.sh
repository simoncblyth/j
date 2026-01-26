#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --wait-all-nodes=1


usage(){ cat << EOH

$BASH_SOURCE usage
$BASH_SOURCE info
$BASH_SOURCE info_chk_env_run


Some commands to query and control a slurm job::

    U[blyth@lxlogin004 j]$ atm/simple.sh sub
    Submitted batch job 2934490
    U[blyth@lxlogin004 j]$ JID=2934490

    squeue -u $USER   # list jobs from USER

    scontrol show job $JID  # show details of one job

    sstat -j $JID --format=JobId,MaxRSS,AveCPU,MaxDiskRead  # show what the job is doing

    tail -f slurm-$JID.out   # follow output from tail of the job log

    scancel $JID  # cancel a job if tail of log shows issue


EOH
}


ORIGINAL_HOME=$HOME
JUNOGPU=/hpcfs/juno/junogpu

if [ -d "$JUNOGPU" ]; then
    home=$JUNOGPU/$USER
    export HOME=$home
    # redefining HOME on lxlogin avoids AFS token complications
fi


export PYTHONUNBUFFERED=1

if command -v srun >/dev/null 2>&1 && [ -n "$SLURM_JOB_ID" ]; then
    # --label adds task ID to every line of output (great for debugging)
    # --output causes it to flush the buffer more aggressively
    RUNNER="srun --label --output=line"
else
    RUNNER=""
fi




ENVSET_SH=$HOME/ENVSET.sh
ENVSET_SH_TEMPLATE(){  cat << EOT

# NB this defines ENVSET pointing to the environment script based on envset_name
# it does not source that

envset_name=OJ_58

case \$envset_name in
  OJ_58)  envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.5.8/el9_amd64_gcc11/2026_01_18/envset.sh ;;
  OJ_59)  envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.5.9/el9_amd64_gcc11/2026_01_26/envset.sh ;;
  OJ_00)  envset=\$HOME/junosw/InstallArea/main/envset.sh  ;;
esac

if [ "\$envset_name" == "OJ_00" ]; then
   envset_name=OJ_00_\$(date -r \$envset  '+%b%d')
fi

export ENVSET_NAME=\$envset_name
export ENVSET=\$envset

EOT

}

[ ! -f "$ENVSET_SH" ] && echo $BASH_SOURCE CREATING ENVSET_SH $ENVSET_SH FROM TEMPLATE && ENVSET_SH_TEMPLATE > $ENVSET_SH
[ ! -f "$ENVSET_SH" ] && echo $BASH_SOURCE FAILED TO CREATE ENVSET_SH $ENVSET_SH && exit 10
source $ENVSET_SH

## NB the above does not source the "$ENVSET" just the script that defines ENVSET_NAME and ENVSET
## DONE THIS WAY TO ALLOW RUNNING AN UNCHANGED SCRIPT AGAINST MULTIPLE ENVSET TO MAKE COMPARISONS
## BY EDITING THE ENVSET_SH BETWEEN SUBMISSIONS

path=$(realpath $BASH_SOURCE)
name=$(basename $path)
name=${name/.sh}


fold=$(dirname $path)
relfold=${fold:$(( 1+${#ORIGINAL_HOME} ))}  # assume repo is within ORIGINAL_HOME
relpath=$relfold/$name
tmp=$HOME/tmp/$relpath/${ENVSET_NAME}

export TMP=$tmp


vv="RUNNER ENVSET_SH ENVSET_NAME ENVSET path name fold relfold relpath ORIGINAL_HOME HOME TMP allarg"

allarg="usage info env chk run sub qu qa"
defarg=info_chk_env_run
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

    mkdir -p $TMP
    pushd $TMP

    $RUNNER \
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
    mkdir -p $TMP
    JID=$(sbatch --parsable --chdir $TMP --job-name=$name $BASH_SOURCE info_chk_env_run)
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from sub && exit 3

    echo JID=$JID > $TMP/JID.sh
    echo $BASH_SOURCE submitted $JID - see $TMP/JID.sh
fi

if [ "${arg/qu}" != "$arg" ]; then
    squeue -u $USER
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from qu && exit 4
fi

if [ "${arg/qa}" != "$arg" ]; then
    squeue
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from qa && exit 5
fi

if [ "${arg/tail}" != "$arg" ]; then
    JID_sh=$TMP/JID.sh
    [ -f "$JID_sh" ] && source $JID_sh
    [ -n "$JID" ] && tail -f $TMP/slurm-$JID.out
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from tail JID[$JID] && exit 6
fi

exit 0


