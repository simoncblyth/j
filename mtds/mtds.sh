#!/bin/bash -l 
usage(){ cat << EOU
mtds.sh : minimal for checking opticksMode 0 vs 2 differnce
===============================================================

::

    ./mtds.sh grab_evt     # rsync SEvt folders from remote

EOU
}

DIR=$(dirname $BASH_SOURCE)

defarg="ana"
#defarg="cf"
arg=${1:-$defarg}

evt=000

export EVT=${EVT:-$evt}

if [ "$arg" == "cfm" ]; then 
    EVT="%0.3d"
fi 

export VERSION="${N:-$n}"

export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=mtds$OPTICKS_MODE
export GEOMDIR=/tmp/$USER/opticks/GEOM
export AGEOM=mtds0
export BGEOM=mtds2
export ABASE=$GEOMDIR/$AGEOM
export BBASE=$GEOMDIR/$BGEOM
export AFOLD=$ABASE/ALL1/$EVT
export BFOLD=$BBASE/ALL1/$EVT

vars="BASH_SOURCE arg defarg DIR OPTICKS_MODE EVT AGEOM ABASE AFOLD BGEOM BBASE BFOLD N VERSION UBASE"
for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done  

geoms="$AGEOM $BGEOM"
if [ "$arg" == "grab_evt" ]; then 
   for geom in $geoms ; do 
       base=/tmp/$USER/opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_evt error grabbing base $base && exit 2 
   done
elif [ "$arg" == "ana" ]; then 
    pyscript=$DIR/mtds.py 
elif [ "$arg" == "cfm" ]; then 
    pyscript=$DIR/mtds_cfm.py 
fi

  
echo $BASH_SOURCE : anascript : $anascript
 
if [ -n "$pyscript"  -a -f "$pyscript" ]; then 
    ${IPYTHON:-ipython} --pdb -i $pyscript
    [ $? -ne 0 ] && echo $BASH_SOURCE pyscript $pyscript error && exit 1
else
    echo $BASH_SOURCE no pyscript for arg $arg 
fi

exit 0 

