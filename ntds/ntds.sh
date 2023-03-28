#!/bin/bash -l 

#defarg="ana"
defarg="cf"
arg=${1:-$defarg}

DIR=$(dirname $BASH_SOURCE)

evt=000
export EVT=${EVT:-$evt}
n=-1  # 0,1,-1
export VERSION="${N:-$n}"
export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export GEOMDIR=/tmp/$USER/opticks/GEOM

export AGEOM=V0J008
export BGEOM=V1J008
export ABASE=$GEOMDIR/$AGEOM/$SCRIPT
export BBASE=$GEOMDIR/$BGEOM/$SCRIPT
export AFOLD=$ABASE/ALL0/$EVT
export BFOLD=$BBASE/ALL1/$EVT

vars="BASH_SOURCE arg defarg DIR OPTICKS_MODE SCRIPT BASE EVT AGEOM ABASE AFOLD BGEOM BBASE BFOLD N VERSION"
for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  

case $VERSION in 
   -1) echo $BASH_SOURCE VERSION:$VERSION load both AFOLD and BFOLD  ;;
    0) echo $BASH_SOURCE VERSION:$VERSION load only AFOLD $AFOLD ;; 
    1) echo $BASH_SOURCE VERSION:$VERSION load only BFOLD $BFOLD ;; 
esac



geoms="$AGEOM $BGEOM"

if [ "$arg" == "grab_evt" ]; then 
   for geom in $geoms ; do 
       base=/tmp/$USER/opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_evt error grabbing base $base && exit 2 
   done
fi

if [ "$arg" == "grab_geom" ]; then 
   for geom in $geoms ; do 
       base=.opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_geom error grabbing base $base && exit 2 
   done  
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

