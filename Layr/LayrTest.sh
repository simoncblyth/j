#!/bin/bash -l 
usage(){ cat << EOU
LayrTest.sh
=============

SysRap lib only needed for WITH_THRUST GPU running 
by the NP.hh header is needed in both cases

EOU
}

name="LayrTest"

defarg=build_run_ana
arg=${1:-$defarg}

opt="-std=c++11 -I. -I/usr/local/cuda/include -I$OPTICKS_PREFIX/include/SysRap"
linkflags="-lstdc++"

WITH_THRUST=1  # comment for CPU only test

if [ -n "$WITH_THRUST" ]; then 
    opt="$opt -DWITH_THRUST"
    linkflags="$linkflags -L$OPTICKS_PREFIX/lib -lSysRap"
    echo $BASH_SOURCE : WITH_THRUST config  
else
    echo $BASH_SOURCE : not WITH_THRUST config 
fi


fold=/tmp/$USER/opticks/$name
export LAYRTEST_BASE=$fold


if [ "${arg/clean}" != "$arg" ]; then
    rm -rf $fold
fi 

if [ "${arg/build}" != "$arg" ]; then

    mkdir -p $fold
    if [ "${opt/WITH_THRUST}" != "$opt" ]; then

        cmds=( "gcc  -c $name.cc $opt -o $fold/$name.o"
               "nvcc -c $name.cu $opt -o $fold/${name}_cu.o"
               "nvcc -o $fold/$name $linkflags $fold/$name.o $fold/${name}_cu.o " 
               "rm $fold/$name.o $fold/${name}_cu.o "
            )
    else
        cmds=( "gcc   $name.cc $opt $linkflags -o  $fold/$name" )
    fi 

    for cmd in "${cmds[@]}"; do
        echo "$cmd"
        eval "$cmd" 
        [ $? -ne 0 ] && echo $BASH_SOURCE :  error with : $cmd  && exit 1
    done
fi

if [ "${arg/run}" != "$arg" ]; then
    $fold/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 

exit 0 

