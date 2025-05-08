#!/bin/bash

######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=genforAFG

######## Part 2 #########

lscpu
nvidia-smi

mkdir ok_clu
pushd ok_clu
source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.3.0_Opticks-v0.4.1/el9_amd64_gcc11/Mon/envset.sh
export CUDA_VISIBLE_DEVICES=0
export OPTICKS_MAX_BOUNCE=31
export OPTICKS_EVENT_MODE=Minimal
export HOME=/hpcfs/juno/junogpu/yangdingyong
export TMP=/hpcfs/juno/junogpu/yangdingyong/datas/test/mode1/tmp

time tut_detsim.py \
    --output oj_edm.root \
    --user-output oj_user.root \
    --evtmax 1000 \
    --seed 42 \
    gun \
    --momentums 1.0;

touch done_flag
popd
