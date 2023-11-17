#!/bin/bash -l 

defarg="info_ana"
arg=${1:-$defarg}

name=jtds
SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
source $HOME/.opticks/GEOM/GEOM.sh 

export REMOTE=${REMOTE:-L}
export L_TMP=/hpcfs/juno/junogpu/blyth/tmp
export P_TMP=/data/blyth/opticks 

TMPVAR=${REMOTE}_TMP
export TMP=${!TMPVAR}

export BASE=${TMP:-/tmp/$USER/opticks}/GEOM/$GEOM/jok-tds/ALL0

export AFOLD=$BASE/p001
export BFOLD=$BASE/n001
script=$SDIR/$name.py 

vars="BASH_SOURCE REMOTE L_TMP P_TMP TMPVAR TMP arg name SDIR GEOM BASE AFOLD BFOLD script"

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


