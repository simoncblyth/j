#!/bin/bash -l 
usage(){ cat << EOU
ntds3.sh
==========

::

    MODE=2 SEL=1 ./ntds3.sh 

EOU
}

name=ntds3
defarg="info_ana"
arg=${1:-$defarg}

source $HOME/.opticks/GEOM/GEOM.sh 
export BASE=/tmp/$USER/opticks/GEOM/$GEOM/ntds3/ALL1
export AFOLD=$BASE/p001
export BFOLD=$BASE/n001

vars="BASH_SOURCE arg GEOM BASE AFOLD BFOLD"


if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $name.py 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 1 
fi

exit 0 

