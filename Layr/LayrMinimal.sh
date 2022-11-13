#!/bin/bash -l 

name=LayrMinimal 

mct=-1
export MCT=${MCT:-$mct}

mode="hama"
#mode="hama_no_abs"
#mode="thick"

export MODE=${MODE:-$mode}

if [ "$MODE"  == "hama" ]; then

l0=1.482,0,0
l1=1.92,0,36.49
l2=2.429,1.366,21.13
l3=1,0,0

elif [ "$MODE" == "hama_no_abs" ]; then

l0=1.482,0,0
l1=1.92,0,36.49
l2=2.429,0,21.13
l3=1,0,0

elif [ "$MODE" == "thick" ]; then

l0=1.482,0,0
l1=1.92,0,0
l2=2.429,0,0
l3=1,0,0

fi 



export L0=${L0:-$l0}
export L1=${L1:-$l1}
export L2=${L2:-$l2}
export L3=${L3:-$l3}

defarg="build_run"
arg=${1:-$defarg}

if [ "${arg/build}" != "$arg" ]; then 
    gcc $name.cc -std=c++11 -lstdc++ -I. -I/usr/local/cuda/include  -o /tmp/$name 
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then 
    /tmp/$name $MCT
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi 

exit 0 

