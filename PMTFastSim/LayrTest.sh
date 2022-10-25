#!/bin/bash -l 

usage(){ cat << EOU
LayrTest.sh
=============


EOU
}

name="LayrTest"

defarg=clean_build_run_ana
arg=${1:-$defarg}
opt="-std=c++11 -I. -I/usr/local/cuda/include -I$OPTICKS_PREFIX/include/SysRap -DWITH_THRUST"
linkflags="-lstdc++ -L$OPTICKS_PREFIX/lib -lSysRap"

fold=/tmp/$USER/opticks/$name
export LAYRTEST_BASE=$fold


if [ "${arg/clean}" != "$arg" ]; then
    rm -rf $fold
fi 

if [ "${arg/build}" != "$arg" ]; then

    mkdir -p $fold
    cmd="gcc -c $name.cc $opt -o  $fold/$name.o"
    echo $cmd
    eval $cmd 
    [ $? -ne 0 ] && echo $BASH_SOURCE : gcc $name error && exit 1

    cmd="nvcc -c $name.cu $opt -o $fold/${name}_cu.o"
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc ${name}_cu error  && exit 2

    cmd="nvcc -o $fold/$name $linkflags $fold/$name.o $fold/${name}_cu.o "
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc link error  && exit 3
fi

if [ "${arg/run}" != "$arg" ]; then
    $fold/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i LayrTest.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 

exit 0 

