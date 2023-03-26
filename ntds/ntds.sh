#!/bin/bash -l 

defarg="ana"
arg=${1:-$defarg}

DIR=$(dirname $BASH_SOURCE)
anascript=$DIR/ntds.py 

export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export EVT=${EVT:-000}
export BASE=/tmp/$USER/opticks/GEOM/$SCRIPT/ALL
export FOLD=$BASE/$EVT

if [ "${arg/grab}" != "$arg" ]; then 
   source $OPTICKS_HOME/bin/rsync.sh $BASE 
   [ $? -ne 0 ] && echo $BASH_SOURCE grab error && exit 1 
fi 

export QLIM=0:20

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $anascript
    [ $? -ne 0 ] && echo $BASH_SOURCE anascript $anascript error && exit 1
fi

exit 0 

