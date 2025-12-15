#!/bin/bash

usage(){ cat << EOU

~/j/WaterDistributor/dbg_frame_offset.sh


    (ok) A[blyth@localhost desc]$ pwd
    /home/blyth/junosw/InstallArea/.opticks/GEOM/J25_4_0_opticks_Debug/CSGFoundry/SSim/stree/desc

    (ok) A[blyth@localhost desc]$ grep -i WaterDistrib nds.txt
     uv    124 :  cn      2  ix  67890  un Waterdistributor_2
     uv    125 :  cn      2  ix  67889  un Waterdistributor_3
     uv     33 :  cn      2  ix  65742  un Waterdistributor_0
     uv     34 :  cn      2  ix  65741  un Waterdistributor_1
     uv     27 :  cn      1  ix  65735  un WaterDistributorPipePartIII_1
     uv     26 :  cn      1  ix  65734  un WaterDistributorPipePartIII_0
     uv     23 :  cn      1  ix  65732  un AirGapWaterDistributorPipe_2
     uv     22 :  cn      1  ix  65731  un AirGapWaterDistributorPipe_1
     uv     21 :  cn      1  ix  65730  un AirGapWaterDistributorPipe_0
     uv     75 :  cn      1  ix  66573  un WaterDistributorPipeOuter_2
     uv     32 :  cn      1  ix  65740  un WaterDistributorPartIIIUnion
     uv     35 :  cn      1  ix  65745  un LowerWaterDistributorSeg1_0
     uv     36 :  cn      1  ix  65746  un LowerWaterDistributorSeg1_1
     uv     37 :  cn      1  ix  65747  un LowerWaterDistributorSeg1_2
     uv    336 :  cn      1  ix  66569  un sOuterReflectorInCD_TSubWaterDistributor_cutTube2
     uv    335 :  cn      1  ix  66570  un sOuterWaterInCD_TSubWaterDistributor_cutTube2
     uv     73 :  cn      1  ix  66571  un WaterDistributorPipeOuter_0
     uv     74 :  cn      1  ix  66572  un WaterDistributorPipeOuter_1
     uv     76 :  cn      1  ix  66574  un LowerWaterDistributorSeg2_0
     uv     77 :  cn      1  ix  66575  un LowerWaterDistributorSeg2_1
     uv     78 :  cn      1  ix  66576  un LowerWaterDistributorSeg2_2
     uv    334 :  cn      1  ix  67887  un sInnerReflectorInCD_TSubWaterDistributor_cutTube2
     uv    333 :  cn      1  ix  67888  un sInnerWater_TSubWaterDistributor_cutTube2
     uv    126 :  cn      1  ix  67893  un WaterDistributorPipeInner_0
     uv    127 :  cn      1  ix  67894  un WaterDistributorPipeInner_1
     uv    128 :  cn      1  ix  67895  un WaterDistributorPipeInner_2
     uv    129 :  cn      1  ix  67896  un LowerWaterDistributorSeg3_0
     uv    130 :  cn      1  ix  67897  un LowerWaterDistributorSeg3_1
     uv    131 :  cn      1  ix  67898  un LowerWaterDistributorSeg3_2
     uv     28 :  cn      1  ix  65736  un WaterDistributorPipePartIII_2




EOU
}

export CSGTarget=INFO 
export FULLSCREEN=0 
export CSGFoundry__getFrame_VERBOSE=1 
export SGLFW__renderloop_tail_LEVEL=1 

export SGLM__setTreeScene_DUMP=1

#LVID=125   # Waterdistributor_3
LVID=32    # WaterDistributorPartIIIUnion


export stree__get_frame_global_LVID=$LVID
export stree__get_node_bb_LVID=$LVID
#export stree__get_node_bb_CONSTITUENT=0


#export MOI=0.000,0.000,18935.000,1435.000 

defarg=cxr
arg=${1:-$defarg}

if [ "${arg/cxr}" != "${arg}" ]; then
   cxr_min.sh $*
fi

if [ "${arg/f}" != "${arg}" ]; then
   cd /data1/blyth/tmp/GEOM/J25_4_0_opticks_Debug/CSGOptiXRenderInteractiveTest 
   f.sh
fi 





