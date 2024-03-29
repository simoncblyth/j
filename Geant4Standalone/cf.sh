#!/bin/bash -l 
usage(){ cat << EOU

   ~/j/Geant4Standalone/cf.sh 

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

VERS=1042 ./build.sh 
VERS=1120 ./build.sh 

