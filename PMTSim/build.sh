#!/bin/bash -l 

g4-
clhep-

name=PMTSim
srcs="$name.cc
      Hamamatsu_R12860_PMTSolid.cc
      HamamatsuR12860PMTManager.cc 
     "

bin=/tmp/$name/$name
mkdir -p $(dirname $bin)

gcc \
        $srcs \
        -DSTANDALONE \
       -std=c++11 \
       -I. \
       -g \
       -I$(g4-prefix)/include/Geant4 \
       -I$(clhep-prefix)/include \
       -L$(g4-libdir) \
       -L$(clhep-prefix)/lib \
       -lstdc++ \
       -lG4global \
       -lG4materials \
       -lG4particles \
       -lG4track \
       -lG4tracking \
       -lG4processes \
       -lG4geometry \
       -lG4graphics_reps \
       -lCLHEP \
       -o $bin

[ $? -ne 0 ] && echo compile error && exit 1


if [ "$(uname)" == "Darwin" ]; then
   lldb__ $bin
else
   gdb -r ex --args  $bin
fi 


[ $? -ne 0 ] && echo run error && exit 2

exit 0 


