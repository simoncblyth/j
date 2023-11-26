#!/bin/bash -l
# ~/j/jok.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/jok.bash
jok-source(){ echo $BASH_SOURCE ; }
jok-vi(){ vi $BASH_SOURCE ; }
jok-(){ source $BASH_SOURCE ; }
jok-notes(){ cat << EON
~/j/jok.bash
============

Aim is for minimal bash functions to test junosw+opticks
as the jx.bash funcs have grown into monsters. 

Usage::

   source ~/j/jok.bash 
   jok-tds 

EON
}

jok-script(){ echo $JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py ; }
jok-tds(){
   export OPTICKS_SCRIPT=$FUNCNAME     # avoid default sproc::_ExecutableName of python3.9 
   export OPTICKS_INTEGRATION_MODE=3   # both geant4 and opticks optical simulation   
   export GEOM=J23_1_0_rc3_ok0         # replace . and - with _ to make valid bash identifier
   export G4CXOpticks__SaveGeometry_DIR=$HOME/.opticks/GEOM/$GEOM

   export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3 
   export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05 
   export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05

   local mode=StandardFullDebug
   #local mode=HitOnly
   #local mode=Minimal
   export OPTICKS_EVENT_MODE=$mode  ## see SEventConfig::Initialize SEventConfig::EventMode

   export OPTICKS_MAX_BOUNCE=31
   export OPTICKS_MAX_PHOTON=1000000

   local opts="" 
   opts="$opts --evtmax 10"
   opts="$opts --opticks-mode $OPTICKS_INTEGRATION_MODE "   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --no-toptask-show"

   NOXJ=${NOXJ:-1}
   case $NOXJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-xj" ;; 
   esac

   NOSJ=${NOSJ:-1}
   case $NOSJ in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-sj" ;; 
   esac

   NOFA=${NOFA:-1}
   case $NOFA in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-fa" ;; 
   esac

   opts="$opts $(jok-anamgr) "

   local gun_default="gun"
   local gun_wangyg="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
   local trgs=""     
   : "trgs" are the arguments after the opts : eg "gun" or "opticks" 

   gun=1 
   GUN=${GUN:-$gun}
   case $GUN in  
     0) trgs="$trgs opticks"      ;;
     1) trgs="$trgs $gun_default" ;;
     2) trgs="$trgs $gun_wangyg"  ;;
   esac

   if [ "$GUN" == "0" ]; then 
       #export OPTICKS_INPUT_PHOTON=RainXZ_Z230_1M_f8.npy 
       export OPTICKS_INPUT_PHOTON=RainXZ_Z230_10k_f8.npy 
       export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000
   fi

   logging()
   {
       ## for SEvt::setFoldVerbose NPFold::set_verbose frm A and B SEvt
       export QEvent__SEvt_NPFold_VERBOSE=1  
       export U4Recorder__SEvt_NPFold_VERBOSE=1  
       export SEvt__LIFECYCLE=1  ## sparse SEvt debug output, works well alone  
   }
   logging


   #local jokdir=$HOME/tmp/$FUNCNAME 
   local jokdir=$HOME/tmp/GEOM/$GEOM/$FUNCNAME/ALL0 
   mkdir -p $jokdir
   cd $jokdir     # log files are dropped in invoking directory 
   pwd
   ls -alst

   local root="sample_detsim_user.root"
   if [ -f "$root" ]; then
       echo === $BASH_SOURCE : deleting $root from PWD $PWD HOME $HOME
       rm -f $root
   else
       echo === $BASH_SOURCE : no $root in PWD $PWD
   fi 


   local runline="python $(jok-script) $opts $trgs"

   if [ -n "$GDB" -o -n "$BP" ]; then
       #export SEvt__CLEAR_SIGINT=1 ## debug  
       runline="jok-gdb $runline"
   fi 
   #runline="gdb -ex r --args python $(jok-script) $opts $trgs"  

   local vars="BASH_SOURCE mode NOXJ NOSJ NOFA GUN opts trgs jokdir PWD runline"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 
   env | grep OPTICKS
   env | grep __

   eval $runline


   local postline="sstampfold_report"
   echo $postline
   eval $postline
 

}
jok-tds-gdb(){ GDB=1 jok-tds ; }


jok-anamgr(){ cat << EOU
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
   : opticks-anamgr is used by the U4Recorder
}

jok-ana(){ ~/j/jtds/jtds.sh $* ; }


jok-gdb() 
{ 
    : ~/j/jok.bash :  invokes gdb - sets up breakpoints based on BP envvar containing space delimited symbols;
    if [ -z "$BP" ]; then
        H="";
        B="";
        T="-ex r";
    else
        H="-ex \"set breakpoint pending on\"";
        B="";
        for bp in $BP;
        do
            B="$B -ex \"break $bp\" ";
        done;
        T="-ex \"info break\" -ex r";
    fi;
    local runline="gdb $H $B $T --args $* ";
    echo $runline;
    date;
    eval $runline;
    date
}


