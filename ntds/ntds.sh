#!/bin/bash -l 

#defarg="ana"
defarg="cf"
arg=${1:-$defarg}

DIR=$(dirname $BASH_SOURCE)

export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export BASE=/tmp/$USER/opticks/GEOM/$SCRIPT

evt=000
#n=0  
#n=1 
n=-1

export VERSION="${N:-$n}"
export EVT=${EVT:-$evt}
export AFOLD=$BASE/ALL0/$EVT
export BFOLD=$BASE/ALL1/$EVT

vars="BASH_SOURCE arg defarg DIR OPTICKS_MODE SCRIPT BASE EVT AFOLD BFOLD N VERSION"
for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  

case $VERSION in 
   -1) echo $BASH_SOURCE VERSION:$VERSION load both AFOLD and BFOLD  ;;
    0) echo $BASH_SOURCE VERSION:$VERSION load only AFOLD $AFOLD ;; 
    1) echo $BASH_SOURCE VERSION:$VERSION load only BFOLD $BFOLD ;; 
esac


if [ "${arg/grab}" != "$arg" ]; then 
   source $OPTICKS_HOME/bin/rsync.sh $BASE 
   [ $? -ne 0 ] && echo $BASH_SOURCE grab error && exit 1 
fi 



if [ "${arg/ana}" != "$arg" ]; then 
    anascript=$DIR/ntds.py 
elif [ "${arg/cf}" != "$arg" ]; then
    anascript=$DIR/ntds_cf.py 
fi

export QLIM=0:10
   
if [ -f "$anascript" ]; then 
    ${IPYTHON:-ipython} --pdb -i $anascript
    [ $? -ne 0 ] && echo $BASH_SOURCE anascript $anascript error && exit 1
else
    echo $BASH_SOURCE no anascript for arg $arg 
fi

exit 0 

