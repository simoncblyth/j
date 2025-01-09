#!/bin/bash 
usage(){ cat << EOU
~/j/jtds/jtds.sh
==================

::

   ~/j/jtds/jtds.sh info

   REMOTE=P ~/j/jtds/jtds.sh grab
   REMOTE=L ~/j/jtds/jtds.sh grab
   ~/j/jtds/jtds.sh grab

   ~/j/jtds/jtds.sh ana
   EVT=2 ~/j/jtds/jtds.sh ana
   EVT=9 ~/j/jtds/jtds.sh ana

EOU
}

defarg="info_pdb"
arg=${1:-$defarg}

name=jtds
SDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
source $HOME/.opticks/GEOM/GEOM.sh 

reldir=ALL0_Debug_Philox

export BASE=${TMP:-/tmp/$USER/opticks}/GEOM/$GEOM/jok-tds/$reldir

EVT=${EVT:-000}
export AFOLD=$BASE/A$EVT
export BFOLD=$BASE/B$EVT
script=$SDIR/$name.py 

vars="BASH_SOURCE TMP arg name SDIR GEOM BASE EVT evt AFOLD BFOLD script"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/scpmeta}" != "$arg" ]; then 
    txts="run_meta.txt SEvt__EndOfRun_SProf.txt"
    for txt in $txts ; do
        scp P:$BASE/$txt $BASE/$txt
    done
fi 

if [ "${arg/grab}" != "$arg" ]; then 
    source $OPTICKS_HOME/bin/rsync.sh $BASE
fi 


if [ "${arg/pdb}" != "$arg" ]; then
   ${IPYTHON:-ipython} --pdb -i $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE pdb error && exit 1 
fi

if [ "${arg/ana}" != "$arg" ]; then
   ${PYTHON:-python} $script 
   [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 2 
fi


