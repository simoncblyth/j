#!/bin/bash -l 

usage(){ cat << EOU
junoPMTOpticalModelTest.sh
============================

NB this also builds with the CMake machinery 


EOU
}

defarg="build_run"
arg=${1:-$defarg}

name=${TEST:-junoPMTOpticalModelTest}
export BASE=/tmp/$USER/opticks/LayrTest 

mkdir -p $BASE
bin=$BASE/$name

if [ "$name" == "junoPMTOpticalModelTest" ]; then
    srcs=("$name.cc" 
          "../HamamatsuR12860PMTManager.cc" 
          "../Hamamatsu_R12860_PMTSolid.cc"
          "../ZSolid.cc"
          "../junoPMTOpticalModel.cc" 
          "../MultiFilmModel.cc" 
          "../OpticalSystem.cc" 
          "../Layer.cc" 
          "../Matrix.cc" 
          "../Material.cc"
          "../DetectorConstruction.cc"
          "../MaterialSvc.cc")

elif [ "$name" == "DetectorConstructionTest" ]; then 
    srcs=("$name.cc"
          "../DetectorConstruction.cc"
          "../MaterialSvc.cc")
fi 

opticks-
boost-
g4-
clhep-

#  -I../../PMTSim     IS NOW INDEP OF PMTSim

if [ "${arg/build}" != "$arg" ]; then 
    echo $BASH_SOURCE build : ${srcs[*]}
    gcc ${srcs[*]} \
         -g -std=c++11 -lstdc++ \
         -DPMTFASTSIM_STANDALONE \
         -I.. \
         -I../../Layr \
         -I$HOME/opticks/sysrap \
         -I$(boost-prefix)/include \
         -I$(clhep-prefix)/include \
         -I$(g4-prefix)/include/Geant4 \
         -L$(g4-prefix)/lib \
         -L$(clhep-prefix)/lib \
         -lG4global \
         -lG4materials \
         -lG4particles \
         -lG4track \
         -lG4tracking \
         -lG4processes \
         -lG4geometry \
         -lG4intercoms \
         -lG4graphics_reps \
         -lCLHEP-$(clhep-ver) \
         -o $bin

    [ $? -ne 0 ] && echo $BASH_SOURCE build fail && exit 1 
fi

     
if [ "${arg/run}" != "$arg" ]; then 
    $bin 
    [ $? -ne 0 ] && echo $BASH_SOURCE run fail && exit 2 
fi 

if [ "${arg/dbg}" != "$arg" ]; then 
    case $(uname) in
        Darwin) lldb__ $bin ;;
        Linux)  gdb__  $bin ;;
    esac
    [ $? -ne 0 ] && echo $BASH_SOURCE dbg fail && exit 3
fi 

exit 0

