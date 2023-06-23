#!/bin/bash -l 

name=StackSpecTest

fold=/tmp/$USER/opticks/$name
export FOLD=$fold
mkdir -p $FOLD 

bin=$FOLD/$name

defarg="info_build_run"
arg=${1:-$defarg}


CUDA_PREFIX=${CUDA_PREFIX:-/usr/local/cuda}

opt="-std=c++11 -I. -I$CUDA_PREFIX/include -I$OPTICKS_PREFIX/include/SysRap"
c4opt="-I$HOME/customgeant4"
linkflags="-lstdc++"

vars="BASH_SOURCE name"

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc $opt $c4opt $linkflags -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2
fi

exit 0 





