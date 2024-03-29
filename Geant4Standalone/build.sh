#!/bin/bash -l 
usage(){ cat << EOU

~/j/Geant4Standalone/build.sh 

EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

unset JUNOTOP

name="Geant4Standalone" 

FOLD=/tmp/$USER/j/$name 
mkdir -p $FOLD
bin=$FOLD/$name

defarg="info_build_run"
arg=${1:-$defarg}

src=$name.cc
SRC=${SRC:-$src}

vers=1042
VERS=${VERS:-$vers}

if [ "$VERS" == "1042" ]; then

    base=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J23.1.0-rc3/ExternalLibs
    my_clhep_prefix=$base/CLHEP/2.4.1.0
    my_geant4_prefix=$base/Geant4/10.04.p02.juno

elif [ "$VERS" == "1120" ]; then 

    base=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J24.1.x-g411/ExternalLibs
    my_clhep_prefix=$base/CLHEP/2.4.7.1
    my_geant4_prefix=$base/Geant4/11.2.0
fi 

source $my_clhep_prefix/bashrc
source $my_geant4_prefix/bashrc


vars="my_geant4_prefix my_clhep_prefix SRC FOLD name bin VERS"

if [ "${arg/info}" != "$arg" ]; then
    for var in $vars ; do printf "%20s : %s\n" "$var" "${!var}" ; done 
fi 

if [ "${arg/config}" != "$arg" ]; then
    geant4-config --cflags
    geant4-config --libs
fi 

if [ "${arg/build}" != "$arg" ]; then
    gcc $SRC \
        -I. \
        -g \
        -Wno-deprecated-copy \
        $(geant4-config --cflags) \
        $(geant4-config --libs) \
         -lstdc++ \
        -o $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : build error && exit 1 
fi

if [ "${arg/run}" != "$arg" ]; then
    $bin
    [ $? -ne 0 ] && echo $BASH_SOURCE : run error && exit 2 
fi


