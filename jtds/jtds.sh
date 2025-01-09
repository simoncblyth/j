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

vars=""
vars="$vars BASH_SOURCE defarg arg name SDIR"

geom_sh=$HOME/.opticks/GEOM/GEOM.sh
if [ -z "$GEOM" -a -f $geom_sh ]; then
    source $geom_sh 
fi
[ -z "$GEOM" ] && GEOM_NOTE="GEOM not defined : use GEOM bash function to set it eg to j_2025jan08 "
vars="$vars geom_sh GEOM GEOM_NOTE"

ctx_sh=$HOME/.opticks/CTX/CTX.sh
if [ -z "$CTX" -a -f $ctx_sh ]; then
    source $ctx_sh
fi
[ -z "$CTX" ] && CTX_NOTE="CTX not defined : use CTX bash function to set it eg to ALL0_Debug_Philox "
vars="$vars ctx_sh CTX CTX_NOTE"

test_sh=$HOME/.opticks/TEST/TEST.sh
if [ -z "$TEST" -a -f $test_sh ]; then
    source $test_sh
fi
[ -z "$TEST" ] && TEST_NOTE="TEST not defined : use TEST bash function to set it eg to GUN1 "
vars="$vars test_sh TEST TEST_NOTE"

reldir=${CTX}_${TEST}
export BASE=${TMP:-/tmp/$USER/opticks}/GEOM/$GEOM/jok-tds/$reldir
vars="$vars reldir BASE"

EVT=${EVT:-000}
export AFOLD=$BASE/A$EVT
export BFOLD=$BASE/B$EVT
script=$SDIR/$name.py 

vars="$vars EVT AFOLD BFOLD script"

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


