#!/bin/bash -l 
usage(){ cat << EOU
ntds.sh
=========

::

    ./ntds.sh grab_evt     # rsync SEvt folders from remote
    ./ntds.sh grab_geom    # rsync CSGFoundry geometry folders from remote
    ./ntds.sh ana          # plotting SEvt 
    ./ntds.sh cf           # chi2 comparison of SEvt histories


    CHECK=all_point ./ntds.sh ana    
    CHECK=few_point ./ntds.sh ana    
    MODE=3 CHECK=few_point ./ntds.sh ana    


    N=0 MODE=3 ./ntds.sh ana




ntds.py
    general analysis comparison of SEvt and plotting  

ntds_cf.py
    chi2 comparison


EOU
}

DIR=$(dirname $BASH_SOURCE)

defarg="ana"
#defarg="cf"
arg=${1:-$defarg}

#check=all_point
#check=few_point
check=sd_point

evt=000
export EVT=${EVT:-$evt}
n=-1  # 0,1,-1
export VERSION="${N:-$n}"


export OPTICKS_MODE=${OPTICKS_MODE:-2}
export SCRIPT=ntds$OPTICKS_MODE
export GEOMDIR=/tmp/$USER/opticks/GEOM
export CHECK=${CHECK:-$check}
export AGEOM=V0J008
export BGEOM=V1J008
export ABASE=$GEOMDIR/$AGEOM/$SCRIPT
export BBASE=$GEOMDIR/$BGEOM/$SCRIPT
export AFOLD=$ABASE/ALL0/$EVT
export BFOLD=$BBASE/ALL1/$EVT

vars="BASH_SOURCE CHECK arg defarg DIR OPTICKS_MODE SCRIPT BASE EVT AGEOM ABASE AFOLD BGEOM BBASE BFOLD N VERSION"
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
elif [ "$arg" == "grab_geom" ]; then 
   for geom in $geoms ; do 
       base=.opticks/GEOM/$geom
       echo rsync geom $geom base $base
       source $OPTICKS_HOME/bin/rsync.sh $base
       [ $? -ne 0 ] && echo $BASH_SOURCE grab_geom error grabbing base $base && exit 2 
   done  
elif [ "$arg" == "ana" ]; then 
    pyscript=$DIR/ntds.py 
elif [ "$arg" == "cf" ]; then
    pyscript=$DIR/ntds_cf.py 
fi

export QLIM=0:10
  
echo $BASH_SOURCE : anascript : $anascript
 
if [ -n "$pyscript"  -a -f "$pyscript" ]; then 
    ${IPYTHON:-ipython} --pdb -i $pyscript
    [ $? -ne 0 ] && echo $BASH_SOURCE pyscript $pyscript error && exit 1
else
    echo $BASH_SOURCE no pyscript for arg $arg 
fi

exit 0 

