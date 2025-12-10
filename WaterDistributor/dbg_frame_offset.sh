#!/bin/bash

usage(){ cat << EOU

~/j/WaterDistributor/dbg_frame_offset.sh

EOU
}

export CSGTarget=INFO 
export FULLSCREEN=0 
export CSGFoundry__getFrame_VERBOSE=1 
export SGLFW__renderloop_tail_LEVEL=1 

export SGLM__setTreeScene_DUMP=1
export stree__get_frame_global_LVID=124

export MOI=0.000,0.000,18935.000,1435.000 

cxr_min.sh $*


