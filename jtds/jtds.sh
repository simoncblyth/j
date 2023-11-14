#!/bin/bash -l 

defarg="info_ana"
arg=${1:-$defarg}

name=jtds
SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
source $HOME/.opticks/GEOM/GEOM.sh 

export BASE=${TMP:-/tmp/$USER/opticks}/GEOM/$GEOM/jok-tds/ALL0
export AFOLD=$BASE/p001
export BFOLD=$BASE/n001
script=$SDIR/$name.py 

vars="BASH_SOURCE arg name SDIR GEOM BASE AFOLD BFOLD script"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/grab}" != "$arg" ]; then 
    source $OPTICKS_HOME/bin/rsync.sh $BASE
fi 

if [ "${arg/ana}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 1 
fi


