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


jok-tds-(){
   local script=$JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py
   python $script $*
}

jok-tds(){

   local mode=3 
   local evtmax=1

   export OPTICKS_SCRIPT=$FUNCNAME  # avoid default sproc::_ExecutableName of python3.9 
   export OPTICKS_INTEGRATION_MODE=$mode
   export GEOM=J23_1_0_rc3_ok0   # replace . and - with _ to make valid bash identifier

   export Tub3inchPMTV3Manager__VIRTUAL_DELTA_MM=0.10            # default 1.e-3 
   export HamamatsuMaskManager__MAGIC_virtual_thickness_MM=0.10  # default 0.05 
   export NNVTMaskManager__MAGIC_virtual_thickness_MM=0.10       # default 0.05

   export G4CXOpticks__SaveGeometry_DIR=$HOME/.opticks/GEOM/$GEOM

   export OPTICKS_EVENT_MODE=StandardFullDebug
   export OPTICKS_MAX_BOUNCE=31
   export OPTICKS_MAX_PHOTON=1000000


   local opts="" 
   opts="$opts --evtmax $evtmax"
   opts="$opts --opticks-mode $mode"   
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

   GUN=${GUN:-0}
   case $GUN in  
     0) trgs="$trgs opticks"  ;;
     1) trgs="$trgs $gun_default" ;;
     2) trgs="$trgs $gun_wangyg" ;;
   esac

   if [ "$GUN" == "0" ]; then 
       export OPTICKS_INPUT_PHOTON=RainXZ_Z230_1M_f8.npy 
       export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000
   fi

   local vars="BASH_SOURCE mode NOXJ NOSJ NOFA GUN opts trgs"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 

   env | grep OPTICKS

   jok-tds- $opts $trgs 
}



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

jok-grab(){
   : ~/j/jok.bash  
   source $HOME/.opticks/GEOM/GEOM.sh 
   local tmp=${TMP:-/tmp/$USER/opticks}/GEOM/$GEOM/jok-tds

   local vars="BASH_SOURCE FUNCNAME tmp TMP GEOM OPTICKS_HOME"
   for var in $vars ; do printf "%25s : %s \n" "$var" "${!var}" ; done 

   source $OPTICKS_HOME/bin/rsync.sh $tmp 
}


