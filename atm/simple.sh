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

    squeue -u \$USER   # list jobs from USER

    scontrol show job \$JID  # show details of one job

    sstat -j \$JID --format=JobId,MaxRSS,AveCPU,MaxDiskRead  # show what the job is doing

    tail -f slurm-\$JID.out   # follow output from tail of the job log

    scancel \$JID  # cancel a job if tail of log shows issue


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
    RUNNER="srun --export=ALL"

    ## When use "sbatch --export=NONE" for cleanliness/reproducibility
    ## at the higher batch submission level it becomes necessary to let the
    ## isolated environment setup by the script thru to the srun executable
    ## including finding that executable with this "srun --export=ALL".
else
    RUNNER=""
fi




ENVSET_SH=$HOME/ENVSET.sh
ENVSET_SH_TEMPLATE(){  cat << EOT

# NB this defines ENVSET pointing to the environment script based on envset_name
# it does not source that

#envset_arg=OJ_058
#envset_arg=OJ_059
envset_arg=OJ_LLL

case \$envset_arg in
  OJ_058)  envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.5.8/el9_amd64_gcc11/2026_01_18/envset.sh ;;
  OJ_059)  envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/J25.7.2_Opticks-v0.5.9/el9_amd64_gcc11/2026_01_26/envset.sh ;;
  OJ_LLL)  envset=/cvmfs/opticks.ihep.ac.cn/oj/releases/LatestRelease/el9_amd64_gcc11/LastRef/envset.sh ;;
  OJ_000)  envset=\$HOME/junosw/InstallArea/main/envset.sh  ;;
esac

envset=\$(realpath \$envset)  # resolve symbolic links within the path


if [ "\$envset_arg" == "OJ_000" ]; then
   envset_name=OJ_000_\$(date -r \$envset  '+%b%d')
elif [ "\$envset_arg" == "OJ_LLL" ]; then
   version=\$(echo \$envset | sed -E 's|.*-v([0-9.]+)/.*|\1|' | sed 's/\.//g') # extract version digits eg "059"
   envset_name=OJ_\${version}
else
   envset_name=\$envset_arg
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


if [ -n "$SCRIPT_SOURCE" ]; then
    path=$SCRIPT_SOURCE
else
    path=$(realpath $BASH_SOURCE)
fi

name=$(basename $path)
name=${name%.sh}  # remove .sh from end of string

fold=$(dirname $path)
export SCRIPT=$fold/run_simple.sh

relfold=${fold:$(( 1+${#ORIGINAL_HOME} ))}  # assume repo is within ORIGINAL_HOME
relpath=$relfold/$name
tmp=$HOME/tmp/$relpath/${ENVSET_NAME}

export TMP=$tmp

vv="RUNNER ENVSET_SH ENVSET_NAME ENVSET BASH_SOURCE SCRIPT_SOURCE PWD path name fold SCRIPT relfold relpath ORIGINAL_HOME HOME TMP allarg stdarg defarg arg"
vv="$vv SLURM_JOB_ID SLURM_ARRAY_JOB_ID SLURM_ARRAY_TASK_ID SLURM_PROCID"

allarg="usage info env chk pyc run sub tail interact qu qa ls"
stdarg=info_chk_env_info_run
#defarg=info
defarg=$stdarg
arg=${1:-$defarg}

if [ "${arg/usage}" != "$arg" ]; then
   usage
fi

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do  printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/env}" != "$arg" ]; then

    [ -n "$SLURM_JOB_ID" ] && env > env-env0-${SLURM_JOB_ID}.txt

    source $ENVSET

    #export CUDA_VISIBLE_DEVICES=0
    #export OPTICKS_MAX_BOUNCE=31
    #export OPTICKS_EVENT_MODE=Minimal

    [ -n "$SLURM_JOB_ID" ] &&                       env > env-env1-${SLURM_JOB_ID}.txt
    [ -n "$SLURM_JOB_ID" ] && srun --export=ALL -n1 env > env-env2-${SLURM_JOB_ID}.txt
    # above lines allow to compare environment of the sbatch and srun processes

   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from env && exit 1
fi

if [ "${arg/chk}" != "$arg" ]; then
    lscpu
    nvidia-smi
fi

if [ "${arg/pyc}" != "$arg" ]; then
    echo $PATH | tr ":" "\n"
    python -c "from Tutorial import JUNODetSimModule"
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from pyc && exit 2
fi

if [ "${arg/run}" != "$arg" ]; then
    BASE_SEED=1000
    srun --export=ALL "$SCRIPT" "$TMP"  $(( BASE_SEED + (SLURM_ARRAY_TASK_ID * 8) + SLURM_PROCID ))
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from run && exit 2
fi

if [ "${arg/sub}" != "$arg" ]; then
    mkdir -p $TMP
    JID=$(sbatch --parsable --chdir $TMP --job-name=$name --export=NONE,SCRIPT_SOURCE=$(realpath $BASH_SOURCE) $BASH_SOURCE $stdarg)
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from sub && exit 3

    echo JID=$JID > $TMP/JID.sh
    echo $BASH_SOURCE submitted $JID - see $TMP/JID.sh
fi

if [ "${arg/tail}" != "$arg" ]; then
    JID_sh=$TMP/JID.sh
    [ -f "$JID_sh" ] && source $JID_sh
    [ -n "$JID" ] && tail -f $TMP/slurm-$JID.out
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from tail JID[$JID] && exit 6
fi

if [ "${arg/interact}" != "$arg" ]; then
    ## workaround lack of ssh access to GPU cluster
    JID_sh=$TMP/JID.sh
    [ -f "$JID_sh" ] && source $JID_sh
    [ -n "$JID" ] && srun --jobid $JID --interact --pty bash
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from tail JID[$JID] && exit 6

    # nvidia-smi dmon -s utp
fi

if [ "${arg/qu}" != "$arg" ]; then
    squeue -u $USER
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from qu && exit 4
fi

if [ "${arg/qa}" != "$arg" ]; then
    squeue
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from qa && exit 5
fi

if [ "${arg/ls}" != "$arg" ]; then
    date
    echo ls -alst $TMP
    ls -alst $TMP
fi

exit 0


