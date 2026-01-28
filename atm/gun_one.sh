#!/bin/bash
usage(){ cat << EOU
gun_one.sh
=============

Do not include anything related to batch systems other than the expedient
SLURM_PROCID SLURM_ARRAY_TASK_ID which safely default to zero when not defined.
Also do not fiddle with environment other than for temporary testing.

Following these will facilitate:

1. running commandline locally
2. submission of same commandline to multiple batch systems
3. submission of same commandline in multiple release environments

Usage for local testing on a GPU workstation::

    ./atm/gun_one.sh <basedir:$PWD> <seed_base:42>

Output directory is::

     <basedir>/<seed_offset>

EOU
}

export BASEDIR="${1:-$PWD}"
export SEED_OFFSET=$(( SLURM_ARRAY_TASK_ID * 10 + SLURM_PROCID ))    ## matches the %a%t in wrapper for t < 10
export OUTDIR="$BASEDIR/$SEED_OFFSET"

export SEED_BASE=${2:-42}
export SEED=$(( SEED_BASE + SEED_OFFSET ))


mkdir -p "$OUTDIR"
cd "$OUTDIR"

vv="BASH_SOURCE PWD BASEDIR SEED_BASE SLURM_ARRAY_TASK_ID SLURM_PROCID SEED_OFFSET SEED OUTDIR"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done

#export OPTICKS_MAX_BOUNCE=31
#export OPTICKS_EVENT_MODE=Minimal


env > env.log

tut_detsim.py \
   --output oj_edm.root \
   --user-output oj_user.root \
   --evtmax 1 \
   --seed $SEED \
   gun \
   --momentums 1.0


