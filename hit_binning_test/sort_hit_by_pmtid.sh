#!/bin/bash

usage(){ cat << EOU

~/j/hit_binning_test/sort_hit_by_pmtid.sh

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

name=sort_hit_by_pmtid

tmp=/tmp/$USER/opticks
TMP=${TMP:-$tmp}

FOLD=$TMP/$name
mkdir -p $FOLD

bin=$FOLD/$name

defarg="info_build_run"
arg=${1:-$defarg}

vv="BASH_SOURCE name PWD tmp TMP FOLD HITFOLD"

if [ "${arg/info}" != "$arg" ];  then
    for v in $vv ; do printf "%30s : %s \n" "$v" "${!v}" ; done
fi

if [ "${arg/build}" != "$arg" ];  then
    nvcc $name.cu -o $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE - build error && exit 1 
fi

if [ "${arg/run}" != "$arg" ];  then
    $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE - run error && exit 2 
fi

exit 0

