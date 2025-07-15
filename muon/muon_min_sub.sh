#!/bin/bash 

usage(){ cat << EOU

~/j/muon/muon_min_sub.sh

EOU
}

RELP=${RELP:-j/muon/muon_min.sh}

STEM=${RELP/.sh}
SCRIPT=$HOME/$RELP
LOGDIR=/hpcfs/juno/junogpu/$USER/logs/$STEM

vv="BASH_SOURCE RELP STEM SCRIPT LOGDIR"

defarg="info_sub"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/sub}" != "$arg" ]; then
   mkdir -p $LOGDIR
   cd $LOGDIR
   sbatch $SCRIPT
fi

if [ "${arg/ls}" != "$arg" ]; then
   mkdir -p $LOGDIR
   ls -alst $LOGDIR
fi




