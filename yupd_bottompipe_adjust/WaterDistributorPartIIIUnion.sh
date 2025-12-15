#!/bin/bash

usage(){ cat << EOU

~/j//WaterDistributorPartIIIUnion.sh


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





