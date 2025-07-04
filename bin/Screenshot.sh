#!/usr/bin/env bash
usage(){ cat << EOU
Screenshot.sh
===============

~/j/bin/Screenshot.sh

EOU
}

script=Screenshot.py
cd $(dirname $(realpath $BASH_SOURCE))

defarg="info_pdb"
arg=${1:-$defarg}

export FOLD=$HOME/Screenshot

vv="BASH_SOURCE BASH_VERSION defarg arg PWD script FOLD"

if [ "${arg/info}" != "$arg" ]; then 
    for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/pdb}" != "$arg" ]; then 
   ${IPYTHON:-ipython} --pdb -i $script
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 1
fi 

if [ "${arg/ana}" != "$arg" ]; then 
   ${PYTHON:-python} $script
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 2
fi 

exit 0 
 
