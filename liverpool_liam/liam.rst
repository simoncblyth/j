Hi Liam,

> Sorry for the delay; I was serving jury duty for the past two weeks. But this
> morning I have got both the junosw and opticks cvmfs mounts on the Liverpool
> machines. Just wondering now if there is any guide to using opticks so I can
> try running on the Liverpool machines.

Opticks and Opticks+JUNOSW "OJ" are still moving too fast for any definitive guides to usage.   

For Opticks testing and interactive usage, visualization etc.. it is 
very useful to have a workstation(or Linux laptop) with NVIDIA GPUs (expecially recent RTX ones) 
and CVMFS setup on it.  If you do not have access to a GPU workstation
you can just try out batch submissions to your GPU cluster. 

The details of the scripts you need for submission to your batch system will
need localization to your file systems and environment. Are you using slurm ?

Below is included a script for double muon simulation from Zhenning, 曲振宁 <quzn@ihep.ac.cn> 
I will give some comments on what some of the lines of that script are doing.


#SBATCH --array=1-200%20
    config 200 jobs with 20 running at once

    you will need to adjust the numbers to the size of your cluster and
    the size of production you want to fo

#SBATCH --gpu-bind=single:1
    ensure that each job gets exclusive access to a GPU,
    which is needed for OJ to avoid VRAM errors
      

source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.5/el9_amd64_gcc11/2025_10_24/envset.sh

    That is sourcing the OJ environment setup "envset.sh" for a particular release. There is now a newer dated release
    that should be used. There are also daily releases with day names like "Wed" but as those may be from
    merge requests you should normally stick to the latest dated release::

        A[blyth@localhost releases]$ pwd
        /cvmfs/opticks.ihep.ac.cn/oj/releases
        A[blyth@localhost releases]$ readlink */el9_amd64_gcc11/LastRef
        2025_04_14
        2025_06_01
        2025_06_24
        2025_06_25
        2025_07_07
        2025_07_17
        2025_09_30
        2025_10_24
        2025_10_29

So the current recommended version is::

    source /cvmfs/opticks.ihep.ac.cn/oj/releases/J25.4.0_Opticks-v0.5.5/el9_amd64_gcc11/2025_10_29/envset.sh

Notice the use of "(" and ")" in the script to make a sub-shell to allow two distinct environments to be used.  
That is kinda dirty, but is sometimes expedient to use a particular version of Muon.exe


Envvars that configure the Opticks simulation and control logging, profiling etc..::

    export SEvt__MINTIME=1    # dump kernel launch times to the logfile called something like python3.11.log

    # export CUDA_VISIBLE_DEVICES=0      ## manual way to pick GPU to use, should NOT use this with "#SBATCH --gpu-bind=single:1"
    export OPTICKS_MAX_BOUNCE=63         ## increases from default of 31, "steps" is better name than "bounce" 
    # export OPTICKS_MAX_PHOTON=M2000    ## no longer needed, as default in latest release is G1000 for 1000 billion

    export SProf__WRITE=1   # enable writing time and memory profiling into SProf.txt in invoking directory



As profiling files, logfiles etc have fixed names, you should improve the below script
to avoid different jobs over-writing each other when using slurm job arrays
by creating a LOGDIR directory that you cd/pushd to before invoking the 
python command, eg something like::

     LOGDIR=$(printf "J%0.5d" "${SLURM_ARRAY_TASK_ID:-0}")
     mkdir -p $LOGDIR
     pushd $LOGDIR
     ... command invoking executable...
     popd


--pmt-hit-type 1
    that is normal hits, in the current release the smaller 
    type 2 or muon hits (quarter the size of normal hits) is not yet supported with Opticks
    [you get millions of lines of error messages and no hits with current release if you try type 2]
 
    Supporting and profiting from type 2 hits is something that I hope to release within a few weeks


Regarding the rest of the detsim options and Muon.exe options, or how to do atmospheric neutrinos if that 
is your task, you should consult with experts from your group. 

Please report problems by copy/paste descriptions of what you did and what you got.


Simon
 






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



