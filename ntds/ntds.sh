#!/bin/bash -l 

DIR=$(dirname $BASH_SOURCE)

export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export EVT=${EVT:-000}

export FOLD=/tmp/blyth/opticks/GEOM/$SCRIPT/ALL/$EVT
anascript=$DIR/ntds.py 

${IPYTHON:-ipython} --pdb -i $anascript
[ $? -ne 0 ] && echo $BASH_SOURCE anascript $anascript error && exit 1

exit 0 


