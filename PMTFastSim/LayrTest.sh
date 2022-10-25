#!/bin/bash -l 

usage(){ cat << EOU


EOU
}

name="LayrTest"
defarg=build_run_ana
arg=${1:-$defarg}

opt="-std=c++11 -I. -I/usr/local/cuda/include -I$OPTICKS_PREFIX/include/SysRap -DWITH_THRUST"
linkflags="-lstdc++ -L$OPTICKS_PREFIX/lib -lSysRap"

mkdir -p /tmp/$name 


if [ "${arg/build}" != "$arg" ]; then

    cmd="gcc -c $name.cc $opt -o  /tmp/$name/$name.o"
    echo $cmd
    eval $cmd 
    [ $? -ne 0 ] && echo $BASH_SOURCE : gcc $name error && exit 1

    cmd="nvcc -c $name.cu $opt -o /tmp/$name/${name}_cu.o"
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc ${name}_cu error  && exit 2

    cmd="nvcc -o /tmp/$name/$name $linkflags /tmp/$name/$name.o /tmp/$name/${name}_cu.o "
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc link error  && exit 3
fi

if [ "${arg/simple}" != "$arg" ]; then

    cmd="nvcc $name.cu $opt $linkflags  -DWITH_CUDA_LAUNCH_MAIN -o /tmp/$name/${name}_simple"
    echo $cmd
    eval $cmd
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc simple build error  && exit 4

    /tmp/$name/${name}_simple
    [ $? -ne 0 ] && echo $BASH_SOURCE : nvcc simple run error  && exit 5
fi 



if [ "${arg/run}" != "$arg" ]; then
    /tmp/$name/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i LayrTest.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 


exit 0 

