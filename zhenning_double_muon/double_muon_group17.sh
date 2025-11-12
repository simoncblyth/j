#!/bin/bash

#SBATCH -A juno
#SBATCH --partition=JUNO
#SBATCH --qos=normal
#SBATCH -J double-muon-group17
#SBATCH --ntasks=1
#SBATCH --array=1-200%20
#SBATCH -c 8
#SBATCH --time=360
#SBATCH --mem-per-cpu=10240
#SBATCH --chdir=/dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/script/group17
#SBATCH --output=/dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/log/group17/%x.%A_%a.out
#SBATCH --error=/dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/log/group17/%x.%A_%a.err
## #SBATCH --gres=gpu:1
#SBATCH --gpus-per-task=1
#SBATCH --gpu-bind=single:1

source /hpcfs/software/modules/init/profile.sh

export PATH=/cvmfs/software.csns.ihep.ac.cn/softwares/cuda-12.9/bin:$PATH
export LD_LIBRARY_PATH=/cvmfs/software.csns.ihep.ac.cn/softwares/cuda-12.9/lib64:$LD_LIBRARY_PATH

group_id=17
seed=$(( group_id * 100000 + SLURM_ARRAY_TASK_ID ))
evtmax=5

echo "###### Generator ######"
(
    source /cvmfs/juno.ihep.ac.cn/el9_amd64_gcc11/Release/J25.6.0/setup.sh
    Muon.exe -seed ${seed} \
             -o /dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/gen/group17/genmuon-${SLURM_ARRAY_TASK_ID}.txt \
             -n ${evtmax} \
             -s juno -v WP -r Yes -cdls -mult 1 -ntrks 2 \
             -music_dir /cvmfs/juno-wg.ihep.ac.cn/Simulation/data/sandbox/MC25A/dbdata/offline-data/Generator/Muon/conf2507a
)

echo "###### DetSim ######"
(
    # source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.1/el9_amd64_gcc11/2025_07_17/envset.sh
    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.5/el9_amd64_gcc11/2025_10_24/envset.sh

    export SEvt__MINTIME=1    # dump kernel launch times

    # export CUDA_VISIBLE_DEVICES=0
    export OPTICKS_MAX_BOUNCE=63
    # export OPTICKS_MAX_PHOTON=M2000

    export SProf__WRITE=1   # enable the time and memory profiling

    $(which python) \
        $(which tut_detsim.py) \
        --evtmax ${evtmax} \
        --seed ${seed} \
        --no-gdml \
        --pmt-hit-type 1 \
        --pmtsd-merge-twindow 1.0 \
        --replace-param "Material.LS.scale.AbsorptionLenAfter:86.5, Material.Water.scale.abs_after:133.6*m" \
        --event-split \
        --anamgr-muon --anamgr-tt \
        --output /dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/data/group17/muon_edm.${SLURM_ARRAY_TASK_ID}.root \
        --user-output /dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/data/group17/muon_user.${SLURM_ARRAY_TASK_ID}.root \
        hepevt --exe Muon --file /dg_hpc/JUNO/junodata/Opticks/data_production/doublemuon/gen/group17/genmuon-${SLURM_ARRAY_TASK_ID}.txt
)

echo "###### Done ######"
