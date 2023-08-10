#!/bin/bash -l 
usage(){ cat << EOU
GetLVTest.sh 
==================

EOU
}


export PMTSim=1 


geom=nnvtLogicalPMT
#geom=tub3LogicalPMT

export GEOM=${GEOM:-$geom}

bin=GetLVTest
$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run $bin error && exit 1 

exit 0 


