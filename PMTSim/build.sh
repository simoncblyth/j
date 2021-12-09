#!/bin/bash -l 

usage(){ cat << EOU

Have moved to building PMTSim using standard Opticks *om* rather than this script

EOU
}


g4-
clhep-
boost-

name=PMTSimTest

srcs="
      tests/$name.cc
      PMTSim.cc
      Hamamatsu_R12860_PMTSolid.cc
      HamamatsuR12860PMTManager.cc 
      NNVT_MCPPMT_PMTSolid.cc
      NNVTMCPPMTManager.cc
      DetectorConstruction.cc
      ZSolid.cc
      MaterialSvc.cc
     "

bin=/tmp/$name/$name
mkdir -p $(dirname $bin)

gcc \
        $srcs \
        -DPMTSIM_STANDALONE \
       -std=c++11 \
       -Wcomment \
       -Wunused-variable \
       -Wunused-parameter \
       -Wextra \
       -Wunused \
       -Wall \
       -I. \
       -I$HOME/np \
       -g \
       -I$(g4-prefix)/include/Geant4 \
       -I$(clhep-prefix)/include \
       -I$(boost-prefix)/include \
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


