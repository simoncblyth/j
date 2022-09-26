#!/bin/bash -l
# ~/j/jx.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jx.bash

jx-usage(){ cat << EOU
jx.bash
=========

Update of the former j/j.bash for the git based junosw environment 


EOU
}

jx-vi(){ vi $BASH_SOURCE ; }


jx-runtime-env-()
{
   : note that CMAKE_PREFIX_PATH and MANPATH keep appending on repeated running but the others dont
   local msg="=== $FUNCNAME: "
   echo $msg
   source $JUNOTOP/bashrc.sh   # sources the bashrc of the JUNOTOP/ExternalLibs
   source $JUNOTOP/sniper/InstallArea/bashrc
   source $JUNOTOP/sniper/InstallArea/share/sniper/setup.sh   
   source $JUNOTOP/mt.sniper/InstallArea/bashrc
   source $JUNOTOP/junosw/InstallArea/setup.sh


   echo $msg
}

jx-runtime-env()
{
   : setup the runtime environment CMAKE_PREFIX_PATH, PKG_CONFIG_PATH, LD_LIBRARY_PATH, PATH, MANPATH
   local msg="=== $FUNCNAME: "
   local var=JX_RUNTIME_ENV
   if [ -n "${!var}" ]; then
       echo $msg skip as $var:${!var} use jre- or jx-runtime-env- to force it 
   else
       export $var=1
       jx-runtime-env-
   fi
}


jre(){  
   jx-runtime-env 
   jo 
   if [ -n "$OPTICKS_PREFIX" ]; then
       : TODO add these settings to standard environment
       opticks-
       export PYTHONPATH=$PYTHONPATH:$JUNOTOP
   fi   
}  
jre-(){ jx-runtime-env- ; }













jx-all()
{
   jx-junoenv
   jx-extlib
   jx-env
   jx-sniper
   jx-offline
   jx-offline-data
}

jx-junoenv()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   [ -z "$JUNOTOP" ] && echo $msg JUNOTOP is not defined && return 1 
   cd $JUNOTOP
   [ ! -d "junoenv" ] && git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
   [ ! -d "junoenv" ] && echo $msg junoenv dir does not exist && return 2 
}

jx-extlib()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   cd $JUNOTOP/junoenv

   if [ ! -d "$JUNOTOP/ExternalLibs" ]; then 
       local jver=J22.2.x
       #local oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/$jver/ExternalLibs
       local oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/$jver/ExternalLibs
       # needs corresponding compiler setup in .local

       [ ! -d "$oldtop" ] && echo $msg oldtop $oldtop does not exist && return 3
       export JUNO_EXTLIB_OLDTOP=$oldtop
       bash junoenv libs reuse allpkgs
   else
       echo $msg JUNOTOP/ExternalLibs exists already 
   fi 
}

jx-env()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -f "$JUNOTOP/bashrc.sh" ]; then
        bash junoenv env
    else
        echo $msg JUNOTOP/bashrc.sh exists already 
    fi
    source $JUNOTOP/bashrc.sh
}

jx-sniper()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/sniper" ]; then
        bash junoenv sniper 
    else
        echo $msg JUNOTOP/sniper exists already 
    fi

    cd $JUNOTOP/sniper/InstallArea
    source bashrc 

    cd $JUNOTOP/junoenv
}

jx-offline()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/offline" ]; then
        bash junoenv offline 
    else
        echo $msg JUNOTOP/offline exists already 
    fi  

    cd $JUNOTOP/junoenv
}

jx-offline-data() 
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/data" ]; then
        bash junoenv offline-data 
    else
        echo $msg JUNOTOP/data exists already 
    fi  

    cd $JUNOTOP/junoenv
}



