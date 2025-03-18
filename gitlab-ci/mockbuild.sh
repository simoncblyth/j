#!/bin/bash

usage(){ cat << EOU
mockbuild.sh
=============

::

    ~/j/gitlab-ci/mockbuild.sh


Observations::

    [ -n "$OPTICKS_SETUP_VERBOSE" ] && printf 


When OPTICKS_SETUP_VERBOSE is not defined the above gives an error with "set -xeo pipefail"


EOU
}

cd $(dirname $(realpath $BASH_SOURCE))

set -xeo pipefail

unset LD_LIBRARY_PATH
PATH=/usr/bin

export JUNO_OFFLINE_OFF=1
export JUNOTOP=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/Jlatest
export JUNO_OPTICKS_PREFIX=/cvmfs/opticks.ihep.ac.cn/ok/releases/Opticks-vLatest/x86_64--gcc11-geant4_10_04_p02-dbg

export OPTICKS_SETUP_VERBOSE=1


source $JUNOTOP/setup.sh
if [ -n "$JUNO_OPTICKS_PREFIX" ]; then source $JUNO_OPTICKS_PREFIX/bashrc; fi



#export OPTICKS_PREFIX=$JUNO_OPTICKS_PREFIX
#
#opticks-setup-find-config-prefix(){
#   : mimick CMake "find_package name CONFIG" identifing the first prefix in the path
#   local name=${1:-Geant4}
#   local prefix=""
#   local rc=0
#   local ifs=$IFS
#   IFS=:
#   for pfx in $CMAKE_PREFIX_PATH ; do
#
#      : protect cmds that can give non-zero rc from "set -e" via pipeline but catch the rc 
#      rc=1  
#      ls -1 $pfx/lib*/$name-*/${name}Config.cmake 2>/dev/null 1>&2 && rc=$?
#      [ $rc -eq 0 ] && prefix=$pfx && break
#      
#      ls -1 $pfx/lib*/cmake/$name-*/${name}Config.cmake 2>/dev/null 1>&2 && rc=$?
#      [ $rc -eq 0 ] && prefix=$pfx && break
#      
#      ls -1 $pfx/lib*/cmake/$name/${name}Config.cmake 2>/dev/null 1>&2 && rc=$?
#      [ $rc -eq 0 ] && prefix=$pfx && break
#      
#      # NB not general, doesnt find the lowercased form : but works for Geant4 and Boost 
#   done 
#   IFS=$ifs
#   echo $prefix
#}
#
#opticks-setup-find-geant4-prefix () 
#{ 
#    opticks-setup-find-config-prefix Geant4
#}
#
#export OPTICKS_GEANT4_PREFIX=$(opticks-setup-find-geant4-prefix)




env | grep OPTICKS
echo =============================================== DONE =============================================

