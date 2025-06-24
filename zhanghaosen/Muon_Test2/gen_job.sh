#!/bin/bash

#nEvent=("5" "10" "20" "50" "100" "180" "200")
#nEvent=("10" "20" "50" "100" "170" "200" "260")
#nEvent=("10" "20" "50" "70" "100" "170")
nEvent=("5")

pushd /hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/run

for n in "${nEvent[@]}"; do

pushd /hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/Tmp
mkdir tmp$n
popd

bash /hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/gen_file.sh $n
echo  "TUTORIALROOT == " $TUTORIALROOT

cat>"run1_$n.sh"<<EOF
#!/bin/bash

######## Part 1 #########
#SBATCH --partition=gpu
#SBATCH --qos=normal
#SBATCH --account=junogpu
#SBATCH --ntasks=1
#SBATCH --mem-per-cpu=16000
#SBATCH --gpus=v100:1
#SBATCH --job-name=run1_$n
#SBATCH --output=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/log/run1_$n.txt

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
export TMP=/hpcfs/juno/junogpu/zhanghaosen/Muon_Test2/Tmp/tmp$n

time tut_detsim.py \\
    --no-gdml \\
    --pmtsd-merge-twindow 1.0 \\
    --event-split \\
    --output oj_edm_$n.root \\
    --user-output oj_user_$n.root \\
    --evtmax $n \\
    --seed $n \\
    hepevt \\
    --file file$n;

touch done_flag_$n
popd

EOF

chmod +x run1_$n.sh
sbatch run1_$n.sh

done

popd
