#!/bin/bash 

name=${TEST:-JPMTPropTest}

echo $BASH_SOURCE TEST $TEST name $name 

mkdir -p /tmp/$name

defarg="build_run_ana"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then
    gcc $name.cc -std=c++11 -lstdc++ \
         -I$OPTICKS_PREFIX/include/SysRap \
         -I/usr/local/cuda/include \
         -o /tmp/$name/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE gcc error && exit 1 
fi

if [ "${arg/run}" != "$arg" ]; then
    /tmp/$name/$name
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi

exit 0

