#!/bin/bash

usage(){ cat << EOU


Haosen get SEGV at 5th event

EOU
}


source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/envset.sh
export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=63
export OPTICKS_EVENT_MODE=Minimal
#export HOME=/hpcfs/juno/junogpu/zhanghaosen
#export TMP=/hpcfs/juno/junogpu/zhanghaosen/Test1/GPU2/mode1_muon_gun/tmp


source dbg__.sh

dbg__
   $(which python) \
   $(which tut_detsim.py) \
   --no-gdml \
   --pmtsd-merge-twindow 1.0 \
   --event-split \
   --output oj_edm.root \
   --user-output oj_user.root \
   --evtmax 5 \
   --seed 42 \
   gun \
   --particles mu+ \
   --positions 0 0 20000 \
   --directions 0 8 -1 \
   --momentums 20000;

