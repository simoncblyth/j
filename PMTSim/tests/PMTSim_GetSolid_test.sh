#!/bin/bash -l 
usage(){ cat << EOU
PMTSim_GetSolid_test.sh
========================

Check standalone use of PMTSim::GetSolid accessing 
complex solids.::

   ~/j/PMTSim/tests/PMTSim_GetSolid_test.sh

EOU
}

cd $(dirname $BASH_SOURCE)
name=PMTSim_GetSolid_test
FOLD=/tmp/$name
bin=$FOLD/$name

mkdir -p $FOLD
export FOLD

opticks-
clhep-
g4-

vars="BASH_SOURCE arg name FOLD bin"

defarg="info_build_run"
arg=${1:-$defarg}

if [ "${arg/info}" != "$arg" ]; then 
    for var in $vars ; do printf "%20s : %s \n" "$var" "${!var}" ; done 
fi 

if [ "${arg/build}" != "$arg" ]; then
    gcc \
         $name.cc \
         -I$HOME/j/PMTSim \
         -std=c++11 -lstdc++ \
         -I$HOME/opticks/sysrap \
         -I$(clhep-prefix)/include \
         -I$(g4-prefix)/include/Geant4  \
         -L$OPTICKS_PREFIX/lib \
         -L$OPTICKS_PREFIX/lib64 \
         -lPMTSim \
         -L$(g4-prefix)/lib \
         -L$(g4-prefix)/lib64 \
         -L$(clhep-prefix)/lib \
         -lG4global \
         -lG4geometry \
         -lG4graphics_reps \
         -lCLHEP \
         -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

if [ "${arg/ana}" != "$arg" ]; then
    ${IPYTHON:-ipython} --pdb -i $name.py 
    [ $? -ne 0 ] && echo $BASH_SOURCE ana error && exit 3
fi 

exit 0 


