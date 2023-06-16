#!/bin/bash -l 
usage(){ cat << EOU
JPMTTest.sh 
=============


EOU
}

REALDIR=$(cd $(dirname $BASH_SOURCE) && pwd)

name=${TEST:-JPMTTest}
echo $BASH_SOURCE TEST $TEST name $name 

mkdir -p /tmp/$name
bin=/tmp/$name/$name 

defarg="build_run_ana"
arg=${1:-$defarg}

vars="REALDIR PWD name FOLD"

if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then

    opt="-DWITH_STACKSPEC"
    gcc $REALDIR/$name.cc \
         $opt -std=c++11 -lstdc++ \
         -I$OPTICKS_PREFIX/include/SysRap \
         -I$HOME/customgeant4 \
         -I/usr/local/cuda/include \
         -o $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE gcc error && exit 1 
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $REALDIR/$name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi

exit 0

