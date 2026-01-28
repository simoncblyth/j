#!/bin/bash

#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --wait-all-nodes=1

usage(){ cat << EOH
slurm.sh
=========

SCRIPTNAME : $SCRIPTNAME
BASE_TMP   : $BASE_TMP
BASE_SEED  : $BASE_SEED


This wrapper script handles only slurm details.
The \${SCRIPTNAME}.sh scripts that this wrapper invokes
handles commandline details, processing options etc..


$BASH_SOURCE usage
    this usage message

$BASH_SOURCE info
    emit the values of variables including output directories
    [this is the default action when no argument is provided]

$BASH_SOURCE info_chk_env_run
    perform sequence of actions

$BASH_SOURCE sub
    submit using sbatch this wrapper script to slurm with argument
    "info_chk_env_info_run" which performs those actions

$BASH_SOURCE run
    invokes \${SCRIPTNAME}.sh via srun with arguments::

          \${SCRIPTNAME}.sh \$BASE_TMP \$BASE_SEED

    The invoked script is expected to be a sibling
    to this wrapper script

$BASH_SOURCE qu
    list slurm jobs of \$USER

$BASH_SOURCE qa
    list all slurm jobs

$BASH_SOURCE ls
    list output directory for \${SCRIPTNAME}.sh

$BASH_SOURCE tail
    follow the sbatch top level log. detailed logging
    is within task folders



Some commands to query and control a slurm job::

    U[blyth@lxlogin004 j]$ atm/slurm.sh sub
    Submitted batch job 2934490

    U[blyth@lxlogin004 j]$ JID=2934490

    squeue -u \$USER   # list jobs from USER

    scontrol show job \$JID  # show details of one job

    sstat -j \$JID --format=JobId,MaxRSS,AveCPU,MaxDiskRead  # show what the job is doing

    tail -f sbatch-\$JID.out   # follow output from tail of the job log

    scancel \$JID  # cancel a job if tail of log shows issue


When use "sbatch --export=NONE" for cleanliness/reproducibility
at the higher sbatch submission level it becomes necessary to let the
isolated environment setup by the script thru to the srun executable
including finding that executable with "srun --export=ALL".

EOH
}


if [ -n "$SCRIPT_SOURCE" ]; then
    path=$SCRIPT_SOURCE
else
    path=$(realpath $BASH_SOURCE)
fi

vv=""
vv="$vv PWD"
vv="$vv BASH_SOURCE SCRIPT_SOURCE path"


fold=$(dirname $path)
name=$(basename $path)
name=${name%.sh}  # remove .sh from end of string

vv="$vv fold name"

base_seed=3000
export BASE_SEED=${BASE_SEED:-$base_seed}
vv="$vv base_seed BASE_SEED"

scriptname=gun_one
export SCRIPTNAME=${SCRIPTNAME:-$scriptname}

export SCRIPT=$fold/$SCRIPTNAME.sh
vv="$vv scriptname SCRIPTNAME SCRIPT"


ORIGINAL_HOME=$HOME
JUNOGPU=/hpcfs/juno/junogpu

if [ -d "$JUNOGPU" ]; then
    home=$JUNOGPU/$USER
    export HOME=$home    # redefining HOME on lxlogin avoids AFS token complications
fi

vv="$vv ORIGINAL_HOME HOME JUNOGPU"


relfold=${fold:$(( 1+${#ORIGINAL_HOME} ))}  # assume repo is within ORIGINAL_HOME
relpath=$relfold/$scriptname
vv="$vv relfold relpath"


ENVSET_sh=$HOME/ENVSET.sh
ENVSET_sh_TEMPLATE(){  cat << EOT

# NB this defines ENVSET pointing to the environment script based on envset_name
# it does not source that
#
# DONE THIS WAY TO ALLOW RUNNING AN UNCHANGED SCRIPT AGAINST MULTIPLE ENVSET TO MAKE COMPARISONS
# BY EDITING THE ENVSET_SH BETWEEN SUBMISSIONS

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

[ ! -f "$ENVSET_sh" ] && echo $BASH_SOURCE CREATING ENVSET_sh $ENVSET_sh FROM TEMPLATE && ENVSET_sh_TEMPLATE > $ENVSET_sh
[ ! -f "$ENVSET_sh" ] && echo $BASH_SOURCE FAILED TO CREATE ENVSET_sh $ENVSET_sh && exit 10

source $ENVSET_sh

vv="$vv ENVSET_sh ENVSET_NAME ENVSET"

base_tmp=$HOME/tmp/$relpath/${ENVSET_NAME}/$BASE_SEED
export BASE_TMP=$base_tmp
mkdir -p $BASE_TMP

export JID_sh=$BASE_TMP/JID.sh
vv="$vv base_tmp BASE_TMP JID_sh"

allarg="usage info env chk run sub tail interact qu qa ls"
defarg=info
arg=${1:-$defarg}

vv="$vv allarg defarg arg"
vv="$vv SLURM_JOB_ID SLURM_ARRAY_JOB_ID SLURM_ARRAY_TASK_ID SLURM_PROCID"

log(){ echo $BASH_SOURCE.$1 at $(date) on $(hostname) ; }


if [ "${arg/usage}" != "$arg" ]; then
   usage
fi

if [ "${arg/info}" != "$arg" ]; then
   log "info.["
   for v in $vv ; do  printf "%30s : %s\n" "$v" "${!v}" ; done
   log "info.]"
fi

if [ "${arg/env}" != "$arg" ]; then
   log "env.["
   source $ENVSET
   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from env && exit 1
   log "env.]"
fi

if [ "${arg/chk}" != "$arg" ]; then
   log "chk.["
   lscpu
   nvidia-smi
   log "chk.]"
fi

if [ "${arg/sub}" != "$arg" ]; then
   log "sub.["
   SCRIPT_SOURCE=$path
   JID=$(sbatch \
             --output="$BASE_TMP/sbatch-%j.out" \
             --parsable \
             --chdir $BASE_TMP \
             --job-name=$SCRIPTNAME \
             --export=NONE,SCRIPT_SOURCE=$path \
             $path \
             info_chk_env_info_run)

   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from sub && exit 3
   [ -n "$JID_sh" -a -n "$JID" ] && echo JID=$JID > $JID_sh
   echo $BASH_SOURCE submitted $JID - see JID_sh $JID_sh
   log "sub.]"
fi

if [ "${arg/sleep}" != "$arg" ]; then
   sleep 1
fi

if [ "${arg/run}" != "$arg" ]; then
   : %t corresponds to SLURM_PROCID task index
   log "run.["
   srun --export=ALL \
        --output="$BASE_TMP/%t/srun.log" \
        "$SCRIPT" \
        "$BASE_TMP" \
        "$BASE_SEED"

   [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from run && exit 2
   log "run.]"
fi

if [ "${arg/tail}" != "$arg" ]; then
    [ -f "$JID_sh" ] && source $JID_sh
    [ -n "$JID" ] && tail -f $BASE_TMP/sbatch-$JID.out
    [ $? -ne 0 ] && echo $BASH_SOURCE ERROR from tail JID[$JID] && exit 6
fi

if [ "${arg/interact}" != "$arg" ]; then
    : enables interactive examination on the job node only during job execution
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
    echo ls -alst $BASE_TMP
    ls -alst $BASE_TMP
    for t in $(seq 0 7) ; do
      if [ -d "$BASE_TMP/$t" ]; then
         echo ls -alst $BASE_TMP/$t
         ls -alst $BASE_TMP/$t
      fi
    done
fi

exit 0

