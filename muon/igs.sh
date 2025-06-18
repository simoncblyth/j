#!/usr/bin/env bash 


cd $(dirname $(realpath $BASH_SOURCE))
name=igs
script=$name.py

defarg=info_pdb
arg=${1:-$defarg}

vv="BASH_SOURCE PWD name script defarg arg IGS_PATH"

#export IGS_PATH=$TMP/.opticks/igs.npy
export IGS_PATH=$HOME/.opticks/crash_muon_igs.npy
export IGS_IDX=8259,8260,8261

if [ "${arg/info}" != "$arg" ]; then
    for v in $vv ; do printf "%20s : %s\n" "$v" "${!v}" ; done
fi 

if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 1 
fi

