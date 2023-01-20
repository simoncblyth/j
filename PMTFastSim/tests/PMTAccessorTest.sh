#!/bin/bash -l 

bin=PMTAccessorTest

iwd=$PWD
export FOLD=/tmp/$bin

defarg="run_ana"
arg=${1:-$defarg}

if [ "${arg/run}" != "$arg" ]; then

    export PMTSimParamData_BASE=$HOME/.opticks/GEOM/${GEOM:-J006}/CSGFoundry/SSim/juno/PMTSimParamData

    rm -rf $FOLD
    mkdir -p $FOLD
    cd $FOLD

    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 1 

    pwd 
    log=$FOLD/$bin.log
    echo log $log 
    ls -l $log
fi

if [ "${arg/ana}" != "$arg" ]; then
    cd $iwd
    ${IPYTHON:-ipython} --pdb -i $bin.py  
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 2
fi 

exit 0 



