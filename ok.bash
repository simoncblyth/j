#!/bin/bash -l
# ~/j/ok.bash 
# ~/.bash_profile > ~/.bashrc > ~/j/ok.bash

ok-notes(){ cat << EON
~/j/ok.bash
============

Aim is for minimal bash functions to test junosw+opticks
as the jx.bash funcs have grown into monsters. 

Usage::

   source ~/j/ok.bash 
   ok-tds 

EON
}


ok-tds-(){
   local script=$JUNOTOP/junosw/Examples/Tutorial/share/tut_detsim.py
   python $script $*
}

ok-tds(){

   local mode=3 
   local evtmax=1

   export OPTICKS_INTEGRATION_MODE=$mode
   local opts="" 
   opts="$opts --evtmax $evtmax"
   opts="$opts --opticks-mode $mode"   
   opts="$opts --no-guide_tube"
   opts="$opts --additionacrylic-simplify-csg"
   opts="$opts --no-toptask-show"

   case ${NOXJ:-1} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-xj" ;; 
   esac

   case ${NOSJ:-1} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-sj" ;; 
   esac

   case ${NOFA:-1} in 
      0) opts="$opts" ;; 
      1) opts="$opts --debug-disable-fa" ;; 
   esac

   opts="$opts $(ok-anamgr) "


   local gun_default="gun"
   local gun_wangyg="gun --particles gamma --momentums 2.223 --momentums-interp KineticEnergy --positions 0 0 0"
   local trgs=""     
   : "trgs" are the arguments after the opts : eg "gun" or "opticks" 

   case ${GUN:-0} in  
     0) trgs="$trgs opticks"  ;;
     1) trgs="$trgs $gun_default" ;;
     2) trgs="$trgs $gun_wangyg" ;;
   esac

   if [ "$GUN" == "0" ]; then 
       export OPTICKS_INPUT_PHOTON=RainXZ_Z230_1M_f8.npy 
       export OPTICKS_INPUT_PHOTON_FRAME=NNVT:0:1000
   fi

   ok-tds- $opts $trgs 
}



ok-anamgr(){ cat << EOU
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


