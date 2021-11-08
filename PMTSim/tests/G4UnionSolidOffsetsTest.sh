#!/bin/bash -l 

name=G4UnionSolidOffsetsTest
usage(){ cat << EOU

Note that this just uses the headers, no need for the libs.
This makes sense as offsets are fully defined in the headers. 

EOU
}

g4-
clhep-

gcc $name.cc \
      -I. \
      -I$(g4-prefix)/include/Geant4 \
      -I$(clhep-prefix)/include \
      -std=c++11 \
      -lstdc++ \
      -o \
          /tmp/$name 

[ $? -ne 0 ] && echo compile error && exit 1 

/tmp/$name
[ $? -ne 0 ] && echo run error && exit 2 

exit 0 


