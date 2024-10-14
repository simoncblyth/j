#!/bin/bash 
usage(){ cat << EOU
~/j/cx.sh : Ray trace render with skipped : big-container-volumes, TT, PMT virtual wrappers
=============================================================================================

::

   ~/j/cx.sh 


Keys::

   H : dump help string

   K : screen shot


EOU
}



elv=$(cat << EOS | tr "\n" ","
sTopRock_domeAir
sTopRock_dome
sDomeRockBox
PoolCoversub
sBar_0
sBar_1
sPanelTape
sPanel
sPlane
sWall
sAirTT
sExpHall
sExpRockBox
sTopRock
sOuterWaterPool
sTyvek_shell
sDeadWater_shell
HamamatsuR12860sMask_virtual
NNVTMCPPMTsMask_virtual
sWaterTube
mask_PMT_20inch_vetosMask_virtual
sAirGap
sPoolLining
sBottomRock
sWorld
EOS
)

elv="${elv},sTarget,sAcrylic" 


echo $elv

logging(){ 
   type $FUNCNAME
   export SGeoConfig__ELVSelection_VERBOSE=1
   export CSGFoundry=INFO
}

[ -n "$LOG" ] && logging 


moi=EXTENT:40000
export MOI=${MOI:-$moi}
export ELV=t:$elv 

~/o/cx.sh

#ELV=filepath:/tmp/elv.txt MOI=EXTENT:40000 ~/o/cx.sh



