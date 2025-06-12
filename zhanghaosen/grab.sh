#!/bin/bash

rel=Test1/GPU/mode1_muon
mkdir -p $rel
cmd="scp L:/hpcfs/juno/junogpu/zhanghaosen/$rel/generation_opticks_mode1_muon.sh $rel/"
echo $cmd
eval $cmd




