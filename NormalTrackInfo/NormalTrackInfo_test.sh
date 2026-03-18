#!/bin/bash 
usage(){ cat << EOU

~/junosw/Simulation/DetSimV2/SimUtil/tests/NormalTrackInfo_test.sh

EOU
}


cd $(dirname $(realpath $BASH_SOURCE))

name=NormalTrackInfo_test

bin=/tmp/$name

vv="BASH_SOURCE PWD name bin defarg arg"

defarg="info_gcc_run"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then
   for v in $vv ; do printf "%30s : %s\n" "$v" "${!v}" ; done
fi

if [ "${arg/gcc}" != "$arg" ]; then
    gcc \
      $name.cc \
      ../src/NormalTrackInfo.cc \
      -std=c++17 -lstdc++ \
      -I../include \
      $(geant4-config --cflags) \
      -Wno-shadow \
      $(geant4-config --libs) \
      -o $bin

   [ $? -ne 0 ] && echo $BASH_SOURCE gcc error && exit 1 
fi 

if [ "${arg/run}" != "$arg" ]; then
   $bin
   [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2 
fi


exit 0 

