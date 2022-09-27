#!/bin/bash -l
# ~/j/jx.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jx.bash

jxv(){ vi $BASH_SOURCE && jxf ; }
jxf(){ source $BASH_SOURCE ; }

jx-usage(){ cat << EOU
jx.bash
=========

Update of the former j/j.bash for the git based junosw environment 


EOU
}

jx-vi(){ vi $BASH_SOURCE ; }



jt(){ cd $JUNOTOP ; pwd ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/junosw && pwd && git status ; } 


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
   jx-oldtop
   jx-junoenv-latest
   jx-extlib-collection
   jx-extlib
   jx-env
   jx-sniper
   jx-offline
   jx-offline-data
}


jx-ccbase()
{
   local ccbase=$(dirname $(dirname $(dirname $(dirname $(dirname $CC)))))
   echo $ccbase
}

jx-extlib-oldtop()
{
   local ccbase=$(jx-ccbase)
   local oldtop
   case $ccbase in
       #/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.0-rc4/ExternalLibs ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830/Pre-Release/J22.1.x/ExternalLibs ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120) oldtop=/cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120/Pre-Release/J22.2.x/ExternalLibs  ;;
   esac
   echo $msg CC $CC ccbase $ccbase oldtop $oldtop
   [ ! -d "$oldtop" ] && echo $msg oldtop $oldtop does not exist && return 3
   export JUNO_EXTLIB_OLDTOP=$oldtop
}

jx-extlib-collection()
{
   local ccbase=$(jx-ccbase)
   local collection
   case $ccbase in
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc830) collection=22.1  ;;
       /cvmfs/juno.ihep.ac.cn/centos7_amd64_gcc1120) collection=22.2 ;;
   esac
   export JUNO_EXTLIB_COLLECTION=$JUNOTOP/junoenv/collections/$collection.sh
}

jx-junotop()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   [ -z "$JUNOTOP" ] && echo $msg JUNOTOP is not defined && return 1 
   cd $JUNOTOP
}

jx-junoenv-latest()
{
   jx-junotop
   local msg="=== $BASH_SOURCE $FUNCNAME "
   [ ! -d "junoenv" ] && git clone git@code.ihep.ac.cn:JUNO/offline/junoenv.git 
   [ ! -d "junoenv" ] && echo $msg junoenv dir does not exist && return 2 
}

jx-junoenv-linked()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   jx-junotop
   jx-extlib-oldtop 

   local oldtop=$(dirname $JUNO_EXTLIB_OLDTOP)
   ln -s $oldtop/junoenv junoenv
}

jx-extlib()
{
   local msg="=== $BASH_SOURCE $FUNCNAME "
   cd $JUNOTOP/junoenv


   if [ ! -d "$JUNOTOP/ExternalLibs" ]; then 
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


tds-dir(){ echo /tmp/$USER/opticks/tds ; }
tds-cd(){ cd $(tds-dir) ; }

tds-(){ 
   type $FUNCNAME
   local msg="=== $FUNCNAME :"

   [ -z "$JX_RUNTIME_ENV" ]  && echo $msg MUST RUN jre BEFORE tds && return 2 
 
   local script=$JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py
   if [ -z "$BP" ]; then
      H="" 
      B="" 
      T="-ex r" 
   else
      H="-ex \"set breakpoint pending on\""
      B="" 
      for bp in $BP ; do B="$B -ex \"break $bp\" " ; done
      T="-ex \"info break\" -ex r" 
   fi

   local iwd=$PWD
   local dir=$(tds-dir)
   mkdir -p $dir
   cd $dir

   local runline
   if [ -n "$PDB" ]; then 
       runline="ipython --pdb $script $*"
   else
       runline="gdb $H $B $T --args python $script $*"
   fi 

   echo $runline
   date
   eval $runline 
   date
   cd $iwd


}

tds0(){
   : run without opticks 
   #local former_opts="--opticks-mode 0 --no-guide_tube --pmt20inch-polycone-neck --pmt20inch-simplify-csg --evtmax 2 " ;   
   local opts="--opticks-mode 0 --no-guide_tube --evtmax 2 " ;   
   tds- $opts gun $*
}


