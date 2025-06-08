#!/bin/bash
usage(){ cat << EOU
testOpticksMode.sh
====================

~/j/opticksMode/testOpticksMode.sh 

::

    tom(){ ~/j/opticksMode/testOpticksMode.sh $* ; }


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

BASE=$(basename $BASH_SOURCE)
STEM=${BASE/.sh}
vv="BASH_SOURCE PWD BASE STEM"

defarg="env_info_run"
arg=${1:-$defarg}

if [ "${arg/env}" != "$arg" ]; then

   echo [ $BASE env 

   source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.3/el9_amd64_gcc11/Sun/envset.sh
   #source /home/blyth/junosw/InstallArea/envset.sh
   unset OJ_VERBOSE

   export OPTICKS_INTEGRATION_MODE=3

   ## what and where to output 
   export OPTICKS_EVENT_MODE=DebugLite
   export OPTICKS_SCRIPT=$STEM
   export OPTICKS_EVENT_NAME=DebugPhilox_${OPTICKS_INTEGRATION_MODE}
   export VERSION=0
   export LOGDIR=$TMP/GEOM/$GEOM/$OPTICKS_SCRIPT/ALL${VERSION}_${OPTICKS_EVENT_NAME}
   vv="$vv OPTICKS_INTEGRATION_MODE OPTICKS_EVENT_MODE OPTICKS_SCRIPT OPTICKS_EVENT_NAME VERSION LOGDIR"

   export OPTICKS_MAX_BOUNCE=31
   vv="$vv OPTICKS_MAX_BOUNCE"

   mkdir -p $LOGDIR
   echo ] $BASE env 
fi 

if [ "${arg/info}" != "$arg" ]; then
   echo [ $BASE info
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
   echo ] $BASE info
fi 

if [ "${arg/run}" != "$arg" ]; then

   echo [ $BASE run
   cd $LOGDIR
   source dbg__.sh
   dbg__ \
    $(which python) \
    $(which tut_detsim.py) \
    --output oj_edm.root \
    --user-output oj_user.root \
    --evtmax 1 \
    --seed 42 \
    --opticks-mode $OPTICKS_INTEGRATION_MODE \
    gun \
    --momentums 1.0;

   rc=$?

   echo ] $BASE run rc $rc
fi
