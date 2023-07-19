#!/bin/bash -l 
usage(){ cat << EOU
build.sh : currently failing to find SysRap due to plog
=========================================================

Need to install PMTSim in a more controllable manner, 
than installing into OPTICKS_PREFIX in order to make 
it easier to switch off finding it. 

As that proved diffult see the kludge : om_remove.sh 

EOU
}

opticks-
pmtsim_prefix=${OPTICKS_PREFIX}_externals/pmtsim
PMTSIM_PREFIX=${PMTSIM_PREFIX:-$pmtsim_prefix}


REALDIR=$(cd $(dirname $BASH_SOURCE) && pwd)
sdir=$(pwd)
name=$(basename $sdir)

BASE=/tmp/$USER/$name
bdir=$BASE/build


defarg="info_install"
arg=${1:-$defarg}

vars="sdir name BASE bdir idir arg OPTICKS_PREFIX pmtsim_prefix PMTSIM_PREFIX"


echo $CMAKE_PREFIX_PATH | tr ":" "\n"


if [ "${arg/info}" != "$arg" ]; then
   for var in $vars ; do printf "%30s : %s \n" "$var" "${!var}" ; done
fi

if [ "${arg/install}" != "$arg" ]; then

    rm -rf $bdir
    mkdir -p $bdir  
    cd $bdir
    pwd

    cmake $sdir \
         -DCMAKE_BUILD_TYPE=Debug \
         -DCMAKE_PREFIX_PATH=$(opticks-prefix)/externals \
         -DCMAKE_MODULE_PATH=$(opticks-home)/cmake/Modules \
         -DCMAKE_INSTALL_PREFIX=$PMTSIM_PREFIX

    make
    make install
fi


