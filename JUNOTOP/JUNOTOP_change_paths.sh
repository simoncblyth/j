#!/bin/bash 

usage(){ cat << EOU
JUNOTOP_change_paths.sh
=========================


Standard JUNOTOP/setup.sh sources a JUNOTOP/bashrc 
that configures access to many externals.
The form of that config is below::

    if [ -z "${JUNOTOP}" ]; then
    export JUNO_EXTLIB_custom4_HOME=/cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J24.2.0/ExternalLibs/custom4/0.1.8
    else
    export JUNO_EXTLIB_custom4_HOME=${JUNOTOP}/ExternalLibs/custom4/0.1.8
    fi

    export PATH=${JUNO_EXTLIB_custom4_HOME}/bin:${PATH}
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_custom4_HOME}/lib:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_custom4_HOME}/lib/pkgconfig:${PKG_CONFIG_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib64 ];
    then
    export LD_LIBRARY_PATH=${JUNO_EXTLIB_custom4_HOME}/lib64:${LD_LIBRARY_PATH}
    fi
    if [ -d ${JUNO_EXTLIB_custom4_HOME}/lib64/pkgconfig ];
    then
    export PKG_CONFIG_PATH=${JUNO_EXTLIB_custom4_HOME}/lib64/pkgconfig:${PKG_CONFIG_PATH}
    fi
    export CPATH=${JUNO_EXTLIB_custom4_HOME}/include:${CPATH}
    export MANPATH=${JUNO_EXTLIB_custom4_HOME}/share/man:${MANPATH}

    # For CMake search path
    export CMAKE_PREFIX_PATH=${JUNO_EXTLIB_custom4_HOME}:${CMAKE_PREFIX_PATH}


As JUNOTOP is 22GB its awkward to copy that
and make a small change.  So instead of that 
keep the standard JUNOTOP but modify the paths that
the bashrc sets.







EOU
}

JUNOTOP_change_paths()
{
   : testing this with local_oj_build_custom4

   local xname=${1:-custom4}
   local yhome=${2:-/some/new/prefix/for/the/$xname/external}
   local xhome=${3:-/default/prefix/for/the/$xname/external}

   # former approach too brittle
   # local _xhome=JUNO_EXTLIB_${xname}_HOME
   # local xhome=${!_xhome}


   local change
   if [ "$yhome" == "$xhome" ]; then
       change=NO
   else
       change=YES
   fi

   local level=1
 
   if [ $level -gt 0 ]; then
       vv="BASH_SOURCE BASH_VERSION FUNCNAME 1 2 xname _xhome xhome yhome change"
       for v in $vv ; do printf " %20s : %s \n" "$v" "${!v}" ; done
   fi 

   if [ "$change" == "NO" ]; then
       echo $BASH_SOURCE NO change so nothing to do - early return
       return 0 
   fi 


   local paths="PATH LD_LIBRARY_PATH PKG_CONFIG_PATH CPATH MANPATH CMAKE_PREFIX_PATH" 
   #local paths="LD_LIBRARY_PATH" 

   for path in $paths
   do
       IFS=$':'
       pv=${!path}

       if [ "${pv:$(( ${#pv} - 1 ))}" ==  ":" ]; then
           TRAILING=1
       else
           TRAILING=0
       fi 

       pp=($pv)
       unset IFS

       if [ $level -gt 1 ]; then
          printf " %15s pp %d TRAILING $TRAILING \n" $path ${#pp[@]} 
       fi

       qq=()
       i=0
       while [ $i -lt ${#pp[@]} ]
       do
           p="${pp[$i]}"
           #printf " %5d : %s \n" $i "$p" 

           q="${p/$xhome/$yhome}"
           qq+=("$q") 
           let i++
       done
       if [ $level -gt 1 ]; then
           printf " %15s pp %d qq %d \n" $path ${#pp[@]} ${#qq[@]} 
       fi

       j=0
       while [ $j -lt ${#qq[@]} ]
       do
           q="${qq[$j]}"

           if [ $level -gt 1 ]; then
               printf " %5d : %s \n" $j "$q" 
           fi

           let j++
       done
 
       ppv=$(IFS=":" ; echo "${pp[*]}" ; unset IFS)
       [ $TRAILING -eq 1 ] && ppv="$ppv:"


       if [ $level -gt 1 ]; then
          [ "$ppv" == "${!path}" ] && printf "ppv matches origin \n" || printf "ppv mismatch\n" 
       fi

       qqv=$(IFS=":" ; echo "${qq[*]}" ; unset IFS)
       [ $TRAILING -eq 1 ] && qqv="$qqv:"

       if [ $level -gt 1 ]; then
           [ "$qqv" == "${!path}" ] && printf "qqv matches origin \n" || printf "qqv mismatch\n" 
       fi 

       declare -n reference_var=$path   ## requires bash 4.3
       reference_var="$qqv"   ## change the path variables via the reference variable

   done
   : testing this with local_oj_build_custom4
}


