#!/bin/bash -l 

usage(){ cat << EOU
GetSolidTest.sh 
==================


EOU
}




source $HOME/.opticks/GEOM/GEOM.sh 

export PMTSim=1 
bin=GetSolidTest

$bin
[ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 1 


exit 0 


