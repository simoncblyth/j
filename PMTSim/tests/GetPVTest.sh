#!/bin/bash -l 
usage(){ cat << EOU
GetPVTest.sh 
==================

EOU
}


export PMTSim=1 
bin=GetPVTest
$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run $bin error && exit 1 

exit 0 


