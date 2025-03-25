#!/bin/bash

usage(){ cat << EOU
mockbuild.sh
=============

::

    ~/j/gitlab-ci/mockbuild.sh


Running mockbuild.sh suggests one cause of 
gitlab-ci shell exits is line 65 in the below opticks-setup-  
The [ -n "" ] causes exit when using "set -e" when 
OPTICKS_SETUP_VERBOSE is not defined::

     36 opticks-setup- () 
     37 {
     38     local mode=${1:-prepend};
     39     local var=${2:-PATH};
     40     local dir=${3:-/tmp};
     41     local st="";
     42     : dir exists and is not in the path variable already;
     43     if [ -d "$dir" ]; then
     44         if [[ ":${!var}:" != *":${dir}:"* ]]; then
     45             if [ -z "${!var}" ]; then
     46                 export $var=$dir;
     47                 st="new";
     48             else
     49                 st="add";
     50                 case $mode in
     51                     prepend)
     52                         export $var=$dir:${!var}
     53                     ;;
     54                     append)
     55                         export $var=${!var}:$dir
     56                     ;;
     57                 esac;
     58             fi;
     59         else
     60             st="skip";
     61         fi;
     62     else
     63         st="nodir";
     64     fi;
     65     [ -n "$OPTICKS_SETUP_VERBOSE" ] && printf "=== %s %10s %10s %20s %s\n" $FUNCNAME $st $mode $var $dir
     66 }

Googling indicates gitlab-ci uses::

    set -eo pipefail

Investigate with::

    fn0(){ [ -n "$HELLO" ] && printf "hello0\n" ; } 
    fn1(){ if [ -n "$HELLO" ]; then printf "hello1\n" ; fi ; } 


Default bash::

    epsilon:~ blyth$ fn0(){ [ -n "$HELLO" ] && printf "hello0\n" ; } 
    epsilon:~ blyth$ fn1(){ if [ -n "$HELLO" ]; then printf "hello1\n" ; fi ; } 
    epsilon:~ blyth$ fn0
    epsilon:~ blyth$ fn1
    epsilon:~ blyth$ HELLO=1
    epsilon:~ blyth$ fn0
    hello0
    epsilon:~ blyth$ fn1
    hello1
    epsilon:~ blyth$ HELLO=
    epsilon:~ blyth$ fn0
    epsilon:~ blyth$ echo $?
    1
    epsilon:~ blyth$ fn1
    epsilon:~ blyth$ echo $?
    0
    epsilon:~ blyth$ HELLO=1
    epsilon:~ blyth$ fn0
    hello0
    epsilon:~ blyth$ echo $?
    0
    epsilon:~ blyth$ fn1
    hello1
    epsilon:~ blyth$ echo $?
    0
    epsilon:~ blyth$ 


With "set -e" bash::

    epsilon:~ blyth$ set -e
    epsilon:~ blyth$ fn0(){ [ -n "$HELLO" ] && printf "hello0\n" ; }
    epsilon:~ blyth$ fn1(){ if [ -n "$HELLO" ]; then printf "hello1\n" ; fi ; } 
    epsilon:~ blyth$ HELLO=1
    epsilon:~ blyth$ fn0
    hello0
    epsilon:~ blyth$ echo $?
    0
    epsilon:~ blyth$ fn1
    hello1
    epsilon:~ blyth$ echo $?
    0
    epsilon:~ blyth$ HELLO=
    epsilon:~ blyth$ fn1
    epsilon:~ blyth$ echo $?
    0

    ### fn0 exits the shell when HELLO is empty or unset as the "-n" returns non-zero rc


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

