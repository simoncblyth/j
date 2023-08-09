#!/bin/bash -l 
usage(){ cat << EOU
ntds3.sh
==========

::

    ~/j/ntds/ntds3.sh info

    PICK=AB MODE=2 SEL=1 ~/j/ntds/ntds3.sh 
    PICK=AB MODE=3 SEL=1 ~/j/ntds/ntds3.sh 


EOU
}

defarg="info_ana"
arg=${1:-$defarg}

name=ntds3
SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
source $HOME/.opticks/GEOM/GEOM.sh 
export BASE=/tmp/$USER/opticks/GEOM/$GEOM/ntds3/ALL1
export AFOLD=$BASE/p001
export BFOLD=$BASE/n001
script=$SDIR/$name.py 

vars="BASH_SOURCE arg name SDIR GEOM BASE AFOLD BFOLD script"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 1 
fi

exit 0 

