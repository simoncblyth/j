#!/bin/bash

######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=run1_5
#SBATCH --output=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/log/run1_5.txt

######## Part 2 #########

lscpu
nvidia-smi

pushd /hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/root
source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.4.5/el9_amd64_gcc11/Fri/envset.sh
export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=63
export OPTICKS_EVENT_MODE=Minimal
export OPTICKS_HIT_MASK=EC
export HOME=/hpcfs/juno/junogpu/zhanghaosen
export TMP=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/Tmp/tmp5

time tut_detsim.py \
    --no-gdml \
    --pmtsd-merge-twindow 1.0 \
    --event-split \
    --output oj_edm_5.root \
    --user-output oj_user_5.root \
    --evtmax 5 \
    --seed 5 \
    hepevt \
    --file file5;

touch done_flag_5
popd

