#!/bin/bash -l 

bin=PMTAccessorTest

tmp=/tmp/$bin
log=$tmp/$bin.log
mkdir -p $tmp

export PMTSimParamData_BASE=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData

cd $tmp
$bin

pwd 
echo log $log 
ls -l $log


