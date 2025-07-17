#!/bin/bash

usage(){ cat << EOU

~/j/muon/muon_min_sub.sh

EOU
}

RELP=${RELP:-j/muon/muon_min.sh}

STEM=${RELP/.sh}
SCRIPT=$HOME/$RELP
TIMEFOLD=$(date +"%Y%m%d_%H%M%S")

LOGDIR=/hpcfs/juno/junogpu/$USER/logs/$STEM/$TIMEFOLD


if [ -n "$FRESH" ]; then
    echo $BASH_SOURCE : FRESH is defined : trying to reproduce first Opticks usage situation
    ## previously this situation gave error "SNiPER is stopped by Ctrl+C"
    export HOME=/afs/ihep.ac.cn/users/${USER:0:1}/$USER
    rm -rf $HOME/.opticks/scontext
    rm -rf $HOME/.opticks/sdevice
else
    echo $BASH_SOURCE : FRESH is not defined
fi



vv="BASH_SOURCE RELP STEM SCRIPT TIMEFOLD LOGDIR HOME FRESH"

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




