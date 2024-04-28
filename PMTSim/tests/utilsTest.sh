#!/bin/bash -l 

usage(){ cat << EOU

epsilon:offline blyth$ jcv utils
3 files to edit
./Detector/Parameter/Parameter/utils.hh
./Simulation/DetSimV2/MCParamsSvc/src/utils.hh
./XmlObjDesc/scripts/xml/parsers/xmlproc/utils.py
epsilon:offline blyth$ 
epsilon:offline blyth$ 
epsilon:offline blyth$ diff Detector/Parameter/Parameter/utils.hh Simulation/DetSimV2/MCParamsSvc/src/utils.hh
1,2c1,2
< #ifndef det_utils_hh
< #define det_utils_hh
---
> #ifndef utils_hh
> #define utils_hh





BOOST IS NO LONGER A STANDARD OPTICKS EXTERNAL : SO TOO MUCH HASSLE TO KEEP THIS WORKING 



EOU
}


name=utilsTest 

opticks-
boost-
g4-
clhep-


gcc $name.cc \
      -std=c++11 \
      -DPMTSIM_STANDALONE \
      -I.. \
      -lstdc++ \
      -I$(boost-prefix)/include \
      -L$(boost-prefix)/lib \
      -I$(g4-prefix)/include/Geant4 \
      -I$(clhep-prefix)/include \
      -L$(g4-prefix)/lib \
      -L$(g4-prefix)/lib64 \
      -lG4global \
      -o \
           /tmp/$name 

[ $? -ne 0 ] && echo compile error && exit 1 


export DYLD_LIBRARY_PATH=$(g4-prefix)/lib:$(clhep-prefix)/lib
export LD_LIBRARY_PATH=$(g4-prefix)/lib64:$(clhep-prefix)/lib

paths=$(find $JUNOTOP/data/Simulation/DetSim/Material -type f)

for path in $paths 
do 
    /tmp/$name $path
done

[ $? -ne 0 ] && echo run error && exit 2

exit 0  


