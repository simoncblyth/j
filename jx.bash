#!/bin/bash -l
# ~/j/jx.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jx.bash

jx-usage(){ cat << EOU
jx.bash : Started Sept 2022 : Updating to git junosw
=========================================================

Update of the former j/j.bash for the git based junosw environment 



EOU
}

jxv(){ vi $BASH_SOURCE ~/j/j.bash && jxf ; }
jx-vi(){ vi $BASH_SOURCE ; }
jxf(){ source $BASH_SOURCE ; }
jxo(){  open -a "Firefox Developer Edition" https://code.ihep.ac.cn/JUNO/offline ;  }

jproj(){ cat << EOL

Simulation/DetSimV2/PhysiSim
Simulation/GenTools
Simulation/DetSimV2/PMTSim
Simulation/DetSimV2/AnalysisCode
Simulation/DetSimV2/DetSimOptions

EOL
}



jx-isim(){ jx-sub Simulation/DetSimV2/PhysiSim ; }
jx-pmts(){ jx-sub Simulation/DetSimV2/PMTSim ; }
jx-sub()
{
   local msg="=== $BASH_SOURCE $FUNCNAME"
   local rel=${1:-Simulation/DetSimV2/PhysiSim} 
   local sdir=$JUNOTOP/junosw/$rel
   local bdir=$JUNOTOP/junosw/build/$rel

   if [ ! -d "$sdir" ]; then 
      echo $msg sdir $sdir for rel $rel does not exist
      return -1
   fi 
   if [ ! -d "$bdir" ]; then 
      echo $msg bdir $bdir for rel $rel does not exist
      return -1
   fi 

   cd $bdir ; pwd

   local njobs=-j$(nproc)
   cmake --build . $njobs || return -1 
   cmake --install . || return -1

   cd $sdir ; pwd
}


jt(){ cd $JUNOTOP ; pwd ; } 
je(){ cd $JUNOTOP/junoenv && pwd ; } 
jo(){ cd $JUNOTOP/junosw && pwd && git status ; } 


# -false to end sequence of ors 
#
# HMM jcl jcld fails when the * shell expansion find the files in the invoking directory 
# as that messes up the find command
# double quoting the f gets some way but somehow messes up other things
# HENCE: use jcl jfi from top level where shell expansion will not find the files in the invoking directory 

jcld(){ local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ; echo find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 
jcl(){  local f="" ; for name in $* ; do f="$f -name $name.* -o " ; done ;      find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 
jfi(){  local f="" ; for name in $* ; do f="$f -name $name   -o " ; done ;      find . \( $f -false \) -a ! -path './*/Linux-x86_64/*' -a ! -path './build/*' ; } 


jcv-(){ local fi=$(jcl $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }
jfv-(){ local fi=$(jfi $* | sort) ; [ "$fi" != "" ] && vi $fi ; echo $fi | tr " " "\n" ;  }

jcv(){ cd $JUNOTOP/junosw ; jcv- $* ; : edit files identified by stem ;  } 
jfv(){ cd $JUNOTOP/junosw ; jfv- $* ; : list files identified by wildcard ; } 

jgr-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -H "${1:-G4OPTICKS}" {} \; ; } 
jgr(){ cd $JUNOTOP/junosw ; jgr- $* ; : search files with the query string and show matches - skips are made to avoid cmt garbage ;  } 

jgl-(){ find . ! -path "./.svn/*"  -a ! -path '*.swp' -a ! -path './*/Linux-x86_64/*' -a ! -path '*.sh' -a ! -path '*.csh'  -type f -exec grep -l "${1:-G4OPTICKS}" {} \; ; }
jgl(){ cd $JUNOTOP/junosw ; jgl- $* ; : search files with the query string and list matched paths - skips are made to avoid cmt garbage ; } 
 





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
   jx-extlib-oldtop
   jx-junoenv-latest
   jx-extlib-collection
   jx-extlib
   jx-env
   jx-sniper
   jx-sniper-env
   jx-offline
   jx-offline-data
   jx-opticks
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

    cd $JUNOTOP/junoenv
}

jx-sniper-env()
{
    cd $JUNOTOP/sniper/InstallArea
    source bashrc 
    cd $JUNOTOP/junoenv
}

jx-offline()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/junosw" ]; then
        bash junoenv offline 
    else
        echo $msg JUNOTOP/junosw exists already 
    fi  

    cd $JUNOTOP/junoenv
}

jx-offline-config()
{
    cd $JUNOTOP/junosw/build
    local installprefix=$JUNOTOP/junosw/InstallArea
    cmake .. -DCMAKE_INSTALL_PREFIX=$installprefix -DCMAKE_CXX_STANDARD=17  
}
jx-offline-build()
{
    : HUH bash junoenv offline is not rerunnable so use this

    jx-offline-config || return -1  

    local njobs=-j$(nproc)
    cmake --build . $njobs || return -1 
    cmake --install . || return -1

    return 0 
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


jx-opticks()
{
    local msg="=== $BASH_SOURCE $FUNCNAME "
    cd $JUNOTOP/junoenv

    if [ ! -d "$JUNOTOP/opticks" ]; then
        bash junoenv opticks 
    else
        echo $msg JUNOTOP/opticks exists already 
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
   local opts="--opticks-mode 0 --no-guide_tube --evtmax 2 " ;   
   tds- $opts gun $*
}



anamgr(){ cat << EOU
--opticks-anamgr
--no-anamgr-normal
--no-anamgr-genevt
--no-anamgr-edm-v2
--no-anamgr-grdm
--no-anamgr-deposit
--no-anamgr-deposit-tt
--no-anamgr-interesting-process
--no-anamgr-optical-parameter
--no-anamgr-timer
EOU
}



ntds0(){ OPTICKS_MODE=0 ntds3 ; }  #0b00   Ordinary running without Opticks involved at all  
ntds1(){ OPTICKS_MODE=1 ntds3 ; }  #0b01   Running with only Opticks doing the optical propagation 
#ntds2(){ OPTICKS_MODE=2 ntds3 ; }  #0b10   Geant4 only with Opticks instrumentation (that was original idea) 
                                    #       but U4RecorderTest running superceeds that :  perhaps assert that this mode is not used 
ntds3()                            #0b11   Running with both Geant4 and Opticks optical propagation
{
   env | grep =INFO

   local args=$*     
   local msg="=== $FUNCNAME :"
   local evtmax=${EVTMAX:-2}
   local mode=${OPTICKS_MODE:-3}

   export SCRIPT=${SCRIPT:-$FUNCNAME} 

   local opts="" 
   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --disable-pmt-optical-model"
   opts="$opts --evtmax $evtmax"
   opts="$opts $(anamgr) "

   if [ -n "$DEBUG_DISABLE_STICKS" ]; then
       opts="$opts --debug-disable-sticks"
   fi 

   local trgs=""
   trgs="$trgs gun"

   echo $msg opts : $opts 
   echo $msg trgs : $trgs 
   echo $msg args : atrgs 

   #BASE=/tmp/$USER/opticks/$SCRIPT   
   BASE=.opticks/$SCRIPT   

   case $(uname) in 
      Linux) tds- $opts $trgs $args  ;;
      Darwin) source $OPTICKS_HOME/bin/rsync.sh $BASE ;;
   esac
   env | grep =INFO
}

ninfo(){ env | grep =INFO ; }


