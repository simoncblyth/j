#!/bin/bash -l 

bin=PMTSimParamSvcTest
defarg="build_run_ana"
arg=${1:-$defarg}

sdir=$(pwd)
bdir=/tmp/$USER/j/$(basename $sdir)/build 
idir=/tmp/$USER/j/$(basename $sdir)/install
export FOLD=$idir

echo sdir $sdir
echo bdir $bdir
echo idir $idir
echo FOLD $FOLD


if [ "${arg/build}" != "$arg" ]; then

    rm -rf $bdir && mkdir -p $bdir && cd $bdir && pwd 
    rm -rf $idir && mkdir -p $idir

    cmake $sdir -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$idir 
    [ $? -ne 0 ] && echo $BASH_SOURCE cmake error && exit 1 

    make
    [ $? -ne 0 ] && echo $BASH_SOURCE make error && exit 2 

    make install   
    [ $? -ne 0 ] && echo $BASH_SOURCE install error && exit 3 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    $idir/bin/$bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 4
fi 

if [ "${arg/ana}" != "$arg" ]; then 
    ${IPYTHON:-ipython} --pdb -i $sdir/$bin.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 5 
fi 

exit 0



