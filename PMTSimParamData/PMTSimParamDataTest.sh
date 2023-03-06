#!/bin/bash -l 

defarg="build_run"
arg=${1:-$defarg}

name=PMTSimParamDataTest
export FOLD=/tmp/$name
mkdir -p $FOLD
bin=$FOLD/$name



export PMTSimParamData_BASE=$HOME/.opticks/GEOM/J007/CSGFoundry/SSim/juno

clhep-
g4-




if [ "${arg/build}" != "$arg" ]; then 

    gcc $name.cc \
          -g -std=c++11 -lstdc++ \
          -I$HOME/opticks/sysrap \
          -DWITH_NP \
          -I$JUNOTOP/junosw/Detector/Geometry \
          -I$JUNOTOP/junosw/Simulation/SimSvc/PMTSimParamSvc \
          -I$(clhep-prefix)/include \
          -I$(g4-prefix)/include/Geant4  \
          -L$(clhep-prefix)/lib \
          -L$(g4-prefix)/lib \
          -lCLHEP \
          -lG4global \
          -lG4materials \
          -o $bin

    [ $? -ne 0 ] && echo $BASH_SOURCE build error && exit 1 
fi

if [ "${arg/run}" != "$arg" ]; then 
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE run error && exit 2
fi 

if [ "${arg/dbg}" != "$arg" ]; then 
    case $(uname) in
     Darwin) lldb__ $bin ;;
      Linux) gdb__ $bin ;;
    esac
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg error && exit 3
fi 




exit 0 

