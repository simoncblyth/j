#!/bin/bash
usage(){ cat << EOU
run_simple.sh
==============

Do not include anything related to batch systems
or environment setup in this script for simplicity 
and to facilitate:

1. simple local testing of a commandline
2. submission of same commandline to multiple batch systems
3. submission of same commandline in multiple release environments

Usage::

    ./run_simple.sh <basedir:$PWD> <seed:42>

Output directory is::

     <basedir>/<seed>

EOU
}

BASEDIR="${1:-$PWD}"
SEED=${2:-42}
OUTDIR="$BASEDIR/$SEED"

mkdir -p "$OUTDIR"
cd "$OUTDIR"
   
vv="BASH_SOURCE PWD BASEDIR SEED OUTDIR"
for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
 
tut_detsim.py \
   --output oj_edm.root \
   --user-output oj_user.root \
   --evtmax 1 \
   --seed $SEED \
   gun \
   --momentums 1.0

 
